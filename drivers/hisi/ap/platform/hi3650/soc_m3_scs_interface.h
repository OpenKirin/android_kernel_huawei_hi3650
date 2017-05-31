#ifndef __SOC_M3_SCS_INTERFACE_H__
#define __SOC_M3_SCS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_M3_SCS_ICTR_ADDR(base) ((base) + (0x004))
#define SOC_M3_SCS_ACTLR_ADDR(base) ((base) + (0x008))
#define SOC_M3_SCS_STCSR_ADDR(base) ((base) + (0x010))
#define SOC_M3_SCS_STRVR_ADDR(base) ((base) + (0x014))
#define SOC_M3_SCS_STCVR_ADDR(base) ((base) + (0x018))
#define SOC_M3_SCS_STCR_ADDR(base) ((base) + (0x01C))
#define SOC_M3_SCS_NVIC_ISERn_ADDR(base,n) ((base) + (0x100+(n)*4))
#define SOC_M3_SCS_NVIC_ICERn_ADDR(base,n) ((base) + (0x180+(n)*4))
#define SOC_M3_SCS_NVIC_ISPRn_ADDR(base,n) ((base) + (0x200+(n)*4))
#define SOC_M3_SCS_NVIC_ICPRn_ADDR(base,n) ((base) + (0x280+(n)*4))
#define SOC_M3_SCS_NVIC_IABRn_ADDR(base,n) ((base) + (0x300+(n)*4))
#define SOC_M3_SCS_NVIC_IPRm_ADDR(base,m) ((base) + (0x400+(m)*4))
#define SOC_M3_SCS_CPUID_ADDR(base) ((base) + (0xD00))
#define SOC_M3_SCS_ICSR_ADDR(base) ((base) + (0xD04))
#define SOC_M3_SCS_VTOR_ADDR(base) ((base) + (0xD08))
#define SOC_M3_SCS_AIRCR_ADDR(base) ((base) + (0xD0C))
#define SOC_M3_SCS_SCR_ADDR(base) ((base) + (0xD10))
#define SOC_M3_SCS_CCR_ADDR(base) ((base) + (0xD14))
#define SOC_M3_SCS_SHPR1_ADDR(base) ((base) + (0xD18))
#define SOC_M3_SCS_SHPR2_ADDR(base) ((base) + (0xD1C))
#define SOC_M3_SCS_SHPR3_ADDR(base) ((base) + (0xD20))
#define SOC_M3_SCS_SHCSR_ADDR(base) ((base) + (0xD24))
#define SOC_M3_SCS_CFSR_ADDR(base) ((base) + (0xD28))
#define SOC_M3_SCS_HFSR_ADDR(base) ((base) + (0xD2C))
#define SOC_M3_SCS_DFSR_ADDR(base) ((base) + (0xD30))
#define SOC_M3_SCS_MMFAR_ADDR(base) ((base) + (0xD34))
#define SOC_M3_SCS_BFAR_ADDR(base) ((base) + (0xD38))
#define SOC_M3_SCS_AFSR_ADDR(base) ((base) + (0xD3C))
#define SOC_M3_SCS_ID_PFR0_ADDR(base) ((base) + (0xD40))
#define SOC_M3_SCS_ID_PFR1_ADDR(base) ((base) + (0xD44))
#define SOC_M3_SCS_ID_DFR0_ADDR(base) ((base) + (0xD48))
#define SOC_M3_SCS_ID_AFR0_ADDR(base) ((base) + (0xD4C))
#define SOC_M3_SCS_ID_MMFR0_ADDR(base) ((base) + (0xD50))
#define SOC_M3_SCS_ID_MMFR1_ADDR(base) ((base) + (0xD54))
#define SOC_M3_SCS_ID_MMFR2_ADDR(base) ((base) + (0xD58))
#define SOC_M3_SCS_ID_MMFR3_ADDR(base) ((base) + (0xD5C))
#define SOC_M3_SCS_ID_ISAR0_ADDR(base) ((base) + (0xD60))
#define SOC_M3_SCS_ID_ISAR1_ADDR(base) ((base) + (0xD64))
#define SOC_M3_SCS_ID_ISAR2_ADDR(base) ((base) + (0xD68))
#define SOC_M3_SCS_ID_ISAR3_ADDR(base) ((base) + (0xD6C))
#define SOC_M3_SCS_ID_ISAR4_ADDR(base) ((base) + (0xD70))
#define SOC_M3_SCS_CPACR_ADDR(base) ((base) + (0xD88))
#define SOC_M3_SCS_STIR_ADDR(base) ((base) + (0xF00))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intlinesnum : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_M3_SCS_ICTR_UNION;
#endif
#define SOC_M3_SCS_ICTR_intlinesnum_START (0)
#define SOC_M3_SCS_ICTR_intlinesnum_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dismcycint : 1;
        unsigned int disdefwbuf : 1;
        unsigned int disfold : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_M3_SCS_ACTLR_UNION;
