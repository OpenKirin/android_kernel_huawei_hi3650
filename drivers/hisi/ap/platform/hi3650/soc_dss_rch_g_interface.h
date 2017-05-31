#ifndef __SOC_DSS_RCH_G_INTERFACE_H__
#define __SOC_DSS_RCH_G_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_RCH_G_DMA_OFT_X0_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_RCH_G_DMA_OFT_Y0_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_RCH_G_DMA_OFT_X1_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_RCH_G_DMA_OFT_Y1_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_RCH_G_DMA_MASK0_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_RCH_G_DMA_MASK1_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_RCH_G_DMA_CTRL_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_RCH_G_DMA_PULSE_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_RCH_G_RWCH_CFG0_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_RCH_G_DMA_STRIDE0_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_ADDR(base) ((base) + (0x0068))
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_RCH_G_DMA_TEST0_ADDR(base) ((base) + (0x0070))
#define SOC_DSS_RCH_G_DMA_TEST1_ADDR(base) ((base) + (0x0074))
#define SOC_DSS_RCH_G_DMA_TEST3_ADDR(base) ((base) + (0x0078))
#define SOC_DSS_RCH_G_DMA_TEST4_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_RCH_G_DMA_STATUS_Y_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_RCH_G_CH_RD_SHADOW_ADDR(base) ((base) + (0x00D0))
#define SOC_DSS_RCH_G_CH_CTL_ADDR(base) ((base) + (0x00D4))
#define SOC_DSS_RCH_G_CH_SECU_EN_ADDR(base) ((base) + (0x00D8))
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ADDR(base) ((base) + (0x00DC))
#define SOC_DSS_RCH_G_CH_CLK_SEL_ADDR(base) ((base) + (0x00E0))
#define SOC_DSS_RCH_G_CH_CLK_EN_ADDR(base) ((base) + (0x00E4))
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_ADDR(base) ((base) + (0x0104))
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_ADDR(base) ((base) + (0x0108))
#define SOC_DSS_RCH_G_DFC_DISP_FMT_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_ADDR(base) ((base) + (0x0114))
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_ADDR(base) ((base) + (0x011C))
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_ADDR(base) ((base) + (0x0120))
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_ADDR(base) ((base) + (0x0124))
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_ADDR(base) ((base) + (0x0200))
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_ADDR(base) ((base) + (0x0204))
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_ADDR(base) ((base) + (0x0208))
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_ADDR(base) ((base) + (0x020C))
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0210))
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0214))
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_ADDR(base) ((base) + (0x0218))
#define SOC_DSS_RCH_G_SCF_EN_HSCL_ADDR(base) ((base) + (0x021C))
#define SOC_DSS_RCH_G_SCF_EN_VSCL_ADDR(base) ((base) + (0x0220))
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_ADDR(base) ((base) + (0x0224))
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_ADDR(base) ((base) + (0x0228))
#define SOC_DSS_RCH_G_SCF_INC_HSCL_ADDR(base) ((base) + (0x0234))
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_ADDR(base) ((base) + (0x0238))
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_ADDR(base) ((base) + (0x023C))
#define SOC_DSS_RCH_G_SCF_INC_VSCL_ADDR(base) ((base) + (0x0248))
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_ADDR(base) ((base) + (0x024C))
#define SOC_DSS_RCH_G_SCF_EN_MMP_ADDR(base) ((base) + (0x027C))
#define SOC_DSS_RCH_G_SCF_DB_H0_ADDR(base) ((base) + (0x0280))
#define SOC_DSS_RCH_G_SCF_DB_H1_ADDR(base) ((base) + (0x0284))
#define SOC_DSS_RCH_G_SCF_DB_V0_ADDR(base) ((base) + (0x0288))
#define SOC_DSS_RCH_G_SCF_DB_V1_ADDR(base) ((base) + (0x028C))
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_ADDR(base) ((base) + (0x0290))
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_ADDR(base) ((base) + (0x03A0))
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_ADDR(base) ((base) + (0x03B0))
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_ADDR(base) ((base) + (0x03B4))
#define SOC_DSS_RCH_G_POST_CLIP_EN_ADDR(base) ((base) + (0x03B8))
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ADDR(base) ((base) + (0x600))
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_ADDR(base) ((base) + (0x0800))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_ADDR(base) ((base) + (0x0804))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_ADDR(base) ((base) + (0x0808))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_ADDR(base) ((base) + (0x080C))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_ADDR(base) ((base) + (0x0810))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_ADDR(base) ((base) + (0x814))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_ADDR(base) ((base) + (0x818))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_ADDR(base) ((base) + (0x81C))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_ADDR(base) ((base) + (0x820))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_ADDR(base) ((base) + (0x824))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_ADDR(base) ((base) + (0x828))
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_ADDR(base) ((base) + (0x82C))
#define SOC_DSS_RCH_G_DMA_REQ_END_ADDR(base) ((base) + (0x830))
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_ADDR(base) ((base) + (0x834))
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_ADDR(base) ((base) + (0x838))
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_ADDR(base) ((base) + (0x83C))
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_ADDR(base) ((base) + (0x840))
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_ADDR(base) ((base) + (0x844))
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_ADDR(base) ((base) + (0x848))
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_ADDR(base) ((base) + (0x84C))
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_ADDR(base) ((base) + (0x850))
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_ADDR(base) ((base) + (0x0854))
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_ADDR(base) ((base) + (0x0900))
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_ADDR(base) ((base) + (0x0904))
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_ADDR(base) ((base) + (0x090C))
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_ADDR(base) ((base) + (0x0910))
#define SOC_DSS_RCH_G_AFBCD_CTL_ADDR(base) ((base) + (0x0914))
#define SOC_DSS_RCH_G_AFBCD_STR_ADDR(base) ((base) + (0x0918))
#define SOC_DSS_RCH_G_LINE_CROP_ADDR(base) ((base) + (0x091C))
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_ADDR(base) ((base) + (0x0920))
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_ADDR(base) ((base) + (0x0924))
#define SOC_DSS_RCH_G_MM_BASE_0_ADDR(base) ((base) + (0x0928))
#define SOC_DSS_RCH_G_MM_BASE_1_ADDR(base) ((base) + (0x092C))
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_ADDR(base) ((base) + (0x0930))
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_ADDR(base) ((base) + (0x0934))
#define SOC_DSS_RCH_G_OS_CFG_ADDR(base) ((base) + (0x0938))
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_ADDR(base) ((base) + (0x093C))
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_ADDR(base) ((base) + (0x0940))
#define SOC_DSS_RCH_G_REG_DEFAULT_ADDR(base) ((base) + (0x0A00))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_x0 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_RCH_G_DMA_OFT_X0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_X0_dma_oft_x0_START (0)
#define SOC_DSS_RCH_G_DMA_OFT_X0_dma_oft_x0_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_y0 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_DMA_OFT_Y0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_Y0_dma_oft_y0_START (0)
#define SOC_DSS_RCH_G_DMA_OFT_Y0_dma_oft_y0_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_x1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_RCH_G_DMA_OFT_X1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_X1_dma_oft_x1_START (0)
#define SOC_DSS_RCH_G_DMA_OFT_X1_dma_oft_x1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_y1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_DMA_OFT_Y1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_OFT_Y1_dma_oft_y1_START (0)
#define SOC_DSS_RCH_G_DMA_OFT_Y1_dma_oft_y1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_mask_y0 : 16;
        unsigned int dma_mask_x0 : 12;
        unsigned int reserved : 4;
    } reg;
} SOC_DSS_RCH_G_DMA_MASK0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_y0_START (0)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_y0_END (15)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_x0_START (16)
#define SOC_DSS_RCH_G_DMA_MASK0_dma_mask_x0_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_mask_y1 : 16;
        unsigned int dma_mask_x1 : 12;
        unsigned int reserved : 4;
    } reg;
} SOC_DSS_RCH_G_DMA_MASK1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_y1_START (0)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_y1_END (15)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_x1_START (16)
#define SOC_DSS_RCH_G_DMA_MASK1_dma_mask_x1_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stretch_size_vrt : 13;
        unsigned int dma_line_skip_step : 6;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_START (0)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_END (12)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_START (13)
