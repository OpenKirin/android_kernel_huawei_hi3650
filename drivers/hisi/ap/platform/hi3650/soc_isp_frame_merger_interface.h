#ifndef __SOC_ISP_FRAME_MERGER_INTERFACE_H__
#define __SOC_ISP_FRAME_MERGER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FRAME_MERGER_CFG_ADDR(base) ((base) + (0x0))
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_ADDR(base) ((base) + (0x4))
#define SOC_ISP_FRAME_MERGER_DEBUG_ADDR(base) ((base) + (0x8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_FRAME_MERGER_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_CFG_mode_START (0)
#define SOC_ISP_FRAME_MERGER_CFG_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fe2_fifo_peak_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_CFG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_START (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_CFG_fe2_fifo_peak_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fe2_fifo_peak : 16;
        unsigned int fe2_fsm_router : 5;
        unsigned int fe2_fsm_pack : 2;
        unsigned int fe2_fsm_unpack : 2;
        unsigned int fe2_fsm_pressure_mode : 1;
        unsigned int reserved : 6;
    } reg;
} SOC_ISP_FRAME_MERGER_DEBUG_UNION;
#endif
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_START (0)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fifo_peak_END (15)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_START (16)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_router_END (20)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_START (21)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pack_END (22)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_START (23)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_unpack_END (24)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_START (25)
#define SOC_ISP_FRAME_MERGER_DEBUG_fe2_fsm_pressure_mode_END (25)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
