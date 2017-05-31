#ifndef __SOC_DSS_DSC_INTERFACE_H__
#define __SOC_DSS_DSC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_DSC_VERSION_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_DSC_PPS_IDENTIFIER_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_DSC_DSC_EN_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_DSC_DSC_CTRL_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_DSC_PIC_SIZE_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_DSC_SLICE_SIZE_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_DSC_CHUNK_SIZE_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_DSC_INITIAL_DELAY_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_DSC_RC_PARAM0_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_DSC_RC_PARAM1_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_DSC_RC_PARAM2_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_DSC_RC_PARAM3_ADDR(base) ((base) + (0x002C))
#define SOC_DSS_DSC_FLATNESS_QP_TH_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_DSC_RC_PARAM4_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_DSC_RC_PARAM5_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_DSC_RC_BUF_THRESH0_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_DSC_RC_BUF_THRESH1_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_DSC_RC_BUF_THRESH2_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_DSC_RC_BUF_THRESH3_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_DSC_RC_RANGE_PARAM0_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_DSC_RC_RANGE_PARAM1_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_DSC_RC_RANGE_PARAM2_ADDR(base) ((base) + (0x0054))
#define SOC_DSS_DSC_RC_RANGE_PARAM3_ADDR(base) ((base) + (0x0058))
#define SOC_DSS_DSC_RC_RANGE_PARAM4_ADDR(base) ((base) + (0x005C))
#define SOC_DSS_DSC_RC_RANGE_PARAM5_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_DSC_RC_RANGE_PARAM6_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_DSC_RC_RANGE_PARAM7_ADDR(base) ((base) + (0x0068))
#define SOC_DSS_DSC_ADJUSTMENT_BITS_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_DSC_BITS_PER_GRP_ADDR(base) ((base) + (0x0070))
#define SOC_DSS_DSC_MULTI_SLICE_CTL_ADDR(base) ((base) + (0x0074))
#define SOC_DSS_DSC_DSC_OUT_CTRL_ADDR(base) ((base) + (0x0078))
#define SOC_DSS_DSC_DSC_CLK_SEL_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_DSC_DSC_CLK_EN_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_DSC_DSC_MEM_CTRL_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_DSC_DSC_ST_DATAIN_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_DSC_DSC_ST_DATAOUT_ADDR(base) ((base) + (0x008C))
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_ADDR(base) ((base) + (0x0090))
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_ADDR(base) ((base) + (0x0094))
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_ADDR(base) ((base) + (0x0098))
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_ADDR(base) ((base) + (0x009C))
#define SOC_DSS_DSC_DSC0_ST_FIFO_ADDR(base) ((base) + (0x00A0))
#define SOC_DSS_DSC_DSC1_ST_FIFO_ADDR(base) ((base) + (0x00A4))
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_ADDR(base) ((base) + (0x00A8))
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_ADDR(base) ((base) + (0x00AC))
#define SOC_DSS_DSC_DSC_ST_ITFC_ADDR(base) ((base) + (0x00B0))
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_ADDR(base) ((base) + (0x00B4))
#define SOC_DSS_DSC_DSC_REG_DEFAULT_ADDR(base) ((base) + (0x00B8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_version_minor : 4;
        unsigned int dsc_version_major : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DSC_VERSION_UNION;
#endif
#define SOC_DSS_DSC_VERSION_dsc_version_minor_START (0)
#define SOC_DSS_DSC_VERSION_dsc_version_minor_END (3)
#define SOC_DSS_DSC_VERSION_dsc_version_major_START (4)
#define SOC_DSS_DSC_VERSION_dsc_version_major_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pps_identifier : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DSC_PPS_IDENTIFIER_UNION;
#endif
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_START (0)
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_en : 1;
        unsigned int dual_dsc_en : 1;
        unsigned int dsc_if_bypass : 1;
        unsigned int reset_ich_per_line : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DSC_DSC_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_EN_dsc_en_START (0)
