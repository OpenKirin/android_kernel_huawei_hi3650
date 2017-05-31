#ifndef __SOC_TSENSOR_INTERFACE_H__
#define __SOC_TSENSOR_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_Tsensor_CALIBRATION11_ADDR(base) ((base) + (0x000))
#define SOC_Tsensor_CALIBRATION21_ADDR(base) ((base) + (0x004))
#define SOC_Tsensor_TEMP_CONFIG1_ADDR(base) ((base) + (0x008))
#define SOC_Tsensor_TEMP_DET_EN1_ADDR(base) ((base) + (0x00C))
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_ADDR(base) ((base) + (0x010))
#define SOC_Tsensor_TEMP_WAIT_TIME1_ADDR(base) ((base) + (0x014))
#define SOC_Tsensor_TEMP_FSMSTAT1_ADDR(base) ((base) + (0x018))
#define SOC_Tsensor_TEMP1_ADDR(base) ((base) + (0x01C))
#define SOC_Tsensor_TEMP_TH1_ADDR(base) ((base) + (0x020))
#define SOC_Tsensor_TEMP_RST_TH1_ADDR(base) ((base) + (0x024))
#define SOC_Tsensor_TEMP_LAG1_ADDR(base) ((base) + (0x028))
#define SOC_Tsensor_TEMP_INT_MSK1_ADDR(base) ((base) + (0x02C))
#define SOC_Tsensor_TEMP_INT_CLR1_ADDR(base) ((base) + (0x030))
#define SOC_Tsensor_TEMP_RST_MSK1_ADDR(base) ((base) + (0x034))
#define SOC_Tsensor_TEMP_RAWINT1_ADDR(base) ((base) + (0x038))
#define SOC_Tsensor_TEMP_MSKINT1_ADDR(base) ((base) + (0x03C))
#define SOC_Tsensor_CALIBRATION12_ADDR(base) ((base) + (0x040))
#define SOC_Tsensor_CALIBRATION22_ADDR(base) ((base) + (0x044))
#define SOC_Tsensor_TEMP_CONFIG2_ADDR(base) ((base) + (0x048))
#define SOC_Tsensor_TEMP_DET_EN2_ADDR(base) ((base) + (0x04C))
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_ADDR(base) ((base) + (0x050))
#define SOC_Tsensor_TEMP_WAIT_TIME2_ADDR(base) ((base) + (0x054))
#define SOC_Tsensor_TEMP_FSMSTAT2_ADDR(base) ((base) + (0x058))
#define SOC_Tsensor_TEMP2_ADDR(base) ((base) + (0x05C))
#define SOC_Tsensor_TEMP_TH2_ADDR(base) ((base) + (0x060))
#define SOC_Tsensor_TEMP_RST_TH2_ADDR(base) ((base) + (0x064))
#define SOC_Tsensor_TEMP_LAG2_ADDR(base) ((base) + (0x068))
#define SOC_Tsensor_TEMP_INT_MSK2_ADDR(base) ((base) + (0x06C))
#define SOC_Tsensor_TEMP_INT_CLR2_ADDR(base) ((base) + (0x070))
#define SOC_Tsensor_TEMP_RST_MSK2_ADDR(base) ((base) + (0x074))
#define SOC_Tsensor_TEMP_RAWINT2_ADDR(base) ((base) + (0x078))
#define SOC_Tsensor_TEMP_MSKINT2_ADDR(base) ((base) + (0x07C))
#define SOC_Tsensor_CALIBRATION13_ADDR(base) ((base) + (0x080))
#define SOC_Tsensor_CALIBRATION23_ADDR(base) ((base) + (0x084))
#define SOC_Tsensor_TEMP_CONFIG3_ADDR(base) ((base) + (0x088))
#define SOC_Tsensor_TEMP_DET_EN3_ADDR(base) ((base) + (0x08C))
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_ADDR(base) ((base) + (0x090))
#define SOC_Tsensor_TEMP_WAIT_TIME3_ADDR(base) ((base) + (0x094))
#define SOC_Tsensor_TEMP_FSMSTAT3_ADDR(base) ((base) + (0x098))
#define SOC_Tsensor_TEMP3_ADDR(base) ((base) + (0x09C))
#define SOC_Tsensor_TEMP_TH3_ADDR(base) ((base) + (0x0A0))
#define SOC_Tsensor_TEMP_RST_TH3_ADDR(base) ((base) + (0x0A4))
#define SOC_Tsensor_TEMP_LAG3_ADDR(base) ((base) + (0x0A8))
#define SOC_Tsensor_TEMP_INT_MSK3_ADDR(base) ((base) + (0x0AC))
#define SOC_Tsensor_TEMP_INT_CLR3_ADDR(base) ((base) + (0x0B0))
#define SOC_Tsensor_TEMP_RST_MSK3_ADDR(base) ((base) + (0x0B4))
#define SOC_Tsensor_TEMP_RAWINT3_ADDR(base) ((base) + (0x0B8))
#define SOC_Tsensor_TEMP_MSKINT3_ADDR(base) ((base) + (0x0BC))
#define SOC_Tsensor_CALIBRATION14_ADDR(base) ((base) + (0x0C0))
#define SOC_Tsensor_CALIBRATION24_ADDR(base) ((base) + (0x0C4))
#define SOC_Tsensor_TEMP_CONFIG4_ADDR(base) ((base) + (0x0C8))
#define SOC_Tsensor_TEMP_DET_EN4_ADDR(base) ((base) + (0x0CC))
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_ADDR(base) ((base) + (0x0D0))
#define SOC_Tsensor_TEMP_WAIT_TIME4_ADDR(base) ((base) + (0x0D4))
#define SOC_Tsensor_TEMP_FSMSTAT4_ADDR(base) ((base) + (0x0D8))
#define SOC_Tsensor_TEMP4_ADDR(base) ((base) + (0x0DC))
#define SOC_Tsensor_TEMP_TH4_ADDR(base) ((base) + (0x0E0))
#define SOC_Tsensor_TEMP_RST_TH4_ADDR(base) ((base) + (0x0E4))
#define SOC_Tsensor_TEMP_LAG4_ADDR(base) ((base) + (0x0E8))
#define SOC_Tsensor_TEMP_INT_MSK4_ADDR(base) ((base) + (0x0EC))
#define SOC_Tsensor_TEMP_INT_CLR4_ADDR(base) ((base) + (0x0F0))
#define SOC_Tsensor_TEMP_RST_MSK4_ADDR(base) ((base) + (0x0F4))
#define SOC_Tsensor_TEMP_RAWINT4_ADDR(base) ((base) + (0x0F8))
#define SOC_Tsensor_TEMP_MSKINT4_ADDR(base) ((base) + (0x0FC))
#define SOC_Tsensor_TEMP_SOFTCTRL1_ADDR(base) ((base) + (0x100))
#define SOC_Tsensor_TEMP1_SOFT_ADDR(base) ((base) + (0x104))
#define SOC_Tsensor_TEMP_SOFTCTRL2_ADDR(base) ((base) + (0x108))
#define SOC_Tsensor_TEMP2_SOFT_ADDR(base) ((base) + (0x10C))
#define SOC_Tsensor_TEMP_SOFTCTRL3_ADDR(base) ((base) + (0x110))
#define SOC_Tsensor_TEMP3_SOFT_ADDR(base) ((base) + (0x114))
#define SOC_Tsensor_TEMP_SOFTCTRL4_ADDR(base) ((base) + (0x118))
#define SOC_Tsensor_TEMP4_SOFT_ADDR(base) ((base) + (0x11C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int local_sensorerror : 10;
        unsigned int remote_sensor1error : 6;
        unsigned int remote_sensor2error : 8;
        unsigned int remote_sensor3error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION11_UNION;
