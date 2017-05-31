#ifndef __SOC_DSS_DSI_INTERFACE_H__
#define __SOC_DSS_DSI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_DSI_VERSION_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_DSI_PWR_UP_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_DSI_CLKMGR_CFG_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_DSI_DPI_VCID_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_DSI_DPI_COLOR_CODING_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_DSI_DPI_CFG_POL_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_DSI_PCKHDL_CFG_ADDR(base) ((base) + (0x002C))
#define SOC_DSS_DSI_GEN_VCID_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_DSI_MODE_CFG_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_DSI_VID_MODE_CFG_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_DSI_VID_PKT_SIZE_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_DSI_VID_NULL_SIZE_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_DSI_VID_HSA_TIME_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_DSI_VID_HBP_TIME_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_DSI_VID_HLINE_TIME_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_DSI_VID_VSA_LINES_ADDR(base) ((base) + (0x0054))
#define SOC_DSS_DSI_VID_VBP_LINES_ADDR(base) ((base) + (0x0058))
#define SOC_DSS_DSI_VID_VFP_LINES_ADDR(base) ((base) + (0x005C))
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_DSI_EDPI_CMD_SIZE_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_DSI_CMD_MODE_CFG_ADDR(base) ((base) + (0x0068))
#define SOC_DSS_DSI_GEN_HDR_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_DSI_GEN_PLD_DATA_ADDR(base) ((base) + (0x0070))
#define SOC_DSS_DSI_CMD_PKT_STATUS_ADDR(base) ((base) + (0x0074))
#define SOC_DSS_DSI_TO_CNT_CFG_ADDR(base) ((base) + (0x0078))
#define SOC_DSS_DSI_HS_RD_TO_CNT_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_DSI_LP_RD_TO_CNT_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_DSI_HS_WR_TO_CNT_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_DSI_LP_WR_TO_CNT_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_DSI_BTA_TO_CNT_ADDR(base) ((base) + (0x008C))
#define SOC_DSS_DSI_SDF_3D_ADDR(base) ((base) + (0x0090))
#define SOC_DSS_DSI_LPCLK_CTRL_ADDR(base) ((base) + (0x0094))
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_ADDR(base) ((base) + (0x0098))
#define SOC_DSS_DSI_PHY_TMR_CFG_ADDR(base) ((base) + (0x009C))
#define SOC_DSS_DSI_PHY_RSTZ_ADDR(base) ((base) + (0x00A0))
#define SOC_DSS_DSI_PHY_IF_CFG_ADDR(base) ((base) + (0x00A4))
#define SOC_DSS_DSI_PHY_ULPS_CTRL_ADDR(base) ((base) + (0x00A8))
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_ADDR(base) ((base) + (0x00AC))
#define SOC_DSS_DSI_PHY_STATUS_ADDR(base) ((base) + (0x00B0))
#define SOC_DSS_DSI_PHY_TST_CTRL0_ADDR(base) ((base) + (0x00B4))
#define SOC_DSS_DSI_PHY_TST_CTRL1_ADDR(base) ((base) + (0x00B8))
#define SOC_DSS_DSI_INT_ST0_ADDR(base) ((base) + (0x00BC))
#define SOC_DSS_DSI_INT_ST1_ADDR(base) ((base) + (0x00C0))
#define SOC_DSS_DSI_INT_MSK0_ADDR(base) ((base) + (0x00C4))
#define SOC_DSS_DSI_INT_MSK1_ADDR(base) ((base) + (0x00C8))
#define SOC_DSS_DSI_INT_FORCE0_ADDR(base) ((base) + (0x00D8))
#define SOC_DSS_DSI_INT_FORCE1_ADDR(base) ((base) + (0x00DC))
#define SOC_DSS_DSI_VID_SHADOW_CTRL_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_DSI_DPI_VCID_ACT_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_ADDR(base) ((base) + (0x0138))
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_ADDR(base) ((base) + (0x013C))
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_ADDR(base) ((base) + (0x0140))
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_ADDR(base) ((base) + (0x0144))
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_ADDR(base) ((base) + (0x0148))
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_ADDR(base) ((base) + (0x014C))
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_ADDR(base) ((base) + (0x0150))
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_ADDR(base) ((base) + (0x0154))
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_ADDR(base) ((base) + (0x0158))
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_ADDR(base) ((base) + (0x015C))
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_ADDR(base) ((base) + (0x0160))
#define SOC_DSS_DSI_SDF_3D_ACT_ADDR(base) ((base) + (0x0190))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version : 32;
    } reg;
} SOC_DSS_DSI_VERSION_UNION;
#endif
#define SOC_DSS_DSI_VERSION_version_START (0)
#define SOC_DSS_DSI_VERSION_version_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shutdownz : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DSI_PWR_UP_UNION;
#endif
#define SOC_DSS_DSI_PWR_UP_shutdownz_START (0)
#define SOC_DSS_DSI_PWR_UP_shutdownz_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_esc_clk_division : 8;
        unsigned int to_clk_division : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_CLKMGR_CFG_UNION;
#endif
#define SOC_DSS_DSI_CLKMGR_CFG_tx_esc_clk_division_START (0)
#define SOC_DSS_DSI_CLKMGR_CFG_tx_esc_clk_division_END (7)
#define SOC_DSS_DSI_CLKMGR_CFG_to_clk_division_START (8)
#define SOC_DSS_DSI_CLKMGR_CFG_to_clk_division_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi_vcid : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DSI_DPI_VCID_UNION;
#endif
#define SOC_DSS_DSI_DPI_VCID_dpi_vcid_START (0)
#define SOC_DSS_DSI_DPI_VCID_dpi_vcid_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi_color_coding : 4;
        unsigned int reserved_0 : 4;
        unsigned int loosely18_en : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_DSS_DSI_DPI_COLOR_CODING_UNION;