#define SOC_DSS_RCH_G_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_page_8k : 1;
        unsigned int dma_tile_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int dma_pix_fmt : 5;
        unsigned int dma_va_en : 1;
        unsigned int dma_mirror_hrz_en : 1;
        unsigned int dma_mirror_vrt_en : 1;
        unsigned int dma_rot : 1;
        unsigned int dma_stretch_en : 1;
        unsigned int reserved_1 : 4;
        unsigned int dma_mask_en : 1;
        unsigned int dma_phy_scrambl_4 : 1;
        unsigned int dma_phy_scrambl_3 : 1;
        unsigned int dma_phy_scrambl_2 : 1;
        unsigned int dma_phy_scrambl_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int dma_cross_128 : 1;
        unsigned int dma_tile_128byte_en : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 6;
    } reg;
} SOC_DSS_RCH_G_DMA_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_CTRL_dma_page_8k_START (0)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_page_8k_END (0)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_en_START (1)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_en_END (1)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_pix_fmt_START (3)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_pix_fmt_END (7)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_va_en_START (8)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_va_en_END (8)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_hrz_en_START (9)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_hrz_en_END (9)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_vrt_en_START (10)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mirror_vrt_en_END (10)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_rot_START (11)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_rot_END (11)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_stretch_en_START (12)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_stretch_en_END (12)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mask_en_START (17)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_mask_en_END (17)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_4_START (18)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_4_END (18)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_3_START (19)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_3_END (19)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_2_START (20)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_2_END (20)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_1_START (21)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_phy_scrambl_1_END (21)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_cross_128_START (23)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_cross_128_END (23)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_128byte_en_START (24)
#define SOC_DSS_RCH_G_DMA_CTRL_dma_tile_128byte_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_tile_scrambling_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DMA_TILE_SCRAM_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_dma_tile_scrambling_en_START (0)
#define SOC_DSS_RCH_G_DMA_TILE_SCRAM_dma_tile_scrambling_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_pulse : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DMA_PULSE_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_PULSE_dma_pulse_START (0)
#define SOC_DSS_RCH_G_DMA_PULSE_dma_pulse_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwch_cfg0 : 32;
    } reg;
} SOC_DSS_RCH_G_RWCH_CFG0_UNION;
#endif
#define SOC_DSS_RCH_G_RWCH_CFG0_rwch_cfg0_START (0)
#define SOC_DSS_RCH_G_RWCH_CFG0_rwch_cfg0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_addr0 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_DATA_ADDR0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_dma_addr0_START (0)
#define SOC_DSS_RCH_G_DMA_DATA_ADDR0_dma_addr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stride0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int dma_l2t_interleave_n0 : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_DSS_RCH_G_DMA_STRIDE0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_stride0_START (0)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_stride0_END (12)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_l2t_interleave_n0_START (16)
#define SOC_DSS_RCH_G_DMA_STRIDE0_dma_l2t_interleave_n0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stretch_stride0 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_dma_stretch_stride0_START (0)
#define SOC_DSS_RCH_G_DMA_STRETCH_STRIDE0_dma_stretch_stride0_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_data_num0 : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_RCH_G_DMA_DATA_NUM0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_dma_data_num0_START (0)
#define SOC_DSS_RCH_G_DMA_DATA_NUM0_dma_data_num0_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test0_y : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_TEST0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST0_dma_test0_y_START (0)
#define SOC_DSS_RCH_G_DMA_TEST0_dma_test0_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test1_y : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_TEST1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST1_dma_test1_y_START (0)
#define SOC_DSS_RCH_G_DMA_TEST1_dma_test1_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test3_y : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_TEST3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST3_dma_test3_y_START (0)
#define SOC_DSS_RCH_G_DMA_TEST3_dma_test3_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test4_y : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_TEST4_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_TEST4_dma_test4_y_START (0)
#define SOC_DSS_RCH_G_DMA_TEST4_dma_test4_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_status_y : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_STATUS_Y_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_STATUS_Y_dma_status_y_START (0)
#define SOC_DSS_RCH_G_DMA_STATUS_Y_dma_status_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwch_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_CH_RD_SHADOW_UNION;
#endif
#define SOC_DSS_RCH_G_CH_RD_SHADOW_rwch_rd_shadow_START (0)
#define SOC_DSS_RCH_G_CH_RD_SHADOW_rwch_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_en : 1;
        unsigned int ch_version_sel : 1;
        unsigned int ch_afbcd_en : 1;
        unsigned int ch_block_en : 1;
        unsigned int reserved_0 : 8;
        unsigned int ch_frm_end_dly : 4;
        unsigned int ch_block_h : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_CH_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CTL_ch_en_START (0)
