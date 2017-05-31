#ifndef __SOC_ISP_PRESCALER_INTERFACE_H__
#define __SOC_ISP_PRESCALER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_PRESCALER_HCROP_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_PRESCALER_VCROP_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_PRESCALER_MODE_ADDR(base) ((base) + (0x0008))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihright1 : 13;
        unsigned int reserved_0: 3;
        unsigned int ihright2 : 13;
        unsigned int ihleft2 : 2;
        unsigned int reserved_1: 1;
    } reg;
} SOC_ISP_PRESCALER_HCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_HCROP_ihright1_START (0)
#define SOC_ISP_PRESCALER_HCROP_ihright1_END (12)
#define SOC_ISP_PRESCALER_HCROP_ihright2_START (16)
#define SOC_ISP_PRESCALER_HCROP_ihright2_END (28)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_START (29)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivbottom : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_PRESCALER_VCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_VCROP_ivbottom_START (0)
#define SOC_ISP_PRESCALER_VCROP_ivbottom_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int input_sel : 2;
        unsigned int bypass : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_PRESCALER_MODE_UNION;
#endif
#define SOC_ISP_PRESCALER_MODE_input_sel_START (0)
#define SOC_ISP_PRESCALER_MODE_input_sel_END (1)
#define SOC_ISP_PRESCALER_MODE_bypass_START (2)
#define SOC_ISP_PRESCALER_MODE_bypass_END (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
