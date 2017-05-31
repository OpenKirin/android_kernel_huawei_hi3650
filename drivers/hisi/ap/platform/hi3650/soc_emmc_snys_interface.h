#ifndef __SOC_EMMC_SNYS_INTERFACE_H__
#define __SOC_EMMC_SNYS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_EMMC_SNYS_CTRL_ADDR(base) ((base) + (0x000))
#define SOC_EMMC_SNYS_CLKDIV_ADDR(base) ((base) + (0x008))
#define SOC_EMMC_SNYS_CLKENA_ADDR(base) ((base) + (0x010))
#define SOC_EMMC_SNYS_TMOUT_ADDR(base) ((base) + (0x014))
#define SOC_EMMC_SNYS_CTYPE_ADDR(base) ((base) + (0x018))
#define SOC_EMMC_SNYS_BLKSIZ_ADDR(base) ((base) + (0x01C))
#define SOC_EMMC_SNYS_BYTCNT_ADDR(base) ((base) + (0x020))
#define SOC_EMMC_SNYS_INTMASK_ADDR(base) ((base) + (0x024))
#define SOC_EMMC_SNYS_CMDARG_ADDR(base) ((base) + (0x028))
#define SOC_EMMC_SNYS_CMD_ADDR(base) ((base) + (0x02C))
#define SOC_EMMC_SNYS_RESP0_ADDR(base) ((base) + (0x030))
#define SOC_EMMC_SNYS_RESP1_ADDR(base) ((base) + (0x034))
#define SOC_EMMC_SNYS_RESP2_ADDR(base) ((base) + (0x038))
#define SOC_EMMC_SNYS_RESP3_ADDR(base) ((base) + (0x03C))
#define SOC_EMMC_SNYS_MINTSTS_ADDR(base) ((base) + (0x040))
#define SOC_EMMC_SNYS_RINTSTS_ADDR(base) ((base) + (0x044))
#define SOC_EMMC_SNYS_STATUS_ADDR(base) ((base) + (0x048))
#define SOC_EMMC_SNYS_FIFOTH_ADDR(base) ((base) + (0x04C))
#define SOC_EMMC_SNYS_GPIO_ADDR(base) ((base) + (0x058))
#define SOC_EMMC_SNYS_TCBCNT_ADDR(base) ((base) + (0x05C))
#define SOC_EMMC_SNYS_TTBCNT_ADDR(base) ((base) + (0x060))
#define SOC_EMMC_SNYS_USRID_ADDR(base) ((base) + (0x068))
#define SOC_EMMC_SNYS_VERID_ADDR(base) ((base) + (0x06C))
#define SOC_EMMC_SNYS_HCON_ADDR(base) ((base) + (0x070))
#define SOC_EMMC_SNYS_UHS_REG_ADDR(base) ((base) + (0x074))
#define SOC_EMMC_SNYS_BMOD_ADDR(base) ((base) + (0x080))
#define SOC_EMMC_SNYS_PLDMND_ADDR(base) ((base) + (0x084))
#define SOC_EMMC_SNYS_DBADDR_ADDR(base) ((base) + (0x088))
#define SOC_EMMC_SNYS_IDSTS_ADDR(base) ((base) + (0x08C))
#define SOC_EMMC_SNYS_IDINTEN_ADDR(base) ((base) + (0x090))
#define SOC_EMMC_SNYS_DSCADDR_ADDR(base) ((base) + (0x094))
#define SOC_EMMC_SNYS_BUFADDR_ADDR(base) ((base) + (0x098))
#define SOC_EMMC_SNYS_CARDTHRCTL_ADDR(base) ((base) + (0x100))
#define SOC_EMMC_SNYS_UHS_REG_EXT_ADDR(base) ((base) + (0x108))
#define SOC_EMMC_SNYS_EMMC_DDR_REG_ADDR(base) ((base) + (0x10C))
#define SOC_EMMC_SNYS_ENABLE_SHIFT_ADDR(base) ((base) + (0x110))
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_ADDR(base) ((base) + (0x400))
#define SOC_EMMC_SNYS_DLL_CFG1_ADDR(base) ((base) + (0x404))
#define SOC_EMMC_SNYS_DLL_CFG2_ADDR(base) ((base) + (0x408))
#define SOC_EMMC_SNYS_DLL_DEBUG1_ADDR(base) ((base) + (0x40C))
#define SOC_EMMC_SNYS_DLL_DEBUG2_ADDR(base) ((base) + (0x410))
#define SOC_EMMC_SNYS_OSC_CFG_ADDR(base) ((base) + (0x414))
#define SOC_EMMC_SNYS_BMOD_DMA_ADDR(base) ((base) + (0x480))
#define SOC_EMMC_SNYS_PLDMND_DMA_ADDR(base) ((base) + (0x0484))
#define SOC_EMMC_SNYS_DBADDR_DMA_ADDR(base) ((base) + (0x0488))
#define SOC_EMMC_SNYS_IDSTS_DMA_ADDR(base) ((base) + (0x048C))
#define SOC_EMMC_SNYS_IDINTEN_DMA_ADDR(base) ((base) + (0x0490))
#define SOC_EMMC_SNYS_DSCADDR_DMA_ADDR(base) ((base) + (0x0494))
#define SOC_EMMC_SNYS_BUFADDR_DMA_ADDR(base) ((base) + (0x0498))
#define SOC_EMMC_SNYS_DMA_CFG_ADDR(base) ((base) + (0x04B0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int controller_reset : 1;
        unsigned int fifo_reset : 1;
        unsigned int dma_reset : 1;
        unsigned int reserved_0 : 1;
        unsigned int int_enable : 1;
        unsigned int dma_enable : 1;
        unsigned int read_wait : 1;
        unsigned int send_irq_response : 1;
        unsigned int abort_read_data : 1;
        unsigned int reserved_1 : 16;
        unsigned int use_internal_dmac : 1;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_EMMC_SNYS_CTRL_UNION;
