

#ifndef __HISI_CUSTOMIZE_WIFI_H__
#define __HISI_CUSTOMIZE_WIFI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NVRAM_PARAMS_ARRAY      "nvram_params"

#define MAC_LEN                 6
#define NV_WLAN_NUM             193
#define NV_WLAN_VALID_SIZE      12
#define MAC2STR(a)              (a)[0], "**", "**", "**", (a)[4], (a)[5]
#define MACFMT                  "%02x:%s:%s:%s:%02x:%02x"
#define MAC2STR_ALL(a)          (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACFMT_ALL              "%02x:%02x:%02x:%02x:%02x:%02x"
#define CUS_TAG_INI                     0x11
#define CUS_TAG_DTS                     0x12
#define CUS_TAG_NV                      0x13
#define CALI_TXPWR_PA_DC_REF_MIN        (1000)
#define CALI_TXPWR_PA_DC_REF_MAX        (10000)
#define CALI_TXPWR_PA_DC_FRE_MIN        (0)
#define CALI_TXPWR_PA_DC_FRE_MAX        (78)
#define CALI_BT_TXPWR_PA_DC_REF_MAX     (15000)
#define CHN_EST_CTRL_EVB                (0x3C192240)
#define CHN_EST_CTRL_MATE7              (0x3C193240)
#define CHN_EST_CTRL_FPGA               (0x3C19A243)
#define PHY_POWER_REF_5G_EVB            (0x04D8EC)
#define PHY_POWER_REF_5G_MT7            (0xF6CADE)
#define RTC_CLK_FREQ_MIN                (32000)
#define RTC_CLK_FREQ_MAX                (33000)
#define RF_LINE_TXRX_GAIN_DB_2G_MIN     (-32)
#define RF_LINE_TXRX_GAIN_DB_5G_MIN     (-12)
#define PSD_THRESHOLD_MIN               (-15)
#define PSD_THRESHOLD_MAX               (-10)
#define LNA_GAIN_DB_MIN                 (-10)
#define LNA_GAIN_DB_MAX                 (20)
#define NUM_OF_NV_MAX_TXPOWER           (45)                                /* NVRAM�д洢�ĸ�Э����������书�ʲ����ĸ��� From:24G_11b_1M To:5G_VHT80_MCS7 */
#define NUM_OF_NV_PARAMS                (2 * NUM_OF_NV_MAX_TXPOWER + 1)     /* NVRAM�д洢�Ĳ���ֵ���ܸ���:ÿ��powerֵ��Ӧһ��scale������dpd���� */
#define MAX_TXPOWER_MIN                 (130)                               /* ����͹��ʵ���С��Чֵ:130 13.0dbm */
#define MAX_TXPOWER_MAX                 (238)                               /* ����͹��ʵ������Чֵ:238 23.8dbm */
#define NUM_OF_BAND_EDGE_LIMIT          (6)                                 /* FCC�ߴ���֤�������� */
#define MAX_DBB_SCALE                   (0xEE)                              /* DBB SCALE�����Чֵ */
#define TX_RATIO_MAX                    (2000)                              /* txռ�ձȵ������Чֵ */
#define TX_PWR_COMP_VAL_MAX             (50)                                /* ���书�ʲ���ֵ�������Чֵ */
#define MORE_PWR_MAX                    (50)                                /* �����¶ȶ��ⲹ���ķ��书�ʵ������Чֵ */
#define COUNTRY_CODE_LEN                (3)                                 /* ������λ�� */
#define MAX_COUNTRY_COUNT               (300)                               /* ֧�ֶ��ƵĹ��ҵ������� */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
   REGDOMAIN_FCC        = 0,
   REGDOMAIN_ETSI       = 1,
   REGDOMAIN_JAPAN      = 2,
   REGDOMAIN_COMMON     = 3,

   REGDOMAIN_COUNT
} regdomain_enum;

