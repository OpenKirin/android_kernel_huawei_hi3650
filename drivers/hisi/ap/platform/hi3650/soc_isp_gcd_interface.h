#ifndef __SOC_ISP_GCD_INTERFACE_H__
#define __SOC_ISP_GCD_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_GCD_GCD_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_GCD_GKM_IHLEFT_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_GCD_GKM_IVTOP_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_GCD_GKM_IHRIGHT_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_GCD_GKM_IVBOTTOM_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_GCD_DMS_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_GCD_FCR_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_GCD_GEQ_ENA_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_GCD_GEQ_WEI_1_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_GCD_GEQ_WEI_2_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_GCD_GEQ_THR_1_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_GCD_GEQ_THR_2_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_GCD_GEQ_THR_3_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_GCD_FCS_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_GCD_CAC_EN_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_GCD_CAC_CEN_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_GCD_CAC_RAD_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_GCD_CAC_WEI_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_GCD_CAC_THR_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_GCD_GCAC_CTRL_ADDR(base) ((base) + (0x004C))
#define SOC_ISP_GCD_GCAC_NORM_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_GCD_GCAC_A_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_GCD_GCAC_B_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_GCD_GCAC_C_ADDR(base) ((base) + (0x005C))
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_GCD_LSC_LUT_0_ADDR(base,Range256) ((base) + (0x0100+0x4*(Range256)))
#define SOC_ISP_GCD_LSC_LUT_1_ADDR(base,Range256) ((base) + (0x0500+0x4*(Range256)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_GCD_GCD_CONFIG_UNION;
#endif
#define SOC_ISP_GCD_GCD_CONFIG_bypass_START (0)
#define SOC_ISP_GCD_GCD_CONFIG_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gkm_crop_left : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_GCD_GKM_IHLEFT_UNION;
#endif
#define SOC_ISP_GCD_GKM_IHLEFT_gkm_crop_left_START (0)
#define SOC_ISP_GCD_GKM_IHLEFT_gkm_crop_left_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gkm_crop_top : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_GCD_GKM_IVTOP_UNION;
#endif
#define SOC_ISP_GCD_GKM_IVTOP_gkm_crop_top_START (0)
#define SOC_ISP_GCD_GKM_IVTOP_gkm_crop_top_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gkm_crop_right : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_GCD_GKM_IHRIGHT_UNION;
#endif
#define SOC_ISP_GCD_GKM_IHRIGHT_gkm_crop_right_START (0)
#define SOC_ISP_GCD_GKM_IHRIGHT_gkm_crop_right_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gkm_crop_bottom : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_GCD_GKM_IVBOTTOM_UNION;
#endif
#define SOC_ISP_GCD_GKM_IVBOTTOM_gkm_crop_bottom_START (0)
#define SOC_ISP_GCD_GKM_IVBOTTOM_gkm_crop_bottom_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dms_wei1 : 9;
        unsigned int dms_wei2 : 7;
        unsigned int dms_cho : 2;
        unsigned int dms_thr1 : 10;
        unsigned int reserved : 4;
    } reg;
} SOC_ISP_GCD_DMS_UNION;
#endif
#define SOC_ISP_GCD_DMS_dms_wei1_START (0)
#define SOC_ISP_GCD_DMS_dms_wei1_END (8)
#define SOC_ISP_GCD_DMS_dms_wei2_START (9)
#define SOC_ISP_GCD_DMS_dms_wei2_END (15)
#define SOC_ISP_GCD_DMS_dms_cho_START (16)
#define SOC_ISP_GCD_DMS_dms_cho_END (17)
#define SOC_ISP_GCD_DMS_dms_thr1_START (18)
#define SOC_ISP_GCD_DMS_dms_thr1_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fcr_ena0 : 1;
        unsigned int fcr_ena1 : 1;
        unsigned int fcr_ena2 : 1;
        unsigned int fcr_cho : 3;
        unsigned int reserved_0: 2;
        unsigned int fcr_wei1 : 8;
        unsigned int fcr_wei2 : 6;
        unsigned int reserved_1: 10;
    } reg;
} SOC_ISP_GCD_FCR_UNION;
#endif
#define SOC_ISP_GCD_FCR_fcr_ena0_START (0)
#define SOC_ISP_GCD_FCR_fcr_ena0_END (0)
#define SOC_ISP_GCD_FCR_fcr_ena1_START (1)
#define SOC_ISP_GCD_FCR_fcr_ena1_END (1)
#define SOC_ISP_GCD_FCR_fcr_ena2_START (2)
#define SOC_ISP_GCD_FCR_fcr_ena2_END (2)
#define SOC_ISP_GCD_FCR_fcr_cho_START (3)
#define SOC_ISP_GCD_FCR_fcr_cho_END (5)
#define SOC_ISP_GCD_FCR_fcr_wei1_START (8)
#define SOC_ISP_GCD_FCR_fcr_wei1_END (15)
#define SOC_ISP_GCD_FCR_fcr_wei2_START (16)
#define SOC_ISP_GCD_FCR_fcr_wei2_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ena0 : 1;
        unsigned int ena1 : 1;
        unsigned int ena2 : 1;
        unsigned int ena3 : 1;
        unsigned int ena4 : 1;
        unsigned int ena5 : 1;
        unsigned int ena6 : 1;
        unsigned int ena7 : 1;
        unsigned int ena8 : 1;
        unsigned int ena9 : 1;
        unsigned int ena10 : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_GCD_GEQ_ENA_UNION;