#endif
#define SOC_DSS_DSI_DPI_COLOR_CODING_dpi_color_coding_START (0)
#define SOC_DSS_DSI_DPI_COLOR_CODING_dpi_color_coding_END (3)
#define SOC_DSS_DSI_DPI_COLOR_CODING_loosely18_en_START (8)
#define SOC_DSS_DSI_DPI_COLOR_CODING_loosely18_en_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dataen_active_low : 1;
        unsigned int vsync_active_low : 1;
        unsigned int hsync_active_low : 1;
        unsigned int shutd_active_low : 1;
        unsigned int colorm_active_low : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_DSS_DSI_DPI_CFG_POL_UNION;
#endif
#define SOC_DSS_DSI_DPI_CFG_POL_dataen_active_low_START (0)
#define SOC_DSS_DSI_DPI_CFG_POL_dataen_active_low_END (0)
#define SOC_DSS_DSI_DPI_CFG_POL_vsync_active_low_START (1)
#define SOC_DSS_DSI_DPI_CFG_POL_vsync_active_low_END (1)
#define SOC_DSS_DSI_DPI_CFG_POL_hsync_active_low_START (2)
#define SOC_DSS_DSI_DPI_CFG_POL_hsync_active_low_END (2)
#define SOC_DSS_DSI_DPI_CFG_POL_shutd_active_low_START (3)
#define SOC_DSS_DSI_DPI_CFG_POL_shutd_active_low_END (3)
#define SOC_DSS_DSI_DPI_CFG_POL_colorm_active_low_START (4)
#define SOC_DSS_DSI_DPI_CFG_POL_colorm_active_low_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int invact_lpcmd_time : 8;
        unsigned int reserved_0 : 8;
        unsigned int outvact_lpcmd_time : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSI_DPI_LP_CMD_TIM_UNION;
#endif
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_invact_lpcmd_time_START (0)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_invact_lpcmd_time_END (7)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_outvact_lpcmd_time_START (16)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_outvact_lpcmd_time_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int eotp_tx_en : 1;
        unsigned int eotp_rx_en : 1;
        unsigned int bta_en : 1;
        unsigned int ecc_rx_en : 1;
        unsigned int crc_rx_en : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_DSS_DSI_PCKHDL_CFG_UNION;
#endif
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_tx_en_START (0)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_tx_en_END (0)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_rx_en_START (1)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_rx_en_END (1)
#define SOC_DSS_DSI_PCKHDL_CFG_bta_en_START (2)
#define SOC_DSS_DSI_PCKHDL_CFG_bta_en_END (2)
#define SOC_DSS_DSI_PCKHDL_CFG_ecc_rx_en_START (3)
#define SOC_DSS_DSI_PCKHDL_CFG_ecc_rx_en_END (3)
#define SOC_DSS_DSI_PCKHDL_CFG_crc_rx_en_START (4)
#define SOC_DSS_DSI_PCKHDL_CFG_crc_rx_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_vcid_rx : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DSI_GEN_VCID_UNION;
#endif
#define SOC_DSS_DSI_GEN_VCID_gen_vcid_rx_START (0)
#define SOC_DSS_DSI_GEN_VCID_gen_vcid_rx_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_video_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DSI_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_MODE_CFG_cmd_video_mode_START (0)
#define SOC_DSS_DSI_MODE_CFG_cmd_video_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_mode_type : 2;
        unsigned int reserved_0 : 6;
        unsigned int lp_vsa_en : 1;
        unsigned int lp_vbp_en : 1;
        unsigned int lp_vfp_en : 1;
        unsigned int lp_vact_en : 1;
        unsigned int lp_hbp_en : 1;
        unsigned int lp_hfp_en : 1;
        unsigned int frame_bta_ack_en : 1;
        unsigned int lp_cmd_en : 1;
        unsigned int vpg_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int vpg_mode : 1;
        unsigned int reserved_2 : 3;
        unsigned int vpg_orientation : 1;
        unsigned int reserved_3 : 7;
    } reg;
} SOC_DSS_DSI_VID_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_VID_MODE_CFG_vid_mode_type_START (0)
#define SOC_DSS_DSI_VID_MODE_CFG_vid_mode_type_END (1)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vsa_en_START (8)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vsa_en_END (8)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vbp_en_START (9)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vbp_en_END (9)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vfp_en_START (10)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vfp_en_END (10)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vact_en_START (11)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vact_en_END (11)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hbp_en_START (12)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hbp_en_END (12)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hfp_en_START (13)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hfp_en_END (13)
#define SOC_DSS_DSI_VID_MODE_CFG_frame_bta_ack_en_START (14)
#define SOC_DSS_DSI_VID_MODE_CFG_frame_bta_ack_en_END (14)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_cmd_en_START (15)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_cmd_en_END (15)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_en_START (16)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_en_END (16)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_mode_START (20)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_mode_END (20)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_orientation_START (24)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_orientation_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_pkt_size : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSI_VID_PKT_SIZE_UNION;
#endif
#define SOC_DSS_DSI_VID_PKT_SIZE_vid_pkt_size_START (0)
#define SOC_DSS_DSI_VID_PKT_SIZE_vid_pkt_size_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_null_chunks : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DSI_VID_NUM_CHUNKS_UNION;
#endif
#define SOC_DSS_DSI_VID_NUM_CHUNKS_vid_null_chunks_START (0)
#define SOC_DSS_DSI_VID_NUM_CHUNKS_vid_null_chunks_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_null_size : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DSI_VID_NULL_SIZE_UNION;
#endif
#define SOC_DSS_DSI_VID_NULL_SIZE_vid_null_size_START (0)
#define SOC_DSS_DSI_VID_NULL_SIZE_vid_null_size_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_has_time : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DSI_VID_HSA_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HSA_TIME_vid_has_time_START (0)
#define SOC_DSS_DSI_VID_HSA_TIME_vid_has_time_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_hbp_time : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DSI_VID_HBP_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HBP_TIME_vid_hbp_time_START (0)
#define SOC_DSS_DSI_VID_HBP_TIME_vid_hbp_time_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_hline_time : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_DSS_DSI_VID_HLINE_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HLINE_TIME_vid_hline_time_START (0)
#define SOC_DSS_DSI_VID_HLINE_TIME_vid_hline_time_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vsa_lines : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VSA_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VSA_LINES_vsa_lines_START (0)
#define SOC_DSS_DSI_VID_VSA_LINES_vsa_lines_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vbp_lines : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VBP_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VBP_LINES_vbp_lines_START (0)
#define SOC_DSS_DSI_VID_VBP_LINES_vbp_lines_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vfp_lines : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VFP_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VFP_LINES_vfp_lines_START (0)
#define SOC_DSS_DSI_VID_VFP_LINES_vfp_lines_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_active_lines : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSI_VID_VACTIVE_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VACTIVE_LINES_v_active_lines_START (0)
#define SOC_DSS_DSI_VID_VACTIVE_LINES_v_active_lines_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int edpi_allowed_cmd_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_EDPI_CMD_SIZE_UNION;
#endif
#define SOC_DSS_DSI_EDPI_CMD_SIZE_edpi_allowed_cmd_size_START (0)
#define SOC_DSS_DSI_EDPI_CMD_SIZE_edpi_allowed_cmd_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tear_fx_en : 1;
        unsigned int ack_rqst_en : 1;
        unsigned int reserved_0 : 6;
        unsigned int gen_sw_0p_tx : 1;
        unsigned int gen_sw_1p_tx : 1;
        unsigned int gen_sw_2p_tx : 1;
        unsigned int gen_sr_0p_tx : 1;
        unsigned int gen_sr_1p_tx : 1;
        unsigned int gen_sr_2p_tx : 1;
        unsigned int gen_lw_tx : 1;
        unsigned int reserved_1 : 1;
        unsigned int dcs_sw_0p_tx : 1;
        unsigned int dcs_sw_1p_tx : 1;
        unsigned int dcs_sr_0p_tx : 1;
        unsigned int dcs_lw_tx : 1;
        unsigned int reserved_2 : 4;
        unsigned int max_rd_pkt_size : 1;
        unsigned int reserved_3 : 7;
    } reg;
} SOC_DSS_DSI_CMD_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_CMD_MODE_CFG_tear_fx_en_START (0)
#define SOC_DSS_DSI_CMD_MODE_CFG_tear_fx_en_END (0)
#define SOC_DSS_DSI_CMD_MODE_CFG_ack_rqst_en_START (1)
#define SOC_DSS_DSI_CMD_MODE_CFG_ack_rqst_en_END (1)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_0p_tx_START (8)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_0p_tx_END (8)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_1p_tx_START (9)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_1p_tx_END (9)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_2p_tx_START (10)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_2p_tx_END (10)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_0p_tx_START (11)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_0p_tx_END (11)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_1p_tx_START (12)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_1p_tx_END (12)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_2p_tx_START (13)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_2p_tx_END (13)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_lw_tx_START (14)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_lw_tx_END (14)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_0p_tx_START (16)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_0p_tx_END (16)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_1p_tx_START (17)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_1p_tx_END (17)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sr_0p_tx_START (18)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sr_0p_tx_END (18)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_lw_tx_START (19)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_lw_tx_END (19)
#define SOC_DSS_DSI_CMD_MODE_CFG_max_rd_pkt_size_START (24)
#define SOC_DSS_DSI_CMD_MODE_CFG_max_rd_pkt_size_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_dt : 6;
        unsigned int gen_vc : 2;
        unsigned int gen_wc_lsbyte : 8;
        unsigned int gen_wc_msbyte : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_DSI_GEN_HDR_UNION;
