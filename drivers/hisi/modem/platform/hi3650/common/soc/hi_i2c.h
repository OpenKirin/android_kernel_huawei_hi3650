#ifndef __HI_I2C_H__
#define __HI_I2C_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI_I2C_CTRL_OFFSET (0x0)
#define HI_I2C_COM_OFFSET (0x4)
#define HI_I2C_ICR_OFFSET (0x8)
#define HI_I2C_SR_OFFSET (0xC)
#define HI_I2C_SCL_H_OFFSET (0x10)
#define HI_I2C_SCL_L_OFFSET (0x14)
#define HI_I2C_TXR_OFFSET (0x18)
#define HI_I2C_RXR_OFFSET (0x1C)
typedef union
{
    struct
    {
        unsigned int int_done_mask : 1;
        unsigned int int_arb_loss_mask : 1;
        unsigned int int_ack_err_mask : 1;
        unsigned int int_rx_mask : 1;
        unsigned int int_tx_mask : 1;
        unsigned int int_stop_mask : 1;
        unsigned int int_start_mask : 1;
        unsigned int int_mask : 1;
        unsigned int i2c_en : 1;
        unsigned int reserved : 23;
    } bits;
    unsigned int u32;
}HI_I2C_CTRL_T;
typedef union
{
    struct
    {
        unsigned int op_stop : 1;
        unsigned int op_we : 1;
        unsigned int op_rd : 1;
        unsigned int op_start : 1;
        unsigned int op_ack : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_I2C_COM_T;
typedef union
{
    struct
    {
        unsigned int clr_int_done : 1;
        unsigned int clr_int_arb_loss : 1;
        unsigned int clr_int_ack_err : 1;
        unsigned int clr_int_rx : 1;
        unsigned int clr_int_tx : 1;
        unsigned int clr_int_stop : 1;
        unsigned int clr_int_start : 1;
        unsigned int reserved : 25;
    } bits;
    unsigned int u32;
}HI_I2C_ICR_T;
typedef union
{
    struct
    {
        unsigned int int_done : 1;
        unsigned int int_arb_loss : 1;
        unsigned int int_ack_err : 1;
        unsigned int int_rx : 1;
        unsigned int int_tx : 1;
        unsigned int int_stop : 1;
        unsigned int int_start : 1;
        unsigned int bus_busy : 1;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_I2C_SR_T;
typedef union
{
    struct
    {
        unsigned int scl_h : 16;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_I2C_SCL_H_T;
typedef union
{
    struct
    {
        unsigned int scl_l : 16;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_I2C_SCL_L_T;
typedef union
{
    struct
    {
        unsigned int i2c_txr : 8;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_I2C_TXR_T;
typedef union
{
    struct
    {
        unsigned int i2c_rxr : 8;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_I2C_RXR_T;
HI_SET_GET(hi_i2c_ctrl_int_done_mask,int_done_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_arb_loss_mask,int_arb_loss_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_ack_err_mask,int_ack_err_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_rx_mask,int_rx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_tx_mask,int_tx_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_stop_mask,int_stop_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_start_mask,int_start_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_int_mask,int_mask,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_i2c_en,i2c_en,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_ctrl_reserved,reserved,HI_I2C_CTRL_T,HI_I2C_BASE_ADDR, HI_I2C_CTRL_OFFSET)
HI_SET_GET(hi_i2c_com_op_stop,op_stop,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_we,op_we,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_rd,op_rd,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_start,op_start,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_op_ack,op_ack,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_com_reserved,reserved,HI_I2C_COM_T,HI_I2C_BASE_ADDR, HI_I2C_COM_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_done,clr_int_done,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_arb_loss,clr_int_arb_loss,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_ack_err,clr_int_ack_err,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_rx,clr_int_rx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_tx,clr_int_tx,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_stop,clr_int_stop,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_clr_int_start,clr_int_start,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_icr_reserved,reserved,HI_I2C_ICR_T,HI_I2C_BASE_ADDR, HI_I2C_ICR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_done,int_done,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_arb_loss,int_arb_loss,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_ack_err,int_ack_err,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_rx,int_rx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_tx,int_tx,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_stop,int_stop,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_int_start,int_start,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_bus_busy,bus_busy,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_sr_reserved,reserved,HI_I2C_SR_T,HI_I2C_BASE_ADDR, HI_I2C_SR_OFFSET)
HI_SET_GET(hi_i2c_scl_h_scl_h,scl_h,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_h_reserved,reserved,HI_I2C_SCL_H_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_H_OFFSET)
HI_SET_GET(hi_i2c_scl_l_scl_l,scl_l,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_scl_l_reserved,reserved,HI_I2C_SCL_L_T,HI_I2C_BASE_ADDR, HI_I2C_SCL_L_OFFSET)
HI_SET_GET(hi_i2c_txr_i2c_txr,i2c_txr,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_txr_reserved,reserved,HI_I2C_TXR_T,HI_I2C_BASE_ADDR, HI_I2C_TXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_i2c_rxr,i2c_rxr,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)
HI_SET_GET(hi_i2c_rxr_reserved,reserved,HI_I2C_RXR_T,HI_I2C_BASE_ADDR, HI_I2C_RXR_OFFSET)
#endif
