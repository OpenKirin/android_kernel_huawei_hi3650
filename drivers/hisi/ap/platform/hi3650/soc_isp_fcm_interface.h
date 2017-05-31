#ifndef __SOC_ISP_FCM_INTERFACE_H__
#define __SOC_ISP_FCM_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FCM_CFG_ADDR(base,CHANNEL_NBR_range) ((base) + (0x20*(CHANNEL_NBR_range)))
#define SOC_ISP_FCM_DEBUG_ADDR(base,CHANNEL_NBR_range) ((base) + (0x4+0x20*(CHANNEL_NBR_range)))
#define SOC_ISP_FCM_SW_WR_REQ_ADDR(base,CHANNEL_NBR_range) ((base) + (0x10+0x20*(CHANNEL_NBR_range)))
#define SOC_ISP_FCM_SW_WR_DONE_ADDR(base,CHANNEL_NBR_range) ((base) + (0x14+0x20*(CHANNEL_NBR_range)))
#define SOC_ISP_FCM_SW_RD_REQ_ADDR(base,CHANNEL_NBR_range) ((base) + (0x18+0x20*(CHANNEL_NBR_range)))
#define SOC_ISP_FCM_SW_RD_DONE_ADDR(base,CHANNEL_NBR_range) ((base) + (0x1C+0x20*(CHANNEL_NBR_range)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffer_depth : 13;
        unsigned int reserved_0 : 3;
        unsigned int read_source : 1;
        unsigned int reserved_1 : 7;
        unsigned int write_source : 1;
        unsigned int reserved_2 : 6;
        unsigned int enable : 1;
    } reg;
} SOC_ISP_FCM_CFG_UNION;
#endif
#define SOC_ISP_FCM_CFG_buffer_depth_START (0)
#define SOC_ISP_FCM_CFG_buffer_depth_END (12)
#define SOC_ISP_FCM_CFG_read_source_START (16)
#define SOC_ISP_FCM_CFG_read_source_END (16)
#define SOC_ISP_FCM_CFG_write_source_START (24)
#define SOC_ISP_FCM_CFG_write_source_END (24)
#define SOC_ISP_FCM_CFG_enable_START (31)
#define SOC_ISP_FCM_CFG_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int active_lines : 13;
        unsigned int fcm_sm : 3;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_FCM_DEBUG_UNION;
#endif
#define SOC_ISP_FCM_DEBUG_active_lines_START (0)
#define SOC_ISP_FCM_DEBUG_active_lines_END (12)
#define SOC_ISP_FCM_DEBUG_fcm_sm_START (13)
#define SOC_ISP_FCM_DEBUG_fcm_sm_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int request : 10;
        unsigned int end : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_FCM_SW_WR_REQ_UNION;
#endif
#define SOC_ISP_FCM_SW_WR_REQ_request_START (0)
#define SOC_ISP_FCM_SW_WR_REQ_request_END (9)
#define SOC_ISP_FCM_SW_WR_REQ_end_START (10)
#define SOC_ISP_FCM_SW_WR_REQ_end_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int done : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_FCM_SW_WR_DONE_UNION;
#endif
#define SOC_ISP_FCM_SW_WR_DONE_done_START (0)
#define SOC_ISP_FCM_SW_WR_DONE_done_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int request : 10;
        unsigned int end : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_FCM_SW_RD_REQ_UNION;
#endif
#define SOC_ISP_FCM_SW_RD_REQ_request_START (0)
#define SOC_ISP_FCM_SW_RD_REQ_request_END (9)
#define SOC_ISP_FCM_SW_RD_REQ_end_START (10)
#define SOC_ISP_FCM_SW_RD_REQ_end_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int done : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_FCM_SW_RD_DONE_UNION;
#endif
#define SOC_ISP_FCM_SW_RD_DONE_done_START (0)
#define SOC_ISP_FCM_SW_RD_DONE_done_END (9)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
