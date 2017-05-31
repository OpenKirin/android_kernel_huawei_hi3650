#ifndef __SOC_ISP_TNR_INTERFACE_H__
#define __SOC_ISP_TNR_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_TNR_CONFIG_ADDR(base) ((base) + (0x000))
#define SOC_ISP_TNR_THD_CFG_ADDR(base) ((base) + (0x004))
#define SOC_ISP_TNR_SLP_OFST_CFG_ADDR(base) ((base) + (0x008))
#define SOC_ISP_TNR_CROP_ADDR(base) ((base) + (0x00C))
#define SOC_ISP_TNR_LUMAA_ADDR(base) ((base) + (0x010))
#define SOC_ISP_TNR_LUMAB_ADDR(base) ((base) + (0x014))
#define SOC_ISP_TNR_LUMAC_ADDR(base) ((base) + (0x018))
#define SOC_ISP_TNR_LUMAD_ADDR(base) ((base) + (0x01C))
#define SOC_ISP_TNR_LUMAE_ADDR(base) ((base) + (0x020))
#define SOC_ISP_TNR_MOTIONUVA_ADDR(base) ((base) + (0x024))
#define SOC_ISP_TNR_MOTIONUVB_ADDR(base) ((base) + (0x028))
#define SOC_ISP_TNR_MOTIONUVC_ADDR(base) ((base) + (0x02C))
#define SOC_ISP_TNR_MOTIONUVD_ADDR(base) ((base) + (0x030))
#define SOC_ISP_TNR_MOTIONUVE_ADDR(base) ((base) + (0x034))
#define SOC_ISP_TNR_MOTIONUVF_ADDR(base) ((base) + (0x038))
#define SOC_ISP_TNR_MOTIONUVG_ADDR(base) ((base) + (0x03C))
#define SOC_ISP_TNR_MOTIONUVH_ADDR(base) ((base) + (0x040))
#define SOC_ISP_TNR_MOTIONA_ADDR(base) ((base) + (0x044))
#define SOC_ISP_TNR_MOTIONB_ADDR(base) ((base) + (0x048))
#define SOC_ISP_TNR_MOTIONC_ADDR(base) ((base) + (0x04C))
#define SOC_ISP_TNR_MOTIOND_ADDR(base) ((base) + (0x050))
#define SOC_ISP_TNR_MOTIONE_ADDR(base) ((base) + (0x054))
#define SOC_ISP_TNR_MOTIONF_ADDR(base) ((base) + (0x058))
#define SOC_ISP_TNR_MOTIONG_ADDR(base) ((base) + (0x05C))
#define SOC_ISP_TNR_MOTIONH_ADDR(base) ((base) + (0x060))
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x070))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TNR_CONFIG_UNION;
#endif
#define SOC_ISP_TNR_CONFIG_bypass_START (0)
#define SOC_ISP_TNR_CONFIG_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alpha_thd : 8;
        unsigned int motion_thd : 8;
        unsigned int global_thd : 11;
        unsigned int reserved : 5;
    } reg;
} SOC_ISP_TNR_THD_CFG_UNION;
#endif
#define SOC_ISP_TNR_THD_CFG_alpha_thd_START (0)
#define SOC_ISP_TNR_THD_CFG_alpha_thd_END (7)
#define SOC_ISP_TNR_THD_CFG_motion_thd_START (8)
#define SOC_ISP_TNR_THD_CFG_motion_thd_END (15)
#define SOC_ISP_TNR_THD_CFG_global_thd_START (16)
#define SOC_ISP_TNR_THD_CFG_global_thd_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int weight_slope : 2;
        unsigned int motion_slope : 6;
        unsigned int reserved_0 : 8;
        unsigned int local_offset_max : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_ISP_TNR_SLP_OFST_CFG_UNION;
