#ifndef __SOC_ASP_SLIMBUS_INTERFACE_H__
#define __SOC_ASP_SLIMBUS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ADDR(base) ((base) + (0x000))
#define SOC_ASP_SLIMBUS_CONFIG_EA_ADDR(base) ((base) + (0x004))
#define SOC_ASP_SLIMBUS_CONFIG_PR_ADDR(base) ((base) + (0x008))
#define SOC_ASP_SLIMBUS_CONFIG_FR_ADDR(base) ((base) + (0x00C))
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_ADDR(base) ((base) + (0x010))
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_ADDR(base) ((base) + (0x014))
#define SOC_ASP_SLIMBUS_CONFIG_EA2_ADDR(base) ((base) + (0x018))
#define SOC_ASP_SLIMBUS_CONFIG_THR_ADDR(base) ((base) + (0x01C))
#define SOC_ASP_SLIMBUS_COMMAND_ADDR(base) ((base) + (0x020))
#define SOC_ASP_SLIMBUS_STATE_ADDR(base) ((base) + (0x024))
#define SOC_ASP_SLIMBUS_IE_STATE_ADDR(base) ((base) + (0x028))
#define SOC_ASP_SLIMBUS_MCH_USAGE_ADDR(base) ((base) + (0x02C))
#define SOC_ASP_SLIMBUS_INT_EN_ADDR(base) ((base) + (0x038))
#define SOC_ASP_SLIMBUS_INT_ADDR(base) ((base) + (0x03C))
#define SOC_ASP_SLIMBUS_MC_FIFO_ADDR(base) ((base) + (0x040бл0x07C))
#define SOC_ASP_SLIMBUS_P0_INT_EN_ADDR(base) ((base) + (0x080))
#define SOC_ASP_SLIMBUS_P4_INT_EN_ADDR(base) ((base) + (0x084))
#define SOC_ASP_SLIMBUS_P8_INT_EN_ADDR(base) ((base) + (0x088))
#define SOC_ASP_SLIMBUS_P12_INT_EN_ADDR(base) ((base) + (0x08C))
#define SOC_ASP_SLIMBUS_P16_INT_EN_ADDR(base) ((base) + (0x090))
#define SOC_ASP_SLIMBUS_P20_INT_EN_ADDR(base) ((base) + (0x094))
#define SOC_ASP_SLIMBUS_P24_INT_EN_ADDR(base) ((base) + (0x098))
#define SOC_ASP_SLIMBUS_P28_INT_EN_ADDR(base) ((base) + (0x09C))
#define SOC_ASP_SLIMBUS_P32_INT_EN_ADDR(base) ((base) + (0x0A0))
#define SOC_ASP_SLIMBUS_P36_INT_EN_ADDR(base) ((base) + (0x0A4))
#define SOC_ASP_SLIMBUS_P40_INT_EN_ADDR(base) ((base) + (0x0A8))
#define SOC_ASP_SLIMBUS_P44_INT_EN_ADDR(base) ((base) + (0x0AC))
#define SOC_ASP_SLIMBUS_P48_INT_EN_ADDR(base) ((base) + (0x0B0))
#define SOC_ASP_SLIMBUS_P52_INT_EN_ADDR(base) ((base) + (0x0B4))
#define SOC_ASP_SLIMBUS_P56_INT_EN_ADDR(base) ((base) + (0x0B8))
#define SOC_ASP_SLIMBUS_P60_INT_EN_ADDR(base) ((base) + (0x0BC))
#define SOC_ASP_SLIMBUS_P0_INT_ADDR(base) ((base) + (0x0C0))
#define SOC_ASP_SLIMBUS_P4_INT_ADDR(base) ((base) + (0x0C4))
#define SOC_ASP_SLIMBUS_P8_INT_ADDR(base) ((base) + (0x0C8))
#define SOC_ASP_SLIMBUS_P12_INT_ADDR(base) ((base) + (0x0CC))
#define SOC_ASP_SLIMBUS_P16_INT_ADDR(base) ((base) + (0x0D0))
#define SOC_ASP_SLIMBUS_P20_INT_ADDR(base) ((base) + (0x0D4))
#define SOC_ASP_SLIMBUS_P24_INT_ADDR(base) ((base) + (0x0D8))
#define SOC_ASP_SLIMBUS_P28_INT_ADDR(base) ((base) + (0x0DC))
#define SOC_ASP_SLIMBUS_P32_INT_ADDR(base) ((base) + (0x0E0))
#define SOC_ASP_SLIMBUS_P36_INT_ADDR(base) ((base) + (0x0E4))
#define SOC_ASP_SLIMBUS_P40_INT_ADDR(base) ((base) + (0x0E8))
#define SOC_ASP_SLIMBUS_P44_INT_ADDR(base) ((base) + (0x0EC))
#define SOC_ASP_SLIMBUS_P48_INT_ADDR(base) ((base) + (0x0F0))
#define SOC_ASP_SLIMBUS_P52_INT_ADDR(base) ((base) + (0x0F4))
#define SOC_ASP_SLIMBUS_P56_INT_ADDR(base) ((base) + (0x0F8))
#define SOC_ASP_SLIMBUS_P60_INT_ADDR(base) ((base) + (0x0FC))
#define SOC_ASP_SLIMBUS_P0_STATE_0_ADDR(base) ((base) + (0x100))
#define SOC_ASP_SLIMBUS_P0_STATE_1_ADDR(base) ((base) + (0x104))
#define SOC_ASP_SLIMBUS_P1_STATE_0_ADDR(base) ((base) + (0x108))
#define SOC_ASP_SLIMBUS_P1_STATE_1_ADDR(base) ((base) + (0x10C))
#define SOC_ASP_SLIMBUS_P2_STATE_0_ADDR(base) ((base) + (0x110))
#define SOC_ASP_SLIMBUS_P2_STATE_1_ADDR(base) ((base) + (0x114))
#define SOC_ASP_SLIMBUS_P3_STATE_0_ADDR(base) ((base) + (0x118))
#define SOC_ASP_SLIMBUS_P3_STATE_1_ADDR(base) ((base) + (0x11C))
#define SOC_ASP_SLIMBUS_P4_STATE_0_ADDR(base) ((base) + (0x120))
#define SOC_ASP_SLIMBUS_P4_STATE_1_ADDR(base) ((base) + (0x124))
#define SOC_ASP_SLIMBUS_P5_STATE_0_ADDR(base) ((base) + (0x128))
#define SOC_ASP_SLIMBUS_P5_STATE_1_ADDR(base) ((base) + (0x12C))
#define SOC_ASP_SLIMBUS_P6_STATE_0_ADDR(base) ((base) + (0x130))
#define SOC_ASP_SLIMBUS_P6_STATE_1_ADDR(base) ((base) + (0x134))
#define SOC_ASP_SLIMBUS_P7_STATE_0_ADDR(base) ((base) + (0x138))
#define SOC_ASP_SLIMBUS_P7_STATE_1_ADDR(base) ((base) + (0x13C))
#define SOC_ASP_SLIMBUS_P8_STATE_0_ADDR(base) ((base) + (0x140))
#define SOC_ASP_SLIMBUS_P8_STATE_1_ADDR(base) ((base) + (0x144))
#define SOC_ASP_SLIMBUS_P9_STATE_0_ADDR(base) ((base) + (0x148))
#define SOC_ASP_SLIMBUS_P9_STATE_1_ADDR(base) ((base) + (0x14C))
#define SOC_ASP_SLIMBUS_P10_STATE_0_ADDR(base) ((base) + (0x150))
#define SOC_ASP_SLIMBUS_P10_STATE_1_ADDR(base) ((base) + (0x154))
#define SOC_ASP_SLIMBUS_P11_STATE_0_ADDR(base) ((base) + (0x158))
#define SOC_ASP_SLIMBUS_P11_STATE_1_ADDR(base) ((base) + (0x15C))
#define SOC_ASP_SLIMBUS_P12_STATE_0_ADDR(base) ((base) + (0x160))
#define SOC_ASP_SLIMBUS_P12_STATE_1_ADDR(base) ((base) + (0x164))
#define SOC_ASP_SLIMBUS_P13_STATE_0_ADDR(base) ((base) + (0x168))
#define SOC_ASP_SLIMBUS_P13_STATE_1_ADDR(base) ((base) + (0x16C))
#define SOC_ASP_SLIMBUS_P14_STATE_0_ADDR(base) ((base) + (0x170))
#define SOC_ASP_SLIMBUS_P14_STATE_1_ADDR(base) ((base) + (0x174))
#define SOC_ASP_SLIMBUS_P15_STATE_0_ADDR(base) ((base) + (0x178))
#define SOC_ASP_SLIMBUS_P15_STATE_1_ADDR(base) ((base) + (0x17C))
#define SOC_ASP_SLIMBUS_P16_STATE_0_ADDR(base) ((base) + (0x180))
#define SOC_ASP_SLIMBUS_P16_STATE_1_ADDR(base) ((base) + (0x184))
#define SOC_ASP_SLIMBUS_P17_STATE_0_ADDR(base) ((base) + (0x188))
#define SOC_ASP_SLIMBUS_P17_STATE_1_ADDR(base) ((base) + (0x18C))
#define SOC_ASP_SLIMBUS_P18_STATE_0_ADDR(base) ((base) + (0x190))
#define SOC_ASP_SLIMBUS_P18_STATE_1_ADDR(base) ((base) + (0x194))
#define SOC_ASP_SLIMBUS_P19_STATE_0_ADDR(base) ((base) + (0x198))
#define SOC_ASP_SLIMBUS_P19_STATE_1_ADDR(base) ((base) + (0x19C))
#define SOC_ASP_SLIMBUS_P20_STATE_0_ADDR(base) ((base) + (0x1A0))
#define SOC_ASP_SLIMBUS_P20_STATE_1_ADDR(base) ((base) + (0x1A4))
#define SOC_ASP_SLIMBUS_P21_STATE_0_ADDR(base) ((base) + (0x1A8))
#define SOC_ASP_SLIMBUS_P21_STATE_1_ADDR(base) ((base) + (0x1AC))
#define SOC_ASP_SLIMBUS_P22_STATE_0_ADDR(base) ((base) + (0x1B0))
#define SOC_ASP_SLIMBUS_P22_STATE_1_ADDR(base) ((base) + (0x1B4))
#define SOC_ASP_SLIMBUS_P23_STATE_0_ADDR(base) ((base) + (0x1B8))
#define SOC_ASP_SLIMBUS_P23_STATE_1_ADDR(base) ((base) + (0x1BC))
#define SOC_ASP_SLIMBUS_P24_STATE_0_ADDR(base) ((base) + (0x1C0))
#define SOC_ASP_SLIMBUS_P24_STATE_1_ADDR(base) ((base) + (0x1C4))
#define SOC_ASP_SLIMBUS_P25_STATE_0_ADDR(base) ((base) + (0x1C8))
#define SOC_ASP_SLIMBUS_P25_STATE_1_ADDR(base) ((base) + (0x1CC))
#define SOC_ASP_SLIMBUS_P26_STATE_0_ADDR(base) ((base) + (0x1D0))
#define SOC_ASP_SLIMBUS_P26_STATE_1_ADDR(base) ((base) + (0x1D4))
#define SOC_ASP_SLIMBUS_P27_STATE_0_ADDR(base) ((base) + (0x1D8))
#define SOC_ASP_SLIMBUS_P27_STATE_1_ADDR(base) ((base) + (0x1DC))
#define SOC_ASP_SLIMBUS_P28_STATE_0_ADDR(base) ((base) + (0x1E0))
#define SOC_ASP_SLIMBUS_P28_STATE_1_ADDR(base) ((base) + (0x1E4))
#define SOC_ASP_SLIMBUS_P29_STATE_0_ADDR(base) ((base) + (0x1E8))
#define SOC_ASP_SLIMBUS_P29_STATE_1_ADDR(base) ((base) + (0x1EC))
#define SOC_ASP_SLIMBUS_P30_STATE_0_ADDR(base) ((base) + (0x1F0))
#define SOC_ASP_SLIMBUS_P30_STATE_1_ADDR(base) ((base) + (0x1F4))
#define SOC_ASP_SLIMBUS_P31_STATE_0_ADDR(base) ((base) + (0x1F8))
#define SOC_ASP_SLIMBUS_P31_STATE_1_ADDR(base) ((base) + (0x1FC))
#define SOC_ASP_SLIMBUS_P32_STATE_0_ADDR(base) ((base) + (0x200))
#define SOC_ASP_SLIMBUS_P32_STATE_1_ADDR(base) ((base) + (0x204))
#define SOC_ASP_SLIMBUS_P33_STATE_0_ADDR(base) ((base) + (0x208))
#define SOC_ASP_SLIMBUS_P33_STATE_1_ADDR(base) ((base) + (0x20C))
#define SOC_ASP_SLIMBUS_P34_STATE_0_ADDR(base) ((base) + (0x210))
#define SOC_ASP_SLIMBUS_P34_STATE_1_ADDR(base) ((base) + (0x214))
#define SOC_ASP_SLIMBUS_P35_STATE_0_ADDR(base) ((base) + (0x218))
#define SOC_ASP_SLIMBUS_P35_STATE_1_ADDR(base) ((base) + (0x21C))
#define SOC_ASP_SLIMBUS_P36_STATE_0_ADDR(base) ((base) + (0x220))
#define SOC_ASP_SLIMBUS_P36_STATE_1_ADDR(base) ((base) + (0x224))
#define SOC_ASP_SLIMBUS_P37_STATE_0_ADDR(base) ((base) + (0x228))
#define SOC_ASP_SLIMBUS_P37_STATE_1_ADDR(base) ((base) + (0x22C))
#define SOC_ASP_SLIMBUS_P38_STATE_0_ADDR(base) ((base) + (0x230))
#define SOC_ASP_SLIMBUS_P38_STATE_1_ADDR(base) ((base) + (0x234))
#define SOC_ASP_SLIMBUS_P39_STATE_0_ADDR(base) ((base) + (0x238))
#define SOC_ASP_SLIMBUS_P39_STATE_1_ADDR(base) ((base) + (0x23C))
#define SOC_ASP_SLIMBUS_P40_STATE_0_ADDR(base) ((base) + (0x240))
#define SOC_ASP_SLIMBUS_P40_STATE_1_ADDR(base) ((base) + (0x244))
#define SOC_ASP_SLIMBUS_P41_STATE_0_ADDR(base) ((base) + (0x248))
#define SOC_ASP_SLIMBUS_P41_STATE_1_ADDR(base) ((base) + (0x24C))
#define SOC_ASP_SLIMBUS_P42_STATE_0_ADDR(base) ((base) + (0x250))
#define SOC_ASP_SLIMBUS_P42_STATE_1_ADDR(base) ((base) + (0x254))
#define SOC_ASP_SLIMBUS_P43_STATE_0_ADDR(base) ((base) + (0x258))
#define SOC_ASP_SLIMBUS_P43_STATE_1_ADDR(base) ((base) + (0x25C))
#define SOC_ASP_SLIMBUS_P44_STATE_0_ADDR(base) ((base) + (0x260))
#define SOC_ASP_SLIMBUS_P44_STATE_1_ADDR(base) ((base) + (0x264))
#define SOC_ASP_SLIMBUS_P45_STATE_0_ADDR(base) ((base) + (0x268))
#define SOC_ASP_SLIMBUS_P45_STATE_1_ADDR(base) ((base) + (0x26C))
#define SOC_ASP_SLIMBUS_P46_STATE_0_ADDR(base) ((base) + (0x270))
#define SOC_ASP_SLIMBUS_P46_STATE_1_ADDR(base) ((base) + (0x274))
#define SOC_ASP_SLIMBUS_P47_STATE_0_ADDR(base) ((base) + (0x278))
#define SOC_ASP_SLIMBUS_P47_STATE_1_ADDR(base) ((base) + (0x27C))
#define SOC_ASP_SLIMBUS_P48_STATE_0_ADDR(base) ((base) + (0x280))
#define SOC_ASP_SLIMBUS_P48_STATE_1_ADDR(base) ((base) + (0x284))
#define SOC_ASP_SLIMBUS_P49_STATE_0_ADDR(base) ((base) + (0x288))
#define SOC_ASP_SLIMBUS_P49_STATE_1_ADDR(base) ((base) + (0x28C))
#define SOC_ASP_SLIMBUS_P50_STATE_0_ADDR(base) ((base) + (0x290))
#define SOC_ASP_SLIMBUS_P50_STATE_1_ADDR(base) ((base) + (0x294))
#define SOC_ASP_SLIMBUS_P51_STATE_0_ADDR(base) ((base) + (0x298))
#define SOC_ASP_SLIMBUS_P51_STATE_1_ADDR(base) ((base) + (0x29C))
#define SOC_ASP_SLIMBUS_P52_STATE_0_ADDR(base) ((base) + (0x2A0))
#define SOC_ASP_SLIMBUS_P52_STATE_1_ADDR(base) ((base) + (0x2A4))
#define SOC_ASP_SLIMBUS_P53_STATE_0_ADDR(base) ((base) + (0x2A8))
#define SOC_ASP_SLIMBUS_P53_STATE_1_ADDR(base) ((base) + (0x2AC))
#define SOC_ASP_SLIMBUS_P54_STATE_0_ADDR(base) ((base) + (0x2B0))
#define SOC_ASP_SLIMBUS_P54_STATE_1_ADDR(base) ((base) + (0x2B4))
#define SOC_ASP_SLIMBUS_P55_STATE_0_ADDR(base) ((base) + (0x2B8))
#define SOC_ASP_SLIMBUS_P55_STATE_1_ADDR(base) ((base) + (0x2BC))
#define SOC_ASP_SLIMBUS_P56_STATE_0_ADDR(base) ((base) + (0x2C0))
#define SOC_ASP_SLIMBUS_P56_STATE_1_ADDR(base) ((base) + (0x2C4))
#define SOC_ASP_SLIMBUS_P57_STATE_0_ADDR(base) ((base) + (0x2C8))
#define SOC_ASP_SLIMBUS_P57_STATE_1_ADDR(base) ((base) + (0x2CC))
#define SOC_ASP_SLIMBUS_P58_STATE_0_ADDR(base) ((base) + (0x2D0))
#define SOC_ASP_SLIMBUS_P58_STATE_1_ADDR(base) ((base) + (0x2D4))
#define SOC_ASP_SLIMBUS_P59_STATE_0_ADDR(base) ((base) + (0x2D8))
#define SOC_ASP_SLIMBUS_P59_STATE_1_ADDR(base) ((base) + (0x2DC))
#define SOC_ASP_SLIMBUS_P60_STATE_0_ADDR(base) ((base) + (0x2E0))
#define SOC_ASP_SLIMBUS_P60_STATE_1_ADDR(base) ((base) + (0x2E4))
#define SOC_ASP_SLIMBUS_P61_STATE_0_ADDR(base) ((base) + (0x2E8))
#define SOC_ASP_SLIMBUS_P61_STATE_1_ADDR(base) ((base) + (0x2EC))
#define SOC_ASP_SLIMBUS_P62_STATE_0_ADDR(base) ((base) + (0x2F0))
#define SOC_ASP_SLIMBUS_P62_STATE_1_ADDR(base) ((base) + (0x2F4))
#define SOC_ASP_SLIMBUS_P63_STATE_0_ADDR(base) ((base) + (0x2F8))
#define SOC_ASP_SLIMBUS_P63_STATE_1_ADDR(base) ((base) + (0x2FC))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ENABLE : 1;
        unsigned int MANAGER_MODE : 1;
        unsigned int SNIFFER_MODE : 1;
        unsigned int FR_EN : 1;
        unsigned int DEV_EN : 1;
        unsigned int GO_ABSENT : 1;
        unsigned int reserved_0 : 2;
        unsigned int RETRY_LMT : 4;
        unsigned int REPORT_AT_EVENT : 1;
        unsigned int CRC_CALC_DISABLE : 1;
        unsigned int LMTD_REPORT : 1;
        unsigned int RECONF_TX_DIS : 1;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_MODE_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ENABLE_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_ENABLE_END (0)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_MANAGER_MODE_START (1)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_MANAGER_MODE_END (1)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_SNIFFER_MODE_START (2)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_SNIFFER_MODE_END (2)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_FR_EN_START (3)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_FR_EN_END (3)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_DEV_EN_START (4)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_DEV_EN_END (4)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_GO_ABSENT_START (5)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_GO_ABSENT_END (5)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RETRY_LMT_START (8)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RETRY_LMT_END (11)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_REPORT_AT_EVENT_START (12)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_REPORT_AT_EVENT_END (12)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_CRC_CALC_DISABLE_START (13)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_CRC_CALC_DISABLE_END (13)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_LMTD_REPORT_START (14)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_LMTD_REPORT_END (14)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RECONF_TX_DIS_START (15)
