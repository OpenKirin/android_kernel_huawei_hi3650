#ifndef __SOC_DSS_DBUG_INTERFACE_H__
#define __SOC_DSS_DBUG_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV0_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_DBUG_CRC_DBG_OV1_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_DBUG_CRC_DBG_SUM_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_DBUG_CRC_OV0_EN_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_DBUG_CRC_OV0_FRM_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_DBUG_CRC_OV1_EN_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_DBUG_CRC_OV1_FRM_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_DBUG_CRC_SUM_EN_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_DBUG_CRC_SUM_FRM_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_ADDR(base) ((base) + (0x0104))
#define SOC_DSS_DBUG_DBG_BUS_MODE_ADDR(base) ((base) + (0x0108))
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_ADDR(base) ((base) + (0x010C))
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_ADDR(base) ((base) + (0x0110))
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_ADDR(base) ((base) + (0x0114))
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_ADDR(base) ((base) + (0x0118))
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_ADDR(base) ((base) + (0x011C))
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_ADDR(base) ((base) + (0x0120))
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_ADDR(base) ((base) + (0x0124))
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_ADDR(base) ((base) + (0x0128))
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_ADDR(base) ((base) + (0x012C))
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_ADDR(base) ((base) + (0x0130))
#define SOC_DSS_DBUG_DBG_PTR_ADDR_ADDR(base) ((base) + (0x0134))
#define SOC_DSS_DBUG_DBG_BUS_TIMING_ADDR(base) ((base) + (0x0138))
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_ADDR(base) ((base) + (0x013C))
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR(base) ((base) + (0x0140))
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_ADDR(base) ((base) + (0x0144))
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_ADDR(base) ((base) + (0x0148))
#define SOC_DSS_DBUG_TP_MEM_CTRL0_ADDR(base) ((base) + (0x014C))
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_ADDR(base) ((base) + (0x0150))
#define SOC_DSS_DBUG_DSS_DBG_WPTR_ADDR(base) ((base) + (0x0154))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_ov0 : 32;
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV0_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_START (0)
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_ov1 : 32;
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV1_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_START (0)
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_dbg_sum : 32;
    } reg;
} SOC_DSS_DBUG_CRC_DBG_SUM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_START (0)
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ov0_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_CRC_OV0_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_START (0)
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_glb_dbg_o : 32;
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_START (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_glb_dbg_i : 32;
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_START (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ov0_frm : 32;
    } reg;
} SOC_DSS_DBUG_CRC_OV0_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_START (0)
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ov1_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_CRC_OV1_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_START (0)
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_ov1_frm : 32;
    } reg;
} SOC_DSS_DBUG_CRC_OV1_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_START (0)
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_sum_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_CRC_SUM_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_START (0)
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crc_sum_frm : 32;
    } reg;
} SOC_DSS_DBUG_CRC_SUM_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_START (0)
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2ctrl_lbs_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION;
#endif
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_START (0)
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2lbs_lbs_frm_len : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_START (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_MODE_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_START (0)
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2lbs_lbs_frm : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_START (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2lbs_lbs_id : 32;
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_START (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2lbs_bus_msk : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_START (0)
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2head_diag_id : 32;
    } reg;
} SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_START (0)
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2head_hsrv_id : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_START (0)
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2head_lsrv_id : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_START (0)
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2head_session_id : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_START (0)
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2head_msg_type : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_START (0)
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int dbg_bus_base_addr : 28;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_START (4)
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int dbg_bus_end_addr : 28;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_START (4)
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int dbg_ptr_addr : 28;
    } reg;
} SOC_DSS_DBUG_DBG_PTR_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_START (4)
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_timing : 32;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_START (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_ldi_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_START (0)
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_end : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_START (0)
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg2mem_gate_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION;
#endif
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_START (0)
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sp_mem_ctrl0_log : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION;
#endif
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_START (0)
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tp_mem_ctrl0 : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_DBUG_TP_MEM_CTRL0_UNION;
#endif
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_START (0)
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_timing_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_START (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dss_dbg_wptr : 32;
    } reg;
} SOC_DSS_DBUG_DSS_DBG_WPTR_UNION;
#endif
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_START (0)
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
