#ifndef __SOC_CORESIGHTX_INTERFACE_H__
#define __SOC_CORESIGHTX_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_coresightx_CTRL_REG_ADDR(base) ((base) + (0x1000))
#define SOC_coresightx_PRIORITY_CTRL_REG_ADDR(base) ((base) + (0x1004))
#define SOC_coresightx_LOCKACCESS_ADDR(base) ((base) + (0x1FB0))
#define SOC_coresightx_LOCKSTATUS_ADDR(base) ((base) + (0x1FB4))
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_ADDR(base) ((base) + (0x2104))
#define SOC_coresightx_FSCR_ADDR(base) ((base) + (0x2308))
#define SOC_coresightx_ITCTRL_ADDR(base) ((base) + (0x2F00))
#define SOC_coresightx_RSZ_ADDR(base) ((base) + (0x3004))
#define SOC_coresightx_CTL_ADDR(base) ((base) + (0x3020))
#define SOC_coresightx_DBALO_ADDR(base) ((base) + (0x3118))
#define SOC_coresightx_CTICONTROL_ADDR(base) ((base) + (0x4000))
#define SOC_coresightx_CTIINEN0_ADDR(base) ((base) + (0x4020))
#define SOC_coresightx_CTIGATE_ADDR(base) ((base) + (0x4140))
#define SOC_coresightx_STMHEER_ADDR(base) ((base) + (0x5D00))
#define SOC_coresightx_STMSPER_ADDR(base) ((base) + (0x5E00))
#define SOC_coresightx_STMTCSR_ADDR(base) ((base) + (0x5E80))
#define SOC_coresightx_ETFCTL_ADDR(base) ((base) + (0x6020))
#define SOC_coresightx_ETFMODE_ADDR(base) ((base) + (0x6028))
#define SOC_coresightx_ETFITCTRL_ADDR(base) ((base) + (0x6F00))
#define SOC_coresightx_TSCNTCR_ADDR(base) ((base) + (0x7000))
#define SOC_coresightx_TSCNTCVLW_ADDR(base) ((base) + (0x7008))
#define SOC_coresightx_TSCNTCVUP_ADDR(base) ((base) + (0x700C))
#define SOC_coresightx_TSCNTCVLW_RO_ADDR(base) ((base) + (0x8000))
#define SOC_coresightx_TSCNTCVUP_RO_ADDR(base) ((base) + (0x8004))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 5;
        unsigned int reserved_0: 3;
        unsigned int holdtime : 4;
        unsigned int reserved_1: 20;
    } reg;
} SOC_coresightx_CTRL_REG_UNION;
#endif
#define SOC_coresightx_CTRL_REG_enable_START (0)
#define SOC_coresightx_CTRL_REG_enable_END (4)
#define SOC_coresightx_CTRL_REG_holdtime_START (8)
#define SOC_coresightx_CTRL_REG_holdtime_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int priport0 : 3;
        unsigned int priport1 : 3;
        unsigned int priport2 : 3;
        unsigned int priport3 : 3;
        unsigned int priport4 : 3;
        unsigned int reserved : 17;
    } reg;
} SOC_coresightx_PRIORITY_CTRL_REG_UNION;
#endif
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_START (0)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_END (2)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_START (3)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_END (5)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_START (6)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_END (8)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_START (9)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_END (11)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_START (12)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_coresightx_LOCKACCESS_UNION;
#endif
#define SOC_coresightx_LOCKACCESS_key_START (0)
#define SOC_coresightx_LOCKACCESS_key_END (31)
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
} SOC_coresightx_LOCKSTATUS_UNION;
#endif
#define SOC_coresightx_LOCKSTATUS_sli_START (0)
#define SOC_coresightx_LOCKSTATUS_sli_END (0)
#define SOC_coresightx_LOCKSTATUS_slk_START (1)
#define SOC_coresightx_LOCKSTATUS_slk_END (1)
#define SOC_coresightx_LOCKSTATUS_ntt_START (2)
#define SOC_coresightx_LOCKSTATUS_ntt_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigcount : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION;
#endif
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_START (0)
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cyccount : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_coresightx_FSCR_UNION;
#endif
#define SOC_coresightx_FSCR_cyccount_START (0)
#define SOC_coresightx_FSCR_cyccount_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ime : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_coresightx_ITCTRL_UNION;
#endif
#define SOC_coresightx_ITCTRL_ime_START (0)
#define SOC_coresightx_ITCTRL_ime_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rsz : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_coresightx_RSZ_UNION;
#endif
#define SOC_coresightx_RSZ_rsz_START (0)
#define SOC_coresightx_RSZ_rsz_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tracecapten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_coresightx_CTL_UNION;
#endif
#define SOC_coresightx_CTL_tracecapten_START (0)
#define SOC_coresightx_CTL_tracecapten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bufaddrlo : 32;
    } reg;
} SOC_coresightx_DBALO_UNION;
#endif
#define SOC_coresightx_DBALO_bufaddrlo_START (0)
#define SOC_coresightx_DBALO_bufaddrlo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int glben : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_coresightx_CTICONTROL_UNION;
#endif
#define SOC_coresightx_CTICONTROL_glben_START (0)
#define SOC_coresightx_CTICONTROL_glben_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_coresightx_CTIINEN0_UNION;
#endif
#define SOC_coresightx_CTIINEN0_triginen_START (0)
#define SOC_coresightx_CTIINEN0_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ctigateen0 : 1;
        unsigned int ctigateen1 : 1;
        unsigned int ctigateen2 : 1;
        unsigned int ctigateen3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_coresightx_CTIGATE_UNION;
