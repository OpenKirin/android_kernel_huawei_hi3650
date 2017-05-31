/*
 * 
 *
 * Copyright (C) 2013 Huawei Inc.
 */


#ifndef __HISI_COUL_DRV_H
#define __HISI_COUL_DRV_H

#define	BAT_VOL_3500						(3500)
#define	BAT_VOL_3600						(3600)
#define	BAT_VOL_3700						(3700)
#define	BAT_VOL_3800						(3800)
#define	BAT_VOL_3900						(3900)

#define BASP_TAG "[BASP] " /* Battery Aging Safe Policy LOG TAG */
#define VTERM_MAX_DEFAULT_MV (4400)
#define MAX_BATT_CHARGE_CUR_RATIO (7) /* 0.7C */
#define COUL_IC_GOOD 0
#define COUL_IC_BAD   1

enum HISI_COULOMETER_TYPE {
    COUL_HISI = 0,
    COUL_BQ27510,
    COUL_BQ28Z610,
    COUL_UNKNOW,
};
typedef struct AGING_SAFE_POLICY_TAG {
   unsigned int volt_dec;  /* voltage decrease mV */
   unsigned int cur_ratio; /* current discount ratio:cur_ratio/10 */
   unsigned int learned_fcc; /* used as charging current 1C after fcc learned */
}AGING_SAFE_POLICY_TYPE;
typedef enum BASP_LEVEL_TAG {
    BASP_LEVEL_0,
    BASP_LEVEL_1,
    BASP_LEVEL_2,
    BASP_LEVEL_3,
    BASP_LEVEL_CNT
}BASP_LEVEL_TYPE;

struct hisi_coul_ops {
    int (*is_coul_ready)(void);
    int (*is_battery_exist)(void);
    int (*is_battery_reach_threshold)(void);
    char *(*battery_brand)(void);
    int (* battery_id_voltage)(void);
    int (*battery_voltage)(void);
    int (*battery_voltage_uv)(void);
    int (*battery_current)(void);
    int (*battery_current_avg)(void);
    int (*battery_unfiltered_capacity)(void);
    int (*battery_capacity)(void);
    int (*battery_temperature)(void);
	int (*battery_temperature_for_charger)(void);
    int (*battery_rm)(void);
    int (*battery_fcc)(void);
    int (*battery_fcc_design)(void);
    int (*battery_tte)(void);
    int (*battery_ttf)(void);
    int (*battery_health)(void);
    int (*battery_capacity_level)(void);
    int (*battery_technology)(void);
    struct chrg_para_lut *(*battery_charge_params)(void);
    int (*battery_vbat_max)(void);
    int (*charger_event_rcv)(unsigned int);
    int (*battery_cycle_count)(void);
    int (*coul_is_fcc_debounce)(void);
    int (*set_hltherm_flag)(int);
    int (*get_hltherm_flag)(void);
    int (*aging_safe_policy)(AGING_SAFE_POLICY_TYPE *asp);
    int (*aging_safe_level)(void);
    int (*dev_check)(void);
};


extern enum HISI_COULOMETER_TYPE hisi_coulometer_type(void);
extern void hisi_coul_charger_event_rcv(unsigned int event);
extern int is_hisi_coul_ready(void);
extern int is_hisi_battery_exist(void);
extern int is_hisi_battery_reach_threshold(void);
extern int hisi_battery_voltage(void);
extern char* hisi_battery_brand(void);
extern int hisi_battery_id_voltage(void);
extern int hisi_battery_voltage_uv(void);
extern int hisi_battery_current(void);
extern int hisi_battery_current_avg(void);
extern int hisi_battery_unfiltered_capacity(void);
extern int hisi_battery_capacity(void);
extern int hisi_battery_temperature(void);
extern int hisi_battery_rm(void);
extern int hisi_battery_fcc(void);
extern int hisi_battery_fcc_design(void);
extern int hisi_battery_tte(void);
extern int hisi_battery_ttf(void);
extern int hisi_battery_health(void);
extern int hisi_battery_capacity_level(void);
extern int hisi_battery_technology(void);
extern struct chrg_para_lut *hisi_battery_charge_params(void);
extern int hisi_battery_vbat_max(void);
extern int hisi_battery_cycle_count(void);
extern int hisi_coul_ops_register (struct hisi_coul_ops *coul_ops,enum HISI_COULOMETER_TYPE coul_type);
extern int hisi_coul_ops_unregister (struct hisi_coul_ops *coul_ops);
extern int hisi_power_supply_voltage(void);
extern int is_hisi_fcc_debounce(void);
extern int hisi_coul_set_hltherm_flag(int temp_flag);
extern int hisi_coul_get_hltherm_flag(void);
extern int hisi_battery_aging_safe_policy(AGING_SAFE_POLICY_TYPE *asp);
extern BASP_LEVEL_TYPE hisi_battery_aging_safe_level(void);
extern int hisi_battery_temperature_for_charger(void);

#endif
