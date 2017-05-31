#ifndef __SOC_ISP_DRC_INTERFACE_H__
#define __SOC_ISP_DRC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_DRC_DRC_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_DRC_BLOCKNUM_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_DRC_FIRSTBLOCK_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_DRC_PLAINBLOCK_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_DRC_LASTBLOCK_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_DRC_XSTRIPESTART_END_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_DRC_STRIPE_INFO_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_DRC_FRAME_INFO_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_DRC_BUFFWINH_ADDR(base,Range3) ((base) + (0x0020+0x4*(Range3)))
#define SOC_ISP_DRC_BUFFWINV_ADDR(base,Range3) ((base) + (0x002C+0x4*(Range3)))
#define SOC_ISP_DRC_BUFFWINSIZE_ADDR(base,Range6) ((base) + (0x0038+0x4*(Range6)))
#define SOC_ISP_DRC_ALPHA_EVEN_0_ADDR(base,Range9) ((base) + (0x0100+0x4*(Range9)))
#define SOC_ISP_DRC_ALPHA_EVEN_1_ADDR(base,Range9) ((base) + (0x0140+0x4*(Range9)))
#define SOC_ISP_DRC_ALPHA_ODD_0_ADDR(base,Range8) ((base) + (0x0180+0x4*(Range8)))
#define SOC_ISP_DRC_ALPHA_ODD_1_ADDR(base,Range8) ((base) + (0x01C0+0x4*(Range8)))
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ADDR(base,Range9) ((base) + (0x0200+0x4*(Range9)))
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ADDR(base,Range9) ((base) + (0x0240+0x4*(Range9)))
#define SOC_ISP_DRC_RA_TAB_ODD_0_ADDR(base,Range8) ((base) + (0x0280+0x4*(Range8)))
#define SOC_ISP_DRC_RA_TAB_ODD_1_ADDR(base,Range8) ((base) + (0x02C0+0x4*(Range8)))
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_ADDR(base,Range33) ((base) + (0x0300+0x4*(Range33)))
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_ADDR(base,Range33) ((base) + (0x0400+0x4*(Range33)))
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_ADDR(base,Range32) ((base) + (0x0500+0x4*(Range32)))
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_ADDR(base,Range32) ((base) + (0x0600+0x4*(Range32)))
#define SOC_ISP_DRC_AVERMATRIX_0_ADDR(base,Range128) ((base) + (0x0700+0x4*(Range128)))
#define SOC_ISP_DRC_AVERMATRIX_1_ADDR(base,Range128) ((base) + (0x0900+0x4*(Range128)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int stat_enable : 1;
        unsigned int alpha_table_active : 1;
        unsigned int ra_tab_table_active : 1;
        unsigned int rat_tabhl_table_active : 1;
        unsigned int avermatrix_table_active : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_DRC_DRC_CONFIG_UNION;
#endif
#define SOC_ISP_DRC_DRC_CONFIG_bypass_START (0)
#define SOC_ISP_DRC_DRC_CONFIG_bypass_END (0)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_START (1)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_END (1)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_START (2)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_END (2)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_START (3)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_END (3)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_START (4)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_END (4)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_START (5)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blocknumv : 5;
        unsigned int reserved_0 : 3;
        unsigned int blocknumh : 5;
        unsigned int reserved_1 : 3;
        unsigned int blocknumh_stripe : 5;
        unsigned int reserved_2 : 11;
    } reg;
} SOC_ISP_DRC_BLOCKNUM_UNION;
#endif
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_START (0)
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_END (4)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_START (8)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_END (12)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_START (16)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int firstblockoffh : 10;
        unsigned int reserved_0 : 6;
        unsigned int firstblocknumh : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_ISP_DRC_FIRSTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_START (0)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_END (9)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_START (16)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blockwinv : 10;
        unsigned int reserved_0: 6;
        unsigned int blockwinh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_DRC_PLAINBLOCK_UNION;
#endif
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_START (0)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_END (9)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_START (16)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lastwinv : 10;
        unsigned int lastwinh : 10;
        unsigned int lastwinh_stripe : 10;
        unsigned int reserved : 2;
    } reg;
} SOC_ISP_DRC_LASTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_START (0)
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_END (9)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_START (10)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_END (19)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_START (20)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int endpoint : 13;
        unsigned int reserved_0 : 3;
        unsigned int startpoint : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_DRC_XSTRIPESTART_END_UNION;
#endif
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_START (0)
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_END (12)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_START (16)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int khright : 7;
        unsigned int reserved_0 : 1;
        unsigned int khleft : 7;
        unsigned int reserved_1 : 1;
        unsigned int stripewinh : 13;
        unsigned int reserved_2 : 3;
    } reg;
} SOC_ISP_DRC_STRIPE_INFO_UNION;
#endif
#define SOC_ISP_DRC_STRIPE_INFO_khright_START (0)
#define SOC_ISP_DRC_STRIPE_INFO_khright_END (6)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_START (8)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_END (14)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_START (16)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frame_height : 13;
        unsigned int reserved_0 : 3;
        unsigned int frame_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_DRC_FRAME_INFO_UNION;
#endif
#define SOC_ISP_DRC_FRAME_INFO_frame_height_START (0)
#define SOC_ISP_DRC_FRAME_INFO_frame_height_END (12)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_START (16)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffwinh : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DRC_BUFFWINH_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINH_buffwinh_START (0)
#define SOC_ISP_DRC_BUFFWINH_buffwinh_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffwinv : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_DRC_BUFFWINV_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINV_buffwinv_START (0)
#define SOC_ISP_DRC_BUFFWINV_buffwinv_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffwinsize : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_ISP_DRC_BUFFWINSIZE_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_START (0)
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alpha_even_0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_START (0)
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alpha_even_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_START (0)
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alpha_odd_0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_START (0)
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alpha_odd_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_START (0)
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ra_tab_even_0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_START (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ra_tab_even_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_START (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ra_tab_odd_0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_START (0)
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ra_tab_odd_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_START (0)
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rat_tabhl_even_0 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_START (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rat_tabhl_even_1 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_START (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rat_tabhl_odd_0 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_START (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rat_tabhl_odd_1 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_START (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int avermatrix_odd_0 : 10;
        unsigned int reserved_0 : 6;
        unsigned int avermatrix_even_0 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_DRC_AVERMATRIX_0_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_START (0)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_END (9)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_START (16)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int avermatrix_odd_1 : 10;
        unsigned int reserved_0 : 6;
        unsigned int avermatrix_even_1 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_DRC_AVERMATRIX_1_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_START (0)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_END (9)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_START (16)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_END (25)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
