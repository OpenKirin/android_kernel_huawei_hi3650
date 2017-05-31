

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*
 * 1 Header File Including
 */

#include <linux/kernel.h>
#include <linux/time.h>
#include "hisi_customize_wifi.h"
#include "hisi_ini.h"
#include "plat_type.h"
#include "oam_ext_if.h"
#include "wlan_spec_1102.h"
#include "mac_vap.h"
#include "oal_sdio_comm.h"

/* �ն�ͷ�ļ� */
#include <linux/mtd/hisi_nve_interface.h>
#include <linux/etherdevice.h>

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_CUSTOMIZE

/*
 * 2 Global Variable Definition
 */
int32 g_al_host_init_params[WLAN_CFG_INIT_BUTT] = {0};      /* ini���ƻ��������� */
int32 g_al_dts_params[WLAN_CFG_DTS_BUTT] = {0};             /* dts���ƻ��������� */
uint8 g_auc_nv_params[NUM_OF_NV_PARAMS] = {0};              /* nv���ƻ��������� */
int8 g_ac_country_code[COUNTRY_CODE_LEN] = "00";
uint8 g_auc_wifimac[MAC_LEN] = {0x00,0x00,0x00,0x00,0x00,0x00};

/*
 * ���ƻ��ṹ��
 * default values as follows:
 * ampdu_tx_max_num:            WLAN_AMPDU_TX_MAX_NUM               = 64
 * switch:                      ON                                  = 1
 * scan_band:                   ROAM_BAND_2G_BIT|ROAM_BAND_5G_BIT   = 3
 * scan_orthogonal:             ROAM_SCAN_CHANNEL_ORG_BUTT          = 4
 */
wlan_customize_stru g_st_wlan_customize = {
            64,             /* addba_buffer_size */
            1,              /* roam switch */
            3,              /* roam scan band */
            4,              /* roam scan org */
            -70,            /* roam trigger 2G */
            -70,            /* roam trigger 5G */
            10,             /* roam delta 2G */
            10,             /* roam delta 5G */
            0,              /* random mac addr scan */
            0,              /* disable_capab_2ght40 */
            0,              /*lte_gpio_check_switch*/
            0,              /*lte_ism_priority*/
            0,              /*lte_rx_act*/
            0,              /*lte_tx_act*/
};

/**
 *  regdomain <-> country code map table
 *  max support country num: MAX_COUNTRY_COUNT
 *
 **/
