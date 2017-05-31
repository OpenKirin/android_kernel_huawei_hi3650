#ifndef __SOC_DSS_MIF_INTERFACE_H__
#define __SOC_DSS_MIF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_MIF_MIF_ENABLE_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_MIF_MIF_MEM_CTRL_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_MIF_MIF_CTRL0_ADDR(base,j) ((base) + (0x0000+32*(j)))
#define SOC_DSS_MIF_MIF_CTRL1_ADDR(base,j) ((base) + (0x0004+32*(j)))
#define SOC_DSS_MIF_MIF_CTRL2_ADDR(base,j) ((base) + (0x0008+32*(j)))
#define SOC_DSS_MIF_MIF_CTRL3_ADDR(base,j) ((base) + (0x000C+32*(j)))
#define SOC_DSS_MIF_MIF_CTRL4_ADDR(base,j) ((base) + (0x0010+32*(j)))
#define SOC_DSS_MIF_MIF_CTRL5_ADDR(base,j) ((base) + (0x0014+32*(j)))
#define SOC_DSS_MIF_MIF_STAT0_ADDR(base,k) ((base) + (0x0160+16*(k)))
#define SOC_DSS_MIF_MIF_STAT1_ADDR(base,k) ((base) + (0x0164+16*(k)))
#define SOC_DSS_MIF_MIF_STAT2_ADDR(base,k) ((base) + (0x0168+16*(k)))
#define SOC_DSS_MIF_REG_DEFAULT_ADDR(base) ((base) + (0x0500))
#define SOC_DSS_MIF_MIF_SHADOW_READ_ADDR(base) ((base) + (0x0504))
#define SOC_DSS_MIF_MIF_CLK_CTL_ADDR(base) ((base) + (0x0508))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 1;
        unsigned int tagcache_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MIF_MIF_ENABLE_UNION;
#endif
#define SOC_DSS_MIF_MIF_ENABLE_enable_START (0)
#define SOC_DSS_MIF_MIF_ENABLE_enable_END (0)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_START (1)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mif_mem_ctrl_s : 16;
        unsigned int mif_mem_ctrl_t : 16;
    } reg;
} SOC_DSS_MIF_MIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_START (0)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_END (15)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_START (16)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctrl_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MIF_MIF_CTRL0_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_START (0)
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sid : 4;
        unsigned int qos_en : 1;
        unsigned int bypass : 1;
        unsigned int reserved_0 : 4;
        unsigned int invalid_sel : 2;
        unsigned int reserved_1 : 5;
        unsigned int rw_type : 1;
        unsigned int initial_en : 1;
        unsigned int pref_va_ctl : 1;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_DSS_MIF_MIF_CTRL1_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL1_sid_START (0)
#define SOC_DSS_MIF_MIF_CTRL1_sid_END (3)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_START (4)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_END (4)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_START (5)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_END (5)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_START (10)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_END (11)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_START (17)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_END (17)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_START (18)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_END (18)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_START (19)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stride0 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_MIF_MIF_CTRL2_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL2_stride0_START (0)
#define SOC_DSS_MIF_MIF_CTRL2_stride0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stride1 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_MIF_MIF_CTRL3_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL3_stride1_START (0)
#define SOC_DSS_MIF_MIF_CTRL3_stride1_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stride2 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_MIF_MIF_CTRL4_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL4_stride2_START (0)
#define SOC_DSS_MIF_MIF_CTRL4_stride2_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stride3 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DSS_MIF_MIF_CTRL5_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL5_stride3_START (0)
#define SOC_DSS_MIF_MIF_CTRL5_stride3_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tag_status : 32;
    } reg;
} SOC_DSS_MIF_MIF_STAT0_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT0_tag_status_START (0)
#define SOC_DSS_MIF_MIF_STAT0_tag_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pref_ostd : 5;
        unsigned int index_ostd : 5;
        unsigned int pref_state : 5;
        unsigned int fetch_state : 4;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_MIF_MIF_STAT1_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_START (0)
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_END (4)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_START (5)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_END (9)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_START (10)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_END (14)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_START (15)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pref_tag_hit : 16;
        unsigned int fetch_tag_hit : 16;
    } reg;
} SOC_DSS_MIF_MIF_STAT2_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_START (0)
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_END (15)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_START (16)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MIF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mif_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_MIF_MIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_START (0)
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_en : 1;
        unsigned int clk_sel : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_MIF_MIF_CLK_CTL_UNION;
#endif
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_START (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_END (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_START (1)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_END (1)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
