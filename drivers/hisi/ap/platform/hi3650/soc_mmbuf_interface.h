#ifndef __SOC_MMBUF_INTERFACE_H__
#define __SOC_MMBUF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_MMBUF_SMC_LOCK_ADDR(base) ((base) + (0x0000))
#define SOC_MMBUF_SMC_MEM_LP_ADDR(base) ((base) + (0x0004))
#define SOC_MMBUF_GCLK_CS_ADDR(base) ((base) + (0x000C))
#define SOC_MMBUF_SMC_QOS_BACKDOOR_ADDR(base) ((base) + (0x0010))
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_ADDR(base) ((base) + (0x0014))
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_ADDR(base) ((base) + (0x0018))
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_ADDR(base) ((base) + (0x001C))
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_ADDR(base) ((base) + (0x0020))
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_ADDR(base) ((base) + (0x0024))
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_ADDR(base) ((base) + (0x0028))
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_ADDR(base) ((base) + (0x002C))
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_ADDR(base) ((base) + (0x0030))
#define SOC_MMBUF_SMC_CS_IDLE_ADDR(base) ((base) + (0x0034))
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_ADDR(base) ((base) + (0x0038))
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_ADDR(base) ((base) + (0x003C))
#define SOC_MMBUF_SP_SRAM_STATE0_ADDR(base) ((base) + (0x0040))
#define SOC_MMBUF_SP_SRAM_STATE1_ADDR(base) ((base) + (0x0044))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smc_lock : 32;
    } reg;
} SOC_MMBUF_SMC_LOCK_UNION;
#endif
#define SOC_MMBUF_SMC_LOCK_smc_lock_START (0)
#define SOC_MMBUF_SMC_LOCK_smc_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smc_ls_en : 1;
        unsigned int smc_ds_en : 1;
        unsigned int reserved_0 : 2;
        unsigned int lp_exit_cycle : 4;
        unsigned int lp_enter_cycle : 16;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_MMBUF_SMC_MEM_LP_UNION;
