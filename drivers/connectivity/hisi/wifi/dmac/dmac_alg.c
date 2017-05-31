/******************************************************************************

                  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_alg.c
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2013��3��21��
  ����޸�   :
  ��������   : �㷨��̿��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��21��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "dmac_alg.h"
#include "dmac_config.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ALG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* �㷨������ṹ�� */
dmac_alg_stru  gst_alg_main;

/* �㷨�������� */
dmac_alg_config_table_stru g_ast_dmac_alg_config_table[] =
{
#ifdef _PRE_WLAN_FEATURE_DBAC
    {"dbac",        DMAC_ALG_CONFIG_ID_DBAC},
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    {"sch",         DMAC_ALG_CONFIG_ID_SCH},
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    {"tfctl",      DMAC_ALG_CONFIG_ID_TRAFF_CTL},
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    {"txbf",        DMAC_ALG_CONFIG_ID_TXBF},
    {"test",        DMAC_ALG_CONFIG_ID_TEST_MAIN},
    {"dbac_ct",     DMAC_ALG_CONFIG_ID_DBAC_TEST},
    {"ar_test",     DMAC_ALG_CONFIG_ID_AUTORATE_TEST},
    {"ant_test",    DMAC_ALG_CONFIG_ID_SMARTANT_TEST},
    {"rssi_test",   DMAC_ALG_CONFIG_ID_RSSI_TEST},
    {"tpc_test",    DMAC_ALG_CONFIG_ID_TPC_TEST},
#endif

    {"cmn",         DMAC_ALG_CONFIG_ID_COMMON},
    {"err_name",    DMAC_ALG_CONFIG_ID_ERROR}
};

