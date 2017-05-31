#ifndef __SOC_ISP_FBDYUV_INTERFACE_H__
#define __SOC_ISP_FBDYUV_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FBDYUV_FBD_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FBDYUV_FBD_STATUS_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_ADDR(base) ((base) + (0x0008))
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
} SOC_ISP_FBDYUV_FBD_CONFIG_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_CONFIG_bypass_START (0)
#define SOC_ISP_FBDYUV_FBD_CONFIG_bypass_END (0)
#define SOC_ISP_FBDYUV_FBD_CONFIG_line_width_START (16)
#define SOC_ISP_FBDYUV_FBD_CONFIG_line_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_error : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_FBDYUV_FBD_STATUS_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_STATUS_stream_error_START (0)
#define SOC_ISP_FBDYUV_FBD_STATUS_stream_error_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamsize : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_ISP_FBDYUV_FBD_STREAM_SIZE_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_streamsize_START (0)
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_streamsize_END (21)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
