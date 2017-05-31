#ifndef __SOC_IOMCU_INTERFACE_H__
#define __SOC_IOMCU_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_IOMCU_CLK_SEL_ADDR(base) ((base) + (0x000))
#define SOC_IOMCU_CFG_DIV0_ADDR(base) ((base) + (0x004))
#define SOC_IOMCU_CFG_DIV1_ADDR(base) ((base) + (0x008))
#define SOC_IOMCU_RTC_CFG_ADDR(base) ((base) + (0x00C))
#define SOC_IOMCU_CLKEN0_ADDR(base) ((base) + (0x010))
#define SOC_IOMCU_CLKDIS0_ADDR(base) ((base) + (0x014))
#define SOC_IOMCU_CLKSTAT0_ADDR(base) ((base) + (0x018))
#define SOC_IOMCU_RSTEN0_ADDR(base) ((base) + (0x020))
#define SOC_IOMCU_RSTDIS0_ADDR(base) ((base) + (0x024))
#define SOC_IOMCU_RSTSTAT0_ADDR(base) ((base) + (0x028))
#define SOC_IOMCU_M7_CFG0_ADDR(base) ((base) + (0x030))
#define SOC_IOMCU_M7_CFG1_ADDR(base) ((base) + (0x034))
#define SOC_IOMCU_M7_STAT0_ADDR(base) ((base) + (0x038))
#define SOC_IOMCU_M7_STAT1_ADDR(base) ((base) + (0x03C))
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ADDR(base) ((base) + (0x040))
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_ADDR(base) ((base) + (0x044))
#define SOC_IOMCU_HACK_ACCESS_WINDOW_ADDR(base) ((base) + (0x048))
#define SOC_IOMCU_DLOCK_BYPASS_ADDR(base) ((base) + (0x04C))
#define SOC_IOMCU_MEM_CTRL_PGT_ADDR(base) ((base) + (0x050))
#define SOC_IOMCU_MEM_CTRL_ADDR(base) ((base) + (0x054))
#define SOC_IOMCU_SYS_STAT_ADDR(base) ((base) + (0x058))
#define SOC_IOMCU_SYS_CONFIG_ADDR(base) ((base) + (0x05C))
#define SOC_IOMCU_WAKEUP_EN_ADDR(base) ((base) + (0x060))
#define SOC_IOMCU_WAKEUP_CLR_ADDR(base) ((base) + (0x064))
#define SOC_IOMCU_WAKEUP_STAT_ADDR(base) ((base) + (0x068))
#define SOC_IOMCU_COMB_INT_RAW_ADDR(base) ((base) + (0x070))
#define SOC_IOMCU_COMB_INT_MSK_ADDR(base) ((base) + (0x074))
#define SOC_IOMCU_COMB_INT_STAT_ADDR(base) ((base) + (0x078))
#define SOC_IOMCU_BUS_AUTO_FREQ_ADDR(base) ((base) + (0x080))
#define SOC_IOMCU_MISC_CTRL_ADDR(base) ((base) + (0x084))
#define SOC_IOMCU_NOC_CTRL_ADDR(base) ((base) + (0x088))
#define SOC_IOMCU_M7_CFG2_ADDR(base) ((base) + (0x08C))
#define SOC_IOMCU_CLKEN1_ADDR(base) ((base) + (0x090))
#define SOC_IOMCU_CLKDIS1_ADDR(base) ((base) + (0x094))
#define SOC_IOMCU_CLKSTAT1_ADDR(base) ((base) + (0x098))
#define SOC_IOMCU_SEC_TZPC_ADDR(base) ((base) + (0x0100))
#define SOC_IOMCU_SEC_RES_ADDR(base) ((base) + (0x104))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_mcu_sel : 2;
        unsigned int clk_mcu_sel_stat : 2;
        unsigned int clk_mmbuf_sel : 2;
        unsigned int clk_mmbuf_sel_stat : 2;
        unsigned int clk_nocbus_sel : 2;
        unsigned int clk_nocbus_sel_stat : 2;
        unsigned int clk_peri0_sel : 2;
        unsigned int clk_peri1_sel : 2;
        unsigned int clk_peri2_sel : 2;
        unsigned int clk_peri3_sel : 2;
        unsigned int clk_peri0_sel_stat : 2;
        unsigned int clk_peri1_sel_stat : 2;
        unsigned int clk_peri2_sel_stat : 2;
        unsigned int clk_peri3_sel_stat : 2;
        unsigned int clk_pll_stable : 1;
        unsigned int clk_fll_stable : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_IOMCU_CLK_SEL_UNION;
