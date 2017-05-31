#ifndef __SOC_EXMBIST_INTERFACE_H__
#define __SOC_EXMBIST_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_EXMBIST_CMD_ADDR_ADDR(base) ((base) + (0x0000))
#define SOC_EXMBIST_DAT_ADDR_ADDR(base) ((base) + (0x0004))
#define SOC_EXMBIST_EN_ADDR(base) ((base) + (0x0008))
#define SOC_EXMBIST_CLKEN0_ADDR(base) ((base) + (0x000C))
#define SOC_EXMBIST_CLKEN1_ADDR(base) ((base) + (0x0010))
#define SOC_EXMBIST_MUX_SEL_ADDR(base) ((base) + (0x0014))
#define SOC_EXMBIST_OTS_LINE_ADDR(base) ((base) + (0x0018))
#define SOC_EXMBIST_SECUER_EN_ADDR(base) ((base) + (0x001C))
#define SOC_EXMBIST_QOS_ADDR(base) ((base) + (0x0020))
#define SOC_EXMBIST_CMD_MERGE_ADDR(base) ((base) + (0x0024))
#define SOC_EXMBIST_RANK_VOL_ADDR(base,i) ((base) + (0x0028+0x4*(i)))
#define SOC_EXMBIST_TEST_RANK_ADDR(base) ((base) + (0x0048))
#define SOC_EXMBIST_DRAM_WIDTH_ADDR(base) ((base) + (0x004C))
#define SOC_EXMBIST_CHAN_INFO_ADDR(base) ((base) + (0x0050))
#define SOC_EXMBIST_ADDR_INTLV_ADDR(base) ((base) + (0x0054))
#define SOC_EXMBIST_STATUS_ADDR(base) ((base) + (0x0058))
#define SOC_EXMBIST_DFX_INFO_ADDR(base) ((base) + (0x005C))
#define SOC_EXMBIST_PCLK_GATE_ADDR(base) ((base) + (0x0060))
#define SOC_EXMBIST_MEM_CTRL_ADDR(base) ((base) + (0x0064))
#define SOC_EXMBIST_COMMON_CTRL0_ADDR(base) ((base) + (0x0068))
#define SOC_EXMBIST_COMMON_CTRL1_ADDR(base) ((base) + (0x006C))
#define SOC_EXMBIST_COMMON_CTRL2_ADDR(base) ((base) + (0x0070))
#define SOC_EXMBIST_COMMON_CTRL3_ADDR(base) ((base) + (0x0074))
#define SOC_EXMBIST_RW_MID_ADDR(base) ((base) + (0x0078))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_info : 8;
        unsigned int data_info_cmd : 24;
    } reg;
} SOC_EXMBIST_CMD_ADDR_UNION;
#endif
#define SOC_EXMBIST_CMD_ADDR_cmd_info_START (0)
#define SOC_EXMBIST_CMD_ADDR_cmd_info_END (7)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_START (8)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_info : 32;
    } reg;
} SOC_EXMBIST_DAT_ADDR_UNION;
#endif
#define SOC_EXMBIST_DAT_ADDR_data_info_START (0)
#define SOC_EXMBIST_DAT_ADDR_data_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_exmbist_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EXMBIST_EN_UNION;
#endif
#define SOC_EXMBIST_EN_cfg_exmbist_en_START (0)
#define SOC_EXMBIST_EN_cfg_exmbist_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_clk_en_0 : 1;
        unsigned int dmc_clk_en_1 : 1;
        unsigned int rdr_clk_en_0 : 1;
        unsigned int apb_clken_0 : 1;
        unsigned int dmc_clk_en_2 : 1;
        unsigned int dmc_clk_en_3 : 1;
        unsigned int rdr_clk_en_1 : 1;
        unsigned int apb_clken_1 : 1;
        unsigned int reserved_0 : 1;
        unsigned int brg_ivp_clk_en : 1;
        unsigned int exmbist_wrap_clk_en : 1;
        unsigned int reserved_1 : 5;
        unsigned int clk_wr_en : 16;
    } reg;
} SOC_EXMBIST_CLKEN0_UNION;
#endif
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_START (0)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_END (0)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_1_START (1)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_1_END (1)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_START (2)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_END (2)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_START (3)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_END (3)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_2_START (4)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_2_END (4)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_3_START (5)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_3_END (5)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_1_START (6)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_1_END (6)
#define SOC_EXMBIST_CLKEN0_apb_clken_1_START (7)
#define SOC_EXMBIST_CLKEN0_apb_clken_1_END (7)
#define SOC_EXMBIST_CLKEN0_brg_ivp_clk_en_START (9)
#define SOC_EXMBIST_CLKEN0_brg_ivp_clk_en_END (9)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_START (10)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_END (10)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_START (16)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pack_clk_en_0 : 1;
        unsigned int pack_apb_clk_en_0 : 1;
        unsigned int pack_clk_en_1 : 1;
        unsigned int pack_apb_clk_en_1 : 1;
        unsigned int pack_clk_en_2 : 1;
        unsigned int pack_apb_clk_en_2 : 1;
        unsigned int pack_clk_en_3 : 1;
        unsigned int pack_apb_clk_en_3 : 1;
        unsigned int reserved : 8;
        unsigned int clk_wr_en : 16;
    } reg;
} SOC_EXMBIST_CLKEN1_UNION;
#endif
#define SOC_EXMBIST_CLKEN1_pack_clk_en_0_START (0)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_0_END (0)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_START (1)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_END (1)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_1_START (2)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_1_END (2)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_1_START (3)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_1_END (3)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_2_START (4)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_2_END (4)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_2_START (5)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_2_END (5)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_3_START (6)
#define SOC_EXMBIST_CLKEN1_pack_clk_en_3_END (6)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_3_START (7)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_3_END (7)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_START (16)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mux_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EXMBIST_MUX_SEL_UNION;
#endif
#define SOC_EXMBIST_MUX_SEL_mux_sel_START (0)
#define SOC_EXMBIST_MUX_SEL_mux_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_wr_ots_line : 6;
        unsigned int reserved_0 : 10;
        unsigned int cfg_rd_ots_line : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_EXMBIST_OTS_LINE_UNION;