#define SOC_ASP_SLIMBUS_CONFIG_MODE_RECONF_TX_DIS_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PRODUCT_ID : 16;
        unsigned int INSTANCE_VAL : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_EA_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_EA_PRODUCT_ID_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_EA_PRODUCT_ID_END (15)
#define SOC_ASP_SLIMBUS_CONFIG_EA_INSTANCE_VAL_START (16)
#define SOC_ASP_SLIMBUS_CONFIG_EA_INSTANCE_VAL_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PR_SUPP : 24;
        unsigned int TP_SUPP : 3;
        unsigned int reserved : 5;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_PR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_PR_PR_SUPP_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_PR_PR_SUPP_END (23)
#define SOC_ASP_SLIMBUS_CONFIG_PR_TP_SUPP_START (24)
#define SOC_ASP_SLIMBUS_CONFIG_PR_TP_SUPP_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RF_SUPP : 16;
        unsigned int QUALITY : 2;
        unsigned int PAUSE_AT_RFCHNG : 1;
        unsigned int reserved : 13;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_FR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_FR_RF_SUPP_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_FR_RF_SUPP_END (15)
#define SOC_ASP_SLIMBUS_CONFIG_FR_QUALITY_START (16)
#define SOC_ASP_SLIMBUS_CONFIG_FR_QUALITY_END (17)
#define SOC_ASP_SLIMBUS_CONFIG_FR_PAUSE_AT_RFCHNG_START (18)
#define SOC_ASP_SLIMBUS_CONFIG_FR_PAUSE_AT_RFCHNG_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SINK_START_LVL : 8;
        unsigned int DPORT_CLK_PRESC : 4;
        unsigned int REFCLK_SEL : 2;
        unsigned int reserved : 18;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_DPORT_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_SINK_START_LVL_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_SINK_START_LVL_END (7)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_DPORT_CLK_PRESC_START (8)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_DPORT_CLK_PRESC_END (11)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_REFCLK_SEL_START (12)
#define SOC_ASP_SLIMBUS_CONFIG_DPORT_REFCLK_SEL_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CPORT_CLK_DIV : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_CPORT_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_CPORT_CLK_DIV_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_CPORT_CPORT_CLK_DIV_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DEVICE_ID_1 : 8;
        unsigned int DEVICE_ID_2 : 8;
        unsigned int DEVICE_ID_3 : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_EA2_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_1_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_1_END (7)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_2_START (8)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_2_END (15)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_3_START (16)
#define SOC_ASP_SLIMBUS_CONFIG_EA2_DEVICE_ID_3_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SRC_THR : 8;
        unsigned int reserved_0: 8;
        unsigned int SINK_THR : 5;
        unsigned int reserved_1: 11;
    } reg;
} SOC_ASP_SLIMBUS_CONFIG_THR_UNION;
#endif
#define SOC_ASP_SLIMBUS_CONFIG_THR_SRC_THR_START (0)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SRC_THR_END (7)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SINK_THR_START (16)
#define SOC_ASP_SLIMBUS_CONFIG_THR_SINK_THR_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TX_PUSH : 1;
        unsigned int RX_PULL : 1;
        unsigned int TX_CLR : 1;
        unsigned int UNFREEZE : 1;
        unsigned int CFG_STROBE : 1;
        unsigned int CFG_STROBE_CLR : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_SLIMBUS_COMMAND_UNION;
#endif
#define SOC_ASP_SLIMBUS_COMMAND_TX_PUSH_START (0)
#define SOC_ASP_SLIMBUS_COMMAND_TX_PUSH_END (0)
#define SOC_ASP_SLIMBUS_COMMAND_RX_PULL_START (1)
#define SOC_ASP_SLIMBUS_COMMAND_RX_PULL_END (1)
#define SOC_ASP_SLIMBUS_COMMAND_TX_CLR_START (2)
#define SOC_ASP_SLIMBUS_COMMAND_TX_CLR_END (2)
#define SOC_ASP_SLIMBUS_COMMAND_UNFREEZE_START (3)
#define SOC_ASP_SLIMBUS_COMMAND_UNFREEZE_END (3)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_START (4)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_END (4)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_CLR_START (5)
#define SOC_ASP_SLIMBUS_COMMAND_CFG_STROBE_CLR_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TX_FULL : 1;
        unsigned int TX_NOTEMPTY : 1;
        unsigned int RX_NOTEMPTY : 1;
        unsigned int reserved_0 : 1;
        unsigned int TX_PUSH : 1;
        unsigned int RX_PULL : 1;
        unsigned int reserved_1 : 2;
        unsigned int F_SYNC : 1;
        unsigned int SF_SYNC : 1;
        unsigned int M_SYNC : 1;
        unsigned int SFB_SYNC : 1;
        unsigned int PH_SYNC : 1;
        unsigned int reserved_2 : 2;
        unsigned int DETACHED : 1;
        unsigned int SUBFRAME_MODE : 5;
        unsigned int reserved_3 : 3;
        unsigned int CLOCK_GEAR : 4;
        unsigned int ROOT_FR : 4;
    } reg;
} SOC_ASP_SLIMBUS_STATE_UNION;
#endif
#define SOC_ASP_SLIMBUS_STATE_TX_FULL_START (0)
#define SOC_ASP_SLIMBUS_STATE_TX_FULL_END (0)
#define SOC_ASP_SLIMBUS_STATE_TX_NOTEMPTY_START (1)
#define SOC_ASP_SLIMBUS_STATE_TX_NOTEMPTY_END (1)
#define SOC_ASP_SLIMBUS_STATE_RX_NOTEMPTY_START (2)
#define SOC_ASP_SLIMBUS_STATE_RX_NOTEMPTY_END (2)
#define SOC_ASP_SLIMBUS_STATE_TX_PUSH_START (4)
#define SOC_ASP_SLIMBUS_STATE_TX_PUSH_END (4)
#define SOC_ASP_SLIMBUS_STATE_RX_PULL_START (5)
#define SOC_ASP_SLIMBUS_STATE_RX_PULL_END (5)
#define SOC_ASP_SLIMBUS_STATE_F_SYNC_START (8)
#define SOC_ASP_SLIMBUS_STATE_F_SYNC_END (8)
#define SOC_ASP_SLIMBUS_STATE_SF_SYNC_START (9)
#define SOC_ASP_SLIMBUS_STATE_SF_SYNC_END (9)
#define SOC_ASP_SLIMBUS_STATE_M_SYNC_START (10)
#define SOC_ASP_SLIMBUS_STATE_M_SYNC_END (10)
#define SOC_ASP_SLIMBUS_STATE_SFB_SYNC_START (11)
#define SOC_ASP_SLIMBUS_STATE_SFB_SYNC_END (11)
#define SOC_ASP_SLIMBUS_STATE_PH_SYNC_START (12)
#define SOC_ASP_SLIMBUS_STATE_PH_SYNC_END (12)
#define SOC_ASP_SLIMBUS_STATE_DETACHED_START (15)
#define SOC_ASP_SLIMBUS_STATE_DETACHED_END (15)
#define SOC_ASP_SLIMBUS_STATE_SUBFRAME_MODE_START (16)
#define SOC_ASP_SLIMBUS_STATE_SUBFRAME_MODE_END (20)
#define SOC_ASP_SLIMBUS_STATE_CLOCK_GEAR_START (24)
#define SOC_ASP_SLIMBUS_STATE_CLOCK_GEAR_END (27)
#define SOC_ASP_SLIMBUS_STATE_ROOT_FR_START (28)
#define SOC_ASP_SLIMBUS_STATE_ROOT_FR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EX_ERROR_IF : 1;
        unsigned int reserved_0 : 1;
        unsigned int UNSPRTD_MSG_IF : 1;
        unsigned int MC_TX_COL : 1;
        unsigned int LOST_FS : 1;
        unsigned int LOST_SFS : 1;
        unsigned int LOST_MS : 1;
        unsigned int DATA_SLOT_OVERLAP : 1;
        unsigned int EX_ERROR_FR : 1;
        unsigned int RCFG_OBJECTION : 1;
        unsigned int UNSPRTD_MSG_FR : 1;
        unsigned int ACTIVE_FRAMER : 1;
        unsigned int FS_TX_COL : 1;
        unsigned int FI_TX_COL : 1;
        unsigned int GC_TX_COL : 1;
        unsigned int reserved_1 : 1;
        unsigned int EX_ERROR_DEV : 1;
        unsigned int DATA_TX_COL : 1;
        unsigned int UNSPRTD_MSG_DEV : 1;
        unsigned int reserved_2 : 13;
    } reg;
} SOC_ASP_SLIMBUS_IE_STATE_UNION;
#endif
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_IF_START (0)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_IF_END (0)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_IF_START (2)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_IF_END (2)
#define SOC_ASP_SLIMBUS_IE_STATE_MC_TX_COL_START (3)
#define SOC_ASP_SLIMBUS_IE_STATE_MC_TX_COL_END (3)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_FS_START (4)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_FS_END (4)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_SFS_START (5)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_SFS_END (5)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_MS_START (6)
#define SOC_ASP_SLIMBUS_IE_STATE_LOST_MS_END (6)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_SLOT_OVERLAP_START (7)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_SLOT_OVERLAP_END (7)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_FR_START (8)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_FR_END (8)
#define SOC_ASP_SLIMBUS_IE_STATE_RCFG_OBJECTION_START (9)
#define SOC_ASP_SLIMBUS_IE_STATE_RCFG_OBJECTION_END (9)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_FR_START (10)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_FR_END (10)
#define SOC_ASP_SLIMBUS_IE_STATE_ACTIVE_FRAMER_START (11)
#define SOC_ASP_SLIMBUS_IE_STATE_ACTIVE_FRAMER_END (11)
#define SOC_ASP_SLIMBUS_IE_STATE_FS_TX_COL_START (12)
#define SOC_ASP_SLIMBUS_IE_STATE_FS_TX_COL_END (12)
#define SOC_ASP_SLIMBUS_IE_STATE_FI_TX_COL_START (13)
#define SOC_ASP_SLIMBUS_IE_STATE_FI_TX_COL_END (13)
#define SOC_ASP_SLIMBUS_IE_STATE_GC_TX_COL_START (14)
#define SOC_ASP_SLIMBUS_IE_STATE_GC_TX_COL_END (14)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_DEV_START (16)
#define SOC_ASP_SLIMBUS_IE_STATE_EX_ERROR_DEV_END (16)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_TX_COL_START (17)
#define SOC_ASP_SLIMBUS_IE_STATE_DATA_TX_COL_END (17)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_DEV_START (18)
#define SOC_ASP_SLIMBUS_IE_STATE_UNSPRTD_MSG_DEV_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MCH_USAGE : 11;
        unsigned int reserved : 5;
        unsigned int MCH_CAPACITY : 11;
        unsigned int MCH_LAPSE : 5;
    } reg;
} SOC_ASP_SLIMBUS_MCH_USAGE_UNION;
#endif
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_USAGE_START (0)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_USAGE_END (10)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_CAPACITY_START (16)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_CAPACITY_END (26)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_LAPSE_START (27)
#define SOC_ASP_SLIMBUS_MCH_USAGE_MCH_LAPSE_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IN_EN : 1;
        unsigned int RX_INT_EN : 1;
        unsigned int TX_INT_EN : 1;
        unsigned int TX_ERR_EN : 1;
        unsigned int SYNC_LOST_EN : 1;
        unsigned int RCFG_INT_EN : 1;
        unsigned int MCH_INT_EN : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_ASP_SLIMBUS_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_INT_EN_IN_EN_START (0)
