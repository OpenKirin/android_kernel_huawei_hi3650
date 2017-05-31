/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_p2p.c
  �� �� ��   : ����
  ��    ��   : duankaiyong
  ��������   : 2014��11��25��
  ����޸�   :
  ��������   : P2P ������Դ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#ifdef _PRE_WLAN_FEATURE_P2P

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_util.h"
#include "hmac_ext_if.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_rx_filter.h"
#include "hmac_fsm.h"
#include "hmac_mgmt_bss_comm.h"
#include "mac_frame.h"
#include "hmac_p2p.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_P2P_C

/*****************************************************************************
  2 ��̬��������
*****************************************************************************/


/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
typedef struct mac_vap_state_priority
{
    oal_uint8                   uc_priority;
}mac_vap_state_priority_stru;

typedef struct hmac_input_req_priority
{
    oal_uint8                   uc_priority;
}hmac_input_req_priority_stru;

mac_vap_state_priority_stru g_mac_vap_state_priority_table[MAC_VAP_STATE_BUTT] =
{
     {0} ,//{MAC_VAP_STATE_INIT
     {2} ,//{MAC_VAP_STATE_UP                    /* VAP UP */
     {0} ,//{MAC_VAP_STATE_PAUSE                 /* pause , for ap &sta */
            ///* ap ����״̬ */
     {0} ,//{MAC_VAP_STATE_AP_PAUSE
            ///* sta����״̬ */
     {0} ,//{MAC_VAP_STATE_STA_FAKE_UP
     {10},//{MAC_VAP_STATE_STA_WAIT_SCAN
     {0} ,//{MAC_VAP_STATE_STA_SCAN_COMP
     {10},//{MAC_VAP_STATE_STA_JOIN_COMP
     {10},//{MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2
     {10},//{MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4
     {10},//{MAC_VAP_STATE_STA_AUTH_COMP
     {10},//{MAC_VAP_STATE_STA_WAIT_ASOC
     {10},//{MAC_VAP_STATE_STA_OBSS_SCAN
     {10},//{MAC_VAP_STATE_STA_BG_SCAN
     {0},//MAC_VAP_STATE_STA_LISTEN/* p2p0 ���� */
};

hmac_input_req_priority_stru g_mac_fsm_input_type_priority_table[HMAC_FSM_INPUT_TYPE_BUTT] =
{
    {0},/* HMAC_FSM_INPUT_RX_MGMT */
    {0},/* HMAC_FSM_INPUT_RX_DATA */
    {0},/* HMAC_FSM_INPUT_TX_DATA */
    {0},/* HMAC_FSM_INPUT_TIMER0_OUT */
    {0},/* HMAC_FSM_INPUT_MISC */

    {0},/* HMAC_FSM_INPUT_START_REQ */

    {5},/* HMAC_FSM_INPUT_SCAN_REQ */
    {5},/* HMAC_FSM_INPUT_JOIN_REQ */
    {5},/* HMAC_FSM_INPUT_AUTH_REQ */
    {5},/* HMAC_FSM_INPUT_ASOC_REQ */

    {5}, /* HMAC_FSM_INPUT_LISTEN_REQ *//* P2P ���� */
    {0}  /* HMAC_FSM_INPUT_LISTEN_TIMEOUT*/ /* P2P ������ʱ */
};


