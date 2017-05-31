#ifndef __SOC_ISP_FBCYUV_INTERFACE_H__
#define __SOC_ISP_FBCYUV_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FBCYUV_FBC_CONFIG1_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FBCYUV_FBC_CONFIG2_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_ADDR(base) ((base) + (0x0008))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved_0 : 15;
        unsigned int line_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_FBCYUV_FBC_CONFIG1_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_CONFIG1_bypass_START (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_bypass_END (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_line_width_START (16)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_line_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int initqpy : 6;
        unsigned int reserved_0: 2;
        unsigned int initqpuv : 5;
        unsigned int reserved_1: 3;
        unsigned int bit_thres : 8;
        unsigned int reserved_2: 8;
    } reg;
} SOC_ISP_FBCYUV_FBC_CONFIG2_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpy_START (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpy_END (5)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpuv_START (8)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpuv_END (12)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_bit_thres_START (16)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_bit_thres_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamsize : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_ISP_FBCYUV_FBC_STREAM_SIZE_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_streamsize_START (0)
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_streamsize_END (21)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
