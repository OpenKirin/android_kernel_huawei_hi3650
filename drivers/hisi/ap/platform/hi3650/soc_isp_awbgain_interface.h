#ifndef __SOC_ISP_AWBGAIN_INTERFACE_H__
#define __SOC_ISP_AWBGAIN_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_ADDR(base) ((base) + (0x0004))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awb_gain_gb : 12;
        unsigned int reserved_0 : 4;
        unsigned int awb_gain_gr : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_START (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_END (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_START (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awb_gain_b : 12;
        unsigned int reserved_0 : 4;
        unsigned int awb_gain_r : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_START (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_END (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_START (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_END (27)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
