#ifndef __SOC_ISP_STAT3A_INTERFACE_H__
#define __SOC_ISP_STAT3A_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_STAT3A_STAT3A_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_STAT3A_STAT3A_STATUS_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_STAT3A_GKM_CROPLR_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_STAT3A_GKM_CROPTB_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_STAT3A_FW_X_0_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_STAT3A_FW_Y_0_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_STAT3A_FW_X_1_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_STAT3A_FW_Y_1_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_STAT3A_FW_X_2_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_STAT3A_FW_Y_2_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_STAT3A_FW_X_3_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_STAT3A_FW_Y_3_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_STAT3A_FW_X_4_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_STAT3A_FW_Y_4_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_STAT3A_FW_X_5_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_STAT3A_FW_Y_5_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_STAT3A_FW_X_6_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_STAT3A_FW_Y_6_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_STAT3A_FW_X_7_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_STAT3A_FW_Y_7_ADDR(base) ((base) + (0x004C))
#define SOC_ISP_STAT3A_FW_X_8_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_STAT3A_FW_Y_8_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_STAT3A_HIST_X_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_STAT3A_HIST_Y_ADDR(base) ((base) + (0x005C))
#define SOC_ISP_STAT3A_AF_PARAM_1_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_STAT3A_Y_C0_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_STAT3A_Y_C1_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_STAT3A_Y_C2_ADDR(base) ((base) + (0x006C))
#define SOC_ISP_STAT3A_Y_C3_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_STAT3A_Y_C4_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_STAT3A_Y_C5_ADDR(base) ((base) + (0x0078))
#define SOC_ISP_STAT3A_Y_C6_ADDR(base) ((base) + (0x007C))
#define SOC_ISP_STAT3A_Y_C7_ADDR(base) ((base) + (0x0080))
#define SOC_ISP_STAT3A_Y_C8_ADDR(base) ((base) + (0x0084))
#define SOC_ISP_STAT3A_Y_C9_ADDR(base) ((base) + (0x0088))
#define SOC_ISP_STAT3A_BLOCKNUM_ADDR(base) ((base) + (0x008C))
#define SOC_ISP_STAT3A_BLOCKWIN_ADDR(base) ((base) + (0x000090))
#define SOC_ISP_STAT3A_COLUMNOFFSET_ADDR(base) ((base) + (0x0094))
#define SOC_ISP_STAT3A_BINTHD_ADDR(base) ((base) + (0x0098))
#define SOC_ISP_STAT3A_LOCATIONROI01_ADDR(base) ((base) + (0x009C))
#define SOC_ISP_STAT3A_LOCATIONROI23_ADDR(base) ((base) + (0x00A0))
#define SOC_ISP_STAT3A_LOCATIONROI45_ADDR(base) ((base) + (0x00A4))
#define SOC_ISP_STAT3A_LOCATIONROI67_ADDR(base) ((base) + (0x00A8))
#define SOC_ISP_STAT3A_LOCATIONROI89_ADDR(base) ((base) + (0x00AC))
#define SOC_ISP_STAT3A_SIZEROI01_ADDR(base) ((base) + (0x00B0))
#define SOC_ISP_STAT3A_SIZEROI23_ADDR(base) ((base) + (0x00B4))
#define SOC_ISP_STAT3A_SIZEROI45_ADDR(base) ((base) + (0x00B8))
#define SOC_ISP_STAT3A_SIZEROI67_ADDR(base) ((base) + (0x00BC))
#define SOC_ISP_STAT3A_SIZEROI8_ADDR(base) ((base) + (0x00C0))
#define SOC_ISP_STAT3A_COLORVALUE_ADDR(base) ((base) + (0x00C4))
#define SOC_ISP_STAT3A_GRAYZONETOP_ADDR(base) ((base) + (0x00C8))
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_ADDR(base) ((base) + (0x00CC))
#define SOC_ISP_STAT3A_GRAYZONELEFT_ADDR(base) ((base) + (0x00D0))
#define SOC_ISP_STAT3A_GRAYZONERIGHT_ADDR(base) ((base) + (0x00D4))
#define SOC_ISP_STAT3A_GREENLUMAVALUE_ADDR(base) ((base) + (0x00D8))
#define SOC_ISP_STAT3A_GREENCEN_ADDR(base) ((base) + (0x00DC))
#define SOC_ISP_STAT3A_GREENDISTCOEF_ADDR(base) ((base) + (0x00E0))
#define SOC_ISP_STAT3A_GREENDIST_ADDR(base) ((base) + (0x00E4))
#define SOC_ISP_STAT3A_RGBHIST_ADDR(base) ((base) + (0x00E8))
#define SOC_ISP_STAT3A_PREGAIN_ADDR(base) ((base) + (0x00EC))
#define SOC_ISP_STAT3A_LUMACOEF_ADDR(base) ((base) + (0x00F0))
#define SOC_ISP_STAT3A_AF_PARAM_2_ADDR(base) ((base) + (0x00F4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 1;
        unsigned int irq_en : 1;
        unsigned int scm : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_STAT3A_STAT3A_CONFIG_UNION;
