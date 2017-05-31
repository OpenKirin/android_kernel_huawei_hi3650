#ifndef __SOC_CS_STM_INTERFACE_H__
#define __SOC_CS_STM_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_STM_STM_DMASTARTR_ADDR(base) ((base) + (0xC04))
#define SOC_CS_STM_STM_DMASTOPR_ADDR(base) ((base) + (0xC08))
#define SOC_CS_STM_STM_DMASTATR_ADDR(base) ((base) + (0xC0C))
#define SOC_CS_STM_STM_DMACTLR_ADDR(base) ((base) + (0xC10))
#define SOC_CS_STM_STM_HEER_ADDR(base) ((base) + (0xD00))
#define SOC_CS_STM_STM_HETER_ADDR(base) ((base) + (0xD20))
#define SOC_CS_STM_STM_HEBSR_ADDR(base) ((base) + (0xD60))
#define SOC_CS_STM_STM_HEMCR_ADDR(base) ((base) + (0xD64))
#define SOC_CS_STM_STM_HEEXTMUXR_ADDR(base) ((base) + (0xD68))
#define SOC_CS_STM_STM_HEMASTR_ADDR(base) ((base) + (0xDF4))
#define SOC_CS_STM_STM_HEFEAT1R_ADDR(base) ((base) + (0xDF8))
#define SOC_CS_STM_STM_HEIDR_ADDR(base) ((base) + (0xDFC))
#define SOC_CS_STM_STM_SPER_ADDR(base) ((base) + (0xE00))
#define SOC_CS_STM_STM_SPTER_ADDR(base) ((base) + (0xE20))
#define SOC_CS_STM_STM_SPSCR_ADDR(base) ((base) + (0xE60))
#define SOC_CS_STM_STM_SPMSCR_ADDR(base) ((base) + (0xE64))
#define SOC_CS_STM_STM_SPOVERRIDER_ADDR(base) ((base) + (0xE68))
#define SOC_CS_STM_STM_SPMOVERRIDER_ADDR(base) ((base) + (0xE6C))
#define SOC_CS_STM_STM_SPTRIGCSR_ADDR(base) ((base) + (0xE70))
#define SOC_CS_STM_STM_TCSR_ADDR(base) ((base) + (0xE80))
#define SOC_CS_STM_STM_TSSTIMR_ADDR(base) ((base) + (0xE84))
#define SOC_CS_STM_STM_TSFREQR_ADDR(base) ((base) + (0xE8C))
#define SOC_CS_STM_STM_SYNCR_ADDR(base) ((base) + (0xE90))
#define SOC_CS_STM_STM_AUXCR_ADDR(base) ((base) + (0xE94))
#define SOC_CS_STM_STM_LAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_STM_STM_LSR_ADDR(base) ((base) + (0xFB4))
#define SOC_CS_STM_STM_AUTHSTATUS_ADDR(base) ((base) + (0xFB8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_STM_STM_DMASTARTR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTARTR_start_START (0)
#define SOC_CS_STM_STM_DMASTARTR_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stop : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_STM_STM_DMASTOPR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTOPR_stop_START (0)
#define SOC_CS_STM_STM_DMASTOPR_stop_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int status : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_STM_STM_DMASTATR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTATR_status_START (0)
#define SOC_CS_STM_STM_DMASTATR_status_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 2;
        unsigned int sens : 2;
        unsigned int reserved_1: 28;
    } reg;
} SOC_CS_STM_STM_DMACTLR_UNION;
#endif
#define SOC_CS_STM_STM_DMACTLR_sens_START (2)
#define SOC_CS_STM_STM_DMACTLR_sens_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int heen : 32;
    } reg;
} SOC_CS_STM_STM_HEER_UNION;
#endif
#define SOC_CS_STM_STM_HEER_heen_START (0)
#define SOC_CS_STM_STM_HEER_heen_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hete : 32;
    } reg;
} SOC_CS_STM_STM_HETER_UNION;
#endif
#define SOC_CS_STM_STM_HETER_hete_START (0)
#define SOC_CS_STM_STM_HETER_hete_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hebs : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_STM_STM_HEBSR_UNION;
#endif
#define SOC_CS_STM_STM_HEBSR_hebs_START (0)
#define SOC_CS_STM_STM_HEBSR_hebs_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int compen : 1;
        unsigned int errdetect : 1;
        unsigned int reserved_0 : 1;
        unsigned int trigctl : 1;
        unsigned int trigstatus : 1;
        unsigned int trigclear : 1;
        unsigned int atbtrigen : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_CS_STM_STM_HEMCR_UNION;
