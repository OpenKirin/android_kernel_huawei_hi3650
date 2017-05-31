#ifndef __SOC_DSS_MCTL_MUTEX_INTERFACE_H__
#define __SOC_DSS_MCTL_MUTEX_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ADDR(base) ((base) + (0x0030))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ADDR(base) ((base) + (0x0044))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ADDR(base) ((base) + (0x0050))
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ADDR(base) ((base) + (0x0054))
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ADDR(base) ((base) + (0x0058))
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ADDR(base) ((base) + (0x0064))
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ADDR(base) ((base) + (0x0068))
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ADDR(base) ((base) + (0x006C))
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ADDR(base) ((base) + (0x00E0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_sw : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_status : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_itf : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_dbuf : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_scf : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_ov : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_wch0 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_wch1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch0 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch5 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch6 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_rch7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_sof_sel : 2;
        unsigned int ctl_frm_st_sel : 1;
        unsigned int ctl_block_mode : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_END (1)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_START (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_END (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_START (3)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mod_flush_status : 32;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_sw_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_cack_tout : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_mutex_tout : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_status : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_inten : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_clk_sel : 32;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_clk_en : 32;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctl_dbg : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_START (0)
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_END (23)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
