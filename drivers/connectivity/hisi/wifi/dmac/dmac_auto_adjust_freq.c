/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_auto_adjust_freq.c
  �� �� ��   : ����
  ��    ��   : w00316376
  ��������   : 2015��6��26��
  ����޸�   :
  ��������   :device��Ƶ��غ���ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��26��
    ��    ��   : w00316376
    �޸�����   : �����ļ�
  2.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : Device������Ƶ

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "pm_extern.h"
#include "dmac_psm_sta.h"
#include "dmac_blockack.h"
#endif

#include "frw_ext_if.h"
#include "dmac_auto_adjust_freq.h"
#include "oam_ext_if.h"
#include "dmac_resource.h"
#ifdef _PRE_WLAN_FEATURE_GREEN_AP
#include "dmac_green_ap.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
dmac_pps_statistics_stru g_device_pps_statistics = {0};

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ

/*device��Ƶ����*/
oal_uint16 g_device_speed_freq[][FREQ_BUTT] = {
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},     /*WLAN_BW_20*/
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},    /*WLAN_HT_BW_40*/
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},   /*WLAN_VHT_BW_40*/
    {PM_80MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},   /*WLAN_VHT_BW_80*/
};

/*�ɶ��ƻ����г�ʼ��*/
device_pps_freq_level_stru g_device_ba_pps_freq_level[] = {
    /*pps����                   CPU��Ƶlevel */
    {PPS_VALUE_0,          FREQ_IDLE},
    {PPS_VALUE_1,          FREQ_MIDIUM},
    {PPS_VALUE_2,          FREQ_HIGHER},
    {PPS_VALUE_3,          FREQ_HIGHEST},
};
device_pps_freq_level_stru g_device_no_ba_pps_freq_level[] = {
    /*pps����                   CPU��Ƶlevel */
    {NO_BA_PPS_VALUE_0,    FREQ_IDLE},
    {NO_BA_PPS_VALUE_1,    FREQ_MIDIUM},
    {NO_BA_PPS_VALUE_2,    FREQ_HIGHER},
    {NO_BA_PPS_VALUE_3,    FREQ_HIGHEST},
};

/* device��Ƶ���ƽṹ�� */
dmac_freq_control_stru g_device_freq_type = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
dmac_freq_control_stru* dmac_get_auto_freq_handle(oal_void)
{
    return &g_device_freq_type;
}