#endif
#define SOC_M3_SCS_ACTLR_dismcycint_START (0)
#define SOC_M3_SCS_ACTLR_dismcycint_END (0)
#define SOC_M3_SCS_ACTLR_disdefwbuf_START (1)
#define SOC_M3_SCS_ACTLR_disdefwbuf_END (1)
#define SOC_M3_SCS_ACTLR_disfold_START (2)
#define SOC_M3_SCS_ACTLR_disfold_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 1;
        unsigned int tickint : 1;
        unsigned int clksource : 1;
        unsigned int reserved_0: 13;
        unsigned int countflag : 1;
        unsigned int reserved_1: 15;
    } reg;
} SOC_M3_SCS_STCSR_UNION;
#endif
#define SOC_M3_SCS_STCSR_enable_START (0)
#define SOC_M3_SCS_STCSR_enable_END (0)
#define SOC_M3_SCS_STCSR_tickint_START (1)
#define SOC_M3_SCS_STCSR_tickint_END (1)
#define SOC_M3_SCS_STCSR_clksource_START (2)
#define SOC_M3_SCS_STCSR_clksource_END (2)
#define SOC_M3_SCS_STCSR_countflag_START (16)
#define SOC_M3_SCS_STCSR_countflag_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reload : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_M3_SCS_STRVR_UNION;
#endif
#define SOC_M3_SCS_STRVR_reload_START (0)
#define SOC_M3_SCS_STRVR_reload_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int current : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_M3_SCS_STCVR_UNION;
#endif
#define SOC_M3_SCS_STCVR_current_START (0)
#define SOC_M3_SCS_STCVR_current_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tenms : 24;
        unsigned int reserved : 6;
        unsigned int skew : 1;
        unsigned int noref : 1;
    } reg;
} SOC_M3_SCS_STCR_UNION;
#endif
#define SOC_M3_SCS_STCR_tenms_START (0)
#define SOC_M3_SCS_STCR_tenms_END (23)
#define SOC_M3_SCS_STCR_skew_START (30)
#define SOC_M3_SCS_STCR_skew_END (30)
#define SOC_M3_SCS_STCR_noref_START (31)
#define SOC_M3_SCS_STCR_noref_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int setena : 32;
    } reg;
} SOC_M3_SCS_NVIC_ISERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISERn_setena_START (0)
#define SOC_M3_SCS_NVIC_ISERn_setena_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clrena : 32;
    } reg;
} SOC_M3_SCS_NVIC_ICERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICERn_clrena_START (0)
#define SOC_M3_SCS_NVIC_ICERn_clrena_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int setpend : 32;
    } reg;
} SOC_M3_SCS_NVIC_ISPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISPRn_setpend_START (0)
#define SOC_M3_SCS_NVIC_ISPRn_setpend_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clrpend : 32;
    } reg;
} SOC_M3_SCS_NVIC_ICPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_START (0)
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int active : 32;
    } reg;
} SOC_M3_SCS_NVIC_IABRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_IABRn_active_START (0)
#define SOC_M3_SCS_NVIC_IABRn_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pri_n0 : 8;
        unsigned int pri_n1 : 8;
        unsigned int pri_n2 : 8;
        unsigned int pri_n3 : 8;
    } reg;
} SOC_M3_SCS_NVIC_IPRm_UNION;
#endif
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_START (0)
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_END (7)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_START (8)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_END (15)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_START (16)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_END (23)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_START (24)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int revision : 4;
        unsigned int partno : 12;
        unsigned int constant : 4;
        unsigned int variant : 4;
        unsigned int implementer : 8;
    } reg;
} SOC_M3_SCS_CPUID_UNION;
#endif
#define SOC_M3_SCS_CPUID_revision_START (0)
#define SOC_M3_SCS_CPUID_revision_END (3)
#define SOC_M3_SCS_CPUID_partno_START (4)
#define SOC_M3_SCS_CPUID_partno_END (15)
#define SOC_M3_SCS_CPUID_constant_START (16)
#define SOC_M3_SCS_CPUID_constant_END (19)
#define SOC_M3_SCS_CPUID_variant_START (20)
#define SOC_M3_SCS_CPUID_variant_END (23)
#define SOC_M3_SCS_CPUID_implementer_START (24)
#define SOC_M3_SCS_CPUID_implementer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vectactive : 9;
        unsigned int reserved_0 : 2;
        unsigned int rettobase : 1;
        unsigned int vectpending : 10;
        unsigned int isrpending : 1;
        unsigned int isrpreempt : 1;
        unsigned int reserved_1 : 1;
        unsigned int pendstclr : 1;
        unsigned int pendstset : 1;
        unsigned int pendsvclr : 1;
        unsigned int pendsvset : 1;
        unsigned int reserved_2 : 2;
        unsigned int nmipendset : 1;
    } reg;
} SOC_M3_SCS_ICSR_UNION;
#endif
#define SOC_M3_SCS_ICSR_vectactive_START (0)
#define SOC_M3_SCS_ICSR_vectactive_END (8)
#define SOC_M3_SCS_ICSR_rettobase_START (11)
#define SOC_M3_SCS_ICSR_rettobase_END (11)
#define SOC_M3_SCS_ICSR_vectpending_START (12)
#define SOC_M3_SCS_ICSR_vectpending_END (21)
#define SOC_M3_SCS_ICSR_isrpending_START (22)
#define SOC_M3_SCS_ICSR_isrpending_END (22)
#define SOC_M3_SCS_ICSR_isrpreempt_START (23)
#define SOC_M3_SCS_ICSR_isrpreempt_END (23)
#define SOC_M3_SCS_ICSR_pendstclr_START (25)
#define SOC_M3_SCS_ICSR_pendstclr_END (25)
#define SOC_M3_SCS_ICSR_pendstset_START (26)
#define SOC_M3_SCS_ICSR_pendstset_END (26)
#define SOC_M3_SCS_ICSR_pendsvclr_START (27)
#define SOC_M3_SCS_ICSR_pendsvclr_END (27)
#define SOC_M3_SCS_ICSR_pendsvset_START (28)
#define SOC_M3_SCS_ICSR_pendsvset_END (28)
#define SOC_M3_SCS_ICSR_nmipendset_START (31)
#define SOC_M3_SCS_ICSR_nmipendset_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 7;
        unsigned int tbloff : 22;
        unsigned int tblabse : 1;
        unsigned int reserved_1: 2;
    } reg;
} SOC_M3_SCS_VTOR_UNION;
#endif
#define SOC_M3_SCS_VTOR_tbloff_START (7)
#define SOC_M3_SCS_VTOR_tbloff_END (28)
#define SOC_M3_SCS_VTOR_tblabse_START (29)
#define SOC_M3_SCS_VTOR_tblabse_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vectreset : 1;
        unsigned int vectclractive : 1;
        unsigned int sysresetreq : 1;
        unsigned int reserved_0 : 5;
        unsigned int prigroup : 3;
        unsigned int reserved_1 : 4;
        unsigned int endianess : 1;
        unsigned int vectkey_vectkeystat : 16;
    } reg;
} SOC_M3_SCS_AIRCR_UNION;
#endif
#define SOC_M3_SCS_AIRCR_vectreset_START (0)
#define SOC_M3_SCS_AIRCR_vectreset_END (0)
#define SOC_M3_SCS_AIRCR_vectclractive_START (1)
#define SOC_M3_SCS_AIRCR_vectclractive_END (1)
#define SOC_M3_SCS_AIRCR_sysresetreq_START (2)
#define SOC_M3_SCS_AIRCR_sysresetreq_END (2)
#define SOC_M3_SCS_AIRCR_prigroup_START (8)
#define SOC_M3_SCS_AIRCR_prigroup_END (10)
#define SOC_M3_SCS_AIRCR_endianess_START (15)
#define SOC_M3_SCS_AIRCR_endianess_END (15)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_START (16)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int sleeponexit : 1;
        unsigned int sleepdeep : 1;
        unsigned int reserved_1 : 1;
        unsigned int sevonpend : 1;
        unsigned int reserved_2 : 27;
    } reg;
} SOC_M3_SCS_SCR_UNION;
#endif
#define SOC_M3_SCS_SCR_sleeponexit_START (1)
#define SOC_M3_SCS_SCR_sleeponexit_END (1)
#define SOC_M3_SCS_SCR_sleepdeep_START (2)
#define SOC_M3_SCS_SCR_sleepdeep_END (2)
#define SOC_M3_SCS_SCR_sevonpend_START (4)
#define SOC_M3_SCS_SCR_sevonpend_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nonebasethrdena : 1;
        unsigned int usersetmpend : 1;
        unsigned int reserved_0 : 1;
        unsigned int unalign_trp : 1;
        unsigned int div_0_trp : 1;
        unsigned int reserved_1 : 3;
        unsigned int bfhfnmign : 1;
        unsigned int stkalign : 1;
        unsigned int reserved_2 : 22;
    } reg;
} SOC_M3_SCS_CCR_UNION;
#endif
#define SOC_M3_SCS_CCR_nonebasethrdena_START (0)
#define SOC_M3_SCS_CCR_nonebasethrdena_END (0)
#define SOC_M3_SCS_CCR_usersetmpend_START (1)
#define SOC_M3_SCS_CCR_usersetmpend_END (1)
#define SOC_M3_SCS_CCR_unalign_trp_START (3)
#define SOC_M3_SCS_CCR_unalign_trp_END (3)
#define SOC_M3_SCS_CCR_div_0_trp_START (4)
#define SOC_M3_SCS_CCR_div_0_trp_END (4)
#define SOC_M3_SCS_CCR_bfhfnmign_START (8)
#define SOC_M3_SCS_CCR_bfhfnmign_END (8)
#define SOC_M3_SCS_CCR_stkalign_START (9)
#define SOC_M3_SCS_CCR_stkalign_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pri_4 : 8;
        unsigned int pri_5 : 8;
        unsigned int pri_6 : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_M3_SCS_SHPR1_UNION;
