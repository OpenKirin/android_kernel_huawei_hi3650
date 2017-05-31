#ifndef __SOC_ISP_CVDR_INTERFACE_H__
#define __SOC_ISP_CVDR_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_CVDR_CVDR_CFG_ADDR(base) ((base) + (0x0))
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_ADDR(base) ((base) + (0x4))
#define SOC_ISP_CVDR_CVDR_DEBUG_ADDR(base) ((base) + (0x8))
#define SOC_ISP_CVDR_CVDR_QOS_CFG_ADDR(base) ((base) + (0xC))
#define SOC_ISP_CVDR_NR_WR_CFG_ADDR(base) ((base) + (0x10))
#define SOC_ISP_CVDR_NR_RD_CFG_ADDR(base,NR_RD_NBR_range,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_WR_CFG_ADDR(base,VP_WR_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR_range)))
#define SOC_ISP_CVDR_VP_WR_AXI_FS_ADDR(base,VP_WR_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x4+0x10*(VP_WR_NBR_range)))
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_ADDR(base,VP_WR_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x8+0x10*(VP_WR_NBR_range)))
#define SOC_ISP_CVDR_VP_WR_PREFETCH_ADDR(base,VP_WR_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0xC+0x10*(VP_WR_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_CFG_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_LWG_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x4+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_FHG_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x8+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_AXI_FS_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0xC+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x10+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_VP_RD_PREFETCH_ADDR(base,VP_WR_NBR,VP_RD_NBR_range,NR_RD_NBR,NR_WR_NBR) ((base) + (0x10+0x4*(NR_WR_NBR)+0x4*(NR_RD_NBR)+0x10*(VP_WR_NBR)+0x14+0x20*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_DEBUG_ADDR(base,Range4) ((base) + (0x310+0x4*(Range4)))
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_ADDR(base) ((base) + (0x320))
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_ADDR(base,NR_RD_NBR_range) ((base) + (0x330+0x4*(NR_RD_NBR_range)))
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_ADDR(base,VP_WR_NBR_range) ((base) + (0x350+0x4*(VP_WR_NBR_range)))
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_ADDR(base,VP_RD_NBR_range) ((base) + (0x400+0x4*(VP_RD_NBR_range)))
#define SOC_ISP_CVDR_SPARE_ADDR(base,Range4) ((base) + (0x430+0x4*(Range4)))
#define SOC_ISP_CVDR_OTHER_RO_ADDR(base) ((base) + (0x440))
#define SOC_ISP_CVDR_OTHER_RW_ADDR(base) ((base) + (0x444))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int du_write_threshold : 6;
        unsigned int reserved_0 : 2;
        unsigned int stall_srt_du_threshold : 8;
        unsigned int max_axiread_id : 5;
        unsigned int reserved_1 : 3;
        unsigned int max_axiwrite_tx : 5;
        unsigned int reserved_2 : 3;
    } reg;
} SOC_ISP_CVDR_CVDR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CFG_du_write_threshold_START (0)
#define SOC_ISP_CVDR_CVDR_CFG_du_write_threshold_END (5)
#define SOC_ISP_CVDR_CVDR_CFG_stall_srt_du_threshold_START (8)
#define SOC_ISP_CVDR_CVDR_CFG_stall_srt_du_threshold_END (15)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiread_id_START (16)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiread_id_END (20)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiwrite_tx_START (24)
#define SOC_ISP_CVDR_CVDR_CFG_max_axiwrite_tx_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_peak_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int rd_peak_en : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_EN_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_wr_peak_en_START (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_wr_peak_en_END (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_rd_peak_en_START (8)
#define SOC_ISP_CVDR_CVDR_DEBUG_EN_rd_peak_en_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_peak : 8;
        unsigned int rd_peak : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_wr_peak_START (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_wr_peak_END (7)
#define SOC_ISP_CVDR_CVDR_DEBUG_rd_peak_START (8)
#define SOC_ISP_CVDR_CVDR_DEBUG_rd_peak_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_qos_rt_default : 2;
        unsigned int rd_qos_threshold_11 : 3;
        unsigned int rd_qos_threshold_10 : 3;
        unsigned int rd_qos_threshold_01 : 3;
        unsigned int rd_qos_sr : 2;
        unsigned int rd_pressure_value : 2;
        unsigned int wr_qos_threshold_11 : 4;
        unsigned int wr_qos_threshold_10 : 4;
        unsigned int wr_qos_threshold_01 : 4;
        unsigned int wr_qos_sr : 2;
        unsigned int wr_pressure_value : 2;
        unsigned int wr_pressure_cvdr_mask : 1;
    } reg;
} SOC_ISP_CVDR_CVDR_QOS_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_rt_default_START (0)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_rt_default_END (1)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_11_START (2)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_11_END (4)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_10_START (5)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_10_END (7)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_01_START (8)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_threshold_01_END (10)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_sr_START (11)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_qos_sr_END (12)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_pressure_value_START (13)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_rd_pressure_value_END (14)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_11_START (15)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_11_END (18)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_10_START (19)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_10_END (22)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_01_START (23)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_threshold_01_END (26)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_sr_START (27)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_qos_sr_END (28)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_value_START (29)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_value_END (30)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_cvdr_mask_START (31)
#define SOC_ISP_CVDR_CVDR_QOS_CFG_wr_pressure_cvdr_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 9;
        unsigned int nrwr_access_limiter : 4;
        unsigned int reserved_1 : 18;
        unsigned int nrwr_enable : 1;
    } reg;
} SOC_ISP_CVDR_NR_WR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_access_limiter_START (9)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_access_limiter_END (12)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_enable_START (31)
#define SOC_ISP_CVDR_NR_WR_CFG_nrwr_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 5;
        unsigned int nrrd_allocated_du : 5;
        unsigned int nrrd_access_limiter : 4;
        unsigned int reserved_1 : 17;
        unsigned int nrrd_enable : 1;
    } reg;
} SOC_ISP_CVDR_NR_RD_CFG_UNION;
#endif
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_allocated_du_START (5)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_allocated_du_END (9)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_access_limiter_START (10)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_access_limiter_END (13)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_enable_START (31)
#define SOC_ISP_CVDR_NR_RD_CFG_nrrd_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpwr_pixel_format : 4;
        unsigned int vpwr_pixel_expansion : 1;
        unsigned int reserved_0 : 4;
        unsigned int vpwr_access_limiter : 4;
        unsigned int reserved_1 : 2;
        unsigned int vpwr_last_page : 17;
    } reg;
} SOC_ISP_CVDR_VP_WR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_format_START (0)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_format_END (3)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_expansion_START (4)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_pixel_expansion_END (4)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_access_limiter_START (9)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_access_limiter_END (12)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_last_page_START (15)
#define SOC_ISP_CVDR_VP_WR_CFG_vpwr_last_page_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int vpwr_address_frame_start : 28;
    } reg;
} SOC_ISP_CVDR_VP_WR_AXI_FS_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_AXI_FS_vpwr_address_frame_start_START (4)
#define SOC_ISP_CVDR_VP_WR_AXI_FS_vpwr_address_frame_start_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpwr_line_stride : 10;
        unsigned int reserved_0 : 5;
        unsigned int vpwr_line_wrap : 14;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_CVDR_VP_WR_AXI_LINE_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_stride_START (0)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_stride_END (9)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_wrap_START (15)
