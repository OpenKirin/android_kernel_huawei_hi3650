/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_user_track.c
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��7��2��
  ����޸�   :
  ��������   : ���û�������غ���ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oam_ext_if.h"

#include "wlan_spec.h"

#include "mac_vap.h"
#include "mac_device.h"

#include "dmac_user_track.h"
#include "dmac_alg_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_USER_TRACK_C

/*****************************************************************************
  2 ����ԭ������
*****************************************************************************/

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_user_track_thrput_timeout
 ��������  : �ϱ��û�ʵʱ���²�����ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_track_thrput_timeout(oal_void *p_arg)
{
    oam_user_track_thrput_param_stru   st_user_track_phrput_param;
    dmac_best_rate_stat_info_stru      st_best_rate_stat_info;
    mac_device_stru                   *pst_macdev = OAL_PTR_NULL;
    mac_user_stru                     *pst_mac_user;
    oal_uint16                         us_rx_ampdu_num;
    oal_uint32                         ul_rx_mpdu_in_ampdu;

    OAL_MEMZERO(&st_user_track_phrput_param, OAL_SIZEOF(oam_user_track_thrput_param_stru));
    OAL_MEMZERO(&st_best_rate_stat_info, OAL_SIZEOF(dmac_best_rate_stat_info_stru));

    pst_mac_user = (mac_user_stru *)p_arg;

    pst_macdev = mac_res_get_dev(pst_mac_user->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_track_thrput_timeout:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���㷨��ȡ���ֲ��� */
    dmac_alg_get_rssi(pst_mac_user,
                      &st_user_track_phrput_param.c_avg_tx_rssi,
                      &st_user_track_phrput_param.c_avg_rx_rssi);

    dmac_alg_get_rate(pst_mac_user,
                      &st_user_track_phrput_param.ul_avg_tx_rate,
                      &st_user_track_phrput_param.ul_avg_rx_rate);

    dmac_alg_get_best_rate(pst_mac_user, &st_best_rate_stat_info);
    oal_memcopy(st_user_track_phrput_param.ast_best_rate_stat,
                st_best_rate_stat_info.ast_best_rate_stat,
                OAL_SIZEOF(dmac_best_rate_stat_info_stru));

    /* ��ȡ����ƽ���ۺϳ��ȣ�device���� */
    if (OAL_PTR_NULL != pst_macdev->pst_device_stru)
    {
        us_rx_ampdu_num = pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.us_rx_ampdu_num;
        ul_rx_mpdu_in_ampdu = pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.ul_rx_mpdu_in_ampdu;
        if (0 != us_rx_ampdu_num)
        {
            st_user_track_phrput_param.us_avg_rx_aggr_num = (oal_uint16)ul_rx_mpdu_in_ampdu / us_rx_ampdu_num;
        }

        /* ����ͳ�� */
        pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.us_rx_ampdu_num = 0;
        pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.ul_rx_mpdu_in_ampdu = 0;
    }

    return oam_report_dft_params(pst_mac_user->auc_user_mac_addr,
                                 (oal_uint8 *)&st_user_track_phrput_param,
                                 (oal_uint16)OAL_SIZEOF(oam_user_track_thrput_param_stru),
                                 OAM_OTA_TYPE_USER_THRPUT_PARAM);
}


/*****************************************************************************
 �� �� ��  : dmac_dft_report_usr_thrput_stat
 ��������  : �ϱ�Ӱ���û�ʵʱ���µ�ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_track_report_usr_thrput_stat(mac_user_stru  *pst_mac_user)
{
    mac_device_stru  *pst_macdev    = OAL_PTR_NULL;
    dmac_user_stru   *pst_dmac_user = (dmac_user_stru *)pst_mac_user;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_track_report_usr_thrput_stat:: user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_macdev = mac_res_get_dev(pst_mac_user->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_track_report_usr_thrput_stat:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ֪ͨ�㷨��ʼͳ�� */
    dmac_alg_start_stat_rssi(pst_mac_user);
    dmac_alg_start_stat_rate(pst_mac_user);
    dmac_alg_start_stat_best_rate(pst_mac_user);

    /* ��ͳ�ƽ���ƽ���ۺϳ��ȿ��� */
    pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.en_flg = OAL_TRUE;

    /* ������ʱ������ʱ��ȡ�㷨ͳ��ֵ */
    FRW_TIMER_CREATE_TIMER(&pst_dmac_user->st_user_track_ctx.st_txrx_param_timer,
                           dmac_user_track_thrput_timeout,
                           DMAC_USER_TRACK_REPORT_PARAM_PERIOD,
                           (oal_void *)pst_mac_user,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_macdev->ul_core_id);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_clear_usr_thrput_stat
 ��������  : ֹͣ�ϱ�Ӱ���û�ʵʱ���µ�ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_user_track_clear_usr_thrput_stat(mac_user_stru  *pst_mac_user)
{
    mac_device_stru       *pst_macdev    = OAL_PTR_NULL;
    dmac_user_stru        *pst_dmac_user = (dmac_user_stru *)pst_mac_user;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_track_report_usr_thrput_stat:: user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_macdev = mac_res_get_dev(pst_mac_user->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_track_clear_usr_thrput_stat:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ɾ����ʱ����ͬʱ֪ͨ�㷨ֹͣͳ�� */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_dmac_user->st_user_track_ctx.st_txrx_param_timer);

    dmac_alg_stop_stat_rssi(pst_mac_user);
    dmac_alg_stop_stat_rate(pst_mac_user);
    dmac_alg_stop_stat_best_rate(pst_mac_user);
    pst_macdev->pst_device_stru->st_user_track_rx_ampdu_stat.en_flg = OAL_FALSE;

    return OAL_SUCC;
}


#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

