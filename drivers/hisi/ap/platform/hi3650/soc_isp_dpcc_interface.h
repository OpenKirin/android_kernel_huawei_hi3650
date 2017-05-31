#ifndef __SOC_ISP_DPCC_INTERFACE_H__
#define __SOC_ISP_DPCC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_DPCC_DPCC_MODE_ADDR(base) ((base) + (0x0))
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_ADDR(base) ((base) + (0x4))
#define SOC_ISP_DPCC_DPCC_SET_USE_ADDR(base) ((base) + (0x8))
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ADDR(base) ((base) + (0xC))
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ADDR(base) ((base) + (0x10))
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ADDR(base) ((base) + (0x14))
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_ADDR(base) ((base) + (0x18))
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_ADDR(base) ((base) + (0x1C))
#define SOC_ISP_DPCC_DPCC_PG_FAC1_ADDR(base) ((base) + (0x20))
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_ADDR(base) ((base) + (0x24))
#define SOC_ISP_DPCC_DPCC_RG_FAC1_ADDR(base) ((base) + (0x28))
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_ADDR(base) ((base) + (0x2C))
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_ADDR(base) ((base) + (0x30))
#define SOC_ISP_DPCC_DPCC_PG_FAC2_ADDR(base) ((base) + (0x34))
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_ADDR(base) ((base) + (0x38))
#define SOC_ISP_DPCC_DPCC_RG_FAC2_ADDR(base) ((base) + (0x3C))
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_ADDR(base) ((base) + (0x40))
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_ADDR(base) ((base) + (0x44))
#define SOC_ISP_DPCC_DPCC_PG_FAC3_ADDR(base) ((base) + (0x48))
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_ADDR(base) ((base) + (0x4C))
#define SOC_ISP_DPCC_DPCC_RG_FAC3_ADDR(base) ((base) + (0x50))
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ADDR(base) ((base) + (0x54))
#define SOC_ISP_DPCC_DPCC_RND_OFFS_ADDR(base) ((base) + (0x58))
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_ADDR(base) ((base) + (0x5C))
#define SOC_ISP_DPCC_DPCC_BPT_NUMBER_ADDR(base) ((base) + (0x60))
#define SOC_ISP_DPCC_DPCC_BPT_ADDR_ADDR(base) ((base) + (0x64))
#define SOC_ISP_DPCC_DPCC_BPT_DATA_ADDR(base) ((base) + (0x68))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpc_enable : 1;
        unsigned int reserved_0 : 1;
        unsigned int stage1_enable : 1;
        unsigned int reserved_1 : 29;
    } reg;
} SOC_ISP_DPCC_DPCC_MODE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_MODE_dpc_enable_START (0)
#define SOC_ISP_DPCC_DPCC_MODE_dpc_enable_END (0)
#define SOC_ISP_DPCC_DPCC_MODE_stage1_enable_START (2)
#define SOC_ISP_DPCC_DPCC_MODE_stage1_enable_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stage1_incl_green_center : 1;
        unsigned int stage1_incl_rb_center : 1;
        unsigned int stage1_g_3x3 : 1;
        unsigned int stage1_rb_3x3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_DPCC_DPCC_OUTPUT_MODE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_green_center_START (0)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_green_center_END (0)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_rb_center_START (1)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_incl_rb_center_END (1)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_g_3x3_START (2)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_g_3x3_END (2)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_rb_3x3_START (3)
#define SOC_ISP_DPCC_DPCC_OUTPUT_MODE_stage1_rb_3x3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stage1_use_set1 : 1;
        unsigned int stage1_use_set2 : 1;
        unsigned int stage1_use_set3 : 1;
        unsigned int stage1_use_fix_set : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_DPCC_DPCC_SET_USE_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set1_START (0)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set1_END (0)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set2_START (1)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set2_END (1)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set3_START (2)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_set3_END (2)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_fix_set_START (3)
