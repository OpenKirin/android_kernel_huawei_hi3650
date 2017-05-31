#ifndef __SOC_ISP_JPGENC_INTERFACE_H__
#define __SOC_ISP_JPGENC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_JPGENC_JPE_ENCODE_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_JPGENC_JPE_INIT_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_ADDR(base) ((base) + (0x002C))
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_JPGENC_JPE_TABLE_ID_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_ADDR(base) ((base) + (0x0004C))
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_JPGENC_JPE_DEBUG_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_ADDR(base) ((base) + (0x006C))
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_ADDR(base) ((base) + (0x0078))
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_ADDR(base) ((base) + (0x007C))
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_ADDR(base) ((base) + (0x0080))
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_ADDR(base) ((base) + (0x0084))
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_ADDR(base) ((base) + (0x0088))
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_ADDR(base) ((base) + (0x008C))
#define SOC_ISP_JPGENC_JPE_CONFIG_ADDR(base) ((base) + (0x0090))
#define SOC_ISP_JPGENC_ADDRESS_Y_ADDR(base) ((base) + (0x0094))
#define SOC_ISP_JPGENC_ADDRESS_UV_ADDR(base) ((base) + (0x00098))
#define SOC_ISP_JPGENC_STRIDE_ADDR(base) ((base) + (0x009C))
#define SOC_ISP_JPGENC_SYNCCFG_ADDR(base) ((base) + (0x0100))
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_ADDR(base) ((base) + (0x0104))
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_ADDR(base) ((base) + (0x0108))
#define SOC_ISP_JPGENC_PREFETCH_ADDR(base) ((base) + (0x010C))
#define SOC_ISP_JPGENC_PREFETCH_IDY0_ADDR(base) ((base) + (0x0110))
#define SOC_ISP_JPGENC_PREFETCH_IDY1_ADDR(base) ((base) + (0x0114))
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_ADDR(base) ((base) + (0x0118))
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_ADDR(base) ((base) + (0x011C))
#define SOC_ISP_JPGENC_PREREAD_ADDR(base) ((base) + (0x0120))
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x0130))
#define SOC_ISP_JPGENC_DBG_0_ADDR(base) ((base) + (0x0200))
#define SOC_ISP_JPGENC_DBG_1_ADDR(base) ((base) + (0x0204))
#define SOC_ISP_JPGENC_DBG_2_ADDR(base) ((base) + (0x0208))
#define SOC_ISP_JPGENC_DBG_3_ADDR(base) ((base) + (0x020c))
#define SOC_ISP_JPGENC_DBG_4_ADDR(base) ((base) + (0x0210))
#define SOC_ISP_JPGENC_DBG_5_ADDR(base) ((base) + (0x0214))
#define SOC_ISP_JPGENC_DBG_6_ADDR(base) ((base) + (0x0218))
#define SOC_ISP_JPGENC_DBG_7_ADDR(base) ((base) + (0x021c))
#define SOC_ISP_JPGENC_DBG_8_ADDR(base) ((base) + (0x0220))
#define SOC_ISP_JPGENC_DBG_9_ADDR(base) ((base) + (0x0224))
#define SOC_ISP_JPGENC_DBG_10_ADDR(base) ((base) + (0x0228))
#define SOC_ISP_JPGENC_DBG_11_ADDR(base) ((base) + (0x022c))
#define SOC_ISP_JPGENC_DBG_12_ADDR(base) ((base) + (0x0230))
#define SOC_ISP_JPGENC_DBG_13_ADDR(base) ((base) + (0x0234))
#define SOC_ISP_JPGENC_DBG_14_ADDR(base) ((base) + (0x0238))
#define SOC_ISP_JPGENC_DBG_15_ADDR(base) ((base) + (0x023c))
#define SOC_ISP_JPGENC_DBG_RW_0_ADDR(base) ((base) + (0x0300))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int encode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_JPGENC_JPE_ENCODE_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENCODE_encode_START (0)
#define SOC_ISP_JPGENC_JPE_ENCODE_encode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int jp_init : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_JPGENC_JPE_INIT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_INIT_jp_init_START (0)
#define SOC_ISP_JPGENC_JPE_INIT_jp_init_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enc_hright1 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_enc_hright1_START (0)
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_enc_hright1_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enc_vbottom : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_enc_vbottom_START (0)
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_enc_vbottom_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enc_pic_format : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_JPGENC_JPE_PIC_FORMAT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_enc_pic_format_START (0)
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_enc_pic_format_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int restart_interval : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_restart_interval_START (0)
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_restart_interval_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tq0_select : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_tq0_select_START (0)
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_tq0_select_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tq1_select : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_U_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_tq1_select_START (0)
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_tq1_select_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tq2_select : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_V_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_tq2_select_START (0)
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_tq2_select_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dc_table_select_y : 1;
        unsigned int dc_table_select_u : 1;
        unsigned int dc_table_select_v : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_y_START (0)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_y_END (0)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_u_START (1)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_u_END (1)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_v_START (2)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_v_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ac_table_select_y : 1;
        unsigned int ac_table_select_u : 1;
        unsigned int ac_table_select_v : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_y_START (0)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_y_END (0)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_u_START (1)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_u_END (1)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_v_START (2)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_v_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int table_wdata_l : 8;
        unsigned int table_wdata_h : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_JPGENC_JPE_TABLE_DATA_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_l_START (0)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_l_END (7)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_h_START (8)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_h_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int table_id : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_JPGENC_JPE_TABLE_ID_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TABLE_ID_table_id_START (0)
