#ifndef __SOC_ISP_I2C_INTERFACE_H__
#define __SOC_ISP_I2C_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_I2C_CON_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_I2C_TAR_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_I2C_SAR_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_I2C_HS_MADDR_ADDR(base) ((base) + (0x000c))
#define SOC_ISP_I2C_DATA_CMD_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_I2C_SS_SCL_HCNT_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_I2C_SS_SCL_LCNT_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_I2C_FS_SCL_HCNT_ADDR(base) ((base) + (0x001c))
#define SOC_ISP_I2C_FS_SCL_LCNT_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_I2C_HS_SCL_HCNT_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_I2C_HS_SCL_LCNT_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_I2C_INTR_STAT_ADDR(base) ((base) + (0x002c))
#define SOC_ISP_I2C_INTR_MASK_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_I2C_RAW_INTR_STAT_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_I2C_RX_TL_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_I2C_TX_TL_ADDR(base) ((base) + (0x003c))
#define SOC_ISP_I2C_CLR_INTR_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_I2C_CLR_RX_UNDER_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_I2C_CLK_RX_OVER_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_I2C_CLR_TX_OVER_ADDR(base) ((base) + (0x004c))
#define SOC_ISP_I2C_CLR_RD_REQ_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_I2C_CLR_TX_ABRT_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_I2C_CLR_RX_DONE_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_I2C_CLR_ACTIVITY_ADDR(base) ((base) + (0x005c))
#define SOC_ISP_I2C_CLK_STOP_DET_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_I2C_CLR_START_DET_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_I2C_CLR_GEN_CALL_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_I2C_ENABLE_ADDR(base) ((base) + (0x006c))
#define SOC_ISP_I2C_STATUS_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_I2C_TXFLR_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_I2C_RXFLR_ADDR(base) ((base) + (0x0078))
#define SOC_ISP_I2C_SDA_HOLD_ADDR(base) ((base) + (0x007c))
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ADDR(base) ((base) + (0x0080))
#define SOC_ISP_I2C_SLV_DATA_NACK_ONLY_ADDR(base) ((base) + (0x0084))
#define SOC_ISP_I2C_DMA_CR_ADDR(base) ((base) + (0x0088))
#define SOC_ISP_I2C_DMA_TDLR_ADDR(base) ((base) + (0x008C))
#define SOC_ISP_I2C_DMA_RDLR_ADDR(base) ((base) + (0x0090))
#define SOC_ISP_I2C_SDA_SETUP_ADDR(base) ((base) + (0x0094))
#define SOC_ISP_I2C_ACK_GENERAL_CALL_ADDR(base) ((base) + (0x0098))
#define SOC_ISP_I2C_ENABLE_STATUS_ADDR(base) ((base) + (0x009c))
#define SOC_ISP_I2C_FS_SPKLEN_ADDR(base) ((base) + (0x00a0))
#define SOC_ISP_I2C_HS_SPKLEN_ADDR(base) ((base) + (0x00a4))
#define SOC_ISP_I2C_CLR_RESTART_DET_ADDR(base) ((base) + (0x00a8))
#define SOC_ISP_I2C_COMP_PARAM_1_ADDR(base) ((base) + (0x00f4))
#define SOC_ISP_I2C_COMP_VERSION_ADDR(base) ((base) + (0x00f8))
#define SOC_ISP_I2C_COMP_TYPE_ADDR(base) ((base) + (0x00fc))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MASTER_MODE : 1;
        unsigned int SPEED : 2;
        unsigned int IC_10BITADDR_SLAVE : 1;
        unsigned int IC_10BITADDR_MASTER : 1;
        unsigned int IC_RESTART_EN : 1;
        unsigned int IC_SLAVE_DISABLE : 1;
        unsigned int STOP_DET_IFADDRESSED : 1;
        unsigned int TX_EMPTY_CTRL : 1;
        unsigned int RX_FIFO_FULL_HLD_CTRL : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_I2C_CON_UNION;