#endif
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_START (0)
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_END (5)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_START (16)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_secure_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EXMBIST_SECUER_EN_UNION;
#endif
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_START (0)
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_rd_qos : 4;
        unsigned int reserved_0 : 12;
        unsigned int cfg_wr_qos : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_EXMBIST_QOS_UNION;
#endif
#define SOC_EXMBIST_QOS_cfg_rd_qos_START (0)
#define SOC_EXMBIST_QOS_cfg_rd_qos_END (3)
#define SOC_EXMBIST_QOS_cfg_wr_qos_START (16)
#define SOC_EXMBIST_QOS_cfg_wr_qos_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_cmd_merge_bypass : 1;
        unsigned int cfg_cmd_wait_timeout : 3;
        unsigned int reserved : 28;
    } reg;
} SOC_EXMBIST_CMD_MERGE_UNION;
#endif
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_START (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_END (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_START (1)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_col_bit : 3;
        unsigned int cfg_row_bit : 3;
        unsigned int cfg_bank_bit : 2;
        unsigned int reserved : 24;
    } reg;
} SOC_EXMBIST_RANK_VOL_UNION;
#endif
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_START (0)
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_END (2)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_START (3)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_END (5)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_START (6)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_test_rank : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_EXMBIST_TEST_RANK_UNION;
#endif
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_START (0)
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_dram_width : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EXMBIST_DRAM_WIDTH_UNION;
#endif
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_START (0)
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_chan_type : 1;
        unsigned int cfg_test_chan : 2;
        unsigned int reserved : 29;
    } reg;
} SOC_EXMBIST_CHAN_INFO_UNION;
#endif
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_START (0)
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_END (0)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_START (1)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_intlv_gran : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_EXMBIST_ADDR_INTLV_UNION;
#endif
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_START (0)
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_END (2)
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
} SOC_EXMBIST_STATUS_UNION;
#endif
#define SOC_EXMBIST_STATUS_bist_done_START (0)
#define SOC_EXMBIST_STATUS_bist_done_END (0)
#define SOC_EXMBIST_STATUS_bist_pass_START (1)
#define SOC_EXMBIST_STATUS_bist_pass_END (1)
#define SOC_EXMBIST_STATUS_parity_error_START (4)
#define SOC_EXMBIST_STATUS_parity_error_END (4)
#define SOC_EXMBIST_STATUS_watchdog_error_START (5)
#define SOC_EXMBIST_STATUS_watchdog_error_END (5)
#define SOC_EXMBIST_STATUS_diag_fifo_last_START (6)
#define SOC_EXMBIST_STATUS_diag_fifo_last_END (6)
#define SOC_EXMBIST_STATUS_diag_ip_START (8)
#define SOC_EXMBIST_STATUS_diag_ip_END (10)
#define SOC_EXMBIST_STATUS_fingerprint_START (12)
#define SOC_EXMBIST_STATUS_fingerprint_END (15)
#define SOC_EXMBIST_STATUS_iter_cnt_START (16)
#define SOC_EXMBIST_STATUS_iter_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_fifo_empty : 1;
        unsigned int wdata_fifo_empty : 1;
        unsigned int cnt_fifo_empty : 1;
        unsigned int cmd_fifo_full : 1;
        unsigned int wdata_fifo_full : 1;
        unsigned int cnt_fifo_full : 1;
        unsigned int wr_ots_cnt : 6;
        unsigned int rd_ots_cnt : 6;
        unsigned int reserved : 14;
    } reg;
} SOC_EXMBIST_DFX_INFO_UNION;
#endif
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_START (0)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_END (0)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_START (1)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_END (1)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_START (2)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_END (2)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_START (3)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_END (3)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_START (4)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_END (4)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_START (5)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_END (5)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_START (6)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_END (11)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_START (12)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int apb_gt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EXMBIST_PCLK_GATE_UNION;
#endif
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_START (0)
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int slp : 1;
        unsigned int dslp : 1;
        unsigned int sd : 1;
        unsigned int rct : 2;
        unsigned int wct : 2;
        unsigned int kp : 3;
        unsigned int reserved_0: 6;
        unsigned int reserved_1: 16;
    } reg;
} SOC_EXMBIST_MEM_CTRL_UNION;
#endif
#define SOC_EXMBIST_MEM_CTRL_slp_START (0)
#define SOC_EXMBIST_MEM_CTRL_slp_END (0)
#define SOC_EXMBIST_MEM_CTRL_dslp_START (1)
#define SOC_EXMBIST_MEM_CTRL_dslp_END (1)
#define SOC_EXMBIST_MEM_CTRL_sd_START (2)
#define SOC_EXMBIST_MEM_CTRL_sd_END (2)
#define SOC_EXMBIST_MEM_CTRL_rct_START (3)
#define SOC_EXMBIST_MEM_CTRL_rct_END (4)
#define SOC_EXMBIST_MEM_CTRL_wct_START (5)
#define SOC_EXMBIST_MEM_CTRL_wct_END (6)
#define SOC_EXMBIST_MEM_CTRL_kp_START (7)
#define SOC_EXMBIST_MEM_CTRL_kp_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_clk_ddrphy_rs : 4;
        unsigned int sel_clk_ddrphy_rsperi : 1;
        unsigned int sel_clk_ddrphy_in : 1;
        unsigned int reserved : 2;
        unsigned int ddrphy_rs_passthrough : 4;
        unsigned int ddrphy_rs_rst_passthrough : 4;
        unsigned int ddrphy_rs_rstcont_passthrough : 4;
        unsigned int rs_passthrough : 1;
        unsigned int rs_rst_passthrough : 1;
        unsigned int rs_rstcont_passthrough : 1;
        unsigned int ddrphy_rs_rx_passthrough : 4;
        unsigned int rs_rx_passthrough : 1;
        unsigned int ddrphy_rs_passthroug_add : 1;
        unsigned int ddrphy_rs_rst_passthroug_add : 1;
        unsigned int ddrphy_rs_rstcont_passthroug_add : 1;
        unsigned int ddrphy_rs_rx_passthroug_add : 1;
    } reg;
} SOC_EXMBIST_COMMON_CTRL0_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_START (0)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_END (3)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rsperi_START (4)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rsperi_END (4)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_in_START (5)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_in_END (5)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthrough_START (8)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthrough_END (11)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthrough_START (12)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthrough_END (15)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthrough_START (16)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthrough_END (19)
#define SOC_EXMBIST_COMMON_CTRL0_rs_passthrough_START (20)
#define SOC_EXMBIST_COMMON_CTRL0_rs_passthrough_END (20)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rst_passthrough_START (21)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rst_passthrough_END (21)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rstcont_passthrough_START (22)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rstcont_passthrough_END (22)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthrough_START (23)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthrough_END (26)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rx_passthrough_START (27)
#define SOC_EXMBIST_COMMON_CTRL0_rs_rx_passthrough_END (27)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthroug_add_START (28)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_passthroug_add_END (28)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthroug_add_START (29)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rst_passthroug_add_END (29)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthroug_add_START (30)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rstcont_passthroug_add_END (30)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthroug_add_START (31)
#define SOC_EXMBIST_COMMON_CTRL0_ddrphy_rs_rx_passthroug_add_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pack_apb_deadlock_avoid : 1;
        unsigned int reserved_0 : 7;
        unsigned int sel_clk_ddrphy_rs_add : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_EXMBIST_COMMON_CTRL1_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_START (0)
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_END (0)
#define SOC_EXMBIST_COMMON_CTRL1_sel_clk_ddrphy_rs_add_START (8)
#define SOC_EXMBIST_COMMON_CTRL1_sel_clk_ddrphy_rs_add_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int common_ctrl2 : 32;
    } reg;
} SOC_EXMBIST_COMMON_CTRL2_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_START (0)
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int common_ctrl3 : 32;
    } reg;
} SOC_EXMBIST_COMMON_CTRL3_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_START (0)
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rw_mid : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_EXMBIST_RW_MID_UNION;
#endif
#define SOC_EXMBIST_RW_MID_rw_mid_START (0)
#define SOC_EXMBIST_RW_MID_rw_mid_END (5)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
