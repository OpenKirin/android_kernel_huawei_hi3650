#ifndef __SOC_PWM_INTERFACE_H__
#define __SOC_PWM_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_PWM__LOCK_ADDR(base) ((base) + (0x000))
#define SOC_PWM_CTL_ADDR(base) ((base) + (0x004))
#define SOC_PWM_CFG_ADDR(base) ((base) + (0x0008))
#define SOC_PWM_PR0_ADDR(base) ((base) + (0x0100))
#define SOC_PWM_PR1_ADDR(base) ((base) + (0x0104))
#define SOC_PWM_PCNT0_ADDR(base) ((base) + (0x0108))
#define SOC_PWM_PCNT1_ADDR(base) ((base) + (0x010C))
#define SOC_PWM_C0_MR_ADDR(base) ((base) + (0x0300))
#define SOC_PWM_C1_MR_ADDR(base) ((base) + (0x0400))
#define SOC_PWM_C0_MR0_ADDR(base) ((base) + (0x0304))
#define SOC_PWM_C1_MR0_ADDR(base) ((base) + (0x0404))
#define SOC_PWM_C0_MR1_ADDR(base) ((base) + (0x0308))
#define SOC_PWM_C1_MR1_ADDR(base) ((base) + (0x0408))
#define SOC_PWM_C0_TCNT_ADDR(base) ((base) + (0x030C))
#define SOC_PWM_C1_TCNT_ADDR(base) ((base) + (0x040C))
#define SOC_PWM_C0_PHA_ADDR(base) ((base) + (0x0310))
#define SOC_PWM_C1_PHA_ADDR(base) ((base) + (0x0410))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_lock : 32;
    } reg;
} SOC_PWM__LOCK_UNION;
#endif
#define SOC_PWM__LOCK_pwm_lock_START (0)
#define SOC_PWM__LOCK_pwm_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_en : 1;
        unsigned int pwm_rst : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PWM_CTL_UNION;
#endif
#define SOC_PWM_CTL_pwm_en_START (0)
#define SOC_PWM_CTL_pwm_en_END (0)
#define SOC_PWM_CTL_pwm_rst_START (1)
#define SOC_PWM_CTL_pwm_rst_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_mode_0 : 1;
        unsigned int pwm_oen_0 : 1;
        unsigned int pwm_mode_1 : 1;
        unsigned int pwm_oen_1 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_PWM_CFG_UNION;
#endif
#define SOC_PWM_CFG_pwm_mode_0_START (0)
#define SOC_PWM_CFG_pwm_mode_0_END (0)
#define SOC_PWM_CFG_pwm_oen_0_START (1)
#define SOC_PWM_CFG_pwm_oen_0_END (1)
#define SOC_PWM_CFG_pwm_mode_1_START (2)
#define SOC_PWM_CFG_pwm_mode_1_END (2)
#define SOC_PWM_CFG_pwm_oen_1_START (3)
#define SOC_PWM_CFG_pwm_oen_1_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_pr0 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PWM_PR0_UNION;
#endif
#define SOC_PWM_PR0_pwm_pr0_START (0)
#define SOC_PWM_PR0_pwm_pr0_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_pr1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PWM_PR1_UNION;
#endif
#define SOC_PWM_PR1_pwm_pr1_START (0)
#define SOC_PWM_PR1_pwm_pr1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_pcnt1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PWM_PCNT0_UNION;
#endif
#define SOC_PWM_PCNT0_pwm_pcnt1_START (0)
#define SOC_PWM_PCNT0_pwm_pcnt1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_pcnt1 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PWM_PCNT1_UNION;
#endif
#define SOC_PWM_PCNT1_pwm_pcnt1_START (0)
#define SOC_PWM_PCNT1_pwm_pcnt1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c0_mr : 32;
    } reg;
} SOC_PWM_C0_MR_UNION;
#endif
#define SOC_PWM_C0_MR_pwm_c0_mr_START (0)
#define SOC_PWM_C0_MR_pwm_c0_mr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c1_mr : 32;
    } reg;
} SOC_PWM_C1_MR_UNION;
#endif
#define SOC_PWM_C1_MR_pwm_c1_mr_START (0)
#define SOC_PWM_C1_MR_pwm_c1_mr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c0_mr0 : 32;
    } reg;
} SOC_PWM_C0_MR0_UNION;
#endif
#define SOC_PWM_C0_MR0_pwm_c0_mr0_START (0)
#define SOC_PWM_C0_MR0_pwm_c0_mr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c1_mr0 : 32;
    } reg;
} SOC_PWM_C1_MR0_UNION;
#endif
#define SOC_PWM_C1_MR0_pwm_c1_mr0_START (0)
#define SOC_PWM_C1_MR0_pwm_c1_mr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c0_mr1 : 32;
    } reg;
} SOC_PWM_C0_MR1_UNION;
#endif
#define SOC_PWM_C0_MR1_pwm_c0_mr1_START (0)
#define SOC_PWM_C0_MR1_pwm_c0_mr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c1_mr1 : 32;
    } reg;
} SOC_PWM_C1_MR1_UNION;
#endif
#define SOC_PWM_C1_MR1_pwm_c1_mr1_START (0)
#define SOC_PWM_C1_MR1_pwm_c1_mr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c0_tcnt : 32;
    } reg;
} SOC_PWM_C0_TCNT_UNION;
#endif
#define SOC_PWM_C0_TCNT_pwm_c0_tcnt_START (0)
#define SOC_PWM_C0_TCNT_pwm_c0_tcnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_c1_tcnt : 32;
    } reg;
} SOC_PWM_C1_TCNT_UNION;
#endif
#define SOC_PWM_C1_TCNT_pwm_c1_tcnt_START (0)
#define SOC_PWM_C1_TCNT_pwm_c1_tcnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_ch0_pha : 32;
    } reg;
} SOC_PWM_C0_PHA_UNION;
#endif
#define SOC_PWM_C0_PHA_pwm_ch0_pha_START (0)
#define SOC_PWM_C0_PHA_pwm_ch0_pha_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwm_ch1_pha : 32;
    } reg;
} SOC_PWM_C1_PHA_UNION;
#endif
#define SOC_PWM_C1_PHA_pwm_ch1_pha_START (0)
#define SOC_PWM_C1_PHA_pwm_ch1_pha_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
