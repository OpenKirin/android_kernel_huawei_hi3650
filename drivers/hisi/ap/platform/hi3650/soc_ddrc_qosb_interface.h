#ifndef __SOC_DDRC_QOSB_INTERFACE_H__
#define __SOC_DDRC_QOSB_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_ADDR(base) ((base) + (0x000))
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_ADDR(base) ((base) + (0x004))
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_ADDR(base,fids) ((base) + (0x008+0x4*(fids)))
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_ADDR(base,fids) ((base) + (0x024+0x4*(fids)))
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_ADDR(base,fgps) ((base) + (0x040+0x4*(fgps)))
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_ADDR(base) ((base) + (0x060))
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_ADDR(base) ((base) + (0x064))
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ADDR(base,chans) ((base) + (0x068+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_ADDR(base,chans) ((base) + (0x078+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_ADDR(base) ((base) + (0x088))
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_ADDR(base,chans) ((base) + (0x08C+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_ADDR(base) ((base) + (0x09C))
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_ADDR(base) ((base) + (0x0A0))
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_ADDR(base) ((base) + (0x0A4))
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_ADDR(base) ((base) + (0x0A8))
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_ADDR(base) ((base) + (0x0AC))
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_ADDR(base) ((base) + (0x0B0))
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_ADDR(base) ((base) + (0x0B4))
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_ADDR(base) ((base) + (0x0B8))
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_ADDR(base) ((base) + (0x0BC))
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_ADDR(base) ((base) + (0x0D0))
#define SOC_DDRC_QOSB_QOSB_WRAGE0_ADDR(base) ((base) + (0x0D4))
#define SOC_DDRC_QOSB_QOSB_WRAGE1_ADDR(base) ((base) + (0x0D8))
#define SOC_DDRC_QOSB_QOSB_RDAGE0_ADDR(base) ((base) + (0x0DC))
#define SOC_DDRC_QOSB_QOSB_RDAGE1_ADDR(base) ((base) + (0x0E0))
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_ADDR(base) ((base) + (0x0E4))
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_ADDR(base) ((base) + (0x0E8))
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ADDR(base) ((base) + (0x0EC))
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ADDR(base) ((base) + (0x0F0))
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ADDR(base) ((base) + (0x0F4))
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ADDR(base) ((base) + (0x0F8))
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_ADDR(base) ((base) + (0x0FC))
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ADDR(base) ((base) + (0x100))
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ADDR(base) ((base) + (0x104))
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_ADDR(base) ((base) + (0x108))
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_ADDR(base,chans) ((base) + (0x10C+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR(base) ((base) + (0x120))
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_ADDR(base) ((base) + (0x124))
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_ADDR(base) ((base) + (0x128))
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_ADDR(base) ((base) + (0x12C))
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_ADDR(base) ((base) + (0x130))
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_ADDR(base) ((base) + (0x134))
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_ADDR(base,chans) ((base) + (0x140+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_ADDR(base,chans) ((base) + (0x150+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_ADDR(base,chans) ((base) + (0x160+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_INTMSK_ADDR(base) ((base) + (0x170))
#define SOC_DDRC_QOSB_QOSB_RINT_ADDR(base) ((base) + (0x174))
#define SOC_DDRC_QOSB_QOSB_INTSTS_ADDR(base) ((base) + (0x178))
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_ADDR(base) ((base) + (0x180))
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_ADDR(base,chans) ((base) + (0x190+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_ADDR(base,chans) ((base) + (0x1A0+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_ADDR(base,chans) ((base) + (0x1B0+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_ADDR(base,chans) ((base) + (0x1C0+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_ADDR(base,chans) ((base) + (0x1D0+0x4*(chans)))
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ADDR(base) ((base) + (0x1E0))
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_ADDR(base) ((base) + (0x1E4))
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_ADDR(base) ((base) + (0x1E8))
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_ADDR(base) ((base) + (0x1EC))
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_ADDR(base) ((base) + (0x1F0))
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_ADDR(base) ((base) + (0x1F4))
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_ADDR(base) ((base) + (0x1F8))
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ADDR(base) ((base) + (0x1FC))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_push_en : 1;
        unsigned int addr_push_en : 1;
        unsigned int mid_push_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_START (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_END (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_START (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_END (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_START (2)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int adpt_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int adpt_share_cnt : 16;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_START (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_END (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_START (4)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_id : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_START (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_id_mask : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_START (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_bandwidth : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_START (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_lvl : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_START (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_START (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ba_intleav_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int ba_cnt_lvl : 4;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_START (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_END (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_START (4)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int green_en : 1;
        unsigned int reserved_0: 3;
        unsigned int green_lvl : 4;
        unsigned int reserved_1: 24;
    } reg;
} SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_START (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_END (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_START (4)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_buf_byp : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_START (0)
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wbuf_lvl0 : 8;
        unsigned int wbuf_lvl1 : 8;
        unsigned int wbuf_pri1 : 3;
        unsigned int reserved : 1;
        unsigned int wbuf_lvl2 : 8;
        unsigned int wbuf_pri2 : 3;
        unsigned int wbuf_ptun_en : 1;
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_START (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_END (7)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_START (8)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_END (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_START (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_END (18)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_START (20)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_END (27)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_START (28)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_END (30)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_START (31)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_tout0 : 8;
        unsigned int wr_tout1 : 8;
        unsigned int wr_tout2 : 8;
        unsigned int wr_tout3 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_START (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_END (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_START (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_END (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_START (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_END (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_START (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_tout4 : 8;
        unsigned int wr_tout5 : 8;
        unsigned int wr_tout6 : 8;
        unsigned int wr_tout7 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_START (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_END (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_START (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_END (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_START (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_END (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_START (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_tout8 : 8;
        unsigned int wr_tout9 : 8;
        unsigned int wr_tout10 : 8;
        unsigned int wr_tout11 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_START (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_END (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_START (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_END (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_START (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_END (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_START (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_tout12 : 8;
        unsigned int wr_tout13 : 8;
        unsigned int wr_tout14 : 8;
        unsigned int wr_tout15 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_START (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_END (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_START (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_END (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_START (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_END (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_START (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_tout0 : 8;
        unsigned int rd_tout1 : 8;
        unsigned int rd_tout2 : 8;
        unsigned int rd_tout3 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_START (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_END (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_START (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_END (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_START (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_END (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_START (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_tout4 : 8;
        unsigned int rd_tout5 : 8;
        unsigned int rd_tout6 : 8;
        unsigned int rd_tout7 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_START (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_END (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_START (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_END (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_START (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_END (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_START (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_tout8 : 8;
        unsigned int rd_tout9 : 8;
        unsigned int rd_tout10 : 8;
        unsigned int rd_tout11 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_START (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_END (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_START (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_END (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_START (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_END (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_START (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_tout12 : 8;
        unsigned int rd_tout13 : 8;
        unsigned int rd_tout14 : 8;
        unsigned int rd_tout15 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_START (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_END (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_START (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_END (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_START (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_END (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_START (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wrtout_map0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int wrtout_map1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int wrtout_map2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int wrtout_map3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_START (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_END (4)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_START (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_END (12)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_START (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_END (20)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_START (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdtout_map0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int rdtout_map1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int rdtout_map2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int rdtout_map3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_START (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_END (4)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_START (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_END (12)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_START (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_END (20)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_START (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_age_prd0 : 4;
        unsigned int wr_age_prd1 : 4;
        unsigned int wr_age_prd2 : 4;
        unsigned int wr_age_prd3 : 4;
        unsigned int wr_age_prd4 : 4;
        unsigned int wr_age_prd5 : 4;
        unsigned int wr_age_prd6 : 4;
        unsigned int wr_age_prd7 : 4;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_START (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_END (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_START (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_END (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_START (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_END (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_START (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_END (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_START (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_END (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_START (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_END (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_START (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_END (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_START (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_age_prd8 : 4;
        unsigned int wr_age_prd9 : 4;
        unsigned int wr_age_prd10 : 4;
        unsigned int wr_age_prd11 : 4;
        unsigned int wr_age_prd12 : 4;
        unsigned int wr_age_prd13 : 4;
        unsigned int wr_age_prd14 : 4;
        unsigned int wr_age_prd15 : 4;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_START (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_END (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_START (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_END (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_START (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_END (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_START (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_END (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_START (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_END (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_START (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_END (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_START (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_END (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_START (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_age_prd0 : 4;
        unsigned int rd_age_prd1 : 4;
        unsigned int rd_age_prd2 : 4;
        unsigned int rd_age_prd3 : 4;
        unsigned int rd_age_prd4 : 4;
        unsigned int rd_age_prd5 : 4;
        unsigned int rd_age_prd6 : 4;
        unsigned int rd_age_prd7 : 4;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_START (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_END (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_START (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_END (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_START (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_END (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_START (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_END (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_START (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_END (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_START (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_END (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_START (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_END (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_START (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_age_prd8 : 4;
        unsigned int rd_age_prd9 : 4;
        unsigned int rd_age_prd10 : 4;
        unsigned int rd_age_prd11 : 4;
        unsigned int rd_age_prd12 : 4;
        unsigned int rd_age_prd13 : 4;
        unsigned int rd_age_prd14 : 4;
        unsigned int rd_age_prd15 : 4;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_START (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_END (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_START (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_END (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_START (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_END (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_START (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_END (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_START (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_END (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_START (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_END (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_START (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_END (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_START (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wrage_map0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int wrage_map1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int wrage_map2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int wrage_map3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_START (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_END (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_START (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_END (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_START (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_END (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_START (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdage_map0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int rdage_map1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int rdage_map2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int rdage_map3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_START (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_END (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_START (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_END (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_START (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_END (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_START (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_rowhit_pri_lvl : 3;
        unsigned int reserved_0 : 1;
        unsigned int ch1_rowhit_pri_lvl : 3;
        unsigned int reserved_1 : 1;
        unsigned int ch2_rowhit_pri_lvl : 3;
        unsigned int reserved_2 : 1;
        unsigned int ch3_rowhit_pri_lvl : 3;
        unsigned int reserved_3 : 17;
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_START (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_END (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_START (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_END (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_START (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_END (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_START (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_rowhit_pri0 : 3;
        unsigned int reserved_0 : 1;
        unsigned int ch0_rowhit_pri1 : 3;
        unsigned int reserved_1 : 1;
        unsigned int ch1_rowhit_pri0 : 3;
        unsigned int reserved_2 : 1;
        unsigned int ch1_rowhit_pri1 : 3;
        unsigned int reserved_3 : 1;
        unsigned int ch2_rowhit_pri0 : 3;
        unsigned int reserved_4 : 1;
        unsigned int ch2_rowhit_pri1 : 3;
        unsigned int reserved_5 : 1;
        unsigned int ch3_rowhit_pri0 : 3;
        unsigned int reserved_6 : 1;
        unsigned int ch3_rowhit_pri1 : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_START (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_END (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_START (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_END (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_START (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_END (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_START (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_END (14)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_START (16)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_END (18)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_START (20)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_END (22)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_START (24)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_END (26)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_START (28)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_row_hit_en : 1;
        unsigned int ch1_row_hit_en : 1;
        unsigned int ch2_row_hit_en : 1;
        unsigned int ch3_row_hit_en : 1;
        unsigned int ch0_dual_flow_en : 1;
        unsigned int ch1_dual_flow_en : 1;
        unsigned int ch2_dual_flow_en : 1;
        unsigned int ch3_dual_flow_en : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_START (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_END (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_START (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_END (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_START (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_END (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_START (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_END (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_START (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_END (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_START (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_END (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_START (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_END (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_START (7)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0wramerrinj : 2;
        unsigned int ch1wramerrinj : 2;
        unsigned int ch2wramerrinj : 2;
        unsigned int ch3wramerrinj : 2;
        unsigned int reserved_0 : 8;
        unsigned int ch0_wbuf_one_bit_err : 1;
        unsigned int ch0_wbuf_two_bit_err : 1;
        unsigned int ch1_wbuf_one_bit_err : 1;
        unsigned int ch1_wbuf_two_bit_err : 1;
        unsigned int ch2_wbuf_one_bit_err : 1;
        unsigned int ch2_wbuf_two_bit_err : 1;
        unsigned int ch3_wbuf_one_bit_err : 1;
        unsigned int ch3_wbuf_two_bit_err : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_START (0)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_END (1)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_START (2)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_END (3)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_START (4)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_END (5)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_START (6)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_END (7)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_START (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_END (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_START (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_END (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_START (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_END (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_START (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_END (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_START (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_END (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_START (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_END (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_START (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_END (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_START (23)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cramerrinj : 2;
        unsigned int reserved_0 : 2;
        unsigned int cram_one_bit_err : 1;
        unsigned int cram_two_bit_err : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_START (0)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_END (1)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_START (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_END (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_START (5)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_rdr_err_inj : 2;
        unsigned int ch1_rdr_err_inj : 2;
        unsigned int ch2_rdr_err_inj : 2;
        unsigned int ch3_rdr_err_inj : 2;
        unsigned int reserved_0 : 8;
        unsigned int ch0_rdr_one_bit_err : 1;
        unsigned int ch0_rdr_two_bit_err : 1;
        unsigned int ch1_rdr_one_bit_err : 1;
        unsigned int ch1_rdr_two_bit_err : 1;
        unsigned int ch2_rdr_one_bit_err : 1;
        unsigned int ch2_rdr_two_bit_err : 1;
        unsigned int ch3_rdr_one_bit_err : 1;
        unsigned int ch3_rdr_two_bit_err : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_START (0)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_END (1)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_START (2)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_END (3)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_START (4)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_END (5)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_START (6)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_END (7)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_START (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_END (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_START (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_END (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_START (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_END (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_START (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_END (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_START (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_END (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_START (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_END (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_START (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_END (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_START (23)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ram_tmod : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_START (0)
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dyn_ck_gate : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_START (0)
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cmd_full_lvl : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_START (0)
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perf_prd : 28;
        unsigned int perf_mode : 1;
        unsigned int perf_en : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_START (0)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_END (27)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_START (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_END (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_START (29)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_cmd_sum : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_START (0)
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grp_cmd_valid_l : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_START (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grp_cmd_valid_m0 : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_START (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grp_cmd_valid_m1 : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_START (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grp_cmd_valid_h : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_START (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buf_ldata_valid_l : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_START (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buf_ldata_valid_h : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_START (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e_vld : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_START (0)
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_stat_int_mask : 1;
        unsigned int rdrbuf_serr_int_mask : 1;
        unsigned int rdrbuf_derr_int_mask : 1;
        unsigned int qosbuf_serr_int_mask : 1;
        unsigned int qosbuf_derr_int_mask : 1;
        unsigned int qoscid_serr_int_mask : 1;
        unsigned int qoscid_derr_int_mask : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_DDRC_QOSB_QOSB_INTMSK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_START (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_END (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_START (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_END (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_START (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_END (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_START (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_END (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_START (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_END (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_START (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_END (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_START (6)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_stat_rint : 1;
        unsigned int rdrbuf_serr_rint : 1;
        unsigned int rdrbuf_derr_rint : 1;
        unsigned int qosbuf_serr_rint : 1;
        unsigned int qosbuf_derr_rint : 1;
        unsigned int qoscid_serr_rint : 1;
        unsigned int qoscid_derr_rint : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_DDRC_QOSB_QOSB_RINT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_START (0)
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_END (0)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_START (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_END (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_START (2)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_END (2)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_START (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_END (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_START (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_END (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_START (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_END (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_START (6)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_stat_intsts : 1;
        unsigned int rdrbuf_serr_intsts : 1;
        unsigned int rdrbuf_derr_intsts : 1;
        unsigned int qosbuf_serr_intsts : 1;
        unsigned int qosbuf_derr_intsts : 1;
        unsigned int qoscid_serr_intsts : 1;
        unsigned int qoscid_derr_intsts : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_DDRC_QOSB_QOSB_INTSTS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_START (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_END (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_START (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_END (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_START (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_END (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_START (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_END (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_START (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_END (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_START (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_END (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_START (6)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_cmd_cnt : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnk0_cmd_cnt : 8;
        unsigned int rnk1_cmd_cnt : 8;
        unsigned int rnk2_cmd_cnt : 8;
        unsigned int rnk3_cmd_cnt : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_END (7)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_START (8)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_END (15)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_START (16)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_END (23)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_START (24)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bnk0_cmd_cnt : 8;
        unsigned int bnk1_cmd_cnt : 8;
        unsigned int bnk2_cmd_cnt : 8;
        unsigned int bnk3_cmd_cnt : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_END (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_START (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_END (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_START (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_END (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_START (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bnk4_cmd_cnt : 8;
        unsigned int bnk5_cmd_cnt : 8;
        unsigned int bnk6_cmd_cnt : 8;
        unsigned int bnk7_cmd_cnt : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_END (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_START (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_END (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_START (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_END (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_START (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bnk8_cmd_cnt : 8;
        unsigned int bnk9_cmd_cnt : 8;
        unsigned int bnk10_cmd_cnt : 8;
        unsigned int bnk11_cmd_cnt : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_END (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_START (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_END (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_START (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_END (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_START (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bnk12_cmd_cnt : 8;
        unsigned int bnk13_cmd_cnt : 8;
        unsigned int bnk14_cmd_cnt : 8;
        unsigned int bnk15_cmd_cnt : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_START (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_END (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_START (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_END (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_START (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_END (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_START (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_cmd_ostd : 8;
        unsigned int ch1_cmd_ostd : 8;
        unsigned int ch2_cmd_ostd : 8;
        unsigned int ch3_cmd_ostd : 8;
    } reg;
} SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_START (0)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_END (7)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_START (8)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_END (15)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_START (16)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_END (23)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_START (24)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_wr_cmd_sum : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_START (0)
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_rd_cmd_sum : 32;
    } reg;
} SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_START (0)
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grt_fifo_vld_0 : 1;
        unsigned int grt_fifo_pid_0 : 7;
        unsigned int grt_fifo_vld_1 : 1;
        unsigned int grt_fifo_pid_1 : 7;
        unsigned int grt_fifo_vld_2 : 1;
        unsigned int grt_fifo_pid_2 : 7;
        unsigned int grt_fifo_vld_3 : 1;
        unsigned int grt_fifo_pid_3 : 7;
    } reg;
} SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_START (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_END (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_START (1)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_END (7)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_START (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_END (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_START (9)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_END (15)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_START (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_END (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_START (17)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_END (23)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_START (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_END (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_START (25)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeout_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_START (0)
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wbuf_lcnt : 16;
        unsigned int wbuf_hcnt : 16;
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_START (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_END (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_START (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rhit_lcnt : 16;
        unsigned int rhit_hcnt : 16;
    } reg;
} SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_START (0)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_END (15)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_START (16)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_merge : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_START (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