#endif
#define SOC_EMMC_SNYS_CTRL_controller_reset_START (0)
#define SOC_EMMC_SNYS_CTRL_controller_reset_END (0)
#define SOC_EMMC_SNYS_CTRL_fifo_reset_START (1)
#define SOC_EMMC_SNYS_CTRL_fifo_reset_END (1)
#define SOC_EMMC_SNYS_CTRL_dma_reset_START (2)
#define SOC_EMMC_SNYS_CTRL_dma_reset_END (2)
#define SOC_EMMC_SNYS_CTRL_int_enable_START (4)
#define SOC_EMMC_SNYS_CTRL_int_enable_END (4)
#define SOC_EMMC_SNYS_CTRL_dma_enable_START (5)
#define SOC_EMMC_SNYS_CTRL_dma_enable_END (5)
#define SOC_EMMC_SNYS_CTRL_read_wait_START (6)
#define SOC_EMMC_SNYS_CTRL_read_wait_END (6)
#define SOC_EMMC_SNYS_CTRL_send_irq_response_START (7)
#define SOC_EMMC_SNYS_CTRL_send_irq_response_END (7)
#define SOC_EMMC_SNYS_CTRL_abort_read_data_START (8)
#define SOC_EMMC_SNYS_CTRL_abort_read_data_END (8)
#define SOC_EMMC_SNYS_CTRL_use_internal_dmac_START (25)
#define SOC_EMMC_SNYS_CTRL_use_internal_dmac_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_divider0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_EMMC_SNYS_CLKDIV_UNION;
#endif
#define SOC_EMMC_SNYS_CLKDIV_clk_divider0_START (0)
#define SOC_EMMC_SNYS_CLKDIV_clk_divider0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cclk_enable : 1;
        unsigned int reserved_0 : 15;
        unsigned int cclk_low_power : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_EMMC_SNYS_CLKENA_UNION;
#endif
#define SOC_EMMC_SNYS_CLKENA_cclk_enable_START (0)
#define SOC_EMMC_SNYS_CLKENA_cclk_enable_END (0)
#define SOC_EMMC_SNYS_CLKENA_cclk_low_power_START (16)
#define SOC_EMMC_SNYS_CLKENA_cclk_low_power_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int response_timeout : 8;
        unsigned int data_timeout : 24;
    } reg;
} SOC_EMMC_SNYS_TMOUT_UNION;
#endif
#define SOC_EMMC_SNYS_TMOUT_response_timeout_START (0)
#define SOC_EMMC_SNYS_TMOUT_response_timeout_END (7)
#define SOC_EMMC_SNYS_TMOUT_data_timeout_START (8)
#define SOC_EMMC_SNYS_TMOUT_data_timeout_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int card_width4 : 1;
        unsigned int reserved_0 : 15;
        unsigned int card_width8 : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_EMMC_SNYS_CTYPE_UNION;
#endif
#define SOC_EMMC_SNYS_CTYPE_card_width4_START (0)
#define SOC_EMMC_SNYS_CTYPE_card_width4_END (0)
#define SOC_EMMC_SNYS_CTYPE_card_width8_START (16)
#define SOC_EMMC_SNYS_CTYPE_card_width8_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int block_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_EMMC_SNYS_BLKSIZ_UNION;
#endif
#define SOC_EMMC_SNYS_BLKSIZ_block_size_START (0)
#define SOC_EMMC_SNYS_BLKSIZ_block_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int byte_count : 32;
    } reg;
} SOC_EMMC_SNYS_BYTCNT_UNION;
#endif
#define SOC_EMMC_SNYS_BYTCNT_byte_count_START (0)
#define SOC_EMMC_SNYS_BYTCNT_byte_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mask : 16;
        unsigned int sdio_int_mask : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_EMMC_SNYS_INTMASK_UNION;