#define SOC_ISP_CVDR_VP_WR_AXI_LINE_vpwr_line_wrap_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vpwr_index_id0 : 7;
        unsigned int reserved_0 : 1;
        unsigned int vpwr_index_id1 : 7;
        unsigned int reserved_1 : 16;
        unsigned int vpwr_prefetch_bypass : 1;
    } reg;
} SOC_ISP_CVDR_VP_WR_PREFETCH_UNION;
#endif
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id0_START (0)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id0_END (6)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id1_START (8)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_index_id1_END (14)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_prefetch_bypass_START (31)
#define SOC_ISP_CVDR_VP_WR_PREFETCH_vpwr_prefetch_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vprd_pixel_format : 4;
        unsigned int vprd_pixel_expansion : 1;
        unsigned int vprd_allocated_du : 5;
        unsigned int vprd_access_limiter : 4;
        unsigned int reserved : 1;
        unsigned int vprd_last_page : 17;
    } reg;
} SOC_ISP_CVDR_VP_RD_CFG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_format_START (0)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_format_END (3)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_expansion_START (4)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_pixel_expansion_END (4)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_allocated_du_START (5)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_allocated_du_END (9)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_access_limiter_START (10)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_access_limiter_END (13)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_last_page_START (15)
#define SOC_ISP_CVDR_VP_RD_CFG_vprd_last_page_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vprd_line_size : 13;
        unsigned int reserved_0 : 3;
        unsigned int vprd_horizontal_blanking : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_ISP_CVDR_VP_RD_LWG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_line_size_START (0)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_line_size_END (12)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_horizontal_blanking_START (16)