#endif
#define SOC_ISP_STAT3A_STAT3A_CONFIG_enable_START (0)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_enable_END (0)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_irq_en_START (1)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_irq_en_END (1)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_scm_START (2)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_scm_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int state : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_STAT3A_STAT3A_STATUS_UNION;
#endif
#define SOC_ISP_STAT3A_STAT3A_STATUS_state_START (0)
#define SOC_ISP_STAT3A_STAT3A_STATUS_state_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cleft : 13;
        unsigned int reserved_0: 3;
        unsigned int cright : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_STAT3A_GKM_CROPLR_UNION;
#endif
#define SOC_ISP_STAT3A_GKM_CROPLR_cleft_START (0)
#define SOC_ISP_STAT3A_GKM_CROPLR_cleft_END (12)
#define SOC_ISP_STAT3A_GKM_CROPLR_cright_START (16)
#define SOC_ISP_STAT3A_GKM_CROPLR_cright_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctop : 13;
        unsigned int reserved_0: 3;
        unsigned int cbottom : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_STAT3A_GKM_CROPTB_UNION;
#endif
#define SOC_ISP_STAT3A_GKM_CROPTB_ctop_START (0)
#define SOC_ISP_STAT3A_GKM_CROPTB_ctop_END (12)
#define SOC_ISP_STAT3A_GKM_CROPTB_cbottom_START (16)
#define SOC_ISP_STAT3A_GKM_CROPTB_cbottom_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_0 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_0_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_0_fw_x_strt_0_START (0)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_strt_0_END (12)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_width_0_START (16)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_width_0_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_0 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_0_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_strt_0_START (0)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_strt_0_END (12)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_width_0_START (16)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_width_0_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_1 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_1_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_1_fw_x_strt_1_START (0)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_strt_1_END (12)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_width_1_START (16)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_width_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_1 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_1_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_strt_1_START (0)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_strt_1_END (12)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_width_1_START (16)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_width_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_2 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_2 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_2_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_2_fw_x_strt_2_START (0)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_strt_2_END (12)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_width_2_START (16)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_width_2_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_2 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_2 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_2_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_strt_2_START (0)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_strt_2_END (12)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_width_2_START (16)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_width_2_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_3 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_3 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_3_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_3_fw_x_strt_3_START (0)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_strt_3_END (12)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_width_3_START (16)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_width_3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_3 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_3 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_3_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_strt_3_START (0)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_strt_3_END (12)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_width_3_START (16)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_width_3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_4 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_4 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_4_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_4_fw_x_strt_4_START (0)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_strt_4_END (12)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_width_4_START (16)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_width_4_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_4 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_4 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_4_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_strt_4_START (0)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_strt_4_END (12)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_width_4_START (16)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_width_4_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_5 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_5 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_5_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_5_fw_x_strt_5_START (0)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_strt_5_END (12)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_width_5_START (16)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_width_5_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_5 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_5 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_5_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_strt_5_START (0)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_strt_5_END (12)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_width_5_START (16)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_width_5_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_6 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_6 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_6_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_6_fw_x_strt_6_START (0)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_strt_6_END (12)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_width_6_START (16)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_width_6_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_6 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_6 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_6_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_strt_6_START (0)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_strt_6_END (12)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_width_6_START (16)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_width_6_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_7 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_7 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_7_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_7_fw_x_strt_7_START (0)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_strt_7_END (12)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_width_7_START (16)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_width_7_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_7 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_7 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_7_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_strt_7_START (0)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_strt_7_END (12)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_width_7_START (16)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_width_7_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_x_strt_8 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_x_width_8 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_X_8_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_8_fw_x_strt_8_START (0)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_strt_8_END (12)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_width_8_START (16)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_width_8_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fw_y_strt_8 : 13;
        unsigned int reserved_0 : 3;
        unsigned int fw_y_width_8 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_FW_Y_8_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_strt_8_START (0)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_strt_8_END (12)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_width_8_START (16)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_width_8_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hist_x_strt : 13;
        unsigned int reserved_0 : 3;
        unsigned int hist_x_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_HIST_X_UNION;