#define SOC_DSS_RCH_G_CH_CTL_ch_en_END (0)
#define SOC_DSS_RCH_G_CH_CTL_ch_version_sel_START (1)
#define SOC_DSS_RCH_G_CH_CTL_ch_version_sel_END (1)
#define SOC_DSS_RCH_G_CH_CTL_ch_afbcd_en_START (2)
#define SOC_DSS_RCH_G_CH_CTL_ch_afbcd_en_END (2)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_en_START (3)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_en_END (3)
#define SOC_DSS_RCH_G_CH_CTL_ch_frm_end_dly_START (12)
#define SOC_DSS_RCH_G_CH_CTL_ch_frm_end_dly_END (15)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_h_START (16)
#define SOC_DSS_RCH_G_CH_CTL_ch_block_h_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_secu_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_CH_SECU_EN_UNION;
#endif
#define SOC_DSS_RCH_G_CH_SECU_EN_ch_secu_en_START (0)
#define SOC_DSS_RCH_G_CH_SECU_EN_ch_secu_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_sw_end_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_CH_SW_END_REQ_UNION;
#endif
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ch_sw_end_req_START (0)
#define SOC_DSS_RCH_G_CH_SW_END_REQ_ch_sw_end_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_clk_sel : 32;
    } reg;
} SOC_DSS_RCH_G_CH_CLK_SEL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CLK_SEL_ch_clk_sel_START (0)
#define SOC_DSS_RCH_G_CH_CLK_SEL_ch_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_clk_en : 32;
    } reg;
} SOC_DSS_RCH_G_CH_CLK_EN_UNION;
#endif
#define SOC_DSS_RCH_G_CH_CLK_EN_ch_clk_en_START (0)
#define SOC_DSS_RCH_G_CH_CLK_EN_ch_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_size_vrt : 13;
        unsigned int reserved_0 : 3;
        unsigned int dfc_size_hrz : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_DFC_DISP_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_vrt_START (0)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_vrt_END (12)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_hrz_START (16)