#endif
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_START (0)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_END (1)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_START (2)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_END (3)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_START (4)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_END (5)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_START (6)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_END (7)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_START (8)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_END (9)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_START (10)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_END (11)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_START (12)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_END (13)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_START (14)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_END (15)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_START (16)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_END (17)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_START (18)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_END (19)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_START (20)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_END (21)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_START (22)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_END (23)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_START (24)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_END (25)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_START (26)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_END (27)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_START (28)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_END (28)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_START (29)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_mcu0_div : 2;
        unsigned int iomcu_apb_l_div_pre : 2;
        unsigned int iomcu_apb_l_div : 2;
        unsigned int reserved_0 : 1;
        unsigned int iomcu_apb_l_div_en : 1;
        unsigned int iomcu_apb_h_div : 2;
        unsigned int iomcu_mcu1_div : 2;
        unsigned int iomcu_peri0_div : 2;
        unsigned int reserved_1 : 1;
        unsigned int iomcu_peri_ahb_div_en : 1;
        unsigned int iomcu_peri1_div : 2;
        unsigned int iomcu_peri2_div : 2;
        unsigned int iomcu_peri3_div : 2;
        unsigned int reserved_2 : 1;
        unsigned int iomcu_peri_div_en : 1;
        unsigned int iomcu_div : 6;
        unsigned int reserved_3 : 1;
        unsigned int iomcu_div_en : 1;
    } reg;
} SOC_IOMCU_CFG_DIV0_UNION;
#endif
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_START (0)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_END (1)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_START (2)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_END (3)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_START (4)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_END (5)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_START (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_END (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_START (8)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_END (9)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_START (10)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_END (11)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_START (12)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_END (13)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_START (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_END (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_START (16)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_END (17)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_START (18)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_END (19)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_START (20)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_END (21)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_START (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_END (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_START (24)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_END (29)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_START (31)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_mcu0_div_nopending : 2;
        unsigned int iomcu_mcu1_div_nopending : 2;
        unsigned int reserved_0 : 3;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 7;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 7;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 7;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_IOMCU_CFG_DIV1_UNION;
#endif
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_START (0)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_END (1)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_START (2)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rtc_clk_sel : 1;
        unsigned int rtc_crc_clken : 1;
        unsigned int reserved_0 : 2;
        unsigned int rtc_div_quotient : 11;
        unsigned int reserved_1 : 1;
        unsigned int rtc_div_remainder : 10;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_IOMCU_RTC_CFG_UNION;
#endif
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_START (0)
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_END (0)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_START (1)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_END (1)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_START (4)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_END (14)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_START (16)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clken0_0dmac : 1;
        unsigned int iomcu_clken0_lwdt : 1;
        unsigned int iomcu_clken0_2timer : 1;
        unsigned int iomcu_clken0_3i2c0 : 1;
        unsigned int iomcu_clken0_4i2c1 : 1;
        unsigned int iomcu_clken0_5i2c2 : 1;
        unsigned int iomcu_clken0_6gpio0 : 1;
        unsigned int iomcu_clken0_7gpio1 : 1;
        unsigned int iomcu_clken0_8gpio2 : 1;
        unsigned int iomcu_clken0_9gpio3 : 1;
        unsigned int iomcu_clken0_10spi0 : 1;
        unsigned int iomcu_clken0_11uart3 : 1;
        unsigned int iomcu_clken0_12uart7 : 1;
        unsigned int iomcu_clken0_13blpwm : 1;
        unsigned int iomcu_clken0_14fclk_mcu : 1;
        unsigned int iomcu_clken0_15clk_mcu : 1;
        unsigned int iomcu_clken0_16clk_etm : 1;
        unsigned int iomcu_clken0_17aclk_mcu : 1;
        unsigned int iomcu_clken0_18hclk_mcu : 1;
        unsigned int iomcu_clken0_19clk_fll : 1;
        unsigned int iomcu_clken0_20clk_ppll0 : 1;
        unsigned int iomcu_clken0_21clk_dapb : 1;
        unsigned int iomcu_clken0_22clk_atb : 1;
        unsigned int iomcu_clken0_23pclk_rtc : 1;
        unsigned int iomcu_clken0_24clk_ctm : 1;
        unsigned int iomcu_clken0_25clk_tcxo_in : 1;
        unsigned int iomcu_clken0_26tcm : 1;
        unsigned int iomcu_clken0_27i2c6 : 1;
        unsigned int iomcu_clken0_28mmbuf : 1;
        unsigned int iomcu_clken0_29ao_bus : 1;
        unsigned int iomcu_clken0_30spi2 : 1;
        unsigned int iomcu_clken0_31uart8 : 1;
    } reg;
} SOC_IOMCU_CLKEN0_UNION;
#endif
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_START (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_END (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_START (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_END (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_START (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_END (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_START (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_END (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_START (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_END (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_START (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_END (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_START (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_END (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_START (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_END (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_START (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_END (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_START (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_END (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_START (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_END (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_START (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_END (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_START (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_END (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_START (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_END (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_START (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_END (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_START (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_END (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_START (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_END (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_START (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_END (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_START (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_END (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_START (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_END (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_START (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_END (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_START (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_END (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_START (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_END (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_START (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_END (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_START (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_END (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_START (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_END (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_START (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_END (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_START (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_END (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_START (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_END (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_START (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_END (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_START (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_END (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_START (31)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clkdis0_0dmac : 1;
        unsigned int iomcu_clkdis0_lwdt : 1;
        unsigned int iomcu_clkdis0_2timer : 1;
        unsigned int iomcu_clkdis0_3i2c0 : 1;
        unsigned int iomcu_clkdis0_4i2c1 : 1;
        unsigned int iomcu_clkdis0_5i2c2 : 1;
        unsigned int iomcu_clkdis0_6gpio0 : 1;
        unsigned int iomcu_clkdis0_7gpio1 : 1;
        unsigned int iomcu_clkdis0_8gpio2 : 1;
        unsigned int iomcu_clkdis0_9gpio3 : 1;
        unsigned int iomcu_clkdis0_10spi0 : 1;
        unsigned int iomcu_clkdis0_11uart3 : 1;
        unsigned int iomcu_clkdis0_12uart7 : 1;
        unsigned int iomcu_clkdis0_13blpwm : 1;
        unsigned int iomcu_clkdis0_14fclk_mcu : 1;
        unsigned int iomcu_clkdis0_15clk_mcu : 1;
        unsigned int iomcu_clkdis0_16clk_etm : 1;
        unsigned int iomcu_clkdis0_17aclk_mcu : 1;
        unsigned int iomcu_clkdis0_18hclk_mcu : 1;
        unsigned int iomcu_clkdis0_19clk_fll : 1;
        unsigned int iomcu_clkdis0_20clk_ppll0 : 1;
        unsigned int iomcu_clkdis0_21clk_dapb : 1;
        unsigned int iomcu_clkdis0_22clk_atb : 1;
        unsigned int iomcu_clkdis0_23pclk_rtc : 1;
        unsigned int iomcu_clkdis0_24clk_ctm : 1;
        unsigned int iomcu_clkdis0_25clk_tcxo_in : 1;
        unsigned int iomcu_clkdis0_26tcm : 1;
        unsigned int iomcu_clkdis0_27i2c6 : 1;
        unsigned int iomcu_clkdis0_28mmbuf : 1;
        unsigned int iomcu_clkdis0_29ao_bus : 1;
        unsigned int iomcu_clkdis0_30spi2 : 1;
        unsigned int iomcu_clkdis0_31uart8 : 1;
    } reg;
} SOC_IOMCU_CLKDIS0_UNION;
#endif
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_START (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_END (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_START (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_END (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_START (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_END (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_START (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_END (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_START (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_END (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_START (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_END (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_START (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_END (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_START (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_END (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_START (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_END (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_START (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_END (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_START (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_END (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_START (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_END (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_START (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_END (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_START (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_END (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_START (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_END (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_START (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_END (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_START (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_END (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_START (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_END (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_START (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_END (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_START (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_END (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_START (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_END (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_START (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_END (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_START (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_END (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_START (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_END (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_START (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_END (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_START (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_END (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_START (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_END (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_START (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_END (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_START (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_END (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_START (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_END (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_START (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_END (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_START (31)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clkstat0_0dmac : 1;
        unsigned int iomcu_clkstat0_lwdt : 1;
        unsigned int iomcu_clkstat0_2timer : 1;
        unsigned int iomcu_clkstat0_3i2c0 : 1;
        unsigned int iomcu_clkstat0_4i2c1 : 1;
        unsigned int iomcu_clkstat0_5i2c2 : 1;
        unsigned int iomcu_clkstat0_6gpio0 : 1;
        unsigned int iomcu_clkstat0_7gpio1 : 1;
        unsigned int iomcu_clkstat0_8gpio2 : 1;
        unsigned int iomcu_clkstat0_9gpio3 : 1;
        unsigned int iomcu_clkstat0_10spi0 : 1;
        unsigned int iomcu_clkstat0_11uart3 : 1;
        unsigned int iomcu_clkstat0_12uart7 : 1;
        unsigned int iomcu_clkstat0_13blpwm : 1;
        unsigned int iomcu_clkstat0_14fclk_mcu : 1;
        unsigned int iomcu_clkstat0_15clk_mcu : 1;
        unsigned int iomcu_clkstat0_16clk_etm : 1;
        unsigned int iomcu_clkstat0_17aclk_mcu : 1;
        unsigned int iomcu_clkstat0_18hclk_mcu : 1;
        unsigned int iomcu_clkstat0_19clk_fll : 1;
        unsigned int iomcu_clkstat0_20clk_ppll0 : 1;
        unsigned int iomcu_clkstat0_21clk_dapb : 1;
        unsigned int iomcu_clkstat0_22clk_atb : 1;
        unsigned int iomcu_clkstat0_23pclk_rtc : 1;
        unsigned int iomcu_clkstat0_24clk_ctm : 1;
        unsigned int iomcu_clkstat0_25clk_tcxo_in : 1;
        unsigned int iomcu_clkstat0_26tcm : 1;
        unsigned int iomcu_clkstat0_27i2c6 : 1;
        unsigned int iomcu_clkstat0_28mmbuf : 1;
        unsigned int iomcu_clkstat0_29ao_bus : 1;
        unsigned int iomcu_clkstat0_30spi2 : 1;
        unsigned int iomcu_clkstat0_31uart8 : 1;
    } reg;
} SOC_IOMCU_CLKSTAT0_UNION;
#endif
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_START (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_END (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_START (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_END (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_START (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_END (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_START (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_END (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_START (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_END (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_START (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_END (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_START (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_END (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_START (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_END (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_START (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_END (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_START (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_END (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_START (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_END (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_START (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_END (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_START (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_END (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_START (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_END (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_START (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_END (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_START (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_END (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_START (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_END (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_START (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_END (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_START (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_END (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_START (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_END (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_START (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_END (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_START (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_END (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_START (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_END (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_START (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_END (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_START (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_END (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_START (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_END (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_START (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_END (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_START (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_END (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_START (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_END (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_START (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_END (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_START (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_END (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_START (31)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_rsten0_0dma : 1;
        unsigned int iomcu_rsten0_1wdt : 1;
        unsigned int iomcu_rsten0_2timer : 1;
        unsigned int iomcu_rsten0_3i2c0 : 1;
        unsigned int iomcu_rsten0_4i2c1 : 1;
        unsigned int iomcu_rsten0_5i2c2 : 1;
        unsigned int iomcu_rsten0_6gpio0 : 1;
        unsigned int iomcu_rsten0_7gpio1 : 1;
        unsigned int iomcu_rsten0_8gpio2 : 1;
        unsigned int iomcu_rsten0_9gpio3 : 1;
        unsigned int iomcu_rsten0_10spi0 : 1;
        unsigned int iomcu_rsten0_11uart3 : 1;
        unsigned int iomcu_rsten0_12uart7 : 1;
        unsigned int iomcu_rsten0_13blpwm : 1;
        unsigned int iomcu_rsten0_14mcu_sys : 1;
        unsigned int iomcu_rsten0_15mcu_etm : 1;
        unsigned int iomcu_rsten0_16reserved : 1;
        unsigned int iomcu_rsten0_17reserved : 1;
        unsigned int iomcu_rsten0_18tcm : 1;
        unsigned int iomcu_rsten0_19reserved : 1;
        unsigned int iomcu_rsten0_20reserved : 1;
        unsigned int iomcu_rsten0_21dapb : 1;
        unsigned int iomcu_rsten0_22atb : 1;
        unsigned int iomcu_rsten0_23rtc : 1;
        unsigned int iomcu_rsten0_24ctm : 1;
        unsigned int iomcu_rsten0_25reserved : 1;
        unsigned int iomcu_rsten0_26reserved : 1;
        unsigned int iomcu_rsten0_27i2c6 : 1;
        unsigned int iomcu_rsten0_28reserved : 1;
        unsigned int iomcu_rsten0_29reserved : 1;
        unsigned int iomcu_rsten0_30spi2 : 1;
        unsigned int iomcu_rsten0_31uart8 : 1;
    } reg;
} SOC_IOMCU_RSTEN0_UNION;
#endif
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_START (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_END (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_START (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_END (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_START (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_END (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_START (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_END (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_START (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_END (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_START (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_END (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_START (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_END (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_START (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_END (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_START (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_END (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_START (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_END (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_START (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_END (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_START (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_END (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_START (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_END (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_START (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_END (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_START (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_END (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_START (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_END (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_START (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_END (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_START (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_END (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_START (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_END (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_START (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_END (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_START (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_END (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_START (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_END (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_START (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_END (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_START (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_END (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_START (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_END (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_START (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_END (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_START (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_END (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_START (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_END (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_START (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_END (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_START (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_END (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_START (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_END (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_START (31)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_rstdis0_0dma : 1;
        unsigned int iomcu_rstdis0_1wdt : 1;
        unsigned int iomcu_rstdis0_2timer : 1;
        unsigned int iomcu_rstdis0_3i2c0 : 1;
        unsigned int iomcu_rstdis0_4i2c1 : 1;
        unsigned int iomcu_rstdis0_5i2c2 : 1;
        unsigned int iomcu_rstdis0_6gpio0 : 1;
        unsigned int iomcu_rstdis0_7gpio1 : 1;
        unsigned int iomcu_rstdis0_8gpio2 : 1;
        unsigned int iomcu_rstdis0_9gpio3 : 1;
        unsigned int iomcu_rstdis0_10spi0 : 1;
        unsigned int iomcu_rstdis0_11uart3 : 1;
        unsigned int iomcu_rstdis0_12uart7 : 1;
        unsigned int iomcu_rstdis0_13blpwm : 1;
        unsigned int iomcu_rstdis0_14mcu_sys : 1;
        unsigned int iomcu_rstdis0_15mcu_etm : 1;
        unsigned int iomcu_rstdis0_16reserved : 1;
        unsigned int iomcu_rstdis0_17reserved : 1;
        unsigned int iomcu_rstdis0_18tcm : 1;
        unsigned int iomcu_rstdis0_19reserved : 1;
        unsigned int iomcu_rstdis0_20reserved : 1;
        unsigned int iomcu_rstdis0_21dapb : 1;
        unsigned int iomcu_rstdis0_22atb : 1;
        unsigned int iomcu_rstdis0_23rtc : 1;
        unsigned int iomcu_rstdis0_24ctm : 1;
        unsigned int iomcu_rstdis0_25reserved : 1;
        unsigned int iomcu_rstdis0_26reserved : 1;
        unsigned int iomcu_rstdis0_27i2c6 : 1;
        unsigned int iomcu_rstdis0_28reserved : 1;
        unsigned int iomcu_rstdis0_29reserved : 1;
        unsigned int iomcu_rstdis0_30spi2 : 1;
        unsigned int iomcu_rstdis0_31uart8 : 1;
    } reg;
} SOC_IOMCU_RSTDIS0_UNION;
#endif
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_START (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_END (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_START (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_END (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_START (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_END (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_START (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_END (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_START (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_END (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_START (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_END (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_START (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_END (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_START (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_END (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_START (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_END (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_START (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_END (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_START (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_END (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_START (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_END (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_START (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_END (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_START (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_END (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_START (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_END (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_START (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_END (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_START (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_END (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_START (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_END (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_START (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_END (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_START (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_END (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_START (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_END (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_START (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_END (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_START (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_END (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_START (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_END (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_START (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_END (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_START (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_END (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_START (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_END (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_START (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_END (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_START (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_END (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_START (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_END (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_START (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_END (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_START (31)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_rststats0_0dma : 1;
        unsigned int iomcu_rststats0_1wdt : 1;
        unsigned int iomcu_rststats0_2timer : 1;
        unsigned int iomcu_rststats0_3i2c0 : 1;
        unsigned int iomcu_rststats0_4i2c1 : 1;
        unsigned int iomcu_rststats0_5i2c2 : 1;
        unsigned int iomcu_rststats0_6gpio0 : 1;
        unsigned int iomcu_rststats0_7gpio1 : 1;
        unsigned int iomcu_rststats0_8gpio2 : 1;
        unsigned int iomcu_rststats0_9gpio3 : 1;
        unsigned int iomcu_rststats0_10spi0 : 1;
        unsigned int iomcu_rststats0_11uart3 : 1;
        unsigned int iomcu_rststats0_12uart7 : 1;
        unsigned int iomcu_rststats0_13blpwm : 1;
        unsigned int iomcu_rststats0_14mcu_sys : 1;
        unsigned int iomcu_rststats0_15mcu_etm : 1;
        unsigned int iomcu_rststats0_16reserved : 1;
        unsigned int iomcu_rststats0_17reserved : 1;
        unsigned int iomcu_rststats0_18tcm : 1;
        unsigned int iomcu_rststats0_19reserved : 1;
        unsigned int iomcu_rststats0_20reserved : 1;
        unsigned int iomcu_rststats0_21dapb : 1;
        unsigned int iomcu_rststats0_22atb : 1;
        unsigned int iomcu_rststats0_23rtc : 1;
        unsigned int iomcu_rststats0_24ctm : 1;
        unsigned int iomcu_rststats0_25reserved : 1;
        unsigned int iomcu_rststats0_26reserved : 1;
        unsigned int iomcu_rststats0_27i2c6 : 1;
        unsigned int iomcu_rststats0_28reserved : 1;
        unsigned int iomcu_rststats0_29reserved : 1;
        unsigned int iomcu_rststats0_30spi2 : 1;
        unsigned int iomcu_rststat0_31uart8 : 1;
    } reg;
} SOC_IOMCU_RSTSTAT0_UNION;
#endif
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_START (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_END (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_START (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_END (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_START (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_END (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_START (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_END (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_START (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_END (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_START (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_END (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_START (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_END (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_START (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_END (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_START (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_END (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_START (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_END (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_START (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_END (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_START (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_END (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_START (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_END (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_START (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_END (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_START (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_END (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_START (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_END (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_START (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_END (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_START (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_END (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_START (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_END (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_START (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_END (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_START (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_END (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_START (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_END (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_START (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_END (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_START (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_END (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_START (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_END (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_START (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_END (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_START (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_END (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_START (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_END (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_START (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_END (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_START (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_END (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_START (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_END (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_START (31)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_wait : 1;
        unsigned int hclken_sleeping_bypass : 1;
        unsigned int reserved_0 : 1;
        unsigned int cpu_iadbgprot : 1;
        unsigned int cpu_initvtor : 25;
        unsigned int ahbs_ready_error_clr : 1;
        unsigned int cfg_bigend : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_IOMCU_M7_CFG0_UNION;
#endif
#define SOC_IOMCU_M7_CFG0_cpu_wait_START (0)
#define SOC_IOMCU_M7_CFG0_cpu_wait_END (0)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_START (1)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_END (1)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_START (3)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_END (3)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_START (4)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_END (28)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_START (29)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_END (29)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_START (30)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfgstcalib_cycclecnt : 24;
        unsigned int cfgstcalib_precision : 1;
        unsigned int cfgstcalib_ticken : 1;
        unsigned int halt_bypass : 1;
        unsigned int hack_remap_bypass : 1;
        unsigned int mmbuf_remap_bypass : 1;
        unsigned int aclken_sleeping_bypass : 1;
        unsigned int deepsleeping_bypass : 1;
        unsigned int clken_sleeping_bypass : 1;
    } reg;
} SOC_IOMCU_M7_CFG1_UNION;
#endif
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_START (0)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_END (23)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_START (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_END (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_START (25)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_END (25)
#define SOC_IOMCU_M7_CFG1_halt_bypass_START (26)
#define SOC_IOMCU_M7_CFG1_halt_bypass_END (26)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_START (27)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_END (27)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_START (28)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_END (28)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_START (29)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_END (29)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_START (30)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_END (30)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_START (31)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m7_iaddr_stat : 29;
        unsigned int ahbs_ready_error_stat : 1;
        unsigned int cpu_halt_stat : 1;
        unsigned int cpu_lockup : 1;
    } reg;
} SOC_IOMCU_M7_STAT0_UNION;
#endif
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_START (0)
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_END (28)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_START (29)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_END (29)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_START (30)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_END (30)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_START (31)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m7_sleeping_stat : 1;
        unsigned int m7_deepsleeping_stat : 1;
        unsigned int m7_ahbs_ready_stat : 1;
        unsigned int m7_axi_bypass : 1;
        unsigned int m7_ahb_bypass : 1;
        unsigned int m7_dma_bypass : 1;
        unsigned int m7_sc_stat : 9;
        unsigned int m7_etmpwrupreq : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_IOMCU_M7_STAT1_UNION;
#endif
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_START (0)
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_END (0)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_START (1)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_END (1)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_START (2)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_END (2)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_START (3)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_END (3)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_START (4)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_END (4)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_START (5)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_END (5)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_START (6)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_END (14)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_START (15)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr_access_window : 32;
    } reg;
} SOC_IOMCU_DDR_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_START (0)
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmbuf_access_window : 32;
    } reg;
} SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_START (0)
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hack_access_window : 32;
    } reg;
} SOC_IOMCU_HACK_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_START (0)
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass_for_watchdog : 1;
        unsigned int bypass_for_timer : 1;
        unsigned int bypass_for_spi : 1;
        unsigned int bypass_for_gpio0 : 1;
        unsigned int bypass_for_gpio1 : 1;
        unsigned int bypass_for_gpio2 : 1;
        unsigned int bypass_for_gpio3 : 1;
        unsigned int bypass_for_i2c0 : 1;
        unsigned int bypass_for_i2c1 : 1;
        unsigned int bypass_for_i2c2 : 1;
        unsigned int bypass_for_uart3 : 1;
        unsigned int bypass_for_blpwm : 1;
        unsigned int bypass_for_uart7 : 1;
        unsigned int bypass_for_dma : 1;
        unsigned int bypass_for_rtc : 1;
        unsigned int bypass_for_i2c6 : 1;
        unsigned int bypass_for_uart8 : 1;
        unsigned int bypass_for_spi2 : 1;
        unsigned int bypass_for_tcm : 1;
        unsigned int reserved : 13;
    } reg;
} SOC_IOMCU_DLOCK_BYPASS_UNION;
#endif
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_START (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_END (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_START (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_END (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_START (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_END (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_START (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_END (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_START (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_END (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_START (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_END (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_START (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_END (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_START (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_END (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_START (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_END (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_START (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_END (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_START (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_END (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_START (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_END (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_START (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_END (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_START (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_END (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_START (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_END (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_START (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_END (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_START (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_END (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_START (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_END (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_START (18)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_ctrl_bank0 : 3;
        unsigned int reserved_0 : 1;
        unsigned int mem_ctrl_bank1 : 3;
        unsigned int reserved_1 : 1;
        unsigned int mem_ctrl_bank2 : 3;
        unsigned int reserved_2 : 1;
        unsigned int mem_ctrl_bank3 : 3;
        unsigned int reserved_3 : 1;
        unsigned int mem_ctrl_bank4 : 3;
        unsigned int reserved_4 : 1;
        unsigned int mem_ctrl_icache : 3;
        unsigned int reserved_5 : 1;
        unsigned int mem_ctrl_dcache : 3;
        unsigned int reserved_6 : 1;
        unsigned int mem_ctrl_map_table : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_IOMCU_MEM_CTRL_PGT_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_START (0)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_END (2)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_START (4)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_END (6)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_START (8)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_END (10)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_START (12)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_END (14)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_START (16)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_END (18)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_START (20)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_END (22)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_START (24)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_END (26)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_START (28)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcm_wtsel : 2;
        unsigned int tcm_rtsel : 2;
        unsigned int cache_wtsel : 2;
        unsigned int cache_rtsel : 2;
        unsigned int tp_rct : 2;
        unsigned int tp_wct : 2;
        unsigned int tp_kp : 3;
        unsigned int reserved : 17;
    } reg;
} SOC_IOMCU_MEM_CTRL_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_START (0)
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_END (1)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_START (2)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_END (3)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_START (4)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_END (5)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_START (6)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_END (7)
#define SOC_IOMCU_MEM_CTRL_tp_rct_START (8)
#define SOC_IOMCU_MEM_CTRL_tp_rct_END (9)
#define SOC_IOMCU_MEM_CTRL_tp_wct_START (10)
#define SOC_IOMCU_MEM_CTRL_tp_wct_END (11)
#define SOC_IOMCU_MEM_CTRL_tp_kp_START (12)
#define SOC_IOMCU_MEM_CTRL_tp_kp_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sys_stat : 4;
        unsigned int xtal_ready : 2;
        unsigned int reserved : 26;
    } reg;
} SOC_IOMCU_SYS_STAT_UNION;
#endif
#define SOC_IOMCU_SYS_STAT_sys_stat_START (0)
#define SOC_IOMCU_SYS_STAT_sys_stat_END (3)
#define SOC_IOMCU_SYS_STAT_xtal_ready_START (4)
#define SOC_IOMCU_SYS_STAT_xtal_ready_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sleep_mode : 1;
        unsigned int ppll0_en : 1;
        unsigned int fll_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_IOMCU_SYS_CONFIG_UNION;
#endif
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_START (0)
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_END (0)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_START (1)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_END (1)
#define SOC_IOMCU_SYS_CONFIG_fll_en_START (2)
#define SOC_IOMCU_SYS_CONFIG_fll_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wakeup_en : 1;
        unsigned int soft_int_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_IOMCU_WAKEUP_EN_UNION;
#endif
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_START (0)
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_END (0)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_START (1)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wakeup_clr : 1;
        unsigned int soft_int_clr : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_IOMCU_WAKEUP_CLR_UNION;
#endif
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_START (0)
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_END (0)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_START (1)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wakeup_stat : 1;
        unsigned int soft_int_stat : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_IOMCU_WAKEUP_STAT_UNION;
#endif
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_START (0)
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_END (0)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_START (1)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio0_int_raw : 1;
        unsigned int gpio1_int_raw : 1;
        unsigned int gpio2_int_raw : 1;
        unsigned int gpio3_int_raw : 1;
        unsigned int timer1_int_raw : 1;
        unsigned int timer2_int_raw : 1;
        unsigned int soft_int_raw : 1;
        unsigned int dss_rise_int_raw : 1;
        unsigned int dss_down_int_raw : 1;
        unsigned int sys_wakeup_int_raw : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_IOMCU_COMB_INT_RAW_UNION;
#endif
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_START (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_END (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_START (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_END (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_START (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_END (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_START (3)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_END (3)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_START (4)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_END (4)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_START (5)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_END (5)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_START (6)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_END (6)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_START (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_END (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_START (8)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_END (8)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_START (9)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio0_int_msk : 1;
        unsigned int gpio1_int_msk : 1;
        unsigned int gpio2_int_msk : 1;
        unsigned int gpio3_int_msk : 1;
        unsigned int timer1_int_msk : 1;
        unsigned int timer2_int_msk : 1;
        unsigned int soft_int_msk : 1;
        unsigned int dss_rise_int_msk : 1;
        unsigned int dss_down_int_msk : 1;
        unsigned int dss_rise_int_clr : 1;
        unsigned int dss_down_int_clr : 1;
        unsigned int sys_wakeup_int_msk : 1;
        unsigned int sys_wakeup_int_clr : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_IOMCU_COMB_INT_MSK_UNION;
#endif
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_START (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_END (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_START (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_END (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_START (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_END (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_START (3)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_END (3)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_START (4)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_END (4)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_START (5)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_END (5)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_START (6)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_END (6)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_START (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_END (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_START (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_END (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_START (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_END (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_START (10)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_END (10)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_START (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_END (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_START (12)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio0_int_mskd : 1;
        unsigned int gpio1_int_mskd : 1;
        unsigned int gpio2_int_mskd : 1;
        unsigned int gpio3_int_mskd : 1;
        unsigned int timer1_int_mskd : 1;
        unsigned int timer2_int_mskd : 1;
        unsigned int soft_int_mskd : 1;
        unsigned int dss_rise_int_mskd : 1;
        unsigned int dss_down_int_mskd : 1;
        unsigned int sys_wakeup_int_mskd : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_IOMCU_COMB_INT_STAT_UNION;
#endif
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_START (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_END (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_START (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_END (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_START (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_END (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_START (3)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_END (3)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_START (4)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_END (4)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_START (5)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_END (5)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_START (6)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_END (6)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_START (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_END (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_START (8)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_END (8)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_START (9)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_m7_freq_bypass : 1;
        unsigned int auto_cpu_freq_bypass : 1;
        unsigned int reserved_0 : 2;
        unsigned int auto_num_in : 10;
        unsigned int reserved_1 : 2;
        unsigned int auto_num_out : 10;
        unsigned int reserved_2 : 1;
        unsigned int noc_clkgate_bypass : 1;
        unsigned int reserved_3 : 4;
    } reg;
} SOC_IOMCU_BUS_AUTO_FREQ_UNION;
#endif
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_START (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_END (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_START (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_END (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_START (4)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_END (13)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_START (16)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_END (25)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_START (27)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spi_cs : 4;
        unsigned int clk_tp_ctrl : 1;
        unsigned int dmac_ckgt_dis : 1;
        unsigned int cfg_itcm_size : 4;
        unsigned int cfg_dtcm_size : 4;
        unsigned int reserved : 18;
    } reg;
} SOC_IOMCU_MISC_CTRL_UNION;
#endif
#define SOC_IOMCU_MISC_CTRL_spi_cs_START (0)
#define SOC_IOMCU_MISC_CTRL_spi_cs_END (3)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_START (4)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_END (4)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_START (5)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_END (5)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_START (6)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_END (9)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_START (10)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int noc_iomcu_dma_mst_awqos : 2;
        unsigned int noc_iomcu_dma_mst_arqos : 2;
        unsigned int noc_iomcu_axi_mst_awqos : 2;
        unsigned int noc_iomcu_axi_mst_arqos : 2;
        unsigned int noc_iomcu_ahb_mst_requser : 2;
        unsigned int noc_ahb_mst_mid : 5;
        unsigned int reserved : 17;
    } reg;
} SOC_IOMCU_NOC_CTRL_UNION;
#endif
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_START (0)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_END (1)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_START (2)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_END (3)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_START (4)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_END (5)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_START (6)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_END (7)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_START (8)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_END (9)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_START (10)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_reserved : 32;
    } reg;
} SOC_IOMCU_M7_CFG2_UNION;
#endif
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_START (0)
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clken1_0peri0 : 1;
        unsigned int iomcu_clken1_1peri1 : 1;
        unsigned int iomcu_clken1_2peri2 : 1;
        unsigned int iomcu_clken1_3peri3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_IOMCU_CLKEN1_UNION;
#endif
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_START (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_END (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_START (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_END (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_START (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_END (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_START (3)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clkdis1_0peri0 : 1;
        unsigned int iomcu_clkdis1_1peri1 : 1;
        unsigned int iomcu_clkdis1_2peri2 : 1;
        unsigned int iomcu_clkdis1_3peri3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_IOMCU_CLKDIS1_UNION;
#endif
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_START (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_END (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_START (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_END (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_START (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_END (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_START (3)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_clkstat1_0peri0 : 1;
        unsigned int iomcu_clkstat1_1peri1 : 1;
        unsigned int iomcu_clkstat1_2peri2 : 1;
        unsigned int iomcu_clkstat1_3peri3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_IOMCU_CLKSTAT1_UNION;
#endif
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_START (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_END (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_START (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_END (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_START (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_END (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_START (3)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_AHB_tzpc : 1;
        unsigned int iomcu_AXI_tzpc : 1;
        unsigned int reserved_0 : 1;
        unsigned int iomcu_i2c2_tzpc : 1;
        unsigned int iomcu_i2c1_tzpc : 1;
        unsigned int iomcu_spi2_tzpc : 1;
        unsigned int iomcu_uart8_tzpc : 1;
        unsigned int iomcu_i2c6_tzpc : 1;
        unsigned int iomcu_tcm_tzpc : 1;
        unsigned int iomcu_spi_tzpc : 1;
        unsigned int iomcu_i2c0_tzpc : 1;
        unsigned int iomcu_uart3_tzpc : 1;
        unsigned int iomcu_blpwm_tzpc : 1;
        unsigned int iomcu_uart7_tzpc : 1;
        unsigned int reserved_1 : 1;
        unsigned int iomcu_gpio0_tzpc : 1;
        unsigned int iomcu_gpio1_tzpc : 1;
        unsigned int iomcu_gpio2_tzpc : 1;
        unsigned int iomcu_gpio3_tzpc : 1;
        unsigned int iomcu_wdg_tzpc : 1;
        unsigned int iomcu_timer_tzpc : 1;
        unsigned int iomcu_sctrl_tzpc : 1;
        unsigned int iomcu_rtc_tzpc : 1;
        unsigned int iomcu_m7_tzpc : 1;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_IOMCU_SEC_TZPC_UNION;
#endif
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_START (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_END (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_START (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_END (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_START (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_END (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_START (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_END (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_START (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_END (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_START (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_END (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_START (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_END (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_START (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_END (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_START (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_END (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_START (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_END (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_START (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_END (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_START (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_END (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_START (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_END (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_START (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_END (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_START (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_END (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_START (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_END (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_START (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_END (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_START (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_END (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_START (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_END (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_START (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_END (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_START (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_END (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_START (23)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iomcu_se_reserved : 32;
    } reg;
} SOC_IOMCU_SEC_RES_UNION;
#endif
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_START (0)
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
