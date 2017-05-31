#ifndef __SOC_DSS_DPP_INTERFACE_H__
#define __SOC_DSS_DPP_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_ADDR(base) ((base) + (0x000))
#define SOC_DSS_DPP_DPP_ID_ADDR(base) ((base) + (0x004))
#define SOC_DSS_DPP_DPP_IMG_HRZ_ADDR(base) ((base) + (0x008))
#define SOC_DSS_DPP_DPP_IMG_VRT_ADDR(base) ((base) + (0x00C))
#define SOC_DSS_DPP_CLRBAR_CTRL_ADDR(base) ((base) + (0x010))
#define SOC_DSS_DPP_DITHER_ADDR(base) ((base) + (0x014))
#define SOC_DSS_DPP_SBL_ADDR(base) ((base) + (0x018))
#define SOC_DSS_DPP_DPP_CLK_SEL_ADDR(base) ((base) + (0x01C))
#define SOC_DSS_DPP_DPP_CLK_EN_ADDR(base) ((base) + (0x020))
#define SOC_DSS_DPP_DPP_DBG_CNT_ADDR(base) ((base) + (0x024))
#define SOC_DSS_DPP_LCP_XCC_COEF_00_ADDR(base) ((base) + (0x100))
#define SOC_DSS_DPP_LCP_XCC_COEF_01_ADDR(base) ((base) + (0x104))
#define SOC_DSS_DPP_LCP_XCC_COEF_02_ADDR(base) ((base) + (0x108))
#define SOC_DSS_DPP_LCP_XCC_COEF_03_ADDR(base) ((base) + (0x10C))
#define SOC_DSS_DPP_LCP_XCC_COEF_10_ADDR(base) ((base) + (0x110))
#define SOC_DSS_DPP_LCP_XCC_COEF_11_ADDR(base) ((base) + (0x114))
#define SOC_DSS_DPP_LCP_XCC_COEF_12_ADDR(base) ((base) + (0x118))
#define SOC_DSS_DPP_LCP_XCC_COEF_13_ADDR(base) ((base) + (0x11C))
#define SOC_DSS_DPP_LCP_XCC_COEF_20_ADDR(base) ((base) + (0x120))
#define SOC_DSS_DPP_LCP_XCC_COEF_21_ADDR(base) ((base) + (0x124))
#define SOC_DSS_DPP_LCP_XCC_COEF_22_ADDR(base) ((base) + (0x128))
#define SOC_DSS_DPP_LCP_XCC_COEF_23_ADDR(base) ((base) + (0x12C))
#define SOC_DSS_DPP_GMP_BYPASS_EN_ADDR(base) ((base) + (0x130))
#define SOC_DSS_DPP_XCC_BYPASS_EN_ADDR(base) ((base) + (0x134))
#define SOC_DSS_DPP_IGM_MEM_CTRL_ADDR(base) ((base) + (0x138))
#define SOC_DSS_DPP_GMP_MEM_CTRL_ADDR(base) ((base) + (0x13C))
#define SOC_DSS_DPP_R0_H_ADDR(base) ((base) + (0x200))
#define SOC_DSS_DPP_R1_H_ADDR(base) ((base) + (0x204))
#define SOC_DSS_DPP_R2_H_ADDR(base) ((base) + (0x208))
#define SOC_DSS_DPP_R3_H_ADDR(base) ((base) + (0x20C))
#define SOC_DSS_DPP_R4_H_ADDR(base) ((base) + (0x210))
#define SOC_DSS_DPP_R5_H_ADDR(base) ((base) + (0x214))
#define SOC_DSS_DPP_R6_H_ADDR(base) ((base) + (0x218))
#define SOC_DSS_DPP_ACM_EN_ADDR(base) ((base) + (0x21C))
#define SOC_DSS_DPP_ACM_MEM_CTRL_ADDR(base) ((base) + (0x220))
#define SOC_DSS_DPP_CE_HIST_RESET_ADDR(base) ((base) + (0x230))
#define SOC_DSS_DPP_CE_HIST_CTL_ADDR(base) ((base) + (0x234))
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ADDR(base) ((base) + (0x238))
#define SOC_DSS_DPP_CE_SIZE_ADDR(base) ((base) + (0x23C))
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ADDR(base) ((base) + (0x240))
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ADDR(base) ((base) + (0x244))
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ADDR(base) ((base) + (0x248))
#define SOC_DSS_DPP_CE_LUT_SEL_ADDR(base) ((base) + (0x24C))
#define SOC_DSS_DPP_CE_LUT_ENABLE_ADDR(base) ((base) + (0x250))
#define SOC_DSS_DPP_CE_LUT_USING_IND_ADDR(base) ((base) + (0x254))
#define SOC_DSS_DPP_CE_STATE_IND_ADDR(base) ((base) + (0x258))
#define SOC_DSS_DPP_CE_MEM_CTRL_ADDR(base) ((base) + (0x25C))
#define SOC_DSS_DPP_CE_TOTALGRAY_ADDR(base) ((base) + (0x264))
#define SOC_DSS_DPP_CE_TOTALPIXL_ADDR(base) ((base) + (0x268))
#define SOC_DSS_DPP_CE_MEAN_ADDR(base) ((base) + (0x26C))
#define SOC_DSS_DPP_CE_PEC0_3_ADDR(base) ((base) + (0x270))
#define SOC_DSS_DPP_CE_PEC4_7_ADDR(base) ((base) + (0x274))
#define SOC_DSS_DPP_CE_PEC8_ADDR(base) ((base) + (0x278))
#define SOC_DSS_DPP_CE_BLACK_NUM_ADDR(base) ((base) + (0x27C))
#define SOC_DSS_DPP_CE_WHITE_NUM_ADDR(base) ((base) + (0x280))
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ADDR(base) ((base) + (0x284))
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_ADDR(base) ((base) + (0x300))
#define SOC_DSS_DPP_GAMA_BYPASS_EN_ADDR(base) ((base) + (0x304))
#define SOC_DSS_DPP_GAMA_MEM_CTRL_ADDR(base) ((base) + (0x308))
#define SOC_DSS_DPP_REG_DEFAULT_ADDR(base) ((base) + (0x030C))
#define SOC_DSS_DPP_SBL_MEM_CTRL_ADDR(base) ((base) + (0x310))
#define SOC_DSS_DPP_DPP_DBG_ADDR(base) ((base) + (0x314))
#define SOC_DSS_DPP_U_GAMA_COEF_ADDR(base) ((base) + (0x0400))
#define SOC_DSS_DPP_U_H_COEF_ADDR(base) ((base) + (0x1000))
#define SOC_DSS_DPP_U_SATA_COEF_ADDR(base) ((base) + (0x1A00))
#define SOC_DSS_DPP_U_SATR_COEF_ADDR(base) ((base) + (0x1C00))
#define SOC_DSS_DPP_CE_HIST_RPT0_ADDR(base) ((base) + (0x2000бл0x23FF))
#define SOC_DSS_DPP_CE_HIST_RPT1_ADDR(base) ((base) + (0x2400бл0x27FF))
#define SOC_DSS_DPP_CE_LUT0_ADDR(base) ((base) + (0x2800))
#define SOC_DSS_DPP_CE_LUT1_ADDR(base) ((base) + (0x2C00))
#define SOC_DSS_DPP_U_GMP_COEF_ADDR(base) ((base) + (0x3000бл0x7CCF))
#define SOC_DSS_DPP_U_IGM_R_COEF_ADDR(base) ((base) + (0xB000))
#define SOC_DSS_DPP_U_IGM_G_COEF_ADDR(base) ((base) + (0xB400))
#define SOC_DSS_DPP_U_IGM_B_COEF_ADDR(base) ((base) + (0xB800))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_START (0)
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp0_id : 32;
    } reg;
} SOC_DSS_DPP_DPP_ID_UNION;
#endif
#define SOC_DSS_DPP_DPP_ID_dpp0_id_START (0)
#define SOC_DSS_DPP_DPP_ID_dpp0_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp0_size_hrz : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DPP_DPP_IMG_HRZ_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_START (0)
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp0_size_vrz : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DPP_DPP_IMG_VRT_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_START (0)
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clrbar_en : 1;
        unsigned int clrbar_mode : 1;
        unsigned int reserved : 22;
        unsigned int clrbar_width : 8;
    } reg;
} SOC_DSS_DPP_CLRBAR_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_START (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_END (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_START (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_END (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_START (24)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dither_en : 1;
        unsigned int dither_fmt : 1;
        unsigned int dither_sel : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_DPP_DITHER_UNION;
#endif
#define SOC_DSS_DPP_DITHER_dither_en_START (0)
#define SOC_DSS_DPP_DITHER_dither_en_END (0)
#define SOC_DSS_DPP_DITHER_dither_fmt_START (1)
#define SOC_DSS_DPP_DITHER_dither_fmt_END (1)
#define SOC_DSS_DPP_DITHER_dither_sel_START (2)
#define SOC_DSS_DPP_DITHER_dither_sel_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sbl_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_SBL_UNION;
#endif
#define SOC_DSS_DPP_SBL_sbl_en_START (0)
#define SOC_DSS_DPP_SBL_sbl_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_clk_sel : 32;
    } reg;
} SOC_DSS_DPP_DPP_CLK_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_START (0)
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_clk_en : 32;
    } reg;
} SOC_DSS_DPP_DPP_CLK_EN_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_START (0)
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_h_cnt : 13;
        unsigned int reserved_0: 3;
        unsigned int dpp_v_cnt : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_DSS_DPP_DPP_DBG_CNT_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_START (0)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_END (12)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_START (16)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_00 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_00_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_01 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_01_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_02 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_02_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_03 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_03_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_10 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_10_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_11 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_11_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_12 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_12_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_13 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_13_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_20 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_20_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_21 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_21_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_22 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_22_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coef_23 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_23_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_START (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gmp_bypass_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_GMP_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_START (0)
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xcc_bypass_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_XCC_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_START (0)
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int igm_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DPP_IGM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_START (0)
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gmp_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DPP_GMP_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_START (0)
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r0_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r0_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R0_H_UNION;
#endif
#define SOC_DSS_DPP_R0_H_r0_lh_START (0)
#define SOC_DSS_DPP_R0_H_r0_lh_END (9)
#define SOC_DSS_DPP_R0_H_r0_hh_START (16)
#define SOC_DSS_DPP_R0_H_r0_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r1_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r1_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R1_H_UNION;
#endif
#define SOC_DSS_DPP_R1_H_r1_lh_START (0)
#define SOC_DSS_DPP_R1_H_r1_lh_END (9)
#define SOC_DSS_DPP_R1_H_r1_hh_START (16)
#define SOC_DSS_DPP_R1_H_r1_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r2_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r2_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R2_H_UNION;
#endif
#define SOC_DSS_DPP_R2_H_r2_lh_START (0)
#define SOC_DSS_DPP_R2_H_r2_lh_END (9)
#define SOC_DSS_DPP_R2_H_r2_hh_START (16)
#define SOC_DSS_DPP_R2_H_r2_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r3_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r3_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R3_H_UNION;
#endif
#define SOC_DSS_DPP_R3_H_r3_lh_START (0)
#define SOC_DSS_DPP_R3_H_r3_lh_END (9)
#define SOC_DSS_DPP_R3_H_r3_hh_START (16)
#define SOC_DSS_DPP_R3_H_r3_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r4_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r4_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R4_H_UNION;
#endif
#define SOC_DSS_DPP_R4_H_r4_lh_START (0)
#define SOC_DSS_DPP_R4_H_r4_lh_END (9)
#define SOC_DSS_DPP_R4_H_r4_hh_START (16)
#define SOC_DSS_DPP_R4_H_r4_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r5_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r5_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R5_H_UNION;
#endif
#define SOC_DSS_DPP_R5_H_r5_lh_START (0)
#define SOC_DSS_DPP_R5_H_r5_lh_END (9)
#define SOC_DSS_DPP_R5_H_r5_hh_START (16)
#define SOC_DSS_DPP_R5_H_r5_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r6_lh : 10;
        unsigned int reserved_0: 6;
        unsigned int r6_hh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_R6_H_UNION;
#endif
#define SOC_DSS_DPP_R6_H_r6_lh_START (0)
#define SOC_DSS_DPP_R6_H_r6_lh_END (9)
#define SOC_DSS_DPP_R6_H_r6_hh_START (16)
#define SOC_DSS_DPP_R6_H_r6_hh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acm_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int acm_valid_num : 3;
        unsigned int reserved_1 : 25;
    } reg;
} SOC_DSS_DPP_ACM_EN_UNION;
#endif
#define SOC_DSS_DPP_ACM_EN_acm_en_START (0)
#define SOC_DSS_DPP_ACM_EN_acm_en_END (0)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_START (4)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acm_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DPP_ACM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_START (0)
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_CE_HIST_RESET_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_START (0)
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_ctl : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_DPP_CE_HIST_CTL_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_START (0)
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_frame_cnt : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_START (0)
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_height : 13;
        unsigned int reserved_0: 3;
        unsigned int ce_width : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_DSS_DPP_CE_SIZE_UNION;