#define SOC_DSS_RCH_G_DFC_DISP_SIZE_dfc_size_hrz_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_pix_in_num : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DFC_PIX_IN_NUM_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_dfc_pix_in_num_START (0)
#define SOC_DSS_RCH_G_DFC_PIX_IN_NUM_dfc_pix_in_num_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_glb_alpha1 : 8;
        unsigned int dfc_glb_alpha0 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_DFC_GLB_ALPHA_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha1_START (0)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha1_END (7)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha0_START (8)
#define SOC_DSS_RCH_G_DFC_GLB_ALPHA_dfc_glb_alpha0_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_ax_swap : 1;
        unsigned int dfc_img_fmt : 5;
        unsigned int dfc_uv_swap : 1;
        unsigned int dfc_rb_swap : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_RCH_G_DFC_DISP_FMT_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_ax_swap_START (0)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_ax_swap_END (0)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_img_fmt_START (1)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_img_fmt_END (5)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_uv_swap_START (6)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_uv_swap_END (6)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_rb_swap_START (7)
#define SOC_DSS_RCH_G_DFC_DISP_FMT_dfc_rb_swap_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_right_clip : 6;
        unsigned int reserved_0 : 10;
        unsigned int dfc_left_clip : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_right_clip_START (0)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_right_clip_END (5)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_left_clip_START (16)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_HRZ_dfc_left_clip_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_bot_clip : 6;
        unsigned int reserved_0 : 10;
        unsigned int dfc_top_clip : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_bot_clip_START (0)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_bot_clip_END (5)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_top_clip_START (16)