#endif
#define SOC_CS_STM_STM_HEMCR_en_START (0)
#define SOC_CS_STM_STM_HEMCR_en_END (0)
#define SOC_CS_STM_STM_HEMCR_compen_START (1)
#define SOC_CS_STM_STM_HEMCR_compen_END (1)
#define SOC_CS_STM_STM_HEMCR_errdetect_START (2)
#define SOC_CS_STM_STM_HEMCR_errdetect_END (2)
#define SOC_CS_STM_STM_HEMCR_trigctl_START (4)
#define SOC_CS_STM_STM_HEMCR_trigctl_END (4)
#define SOC_CS_STM_STM_HEMCR_trigstatus_START (5)
#define SOC_CS_STM_STM_HEMCR_trigstatus_END (5)
#define SOC_CS_STM_STM_HEMCR_trigclear_START (6)
#define SOC_CS_STM_STM_HEMCR_trigclear_END (6)
#define SOC_CS_STM_STM_HEMCR_atbtrigen_START (7)
#define SOC_CS_STM_STM_HEMCR_atbtrigen_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int extmux : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_STM_STM_HEEXTMUXR_UNION;
#endif
#define SOC_CS_STM_STM_HEEXTMUXR_extmux_START (0)
#define SOC_CS_STM_STM_HEEXTMUXR_extmux_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int master : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_STM_STM_HEMASTR_UNION;
#endif
#define SOC_CS_STM_STM_HEMASTR_master_START (0)
#define SOC_CS_STM_STM_HEMASTR_master_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int heter : 1;
        unsigned int reserved_0 : 1;
        unsigned int heerr : 1;
        unsigned int hemaster : 1;
        unsigned int hecomp : 2;
        unsigned int reserved_1 : 9;
        unsigned int numhe : 9;
        unsigned int reserved_2 : 4;
        unsigned int heextmuxsize : 3;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_CS_STM_STM_HEFEAT1R_UNION;
#endif
#define SOC_CS_STM_STM_HEFEAT1R_heter_START (0)
#define SOC_CS_STM_STM_HEFEAT1R_heter_END (0)
#define SOC_CS_STM_STM_HEFEAT1R_heerr_START (2)
#define SOC_CS_STM_STM_HEFEAT1R_heerr_END (2)
#define SOC_CS_STM_STM_HEFEAT1R_hemaster_START (3)
#define SOC_CS_STM_STM_HEFEAT1R_hemaster_END (3)
#define SOC_CS_STM_STM_HEFEAT1R_hecomp_START (4)
#define SOC_CS_STM_STM_HEFEAT1R_hecomp_END (5)
#define SOC_CS_STM_STM_HEFEAT1R_numhe_START (15)
#define SOC_CS_STM_STM_HEFEAT1R_numhe_END (23)
#define SOC_CS_STM_STM_HEFEAT1R_heextmuxsize_START (28)
#define SOC_CS_STM_STM_HEFEAT1R_heextmuxsize_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int class : 4;
        unsigned int classrev : 4;
        unsigned int vendspec : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_CS_STM_STM_HEIDR_UNION;
