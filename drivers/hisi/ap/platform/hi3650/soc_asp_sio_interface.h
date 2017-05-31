#ifndef __SOC_ASP_SIO_INTERFACE_H__
#define __SOC_ASP_SIO_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASP_SIO_SIO_VERSION_ADDR(base) ((base) + (0x03C))
#define SOC_ASP_SIO_SIO_MODE_ADDR(base) ((base) + (0x040))
#define SOC_ASP_SIO_SIO_INTSTATUS_ADDR(base) ((base) + (0x044))
#define SOC_ASP_SIO_SIO_INTCLR_ADDR(base) ((base) + (0x048))
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_ADDR(base) ((base) + (0x04C))
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_ADDR(base) ((base) + (0x050))
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_ADDR(base) ((base) + (0x054))
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_ADDR(base) ((base) + (0x058))
#define SOC_ASP_SIO_SIO_CT_SET_ADDR(base) ((base) + (0x05C))
#define SOC_ASP_SIO_SIO_CT_CLR_ADDR(base) ((base) + (0x060))
#define SOC_ASP_SIO_SIO_RX_STA_ADDR(base) ((base) + (0x068))
#define SOC_ASP_SIO_SIO_TX_STA_ADDR(base) ((base) + (0x06C))
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_ADDR(base) ((base) + (0x078))
#define SOC_ASP_SIO_SIO_I2S_START_POS_ADDR(base) ((base) + (0x07C))
#define SOC_ASP_SIO_I2S_POS_FLAG_ADDR(base) ((base) + (0x080))
#define SOC_ASP_SIO_SIO_SIGNED_EXT_ADDR(base) ((base) + (0x084))
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_ADDR(base) ((base) + (0x088))
#define SOC_ASP_SIO_SIO_INTMASK_ADDR(base) ((base) + (0x08C))
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_ADDR(base) ((base) + (0x0A0))
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_ADDR(base) ((base) + (0x0C0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version : 8;
        unsigned int sio_loop : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_ASP_SIO_SIO_VERSION_UNION;
#endif
#define SOC_ASP_SIO_SIO_VERSION_version_START (0)
#define SOC_ASP_SIO_SIO_VERSION_version_END (7)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_START (8)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio_mode : 1;
        unsigned int pcm_mode : 1;
        unsigned int reserved_0 : 1;
        unsigned int ext_rec_en : 1;
        unsigned int chn_num : 2;
        unsigned int clk_edge : 1;
        unsigned int reserved_1 : 25;
    } reg;
} SOC_ASP_SIO_SIO_MODE_UNION;
#endif
#define SOC_ASP_SIO_SIO_MODE_sio_mode_START (0)
#define SOC_ASP_SIO_SIO_MODE_sio_mode_END (0)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_START (1)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_END (1)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_START (3)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_END (3)
#define SOC_ASP_SIO_SIO_MODE_chn_num_START (4)
#define SOC_ASP_SIO_SIO_MODE_chn_num_END (5)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_START (6)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_SIO_SIO_INTSTATUS_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_START (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_END (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_START (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_END (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_START (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_END (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_START (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_END (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_START (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_END (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_START (5)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_SIO_SIO_INTCLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_START (0)
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_END (0)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_START (1)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_END (1)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_START (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_END (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_START (3)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_END (3)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_START (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_END (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_START (5)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_left_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_right_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_left_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_right_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_fifo_threshold : 4;
        unsigned int rx_fifo_threshold : 4;
        unsigned int tx_data_merge_en : 1;
        unsigned int rx_data_merge_en : 1;
        unsigned int tx_fifo_disable : 1;
        unsigned int rx_fifo_disable : 1;
        unsigned int tx_enable : 1;
        unsigned int rx_enable : 1;
        unsigned int intr_en : 1;
        unsigned int rst_n : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_SIO_SIO_CT_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_START (0)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_END (3)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_START (4)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_END (7)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_START (8)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_END (8)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_START (9)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_END (9)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_START (10)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_END (10)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_START (11)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_END (11)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_START (12)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_END (12)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_START (13)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_END (13)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_START (14)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_END (14)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_START (15)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_fifo_threshold : 4;
        unsigned int rx_fifo_threshold : 4;
        unsigned int tx_data_merge_en : 1;
        unsigned int rx_data_merge_en : 1;
        unsigned int tx_fifo_disable : 1;
        unsigned int rx_fifo_disable : 1;
        unsigned int tx_enable : 1;
        unsigned int rx_enable : 1;
        unsigned int intr_en : 1;
        unsigned int rst_n : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_SIO_SIO_CT_CLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_START (0)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_END (3)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_START (4)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_END (7)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_START (8)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_END (8)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_START (9)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_END (9)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_START (10)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_END (10)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_START (11)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_END (11)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_START (12)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_END (12)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_START (13)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_END (13)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_START (14)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_END (14)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_START (15)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_right_depth : 5;
        unsigned int rx_left_depth : 5;
        unsigned int reserved : 22;
    } reg;
} SOC_ASP_SIO_SIO_RX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_START (0)
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_END (4)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_START (5)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_right_depth : 5;
        unsigned int tx_left_depth : 5;
        unsigned int reserved : 22;
    } reg;
} SOC_ASP_SIO_SIO_TX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_START (0)
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_END (4)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_START (5)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_mode : 3;
        unsigned int rx_mode : 3;
        unsigned int reserved_0: 2;
        unsigned int reserved_1: 24;
    } reg;
} SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_START (0)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_END (2)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_START (3)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start_pos_read : 1;
        unsigned int start_pos_write : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ASP_SIO_SIO_I2S_START_POS_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_START (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_END (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_START (1)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start_pos_read : 1;
        unsigned int start_pos_write : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ASP_SIO_I2S_POS_FLAG_UNION;
#endif
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_START (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_END (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_START (1)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int signed_ext_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_SIO_SIO_SIGNED_EXT_UNION;
#endif
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_START (0)
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merge_on : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_START (0)
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_SIO_SIO_INTMASK_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_START (0)
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_END (0)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_START (1)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_END (1)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_START (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_END (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_START (3)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_END (3)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_START (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_END (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_START (5)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rx_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_data : 32;
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_START (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