OAL_STATIC countryinfo_stru g_ast_country_info_table[] =
{
    {REGDOMAIN_COMMON, {'0', '0'}}, // WORLD DOMAIN
    {REGDOMAIN_FCC, {'A', 'D'}}, // ANDORRA
    {REGDOMAIN_ETSI, {'A', 'E'}}, //UAE
    {REGDOMAIN_ETSI, {'A', 'L'}}, //ALBANIA
    {REGDOMAIN_ETSI, {'A', 'M'}}, //ARMENIA
    {REGDOMAIN_ETSI, {'A', 'N'}}, //NETHERLANDS ANTILLES
    {REGDOMAIN_FCC, {'A', 'R'}}, //ARGENTINA
    {REGDOMAIN_FCC, {'A', 'S'}}, //AMERICAN SOMOA
    {REGDOMAIN_ETSI, {'A', 'T'}}, //AUSTRIA
    {REGDOMAIN_FCC, {'A', 'U'}}, //AUSTRALIA
    {REGDOMAIN_ETSI , {'A', 'W'}}, //ARUBA
    {REGDOMAIN_ETSI,  {'A', 'Z'}}, //AZERBAIJAN
    {REGDOMAIN_ETSI, {'B', 'A'}}, //BOSNIA AND HERZEGOVINA
    {REGDOMAIN_FCC, {'B', 'B'}}, //BARBADOS
    {REGDOMAIN_ETSI, {'B', 'D'}}, //BANGLADESH
    {REGDOMAIN_ETSI, { 'B', 'E'}}, //BELGIUM
    {REGDOMAIN_ETSI, {'B', 'G'}}, //BULGARIA
    {REGDOMAIN_ETSI, {'B', 'H'}}, //BAHRAIN
    {REGDOMAIN_ETSI, {'B', 'L'}}, //
    {REGDOMAIN_FCC, {'B', 'M'}}, //BERMUDA
    {REGDOMAIN_ETSI, {'B', 'N'}}, //BRUNEI DARUSSALAM
    {REGDOMAIN_ETSI, {'B', 'O'}}, //BOLIVIA
    {REGDOMAIN_ETSI, {'B', 'R'}}, //BRAZIL
    {REGDOMAIN_FCC, {'B', 'S'}}, //BAHAMAS
    {REGDOMAIN_ETSI, {'B', 'Y'}}, //BELARUS
    {REGDOMAIN_ETSI, {'B', 'Z'}}, //BELIZE
    {REGDOMAIN_FCC, {'C', 'A'}}, //CANADA
    {REGDOMAIN_ETSI, {'C', 'H'}}, //SWITZERLAND
    {REGDOMAIN_ETSI, {'C', 'L'}}, //CHILE
    {REGDOMAIN_COMMON, {'C', 'N'}}, //CHINA
    {REGDOMAIN_FCC, {'C', 'O'}}, //COLOMBIA
    {REGDOMAIN_ETSI, {'C', 'R'}}, //COSTA RICA
    {REGDOMAIN_ETSI, {'C', 'S'}},
    {REGDOMAIN_ETSI, {'C', 'Y'}}, //CYPRUS
    {REGDOMAIN_ETSI, {'C', 'Z'}}, //CZECH REPUBLIC
    {REGDOMAIN_ETSI, {'D', 'E'}}, //GERMANY
    {REGDOMAIN_ETSI, {'D', 'K'}}, //DENMARK
    {REGDOMAIN_FCC, {'D', 'O'}}, //DOMINICAN REPUBLIC
    {REGDOMAIN_ETSI, {'D', 'Z'}}, //ALGERIA
    {REGDOMAIN_ETSI, {'E', 'C'}}, //ECUADOR
    {REGDOMAIN_ETSI, {'E', 'E'}}, //ESTONIA
    {REGDOMAIN_ETSI, {'E', 'G'}}, //EGYPT
    {REGDOMAIN_ETSI, {'E', 'S'}}, //SPAIN
    {REGDOMAIN_ETSI, {'F', 'I'}}, //FINLAND
    {REGDOMAIN_ETSI, {'F', 'R'}}, //FRANCE
    {REGDOMAIN_ETSI, {'G', 'B'}}, //UNITED KINGDOM
    {REGDOMAIN_FCC, {'G', 'D'}},  //GRENADA
    {REGDOMAIN_ETSI, {'G', 'E'}}, //GEORGIA
    {REGDOMAIN_ETSI, {'G', 'F'}}, //FRENCH GUIANA
    {REGDOMAIN_ETSI, {'G', 'L'}}, //GREENLAND
    {REGDOMAIN_ETSI, {'G', 'P'}}, //GUADELOUPE
    {REGDOMAIN_ETSI, {'G', 'R'}}, //GREECE
    {REGDOMAIN_FCC, {'G', 'T'}},  //GUATEMALA
    {REGDOMAIN_FCC, {'G', 'U'}},  //GUAM
    {REGDOMAIN_ETSI, {'H', 'U'}}, //HUNGARY
    {REGDOMAIN_FCC, {'I', 'D'}},  //INDONESIA
    {REGDOMAIN_ETSI, {'I', 'E'}}, //IRELAND
    {REGDOMAIN_ETSI, {'I', 'L'}}, //ISRAEL
    {REGDOMAIN_ETSI, {'I', 'N'}}, //INDIA
    {REGDOMAIN_ETSI, {'I', 'R'}}, //IRAN, ISLAMIC REPUBLIC OF
    {REGDOMAIN_ETSI, {'I', 'S'}}, //ICELNAD
    {REGDOMAIN_ETSI, {'I', 'T'}}, //ITALY
    {REGDOMAIN_FCC, {'J', 'M'}},  //JAMAICA
    {REGDOMAIN_JAPAN, {'J', 'P'}}, //JAPAN
    {REGDOMAIN_ETSI, {'J', 'O'}}, //JORDAN
    {REGDOMAIN_ETSI, {'K', 'E'}}, //KENYA
    {REGDOMAIN_ETSI, {'K', 'H'}}, //CAMBODIA
    {REGDOMAIN_ETSI, {'K', 'P'}}, //KOREA, DEMOCRATIC PEOPLE's REPUBLIC OF
    {REGDOMAIN_ETSI, {'K', 'R'}}, //KOREA, REPUBLIC OF
    {REGDOMAIN_ETSI, {'K', 'W'}}, //KUWAIT
    {REGDOMAIN_ETSI, {'K', 'Z'}}, //KAZAKHSTAN
    {REGDOMAIN_ETSI, {'L', 'B'}}, //LEBANON
    {REGDOMAIN_ETSI, {'L', 'I'}}, //LIECHTENSTEIN
    {REGDOMAIN_ETSI, {'L', 'K'}}, //SRI-LANKA
    {REGDOMAIN_ETSI, {'L', 'T'}}, //LITHUANIA
    {REGDOMAIN_ETSI, {'L', 'U'}}, //LUXEMBOURG
    {REGDOMAIN_ETSI, {'L','V'}},  //LATVIA
    {REGDOMAIN_ETSI, {'M', 'A'}}, //MOROCCO
    {REGDOMAIN_ETSI, {'M', 'C'}}, //MONACO
    {REGDOMAIN_ETSI, {'M', 'K'}}, //MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF
    {REGDOMAIN_FCC, {'M','N'}}, //MONGOLIA
    {REGDOMAIN_FCC, {'M', 'O'}}, //MACAO
    {REGDOMAIN_FCC, {'M', 'P'}}, //NORTHERN MARIANA ISLANDS
    {REGDOMAIN_ETSI, {'M', 'Q'}}, //MARTINIQUE
    {REGDOMAIN_FCC, {'M', 'T'}}, //MALTA
    {REGDOMAIN_ETSI, {'M', 'U'}}, //MAURITIUS
    {REGDOMAIN_ETSI, {'M', 'W'}}, //MALAWI
    {REGDOMAIN_FCC, {'M', 'X'}}, //MEXICO
    {REGDOMAIN_ETSI, {'M', 'Y'}}, //MALAYSIA
    {REGDOMAIN_ETSI, {'N', 'G'}}, //NIGERIA
    {REGDOMAIN_FCC, {'N', 'I'}}, //NICARAGUA
    {REGDOMAIN_ETSI, {'N', 'L'}}, //NETHERLANDS
    {REGDOMAIN_ETSI, {'N', 'O'}}, //NORWAY
    {REGDOMAIN_ETSI, {'N', 'P'}}, //NEPAL
    {REGDOMAIN_FCC, {'N', 'Z'}}, //NEW-ZEALAND
    {REGDOMAIN_FCC, {'O', 'M'}}, //OMAN
    {REGDOMAIN_FCC, {'P', 'A'}}, //PANAMA
    {REGDOMAIN_ETSI, {'P', 'E'}}, //PERU
    {REGDOMAIN_ETSI, {'P', 'F'}}, //FRENCH POLYNESIA
    {REGDOMAIN_ETSI, {'P', 'G'}}, //PAPUA NEW GUINEA
    {REGDOMAIN_FCC, {'P', 'H'}}, //PHILIPPINES
    {REGDOMAIN_ETSI, {'P', 'K'}}, //PAKISTAN
    {REGDOMAIN_ETSI, {'P', 'L'}}, //POLAND
    {REGDOMAIN_FCC, {'P', 'R'}}, //PUERTO RICO
    {REGDOMAIN_FCC, {'P', 'S'}}, //PALESTINIAN TERRITORY, OCCUPIED
    {REGDOMAIN_ETSI, {'P', 'T'}}, //PORTUGAL
    {REGDOMAIN_FCC, {'P', 'Y'}}, //PARAGUAY
    {REGDOMAIN_ETSI, {'Q', 'A'}}, //QATAR
    {REGDOMAIN_ETSI, {'R', 'E'}}, //REUNION
    {REGDOMAIN_ETSI, {'R', 'O'}}, //ROMAINIA
    {REGDOMAIN_ETSI, {'R', 'S'}}, //SERBIA
    {REGDOMAIN_ETSI, {'R', 'U'}}, //RUSSIA
    {REGDOMAIN_FCC, {'R', 'W'}}, //RWANDA
    {REGDOMAIN_ETSI, {'S', 'A'}}, //SAUDI ARABIA
    {REGDOMAIN_ETSI, {'S', 'E'}}, //SWEDEN
    {REGDOMAIN_ETSI, {'S', 'G'}}, //SINGAPORE
    {REGDOMAIN_ETSI, {'S', 'I'}}, //SLOVENNIA
    {REGDOMAIN_ETSI, {'S', 'K'}}, //SLOVAKIA
    {REGDOMAIN_ETSI, {'S', 'V'}}, //EL SALVADOR
    {REGDOMAIN_ETSI, {'S', 'Y'}}, //SYRIAN ARAB REPUBLIC
    {REGDOMAIN_ETSI, {'T', 'H'}}, //THAILAND
    {REGDOMAIN_ETSI, {'T', 'N'}}, //TUNISIA
    {REGDOMAIN_ETSI, {'T', 'R'}}, //TURKEY
    {REGDOMAIN_ETSI, {'T', 'T'}}, //TRINIDAD AND TOBAGO
    {REGDOMAIN_FCC, {'T', 'W'}}, //TAIWAN, PRIVINCE OF CHINA
    {REGDOMAIN_FCC, {'T', 'Z'}}, //TANZANIA, UNITED REPUBLIC OF
    {REGDOMAIN_ETSI, {'U', 'A'}}, //UKRAINE
    {REGDOMAIN_ETSI, {'U', 'G'}}, //UGANDA
    {REGDOMAIN_FCC, {'U', 'S'}}, //USA
    {REGDOMAIN_ETSI, {'U', 'Y'}}, //URUGUAY
    {REGDOMAIN_FCC, {'U', 'Z'}}, //UZBEKISTAN
    {REGDOMAIN_ETSI, {'V', 'E'}}, //VENEZUELA
    {REGDOMAIN_FCC, {'V', 'I'}}, //VIRGIN ISLANDS, US
    {REGDOMAIN_ETSI, {'V', 'N'}}, //VIETNAM
    {REGDOMAIN_ETSI, {'Y', 'E'}}, //YEMEN
    {REGDOMAIN_ETSI, {'Y', 'T'}}, //MAYOTTE
    {REGDOMAIN_ETSI, {'Z', 'A'}}, //SOUTH AFRICA
    {REGDOMAIN_ETSI, {'Z', 'W'}}, //ZIMBABWE

    {REGDOMAIN_COUNT,{'9','9'}},
};