#define SOC_ASP_SLIMBUS_INT_EN_IN_EN_END (0)
#define SOC_ASP_SLIMBUS_INT_EN_RX_INT_EN_START (1)
#define SOC_ASP_SLIMBUS_INT_EN_RX_INT_EN_END (1)
#define SOC_ASP_SLIMBUS_INT_EN_TX_INT_EN_START (2)
#define SOC_ASP_SLIMBUS_INT_EN_TX_INT_EN_END (2)
#define SOC_ASP_SLIMBUS_INT_EN_TX_ERR_EN_START (3)
#define SOC_ASP_SLIMBUS_INT_EN_TX_ERR_EN_END (3)
#define SOC_ASP_SLIMBUS_INT_EN_SYNC_LOST_EN_START (4)
#define SOC_ASP_SLIMBUS_INT_EN_SYNC_LOST_EN_END (4)
#define SOC_ASP_SLIMBUS_INT_EN_RCFG_INT_EN_START (5)
#define SOC_ASP_SLIMBUS_INT_EN_RCFG_INT_EN_END (5)
#define SOC_ASP_SLIMBUS_INT_EN_MCH_INT_EN_START (6)
#define SOC_ASP_SLIMBUS_INT_EN_MCH_INT_EN_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int RX_INT : 1;
        unsigned int TX_INT : 1;
        unsigned int TX_ERR : 1;
        unsigned int SYNC_LOST : 1;
        unsigned int RCFG_INT : 1;
        unsigned int MCH_INT : 1;
        unsigned int PORT_INT : 1;
        unsigned int reserved_1: 24;
    } reg;
} SOC_ASP_SLIMBUS_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_INT_RX_INT_START (1)
#define SOC_ASP_SLIMBUS_INT_RX_INT_END (1)
#define SOC_ASP_SLIMBUS_INT_TX_INT_START (2)
#define SOC_ASP_SLIMBUS_INT_TX_INT_END (2)
#define SOC_ASP_SLIMBUS_INT_TX_ERR_START (3)
#define SOC_ASP_SLIMBUS_INT_TX_ERR_END (3)
#define SOC_ASP_SLIMBUS_INT_SYNC_LOST_START (4)
#define SOC_ASP_SLIMBUS_INT_SYNC_LOST_END (4)
#define SOC_ASP_SLIMBUS_INT_RCFG_INT_START (5)
#define SOC_ASP_SLIMBUS_INT_RCFG_INT_END (5)
#define SOC_ASP_SLIMBUS_INT_MCH_INT_START (6)
#define SOC_ASP_SLIMBUS_INT_MCH_INT_END (6)
#define SOC_ASP_SLIMBUS_INT_PORT_INT_START (7)
#define SOC_ASP_SLIMBUS_INT_PORT_INT_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MSG_SIZE : 6;
        unsigned int reserved : 2;
        unsigned int RX_OVERFLOW : 1;
        unsigned int TX_ERR : 7;
        unsigned int LOST_MSG_NUM : 16;
    } reg;
} SOC_ASP_SLIMBUS_MC_FIFO_UNION;
#endif
#define SOC_ASP_SLIMBUS_MC_FIFO_MSG_SIZE_START (0)
#define SOC_ASP_SLIMBUS_MC_FIFO_MSG_SIZE_END (5)
#define SOC_ASP_SLIMBUS_MC_FIFO_RX_OVERFLOW_START (8)
#define SOC_ASP_SLIMBUS_MC_FIFO_RX_OVERFLOW_END (8)
#define SOC_ASP_SLIMBUS_MC_FIFO_TX_ERR_START (9)
#define SOC_ASP_SLIMBUS_MC_FIFO_TX_ERR_END (15)
#define SOC_ASP_SLIMBUS_MC_FIFO_LOST_MSG_NUM_START (16)
#define SOC_ASP_SLIMBUS_MC_FIFO_LOST_MSG_NUM_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int_en0 : 1;
        unsigned int con_int_en0 : 1;
        unsigned int chan_int_en0 : 1;
        unsigned int dma_int_en0 : 1;
        unsigned int ovf_int_en0 : 1;
        unsigned int und_int_en0 : 1;
        unsigned int fifo_clr0 : 1;
        unsigned int pr_gen_en0 : 1;
        unsigned int act_int_en1 : 1;
        unsigned int con_int_en1 : 1;
        unsigned int chan_int_en1 : 1;
        unsigned int dma_int_en1 : 1;
        unsigned int ovf_int_en1 : 1;
        unsigned int und_int_en1 : 1;
        unsigned int fifo_clr1 : 1;
        unsigned int pr_gen_en1 : 1;
        unsigned int act_int_en2 : 1;
        unsigned int con_int_en2 : 1;
        unsigned int chan_int_en2 : 1;
        unsigned int dma_int_en2 : 1;
        unsigned int ovf_int_en2 : 1;
        unsigned int und_int_en2 : 1;
        unsigned int fifo_clr2 : 1;
        unsigned int pr_gen_en2 : 1;
        unsigned int act_int_en3 : 1;
        unsigned int con_int_en3 : 1;
        unsigned int chan_int_en3 : 1;
        unsigned int dma_int_en3 : 1;
        unsigned int ovf_int_en3 : 1;
        unsigned int und_int_en3 : 1;
        unsigned int fifo_clr3 : 1;
        unsigned int pr_gen_en3 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P0_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en0_START (0)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en0_END (0)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en0_START (1)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en0_END (1)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en0_START (2)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en0_END (2)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en0_START (3)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en0_END (3)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en0_START (4)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en0_END (4)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en0_START (5)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en0_END (5)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr0_START (6)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr0_END (6)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en0_START (7)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en0_END (7)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en1_START (8)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en1_END (8)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en1_START (9)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en1_END (9)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en1_START (10)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en1_END (10)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en1_START (11)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en1_END (11)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en1_START (12)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en1_END (12)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en1_START (13)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en1_END (13)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr1_START (14)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr1_END (14)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en1_START (15)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en1_END (15)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en2_START (16)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en2_END (16)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en2_START (17)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en2_END (17)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en2_START (18)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en2_END (18)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en2_START (19)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en2_END (19)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en2_START (20)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en2_END (20)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en2_START (21)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en2_END (21)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr2_START (22)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr2_END (22)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en2_START (23)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en2_END (23)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en3_START (24)
#define SOC_ASP_SLIMBUS_P0_INT_EN_act_int_en3_END (24)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en3_START (25)
#define SOC_ASP_SLIMBUS_P0_INT_EN_con_int_en3_END (25)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en3_START (26)
#define SOC_ASP_SLIMBUS_P0_INT_EN_chan_int_en3_END (26)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en3_START (27)
#define SOC_ASP_SLIMBUS_P0_INT_EN_dma_int_en3_END (27)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en3_START (28)
#define SOC_ASP_SLIMBUS_P0_INT_EN_ovf_int_en3_END (28)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en3_START (29)
#define SOC_ASP_SLIMBUS_P0_INT_EN_und_int_en3_END (29)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr3_START (30)
#define SOC_ASP_SLIMBUS_P0_INT_EN_fifo_clr3_END (30)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en3_START (31)
#define SOC_ASP_SLIMBUS_P0_INT_EN_pr_gen_en3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int_en4 : 1;
        unsigned int con_int_en4 : 1;
        unsigned int chan_int_en4 : 1;
        unsigned int dma_int_en4 : 1;
        unsigned int ovf_int_en4 : 1;
        unsigned int und_int_en4 : 1;
        unsigned int fifo_clr4 : 1;
        unsigned int pr_gen_en4 : 1;
        unsigned int act_int_en5 : 1;
        unsigned int con_int_en5 : 1;
        unsigned int chan_int_en5 : 1;
        unsigned int dma_int_en5 : 1;
        unsigned int ovf_int_en5 : 1;
        unsigned int und_int_en5 : 1;
        unsigned int fifo_clr5 : 1;
        unsigned int pr_gen_en5 : 1;
        unsigned int act_int_en6 : 1;
        unsigned int con_int_en6 : 1;
        unsigned int chan_int_en6 : 1;
        unsigned int dma_int_en6 : 1;
        unsigned int ovf_int_en6 : 1;
        unsigned int und_int_en6 : 1;
        unsigned int fifo_clr6 : 1;
        unsigned int pr_gen_en6 : 1;
        unsigned int act_int_en7 : 1;
        unsigned int con_int_en7 : 1;
        unsigned int chan_int_en7 : 1;
        unsigned int dma_int_en7 : 1;
        unsigned int ovf_int_en7 : 1;
        unsigned int und_int_en7 : 1;
        unsigned int fifo_clr7 : 1;
        unsigned int pr_gen_en7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P4_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en4_START (0)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en4_END (0)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en4_START (1)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en4_END (1)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en4_START (2)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en4_END (2)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en4_START (3)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en4_END (3)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en4_START (4)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en4_END (4)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en4_START (5)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en4_END (5)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr4_START (6)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr4_END (6)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en4_START (7)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en4_END (7)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en5_START (8)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en5_END (8)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en5_START (9)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en5_END (9)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en5_START (10)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en5_END (10)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en5_START (11)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en5_END (11)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en5_START (12)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en5_END (12)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en5_START (13)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en5_END (13)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr5_START (14)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr5_END (14)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en5_START (15)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en5_END (15)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en6_START (16)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en6_END (16)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en6_START (17)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en6_END (17)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en6_START (18)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en6_END (18)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en6_START (19)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en6_END (19)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en6_START (20)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en6_END (20)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en6_START (21)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en6_END (21)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr6_START (22)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr6_END (22)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en6_START (23)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en6_END (23)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en7_START (24)
#define SOC_ASP_SLIMBUS_P4_INT_EN_act_int_en7_END (24)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en7_START (25)
#define SOC_ASP_SLIMBUS_P4_INT_EN_con_int_en7_END (25)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en7_START (26)
#define SOC_ASP_SLIMBUS_P4_INT_EN_chan_int_en7_END (26)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en7_START (27)
#define SOC_ASP_SLIMBUS_P4_INT_EN_dma_int_en7_END (27)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en7_START (28)
#define SOC_ASP_SLIMBUS_P4_INT_EN_ovf_int_en7_END (28)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en7_START (29)
#define SOC_ASP_SLIMBUS_P4_INT_EN_und_int_en7_END (29)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr7_START (30)
#define SOC_ASP_SLIMBUS_P4_INT_EN_fifo_clr7_END (30)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en7_START (31)
#define SOC_ASP_SLIMBUS_P4_INT_EN_pr_gen_en7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int_en8 : 1;
        unsigned int con_int_en8 : 1;
        unsigned int chan_int_en8 : 1;
        unsigned int dma_int_en8 : 1;
        unsigned int ovf_int_en8 : 1;
        unsigned int und_int_en8 : 1;
        unsigned int fifo_clr8 : 1;
        unsigned int pr_gen_en8 : 1;
        unsigned int act_int_en9 : 1;
        unsigned int con_int_en9 : 1;
        unsigned int chan_int_en9 : 1;
        unsigned int dma_int_en9 : 1;
        unsigned int ovf_int_en9 : 1;
        unsigned int und_int_en9 : 1;
        unsigned int fifo_clr9 : 1;
        unsigned int pr_gen_en9 : 1;
        unsigned int act_int_en10 : 1;
        unsigned int con_int_en10 : 1;
        unsigned int chan_int_en10 : 1;
        unsigned int dma_int_en10 : 1;
        unsigned int ovf_int_en10 : 1;
        unsigned int und_int_en10 : 1;
        unsigned int fifo_clr10 : 1;
        unsigned int pr_gen_en10 : 1;
        unsigned int act_int_en11 : 1;
        unsigned int con_int_en11 : 1;
        unsigned int chan_int_en11 : 1;
        unsigned int dma_int_en11 : 1;
        unsigned int ovf_int_en11 : 1;
        unsigned int und_int_en11 : 1;
        unsigned int fifo_clr11 : 1;
        unsigned int pr_gen_en11 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P8_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en8_START (0)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en8_END (0)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en8_START (1)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en8_END (1)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en8_START (2)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en8_END (2)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en8_START (3)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en8_END (3)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en8_START (4)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en8_END (4)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en8_START (5)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en8_END (5)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr8_START (6)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr8_END (6)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en8_START (7)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en8_END (7)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en9_START (8)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en9_END (8)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en9_START (9)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en9_END (9)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en9_START (10)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en9_END (10)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en9_START (11)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en9_END (11)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en9_START (12)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en9_END (12)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en9_START (13)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en9_END (13)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr9_START (14)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr9_END (14)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en9_START (15)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en9_END (15)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en10_START (16)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en10_END (16)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en10_START (17)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en10_END (17)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en10_START (18)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en10_END (18)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en10_START (19)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en10_END (19)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en10_START (20)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en10_END (20)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en10_START (21)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en10_END (21)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr10_START (22)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr10_END (22)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en10_START (23)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en10_END (23)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en11_START (24)
#define SOC_ASP_SLIMBUS_P8_INT_EN_act_int_en11_END (24)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en11_START (25)
#define SOC_ASP_SLIMBUS_P8_INT_EN_con_int_en11_END (25)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en11_START (26)
#define SOC_ASP_SLIMBUS_P8_INT_EN_chan_int_en11_END (26)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en11_START (27)
#define SOC_ASP_SLIMBUS_P8_INT_EN_dma_int_en11_END (27)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en11_START (28)
#define SOC_ASP_SLIMBUS_P8_INT_EN_ovf_int_en11_END (28)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en11_START (29)
#define SOC_ASP_SLIMBUS_P8_INT_EN_und_int_en11_END (29)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr11_START (30)
#define SOC_ASP_SLIMBUS_P8_INT_EN_fifo_clr11_END (30)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en11_START (31)
#define SOC_ASP_SLIMBUS_P8_INT_EN_pr_gen_en11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int_en12 : 1;
        unsigned int con_int_en12 : 1;
        unsigned int chan_int_en12 : 1;
        unsigned int dma_int_en12 : 1;
        unsigned int ovf_int_en12 : 1;
        unsigned int und_int_en12 : 1;
        unsigned int fifo_clr12 : 1;
        unsigned int pr_gen_en12 : 1;
        unsigned int act_int_en13 : 1;
        unsigned int con_int_en13 : 1;
        unsigned int chan_int_en13 : 1;
        unsigned int dma_int_en13 : 1;
        unsigned int ovf_int_en13 : 1;
        unsigned int und_int_en13 : 1;
        unsigned int fifo_clr13 : 1;
        unsigned int pr_gen_en13 : 1;
        unsigned int act_int_en14 : 1;
        unsigned int con_int_en14 : 1;
        unsigned int chan_int_en14 : 1;
        unsigned int dma_int_en14 : 1;
        unsigned int ovf_int_en14 : 1;
        unsigned int und_int_en14 : 1;
        unsigned int fifo_clr14 : 1;
        unsigned int pr_gen_en14 : 1;
        unsigned int act_int_en15 : 1;
        unsigned int con_int_en15 : 1;
        unsigned int chan_int_en15 : 1;
        unsigned int dma_int_en15 : 1;
        unsigned int ovf_int_en15 : 1;
        unsigned int und_int_en15 : 1;
        unsigned int fifo_clr15 : 1;
        unsigned int pr_gen_en15 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P12_INT_EN_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en12_START (0)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en12_END (0)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en12_START (1)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en12_END (1)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en12_START (2)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en12_END (2)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en12_START (3)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en12_END (3)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en12_START (4)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en12_END (4)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en12_START (5)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en12_END (5)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr12_START (6)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr12_END (6)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en12_START (7)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en12_END (7)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en13_START (8)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en13_END (8)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en13_START (9)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en13_END (9)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en13_START (10)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en13_END (10)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en13_START (11)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en13_END (11)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en13_START (12)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en13_END (12)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en13_START (13)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en13_END (13)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr13_START (14)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr13_END (14)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en13_START (15)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en13_END (15)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en14_START (16)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en14_END (16)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en14_START (17)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en14_END (17)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en14_START (18)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en14_END (18)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en14_START (19)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en14_END (19)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en14_START (20)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en14_END (20)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en14_START (21)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en14_END (21)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr14_START (22)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr14_END (22)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en14_START (23)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en14_END (23)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en15_START (24)
