#ifndef __SOC_CS_TOP_FUNNEL_INTERFACE_H__
#define __SOC_CS_TOP_FUNNEL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_ADDR(base) ((base) + (0x000))
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_ADDR(base) ((base) + (0x004))
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ADDR(base) ((base) + (0xFB4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 7;
        unsigned int reserved_0: 1;
        unsigned int holdtime : 4;
        unsigned int reserved_1: 20;
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_enable_START (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_enable_END (6)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_holdtime_START (8)
#define SOC_CS_TOP_FUNNEL_FUNNEL_CTRL_REG_holdtime_END (11)
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
        unsigned int priport5 : 3;
        unsigned int priport6 : 3;
        unsigned int reserved : 11;
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport0_START (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport0_END (2)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport1_START (3)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport1_END (5)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport2_START (6)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport2_END (8)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport3_START (9)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport3_END (11)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport4_START (12)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport4_END (14)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport5_START (15)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport5_END (17)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport6_START (18)
#define SOC_CS_TOP_FUNNEL_FUNNEL_PRIORITY_CTRL_REG_priport6_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_TOP_FUNNEL_FUNNEL_LAR_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_key_START (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LAR_key_END (31)
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
} SOC_CS_TOP_FUNNEL_FUNNEL_LSR_UNION;
#endif
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_sli_START (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_sli_END (0)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_slk_START (1)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_slk_END (1)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ntt_START (2)
#define SOC_CS_TOP_FUNNEL_FUNNEL_LSR_ntt_END (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
