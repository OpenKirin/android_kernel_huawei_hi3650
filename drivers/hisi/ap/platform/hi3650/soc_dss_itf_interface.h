#ifndef __SOC_DSS_ITF_INTERFACE_H__
#define __SOC_DSS_ITF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_ITF_LDI_VRT_CTRL0_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_ITF_LDI_VRT_CTRL1_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_ITF_LDI_VRT_CTRL2_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_ITF_LDI_PLR_CTRL_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_ITF_DSS_SH_MASK_INT_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_ITF_LDI_3D_CTRL_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_ITF_LDI_CTRL_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_ITF_LDI_WORK_MODE_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_ADDR(base) ((base) + (0x002C))
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_ITF_DSI_TE_CTRL_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_ITF_DSI_TE_HS_NUM_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_ITF_DSI_TE_HS_WD_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_ITF_DSI_TE_VS_WD_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_ITF_LDI_FRM_MSK_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_ITF_SRAM_LP_CTRL_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_ITF_ITF_RD_SHADOW_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_ADDR(base) ((base) + (0x00F0))
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_ADDR(base) ((base) + (0x00F4))
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_ADDR(base) ((base) + (0x00F8))
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_ADDR(base) ((base) + (0x00FC))
#define SOC_DSS_ITF_LDI_MEM_CTRL_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_ITF_LDI_CLK_SEL_ADDR(base) ((base) + (0x0108))
#define SOC_DSS_ITF_LDI_CLK_EN_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_ITF_LDI_IF_BYPASS_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_ITF_REG_DEFAULT_ADDR(base) ((base) + (0x0114))
#define SOC_DSS_ITF_FRM_VALID_DBG_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_ITF_CRC_DBG_ITF_ADDR(base) ((base) + (0x0200))
#define SOC_DSS_ITF_CRC_ITF_EN_ADDR(base) ((base) + (0x0204))
#define SOC_DSS_ITF_CRC_ITF_FRM_ADDR(base) ((base) + (0x0208))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi0_hfp : 13;
        unsigned int reserved_0: 3;
        unsigned int dpi0_hbp : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_START (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_END (12)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_START (16)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi0_hsw : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_START (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi0_hsize : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_START (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vfp : 13;
        unsigned int reserved_0: 3;
        unsigned int vbp : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_START (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_END (12)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_START (16)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vsw : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_START (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vsize : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_START (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vsync_plr : 1;
        unsigned int hsync_plr : 1;
        unsigned int pixel_clk_plr : 1;
        unsigned int data_en_plr : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_ITF_LDI_PLR_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_START (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_END (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_START (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_END (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_START (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_END (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_START (3)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_sh_mask_int : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_ITF_DSS_SH_MASK_INT_UNION;
#endif
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_START (0)
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int active_space : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_3D_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_START (0)
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_en : 1;
        unsigned int disp_mode_buf : 1;
        unsigned int data_gate_en : 1;
        unsigned int bpp : 2;
        unsigned int dual_mode_en : 1;
        unsigned int colorbar_width : 7;
        unsigned int bgr : 1;
        unsigned int color_mode : 1;
        unsigned int shutdown : 1;
        unsigned int split_mode : 1;
        unsigned int dpi0_rs_clear : 1;
        unsigned int dpi1_rs_clear : 1;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_ITF_LDI_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_START (0)
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_END (0)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_START (1)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_END (1)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_START (2)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_END (2)
#define SOC_DSS_ITF_LDI_CTRL_bpp_START (3)
#define SOC_DSS_ITF_LDI_CTRL_bpp_END (4)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_START (5)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_END (5)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_START (6)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_END (12)
#define SOC_DSS_ITF_LDI_CTRL_bgr_START (13)
#define SOC_DSS_ITF_LDI_CTRL_bgr_END (13)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_START (14)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_END (14)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_START (15)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_END (15)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_START (16)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_END (16)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_START (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_END (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_START (18)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int work_mode : 1;
        unsigned int colorbar_ort : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_ITF_LDI_WORK_MODE_UNION;
#endif
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_START (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_END (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_START (1)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int de_space_low : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION;
#endif
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_START (0)
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_halt_cmd_en : 1;
        unsigned int dsi_halt_video_en : 1;
        unsigned int dsi_wms_3d_mode : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_START (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_END (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_START (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_END (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_START (2)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_te_hard_en : 1;
        unsigned int dsi_te0_pin_p : 1;
        unsigned int dsi_te1_pin_p : 1;
        unsigned int dsi_te_hard_sel : 1;
        unsigned int dsi_te_tri_sel : 2;
        unsigned int dsi_te_pin_hd_sel : 2;
        unsigned int dsi_te_mask_en : 1;
        unsigned int dsi_te_mask_dis : 4;
        unsigned int dsi_te_mask_und : 4;
        unsigned int dsi_te_pin_en : 1;
        unsigned int reserved : 14;
    } reg;
} SOC_DSS_ITF_DSI_TE_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_START (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_END (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_START (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_END (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_START (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_END (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_START (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_END (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_START (4)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_END (5)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_START (6)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_END (7)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_START (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_END (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_START (9)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_END (12)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_START (13)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_END (16)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_START (17)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_te0_hs_num : 13;
        unsigned int dsi_te1_hs_num : 13;
        unsigned int reserved : 6;
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_NUM_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_START (0)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_END (12)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_START (13)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_te0_hs_wd : 12;
        unsigned int dsi_te1_hs_wd : 12;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_START (0)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_END (11)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_START (12)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_te0_vs_wd : 12;
        unsigned int dsi_te1_vs_wd : 12;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_ITF_DSI_TE_VS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_START (0)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_END (11)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_START (12)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_msk_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int frm_msk : 8;
        unsigned int frm_unmsk : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_START (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_END (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_START (8)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_END (15)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_START (16)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int single_frm_update : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_START (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_vinact_msk_len : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION;
#endif
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_START (0)
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_cmd_event_sel : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_START (0)
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_in_vfp : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_SRAM_LP_CTRL_UNION;
#endif
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_START (0)
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itf_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_ITF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_START (0)
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int dpi1_hbp : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_START (16)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi1_hsw : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_START (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi1_hsize : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_START (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpi0_overlap_size : 8;
        unsigned int reserved_0 : 8;
        unsigned int dpi1_overlap_size : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION;
#endif
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_START (0)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_END (7)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_START (16)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_ITF_LDI_MEM_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_START (0)
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_clk_sel : 32;
    } reg;
} SOC_DSS_ITF_LDI_CLK_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_START (0)
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_clk_en : 32;
    } reg;
} SOC_DSS_ITF_LDI_CLK_EN_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_START (0)
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ldi_if_bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_LDI_IF_BYPASS_UNION;
#endif
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_START (0)
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frm_valid_dbg : 32;
    } reg;
} SOC_DSS_ITF_FRM_VALID_DBG_UNION;
#endif
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_START (0)
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_itf : 32;
    } reg;
} SOC_DSS_ITF_CRC_DBG_ITF_UNION;
#endif
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_START (0)
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_itf_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_ITF_CRC_ITF_EN_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_START (0)
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_itf_frm : 32;
    } reg;
} SOC_DSS_ITF_CRC_ITF_FRM_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_START (0)
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