#endif
#define SOC_ISP_GCD_GEQ_ENA_ena0_START (0)
#define SOC_ISP_GCD_GEQ_ENA_ena0_END (0)
#define SOC_ISP_GCD_GEQ_ENA_ena1_START (1)
#define SOC_ISP_GCD_GEQ_ENA_ena1_END (1)
#define SOC_ISP_GCD_GEQ_ENA_ena2_START (2)
#define SOC_ISP_GCD_GEQ_ENA_ena2_END (2)
#define SOC_ISP_GCD_GEQ_ENA_ena3_START (3)
#define SOC_ISP_GCD_GEQ_ENA_ena3_END (3)
#define SOC_ISP_GCD_GEQ_ENA_ena4_START (4)
#define SOC_ISP_GCD_GEQ_ENA_ena4_END (4)
#define SOC_ISP_GCD_GEQ_ENA_ena5_START (5)
#define SOC_ISP_GCD_GEQ_ENA_ena5_END (5)
#define SOC_ISP_GCD_GEQ_ENA_ena6_START (6)
#define SOC_ISP_GCD_GEQ_ENA_ena6_END (6)
#define SOC_ISP_GCD_GEQ_ENA_ena7_START (7)
#define SOC_ISP_GCD_GEQ_ENA_ena7_END (7)
#define SOC_ISP_GCD_GEQ_ENA_ena8_START (8)
#define SOC_ISP_GCD_GEQ_ENA_ena8_END (8)
#define SOC_ISP_GCD_GEQ_ENA_ena9_START (9)
#define SOC_ISP_GCD_GEQ_ENA_ena9_END (9)
#define SOC_ISP_GCD_GEQ_ENA_ena10_START (10)
#define SOC_ISP_GCD_GEQ_ENA_ena10_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int geq_wei1 : 9;
        unsigned int reserved_0: 7;
        unsigned int geq_wei2 : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_GCD_GEQ_WEI_1_UNION;
#endif
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei1_START (0)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei1_END (8)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei2_START (16)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei2_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int geq_wei3 : 9;
        unsigned int reserved_0: 7;
        unsigned int geq_wei4 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_GCD_GEQ_WEI_2_UNION;
