#ifndef __HI_NANDC_H__
#define __HI_NANDC_H__ 
#include <hi_base.h>
#include <bsp_memmap.h>
#define HI_NFC_CON_OFFSET (0x0)
#define HI_NFC_PWIDTH_OFFSET (0x4)
#define HI_NFC_OPIDLE_OFFSET (0x8)
#define HI_NFC_CMD_OFFSET (0xC)
#define HI_NFC_ADDRL_OFFSET (0x10)
#define HI_NFC_ADDRH_OFFSET (0x14)
#define HI_NFC_DATA_NUM_OFFSET (0x18)
#define HI_NFC_OP_OFFSET (0x1C)
#define HI_NFC_STATUS_OFFSET (0x20)
#define HI_NFC_INTEN_OFFSET (0x24)
#define HI_NFC_INTS_OFFSET (0x28)
#define HI_NFC_INTCLR_OFFSET (0x2C)
#define HI_NFC_LOCK_OFFSET (0x30)
#define HI_NFC_LOCK_SA0_OFFSET (0x34)
#define HI_NFC_LOCK_SA1_OFFSET (0x38)
#define HI_NFC_LOCK_SA2_OFFSET (0x3C)
#define HI_NFC_LOCK_SA3_OFFSET (0x40)
#define HI_NFC_LOCK_EA0_OFFSET (0x44)
#define HI_NFC_LOCK_EA1_OFFSET (0x48)
#define HI_NFC_LOCK_EA2_OFFSET (0x4C)
#define HI_NFC_LOCK_EA3_OFFSET (0x50)
#define HI_NFC_EXPCMD_OFFSET (0x54)
#define HI_NFC_EXBCMD_OFFSET (0x58)
#define HI_NFC_ECC_TEST_OFFSET (0x5C)
#define HI_NFC_DMA_CTRL_OFFSET (0x60)
#define HI_NFC_BADDR_D_OFFSET (0x64)
#define HI_NFC_BADDR_OOB_OFFSET (0x68)
#define HI_NFC_DMA_LEN_OFFSET (0x6C)
#define HI_NFC_OP_PARA_OFFSET (0x70)
#define HI_NFC_VERSION_OFFSET (0x74)
#define HI_NFC_SEGMENT_ID_OFFSET (0x84)
#define HI_NFC_FIFO_EMPTY_OFFSET (0x90)
#define HI_NFC_BOOT_SET_OFFSET (0x94)
#define HI_NF_LP_CTRL_OFFSET (0x9C)
#define HI_NFC_ERR_NUM0_BUF0_OFFSET (0xA0)
#define HI_NFC_ERR_NUM1_BUF0_OFFSET (0xA4)
#define HI_NFC_ERR_NUM0_BUF1_OFFSET (0xA8)
#define HI_NFC_ERR_NUM1_BUF1_OFFSET (0xAC)
#define HI_NF_RB_MODE_OFFSET (0xB0)
#define HI_NFC_BADDR_D1_OFFSET (0xB4)
#define HI_NFC_BADDR_D2_OFFSET (0xB8)
#define HI_NFC_BADDR_D3_OFFSET (0xBC)
#define HI_NFC_BOOT_CFG_OFFSET (0xC4)
#define HI_NFC_OOB_SEL_OFFSET (0xC8)
#define HI_NFC_MEM_CTRL_OFFSET (0xCC)
#define HI_NFC_SYNC_TIMING_OFFSET (0xD0)
#define HI_NFC_DLL_CONTROL_OFFSET (0xD4)
#define HI_NFC_DLL_STATUS_OFFSET (0xD8)
typedef union
{
    struct
    {
        unsigned int op_mode : 1;
        unsigned int pagesize : 3;
        unsigned int bus_width : 1;
        unsigned int reserved_2 : 2;
        unsigned int cs_ctrl : 1;
        unsigned int rb_sel : 1;
        unsigned int ecc_type : 3;
        unsigned int reserved_1 : 1;
        unsigned int randomizer_en : 1;
        unsigned int nf_mode : 2;
        unsigned int reserved_0 : 16;
    } bits;
    unsigned int u32;
}HI_NFC_CON_T;
typedef union
{
    struct
    {
        unsigned int w_lcnt : 4;
        unsigned int r_lcnt : 4;
        unsigned int rw_hcnt : 4;
        unsigned int reserved : 20;
    } bits;
    unsigned int u32;
}HI_NFC_PWIDTH_T;
typedef union
{
    struct
    {
        unsigned int wait_ready_wait : 4;
        unsigned int cmd2_wait : 4;
        unsigned int rsv : 4;
        unsigned int addr_wait : 4;
        unsigned int cmd1_wait : 4;
        unsigned int frb_wait : 4;
        unsigned int reserved : 8;
    } bits;
    unsigned int u32;
}HI_NFC_OPIDLE_T;
typedef union
{
    struct
    {
        unsigned int cmd1 : 8;
        unsigned int cmd2 : 8;
        unsigned int read_status_cmd : 8;
        unsigned int reserved : 8;
    } bits;
    unsigned int u32;
}HI_NFC_CMD_T;
typedef union
{
    struct
    {
        unsigned int addr_l : 32;
    } bits;
    unsigned int u32;
}HI_NFC_ADDRL_T;
typedef union
{
    struct
    {
        unsigned int addr_h : 8;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_NFC_ADDRH_T;
typedef union
{
    struct
    {
        unsigned int nfc_data_num : 14;
        unsigned int reserved : 18;
    } bits;
    unsigned int u32;
}HI_NFC_DATA_NUM_T;
typedef union
{
    struct
    {
        unsigned int read_status_en : 1;
        unsigned int read_data_en : 1;
        unsigned int wait_ready_en : 1;
        unsigned int cmd2_en : 1;
        unsigned int write_data_en : 1;
        unsigned int addr_en : 1;
        unsigned int cmd1_en : 1;
        unsigned int nf_cs : 2;
        unsigned int address_cycles : 3;
        unsigned int read_id_en : 1;
        unsigned int rw_reg_en : 1;
        unsigned int reserved : 18;
    } bits;
    unsigned int u32;
}HI_NFC_OP_T;
typedef union
{
    struct
    {
        unsigned int nfc_ready : 1;
        unsigned int nf0_ready : 1;
        unsigned int nf1_ready : 1;
        unsigned int nf2_ready : 1;
        unsigned int nf3_ready : 1;
        unsigned int reserved_1 : 3;
        unsigned int nf_status : 8;
        unsigned int nfc_ecc_type : 3;
        unsigned int nfc_randomizer_en : 1;
        unsigned int reserved_0 : 12;
    } bits;
    unsigned int u32;
}HI_NFC_STATUS_T;
typedef union
{
    struct
    {
        unsigned int op_done_en : 1;
        unsigned int cs0_done_en : 1;
        unsigned int cs1_done_en : 1;
        unsigned int cs2_done_en : 1;
        unsigned int cs3_done_en : 1;
        unsigned int err_valid_en : 1;
        unsigned int err_invalid_en : 1;
        unsigned int ahb_op_en : 1;
        unsigned int wr_lock_en : 1;
        unsigned int dma_done_en : 1;
        unsigned int dma_err_en : 1;
        unsigned int reserved : 21;
    } bits;
    unsigned int u32;
}HI_NFC_INTEN_T;
typedef union
{
    struct
    {
        unsigned int op_done : 1;
        unsigned int cs0_done : 1;
        unsigned int cs1_done : 1;
        unsigned int cs2_done : 1;
        unsigned int cs3_done : 1;
        unsigned int err_valid : 1;
        unsigned int err_invalid : 1;
        unsigned int ahb_op_err : 1;
        unsigned int wr_lock_err : 1;
        unsigned int dma_done : 1;
        unsigned int dma_err : 1;
        unsigned int reserved : 21;
    } bits;
    unsigned int u32;
}HI_NFC_INTS_T;
typedef union
{
    struct
    {
        unsigned int op_done_clr : 1;
        unsigned int cs0_done_clr : 1;
        unsigned int cs1_done_clr : 1;
        unsigned int cs2_done_clr : 1;
        unsigned int cs3_done_clr : 1;
        unsigned int err_valid_clr : 1;
        unsigned int err_invalid_clr : 1;
        unsigned int ahb_op_err_clr : 1;
        unsigned int wr_lock_err_clr : 1;
        unsigned int dma_done_clr : 1;
        unsigned int dma_err_clr : 1;
        unsigned int reserved : 21;
    } bits;
    unsigned int u32;
}HI_NFC_INTCLR_T;
typedef union
{
    struct
    {
        unsigned int lock_down : 1;
        unsigned int global_lock_en : 1;
        unsigned int lock_en : 1;
        unsigned int lock_excmd_en : 1;
        unsigned int reserved : 28;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_addr0 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_SA0_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_addr1 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_SA1_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_addr2 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_SA2_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_addr3 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_SA3_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_eaddr0 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_EA0_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_eaddr1 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_EA1_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_eaddr2 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_EA2_T;
typedef union
{
    struct
    {
        unsigned int flash_lock_eaddr3 : 19;
        unsigned int flash_lock_cs : 2;
        unsigned int reserved : 11;
    } bits;
    unsigned int u32;
}HI_NFC_LOCK_EA3_T;
typedef union
{
    struct
    {
        unsigned int ex_pcmd0 : 8;
        unsigned int ex_pcmd1 : 8;
        unsigned int ex_pcmd2 : 8;
        unsigned int ex_pcmd3 : 8;
    } bits;
    unsigned int u32;
}HI_NFC_EXPCMD_T;
typedef union
{
    struct
    {
        unsigned int ex_bcmd0 : 8;
        unsigned int ex_bcmd1 : 8;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_NFC_EXBCMD_T;
typedef union
{
    struct
    {
        unsigned int enc_only : 1;
        unsigned int dec_only : 1;
        unsigned int ecc_mask : 1;
        unsigned int reserved_1 : 1;
        unsigned int bb_err : 1;
        unsigned int reserved_0 : 27;
    } bits;
    unsigned int u32;
}HI_NFC_ECC_TEST_T;
typedef union
{
    struct
    {
        unsigned int dma_start : 1;
        unsigned int dma_wr_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int burst4_en : 1;
        unsigned int burst8_en : 1;
        unsigned int burst16_en : 1;
        unsigned int dma_addr_num : 1;
        unsigned int dma_nf_cs : 2;
        unsigned int rsv : 1;
        unsigned int wr_cmd_disable : 1;
        unsigned int dma_rd_oob : 1;
        unsigned int reserved_0 : 19;
    } bits;
    unsigned int u32;
}HI_NFC_DMA_CTRL_T;
typedef union
{
    struct
    {
        unsigned int base_addr_d : 32;
    } bits;
    unsigned int u32;
}HI_NFC_BADDR_D_T;
typedef union
{
    struct
    {
        unsigned int base_addr_oob : 32;
    } bits;
    unsigned int u32;
}HI_NFC_BADDR_OOB_T;
typedef union
{
    struct
    {
        unsigned int reserved_1 : 16;
        unsigned int len_oob : 12;
        unsigned int reserved_0 : 4;
    } bits;
    unsigned int u32;
}HI_NFC_DMA_LEN_T;
typedef union
{
    struct
    {
        unsigned int data_rw_en : 1;
        unsigned int oob_rw_en : 1;
        unsigned int data_edc_en : 1;
        unsigned int oob_edc_en : 1;
        unsigned int reserved : 28;
    } bits;
    unsigned int u32;
}HI_NFC_OP_PARA_T;
typedef union
{
    struct
    {
        unsigned int version : 12;
        unsigned int reserved : 20;
    } bits;
    unsigned int u32;
}HI_NFC_VERSION_T;
typedef union
{
    struct
    {
        unsigned int last_flag : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_NFC_SEGMENT_ID_T;
typedef union
{
    struct
    {
        unsigned int empty_dbg : 24;
        unsigned int reserved : 8;
    } bits;
    unsigned int u32;
}HI_NFC_FIFO_EMPTY_T;
typedef union
{
    struct
    {
        unsigned int block_size : 2;
        unsigned int addr_num : 1;
        unsigned int rsv : 29;
    } bits;
    unsigned int u32;
}HI_NFC_BOOT_SET_T;
typedef union
{
    struct
    {
        unsigned int clk_gate_en : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_NF_LP_CTRL_T;
typedef union
{
    struct
    {
        unsigned int err_num0_buf0 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_ERR_NUM0_BUF0_T;
typedef union
{
    struct
    {
        unsigned int err_num1_buf0 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_ERR_NUM1_BUF0_T;
typedef union
{
    struct
    {
        unsigned int err_num0_buf1 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_ERR_NUM0_BUF1_T;
typedef union
{
    struct
    {
        unsigned int err_num1_buf1 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_ERR_NUM1_BUF1_T;
typedef union
{
    struct
    {
        unsigned int status : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_NF_RB_MODE_T;
typedef union
{
    struct
    {
        unsigned int base_addr_d1 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_BADDR_D1_T;
typedef union
{
    struct
    {
        unsigned int base_addr_d2 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_BADDR_D2_T;
typedef union
{
    struct
    {
        unsigned int base_addr_d3 : 32;
    } bits;
    unsigned int u32;
}HI_NFC_BADDR_D3_T;
typedef union
{
    struct
    {
        unsigned int randomizer_pad : 1;
        unsigned int page_size_pad : 3;
        unsigned int ecc_type_pad : 3;
        unsigned int block_size_pad : 2;
        unsigned int addr_num_pad : 1;
        unsigned int bus_width_pad : 1;
        unsigned int sync_nand_pad : 1;
        unsigned int reserved : 20;
    } bits;
    unsigned int u32;
}HI_NFC_BOOT_CFG_T;
typedef union
{
    struct
    {
        unsigned int oob_len_sel : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_NFC_OOB_SEL_T;
typedef union
{
    struct
    {
        unsigned int mem_ctrl : 5;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_NFC_MEM_CTRL_T;
typedef union
{
    struct
    {
        unsigned int rw_psth : 4;
        unsigned int post_wdqs : 4;
        unsigned int pre_wdqs : 4;
        unsigned int post_rdqs : 4;
        unsigned int pre_rdqs : 4;
        unsigned int t_dqz : 4;
        unsigned int t_cad : 4;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI_NFC_SYNC_TIMING_T;
typedef union
{
    struct
    {
        unsigned int dll_bypass : 1;
        unsigned int dll_stop : 1;
        unsigned int dll_slave_en : 1;
        unsigned int dll_mode : 1;
        unsigned int dll_tune : 4;
        unsigned int dll_ssel : 8;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_NFC_DLL_CONTROL_T;
typedef union
{
    struct
    {
        unsigned int dll_ready : 1;
        unsigned int dll_overflow : 1;
        unsigned int dll_lockrd : 1;
        unsigned int reserved_1 : 1;
        unsigned int mdly_tap : 8;
        unsigned int reserved_0 : 20;
    } bits;
    unsigned int u32;
}HI_NFC_DLL_STATUS_T;
HI_SET_GET(hi_nfc_con_op_mode,op_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_pagesize,pagesize,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_bus_width,bus_width,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_2,reserved_2,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_cs_ctrl,cs_ctrl,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_rb_sel,rb_sel,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_ecc_type,ecc_type,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_1,reserved_1,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_randomizer_en,randomizer_en,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_nf_mode,nf_mode,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_con_reserved_0,reserved_0,HI_NFC_CON_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CON_OFFSET)
HI_SET_GET(hi_nfc_pwidth_w_lcnt,w_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_r_lcnt,r_lcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_rw_hcnt,rw_hcnt,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_pwidth_reserved,reserved,HI_NFC_PWIDTH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_PWIDTH_OFFSET)
HI_SET_GET(hi_nfc_opidle_wait_ready_wait,wait_ready_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd2_wait,cmd2_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_rsv,rsv,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_addr_wait,addr_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_cmd1_wait,cmd1_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_frb_wait,frb_wait,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_opidle_reserved,reserved,HI_NFC_OPIDLE_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OPIDLE_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd1,cmd1,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_cmd2,cmd2,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_read_status_cmd,read_status_cmd,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_cmd_reserved,reserved,HI_NFC_CMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_CMD_OFFSET)
HI_SET_GET(hi_nfc_addrl_addr_l,addr_l,HI_NFC_ADDRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRL_OFFSET)
HI_SET_GET(hi_nfc_addrh_addr_h,addr_h,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_addrh_reserved,reserved,HI_NFC_ADDRH_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ADDRH_OFFSET)
HI_SET_GET(hi_nfc_data_num_nfc_data_num,nfc_data_num,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_data_num_reserved,reserved,HI_NFC_DATA_NUM_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DATA_NUM_OFFSET)
HI_SET_GET(hi_nfc_op_read_status_en,read_status_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_data_en,read_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_wait_ready_en,wait_ready_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd2_en,cmd2_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_write_data_en,write_data_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_addr_en,addr_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_cmd1_en,cmd1_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_nf_cs,nf_cs,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_address_cycles,address_cycles,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_read_id_en,read_id_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_rw_reg_en,rw_reg_en,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_op_reserved,reserved,HI_NFC_OP_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ready,nfc_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf0_ready,nf0_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf1_ready,nf1_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf2_ready,nf2_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf3_ready,nf3_ready,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_1,reserved_1,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nf_status,nf_status,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_ecc_type,nfc_ecc_type,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_nfc_randomizer_en,nfc_randomizer_en,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_status_reserved_0,reserved_0,HI_NFC_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_STATUS_OFFSET)
HI_SET_GET(hi_nfc_inten_op_done_en,op_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs0_done_en,cs0_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs1_done_en,cs1_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs2_done_en,cs2_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_cs3_done_en,cs3_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_valid_en,err_valid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_err_invalid_en,err_invalid_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_ahb_op_en,ahb_op_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_wr_lock_en,wr_lock_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_done_en,dma_done_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_dma_err_en,dma_err_en,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_inten_reserved,reserved,HI_NFC_INTEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTEN_OFFSET)
HI_SET_GET(hi_nfc_ints_op_done,op_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs0_done,cs0_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs1_done,cs1_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs2_done,cs2_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_cs3_done,cs3_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_valid,err_valid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_err_invalid,err_invalid,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_ahb_op_err,ahb_op_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_wr_lock_err,wr_lock_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_done,dma_done,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_dma_err,dma_err,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_ints_reserved,reserved,HI_NFC_INTS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTS_OFFSET)
HI_SET_GET(hi_nfc_intclr_op_done_clr,op_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs0_done_clr,cs0_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs1_done_clr,cs1_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs2_done_clr,cs2_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_cs3_done_clr,cs3_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_valid_clr,err_valid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_err_invalid_clr,err_invalid_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_ahb_op_err_clr,ahb_op_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_wr_lock_err_clr,wr_lock_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_done_clr,dma_done_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_dma_err_clr,dma_err_clr,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_intclr_reserved,reserved,HI_NFC_INTCLR_T,HI_NANDC_REGBASE_ADDR, HI_NFC_INTCLR_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_down,lock_down,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_global_lock_en,global_lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_en,lock_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_lock_excmd_en,lock_excmd_en,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_reserved,reserved,HI_NFC_LOCK_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_addr0,flash_lock_addr0,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa0_reserved,reserved,HI_NFC_LOCK_SA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA0_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_addr1,flash_lock_addr1,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa1_reserved,reserved,HI_NFC_LOCK_SA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA1_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_addr2,flash_lock_addr2,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa2_reserved,reserved,HI_NFC_LOCK_SA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA2_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_addr3,flash_lock_addr3,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_sa3_reserved,reserved,HI_NFC_LOCK_SA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_SA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_eaddr0,flash_lock_eaddr0,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea0_reserved,reserved,HI_NFC_LOCK_EA0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA0_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_eaddr1,flash_lock_eaddr1,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea1_reserved,reserved,HI_NFC_LOCK_EA1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA1_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_eaddr2,flash_lock_eaddr2,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea2_reserved,reserved,HI_NFC_LOCK_EA2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA2_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_eaddr3,flash_lock_eaddr3,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_flash_lock_cs,flash_lock_cs,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_lock_ea3_reserved,reserved,HI_NFC_LOCK_EA3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_LOCK_EA3_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd0,ex_pcmd0,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd1,ex_pcmd1,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd2,ex_pcmd2,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_expcmd_ex_pcmd3,ex_pcmd3,HI_NFC_EXPCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXPCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd0,ex_bcmd0,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_ex_bcmd1,ex_bcmd1,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_exbcmd_reserved,reserved,HI_NFC_EXBCMD_T,HI_NANDC_REGBASE_ADDR, HI_NFC_EXBCMD_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_enc_only,enc_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_dec_only,dec_only,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_ecc_mask,ecc_mask,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_1,reserved_1,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_bb_err,bb_err,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_ecc_test_reserved_0,reserved_0,HI_NFC_ECC_TEST_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ECC_TEST_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_start,dma_start,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_wr_en,dma_wr_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_1,reserved_1,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst4_en,burst4_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst8_en,burst8_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_burst16_en,burst16_en,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_addr_num,dma_addr_num,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_nf_cs,dma_nf_cs,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_rsv,rsv,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_wr_cmd_disable,wr_cmd_disable,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_dma_rd_oob,dma_rd_oob,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_dma_ctrl_reserved_0,reserved_0,HI_NFC_DMA_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_CTRL_OFFSET)
HI_SET_GET(hi_nfc_baddr_d_base_addr_d,base_addr_d,HI_NFC_BADDR_D_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D_OFFSET)
HI_SET_GET(hi_nfc_baddr_oob_base_addr_oob,base_addr_oob,HI_NFC_BADDR_OOB_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_OOB_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_1,reserved_1,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_len_oob,len_oob,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_dma_len_reserved_0,reserved_0,HI_NFC_DMA_LEN_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DMA_LEN_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_rw_en,data_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_rw_en,oob_rw_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_data_edc_en,data_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_oob_edc_en,oob_edc_en,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_op_para_reserved,reserved,HI_NFC_OP_PARA_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OP_PARA_OFFSET)
HI_SET_GET(hi_nfc_version_version,version,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_version_reserved,reserved,HI_NFC_VERSION_T,HI_NANDC_REGBASE_ADDR, HI_NFC_VERSION_OFFSET)
HI_SET_GET(hi_nfc_segment_id_last_flag,last_flag,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_segment_id_reserved,reserved,HI_NFC_SEGMENT_ID_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SEGMENT_ID_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_empty_dbg,empty_dbg,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_fifo_empty_reserved,reserved,HI_NFC_FIFO_EMPTY_T,HI_NANDC_REGBASE_ADDR, HI_NFC_FIFO_EMPTY_OFFSET)
HI_SET_GET(hi_nfc_boot_set_block_size,block_size,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_addr_num,addr_num,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nfc_boot_set_rsv,rsv,HI_NFC_BOOT_SET_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_SET_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_clk_gate_en,clk_gate_en,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nf_lp_ctrl_reserved,reserved,HI_NF_LP_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NF_LP_CTRL_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf0_err_num0_buf0,err_num0_buf0,HI_NFC_ERR_NUM0_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf0_err_num1_buf0,err_num1_buf0,HI_NFC_ERR_NUM1_BUF0_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF0_OFFSET)
HI_SET_GET(hi_nfc_err_num0_buf1_err_num0_buf1,err_num0_buf1,HI_NFC_ERR_NUM0_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM0_BUF1_OFFSET)
HI_SET_GET(hi_nfc_err_num1_buf1_err_num1_buf1,err_num1_buf1,HI_NFC_ERR_NUM1_BUF1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_ERR_NUM1_BUF1_OFFSET)
HI_SET_GET(hi_nf_rb_mode_status,status,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nf_rb_mode_reserved,reserved,HI_NF_RB_MODE_T,HI_NANDC_REGBASE_ADDR, HI_NF_RB_MODE_OFFSET)
HI_SET_GET(hi_nfc_baddr_d1_base_addr_d1,base_addr_d1,HI_NFC_BADDR_D1_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D1_OFFSET)
HI_SET_GET(hi_nfc_baddr_d2_base_addr_d2,base_addr_d2,HI_NFC_BADDR_D2_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D2_OFFSET)
HI_SET_GET(hi_nfc_baddr_d3_base_addr_d3,base_addr_d3,HI_NFC_BADDR_D3_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BADDR_D3_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_randomizer_pad,randomizer_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_page_size_pad,page_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_ecc_type_pad,ecc_type_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_block_size_pad,block_size_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_addr_num_pad,addr_num_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_bus_width_pad,bus_width_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_sync_nand_pad,sync_nand_pad,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_boot_cfg_reserved,reserved,HI_NFC_BOOT_CFG_T,HI_NANDC_REGBASE_ADDR, HI_NFC_BOOT_CFG_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_oob_len_sel,oob_len_sel,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_oob_sel_reserved,reserved,HI_NFC_OOB_SEL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_OOB_SEL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_mem_ctrl,mem_ctrl,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_mem_ctrl_reserved,reserved,HI_NFC_MEM_CTRL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_MEM_CTRL_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_rw_psth,rw_psth,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_wdqs,post_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_wdqs,pre_wdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_post_rdqs,post_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_pre_rdqs,pre_rdqs,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_dqz,t_dqz,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_t_cad,t_cad,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_sync_timing_reserved,reserved,HI_NFC_SYNC_TIMING_T,HI_NANDC_REGBASE_ADDR, HI_NFC_SYNC_TIMING_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_bypass,dll_bypass,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_stop,dll_stop,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_slave_en,dll_slave_en,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_mode,dll_mode,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_tune,dll_tune,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_dll_ssel,dll_ssel,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_control_reserved,reserved,HI_NFC_DLL_CONTROL_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_CONTROL_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_ready,dll_ready,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_overflow,dll_overflow,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_dll_lockrd,dll_lockrd,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_1,reserved_1,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_mdly_tap,mdly_tap,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
HI_SET_GET(hi_nfc_dll_status_reserved_0,reserved_0,HI_NFC_DLL_STATUS_T,HI_NANDC_REGBASE_ADDR, HI_NFC_DLL_STATUS_OFFSET)
#endif
