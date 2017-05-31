#ifndef __SOC_EMMC_ARASAN_INTERFACE_H__
#define __SOC_EMMC_ARASAN_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_ADDR(base) ((base) + (0x00))
#define SOC_EMMC_ARASAN_BLOCK_CTRL_ADDR(base) ((base) + (0x04))
#define SOC_EMMC_ARASAN_ARGUMENT1_ADDR(base) ((base) + (0x08))
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_ADDR(base) ((base) + (0x0C))
#define SOC_EMMC_ARASAN_CMD_RES0_ADDR(base) ((base) + (0x10))
#define SOC_EMMC_ARASAN_CMD_RES1_ADDR(base) ((base) + (0x14))
#define SOC_EMMC_ARASAN_CMD_RES2_ADDR(base) ((base) + (0x18))
#define SOC_EMMC_ARASAN_CMD_RES3_ADDR(base) ((base) + (0x1C))
#define SOC_EMMC_ARASAN_BUFFER_DATA_ADDR(base) ((base) + (0x20))
#define SOC_EMMC_ARASAN_PRESENT_STATE_ADDR(base) ((base) + (0x24))
#define SOC_EMMC_ARASAN_HOST_CTRL1_ADDR(base) ((base) + (0x28))
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_ADDR(base) ((base) + (0x2C))
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ADDR(base) ((base) + (0x30))
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_ADDR(base) ((base) + (0x34))
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_ADDR(base) ((base) + (0x38))
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_ADDR(base) ((base) + (0x3C))
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_ADDR(base) ((base) + (0x40))
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ADDR(base) ((base) + (0x44))
#define SOC_EMMC_ARASAN_MAX_CURRENT_ADDR(base) ((base) + (0x48))
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_ADDR(base) ((base) + (0x50))
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_ADDR(base) ((base) + (0x54))
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_ADDR(base) ((base) + (0x58))
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_ADDR(base) ((base) + (0x5C))
#define SOC_EMMC_ARASAN_PRESET_VALUE1_ADDR(base) ((base) + (0x60))
#define SOC_EMMC_ARASAN_PRESET_VALUE2_ADDR(base) ((base) + (0x64))
#define SOC_EMMC_ARASAN_PRESET_VALUE3_ADDR(base) ((base) + (0x68))
#define SOC_EMMC_ARASAN_PRESET_VALUE4_ADDR(base) ((base) + (0x6C))
#define SOC_EMMC_ARASAN_PRESET_VALUE5_ADDR(base) ((base) + (0x74))
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_ADDR(base) ((base) + (0x70))
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_ADDR(base) ((base) + (0x78))
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_ADDR(base) ((base) + (0x200))
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_ADDR(base) ((base) + (0x204))
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_ADDR(base) ((base) + (0x208))
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_ADDR(base) ((base) + (0x20C))
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ADDR(base) ((base) + (0x210))
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_ADDR(base) ((base) + (0x214))
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_ADDR(base) ((base) + (0x218))
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_ADDR(base) ((base) + (0x21C))
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_ADDR(base) ((base) + (0x220))
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_ADDR(base) ((base) + (0x224))
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_ADDR(base) ((base) + (0x228))
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_ADDR(base) ((base) + (0x22C))
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_ADDR(base) ((base) + (0x230))
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_ADDR(base) ((base) + (0x234))
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_ADDR(base) ((base) + (0x238))
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_ADDR(base) ((base) + (0x240))
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_ADDR(base) ((base) + (0x244))
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_ADDR(base) ((base) + (0x248))
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_ADDR(base) ((base) + (0x250))
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_ADDR(base) ((base) + (0x254))
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_ADDR(base) ((base) + (0x258))
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_ADDR(base) ((base) + (0x25C))
#define SOC_EMMC_ARASAN_CORE_CFG0_ADDR(base) ((base) + (0x400))
#define SOC_EMMC_ARASAN_CORE_CFG1_ADDR(base) ((base) + (0x404))
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_ADDR(base) ((base) + (0x408))
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_ADDR(base) ((base) + (0x40C))
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_ADDR(base) ((base) + (0x410))
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_ADDR(base) ((base) + (0x414))
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_ADDR(base) ((base) + (0x418))
#define SOC_EMMC_ARASAN_CORE_CFG2_ADDR(base) ((base) + (0x41C))
#define SOC_EMMC_ARASAN_DEBUG_REG0_ADDR(base) ((base) + (0x420))
#define SOC_EMMC_ARASAN_DEBUG_REG1_ADDR(base) ((base) + (0x424))
#define SOC_EMMC_ARASAN_DEBUG_REG2_ADDR(base) ((base) + (0x428))
#define SOC_EMMC_ARASAN_DEBUG_REG3_ADDR(base) ((base) + (0x42C))
#define SOC_EMMC_ARASAN_PHYCTRL1_ADDR(base) ((base) + (0x430))
#define SOC_EMMC_ARASAN_PHYCTRL2_ADDR(base) ((base) + (0x434))
#define SOC_EMMC_ARASAN_PHYCTRL3_ADDR(base) ((base) + (0x438))
#define SOC_EMMC_ARASAN_PHYCTRL4_ADDR(base) ((base) + (0x43C))
#define SOC_EMMC_ARASAN_PHY_STATUS_ADDR(base) ((base) + (0x440))
#define SOC_EMMC_ARASAN_TEST_CONTROL_ADDR(base) ((base) + (0x444))
#define SOC_EMMC_ARASAN_CORE_CFG3_ADDR(base) ((base) + (0x448))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trans_block_size : 12;
        unsigned int sdma_buffer_size : 3;
        unsigned int reserved : 1;
        unsigned int block_count : 16;
    } reg;
} SOC_EMMC_ARASAN_BLOCK_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_BLOCK_CTRL_trans_block_size_START (0)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_trans_block_size_END (11)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_sdma_buffer_size_START (12)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_sdma_buffer_size_END (14)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_block_count_START (16)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_block_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_argument : 32;
    } reg;
} SOC_EMMC_ARASAN_ARGUMENT1_UNION;
#endif
#define SOC_EMMC_ARASAN_ARGUMENT1_cmd_argument_START (0)
#define SOC_EMMC_ARASAN_ARGUMENT1_cmd_argument_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dma_enable : 1;
        unsigned int block_count_enable : 1;
        unsigned int auto_cmd_enable : 2;
        unsigned int data_trans_direction : 1;
        unsigned int multi_block_select : 1;
        unsigned int reserved_0 : 10;
        unsigned int response_type : 2;
        unsigned int reserved_1 : 1;
        unsigned int cmd_crc_check : 1;
        unsigned int cmd_index_check : 1;
        unsigned int data_present_select : 1;
        unsigned int cmd_type : 2;
        unsigned int cmd_index : 6;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_EMMC_ARASAN_TRANS_CMD_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_dma_enable_START (0)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_dma_enable_END (0)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_block_count_enable_START (1)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_block_count_enable_END (1)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_auto_cmd_enable_START (2)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_auto_cmd_enable_END (3)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_trans_direction_START (4)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_trans_direction_END (4)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_multi_block_select_START (5)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_multi_block_select_END (5)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_response_type_START (16)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_response_type_END (17)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_crc_check_START (19)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_crc_check_END (19)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_check_START (20)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_check_END (20)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_present_select_START (21)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_present_select_END (21)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_type_START (22)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_type_END (23)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_START (24)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_response0 : 32;
    } reg;
} SOC_EMMC_ARASAN_CMD_RES0_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES0_cmd_response0_START (0)
#define SOC_EMMC_ARASAN_CMD_RES0_cmd_response0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_response1 : 32;
    } reg;
} SOC_EMMC_ARASAN_CMD_RES1_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES1_cmd_response1_START (0)
#define SOC_EMMC_ARASAN_CMD_RES1_cmd_response1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_response2 : 32;
    } reg;
} SOC_EMMC_ARASAN_CMD_RES2_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES2_cmd_response2_START (0)
#define SOC_EMMC_ARASAN_CMD_RES2_cmd_response2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_response3 : 32;
    } reg;
} SOC_EMMC_ARASAN_CMD_RES3_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES3_cmd_response3_START (0)
#define SOC_EMMC_ARASAN_CMD_RES3_cmd_response3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffer_data : 32;
    } reg;
} SOC_EMMC_ARASAN_BUFFER_DATA_UNION;
#endif
#define SOC_EMMC_ARASAN_BUFFER_DATA_buffer_data_START (0)
#define SOC_EMMC_ARASAN_BUFFER_DATA_buffer_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_inhibit_cmd : 1;
        unsigned int cmd_inhibit_data : 1;
        unsigned int data_line_active : 1;
        unsigned int retuning_request : 1;
        unsigned int reserved_0 : 4;
        unsigned int write_transfer_active : 1;
        unsigned int read_transfer_active : 1;
        unsigned int buffer_write_enable : 1;
        unsigned int buffer_read_enable : 1;
        unsigned int reserved_1 : 4;
        unsigned int card_inserted : 1;
        unsigned int card_state_stable : 1;
        unsigned int card_detect_level : 1;
        unsigned int write_protect_level : 1;
        unsigned int data3_0_line_level : 4;
        unsigned int cmd_line_level : 1;
        unsigned int data7_4_line_level : 4;
        unsigned int reserved_2 : 3;
    } reg;
} SOC_EMMC_ARASAN_PRESENT_STATE_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_cmd_START (0)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_cmd_END (0)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_data_START (1)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_data_END (1)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data_line_active_START (2)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data_line_active_END (2)
#define SOC_EMMC_ARASAN_PRESENT_STATE_retuning_request_START (3)
#define SOC_EMMC_ARASAN_PRESENT_STATE_retuning_request_END (3)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_transfer_active_START (8)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_transfer_active_END (8)
#define SOC_EMMC_ARASAN_PRESENT_STATE_read_transfer_active_START (9)
#define SOC_EMMC_ARASAN_PRESENT_STATE_read_transfer_active_END (9)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_write_enable_START (10)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_write_enable_END (10)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_read_enable_START (11)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_read_enable_END (11)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_inserted_START (16)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_inserted_END (16)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_state_stable_START (17)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_state_stable_END (17)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_detect_level_START (18)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_detect_level_END (18)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_protect_level_START (19)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_protect_level_END (19)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data3_0_line_level_START (20)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data3_0_line_level_END (23)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_line_level_START (24)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_line_level_END (24)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data7_4_line_level_START (25)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data7_4_line_level_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int led_control : 1;
        unsigned int data_transfer_width : 1;
        unsigned int high_speed_enable : 1;
        unsigned int dma_select : 2;
        unsigned int extended_data_transfer_width : 1;
        unsigned int card_detect_test_level : 1;
        unsigned int card_detect_sig_dect : 1;
        unsigned int sd_bus_power : 1;
        unsigned int sd_bus_voltage_sel : 3;
        unsigned int emmc_devive_hw_rst_n : 1;
        unsigned int reserved_0 : 3;
        unsigned int stop_at_block_gap : 1;
        unsigned int continue_request : 1;
        unsigned int read_wait_control : 1;
        unsigned int intrrup_at_block_gap : 1;
        unsigned int spi_mode : 1;
        unsigned int boot_en : 1;
        unsigned int alt_boot_en : 1;
        unsigned int boot_ack_chk : 1;
        unsigned int wakeup_en_sd_intrrupt : 1;
        unsigned int wakeup_en_sd_instert : 1;
        unsigned int wakeup_en_sd_removal : 1;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_EMMC_ARASAN_HOST_CTRL1_UNION;
