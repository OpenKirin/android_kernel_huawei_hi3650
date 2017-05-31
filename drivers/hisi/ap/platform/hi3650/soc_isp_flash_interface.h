#ifndef __SOC_ISP_FLASH_INTERFACE_H__
#define __SOC_ISP_FLASH_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FLASH_CMD_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FLASH_CONFIG_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_FLASH_PREDIV_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_FLASH_DELAY_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_FLASH_TIME_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_FLASH_MAXP_ADDR(base) ((base) + (0x0014))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prelight_on : 1;
        unsigned int flash_on : 1;
        unsigned int preflash_on : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_FLASH_CMD_UNION;
#endif
#define SOC_ISP_FLASH_CMD_prelight_on_START (0)
#define SOC_ISP_FLASH_CMD_prelight_on_END (0)
#define SOC_ISP_FLASH_CMD_flash_on_START (1)
#define SOC_ISP_FLASH_CMD_flash_on_END (1)
#define SOC_ISP_FLASH_CMD_preflash_on_START (2)
#define SOC_ISP_FLASH_CMD_preflash_on_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prelight_mode : 1;
        unsigned int vs_in_edge : 1;
        unsigned int fl_pol : 1;
        unsigned int fl_trig_sel : 2;
        unsigned int fl_cap_del : 4;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_FLASH_CONFIG_UNION;
#endif
#define SOC_ISP_FLASH_CONFIG_prelight_mode_START (0)
#define SOC_ISP_FLASH_CONFIG_prelight_mode_END (0)
#define SOC_ISP_FLASH_CONFIG_vs_in_edge_START (1)
#define SOC_ISP_FLASH_CONFIG_vs_in_edge_END (1)
#define SOC_ISP_FLASH_CONFIG_fl_pol_START (2)
#define SOC_ISP_FLASH_CONFIG_fl_pol_END (2)
#define SOC_ISP_FLASH_CONFIG_fl_trig_sel_START (3)
#define SOC_ISP_FLASH_CONFIG_fl_trig_sel_END (4)
#define SOC_ISP_FLASH_CONFIG_fl_cap_del_START (5)
#define SOC_ISP_FLASH_CONFIG_fl_cap_del_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fl_pre_div : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_FLASH_PREDIV_UNION;
#endif
#define SOC_ISP_FLASH_PREDIV_fl_pre_div_START (0)
#define SOC_ISP_FLASH_PREDIV_fl_pre_div_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fl_delay : 18;
        unsigned int reserved : 14;
    } reg;
} SOC_ISP_FLASH_DELAY_UNION;
#endif
#define SOC_ISP_FLASH_DELAY_fl_delay_START (0)
#define SOC_ISP_FLASH_DELAY_fl_delay_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fl_time : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_FLASH_TIME_UNION;
#endif
#define SOC_ISP_FLASH_TIME_fl_time_START (0)
#define SOC_ISP_FLASH_TIME_fl_time_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fl_mawp : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_FLASH_MAXP_UNION;
#endif
#define SOC_ISP_FLASH_MAXP_fl_mawp_START (0)
#define SOC_ISP_FLASH_MAXP_fl_mawp_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