/**
 * regdomain <-> plat_tag mapping table
 *
 **/
OAL_STATIC regdomain_plat_tag_map_stru g_ast_plat_tag_mapping_table[] =
{
        {REGDOMAIN_FCC,     INI_MODU_POWER_FCC},        //FCC
        {REGDOMAIN_ETSI,    INI_MODU_POWER_ETSI},       //ETSI
        {REGDOMAIN_JAPAN,   INI_MODU_POWER_JP},         //JP
        {REGDOMAIN_COMMON,  INI_MODU_WIFI},             //COMMON

        {REGDOMAIN_COUNT,   INI_MODU_INVALID}
};

OAL_STATIC wlan_cfg_cmd g_ast_wifi_config_dts[] =
{
    /* 5g���� */
    {"band_5g_enable",                                       WLAN_CFG_DTS_BAND_5G_ENABLE},
    /* У׼ */
    {"cali_txpwr_pa_dc_ref_2g_val_chan1",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1},
    {"cali_txpwr_pa_dc_ref_2g_val_chan2",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN2},
    {"cali_txpwr_pa_dc_ref_2g_val_chan3",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN3},
    {"cali_txpwr_pa_dc_ref_2g_val_chan4",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN4},
    {"cali_txpwr_pa_dc_ref_2g_val_chan5",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN5},
    {"cali_txpwr_pa_dc_ref_2g_val_chan6",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN6},
    {"cali_txpwr_pa_dc_ref_2g_val_chan7",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN7},
    {"cali_txpwr_pa_dc_ref_2g_val_chan8",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN8},
    {"cali_txpwr_pa_dc_ref_2g_val_chan9",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN9},
    {"cali_txpwr_pa_dc_ref_2g_val_chan10",                   WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN10},
    {"cali_txpwr_pa_dc_ref_2g_val_chan11",                   WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN11},
    {"cali_txpwr_pa_dc_ref_2g_val_chan12",                   WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN12},
    {"cali_txpwr_pa_dc_ref_2g_val_chan13",                   WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN13},
    {"cali_txpwr_pa_dc_ref_5g_val_band1",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1},
    {"cali_txpwr_pa_dc_ref_5g_val_band2",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND2},
    {"cali_txpwr_pa_dc_ref_5g_val_band3",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND3},
    {"cali_txpwr_pa_dc_ref_5g_val_band4",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND4},
    {"cali_txpwr_pa_dc_ref_5g_val_band5",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND5},
    {"cali_txpwr_pa_dc_ref_5g_val_band6",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND6},
    {"cali_txpwr_pa_dc_ref_5g_val_band7",                    WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND7},
    {"cali_tone_amp_grade",                                  WLAN_CFG_DTS_CALI_TONE_AMP_GRADE},
    /* FCC��֤ */
    {"band_edge_limit_2g_11g_txpwr",                         WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR},
    {"band_edge_limit_2g_11n_ht20_txpwr",                    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_TXPWR},
    {"band_edge_limit_2g_11n_ht40_txpwr",                    WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_TXPWR},
    {"band_edge_limit_5g_11a_ht20_vht20_txpwr",              WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_TXPWR},
    {"band_edge_limit_5g_ht40_vht40_txpwr",                  WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_TXPWR},
    {"band_edge_limit_5g_vht80_txpwr",                       WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_TXPWR},
    {"band_edge_limit_2g_11g_dbb_scaling",                   WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING},
    {"band_edge_limit_2g_11n_ht20_dbb_scaling",              WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_DBB_SCALING},
    {"band_edge_limit_2g_11n_ht40_dbb_scaling",              WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_DBB_SCALING},
    {"band_edge_limit_5g_11a_ht20_vht20_dbb_scaling",        WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_DBB_SCALING},
    {"band_edge_limit_5g_ht40_vht40_dbb_scaling",            WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_DBB_SCALING},
    {"band_edge_limit_5g_vht80_dbb_scaling",                 WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_DBB_SCALING},
    /* RF REGISTER */
    {"rf_reg117",                                           WLAN_CFG_DTS_RF_REG117},
    {"rf_reg123",                                           WLAN_CFG_DTS_RF_REG123},
    {"rf_reg124",                                           WLAN_CFG_DTS_RF_REG124},
    {"rf_reg125",                                           WLAN_CFG_DTS_RF_REG125},
    {"rf_reg126",                                           WLAN_CFG_DTS_RF_REG126},
    /* bt У׼ */
    {"cali_txpwr_pa_ref_band1",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND1},
    {"cali_txpwr_pa_ref_band2",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND2},
    {"cali_txpwr_pa_ref_band3",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND3},
    {"cali_txpwr_pa_ref_band4",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND4},
    {"cali_txpwr_pa_ref_band5",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND5},
    {"cali_txpwr_pa_ref_band6",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND6},
    {"cali_txpwr_pa_ref_band7",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND7},
    {"cali_txpwr_pa_ref_band8",                              WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND8},
    {"cali_txpwr_pa_ref_num",                                WLAN_CFG_DTS_BT_CALI_TXPWR_PA_NUM},
    {"cali_txpwr_pa_fre1",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE1},
    {"cali_txpwr_pa_fre2",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE2},
    {"cali_txpwr_pa_fre3",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE3},
    {"cali_txpwr_pa_fre4",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE4},
    {"cali_txpwr_pa_fre5",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE5},
    {"cali_txpwr_pa_fre6",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE6},
    {"cali_txpwr_pa_fre7",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE7},
    {"cali_txpwr_pa_fre8",                                   WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE8},
    {"cali_bt_tone_amp_grade",                               WLAN_CFG_DTS_BT_CALI_TONE_AMP_GRADE},

    {OAL_PTR_NULL, 0}
};