#endif
#define SOC_EMMC_SNYS_INTMASK_int_mask_START (0)
#define SOC_EMMC_SNYS_INTMASK_int_mask_END (15)
#define SOC_EMMC_SNYS_INTMASK_sdio_int_mask_START (16)
#define SOC_EMMC_SNYS_INTMASK_sdio_int_mask_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_arg : 32;
    } reg;
} SOC_EMMC_SNYS_CMDARG_UNION;
#endif
#define SOC_EMMC_SNYS_CMDARG_cmd_arg_START (0)
#define SOC_EMMC_SNYS_CMDARG_cmd_arg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_index : 6;
        unsigned int response_expect : 1;
        unsigned int response_length : 1;
        unsigned int check_response_crc : 1;
        unsigned int data_expected : 1;
        unsigned int read_write : 1;
        unsigned int transfer_mode : 1;
        unsigned int send_auto_stop : 1;
        unsigned int wait_prvdata_complete : 1;
        unsigned int stop_abort_cmd : 1;
        unsigned int send_initialization : 1;
        unsigned int reserved_0 : 5;
        unsigned int update_clock_registers_only : 1;
        unsigned int reserved_1 : 2;
        unsigned int enable_boot : 1;
        unsigned int expect_boot_ack : 1;
        unsigned int disable_boot : 1;
        unsigned int boot_mode : 1;
        unsigned int volt_switch : 1;
        unsigned int use_hold_reg : 1;
        unsigned int reserved_2 : 1;
        unsigned int start_cmd : 1;
    } reg;
} SOC_EMMC_SNYS_CMD_UNION;
#endif
#define SOC_EMMC_SNYS_CMD_cmd_index_START (0)
#define SOC_EMMC_SNYS_CMD_cmd_index_END (5)
#define SOC_EMMC_SNYS_CMD_response_expect_START (6)
#define SOC_EMMC_SNYS_CMD_response_expect_END (6)
#define SOC_EMMC_SNYS_CMD_response_length_START (7)
#define SOC_EMMC_SNYS_CMD_response_length_END (7)
#define SOC_EMMC_SNYS_CMD_check_response_crc_START (8)
#define SOC_EMMC_SNYS_CMD_check_response_crc_END (8)
#define SOC_EMMC_SNYS_CMD_data_expected_START (9)
#define SOC_EMMC_SNYS_CMD_data_expected_END (9)
#define SOC_EMMC_SNYS_CMD_read_write_START (10)
#define SOC_EMMC_SNYS_CMD_read_write_END (10)
#define SOC_EMMC_SNYS_CMD_transfer_mode_START (11)
#define SOC_EMMC_SNYS_CMD_transfer_mode_END (11)
#define SOC_EMMC_SNYS_CMD_send_auto_stop_START (12)
#define SOC_EMMC_SNYS_CMD_send_auto_stop_END (12)
#define SOC_EMMC_SNYS_CMD_wait_prvdata_complete_START (13)
#define SOC_EMMC_SNYS_CMD_wait_prvdata_complete_END (13)
#define SOC_EMMC_SNYS_CMD_stop_abort_cmd_START (14)
#define SOC_EMMC_SNYS_CMD_stop_abort_cmd_END (14)
#define SOC_EMMC_SNYS_CMD_send_initialization_START (15)
#define SOC_EMMC_SNYS_CMD_send_initialization_END (15)
#define SOC_EMMC_SNYS_CMD_update_clock_registers_only_START (21)
#define SOC_EMMC_SNYS_CMD_update_clock_registers_only_END (21)
#define SOC_EMMC_SNYS_CMD_enable_boot_START (24)
#define SOC_EMMC_SNYS_CMD_enable_boot_END (24)
#define SOC_EMMC_SNYS_CMD_expect_boot_ack_START (25)
#define SOC_EMMC_SNYS_CMD_expect_boot_ack_END (25)
#define SOC_EMMC_SNYS_CMD_disable_boot_START (26)
#define SOC_EMMC_SNYS_CMD_disable_boot_END (26)
#define SOC_EMMC_SNYS_CMD_boot_mode_START (27)
#define SOC_EMMC_SNYS_CMD_boot_mode_END (27)
#define SOC_EMMC_SNYS_CMD_volt_switch_START (28)
#define SOC_EMMC_SNYS_CMD_volt_switch_END (28)
#define SOC_EMMC_SNYS_CMD_use_hold_reg_START (29)
#define SOC_EMMC_SNYS_CMD_use_hold_reg_END (29)
#define SOC_EMMC_SNYS_CMD_start_cmd_START (31)
#define SOC_EMMC_SNYS_CMD_start_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int resp0 : 32;
    } reg;
} SOC_EMMC_SNYS_RESP0_UNION;
#endif
#define SOC_EMMC_SNYS_RESP0_resp0_START (0)
#define SOC_EMMC_SNYS_RESP0_resp0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int resp1 : 32;
    } reg;
} SOC_EMMC_SNYS_RESP1_UNION;
#endif
#define SOC_EMMC_SNYS_RESP1_resp1_START (0)
#define SOC_EMMC_SNYS_RESP1_resp1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int resp2 : 32;
    } reg;
} SOC_EMMC_SNYS_RESP2_UNION;
#endif
#define SOC_EMMC_SNYS_RESP2_resp2_START (0)
#define SOC_EMMC_SNYS_RESP2_resp2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int resp3 : 32;
    } reg;
} SOC_EMMC_SNYS_RESP3_UNION;
#endif
#define SOC_EMMC_SNYS_RESP3_resp3_START (0)
#define SOC_EMMC_SNYS_RESP3_resp3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_status : 16;
        unsigned int sdio_interrupt : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_EMMC_SNYS_MINTSTS_UNION;