#define SOC_DSS_RCH_G_DFC_CLIP_CTL_VRZ_dfc_top_clip_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_ctl_clip_enable : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_START (0)
#define SOC_DSS_RCH_G_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_module_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DFC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_dfc_module_en_START (0)
#define SOC_DSS_RCH_G_DFC_ICG_MODULE_dfc_module_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_dither_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DFC_DITHER_ENABLE_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_dfc_dither_en_START (0)
#define SOC_DSS_RCH_G_DFC_DITHER_ENABLE_dfc_dither_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_left_pad : 4;
        unsigned int reserved_0 : 4;
        unsigned int dfc_right_pad : 4;
        unsigned int reserved_1 : 4;
        unsigned int dfc_top_pad : 4;
        unsigned int reserved_2 : 4;
        unsigned int dfc_bot_pad : 4;
        unsigned int reserved_3 : 3;
        unsigned int dfc_ctl_pad_enable : 1;
    } reg;
} SOC_DSS_RCH_G_DFC_PADDING_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_left_pad_START (0)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_left_pad_END (3)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_right_pad_START (8)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_right_pad_END (11)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_top_pad_START (16)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_top_pad_END (19)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_bot_pad_START (24)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_bot_pad_END (27)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_ctl_pad_enable_START (31)
#define SOC_DSS_RCH_G_DFC_PADDING_CTL_dfc_ctl_pad_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_hscl_str : 1;
        unsigned int scf_en_hscl_str_a : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_HSCL_STR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_START (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_END (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_a_START (1)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_STR_scf_en_hscl_str_a_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_vscl_str : 1;
        unsigned int scf_en_vscl_str_a : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_VSCL_STR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_START (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_END (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_a_START (1)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_STR_scf_en_vscl_str_a_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_h_v_order : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_SCF_H_V_ORDER_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_scf_h_v_order_START (0)
#define SOC_DSS_RCH_G_SCF_H_V_ORDER_scf_h_v_order_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_a_core_gt : 1;
        unsigned int scf_r_core_gt : 1;
        unsigned int scf_g_core_gt : 1;
        unsigned int scf_b_core_gt : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_RCH_G_SCF_CH_CORE_GT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_a_core_gt_START (0)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_a_core_gt_END (0)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_r_core_gt_START (1)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_r_core_gt_END (1)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_g_core_gt_START (2)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_g_core_gt_END (2)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_b_core_gt_START (3)
#define SOC_DSS_RCH_G_SCF_CH_CORE_GT_scf_b_core_gt_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_input_height : 13;
        unsigned int reserved_0 : 3;
        unsigned int scf_input_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_START (0)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_END (12)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_START (16)
#define SOC_DSS_RCH_G_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_output_height : 13;
        unsigned int reserved_0 : 3;
        unsigned int scf_output_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_START (0)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_END (12)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_START (16)
#define SOC_DSS_RCH_G_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_hcoef_mem_ctrl : 4;
        unsigned int scf_vcoef_mem_ctrl : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_START (0)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_END (3)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_START (4)
#define SOC_DSS_RCH_G_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_hscl_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_HSCL_scf_en_hscl_en_START (0)
#define SOC_DSS_RCH_G_SCF_EN_HSCL_scf_en_hscl_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_vscl_en : 1;
        unsigned int scf_out_buffer_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_en_vscl_en_START (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_en_vscl_en_END (0)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_out_buffer_en_START (1)
#define SOC_DSS_RCH_G_SCF_EN_VSCL_scf_out_buffer_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_hscl : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_scf_acc_hscl_START (0)
#define SOC_DSS_RCH_G_SCF_ACC_HSCL_scf_acc_hscl_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_hscl1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_HSCL1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_scf_acc_hscl1_START (0)
#define SOC_DSS_RCH_G_SCF_ACC_HSCL1_scf_acc_hscl1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_inc_hscl : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_RCH_G_SCF_INC_HSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INC_HSCL_scf_inc_hscl_START (0)
#define SOC_DSS_RCH_G_SCF_INC_HSCL_scf_inc_hscl_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_vscl : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_scf_acc_vscl_START (0)
#define SOC_DSS_RCH_G_SCF_ACC_VSCL_scf_acc_vscl_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_vscl1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_RCH_G_SCF_ACC_VSCL1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_scf_acc_vscl1_START (0)
#define SOC_DSS_RCH_G_SCF_ACC_VSCL1_scf_acc_vscl1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_inc_vscl : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_RCH_G_SCF_INC_VSCL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_INC_VSCL_scf_inc_vscl_START (0)
#define SOC_DSS_RCH_G_SCF_INC_VSCL_scf_inc_vscl_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_sw_rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_NONLINEAR_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_scf_sw_rst_START (0)
#define SOC_DSS_RCH_G_SCF_EN_NONLINEAR_scf_sw_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_mmp : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_SCF_EN_MMP_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_EN_MMP_scf_en_mmp_START (0)
#define SOC_DSS_RCH_G_SCF_EN_MMP_scf_en_mmp_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_h0 : 32;
    } reg;
} SOC_DSS_RCH_G_SCF_DB_H0_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_H0_scf_debug_h0_START (0)
#define SOC_DSS_RCH_G_SCF_DB_H0_scf_debug_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_h1 : 32;
    } reg;
} SOC_DSS_RCH_G_SCF_DB_H1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_H1_scf_debug_h1_START (0)
#define SOC_DSS_RCH_G_SCF_DB_H1_scf_debug_h1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_v0 : 32;
    } reg;
} SOC_DSS_RCH_G_SCF_DB_V0_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_V0_scf_debug_v0_START (0)
#define SOC_DSS_RCH_G_SCF_DB_V0_scf_debug_v0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_v1 : 32;
    } reg;
} SOC_DSS_RCH_G_SCF_DB_V1_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_DB_V1_scf_debug_v1_START (0)
#define SOC_DSS_RCH_G_SCF_DB_V1_scf_debug_v1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_lb_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_START (0)
#define SOC_DSS_RCH_G_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int post_clip_size_vrt : 13;
        unsigned int reserved_0 : 3;
        unsigned int post_clip_size_hrz : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_vrt_START (0)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_vrt_END (12)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_hrz_START (16)