#endif
#define SOC_ISP_TNR_SLP_OFST_CFG_weight_slope_START (0)
#define SOC_ISP_TNR_SLP_OFST_CFG_weight_slope_END (1)
#define SOC_ISP_TNR_SLP_OFST_CFG_motion_slope_START (2)
#define SOC_ISP_TNR_SLP_OFST_CFG_motion_slope_END (7)
#define SOC_ISP_TNR_SLP_OFST_CFG_local_offset_max_START (16)
#define SOC_ISP_TNR_SLP_OFST_CFG_local_offset_max_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihright : 13;
        unsigned int reserved_0: 3;
        unsigned int ivbottom : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_TNR_CROP_UNION;
#endif
#define SOC_ISP_TNR_CROP_ihright_START (0)
#define SOC_ISP_TNR_CROP_ihright_END (12)
#define SOC_ISP_TNR_CROP_ivbottom_START (16)
#define SOC_ISP_TNR_CROP_ivbottom_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma0 : 8;
        unsigned int luma1 : 8;
        unsigned int luma2 : 8;
        unsigned int luma3 : 8;
    } reg;
} SOC_ISP_TNR_LUMAA_UNION;
#endif
#define SOC_ISP_TNR_LUMAA_luma0_START (0)
#define SOC_ISP_TNR_LUMAA_luma0_END (7)
#define SOC_ISP_TNR_LUMAA_luma1_START (8)
#define SOC_ISP_TNR_LUMAA_luma1_END (15)
#define SOC_ISP_TNR_LUMAA_luma2_START (16)
#define SOC_ISP_TNR_LUMAA_luma2_END (23)
#define SOC_ISP_TNR_LUMAA_luma3_START (24)
#define SOC_ISP_TNR_LUMAA_luma3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma4 : 8;
        unsigned int luma5 : 8;
        unsigned int luma6 : 8;
        unsigned int luma7 : 8;
    } reg;
} SOC_ISP_TNR_LUMAB_UNION;
#endif
#define SOC_ISP_TNR_LUMAB_luma4_START (0)
#define SOC_ISP_TNR_LUMAB_luma4_END (7)
#define SOC_ISP_TNR_LUMAB_luma5_START (8)
#define SOC_ISP_TNR_LUMAB_luma5_END (15)
#define SOC_ISP_TNR_LUMAB_luma6_START (16)
#define SOC_ISP_TNR_LUMAB_luma6_END (23)
#define SOC_ISP_TNR_LUMAB_luma7_START (24)
#define SOC_ISP_TNR_LUMAB_luma7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma8 : 8;
        unsigned int luma9 : 8;
        unsigned int luma10 : 8;
        unsigned int luma11 : 8;
    } reg;
} SOC_ISP_TNR_LUMAC_UNION;
#endif
#define SOC_ISP_TNR_LUMAC_luma8_START (0)
#define SOC_ISP_TNR_LUMAC_luma8_END (7)
#define SOC_ISP_TNR_LUMAC_luma9_START (8)
#define SOC_ISP_TNR_LUMAC_luma9_END (15)
#define SOC_ISP_TNR_LUMAC_luma10_START (16)
#define SOC_ISP_TNR_LUMAC_luma10_END (23)
#define SOC_ISP_TNR_LUMAC_luma11_START (24)
#define SOC_ISP_TNR_LUMAC_luma11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma12 : 8;
        unsigned int luma13 : 8;
        unsigned int luma14 : 8;
        unsigned int luma15 : 8;
    } reg;
} SOC_ISP_TNR_LUMAD_UNION;
#endif
#define SOC_ISP_TNR_LUMAD_luma12_START (0)
#define SOC_ISP_TNR_LUMAD_luma12_END (7)
#define SOC_ISP_TNR_LUMAD_luma13_START (8)
#define SOC_ISP_TNR_LUMAD_luma13_END (15)
#define SOC_ISP_TNR_LUMAD_luma14_START (16)
#define SOC_ISP_TNR_LUMAD_luma14_END (23)
#define SOC_ISP_TNR_LUMAD_luma15_START (24)
#define SOC_ISP_TNR_LUMAD_luma15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma16 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_TNR_LUMAE_UNION;
#endif
#define SOC_ISP_TNR_LUMAE_luma16_START (0)
#define SOC_ISP_TNR_LUMAE_luma16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv0 : 8;
        unsigned int motionuv1 : 8;
        unsigned int motionuv2 : 8;
        unsigned int motionuv3 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVA_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVA_motionuv0_START (0)