#endif
#define SOC_EMMC_SNYS_MINTSTS_int_status_START (0)
#define SOC_EMMC_SNYS_MINTSTS_int_status_END (15)
#define SOC_EMMC_SNYS_MINTSTS_sdio_interrupt_START (16)
#define SOC_EMMC_SNYS_MINTSTS_sdio_interrupt_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_status : 16;
        unsigned int sdio_interrupt : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_EMMC_SNYS_RINTSTS_UNION;
#endif
#define SOC_EMMC_SNYS_RINTSTS_int_status_START (0)
#define SOC_EMMC_SNYS_RINTSTS_int_status_END (15)
#define SOC_EMMC_SNYS_RINTSTS_sdio_interrupt_START (16)
#define SOC_EMMC_SNYS_RINTSTS_sdio_interrupt_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fifo_rx_watermark : 1;
        unsigned int fifo_tx_watermark : 1;
        unsigned int fifo_empty : 1;
        unsigned int fifo_full : 1;
        unsigned int cmd_fsm_state : 4;
        unsigned int data_3_status : 1;
        unsigned int data_busy : 1;
        unsigned int data_state_mc_busy : 1;
        unsigned int response_index : 6;
        unsigned int fifo_count : 13;
        unsigned int dma_ack : 1;
        unsigned int dma_req : 1;
    } reg;
} SOC_EMMC_SNYS_STATUS_UNION;
#endif
#define SOC_EMMC_SNYS_STATUS_fifo_rx_watermark_START (0)
#define SOC_EMMC_SNYS_STATUS_fifo_rx_watermark_END (0)
#define SOC_EMMC_SNYS_STATUS_fifo_tx_watermark_START (1)
#define SOC_EMMC_SNYS_STATUS_fifo_tx_watermark_END (1)
#define SOC_EMMC_SNYS_STATUS_fifo_empty_START (2)
#define SOC_EMMC_SNYS_STATUS_fifo_empty_END (2)
#define SOC_EMMC_SNYS_STATUS_fifo_full_START (3)
#define SOC_EMMC_SNYS_STATUS_fifo_full_END (3)
#define SOC_EMMC_SNYS_STATUS_cmd_fsm_state_START (4)
#define SOC_EMMC_SNYS_STATUS_cmd_fsm_state_END (7)
#define SOC_EMMC_SNYS_STATUS_data_3_status_START (8)
#define SOC_EMMC_SNYS_STATUS_data_3_status_END (8)
#define SOC_EMMC_SNYS_STATUS_data_busy_START (9)
#define SOC_EMMC_SNYS_STATUS_data_busy_END (9)
#define SOC_EMMC_SNYS_STATUS_data_state_mc_busy_START (10)
#define SOC_EMMC_SNYS_STATUS_data_state_mc_busy_END (10)
#define SOC_EMMC_SNYS_STATUS_response_index_START (11)
#define SOC_EMMC_SNYS_STATUS_response_index_END (16)
#define SOC_EMMC_SNYS_STATUS_fifo_count_START (17)
#define SOC_EMMC_SNYS_STATUS_fifo_count_END (29)
#define SOC_EMMC_SNYS_STATUS_dma_ack_START (30)
#define SOC_EMMC_SNYS_STATUS_dma_ack_END (30)
#define SOC_EMMC_SNYS_STATUS_dma_req_START (31)
#define SOC_EMMC_SNYS_STATUS_dma_req_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_wmark : 12;
        unsigned int reserved_0 : 4;
        unsigned int rx_wmark : 12;
        unsigned int dw_dma_multiple_transaction_size : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_EMMC_SNYS_FIFOTH_UNION;