#ifdef _PRE_WLAN_FEATURE_DBAC
extern frw_event_sub_table_item_stru g_ast_dmac_misc_event_sub_table[];
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
oal_uint32 gul_dmac_alg_pktno = 0;
#else
oal_uint8 guc_dmac_alg_pktno = 0;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_alg_free_tid_priv_stru
 ��������  : �ͷ�user�µ�tid˽�����ݽṹ
 �������  : pst_user: �û��ṹ��;
 �������  : ul_output ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_alg_free_tid_priv_stru(dmac_user_stru *pst_user)
{
    oal_uint8   uc_index;

    for (uc_index = 0; uc_index < WLAN_TID_MAX_NUM; uc_index++)
    {
        if (OAL_PTR_NULL == pst_user->ast_tx_tid_queue[uc_index].p_alg_priv)
        {
            break;
        }

        OAL_MEM_FREE(pst_user->ast_tx_tid_queue[uc_index].p_alg_priv, OAL_TRUE);

        pst_user->ast_tx_tid_queue[uc_index].p_alg_priv = OAL_PTR_NULL;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tx_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_notify_func(dmac_alg_tx_notify_enum_uint8    en_notify_sub_type,
                                                      p_alg_tx_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_tx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tx_complete_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8    en_notify_sub_type,
                                                                  p_alg_tx_complete_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_tx_complete_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_rx_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_rx_notify_func(dmac_alg_rx_notify_enum_uint8    en_notify_sub_type,
                                                      p_alg_rx_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_rx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tx_schedule_func
 ��������  : ע����Ⱥ���
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_schedule_func(p_alg_tx_schedule_func  p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tx_schedule_func = p_func;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 �� �� ��  : dmac_alg_register_tx_schedule_stat_event_notify_func
 ��������  : ע��ͳ���û���Ϣ���޸ĵ��Ȳ�������
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : kongheng 00347307
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_schedule_stat_event_notify_func(p_alg_tx_schedule_stat_event_notify_func  p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tx_schedule_stat_event_notify_func = p_func;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tid_update_notify_func
 ��������  : ע����Ⱥ���
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tid_update_notify_func(p_alg_update_tid_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tid_update_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tid_update_notify_func
 ��������  : ע����Ⱥ���
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_downlink_flowctl_notify_func(p_alg_downlink_flowctl_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_downlink_flowctl_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_add_vap_notify_func
 ��������  : ���㷨ע�ᴴ��VAP�ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8    en_notify_sub_type,
                                                          p_alg_create_vap_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_VAP_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_create_vap_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_del_vap_notify_func
 ��������  : ���㷨ע�ᴴ��VAP�ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8   en_notify_sub_type,
                                                          p_alg_delete_vap_notify_func       p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_VAP_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_delete_vap_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_channel_notify_func
 ��������  : ���㷨ע�������ŵ��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8  en_notify_sub_type,
                                                            p_alg_cfg_channel_notify_func      p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_channel_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_start_connect_notify_func
 ��������  : ���㷨ע�������ŵ��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_start_connect_notify_func(dmac_alg_cfg_start_connect_notify_enum_uint8  en_notify_sub_type,
                                                                            p_alg_cfg_start_connect_notify_func     p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_cfg_start_connect_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_btcoex_state_notify_func
 ��������  : ���㷨ע�������ŵ��ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8  en_notify_sub_type,
                                                                            p_alg_cfg_btcoex_state_notify_func     p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_cfg_btcoex_state_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32 dmac_alg_register_cfg_dual_antenna_state_notify_func(p_alg_cfg_dual_antenna_state_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_cfg_dual_antenna_state_notify_func = p_func;
    return OAL_SUCC;
}
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_bandwidth_notify_func
 ��������  : ���㷨ע������VAP����ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8    en_notify_sub_type,
                                                               p_alg_cfg_bandwidth_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_bandwidth_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_user_bandwidth_notify_func
 ��������  : ���㷨ע������USER����ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_bandwidth_notify_func(
                dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type,
                p_alg_cfg_user_bandwidth_notify_func          p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_bandwidth_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_user_ant_changed_notify_func
 ��������  : ���㷨ע���л�user���߻ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : libani
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_ant_changed_notify_func(
                dmac_alg_cfg_user_ant_changed_notify_enum_uint8 en_notify_sub_type,
                p_alg_cfg_user_ant_changed_notify_func          p_func)
{
    if (OAL_UNLIKELY((en_notify_sub_type >= DMAC_ALG_CFG_USER_ANT_CHANGED_NOTIFY_BUTT) || (OAL_PTR_NULL == p_func)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "en_notify_sub_type >= DMAC_ALG_CFG_ANT_CHANGED_NOTIFY_BUTT or p_func == OAL_PTR_NULL");
        return OAL_FAIL;
    }

    gst_alg_main.pa_cfg_user_ant_changed_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32  dmac_alg_register_cfg_get_ant_info_notify_func(
                p_alg_get_ant_info_notify_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_cfg_get_ant_info_notify_func = p_func;
    return OAL_SUCC;
}
oal_uint32  dmac_alg_register_cfg_double_ant_switch_notify_func(
                p_alg_double_ant_switch_notify_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_cfg_double_ant_switch_notify_func = p_func;
    return OAL_SUCC;
}
#endif

oal_uint32  dmac_alg_register_get_mgmt_tx_pow_notify_func(
                p_alg_get_mgmt_tx_pow_notify_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_mgmt_tx_pow_notify_func = p_func;
    return OAL_SUCC;
}
oal_uint32  dmac_alg_unregister_get_mgmt_tx_pow_notify_func(oal_void)
{
    gst_alg_main.p_get_mgmt_tx_pow_notify_func = OAL_PTR_NULL;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_user_protocol_notify_func
 ��������  : ���㷨ע������USERЭ��ģʽ�ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��19��
    ��    ��   : liwenjun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8 en_notify_sub_type,
                                                               p_alg_cfg_user_protocol_notify_func        p_func)

{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_protocol_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_user_spatial_stream_notify_func
 ��������  : ���㷨ע������USER�ռ����ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_spatial_stream_notify_func(
                dmac_alg_cfg_user_spatial_stream_notify_enum_uint8  en_notify_sub_type,
                p_alg_cfg_user_spatial_stream_notify_func          p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_spatial_stream_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_add_user_notify_func
 ��������  : ���㷨ע����ӹ����û��Ļص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_add_user_notify_func(
                dmac_alg_add_user_notify_enum_uint8     en_notify_sub_type,
                p_alg_add_assoc_user_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_USER_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_add_assoc_user_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_add_user_notify_func
 ��������  : ���㷨ע����ӹ����û��Ļص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8   en_notify_sub_type,
                                                                    p_alg_delete_assoc_user_notify_func       p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_USER_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_delete_assoc_user_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_rx_mgmt_notify_func
 ��������  : ע��txbf/�������㷨�����жԽ��չ���֡������
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��22��
    ��    ��   : wanran
    �޸�����   : �����㷨ID�������㷨ģ��ͨ��

*****************************************************************************/
oal_uint32  dmac_alg_register_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type, p_alg_rx_mgmt_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_MGMT_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.p_rx_mgmt_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_register_config_notify_func
 ��������  : ע���㷨���������
 �������  : dmac_alg_config_id_enum_uint8 en_notify_sub_type
             p_alg_config_func p_func
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type, p_alg_config_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CONFIG_ID_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_config_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_config_notify_func
 ��������  : ע���㷨��������Ӻ���
 �������  : dmac_alg_config_id_enum_uint8 en_notify_sub_type
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CONFIG_ID_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_config_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 �� �� ��  : dmac_alg_register_dmac_misc_event
 ��������  : ע��DMAC MISC�¼����Ӻ���
 �������  : hal_dmac_misc_sub_type_enum en_event_type
             oal_uint32 (*p_func)(frw_event_mem_stru *)
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    ALG_ASSERT_RET(en_event_type < HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT && NULL != p_func, OAL_FAIL);
    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_dmac_misc_event
 ��������  : ע��DMAC MISC�¼����Ӻ���
 �������  : hal_dmac_misc_sub_type_enum en_event_type
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    ALG_ASSERT_RET(en_event_type < HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT, OAL_FAIL);
    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_enqueue_tid_notify_func
 ��������  : ������tid���лص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
             p_func  : ע��ĺ���
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_enqueue_tid_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ENQUEUE_TID_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_enqueue_tid_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_enqueue_tid_notify_func
 ��������  : ������tid���лص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ENQUEUE_TID_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_enqueue_tid_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_vap_down_notify_func
 ��������  : vap down�ص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
             p_func  : ע��ĺ���
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_down_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_DOWN_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_vap_down_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_vap_down_notify_func
 ��������  : vap down�ص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_DOWN_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_vap_down_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_probe_req_rx_notify_func
 ��������  : �յ�probe reqʱ�Ĺ��Ӻ���
 �������  : en_notify_sub_type : ֪ͨ����
             p_func  : ע��ĺ���
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��1��
    ��    ��   : gaolin 196511
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_alg_register_probe_req_rx_notify_func(dmac_alg_probe_req_rx_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_probe_req_rx_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_PROBE_REQ_RX_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_probe_req_rx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_probe_req_rx_notify_func
 ��������  : �յ�probe reqʱ�Ĺ��Ӻ���
 �������  : en_notify_sub_type : ֪ͨ����
             p_func  : ע��ĺ���
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��1��
    ��    ��   : gaolin 196511
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  dmac_alg_unregister_probe_req_rx_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_PROBE_REQ_RX_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_probe_req_rx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_dbac_fakeq_id_func
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��9��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_dbac_fakeq_id_func(p_alg_get_dbac_fakeq_id_func p_func)
{
    gst_alg_main.p_get_dbac_fakeq_id_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_update_dbac_fcs_config_func
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��9��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_update_dbac_fcs_config_func(p_alg_update_dbac_config_func p_func)
{
    gst_alg_main.p_update_dbac_fcs_config_func = p_func;

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_register_vap_up_notify_func
 ��������  : vap up�ص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
             p_func  : ע��ĺ���
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_up_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_UP_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_vap_up_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_vap_up_notify_func
 ��������  : vap up�ص�����ע��
 �������  : en_notify_sub_type : ֪ͨ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_UP_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_vap_up_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}


#ifdef _PRE_WLAN_CHIP_TEST_ALG
/*****************************************************************************
 �� �� ��  : dmac_alg_register_rx_event_notify
 ��������  : ע��Խ���WLAN�����¼�֪ͨ�Ĵ�����
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : liwenjun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_alg_register_rx_event_notify(p_alg_rx_event_notify_func p_func)
{
    gst_alg_main.p_rx_event_notify_func = p_func;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_rx_event_notify
 ��������  : ע��Խ���WLAN�����¼�֪ͨ�Ĵ�����
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : liwenjun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_alg_unregister_rx_event_notify(oal_void)
{
    gst_alg_main.p_rx_event_notify_func = OAL_PTR_NULL;
}

#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

/*****************************************************************************
 �� �� ��  : dmac_alg_register_flowctl_backp_notify_func
 ��������  : ע���������Ƶķ�ѹ����
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_flowctl_backp_notify_func(p_alg_flowctl_backp_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_alg_flowctl_backp_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_flowctl_backp_notify_func
 ��������  : ע���������Ƶķ�ѹ����
 �������  : en_notify_sub_type : ֪ͨ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_flowctl_backp_notify_func()
{
    gst_alg_main.p_alg_flowctl_backp_func = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_flowctl_backp
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_flowctl_backp(mac_vap_stru *pst_mac_vap, oal_uint16 us_assoc_id, oal_uint8 uc_tidno, oal_uint8 uc_is_stop)
{
    frw_event_mem_stru          *pst_event_mem;          /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru              *pst_dmac_to_hmac_event;  /* ָ�������¼���payloadָ�� */
    mac_ioctl_queue_backp_stru  *pst_flowctl_backp_event;
    oal_uint32                   ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_ioctl_queue_backp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_flowctl_backp::alloc event failed!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP,
                       OAL_SIZEOF(mac_ioctl_queue_backp_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_flowctl_backp_event = (mac_ioctl_queue_backp_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_flowctl_backp_event->uc_vap_id      = pst_mac_vap->uc_vap_id;
    pst_flowctl_backp_event->us_assoc_id    = us_assoc_id;
    pst_flowctl_backp_event->uc_tidno       = uc_tidno;
    pst_flowctl_backp_event->uc_is_stop     = uc_is_stop;

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_flowctl_backp::frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
        return ul_ret;
    }

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_register_txbf_rx_cntl_notify_func
 ��������  : ע��txbf�����жԽ��տ���֡������
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_txbf_rx_cntl_notify_func(p_alg_txbf_rx_cntl_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_txbf_rx_cntl_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tx_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_notify_func(dmac_alg_tx_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_tx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tx_complete_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8  en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_tx_complete_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_rx_notify_func
 ��������  : ���㷨ע��ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_rx_notify_func(dmac_alg_rx_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_rx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tx_schedule_func
 ��������  : ע����Ⱥ���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_schedule_func(oal_void)
{
    gst_alg_main.p_tx_schedule_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 �� �� ��  : dmac_alg_register_tx_schedule_stat_event_notify_func
 ��������  : ע��ע��ͳ���û���Ϣ���޸ĵ��Ȳ�������
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : kongheng 00347307
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_schedule_stat_event_notify_func(oal_void)
{

    gst_alg_main.p_tx_schedule_stat_event_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tid_update_notify_func
 ��������  : ע����Ⱥ���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tid_update_notify_func(oal_void)
{
    gst_alg_main.p_tid_update_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tid_update_notify_func
 ��������  : ע����Ⱥ���
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_downlink_flowctl_notify_func(oal_void)
{
    gst_alg_main.p_downlink_flowctl_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_add_vap_notify_func
 ��������  : ���㷨ע�ᴴ��VAP�ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8  en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_VAP_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_create_vap_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_start_connect_notify_func
 ��������  : ����ʼ������Ϣ֪ͨ
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��17��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_start_connect_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_start_connect_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_btcoex_state_notify_func
 ��������  : ����ʼ������Ϣ֪ͨ
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : c0021210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_btcoex_state_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32 dmac_alg_unregister_cfg_dual_antenna_state_notify_func()
{
    gst_alg_main.p_cfg_dual_antenna_state_notify_func = OAL_PTR_NULL;
    return OAL_SUCC;
}
#endif
#endif /*_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_channel_notify_func
 ��������  : ���㷨ע�������ŵ��ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_channel_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_bandwidth_notify_func
 ��������  : ���㷨ע�����ô���ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_bandwidth_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_user_bandwidth_notify_func
 ��������  : ���㷨ȥע������USER����ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_bandwidth_notify_func(dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_user_bandwidth_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_user_ant_changed_notify_func
 ��������  : ���㷨ȥע���л�user���߻ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : libani
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_ant_changed_notify_func(dmac_alg_cfg_user_ant_changed_notify_enum_uint8 en_notify_sub_type)
{
    if (OAL_UNLIKELY(en_notify_sub_type >= DMAC_ALG_CFG_USER_ANT_CHANGED_NOTIFY_BUTT))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "en_notify_sub_type >= DMAC_ALG_CFG_ANT_CHANGED_NOTIFY_BUTT");
        return OAL_FAIL;
    }

    gst_alg_main.pa_cfg_user_ant_changed_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32  dmac_alg_unregister_cfg_get_ant_info_notify_func(oal_void)
{
    gst_alg_main.p_cfg_get_ant_info_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
oal_uint32  dmac_alg_unregister_cfg_double_ant_switch_notify_func(oal_void)
{
    gst_alg_main.p_cfg_double_ant_switch_notify_func = OAL_PTR_NULL;
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_user_protocol_notify_func
 ��������  : ���㷨ע������USERЭ��ģʽ�ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��19��
    ��    ��   : liwenjun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_user_protocol_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_spatial_stream_notify_func
 ��������  : ���㷨ȥע������USER�ռ����ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_spatial_stream_notify_func(dmac_alg_cfg_user_spatial_stream_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_user_spatial_stream_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_del_vap_notify_func
 ��������  : ���㷨ע�ᴴ��VAP�ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC




 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_VAP_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_delete_vap_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_add_user_notify_func
 ��������  : ���㷨ע����ӹ����û��Ļص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_USER_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_delete_assoc_user_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_add_user_notify_func
 ��������  : ���㷨ע�����ȥ�����û��Ļص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_add_user_notify_func(dmac_alg_add_user_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_USER_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_add_assoc_user_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_rx_mgmt_notify_func
 ��������  : ȥע�����㷨�����жԽ��չ���֡������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��22��
    ��    ��   : wanran
    �޸�����   : �����㷨ID�������㷨ģ��ͨ��

*****************************************************************************/
oal_uint32  dmac_alg_unregister_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_MGMT_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.p_rx_mgmt_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_txbf_rx_cntl_notify_func
 ��������  : ȥע��txbf�����жԽ��տ���֡������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_txbf_rx_cntl_notify_func(oal_void)
{
    gst_alg_main.p_txbf_rx_cntl_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_timer
 ��������  : ���㷨ע�ᶨʱ���ܺ���
 �������  :
 �������  : ppst_timer
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_timer(oal_uint32  ul_file_id,
                                   oal_uint32  ul_line_num,
                                   oam_module_id_enum_uint16 en_module_id,
                                   oal_uint32 ul_core_id,
                                   p_alg_timer_notify_func p_timer_notify_func,
                                   oal_void *p_arg,
                                   oal_bool_enum_uint8 en_is_periodic,
                                   dmac_alg_timer_stru **ppst_timer)
{
    dmac_alg_timer_stru *pst_timer;

    if (OAL_UNLIKELY(OAL_PTR_NULL == ppst_timer
        || OAL_PTR_NULL == p_timer_notify_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_timer ERROR");
        return OAL_FAIL;
    }

    pst_timer = (dmac_alg_timer_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_timer_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_timer)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_timer OAL_MEM_ALLOC ERROR");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_timer->en_module_id   = en_module_id;
    pst_timer->p_func         = p_timer_notify_func;
    pst_timer->p_timeout_arg  = p_arg;
    pst_timer->en_is_periodic = en_is_periodic;
    pst_timer->ul_file_id     = ul_file_id;
    pst_timer->ul_line_num    = ul_line_num;
    pst_timer->en_is_enabled  = OAL_FALSE;
    pst_timer->en_is_registerd= OAL_TRUE;
    pst_timer->en_is_deleting = OAL_FALSE;
    pst_timer->en_is_running  = OAL_FALSE;
    pst_timer->ul_core_id     = ul_core_id;

    frw_timer_add_timer(pst_timer);

    *ppst_timer = pst_timer;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_timer
 ��������  : ���㷨ע����ʱ���ܺ���
 �������  : pst_mac_dev
             pst_timer
 �������  :
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_timer(dmac_alg_timer_stru *pst_timer)
{

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_unregister_timer ERROR");
        return OAL_FAIL;
    }

    /* �ж϶�ʱ���Ƿ�ֹͣ */
    if (pst_timer->en_is_enabled == OAL_TRUE)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_timer::pst_timer->en_is_enabled == OAL_TRUE}\r\n");
        return OAL_FAIL;
    }

    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_timer);

    OAL_MEM_FREE(pst_timer, OAL_TRUE);


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_start_timer
 ��������  : ���㷨������ʱ���ܺ���
 �������  : pst_timer
             ul_timeout_ms
 �������  :
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_start_timer(dmac_alg_timer_stru *pst_timer, oal_uint16 us_timeout_ms)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer
        || 0 == us_timeout_ms))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_start_timer ERROR");
        return OAL_FAIL;
    }

    frw_timer_restart_timer(pst_timer, us_timeout_ms, pst_timer->en_is_periodic);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_stop_timer
 ��������  : ���㷨ֹͣ��ʱ���ܺ���
 �������  : pst_timer
             ul_timeout_ms
 �������  :
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_stop_timer(dmac_alg_timer_stru *pst_timer)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_stop_timer ERROR");
        return OAL_FAIL;
    }

    frw_timer_stop_timer(pst_timer);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_device_priv_stru
 ��������  : ע���豸����Ľṹ��
 �������  : en_dev_stru_type    : �ṹ������
             p_dev_stru          : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                  dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type,
                                                  oal_void                        *p_dev_stru)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (OAL_PTR_NULL == p_dev_stru)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, p_dev_stru=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, p_dev_stru, en_dev_stru_type);
        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_device_priv_stru:: pst_dev_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dev_info->p_alg_info[en_dev_stru_type] = p_dev_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_device_priv_stru
 ��������  : ע���豸����Ľṹ��
 �������  : en_dev_stru_type    : �ṹ������
             p_dev_stru          : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                  dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, en_dev_stru_type);
        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_device_priv_stru:: pst_dev_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dev_info->p_alg_info[en_dev_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_vap_priv_stru
 ��������  : ע��VAP˽�����ݽṹ��
 �������  : pst_vap: VAP�ṹ��
             en_vap_stru_type  : �ṹ��ö������
             p_vap_stru        : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                              dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                              oal_void                     *p_vap_stru)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (OAL_PTR_NULL == p_vap_stru)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, p_vap_stru=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, p_vap_stru, en_vap_stru_type);
        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_vap_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_vap_stru_type] = p_vap_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_vap_priv_stru
 ��������  : ע��VAP˽�����ݽṹ��
 �������  : pst_vap: VAP�ṹ��
             en_vap_stru_type  : �ṹ��ö������
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                              dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, en_vap_stru_type);

        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_vap_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_vap_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_user_priv_stru
 ��������  : ע��USER˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             en_user_stru_type : �ṹ��ö������
             p_user_stru       : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_user_priv_stru(mac_user_stru                     *pst_user,
                                                       dmac_alg_user_stru_id_enum_uint8   en_user_stru_type,
                                                       oal_void                          *p_user_stru)
{
    dmac_user_stru         *pst_dmac_user;
    dmac_alg_user_stru     *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == p_user_stru)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_user_priv_stru:: ERROR INFO: pst_user=0x%x, p_user_stru=0x%x, en_user_stru_type=%d.}",
                       pst_user, p_user_stru, en_user_stru_type);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_user_priv_stru:: pst_dmac_user is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->p_alg_priv;
    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_user_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_user_stru_type] = p_user_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_user_priv_stru
 ��������  : ע��USER˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             en_user_stru_type : �ṹ��ö������
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_user_priv_stru(mac_user_stru                     *pst_user,
                                                       dmac_alg_user_stru_id_enum_uint8   en_user_stru_type)
{
    dmac_user_stru         *pst_dmac_user;
    dmac_alg_user_stru     *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_user_priv_stru:: ERROR INFO: pst_user=0x%x, en_user_stru_type=%d.}",
                       pst_user, en_user_stru_type);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_user_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->p_alg_priv;
    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "ERROR INFO: p_alg_priv is NULL PTR");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_user_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_tid_priv_stru
 ��������  : ע��TID˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             uc_tid_no : tid��
             en_tid_stru_type : �ṹ������
             p_tid_stru : TID�ṹ��

 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type,
                oal_void                           *p_tid_stru)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == p_tid_stru)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG4(0, OAM_SF_ANY,
                        "{dmac_alg_register_tid_priv_stru:: ERROR INFO: pst_user=0x%x, p_tid_stru=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, p_tid_stru, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_tid_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->st_tx_tid_queue[uc_tid_no].p_alg_priv;
    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
         OAM_ERROR_LOG0(0, OAM_SF_ANY, "ERROR INFO:pst_alg_info is NULL PTR.");

         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_tid_stru_type] = p_tid_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_tid_priv_stru
 ��������  : ע��TID˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             uc_tid_no : tid��
             en_tid_stru_type : �ṹ������
             p_tid_stru : TID�ṹ��

 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG3(0, OAM_SF_ANY,
                        "{dmac_alg_unregister_tid_priv_stru:: ERROR INFO: pst_user=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_ANY, "dmac_alg_register_tid_priv_stru, mac_res_get_dmac_user[user idx %d] RETURN NULL PTR.", pst_user->us_assoc_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->st_tx_tid_queue[uc_tid_no].p_alg_priv;
    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
         OAM_ERROR_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "ERROR INFO:pst_alg_info is NULL PTR, user idx = %d, tid no = %d.", pst_user->us_assoc_id, uc_tid_no);

         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_tid_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_device_priv_stru
 ��������  : ��ȡTID�µ�˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             uc_tid_no : tid��
             en_tid_stru_type : �ṹ������
 �������  : p_tid_stru : TID�ṹ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_device_priv_stru(
                mac_device_stru                        *pst_mac_dev,
                dmac_alg_device_stru_id_enum_uint8      en_dev_stru_type,
                oal_void                              **pp_dev_stru)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (OAL_PTR_NULL == pp_dev_stru)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, pp_dev_stru=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, pp_dev_stru, en_dev_stru_type);


        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_device_priv_stru::pst_dev_info is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_dev_stru = pst_dev_info->p_alg_info[en_dev_stru_type];

    if (OAL_UNLIKELY(*pp_dev_stru == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_device_priv_stru::pp_dev_stru is null, en_dev_stru_type=%d}", en_dev_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_vap_priv_stru
 ��������  : ��ȡVAP˽�����ݽṹ��
 �������  : pst_vap: VAP�ṹ��
             en_vap_stru_type  : �ṹ��ö������
             p_vap_stru        : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                        dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                        oal_void                     **pp_vap_stru)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (OAL_PTR_NULL == pp_vap_stru)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, pp_vap_stru=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, pp_vap_stru, en_vap_stru_type);

        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_vap_stru = pst_alg_info->p_alg_info[en_vap_stru_type];

    if (OAL_UNLIKELY(*pp_vap_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_vap_priv_stru::alg priv pp_vap_stru is null, en_vap_stru_type=%d}", en_vap_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_user_priv_stru
 ��������  : ��ȡUSER˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             en_user_stru_type : �ṹ��ö������
             p_user_stru       : ��Ҫע��Ľṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_user_priv_stru(
                mac_user_stru                      *pst_user,
                dmac_alg_user_stru_id_enum_uint8    en_user_stru_type,
                oal_void                          **pp_user_stru)
{
    dmac_alg_user_stru     *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == pp_user_stru)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_user_priv_stru:: ERROR INFO: pst_user=0x%x, pp_user_stru=0x%x, en_user_stru_type=%d.}",
                       pst_user, pp_user_stru, en_user_stru_type);
        return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_ANY, "dmac_alg_get_user_priv_stru, mac_res_get_dmac_user RETURN NULL PTR, user idx = %d.", pst_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        if (MAC_USER_STATE_ASSOC != pst_user->en_user_asoc_state)
        {
           OAM_WARNING_LOG4(pst_user->uc_vap_id, OAM_SF_ANY,
                            "{dmac_alg_get_user_priv_stru:: us_assoc_id=%d, en_user_asoc_state=%d, user mac: %2x:%2x}",
                            pst_user->us_assoc_id,
                            pst_user->en_user_asoc_state,
                            pst_user->auc_user_mac_addr[0],
                            pst_user->auc_user_mac_addr[1]);
           OAM_WARNING_LOG4(pst_user->uc_vap_id, OAM_SF_ANY,
                            "{dmac_alg_get_user_priv_stru:: user mac:%2x:%2x:%2x:%2x}",
                            pst_user->auc_user_mac_addr[2],
                            pst_user->auc_user_mac_addr[3],
                            pst_user->auc_user_mac_addr[4],
                            pst_user->auc_user_mac_addr[5]);
        }

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_user_stru = pst_alg_info->p_alg_info[en_user_stru_type];

    if (OAL_UNLIKELY(*pp_user_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_user_priv_stru::alg priv pp_user_stru is null, en_user_stru_type=%d, user idx = %d}",
                         en_user_stru_type, pst_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_tid_priv_stru
 ��������  : ��ȡTID�µ�˽�����ݽṹ��
 �������  : pst_user: user�ṹ��
             uc_tid_no : tid��
             en_tid_stru_type : �ṹ������
 �������  : p_tid_stru : TID�ṹ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��3��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type,
                oal_void                          **pp_tid_stru)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == pp_tid_stru)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG4(0, OAM_SF_ANY,
                        "{dmac_alg_get_tid_priv_stru:: ERROR INFO: pst_user=0x%x, pp_tid_stru=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, pp_tid_stru, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_get_tid_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        if (MAC_USER_STATE_ASSOC != pst_user->en_user_asoc_state)
        {
            OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_alg_get_tid_priv_stru::p_alg_priv is null ptr. user state = %d, user_id=%d}",
                            pst_user->en_user_asoc_state,
                            pst_user->us_assoc_id);
        }

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_tid_stru = pst_alg_info->p_alg_info[en_tid_stru_type];

    if (OAL_UNLIKELY(*pp_tid_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_tid_priv_stru::pp_tid_stru is null, en_tid_stru_type=%d}", en_tid_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_channel_notify
 ��������  : ���������ŵ�
 �������  : pst_vap: VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_channel_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_channel_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_channel_notify_func[uc_index](pst_vap, en_type);
        }
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_start_connect_notify
 ��������  : ����staģʽ�������
 �������  : pst_vap: VAP�ṹ��
             c_rssi: ׼������AP��rssi
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��17��
    ��    ��   : t00190962
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_start_connect_notify(mac_vap_stru *pst_vap, oal_int8 c_rssi)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;
    oal_uint32      ul_ret;

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_start_connect_notify_func[uc_index])
        {
            ul_ret = pst_alg_stru->pa_cfg_start_connect_notify_func[uc_index](pst_vap, c_rssi);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_cfg_start_connect_notify::ul_ret=%d, uc_index=%d}", ul_ret, uc_index);
            }
        }
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_btcoex_state_notify
 ��������  : ����staģʽ�������
 �������  : pst_vap: VAP�ṹ��
             c_rssi: ׼������AP��rssi
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_btcoex_state_notify(mac_device_stru *pst_device, dmac_alg_bt_state_type_uint8 en_type)
{
    dmac_alg_stru  *pst_alg_stru;

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_btcoex_state_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_TPC])
    {
        pst_alg_stru->pa_cfg_btcoex_state_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_TPC](pst_device, en_type);
    }

    return OAL_SUCC;
}
#endif /* _PRE_WLAN_FEATURE_BTCOEX */
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32 dmac_alg_cfg_dual_antenna_state_notify(mac_device_stru *pst_device, oal_uint32 ul_status)
{
    dmac_alg_stru  *pst_alg_stru;

    pst_alg_stru = &gst_alg_main;
    if (OAL_PTR_NULL != pst_alg_stru->p_cfg_dual_antenna_state_notify_func)
    {
        pst_alg_stru->p_cfg_dual_antenna_state_notify_func(pst_device, ul_status);
    }
    return OAL_SUCC;
}
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */


