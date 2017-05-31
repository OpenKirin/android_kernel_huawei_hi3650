#ifndef __SOC_ISP_FBDRAW_INTERFACE_H__
#define __SOC_ISP_FBDRAW_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FBDRAW_FBD_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FBDRAW_FBD_STATUS_ADDR(base) ((base) + (0x0004))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int seg_size : 1;
        unsigned int pix_size : 2;
        unsigned int reserved_0 : 12;
        unsigned int line_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_FBDRAW_FBD_CONFIG_UNION;
#endif
#define SOC_ISP_FBDRAW_FBD_CONFIG_bypass_START (0)
#define SOC_ISP_FBDRAW_FBD_CONFIG_bypass_END (0)
#define SOC_ISP_FBDRAW_FBD_CONFIG_seg_size_START (1)
#define SOC_ISP_FBDRAW_FBD_CONFIG_seg_size_END (1)
#define SOC_ISP_FBDRAW_FBD_CONFIG_pix_size_START (2)
#define SOC_ISP_FBDRAW_FBD_CONFIG_pix_size_END (3)
#define SOC_ISP_FBDRAW_FBD_CONFIG_line_width_START (16)
#define SOC_ISP_FBDRAW_FBD_CONFIG_line_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_error : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_FBDRAW_FBD_STATUS_UNION;
#endif
#define SOC_ISP_FBDRAW_FBD_STATUS_stream_error_START (0)
#define SOC_ISP_FBDRAW_FBD_STATUS_stream_error_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
