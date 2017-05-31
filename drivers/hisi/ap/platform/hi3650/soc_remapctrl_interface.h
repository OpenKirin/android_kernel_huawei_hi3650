#ifndef __SOC_REMAPCTRL_INTERFACE_H__
#define __SOC_REMAPCTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_REMAPCTRL_REMAP_CFG_ADDR(base) ((base) + (0x000))
#define SOC_REMAPCTRL_MAP_TABLE_WP_ADDR(base) ((base) + (0x004))
#define SOC_REMAPCTRL_LP_CTRL_ADDR(base) ((base) + (0x008))
#define SOC_REMAPCTRL_LP_CTRL_1_ADDR(base) ((base) + (0x00C))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY0_ADDR(base) ((base) + (0x010))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY1_ADDR(base) ((base) + (0x014))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY2_ADDR(base) ((base) + (0x018))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY3_ADDR(base) ((base) + (0x01C))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY4_ADDR(base) ((base) + (0x020))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY5_ADDR(base) ((base) + (0x024))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY6_ADDR(base) ((base) + (0x028))
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY7_ADDR(base) ((base) + (0x02C))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY0_ADDR(base) ((base) + (0x030))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY1_ADDR(base) ((base) + (0x034))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY2_ADDR(base) ((base) + (0x038))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY3_ADDR(base) ((base) + (0x03C))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY4_ADDR(base) ((base) + (0x040))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY5_ADDR(base) ((base) + (0x044))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY6_ADDR(base) ((base) + (0x048))
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY7_ADDR(base) ((base) + (0x04C))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY0_ADDR(base) ((base) + (0x050))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY1_ADDR(base) ((base) + (0x054))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY2_ADDR(base) ((base) + (0x058))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY3_ADDR(base) ((base) + (0x05C))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY4_ADDR(base) ((base) + (0x060))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY5_ADDR(base) ((base) + (0x064))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY6_ADDR(base) ((base) + (0x068))
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY7_ADDR(base) ((base) + (0x06C))
#define SOC_REMAPCTRL_ITCM_HIT_CNT_ADDR(base) ((base) + (0x070))
#define SOC_REMAPCTRL_ITCM_MISS_CNT_ADDR(base) ((base) + (0x074))
#define SOC_REMAPCTRL_D0TCM_HIT_CNT_ADDR(base) ((base) + (0x078))
#define SOC_REMAPCTRL_D0TCM_MISS_CNT_ADDR(base) ((base) + (0x07C))
#define SOC_REMAPCTRL_D1TCM_HIT_CNT_ADDR(base) ((base) + (0x080))
#define SOC_REMAPCTRL_D1TCM_MISS_CNT_ADDR(base) ((base) + (0x084))
#define SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_ADDR(base) ((base) + (0x098))
#define SOC_REMAPCTRL_TCM_ERR_TYPE_ADDR(base) ((base) + (0x09C))
#define SOC_REMAPCTRL_BANK_SEL_ADDR(base) ((base) + (0x0A0))
#define SOC_REMAPCTRL_ITCM_ERR_ADDR_ADDR(base) ((base) + (0x0A8))
#define SOC_REMAPCTRL_D0TCM_ERR_ADDR_ADDR(base) ((base) + (0x0AC))
#define SOC_REMAPCTRL_D1TCM_ERR_ADDR_ADDR(base) ((base) + (0x0B0))
#define SOC_REMAPCTRL_ITCM_ERR_CNT_ADDR(base) ((base) + (0x0B4))
#define SOC_REMAPCTRL_D0TCM_ERR_CNT_ADDR(base) ((base) + (0x0B8))
#define SOC_REMAPCTRL_D1TCM_ERR_CNT_ADDR(base) ((base) + (0x0BC))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int invalid : 1;
        unsigned int itcm_cnt_clr : 1;
        unsigned int d0tcm_cnt_clr : 1;
        unsigned int d1tcm_cnt_clr : 1;
        unsigned int itcm_err_cnt_clr : 1;
        unsigned int d0tcm_err_cnt_clr : 1;
        unsigned int d1tcm_err_cnt_clr : 1;
        unsigned int itcm_err_clr : 1;
        unsigned int d0tcm_err_clr : 1;
        unsigned int d1tcm_err_clr : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_REMAPCTRL_REMAP_CFG_UNION;