#ifdef _PRE_WLAN_FEATURE_CCA_OPT

/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_cca_intf_mode_notify_func
 ��������  : ���㷨ע�����ģʽ�ı�ص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : liuming 00222214
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type,
                                                               p_alg_cfg_cca_intf_mode_notify_func        p_func)

{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_cca_intf_mode_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_cca_intf_mode_notify_func
 ��������  : ���㷨ע������ģʽ�ı�ص�����
 �������  : en_feature    : ����ö��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : liuming 00222214
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_cca_intf_mode_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_cca_intf_mode_notify
 ��������  : ֪ͨ�㷨����ģʽ�ı�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : liuming 00222214
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_cca_intf_mode_notify(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* ������ػص����� */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_cca_intf_mode_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_cca_intf_mode_notify_func[uc_index](pst_device, uc_intf_mode_old,
                    uc_intf_mode_new, c_cca_opt_avg_rssi_20, c_cca_opt_avg_rssi_40, c_cca_opt_avg_rssi_80);
        }
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_user_bandwidth_notify
 ��������  : ֪ͨ�㷨USER����ı�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_bandwidth_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* ������ػص����� */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_bandwidth_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_bandwidth_notify_func[uc_index](pst_vap, pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_user_ant_changed_notify
 ��������  : ֪ͨ�㷨USER���߸ı�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_ant_changed_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;
    oal_uint32                ul_ret;

    pst_alg_stru = &gst_alg_main;

    /* ������ػص����� Ŀǰֻ��Ҫ֪ͨtxbf������������Ҫ֪ͨ����ģ�飬Ԥ���ӿ�*/
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_ANT_CHANGED_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_ant_changed_notify_func[uc_index])
        {
            ul_ret = pst_alg_stru->pa_cfg_user_ant_changed_notify_func[uc_index](pst_vap, pst_mac_user);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_alg_cfg_user_ant_changed_notify::ul_ret=%d, uc_index=%d}", ul_ret, uc_index);
            }
        }
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_uint32  dmac_alg_cfg_get_ant_info_notify(mac_vap_stru *pst_vap, oal_uint8 *puc_param,
    oal_uint32 *pul_param1, oal_uint32 *pul_param2, oal_uint32 *pul_param3, oal_uint32 *pul_param4, oal_uint32 *pul_param5)
{
    dmac_alg_stru  *pst_alg_stru;
    pst_alg_stru = &gst_alg_main;
    if (OAL_PTR_NULL != pst_alg_stru->p_cfg_get_ant_info_notify_func)
    {
        pst_alg_stru->p_cfg_get_ant_info_notify_func(pst_vap, puc_param, pul_param1, pul_param2, pul_param3, pul_param4, pul_param5);
    }
    return OAL_SUCC;
}
oal_uint32  dmac_alg_cfg_double_ant_switch_notify(mac_device_stru *pst_mac_device, oal_uint8 uc_param)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint32      ul_ret = OAL_FAIL;
    pst_alg_stru = &gst_alg_main;
    if (OAL_PTR_NULL != pst_alg_stru->p_cfg_double_ant_switch_notify_func)
    {
        ul_ret = pst_alg_stru->p_cfg_double_ant_switch_notify_func(pst_mac_device, uc_param);
    }
    return ul_ret;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_user_protocol_notify
 ��������  : ֪ͨ�㷨USERЭ��ģʽ�ı�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_protocol_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* ������ػص����� */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_protocol_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_protocol_notify_func[uc_index](pst_vap, pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_bandwidth_notify
 ��������  : �������ô���
 �������  : pst_vap: VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_bandwidth_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;
    oal_dlist_head_stru      *pst_entry;
    mac_user_stru            *pst_mac_user;
    wlan_bw_cap_enum_uint8    en_bwcap_ap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_bandwidth_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_bandwidth_notify_func[uc_index](pst_vap, en_type);
        }
    }

    if (CH_BW_CHG_TYPE_SCAN == en_type)
    {
        return OAL_SUCC;
    }
    /* ��ȡVAP�������� */
    mac_vap_get_bandwidth_cap(pst_vap, &en_bwcap_ap);

    /* ����VAP������USER */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_vap->st_mac_user_list_head))
    {
        pst_mac_user = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);

        /* ֪ͨ�㷨 */
        dmac_alg_cfg_user_bandwidth_notify(pst_vap, pst_mac_user);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_user_spatial_stream_notify
 ��������  : ֪ͨ�㷨USER����ı�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_spatial_stream_notify(mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* ������ػص����� */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_spatial_stream_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_spatial_stream_notify_func[uc_index](pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_add_assoc_user_notify
 ��������  : ��DMAC���һ�������û�ʱ������øú���
 �������  : pst_vap: VAP�ṹ��; pst_user: �û��ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_alg_add_assoc_user_notify(dmac_vap_stru *pst_vap, dmac_user_stru *pst_user)
{
    dmac_alg_user_stru  *pst_user_info;
    dmac_alg_tid_stru   *pst_tid_info;
    dmac_alg_stru       *pst_alg_stru;
    oal_uint8            uc_index;
    oal_uint8            uc_loop = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_user->p_alg_priv)
    {
        dmac_alg_del_assoc_user_notify(pst_vap, pst_user);
    }

    /* �ҽ��û���������ݽṹ */
    pst_user_info = (dmac_alg_user_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_user_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_add_assoc_user_notify: alloc mem fail, dmac_alg_user_stru, pool id is OAL_MEM_POOL_ID_LOCAL");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    for (uc_index = 0; uc_index < DMAC_ALG_USER_STRU_ID_BUTT; uc_index++)
    {
        pst_user_info->p_alg_info[uc_index] = OAL_PTR_NULL;
    }

    pst_user->p_alg_priv = pst_user_info;

    /* �ҽ�TID��������ݽṹ */
    for (uc_index = 0; uc_index < WLAN_TID_MAX_NUM; uc_index++)
    {
        pst_tid_info = (dmac_alg_tid_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_tid_stru), OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_info))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_add_assoc_user_notify: alloc mem fail, dmac_alg_tid_stru, pool id is OAL_MEM_POOL_ID_LOCAL");
            OAL_MEM_FREE((oal_void *)pst_user_info, OAL_TRUE);
            pst_user->p_alg_priv = OAL_PTR_NULL;

            dmac_alg_free_tid_priv_stru(pst_user);

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        for (uc_loop = 0; uc_loop < DMAC_ALG_TID_STRU_ID_BUTT; uc_loop++)
        {
            pst_tid_info->p_alg_info[uc_loop] = OAL_PTR_NULL;
        }

        pst_user->ast_tx_tid_queue[uc_index].p_alg_priv = pst_tid_info;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_ADD_USER_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_add_assoc_user_notify_func[uc_index])
        {
            pst_alg_stru->pa_add_assoc_user_notify_func[uc_index](&(pst_vap->st_vap_base_info), &(pst_user->st_user_base_info));
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_notify_del_assoc_user
 ��������  : ��DMACɾ��һ�������û�ʱ������øú���
 �������  : pst_vap: VAP�ṹ��; pst_user: �û��ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_alg_del_assoc_user_notify(dmac_vap_stru *pst_vap, dmac_user_stru *pst_user)
{
    dmac_alg_user_stru     *pst_user_info;
    dmac_alg_stru          *pst_alg_stru;
    oal_uint8               uc_index;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_user->p_alg_priv)
    {
        return OAL_SUCC;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_DEL_USER_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_delete_assoc_user_notify_func[uc_index])
        {
            pst_alg_stru->pa_delete_assoc_user_notify_func[uc_index](&(pst_vap->st_vap_base_info), &(pst_user->st_user_base_info));
        }
    }

    /* �ͷ�TID��������ݽṹ */
    dmac_alg_free_tid_priv_stru(pst_user);

    /* �ͷ��û���������ݽṹ */
    pst_user_info = pst_user->p_alg_priv;

    if (OAL_PTR_NULL != pst_user_info)
    {
        OAL_MEM_FREE(pst_user_info, OAL_TRUE);
        pst_user->p_alg_priv = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_rx_mgmt_notify
 ��������  : �����չ���֪֡ͨ�㷨txbf/������ģ��
 �������  : pst_vap      : VAP�ṹ��
             pst_user     : user�ṹ��
             pst_buf      : netbuf�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��22��
    ��    ��   : wanran
    �޸�����   : �����㷨ID, ɾ��pst userΪ�յ��жϣ������㷨ģ��ͨ��

*****************************************************************************/
oal_uint32  dmac_alg_rx_mgmt_notify(mac_vap_stru *pst_vap,  mac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY,
                       "{dmac_alg_rx_mgmt_notify:: ERROR INFO: pst_vap=0x%x, pst_buf=0x%x.}",
                       pst_vap, pst_buf);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_RX_MGMT_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->p_rx_mgmt_func[uc_index])
        {
            pst_alg_stru->p_rx_mgmt_func[uc_index](pst_vap, pst_user, pst_buf);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_txbf_rx_cntl_notify
 ��������  : �����տ���֪֡ͨ�㷨txbfģ��
 �������  : pst_vap      : VAP�ṹ��
             pst_user     : user�ṹ��
             pst_buf      : netbuf�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_txbf_rx_cntl_notify(mac_vap_stru *pst_vap,  mac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    dmac_alg_stru  *pst_alg_stru;


    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_txbf_rx_cntl_notify:: ERROR INFO: pst_vap=0x%x, pst_user=0x%x, pst_buf=0x%x.}",
                       pst_vap, pst_user, pst_buf);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    if (OAL_PTR_NULL != pst_alg_stru->p_txbf_rx_cntl_func)
    {
        pst_alg_stru->p_txbf_rx_cntl_func(pst_vap, pst_user, pst_buf);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_notify_create_vap
 ��������  : ������VAPʱ������øú���
 �������  : pst_event_mem: �¼��ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_alg_create_vap_notify(dmac_vap_stru *pst_vap)
{
    dmac_alg_vap_stru  *pst_alg_info;
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_create_vap_notify::pst_vap is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_vap_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_vap_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_create_vap_notify::pst_alg_infois null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_index = 0; uc_index < DMAC_ALG_VAP_STRU_ID_BUTT; uc_index++)
    {
        pst_alg_info->p_alg_info[uc_index] = OAL_PTR_NULL;
    }


    /* �ҽ�VAP��������ݽṹ */
    pst_vap->p_alg_priv = pst_alg_info;

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_ADD_VAP_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_create_vap_notify_func[uc_index])
        {
            pst_alg_stru->pa_create_vap_notify_func[uc_index]((mac_vap_stru *)pst_vap);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_notify_delete_vap
 ��������  : ��ɾ��VAPʱ������øú���
 �������  : pst_vap: VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_alg_delete_vap_notify(dmac_vap_stru *pst_vap)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_DEL_VAP_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_delete_vap_notify_func[uc_index])
        {
            pst_alg_stru->pa_delete_vap_notify_func[uc_index]((mac_vap_stru *)pst_vap);
        }
    }

    /* ɾ��VAP��������ݽṹ */
    if (OAL_PTR_NULL != pst_vap->p_alg_priv)
    {
        OAL_MEM_FREE(pst_vap->p_alg_priv, OAL_TRUE);
        /* DTS2015041407876 P2P��WLAN��Ƶ����ʱ����������P2P��WLAN�󣬵����������� */
        pst_vap->p_alg_priv = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_create_ba
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_create_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_tid)
{
    frw_event_mem_stru          *pst_event_mem;          /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru              *pst_dmac_to_hmac_event;  /* ָ�������¼���payloadָ�� */
    dmac_to_hmac_ctx_event_stru *pst_create_ba_event;
    oal_uint32                   ul_ret;
    dmac_tid_stru               *pst_tid;
    dmac_user_stru              *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_alg_create_ba::null pointer,pst_dmac_user[%d].}", pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid];

    if (OAL_PTR_NULL != pst_tid->pst_ba_tx_hdl)
    {
        return OAL_SUCC;
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_ctx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "alloc event failed!");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_CREATE_BA,
                       OAL_SIZEOF(dmac_to_hmac_ctx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_create_ba_event = (dmac_to_hmac_ctx_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_create_ba_event->us_user_index  = pst_mac_user->us_assoc_id;
    pst_create_ba_event->uc_tid         = uc_tid;
    pst_create_ba_event->uc_vap_id      = pst_mac_vap->uc_vap_id;

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_create_ba::frw_event_dispatch_event fail, ul_ret=%d}\r\n", ul_ret);
        return ul_ret;
    }

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_create_ba
 ��������  : �㷨ɾ��ba�ӿڣ��˽ӿ�ֻ����һ����־λ����������ɾ��
             Լ��: ���ֻ�ڷ�����ɼ��˱�־λ����˴˽ӿ�ֻ�ڷ�����������е�����Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_del_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_tid)
{
    dmac_user_stru *pst_dmac_user;

    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "user is null ptr!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac user is null ptr!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_delete_ba_flag = OAL_TRUE;

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_alg_syn_info
 ��������  : �㷨�ı�Э�飬��dmacͬ����ǰЭ��ģʽ��hmac
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_syn_info(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    frw_event_mem_stru                      *pst_event_mem;          /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru                          *pst_dmac_to_hmac_event;  /* ָ�������¼���payloadָ�� */
    dmac_to_hmac_syn_info_event_stru        *pst_syn_info_event;
    oal_uint32                               ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_syn_info: alloc event failed! size=%d}", OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_ALG_INFO_SYN,
                       OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_syn_info_event = (dmac_to_hmac_syn_info_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_syn_info_event->us_user_index  = pst_mac_user->us_assoc_id;
    pst_syn_info_event->uc_cur_protocol = pst_mac_user->en_cur_protocol_mode;
    pst_syn_info_event->uc_cur_bandwidth = pst_mac_user->en_cur_bandwidth;

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_syn_info::frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
    }

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_voice_aggr
 ��������  : �㷨�ı�֧��Voice�ۺϵı�־ʱ����dmac֪ͨhmac
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : liwenjun 00330043
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_voice_aggr(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru                      *pst_event_mem;          /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru                          *pst_dmac_to_hmac_event;  /* ָ�������¼���payloadָ�� */
    dmac_to_hmac_voice_aggr_event_stru      *pst_voice_aggr_event;
    oal_uint32                               ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_voice_aggr: alloc event failed! size=%d}", OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru));

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_VOICE_AGGR,
                       OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_voice_aggr_event = (dmac_to_hmac_voice_aggr_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);
    pst_voice_aggr_event->uc_vap_id     = pst_mac_vap->uc_vap_id;
    pst_voice_aggr_event->en_voice_aggr = pst_mac_vap->bit_voice_aggr;

    /* �ַ� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_voice_aggr: frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
    }

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}

#endif
/*****************************************************************************
 �� �� ��  : dmac_alg_get_qap_wme_info
 ��������  : ��ȡ��ǰAP�����WME����
 �������  : pst_vap      : ָ��VAP��ָ��
             en_wme_type  : WME����
 �������  : ppst_wme_info: ָ��WME����
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if ((OAL_PTR_NULL == pst_vap)||(OAL_PTR_NULL == pst_wme_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    /* config vapû��mib�⣬���ܲ�ѯwme���� */
    if (WLAN_VAP_MODE_CONFIG == pst_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_qap_wme_info::config vap has no mib}\r\n");

        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_qap_wme_info::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    pst_wme_info->ul_aifsn      = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableAIFSN;
    pst_wme_info->ul_logcwmax   = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableCWmax;
    pst_wme_info->ul_logcwmin   = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableCWmin;
    pst_wme_info->ul_txop_limit = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableTXOPLimit;

    return OAL_SUCC;
}

