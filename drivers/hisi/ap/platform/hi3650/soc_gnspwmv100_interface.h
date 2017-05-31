#ifndef __SOC_GNSPWMV100_INTERFACE_H__
#define __SOC_GNSPWMV100_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_GNSPWMV100_PWM_CFG_ADDR(base) ((base) + (0x000))
#define SOC_GNSPWMV100_PWM_NUM_ADDR(base) ((base) + (0x004))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_code : 3;
        unsigned int cfg_start : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_GNSPWMV100_PWM_CFG_UNION;
#endif
#define SOC_GNSPWMV100_PWM_CFG_cfg_code_START (0)
#define SOC_GNSPWMV100_PWM_CFG_cfg_code_END (2)
#define SOC_GNSPWMV100_PWM_CFG_cfg_start_START (3)
#define SOC_GNSPWMV100_PWM_CFG_cfg_start_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_num : 32;
    } reg;
} SOC_GNSPWMV100_PWM_NUM_UNION;
#endif
#define SOC_GNSPWMV100_PWM_NUM_pwm_num_START (0)
#define SOC_GNSPWMV100_PWM_NUM_pwm_num_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