#endif
#define SOC_coresightx_CTIGATE_ctigateen0_START (0)
#define SOC_coresightx_CTIGATE_ctigateen0_END (0)
#define SOC_coresightx_CTIGATE_ctigateen1_START (1)
#define SOC_coresightx_CTIGATE_ctigateen1_END (1)
#define SOC_coresightx_CTIGATE_ctigateen2_START (2)
#define SOC_coresightx_CTIGATE_ctigateen2_END (2)
#define SOC_coresightx_CTIGATE_ctigateen3_START (3)
#define SOC_coresightx_CTIGATE_ctigateen3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int heen : 32;
    } reg;
} SOC_coresightx_STMHEER_UNION;
#endif
#define SOC_coresightx_STMHEER_heen_START (0)
#define SOC_coresightx_STMHEER_heen_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spe : 32;
    } reg;
} SOC_coresightx_STMSPER_UNION;
#endif
#define SOC_coresightx_STMSPER_spe_START (0)
#define SOC_coresightx_STMSPER_spe_END (31)
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
} SOC_coresightx_STMTCSR_UNION;
#endif
#define SOC_coresightx_STMTCSR_en_START (0)
#define SOC_coresightx_STMTCSR_en_END (0)
#define SOC_coresightx_STMTCSR_tsen_START (1)
#define SOC_coresightx_STMTCSR_tsen_END (1)
#define SOC_coresightx_STMTCSR_syncen_START (2)
#define SOC_coresightx_STMTCSR_syncen_END (2)
#define SOC_coresightx_STMTCSR_compen_START (5)
#define SOC_coresightx_STMTCSR_compen_END (5)
#define SOC_coresightx_STMTCSR_traceid_START (16)
#define SOC_coresightx_STMTCSR_traceid_END (22)
#define SOC_coresightx_STMTCSR_busy_START (23)
#define SOC_coresightx_STMTCSR_busy_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tracecapten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_coresightx_ETFCTL_UNION;
#endif
#define SOC_coresightx_ETFCTL_tracecapten_START (0)
#define SOC_coresightx_ETFCTL_tracecapten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_coresightx_ETFMODE_UNION;
#endif
#define SOC_coresightx_ETFMODE_mode_START (0)
#define SOC_coresightx_ETFMODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int integrationmode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_coresightx_ETFITCTRL_UNION;
#endif
#define SOC_coresightx_ETFITCTRL_integrationmode_START (0)
#define SOC_coresightx_ETFITCTRL_integrationmode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int hdbg : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_coresightx_TSCNTCR_UNION;
#endif
#define SOC_coresightx_TSCNTCR_en_START (0)
#define SOC_coresightx_TSCNTCR_en_END (0)
#define SOC_coresightx_TSCNTCR_hdbg_START (1)
#define SOC_coresightx_TSCNTCR_hdbg_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvlw : 32;
    } reg;
} SOC_coresightx_TSCNTCVLW_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_cntcvlw_START (0)
#define SOC_coresightx_TSCNTCVLW_cntcvlw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvup : 32;
    } reg;
} SOC_coresightx_TSCNTCVUP_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_cntcvup_START (0)
#define SOC_coresightx_TSCNTCVUP_cntcvup_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvlw_ro : 32;
    } reg;
} SOC_coresightx_TSCNTCVLW_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_START (0)
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvup_ro : 32;
    } reg;
} SOC_coresightx_TSCNTCVUP_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_START (0)
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
