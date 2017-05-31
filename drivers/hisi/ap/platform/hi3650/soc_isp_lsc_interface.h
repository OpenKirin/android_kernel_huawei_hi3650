#ifndef __SOC_ISP_LSC_INTERFACE_H__
#define __SOC_ISP_LSC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_LSC_LSC_CTRL_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_LSC_LSC_XGRAD_0_1_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_LSC_LSC_XGRAD_2_3_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_LSC_LSC_XGRAD_4_5_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_LSC_LSC_XGRAD_6_7_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_LSC_LSC_XGRAD_8_9_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_LSC_LSC_XGRAD_10_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_LSC_LSC_XSIZE_0_1_ADDR(base) ((base) + (0x004C))
#define SOC_ISP_LSC_LSC_XSIZE_2_3_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_LSC_LSC_XSIZE_4_5_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_LSC_LSC_XSIZE_6_7_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_LSC_LSC_XSIZE_8_9_ADDR(base) ((base) + (0x005C))
#define SOC_ISP_LSC_LSC_XSIZE_10_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_LSC_LSC_YSIZE_0_1_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_LSC_LSC_YSIZE_2_3_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_LSC_LSC_YSIZE_4_5_ADDR(base) ((base) + (0x006C))
#define SOC_ISP_LSC_LSC_YSIZE_6_7_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_LSC_LSC_TABLE_SEL_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_LSC_LSC_STATUS_ADDR(base) ((base) + (0x0078))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lsc_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_LSC_LSC_CTRL_UNION;
#endif
#define SOC_ISP_LSC_LSC_CTRL_lsc_en_START (0)
#define SOC_ISP_LSC_LSC_CTRL_lsc_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r_ram_addr : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_LSC_LSC_R_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_r_ram_addr_START (0)
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_r_ram_addr_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gr_ram_addr : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_LSC_LSC_GR_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_gr_ram_addr_START (0)
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_gr_ram_addr_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_ram_addr : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_LSC_LSC_B_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_b_ram_addr_START (0)
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_b_ram_addr_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gb_ram_addr : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_LSC_LSC_GB_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_gb_ram_addr_START (0)
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_gb_ram_addr_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r_sample_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int r_sample_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_LSC_LSC_R_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_0_START (0)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_0_END (12)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_1_START (16)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gr_sample_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int gr_sample_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_LSC_LSC_GR_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_0_START (0)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_0_END (12)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_1_START (16)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_sample_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int b_sample_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_LSC_LSC_B_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_0_START (0)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_0_END (12)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_1_START (16)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gb_sample_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int gb_sample_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_LSC_LSC_GB_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_0_START (0)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_0_END (12)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_1_START (16)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_0 : 12;
        unsigned int reserved_0: 4;
        unsigned int xgrad_1 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_0_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_0_END (11)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_1_START (16)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_1_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_2 : 12;
        unsigned int reserved_0: 4;
        unsigned int xgrad_3 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_2_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_2_END (11)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_3_START (16)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_3_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_4 : 12;
        unsigned int reserved_0: 4;
        unsigned int xgrad_5 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_4_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_4_END (11)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_5_START (16)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_5_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_6 : 12;
        unsigned int reserved_0: 4;
        unsigned int xgrad_7 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_6_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_6_END (11)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_7_START (16)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_7_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_8 : 12;
        unsigned int reserved_0: 4;
        unsigned int xgrad_9 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_8_9_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_8_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_8_END (11)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_9_START (16)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_9_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xgrad_10 : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_10_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_10_xgrad_10_START (0)
#define SOC_ISP_LSC_LSC_XGRAD_10_xgrad_10_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ygrad_0 : 12;
        unsigned int reserved_0: 4;
        unsigned int ygrad_1 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_0_START (0)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_0_END (11)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_1_START (16)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_1_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ygrad_2 : 12;
        unsigned int reserved_0: 4;
        unsigned int ygrad_3 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_2_START (0)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_2_END (11)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_3_START (16)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_3_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ygrad_4 : 12;
        unsigned int reserved_0: 4;
        unsigned int ygrad_5 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_4_START (0)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_4_END (11)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_5_START (16)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_5_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ygrad_6 : 12;
        unsigned int reserved_0: 4;
        unsigned int ygrad_7 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_6_START (0)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_6_END (11)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_7_START (16)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_7_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_0 : 10;
        unsigned int reserved_0 : 6;
        unsigned int x_sect_size_1 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_0_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_0_END (9)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_1_START (16)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_2 : 10;
        unsigned int reserved_0 : 6;
        unsigned int x_sect_size_3 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_2_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_2_END (9)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_3_START (16)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_4 : 10;
        unsigned int reserved_0 : 6;
        unsigned int x_sect_size_5 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_4_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_4_END (9)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_5_START (16)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_5_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_6 : 10;
        unsigned int reserved_0 : 6;
        unsigned int x_sect_size_7 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_6_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_6_END (9)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_7_START (16)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_7_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_8 : 10;
        unsigned int reserved_0 : 6;
        unsigned int x_sect_size_9 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_8_9_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_8_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_8_END (9)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_9_START (16)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_9_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_sect_size_10 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_10_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_10_x_sect_size_10_START (0)
#define SOC_ISP_LSC_LSC_XSIZE_10_x_sect_size_10_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_sect_size_0 : 10;
        unsigned int reserved_0 : 6;
        unsigned int y_sect_size_1 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_0_START (0)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_0_END (9)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_1_START (16)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_sect_size_2 : 10;
        unsigned int reserved_0 : 6;
        unsigned int y_sect_size_3 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_2_START (0)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_2_END (9)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_3_START (16)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_sect_size_4 : 10;
        unsigned int reserved_0 : 6;
        unsigned int y_sect_size_5 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_4_START (0)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_4_END (9)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_5_START (16)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_5_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_sect_size_6 : 10;
        unsigned int reserved_0 : 6;
        unsigned int y_sect_size_7 : 10;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_6_START (0)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_6_END (9)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_7_START (16)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_7_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int table_select : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_LSC_LSC_TABLE_SEL_UNION;
#endif
#define SOC_ISP_LSC_LSC_TABLE_SEL_table_select_START (0)
#define SOC_ISP_LSC_LSC_TABLE_SEL_table_select_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lsc_en_status : 1;
        unsigned int active_table : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_LSC_LSC_STATUS_UNION;
#endif
#define SOC_ISP_LSC_LSC_STATUS_lsc_en_status_START (0)
#define SOC_ISP_LSC_LSC_STATUS_lsc_en_status_END (0)
#define SOC_ISP_LSC_LSC_STATUS_active_table_START (1)
#define SOC_ISP_LSC_LSC_STATUS_active_table_END (1)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
