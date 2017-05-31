#ifndef __SOC_CS_TPIU_INTERFACE_H__
#define __SOC_CS_TPIU_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_ADDR(base) ((base) + (0x000))
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_ADDR(base) ((base) + (0x004))
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_ADDR(base) ((base) + (0x100))
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_ADDR(base) ((base) + (0x104))
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_ADDR(base) ((base) + (0x108))
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ADDR(base) ((base) + (0x200))
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ADDR(base) ((base) + (0x204))
#define SOC_CS_TPIU_TPIU_TPRCR_ADDR(base) ((base) + (0x208))
#define SOC_CS_TPIU_TPIU_FFSR_ADDR(base) ((base) + (0x300))
#define SOC_CS_TPIU_TPIU_FFCR_ADDR(base) ((base) + (0x304))
#define SOC_CS_TPIU_TPIU_FSCR_ADDR(base) ((base) + (0x308))
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_ADDR(base) ((base) + (0x400))
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_ADDR(base) ((base) + (0x404))
#define SOC_CS_TPIU_TPIU_LAR_ADDR(base) ((base) + (0xFB0))
#define SOC_CS_TPIU_TPIU_LSR_ADDR(base) ((base) + (0xFB4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int port_size_s : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_port_size_s_START (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_port_size_s_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int port_size_c : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_port_size_c_START (0)
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_port_size_c_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mult2 : 1;
        unsigned int mult4 : 1;
        unsigned int mult16 : 1;
        unsigned int mult256 : 1;
        unsigned int mult64k : 1;
        unsigned int reserved_0: 3;
        unsigned int tcount8 : 1;
        unsigned int reserved_1: 7;
        unsigned int triggered : 1;
        unsigned int trgrun : 1;
        unsigned int reserved_2: 14;
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult2_START (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult2_END (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult4_START (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult4_END (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult16_START (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult16_END (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult256_START (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult256_END (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult64k_START (4)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult64k_END (4)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_tcount8_START (8)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_tcount8_END (8)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_triggered_START (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_triggered_END (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_trgrun_START (17)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_trgrun_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trigcount : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_trigcount_START (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_trigcount_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mult2 : 1;
        unsigned int mult4 : 1;
        unsigned int mult16 : 1;
        unsigned int mult256 : 1;
        unsigned int mult64k : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult2_START (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult2_END (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult4_START (1)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult4_END (1)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult16_START (2)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult16_END (2)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult256_START (3)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult256_END (3)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult64k_START (4)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult64k_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int patw1 : 1;
        unsigned int patw0 : 1;
        unsigned int pata5 : 1;
        unsigned int patf0 : 1;
        unsigned int reserved_0: 12;
        unsigned int ptimeen : 1;
        unsigned int pcouten : 1;
        unsigned int reserved_1: 14;
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw1_START (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw1_END (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw0_START (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw0_END (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pata5_START (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pata5_END (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patf0_START (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patf0_END (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ptimeen_START (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ptimeen_END (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pcouten_START (17)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pcouten_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int patw1 : 1;
        unsigned int patw0 : 1;
        unsigned int pata5 : 1;
        unsigned int patf0 : 1;
        unsigned int reserved_0: 12;
        unsigned int ptimeen : 1;
        unsigned int pcouten : 1;
        unsigned int reserved_1: 14;
    } reg;
} SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw1_START (0)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw1_END (0)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw0_START (1)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw0_END (1)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pata5_START (2)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pata5_END (2)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patf0_START (3)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patf0_END (3)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ptimeen_START (16)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ptimeen_END (16)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pcouten_START (17)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pcouten_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pattcount : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_TPIU_TPIU_TPRCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TPRCR_pattcount_START (0)
#define SOC_CS_TPIU_TPIU_TPRCR_pattcount_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flinprog : 1;
        unsigned int ftstopped : 1;
        unsigned int tcpresent : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CS_TPIU_TPIU_FFSR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FFSR_flinprog_START (0)
#define SOC_CS_TPIU_TPIU_FFSR_flinprog_END (0)
#define SOC_CS_TPIU_TPIU_FFSR_ftstopped_START (1)
#define SOC_CS_TPIU_TPIU_FFSR_ftstopped_END (1)
#define SOC_CS_TPIU_TPIU_FFSR_tcpresent_START (2)
#define SOC_CS_TPIU_TPIU_FFSR_tcpresent_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enftc : 1;
        unsigned int encont : 1;
        unsigned int reserved_0: 2;
        unsigned int fonflin : 1;
        unsigned int fontrig : 1;
        unsigned int fonman : 1;
        unsigned int reserved_1: 1;
        unsigned int trigin : 1;
        unsigned int trigevt : 1;
        unsigned int trigfl : 1;
        unsigned int reserved_2: 1;
        unsigned int stopfl : 1;
        unsigned int stoptrig : 1;
        unsigned int reserved_3: 18;
    } reg;
} SOC_CS_TPIU_TPIU_FFCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FFCR_enftc_START (0)
#define SOC_CS_TPIU_TPIU_FFCR_enftc_END (0)
#define SOC_CS_TPIU_TPIU_FFCR_encont_START (1)
#define SOC_CS_TPIU_TPIU_FFCR_encont_END (1)
#define SOC_CS_TPIU_TPIU_FFCR_fonflin_START (4)
#define SOC_CS_TPIU_TPIU_FFCR_fonflin_END (4)
#define SOC_CS_TPIU_TPIU_FFCR_fontrig_START (5)
#define SOC_CS_TPIU_TPIU_FFCR_fontrig_END (5)
#define SOC_CS_TPIU_TPIU_FFCR_fonman_START (6)
#define SOC_CS_TPIU_TPIU_FFCR_fonman_END (6)
#define SOC_CS_TPIU_TPIU_FFCR_trigin_START (8)
#define SOC_CS_TPIU_TPIU_FFCR_trigin_END (8)
#define SOC_CS_TPIU_TPIU_FFCR_trigevt_START (9)
#define SOC_CS_TPIU_TPIU_FFCR_trigevt_END (9)
#define SOC_CS_TPIU_TPIU_FFCR_trigfl_START (10)
#define SOC_CS_TPIU_TPIU_FFCR_trigfl_END (10)
#define SOC_CS_TPIU_TPIU_FFCR_stopfl_START (12)
#define SOC_CS_TPIU_TPIU_FFCR_stopfl_END (12)
#define SOC_CS_TPIU_TPIU_FFCR_stoptrig_START (13)
#define SOC_CS_TPIU_TPIU_FFCR_stoptrig_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cyccount : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CS_TPIU_TPIU_FSCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FSCR_cyccount_START (0)
#define SOC_CS_TPIU_TPIU_FSCR_cyccount_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int extctlin : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_UNION;
#endif
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_extctlin_START (0)
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_extctlin_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int extctlout : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_UNION;
#endif
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_extctlout_START (0)
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_extctlout_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int key : 32;
    } reg;
} SOC_CS_TPIU_TPIU_LAR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_LAR_key_START (0)
#define SOC_CS_TPIU_TPIU_LAR_key_END (31)
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
} SOC_CS_TPIU_TPIU_LSR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_LSR_sli_START (0)
#define SOC_CS_TPIU_TPIU_LSR_sli_END (0)
#define SOC_CS_TPIU_TPIU_LSR_slk_START (1)
#define SOC_CS_TPIU_TPIU_LSR_slk_END (1)
#define SOC_CS_TPIU_TPIU_LSR_ntt_START (2)
#define SOC_CS_TPIU_TPIU_LSR_ntt_END (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