#endif
#define SOC_DSS_DPP_CE_SIZE_ce_height_START (0)
#define SOC_DSS_DPP_CE_SIZE_ce_height_END (12)
#define SOC_DSS_DPP_CE_SIZE_ce_width_START (16)
#define SOC_DSS_DPP_CE_SIZE_ce_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_no_stat_lines : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_NO_STAT_LINES_UNION;
#endif
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_START (0)
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_black_region_thre : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_START (0)
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_white_region_thre : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_START (0)
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_CE_LUT_SEL_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_START (0)
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut_enable : 1;
        unsigned int ce_hist_enable : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DPP_CE_LUT_ENABLE_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_START (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_END (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_START (1)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut_using_ind : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_CE_LUT_USING_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_START (0)
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_state_ind : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_CE_STATE_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_START (0)
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut_mem_ctrl : 4;
        unsigned int ce_his_mem_ctrl : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_START (0)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_END (3)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_START (4)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_totalgray : 32;
    } reg;
} SOC_DSS_DPP_CE_TOTALGRAY_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_START (0)
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_totalpixl : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DPP_CE_TOTALPIXL_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_START (0)
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_mean : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_MEAN_UNION;
#endif
#define SOC_DSS_DPP_CE_MEAN_ce_mean_START (0)
#define SOC_DSS_DPP_CE_MEAN_ce_mean_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_pec0 : 8;
        unsigned int ce_pec1 : 8;
        unsigned int ce_pec2 : 8;
        unsigned int ce_pec3 : 8;
    } reg;
} SOC_DSS_DPP_CE_PEC0_3_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_START (0)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_END (7)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_START (8)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_END (15)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_START (16)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_END (23)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_START (24)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_pec4 : 8;
        unsigned int ce_pec5 : 8;
        unsigned int ce_pec6 : 8;
        unsigned int ce_pec7 : 8;
    } reg;
} SOC_DSS_DPP_CE_PEC4_7_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_START (0)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_END (7)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_START (8)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_END (15)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_START (16)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_END (23)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_START (24)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_pec8 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_CE_PEC8_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_START (0)
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_black_num : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DPP_CE_BLACK_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_START (0)
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_white_num : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DPP_CE_WHITE_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_START (0)
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_rpt_ind : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_START (0)
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shortbit_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_START (0)
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_GAMA_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_START (0)
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gama_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DPP_GAMA_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_START (0)
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DPP_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sbl_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DPP_SBL_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_START (0)
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_dbg : 32;
    } reg;
} SOC_DSS_DPP_DPP_DBG_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_START (0)
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_gama_coef : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DPP_U_GAMA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_START (0)
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int h_l_out : 10;
        unsigned int reserved_0: 6;
        unsigned int h_r_out : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_DSS_DPP_U_H_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_H_COEF_h_l_out_START (0)
#define SOC_DSS_DPP_U_H_COEF_h_l_out_END (9)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_START (16)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sata_l_out : 8;
        unsigned int sata_r_out : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DPP_U_SATA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_START (0)
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_END (7)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_START (8)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int satr_l_out : 8;
        unsigned int satr_r_out : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DPP_U_SATR_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_START (0)
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_END (7)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_START (8)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_rpt0 : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT0_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_START (0)
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_hist_rpt1 : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT1_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_START (0)
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut0 : 8;
        unsigned int reserved: 24;
    } reg;
} SOC_DSS_DPP_CE_LUT0_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_START (0)
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ce_lut1 : 8;
        unsigned int reserved: 24;
    } reg;
} SOC_DSS_DPP_CE_LUT1_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_START (0)
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_gmp_coef : 32;
    } reg;
} SOC_DSS_DPP_U_GMP_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_START (0)
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_igm_r_coef : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DPP_U_IGM_R_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_START (0)
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_igm_g_coef : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DPP_U_IGM_G_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_START (0)
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_igm_b_coef : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DPP_U_IGM_B_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_START (0)
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_END (11)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