#define SOC_ASP_SLIMBUS_P12_INT_EN_act_int_en15_END (24)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en15_START (25)
#define SOC_ASP_SLIMBUS_P12_INT_EN_con_int_en15_END (25)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en15_START (26)
#define SOC_ASP_SLIMBUS_P12_INT_EN_chan_int_en15_END (26)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en15_START (27)
#define SOC_ASP_SLIMBUS_P12_INT_EN_dma_int_en15_END (27)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en15_START (28)
#define SOC_ASP_SLIMBUS_P12_INT_EN_ovf_int_en15_END (28)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en15_START (29)
#define SOC_ASP_SLIMBUS_P12_INT_EN_und_int_en15_END (29)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr15_START (30)
#define SOC_ASP_SLIMBUS_P12_INT_EN_fifo_clr15_END (30)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en15_START (31)
#define SOC_ASP_SLIMBUS_P12_INT_EN_pr_gen_en15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P16_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P20_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P24_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P28_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P32_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P36_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P40_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P44_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P48_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P52_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P56_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
        unsigned int reserved_28: 1;
        unsigned int reserved_29: 1;
        unsigned int reserved_30: 1;
        unsigned int reserved_31: 1;
    } reg;
} SOC_ASP_SLIMBUS_P60_INT_EN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int0 : 1;
        unsigned int con_int0 : 1;
        unsigned int chan_int0 : 1;
        unsigned int dma_int0 : 1;
        unsigned int ovf_int0 : 1;
        unsigned int und_int0 : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int act_int1 : 1;
        unsigned int con_int1 : 1;
        unsigned int chan_int1 : 1;
        unsigned int dma_int1 : 1;
        unsigned int ovf_int1 : 1;
        unsigned int und_int1 : 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int act_int2 : 1;
        unsigned int con_int2 : 1;
        unsigned int chan_int2 : 1;
        unsigned int dma_int2 : 1;
        unsigned int ovf_int2 : 1;
        unsigned int und_int2 : 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int act_int3 : 1;
        unsigned int con_int3 : 1;
        unsigned int chan_int3 : 1;
        unsigned int dma_int3 : 1;
        unsigned int ovf_int3 : 1;
        unsigned int und_int3 : 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
    } reg;
} SOC_ASP_SLIMBUS_P0_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_INT_act_int0_START (0)
#define SOC_ASP_SLIMBUS_P0_INT_act_int0_END (0)
#define SOC_ASP_SLIMBUS_P0_INT_con_int0_START (1)
#define SOC_ASP_SLIMBUS_P0_INT_con_int0_END (1)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int0_START (2)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int0_END (2)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int0_START (3)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int0_END (3)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int0_START (4)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int0_END (4)
#define SOC_ASP_SLIMBUS_P0_INT_und_int0_START (5)
#define SOC_ASP_SLIMBUS_P0_INT_und_int0_END (5)
#define SOC_ASP_SLIMBUS_P0_INT_act_int1_START (8)
#define SOC_ASP_SLIMBUS_P0_INT_act_int1_END (8)
#define SOC_ASP_SLIMBUS_P0_INT_con_int1_START (9)
#define SOC_ASP_SLIMBUS_P0_INT_con_int1_END (9)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int1_START (10)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int1_END (10)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int1_START (11)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int1_END (11)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int1_START (12)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int1_END (12)
#define SOC_ASP_SLIMBUS_P0_INT_und_int1_START (13)
#define SOC_ASP_SLIMBUS_P0_INT_und_int1_END (13)
#define SOC_ASP_SLIMBUS_P0_INT_act_int2_START (16)
#define SOC_ASP_SLIMBUS_P0_INT_act_int2_END (16)
#define SOC_ASP_SLIMBUS_P0_INT_con_int2_START (17)
#define SOC_ASP_SLIMBUS_P0_INT_con_int2_END (17)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int2_START (18)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int2_END (18)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int2_START (19)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int2_END (19)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int2_START (20)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int2_END (20)
#define SOC_ASP_SLIMBUS_P0_INT_und_int2_START (21)
#define SOC_ASP_SLIMBUS_P0_INT_und_int2_END (21)
#define SOC_ASP_SLIMBUS_P0_INT_act_int3_START (24)
#define SOC_ASP_SLIMBUS_P0_INT_act_int3_END (24)
#define SOC_ASP_SLIMBUS_P0_INT_con_int3_START (25)
#define SOC_ASP_SLIMBUS_P0_INT_con_int3_END (25)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int3_START (26)
#define SOC_ASP_SLIMBUS_P0_INT_chan_int3_END (26)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int3_START (27)
#define SOC_ASP_SLIMBUS_P0_INT_dma_int3_END (27)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int3_START (28)
#define SOC_ASP_SLIMBUS_P0_INT_ovf_int3_END (28)
#define SOC_ASP_SLIMBUS_P0_INT_und_int3_START (29)
#define SOC_ASP_SLIMBUS_P0_INT_und_int3_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int4 : 1;
        unsigned int con_int4 : 1;
        unsigned int chan_int4 : 1;
        unsigned int dma_int4 : 1;
        unsigned int ovf_int4 : 1;
        unsigned int und_int4 : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int act_int5 : 1;
        unsigned int con_int5 : 1;
        unsigned int chan_int5 : 1;
        unsigned int dma_int5 : 1;
        unsigned int ovf_int5 : 1;
        unsigned int und_int5 : 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int act_int6 : 1;
        unsigned int con_int6 : 1;
        unsigned int chan_int6 : 1;
        unsigned int dma_int6 : 1;
        unsigned int ovf_int6 : 1;
        unsigned int und_int6 : 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int act_int7 : 1;
        unsigned int con_int7 : 1;
        unsigned int chan_int7 : 1;
        unsigned int dma_int7 : 1;
        unsigned int ovf_int7 : 1;
        unsigned int und_int7 : 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
    } reg;
} SOC_ASP_SLIMBUS_P4_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_INT_act_int4_START (0)
#define SOC_ASP_SLIMBUS_P4_INT_act_int4_END (0)
#define SOC_ASP_SLIMBUS_P4_INT_con_int4_START (1)
#define SOC_ASP_SLIMBUS_P4_INT_con_int4_END (1)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int4_START (2)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int4_END (2)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int4_START (3)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int4_END (3)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int4_START (4)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int4_END (4)
#define SOC_ASP_SLIMBUS_P4_INT_und_int4_START (5)
#define SOC_ASP_SLIMBUS_P4_INT_und_int4_END (5)
#define SOC_ASP_SLIMBUS_P4_INT_act_int5_START (8)
#define SOC_ASP_SLIMBUS_P4_INT_act_int5_END (8)
#define SOC_ASP_SLIMBUS_P4_INT_con_int5_START (9)
#define SOC_ASP_SLIMBUS_P4_INT_con_int5_END (9)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int5_START (10)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int5_END (10)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int5_START (11)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int5_END (11)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int5_START (12)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int5_END (12)
#define SOC_ASP_SLIMBUS_P4_INT_und_int5_START (13)
#define SOC_ASP_SLIMBUS_P4_INT_und_int5_END (13)
#define SOC_ASP_SLIMBUS_P4_INT_act_int6_START (16)
#define SOC_ASP_SLIMBUS_P4_INT_act_int6_END (16)
#define SOC_ASP_SLIMBUS_P4_INT_con_int6_START (17)
#define SOC_ASP_SLIMBUS_P4_INT_con_int6_END (17)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int6_START (18)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int6_END (18)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int6_START (19)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int6_END (19)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int6_START (20)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int6_END (20)
#define SOC_ASP_SLIMBUS_P4_INT_und_int6_START (21)
#define SOC_ASP_SLIMBUS_P4_INT_und_int6_END (21)
#define SOC_ASP_SLIMBUS_P4_INT_act_int7_START (24)
#define SOC_ASP_SLIMBUS_P4_INT_act_int7_END (24)
#define SOC_ASP_SLIMBUS_P4_INT_con_int7_START (25)
#define SOC_ASP_SLIMBUS_P4_INT_con_int7_END (25)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int7_START (26)
#define SOC_ASP_SLIMBUS_P4_INT_chan_int7_END (26)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int7_START (27)
#define SOC_ASP_SLIMBUS_P4_INT_dma_int7_END (27)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int7_START (28)
#define SOC_ASP_SLIMBUS_P4_INT_ovf_int7_END (28)
#define SOC_ASP_SLIMBUS_P4_INT_und_int7_START (29)
#define SOC_ASP_SLIMBUS_P4_INT_und_int7_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int8 : 1;
        unsigned int con_int8 : 1;
        unsigned int chan_int8 : 1;
        unsigned int dma_int8 : 1;
        unsigned int ovf_int8 : 1;
        unsigned int und_int8 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int9 : 1;
        unsigned int con_int9 : 1;
        unsigned int chan_int9 : 1;
        unsigned int dma_int9 : 1;
        unsigned int ovf_int9 : 1;
        unsigned int und_int9 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int10 : 1;
        unsigned int con_int10 : 1;
        unsigned int chan_int10 : 1;
        unsigned int dma_int10 : 1;
        unsigned int ovf_int10 : 1;
        unsigned int und_int10 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int11 : 1;
        unsigned int con_int11 : 1;
        unsigned int chan_int11 : 1;
        unsigned int dma_int11 : 1;
        unsigned int ovf_int11 : 1;
        unsigned int und_int11 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P8_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_INT_act_int8_START (0)
#define SOC_ASP_SLIMBUS_P8_INT_act_int8_END (0)
#define SOC_ASP_SLIMBUS_P8_INT_con_int8_START (1)
#define SOC_ASP_SLIMBUS_P8_INT_con_int8_END (1)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int8_START (2)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int8_END (2)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int8_START (3)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int8_END (3)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int8_START (4)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int8_END (4)
#define SOC_ASP_SLIMBUS_P8_INT_und_int8_START (5)
#define SOC_ASP_SLIMBUS_P8_INT_und_int8_END (5)
#define SOC_ASP_SLIMBUS_P8_INT_act_int9_START (8)
#define SOC_ASP_SLIMBUS_P8_INT_act_int9_END (8)
#define SOC_ASP_SLIMBUS_P8_INT_con_int9_START (9)
#define SOC_ASP_SLIMBUS_P8_INT_con_int9_END (9)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int9_START (10)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int9_END (10)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int9_START (11)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int9_END (11)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int9_START (12)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int9_END (12)
#define SOC_ASP_SLIMBUS_P8_INT_und_int9_START (13)
#define SOC_ASP_SLIMBUS_P8_INT_und_int9_END (13)
#define SOC_ASP_SLIMBUS_P8_INT_act_int10_START (16)
#define SOC_ASP_SLIMBUS_P8_INT_act_int10_END (16)
#define SOC_ASP_SLIMBUS_P8_INT_con_int10_START (17)
#define SOC_ASP_SLIMBUS_P8_INT_con_int10_END (17)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int10_START (18)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int10_END (18)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int10_START (19)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int10_END (19)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int10_START (20)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int10_END (20)
#define SOC_ASP_SLIMBUS_P8_INT_und_int10_START (21)
#define SOC_ASP_SLIMBUS_P8_INT_und_int10_END (21)
#define SOC_ASP_SLIMBUS_P8_INT_act_int11_START (24)
#define SOC_ASP_SLIMBUS_P8_INT_act_int11_END (24)
#define SOC_ASP_SLIMBUS_P8_INT_con_int11_START (25)
#define SOC_ASP_SLIMBUS_P8_INT_con_int11_END (25)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int11_START (26)
#define SOC_ASP_SLIMBUS_P8_INT_chan_int11_END (26)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int11_START (27)
#define SOC_ASP_SLIMBUS_P8_INT_dma_int11_END (27)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int11_START (28)
#define SOC_ASP_SLIMBUS_P8_INT_ovf_int11_END (28)
#define SOC_ASP_SLIMBUS_P8_INT_und_int11_START (29)
#define SOC_ASP_SLIMBUS_P8_INT_und_int11_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int12 : 1;
        unsigned int con_int12 : 1;
        unsigned int chan_int12 : 1;
        unsigned int dma_int12 : 1;
        unsigned int ovf_int12 : 1;
        unsigned int und_int12 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int13 : 1;
        unsigned int con_int13 : 1;
        unsigned int chan_int13 : 1;
        unsigned int dma_int13 : 1;
        unsigned int ovf_int13 : 1;
        unsigned int und_int13 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int14 : 1;
        unsigned int con_int14 : 1;
        unsigned int chan_int14 : 1;
        unsigned int dma_int14 : 1;
        unsigned int ovf_int14 : 1;
        unsigned int und_int14 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int15 : 1;
        unsigned int con_int15 : 1;
        unsigned int chan_int15 : 1;
        unsigned int dma_int15 : 1;
        unsigned int ovf_int15 : 1;
        unsigned int und_int15 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P12_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_INT_act_int12_START (0)
