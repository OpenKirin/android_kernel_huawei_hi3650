#ifndef __SOC_DMAC_INTERFACE_H__
#define __SOC_DMAC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DMAC_INT_STAT_ADDR(base,in) ((base) + (0x0000+0x40*(in)))
#define SOC_DMAC_INT_TC1_ADDR(base,in) ((base) + (0x0004+0x40*(in)))
#define SOC_DMAC_INT_TC2_ADDR(base,in) ((base) + (0x0008+0x40*(in)))
#define SOC_DMAC_INT_ERR1_ADDR(base,in) ((base) + (0x000C+0x40*(in)))
#define SOC_DMAC_INT_ERR2_ADDR(base,in) ((base) + (0x0010+0x40*(in)))
#define SOC_DMAC_INT_ERR3_ADDR(base,in) ((base) + (0x0014+0x40*(in)))
#define SOC_DMAC_INT_TC1_MASK_ADDR(base,in) ((base) + (0x0018+0x40*(in)))
#define SOC_DMAC_INT_TC2_MASK_ADDR(base,in) ((base) + (0x001C+0x40*(in)))
#define SOC_DMAC_INT_ERR1_MASK_ADDR(base,in) ((base) + (0x0020+0x40*(in)))
#define SOC_DMAC_INT_ERR2_MASK_ADDR(base,in) ((base) + (0x0024+0x40*(in)))
#define SOC_DMAC_INT_ERR3_MASK_ADDR(base,in) ((base) + (0x0028+0x40*(in)))
#define SOC_DMAC_INT_TC1_RAW_ADDR(base) ((base) + (0x0600))
#define SOC_DMAC_INT_TC2_RAW_ADDR(base) ((base) + (0x0608))
#define SOC_DMAC_INT_ERR1_RAW_ADDR(base) ((base) + (0x0610))
#define SOC_DMAC_INT_ERR2_RAW_ADDR(base) ((base) + (0x0618))
#define SOC_DMAC_INT_ERR3_RAW_ADDR(base) ((base) + (0x0620))
#define SOC_DMAC_SREQ_ADDR(base) ((base) + (0x660))
#define SOC_DMAC_LSREQ_ADDR(base) ((base) + (0x664))
#define SOC_DMAC_BREQ_ADDR(base) ((base) + (0x668))
#define SOC_DMAC_LBREQ_ADDR(base) ((base) + (0x66C))
#define SOC_DMAC_FREQ_ADDR(base) ((base) + (0x670))
#define SOC_DMAC_LFREQ_ADDR(base) ((base) + (0x674))
#define SOC_DMAC_CH_PRI_ADDR(base) ((base) + (0x688))
#define SOC_DMAC_CH_STAT_ADDR(base) ((base) + (0x690))
#define SOC_DMAC_SEC_CTRL_ADDR(base) ((base) + (0x0694))
#define SOC_DMAC_DMA_CTRL_ADDR(base) ((base) + (0x0698))
#define SOC_DMAC_CX_CURR_CNT1_ADDR(base,cn) ((base) + (0x0700+0x10*(cn)))
#define SOC_DMAC_CX_CURR_CNT0_ADDR(base,cn) ((base) + (0x0704+0x10*(cn)))
#define SOC_DMAC_CX_CURR_SRC_ADDR_ADDR(base,cn) ((base) + (0x0708+0x10*(cn)))
#define SOC_DMAC_CX_CURR_DES_ADDR_ADDR(base,cn) ((base) + (0x070C+0x10*(cn)))
#define SOC_DMAC_CX_LLI_ADDR(base,cn) ((base) + (0x0800+0x40*(cn)))
#define SOC_DMAC_CX_BINDX_ADDR(base,cn) ((base) + (0x0804+0x40*(cn)))
#define SOC_DMAC_CX_CINDX_ADDR(base,cn) ((base) + (0x0808+0x40*(cn)))
#define SOC_DMAC_CX_CNT1_ADDR(base,cn) ((base) + (0x080C+0x40*(cn)))
#define SOC_DMAC_CX_CNT0_ADDR(base,cn) ((base) + (0x0810+0x40*(cn)))
#define SOC_DMAC_CX_SRC_ADDR_ADDR(base,cn) ((base) + (0x0814+0x40*(cn)))
#define SOC_DMAC_CX_DES_ADDR_ADDR(base,cn) ((base) + (0x0818+0x40*(cn)))
#define SOC_DMAC_CX_CONFIG_ADDR(base,cn) ((base) + (0x081C+0x40*(cn)))
#define SOC_DMAC_CX_AXI_CONF_ADDR(base,cn) ((base) + (0x0820+0x40*(cn)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_stat : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_STAT_UNION;
#endif
#define SOC_DMAC_INT_STAT_int_stat_START (0)
#define SOC_DMAC_INT_STAT_int_stat_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC1_UNION;
#endif
#define SOC_DMAC_INT_TC1_int_tc1_START (0)
#define SOC_DMAC_INT_TC1_int_tc1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc2 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC2_UNION;
#endif
#define SOC_DMAC_INT_TC2_int_tc2_START (0)
#define SOC_DMAC_INT_TC2_int_tc2_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR1_UNION;
#endif
#define SOC_DMAC_INT_ERR1_int_err1_START (0)
#define SOC_DMAC_INT_ERR1_int_err1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err2 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR2_UNION;
#endif
#define SOC_DMAC_INT_ERR2_int_err2_START (0)
#define SOC_DMAC_INT_ERR2_int_err2_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err3 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR3_UNION;
#endif
#define SOC_DMAC_INT_ERR3_int_err3_START (0)
#define SOC_DMAC_INT_ERR3_int_err3_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc1_mask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC1_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_START (0)
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc2_mask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC2_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_START (0)
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err1_mask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR1_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_START (0)
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err2_mask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR2_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_START (0)
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err3_mask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR3_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_START (0)
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc1_raw : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC1_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_START (0)
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_tc2_raw : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_TC2_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_START (0)
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err1_raw : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR1_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_START (0)
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err2_raw : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR2_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_START (0)
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_err3_raw : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_INT_ERR3_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_START (0)
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sreq : 32;
    } reg;
} SOC_DMAC_SREQ_UNION;
#endif
#define SOC_DMAC_SREQ_sreq_START (0)
#define SOC_DMAC_SREQ_sreq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lsreq : 32;
    } reg;
} SOC_DMAC_LSREQ_UNION;
#endif
#define SOC_DMAC_LSREQ_lsreq_START (0)
#define SOC_DMAC_LSREQ_lsreq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int breq : 32;
    } reg;
} SOC_DMAC_BREQ_UNION;
#endif
#define SOC_DMAC_BREQ_breq_START (0)
#define SOC_DMAC_BREQ_breq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lbreq : 32;
    } reg;
} SOC_DMAC_LBREQ_UNION;
#endif
#define SOC_DMAC_LBREQ_lbreq_START (0)
#define SOC_DMAC_LBREQ_lbreq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int freq : 32;
    } reg;
} SOC_DMAC_FREQ_UNION;
#endif
#define SOC_DMAC_FREQ_freq_START (0)
#define SOC_DMAC_FREQ_freq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lfreq : 32;
    } reg;
} SOC_DMAC_LFREQ_UNION;
#endif
#define SOC_DMAC_LFREQ_lfreq_START (0)
#define SOC_DMAC_LFREQ_lfreq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch0_pri : 2;
        unsigned int ch1_pri : 2;
        unsigned int ch2_pri : 2;
        unsigned int ch3_pri : 2;
        unsigned int ch4_pri : 2;
        unsigned int ch5_pri : 2;
        unsigned int ch6_pri : 2;
        unsigned int ch7_pri : 2;
        unsigned int ch8_pri : 2;
        unsigned int ch9_pri : 2;
        unsigned int ch10_pri : 2;
        unsigned int ch11_pri : 2;
        unsigned int ch12_pri : 2;
        unsigned int ch13_pri : 2;
        unsigned int ch14_pri : 2;
        unsigned int ch15_pri : 2;
    } reg;
} SOC_DMAC_CH_PRI_UNION;
#endif
#define SOC_DMAC_CH_PRI_ch0_pri_START (0)
#define SOC_DMAC_CH_PRI_ch0_pri_END (1)
#define SOC_DMAC_CH_PRI_ch1_pri_START (2)
#define SOC_DMAC_CH_PRI_ch1_pri_END (3)
#define SOC_DMAC_CH_PRI_ch2_pri_START (4)
#define SOC_DMAC_CH_PRI_ch2_pri_END (5)
#define SOC_DMAC_CH_PRI_ch3_pri_START (6)
#define SOC_DMAC_CH_PRI_ch3_pri_END (7)
#define SOC_DMAC_CH_PRI_ch4_pri_START (8)
#define SOC_DMAC_CH_PRI_ch4_pri_END (9)
#define SOC_DMAC_CH_PRI_ch5_pri_START (10)
#define SOC_DMAC_CH_PRI_ch5_pri_END (11)
#define SOC_DMAC_CH_PRI_ch6_pri_START (12)
#define SOC_DMAC_CH_PRI_ch6_pri_END (13)
#define SOC_DMAC_CH_PRI_ch7_pri_START (14)
#define SOC_DMAC_CH_PRI_ch7_pri_END (15)
#define SOC_DMAC_CH_PRI_ch8_pri_START (16)
#define SOC_DMAC_CH_PRI_ch8_pri_END (17)
#define SOC_DMAC_CH_PRI_ch9_pri_START (18)
#define SOC_DMAC_CH_PRI_ch9_pri_END (19)
#define SOC_DMAC_CH_PRI_ch10_pri_START (20)
#define SOC_DMAC_CH_PRI_ch10_pri_END (21)
#define SOC_DMAC_CH_PRI_ch11_pri_START (22)
#define SOC_DMAC_CH_PRI_ch11_pri_END (23)
#define SOC_DMAC_CH_PRI_ch12_pri_START (24)
#define SOC_DMAC_CH_PRI_ch12_pri_END (25)
#define SOC_DMAC_CH_PRI_ch13_pri_START (26)
#define SOC_DMAC_CH_PRI_ch13_pri_END (27)
#define SOC_DMAC_CH_PRI_ch14_pri_START (28)
#define SOC_DMAC_CH_PRI_ch14_pri_END (29)
#define SOC_DMAC_CH_PRI_ch15_pri_START (30)
#define SOC_DMAC_CH_PRI_ch15_pri_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_stat : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_CH_STAT_UNION;
#endif
#define SOC_DMAC_CH_STAT_ch_stat_START (0)
#define SOC_DMAC_CH_STAT_ch_stat_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int global_sec : 1;
        unsigned int intr_sec_ctrl : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DMAC_SEC_CTRL_UNION;