#define SOC_ISP_TNR_MOTIONUVA_motionuv0_END (7)
#define SOC_ISP_TNR_MOTIONUVA_motionuv1_START (8)
#define SOC_ISP_TNR_MOTIONUVA_motionuv1_END (15)
#define SOC_ISP_TNR_MOTIONUVA_motionuv2_START (16)
#define SOC_ISP_TNR_MOTIONUVA_motionuv2_END (23)
#define SOC_ISP_TNR_MOTIONUVA_motionuv3_START (24)
#define SOC_ISP_TNR_MOTIONUVA_motionuv3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv4 : 8;
        unsigned int motionuv5 : 8;
        unsigned int motionuv6 : 8;
        unsigned int motionuv7 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVB_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVB_motionuv4_START (0)
#define SOC_ISP_TNR_MOTIONUVB_motionuv4_END (7)
#define SOC_ISP_TNR_MOTIONUVB_motionuv5_START (8)
#define SOC_ISP_TNR_MOTIONUVB_motionuv5_END (15)
#define SOC_ISP_TNR_MOTIONUVB_motionuv6_START (16)
#define SOC_ISP_TNR_MOTIONUVB_motionuv6_END (23)
#define SOC_ISP_TNR_MOTIONUVB_motionuv7_START (24)
#define SOC_ISP_TNR_MOTIONUVB_motionuv7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv8 : 8;
        unsigned int motionuv9 : 8;
        unsigned int motionuv10 : 8;
        unsigned int motionuv11 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVC_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVC_motionuv8_START (0)
#define SOC_ISP_TNR_MOTIONUVC_motionuv8_END (7)
#define SOC_ISP_TNR_MOTIONUVC_motionuv9_START (8)
#define SOC_ISP_TNR_MOTIONUVC_motionuv9_END (15)
#define SOC_ISP_TNR_MOTIONUVC_motionuv10_START (16)
#define SOC_ISP_TNR_MOTIONUVC_motionuv10_END (23)
#define SOC_ISP_TNR_MOTIONUVC_motionuv11_START (24)
#define SOC_ISP_TNR_MOTIONUVC_motionuv11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv12 : 8;
        unsigned int motionuv13 : 8;
        unsigned int motionuv14 : 8;
        unsigned int motionuv15 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVD_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVD_motionuv12_START (0)
#define SOC_ISP_TNR_MOTIONUVD_motionuv12_END (7)
#define SOC_ISP_TNR_MOTIONUVD_motionuv13_START (8)
#define SOC_ISP_TNR_MOTIONUVD_motionuv13_END (15)
#define SOC_ISP_TNR_MOTIONUVD_motionuv14_START (16)
#define SOC_ISP_TNR_MOTIONUVD_motionuv14_END (23)
#define SOC_ISP_TNR_MOTIONUVD_motionuv15_START (24)
#define SOC_ISP_TNR_MOTIONUVD_motionuv15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv16 : 8;
        unsigned int motionuv17 : 8;
        unsigned int motionuv18 : 8;
        unsigned int motionuv19 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVE_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVE_motionuv16_START (0)
#define SOC_ISP_TNR_MOTIONUVE_motionuv16_END (7)
#define SOC_ISP_TNR_MOTIONUVE_motionuv17_START (8)
#define SOC_ISP_TNR_MOTIONUVE_motionuv17_END (15)
#define SOC_ISP_TNR_MOTIONUVE_motionuv18_START (16)
#define SOC_ISP_TNR_MOTIONUVE_motionuv18_END (23)
#define SOC_ISP_TNR_MOTIONUVE_motionuv19_START (24)
#define SOC_ISP_TNR_MOTIONUVE_motionuv19_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv20 : 8;
        unsigned int motionuv21 : 8;
        unsigned int motionuv22 : 8;
        unsigned int motionuv23 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVF_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVF_motionuv20_START (0)
