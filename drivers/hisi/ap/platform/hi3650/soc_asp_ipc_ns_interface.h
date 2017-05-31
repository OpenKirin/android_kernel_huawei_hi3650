#ifndef __SOC_ASP_IPC_NS_INTERFACE_H__
#define __SOC_ASP_IPC_NS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASP_IPC_NS_MBX_SOURCE_ADDR(base,i) ((base) + (0x000+(i)*64))
#define SOC_ASP_IPC_NS_MBX_DSET_ADDR(base,i) ((base) + (0x004+(i)*64))
#define SOC_ASP_IPC_NS_MBX_DCLEAR_ADDR(base,i) ((base) + (0x008+(i)*64))
#define SOC_ASP_IPC_NS_MBX_DSTATUS_ADDR(base,i) ((base) + (0x00C+(i)*64))
#define SOC_ASP_IPC_NS_MBX_MODE_ADDR(base,i) ((base) + (0x010+(i)*64))
#define SOC_ASP_IPC_NS_MBX_IMASK_ADDR(base,i) ((base) + (0x014+(i)*64))
#define SOC_ASP_IPC_NS_MBX_ICLR_ADDR(base,i) ((base) + (0x018+(i)*64))
#define SOC_ASP_IPC_NS_MBX_SEND_ADDR(base,i) ((base) + (0x01C+(i)*64))
#define SOC_ASP_IPC_NS_MBX_DATA0_ADDR(base,i) ((base) + (0x020+(i)*64))
#define SOC_ASP_IPC_NS_MBX_DATA1_ADDR(base,i) ((base) + (0x024+(i)*64))
#define SOC_ASP_IPC_NS_CPU_IMST_ADDR(base,j) ((base) + (0x800+(j)*8))
#define SOC_ASP_IPC_NS_CPU_IRST_ADDR(base,j) ((base) + (0x804+(j)*8))
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_ADDR(base) ((base) + (0x900))
#define SOC_ASP_IPC_NS_IPC_LOCK_ADDR(base) ((base) + (0xA00))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int source : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_SOURCE_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_SOURCE_source_START (0)
#define SOC_ASP_IPC_NS_MBX_SOURCE_source_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dset : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_DSET_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DSET_dset_START (0)
#define SOC_ASP_IPC_NS_MBX_DSET_dset_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dclear : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_DCLEAR_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DCLEAR_dclear_START (0)
#define SOC_ASP_IPC_NS_MBX_DCLEAR_dclear_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dstatus : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_DSTATUS_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DSTATUS_dstatus_START (0)
#define SOC_ASP_IPC_NS_MBX_DSTATUS_dstatus_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_answer : 1;
        unsigned int auto_link : 1;
        unsigned int reserved_0 : 2;
        unsigned int state_status : 4;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_ASP_IPC_NS_MBX_MODE_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_MODE_auto_answer_START (0)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_answer_END (0)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_link_START (1)
#define SOC_ASP_IPC_NS_MBX_MODE_auto_link_END (1)
#define SOC_ASP_IPC_NS_MBX_MODE_state_status_START (4)
#define SOC_ASP_IPC_NS_MBX_MODE_state_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mask : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_IMASK_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_IMASK_int_mask_START (0)
#define SOC_ASP_IPC_NS_MBX_IMASK_int_mask_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_clear : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_ICLR_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_ICLR_int_clear_START (0)
#define SOC_ASP_IPC_NS_MBX_ICLR_int_clear_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int send : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_MBX_SEND_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_SEND_send_START (0)
#define SOC_ASP_IPC_NS_MBX_SEND_send_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data0 : 32;
    } reg;
} SOC_ASP_IPC_NS_MBX_DATA0_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DATA0_data0_START (0)
#define SOC_ASP_IPC_NS_MBX_DATA0_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data1 : 32;
    } reg;
} SOC_ASP_IPC_NS_MBX_DATA1_UNION;
#endif
#define SOC_ASP_IPC_NS_MBX_DATA1_data1_START (0)
#define SOC_ASP_IPC_NS_MBX_DATA1_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mask_status : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_CPU_IMST_UNION;
#endif
#define SOC_ASP_IPC_NS_CPU_IMST_int_mask_status_START (0)
#define SOC_ASP_IPC_NS_CPU_IMST_int_mask_status_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_raw_status : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_CPU_IRST_UNION;
#endif
#define SOC_ASP_IPC_NS_CPU_IRST_int_raw_status_START (0)
#define SOC_ASP_IPC_NS_CPU_IRST_int_raw_status_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mbx_active_status : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_UNION;
#endif
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_mbx_active_status_START (0)
#define SOC_ASP_IPC_NS_IPC_MBX_ACTIVE_mbx_active_status_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ipc_lock : 32;
    } reg;
} SOC_ASP_IPC_NS_IPC_LOCK_UNION;
#endif
#define SOC_ASP_IPC_NS_IPC_LOCK_ipc_lock_START (0)
#define SOC_ASP_IPC_NS_IPC_LOCK_ipc_lock_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