#define SOC_ASP_SLIMBUS_P12_INT_act_int12_END (0)
#define SOC_ASP_SLIMBUS_P12_INT_con_int12_START (1)
#define SOC_ASP_SLIMBUS_P12_INT_con_int12_END (1)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int12_START (2)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int12_END (2)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int12_START (3)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int12_END (3)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int12_START (4)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int12_END (4)
#define SOC_ASP_SLIMBUS_P12_INT_und_int12_START (5)
#define SOC_ASP_SLIMBUS_P12_INT_und_int12_END (5)
#define SOC_ASP_SLIMBUS_P12_INT_act_int13_START (8)
#define SOC_ASP_SLIMBUS_P12_INT_act_int13_END (8)
#define SOC_ASP_SLIMBUS_P12_INT_con_int13_START (9)
#define SOC_ASP_SLIMBUS_P12_INT_con_int13_END (9)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int13_START (10)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int13_END (10)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int13_START (11)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int13_END (11)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int13_START (12)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int13_END (12)
#define SOC_ASP_SLIMBUS_P12_INT_und_int13_START (13)
#define SOC_ASP_SLIMBUS_P12_INT_und_int13_END (13)
#define SOC_ASP_SLIMBUS_P12_INT_act_int14_START (16)
#define SOC_ASP_SLIMBUS_P12_INT_act_int14_END (16)
#define SOC_ASP_SLIMBUS_P12_INT_con_int14_START (17)
#define SOC_ASP_SLIMBUS_P12_INT_con_int14_END (17)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int14_START (18)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int14_END (18)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int14_START (19)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int14_END (19)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int14_START (20)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int14_END (20)
#define SOC_ASP_SLIMBUS_P12_INT_und_int14_START (21)
#define SOC_ASP_SLIMBUS_P12_INT_und_int14_END (21)
#define SOC_ASP_SLIMBUS_P12_INT_act_int15_START (24)
#define SOC_ASP_SLIMBUS_P12_INT_act_int15_END (24)
#define SOC_ASP_SLIMBUS_P12_INT_con_int15_START (25)
#define SOC_ASP_SLIMBUS_P12_INT_con_int15_END (25)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int15_START (26)
#define SOC_ASP_SLIMBUS_P12_INT_chan_int15_END (26)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int15_START (27)
#define SOC_ASP_SLIMBUS_P12_INT_dma_int15_END (27)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int15_START (28)
#define SOC_ASP_SLIMBUS_P12_INT_ovf_int15_END (28)
#define SOC_ASP_SLIMBUS_P12_INT_und_int15_START (29)
#define SOC_ASP_SLIMBUS_P12_INT_und_int15_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int16 : 1;
        unsigned int con_int16 : 1;
        unsigned int chan_int16 : 1;
        unsigned int dma_int16 : 1;
        unsigned int ovf_int16 : 1;
        unsigned int und_int16 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int17 : 1;
        unsigned int con_int17 : 1;
        unsigned int chan_int17 : 1;
        unsigned int dma_int17 : 1;
        unsigned int ovf_int17 : 1;
        unsigned int und_int17 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int18 : 1;
        unsigned int con_int18 : 1;
        unsigned int chan_int18 : 1;
        unsigned int dma_int18 : 1;
        unsigned int ovf_int18 : 1;
        unsigned int und_int18 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int19 : 1;
        unsigned int con_int19 : 1;
        unsigned int chan_int19 : 1;
        unsigned int dma_int19 : 1;
        unsigned int ovf_int19 : 1;
        unsigned int und_int19 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P16_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_INT_act_int16_START (0)
#define SOC_ASP_SLIMBUS_P16_INT_act_int16_END (0)
#define SOC_ASP_SLIMBUS_P16_INT_con_int16_START (1)
#define SOC_ASP_SLIMBUS_P16_INT_con_int16_END (1)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int16_START (2)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int16_END (2)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int16_START (3)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int16_END (3)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int16_START (4)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int16_END (4)
#define SOC_ASP_SLIMBUS_P16_INT_und_int16_START (5)
#define SOC_ASP_SLIMBUS_P16_INT_und_int16_END (5)
#define SOC_ASP_SLIMBUS_P16_INT_act_int17_START (8)
#define SOC_ASP_SLIMBUS_P16_INT_act_int17_END (8)
#define SOC_ASP_SLIMBUS_P16_INT_con_int17_START (9)
#define SOC_ASP_SLIMBUS_P16_INT_con_int17_END (9)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int17_START (10)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int17_END (10)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int17_START (11)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int17_END (11)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int17_START (12)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int17_END (12)
#define SOC_ASP_SLIMBUS_P16_INT_und_int17_START (13)
#define SOC_ASP_SLIMBUS_P16_INT_und_int17_END (13)
#define SOC_ASP_SLIMBUS_P16_INT_act_int18_START (16)
#define SOC_ASP_SLIMBUS_P16_INT_act_int18_END (16)
#define SOC_ASP_SLIMBUS_P16_INT_con_int18_START (17)
#define SOC_ASP_SLIMBUS_P16_INT_con_int18_END (17)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int18_START (18)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int18_END (18)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int18_START (19)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int18_END (19)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int18_START (20)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int18_END (20)
#define SOC_ASP_SLIMBUS_P16_INT_und_int18_START (21)
#define SOC_ASP_SLIMBUS_P16_INT_und_int18_END (21)
#define SOC_ASP_SLIMBUS_P16_INT_act_int19_START (24)
#define SOC_ASP_SLIMBUS_P16_INT_act_int19_END (24)
#define SOC_ASP_SLIMBUS_P16_INT_con_int19_START (25)
#define SOC_ASP_SLIMBUS_P16_INT_con_int19_END (25)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int19_START (26)
#define SOC_ASP_SLIMBUS_P16_INT_chan_int19_END (26)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int19_START (27)
#define SOC_ASP_SLIMBUS_P16_INT_dma_int19_END (27)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int19_START (28)
#define SOC_ASP_SLIMBUS_P16_INT_ovf_int19_END (28)
#define SOC_ASP_SLIMBUS_P16_INT_und_int19_START (29)
#define SOC_ASP_SLIMBUS_P16_INT_und_int19_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int20 : 1;
        unsigned int con_int20 : 1;
        unsigned int chan_int20 : 1;
        unsigned int dma_int20 : 1;
        unsigned int ovf_int20 : 1;
        unsigned int und_int20 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int21 : 1;
        unsigned int con_int21 : 1;
        unsigned int chan_int21 : 1;
        unsigned int dma_int21 : 1;
        unsigned int ovf_int21 : 1;
        unsigned int und_int21 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int22 : 1;
        unsigned int con_int22 : 1;
        unsigned int chan_int22 : 1;
        unsigned int dma_int22 : 1;
        unsigned int ovf_int22 : 1;
        unsigned int und_int22 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int23 : 1;
        unsigned int con_int23 : 1;
        unsigned int chan_int23 : 1;
        unsigned int dma_int23 : 1;
        unsigned int ovf_int23 : 1;
        unsigned int und_int23 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P20_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_INT_act_int20_START (0)
#define SOC_ASP_SLIMBUS_P20_INT_act_int20_END (0)
#define SOC_ASP_SLIMBUS_P20_INT_con_int20_START (1)
#define SOC_ASP_SLIMBUS_P20_INT_con_int20_END (1)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int20_START (2)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int20_END (2)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int20_START (3)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int20_END (3)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int20_START (4)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int20_END (4)
#define SOC_ASP_SLIMBUS_P20_INT_und_int20_START (5)
#define SOC_ASP_SLIMBUS_P20_INT_und_int20_END (5)
#define SOC_ASP_SLIMBUS_P20_INT_act_int21_START (8)
#define SOC_ASP_SLIMBUS_P20_INT_act_int21_END (8)
#define SOC_ASP_SLIMBUS_P20_INT_con_int21_START (9)
#define SOC_ASP_SLIMBUS_P20_INT_con_int21_END (9)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int21_START (10)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int21_END (10)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int21_START (11)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int21_END (11)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int21_START (12)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int21_END (12)
#define SOC_ASP_SLIMBUS_P20_INT_und_int21_START (13)
#define SOC_ASP_SLIMBUS_P20_INT_und_int21_END (13)
#define SOC_ASP_SLIMBUS_P20_INT_act_int22_START (16)
#define SOC_ASP_SLIMBUS_P20_INT_act_int22_END (16)
#define SOC_ASP_SLIMBUS_P20_INT_con_int22_START (17)
#define SOC_ASP_SLIMBUS_P20_INT_con_int22_END (17)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int22_START (18)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int22_END (18)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int22_START (19)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int22_END (19)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int22_START (20)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int22_END (20)
#define SOC_ASP_SLIMBUS_P20_INT_und_int22_START (21)
#define SOC_ASP_SLIMBUS_P20_INT_und_int22_END (21)
#define SOC_ASP_SLIMBUS_P20_INT_act_int23_START (24)
#define SOC_ASP_SLIMBUS_P20_INT_act_int23_END (24)
#define SOC_ASP_SLIMBUS_P20_INT_con_int23_START (25)
#define SOC_ASP_SLIMBUS_P20_INT_con_int23_END (25)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int23_START (26)
#define SOC_ASP_SLIMBUS_P20_INT_chan_int23_END (26)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int23_START (27)
#define SOC_ASP_SLIMBUS_P20_INT_dma_int23_END (27)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int23_START (28)
#define SOC_ASP_SLIMBUS_P20_INT_ovf_int23_END (28)
#define SOC_ASP_SLIMBUS_P20_INT_und_int23_START (29)
#define SOC_ASP_SLIMBUS_P20_INT_und_int23_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int24 : 1;
        unsigned int con_int24 : 1;
        unsigned int chan_int24 : 1;
        unsigned int dma_int24 : 1;
        unsigned int ovf_int24 : 1;
        unsigned int und_int24 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int25 : 1;
        unsigned int con_int25 : 1;
        unsigned int chan_int25 : 1;
        unsigned int dma_int25 : 1;
        unsigned int ovf_int25 : 1;
        unsigned int und_int25 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int26 : 1;
        unsigned int con_int26 : 1;
        unsigned int chan_int26 : 1;
        unsigned int dma_int26 : 1;
        unsigned int ovf_int26 : 1;
        unsigned int und_int26 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int27 : 1;
        unsigned int con_int27 : 1;
        unsigned int chan_int27 : 1;
        unsigned int dma_int27 : 1;
        unsigned int ovf_int27 : 1;
        unsigned int und_int27 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P24_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_INT_act_int24_START (0)
#define SOC_ASP_SLIMBUS_P24_INT_act_int24_END (0)
#define SOC_ASP_SLIMBUS_P24_INT_con_int24_START (1)
#define SOC_ASP_SLIMBUS_P24_INT_con_int24_END (1)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int24_START (2)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int24_END (2)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int24_START (3)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int24_END (3)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int24_START (4)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int24_END (4)
#define SOC_ASP_SLIMBUS_P24_INT_und_int24_START (5)
#define SOC_ASP_SLIMBUS_P24_INT_und_int24_END (5)
#define SOC_ASP_SLIMBUS_P24_INT_act_int25_START (8)
#define SOC_ASP_SLIMBUS_P24_INT_act_int25_END (8)
#define SOC_ASP_SLIMBUS_P24_INT_con_int25_START (9)
#define SOC_ASP_SLIMBUS_P24_INT_con_int25_END (9)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int25_START (10)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int25_END (10)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int25_START (11)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int25_END (11)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int25_START (12)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int25_END (12)
#define SOC_ASP_SLIMBUS_P24_INT_und_int25_START (13)
#define SOC_ASP_SLIMBUS_P24_INT_und_int25_END (13)
#define SOC_ASP_SLIMBUS_P24_INT_act_int26_START (16)
#define SOC_ASP_SLIMBUS_P24_INT_act_int26_END (16)
#define SOC_ASP_SLIMBUS_P24_INT_con_int26_START (17)
#define SOC_ASP_SLIMBUS_P24_INT_con_int26_END (17)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int26_START (18)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int26_END (18)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int26_START (19)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int26_END (19)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int26_START (20)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int26_END (20)
#define SOC_ASP_SLIMBUS_P24_INT_und_int26_START (21)
#define SOC_ASP_SLIMBUS_P24_INT_und_int26_END (21)
#define SOC_ASP_SLIMBUS_P24_INT_act_int27_START (24)
#define SOC_ASP_SLIMBUS_P24_INT_act_int27_END (24)
#define SOC_ASP_SLIMBUS_P24_INT_con_int27_START (25)
#define SOC_ASP_SLIMBUS_P24_INT_con_int27_END (25)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int27_START (26)
#define SOC_ASP_SLIMBUS_P24_INT_chan_int27_END (26)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int27_START (27)
#define SOC_ASP_SLIMBUS_P24_INT_dma_int27_END (27)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int27_START (28)
#define SOC_ASP_SLIMBUS_P24_INT_ovf_int27_END (28)
#define SOC_ASP_SLIMBUS_P24_INT_und_int27_START (29)
#define SOC_ASP_SLIMBUS_P24_INT_und_int27_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int28 : 1;
        unsigned int con_int28 : 1;
        unsigned int chan_int28 : 1;
        unsigned int dma_int28 : 1;
        unsigned int ovf_int28 : 1;
        unsigned int und_int28 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int29 : 1;
        unsigned int con_int29 : 1;
        unsigned int chan_int29 : 1;
        unsigned int dma_int29 : 1;
        unsigned int ovf_int29 : 1;
        unsigned int und_int29 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int30 : 1;
        unsigned int con_int30 : 1;
        unsigned int chan_int30 : 1;
        unsigned int dma_int30 : 1;
        unsigned int ovf_int30 : 1;
        unsigned int und_int30 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int31 : 1;
        unsigned int con_int31 : 1;
        unsigned int chan_int31 : 1;
        unsigned int dma_int31 : 1;
        unsigned int ovf_int31 : 1;
        unsigned int und_int31 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P28_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_INT_act_int28_START (0)
#define SOC_ASP_SLIMBUS_P28_INT_act_int28_END (0)
#define SOC_ASP_SLIMBUS_P28_INT_con_int28_START (1)
#define SOC_ASP_SLIMBUS_P28_INT_con_int28_END (1)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int28_START (2)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int28_END (2)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int28_START (3)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int28_END (3)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int28_START (4)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int28_END (4)
#define SOC_ASP_SLIMBUS_P28_INT_und_int28_START (5)
#define SOC_ASP_SLIMBUS_P28_INT_und_int28_END (5)
#define SOC_ASP_SLIMBUS_P28_INT_act_int29_START (8)
#define SOC_ASP_SLIMBUS_P28_INT_act_int29_END (8)
#define SOC_ASP_SLIMBUS_P28_INT_con_int29_START (9)
#define SOC_ASP_SLIMBUS_P28_INT_con_int29_END (9)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int29_START (10)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int29_END (10)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int29_START (11)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int29_END (11)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int29_START (12)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int29_END (12)
#define SOC_ASP_SLIMBUS_P28_INT_und_int29_START (13)
#define SOC_ASP_SLIMBUS_P28_INT_und_int29_END (13)
#define SOC_ASP_SLIMBUS_P28_INT_act_int30_START (16)
#define SOC_ASP_SLIMBUS_P28_INT_act_int30_END (16)
#define SOC_ASP_SLIMBUS_P28_INT_con_int30_START (17)
#define SOC_ASP_SLIMBUS_P28_INT_con_int30_END (17)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int30_START (18)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int30_END (18)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int30_START (19)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int30_END (19)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int30_START (20)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int30_END (20)
#define SOC_ASP_SLIMBUS_P28_INT_und_int30_START (21)
#define SOC_ASP_SLIMBUS_P28_INT_und_int30_END (21)
#define SOC_ASP_SLIMBUS_P28_INT_act_int31_START (24)
#define SOC_ASP_SLIMBUS_P28_INT_act_int31_END (24)
#define SOC_ASP_SLIMBUS_P28_INT_con_int31_START (25)
#define SOC_ASP_SLIMBUS_P28_INT_con_int31_END (25)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int31_START (26)
#define SOC_ASP_SLIMBUS_P28_INT_chan_int31_END (26)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int31_START (27)
#define SOC_ASP_SLIMBUS_P28_INT_dma_int31_END (27)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int31_START (28)
#define SOC_ASP_SLIMBUS_P28_INT_ovf_int31_END (28)
#define SOC_ASP_SLIMBUS_P28_INT_und_int31_START (29)
#define SOC_ASP_SLIMBUS_P28_INT_und_int31_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int32 : 1;
        unsigned int con_int32 : 1;
        unsigned int chan_int32 : 1;
        unsigned int dma_int32 : 1;
        unsigned int ovf_int32 : 1;
        unsigned int und_int32 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int33 : 1;
        unsigned int con_int33 : 1;
        unsigned int chan_int33 : 1;
        unsigned int dma_int33 : 1;
        unsigned int ovf_int33 : 1;
        unsigned int und_int33 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int34 : 1;
        unsigned int con_int34 : 1;
        unsigned int chan_int34 : 1;
        unsigned int dma_int34 : 1;
        unsigned int ovf_int34 : 1;
        unsigned int und_int34 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int35 : 1;
        unsigned int con_int35 : 1;
        unsigned int chan_int35 : 1;
        unsigned int dma_int35 : 1;
        unsigned int ovf_int35 : 1;
        unsigned int und_int35 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P32_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_INT_act_int32_START (0)
