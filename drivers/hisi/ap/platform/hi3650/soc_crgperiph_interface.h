#ifndef __SOC_CRGPERIPH_INTERFACE_H__
#define __SOC_CRGPERIPH_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CRGPERIPH_PEREN0_ADDR(base) ((base) + (0x000))
#define SOC_CRGPERIPH_PERDIS0_ADDR(base) ((base) + (0x004))
#define SOC_CRGPERIPH_PERCLKEN0_ADDR(base) ((base) + (0x008))
#define SOC_CRGPERIPH_PERSTAT0_ADDR(base) ((base) + (0x00C))
#define SOC_CRGPERIPH_PEREN1_ADDR(base) ((base) + (0x010))
#define SOC_CRGPERIPH_PERDIS1_ADDR(base) ((base) + (0x014))
#define SOC_CRGPERIPH_PERCLKEN1_ADDR(base) ((base) + (0x018))
#define SOC_CRGPERIPH_PERSTAT1_ADDR(base) ((base) + (0x01C))
#define SOC_CRGPERIPH_PEREN2_ADDR(base) ((base) + (0x020))
#define SOC_CRGPERIPH_PERDIS2_ADDR(base) ((base) + (0x024))
#define SOC_CRGPERIPH_PERCLKEN2_ADDR(base) ((base) + (0x028))
#define SOC_CRGPERIPH_PERSTAT2_ADDR(base) ((base) + (0x02C))
#define SOC_CRGPERIPH_PEREN3_ADDR(base) ((base) + (0x030))
#define SOC_CRGPERIPH_PERDIS3_ADDR(base) ((base) + (0x034))
#define SOC_CRGPERIPH_PERCLKEN3_ADDR(base) ((base) + (0x038))
#define SOC_CRGPERIPH_PERSTAT3_ADDR(base) ((base) + (0x03C))
#define SOC_CRGPERIPH_PEREN4_ADDR(base) ((base) + (0x040))
#define SOC_CRGPERIPH_PERDIS4_ADDR(base) ((base) + (0x044))
#define SOC_CRGPERIPH_PERCLKEN4_ADDR(base) ((base) + (0x048))
#define SOC_CRGPERIPH_PERSTAT4_ADDR(base) ((base) + (0x04C))
#define SOC_CRGPERIPH_PEREN5_ADDR(base) ((base) + (0x050))
#define SOC_CRGPERIPH_PERDIS5_ADDR(base) ((base) + (0x054))
#define SOC_CRGPERIPH_PERCLKEN5_ADDR(base) ((base) + (0x058))
#define SOC_CRGPERIPH_PERSTAT5_ADDR(base) ((base) + (0x05C))
#define SOC_CRGPERIPH_PERRSTEN0_ADDR(base) ((base) + (0x060))
#define SOC_CRGPERIPH_PERRSTDIS0_ADDR(base) ((base) + (0x064))
#define SOC_CRGPERIPH_PERRSTSTAT0_ADDR(base) ((base) + (0x068))
#define SOC_CRGPERIPH_PERRSTEN1_ADDR(base) ((base) + (0x06C))
#define SOC_CRGPERIPH_PERRSTDIS1_ADDR(base) ((base) + (0x070))
#define SOC_CRGPERIPH_PERRSTSTAT1_ADDR(base) ((base) + (0x074))
#define SOC_CRGPERIPH_PERRSTEN2_ADDR(base) ((base) + (0x078))
#define SOC_CRGPERIPH_PERRSTDIS2_ADDR(base) ((base) + (0x07C))
#define SOC_CRGPERIPH_PERRSTSTAT2_ADDR(base) ((base) + (0x080))
#define SOC_CRGPERIPH_PERRSTEN3_ADDR(base) ((base) + (0x084))
#define SOC_CRGPERIPH_PERRSTDIS3_ADDR(base) ((base) + (0x088))
#define SOC_CRGPERIPH_PERRSTSTAT3_ADDR(base) ((base) + (0x008C))
#define SOC_CRGPERIPH_PERRSTEN4_ADDR(base) ((base) + (0x090))
#define SOC_CRGPERIPH_PERRSTDIS4_ADDR(base) ((base) + (0x094))
#define SOC_CRGPERIPH_PERRSTSTAT4_ADDR(base) ((base) + (0x098))
#define SOC_CRGPERIPH_PERRSTEN5_ADDR(base) ((base) + (0x09C))
#define SOC_CRGPERIPH_PERRSTDIS5_ADDR(base) ((base) + (0x0A0))
#define SOC_CRGPERIPH_PERRSTSTAT5_ADDR(base) ((base) + (0x0A4))
#define SOC_CRGPERIPH_CLKDIV0_ADDR(base) ((base) + (0x0A8))
#define SOC_CRGPERIPH_CLKDIV1_ADDR(base) ((base) + (0x0AC))
#define SOC_CRGPERIPH_CLKDIV2_ADDR(base) ((base) + (0x0B0))
#define SOC_CRGPERIPH_CLKDIV3_ADDR(base) ((base) + (0x0B4))
#define SOC_CRGPERIPH_CLKDIV4_ADDR(base) ((base) + (0x0B8))
#define SOC_CRGPERIPH_CLKDIV5_ADDR(base) ((base) + (0x0BC))
#define SOC_CRGPERIPH_CLKDIV6_ADDR(base) ((base) + (0x0C0))
#define SOC_CRGPERIPH_CLKDIV7_ADDR(base) ((base) + (0x0C4))
#define SOC_CRGPERIPH_CLKDIV8_ADDR(base) ((base) + (0x0C8))
#define SOC_CRGPERIPH_CLKDIV9_ADDR(base) ((base) + (0x0CC))
#define SOC_CRGPERIPH_CLKDIV10_ADDR(base) ((base) + (0x0D0))
#define SOC_CRGPERIPH_CLKDIV11_ADDR(base) ((base) + (0x0D4))
#define SOC_CRGPERIPH_CLKDIV12_ADDR(base) ((base) + (0x0D8))
#define SOC_CRGPERIPH_CLKDIV13_ADDR(base) ((base) + (0x0DC))
#define SOC_CRGPERIPH_CLKDIV14_ADDR(base) ((base) + (0x0E0))
#define SOC_CRGPERIPH_CLKDIV15_ADDR(base) ((base) + (0x0E4))
#define SOC_CRGPERIPH_CLKDIV16_ADDR(base) ((base) + (0x0E8))
#define SOC_CRGPERIPH_CLKDIV17_ADDR(base) ((base) + (0x0EC))
#define SOC_CRGPERIPH_CLKDIV18_ADDR(base) ((base) + (0x0F0))
#define SOC_CRGPERIPH_CLKDIV19_ADDR(base) ((base) + (0x0F4))
#define SOC_CRGPERIPH_CLKDIV20_ADDR(base) ((base) + (0x0F8))
#define SOC_CRGPERIPH_CLKDIV21_ADDR(base) ((base) + (0x0FC))
#define SOC_CRGPERIPH_CLKDIV22_ADDR(base) ((base) + (0x100))
#define SOC_CRGPERIPH_CLKDIV23_ADDR(base) ((base) + (0x104))
#define SOC_CRGPERIPH_CLKDIV24_ADDR(base) ((base) + (0x108))
#define SOC_CRGPERIPH_CLKDIV25_ADDR(base) ((base) + (0x10C))
#define SOC_CRGPERIPH_PER_STAT0_ADDR(base) ((base) + (0x110))
#define SOC_CRGPERIPH_PER_STAT1_ADDR(base) ((base) + (0x114))
#define SOC_CRGPERIPH_PER_STAT2_ADDR(base) ((base) + (0x118))
#define SOC_CRGPERIPH_PER_STAT3_ADDR(base) ((base) + (0x11C))
#define SOC_CRGPERIPH_PERCTRL0_ADDR(base) ((base) + (0x120))
#define SOC_CRGPERIPH_PERCTRL1_ADDR(base) ((base) + (0x124))
#define SOC_CRGPERIPH_PERCTRL2_ADDR(base) ((base) + (0x128))
#define SOC_CRGPERIPH_PERCTRL3_ADDR(base) ((base) + (0x12C))
#define SOC_CRGPERIPH_PERCTRL4_ADDR(base) ((base) + (0x130))
#define SOC_CRGPERIPH_PERCTRL5_ADDR(base) ((base) + (0x134))
#define SOC_CRGPERIPH_PERCTRL6_ADDR(base) ((base) + (0x138))
#define SOC_CRGPERIPH_PERTIMECTRL_ADDR(base) ((base) + (0x140))
#define SOC_CRGPERIPH_ISOEN_ADDR(base) ((base) + (0x144))
#define SOC_CRGPERIPH_ISODIS_ADDR(base) ((base) + (0x148))
#define SOC_CRGPERIPH_ISOSTAT_ADDR(base) ((base) + (0x14C))
#define SOC_CRGPERIPH_PERPWREN_ADDR(base) ((base) + (0x150))
#define SOC_CRGPERIPH_PERPWRDIS_ADDR(base) ((base) + (0x154))
#define SOC_CRGPERIPH_PERPWRSTAT_ADDR(base) ((base) + (0x158))
#define SOC_CRGPERIPH_PERPWRACK_ADDR(base) ((base) + (0x15C))
#define SOC_CRGPERIPH_A53_CLKEN_ADDR(base) ((base) + (0x160))
#define SOC_CRGPERIPH_A53_RSTEN_ADDR(base) ((base) + (0x164))
#define SOC_CRGPERIPH_A53_RSTDIS_ADDR(base) ((base) + (0x168))
#define SOC_CRGPERIPH_A53_RSTSTAT_ADDR(base) ((base) + (0x16C))
#define SOC_CRGPERIPH_A53_ADBLPSTAT_ADDR(base) ((base) + (0x174))
#define SOC_CRGPERIPH_A53_CTRL0_ADDR(base) ((base) + (0x178))
#define SOC_CRGPERIPH_A53_CTRL1_ADDR(base) ((base) + (0x17C))
#define SOC_CRGPERIPH_A53_CTRL2_ADDR(base) ((base) + (0x180))
#define SOC_CRGPERIPH_A53_STAT_ADDR(base) ((base) + (0x194))
#define SOC_CRGPERIPH_MAIA_CLKEN_ADDR(base) ((base) + (0x1C0))
#define SOC_CRGPERIPH_MAIA_RSTEN_ADDR(base) ((base) + (0x1C4))
#define SOC_CRGPERIPH_MAIA_RSTDIS_ADDR(base) ((base) + (0x1C8))
#define SOC_CRGPERIPH_MAIA_RSTSTAT_ADDR(base) ((base) + (0x1CC))
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_ADDR(base) ((base) + (0x1D4))
#define SOC_CRGPERIPH_MAIA_CTRL0_ADDR(base) ((base) + (0x1D8))
#define SOC_CRGPERIPH_MAIA_CTRL1_ADDR(base) ((base) + (0x1DC))
#define SOC_CRGPERIPH_MAIA_CTRL2_ADDR(base) ((base) + (0x1E0))
#define SOC_CRGPERIPH_MAIA_STAT_ADDR(base) ((base) + (0x1F4))
#define SOC_CRGPERIPH_MAIA_STAT_1_ADDR(base) ((base) + (0x1F8))
#define SOC_CRGPERIPH_CORESIGHTSTAT_ADDR(base) ((base) + (0x200))
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_ADDR(base) ((base) + (0x204))
#define SOC_CRGPERIPH_CORESIGHTCTRL0_ADDR(base) ((base) + (0x208))
#define SOC_CRGPERIPH_CORESIGHTETFINT_ADDR(base) ((base) + (0x20C))
#define SOC_CRGPERIPH_CORESIGHTETRINT_ADDR(base) ((base) + (0x210))
#define SOC_CRGPERIPH_CCI400STAT1_ADDR(base) ((base) + (0x21C))
#define SOC_CRGPERIPH_ADB400STAT_ADDR(base) ((base) + (0x220))
#define SOC_CRGPERIPH_CCI400CTRL0_ADDR(base) ((base) + (0x228))
#define SOC_CRGPERIPH_CCI400CTRL1_ADDR(base) ((base) + (0x22C))
#define SOC_CRGPERIPH_CCI400STAT_ADDR(base) ((base) + (0x230))
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_ADDR(base) ((base) + (0x234))
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_ADDR(base) ((base) + (0x238))
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_ADDR(base) ((base) + (0x240))
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ADDR(base) ((base) + (0x244))
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_ADDR(base) ((base) + (0x248))
#define SOC_CRGPERIPH_A53_PDCEN_ADDR(base) ((base) + (0x260))
#define SOC_CRGPERIPH_A53_COREPWRINTEN_ADDR(base) ((base) + (0x264))
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_ADDR(base) ((base) + (0x268))
#define SOC_CRGPERIPH_A53_COREGICMASK_ADDR(base) ((base) + (0x26C))
#define SOC_CRGPERIPH_A53_COREPOWERUP_ADDR(base) ((base) + (0x270))
#define SOC_CRGPERIPH_A53_COREPOWERDN_ADDR(base) ((base) + (0x274))
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_ADDR(base) ((base) + (0x278))
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_ADDR(base) ((base) + (0x27C))
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_ADDR(base) ((base) + (0x280))
#define SOC_CRGPERIPH_A53_COREISOTIME_ADDR(base) ((base) + (0x284))
#define SOC_CRGPERIPH_A53_COREDBGTIME_ADDR(base) ((base) + (0x288))
#define SOC_CRGPERIPH_A53_CORERSTTIME_ADDR(base) ((base) + (0x28C))
#define SOC_CRGPERIPH_A53_COREURSTTIME_ADDR(base) ((base) + (0x290))
#define SOC_CRGPERIPH_MAIA_PDCEN_ADDR(base) ((base) + (0x300))
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_ADDR(base) ((base) + (0x304))
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_ADDR(base) ((base) + (0x308))
#define SOC_CRGPERIPH_MAIA_COREGICMASK_ADDR(base) ((base) + (0x30C))
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_ADDR(base) ((base) + (0x310))
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_ADDR(base) ((base) + (0x314))
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_ADDR(base) ((base) + (0x318))
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_ADDR(base) ((base) + (0x31C))
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_ADDR(base) ((base) + (0x320))
#define SOC_CRGPERIPH_MAIA_COREISOTIME_ADDR(base) ((base) + (0x324))
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_ADDR(base) ((base) + (0x328))
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_ADDR(base) ((base) + (0x32C))
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_ADDR(base) ((base) + (0x330))
#define SOC_CRGPERIPH_ISPA7_CLKEN_ADDR(base) ((base) + (0x340))
#define SOC_CRGPERIPH_ISPA7_RSTEN_ADDR(base) ((base) + (0x344))
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ADDR(base) ((base) + (0x348))
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ADDR(base) ((base) + (0x34C))
#define SOC_CRGPERIPH_ISPA7_STAT_ADDR(base) ((base) + (0x354))
#define SOC_CRGPERIPH_PERI_AUTODIV0_ADDR(base) ((base) + (0x360))
#define SOC_CRGPERIPH_PERI_AUTODIV1_ADDR(base) ((base) + (0x364))
#define SOC_CRGPERIPH_PERI_AUTODIV2_ADDR(base) ((base) + (0x368))
#define SOC_CRGPERIPH_PERI_AUTODIV3_ADDR(base) ((base) + (0x36C))
#define SOC_CRGPERIPH_PERI_AUTODIV4_ADDR(base) ((base) + (0x370))
#define SOC_CRGPERIPH_PERI_AUTODIV5_ADDR(base) ((base) + (0x374))
#define SOC_CRGPERIPH_PERI_AUTODIV6_ADDR(base) ((base) + (0x378))
#define SOC_CRGPERIPH_PERI_AUTODIV7_ADDR(base) ((base) + (0x37C))
#define SOC_CRGPERIPH_PERI_AUTODIV8_ADDR(base) ((base) + (0x380))
#define SOC_CRGPERIPH_PERI_AUTODIV9_ADDR(base) ((base) + (0x384))
#define SOC_CRGPERIPH_PERI_AUTODIV10_ADDR(base) ((base) + (0x388))
#define SOC_CRGPERIPH_PERI_AUTODIV11_ADDR(base) ((base) + (0x38C))
#define SOC_CRGPERIPH_PERI_AUTODIV12_ADDR(base) ((base) + (0x390))
#define SOC_CRGPERIPH_PERI_AUTODIV13_ADDR(base) ((base) + (0x394))
#define SOC_CRGPERIPH_PERI_AUTODIV14_ADDR(base) ((base) + (0x398))
#define SOC_CRGPERIPH_PERI_AUTODIV15_ADDR(base) ((base) + (0x39C))
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_ADDR(base) ((base) + (0x404))
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_ADDR(base) ((base) + (0x408))
#define SOC_CRGPERIPH_PEREN6_ADDR(base) ((base) + (0x410))
#define SOC_CRGPERIPH_PERDIS6_ADDR(base) ((base) + (0x414))
#define SOC_CRGPERIPH_PERCLKEN6_ADDR(base) ((base) + (0x418))
#define SOC_CRGPERIPH_PERSTAT6_ADDR(base) ((base) + (0x41C))
#define SOC_CRGPERIPH_PEREN7_ADDR(base) ((base) + (0x420))
#define SOC_CRGPERIPH_PERDIS7_ADDR(base) ((base) + (0x424))
#define SOC_CRGPERIPH_PERCLKEN7_ADDR(base) ((base) + (0x428))
#define SOC_CRGPERIPH_PERSTAT7_ADDR(base) ((base) + (0x42C))
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ADDR(base) ((base) + (0xC00))
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ADDR(base) ((base) + (0xC04))
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ADDR(base) ((base) + (0xC08))
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ADDR(base) ((base) + (0xC80))
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ADDR(base) ((base) + (0xC84))
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ADDR(base) ((base) + (0xC88))
#define SOC_CRGPERIPH_ISPA7_CTRL0_ADDR(base) ((base) + (0xC90))
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ADDR(base) ((base) + (0xD00))
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ADDR(base) ((base) + (0xD04))
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ADDR(base) ((base) + (0xD08))
#define SOC_CRGPERIPH_A53_CTRL3_ADDR(base) ((base) + (0xE00))
#define SOC_CRGPERIPH_A53_CTRL4_ADDR(base) ((base) + (0xE04))
#define SOC_CRGPERIPH_A53_CTRL5_ADDR(base) ((base) + (0xE08))
#define SOC_CRGPERIPH_A53_CTRL6_ADDR(base) ((base) + (0xE0C))
#define SOC_CRGPERIPH_MAIA_CTRL3_ADDR(base) ((base) + (0xE10))
#define SOC_CRGPERIPH_MAIA_CTRL4_ADDR(base) ((base) + (0xE14))
#define SOC_CRGPERIPH_MAIA_CTRL5_ADDR(base) ((base) + (0xE18))
#define SOC_CRGPERIPH_MAIA_CTRL6_ADDR(base) ((base) + (0xE1C))
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ADDR(base) ((base) + (0xE20))
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ADDR(base) ((base) + (0xE24))
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ADDR(base) ((base) + (0xE28))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_b : 1;
        unsigned int gt_clk_ddrbyp_ckp0 : 1;
        unsigned int gt_clk_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_ref : 1;
        unsigned int gt_clk_vcodeccfg : 1;
        unsigned int gt_clk_vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_sysbus : 1;
        unsigned int gt_clk_cfgbus : 1;
        unsigned int gt_clk_sys2cfgbus : 1;
        unsigned int gt_clk_vivobus2ddrc : 1;
        unsigned int gt_hclk_emmc0 : 1;
        unsigned int gt_clk_mmc1peri2sysbus : 1;
        unsigned int gt_clk_mmc1_peribus : 1;
        unsigned int gt_hclk_emmc1 : 1;
        unsigned int gt_clk_mmc0peri2sysbus : 1;
        unsigned int gt_clk_mmc0_peribus : 1;
        unsigned int gt_hclk_sdio0 : 1;
        unsigned int gt_clk_lpm32cfgbus : 1;
        unsigned int gt_hclk_sdio1 : 1;
        unsigned int gt_clk_dmabus : 1;
        unsigned int gt_clk_dma2cfgbus : 1;
        unsigned int gt_clk_hclk_memrep : 1;
        unsigned int gt_clk_dbgsechsicbus : 1;
        unsigned int gt_clk_dbgsechsic2sysbus : 1;
        unsigned int gt_clk_ddrphy_a : 1;
        unsigned int gt_clk_ddrphy_c : 1;
        unsigned int gt_clk_ddrphy_d : 1;
        unsigned int gt_hclk_sd : 1;
        unsigned int gt_clk_aomm : 1;
    } reg;
} SOC_CRGPERIPH_PEREN0_UNION;
#endif
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_START (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_END (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_START (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_END (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_START (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_END (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_START (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_END (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_START (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_END (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_START (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_END (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_START (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_END (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_START (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_END (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_START (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_END (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_START (12)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_END (12)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_START (13)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_END (13)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_START (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_END (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_START (15)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_END (15)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_START (16)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_END (16)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_START (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_END (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_START (18)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_END (18)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_START (19)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_END (19)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_START (21)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_END (21)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_START (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_END (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_START (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_END (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_START (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_END (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_START (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_END (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_START (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_END (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_START (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_END (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_START (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_END (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_START (29)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_END (29)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_START (30)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_END (30)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_START (31)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_b : 1;
        unsigned int gt_clk_ddrbyp_ckp0 : 1;
        unsigned int gt_clk_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_ref : 1;
        unsigned int gt_clk_vcodeccfg : 1;
        unsigned int gt_clk_vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_sysbus : 1;
        unsigned int gt_clk_cfgbus : 1;
        unsigned int gt_clk_sys2cfgbus : 1;
        unsigned int gt_clk_vivobus2ddrc : 1;
        unsigned int gt_hclk_emmc0 : 1;
        unsigned int gt_clk_mmc1peri2sysbus : 1;
        unsigned int gt_clk_mmc1_peribus : 1;
        unsigned int gt_hclk_emmc1 : 1;
        unsigned int gt_clk_mmc0peri2sysbus : 1;
        unsigned int gt_clk_mmc0_peribus : 1;
        unsigned int gt_hclk_sdio0 : 1;
        unsigned int gt_clk_lpm32cfgbus : 1;
        unsigned int gt_hclk_sdio1 : 1;
        unsigned int gt_clk_dmabus : 1;
        unsigned int gt_clk_dma2cfgbus : 1;
        unsigned int gt_clk_hclk_memrep : 1;
        unsigned int gt_clk_dbgsechsicbus : 1;
        unsigned int gt_clk_dbgsechsic2sysbus : 1;
        unsigned int gt_clk_ddrphy_a : 1;
        unsigned int gt_clk_ddrphy_c : 1;
        unsigned int gt_clk_ddrphy_d : 1;
        unsigned int gt_hclk_sd : 1;
        unsigned int gt_clk_aomm : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_START (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_END (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_START (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_END (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_START (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_END (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_START (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_END (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_START (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_END (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_START (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_END (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_START (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_END (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_START (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_END (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_START (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_END (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_START (12)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_END (12)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_START (13)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_END (13)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_START (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_END (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_START (15)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_END (15)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_START (16)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_END (16)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_START (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_END (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_START (18)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_END (18)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_START (19)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_END (19)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_START (21)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_END (21)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_START (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_END (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_START (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_END (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_START (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_END (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_START (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_END (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_START (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_END (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_START (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_END (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_START (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_END (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_START (29)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_END (29)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_START (30)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_END (30)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_START (31)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_b : 1;
        unsigned int gt_clk_ddrbyp_ckp0 : 1;
        unsigned int gt_clk_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_ref : 1;
        unsigned int gt_clk_vcodeccfg : 1;
        unsigned int gt_clk_vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_sysbus : 1;
        unsigned int gt_clk_cfgbus : 1;
        unsigned int gt_clk_sys2cfgbus : 1;
        unsigned int gt_clk_vivobus2ddrc : 1;
        unsigned int gt_hclk_emmc0 : 1;
        unsigned int gt_clk_mmc1peri2sysbus : 1;
        unsigned int gt_clk_mmc1_peribus : 1;
        unsigned int gt_hclk_emmc1 : 1;
        unsigned int gt_clk_mmc0peri2sysbus : 1;
        unsigned int gt_clk_mmc0_peribus : 1;
        unsigned int gt_hclk_sdio0 : 1;
        unsigned int gt_clk_lpm32cfgbus : 1;
        unsigned int gt_hclk_sdio1 : 1;
        unsigned int gt_clk_dmabus : 1;
        unsigned int gt_clk_dma2cfgbus : 1;
        unsigned int gt_clk_hclk_memrep : 1;
        unsigned int gt_clk_dbgsechsicbus : 1;
        unsigned int gt_clk_dbgsechsic2sysbus : 1;
        unsigned int gt_clk_ddrphy_a : 1;
        unsigned int gt_clk_ddrphy_c : 1;
        unsigned int gt_clk_ddrphy_d : 1;
        unsigned int gt_hclk_sd : 1;
        unsigned int gt_clk_aomm : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_START (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_END (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_START (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_END (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_START (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_END (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_START (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_END (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_START (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_END (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_START (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_END (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_START (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_END (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_START (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_END (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_START (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_END (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_START (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_END (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_START (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_END (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_START (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_END (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_START (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_END (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_START (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_END (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_START (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_END (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_START (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_END (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_START (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_END (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_START (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_END (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_START (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_END (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_START (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_END (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_START (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_END (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_START (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_END (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_START (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_END (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_START (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_END (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_START (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_END (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_START (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_END (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_START (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_END (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_START (31)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_b : 1;
        unsigned int gt_clk_ddrbyp_ckp0 : 1;
        unsigned int gt_clk_ddrc : 1;
        unsigned int gt_clk_ddrcfg : 1;
        unsigned int gt_clk_ddrphy_ref : 1;
        unsigned int gt_clk_vcodeccfg : 1;
        unsigned int gt_clk_vcodecbus : 1;
        unsigned int gt_clk_ddrsys_noc : 1;
        unsigned int gt_clk_ddrsys_ao : 1;
        unsigned int gt_clk_sysbus : 1;
        unsigned int gt_clk_cfgbus : 1;
        unsigned int gt_clk_sys2cfgbus : 1;
        unsigned int gt_clk_vivobus2ddrc : 1;
        unsigned int gt_hclk_emmc0 : 1;
        unsigned int gt_clk_mmc1peri2sysbus : 1;
        unsigned int gt_clk_mmc1_peribus : 1;
        unsigned int gt_hclk_emmc1 : 1;
        unsigned int gt_clk_mmc0peri2sysbus : 1;
        unsigned int gt_clk_mmc0_peribus : 1;
        unsigned int gt_hclk_sdio0 : 1;
        unsigned int gt_clk_lpm32cfgbus : 1;
        unsigned int gt_hclk_sdio1 : 1;
        unsigned int gt_clk_dmabus : 1;
        unsigned int gt_clk_dma2cfgbus : 1;
        unsigned int gt_clk_hclk_memrep : 1;
        unsigned int gt_clk_dbgsechsicbus : 1;
        unsigned int gt_clk_dbgsechsic2sysbus : 1;
        unsigned int gt_clk_ddrphy_a : 1;
        unsigned int gt_clk_ddrphy_c : 1;
        unsigned int gt_clk_ddrphy_d : 1;
        unsigned int gt_hclk_sd : 1;
        unsigned int gt_clk_aomm : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_START (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_END (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_START (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_END (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_START (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_END (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_START (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_END (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_START (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_END (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_START (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_END (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_START (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_END (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_START (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_END (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_START (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_END (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_START (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_END (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_START (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_END (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_START (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_END (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_START (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_END (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_START (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_END (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_START (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_END (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_START (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_END (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_START (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_END (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_START (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_END (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_START (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_END (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_START (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_END (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_START (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_END (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_START (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_END (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_START (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_END (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_START (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_END (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_START (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_END (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_START (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_END (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_START (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_END (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_START (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_END (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_START (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_END (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_START (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_END (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_START (31)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_pclk_gpio0 : 1;
        unsigned int gt_pclk_gpio1 : 1;
        unsigned int gt_pclk_gpio2 : 1;
        unsigned int gt_pclk_gpio3 : 1;
        unsigned int gt_pclk_gpio4 : 1;
        unsigned int gt_pclk_gpio5 : 1;
        unsigned int gt_pclk_gpio6 : 1;
        unsigned int gt_pclk_gpio7 : 1;
        unsigned int gt_pclk_gpio8 : 1;
        unsigned int gt_pclk_gpio9 : 1;
        unsigned int gt_pclk_gpio10 : 1;
        unsigned int gt_pclk_gpio11 : 1;
        unsigned int gt_pclk_gpio12 : 1;
        unsigned int gt_pclk_gpio13 : 1;
        unsigned int gt_pclk_gpio14 : 1;
        unsigned int gt_pclk_gpio15 : 1;
        unsigned int gt_pclk_gpio16 : 1;
        unsigned int gt_pclk_gpio17 : 1;
        unsigned int gt_pclk_gpio18 : 1;
        unsigned int gt_pclk_gpio19 : 1;
        unsigned int gt_pclk_gpio20 : 1;
        unsigned int gt_pclk_gpio21 : 1;
        unsigned int gt_pclk_timer9 : 1;
        unsigned int gt_pclk_timer10 : 1;
        unsigned int gt_pclk_timer11 : 1;
        unsigned int gt_pclk_timer12 : 1;
        unsigned int gt_clk_socp_lpm3 : 1;
        unsigned int gt_clk_djtag : 1;
        unsigned int gt_clk_socp_acpu : 1;
        unsigned int gt_clk_socp_mcpu : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_CRGPERIPH_PEREN1_UNION;
#endif
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_START (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_END (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_START (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_END (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_START (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_END (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_START (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_END (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_START (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_END (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_START (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_END (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_START (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_END (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_START (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_END (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_START (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_END (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_START (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_END (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_START (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_END (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_START (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_END (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_START (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_END (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_START (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_END (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_START (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_END (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_START (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_END (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_START (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_END (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_START (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_END (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_START (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_END (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_START (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_END (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_START (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_END (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_START (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_END (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_START (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_END (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_START (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_END (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_START (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_END (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_START (25)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_END (25)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_START (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_END (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_START (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_END (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_START (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_END (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_START (29)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_pclk_gpio0 : 1;
        unsigned int gt_pclk_gpio1 : 1;
        unsigned int gt_pclk_gpio2 : 1;
        unsigned int gt_pclk_gpio3 : 1;
        unsigned int gt_pclk_gpio4 : 1;
        unsigned int gt_pclk_gpio5 : 1;
        unsigned int gt_pclk_gpio6 : 1;
        unsigned int gt_pclk_gpio7 : 1;
        unsigned int gt_pclk_gpio8 : 1;
        unsigned int gt_pclk_gpio9 : 1;
        unsigned int gt_pclk_gpio10 : 1;
        unsigned int gt_pclk_gpio11 : 1;
        unsigned int gt_pclk_gpio12 : 1;
        unsigned int gt_pclk_gpio13 : 1;
        unsigned int gt_pclk_gpio14 : 1;
        unsigned int gt_pclk_gpio15 : 1;
        unsigned int gt_pclk_gpio16 : 1;
        unsigned int gt_pclk_gpio17 : 1;
        unsigned int gt_pclk_gpio18 : 1;
        unsigned int gt_pclk_gpio19 : 1;
        unsigned int gt_pclk_gpio20 : 1;
        unsigned int gt_pclk_gpio21 : 1;
        unsigned int gt_pclk_timer9 : 1;
        unsigned int gt_pclk_timer10 : 1;
        unsigned int gt_pclk_timer11 : 1;
        unsigned int gt_pclk_timer12 : 1;
        unsigned int gt_clk_socp_lpm3 : 1;
        unsigned int gt_clk_djtag : 1;
        unsigned int gt_clk_socp_acpu : 1;
        unsigned int gt_clk_socp_mcpu : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_START (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_END (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_START (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_END (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_START (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_END (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_START (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_END (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_START (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_END (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_START (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_END (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_START (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_END (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_START (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_END (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_START (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_END (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_START (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_END (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_START (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_END (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_START (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_END (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_START (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_END (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_START (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_END (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_START (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_END (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_START (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_END (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_START (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_END (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_START (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_END (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_START (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_END (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_START (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_END (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_START (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_END (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_START (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_END (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_START (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_END (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_START (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_END (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_START (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_END (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_START (25)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_END (25)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_START (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_END (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_START (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_END (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_START (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_END (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_START (29)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_pclk_gpio0 : 1;
        unsigned int gt_pclk_gpio1 : 1;
        unsigned int gt_pclk_gpio2 : 1;
        unsigned int gt_pclk_gpio3 : 1;
        unsigned int gt_pclk_gpio4 : 1;
        unsigned int gt_pclk_gpio5 : 1;
        unsigned int gt_pclk_gpio6 : 1;
        unsigned int gt_pclk_gpio7 : 1;
        unsigned int gt_pclk_gpio8 : 1;
        unsigned int gt_pclk_gpio9 : 1;
        unsigned int gt_pclk_gpio10 : 1;
        unsigned int gt_pclk_gpio11 : 1;
        unsigned int gt_pclk_gpio12 : 1;
        unsigned int gt_pclk_gpio13 : 1;
        unsigned int gt_pclk_gpio14 : 1;
        unsigned int gt_pclk_gpio15 : 1;
        unsigned int gt_pclk_gpio16 : 1;
        unsigned int gt_pclk_gpio17 : 1;
        unsigned int gt_pclk_gpio18 : 1;
        unsigned int gt_pclk_gpio19 : 1;
        unsigned int gt_pclk_gpio20 : 1;
        unsigned int gt_pclk_gpio21 : 1;
        unsigned int gt_pclk_timer9 : 1;
        unsigned int gt_pclk_timer10 : 1;
        unsigned int gt_pclk_timer11 : 1;
        unsigned int gt_pclk_timer12 : 1;
        unsigned int gt_clk_socp_lpm3 : 1;
        unsigned int gt_clk_djtag : 1;
        unsigned int gt_clk_socp_acpu : 1;
        unsigned int gt_clk_socp_mcpu : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_START (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_END (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_START (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_END (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_START (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_END (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_START (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_END (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_START (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_END (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_START (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_END (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_START (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_END (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_START (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_END (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_START (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_END (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_START (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_END (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_START (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_END (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_START (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_END (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_START (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_END (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_START (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_END (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_START (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_END (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_START (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_END (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_START (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_END (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_START (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_END (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_START (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_END (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_START (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_END (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_START (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_END (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_START (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_END (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_START (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_END (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_START (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_END (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_START (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_END (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_START (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_END (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_START (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_END (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_START (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_END (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_START (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_END (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_START (29)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_pclk_gpio0 : 1;
        unsigned int gt_pclk_gpio1 : 1;
        unsigned int gt_pclk_gpio2 : 1;
        unsigned int gt_pclk_gpio3 : 1;
        unsigned int gt_pclk_gpio4 : 1;
        unsigned int gt_pclk_gpio5 : 1;
        unsigned int gt_pclk_gpio6 : 1;
        unsigned int gt_pclk_gpio7 : 1;
        unsigned int gt_pclk_gpio8 : 1;
        unsigned int gt_pclk_gpio9 : 1;
        unsigned int gt_pclk_gpio10 : 1;
        unsigned int gt_pclk_gpio11 : 1;
        unsigned int gt_pclk_gpio12 : 1;
        unsigned int gt_pclk_gpio13 : 1;
        unsigned int gt_pclk_gpio14 : 1;
        unsigned int gt_pclk_gpio15 : 1;
        unsigned int gt_pclk_gpio16 : 1;
        unsigned int gt_pclk_gpio17 : 1;
        unsigned int gt_pclk_gpio18 : 1;
        unsigned int gt_pclk_gpio19 : 1;
        unsigned int gt_pclk_gpio20 : 1;
        unsigned int gt_pclk_gpio21 : 1;
        unsigned int gt_pclk_timer9 : 1;
        unsigned int gt_pclk_timer10 : 1;
        unsigned int gt_pclk_timer11 : 1;
        unsigned int gt_pclk_timer12 : 1;
        unsigned int gt_clk_socp : 1;
        unsigned int gt_clk_djtag : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_START (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_END (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_START (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_END (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_START (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_END (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_START (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_END (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_START (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_END (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_START (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_END (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_START (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_END (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_START (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_END (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_START (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_END (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_START (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_END (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_START (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_END (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_START (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_END (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_START (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_END (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_START (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_END (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_START (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_END (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_START (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_END (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_START (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_END (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_START (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_END (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_START (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_END (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_START (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_END (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_START (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_END (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_START (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_END (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_START (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_END (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_START (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_END (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_START (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_END (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_START (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_END (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_START (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_END (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_START (27)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ipc0 : 1;
        unsigned int gt_clk_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_spi1 : 1;
        unsigned int gt_clk_uart0 : 1;
        unsigned int gt_clk_uart1 : 1;
        unsigned int gt_clk_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_uart4 : 1;
        unsigned int gt_clk_uart5 : 1;
        unsigned int gt_pclk_wd0 : 1;
        unsigned int gt_pclk_wd1 : 1;
        unsigned int gt_pclk_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int gt_pclk_ipc_mdm : 1;
        unsigned int gt_clk_adb_mst_a53 : 1;
        unsigned int gt_clk_adb_mst_a57 : 1;
        unsigned int gt_clk_gic : 1;
        unsigned int gt_clk_hkadcssi : 1;
        unsigned int gt_pclk_ioc : 1;
        unsigned int gt_clk_codecssi : 1;
        unsigned int gt_clk_i2c4 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int gt_pclk_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PEREN2_UNION;
#endif
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_START (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_END (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_START (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_END (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_START (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_END (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_START (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_END (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_START (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_END (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_START (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_END (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_START (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_END (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_START (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_END (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_START (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_END (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_START (15)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_END (15)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_START (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_END (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_START (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_END (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_START (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_END (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_START (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_END (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_START (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_END (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_START (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_END (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_START (24)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_END (24)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_START (25)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_END (25)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_START (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_END (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_START (27)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_END (27)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_START (31)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ipc0 : 1;
        unsigned int gt_clk_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_spi1 : 1;
        unsigned int gt_clk_uart0 : 1;
        unsigned int gt_clk_uart1 : 1;
        unsigned int gt_clk_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_uart4 : 1;
        unsigned int gt_clk_uart5 : 1;
        unsigned int gt_pclk_wd0 : 1;
        unsigned int gt_pclk_wd1 : 1;
        unsigned int gt_pclk_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int gt_pclk_ipc_mdm : 1;
        unsigned int gt_clk_adb_mst_a53 : 1;
        unsigned int gt_clk_adb_mst_a57 : 1;
        unsigned int gt_clk_gic : 1;
        unsigned int gt_clk_hkadcssi : 1;
        unsigned int gt_pclk_ioc : 1;
        unsigned int gt_clk_codecssi : 1;
        unsigned int gt_clk_i2c4 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int gt_pclk_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_START (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_END (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_START (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_END (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_START (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_END (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_START (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_END (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_START (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_END (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_START (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_END (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_START (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_END (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_START (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_END (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_START (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_END (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_START (15)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_END (15)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_START (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_END (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_START (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_END (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_START (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_END (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_START (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_END (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_START (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_END (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_START (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_END (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_START (25)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_END (25)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_START (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_END (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_START (27)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_END (27)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_START (31)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ipc0 : 1;
        unsigned int gt_clk_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_spi1 : 1;
        unsigned int gt_clk_uart0 : 1;
        unsigned int gt_clk_uart1 : 1;
        unsigned int gt_clk_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_uart4 : 1;
        unsigned int gt_clk_uart5 : 1;
        unsigned int gt_pclk_wd0 : 1;
        unsigned int gt_pclk_wd1 : 1;
        unsigned int gt_pclk_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int gt_pclk_ipc_mdm : 1;
        unsigned int gt_clk_adb_mst_a53 : 1;
        unsigned int gt_clk_adb_mst_a57 : 1;
        unsigned int gt_clk_gic : 1;
        unsigned int gt_clk_hkadcssi : 1;
        unsigned int gt_pclk_ioc : 1;
        unsigned int gt_clk_codecssi : 1;
        unsigned int gt_clk_i2c4 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int gt_pclk_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_START (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_END (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_START (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_END (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_START (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_END (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_START (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_END (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_START (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_END (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_START (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_END (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_START (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_END (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_START (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_END (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_START (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_END (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_START (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_END (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_START (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_END (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_START (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_END (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_START (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_END (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_START (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_END (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_START (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_END (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_START (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_END (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_START (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_END (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_START (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_END (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_START (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_END (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_START (31)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ipc0 : 1;
        unsigned int gt_clk_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_spi1 : 1;
        unsigned int gt_clk_uart0 : 1;
        unsigned int gt_clk_uart1 : 1;
        unsigned int gt_clk_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_uart4 : 1;
        unsigned int gt_clk_uart5 : 1;
        unsigned int gt_pclk_wd0 : 1;
        unsigned int gt_pclk_wd1 : 1;
        unsigned int gt_pclk_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int gt_pclk_ipc_mdm : 1;
        unsigned int gt_clk_adb_mst_a53 : 1;
        unsigned int gt_clk_adb_mst_a57 : 1;
        unsigned int gt_clk_gic : 1;
        unsigned int gt_clk_hkadcssi : 1;
        unsigned int gt_pclk_ioc : 1;
        unsigned int gt_clk_codecssi : 1;
        unsigned int gt_clk_i2c4 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int gt_pclk_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_START (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_END (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_START (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_END (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_START (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_END (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_START (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_END (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_START (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_END (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_START (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_END (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_START (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_END (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_START (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_END (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_START (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_END (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_START (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_END (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_START (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_END (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_START (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_END (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_START (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_END (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_START (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_END (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_START (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_END (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_START (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_END (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_START (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_END (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_START (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_END (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_START (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_END (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_START (31)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_dmac_lpm3 : 1;
        unsigned int gt_clk_dmac_acpu : 1;
        unsigned int gt_clk_dmac_mcpu : 1;
        unsigned int gt_pclk_g3d : 1;
        unsigned int gt_clk_g3dmt : 1;
        unsigned int gt_clk_g3d : 1;
        unsigned int sc_abb_pll_gps_en : 2;
        unsigned int sc_abb_pll_audio_en : 2;
        unsigned int gt_clk_venc : 1;
        unsigned int gt_clk_vdec : 1;
        unsigned int gt_pclk_dss : 1;
        unsigned int gt_aclk_dss : 1;
        unsigned int gt_clk_ldi1 : 1;
        unsigned int gt_clk_ldi0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_edc0 : 1;
        unsigned int sc_abb_pll_gps_gt_en : 1;
        unsigned int sc_abb_pll_audio_gt_en : 1;
        unsigned int gt_clk_rxdphy0_cfg : 1;
        unsigned int gt_clk_rxdphy1_cfg : 1;
        unsigned int gt_clk_rxdphy2_cfg : 1;
        unsigned int gt_aclk_isp : 1;
        unsigned int gt_hclk_isp : 1;
        unsigned int gt_clk_ispfunc : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_ispa7cfg : 1;
        unsigned int gt_clk_txdphy0_cfg : 1;
        unsigned int gt_clk_txdphy0_ref : 1;
        unsigned int gt_clk_txdphy1_cfg : 1;
        unsigned int gt_clk_txdphy1_ref : 1;
    } reg;
} SOC_CRGPERIPH_PEREN3_UNION;
#endif
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_START (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_END (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_START (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_END (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_START (2)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_END (2)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_START (3)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_END (3)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_START (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_END (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_START (5)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_END (5)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_START (6)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_END (7)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_START (8)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_END (9)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_START (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_END (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_START (11)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_END (11)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_START (12)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_END (12)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_START (13)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_END (13)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_START (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_END (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_START (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_END (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_START (17)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_END (17)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_START (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_END (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_START (19)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_END (19)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_START (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_END (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_START (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_END (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_START (22)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_END (22)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_START (23)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_END (23)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_START (24)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_END (24)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_START (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_END (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_START (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_END (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_START (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_END (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_START (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_END (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_START (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_END (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_START (31)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_dmac_lpm3 : 1;
        unsigned int gt_clk_dmac_acpu : 1;
        unsigned int gt_clk_dmac_mcpu : 1;
        unsigned int gt_pclk_g3d : 1;
        unsigned int gt_clk_g3dmt : 1;
        unsigned int gt_clk_g3d : 1;
        unsigned int sc_abb_pll_gps_en : 2;
        unsigned int sc_abb_pll_audio_en : 2;
        unsigned int gt_clk_venc : 1;
        unsigned int gt_clk_vdec : 1;
        unsigned int gt_pclk_dss : 1;
        unsigned int gt_aclk_dss : 1;
        unsigned int gt_clk_ldi1 : 1;
        unsigned int gt_clk_ldi0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_edc0 : 1;
        unsigned int sc_abb_pll_gps_gt_en : 1;
        unsigned int sc_abb_pll_audio_gt_en : 1;
        unsigned int gt_clk_rxdphy0_cfg : 1;
        unsigned int gt_clk_rxdphy1_cfg : 1;
        unsigned int gt_clk_rxdphy2_cfg : 1;
        unsigned int gt_aclk_isp : 1;
        unsigned int gt_hclk_isp : 1;
        unsigned int gt_clk_ispfunc : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_ispa7cfg : 1;
        unsigned int gt_clk_txdphy0_cfg : 1;
        unsigned int gt_clk_txdphy0_ref : 1;
        unsigned int gt_clk_txdphy1_cfg : 1;
        unsigned int gt_clk_txdphy1_ref : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_START (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_END (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_START (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_END (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_START (2)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_END (2)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_START (3)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_END (3)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_START (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_END (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_START (5)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_END (5)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_START (6)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_END (7)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_START (8)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_END (9)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_START (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_END (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_START (11)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_END (11)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_START (12)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_END (12)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_START (13)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_END (13)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_START (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_END (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_START (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_END (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_START (17)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_END (17)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_START (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_END (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_START (19)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_END (19)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_START (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_END (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_START (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_END (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_START (22)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_END (22)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_START (23)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_END (23)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_START (24)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_END (24)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_START (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_END (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_START (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_END (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_START (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_END (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_START (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_END (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_START (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_END (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_START (31)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_dmac_lpm3 : 1;
        unsigned int gt_clk_dmac_acpu : 1;
        unsigned int gt_clk_dmac_mcpu : 1;
        unsigned int gt_pclk_g3d : 1;
        unsigned int gt_clk_g3dmt : 1;
        unsigned int gt_clk_g3d : 1;
        unsigned int sc_abb_pll_gps_en : 2;
        unsigned int sc_abb_pll_audio_en : 2;
        unsigned int gt_clk_venc : 1;
        unsigned int gt_clk_vdec : 1;
        unsigned int gt_pclk_dss : 1;
        unsigned int gt_aclk_dss : 1;
        unsigned int gt_clk_ldi1 : 1;
        unsigned int gt_clk_ldi0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_edc0 : 1;
        unsigned int sc_abb_pll_gps_gt_en : 1;
        unsigned int sc_abb_pll_audio_gt_en : 1;
        unsigned int gt_clk_rxdphy0_cfg : 1;
        unsigned int gt_clk_rxdphy1_cfg : 1;
        unsigned int gt_clk_rxdphy2_cfg : 1;
        unsigned int gt_aclk_isp : 1;
        unsigned int gt_hclk_isp : 1;
        unsigned int gt_clk_ispfunc : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_ispa7cfg : 1;
        unsigned int gt_clk_txdphy0_cfg : 1;
        unsigned int gt_clk_txdphy0_ref : 1;
        unsigned int gt_clk_txdphy1_cfg : 1;
        unsigned int gt_clk_txdphy1_ref : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_START (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_END (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_START (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_END (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_START (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_END (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_START (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_END (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_START (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_END (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_START (5)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_END (5)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_START (6)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_END (7)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_START (8)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_END (9)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_START (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_END (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_START (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_END (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_START (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_END (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_START (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_END (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_START (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_END (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_START (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_END (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_START (17)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_END (17)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_START (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_END (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_START (19)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_END (19)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_START (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_END (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_START (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_END (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_START (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_END (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_START (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_END (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_START (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_END (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_START (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_END (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_START (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_END (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_START (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_END (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_START (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_END (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_START (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_END (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_START (31)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_dmac0 : 1;
        unsigned int gt_clk_dmac1 : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_pclk_g3d : 1;
        unsigned int gt_clk_g3dmt : 1;
        unsigned int gt_clk_g3d : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_venc : 1;
        unsigned int gt_clk_vdec : 1;
        unsigned int gt_pclk_dss : 1;
        unsigned int gt_aclk_dss : 1;
        unsigned int gt_clk_ldi1 : 1;
        unsigned int gt_clk_ldi0 : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_edc0 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int gt_clk_rxdphy0_cfg : 1;
        unsigned int gt_clk_rxdphy1_cfg : 1;
        unsigned int gt_clk_rxdphy2_cfg : 1;
        unsigned int gt_aclk_isp : 1;
        unsigned int gt_hclk_isp : 1;
        unsigned int gt_clk_ispfunc : 1;
        unsigned int reserved_8 : 1;
        unsigned int gt_clk_ispa7cfg : 1;
        unsigned int gt_clk_txdphy0_cfg : 1;
        unsigned int gt_clk_txdphy0_ref : 1;
        unsigned int gt_clk_txdphy1_cfg : 1;
        unsigned int gt_clk_txdphy1_ref : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_START (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_END (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_START (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_END (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_START (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_END (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_START (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_END (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_START (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_END (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_START (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_END (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_START (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_END (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_START (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_END (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_START (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_END (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_START (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_END (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_START (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_END (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_START (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_END (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_START (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_END (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_START (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_END (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_START (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_END (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_START (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_END (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_START (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_END (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_START (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_END (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_START (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_END (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_START (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_END (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_START (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_END (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_START (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_END (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_START (31)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_usb3otg_ref : 1;
        unsigned int gt_aclk_usb3otg : 1;
        unsigned int gt_clk_usb3phy_ref : 1;
        unsigned int gt_clk_ivp32dsp_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ivp32dsp_sysbus : 1;
        unsigned int gt_clk_usb3phy_ref_pll : 1;
        unsigned int gt_clk_ivp32dsp_tcxo : 1;
        unsigned int gt_clk_perf_stat : 1;
        unsigned int gt_pclk_perf_stat : 1;
        unsigned int gt_aclk_perf_stat : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_secp : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_emmc1_3p2m : 1;
        unsigned int gt_clk_emmc0 : 1;
        unsigned int gt_clk_emmc1 : 1;
        unsigned int gt_clk_sd : 1;
        unsigned int gt_clk_sdio0 : 1;
        unsigned int gt_clk_sdio1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_a57_tsensor : 1;
        unsigned int gt_clk_a53_tsensor : 1;
        unsigned int gt_clk_apll0_sscg : 1;
        unsigned int gt_clk_apll1_sscg : 1;
        unsigned int gt_clk_apll2_sscg : 1;
        unsigned int gt_clk_ppll1_sscg : 1;
        unsigned int gt_clk_ppll2_sscg : 1;
        unsigned int gt_clk_ppll3_sscg : 1;
        unsigned int gt_clk_ppll4_sscg : 1;
        unsigned int gt_clk_ppll5_sscg : 1;
        unsigned int gt_clk_a53_tp : 1;
    } reg;
} SOC_CRGPERIPH_PEREN4_UNION;
#endif
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_START (0)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_END (0)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_START (1)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_END (1)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_START (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_END (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_START (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_END (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_START (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_END (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_START (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_END (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_START (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_END (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_START (8)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_END (8)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_START (9)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_END (9)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_START (10)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_END (10)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_START (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_END (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_START (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_END (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_START (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_END (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_START (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_END (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_START (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_END (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_START (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_END (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_START (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_END (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_START (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_END (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_START (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_END (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_START (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_END (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_START (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_END (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_START (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_END (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_START (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_END (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_START (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_END (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_START (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_END (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_START (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_END (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_START (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_END (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_START (31)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_usb3otg_ref : 1;
        unsigned int gt_aclk_usb3otg : 1;
        unsigned int gt_clk_usb3phy_ref : 1;
        unsigned int gt_clk_ivp32dsp_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ivp32dsp_sysbus : 1;
        unsigned int gt_clk_usb3phy_ref_pll : 1;
        unsigned int gt_clk_ivp32dsp_tcxo : 1;
        unsigned int gt_clk_perf_stat : 1;
        unsigned int gt_pclk_perf_stat : 1;
        unsigned int gt_aclk_perf_stat : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_secp : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_emmc1_3p2m : 1;
        unsigned int gt_clk_emmc0 : 1;
        unsigned int gt_clk_emmc1 : 1;
        unsigned int gt_clk_sd : 1;
        unsigned int gt_clk_sdio0 : 1;
        unsigned int gt_clk_sdio1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_a57_tsensor : 1;
        unsigned int gt_clk_a53_tsensor : 1;
        unsigned int gt_clk_apll0_sscg : 1;
        unsigned int gt_clk_apll1_sscg : 1;
        unsigned int gt_clk_apll2_sscg : 1;
        unsigned int gt_clk_ppll1_sscg : 1;
        unsigned int gt_clk_ppll2_sscg : 1;
        unsigned int gt_clk_ppll3_sscg : 1;
        unsigned int gt_clk_ppll4_sscg : 1;
        unsigned int gt_clk_ppll5_sscg : 1;
        unsigned int gt_clk_a53_tp : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_START (0)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_END (0)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_START (1)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_END (1)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_START (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_END (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_START (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_END (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_START (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_END (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_START (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_END (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_START (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_END (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_START (8)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_END (8)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_START (9)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_END (9)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_START (10)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_END (10)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_START (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_END (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_START (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_END (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_START (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_END (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_START (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_END (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_START (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_END (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_START (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_END (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_START (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_END (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_START (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_END (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_START (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_END (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_START (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_END (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_START (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_END (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_START (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_END (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_START (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_END (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_START (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_END (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_START (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_END (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_START (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_END (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_START (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_END (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_START (31)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_usb3otg_ref : 1;
        unsigned int gt_aclk_usb3otg : 1;
        unsigned int gt_clk_usb3phy_ref : 1;
        unsigned int gt_clk_ivp32dsp_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ivp32dsp_sysbus : 1;
        unsigned int gt_clk_usb3phy_ref_pll : 1;
        unsigned int gt_clk_ivp32dsp_tcxo : 1;
        unsigned int gt_clk_perf_stat : 1;
        unsigned int gt_pclk_perf_stat : 1;
        unsigned int gt_aclk_perf_stat : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_secp : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_emmc1_3p2m : 1;
        unsigned int gt_clk_emmc0 : 1;
        unsigned int gt_clk_emmc1 : 1;
        unsigned int gt_clk_sd : 1;
        unsigned int gt_clk_sdio0 : 1;
        unsigned int gt_clk_sdio1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_a57_tsensor : 1;
        unsigned int gt_clk_a53_tsensor : 1;
        unsigned int gt_clk_apll0_sscg : 1;
        unsigned int gt_clk_apll1_sscg : 1;
        unsigned int gt_clk_apll2_sscg : 1;
        unsigned int gt_clk_ppll1_sscg : 1;
        unsigned int gt_clk_ppll2_sscg : 1;
        unsigned int gt_clk_ppll3_sscg : 1;
        unsigned int gt_clk_ppll4_sscg : 1;
        unsigned int gt_clk_ppll5_sscg : 1;
        unsigned int gt_clk_a53_tp : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_START (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_END (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_START (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_END (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_START (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_END (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_START (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_END (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_START (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_END (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_START (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_END (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_START (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_END (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_START (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_END (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_START (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_END (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_START (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_END (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_START (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_END (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_START (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_END (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_START (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_END (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_START (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_END (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_START (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_END (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_START (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_END (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_START (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_END (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_START (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_END (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_START (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_END (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_START (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_END (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_START (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_END (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_START (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_END (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_START (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_END (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_START (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_END (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_START (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_END (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_START (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_END (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_START (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_END (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_START (31)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_usb3otg_ref : 1;
        unsigned int gt_aclk_usb3otg : 1;
        unsigned int gt_clk_usb3phy_ref : 1;
        unsigned int gt_clk_ivp32dsp_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ivp32dsp_sysbus : 1;
        unsigned int gt_clk_usb3phy_ref_pll : 1;
        unsigned int gt_clk_ivp32dsp_tcxo : 1;
        unsigned int gt_clk_perf_stat : 1;
        unsigned int gt_pclk_perf_stat : 1;
        unsigned int gt_aclk_perf_stat : 1;
        unsigned int gt_clk_secs : 1;
        unsigned int gt_clk_secp : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_emmc1_3p2m : 1;
        unsigned int gt_clk_emmc0 : 1;
        unsigned int gt_clk_emmc1 : 1;
        unsigned int gt_clk_sd : 1;
        unsigned int gt_clk_sdio0 : 1;
        unsigned int gt_clk_sdio1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_a57_tsensor : 1;
        unsigned int gt_clk_a53_tsensor : 1;
        unsigned int gt_clk_apll0_sscg : 1;
        unsigned int gt_clk_apll1_sscg : 1;
        unsigned int gt_clk_apll2_sscg : 1;
        unsigned int gt_clk_ppll1_sscg : 1;
        unsigned int gt_clk_ppll2_sscg : 1;
        unsigned int gt_clk_ppll3_sscg : 1;
        unsigned int gt_clk_ppll4_sscg : 1;
        unsigned int gt_clk_ppll5_sscg : 1;
        unsigned int gt_clk_a53_tp : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_START (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_END (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_START (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_END (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_START (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_END (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_START (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_END (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_START (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_END (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_START (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_END (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_START (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_END (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_START (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_END (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_START (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_END (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_START (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_END (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_START (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_END (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_START (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_END (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_START (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_END (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_START (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_END (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_START (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_END (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_START (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_END (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_START (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_END (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_START (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_END (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_START (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_END (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_START (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_END (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_START (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_END (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_START (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_END (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_START (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_END (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_START (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_END (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_START (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_END (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_START (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_END (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_START (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_END (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_START (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_END (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_START (31)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_sysbus2hkmem : 1;
        unsigned int gt_clk_modem_sys : 1;
        unsigned int gt_clk_modem_subsys : 1;
        unsigned int gt_clk_noc_timeout_extref : 1;
        unsigned int gt_clk_ispa7 : 1;
        unsigned int gt_clk_g3d_tsensor : 1;
        unsigned int gt_clk_modem_tsensor : 1;
        unsigned int gt_clk_slimbus : 1;
        unsigned int gt_clk_lpmcu : 1;
        unsigned int gt_clk_a57_hpm : 1;
        unsigned int gt_clk_cci2sysbus_asyn : 1;
        unsigned int gt_clk_ao_hpm : 1;
        unsigned int gt_clk_peri_hpm : 1;
        unsigned int gt_clk_a53_hpm : 1;
        unsigned int gt_clk_cci400 : 1;
        unsigned int gt_clk_gpu_hpm : 1;
        unsigned int gt_clk_isp_snclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_modem_mcpu_tp : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_c : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_d : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_b : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_a : 1;
        unsigned int gt_pclk_dsi0 : 1;
        unsigned int gt_pclk_dsi1 : 1;
        unsigned int gt_clk_lpmcu_tp : 1;
        unsigned int gt_clk_sysbus_tp : 1;
    } reg;
} SOC_CRGPERIPH_PEREN5_UNION;
#endif
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_START (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_END (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_START (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_END (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_START (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_END (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_START (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_END (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_START (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_END (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_START (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_END (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_START (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_END (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_START (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_END (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_START (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_END (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_START (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_END (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_START (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_END (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_START (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_END (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_START (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_END (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_START (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_END (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_START (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_END (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_START (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_END (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_START (16)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_END (18)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_START (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_END (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_START (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_END (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_START (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_END (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_START (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_END (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_START (27)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_END (27)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_START (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_END (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_START (29)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_END (29)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_START (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_END (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_START (31)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_sysbus2hkmem : 1;
        unsigned int gt_clk_modem_sys : 1;
        unsigned int gt_clk_modem_subsys : 1;
        unsigned int gt_clk_noc_timeout_extref : 1;
        unsigned int gt_clk_ispa7 : 1;
        unsigned int gt_clk_g3d_tsensor : 1;
        unsigned int gt_clk_modem_tsensor : 1;
        unsigned int gt_clk_slimbus : 1;
        unsigned int gt_clk_lpmcu : 1;
        unsigned int gt_clk_a57_hpm : 1;
        unsigned int gt_clk_cci2sysbus_asyn : 1;
        unsigned int gt_clk_ao_hpm : 1;
        unsigned int gt_clk_peri_hpm : 1;
        unsigned int gt_clk_a53_hpm : 1;
        unsigned int gt_clk_cci400 : 1;
        unsigned int gt_clk_gpu_hpm : 1;
        unsigned int gt_clk_isp_snclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_modem_mcpu_tp : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_c : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_d : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_b : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_a : 1;
        unsigned int gt_pclk_dsi0 : 1;
        unsigned int gt_pclk_dsi1 : 1;
        unsigned int gt_clk_lpmcu_tp : 1;
        unsigned int gt_clk_sysbus_tp : 1;
    } reg;
} SOC_CRGPERIPH_PERDIS5_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_START (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_END (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_START (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_END (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_START (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_END (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_START (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_END (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_START (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_END (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_START (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_END (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_START (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_END (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_START (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_END (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_START (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_END (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_START (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_END (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_START (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_END (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_START (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_END (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_START (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_END (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_START (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_END (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_START (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_END (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_START (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_END (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_START (16)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_END (18)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_START (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_END (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_START (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_END (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_START (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_END (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_START (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_END (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_START (27)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_END (27)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_START (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_END (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_START (29)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_END (29)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_START (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_END (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_START (31)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_sysbus2hkmem : 1;
        unsigned int gt_clk_modem_sys : 1;
        unsigned int gt_clk_modem_subsys : 1;
        unsigned int gt_clk_noc_timeout_extref : 1;
        unsigned int gt_clk_ispa7 : 1;
        unsigned int gt_clk_g3d_tsensor : 1;
        unsigned int gt_clk_modem_tsensor : 1;
        unsigned int gt_clk_slimbus : 1;
        unsigned int gt_clk_lpmcu : 1;
        unsigned int gt_clk_a57_hpm : 1;
        unsigned int gt_clk_cci2sysbus_asyn : 1;
        unsigned int gt_clk_ao_hpm : 1;
        unsigned int gt_clk_peri_hpm : 1;
        unsigned int gt_clk_a53_hpm : 1;
        unsigned int gt_clk_cci400 : 1;
        unsigned int gt_clk_gpu_hpm : 1;
        unsigned int gt_clk_isp_snclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int gt_clk_modem_mcpu_tp : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_c : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_d : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_b : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_a : 1;
        unsigned int gt_pclk_dsi0 : 1;
        unsigned int gt_pclk_dsi1 : 1;
        unsigned int gt_clk_lpmcu_tp : 1;
        unsigned int gt_clk_sysbus_tp : 1;
    } reg;
} SOC_CRGPERIPH_PERCLKEN5_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_START (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_END (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_START (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_END (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_START (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_END (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_START (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_END (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_START (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_END (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_START (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_END (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_START (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_END (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_START (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_END (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_START (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_END (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_START (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_END (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_START (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_END (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_START (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_END (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_START (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_END (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_START (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_END (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_START (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_END (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_START (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_END (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_START (16)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_END (18)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_START (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_END (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_START (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_END (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_START (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_END (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_START (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_END (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_START (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_END (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_START (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_END (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_START (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_END (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_START (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_END (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_START (31)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_sysbus2hkmem : 1;
        unsigned int gt_clk_modem_sys : 1;
        unsigned int gt_clk_modem_subsys : 1;
        unsigned int gt_clk_noc_timeout_extref : 1;
        unsigned int gt_clk_ispa7 : 1;
        unsigned int gt_clk_g3d_tsensor : 1;
        unsigned int gt_clk_modem_tsensor : 1;
        unsigned int gt_clk_slimbus : 1;
        unsigned int gt_clk_lpmcu : 1;
        unsigned int gt_clk_a57_hpm : 1;
        unsigned int gt_clk_cci2sysbus_asyn : 1;
        unsigned int gt_clk_ao_hpm : 1;
        unsigned int gt_clk_peri_hpm : 1;
        unsigned int gt_clk_a53_hpm : 1;
        unsigned int gt_clk_cci400 : 1;
        unsigned int gt_clk_gpu_hpm : 1;
        unsigned int gt_clk_isp_snclk : 3;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_c : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_d : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_b : 1;
        unsigned int gt_clk_ddrphy_apb_dfi_a : 1;
        unsigned int gt_pclk_dsi0 : 1;
        unsigned int gt_pclk_dsi1 : 1;
        unsigned int gt_clk_ace0_mst_g3d : 1;
        unsigned int gt_clk_ace1_mst_g3d : 1;
    } reg;
} SOC_CRGPERIPH_PERSTAT5_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_START (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_END (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_START (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_END (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_START (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_END (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_START (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_END (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_START (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_END (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_START (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_END (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_START (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_END (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_START (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_END (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_START (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_END (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_START (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_END (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_START (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_END (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_START (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_END (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_START (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_END (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_START (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_END (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_START (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_END (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_START (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_END (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_START (16)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_END (18)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_START (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_END (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_START (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_END (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_START (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_END (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_START (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_END (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_START (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_END (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_START (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_END (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_START (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_END (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_START (31)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ddrc : 1;
        unsigned int ip_rst_sysbus2ddrc : 1;
        unsigned int ip_rst_ddr_exmbist : 1;
        unsigned int ip_rst_vcodeccfg : 1;
        unsigned int ip_rst_vcodecbus : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_vivobus : 1;
        unsigned int ip_rst_sysbus : 1;
        unsigned int ip_rst_cfgbus : 1;
        unsigned int ip_rst_timerperi : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_mmc1pericfg : 1;
        unsigned int ip_rst_mmc0pericfg : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int ip_rst_perf_stat : 1;
        unsigned int ip_rst_dbgsechsicbus : 1;
        unsigned int ip_rst_lpm32cfgbus : 1;
        unsigned int ip_rst_noc_dmabus : 1;
        unsigned int ip_rst_memrep : 1;
        unsigned int ip_rst_vdm_gpu : 1;
        unsigned int ip_rst_vdm_acg2 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_mbus2bus : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 2;
    } reg;
} SOC_CRGPERIPH_PERRSTEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_START (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_END (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_START (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_END (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_START (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_END (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_START (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_END (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_START (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_END (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_START (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_END (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_START (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_END (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_START (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_END (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_START (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_END (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_START (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_END (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_START (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_END (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_START (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_END (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_START (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_END (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_START (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_END (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_START (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_END (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_START (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_END (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_START (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_END (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_START (28)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ddrc : 1;
        unsigned int ip_rst_sysbus2ddrc : 1;
        unsigned int ip_rst_ddr_exmbist : 1;
        unsigned int ip_rst_vcodeccfg : 1;
        unsigned int ip_rst_vcodecbus : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_vivobus : 1;
        unsigned int ip_rst_sysbus : 1;
        unsigned int ip_rst_cfgbus : 1;
        unsigned int ip_rst_timerperi : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_mmc1pericfg : 1;
        unsigned int ip_rst_mmc0pericfg : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int ip_rst_perf_stat : 1;
        unsigned int ip_rst_dbgsechsicbus : 1;
        unsigned int ip_rst_lpm32cfgbus : 1;
        unsigned int ip_rst_noc_dmabus : 1;
        unsigned int ip_rst_memrep : 1;
        unsigned int ip_rst_vdm_gpu : 1;
        unsigned int ip_rst_vdm_acg2 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_mbus2bus : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 2;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_START (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_END (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_START (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_END (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_START (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_END (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_START (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_END (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_START (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_END (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_START (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_END (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_START (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_END (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_START (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_END (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_START (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_END (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_START (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_END (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_START (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_END (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_START (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_END (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_START (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_END (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_START (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_END (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_START (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_END (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_START (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_END (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_START (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_END (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_START (28)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ddrc : 1;
        unsigned int ip_rst_sysbus2ddrc : 1;
        unsigned int ip_rst_ddr_exmbist : 1;
        unsigned int ip_rst_vcodeccfg : 1;
        unsigned int ip_rst_vcodecbus : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_vivobus : 1;
        unsigned int ip_rst_sysbus : 1;
        unsigned int ip_rst_cfgbus : 1;
        unsigned int ip_rst_timerperi : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_mmc1pericfg : 1;
        unsigned int ip_rst_mmc0pericfg : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int ip_rst_perf_stat : 1;
        unsigned int ip_rst_dbgsechsicbus : 1;
        unsigned int ip_rst_lpm32cfgbus : 1;
        unsigned int ip_rst_noc_dmabus : 1;
        unsigned int ip_rst_memrep : 1;
        unsigned int ip_rst_vdm_gpu : 1;
        unsigned int ip_rst_vdm_acg2 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_mbus2bus : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 2;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_START (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_END (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_START (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_END (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_START (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_END (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_START (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_END (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_START (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_END (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_START (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_END (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_START (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_END (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_START (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_END (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_START (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_END (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_START (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_END (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_START (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_END (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_START (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_END (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_START (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_END (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_START (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_END (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_START (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_END (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_START (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_END (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_START (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_END (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_START (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_END (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_START (28)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_gpio0 : 1;
        unsigned int ip_rst_gpio1 : 1;
        unsigned int ip_rst_gpio2 : 1;
        unsigned int ip_rst_gpio3 : 1;
        unsigned int ip_rst_gpio4 : 1;
        unsigned int ip_rst_gpio5 : 1;
        unsigned int ip_rst_gpio6 : 1;
        unsigned int ip_rst_gpio7 : 1;
        unsigned int ip_rst_gpio8 : 1;
        unsigned int ip_rst_gpio9 : 1;
        unsigned int ip_rst_gpio10 : 1;
        unsigned int ip_rst_gpio11 : 1;
        unsigned int ip_rst_gpio12 : 1;
        unsigned int ip_rst_gpio13 : 1;
        unsigned int ip_rst_gpio14 : 1;
        unsigned int ip_rst_gpio15 : 1;
        unsigned int ip_rst_gpio16 : 1;
        unsigned int ip_rst_gpio17 : 1;
        unsigned int ip_rst_gpio18 : 1;
        unsigned int ip_rst_gpio19 : 1;
        unsigned int ip_rst_gpio20 : 1;
        unsigned int ip_rst_gpio21 : 1;
        unsigned int ip_rst_timer9 : 1;
        unsigned int ip_rst_timer10 : 1;
        unsigned int ip_rst_timer11 : 1;
        unsigned int ip_rst_timer12 : 1;
        unsigned int ip_rst_socp : 1;
        unsigned int ip_rst_djtag : 1;
        unsigned int ip_rst_vdm_maya : 1;
        unsigned int ip_rst_vdm_a53 : 1;
        unsigned int ip_rst_vdm_acg0 : 1;
        unsigned int ip_rst_vdm_acg1 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_START (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_END (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_START (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_END (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_START (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_END (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_START (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_END (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_START (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_END (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_START (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_END (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_START (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_END (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_START (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_END (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_START (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_END (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_START (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_END (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_START (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_END (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_START (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_END (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_START (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_END (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_START (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_END (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_START (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_END (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_START (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_END (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_START (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_END (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_START (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_END (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_START (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_END (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_START (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_END (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_START (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_END (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_START (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_END (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_START (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_END (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_START (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_END (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_START (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_END (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_START (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_END (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_START (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_END (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_START (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_END (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_START (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_END (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_START (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_END (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_START (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_END (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_START (31)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_gpio0 : 1;
        unsigned int ip_rst_gpio1 : 1;
        unsigned int ip_rst_gpio2 : 1;
        unsigned int ip_rst_gpio3 : 1;
        unsigned int ip_rst_gpio4 : 1;
        unsigned int ip_rst_gpio5 : 1;
        unsigned int ip_rst_gpio6 : 1;
        unsigned int ip_rst_gpio7 : 1;
        unsigned int ip_rst_gpio8 : 1;
        unsigned int ip_rst_gpio9 : 1;
        unsigned int ip_rst_gpio10 : 1;
        unsigned int ip_rst_gpio11 : 1;
        unsigned int ip_rst_gpio12 : 1;
        unsigned int ip_rst_gpio13 : 1;
        unsigned int ip_rst_gpio14 : 1;
        unsigned int ip_rst_gpio15 : 1;
        unsigned int ip_rst_gpio16 : 1;
        unsigned int ip_rst_gpio17 : 1;
        unsigned int ip_rst_gpio18 : 1;
        unsigned int ip_rst_gpio19 : 1;
        unsigned int ip_rst_gpio20 : 1;
        unsigned int ip_rst_gpio21 : 1;
        unsigned int ip_rst_timer9 : 1;
        unsigned int ip_rst_timer10 : 1;
        unsigned int ip_rst_timer11 : 1;
        unsigned int ip_rst_timer12 : 1;
        unsigned int ip_rst_socp : 1;
        unsigned int ip_rst_djtag : 1;
        unsigned int ip_rst_vdm_maya : 1;
        unsigned int ip_rst_vdm_a53 : 1;
        unsigned int ip_rst_vdm_acg0 : 1;
        unsigned int ip_rst_vdm_acg1 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_START (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_END (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_START (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_END (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_START (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_END (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_START (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_END (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_START (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_END (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_START (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_END (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_START (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_END (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_START (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_END (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_START (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_END (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_START (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_END (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_START (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_END (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_START (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_END (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_START (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_END (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_START (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_END (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_START (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_END (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_START (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_END (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_START (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_END (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_START (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_END (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_START (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_END (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_START (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_END (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_START (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_END (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_START (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_END (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_START (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_END (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_START (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_END (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_START (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_END (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_START (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_END (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_START (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_END (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_START (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_END (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_START (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_END (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_START (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_END (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_START (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_END (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_START (31)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_gpio0 : 1;
        unsigned int ip_rst_gpio1 : 1;
        unsigned int ip_rst_gpio2 : 1;
        unsigned int ip_rst_gpio3 : 1;
        unsigned int ip_rst_gpio4 : 1;
        unsigned int ip_rst_gpio5 : 1;
        unsigned int ip_rst_gpio6 : 1;
        unsigned int ip_rst_gpio7 : 1;
        unsigned int ip_rst_gpio8 : 1;
        unsigned int ip_rst_gpio9 : 1;
        unsigned int ip_rst_gpio10 : 1;
        unsigned int ip_rst_gpio11 : 1;
        unsigned int ip_rst_gpio12 : 1;
        unsigned int ip_rst_gpio13 : 1;
        unsigned int ip_rst_gpio14 : 1;
        unsigned int ip_rst_gpio15 : 1;
        unsigned int ip_rst_gpio16 : 1;
        unsigned int ip_rst_gpio17 : 1;
        unsigned int ip_rst_gpio18 : 1;
        unsigned int ip_rst_gpio19 : 1;
        unsigned int ip_rst_gpio20 : 1;
        unsigned int ip_rst_gpio21 : 1;
        unsigned int ip_rst_timer9 : 1;
        unsigned int ip_rst_timer10 : 1;
        unsigned int ip_rst_timer11 : 1;
        unsigned int ip_rst_timer12 : 1;
        unsigned int ip_rst_socp : 1;
        unsigned int ip_rst_djtag : 1;
        unsigned int ip_rst_vdm_maya : 1;
        unsigned int ip_rst_vdm_a53 : 1;
        unsigned int ip_rst_vdm_acg0 : 1;
        unsigned int ip_rst_vdm_acg1 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_START (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_END (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_START (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_END (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_START (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_END (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_START (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_END (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_START (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_END (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_START (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_END (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_START (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_END (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_START (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_END (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_START (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_END (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_START (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_END (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_START (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_END (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_START (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_END (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_START (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_END (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_START (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_END (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_START (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_END (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_START (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_END (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_START (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_END (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_START (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_END (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_START (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_END (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_START (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_END (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_START (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_END (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_START (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_END (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_START (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_END (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_START (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_END (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_START (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_END (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_START (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_END (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_START (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_END (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_START (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_END (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_START (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_END (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_START (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_END (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_START (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_END (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_START (31)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_ipc0 : 1;
        unsigned int ip_rst_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int ip_rst_spi1 : 1;
        unsigned int ip_rst_uart0 : 1;
        unsigned int ip_rst_uart1 : 1;
        unsigned int ip_rst_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int ip_rst_uart4 : 1;
        unsigned int ip_rst_uart5 : 1;
        unsigned int ip_rst_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_prst_ipc_mdm : 1;
        unsigned int ip_rst_adb_a53 : 1;
        unsigned int ip_rst_adb_a57 : 1;
        unsigned int ip_rst_gic : 1;
        unsigned int ip_rst_hkadcssi : 1;
        unsigned int ip_rst_ioc : 1;
        unsigned int ip_rst_codecssi : 1;
        unsigned int ip_rst_i2c4 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int ip_rst_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_START (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_END (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_START (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_END (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_START (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_END (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_START (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_END (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_START (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_END (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_START (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_END (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_START (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_END (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_START (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_END (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_START (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_END (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_START (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_END (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_START (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_END (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_START (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_END (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_START (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_END (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_START (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_END (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_START (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_END (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_START (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_END (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_START (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_END (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_START (31)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_ipc0 : 1;
        unsigned int ip_rst_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int ip_rst_spi1 : 1;
        unsigned int ip_rst_uart0 : 1;
        unsigned int ip_rst_uart1 : 1;
        unsigned int ip_rst_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int ip_rst_uart4 : 1;
        unsigned int ip_rst_uart5 : 1;
        unsigned int ip_rst_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_prst_ipc_mdm : 1;
        unsigned int ip_rst_adb_a53 : 1;
        unsigned int ip_rst_adb_a57 : 1;
        unsigned int ip_rst_gic : 1;
        unsigned int ip_rst_hkadcssi : 1;
        unsigned int ip_rst_ioc : 1;
        unsigned int ip_rst_codecssi : 1;
        unsigned int ip_rst_i2c4 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int ip_rst_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_START (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_END (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_START (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_END (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_START (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_END (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_START (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_END (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_START (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_END (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_START (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_END (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_START (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_END (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_START (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_END (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_START (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_END (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_START (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_END (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_START (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_END (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_START (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_END (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_START (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_END (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_START (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_END (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_START (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_END (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_START (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_END (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_START (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_END (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_START (31)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_pwm : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_ipc0 : 1;
        unsigned int ip_rst_ipc1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_i2c3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int ip_rst_spi1 : 1;
        unsigned int ip_rst_uart0 : 1;
        unsigned int ip_rst_uart1 : 1;
        unsigned int ip_rst_uart2 : 1;
        unsigned int reserved_5 : 1;
        unsigned int ip_rst_uart4 : 1;
        unsigned int ip_rst_uart5 : 1;
        unsigned int ip_rst_tzpc : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_prst_ipc_mdm : 1;
        unsigned int ip_rst_adb_a53 : 1;
        unsigned int ip_rst_adb_a57 : 1;
        unsigned int ip_rst_gic : 1;
        unsigned int ip_rst_hkadcssi : 1;
        unsigned int ip_rst_ioc : 1;
        unsigned int ip_rst_codecssi : 1;
        unsigned int ip_rst_i2c4 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int ip_rst_pctrl : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_START (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_END (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_START (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_END (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_START (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_END (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_START (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_END (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_START (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_END (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_START (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_END (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_START (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_END (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_START (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_END (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_START (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_END (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_START (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_END (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_START (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_END (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_START (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_END (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_START (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_END (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_START (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_END (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_START (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_END (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_START (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_END (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_START (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_END (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_START (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_END (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_START (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_END (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_START (31)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dmac : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_prst_g3d : 1;
        unsigned int ip_rst_g3d : 1;
        unsigned int ip_rst_g3dmt : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_venc : 1;
        unsigned int ip_rst_vdec : 1;
        unsigned int ip_rst_dss : 1;
        unsigned int ip_prst_dss : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int ip_rst_g3ds_hpm5 : 1;
        unsigned int ip_rst_g3ds_hpm4 : 1;
        unsigned int ip_rst_g3ds_hpm3 : 1;
        unsigned int ip_rst_g3ds_hpm2 : 1;
        unsigned int ip_rst_g3ds_hpm1 : 1;
        unsigned int ip_rst_g3ds_hpm0 : 1;
        unsigned int ip_rst_g3dg_hpm : 1;
        unsigned int ip_rst_peri_hpm : 1;
        unsigned int ip_rst_ao_hpm : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int ip_rst_dsi0 : 1;
        unsigned int ip_rst_dsi1 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_START (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_END (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_START (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_END (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_START (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_END (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_START (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_END (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_START (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_END (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_START (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_END (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_START (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_END (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_START (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_END (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_START (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_END (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_START (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_END (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_START (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_END (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_START (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_END (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_START (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_END (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_START (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_END (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_START (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_END (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_START (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_END (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_START (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_END (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_START (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_END (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_START (29)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dmac : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_prst_g3d : 1;
        unsigned int ip_rst_g3d : 1;
        unsigned int ip_rst_g3dmt : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_venc : 1;
        unsigned int ip_rst_vdec : 1;
        unsigned int ip_rst_dss : 1;
        unsigned int ip_prst_dss : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int ip_rst_g3ds_hpm5 : 1;
        unsigned int ip_rst_g3ds_hpm4 : 1;
        unsigned int ip_rst_g3ds_hpm3 : 1;
        unsigned int ip_rst_g3ds_hpm2 : 1;
        unsigned int ip_rst_g3ds_hpm1 : 1;
        unsigned int ip_rst_g3ds_hpm0 : 1;
        unsigned int ip_rst_g3dg_hpm : 1;
        unsigned int ip_rst_peri_hpm : 1;
        unsigned int ip_rst_ao_hpm : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int ip_rst_dsi0 : 1;
        unsigned int ip_rst_dsi1 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_START (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_END (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_START (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_END (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_START (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_END (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_START (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_END (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_START (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_END (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_START (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_END (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_START (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_END (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_START (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_END (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_START (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_END (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_START (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_END (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_START (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_END (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_START (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_END (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_START (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_END (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_START (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_END (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_START (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_END (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_START (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_END (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_START (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_END (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_START (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_END (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_START (29)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dmac : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_prst_g3d : 1;
        unsigned int ip_rst_g3d : 1;
        unsigned int ip_rst_g3dmt : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_venc : 1;
        unsigned int ip_rst_vdec : 1;
        unsigned int ip_rst_dss : 1;
        unsigned int ip_prst_dss : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int ip_rst_g3ds_hpm5 : 1;
        unsigned int ip_rst_g3ds_hpm4 : 1;
        unsigned int ip_rst_g3ds_hpm3 : 1;
        unsigned int ip_rst_g3ds_hpm2 : 1;
        unsigned int ip_rst_g3ds_hpm1 : 1;
        unsigned int ip_rst_g3ds_hpm0 : 1;
        unsigned int ip_rst_g3dg_hpm : 1;
        unsigned int ip_rst_peri_hpm : 1;
        unsigned int ip_rst_ao_hpm : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int ip_rst_dsi0 : 1;
        unsigned int ip_rst_dsi1 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_START (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_END (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_START (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_END (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_START (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_END (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_START (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_END (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_START (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_END (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_START (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_END (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_START (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_END (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_START (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_END (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_START (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_END (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_START (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_END (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_START (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_END (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_START (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_END (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_START (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_END (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_START (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_END (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_START (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_END (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_START (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_END (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_START (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_END (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_START (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_END (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_START (29)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dbgsechsic_subsys_crg : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_usb3otgphy_por : 1;
        unsigned int reserved_2 : 1;
        unsigned int ip_rst_usb3otg : 1;
        unsigned int ip_rst_usb3otg_32k : 1;
        unsigned int ip_rst_usb3otg_ahbif : 1;
        unsigned int ip_rst_usb3otg_mux : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_rst_secp : 1;
        unsigned int ip_rst_emmc0 : 1;
        unsigned int ip_rst_emmc1 : 1;
        unsigned int ip_rst_sd : 1;
        unsigned int ip_rst_sdio0 : 1;
        unsigned int ip_rst_sdio1 : 1;
        unsigned int ip_rst_cci400 : 1;
        unsigned int ip_rst_emmc0_m : 1;
        unsigned int ip_rst_emmc1_m : 1;
        unsigned int ip_rst_sd_m : 1;
        unsigned int ip_rst_sdio0_m : 1;
        unsigned int ip_rst_sdio1_m : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_lpmcu : 1;
        unsigned int ip_rst_sysbus2hkmem : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_START (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_END (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_START (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_END (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_START (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_END (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_START (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_END (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_START (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_END (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_START (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_END (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_START (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_END (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_START (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_END (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_START (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_END (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_START (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_END (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_START (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_END (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_START (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_END (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_START (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_END (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_START (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_END (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_START (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_END (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_START (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_END (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_START (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_END (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_START (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_END (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_START (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_END (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_START (29)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dbgsechsic_subsys_crg : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_usb3otgphy_por : 1;
        unsigned int reserved_2 : 1;
        unsigned int ip_rst_usb3otg : 1;
        unsigned int ip_rst_usb3otg_32k : 1;
        unsigned int ip_rst_usb3otg_ahbif : 1;
        unsigned int ip_rst_usb3otg_mux : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_rst_secp : 1;
        unsigned int ip_rst_emmc0 : 1;
        unsigned int ip_rst_emmc1 : 1;
        unsigned int ip_rst_sd : 1;
        unsigned int ip_rst_sdio0 : 1;
        unsigned int ip_rst_sdio1 : 1;
        unsigned int ip_rst_cci400 : 1;
        unsigned int ip_rst_emmc0_m : 1;
        unsigned int ip_rst_emmc1_m : 1;
        unsigned int ip_rst_sd_m : 1;
        unsigned int ip_rst_sdio0_m : 1;
        unsigned int ip_rst_sdio1_m : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_lpmcu : 1;
        unsigned int ip_rst_sysbus2hkmem : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_START (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_END (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_START (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_END (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_START (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_END (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_START (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_END (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_START (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_END (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_START (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_END (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_START (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_END (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_START (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_END (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_START (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_END (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_START (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_END (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_START (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_END (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_START (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_END (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_START (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_END (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_START (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_END (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_START (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_END (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_START (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_END (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_START (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_END (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_START (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_END (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_START (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_END (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_START (29)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_dbgsechsic_subsys_crg : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_usb3otgphy_por : 1;
        unsigned int reserved_2 : 1;
        unsigned int ip_rst_usb3otg : 1;
        unsigned int ip_rst_usb3otg_32k : 1;
        unsigned int ip_rst_usb3otg_ahbif : 1;
        unsigned int ip_rst_usb3otg_mux : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int ip_rst_secp : 1;
        unsigned int ip_rst_emmc0 : 1;
        unsigned int ip_rst_emmc1 : 1;
        unsigned int ip_rst_sd : 1;
        unsigned int ip_rst_sdio0 : 1;
        unsigned int ip_rst_sdio1 : 1;
        unsigned int ip_rst_cci400 : 1;
        unsigned int ip_rst_emmc0_m : 1;
        unsigned int ip_rst_emmc1_m : 1;
        unsigned int ip_rst_sd_m : 1;
        unsigned int ip_rst_sdio0_m : 1;
        unsigned int ip_rst_sdio1_m : 1;
        unsigned int reserved_9 : 1;
        unsigned int ip_rst_lpmcu : 1;
        unsigned int ip_rst_sysbus2hkmem : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_START (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_END (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_START (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_END (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_START (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_END (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_START (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_END (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_START (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_END (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_START (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_END (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_START (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_END (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_START (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_END (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_START (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_END (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_START (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_END (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_START (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_END (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_START (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_END (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_START (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_END (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_START (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_END (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_START (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_END (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_START (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_END (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_START (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_END (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_START (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_END (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_START (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_END (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_START (29)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PERRSTEN5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PERRSTDIS5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_sysbus : 5;
        unsigned int sc_div_lpmcu : 5;
        unsigned int sc_div_ivp32dsp_core : 4;
        unsigned int sel_ivp32dsp_core : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV0_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_START (0)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_END (4)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_START (5)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_END (9)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_START (10)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_END (13)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_START (14)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_END (15)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_sysbus : 1;
        unsigned int sel_lpmcu : 1;
        unsigned int sel_uartl : 1;
        unsigned int sel_uarth : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int sel_spi : 1;
        unsigned int lpmcu_clk_sw_req_cfg : 2;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int sel_i2c : 1;
        unsigned int sysbus_clk_sw_req_cfg : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV1_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_START (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_END (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_START (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_END (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_START (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_END (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_START (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_END (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_START (8)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_END (8)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_START (9)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_END (10)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_START (13)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_END (13)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_START (14)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_END (15)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 7;
        unsigned int sc_div_uarth : 4;
        unsigned int sc_div_uartl : 4;
        unsigned int reserved_1 : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV2_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_START (7)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_END (10)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_START (11)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_END (14)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_sel_emmc : 3;
        unsigned int sc_div_emmc : 4;
        unsigned int reserved : 7;
        unsigned int sc_div_ldi0 : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV3_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_START (0)
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_END (2)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_START (3)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_END (6)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_START (14)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_END (15)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_sd : 4;
        unsigned int sc_sel_sd : 3;
        unsigned int sc_div_sdio0 : 4;
        unsigned int sc_sel_sdio0 : 3;
        unsigned int sc_div_ldi1 : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV4_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_START (0)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_END (3)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_START (4)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_END (6)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_START (7)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_END (10)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_START (11)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_END (13)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_START (14)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_END (15)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_edc0 : 6;
        unsigned int sel_edc0_pll : 2;
        unsigned int sc_div_ldi0 : 6;
        unsigned int sel_ldi0_pll : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV5_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_START (0)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_END (5)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_START (6)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_END (7)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_START (8)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_END (13)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_START (14)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_END (15)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_sdio1 : 4;
        unsigned int sc_sel_sdio1 : 3;
        unsigned int reserved : 1;
        unsigned int sc_div_ldi1 : 6;
        unsigned int sel_ldi1_pll : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV6_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_START (0)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_END (3)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_START (4)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_END (6)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_START (8)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_END (13)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_START (14)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_END (15)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_ispfunc1 : 5;
        unsigned int sel_ispfunc1 : 2;
        unsigned int sc_isp_func_clk_sel_ispfunc1 : 1;
        unsigned int sc_sel_clk_rxdpbhy_cfg : 1;
        unsigned int reserved : 3;
        unsigned int div_clk_spi : 4;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV7_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_START (0)
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_END (4)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_START (5)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_END (6)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_START (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_END (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_START (8)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_END (8)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_START (12)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_END (15)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_ispfunc2 : 5;
        unsigned int sel_ispfunc2 : 1;
        unsigned int sc_div_venc : 5;
        unsigned int sel_venc : 2;
        unsigned int reserved : 3;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV8_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_START (0)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_END (4)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_START (5)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_END (5)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_START (6)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_END (10)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_START (11)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_END (12)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_vdec : 5;
        unsigned int sel_vdec : 2;
        unsigned int reserved : 9;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV9_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_START (0)
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_END (4)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_START (5)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_END (6)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_vcodecbus : 5;
        unsigned int sc_sel_vcodecbus : 2;
        unsigned int sc_div_vivobus : 5;
        unsigned int sc_sel_vivobus : 2;
        unsigned int sc_div_perf_stat : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV10_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_START (0)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_END (4)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_START (5)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_END (6)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_START (7)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_END (11)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_START (12)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_END (13)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_START (14)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_END (15)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_ispa7 : 5;
        unsigned int sel_ispa7 : 2;
        unsigned int sc_div_a53hpm : 2;
        unsigned int sel_a53hpm : 1;
        unsigned int reserved : 6;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV11_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_START (0)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_END (4)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_START (5)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_END (6)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_START (7)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_END (8)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_START (9)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_END (9)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_modem_bbe16 : 2;
        unsigned int sc_div_modem_mcpu : 2;
        unsigned int reserved_0 : 1;
        unsigned int sc_div_slimbus : 6;
        unsigned int sc_sel_slimbus : 2;
        unsigned int reserved_1 : 3;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV12_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_START (0)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_END (1)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_START (2)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_END (3)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_START (5)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_END (10)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_START (11)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_END (12)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int div_modem_bbe16 : 4;
        unsigned int sel_modem_bbe16 : 2;
        unsigned int div_modem_mcpu : 4;
        unsigned int sel_modem_mcpu : 2;
        unsigned int div_ptp : 4;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV13_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_START (0)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_END (3)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_START (4)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_END (5)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_START (6)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_END (9)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_START (10)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_END (11)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_START (12)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_END (15)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_sel_clk_usb3phy_ref : 1;
        unsigned int reserved : 3;
        unsigned int div_clkout0_pll : 6;
        unsigned int div_clkout1_pll : 6;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV14_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_START (0)
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_END (0)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_START (4)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_END (9)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_START (10)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_END (15)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int div_avstrig : 16;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV15_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_START (0)
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_END (15)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int div_avstrig : 4;
        unsigned int sc_div_i2c : 4;
        unsigned int ddrcpll_sw : 4;
        unsigned int ddrc_clk_sw_req_cfg : 2;
        unsigned int reserved : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV16_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_START (0)
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_END (3)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_START (4)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_END (7)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_START (8)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_END (11)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_START (12)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_END (13)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_div_cfgbus : 2;
        unsigned int sc_div_mmc0_peribus : 1;
        unsigned int sc_div_mmc1_peribus : 1;
        unsigned int div_modem_bbe16_tdl : 4;
        unsigned int sel_modem_bbe16_tdl : 4;
        unsigned int sc_div_dbgsechsic_bus : 1;
        unsigned int sc_div_cssysdbg : 1;
        unsigned int reserved : 1;
        unsigned int sc_div_dmabus : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV17_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_START (0)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_END (1)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_START (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_END (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_START (3)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_END (3)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_START (4)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_END (7)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_START (8)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_END (11)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_START (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_END (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_START (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_END (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_START (15)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_END (15)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_g3daxi0 : 1;
        unsigned int gt_clk_g3daxi1 : 1;
        unsigned int gt_clk_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_lpmcu : 1;
        unsigned int reserved_1 : 1;
        unsigned int gt_clk_ldi0 : 1;
        unsigned int gt_clk_ldi1 : 1;
        unsigned int gt_clk_edc0 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_out0 : 1;
        unsigned int gt_clk_out1 : 1;
        unsigned int gt_clk_rxdphy_cfg : 1;
        unsigned int gt_clk_ispfunc1 : 1;
        unsigned int gt_clk_ispfunc2 : 1;
        unsigned int gt_clk_vdec : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV18_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_START (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_END (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_START (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_END (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_START (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_END (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_START (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_END (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_START (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_END (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_START (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_END (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_START (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_END (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_START (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_END (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_START (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_END (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_START (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_END (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_START (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_END (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_START (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_END (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_START (15)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_END (15)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_venc : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_emmc0 : 1;
        unsigned int gt_clk_sd : 1;
        unsigned int gt_clk_sdio0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int gt_clk_a53hpm : 1;
        unsigned int gt_clk_sdio1 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int gt_clk_uarth : 1;
        unsigned int gt_clk_uartl : 1;
        unsigned int gt_clk_spi : 1;
        unsigned int reserved_5 : 1;
        unsigned int gt_clk_slimbus : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV19_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_START (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_END (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_START (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_END (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_START (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_END (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_START (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_END (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_START (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_END (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_START (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_END (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_START (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_END (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_START (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_END (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_START (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_END (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_START (15)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_END (15)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_i2c : 1;
        unsigned int gt_clk_vivobus : 1;
        unsigned int gt_clk_vcodecbus : 1;
        unsigned int gt_clk_aomm : 1;
        unsigned int gt_clk_ispa7 : 1;
        unsigned int gt_clk_ptp : 1;
        unsigned int gt_clk_modem_mcpu : 1;
        unsigned int gt_clk_modem_bbe16 : 1;
        unsigned int gt_clk_modem_bbe16_tdl : 1;
        unsigned int gt_clk_ivp32dsp_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_ref_a : 1;
        unsigned int gt_clk_ddrphy_ref_b : 1;
        unsigned int gt_clk_ddrphy_ref_c : 1;
        unsigned int gt_clk_ddrphy_ref_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV20_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_START (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_END (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_START (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_END (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_START (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_END (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_START (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_END (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_START (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_END (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_START (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_END (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_START (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_END (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_START (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_END (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_START (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_END (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_START (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_END (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_START (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_END (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_START (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_END (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_START (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_END (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_START (14)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_END (14)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV21_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 7;
        unsigned int sc_div_aomm : 4;
        unsigned int div_clk_sys_ddr : 2;
        unsigned int div_clk_sys_sysbus : 2;
        unsigned int reserved_1 : 1;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV22_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_START (7)
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_END (10)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_START (11)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_END (12)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_START (13)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_END (14)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int div_clk_ddrc : 5;
        unsigned int div_clk_ddrcfg : 2;
        unsigned int gt_clk_ddrcfg : 1;
        unsigned int div_clk_ddrphy_ref : 1;
        unsigned int div_clk_ddrphy_ref_en : 1;
        unsigned int div_clk_ddrsys : 2;
        unsigned int gt_div_ddrsys_noc : 1;
        unsigned int gt_clk_ddrc_sw : 1;
        unsigned int reserved : 2;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV23_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_START (0)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_END (4)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_START (5)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_END (6)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_START (7)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_END (7)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_START (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_END (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_START (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_END (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_START (10)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_END (11)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_START (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_END (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_START (13)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_END (13)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int div_isp_snclk : 2;
        unsigned int gt_clk_isp_snclk : 1;
        unsigned int sel_clk_isp_snclk : 1;
        unsigned int reserved : 12;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV24_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_START (0)
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_END (1)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_START (2)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_END (2)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_START (3)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_END (3)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int clkdivmasken : 16;
    } reg;
} SOC_CRGPERIPH_CLKDIV25_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_START (16)
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PER_STAT0_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bootmode : 2;
        unsigned int sc_noc_aobus_idle_flag : 1;
        unsigned int isp_to_ddrc_dfs_en : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_PER_STAT1_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT1_bootmode_START (0)
#define SOC_CRGPERIPH_PER_STAT1_bootmode_END (1)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_START (2)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_END (2)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_START (3)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int swdone_clk_aclk_ddrc : 1;
        unsigned int swdone_clk_sysbus_div : 1;
        unsigned int swdone_clk_lpmcu_div : 1;
        unsigned int swdone_clk_vcodecbus_div : 1;
        unsigned int swdone_clk_vivobus_div : 1;
        unsigned int swdone_clk_ddrcfg : 1;
        unsigned int swdone_clk_ldi0_div : 1;
        unsigned int swdone_clk_ldi1_div : 1;
        unsigned int swdone_clk_edc0_div : 1;
        unsigned int swdone_clk_ddrsys : 1;
        unsigned int swdone_clk_ispfunc1_div : 1;
        unsigned int swdone_clk_ispfunc2_div : 1;
        unsigned int swdone_clk_vdec_div : 1;
        unsigned int swdone_clk_venc_div : 1;
        unsigned int ddr_pll_sw_ack : 4;
        unsigned int swdone_clk_sd_div : 1;
        unsigned int swdone_clk_sdio0_div : 1;
        unsigned int swdone_clk_sdio1_div : 1;
        unsigned int swdone_clk_a53hpm_div : 1;
        unsigned int swdone_clk_emmc0_div : 1;
        unsigned int swdone_clk_aomm_div : 1;
        unsigned int swdone_clk_isp_snclk_div : 1;
        unsigned int swdone_clk_uarth_div : 1;
        unsigned int swdone_clk_uartl_div : 1;
        unsigned int swdone_clk_spi_div : 1;
        unsigned int swdone_clk_i2c_div : 1;
        unsigned int swdone_clk_modem_mcpu_div : 1;
        unsigned int swdone_clk_modem_bbe16_div : 1;
        unsigned int swdone_clk_out0_div1 : 1;
    } reg;
} SOC_CRGPERIPH_PER_STAT2_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_START (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_END (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_START (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_END (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_START (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_END (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_START (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_END (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_START (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_END (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_START (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_END (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_START (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_END (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_START (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_END (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_START (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_END (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_START (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_END (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_START (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_END (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_START (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_END (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_START (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_END (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_START (13)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_END (13)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_START (14)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_END (17)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_START (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_END (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_START (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_END (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_START (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_END (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_START (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_END (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_START (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_END (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_START (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_END (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_START (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_END (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_START (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_END (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_START (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_END (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_START (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_END (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_START (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_END (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_START (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_END (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_START (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_END (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_START (31)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int swdone_clk_out1_div1 : 1;
        unsigned int swdone_clk_cfgbus_div : 1;
        unsigned int swdone_clk_dbgsechsic_bus_div : 1;
        unsigned int swdone_clk_modem_bbe16_tdl_div : 1;
        unsigned int swdone_clk_dmabus_div : 1;
        unsigned int swdone_clk_ispfunc : 1;
        unsigned int swdone_clk_slimbus_div : 1;
        unsigned int swdone_clk_ispa7_div : 1;
        unsigned int ldi0_pll_sw_ack : 4;
        unsigned int ldi1_pll_sw_ack : 4;
        unsigned int mcpu_pll_sw_ack : 4;
        unsigned int bbe16_pll_sw_ack : 4;
        unsigned int ddrclksw2sys : 1;
        unsigned int ddrclksw2pll : 1;
        unsigned int sysbusclksw2sys : 1;
        unsigned int sysbusclksw2pll : 1;
        unsigned int lpmcuclksw2sys : 1;
        unsigned int lpmcuclksw2pll : 1;
        unsigned int swdone_clk_cssysdbg_div : 1;
        unsigned int swdone_clk_ivp32dsp_core_div : 1;
    } reg;
} SOC_CRGPERIPH_PER_STAT3_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_START (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_END (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_START (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_END (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_START (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_END (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_START (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_END (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_START (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_END (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_START (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_END (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_START (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_END (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_START (7)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_END (7)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_START (8)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_END (11)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_START (12)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_END (15)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_START (16)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_END (19)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_START (20)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_END (23)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_START (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_END (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_START (25)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_END (25)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_START (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_END (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_START (27)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_END (27)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_START (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_END (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_START (29)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_END (29)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_START (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_END (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_START (31)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cactive_cci400_cfgcnt : 8;
        unsigned int gt_clk_cci400_bypass : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_CRGPERIPH_PERCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_START (0)
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_END (7)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_START (8)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_auto_clk_cci2sysbus_async_bypass : 1;
        unsigned int gt_auto_clk_i2c34_bypass : 1;
        unsigned int gt_auto_clk_uart025_bypass : 1;
        unsigned int gt_auto_clk_uart14_bypass : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_PERCTRL1_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_START (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_END (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_START (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_END (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_START (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_END (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_START (3)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pclkdbg_sel : 1;
        unsigned int pclkdbg_clkoff_sys : 1;
        unsigned int pclkdbg_to_a53cfg_clkoff_sys_0 : 1;
        unsigned int pclkdbg_to_a53cfg_clkoff_sys_1 : 1;
        unsigned int pclkdbg_to_iomcu_clkoff_sys : 1;
        unsigned int pclkdbg_to_lpmcu_clkoff_sys : 1;
        unsigned int traceclkin_clkoff_sys : 1;
        unsigned int atclkoff_sys : 1;
        unsigned int atclk_to_iomcu_clkoff_sys : 1;
        unsigned int atclk_to_a53crg_clkoff_sys_0 : 1;
        unsigned int atclk_to_a53crg_clkoff_sys_1 : 1;
        unsigned int cs_soft_rst_req : 1;
        unsigned int traceclkin_sel : 2;
        unsigned int reserved : 1;
        unsigned int cs_cssys_rst_req : 1;
        unsigned int atclk_to_modem_clkoff_sys : 1;
        unsigned int pclkdbg_to_modem_clkoff_sys : 1;
        unsigned int modem_cssys_rst_req : 1;
        unsigned int asp_cssys_rst_req : 1;
        unsigned int atclk_to_asp_clkoff_sys : 1;
        unsigned int pclkdbg_to_asp_clkoff_sys : 1;
        unsigned int time_stamp_clk_sel : 3;
        unsigned int gt_clk_cssys_atclk : 1;
        unsigned int ip_rst_cssys_atclk : 1;
        unsigned int gt_clk_time_stamp : 1;
        unsigned int ip_rst_time_stamp : 1;
        unsigned int atclk_to_iapa7_clkoff_sys : 1;
        unsigned int pclkdbg_to_iapa7_clkoff_sys : 1;
        unsigned int ispa7_mask : 1;
    } reg;
} SOC_CRGPERIPH_PERCTRL2_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_START (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_END (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_START (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_END (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_START (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_END (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_START (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_END (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_START (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_END (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_START (5)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_END (5)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_START (6)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_END (6)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_START (7)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_END (7)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_START (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_END (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_START (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_END (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_START (10)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_END (10)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_START (11)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_END (11)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_START (12)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_END (13)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_START (15)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_END (15)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_START (16)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_END (16)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_START (17)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_END (17)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_START (18)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_END (18)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_START (19)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_END (19)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_START (20)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_END (20)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_START (21)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_END (21)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_START (22)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_END (24)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_START (25)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_END (25)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_START (26)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_END (26)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_START (27)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_END (27)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_START (28)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_END (28)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_START (29)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_END (29)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_START (30)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_END (30)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_START (31)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int noc_timeout_en : 1;
        unsigned int reserved_0 : 5;
        unsigned int mem_ctrl_pgt_lpm3 : 6;
        unsigned int mcpu_fiq_n : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_CRGPERIPH_PERCTRL3_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_START (0)
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_END (0)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_START (6)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_END (11)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_START (12)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_ipf_clk_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_PERCTRL4_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_START (0)
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PERCTRL5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_PERCTRL6_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeren18sel : 1;
        unsigned int timeren18ov : 1;
        unsigned int timeren19sel : 1;
        unsigned int timeren19ov : 1;
        unsigned int timeren20sel : 1;
        unsigned int timeren20ov : 1;
        unsigned int timeren21sel : 1;
        unsigned int timeren21ov : 1;
        unsigned int timeren22sel : 1;
        unsigned int timeren22ov : 1;
        unsigned int timeren23sel : 1;
        unsigned int timeren23ov : 1;
        unsigned int timeren24sel : 1;
        unsigned int timeren24ov : 1;
        unsigned int timeren25sel : 1;
        unsigned int timeren25ov : 1;
        unsigned int wdog1enov : 1;
        unsigned int wdog0enov : 1;
        unsigned int wd0_dbgack_byp : 1;
        unsigned int wd1_dbgack_byp : 1;
        unsigned int reserved : 12;
    } reg;
} SOC_CRGPERIPH_PERTIMECTRL_UNION;
#endif
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_START (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_END (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_START (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_END (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_START (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_END (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_START (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_END (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_START (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_END (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_START (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_END (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_START (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_END (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_START (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_END (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_START (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_END (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_START (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_END (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_START (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_END (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_START (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_END (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_START (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_END (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_START (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_END (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_START (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_END (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_START (15)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_END (15)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_START (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_END (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_START (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_END (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_START (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_END (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_START (19)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispisoen : 1;
        unsigned int vencisoen : 1;
        unsigned int vdecisoen : 1;
        unsigned int reserved_0 : 1;
        unsigned int modemsubsysisoen : 1;
        unsigned int g3disoen : 1;
        unsigned int dsssubsysisoen : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int a53_0_cor0isoen : 1;
        unsigned int a53_0_cor1isoen : 1;
        unsigned int a53_0_cor2isoen : 1;
        unsigned int a53_0_cor3isoen : 1;
        unsigned int a53isoen : 1;
        unsigned int a53_1_cor0isoen : 1;
        unsigned int a53_1_cor1isoen : 1;
        unsigned int a53_1_cor2isoen : 1;
        unsigned int a53_1_cor3isoen : 1;
        unsigned int a57isoen : 1;
        unsigned int modemperiisoen : 1;
        unsigned int modemirmisoen : 1;
        unsigned int ivp32dspisoen : 1;
        unsigned int reserved_6 : 7;
    } reg;
} SOC_CRGPERIPH_ISOEN_UNION;
#endif
#define SOC_CRGPERIPH_ISOEN_ispisoen_START (0)
#define SOC_CRGPERIPH_ISOEN_ispisoen_END (0)
#define SOC_CRGPERIPH_ISOEN_vencisoen_START (1)
#define SOC_CRGPERIPH_ISOEN_vencisoen_END (1)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_START (2)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_END (2)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_START (4)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_END (4)
#define SOC_CRGPERIPH_ISOEN_g3disoen_START (5)
#define SOC_CRGPERIPH_ISOEN_g3disoen_END (5)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_START (6)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_END (6)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_START (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_END (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_START (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_END (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_START (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_END (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_START (15)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_END (15)
#define SOC_CRGPERIPH_ISOEN_a53isoen_START (16)
#define SOC_CRGPERIPH_ISOEN_a53isoen_END (16)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_START (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_END (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_START (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_END (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_START (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_END (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_START (20)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_END (20)
#define SOC_CRGPERIPH_ISOEN_a57isoen_START (21)
#define SOC_CRGPERIPH_ISOEN_a57isoen_END (21)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_START (22)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_END (22)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_START (23)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_END (23)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_START (24)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispisoen : 1;
        unsigned int vencisoen : 1;
        unsigned int vdecisoen : 1;
        unsigned int reserved_0 : 1;
        unsigned int modemsubsysisoen : 1;
        unsigned int g3disoen : 1;
        unsigned int dsssubsysisoen : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int a53_0_cor0isoen : 1;
        unsigned int a53_0_cor1isoen : 1;
        unsigned int a53_0_cor2isoen : 1;
        unsigned int a53_0_cor3isoen : 1;
        unsigned int a53isoen : 1;
        unsigned int a53_1_cor0isoen : 1;
        unsigned int a53_1_cor1isoen : 1;
        unsigned int a53_1_cor2isoen : 1;
        unsigned int a53_1_cor3isoen : 1;
        unsigned int a57isoen : 1;
        unsigned int modemperiisoen : 1;
        unsigned int modemirmisoen : 1;
        unsigned int ivp32dspisoen : 1;
        unsigned int reserved_6 : 7;
    } reg;
} SOC_CRGPERIPH_ISODIS_UNION;
#endif
#define SOC_CRGPERIPH_ISODIS_ispisoen_START (0)
#define SOC_CRGPERIPH_ISODIS_ispisoen_END (0)
#define SOC_CRGPERIPH_ISODIS_vencisoen_START (1)
#define SOC_CRGPERIPH_ISODIS_vencisoen_END (1)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_START (2)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_END (2)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_START (4)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_END (4)
#define SOC_CRGPERIPH_ISODIS_g3disoen_START (5)
#define SOC_CRGPERIPH_ISODIS_g3disoen_END (5)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_START (6)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_END (6)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_START (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_END (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_START (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_END (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_START (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_END (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_START (15)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_END (15)
#define SOC_CRGPERIPH_ISODIS_a53isoen_START (16)
#define SOC_CRGPERIPH_ISODIS_a53isoen_END (16)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_START (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_END (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_START (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_END (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_START (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_END (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_START (20)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_END (20)
#define SOC_CRGPERIPH_ISODIS_a57isoen_START (21)
#define SOC_CRGPERIPH_ISODIS_a57isoen_END (21)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_START (22)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_END (22)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_START (23)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_END (23)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_START (24)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispisoen : 1;
        unsigned int vencisoen : 1;
        unsigned int vdecisoen : 1;
        unsigned int reserved_0 : 1;
        unsigned int modemsubsysisoen : 1;
        unsigned int g3disoen : 1;
        unsigned int dsssubsysisoen : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int a53_0_cor0isoen : 1;
        unsigned int a53_0_cor1isoen : 1;
        unsigned int a53_0_cor2isoen : 1;
        unsigned int a53_0_cor3isoen : 1;
        unsigned int a53isoen : 1;
        unsigned int a53_1_cor0isoen : 1;
        unsigned int a53_1_cor1isoen : 1;
        unsigned int a53_1_cor2isoen : 1;
        unsigned int a53_1_cor3isoen : 1;
        unsigned int a57isoen : 1;
        unsigned int modemperiisoen : 1;
        unsigned int modemirmisoen : 1;
        unsigned int ivp32dspisoen : 1;
        unsigned int reserved_6 : 7;
    } reg;
} SOC_CRGPERIPH_ISOSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_START (0)
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_END (0)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_START (1)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_END (1)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_START (2)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_END (2)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_START (4)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_END (4)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_START (5)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_END (5)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_START (6)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_END (6)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_START (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_END (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_START (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_END (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_START (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_END (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_START (15)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_END (15)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_START (16)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_END (16)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_START (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_END (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_START (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_END (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_START (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_END (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_START (20)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_END (20)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_START (21)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_END (21)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_START (22)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_END (22)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_START (23)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_END (23)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_START (24)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isppwren : 1;
        unsigned int vencpwren : 1;
        unsigned int vdecpwren : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dsssubsyspwren : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int a53_0_cor0pwren : 1;
        unsigned int a53_0_cor1pwren : 1;
        unsigned int a53_0_cor2pwren : 1;
        unsigned int a53_0_cor3pwren : 1;
        unsigned int a53_1_cor0pwren : 1;
        unsigned int a53_1_cor1pwren : 1;
        unsigned int a53_1_cor2pwren : 1;
        unsigned int a53_1_cor3pwren : 1;
        unsigned int modemperipwren : 1;
        unsigned int modemirmpwren : 1;
        unsigned int ivp32dsppwren : 1;
        unsigned int reserved_7 : 10;
    } reg;
} SOC_CRGPERIPH_PERPWREN_UNION;
#endif
#define SOC_CRGPERIPH_PERPWREN_isppwren_START (0)
#define SOC_CRGPERIPH_PERPWREN_isppwren_END (0)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_START (1)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_END (1)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_START (2)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_END (2)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_START (5)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_END (5)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_START (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_END (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_START (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_END (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_START (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_END (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_START (14)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_END (14)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_START (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_END (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_START (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_END (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_START (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_END (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_START (18)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_END (18)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_START (19)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_END (19)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_START (20)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_END (20)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_START (21)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isppwrdis : 1;
        unsigned int vencpwrdis : 1;
        unsigned int vdecpwrdis : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dsssubsyspwrdis : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int a53_0_cor0pwrdis : 1;
        unsigned int a53_0_cor1pwrdis : 1;
        unsigned int a53_0_cor2pwrdis : 1;
        unsigned int a53_0_cor3pwrdis : 1;
        unsigned int a53_1_cor0pwrdis : 1;
        unsigned int a53_1_cor1pwrdis : 1;
        unsigned int a53_1_cor2pwrdis : 1;
        unsigned int a53_1_cor3pwrdis : 1;
        unsigned int modemperipwrdis : 1;
        unsigned int modemirmpwrdis : 1;
        unsigned int ivp32dsppwrdis : 1;
        unsigned int reserved_7 : 10;
    } reg;
} SOC_CRGPERIPH_PERPWRDIS_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_START (0)
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_END (0)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_START (1)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_END (1)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_START (2)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_END (2)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_START (5)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_END (5)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_START (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_END (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_START (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_END (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_START (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_END (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_START (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_END (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_START (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_END (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_START (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_END (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_START (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_END (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_START (18)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_END (18)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_START (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_END (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_START (20)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_END (20)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_START (21)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isppwrstat : 1;
        unsigned int vencpwrstat : 1;
        unsigned int vdecpwrstat : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dsssubsyspwrstat : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int a53_0_cor0pwrstat : 1;
        unsigned int a53_0_cor1pwrstat : 1;
        unsigned int a53_0_cor2pwrstat : 1;
        unsigned int a53_0_cor3pwrstat : 1;
        unsigned int a53_1_cor0pwrstat : 1;
        unsigned int a53_1_cor1pwrstat : 1;
        unsigned int a53_1_cor2pwrstat : 1;
        unsigned int a53_1_cor3pwrstat : 1;
        unsigned int modemperipwrstat : 1;
        unsigned int modemirmpwrstat : 1;
        unsigned int ivp32dsppwrstat : 1;
        unsigned int reserved_7 : 10;
    } reg;
} SOC_CRGPERIPH_PERPWRSTAT_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_START (0)
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_END (0)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_START (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_END (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_START (2)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_END (2)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_START (5)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_END (5)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_START (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_END (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_START (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_END (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_START (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_END (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_START (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_END (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_START (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_END (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_START (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_END (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_START (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_END (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_START (18)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_END (18)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_START (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_END (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_START (20)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_END (20)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_START (21)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isppwrack : 1;
        unsigned int vencpwrack : 1;
        unsigned int vdecpwrack : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dsssubsyspwrack : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int a53_0_core0pwrack : 1;
        unsigned int a53_0_core1pwrack : 1;
        unsigned int a53_0_core2pwrack : 1;
        unsigned int a53_0_core3pwrack : 1;
        unsigned int a53_1_core0pwrack : 1;
        unsigned int a53_1_core1pwrack : 1;
        unsigned int a53_1_core2pwrack : 1;
        unsigned int a53_1_core3pwrack : 1;
        unsigned int reserved_7 : 1;
        unsigned int g3dshpwrack0 : 1;
        unsigned int g3dshpwrack1 : 1;
        unsigned int g3dshpwrack2 : 1;
        unsigned int g3dshpwrack3 : 1;
        unsigned int g3dshpwrack4 : 1;
        unsigned int g3dshpwrack5 : 1;
        unsigned int g3dcg0en : 1;
        unsigned int modemperipwrack : 1;
        unsigned int modemirmpwrack : 1;
        unsigned int ivp32dsppwrack : 1;
        unsigned int reserved_8 : 2;
    } reg;
} SOC_CRGPERIPH_PERPWRACK_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_START (0)
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_END (0)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_START (1)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_END (1)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_START (2)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_END (2)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_START (5)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_END (5)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_START (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_END (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_START (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_END (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_START (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_END (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_START (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_END (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_START (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_END (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_START (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_END (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_START (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_END (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_START (18)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_END (18)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_START (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_END (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_START (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_END (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_START (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_END (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_START (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_END (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_START (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_END (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_START (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_END (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_START (26)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_END (26)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_START (27)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_END (27)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_START (28)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_END (28)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_START (29)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_clkinen_sys : 1;
        unsigned int a53_atclkoff_sys_n : 1;
        unsigned int a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;
        unsigned int a53_atclk_to_asyn_bri_clkoff_sys_n : 1;
        unsigned int a53_pclkdbg_to_a53_cs_clkoff_sys_n : 1;
        unsigned int reserved : 10;
        unsigned int a53_clkoff_sys : 1;
        unsigned int clkmasken : 16;
    } reg;
} SOC_CRGPERIPH_A53_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_START (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_END (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_START (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_END (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_START (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_END (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_START (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_END (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_START (15)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_END (15)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_START (16)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_coresight_soft_rst_req : 1;
        unsigned int a53_adb_asyn_bri_rst_req : 1;
        unsigned int a53_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a53_core_rst_software_req : 4;
        unsigned int a53_rst_software_req : 1;
        unsigned int a53_core_por_rst_req : 4;
        unsigned int a53_hpm_cpu_rst_req : 4;
        unsigned int a53_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a53_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_A53_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_START (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_END (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_START (31)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_coresight_soft_rst_req : 1;
        unsigned int a53_adb_asyn_bri_rst_req : 1;
        unsigned int a53_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a53_core_rst_software_req : 4;
        unsigned int a53_rst_software_req : 1;
        unsigned int a53_core_por_rst_req : 4;
        unsigned int a53_hpm_cpu_rst_req : 4;
        unsigned int a53_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a53_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_A53_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_START (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_END (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_START (31)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_coresight_soft_rst_req : 1;
        unsigned int a53_adb_asyn_bri_rst_req : 1;
        unsigned int a53_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a53_core_rst_software_req : 4;
        unsigned int a53_rst_software_req : 1;
        unsigned int a53_core_por_rst_req : 4;
        unsigned int a53_hpm_cpu_rst_req : 4;
        unsigned int a53_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a53_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_A53_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_START (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_END (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_START (31)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_d_pwrdnreqn : 1;
        unsigned int a53_d_pwrdnackn : 1;
        unsigned int a53_d_cactives : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_A53_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_START (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_END (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_START (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_END (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_START (2)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_pd_detect_clr : 1;
        unsigned int a53_pd_detect_start : 1;
        unsigned int a53_set_acinactm_low : 1;
        unsigned int a53_set_acinactm_high : 1;
        unsigned int a53_dbgpwrdup : 4;
        unsigned int a53_l2rstdisable : 1;
        unsigned int a53_l1rstdisable : 1;
        unsigned int reserved : 2;
        unsigned int a53_broadcastcachemaint : 1;
        unsigned int a53_broadcastouter : 1;
        unsigned int a53_broadcastinner : 1;
        unsigned int a53_sysbardisable : 1;
        unsigned int a53_vinithi : 4;
        unsigned int a53_sei_n : 4;
        unsigned int a53_rei_n : 4;
        unsigned int a53_vsei_n : 4;
    } reg;
} SOC_CRGPERIPH_A53_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_START (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_END (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_START (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_END (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_START (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_END (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_START (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_END (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_START (4)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_END (7)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_START (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_END (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_START (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_END (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_START (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_END (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_START (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_END (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_START (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_END (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_START (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_END (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_START (16)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_END (19)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_START (20)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_END (23)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_START (24)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_END (27)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_START (28)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_ctrl_cpu : 16;
        unsigned int mem_ctrl_s_a53cs : 16;
    } reg;
} SOC_CRGPERIPH_A53_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_START (0)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_END (15)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_START (16)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_aa64naa32 : 4;
        unsigned int a53_ret_ctrl_ret : 3;
        unsigned int a53_ret_ctrl_norm : 3;
        unsigned int a53_wfe_ret_en_l2 : 1;
        unsigned int a53_wfi_ret_en_l2 : 1;
        unsigned int a53_dyn_ret_en_l2 : 1;
        unsigned int a53_l2flushreq : 1;
        unsigned int a53_sys_cnt_en_dly : 6;
        unsigned int a53_ret_wait_cycle : 6;
        unsigned int a53_ret_wait_cycle_chg : 1;
        unsigned int a53_l2_input_lat_sel : 1;
        unsigned int a53_l2_output_lat_sel : 1;
        unsigned int a53_stretch_l2ramclk_en : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_CRGPERIPH_A53_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_START (0)
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_END (3)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_START (4)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_END (6)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_START (7)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_END (9)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_START (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_END (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_START (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_END (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_START (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_END (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_START (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_END (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_START (14)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_END (19)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_START (20)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_END (25)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_START (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_END (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_START (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_END (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_START (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_END (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_START (29)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_standbywfi : 4;
        unsigned int a53_standbywfe : 4;
        unsigned int a53_smpen : 4;
        unsigned int a53_standbywfil2 : 1;
        unsigned int a53_dbgack : 1;
        unsigned int a53_l2flushdone : 1;
        unsigned int a53_idle_flag : 1;
        unsigned int a53_sbgpwrupreq : 4;
        unsigned int a53_dbgnopwrdwn : 4;
        unsigned int a53_snoop_cnt : 6;
        unsigned int reserved : 2;
    } reg;
} SOC_CRGPERIPH_A53_STAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_START (0)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_END (3)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_START (4)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_END (7)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_START (8)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_END (11)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_START (12)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_END (12)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_START (13)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_END (13)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_START (14)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_END (14)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_START (15)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_END (15)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_START (16)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_END (19)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_START (20)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_END (23)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_START (24)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_clkinen_sys : 1;
        unsigned int a57_atclkoff_sys_n : 1;
        unsigned int a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;
        unsigned int a57_atclk_to_asyn_bri_clkoff_sys_n : 1;
        unsigned int reserved : 11;
        unsigned int a57_clkoff_sys : 1;
        unsigned int clkmasken : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_START (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_END (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_START (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_END (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_START (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_END (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_START (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_END (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_START (16)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_coresight_soft_rst_req : 1;
        unsigned int a57_adb_asyn_bri_rst_req : 1;
        unsigned int a57_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a57_core_rst_software_req : 4;
        unsigned int a57_rst_software_req : 1;
        unsigned int a57_core_por_rst_req : 4;
        unsigned int a57_hpm_cpu_rst_req : 4;
        unsigned int a57_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a57_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_MAIA_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_START (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_END (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_START (31)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_coresight_soft_rst_req : 1;
        unsigned int a57_adb_asyn_bri_rst_req : 1;
        unsigned int a57_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a57_core_rst_software_req : 4;
        unsigned int a57_rst_software_req : 1;
        unsigned int a57_core_por_rst_req : 4;
        unsigned int a57_hpm_cpu_rst_req : 4;
        unsigned int a57_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a57_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_MAIA_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_START (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_END (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_START (31)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_coresight_soft_rst_req : 1;
        unsigned int a57_adb_asyn_bri_rst_req : 1;
        unsigned int a57_npresetdbg_rst_req : 1;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int a57_core_rst_software_req : 4;
        unsigned int a57_rst_software_req : 1;
        unsigned int a57_core_por_rst_req : 4;
        unsigned int a57_hpm_cpu_rst_req : 4;
        unsigned int a57_hpm_scu_rst_req : 1;
        unsigned int reserved_2 : 6;
        unsigned int a57_srst_req_en : 1;
    } reg;
} SOC_CRGPERIPH_MAIA_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_START (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_END (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_START (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_END (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_START (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_END (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_START (11)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_END (14)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_START (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_END (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_START (16)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_END (19)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_START (20)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_END (23)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_START (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_END (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_START (31)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_d_pwrdnreqn : 1;
        unsigned int a57_d_pwrdnackn : 1;
        unsigned int a57_d_cactives : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_START (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_END (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_START (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_END (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_START (2)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_pd_detect_clr : 1;
        unsigned int a57_pd_detect_start : 1;
        unsigned int a57_set_acinactm_low : 1;
        unsigned int a57_set_acinactm_high : 1;
        unsigned int a57_dbgpwrdup : 4;
        unsigned int a57_l2rstdisable : 1;
        unsigned int a57_l1rstdisable : 1;
        unsigned int reserved : 2;
        unsigned int a57_broadcastcachemaint : 1;
        unsigned int a57_broadcastouter : 1;
        unsigned int a57_broadcastinner : 1;
        unsigned int a57_sysbardisable : 1;
        unsigned int a57_vinithi : 4;
        unsigned int a57_sei_n : 4;
        unsigned int a57_rei_n : 4;
        unsigned int a57_vsei_n : 4;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_END (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_START (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_END (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_START (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_END (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_START (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_END (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_START (4)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_END (7)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_START (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_END (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_START (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_END (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_START (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_END (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_START (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_END (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_START (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_END (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_START (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_END (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_START (16)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_END (19)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_START (20)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_END (23)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_START (24)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_END (27)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_START (28)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_ctrl_apu : 16;
        unsigned int mem_ctrl_s_a53cs : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_END (15)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_START (16)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_aa64naa32 : 4;
        unsigned int a57_ret_ctrl_ret : 3;
        unsigned int a57_ret_ctrl_norm : 3;
        unsigned int a57_wfe_ret_en_l2 : 1;
        unsigned int a57_wfi_ret_en_l2 : 1;
        unsigned int a57_dyn_ret_en_l2 : 1;
        unsigned int a57_l2flushreq : 1;
        unsigned int a57_sys_cnt_en_dly : 6;
        unsigned int a57_ret_wait_cycle : 6;
        unsigned int a57_ret_wait_cycle_chg : 1;
        unsigned int reserved : 1;
        unsigned int a57_pmusnapshotreq : 4;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_END (3)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_START (4)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_END (6)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_START (7)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_END (9)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_START (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_END (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_START (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_END (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_START (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_END (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_START (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_END (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_START (14)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_END (19)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_START (20)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_END (25)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_START (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_END (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_START (28)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_standbywfi : 4;
        unsigned int a57_standbywfe : 4;
        unsigned int a57_smpen : 4;
        unsigned int a57_standbywfil2 : 1;
        unsigned int a57_dbgack : 1;
        unsigned int a57_l2flushdone : 1;
        unsigned int a57_idle_flag : 1;
        unsigned int a57_sbgpwrupreq : 4;
        unsigned int a57_dbgnopwrdwn : 4;
        unsigned int a57_snoop_cnt : 6;
        unsigned int reserved : 2;
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_START (0)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_END (3)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_START (4)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_END (7)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_START (8)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_END (11)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_START (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_END (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_START (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_END (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_START (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_END (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_START (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_END (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_START (16)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_END (19)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_START (20)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_END (23)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_START (24)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_pmusnapshotack : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_START (0)
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_CRGPERIPH_CORESIGHTSTAT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csysreq_etr_lpi : 1;
        unsigned int csysack_etr_lpi : 1;
        unsigned int cactive_etr_lpi : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_START (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_END (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_START (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_END (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_START (2)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_ctrl_s_cssys : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_CORESIGHTCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_START (0)
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int etf_a53_1_full : 1;
        unsigned int etf_a53_0_full : 1;
        unsigned int etf_top_full : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_CORESIGHTETFINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_START (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_END (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_START (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_END (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_START (2)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int etr_top_full : 1;
        unsigned int intr_a53_0_core0_gic : 1;
        unsigned int intr_a53_0_core1_gic : 1;
        unsigned int intr_a53_0_core2_gic : 1;
        unsigned int intr_a53_0_core3_gic : 1;
        unsigned int intr_a53_1_core0_gic : 1;
        unsigned int intr_a53_1_core1_gic : 1;
        unsigned int intr_a53_1_core2_gic : 1;
        unsigned int intr_a53_1_core3_gic : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_CRGPERIPH_CORESIGHTETRINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_START (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_END (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_START (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_END (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_START (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_END (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_START (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_END (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_START (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_END (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_START (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_END (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_START (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_END (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_START (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_END (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_START (8)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rs_awvalid_s3 : 1;
        unsigned int rs_arvalid_s3 : 1;
        unsigned int rs_awvalid_s4 : 1;
        unsigned int rs_arvalid_s4 : 1;
        unsigned int cactive_asi_s3 : 1;
        unsigned int cactive_asi_s4 : 1;
        unsigned int dvm_complete_expect1 : 2;
        unsigned int dvm_complete_expect2 : 2;
        unsigned int dvm_complete_expect3 : 2;
        unsigned int dvm_complete_expect4 : 2;
        unsigned int dvm_complete_expect5 : 2;
        unsigned int srb_entry_expect_cr3 : 1;
        unsigned int srb_entry_expect_cd3 : 1;
        unsigned int srb_entry_expect_cr4 : 1;
        unsigned int srb_entry_expect_cd4 : 1;
        unsigned int dvm_scoreboard1 : 2;
        unsigned int dvm_scoreboard2 : 2;
        unsigned int dvm_scoreboard3 : 2;
        unsigned int dvm_scoreboard4 : 2;
        unsigned int dvm_scoreboard5 : 2;
        unsigned int reserved : 2;
    } reg;
} SOC_CRGPERIPH_CCI400STAT1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_START (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_END (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_START (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_END (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_START (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_END (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_START (3)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_END (3)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_START (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_END (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_START (5)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_END (5)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_START (6)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_END (7)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_START (8)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_END (9)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_START (10)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_END (11)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_START (12)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_END (13)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_START (14)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_END (15)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_START (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_END (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_START (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_END (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_START (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_END (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_START (19)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_END (19)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_START (20)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_END (21)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_START (22)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_END (23)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_START (24)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_END (25)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_START (26)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_END (27)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_START (28)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cactivem_adb400_a53_0 : 1;
        unsigned int cactivem_adb400_a53_1 : 1;
        unsigned int cactivem_adb400_g3d_0 : 1;
        unsigned int cactivem_adb400_g3d_1 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_ADB400STAT_UNION;
#endif
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_START (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_END (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_START (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_END (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_START (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_END (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_START (3)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 10;
        unsigned int bufferableoverride : 3;
        unsigned int barrierterminate : 3;
        unsigned int reserved_1 : 13;
        unsigned int striping_granule : 3;
    } reg;
} SOC_CRGPERIPH_CCI400CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_START (10)
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_END (12)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_START (13)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_END (15)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_START (29)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 26;
        unsigned int cci_status_sample_en : 1;
        unsigned int ecorevnum : 4;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_CRGPERIPH_CCI400CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_START (26)
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_END (26)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_START (27)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int activem0 : 1;
        unsigned int activem1 : 1;
        unsigned int activem2 : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_CCI400STAT_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT_activem0_START (0)
#define SOC_CRGPERIPH_CCI400STAT_activem0_END (0)
#define SOC_CRGPERIPH_CCI400STAT_activem1_START (1)
#define SOC_CRGPERIPH_CCI400STAT_activem1_END (1)
#define SOC_CRGPERIPH_CCI400STAT_activem2_START (2)
#define SOC_CRGPERIPH_CCI400STAT_activem2_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_d_pwrdnreqn : 1;
        unsigned int g3d_d_pwrdnackn : 1;
        unsigned int g3d_d_cactives : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_START (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_END (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_START (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_END (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_START (2)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_d_pwrdnreqn : 1;
        unsigned int g3d_d_pwrdnackn : 1;
        unsigned int g3d_d_cactives : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_START (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_END (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_START (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_END (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_START (2)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vcodec_clkrst_bypass : 1;
        unsigned int pctrl_clkrst_bypass : 1;
        unsigned int pwm_clkrst_bypass : 1;
        unsigned int reserved : 1;
        unsigned int wd0_clkrst_bypass : 1;
        unsigned int wd1_clkrst_bypass : 1;
        unsigned int gpio0_clkrst_bypass : 1;
        unsigned int gpio1_clkrst_bypass : 1;
        unsigned int gpio2_clkrst_bypass : 1;
        unsigned int gpio3_clkrst_bypass : 1;
        unsigned int gpio4_clkrst_bypass : 1;
        unsigned int gpio5_clkrst_bypass : 1;
        unsigned int gpio6_clkrst_bypass : 1;
        unsigned int gpio7_clkrst_bypass : 1;
        unsigned int gpio8_clkrst_bypass : 1;
        unsigned int gpio9_clkrst_bypass : 1;
        unsigned int gpio10_clkrst_bypass : 1;
        unsigned int gpio11_clkrst_bypass : 1;
        unsigned int gpio12_clkrst_bypass : 1;
        unsigned int gpio13_clkrst_bypass : 1;
        unsigned int gpio14_clkrst_bypass : 1;
        unsigned int gpio15_clkrst_bypass : 1;
        unsigned int gpio16_clkrst_bypass : 1;
        unsigned int gpio17_clkrst_bypass : 1;
        unsigned int gpio18_clkrst_bypass : 1;
        unsigned int gpio19_clkrst_bypass : 1;
        unsigned int gpio20_clkrst_bypass : 1;
        unsigned int gpio21_clkrst_bypass : 1;
        unsigned int timer9_clkrst_bypass : 1;
        unsigned int timer10_clkrst_bypass : 1;
        unsigned int timer11_clkrst_bypass : 1;
        unsigned int timer12_clkrst_bypass : 1;
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_START (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_END (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_START (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_END (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_START (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_END (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_START (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_END (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_START (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_END (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_START (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_END (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_START (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_END (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_START (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_END (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_START (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_END (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_START (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_END (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_START (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_END (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_START (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_END (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_START (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_END (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_START (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_END (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_START (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_END (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_START (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_END (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_START (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_END (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_START (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_END (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_START (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_END (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_START (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_END (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_START (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_END (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_START (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_END (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_START (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_END (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_START (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_END (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_START (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_END (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_START (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_END (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_START (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_END (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_START (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_END (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_START (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_END (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_START (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_END (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_START (31)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tzpc_clkrst_bypass : 1;
        unsigned int ipc0_clkrst_bypass : 1;
        unsigned int ipc1_clkrst_bypass : 1;
        unsigned int ioc_clkrst_bypass : 1;
        unsigned int codecssi_clkrst_bypass : 1;
        unsigned int hkadcssi_clkrst_bypass : 1;
        unsigned int memrep_clkrst_bypass : 1;
        unsigned int ipc_mdm_clkrst_bypass : 1;
        unsigned int uart0_clkrst_bypass : 1;
        unsigned int uart1_clkrst_bypass : 1;
        unsigned int uart2_clkrst_bypass : 1;
        unsigned int reserved_0 : 1;
        unsigned int uart4_clkrst_bypass : 1;
        unsigned int uart5_clkrst_bypass : 1;
        unsigned int reserved_1 : 1;
        unsigned int spi1_clkrst_bypass : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int i2c3_clkrst_bypass : 1;
        unsigned int i2c4_clkrst_bypass : 1;
        unsigned int dmac_clkrst_bypass : 1;
        unsigned int emmc0_clkrst_bypass : 1;
        unsigned int emmc1_clkrst_bypass : 1;
        unsigned int sd_clkrst_bypass : 1;
        unsigned int sdio0_clkrst_bypass : 1;
        unsigned int socp_clkrst_bypass : 1;
        unsigned int usb3otg_clkrst_bypass : 1;
        unsigned int isp_clkrst_bypass : 1;
        unsigned int dss_clkrst_bypass : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_START (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_END (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_START (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_END (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_START (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_END (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_START (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_END (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_START (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_END (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_START (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_END (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_START (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_END (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_START (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_END (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_START (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_END (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_START (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_END (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_START (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_END (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_START (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_END (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_START (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_END (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_START (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_END (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_START (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_END (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_START (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_END (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_START (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_END (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_START (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_END (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_START (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_END (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_START (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_END (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_START (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_END (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_START (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_END (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_START (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_END (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_START (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_END (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_START (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_clkrst_bypass : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int usb3otg_mux_clkrst_bypass : 1;
        unsigned int usb3otg_ahbif_clkrst_bypass : 1;
        unsigned int reserved_2 : 1;
        unsigned int dsi0_clkrst_bypass : 1;
        unsigned int dsi1_clkrst_bypass : 1;
        unsigned int sdio1_clkrst_bypass : 1;
        unsigned int perf_clkrst_bypass : 1;
        unsigned int secs_clkrst_bypass : 1;
        unsigned int secp_clkrst_bypass : 1;
        unsigned int reserved_3 : 20;
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_START (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_END (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_START (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_END (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_START (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_END (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_START (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_END (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_START (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_END (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_START (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_END (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_START (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_END (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_START (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_END (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_START (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_pdc_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_A53_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_START (0)
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_0_core0_pwr_en : 1;
        unsigned int intr_a53_0_core1_pwr_en : 1;
        unsigned int intr_a53_0_core2_pwr_en : 1;
        unsigned int intr_a53_0_core3_pwr_en : 1;
        unsigned int reserved : 12;
        unsigned int corepwrintenmasken : 16;
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_START (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_END (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_START (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_END (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_START (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_END (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_START (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_END (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_START (16)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_0_core0_pwr_stat : 1;
        unsigned int intr_a53_0_core1_pwr_stat : 1;
        unsigned int intr_a53_0_core2_pwr_stat : 1;
        unsigned int intr_a53_0_core3_pwr_stat : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_START (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_END (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_START (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_END (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_START (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_END (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_START (3)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_0_core0_gic_mask : 1;
        unsigned int intr_a53_0_core1_gic_mask : 1;
        unsigned int intr_a53_0_core2_gic_mask : 1;
        unsigned int intr_a53_0_core3_gic_mask : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_A53_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_START (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_END (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_START (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_END (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_START (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_END (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_START (3)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core0_pwrup_req : 1;
        unsigned int a53_0_core1_pwrup_req : 1;
        unsigned int a53_0_core2_pwrup_req : 1;
        unsigned int a53_0_core3_pwrup_req : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_START (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_END (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_START (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_END (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_START (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_END (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_START (3)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core0_pwrdn_req : 1;
        unsigned int a53_0_core1_pwrdn_req : 1;
        unsigned int a53_0_core2_pwrdn_req : 1;
        unsigned int a53_0_core3_pwrdn_req : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_START (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_END (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_START (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_END (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_START (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_END (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_START (3)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core0_pwr_stat : 4;
        unsigned int a53_0_core1_pwr_stat : 4;
        unsigned int a53_0_core2_pwr_stat : 4;
        unsigned int a53_0_core3_pwr_stat : 4;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_START (0)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_END (3)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_START (4)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_END (7)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_START (8)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_END (11)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_START (12)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_pwrup_time : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_START (0)
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_pwrdn_time : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_START (0)
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_iso_time : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_A53_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_START (0)
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_dbg_time : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_A53_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_START (0)
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_rst_time : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_A53_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_START (0)
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_0_core_urst_time : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CRGPERIPH_A53_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_START (0)
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_1_pdc_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_MAIA_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_START (0)
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_1_core0_pwr_en : 1;
        unsigned int intr_a53_1_core1_pwr_en : 1;
        unsigned int intr_a53_1_core2_pwr_en : 1;
        unsigned int intr_a53_1_core3_pwr_en : 1;
        unsigned int reserved : 12;
        unsigned int corepwrintenmasken : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_START (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_END (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_START (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_END (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_START (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_END (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_START (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_END (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_START (16)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_1_core0_pwr_stat : 1;
        unsigned int intr_a53_1_core1_pwr_stat : 1;
        unsigned int intr_a53_1_core2_pwr_stat : 1;
        unsigned int intr_a53_1_core3_pwr_stat : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_START (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_END (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_START (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_END (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_START (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_END (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_START (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intr_a53_1_core0_gic_mask : 1;
        unsigned int intr_a53_1_core1_gic_mask : 1;
        unsigned int intr_a53_1_core2_gic_mask : 1;
        unsigned int intr_a53_1_core3_gic_mask : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_START (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_END (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_START (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_END (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_START (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_END (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_START (3)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core0_pwrup_req : 1;
        unsigned int a53_1_core1_pwrup_req : 1;
        unsigned int a53_1_core2_pwrup_req : 1;
        unsigned int a53_1_core3_pwrup_req : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_START (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_END (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_START (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_END (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_START (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_END (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_START (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core0_pwrdn_req : 1;
        unsigned int a53_1_core1_pwrdn_req : 1;
        unsigned int a53_1_core2_pwrdn_req : 1;
        unsigned int a53_1_core3_pwrdn_req : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_START (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_END (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_START (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_END (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_START (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_END (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_START (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core0_pwr_stat : 4;
        unsigned int a53_1_core1_pwr_stat : 4;
        unsigned int a53_1_core2_pwr_stat : 4;
        unsigned int a53_1_core3_pwr_stat : 4;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_START (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_END (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_START (4)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_END (7)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_START (8)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_END (11)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_START (12)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_pwrup_time : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_START (0)
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_pwrdn_time : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_START (0)
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_iso_time : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_MAIA_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_START (0)
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_dbg_time : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_START (0)
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_rst_time : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_START (0)
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_1_core_urst_time : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_START (0)
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_clkinen : 1;
        unsigned int ispa7_atclkoff_n : 1;
        unsigned int pclkdbg_to_asyn_bri_clkoff_n : 1;
        unsigned int ispa7_atclk_to_asyn_bri_clkoff_n : 1;
        unsigned int ispa7_pclkdbg_to_cs_clkoff_n : 1;
        unsigned int ispa7_aclkenm_sel : 1;
        unsigned int ispa7_sys_cnt_en_dly : 4;
        unsigned int reserved : 6;
        unsigned int clkmasken : 16;
    } reg;
} SOC_CRGPERIPH_ISPA7_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_START (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_END (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_START (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_END (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_START (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_END (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_START (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_END (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_START (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_END (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_START (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_END (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_START (6)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_END (9)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_START (16)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_core_por_rst_req : 1;
        unsigned int ispa7_rst_software_req : 1;
        unsigned int ispa7_core_rst_software_req : 1;
        unsigned int ispa7_debug_all_rst_req : 1;
        unsigned int ispa7_core_debug_rst_req : 1;
        unsigned int ispa7_coresight_soft_rst_req : 1;
        unsigned int ispa7_dbgrstreq : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_START (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_END (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_START (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_END (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_START (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_END (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_START (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_END (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_START (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_END (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_START (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_END (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_START (6)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_core_por_rst_req : 1;
        unsigned int ispa7_rst_software_req : 1;
        unsigned int ispa7_core_rst_software_req : 1;
        unsigned int ispa7_debug_all_rst_req : 1;
        unsigned int ispa7_core_debug_rst_req : 1;
        unsigned int ispa7_coresight_soft_rst_req : 1;
        unsigned int ispa7_dbgrstreq : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_START (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_END (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_START (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_END (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_START (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_END (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_START (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_END (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_START (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_END (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_START (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_END (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_START (6)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_core_por_rst_req : 1;
        unsigned int ispa7_rst_software_req : 1;
        unsigned int ispa7_core_rst_software_req : 1;
        unsigned int ispa7_debug_all_rst_req : 1;
        unsigned int ispa7_core_debug_rst_req : 1;
        unsigned int ispa7_coresight_soft_rst_req : 1;
        unsigned int ispa7_dbgrstreq : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_START (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_END (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_START (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_END (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_START (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_END (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_START (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_END (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_START (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_END (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_START (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_END (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_START (6)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_standbywfi : 1;
        unsigned int ispa7_standbywfe : 1;
        unsigned int ispa7_smpnamp : 1;
        unsigned int ispa7_standbywfil2 : 1;
        unsigned int ispa7_dbgack : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_ISPA7_STAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_START (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_END (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_START (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_END (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_START (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_END (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_START (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_END (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_START (4)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivp_div_auto_reduce_bypass : 1;
        unsigned int ivp_auto_waitcfg_in : 10;
        unsigned int ivp_auto_waitcfg_out : 10;
        unsigned int ivp_div_auto_cfg : 6;
        unsigned int ivp_pwaitmode_bypass : 1;
        unsigned int ivp_dw_axi_m1_st_bypass : 1;
        unsigned int ivp_dw_axi_m2_st_bypass : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV0_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_END (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_START (29)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_div_auto_reduce_bypass : 1;
        unsigned int ispa7_auto_waitcfg_in : 10;
        unsigned int ispa7_auto_waitcfg_out : 10;
        unsigned int ispa7_div_auto_cfg : 6;
        unsigned int reserved : 5;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV1_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int venc_div_auto_reduce_bypass : 1;
        unsigned int venc_auto_waitcfg_in : 10;
        unsigned int venc_auto_waitcfg_out : 10;
        unsigned int venc_div_auto_cfg : 6;
        unsigned int venc_vcodecbus_cfg_bypass : 1;
        unsigned int reserved : 4;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV2_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vdec_div_auto_reduce_bypass : 1;
        unsigned int vdec_auto_waitcfg_in : 10;
        unsigned int vdec_auto_waitcfg_out : 10;
        unsigned int vdec_div_auto_cfg : 6;
        unsigned int vdec_vcodecbus_cfg_bypass : 1;
        unsigned int reserved : 4;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV3_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vivobus_div_auto_reduce_bypass : 1;
        unsigned int vivobus_auto_waitcfg_in : 10;
        unsigned int vivobus_auto_waitcfg_out : 9;
        unsigned int vivobus_ispa7_wfi_bypass : 1;
        unsigned int vivobus_div_auto_cfg : 6;
        unsigned int vivobus_vivo_cfg_bypass : 1;
        unsigned int vivobus_dss0_bypass : 1;
        unsigned int vivobus_dss1_bypass : 1;
        unsigned int vivobus_isp_bypass : 1;
        unsigned int vivobus_ispa7_bypass : 1;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV4_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_END (19)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_START (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_END (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_START (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_END (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_START (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_END (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_START (31)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vcodecbus_div_auto_reduce_bypass : 1;
        unsigned int vcodecbus_auto_waitcfg_in : 10;
        unsigned int vcodecbus_auto_waitcfg_out : 10;
        unsigned int vcodecbus_div_auto_cfg : 6;
        unsigned int vcodecbus_vcodec_cfg_bypass : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int vcodecbus_venc_bypass : 1;
        unsigned int vcodecbus_vdec_bypass : 1;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV5_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_START (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_END (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_START (31)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sysbus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int sysbus_auto_waitcfg_in : 10;
        unsigned int sysbus_auto_waitcfg_out : 10;
        unsigned int sysbus_div_auto_cfg : 6;
        unsigned int reserved : 5;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV6_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sysbus_aobus_bypass : 1;
        unsigned int sysbus_top_cssys_bypass : 1;
        unsigned int sysbus_perf_stat_bypass : 1;
        unsigned int sysbus_usb3_bypass : 1;
        unsigned int sysbus_secp_bypass : 1;
        unsigned int sysbus_secs_bypass : 1;
        unsigned int sysbus_socp_bypass : 1;
        unsigned int sysbus_dmac_mst_bypass : 1;
        unsigned int sysbus_emmc0_bypass : 1;
        unsigned int sysbus_emmc1_bypass : 1;
        unsigned int sysbus_mmc1bus_bypass : 1;
        unsigned int reserved_0 : 1;
        unsigned int sysbus_cci2sysbus_bypass : 1;
        unsigned int sysbus_modem_mst_bypass : 1;
        unsigned int reserved_1 : 1;
        unsigned int sysbus_djtag_mst_bypass : 1;
        unsigned int sysbus_lpm3_mst_bypass : 1;
        unsigned int sysbus_a72cfg_bypass : 1;
        unsigned int sysbus_ivp32_mst_bypass : 1;
        unsigned int sysbus_mmc0bus_sdio0_bypass : 1;
        unsigned int reserved_2 : 6;
        unsigned int cfgbus_vivo_cfg_bypass : 1;
        unsigned int cfgbus_vcodec_cfg_bypass : 1;
        unsigned int reserved_3 : 1;
        unsigned int cfgbus_djtag_mst_bypass : 1;
        unsigned int cfgbus_lpm3_mst_bypass : 1;
        unsigned int cfgbus_a7tocfg_bypass : 1;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV7_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_END (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_START (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_END (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_START (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_END (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_START (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_END (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_START (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_END (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_START (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_END (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_START (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_END (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_START (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_END (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_START (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_END (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_START (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_START (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_END (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_START (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_END (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_START (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_END (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_START (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_END (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_START (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_END (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_START (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_END (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_START (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_END (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_START (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_START (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_END (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_START (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_END (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_START (31)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfgbus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int cfgbus_auto_waitcfg_in : 10;
        unsigned int cfgbus_auto_waitcfg_out : 10;
        unsigned int cfgbus_div_auto_cfg : 6;
        unsigned int cfgbus_sysbus_relate_auto_reduce_bypass : 1;
        unsigned int reserved : 4;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV8_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmabus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int dmabus_auto_waitcfg_in : 10;
        unsigned int dmabus_auto_waitcfg_out : 10;
        unsigned int dmabus_div_auto_cfg : 6;
        unsigned int dmabus_dmac_mst_bypass : 1;
        unsigned int dmabus_sysbus_relate_auto_reduce_bypass : 1;
        unsigned int reserved : 3;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV9_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbgbus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int dbgbus_auto_waitcfg_in : 10;
        unsigned int dbgbus_auto_waitcfg_out : 8;
        unsigned int dbgbus_sysbus_relate_auto_reduce_bypass : 1;
        unsigned int dbgbus_div_auto_cfg : 6;
        unsigned int dbgbus_socp_bypass : 1;
        unsigned int dbgbus_secp_bypass : 1;
        unsigned int dbgbus_secs_bypass : 1;
        unsigned int dbgbus_usb3_bypass : 1;
        unsigned int dbgbus_perf_stat_bypass : 1;
        unsigned int dbgbus_top_cssys_bypass : 1;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV10_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_END (18)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_START (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_END (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_START (20)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_END (25)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_START (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_END (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_START (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_END (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_START (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_END (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_START (31)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emmc0bus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int emmc0bus_auto_waitcfg_in : 10;
        unsigned int emmc0bus_auto_waitcfg_out : 10;
        unsigned int emmc0bus_div_auto_cfg : 6;
        unsigned int emmc0bus_emm0_bypass : 1;
        unsigned int emmc0bus_emm1_bypass : 1;
        unsigned int emmc0bus_sdio_bypass : 1;
        unsigned int emmc0bus_sysbus_relate_auto_reduce_bypass : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV11_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_END (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_START (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_END (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_START (30)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emmc1bus_div_auto_reduce_bypass_lpm3 : 1;
        unsigned int emmc1bus_auto_waitcfg_in : 10;
        unsigned int emmc1bus_auto_waitcfg_out : 10;
        unsigned int emmc1bus_div_auto_cfg : 6;
        unsigned int emmc1bus_other_bypass : 1;
        unsigned int emmc1bus_sysbus_relate_auto_reduce_bypass : 1;
        unsigned int reserved : 3;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV12_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_END (26)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_START (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_END (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_START (28)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpmcu_div_auto_reduce_bypass : 1;
        unsigned int lpmcu_auto_waitcfg_in : 10;
        unsigned int lpmcu_auto_waitcfg_out : 10;
        unsigned int lpmcu_div_auto_cfg : 6;
        unsigned int reserved : 5;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV13_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_END (20)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_START (21)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_auto_swtotcxo_bypass : 1;
        unsigned int a57_auto_waitcfg_in : 10;
        unsigned int a57_auto_waitcfg_out : 10;
        unsigned int reserved : 11;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV14_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_auto_swtotcxo_bypass : 1;
        unsigned int a53_auto_waitcfg_in : 10;
        unsigned int a53_auto_waitcfg_out : 10;
        unsigned int reserved : 11;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV15_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_END (10)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_START (11)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emmc1bus_div_auto_reduce_bypass_acpu : 1;
        unsigned int emmc0bus_div_auto_reduce_bypass_acpu : 1;
        unsigned int dbgbus_div_auto_reduce_bypass_acpu : 1;
        unsigned int dmabus_div_auto_reduce_bypass_acpu : 1;
        unsigned int cfgbus_div_auto_reduce_bypass_acpu : 1;
        unsigned int sysbus_div_auto_reduce_bypass_acpu : 1;
        unsigned int reserved : 10;
        unsigned int autodivmasken : 16;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_END (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_START (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_END (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_START (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_END (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_START (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_END (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_START (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_END (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_START (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emmc1bus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int emmc0bus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int dbgbus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int dmabus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int cfgbus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int sysbus_div_auto_reduce_bypass_mcpu : 1;
        unsigned int reserved : 10;
        unsigned int autodivmasken : 16;
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_START (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_END (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_START (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_END (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_START (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_END (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_START (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_END (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_START (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_END (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_START (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_END (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_START (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_autodiv_ivp : 1;
        unsigned int gt_clk_autodiv_ispa7 : 1;
        unsigned int gt_clk_autodiv_venc : 1;
        unsigned int gt_clk_autodiv_vdec : 1;
        unsigned int gt_clk_autodiv_vivobus : 1;
        unsigned int gt_clk_autodiv_vcodecbus : 1;
        unsigned int gt_clk_autodiv_sysbus : 1;
        unsigned int gt_clk_autodiv_cfgbus : 1;
        unsigned int gt_clk_autodiv_dmabus : 1;
        unsigned int gt_clk_autodiv_dbgbus : 1;
        unsigned int gt_clk_autodiv_emmc0bus : 1;
        unsigned int gt_clk_autodiv_emmc1bus : 1;
        unsigned int gt_clk_autodiv_lpmcu : 1;
        unsigned int gt_clk_autodiv_a57 : 1;
        unsigned int gt_clk_autodiv_a53 : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_CRGPERIPH_PEREN6_UNION;
#endif
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_START (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_END (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_START (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_END (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_START (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_END (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_START (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_END (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_START (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_END (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_START (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_END (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_START (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_END (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_START (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_END (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_START (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_END (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_START (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_END (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_START (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_END (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_START (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_END (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_START (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_END (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_START (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_END (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_START (14)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_autodiv_ivp : 1;
        unsigned int gt_clk_autodiv_ispa7 : 1;
        unsigned int gt_clk_autodiv_venc : 1;
        unsigned int gt_clk_autodiv_vdec : 1;
        unsigned int gt_clk_autodiv_vivobus : 1;
        unsigned int gt_clk_autodiv_vcodecbus : 1;
        unsigned int gt_clk_autodiv_sysbus : 1;
        unsigned int gt_clk_autodiv_cfgbus : 1;
        unsigned int gt_clk_autodiv_dmabus : 1;
        unsigned int gt_clk_autodiv_dbgbus : 1;
        unsigned int gt_clk_autodiv_emmc0bus : 1;
        unsigned int gt_clk_autodiv_emmc1bus : 1;
        unsigned int gt_clk_autodiv_lpmcu : 1;
        unsigned int gt_clk_autodiv_a57 : 1;
        unsigned int gt_clk_autodiv_a53 : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_CRGPERIPH_PERDIS6_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_START (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_END (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_START (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_END (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_START (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_END (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_START (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_END (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_START (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_END (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_START (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_END (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_START (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_END (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_START (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_END (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_START (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_END (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_START (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_END (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_START (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_END (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_START (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_END (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_START (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_END (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_START (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_END (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_START (14)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_autodiv_ivp : 1;
        unsigned int gt_clk_autodiv_ispa7 : 1;
        unsigned int gt_clk_autodiv_venc : 1;
        unsigned int gt_clk_autodiv_vdec : 1;
        unsigned int gt_clk_autodiv_vivobus : 1;
        unsigned int gt_clk_autodiv_vcodecbus : 1;
        unsigned int gt_clk_autodiv_sysbus : 1;
        unsigned int gt_clk_autodiv_cfgbus : 1;
        unsigned int gt_clk_autodiv_dmabus : 1;
        unsigned int gt_clk_autodiv_dbgbus : 1;
        unsigned int gt_clk_autodiv_emmc0bus : 1;
        unsigned int gt_clk_autodiv_emmc1bus : 1;
        unsigned int gt_clk_autodiv_lpmcu : 1;
        unsigned int gt_clk_autodiv_a57 : 1;
        unsigned int gt_clk_autodiv_a53 : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_CRGPERIPH_PERCLKEN6_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_START (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_END (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_START (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_END (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_START (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_END (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_START (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_END (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_START (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_END (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_START (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_END (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_START (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_END (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_START (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_END (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_START (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_END (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_START (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_END (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_START (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_END (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_START (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_END (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_START (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_END (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_START (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_END (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_START (14)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_autodiv_ivp : 1;
        unsigned int gt_clk_autodiv_ispa7 : 1;
        unsigned int gt_clk_autodiv_venc : 1;
        unsigned int gt_clk_autodiv_vdec : 1;
        unsigned int gt_clk_autodiv_vivobus : 1;
        unsigned int gt_clk_autodiv_vcodecbus : 1;
        unsigned int gt_clk_autodiv_sysbus : 1;
        unsigned int gt_clk_autodiv_cfgbus : 1;
        unsigned int gt_clk_autodiv_dmabus : 1;
        unsigned int gt_clk_autodiv_dbgbus : 1;
        unsigned int gt_clk_autodiv_emmc0bus : 1;
        unsigned int gt_clk_autodiv_emmc1bus : 1;
        unsigned int gt_clk_autodiv_lpmcu : 1;
        unsigned int gt_clk_autodiv_a57 : 1;
        unsigned int gt_clk_autodiv_a53 : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_CRGPERIPH_PERSTAT6_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_START (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_END (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_START (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_END (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_START (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_END (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_START (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_END (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_START (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_END (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_START (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_END (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_START (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_END (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_START (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_END (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_START (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_END (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_START (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_END (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_START (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_END (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_START (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_END (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_START (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_END (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_START (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_END (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_START (14)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_rs0 : 1;
        unsigned int gt_clk_ddrphy_rs1 : 1;
        unsigned int gt_clk_ddrphy_rs2 : 1;
        unsigned int gt_clk_ddrphy_rs3 : 1;
        unsigned int gt_clk_ddrphy_gt : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_rsadd : 1;
        unsigned int reserved_1 : 25;
    } reg;
} SOC_CRGPERIPH_PEREN7_UNION;
#endif
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_START (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_END (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_START (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_END (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_START (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_END (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_START (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_END (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_START (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_END (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_START (6)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_rs0 : 1;
        unsigned int gt_clk_ddrphy_rs1 : 1;
        unsigned int gt_clk_ddrphy_rs2 : 1;
        unsigned int gt_clk_ddrphy_rs3 : 1;
        unsigned int gt_clk_ddrphy_gt : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_rsadd : 1;
        unsigned int reserved_1 : 25;
    } reg;
} SOC_CRGPERIPH_PERDIS7_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_START (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_END (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_START (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_END (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_START (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_END (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_START (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_END (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_START (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_END (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_START (6)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_rs0 : 1;
        unsigned int gt_clk_ddrphy_rs1 : 1;
        unsigned int gt_clk_ddrphy_rs2 : 1;
        unsigned int gt_clk_ddrphy_rs3 : 1;
        unsigned int gt_clk_ddrphy_gt : 1;
        unsigned int reserved_0 : 1;
        unsigned int gt_clk_ddrphy_rsadd : 1;
        unsigned int reserved_1 : 25;
    } reg;
} SOC_CRGPERIPH_PERCLKEN7_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_START (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_END (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_START (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_END (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_START (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_END (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_START (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_END (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_START (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_END (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_START (6)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gt_clk_ddrphy_rs0 : 1;
        unsigned int gt_clk_ddrphy_rs1 : 1;
        unsigned int gt_clk_ddrphy_rs2 : 1;
        unsigned int gt_clk_ddrphy_rs3 : 1;
        unsigned int gt_clk_ddrphy_gt : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_PERSTAT7_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_START (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_END (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_START (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_END (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_START (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_END (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_START (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_END (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_START (4)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ivp32dsp_subsys_crg : 1;
        unsigned int ip_rst_ivp32dsp_subsys : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_START (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_END (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_START (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ivp32dsp_subsys_crg : 1;
        unsigned int ip_rst_ivp32dsp_subsys : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_START (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_END (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_START (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_ivp32dsp_subsys_crg : 1;
        unsigned int ip_rst_ivp32dsp_subsys : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_START (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_END (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_START (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_isp : 1;
        unsigned int ip_arst_isp : 1;
        unsigned int ip_hrst_isp : 1;
        unsigned int ip_rst_ispa7cfg : 1;
        unsigned int ip_rst_ispa7 : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_START (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_END (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_START (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_END (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_START (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_END (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_START (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_END (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_START (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_isp : 1;
        unsigned int ip_arst_isp : 1;
        unsigned int ip_hrst_isp : 1;
        unsigned int ip_rst_ispa7cfg : 1;
        unsigned int ip_rst_ispa7 : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_START (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_END (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_START (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_END (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_START (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_END (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_START (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_END (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_START (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_isp : 1;
        unsigned int ip_arst_isp : 1;
        unsigned int ip_hrst_isp : 1;
        unsigned int ip_rst_ispa7cfg : 1;
        unsigned int ip_rst_ispa7 : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_START (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_END (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_START (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_END (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_START (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_END (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_START (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_END (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_START (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ispa7_cfgend : 1;
        unsigned int ispa7_vinithi : 1;
        unsigned int ispa7_dbgpwrdup : 1;
        unsigned int ispa7_l2rstdisable : 1;
        unsigned int ispa7_l1rstdisable : 1;
        unsigned int reserved_0 : 2;
        unsigned int ispa7_tsel_a7 : 4;
        unsigned int ispa7_remap_enable : 1;
        unsigned int ispa7_remap_offset : 18;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_CRGPERIPH_ISPA7_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_START (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_END (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_START (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_END (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_START (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_END (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_START (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_END (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_START (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_END (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_START (7)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_END (10)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_START (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_END (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_START (12)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_modem : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_START (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_modem : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_START (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_modem : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_START (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_rvbaraddr0 : 32;
    } reg;
} SOC_CRGPERIPH_A53_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_START (0)
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_rvbaraddr1 : 32;
    } reg;
} SOC_CRGPERIPH_A53_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_START (0)
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_rvbaraddr2 : 32;
    } reg;
} SOC_CRGPERIPH_A53_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_START (0)
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a53_rvbaraddr3 : 32;
    } reg;
} SOC_CRGPERIPH_A53_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_START (0)
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_rvbaraddr0 : 32;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_rvbaraddr1 : 32;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_rvbaraddr2 : 32;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a57_rvbaraddr3 : 32;
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_START (0)
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_secs : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_START (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_secs : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_START (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ip_rst_secs : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_START (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