#endif
#define SOC_ISP_I2C_CON_MASTER_MODE_START (0)
#define SOC_ISP_I2C_CON_MASTER_MODE_END (0)
#define SOC_ISP_I2C_CON_SPEED_START (1)
#define SOC_ISP_I2C_CON_SPEED_END (2)
#define SOC_ISP_I2C_CON_IC_10BITADDR_SLAVE_START (3)
#define SOC_ISP_I2C_CON_IC_10BITADDR_SLAVE_END (3)
#define SOC_ISP_I2C_CON_IC_10BITADDR_MASTER_START (4)
#define SOC_ISP_I2C_CON_IC_10BITADDR_MASTER_END (4)
#define SOC_ISP_I2C_CON_IC_RESTART_EN_START (5)
#define SOC_ISP_I2C_CON_IC_RESTART_EN_END (5)
#define SOC_ISP_I2C_CON_IC_SLAVE_DISABLE_START (6)
#define SOC_ISP_I2C_CON_IC_SLAVE_DISABLE_END (6)
#define SOC_ISP_I2C_CON_STOP_DET_IFADDRESSED_START (7)
#define SOC_ISP_I2C_CON_STOP_DET_IFADDRESSED_END (7)
#define SOC_ISP_I2C_CON_TX_EMPTY_CTRL_START (8)
#define SOC_ISP_I2C_CON_TX_EMPTY_CTRL_END (8)
#define SOC_ISP_I2C_CON_RX_FIFO_FULL_HLD_CTRL_START (9)
#define SOC_ISP_I2C_CON_RX_FIFO_FULL_HLD_CTRL_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_TAR : 10;
        unsigned int GC_OR_START : 1;
        unsigned int SPECIAL : 1;
        unsigned int IC_10BITADDR_MASTER : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_I2C_TAR_UNION;
#endif
#define SOC_ISP_I2C_TAR_IC_TAR_START (0)
#define SOC_ISP_I2C_TAR_IC_TAR_END (9)
#define SOC_ISP_I2C_TAR_GC_OR_START_START (10)
#define SOC_ISP_I2C_TAR_GC_OR_START_END (10)
#define SOC_ISP_I2C_TAR_SPECIAL_START (11)
#define SOC_ISP_I2C_TAR_SPECIAL_END (11)
#define SOC_ISP_I2C_TAR_IC_10BITADDR_MASTER_START (12)
#define SOC_ISP_I2C_TAR_IC_10BITADDR_MASTER_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_SAR : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_I2C_SAR_UNION;
#endif
#define SOC_ISP_I2C_SAR_IC_SAR_START (0)
#define SOC_ISP_I2C_SAR_IC_SAR_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_HS_MAR : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_I2C_HS_MADDR_UNION;
#endif
#define SOC_ISP_I2C_HS_MADDR_IC_HS_MAR_START (0)
#define SOC_ISP_I2C_HS_MADDR_IC_HS_MAR_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DAT : 8;
        unsigned int CMD : 1;
        unsigned int STOP : 1;
        unsigned int RESTART : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_I2C_DATA_CMD_UNION;
