#ifndef __SOC_ISP_FBCRAW_INTERFACE_H__
#define __SOC_ISP_FBCRAW_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FBCRAW_FBC_CONFIG1_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FBCRAW_FBC_CONFIG2_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_FBCRAW_TEEE_ADDR(base) ((base) + (0x2000))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int seg_size : 1;
        unsigned int pix_size : 2;
        unsigned int dualmode : 1;
        unsigned int reserved_0 : 11;
        unsigned int line_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_FBCRAW_FBC_CONFIG1_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CONFIG1_bypass_START (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_bypass_END (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_seg_size_START (1)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_seg_size_END (1)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_pix_size_START (2)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_pix_size_END (3)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_dualmode_START (4)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_dualmode_END (4)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_line_width_START (16)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_line_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int initqp : 6;
        unsigned int reserved_0: 10;
        unsigned int bit_thres : 8;
        unsigned int reserved_1: 8;
    } reg;
} SOC_ISP_FBCRAW_FBC_CONFIG2_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CONFIG2_initqp_START (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_initqp_END (5)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_bit_thres_START (16)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_bit_thres_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvv : 2;
        unsigned int aaa : 30;
    } reg;
} SOC_ISP_FBCRAW_TEEE_UNION;
#endif
#define SOC_ISP_FBCRAW_TEEE_cvv_START (0)
#define SOC_ISP_FBCRAW_TEEE_cvv_END (1)
#define SOC_ISP_FBCRAW_TEEE_aaa_START (2)
#define SOC_ISP_FBCRAW_TEEE_aaa_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
