#ifndef __SOC_ISP_SCALER_INTERFACE_H__
#define __SOC_ISP_SCALER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_SCALER_IHLEFT_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_SCALER_IHRIGHT_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_SCALER_UV_HOFFSET_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_SCALER_IVTOP_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_SCALER_IVBOTTOM_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_SCALER_UV_VOFFSET_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_SCALER_IHINC_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_SCALER_IVINC_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_SCALER_BYPASS_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_SCALER_FORMAT_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_SCALER_OVERRIDEH_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_SCALER_OVERRIDEV_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_SCALER_IH_HPOS_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_SCALER_IV_HPOS_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_SCALER_IH_VPOS_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_SCALER_IV_VPOS_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x50))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihleft : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_SCALER_IHLEFT_UNION;
#endif
#define SOC_ISP_SCALER_IHLEFT_ihleft_START (0)
#define SOC_ISP_SCALER_IHLEFT_ihleft_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihright : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_SCALER_IHRIGHT_UNION;
#endif
#define SOC_ISP_SCALER_IHRIGHT_ihright_START (0)
#define SOC_ISP_SCALER_IHRIGHT_ihright_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int uv_hoffset : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_SCALER_UV_HOFFSET_UNION;
#endif
#define SOC_ISP_SCALER_UV_HOFFSET_uv_hoffset_START (0)
#define SOC_ISP_SCALER_UV_HOFFSET_uv_hoffset_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivtop : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_SCALER_IVTOP_UNION;
#endif
#define SOC_ISP_SCALER_IVTOP_ivtop_START (0)
#define SOC_ISP_SCALER_IVTOP_ivtop_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivbottom : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_SCALER_IVBOTTOM_UNION;
#endif
#define SOC_ISP_SCALER_IVBOTTOM_ivbottom_START (0)
#define SOC_ISP_SCALER_IVBOTTOM_ivbottom_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int uv_voffset : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_SCALER_UV_VOFFSET_UNION;
#endif
#define SOC_ISP_SCALER_UV_VOFFSET_uv_voffset_START (0)
#define SOC_ISP_SCALER_UV_VOFFSET_uv_voffset_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihinc : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_SCALER_IHINC_UNION;
#endif
#define SOC_ISP_SCALER_IHINC_ihinc_START (0)
#define SOC_ISP_SCALER_IHINC_ihinc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivinc : 20;
        unsigned int halflinemode : 1;
        unsigned int reserved : 11;
    } reg;
} SOC_ISP_SCALER_IVINC_UNION;
#endif
#define SOC_ISP_SCALER_IVINC_ivinc_START (0)
#define SOC_ISP_SCALER_IVINC_ivinc_END (19)
#define SOC_ISP_SCALER_IVINC_halflinemode_START (20)
#define SOC_ISP_SCALER_IVINC_halflinemode_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_SCALER_BYPASS_UNION;
#endif
#define SOC_ISP_SCALER_BYPASS_bypass_START (0)
#define SOC_ISP_SCALER_BYPASS_bypass_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int outformat : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_SCALER_FORMAT_UNION;
#endif
#define SOC_ISP_SCALER_FORMAT_outformat_START (0)
#define SOC_ISP_SCALER_FORMAT_outformat_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int h_overrideid : 8;
        unsigned int h_overridephase : 4;
        unsigned int reserved_0 : 4;
        unsigned int h_id_overrideen : 1;
        unsigned int h_ph_overrideen : 1;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_ISP_SCALER_OVERRIDEH_UNION;
#endif
#define SOC_ISP_SCALER_OVERRIDEH_h_overrideid_START (0)
#define SOC_ISP_SCALER_OVERRIDEH_h_overrideid_END (7)
#define SOC_ISP_SCALER_OVERRIDEH_h_overridephase_START (8)
#define SOC_ISP_SCALER_OVERRIDEH_h_overridephase_END (11)
#define SOC_ISP_SCALER_OVERRIDEH_h_id_overrideen_START (16)
#define SOC_ISP_SCALER_OVERRIDEH_h_id_overrideen_END (16)
#define SOC_ISP_SCALER_OVERRIDEH_h_ph_overrideen_START (17)
#define SOC_ISP_SCALER_OVERRIDEH_h_ph_overrideen_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_overrideid : 4;
        unsigned int v_overridephase : 4;
        unsigned int reserved_0 : 8;
        unsigned int v_id_overrideen : 1;
        unsigned int v_ph_overrideen : 1;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_ISP_SCALER_OVERRIDEV_UNION;
#endif
#define SOC_ISP_SCALER_OVERRIDEV_v_overrideid_START (0)
#define SOC_ISP_SCALER_OVERRIDEV_v_overrideid_END (3)
#define SOC_ISP_SCALER_OVERRIDEV_v_overridephase_START (4)
#define SOC_ISP_SCALER_OVERRIDEV_v_overridephase_END (7)
#define SOC_ISP_SCALER_OVERRIDEV_v_id_overrideen_START (16)
#define SOC_ISP_SCALER_OVERRIDEV_v_id_overrideen_END (16)
#define SOC_ISP_SCALER_OVERRIDEV_v_ph_overrideen_START (17)
#define SOC_ISP_SCALER_OVERRIDEV_v_ph_overrideen_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ih_hpos : 32;
    } reg;
} SOC_ISP_SCALER_IH_HPOS_UNION;
#endif
#define SOC_ISP_SCALER_IH_HPOS_ih_hpos_START (0)
#define SOC_ISP_SCALER_IH_HPOS_ih_hpos_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iv_hpos : 32;
    } reg;
} SOC_ISP_SCALER_IV_HPOS_UNION;
#endif
#define SOC_ISP_SCALER_IV_HPOS_iv_hpos_START (0)
#define SOC_ISP_SCALER_IV_HPOS_iv_hpos_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ih_vpos : 32;
    } reg;
} SOC_ISP_SCALER_IH_VPOS_UNION;
#endif
#define SOC_ISP_SCALER_IH_VPOS_ih_vpos_START (0)
#define SOC_ISP_SCALER_IH_VPOS_ih_vpos_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iv_vpos : 32;
    } reg;
} SOC_ISP_SCALER_IV_VPOS_UNION;
#endif
#define SOC_ISP_SCALER_IV_VPOS_iv_vpos_START (0)
#define SOC_ISP_SCALER_IV_VPOS_iv_vpos_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_clk_on : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_SCALER_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_force_clk_on_START (0)
#define SOC_ISP_SCALER_FORCE_CLK_ON_CFG_force_clk_on_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
