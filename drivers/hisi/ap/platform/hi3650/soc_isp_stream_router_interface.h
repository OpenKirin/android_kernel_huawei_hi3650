#ifndef __SOC_ISP_STREAM_ROUTER_INTERFACE_H__
#define __SOC_ISP_STREAM_ROUTER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_ADDR(base) ((base) + (0x0))
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_ADDR(base) ((base) + (0x4))
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_ADDR(base) ((base) + (0x8))
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_ADDR(base) ((base) + (0xC))
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_ADDR(base) ((base) + (0x10))
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_ADDR(base) ((base) + (0x14))
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_ADDR(base) ((base) + (0x18))
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_ADDR(base) ((base) + (0x1C))
#define SOC_ISP_STREAM_ROUTER_REFORMAT_ADDR(base,ReformatRange) ((base) + (0x20+0x8*(ReformatRange)))
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_ADDR(base,ReformatRange) ((base) + (0x24+0x8*(ReformatRange)))
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_ADDR(base) ((base) + (0x60))
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_ADDR(base) ((base) + (0x64))
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_ADDR(base,LR_Range) ((base) + (0x68+0x4*(LR_Range)))
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_ADDR(base) ((base) + (0x74))
#define SOC_ISP_STREAM_ROUTER_DPCM_ADDR(base) ((base) + (0x78))
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_ADDR(base) ((base) + (0x7C))
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_ADDR(base) ((base) + (0x80))
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_ADDR(base) ((base) + (0x84))
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_ADDR(base) ((base) + (0x88))
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_ADDR(base) ((base) + (0x8C))
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_ADDR(base) ((base) + (0x90))
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_ADDR(base) ((base) + (0x94))
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_ADDR(base) ((base) + (0x98))
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_ADDR(base) ((base) + (0x9C))
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_ADDR(base) ((base) + (0x100))
#define SOC_ISP_STREAM_ROUTER_CROPV_ADDR(base,Range2) ((base) + (0x104+0x8*(Range2)))
#define SOC_ISP_STREAM_ROUTER_CROPH_ADDR(base,Range2) ((base) + (0x108+0x8*(Range2)))
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x120))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csia_data_type_0 : 6;
        unsigned int csia_virtual_ch_0 : 2;
        unsigned int csia_data_type_1 : 6;
        unsigned int csia_virtual_ch_1 : 2;
        unsigned int csia_data_type_2 : 6;
        unsigned int csia_virtual_ch_2 : 2;
        unsigned int csia_data_type_3 : 6;
        unsigned int csia_virtual_ch_3 : 2;
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_A_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_0_START (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_0_END (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_0_START (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_0_END (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_1_START (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_1_END (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_1_START (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_1_END (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_2_START (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_2_END (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_2_START (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_2_END (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_3_START (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_3_END (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_3_START (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csib_data_type_0 : 6;
        unsigned int csib_virtual_ch_0 : 2;
        unsigned int csib_data_type_1 : 6;
        unsigned int csib_virtual_ch_1 : 2;
        unsigned int csib_data_type_2 : 6;
        unsigned int csib_virtual_ch_2 : 2;
        unsigned int csib_data_type_3 : 6;
        unsigned int csib_virtual_ch_3 : 2;
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_B_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_0_START (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_0_END (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_0_START (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_0_END (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_1_START (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_1_END (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_1_START (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_1_END (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_2_START (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_2_END (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_2_START (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_2_END (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_3_START (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_3_END (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_3_START (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csic_data_type_0 : 6;
        unsigned int csic_virtual_ch_0 : 2;
        unsigned int csic_data_type_1 : 6;
        unsigned int csic_virtual_ch_1 : 2;
        unsigned int csic_data_type_2 : 6;
        unsigned int csic_virtual_ch_2 : 2;
        unsigned int csic_data_type_3 : 6;
        unsigned int csic_virtual_ch_3 : 2;
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_C_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_0_START (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_0_END (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_0_START (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_0_END (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_1_START (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_1_END (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_1_START (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_1_END (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_2_START (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_2_END (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_2_START (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_2_END (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_3_START (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_3_END (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_3_START (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filter_go : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_START (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pressure_threshold_start_a : 7;
        unsigned int reserved_0 : 1;
        unsigned int pressure_threshold_start_b : 7;
        unsigned int reserved_1 : 1;
        unsigned int pressure_threshold_start_c : 7;
        unsigned int reserved_2 : 8;
        unsigned int pressure_enable : 1;
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_START (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_END (6)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_START (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_END (14)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_c_START (16)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_c_END (22)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_START (31)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pressure_threshold_stop_a : 4;
        unsigned int reserved_0 : 4;
        unsigned int pressure_threshold_stop_b : 4;
        unsigned int reserved_1 : 4;
        unsigned int pressure_threshold_stop_c : 4;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_START (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_END (3)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_START (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_END (11)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_c_START (16)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_c_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int idr_input_stream_0 : 4;
        unsigned int idr_enable_0 : 1;
        unsigned int reserved_0 : 3;
        unsigned int idr_input_stream_1 : 4;
        unsigned int idr_enable_1 : 1;
        unsigned int reserved_1 : 3;
        unsigned int idr_input_stream_2 : 4;
        unsigned int idr_enable_2 : 1;
        unsigned int reserved_2 : 3;
        unsigned int idr_input_stream_3 : 4;
        unsigned int idr_enable_3 : 1;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_0_START (0)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_0_END (3)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_0_START (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_0_END (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_1_START (8)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_1_END (11)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_1_START (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_1_END (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_2_START (16)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_2_END (19)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_2_START (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_2_END (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_3_START (24)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_3_END (27)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_3_START (28)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int idr_input_stream_4 : 4;
        unsigned int idr_enable_4 : 1;
        unsigned int reserved_0 : 3;
        unsigned int idr_input_stream_5 : 4;
        unsigned int idr_enable_5 : 1;
        unsigned int reserved_1 : 3;
        unsigned int idr_input_stream_6 : 4;
        unsigned int idr_enable_6 : 1;
        unsigned int reserved_2 : 3;
        unsigned int idr_input_stream_7 : 4;
        unsigned int idr_enable_7 : 1;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_4_START (0)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_4_END (3)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_4_START (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_4_END (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_5_START (8)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_5_END (11)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_5_START (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_5_END (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_START (16)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_END (19)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_START (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_END (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_START (24)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_END (27)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_START (28)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reformat_num_lines : 13;
        unsigned int reformat_pixel_reorder : 3;
        unsigned int reformat_num_pixels : 13;
        unsigned int reserved : 2;
        unsigned int enable : 1;
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_lines_START (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_lines_END (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_pixel_reorder_START (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_pixel_reorder_END (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_pixels_START (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_pixels_END (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_enable_START (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reformat_min_vertical_space : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_reformat_min_vertical_space_START (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_reformat_min_vertical_space_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int eol_num_lines_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int eol_num_lines_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_EOL_CNT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_0_START (0)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_0_END (12)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_1_START (16)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int last_line : 12;
        unsigned int reserved_0: 4;
        unsigned int location : 2;
        unsigned int reserved_1: 14;
    } reg;
} SOC_ISP_STREAM_ROUTER_PROCESSING_IR_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_last_line_START (0)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_last_line_END (11)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_location_START (16)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_location_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lr_left_size : 12;
        unsigned int reserved_0 : 4;
        unsigned int lr_overlap : 7;
        unsigned int reserved_1 : 9;
    } reg;
} SOC_ISP_STREAM_ROUTER_PROCESSING_LR_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_left_size_START (0)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_left_size_END (11)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_overlap_START (16)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_overlap_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lbm_threshold_0 : 9;
        unsigned int reserved_0 : 7;
        unsigned int lbm_threshold_1 : 9;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_0_START (0)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_0_END (8)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_1_START (16)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_1_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 14;
        unsigned int dpcm_enable_0 : 1;
        unsigned int dpcm_format_0 : 1;
        unsigned int reserved_1 : 14;
        unsigned int dpcm_enable_1 : 1;
        unsigned int dpcm_format_1 : 1;
    } reg;
} SOC_ISP_STREAM_ROUTER_DPCM_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_0_START (14)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_0_END (14)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_0_START (15)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_0_END (15)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_1_START (30)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_1_END (30)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_1_START (31)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpr_input_vp_0 : 4;
        unsigned int vpr_enable_0 : 1;
        unsigned int reserved_0 : 3;
        unsigned int vpr_input_vp_1 : 4;
        unsigned int vpr_enable_1 : 1;
        unsigned int reserved_1 : 3;
        unsigned int vpr_input_vp_2 : 4;
        unsigned int vpr_enable_2 : 1;
        unsigned int reserved_2 : 3;
        unsigned int vpr_input_vp_3 : 4;
        unsigned int vpr_enable_3 : 1;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_0_START (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_0_END (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_0_START (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_0_END (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_1_START (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_1_END (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_1_START (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_1_END (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_2_START (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_2_END (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_2_START (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_2_END (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_3_START (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_3_END (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_3_START (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpr_input_vp_4 : 4;
        unsigned int vpr_enable_4 : 1;
        unsigned int reserved_0 : 3;
        unsigned int vpr_input_vp_5 : 4;
        unsigned int vpr_enable_5 : 1;
        unsigned int reserved_1 : 3;
        unsigned int vpr_input_vp_6 : 4;
        unsigned int vpr_enable_6 : 1;
        unsigned int reserved_2 : 3;
        unsigned int vpr_input_vp_7 : 4;
        unsigned int vpr_enable_7 : 1;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_START (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_END (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_START (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_END (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_5_START (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_5_END (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_5_START (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_5_END (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_START (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_END (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_START (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_END (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_START (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_END (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_START (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpr_input_vp_8 : 4;
        unsigned int vpr_enable_8 : 1;
        unsigned int reserved_0 : 3;
        unsigned int vpr_input_vp_9 : 4;
        unsigned int vpr_enable_9 : 1;
        unsigned int reserved_1 : 3;
        unsigned int vpr_input_vp_10 : 4;
        unsigned int vpr_enable_10 : 1;
        unsigned int reserved_2 : 3;
        unsigned int vpr_input_vp_11 : 4;
        unsigned int vpr_enable_11 : 1;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_8_START (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_8_END (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_8_START (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_8_END (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_9_START (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_9_END (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_9_START (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_9_END (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_10_START (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_10_END (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_10_START (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_10_END (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_11_START (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_11_END (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_11_START (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_11_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpr_input_vp_12 : 4;
        unsigned int vpr_enable_12 : 1;
        unsigned int reserved_0 : 3;
        unsigned int vpr_input_vp_13 : 4;
        unsigned int vpr_enable_13 : 1;
        unsigned int reserved_1 : 3;
        unsigned int vpr_input_vp_14 : 4;
        unsigned int vpr_enable_14 : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 8;
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_12_START (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_12_END (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_12_START (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_12_END (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_13_START (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_13_END (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_13_START (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_13_END (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_START (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_END (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_START (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma3_out : 1;
        unsigned int dma2_out : 1;
        unsigned int dma1_out : 1;
        unsigned int fe2_out : 1;
        unsigned int fe1_out : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_START (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_END (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_START (1)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_END (1)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma1_out_START (2)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma1_out_END (2)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe2_out_START (3)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe2_out_END (3)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe1_out_START (4)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe1_out_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peak_fifo_id : 3;
        unsigned int reserved_0 : 5;
        unsigned int peak_enable : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_ISP_STREAM_ROUTER_PEAK_CTRL_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_fifo_id_START (0)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_fifo_id_END (2)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_enable_START (8)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_enable_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peak_fifo_status : 12;
        unsigned int reserved : 17;
        unsigned int csi_afifo_status : 3;
    } reg;
} SOC_ISP_STREAM_ROUTER_PEAK_STATUS_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_peak_fifo_status_START (0)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_peak_fifo_status_END (11)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_csi_afifo_status_START (29)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_csi_afifo_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bp_source_a : 2;
        unsigned int bp_source_b : 2;
        unsigned int bp_source_c : 2;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_STREAM_ROUTER_BP_SOURCE_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_START (0)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_END (1)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_START (2)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_END (3)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_c_START (4)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_c_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pressure_threshold_start_dfs_b : 12;
        unsigned int reserved_0 : 3;
        unsigned int bp_extension_b_enable : 1;
        unsigned int pressure_threshold_start_dfs_c : 12;
        unsigned int reserved_1 : 3;
        unsigned int bp_extension_c_enable : 1;
    } reg;
} SOC_ISP_STREAM_ROUTER_BP_EXTENSION_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_b_START (0)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_b_END (11)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_b_enable_START (15)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_b_enable_END (15)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_c_START (16)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_c_END (27)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_c_enable_START (31)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_c_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfs_granularity : 10;
        unsigned int dfs_trig_wait_before : 2;
        unsigned int dfs_enable : 11;
        unsigned int dfs_trig_wait_after : 9;
    } reg;
} SOC_ISP_STREAM_ROUTER_DFS_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_granularity_START (0)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_granularity_END (9)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_before_START (10)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_before_END (11)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_enable_START (12)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_enable_END (22)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_after_START (23)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_after_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cropv_start_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int cropv_end_0 : 13;
        unsigned int reserved_1 : 2;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_ISP_STREAM_ROUTER_CROPV_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_start_0_START (0)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_start_0_END (12)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_end_0_START (16)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_end_0_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int croph_start_0 : 12;
        unsigned int reserved_0 : 4;
        unsigned int croph_end_0 : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_ISP_STREAM_ROUTER_CROPH_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_start_0_START (0)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_start_0_END (11)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_end_0_START (16)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_end_0_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_clk_on : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_force_clk_on_START (0)
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_force_clk_on_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