#define SOC_ISP_TNR_MOTIONUVF_motionuv20_END (7)
#define SOC_ISP_TNR_MOTIONUVF_motionuv21_START (8)
#define SOC_ISP_TNR_MOTIONUVF_motionuv21_END (15)
#define SOC_ISP_TNR_MOTIONUVF_motionuv22_START (16)
#define SOC_ISP_TNR_MOTIONUVF_motionuv22_END (23)
#define SOC_ISP_TNR_MOTIONUVF_motionuv23_START (24)
#define SOC_ISP_TNR_MOTIONUVF_motionuv23_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv24 : 8;
        unsigned int motionuv25 : 8;
        unsigned int motionuv26 : 8;
        unsigned int motionuv27 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONUVG_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVG_motionuv24_START (0)
#define SOC_ISP_TNR_MOTIONUVG_motionuv24_END (7)
#define SOC_ISP_TNR_MOTIONUVG_motionuv25_START (8)
#define SOC_ISP_TNR_MOTIONUVG_motionuv25_END (15)
#define SOC_ISP_TNR_MOTIONUVG_motionuv26_START (16)
#define SOC_ISP_TNR_MOTIONUVG_motionuv26_END (23)
#define SOC_ISP_TNR_MOTIONUVG_motionuv27_START (24)
#define SOC_ISP_TNR_MOTIONUVG_motionuv27_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motionuv28 : 8;
        unsigned int motionuv29 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_TNR_MOTIONUVH_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVH_motionuv28_START (0)
#define SOC_ISP_TNR_MOTIONUVH_motionuv28_END (7)
#define SOC_ISP_TNR_MOTIONUVH_motionuv29_START (8)
#define SOC_ISP_TNR_MOTIONUVH_motionuv29_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion0 : 8;
        unsigned int motion1 : 8;
        unsigned int motion2 : 8;
        unsigned int motion3 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONA_UNION;
#endif
#define SOC_ISP_TNR_MOTIONA_motion0_START (0)
#define SOC_ISP_TNR_MOTIONA_motion0_END (7)
#define SOC_ISP_TNR_MOTIONA_motion1_START (8)
#define SOC_ISP_TNR_MOTIONA_motion1_END (15)
#define SOC_ISP_TNR_MOTIONA_motion2_START (16)
#define SOC_ISP_TNR_MOTIONA_motion2_END (23)
#define SOC_ISP_TNR_MOTIONA_motion3_START (24)
#define SOC_ISP_TNR_MOTIONA_motion3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion4 : 8;
        unsigned int motion5 : 8;
        unsigned int motion6 : 8;
        unsigned int motion7 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONB_UNION;
#endif
#define SOC_ISP_TNR_MOTIONB_motion4_START (0)
#define SOC_ISP_TNR_MOTIONB_motion4_END (7)
#define SOC_ISP_TNR_MOTIONB_motion5_START (8)
#define SOC_ISP_TNR_MOTIONB_motion5_END (15)
#define SOC_ISP_TNR_MOTIONB_motion6_START (16)
#define SOC_ISP_TNR_MOTIONB_motion6_END (23)
#define SOC_ISP_TNR_MOTIONB_motion7_START (24)
#define SOC_ISP_TNR_MOTIONB_motion7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion8 : 8;
        unsigned int motion9 : 8;
        unsigned int motion10 : 8;
        unsigned int motion11 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONC_UNION;
