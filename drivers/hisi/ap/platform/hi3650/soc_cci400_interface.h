#ifndef __SOC_CCI400_INTERFACE_H__
#define __SOC_CCI400_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CCI400_CCI_CR_ADDR(base) ((base) + (0x90000))
#define SOC_CCI400_CCI_SPECCTRL_ADDR(base) ((base) + (0x90004))
#define SOC_CCI400_CCI_SAR_ADDR(base) ((base) + (0x90008))
#define SOC_CCI400_CCI_SR_ADDR(base) ((base) + (0x9000C))
#define SOC_CCI400_CCI_IMPR_ADDR(base) ((base) + (0x90010))
#define SOC_CCI400_CCI_PMCR_ADDR(base) ((base) + (0x90100))
#define SOC_CCI400_CCI_PERI4_ADDR(base) ((base) + (0x90FD0))
#define SOC_CCI400_CCI_PERI5_ADDR(base) ((base) + (0x90FD4))
#define SOC_CCI400_CCI_PERI6_ADDR(base) ((base) + (0x90FD8))
#define SOC_CCI400_CCI_PERI7_ADDR(base) ((base) + (0x90FDC))
#define SOC_CCI400_CCI_PERI0_ADDR(base) ((base) + (0x90FE0))
#define SOC_CCI400_CCI_PERI1_ADDR(base) ((base) + (0x90FE4))
#define SOC_CCI400_CCI_PERI2_ADDR(base) ((base) + (0x90FE8))
#define SOC_CCI400_CCI_PERI3_ADDR(base) ((base) + (0x90FEC))
#define SOC_CCI400_CCI_COMP0_ADDR(base) ((base) + (0x90FF0))
#define SOC_CCI400_CCI_COMP1_ADDR(base) ((base) + (0x90FF4))
#define SOC_CCI400_CCI_COMP2_ADDR(base) ((base) + (0x90FF8))
#define SOC_CCI400_CCI_COMP3_ADDR(base) ((base) + (0x90FFC))
#define SOC_CCI400_CCI_SCR_S0_ADDR(base) ((base) + (0x91000))
#define SOC_CCI400_CCI_SOR_S0_ADDR(base) ((base) + (0x91004))
#define SOC_CCI400_CCI_RCQVOR_S0_ADDR(base) ((base) + (0x91100))
#define SOC_CCI400_CCI_WCQVOR_S0_ADDR(base) ((base) + (0x91104))
#define SOC_CCI400_CCI_QCR_S0_ADDR(base) ((base) + (0x9110C))
#define SOC_CCI400_CCI_MOTR_S0_ADDR(base) ((base) + (0x91110))
#define SOC_CCI400_CCI_RTR_S0_ADDR(base) ((base) + (0x91130))
#define SOC_CCI400_CCI_QRSFR_S0_ADDR(base) ((base) + (0x91134))
#define SOC_CCI400_CCI_QRR_S0_ADDR(base) ((base) + (0x91138))
#define SOC_CCI400_CCI_SCR_S1_ADDR(base) ((base) + (0x92000))
#define SOC_CCI400_CCI_SOR_S1_ADDR(base) ((base) + (0x92004))
#define SOC_CCI400_CCI_RCQVOR_S1_ADDR(base) ((base) + (0x92100))
#define SOC_CCI400_CCI_WCQVOR_S1_ADDR(base) ((base) + (0x92104))
#define SOC_CCI400_CCI_QCR_S1_ADDR(base) ((base) + (0x9210C))
#define SOC_CCI400_CCI_MOTR_S1_ADDR(base) ((base) + (0x92110))
#define SOC_CCI400_CCI_RTR_S1_ADDR(base) ((base) + (0x92130))
#define SOC_CCI400_CCI_QRSFR_S1_ADDR(base) ((base) + (0x92134))
#define SOC_CCI400_CCI_QRR_S1_ADDR(base) ((base) + (0x92138))
#define SOC_CCI400_CCI_SCR_S2_ADDR(base) ((base) + (0x93000))
#define SOC_CCI400_CCI_SOR_S2_ADDR(base) ((base) + (0x93004))
#define SOC_CCI400_CCI_RCQVOR_S2_ADDR(base) ((base) + (0x93100))
#define SOC_CCI400_CCI_WCQVOR_S2_ADDR(base) ((base) + (0x93104))
#define SOC_CCI400_CCI_QCR_S2_ADDR(base) ((base) + (0x9310C))
#define SOC_CCI400_CCI_MOTR_S2_ADDR(base) ((base) + (0x93110))
#define SOC_CCI400_CCI_RTR_S2_ADDR(base) ((base) + (0x93130))
#define SOC_CCI400_CCI_QRSFR_S2_ADDR(base) ((base) + (0x93134))
#define SOC_CCI400_CCI_QRR_S2_ADDR(base) ((base) + (0x93138))
#define SOC_CCI400_CCI_SCR_S3_ADDR(base) ((base) + (0x94000))
#define SOC_CCI400_CCI_RCQVOR_S3_ADDR(base) ((base) + (0x94100))
#define SOC_CCI400_CCI_WCQVOR_S3_ADDR(base) ((base) + (0x94104))
#define SOC_CCI400_CCI_QCR_S3_ADDR(base) ((base) + (0x9410C))
#define SOC_CCI400_CCI_RTR_S3_ADDR(base) ((base) + (0x94130))
#define SOC_CCI400_CCI_QRSFR_S3_ADDR(base) ((base) + (0x94134))
#define SOC_CCI400_CCI_QRR_S3_ADDR(base) ((base) + (0x94138))
#define SOC_CCI400_CCI_SCR_S4_ADDR(base) ((base) + (0x95000))
#define SOC_CCI400_CCI_RCQVOR_S4_ADDR(base) ((base) + (0x95100))
#define SOC_CCI400_CCI_WCQVOR_S4_ADDR(base) ((base) + (0x95104))
#define SOC_CCI400_CCI_QCR_S4_ADDR(base) ((base) + (0x9510C))
#define SOC_CCI400_CCI_RTR_S4_ADDR(base) ((base) + (0x95130))
#define SOC_CCI400_CCI_QRSFR_S4_ADDR(base) ((base) + (0x91134))
#define SOC_CCI400_CCI_QRR_S4_ADDR(base) ((base) + (0x95138))
#define SOC_CCI400_CCI_ECCR_ADDR(base) ((base) + (0x99004))
#define SOC_CCI400_CCI_CCR_ADDR(base) ((base) + (0x99008))
#define SOC_CCI400_CCI_OFSR_ADDR(base) ((base) + (0x9900C))
#define SOC_CCI400_CCI_ESR_0_ADDR(base) ((base) + (0x9A000))
#define SOC_CCI400_CCI_ECCR_0_ADDR(base) ((base) + (0x9A004))
#define SOC_CCI400_CCI_CCR_0_ADDR(base) ((base) + (0x9A008))
#define SOC_CCI400_CCI_OFSR_0_ADDR(base) ((base) + (0x9A00C))
#define SOC_CCI400_CCI_ESR_1_ADDR(base) ((base) + (0x9B000))
#define SOC_CCI400_CCI_ECCR_1_ADDR(base) ((base) + (0x9B004))
#define SOC_CCI400_CCI_CCR_1_ADDR(base) ((base) + (0x9B008))
#define SOC_CCI400_CCI_OFSR_1_ADDR(base) ((base) + (0x9B00C))
#define SOC_CCI400_CCI_ESR_2_ADDR(base) ((base) + (0x9C000))
#define SOC_CCI400_CCI_ECCR_2_ADDR(base) ((base) + (0x9C004))
#define SOC_CCI400_CCI_CCR_2_ADDR(base) ((base) + (0x9C008))
#define SOC_CCI400_CCI_OFSR_2_ADDR(base) ((base) + (0x9C00C))
#define SOC_CCI400_CCI_ESR_3_ADDR(base) ((base) + (0x9D000))
#define SOC_CCI400_CCI_ECCR_3_ADDR(base) ((base) + (0x9D004))
#define SOC_CCI400_CCI_CCR_3_ADDR(base) ((base) + (0x9D008))
#define SOC_CCI400_CCI_OFSR_3_ADDR(base) ((base) + (0x9D00C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int Snoop_disable : 1;
        unsigned int DVM_message_disable : 1;
        unsigned int spec_fetch_disable : 1;
        unsigned int barrier_terminate : 1;
        unsigned int prop_prom_disable : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CCI400_CCI_CR_UNION;
