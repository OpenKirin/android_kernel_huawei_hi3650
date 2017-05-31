#ifndef __SOC_ISP_IPC_INTERFACE_H__
#define __SOC_ISP_IPC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_IPC_MBX_SOURCE_ADDR(base,i) ((base) + (0x000+(i)*64))
#define SOC_ISP_IPC_MBX_DSET_ADDR(base,i) ((base) + (0x004+(i)*64))
#define SOC_ISP_IPC_MBX_DCLEAR_ADDR(base,i) ((base) + (0x008+(i)*64))
#define SOC_ISP_IPC_MBX_DSTATUS_ADDR(base,i) ((base) + (0x00C+(i)*64))
#define SOC_ISP_IPC_MBX_MODE_ADDR(base,i) ((base) + (0x010+(i)*64))
#define SOC_ISP_IPC_MBX_IMASK_ADDR(base,i) ((base) + (0x014+(i)*64))
#define SOC_ISP_IPC_MBX_ICLR_ADDR(base,i) ((base) + (0x018+(i)*64))
#define SOC_ISP_IPC_MBX_SEND_ADDR(base,i) ((base) + (0x01C+(i)*64))
#define SOC_ISP_IPC_MBX_DATA0_ADDR(base,i) ((base) + (0x020+(i)*64))
#define SOC_ISP_IPC_MBX_DATA1_ADDR(base,i) ((base) + (0x024+(i)*64))
#define SOC_ISP_IPC_MBX_DATA2_ADDR(base,i) ((base) + (0x028+(i)*64))
#define SOC_ISP_IPC_MBX_DATA3_ADDR(base,i) ((base) + (0x02C+(i)*64))
#define SOC_ISP_IPC_MBX_DATA4_ADDR(base,i) ((base) + (0x030+(i)*64))
#define SOC_ISP_IPC_MBX_DATA5_ADDR(base,i) ((base) + (0x034+(i)*64))
#define SOC_ISP_IPC_MBX_DATA6_ADDR(base,i) ((base) + (0x038+(i)*64))
#define SOC_ISP_IPC_MBX_DATA7_ADDR(base,i) ((base) + (0x03C+(i)*64))
#define SOC_ISP_IPC_CPU_IMST_ADDR(base,j) ((base) + (0x800+(j)*8))
#define SOC_ISP_IPC_CPU_IRST_ADDR(base,j) ((base) + (0x804+(j)*8))
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_ADDR(base) ((base) + (0x900))
#define SOC_ISP_IPC_IPC_LP_STATE_ADDR(base) ((base) + (0x904))
#define SOC_ISP_IPC_IPC_LOCK_ADDR(base) ((base) + (0xA00))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int source : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_SOURCE_UNION;
#endif
#define SOC_ISP_IPC_MBX_SOURCE_source_START (0)
#define SOC_ISP_IPC_MBX_SOURCE_source_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_DSET_UNION;
#endif
#define SOC_ISP_IPC_MBX_DSET_dset_START (0)
#define SOC_ISP_IPC_MBX_DSET_dset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dclear : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_DCLEAR_UNION;
#endif
#define SOC_ISP_IPC_MBX_DCLEAR_dclear_START (0)
#define SOC_ISP_IPC_MBX_DCLEAR_dclear_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dstatus : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_DSTATUS_UNION;
#endif
#define SOC_ISP_IPC_MBX_DSTATUS_dstatus_START (0)
#define SOC_ISP_IPC_MBX_DSTATUS_dstatus_END (2)
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
} SOC_ISP_IPC_MBX_MODE_UNION;
#endif
#define SOC_ISP_IPC_MBX_MODE_auto_answer_START (0)
#define SOC_ISP_IPC_MBX_MODE_auto_answer_END (0)
#define SOC_ISP_IPC_MBX_MODE_auto_link_START (1)
#define SOC_ISP_IPC_MBX_MODE_auto_link_END (1)
#define SOC_ISP_IPC_MBX_MODE_state_status_START (4)
#define SOC_ISP_IPC_MBX_MODE_state_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mask : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_IMASK_UNION;
#endif
#define SOC_ISP_IPC_MBX_IMASK_int_mask_START (0)
#define SOC_ISP_IPC_MBX_IMASK_int_mask_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_clear : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_ICLR_UNION;
#endif
#define SOC_ISP_IPC_MBX_ICLR_int_clear_START (0)
#define SOC_ISP_IPC_MBX_ICLR_int_clear_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int send : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_MBX_SEND_UNION;
#endif
#define SOC_ISP_IPC_MBX_SEND_send_START (0)
#define SOC_ISP_IPC_MBX_SEND_send_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data0 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA0_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA0_data0_START (0)
#define SOC_ISP_IPC_MBX_DATA0_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data1 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA1_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA1_data1_START (0)
#define SOC_ISP_IPC_MBX_DATA1_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data2 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA2_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA2_data2_START (0)
#define SOC_ISP_IPC_MBX_DATA2_data2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data3 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA3_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA3_data3_START (0)
#define SOC_ISP_IPC_MBX_DATA3_data3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data4 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA4_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA4_data4_START (0)
#define SOC_ISP_IPC_MBX_DATA4_data4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data5 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA5_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA5_data5_START (0)
#define SOC_ISP_IPC_MBX_DATA5_data5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data6 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA6_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA6_data6_START (0)
#define SOC_ISP_IPC_MBX_DATA6_data6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data7 : 32;
    } reg;
} SOC_ISP_IPC_MBX_DATA7_UNION;
#endif
#define SOC_ISP_IPC_MBX_DATA7_data7_START (0)
#define SOC_ISP_IPC_MBX_DATA7_data7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mask_status : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IPC_CPU_IMST_UNION;
#endif
#define SOC_ISP_IPC_CPU_IMST_int_mask_status_START (0)
#define SOC_ISP_IPC_CPU_IMST_int_mask_status_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_raw_status : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IPC_CPU_IRST_UNION;
#endif
#define SOC_ISP_IPC_CPU_IRST_int_raw_status_START (0)
#define SOC_ISP_IPC_CPU_IRST_int_raw_status_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mbx_active_status : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IPC_IPC_MBX_ACTIVE_UNION;
#endif
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_mbx_active_status_START (0)
#define SOC_ISP_IPC_IPC_MBX_ACTIVE_mbx_active_status_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_state : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_IPC_IPC_LP_STATE_UNION;
#endif
#define SOC_ISP_IPC_IPC_LP_STATE_lp_state_START (0)
#define SOC_ISP_IPC_IPC_LP_STATE_lp_state_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ipc_lock : 32;
    } reg;
} SOC_ISP_IPC_IPC_LOCK_UNION;
#endif
#define SOC_ISP_IPC_IPC_LOCK_ipc_lock_START (0)
#define SOC_ISP_IPC_IPC_LOCK_ipc_lock_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
