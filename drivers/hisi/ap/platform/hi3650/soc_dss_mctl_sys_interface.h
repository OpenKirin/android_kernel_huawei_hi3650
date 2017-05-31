#ifndef __SOC_DSS_MCTL_SYS_INTERFACE_H__
#define __SOC_DSS_MCTL_SYS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_ADDR(base) ((base) + (0x00A0))
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_ADDR(base) ((base) + (0x00A4))
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_ADDR(base) ((base) + (0x0104))
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_ADDR(base) ((base) + (0x0108))
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_ADDR(base) ((base) + (0x0114))
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_ADDR(base) ((base) + (0x011C))
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_ADDR(base) ((base) + (0x0120))
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_ADDR(base) ((base) + (0x0124))
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ADDR(base) ((base) + (0x0128))
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ADDR(base) ((base) + (0x012C))
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ADDR(base) ((base) + (0x0130))
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ADDR(base) ((base) + (0x0134))
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_ADDR(base) ((base) + (0x0160))
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_ADDR(base) ((base) + (0x0164))
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_ADDR(base) ((base) + (0x0168))
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_ADDR(base) ((base) + (0x016C))
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_ADDR(base) ((base) + (0x0170))
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_ADDR(base) ((base) + (0x0174))
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_ADDR(base) ((base) + (0x0178))
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_ADDR(base) ((base) + (0x017C))
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_ADDR(base) ((base) + (0x0180))
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_ADDR(base) ((base) + (0x0184))
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_ADDR(base) ((base) + (0x0188))
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_ADDR(base) ((base) + (0x018C))
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_ADDR(base) ((base) + (0x01A0))
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_ADDR(base) ((base) + (0x01A4))
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_ADDR(base) ((base) + (0x01A8))
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_ADDR(base) ((base) + (0x01AC))
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_ADDR(base) ((base) + (0x01B0))
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_ADDR(base) ((base) + (0x01B4))
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_ADDR(base) ((base) + (0x01C0))
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_ADDR(base) ((base) + (0x01C4))
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_ADDR(base) ((base) + (0x01C8))
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_ADDR(base) ((base) + (0x01CC))
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_ADDR(base) ((base) + (0x01D0))
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_ADDR(base) ((base) + (0x01D4))
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_ADDR(base) ((base) + (0x01D8))
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_ADDR(base) ((base) + (0x01DC))
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_ADDR(base) ((base) + (0x01F0))
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_ADDR(base) ((base) + (0x01F4))
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_ADDR(base) ((base) + (0x01F8))
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_ADDR(base) ((base) + (0x01FC))
#define SOC_DSS_MCTL_SYS_MOD0_DBG_ADDR(base) ((base) + (0x0200))
#define SOC_DSS_MCTL_SYS_MOD1_DBG_ADDR(base) ((base) + (0x0204))
#define SOC_DSS_MCTL_SYS_MOD2_DBG_ADDR(base) ((base) + (0x0208))
#define SOC_DSS_MCTL_SYS_MOD3_DBG_ADDR(base) ((base) + (0x020C))
#define SOC_DSS_MCTL_SYS_MOD4_DBG_ADDR(base) ((base) + (0x0210))
#define SOC_DSS_MCTL_SYS_MOD5_DBG_ADDR(base) ((base) + (0x0214))
#define SOC_DSS_MCTL_SYS_MOD6_DBG_ADDR(base) ((base) + (0x0218))
#define SOC_DSS_MCTL_SYS_MOD7_DBG_ADDR(base) ((base) + (0x021C))
#define SOC_DSS_MCTL_SYS_MOD8_DBG_ADDR(base) ((base) + (0x0220))
#define SOC_DSS_MCTL_SYS_MOD9_DBG_ADDR(base) ((base) + (0x0224))
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ADDR(base) ((base) + (0x0228))
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ADDR(base) ((base) + (0x022C))
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ADDR(base) ((base) + (0x0230))
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ADDR(base) ((base) + (0x0234))
#define SOC_DSS_MCTL_SYS_MOD14_DBG_ADDR(base) ((base) + (0x0238))
#define SOC_DSS_MCTL_SYS_MOD15_DBG_ADDR(base) ((base) + (0x023C))
#define SOC_DSS_MCTL_SYS_MOD16_DBG_ADDR(base) ((base) + (0x0240))
#define SOC_DSS_MCTL_SYS_MOD17_DBG_ADDR(base) ((base) + (0x0244))
#define SOC_DSS_MCTL_SYS_MOD18_DBG_ADDR(base) ((base) + (0x0248))
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_ADDR(base) ((base) + (0x0250))
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_ADDR(base) ((base) + (0x0254))
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_ADDR(base) ((base) + (0x0258))
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_ADDR(base) ((base) + (0x025C))
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_ADDR(base) ((base) + (0x0260))
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_ADDR(base) ((base) + (0x0264))
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_ADDR(base) ((base) + (0x0268))
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_ADDR(base) ((base) + (0x026C))
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_ADDR(base) ((base) + (0x0270))
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_ADDR(base) ((base) + (0x0274))
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ADDR(base) ((base) + (0x0278))
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ADDR(base) ((base) + (0x027C))
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ADDR(base) ((base) + (0x0280))
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_ADDR(base) ((base) + (0x0284))
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ADDR(base) ((base) + (0x0288))
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_ADDR(base) ((base) + (0x028C))
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_ADDR(base) ((base) + (0x0290))
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_ADDR(base) ((base) + (0x0294))
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_ADDR(base) ((base) + (0x0298))
#define SOC_DSS_MCTL_SYS_SW_DBG_ADDR(base) ((base) + (0x02B0))
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_ADDR(base) ((base) + (0x02B4))
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_ADDR(base) ((base) + (0x02B8))
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_ADDR(base) ((base) + (0x02BC))
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_ADDR(base) ((base) + (0x02C0))
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_ADDR(base) ((base) + (0x02C4))
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_ADDR(base) ((base) + (0x02C8))
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_ADDR(base) ((base) + (0x02D0))
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_ADDR(base) ((base) + (0x02D4))
#define SOC_DSS_MCTL_SYS_SW1_STATUS_ADDR(base) ((base) + (0x02D8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 4;
        unsigned int pay_secu : 1;
        unsigned int reserved_1: 27;
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_START (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pay_secu_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_rch0_secu_gate : 6;
        unsigned int reserved_0 : 2;
        unsigned int ctl_rch1_secu_gate : 6;
        unsigned int reserved_1 : 2;
        unsigned int ctl_rch2_secu_gate : 6;
        unsigned int reserved_2 : 2;
        unsigned int ctl_rch3_secu_gate : 6;
        unsigned int reserved_3 : 2;
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_START (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_END (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_START (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_END (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_START (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_END (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_START (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_rch4_secu_gate : 6;
        unsigned int reserved_0 : 2;
        unsigned int ctl_rch5_secu_gate : 6;
        unsigned int reserved_1 : 2;
        unsigned int ctl_rch6_secu_gate : 6;
        unsigned int reserved_2 : 2;
        unsigned int ctl_rch7_secu_gate : 6;
        unsigned int reserved_3 : 2;
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_START (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_END (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_START (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_END (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_START (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_END (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_START (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int ctl_ov2_secu_gate : 2;
        unsigned int ctl_ov3_secu_gate : 2;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_START (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_END (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_START (6)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi0_secu_cfg_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_START (0)
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi1_secu_cfg_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_START (0)
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch0_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch1_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch2_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch3_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch4_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch5_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch6_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch7_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch0_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch1_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov0_flush_en : 1;
        unsigned int scf_flush_en : 1;
        unsigned int dbuf0_flush_en : 1;
        unsigned int itf0_flush_en : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_END (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_START (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_END (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_START (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_END (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_START (3)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov1_flush_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int dbuf1_flush_en : 1;
        unsigned int itf1_flush_en : 1;
        unsigned int reserved_1 : 28;
    } reg;
} SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_END (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_START (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_END (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_START (3)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov2_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov3_flush_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_START (0)
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch0_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch1_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch2_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch3_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch4_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch5_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch6_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch7_ov_oen : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_START (0)
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ov0_sel : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_START (0)
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ov1_sel : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_START (0)
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ov2_sel : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_START (0)
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch_ov3_sel : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_START (0)
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch0_ov_ien : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_START (0)
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch1_ov_ien : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_START (0)
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch_ov2_sel : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_START (0)
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch_ov3_sel : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_START (0)
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wb_enc_sel : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_START (0)
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsi_mux_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_START (0)
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch0_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch0_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch1_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch1_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch2_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch2_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch3_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch3_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch4_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch4_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch5_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch5_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch6_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch6_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch7_starty : 15;
        unsigned int reserved_0 : 1;
        unsigned int rch7_thld : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_START (0)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_END (14)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_START (16)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mctl_clk_sel : 32;
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_START (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mctl_clk_en : 32;
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_START (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mod_clk_sel : 32;
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_START (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mod_clk_en : 32;
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_START (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch0_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch1_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch2_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch3_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch4_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch5_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch6_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch7_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch0_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch1_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov0_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov1_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov2_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov3_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf0_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf1_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itf0_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itf1_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_START (0)
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch0_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch1_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch2_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch3_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch4_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch5_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch6_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rch7_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch0_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wch1_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov1_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov2_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov3_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov0_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf0_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbuf1_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itf0_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itf1_status : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_START (0)
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_dbg : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_MCTL_SYS_SW_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_START (0)
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status0 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status1 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status2 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status3 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status4 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status5 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status6 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw0_status7 : 32;
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_START (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw1_status : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_MCTL_SYS_SW1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_START (0)
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