#endif
#define SOC_EMMC_ARASAN_HOST_CTRL1_led_control_START (0)
#define SOC_EMMC_ARASAN_HOST_CTRL1_led_control_END (0)
#define SOC_EMMC_ARASAN_HOST_CTRL1_data_transfer_width_START (1)
#define SOC_EMMC_ARASAN_HOST_CTRL1_data_transfer_width_END (1)
#define SOC_EMMC_ARASAN_HOST_CTRL1_high_speed_enable_START (2)
#define SOC_EMMC_ARASAN_HOST_CTRL1_high_speed_enable_END (2)
#define SOC_EMMC_ARASAN_HOST_CTRL1_dma_select_START (3)
#define SOC_EMMC_ARASAN_HOST_CTRL1_dma_select_END (4)
#define SOC_EMMC_ARASAN_HOST_CTRL1_extended_data_transfer_width_START (5)
#define SOC_EMMC_ARASAN_HOST_CTRL1_extended_data_transfer_width_END (5)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_test_level_START (6)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_test_level_END (6)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_sig_dect_START (7)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_sig_dect_END (7)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_power_START (8)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_power_END (8)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_voltage_sel_START (9)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_voltage_sel_END (11)
#define SOC_EMMC_ARASAN_HOST_CTRL1_emmc_devive_hw_rst_n_START (12)
#define SOC_EMMC_ARASAN_HOST_CTRL1_emmc_devive_hw_rst_n_END (12)
#define SOC_EMMC_ARASAN_HOST_CTRL1_stop_at_block_gap_START (16)
#define SOC_EMMC_ARASAN_HOST_CTRL1_stop_at_block_gap_END (16)
#define SOC_EMMC_ARASAN_HOST_CTRL1_continue_request_START (17)
#define SOC_EMMC_ARASAN_HOST_CTRL1_continue_request_END (17)
#define SOC_EMMC_ARASAN_HOST_CTRL1_read_wait_control_START (18)
#define SOC_EMMC_ARASAN_HOST_CTRL1_read_wait_control_END (18)
#define SOC_EMMC_ARASAN_HOST_CTRL1_intrrup_at_block_gap_START (19)
#define SOC_EMMC_ARASAN_HOST_CTRL1_intrrup_at_block_gap_END (19)
#define SOC_EMMC_ARASAN_HOST_CTRL1_spi_mode_START (20)
#define SOC_EMMC_ARASAN_HOST_CTRL1_spi_mode_END (20)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_en_START (21)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_en_END (21)
#define SOC_EMMC_ARASAN_HOST_CTRL1_alt_boot_en_START (22)
#define SOC_EMMC_ARASAN_HOST_CTRL1_alt_boot_en_END (22)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_ack_chk_START (23)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_ack_chk_END (23)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_intrrupt_START (24)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_intrrupt_END (24)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_instert_START (25)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_instert_END (25)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_removal_START (26)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_removal_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int internal_clk_enable : 1;
        unsigned int internal_clk_stable : 1;
        unsigned int sd_clk_en : 1;
        unsigned int reserved_0 : 2;
        unsigned int clock_gen_sel : 1;
        unsigned int upper_bits_sdclk_frq_sel : 2;
        unsigned int clock_freq_sel : 8;
        unsigned int data_timeout_cnt_value : 3;
        unsigned int reserved_1 : 5;
        unsigned int soft_reset_all : 1;
        unsigned int soft_reset_cmdline : 1;
        unsigned int soft_reset_dataline : 1;
        unsigned int reserved_2 : 5;
    } reg;
} SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_enable_START (0)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_enable_END (0)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_stable_START (1)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_stable_END (1)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_sd_clk_en_START (2)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_sd_clk_en_END (2)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_gen_sel_START (5)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_gen_sel_END (5)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_upper_bits_sdclk_frq_sel_START (6)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_upper_bits_sdclk_frq_sel_END (7)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_freq_sel_START (8)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_freq_sel_END (15)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_data_timeout_cnt_value_START (16)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_data_timeout_cnt_value_END (18)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_all_START (24)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_all_END (24)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_cmdline_START (25)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_cmdline_END (25)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_dataline_START (26)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_dataline_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_complete : 1;
        unsigned int transfer_complete : 1;
        unsigned int bloack_gap_event : 1;
        unsigned int dma_imterrupt : 1;
        unsigned int buffer_write_ready : 1;
        unsigned int buffer_read_ready : 1;
        unsigned int card_insertion : 1;
        unsigned int card_removal : 1;
        unsigned int card_interrupt : 1;
        unsigned int int_a : 1;
        unsigned int int_b : 1;
        unsigned int int_c : 1;
        unsigned int retuning_event : 1;
        unsigned int boot_ack_rev : 1;
        unsigned int boot_terminate_intrrupt : 1;
        unsigned int error_interrupt : 1;
        unsigned int cmd_timeout_error : 1;
        unsigned int cmd_crc_error : 1;
        unsigned int cmd_end_bit_error : 1;
        unsigned int cmd_index_err : 1;
        unsigned int data_timeout_error : 1;
        unsigned int data_crc_error : 1;
        unsigned int data_endbit_error : 1;
        unsigned int current_limit_error : 1;
        unsigned int auto_cmd_error : 1;
        unsigned int adma_error : 1;
        unsigned int reserved_0 : 2;
        unsigned int target_resp_error : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_complete_START (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_complete_END (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_transfer_complete_START (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_transfer_complete_END (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_bloack_gap_event_START (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_bloack_gap_event_END (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_dma_imterrupt_START (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_dma_imterrupt_END (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_write_ready_START (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_write_ready_END (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_read_ready_START (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_read_ready_END (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_insertion_START (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_insertion_END (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_removal_START (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_removal_END (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_interrupt_START (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_interrupt_END (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_a_START (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_a_END (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_b_START (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_b_END (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_c_START (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_c_END (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_retuning_event_START (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_retuning_event_END (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_ack_rev_START (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_ack_rev_END (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_terminate_intrrupt_START (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_terminate_intrrupt_END (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_error_interrupt_START (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_error_interrupt_END (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_timeout_error_START (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_timeout_error_END (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_crc_error_START (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_crc_error_END (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_end_bit_error_START (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_end_bit_error_END (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_index_err_START (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_index_err_END (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_timeout_error_START (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_timeout_error_END (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_crc_error_START (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_crc_error_END (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_endbit_error_START (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_endbit_error_END (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_current_limit_error_START (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_current_limit_error_END (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_auto_cmd_error_START (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_auto_cmd_error_END (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_adma_error_START (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_adma_error_END (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_target_resp_error_START (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_target_resp_error_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_complete_mask : 1;
        unsigned int transfer_complete_mask : 1;
        unsigned int bloack_gap_event_mask : 1;
        unsigned int dma_imterrupt_mask : 1;
        unsigned int buffer_write_ready_mask : 1;
        unsigned int buffer_read_ready_mask : 1;
        unsigned int card_insertion_mask : 1;
        unsigned int card_removal_mask : 1;
        unsigned int card_interrupt_mask : 1;
        unsigned int int_a_mask : 1;
        unsigned int int_b_mask : 1;
        unsigned int int_c_mask : 1;
        unsigned int retuning_event_mask : 1;
        unsigned int boot_ack_rev_mask : 1;
        unsigned int boot_terminate_intrrupt_mask : 1;
        unsigned int fixed_zero : 1;
        unsigned int cmd_timeout_err_mask : 1;
        unsigned int cmd_crc_err_mask : 1;
        unsigned int cmd_end_bit_err_mask : 1;
        unsigned int cmd_index_err_mask : 1;
        unsigned int data_timeout_err_mask : 1;
        unsigned int data_crc_err_mask : 1;
        unsigned int data_endbit_err_mask : 1;
        unsigned int current_limit_err_mask : 1;
        unsigned int auto_cmd12_err_mask : 1;
        unsigned int adma_err_mask : 1;
        unsigned int tuning_err_mask : 1;
        unsigned int reserved_0 : 1;
        unsigned int target_resp_err_mask : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_complete_mask_START (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_complete_mask_END (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_transfer_complete_mask_START (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_transfer_complete_mask_END (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_bloack_gap_event_mask_START (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_bloack_gap_event_mask_END (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_dma_imterrupt_mask_START (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_dma_imterrupt_mask_END (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_write_ready_mask_START (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_write_ready_mask_END (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_read_ready_mask_START (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_read_ready_mask_END (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_insertion_mask_START (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_insertion_mask_END (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_removal_mask_START (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_removal_mask_END (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_interrupt_mask_START (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_interrupt_mask_END (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_a_mask_START (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_a_mask_END (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_b_mask_START (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_b_mask_END (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_c_mask_START (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_c_mask_END (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_retuning_event_mask_START (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_retuning_event_mask_END (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_ack_rev_mask_START (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_ack_rev_mask_END (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_terminate_intrrupt_mask_START (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_terminate_intrrupt_mask_END (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_fixed_zero_START (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_fixed_zero_END (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_timeout_err_mask_START (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_timeout_err_mask_END (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_crc_err_mask_START (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_crc_err_mask_END (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_end_bit_err_mask_START (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_end_bit_err_mask_END (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_index_err_mask_START (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_index_err_mask_END (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_timeout_err_mask_START (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_timeout_err_mask_END (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_crc_err_mask_START (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_crc_err_mask_END (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_endbit_err_mask_START (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_endbit_err_mask_END (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_current_limit_err_mask_START (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_current_limit_err_mask_END (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_auto_cmd12_err_mask_START (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_auto_cmd12_err_mask_END (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_adma_err_mask_START (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_adma_err_mask_END (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_tuning_err_mask_START (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_tuning_err_mask_END (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_target_resp_err_mask_START (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_target_resp_err_mask_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_complete_enable : 1;
        unsigned int transfer_complete_enable : 1;
        unsigned int bloack_gap_event_enable : 1;
        unsigned int dma_imterrupt_enable : 1;
        unsigned int buffer_write_ready_enable : 1;
        unsigned int buffer_read_ready_enable : 1;
        unsigned int card_insertion_enable : 1;
        unsigned int card_removal_enable : 1;
        unsigned int card_interrupt_enable : 1;
        unsigned int int_a_enable : 1;
        unsigned int int_b_enable : 1;
        unsigned int int_c_enable : 1;
        unsigned int retuning_event_enable : 1;
        unsigned int boot_ack_rev_enable : 1;
        unsigned int boot_terminate_intrrupt_enable : 1;
        unsigned int fixed_zero : 1;
        unsigned int cmd_timeout_err_enable : 1;
        unsigned int cmd_crc_err_enable : 1;
        unsigned int cmd_end_bit_err_enable : 1;
        unsigned int cmd_index_err_enable : 1;
        unsigned int data_timeout_err_enable : 1;
        unsigned int data_crc_err_enable : 1;
        unsigned int data_endbit_err_enable : 1;
        unsigned int current_limit_err_enable : 1;
        unsigned int auto_cmd12_err_enable : 1;
        unsigned int adma_err_enable : 1;
        unsigned int tuning_err_enable : 1;
        unsigned int reserved_0 : 1;
        unsigned int target_resp_err_enable : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_complete_enable_START (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_complete_enable_END (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_transfer_complete_enable_START (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_transfer_complete_enable_END (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_bloack_gap_event_enable_START (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_bloack_gap_event_enable_END (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_dma_imterrupt_enable_START (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_dma_imterrupt_enable_END (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_write_ready_enable_START (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_write_ready_enable_END (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_read_ready_enable_START (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_read_ready_enable_END (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_insertion_enable_START (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_insertion_enable_END (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_removal_enable_START (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_removal_enable_END (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_interrupt_enable_START (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_interrupt_enable_END (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_a_enable_START (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_a_enable_END (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_b_enable_START (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_b_enable_END (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_c_enable_START (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_c_enable_END (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_retuning_event_enable_START (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_retuning_event_enable_END (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_ack_rev_enable_START (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_ack_rev_enable_END (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_terminate_intrrupt_enable_START (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_terminate_intrrupt_enable_END (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_fixed_zero_START (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_fixed_zero_END (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_timeout_err_enable_START (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_timeout_err_enable_END (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_crc_err_enable_START (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_crc_err_enable_END (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_end_bit_err_enable_START (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_end_bit_err_enable_END (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_index_err_enable_START (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_index_err_enable_END (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_timeout_err_enable_START (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_timeout_err_enable_END (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_crc_err_enable_START (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_crc_err_enable_END (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_endbit_err_enable_START (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_endbit_err_enable_END (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_current_limit_err_enable_START (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_current_limit_err_enable_END (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_auto_cmd12_err_enable_START (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_auto_cmd12_err_enable_END (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_adma_err_enable_START (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_adma_err_enable_END (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_tuning_err_enable_START (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_tuning_err_enable_END (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_target_resp_err_enable_START (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_target_resp_err_enable_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_cmd12_not_executed : 1;
        unsigned int auto_cmd_timeout_error : 1;
        unsigned int auto_cmd_crc_error : 1;
        unsigned int auto_cmd_end_bit_error : 1;
        unsigned int auto_cmd_index_error : 1;
        unsigned int reserved_0 : 2;
        unsigned int command_not_issued_by_auto_cmd12_error : 1;
        unsigned int reserved_1 : 8;
        unsigned int uhs_mode_select : 3;
        unsigned int v1p8_signaling_enable : 1;
        unsigned int driver_strength_select : 2;
        unsigned int executetuning : 1;
        unsigned int sampling_clock_select : 1;
        unsigned int reserved_2 : 1;
        unsigned int driverstrength : 1;
        unsigned int reserved_3 : 4;
        unsigned int asynchronous_interrupt_enable : 1;
        unsigned int preset_value_enable : 1;
    } reg;
} SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_UNION;
#endif
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd12_not_executed_START (0)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd12_not_executed_END (0)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_timeout_error_START (1)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_timeout_error_END (1)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_crc_error_START (2)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_crc_error_END (2)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_end_bit_error_START (3)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_end_bit_error_END (3)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_index_error_START (4)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_index_error_END (4)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_command_not_issued_by_auto_cmd12_error_START (7)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_command_not_issued_by_auto_cmd12_error_END (7)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_uhs_mode_select_START (16)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_uhs_mode_select_END (18)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_v1p8_signaling_enable_START (19)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_v1p8_signaling_enable_END (19)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driver_strength_select_START (20)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driver_strength_select_END (21)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_executetuning_START (22)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_executetuning_END (22)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_sampling_clock_select_START (23)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_sampling_clock_select_END (23)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driverstrength_START (25)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driverstrength_END (25)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_asynchronous_interrupt_enable_START (30)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_asynchronous_interrupt_enable_END (30)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_preset_value_enable_START (31)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_preset_value_enable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeoutclockfrequency : 6;
        unsigned int reserved_0 : 1;
        unsigned int timeoutclockunit : 1;
        unsigned int baseclockfrequencyforsdclock : 8;
        unsigned int max_block_length : 2;
        unsigned int extendedmediabussupport : 1;
        unsigned int adma2support : 1;
        unsigned int reserved_1 : 1;
        unsigned int highspeedsupport : 1;
        unsigned int sdma_support : 1;
        unsigned int suspend_resumesupport : 1;
        unsigned int voltagesupport3_3v : 1;
        unsigned int voltagesupport3_0v : 1;
        unsigned int voltagesupport1_8v : 1;
        unsigned int reserved_2 : 1;
        unsigned int bus64_bitsystembussupport : 1;
        unsigned int asynchronous_interrupt_support : 1;
        unsigned int slottype : 2;
    } reg;
} SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_UNION;
#endif
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockfrequency_START (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockfrequency_END (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockunit_START (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockunit_END (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_baseclockfrequencyforsdclock_START (8)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_baseclockfrequencyforsdclock_END (15)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_max_block_length_START (16)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_max_block_length_END (17)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_extendedmediabussupport_START (18)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_extendedmediabussupport_END (18)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_adma2support_START (19)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_adma2support_END (19)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_highspeedsupport_START (21)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_highspeedsupport_END (21)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_sdma_support_START (22)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_sdma_support_END (22)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_suspend_resumesupport_START (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_suspend_resumesupport_END (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_3v_START (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_3v_END (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_0v_START (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_0v_END (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport1_8v_START (26)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport1_8v_END (26)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_bus64_bitsystembussupport_START (28)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_bus64_bitsystembussupport_END (28)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_asynchronous_interrupt_support_START (29)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_asynchronous_interrupt_support_END (29)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_slottype_START (30)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_slottype_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sdr50_support : 1;
        unsigned int sdr104_support : 1;
        unsigned int ddr50_support : 1;
        unsigned int reserved_0 : 1;
        unsigned int driver_typea_support : 1;
        unsigned int driver_typec_support : 1;
        unsigned int driver_typed_support : 1;
        unsigned int driver_type4_support : 1;
        unsigned int timer_count_for_retuning : 4;
        unsigned int reserved_1 : 1;
        unsigned int use_tuning_for_sdr50 : 1;
        unsigned int re_tuning_modes : 2;
        unsigned int clock_multiplier : 8;
        unsigned int spi_mode : 1;
        unsigned int spi_block_mode : 1;
        unsigned int reserved_2 : 5;
        unsigned int hs400_support : 1;
    } reg;
} SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_UNION;
#endif
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr50_support_START (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr50_support_END (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr104_support_START (1)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr104_support_END (1)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ddr50_support_START (2)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ddr50_support_END (2)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typea_support_START (4)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typea_support_END (4)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typec_support_START (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typec_support_END (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typed_support_START (6)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typed_support_END (6)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_type4_support_START (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_type4_support_END (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_timer_count_for_retuning_START (8)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_timer_count_for_retuning_END (11)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_use_tuning_for_sdr50_START (13)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_use_tuning_for_sdr50_END (13)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_re_tuning_modes_START (14)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_re_tuning_modes_END (15)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_clock_multiplier_START (16)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_clock_multiplier_END (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_mode_START (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_mode_END (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_block_mode_START (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_block_mode_END (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_hs400_support_START (31)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_hs400_support_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int max_current : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_EMMC_ARASAN_MAX_CURRENT_UNION;
#endif
#define SOC_EMMC_ARASAN_MAX_CURRENT_max_current_START (0)
#define SOC_EMMC_ARASAN_MAX_CURRENT_max_current_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int forceeventforautocmd12notexecuted_ : 1;
        unsigned int forceeventforautocmdtimeouterror_ : 1;
        unsigned int forceeventforautocmdcrcerror : 1;
        unsigned int forceeventforautocmdendbiterror : 1;
        unsigned int forceeventforautocmdindexerror : 1;
        unsigned int reserved_0 : 2;
        unsigned int forceeventforcommandnotissuedbyautocmd12error : 1;
        unsigned int reserved_1 : 8;
        unsigned int forceeventforcommandtime_outerror : 1;
        unsigned int forceeventforcommandcrcerror : 1;
        unsigned int forceeventforcommandendbiterror : 1;
        unsigned int forceeventforcommandindexerror : 1;
        unsigned int forceeventfordatatimeouterror : 1;
        unsigned int forceeventfordatacrcerror : 1;
        unsigned int forceeventfordataendbiterror : 1;
        unsigned int forceeventforcurrentlimiterror : 1;
        unsigned int forceeventforautocmderror : 1;
        unsigned int forceeventforadmaerror : 1;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmd12notexecuted__START (0)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmd12notexecuted__END (0)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdtimeouterror__START (1)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdtimeouterror__END (1)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdcrcerror_START (2)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdcrcerror_END (2)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdendbiterror_START (3)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdendbiterror_END (3)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdindexerror_START (4)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdindexerror_END (4)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandnotissuedbyautocmd12error_START (7)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandnotissuedbyautocmd12error_END (7)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandtime_outerror_START (16)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandtime_outerror_END (16)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandcrcerror_START (17)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandcrcerror_END (17)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandendbiterror_START (18)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandendbiterror_END (18)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandindexerror_START (19)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandindexerror_END (19)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatatimeouterror_START (20)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatatimeouterror_END (20)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatacrcerror_START (21)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatacrcerror_END (21)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordataendbiterror_START (22)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordataendbiterror_END (22)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcurrentlimiterror_START (23)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcurrentlimiterror_END (23)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmderror_START (24)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmderror_END (24)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforadmaerror_START (25)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforadmaerror_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int admaerrorstate : 2;
        unsigned int admalengthmismatcherror : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admaerrorstate_START (0)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admaerrorstate_END (1)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admalengthmismatcherror_START (2)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admalengthmismatcherror_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int admasystemaddress2 : 32;
    } reg;
} SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_admasystemaddress2_START (0)
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_admasystemaddress2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int adma_system_address1 : 32;
    } reg;
} SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_adma_system_address1_START (0)
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_adma_system_address1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int presetvalueforinitialization : 17;
        unsigned int presetvaluefordefaultspeed : 15;
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE1_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvalueforinitialization_START (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvalueforinitialization_END (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvaluefordefaultspeed_START (17)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvaluefordefaultspeed_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int presetvalueforsdr12 : 16;
        unsigned int presetvalueforhighspeed : 16;
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE2_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforsdr12_START (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforsdr12_END (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforhighspeed_START (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforhighspeed_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int presetvalueforsdr25 : 16;
        unsigned int presetvalueforsdr50 : 16;
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE3_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr25_START (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr25_END (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr50_START (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr50_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int presetvalueforsdr104 : 16;
        unsigned int presetvalueforddr50 : 16;
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE4_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforsdr104_START (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforsdr104_END (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforddr50_START (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforddr50_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int presetvalueforhs400 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE5_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE5_presetvalueforhs400_START (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE5_presetvalueforhs400_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bootdatatimeoutcountervalue : 32;
    } reg;
} SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_bootdatatimeoutcountervalue_START (0)
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_bootdatatimeoutcountervalue_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enhancedstrobe : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_enhancedstrobe_START (0)
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_enhancedstrobe_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emmcversionsuffix : 4;
        unsigned int emmcminorversionnum : 4;
        unsigned int emmcmajorversionnum : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcversionsuffix_START (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcversionsuffix_END (3)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcminorversionnum_START (4)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcminorversionnum_END (7)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcmajorversionnum_START (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcmajorversionnum_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intertimerclkfreqval : 10;
        unsigned int reserved_0 : 2;
        unsigned int intertimerclkfreqmul : 4;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqval_START (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqval_END (9)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqmul_START (12)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqmul_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmdqueueing_en : 1;
        unsigned int reserved_0 : 7;
        unsigned int taskdescsize : 1;
        unsigned int reserved_1 : 3;
        unsigned int directcmd_en : 1;
        unsigned int reserved_2 : 19;
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_cmdqueueing_en_START (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_cmdqueueing_en_END (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_taskdescsize_START (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_taskdescsize_END (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_directcmd_en_START (12)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_directcmd_en_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int halt : 1;
        unsigned int reserved_0 : 7;
        unsigned int clearalltasks : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_halt_START (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_halt_END (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_clearalltasks_START (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_clearalltasks_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int haltcompleteintr : 1;
        unsigned int taskcompleteintr : 1;
        unsigned int resperrdetectedintr : 1;
        unsigned int taskcleared : 1;
        unsigned int taskerrorintr : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_haltcompleteintr_START (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_haltcompleteintr_END (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcompleteintr_START (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcompleteintr_END (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_resperrdetectedintr_START (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_resperrdetectedintr_END (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcleared_START (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcleared_END (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskerrorintr_START (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskerrorintr_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int haltcompletestatus_en : 1;
        unsigned int taskcompletestatus_en : 1;
        unsigned int resperrdetecstatus_en : 1;
        unsigned int taskclearedstatus_en : 1;
        unsigned int taskerrintrstatus_en : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_haltcompletestatus_en_START (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_haltcompletestatus_en_END (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskcompletestatus_en_START (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskcompletestatus_en_END (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_resperrdetecstatus_en_START (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_resperrdetecstatus_en_END (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskclearedstatus_en_START (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskclearedstatus_en_END (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskerrintrstatus_en_START (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskerrintrstatus_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int haltcompletesig_en : 1;
        unsigned int taskcompletesig_en : 1;
        unsigned int resperrdetecsig_en : 1;
        unsigned int taskclearedsig_en : 1;
        unsigned int taskerrintrsig_en : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_haltcompletesig_en_START (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_haltcompletesig_en_END (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskcompletesig_en_START (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskcompletesig_en_END (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_resperrdetecsig_en_START (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_resperrdetecsig_en_END (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskclearedsig_en_START (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskclearedsig_en_END (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskerrintrsig_en_START (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskerrintrsig_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int intrcoaltimeoutval : 7;
        unsigned int intrcoaltimeoutval_wen : 1;
        unsigned int intrcoalcntthres : 5;
        unsigned int reserved_0 : 2;
        unsigned int intrcoalcntthres_wen : 1;
        unsigned int cnttimerrst : 1;
        unsigned int reserved_1 : 3;
        unsigned int intrcoalescingstatus : 1;
        unsigned int reserved_2 : 10;
        unsigned int intrcoalescing_en : 1;
    } reg;
} SOC_EMMC_ARASAN_INTERRUPT_COALESCING_UNION;
#endif
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_START (0)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_END (6)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_wen_START (7)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_wen_END (7)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_START (8)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_END (12)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_wen_START (15)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_wen_END (15)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_cnttimerrst_START (16)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_cnttimerrst_END (16)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescingstatus_START (20)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescingstatus_END (20)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescing_en_START (31)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescing_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taskdesclistbaseaddr_lower : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_taskdesclistbaseaddr_lower_START (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_taskdesclistbaseaddr_lower_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taskdesclistbaseaddr_upper : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_taskdesclistbaseaddr_upper_START (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_taskdesclistbaseaddr_upper_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmdqueuetaskdoorbell : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_cmdqueuetaskdoorbell_START (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_cmdqueuetaskdoorbell_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taskcomplnotification : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_taskcomplnotification_START (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_taskcomplnotification_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int devqueuestatus : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_devqueuestatus_START (0)
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_devqueuestatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int devpendtask : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_devpendtask_START (0)
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_devpendtask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmdqueueingtaskclr : 32;
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_CLEAR_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_cmdqueueingtaskclr_START (0)
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_cmdqueueingtaskclr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sendstatuscmdidletimer : 16;
        unsigned int sendstatuscmdblockcnt : 4;
        unsigned int reserved : 12;
    } reg;
} SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_UNION;
#endif
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdidletimer_START (0)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdidletimer_END (15)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdblockcnt_START (16)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdblockcnt_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sendqueuerca : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_EMMC_ARASAN_SEND_STATUS_CFG2_UNION;
#endif
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_sendqueuerca_START (0)
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_sendqueuerca_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int direcmdlastresp : 32;
    } reg;
} SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_UNION;
#endif
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_direcmdlastresp_START (0)
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_direcmdlastresp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int respmodeerrmask : 32;
    } reg;
} SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_UNION;
#endif
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_respmodeerrmask_START (0)
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_respmodeerrmask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int respmodeerrcmdindex : 6;
        unsigned int reserved_0 : 2;
        unsigned int respmode0errtaskid : 5;
        unsigned int reserved_1 : 2;
        unsigned int respmodeerrfieldsvalid : 1;
        unsigned int datatranserrcmdindex : 6;
        unsigned int reserved_2 : 2;
        unsigned int datatranserrtaskid : 5;
        unsigned int reserved_3 : 2;
        unsigned int datatranserrfieldsvalid : 1;
    } reg;
} SOC_EMMC_ARASAN_TASK_ERROR_INFO_UNION;
#endif
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrcmdindex_START (0)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrcmdindex_END (5)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmode0errtaskid_START (8)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmode0errtaskid_END (12)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrfieldsvalid_START (15)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrfieldsvalid_END (15)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrcmdindex_START (16)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrcmdindex_END (21)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrtaskid_START (24)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrtaskid_END (28)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrfieldsvalid_START (31)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrfieldsvalid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lastcmdrespindex : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_EMMC_ARASAN_CMD_RESP_INDEX_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_lastcmdrespindex_START (0)
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_lastcmdrespindex_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lastcmdrespargumemt : 32;
    } reg;
} SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_lastcmdrespargumemt_START (0)
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_lastcmdrespargumemt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_1p8voltsupport : 1;
        unsigned int corecfg_3p0voltsupport : 1;
        unsigned int corecfg_3p3voltsupport : 1;
        unsigned int corecfg_suspressupport : 1;
        unsigned int corecfg_sdmasupport : 1;
        unsigned int corecfg_highspeedsupport : 1;
        unsigned int corecfg_adma2support : 1;
        unsigned int corecfg_8bitsupport : 1;
        unsigned int corecfg_maxblklength : 2;
        unsigned int corecfg_baseclkfreq : 8;
        unsigned int corecfg_timeoutclkunit : 1;
        unsigned int corecfg_timeoutclkfreq : 6;
        unsigned int corecfg_tuningcount : 6;
        unsigned int corecfg_asyncwkupena : 1;
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG0_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_1p8voltsupport_START (0)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_1p8voltsupport_END (0)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p0voltsupport_START (1)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p0voltsupport_END (1)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p3voltsupport_START (2)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p3voltsupport_END (2)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_suspressupport_START (3)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_suspressupport_END (3)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_sdmasupport_START (4)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_sdmasupport_END (4)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_highspeedsupport_START (5)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_highspeedsupport_END (5)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_adma2support_START (6)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_adma2support_END (6)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_8bitsupport_START (7)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_8bitsupport_END (7)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_maxblklength_START (8)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_maxblklength_END (9)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_baseclkfreq_START (10)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_baseclkfreq_END (17)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkunit_START (18)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkunit_END (18)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkfreq_START (19)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkfreq_END (24)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_tuningcount_START (25)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_tuningcount_END (30)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_asyncwkupena_START (31)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_asyncwkupena_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 3;
        unsigned int corecfg_spiblkmode : 1;
        unsigned int corecfg_spisupport : 1;
        unsigned int corecfg_clockmultiplier : 8;
        unsigned int corecfg_retuningmodes : 2;
        unsigned int corecfg_tuningforsdr50 : 1;
        unsigned int corecfg_retuningtimercnt : 4;
        unsigned int corecfg_type4support : 1;
        unsigned int corecfg_ddriversupport : 1;
        unsigned int corecfg_cdriversupport : 1;
        unsigned int corecfg_adriversupport : 1;
        unsigned int corecfg_hs400support : 1;
        unsigned int corecfg_ddr50support : 1;
        unsigned int corecfg_sdr104support : 1;
        unsigned int corecfg_sdr50support : 1;
        unsigned int corecfg_slottype : 2;
        unsigned int corecfg_asynchintrsupport : 1;
        unsigned int corecfg_64bitsupport : 1;
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG1_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spiblkmode_START (3)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spiblkmode_END (3)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spisupport_START (4)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spisupport_END (4)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_clockmultiplier_START (5)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_clockmultiplier_END (12)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningmodes_START (13)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningmodes_END (14)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_tuningforsdr50_START (15)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_tuningforsdr50_END (15)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningtimercnt_START (16)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningtimercnt_END (19)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_type4support_START (20)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_type4support_END (20)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddriversupport_START (21)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddriversupport_END (21)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_cdriversupport_START (22)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_cdriversupport_END (22)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_adriversupport_START (23)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_adriversupport_END (23)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_hs400support_START (24)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_hs400support_END (24)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddr50support_START (25)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddr50support_END (25)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr104support_START (26)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr104support_END (26)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr50support_START (27)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr50support_END (27)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_slottype_START (28)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_slottype_END (29)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_asynchintrsupport_START (30)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_asynchintrsupport_END (30)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_64bitsupport_START (31)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_64bitsupport_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_dspdpresetval : 13;
        unsigned int reserved_0 : 3;
        unsigned int corecfg_initpresetval : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_dspdpresetval_START (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_dspdpresetval_END (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_initpresetval_START (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_initpresetval_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_sdr12presetval : 13;
        unsigned int reserved_0 : 3;
        unsigned int corecfg_hspdpresetval : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_sdr12presetval_START (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_sdr12presetval_END (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_hspdpresetval_START (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_hspdpresetval_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_sdr50presetval : 13;
        unsigned int reserved_0 : 3;
        unsigned int corecfg_sdr25presetval : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr50presetval_START (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr50presetval_END (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr25presetval_START (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr25presetval_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_ddr50presetval : 13;
        unsigned int reserved_0 : 3;
        unsigned int corecfg_sdr104presetval : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_ddr50presetval_START (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_ddr50presetval_END (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_sdr104presetval_START (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_sdr104presetval_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_hs400presetval : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_corecfg_hs400presetval_START (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_corecfg_hs400presetval_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_maxcurrent3p3v : 8;
        unsigned int corecfg_maxcurrent3p0v : 8;
        unsigned int corecfg_maxcurrent1p8v : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG2_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p3v_START (0)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p3v_END (7)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p0v_START (8)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p0v_END (15)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent1p8v_START (16)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent1p8v_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_cmdfsm_state : 4;
        unsigned int cmd_cmdfsm_cmdout : 1;
        unsigned int cmd_cmdfsm_cmdena : 1;
        unsigned int cmd_cmdfsm_cmdcomplete : 1;
        unsigned int cmd_cmdfsm_cmdissued : 1;
        unsigned int cmd_cmdfsm_autocmd12 : 1;
        unsigned int cmd_cmdfsm_autocmd23 : 1;
        unsigned int cmd_regset_cmdexecute_sdclk : 1;
        unsigned int cmd_regset_bootena_sdclk : 1;
        unsigned int cmd_cmdfsm_cmdrespstatus : 4;
        unsigned int dma_piosdma_state : 3;
        unsigned int dma_adma2_state : 4;
        unsigned int dma_hosttrans_state : 2;
        unsigned int dma_hostrddat_state : 1;
        unsigned int dma_hostwrdat_state : 1;
        unsigned int dma_hostintf_stopatblkgap : 1;
        unsigned int dma_hostintf_enddataxfer : 1;
        unsigned int dma_hostintf_rdxferactive : 1;
        unsigned int dma_hostintf_abortcmdmode : 1;
        unsigned int dma_hostintf_blocknextcmd : 1;
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG0_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_state_START (0)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_state_END (3)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdout_START (4)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdout_END (4)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdena_START (5)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdena_END (5)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdcomplete_START (6)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdcomplete_END (6)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdissued_START (7)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdissued_END (7)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd12_START (8)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd12_END (8)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd23_START (9)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd23_END (9)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_cmdexecute_sdclk_START (10)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_cmdexecute_sdclk_END (10)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_bootena_sdclk_START (11)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_bootena_sdclk_END (11)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdrespstatus_START (12)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdrespstatus_END (15)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_piosdma_state_START (16)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_piosdma_state_END (18)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_adma2_state_START (19)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_adma2_state_END (22)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hosttrans_state_START (23)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hosttrans_state_END (24)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostrddat_state_START (25)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostrddat_state_END (25)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostwrdat_state_START (26)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostwrdat_state_END (26)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_stopatblkgap_START (27)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_stopatblkgap_END (27)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_enddataxfer_START (28)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_enddataxfer_END (28)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_rdxferactive_START (29)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_rdxferactive_END (29)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_abortcmdmode_START (30)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_abortcmdmode_END (30)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_blocknextcmd_START (31)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_blocknextcmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rxctrl_rcvdata : 1;
        unsigned int rxctrl_stopsdcardclk1 : 1;
        unsigned int rxctrl_stopsdcardclk2 : 1;
        unsigned int rxctrl_stopafterblk : 1;
        unsigned int rxctrl_rcvstsvld : 1;
        unsigned int rxctrl_rcvstatus : 3;
        unsigned int reserved : 8;
        unsigned int txdfsm_state : 4;
        unsigned int txdfsm_datalineactive : 1;
        unsigned int txdfsm_wrxferactive : 1;
        unsigned int txdfsm_sddataena : 1;
        unsigned int txdfsm_readbuffer : 1;
        unsigned int txdfsm_readeob : 1;
        unsigned int txdfsm_rcvcrcsts : 1;
        unsigned int txdfsm_xmitstsvld : 1;
        unsigned int txdfsm_xmitstatus : 3;
        unsigned int txdfsm_stopsdcardclk : 1;
        unsigned int txdfsm_enatimeoutchk : 1;
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG1_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvdata_START (0)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvdata_END (0)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk1_START (1)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk1_END (1)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk2_START (2)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk2_END (2)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopafterblk_START (3)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopafterblk_END (3)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstsvld_START (4)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstsvld_END (4)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstatus_START (5)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstatus_END (7)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_state_START (16)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_state_END (19)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_datalineactive_START (20)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_datalineactive_END (20)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_wrxferactive_START (21)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_wrxferactive_END (21)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_sddataena_START (22)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_sddataena_END (22)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readbuffer_START (23)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readbuffer_END (23)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readeob_START (24)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readeob_END (24)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_rcvcrcsts_START (25)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_rcvcrcsts_END (25)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstsvld_START (26)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstsvld_END (26)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstatus_START (27)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstatus_END (29)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_stopsdcardclk_START (30)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_stopsdcardclk_END (30)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_enatimeoutchk_START (31)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_enatimeoutchk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tuningfsm_state : 3;
        unsigned int tuningfsm_count : 6;
        unsigned int tuningfsm_numseqmatch : 6;
        unsigned int tuningfsm_done : 1;
        unsigned int rxdfsm_state : 3;
        unsigned int rxdfsm_wtforblk : 1;
        unsigned int rxdfsm_datawrite : 1;
        unsigned int rxdfsm_dataeob : 1;
        unsigned int rxdfsm_okstopclk : 1;
        unsigned int rxdfsm_reachingeob : 1;
        unsigned int sdhc_rxddebugbus1 : 8;
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG2_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_state_START (0)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_state_END (2)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_count_START (3)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_count_END (8)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_numseqmatch_START (9)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_numseqmatch_END (14)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_done_START (15)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_done_END (15)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_state_START (16)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_state_END (18)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_wtforblk_START (19)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_wtforblk_END (19)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_datawrite_START (20)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_datawrite_END (20)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_dataeob_START (21)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_dataeob_END (21)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_okstopclk_START (22)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_okstopclk_END (22)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_reachingeob_START (23)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_reachingeob_END (23)
#define SOC_EMMC_ARASAN_DEBUG_REG2_sdhc_rxddebugbus1_START (24)
#define SOC_EMMC_ARASAN_DEBUG_REG2_sdhc_rxddebugbus1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sdhc_ledcontrol : 1;
        unsigned int sdhc_sdbuspower : 1;
        unsigned int sdhc_sdbusvoltage : 3;
        unsigned int sdhc_driverstrength : 3;
        unsigned int sdhc_1p8vsigenable : 1;
        unsigned int sdhc_emmchwrst_n : 1;
        unsigned int sdhc_cmddir : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG3_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_ledcontrol_START (0)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_ledcontrol_END (0)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbuspower_START (1)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbuspower_END (1)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbusvoltage_START (2)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbusvoltage_END (4)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_driverstrength_START (5)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_driverstrength_END (7)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_1p8vsigenable_START (8)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_1p8vsigenable_END (8)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_emmchwrst_n_START (9)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_emmchwrst_n_END (9)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_cmddir_START (10)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_cmddir_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyctrl_oden_cmd : 1;
        unsigned int phyctrl_oden_strb : 1;
        unsigned int phyctrl_retenb : 1;
        unsigned int phyctrl_reten : 1;
        unsigned int phyctrl_dlliff : 3;
        unsigned int phyctrl_endll : 1;
        unsigned int phyctrl_dll_trm_icp : 8;
        unsigned int phyctrl_en_rtrim : 1;
        unsigned int reserved_0 : 4;
        unsigned int phyctrl_retrim : 1;
        unsigned int phyctrl_dr_ty : 3;
        unsigned int phyctrl_pdb : 1;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL1_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_cmd_START (0)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_cmd_END (0)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_strb_START (1)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_strb_END (1)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retenb_START (2)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retenb_END (2)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_reten_START (3)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_reten_END (3)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dlliff_START (4)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dlliff_END (6)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_endll_START (7)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_endll_END (7)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dll_trm_icp_START (8)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dll_trm_icp_END (15)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_en_rtrim_START (16)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_en_rtrim_END (16)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retrim_START (21)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retrim_END (21)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dr_ty_START (22)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dr_ty_END (24)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_pdb_START (25)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_pdb_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyctrl_od_release_cmd : 1;
        unsigned int phyctrl_od_release_strb : 1;
        unsigned int phyctrl_pu_dat : 8;
        unsigned int phyctrl_pu_cmd : 1;
        unsigned int phyctrl_pu_strb : 1;
        unsigned int phyctrl_ren_dat : 8;
        unsigned int phyctrl_ren_cmd : 1;
        unsigned int phyctrl_ren_strb : 1;
        unsigned int phyctrl_oden_dat : 8;
        unsigned int reserved : 2;
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL2_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_cmd_START (0)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_cmd_END (0)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_strb_START (1)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_strb_END (1)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_dat_START (2)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_dat_END (9)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_cmd_START (10)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_cmd_END (10)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_strb_START (11)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_strb_END (11)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_dat_START (12)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_dat_END (19)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_cmd_START (20)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_cmd_END (20)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_strb_START (21)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_strb_END (21)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_oden_dat_START (22)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_oden_dat_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyctrl_seldlytxclk : 1;
        unsigned int phyctrl_seldlyrxclk : 1;
        unsigned int phyctrl_strbsel : 4;
        unsigned int reserved_0 : 2;
        unsigned int phyctrl_otapdlyena : 1;
        unsigned int phyctrl_otapdlysel : 4;
        unsigned int phyctrl_itapchgwin : 1;
        unsigned int phyctrl_itapdlyena : 1;
        unsigned int phyctrl_itapdlysel : 5;
        unsigned int phyctrl_od_release_dat : 8;
        unsigned int phyctrl_freqsel : 3;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL3_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlytxclk_START (0)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlytxclk_END (0)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlyrxclk_START (1)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlyrxclk_END (1)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_strbsel_START (2)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_strbsel_END (5)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlyena_START (8)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlyena_END (8)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlysel_START (9)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlysel_END (12)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapchgwin_START (13)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapchgwin_END (13)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlyena_START (14)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlyena_END (14)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlysel_START (15)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlysel_END (19)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_od_release_dat_START (20)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_od_release_dat_END (27)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_freqsel_START (28)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_freqsel_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyctrl_testctrl : 8;
        unsigned int reserved_0 : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL4_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL4_phyctrl_testctrl_START (0)
#define SOC_EMMC_ARASAN_PHYCTRL4_phyctrl_testctrl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phyctrl_exr_ninst : 1;
        unsigned int phyctrl_dllrdy : 1;
        unsigned int phyctrl_rtrim : 4;
        unsigned int phyctrl_caldone : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_EMMC_ARASAN_PHY_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_exr_ninst_START (0)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_exr_ninst_END (0)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_dllrdy_START (1)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_dllrdy_END (1)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_rtrim_START (2)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_rtrim_END (5)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_caldone_START (6)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_caldone_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int test_output_en : 1;
        unsigned int phyctrl_clkbufsel : 3;
        unsigned int sdcard_buf_bypass : 1;
        unsigned int test_ctrl_bak : 11;
        unsigned int reserved : 16;
    } reg;
} SOC_EMMC_ARASAN_TEST_CONTROL_UNION;
#endif
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_output_en_START (0)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_output_en_END (0)
#define SOC_EMMC_ARASAN_TEST_CONTROL_phyctrl_clkbufsel_START (1)
#define SOC_EMMC_ARASAN_TEST_CONTROL_phyctrl_clkbufsel_END (3)
#define SOC_EMMC_ARASAN_TEST_CONTROL_sdcard_buf_bypass_START (4)
#define SOC_EMMC_ARASAN_TEST_CONTROL_sdcard_buf_bypass_END (4)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_ctrl_bak_START (5)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_ctrl_bak_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int corecfg_cqfval : 10;
        unsigned int corecfg_cqfmul : 4;
        unsigned int reserved : 18;
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG3_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfval_START (0)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfval_END (9)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfmul_START (10)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfmul_END (13)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