OAL_STATIC wlan_cfg_cmd g_ast_wifi_config_cmds[] =
{
    /* ROAM */
    {"roam_switch",                     WLAN_CFG_INIT_ROAM_SWITCH},
    {"scan_orthogonal",                 WLAN_CFG_INIT_SCAN_ORTHOGONAL},
    {"trigger_b",                       WLAN_CFG_INIT_TRIGGER_B},
    {"trigger_a",                       WLAN_CFG_INIT_TRIGGER_A},
    {"delta_b",                         WLAN_CFG_INIT_DELTA_B},
    {"delta_a",                         WLAN_CFG_INIT_DELTA_A},

    /* ���� */
    {"ampdu_tx_max_num",                WLAN_CFG_INIT_AMPDU_TX_MAX_NUM},
    {"used_mem_for_start",              WLAN_CFG_INIT_USED_MEM_FOR_START},
    {"used_mem_for_stop",               WLAN_CFG_INIT_USED_MEM_FOR_STOP},
    {"rx_ack_limit",                    WLAN_CFG_INIT_RX_ACK_LIMIT},
    {"sdio_d2h_assemble_count",         WLAN_CFG_INIT_SDIO_D2H_ASSEMBLE_COUNT},
    {"sdio_h2d_assemble_count",         WLAN_CFG_INIT_SDIO_H2D_ASSEMBLE_COUNT},
    /* LINKLOSS */
    {"link_loss_threshold_wlan_near",   WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_NEAR},
    {"link_loss_threshold_wlan_far",    WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_FAR},
    {"link_loss_threshold_p2p",         WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_P2P},
    /* �Զ���Ƶ */
    {"pss_threshold_level_0",           WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_0},
    {"cpu_freq_limit_level_0",          WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_0},
    {"ddr_freq_limit_level_0",          WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_0},
    {"pss_threshold_level_1",           WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_1},
    {"cpu_freq_limit_level_1",          WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_1},
    {"ddr_freq_limit_level_1",          WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_1},
    {"pss_threshold_level_2",           WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_2},
    {"cpu_freq_limit_level_2",          WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_2},
    {"ddr_freq_limit_level_2",          WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_2},
    {"pss_threshold_level_3",           WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_3},
    {"cpu_freq_limit_level_3",          WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_3},
    {"ddr_freq_limit_level_3",          WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_3},
    {"device_type_level_0",             WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_0},
    {"device_type_level_1",             WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_1},
    {"device_type_level_2",             WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_2},
    {"device_type_level_3",             WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_3},
    /* �͹��� */
    {"powermgmt_switch",                WLAN_CFG_INIT_POWERMGMT_SWITCH},
    /* ��ά�ɲ� */
    {"loglevel",                        WLAN_CFG_INIT_LOGLEVEL},
    /* PHY�㷨 */
    {"chn_est_ctrl",                    WLAN_CFG_INIT_CHN_EST_CTRL},
    {"power_ref_5g",                    WLAN_CFG_INIT_POWER_REF_5G},
    /* ʱ����Ϣ */
    {"rts_clk_freq",                    WLAN_CFG_INIT_RTS_CLK_FREQ},
    {"clk_type",                        WLAN_CFG_INIT_CLK_TYPE},
    /* 2G RFǰ�� */
    {"rf_line_txrx_gain_db_2g_band1_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4},
    {"rf_line_txrx_gain_db_2g_band1_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT10},
    {"rf_line_txrx_gain_db_2g_band2_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT4},
    {"rf_line_txrx_gain_db_2g_band2_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT10},
    {"rf_line_txrx_gain_db_2g_band3_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT4},
    {"rf_line_txrx_gain_db_2g_band3_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10},
    /* 5G RFǰ�� */
    {"rf_line_txrx_gain_db_5g_band1_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT4},
    {"rf_line_txrx_gain_db_5g_band1_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT10},
    {"rf_line_txrx_gain_db_5g_band2_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT4},
    {"rf_line_txrx_gain_db_5g_band2_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT10},
    {"rf_line_txrx_gain_db_5g_band3_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT4},
    {"rf_line_txrx_gain_db_5g_band3_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT10},
    {"rf_line_txrx_gain_db_5g_band4_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT4},
    {"rf_line_txrx_gain_db_5g_band4_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT10},
    {"rf_line_txrx_gain_db_5g_band5_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT4},
    {"rf_line_txrx_gain_db_5g_band5_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT10},
    {"rf_line_txrx_gain_db_5g_band6_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT4},
    {"rf_line_txrx_gain_db_5g_band6_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT10},
    {"rf_line_txrx_gain_db_5g_band7_mult4",     WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT4},
    {"rf_line_txrx_gain_db_5g_band7_mult10",    WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT10},
    {"rf_line_rx_gain_db_5g",           WLAN_CFG_INIT_RF_LINE_RX_GAIN_DB_5G},
    {"lna_gain_db_5g",                  WLAN_CFG_INIT_LNA_GAIN_DB_5G},
    {"rf_line_tx_gain_db_5g",           WLAN_CFG_INIT_RF_LINE_TX_GAIN_DB_5G},
    {"ext_switch_isexist_5g",           WLAN_CFG_INIT_EXT_SWITCH_ISEXIST_5G},
    {"ext_pa_isexist_5g",               WLAN_CFG_INIT_EXT_PA_ISEXIST_5G},
    {"ext_lna_isexist_5g",              WLAN_CFG_INIT_EXT_LNA_ISEXIST_5G},
    {"lna_on2off_time_ns_5g",           WLAN_CFG_INIT_LNA_ON2OFF_TIME_NS_5G},
    {"lna_off2on_time_ns_5g",           WLAN_CFG_INIT_LNA_OFF2ON_TIME_NS_5G},
    /* �¶��������·��书���½�����Ĺ��ʲ��� */
    {"tx_ratio_level_0",                WLAN_CFG_INIT_TX_RATIO_LEVEL_0},
    {"tx_pwr_comp_val_level_0",         WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_0},
    {"tx_ratio_level_1",                WLAN_CFG_INIT_TX_RATIO_LEVEL_1},
    {"tx_pwr_comp_val_level_1",         WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_1},
    {"tx_ratio_level_2",                WLAN_CFG_INIT_TX_RATIO_LEVEL_2},
    {"tx_pwr_comp_val_level_2",         WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_2},
    {"more_pwr",                        WLAN_CFG_INIT_MORE_PWR},
    /* SCAN */
    {"random_mac_addr_scan",            WLAN_CFG_INIT_RANDOM_MAC_ADDR_SCAN},
    /* 11AC2G */
    {"11ac2g_enable",                   WLAN_CFG_INIT_11AC2G_ENABLE},
    {"disable_capab_2ght40",            WLAN_CFG_INIT_DISABLE_CAPAB_2GHT40},
    {"dual_antenna_enable",             WLAN_CFG_INIT_DUAL_ANTENNA_ENABLE}, /* ˫���߿��� */
    {"far_dist_pow_gain_switch",        WLAN_CFG_INIT_FAR_DIST_POW_GAIN_SWITCH},
    {"lte_gpio_check_switch",           WLAN_CFG_LTE_GPIO_CHECK_SWITCH},/* lte�ܽż�⿪�� */
    {"lte_ism_priority",                WLAN_ATCMDSRV_LTE_ISM_PRIORITY},
    {"lte_rx_act",                      WLAN_ATCMDSRV_LTE_RX_ACT},
    {"lte_tx_act",                      WLAN_ATCMDSRV_LTE_TX_ACT},
    {"far_dist_dsss_scale_promote_switch",      WLAN_CFG_INIT_FAR_DIST_DSSS_SCALE_PROMOTE_SWITCH},
    {OAL_PTR_NULL, 0}
};

OAL_STATIC wlan_cfg_cmd g_ast_nvram_config_ini[NVRAM_PARAMS_INDEX_BUTT] =
{
    {"nvram_params0",                     NVRAM_PARAMS_INDEX_0},
    {"nvram_params1",                     NVRAM_PARAMS_INDEX_1},
    {"nvram_params2",                     NVRAM_PARAMS_INDEX_2},
    {"nvram_params3",                     NVRAM_PARAMS_INDEX_3},
    {"nvram_params4",                     NVRAM_PARAMS_INDEX_4},
    {"nvram_params5",                     NVRAM_PARAMS_INDEX_5},
    {"nvram_params6",                     NVRAM_PARAMS_INDEX_6},
    {"nvram_params7",                     NVRAM_PARAMS_INDEX_7},
    {"nvram_params8",                     NVRAM_PARAMS_INDEX_8},
    {"nvram_params9",                     NVRAM_PARAMS_INDEX_9},
    {"nvram_params10",                    NVRAM_PARAMS_INDEX_10},
    {"nvram_params11",                    NVRAM_PARAMS_INDEX_11},
    {"nvram_params12",                    NVRAM_PARAMS_INDEX_12},
    {"nvram_params13",                    NVRAM_PARAMS_INDEX_13},
    {"nvram_params14",                    NVRAM_PARAMS_INDEX_14},
    {"nvram_params15",                    NVRAM_PARAMS_INDEX_15},
    {"nvram_params16",                    NVRAM_PARAMS_INDEX_16},
    {"nvram_params17",                    NVRAM_PARAMS_INDEX_17},
    {"nvram_params18",                    NVRAM_PARAMS_INDEX_18},
    {"nvram_params19",                    NVRAM_PARAMS_INDEX_19},
    {"nvram_params20",                    NVRAM_PARAMS_INDEX_20},
    {"nvram_params21",                    NVRAM_PARAMS_INDEX_21},
    {"nvram_params22",                    NVRAM_PARAMS_INDEX_22},
    {"nvram_params23",                    NVRAM_PARAMS_INDEX_23},
    {"nvram_params24",                    NVRAM_PARAMS_INDEX_24},
    {"nvram_params25",                    NVRAM_PARAMS_INDEX_25},
};

/*****************************************************************************
 �� �� ��  : original_value_for_dts_params
 ��������  : dts���ƻ�������ֵ����
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void original_value_for_dts_params(oal_void)
{
    g_al_dts_params[WLAN_CFG_DTS_BAND_5G_ENABLE]                        = 0;
    /* У׼ */
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN1]     = 6250;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN2]     = 5362;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN3]     = 4720;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN4]     = 4480;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN5]     = 4470;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN6]     = 4775;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN7]     = 5200;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN8]     = 5450;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN9]     = 5600;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN10]    = 6100;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN11]    = 6170;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN12]    = 6350;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_2G_VAL_CHAN13]    = 6530;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND1]     = 2500;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND2]     = 2800;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND3]     = 3100;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND4]     = 3600;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND5]     = 3600;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND6]     = 3700;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TXPWR_PA_DC_REF_5G_VAL_BAND7]     = 3800;
    g_al_dts_params[WLAN_CFG_DTS_CALI_TONE_AMP_GRADE]                   = 2;
    /* FCC��֤ */
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_TXPWR]                      = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_TXPWR]                 = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_TXPWR]                 = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_TXPWR]           = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_TXPWR]               = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_TXPWR]                    = 150;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11G_DBB_SCALING]                = 0x68;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT20_DBB_SCALING]           = 0x62;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_2G_11N_HT40_DBB_SCALING]           = 0x62;
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_11A_HT20_VHT20_DBB_SCALING]     = 0x68;/* ���� */
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_HT40_VHT40_DBB_SCALING]         = 0x68;/* ���� */
    g_al_dts_params[WLAN_CFG_DTS_BAND_EDGE_LIMIT_5G_VHT80_DBB_SCALING]              = 0x68;/* ���� */
    /* rf register */
    g_al_dts_params[WLAN_CFG_DTS_RF_REG117]                                 = 0x0505;
    g_al_dts_params[WLAN_CFG_DTS_RF_REG123]                                 = 0x9d01;
    g_al_dts_params[WLAN_CFG_DTS_RF_REG124]                                 = 0x9d01;
    g_al_dts_params[WLAN_CFG_DTS_RF_REG125]                                 = 0x9d01;
    g_al_dts_params[WLAN_CFG_DTS_RF_REG126]                                 = 0x9d01;
    /* bt tmp */
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND1]            = 11000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND2]            = 10000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND3]            = 7000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND4]            = 8000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND5]            = 7000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND6]            = 7000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND7]            = 12000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_REF_BAND8]            = 12000;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_NUM]                  = 7;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE1]                 = 0;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE2]                 = 10;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE3]                 = 28;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE4]                 = 45;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE5]                 = 53;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE6]                 = 63;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE7]                 = 76;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TXPWR_PA_FRE8]                 = 78;
    g_al_dts_params[WLAN_CFG_DTS_BT_CALI_TONE_AMP_GRADE]                = 2;
}
/*****************************************************************************
 �� �� ��  : host_params_init_first
 ��������  : �����ƻ�����ȫ������ g_al_host_init_params ����ֵ
             ini�ļ���ȡʧ��ʱ�ó�ֵ
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void host_params_init_first(oal_void)
{
    /* ROAM */
    g_al_host_init_params[WLAN_CFG_INIT_ROAM_SWITCH]                       = 1;
    g_al_host_init_params[WLAN_CFG_INIT_SCAN_ORTHOGONAL]                   = 4;
    g_al_host_init_params[WLAN_CFG_INIT_TRIGGER_B]                         = -70;
    g_al_host_init_params[WLAN_CFG_INIT_TRIGGER_A]                         = -70;
    g_al_host_init_params[WLAN_CFG_INIT_DELTA_B]                           = 10;
    g_al_host_init_params[WLAN_CFG_INIT_DELTA_A]                           = 10;

    /* ���� */
    g_al_host_init_params[WLAN_CFG_INIT_AMPDU_TX_MAX_NUM]                  = WLAN_AMPDU_TX_MAX_BUF_SIZE;
    g_al_host_init_params[WLAN_CFG_INIT_USED_MEM_FOR_START]                = 45;
    g_al_host_init_params[WLAN_CFG_INIT_USED_MEM_FOR_STOP]                 = 25;
    g_al_host_init_params[WLAN_CFG_INIT_RX_ACK_LIMIT]                      = 10;
    g_al_host_init_params[WLAN_CFG_INIT_SDIO_D2H_ASSEMBLE_COUNT]           = HISDIO_DEV2HOST_SCATT_MAX;
    g_al_host_init_params[WLAN_CFG_INIT_SDIO_H2D_ASSEMBLE_COUNT]           = 8;
    /* LINKLOSS */
    g_al_host_init_params[WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_NEAR]     = 40;
    g_al_host_init_params[WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_WLAN_FAR]      = 100;
    g_al_host_init_params[WLAN_CFG_INIT_LINK_LOSS_THRESHOLD_P2P]           = 40;
    /* �Զ���Ƶ */
    g_al_host_init_params[WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_0]             = PPS_VALUE_0;
    g_al_host_init_params[WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_0]            = CPU_MIN_FREQ_VALUE_0;
    g_al_host_init_params[WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_0]            = DDR_MIN_FREQ_VALUE_0;
    g_al_host_init_params[WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_0]               = FREQ_IDLE;
    g_al_host_init_params[WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_1]             = PPS_VALUE_1;
    g_al_host_init_params[WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_1]            = CPU_MIN_FREQ_VALUE_1;
    g_al_host_init_params[WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_1]            = DDR_MIN_FREQ_VALUE_1;
    g_al_host_init_params[WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_1]               = FREQ_MIDIUM;
    g_al_host_init_params[WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_2]             = PPS_VALUE_2;
    g_al_host_init_params[WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_2]            = CPU_MIN_FREQ_VALUE_2;
    g_al_host_init_params[WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_2]            = DDR_MIN_FREQ_VALUE_2;
    g_al_host_init_params[WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_2]               = FREQ_HIGHER;
    g_al_host_init_params[WLAN_CFG_INIT_PSS_THRESHOLD_LEVEL_3]             = PPS_VALUE_3;
    g_al_host_init_params[WLAN_CFG_INIT_CPU_FREQ_LIMIT_LEVEL_3]            = CPU_MIN_FREQ_VALUE_3;
    g_al_host_init_params[WLAN_CFG_INIT_DDR_FREQ_LIMIT_LEVEL_3]            = DDR_MIN_FREQ_VALUE_3;
    g_al_host_init_params[WLAN_CFG_INIT_DEVICE_TYPE_LEVEL_3]               = FREQ_HIGHEST;
    /* �͹��� */
    g_al_host_init_params[WLAN_CFG_INIT_POWERMGMT_SWITCH]                  = 1;
    /* ��ά�ɲ� */
    /* ��־���� */
    g_al_host_init_params[WLAN_CFG_INIT_LOGLEVEL]                          = OAM_LOG_LEVEL_WARNING;
    /* PHY�㷨 */
    g_al_host_init_params[WLAN_CFG_INIT_CHN_EST_CTRL]                      = CHN_EST_CTRL_MATE7;
    g_al_host_init_params[WLAN_CFG_INIT_POWER_REF_5G]                      = PHY_POWER_REF_5G_MT7;
    /* ʱ����Ϣ */
    g_al_host_init_params[WLAN_CFG_INIT_RTS_CLK_FREQ]                      = 32768;
    g_al_host_init_params[WLAN_CFG_INIT_CLK_TYPE]                          = 0;
    /* 2G RFǰ�� */
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT4]    = -12;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND1_MULT10]   = -30;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT4]    = -12;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND2_MULT10]   = -30;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT4]    = -12;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_2G_BAND3_MULT10]   = -30;
    /* 5G RFǰ�� */
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND1_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND2_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND3_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND4_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND5_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND6_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT4]    = -8;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TXRX_GAIN_DB_5G_BAND7_MULT10]   = -20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_RX_GAIN_DB_5G]             = -12;
    g_al_host_init_params[WLAN_CFG_INIT_LNA_GAIN_DB_5G]                    = 20;
    g_al_host_init_params[WLAN_CFG_INIT_RF_LINE_TX_GAIN_DB_5G]             = -12;
    g_al_host_init_params[WLAN_CFG_INIT_EXT_SWITCH_ISEXIST_5G]             = 1;
    g_al_host_init_params[WLAN_CFG_INIT_EXT_PA_ISEXIST_5G]                 = 1;
    g_al_host_init_params[WLAN_CFG_INIT_EXT_LNA_ISEXIST_5G]                = 1;
    g_al_host_init_params[WLAN_CFG_INIT_LNA_ON2OFF_TIME_NS_5G]             = 630;
    g_al_host_init_params[WLAN_CFG_INIT_LNA_OFF2ON_TIME_NS_5G]             = 320;
    /* �¶��������·��书���½�����Ĺ��ʲ��� */
    g_al_host_init_params[WLAN_CFG_INIT_TX_RATIO_LEVEL_0]                  = 900;
    g_al_host_init_params[WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_0]           = 17;
    g_al_host_init_params[WLAN_CFG_INIT_TX_RATIO_LEVEL_1]                  = 650;
    g_al_host_init_params[WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_1]           = 13;
    g_al_host_init_params[WLAN_CFG_INIT_TX_RATIO_LEVEL_2]                  = 280;
    g_al_host_init_params[WLAN_CFG_INIT_TX_PWR_COMP_VAL_LEVEL_2]           = 5;
    g_al_host_init_params[WLAN_CFG_INIT_MORE_PWR]                          = 7;
    /* SCAN */
    g_al_host_init_params[WLAN_CFG_INIT_RANDOM_MAC_ADDR_SCAN]              = 0;
    /* 11AC2G */
    g_al_host_init_params[WLAN_CFG_INIT_11AC2G_ENABLE]                     = 1;
    g_al_host_init_params[WLAN_CFG_INIT_DISABLE_CAPAB_2GHT40]              = 0;
    g_al_host_init_params[WLAN_CFG_INIT_DUAL_ANTENNA_ENABLE]            = 0;
    g_al_host_init_params[WLAN_CFG_INIT_FAR_DIST_POW_GAIN_SWITCH]          = 1;
    g_al_host_init_params[WLAN_CFG_LTE_GPIO_CHECK_SWITCH]                  = 0;
    g_al_host_init_params[WLAN_ATCMDSRV_LTE_ISM_PRIORITY]                  = 0;
    g_al_host_init_params[WLAN_ATCMDSRV_LTE_RX_ACT]                        = 0;
    g_al_host_init_params[WLAN_ATCMDSRV_LTE_TX_ACT]                        = 0;
    g_al_host_init_params[WLAN_CFG_INIT_FAR_DIST_DSSS_SCALE_PROMOTE_SWITCH]     = 1;
}