#endif
#define SOC_CS_STM_STM_HEIDR_class_START (0)
#define SOC_CS_STM_STM_HEIDR_class_END (3)
#define SOC_CS_STM_STM_HEIDR_classrev_START (4)
#define SOC_CS_STM_STM_HEIDR_classrev_END (7)
#define SOC_CS_STM_STM_HEIDR_vendspec_START (8)
#define SOC_CS_STM_STM_HEIDR_vendspec_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spe : 32;
    } reg;
} SOC_CS_STM_STM_SPER_UNION;
#endif
#define SOC_CS_STM_STM_SPER_spe_START (0)
#define SOC_CS_STM_STM_SPER_spe_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spte : 32;
    } reg;
} SOC_CS_STM_STM_SPTER_UNION;
#endif
#define SOC_CS_STM_STM_SPTER_spte_START (0)
#define SOC_CS_STM_STM_SPTER_spte_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int portctl : 2;
        unsigned int reserved : 18;
        unsigned int portsel : 12;
    } reg;
} SOC_CS_STM_STM_SPSCR_UNION;
#endif
#define SOC_CS_STM_STM_SPSCR_portctl_START (0)
#define SOC_CS_STM_STM_SPSCR_portctl_END (1)
#define SOC_CS_STM_STM_SPSCR_portsel_START (20)
#define SOC_CS_STM_STM_SPSCR_portsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mastctl : 1;
        unsigned int reserved : 14;
        unsigned int mastsel : 17;
    } reg;
} SOC_CS_STM_STM_SPMSCR_UNION;
#endif
#define SOC_CS_STM_STM_SPMSCR_mastctl_START (0)
#define SOC_CS_STM_STM_SPMSCR_mastctl_END (0)
#define SOC_CS_STM_STM_SPMSCR_mastsel_START (15)
#define SOC_CS_STM_STM_SPMSCR_mastsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overctl : 2;
        unsigned int overts : 1;
        unsigned int reserved : 12;
        unsigned int portsel : 17;
    } reg;
} SOC_CS_STM_STM_SPOVERRIDER_UNION;
#endif
#define SOC_CS_STM_STM_SPOVERRIDER_overctl_START (0)
#define SOC_CS_STM_STM_SPOVERRIDER_overctl_END (1)
#define SOC_CS_STM_STM_SPOVERRIDER_overts_START (2)
#define SOC_CS_STM_STM_SPOVERRIDER_overts_END (2)
#define SOC_CS_STM_STM_SPOVERRIDER_portsel_START (15)
#define SOC_CS_STM_STM_SPOVERRIDER_portsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mastctl : 1;
        unsigned int reserved : 14;
        unsigned int mastsel : 17;
    } reg;
} SOC_CS_STM_STM_SPMOVERRIDER_UNION;
#endif
#define SOC_CS_STM_STM_SPMOVERRIDER_mastctl_START (0)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastctl_END (0)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastsel_START (15)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastsel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigctl : 1;
        unsigned int trigstatus : 1;
        unsigned int trigclear : 1;
        unsigned int atbtrigen_te : 1;
        unsigned int atbtrigen_dir : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CS_STM_STM_SPTRIGCSR_UNION;