#endif
#define SOC_DSS_DSI_GEN_HDR_gen_dt_START (0)
#define SOC_DSS_DSI_GEN_HDR_gen_dt_END (5)
#define SOC_DSS_DSI_GEN_HDR_gen_vc_START (6)
#define SOC_DSS_DSI_GEN_HDR_gen_vc_END (7)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_lsbyte_START (8)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_lsbyte_END (15)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_msbyte_START (16)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_msbyte_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_pld_b1 : 8;
        unsigned int gen_pld_b2 : 8;
        unsigned int gen_pld_b3 : 8;
        unsigned int gen_pld_b4 : 8;
    } reg;
} SOC_DSS_DSI_GEN_PLD_DATA_UNION;
#endif
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b1_START (0)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b1_END (7)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b2_START (8)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b2_END (15)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b3_START (16)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b3_END (23)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b4_START (24)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_cmd_empty : 1;
        unsigned int gen_cmd_full : 1;
        unsigned int gen_pld_w_empty : 1;
        unsigned int gen_pld_w_full : 1;
        unsigned int gen_pld_r_empty : 1;
        unsigned int gen_pld_r_full : 1;
        unsigned int gen_rd_cmd_busy : 1;
        unsigned int reserved_0 : 1;
        unsigned int dbi_cmd_empty : 1;
        unsigned int dbi_cmd_full : 1;
        unsigned int dbi_pld_w_empty : 1;
        unsigned int dbi_pld_w_full : 1;
        unsigned int dbi_pld_r_empty : 1;
        unsigned int dbi_pld_r_full : 1;
        unsigned int dbi_rd_cmd_busy : 1;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_DSS_DSI_CMD_PKT_STATUS_UNION;