#endif
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_START (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_END (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_START (1)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_END (1)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_START (4)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_END (7)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_START (8)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_s0_clock_disable : 1;
        unsigned int axi_s1_clock_disable : 1;
        unsigned int axi_s2_clock_disable : 1;
        unsigned int axi_s3_clock_disable : 1;
        unsigned int axi_s4_clock_disable : 1;
        unsigned int axi_s5_clock_disable : 1;
        unsigned int axi_s6_clock_disable : 1;
        unsigned int axi_s7_clock_disable : 1;
        unsigned int axi_s8_clock_disable : 1;
        unsigned int axi_s9_clock_disable : 1;
        unsigned int axi_s10_clock_disable : 1;
        unsigned int axi_s11_clock_disable : 1;
        unsigned int axi_s12_clock_disable : 1;
        unsigned int axi_s13_clock_disable : 1;
        unsigned int axi_s14_clock_disable : 1;
        unsigned int axi_s15_clock_disable : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_MMBUF_GCLK_CS_UNION;
#endif
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_START (0)
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_END (0)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_START (1)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_END (1)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_START (2)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_END (2)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_START (3)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_END (3)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_START (4)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_END (4)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_START (5)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_END (5)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_START (6)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_END (6)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_START (7)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_END (7)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_START (8)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_END (8)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_START (9)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_END (9)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_START (10)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_END (10)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_START (11)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_END (11)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_START (12)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_END (12)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_START (13)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_END (13)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_START (14)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_END (14)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_START (15)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int s0_qos_modify_en : 1;
        unsigned int s0_qos_modify_value : 1;
        unsigned int s1_qos_modify_en : 1;
        unsigned int s1_qos_modify_value : 1;
        unsigned int s2_qos_modify_en : 1;
        unsigned int s2_qos_modify_value : 1;
        unsigned int s3_qos_modify_en : 1;
        unsigned int s3_qos_modify_value : 1;
        unsigned int s4_qos_modify_en : 1;
        unsigned int s4_qos_modify_value : 1;
        unsigned int s5_qos_modify_en : 1;
        unsigned int s5_qos_modify_value : 1;
        unsigned int s6_qos_modify_en : 1;
        unsigned int s6_qos_modify_value : 1;
        unsigned int s7_qos_modify_en : 1;
        unsigned int s7_qos_modify_value : 1;
        unsigned int s8_qos_modify_en : 1;
        unsigned int s8_qos_modify_value : 1;
        unsigned int s9_qos_modify_en : 1;
        unsigned int s9_qos_modify_value : 1;
        unsigned int s10_qos_modify_en : 1;
        unsigned int s10_qos_modify_value : 1;
        unsigned int s11_qos_modify_en : 1;
        unsigned int s11_qos_modify_value : 1;
        unsigned int s12_qos_modify_en : 1;
        unsigned int s12_qos_modify_value : 1;
        unsigned int s13_qos_modify_en : 1;
        unsigned int s13_qos_modify_value : 1;
        unsigned int s14_qos_modify_en : 1;
        unsigned int s14_qos_modify_value : 1;
        unsigned int s15_qos_modify_en : 1;
        unsigned int s15_qos_modify_value : 1;
    } reg;
} SOC_MMBUF_SMC_QOS_BACKDOOR_UNION;
#endif
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_START (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_END (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_START (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_END (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_START (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_END (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_START (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_END (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_START (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_END (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_START (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_END (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_START (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_END (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_START (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_END (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_START (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_END (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_START (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_END (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_START (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_END (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_START (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_END (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_START (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_END (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_START (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_END (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_START (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_END (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_START (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_END (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_START (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_END (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_START (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_END (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_START (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_END (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_START (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_END (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_START (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_END (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_START (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_END (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_START (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_END (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_START (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_END (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_START (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_END (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_START (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_END (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_START (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_END (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_START (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_END (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_START (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_END (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_START (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_END (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_START (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_END (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_START (31)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs0_wcmd_cnt_1st : 4;
        unsigned int dfx_cs0_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs1_wcmd_cnt_1st : 4;
        unsigned int dfx_cs1_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs2_wcmd_cnt_1st : 4;
        unsigned int dfx_cs2_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs3_wcmd_cnt_1st : 4;
        unsigned int dfx_cs3_wcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs4_wcmd_cnt_1st : 4;
        unsigned int dfx_cs4_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs5_wcmd_cnt_1st : 4;
        unsigned int dfx_cs5_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs6_wcmd_cnt_1st : 4;
        unsigned int dfx_cs6_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs7_wcmd_cnt_1st : 4;
        unsigned int dfx_cs7_wcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs8_wcmd_cnt_1st : 4;
        unsigned int dfx_cs8_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs9_wcmd_cnt_1st : 4;
        unsigned int dfx_cs9_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs10_wcmd_cnt_1st : 4;
        unsigned int dfx_cs10_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs11_wcmd_cnt_1st : 4;
        unsigned int dfx_cs11_wcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs12_wcmd_cnt_1st : 4;
        unsigned int dfx_cs12_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs13_wcmd_cnt_1st : 4;
        unsigned int dfx_cs13_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs14_wcmd_cnt_1st : 4;
        unsigned int dfx_cs14_wcmd_cnt_2nd : 4;
        unsigned int dfx_cs15_wcmd_cnt_1st : 4;
        unsigned int dfx_cs15_wcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs0_rcmd_cnt_1st : 4;
        unsigned int dfx_cs0_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs1_rcmd_cnt_1st : 4;
        unsigned int dfx_cs1_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs2_rcmd_cnt_1st : 4;
        unsigned int dfx_cs2_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs3_rcmd_cnt_1st : 4;
        unsigned int dfx_cs3_rcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs4_rcmd_cnt_1st : 4;
        unsigned int dfx_cs4_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs5_rcmd_cnt_1st : 4;
        unsigned int dfx_cs5_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs6_rcmd_cnt_1st : 4;
        unsigned int dfx_cs6_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs7_rcmd_cnt_1st : 4;
        unsigned int dfx_cs7_rcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs8_rcmd_cnt_1st : 4;
        unsigned int dfx_cs8_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs9_rcmd_cnt_1st : 4;
        unsigned int dfx_cs9_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs10_rcmd_cnt_1st : 4;
        unsigned int dfx_cs10_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs11_rcmd_cnt_1st : 4;
        unsigned int dfx_cs11_rcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs12_rcmd_cnt_1st : 4;
        unsigned int dfx_cs12_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs13_rcmd_cnt_1st : 4;
        unsigned int dfx_cs13_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs14_rcmd_cnt_1st : 4;
        unsigned int dfx_cs14_rcmd_cnt_2nd : 4;
        unsigned int dfx_cs15_rcmd_cnt_1st : 4;
        unsigned int dfx_cs15_rcmd_cnt_2nd : 4;
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_START (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_END (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_START (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_END (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_START (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_END (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_START (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_END (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_START (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_END (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_START (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_END (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_START (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_END (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_START (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs0_idle : 1;
        unsigned int dfx_cs1_idle : 1;
        unsigned int dfx_cs2_idle : 1;
        unsigned int dfx_cs3_idle : 1;
        unsigned int dfx_cs4_idle : 1;
        unsigned int dfx_cs5_idle : 1;
        unsigned int dfx_cs6_idle : 1;
        unsigned int dfx_cs7_idle : 1;
        unsigned int dfx_cs8_idle : 1;
        unsigned int dfx_cs9_idle : 1;
        unsigned int dfx_cs10_idle : 1;
        unsigned int dfx_cs11_idle : 1;
        unsigned int dfx_cs12_idle : 1;
        unsigned int dfx_cs13_idle : 1;
        unsigned int dfx_cs14_idle : 1;
        unsigned int dfx_cs15_idle : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_MMBUF_SMC_CS_IDLE_UNION;
#endif
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_START (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_END (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_START (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_END (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_START (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_END (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_START (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_END (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_START (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_END (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_START (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_END (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_START (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_END (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_START (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_END (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_START (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_END (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_START (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_END (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_START (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_END (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_START (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_END (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_START (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_END (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_START (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_END (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_START (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_END (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_START (15)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs0_bfifo_cnt : 2;
        unsigned int dfx_cs1_bfifo_cnt : 2;
        unsigned int dfx_cs2_bfifo_cnt : 2;
        unsigned int dfx_cs3_bfifo_cnt : 2;
        unsigned int dfx_cs4_bfifo_cnt : 2;
        unsigned int dfx_cs5_bfifo_cnt : 2;
        unsigned int dfx_cs6_bfifo_cnt : 2;
        unsigned int dfx_cs7_bfifo_cnt : 2;
        unsigned int dfx_cs8_bfifo_cnt : 2;
        unsigned int dfx_cs9_bfifo_cnt : 2;
        unsigned int dfx_cs10_bfifo_cnt : 2;
        unsigned int dfx_cs11_bfifo_cnt : 2;
        unsigned int dfx_cs12_bfifo_cnt : 2;
        unsigned int dfx_cs13_bfifo_cnt : 2;
        unsigned int dfx_cs14_bfifo_cnt : 2;
        unsigned int dfx_cs15_bfifo_cnt : 2;
    } reg;
} SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_START (0)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_END (1)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_START (2)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_END (3)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_START (4)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_END (5)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_START (6)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_END (7)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_START (8)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_END (9)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_START (10)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_END (11)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_START (12)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_END (13)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_START (14)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_END (15)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_START (16)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_END (17)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_START (18)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_END (19)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_START (20)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_END (21)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_START (22)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_END (23)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_START (24)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_END (25)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_START (26)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_END (27)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_START (28)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_END (29)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_START (30)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dfx_cs0_rdfifo_cnt : 2;
        unsigned int dfx_cs1_rdfifo_cnt : 2;
        unsigned int dfx_cs2_rdfifo_cnt : 2;
        unsigned int dfx_cs3_rdfifo_cnt : 2;
        unsigned int dfx_cs4_rdfifo_cnt : 2;
        unsigned int dfx_cs5_rdfifo_cnt : 2;
        unsigned int dfx_cs6_rdfifo_cnt : 2;
        unsigned int dfx_cs7_rdfifo_cnt : 2;
        unsigned int dfx_cs8_rdfifo_cnt : 2;
        unsigned int dfx_cs9_rdfifo_cnt : 2;
        unsigned int dfx_cs10_rdfifo_cnt : 2;
        unsigned int dfx_cs11_rdfifo_cnt : 2;
        unsigned int dfx_cs12_rdfifo_cnt : 2;
        unsigned int dfx_cs13_rdfifo_cnt : 2;
        unsigned int dfx_cs14_rdfifo_cnt : 2;
        unsigned int dfx_cs15_rdfifo_cnt : 2;
    } reg;
} SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_START (0)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_END (1)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_START (2)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_END (3)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_START (4)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_END (5)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_START (6)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_END (7)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_START (8)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_END (9)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_START (10)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_END (11)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_START (12)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_END (13)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_START (14)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_END (15)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_START (16)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_END (17)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_START (18)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_END (19)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_START (20)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_END (21)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_START (22)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_END (23)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_START (24)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_END (25)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_START (26)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_END (27)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_START (28)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_END (29)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_START (30)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int st_int0_sram0 : 2;
        unsigned int st_int0_sram1 : 2;
        unsigned int st_int1_sram0 : 2;
        unsigned int st_int1_sram1 : 2;
        unsigned int st_int2_sram0 : 2;
        unsigned int st_int2_sram1 : 2;
        unsigned int st_int3_sram0 : 2;
        unsigned int st_int3_sram1 : 2;
        unsigned int st_int4_sram0 : 2;
        unsigned int st_int4_sram1 : 2;
        unsigned int st_int5_sram0 : 2;
        unsigned int st_int5_sram1 : 2;
        unsigned int st_int6_sram0 : 2;
        unsigned int st_int6_sram1 : 2;
        unsigned int st_int7_sram0 : 2;
        unsigned int st_int7_sram1 : 2;
    } reg;
} SOC_MMBUF_SP_SRAM_STATE0_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_START (0)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_END (1)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_START (2)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_END (3)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_START (4)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_END (5)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_START (6)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_END (7)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_START (8)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_END (9)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_START (10)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_END (11)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_START (12)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_END (13)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_START (14)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_END (15)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_START (16)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_END (17)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_START (18)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_END (19)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_START (20)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_END (21)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_START (22)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_END (23)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_START (24)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_END (25)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_START (26)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_END (27)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_START (28)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_END (29)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_START (30)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int st_int8_sram0 : 2;
        unsigned int st_int8_sram1 : 2;
        unsigned int st_int9_sram0 : 2;
        unsigned int st_int9_sram1 : 2;
        unsigned int st_int10_sram0 : 2;
        unsigned int st_int10_sram1 : 2;
        unsigned int st_int11_sram0 : 2;
        unsigned int st_int11_sram1 : 2;
        unsigned int st_int12_sram0 : 2;
        unsigned int st_int12_sram1 : 2;
        unsigned int st_int13_sram0 : 2;
        unsigned int st_int13_sram1 : 2;
        unsigned int st_int14_sram0 : 2;
        unsigned int st_int14_sram1 : 2;
        unsigned int st_int15_sram0 : 2;
        unsigned int st_int15_sram1 : 2;
    } reg;
} SOC_MMBUF_SP_SRAM_STATE1_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_START (0)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_END (1)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_START (2)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_END (3)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_START (4)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_END (5)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_START (6)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_END (7)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_START (8)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_END (9)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_START (10)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_END (11)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_START (12)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_END (13)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_START (14)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_END (15)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_START (16)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_END (17)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_START (18)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_END (19)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_START (20)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_END (21)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_START (22)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_END (23)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_START (24)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_END (25)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_START (26)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_END (27)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_START (28)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_END (29)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_START (30)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
