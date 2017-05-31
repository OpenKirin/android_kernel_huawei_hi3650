#ifndef __SOC_ISP_TIMER_INTERFACE_H__
#define __SOC_ISP_TIMER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_TIMER_TIMER0_LOAD_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_TIMER_TIMER1_LOAD_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_TIMER_TIMER0_VALUE_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_TIMER_TIMER1_VALUE_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_TIMER_TIMER0_CONTROL_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_TIMER_TIMER1_CONTROL_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_TIMER_TIMER0_INTCLR_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_TIMER_TIMER1_INTCLR_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_TIMER_TIMER0_RIS_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_TIMER_TIMER1_RIS_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_TIMER_TIMER0_MIS_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_TIMER_TIMER1_MIS_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_TIMER_TIMER0_BGLOAD_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_TIMER_TIMER1_BGLOAD_ADDR(base) ((base) + (0x0038))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxload : 32;
    } reg;
} SOC_ISP_TIMER_TIMER0_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_START (0)
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxload : 32;
    } reg;
} SOC_ISP_TIMER_TIMER1_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_START (0)
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxvalue : 32;
    } reg;
} SOC_ISP_TIMER_TIMER0_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_START (0)
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxvalue : 32;
    } reg;
} SOC_ISP_TIMER_TIMER1_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_START (0)
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oneshot : 1;
        unsigned int timersize : 1;
        unsigned int timerpre : 2;
        unsigned int reserved_0 : 1;
        unsigned int internable : 1;
        unsigned int timermode : 1;
        unsigned int timeren : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_ISP_TIMER_TIMER0_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_START (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_END (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_START (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_END (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_START (2)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_END (3)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_START (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_END (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_START (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_END (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_START (7)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oneshot : 1;
        unsigned int timersize : 1;
        unsigned int timerpre : 2;
        unsigned int reserved_0 : 1;
        unsigned int internable : 1;
        unsigned int timermode : 1;
        unsigned int timeren : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_ISP_TIMER_TIMER1_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_START (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_END (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_START (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_END (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_START (2)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_END (3)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_START (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_END (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_START (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_END (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_START (7)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxintclr : 32;
    } reg;
} SOC_ISP_TIMER_TIMER0_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_START (0)
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxintclr : 32;
    } reg;
} SOC_ISP_TIMER_TIMER1_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_START (0)
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxris : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TIMER_TIMER0_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_START (0)
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxris : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TIMER_TIMER1_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_START (0)
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxmis : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TIMER_TIMER0_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_START (0)
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxmis : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_TIMER_TIMER1_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_START (0)
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxbgload : 32;
    } reg;
} SOC_ISP_TIMER_TIMER0_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_START (0)
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timerxbgload : 32;
    } reg;
} SOC_ISP_TIMER_TIMER1_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_START (0)
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
