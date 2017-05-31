#ifndef __SOC_DSS_GLB_INTERFACE_H__
#define __SOC_DSS_GLB_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_GLB_DSS_TAG_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_GLB_APB_CTL_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_ADDR(base) ((base) + (0x104))
#define SOC_DSS_GLB_PXL0_GT_EN_ADDR(base) ((base) + (0x108))
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_ADDR(base) ((base) + (0x10C))
#define SOC_DSS_GLB_PXL0_DIVXCFG_ADDR(base) ((base) + (0x110))
#define SOC_DSS_GLB_DSI1_CLK_SEL_ADDR(base) ((base) + (0x114))
#define SOC_DSS_GLB_DSS_AXI_RST_EN_ADDR(base) ((base) + (0x118))
#define SOC_DSS_GLB_DSS_APB_RST_EN_ADDR(base) ((base) + (0x11C))
#define SOC_DSS_GLB_DSS_CORE_RST_EN_ADDR(base) ((base) + (0x120))
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_ADDR(base) ((base) + (0x124))
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_ADDR(base) ((base) + (0x128))
#define SOC_DSS_GLB_PXL0_RST_EN_ADDR(base) ((base) + (0x12C))
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_ADDR(base) ((base) + (0x130))
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_ADDR(base) ((base) + (0x134))
#define SOC_DSS_GLB_DSI1_RST_SEL_ADDR(base) ((base) + (0x138))
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_ADDR(base) ((base) + (0x13C))
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_ADDR(base) ((base) + (0x140))
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_ADDR(base) ((base) + (0x144))
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_ADDR(base) ((base) + (0x148))
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_ADDR(base) ((base) + (0x14C))
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_ADDR(base) ((base) + (0x150))
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_ADDR(base) ((base) + (0x154))
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_ADDR(base) ((base) + (0x158))
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_ADDR(base) ((base) + (0x15C))
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_ADDR(base) ((base) + (0x160))
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_ADDR(base) ((base) + (0x164))
#define SOC_DSS_GLB_MCU_ITF0_INTS_ADDR(base) ((base) + (0x0170))
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_ADDR(base) ((base) + (0x0174))
#define SOC_DSS_GLB_MCU_ITF1_INTS_ADDR(base) ((base) + (0x0178))
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_ADDR(base) ((base) + (0x017C))
#define SOC_DSS_GLB_CPU_ITF0_INTS_ADDR(base) ((base) + (0x0180))
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_ADDR(base) ((base) + (0x0184))
#define SOC_DSS_GLB_CPU_ITF1_INTS_ADDR(base) ((base) + (0x0188))
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_ADDR(base) ((base) + (0x018C))
#define SOC_DSS_GLB_DPP_INTS_ADDR(base) ((base) + (0x0190))
#define SOC_DSS_GLB_DPP_INT_MSK_ADDR(base) ((base) + (0x0194))
#define SOC_DSS_GLB_RCH_CE_INTS_ADDR(base) ((base) + (0x198))
#define SOC_DSS_GLB_RCH_CE_INT_MSK_ADDR(base) ((base) + (0x19C))
#define SOC_DSS_GLB_MCU_PDP_INTS_ADDR(base) ((base) + (0x20C))
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_ADDR(base) ((base) + (0x210))
#define SOC_DSS_GLB_MCU_SDP_INTS_ADDR(base) ((base) + (0x214))
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_ADDR(base) ((base) + (0x218))
#define SOC_DSS_GLB_MCU_OFF_INTS_ADDR(base) ((base) + (0x21C))
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_ADDR(base) ((base) + (0x220))
#define SOC_DSS_GLB_CPU_PDP_INTS_ADDR(base) ((base) + (0x224))
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_ADDR(base) ((base) + (0x228))
#define SOC_DSS_GLB_CPU_SDP_INTS_ADDR(base) ((base) + (0x22C))
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_ADDR(base) ((base) + (0x230))
#define SOC_DSS_GLB_CPU_OFF_INTS_ADDR(base) ((base) + (0x234))
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_ADDR(base) ((base) + (0x238))
#define SOC_DSS_GLB_DBG_MCTL_INTS_ADDR(base) ((base) + (0x23C))
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_ADDR(base) ((base) + (0x240))
#define SOC_DSS_GLB_DBG_WCH0_INTS_ADDR(base) ((base) + (0x244))
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_ADDR(base) ((base) + (0x248))
#define SOC_DSS_GLB_DBG_WCH1_INTS_ADDR(base) ((base) + (0x24C))
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_ADDR(base) ((base) + (0x250))
#define SOC_DSS_GLB_DBG_RCH0_INTS_ADDR(base) ((base) + (0x254))
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_ADDR(base) ((base) + (0x258))
#define SOC_DSS_GLB_DBG_RCH1_INTS_ADDR(base) ((base) + (0x25C))
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_ADDR(base) ((base) + (0x260))
#define SOC_DSS_GLB_DBG_RCH2_INTS_ADDR(base) ((base) + (0x264))
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_ADDR(base) ((base) + (0x268))
#define SOC_DSS_GLB_DBG_RCH3_INTS_ADDR(base) ((base) + (0x26C))
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_ADDR(base) ((base) + (0x270))
#define SOC_DSS_GLB_DBG_RCH4_INTS_ADDR(base) ((base) + (0x274))
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_ADDR(base) ((base) + (0x278))
#define SOC_DSS_GLB_DBG_RCH5_INTS_ADDR(base) ((base) + (0x27C))
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_ADDR(base) ((base) + (0x280))
#define SOC_DSS_GLB_DBG_RCH6_INTS_ADDR(base) ((base) + (0x284))
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_ADDR(base) ((base) + (0x288))
#define SOC_DSS_GLB_DBG_RCH7_INTS_ADDR(base) ((base) + (0x28C))
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_ADDR(base) ((base) + (0x290))
#define SOC_DSS_GLB_INTS_ADDR(base) ((base) + (0x294))
#define SOC_DSS_GLB_INT_MSK_ADDR(base) ((base) + (0x298))
#define SOC_DSS_GLB_MODULE_CLK_SEL_ADDR(base) ((base) + (0x0300))
#define SOC_DSS_GLB_MODULE_CLK_EN_ADDR(base) ((base) + (0x304))
#define SOC_DSS_GLB_MODULE1_CLK_SEL_ADDR(base) ((base) + (0x308))
#define SOC_DSS_GLB_MODULE1_CLK_EN_ADDR(base) ((base) + (0x30C))
#define SOC_DSS_GLB_GLB0_DBG_SEL_ADDR(base) ((base) + (0x310))
#define SOC_DSS_GLB_GLB1_DBG_SEL_ADDR(base) ((base) + (0x314))
#define SOC_DSS_GLB_DBG_IRQ_CPU_ADDR(base) ((base) + (0x320))
#define SOC_DSS_GLB_DBG_IRQ_MCU_ADDR(base) ((base) + (0x324))
#define SOC_DSS_GLB_TP_SEL_ADDR(base) ((base) + (0x0400))
#define SOC_DSS_GLB_CRC_DBG_LDI0_ADDR(base) ((base) + (0x0404))
#define SOC_DSS_GLB_CRC_DBG_LDI1_ADDR(base) ((base) + (0x0408))
#define SOC_DSS_GLB_CRC_LDI0_EN_ADDR(base) ((base) + (0x040C))
#define SOC_DSS_GLB_CRC_LDI0_FRM_ADDR(base) ((base) + (0x0410))
#define SOC_DSS_GLB_CRC_LDI1_EN_ADDR(base) ((base) + (0x0414))
#define SOC_DSS_GLB_CRC_LDI1_FRM_ADDR(base) ((base) + (0x0418))
#define SOC_DSS_GLB_DSS_MEM_CTRL_ADDR(base) ((base) + (0x0600))
#define SOC_DSS_GLB_DSS_PM_CTRL_ADDR(base) ((base) + (0x0604))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_tag : 32;
    } reg;
} SOC_DSS_GLB_DSS_TAG_UNION;
#endif
#define SOC_DSS_GLB_DSS_TAG_dss_tag_START (0)
#define SOC_DSS_GLB_DSS_TAG_dss_tag_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int apb_cpu_force : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_APB_CTL_UNION;
#endif
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_START (0)
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_div2_gt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_START (0)
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_div4_gt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_START (0)
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_gt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_START (0)
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_dsi_gt_en : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_START (0)
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_divxcfg : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_GLB_PXL0_DIVXCFG_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_START (0)
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi1_clk_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSI1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_START (0)
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_axi_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSS_AXI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_START (0)
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_apb_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSS_APB_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_START (0)
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_core_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSS_CORE_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_START (0)
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_div2_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_START (0)
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_div4_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_START (0)
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_START (0)
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pxl0_dsi_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_START (0)
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_pxl1_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_START (0)
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi1_rst_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_DSI1_RST_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_START (0)
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mm_axi_clk_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_START (0)
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd0_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd1_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd2_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd3_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd4_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd5_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd6_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbcd7_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce0_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afbce1_ip_rst_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_START (0)
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_itf0_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_START (0)
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_itf0_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_START (0)
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_itf1_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_START (0)
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_itf1_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_START (0)
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_itf0_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_START (0)
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_itf0_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_START (0)
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_itf1_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_START (0)
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_itf1_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_START (0)
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_ints : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_GLB_DPP_INTS_UNION;
#endif
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_START (0)
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpp_int_msk : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_GLB_DPP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_START (0)
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ce_ints : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_GLB_RCH_CE_INTS_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_START (0)
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ce_int_msk : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_GLB_RCH_CE_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_START (0)
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_pdp_ints : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_DSS_GLB_MCU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_START (0)
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_pdp_int_msk : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_START (0)
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_sdp_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_MCU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_START (0)
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_sdp_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_START (0)
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_off_ints : 32;
    } reg;
} SOC_DSS_GLB_MCU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_START (0)
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_off_int_msk : 32;
    } reg;
} SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_START (0)
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_pdp_ints : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_DSS_GLB_CPU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_START (0)
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_pdp_int_msk : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_START (0)
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_sdp_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_CPU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_START (0)
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_sdp_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_START (0)
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_off_ints : 32;
    } reg;
} SOC_DSS_GLB_CPU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_START (0)
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_off_int_msk : 32;
    } reg;
} SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_START (0)
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_mctl_ints : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_START (0)
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_mctl_int_msk : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_START (0)
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_wch0_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_START (0)
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_wch0_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_START (0)
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_wch1_ints : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_START (0)
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_wch1_int_msk : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_START (0)
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch0_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch0_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch1_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch1_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch2_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch2_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch3_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch3_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch4_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch4_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch5_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch5_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch6_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch6_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch7_ints : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_START (0)
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rch7_int_msk : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_START (0)
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_glb_ints : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_GLB_INTS_UNION;
#endif
#define SOC_DSS_GLB_INTS_dss_glb_ints_START (0)
#define SOC_DSS_GLB_INTS_dss_glb_ints_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_glb_int_msk : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_GLB_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_START (0)
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int module_clk_sel : 32;
    } reg;
} SOC_DSS_GLB_MODULE_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_START (0)
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int module_clk_en : 32;
    } reg;
} SOC_DSS_GLB_MODULE_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_START (0)
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int module1_clk_sel : 32;
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_START (0)
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int module1_clk_en : 32;
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_START (0)
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int glb0_core_dbg_sel : 4;
        unsigned int dss_sum_dbg_sel : 2;
        unsigned int reserved_0 : 2;
        unsigned int glb0_axi_dbg_sel : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_DSS_GLB_GLB0_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_START (0)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_END (3)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_START (4)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_END (5)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_START (8)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int glb1_core_dbg_sel : 2;
        unsigned int glb1_clk_dbg_sel : 2;
        unsigned int reserved_0 : 4;
        unsigned int glb1_pxl0_dbg_sel : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_DSS_GLB_GLB1_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_START (0)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_END (1)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_START (2)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_END (3)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_START (8)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_cpu : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_GLB_DBG_IRQ_CPU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_START (0)
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_mcu : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_GLB_DBG_IRQ_MCU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_START (0)
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tp_sel : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_GLB_TP_SEL_UNION;
#endif
#define SOC_DSS_GLB_TP_SEL_tp_sel_START (0)
#define SOC_DSS_GLB_TP_SEL_tp_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_ldi0 : 32;
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI0_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_START (0)
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_ldi1 : 32;
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI1_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_START (0)
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ldi0_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_CRC_LDI0_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_START (0)
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ldi0_frm : 32;
    } reg;
} SOC_DSS_GLB_CRC_LDI0_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_START (0)
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ldi1_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_GLB_CRC_LDI1_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_START (0)
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ldi1_frm : 32;
    } reg;
} SOC_DSS_GLB_CRC_LDI1_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_START (0)
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_spram_ctrl : 16;
        unsigned int dss_tpram_ctrl : 16;
    } reg;
} SOC_DSS_GLB_DSS_MEM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_START (0)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_END (15)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_START (16)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_pm_ctrl : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_DSS_GLB_DSS_PM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_START (0)
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_END (30)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