#endif
#define SOC_REMAPCTRL_REMAP_CFG_bypass_START (0)
#define SOC_REMAPCTRL_REMAP_CFG_bypass_END (0)
#define SOC_REMAPCTRL_REMAP_CFG_invalid_START (1)
#define SOC_REMAPCTRL_REMAP_CFG_invalid_END (1)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_cnt_clr_START (2)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_cnt_clr_END (2)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_cnt_clr_START (3)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_cnt_clr_END (3)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_cnt_clr_START (4)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_cnt_clr_END (4)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_err_cnt_clr_START (5)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_err_cnt_clr_END (5)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_err_cnt_clr_START (6)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_err_cnt_clr_END (6)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_err_cnt_clr_START (7)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_err_cnt_clr_END (7)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_err_clr_START (8)
#define SOC_REMAPCTRL_REMAP_CFG_itcm_err_clr_END (8)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_err_clr_START (9)
#define SOC_REMAPCTRL_REMAP_CFG_d0tcm_err_clr_END (9)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_err_clr_START (10)
#define SOC_REMAPCTRL_REMAP_CFG_d1tcm_err_clr_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mt_wp : 32;
    } reg;
} SOC_REMAPCTRL_MAP_TABLE_WP_UNION;
#endif
#define SOC_REMAPCTRL_MAP_TABLE_WP_mt_wp_START (0)
#define SOC_REMAPCTRL_MAP_TABLE_WP_mt_wp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_gate_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int auto_gate_cnt : 8;
        unsigned int reserved_1 : 4;
        unsigned int auto_mem_lp_en : 1;
        unsigned int reserved_2 : 3;
        unsigned int auto_mem_lp_cnt : 8;
        unsigned int reserved_3 : 4;
    } reg;
} SOC_REMAPCTRL_LP_CTRL_UNION;
#endif
#define SOC_REMAPCTRL_LP_CTRL_auto_gate_en_START (0)
#define SOC_REMAPCTRL_LP_CTRL_auto_gate_en_END (0)
#define SOC_REMAPCTRL_LP_CTRL_auto_gate_cnt_START (4)
#define SOC_REMAPCTRL_LP_CTRL_auto_gate_cnt_END (11)
#define SOC_REMAPCTRL_LP_CTRL_auto_mem_lp_en_START (16)
#define SOC_REMAPCTRL_LP_CTRL_auto_mem_lp_en_END (16)
#define SOC_REMAPCTRL_LP_CTRL_auto_mem_lp_cnt_START (20)
#define SOC_REMAPCTRL_LP_CTRL_auto_mem_lp_cnt_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcm128_gate_en_soft : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_REMAPCTRL_LP_CTRL_1_UNION;
#endif
#define SOC_REMAPCTRL_LP_CTRL_1_tcm128_gate_en_soft_START (0)
#define SOC_REMAPCTRL_LP_CTRL_1_tcm128_gate_en_soft_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry0 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY0_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY0_itcm_tlb_entry0_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY0_itcm_tlb_entry0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry1 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY1_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY1_itcm_tlb_entry1_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY1_itcm_tlb_entry1_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry2 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY2_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY2_itcm_tlb_entry2_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY2_itcm_tlb_entry2_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry3 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY3_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY3_itcm_tlb_entry3_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY3_itcm_tlb_entry3_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry4 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY4_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY4_itcm_tlb_entry4_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY4_itcm_tlb_entry4_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry5 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY5_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY5_itcm_tlb_entry5_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY5_itcm_tlb_entry5_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry6 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY6_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY6_itcm_tlb_entry6_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY6_itcm_tlb_entry6_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_tlb_entry7 : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_REMAPCTRL_ITCM_TLB_ENTRY7_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY7_itcm_tlb_entry7_START (0)
#define SOC_REMAPCTRL_ITCM_TLB_ENTRY7_itcm_tlb_entry7_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry0 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry2 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry3 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry4 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry5 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry6 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_tlb_entry7 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D0TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_START (0)
#define SOC_REMAPCTRL_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry0 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry2 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry3 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry4 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry5 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry6 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_tlb_entry7 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_REMAPCTRL_D1TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_START (0)
#define SOC_REMAPCTRL_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_hit_cnt : 32;
    } reg;
} SOC_REMAPCTRL_ITCM_HIT_CNT_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_HIT_CNT_itcm_hit_cnt_START (0)
#define SOC_REMAPCTRL_ITCM_HIT_CNT_itcm_hit_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_miss_cnt : 32;
    } reg;
} SOC_REMAPCTRL_ITCM_MISS_CNT_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_MISS_CNT_itcm_miss_cnt_START (0)
#define SOC_REMAPCTRL_ITCM_MISS_CNT_itcm_miss_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_hit_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D0TCM_HIT_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_HIT_CNT_d0tcm_hit_cnt_START (0)
#define SOC_REMAPCTRL_D0TCM_HIT_CNT_d0tcm_hit_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_miss_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D0TCM_MISS_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_MISS_CNT_d0tcm_miss_cnt_START (0)
#define SOC_REMAPCTRL_D0TCM_MISS_CNT_d0tcm_miss_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_hit_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D1TCM_HIT_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_HIT_CNT_d1tcm_hit_cnt_START (0)
#define SOC_REMAPCTRL_D1TCM_HIT_CNT_d1tcm_hit_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_miss_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D1TCM_MISS_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_MISS_CNT_d1tcm_miss_cnt_START (0)
#define SOC_REMAPCTRL_D1TCM_MISS_CNT_d1tcm_miss_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcmaddr_boundary_check_bypass : 1;
        unsigned int bank_collision_check_bypass : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION;