#endif
#define SOC_EMMC_SNYS_FIFOTH_tx_wmark_START (0)
#define SOC_EMMC_SNYS_FIFOTH_tx_wmark_END (11)
#define SOC_EMMC_SNYS_FIFOTH_rx_wmark_START (16)
#define SOC_EMMC_SNYS_FIFOTH_rx_wmark_END (27)
#define SOC_EMMC_SNYS_FIFOTH_dw_dma_multiple_transaction_size_START (28)
#define SOC_EMMC_SNYS_FIFOTH_dw_dma_multiple_transaction_size_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int div_cclk : 4;
        unsigned int reserved_1 : 1;
        unsigned int use_delay_sample : 1;
        unsigned int reserved_2 : 2;
        unsigned int enable_cclk : 1;
        unsigned int reserved_3 : 15;
    } reg;
} SOC_EMMC_SNYS_GPIO_UNION;
#endif
#define SOC_EMMC_SNYS_GPIO_div_cclk_START (8)
#define SOC_EMMC_SNYS_GPIO_div_cclk_END (11)
#define SOC_EMMC_SNYS_GPIO_use_delay_sample_START (13)
#define SOC_EMMC_SNYS_GPIO_use_delay_sample_END (13)
#define SOC_EMMC_SNYS_GPIO_enable_cclk_START (16)
#define SOC_EMMC_SNYS_GPIO_enable_cclk_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trans_card_byte_count : 32;
    } reg;
} SOC_EMMC_SNYS_TCBCNT_UNION;
#endif
#define SOC_EMMC_SNYS_TCBCNT_trans_card_byte_count_START (0)
#define SOC_EMMC_SNYS_TCBCNT_trans_card_byte_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trans_fifo_byte_count : 32;
    } reg;
} SOC_EMMC_SNYS_TTBCNT_UNION;
#endif
#define SOC_EMMC_SNYS_TTBCNT_trans_fifo_byte_count_START (0)
#define SOC_EMMC_SNYS_TTBCNT_trans_fifo_byte_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int usrid : 32;
    } reg;
} SOC_EMMC_SNYS_USRID_UNION;
#endif
#define SOC_EMMC_SNYS_USRID_usrid_START (0)
#define SOC_EMMC_SNYS_USRID_usrid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int verid : 32;
    } reg;
} SOC_EMMC_SNYS_VERID_UNION;
#endif
#define SOC_EMMC_SNYS_VERID_verid_START (0)
#define SOC_EMMC_SNYS_VERID_verid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hcon : 32;
    } reg;
} SOC_EMMC_SNYS_HCON_UNION;
#endif
#define SOC_EMMC_SNYS_HCON_hcon_START (0)
#define SOC_EMMC_SNYS_HCON_hcon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int ddr_reg : 1;
        unsigned int reserved_1: 15;
    } reg;
} SOC_EMMC_SNYS_UHS_REG_UNION;
#endif
#define SOC_EMMC_SNYS_UHS_REG_ddr_reg_START (16)
#define SOC_EMMC_SNYS_UHS_REG_ddr_reg_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int swr : 1;
        unsigned int fb : 1;
        unsigned int dsl : 5;
        unsigned int de : 1;
        unsigned int pbl : 3;
        unsigned int reserved : 21;
    } reg;
} SOC_EMMC_SNYS_BMOD_UNION;
#endif
#define SOC_EMMC_SNYS_BMOD_swr_START (0)
#define SOC_EMMC_SNYS_BMOD_swr_END (0)
#define SOC_EMMC_SNYS_BMOD_fb_START (1)
#define SOC_EMMC_SNYS_BMOD_fb_END (1)
#define SOC_EMMC_SNYS_BMOD_dsl_START (2)
#define SOC_EMMC_SNYS_BMOD_dsl_END (6)
#define SOC_EMMC_SNYS_BMOD_de_START (7)
#define SOC_EMMC_SNYS_BMOD_de_END (7)
#define SOC_EMMC_SNYS_BMOD_pbl_START (8)
#define SOC_EMMC_SNYS_BMOD_pbl_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pldmnd : 32;
    } reg;
} SOC_EMMC_SNYS_PLDMND_UNION;
#endif
#define SOC_EMMC_SNYS_PLDMND_pldmnd_START (0)
#define SOC_EMMC_SNYS_PLDMND_pldmnd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sdl : 32;
    } reg;
} SOC_EMMC_SNYS_DBADDR_UNION;
#endif
#define SOC_EMMC_SNYS_DBADDR_sdl_START (0)
#define SOC_EMMC_SNYS_DBADDR_sdl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ti : 1;
        unsigned int ri : 1;
        unsigned int fbe : 1;
        unsigned int reserved_0: 1;
        unsigned int du : 1;
        unsigned int ces : 1;
        unsigned int reserved_1: 2;
        unsigned int nis : 1;
        unsigned int ais : 1;
        unsigned int eb : 3;
        unsigned int fsm : 4;
        unsigned int reserved_2: 15;
    } reg;
} SOC_EMMC_SNYS_IDSTS_UNION;
#endif
#define SOC_EMMC_SNYS_IDSTS_ti_START (0)
#define SOC_EMMC_SNYS_IDSTS_ti_END (0)
#define SOC_EMMC_SNYS_IDSTS_ri_START (1)
#define SOC_EMMC_SNYS_IDSTS_ri_END (1)
#define SOC_EMMC_SNYS_IDSTS_fbe_START (2)
#define SOC_EMMC_SNYS_IDSTS_fbe_END (2)
#define SOC_EMMC_SNYS_IDSTS_du_START (4)
#define SOC_EMMC_SNYS_IDSTS_du_END (4)
#define SOC_EMMC_SNYS_IDSTS_ces_START (5)
#define SOC_EMMC_SNYS_IDSTS_ces_END (5)
#define SOC_EMMC_SNYS_IDSTS_nis_START (8)
#define SOC_EMMC_SNYS_IDSTS_nis_END (8)
#define SOC_EMMC_SNYS_IDSTS_ais_START (9)
#define SOC_EMMC_SNYS_IDSTS_ais_END (9)
#define SOC_EMMC_SNYS_IDSTS_eb_START (10)
#define SOC_EMMC_SNYS_IDSTS_eb_END (12)
#define SOC_EMMC_SNYS_IDSTS_fsm_START (13)
#define SOC_EMMC_SNYS_IDSTS_fsm_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ti : 1;
        unsigned int ri : 1;
        unsigned int fbe : 1;
        unsigned int reserved_0: 1;
        unsigned int du : 1;
        unsigned int ces : 1;
        unsigned int reserved_1: 2;
        unsigned int ni : 1;
        unsigned int ai : 1;
        unsigned int reserved_2: 22;
    } reg;
} SOC_EMMC_SNYS_IDINTEN_UNION;
#endif
#define SOC_EMMC_SNYS_IDINTEN_ti_START (0)
#define SOC_EMMC_SNYS_IDINTEN_ti_END (0)
#define SOC_EMMC_SNYS_IDINTEN_ri_START (1)
#define SOC_EMMC_SNYS_IDINTEN_ri_END (1)
#define SOC_EMMC_SNYS_IDINTEN_fbe_START (2)
#define SOC_EMMC_SNYS_IDINTEN_fbe_END (2)
#define SOC_EMMC_SNYS_IDINTEN_du_START (4)
#define SOC_EMMC_SNYS_IDINTEN_du_END (4)
#define SOC_EMMC_SNYS_IDINTEN_ces_START (5)
#define SOC_EMMC_SNYS_IDINTEN_ces_END (5)
#define SOC_EMMC_SNYS_IDINTEN_ni_START (8)
#define SOC_EMMC_SNYS_IDINTEN_ni_END (8)
#define SOC_EMMC_SNYS_IDINTEN_ai_START (9)
#define SOC_EMMC_SNYS_IDINTEN_ai_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hda : 32;
    } reg;
} SOC_EMMC_SNYS_DSCADDR_UNION;
#endif
#define SOC_EMMC_SNYS_DSCADDR_hda_START (0)
#define SOC_EMMC_SNYS_DSCADDR_hda_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hba : 32;
    } reg;
} SOC_EMMC_SNYS_BUFADDR_UNION;
#endif
#define SOC_EMMC_SNYS_BUFADDR_hba_START (0)
#define SOC_EMMC_SNYS_BUFADDR_hba_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int card_rd_thr_en : 1;
        unsigned int bsy_clr_int_en : 1;
        unsigned int reserved_0 : 14;
        unsigned int card_rd_threshhold : 11;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_EMMC_SNYS_CARDTHRCTL_UNION;
