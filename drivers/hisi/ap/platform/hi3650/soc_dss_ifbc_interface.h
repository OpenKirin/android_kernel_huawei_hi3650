#ifndef __SOC_DSS_IFBC_INTERFACE_H__
#define __SOC_DSS_IFBC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_IFBC_IFBC_SIZE_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_IFBC_IFBC_CTRL_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_IFBC_IFBC_EN_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_IFBC_IFBC_INSERT_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_IFBC_IFBC_CORE_GT_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ADDR(base) ((base) + (0x002C))
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_IFBC_ORISE_CTL_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_IFBC_ORSISE_DEBUG0_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_IFBC_ORSISE_DEBUG1_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_IFBC_rsp_comp_test_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ADDR(base) ((base) + (0x044))
#define SOC_DSS_IFBC_IFBC_CLK_EN_ADDR(base) ((base) + (0x048))
#define SOC_DSS_IFBC_IFBC_PAD_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_IFBC_REG_DEFAULT_ADDR(base) ((base) + (0x0050))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_size_vrt : 16;
        unsigned int ifbc_size_hrz : 16;
    } reg;
} SOC_DSS_IFBC_IFBC_SIZE_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_START (0)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_END (15)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_START (16)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int comp_mode : 3;
        unsigned int ifbc_out_mode : 1;
        unsigned int cmp_dat_rev0 : 1;
        unsigned int cmp_dat_rev1 : 1;
        unsigned int auto_sel : 1;
        unsigned int dpk_mode_sel : 3;
        unsigned int dup_mode_sel : 3;
        unsigned int porch_num : 8;
        unsigned int reserved : 11;
    } reg;
} SOC_DSS_IFBC_IFBC_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_START (0)
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_END (2)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_START (3)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_END (3)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_START (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_END (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_START (5)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_END (5)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_START (6)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_END (6)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_START (7)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_END (9)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_START (10)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_END (12)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_START (13)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_hm_lut0 : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_START (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_hm_lut1 : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_START (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_hm_lut2 : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_START (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_hm_lut3 : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_START (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_en : 1;
        unsigned int ifbc_out_sel : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_IFBC_IFBC_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_START (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_END (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_START (1)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_mem_ctrl_0 : 4;
        unsigned int ifbc_mem_ctrl_1 : 4;
        unsigned int ifbc_mem_ctrl_2 : 4;
        unsigned int ifbc_mem_ctrl_3 : 4;
        unsigned int ifbc_mem_ctrl_4 : 4;
        unsigned int ifbc_mem_ctrl_5 : 4;
        unsigned int ifbc_mem_ctrl_6 : 4;
        unsigned int ifbc_mem_ctrl_7 : 4;
    } reg;
} SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_START (0)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_END (3)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_START (4)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_END (7)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_START (8)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_END (11)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_START (12)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_END (15)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_START (16)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_END (19)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_START (20)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_END (23)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_START (24)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_END (27)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_START (28)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int insert_byte_num : 16;
        unsigned int insert_byte : 16;
    } reg;
} SOC_DSS_IFBC_IFBC_INSERT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_START (0)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_END (15)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_START (16)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_pat_ext_mode : 1;
        unsigned int force_pat_mode : 1;
        unsigned int force_yuv_mode : 1;
        unsigned int mcmp_pat_ext_en : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION;
#endif
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_START (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_END (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_START (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_END (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_START (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_END (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_START (3)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_core_1_gt : 2;
        unsigned int ifbc_core_2_gt : 2;
        unsigned int ifbc_core_2_gt_h : 2;
        unsigned int ifbc_core_2_gt_o : 2;
        unsigned int ifbc_core_2_gt_n : 2;
        unsigned int ifbc_core_4_gt : 2;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_IFBC_IFBC_CORE_GT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_START (0)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_END (1)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_START (2)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_END (3)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_START (4)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_END (5)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_START (6)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_END (7)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_START (8)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_END (9)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_START (10)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_pm_ctrl : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_PM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_START (0)
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_START (0)
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int i_param_value : 8;
        unsigned int i_param_addr : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_IFBC_ORISE_CTL_UNION;
#endif
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_START (0)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_END (7)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_START (8)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int orise_debug_l : 32;
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG0_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_START (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int orise_debug_h : 32;
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG1_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_START (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rsp_comp_test : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_IFBC_rsp_comp_test_UNION;
#endif
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_START (0)
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_clk_sel : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_SEL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_START (0)
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ifbc_clk_en : 32;
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_START (0)
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int num_pad : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_IFBC_IFBC_PAD_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_START (0)
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_IFBC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
