#ifndef __SOC_DSS_DBUF_INTERFACE_H__
#define __SOC_DSS_DBUF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_DBUF_FRM_SIZE_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_DBUF_FRM_HSIZE_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_DBUF_SRAM_VALID_NUM_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_DBUF_WBE_EN_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_DBUF_THD_FILL_LEV0_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_DBUF_DFS_FILL_LEV1_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_DBUF_THD_RQOS_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_DBUF_THD_WQOS_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_DBUF_THD_CG_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_DBUF_THD_OTHER_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_DBUF_FILL_LEV0_CNT_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_DBUF_FILL_LEV1_CNT_ADDR(base) ((base) + (0x002C))
#define SOC_DSS_DBUF_FILL_LEV2_CNT_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_DBUF_FILL_LEV3_CNT_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_DBUF_FILL_LEV4_CNT_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_DBUF_WB_FILL_LEVEL_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_DBUF_DFS_STATUS_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_DBUF_DFS_LP_CTRL_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_ADDR(base) ((base) + (0x0054))
#define SOC_DSS_DBUF_DBUF_CLK_SEL_ADDR(base) ((base) + (0x005C))
#define SOC_DSS_DBUF_DBUF_CLK_EN_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_DBUF_DBG_CPU_EN_ADDR(base) ((base) + (0x0070))
#define SOC_DSS_DBUF_DBG_CPU_START_ADDR(base) ((base) + (0x0074))
#define SOC_DSS_DBUF_DBG_CPU_CTL_ADDR(base) ((base) + (0x0078))
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_ADDR(base) ((base) + (0x008C))
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_ADDR(base) ((base) + (0x0090))
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_ADDR(base) ((base) + (0x0094))
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_ADDR(base) ((base) + (0x0098))
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_ADDR(base) ((base) + (0x009C))
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_ADDR(base) ((base) + (0x00A0))
#define SOC_DSS_DBUF_REG_DEFAULT_ADDR(base) ((base) + (0x00A4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_size : 27;
        unsigned int reserved : 5;
    } reg;
} SOC_DSS_DBUF_FRM_SIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_START (0)
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_hsize : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DBUF_FRM_HSIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_START (0)
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_valid_num : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DBUF_SRAM_VALID_NUM_UNION;
#endif
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_START (0)
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wbe_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUF_WBE_EN_UNION;
#endif
#define SOC_DSS_DBUF_WBE_EN_wbe_en_START (0)
#define SOC_DSS_DBUF_WBE_EN_wbe_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_fill_lev1 : 14;
        unsigned int reserved_0 : 2;
        unsigned int thd_fill_lev2 : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_DSS_DBUF_THD_FILL_LEV0_UNION;
#endif
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_START (0)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_END (13)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_START (16)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_fill_lev3 : 14;
        unsigned int reserved_0 : 2;
        unsigned int thd_fill_lev4 : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_DSS_DBUF_DFS_FILL_LEV1_UNION;
#endif
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_START (0)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_END (13)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_START (16)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_rqos_in : 14;
        unsigned int reserved_0 : 2;
        unsigned int thd_rqos_out : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_DSS_DBUF_THD_RQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_START (0)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_END (13)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_START (16)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_wqos_in : 14;
        unsigned int reserved_0 : 2;
        unsigned int thd_wqos_out : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_DSS_DBUF_THD_WQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_START (0)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_END (13)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_START (16)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_cg_in : 14;
        unsigned int reserved_0 : 2;
        unsigned int thd_cg_out : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_DSS_DBUF_THD_CG_UNION;
#endif
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_START (0)
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_END (13)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_START (16)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thd_wr_wait : 14;
        unsigned int reserved_0 : 2;
        unsigned int dfs_cg_hold : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DBUF_THD_OTHER_UNION;
#endif
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_START (0)
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_END (13)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_START (16)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fill_lev0_cnt : 32;
    } reg;
} SOC_DSS_DBUF_FILL_LEV0_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_START (0)
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fill_lev1_cnt : 32;
    } reg;
} SOC_DSS_DBUF_FILL_LEV1_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_START (0)
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fill_lev2_cnt : 32;
    } reg;
} SOC_DSS_DBUF_FILL_LEV2_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_START (0)
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fill_lev3_cnt : 32;
    } reg;
} SOC_DSS_DBUF_FILL_LEV3_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_START (0)
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fill_lev4_cnt : 32;
    } reg;
} SOC_DSS_DBUF_FILL_LEV4_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_START (0)
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int online_fill_lev : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_START (0)
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wb_fill_lev : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DBUF_WB_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_START (0)
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int online_empty : 1;
        unsigned int online_full : 1;
        unsigned int offline_empty : 1;
        unsigned int offline_full : 1;
        unsigned int dfs_cg : 1;
        unsigned int dfs_wqos : 1;
        unsigned int dfs_rqos : 1;
        unsigned int dfs_wb_error : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DBUF_DFS_STATUS_UNION;
#endif
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_START (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_END (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_START (1)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_END (1)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_START (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_END (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_START (3)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_END (3)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_START (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_END (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_START (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_END (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_START (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_END (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_START (7)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_upon_frm_end : 1;
        unsigned int ret_aft_prefetch : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DBUF_DFS_LP_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_START (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_END (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_START (1)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_START (0)
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_START (0)
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf_clk_sel : 32;
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_START (0)
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf_clk_en : 32;
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_START (0)
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_ctl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_START (0)
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_START_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_START (0)
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_addr : 13;
        unsigned int reserved_0: 3;
        unsigned int cpu_we : 1;
        unsigned int reserved_1: 15;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_CTL_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_START (0)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_END (12)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_START (16)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_rdata0 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_START (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_rdata1 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_START (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_rdata2 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_START (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_rdata3 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_START (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_rdata4 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_START (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wdata0 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_START (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wdata1 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_START (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wdata2 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_START (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wdata3 : 32;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_START (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wdata4 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_START (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