#endif
#define SOC_ISP_I2C_DATA_CMD_DAT_START (0)
#define SOC_ISP_I2C_DATA_CMD_DAT_END (7)
#define SOC_ISP_I2C_DATA_CMD_CMD_START (8)
#define SOC_ISP_I2C_DATA_CMD_CMD_END (8)
#define SOC_ISP_I2C_DATA_CMD_STOP_START (9)
#define SOC_ISP_I2C_DATA_CMD_STOP_END (9)
#define SOC_ISP_I2C_DATA_CMD_RESTART_START (10)
#define SOC_ISP_I2C_DATA_CMD_RESTART_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_SS_SCL_HCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_SS_SCL_HCNT_UNION;
#endif
#define SOC_ISP_I2C_SS_SCL_HCNT_IC_SS_SCL_HCNT_START (0)
#define SOC_ISP_I2C_SS_SCL_HCNT_IC_SS_SCL_HCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_SS_SCL_LCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_SS_SCL_LCNT_UNION;
#endif
#define SOC_ISP_I2C_SS_SCL_LCNT_IC_SS_SCL_LCNT_START (0)
#define SOC_ISP_I2C_SS_SCL_LCNT_IC_SS_SCL_LCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_FS_SCL_HCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_FS_SCL_HCNT_UNION;
#endif
#define SOC_ISP_I2C_FS_SCL_HCNT_IC_FS_SCL_HCNT_START (0)
#define SOC_ISP_I2C_FS_SCL_HCNT_IC_FS_SCL_HCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_FS_SCL_LCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_FS_SCL_LCNT_UNION;
#endif
#define SOC_ISP_I2C_FS_SCL_LCNT_IC_FS_SCL_LCNT_START (0)
#define SOC_ISP_I2C_FS_SCL_LCNT_IC_FS_SCL_LCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_HS_SCL_HCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_HS_SCL_HCNT_UNION;
#endif
#define SOC_ISP_I2C_HS_SCL_HCNT_IC_HS_SCL_HCNT_START (0)
#define SOC_ISP_I2C_HS_SCL_HCNT_IC_HS_SCL_HCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_HS_SCL_LCNT : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_I2C_HS_SCL_LCNT_UNION;
#endif
#define SOC_ISP_I2C_HS_SCL_LCNT_IC_HS_SCL_LCNT_START (0)
#define SOC_ISP_I2C_HS_SCL_LCNT_IC_HS_SCL_LCNT_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int R_RX_UNDER : 1;
        unsigned int R_RX_OVER : 1;
        unsigned int R_RX_FULL : 1;
        unsigned int R_TX_OVER : 1;
        unsigned int R_TX_EMPTY : 1;
        unsigned int R_RD_REQ : 1;
        unsigned int R_TX_ABRT : 1;
        unsigned int R_RX_DONE : 1;
        unsigned int R_ACTIVITY : 1;
        unsigned int R_STOP_DET : 1;
        unsigned int R_START_DET : 1;
        unsigned int R_GEN_CALL : 1;
        unsigned int R_RESTART_DET : 1;
        unsigned int R_MST_ON_HOLD : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_I2C_INTR_STAT_UNION;
#endif
#define SOC_ISP_I2C_INTR_STAT_R_RX_UNDER_START (0)
#define SOC_ISP_I2C_INTR_STAT_R_RX_UNDER_END (0)
#define SOC_ISP_I2C_INTR_STAT_R_RX_OVER_START (1)
#define SOC_ISP_I2C_INTR_STAT_R_RX_OVER_END (1)
#define SOC_ISP_I2C_INTR_STAT_R_RX_FULL_START (2)
#define SOC_ISP_I2C_INTR_STAT_R_RX_FULL_END (2)
#define SOC_ISP_I2C_INTR_STAT_R_TX_OVER_START (3)
#define SOC_ISP_I2C_INTR_STAT_R_TX_OVER_END (3)
#define SOC_ISP_I2C_INTR_STAT_R_TX_EMPTY_START (4)
#define SOC_ISP_I2C_INTR_STAT_R_TX_EMPTY_END (4)
#define SOC_ISP_I2C_INTR_STAT_R_RD_REQ_START (5)
#define SOC_ISP_I2C_INTR_STAT_R_RD_REQ_END (5)
#define SOC_ISP_I2C_INTR_STAT_R_TX_ABRT_START (6)
#define SOC_ISP_I2C_INTR_STAT_R_TX_ABRT_END (6)
#define SOC_ISP_I2C_INTR_STAT_R_RX_DONE_START (7)
#define SOC_ISP_I2C_INTR_STAT_R_RX_DONE_END (7)
#define SOC_ISP_I2C_INTR_STAT_R_ACTIVITY_START (8)
#define SOC_ISP_I2C_INTR_STAT_R_ACTIVITY_END (8)
#define SOC_ISP_I2C_INTR_STAT_R_STOP_DET_START (9)
#define SOC_ISP_I2C_INTR_STAT_R_STOP_DET_END (9)
#define SOC_ISP_I2C_INTR_STAT_R_START_DET_START (10)
#define SOC_ISP_I2C_INTR_STAT_R_START_DET_END (10)
#define SOC_ISP_I2C_INTR_STAT_R_GEN_CALL_START (11)
#define SOC_ISP_I2C_INTR_STAT_R_GEN_CALL_END (11)
#define SOC_ISP_I2C_INTR_STAT_R_RESTART_DET_START (12)
#define SOC_ISP_I2C_INTR_STAT_R_RESTART_DET_END (12)
#define SOC_ISP_I2C_INTR_STAT_R_MST_ON_HOLD_START (13)
#define SOC_ISP_I2C_INTR_STAT_R_MST_ON_HOLD_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int M_RX_UNDER : 1;
        unsigned int R_RX_OVER : 1;
        unsigned int R_RX_FULL : 1;
        unsigned int M_TX_OVER : 1;
        unsigned int M_TX_EMPTY : 1;
        unsigned int M_RD_REQ : 1;
        unsigned int M_TX_ABRT : 1;
        unsigned int R_RX_DONE : 1;
        unsigned int M_ACTIVITY : 1;
        unsigned int M_STOP_DET : 1;
        unsigned int M_START_DET : 1;
        unsigned int M_GEN_CALL : 1;
        unsigned int M_RESTART_DET : 1;
        unsigned int M_MST_ON_HOLD : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_I2C_INTR_MASK_UNION;