device_pps_freq_level_stru* dmac_get_ba_pps_freq_level(oal_void)
{
    return g_device_ba_pps_freq_level;
}
/*****************************************************************************
 �� �� ��  : dmac_get_device_freq_level
 ��������  : ��ȡdevice�ĵ�Ƶ�ȼ�
 �������  : ��
 �������  : device�ĵ�Ƶ����
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 dmac_get_device_freq_level(void)
{
    oal_uint8     uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type = WLAN_BW_20;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_get_device_freq_level::pst_mac_device null.}");
        return uc_auto_freq_bw_type;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_get_device_freq_type pst_mac_vap is null.}");
            continue;
        }
        if ((MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state) &&
            (MAC_VAP_STATE_PAUSE != pst_mac_vap->en_vap_state))
        {
            continue;
        }

        if ((pst_mac_vap->en_protocol != WLAN_VHT_MODE) &&
            (pst_mac_vap->en_protocol != WLAN_VHT_ONLY_MODE))   /*��11ac*/
        {
            if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
            {
                if (uc_auto_freq_bw_type <= WLAN_HT_BW_40)
                {
                    uc_auto_freq_bw_type = WLAN_HT_BW_40;
                }
            }
        }
        else
        {
            if ((WLAN_BAND_WIDTH_20M == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth))
            {
                if (uc_auto_freq_bw_type <= WLAN_VHT_BW_40)
                {
                    uc_auto_freq_bw_type = WLAN_VHT_BW_40;
                }
            }
            else
            {
                uc_auto_freq_bw_type = WLAN_VHT_BW_80;
            }
        }
    }
    return uc_auto_freq_bw_type;
}
/*****************************************************************************
 �� �� ��  : dmac_get_device_freq_value
 ��������  : ��ȡdevice�ĵ�Ƶ����
 �������  : ��
 �������  : oal_device_freq_type_enum_uint8 uc_device_freq_type,device�ĵ�Ƶ����,
             wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type,��ƵƵ������
             oal_uint16* pusdevice_freq_value,device��Ƶֵ
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_get_device_freq_value(oal_device_freq_type_enum_uint8 uc_device_freq_type,wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type,oal_uint16* pusdevice_freq_value)
{
    if (uc_device_freq_type > FREQ_HIGHEST)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_get_device_freq_value:para error,uc_device_freq_type = %d.}",uc_device_freq_type);
        return OAL_FAIL;
    }
    if (uc_auto_freq_bw_type >= WLAN_BW_BUTT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_get_device_freq_value:para error,uc_auto_freq_bw_type = %d.}",uc_auto_freq_bw_type);
        return OAL_FAIL;
    }
    *pusdevice_freq_value = g_device_speed_freq[uc_auto_freq_bw_type][uc_device_freq_type];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_auto_set_device_freq
 ��������  : device�ĵ�Ƶ����
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
oal_void dmac_auto_set_device_freq(oal_void)
{
    wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type = WLAN_BW_20;
    oal_uint16                   us_device_freq = PM_40MHZ;
    oal_uint32                    uc_ret;

    /* ��Ȳ���Ҫ��Ƶ */
    if(g_device_freq_type.uc_curr_freq_level == g_device_freq_type.uc_req_freq_level)
    {
        return;
    }

    uc_auto_freq_bw_type = dmac_get_device_freq_level();
    uc_ret = dmac_get_device_freq_value(g_device_freq_type.uc_req_freq_level, uc_auto_freq_bw_type, &us_device_freq);
    if(OAL_SUCC != uc_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_auto_set_device_freq: get us_device_freq fail[%d].}",us_device_freq);
        return;
    }

    PM_WLAN_SetMaxCpuFreq(us_device_freq);

    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_auto_set_device_freq:change freq to[%d] [%d].}", g_device_freq_type.uc_curr_freq_level, g_device_freq_type.uc_req_freq_level);
    g_device_freq_type.uc_curr_freq_level = g_device_freq_type.uc_req_freq_level;

    if (us_device_freq < PM_80MHZ)
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_IDLE_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_IDLE_CNT;

    }
    else if ((us_device_freq >= PM_80MHZ) && (us_device_freq < PM_160MHZ))
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_MIDIUM_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_MIDIUM_CNT;
    }
    else
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_BUSY_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_BUSY_CNT;
    }

    PM_WLAN_SwitchToState(PM_WPF_ID, (PM_WPF_WK | PM_WLAN_GetMaxCpuFreq()));

}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_netbuf_notify
 ��������  : device����netbufʣ�����ĵ�Ƶ����
 �������  : large netbuf ʣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_auto_freq_netbuf_notify(oal_uint32 ul_free_cnt)
{
    dmac_freq_control_stru   *pst_freq_handle = &g_device_freq_type;

    /* �����ʹ�ܣ������� */
    if(OAL_FALSE == pst_freq_handle->uc_auto_freq_enable)
    {
        return;
    }
    /* ����͹���˯�ߣ������� */
    if(OAL_FALSE == pst_freq_handle->uc_pm_enable)
    {
        return;
    }

    /* ���������ȼ�����ʱ������Ƶ�� */
    if ((ul_free_cnt <= (WLAN_AUTO_FREQ_NETBUF_THRESHOLD + 1)) && (pst_freq_handle->uc_curr_freq_level != FREQ_HIGHEST))
    {
        //OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_auto_freq_netbuf_notify:ul_free_cnt[%d].}", ul_free_cnt);
        pst_freq_handle->uc_req_freq_level = FREQ_HIGHEST;
        dmac_auto_set_device_freq();
    }
}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_set_pps_level
 ��������  : device���������ʻ�ȡ��Ӧ��cpu��Ƶlevel
 �������  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_auto_freq_set_pps_level(oal_uint32 ul_pps_rate)
{
    dmac_freq_control_stru   *pst_freq_handle = &g_device_freq_type;
    oal_uint8 level_idx = 0;

    if(dmac_is_ba_setup())/* �Ѿ�����BA */
    {
        if (ul_pps_rate <= g_device_ba_pps_freq_level[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_pps_rate > g_device_ba_pps_freq_level[1].ul_speed_level)
            && (ul_pps_rate <= g_device_ba_pps_freq_level[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_pps_rate > g_device_ba_pps_freq_level[2].ul_speed_level)
            && (ul_pps_rate <= g_device_ba_pps_freq_level[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }

        pst_freq_handle->uc_req_freq_level = (oal_uint8)g_device_ba_pps_freq_level[level_idx].ul_cpu_freq_level;
    }
    else
    {
        if (ul_pps_rate <= g_device_no_ba_pps_freq_level[1].ul_speed_level)
        {
            level_idx = 0;
        }
        else if ((ul_pps_rate > g_device_no_ba_pps_freq_level[1].ul_speed_level)
            && (ul_pps_rate <= g_device_no_ba_pps_freq_level[2].ul_speed_level))
        {
            level_idx = 1;
        }
        else if ((ul_pps_rate > g_device_no_ba_pps_freq_level[2].ul_speed_level)
            && (ul_pps_rate <= g_device_no_ba_pps_freq_level[3].ul_speed_level))
        {
            level_idx = 2;
        }
        else
        {
            level_idx = 3;
        }

        pst_freq_handle->uc_req_freq_level = (oal_uint8)g_device_no_ba_pps_freq_level[level_idx].ul_cpu_freq_level;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_pps_process
 ��������  : device�����������ж��Ƿ���Ҫ��Ƶ
 �������  : ��ʱ�������ڵ��շ�֡����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_auto_freq_pps_process(oal_uint32 ul_pkt_count)
{
    dmac_freq_control_stru   *pst_freq_handle = &g_device_freq_type;

    if (pst_freq_handle->uc_req_freq_level != pst_freq_handle->uc_curr_freq_level)
    {
        if(pst_freq_handle->uc_req_freq_level < pst_freq_handle->uc_curr_freq_level)
        {
            /*����MAX_DEGRADE_FREQ_TIME_THRESHOLD��Ž�Ƶ����֤����*/
            pst_freq_handle->ul_pps_loop_count++;
            if(0 != ul_pkt_count)
            {
                if(pst_freq_handle->ul_pps_loop_count >= WLAN_AUTO_FREQ_DATA_LOOP_THRESHOLD)
                {
                    pst_freq_handle->ul_pps_loop_count = 0;
                    dmac_auto_set_device_freq();
                }
            }
            else
            {
                if(pst_freq_handle->ul_pps_loop_count >= WLAN_AUTO_FREQ_NO_DATA_LOOP_THRESHOLD)
                {
                    pst_freq_handle->ul_pps_loop_count = 0;
                    dmac_auto_set_device_freq();
                }
            }
        }
        else
        {
            /*��Ƶ���ȴ�������ִ�б�֤����*/
            pst_freq_handle->ul_pps_loop_count = 0;

            /* ����Ҫ��Ƶʱ��һ����burst�����Ƶ;Ȼ���ٸ��������µ�Ƶ�� */
            if(FREQ_HIGHEST != pst_freq_handle->uc_curr_freq_level)
            {
                pst_freq_handle->uc_req_freq_level = FREQ_HIGHEST;
            }

            dmac_auto_set_device_freq();
        }
    }
    else
    {
        pst_freq_handle->ul_pps_loop_count = 0;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_pps_timeout
 ��������  : device��Ƶ���ܳ�ʼ������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_init(oal_void)
{
    dmac_freq_control_stru   *pst_freq_handle = &g_device_freq_type;
    dmac_pps_statistics_stru *pst_pps_handle = &g_device_pps_statistics;
    frw_timeout_stru         *pst_timer = &pst_pps_handle->timer;

    pst_freq_handle->uc_auto_freq_enable = OAL_TRUE;
    pst_freq_handle->uc_pm_enable = OAL_FALSE;
    pst_freq_handle->uc_curr_freq_level = FREQ_HIGHEST;
    pst_freq_handle->uc_req_freq_level = FREQ_IDLE; /* Ĭ�ϴ�����͹���Ƶ�� */
    pst_freq_handle->ul_pps_loop_count = 0;

    pst_pps_handle->ul_pps_rate = 0;
    pst_pps_handle->ul_last_timeout = 0;
    pst_pps_handle->ul_hcc_rxtx_total = 0;

    /* ��ʼ��Ϊlevel0 */
    dmac_auto_set_device_freq();

    if(OAL_FALSE == pst_timer->en_is_registerd)
    {
        FRW_TIMER_CREATE_TIMER(pst_timer,
                           dmac_auto_freq_pps_timeout,
                           WLAN_AUTO_FREQ_THROUGHPUT_TIMEOUT,
                           OAL_PTR_NULL,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           0);

       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_set_auto_freq_init: timer start.}");
    }

    g_device_pps_statistics.uc_timer_reuse_count++;
}

/*****************************************************************************
 �� �� ��  : dmac_set_auto_freq_deinit
 ��������  : device��Ƶ����ȥ��ʼ������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_deinit(oal_void)
{
    frw_timeout_stru  *pst_timer = &g_device_pps_statistics.timer;

    g_device_freq_type.uc_auto_freq_enable = OAL_FALSE;

    if(OAL_TRUE == pst_timer->en_is_registerd)
    {
        g_device_pps_statistics.uc_timer_reuse_count --;

        /* ������˳���ģ��ɾ����ʱ�� */
        if (0 == g_device_pps_statistics.uc_timer_reuse_count)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_timer);
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_set_auto_freq_init: timer exit.}");
        }
    }

}

/*****************************************************************************
 �� �� ��  : dmac_set_auto_freq_exit
 ��������  : device��Ƶ����ȥ��ʼ������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_exit(oal_void)
{
    dmac_set_auto_freq_deinit();

   g_device_freq_type.uc_req_freq_level = FREQ_IDLE;
   dmac_auto_set_device_freq();
}

/*****************************************************************************
 �� �� ��  : dmac_auto_freq_pps_timeout
 ��������  : device��Ƶע�ṳ�Ӻ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_process_func(oal_void)
{
    struct oal_process_func_handler    *pst_func_handle;

    pst_func_handle = oal_get_device_auto_freq_handle();
    pst_func_handle->p_auto_freq_judge_func = dmac_auto_freq_netbuf_notify;
}

#endif /* end of _PRE_WLAN_FEATURE_AUTO_FREQ */


/*****************************************************************************
 �� �� ��  : dmac_auto_freq_pps_timeout
 ��������  : device��Ƶ������ͳ�ƶ�ʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_auto_freq_pps_timeout(void *prg)
{
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    dmac_freq_control_stru   *pst_freq_handle = &g_device_freq_type;
#endif
    dmac_pps_statistics_stru *pst_pps_handle = &g_device_pps_statistics;
    oal_uint32                ul_cur_time = 0;
    oal_uint32                ul_return_total_count = 0;

    ul_return_total_count = pst_pps_handle->ul_hcc_rxtx_total;

    ul_cur_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    if (ul_cur_time > pst_pps_handle->ul_last_timeout)
    {
        pst_pps_handle->ul_pps_rate = (ul_return_total_count << 10) / (ul_cur_time - pst_pps_handle->ul_last_timeout);

        //OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_auto_freq_pps_timeout:DATA RATE [%d].,time[%d]}",
        //          pst_pps_handle->ul_pps_rate, (ul_cur_time - pst_pps_handle->ul_last_timeout));
    }

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if (OAL_TRUE == pst_freq_handle->uc_auto_freq_enable)
    {
        /* ������������ȡ��Ƶ���� */
        dmac_auto_freq_set_pps_level(pst_pps_handle->ul_pps_rate);

        dmac_auto_freq_pps_process(ul_return_total_count);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    /* green ap������ */
    dmac_green_ap_pps_process(pst_pps_handle->ul_pps_rate);
#endif

    pst_pps_handle->ul_hcc_rxtx_total = 0;

    pst_pps_handle->ul_last_timeout = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_set_auto_freq_pps_reuse
 ��������  : ����Device��������PPSͳ�ƽӿ�(����timer,����ģ�����)
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_pps_reuse(oal_void)
{
    frw_timeout_stru         *pst_timer = &g_device_pps_statistics.timer;

    if(OAL_FALSE == pst_timer->en_is_registerd)
    {
        FRW_TIMER_CREATE_TIMER(pst_timer,
                           dmac_auto_freq_pps_timeout,
                           WLAN_AUTO_FREQ_THROUGHPUT_TIMEOUT,
                           OAL_PTR_NULL,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           0);

       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_set_auto_freq_pps_reuse: timer start.}");
    }

    g_device_pps_statistics.uc_timer_reuse_count ++;
}
/*****************************************************************************
 �� �� ��  : dmac_set_auto_freq_pps_reuse_deinit
 ��������  : ����Device��������PPSֹͣͳ�ƽӿ�(ע��timer,����ģ�����)
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_set_auto_freq_pps_reuse_deinit(oal_void)
{
    frw_timeout_stru         *pst_timer = &g_device_pps_statistics.timer;

    if(OAL_TRUE == pst_timer->en_is_registerd)
    {
        g_device_pps_statistics.uc_timer_reuse_count --;

        /* ������˳���ģ��ɾ����ʱ�� */
        if (0 == g_device_pps_statistics.uc_timer_reuse_count)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_timer);

            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_set_auto_freq_pps_reuse_deinit: timer exit.}");
        }
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


