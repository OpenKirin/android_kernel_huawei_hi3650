#ifndef __SOC_NANDC_INTERFACE_H__
#define __SOC_NANDC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_NANDC_NFC_DATANUM_ADDR(base) ((base) + (0x00))
#define SOC_NANDC_NFC_WSC_ADDR(base) ((base) + (0x04))
#define SOC_NANDC_NFC_DEVCFG_ADDR(base) ((base) + (0x08))
#define SOC_NANDC_NFC_CMDCFG_ADDR(base) ((base) + (0x0C))
#define SOC_NANDC_NFC_COM_ADDR(base) ((base) + (0x10))
#define SOC_NANDC_NFC_ADDRL_ADDR(base) ((base) + (0x14))
#define SOC_NANDC_NFC_ADDRH_ADDR(base) ((base) + (0x18))
#define SOC_NANDC_NFC_BUFEN_ADDR(base) ((base) + (0x1C))
#define SOC_NANDC_NFC_BUFCTRL_ADDR(base) ((base) + (0x20))
#define SOC_NANDC_NFC_INTEN_ADDR(base) ((base) + (0x24))
#define SOC_NANDC_NFC_INTSTATUS_ADDR(base) ((base) + (0x28))
#define SOC_NANDC_NFC_INTCLR_ADDR(base) ((base) + (0x2C))
#define SOC_NANDC_NFC_STARTRD_ADDR(base) ((base) + (0x30))
#define SOC_NANDC_NFC_CSDNEN_ADDR(base) ((base) + (0x34))
#define SOC_NANDC_NFC_LOCK_SA1_ADDR(base) ((base) + (0x38))
#define SOC_NANDC_NFC_LOCK_ED1_ADDR(base) ((base) + (0x3C))
#define SOC_NANDC_NFC_LOCK_SA2_ADDR(base) ((base) + (0x40))
#define SOC_NANDC_NFC_LOCK_ED2_ADDR(base) ((base) + (0x44))
#define SOC_NANDC_NFC_LOCK_SA3_ADDR(base) ((base) + (0x48))
#define SOC_NANDC_NFC_LOCK_ED3_ADDR(base) ((base) + (0x4C))
#define SOC_NANDC_NFC_LOCK_SA4_ADDR(base) ((base) + (0x50))
#define SOC_NANDC_NFC_LOCK_ED4_ADDR(base) ((base) + (0x54))
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_ADDR(base) ((base) + (0x58))
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_ADDR(base) ((base) + (0x5C))
#define SOC_NANDC_NFC_FLASHLOCK_COM1_ADDR(base) ((base) + (0x60))
#define SOC_NANDC_NFC_FLASHLOCK_COM2_ADDR(base) ((base) + (0x64))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_num : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_NANDC_NFC_DATANUM_UNION;
#endif
#define SOC_NANDC_NFC_DATANUM_data_num_START (0)
#define SOC_NANDC_NFC_DATANUM_data_num_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wt_pulse : 4;
        unsigned int rd_pulse : 4;
        unsigned int rdwt_high : 4;
        unsigned int wait_busy : 4;
        unsigned int cs_wait_wide_wr : 4;
        unsigned int reserved : 12;
    } reg;
} SOC_NANDC_NFC_WSC_UNION;
#endif
#define SOC_NANDC_NFC_WSC_wt_pulse_START (0)
#define SOC_NANDC_NFC_WSC_wt_pulse_END (3)
#define SOC_NANDC_NFC_WSC_rd_pulse_START (4)
#define SOC_NANDC_NFC_WSC_rd_pulse_END (7)
#define SOC_NANDC_NFC_WSC_rdwt_high_START (8)
#define SOC_NANDC_NFC_WSC_rdwt_high_END (11)
#define SOC_NANDC_NFC_WSC_wait_busy_START (12)
#define SOC_NANDC_NFC_WSC_wait_busy_END (15)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_START (16)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_size : 1;
        unsigned int bus_wide : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_NANDC_NFC_DEVCFG_UNION;