#endif
#define SOC_ISP_I2C_INTR_MASK_M_RX_UNDER_START (0)
#define SOC_ISP_I2C_INTR_MASK_M_RX_UNDER_END (0)
#define SOC_ISP_I2C_INTR_MASK_R_RX_OVER_START (1)
#define SOC_ISP_I2C_INTR_MASK_R_RX_OVER_END (1)
#define SOC_ISP_I2C_INTR_MASK_R_RX_FULL_START (2)
#define SOC_ISP_I2C_INTR_MASK_R_RX_FULL_END (2)
#define SOC_ISP_I2C_INTR_MASK_M_TX_OVER_START (3)
#define SOC_ISP_I2C_INTR_MASK_M_TX_OVER_END (3)
#define SOC_ISP_I2C_INTR_MASK_M_TX_EMPTY_START (4)
#define SOC_ISP_I2C_INTR_MASK_M_TX_EMPTY_END (4)
#define SOC_ISP_I2C_INTR_MASK_M_RD_REQ_START (5)
#define SOC_ISP_I2C_INTR_MASK_M_RD_REQ_END (5)
#define SOC_ISP_I2C_INTR_MASK_M_TX_ABRT_START (6)
#define SOC_ISP_I2C_INTR_MASK_M_TX_ABRT_END (6)
#define SOC_ISP_I2C_INTR_MASK_R_RX_DONE_START (7)
#define SOC_ISP_I2C_INTR_MASK_R_RX_DONE_END (7)
#define SOC_ISP_I2C_INTR_MASK_M_ACTIVITY_START (8)
#define SOC_ISP_I2C_INTR_MASK_M_ACTIVITY_END (8)
#define SOC_ISP_I2C_INTR_MASK_M_STOP_DET_START (9)
#define SOC_ISP_I2C_INTR_MASK_M_STOP_DET_END (9)
#define SOC_ISP_I2C_INTR_MASK_M_START_DET_START (10)
#define SOC_ISP_I2C_INTR_MASK_M_START_DET_END (10)
#define SOC_ISP_I2C_INTR_MASK_M_GEN_CALL_START (11)
#define SOC_ISP_I2C_INTR_MASK_M_GEN_CALL_END (11)
#define SOC_ISP_I2C_INTR_MASK_M_RESTART_DET_START (12)
#define SOC_ISP_I2C_INTR_MASK_M_RESTART_DET_END (12)
#define SOC_ISP_I2C_INTR_MASK_M_MST_ON_HOLD_START (13)
#define SOC_ISP_I2C_INTR_MASK_M_MST_ON_HOLD_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RX_UNDER : 1;
        unsigned int RX_OVER : 1;
        unsigned int RX_FULL : 1;
        unsigned int TX_OVER : 1;
        unsigned int TX_EMPTY : 1;
        unsigned int RD_REQ : 1;
        unsigned int TX_ABRT : 1;
        unsigned int RX_DONE : 1;
        unsigned int ACTIVITY : 1;
        unsigned int STOP_DET : 1;
        unsigned int START_DET : 1;
        unsigned int GEN_CALL : 1;
        unsigned int RESTART_DET : 1;
        unsigned int MST_ON_HOLD : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_I2C_RAW_INTR_STAT_UNION;