//#if ALG_SCHEUDLE_EDCA_FEATURE
/*****************************************************************************
 �� �� ��  : dmac_alg_set_wme_info
 ��������  : ����AP��WME����
 �������  : pst_vap     : ָ��VAP��ָ��
             en_wme_type : WME����ö��
             pst_wme_info: ָ��WME������ָ��
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_set_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    oal_uint32   aul_param[3];

    if ((OAL_PTR_NULL == pst_vap)||(OAL_PTR_NULL == pst_wme_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_set_qap_wme_info::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    /* �������ýӿ� */
    aul_param[0] = WLAN_CFGID_EDCA_TABLE_CWMIN;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_logcwmin;
    dmac_config_set_qap_cwmin(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_CWMAX;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_logcwmax;
    dmac_config_set_qap_cwmax(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_AIFSN;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_aifsn;
    dmac_config_set_qap_aifsn(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_TXOP_LIMIT;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_txop_limit;
    dmac_config_set_qap_txop_limit(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    return OAL_SUCC;
}
//#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_set_msdu_lifetime
 ��������  : ����AP��msdu��lifetime����
 �������  : pst_vap     : ָ��VAP��ָ��
             en_wme_type : WME����ö��
             ul_msdu_lifetime: �����õ�ac��lifetime����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��4��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_set_qap_msdu_lifetime(
                                    mac_vap_stru               *pst_vap,
                                    wlan_wme_ac_type_enum_uint8 en_wme_type,
                                    oal_uint32                  ul_msdu_lifetime)
{
    oal_uint32   aul_param[3];
    oal_uint32   ul_ret = OAL_SUCC;

    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_set_qap_msdu_lifetime::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    /* �������ýӿ� */
    aul_param[1] = (oal_uint32)en_wme_type;
    aul_param[2] = ul_msdu_lifetime;

    ul_ret = dmac_config_set_qap_msdu_lifetime(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "dmac_config_set_msdu_lifetime failed");
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_register
 ��������  : �㷨ע��
 �������  : en_alg_id: �㷨��ö������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register(dmac_alg_id_enum_uint32 en_alg_id)
{
    ALG_ASSERT_RET(en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_ARRAY_OVERFLOW);
    gst_alg_main.ul_alg_bitmap |= en_alg_id;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register
 ��������  : �㷨ע��
 �������  : en_alg_id: �㷨��ö������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister(dmac_alg_id_enum_uint32 en_alg_id)
{
    ALG_ASSERT_RET(en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_ARRAY_OVERFLOW);
    gst_alg_main.ul_alg_bitmap &= (~en_alg_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_is_registered
 ��������  : �鿴�㷨�Ƿ�ע��
 �������  : p_mac_dev: MAC DEVICE; en_alg_id: �㷨��ö������
 �������  : pen_is_registered: �Ƿ�ע��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��20��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_is_registered(dmac_alg_id_enum_uint32 en_alg_id, oal_bool_enum_uint8 *pen_is_registered)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != pen_is_registered && en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_PTR_NULL);
    if((gst_alg_main.ul_alg_bitmap & en_alg_id) == en_alg_id)
    {
        *pen_is_registered = OAL_TRUE;
    }
    else
    {
        *pen_is_registered = OAL_FALSE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_main_init
 ��������  : ALGģ���ʼ������ڣ�����ALGģ���ڲ��������Եĳ�ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ�������룬�ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_init(mac_device_stru  *pst_device)
{
    dmac_alg_device_stru *p_alg_dev_stru;     /* device�����㷨��˽�����ݽṹ */
    oal_uint32  uc_idx;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_init: OAL_PTR_NULL == pst_device");
        return OAL_ERR_CODE_PTR_NULL;
    }

    p_alg_dev_stru = (dmac_alg_device_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_device_stru), OAL_TRUE);

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_alg_dev_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "alg_main_init: OAL_PTR_NULL == p_alg_stru\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_idx = 0; uc_idx < DMAC_ALG_DEVICE_STRU_ID_BUTT; uc_idx++)
    {
        p_alg_dev_stru->p_alg_info[uc_idx] = OAL_PTR_NULL;
    }

    /* �ҽ��㷨���ṹ�� */
    MAC_DEV_ALG_PRIV(pst_device) = p_alg_dev_stru;

    /* ���ṹ���ʼ�� */
    oal_dlist_init_head(&gst_alg_main.st_timer_list);     /* ��ʱ��˫�������ʼ�� */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_main_exit
 ��������  : ALGģ��ж��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ж�ط����룬�ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_exit(mac_device_stru  *pst_device)
{
    dmac_alg_device_stru *p_alg_dev_stru;     /* device�����㷨��˽�����ݽṹ */

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_exit: OAL_PTR_NULL == pst_device");
        return OAL_ERR_CODE_PTR_NULL;
    }

    p_alg_dev_stru = MAC_DEV_ALG_PRIV(pst_device);
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_alg_dev_stru))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_exit::OAL_PTR_NULL == p_alg_stru}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_FREE(p_alg_dev_stru, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : alg_main_exit
 ��������  : ��ȡĳӲ��������ppdu�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ж�ط����룬�ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2012��9��18��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32   dmac_alg_get_hal_queue_ppdu_num(oal_uint16 us_assoc_id, oal_uint8 uc_ac_num, oal_uint8 *puc_ppdu_num)
{
    dmac_vap_stru             *pst_dmac_vap;
    mac_user_stru             *pst_user;
    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_assoc_id);
    if(OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_get_hal_queue_ppdu_num: OAL_PTR_NULL == pst_user");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap    = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_user->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_hal_queue_ppdu_num::mac_res_get_dmac_vap fail. vap_id[%u]}",pst_user->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_ppdu_num   = pst_dmac_vap->pst_hal_device->ast_tx_dscr_queue[HAL_AC_TO_Q_NUM(uc_ac_num)].uc_ppdu_cnt;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_alg_set_hal_queue_ppdu_num
 ��������  : ����ĳӲ��������ppdu�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ж�ط����룬�ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��6��23��
    ��    ��   : pwx284245
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32   dmac_alg_set_hal_queue_ppdu_num(oal_uint16 us_assoc_id, oal_uint8 uc_ac_num, oal_uint8 puc_ppdu_num)
{
    dmac_vap_stru             *pst_dmac_vap;
    hal_to_dmac_device_stru   *pst_hal_device;
    mac_user_stru             *pst_user;
    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_assoc_id);
    if(OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_set_hal_queue_ppdu_num: OAL_PTR_NULL == pst_user");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap    = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_user->uc_vap_id);
    pst_hal_device  = pst_dmac_vap->pst_hal_device;
    pst_hal_device->ast_tx_dscr_queue[HAL_AC_TO_Q_NUM(uc_ac_num)].uc_ppdu_cnt = puc_ppdu_num;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_get_hal_to_dmac_vap
 ��������  : ����mac_vap_id��ȡhal_to_dmac_vap�ṹ
 �������  : oal_uint8 uc_mac_vap_id
 �������  : ��
 �� �� ֵ  : hal_to_dmac_vap_stru *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
hal_to_dmac_vap_stru *dmac_alg_get_hal_to_dmac_vap(oal_uint8 uc_mac_vap_id)
{
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(uc_mac_vap_id);
    if (NULL == pst_dmac_vap)
    {
        return OAL_PTR_NULL;
    }

    return pst_dmac_vap->pst_hal_vap;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : dmac_alg_register_cfg_smps_notify_func
 ��������  : ���㷨ע������SMPS�Ļص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type,
                                                   p_alg_cfg_smps_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_smps_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_cfg_smps_notify_func
 ��������  : ���㷨ע������SMPS�Ļص�����
 �������  : en_feature    : ����ö��
             p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_smps_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_cfg_smps_notify
 ��������  : ��������SMPSģʽ
 �������  : pst_vap: VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_cfg_smps_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_smps_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_smps_notify_func[uc_index](pst_vap, pst_user);
        }
    }

    return OAL_SUCC;
}

#endif

/* ���û����ٻ�ȡ������ؽӿ� */
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 �� �� ��  : dmac_alg_register_start_stat_rssi_notify
 ��������  : ע������ͳ��rssi���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_rssi_notify(
                                        p_alg_start_stat_rssi_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_start_stat_rssi_notify
 ��������  : ȥע������ͳ��rssi���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_rssi_notify(oal_void)
{
    gst_alg_main.p_start_stat_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_rssi_notify
 ��������  : ע���ȡrssi���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rssi_notify(p_alg_get_rssi_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_get_rssi_notify
 ��������  : ȥע���ȡrssi���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rssi_notify(oal_void)
{
    gst_alg_main.p_get_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_register_stop_stat_rssi_notify
 ��������  : ע��ֹͣͳ��rssi���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_rssi_notify(
                                        p_alg_stop_stat_rssi_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_stop_stat_rssi_notify
 ��������  : ȥע��ֹͣͳ��rssi���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_rssi_notify(oal_void)
{
    gst_alg_main.p_stop_stat_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_start_stat_rate_notify
 ��������  : ע������ͳ��rate���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_rate_notify(
                                        p_alg_start_stat_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_start_stat_rate_notify
 ��������  : ȥע������ͳ��rate���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_rate_notify(oal_void)
{
    gst_alg_main.p_start_stat_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_rate_notify
 ��������  : ע���ȡrate���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rate_notify(p_alg_get_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_get_rate_notify
 ��������  : ȥע���ȡrate���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rate_notify(oal_void)
{
    gst_alg_main.p_get_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_register_stop_stat_rate_notify
 ��������  : ע��ֹͣͳ��rate���ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_rate_notify(
                                        p_alg_start_stat_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_stop_stat_rate_notify
 ��������  : ȥע��ֹͣͳ��rate���ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_rate_notify(oal_void)
{
    gst_alg_main.p_stop_stat_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_start_stat_best_rate_notify
 ��������  : ע������ͳ������������ز������ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_best_rate_notify(
                                        p_alg_start_stat_best_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_start_stat_best_rate_notify
 ��������  : ȥע������ͳ���������ʹ��ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_best_rate_notify(oal_void)
{
    gst_alg_main.p_start_stat_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_best_rate_notify
 ��������  : ע���ȡ�������ʹ��ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_best_rate_notify(p_alg_get_best_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_get_best_rate_notify
 ��������  : ȥע���ȡ�������ʹ��ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_best_rate_notify(oal_void)
{
    gst_alg_main.p_get_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_alg_register_stop_stat_best_rate_notify
 ��������  : ע��ֹͣͳ���������ʹ��ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_best_rate_notify(
                                        p_alg_stop_stat_best_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_stop_stat_best_rate_notify
 ��������  : ȥע��ֹͣͳ���������ʹ��ܵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_best_rate_notify(oal_void)
{
    gst_alg_main.p_stop_stat_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_start_stat_rssi
 ��������  : ��װȫ�ֹ��ӣ���ʼͳ���շ�rssi
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_rssi(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "param null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_rssi_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "p_start_stat_rssi_func null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_rssi_func(pst_mac_user);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_rssi
 ��������  : ��װȫ�ֹ��ӣ���ȡ�շ�rssi
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_rssi(mac_user_stru *pst_mac_user,
                                  oal_int8      *pc_tx_rssi,
                                  oal_int8      *pc_rx_rssi)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pc_rx_rssi || OAL_PTR_NULL == pc_tx_rssi))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rssi:: ERROR INFO: pst_mac_user=0x%x, pc_tx_rssi=0x%x, pc_rx_rssi=0x%x.}",
                       pst_mac_user, pc_tx_rssi, pc_rx_rssi);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rssi_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rssi::p_get_rssi_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rssi_func(pst_mac_user, pc_tx_rssi, pc_rx_rssi);
}


/*****************************************************************************
 �� �� ��  : dmac_alg_stop_stat_rssi
 ��������  : ��װ���ӣ�ֹͣͳ���շ�rssi
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_rssi(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rssi::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_rssi_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rssi::p_stop_stat_rssi_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_rssi_func(pst_mac_user);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_start_stat_rate
 ��������  : ��װȫ�ֹ��ӣ���ʼͳ���շ�rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_rate::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "p_start_stat_rate_func null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_rate_func(pst_mac_user);
}


/*****************************************************************************
 �� �� ��  : dmac_alg_get_rate
 ��������  : ��װȫ�ֹ��ӣ���ȡ�շ�rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_rate(mac_user_stru *pst_mac_user,
                                  oal_uint32     *pul_tx_rate,
                                  oal_uint32     *pul_rx_rate)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pul_rx_rate || OAL_PTR_NULL == pul_tx_rate))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rate:: ERROR INFO: pst_mac_user=0x%x, pul_tx_rate=0x%x, pul_rx_rate=0x%x.}",
                       pst_mac_user, pul_tx_rate, pul_rx_rate);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rate::p_get_rate_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rate_func(pst_mac_user, pul_tx_rate, pul_rx_rate);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_stop_stat_rate
 ��������  : ��װ���ӣ�ֹͣͳ���շ�rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rate::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rate::p_stop_stat_rate_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_rate_func(pst_mac_user);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_start_stat_best_rate
 ��������  : ��װȫ�ֹ��ӣ���ʼͳ������rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_best_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_best_rate::user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_best_rate::p_start_stat_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_best_rate_func(pst_mac_user);
}


/*****************************************************************************
 �� �� ��  : dmac_alg_get_best_rate
 ��������  : ��װȫ�ֹ��ӣ���ȡ����rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_best_rate(
                                  mac_user_stru   *pst_mac_user,
                                  dmac_best_rate_stat_info_stru *pst_best_rate_info)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user || OAL_PTR_NULL == pst_best_rate_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_get_best_rate::pst_mac_user = [%d], \
                       pst_best_rate_info = [%d].}", pst_mac_user, pst_best_rate_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_best_rate::p_get_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_best_rate_func(pst_mac_user, pst_best_rate_info);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_stop_stat_best_rate
 ��������  : ��װ���ӣ�ֹͣͳ������rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_best_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_best_rate::usr is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_best_rate::p_stop_stat_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_best_rate_func(pst_mac_user);
}


#endif
/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_rate_by_table_notify
 ��������  : ע��ͨ�����ʱ��ѯ���ʵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rate_by_table_notify(p_alg_get_rate_by_table_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rate_by_table_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_get_rate_by_table_notify
 ��������  : ע��ͨ�����ʱ��ѯ���ʵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rate_by_table_notify(oal_void)
{
    gst_alg_main.p_get_rate_by_table_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_rate_by_table
 ��������  : ��װȫ�ֹ��ӣ���ȡ���ʴ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_rate_by_table(mac_user_stru *pst_mac_user,
                                  hal_rx_statistic_stru *pst_rx_stats,
                                  oal_uint32 *pul_rate_kbps)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pst_rx_stats || OAL_PTR_NULL == pul_rate_kbps))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rate_by_table:: ERROR INFO: pst_mac_user=0x%x, pst_rx_stats=0x%x, pul_rate_kbps=0x%x.}",
                       pst_mac_user, pst_rx_stats, pst_rx_stats);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rate_by_table_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rate_by_table::p_get_rate_by_table_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rate_by_table_func(pst_mac_user, pst_rx_stats, pul_rate_kbps);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_get_tx_best_rate_notify
 ��������  : ע���ѯtx���ʵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_get_tx_best_rate_notify(p_alg_get_tx_best_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_tx_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_get_rate_by_table_notify
 ��������  : ע����ѯtx���ʵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_tx_best_rate_notify(oal_void)
{
    gst_alg_main.p_get_tx_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_get_tx_best_rate
 ��������  : ��װȫ�ֹ��ӣ���ȡtx�������ʴ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_tx_best_rate(mac_user_stru *pst_mac_user,
                                  wlan_wme_ac_type_enum_uint8 en_traffic_type,
                                  oal_uint32 *pul_rate_kbps)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       ||  OAL_PTR_NULL == pul_rate_kbps))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY,
                       "{dmac_alg_get_tx_best_rate:: ERROR INFO: pst_mac_user=0x%x, pul_rate_kbps=0x%x.}",
                       pst_mac_user, pul_rate_kbps);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_tx_best_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_tx_best_rate::p_get_rate_by_table_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_tx_best_rate_func(pst_mac_user, en_traffic_type, pul_rate_kbps);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_delete_ba_fail_notify
 ��������  : ע��ɾ��baʧ�ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��15��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_delete_ba_fail_notify(p_alg_delete_ba_fail_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_delete_ba_fail_notify_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_delete_ba_fail_notify
 ��������  : ע��ɾ��baʧ�ܵĽӿ�
 �������  : p_func:�㷨ע�������ĺ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��15��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_delete_ba_fail_notify(oal_void)
{
    gst_alg_main.p_delete_ba_fail_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_delete_ba_fail_notify
 ��������  : ��װ֪ͨ�㷨baɾ��ʧ�ܵĹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��15��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_delete_ba_fail_notify(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,
                       "{dmac_alg_delete_ba_fail_notify:: ERROR INFO: pst_mac_user=0x%x.}",
                       pst_mac_user);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_delete_ba_fail_notify_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_delete_ba_fail_notify::p_delete_ba_fail_notify_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_delete_ba_fail_notify_func(pst_mac_user);
}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 �� �� ��  : dmac_edca_opt_stat_event_process
 ��������  : ��edca�Ż�ͳ����Ϣ�¼�������
 �������  : pst_event_mem
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_edca_opt_stat_event_process(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    dmac_alg_stru           *pst_alg_stru;
    oal_uint8                uc_vap_id;
    oal_uint8                uc_device_id;
    oal_uint32               ul_ret;
    oal_uint8                aast_uc_traffic_num[WLAN_WME_AC_BUTT][ALG_TXRX_DATA_BUTT];

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANTI_INTF, "{dmac_join_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    uc_vap_id       = pst_event_hdr->uc_vap_id;
    uc_device_id    = pst_event_hdr->uc_device_id;

    oal_memcopy(aast_uc_traffic_num, pst_event->auc_event_data, OAL_SIZEOF(aast_uc_traffic_num));

    /* ������ػص����� */
    pst_alg_stru = &gst_alg_main;

    /* EDCA �㷨���Ӻ������ڲ�ʶ����û������ȼ���32�û������ȼ�ҵ�� */
    if (OAL_PTR_NULL != pst_alg_stru->p_edca_stat_event_notify_func)
    {
        ul_ret = pst_alg_stru->p_edca_stat_event_notify_func(uc_device_id, uc_vap_id, aast_uc_traffic_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANTI_INTF, "{dmac_edca_opt_stat_event_process::ul_ret=%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
    /*���ȸ��²����㷨���Ӻ���*/
    if (OAL_PTR_NULL != pst_alg_stru->p_tx_schedule_stat_event_notify_func)
    {
        ul_ret = pst_alg_stru->p_tx_schedule_stat_event_notify_func(uc_device_id, uc_vap_id, aast_uc_traffic_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANTI_INTF, "{dmac_edca_opt_stat_event_process::ul_ret=%d", ul_ret);
            return ul_ret;
        }
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_edca_stat_event_notify
 ��������  : ע�Ό������EDCA�Ż�ͳ����Ϣ�¼���֪ͨ����
 �������  : p_func        : ע��ĺ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_edca_stat_event_notify(p_alg_edca_stat_event_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_edca_stat_event_notify_func = p_func;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_edca_stat_event_notify
 ��������  : ȥע�Ό������EDCA�Ż�ͳ����Ϣ�¼���֪ͨ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_edca_stat_event_notify(oal_void)
{
    gst_alg_main.p_edca_stat_event_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

#endif
/*****************************************************************************
 �� �� ��  : dmac_alg_register_dbac_pause_notify
 ��������  : ע��dbac pause�ص�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_pause_notify(
                p_alg_dbac_pause_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_pause_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_dbac_resume_notify
 ��������  : ע��dbac resume�ص�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_resume_notify(
                p_alg_dbac_pause_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_resume_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_register_dbac_is_pause
 ��������  : ע��dbac pause״̬��ѯ�ص�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_is_pause(
                p_alg_dbac_is_pause   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_is_pause_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_dbac_pause
 ��������  : ��ͣDBAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_dbac_pause(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_pause_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_pause_func(pst_mac_device);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_dbac_resume
 ��������  : ��ͣDBAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_dbac_resume(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_resume_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_resume_func(pst_mac_device);
}

/*****************************************************************************
 �� �� ��  : dmac_alg_dbac_is_pause
 ��������  : ��ͣDBAC
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  dmac_alg_dbac_is_pause(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_is_pause_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_is_pause_func(pst_mac_device);
}

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
/*****************************************************************************
 �� �� ��  : dmac_alg_register_anti_intf_switch_notify
 ��������  : ע�����������߿�/�����ûص�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��13��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_register_anti_intf_switch_notify(
                p_alg_anti_intf_switch_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_anti_intf_switch_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_unregister_anti_intf_switch_notify
 ��������  : ȥע�������������㷨��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��13��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_unregister_anti_intf_switch_notify(oal_void)
{
    gst_alg_main.p_anti_intf_switch_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_alg_anti_intf_switch
 ��������  : ����������ʹ�ܿ�/��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��13��
    ��    ��   : wanran
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_anti_intf_switch(mac_device_stru *pst_device, oal_uint8 uc_alg_enable)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_anti_intf_switch_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_anti_intf_switch_func(pst_device, uc_alg_enable);
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_alg_get_mgmt_tx_pow
 ��������  : ��ȡ����֡�ķ��͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��14��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_get_mgmt_tx_pow(mac_user_stru *pst_user, wlan_channel_band_enum_uint8 en_freq_band,oal_uint8 *puc_tx_pow)
{
    oal_uint8   uc_mix_txpwr;
    oal_uint16  us_tx_pow;
    oal_uint32  ul_ret;
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_mgmt_tx_pow_notify_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD: txpwr��Сֵ����ԴΪmac_set_power_cap_ie��������� */
    uc_mix_txpwr = (WLAN_BAND_2G == en_freq_band) ? 4 : 3;
    us_tx_pow    = uc_mix_txpwr;

    ul_ret = gst_alg_main.p_get_mgmt_tx_pow_notify_func(pst_user, en_freq_band, &us_tx_pow, OAL_FALSE);

    /* TBD: us_tx_pow��Ҫ��ȥrf_line_txrx_gain_db_2g_band1_mult10����ֵ��Ҫ��host����ʵ��ͬ����divce */
    us_tx_pow = us_tx_pow - 3;

    if (us_tx_pow < uc_mix_txpwr )
    {
        us_tx_pow = uc_mix_txpwr;
    }

    *puc_tx_pow = (oal_uint8)us_tx_pow;
    return ul_ret;
}


/*lint -e19*/
oal_module_symbol(dmac_alg_register_add_user_notify_func);
oal_module_symbol(dmac_alg_register_device_priv_stru);
oal_module_symbol(dmac_alg_get_device_priv_stru);
oal_module_symbol(dmac_alg_register_tx_schedule_func);
oal_module_symbol(dmac_alg_unregister_tx_schedule_func);

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
oal_module_symbol(dmac_alg_register_tx_schedule_stat_event_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_schedule_stat_event_notify_func);
#endif

oal_module_symbol(dmac_alg_unregister_device_priv_stru);
oal_module_symbol(dmac_alg_unregister_add_user_notify_func);
oal_module_symbol(dmac_alg_create_vap_notify);
oal_module_symbol(dmac_alg_add_assoc_user_notify);
oal_module_symbol(dmac_alg_register_del_user_notify_func);
oal_module_symbol(dmac_alg_unregister_del_user_notify_func);
oal_module_symbol(dmac_alg_unregister_user_priv_stru);
oal_module_symbol(dmac_alg_unregister);
oal_module_symbol(dmac_alg_register_tx_complete_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_notify_func);
oal_module_symbol(dmac_alg_register_user_priv_stru);
oal_module_symbol(dmac_alg_register);
oal_module_symbol(dmac_alg_stop_timer);
oal_module_symbol(dmac_alg_register_timer);
oal_module_symbol(dmac_alg_register_tx_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_complete_notify_func);
oal_module_symbol(dmac_alg_start_timer);
oal_module_symbol(dmac_alg_is_registered);
oal_module_symbol(dmac_alg_unregister_timer);
oal_module_symbol(dmac_alg_register_tid_update_notify_func);
oal_module_symbol(dmac_alg_get_tid_priv_stru);
oal_module_symbol(dmac_alg_register_tid_priv_stru);
oal_module_symbol(dmac_alg_unregister_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_tid_update_notify_func);
oal_module_symbol(dmac_alg_register_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_add_vap_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_channel_notify_func);
oal_module_symbol(dmac_alg_register_cfg_channel_notify_func);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_register_cfg_start_connect_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_start_connect_notify_func);
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
oal_module_symbol(dmac_alg_register_del_vap_notify_func);
oal_module_symbol(dmac_alg_unregister_tid_priv_stru);
oal_module_symbol(dmac_alg_get_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_del_vap_notify_func);
oal_module_symbol(dmac_alg_register_add_vap_notify_func);
oal_module_symbol(dmac_alg_get_user_priv_stru);
oal_module_symbol(dmac_alg_register_rx_notify_func);
oal_module_symbol(dmac_alg_unregister_rx_notify_func);
oal_module_symbol(dmac_alg_del_ba);
oal_module_symbol(dmac_alg_get_hal_queue_ppdu_num);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_set_hal_queue_ppdu_num);
#endif

oal_module_symbol(dmac_alg_get_qap_wme_info);
//#if ALG_SCHEUDLE_EDCA_FEATURE
oal_module_symbol(dmac_alg_set_qap_wme_info);
//#endif
oal_module_symbol(dmac_alg_set_qap_msdu_lifetime);
oal_module_symbol(dmac_alg_get_hal_to_dmac_vap);
oal_module_symbol(dmac_alg_register_config_notify_func);
oal_module_symbol(dmac_alg_unregister_config_notify_func);
oal_module_symbol(dmac_alg_register_downlink_flowctl_notify_func);
oal_module_symbol(dmac_alg_unregister_downlink_flowctl_notify_func);

oal_module_symbol(dmac_alg_register_cfg_user_bandwidth_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_bandwidth_notify_func);
oal_module_symbol(dmac_alg_register_cfg_user_ant_changed_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_ant_changed_notify_func);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_alg_register_cfg_get_ant_info_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_get_ant_info_notify_func);
oal_module_symbol(dmac_alg_register_cfg_double_ant_switch_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_double_ant_switch_notify_func);
#endif
oal_module_symbol(dmac_alg_register_get_mgmt_tx_pow_notify_func);
oal_module_symbol(dmac_alg_unregister_get_mgmt_tx_pow_notify_func);
oal_module_symbol(dmac_alg_register_cfg_user_protocol_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_protocol_notify_func);
oal_module_symbol(dmac_alg_cfg_user_protocol_notify);
oal_module_symbol(dmac_alg_register_rx_mgmt_notify_func);
oal_module_symbol(dmac_alg_unregister_rx_mgmt_notify_func);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_syn_info);
oal_module_symbol(dmac_alg_voice_aggr);
#endif

#ifdef _PRE_WLAN_FEATURE_DBAC
oal_module_symbol(dmac_alg_register_dmac_misc_event);
oal_module_symbol(dmac_alg_unregister_dmac_misc_event);
oal_module_symbol(dmac_alg_register_enqueue_tid_notify_func);
oal_module_symbol(dmac_alg_unregister_enqueue_tid_notify_func);
oal_module_symbol(dmac_alg_register_vap_down_notify_func);
oal_module_symbol(dmac_alg_unregister_vap_down_notify_func);
oal_module_symbol(dmac_alg_register_probe_req_rx_notify_func);
oal_module_symbol(dmac_alg_unregister_probe_req_rx_notify_func);
oal_module_symbol(dmac_alg_register_get_dbac_fakeq_id_func);
oal_module_symbol(dmac_alg_register_update_dbac_fcs_config_func);

#endif

oal_module_symbol(dmac_alg_register_vap_up_notify_func);
oal_module_symbol(dmac_alg_unregister_vap_up_notify_func);

#ifdef _PRE_WLAN_CHIP_TEST_ALG
oal_module_symbol(dmac_alg_register_rx_event_notify);
oal_module_symbol(dmac_alg_unregister_rx_event_notify);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
oal_module_symbol(dmac_alg_register_flowctl_backp_notify_func);
oal_module_symbol(dmac_alg_unregister_flowctl_backp_notify_func);
oal_module_symbol(dmac_alg_flowctl_backp);
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
oal_module_symbol(dmac_alg_register_start_stat_rssi_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_rssi_notify);
oal_module_symbol(dmac_alg_register_start_stat_rate_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_rate_notify);
oal_module_symbol(dmac_alg_register_start_stat_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_rssi_notify);
oal_module_symbol(dmac_alg_unregister_get_rssi_notify);
oal_module_symbol(dmac_alg_register_get_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_get_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_rate_notify);
oal_module_symbol(dmac_alg_unregister_get_rate_notify);
oal_module_symbol(dmac_alg_register_stop_stat_rssi_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_rssi_notify);
oal_module_symbol(dmac_alg_register_stop_stat_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_best_rate_notify);
oal_module_symbol(dmac_alg_register_stop_stat_rate_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_rate_notify);

#endif

oal_module_symbol(dmac_alg_register_get_rate_by_table_notify);
oal_module_symbol(dmac_alg_unregister_get_rate_by_table_notify);


oal_module_symbol(dmac_alg_register_cfg_user_spatial_stream_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_spatial_stream_notify_func);
oal_module_symbol(dmac_alg_register_dbac_pause_notify);
oal_module_symbol(dmac_alg_register_dbac_resume_notify);
oal_module_symbol(dmac_alg_register_dbac_is_pause);

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
oal_module_symbol(dmac_alg_register_edca_stat_event_notify);
oal_module_symbol(dmac_alg_unregister_edca_stat_event_notify);
#endif

oal_module_symbol(dmac_alg_cfg_user_bandwidth_notify);
oal_module_symbol(dmac_alg_cfg_user_ant_changed_notify);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_alg_cfg_get_ant_info_notify);
oal_module_symbol(dmac_alg_cfg_double_ant_switch_notify);
#endif
oal_module_symbol(dmac_alg_unregister_get_tx_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_tx_best_rate_notify);

#ifdef _PRE_WLAN_FEATURE_CCA_OPT
oal_module_symbol(dmac_alg_register_cfg_cca_intf_mode_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_cca_intf_mode_notify_func);
oal_module_symbol(dmac_alg_cfg_cca_intf_mode_notify);
#endif

oal_module_symbol(dmac_alg_register_delete_ba_fail_notify);
oal_module_symbol(dmac_alg_unregister_delete_ba_fail_notify);

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
oal_module_symbol(dmac_alg_register_anti_intf_switch_notify);
oal_module_symbol(dmac_alg_unregister_anti_intf_switch_notify);
#endif/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