#endif
#define SOC_NANDC_NFC_DEVCFG_page_size_START (0)
#define SOC_NANDC_NFC_DEVCFG_page_size_END (0)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_START (1)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_num : 3;
        unsigned int reserved_0 : 1;
        unsigned int ca_sequence : 1;
        unsigned int com_only : 1;
        unsigned int rdwt_mode : 1;
        unsigned int busy_not_care : 1;
        unsigned int cs_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int ebi_n : 1;
        unsigned int reserved_2 : 19;
    } reg;
} SOC_NANDC_NFC_CMDCFG_UNION;
#endif
#define SOC_NANDC_NFC_CMDCFG_addr_num_START (0)
#define SOC_NANDC_NFC_CMDCFG_addr_num_END (2)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_START (4)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_END (4)
#define SOC_NANDC_NFC_CMDCFG_com_only_START (5)
#define SOC_NANDC_NFC_CMDCFG_com_only_END (5)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_START (6)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_END (6)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_START (7)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_END (7)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_START (8)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_END (9)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_START (12)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int command1 : 8;
        unsigned int command2 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_NANDC_NFC_COM_UNION;
#endif
#define SOC_NANDC_NFC_COM_command1_START (0)
#define SOC_NANDC_NFC_COM_command1_END (7)
#define SOC_NANDC_NFC_COM_command2_START (8)
#define SOC_NANDC_NFC_COM_command2_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_l : 32;
    } reg;
} SOC_NANDC_NFC_ADDRL_UNION;
#endif
#define SOC_NANDC_NFC_ADDRL_addr_l_START (0)
#define SOC_NANDC_NFC_ADDRL_addr_l_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_NANDC_NFC_ADDRH_UNION;
#endif
#define SOC_NANDC_NFC_ADDRH_addr_h_START (0)
#define SOC_NANDC_NFC_ADDRH_addr_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int boot_mode_n : 1;
        unsigned int ecc_bypass : 1;
        unsigned int secc_bypass : 1;
        unsigned int ecc_crct_bypass : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_NANDC_NFC_BUFEN_UNION;