#endif
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_UNDER_START (0)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_UNDER_END (0)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_OVER_START (1)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_OVER_END (1)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_FULL_START (2)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_FULL_END (2)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_OVER_START (3)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_OVER_END (3)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_EMPTY_START (4)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_EMPTY_END (4)
#define SOC_ISP_I2C_RAW_INTR_STAT_RD_REQ_START (5)
#define SOC_ISP_I2C_RAW_INTR_STAT_RD_REQ_END (5)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_ABRT_START (6)
#define SOC_ISP_I2C_RAW_INTR_STAT_TX_ABRT_END (6)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_DONE_START (7)
#define SOC_ISP_I2C_RAW_INTR_STAT_RX_DONE_END (7)
#define SOC_ISP_I2C_RAW_INTR_STAT_ACTIVITY_START (8)
#define SOC_ISP_I2C_RAW_INTR_STAT_ACTIVITY_END (8)
#define SOC_ISP_I2C_RAW_INTR_STAT_STOP_DET_START (9)
#define SOC_ISP_I2C_RAW_INTR_STAT_STOP_DET_END (9)
#define SOC_ISP_I2C_RAW_INTR_STAT_START_DET_START (10)
#define SOC_ISP_I2C_RAW_INTR_STAT_START_DET_END (10)
#define SOC_ISP_I2C_RAW_INTR_STAT_GEN_CALL_START (11)
#define SOC_ISP_I2C_RAW_INTR_STAT_GEN_CALL_END (11)
#define SOC_ISP_I2C_RAW_INTR_STAT_RESTART_DET_START (12)
#define SOC_ISP_I2C_RAW_INTR_STAT_RESTART_DET_END (12)
#define SOC_ISP_I2C_RAW_INTR_STAT_MST_ON_HOLD_START (13)
#define SOC_ISP_I2C_RAW_INTR_STAT_MST_ON_HOLD_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RX_TL : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_I2C_RX_TL_UNION;
#endif
#define SOC_ISP_I2C_RX_TL_RX_TL_START (0)
#define SOC_ISP_I2C_RX_TL_RX_TL_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TX_TL : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_I2C_TX_TL_UNION;
#endif
#define SOC_ISP_I2C_TX_TL_TX_TL_START (0)
#define SOC_ISP_I2C_TX_TL_TX_TL_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_INTR : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_INTR_UNION;
#endif
#define SOC_ISP_I2C_CLR_INTR_CLR_INTR_START (0)
#define SOC_ISP_I2C_CLR_INTR_CLR_INTR_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_RX_UNDER : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_RX_UNDER_UNION;
#endif
#define SOC_ISP_I2C_CLR_RX_UNDER_CLR_RX_UNDER_START (0)
#define SOC_ISP_I2C_CLR_RX_UNDER_CLR_RX_UNDER_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_RX_OVER : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLK_RX_OVER_UNION;
#endif
#define SOC_ISP_I2C_CLK_RX_OVER_CLR_RX_OVER_START (0)
#define SOC_ISP_I2C_CLK_RX_OVER_CLR_RX_OVER_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_TX_OVER : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_TX_OVER_UNION;
#endif
#define SOC_ISP_I2C_CLR_TX_OVER_CLR_TX_OVER_START (0)
#define SOC_ISP_I2C_CLR_TX_OVER_CLR_TX_OVER_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_RD_REQ : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_RD_REQ_UNION;
#endif
#define SOC_ISP_I2C_CLR_RD_REQ_CLR_RD_REQ_START (0)
#define SOC_ISP_I2C_CLR_RD_REQ_CLR_RD_REQ_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_TX_ABRT : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_TX_ABRT_UNION;
#endif
#define SOC_ISP_I2C_CLR_TX_ABRT_CLR_TX_ABRT_START (0)
#define SOC_ISP_I2C_CLR_TX_ABRT_CLR_TX_ABRT_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_RX_DONE : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_RX_DONE_UNION;
#endif
#define SOC_ISP_I2C_CLR_RX_DONE_CLR_RX_DONE_START (0)
#define SOC_ISP_I2C_CLR_RX_DONE_CLR_RX_DONE_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_ACTIVITY : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_ACTIVITY_UNION;
#endif
#define SOC_ISP_I2C_CLR_ACTIVITY_CLR_ACTIVITY_START (0)
#define SOC_ISP_I2C_CLR_ACTIVITY_CLR_ACTIVITY_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_STOP_DET : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLK_STOP_DET_UNION;
#endif
#define SOC_ISP_I2C_CLK_STOP_DET_CLR_STOP_DET_START (0)
#define SOC_ISP_I2C_CLK_STOP_DET_CLR_STOP_DET_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_START_DET : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_START_DET_UNION;
#endif
#define SOC_ISP_I2C_CLR_START_DET_CLR_START_DET_START (0)
#define SOC_ISP_I2C_CLR_START_DET_CLR_START_DET_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_GEN_CALL : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_GEN_CALL_UNION;
#endif
#define SOC_ISP_I2C_CLR_GEN_CALL_CLR_GEN_CALL_START (0)
#define SOC_ISP_I2C_CLR_GEN_CALL_CLR_GEN_CALL_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ENABLE : 1;
        unsigned int ABORT : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_I2C_ENABLE_UNION;
