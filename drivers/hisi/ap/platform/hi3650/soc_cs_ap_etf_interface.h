#ifndef __SOC_CS_AP_ETF_INTERFACE_H__
#define __SOC_CS_AP_ETF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_AP_ETF_ETF_RSZ_ADDR(base) ((base) + (0x004))
#define SOC_CS_AP_ETF_ETF_STS_ADDR(base) ((base) + (0x00C))
#define SOC_CS_AP_ETF_ETF_RRD_ADDR(base) ((base) + (0x010))
#define SOC_CS_AP_ETF_ETF_RRP_ADDR(base) ((base) + (0x014))
#define SOC_CS_AP_ETF_ETF_RWP_ADDR(base) ((base) + (0x018))
#define SOC_CS_AP_ETF_ETF_TRG_ADDR(base) ((base) + (0x01C))
#define SOC_CS_AP_ETF_ETF_CTL_ADDR(base) ((base) + (0x020))
#define SOC_CS_AP_ETF_ETF_RWD_ADDR(base) ((base) + (0x024))
#define SOC_CS_AP_ETF_ETF_MODE_ADDR(base) ((base) + (0x028))
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_ADDR(base) ((base) + (0x02C))
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_ADDR(base) ((base) + (0x030))
#define SOC_CS_AP_ETF_ETF_BUFWM_ADDR(base) ((base) + (0x034))
#define SOC_CS_AP_ETF_ETF_FFSR_ADDR(base) ((base) + (0x300))
#define SOC_CS_AP_ETF_ETF_FFCR_ADDR(base) ((base) + (0x304))
#define SOC_CS_AP_ETF_ETF_FSCR_ADDR(base) ((base) + (0x308))
#define SOC_CS_AP_ETF_ETF_LAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_AP_ETF_ETF_LSR_ADDR(base) ((base) + (0xFB4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rsz : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_CS_AP_ETF_ETF_RSZ_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RSZ_rsz_START (0)
#define SOC_CS_AP_ETF_ETF_RSZ_rsz_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int full : 1;
        unsigned int triggered : 1;
        unsigned int tmcready : 1;
        unsigned int ftempty : 1;
        unsigned int empty : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CS_AP_ETF_ETF_STS_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_STS_full_START (0)
#define SOC_CS_AP_ETF_ETF_STS_full_END (0)
#define SOC_CS_AP_ETF_ETF_STS_triggered_START (1)
#define SOC_CS_AP_ETF_ETF_STS_triggered_END (1)
#define SOC_CS_AP_ETF_ETF_STS_tmcready_START (2)
#define SOC_CS_AP_ETF_ETF_STS_tmcready_END (2)
#define SOC_CS_AP_ETF_ETF_STS_ftempty_START (3)
#define SOC_CS_AP_ETF_ETF_STS_ftempty_END (3)
#define SOC_CS_AP_ETF_ETF_STS_empty_START (4)
#define SOC_CS_AP_ETF_ETF_STS_empty_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rrd : 32;
    } reg;
} SOC_CS_AP_ETF_ETF_RRD_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RRD_rrd_START (0)
#define SOC_CS_AP_ETF_ETF_RRD_rrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rrp : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CS_AP_ETF_ETF_RRP_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RRP_rrp_START (0)
#define SOC_CS_AP_ETF_ETF_RRP_rrp_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwp : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CS_AP_ETF_ETF_RWP_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RWP_rwp_START (0)
#define SOC_CS_AP_ETF_ETF_RWP_rwp_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trg : 32;
    } reg;
} SOC_CS_AP_ETF_ETF_TRG_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_TRG_trg_START (0)
#define SOC_CS_AP_ETF_ETF_TRG_trg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tracecapten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_AP_ETF_ETF_CTL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_CTL_tracecapten_START (0)
#define SOC_CS_AP_ETF_ETF_CTL_tracecapten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rwd : 32;
    } reg;
} SOC_CS_AP_ETF_ETF_RWD_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RWD_rwd_START (0)
#define SOC_CS_AP_ETF_ETF_RWD_rwd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CS_AP_ETF_ETF_MODE_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_MODE_mode_START (0)
#define SOC_CS_AP_ETF_ETF_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lbuflevel : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_CS_AP_ETF_ETF_LBUFLEVEL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_lbuflevel_START (0)
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_lbuflevel_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cbuflevel : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_CS_AP_ETF_ETF_CBUFLEVEL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_cbuflevel_START (0)
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_cbuflevel_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int protctrlbit0 : 1;
        unsigned int protctrlbit1 : 1;
        unsigned int cachectrlbit0 : 1;
        unsigned int cachectrlbit1 : 1;
        unsigned int cachectrlbit2 : 1;
        unsigned int cachectrlbit3 : 1;
        unsigned int reserved_0 : 1;
        unsigned int scattergathermode : 1;
        unsigned int wrburstlen : 4;
        unsigned int bufwm : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_CS_AP_ETF_ETF_BUFWM_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit0_START (0)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit0_END (0)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit1_START (1)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit1_END (1)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit0_START (2)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit0_END (2)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit1_START (3)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit1_END (3)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit2_START (4)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit2_END (4)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit3_START (5)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit3_END (5)