#endif
#define SOC_CCI400_CCI_CR_Snoop_disable_START (0)
#define SOC_CCI400_CCI_CR_Snoop_disable_END (0)
#define SOC_CCI400_CCI_CR_DVM_message_disable_START (1)
#define SOC_CCI400_CCI_CR_DVM_message_disable_END (1)
#define SOC_CCI400_CCI_CR_spec_fetch_disable_START (2)
#define SOC_CCI400_CCI_CR_spec_fetch_disable_END (2)
#define SOC_CCI400_CCI_CR_barrier_terminate_START (3)
#define SOC_CCI400_CCI_CR_barrier_terminate_END (3)
#define SOC_CCI400_CCI_CR_prop_prom_disable_START (4)
#define SOC_CCI400_CCI_CR_prop_prom_disable_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spec_fetch_disable_mst : 3;
        unsigned int reserved_0 : 13;
        unsigned int spec_fetch_disable_slv : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_CCI400_CCI_SPECCTRL_UNION;
#endif
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_mst_START (0)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_mst_END (2)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_slv_START (16)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_slv_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trans_pending : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_SAR_UNION;
#endif
#define SOC_CCI400_CCI_SAR_trans_pending_START (0)
#define SOC_CCI400_CCI_SAR_trans_pending_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dvm_pending : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_SR_UNION;
#endif
#define SOC_CCI400_CCI_SR_dvm_pending_START (0)
#define SOC_CCI400_CCI_SR_dvm_pending_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int err_ind0_m0 : 1;
        unsigned int err_ind0_m1 : 1;
        unsigned int err_ind0_m2 : 1;
        unsigned int reserved_0 : 13;
        unsigned int err_ind0_s : 1;
        unsigned int err_ind1_s : 1;
        unsigned int err_ind2_s : 1;
        unsigned int err_ind3_s : 1;
        unsigned int err_ind4_s : 1;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_CCI400_CCI_IMPR_UNION;