#endif
#define SOC_ISP_I2C_ENABLE_ENABLE_START (0)
#define SOC_ISP_I2C_ENABLE_ENABLE_END (0)
#define SOC_ISP_I2C_ENABLE_ABORT_START (1)
#define SOC_ISP_I2C_ENABLE_ABORT_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACTIVITY : 1;
        unsigned int TFNF : 1;
        unsigned int TFE : 1;
        unsigned int RFNE : 1;
        unsigned int RFF : 1;
        unsigned int MST_ACTIVITY : 1;
        unsigned int SLV_ACTIVITY : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_ISP_I2C_STATUS_UNION;
#endif
#define SOC_ISP_I2C_STATUS_ACTIVITY_START (0)
#define SOC_ISP_I2C_STATUS_ACTIVITY_END (0)
#define SOC_ISP_I2C_STATUS_TFNF_START (1)
#define SOC_ISP_I2C_STATUS_TFNF_END (1)
#define SOC_ISP_I2C_STATUS_TFE_START (2)
#define SOC_ISP_I2C_STATUS_TFE_END (2)
#define SOC_ISP_I2C_STATUS_RFNE_START (3)
#define SOC_ISP_I2C_STATUS_RFNE_END (3)
#define SOC_ISP_I2C_STATUS_RFF_START (4)
#define SOC_ISP_I2C_STATUS_RFF_END (4)
#define SOC_ISP_I2C_STATUS_MST_ACTIVITY_START (5)
#define SOC_ISP_I2C_STATUS_MST_ACTIVITY_END (5)
#define SOC_ISP_I2C_STATUS_SLV_ACTIVITY_START (6)
#define SOC_ISP_I2C_STATUS_SLV_ACTIVITY_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TXFLR : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_I2C_TXFLR_UNION;
#endif
#define SOC_ISP_I2C_TXFLR_TXFLR_START (0)
#define SOC_ISP_I2C_TXFLR_TXFLR_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RXFLR : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_I2C_RXFLR_UNION;
#endif
#define SOC_ISP_I2C_RXFLR_RXFLR_START (0)
#define SOC_ISP_I2C_RXFLR_RXFLR_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_SDA_TX_HOLD : 16;
        unsigned int IC_SDA_RX_HOLD : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_I2C_SDA_HOLD_UNION;