#define SOC_DSS_DSC_DSC_EN_dsc_en_END (0)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_START (1)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_END (1)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_START (2)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_END (2)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_START (3)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bits_per_component : 4;
        unsigned int linebuf_depth : 4;
        unsigned int reserved_0 : 2;
        unsigned int block_pred_enable : 1;
        unsigned int convert_rgb : 1;
        unsigned int enable_422 : 1;
        unsigned int vbr_enable : 1;
        unsigned int reserved_1 : 2;
        unsigned int bits_per_pixel : 10;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_DSS_DSC_DSC_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_START (0)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_END (3)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_START (4)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_END (7)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_START (10)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_END (10)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_START (11)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_END (11)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_START (12)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_END (12)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_START (13)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_END (13)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_START (16)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pic_height : 16;
        unsigned int pic_width : 16;
    } reg;
} SOC_DSS_DSC_PIC_SIZE_UNION;
#endif
#define SOC_DSS_DSC_PIC_SIZE_pic_height_START (0)
#define SOC_DSS_DSC_PIC_SIZE_pic_height_END (15)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_START (16)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int slice_height : 16;
        unsigned int slice_width : 16;
    } reg;
} SOC_DSS_DSC_SLICE_SIZE_UNION;
#endif
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_START (0)
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_END (15)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_START (16)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int chunk_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DSC_CHUNK_SIZE_UNION;
#endif
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_START (0)
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int initial_xmit_delay : 10;
        unsigned int reserved : 6;
        unsigned int initial_dec_delay : 16;
    } reg;
} SOC_DSS_DSC_INITIAL_DELAY_UNION;
#endif
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_START (0)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_END (9)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_START (16)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int initial_scale_value : 6;
        unsigned int reserved : 10;
        unsigned int scale_increment_interval : 16;
    } reg;
} SOC_DSS_DSC_RC_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_START (0)
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_END (5)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_START (16)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scale_decrement_interval : 12;
        unsigned int reserved_0 : 4;
        unsigned int first_line_bpg_offset : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_DSS_DSC_RC_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_START (0)
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_END (11)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_START (16)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nfl_bpg_offset : 16;
        unsigned int slice_bpg_offset : 16;
    } reg;
} SOC_DSS_DSC_RC_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_START (0)
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_END (15)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_START (16)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int initial_offset : 16;
        unsigned int final_offset : 16;
    } reg;
} SOC_DSS_DSC_RC_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_START (0)
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_END (15)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_START (16)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flatness_min_qp : 8;
        unsigned int reserved_0 : 8;
        unsigned int flatness_max_qp : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSC_FLATNESS_QP_TH_UNION;