/*****************************************************************************
 �� �� ��  : hwifi_get_regdomain_from_country_code
 ��������  : ���ݹ������ҵ���Ӧ��regdomain
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC regdomain_enum hwifi_get_regdomain_from_country_code(const countrycode_t country_code)
{
    regdomain_enum  en_regdomain = REGDOMAIN_COMMON;
    int32           table_idx = 0;

    while (g_ast_country_info_table[table_idx].en_regdomain != REGDOMAIN_COUNT)
    {
        if (0 == oal_memcmp(country_code, g_ast_country_info_table[table_idx].auc_country_code, COUNTRY_CODE_LEN))
        {
            // en_regdomain = g_ast_country_info_table[table_idx].en_regdomain;

            /* Ŀǰֻ����FCC�ͷ�FCC */
            en_regdomain = (g_ast_country_info_table[table_idx].en_regdomain == REGDOMAIN_FCC) ? REGDOMAIN_FCC : REGDOMAIN_COMMON;
            break;
        }
        ++table_idx;
    }

    return en_regdomain;
}

/*****************************************************************************
 �� �� ��  : hwifi_is_regdomain_changed
 ��������  : ������ı�󣬶�Ӧ��regdomain�Ƿ��б仯
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 hwifi_is_regdomain_changed(const countrycode_t country_code_old, const countrycode_t country_code_new)
{
    return hwifi_get_regdomain_from_country_code(country_code_old) != hwifi_get_regdomain_from_country_code(country_code_new);
}

/*****************************************************************************
 �� �� ��  : hwifi_get_plat_tag_from_country_code
 ��������  : ���ݹ������ҵ�ƽ̨��Ӧ��tag
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC int32 hwifi_get_plat_tag_from_country_code(const countrycode_t country_code)
{
    regdomain_enum  en_regdomain;
    int32           table_idx = 0;

    en_regdomain = hwifi_get_regdomain_from_country_code(country_code);

    while(g_ast_plat_tag_mapping_table[table_idx].en_regdomain != REGDOMAIN_COUNT
        && g_ast_plat_tag_mapping_table[table_idx].plat_tag != INI_MODU_INVALID)
    {
        /* matched */
        if (en_regdomain == g_ast_plat_tag_mapping_table[table_idx].en_regdomain)
        {
            return g_ast_plat_tag_mapping_table[table_idx].plat_tag;
        }

        ++table_idx;
    }

    /* not found, use common regdomain */
    return INI_MODU_WIFI;
}