#endif
#define SOC_EMMC_SNYS_CARDTHRCTL_card_rd_thr_en_START (0)
#define SOC_EMMC_SNYS_CARDTHRCTL_card_rd_thr_en_END (0)
#define SOC_EMMC_SNYS_CARDTHRCTL_bsy_clr_int_en_START (1)
#define SOC_EMMC_SNYS_CARDTHRCTL_bsy_clr_int_en_END (1)
#define SOC_EMMC_SNYS_CARDTHRCTL_card_rd_threshhold_START (16)
#define SOC_EMMC_SNYS_CARDTHRCTL_card_rd_threshhold_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int clk_smpl_phase_ctrl : 5;
        unsigned int clk_drv_phase_ctrl : 5;
        unsigned int clk_samdly_phase_ctrl : 5;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_EMMC_SNYS_UHS_REG_EXT_UNION;
#endif
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_smpl_phase_ctrl_START (16)
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_smpl_phase_ctrl_END (20)
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_drv_phase_ctrl_START (21)
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_drv_phase_ctrl_END (25)
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_samdly_phase_ctrl_START (26)
#define SOC_EMMC_SNYS_UHS_REG_EXT_clk_samdly_phase_ctrl_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int half_start_bit : 16;
        unsigned int reserved : 15;
        unsigned int hs400_mode : 1;
    } reg;
} SOC_EMMC_SNYS_EMMC_DDR_REG_UNION;
#endif
#define SOC_EMMC_SNYS_EMMC_DDR_REG_half_start_bit_START (0)
#define SOC_EMMC_SNYS_EMMC_DDR_REG_half_start_bit_END (15)
#define SOC_EMMC_SNYS_EMMC_DDR_REG_hs400_mode_START (31)
#define SOC_EMMC_SNYS_EMMC_DDR_REG_hs400_mode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable_shift : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_EMMC_SNYS_ENABLE_SHIFT_UNION;
#endif
#define SOC_EMMC_SNYS_ENABLE_SHIFT_enable_shift_START (0)
#define SOC_EMMC_SNYS_ENABLE_SHIFT_enable_shift_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dqs_ds : 3;
        unsigned int dqs_pd : 1;
        unsigned int dqs_pu : 1;
        unsigned int cmd_ds : 3;
        unsigned int cmd_pd : 1;
        unsigned int cmd_pu : 1;
        unsigned int data_ds : 3;
        unsigned int data_pd : 1;
        unsigned int data_pu : 1;
        unsigned int clk_ds : 3;
        unsigned int clk_pd : 1;
        unsigned int clk_pu : 1;
        unsigned int osc_ds : 3;
        unsigned int osc_pd : 1;
        unsigned int osc_pu : 1;
        unsigned int retention : 1;
        unsigned int reserved : 6;
    } reg;
} SOC_EMMC_SNYS_EMMC1_IO_CFG_UNION;
#endif
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_ds_START (0)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_ds_END (2)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_pd_START (3)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_pd_END (3)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_pu_START (4)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_dqs_pu_END (4)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_ds_START (5)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_ds_END (7)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_pd_START (8)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_pd_END (8)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_pu_START (9)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_cmd_pu_END (9)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_ds_START (10)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_ds_END (12)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_pd_START (13)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_pd_END (13)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_pu_START (14)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_data_pu_END (14)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_ds_START (15)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_ds_END (17)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_pd_START (18)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_pd_END (18)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_pu_START (19)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_clk_pu_END (19)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_ds_START (20)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_ds_END (22)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_pd_START (23)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_pd_END (23)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_pu_START (24)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_osc_pu_END (24)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_retention_START (25)
#define SOC_EMMC_SNYS_EMMC1_IO_CFG_retention_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dll_en : 1;
        unsigned int soft_en : 1;
        unsigned int soft_update : 1;
        unsigned int soft_dly_num : 9;
        unsigned int cfg_lock_range : 11;
        unsigned int cfg_avg_time : 8;
        unsigned int reserved : 1;
    } reg;
} SOC_EMMC_SNYS_DLL_CFG1_UNION;
#endif
#define SOC_EMMC_SNYS_DLL_CFG1_dll_en_START (0)
#define SOC_EMMC_SNYS_DLL_CFG1_dll_en_END (0)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_en_START (1)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_en_END (1)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_update_START (2)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_update_END (2)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_dly_num_START (3)
#define SOC_EMMC_SNYS_DLL_CFG1_soft_dly_num_END (11)
#define SOC_EMMC_SNYS_DLL_CFG1_cfg_lock_range_START (12)
#define SOC_EMMC_SNYS_DLL_CFG1_cfg_lock_range_END (22)
#define SOC_EMMC_SNYS_DLL_CFG1_cfg_avg_time_START (23)
#define SOC_EMMC_SNYS_DLL_CFG1_cfg_avg_time_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_balance_sel0 : 16;
        unsigned int cfg_balance_sel1 : 16;
    } reg;
} SOC_EMMC_SNYS_DLL_CFG2_UNION;
#endif
#define SOC_EMMC_SNYS_DLL_CFG2_cfg_balance_sel0_START (0)
#define SOC_EMMC_SNYS_DLL_CFG2_cfg_balance_sel0_END (15)
#define SOC_EMMC_SNYS_DLL_CFG2_cfg_balance_sel1_START (16)
#define SOC_EMMC_SNYS_DLL_CFG2_cfg_balance_sel1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddll_lock : 1;
        unsigned int dbg_phase : 9;
        unsigned int dbg_dtc_worst : 16;
        unsigned int reserved : 6;
    } reg;
} SOC_EMMC_SNYS_DLL_DEBUG1_UNION;
#endif
#define SOC_EMMC_SNYS_DLL_DEBUG1_ddll_lock_START (0)
#define SOC_EMMC_SNYS_DLL_DEBUG1_ddll_lock_END (0)
#define SOC_EMMC_SNYS_DLL_DEBUG1_dbg_phase_START (1)
#define SOC_EMMC_SNYS_DLL_DEBUG1_dbg_phase_END (9)
#define SOC_EMMC_SNYS_DLL_DEBUG1_dbg_dtc_worst_START (10)
#define SOC_EMMC_SNYS_DLL_DEBUG1_dbg_dtc_worst_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_sum : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_EMMC_SNYS_DLL_DEBUG2_UNION;
#endif
#define SOC_EMMC_SNYS_DLL_DEBUG2_dbg_sum_START (0)
#define SOC_EMMC_SNYS_DLL_DEBUG2_dbg_sum_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int osc_test_en : 1;
        unsigned int osc_ready : 1;
        unsigned int osc_cnt : 8;
        unsigned int test_en : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_EMMC_SNYS_OSC_CFG_UNION;