#endif
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_START (0)
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_END (0)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_START (1)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_END (1)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_START (2)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_END (2)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_START (3)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int buffer_ready : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_NANDC_NFC_BUFCTRL_UNION;
#endif
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_START (0)
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cod_done_cs0_en : 1;
        unsigned int read_done_cs0_en : 1;
        unsigned int write_done_cs0_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int cod_done_cs1_en : 1;
        unsigned int read_done_cs1_en : 1;
        unsigned int write_done_cs1_en : 1;
        unsigned int reserved_1 : 1;
        unsigned int cod_done_cs2_en : 1;
        unsigned int read_done_cs2_en : 1;
        unsigned int write_done_cs2_en : 1;
        unsigned int reserved_2 : 1;
        unsigned int cod_done_cs3_en : 1;
        unsigned int read_done_cs3_en : 1;
        unsigned int write_done_cs3_en : 1;
        unsigned int reserved_3 : 1;
        unsigned int allbufferready_en : 1;
        unsigned int buffer1_ready_en : 1;
        unsigned int buffer2_ready_en : 1;
        unsigned int buffer3_ready_en : 1;
        unsigned int buffer4_ready_en : 1;
        unsigned int data_ecc_1bit_error_en : 1;
        unsigned int data_ecc_2bit_error_en : 1;
        unsigned int lsn_ecc_1bit_error_en : 1;
        unsigned int lsn_ecc_2bit_error_en : 1;
        unsigned int flashlock_error_en : 1;
        unsigned int reserved_4 : 6;
    } reg;
} SOC_NANDC_NFC_INTEN_UNION;
#endif
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_START (0)
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_END (0)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_START (1)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_END (1)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_START (2)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_END (2)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_START (4)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_END (4)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_START (5)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_END (5)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_START (6)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_END (6)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_START (8)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_END (8)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_START (9)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_END (9)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_START (10)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_END (10)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_START (12)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_END (12)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_START (13)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_END (13)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_START (14)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_END (14)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_START (16)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_END (16)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_START (17)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_END (17)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_START (18)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_END (18)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_START (19)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_END (19)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_START (20)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_END (20)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_START (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_END (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_START (22)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_END (22)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_START (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_END (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_START (24)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_END (24)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_START (25)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cod_done_cs0 : 1;
        unsigned int read_done_cs0 : 1;
        unsigned int write_done_cs0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int cod_done_cs1 : 1;
        unsigned int read_done_cs1 : 1;
        unsigned int write_done_cs1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int cod_done_cs2 : 1;
        unsigned int read_done_cs2 : 1;
        unsigned int write_done_cs2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int cod_done_cs3 : 1;
        unsigned int read_done_cs3 : 1;
        unsigned int write_done_cs3 : 1;
        unsigned int reserved_3 : 1;
        unsigned int allbufferready : 1;
        unsigned int buffer1_ready : 1;
        unsigned int buffer2_ready : 1;
        unsigned int buffer3_ready : 1;
        unsigned int buffer4_ready : 1;
        unsigned int data_ecc_1bit_error : 1;
        unsigned int data_ecc_2bit_error : 1;
        unsigned int lsn_ecc_1bit_error : 1;
        unsigned int lsn_ecc_2bit_error : 1;
        unsigned int flashlock_error : 1;
        unsigned int reserved_4 : 6;
    } reg;
} SOC_NANDC_NFC_INTSTATUS_UNION;
#endif
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_START (0)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_END (0)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_START (1)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_END (1)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_START (2)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_END (2)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_START (4)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_END (4)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_START (5)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_END (5)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_START (6)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_END (6)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_START (8)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_END (8)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_START (9)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_END (9)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_START (10)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_END (10)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_START (12)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_END (12)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_START (13)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_END (13)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_START (14)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_END (14)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_START (16)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_END (16)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_START (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_END (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_START (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_END (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_START (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_END (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_START (20)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_END (20)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_START (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_END (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_START (22)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_END (22)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_START (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_END (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_START (24)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_END (24)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_START (25)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int command_done_cs0 : 1;
        unsigned int read_done_cs0 : 1;
        unsigned int write_done_cs0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int command_done_cs1 : 1;
        unsigned int read_done_cs1 : 1;
        unsigned int write_done_cs1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int command_done_cs2 : 1;
        unsigned int read_done_cs2 : 1;
        unsigned int write_done_cs2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int command_done_cs3 : 1;
        unsigned int read_done_cs3 : 1;
        unsigned int write_done_cs3 : 1;
        unsigned int reserved_3 : 1;
        unsigned int all_buffer_ready : 1;
        unsigned int buffer1_ready : 1;
        unsigned int buffer2_ready : 1;
        unsigned int buffer3_ready : 1;
        unsigned int buffer4_ready : 1;
        unsigned int data_ecc_1bit_error : 1;
        unsigned int data_ecc_2bit_error : 1;
        unsigned int lsn_err_1bit_error : 1;
        unsigned int lsn_err_2bit_error : 1;
        unsigned int flashlock_error : 1;
        unsigned int reserved_4 : 6;
    } reg;
} SOC_NANDC_NFC_INTCLR_UNION;
#endif
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_START (0)
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_END (0)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_START (1)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_END (1)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_START (2)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_END (2)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_START (4)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_END (4)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_START (5)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_END (5)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_START (6)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_END (6)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_START (8)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_END (8)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_START (9)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_END (9)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_START (10)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_END (10)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_START (12)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_END (12)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_START (13)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_END (13)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_START (14)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_END (14)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_START (16)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_END (16)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_START (17)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_END (17)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_START (18)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_END (18)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_START (19)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_END (19)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_START (20)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_END (20)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_START (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_END (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_START (22)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_END (22)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_START (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_END (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_START (24)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_END (24)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_START (25)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int write_only_self_clear : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_NANDC_NFC_STARTRD_UNION;
#endif
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_START (0)
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csdnen : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_NANDC_NFC_CSDNEN_UNION;
#endif
#define SOC_NANDC_NFC_CSDNEN_csdnen_START (0)
#define SOC_NANDC_NFC_CSDNEN_csdnen_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_start_addr1 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_SA1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_START (0)
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_end_addr1 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_ED1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_START (0)
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_start_addr2 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_SA2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_START (0)
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_end_addr2 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_ED2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_START (0)
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_start_addr3 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_SA3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_START (0)
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_end_addr3 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_ED3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_START (0)
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_start_addr4 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_SA4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_START (0)
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_end_addr4 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_NANDC_NFC_LOCK_ED4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_START (0)
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashlock_whole_enable : 1;
        unsigned int flashlock_enable : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_START (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_END (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_START (1)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flashloc_control : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_START (0)
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int block_command1 : 8;
        unsigned int block_command2 : 8;
        unsigned int page_command1 : 8;
        unsigned int page_command2 : 8;
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM1_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_START (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_END (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_START (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_END (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_START (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_END (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_START (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_command3 : 8;
        unsigned int page_command4 : 8;
        unsigned int page_command5 : 8;
        unsigned int page_command6 : 8;
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM2_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_START (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_END (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_START (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_END (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_START (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_END (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_START (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
