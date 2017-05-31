#ifndef __SOC_SCTRL_INTERFACE_H__
#define __SOC_SCTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SCTRL_MDM_CRG_PERIPH_CLKEN_ADDR(base) ((base) + (0x024))
#define SOC_SCTRL_MDM_CRG_PERIPH_CLKDIS_ADDR(base) ((base) + (0x028))
#define SOC_SCTRL_MDM_CRG_PERIPH_CLKSTAT_ADDR(base) ((base) + (0x02C))
#define SOC_SCTRL_MDM_CRG_PERIPH_CICOM0_BIT_POS (8)
#define SOC_SCTRL_MDM_CRG_PERIPH_CICOM1_BIT_POS (9)
#define SOC_SCTRL_SC_PERIPH_CTRL4_ADDR(base) ((base) + (0x410))
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gucicom0sel_mode : 1;
        unsigned int gucicom1sel_mode : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_SCtrl_SC_PERIPH_CTRL1_UNION;
#define SOC_SCtrl_SC_PERIPH_CTRL1_cicomsel_mode_START (0)
#define SOC_SCtrl_SC_PERIPH_CTRL1_cicomsel_mode_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
