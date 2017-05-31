#ifndef __SOC_HDLC_INTERFACE_H__
#define __SOC_HDLC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_HDLC_STATE_SW_RST_ADDR(base) ((base) + (0x0000))
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(base) ((base) + (0x0004))
#define SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(base) ((base) + (0x0008))
#define SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(base) ((base) + (0x000C))
#define SOC_HDLC_FRM_EN_ADDR(base) ((base) + (0x0010))
#define SOC_HDLC_FRM_RAW_INT_ADDR(base) ((base) + (0x0014))
#define SOC_HDLC_FRM_INT_STATUS_ADDR(base) ((base) + (0x0018))
#define SOC_HDLC_FRM_INT_CLR_ADDR(base) ((base) + (0x001C))
#define SOC_HDLC_FRM_CFG_ADDR(base) ((base) + (0x0020))
#define SOC_HDLC_FRM_ACCM_ADDR(base) ((base) + (0x0024))
#define SOC_HDLC_FRM_STATUS_ADDR(base) ((base) + (0x0028))
#define SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(base) ((base) + (0x0030))
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(base) ((base) + (0x0034))
#define SOC_HDLC_FRM_IN_PKT_LEN_ADDR(base) ((base) + (0x0038))
#define SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(base) ((base) + (0x003C))
#define SOC_HDLC_FRM_IN_BLK_LEN_ADDR(base) ((base) + (0x0040))
#define SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(base) ((base) + (0x0044))
#define SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(base) ((base) + (0x0048))
#define SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(base) ((base) + (0x004C))
#define SOC_HDLC_FRM_RPT_ADDR_ADDR(base) ((base) + (0x0050))
#define SOC_HDLC_FRM_RPT_DEP_ADDR(base) ((base) + (0x0054))
#define SOC_HDLC_DEF_EN_ADDR(base) ((base) + (0x0060))
#define SOC_HDLC_DEF_RAW_INT_ADDR(base) ((base) + (0x0064))
#define SOC_HDLC_DEF_INT_STATUS_ADDR(base) ((base) + (0x0068))
#define SOC_HDLC_DEF_INT_CLR_ADDR(base) ((base) + (0x006C))
#define SOC_HDLC_DEF_CFG_ADDR(base) ((base) + (0x0070))
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(base) ((base) + (0x0074))
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(base) ((base) + (0x0078))
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(base) ((base) + (0x007C))
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(base) ((base) + (0x0080))
#define SOC_HDLC_DEF_GO_ON_ADDR(base) ((base) + (0x0084))
#define SOC_HDLC_DEF_STATUS_ADDR(base) ((base) + (0x0088))
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(base) ((base) + (0x008C))
#define SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(base) ((base) + (0x0090))
#define SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(base) ((base) + (0x0094))
#define SOC_HDLC_DEF_IN_PKT_LEN_ADDR(base) ((base) + (0x0098))
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(base) ((base) + (0x009C))
#define SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(base) ((base) + (0x00A0))
#define SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(base) ((base) + (0x00A4))
#define SOC_HDLC_DEF_RPT_ADDR_ADDR(base) ((base) + (0x00A8))
#define SOC_HDLC_DEF_RPT_DEP_ADDR(base) ((base) + (0x00AC))
#define SOC_HDLC_DEF_ERR_INFO_0_ADDR(base) ((base) + (0x00B0))
#define SOC_HDLC_DEF_ERR_INFO_1_ADDR(base) ((base) + (0x00B4))
#define SOC_HDLC_DEF_ERR_INFO_2_ADDR(base) ((base) + (0x00B8))
#define SOC_HDLC_DEF_ERR_INFO_3_ADDR(base) ((base) + (0x00BC))
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(base) ((base) + (0x00C0))
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(base) ((base) + (0x00C4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int state_sw_rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HDLC_STATE_SW_RST_UNION;
#endif
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_START (0)
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdlc_prior_ctrl : 2;
        unsigned int reserved_0 : 6;
        unsigned int axireq_timeout_en : 1;
        unsigned int reserved_1 : 7;
        unsigned int axireq_timeout_value : 8;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION;
#endif
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_START (0)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_END (1)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_START (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_END (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_START (16)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_err_curr_addr : 32;
    } reg;
} SOC_HDLC_RD_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_START (0)
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_err_curr_addr : 32;
    } reg;
} SOC_HDLC_WR_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_START (0)
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int frm_rd_err_en : 1;
        unsigned int frm_wr_err_en : 1;
        unsigned int frm_rd_timeout_en : 1;
        unsigned int frm_wr_timeout_en : 1;
        unsigned int frm_cfg_err_en : 1;
        unsigned int frm_in_prm_err_en : 1;
        unsigned int frm_out_prm_err_en : 1;
        unsigned int frm_rpt_prm_err_en : 1;
        unsigned int frm_out_spc_err_en : 1;
        unsigned int frm_rpt_dep_err_en : 1;
        unsigned int reserved_1 : 6;
        unsigned int frm_over_int_en : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_FRM_EN_UNION;