#define SOC_ASP_SLIMBUS_P32_INT_act_int32_END (0)
#define SOC_ASP_SLIMBUS_P32_INT_con_int32_START (1)
#define SOC_ASP_SLIMBUS_P32_INT_con_int32_END (1)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int32_START (2)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int32_END (2)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int32_START (3)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int32_END (3)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int32_START (4)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int32_END (4)
#define SOC_ASP_SLIMBUS_P32_INT_und_int32_START (5)
#define SOC_ASP_SLIMBUS_P32_INT_und_int32_END (5)
#define SOC_ASP_SLIMBUS_P32_INT_act_int33_START (8)
#define SOC_ASP_SLIMBUS_P32_INT_act_int33_END (8)
#define SOC_ASP_SLIMBUS_P32_INT_con_int33_START (9)
#define SOC_ASP_SLIMBUS_P32_INT_con_int33_END (9)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int33_START (10)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int33_END (10)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int33_START (11)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int33_END (11)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int33_START (12)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int33_END (12)
#define SOC_ASP_SLIMBUS_P32_INT_und_int33_START (13)
#define SOC_ASP_SLIMBUS_P32_INT_und_int33_END (13)
#define SOC_ASP_SLIMBUS_P32_INT_act_int34_START (16)
#define SOC_ASP_SLIMBUS_P32_INT_act_int34_END (16)
#define SOC_ASP_SLIMBUS_P32_INT_con_int34_START (17)
#define SOC_ASP_SLIMBUS_P32_INT_con_int34_END (17)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int34_START (18)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int34_END (18)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int34_START (19)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int34_END (19)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int34_START (20)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int34_END (20)
#define SOC_ASP_SLIMBUS_P32_INT_und_int34_START (21)
#define SOC_ASP_SLIMBUS_P32_INT_und_int34_END (21)
#define SOC_ASP_SLIMBUS_P32_INT_act_int35_START (24)
#define SOC_ASP_SLIMBUS_P32_INT_act_int35_END (24)
#define SOC_ASP_SLIMBUS_P32_INT_con_int35_START (25)
#define SOC_ASP_SLIMBUS_P32_INT_con_int35_END (25)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int35_START (26)
#define SOC_ASP_SLIMBUS_P32_INT_chan_int35_END (26)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int35_START (27)
#define SOC_ASP_SLIMBUS_P32_INT_dma_int35_END (27)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int35_START (28)
#define SOC_ASP_SLIMBUS_P32_INT_ovf_int35_END (28)
#define SOC_ASP_SLIMBUS_P32_INT_und_int35_START (29)
#define SOC_ASP_SLIMBUS_P32_INT_und_int35_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int36 : 1;
        unsigned int con_int36 : 1;
        unsigned int chan_int36 : 1;
        unsigned int dma_int36 : 1;
        unsigned int ovf_int36 : 1;
        unsigned int und_int36 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int37 : 1;
        unsigned int con_int37 : 1;
        unsigned int chan_int37 : 1;
        unsigned int dma_int37 : 1;
        unsigned int ovf_int37 : 1;
        unsigned int und_int37 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int38 : 1;
        unsigned int con_int38 : 1;
        unsigned int chan_int38 : 1;
        unsigned int dma_int38 : 1;
        unsigned int ovf_int38 : 1;
        unsigned int und_int38 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int39 : 1;
        unsigned int con_int39 : 1;
        unsigned int chan_int39 : 1;
        unsigned int dma_int39 : 1;
        unsigned int ovf_int39 : 1;
        unsigned int und_int39 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P36_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_INT_act_int36_START (0)
#define SOC_ASP_SLIMBUS_P36_INT_act_int36_END (0)
#define SOC_ASP_SLIMBUS_P36_INT_con_int36_START (1)
#define SOC_ASP_SLIMBUS_P36_INT_con_int36_END (1)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int36_START (2)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int36_END (2)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int36_START (3)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int36_END (3)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int36_START (4)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int36_END (4)
#define SOC_ASP_SLIMBUS_P36_INT_und_int36_START (5)
#define SOC_ASP_SLIMBUS_P36_INT_und_int36_END (5)
#define SOC_ASP_SLIMBUS_P36_INT_act_int37_START (8)
#define SOC_ASP_SLIMBUS_P36_INT_act_int37_END (8)
#define SOC_ASP_SLIMBUS_P36_INT_con_int37_START (9)
#define SOC_ASP_SLIMBUS_P36_INT_con_int37_END (9)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int37_START (10)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int37_END (10)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int37_START (11)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int37_END (11)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int37_START (12)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int37_END (12)
#define SOC_ASP_SLIMBUS_P36_INT_und_int37_START (13)
#define SOC_ASP_SLIMBUS_P36_INT_und_int37_END (13)
#define SOC_ASP_SLIMBUS_P36_INT_act_int38_START (16)
#define SOC_ASP_SLIMBUS_P36_INT_act_int38_END (16)
#define SOC_ASP_SLIMBUS_P36_INT_con_int38_START (17)
#define SOC_ASP_SLIMBUS_P36_INT_con_int38_END (17)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int38_START (18)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int38_END (18)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int38_START (19)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int38_END (19)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int38_START (20)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int38_END (20)
#define SOC_ASP_SLIMBUS_P36_INT_und_int38_START (21)
#define SOC_ASP_SLIMBUS_P36_INT_und_int38_END (21)
#define SOC_ASP_SLIMBUS_P36_INT_act_int39_START (24)
#define SOC_ASP_SLIMBUS_P36_INT_act_int39_END (24)
#define SOC_ASP_SLIMBUS_P36_INT_con_int39_START (25)
#define SOC_ASP_SLIMBUS_P36_INT_con_int39_END (25)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int39_START (26)
#define SOC_ASP_SLIMBUS_P36_INT_chan_int39_END (26)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int39_START (27)
#define SOC_ASP_SLIMBUS_P36_INT_dma_int39_END (27)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int39_START (28)
#define SOC_ASP_SLIMBUS_P36_INT_ovf_int39_END (28)
#define SOC_ASP_SLIMBUS_P36_INT_und_int39_START (29)
#define SOC_ASP_SLIMBUS_P36_INT_und_int39_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int40 : 1;
        unsigned int con_int40 : 1;
        unsigned int chan_int40 : 1;
        unsigned int dma_int40 : 1;
        unsigned int ovf_int40 : 1;
        unsigned int und_int40 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int41 : 1;
        unsigned int con_int41 : 1;
        unsigned int chan_int41 : 1;
        unsigned int dma_int41 : 1;
        unsigned int ovf_int41 : 1;
        unsigned int und_int41 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int42 : 1;
        unsigned int con_int42 : 1;
        unsigned int chan_int42 : 1;
        unsigned int dma_int42 : 1;
        unsigned int ovf_int42 : 1;
        unsigned int und_int42 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int43 : 1;
        unsigned int con_int43 : 1;
        unsigned int chan_int43 : 1;
        unsigned int dma_int43 : 1;
        unsigned int ovf_int43 : 1;
        unsigned int und_int43 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P40_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_INT_act_int40_START (0)
#define SOC_ASP_SLIMBUS_P40_INT_act_int40_END (0)
#define SOC_ASP_SLIMBUS_P40_INT_con_int40_START (1)
#define SOC_ASP_SLIMBUS_P40_INT_con_int40_END (1)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int40_START (2)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int40_END (2)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int40_START (3)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int40_END (3)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int40_START (4)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int40_END (4)
#define SOC_ASP_SLIMBUS_P40_INT_und_int40_START (5)
#define SOC_ASP_SLIMBUS_P40_INT_und_int40_END (5)
#define SOC_ASP_SLIMBUS_P40_INT_act_int41_START (8)
#define SOC_ASP_SLIMBUS_P40_INT_act_int41_END (8)
#define SOC_ASP_SLIMBUS_P40_INT_con_int41_START (9)
#define SOC_ASP_SLIMBUS_P40_INT_con_int41_END (9)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int41_START (10)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int41_END (10)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int41_START (11)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int41_END (11)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int41_START (12)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int41_END (12)
#define SOC_ASP_SLIMBUS_P40_INT_und_int41_START (13)
#define SOC_ASP_SLIMBUS_P40_INT_und_int41_END (13)
#define SOC_ASP_SLIMBUS_P40_INT_act_int42_START (16)
#define SOC_ASP_SLIMBUS_P40_INT_act_int42_END (16)
#define SOC_ASP_SLIMBUS_P40_INT_con_int42_START (17)
#define SOC_ASP_SLIMBUS_P40_INT_con_int42_END (17)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int42_START (18)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int42_END (18)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int42_START (19)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int42_END (19)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int42_START (20)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int42_END (20)
#define SOC_ASP_SLIMBUS_P40_INT_und_int42_START (21)
#define SOC_ASP_SLIMBUS_P40_INT_und_int42_END (21)
#define SOC_ASP_SLIMBUS_P40_INT_act_int43_START (24)
#define SOC_ASP_SLIMBUS_P40_INT_act_int43_END (24)
#define SOC_ASP_SLIMBUS_P40_INT_con_int43_START (25)
#define SOC_ASP_SLIMBUS_P40_INT_con_int43_END (25)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int43_START (26)
#define SOC_ASP_SLIMBUS_P40_INT_chan_int43_END (26)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int43_START (27)
#define SOC_ASP_SLIMBUS_P40_INT_dma_int43_END (27)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int43_START (28)
#define SOC_ASP_SLIMBUS_P40_INT_ovf_int43_END (28)
#define SOC_ASP_SLIMBUS_P40_INT_und_int43_START (29)
#define SOC_ASP_SLIMBUS_P40_INT_und_int43_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int44 : 1;
        unsigned int con_int44 : 1;
        unsigned int chan_int44 : 1;
        unsigned int dma_int44 : 1;
        unsigned int ovf_int44 : 1;
        unsigned int und_int44 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int45 : 1;
        unsigned int con_int45 : 1;
        unsigned int chan_int45 : 1;
        unsigned int dma_int45 : 1;
        unsigned int ovf_int45 : 1;
        unsigned int und_int45 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int46 : 1;
        unsigned int con_int46 : 1;
        unsigned int chan_int46 : 1;
        unsigned int dma_int46 : 1;
        unsigned int ovf_int46 : 1;
        unsigned int und_int46 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int47 : 1;
        unsigned int con_int47 : 1;
        unsigned int chan_int47 : 1;
        unsigned int dma_int47 : 1;
        unsigned int ovf_int47 : 1;
        unsigned int und_int47 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P44_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_INT_act_int44_START (0)
#define SOC_ASP_SLIMBUS_P44_INT_act_int44_END (0)
#define SOC_ASP_SLIMBUS_P44_INT_con_int44_START (1)
#define SOC_ASP_SLIMBUS_P44_INT_con_int44_END (1)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int44_START (2)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int44_END (2)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int44_START (3)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int44_END (3)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int44_START (4)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int44_END (4)
#define SOC_ASP_SLIMBUS_P44_INT_und_int44_START (5)
#define SOC_ASP_SLIMBUS_P44_INT_und_int44_END (5)
#define SOC_ASP_SLIMBUS_P44_INT_act_int45_START (8)
#define SOC_ASP_SLIMBUS_P44_INT_act_int45_END (8)
#define SOC_ASP_SLIMBUS_P44_INT_con_int45_START (9)
#define SOC_ASP_SLIMBUS_P44_INT_con_int45_END (9)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int45_START (10)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int45_END (10)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int45_START (11)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int45_END (11)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int45_START (12)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int45_END (12)
#define SOC_ASP_SLIMBUS_P44_INT_und_int45_START (13)
#define SOC_ASP_SLIMBUS_P44_INT_und_int45_END (13)
#define SOC_ASP_SLIMBUS_P44_INT_act_int46_START (16)
#define SOC_ASP_SLIMBUS_P44_INT_act_int46_END (16)
#define SOC_ASP_SLIMBUS_P44_INT_con_int46_START (17)
#define SOC_ASP_SLIMBUS_P44_INT_con_int46_END (17)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int46_START (18)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int46_END (18)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int46_START (19)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int46_END (19)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int46_START (20)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int46_END (20)
#define SOC_ASP_SLIMBUS_P44_INT_und_int46_START (21)
#define SOC_ASP_SLIMBUS_P44_INT_und_int46_END (21)
#define SOC_ASP_SLIMBUS_P44_INT_act_int47_START (24)
#define SOC_ASP_SLIMBUS_P44_INT_act_int47_END (24)
#define SOC_ASP_SLIMBUS_P44_INT_con_int47_START (25)
#define SOC_ASP_SLIMBUS_P44_INT_con_int47_END (25)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int47_START (26)
#define SOC_ASP_SLIMBUS_P44_INT_chan_int47_END (26)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int47_START (27)
#define SOC_ASP_SLIMBUS_P44_INT_dma_int47_END (27)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int47_START (28)
#define SOC_ASP_SLIMBUS_P44_INT_ovf_int47_END (28)
#define SOC_ASP_SLIMBUS_P44_INT_und_int47_START (29)
#define SOC_ASP_SLIMBUS_P44_INT_und_int47_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int48 : 1;
        unsigned int con_int48 : 1;
        unsigned int chan_int48 : 1;
        unsigned int dma_int48 : 1;
        unsigned int ovf_int48 : 1;
        unsigned int und_int48 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int49 : 1;
        unsigned int con_int49 : 1;
        unsigned int chan_int49 : 1;
        unsigned int dma_int49 : 1;
        unsigned int ovf_int49 : 1;
        unsigned int und_int49 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int50 : 1;
        unsigned int con_int50 : 1;
        unsigned int chan_int50 : 1;
        unsigned int dma_int50 : 1;
        unsigned int ovf_int50 : 1;
        unsigned int und_int50 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int51 : 1;
        unsigned int con_int51 : 1;
        unsigned int chan_int51 : 1;
        unsigned int dma_int51 : 1;
        unsigned int ovf_int51 : 1;
        unsigned int und_int51 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P48_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_INT_act_int48_START (0)
