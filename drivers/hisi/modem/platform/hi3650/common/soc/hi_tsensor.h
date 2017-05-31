#ifndef __HI_TSENSOR_H__
#define __HI_TSENSOR_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI_TEMP_EN_OFFSET (0x0)
#define HI_TEMP_DIS_TIME_OFFSET (0x4)
#define HI_TRIM0_OFFSET (0x8)
#define HI_TRIM1_OFFSET (0xC)
#define HI_TEMP_TH_OFFSET (0x10)
#define HI_TEMP_B_TH_OFFSET (0x14)
#define HI_TEMP_CONFIG_OFFSET (0x18)
#define HI_TEMP_RAWINT_OFFSET (0x1C)
#define HI_TEMP_MSKINT_OFFSET (0x20)
#define HI_TEMP_STATINT_OFFSET (0x24)
#define HI_TEMP_OFFSET (0x28)
#define HI_TEMP_TRIM_MODE_OFFSET (0x2C)
typedef union
{
    struct
    {
        unsigned int temp_en : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_TEMP_EN_T;
typedef union
{
    struct
    {
        unsigned int temp_dis_time : 8;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_TEMP_DIS_TIME_T;
typedef union
{
    struct
    {
        unsigned int local_sensor_trim : 8;
        unsigned int remote_sensor1_trim : 8;
        unsigned int remote_sensor2_trim : 8;
        unsigned int remote_sensor3_trim : 8;
    } bits;
    unsigned int u32;
}HI_TRIM0_T;
typedef union
{
    struct
    {
        unsigned int remote_sensor4_trim : 8;
        unsigned int remote_sensor5_trim : 8;
        unsigned int remote_sensor6_trim : 8;
        unsigned int remote_sensor7_trim : 8;
    } bits;
    unsigned int u32;
}HI_TRIM1_T;
typedef union
{
    struct
    {
        unsigned int temp_0th : 8;
        unsigned int temp_1th : 8;
        unsigned int temp_2th : 8;
        unsigned int temp_3th : 8;
    } bits;
    unsigned int u32;
}HI_TEMP_TH_T;
typedef union
{
    struct
    {
        unsigned int temp_b_th : 5;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_TEMP_B_TH_T;
typedef union
{
    struct
    {
        unsigned int ct_sel : 2;
        unsigned int test : 3;
        unsigned int sample_mode : 2;
        unsigned int sample_num : 3;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_TEMP_CONFIG_T;
typedef union
{
    struct
    {
        unsigned int temp_rawint : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_TEMP_RAWINT_T;
typedef union
{
    struct
    {
        unsigned int temp_maskint : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_TEMP_MSKINT_T;
typedef union
{
    struct
    {
        unsigned int temp_statint : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_TEMP_STATINT_T;
typedef union
{
    struct
    {
        unsigned int temp : 8;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_TEMP_T;
typedef union
{
    struct
    {
        unsigned int temp_trim_mode : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_TEMP_TRIM_MODE_T;
HI_SET_GET(hi_temp_en_temp_en,temp_en,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_en_reserved,reserved,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_dis_time_temp_dis_time,temp_dis_time,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_temp_dis_time_reserved,reserved,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_trim0_local_sensor_trim,local_sensor_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor1_trim,remote_sensor1_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor2_trim,remote_sensor2_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor3_trim,remote_sensor3_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor4_trim,remote_sensor4_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor5_trim,remote_sensor5_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor6_trim,remote_sensor6_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor7_trim,remote_sensor7_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_temp_th_temp_0th,temp_0th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_1th,temp_1th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_2th,temp_2th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_3th,temp_3th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_temp_b_th,temp_b_th,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_reserved,reserved,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_config_ct_sel,ct_sel,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_test,test,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_mode,sample_mode,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_num,sample_num,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_reserved,reserved,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_rawint_temp_rawint,temp_rawint,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_rawint_reserved,reserved,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_mskint_temp_maskint,temp_maskint,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_mskint_reserved,reserved,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_statint_temp_statint,temp_statint,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_statint_reserved,reserved,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_temp,temp,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_reserved,reserved,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_trim_mode_temp_trim_mode,temp_trim_mode,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)
HI_SET_GET(hi_temp_trim_mode_reserved,reserved,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)
#endif