#define SOC_ISP_JPGENC_JPE_TABLE_ID_table_id_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tac0_len : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_JPGENC_JPE_TAC0_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_tac0_len_START (0)
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_tac0_len_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tdc0_len : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_JPGENC_JPE_TDC0_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_tdc0_len_START (0)
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_tdc0_len_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tac1_len : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_JPGENC_JPE_TAC1_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_tac1_len_START (0)
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_tac1_len_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tdc1_len : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_JPGENC_JPE_TDC1_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_tdc1_len_START (0)
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_tdc1_len_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int encode_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_JPGENC_JPE_ENCODER_MODE_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_encode_mode_START (0)
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_encode_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int deb_qiq_table_acc : 1;
        unsigned int deb_vlc_encode_busy : 1;
        unsigned int deb_r2b_memory_full : 1;
        unsigned int deb_vlc_table_busy : 1;
        unsigned int reserved_1 : 2;
        unsigned int deb_bad_table_access : 1;
        unsigned int reserved_2 : 23;
    } reg;
} SOC_ISP_JPGENC_JPE_DEBUG_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_qiq_table_acc_START (2)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_qiq_table_acc_END (2)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_encode_busy_START (3)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_encode_busy_END (3)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_r2b_memory_full_START (4)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_r2b_memory_full_END (4)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_table_busy_START (5)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_table_busy_END (5)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_bad_table_access_START (8)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_bad_table_access_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int vlc_symbol_err_imr : 1;
        unsigned int reserved_1 : 2;
        unsigned int dct_err_imr : 1;
        unsigned int reserved_2 : 1;
        unsigned int r2b_img_size_err_imr : 1;
        unsigned int vlc_table_err_imr : 1;
        unsigned int reserved_3 : 21;
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_IMR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_symbol_err_imr_START (4)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_symbol_err_imr_END (4)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_dct_err_imr_START (7)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_dct_err_imr_END (7)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_r2b_img_size_err_imr_START (9)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_r2b_img_size_err_imr_END (9)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_table_err_imr_START (10)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_table_err_imr_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int vlc_symbol_err_ris : 1;
        unsigned int reserved_1 : 2;
        unsigned int dct_err_ris : 1;
        unsigned int reserved_2 : 1;
        unsigned int r2b_img_size_err_ris : 1;
        unsigned int vlc_table_err_ris : 1;
        unsigned int reserved_3 : 21;
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_RIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_symbol_err_ris_START (4)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_symbol_err_ris_END (4)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_dct_err_ris_START (7)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_dct_err_ris_END (7)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_r2b_img_size_err_ris_START (9)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_r2b_img_size_err_ris_END (9)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_table_err_ris_START (10)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_table_err_ris_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int vlc_symbol_err_mis : 1;
        unsigned int reserved_1 : 2;
        unsigned int dct_err_mis : 1;
        unsigned int reserved_2 : 1;
        unsigned int r2b_img_size_err_mis : 1;
        unsigned int vlc_table_err_mis : 1;
        unsigned int reserved_3 : 21;
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_MIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_symbol_err_mis_START (4)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_symbol_err_mis_END (4)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_dct_err_mis_START (7)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_dct_err_mis_END (7)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_r2b_img_size_err_mis_START (9)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_r2b_img_size_err_mis_END (9)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_table_err_mis_START (10)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_table_err_mis_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int vlc_symbol_err_icr : 1;
        unsigned int reserved_1 : 2;
        unsigned int dct_err_icr : 1;
        unsigned int reserved_2 : 1;
        unsigned int r2b_img_size_err_icr : 1;
        unsigned int vlc_table_err_icr : 1;
        unsigned int reserved_3 : 21;
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_ICR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_symbol_err_icr_START (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_symbol_err_icr_END (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_dct_err_icr_START (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_dct_err_icr_END (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_r2b_img_size_err_icr_START (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_r2b_img_size_err_icr_END (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_table_err_icr_START (10)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_table_err_icr_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int vlc_symbol_err_isr : 1;
        unsigned int reserved_1 : 2;
        unsigned int dct_err_isr : 1;
        unsigned int reserved_2 : 1;
        unsigned int r2b_img_size_err_isr : 1;
        unsigned int vlc_table_err_isr : 1;
        unsigned int reserved_3 : 21;
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_ISR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_symbol_err_isr_START (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_symbol_err_isr_END (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_dct_err_isr_START (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_dct_err_isr_END (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_r2b_img_size_err_isr_START (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_r2b_img_size_err_isr_END (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_table_err_isr_START (10)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_table_err_isr_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int encode_done_imr : 1;
        unsigned int gen_header_done_imr : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_IMR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_encode_done_imr_START (4)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_encode_done_imr_END (4)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_gen_header_done_imr_START (5)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_gen_header_done_imr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int encode_done_ris : 1;
        unsigned int gen_header_done_ris : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_RIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_encode_done_ris_START (4)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_encode_done_ris_END (4)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_gen_header_done_ris_START (5)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_gen_header_done_ris_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int encode_done_mis : 1;
        unsigned int gen_header_done_mis : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_MIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_encode_done_mis_START (4)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_encode_done_mis_END (4)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_gen_header_done_mis_START (5)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_gen_header_done_mis_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int encode_done_icr : 1;
        unsigned int gen_header_done_icr : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_ICR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_encode_done_icr_START (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_encode_done_icr_END (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_gen_header_done_icr_START (5)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_gen_header_done_icr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int encode_done_isr : 1;
        unsigned int gen_header_done_isr : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_ISR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_encode_done_isr_START (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_encode_done_isr_END (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_gen_header_done_isr_START (5)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_gen_header_done_isr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int speedview_en : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_ISP_JPGENC_JPE_CONFIG_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_CONFIG_speedview_en_START (4)
#define SOC_ISP_JPGENC_JPE_CONFIG_speedview_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int address_y : 28;
    } reg;
} SOC_ISP_JPGENC_ADDRESS_Y_UNION;
#endif
#define SOC_ISP_JPGENC_ADDRESS_Y_address_y_START (4)
#define SOC_ISP_JPGENC_ADDRESS_Y_address_y_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int address_uv : 28;
    } reg;
} SOC_ISP_JPGENC_ADDRESS_UV_UNION;
#endif
#define SOC_ISP_JPGENC_ADDRESS_UV_address_uv_START (4)
#define SOC_ISP_JPGENC_ADDRESS_UV_address_uv_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 4;
        unsigned int stride : 11;
        unsigned int reserved_1: 17;
    } reg;
} SOC_ISP_JPGENC_STRIDE_UNION;
#endif
#define SOC_ISP_JPGENC_STRIDE_stride_START (4)
#define SOC_ISP_JPGENC_STRIDE_stride_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int source : 1;
        unsigned int reserved_0 : 1;
        unsigned int sram_noopt : 1;
        unsigned int reserved_1 : 29;
    } reg;
} SOC_ISP_JPGENC_SYNCCFG_UNION;
#endif
#define SOC_ISP_JPGENC_SYNCCFG_source_START (0)
#define SOC_ISP_JPGENC_SYNCCFG_source_END (0)
#define SOC_ISP_JPGENC_SYNCCFG_sram_noopt_START (2)
#define SOC_ISP_JPGENC_SYNCCFG_sram_noopt_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enc_hright2 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_enc_hright2_START (0)
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_enc_hright2_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int byte_cnt : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_ISP_JPGENC_JPG_BYTE_CNT_UNION;
#endif
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_byte_cnt_START (0)
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_byte_cnt_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prefetch_en : 1;
        unsigned int prefetch_delay : 11;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_JPGENC_PREFETCH_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_prefetch_en_START (0)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_en_END (0)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_delay_START (1)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_delay_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id0_y : 7;
        unsigned int reserved_0: 1;
        unsigned int id1_y : 7;
        unsigned int reserved_1: 1;
        unsigned int id2_y : 7;
        unsigned int reserved_2: 1;
        unsigned int id3_y : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDY0_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id0_y_START (0)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id0_y_END (6)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id1_y_START (8)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id1_y_END (14)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id2_y_START (16)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id2_y_END (22)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id3_y_START (24)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id3_y_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id4_y : 7;
        unsigned int reserved_0: 1;
        unsigned int id5_y : 7;
        unsigned int reserved_1: 1;
        unsigned int id6_y : 7;
        unsigned int reserved_2: 1;
        unsigned int id7_y : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDY1_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id4_y_START (0)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id4_y_END (6)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id5_y_START (8)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id5_y_END (14)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id6_y_START (16)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id6_y_END (22)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id7_y_START (24)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id7_y_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id0_uv : 7;
        unsigned int reserved_0: 1;
        unsigned int id1_uv : 7;
        unsigned int reserved_1: 1;
        unsigned int id2_uv : 7;
        unsigned int reserved_2: 1;
        unsigned int id3_uv : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDUV0_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id0_uv_START (0)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id0_uv_END (6)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id1_uv_START (8)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id1_uv_END (14)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id2_uv_START (16)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id2_uv_END (22)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id3_uv_START (24)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id3_uv_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id4_uv : 7;
        unsigned int reserved_0: 1;
        unsigned int id8_y : 7;
        unsigned int reserved_1: 17;
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDUVY_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id4_uv_START (0)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id4_uv_END (6)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id8_y_START (8)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id8_y_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int preread : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_JPGENC_PREREAD_UNION;
#endif
#define SOC_ISP_JPGENC_PREREAD_preread_START (0)
#define SOC_ISP_JPGENC_PREREAD_preread_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_clk_on : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_force_clk_on_START (0)
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_force_clk_on_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_0 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_0_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_0_dbg_0_START (0)
#define SOC_ISP_JPGENC_DBG_0_dbg_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_1 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_1_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_1_dbg_1_START (0)
#define SOC_ISP_JPGENC_DBG_1_dbg_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_2 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_2_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_2_dbg_2_START (0)
#define SOC_ISP_JPGENC_DBG_2_dbg_2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_3 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_3_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_3_dbg_3_START (0)
#define SOC_ISP_JPGENC_DBG_3_dbg_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_4 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_4_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_4_dbg_4_START (0)
#define SOC_ISP_JPGENC_DBG_4_dbg_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_5 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_5_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_5_dbg_5_START (0)
#define SOC_ISP_JPGENC_DBG_5_dbg_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_6 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_6_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_6_dbg_6_START (0)
#define SOC_ISP_JPGENC_DBG_6_dbg_6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_7 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_7_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_7_dbg_7_START (0)
#define SOC_ISP_JPGENC_DBG_7_dbg_7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_8 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_8_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_8_dbg_8_START (0)
#define SOC_ISP_JPGENC_DBG_8_dbg_8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_9 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_9_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_9_dbg_9_START (0)
#define SOC_ISP_JPGENC_DBG_9_dbg_9_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_10 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_10_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_10_dbg_10_START (0)
#define SOC_ISP_JPGENC_DBG_10_dbg_10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_11 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_11_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_11_dbg_11_START (0)
#define SOC_ISP_JPGENC_DBG_11_dbg_11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_12 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_12_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_12_dbg_12_START (0)
#define SOC_ISP_JPGENC_DBG_12_dbg_12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_13 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_13_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_13_dbg_13_START (0)
#define SOC_ISP_JPGENC_DBG_13_dbg_13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_14 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_14_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_14_dbg_14_START (0)
#define SOC_ISP_JPGENC_DBG_14_dbg_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_15 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_15_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_15_dbg_15_START (0)
#define SOC_ISP_JPGENC_DBG_15_dbg_15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_rw_0 : 32;
    } reg;
} SOC_ISP_JPGENC_DBG_RW_0_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_RW_0_dbg_rw_0_START (0)
#define SOC_ISP_JPGENC_DBG_RW_0_dbg_rw_0_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