#endif
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_START (0)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_END (7)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_START (16)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rc_model_size : 16;
        unsigned int reserved_0 : 4;
        unsigned int rc_edge_factor : 4;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSC_RC_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_START (0)
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_END (15)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_START (20)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rc_quant_incr_limit0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int rc_quant_incr_limit1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int rc_tgt_offset_hi : 4;
        unsigned int rc_tgt_offset_lo : 4;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_DSS_DSC_RC_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_START (0)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_END (4)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_START (8)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_END (12)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_START (16)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_END (19)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_START (20)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rc_buf_thresh3 : 8;
        unsigned int rc_buf_thresh2 : 8;
        unsigned int rc_buf_thresh1 : 8;
        unsigned int rc_buf_thresh0 : 8;
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH0_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_START (0)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_END (7)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_START (8)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_END (15)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_START (16)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_END (23)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_START (24)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rc_buf_thresh7 : 8;
        unsigned int rc_buf_thresh6 : 8;
        unsigned int rc_buf_thresh5 : 8;
        unsigned int rc_buf_thresh4 : 8;
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH1_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_START (0)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_END (7)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_START (8)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_END (15)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_START (16)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_END (23)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_START (24)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rc_buf_thresh11 : 8;
        unsigned int rc_buf_thresh10 : 8;
        unsigned int rc_buf_thresh9 : 8;
        unsigned int rc_buf_thresh8 : 8;
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH2_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_START (0)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_END (7)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_START (8)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_END (15)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_START (16)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_END (23)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_START (24)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int rc_buf_thresh13 : 8;
        unsigned int rc_buf_thresh12 : 8;
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH3_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_START (16)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_END (23)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_START (24)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset1 : 6;
        unsigned int range_max_qp1 : 5;
        unsigned int range_min_qp1 : 5;
        unsigned int range_bpg_offset0 : 6;
        unsigned int range_max_qp0 : 5;
        unsigned int range_min_qp0 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset3 : 6;
        unsigned int range_max_qp3 : 5;
        unsigned int range_min_qp3 : 5;
        unsigned int range_bpg_offset2 : 6;
        unsigned int range_max_qp2 : 5;
        unsigned int range_min_qp2 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset5 : 6;
        unsigned int range_max_qp5 : 5;
        unsigned int range_min_qp5 : 5;
        unsigned int range_bpg_offset4 : 6;
        unsigned int range_max_qp4 : 5;
        unsigned int range_min_qp4 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset7 : 6;
        unsigned int range_max_qp7 : 5;
        unsigned int range_min_qp7 : 5;
        unsigned int range_bpg_offset6 : 6;
        unsigned int range_max_qp6 : 5;
        unsigned int range_min_qp6 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset9 : 6;
        unsigned int range_max_qp9 : 5;
        unsigned int range_min_qp9 : 5;
        unsigned int range_bpg_offset8 : 6;
        unsigned int range_max_qp8 : 5;
        unsigned int range_min_qp8 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset11 : 6;
        unsigned int range_max_qp11 : 5;
        unsigned int range_min_qp11 : 5;
        unsigned int range_bpg_offset10 : 6;
        unsigned int range_max_qp10 : 5;
        unsigned int range_min_qp10 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range_bpg_offset13 : 6;
        unsigned int range_max_qp13 : 5;
        unsigned int range_min_qp13 : 5;
        unsigned int range_bpg_offset12 : 6;
        unsigned int range_max_qp12 : 5;
        unsigned int range_min_qp12 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM6_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_START (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_END (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_START (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_END (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_START (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_END (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int range_bpg_offset14 : 6;
        unsigned int range_max_qp14 : 5;
        unsigned int range_min_qp14 : 5;
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM7_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_START (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_END (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_START (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_END (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_START (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int adjustment_bits : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DSC_ADJUSTMENT_BITS_UNION;
#endif
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_START (0)
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bits_per_grp : 6;
        unsigned int reserved_0 : 2;
        unsigned int adj_bits_per_grp : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_DSS_DSC_BITS_PER_GRP_UNION;
#endif
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_START (0)
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_END (5)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_START (8)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int slices_per_line : 2;
        unsigned int reserved : 14;
        unsigned int pic_line_grp_num : 16;
    } reg;
} SOC_DSS_DSC_MULTI_SLICE_CTL_UNION;
#endif
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_START (0)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_END (1)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_START (16)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_out_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DSC_DSC_OUT_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_START (0)
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_clk_sel : 32;
    } reg;
} SOC_DSS_DSC_DSC_CLK_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_START (0)
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_clk_en : 32;
    } reg;
} SOC_DSS_DSC_DSC_CLK_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_START (0)
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_mem_ctrl_0 : 4;
        unsigned int dsc_mem_ctrl_1 : 4;
        unsigned int dsc_mem_ctrl_2 : 4;
        unsigned int dsc_mem_ctrl_3 : 4;
        unsigned int dsc_mem_ctrl_4 : 4;
        unsigned int dsc_mem_ctrl_5 : 4;
        unsigned int dsc_mem_ctrl_6 : 4;
        unsigned int dsc_mem_ctrl_7 : 4;
    } reg;
} SOC_DSS_DSC_DSC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_START (0)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_END (3)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_START (4)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_END (7)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_START (8)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_END (11)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_START (12)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_END (15)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_START (16)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_END (19)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_START (20)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_END (23)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_START (24)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_END (27)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_START (28)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int datain_line_cnt : 12;
        unsigned int reserved_0 : 4;
        unsigned int datain_pix_cnt : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAIN_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_START (0)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_END (11)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_START (16)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dataout_line_cnt : 12;
        unsigned int reserved : 4;
        unsigned int dataout_byte_cnt : 16;
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAOUT_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_START (0)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_END (11)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_START (16)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc0_slice_line_cnt : 12;
        unsigned int reserved_0 : 4;
        unsigned int dsc0_slice_pix_cnt : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_START (0)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_END (11)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_START (16)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc1_slice_line_cnt : 12;
        unsigned int reserved_0 : 4;
        unsigned int dsc1_slice_pix_cnt : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_START (0)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_END (11)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_START (16)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc0_pic_line_cnt : 12;
        unsigned int reserved_0 : 4;
        unsigned int dsc0_pic_pix_cnt : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_START (0)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_END (11)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_START (16)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc1_pic_line_cnt : 12;
        unsigned int reserved_0 : 4;
        unsigned int dsc1_pic_pix_cnt : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_START (0)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_END (11)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_START (16)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc0_flatff_full : 1;
        unsigned int dsc0_flatff_empty : 1;
        unsigned int dsc0_blncff0_full : 1;
        unsigned int dsc0_blncff0_empty : 1;
        unsigned int dsc0_blncff1_full : 1;
        unsigned int dsc0_blncff1_empty : 1;
        unsigned int dsc0_sesizeff0_full : 1;
        unsigned int dsc0_sesizeff0_empty : 1;
        unsigned int dsc0_sesizeff1_full : 1;
        unsigned int dsc0_sesizeff1_empty : 1;
        unsigned int dsc0_rcbuf0_full : 1;
        unsigned int dsc0_rcbuf0_empty : 1;
        unsigned int dsc0_rcbuf1_full : 1;
        unsigned int dsc0_rcbuf1_empty : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSC_DSC0_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_START (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_END (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_START (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_END (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_START (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_END (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_START (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_END (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_START (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_END (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_START (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_END (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_START (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_END (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_START (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_END (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_START (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_END (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_START (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_END (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_START (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_END (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_START (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_END (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_START (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_END (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_START (13)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc1_flatff_full : 1;
        unsigned int dsc1_flatff_empty : 1;
        unsigned int dsc1_blncff0_full : 1;
        unsigned int dsc1_blncff0_empty : 1;
        unsigned int dsc1_blncff1_full : 1;
        unsigned int dsc1_blncff1_empty : 1;
        unsigned int dsc1_sesizeff0_full : 1;
        unsigned int dsc1_sesizeff0_empty : 1;
        unsigned int dsc1_sesizeff1_full : 1;
        unsigned int dsc1_sesizeff1_empty : 1;
        unsigned int dsc1_rcbuf0_full : 1;
        unsigned int dsc1_rcbuf0_empty : 1;
        unsigned int dsc1_rcbuf1_full : 1;
        unsigned int dsc1_rcbuf1_empty : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_DSC_DSC1_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_START (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_END (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_START (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_END (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_START (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_END (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_START (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_END (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_START (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_END (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_START (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_END (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_START (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_END (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_START (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_END (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_START (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_END (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_START (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_END (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_START (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_END (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_START (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_END (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_START (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_END (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_START (13)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc0_addr_linebuf : 10;
        unsigned int reserved_0 : 6;
        unsigned int dsc0_infifo_full : 1;
        unsigned int dsc0_infifo_empty : 1;
        unsigned int dsc0_infifo_uflow : 1;
        unsigned int dsc0_infifo_oflow : 1;
        unsigned int dsc0_outfifo_full : 1;
        unsigned int dsc0_outfifo_empty : 1;
        unsigned int dsc0_outfifo_uflow : 1;
        unsigned int dsc0_outfifo_oflow : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_START (0)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_END (9)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_START (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_END (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_START (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_END (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_START (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_END (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_START (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_END (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_START (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_END (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_START (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_END (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_START (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_END (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_START (23)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc1_addr_linebuf : 10;
        unsigned int reserved_0 : 6;
        unsigned int dsc1_infifo_full : 1;
        unsigned int dsc1_infifo_empty : 1;
        unsigned int dsc1_infifo_uflow : 1;
        unsigned int dsc1_infifo_oflow : 1;
        unsigned int dsc1_outfifo_full : 1;
        unsigned int dsc1_outfifo_empty : 1;
        unsigned int dsc1_outfifo_uflow : 1;
        unsigned int dsc1_outfifo_oflow : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_START (0)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_END (9)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_START (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_END (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_START (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_END (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_START (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_END (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_START (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_END (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_START (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_END (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_START (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_END (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_START (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_END (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_START (23)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc1_pre_drdy : 1;
        unsigned int dsc1_pre_dneed : 1;
        unsigned int dsc1_dv2pred : 1;
        unsigned int dsc1_nxt_dneed : 1;
        unsigned int dsc1_nxt_drdy : 1;
        unsigned int dsc0_pre_drdy : 1;
        unsigned int dsc0_pre_dneed : 1;
        unsigned int dsc0_dv2pred : 1;
        unsigned int dsc0_nxt_dneed : 1;
        unsigned int dsc0_nxt_drdy : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_DSS_DSC_DSC_ST_ITFC_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_START (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_END (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_START (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_END (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_START (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_END (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_START (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_END (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_START (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_END (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_START (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_END (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_START (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_END (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_START (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_END (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_START (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_END (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_START (9)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_START (0)
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsc_reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DSC_DSC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_START (0)
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