#endif
#define SOC_ISP_STAT3A_HIST_X_hist_x_strt_START (0)
#define SOC_ISP_STAT3A_HIST_X_hist_x_strt_END (12)
#define SOC_ISP_STAT3A_HIST_X_hist_x_width_START (16)
#define SOC_ISP_STAT3A_HIST_X_hist_x_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hist_y_strt : 13;
        unsigned int reserved_0 : 3;
        unsigned int hist_y_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_HIST_Y_UNION;
#endif
#define SOC_ISP_STAT3A_HIST_Y_hist_y_strt_START (0)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_strt_END (12)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_width_START (16)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thld : 24;
        unsigned int thld_en : 1;
        unsigned int fdog_dog : 1;
        unsigned int square_en : 1;
        unsigned int reserved : 3;
        unsigned int grad_sel : 2;
    } reg;
} SOC_ISP_STAT3A_AF_PARAM_1_UNION;
#endif
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_START (0)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_END (23)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_en_START (24)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_en_END (24)
#define SOC_ISP_STAT3A_AF_PARAM_1_fdog_dog_START (25)
#define SOC_ISP_STAT3A_AF_PARAM_1_fdog_dog_END (25)
#define SOC_ISP_STAT3A_AF_PARAM_1_square_en_START (26)
#define SOC_ISP_STAT3A_AF_PARAM_1_square_en_END (26)
#define SOC_ISP_STAT3A_AF_PARAM_1_grad_sel_START (30)
#define SOC_ISP_STAT3A_AF_PARAM_1_grad_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c00 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c01 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C0_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C0_flt_c00_START (0)
#define SOC_ISP_STAT3A_Y_C0_flt_c00_END (8)
#define SOC_ISP_STAT3A_Y_C0_flt_c01_START (16)
#define SOC_ISP_STAT3A_Y_C0_flt_c01_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c02 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c03 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C1_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C1_flt_c02_START (0)
#define SOC_ISP_STAT3A_Y_C1_flt_c02_END (8)
#define SOC_ISP_STAT3A_Y_C1_flt_c03_START (16)
#define SOC_ISP_STAT3A_Y_C1_flt_c03_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c04 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c10 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C2_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C2_flt_c04_START (0)
#define SOC_ISP_STAT3A_Y_C2_flt_c04_END (8)
#define SOC_ISP_STAT3A_Y_C2_flt_c10_START (16)
#define SOC_ISP_STAT3A_Y_C2_flt_c10_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c11 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c12 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C3_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C3_flt_c11_START (0)
#define SOC_ISP_STAT3A_Y_C3_flt_c11_END (8)
#define SOC_ISP_STAT3A_Y_C3_flt_c12_START (16)
#define SOC_ISP_STAT3A_Y_C3_flt_c12_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c13 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c14 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C4_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C4_flt_c13_START (0)
#define SOC_ISP_STAT3A_Y_C4_flt_c13_END (8)
#define SOC_ISP_STAT3A_Y_C4_flt_c14_START (16)
#define SOC_ISP_STAT3A_Y_C4_flt_c14_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c20 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c21 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C5_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C5_flt_c20_START (0)
#define SOC_ISP_STAT3A_Y_C5_flt_c20_END (8)
#define SOC_ISP_STAT3A_Y_C5_flt_c21_START (16)
#define SOC_ISP_STAT3A_Y_C5_flt_c21_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c22 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c23 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C6_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C6_flt_c22_START (0)
#define SOC_ISP_STAT3A_Y_C6_flt_c22_END (8)
#define SOC_ISP_STAT3A_Y_C6_flt_c23_START (16)
#define SOC_ISP_STAT3A_Y_C6_flt_c23_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c24 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c30 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C7_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C7_flt_c24_START (0)
#define SOC_ISP_STAT3A_Y_C7_flt_c24_END (8)
#define SOC_ISP_STAT3A_Y_C7_flt_c30_START (16)
#define SOC_ISP_STAT3A_Y_C7_flt_c30_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c31 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c32 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C8_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C8_flt_c31_START (0)
#define SOC_ISP_STAT3A_Y_C8_flt_c31_END (8)
#define SOC_ISP_STAT3A_Y_C8_flt_c32_START (16)
#define SOC_ISP_STAT3A_Y_C8_flt_c32_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flt_c33 : 9;
        unsigned int reserved_0: 7;
        unsigned int flt_c34 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_STAT3A_Y_C9_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C9_flt_c33_START (0)