#endif
#define SOC_HDLC_FRM_EN_frm_en_START (0)
#define SOC_HDLC_FRM_EN_frm_en_END (0)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_START (8)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_END (8)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_START (9)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_END (9)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_START (10)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_END (10)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_START (11)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_END (11)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_START (12)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_END (12)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_START (13)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_END (13)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_START (14)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_END (14)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_START (15)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_END (15)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_START (16)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_END (16)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_START (17)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_END (17)
#define SOC_HDLC_FRM_EN_frm_over_int_en_START (24)
#define SOC_HDLC_FRM_EN_frm_over_int_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int frm_rd_err_raw : 1;
        unsigned int frm_wr_err_raw : 1;
        unsigned int frm_rd_timeout_raw : 1;
        unsigned int frm_wr_timeout_raw : 1;
        unsigned int frm_cfg_err_raw : 1;
        unsigned int frm_in_prm_err_raw : 1;
        unsigned int frm_out_prm_err_raw : 1;
        unsigned int frm_rpt_prm_err_raw : 1;
        unsigned int frm_out_spc_err_raw : 1;
        unsigned int frm_rpt_dep_err_raw : 1;
        unsigned int reserved_1 : 6;
        unsigned int frm_over_int_raw : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_FRM_RAW_INT_UNION;
