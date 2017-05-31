#ifndef __SOC_HKADC_SSI_INTERFACE_H__
#define __SOC_HKADC_SSI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_ADDR(base) ((base) + (0x0000))
#define SOC_HKADC_SSI_HKADC_DSP_CFG_ADDR(base) ((base) + (0x0004))
#define SOC_HKADC_SSI_HKADC_WR_NUM_ADDR(base) ((base) + (0x0008))
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_ADDR(base) ((base) + (0x000C))
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_ADDR(base) ((base) + (0x0010))
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_ADDR(base) ((base) + (0x0018))
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_ADDR(base) ((base) + (0x001C))
#define SOC_HKADC_SSI_HKADC_WR01_DATA_ADDR(base) ((base) + (0x0020))
#define SOC_HKADC_SSI_HKADC_WR23_DATA_ADDR(base) ((base) + (0x0024))
#define SOC_HKADC_SSI_HKADC_WR45_DATA_ADDR(base) ((base) + (0x0028))
#define SOC_HKADC_SSI_HKADC_WR67_DATA_ADDR(base) ((base) + (0x002C))
#define SOC_HKADC_SSI_HKADC_DELAY01_ADDR(base) ((base) + (0x0030))
#define SOC_HKADC_SSI_HKADC_DELAY23_ADDR(base) ((base) + (0x0034))
#define SOC_HKADC_SSI_HKADC_DELAY45_ADDR(base) ((base) + (0x0038))
#define SOC_HKADC_SSI_HKADC_DELAY6_ADDR(base) ((base) + (0x003C))
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_ADDR(base) ((base) + (0x0040))
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_ADDR(base) ((base) + (0x0044))
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_ADDR(base) ((base) + (0x0048))
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_ADDR(base) ((base) + (0x004C))
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_ADDR(base) ((base) + (0x0050))
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_ADDR(base) ((base) + (0x0054))
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_ADDR(base) ((base) + (0x0058))
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_ADDR(base) ((base) + (0x005C))
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_ADDR(base) ((base) + (0x0060))
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_ADDR(base) ((base) + (0x0064))
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_ADDR(base) ((base) + (0x0068))
#define SOC_HKADC_SSI_HKADC_DBG_INFO_ADDR(base) ((base) + (0x00D0))
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_ADDR(base) ((base) + (0x0100))
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_ADDR(base) ((base) + (0x0104))
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_ADDR(base) ((base) + (0x0108))
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_ADDR(base) ((base) + (0x010C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_cfg : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_CFG_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_wr_num : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_HKADC_SSI_HKADC_WR_NUM_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_START (0)
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_wait_time : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int time_out_err_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_START (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeout_err : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_START (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_start_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_wr0_cfg : 16;
        unsigned int dsp_wr1_cfg : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_WR01_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_START (0)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_END (15)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_START (16)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_wr2_cfg : 16;
        unsigned int dsp_wr3_cfg : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_WR23_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_START (0)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_END (15)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_START (16)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_wr4_cfg : 16;
        unsigned int dsp_wr5_cfg : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_WR45_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_START (0)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_END (15)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_START (16)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_wr6_cfg : 16;
        unsigned int dsp_wr7_cfg : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_WR67_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_START (0)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_END (15)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_START (16)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_delay0 : 16;
        unsigned int dsp_delay1 : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY01_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_START (0)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_END (15)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_START (16)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_delay2 : 16;
        unsigned int dsp_delay3 : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY23_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_START (0)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_END (15)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_START (16)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_delay4 : 16;
        unsigned int dsp_delay5 : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY45_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_START (0)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_END (15)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_START (16)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_delay6 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY6_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_START (0)
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd0_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd1_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd2_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd3_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd4_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd5_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd6_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_rd7_data : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_START (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_op_interval : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_START (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int op_interval_bypass_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_START (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_channel_en_sft : 1;
        unsigned int hkadc_channel_en_hd0 : 1;
        unsigned int hkadc_channel_en_hd1 : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_START (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_END (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_START (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_END (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_START (2)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int arb_info : 32;
    } reg;
} SOC_HKADC_SSI_HKADC_DBG_INFO_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_START (0)
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_finish_raw_int : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_START (0)
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_finish_msk_int : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_START (0)
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_finish_int_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_START (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hkadc_finish_int_msk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_START (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
