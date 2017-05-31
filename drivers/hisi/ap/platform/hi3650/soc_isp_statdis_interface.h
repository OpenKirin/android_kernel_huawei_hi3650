#ifndef __SOC_ISP_STATDIS_INTERFACE_H__
#define __SOC_ISP_STATDIS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_STATDIS_DIS_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_STATDIS_RESTOREDONE_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_STATDIS_DIS_H_OFFS_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_STATDIS_DIS_V_OFFS_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_STATDIS_DIS_H_SIZE_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_STATDIS_DIS_V_SIZE_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_STATDIS_SRAM2_ADDR(base,Range2112) ((base) + (0x1000+0x4*(Range2112)))
#define SOC_ISP_STATDIS_SRAM4_ADDR(base,Range2496) ((base) + (0x4000+0x4*(Range2496)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 1;
        unsigned int irq_en : 1;
        unsigned int nb_zone : 1;
        unsigned int scm : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_STATDIS_DIS_CONFIG_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_CONFIG_enable_START (0)
#define SOC_ISP_STATDIS_DIS_CONFIG_enable_END (0)
#define SOC_ISP_STATDIS_DIS_CONFIG_irq_en_START (1)
#define SOC_ISP_STATDIS_DIS_CONFIG_irq_en_END (1)
#define SOC_ISP_STATDIS_DIS_CONFIG_nb_zone_START (2)
#define SOC_ISP_STATDIS_DIS_CONFIG_nb_zone_END (2)
#define SOC_ISP_STATDIS_DIS_CONFIG_scm_START (3)
#define SOC_ISP_STATDIS_DIS_CONFIG_scm_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int restoredone : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_STATDIS_RESTOREDONE_UNION;
#endif
#define SOC_ISP_STATDIS_RESTOREDONE_restoredone_START (0)
#define SOC_ISP_STATDIS_RESTOREDONE_restoredone_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int h_offs : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_OFFS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_OFFS_h_offs_START (0)
#define SOC_ISP_STATDIS_DIS_H_OFFS_h_offs_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_offs : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_V_OFFS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_OFFS_v_offs_START (0)
#define SOC_ISP_STATDIS_DIS_V_OFFS_v_offs_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int h_size : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_SIZE_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_SIZE_h_size_START (0)
#define SOC_ISP_STATDIS_DIS_H_SIZE_h_size_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_size : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_STATDIS_DIS_V_SIZE_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_SIZE_v_size_START (0)
#define SOC_ISP_STATDIS_DIS_V_SIZE_v_size_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int h_segments : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_ISP_STATDIS_DIS_H_SEGMENTS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_h_segments_START (0)
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_h_segments_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_segments : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_ISP_STATDIS_DIS_V_SEGMENTS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_v_segments_START (0)
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_v_segments_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_h_0 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_0_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_delta_h_0_START (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_delta_h_0_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_v_0 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_0_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_delta_v_0_START (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_delta_v_0_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_h_1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_1_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_delta_h_1_START (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_delta_h_1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_v_1 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_1_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_delta_v_1_START (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_delta_v_1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_h_2 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_2_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_delta_h_2_START (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_delta_h_2_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_v_2 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_2_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_delta_v_2_START (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_delta_v_2_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_h_3 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_3_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_delta_h_3_START (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_delta_h_3_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delta_v_3 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_3_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_delta_v_3_START (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_delta_v_3_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_proj : 32;
    } reg;
} SOC_ISP_STATDIS_SRAM2_UNION;
#endif
#define SOC_ISP_STATDIS_SRAM2_x_proj_START (0)
#define SOC_ISP_STATDIS_SRAM2_x_proj_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_proj : 32;
    } reg;
} SOC_ISP_STATDIS_SRAM4_UNION;
#endif
#define SOC_ISP_STATDIS_SRAM4_y_proj_START (0)
#define SOC_ISP_STATDIS_SRAM4_y_proj_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