#endif
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_START (8)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_END (8)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_START (9)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_END (9)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_START (10)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_END (10)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_START (11)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_END (11)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_START (12)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_END (12)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_START (13)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_END (13)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_START (14)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_END (14)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_START (15)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_END (15)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_START (16)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_END (16)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_START (17)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_END (17)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_START (24)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int frm_rd_err_stat : 1;
        unsigned int frm_wr_err_stat : 1;
        unsigned int frm_rd_timeout_stat : 1;
        unsigned int frm_wr_timeout_stat : 1;
        unsigned int frm_cfg_err_stat : 1;
        unsigned int frm_in_prm_err_stat : 1;
        unsigned int frm_out_prm_err_stat : 1;
        unsigned int frm_rpt_prm_err_stat : 1;
        unsigned int frm_out_spc_err_stat : 1;
        unsigned int frm_rpt_dep_err_stat : 1;
        unsigned int reserved_1 : 6;
        unsigned int frm_over_int_stat : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_FRM_INT_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_START (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_END (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_START (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_END (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_START (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_END (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_START (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_END (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_START (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_END (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_START (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_END (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_START (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_END (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_START (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_END (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_START (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_END (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_START (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_END (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_START (24)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int frm_rd_err_clr : 1;
        unsigned int frm_wr_err_clr : 1;
        unsigned int frm_rd_timeout_clr : 1;
        unsigned int frm_wr_timeout_clr : 1;
        unsigned int frm_cfg_err_clr : 1;
        unsigned int frm_in_prm_err_clr : 1;
        unsigned int frm_out_prm_err_clr : 1;
        unsigned int frm_rpt_prm_err_clr : 1;
        unsigned int frm_out_spc_err_clr : 1;
        unsigned int frm_rpt_dep_err_clr : 1;
        unsigned int reserved_1 : 6;
        unsigned int frm_over_int_clr : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_FRM_INT_CLR_UNION;
#endif
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_START (8)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_END (8)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_START (9)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_END (9)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_START (10)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_END (10)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_START (11)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_END (11)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_START (12)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_END (12)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_START (13)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_END (13)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_START (14)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_END (14)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_START (15)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_END (15)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_START (16)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_END (16)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_START (17)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_END (17)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_START (24)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_lli_1dor2d : 1;
        unsigned int frm_acfc : 1;
        unsigned int frm_pfc : 2;
        unsigned int reserved : 12;
        unsigned int frm_protocol : 16;
    } reg;
} SOC_HDLC_FRM_CFG_UNION;
#endif
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_START (0)
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_END (0)
#define SOC_HDLC_FRM_CFG_frm_acfc_START (1)
#define SOC_HDLC_FRM_CFG_frm_acfc_END (1)
#define SOC_HDLC_FRM_CFG_frm_pfc_START (2)
#define SOC_HDLC_FRM_CFG_frm_pfc_END (3)
#define SOC_HDLC_FRM_CFG_frm_protocol_START (16)
#define SOC_HDLC_FRM_CFG_frm_protocol_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdlc_frm_accm : 32;
    } reg;
} SOC_HDLC_FRM_ACCM_UNION;
#endif
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_START (0)
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_all_pkt_done : 1;
        unsigned int frm_error_index : 1;
        unsigned int reserved : 6;
        unsigned int frm_valid_num : 8;
        unsigned int frm_out_seg_num : 16;
    } reg;
} SOC_HDLC_FRM_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_START (0)
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_END (0)
#define SOC_HDLC_FRM_STATUS_frm_error_index_START (1)
#define SOC_HDLC_FRM_STATUS_frm_error_index_END (1)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_START (8)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_END (15)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_START (16)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_lli_addr : 32;
    } reg;
} SOC_HDLC_FRM_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_START (0)
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_sublli_addr : 32;
    } reg;
} SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_START (0)
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_pkt_len : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_FRM_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_START (0)
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_blk_addr : 32;
    } reg;
} SOC_HDLC_FRM_IN_BLK_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_START (0)
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_in_blk_len : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_FRM_IN_BLK_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_START (0)
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_out_lli_addr : 32;
    } reg;
} SOC_HDLC_FRM_OUT_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_START (0)
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_out_spc_addr : 32;
    } reg;
} SOC_HDLC_FRM_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_START (0)
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_out_spc_dep : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_FRM_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_START (0)
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_rpt_addr : 32;
    } reg;
} SOC_HDLC_FRM_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_START (0)
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_rpt_dep : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_FRM_RPT_DEP_UNION;
#endif
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_START (0)
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int def_rd_err_en : 1;
        unsigned int def_wr_err_en : 1;
        unsigned int def_rd_timeout_en : 1;
        unsigned int def_wr_timeout_en : 1;
        unsigned int def_cfg_err_en : 1;
        unsigned int def_in_prm_err_en : 1;
        unsigned int def_out_prm_err_en : 1;
        unsigned int def_rpt_prm_err_en : 1;
        unsigned int def_lcp_int_en : 1;
        unsigned int def_out_spc_ful_en : 1;
        unsigned int def_rpt_ful_en : 1;
        unsigned int reserved_1 : 5;
        unsigned int def_over_int_en : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_DEF_EN_UNION;
#endif
#define SOC_HDLC_DEF_EN_def_en_START (0)
#define SOC_HDLC_DEF_EN_def_en_END (0)
#define SOC_HDLC_DEF_EN_def_rd_err_en_START (8)
#define SOC_HDLC_DEF_EN_def_rd_err_en_END (8)
#define SOC_HDLC_DEF_EN_def_wr_err_en_START (9)
#define SOC_HDLC_DEF_EN_def_wr_err_en_END (9)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_START (10)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_END (10)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_START (11)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_END (11)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_START (12)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_END (12)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_START (13)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_END (13)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_START (14)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_END (14)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_START (15)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_END (15)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_START (16)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_END (16)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_START (17)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_END (17)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_START (18)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_END (18)
#define SOC_HDLC_DEF_EN_def_over_int_en_START (24)
#define SOC_HDLC_DEF_EN_def_over_int_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int def_rd_err_raw : 1;
        unsigned int def_wr_err_raw : 1;
        unsigned int def_rd_timeoutraw : 1;
        unsigned int def_wr_timeout_raw : 1;
        unsigned int def_cfg_err_raw : 1;
        unsigned int def_in_prm_err_raw : 1;
        unsigned int def_out_prm_err_raw : 1;
        unsigned int def_rpt_prm_err_raw : 1;
        unsigned int def_lcp_int_raw : 1;
        unsigned int def_out_spc_ful_raw : 1;
        unsigned int def_rpt_ful_raw : 1;
        unsigned int reserved_1 : 5;
        unsigned int def_over_int_raw : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_DEF_RAW_INT_UNION;
#endif
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_START (8)
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_END (8)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_START (9)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_END (9)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_START (10)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_END (10)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_START (11)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_END (11)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_START (12)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_END (12)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_START (13)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_END (13)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_START (14)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_END (14)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_START (15)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_END (15)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_START (16)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_END (16)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_START (17)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_END (17)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_START (18)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_END (18)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_START (24)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int def_rd_err_stat : 1;
        unsigned int def_wr_err_stat : 1;
        unsigned int def_rd_timeoutstat : 1;
        unsigned int def_wr_timeout_stat : 1;
        unsigned int def_cfg_err_stat : 1;
        unsigned int def_in_prm_err_stat : 1;
        unsigned int def_out_prm_err_stat : 1;
        unsigned int def_rpt_prm_err_stat : 1;
        unsigned int def_lcp_int_stat : 1;
        unsigned int def_out_spc_ful_stat : 1;
        unsigned int def_rpt_ful_stat : 1;
        unsigned int reserved_1 : 5;
        unsigned int def_over_int_stat : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_DEF_INT_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_START (8)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_END (8)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_START (9)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_END (9)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_START (10)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_END (10)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_START (11)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_END (11)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_START (12)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_END (12)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_START (13)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_END (13)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_START (14)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_END (14)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_START (15)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_END (15)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_START (16)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_END (16)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_START (17)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_END (17)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_START (18)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_END (18)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_START (24)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int def_rd_err_clr : 1;
        unsigned int def_wr_err_clr : 1;
        unsigned int def_rd_timeoutclr : 1;
        unsigned int def_wr_timeout_clr : 1;
        unsigned int def_cfg_err_clr : 1;
        unsigned int def_in_prm_err_clr : 1;
        unsigned int def_out_prm_err_clr : 1;
        unsigned int def_rpt_prm_err_clr : 1;
        unsigned int def_lcp_int_clr : 1;
        unsigned int def_out_spc_ful_clr : 1;
        unsigned int def_rpt_ful_clr : 1;
        unsigned int reserved_1 : 5;
        unsigned int def_over_int_clr : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_HDLC_DEF_INT_CLR_UNION;
#endif
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_START (8)
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_END (8)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_START (9)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_END (9)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_START (10)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_END (10)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_START (11)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_END (11)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_START (12)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_END (12)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_START (13)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_END (13)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_START (14)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_END (14)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_START (15)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_END (15)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_START (16)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_END (16)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_START (17)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_END (17)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_START (18)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_END (18)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_START (24)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_uncompleted_ago : 1;
        unsigned int def_acfc : 1;
        unsigned int def_pfc : 2;
        unsigned int reserved : 28;
    } reg;
} SOC_HDLC_DEF_CFG_UNION;
#endif
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_START (0)
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_END (0)
#define SOC_HDLC_DEF_CFG_def_acfc_START (1)
#define SOC_HDLC_DEF_CFG_def_acfc_END (1)
#define SOC_HDLC_DEF_CFG_def_pfc_START (2)
#define SOC_HDLC_DEF_CFG_def_pfc_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_uncompleted_len : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_START (0)
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_uncompleted_pro : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_START (0)
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_uncompleted_addr : 32;
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_START (0)
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_data_st_curr_ago : 5;
        unsigned int reserved : 11;
        unsigned int crc16_result_ago : 16;
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_START (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_END (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_START (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_lcp_goon : 1;
        unsigned int reserved_0 : 7;
        unsigned int def_outspc_ful_goon : 1;
        unsigned int reserved_1 : 7;
        unsigned int def_rpt_ful_goon : 1;
        unsigned int reserved_2 : 15;
    } reg;
} SOC_HDLC_DEF_GO_ON_UNION;
#endif
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_START (0)
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_END (0)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_START (8)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_END (8)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_START (16)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_all_pkt_pro_stat : 2;
        unsigned int def_uncompleted_now : 1;
        unsigned int def_out_spc_ful : 1;
        unsigned int def_rpt_ful : 1;
        unsigned int def_error_index : 1;
        unsigned int reserved_0 : 2;
        unsigned int def_valid_num : 16;
        unsigned int def_err_type : 7;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_HDLC_DEF_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_START (0)
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_END (1)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_START (2)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_END (2)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_START (3)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_END (3)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_START (4)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_END (4)
#define SOC_HDLC_DEF_STATUS_def_error_index_START (5)
#define SOC_HDLC_DEF_STATUS_def_error_index_END (5)
#define SOC_HDLC_DEF_STATUS_def_valid_num_START (8)
#define SOC_HDLC_DEF_STATUS_def_valid_num_END (23)
#define SOC_HDLC_DEF_STATUS_def_err_type_START (24)
#define SOC_HDLC_DEF_STATUS_def_err_type_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_data_st_curr_now : 5;
        unsigned int reserved : 11;
        unsigned int crc16_result_now : 16;
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_START (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_END (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_START (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_in_lli_addr : 32;
    } reg;
} SOC_HDLC_DEF_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_START (0)
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_in_pkt_addr : 32;
    } reg;
} SOC_HDLC_DEF_IN_PKT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_START (0)
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_in_pkt_len : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_START (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_in_pkt_len_max : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_START (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_out_spc_addr : 32;
    } reg;
} SOC_HDLC_DEF_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_START (0)
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_out_spc_dep : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_START (0)
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_rpt_addr : 32;
    } reg;
} SOC_HDLC_DEF_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_START (0)
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_out_result_dep : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_RPT_DEP_UNION;
#endif
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_START (0)
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_err0_num : 16;
        unsigned int def_err1_num : 16;
    } reg;
} SOC_HDLC_DEF_ERR_INFO_0_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_START (0)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_END (15)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_START (16)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_err2_num : 16;
        unsigned int def_err3_num : 16;
    } reg;
} SOC_HDLC_DEF_ERR_INFO_1_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_START (0)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_END (15)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_START (16)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_err4_num : 16;
        unsigned int def_err5_num : 16;
    } reg;
} SOC_HDLC_DEF_ERR_INFO_2_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_START (0)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_END (15)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_START (16)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_err6_num : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HDLC_DEF_ERR_INFO_3_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_START (0)
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_info_cnt_ago : 11;
        unsigned int reserved_0 : 5;
        unsigned int def_framel_cnt_ago : 11;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_START (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_END (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_START (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int def_info_cnt_now : 11;
        unsigned int reserved_0 : 5;
        unsigned int def_framel_cnt_now : 11;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_START (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_END (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_START (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_END (26)
#define SOC_HDLC_REG_ACTUAL_ADDR(base,offset) ((base)+(offset))
#define FEATURE_HDLC_MASTER 
#ifdef FEATURE_HDLC_MASTER
#define SOC_ARM_HDLC_STATE_SW_RST_ADDR(BaseAddr) SOC_HDLC_STATE_SW_RST_ADDR(BaseAddr)
#define SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(BaseAddr) SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(BaseAddr)
#define SOC_ARM_HDLC_RD_ERR_CURR_ADDR(BaseAddr) SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_WR_ERR_CURR_ADDR(BaseAddr) SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_EN_ADDR(BaseAddr) SOC_HDLC_FRM_EN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_RAW_INT_ADDR(BaseAddr) SOC_HDLC_FRM_RAW_INT_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(BaseAddr) SOC_HDLC_FRM_INT_STATUS_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_INT_CLR_ADDR(BaseAddr) SOC_HDLC_FRM_INT_CLR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_CFG_ADDR(BaseAddr) SOC_HDLC_FRM_CFG_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_ACCM_ADDR(BaseAddr) SOC_HDLC_FRM_ACCM_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_STATUS_ADDR(BaseAddr) SOC_HDLC_FRM_STATUS_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_IN_LLI_ADDR(BaseAddr) SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(BaseAddr) SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr) SOC_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_IN_BLK_ADDR(BaseAddr) SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr) SOC_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(BaseAddr) SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(BaseAddr) SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(BaseAddr) SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_RPT_ADDR(BaseAddr) SOC_HDLC_FRM_RPT_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(BaseAddr) SOC_HDLC_FRM_RPT_DEP_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_EN_ADDR(BaseAddr) SOC_HDLC_DEF_EN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_RAW_INT_ADDR(BaseAddr) SOC_HDLC_DEF_RAW_INT_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(BaseAddr) SOC_HDLC_DEF_INT_STATUS_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_INT_CLR_ADDR(BaseAddr) SOC_HDLC_DEF_INT_CLR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_CFG_ADDR(BaseAddr) SOC_HDLC_DEF_CFG_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr) SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr) SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(BaseAddr) SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(BaseAddr) SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_GO_ON_ADDR(BaseAddr) SOC_HDLC_DEF_GO_ON_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_STATUS_ADDR(BaseAddr) SOC_HDLC_DEF_STATUS_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(BaseAddr) SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_IN_LLI_ADDR(BaseAddr) SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_IN_PKT_ADDR(BaseAddr) SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr) SOC_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr) SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(BaseAddr) SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(BaseAddr) SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_RPT_ADDR(BaseAddr) SOC_HDLC_DEF_RPT_ADDR_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(BaseAddr) SOC_HDLC_DEF_RPT_DEP_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr) SOC_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr) SOC_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr) SOC_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr) SOC_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr) SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr)
#define SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr) SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr)
#else
#define SOC_ARM_HDLC_ENABLE_REG_ADDR SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x0038)
#define SOC_ARM_HDLC_DISABLE_REG_ADDR SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x003C)
#define SOC_ARM_HDLC_REG_BIT (9)
#define SOC_AMR_HDLC_ENABLE() 
#define SOC_AMR_HDLC_DISABLE() 
#define SOC_ARM_HDLC_FRAMER_IN_DATA_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x1000)
#define SOC_ARM_HDLC_FRAMER_OUT_DATA_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x2000)
#define SOC_ARM_HDLC_DEFRAMER_IN_DATA_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x3000)
#define SOC_ARM_HDLC_DEFRAMER_OUT_DATA_BASE_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x4000)
#define SOC_ARM_HDLC_DEFRAMER_OUT_LIST_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x6000)
#define SOC_ARM_HDLC_INTERRUPT_ENABLE_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0004)
#define SOC_ARM_HDLC_INTERRUPT_FRAMER_RAW_INT_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0008)
#define SOC_ARM_HDLC_INTERRUPT_INT_STATUS_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x000C)
#define SOC_ARM_HDLC_FRAMER_INTERRUPT_CLEAR_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0010)
#define SOC_ARM_HDLC_FRAMER_CFG_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0020)
#define SOC_ARM_HDLC_FRAMER_ACCM_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0024)
#define SOC_ARM_HDLC_FRAMER_CTRL_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0028)
#define SOC_ARM_HDLC_FRAMER_STATUS_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x002C)
#define SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0040)
#define SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0044)
#define SOC_ARM_HDLC_DEFRAMER_GO_ON_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0048)
#define SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x004C)
#define SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_0_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0050)
#define SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_1_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0054)
#define SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_2_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0058)
#define SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_3_ADDR(BaseAddr) SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x005C)
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
