#ifndef __SOC_LPM3_CFG_INTERFACE_H__
#define __SOC_LPM3_CFG_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_LPM3_CFG_ACCESS_WIN_ADDR(base) ((base) + (0x000))
#define SOC_LPM3_CFG_HALT_BYPASS_ADDR(base) ((base) + (0x004))
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_ADDR(base) ((base) + (0x008))
#define SOC_LPM3_CFG_DLOCK_BYPASS_ADDR(base) ((base) + (0x00C))
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_ADDR(base) ((base) + (0x010))
#define SOC_LPM3_CFG_TESTPIN_EN_ADDR(base) ((base) + (0x014))
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ADDR(base) ((base) + (0x020))
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ADDR(base) ((base) + (0x024))
#define SOC_LPM3_CFG_NMI_SOFT_ADDR(base) ((base) + (0x028))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 28;
        unsigned int access_window : 4;
    } reg;
} SOC_LPM3_CFG_ACCESS_WIN_UNION;
#endif
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_START (28)
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int halt_bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_LPM3_CFG_HALT_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_START (0)
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpram_multi_ctrl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION;
#endif
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_START (0)
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass_for_ssi1 : 1;
        unsigned int bypass_for_ddrc : 1;
        unsigned int bypass_for_tsen : 1;
        unsigned int bypass_for_pmc : 1;
        unsigned int bypass_for_uart : 1;
        unsigned int bypass_for_i2c : 1;
        unsigned int bypass_for_ssi0 : 1;
        unsigned int bypass_for_pcrg : 1;
        unsigned int bypass_for_wdog : 1;
        unsigned int bypass_for_timer : 1;
        unsigned int reserved_0 : 1;
        unsigned int bypass_for_cssys : 1;
        unsigned int bypass_for_pwm : 1;
        unsigned int bypass_for_rom : 1;
        unsigned int bypass_for_ram : 1;
        unsigned int bypass_for_nandc : 1;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_LPM3_CFG_DLOCK_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_START (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_END (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_START (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_END (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_START (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_END (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_START (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_END (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_START (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_END (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_START (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_END (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_START (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_END (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_START (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_END (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_START (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_END (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_START (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_END (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_START (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_END (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_START (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_END (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_START (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_END (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_START (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_END (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_START (15)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timclken_bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_START (0)
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int testpin_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_LPM3_CFG_TESTPIN_EN_UNION;
#endif
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_START (0)
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_ap_occupy_grp1 : 2;
        unsigned int soc_ap_occupy_grp2 : 2;
        unsigned int soc_ap_occupy_grp3 : 2;
        unsigned int soc_ap_occupy_grp4 : 2;
        unsigned int soc_ap_occupy_grp5 : 2;
        unsigned int soc_ap_occupy_grp6 : 2;
        unsigned int soc_ap_occupy_grp7 : 2;
        unsigned int reserved : 2;
        unsigned int ram_ctrl_sd_grp1 : 1;
        unsigned int ram_ctrl_sd_grp2 : 1;
        unsigned int ram_ctrl_sd_grp3 : 1;
        unsigned int ram_ctrl_sd_grp4 : 3;
        unsigned int ram_ctrl_sd_grp5 : 2;
        unsigned int ram_ctrl_dslp_grp1 : 1;
        unsigned int ram_ctrl_dslp_grp2 : 1;
        unsigned int ram_ctrl_dslp_grp3 : 1;
        unsigned int ram_ctrl_dslp_grp4 : 3;
        unsigned int ram_ctrl_dslp_grp5 : 2;
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL0_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_START (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_END (1)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_START (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_END (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_START (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_END (5)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_START (6)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_END (7)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_START (8)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_END (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_START (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_END (11)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_START (12)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_END (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_START (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_END (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_START (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_END (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_START (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_END (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_START (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_END (21)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_START (22)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_END (23)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_START (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_END (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_START (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_END (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_START (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_END (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_START (27)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_END (29)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_START (30)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ram_ctrl_sd_grp6 : 3;
        unsigned int ram_ctrl_sd_grp7 : 11;
        unsigned int reserved_0 : 2;
        unsigned int ram_ctrl_dslp_grp6 : 3;
        unsigned int ram_ctrl_dslp_grp7 : 11;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL1_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_START (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_END (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_START (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_END (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_START (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_END (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_START (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nmi_soft : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_LPM3_CFG_NMI_SOFT_UNION;
#endif
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_START (0)
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