#endif
#define SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_START (0)
#define SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_END (0)
#define SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_START (1)
#define SOC_REMAPCTRL_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_page_err : 1;
        unsigned int itcmaddr_out_320k_err : 1;
        unsigned int reserved_0 : 2;
        unsigned int d0tcm_page_err : 1;
        unsigned int d0tcmaddr_out_320k_err : 1;
        unsigned int reserved_1 : 2;
        unsigned int d1tcm_page_err : 1;
        unsigned int d1tcmaddr_out_320k_err : 1;
        unsigned int reserved_2 : 2;
        unsigned int itcm_err_bank0 : 1;
        unsigned int itcm_err_bank1 : 1;
        unsigned int itcm_err_bank2 : 1;
        unsigned int itcm_err_bank3 : 1;
        unsigned int itcm_err_bank4 : 1;
        unsigned int d0tcm_err_bank0 : 1;
        unsigned int d0tcm_err_bank1 : 1;
        unsigned int d0tcm_err_bank2 : 1;
        unsigned int d0tcm_err_bank3 : 1;
        unsigned int d0tcm_err_bank4 : 1;
        unsigned int d1tcm_err_bank0 : 1;
        unsigned int d1tcm_err_bank1 : 1;
        unsigned int d1tcm_err_bank2 : 1;
        unsigned int d1tcm_err_bank3 : 1;
        unsigned int d1tcm_err_bank4 : 1;
        unsigned int reserved_3 : 5;
    } reg;
} SOC_REMAPCTRL_TCM_ERR_TYPE_UNION;
#endif
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_page_err_START (0)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_page_err_END (0)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcmaddr_out_320k_err_START (1)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcmaddr_out_320k_err_END (1)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_page_err_START (4)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_page_err_END (4)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_START (5)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_END (5)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_page_err_START (8)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_page_err_END (8)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_START (9)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_END (9)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank0_START (12)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank0_END (12)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank1_START (13)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank1_END (13)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank2_START (14)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank2_END (14)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank3_START (15)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank3_END (15)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank4_START (16)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_itcm_err_bank4_END (16)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank0_START (17)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank0_END (17)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank1_START (18)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank1_END (18)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank2_START (19)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank2_END (19)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank3_START (20)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank3_END (20)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank4_START (21)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d0tcm_err_bank4_END (21)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank0_START (22)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank0_END (22)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank1_START (23)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank1_END (23)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank2_START (24)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank2_END (24)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank3_START (25)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank3_END (25)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank4_START (26)
#define SOC_REMAPCTRL_TCM_ERR_TYPE_d1tcm_err_bank4_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bank0_sel : 1;
        unsigned int bank1_sel : 1;
        unsigned int bank2_sel : 1;
        unsigned int bank3_sel : 1;
        unsigned int bank4_sel : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_REMAPCTRL_BANK_SEL_UNION;
#endif
#define SOC_REMAPCTRL_BANK_SEL_bank0_sel_START (0)
#define SOC_REMAPCTRL_BANK_SEL_bank0_sel_END (0)
#define SOC_REMAPCTRL_BANK_SEL_bank1_sel_START (1)
#define SOC_REMAPCTRL_BANK_SEL_bank1_sel_END (1)
#define SOC_REMAPCTRL_BANK_SEL_bank2_sel_START (2)
#define SOC_REMAPCTRL_BANK_SEL_bank2_sel_END (2)
#define SOC_REMAPCTRL_BANK_SEL_bank3_sel_START (3)
#define SOC_REMAPCTRL_BANK_SEL_bank3_sel_END (3)
#define SOC_REMAPCTRL_BANK_SEL_bank4_sel_START (4)
#define SOC_REMAPCTRL_BANK_SEL_bank4_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_err_addr : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_REMAPCTRL_ITCM_ERR_ADDR_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_ERR_ADDR_itcm_err_addr_START (0)
#define SOC_REMAPCTRL_ITCM_ERR_ADDR_itcm_err_addr_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_err_addr : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_REMAPCTRL_D0TCM_ERR_ADDR_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_ERR_ADDR_d0tcm_err_addr_START (0)
#define SOC_REMAPCTRL_D0TCM_ERR_ADDR_d0tcm_err_addr_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_err_addr : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_REMAPCTRL_D1TCM_ERR_ADDR_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_ERR_ADDR_d1tcm_err_addr_START (0)
#define SOC_REMAPCTRL_D1TCM_ERR_ADDR_d1tcm_err_addr_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itcm_err_cnt : 32;
    } reg;
} SOC_REMAPCTRL_ITCM_ERR_CNT_UNION;
#endif
#define SOC_REMAPCTRL_ITCM_ERR_CNT_itcm_err_cnt_START (0)
#define SOC_REMAPCTRL_ITCM_ERR_CNT_itcm_err_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d0tcm_err_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D0TCM_ERR_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D0TCM_ERR_CNT_d0tcm_err_cnt_START (0)
#define SOC_REMAPCTRL_D0TCM_ERR_CNT_d0tcm_err_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int d1tcm_err_cnt : 32;
    } reg;
} SOC_REMAPCTRL_D1TCM_ERR_CNT_UNION;
#endif
#define SOC_REMAPCTRL_D1TCM_ERR_CNT_d1tcm_err_cnt_START (0)
#define SOC_REMAPCTRL_D1TCM_ERR_CNT_d1tcm_err_cnt_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
