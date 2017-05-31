#ifndef __SOC_ASC_INTERFACE_H__
#define __SOC_ASC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASC_EN_ADDR(base) ((base) + (0x000))
#define SOC_ASC_REGION_NON_SECURE_ADDR(base,i) ((base) + (0x010+0x20*(i)))
#define SOC_ASC_REGION_START_ADDR_LOW_ADDR(base,i) ((base) + (0x014+0x20*(i)))
#define SOC_ASC_REGION_START_ADDR_HIGH_ADDR(base,i) ((base) + (0x018+0x20*(i)))
#define SOC_ASC_REGION_END_ADDR_LOW_ADDR(base,i) ((base) + (0x01C+0x20*(i)))
#define SOC_ASC_REGION_END_ADDR_HIGH_ADDR(base,i) ((base) + (0x020+0x20*(i)))
#define SOC_ASC_INT_STATUS_ADDR(base) ((base) + (0x120))
#define SOC_ASC_INT_CLEAR_ADDR(base) ((base) + (0x124))
#define SOC_ASC_FAIL_ADDR_LOW_ADDR(base) ((base) + (0x128))
#define SOC_ASC_FAIL_ADDR_HIGH_ADDR(base) ((base) + (0x12C))
#define SOC_ASC_FAIL_ID_ADDR(base) ((base) + (0x130))
#define SOC_ASC_FAIL_INFO_ADDR(base) ((base) + (0x134))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int asc_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASC_EN_UNION;
#endif
#define SOC_ASC_EN_asc_en_START (0)
#define SOC_ASC_EN_asc_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int region_non_secure : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASC_REGION_NON_SECURE_UNION;
#endif
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_START (0)
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 12;
        unsigned int region_start_addr_low : 20;
    } reg;
} SOC_ASC_REGION_START_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_START (12)
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int region_start_addr_high : 32;
    } reg;
} SOC_ASC_REGION_START_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_START (0)
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 12;
        unsigned int region_end_addr_low : 20;
    } reg;
} SOC_ASC_REGION_END_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_START (12)
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int region_end_addr_high : 32;
    } reg;
} SOC_ASC_REGION_END_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_START (0)
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_status : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASC_INT_STATUS_UNION;
#endif
#define SOC_ASC_INT_STATUS_int_status_START (0)
#define SOC_ASC_INT_STATUS_int_status_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_clear : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASC_INT_CLEAR_UNION;
#endif
#define SOC_ASC_INT_CLEAR_int_clear_START (0)
#define SOC_ASC_INT_CLEAR_int_clear_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fail_addr_low : 32;
    } reg;
} SOC_ASC_FAIL_ADDR_LOW_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_START (0)
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fail_addr_high : 32;
    } reg;
} SOC_ASC_FAIL_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_START (0)
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fail_id : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASC_FAIL_ID_UNION;
#endif
#define SOC_ASC_FAIL_ID_fail_id_START (0)
#define SOC_ASC_FAIL_ID_fail_id_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fail_wr : 1;
        unsigned int fail_rd : 1;
        unsigned int fail_len : 4;
        unsigned int fail_size : 3;
        unsigned int fail_burst : 2;
        unsigned int fail_lock : 2;
        unsigned int fail_cache : 4;
        unsigned int fail_prot : 3;
        unsigned int reserved : 12;
    } reg;
} SOC_ASC_FAIL_INFO_UNION;
#endif
#define SOC_ASC_FAIL_INFO_fail_wr_START (0)
#define SOC_ASC_FAIL_INFO_fail_wr_END (0)
#define SOC_ASC_FAIL_INFO_fail_rd_START (1)
#define SOC_ASC_FAIL_INFO_fail_rd_END (1)
#define SOC_ASC_FAIL_INFO_fail_len_START (2)
#define SOC_ASC_FAIL_INFO_fail_len_END (5)
#define SOC_ASC_FAIL_INFO_fail_size_START (6)
#define SOC_ASC_FAIL_INFO_fail_size_END (8)
#define SOC_ASC_FAIL_INFO_fail_burst_START (9)
#define SOC_ASC_FAIL_INFO_fail_burst_END (10)
#define SOC_ASC_FAIL_INFO_fail_lock_START (11)
#define SOC_ASC_FAIL_INFO_fail_lock_END (12)
#define SOC_ASC_FAIL_INFO_fail_cache_START (13)
#define SOC_ASC_FAIL_INFO_fail_cache_END (16)
#define SOC_ASC_FAIL_INFO_fail_prot_START (17)
#define SOC_ASC_FAIL_INFO_fail_prot_END (19)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