/*****************************************************************************
 �� �� ��  : hwifi_fetch_ori_caldata
 ��������  : ����У׼��ȡ��ʼУ׼���������ṩ�ӿڣ���atcmdģ�����
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 hwifi_fetch_ori_caldata(uint8* auc_caldata, int32 l_nvm_len)
{
    int32 l_ret = INI_FAILED;
    int32 l_cfg_id;
    int32 aul_nvram_params[NVRAM_PARAMS_INDEX_BUTT]={0};

    if (l_nvm_len != HISI_CUST_NVRAM_LEN)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwifi_fetch_ori_caldata atcmd[nv_len:%d] and plat_ini[nv_len:%d] model have different nvm lenth!!",
                        l_nvm_len, HISI_CUST_NVRAM_LEN);
        return INI_FAILED;
    }

    oal_memset(auc_caldata, 0x00, HISI_CUST_NVRAM_LEN);

    for (l_cfg_id = NVRAM_PARAMS_INDEX_0; l_cfg_id < NVRAM_PARAMS_INDEX_BUTT; l_cfg_id++)
    {
        l_ret = get_cust_conf_int32(INI_MODU_WIFI, g_ast_nvram_config_ini[l_cfg_id].name, &aul_nvram_params[l_cfg_id]);
        if(INI_FAILED == l_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "hwifi_fetch_ori_caldata read ori caldata %d from ini failed!", l_cfg_id);
            return INI_FAILED;
        }
    }

    OAM_INFO_LOG0(0, OAM_SF_ANY, "hwifi_fetch_ori_caldata read ori caldata from ini success!");
    oal_memcopy(auc_caldata, aul_nvram_params, HISI_CUST_NVRAM_LEN);

    return INI_SUCC;
}
/*****************************************************************************
 �� �� ��  : hwifi_config_init_nvram
 ��������  : handle nvram customize params
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC int32 hwifi_config_init_nvram(void)
{
    OAL_STATIC oal_bool_enum en_nvm_initialed = OAL_FALSE;  /* �Ƿ�Ϊ��һ�γ�ʼ��������ǹ�������µ��õı��ӿڣ�����ȥnvm��ȡ���� */
    int32 l_ret = INI_FAILED;
    int32 l_cfg_id;
    int32 aul_nvram_params[NVRAM_PARAMS_INDEX_BUTT]={0};
    int32 l_plat_tag;

    oal_memset(g_auc_nv_params, 0x00, sizeof(g_auc_nv_params));

    if (OAL_FALSE == en_nvm_initialed)
    {
        /* DTS2016080509156:FCC��֤���Ҳ����ò���У׼���� */
        if (hwifi_get_regdomain_from_country_code(hwifi_get_country_code()) != REGDOMAIN_FCC)
        {
            l_ret = get_cust_conf_string(CUST_MODU_NVRAM, OAL_PTR_NULL, g_auc_nv_params, sizeof(g_auc_nv_params));

            if (INI_SUCC == l_ret && g_auc_nv_params[0] != 0)
            {
                /* ��ȡ�ɹ�������־λ��TRUE */
                en_nvm_initialed = OAL_TRUE;
                return INI_SUCC;
            }

            OAM_WARNING_LOG3(0, OAM_SF_ANY, "hwifi_config_init_nvram read nvram failed[ret:%d] or wrong values[first eight values:0x%x %x], read dts instead!", l_ret, *((oal_uint32*)g_auc_nv_params),*((oal_uint32*)(g_auc_nv_params+4)));
        }
        else
        {
            en_nvm_initialed = OAL_TRUE;
        }
    }

    /* read nvm failed or data not exist or country_code updated, read ini:cust_spec > cust_common > default */
    /* find plat tag */
    l_plat_tag = hwifi_get_plat_tag_from_country_code(hwifi_get_country_code());
    OAM_WARNING_LOG1(0, OAM_SF_ANY, "hwifi_config_init_nvram plat_tag:0x%2x!", l_plat_tag);

    for (l_cfg_id = NVRAM_PARAMS_INDEX_0; l_cfg_id < NVRAM_PARAMS_INDEX_BUTT; l_cfg_id++)
    {
        l_ret = get_cust_conf_int32(l_plat_tag, g_ast_nvram_config_ini[l_cfg_id].name, &aul_nvram_params[l_cfg_id]);

        if(INI_FAILED == l_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "hwifi_config_init_nvram read %d from ini failed!", l_cfg_id);
            /* ��ȡʧ��ʱ���������㣬��ֹ�·���device */
            oal_memset(g_auc_nv_params, 0x00, sizeof(g_auc_nv_params));
            return INI_FAILED;
        }
    }

    OAM_INFO_LOG0(0, OAM_SF_ANY, "hwifi_config_init_nvram read from ini success!");
    oal_memcopy(g_auc_nv_params, aul_nvram_params, sizeof(g_auc_nv_params));

    return INI_SUCC;
}
/*****************************************************************************
 �� �� ��  : hwifi_config_init
 ��������  : netdev open ���õĶ��ƻ������
             ��ȡini�ļ������� g_al_host_init_params ȫ������
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��2��
    ��    ��   : h00349274
    �޸�����   : ����tag�����ж�ini��dts

*****************************************************************************/
int32 hwifi_config_init(int32 cus_tag)
{
    int32               l_cfg_id;
    int32               l_ret = INI_FAILED;
    int32               l_ori_val;
    wlan_cfg_cmd*       pgast_wifi_config;
    int32*              pgal_params;
    int32               l_cfg_value = 0;
    int32               l_wlan_cfg_butt;

    switch (cus_tag)
    {
        case CUS_TAG_NV:
            return hwifi_config_init_nvram();
        case CUS_TAG_INI:
            host_params_init_first();
            pgast_wifi_config = g_ast_wifi_config_cmds;
            pgal_params = g_al_host_init_params;
            l_wlan_cfg_butt = WLAN_CFG_INIT_BUTT;
            break;
        case CUS_TAG_DTS:
            original_value_for_dts_params();
            pgast_wifi_config = g_ast_wifi_config_dts;
            pgal_params = g_al_dts_params;
            l_wlan_cfg_butt = WLAN_CFG_DTS_BUTT;
            break;
        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "hisi_customize_wifi tag number[0x%x] not correct!", cus_tag);
            return INI_FAILED;
    }

    for(l_cfg_id=0; l_cfg_id<l_wlan_cfg_butt; ++l_cfg_id)
    {


        /* ��ȡini������ֵ */
        l_ret = get_cust_conf_int32(INI_MODU_WIFI, pgast_wifi_config[l_cfg_id].name, &l_cfg_value);
        if (INI_FAILED == l_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "hisi_customize_wifi read ini file failed, check if cfg_id[%d] exists!", l_cfg_id);
            continue;
        }

        l_ori_val = pgal_params[l_cfg_id];
        pgal_params[l_cfg_id] = l_cfg_value;
        OAM_WARNING_LOG3(0, OAM_SF_ANY, "hisi_customize_wifi [cfg_id:%d]value changed from [init:%d] to [config:%d]. \n", l_cfg_id, l_ori_val, pgal_params[l_cfg_id]);
    }

    return INI_SUCC;
}
/*****************************************************************************
 �� �� ��  : char2byte
 ��������  : ͳ��ֵ���ж����޶�ȡ��mac��ַ
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC int char2byte( char* strori, char* outbuf )
{
    int i = 0;
    int temp = 0;
    int sum = 0;

    for( i = 0; i < 12; i++ )
    {
        switch (strori[i]) {
            case '0' ... '9':
                temp = strori[i] - '0';
                break;

            case 'a' ... 'f':
                temp = strori[i] - 'a' + 10;
                break;

            case 'A' ... 'F':
                temp = strori[i] - 'A' + 10;
                break;
        }

        sum += temp;
        if( i % 2 == 0 ){
            outbuf[i/2] |= temp << 4;
        }
        else{
            outbuf[i/2] |= temp;
        }
    }

    return sum;
}
/*****************************************************************************
 �� �� ��  : hwifi_get_mac_addr
 ��������  : ��nvram�л�ȡmac��ַ
             �����ȡʧ�ܣ������һ��mac��ַ
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 hwifi_get_mac_addr(uint8 *puc_buf)
{
    struct hisi_nve_info_user st_info;
    int32 l_ret = -1;
    int32 l_sum = 0;

    if (NULL == puc_buf)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hisi_customize_wifi::buf is NULL!");
        return INI_FAILED;
    }

    oal_memset(puc_buf, 0, MAC_LEN);

    oal_memset(&st_info, 0, sizeof(st_info));
    st_info.nv_number  = NV_WLAN_NUM;   //nve item

    strncpy(st_info.nv_name, "MACWLAN", sizeof("MACWLAN"));

    st_info.valid_size = NV_WLAN_VALID_SIZE;
    st_info.nv_operation = NV_READ;

    if (0 != g_auc_wifimac[0] || 0 != g_auc_wifimac[1] || 0 != g_auc_wifimac[2] || 0 != g_auc_wifimac[3]
        || 0 != g_auc_wifimac[4] || 0 != g_auc_wifimac[5])
    {
        memcpy(puc_buf, g_auc_wifimac, MAC_LEN);
        return INI_SUCC;
    }

    l_ret = hisi_nve_direct_access(&st_info);

    if (!l_ret)
    {
        l_sum = char2byte(st_info.nv_data, puc_buf);
        if (0 != l_sum)
        {
            INI_WARNING("hisi_customize_wifi get MAC from NV: mac="MACFMT"\n", MAC2STR(puc_buf));
            oal_memcopy(g_auc_wifimac, puc_buf, MAC_LEN);
        }else{
            random_ether_addr(puc_buf);
            puc_buf[1] = 0x11;
            puc_buf[2] = 0x02;
        }
    }else{
        random_ether_addr(puc_buf);
        puc_buf[1] = 0x11;
        puc_buf[2] = 0x02;
    }

    return INI_SUCC;
}
/*****************************************************************************
 �� �� ��  : hwifi_get_init_value
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��2��
    ��    ��   : h00349274
    �޸�����   : ����tag�����ж�ini��dts

*****************************************************************************/
int32 hwifi_get_init_value(int32 cus_tag, int32 cfg_id)
{
    int32*              pgal_params = OAL_PTR_NULL;
    int32               l_wlan_cfg_butt;

    if (CUS_TAG_INI == cus_tag)
    {
        pgal_params = &g_al_host_init_params[0];
        l_wlan_cfg_butt = WLAN_CFG_INIT_BUTT;
    }
    else if (CUS_TAG_DTS == cus_tag)
    {
        pgal_params = &g_al_dts_params[0];
        l_wlan_cfg_butt = WLAN_CFG_DTS_BUTT;
    }
    else
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "hisi_customize_wifi tag number[0x%2x] not correct!", cus_tag);
        return INI_FAILED;
    }

    if (0 > cfg_id || l_wlan_cfg_butt <= cfg_id)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hisi_customize_wifi cfg id[%d] out of range, max cfg id is:%d", cfg_id, l_wlan_cfg_butt-1);
        return INI_FAILED;
    }
    return pgal_params[cfg_id];
}
/*****************************************************************************
 �� �� ��  : hwifi_get_country_code
 ��������  :

 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
int8* hwifi_get_country_code(void)
{
    int32 l_ret;

    if (g_ac_country_code[0] != '0' && g_ac_country_code[1] != '0')
    {
        return g_ac_country_code;
    }

    /* ��ȡcust������ */
    l_ret = get_cust_conf_string(INI_MODU_WIFI, STR_COUNTRY_CODE, g_ac_country_code, sizeof(g_ac_country_code)-1);

    if(INI_FAILED == l_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "hisi_customize_wifi read country code failed, check if it exists!");
        strncpy(g_ac_country_code, "99", 2);
    }
    g_ac_country_code[2] = '\0';

    return g_ac_country_code;
}