#endif
#define SOC_CCI400_CCI_IMPR_err_ind0_m0_START (0)
#define SOC_CCI400_CCI_IMPR_err_ind0_m0_END (0)
#define SOC_CCI400_CCI_IMPR_err_ind0_m1_START (1)
#define SOC_CCI400_CCI_IMPR_err_ind0_m1_END (1)
#define SOC_CCI400_CCI_IMPR_err_ind0_m2_START (2)
#define SOC_CCI400_CCI_IMPR_err_ind0_m2_END (2)
#define SOC_CCI400_CCI_IMPR_err_ind0_s_START (16)
#define SOC_CCI400_CCI_IMPR_err_ind0_s_END (16)
#define SOC_CCI400_CCI_IMPR_err_ind1_s_START (17)
#define SOC_CCI400_CCI_IMPR_err_ind1_s_END (17)
#define SOC_CCI400_CCI_IMPR_err_ind2_s_START (18)
#define SOC_CCI400_CCI_IMPR_err_ind2_s_END (18)
#define SOC_CCI400_CCI_IMPR_err_ind3_s_START (19)
#define SOC_CCI400_CCI_IMPR_err_ind3_s_END (19)
#define SOC_CCI400_CCI_IMPR_err_ind4_s_START (20)
#define SOC_CCI400_CCI_IMPR_err_ind4_s_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CEN : 1;
        unsigned int RST : 1;
        unsigned int CCR : 1;
        unsigned int CCD : 1;
        unsigned int EX : 1;
        unsigned int DP : 1;
        unsigned int reserved_0: 5;
        unsigned int cnt_num : 5;
        unsigned int reserved_1: 16;
    } reg;
} SOC_CCI400_CCI_PMCR_UNION;
#endif
#define SOC_CCI400_CCI_PMCR_CEN_START (0)
#define SOC_CCI400_CCI_PMCR_CEN_END (0)
#define SOC_CCI400_CCI_PMCR_RST_START (1)
#define SOC_CCI400_CCI_PMCR_RST_END (1)
#define SOC_CCI400_CCI_PMCR_CCR_START (2)
#define SOC_CCI400_CCI_PMCR_CCR_END (2)
#define SOC_CCI400_CCI_PMCR_CCD_START (3)
#define SOC_CCI400_CCI_PMCR_CCD_END (3)
#define SOC_CCI400_CCI_PMCR_EX_START (4)
#define SOC_CCI400_CCI_PMCR_EX_END (4)
#define SOC_CCI400_CCI_PMCR_DP_START (5)
#define SOC_CCI400_CCI_PMCR_DP_END (5)
#define SOC_CCI400_CCI_PMCR_cnt_num_START (11)
#define SOC_CCI400_CCI_PMCR_cnt_num_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int jep106_continue : 4;
        unsigned int reg_cnt : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI4_UNION;
#endif
#define SOC_CCI400_CCI_PERI4_jep106_continue_START (0)
#define SOC_CCI400_CCI_PERI4_jep106_continue_END (3)
#define SOC_CCI400_CCI_PERI4_reg_cnt_START (4)
#define SOC_CCI400_CCI_PERI4_reg_cnt_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peri_id5 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI5_UNION;
#endif
#define SOC_CCI400_CCI_PERI5_peri_id5_START (0)
#define SOC_CCI400_CCI_PERI5_peri_id5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peri_id6 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI6_UNION;
#endif
#define SOC_CCI400_CCI_PERI6_peri_id6_START (0)
#define SOC_CCI400_CCI_PERI6_peri_id6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peri_id7 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI7_UNION;
#endif
#define SOC_CCI400_CCI_PERI7_peri_id7_START (0)
#define SOC_CCI400_CCI_PERI7_peri_id7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peri_id0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI0_UNION;
#endif
#define SOC_CCI400_CCI_PERI0_peri_id0_START (0)
#define SOC_CCI400_CCI_PERI0_peri_id0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peri_id1_num : 4;
        unsigned int jep106_id_l : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI1_UNION;
#endif
#define SOC_CCI400_CCI_PERI1_peri_id1_num_START (0)
#define SOC_CCI400_CCI_PERI1_peri_id1_num_END (3)
#define SOC_CCI400_CCI_PERI1_jep106_id_l_START (4)
#define SOC_CCI400_CCI_PERI1_jep106_id_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int jep106_id_h : 3;
        unsigned int manu_id_code : 1;
        unsigned int ccr_rev : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI2_UNION;
#endif
#define SOC_CCI400_CCI_PERI2_jep106_id_h_START (0)
#define SOC_CCI400_CCI_PERI2_jep106_id_h_END (2)
#define SOC_CCI400_CCI_PERI2_manu_id_code_START (3)
#define SOC_CCI400_CCI_PERI2_manu_id_code_END (3)
#define SOC_CCI400_CCI_PERI2_ccr_rev_START (4)
#define SOC_CCI400_CCI_PERI2_ccr_rev_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mod_num : 4;
        unsigned int eco_num : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_PERI3_UNION;
#endif
#define SOC_CCI400_CCI_PERI3_mod_num_START (0)
#define SOC_CCI400_CCI_PERI3_mod_num_END (3)
#define SOC_CCI400_CCI_PERI3_eco_num_START (4)
#define SOC_CCI400_CCI_PERI3_eco_num_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int component_id0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_COMP0_UNION;
#endif
#define SOC_CCI400_CCI_COMP0_component_id0_START (0)
#define SOC_CCI400_CCI_COMP0_component_id0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int component_id1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_COMP1_UNION;
#endif
#define SOC_CCI400_CCI_COMP1_component_id1_START (0)
#define SOC_CCI400_CCI_COMP1_component_id1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int component_id2 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_COMP2_UNION;
#endif
#define SOC_CCI400_CCI_COMP2_component_id2_START (0)
#define SOC_CCI400_CCI_COMP2_component_id2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int component_id3 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_COMP3_UNION;
#endif
#define SOC_CCI400_CCI_COMP3_component_id3_START (0)
#define SOC_CCI400_CCI_COMP3_component_id3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int snoop_en : 1;
        unsigned int dvm_en : 1;
        unsigned int reserved : 28;
        unsigned int snoop_support : 1;
        unsigned int dvm_support : 1;
    } reg;
} SOC_CCI400_CCI_SCR_S0_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S0_snoop_en_START (0)
#define SOC_CCI400_CCI_SCR_S0_snoop_en_END (0)
#define SOC_CCI400_CCI_SCR_S0_dvm_en_START (1)
#define SOC_CCI400_CCI_SCR_S0_dvm_en_END (1)
#define SOC_CCI400_CCI_SCR_S0_snoop_support_START (30)
#define SOC_CCI400_CCI_SCR_S0_snoop_support_END (30)
#define SOC_CCI400_CCI_SCR_S0_dvm_support_START (31)
#define SOC_CCI400_CCI_SCR_S0_dvm_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shareable_override : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CCI400_CCI_SOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S0_shareable_override_START (0)
#define SOC_CCI400_CCI_SOR_S0_shareable_override_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int arqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_RCQVOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_ov_START (0)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_ov_END (3)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_value_START (8)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int awqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_WCQVOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_ov_START (0)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_ov_END (3)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_value_START (8)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_reg_en : 1;
        unsigned int rd_s_en : 1;
        unsigned int osd_wr_en : 1;
        unsigned int osd_rd_en : 1;
        unsigned int reserved_0 : 12;
        unsigned int mode_wr : 1;
        unsigned int reserved_1 : 3;
        unsigned int mode_rd : 1;
        unsigned int bandwidth_reg : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_CCI400_CCI_QCR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S0_qos_reg_en_START (0)