#endif
#define SOC_DMAC_SEC_CTRL_global_sec_START (0)
#define SOC_DMAC_SEC_CTRL_global_sec_END (0)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_START (1)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int halt_ack : 1;
        unsigned int halt_req : 1;
        unsigned int reserved_0: 2;
        unsigned int conf_out4 : 1;
        unsigned int reserved_1: 27;
    } reg;
} SOC_DMAC_DMA_CTRL_UNION;
#endif
#define SOC_DMAC_DMA_CTRL_halt_ack_START (0)
#define SOC_DMAC_DMA_CTRL_halt_ack_END (0)
#define SOC_DMAC_DMA_CTRL_halt_req_START (1)
#define SOC_DMAC_DMA_CTRL_halt_req_END (1)
#define SOC_DMAC_DMA_CTRL_conf_out4_START (4)
#define SOC_DMAC_DMA_CTRL_conf_out4_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int curr_c_count : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_CX_CURR_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_START (0)
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int curr_a_count : 16;
        unsigned int curr_b_count : 16;
    } reg;
} SOC_DMAC_CX_CURR_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_START (0)
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_END (15)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_START (16)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int curr_src_addr : 32;
    } reg;
} SOC_DMAC_CX_CURR_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_START (0)
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int curr_des_addr : 32;
    } reg;
} SOC_DMAC_CX_CURR_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_START (0)
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int chain_en : 2;
        unsigned int reserved : 3;
        unsigned int lli : 27;
    } reg;
} SOC_DMAC_CX_LLI_UNION;
#endif
#define SOC_DMAC_CX_LLI_chain_en_START (0)
#define SOC_DMAC_CX_LLI_chain_en_END (1)
#define SOC_DMAC_CX_LLI_lli_START (5)
#define SOC_DMAC_CX_LLI_lli_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int des_bindx : 15;
        unsigned int des_bsign : 1;
        unsigned int src_bindx : 15;
        unsigned int src_bsign : 1;
    } reg;
} SOC_DMAC_CX_BINDX_UNION;
#endif
#define SOC_DMAC_CX_BINDX_des_bindx_START (0)
#define SOC_DMAC_CX_BINDX_des_bindx_END (14)
#define SOC_DMAC_CX_BINDX_des_bsign_START (15)
#define SOC_DMAC_CX_BINDX_des_bsign_END (15)
#define SOC_DMAC_CX_BINDX_src_bindx_START (16)
#define SOC_DMAC_CX_BINDX_src_bindx_END (30)
#define SOC_DMAC_CX_BINDX_src_bsign_START (31)
#define SOC_DMAC_CX_BINDX_src_bsign_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int des_cindx : 15;
        unsigned int des_csign : 1;
        unsigned int src_cindx : 15;
        unsigned int src_csign : 1;
    } reg;
} SOC_DMAC_CX_CINDX_UNION;
#endif
#define SOC_DMAC_CX_CINDX_des_cindx_START (0)
#define SOC_DMAC_CX_CINDX_des_cindx_END (14)
#define SOC_DMAC_CX_CINDX_des_csign_START (15)
#define SOC_DMAC_CX_CINDX_des_csign_END (15)
#define SOC_DMAC_CX_CINDX_src_cindx_START (16)
#define SOC_DMAC_CX_CINDX_src_cindx_END (30)
#define SOC_DMAC_CX_CINDX_src_csign_START (31)
#define SOC_DMAC_CX_CINDX_src_csign_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int c_count : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DMAC_CX_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CNT1_c_count_START (0)
#define SOC_DMAC_CX_CNT1_c_count_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a_count : 16;
        unsigned int b_count : 16;
    } reg;
} SOC_DMAC_CX_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CNT0_a_count_START (0)
#define SOC_DMAC_CX_CNT0_a_count_END (15)
#define SOC_DMAC_CX_CNT0_b_count_START (16)
#define SOC_DMAC_CX_CNT0_b_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int src_addr : 32;
    } reg;
} SOC_DMAC_CX_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_SRC_ADDR_src_addr_START (0)
#define SOC_DMAC_CX_SRC_ADDR_src_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int des_addr : 32;
    } reg;
} SOC_DMAC_CX_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_DES_ADDR_des_addr_START (0)
#define SOC_DMAC_CX_DES_ADDR_des_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_en : 1;
        unsigned int itc_en : 1;
        unsigned int flow_ctrl : 2;
        unsigned int peri : 6;
        unsigned int reserved_0: 2;
        unsigned int dw : 3;
        unsigned int reserved_1: 1;
        unsigned int sw : 3;
        unsigned int reserved_2: 1;
        unsigned int dl : 4;
        unsigned int sl : 4;
        unsigned int dmode : 1;
        unsigned int smode : 1;
        unsigned int di : 1;
        unsigned int si : 1;
    } reg;
} SOC_DMAC_CX_CONFIG_UNION;
#endif
#define SOC_DMAC_CX_CONFIG_ch_en_START (0)
#define SOC_DMAC_CX_CONFIG_ch_en_END (0)
#define SOC_DMAC_CX_CONFIG_itc_en_START (1)
#define SOC_DMAC_CX_CONFIG_itc_en_END (1)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_START (2)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_END (3)
#define SOC_DMAC_CX_CONFIG_peri_START (4)
#define SOC_DMAC_CX_CONFIG_peri_END (9)
#define SOC_DMAC_CX_CONFIG_dw_START (12)
#define SOC_DMAC_CX_CONFIG_dw_END (14)
#define SOC_DMAC_CX_CONFIG_sw_START (16)
#define SOC_DMAC_CX_CONFIG_sw_END (18)
#define SOC_DMAC_CX_CONFIG_dl_START (20)
#define SOC_DMAC_CX_CONFIG_dl_END (23)
#define SOC_DMAC_CX_CONFIG_sl_START (24)
#define SOC_DMAC_CX_CONFIG_sl_END (27)
#define SOC_DMAC_CX_CONFIG_dmode_START (28)
#define SOC_DMAC_CX_CONFIG_dmode_END (28)
#define SOC_DMAC_CX_CONFIG_smode_START (29)
#define SOC_DMAC_CX_CONFIG_smode_END (29)
#define SOC_DMAC_CX_CONFIG_di_START (30)
#define SOC_DMAC_CX_CONFIG_di_END (30)
#define SOC_DMAC_CX_CONFIG_si_START (31)
#define SOC_DMAC_CX_CONFIG_si_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aruser : 5;
        unsigned int arprot : 3;
        unsigned int arcache : 4;
        unsigned int awuser : 5;
        unsigned int awprot : 3;
        unsigned int awcache : 4;
        unsigned int reserved : 8;
    } reg;
} SOC_DMAC_CX_AXI_CONF_UNION;
#endif
#define SOC_DMAC_CX_AXI_CONF_aruser_START (0)
#define SOC_DMAC_CX_AXI_CONF_aruser_END (4)
#define SOC_DMAC_CX_AXI_CONF_arprot_START (5)
#define SOC_DMAC_CX_AXI_CONF_arprot_END (7)
#define SOC_DMAC_CX_AXI_CONF_arcache_START (8)
#define SOC_DMAC_CX_AXI_CONF_arcache_END (11)
#define SOC_DMAC_CX_AXI_CONF_awuser_START (12)
#define SOC_DMAC_CX_AXI_CONF_awuser_END (16)
#define SOC_DMAC_CX_AXI_CONF_awprot_START (17)
#define SOC_DMAC_CX_AXI_CONF_awprot_END (19)
#define SOC_DMAC_CX_AXI_CONF_awcache_START (20)
#define SOC_DMAC_CX_AXI_CONF_awcache_END (23)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