#endif
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei3_START (0)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei3_END (8)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei4_START (16)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei4_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int geq_thr1 : 10;
        unsigned int reserved_0: 6;
        unsigned int geq_thr2 : 10;
        unsigned int reserved_1: 6;
    } reg;
} SOC_ISP_GCD_GEQ_THR_1_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr1_START (0)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr1_END (9)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr2_START (16)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr2_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int geq_thr3 : 9;
        unsigned int reserved_0: 7;
        unsigned int geq_thr4 : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_ISP_GCD_GEQ_THR_2_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr3_START (0)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr3_END (8)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr4_START (16)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr4_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int geq_thr5 : 11;
        unsigned int reserved_0: 5;
        unsigned int geq_thr6 : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_ISP_GCD_GEQ_THR_3_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr5_START (0)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr5_END (10)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr6_START (16)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr6_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fcs_ena0 : 1;
        unsigned int fcs_ena1 : 1;
        unsigned int reserved_0: 6;
        unsigned int fcs_wei1 : 5;
        unsigned int reserved_1: 3;
        unsigned int fcs_thr1 : 10;
        unsigned int reserved_2: 6;
    } reg;
} SOC_ISP_GCD_FCS_UNION;
#endif
#define SOC_ISP_GCD_FCS_fcs_ena0_START (0)
#define SOC_ISP_GCD_FCS_fcs_ena0_END (0)
#define SOC_ISP_GCD_FCS_fcs_ena1_START (1)
#define SOC_ISP_GCD_FCS_fcs_ena1_END (1)
#define SOC_ISP_GCD_FCS_fcs_wei1_START (8)
#define SOC_ISP_GCD_FCS_fcs_wei1_END (12)
#define SOC_ISP_GCD_FCS_fcs_thr1_START (16)
#define SOC_ISP_GCD_FCS_fcs_thr1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cac_ena0 : 1;
        unsigned int reserved_0: 1;
        unsigned int cac_ena2 : 1;
        unsigned int cac_ena3 : 1;
        unsigned int cac_ena4 : 1;
        unsigned int cacgena0 : 1;
        unsigned int cacgena1 : 1;
        unsigned int reserved_1: 1;
        unsigned int cac_rad2 : 21;
        unsigned int reserved_2: 3;
    } reg;
} SOC_ISP_GCD_CAC_EN_UNION;
#endif
#define SOC_ISP_GCD_CAC_EN_cac_ena0_START (0)
#define SOC_ISP_GCD_CAC_EN_cac_ena0_END (0)
#define SOC_ISP_GCD_CAC_EN_cac_ena2_START (2)
#define SOC_ISP_GCD_CAC_EN_cac_ena2_END (2)
#define SOC_ISP_GCD_CAC_EN_cac_ena3_START (3)
#define SOC_ISP_GCD_CAC_EN_cac_ena3_END (3)
#define SOC_ISP_GCD_CAC_EN_cac_ena4_START (4)
#define SOC_ISP_GCD_CAC_EN_cac_ena4_END (4)
#define SOC_ISP_GCD_CAC_EN_cacgena0_START (5)
#define SOC_ISP_GCD_CAC_EN_cacgena0_END (5)
#define SOC_ISP_GCD_CAC_EN_cacgena1_START (6)
#define SOC_ISP_GCD_CAC_EN_cacgena1_END (6)
#define SOC_ISP_GCD_CAC_EN_cac_rad2_START (8)
#define SOC_ISP_GCD_CAC_EN_cac_rad2_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cac_cen1 : 14;
        unsigned int reserved_0: 2;
        unsigned int cac_cen2 : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_GCD_CAC_CEN_UNION;
#endif
#define SOC_ISP_GCD_CAC_CEN_cac_cen1_START (0)
#define SOC_ISP_GCD_CAC_CEN_cac_cen1_END (13)
#define SOC_ISP_GCD_CAC_CEN_cac_cen2_START (16)
#define SOC_ISP_GCD_CAC_CEN_cac_cen2_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cac_rad1 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_GCD_CAC_RAD_UNION;
#endif
#define SOC_ISP_GCD_CAC_RAD_cac_rad1_START (0)
#define SOC_ISP_GCD_CAC_RAD_cac_rad1_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cac_wei1 : 8;
        unsigned int cac_wei2 : 6;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_GCD_CAC_WEI_UNION;
#endif
#define SOC_ISP_GCD_CAC_WEI_cac_wei1_START (0)
#define SOC_ISP_GCD_CAC_WEI_cac_wei1_END (7)
#define SOC_ISP_GCD_CAC_WEI_cac_wei2_START (8)
#define SOC_ISP_GCD_CAC_WEI_cac_wei2_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cac_cho1 : 2;
        unsigned int cac_cho2 : 2;
        unsigned int cac_cho3 : 3;
        unsigned int reserved_0: 9;
        unsigned int cac_thr : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_GCD_CAC_THR_UNION;
