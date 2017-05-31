#ifndef __SOC_CS_AP_ETM_INTERFACE_H__
#define __SOC_CS_AP_ETM_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_AP_ETM_ETM_TRCPRGCTLR_ADDR(base) ((base) + (0x004))
#define SOC_CS_AP_ETM_ETM_TRCSTATR_ADDR(base) ((base) + (0x00C))
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_ADDR(base) ((base) + (0x010))
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_ADDR(base) ((base) + (0x018))
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_ADDR(base) ((base) + (0x020))
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_ADDR(base) ((base) + (0x024))
#define SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_ADDR(base) ((base) + (0x02C))
#define SOC_CS_AP_ETM_ETM_TRCTSCTLR_ADDR(base) ((base) + (0x030))
#define SOC_CS_AP_ETM_ETM_TRCSYNCPR_ADDR(base) ((base) + (0x034))
#define SOC_CS_AP_ETM_ETM_TRCCCCTLR_ADDR(base) ((base) + (0x038))
#define SOC_CS_AP_ETM_ETM_TRCBBCTLR_ADDR(base) ((base) + (0x03C))
#define SOC_CS_AP_ETM_ETM_TRCTRACEIDR_ADDR(base) ((base) + (0x040))
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_ADDR(base) ((base) + (0x080))
#define SOC_CS_AP_ETM_ETM_TRCVIIECTLR_ADDR(base) ((base) + (0x084))
#define SOC_CS_AP_ETM_ETM_TRCVISSCTLR_ADDR(base) ((base) + (0x088))
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_ADDR(base) ((base) + (0x100))
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_ADDR(base) ((base) + (0x104))
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_ADDR(base) ((base) + (0x108))
#define SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_ADDR(base) ((base) + (0x118))
#define SOC_CS_AP_ETM_ETM_TRCSEQSTR_ADDR(base) ((base) + (0x11C))
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_ADDR(base) ((base) + (0x120))
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR0_ADDR(base) ((base) + (0x140))
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR1_ADDR(base) ((base) + (0x144))
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_ADDR(base) ((base) + (0x150))
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_ADDR(base) ((base) + (0x154))
#define SOC_CS_AP_ETM_ETM_TRCCNTVR0_ADDR(base) ((base) + (0x160))
#define SOC_CS_AP_ETM_ETM_TRCCNTVR1_ADDR(base) ((base) + (0x164))
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_ADDR(base,n) ((base) + (0x200+(4*(n))))
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_ADDR(base) ((base) + (0x280))
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_ADDR(base) ((base) + (0x2A0))
#define SOC_CS_AP_ETM_ETM_TRCOSLAR_ADDR(base) ((base) + (0x300))
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_ADDR(base) ((base) + (0x304))
#define SOC_CS_AP_ETM_ETM_TRCPDCR_ADDR(base) ((base) + (0x310))
#define SOC_CS_AP_ETM_ETM_TRCPDSR_ADDR(base) ((base) + (0x314))
#define SOC_CS_AP_ETM_ETM_TRCACVRLm_ADDR(base,m) ((base) + (0x400+(8*(m))))
#define SOC_CS_AP_ETM_ETM_TRCACVRHm_ADDR(base,m) ((base) + (0x404+(8*(m))))
#define SOC_CS_AP_ETM_ETM_TRCACATRm_ADDR(base,m) ((base) + (0x480+(8*(m))))
#define SOC_CS_AP_ETM_ETM_TRCCIDCVR0_ADDR(base) ((base) + (0x600))
#define SOC_CS_AP_ETM_ETM_TRCVMIDCVR0_ADDR(base) ((base) + (0x640))
#define SOC_CS_AP_ETM_ETM_TRCCIDCCTLR0_ADDR(base) ((base) + (0x680))
#define SOC_CS_AP_ETM_ETM_TRCLAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_AP_ETM_ETM_TRCLSR_ADDR(base) ((base) + (0xFB4))
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_ADDR(base) ((base) + (0xFB8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCPRGCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCPRGCTLR_en_START (0)
#define SOC_CS_AP_ETM_ETM_TRCPRGCTLR_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int idle : 1;
        unsigned int pmstable : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSTATR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSTATR_idle_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSTATR_idle_END (0)
#define SOC_CS_AP_ETM_ETM_TRCSTATR_pmstable_START (1)
#define SOC_CS_AP_ETM_ETM_TRCSTATR_pmstable_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 2;
        unsigned int bb : 1;
        unsigned int cci : 1;
        unsigned int reserved_2: 1;
        unsigned int cid : 1;
        unsigned int vmid : 1;
        unsigned int reserved_3: 3;
        unsigned int ts : 1;
        unsigned int rs : 1;
        unsigned int reserved_4: 19;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCONFIGR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_bb_START (3)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_bb_END (3)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_cci_START (4)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_cci_END (4)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_cid_START (6)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_cid_END (6)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_vmid_START (7)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_vmid_END (7)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_ts_START (11)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_ts_END (11)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_rs_START (12)
#define SOC_CS_AP_ETM_ETM_TRCCONFIGR_rs_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afready : 1;
        unsigned int idleack : 1;
        unsigned int ovflw : 1;
        unsigned int syncdelay : 1;
        unsigned int tsnodelay : 1;
        unsigned int authnoflush : 1;
        unsigned int reserved_0 : 1;
        unsigned int coreifen : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCAUXCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_afready_START (0)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_afready_END (0)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_idleack_START (1)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_idleack_END (1)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_ovflw_START (2)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_ovflw_END (2)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_syncdelay_START (3)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_syncdelay_END (3)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_tsnodelay_START (4)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_tsnodelay_END (4)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_authnoflush_START (5)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_authnoflush_END (5)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_coreifen_START (7)
#define SOC_CS_AP_ETM_ETM_TRCAUXCTLR_coreifen_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel0 : 4;
        unsigned int reserved_0: 3;
        unsigned int type0 : 1;
        unsigned int sel1 : 4;
        unsigned int reserved_1: 3;
        unsigned int type1 : 1;
        unsigned int sel2 : 4;
        unsigned int reserved_2: 3;
        unsigned int type2 : 1;
        unsigned int sel3 : 4;
        unsigned int reserved_3: 3;
        unsigned int type3 : 1;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel0_START (0)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel0_END (3)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type0_START (7)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type0_END (7)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel1_START (8)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel1_END (11)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type1_START (15)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type1_END (15)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel2_START (16)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel2_END (19)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type2_START (23)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type2_END (23)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel3_START (24)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_sel3_END (27)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type3_START (31)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL0R_type3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 4;
        unsigned int reserved_0 : 7;
        unsigned int atb : 1;
        unsigned int lpoverride : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_en_START (0)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_en_END (3)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_atb_START (11)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_atb_END (11)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_lpoverride_START (12)
#define SOC_CS_AP_ETM_ETM_TRCEVENTCTL1R_lpoverride_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 2;
        unsigned int level : 2;
        unsigned int reserved_1: 4;
        unsigned int istall : 1;
        unsigned int reserved_2: 23;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_level_START (2)
#define SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_level_END (3)
#define SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_istall_START (8)
#define SOC_CS_AP_ETM_ETM_TRCSTALLCTLR_istall_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel : 4;
        unsigned int reserved_0: 3;
        unsigned int type : 1;
        unsigned int reserved_1: 24;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCTSCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCTSCTLR_sel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCTSCTLR_sel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCTSCTLR_type_START (7)
#define SOC_CS_AP_ETM_ETM_TRCTSCTLR_type_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int period : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSYNCPR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSYNCPR_period_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSYNCPR_period_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int threshold : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCCCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCCCTLR_threshold_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCCCTLR_threshold_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int range : 8;
        unsigned int mode : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCBBCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCBBCTLR_range_START (0)
#define SOC_CS_AP_ETM_ETM_TRCBBCTLR_range_END (7)
#define SOC_CS_AP_ETM_ETM_TRCBBCTLR_mode_START (8)
#define SOC_CS_AP_ETM_ETM_TRCBBCTLR_mode_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int traceid : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCTRACEIDR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCTRACEIDR_traceid_START (0)
#define SOC_CS_AP_ETM_ETM_TRCTRACEIDR_traceid_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel : 4;
        unsigned int reserved_0 : 3;
        unsigned int type : 1;
        unsigned int reserved_1 : 1;
        unsigned int ssstatus : 1;
        unsigned int trcreset : 1;
        unsigned int trcerr : 1;
        unsigned int reserved_2 : 4;
        unsigned int exlevel_s : 4;
        unsigned int exlevel_ns : 4;
        unsigned int reserved_3 : 8;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCVICTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_sel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_sel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_type_START (7)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_type_END (7)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_ssstatus_START (9)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_ssstatus_END (9)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_trcreset_START (10)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_trcreset_END (10)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_trcerr_START (11)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_trcerr_END (11)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_exlevel_s_START (16)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_exlevel_s_END (19)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_exlevel_ns_START (20)
#define SOC_CS_AP_ETM_ETM_TRCVICTLR_exlevel_ns_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int include : 4;
        unsigned int reserved_0: 12;
        unsigned int exclude : 4;
        unsigned int reserved_1: 12;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCVIIECTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCVIIECTLR_include_START (0)
#define SOC_CS_AP_ETM_ETM_TRCVIIECTLR_include_END (3)
#define SOC_CS_AP_ETM_ETM_TRCVIIECTLR_exclude_START (16)
#define SOC_CS_AP_ETM_ETM_TRCVIIECTLR_exclude_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start : 8;
        unsigned int reserved_0: 8;
        unsigned int stop : 8;
        unsigned int reserved_1: 8;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCVISSCTLR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCVISSCTLR_start_START (0)
#define SOC_CS_AP_ETM_ETM_TRCVISSCTLR_start_END (7)
#define SOC_CS_AP_ETM_ETM_TRCVISSCTLR_stop_START (16)
#define SOC_CS_AP_ETM_ETM_TRCVISSCTLR_stop_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int f_sel : 4;
        unsigned int reserved_0: 3;
        unsigned int f_type : 1;
        unsigned int b_sel : 4;
        unsigned int reserved_1: 3;
        unsigned int b_type : 1;
        unsigned int reserved_2: 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSEQEVR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_f_sel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_f_sel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_f_type_START (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_f_type_END (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_b_sel_START (8)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_b_sel_END (11)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_b_type_START (15)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR0_b_type_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int f_sel : 4;
        unsigned int reserved_0: 3;
        unsigned int f_type : 1;
        unsigned int b_sel : 4;
        unsigned int reserved_1: 3;
        unsigned int b_type : 1;
        unsigned int reserved_2: 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSEQEVR1_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_f_sel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_f_sel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_f_type_START (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_f_type_END (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_b_sel_START (8)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_b_sel_END (11)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_b_type_START (15)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR1_b_type_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int f_sel : 4;
        unsigned int reserved_0: 3;
        unsigned int f_type : 1;
        unsigned int b_sel : 4;
        unsigned int reserved_1: 3;
        unsigned int b_type : 1;
        unsigned int reserved_2: 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSEQEVR2_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_f_sel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_f_sel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_f_type_START (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_f_type_END (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_b_sel_START (8)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_b_sel_END (11)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_b_type_START (15)
#define SOC_CS_AP_ETM_ETM_TRCSEQEVR2_b_type_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int resetsel : 4;
        unsigned int reserved_0: 3;
        unsigned int resettype : 1;
        unsigned int reserved_1: 24;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_resetsel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_resetsel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_resettype_START (7)
#define SOC_CS_AP_ETM_ETM_TRCSEQRSTEVR_resettype_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int state : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSEQSTR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSEQSTR_state_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSEQSTR_state_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel0 : 5;
        unsigned int reserved_0: 3;
        unsigned int sel1 : 5;
        unsigned int reserved_1: 3;
        unsigned int sel2 : 5;
        unsigned int reserved_2: 3;
        unsigned int sel3 : 5;
        unsigned int reserved_3: 3;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCEXTINSELR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel0_START (0)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel0_END (4)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel1_START (8)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel1_END (12)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel2_START (16)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel2_END (20)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel3_START (24)
#define SOC_CS_AP_ETM_ETM_TRCEXTINSELR_sel3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTRLDVR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR0_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR0_value_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTRLDVR1_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR1_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTRLDVR1_value_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntsel : 4;
        unsigned int reserved_0: 3;
        unsigned int cnttype : 1;
        unsigned int rldsel : 4;
        unsigned int reserved_1: 3;
        unsigned int rldtype : 1;
        unsigned int rldself : 1;
        unsigned int reserved_2: 15;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_cntsel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_cntsel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_cnttype_START (7)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_cnttype_END (7)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldsel_START (8)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldsel_END (11)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldtype_START (15)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldtype_END (15)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldself_START (16)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR0_rldself_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntsel : 4;
        unsigned int reserved_0: 3;
        unsigned int cnttype : 1;
        unsigned int rldsel : 4;
        unsigned int reserved_1: 3;
        unsigned int rldtype : 1;
        unsigned int rldself : 1;
        unsigned int cntchain : 1;
        unsigned int reserved_2: 14;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cntsel_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cntsel_END (3)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cnttype_START (7)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cnttype_END (7)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldsel_START (8)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldsel_END (11)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldtype_START (15)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldtype_END (15)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldself_START (16)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_rldself_END (16)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cntchain_START (17)
#define SOC_CS_AP_ETM_ETM_TRCCNTCTLR1_cntchain_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTVR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTVR0_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTVR0_value_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCNTVR1_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCNTVR1_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCNTVR1_value_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int select : 8;
        unsigned int reserved_0: 8;
        unsigned int group : 3;
        unsigned int reserved_1: 1;
        unsigned int inv : 1;
        unsigned int pairinv : 1;
        unsigned int reserved_2: 10;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCRSCTLRn_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_select_START (0)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_select_END (7)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_group_START (16)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_group_END (18)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_inv_START (20)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_inv_END (20)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_pairinv_START (21)
#define SOC_CS_AP_ETM_ETM_TRCRSCTLRn_pairinv_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sac : 8;
        unsigned int reserved_0: 8;
        unsigned int arc : 4;
        unsigned int reserved_1: 4;
        unsigned int rst : 1;
        unsigned int reserved_2: 7;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSSCCR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_sac_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_sac_END (7)
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_arc_START (16)
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_arc_END (19)
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_rst_START (24)
#define SOC_CS_AP_ETM_ETM_TRCSSCCR0_rst_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inst : 1;
        unsigned int da : 1;
        unsigned int dv : 1;
        unsigned int reserved : 28;
        unsigned int status : 1;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCSSCSR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_inst_START (0)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_inst_END (0)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_da_START (1)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_da_END (1)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_dv_START (2)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_dv_END (2)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_status_START (31)
#define SOC_CS_AP_ETM_ETM_TRCSSCSR0_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oslk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCOSLAR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCOSLAR_oslk_START (0)
#define SOC_CS_AP_ETM_ETM_TRCOSLAR_oslk_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oslm_0 : 1;
        unsigned int oslk : 1;
        unsigned int ntt : 1;
        unsigned int oslm_1 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCOSLSR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslm_0_START (0)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslm_0_END (0)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslk_START (1)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslk_END (1)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_ntt_START (2)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_ntt_END (2)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslm_1_START (3)
#define SOC_CS_AP_ETM_ETM_TRCOSLSR_oslm_1_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 3;
        unsigned int pu : 1;
        unsigned int reserved_1: 28;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCPDCR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCPDCR_pu_START (3)
#define SOC_CS_AP_ETM_ETM_TRCPDCR_pu_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int power : 1;
        unsigned int stickypd : 1;
        unsigned int reserved_0: 3;
        unsigned int oslk : 1;
        unsigned int reserved_1: 26;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCPDSR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCPDSR_power_START (0)
#define SOC_CS_AP_ETM_ETM_TRCPDSR_power_END (0)
#define SOC_CS_AP_ETM_ETM_TRCPDSR_stickypd_START (1)
#define SOC_CS_AP_ETM_ETM_TRCPDSR_stickypd_END (1)
#define SOC_CS_AP_ETM_ETM_TRCPDSR_oslk_START (5)
#define SOC_CS_AP_ETM_ETM_TRCPDSR_oslk_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_low : 32;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCACVRLm_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCACVRLm_address_low_START (0)
#define SOC_CS_AP_ETM_ETM_TRCACVRLm_address_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_hi : 32;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCACVRHm_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCACVRHm_address_hi_START (0)
#define SOC_CS_AP_ETM_ETM_TRCACVRHm_address_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int type : 2;
        unsigned int contexttype : 2;
        unsigned int reserved_0 : 4;
        unsigned int exlevel_s : 4;
        unsigned int exlevel_ns : 4;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCACATRm_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCACATRm_type_START (0)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_type_END (1)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_contexttype_START (2)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_contexttype_END (3)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_exlevel_s_START (8)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_exlevel_s_END (11)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_exlevel_ns_START (12)
#define SOC_CS_AP_ETM_ETM_TRCACATRm_exlevel_ns_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 32;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCIDCVR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCIDCVR0_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCIDCVR0_value_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int value : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCVMIDCVR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCVMIDCVR0_value_START (0)
#define SOC_CS_AP_ETM_ETM_TRCVMIDCVR0_value_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int comp0 : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCCIDCCTLR0_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCCIDCCTLR0_comp0_START (0)
#define SOC_CS_AP_ETM_ETM_TRCCIDCCTLR0_comp0_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_AP_ETM_ETM_TRCLAR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCLAR_key_START (0)
#define SOC_CS_AP_ETM_ETM_TRCLAR_key_END (31)
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
} SOC_CS_AP_ETM_ETM_TRCLSR_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCLSR_sli_START (0)
#define SOC_CS_AP_ETM_ETM_TRCLSR_sli_END (0)
#define SOC_CS_AP_ETM_ETM_TRCLSR_slk_START (1)
#define SOC_CS_AP_ETM_ETM_TRCLSR_slk_END (1)
#define SOC_CS_AP_ETM_ETM_TRCLSR_ntt_START (2)
#define SOC_CS_AP_ETM_ETM_TRCLSR_ntt_END (2)
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
} SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_UNION;
#endif
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_nsid_START (0)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_nsid_END (1)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_nsnid_START (2)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_nsnid_END (3)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_sid_START (4)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_sid_END (5)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_snid_START (6)
#define SOC_CS_AP_ETM_ETM_TRCAUTHSTATUS_snid_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