#endif
#define SOC_ISP_I2C_SDA_HOLD_IC_SDA_TX_HOLD_START (0)
#define SOC_ISP_I2C_SDA_HOLD_IC_SDA_TX_HOLD_END (15)
#define SOC_ISP_I2C_SDA_HOLD_IC_SDA_RX_HOLD_START (16)
#define SOC_ISP_I2C_SDA_HOLD_IC_SDA_RX_HOLD_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ABRT_7B_ADDR_NOACK : 1;
        unsigned int ABRT_10ADDR1_NOACK : 1;
        unsigned int ABRT_10ADDR2_NOACK : 1;
        unsigned int ABRT_TXDATA_NOACK : 1;
        unsigned int ABRT_GCALL_NOACK : 1;
        unsigned int ABRT_GCALL_READ : 1;
        unsigned int ABRT_HS_ACKDET : 1;
        unsigned int ABRT_SBYTE_ACKDET : 1;
        unsigned int ABRT_HS_NORSTRT : 1;
        unsigned int ABRT_SBYTE_NORSTRT : 1;
        unsigned int ABRT_10B_RD_NORSTRT : 1;
        unsigned int ABRT_MASTER_DIS : 1;
        unsigned int ARB_LOST : 1;
        unsigned int ABRT_SLVFLUSH_TXFIFO : 1;
        unsigned int ABRT_SLV_ARBLOST : 1;
        unsigned int ABRT_SLVRD_INTX : 1;
        unsigned int ABRT_USER_ABRT : 1;
        unsigned int reserved : 7;
        unsigned int TX_FLUSH_CNT : 8;
    } reg;
} SOC_ISP_I2C_TX_ABRT_SOURCE_UNION;
#endif
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_START (0)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_END (0)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_START (1)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_END (1)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_START (2)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_END (2)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_START (3)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_END (3)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_START (4)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_END (4)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_START (5)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_END (5)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_START (6)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_END (6)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_START (7)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_END (7)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_START (8)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_END (8)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_START (9)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT_END (9)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_START (10)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT_END (10)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_START (11)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_MASTER_DIS_END (11)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ARB_LOST_START (12)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ARB_LOST_END (12)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_START (13)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_END (13)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_START (14)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_END (14)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_START (15)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_END (15)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_USER_ABRT_START (16)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_ABRT_USER_ABRT_END (16)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_START (24)
#define SOC_ISP_I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int NACK : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_SLV_DATA_NACK_ONLY_UNION;
#endif
#define SOC_ISP_I2C_SLV_DATA_NACK_ONLY_NACK_START (0)
#define SOC_ISP_I2C_SLV_DATA_NACK_ONLY_NACK_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RDMAE : 1;
        unsigned int TDMAE : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_I2C_DMA_CR_UNION;
#endif
#define SOC_ISP_I2C_DMA_CR_RDMAE_START (0)
#define SOC_ISP_I2C_DMA_CR_RDMAE_END (0)
#define SOC_ISP_I2C_DMA_CR_TDMAE_START (1)
#define SOC_ISP_I2C_DMA_CR_TDMAE_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DMATDL : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_I2C_DMA_TDLR_UNION;
#endif
#define SOC_ISP_I2C_DMA_TDLR_DMATDL_START (0)
#define SOC_ISP_I2C_DMA_TDLR_DMATDL_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DMARDL : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_I2C_DMA_RDLR_UNION;
#endif
#define SOC_ISP_I2C_DMA_RDLR_DMARDL_START (0)
#define SOC_ISP_I2C_DMA_RDLR_DMARDL_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SDA_SETUP : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_I2C_SDA_SETUP_UNION;
#endif
#define SOC_ISP_I2C_SDA_SETUP_SDA_SETUP_START (0)
#define SOC_ISP_I2C_SDA_SETUP_SDA_SETUP_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ACK_GEN_CALL : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_ACK_GENERAL_CALL_UNION;
#endif
#define SOC_ISP_I2C_ACK_GENERAL_CALL_ACK_GEN_CALL_START (0)
#define SOC_ISP_I2C_ACK_GENERAL_CALL_ACK_GEN_CALL_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_EN : 1;
        unsigned int SLV_DISABLED_WHIL&#10;E_BUSY : 1;
        unsigned int SLV_RX_DATA_LOST : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_I2C_ENABLE_STATUS_UNION;