#define SOC_CS_AP_ETF_ETF_BUFWM_scattergathermode_START (7)
#define SOC_CS_AP_ETF_ETF_BUFWM_scattergathermode_END (7)
#define SOC_CS_AP_ETF_ETF_BUFWM_wrburstlen_START (8)
#define SOC_CS_AP_ETF_ETF_BUFWM_wrburstlen_END (11)
#define SOC_CS_AP_ETF_ETF_BUFWM_bufwm_START (12)
#define SOC_CS_AP_ETF_ETF_BUFWM_bufwm_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flinprog : 1;
        unsigned int ftstopped : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CS_AP_ETF_ETF_FFSR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FFSR_flinprog_START (0)
#define SOC_CS_AP_ETF_ETF_FFSR_flinprog_END (0)
#define SOC_CS_AP_ETF_ETF_FFSR_ftstopped_START (1)
#define SOC_CS_AP_ETF_ETF_FFSR_ftstopped_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enft : 1;
        unsigned int enti : 1;
        unsigned int reserved_0 : 2;
        unsigned int fonflin : 1;
        unsigned int fontrig : 1;
        unsigned int flushman : 1;
        unsigned int reserved_1 : 1;
        unsigned int trigontrigin : 1;
        unsigned int trigontrigevt : 1;
        unsigned int trigonfl : 1;
        unsigned int reserved_2 : 1;
        unsigned int stoponfl : 1;
        unsigned int stopontrigevt : 1;
        unsigned int drainbuffer : 1;
        unsigned int reserved_3 : 17;
    } reg;
} SOC_CS_AP_ETF_ETF_FFCR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FFCR_enft_START (0)
#define SOC_CS_AP_ETF_ETF_FFCR_enft_END (0)
#define SOC_CS_AP_ETF_ETF_FFCR_enti_START (1)
#define SOC_CS_AP_ETF_ETF_FFCR_enti_END (1)
#define SOC_CS_AP_ETF_ETF_FFCR_fonflin_START (4)
#define SOC_CS_AP_ETF_ETF_FFCR_fonflin_END (4)
#define SOC_CS_AP_ETF_ETF_FFCR_fontrig_START (5)
#define SOC_CS_AP_ETF_ETF_FFCR_fontrig_END (5)
#define SOC_CS_AP_ETF_ETF_FFCR_flushman_START (6)
#define SOC_CS_AP_ETF_ETF_FFCR_flushman_END (6)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigin_START (8)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigin_END (8)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigevt_START (9)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigevt_END (9)
#define SOC_CS_AP_ETF_ETF_FFCR_trigonfl_START (10)
#define SOC_CS_AP_ETF_ETF_FFCR_trigonfl_END (10)
#define SOC_CS_AP_ETF_ETF_FFCR_stoponfl_START (12)
#define SOC_CS_AP_ETF_ETF_FFCR_stoponfl_END (12)
#define SOC_CS_AP_ETF_ETF_FFCR_stopontrigevt_START (13)
#define SOC_CS_AP_ETF_ETF_FFCR_stopontrigevt_END (13)
#define SOC_CS_AP_ETF_ETF_FFCR_drainbuffer_START (14)
#define SOC_CS_AP_ETF_ETF_FFCR_drainbuffer_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pscount : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CS_AP_ETF_ETF_FSCR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FSCR_pscount_START (0)
#define SOC_CS_AP_ETF_ETF_FSCR_pscount_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_AP_ETF_ETF_LAR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LAR_key_START (0)
#define SOC_CS_AP_ETF_ETF_LAR_key_END (31)
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
} SOC_CS_AP_ETF_ETF_LSR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LSR_sli_START (0)
#define SOC_CS_AP_ETF_ETF_LSR_sli_END (0)
#define SOC_CS_AP_ETF_ETF_LSR_slk_START (1)
#define SOC_CS_AP_ETF_ETF_LSR_slk_END (1)
#define SOC_CS_AP_ETF_ETF_LSR_ntt_START (2)
#define SOC_CS_AP_ETF_ETF_LSR_ntt_END (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
