#ifndef __SOC_DSS_CMD_INTERFACE_H__
#define __SOC_DSS_CMD_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ADDR(base,i) ((base) + (0x0000+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ADDR(base,i) ((base) + (0x0004+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ADDR(base,i) ((base) + (0x0008+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ADDR(base,i) ((base) + (0x000C+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ADDR(base,i) ((base) + (0x0010+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ADDR(base,i) ((base) + (0x0014+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ADDR(base,i) ((base) + (0x0018+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ADDR(base,i) ((base) + (0x001C+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ADDR(base,i) ((base) + (0x0024+0x40*(i)))
#define SOC_DSS_CMD_CMDLIST_CH_DBG_ADDR(base,i) ((base) + (0x0028+0x40*(i)))
#define SOC_DSS_CMD_BUF_DBG_EN_ADDR(base) ((base) + (0x03F0))
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_ADDR(base) ((base) + (0x03F4))
#define SOC_DSS_CMD_BUF_DBG_CNT_ADDR(base) ((base) + (0x03F8))
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_ADDR(base) ((base) + (0x03FC))
#define SOC_DSS_CMD_CMDLIST_START_ADDR(base) ((base) + (0x0400))
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_ADDR(base) ((base) + (0x03E8))
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_ADDR(base) ((base) + (0x03EC))
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_ADDR(base) ((base) + (0x0404))
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_ADDR(base) ((base) + (0x0408))
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_ADDR(base) ((base) + (0x040C))
#define SOC_DSS_CMD_CMDLIST_CTRL_ADDR(base) ((base) + (0x0410))
#define SOC_DSS_CMD_CMDLIST_SECU_ADDR(base) ((base) + (0x0414))
#define SOC_DSS_CMD_CMDLIST_INTS_ADDR(base) ((base) + (0x0418))
#define SOC_DSS_CMD_CMDLIST_SWRST_ADDR(base) ((base) + (0x041C))
#define SOC_DSS_CMD_CMD_MEM_CTRL_ADDR(base) ((base) + (0x0420))
#define SOC_DSS_CMD_CMD_CLK_SEL_ADDR(base) ((base) + (0x0428))
#define SOC_DSS_CMD_CMD_CLK_EN_ADDR(base) ((base) + (0x042C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_pending_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_PENDING_CLR_ch_pending_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_enable : 1;
        unsigned int ch_auto_single : 1;
        unsigned int ch_start_sel : 1;
        unsigned int ch_pause : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_enable_END (0)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_START (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_auto_single_END (1)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_START (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_start_sel_END (2)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_START (3)
#define SOC_DSS_CMD_CMDLIST_CH_CTRL_ch_pause_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_ctl_fsm : 4;
        unsigned int ch_items_fsm : 4;
        unsigned int ch_dma_fsm : 2;
        unsigned int ch_idle : 1;
        unsigned int oa_idle : 1;
        unsigned int ch_cmd_done_id : 10;
        unsigned int ch_cmd_id : 10;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_ctl_fsm_END (3)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_items_fsm_END (7)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_START (8)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_dma_fsm_END (9)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_START (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_idle_END (10)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_START (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_oa_idle_END (11)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_START (12)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_done_id_END (21)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_START (22)
#define SOC_DSS_CMD_CMDLIST_CH_STATUS_ch_cmd_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int ch_start_addr : 28;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_STAAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_STAAD_ch_start_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int ch_curr_addr : 28;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_CURAD_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_CURAD_ch_curr_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_onedone_inte : 1;
        unsigned int ch_alldone_inte : 1;
        unsigned int ch_axi_err_inte : 1;
        unsigned int ch_pending_inte : 1;
        unsigned int ch_start_inte : 1;
        unsigned int ch_badcmd_inte : 1;
        unsigned int ch_timeout_inte : 1;
        unsigned int ch_taskdone_inte : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_onedone_inte_END (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_START (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_alldone_inte_END (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_START (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_axi_err_inte_END (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_START (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_pending_inte_END (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_start_inte_END (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_START (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_badcmd_inte_END (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_START (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_timeout_inte_END (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_START (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTE_ch_taskdone_inte_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_onedone_intc : 1;
        unsigned int ch_alldone_intc : 1;
        unsigned int ch_axi_err_intc : 1;
        unsigned int ch_pending_intc : 1;
        unsigned int ch_start_intc : 1;
        unsigned int ch_badcmd_intc : 1;
        unsigned int ch_timeout_intc : 1;
        unsigned int ch_taskdone_intc : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTC_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_onedone_intc_END (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_START (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_alldone_intc_END (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_START (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_axi_err_intc_END (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_START (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_pending_intc_END (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_start_intc_END (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_START (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_badcmd_intc_END (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_START (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_timeout_intc_END (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_START (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTC_ch_taskdone_intc_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_onedone_ints : 1;
        unsigned int ch_alldone_ints : 1;
        unsigned int ch_axi_err_ints : 1;
        unsigned int ch_pending_ints : 1;
        unsigned int ch_start_ints : 1;
        unsigned int ch_badcmd_ints : 1;
        unsigned int ch_timeout_ints : 1;
        unsigned int ch_taskdone_ints : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_onedone_ints_END (0)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_START (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_alldone_ints_END (1)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_START (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_axi_err_ints_END (2)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_START (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_pending_ints_END (3)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_start_ints_END (4)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_START (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_badcmd_ints_END (5)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_START (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_timeout_ints_END (6)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_START (7)
#define SOC_DSS_CMD_CMDLIST_CH_INTS_ch_taskdone_ints_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_perf_cnt : 32;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_PERF_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_PERF_ch_perf_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_dbg0 : 1;
        unsigned int cmd_dbg1 : 1;
        unsigned int cmd_dbg2 : 1;
        unsigned int cmd_dbg3 : 1;
        unsigned int cmd_dbg4 : 1;
        unsigned int cmd_dbg5 : 1;
        unsigned int cmd_dbg6 : 1;
        unsigned int cmd_dbg7 : 1;
        unsigned int cmd_dbg8 : 1;
        unsigned int cmd_dbg9 : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_CMD_CMDLIST_CH_DBG_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_START (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg0_END (0)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_START (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg1_END (1)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_START (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg2_END (2)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_START (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg3_END (3)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_START (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg4_END (4)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_START (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg5_END (5)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_START (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg6_END (6)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_START (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg7_END (7)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_START (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg8_END (8)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_START (9)
#define SOC_DSS_CMD_CMDLIST_CH_DBG_cmd_dbg9_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buf_dbg_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_CMD_BUF_DBG_EN_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_START (0)
#define SOC_DSS_CMD_BUF_DBG_EN_buf_dbg_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buf_dbg_cnt_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_CLR_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_START (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_CLR_buf_dbg_cnt_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buf_dbg_cnt_th : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_CMD_BUF_DBG_CNT_UNION;
#endif
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_START (0)
#define SOC_DSS_CMD_BUF_DBG_CNT_buf_dbg_cnt_th_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeout_th : 32;
    } reg;
} SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_START (0)
#define SOC_DSS_CMD_CMDLIST_TIMEOUT_TH_timeout_th_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_START_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_START_start_START (0)
#define SOC_DSS_CMD_CMDLIST_START_start_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_mask_status : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_START (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_STATUS_addr_mask_status_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_mask_dis : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_START (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_DIS_addr_mask_dis_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_mask_en : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_START (0)
#define SOC_DSS_CMD_CMDLIST_ADDR_MASK_EN_addr_mask_en_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int task_continue : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_START (0)
#define SOC_DSS_CMD_CMDLIST_TASK_CONTINUE_task_continue_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int task_status : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_TASK_STATUS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_START (0)
#define SOC_DSS_CMD_CMDLIST_TASK_STATUS_task_status_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_mid : 4;
        unsigned int axi_qos : 2;
        unsigned int axi_mainpress : 2;
        unsigned int axi_outstd_depth : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_CMD_CMDLIST_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_START (0)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mid_END (3)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_START (4)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_qos_END (5)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_START (6)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_mainpress_END (7)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_START (8)
#define SOC_DSS_CMD_CMDLIST_CTRL_axi_outstd_depth_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_secu : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_SECU_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_START (0)
#define SOC_DSS_CMD_CMDLIST_SECU_ch_secu_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_INTS_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_START (0)
#define SOC_DSS_CMD_CMDLIST_INTS_ch_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_swreset : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_CMD_CMDLIST_SWRST_UNION;
#endif
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_START (0)
#define SOC_DSS_CMD_CMDLIST_SWRST_ch_swreset_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_CMD_CMD_MEM_CTRL_UNION;
#endif
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_START (0)
#define SOC_DSS_CMD_CMD_MEM_CTRL_cmd_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_clk_sel : 32;
    } reg;
} SOC_DSS_CMD_CMD_CLK_SEL_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_START (0)
#define SOC_DSS_CMD_CMD_CLK_SEL_cmd_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_clk_en : 32;
    } reg;
} SOC_DSS_CMD_CMD_CLK_EN_UNION;
#endif
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_START (0)
#define SOC_DSS_CMD_CMD_CLK_EN_cmd_clk_en_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