#endif
#define SOC_M3_SCS_SHPR1_pri_4_START (0)
#define SOC_M3_SCS_SHPR1_pri_4_END (7)
#define SOC_M3_SCS_SHPR1_pri_5_START (8)
#define SOC_M3_SCS_SHPR1_pri_5_END (15)
#define SOC_M3_SCS_SHPR1_pri_6_START (16)
#define SOC_M3_SCS_SHPR1_pri_6_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int pri_11 : 8;
    } reg;
} SOC_M3_SCS_SHPR2_UNION;
#endif
#define SOC_M3_SCS_SHPR2_pri_11_START (24)
#define SOC_M3_SCS_SHPR2_pri_11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pri_12 : 8;
        unsigned int reserved : 8;
        unsigned int pri_14 : 8;
        unsigned int pri_15 : 8;
    } reg;
} SOC_M3_SCS_SHPR3_UNION;
#endif
#define SOC_M3_SCS_SHPR3_pri_12_START (0)
#define SOC_M3_SCS_SHPR3_pri_12_END (7)
#define SOC_M3_SCS_SHPR3_pri_14_START (16)
#define SOC_M3_SCS_SHPR3_pri_14_END (23)
#define SOC_M3_SCS_SHPR3_pri_15_START (24)
#define SOC_M3_SCS_SHPR3_pri_15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int memfaultact : 1;
        unsigned int busfaultact : 1;
        unsigned int reserved_0 : 1;
        unsigned int usgfaultact : 1;
        unsigned int reserved_1 : 3;
        unsigned int svcallact : 1;
        unsigned int monitoract : 1;
        unsigned int reserved_2 : 1;
        unsigned int pendsvact : 1;
        unsigned int systickact : 1;
        unsigned int usgfaultpended : 1;
        unsigned int memfaultpended : 1;
        unsigned int busfaultpended : 1;
        unsigned int svcallpended : 1;
        unsigned int memfaultena : 1;
        unsigned int busfaultena : 1;
        unsigned int usgfaultena : 1;
        unsigned int reserved_3 : 13;
    } reg;
} SOC_M3_SCS_SHCSR_UNION;
#endif
#define SOC_M3_SCS_SHCSR_memfaultact_START (0)
#define SOC_M3_SCS_SHCSR_memfaultact_END (0)
#define SOC_M3_SCS_SHCSR_busfaultact_START (1)
#define SOC_M3_SCS_SHCSR_busfaultact_END (1)
#define SOC_M3_SCS_SHCSR_usgfaultact_START (3)
#define SOC_M3_SCS_SHCSR_usgfaultact_END (3)
#define SOC_M3_SCS_SHCSR_svcallact_START (7)
#define SOC_M3_SCS_SHCSR_svcallact_END (7)
#define SOC_M3_SCS_SHCSR_monitoract_START (8)
#define SOC_M3_SCS_SHCSR_monitoract_END (8)
#define SOC_M3_SCS_SHCSR_pendsvact_START (10)
#define SOC_M3_SCS_SHCSR_pendsvact_END (10)
#define SOC_M3_SCS_SHCSR_systickact_START (11)
#define SOC_M3_SCS_SHCSR_systickact_END (11)
#define SOC_M3_SCS_SHCSR_usgfaultpended_START (12)
#define SOC_M3_SCS_SHCSR_usgfaultpended_END (12)
#define SOC_M3_SCS_SHCSR_memfaultpended_START (13)
#define SOC_M3_SCS_SHCSR_memfaultpended_END (13)
#define SOC_M3_SCS_SHCSR_busfaultpended_START (14)
#define SOC_M3_SCS_SHCSR_busfaultpended_END (14)
#define SOC_M3_SCS_SHCSR_svcallpended_START (15)
#define SOC_M3_SCS_SHCSR_svcallpended_END (15)
#define SOC_M3_SCS_SHCSR_memfaultena_START (16)
#define SOC_M3_SCS_SHCSR_memfaultena_END (16)
#define SOC_M3_SCS_SHCSR_busfaultena_START (17)
#define SOC_M3_SCS_SHCSR_busfaultena_END (17)
#define SOC_M3_SCS_SHCSR_usgfaultena_START (18)
#define SOC_M3_SCS_SHCSR_usgfaultena_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int iaccviol : 1;
        unsigned int daccviol : 1;
        unsigned int reserved_0 : 1;
        unsigned int munstkerr : 1;
        unsigned int mstkerr : 1;
        unsigned int mlsperr : 1;
        unsigned int reserved_1 : 1;
        unsigned int mmarvalid : 1;
        unsigned int ibuserr : 1;
        unsigned int preciserr : 1;
        unsigned int impreciserr : 1;
        unsigned int unstkerr : 1;
        unsigned int stkerr : 1;
        unsigned int lsperr : 1;
        unsigned int reserved_2 : 1;
        unsigned int bfarvalid : 1;
        unsigned int undefinstr : 1;
        unsigned int invstate : 1;
        unsigned int invpc : 1;
        unsigned int nocp : 1;
        unsigned int reserved_3 : 4;
        unsigned int unaligned : 1;
        unsigned int divbyzero : 1;
        unsigned int reserved_4 : 6;
    } reg;
} SOC_M3_SCS_CFSR_UNION;
#endif
#define SOC_M3_SCS_CFSR_iaccviol_START (0)
#define SOC_M3_SCS_CFSR_iaccviol_END (0)
#define SOC_M3_SCS_CFSR_daccviol_START (1)
#define SOC_M3_SCS_CFSR_daccviol_END (1)
#define SOC_M3_SCS_CFSR_munstkerr_START (3)
#define SOC_M3_SCS_CFSR_munstkerr_END (3)
#define SOC_M3_SCS_CFSR_mstkerr_START (4)
#define SOC_M3_SCS_CFSR_mstkerr_END (4)
#define SOC_M3_SCS_CFSR_mlsperr_START (5)
#define SOC_M3_SCS_CFSR_mlsperr_END (5)
#define SOC_M3_SCS_CFSR_mmarvalid_START (7)
#define SOC_M3_SCS_CFSR_mmarvalid_END (7)
#define SOC_M3_SCS_CFSR_ibuserr_START (8)
#define SOC_M3_SCS_CFSR_ibuserr_END (8)
#define SOC_M3_SCS_CFSR_preciserr_START (9)
#define SOC_M3_SCS_CFSR_preciserr_END (9)
#define SOC_M3_SCS_CFSR_impreciserr_START (10)
#define SOC_M3_SCS_CFSR_impreciserr_END (10)
#define SOC_M3_SCS_CFSR_unstkerr_START (11)
#define SOC_M3_SCS_CFSR_unstkerr_END (11)
#define SOC_M3_SCS_CFSR_stkerr_START (12)
#define SOC_M3_SCS_CFSR_stkerr_END (12)
#define SOC_M3_SCS_CFSR_lsperr_START (13)
#define SOC_M3_SCS_CFSR_lsperr_END (13)
#define SOC_M3_SCS_CFSR_bfarvalid_START (15)
#define SOC_M3_SCS_CFSR_bfarvalid_END (15)
#define SOC_M3_SCS_CFSR_undefinstr_START (16)
#define SOC_M3_SCS_CFSR_undefinstr_END (16)
#define SOC_M3_SCS_CFSR_invstate_START (17)
#define SOC_M3_SCS_CFSR_invstate_END (17)
#define SOC_M3_SCS_CFSR_invpc_START (18)
#define SOC_M3_SCS_CFSR_invpc_END (18)
#define SOC_M3_SCS_CFSR_nocp_START (19)
#define SOC_M3_SCS_CFSR_nocp_END (19)
#define SOC_M3_SCS_CFSR_unaligned_START (24)
#define SOC_M3_SCS_CFSR_unaligned_END (24)
#define SOC_M3_SCS_CFSR_divbyzero_START (25)
#define SOC_M3_SCS_CFSR_divbyzero_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int vecttbl : 1;
        unsigned int reserved_1: 28;
        unsigned int forced : 1;
        unsigned int debugevt : 1;
    } reg;
} SOC_M3_SCS_HFSR_UNION;
#endif
#define SOC_M3_SCS_HFSR_vecttbl_START (1)
#define SOC_M3_SCS_HFSR_vecttbl_END (1)
#define SOC_M3_SCS_HFSR_forced_START (30)
#define SOC_M3_SCS_HFSR_forced_END (30)
#define SOC_M3_SCS_HFSR_debugevt_START (31)
#define SOC_M3_SCS_HFSR_debugevt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int halted : 1;
        unsigned int bkpt : 1;
        unsigned int dwttrap : 1;
        unsigned int vcatch : 1;
        unsigned int external : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_M3_SCS_DFSR_UNION;