#endif
#define SOC_ISP_TNR_MOTIONC_motion8_START (0)
#define SOC_ISP_TNR_MOTIONC_motion8_END (7)
#define SOC_ISP_TNR_MOTIONC_motion9_START (8)
#define SOC_ISP_TNR_MOTIONC_motion9_END (15)
#define SOC_ISP_TNR_MOTIONC_motion10_START (16)
#define SOC_ISP_TNR_MOTIONC_motion10_END (23)
#define SOC_ISP_TNR_MOTIONC_motion11_START (24)
#define SOC_ISP_TNR_MOTIONC_motion11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion12 : 8;
        unsigned int motion13 : 8;
        unsigned int motion14 : 8;
        unsigned int motion15 : 8;
    } reg;
} SOC_ISP_TNR_MOTIOND_UNION;
#endif
#define SOC_ISP_TNR_MOTIOND_motion12_START (0)
#define SOC_ISP_TNR_MOTIOND_motion12_END (7)
#define SOC_ISP_TNR_MOTIOND_motion13_START (8)
#define SOC_ISP_TNR_MOTIOND_motion13_END (15)
#define SOC_ISP_TNR_MOTIOND_motion14_START (16)
#define SOC_ISP_TNR_MOTIOND_motion14_END (23)
#define SOC_ISP_TNR_MOTIOND_motion15_START (24)
#define SOC_ISP_TNR_MOTIOND_motion15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion16 : 8;
        unsigned int motion17 : 8;
        unsigned int motion18 : 8;
        unsigned int motion19 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONE_UNION;
#endif
#define SOC_ISP_TNR_MOTIONE_motion16_START (0)
#define SOC_ISP_TNR_MOTIONE_motion16_END (7)
#define SOC_ISP_TNR_MOTIONE_motion17_START (8)
#define SOC_ISP_TNR_MOTIONE_motion17_END (15)
#define SOC_ISP_TNR_MOTIONE_motion18_START (16)
#define SOC_ISP_TNR_MOTIONE_motion18_END (23)
#define SOC_ISP_TNR_MOTIONE_motion19_START (24)
#define SOC_ISP_TNR_MOTIONE_motion19_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion20 : 8;
        unsigned int motion21 : 8;
        unsigned int motion22 : 8;
        unsigned int motion23 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONF_UNION;
#endif
#define SOC_ISP_TNR_MOTIONF_motion20_START (0)
#define SOC_ISP_TNR_MOTIONF_motion20_END (7)
#define SOC_ISP_TNR_MOTIONF_motion21_START (8)
#define SOC_ISP_TNR_MOTIONF_motion21_END (15)
#define SOC_ISP_TNR_MOTIONF_motion22_START (16)
#define SOC_ISP_TNR_MOTIONF_motion22_END (23)
#define SOC_ISP_TNR_MOTIONF_motion23_START (24)
#define SOC_ISP_TNR_MOTIONF_motion23_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion24 : 8;
        unsigned int motion25 : 8;
        unsigned int motion26 : 8;
        unsigned int motion27 : 8;
    } reg;
} SOC_ISP_TNR_MOTIONG_UNION;
#endif
#define SOC_ISP_TNR_MOTIONG_motion24_START (0)
#define SOC_ISP_TNR_MOTIONG_motion24_END (7)
#define SOC_ISP_TNR_MOTIONG_motion25_START (8)
#define SOC_ISP_TNR_MOTIONG_motion25_END (15)
#define SOC_ISP_TNR_MOTIONG_motion26_START (16)
#define SOC_ISP_TNR_MOTIONG_motion26_END (23)
#define SOC_ISP_TNR_MOTIONG_motion27_START (24)
#define SOC_ISP_TNR_MOTIONG_motion27_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int motion28 : 8;
        unsigned int motion29 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_TNR_MOTIONH_UNION;
#endif
#define SOC_ISP_TNR_MOTIONH_motion28_START (0)
#define SOC_ISP_TNR_MOTIONH_motion28_END (7)
#define SOC_ISP_TNR_MOTIONH_motion29_START (8)
#define SOC_ISP_TNR_MOTIONH_motion29_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_clk_on : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TNR_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_force_clk_on_START (0)
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_force_clk_on_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
