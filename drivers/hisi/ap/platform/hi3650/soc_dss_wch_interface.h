#ifndef __SOC_DSS_WCH_INTERFACE_H__
#define __SOC_DSS_WCH_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_WCH_DMA_OFT_X0_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_WCH_DMA_OFT_Y0_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_WCH_DMA_OFT_X1_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_WCH_DMA_OFT_Y1_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_WCH_DMA_MASK0_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_WCH_DMA_MASK1_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_WCH_DMA_CTRL_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_WCH_DMA_TILE_SCRAM_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_WCH_DMA_PULSE_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_WCH_RWCH_CFG0_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_WCH_DMA_FIFO_CLR_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_WCH_DMA_COUNTER_DGB_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_WCH_DMA_ROT_BURST4_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_WCH_DMA_RSV1_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_WCH_DMA_RSV2_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_WCH_DMA_SW_MASK_EN_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_WCH_DMA_START_MASK0_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_WCH_DMA_END_MASK0_ADDR(base) ((base) + (0x0054))
#define SOC_DSS_WCH_DMA_START_MASK1_ADDR(base) ((base) + (0x0058))
#define SOC_DSS_WCH_DMA_END_MASK1_ADDR(base) ((base) + (0x005C))
#define SOC_DSS_WCH_DMA_DATA_ADDR0_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_WCH_DMA_STRIDE0_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_ADDR(base) ((base) + (0x0068))
#define SOC_DSS_WCH_DMA_DATA_NUM0_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_WCH_DMA_TEST0_ADDR(base) ((base) + (0x0070))
#define SOC_DSS_WCH_DMA_TEST1_ADDR(base) ((base) + (0x0074))
#define SOC_DSS_WCH_DMA_TEST3_ADDR(base) ((base) + (0x0078))
#define SOC_DSS_WCH_DMA_TEST4_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_WCH_DMA_STATUS_Y_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_WCH_DMA_DATA_ADDR1_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_WCH_DMA_STRIDE1_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_ADDR(base) ((base) + (0x008C))
#define SOC_DSS_WCH_DMA_DATA_NUM1_ADDR(base) ((base) + (0x0090))
#define SOC_DSS_WCH_DMA_TEST0_U_ADDR(base) ((base) + (0x0094))
#define SOC_DSS_WCH_DMA_TEST1_U_ADDR(base) ((base) + (0x0098))
#define SOC_DSS_WCH_DMA_TEST3_U_ADDR(base) ((base) + (0x009C))
#define SOC_DSS_WCH_DMA_TEST4_U_ADDR(base) ((base) + (0x00A0))
#define SOC_DSS_WCH_DMA_STATUS_U_ADDR(base) ((base) + (0x00A4))
#define SOC_DSS_WCH_CH_RD_SHADOW_ADDR(base) ((base) + (0x00D0))
#define SOC_DSS_WCH_CH_CTL_ADDR(base) ((base) + (0x00D4))
#define SOC_DSS_WCH_CH_SECU_EN_ADDR(base) ((base) + (0x00D8))
#define SOC_DSS_WCH_CH_SW_END_REQ_ADDR(base) ((base) + (0x00DC))
#define SOC_DSS_WCH_CH_CLK_SEL_ADDR(base) ((base) + (0x00E0))
#define SOC_DSS_WCH_CH_CLK_EN_ADDR(base) ((base) + (0x00E4))
#define SOC_DSS_WCH_DFC_DISP_SIZE_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_ADDR(base) ((base) + (0x0104))
#define SOC_DSS_WCH_DFC_GLB_ALPHA_ADDR(base) ((base) + (0x0108))
#define SOC_DSS_WCH_DFC_DISP_FMT_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_ADDR(base) ((base) + (0x0114))
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_WCH_DFC_ICG_MODULE_ADDR(base) ((base) + (0x011C))
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_ADDR(base) ((base) + (0x0120))
#define SOC_DSS_WCH_DFC_PADDING_CTL_ADDR(base) ((base) + (0x0124))
#define SOC_DSS_WCH_CSC_IDC_ADDR(base) ((base) + (0x0500))
#define SOC_DSS_WCH_CSC_ODC_ADDR(base) ((base) + (0x0504))
#define SOC_DSS_WCH_CSC_P0_ADDR(base) ((base) + (0x0508))
#define SOC_DSS_WCH_CSC_P1_ADDR(base) ((base) + (0x050C))
#define SOC_DSS_WCH_CSC_P2_ADDR(base) ((base) + (0x0510))
#define SOC_DSS_WCH_CSC_P3_ADDR(base) ((base) + (0x0514))
#define SOC_DSS_WCH_CSC_P4_ADDR(base) ((base) + (0x0518))
#define SOC_DSS_WCH_CSC_ICG_MODULE_ADDR(base) ((base) + (0x051C))
#define SOC_DSS_WCH_ROT_FIRST_LNS_ADDR(base) ((base) + (0x0530))
#define SOC_DSS_WCH_ROT_STATE_ADDR(base) ((base) + (0x0534))
#define SOC_DSS_WCH_ROT_MEM_CTRL_ADDR(base) ((base) + (0x0538))
#define SOC_DSS_WCH_ROT_SIZE_ADDR(base) ((base) + (0x053C))
#define SOC_DSS_WCH_ROT_CPU_CTL0_ADDR(base) ((base) + (0x0540))
#define SOC_DSS_WCH_ROT_CPU_START0_ADDR(base) ((base) + (0x0544))
#define SOC_DSS_WCH_ROT_CPU_ADDR0_ADDR(base) ((base) + (0x0548))
#define SOC_DSS_WCH_ROT_CPU_RDATA0_ADDR(base) ((base) + (0x054C))
#define SOC_DSS_WCH_ROT_CPU_RDATA1_ADDR(base) ((base) + (0x0550))
#define SOC_DSS_WCH_ROT_CPU_WDATA0_ADDR(base) ((base) + (0x0554))
#define SOC_DSS_WCH_ROT_CPU_WDATA1_ADDR(base) ((base) + (0x0558))
#define SOC_DSS_WCH_ROT_CPU_CTL1_ADDR(base) ((base) + (0x055C))
#define SOC_DSS_WCH_ROT_CPU_START1_ADDR(base) ((base) + (0x0560))
#define SOC_DSS_WCH_ROT_CPU_ADDR1_ADDR(base) ((base) + (0x0564))
#define SOC_DSS_WCH_ROT_CPU_RDATA2_ADDR(base) ((base) + (0x0568))
#define SOC_DSS_WCH_ROT_CPU_RDATA3_ADDR(base) ((base) + (0x056C))
#define SOC_DSS_WCH_ROT_CPU_WDATA2_ADDR(base) ((base) + (0x0570))
#define SOC_DSS_WCH_ROT_CPU_WDATA3_ADDR(base) ((base) + (0x0574))
#define SOC_DSS_WCH_CH_DEBUG_SEL_ADDR(base) ((base) + (0x600))
#define SOC_DSS_WCH_DMA_BUF_CTRL_ADDR(base) ((base) + (0x0800))
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_ADDR(base) ((base) + (0x0804))
#define SOC_DSS_WCH_DMA_BUF_CPU_START_ADDR(base) ((base) + (0x0808))
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_ADDR(base) ((base) + (0x080C))
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_ADDR(base) ((base) + (0x0810))
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_ADDR(base) ((base) + (0x814))
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_ADDR(base) ((base) + (0x818))
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_ADDR(base) ((base) + (0x81C))
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_ADDR(base) ((base) + (0x820))
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_ADDR(base) ((base) + (0x824))
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_ADDR(base) ((base) + (0x828))
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_ADDR(base) ((base) + (0x82C))
#define SOC_DSS_WCH_DMA_REQ_END_ADDR(base) ((base) + (0x830))
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_ADDR(base) ((base) + (0x834))
#define SOC_DSS_WCH_DMA_BUF_DBG0_ADDR(base) ((base) + (0x838))
#define SOC_DSS_WCH_DMA_BUF_DBG1_ADDR(base) ((base) + (0x83C))
#define SOC_DSS_WCH_DMA_BUF_DBG2_ADDR(base) ((base) + (0x840))
#define SOC_DSS_WCH_DMA_BUF_DBG3_ADDR(base) ((base) + (0x844))
#define SOC_DSS_WCH_DMA_BUF_DBG4_ADDR(base) ((base) + (0x848))
#define SOC_DSS_WCH_DMA_BUF_DBG5_ADDR(base) ((base) + (0x84C))
#define SOC_DSS_WCH_DMA_BUF_SIZE_ADDR(base) ((base) + (0x850))
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_ADDR(base) ((base) + (0x0854))
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_ADDR(base) ((base) + (0x0900))
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_ADDR(base) ((base) + (0x0904))
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_ADDR(base) ((base) + (0x0908))
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_ADDR(base) ((base) + (0x090C))
#define SOC_DSS_WCH_PICTURE_SIZE_ADDR(base) ((base) + (0x0910))
#define SOC_DSS_WCH_AFBCE_CTL_ADDR(base) ((base) + (0x0914))
#define SOC_DSS_WCH_HEADER_SRTIDE_ADDR(base) ((base) + (0x0918))
#define SOC_DSS_WCH_PAYLOAD_STRIDE_ADDR(base) ((base) + (0x091C))
#define SOC_DSS_WCH_ENC_OS_CFG_ADDR(base) ((base) + (0x0920))
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_ADDR(base) ((base) + (0x0924))
#define SOC_DSS_WCH_AFBCE_QOS_CFG_ADDR(base) ((base) + (0x0928))
#define SOC_DSS_WCH_AFBCE_THRESHOLD_ADDR(base) ((base) + (0x092C))
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_ADDR(base) ((base) + (0x0930))
#define SOC_DSS_WCH_REG_DEFAULT_ADDR(base) ((base) + (0x0A00))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_x0 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_WCH_DMA_OFT_X0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_START (0)
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_y0 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_START (0)
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_x1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_WCH_DMA_OFT_X1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_START (0)
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_oft_y1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_START (0)
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_END (15)
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
} SOC_DSS_WCH_DMA_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_START (0)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_END (15)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_START (16)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_END (27)
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
} SOC_DSS_WCH_DMA_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_START (0)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_END (15)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_START (16)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_END (27)
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
} SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_START (0)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_END (12)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_START (13)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_END (18)
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
} SOC_DSS_WCH_DMA_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_START (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_END (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_START (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_END (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_START (3)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_END (7)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_START (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_END (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_START (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_END (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_START (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_END (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_START (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_END (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_START (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_END (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_START (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_END (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_START (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_END (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_START (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_END (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_START (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_END (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_START (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_END (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_START (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_END (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_START (24)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_tile_scrambling_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_TILE_SCRAM_UNION;
#endif
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_START (0)
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_pulse : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_PULSE_UNION;
#endif
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_START (0)
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwch_cfg0 : 32;
    } reg;
} SOC_DSS_WCH_RWCH_CFG0_UNION;
#endif
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_START (0)
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_fifo_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_FIFO_CLR_UNION;
#endif
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_START (0)
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_counter_en : 1;
        unsigned int dma_counter_inc_cnum : 4;
        unsigned int dma_counter_rst_cnum : 4;
        unsigned int wch_enc_slice_h : 8;
        unsigned int wch_enc_space : 4;
        unsigned int reserved : 11;
    } reg;
} SOC_DSS_WCH_DMA_COUNTER_DGB_UNION;
#endif
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_START (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_END (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_START (1)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_END (4)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_START (5)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_END (8)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_START (9)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_END (16)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_START (17)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_rot_burst4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_ROT_BURST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_START (0)
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_reload_rsv1_reg : 32;
    } reg;
} SOC_DSS_WCH_DMA_RSV1_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_START (0)
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_rsv2_reg : 32;
    } reg;
} SOC_DSS_WCH_DMA_RSV2_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_START (0)
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_sw_mask_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_SW_MASK_EN_UNION;
#endif
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_START (0)
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_start_mask0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_START_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_START (0)
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_end_mask0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_END_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_START (0)
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_start_mask1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_START_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_START (0)
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_end_mask1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_END_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_START (0)
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_addr0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_START (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_END (31)
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
} SOC_DSS_WCH_DMA_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_START (0)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_END (12)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_START (16)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stretch_stride0 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_START (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_data_num0 : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_START (0)
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test0_y : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST0_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_START (0)
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test1_y : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST1_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_START (0)
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test3_y : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST3_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_START (0)
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test4_y : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_START (0)
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_status_y : 32;
    } reg;
} SOC_DSS_WCH_DMA_STATUS_Y_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_START (0)
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_addr1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_START (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stride1 : 13;
        unsigned int reserved_0 : 3;
        unsigned int dma_l2t_interleave_n1 : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_DSS_WCH_DMA_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_START (0)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_END (12)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_START (16)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_stretch_stride1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_START (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_data_num1 : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_START (0)
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test0_u : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST0_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_START (0)
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test1_u : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST1_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_START (0)
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test3_u : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST3_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_START (0)
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_test4_u : 32;
    } reg;
} SOC_DSS_WCH_DMA_TEST4_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_START (0)
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_status_u : 32;
    } reg;
} SOC_DSS_WCH_DMA_STATUS_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_START (0)
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwch_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_CH_RD_SHADOW_UNION;
#endif
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_START (0)
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_en : 1;
        unsigned int ch_version_sel : 1;
        unsigned int ch_afbce_en : 1;
        unsigned int ch_block_en : 1;
        unsigned int ch_last_block : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_DSS_WCH_CH_CTL_UNION;
#endif
#define SOC_DSS_WCH_CH_CTL_ch_en_START (0)
#define SOC_DSS_WCH_CH_CTL_ch_en_END (0)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_START (1)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_END (1)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_START (2)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_END (2)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_START (3)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_END (3)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_START (4)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_secu_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_CH_SECU_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_START (0)
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_sw_end_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_CH_SW_END_REQ_UNION;
#endif
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_START (0)
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_clk_sel : 32;
    } reg;
} SOC_DSS_WCH_CH_CLK_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_START (0)
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_clk_en : 32;
    } reg;
} SOC_DSS_WCH_CH_CLK_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_START (0)
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_END (31)
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
} SOC_DSS_WCH_DFC_DISP_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_START (0)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_END (12)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_START (16)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_pix_in_num : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION;
#endif
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_START (0)
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_END (0)
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
} SOC_DSS_WCH_DFC_GLB_ALPHA_UNION;
#endif
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_START (0)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_END (7)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_START (8)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_END (15)
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
} SOC_DSS_WCH_DFC_DISP_FMT_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_START (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_END (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_START (1)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_END (5)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_START (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_END (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_START (7)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_END (7)
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
} SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_START (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_END (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_START (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_END (21)
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
} SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_START (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_END (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_START (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_ctl_clip_enable : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION;
#endif
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_START (0)
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_module_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DFC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_START (0)
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_dither_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_START (0)
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfc_left_pad : 5;
        unsigned int reserved_0 : 3;
        unsigned int dfc_right_pad : 5;
        unsigned int reserved_1 : 3;
        unsigned int dfc_top_pad : 5;
        unsigned int reserved_2 : 3;
        unsigned int dfc_bot_pad : 5;
        unsigned int reserved_3 : 2;
        unsigned int dfc_ctl_pad_enable : 1;
    } reg;
} SOC_DSS_WCH_DFC_PADDING_CTL_UNION;
#endif
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_START (0)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_END (4)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_START (8)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_END (12)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_START (16)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_END (20)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_START (24)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_END (28)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_START (31)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_idc0 : 9;
        unsigned int csc_idc1 : 9;
        unsigned int csc_idc2 : 9;
        unsigned int reserved : 5;
    } reg;
} SOC_DSS_WCH_CSC_IDC_UNION;
#endif
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_START (0)
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_END (8)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_START (9)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_END (17)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_START (18)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_odc0 : 9;
        unsigned int csc_odc1 : 9;
        unsigned int csc_odc2 : 9;
        unsigned int reserved : 5;
    } reg;
} SOC_DSS_WCH_CSC_ODC_UNION;
#endif
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_START (0)
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_END (8)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_START (9)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_END (17)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_START (18)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_p00 : 11;
        unsigned int reserved_0: 5;
        unsigned int csc_p01 : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_DSS_WCH_CSC_P0_UNION;
#endif
#define SOC_DSS_WCH_CSC_P0_csc_p00_START (0)
#define SOC_DSS_WCH_CSC_P0_csc_p00_END (10)
#define SOC_DSS_WCH_CSC_P0_csc_p01_START (16)
#define SOC_DSS_WCH_CSC_P0_csc_p01_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_p02 : 11;
        unsigned int reserved_0: 5;
        unsigned int csc_p10 : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_DSS_WCH_CSC_P1_UNION;
#endif
#define SOC_DSS_WCH_CSC_P1_csc_p02_START (0)
#define SOC_DSS_WCH_CSC_P1_csc_p02_END (10)
#define SOC_DSS_WCH_CSC_P1_csc_p10_START (16)
#define SOC_DSS_WCH_CSC_P1_csc_p10_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_p11 : 11;
        unsigned int reserved_0: 5;
        unsigned int csc_p12 : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_DSS_WCH_CSC_P2_UNION;
#endif
#define SOC_DSS_WCH_CSC_P2_csc_p11_START (0)
#define SOC_DSS_WCH_CSC_P2_csc_p11_END (10)
#define SOC_DSS_WCH_CSC_P2_csc_p12_START (16)
#define SOC_DSS_WCH_CSC_P2_csc_p12_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_p20 : 11;
        unsigned int reserved_0: 5;
        unsigned int csc_p21 : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_DSS_WCH_CSC_P3_UNION;
#endif
#define SOC_DSS_WCH_CSC_P3_csc_p20_START (0)
#define SOC_DSS_WCH_CSC_P3_csc_p20_END (10)
#define SOC_DSS_WCH_CSC_P3_csc_p21_START (16)
#define SOC_DSS_WCH_CSC_P3_csc_p21_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_p22 : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_DSS_WCH_CSC_P4_UNION;
#endif
#define SOC_DSS_WCH_CSC_P4_csc_p22_START (0)
#define SOC_DSS_WCH_CSC_P4_csc_p22_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csc_module_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_CSC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_START (0)
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_first_lns_en : 1;
        unsigned int rot_first_lns : 5;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_WCH_ROT_FIRST_LNS_UNION;
#endif
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_START (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_END (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_START (1)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_state : 32;
    } reg;
} SOC_DSS_WCH_ROT_STATE_UNION;
#endif
#define SOC_DSS_WCH_ROT_STATE_rot_state_START (0)
#define SOC_DSS_WCH_ROT_STATE_rot_state_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_WCH_ROT_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_START (0)
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_img_width : 13;
        unsigned int reserved_0 : 3;
        unsigned int rot_img_height : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_WCH_ROT_SIZE_UNION;
#endif
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_START (0)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_END (12)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_START (16)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_ctl0 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_START (0)
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_start0 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_ROT_CPU_START0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_START (0)
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_addr0 : 12;
        unsigned int reserved : 19;
        unsigned int rot_cpu_rw0 : 1;
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_START (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_END (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_START (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_rdata0 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_START (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_rdata1 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_START (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_wdata0 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_START (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_wdata1 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_START (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_ctl1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_START (0)
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_start1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_ROT_CPU_START1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_START (0)
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_addr1 : 12;
        unsigned int reserved : 19;
        unsigned int rot_cpu_rw1 : 1;
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_START (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_END (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_START (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_rdata2 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_START (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_rdata3 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_START (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_wdata2 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_START (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rot_cpu_wdata3 : 32;
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_START (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_debug_sel : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_WCH_CH_DEBUG_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_START (0)
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_END (3)
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
} SOC_DSS_WCH_DMA_BUF_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_START (0)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_END (5)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_START (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_END (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_START (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_END (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_START (10)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_ctl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_START_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_END (0)
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
} SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_END (8)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_START (31)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata2 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_rdata3 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata2 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_cpu_wdata3 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_START (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_req_end : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_DMA_REQ_END_UNION;
#endif
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_START (0)
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbgcfg : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg0 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg1 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg2 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg3 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg4 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG4_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_dbg5 : 32;
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG5_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_START (0)
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_END (31)
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
} SOC_DSS_WCH_DMA_BUF_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_START (0)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_END (12)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_START (16)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_buf_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_START (0)
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_pic_blks : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_START (0)
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int reserved_1 : 5;
        unsigned int afbce_color_transform : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_START (21)
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_hdr_ptr_lo : 32;
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_START (0)
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_payload_ptr_lo : 32;
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_START (0)
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_block_height : 16;
        unsigned int afbce_block_width : 10;
        unsigned int reserved : 6;
    } reg;
} SOC_DSS_WCH_PICTURE_SIZE_UNION;
#endif
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_START (0)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_END (15)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_START (16)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 29;
    } reg;
} SOC_DSS_WCH_AFBCE_CTL_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_header_stride : 14;
        unsigned int afbce_header_start_pos : 2;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_WCH_HEADER_SRTIDE_UNION;
#endif
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_START (0)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_END (13)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_START (14)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_payload_stride : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_WCH_PAYLOAD_STRIDE_UNION;
#endif
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_START (0)
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_ddrw_os : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_WCH_ENC_OS_CFG_UNION;
#endif
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_START (0)
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_mem_ctrl_0 : 4;
        unsigned int afbce_mem_ctrl_1 : 4;
        unsigned int afbce_mem_ctrl_2 : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_START (0)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_END (3)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_START (4)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_END (7)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_START (8)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_qos_cfg : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_WCH_AFBCE_QOS_CFG_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_START (0)
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_threshold : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_WCH_AFBCE_THRESHOLD_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_START (0)
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce_scramble_mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_START (0)
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_WCH_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
