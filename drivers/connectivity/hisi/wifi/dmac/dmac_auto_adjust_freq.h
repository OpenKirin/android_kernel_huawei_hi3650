/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_auto_adjust_freq.h
  �� �� ��   : ����
  ��    ��   : w00316376
  ��������   : 2015��6��26��
  ����޸�   :
  ��������   : device��Ƶ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��26��
    ��    ��   : w00316376
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_AUTO_ADJUST_FREQ_H__
#define __DMAC_AUTO_ADJUST_FREQ_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_H

/* ����1151��1102�ȵ�pps/����ͳ�Ƹ��ã�����AUTO_FREQ������ */
#define WLAN_AUTO_FREQ_THROUGHPUT_TIMEOUT     100   /* ������ͳ�ƶ�ʱ������ */

/* ppsͳ�ƽṹ�� */
typedef struct {
    oal_uint32             ul_last_timeout;
    oal_uint32             ul_pps_rate;
    oal_uint32             ul_hcc_rxtx_total;    /* hcc slave �շ�����֡ͳ�� */
    oal_uint8              uc_timer_reuse_count; /* ���ô˶�ʱ����ģ����� */
    oal_uint8              resv[3];

    frw_timeout_stru       timer;
} dmac_pps_statistics_stru;

extern dmac_pps_statistics_stru g_device_pps_statistics;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WLAN_AUTO_FREQ_NETBUF_THRESHOLD       OAL_NETBUF_HIGH_PRIORITY_COUNT    /* ��netbufʣ�ൽ������ȼ�����ˮ�ߣ��������Ƶ���� */
//#define WLAN_AUTO_FREQ_NETBUF_CNT             5     /* ��netbuf����������ֵ��������deviceƵ�ʵ���� */

#define WLAN_AUTO_FREQ_DATA_LOOP_THRESHOLD    50    /*�а�ʱ����50�����ڶ���Ҫ��Ƶ�Ž�Ƶ*/
#define WLAN_AUTO_FREQ_NO_DATA_LOOP_THRESHOLD 3     /*û�а�ʱ����2�����ڶ���Ҫ��Ƶ�Ž�Ƶ*/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    WLAN_BW_20,
    WLAN_HT_BW_40,
    WLAN_VHT_BW_40,
    WLAN_VHT_BW_80,
    WLAN_BW_BUTT
}wlan_auto_freq_bw_enum;
typedef oal_uint8 wlan_auto_freq_bw_enum_uint8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint16 g_device_speed_freq[][FREQ_BUTT];

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct {
    oal_bool_enum_uint8              uc_auto_freq_enable;  /*ʹ�ܿ���*/
    oal_bool_enum_uint8              uc_pm_enable;  /*�͹���״̬��־*/
    oal_device_freq_type_enum_uint8  uc_curr_freq_level;  /*��ǰ����Ƶ�ʼ���*/
    oal_device_freq_type_enum_uint8  uc_req_freq_level;   /*����netbuf�ж���Ҫ��Ƶ�ʼ���*/

    oal_uint32                       ul_pps_loop_count;

    /* netbuf ͳ����� *//* ������ʣ��151�� */
    //oal_uint32             ul_netbuf_loop_count;

} dmac_freq_control_stru;

typedef struct {
    oal_uint32  ul_speed_level;    /*����������*/
    oal_uint32  ul_cpu_freq_level;  /*CPU��Ƶ����*/
} device_pps_freq_level_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void dmac_auto_set_device_freq(oal_void);
extern oal_void dmac_auto_freq_netbuf_notify(oal_uint32 ul_free_cnt);
extern oal_void dmac_set_auto_freq_process_func(oal_void);
extern oal_void dmac_set_auto_freq_init(oal_void);
extern oal_void dmac_set_auto_freq_deinit(oal_void);
extern oal_void dmac_set_auto_freq_exit(oal_void);
extern dmac_freq_control_stru* dmac_get_auto_freq_handle(oal_void);
extern device_pps_freq_level_stru* dmac_get_ba_pps_freq_level(oal_void);

#endif /* end of _PRE_WLAN_FEATURE_AUTO_FREQ */


/* ����1151��1102�ȵ�pps/����ͳ�Ƹ��ã�����AUTO_FREQ������ */
extern oal_uint32 dmac_auto_freq_pps_timeout(void *prg);
extern oal_void dmac_set_auto_freq_pps_reuse_deinit(oal_void);
extern oal_void dmac_set_auto_freq_pps_reuse(oal_void);

/*****************************************************************************
 �� �� ��  : dmac_get_pps_statistics_handle
 ��������  : ��ȡppsͳ�ƽṹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE  dmac_pps_statistics_stru* dmac_get_pps_statistics_handle(oal_void)
{
    return &g_device_pps_statistics;
}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_pps_count
 ��������  : deviceͳ��device�շ�����֡����
 �������  : ֡����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_auto_freq_pps_count(oal_uint32 pkt_cnt)
{
    g_device_pps_statistics.ul_hcc_rxtx_total += pkt_cnt;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_auto_adjust_freq.h */