#define SOC_ISP_STAT3A_Y_C9_flt_c33_END (8)
#define SOC_ISP_STAT3A_Y_C9_flt_c34_START (16)
#define SOC_ISP_STAT3A_Y_C9_flt_c34_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int numv : 5;
        unsigned int reserved_0: 11;
        unsigned int numh : 5;
        unsigned int reserved_1: 11;
    } reg;
} SOC_ISP_STAT3A_BLOCKNUM_UNION;
#endif
#define SOC_ISP_STAT3A_BLOCKNUM_numv_START (0)
#define SOC_ISP_STAT3A_BLOCKNUM_numv_END (4)
#define SOC_ISP_STAT3A_BLOCKNUM_numh_START (16)
#define SOC_ISP_STAT3A_BLOCKNUM_numh_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int winv : 10;
        unsigned int reserved_0: 6;
        unsigned int winh : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_BLOCKWIN_UNION;
#endif
#define SOC_ISP_STAT3A_BLOCKWIN_winv_START (0)
#define SOC_ISP_STAT3A_BLOCKWIN_winv_END (9)
#define SOC_ISP_STAT3A_BLOCKWIN_winh_START (16)
#define SOC_ISP_STAT3A_BLOCKWIN_winh_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int startcol : 12;
        unsigned int reserved_0: 4;
        unsigned int endcol : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_STAT3A_COLUMNOFFSET_UNION;
#endif
#define SOC_ISP_STAT3A_COLUMNOFFSET_startcol_START (0)
#define SOC_ISP_STAT3A_COLUMNOFFSET_startcol_END (11)
#define SOC_ISP_STAT3A_COLUMNOFFSET_endcol_START (16)
#define SOC_ISP_STAT3A_COLUMNOFFSET_endcol_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bin01thd : 12;
        unsigned int reserved_0: 4;
        unsigned int bin23thd : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_STAT3A_BINTHD_UNION;