#endif
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_START (0)
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_END (9)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_START (10)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_END (15)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_START (16)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_END (23)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_START (24)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int remote_sensor4error : 10;
        unsigned int remote_sensor5error : 6;
        unsigned int remote_sensor6error : 8;
        unsigned int remote_sensor7error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION21_UNION;
#endif
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_START (0)
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_END (9)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_START (10)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_END (15)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_START (16)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_END (23)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_START (24)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int channel_num1 : 3;
        unsigned int channel_sel1 : 4;
        unsigned int temp_mode1 : 2;
        unsigned int sample_num1 : 8;
        unsigned int ct_sel_apb1 : 2;
        unsigned int reserved : 13;
    } reg;
} SOC_Tsensor_TEMP_CONFIG1_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_START (0)
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_END (2)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_START (3)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_END (6)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_START (7)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_END (8)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_START (9)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_END (16)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_START (17)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_det_en1 : 1;
        unsigned int calib1 : 1;
        unsigned int calib1_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_Tsensor_TEMP_DET_EN1_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_START (0)
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_END (0)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_START (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_END (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_START (2)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_bypass1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_START (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_time1 : 32;
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_START (0)
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m_fsm_stat : 4;
        unsigned int s_fsm_stat : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT1_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_START (0)
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_END (3)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_START (4)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP1_UNION;
#endif
#define SOC_Tsensor_TEMP1_temp1_START (0)
#define SOC_Tsensor_TEMP1_temp1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_0th1 : 10;
        unsigned int temp_1th1 : 10;
        unsigned int temp_2th1 : 10;
        unsigned int reserved : 2;
    } reg;
} SOC_Tsensor_TEMP_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_TH1_temp_0th1_START (0)
#define SOC_Tsensor_TEMP_TH1_temp_0th1_END (9)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_START (10)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_END (19)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_START (20)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_th1 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP_RST_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_START (0)
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_lag1 : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_Tsensor_TEMP_LAG1_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_START (0)
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_msk1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_START (0)
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_clr1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_CLR1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_START (0)
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_msk1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RST_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_START (0)
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rawint1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RAWINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_START (0)
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_mskint1 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_MSKINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_START (0)
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int local_sensorerror : 10;
        unsigned int remote_sensor1error : 6;
        unsigned int remote_sensor2error : 8;
        unsigned int remote_sensor3error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION12_UNION;
#endif
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_START (0)
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_END (9)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_START (10)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_END (15)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_START (16)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_END (23)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_START (24)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int remote_sensor4error : 10;
        unsigned int remote_sensor5error : 6;
        unsigned int remote_sensor6error : 8;
        unsigned int remote_sensor7error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION22_UNION;
#endif
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_START (0)
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_END (9)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_START (10)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_END (15)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_START (16)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_END (23)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_START (24)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int channel_num2 : 3;
        unsigned int channel_sel2 : 4;
        unsigned int temp_mode2 : 2;
        unsigned int sample_num2 : 8;
        unsigned int ct_sel_apb2 : 2;
        unsigned int reserved : 13;
    } reg;
} SOC_Tsensor_TEMP_CONFIG2_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_START (0)
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_END (2)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_START (3)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_END (6)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_START (7)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_END (8)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_START (9)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_END (16)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_START (17)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_det_en2 : 1;
        unsigned int calib2 : 1;
        unsigned int calib2_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_Tsensor_TEMP_DET_EN2_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_START (0)
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_END (0)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_START (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_END (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_START (2)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_bypass2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_START (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_time2 : 32;
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_START (0)
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m_fsm_stat : 4;
        unsigned int s_fsm_stat : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT2_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_START (0)
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_END (3)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_START (4)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp2 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP2_UNION;
#endif
#define SOC_Tsensor_TEMP2_temp2_START (0)
#define SOC_Tsensor_TEMP2_temp2_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_0th2 : 10;
        unsigned int temp_1th2 : 10;
        unsigned int temp_2th2 : 10;
        unsigned int temp_3th2 : 2;
    } reg;
} SOC_Tsensor_TEMP_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_TH2_temp_0th2_START (0)
#define SOC_Tsensor_TEMP_TH2_temp_0th2_END (9)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_START (10)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_END (19)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_START (20)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_END (29)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_START (30)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_th2 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP_RST_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_START (0)
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_lag2 : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_Tsensor_TEMP_LAG2_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_START (0)
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_msk2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_START (0)
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_clr2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_CLR2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_START (0)
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_msk2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RST_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_START (0)
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rawint2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RAWINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_START (0)
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_mskint2 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_MSKINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_START (0)
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int local_sensorerror : 10;
        unsigned int remote_sensor1error : 6;
        unsigned int remote_sensor2error : 8;
        unsigned int remote_sensor3error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION13_UNION;
#endif
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_START (0)
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_END (9)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_START (10)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_END (15)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_START (16)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_END (23)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_START (24)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int remote_sensor4error : 10;
        unsigned int remote_sensor5error : 6;
        unsigned int remote_sensor6error : 8;
        unsigned int remote_sensor7error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION23_UNION;
#endif
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_START (0)
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_END (9)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_START (10)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_END (15)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_START (16)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_END (23)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_START (24)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int channel_num3 : 3;
        unsigned int channel_sel3 : 4;
        unsigned int temp_mode3 : 2;
        unsigned int sample_num3 : 8;
        unsigned int ct_sel_apb3 : 2;
        unsigned int reserved : 13;
    } reg;
} SOC_Tsensor_TEMP_CONFIG3_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_START (0)
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_END (2)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_START (3)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_END (6)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_START (7)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_END (8)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_START (9)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_END (16)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_START (17)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_det_en3 : 1;
        unsigned int calib3 : 1;
        unsigned int calib3_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_Tsensor_TEMP_DET_EN3_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_START (0)
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_END (0)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_START (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_END (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_START (2)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_bypass3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_START (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_time3 : 32;
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_START (0)
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m_fsm_stat : 4;
        unsigned int s_fsm_stat : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT3_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_START (0)
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_END (3)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_START (4)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp3 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP3_UNION;
#endif
#define SOC_Tsensor_TEMP3_temp3_START (0)
#define SOC_Tsensor_TEMP3_temp3_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_0th3 : 10;
        unsigned int temp_1th3 : 10;
        unsigned int temp_2th3 : 10;
        unsigned int temp_3th3 : 2;
    } reg;
} SOC_Tsensor_TEMP_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_TH3_temp_0th3_START (0)
#define SOC_Tsensor_TEMP_TH3_temp_0th3_END (9)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_START (10)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_END (19)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_START (20)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_END (29)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_START (30)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_th3 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP_RST_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_START (0)
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_lag3 : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_Tsensor_TEMP_LAG3_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_START (0)
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_msk3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_START (0)
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_clr3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_CLR3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_START (0)
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_msk3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RST_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_START (0)
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rawint3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RAWINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_START (0)
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_mskint3 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_MSKINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_START (0)
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int local_sensorerror : 10;
        unsigned int remote_sensor1error : 6;
        unsigned int remote_sensor2error : 8;
        unsigned int remote_sensor3error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION14_UNION;
#endif
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_START (0)
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_END (9)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_START (10)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_END (15)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_START (16)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_END (23)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_START (24)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int remote_sensor4error : 10;
        unsigned int remote_sensor5error : 6;
        unsigned int remote_sensor6error : 8;
        unsigned int remote_sensor7error : 8;
    } reg;
} SOC_Tsensor_CALIBRATION24_UNION;
#endif
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_START (0)
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_END (9)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_START (10)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_END (15)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_START (16)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_END (23)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_START (24)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int channel_num4 : 3;
        unsigned int channel_sel4 : 4;
        unsigned int temp_mode4 : 2;
        unsigned int sample_num4 : 8;
        unsigned int ct_sel_apb4 : 2;
        unsigned int reserved : 13;
    } reg;
} SOC_Tsensor_TEMP_CONFIG4_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_START (0)
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_END (2)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_START (3)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_END (6)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_START (7)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_END (8)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_START (9)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_END (16)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_START (17)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_det_en4 : 1;
        unsigned int calib4 : 1;
        unsigned int calib4_en : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_Tsensor_TEMP_DET_EN4_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_START (0)
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_END (0)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_START (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_END (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_START (2)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_bypass4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_START (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_wait_time4 : 32;
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_START (0)
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m_fsm_stat : 4;
        unsigned int s_fsm_stat : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT4_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_START (0)
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_END (3)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_START (4)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp4 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP4_UNION;
#endif
#define SOC_Tsensor_TEMP4_temp4_START (0)
#define SOC_Tsensor_TEMP4_temp4_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_0th4 : 10;
        unsigned int temp_1th4 : 10;
        unsigned int temp_2th4 : 10;
        unsigned int temp_3th4 : 2;
    } reg;
} SOC_Tsensor_TEMP_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_TH4_temp_0th4_START (0)
#define SOC_Tsensor_TEMP_TH4_temp_0th4_END (9)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_START (10)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_END (19)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_START (20)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_END (29)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_START (30)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_th4 : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP_RST_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_START (0)
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_lag4 : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_Tsensor_TEMP_LAG4_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_START (0)
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_msk4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_START (0)
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_int_clr4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_INT_CLR4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_START (0)
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rst_msk4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RST_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_START (0)
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_rawint4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_RAWINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_START (0)
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp_mskint4 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_Tsensor_TEMP_MSKINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_START (0)
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_soft1 : 1;
        unsigned int temp_en1_soft : 1;
        unsigned int ct_sel1_soft : 2;
        unsigned int test1_soft : 8;
        unsigned int calib1_soft : 1;
        unsigned int calib1_en_soft : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL1_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_START (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_END (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_START (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_END (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_START (2)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_END (3)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_START (4)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_END (11)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_START (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_END (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_START (13)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_soft : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP1_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_START (0)
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_soft2 : 1;
        unsigned int temp_en2_soft : 1;
        unsigned int ct_sel2_soft : 2;
        unsigned int test2_soft : 8;
        unsigned int calib2_soft : 1;
        unsigned int calib2_en_soft : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL2_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_START (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_END (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_START (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_END (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_START (2)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_END (3)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_START (4)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_END (11)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_START (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_END (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_START (13)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp2_soft : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP2_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_START (0)
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_soft3 : 1;
        unsigned int temp_en3_soft : 1;
        unsigned int ct_sel3_soft : 2;
        unsigned int test3_soft : 8;
        unsigned int calib3_soft : 1;
        unsigned int calib3_en_soft : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL3_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_START (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_END (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_START (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_END (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_START (2)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_END (3)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_START (4)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_END (11)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_START (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_END (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_START (13)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp3_soft : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP3_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_START (0)
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_soft4 : 1;
        unsigned int temp_en4_soft : 1;
        unsigned int ct_sel4_soft : 2;
        unsigned int test4_soft : 8;
        unsigned int calib4_soft : 1;
        unsigned int calib4_en_soft : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL4_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_START (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_END (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_START (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_END (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_START (2)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_END (3)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_START (4)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_END (11)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_START (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_END (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_START (13)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp4_soft : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_Tsensor_TEMP4_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_START (0)
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_END (9)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