#define SOC_CCI400_CCI_QCR_S0_qos_reg_en_END (0)
#define SOC_CCI400_CCI_QCR_S0_rd_s_en_START (1)
#define SOC_CCI400_CCI_QCR_S0_rd_s_en_END (1)
#define SOC_CCI400_CCI_QCR_S0_osd_wr_en_START (2)
#define SOC_CCI400_CCI_QCR_S0_osd_wr_en_END (2)
#define SOC_CCI400_CCI_QCR_S0_osd_rd_en_START (3)
#define SOC_CCI400_CCI_QCR_S0_osd_rd_en_END (3)
#define SOC_CCI400_CCI_QCR_S0_mode_wr_START (16)
#define SOC_CCI400_CCI_QCR_S0_mode_wr_END (16)
#define SOC_CCI400_CCI_QCR_S0_mode_rd_START (20)
#define SOC_CCI400_CCI_QCR_S0_mode_rd_END (20)
#define SOC_CCI400_CCI_QCR_S0_bandwidth_reg_START (21)
#define SOC_CCI400_CCI_QCR_S0_bandwidth_reg_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fra_awaddr : 8;
        unsigned int int_awaddr : 6;
        unsigned int reserved_0 : 2;
        unsigned int fra_araddr : 8;
        unsigned int int_araddr : 6;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_CCI400_CCI_MOTR_S0_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S0_fra_awaddr_START (0)
#define SOC_CCI400_CCI_MOTR_S0_fra_awaddr_END (7)
#define SOC_CCI400_CCI_MOTR_S0_int_awaddr_START (8)
#define SOC_CCI400_CCI_MOTR_S0_int_awaddr_END (13)
#define SOC_CCI400_CCI_MOTR_S0_fra_araddr_START (16)
#define SOC_CCI400_CCI_MOTR_S0_fra_araddr_END (23)
#define SOC_CCI400_CCI_MOTR_S0_int_araddr_START (24)
#define SOC_CCI400_CCI_MOTR_S0_int_araddr_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rt_aw : 12;
        unsigned int reserved_0: 4;
        unsigned int rt_ar : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_CCI400_CCI_RTR_S0_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S0_rt_aw_START (0)
#define SOC_CCI400_CCI_RTR_S0_rt_aw_END (11)
#define SOC_CCI400_CCI_RTR_S0_rt_ar_START (16)
#define SOC_CCI400_CCI_RTR_S0_rt_ar_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_sf : 3;
        unsigned int reserved_0: 5;
        unsigned int arqos_sf : 3;
        unsigned int reserved_1: 21;
    } reg;
} SOC_CCI400_CCI_QRSFR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S0_awqos_sf_START (0)
#define SOC_CCI400_CCI_QRSFR_S0_awqos_sf_END (2)
#define SOC_CCI400_CCI_QRSFR_S0_arqos_sf_START (8)
#define SOC_CCI400_CCI_QRSFR_S0_arqos_sf_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_min : 4;
        unsigned int reserved_0: 4;
        unsigned int awqos_max : 4;
        unsigned int reserved_1: 4;
        unsigned int arqos_min : 4;
        unsigned int reserved_2: 4;
        unsigned int arqos_max : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_CCI400_CCI_QRR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S0_awqos_min_START (0)
#define SOC_CCI400_CCI_QRR_S0_awqos_min_END (3)
#define SOC_CCI400_CCI_QRR_S0_awqos_max_START (8)
#define SOC_CCI400_CCI_QRR_S0_awqos_max_END (11)
#define SOC_CCI400_CCI_QRR_S0_arqos_min_START (16)
#define SOC_CCI400_CCI_QRR_S0_arqos_min_END (19)
#define SOC_CCI400_CCI_QRR_S0_arqos_max_START (24)
#define SOC_CCI400_CCI_QRR_S0_arqos_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int snoop_en : 1;
        unsigned int dvm_en : 1;
        unsigned int reserved : 28;
        unsigned int snoop_support : 1;
        unsigned int dvm_support : 1;
    } reg;
} SOC_CCI400_CCI_SCR_S1_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S1_snoop_en_START (0)
#define SOC_CCI400_CCI_SCR_S1_snoop_en_END (0)
#define SOC_CCI400_CCI_SCR_S1_dvm_en_START (1)
#define SOC_CCI400_CCI_SCR_S1_dvm_en_END (1)
#define SOC_CCI400_CCI_SCR_S1_snoop_support_START (30)
#define SOC_CCI400_CCI_SCR_S1_snoop_support_END (30)
#define SOC_CCI400_CCI_SCR_S1_dvm_support_START (31)
#define SOC_CCI400_CCI_SCR_S1_dvm_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shareable_override : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CCI400_CCI_SOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S1_shareable_override_START (0)
#define SOC_CCI400_CCI_SOR_S1_shareable_override_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int arqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_RCQVOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_ov_START (0)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_ov_END (3)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_value_START (8)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int awqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_WCQVOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_ov_START (0)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_ov_END (3)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_value_START (8)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_reg_en : 1;
        unsigned int rd_s_en : 1;
        unsigned int osd_wr_en : 1;
        unsigned int osd_rd_en : 1;
        unsigned int reserved_0 : 12;
        unsigned int mode_wr : 1;
        unsigned int reserved_1 : 3;
        unsigned int mode_rd : 1;
        unsigned int bandwidth_reg : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_CCI400_CCI_QCR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S1_qos_reg_en_START (0)