#define SOC_DSS_RCH_G_POST_CLIP_DISP_SIZE_post_clip_size_hrz_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int post_clip_right : 6;
        unsigned int reserved_0 : 10;
        unsigned int post_clip_left : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_right_START (0)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_right_END (5)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_left_START (16)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_HRZ_post_clip_left_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int post_clip_bot : 6;
        unsigned int reserved_0 : 10;
        unsigned int post_clip_top : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_bot_START (0)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_bot_END (5)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_top_START (16)
#define SOC_DSS_RCH_G_POST_CLIP_CTL_VRZ_post_clip_top_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int post_clip_enable : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_POST_CLIP_EN_UNION;
#endif
#define SOC_DSS_RCH_G_POST_CLIP_EN_post_clip_enable_START (0)
#define SOC_DSS_RCH_G_POST_CLIP_EN_post_clip_enable_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_debug_sel : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_RCH_G_CH_DEBUG_SEL_UNION;
#endif
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ch_debug_sel_START (0)
#define SOC_DSS_RCH_G_CH_DEBUG_SEL_ch_debug_sel_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_os_cfg : 6;
        unsigned int reserved_0 : 2;
        unsigned int dma_buf_qos_mask : 1;
        unsigned int dma_buf_cont_mask : 1;
        unsigned int dma_buf_l_e_mask : 1;
        unsigned int reserved_1 : 21;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_os_cfg_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_os_cfg_END (5)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_qos_mask_START (8)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_qos_mask_END (8)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_cont_mask_START (9)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_cont_mask_END (9)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_l_e_mask_START (10)
#define SOC_DSS_RCH_G_DMA_BUF_CTRL_dma_buf_l_e_mask_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_ctl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_START_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_dma_buf_cpu_start_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_START_dma_buf_cpu_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_addr : 9;
        unsigned int reserved : 22;
        unsigned int dma_buf_cpu_rw : 1;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_END (8)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_START (31)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata0 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata1 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata2 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata3 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata0 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata1 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata2 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata3 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_req_end : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_DMA_REQ_END_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_REQ_END_dma_req_end_START (0)
#define SOC_DSS_RCH_G_DMA_REQ_END_dma_req_end_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbgcfg : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBGCFG_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_dma_buf_dbgcfg_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBGCFG_dma_buf_dbgcfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg0 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG0_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_dma_buf_dbg0_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG0_dma_buf_dbg0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg1 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG1_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_dma_buf_dbg1_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG1_dma_buf_dbg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg2 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG2_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_dma_buf_dbg2_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG2_dma_buf_dbg2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg3 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG3_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_dma_buf_dbg3_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG3_dma_buf_dbg3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg4 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG4_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_dma_buf_dbg4_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG4_dma_buf_dbg4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg5 : 32;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_DBG5_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_dma_buf_dbg5_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_DBG5_dma_buf_dbg5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_img_width : 13;
        unsigned int reserved_0 : 3;
        unsigned int dma_buf_img_height : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_SIZE_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_width_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_width_END (12)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_height_START (16)