#endif
#define SOC_M3_SCS_DFSR_halted_START (0)
#define SOC_M3_SCS_DFSR_halted_END (0)
#define SOC_M3_SCS_DFSR_bkpt_START (1)
#define SOC_M3_SCS_DFSR_bkpt_END (1)
#define SOC_M3_SCS_DFSR_dwttrap_START (2)
#define SOC_M3_SCS_DFSR_dwttrap_END (2)
#define SOC_M3_SCS_DFSR_vcatch_START (3)
#define SOC_M3_SCS_DFSR_vcatch_END (3)
#define SOC_M3_SCS_DFSR_external_START (4)
#define SOC_M3_SCS_DFSR_external_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_mem : 32;
    } reg;
} SOC_M3_SCS_MMFAR_UNION;
#endif
#define SOC_M3_SCS_MMFAR_address_mem_START (0)
#define SOC_M3_SCS_MMFAR_address_mem_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_bus : 32;
    } reg;
} SOC_M3_SCS_BFAR_UNION;
#endif
#define SOC_M3_SCS_BFAR_address_bus_START (0)
#define SOC_M3_SCS_BFAR_address_bus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auxfault : 32;
    } reg;
} SOC_M3_SCS_AFSR_UNION;
#endif
#define SOC_M3_SCS_AFSR_auxfault_START (0)
#define SOC_M3_SCS_AFSR_auxfault_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_PFR0 : 32;
    } reg;
} SOC_M3_SCS_ID_PFR0_UNION;
#endif
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_START (0)
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_PFR1 : 32;
    } reg;
} SOC_M3_SCS_ID_PFR1_UNION;
#endif
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_START (0)
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_DFR0 : 32;
    } reg;
} SOC_M3_SCS_ID_DFR0_UNION;
#endif
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_START (0)
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_AFR0 : 32;
    } reg;
} SOC_M3_SCS_ID_AFR0_UNION;
#endif
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_START (0)
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_MMFR0 : 32;
    } reg;
} SOC_M3_SCS_ID_MMFR0_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_START (0)
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_MMFR1 : 32;
    } reg;
} SOC_M3_SCS_ID_MMFR1_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_START (0)
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_MMFR2 : 32;
    } reg;
} SOC_M3_SCS_ID_MMFR2_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_START (0)
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_MMFR3 : 32;
    } reg;
} SOC_M3_SCS_ID_MMFR3_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_START (0)
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_ISAR0 : 32;
    } reg;
} SOC_M3_SCS_ID_ISAR0_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_START (0)
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_ISAR1 : 32;
    } reg;
} SOC_M3_SCS_ID_ISAR1_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_START (0)
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_ISAR2 : 32;
    } reg;
} SOC_M3_SCS_ID_ISAR2_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_START (0)
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_ISAR3 : 32;
    } reg;
} SOC_M3_SCS_ID_ISAR3_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_START (0)
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ID_ISAR4 : 32;
    } reg;
} SOC_M3_SCS_ID_ISAR4_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_START (0)
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CPACR : 32;
    } reg;
} SOC_M3_SCS_CPACR_UNION;
#endif
#define SOC_M3_SCS_CPACR_CPACR_START (0)
#define SOC_M3_SCS_CPACR_CPACR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intid : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_M3_SCS_STIR_UNION;
#endif
#define SOC_M3_SCS_STIR_intid_START (0)
#define SOC_M3_SCS_STIR_intid_END (8)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