#endif
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_empty_START (0)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_empty_END (0)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_full_START (1)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_full_END (1)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_empty_START (2)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_empty_END (2)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_full_START (3)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_full_END (3)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_empty_START (4)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_empty_END (4)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_full_START (5)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_full_END (5)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_rd_cmd_busy_START (6)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_rd_cmd_busy_END (6)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_empty_START (8)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_empty_END (8)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_full_START (9)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_full_END (9)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_empty_START (10)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_empty_END (10)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_full_START (11)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_full_END (11)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_empty_START (12)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_empty_END (12)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_full_START (13)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_full_END (13)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_rd_cmd_busy_START (14)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_rd_cmd_busy_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lprx_to_cnt : 16;
        unsigned int hstx_to_cnt : 16;
    } reg;
} SOC_DSS_DSI_TO_CNT_CFG_UNION;
#endif
#define SOC_DSS_DSI_TO_CNT_CFG_lprx_to_cnt_START (0)
#define SOC_DSS_DSI_TO_CNT_CFG_lprx_to_cnt_END (15)
#define SOC_DSS_DSI_TO_CNT_CFG_hstx_to_cnt_START (16)
#define SOC_DSS_DSI_TO_CNT_CFG_hstx_to_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hs_rd_to_cnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_HS_RD_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_HS_RD_TO_CNT_hs_rd_to_cnt_START (0)
#define SOC_DSS_DSI_HS_RD_TO_CNT_hs_rd_to_cnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_rd_to_cnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_LP_RD_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_LP_RD_TO_CNT_lp_rd_to_cnt_START (0)
#define SOC_DSS_DSI_LP_RD_TO_CNT_lp_rd_to_cnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hs_wr_to_cnt : 16;
        unsigned int reserved_0 : 8;
        unsigned int presp_to_mode : 1;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_DSS_DSI_HS_WR_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_HS_WR_TO_CNT_hs_wr_to_cnt_START (0)
#define SOC_DSS_DSI_HS_WR_TO_CNT_hs_wr_to_cnt_END (15)
#define SOC_DSS_DSI_HS_WR_TO_CNT_presp_to_mode_START (24)
#define SOC_DSS_DSI_HS_WR_TO_CNT_presp_to_mode_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_wr_to_cnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_LP_WR_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_LP_WR_TO_CNT_lp_wr_to_cnt_START (0)
#define SOC_DSS_DSI_LP_WR_TO_CNT_lp_wr_to_cnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bta_to_cnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSI_BTA_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_BTA_TO_CNT_bta_to_cnt_START (0)
#define SOC_DSS_DSI_BTA_TO_CNT_bta_to_cnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode_3d : 2;
        unsigned int format_3d : 2;
        unsigned int second_vsync : 1;
        unsigned int right_first : 1;
        unsigned int reserved_0 : 10;
        unsigned int send_3d_cfg : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_DSS_DSI_SDF_3D_UNION;
#endif
#define SOC_DSS_DSI_SDF_3D_mode_3d_START (0)
#define SOC_DSS_DSI_SDF_3D_mode_3d_END (1)
#define SOC_DSS_DSI_SDF_3D_format_3d_START (2)
#define SOC_DSS_DSI_SDF_3D_format_3d_END (3)
#define SOC_DSS_DSI_SDF_3D_second_vsync_START (4)
#define SOC_DSS_DSI_SDF_3D_second_vsync_END (4)
#define SOC_DSS_DSI_SDF_3D_right_first_START (5)
#define SOC_DSS_DSI_SDF_3D_right_first_END (5)
#define SOC_DSS_DSI_SDF_3D_send_3d_cfg_START (16)
#define SOC_DSS_DSI_SDF_3D_send_3d_cfg_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_txrequestclkhs : 1;
        unsigned int auto_clklane_ctrl : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DSI_LPCLK_CTRL_UNION;
#endif
#define SOC_DSS_DSI_LPCLK_CTRL_phy_txrequestclkhs_START (0)
#define SOC_DSS_DSI_LPCLK_CTRL_phy_txrequestclkhs_END (0)
#define SOC_DSS_DSI_LPCLK_CTRL_auto_clklane_ctrl_START (1)
#define SOC_DSS_DSI_LPCLK_CTRL_auto_clklane_ctrl_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_clklp2hs_time : 10;
        unsigned int reserved_0 : 6;
        unsigned int phy_clkhs2lp_time : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time_START (0)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time_END (9)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time_START (16)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int max_rd_time : 15;
        unsigned int reserved : 1;
        unsigned int phy_lp2hs_time : 8;
        unsigned int phy_hs2lp_time : 8;
    } reg;
} SOC_DSS_DSI_PHY_TMR_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_TMR_CFG_max_rd_time_START (0)
#define SOC_DSS_DSI_PHY_TMR_CFG_max_rd_time_END (14)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_lp2hs_time_START (16)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_lp2hs_time_END (23)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_hs2lp_time_START (24)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_hs2lp_time_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_shutdownz : 1;
        unsigned int phy_rstz : 1;
        unsigned int phy_enableclk : 1;
        unsigned int phy_forcepll : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DSI_PHY_RSTZ_UNION;
#endif
#define SOC_DSS_DSI_PHY_RSTZ_phy_shutdownz_START (0)
#define SOC_DSS_DSI_PHY_RSTZ_phy_shutdownz_END (0)
#define SOC_DSS_DSI_PHY_RSTZ_phy_rstz_START (1)
#define SOC_DSS_DSI_PHY_RSTZ_phy_rstz_END (1)
#define SOC_DSS_DSI_PHY_RSTZ_phy_enableclk_START (2)
#define SOC_DSS_DSI_PHY_RSTZ_phy_enableclk_END (2)
#define SOC_DSS_DSI_PHY_RSTZ_phy_forcepll_START (3)
#define SOC_DSS_DSI_PHY_RSTZ_phy_forcepll_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int n_lanes : 2;
        unsigned int reserved_0 : 6;
        unsigned int phy_stop_wait_time : 8;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_DSS_DSI_PHY_IF_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_IF_CFG_n_lanes_START (0)
#define SOC_DSS_DSI_PHY_IF_CFG_n_lanes_END (1)
#define SOC_DSS_DSI_PHY_IF_CFG_phy_stop_wait_time_START (8)
#define SOC_DSS_DSI_PHY_IF_CFG_phy_stop_wait_time_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_txrequlpsclk : 1;
        unsigned int phy_txexitulpsclk : 1;
        unsigned int phy_txrequlpslan : 1;
        unsigned int phy_txexitulpslan : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DSI_PHY_ULPS_CTRL_UNION;
