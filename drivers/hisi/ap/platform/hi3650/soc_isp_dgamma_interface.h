#ifndef __SOC_ISP_DGAMMA_INTERFACE_H__
#define __SOC_ISP_DGAMMA_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_ADDR(base) ((base) + (0x000c))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_ADDR(base,Range96) ((base) + (0x0100+0x4*(Range96)))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_ADDR(base,Range96,Num96) ((base) + (0x0100+0x4*(Num96)+0x4*(Range96)))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_ADDR(base,Range96,Num96) ((base) + (0x0100+0x4*2*(Num96)+0x4*(Range96)))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_ADDR(base,Range96) ((base) + (0x0600+0x4*(Range96)))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_ADDR(base,Range96,Num96) ((base) + (0x0600+0x4*(Num96)+0x4*(Range96)))
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_ADDR(base,Range96,Num96) ((base) + (0x0600+0x4*2*(Num96)+0x4*(Range96)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_CONFIG_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_bypass_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_dgamma_active_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_dgamma_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lutscl_factor : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_DGAMMA_LUTSCL_FACTOR_UNION;
#endif
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_lutscl_factor_START (0)
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_lutscl_factor_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_r : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_dgamma_out_r_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_dgamma_out_r_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_g : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_dgamma_out_g_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_dgamma_out_g_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_b : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_dgamma_out_b_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_dgamma_out_b_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_r : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_dgamma_out_r_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_dgamma_out_r_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_g : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_dgamma_out_g_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_dgamma_out_g_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dgamma_out_b : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_dgamma_out_b_START (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_dgamma_out_b_END (9)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