#endif
#define SOC_ISP_GCD_CAC_THR_cac_cho1_START (0)
#define SOC_ISP_GCD_CAC_THR_cac_cho1_END (1)
#define SOC_ISP_GCD_CAC_THR_cac_cho2_START (2)
#define SOC_ISP_GCD_CAC_THR_cac_cho2_END (3)
#define SOC_ISP_GCD_CAC_THR_cac_cho3_START (4)
#define SOC_ISP_GCD_CAC_THR_cac_cho3_END (6)
#define SOC_ISP_GCD_CAC_THR_cac_thr_START (16)
#define SOC_ISP_GCD_CAC_THR_cac_thr_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gcac_enable : 1;
        unsigned int gcac_v_clip_mode : 2;
        unsigned int gcac_h_clip_mode : 1;
        unsigned int cv_mask : 2;
        unsigned int reserved : 26;
    } reg;
} SOC_ISP_GCD_GCAC_CTRL_UNION;
#endif
#define SOC_ISP_GCD_GCAC_CTRL_gcac_enable_START (0)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_enable_END (0)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_v_clip_mode_START (1)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_v_clip_mode_END (2)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_h_clip_mode_START (3)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_h_clip_mode_END (3)
#define SOC_ISP_GCD_GCAC_CTRL_cv_mask_START (4)
#define SOC_ISP_GCD_GCAC_CTRL_cv_mask_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_nf : 5;
        unsigned int reserved_0: 3;
        unsigned int x_ns : 4;
        unsigned int reserved_1: 4;
        unsigned int y_nf : 5;
        unsigned int reserved_2: 3;
        unsigned int y_ns : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_ISP_GCD_GCAC_NORM_UNION;
#endif
#define SOC_ISP_GCD_GCAC_NORM_x_nf_START (0)
#define SOC_ISP_GCD_GCAC_NORM_x_nf_END (4)
#define SOC_ISP_GCD_GCAC_NORM_x_ns_START (8)
#define SOC_ISP_GCD_GCAC_NORM_x_ns_END (11)
#define SOC_ISP_GCD_GCAC_NORM_y_nf_START (16)
#define SOC_ISP_GCD_GCAC_NORM_y_nf_END (20)
#define SOC_ISP_GCD_GCAC_NORM_y_ns_START (24)
#define SOC_ISP_GCD_GCAC_NORM_y_ns_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int a_red : 9;
        unsigned int reserved_0: 7;
        unsigned int a_blue : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_GCD_GCAC_A_UNION;
#endif
#define SOC_ISP_GCD_GCAC_A_a_red_START (0)
#define SOC_ISP_GCD_GCAC_A_a_red_END (8)
#define SOC_ISP_GCD_GCAC_A_a_blue_START (16)
#define SOC_ISP_GCD_GCAC_A_a_blue_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_red : 9;
        unsigned int reserved_0: 7;
        unsigned int b_blue : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_GCD_GCAC_B_UNION;
#endif
#define SOC_ISP_GCD_GCAC_B_b_red_START (0)
#define SOC_ISP_GCD_GCAC_B_b_red_END (8)
#define SOC_ISP_GCD_GCAC_B_b_blue_START (16)
#define SOC_ISP_GCD_GCAC_B_b_blue_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int c_red : 9;
        unsigned int reserved_0: 7;
        unsigned int c_blue : 9;
        unsigned int reserved_1: 7;
    } reg;
} SOC_ISP_GCD_GCAC_C_UNION;
#endif
#define SOC_ISP_GCD_GCAC_C_c_red_START (0)
#define SOC_ISP_GCD_GCAC_C_c_red_END (8)
#define SOC_ISP_GCD_GCAC_C_c_blue_START (16)
#define SOC_ISP_GCD_GCAC_C_c_blue_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lsc_table_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_GCD_LSC_TABLE_ACTIVE_UNION;
#endif
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_lsc_table_active_START (0)
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_lsc_table_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lcsgain : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_GCD_LSC_LUT_0_UNION;
#endif
#define SOC_ISP_GCD_LSC_LUT_0_lcsgain_START (0)
#define SOC_ISP_GCD_LSC_LUT_0_lcsgain_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lcsgain : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_GCD_LSC_LUT_1_UNION;
#endif
#define SOC_ISP_GCD_LSC_LUT_1_lcsgain_START (0)
#define SOC_ISP_GCD_LSC_LUT_1_lcsgain_END (10)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
