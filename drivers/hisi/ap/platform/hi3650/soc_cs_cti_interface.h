#ifndef __SOC_CS_CTI_INTERFACE_H__
#define __SOC_CS_CTI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_CTI_CTI_CONTROL_ADDR(base) ((base) + (0x000))
#define SOC_CS_CTI_CTI_INTACK_ADDR(base) ((base) + (0x010))
#define SOC_CS_CTI_CTI_APPSET_ADDR(base) ((base) + (0x014))
#define SOC_CS_CTI_CTI_APPCLEAR_ADDR(base) ((base) + (0x018))
#define SOC_CS_CTI_CTI_APPPULSE_ADDR(base) ((base) + (0x01C))
#define SOC_CS_CTI_CTI_INEN0_ADDR(base) ((base) + (0x020))
#define SOC_CS_CTI_CTI_INEN1_ADDR(base) ((base) + (0x024))
#define SOC_CS_CTI_CTI_INEN2_ADDR(base) ((base) + (0x028))
#define SOC_CS_CTI_CTI_INEN3_ADDR(base) ((base) + (0x02C))
#define SOC_CS_CTI_CTI_INEN4_ADDR(base) ((base) + (0x030))
#define SOC_CS_CTI_CTI_INEN5_ADDR(base) ((base) + (0x034))
#define SOC_CS_CTI_CTI_INEN6_ADDR(base) ((base) + (0x038))
#define SOC_CS_CTI_CTI_INEN7_ADDR(base) ((base) + (0x03C))
#define SOC_CS_CTI_CTI_OUTEN0_ADDR(base) ((base) + (0x0A0))
#define SOC_CS_CTI_CTI_OUTEN1_ADDR(base) ((base) + (0x0A4))
#define SOC_CS_CTI_CTI_OUTEN2_ADDR(base) ((base) + (0x0A8))
#define SOC_CS_CTI_CTI_OUTEN3_ADDR(base) ((base) + (0x0AC))
#define SOC_CS_CTI_CTI_OUTEN4_ADDR(base) ((base) + (0x0B0))
#define SOC_CS_CTI_CTI_OUTEN5_ADDR(base) ((base) + (0x0B4))
#define SOC_CS_CTI_CTI_OUTEN6_ADDR(base) ((base) + (0x0B8))
#define SOC_CS_CTI_CTI_OUTEN7_ADDR(base) ((base) + (0x0BC))
#define SOC_CS_CTI_CTI_TRIGINSTATUS_ADDR(base) ((base) + (0x130))
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_ADDR(base) ((base) + (0x134))
#define SOC_CS_CTI_CTI_CHINSTATUS_ADDR(base) ((base) + (0x138))
#define SOC_CS_CTI_CTI_CHOUTSTATUS_ADDR(base) ((base) + (0x13C))
#define SOC_CS_CTI_CTI_GATE_ADDR(base) ((base) + (0x140))
#define SOC_CS_CTI_CTI_LAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_CTI_CTI_LSR_ADDR(base) ((base) + (0xFB4))
#define SOC_CS_CTI_CTI_AUTHSTATUS_ADDR(base) ((base) + (0xFB8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int glben : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CS_CTI_CTI_CONTROL_UNION;
#endif
#define SOC_CS_CTI_CTI_CONTROL_glben_START (0)
#define SOC_CS_CTI_CTI_CONTROL_glben_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intack : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_CTI_CTI_INTACK_UNION;
#endif
#define SOC_CS_CTI_CTI_INTACK_intack_START (0)
#define SOC_CS_CTI_CTI_INTACK_intack_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int appset : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_APPSET_UNION;
#endif
#define SOC_CS_CTI_CTI_APPSET_appset_START (0)
#define SOC_CS_CTI_CTI_APPSET_appset_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int appclear : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_APPCLEAR_UNION;
#endif
#define SOC_CS_CTI_CTI_APPCLEAR_appclear_START (0)
#define SOC_CS_CTI_CTI_APPCLEAR_appclear_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int appulse : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_APPPULSE_UNION;
#endif
#define SOC_CS_CTI_CTI_APPPULSE_appulse_START (0)
#define SOC_CS_CTI_CTI_APPPULSE_appulse_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN0_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN0_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN0_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN1_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN1_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN1_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN2_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN2_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN2_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN3_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN3_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN3_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN4_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN4_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN4_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN5_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN5_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN5_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN6_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN6_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN6_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginen : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_INEN7_UNION;
#endif
#define SOC_CS_CTI_CTI_INEN7_triginen_START (0)
#define SOC_CS_CTI_CTI_INEN7_triginen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN0_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN0_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN0_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN1_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN1_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN1_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN2_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN2_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN2_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN3_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN3_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN3_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN4_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN4_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN4_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN5_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN5_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN5_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN6_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN6_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN6_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigouten : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_OUTEN7_UNION;
#endif
#define SOC_CS_CTI_CTI_OUTEN7_trigouten_START (0)
#define SOC_CS_CTI_CTI_OUTEN7_trigouten_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int triginstatus : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_CTI_CTI_TRIGINSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_TRIGINSTATUS_triginstatus_START (0)
#define SOC_CS_CTI_CTI_TRIGINSTATUS_triginstatus_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigoutstatus : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_CTI_CTI_TRIGOUTSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_trigoutstatus_START (0)
#define SOC_CS_CTI_CTI_TRIGOUTSTATUS_trigoutstatus_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int chinstatus : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_CHINSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_CHINSTATUS_chinstatus_START (0)
#define SOC_CS_CTI_CTI_CHINSTATUS_chinstatus_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int choutstatus : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CS_CTI_CTI_CHOUTSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_CHOUTSTATUS_choutstatus_START (0)
#define SOC_CS_CTI_CTI_CHOUTSTATUS_choutstatus_END (3)
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
} SOC_CS_CTI_CTI_GATE_UNION;
#endif
#define SOC_CS_CTI_CTI_GATE_ctigateen0_START (0)
#define SOC_CS_CTI_CTI_GATE_ctigateen0_END (0)
#define SOC_CS_CTI_CTI_GATE_ctigateen1_START (1)
#define SOC_CS_CTI_CTI_GATE_ctigateen1_END (1)
#define SOC_CS_CTI_CTI_GATE_ctigateen2_START (2)
#define SOC_CS_CTI_CTI_GATE_ctigateen2_END (2)
#define SOC_CS_CTI_CTI_GATE_ctigateen3_START (3)
#define SOC_CS_CTI_CTI_GATE_ctigateen3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_CTI_CTI_LAR_UNION;
#endif
#define SOC_CS_CTI_CTI_LAR_key_START (0)
#define SOC_CS_CTI_CTI_LAR_key_END (31)
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
} SOC_CS_CTI_CTI_LSR_UNION;
#endif
#define SOC_CS_CTI_CTI_LSR_sli_START (0)
#define SOC_CS_CTI_CTI_LSR_sli_END (0)
#define SOC_CS_CTI_CTI_LSR_slk_START (1)
#define SOC_CS_CTI_CTI_LSR_slk_END (1)
#define SOC_CS_CTI_CTI_LSR_ntt_START (2)
#define SOC_CS_CTI_CTI_LSR_ntt_END (2)
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
} SOC_CS_CTI_CTI_AUTHSTATUS_UNION;
#endif
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsid_START (0)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsid_END (1)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsnid_START (2)
#define SOC_CS_CTI_CTI_AUTHSTATUS_nsnid_END (3)
#define SOC_CS_CTI_CTI_AUTHSTATUS_sid_START (4)
#define SOC_CS_CTI_CTI_AUTHSTATUS_sid_END (5)
#define SOC_CS_CTI_CTI_AUTHSTATUS_snid_START (6)
#define SOC_CS_CTI_CTI_AUTHSTATUS_snid_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