#define SOC_CCI400_CCI_QCR_S1_qos_reg_en_END (0)
#define SOC_CCI400_CCI_QCR_S1_rd_s_en_START (1)
#define SOC_CCI400_CCI_QCR_S1_rd_s_en_END (1)
#define SOC_CCI400_CCI_QCR_S1_osd_wr_en_START (2)
#define SOC_CCI400_CCI_QCR_S1_osd_wr_en_END (2)
#define SOC_CCI400_CCI_QCR_S1_osd_rd_en_START (3)
#define SOC_CCI400_CCI_QCR_S1_osd_rd_en_END (3)
#define SOC_CCI400_CCI_QCR_S1_mode_wr_START (16)
#define SOC_CCI400_CCI_QCR_S1_mode_wr_END (16)
#define SOC_CCI400_CCI_QCR_S1_mode_rd_START (20)
#define SOC_CCI400_CCI_QCR_S1_mode_rd_END (20)
#define SOC_CCI400_CCI_QCR_S1_bandwidth_reg_START (21)
#define SOC_CCI400_CCI_QCR_S1_bandwidth_reg_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fra_awaddr : 8;
        unsigned int int_awaddr : 6;
        unsigned int reserved_0 : 2;
        unsigned int fra_araddr : 8;
        unsigned int int_araddr : 6;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_CCI400_CCI_MOTR_S1_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S1_fra_awaddr_START (0)
#define SOC_CCI400_CCI_MOTR_S1_fra_awaddr_END (7)
#define SOC_CCI400_CCI_MOTR_S1_int_awaddr_START (8)
#define SOC_CCI400_CCI_MOTR_S1_int_awaddr_END (13)
#define SOC_CCI400_CCI_MOTR_S1_fra_araddr_START (16)
#define SOC_CCI400_CCI_MOTR_S1_fra_araddr_END (23)
#define SOC_CCI400_CCI_MOTR_S1_int_araddr_START (24)
#define SOC_CCI400_CCI_MOTR_S1_int_araddr_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rt_aw : 12;
        unsigned int reserved_0: 4;
        unsigned int rt_ar : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_CCI400_CCI_RTR_S1_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S1_rt_aw_START (0)
#define SOC_CCI400_CCI_RTR_S1_rt_aw_END (11)
#define SOC_CCI400_CCI_RTR_S1_rt_ar_START (16)
#define SOC_CCI400_CCI_RTR_S1_rt_ar_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_sf : 3;
        unsigned int reserved_0: 5;
        unsigned int arqos_sf : 3;
        unsigned int reserved_1: 21;
    } reg;
} SOC_CCI400_CCI_QRSFR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S1_awqos_sf_START (0)
#define SOC_CCI400_CCI_QRSFR_S1_awqos_sf_END (2)
#define SOC_CCI400_CCI_QRSFR_S1_arqos_sf_START (8)
#define SOC_CCI400_CCI_QRSFR_S1_arqos_sf_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_min : 4;
        unsigned int reserved_0: 4;
        unsigned int awqos_max : 4;
        unsigned int reserved_1: 4;
        unsigned int arqos_min : 4;
        unsigned int reserved_2: 4;
        unsigned int arqos_max : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_CCI400_CCI_QRR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S1_awqos_min_START (0)
#define SOC_CCI400_CCI_QRR_S1_awqos_min_END (3)
#define SOC_CCI400_CCI_QRR_S1_awqos_max_START (8)
#define SOC_CCI400_CCI_QRR_S1_awqos_max_END (11)
#define SOC_CCI400_CCI_QRR_S1_arqos_min_START (16)
#define SOC_CCI400_CCI_QRR_S1_arqos_min_END (19)
#define SOC_CCI400_CCI_QRR_S1_arqos_max_START (24)
#define SOC_CCI400_CCI_QRR_S1_arqos_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int snoop_en : 1;
        unsigned int dvm_en : 1;
        unsigned int reserved : 28;
        unsigned int snoop_support : 1;
        unsigned int dvm_support : 1;
    } reg;
} SOC_CCI400_CCI_SCR_S2_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S2_snoop_en_START (0)
#define SOC_CCI400_CCI_SCR_S2_snoop_en_END (0)
#define SOC_CCI400_CCI_SCR_S2_dvm_en_START (1)
#define SOC_CCI400_CCI_SCR_S2_dvm_en_END (1)
#define SOC_CCI400_CCI_SCR_S2_snoop_support_START (30)
#define SOC_CCI400_CCI_SCR_S2_snoop_support_END (30)
#define SOC_CCI400_CCI_SCR_S2_dvm_support_START (31)
#define SOC_CCI400_CCI_SCR_S2_dvm_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shareable_override : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CCI400_CCI_SOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S2_shareable_override_START (0)
#define SOC_CCI400_CCI_SOR_S2_shareable_override_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int arqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_RCQVOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_ov_START (0)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_ov_END (3)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_value_START (8)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int awqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_WCQVOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_ov_START (0)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_ov_END (3)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_value_START (8)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_reg_en : 1;
        unsigned int rd_s_en : 1;
        unsigned int osd_wr_en : 1;
        unsigned int osd_rd_en : 1;
        unsigned int reserved_0 : 12;
        unsigned int mode_wr : 1;
        unsigned int reserved_1 : 3;
        unsigned int mode_rd : 1;
        unsigned int bandwidth_reg : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_CCI400_CCI_QCR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S2_qos_reg_en_START (0)