/*****************************************************************************
 �� �� ��  : hmac_p2p_check_can_enter_state
 ��������  : ����ⲿ�����¼��Ƿ�����ִ��
 �������  : mac_vap_stru *pst_mac_vap
             hmac_fsm_input_type_enum_uint8 en_input_req
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_p2p_check_can_enter_state(mac_vap_stru *pst_mac_vap,
                                            hmac_fsm_input_type_enum_uint8 en_input_req)
{
    mac_device_stru         *pst_mac_device;
    mac_vap_stru            *pst_other_vap;
    oal_uint8                uc_vap_num;
    oal_uint8                uc_vap_idx;

    /* 2.1 �������vap ״̬���ж������¼����ȼ��Ƿ��vap ״̬���ȼ���
    *  ��������¼����ȼ��ߣ������ִ�������¼�
    */
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_p2p_check_can_enter_state::mac_res_get_dev fail.device_id = %u}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_vap_num      = pst_mac_device->uc_vap_num;

    for (uc_vap_idx = 0; uc_vap_idx < uc_vap_num; uc_vap_idx++)
    {
        pst_other_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_other_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_p2p_check_can_enter_state::hmac_res_get_mac_vap fail.vap_idx = %u}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (pst_other_vap->uc_vap_id == pst_mac_vap->uc_vap_id)
        {
            /* �����⵽���Լ���������������VAP ״̬ */
            continue;
        }
        if (g_mac_vap_state_priority_table[pst_other_vap->en_vap_state].uc_priority
            > g_mac_fsm_input_type_priority_table[en_input_req].uc_priority)
        {
            return OAL_ERR_CODE_CONFIG_BUSY;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_p2p_get_home_channel
 ��������  : �����Ѿ�UP ��vap ���ŵ�
 �������  : mac_vap_stru                     *pst_mac_vap
             oal_uint32                        *pul_home_channel
             wlan_channel_bandwidth_enum_uint8 *pen_home_channel_type
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_p2p_get_home_channel(mac_vap_stru                     *pst_mac_vap,
                                    oal_uint32                        *pul_home_channel,
                                    wlan_channel_bandwidth_enum_uint8 *pen_home_channel_bandwidth)
{
    mac_device_stru         *pst_mac_device;
    oal_uint8                uc_vap_idx;

    oal_uint32               ul_home_channel = 0;
    oal_uint32               ul_last_home_channel = 0;
    wlan_channel_bandwidth_enum_uint8   en_home_channel_bandwidth      = WLAN_BAND_WIDTH_20M;
    wlan_channel_bandwidth_enum_uint8   en_last_home_channel_bandwidth = WLAN_BAND_WIDTH_20M;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{hmac_p2p_get_home_channel::pst_mac_vap is NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ�� */
    pst_mac_device              = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_p2p_get_home_channel::mac_res_get_dev fail.device_id = %u}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    *pul_home_channel           = 0;
    *pen_home_channel_bandwidth = WLAN_BAND_WIDTH_20M;

    /* ��ȡhome �ŵ� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_p2p_get_home_channel::hmac_res_get_mac_vap fail.vap_idx = %u}", uc_vap_idx);
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state)
        {
            ul_home_channel              = pst_mac_vap->st_channel.uc_chan_number;
            en_home_channel_bandwidth    = pst_mac_vap->st_channel.en_bandwidth;

            if (0 == ul_last_home_channel)
            {
                ul_last_home_channel           = ul_home_channel;
                en_last_home_channel_bandwidth = en_home_channel_bandwidth;
            }
            else if (ul_last_home_channel != ul_home_channel
                        || en_last_home_channel_bandwidth != en_home_channel_bandwidth)
            {
                /* TBD:Ŀǰ�ݲ�֧�ֲ�ͬ�ŵ���listen */
                OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                                "{hmac_p2p_get_home_channel::failed.home_channel[%d], last_home_channel[%d],home bw[%d], last bw[%d].}",
                                ul_home_channel, ul_last_home_channel,
                                en_home_channel_bandwidth,en_last_home_channel_bandwidth);
                return OAL_FAIL;
            }
        }
    }

    *pul_home_channel           = ul_home_channel;
    *pen_home_channel_bandwidth = en_home_channel_bandwidth;
    
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_check_p2p_vap_num
 ��������  : ���vapʱ���P2P vap��num�Ƿ����Ҫ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_check_p2p_vap_num(mac_device_stru *pst_mac_device, wlan_p2p_mode_enum_uint8 en_p2p_mode)
{
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
        /* �ж��Ѵ�����P2P_DEVICE �����Ƿ�ﵽ���ֵ */
        /* P2P0ֻ�ܴ���1�����Ҳ�����AP���� */
        if (pst_mac_device->st_p2p_info.uc_p2p_device_num >= WLAN_MAX_SERVICE_P2P_DEV_NUM)
        {
            /* �Ѵ�����P2P_DEV�����ﵽ���ֵ */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_config_check_vap_num::have created 1 p2p_device.can not create p2p_device any more[%d].}", pst_mac_device->st_p2p_info.uc_p2p_device_num);
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }

        /* ʣ����Դ�Ƿ��㹻����һ��P2P_DEV */
        if (pst_mac_device->uc_sta_num >= WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE)
        {
            /* ����AP���� */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_check_p2p_vap_num::can not create p2p_device any more[uc_sta_num:%d].}",
                        pst_mac_device->uc_sta_num);
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }

    }
    else if (WLAN_P2P_CL_MODE == en_p2p_mode)
    {
        /* �ж��Ѵ�����P2P_CLIENT �����Ƿ�ﵽ���ֵ */
        if (pst_mac_device->st_p2p_info.uc_p2p_goclient_num >= WLAN_MAX_SERVICE_P2P_GOCLIENT_NUM)
        {
            /* �Ѵ�����P2P_DEV�����ﵽ���ֵ */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_check_p2p_vap_num::have created 1 p2p_GO/Client.can not createany more[%d].}",
                        pst_mac_device->st_p2p_info.uc_p2p_goclient_num);
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }

        /* P2P0�Ƿ��Ѿ����� */
        if (pst_mac_device->st_p2p_info.uc_p2p_device_num != WLAN_MAX_SERVICE_P2P_DEV_NUM)
        {
            /* ����AP���� */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_check_p2p_vap_num::there ia no p2p0 %d,so can not create p2p_CL.}"
                    ,pst_mac_device->st_p2p_info.uc_p2p_device_num);
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }
    }
    else if (WLAN_P2P_GO_MODE == en_p2p_mode)
    {
        /* �ж��Ѵ�����P2P_CL/P2P_GO �����Ƿ�ﵽ���ֵ */
        if (pst_mac_device->st_p2p_info.uc_p2p_goclient_num >= WLAN_MAX_SERVICE_P2P_GOCLIENT_NUM)
        {
            /* �Ѵ�����P2P_DEV�����ﵽ���ֵ */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_check_p2p_vap_num::have created 1 p2p_GO/Client.can not createany more[%d].}", pst_mac_device->st_p2p_info.uc_p2p_goclient_num);
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }
        /* �Ƿ����㹻��AP vapģʽ��Դ������һ��P2P_GO */
        if ((pst_mac_device->uc_vap_num - pst_mac_device->uc_sta_num) >= WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE)
        {
            /* �Ѵ�����AP�����ﵽ���ֵ4 */
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_check_p2p_vap_num::ap num exceeds the supported spec[%d].}",
                        (pst_mac_device->uc_vap_num - pst_mac_device->uc_sta_num));
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }
    }
    else
    {
        return OAL_ERR_CODE_INVALID_CONFIG; /* ��δ�����Ч���� */
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_add_p2p_cl_vap
 ��������  : ����P2P CL ҵ��VAP
 �������  : pst_vap   : ָ������vap
             us_len    : ��������
             puc_param : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��12��31��
     ��    ��   : z00273164
     �޸�����   : �����ɺ���


*****************************************************************************/
oal_uint32  hmac_add_p2p_cl_vap(mac_vap_stru *pst_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_add_vap_param_stru    *pst_param;
    hmac_vap_stru                 *pst_hmac_vap;
    oal_uint32                     ul_ret;
    mac_device_stru               *pst_dev;
    oal_uint8                      uc_vap_id;
    wlan_p2p_mode_enum_uint8       en_p2p_mode;


    pst_param      = (mac_cfg_add_vap_param_stru *)puc_param;
    pst_dev        = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_add_p2p_cl_vap::pst_dev null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* VAP�����ж� */
    en_p2p_mode = pst_param->en_p2p_mode;
    ul_ret = hmac_check_p2p_vap_num(pst_dev, en_p2p_mode);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_add_p2p_cl_vap::hmac_config_check_vap_num failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* P2P CL ��P2P0 ����һ��VAP �ṹ������P2P CL ʱ����Ҫ����VAP ��Դ����Ҫ����p2p0 ��vap �ṹ */
    uc_vap_id    = pst_dev->st_p2p_info.uc_p2p0_vap_idx;
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_add_p2p_cl_vap::mac_res_get_hmac_vap failed.vap_id:[%d].}", uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;

    }

    pst_param->uc_vap_id = uc_vap_id;
    pst_hmac_vap->pst_net_device = pst_param->pst_net_dev;

    /* ����'\0' */
    oal_memcopy(pst_hmac_vap->auc_name, pst_param->pst_net_dev->name,OAL_IF_NAME_SIZE);

    /* �����뵽��mac_vap�ռ�ҵ�net_device privָ����ȥ */
    OAL_NET_DEV_PRIV(pst_param->pst_net_dev) = &pst_hmac_vap->st_vap_base_info;

    pst_param->us_muti_user_id = pst_hmac_vap->st_vap_base_info.us_multi_user_idx;

    /***************************************************************************
        ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info,
                                    WLAN_CFGID_ADD_VAP,
                                    us_len,
                                    puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* �쳣�����ͷ��ڴ� */
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_add_p2p_cl_vap::hmac_config_alloc_event failed[%d].}", ul_ret);
        return ul_ret;
    }


    if (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode)
    {
        /* ��ʼ��uc_assoc_vap_idΪ���ֵ����apδ���� */
        mac_vap_set_assoc_id(&pst_hmac_vap->st_vap_base_info, 0xff);
    }
    mac_vap_set_p2p_mode(&pst_hmac_vap->st_vap_base_info, pst_param->en_p2p_mode);
    mac_inc_p2p_num(&pst_hmac_vap->st_vap_base_info);

    /* ����֡���� */
    hmac_set_rx_filter_value(&pst_hmac_vap->st_vap_base_info);

    OAM_INFO_LOG3(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_add_p2p_cl_vap::func out.vap_mode[%d], p2p_mode[%d}, vap_id[%d]",
                        pst_param->en_vap_mode, pst_param->en_p2p_mode, pst_param->uc_vap_id);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_del_p2p_cl_vap
 ��������  : ɾ��p2p cl vap
 �������  : pst_vap   : ָ��vap��ָ��
             us_len    : ��������
             puc_param : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_del_p2p_cl_vap(mac_vap_stru *pst_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_vap_stru                 *pst_hmac_vap;
    oal_uint32                     ul_ret;
    mac_device_stru               *pst_device;
    oal_uint8                      uc_vap_id;
    mac_cfg_del_vap_param_stru    *pst_del_vap_param;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{hmac_config_del_vap::param null,pst_vap=%d puc_param=%d.}", pst_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_del_vap_param = (mac_cfg_del_vap_param_stru *)puc_param;

    pst_device        = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_del_vap::pst_device null.devid[%d]}", pst_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* �����ɾ��P2P CL ������Ҫ�ͷ�VAP ��Դ */
    uc_vap_id    = pst_device->st_p2p_info.uc_p2p0_vap_idx;
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_del_vap::mac_res_get_hmac_vap fail.vap_id[%d]}", uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hmac_vap->pst_net_device = pst_hmac_vap->pst_p2p0_net_device;

    mac_dec_p2p_num(&pst_hmac_vap->st_vap_base_info);
    mac_vap_set_p2p_mode(&pst_hmac_vap->st_vap_base_info, WLAN_P2P_DEV_MODE);
    //pst_hmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_hmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    oal_memcopy(pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    if (OAL_PTR_NULL != pst_hmac_vap->puc_asoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_hmac_vap->puc_asoc_req_ie_buff, OAL_TRUE);
        pst_hmac_vap->puc_asoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_vap->ul_asoc_req_ie_len   = 0;
    }

    /***************************************************************************
                          ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_vap,
                                    WLAN_CFGID_DEL_VAP,
                                    us_len,
                                    puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_del_p2p_cl_vap::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG2(pst_vap->uc_vap_id, OAM_SF_ANY, "{hmac_del_p2p_cl_vap::func out.vap_mode[%d], p2p_mode[%d]}",
                pst_del_vap_param->en_vap_mode, pst_del_vap_param->en_p2p_mode);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_p2p_send_listen_expired_to_host
 ��������  : ������ʱ����,֪ͨWAL ������ʱ
 �������  : mac_device_stru *pst_mac_device
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_p2p_send_listen_expired_to_host(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru                 *pst_mac_device;
    frw_event_mem_stru              *pst_event_mem;
    frw_event_stru                  *pst_event;
    oal_wireless_dev_stru           *pst_wdev;
    mac_p2p_info_stru               *pst_p2p_info;
    hmac_p2p_listen_expired_stru    *pst_p2p_listen_expired;


    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{hmac_send_mgmt_to_host::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_p2p_info = &pst_mac_device->st_p2p_info;

    /* ��װ�¼���WAL ���ϱ��������� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_p2p_listen_expired_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P, "{hmac_send_mgmt_to_host::pst_event_mem null.}");
        return OAL_FAIL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_LISTEN_EXPIRED,
                       OAL_SIZEOF(hmac_p2p_listen_expired_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ��д�ϱ�������ʱ, �ϱ��������豸Ӧ�ò���p2p0 */
    if (pst_hmac_vap->pst_p2p0_net_device && pst_hmac_vap->pst_p2p0_net_device->ieee80211_ptr)
    {
        pst_wdev = pst_hmac_vap->pst_p2p0_net_device->ieee80211_ptr;
    }
    else
    {
        pst_wdev = pst_hmac_vap->pst_net_device->ieee80211_ptr;
    }
    pst_p2p_listen_expired = (hmac_p2p_listen_expired_stru *)(pst_event->auc_event_data);
    pst_p2p_listen_expired->st_listen_channel = pst_p2p_info->st_listen_channel;
    pst_p2p_listen_expired->pst_wdev          = pst_wdev;

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_p2p_send_listen_expired_to_device
 ��������  : ������ʱ����֪ͨDMAC ����home �ŵ�
 �������  : hmac_vap_stru *pst_hmac_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��25��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_p2p_send_listen_expired_to_device(hmac_vap_stru *pst_hmac_vap)
{
    mac_device_stru                 *pst_mac_device;
    mac_vap_stru                    *pst_mac_vap;
    mac_p2p_info_stru               *pst_p2p_info;
    oal_uint32                       ul_ret;
    hmac_device_stru                *pst_hmac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                        "{hmac_p2p_send_listen_expired_to_device::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
                    "{hmac_p2p_send_listen_expired_to_device:: listen timeout!.}");

    /***************************************************************************
     ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/

    pst_p2p_info = &pst_mac_device->st_p2p_info;
    pst_mac_vap  = &pst_hmac_vap->st_vap_base_info;
    ul_ret = hmac_config_send_event(pst_mac_vap,
                                    WLAN_CFGID_CFG80211_CANCEL_REMAIN_ON_CHANNEL,
                                    OAL_SIZEOF(mac_p2p_info_stru),
                                    (oal_uint8 *)pst_p2p_info);

    /* ǿ��stop listen */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_p2p_send_listen_expired_to_device::pst_hmac_device[%d] null!}", pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_TRUE == pst_hmac_device->st_scan_mgmt.en_is_scanning)
    {
        pst_hmac_device->st_scan_mgmt.en_is_scanning = OAL_FALSE;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{hmac_p2p_send_listen_expired_to_device::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_disable_p2p_pm
 ��������  : ֹͣp2p noa,p2p oppps
 �������  : hmac_vap_stru *pst_hmac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��11��
    ��    ��   : xiaoyuren 00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_disable_p2p_pm(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru                   *pst_mac_vap;
    mac_cfg_p2p_ops_param_stru      st_p2p_ops;
    mac_cfg_p2p_noa_param_stru      st_p2p_noa;
    oal_uint32                      ul_ret;

    pst_mac_vap  =  &(pst_hmac_vap->st_vap_base_info);

    OAL_MEMZERO(&st_p2p_noa, OAL_SIZEOF(st_p2p_noa));
    ul_ret = hmac_config_set_p2p_ps_noa(pst_mac_vap, OAL_SIZEOF(mac_cfg_p2p_noa_param_stru), (oal_uint8 *)&st_p2p_noa);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
        "{hmac_disable_p2p_pm::hmac_config_set_p2p_ps_noa disable p2p NoA fail.}");
    }
    OAL_MEMZERO(&st_p2p_ops, OAL_SIZEOF(st_p2p_ops));
    ul_ret = hmac_config_set_p2p_ps_ops(pst_mac_vap, OAL_SIZEOF(mac_cfg_p2p_ops_param_stru), (oal_uint8 *)&st_p2p_ops);
    if (ul_ret != OAL_SUCC)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_P2P,
        "{hmac_disable_p2p_pm::hmac_config_set_p2p_ps_ops disable p2p OppPS fail.}");
    }
}