#define SOC_DSS_RCH_G_DMA_BUF_SIZE_dma_buf_img_height_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_START (0)
#define SOC_DSS_RCH_G_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_hdr_ptr_lo : 32;
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_afbcd_hdr_ptr_lo_START (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_HDR_PTR_LO_afbcd_hdr_ptr_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_pic_width : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_afbcd_pic_width_START (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_WIDTH_afbcd_pic_width_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_pic_height : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_afbcd_pic_height_START (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_PIC_HEIGHT_afbcd_pic_height_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_block_split : 1;
        unsigned int reserved_0 : 15;
        unsigned int reserved_1 : 5;
        unsigned int afbcd_color_transform : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_block_split_START (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_block_split_END (0)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_color_transform_START (21)
#define SOC_DSS_RCH_G_AFBCD_HREG_FORMAT_afbcd_color_transform_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int afbcd_half_block_mode : 2;
        unsigned int reserved_6 : 24;
    } reg;
} SOC_DSS_RCH_G_AFBCD_CTL_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_CTL_afbcd_half_block_mode_START (6)
#define SOC_DSS_RCH_G_AFBCD_CTL_afbcd_half_block_mode_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_stretch_inc : 8;
        unsigned int afbcd_stretch_acc : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_RCH_G_AFBCD_STR_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_inc_START (0)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_inc_END (7)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_acc_START (8)
#define SOC_DSS_RCH_G_AFBCD_STR_afbcd_stretch_acc_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_bottom_crop_num : 4;
        unsigned int afbcd_top_crop_num : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_RCH_G_LINE_CROP_UNION;
#endif
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_bottom_crop_num_START (0)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_bottom_crop_num_END (3)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_top_crop_num_START (4)
#define SOC_DSS_RCH_G_LINE_CROP_afbcd_top_crop_num_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_header_stride : 14;
        unsigned int afbcd_header_start_pos : 2;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_UNION;
#endif
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_stride_START (0)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_stride_END (13)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_start_pos_START (14)
#define SOC_DSS_RCH_G_INPUT_HEADER_STRIDE_afbcd_header_start_pos_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_payload_stride : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_afbcd_payload_stride_START (0)
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_STRIDE_afbcd_payload_stride_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_mm_base_0 : 32;
    } reg;
} SOC_DSS_RCH_G_MM_BASE_0_UNION;
#endif
#define SOC_DSS_RCH_G_MM_BASE_0_afbcd_mm_base_0_START (0)
#define SOC_DSS_RCH_G_MM_BASE_0_afbcd_mm_base_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_mm_base_1 : 32;
    } reg;
} SOC_DSS_RCH_G_MM_BASE_1_UNION;
#endif
#define SOC_DSS_RCH_G_MM_BASE_1_afbcd_mm_base_1_START (0)
#define SOC_DSS_RCH_G_MM_BASE_1_afbcd_mm_base_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_payload_ptr : 32;
    } reg;
} SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_afbcd_payload_ptr_START (0)
#define SOC_DSS_RCH_G_AFBCD_PAYLOAD_POINTER_afbcd_payload_ptr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_pic_height_bf_stretch : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_RCH_G_HEIGHT_BF_STR_UNION;
#endif
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_afbcd_pic_height_bf_stretch_START (0)
#define SOC_DSS_RCH_G_HEIGHT_BF_STR_afbcd_pic_height_bf_stretch_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_mmrd_os : 4;
        unsigned int afbcd_mmwr_os : 4;
        unsigned int afbcd_ddrr_os : 6;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_RCH_G_OS_CFG_UNION;
#endif
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmrd_os_START (0)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmrd_os_END (3)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmwr_os_START (4)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_mmwr_os_END (7)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_ddrr_os_START (8)
#define SOC_DSS_RCH_G_OS_CFG_afbcd_ddrr_os_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_mem_ctrl_0 : 4;
        unsigned int afbcd_mem_ctrl_1 : 4;
        unsigned int afbcd_mem_ctrl_2 : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_RCH_G_AFBCD_MEM_CTRL_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_0_START (0)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_0_END (3)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_1_START (4)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_1_END (7)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_2_START (8)
#define SOC_DSS_RCH_G_AFBCD_MEM_CTRL_afbcd_mem_ctrl_2_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd_scramble_mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_UNION;
#endif
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_afbcd_scramble_mode_START (0)
#define SOC_DSS_RCH_G_AFBCD_SCRAMBLE_MODE_afbcd_scramble_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_RCH_G_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_RCH_G_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_RCH_G_REG_DEFAULT_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
