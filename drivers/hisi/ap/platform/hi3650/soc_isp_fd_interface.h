#ifndef __SOC_ISP_FD_INTERFACE_H__
#define __SOC_ISP_FD_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_FD_CTRL_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_FD_RESULT_CNT_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_FD_DETECT_CONDITION_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_FD_DETECT_START_X_ADDR(base) ((base) + (0x000c))
#define SOC_ISP_FD_DETECT_START_Y_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_FD_DETECT_SIZE_X_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_FD_DETECT_SIZE_Y_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_FD_THRESHOLD_ADDR(base) ((base) + (0x001c))
#define SOC_ISP_FD_BASE_ADDR_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_FD_VERSION_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_FD_RESULT_X_ADDR(base,result_range) ((base) + (0x0400+(result_range)*16))
#define SOC_ISP_FD_RESULT_Y_ADDR(base,result_range) ((base) + (0x0404+(result_range)*16))
#define SOC_ISP_FD_RESULT_LS_ADDR(base,result_range) ((base) + (0x0408+(result_range)*16))
#define SOC_ISP_FD_RESULT_ANGLE_ADDR(base,result_range) ((base) + (0x040c+(result_range)*16))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int RUN : 1;
        unsigned int FINISH : 1;
        unsigned int reserved_1: 3;
        unsigned int RD_IID : 7;
        unsigned int RD_SID : 6;
        unsigned int WR_IID : 7;
        unsigned int WR_SID : 6;
    } reg;
} SOC_ISP_FD_CTRL_UNION;
#endif
#define SOC_ISP_FD_CTRL_RUN_START (1)
#define SOC_ISP_FD_CTRL_RUN_END (1)
#define SOC_ISP_FD_CTRL_FINISH_START (2)
#define SOC_ISP_FD_CTRL_FINISH_END (2)
#define SOC_ISP_FD_CTRL_RD_IID_START (6)
#define SOC_ISP_FD_CTRL_RD_IID_END (12)
#define SOC_ISP_FD_CTRL_RD_SID_START (13)
#define SOC_ISP_FD_CTRL_RD_SID_END (18)
#define SOC_ISP_FD_CTRL_WR_IID_START (19)
#define SOC_ISP_FD_CTRL_WR_IID_END (25)
#define SOC_ISP_FD_CTRL_WR_SID_START (26)
#define SOC_ISP_FD_CTRL_WR_SID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DNUM : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_FD_RESULT_CNT_UNION;
#endif
#define SOC_ISP_FD_RESULT_CNT_DNUM_START (0)
#define SOC_ISP_FD_RESULT_CNT_DNUM_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MIN : 2;
        unsigned int DIR : 4;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_FD_DETECT_CONDITION_UNION;
#endif
#define SOC_ISP_FD_DETECT_CONDITION_MIN_START (0)
#define SOC_ISP_FD_DETECT_CONDITION_MIN_END (1)
#define SOC_ISP_FD_DETECT_CONDITION_DIR_START (2)
#define SOC_ISP_FD_DETECT_CONDITION_DIR_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int STARTX : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_FD_DETECT_START_X_UNION;
#endif
#define SOC_ISP_FD_DETECT_START_X_STARTX_START (0)
#define SOC_ISP_FD_DETECT_START_X_STARTX_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int STARTY : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_FD_DETECT_START_Y_UNION;
#endif
#define SOC_ISP_FD_DETECT_START_Y_STARTY_START (0)
#define SOC_ISP_FD_DETECT_START_Y_STARTY_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SIZEX : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_FD_DETECT_SIZE_X_UNION;
#endif
#define SOC_ISP_FD_DETECT_SIZE_X_SIZEX_START (0)
#define SOC_ISP_FD_DETECT_SIZE_X_SIZEX_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SIZEY : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_FD_DETECT_SIZE_Y_UNION;
#endif
#define SOC_ISP_FD_DETECT_SIZE_Y_SIZEY_START (0)
#define SOC_ISP_FD_DETECT_SIZE_Y_SIZEY_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DHIT : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_FD_THRESHOLD_UNION;
#endif
#define SOC_ISP_FD_THRESHOLD_DHIT_START (0)
#define SOC_ISP_FD_THRESHOLD_DHIT_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 12;
        unsigned int base_address : 20;
    } reg;
} SOC_ISP_FD_BASE_ADDR_UNION;
#endif
#define SOC_ISP_FD_BASE_ADDR_base_address_START (12)
#define SOC_ISP_FD_BASE_ADDR_base_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int VER : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_FD_VERSION_UNION;
#endif
#define SOC_ISP_FD_VERSION_VER_START (0)
#define SOC_ISP_FD_VERSION_VER_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CENTERX : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_FD_RESULT_X_UNION;
#endif
#define SOC_ISP_FD_RESULT_X_CENTERX_START (0)
#define SOC_ISP_FD_RESULT_X_CENTERX_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CENTERY : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_FD_RESULT_Y_UNION;
#endif
#define SOC_ISP_FD_RESULT_Y_CENTERY_START (0)
#define SOC_ISP_FD_RESULT_Y_CENTERY_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SIZE : 9;
        unsigned int CONF : 4;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_FD_RESULT_LS_UNION;
#endif
#define SOC_ISP_FD_RESULT_LS_SIZE_START (0)
#define SOC_ISP_FD_RESULT_LS_SIZE_END (8)
#define SOC_ISP_FD_RESULT_LS_CONF_START (9)
#define SOC_ISP_FD_RESULT_LS_CONF_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ANGLE : 9;
        unsigned int POSE : 3;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_FD_RESULT_ANGLE_UNION;
#endif
#define SOC_ISP_FD_RESULT_ANGLE_ANGLE_START (0)
#define SOC_ISP_FD_RESULT_ANGLE_ANGLE_END (8)
#define SOC_ISP_FD_RESULT_ANGLE_POSE_START (9)
#define SOC_ISP_FD_RESULT_ANGLE_POSE_END (11)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
