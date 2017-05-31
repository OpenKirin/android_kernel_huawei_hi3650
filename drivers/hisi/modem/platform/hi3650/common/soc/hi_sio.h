#ifndef __HI_SIO_H__
#define __HI_SIO_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI_SIO_VERSION_OFFSET (0x3C)
#define HI_SIO_MODE_OFFSET (0x40)
#define HI_SIO_INTSTATUS_OFFSET (0x44)
#define HI_SIO_INTCLR_OFFSET (0x48)
#define HI_SIO_I2S_LEFT_XD_OFFSET (0x4C)
#define HI_SIO_I2S_RIGHT_XD_OFFSET (0x50)
#define HI_SIO_PCM_XD_OFFSET (0x50)
#define HI_SIO_I2S_LEFT_RD_OFFSET (0x54)
#define HI_SIO_I2S_RIGHT_RD_OFFSET (0x58)
#define HI_SIO_PCM_RD_OFFSET (0x58)
#define HI_SIO_RX_STA_OFFSET (0x68)
#define HI_SIO_TX_STA_OFFSET (0x6C)
#define HI_SIO_DATA_WIDTH_SET_OFFSET (0x78)
#define HI_SIO_I2S_START_POS_OFFSET (0x7C)
#define HI_I2S_POS_FLAG_OFFSET (0x80)
#define HI_SIO_SIGNED_EXT_OFFSET (0x84)
#define HI_SIO_I2S_POS_MERGE_EN_OFFSET (0x88)
#define HI_SIO_INTMASK_OFFSET (0x8C)
#define HI_SIO_I2S_DUAL_RX_CHN_OFFSET (0xA0)
#define HI_SIO_I2S_DUAL_TX_CHN_OFFSET (0xC0)
#define HI_SIO_I2S_CT_SET_OFFSET (0x5C)
#define HI_SIO_I2S_CT_CLR_OFFSET (0x60)
typedef union
{
    struct
    {
        unsigned int vesion : 8;
        unsigned int sio_loop : 1;
        unsigned int reserved : 23;
    } bits;
    unsigned int u32;
}HI_SIO_VERSION_T;
typedef union
{
    struct
    {
        unsigned int sio_mode : 1;
        unsigned int pcm_mode : 1;
        unsigned int reserved_1 : 1;
        unsigned int ext_rec_en : 1;
        unsigned int chn_num : 2;
        unsigned int clk_edge : 1;
        unsigned int reserved_0 : 25;
    } bits;
    unsigned int u32;
}HI_SIO_MODE_T;
typedef union
{
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_SIO_INTSTATUS_T;
typedef union
{
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_SIO_INTCLR_T;
typedef union
{
    struct
    {
        unsigned int tx_left_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_LEFT_XD_T;
typedef union
{
    struct
    {
        unsigned int tx_right_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_RIGHT_XD_T;
typedef union
{
    struct
    {
        unsigned int tx_data : 16;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_SIO_PCM_XD_T;
typedef union
{
    struct
    {
        unsigned int rx_left_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_LEFT_RD_T;
typedef union
{
    struct
    {
        unsigned int rx_right_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_RIGHT_RD_T;
typedef union
{
    struct
    {
        unsigned int rx__data : 16;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_SIO_PCM_RD_T;
typedef union
{
    struct
    {
        unsigned int rx_right_depth : 5;
        unsigned int rx_left_depth : 5;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_SIO_RX_STA_T;
typedef union
{
    struct
    {
        unsigned int tx_right_depth : 5;
        unsigned int tx_left_depth : 5;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_SIO_TX_STA_T;
typedef union
{
    struct
    {
        unsigned int tx_mode : 3;
        unsigned int rx_mode : 3;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_SIO_DATA_WIDTH_SET_T;
typedef union
{
    struct
    {
        unsigned int start_pos_read : 1;
        unsigned int start_pos_write : 1;
        unsigned int reserved : 30;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_START_POS_T;
typedef union
{
    struct
    {
        unsigned int start_pos_read : 1;
        unsigned int start_pos_write : 1;
        unsigned int reserved : 30;
    } bits;
    unsigned int u32;
}HI_I2S_POS_FLAG_T;
typedef union
{
    struct
    {
        unsigned int signed_ext_en : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_SIO_SIGNED_EXT_T;
typedef union
{
    struct
    {
        unsigned int merge_en : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_POS_MERGE_EN_T;
typedef union
{
    struct
    {
        unsigned int rx_intr : 1;
        unsigned int tx_intr : 1;
        unsigned int rx_right_fifo_over : 1;
        unsigned int rx_left_fifo_over : 1;
        unsigned int tx_right_fifo_under : 1;
        unsigned int tx_left_fifo_under : 1;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_SIO_INTMASK_T;
typedef union
{
    struct
    {
        unsigned int rx_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_DUAL_RX_CHN_T;
typedef union
{
    struct
    {
        unsigned int tx_data : 32;
    } bits;
    unsigned int u32;
}HI_SIO_I2S_DUAL_TX_CHN_T;
typedef union
{
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
    } bits;
    unsigned int u32;
} HI_SIO_CT_SET_T;
typedef union
{
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
    } bits;
    unsigned int u32;
} HI_SIO_CT_CLR_T;
#endif