/*****************************************************************************
 �� �� ��  : hmac_is_p2p_go_neg_req_frame
 ��������  : �Ƿ���P2P GO negotiation request action֡
 �������  : oal_uint8 *puc_data
 �������  : ��
 �� �� ֵ  : OAL_TRUE ��P2P GO negotiation request action֡
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_is_p2p_go_neg_req_frame(OAL_CONST oal_uint8* puc_data)
{
    if((MAC_ACTION_CATEGORY_PUBLIC == puc_data[MAC_ACTION_OFFSET_CATEGORY + MAC_80211_FRAME_LEN])&&
        (WFA_OUI_BYTE1== puc_data[P2P_PUB_ACT_OUI_OFF1 + MAC_80211_FRAME_LEN])&&
        (WFA_OUI_BYTE2== puc_data[P2P_PUB_ACT_OUI_OFF2+ MAC_80211_FRAME_LEN])&&
        (WFA_OUI_BYTE3== puc_data[P2P_PUB_ACT_OUI_OFF3+ MAC_80211_FRAME_LEN])&&
        (WFA_P2P_v1_0== puc_data[P2P_PUB_ACT_OUI_TYPE_OFF+ MAC_80211_FRAME_LEN])&&
        (P2P_PAF_GON_REQ== puc_data[P2P_PUB_ACT_OUI_SUBTYPE_OFF + MAC_80211_FRAME_LEN]))
        return OAL_TRUE;
    else
        return OAL_FALSE;
}


/*****************************************************************************
 �� �� ��  : hmac_get_p2p_status
 ��������  : �ж�p2p �Ƿ�Ϊ��״̬
 �������  : oal_uint32 ul_p2p_status
             hmac_cfgp2p_status_enum_uint32 en_status
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 hmac_get_p2p_status(oal_uint32 ul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status)
{
    if (ul_p2p_status & BIT(en_status))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_set_p2p_status
 ��������  : ����p2p Ϊ��Ӧ״̬
 �������  : oal_uint32 ul_p2p_status
             hmac_cfgp2p_status_enum_uint32 en_status
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_set_p2p_status(oal_uint32 *pul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status)
{
    *pul_p2p_status |= ((oal_uint32)BIT(en_status));
}

/*****************************************************************************
 �� �� ��  : hmac_clr_p2p_status
 ��������  : ���p2p ��Ӧ״̬
 �������  : oal_uint32 ul_p2p_status
             hmac_cfgp2p_status_enum_uint32 en_status
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_clr_p2p_status(oal_uint32 *pul_p2p_status, hmac_cfgp2p_status_enum_uint32 en_status)
{
    *pul_p2p_status &= ~((oal_uint32)BIT(en_status));
}


/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_get_p2p_status);
oal_module_symbol(hmac_set_p2p_status);
oal_module_symbol(hmac_clr_p2p_status);
/*lint +e578*//*lint +e19*/

#endif /* _PRE_WLAN_FEATURE_P2P */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


