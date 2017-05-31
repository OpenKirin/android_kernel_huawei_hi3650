#ifndef __HI_MIPI_H__
#define __HI_MIPI_H__ 
#ifndef HI_SET_GET_MIPI
#define HI_SET_GET_MIPI(a0,a1,a2,a3,a4) 
#endif
#define MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET (0xD8)
#define MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET (0xDC)
#define MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET (0xE0)
#define MIPI_MIPI0_GRANT_DSP_OFFSET (0xE4)
#define MIPI_DSP_MIPI0_WDATA_LOW_OFFSET (0xE8)
#define MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET (0xEC)
#define MIPI_DSP_MIPI0_EN_IMI_OFFSET (0xF0)
#define MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET (0xF4)
#define MIPI_DSP_MIPI0_RD_CLR_OFFSET (0xF8)
typedef union
{
    struct
    {
        unsigned int mipi0_rd_data_low_soft : 32;
    } bits;
    unsigned int u32;
}MIPI_MIPI0_RD_DATA_LOW_SOFT_T;
typedef union
{
    struct
    {
        unsigned int mipi0_rd_data_high_soft : 32;
    } bits;
    unsigned int u32;
}MIPI_MIPI0_RD_DATA_HIGH_SOFT_T;
typedef union
{
    struct
    {
        unsigned int rd_end_flag_mipi0_soft : 1;
        unsigned int Reserved : 31;
    } bits;
    unsigned int u32;
}MIPI_RD_END_FLAG_MIPI0_SOFT_T;
typedef union
{
    struct
    {
        unsigned int mipi0_grant_dsp : 1;
        unsigned int Reserved : 31;
    } bits;
    unsigned int u32;
}MIPI_MIPI0_GRANT_DSP_T;
typedef union
{
    struct
    {
        unsigned int dsp_mipi0_wdata_low : 32;
    } bits;
    unsigned int u32;
}MIPI_DSP_MIPI0_WDATA_LOW_T;
typedef union
{
    struct
    {
        unsigned int dsp_mipi0_wdata_high : 32;
    } bits;
    unsigned int u32;
}MIPI_DSP_MIPI0_WDATA_HIGH_T;
typedef union
{
    struct
    {
        unsigned int dsp_mipi0_en_imi : 1;
        unsigned int Reserved : 31;
    } bits;
    unsigned int u32;
}MIPI_DSP_MIPI0_EN_IMI_T;
typedef union
{
    struct
    {
        unsigned int dsp_mipi0_cfg_ind_imi : 1;
        unsigned int Reserved : 31;
    } bits;
    unsigned int u32;
}MIPI_DSP_MIPI0_CFG_IND_IMI_T;
typedef union
{
    struct
    {
        unsigned int dsp_mipi0_rd_clr : 1;
        unsigned int Reserved : 31;
    } bits;
    unsigned int u32;
}MIPI_DSP_MIPI0_RD_CLR_T;
HI_SET_GET_MIPI(mipi_mipi0_rd_data_low_soft_mipi0_rd_data_low_soft,mipi0_rd_data_low_soft,MIPI_MIPI0_RD_DATA_LOW_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_rd_data_high_soft_mipi0_rd_data_high_soft,mipi0_rd_data_high_soft,MIPI_MIPI0_RD_DATA_HIGH_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_rd_end_flag_mipi0_soft,rd_end_flag_mipi0_soft,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_reserved,Reserved,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_mipi0_grant_dsp,mipi0_grant_dsp,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_reserved,Reserved,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_low_dsp_mipi0_wdata_low,dsp_mipi0_wdata_low,MIPI_DSP_MIPI0_WDATA_LOW_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_LOW_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_high_dsp_mipi0_wdata_high,dsp_mipi0_wdata_high,MIPI_DSP_MIPI0_WDATA_HIGH_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi,dsp_mipi0_en_imi,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_reserved,Reserved,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_dsp_mipi0_cfg_ind_imi,dsp_mipi0_cfg_ind_imi,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_reserved,Reserved,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_dsp_mipi0_rd_clr,dsp_mipi0_rd_clr,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_reserved,Reserved,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)
#endif