#define SOC_ASP_SLIMBUS_P48_INT_act_int48_END (0)
#define SOC_ASP_SLIMBUS_P48_INT_con_int48_START (1)
#define SOC_ASP_SLIMBUS_P48_INT_con_int48_END (1)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int48_START (2)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int48_END (2)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int48_START (3)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int48_END (3)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int48_START (4)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int48_END (4)
#define SOC_ASP_SLIMBUS_P48_INT_und_int48_START (5)
#define SOC_ASP_SLIMBUS_P48_INT_und_int48_END (5)
#define SOC_ASP_SLIMBUS_P48_INT_act_int49_START (8)
#define SOC_ASP_SLIMBUS_P48_INT_act_int49_END (8)
#define SOC_ASP_SLIMBUS_P48_INT_con_int49_START (9)
#define SOC_ASP_SLIMBUS_P48_INT_con_int49_END (9)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int49_START (10)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int49_END (10)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int49_START (11)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int49_END (11)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int49_START (12)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int49_END (12)
#define SOC_ASP_SLIMBUS_P48_INT_und_int49_START (13)
#define SOC_ASP_SLIMBUS_P48_INT_und_int49_END (13)
#define SOC_ASP_SLIMBUS_P48_INT_act_int50_START (16)
#define SOC_ASP_SLIMBUS_P48_INT_act_int50_END (16)
#define SOC_ASP_SLIMBUS_P48_INT_con_int50_START (17)
#define SOC_ASP_SLIMBUS_P48_INT_con_int50_END (17)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int50_START (18)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int50_END (18)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int50_START (19)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int50_END (19)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int50_START (20)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int50_END (20)
#define SOC_ASP_SLIMBUS_P48_INT_und_int50_START (21)
#define SOC_ASP_SLIMBUS_P48_INT_und_int50_END (21)
#define SOC_ASP_SLIMBUS_P48_INT_act_int51_START (24)
#define SOC_ASP_SLIMBUS_P48_INT_act_int51_END (24)
#define SOC_ASP_SLIMBUS_P48_INT_con_int51_START (25)
#define SOC_ASP_SLIMBUS_P48_INT_con_int51_END (25)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int51_START (26)
#define SOC_ASP_SLIMBUS_P48_INT_chan_int51_END (26)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int51_START (27)
#define SOC_ASP_SLIMBUS_P48_INT_dma_int51_END (27)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int51_START (28)
#define SOC_ASP_SLIMBUS_P48_INT_ovf_int51_END (28)
#define SOC_ASP_SLIMBUS_P48_INT_und_int51_START (29)
#define SOC_ASP_SLIMBUS_P48_INT_und_int51_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int52 : 1;
        unsigned int con_int52 : 1;
        unsigned int chan_int52 : 1;
        unsigned int dma_int52 : 1;
        unsigned int ovf_int52 : 1;
        unsigned int und_int52 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int53 : 1;
        unsigned int con_int53 : 1;
        unsigned int chan_int53 : 1;
        unsigned int dma_int53 : 1;
        unsigned int ovf_int53 : 1;
        unsigned int und_int53 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int54 : 1;
        unsigned int con_int54 : 1;
        unsigned int chan_int54 : 1;
        unsigned int dma_int54 : 1;
        unsigned int ovf_int54 : 1;
        unsigned int und_int54 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int55 : 1;
        unsigned int con_int55 : 1;
        unsigned int chan_int55 : 1;
        unsigned int dma_int55 : 1;
        unsigned int ovf_int55 : 1;
        unsigned int und_int55 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P52_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_INT_act_int52_START (0)
#define SOC_ASP_SLIMBUS_P52_INT_act_int52_END (0)
#define SOC_ASP_SLIMBUS_P52_INT_con_int52_START (1)
#define SOC_ASP_SLIMBUS_P52_INT_con_int52_END (1)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int52_START (2)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int52_END (2)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int52_START (3)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int52_END (3)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int52_START (4)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int52_END (4)
#define SOC_ASP_SLIMBUS_P52_INT_und_int52_START (5)
#define SOC_ASP_SLIMBUS_P52_INT_und_int52_END (5)
#define SOC_ASP_SLIMBUS_P52_INT_act_int53_START (8)
#define SOC_ASP_SLIMBUS_P52_INT_act_int53_END (8)
#define SOC_ASP_SLIMBUS_P52_INT_con_int53_START (9)
#define SOC_ASP_SLIMBUS_P52_INT_con_int53_END (9)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int53_START (10)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int53_END (10)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int53_START (11)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int53_END (11)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int53_START (12)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int53_END (12)
#define SOC_ASP_SLIMBUS_P52_INT_und_int53_START (13)
#define SOC_ASP_SLIMBUS_P52_INT_und_int53_END (13)
#define SOC_ASP_SLIMBUS_P52_INT_act_int54_START (16)
#define SOC_ASP_SLIMBUS_P52_INT_act_int54_END (16)
#define SOC_ASP_SLIMBUS_P52_INT_con_int54_START (17)
#define SOC_ASP_SLIMBUS_P52_INT_con_int54_END (17)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int54_START (18)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int54_END (18)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int54_START (19)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int54_END (19)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int54_START (20)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int54_END (20)
#define SOC_ASP_SLIMBUS_P52_INT_und_int54_START (21)
#define SOC_ASP_SLIMBUS_P52_INT_und_int54_END (21)
#define SOC_ASP_SLIMBUS_P52_INT_act_int55_START (24)
#define SOC_ASP_SLIMBUS_P52_INT_act_int55_END (24)
#define SOC_ASP_SLIMBUS_P52_INT_con_int55_START (25)
#define SOC_ASP_SLIMBUS_P52_INT_con_int55_END (25)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int55_START (26)
#define SOC_ASP_SLIMBUS_P52_INT_chan_int55_END (26)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int55_START (27)
#define SOC_ASP_SLIMBUS_P52_INT_dma_int55_END (27)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int55_START (28)
#define SOC_ASP_SLIMBUS_P52_INT_ovf_int55_END (28)
#define SOC_ASP_SLIMBUS_P52_INT_und_int55_START (29)
#define SOC_ASP_SLIMBUS_P52_INT_und_int55_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int56 : 1;
        unsigned int con_int56 : 1;
        unsigned int chan_int56 : 1;
        unsigned int dma_int56 : 1;
        unsigned int ovf_int56 : 1;
        unsigned int und_int56 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int57 : 1;
        unsigned int con_int57 : 1;
        unsigned int chan_int57 : 1;
        unsigned int dma_int57 : 1;
        unsigned int ovf_int57 : 1;
        unsigned int und_int57 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int58 : 1;
        unsigned int con_int58 : 1;
        unsigned int chan_int58 : 1;
        unsigned int dma_int58 : 1;
        unsigned int ovf_int58 : 1;
        unsigned int und_int58 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int59 : 1;
        unsigned int con_int59 : 1;
        unsigned int chan_int59 : 1;
        unsigned int dma_int59 : 1;
        unsigned int ovf_int59 : 1;
        unsigned int und_int59 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P56_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_INT_act_int56_START (0)
#define SOC_ASP_SLIMBUS_P56_INT_act_int56_END (0)
#define SOC_ASP_SLIMBUS_P56_INT_con_int56_START (1)
#define SOC_ASP_SLIMBUS_P56_INT_con_int56_END (1)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int56_START (2)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int56_END (2)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int56_START (3)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int56_END (3)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int56_START (4)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int56_END (4)
#define SOC_ASP_SLIMBUS_P56_INT_und_int56_START (5)
#define SOC_ASP_SLIMBUS_P56_INT_und_int56_END (5)
#define SOC_ASP_SLIMBUS_P56_INT_act_int57_START (8)
#define SOC_ASP_SLIMBUS_P56_INT_act_int57_END (8)
#define SOC_ASP_SLIMBUS_P56_INT_con_int57_START (9)
#define SOC_ASP_SLIMBUS_P56_INT_con_int57_END (9)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int57_START (10)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int57_END (10)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int57_START (11)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int57_END (11)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int57_START (12)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int57_END (12)
#define SOC_ASP_SLIMBUS_P56_INT_und_int57_START (13)
#define SOC_ASP_SLIMBUS_P56_INT_und_int57_END (13)
#define SOC_ASP_SLIMBUS_P56_INT_act_int58_START (16)
#define SOC_ASP_SLIMBUS_P56_INT_act_int58_END (16)
#define SOC_ASP_SLIMBUS_P56_INT_con_int58_START (17)
#define SOC_ASP_SLIMBUS_P56_INT_con_int58_END (17)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int58_START (18)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int58_END (18)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int58_START (19)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int58_END (19)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int58_START (20)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int58_END (20)
#define SOC_ASP_SLIMBUS_P56_INT_und_int58_START (21)
#define SOC_ASP_SLIMBUS_P56_INT_und_int58_END (21)
#define SOC_ASP_SLIMBUS_P56_INT_act_int59_START (24)
#define SOC_ASP_SLIMBUS_P56_INT_act_int59_END (24)
#define SOC_ASP_SLIMBUS_P56_INT_con_int59_START (25)
#define SOC_ASP_SLIMBUS_P56_INT_con_int59_END (25)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int59_START (26)
#define SOC_ASP_SLIMBUS_P56_INT_chan_int59_END (26)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int59_START (27)
#define SOC_ASP_SLIMBUS_P56_INT_dma_int59_END (27)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int59_START (28)
#define SOC_ASP_SLIMBUS_P56_INT_ovf_int59_END (28)
#define SOC_ASP_SLIMBUS_P56_INT_und_int59_START (29)
#define SOC_ASP_SLIMBUS_P56_INT_und_int59_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int act_int60 : 1;
        unsigned int con_int60 : 1;
        unsigned int chan_int60 : 1;
        unsigned int dma_int60 : 1;
        unsigned int ovf_int60 : 1;
        unsigned int und_int60 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int act_int61 : 1;
        unsigned int con_int61 : 1;
        unsigned int chan_int61 : 1;
        unsigned int dma_int61 : 1;
        unsigned int ovf_int61 : 1;
        unsigned int und_int61 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int act_int62 : 1;
        unsigned int con_int62 : 1;
        unsigned int chan_int62 : 1;
        unsigned int dma_int62 : 1;
        unsigned int ovf_int62 : 1;
        unsigned int und_int62 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int act_int63 : 1;
        unsigned int con_int63 : 1;
        unsigned int chan_int63 : 1;
        unsigned int dma_int63 : 1;
        unsigned int ovf_int63 : 1;
        unsigned int und_int63 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_ASP_SLIMBUS_P60_INT_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_INT_act_int60_START (0)
