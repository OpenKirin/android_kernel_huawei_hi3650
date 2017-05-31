#ifndef __SOC_ISP_SHARPEN_INTERFACE_H__
#define __SOC_ISP_SHARPEN_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_SHARPEN_G33_0_ADDR(base) ((base) + (0x000))
#define SOC_ISP_SHARPEN_G33_1_ADDR(base) ((base) + (0x004))
#define SOC_ISP_SHARPEN_G33_2_ADDR(base) ((base) + (0x008))
#define SOC_ISP_SHARPEN_LINEDET_ADDR(base) ((base) + (0x00C))
#define SOC_ISP_SHARPEN_SHARPCFG_ADDR(base) ((base) + (0x010))
#define SOC_ISP_SHARPEN_EDGECFG_ADDR(base) ((base) + (0x014))
#define SOC_ISP_SHARPEN_SHOOTCFG_ADDR(base) ((base) + (0x018))
#define SOC_ISP_SHARPEN_SELCFG_ADDR(base) ((base) + (0x01C))
#define SOC_ISP_SHARPEN_HCROP_ADDR(base) ((base) + (0x020))
#define SOC_ISP_SHARPEN_VCROP_ADDR(base) ((base) + (0x024))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g0_0 : 8;
        unsigned int g0_1 : 8;
        unsigned int g0_2 : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_SHARPEN_G33_0_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_0_g0_0_START (0)
#define SOC_ISP_SHARPEN_G33_0_g0_0_END (7)
#define SOC_ISP_SHARPEN_G33_0_g0_1_START (8)
#define SOC_ISP_SHARPEN_G33_0_g0_1_END (15)
#define SOC_ISP_SHARPEN_G33_0_g0_2_START (16)
#define SOC_ISP_SHARPEN_G33_0_g0_2_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g1_0 : 8;
        unsigned int g1_1 : 8;
        unsigned int g1_2 : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_SHARPEN_G33_1_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_1_g1_0_START (0)
#define SOC_ISP_SHARPEN_G33_1_g1_0_END (7)
#define SOC_ISP_SHARPEN_G33_1_g1_1_START (8)
#define SOC_ISP_SHARPEN_G33_1_g1_1_END (15)
#define SOC_ISP_SHARPEN_G33_1_g1_2_START (16)
#define SOC_ISP_SHARPEN_G33_1_g1_2_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g2_0 : 8;
        unsigned int g2_1 : 8;
        unsigned int g2_2 : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_SHARPEN_G33_2_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_2_g2_0_START (0)
#define SOC_ISP_SHARPEN_G33_2_g2_0_END (7)
#define SOC_ISP_SHARPEN_G33_2_g2_1_START (8)
#define SOC_ISP_SHARPEN_G33_2_g2_1_END (15)
#define SOC_ISP_SHARPEN_G33_2_g2_2_START (16)
#define SOC_ISP_SHARPEN_G33_2_g2_2_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int linethd1 : 5;
        unsigned int reserved_0: 3;
        unsigned int linethd2 : 5;
        unsigned int reserved_1: 3;
        unsigned int lineamt1 : 12;
        unsigned int reserved_2: 3;
        unsigned int linedeten : 1;
    } reg;
} SOC_ISP_SHARPEN_LINEDET_UNION;
#endif
#define SOC_ISP_SHARPEN_LINEDET_linethd1_START (0)
#define SOC_ISP_SHARPEN_LINEDET_linethd1_END (4)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_START (8)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_END (12)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_START (16)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_END (27)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_START (31)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sharpamt1 : 12;
        unsigned int sharpthd1mul : 12;
        unsigned int sharpthd1 : 8;
    } reg;
} SOC_ISP_SHARPEN_SHARPCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_START (0)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_END (11)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_START (12)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_END (23)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_START (24)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int edgeamt1 : 12;
        unsigned int edgethd1mul : 12;
        unsigned int edgethd1 : 8;
    } reg;
} SOC_ISP_SHARPEN_EDGECFG_UNION;
#endif
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_START (0)
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_END (11)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_START (12)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_END (23)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_START (24)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int undershootamt : 8;
        unsigned int overshootamt : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_SHARPEN_SHOOTCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_START (0)
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_END (7)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_START (8)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hbfsel : 1;
        unsigned int edgecmp : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_SHARPEN_SELCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_START (0)
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_END (0)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_START (1)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihright : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_SHARPEN_HCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_HCROP_ihright_START (0)
#define SOC_ISP_SHARPEN_HCROP_ihright_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivbottom : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_SHARPEN_VCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_VCROP_ivbottom_START (0)
#define SOC_ISP_SHARPEN_VCROP_ivbottom_END (12)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