#define SOC_CCI400_CCI_QCR_S2_qos_reg_en_END (0)
#define SOC_CCI400_CCI_QCR_S2_rd_s_en_START (1)
#define SOC_CCI400_CCI_QCR_S2_rd_s_en_END (1)
#define SOC_CCI400_CCI_QCR_S2_osd_wr_en_START (2)
#define SOC_CCI400_CCI_QCR_S2_osd_wr_en_END (2)
#define SOC_CCI400_CCI_QCR_S2_osd_rd_en_START (3)
#define SOC_CCI400_CCI_QCR_S2_osd_rd_en_END (3)
#define SOC_CCI400_CCI_QCR_S2_mode_wr_START (16)
#define SOC_CCI400_CCI_QCR_S2_mode_wr_END (16)
#define SOC_CCI400_CCI_QCR_S2_mode_rd_START (20)
#define SOC_CCI400_CCI_QCR_S2_mode_rd_END (20)
#define SOC_CCI400_CCI_QCR_S2_bandwidth_reg_START (21)
#define SOC_CCI400_CCI_QCR_S2_bandwidth_reg_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fra_awaddr : 8;
        unsigned int int_awaddr : 6;
        unsigned int reserved_0 : 2;
        unsigned int fra_araddr : 8;
        unsigned int int_araddr : 6;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_CCI400_CCI_MOTR_S2_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S2_fra_awaddr_START (0)
#define SOC_CCI400_CCI_MOTR_S2_fra_awaddr_END (7)
#define SOC_CCI400_CCI_MOTR_S2_int_awaddr_START (8)
#define SOC_CCI400_CCI_MOTR_S2_int_awaddr_END (13)
#define SOC_CCI400_CCI_MOTR_S2_fra_araddr_START (16)
#define SOC_CCI400_CCI_MOTR_S2_fra_araddr_END (23)
#define SOC_CCI400_CCI_MOTR_S2_int_araddr_START (24)
#define SOC_CCI400_CCI_MOTR_S2_int_araddr_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rt_aw : 12;
        unsigned int reserved_0: 4;
        unsigned int rt_ar : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_CCI400_CCI_RTR_S2_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S2_rt_aw_START (0)
#define SOC_CCI400_CCI_RTR_S2_rt_aw_END (11)
#define SOC_CCI400_CCI_RTR_S2_rt_ar_START (16)
#define SOC_CCI400_CCI_RTR_S2_rt_ar_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_sf : 3;
        unsigned int reserved_0: 5;
        unsigned int arqos_sf : 3;
        unsigned int reserved_1: 21;
    } reg;
} SOC_CCI400_CCI_QRSFR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S2_awqos_sf_START (0)
#define SOC_CCI400_CCI_QRSFR_S2_awqos_sf_END (2)
#define SOC_CCI400_CCI_QRSFR_S2_arqos_sf_START (8)
#define SOC_CCI400_CCI_QRSFR_S2_arqos_sf_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_min : 4;
        unsigned int reserved_0: 4;
        unsigned int awqos_max : 4;
        unsigned int reserved_1: 4;
        unsigned int arqos_min : 4;
        unsigned int reserved_2: 4;
        unsigned int arqos_max : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_CCI400_CCI_QRR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S2_awqos_min_START (0)
#define SOC_CCI400_CCI_QRR_S2_awqos_min_END (3)
#define SOC_CCI400_CCI_QRR_S2_awqos_max_START (8)
#define SOC_CCI400_CCI_QRR_S2_awqos_max_END (11)
#define SOC_CCI400_CCI_QRR_S2_arqos_min_START (16)
#define SOC_CCI400_CCI_QRR_S2_arqos_min_END (19)
#define SOC_CCI400_CCI_QRR_S2_arqos_max_START (24)
#define SOC_CCI400_CCI_QRR_S2_arqos_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int snoop_en : 1;
        unsigned int dvm_en : 1;
        unsigned int reserved : 28;
        unsigned int snoop_support : 1;
        unsigned int dvm_support : 1;
    } reg;
} SOC_CCI400_CCI_SCR_S3_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S3_snoop_en_START (0)
#define SOC_CCI400_CCI_SCR_S3_snoop_en_END (0)
#define SOC_CCI400_CCI_SCR_S3_dvm_en_START (1)
#define SOC_CCI400_CCI_SCR_S3_dvm_en_END (1)
#define SOC_CCI400_CCI_SCR_S3_snoop_support_START (30)
#define SOC_CCI400_CCI_SCR_S3_snoop_support_END (30)
#define SOC_CCI400_CCI_SCR_S3_dvm_support_START (31)
#define SOC_CCI400_CCI_SCR_S3_dvm_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int arqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_RCQVOR_S3_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_ov_START (0)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_ov_END (3)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_value_START (8)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int awqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_WCQVOR_S3_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_ov_START (0)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_ov_END (3)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_value_START (8)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_reg_en : 1;
        unsigned int rd_s_en : 1;
        unsigned int osd_wr_en : 1;
        unsigned int osd_rd_en : 1;
        unsigned int reserved_0 : 12;
        unsigned int mode_wr : 1;
        unsigned int reserved_1 : 3;
        unsigned int mode_rd : 1;
        unsigned int bandwidth_reg : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_CCI400_CCI_QCR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S3_qos_reg_en_START (0)
