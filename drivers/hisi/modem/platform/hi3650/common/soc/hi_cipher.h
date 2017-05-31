#ifndef __HI_CIPHER_H__
#define __HI_CIPHER_H__ 
#if 0
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#endif
#define HI_CIPHER_CTRL_OFFSET (0x0)
#define HI_CIPHER_PRI_OFFSET (0x4)
#define HI_TOTAL_BD_NUM_OFFSET (0x8)
#define HI_INVALID_BD_NUM_OFFSET (0xC)
#define HI_DMA_CFG_OFFSET (0x14)
#define HI_CIPHER_VERSION_OFFSET (0x18)
#define HI_TEST_REG0_OFFSET (0x20)
#define HI_TEST_REG1_OFFSET (0x24)
#define HI_TEST_REG2_OFFSET (0x28)
#define HI_CIPHER_DEBUG20_OFFSET (0x2C)
#define HI_CIPHER_DEBUG0_OFFSET (0x30)
#define HI_CIPHER_DEBUG1_OFFSET (0x34)
#define HI_CIPHER_DEBUG2_OFFSET (0x38)
#define HI_CIPHER_DEBUG3_OFFSET (0x3C)
#define HI_CIPHER_DEBUG4_OFFSET (0x40)
#define HI_CIPHER_DEBUG5_OFFSET (0x44)
#define HI_CIPHER_DEBUG6_OFFSET (0x48)
#define HI_CIPHER_DEBUG7_OFFSET (0x4C)
#define HI_CIPHER_DEBUG8_OFFSET (0x50)
#define HI_CIPHER_DEBUG9_OFFSET (0x54)
#define HI_CIPHER_DEBUG10_OFFSET (0x58)
#define HI_CIPHER_DEBUG11_OFFSET (0x5C)
#define HI_CIPHER_DEBUG12_OFFSET (0x60)
#define HI_CIPHER_DEBUG13_OFFSET (0x64)
#define HI_CIPHER_DEBUG14_OFFSET (0x68)
#define HI_CIPHER_DEBUG15_OFFSET (0x6C)
#define HI_CIPHER_DEBUG16_OFFSET (0x70)
#define HI_CIPHER_DEBUG17_OFFSET (0x74)
#define HI_CIPHER_DEBUG18_OFFSET (0x78)
#define HI_CIPHER_DEBUG19_OFFSET (0x7C)
#define HI_CH0_SOFTRESET_OFFSET (0x80)
#define HI_CH0_EN_OFFSET (0x84)
#define HI_CH0_CONFIG_OFFSET (0x88)
#define HI_CH0_BDQ_BADDR_OFFSET (0x8C)
#define HI_CH0_BDQ_SIZE_OFFSET (0x90)
#define HI_CH0_BDQ_PTR_OFFSET (0x94)
#define HI_CH0_BDQ_RADDR_OFFSET (0x98)
#define HI_CH0_BDQ_WADDR_OFFSET (0x9C)
#define HI_CH0_BD_NUM_OFFSET (0xA0)
#define HI_CH0_INVALID_BD_NUM_OFFSET (0xA4)
#define HI_CH1_SOFTRESET_OFFSET (0x100)
#define HI_CH1_EN_OFFSET (0x104)
#define HI_CH1_CONFIG_OFFSET (0x108)
#define HI_CH1_BDQ_BADDR_OFFSET (0x10C)
#define HI_CH1_BDQ_SIZE_OFFSET (0x110)
#define HI_CH1_BDQ_PTR_OFFSET (0x114)
#define HI_CH1_BDQ_RADDR_OFFSET (0x118)
#define HI_CH1_BDQ_WADDR_OFFSET (0x11C)
#define HI_CH1_BD_NUM_OFFSET (0x120)
#define HI_CH1_INVALID_BD_NUM_OFFSET (0x124)
#define HI_CH2_SOFTRESET_OFFSET (0x180)
#define HI_CH2_EN_OFFSET (0x184)
#define HI_CH2_CONFIG_OFFSET (0x188)
#define HI_CH2_BDQ_BADDR_OFFSET (0x18C)
#define HI_CH2_BDQ_SIZE_OFFSET (0x190)
#define HI_CH2_BDQ_PTR_OFFSET (0x194)
#define HI_CH2_BDQ_RADDR_OFFSET (0x198)
#define HI_CH2_BDQ_WADDR_OFFSET (0x19C)
#define HI_CH2_BD_NUM_OFFSET (0x1A0)
#define HI_CH2_INVALID_BD_NUM_OFFSET (0x1A4)
#define HI_CH3_SOFTRESET_OFFSET (0x200)
#define HI_CH3_EN_OFFSET (0x204)
#define HI_CH3_CONFIG_OFFSET (0x208)
#define HI_CH3_BDQ_BADDR_OFFSET (0x20C)
#define HI_CH3_BDQ_SIZE_OFFSET (0x210)
#define HI_CH3_BDQ_PTR_OFFSET (0x214)
#define HI_CH3_BDQ_RADDR_OFFSET (0x218)
#define HI_CH3_BDQ_WADDR_OFFSET (0x21C)
#define HI_CH3_BD_NUM_OFFSET (0x220)
#define HI_CH3_INVALID_BD_NUM_OFFSET (0x224)
#define HI_CH4_SOFTRESET_OFFSET (0x280)
#define HI_CH4_EN_OFFSET (0x284)
#define HI_CH4_CONFIG_OFFSET (0x288)
#define HI_CH4_BDQ_BADDR_OFFSET (0x28C)
#define HI_CH4_BDQ_SIZE_OFFSET (0x290)
#define HI_CH4_BDQ_PTR_OFFSET (0x294)
#define HI_CH4_BDQ_RADDR_OFFSET (0x298)
#define HI_CH4_BDQ_WADDR_OFFSET (0x29C)
#define HI_CH4_BD_NUM_OFFSET (0x2A0)
#define HI_CH4_INVALID_BD_NUM_OFFSET (0x2A4)
#define HI_CH_INT_PKT_INTERVAL_OFFSET (0x400)
#define HI_CIPHER_INT_STATUS_OFFSET (0x404)
#define HI_CIPHER_INT0_STATUS_OFFSET (0x408)
#define HI_CIPHER_INT0_MASK_OFFSET (0x40C)
#define HI_CIPHER_INT0_MSTATUS_OFFSET (0x410)
#define HI_CIPHER_INT1_STATUS_OFFSET (0x414)
#define HI_CIPHER_INT1_MASK_OFFSET (0x418)
#define HI_CIPHER_INT1_MSTATUS_OFFSET (0x41C)
#define HI_CIPHER_INT2_STATUS_OFFSET (0x420)
#define HI_CIPHER_INT2_MASK_OFFSET (0x424)
#define HI_CIPHER_INT2_MSTATUS_OFFSET (0x428)
#define HI_CH0_RDQ_BADDR_OFFSET (0x480)
#define HI_CH0_RDQ_SIZE_OFFSET (0x484)
#define HI_CH0_RDQ_PTR_OFFSET (0x488)
#define HI_CH0_RDQ_RADDR_OFFSET (0x48C)
#define HI_CH0_RDQ_WADDR_OFFSET (0x490)
#define HI_CH1_RDQ_BADDR_OFFSET (0x500)
#define HI_CH1_RDQ_SIZE_OFFSET (0x504)
#define HI_CH1_RDQ_PTR_OFFSET (0x508)
#define HI_CH1_RDQ_RADDR_OFFSET (0x50C)
#define HI_CH1_RDQ_WADDR_OFFSET (0x510)
#define HI_CH2_RDQ_BADDR_OFFSET (0x580)
#define HI_CH2_RDQ_SIZE_OFFSET (0x584)
#define HI_CH2_RDQ_PTR_OFFSET (0x588)
#define HI_CH2_RDQ_RADDR_OFFSET (0x58C)
#define HI_CH2_RDQ_WADDR_OFFSET (0x590)
#define HI_CH3_RDQ_BADDR_OFFSET (0x600)
#define HI_CH3_RDQ_SIZE_OFFSET (0x604)
#define HI_CH3_RDQ_PTR_OFFSET (0x608)
#define HI_CH3_RDQ_RADDR_OFFSET (0x60C)
#define HI_CH3_RDQ_WADDR_OFFSET (0x610)
#define HI_CH4_RDQ_BADDR_OFFSET (0x680)
#define HI_CH4_RDQ_SIZE_OFFSET (0x684)
#define HI_CH4_RDQ_PTR_OFFSET (0x688)
#define HI_CH4_RDQ_RADDR_OFFSET (0x68C)
#define HI_CH4_RDQ_WADDR_OFFSET (0x690)
#define HI_KEY_RAM_OFFSET (0x800)
typedef union
{
    struct
    {
        unsigned int cipher_srst : 1;
        unsigned int cipher_cg_en : 1;
        unsigned int reserved : 29;
        unsigned int cipher_busy : 1;
    } bits;
    unsigned int u32;
}HI_CIPHER_CTRL_T;
typedef union
{
    struct
    {
        unsigned int idata_threshold : 28;
        unsigned int ch_pri : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI_CIPHER_PRI_T;
typedef union
{
    struct
    {
        unsigned int total_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_TOTAL_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int rd_id : 3;
        unsigned int obuf_id : 3;
        unsigned int ocd_id : 3;
        unsigned int icd_id : 3;
        unsigned int ibuf_id : 3;
        unsigned int reserved_1 : 1;
        unsigned int rd_pri : 3;
        unsigned int obuf_pri : 3;
        unsigned int ocd_pri : 3;
        unsigned int icd_pri : 3;
        unsigned int ibuf_pri : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI_DMA_CFG_T;
typedef union
{
    struct
    {
        unsigned int spram_mem_ctrl : 16;
        unsigned int atpram_mem_ctrl : 16;
    } bits;
    unsigned int u32;
}HI_TEST_REG0_T;
typedef union
{
    struct
    {
        unsigned int aes_key_cov : 1;
        unsigned int snow3g_key_cov : 1;
        unsigned int cipher_dma_ctrl : 6;
        unsigned int zuc_key_cov : 1;
        unsigned int reserved_2 : 1;
        unsigned int snow3g_iv_cov : 1;
        unsigned int reserved_1 : 5;
        unsigned int ibuf_dma_req_len : 5;
        unsigned int dma_opt : 1;
        unsigned int reserved_0 : 10;
    } bits;
    unsigned int u32;
}HI_TEST_REG1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_TEST_REG2_T;
typedef union
{
    struct
    {
        unsigned int dma_rd_gnt : 1;
        unsigned int dma_ocd_gnt : 1;
        unsigned int dma_icd_gnt : 1;
        unsigned int dma_obuf_gnt : 1;
        unsigned int dma_ibuf_gnt : 1;
        unsigned int reserved_3 : 3;
        unsigned int dma_rd_req : 1;
        unsigned int dma_ocd_req : 1;
        unsigned int dma_icd_req : 1;
        unsigned int dma_obuf_req : 1;
        unsigned int dma_ibuf_req : 1;
        unsigned int reserved_2 : 3;
        unsigned int dma_rd_idle : 1;
        unsigned int dma_ocd_idle : 1;
        unsigned int dma_icd_idle : 1;
        unsigned int dma_obuf_idle : 1;
        unsigned int dma_ibuf_idle : 1;
        unsigned int reserved_1 : 3;
        unsigned int dma_rd_trans_end : 1;
        unsigned int dma_ocd_last_read : 1;
        unsigned int dma_icd_last_read : 1;
        unsigned int dma_obuf_trans_end : 1;
        unsigned int dma_ibuf_last_read : 1;
        unsigned int reserved_0 : 3;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG20_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG0_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG3_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG4_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG5_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG6_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG7_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG8_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG9_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG10_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG11_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG12_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG13_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG14_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG15_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG16_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG17_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG18_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_DEBUG19_T;
typedef union
{
    struct
    {
        unsigned int ch_srst : 1;
        unsigned int ch_bdq_clear : 1;
        unsigned int ch_rdq_clear : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CH0_SOFTRESET_T;
typedef union
{
    struct
    {
        unsigned int ch_en : 1;
        unsigned int reserved : 29;
        unsigned int pack_en : 1;
        unsigned int ch_busy : 1;
    } bits;
    unsigned int u32;
}HI_CH0_EN_T;
typedef union
{
    struct
    {
        unsigned int iv_sel : 1;
        unsigned int iv_num : 1;
        unsigned int rdq_ctrl : 2;
        unsigned int reserved_1 : 1;
        unsigned int ufield_len : 2;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_CH0_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH0_BDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH0_BDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 4;
        unsigned int ch_bdq_empty : 1;
        unsigned int ch_bdq_full : 1;
    } bits;
    unsigned int u32;
}HI_CH0_BDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH0_BDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH0_BDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int ch0_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH0_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch0_invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH0_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch_srst : 1;
        unsigned int ch_bdq_clear : 1;
        unsigned int ch_rdq_clear : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CH1_SOFTRESET_T;
typedef union
{
    struct
    {
        unsigned int ch_en : 1;
        unsigned int reserved : 29;
        unsigned int pack_en : 1;
        unsigned int ch_busy : 1;
    } bits;
    unsigned int u32;
}HI_CH1_EN_T;
typedef union
{
    struct
    {
        unsigned int iv_sel : 1;
        unsigned int iv_num : 1;
        unsigned int rdq_ctrl : 2;
        unsigned int reserved_1 : 1;
        unsigned int ufield_len : 2;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_CH1_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH1_BDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH1_BDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 4;
        unsigned int ch1_bdq_empty : 1;
        unsigned int ch1_bdq_full : 1;
    } bits;
    unsigned int u32;
}HI_CH1_BDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH1_BDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH1_BDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int ch1_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH1_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch1_invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH1_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch_srst : 1;
        unsigned int ch_bdq_clear : 1;
        unsigned int ch_rdq_clear : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CH2_SOFTRESET_T;
typedef union
{
    struct
    {
        unsigned int ch_en : 1;
        unsigned int reserved : 29;
        unsigned int pack_en : 1;
        unsigned int ch_busy : 1;
    } bits;
    unsigned int u32;
}HI_CH2_EN_T;
typedef union
{
    struct
    {
        unsigned int iv_sel : 1;
        unsigned int iv_num : 1;
        unsigned int rdq_ctrl : 2;
        unsigned int reserved_1 : 1;
        unsigned int ufield_len : 2;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_CH2_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH2_BDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH2_BDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 4;
        unsigned int ch2_bdq_empty : 1;
        unsigned int ch2_bdq_full : 1;
    } bits;
    unsigned int u32;
}HI_CH2_BDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH2_BDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH2_BDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int ch2_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH2_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch2_invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH2_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch_srst : 1;
        unsigned int ch_bdq_clear : 1;
        unsigned int ch_rdq_clear : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CH3_SOFTRESET_T;
typedef union
{
    struct
    {
        unsigned int ch_en : 1;
        unsigned int reserved : 29;
        unsigned int pack_en : 1;
        unsigned int ch_busy : 1;
    } bits;
    unsigned int u32;
}HI_CH3_EN_T;
typedef union
{
    struct
    {
        unsigned int iv_sel : 1;
        unsigned int iv_num : 1;
        unsigned int rdq_ctrl : 2;
        unsigned int reserved_1 : 1;
        unsigned int ufield_len : 2;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_CH3_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH3_BDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH3_BDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 4;
        unsigned int ch3_bdq_empty : 1;
        unsigned int ch3_bdq_full : 1;
    } bits;
    unsigned int u32;
}HI_CH3_BDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH3_BDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH3_BDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int ch3_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH3_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch3_invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH3_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch_srst : 1;
        unsigned int ch_bdq_clear : 1;
        unsigned int ch_rdq_clear : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CH4_SOFTRESET_T;
typedef union
{
    struct
    {
        unsigned int ch_en : 1;
        unsigned int reserved : 29;
        unsigned int pack_en : 1;
        unsigned int ch_busy : 1;
    } bits;
    unsigned int u32;
}HI_CH4_EN_T;
typedef union
{
    struct
    {
        unsigned int iv_sel : 1;
        unsigned int iv_num : 1;
        unsigned int rdq_ctrl : 2;
        unsigned int reserved_1 : 1;
        unsigned int ufield_len : 2;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_CH4_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH4_BDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH4_BDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 4;
        unsigned int ch4_bdq_empty : 1;
        unsigned int ch4_bdq_full : 1;
    } bits;
    unsigned int u32;
}HI_CH4_BDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH4_BDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int addr : 32;
    } bits;
    unsigned int u32;
}HI_CH4_BDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int ch4_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH4_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch4_invalid_bd_num : 32;
    } bits;
    unsigned int u32;
}HI_CH4_INVALID_BD_NUM_T;
typedef union
{
    struct
    {
        unsigned int ch0_pkt_num : 4;
        unsigned int ch1_pkt_num : 4;
        unsigned int ch2_pkt_num : 4;
        unsigned int ch3_pkt_num : 4;
        unsigned int timeout_time : 9;
        unsigned int ch4_pkt_num : 4;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI_CH_INT_PKT_INTERVAL_T;
typedef union
{
    struct
    {
        unsigned int cipher_int0 : 1;
        unsigned int cipher_int1 : 1;
        unsigned int cipher_int2 : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT_STATUS_T;
typedef union
{
    struct
    {
        unsigned int ch0_bdq_full : 1;
        unsigned int ch0_rdq_full : 1;
        unsigned int ch0_nbd_done : 1;
        unsigned int ch0_bd_done : 1;
        unsigned int ch0_allbd_done : 1;
        unsigned int ch0_integrity_err : 1;
        unsigned int reserved_3 : 2;
        unsigned int ch1_bdq_full : 1;
        unsigned int ch1_rdq_full : 1;
        unsigned int ch1_nbd_done : 1;
        unsigned int ch1_bd_done : 1;
        unsigned int ch1_allbd_done : 1;
        unsigned int ch1_integrity_err : 1;
        unsigned int reserved_2 : 2;
        unsigned int ch2_bdq_full : 1;
        unsigned int ch2_rdq_full : 1;
        unsigned int ch2_nbd_done : 1;
        unsigned int ch2_bd_done : 1;
        unsigned int ch2_allbd_done : 1;
        unsigned int ch2_integrity_err : 1;
        unsigned int reserved_1 : 2;
        unsigned int ch3_bdq_full : 1;
        unsigned int ch3_rdq_full : 1;
        unsigned int ch3_nbd_done : 1;
        unsigned int ch3_bd_done : 1;
        unsigned int ch3_allbd_done : 1;
        unsigned int ch3_integrity_err : 1;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT0_STATUS_T;
typedef union
{
    struct
    {
        unsigned int int0_mask : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT0_MASK_T;
typedef union
{
    struct
    {
        unsigned int int0_mstatus : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT0_MSTATUS_T;
typedef union
{
    struct
    {
        unsigned int ch0_bdq_empty : 1;
        unsigned int ch0_rdq_empty : 1;
        unsigned int ch0_timeout : 1;
        unsigned int reserved_3 : 5;
        unsigned int ch1_bdq_empty : 1;
        unsigned int ch1_rdq_empty : 1;
        unsigned int ch1_timeout : 1;
        unsigned int reserved_2 : 5;
        unsigned int ch2_bdq_empty : 1;
        unsigned int ch2_rdq_empty : 1;
        unsigned int ch2_timeout : 1;
        unsigned int reserved_1 : 5;
        unsigned int ch3_bdq_empty : 1;
        unsigned int ch3_rdq_empty : 1;
        unsigned int ch3_timeout : 1;
        unsigned int reserved_0 : 5;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT1_STATUS_T;
typedef union
{
    struct
    {
        unsigned int int1_mask : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT1_MASK_T;
typedef union
{
    struct
    {
        unsigned int int1_mstatus : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT1_MSTATUS_T;
typedef union
{
    struct
    {
        unsigned int ch4_bdq_full : 1;
        unsigned int ch4_rdq_full : 1;
        unsigned int ch4_nbd_done : 1;
        unsigned int ch4_bd_done : 1;
        unsigned int ch4_allbd_done : 1;
        unsigned int ch4_bdq_empty : 1;
        unsigned int ch4_rdq_empty : 1;
        unsigned int ch4_timeout : 1;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT2_STATUS_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT2_MASK_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_CIPHER_INT2_MSTATUS_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH0_RDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH0_RDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_CH0_RDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int raddr : 32;
    } bits;
    unsigned int u32;
}HI_CH0_RDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int waddr : 32;
    } bits;
    unsigned int u32;
}HI_CH0_RDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH1_RDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH1_RDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_CH1_RDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int raddr : 32;
    } bits;
    unsigned int u32;
}HI_CH1_RDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int waddr : 32;
    } bits;
    unsigned int u32;
}HI_CH1_RDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH2_RDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH2_RDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_CH2_RDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int raddr : 32;
    } bits;
    unsigned int u32;
}HI_CH2_RDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int waddr : 32;
    } bits;
    unsigned int u32;
}HI_CH2_RDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH3_RDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH3_RDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_CH3_RDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int raddr : 32;
    } bits;
    unsigned int u32;
}HI_CH3_RDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int waddr : 32;
    } bits;
    unsigned int u32;
}HI_CH3_RDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int base_addr_l : 3;
        unsigned int base_addr : 29;
    } bits;
    unsigned int u32;
}HI_CH4_RDQ_BADDR_T;
typedef union
{
    struct
    {
        unsigned int size : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_CH4_RDQ_SIZE_T;
typedef union
{
    struct
    {
        unsigned int wptr : 10;
        unsigned int reserved_1 : 6;
        unsigned int rptr : 10;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_CH4_RDQ_PTR_T;
typedef union
{
    struct
    {
        unsigned int raddr : 32;
    } bits;
    unsigned int u32;
}HI_CH4_RDQ_RADDR_T;
typedef union
{
    struct
    {
        unsigned int waddr : 32;
    } bits;
    unsigned int u32;
}HI_CH4_RDQ_WADDR_T;
typedef union
{
    struct
    {
        unsigned int key : 32;
    } bits;
    unsigned int u32;
}HI_KEY_RAM_T;
#if 0
HI_SET_GET(hi_cipher_ctrl_cipher_srst,cipher_srst,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_cg_en,cipher_cg_en,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_reserved,reserved,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_ctrl_cipher_busy,cipher_busy,HI_CIPHER_CTRL_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_CTRL_OFFSET)
HI_SET_GET(hi_cipher_pri_idata_threshold,idata_threshold,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_ch_pri,ch_pri,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_cipher_pri_reserved,reserved,HI_CIPHER_PRI_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_PRI_OFFSET)
HI_SET_GET(hi_total_bd_num_total_bd_num,total_bd_num,HI_TOTAL_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_TOTAL_BD_NUM_OFFSET)
HI_SET_GET(hi_invalid_bd_num_invalid_bd_num,invalid_bd_num,HI_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_id,rd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_id,obuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_id,ocd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_id,icd_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_id,ibuf_id,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_1,reserved_1,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_rd_pri,rd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_obuf_pri,obuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ocd_pri,ocd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_icd_pri,icd_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_ibuf_pri,ibuf_pri,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_dma_cfg_reserved_0,reserved_0,HI_DMA_CFG_T,HI_CIPHER_BASE_ADDR, HI_DMA_CFG_OFFSET)
HI_SET_GET(hi_test_reg0_spram_mem_ctrl,spram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg0_atpram_mem_ctrl,atpram_mem_ctrl,HI_TEST_REG0_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG0_OFFSET)
HI_SET_GET(hi_test_reg1_aes_key_cov,aes_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_key_cov,snow3g_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_cipher_dma_ctrl,cipher_dma_ctrl,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_zuc_key_cov,zuc_key_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_2,reserved_2,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_snow3g_iv_cov,snow3g_iv_cov,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_1,reserved_1,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_ibuf_dma_req_len,ibuf_dma_req_len,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_dma_opt,dma_opt,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg1_reserved_0,reserved_0,HI_TEST_REG1_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG1_OFFSET)
HI_SET_GET(hi_test_reg2_reserved,reserved,HI_TEST_REG2_T,HI_CIPHER_BASE_ADDR, HI_TEST_REG2_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_gnt,dma_rd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_gnt,dma_ocd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_gnt,dma_icd_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_gnt,dma_obuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_gnt,dma_ibuf_gnt,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_3,reserved_3,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_req,dma_rd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_req,dma_ocd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_req,dma_icd_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_req,dma_obuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_req,dma_ibuf_req,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_2,reserved_2,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_idle,dma_rd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_idle,dma_ocd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_idle,dma_icd_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_idle,dma_obuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_idle,dma_ibuf_idle,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_1,reserved_1,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_rd_trans_end,dma_rd_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ocd_last_read,dma_ocd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_icd_last_read,dma_icd_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_obuf_trans_end,dma_obuf_trans_end,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_dma_ibuf_last_read,dma_ibuf_last_read,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug20_reserved_0,reserved_0,HI_CIPHER_DEBUG20_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG20_OFFSET)
HI_SET_GET(hi_cipher_debug0_reserved,reserved,HI_CIPHER_DEBUG0_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG0_OFFSET)
HI_SET_GET(hi_cipher_debug1_reserved,reserved,HI_CIPHER_DEBUG1_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG1_OFFSET)
HI_SET_GET(hi_cipher_debug2_reserved,reserved,HI_CIPHER_DEBUG2_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG2_OFFSET)
HI_SET_GET(hi_cipher_debug3_reserved,reserved,HI_CIPHER_DEBUG3_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG3_OFFSET)
HI_SET_GET(hi_cipher_debug4_reserved,reserved,HI_CIPHER_DEBUG4_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG4_OFFSET)
HI_SET_GET(hi_cipher_debug5_reserved,reserved,HI_CIPHER_DEBUG5_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG5_OFFSET)
HI_SET_GET(hi_cipher_debug6_reserved,reserved,HI_CIPHER_DEBUG6_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG6_OFFSET)
HI_SET_GET(hi_cipher_debug7_reserved,reserved,HI_CIPHER_DEBUG7_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG7_OFFSET)
HI_SET_GET(hi_cipher_debug8_reserved,reserved,HI_CIPHER_DEBUG8_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG8_OFFSET)
HI_SET_GET(hi_cipher_debug9_reserved,reserved,HI_CIPHER_DEBUG9_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG9_OFFSET)
HI_SET_GET(hi_cipher_debug10_reserved,reserved,HI_CIPHER_DEBUG10_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG10_OFFSET)
HI_SET_GET(hi_cipher_debug11_reserved,reserved,HI_CIPHER_DEBUG11_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG11_OFFSET)
HI_SET_GET(hi_cipher_debug12_reserved,reserved,HI_CIPHER_DEBUG12_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG12_OFFSET)
HI_SET_GET(hi_cipher_debug13_reserved,reserved,HI_CIPHER_DEBUG13_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG13_OFFSET)
HI_SET_GET(hi_cipher_debug14_reserved,reserved,HI_CIPHER_DEBUG14_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG14_OFFSET)
HI_SET_GET(hi_cipher_debug15_reserved,reserved,HI_CIPHER_DEBUG15_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG15_OFFSET)
HI_SET_GET(hi_cipher_debug16_reserved,reserved,HI_CIPHER_DEBUG16_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG16_OFFSET)
HI_SET_GET(hi_cipher_debug17_reserved,reserved,HI_CIPHER_DEBUG17_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG17_OFFSET)
HI_SET_GET(hi_cipher_debug18_reserved,reserved,HI_CIPHER_DEBUG18_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG18_OFFSET)
HI_SET_GET(hi_cipher_debug19_reserved,reserved,HI_CIPHER_DEBUG19_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_DEBUG19_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_srst,ch_srst,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_softreset_reserved,reserved,HI_CH0_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH0_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch0_en_ch_en,ch_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_reserved,reserved,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_pack_en,pack_en,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_en_ch_busy,ch_busy,HI_CH0_EN_T,HI_CIPHER_BASE_ADDR, HI_CH0_EN_OFFSET)
HI_SET_GET(hi_ch0_config_iv_sel,iv_sel,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_iv_num,iv_num,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_rdq_ctrl,rdq_ctrl,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_1,reserved_1,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_ufield_len,ufield_len,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_config_reserved_0,reserved_0,HI_CH0_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH0_CONFIG_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr_l,base_addr_l,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_baddr_base_addr,base_addr,HI_CH0_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_size,size,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_size_reserved,reserved,HI_CH0_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_wptr,wptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_1,reserved_1,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_rptr,rptr,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_reserved_0,reserved_0,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_empty,ch_bdq_empty,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_ptr_ch_bdq_full,ch_bdq_full,HI_CH0_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_bdq_raddr_addr,addr,HI_CH0_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_bdq_waddr_addr,addr,HI_CH0_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch0_bd_num_ch0_bd_num,ch0_bd_num,HI_CH0_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_BD_NUM_OFFSET)
HI_SET_GET(hi_ch0_invalid_bd_num_ch0_invalid_bd_num,ch0_invalid_bd_num,HI_CH0_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH0_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_srst,ch_srst,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_softreset_reserved,reserved,HI_CH1_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH1_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch1_en_ch_en,ch_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_reserved,reserved,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_pack_en,pack_en,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_en_ch_busy,ch_busy,HI_CH1_EN_T,HI_CIPHER_BASE_ADDR, HI_CH1_EN_OFFSET)
HI_SET_GET(hi_ch1_config_iv_sel,iv_sel,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_iv_num,iv_num,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_rdq_ctrl,rdq_ctrl,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_1,reserved_1,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_ufield_len,ufield_len,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_config_reserved_0,reserved_0,HI_CH1_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH1_CONFIG_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr_l,base_addr_l,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_baddr_base_addr,base_addr,HI_CH1_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_size,size,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_size_reserved,reserved,HI_CH1_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_wptr,wptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_1,reserved_1,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_rptr,rptr,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_reserved_0,reserved_0,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_empty,ch1_bdq_empty,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_ptr_ch1_bdq_full,ch1_bdq_full,HI_CH1_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_bdq_raddr_addr,addr,HI_CH1_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_bdq_waddr_addr,addr,HI_CH1_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_bd_num_ch1_bd_num,ch1_bd_num,HI_CH1_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_BD_NUM_OFFSET)
HI_SET_GET(hi_ch1_invalid_bd_num_ch1_invalid_bd_num,ch1_invalid_bd_num,HI_CH1_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH1_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_srst,ch_srst,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_softreset_reserved,reserved,HI_CH2_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH2_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch2_en_ch_en,ch_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_reserved,reserved,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_pack_en,pack_en,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_en_ch_busy,ch_busy,HI_CH2_EN_T,HI_CIPHER_BASE_ADDR, HI_CH2_EN_OFFSET)
HI_SET_GET(hi_ch2_config_iv_sel,iv_sel,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_iv_num,iv_num,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_rdq_ctrl,rdq_ctrl,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_1,reserved_1,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_ufield_len,ufield_len,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_config_reserved_0,reserved_0,HI_CH2_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH2_CONFIG_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr_l,base_addr_l,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_baddr_base_addr,base_addr,HI_CH2_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_size,size,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_size_reserved,reserved,HI_CH2_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_wptr,wptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_1,reserved_1,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_rptr,rptr,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_reserved_0,reserved_0,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_empty,ch2_bdq_empty,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_ptr_ch2_bdq_full,ch2_bdq_full,HI_CH2_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_bdq_raddr_addr,addr,HI_CH2_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_bdq_waddr_addr,addr,HI_CH2_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_bd_num_ch2_bd_num,ch2_bd_num,HI_CH2_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_BD_NUM_OFFSET)
HI_SET_GET(hi_ch2_invalid_bd_num_ch2_invalid_bd_num,ch2_invalid_bd_num,HI_CH2_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH2_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_srst,ch_srst,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_softreset_reserved,reserved,HI_CH3_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH3_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch3_en_ch_en,ch_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_reserved,reserved,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_pack_en,pack_en,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_en_ch_busy,ch_busy,HI_CH3_EN_T,HI_CIPHER_BASE_ADDR, HI_CH3_EN_OFFSET)
HI_SET_GET(hi_ch3_config_iv_sel,iv_sel,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_iv_num,iv_num,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_rdq_ctrl,rdq_ctrl,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_1,reserved_1,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_ufield_len,ufield_len,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_config_reserved_0,reserved_0,HI_CH3_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH3_CONFIG_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr_l,base_addr_l,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_baddr_base_addr,base_addr,HI_CH3_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_size,size,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_size_reserved,reserved,HI_CH3_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_wptr,wptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_1,reserved_1,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_rptr,rptr,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_reserved_0,reserved_0,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_empty,ch3_bdq_empty,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_ptr_ch3_bdq_full,ch3_bdq_full,HI_CH3_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_bdq_raddr_addr,addr,HI_CH3_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_bdq_waddr_addr,addr,HI_CH3_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_bd_num_ch3_bd_num,ch3_bd_num,HI_CH3_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_BD_NUM_OFFSET)
HI_SET_GET(hi_ch3_invalid_bd_num_ch3_invalid_bd_num,ch3_invalid_bd_num,HI_CH3_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH3_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_srst,ch_srst,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_bdq_clear,ch_bdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_ch_rdq_clear,ch_rdq_clear,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_softreset_reserved,reserved,HI_CH4_SOFTRESET_T,HI_CIPHER_BASE_ADDR, HI_CH4_SOFTRESET_OFFSET)
HI_SET_GET(hi_ch4_en_ch_en,ch_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_reserved,reserved,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_pack_en,pack_en,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_en_ch_busy,ch_busy,HI_CH4_EN_T,HI_CIPHER_BASE_ADDR, HI_CH4_EN_OFFSET)
HI_SET_GET(hi_ch4_config_iv_sel,iv_sel,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_iv_num,iv_num,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_rdq_ctrl,rdq_ctrl,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_1,reserved_1,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_ufield_len,ufield_len,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_config_reserved_0,reserved_0,HI_CH4_CONFIG_T,HI_CIPHER_BASE_ADDR, HI_CH4_CONFIG_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr_l,base_addr_l,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_baddr_base_addr,base_addr,HI_CH4_BDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_size,size,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_size_reserved,reserved,HI_CH4_BDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_wptr,wptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_1,reserved_1,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_rptr,rptr,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_reserved_0,reserved_0,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_empty,ch4_bdq_empty,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_ptr_ch4_bdq_full,ch4_bdq_full,HI_CH4_BDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_bdq_raddr_addr,addr,HI_CH4_BDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_bdq_waddr_addr,addr,HI_CH4_BDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_BDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_bd_num_ch4_bd_num,ch4_bd_num,HI_CH4_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_BD_NUM_OFFSET)
HI_SET_GET(hi_ch4_invalid_bd_num_ch4_invalid_bd_num,ch4_invalid_bd_num,HI_CH4_INVALID_BD_NUM_T,HI_CIPHER_BASE_ADDR, HI_CH4_INVALID_BD_NUM_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch0_pkt_num,ch0_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch1_pkt_num,ch1_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch2_pkt_num,ch2_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch3_pkt_num,ch3_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_timeout_time,timeout_time,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_ch4_pkt_num,ch4_pkt_num,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_ch_int_pkt_interval_reserved,reserved,HI_CH_INT_PKT_INTERVAL_T,HI_CIPHER_BASE_ADDR, HI_CH_INT_PKT_INTERVAL_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int0,cipher_int0,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int1,cipher_int1,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_cipher_int2,cipher_int2,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int_status_reserved,reserved,HI_CIPHER_INT_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bdq_full,ch0_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_rdq_full,ch0_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_nbd_done,ch0_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_bd_done,ch0_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_allbd_done,ch0_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch0_integrity_err,ch0_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_3,reserved_3,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bdq_full,ch1_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_rdq_full,ch1_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_nbd_done,ch1_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_bd_done,ch1_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_allbd_done,ch1_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch1_integrity_err,ch1_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_2,reserved_2,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bdq_full,ch2_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_rdq_full,ch2_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_nbd_done,ch2_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_bd_done,ch2_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_allbd_done,ch2_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch2_integrity_err,ch2_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_1,reserved_1,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bdq_full,ch3_bdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_rdq_full,ch3_rdq_full,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_nbd_done,ch3_nbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_bd_done,ch3_bd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_allbd_done,ch3_allbd_done,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_ch3_integrity_err,ch3_integrity_err,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_status_reserved_0,reserved_0,HI_CIPHER_INT0_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int0_mask_int0_mask,int0_mask,HI_CIPHER_INT0_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MASK_OFFSET)
HI_SET_GET(hi_cipher_int0_mstatus_int0_mstatus,int0_mstatus,HI_CIPHER_INT0_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT0_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_bdq_empty,ch0_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_rdq_empty,ch0_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch0_timeout,ch0_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_3,reserved_3,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_bdq_empty,ch1_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_rdq_empty,ch1_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch1_timeout,ch1_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_2,reserved_2,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_bdq_empty,ch2_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_rdq_empty,ch2_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch2_timeout,ch2_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_1,reserved_1,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_bdq_empty,ch3_bdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_rdq_empty,ch3_rdq_empty,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_ch3_timeout,ch3_timeout,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_status_reserved_0,reserved_0,HI_CIPHER_INT1_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int1_mask_int1_mask,int1_mask,HI_CIPHER_INT1_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MASK_OFFSET)
HI_SET_GET(hi_cipher_int1_mstatus_int1_mstatus,int1_mstatus,HI_CIPHER_INT1_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT1_MSTATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_full,ch4_bdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_full,ch4_rdq_full,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_nbd_done,ch4_nbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bd_done,ch4_bd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_allbd_done,ch4_allbd_done,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_bdq_empty,ch4_bdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_rdq_empty,ch4_rdq_empty,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_ch4_timeout,ch4_timeout,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_status_reserved,reserved,HI_CIPHER_INT2_STATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_STATUS_OFFSET)
HI_SET_GET(hi_cipher_int2_mask_reserved,reserved,HI_CIPHER_INT2_MASK_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MASK_OFFSET)
HI_SET_GET(hi_cipher_int2_mstatus_reserved,reserved,HI_CIPHER_INT2_MSTATUS_T,HI_CIPHER_BASE_ADDR, HI_CIPHER_INT2_MSTATUS_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr_l,base_addr_l,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_baddr_base_addr,base_addr,HI_CH0_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_size,size,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_size_reserved,reserved,HI_CH0_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_wptr,wptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_1,reserved_1,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_rptr,rptr,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_ptr_reserved_0,reserved_0,HI_CH0_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch0_rdq_raddr_raddr,raddr,HI_CH0_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch0_rdq_waddr_waddr,waddr,HI_CH0_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH0_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr_l,base_addr_l,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_baddr_base_addr,base_addr,HI_CH1_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_size,size,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_size_reserved,reserved,HI_CH1_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_wptr,wptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_1,reserved_1,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_rptr,rptr,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_ptr_reserved_0,reserved_0,HI_CH1_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch1_rdq_raddr_raddr,raddr,HI_CH1_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch1_rdq_waddr_waddr,waddr,HI_CH1_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH1_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr_l,base_addr_l,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_baddr_base_addr,base_addr,HI_CH2_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_size,size,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_size_reserved,reserved,HI_CH2_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_wptr,wptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_1,reserved_1,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_rptr,rptr,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_ptr_reserved_0,reserved_0,HI_CH2_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch2_rdq_raddr_raddr,raddr,HI_CH2_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch2_rdq_waddr_waddr,waddr,HI_CH2_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH2_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr_l,base_addr_l,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_baddr_base_addr,base_addr,HI_CH3_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_size,size,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_size_reserved,reserved,HI_CH3_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_wptr,wptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_1,reserved_1,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_rptr,rptr,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_ptr_reserved_0,reserved_0,HI_CH3_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch3_rdq_raddr_raddr,raddr,HI_CH3_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch3_rdq_waddr_waddr,waddr,HI_CH3_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH3_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr_l,base_addr_l,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_baddr_base_addr,base_addr,HI_CH4_RDQ_BADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_BADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_size,size,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_size_reserved,reserved,HI_CH4_RDQ_SIZE_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_SIZE_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_wptr,wptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_1,reserved_1,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_rptr,rptr,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_ptr_reserved_0,reserved_0,HI_CH4_RDQ_PTR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_PTR_OFFSET)
HI_SET_GET(hi_ch4_rdq_raddr_raddr,raddr,HI_CH4_RDQ_RADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_RADDR_OFFSET)
HI_SET_GET(hi_ch4_rdq_waddr_waddr,waddr,HI_CH4_RDQ_WADDR_T,HI_CIPHER_BASE_ADDR, HI_CH4_RDQ_WADDR_OFFSET)
HI_SET_GET(hi_key_ram_key,key,HI_KEY_RAM_T,HI_CIPHER_BASE_ADDR, HI_KEY_RAM_OFFSET)
#endif
#endif