#endif
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpsclk_START (0)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpsclk_END (0)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpsclk_START (1)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpsclk_END (1)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpslan_START (2)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpslan_END (2)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpslan_START (3)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpslan_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_tx_triggers : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DSI_PHY_TX_TRIGGERS_UNION;
#endif
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_phy_tx_triggers_START (0)
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_phy_tx_triggers_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_lock : 1;
        unsigned int phy_direction : 1;
        unsigned int phy_stopstateclklane : 1;
        unsigned int phy_ulpsactivenotclk : 1;
        unsigned int phy_stopstate0lane : 1;
        unsigned int phy_ulpsactivenot0lane : 1;
        unsigned int phy_rxulpsesc0lane : 1;
        unsigned int phy_stopstate1lane : 1;
        unsigned int phy_ulpsactivenot1lane : 1;
        unsigned int phy_stopstate2lane : 1;
        unsigned int phy_ulpsactivenot2lane : 1;
        unsigned int phy_stopstate3lane : 1;
        unsigned int phy_ulpsactivenot3lane : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DSI_PHY_STATUS_UNION;
#endif
#define SOC_DSS_DSI_PHY_STATUS_phy_lock_START (0)
#define SOC_DSS_DSI_PHY_STATUS_phy_lock_END (0)
#define SOC_DSS_DSI_PHY_STATUS_phy_direction_START (1)
#define SOC_DSS_DSI_PHY_STATUS_phy_direction_END (1)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstateclklane_START (2)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstateclklane_END (2)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenotclk_START (3)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenotclk_END (3)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate0lane_START (4)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate0lane_END (4)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot0lane_START (5)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot0lane_END (5)
#define SOC_DSS_DSI_PHY_STATUS_phy_rxulpsesc0lane_START (6)
#define SOC_DSS_DSI_PHY_STATUS_phy_rxulpsesc0lane_END (6)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate1lane_START (7)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate1lane_END (7)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot1lane_START (8)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot1lane_END (8)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate2lane_START (9)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate2lane_END (9)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot2lane_START (10)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot2lane_END (10)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate3lane_START (11)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate3lane_END (11)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot3lane_START (12)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot3lane_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_testclr : 1;
        unsigned int phy_testclk : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DSI_PHY_TST_CTRL0_UNION;
#endif
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclr_START (0)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclr_END (0)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclk_START (1)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclk_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_testdin : 8;
        unsigned int phy_testdout : 8;
        unsigned int phy_testen : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_DSS_DSI_PHY_TST_CTRL1_UNION;