#define SOC_ASP_SLIMBUS_P60_INT_act_int60_END (0)
#define SOC_ASP_SLIMBUS_P60_INT_con_int60_START (1)
#define SOC_ASP_SLIMBUS_P60_INT_con_int60_END (1)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int60_START (2)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int60_END (2)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int60_START (3)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int60_END (3)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int60_START (4)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int60_END (4)
#define SOC_ASP_SLIMBUS_P60_INT_und_int60_START (5)
#define SOC_ASP_SLIMBUS_P60_INT_und_int60_END (5)
#define SOC_ASP_SLIMBUS_P60_INT_act_int61_START (8)
#define SOC_ASP_SLIMBUS_P60_INT_act_int61_END (8)
#define SOC_ASP_SLIMBUS_P60_INT_con_int61_START (9)
#define SOC_ASP_SLIMBUS_P60_INT_con_int61_END (9)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int61_START (10)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int61_END (10)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int61_START (11)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int61_END (11)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int61_START (12)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int61_END (12)
#define SOC_ASP_SLIMBUS_P60_INT_und_int61_START (13)
#define SOC_ASP_SLIMBUS_P60_INT_und_int61_END (13)
#define SOC_ASP_SLIMBUS_P60_INT_act_int62_START (16)
#define SOC_ASP_SLIMBUS_P60_INT_act_int62_END (16)
#define SOC_ASP_SLIMBUS_P60_INT_con_int62_START (17)
#define SOC_ASP_SLIMBUS_P60_INT_con_int62_END (17)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int62_START (18)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int62_END (18)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int62_START (19)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int62_END (19)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int62_START (20)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int62_END (20)
#define SOC_ASP_SLIMBUS_P60_INT_und_int62_START (21)
#define SOC_ASP_SLIMBUS_P60_INT_und_int62_END (21)
#define SOC_ASP_SLIMBUS_P60_INT_act_int63_START (24)
#define SOC_ASP_SLIMBUS_P60_INT_act_int63_END (24)
#define SOC_ASP_SLIMBUS_P60_INT_con_int63_START (25)
#define SOC_ASP_SLIMBUS_P60_INT_con_int63_END (25)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int63_START (26)
#define SOC_ASP_SLIMBUS_P60_INT_chan_int63_END (26)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int63_START (27)
#define SOC_ASP_SLIMBUS_P60_INT_dma_int63_END (27)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int63_START (28)
#define SOC_ASP_SLIMBUS_P60_INT_ovf_int63_END (28)
#define SOC_ASP_SLIMBUS_P60_INT_und_int63_START (29)
#define SOC_ASP_SLIMBUS_P60_INT_und_int63_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P0_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P0_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P0_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P0_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P0_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P0_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P0_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P0_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P0_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P0_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P0_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P0_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P0_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P0_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P0_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P0_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P0_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P0_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P0_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P0_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P0_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P0_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P0_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P0_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P0_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P1_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P1_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P1_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P1_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P1_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P1_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P1_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P1_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P1_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P1_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P1_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P1_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P1_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P1_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P1_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P1_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P1_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P1_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P1_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P1_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P1_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P1_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P1_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P1_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P1_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P1_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P2_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P2_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P2_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P2_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P2_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P2_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P2_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P2_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P2_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P2_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P2_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P2_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P2_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P2_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P2_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P2_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P2_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P2_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P2_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P2_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P2_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P2_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P2_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P2_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P2_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P2_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P3_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P3_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P3_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P3_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P3_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P3_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P3_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P3_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P3_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P3_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P3_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P3_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P3_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P3_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P3_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P3_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P3_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P3_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P3_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P3_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P3_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P3_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P3_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P3_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P3_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P3_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P4_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P4_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P4_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P4_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P4_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P4_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P4_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P4_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P4_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P4_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P4_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P4_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P4_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P4_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P4_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P4_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P4_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P4_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P4_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P4_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P4_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P4_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P4_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P4_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P4_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P5_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P5_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P5_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P5_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P5_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P5_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P5_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P5_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P5_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P5_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P5_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P5_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P5_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P5_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P5_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P5_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P5_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P5_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P5_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P5_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P5_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P5_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P5_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P5_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P5_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P5_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P6_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P6_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P6_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P6_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P6_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P6_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P6_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P6_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P6_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P6_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P6_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P6_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P6_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P6_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P6_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P6_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P6_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P6_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P6_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P6_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P6_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P6_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P6_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P6_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P6_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P6_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P7_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P7_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P7_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P7_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P7_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P7_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P7_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P7_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P7_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P7_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P7_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P7_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P7_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P7_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P7_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P7_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P7_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P7_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P7_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P7_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P7_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P7_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P7_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P7_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P7_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P7_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_2 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P8_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P8_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P8_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P8_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P8_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P8_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P8_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P8_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P8_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P8_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P8_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P8_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P8_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P8_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P8_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P8_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P8_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P8_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P8_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P8_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P8_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P8_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P8_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P9_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P9_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P9_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P9_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P9_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P9_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P9_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P9_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P9_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P9_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P9_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P9_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P9_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P9_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P9_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P9_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P9_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P9_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P9_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P9_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P9_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P9_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P9_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P9_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P9_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P9_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P10_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P10_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P10_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P10_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P10_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P10_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P10_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P10_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P10_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P10_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P10_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P10_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P10_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P10_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P10_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P10_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P10_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P10_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P10_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P10_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P10_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P10_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P10_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P10_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P10_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P10_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P11_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P11_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P11_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P11_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P11_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P11_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P11_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P11_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P11_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P11_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P11_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P11_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P11_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P11_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P11_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P11_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P11_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P11_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P11_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P11_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P11_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P11_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P11_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P11_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P11_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P11_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P12_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P12_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P12_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P12_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P12_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P12_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P12_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P12_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P12_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P12_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P12_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P12_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P12_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P12_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P12_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P12_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P12_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P12_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P12_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P12_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P12_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P12_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P12_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P12_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P12_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P13_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P13_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P13_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P13_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P13_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P13_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P13_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P13_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P13_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P13_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P13_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P13_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P13_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P13_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P13_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P13_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P13_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P13_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P13_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P13_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P13_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P13_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P13_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P13_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P13_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P13_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P14_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P14_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P14_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P14_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P14_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P14_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P14_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P14_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P14_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P14_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P14_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P14_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P14_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P14_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P14_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P14_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P14_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P14_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P14_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P14_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P14_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P14_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P14_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P14_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P14_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P14_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P15_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P15_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P15_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P15_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P15_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P15_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P15_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P15_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P15_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P15_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P15_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P15_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P15_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P15_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P15_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P15_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P15_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P15_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P15_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P15_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P15_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P15_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P15_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P15_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P15_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P15_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P16_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P16_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P16_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P16_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P16_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P16_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P16_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P16_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P16_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P16_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P16_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P16_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P16_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P16_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P16_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P16_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P16_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P16_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P16_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P16_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P16_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P16_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P16_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P16_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P16_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P17_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P17_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P17_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P17_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P17_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P17_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P17_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P17_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P17_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P17_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P17_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P17_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P17_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P17_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P17_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P17_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P17_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P17_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P17_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P17_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P17_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P17_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P17_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P17_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P17_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P17_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P18_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P18_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P18_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P18_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P18_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P18_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P18_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P18_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P18_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P18_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P18_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P18_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P18_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P18_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P18_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P18_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P18_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P18_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P18_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P18_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P18_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P18_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P18_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P18_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P18_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P18_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P19_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P19_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P19_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P19_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P19_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P19_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P19_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P19_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P19_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P19_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P19_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P19_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P19_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P19_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P19_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P19_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P19_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P19_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P19_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P19_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P19_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P19_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P19_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P19_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P19_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P19_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P20_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P20_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P20_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P20_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P20_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P20_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P20_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P20_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P20_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P20_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P20_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P20_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P20_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P20_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P20_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P20_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P20_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P20_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P20_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P20_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P20_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P20_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P20_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P20_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P20_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P21_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P21_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P21_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P21_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P21_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P21_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P21_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P21_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P21_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P21_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P21_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P21_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P21_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P21_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P21_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P21_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P21_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P21_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P21_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P21_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P21_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P21_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P21_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P21_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P21_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P21_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P22_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P22_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P22_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P22_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P22_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P22_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P22_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P22_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P22_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P22_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P22_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P22_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P22_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P22_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P22_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P22_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P22_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P22_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P22_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P22_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P22_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P22_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P22_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P22_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P22_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P22_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P23_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P23_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P23_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P23_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P23_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P23_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P23_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P23_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P23_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P23_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P23_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P23_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P23_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P23_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P23_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P23_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P23_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P23_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P23_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P23_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P23_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P23_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P23_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P23_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P23_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P23_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P24_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P24_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P24_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P24_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P24_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P24_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P24_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P24_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P24_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P24_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P24_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P24_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P24_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P24_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P24_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P24_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P24_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P24_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P24_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P24_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P24_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P24_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P24_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P24_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P24_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P25_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P25_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P25_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P25_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P25_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P25_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P25_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P25_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P25_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P25_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P25_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P25_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P25_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P25_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P25_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P25_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P25_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P25_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P25_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P25_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P25_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P25_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P25_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P25_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P25_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P25_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P26_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P26_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P26_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P26_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P26_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P26_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P26_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P26_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P26_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P26_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P26_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P26_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P26_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P26_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P26_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P26_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P26_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P26_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P26_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P26_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P26_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P26_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P26_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P26_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P26_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P26_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P27_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P27_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P27_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P27_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P27_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P27_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P27_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P27_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P27_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P27_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P27_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P27_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P27_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P27_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P27_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P27_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P27_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P27_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P27_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P27_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P27_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P27_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P27_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P27_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P27_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P27_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P28_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P28_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P28_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P28_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P28_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P28_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P28_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P28_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P28_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P28_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P28_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P28_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P28_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P28_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P28_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P28_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P28_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P28_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P28_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P28_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P28_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P28_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P28_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P28_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P28_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P29_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P29_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P29_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P29_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P29_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P29_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P29_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P29_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P29_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P29_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P29_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P29_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P29_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P29_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P29_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P29_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P29_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P29_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P29_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P29_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P29_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P29_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P29_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P29_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P29_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P29_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P30_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P30_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P30_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P30_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P30_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P30_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P30_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P30_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P30_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P30_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P30_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P30_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P30_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P30_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P30_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P30_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P30_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P30_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P30_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P30_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P30_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P30_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P30_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P30_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P30_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P30_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P31_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P31_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P31_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P31_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P31_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P31_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P31_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P31_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P31_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P31_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P31_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P31_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P31_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P31_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P31_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P31_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P31_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P31_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P31_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P31_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P31_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P31_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P31_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P31_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P31_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P31_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P32_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P32_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P32_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P32_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P32_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P32_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P32_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P32_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P32_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P32_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P32_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P32_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P32_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P32_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P32_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P32_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P32_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P32_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P32_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P32_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P32_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P32_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P32_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P32_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P32_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P33_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P33_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P33_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P33_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P33_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P33_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P33_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P33_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P33_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P33_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P33_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P33_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P33_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P33_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P33_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P33_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P33_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P33_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P33_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P33_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P33_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P33_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P33_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P33_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P33_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P33_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P34_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P34_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P34_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P34_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P34_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P34_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P34_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P34_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P34_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P34_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P34_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P34_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P34_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P34_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P34_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P34_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P34_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P34_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P34_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P34_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P34_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P34_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P34_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P34_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P34_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P34_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P35_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P35_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P35_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P35_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P35_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P35_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P35_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P35_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P35_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P35_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P35_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P35_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P35_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P35_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P35_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P35_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P35_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P35_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P35_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P35_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P35_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P35_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P35_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P35_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P35_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P35_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P36_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P36_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P36_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P36_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P36_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P36_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P36_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P36_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P36_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P36_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P36_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P36_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P36_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P36_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P36_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P36_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P36_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P36_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P36_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P36_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P36_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P36_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P36_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P36_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P36_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P37_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P37_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P37_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P37_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P37_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P37_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P37_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P37_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P37_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P37_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P37_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P37_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P37_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P37_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P37_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P37_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P37_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P37_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P37_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P37_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P37_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P37_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P37_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P37_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P37_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P37_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P38_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P38_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P38_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P38_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P38_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P38_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P38_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P38_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P38_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P38_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P38_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P38_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P38_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P38_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P38_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P38_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P38_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P38_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P38_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P38_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P38_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P38_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P38_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P38_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P38_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P38_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P39_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P39_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P39_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P39_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P39_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P39_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P39_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P39_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P39_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P39_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P39_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P39_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P39_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P39_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P39_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P39_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P39_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P39_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P39_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P39_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P39_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P39_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P39_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P39_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P39_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P39_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P40_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P40_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P40_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P40_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P40_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P40_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P40_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P40_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P40_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P40_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P40_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P40_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P40_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P40_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P40_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P40_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P40_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P40_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P40_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P40_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P40_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P40_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P40_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P40_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P40_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P41_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P41_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P41_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P41_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P41_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P41_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P41_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P41_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P41_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P41_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P41_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P41_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P41_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P41_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P41_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P41_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P41_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P41_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P41_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P41_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P41_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P41_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P41_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P41_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P41_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P41_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P42_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P42_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P42_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P42_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P42_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P42_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P42_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P42_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P42_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P42_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P42_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P42_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P42_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P42_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P42_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P42_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P42_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P42_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P42_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P42_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P42_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P42_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P42_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P42_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P42_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P42_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P43_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P43_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P43_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P43_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P43_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P43_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P43_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P43_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P43_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P43_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P43_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P43_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P43_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P43_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P43_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P43_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P43_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P43_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P43_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P43_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P43_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P43_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P43_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P43_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P43_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P43_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P44_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P44_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P44_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P44_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P44_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P44_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P44_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P44_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P44_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P44_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P44_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P44_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P44_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P44_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P44_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P44_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P44_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P44_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P44_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P44_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P44_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P44_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P44_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P44_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P44_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P45_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P45_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P45_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P45_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P45_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P45_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P45_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P45_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P45_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P45_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P45_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P45_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P45_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P45_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P45_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P45_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P45_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P45_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P45_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P45_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P45_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P45_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P45_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P45_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P45_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P45_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P46_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P46_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P46_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P46_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P46_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P46_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P46_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P46_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P46_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P46_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P46_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P46_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P46_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P46_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P46_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P46_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P46_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P46_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P46_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P46_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P46_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P46_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P46_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P46_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P46_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P46_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P47_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P47_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P47_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P47_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P47_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P47_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P47_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P47_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P47_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P47_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P47_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P47_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P47_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P47_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P47_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P47_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P47_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P47_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P47_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P47_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P47_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P47_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P47_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P47_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P47_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P47_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P48_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P48_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P48_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P48_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P48_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P48_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P48_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P48_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P48_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P48_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P48_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P48_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P48_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P48_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P48_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P48_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P48_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P48_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P48_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P48_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P48_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P48_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P48_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P48_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P48_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P49_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P49_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P49_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P49_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P49_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P49_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P49_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P49_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P49_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P49_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P49_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P49_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P49_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P49_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P49_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P49_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P49_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P49_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P49_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P49_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P49_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P49_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P49_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P49_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P49_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P49_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P50_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P50_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P50_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P50_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P50_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P50_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P50_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P50_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P50_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P50_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P50_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P50_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P50_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P50_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P50_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P50_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P50_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P50_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P50_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P50_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P50_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P50_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P50_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P50_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P50_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P50_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P51_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P51_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P51_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P51_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P51_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P51_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P51_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P51_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P51_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P51_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P51_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P51_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P51_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P51_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P51_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P51_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P51_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P51_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P51_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P51_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P51_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P51_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P51_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P51_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P51_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P51_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P52_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P52_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P52_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P52_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P52_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P52_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P52_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P52_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P52_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P52_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P52_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P52_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P52_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P52_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P52_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P52_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P52_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P52_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P52_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P52_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P52_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P52_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P52_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P52_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P52_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P53_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P53_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P53_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P53_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P53_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P53_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P53_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P53_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P53_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P53_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P53_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P53_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P53_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P53_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P53_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P53_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P53_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P53_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P53_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P53_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P53_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P53_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P53_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P53_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P53_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P53_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P54_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P54_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P54_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P54_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P54_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P54_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P54_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P54_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P54_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P54_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P54_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P54_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P54_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P54_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P54_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P54_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P54_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P54_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P54_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P54_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P54_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P54_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P54_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P54_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P54_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P54_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P55_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P55_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P55_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P55_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P55_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P55_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P55_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P55_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P55_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P55_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P55_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P55_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P55_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P55_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P55_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P55_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P55_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P55_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P55_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P55_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P55_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P55_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P55_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P55_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P55_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P55_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P56_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P56_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P56_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P56_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P56_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P56_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P56_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P56_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P56_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P56_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P56_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P56_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P56_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P56_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P56_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P56_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P56_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P56_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P56_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P56_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P56_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P56_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P56_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P56_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P56_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P57_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P57_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P57_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P57_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P57_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P57_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P57_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P57_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P57_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P57_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P57_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P57_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P57_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P57_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P57_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P57_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P57_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P57_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P57_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P57_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P57_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P57_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P57_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P57_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P57_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P57_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P58_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P58_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P58_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P58_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P58_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P58_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P58_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P58_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P58_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P58_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P58_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P58_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P58_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P58_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P58_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P58_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P58_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P58_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P58_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P58_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P58_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P58_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P58_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P58_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P58_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P58_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P59_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P59_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P59_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P59_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P59_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P59_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P59_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P59_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P59_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P59_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P59_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P59_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P59_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P59_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P59_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P59_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P59_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P59_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P59_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P59_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P59_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P59_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P59_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P59_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P59_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P59_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P60_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P60_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P60_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P60_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P60_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P60_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P60_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P60_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P60_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P60_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P60_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P60_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P60_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P60_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P60_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P60_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P60_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P60_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P60_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P60_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P60_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P60_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P60_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P60_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P60_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P61_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P61_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P61_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P61_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P61_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P61_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P61_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P61_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P61_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P61_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P61_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P61_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P61_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P61_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P61_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P61_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P61_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P61_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P61_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P61_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P61_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P61_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P61_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P61_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P61_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P61_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P62_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P62_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P62_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P62_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P62_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P62_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P62_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P62_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P62_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P62_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P62_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P62_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P62_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P62_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P62_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P62_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P62_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P62_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P62_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P62_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P62_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P62_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P62_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P62_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P62_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P62_STATE_1_CH_LINK_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVE : 1;
        unsigned int CONTENT_DEFINED : 1;
        unsigned int CHANNEL_DEFINED : 1;
        unsigned int SINK : 1;
        unsigned int OVF : 1;
        unsigned int UND : 1;
        unsigned int DPORT_READY : 1;
        unsigned int reserved_0 : 9;
        unsigned int S_INTERVAL : 11;
        unsigned int reserved_1 : 1;
        unsigned int TR_PROTOCOL : 4;
    } reg;
} SOC_ASP_SLIMBUS_P63_STATE_0_UNION;
#endif
#define SOC_ASP_SLIMBUS_P63_STATE_0_ACTIVE_START (0)
#define SOC_ASP_SLIMBUS_P63_STATE_0_ACTIVE_END (0)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CONTENT_DEFINED_START (1)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CONTENT_DEFINED_END (1)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CHANNEL_DEFINED_START (2)
#define SOC_ASP_SLIMBUS_P63_STATE_0_CHANNEL_DEFINED_END (2)
#define SOC_ASP_SLIMBUS_P63_STATE_0_SINK_START (3)
#define SOC_ASP_SLIMBUS_P63_STATE_0_SINK_END (3)
#define SOC_ASP_SLIMBUS_P63_STATE_0_OVF_START (4)
#define SOC_ASP_SLIMBUS_P63_STATE_0_OVF_END (4)
#define SOC_ASP_SLIMBUS_P63_STATE_0_UND_START (5)
#define SOC_ASP_SLIMBUS_P63_STATE_0_UND_END (5)
#define SOC_ASP_SLIMBUS_P63_STATE_0_DPORT_READY_START (6)
#define SOC_ASP_SLIMBUS_P63_STATE_0_DPORT_READY_END (6)
#define SOC_ASP_SLIMBUS_P63_STATE_0_S_INTERVAL_START (16)
#define SOC_ASP_SLIMBUS_P63_STATE_0_S_INTERVAL_END (26)
#define SOC_ASP_SLIMBUS_P63_STATE_0_TR_PROTOCOL_START (28)
#define SOC_ASP_SLIMBUS_P63_STATE_0_TR_PROTOCOL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int P_RATE : 7;
        unsigned int FR_LOCK : 1;
        unsigned int DATA_TYPE : 4;
        unsigned int reserved_0 : 4;
        unsigned int DATA_LENGTH : 6;
        unsigned int reserved_1 : 2;
        unsigned int PORT_LINKED : 6;
        unsigned int reserved_2 : 1;
        unsigned int CH_LINK : 1;
    } reg;
} SOC_ASP_SLIMBUS_P63_STATE_1_UNION;
#endif
#define SOC_ASP_SLIMBUS_P63_STATE_1_P_RATE_START (0)
#define SOC_ASP_SLIMBUS_P63_STATE_1_P_RATE_END (6)
#define SOC_ASP_SLIMBUS_P63_STATE_1_FR_LOCK_START (7)
#define SOC_ASP_SLIMBUS_P63_STATE_1_FR_LOCK_END (7)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_TYPE_START (8)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_TYPE_END (11)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_LENGTH_START (16)
#define SOC_ASP_SLIMBUS_P63_STATE_1_DATA_LENGTH_END (21)
#define SOC_ASP_SLIMBUS_P63_STATE_1_PORT_LINKED_START (24)
#define SOC_ASP_SLIMBUS_P63_STATE_1_PORT_LINKED_END (29)
#define SOC_ASP_SLIMBUS_P63_STATE_1_CH_LINK_START (31)
#define SOC_ASP_SLIMBUS_P63_STATE_1_CH_LINK_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
