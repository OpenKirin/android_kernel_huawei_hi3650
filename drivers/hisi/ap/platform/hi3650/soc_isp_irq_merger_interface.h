#ifndef __SOC_ISP_IRQ_MERGER_INTERFACE_H__
#define __SOC_ISP_IRQ_MERGER_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_ADDR(base) ((base) + (0x0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_ADDR(base) ((base) + (0x4))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_ADDR(base) ((base) + (0x8))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_ADDR(base) ((base) + (0xC))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_ADDR(base) ((base) + (0x10))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_ADDR(base) ((base) + (0x20))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_ADDR(base) ((base) + (0x24))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_ADDR(base) ((base) + (0x28))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_ADDR(base) ((base) + (0x2C))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_ADDR(base) ((base) + (0x30))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_ADDR(base) ((base) + (0x40))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_ADDR(base) ((base) + (0x44))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_ADDR(base) ((base) + (0x48))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_ADDR(base) ((base) + (0x4C))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_ADDR(base) ((base) + (0x50))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_ADDR(base) ((base) + (0x60))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_ADDR(base) ((base) + (0x64))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_ADDR(base) ((base) + (0x68))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_ADDR(base) ((base) + (0x6C))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_ADDR(base) ((base) + (0x70))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_ADDR(base) ((base) + (0x80))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_ADDR(base) ((base) + (0x84))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_ADDR(base) ((base) + (0x88))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_ADDR(base) ((base) + (0x8C))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_ADDR(base) ((base) + (0x90))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_ADDR(base) ((base) + (0xA0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_ADDR(base) ((base) + (0xA4))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_ADDR(base) ((base) + (0xA8))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_ADDR(base) ((base) + (0xAC))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_ADDR(base) ((base) + (0xB0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_ADDR(base) ((base) + (0xC0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_ADDR(base) ((base) + (0xC4))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_ADDR(base) ((base) + (0xC8))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_ADDR(base) ((base) + (0xCC))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_ADDR(base) ((base) + (0xD0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ADDR(base) ((base) + (0xE0))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ADDR(base) ((base) + (0xE4))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ADDR(base) ((base) + (0xE8))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ADDR(base) ((base) + (0xEC))
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ADDR(base) ((base) + (0xF0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__dropped_vpwr_0 : 1;
        unsigned int otap_1_1__cvdr_rt__sof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__dropped_vpwr_1 : 1;
        unsigned int otap_1_2__cvdr_rt__sof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__dropped_vpwr_2 : 1;
        unsigned int scaler_3_y__cvdr_rt__sof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__dropped_vpwr_3 : 1;
        unsigned int scaler_3_uv__cvdr_rt__sof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__dropped_vpwr_4 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__sof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__dropped_vpwr_5 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__sof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__dropped_vpwr_6 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__sof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__dropped_vpwr_7 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__sof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__dropped_vpwr_8 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__sof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__dropped_vpwr_9 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__sof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__dropped_vpwr_10 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__sof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__sof_vpwr_11 : 1;
        unsigned int fbcyuv_1__cvdr_rt__dropped_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__sof_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__eof_vpwr_12 : 1;
        unsigned int isp_be_2__cvdr_rt__dropped_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vpwr_13 : 1;
        unsigned int otap_2_1__cvdr_rt__dropped_vpwr_14 : 1;
        unsigned int otap_2_1__cvdr_rt__sof_vpwr_14 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__dropped_vpwr_0 : 1;
        unsigned int otap_1_1__cvdr_rt__sof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__dropped_vpwr_1 : 1;
        unsigned int otap_1_2__cvdr_rt__sof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__dropped_vpwr_2 : 1;
        unsigned int scaler_3_y__cvdr_rt__sof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__dropped_vpwr_3 : 1;
        unsigned int scaler_3_uv__cvdr_rt__sof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__dropped_vpwr_4 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__sof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__dropped_vpwr_5 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__sof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__dropped_vpwr_6 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__sof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__dropped_vpwr_7 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__sof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__dropped_vpwr_8 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__sof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__dropped_vpwr_9 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__sof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__dropped_vpwr_10 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__sof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__sof_vpwr_11 : 1;
        unsigned int fbcyuv_1__cvdr_rt__dropped_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__sof_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__eof_vpwr_12 : 1;
        unsigned int isp_be_2__cvdr_rt__dropped_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vpwr_13 : 1;
        unsigned int otap_2_1__cvdr_rt__dropped_vpwr_14 : 1;
        unsigned int otap_2_1__cvdr_rt__sof_vpwr_14 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__dropped_vpwr_0 : 1;
        unsigned int otap_1_1__cvdr_rt__sof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__dropped_vpwr_1 : 1;
        unsigned int otap_1_2__cvdr_rt__sof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__dropped_vpwr_2 : 1;
        unsigned int scaler_3_y__cvdr_rt__sof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__dropped_vpwr_3 : 1;
        unsigned int scaler_3_uv__cvdr_rt__sof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__dropped_vpwr_4 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__sof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__dropped_vpwr_5 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__sof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__dropped_vpwr_6 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__sof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__dropped_vpwr_7 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__sof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__dropped_vpwr_8 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__sof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__dropped_vpwr_9 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__sof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__dropped_vpwr_10 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__sof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__sof_vpwr_11 : 1;
        unsigned int fbcyuv_1__cvdr_rt__dropped_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__sof_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__eof_vpwr_12 : 1;
        unsigned int isp_be_2__cvdr_rt__dropped_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vpwr_13 : 1;
        unsigned int otap_2_1__cvdr_rt__dropped_vpwr_14 : 1;
        unsigned int otap_2_1__cvdr_rt__sof_vpwr_14 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__dropped_vpwr_0 : 1;
        unsigned int otap_1_1__cvdr_rt__sof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__dropped_vpwr_1 : 1;
        unsigned int otap_1_2__cvdr_rt__sof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__dropped_vpwr_2 : 1;
        unsigned int scaler_3_y__cvdr_rt__sof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__dropped_vpwr_3 : 1;
        unsigned int scaler_3_uv__cvdr_rt__sof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__dropped_vpwr_4 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__sof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__dropped_vpwr_5 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__sof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__dropped_vpwr_6 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__sof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__dropped_vpwr_7 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__sof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__dropped_vpwr_8 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__sof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__dropped_vpwr_9 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__sof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__dropped_vpwr_10 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__sof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__sof_vpwr_11 : 1;
        unsigned int fbcyuv_1__cvdr_rt__dropped_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__sof_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__eof_vpwr_12 : 1;
        unsigned int isp_be_2__cvdr_rt__dropped_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vpwr_13 : 1;
        unsigned int otap_2_1__cvdr_rt__dropped_vpwr_14 : 1;
        unsigned int otap_2_1__cvdr_rt__sof_vpwr_14 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__dropped_vpwr_0 : 1;
        unsigned int otap_1_1__cvdr_rt__sof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__dropped_vpwr_1 : 1;
        unsigned int otap_1_2__cvdr_rt__sof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__dropped_vpwr_2 : 1;
        unsigned int scaler_3_y__cvdr_rt__sof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__dropped_vpwr_3 : 1;
        unsigned int scaler_3_uv__cvdr_rt__sof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__dropped_vpwr_4 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__sof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__dropped_vpwr_5 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__sof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__dropped_vpwr_6 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__sof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__dropped_vpwr_7 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__sof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__dropped_vpwr_8 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__sof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__dropped_vpwr_9 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__sof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__dropped_vpwr_10 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__sof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__sof_vpwr_11 : 1;
        unsigned int fbcyuv_1__cvdr_rt__dropped_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__sof_vpwr_12 : 1;
        unsigned int fbcyuv_1__cvdr_rt__eof_vpwr_12 : 1;
        unsigned int isp_be_2__cvdr_rt__dropped_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vpwr_13 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vpwr_13 : 1;
        unsigned int otap_2_1__cvdr_rt__dropped_vpwr_14 : 1;
        unsigned int otap_2_1__cvdr_rt__sof_vpwr_14 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_2_2__cvdr_rt__dropped_vpwr_15 : 1;
        unsigned int otap_2_2__cvdr_rt__sof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__dropped_vpwr_16 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;
        unsigned int stream_router_1__cvdr_rt__sof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__dropped_vpwr_17 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;
        unsigned int stream_router_2__cvdr_rt__sof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__dropped_vpwr_20 : 1;
        unsigned int stat3a_1__cvdr_rt__sof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__dropped_vpwr_21 : 1;
        unsigned int stat3a_2__cvdr_rt__sof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__dropped_vpwr_22 : 1;
        unsigned int stream_router_3__cvdr_rt__sof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__dropped_vpwr_23 : 1;
        unsigned int stream_router_4__cvdr_rt__sof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__dropped_vpwr_24 : 1;
        unsigned int stream_router_5__cvdr_rt__sof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__dropped_vpwr_25 : 1;
        unsigned int jpgenc__cvdr_rt__sof_vpwr_25 : 1;
        unsigned int fbdyuv_1__cvdr_rt__sof_vprd_0 : 1;
        unsigned int fbdyuv_1__cvdr_rt__eof_vprd_0 : 1;
        unsigned int scaler_x_2__cvdr_rt__sof_vprd_1 : 1;
        unsigned int scaler_x_2__cvdr_rt__eof_vprd_1 : 1;
        unsigned int isp_be_1__cvdr_rt__sof_vprd_2 : 1;
        unsigned int isp_be_1__cvdr_rt__eof_vprd_2 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vprd_3 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vprd_3 : 1;
        unsigned int itap_1_1__cvdr_rt__sof_vprd_4 : 1;
        unsigned int itap_1_1__cvdr_rt__eof_vprd_4 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_2_2__cvdr_rt__dropped_vpwr_15 : 1;
        unsigned int otap_2_2__cvdr_rt__sof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__dropped_vpwr_16 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;
        unsigned int stream_router_1__cvdr_rt__sof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__dropped_vpwr_17 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;
        unsigned int stream_router_2__cvdr_rt__sof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__dropped_vpwr_20 : 1;
        unsigned int stat3a_1__cvdr_rt__sof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__dropped_vpwr_21 : 1;
        unsigned int stat3a_2__cvdr_rt__sof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__dropped_vpwr_22 : 1;
        unsigned int stream_router_3__cvdr_rt__sof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__dropped_vpwr_23 : 1;
        unsigned int stream_router_4__cvdr_rt__sof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__dropped_vpwr_24 : 1;
        unsigned int stream_router_5__cvdr_rt__sof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__dropped_vpwr_25 : 1;
        unsigned int jpgenc__cvdr_rt__sof_vpwr_25 : 1;
        unsigned int fbdyuv_1__cvdr_rt__sof_vprd_0 : 1;
        unsigned int fbdyuv_1__cvdr_rt__eof_vprd_0 : 1;
        unsigned int scaler_x_2__cvdr_rt__sof_vprd_1 : 1;
        unsigned int scaler_x_2__cvdr_rt__eof_vprd_1 : 1;
        unsigned int isp_be_1__cvdr_rt__sof_vprd_2 : 1;
        unsigned int isp_be_1__cvdr_rt__eof_vprd_2 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vprd_3 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vprd_3 : 1;
        unsigned int itap_1_1__cvdr_rt__sof_vprd_4 : 1;
        unsigned int itap_1_1__cvdr_rt__eof_vprd_4 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_2_2__cvdr_rt__dropped_vpwr_15 : 1;
        unsigned int otap_2_2__cvdr_rt__sof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__dropped_vpwr_16 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;
        unsigned int stream_router_1__cvdr_rt__sof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__dropped_vpwr_17 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;
        unsigned int stream_router_2__cvdr_rt__sof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__dropped_vpwr_20 : 1;
        unsigned int stat3a_1__cvdr_rt__sof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__dropped_vpwr_21 : 1;
        unsigned int stat3a_2__cvdr_rt__sof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__dropped_vpwr_22 : 1;
        unsigned int stream_router_3__cvdr_rt__sof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__dropped_vpwr_23 : 1;
        unsigned int stream_router_4__cvdr_rt__sof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__dropped_vpwr_24 : 1;
        unsigned int stream_router_5__cvdr_rt__sof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__dropped_vpwr_25 : 1;
        unsigned int jpgenc__cvdr_rt__sof_vpwr_25 : 1;
        unsigned int fbdyuv_1__cvdr_rt__sof_vprd_0 : 1;
        unsigned int fbdyuv_1__cvdr_rt__eof_vprd_0 : 1;
        unsigned int scaler_x_2__cvdr_rt__sof_vprd_1 : 1;
        unsigned int scaler_x_2__cvdr_rt__eof_vprd_1 : 1;
        unsigned int isp_be_1__cvdr_rt__sof_vprd_2 : 1;
        unsigned int isp_be_1__cvdr_rt__eof_vprd_2 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vprd_3 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vprd_3 : 1;
        unsigned int itap_1_1__cvdr_rt__sof_vprd_4 : 1;
        unsigned int itap_1_1__cvdr_rt__eof_vprd_4 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_2_2__cvdr_rt__dropped_vpwr_15 : 1;
        unsigned int otap_2_2__cvdr_rt__sof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__dropped_vpwr_16 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;
        unsigned int stream_router_1__cvdr_rt__sof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__dropped_vpwr_17 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;
        unsigned int stream_router_2__cvdr_rt__sof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__dropped_vpwr_20 : 1;
        unsigned int stat3a_1__cvdr_rt__sof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__dropped_vpwr_21 : 1;
        unsigned int stat3a_2__cvdr_rt__sof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__dropped_vpwr_22 : 1;
        unsigned int stream_router_3__cvdr_rt__sof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__dropped_vpwr_23 : 1;
        unsigned int stream_router_4__cvdr_rt__sof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__dropped_vpwr_24 : 1;
        unsigned int stream_router_5__cvdr_rt__sof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__dropped_vpwr_25 : 1;
        unsigned int jpgenc__cvdr_rt__sof_vpwr_25 : 1;
        unsigned int fbdyuv_1__cvdr_rt__sof_vprd_0 : 1;
        unsigned int fbdyuv_1__cvdr_rt__eof_vprd_0 : 1;
        unsigned int scaler_x_2__cvdr_rt__sof_vprd_1 : 1;
        unsigned int scaler_x_2__cvdr_rt__eof_vprd_1 : 1;
        unsigned int isp_be_1__cvdr_rt__sof_vprd_2 : 1;
        unsigned int isp_be_1__cvdr_rt__eof_vprd_2 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vprd_3 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vprd_3 : 1;
        unsigned int itap_1_1__cvdr_rt__sof_vprd_4 : 1;
        unsigned int itap_1_1__cvdr_rt__eof_vprd_4 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_2_2__cvdr_rt__dropped_vpwr_15 : 1;
        unsigned int otap_2_2__cvdr_rt__sof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__dropped_vpwr_16 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;
        unsigned int stream_router_1__cvdr_rt__sof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__dropped_vpwr_17 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;
        unsigned int stream_router_2__cvdr_rt__sof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__dropped_vpwr_20 : 1;
        unsigned int stat3a_1__cvdr_rt__sof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__dropped_vpwr_21 : 1;
        unsigned int stat3a_2__cvdr_rt__sof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__dropped_vpwr_22 : 1;
        unsigned int stream_router_3__cvdr_rt__sof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__dropped_vpwr_23 : 1;
        unsigned int stream_router_4__cvdr_rt__sof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__dropped_vpwr_24 : 1;
        unsigned int stream_router_5__cvdr_rt__sof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__dropped_vpwr_25 : 1;
        unsigned int jpgenc__cvdr_rt__sof_vpwr_25 : 1;
        unsigned int fbdyuv_1__cvdr_rt__sof_vprd_0 : 1;
        unsigned int fbdyuv_1__cvdr_rt__eof_vprd_0 : 1;
        unsigned int scaler_x_2__cvdr_rt__sof_vprd_1 : 1;
        unsigned int scaler_x_2__cvdr_rt__eof_vprd_1 : 1;
        unsigned int isp_be_1__cvdr_rt__sof_vprd_2 : 1;
        unsigned int isp_be_1__cvdr_rt__eof_vprd_2 : 1;
        unsigned int isp_be_2__cvdr_rt__sof_vprd_3 : 1;
        unsigned int isp_be_2__cvdr_rt__eof_vprd_3 : 1;
        unsigned int itap_1_1__cvdr_rt__sof_vprd_4 : 1;
        unsigned int itap_1_1__cvdr_rt__eof_vprd_4 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itap_2_1__cvdr_rt__sof_vprd_5 : 1;
        unsigned int itap_2_1__cvdr_rt__eof_vprd_5 : 1;
        unsigned int itap_1_2__cvdr_rt__sof_vprd_6 : 1;
        unsigned int itap_1_2__cvdr_rt__eof_vprd_6 : 1;
        unsigned int itap_2_2__cvdr_rt__sof_vprd_7 : 1;
        unsigned int itap_2_2__cvdr_rt__eof_vprd_7 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vprd_8 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vprd_8 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vprd_9 : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vprd_9 : 1;
        unsigned int prescaler__start_of_frame1 : 1;
        unsigned int prescaler__start_of_frame2 : 1;
        unsigned int scaler_1_1__start_of_frame : 1;
        unsigned int scaler_1_1__end_of_rescale : 1;
        unsigned int scaler_2_1__start_of_frame : 1;
        unsigned int scaler_2_1__end_of_rescale : 1;
        unsigned int scaler_1_2__start_of_frame : 1;
        unsigned int scaler_1_2__end_of_rescale : 1;
        unsigned int scaler_2_2__start_of_frame : 1;
        unsigned int scaler_2_2__end_of_rescale : 1;
        unsigned int scaler_3__start_of_frame : 1;
        unsigned int stream_router__eol_0 : 1;
        unsigned int stream_router__eol_1 : 1;
        unsigned int bas_1__start_of_frame : 1;
        unsigned int bas_1__end_of_frame : 1;
        unsigned int bas_2__start_of_frame : 1;
        unsigned int bas_2__end_of_frame : 1;
        unsigned int blc_1__frame_in : 1;
        unsigned int blc_2__frame_in : 1;
        unsigned int fbcraw_1__fbc_done : 1;
        unsigned int fbcraw_2__fbc_done : 1;
        unsigned int fbdraw_1__fbd_done : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame1_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame1_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame2_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame2_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__start_of_frame_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__start_of_frame_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__end_of_rescale_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__end_of_rescale_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__start_of_frame_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__start_of_frame_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__end_of_rescale_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__end_of_rescale_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__start_of_frame_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__start_of_frame_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__end_of_rescale_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__end_of_rescale_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__start_of_frame_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__start_of_frame_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__end_of_rescale_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__end_of_rescale_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_3__start_of_frame_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_3__start_of_frame_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_0_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_0_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_1_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_1_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__start_of_frame_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__start_of_frame_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__end_of_frame_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__end_of_frame_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__start_of_frame_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__start_of_frame_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__end_of_frame_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__end_of_frame_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_1__frame_in_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_1__frame_in_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_2__frame_in_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_2__frame_in_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_1__fbc_done_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_1__fbc_done_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_2__fbc_done_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_2__fbc_done_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbdraw_1__fbd_done_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbdraw_1__fbd_done_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itap_2_1__cvdr_rt__sof_vprd_5 : 1;
        unsigned int itap_2_1__cvdr_rt__eof_vprd_5 : 1;
        unsigned int itap_1_2__cvdr_rt__sof_vprd_6 : 1;
        unsigned int itap_1_2__cvdr_rt__eof_vprd_6 : 1;
        unsigned int itap_2_2__cvdr_rt__sof_vprd_7 : 1;
        unsigned int itap_2_2__cvdr_rt__eof_vprd_7 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vprd_8 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vprd_8 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vprd_9 : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vprd_9 : 1;
        unsigned int prescaler__start_of_frame1 : 1;
        unsigned int prescaler__start_of_frame2 : 1;
        unsigned int scaler_1_1__start_of_frame : 1;
        unsigned int scaler_1_1__end_of_rescale : 1;
        unsigned int scaler_2_1__start_of_frame : 1;
        unsigned int scaler_2_1__end_of_rescale : 1;
        unsigned int scaler_1_2__start_of_frame : 1;
        unsigned int scaler_1_2__end_of_rescale : 1;
        unsigned int scaler_2_2__start_of_frame : 1;
        unsigned int scaler_2_2__end_of_rescale : 1;
        unsigned int scaler_3__start_of_frame : 1;
        unsigned int stream_router__eol_0 : 1;
        unsigned int stream_router__eol_1 : 1;
        unsigned int bas_1__start_of_frame : 1;
        unsigned int bas_1__end_of_frame : 1;
        unsigned int bas_2__start_of_frame : 1;
        unsigned int bas_2__end_of_frame : 1;
        unsigned int blc_1__frame_in : 1;
        unsigned int blc_2__frame_in : 1;
        unsigned int fbcraw_1__fbc_done : 1;
        unsigned int fbcraw_2__fbc_done : 1;
        unsigned int fbdraw_1__fbd_done : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame1_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame1_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame2_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame2_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__start_of_frame_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__start_of_frame_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__end_of_rescale_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__end_of_rescale_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__start_of_frame_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__start_of_frame_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__end_of_rescale_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__end_of_rescale_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__start_of_frame_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__start_of_frame_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__end_of_rescale_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__end_of_rescale_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__start_of_frame_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__start_of_frame_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__end_of_rescale_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__end_of_rescale_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_3__start_of_frame_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_3__start_of_frame_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_0_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_0_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_1_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_1_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__start_of_frame_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__start_of_frame_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__end_of_frame_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__end_of_frame_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__start_of_frame_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__start_of_frame_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__end_of_frame_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__end_of_frame_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_1__frame_in_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_1__frame_in_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_2__frame_in_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_2__frame_in_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_1__fbc_done_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_1__fbc_done_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_2__fbc_done_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_2__fbc_done_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbdraw_1__fbd_done_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbdraw_1__fbd_done_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itap_2_1__cvdr_rt__sof_vprd_5 : 1;
        unsigned int itap_2_1__cvdr_rt__eof_vprd_5 : 1;
        unsigned int itap_1_2__cvdr_rt__sof_vprd_6 : 1;
        unsigned int itap_1_2__cvdr_rt__eof_vprd_6 : 1;
        unsigned int itap_2_2__cvdr_rt__sof_vprd_7 : 1;
        unsigned int itap_2_2__cvdr_rt__eof_vprd_7 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vprd_8 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vprd_8 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vprd_9 : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vprd_9 : 1;
        unsigned int prescaler__start_of_frame1 : 1;
        unsigned int prescaler__start_of_frame2 : 1;
        unsigned int scaler_1_1__start_of_frame : 1;
        unsigned int scaler_1_1__end_of_rescale : 1;
        unsigned int scaler_2_1__start_of_frame : 1;
        unsigned int scaler_2_1__end_of_rescale : 1;
        unsigned int scaler_1_2__start_of_frame : 1;
        unsigned int scaler_1_2__end_of_rescale : 1;
        unsigned int scaler_2_2__start_of_frame : 1;
        unsigned int scaler_2_2__end_of_rescale : 1;
        unsigned int scaler_3__start_of_frame : 1;
        unsigned int stream_router__eol_0 : 1;
        unsigned int stream_router__eol_1 : 1;
        unsigned int bas_1__start_of_frame : 1;
        unsigned int bas_1__end_of_frame : 1;
        unsigned int bas_2__start_of_frame : 1;
        unsigned int bas_2__end_of_frame : 1;
        unsigned int blc_1__frame_in : 1;
        unsigned int blc_2__frame_in : 1;
        unsigned int fbcraw_1__fbc_done : 1;
        unsigned int fbcraw_2__fbc_done : 1;
        unsigned int fbdraw_1__fbd_done : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame1_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame1_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame2_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame2_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__start_of_frame_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__start_of_frame_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__end_of_rescale_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__end_of_rescale_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__start_of_frame_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__start_of_frame_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__end_of_rescale_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__end_of_rescale_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__start_of_frame_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__start_of_frame_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__end_of_rescale_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__end_of_rescale_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__start_of_frame_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__start_of_frame_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__end_of_rescale_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__end_of_rescale_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_3__start_of_frame_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_3__start_of_frame_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_0_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_0_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_1_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_1_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__start_of_frame_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__start_of_frame_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__end_of_frame_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__end_of_frame_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__start_of_frame_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__start_of_frame_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__end_of_frame_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__end_of_frame_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_1__frame_in_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_1__frame_in_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_2__frame_in_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_2__frame_in_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_1__fbc_done_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_1__fbc_done_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_2__fbc_done_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_2__fbc_done_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbdraw_1__fbd_done_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbdraw_1__fbd_done_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itap_2_1__cvdr_rt__sof_vprd_5 : 1;
        unsigned int itap_2_1__cvdr_rt__eof_vprd_5 : 1;
        unsigned int itap_1_2__cvdr_rt__sof_vprd_6 : 1;
        unsigned int itap_1_2__cvdr_rt__eof_vprd_6 : 1;
        unsigned int itap_2_2__cvdr_rt__sof_vprd_7 : 1;
        unsigned int itap_2_2__cvdr_rt__eof_vprd_7 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vprd_8 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vprd_8 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vprd_9 : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vprd_9 : 1;
        unsigned int prescaler__start_of_frame1 : 1;
        unsigned int prescaler__start_of_frame2 : 1;
        unsigned int scaler_1_1__start_of_frame : 1;
        unsigned int scaler_1_1__end_of_rescale : 1;
        unsigned int scaler_2_1__start_of_frame : 1;
        unsigned int scaler_2_1__end_of_rescale : 1;
        unsigned int scaler_1_2__start_of_frame : 1;
        unsigned int scaler_1_2__end_of_rescale : 1;
        unsigned int scaler_2_2__start_of_frame : 1;
        unsigned int scaler_2_2__end_of_rescale : 1;
        unsigned int scaler_3__start_of_frame : 1;
        unsigned int stream_router__eol_0 : 1;
        unsigned int stream_router__eol_1 : 1;
        unsigned int bas_1__start_of_frame : 1;
        unsigned int bas_1__end_of_frame : 1;
        unsigned int bas_2__start_of_frame : 1;
        unsigned int bas_2__end_of_frame : 1;
        unsigned int blc_1__frame_in : 1;
        unsigned int blc_2__frame_in : 1;
        unsigned int fbcraw_1__fbc_done : 1;
        unsigned int fbcraw_2__fbc_done : 1;
        unsigned int fbdraw_1__fbd_done : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame1_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame1_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame2_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame2_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__start_of_frame_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__start_of_frame_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__end_of_rescale_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__end_of_rescale_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__start_of_frame_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__start_of_frame_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__end_of_rescale_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__end_of_rescale_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__start_of_frame_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__start_of_frame_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__end_of_rescale_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__end_of_rescale_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__start_of_frame_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__start_of_frame_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__end_of_rescale_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__end_of_rescale_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_3__start_of_frame_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_3__start_of_frame_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_0_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_0_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_1_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_1_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__start_of_frame_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__start_of_frame_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__end_of_frame_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__end_of_frame_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__start_of_frame_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__start_of_frame_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__end_of_frame_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__end_of_frame_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_1__frame_in_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_1__frame_in_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_2__frame_in_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_2__frame_in_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_1__fbc_done_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_1__fbc_done_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_2__fbc_done_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_2__fbc_done_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbdraw_1__fbd_done_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbdraw_1__fbd_done_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itap_2_1__cvdr_rt__sof_vprd_5 : 1;
        unsigned int itap_2_1__cvdr_rt__eof_vprd_5 : 1;
        unsigned int itap_1_2__cvdr_rt__sof_vprd_6 : 1;
        unsigned int itap_1_2__cvdr_rt__eof_vprd_6 : 1;
        unsigned int itap_2_2__cvdr_rt__sof_vprd_7 : 1;
        unsigned int itap_2_2__cvdr_rt__eof_vprd_7 : 1;
        unsigned int isp_fe_1__cvdr_rt__sof_vprd_8 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vprd_8 : 1;
        unsigned int isp_fe_2__cvdr_rt__sof_vprd_9 : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vprd_9 : 1;
        unsigned int prescaler__start_of_frame1 : 1;
        unsigned int prescaler__start_of_frame2 : 1;
        unsigned int scaler_1_1__start_of_frame : 1;
        unsigned int scaler_1_1__end_of_rescale : 1;
        unsigned int scaler_2_1__start_of_frame : 1;
        unsigned int scaler_2_1__end_of_rescale : 1;
        unsigned int scaler_1_2__start_of_frame : 1;
        unsigned int scaler_1_2__end_of_rescale : 1;
        unsigned int scaler_2_2__start_of_frame : 1;
        unsigned int scaler_2_2__end_of_rescale : 1;
        unsigned int scaler_3__start_of_frame : 1;
        unsigned int stream_router__eol_0 : 1;
        unsigned int stream_router__eol_1 : 1;
        unsigned int bas_1__start_of_frame : 1;
        unsigned int bas_1__end_of_frame : 1;
        unsigned int bas_2__start_of_frame : 1;
        unsigned int bas_2__end_of_frame : 1;
        unsigned int blc_1__frame_in : 1;
        unsigned int blc_2__frame_in : 1;
        unsigned int fbcraw_1__fbc_done : 1;
        unsigned int fbcraw_2__fbc_done : 1;
        unsigned int fbdraw_1__fbd_done : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame1_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame1_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame2_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame2_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__start_of_frame_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__start_of_frame_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__end_of_rescale_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__end_of_rescale_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__start_of_frame_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__start_of_frame_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__end_of_rescale_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__end_of_rescale_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__start_of_frame_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__start_of_frame_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__end_of_rescale_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__end_of_rescale_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__start_of_frame_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__start_of_frame_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__end_of_rescale_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__end_of_rescale_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_3__start_of_frame_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_3__start_of_frame_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_0_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_0_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_1_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_1_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__start_of_frame_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__start_of_frame_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__end_of_frame_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__end_of_frame_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__start_of_frame_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__start_of_frame_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__end_of_frame_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__end_of_frame_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_1__frame_in_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_1__frame_in_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_2__frame_in_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_2__frame_in_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_1__fbc_done_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_1__fbc_done_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_2__fbc_done_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_2__fbc_done_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbdraw_1__fbd_done_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbdraw_1__fbd_done_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fbdraw_2__fbd_done : 1;
        unsigned int fbcyuv_1__fbc_done : 1;
        unsigned int reserved_0 : 1;
        unsigned int fbdyuv_1__fbd_done : 1;
        unsigned int reserved_1 : 1;
        unsigned int tnr_1__frame_filtering_done : 1;
        unsigned int flash__flash_cap : 1;
        unsigned int otap_2_1__cvdr_rt__eol_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eol_vpwr_15 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
        unsigned int reserved_19 : 1;
        unsigned int reserved_20 : 1;
        unsigned int reserved_21 : 1;
        unsigned int reserved_22 : 1;
        unsigned int reserved_23 : 1;
        unsigned int reserved_24 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdraw_2__fbd_done_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdraw_2__fbd_done_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbcyuv_1__fbc_done_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbcyuv_1__fbc_done_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdyuv_1__fbd_done_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdyuv_1__fbd_done_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_tnr_1__frame_filtering_done_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_tnr_1__frame_filtering_done_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_flash__flash_cap_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_flash__flash_cap_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fbdraw_2__fbd_done : 1;
        unsigned int fbcyuv_1__fbc_done : 1;
        unsigned int reserved_0 : 1;
        unsigned int fbdyuv_1__fbd_done : 1;
        unsigned int reserved_1 : 1;
        unsigned int tnr_1__frame_filtering_done : 1;
        unsigned int flash__flash_cap : 1;
        unsigned int otap_2_1__cvdr_rt__eol_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eol_vpwr_15 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
        unsigned int reserved_19 : 1;
        unsigned int reserved_20 : 1;
        unsigned int reserved_21 : 1;
        unsigned int reserved_22 : 1;
        unsigned int reserved_23 : 1;
        unsigned int reserved_24 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdraw_2__fbd_done_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdraw_2__fbd_done_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbcyuv_1__fbc_done_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbcyuv_1__fbc_done_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdyuv_1__fbd_done_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdyuv_1__fbd_done_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_tnr_1__frame_filtering_done_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_tnr_1__frame_filtering_done_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_flash__flash_cap_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_flash__flash_cap_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fbdraw_2__fbd_done : 1;
        unsigned int fbcyuv_1__fbc_done : 1;
        unsigned int reserved_0 : 1;
        unsigned int fbdyuv_1__fbd_done : 1;
        unsigned int reserved_1 : 1;
        unsigned int tnr_1__frame_filtering_done : 1;
        unsigned int flash__flash_cap : 1;
        unsigned int otap_2_1__cvdr_rt__eol_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eol_vpwr_15 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
        unsigned int reserved_19 : 1;
        unsigned int reserved_20 : 1;
        unsigned int reserved_21 : 1;
        unsigned int reserved_22 : 1;
        unsigned int reserved_23 : 1;
        unsigned int reserved_24 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdraw_2__fbd_done_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdraw_2__fbd_done_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbcyuv_1__fbc_done_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbcyuv_1__fbc_done_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdyuv_1__fbd_done_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdyuv_1__fbd_done_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_tnr_1__frame_filtering_done_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_tnr_1__frame_filtering_done_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_flash__flash_cap_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_flash__flash_cap_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fbdraw_2__fbd_done : 1;
        unsigned int fbcyuv_1__fbc_done : 1;
        unsigned int reserved_0 : 1;
        unsigned int fbdyuv_1__fbd_done : 1;
        unsigned int reserved_1 : 1;
        unsigned int tnr_1__frame_filtering_done : 1;
        unsigned int flash__flash_cap : 1;
        unsigned int otap_2_1__cvdr_rt__eol_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eol_vpwr_15 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
        unsigned int reserved_19 : 1;
        unsigned int reserved_20 : 1;
        unsigned int reserved_21 : 1;
        unsigned int reserved_22 : 1;
        unsigned int reserved_23 : 1;
        unsigned int reserved_24 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdraw_2__fbd_done_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdraw_2__fbd_done_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbcyuv_1__fbc_done_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbcyuv_1__fbc_done_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdyuv_1__fbd_done_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdyuv_1__fbd_done_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_tnr_1__frame_filtering_done_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_tnr_1__frame_filtering_done_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_flash__flash_cap_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_flash__flash_cap_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fbdraw_2__fbd_done : 1;
        unsigned int fbcyuv_1__fbc_done : 1;
        unsigned int reserved_0 : 1;
        unsigned int fbdyuv_1__fbd_done : 1;
        unsigned int reserved_1 : 1;
        unsigned int tnr_1__frame_filtering_done : 1;
        unsigned int flash__flash_cap : 1;
        unsigned int otap_2_1__cvdr_rt__eol_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eol_vpwr_15 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
        unsigned int reserved_19 : 1;
        unsigned int reserved_20 : 1;
        unsigned int reserved_21 : 1;
        unsigned int reserved_22 : 1;
        unsigned int reserved_23 : 1;
        unsigned int reserved_24 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdraw_2__fbd_done_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdraw_2__fbd_done_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbcyuv_1__fbc_done_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbcyuv_1__fbc_done_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdyuv_1__fbd_done_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdyuv_1__fbd_done_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_tnr_1__frame_filtering_done_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_tnr_1__frame_filtering_done_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_flash__flash_cap_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_flash__flash_cap_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvdr_rt__axi_wr_full : 1;
        unsigned int cvdr_sram__axi_wr_full : 1;
        unsigned int isp_fe_1__fcm__short_wr_evt_0 : 1;
        unsigned int isp_fe_1__fcm__short_rd_evt_0 : 1;
        unsigned int isp_fe_2__fcm__short_wr_evt_1 : 1;
        unsigned int isp_fe_2__fcm__short_rd_evt_1 : 1;
        unsigned int scaler_1_1_y__fcm__short_wr_evt_2 : 1;
        unsigned int scaler_1_1_y__fcm__short_rd_evt_2 : 1;
        unsigned int scaler_1_1_uv__fcm__short_wr_evt_3 : 1;
        unsigned int scaler_1_1_uv__fcm__short_rd_evt_3 : 1;
        unsigned int scaler_1_2_y__fcm__short_wr_evt_4 : 1;
        unsigned int scaler_1_2_y__fcm__short_rd_evt_4 : 1;
        unsigned int scaler_1_2_uv__fcm__short_wr_evt_5 : 1;
        unsigned int scaler_1_2_uv__fcm__short_rd_evt_5 : 1;
        unsigned int prescaler__end_of_frame_error : 1;
        unsigned int stream_router__cam_a_ovf : 1;
        unsigned int stream_router__cam_b_ovf : 1;
        unsigned int stream_router__cam_c_ovf : 1;
        unsigned int stream_router__reformater_h_err_0 : 1;
        unsigned int stream_router__reformater_h_err_1 : 1;
        unsigned int stream_router__reformater_h_err_2 : 1;
        unsigned int stream_router__reformater_h_err_3 : 1;
        unsigned int stream_router__reformater_h_err_4 : 1;
        unsigned int stream_router__reformater_h_err_5 : 1;
        unsigned int stream_router__reformater_h_err_6 : 1;
        unsigned int stream_router__reformater_h_err_7 : 1;
        unsigned int stream_router__reformater_err_0 : 1;
        unsigned int stream_router__reformater_err_1 : 1;
        unsigned int stream_router__reformater_err_2 : 1;
        unsigned int stream_router__reformater_err_3 : 1;
        unsigned int stream_router__reformater_err_4 : 1;
        unsigned int stream_router__reformater_err_5 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_rt__axi_wr_full_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_rt__axi_wr_full_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_sram__axi_wr_full_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_sram__axi_wr_full_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_prescaler__end_of_frame_error_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_prescaler__end_of_frame_error_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_a_ovf_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_a_ovf_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_b_ovf_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_b_ovf_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_c_ovf_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_c_ovf_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_0_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_0_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_1_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_1_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_2_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_2_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_3_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_3_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_4_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_4_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_5_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_5_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_6_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_6_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_7_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_7_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_0_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_0_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_5_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvdr_rt__axi_wr_full : 1;
        unsigned int cvdr_sram__axi_wr_full : 1;
        unsigned int isp_fe_1__fcm__short_wr_evt_0 : 1;
        unsigned int isp_fe_1__fcm__short_rd_evt_0 : 1;
        unsigned int isp_fe_2__fcm__short_wr_evt_1 : 1;
        unsigned int isp_fe_2__fcm__short_rd_evt_1 : 1;
        unsigned int scaler_1_1_y__fcm__short_wr_evt_2 : 1;
        unsigned int scaler_1_1_y__fcm__short_rd_evt_2 : 1;
        unsigned int scaler_1_1_uv__fcm__short_wr_evt_3 : 1;
        unsigned int scaler_1_1_uv__fcm__short_rd_evt_3 : 1;
        unsigned int scaler_1_2_y__fcm__short_wr_evt_4 : 1;
        unsigned int scaler_1_2_y__fcm__short_rd_evt_4 : 1;
        unsigned int scaler_1_2_uv__fcm__short_wr_evt_5 : 1;
        unsigned int scaler_1_2_uv__fcm__short_rd_evt_5 : 1;
        unsigned int prescaler__end_of_frame_error : 1;
        unsigned int stream_router__cam_a_ovf : 1;
        unsigned int stream_router__cam_b_ovf : 1;
        unsigned int stream_router__cam_c_ovf : 1;
        unsigned int stream_router__reformater_h_err_0 : 1;
        unsigned int stream_router__reformater_h_err_1 : 1;
        unsigned int stream_router__reformater_h_err_2 : 1;
        unsigned int stream_router__reformater_h_err_3 : 1;
        unsigned int stream_router__reformater_h_err_4 : 1;
        unsigned int stream_router__reformater_h_err_5 : 1;
        unsigned int stream_router__reformater_h_err_6 : 1;
        unsigned int stream_router__reformater_h_err_7 : 1;
        unsigned int stream_router__reformater_err_0 : 1;
        unsigned int stream_router__reformater_err_1 : 1;
        unsigned int stream_router__reformater_err_2 : 1;
        unsigned int stream_router__reformater_err_3 : 1;
        unsigned int stream_router__reformater_err_4 : 1;
        unsigned int stream_router__reformater_err_5 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_rt__axi_wr_full_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_rt__axi_wr_full_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_sram__axi_wr_full_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_sram__axi_wr_full_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_prescaler__end_of_frame_error_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_prescaler__end_of_frame_error_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_a_ovf_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_a_ovf_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_b_ovf_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_b_ovf_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_c_ovf_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_c_ovf_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_0_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_0_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_1_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_1_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_2_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_2_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_3_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_3_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_4_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_4_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_5_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_5_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_6_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_6_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_7_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_7_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_0_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_0_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_5_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvdr_rt__axi_wr_full : 1;
        unsigned int cvdr_sram__axi_wr_full : 1;
        unsigned int isp_fe_1__fcm__short_wr_evt_0 : 1;
        unsigned int isp_fe_1__fcm__short_rd_evt_0 : 1;
        unsigned int isp_fe_2__fcm__short_wr_evt_1 : 1;
        unsigned int isp_fe_2__fcm__short_rd_evt_1 : 1;
        unsigned int scaler_1_1_y__fcm__short_wr_evt_2 : 1;
        unsigned int scaler_1_1_y__fcm__short_rd_evt_2 : 1;
        unsigned int scaler_1_1_uv__fcm__short_wr_evt_3 : 1;
        unsigned int scaler_1_1_uv__fcm__short_rd_evt_3 : 1;
        unsigned int scaler_1_2_y__fcm__short_wr_evt_4 : 1;
        unsigned int scaler_1_2_y__fcm__short_rd_evt_4 : 1;
        unsigned int scaler_1_2_uv__fcm__short_wr_evt_5 : 1;
        unsigned int scaler_1_2_uv__fcm__short_rd_evt_5 : 1;
        unsigned int prescaler__end_of_frame_error : 1;
        unsigned int stream_router__cam_a_ovf : 1;
        unsigned int stream_router__cam_b_ovf : 1;
        unsigned int stream_router__cam_c_ovf : 1;
        unsigned int stream_router__reformater_h_err_0 : 1;
        unsigned int stream_router__reformater_h_err_1 : 1;
        unsigned int stream_router__reformater_h_err_2 : 1;
        unsigned int stream_router__reformater_h_err_3 : 1;
        unsigned int stream_router__reformater_h_err_4 : 1;
        unsigned int stream_router__reformater_h_err_5 : 1;
        unsigned int stream_router__reformater_h_err_6 : 1;
        unsigned int stream_router__reformater_h_err_7 : 1;
        unsigned int stream_router__reformater_err_0 : 1;
        unsigned int stream_router__reformater_err_1 : 1;
        unsigned int stream_router__reformater_err_2 : 1;
        unsigned int stream_router__reformater_err_3 : 1;
        unsigned int stream_router__reformater_err_4 : 1;
        unsigned int stream_router__reformater_err_5 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_rt__axi_wr_full_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_rt__axi_wr_full_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_sram__axi_wr_full_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_sram__axi_wr_full_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_prescaler__end_of_frame_error_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_prescaler__end_of_frame_error_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_a_ovf_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_a_ovf_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_b_ovf_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_b_ovf_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_c_ovf_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_c_ovf_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_0_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_0_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_1_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_1_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_2_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_2_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_3_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_3_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_4_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_4_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_5_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_5_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_6_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_6_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_7_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_7_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_0_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_0_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_5_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvdr_rt__axi_wr_full : 1;
        unsigned int cvdr_sram__axi_wr_full : 1;
        unsigned int isp_fe_1__fcm__short_wr_evt_0 : 1;
        unsigned int isp_fe_1__fcm__short_rd_evt_0 : 1;
        unsigned int isp_fe_2__fcm__short_wr_evt_1 : 1;
        unsigned int isp_fe_2__fcm__short_rd_evt_1 : 1;
        unsigned int scaler_1_1_y__fcm__short_wr_evt_2 : 1;
        unsigned int scaler_1_1_y__fcm__short_rd_evt_2 : 1;
        unsigned int scaler_1_1_uv__fcm__short_wr_evt_3 : 1;
        unsigned int scaler_1_1_uv__fcm__short_rd_evt_3 : 1;
        unsigned int scaler_1_2_y__fcm__short_wr_evt_4 : 1;
        unsigned int scaler_1_2_y__fcm__short_rd_evt_4 : 1;
        unsigned int scaler_1_2_uv__fcm__short_wr_evt_5 : 1;
        unsigned int scaler_1_2_uv__fcm__short_rd_evt_5 : 1;
        unsigned int prescaler__end_of_frame_error : 1;
        unsigned int stream_router__cam_a_ovf : 1;
        unsigned int stream_router__cam_b_ovf : 1;
        unsigned int stream_router__cam_c_ovf : 1;
        unsigned int stream_router__reformater_h_err_0 : 1;
        unsigned int stream_router__reformater_h_err_1 : 1;
        unsigned int stream_router__reformater_h_err_2 : 1;
        unsigned int stream_router__reformater_h_err_3 : 1;
        unsigned int stream_router__reformater_h_err_4 : 1;
        unsigned int stream_router__reformater_h_err_5 : 1;
        unsigned int stream_router__reformater_h_err_6 : 1;
        unsigned int stream_router__reformater_h_err_7 : 1;
        unsigned int stream_router__reformater_err_0 : 1;
        unsigned int stream_router__reformater_err_1 : 1;
        unsigned int stream_router__reformater_err_2 : 1;
        unsigned int stream_router__reformater_err_3 : 1;
        unsigned int stream_router__reformater_err_4 : 1;
        unsigned int stream_router__reformater_err_5 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_rt__axi_wr_full_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_rt__axi_wr_full_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_sram__axi_wr_full_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_sram__axi_wr_full_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_prescaler__end_of_frame_error_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_prescaler__end_of_frame_error_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_a_ovf_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_a_ovf_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_b_ovf_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_b_ovf_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_c_ovf_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_c_ovf_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_0_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_0_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_1_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_1_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_2_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_2_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_3_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_3_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_4_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_4_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_5_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_5_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_6_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_6_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_7_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_7_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_0_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_0_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_5_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cvdr_rt__axi_wr_full : 1;
        unsigned int cvdr_sram__axi_wr_full : 1;
        unsigned int isp_fe_1__fcm__short_wr_evt_0 : 1;
        unsigned int isp_fe_1__fcm__short_rd_evt_0 : 1;
        unsigned int isp_fe_2__fcm__short_wr_evt_1 : 1;
        unsigned int isp_fe_2__fcm__short_rd_evt_1 : 1;
        unsigned int scaler_1_1_y__fcm__short_wr_evt_2 : 1;
        unsigned int scaler_1_1_y__fcm__short_rd_evt_2 : 1;
        unsigned int scaler_1_1_uv__fcm__short_wr_evt_3 : 1;
        unsigned int scaler_1_1_uv__fcm__short_rd_evt_3 : 1;
        unsigned int scaler_1_2_y__fcm__short_wr_evt_4 : 1;
        unsigned int scaler_1_2_y__fcm__short_rd_evt_4 : 1;
        unsigned int scaler_1_2_uv__fcm__short_wr_evt_5 : 1;
        unsigned int scaler_1_2_uv__fcm__short_rd_evt_5 : 1;
        unsigned int prescaler__end_of_frame_error : 1;
        unsigned int stream_router__cam_a_ovf : 1;
        unsigned int stream_router__cam_b_ovf : 1;
        unsigned int stream_router__cam_c_ovf : 1;
        unsigned int stream_router__reformater_h_err_0 : 1;
        unsigned int stream_router__reformater_h_err_1 : 1;
        unsigned int stream_router__reformater_h_err_2 : 1;
        unsigned int stream_router__reformater_h_err_3 : 1;
        unsigned int stream_router__reformater_h_err_4 : 1;
        unsigned int stream_router__reformater_h_err_5 : 1;
        unsigned int stream_router__reformater_h_err_6 : 1;
        unsigned int stream_router__reformater_h_err_7 : 1;
        unsigned int stream_router__reformater_err_0 : 1;
        unsigned int stream_router__reformater_err_1 : 1;
        unsigned int stream_router__reformater_err_2 : 1;
        unsigned int stream_router__reformater_err_3 : 1;
        unsigned int stream_router__reformater_err_4 : 1;
        unsigned int stream_router__reformater_err_5 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_rt__axi_wr_full_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_rt__axi_wr_full_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_sram__axi_wr_full_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_sram__axi_wr_full_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_prescaler__end_of_frame_error_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_prescaler__end_of_frame_error_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_a_ovf_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_a_ovf_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_b_ovf_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_b_ovf_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_c_ovf_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_c_ovf_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_0_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_0_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_1_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_1_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_2_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_2_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_3_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_3_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_4_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_4_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_5_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_5_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_6_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_6_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_7_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_7_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_0_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_0_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_3_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_3_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_4_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_4_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_5_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_router__reformater_err_6 : 1;
        unsigned int stream_router__reformater_err_7 : 1;
        unsigned int stream_router__reformater_frame_dropped_0 : 1;
        unsigned int stream_router__reformater_frame_dropped_1 : 1;
        unsigned int stream_router__reformater_frame_dropped_2 : 1;
        unsigned int stream_router__reformater_frame_dropped_3 : 1;
        unsigned int stream_router__reformater_frame_dropped_4 : 1;
        unsigned int stream_router__reformater_frame_dropped_5 : 1;
        unsigned int stream_router__reformater_frame_dropped_6 : 1;
        unsigned int stream_router__reformater_frame_dropped_7 : 1;
        unsigned int frame_merger__end_of_frame_error : 1;
        unsigned int cvdr_rt__axi_wr_resp_err : 1;
        unsigned int cvdr_rt__axi_rd_resp_err : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_6_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_6_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_7_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_7_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_3_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_3_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_4_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_4_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_5_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_5_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_6_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_6_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_7_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_7_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_frame_merger__end_of_frame_error_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_frame_merger__end_of_frame_error_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_wr_resp_err_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_wr_resp_err_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_rd_resp_err_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_rd_resp_err_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_router__reformater_err_6 : 1;
        unsigned int stream_router__reformater_err_7 : 1;
        unsigned int stream_router__reformater_frame_dropped_0 : 1;
        unsigned int stream_router__reformater_frame_dropped_1 : 1;
        unsigned int stream_router__reformater_frame_dropped_2 : 1;
        unsigned int stream_router__reformater_frame_dropped_3 : 1;
        unsigned int stream_router__reformater_frame_dropped_4 : 1;
        unsigned int stream_router__reformater_frame_dropped_5 : 1;
        unsigned int stream_router__reformater_frame_dropped_6 : 1;
        unsigned int stream_router__reformater_frame_dropped_7 : 1;
        unsigned int frame_merger__end_of_frame_error : 1;
        unsigned int cvdr_rt__axi_wr_resp_err : 1;
        unsigned int cvdr_rt__axi_rd_resp_err : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_6_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_6_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_7_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_7_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_3_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_3_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_4_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_4_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_5_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_5_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_6_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_6_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_7_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_7_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_frame_merger__end_of_frame_error_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_frame_merger__end_of_frame_error_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_wr_resp_err_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_wr_resp_err_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_rd_resp_err_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_rd_resp_err_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_router__reformater_err_6 : 1;
        unsigned int stream_router__reformater_err_7 : 1;
        unsigned int stream_router__reformater_frame_dropped_0 : 1;
        unsigned int stream_router__reformater_frame_dropped_1 : 1;
        unsigned int stream_router__reformater_frame_dropped_2 : 1;
        unsigned int stream_router__reformater_frame_dropped_3 : 1;
        unsigned int stream_router__reformater_frame_dropped_4 : 1;
        unsigned int stream_router__reformater_frame_dropped_5 : 1;
        unsigned int stream_router__reformater_frame_dropped_6 : 1;
        unsigned int stream_router__reformater_frame_dropped_7 : 1;
        unsigned int frame_merger__end_of_frame_error : 1;
        unsigned int cvdr_rt__axi_wr_resp_err : 1;
        unsigned int cvdr_rt__axi_rd_resp_err : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_6_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_6_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_7_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_7_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_3_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_3_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_4_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_4_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_5_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_5_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_6_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_6_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_7_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_7_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_frame_merger__end_of_frame_error_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_frame_merger__end_of_frame_error_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_wr_resp_err_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_wr_resp_err_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_rd_resp_err_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_rd_resp_err_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_router__reformater_err_6 : 1;
        unsigned int stream_router__reformater_err_7 : 1;
        unsigned int stream_router__reformater_frame_dropped_0 : 1;
        unsigned int stream_router__reformater_frame_dropped_1 : 1;
        unsigned int stream_router__reformater_frame_dropped_2 : 1;
        unsigned int stream_router__reformater_frame_dropped_3 : 1;
        unsigned int stream_router__reformater_frame_dropped_4 : 1;
        unsigned int stream_router__reformater_frame_dropped_5 : 1;
        unsigned int stream_router__reformater_frame_dropped_6 : 1;
        unsigned int stream_router__reformater_frame_dropped_7 : 1;
        unsigned int frame_merger__end_of_frame_error : 1;
        unsigned int cvdr_rt__axi_wr_resp_err : 1;
        unsigned int cvdr_rt__axi_rd_resp_err : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_6_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_6_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_7_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_7_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_3_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_3_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_4_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_4_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_5_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_5_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_6_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_6_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_7_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_7_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_frame_merger__end_of_frame_error_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_frame_merger__end_of_frame_error_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_wr_resp_err_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_wr_resp_err_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_rd_resp_err_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_rd_resp_err_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stream_router__reformater_err_6 : 1;
        unsigned int stream_router__reformater_err_7 : 1;
        unsigned int stream_router__reformater_frame_dropped_0 : 1;
        unsigned int stream_router__reformater_frame_dropped_1 : 1;
        unsigned int stream_router__reformater_frame_dropped_2 : 1;
        unsigned int stream_router__reformater_frame_dropped_3 : 1;
        unsigned int stream_router__reformater_frame_dropped_4 : 1;
        unsigned int stream_router__reformater_frame_dropped_5 : 1;
        unsigned int stream_router__reformater_frame_dropped_6 : 1;
        unsigned int stream_router__reformater_frame_dropped_7 : 1;
        unsigned int frame_merger__end_of_frame_error : 1;
        unsigned int cvdr_rt__axi_wr_resp_err : 1;
        unsigned int cvdr_rt__axi_rd_resp_err : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_6_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_6_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_7_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_7_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_0_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_0_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_1_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_1_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_2_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_2_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_3_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_3_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_4_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_4_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_5_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_5_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_6_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_6_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_7_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_7_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_frame_merger__end_of_frame_error_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_frame_merger__end_of_frame_error_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_wr_resp_err_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_wr_resp_err_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_rd_resp_err_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_rd_resp_err_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__eof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__eof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__eof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__eof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__eof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__eof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__eof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__eof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__eof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__eof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__eof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__eof_vpwr_11 : 1;
        unsigned int otap_2_1__cvdr_rt__eof_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__eof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__eof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__eof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__eof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__eof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__eof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__eof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__eof_vpwr_25 : 1;
        unsigned int isp_fe_1__fcm__sw_wr_ack_0 : 1;
        unsigned int isp_fe_1__fcm__sw_rd_ack_0 : 1;
        unsigned int isp_fe_2__fcm__sw_wr_ack_1 : 1;
        unsigned int isp_fe_2__fcm__sw_rd_ack_1 : 1;
        unsigned int scaler_1_1_y__fcm__sw_wr_ack_2 : 1;
        unsigned int scaler_1_1_y__fcm__sw_rd_ack_2 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_wr_ack_3 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_rd_ack_3 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__eof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__eof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__eof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__eof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__eof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__eof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__eof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__eof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__eof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__eof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__eof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__eof_vpwr_11 : 1;
        unsigned int otap_2_1__cvdr_rt__eof_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__eof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__eof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__eof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__eof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__eof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__eof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__eof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__eof_vpwr_25 : 1;
        unsigned int isp_fe_1__fcm__sw_wr_ack_0 : 1;
        unsigned int isp_fe_1__fcm__sw_rd_ack_0 : 1;
        unsigned int isp_fe_2__fcm__sw_wr_ack_1 : 1;
        unsigned int isp_fe_2__fcm__sw_rd_ack_1 : 1;
        unsigned int scaler_1_1_y__fcm__sw_wr_ack_2 : 1;
        unsigned int scaler_1_1_y__fcm__sw_rd_ack_2 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_wr_ack_3 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_rd_ack_3 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__eof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__eof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__eof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__eof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__eof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__eof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__eof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__eof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__eof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__eof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__eof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__eof_vpwr_11 : 1;
        unsigned int otap_2_1__cvdr_rt__eof_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__eof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__eof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__eof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__eof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__eof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__eof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__eof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__eof_vpwr_25 : 1;
        unsigned int isp_fe_1__fcm__sw_wr_ack_0 : 1;
        unsigned int isp_fe_1__fcm__sw_rd_ack_0 : 1;
        unsigned int isp_fe_2__fcm__sw_wr_ack_1 : 1;
        unsigned int isp_fe_2__fcm__sw_rd_ack_1 : 1;
        unsigned int scaler_1_1_y__fcm__sw_wr_ack_2 : 1;
        unsigned int scaler_1_1_y__fcm__sw_rd_ack_2 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_wr_ack_3 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_rd_ack_3 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__eof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__eof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__eof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__eof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__eof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__eof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__eof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__eof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__eof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__eof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__eof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__eof_vpwr_11 : 1;
        unsigned int otap_2_1__cvdr_rt__eof_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__eof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__eof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__eof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__eof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__eof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__eof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__eof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__eof_vpwr_25 : 1;
        unsigned int isp_fe_1__fcm__sw_wr_ack_0 : 1;
        unsigned int isp_fe_1__fcm__sw_rd_ack_0 : 1;
        unsigned int isp_fe_2__fcm__sw_wr_ack_1 : 1;
        unsigned int isp_fe_2__fcm__sw_rd_ack_1 : 1;
        unsigned int scaler_1_1_y__fcm__sw_wr_ack_2 : 1;
        unsigned int scaler_1_1_y__fcm__sw_rd_ack_2 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_wr_ack_3 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_rd_ack_3 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int otap_1_1__cvdr_rt__eof_vpwr_0 : 1;
        unsigned int otap_1_2__cvdr_rt__eof_vpwr_1 : 1;
        unsigned int scaler_3_y__cvdr_rt__eof_vpwr_2 : 1;
        unsigned int scaler_3_uv__cvdr_rt__eof_vpwr_3 : 1;
        unsigned int scaler_2_1_y__cvdr_rt__eof_vpwr_4 : 1;
        unsigned int scaler_2_1_uv__cvdr_rt__eof_vpwr_5 : 1;
        unsigned int scaler_2_2_y__cvdr_rt__eof_vpwr_6 : 1;
        unsigned int scaler_2_2_uv__cvdr_rt__eof_vpwr_7 : 1;
        unsigned int scaler_1_1_y__cvdr_rt__eof_vpwr_8 : 1;
        unsigned int scaler_1_1_uv__cvdr_rt__eof_vpwr_9 : 1;
        unsigned int scaler_1_2_y__cvdr_rt__eof_vpwr_10 : 1;
        unsigned int scaler_1_2_uv__cvdr_rt__eof_vpwr_11 : 1;
        unsigned int otap_2_1__cvdr_rt__eof_vpwr_14 : 1;
        unsigned int otap_2_2__cvdr_rt__eof_vpwr_15 : 1;
        unsigned int isp_fe_1__cvdr_rt__eof_vpwr_16 : 1;
        unsigned int stream_router_1__cvdr_rt__eof_vpwr_18b : 1;
        unsigned int isp_fe_2__cvdr_rt__eof_vpwr_17 : 1;
        unsigned int stream_router_2__cvdr_rt__eof_vpwr_19b : 1;
        unsigned int stat3a_1__cvdr_rt__eof_vpwr_20 : 1;
        unsigned int stat3a_2__cvdr_rt__eof_vpwr_21 : 1;
        unsigned int stream_router_3__cvdr_rt__eof_vpwr_22 : 1;
        unsigned int stream_router_4__cvdr_rt__eof_vpwr_23 : 1;
        unsigned int stream_router_5__cvdr_rt__eof_vpwr_24 : 1;
        unsigned int jpgenc__cvdr_rt__eof_vpwr_25 : 1;
        unsigned int isp_fe_1__fcm__sw_wr_ack_0 : 1;
        unsigned int isp_fe_1__fcm__sw_rd_ack_0 : 1;
        unsigned int isp_fe_2__fcm__sw_wr_ack_1 : 1;
        unsigned int isp_fe_2__fcm__sw_rd_ack_1 : 1;
        unsigned int scaler_1_1_y__fcm__sw_wr_ack_2 : 1;
        unsigned int scaler_1_1_y__fcm__sw_rd_ack_2 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_wr_ack_3 : 1;
        unsigned int scaler_1_1_uv__fcm__sw_rd_ack_3 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scaler_1_2_y__fcm__sw_wr_ack_4 : 1;
        unsigned int scaler_1_2_y__fcm__sw_rd_ack_4 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_wr_ack_5 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_rd_ack_5 : 1;
        unsigned int scaler_3__end_of_rescale : 1;
        unsigned int stream_router__reformater_sof_0 : 1;
        unsigned int stream_router__reformater_sof_1 : 1;
        unsigned int stream_router__reformater_sof_2 : 1;
        unsigned int stream_router__reformater_sof_3 : 1;
        unsigned int stream_router__reformater_sof_4 : 1;
        unsigned int stream_router__reformater_sof_5 : 1;
        unsigned int stream_router__reformater_sof_6 : 1;
        unsigned int stream_router__reformater_sof_7 : 1;
        unsigned int fd__process_finish : 1;
        unsigned int stat3a_1__3astats_ready : 1;
        unsigned int stat3a_2__3astats_ready : 1;
        unsigned int bas_1__end_of_filtering : 1;
        unsigned int bas_2__end_of_filtering : 1;
        unsigned int statdis_1__dis_ready : 1;
        unsigned int statdis_2__dis_ready : 1;
        unsigned int flash__flash_on : 1;
        unsigned int flash__flash_off : 1;
        unsigned int stream_router_5__cvdr_rt__eol_vpwr_24 : 1;
        unsigned int ispss_ctrl__pwm_channel_0 : 1;
        unsigned int ispss_ctrl__pwm_channel_1 : 1;
        unsigned int cc_1__endofhist : 1;
        unsigned int cc_2__endofhist : 1;
        unsigned int ispss_ctrl__pwm_channel_2 : 1;
        unsigned int ispss_ctrl__pwm_channel_3 : 1;
        unsigned int ispss_ctrl__pwm_channel_4 : 1;
        unsigned int ispss_ctrl__pwm_channel_5 : 1;
        unsigned int ispss_ctrl__pwm_channel_6 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_3__end_of_rescale_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_3__end_of_rescale_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_0_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_0_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_1_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_1_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_6_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_6_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_7_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_7_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_fd__process_finish_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_fd__process_finish_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_1__3astats_ready_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_1__3astats_ready_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_2__3astats_ready_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_2__3astats_ready_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_1__end_of_filtering_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_1__end_of_filtering_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_2__end_of_filtering_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_2__end_of_filtering_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_1__dis_ready_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_1__dis_ready_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_2__dis_ready_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_2__dis_ready_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_on_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_on_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_off_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_off_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_1__endofhist_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_1__endofhist_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_2__endofhist_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_2__endofhist_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_4_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_4_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_5_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_5_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_6_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scaler_1_2_y__fcm__sw_wr_ack_4 : 1;
        unsigned int scaler_1_2_y__fcm__sw_rd_ack_4 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_wr_ack_5 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_rd_ack_5 : 1;
        unsigned int scaler_3__end_of_rescale : 1;
        unsigned int stream_router__reformater_sof_0 : 1;
        unsigned int stream_router__reformater_sof_1 : 1;
        unsigned int stream_router__reformater_sof_2 : 1;
        unsigned int stream_router__reformater_sof_3 : 1;
        unsigned int stream_router__reformater_sof_4 : 1;
        unsigned int stream_router__reformater_sof_5 : 1;
        unsigned int stream_router__reformater_sof_6 : 1;
        unsigned int stream_router__reformater_sof_7 : 1;
        unsigned int fd__process_finish : 1;
        unsigned int stat3a_1__3astats_ready : 1;
        unsigned int stat3a_2__3astats_ready : 1;
        unsigned int bas_1__end_of_filtering : 1;
        unsigned int bas_2__end_of_filtering : 1;
        unsigned int statdis_1__dis_ready : 1;
        unsigned int statdis_2__dis_ready : 1;
        unsigned int flash__flash_on : 1;
        unsigned int flash__flash_off : 1;
        unsigned int stream_router_5__cvdr_rt__eol_vpwr_24 : 1;
        unsigned int ispss_ctrl__pwm_channel_0 : 1;
        unsigned int ispss_ctrl__pwm_channel_1 : 1;
        unsigned int cc_1__endofhist : 1;
        unsigned int cc_2__endofhist : 1;
        unsigned int ispss_ctrl__pwm_channel_2 : 1;
        unsigned int ispss_ctrl__pwm_channel_3 : 1;
        unsigned int ispss_ctrl__pwm_channel_4 : 1;
        unsigned int ispss_ctrl__pwm_channel_5 : 1;
        unsigned int ispss_ctrl__pwm_channel_6 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_3__end_of_rescale_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_3__end_of_rescale_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_0_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_0_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_1_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_1_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_6_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_6_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_7_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_7_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_fd__process_finish_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_fd__process_finish_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_1__3astats_ready_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_1__3astats_ready_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_2__3astats_ready_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_2__3astats_ready_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_1__end_of_filtering_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_1__end_of_filtering_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_2__end_of_filtering_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_2__end_of_filtering_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_1__dis_ready_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_1__dis_ready_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_2__dis_ready_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_2__dis_ready_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_on_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_on_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_off_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_off_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_1__endofhist_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_1__endofhist_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_2__endofhist_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_2__endofhist_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_4_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_4_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_5_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_5_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_6_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scaler_1_2_y__fcm__sw_wr_ack_4 : 1;
        unsigned int scaler_1_2_y__fcm__sw_rd_ack_4 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_wr_ack_5 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_rd_ack_5 : 1;
        unsigned int scaler_3__end_of_rescale : 1;
        unsigned int stream_router__reformater_sof_0 : 1;
        unsigned int stream_router__reformater_sof_1 : 1;
        unsigned int stream_router__reformater_sof_2 : 1;
        unsigned int stream_router__reformater_sof_3 : 1;
        unsigned int stream_router__reformater_sof_4 : 1;
        unsigned int stream_router__reformater_sof_5 : 1;
        unsigned int stream_router__reformater_sof_6 : 1;
        unsigned int stream_router__reformater_sof_7 : 1;
        unsigned int fd__process_finish : 1;
        unsigned int stat3a_1__3astats_ready : 1;
        unsigned int stat3a_2__3astats_ready : 1;
        unsigned int bas_1__end_of_filtering : 1;
        unsigned int bas_2__end_of_filtering : 1;
        unsigned int statdis_1__dis_ready : 1;
        unsigned int statdis_2__dis_ready : 1;
        unsigned int flash__flash_on : 1;
        unsigned int flash__flash_off : 1;
        unsigned int stream_router_5__cvdr_rt__eol_vpwr_24 : 1;
        unsigned int ispss_ctrl__pwm_channel_0 : 1;
        unsigned int ispss_ctrl__pwm_channel_1 : 1;
        unsigned int cc_1__endofhist : 1;
        unsigned int cc_2__endofhist : 1;
        unsigned int ispss_ctrl__pwm_channel_2 : 1;
        unsigned int ispss_ctrl__pwm_channel_3 : 1;
        unsigned int ispss_ctrl__pwm_channel_4 : 1;
        unsigned int ispss_ctrl__pwm_channel_5 : 1;
        unsigned int ispss_ctrl__pwm_channel_6 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_3__end_of_rescale_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_3__end_of_rescale_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_0_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_0_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_1_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_1_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_6_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_6_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_7_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_7_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_fd__process_finish_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_fd__process_finish_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_1__3astats_ready_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_1__3astats_ready_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_2__3astats_ready_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_2__3astats_ready_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_1__end_of_filtering_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_1__end_of_filtering_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_2__end_of_filtering_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_2__end_of_filtering_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_1__dis_ready_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_1__dis_ready_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_2__dis_ready_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_2__dis_ready_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_on_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_on_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_off_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_off_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_1__endofhist_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_1__endofhist_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_2__endofhist_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_2__endofhist_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_4_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_4_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_5_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_5_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_6_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scaler_1_2_y__fcm__sw_wr_ack_4 : 1;
        unsigned int scaler_1_2_y__fcm__sw_rd_ack_4 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_wr_ack_5 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_rd_ack_5 : 1;
        unsigned int scaler_3__end_of_rescale : 1;
        unsigned int stream_router__reformater_sof_0 : 1;
        unsigned int stream_router__reformater_sof_1 : 1;
        unsigned int stream_router__reformater_sof_2 : 1;
        unsigned int stream_router__reformater_sof_3 : 1;
        unsigned int stream_router__reformater_sof_4 : 1;
        unsigned int stream_router__reformater_sof_5 : 1;
        unsigned int stream_router__reformater_sof_6 : 1;
        unsigned int stream_router__reformater_sof_7 : 1;
        unsigned int fd__process_finish : 1;
        unsigned int stat3a_1__3astats_ready : 1;
        unsigned int stat3a_2__3astats_ready : 1;
        unsigned int bas_1__end_of_filtering : 1;
        unsigned int bas_2__end_of_filtering : 1;
        unsigned int statdis_1__dis_ready : 1;
        unsigned int statdis_2__dis_ready : 1;
        unsigned int flash__flash_on : 1;
        unsigned int flash__flash_off : 1;
        unsigned int stream_router_5__cvdr_rt__eol_vpwr_24 : 1;
        unsigned int ispss_ctrl__pwm_channel_0 : 1;
        unsigned int ispss_ctrl__pwm_channel_1 : 1;
        unsigned int cc_1__endofhist : 1;
        unsigned int cc_2__endofhist : 1;
        unsigned int ispss_ctrl__pwm_channel_2 : 1;
        unsigned int ispss_ctrl__pwm_channel_3 : 1;
        unsigned int ispss_ctrl__pwm_channel_4 : 1;
        unsigned int ispss_ctrl__pwm_channel_5 : 1;
        unsigned int ispss_ctrl__pwm_channel_6 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_3__end_of_rescale_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_3__end_of_rescale_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_0_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_0_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_1_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_1_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_6_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_6_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_7_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_7_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_fd__process_finish_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_fd__process_finish_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_1__3astats_ready_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_1__3astats_ready_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_2__3astats_ready_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_2__3astats_ready_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_1__end_of_filtering_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_1__end_of_filtering_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_2__end_of_filtering_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_2__end_of_filtering_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_1__dis_ready_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_1__dis_ready_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_2__dis_ready_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_2__dis_ready_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_on_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_on_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_off_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_off_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_1__endofhist_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_1__endofhist_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_2__endofhist_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_2__endofhist_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_4_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_4_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_5_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_5_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_6_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scaler_1_2_y__fcm__sw_wr_ack_4 : 1;
        unsigned int scaler_1_2_y__fcm__sw_rd_ack_4 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_wr_ack_5 : 1;
        unsigned int scaler_1_2_uv__fcm__sw_rd_ack_5 : 1;
        unsigned int scaler_3__end_of_rescale : 1;
        unsigned int stream_router__reformater_sof_0 : 1;
        unsigned int stream_router__reformater_sof_1 : 1;
        unsigned int stream_router__reformater_sof_2 : 1;
        unsigned int stream_router__reformater_sof_3 : 1;
        unsigned int stream_router__reformater_sof_4 : 1;
        unsigned int stream_router__reformater_sof_5 : 1;
        unsigned int stream_router__reformater_sof_6 : 1;
        unsigned int stream_router__reformater_sof_7 : 1;
        unsigned int fd__process_finish : 1;
        unsigned int stat3a_1__3astats_ready : 1;
        unsigned int stat3a_2__3astats_ready : 1;
        unsigned int bas_1__end_of_filtering : 1;
        unsigned int bas_2__end_of_filtering : 1;
        unsigned int statdis_1__dis_ready : 1;
        unsigned int statdis_2__dis_ready : 1;
        unsigned int flash__flash_on : 1;
        unsigned int flash__flash_off : 1;
        unsigned int stream_router_5__cvdr_rt__eol_vpwr_24 : 1;
        unsigned int ispss_ctrl__pwm_channel_0 : 1;
        unsigned int ispss_ctrl__pwm_channel_1 : 1;
        unsigned int cc_1__endofhist : 1;
        unsigned int cc_2__endofhist : 1;
        unsigned int ispss_ctrl__pwm_channel_2 : 1;
        unsigned int ispss_ctrl__pwm_channel_3 : 1;
        unsigned int ispss_ctrl__pwm_channel_4 : 1;
        unsigned int ispss_ctrl__pwm_channel_5 : 1;
        unsigned int ispss_ctrl__pwm_channel_6 : 1;
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_3__end_of_rescale_START (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_3__end_of_rescale_END (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_0_START (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_0_END (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_1_START (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_1_END (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_2_START (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_2_END (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_3_START (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_3_END (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_4_START (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_4_END (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_5_START (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_5_END (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_6_START (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_6_END (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_7_START (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_7_END (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_fd__process_finish_START (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_fd__process_finish_END (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_1__3astats_ready_START (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_1__3astats_ready_END (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_2__3astats_ready_START (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_2__3astats_ready_END (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_1__end_of_filtering_START (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_1__end_of_filtering_END (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_2__end_of_filtering_START (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_2__end_of_filtering_END (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_1__dis_ready_START (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_1__dis_ready_END (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_2__dis_ready_START (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_2__dis_ready_END (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_on_START (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_on_END (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_off_START (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_off_END (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_0_START (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_0_END (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_1_START (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_1_END (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_1__endofhist_START (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_1__endofhist_END (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_2__endofhist_START (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_2__endofhist_END (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_2_START (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_2_END (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_3_START (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_3_END (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_4_START (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_4_END (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_5_START (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_5_END (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_6_START (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_6_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