#define SOC_CCI400_CCI_QCR_S3_qos_reg_en_END (0)
#define SOC_CCI400_CCI_QCR_S3_rd_s_en_START (1)
#define SOC_CCI400_CCI_QCR_S3_rd_s_en_END (1)
#define SOC_CCI400_CCI_QCR_S3_osd_wr_en_START (2)
#define SOC_CCI400_CCI_QCR_S3_osd_wr_en_END (2)
#define SOC_CCI400_CCI_QCR_S3_osd_rd_en_START (3)
#define SOC_CCI400_CCI_QCR_S3_osd_rd_en_END (3)
#define SOC_CCI400_CCI_QCR_S3_mode_wr_START (16)
#define SOC_CCI400_CCI_QCR_S3_mode_wr_END (16)
#define SOC_CCI400_CCI_QCR_S3_mode_rd_START (20)
#define SOC_CCI400_CCI_QCR_S3_mode_rd_END (20)
#define SOC_CCI400_CCI_QCR_S3_bandwidth_reg_START (21)
#define SOC_CCI400_CCI_QCR_S3_bandwidth_reg_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rt_aw : 12;
        unsigned int reserved_0: 4;
        unsigned int rt_ar : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_CCI400_CCI_RTR_S3_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S3_rt_aw_START (0)
#define SOC_CCI400_CCI_RTR_S3_rt_aw_END (11)
#define SOC_CCI400_CCI_RTR_S3_rt_ar_START (16)
#define SOC_CCI400_CCI_RTR_S3_rt_ar_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_sf : 3;
        unsigned int reserved_0: 5;
        unsigned int arqos_sf : 3;
        unsigned int reserved_1: 21;
    } reg;
} SOC_CCI400_CCI_QRSFR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S3_awqos_sf_START (0)
#define SOC_CCI400_CCI_QRSFR_S3_awqos_sf_END (2)
#define SOC_CCI400_CCI_QRSFR_S3_arqos_sf_START (8)
#define SOC_CCI400_CCI_QRSFR_S3_arqos_sf_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_min : 4;
        unsigned int reserved_0: 4;
        unsigned int awqos_max : 4;
        unsigned int reserved_1: 4;
        unsigned int arqos_min : 4;
        unsigned int reserved_2: 4;
        unsigned int arqos_max : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_CCI400_CCI_QRR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S3_awqos_min_START (0)
#define SOC_CCI400_CCI_QRR_S3_awqos_min_END (3)
#define SOC_CCI400_CCI_QRR_S3_awqos_max_START (8)
#define SOC_CCI400_CCI_QRR_S3_awqos_max_END (11)
#define SOC_CCI400_CCI_QRR_S3_arqos_min_START (16)
#define SOC_CCI400_CCI_QRR_S3_arqos_min_END (19)
#define SOC_CCI400_CCI_QRR_S3_arqos_max_START (24)
#define SOC_CCI400_CCI_QRR_S3_arqos_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int snoop_en : 1;
        unsigned int dvm_en : 1;
        unsigned int reserved : 28;
        unsigned int snoop_support : 1;
        unsigned int dvm_support : 1;
    } reg;
} SOC_CCI400_CCI_SCR_S4_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S4_snoop_en_START (0)
#define SOC_CCI400_CCI_SCR_S4_snoop_en_END (0)
#define SOC_CCI400_CCI_SCR_S4_dvm_en_START (1)
#define SOC_CCI400_CCI_SCR_S4_dvm_en_END (1)
#define SOC_CCI400_CCI_SCR_S4_snoop_support_START (30)
#define SOC_CCI400_CCI_SCR_S4_snoop_support_END (30)
#define SOC_CCI400_CCI_SCR_S4_dvm_support_START (31)
#define SOC_CCI400_CCI_SCR_S4_dvm_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int arqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_RCQVOR_S4_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_ov_START (0)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_ov_END (3)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_value_START (8)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_ov : 4;
        unsigned int reserved_0 : 4;
        unsigned int awqos_value : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_CCI400_CCI_WCQVOR_S4_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_ov_START (0)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_ov_END (3)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_value_START (8)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_value_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int qos_reg_en : 1;
        unsigned int rd_s_en : 1;
        unsigned int osd_wr_en : 1;
        unsigned int osd_rd_en : 1;
        unsigned int reserved_0 : 12;
        unsigned int mode_wr : 1;
        unsigned int reserved_1 : 3;
        unsigned int mode_rd : 1;
        unsigned int bandwidth_reg : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_CCI400_CCI_QCR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S4_qos_reg_en_START (0)
#define SOC_CCI400_CCI_QCR_S4_qos_reg_en_END (0)
#define SOC_CCI400_CCI_QCR_S4_rd_s_en_START (1)
#define SOC_CCI400_CCI_QCR_S4_rd_s_en_END (1)
#define SOC_CCI400_CCI_QCR_S4_osd_wr_en_START (2)
#define SOC_CCI400_CCI_QCR_S4_osd_wr_en_END (2)
#define SOC_CCI400_CCI_QCR_S4_osd_rd_en_START (3)
#define SOC_CCI400_CCI_QCR_S4_osd_rd_en_END (3)
#define SOC_CCI400_CCI_QCR_S4_mode_wr_START (16)
#define SOC_CCI400_CCI_QCR_S4_mode_wr_END (16)
#define SOC_CCI400_CCI_QCR_S4_mode_rd_START (20)
#define SOC_CCI400_CCI_QCR_S4_mode_rd_END (20)
#define SOC_CCI400_CCI_QCR_S4_bandwidth_reg_START (21)
#define SOC_CCI400_CCI_QCR_S4_bandwidth_reg_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rt_aw : 12;
        unsigned int reserved_0: 4;
        unsigned int rt_ar : 12;
        unsigned int reserved_1: 4;
    } reg;
} SOC_CCI400_CCI_RTR_S4_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S4_rt_aw_START (0)
#define SOC_CCI400_CCI_RTR_S4_rt_aw_END (11)
#define SOC_CCI400_CCI_RTR_S4_rt_ar_START (16)
#define SOC_CCI400_CCI_RTR_S4_rt_ar_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_sf : 3;
        unsigned int reserved_0: 5;
        unsigned int arqos_sf : 3;
        unsigned int reserved_1: 21;
    } reg;
} SOC_CCI400_CCI_QRSFR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S4_awqos_sf_START (0)
#define SOC_CCI400_CCI_QRSFR_S4_awqos_sf_END (2)
#define SOC_CCI400_CCI_QRSFR_S4_arqos_sf_START (8)
#define SOC_CCI400_CCI_QRSFR_S4_arqos_sf_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awqos_min : 4;
        unsigned int reserved_0: 4;
        unsigned int awqos_max : 4;
        unsigned int reserved_1: 4;
        unsigned int arqos_min : 4;
        unsigned int reserved_2: 4;
        unsigned int arqos_max : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_CCI400_CCI_QRR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S4_awqos_min_START (0)