#endif
#define SOC_ISP_I2C_ENABLE_STATUS_IC_EN_START (0)
#define SOC_ISP_I2C_ENABLE_STATUS_IC_EN_END (0)
#define SOC_ISP_I2C_ENABLE_STATUS_SLV_DISABLED_WHIL &#10;E_BUSY_START (1)
#define SOC_ISP_I2C_ENABLE_STATUS_SLV_DISABLED_WHIL &#10;E_BUSY_END (1)
#define SOC_ISP_I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_START (2)
#define SOC_ISP_I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_FS_SPKLEN : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_I2C_FS_SPKLEN_UNION;
#endif
#define SOC_ISP_I2C_FS_SPKLEN_IC_FS_SPKLEN_START (0)
#define SOC_ISP_I2C_FS_SPKLEN_IC_FS_SPKLEN_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_HS_SPKLEN : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_I2C_HS_SPKLEN_UNION;
#endif
#define SOC_ISP_I2C_HS_SPKLEN_IC_HS_SPKLEN_START (0)
#define SOC_ISP_I2C_HS_SPKLEN_IC_HS_SPKLEN_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CLR_RESTART_DET : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_I2C_CLR_RESTART_DET_UNION;
#endif
#define SOC_ISP_I2C_CLR_RESTART_DET_CLR_RESTART_DET_START (0)
#define SOC_ISP_I2C_CLR_RESTART_DET_CLR_RESTART_DET_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int APB_DATA_WIDTH : 2;
        unsigned int MAX_SPEED_MODE : 2;
        unsigned int HC_COUNT_VALUES : 1;
        unsigned int INTR_IO : 1;
        unsigned int HAS_DMA : 1;
        unsigned int ADD_ENCODED_PARAMS : 1;
        unsigned int RX_BUFFER_DEPTH : 8;
        unsigned int TX_BUFFER_DEPTH : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_I2C_COMP_PARAM_1_UNION;
#endif
#define SOC_ISP_I2C_COMP_PARAM_1_APB_DATA_WIDTH_START (0)
#define SOC_ISP_I2C_COMP_PARAM_1_APB_DATA_WIDTH_END (1)
#define SOC_ISP_I2C_COMP_PARAM_1_MAX_SPEED_MODE_START (2)
#define SOC_ISP_I2C_COMP_PARAM_1_MAX_SPEED_MODE_END (3)
#define SOC_ISP_I2C_COMP_PARAM_1_HC_COUNT_VALUES_START (4)
#define SOC_ISP_I2C_COMP_PARAM_1_HC_COUNT_VALUES_END (4)
#define SOC_ISP_I2C_COMP_PARAM_1_INTR_IO_START (5)
#define SOC_ISP_I2C_COMP_PARAM_1_INTR_IO_END (5)
#define SOC_ISP_I2C_COMP_PARAM_1_HAS_DMA_START (6)
#define SOC_ISP_I2C_COMP_PARAM_1_HAS_DMA_END (6)
#define SOC_ISP_I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_START (7)
#define SOC_ISP_I2C_COMP_PARAM_1_ADD_ENCODED_PARAMS_END (7)
#define SOC_ISP_I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_START (8)
#define SOC_ISP_I2C_COMP_PARAM_1_RX_BUFFER_DEPTH_END (15)
#define SOC_ISP_I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_START (16)
#define SOC_ISP_I2C_COMP_PARAM_1_TX_BUFFER_DEPTH_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_COMP_VERSION : 32;
    } reg;
} SOC_ISP_I2C_COMP_VERSION_UNION;
#endif
#define SOC_ISP_I2C_COMP_VERSION_IC_COMP_VERSION_START (0)
#define SOC_ISP_I2C_COMP_VERSION_IC_COMP_VERSION_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IC_COMP_TYPE : 32;
    } reg;
} SOC_ISP_I2C_COMP_TYPE_UNION;
#endif
#define SOC_ISP_I2C_COMP_TYPE_IC_COMP_TYPE_START (0)
#define SOC_ISP_I2C_COMP_TYPE_IC_COMP_TYPE_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
