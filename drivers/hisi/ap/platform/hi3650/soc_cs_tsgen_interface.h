#ifndef __SOC_CS_TSGEN_INTERFACE_H__
#define __SOC_CS_TSGEN_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_TSGEN_TS_CNTCR_ADDR(base) ((base) + (0x0000))
#define SOC_CS_TSGEN_TS_CNTSR_ADDR(base) ((base) + (0x0004))
#define SOC_CS_TSGEN_TS_CNTCVLW_ADDR(base) ((base) + (0x0008))
#define SOC_CS_TSGEN_TS_CNTCVUP_ADDR(base) ((base) + (0x000C))
#define SOC_CS_TSGEN_TS_CNTFID0_ADDR(base) ((base) + (0x0020))
#define SOC_CS_TSGEN_TSCNTCVLW_RO_ADDR(base) ((base) + (0x1000))
#define SOC_CS_TSGEN_TSCNTCVUP_RO_ADDR(base) ((base) + (0x1004))
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
} SOC_CS_TSGEN_TS_CNTCR_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCR_en_START (0)
#define SOC_CS_TSGEN_TS_CNTCR_en_END (0)
#define SOC_CS_TSGEN_TS_CNTCR_hdbg_START (1)
#define SOC_CS_TSGEN_TS_CNTCR_hdbg_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int dbgh : 1;
        unsigned int reserved_1: 30;
    } reg;
} SOC_CS_TSGEN_TS_CNTSR_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTSR_dbgh_START (1)
#define SOC_CS_TSGEN_TS_CNTSR_dbgh_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvlw : 32;
    } reg;
} SOC_CS_TSGEN_TS_CNTCVLW_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCVLW_cntcvlw_START (0)
#define SOC_CS_TSGEN_TS_CNTCVLW_cntcvlw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvup : 32;
    } reg;
} SOC_CS_TSGEN_TS_CNTCVUP_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCVUP_cntcvup_START (0)
#define SOC_CS_TSGEN_TS_CNTCVUP_cntcvup_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int freq : 32;
    } reg;
} SOC_CS_TSGEN_TS_CNTFID0_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTFID0_freq_START (0)
#define SOC_CS_TSGEN_TS_CNTFID0_freq_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvlw_ro : 32;
    } reg;
} SOC_CS_TSGEN_TSCNTCVLW_RO_UNION;
#endif
#define SOC_CS_TSGEN_TSCNTCVLW_RO_cntcvlw_ro_START (0)
#define SOC_CS_TSGEN_TSCNTCVLW_RO_cntcvlw_ro_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cntcvup_ro : 32;
    } reg;
} SOC_CS_TSGEN_TSCNTCVUP_RO_UNION;
#endif
#define SOC_CS_TSGEN_TSCNTCVUP_RO_cntcvup_ro_START (0)
#define SOC_CS_TSGEN_TSCNTCVUP_RO_cntcvup_ro_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