#define SOC_CCI400_CCI_QRR_S4_awqos_min_END (3)
#define SOC_CCI400_CCI_QRR_S4_awqos_max_START (8)
#define SOC_CCI400_CCI_QRR_S4_awqos_max_END (11)
#define SOC_CCI400_CCI_QRR_S4_arqos_min_START (16)
#define SOC_CCI400_CCI_QRR_S4_arqos_min_END (19)
#define SOC_CCI400_CCI_QRR_S4_arqos_max_START (24)
#define SOC_CCI400_CCI_QRR_S4_arqos_max_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_cycle_cnt : 32;
    } reg;
} SOC_CCI400_CCI_ECCR_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_event_cycle_cnt_START (0)
#define SOC_CCI400_CCI_ECCR_event_cycle_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_CCR_UNION;
#endif
#define SOC_CCI400_CCI_CCR_cnt_en_START (0)
#define SOC_CCI400_CCI_CCR_cnt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflow_flag : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_OFSR_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_overflow_flag_START (0)
#define SOC_CCI400_CCI_OFSR_overflow_flag_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_mon : 5;
        unsigned int int_mon : 3;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_ESR_0_UNION;
#endif
#define SOC_CCI400_CCI_ESR_0_event_mon_START (0)
#define SOC_CCI400_CCI_ESR_0_event_mon_END (4)
#define SOC_CCI400_CCI_ESR_0_int_mon_START (5)
#define SOC_CCI400_CCI_ESR_0_int_mon_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_cycle_cnt : 32;
    } reg;
} SOC_CCI400_CCI_ECCR_0_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_0_event_cycle_cnt_START (0)
#define SOC_CCI400_CCI_ECCR_0_event_cycle_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_CCR_0_UNION;
#endif
#define SOC_CCI400_CCI_CCR_0_cnt_en_START (0)
#define SOC_CCI400_CCI_CCR_0_cnt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflow_flag : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_OFSR_0_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_0_overflow_flag_START (0)
#define SOC_CCI400_CCI_OFSR_0_overflow_flag_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_mon : 5;
        unsigned int int_mon : 3;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_ESR_1_UNION;
#endif
#define SOC_CCI400_CCI_ESR_1_event_mon_START (0)
#define SOC_CCI400_CCI_ESR_1_event_mon_END (4)
#define SOC_CCI400_CCI_ESR_1_int_mon_START (5)
#define SOC_CCI400_CCI_ESR_1_int_mon_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_cycle_cnt : 32;
    } reg;
} SOC_CCI400_CCI_ECCR_1_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_1_event_cycle_cnt_START (0)
#define SOC_CCI400_CCI_ECCR_1_event_cycle_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_CCR_1_UNION;
#endif
#define SOC_CCI400_CCI_CCR_1_cnt_en_START (0)
#define SOC_CCI400_CCI_CCR_1_cnt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflow_flag : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_OFSR_1_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_1_overflow_flag_START (0)
#define SOC_CCI400_CCI_OFSR_1_overflow_flag_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_mon : 5;
        unsigned int int_mon : 3;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_ESR_2_UNION;
#endif
#define SOC_CCI400_CCI_ESR_2_event_mon_START (0)
#define SOC_CCI400_CCI_ESR_2_event_mon_END (4)
#define SOC_CCI400_CCI_ESR_2_int_mon_START (5)
#define SOC_CCI400_CCI_ESR_2_int_mon_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_cycle_cnt : 32;
    } reg;
} SOC_CCI400_CCI_ECCR_2_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_2_event_cycle_cnt_START (0)
#define SOC_CCI400_CCI_ECCR_2_event_cycle_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_CCR_2_UNION;
#endif
#define SOC_CCI400_CCI_CCR_2_cnt_en_START (0)
#define SOC_CCI400_CCI_CCR_2_cnt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflow_flag : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_OFSR_2_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_2_overflow_flag_START (0)
#define SOC_CCI400_CCI_OFSR_2_overflow_flag_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_mon : 5;
        unsigned int int_mon : 3;
        unsigned int reserved : 24;
    } reg;
} SOC_CCI400_CCI_ESR_3_UNION;
#endif
#define SOC_CCI400_CCI_ESR_3_event_mon_START (0)
#define SOC_CCI400_CCI_ESR_3_event_mon_END (4)
#define SOC_CCI400_CCI_ESR_3_int_mon_START (5)
#define SOC_CCI400_CCI_ESR_3_int_mon_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_cycle_cnt : 32;
    } reg;
} SOC_CCI400_CCI_ECCR_3_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_3_event_cycle_cnt_START (0)
#define SOC_CCI400_CCI_ECCR_3_event_cycle_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_CCR_3_UNION;
#endif
#define SOC_CCI400_CCI_CCR_3_cnt_en_START (0)
#define SOC_CCI400_CCI_CCR_3_cnt_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflow_flag : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CCI400_CCI_OFSR_3_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_3_overflow_flag_START (0)
#define SOC_CCI400_CCI_OFSR_3_overflow_flag_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