#endif
#define SOC_ISP_STAT3A_BINTHD_bin01thd_START (0)
#define SOC_ISP_STAT3A_BINTHD_bin01thd_END (11)
#define SOC_ISP_STAT3A_BINTHD_bin23thd_START (16)
#define SOC_ISP_STAT3A_BINTHD_bin23thd_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int locationroi_0 : 13;
        unsigned int reserved_0 : 3;
        unsigned int locationroi_1 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI01_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_0_START (0)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_0_END (12)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_1_START (16)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int locationroi_2 : 13;
        unsigned int reserved_0 : 3;
        unsigned int locationroi_3 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI23_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_2_START (0)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_2_END (12)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_3_START (16)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int locationroi_4 : 13;
        unsigned int reserved_0 : 3;
        unsigned int locationroi_5 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI45_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_4_START (0)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_4_END (12)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_5_START (16)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_5_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int locationroi_6 : 13;
        unsigned int reserved_0 : 3;
        unsigned int locationroi_7 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI67_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_6_START (0)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_6_END (12)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_7_START (16)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_7_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int locationroi_8 : 13;
        unsigned int reserved_0 : 3;
        unsigned int locationroi_9 : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI89_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_8_START (0)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_8_END (12)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_9_START (16)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_9_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sizeroi_0 : 10;
        unsigned int reserved_0: 6;
        unsigned int sizeroi_1 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_SIZEROI01_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_0_START (0)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_0_END (9)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_1_START (16)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sizeroi_2 : 10;
        unsigned int reserved_0: 6;
        unsigned int sizeroi_3 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_SIZEROI23_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_2_START (0)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_2_END (9)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_3_START (16)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sizeroi_4 : 10;
        unsigned int reserved_0: 6;
        unsigned int sizeroi_5 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_SIZEROI45_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_4_START (0)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_4_END (9)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_5_START (16)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_5_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sizeroi_6 : 10;
        unsigned int reserved_0: 6;
        unsigned int sizeroi_7 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_SIZEROI67_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_6_START (0)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_6_END (9)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_7_START (16)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_7_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sizeroi_8 : 10;
        unsigned int reserved_0: 6;
        unsigned int sizeroi_h : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_STAT3A_SIZEROI8_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_8_START (0)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_8_END (9)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_h_START (16)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_h_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int maxcolorvalue : 12;
        unsigned int reserved_0 : 4;
        unsigned int mincolorvalue : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_ISP_STAT3A_COLORVALUE_UNION;
#endif
#define SOC_ISP_STAT3A_COLORVALUE_maxcolorvalue_START (0)
#define SOC_ISP_STAT3A_COLORVALUE_maxcolorvalue_END (11)
#define SOC_ISP_STAT3A_COLORVALUE_mincolorvalue_START (16)
#define SOC_ISP_STAT3A_COLORVALUE_mincolorvalue_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int topk : 14;
        unsigned int reserved_0: 2;
        unsigned int topb : 14;
        unsigned int reserved_1: 2;
    } reg;
} SOC_ISP_STAT3A_GRAYZONETOP_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONETOP_topk_START (0)
#define SOC_ISP_STAT3A_GRAYZONETOP_topk_END (13)
#define SOC_ISP_STAT3A_GRAYZONETOP_topb_START (16)
#define SOC_ISP_STAT3A_GRAYZONETOP_topb_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bottomk : 14;
        unsigned int reserved_0: 2;
        unsigned int bottomb : 14;
        unsigned int reserved_1: 2;
    } reg;
} SOC_ISP_STAT3A_GRAYZONEBOTTOM_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomk_START (0)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomk_END (13)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomb_START (16)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomb_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int leftk : 14;
        unsigned int reserved_0: 2;
        unsigned int leftb : 14;
        unsigned int reserved_1: 2;
    } reg;
} SOC_ISP_STAT3A_GRAYZONELEFT_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftk_START (0)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftk_END (13)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftb_START (16)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftb_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rightk : 14;
        unsigned int reserved_0: 2;
        unsigned int rightb : 14;
        unsigned int reserved_1: 2;
    } reg;
} SOC_ISP_STAT3A_GRAYZONERIGHT_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightk_START (0)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightk_END (13)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightb_START (16)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightb_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int maxvalue : 12;
        unsigned int reserved_0: 4;
        unsigned int minvalue : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_STAT3A_GREENLUMAVALUE_UNION;