#define SOC_ISP_DPCC_DPCC_SET_USE_stage1_use_fix_set_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_green1_enable : 1;
        unsigned int lc_green1_enable : 1;
        unsigned int ro_green1_enable : 1;
        unsigned int rnd_green1_enable : 1;
        unsigned int rg_green1_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int pg_red_blue1_enable : 1;
        unsigned int lc_red_blue1_enable : 1;
        unsigned int ro_red_blue1_enable : 1;
        unsigned int rnd_red_blue1_enable : 1;
        unsigned int rg_red_blue1_enable : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_green1_enable_START (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_green1_enable_END (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_green1_enable_START (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_green1_enable_END (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_green1_enable_START (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_green1_enable_END (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_green1_enable_START (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_green1_enable_END (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_green1_enable_START (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_green1_enable_END (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_red_blue1_enable_START (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_pg_red_blue1_enable_END (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_red_blue1_enable_START (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_lc_red_blue1_enable_END (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_red_blue1_enable_START (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_ro_red_blue1_enable_END (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_red_blue1_enable_START (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rnd_red_blue1_enable_END (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_red_blue1_enable_START (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_1_rg_red_blue1_enable_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_green2_enable : 1;
        unsigned int lc_green2_enable : 1;
        unsigned int ro_green2_enable : 1;
        unsigned int rnd_green2_enable : 1;
        unsigned int rg_green2_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int pg_red_blue2_enable : 1;
        unsigned int lc_red_blue2_enable : 1;
        unsigned int ro_red_blue2_enable : 1;
        unsigned int rnd_red_blue2_enable : 1;
        unsigned int rg_red_blue2_enable : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_green2_enable_START (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_green2_enable_END (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_green2_enable_START (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_green2_enable_END (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_green2_enable_START (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_green2_enable_END (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_green2_enable_START (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_green2_enable_END (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_green2_enable_START (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_green2_enable_END (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_red_blue2_enable_START (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_pg_red_blue2_enable_END (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_red_blue2_enable_START (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_lc_red_blue2_enable_END (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_red_blue2_enable_START (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_ro_red_blue2_enable_END (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_red_blue2_enable_START (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rnd_red_blue2_enable_END (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_red_blue2_enable_START (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_2_rg_red_blue2_enable_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_green3_enable : 1;
        unsigned int lc_green3_enable : 1;
        unsigned int ro_green3_enable : 1;
        unsigned int rnd_green3_enable : 1;
        unsigned int rg_green3_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int pg_red_blue3_enable : 1;
        unsigned int lc_red_blue3_enable : 1;
        unsigned int ro_red_blue3_enable : 1;
        unsigned int rnd_red_blue3_enable : 1;
        unsigned int rg_red_blue3_enable : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_ISP_DPCC_DPCC_METHODS_SET_3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_green3_enable_START (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_green3_enable_END (0)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_green3_enable_START (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_green3_enable_END (1)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_green3_enable_START (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_green3_enable_END (2)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_green3_enable_START (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_green3_enable_END (3)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_green3_enable_START (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_green3_enable_END (4)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_red_blue3_enable_START (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_pg_red_blue3_enable_END (8)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_red_blue3_enable_START (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_lc_red_blue3_enable_END (9)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_red_blue3_enable_START (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_ro_red_blue3_enable_END (10)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_red_blue3_enable_START (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rnd_red_blue3_enable_END (11)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_red_blue3_enable_START (12)
#define SOC_ISP_DPCC_DPCC_METHODS_SET_3_rg_red_blue3_enable_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_thr1_g : 8;
        unsigned int line_thr1_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_g_END (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH1_line_thr1_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_mad_fac_1_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int line_mad_fac_1_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_g_END (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC1_line_mad_fac_1_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_fac_1_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int pg_fac_1_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_g_START (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_g_END (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_rb_START (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC1_pg_fac_1_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_thr1_g : 8;
        unsigned int rnd_thr1_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_g_START (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_g_END (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH1_rnd_thr1_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rg_fac_1_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int rg_fac_1_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC1_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_g_START (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_g_END (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC1_rg_fac_1_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_thr2_g : 8;
        unsigned int line_thr2_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_g_END (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH2_line_thr2_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_mad_fac_2_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int line_mad_fac_2_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_g_END (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC2_line_mad_fac_2_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_fac_2_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int pg_fac_2_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_g_START (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_g_END (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_rb_START (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC2_pg_fac_2_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_thr2_g : 8;
        unsigned int rnd_thr2_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_g_START (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_g_END (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH2_rnd_thr2_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rg_fac_2_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int rg_fac_2_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC2_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_g_START (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_g_END (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC2_rg_fac_2_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_thr3_g : 8;
        unsigned int line_thr3_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_THRESH3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_g_END (7)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_THRESH3_line_thr3_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_mad_fac_3_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int line_mad_fac_3_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_g_START (0)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_g_END (5)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_rb_START (8)
#define SOC_ISP_DPCC_DPCC_LINE_MAD_FAC3_line_mad_fac_3_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg_fac_3_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int pg_fac_3_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_PG_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_g_START (0)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_g_END (5)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_rb_START (8)
#define SOC_ISP_DPCC_DPCC_PG_FAC3_pg_fac_3_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_thr3_g : 8;
        unsigned int rnd_thr3_rb : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DPCC_DPCC_RND_THRESH3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_g_START (0)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_g_END (7)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RND_THRESH3_rnd_thr3_rb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rg_fac_3_g : 6;
        unsigned int reserved_0 : 2;
        unsigned int rg_fac_3_rb : 6;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_ISP_DPCC_DPCC_RG_FAC3_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_g_START (0)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_g_END (5)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_rb_START (8)
#define SOC_ISP_DPCC_DPCC_RG_FAC3_rg_fac_3_rb_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ro_lim_1_g : 2;
        unsigned int ro_lim_1_rb : 2;
        unsigned int ro_lim_2_g : 2;
        unsigned int ro_lim_2_rb : 2;
        unsigned int ro_lim_3_g : 2;
        unsigned int ro_lim_3_rb : 2;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_DPCC_DPCC_RO_LIMITS_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_g_START (0)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_g_END (1)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_rb_START (2)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_1_rb_END (3)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_g_START (4)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_g_END (5)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_rb_START (6)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_2_rb_END (7)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_g_START (8)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_g_END (9)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_rb_START (10)
#define SOC_ISP_DPCC_DPCC_RO_LIMITS_ro_lim_3_rb_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_offs_1_g : 2;
        unsigned int rnd_offs_1_rb : 2;
        unsigned int rnd_offs_2_g : 2;
        unsigned int rnd_offs_2_rb : 2;
        unsigned int rnd_offs_3_g : 2;
        unsigned int rnd_offs_3_rb : 2;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_DPCC_DPCC_RND_OFFS_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_g_START (0)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_g_END (1)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_rb_START (2)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_1_rb_END (3)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_g_START (4)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_g_END (5)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_rb_START (6)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_2_rb_END (7)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_g_START (8)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_g_END (9)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_rb_START (10)
#define SOC_ISP_DPCC_DPCC_RND_OFFS_rnd_offs_3_rb_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int bpt_cor_en : 1;
        unsigned int reserved_1 : 6;
        unsigned int bpt_incl_green_center : 1;
        unsigned int bpt_incl_rb_center : 1;
        unsigned int bpt_g_3x3 : 1;
        unsigned int bpt_rb_3x3 : 1;
        unsigned int reserved_2 : 20;
    } reg;
} SOC_ISP_DPCC_DPCC_BPT_CTRL_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_cor_en_START (1)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_cor_en_END (1)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_incl_green_center_START (8)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_incl_green_center_END (8)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_incl_rb_center_START (9)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_incl_rb_center_END (9)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_g_3x3_START (10)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_g_3x3_END (10)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_rb_3x3_START (11)
#define SOC_ISP_DPCC_DPCC_BPT_CTRL_bpt_rb_3x3_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bp_number : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_DPCC_DPCC_BPT_NUMBER_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_BPT_NUMBER_bp_number_START (0)
#define SOC_ISP_DPCC_DPCC_BPT_NUMBER_bp_number_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bp_table_addr : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_DPCC_DPCC_BPT_ADDR_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_BPT_ADDR_bp_table_addr_START (0)
#define SOC_ISP_DPCC_DPCC_BPT_ADDR_bp_table_addr_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bpt_h_addr : 13;
        unsigned int reserved_0 : 3;
        unsigned int bpt_v_addr : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_DPCC_DPCC_BPT_DATA_UNION;
#endif
#define SOC_ISP_DPCC_DPCC_BPT_DATA_bpt_h_addr_START (0)
#define SOC_ISP_DPCC_DPCC_BPT_DATA_bpt_h_addr_END (12)
#define SOC_ISP_DPCC_DPCC_BPT_DATA_bpt_v_addr_START (16)
#define SOC_ISP_DPCC_DPCC_BPT_DATA_bpt_v_addr_END (28)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