/* ���ƻ� DTS CONFIG ID */
typedef enum
{
    /* 5g���� */
    WLAN_CFG_DTS_BAND_5G_ENABLE = 0,
    /* У׼ */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_START = WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1,     /* У׼ 2g TXPWR_REF��ʼ����ID */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN2,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN3,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN4,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN5,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN6,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN7,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN8,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN9,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN10,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN11,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN12,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN13,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_START = WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1,    /* У׼ 5g TXPWR_REF��ʼ����ID */
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND2,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND3,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND4,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND5,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND6,
    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND7,
    WLAN_CFG_DTS_CALI_TONE_AMP_GRADE,
    /* FCC��֤ */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR,                                                      /* FCC CH1,CH11 band edge limit */      //21
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_TXPWR_START = WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR,           /* FCC��֤:TXPWR ��ʼ����ID */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_TXPWR,                                                 /* FCC CH1,CH11 band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_TXPWR,                                                 /* FCC CH3,CH9 band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_TXPWR,                                           /* FCC CH36��64��100��149��165, band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_TXPWR,                                               /* FCC CH38,CH62 ��102��151��band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_TXPWR,                                                    /* FCC CH42��58��106��155��band edge limit */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING,                                                /* FCC CH1,CH11 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_SCALE_START = WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING,     /* FCC��֤:SCALE ��ʼ����ID */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_DBB_SCALING,                                           /* FCC CH1,CH11 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_DBB_SCALING,                                           /* FCC CH3,CH9 dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_DBB_SCALING,                                     /* FCC CH36��64��100��149��165, dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_DBB_SCALING,                                         /* FCC CH38,CH62 ��102��151��dbb scaling */
    WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_DBB_SCALING,                                              /* FCC CH42��58��106��155��dbb scaling */
    /* rf register */
    WLAN_CFG_DTS_RF_REG117,                     //33
    WLAN_CFG_DTS_RF_FIRST = WLAN_CFG_DTS_RF_REG117,
    WLAN_CFG_DTS_RF_REG123,
    WLAN_CFG_DTS_RF_REG124,
    WLAN_CFG_DTS_RF_REG125,
    WLAN_CFG_DTS_RF_REG126,
    WLAN_CFG_DTS_RF_LAST = WLAN_CFG_DTS_RF_REG126,
    /* bt tmp */
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND1,    //37
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND2,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND3,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND4,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND5,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND6,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND7,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND8,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_NUM,          //45
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE1,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE2,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE3,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE4,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE5,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE6,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE7,
    WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE8,         //53
    WLAN_CFG_DTS_BT_CALI_TONE_AMP_GRADE,

    WLAN_CFG_DTS_BUTT,
}WLAN_CFG_DTS;

/* ���ƻ� INI CONFIG ID */
typedef enum
{
    /* ROAM */
    WLAN_CFG_INIT_ROAM_SWITCH = 0,
    WLAN_CFG_INIT_SCAN_ORTHOGONAL,
    WLAN_CFG_INIT_TRIGGER_B,
    WLAN_CFG_INIT_TRIGGER_A,
    WLAN_CFG_INIT_DELTA_B,
    WLAN_CFG_INIT_DELTA_A,

    /* ���� */
    WLAN_CFG_INIT_AMPDU_TX_MAX_NUM,
    WLAN_CFG_INIT_USED_MEM_FOR_START,
    WLAN_CFG_INIT_USED_MEM_FOR_STOP,
    WLAN_CFG_INIT_RX_ACK_LIMIT,
    WLAN_CFG_INIT_SDIO_D2H_ASSEMBLE_COUNT,
    WLAN_CFG_INIT_SDIO_H2D_ASSEMBLE_COUNT,
    /* LINKLOSS */
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_NEAR,    //9,���ﲻ��ֱ�Ӹ�ֵ
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_FAR,
    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_P2P,
    /* �Զ���Ƶ */
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_0,            //12
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_0,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_0,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_1,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_1,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_1,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_2,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_2,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_2,
    WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_3,
    WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_3,
    WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_3,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_0,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_1,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_2,
    WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_3,
    /* �͹��� */
    WLAN_CFG_INIT_POWERMGMT_SWITCH,                 //28
    /* ��ά�ɲ� */
    WLAN_CFG_INIT_LOGLEVEL,
    /* PHY�㷨 */
    WLAN_CFG_INIT_CHN_EST_CTRL,
    WLAN_CFG_INIT_POWER_REF_5G,
    /* ʱ����Ϣ */
    WLAN_CFG_INIT_RTS_CLK_FREQ,
    WLAN_CFG_INIT_CLK_TYPE,
    /* 2G RFǰ�� */
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4,    //34
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND_START = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND_END = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10,
    /* 5G RFǰ�� */
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT4,  //44
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND_START = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT4,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT10,
    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND_END = WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT10,
    WLAN_CFG_INIT_RF_LINE_RX_GAIN_DB_5G,
    WLAN_CFG_INIT_LNA_GAIN_DB_5G,
    WLAN_CFG_INIT_RF_LINE_TX_GAIN_DB_5G,
    WLAN_CFG_INIT_EXT_SWITCH_ISEXIST_5G,
    WLAN_CFG_INIT_EXT_PA_ISEXIST_5G,
    WLAN_CFG_INIT_EXT_LNA_ISEXIST_5G,
    WLAN_CFG_INIT_LNA_ON2OFF_TIME_NS_5G,
    WLAN_CFG_INIT_LNA_OFF2ON_TIME_NS_5G,
    /* �¶��������·��书���½�����Ĺ��ʲ��� */
    WLAN_CFG_INIT_TX_RATIO_LEVEL_0,                 /* txռ�ձ� */                      //48
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_0,          /* ���书�ʲ���ֵ */
    WLAN_CFG_INIT_TX_RATIO_LEVEL_1,
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_1,
    WLAN_CFG_INIT_TX_RATIO_LEVEL_2,
    WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_2,
    WLAN_CFG_INIT_MORE_PWR,                         /* �����¶ȶ��ⲹ���ķ��书�� */
    /* SCAN */
    WLAN_CFG_INIT_RANDOM_MAC_ADDR_SCAN,
    /* 11AC2G */
    WLAN_CFG_INIT_11AC2G_ENABLE,                    /* 11ac2g���� */                    //56
    WLAN_CFG_INIT_DISABLE_CAPAB_2GHT40,             /* 2ght40��ֹ���� */
    WLAN_CFG_INIT_DUAL_ANTENNA_ENABLE,              /* ˫���߿��� */
    WLAN_CFG_INIT_FAR_DIST_POW_GAIN_SWITCH,         /* Զ���빦�����濪�� */
    WLAN_CFG_LTE_GPIO_CHECK_SWITCH,                 /* lte�ܽż�⿪�� */
    WLAN_ATCMDSRV_LTE_ISM_PRIORITY,
    WLAN_ATCMDSRV_LTE_RX_ACT,
    WLAN_ATCMDSRV_LTE_TX_ACT,
    WLAN_CFG_INIT_FAR_DIST_DSSS_SCALE_PROMOTE_SWITCH,    /* ��Զ��11b 1m 2m dbb scale����ʹ�ܿ��� */
    WLAN_CFG_INIT_BUTT,
}WLAN_CFG_INIT;