#define SOC_ISP_CVDR_VP_RD_LWG_vprd_horizontal_blanking_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vprd_frame_size : 13;
        unsigned int reserved_0 : 3;
        unsigned int vprd_vertical_blanking : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_ISP_CVDR_VP_RD_FHG_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_frame_size_START (0)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_frame_size_END (12)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_vertical_blanking_START (16)
#define SOC_ISP_CVDR_VP_RD_FHG_vprd_vertical_blanking_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int vprd_axi_frame_start : 28;
    } reg;
} SOC_ISP_CVDR_VP_RD_AXI_FS_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_AXI_FS_vprd_axi_frame_start_START (4)
#define SOC_ISP_CVDR_VP_RD_AXI_FS_vprd_axi_frame_start_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vprd_line_stride : 10;
        unsigned int reserved_0 : 6;
        unsigned int vprd_line_wrap : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_CVDR_VP_RD_AXI_LINE_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_stride_START (0)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_stride_END (9)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_wrap_START (16)
#define SOC_ISP_CVDR_VP_RD_AXI_LINE_vprd_line_wrap_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vprd_index_id0 : 7;
        unsigned int reserved_0 : 1;
        unsigned int vprd_index_id1 : 7;
        unsigned int reserved_1 : 16;
        unsigned int vprd_prefetch_bypass : 1;
    } reg;
} SOC_ISP_CVDR_VP_RD_PREFETCH_UNION;
#endif
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id0_START (0)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id0_END (6)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id1_START (8)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_index_id1_END (14)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_prefetch_bypass_START (31)
#define SOC_ISP_CVDR_VP_RD_PREFETCH_vprd_prefetch_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debug_info : 32;
    } reg;
} SOC_ISP_CVDR_DEBUG_UNION;
#endif
#define SOC_ISP_CVDR_DEBUG_debug_info_START (0)
#define SOC_ISP_CVDR_DEBUG_debug_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nr_wr_mid : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_CVDR_AXI_CFG_NR_WR_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_nr_wr_mid_START (0)
#define SOC_ISP_CVDR_AXI_CFG_NR_WR_nr_wr_mid_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nr_rd_mid : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_CVDR_AXI_CFG_NR_RD_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_nr_rd_mid_START (0)
#define SOC_ISP_CVDR_AXI_CFG_NR_RD_nr_rd_mid_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vp_wr_mid : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_CVDR_AXI_CFG_VP_WR_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_vp_wr_mid_START (0)
#define SOC_ISP_CVDR_AXI_CFG_VP_WR_vp_wr_mid_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vp_rd_mid : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_CVDR_AXI_CFG_VP_RD_UNION;
#endif
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_vp_rd_mid_START (0)
#define SOC_ISP_CVDR_AXI_CFG_VP_RD_vp_rd_mid_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spare : 32;
    } reg;
} SOC_ISP_CVDR_SPARE_UNION;
#endif
#define SOC_ISP_CVDR_SPARE_spare_START (0)
#define SOC_ISP_CVDR_SPARE_spare_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int other_ro : 32;
    } reg;
} SOC_ISP_CVDR_OTHER_RO_UNION;
#endif
#define SOC_ISP_CVDR_OTHER_RO_other_ro_START (0)
#define SOC_ISP_CVDR_OTHER_RO_other_ro_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int other_rw : 32;
    } reg;
} SOC_ISP_CVDR_OTHER_RW_UNION;
#endif
#define SOC_ISP_CVDR_OTHER_RW_other_rw_START (0)
#define SOC_ISP_CVDR_OTHER_RW_other_rw_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