#endif
#define SOC_EMMC_SNYS_OSC_CFG_osc_test_en_START (0)
#define SOC_EMMC_SNYS_OSC_CFG_osc_test_en_END (0)
#define SOC_EMMC_SNYS_OSC_CFG_osc_ready_START (1)
#define SOC_EMMC_SNYS_OSC_CFG_osc_ready_END (1)
#define SOC_EMMC_SNYS_OSC_CFG_osc_cnt_START (2)
#define SOC_EMMC_SNYS_OSC_CFG_osc_cnt_END (9)
#define SOC_EMMC_SNYS_OSC_CFG_test_en_START (10)
#define SOC_EMMC_SNYS_OSC_CFG_test_en_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sw_reset : 1;
        unsigned int reserved_0 : 6;
        unsigned int dma_enable : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_EMMC_SNYS_BMOD_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_BMOD_DMA_sw_reset_START (0)
#define SOC_EMMC_SNYS_BMOD_DMA_sw_reset_END (0)
#define SOC_EMMC_SNYS_BMOD_DMA_dma_enable_START (7)
#define SOC_EMMC_SNYS_BMOD_DMA_dma_enable_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int poll_cmd : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EMMC_SNYS_PLDMND_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_PLDMND_DMA_poll_cmd_START (0)
#define SOC_EMMC_SNYS_PLDMND_DMA_poll_cmd_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cfg_dsc_addr : 32;
    } reg;
} SOC_EMMC_SNYS_DBADDR_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_DBADDR_DMA_cfg_dsc_addr_START (0)
#define SOC_EMMC_SNYS_DBADDR_DMA_cfg_dsc_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int fbe_intr : 1;
        unsigned int abnormal_abortion : 1;
        unsigned int desc_unavailable : 1;
        unsigned int reserved_1 : 4;
        unsigned int abnormal_intr_sum : 1;
        unsigned int fbe_code : 3;
        unsigned int fsm_state : 4;
        unsigned int gif_state : 2;
        unsigned int reserved_2 : 1;
        unsigned int dma_read_done : 1;
        unsigned int dma_write_done : 1;
        unsigned int reserved_3 : 10;
    } reg;
} SOC_EMMC_SNYS_IDSTS_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_IDSTS_DMA_fbe_intr_START (2)
#define SOC_EMMC_SNYS_IDSTS_DMA_fbe_intr_END (2)
#define SOC_EMMC_SNYS_IDSTS_DMA_abnormal_abortion_START (3)
#define SOC_EMMC_SNYS_IDSTS_DMA_abnormal_abortion_END (3)
#define SOC_EMMC_SNYS_IDSTS_DMA_desc_unavailable_START (4)
#define SOC_EMMC_SNYS_IDSTS_DMA_desc_unavailable_END (4)
#define SOC_EMMC_SNYS_IDSTS_DMA_abnormal_intr_sum_START (9)
#define SOC_EMMC_SNYS_IDSTS_DMA_abnormal_intr_sum_END (9)
#define SOC_EMMC_SNYS_IDSTS_DMA_fbe_code_START (10)
#define SOC_EMMC_SNYS_IDSTS_DMA_fbe_code_END (12)
#define SOC_EMMC_SNYS_IDSTS_DMA_fsm_state_START (13)
#define SOC_EMMC_SNYS_IDSTS_DMA_fsm_state_END (16)
#define SOC_EMMC_SNYS_IDSTS_DMA_gif_state_START (17)
#define SOC_EMMC_SNYS_IDSTS_DMA_gif_state_END (18)
#define SOC_EMMC_SNYS_IDSTS_DMA_dma_read_done_START (20)
#define SOC_EMMC_SNYS_IDSTS_DMA_dma_read_done_END (20)
#define SOC_EMMC_SNYS_IDSTS_DMA_dma_write_done_START (21)
#define SOC_EMMC_SNYS_IDSTS_DMA_dma_write_done_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int fbe_intr_en : 1;
        unsigned int abnormal_abortion_en : 1;
        unsigned int desc_unavailable_en : 1;
        unsigned int reserved_1 : 4;
        unsigned int abnormal_intr_sum_en : 1;
        unsigned int reserved_2 : 10;
        unsigned int dma_read_done_en : 1;
        unsigned int dma_write_done_en : 1;
        unsigned int reserved_3 : 10;
    } reg;
} SOC_EMMC_SNYS_IDINTEN_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_IDINTEN_DMA_fbe_intr_en_START (2)
#define SOC_EMMC_SNYS_IDINTEN_DMA_fbe_intr_en_END (2)
#define SOC_EMMC_SNYS_IDINTEN_DMA_abnormal_abortion_en_START (3)
#define SOC_EMMC_SNYS_IDINTEN_DMA_abnormal_abortion_en_END (3)
#define SOC_EMMC_SNYS_IDINTEN_DMA_desc_unavailable_en_START (4)
#define SOC_EMMC_SNYS_IDINTEN_DMA_desc_unavailable_en_END (4)
#define SOC_EMMC_SNYS_IDINTEN_DMA_abnormal_intr_sum_en_START (9)
#define SOC_EMMC_SNYS_IDINTEN_DMA_abnormal_intr_sum_en_END (9)
#define SOC_EMMC_SNYS_IDINTEN_DMA_dma_read_done_en_START (20)
#define SOC_EMMC_SNYS_IDINTEN_DMA_dma_read_done_en_END (20)
#define SOC_EMMC_SNYS_IDINTEN_DMA_dma_write_done_en_START (21)
#define SOC_EMMC_SNYS_IDINTEN_DMA_dma_write_done_en_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int curr_dsc_addr : 32;
    } reg;
} SOC_EMMC_SNYS_DSCADDR_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_DSCADDR_DMA_curr_dsc_addr_START (0)
#define SOC_EMMC_SNYS_DSCADDR_DMA_curr_dsc_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_buffer_addr : 32;
    } reg;
} SOC_EMMC_SNYS_BUFADDR_DMA_UNION;
#endif
#define SOC_EMMC_SNYS_BUFADDR_DMA_data_buffer_addr_START (0)
#define SOC_EMMC_SNYS_BUFADDR_DMA_data_buffer_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int desc_own_clr_en : 1;
        unsigned int clear_error_abort : 1;
        unsigned int sfifo_reset : 1;
        unsigned int reserved_0 : 25;
        unsigned int fbe_err_type : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_EMMC_SNYS_DMA_CFG_UNION;
#endif
#define SOC_EMMC_SNYS_DMA_CFG_desc_own_clr_en_START (0)
#define SOC_EMMC_SNYS_DMA_CFG_desc_own_clr_en_END (0)
#define SOC_EMMC_SNYS_DMA_CFG_clear_error_abort_START (1)
#define SOC_EMMC_SNYS_DMA_CFG_clear_error_abort_END (1)
#define SOC_EMMC_SNYS_DMA_CFG_sfifo_reset_START (2)
#define SOC_EMMC_SNYS_DMA_CFG_sfifo_reset_END (2)
#define SOC_EMMC_SNYS_DMA_CFG_fbe_err_type_START (28)
#define SOC_EMMC_SNYS_DMA_CFG_fbe_err_type_END (30)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
