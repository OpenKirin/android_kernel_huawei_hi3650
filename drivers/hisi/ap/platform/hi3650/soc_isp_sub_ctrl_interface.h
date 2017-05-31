#ifndef __SOC_ISP_SUB_CTRL_INTERFACE_H__
#define __SOC_ISP_SUB_CTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_ADDR(base) ((base) + (0x0))
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_ADDR(base) ((base) + (0x4))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_ADDR(base) ((base) + (0x8))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_ADDR(base) ((base) + (0xC))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_ADDR(base) ((base) + (0x10))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_ADDR(base) ((base) + (0x14))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_ADDR(base) ((base) + (0x18))
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_ADDR(base) ((base) + (0x1C))
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_ADDR(base) ((base) + (0x20))
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_ADDR(base) ((base) + (0x24))
#define SOC_ISP_SUB_CTRL_vic0_out0_ADDR(base) ((base) + (0x28))
#define SOC_ISP_SUB_CTRL_vic0_in0_ADDR(base) ((base) + (0x2C))
#define SOC_ISP_SUB_CTRL_vic0_in1_ADDR(base) ((base) + (0x30))
#define SOC_ISP_SUB_CTRL_vic1_out0_ADDR(base) ((base) + (0x34))
#define SOC_ISP_SUB_CTRL_vic1_in0_ADDR(base) ((base) + (0x38))
#define SOC_ISP_SUB_CTRL_vic1_in1_ADDR(base) ((base) + (0x3C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_wdt_apm_clken : 1;
        unsigned int isp_ipc_apm_clken : 1;
        unsigned int isp_tim_apm_clken : 1;
        unsigned int sub_ctrl_reg0_7to3b : 5;
        unsigned int sub_ctrl_reg0_15to8b : 8;
        unsigned int sub_ctrl_reg0_23to16b : 8;
        unsigned int sub_ctrl_reg0_31to24b : 8;
    } reg;
} SOC_ISP_SUB_CTRL_SUBSYS_CFG_UNION;
#endif
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_wdt_apm_clken_START (0)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_wdt_apm_clken_END (0)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_ipc_apm_clken_START (1)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_ipc_apm_clken_END (1)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_tim_apm_clken_START (2)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_isp_tim_apm_clken_END (2)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_START (3)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_END (7)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_START (8)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_END (15)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_START (16)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_END (23)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_START (24)
#define SOC_ISP_SUB_CTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sub_ctrl_reg1_7to0b : 8;
        unsigned int sub_ctrl_reg1_15to8b : 8;
        unsigned int sub_ctrl_reg1_23to16b : 8;
        unsigned int sub_ctrl_reg1_31to24b : 8;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_CORE_CFG_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_START (0)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_END (7)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_START (8)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_END (15)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to16b_START (16)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to16b_END (23)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_START (24)
#define SOC_ISP_SUB_CTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_axi_m1_waddr_err : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_axi_m1_raddr_err : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_axi_m2_waddr_err : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_axi_m2_raddr_err : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int isp_axi_mst_err_srst_req_apm : 1;
        unsigned int reserved_0 : 7;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 23;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sub_ctrl_ro_reg : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_START (0)
#define SOC_ISP_SUB_CTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int subctrl_to_core_grp0 : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_START (0)
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int subctrl_to_core_grp1 : 32;
    } reg;
} SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_START (0)
#define SOC_ISP_SUB_CTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic0_out_irq_mask : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic0_out0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_out0_vic0_out_irq_mask_START (0)
#define SOC_ISP_SUB_CTRL_vic0_out0_vic0_out_irq_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic0_in_irq_level_mask : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic0_in0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_in0_vic0_in_irq_level_mask_START (0)
#define SOC_ISP_SUB_CTRL_vic0_in0_vic0_in_irq_level_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic0_in_irq_level_force : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic0_in1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic0_in1_vic0_in_irq_level_force_START (0)
#define SOC_ISP_SUB_CTRL_vic0_in1_vic0_in_irq_level_force_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic1_out_irq_mask : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic1_out0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_out0_vic1_out_irq_mask_START (0)
#define SOC_ISP_SUB_CTRL_vic1_out0_vic1_out_irq_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic1_in_irq_level_mask : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic1_in0_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_in0_vic1_in_irq_level_mask_START (0)
#define SOC_ISP_SUB_CTRL_vic1_in0_vic1_in_irq_level_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vic1_in_irq_level_force : 32;
    } reg;
} SOC_ISP_SUB_CTRL_vic1_in1_UNION;
#endif
#define SOC_ISP_SUB_CTRL_vic1_in1_vic1_in_irq_level_force_START (0)
#define SOC_ISP_SUB_CTRL_vic1_in1_vic1_in_irq_level_force_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