#endif
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdin_START (0)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdin_END (7)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdout_START (8)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdout_END (15)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testen_START (16)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testen_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ack_with_err_0 : 1;
        unsigned int ack_with_err_1 : 1;
        unsigned int ack_with_err_2 : 1;
        unsigned int ack_with_err_3 : 1;
        unsigned int ack_with_err_4 : 1;
        unsigned int ack_with_err_5 : 1;
        unsigned int ack_with_err_6 : 1;
        unsigned int ack_with_err_7 : 1;
        unsigned int ack_with_err_8 : 1;
        unsigned int ack_with_err_9 : 1;
        unsigned int ack_with_err_10 : 1;
        unsigned int ack_with_err_11 : 1;
        unsigned int ack_with_err_12 : 1;
        unsigned int ack_with_err_13 : 1;
        unsigned int ack_with_err_14 : 1;
        unsigned int ack_with_err_15 : 1;
        unsigned int dphy_errors_0 : 1;
        unsigned int dphy_errors_1 : 1;
        unsigned int dphy_errors_2 : 1;
        unsigned int dphy_errors_3 : 1;
        unsigned int dphy_errors_4 : 1;
        unsigned int reserved : 11;
    } reg;
} SOC_DSS_DSI_INT_ST0_UNION;
#endif
#define SOC_DSS_DSI_INT_ST0_ack_with_err_0_START (0)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_0_END (0)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_1_START (1)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_1_END (1)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_2_START (2)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_2_END (2)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_3_START (3)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_3_END (3)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_4_START (4)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_4_END (4)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_5_START (5)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_5_END (5)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_6_START (6)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_6_END (6)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_7_START (7)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_7_END (7)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_8_START (8)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_8_END (8)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_9_START (9)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_9_END (9)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_10_START (10)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_10_END (10)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_11_START (11)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_11_END (11)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_12_START (12)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_12_END (12)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_13_START (13)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_13_END (13)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_14_START (14)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_14_END (14)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_15_START (15)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_15_END (15)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_0_START (16)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_0_END (16)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_1_START (17)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_1_END (17)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_2_START (18)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_2_END (18)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_3_START (19)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_3_END (19)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_4_START (20)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_4_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int to_hs_tx : 1;
        unsigned int to_lp_rx : 1;
        unsigned int ecc_single_err : 1;
        unsigned int ecc_milti_err : 1;
        unsigned int crc_err : 1;
        unsigned int pkt_size_err : 1;
        unsigned int eopt_err : 1;
        unsigned int dpi_pld_wr_err : 1;
        unsigned int gen_cmd_wr_err : 1;
        unsigned int gen_pld_wr_err : 1;
        unsigned int gen_pld_send_err : 1;
        unsigned int gen_pld_rd_err : 1;
        unsigned int gen_pld_recv_err : 1;
        unsigned int dbi_cmd_wr_err : 1;
        unsigned int dbi_pld_wr_err : 1;
        unsigned int dbi_pld_rd_err : 1;
        unsigned int dbi_pld_recv_err : 1;
        unsigned int dbi_illegal_comm_err : 1;
        unsigned int reserved : 14;
    } reg;
} SOC_DSS_DSI_INT_ST1_UNION;
#endif
#define SOC_DSS_DSI_INT_ST1_to_hs_tx_START (0)
#define SOC_DSS_DSI_INT_ST1_to_hs_tx_END (0)
#define SOC_DSS_DSI_INT_ST1_to_lp_rx_START (1)
#define SOC_DSS_DSI_INT_ST1_to_lp_rx_END (1)
#define SOC_DSS_DSI_INT_ST1_ecc_single_err_START (2)
#define SOC_DSS_DSI_INT_ST1_ecc_single_err_END (2)
#define SOC_DSS_DSI_INT_ST1_ecc_milti_err_START (3)
#define SOC_DSS_DSI_INT_ST1_ecc_milti_err_END (3)
#define SOC_DSS_DSI_INT_ST1_crc_err_START (4)
#define SOC_DSS_DSI_INT_ST1_crc_err_END (4)
#define SOC_DSS_DSI_INT_ST1_pkt_size_err_START (5)
#define SOC_DSS_DSI_INT_ST1_pkt_size_err_END (5)
#define SOC_DSS_DSI_INT_ST1_eopt_err_START (6)
#define SOC_DSS_DSI_INT_ST1_eopt_err_END (6)
#define SOC_DSS_DSI_INT_ST1_dpi_pld_wr_err_START (7)
#define SOC_DSS_DSI_INT_ST1_dpi_pld_wr_err_END (7)
#define SOC_DSS_DSI_INT_ST1_gen_cmd_wr_err_START (8)
#define SOC_DSS_DSI_INT_ST1_gen_cmd_wr_err_END (8)
#define SOC_DSS_DSI_INT_ST1_gen_pld_wr_err_START (9)
#define SOC_DSS_DSI_INT_ST1_gen_pld_wr_err_END (9)
#define SOC_DSS_DSI_INT_ST1_gen_pld_send_err_START (10)
#define SOC_DSS_DSI_INT_ST1_gen_pld_send_err_END (10)
#define SOC_DSS_DSI_INT_ST1_gen_pld_rd_err_START (11)
#define SOC_DSS_DSI_INT_ST1_gen_pld_rd_err_END (11)
#define SOC_DSS_DSI_INT_ST1_gen_pld_recv_err_START (12)
#define SOC_DSS_DSI_INT_ST1_gen_pld_recv_err_END (12)
#define SOC_DSS_DSI_INT_ST1_dbi_cmd_wr_err_START (13)
#define SOC_DSS_DSI_INT_ST1_dbi_cmd_wr_err_END (13)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_wr_err_START (14)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_wr_err_END (14)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_rd_err_START (15)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_rd_err_END (15)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_recv_err_START (16)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_recv_err_END (16)
#define SOC_DSS_DSI_INT_ST1_dbi_illegal_comm_err_START (17)
#define SOC_DSS_DSI_INT_ST1_dbi_illegal_comm_err_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ack_with_err_msk_0 : 1;
        unsigned int ack_with_err_msk_1 : 1;
        unsigned int ack_with_err_msk_2 : 1;
        unsigned int ack_with_err_msk_3 : 1;
        unsigned int ack_with_err_msk_4 : 1;
        unsigned int ack_with_err_msk_5 : 1;
        unsigned int ack_with_err_msk_6 : 1;
        unsigned int ack_with_err_msk_7 : 1;
        unsigned int ack_with_err_msk_8 : 1;
        unsigned int ack_with_err_msk_9 : 1;
        unsigned int ack_with_err_msk_10 : 1;
        unsigned int ack_with_err_msk_11 : 1;
        unsigned int ack_with_err_msk_12 : 1;
        unsigned int ack_with_err_msk_13 : 1;
        unsigned int ack_with_err_msk_14 : 1;
        unsigned int ack_with_err_msk_15 : 1;
        unsigned int dphy_errors_msk_0 : 1;
        unsigned int dphy_errors_msk_1 : 1;
        unsigned int dphy_errors_msk_2 : 1;
        unsigned int dphy_errors_msk_3 : 1;
        unsigned int dphy_errors_msk_4 : 1;
        unsigned int reserved : 11;
    } reg;
} SOC_DSS_DSI_INT_MSK0_UNION;
#endif
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_0_START (0)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_0_END (0)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_1_START (1)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_1_END (1)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_2_START (2)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_2_END (2)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_3_START (3)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_3_END (3)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_4_START (4)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_4_END (4)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_5_START (5)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_5_END (5)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_6_START (6)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_6_END (6)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_7_START (7)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_7_END (7)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_8_START (8)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_8_END (8)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_9_START (9)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_9_END (9)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_10_START (10)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_10_END (10)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_11_START (11)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_11_END (11)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_12_START (12)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_12_END (12)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_13_START (13)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_13_END (13)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_14_START (14)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_14_END (14)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_15_START (15)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_15_END (15)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_0_START (16)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_0_END (16)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_1_START (17)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_1_END (17)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_2_START (18)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_2_END (18)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_3_START (19)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_3_END (19)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_4_START (20)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_4_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int to_hs_tx_msk : 1;
        unsigned int to_lp_rx_msk : 1;
        unsigned int ecc_single_err_msk : 1;
        unsigned int ecc_milti_err_msk : 1;
        unsigned int crc_err_msk : 1;
        unsigned int pkt_size_err_msk : 1;
        unsigned int eopt_err_msk : 1;
        unsigned int dpi_pld_wr_err_msk : 1;
        unsigned int gen_cmd_wr_err_msk : 1;
        unsigned int gen_pld_wr_err_msk : 1;
        unsigned int gen_pld_send_err_msk : 1;
        unsigned int gen_pld_rd_err_msk : 1;
        unsigned int gen_pld_recv_err_msk : 1;
        unsigned int dbi_cmd_wr_err_msk : 1;
        unsigned int dbi_pld_wr_err_msk : 1;
        unsigned int dbi_pld_rd_err_msk : 1;
        unsigned int dbi_pld_recv_err_msk : 1;
        unsigned int dbi_illegal_comm_err_msk : 1;
        unsigned int reserved : 14;
    } reg;
} SOC_DSS_DSI_INT_MSK1_UNION;
#endif
#define SOC_DSS_DSI_INT_MSK1_to_hs_tx_msk_START (0)
#define SOC_DSS_DSI_INT_MSK1_to_hs_tx_msk_END (0)
#define SOC_DSS_DSI_INT_MSK1_to_lp_rx_msk_START (1)
#define SOC_DSS_DSI_INT_MSK1_to_lp_rx_msk_END (1)
#define SOC_DSS_DSI_INT_MSK1_ecc_single_err_msk_START (2)
#define SOC_DSS_DSI_INT_MSK1_ecc_single_err_msk_END (2)
#define SOC_DSS_DSI_INT_MSK1_ecc_milti_err_msk_START (3)
#define SOC_DSS_DSI_INT_MSK1_ecc_milti_err_msk_END (3)
#define SOC_DSS_DSI_INT_MSK1_crc_err_msk_START (4)
#define SOC_DSS_DSI_INT_MSK1_crc_err_msk_END (4)
#define SOC_DSS_DSI_INT_MSK1_pkt_size_err_msk_START (5)
#define SOC_DSS_DSI_INT_MSK1_pkt_size_err_msk_END (5)
#define SOC_DSS_DSI_INT_MSK1_eopt_err_msk_START (6)
#define SOC_DSS_DSI_INT_MSK1_eopt_err_msk_END (6)
#define SOC_DSS_DSI_INT_MSK1_dpi_pld_wr_err_msk_START (7)
#define SOC_DSS_DSI_INT_MSK1_dpi_pld_wr_err_msk_END (7)
#define SOC_DSS_DSI_INT_MSK1_gen_cmd_wr_err_msk_START (8)
#define SOC_DSS_DSI_INT_MSK1_gen_cmd_wr_err_msk_END (8)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_wr_err_msk_START (9)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_wr_err_msk_END (9)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_send_err_msk_START (10)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_send_err_msk_END (10)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_rd_err_msk_START (11)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_rd_err_msk_END (11)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_recv_err_msk_START (12)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_recv_err_msk_END (12)
#define SOC_DSS_DSI_INT_MSK1_dbi_cmd_wr_err_msk_START (13)
#define SOC_DSS_DSI_INT_MSK1_dbi_cmd_wr_err_msk_END (13)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_wr_err_msk_START (14)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_wr_err_msk_END (14)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_rd_err_msk_START (15)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_rd_err_msk_END (15)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_recv_err_msk_START (16)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_recv_err_msk_END (16)
#define SOC_DSS_DSI_INT_MSK1_dbi_illegal_comm_err_msk_START (17)
#define SOC_DSS_DSI_INT_MSK1_dbi_illegal_comm_err_msk_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ack_with_err_frc_0 : 1;
        unsigned int ack_with_err_frc_1 : 1;
        unsigned int ack_with_err_frc_2 : 1;
        unsigned int ack_with_err_frc_3 : 1;
        unsigned int ack_with_err_frc_4 : 1;
        unsigned int ack_with_err_frc_5 : 1;
        unsigned int ack_with_err_frc_6 : 1;
        unsigned int ack_with_err_frc_7 : 1;
        unsigned int ack_with_err_frc_8 : 1;
        unsigned int ack_with_err_frc_9 : 1;
        unsigned int ack_with_err_frc_10 : 1;
        unsigned int ack_with_err_frc_11 : 1;
        unsigned int ack_with_err_frc_12 : 1;
        unsigned int ack_with_err_frc_13 : 1;
        unsigned int ack_with_err_frc_14 : 1;
        unsigned int ack_with_err_frc_15 : 1;
        unsigned int dphy_error_frc_0 : 1;
        unsigned int dphy_error_frc_1 : 1;
        unsigned int dphy_error_frc_2 : 1;
        unsigned int dphy_error_frc_3 : 1;
        unsigned int dphy_error_frc_4 : 1;
        unsigned int reserved : 11;
    } reg;
} SOC_DSS_DSI_INT_FORCE0_UNION;
#endif
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_0_START (0)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_0_END (0)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_1_START (1)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_1_END (1)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_2_START (2)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_2_END (2)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_3_START (3)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_3_END (3)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_4_START (4)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_4_END (4)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_5_START (5)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_5_END (5)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_6_START (6)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_6_END (6)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_7_START (7)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_7_END (7)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_8_START (8)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_8_END (8)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_9_START (9)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_9_END (9)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_10_START (10)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_10_END (10)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_11_START (11)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_11_END (11)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_12_START (12)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_12_END (12)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_13_START (13)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_13_END (13)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_14_START (14)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_14_END (14)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_15_START (15)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_15_END (15)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_0_START (16)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_0_END (16)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_1_START (17)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_1_END (17)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_2_START (18)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_2_END (18)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_3_START (19)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_3_END (19)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_4_START (20)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_4_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int to_hs_tx_frc : 1;
        unsigned int to_lp_rx_frc : 1;
        unsigned int ecc_single_err_frc : 1;
        unsigned int ecc_milti_err_frc : 1;
        unsigned int crc_err_frc : 1;
        unsigned int pkt_size_err_frc : 1;
        unsigned int eopt_err_frc : 1;
        unsigned int dpi_pld_wr_err_frc : 1;
        unsigned int gen_cmd_wr_err_frc : 1;
        unsigned int gen_pld_wr_err_frc : 1;
        unsigned int gen_pld_send_err_frc : 1;
        unsigned int gen_pld_rd_err_frc : 1;
        unsigned int gen_pld_recev_err_frc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 14;
    } reg;
} SOC_DSS_DSI_INT_FORCE1_UNION;
#endif
#define SOC_DSS_DSI_INT_FORCE1_to_hs_tx_frc_START (0)
#define SOC_DSS_DSI_INT_FORCE1_to_hs_tx_frc_END (0)
#define SOC_DSS_DSI_INT_FORCE1_to_lp_rx_frc_START (1)
#define SOC_DSS_DSI_INT_FORCE1_to_lp_rx_frc_END (1)
#define SOC_DSS_DSI_INT_FORCE1_ecc_single_err_frc_START (2)
#define SOC_DSS_DSI_INT_FORCE1_ecc_single_err_frc_END (2)
#define SOC_DSS_DSI_INT_FORCE1_ecc_milti_err_frc_START (3)
#define SOC_DSS_DSI_INT_FORCE1_ecc_milti_err_frc_END (3)
#define SOC_DSS_DSI_INT_FORCE1_crc_err_frc_START (4)
#define SOC_DSS_DSI_INT_FORCE1_crc_err_frc_END (4)
#define SOC_DSS_DSI_INT_FORCE1_pkt_size_err_frc_START (5)
#define SOC_DSS_DSI_INT_FORCE1_pkt_size_err_frc_END (5)
#define SOC_DSS_DSI_INT_FORCE1_eopt_err_frc_START (6)
#define SOC_DSS_DSI_INT_FORCE1_eopt_err_frc_END (6)
#define SOC_DSS_DSI_INT_FORCE1_dpi_pld_wr_err_frc_START (7)
#define SOC_DSS_DSI_INT_FORCE1_dpi_pld_wr_err_frc_END (7)
#define SOC_DSS_DSI_INT_FORCE1_gen_cmd_wr_err_frc_START (8)
#define SOC_DSS_DSI_INT_FORCE1_gen_cmd_wr_err_frc_END (8)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_wr_err_frc_START (9)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_wr_err_frc_END (9)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_send_err_frc_START (10)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_send_err_frc_END (10)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_rd_err_frc_START (11)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_rd_err_frc_END (11)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_recev_err_frc_START (12)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_recev_err_frc_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_shadow_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int vid_shadow_req : 1;
        unsigned int reserved_1 : 7;
        unsigned int vid_shadow_pin_req : 1;
        unsigned int reserved_2 : 15;
    } reg;
} SOC_DSS_DSI_VID_SHADOW_CTRL_UNION;
#endif
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_en_START (0)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_en_END (0)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_req_START (8)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_req_END (8)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_pin_req_START (16)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_pin_req_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi_vcid_act : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DSI_DPI_VCID_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_VCID_ACT_dpi_vcid_act_START (0)
#define SOC_DSS_DSI_DPI_VCID_ACT_dpi_vcid_act_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi_color_coding_act : 4;
        unsigned int reserved_0 : 4;
        unsigned int loosely18_en_act : 1;
        unsigned int reserved_1 : 18;
        unsigned int reserved_2 : 5;
    } reg;
} SOC_DSS_DSI_DPI_COLOR_CODING_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_dpi_color_coding_act_START (0)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_dpi_color_coding_act_END (3)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_loosely18_en_act_START (8)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_loosely18_en_act_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int invact_lpcmd_time_act : 8;
        unsigned int reserved_0 : 8;
        unsigned int outvact_lpcmd_time_act : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_invact_lpcmd_time_act_START (0)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_invact_lpcmd_time_act_END (7)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_outvact_lpcmd_time_act_START (16)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_outvact_lpcmd_time_act_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_mode_type_act : 2;
        unsigned int reserved_0 : 6;
        unsigned int lp_vsa_en_act : 1;
        unsigned int lp_vbp_en_act : 1;
        unsigned int lp_vfp_en_act : 1;
        unsigned int lp_vact_en_act : 1;
        unsigned int lp_hbp_en_act : 1;
        unsigned int lp_hfp_en_act : 1;
        unsigned int frame_bta_ack_en_act : 1;
        unsigned int lp_cmd_en_act : 1;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_DSS_DSI_VID_MODE_CFG_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_vid_mode_type_act_START (0)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_vid_mode_type_act_END (1)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vsa_en_act_START (8)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vsa_en_act_END (8)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vbp_en_act_START (9)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vbp_en_act_END (9)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vfp_en_act_START (10)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vfp_en_act_END (10)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vact_en_act_START (11)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vact_en_act_END (11)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hbp_en_act_START (12)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hbp_en_act_END (12)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hfp_en_act_START (13)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hfp_en_act_END (13)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_frame_bta_ack_en_act_START (14)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_frame_bta_ack_en_act_END (14)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_cmd_en_act_START (15)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_cmd_en_act_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_pkt_size_act : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSI_VID_PKT_SIZE_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_vid_pkt_size_act_START (0)
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_vid_pkt_size_act_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_null_chunks_act : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_vid_null_chunks_act_START (0)
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_vid_null_chunks_act_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_null_size_act : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_DSI_VID_NULL_SIZE_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_vid_null_size_act_START (0)
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_vid_null_size_act_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_has_time_act : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DSI_VID_HSA_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_vid_has_time_act_START (0)
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_vid_has_time_act_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_hbp_time_act : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_DSI_VID_HBP_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_vid_hbp_time_act_START (0)
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_vid_hbp_time_act_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vid_hline_time_act : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_DSS_DSI_VID_HLINE_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_vid_hline_time_act_START (0)
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_vid_hline_time_act_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vsa_lines_act : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VSA_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_vsa_lines_act_START (0)
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_vsa_lines_act_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vbp_lines_act : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VBP_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_vbp_lines_act_START (0)
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_vbp_lines_act_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vfp_lines_act : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSI_VID_VFP_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_vfp_lines_act_START (0)
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_vfp_lines_act_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_active_lines_act : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_v_active_lines_act_START (0)
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_v_active_lines_act_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode_3d_act : 2;
        unsigned int format_3d_act : 2;
        unsigned int second_vsync_act : 1;
        unsigned int right_first_act : 1;
        unsigned int reserved_0 : 10;
        unsigned int send_3d_cfg_act : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_DSS_DSI_SDF_3D_ACT_UNION;
#endif
#define SOC_DSS_DSI_SDF_3D_ACT_mode_3d_act_START (0)
#define SOC_DSS_DSI_SDF_3D_ACT_mode_3d_act_END (1)
#define SOC_DSS_DSI_SDF_3D_ACT_format_3d_act_START (2)
#define SOC_DSS_DSI_SDF_3D_ACT_format_3d_act_END (3)
#define SOC_DSS_DSI_SDF_3D_ACT_second_vsync_act_START (4)
#define SOC_DSS_DSI_SDF_3D_ACT_second_vsync_act_END (4)
#define SOC_DSS_DSI_SDF_3D_ACT_right_first_act_START (5)
#define SOC_DSS_DSI_SDF_3D_ACT_right_first_act_END (5)
#define SOC_DSS_DSI_SDF_3D_ACT_send_3d_cfg_act_START (16)
#define SOC_DSS_DSI_SDF_3D_ACT_send_3d_cfg_act_END (16)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