/* ���ƻ� NVRAM PARAMS INDEX */
typedef enum
{
    NVRAM_PARAMS_INDEX_0   = 0,
    NVRAM_PARAMS_INDEX_1   = 1,
    NVRAM_PARAMS_INDEX_2   = 2,
    NVRAM_PARAMS_INDEX_3   = 3,
    NVRAM_PARAMS_INDEX_4   = 4,
    NVRAM_PARAMS_INDEX_5   = 5,
    NVRAM_PARAMS_INDEX_6   = 6,
    NVRAM_PARAMS_INDEX_7   = 7,
    NVRAM_PARAMS_INDEX_8   = 8,
    NVRAM_PARAMS_INDEX_9   = 9,
    NVRAM_PARAMS_INDEX_10  = 10,
    NVRAM_PARAMS_INDEX_11  = 11,
    NVRAM_PARAMS_INDEX_12  = 12,
    NVRAM_PARAMS_INDEX_13  = 13,
    NVRAM_PARAMS_INDEX_14  = 14,
    NVRAM_PARAMS_INDEX_15  = 15,
    NVRAM_PARAMS_INDEX_16  = 16,
    NVRAM_PARAMS_INDEX_17  = 17,
    NVRAM_PARAMS_INDEX_18  = 18,
    NVRAM_PARAMS_INDEX_19  = 19,
    NVRAM_PARAMS_INDEX_20  = 20,
    NVRAM_PARAMS_INDEX_21  = 21,
    NVRAM_PARAMS_INDEX_22  = 22,
    NVRAM_PARAMS_INDEX_23  = 23,
    NVRAM_PARAMS_INDEX_24  = 24,
    NVRAM_PARAMS_INDEX_25  = 25,

    NVRAM_PARAMS_INDEX_BUTT,
}NVRAM_PARAMS_INDEX;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef unsigned char countrycode_t[COUNTRY_CODE_LEN];
typedef struct
{
   regdomain_enum       en_regdomain;
   countrycode_t        auc_country_code;
} countryinfo_stru;

/**
 *  regdomain <-> plat_tag map structure
 *
 **/
typedef struct regdomain_plat_tag_map
{
    regdomain_enum  en_regdomain;
    int             plat_tag;
} regdomain_plat_tag_map_stru;

typedef struct
{
    char*   name;
    int     case_entry;
} wlan_cfg_cmd;

/* ���ƻ�HOSTȫ�ֱ����ṹ�� */
typedef struct
{
    /* ba tx �ۺ��� */
    unsigned int    ul_ampdu_tx_max_num;
    /* ���� */
    unsigned char   uc_roam_switch;
    unsigned char   uc_roam_scan_band;
    unsigned char   uc_roam_scan_orthogonal;
    signed char     c_roam_trigger_b;
    signed char     c_roam_trigger_a;
    signed char     c_roam_delta_b;
    signed char     c_roam_delta_a;
    /* scan */
    unsigned char   uc_random_mac_addr_scan;
    /* capab */
    unsigned char   uc_disable_capab_2ght40;
    unsigned int   ul_lte_gpio_check_switch;
    unsigned int   ul_lte_ism_priority;
    unsigned int   ul_lte_rx_act;
    unsigned int   ul_lte_tx_act;
} wlan_customize_stru;

extern wlan_customize_stru g_st_wlan_customize;
extern int hwifi_config_init(int);
extern int hwifi_get_init_value(int, int);
extern char* hwifi_get_country_code(void);
extern void hwifi_set_country_code(char*, const unsigned int);
extern int hwifi_get_mac_addr(unsigned char *);
extern unsigned char* hwifi_get_nvram_params(void);
extern int hwifi_is_regdomain_changed(const countrycode_t, const countrycode_t);
extern int hwifi_atcmd_update_host_nv_params(void);

#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif //hisi_customize_wifi.h