#endif
#define SOC_CS_STM_STM_SPTRIGCSR_trigctl_START (0)
#define SOC_CS_STM_STM_SPTRIGCSR_trigctl_END (0)
#define SOC_CS_STM_STM_SPTRIGCSR_trigstatus_START (1)
#define SOC_CS_STM_STM_SPTRIGCSR_trigstatus_END (1)
#define SOC_CS_STM_STM_SPTRIGCSR_trigclear_START (2)
#define SOC_CS_STM_STM_SPTRIGCSR_trigclear_END (2)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_te_START (3)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_te_END (3)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_dir_START (4)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_dir_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int tsen : 1;
        unsigned int syncen : 1;
        unsigned int reserved_0: 2;
        unsigned int compen : 1;
        unsigned int reserved_1: 10;
        unsigned int traceid : 7;
        unsigned int busy : 1;
        unsigned int reserved_2: 8;
    } reg;
} SOC_CS_STM_STM_TCSR_UNION;
#endif
#define SOC_CS_STM_STM_TCSR_en_START (0)
#define SOC_CS_STM_STM_TCSR_en_END (0)
#define SOC_CS_STM_STM_TCSR_tsen_START (1)
#define SOC_CS_STM_STM_TCSR_tsen_END (1)
#define SOC_CS_STM_STM_TCSR_syncen_START (2)
#define SOC_CS_STM_STM_TCSR_syncen_END (2)
#define SOC_CS_STM_STM_TCSR_compen_START (5)
#define SOC_CS_STM_STM_TCSR_compen_END (5)
#define SOC_CS_STM_STM_TCSR_traceid_START (16)
#define SOC_CS_STM_STM_TCSR_traceid_END (22)
#define SOC_CS_STM_STM_TCSR_busy_START (23)
#define SOC_CS_STM_STM_TCSR_busy_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int forcets : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_STM_STM_TSSTIMR_UNION;
#endif
#define SOC_CS_STM_STM_TSSTIMR_forcets_START (0)
#define SOC_CS_STM_STM_TSSTIMR_forcets_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int freq : 32;
    } reg;
} SOC_CS_STM_STM_TSFREQR_UNION;
#endif
#define SOC_CS_STM_STM_TSFREQR_freq_START (0)
#define SOC_CS_STM_STM_TSFREQR_freq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int count : 12;
        unsigned int mode : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_CS_STM_STM_SYNCR_UNION;
#endif
#define SOC_CS_STM_STM_SYNCR_count_START (0)
#define SOC_CS_STM_STM_SYNCR_count_END (11)
#define SOC_CS_STM_STM_SYNCR_mode_START (12)
#define SOC_CS_STM_STM_SYNCR_mode_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fifoaf : 1;
        unsigned int asyncpe : 1;
        unsigned int priorinvdis : 1;
        unsigned int reserved_0 : 4;
        unsigned int qhwevoverride : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_CS_STM_STM_AUXCR_UNION;
#endif
#define SOC_CS_STM_STM_AUXCR_fifoaf_START (0)
#define SOC_CS_STM_STM_AUXCR_fifoaf_END (0)
#define SOC_CS_STM_STM_AUXCR_asyncpe_START (1)
#define SOC_CS_STM_STM_AUXCR_asyncpe_END (1)
#define SOC_CS_STM_STM_AUXCR_priorinvdis_START (2)
#define SOC_CS_STM_STM_AUXCR_priorinvdis_END (2)
#define SOC_CS_STM_STM_AUXCR_qhwevoverride_START (7)
#define SOC_CS_STM_STM_AUXCR_qhwevoverride_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_STM_STM_LAR_UNION;
#endif
#define SOC_CS_STM_STM_LAR_key_START (0)
#define SOC_CS_STM_STM_LAR_key_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sli : 1;
        unsigned int slk : 1;
        unsigned int ntt : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CS_STM_STM_LSR_UNION;
#endif
#define SOC_CS_STM_STM_LSR_sli_START (0)
#define SOC_CS_STM_STM_LSR_sli_END (0)
#define SOC_CS_STM_STM_LSR_slk_START (1)
#define SOC_CS_STM_STM_LSR_slk_END (1)
#define SOC_CS_STM_STM_LSR_ntt_START (2)
#define SOC_CS_STM_STM_LSR_ntt_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nsid : 2;
        unsigned int nsnid : 2;
        unsigned int sid : 2;
        unsigned int snid : 2;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_STM_STM_AUTHSTATUS_UNION;
#endif
#define SOC_CS_STM_STM_AUTHSTATUS_nsid_START (0)
#define SOC_CS_STM_STM_AUTHSTATUS_nsid_END (1)
#define SOC_CS_STM_STM_AUTHSTATUS_nsnid_START (2)
#define SOC_CS_STM_STM_AUTHSTATUS_nsnid_END (3)
#define SOC_CS_STM_STM_AUTHSTATUS_sid_START (4)
#define SOC_CS_STM_STM_AUTHSTATUS_sid_END (5)
#define SOC_CS_STM_STM_AUTHSTATUS_snid_START (6)
#define SOC_CS_STM_STM_AUTHSTATUS_snid_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