#endif
#define SOC_ISP_STAT3A_GREENLUMAVALUE_maxvalue_START (0)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_maxvalue_END (11)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_minvalue_START (16)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_minvalue_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int greencenrg : 12;
        unsigned int reserved_0 : 4;
        unsigned int greencnbg : 12;
        unsigned int reserved_1 : 4;
    } reg;
} SOC_ISP_STAT3A_GREENCEN_UNION;
#endif
#define SOC_ISP_STAT3A_GREENCEN_greencenrg_START (0)
#define SOC_ISP_STAT3A_GREENCEN_greencenrg_END (11)
#define SOC_ISP_STAT3A_GREENCEN_greencnbg_START (16)
#define SOC_ISP_STAT3A_GREENCEN_greencnbg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int greendistrg : 16;
        unsigned int greendistbg : 16;
    } reg;
} SOC_ISP_STAT3A_GREENDISTCOEF_UNION;
#endif
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistrg_START (0)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistrg_END (15)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistbg_START (16)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crosscoef : 16;
        unsigned int thresh : 12;
        unsigned int reserved : 4;
    } reg;
} SOC_ISP_STAT3A_GREENDIST_UNION;
#endif
#define SOC_ISP_STAT3A_GREENDIST_crosscoef_START (0)
#define SOC_ISP_STAT3A_GREENDIST_crosscoef_END (15)
#define SOC_ISP_STAT3A_GREENDIST_thresh_START (16)
#define SOC_ISP_STAT3A_GREENDIST_thresh_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rgbhistmin : 12;
        unsigned int reserved_0 : 4;
        unsigned int rgbhistshift : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_ISP_STAT3A_RGBHIST_UNION;
#endif
#define SOC_ISP_STAT3A_RGBHIST_rgbhistmin_START (0)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistmin_END (11)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistshift_START (16)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistshift_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rgpregain : 12;
        unsigned int reserved_0: 4;
        unsigned int bgpregain : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_STAT3A_PREGAIN_UNION;
#endif
#define SOC_ISP_STAT3A_PREGAIN_rgpregain_START (0)
#define SOC_ISP_STAT3A_PREGAIN_rgpregain_END (11)
#define SOC_ISP_STAT3A_PREGAIN_bgpregain_START (16)
#define SOC_ISP_STAT3A_PREGAIN_bgpregain_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rcoef : 8;
        unsigned int gcoef : 8;
        unsigned int bcoef : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_STAT3A_LUMACOEF_UNION;
#endif
#define SOC_ISP_STAT3A_LUMACOEF_rcoef_START (0)
#define SOC_ISP_STAT3A_LUMACOEF_rcoef_END (7)
#define SOC_ISP_STAT3A_LUMACOEF_gcoef_START (8)
#define SOC_ISP_STAT3A_LUMACOEF_gcoef_END (15)
#define SOC_ISP_STAT3A_LUMACOEF_bcoef_START (16)
#define SOC_ISP_STAT3A_LUMACOEF_bcoef_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hist_shft : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_STAT3A_AF_PARAM_2_UNION;
#endif
#define SOC_ISP_STAT3A_AF_PARAM_2_hist_shft_START (0)
#define SOC_ISP_STAT3A_AF_PARAM_2_hist_shft_END (3)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