/*****************************************************************************
 �� �� ��  : hwifi_set_country_code
 ��������  :

 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
void hwifi_set_country_code(int8* country_code, const uint32 len)
{
    if (OAL_PTR_NULL == country_code || len != COUNTRY_CODE_LEN)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "hwifi_get_country_code ptr null or illegal len!");
        return;
    }

    oal_memcopy(g_ac_country_code, country_code, COUNTRY_CODE_LEN);
    g_ac_country_code[2] = '\0';

    return;
}
/*****************************************************************************
 �� �� ��  : hwifi_get_nvram_params
 ��������  :

 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
uint8* hwifi_get_nvram_params(void)
{
    return g_auc_nv_params;
}

/*****************************************************************************
 �� �� ��  : hwifi_atcmd_update_host_nv_params
 ��������  : ������ֻ������AT����:AT^WICALDATA=0,,,,,,���ã���������벻Ҫ���ñ��ӿ�
             ������ֻ������AT����:AT^WICALDATA=0,,,,,,���ã���������벻Ҫ���ñ��ӿ�
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��6��24��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
int32 hwifi_atcmd_update_host_nv_params(void)
{
    int32 l_ret = INI_FAILED;

    oal_memset(g_auc_nv_params, 0x00, sizeof(g_auc_nv_params));

    l_ret = get_cust_conf_string(CUST_MODU_NVRAM, OAL_PTR_NULL, g_auc_nv_params, sizeof(g_auc_nv_params));

    if (INI_FAILED == l_ret || !g_auc_nv_params[0])
    {
        /* �������̱��뷵�سɹ���ʧ���򱾴�У׼ʧ�ܣ���Ӧ���ٰ����������ߣ�ֱ�ӷ���ʧ�� */
        /* ʧ��ԭ�����������ڵ��ò�У����֮ǰд��NV�Ĳ������Ѿ�ʧ�ܵ���NV����Ϊ�� */
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "hwifi_atcmd_update_host_nv_params::read nvram params failed or nv is empty, ret=[%d], nv_param[%u]!!", l_ret, g_auc_nv_params[0]);
        oal_memset(g_auc_nv_params, 0x00, sizeof(g_auc_nv_params));
        return INI_FAILED;
    }

    OAM_WARNING_LOG0(0, OAM_SF_ANY, "hwifi_atcmd_update_host_nv_params::update nvram params succ.");
    return INI_SUCC;
}


/* �������� */
EXPORT_SYMBOL_GPL(g_st_wlan_customize);
EXPORT_SYMBOL_GPL(hwifi_config_init);
EXPORT_SYMBOL_GPL(hwifi_get_mac_addr);
EXPORT_SYMBOL_GPL(hwifi_get_init_value);
EXPORT_SYMBOL_GPL(hwifi_get_country_code);
EXPORT_SYMBOL_GPL(hwifi_get_nvram_params);
EXPORT_SYMBOL_GPL(hwifi_fetch_ori_caldata);
EXPORT_SYMBOL_GPL(hwifi_set_country_code);
EXPORT_SYMBOL_GPL(hwifi_is_regdomain_changed);
EXPORT_SYMBOL_GPL(hwifi_atcmd_update_host_nv_params);

#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

