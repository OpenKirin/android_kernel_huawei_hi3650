/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_chip_test.c
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : оƬ��֤��dmac����Դ��롢׮������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : z52447
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
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_mgmt_ap.h"
#include "dmac_scan.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_LPM_TEST_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint32  dmac_scan_send_probe_req_frame(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_bssid, oal_int8 *pc_ssid);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_test_lpm_smps_set_rate
 ��������  : SMPS���Դ�׮�������������������÷��͵�11n�����ʡ�RTSʹ��. ����������Բ���SMPS����Ϊ�Ƿ���ȷ:
             1. �������ͣ�Ӧ�ÿ���ͨ
             2. ˫�����ͣ�����RTS��Ӧ�ò���ͨ
             3. ˫�����ͣ��ȷ�RTS��Ӧ�ÿ���ͨ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_smps_set_rate(mac_tx_ctl_stru *pst_tx_ctl, hal_tx_txop_alg_stru *pst_txop_alg,dmac_test_stub_opera_enum_uint8 en_opera)
{
    dmac_lpm_smps_tx_stub_stru          *pst_smps_stub ;
    hal_tx_txop_per_rate_params_union   *past_rate_param;

    pst_smps_stub = &g_st_dmac_test_mng.st_lpm_smps_stub;
    past_rate_param = pst_txop_alg->ast_per_rate;

    if ((0 == pst_smps_stub->uc_stub_type)||(OAL_PTR_NULL == pst_tx_ctl))
    {
        return;
    }

    /*�㲥���鲥���������RTS�Ļ����Զ˲����CTS*/
    if(OAL_TRUE == pst_tx_ctl->en_ismcast)
    {
        return;
    }

    /*��׮��ʼ������ԭʼ���ݣ���׮����*/
    if (DMAC_TEST_STUB_BEGIN == en_opera)
    {
        pst_smps_stub->ul_rate_real[0] = pst_txop_alg->ast_per_rate[0].ul_value;
        pst_smps_stub->ul_rate_real[1] = pst_txop_alg->ast_per_rate[1].ul_value;
        pst_smps_stub->ul_rate_real[2] = pst_txop_alg->ast_per_rate[2].ul_value;
        pst_smps_stub->ul_rate_real[3] = pst_txop_alg->ast_per_rate[3].ul_value;

        past_rate_param[0].rate_bit_stru.bit_tx_count = 1;
        past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode = WLAN_HT_PHY_PROTOCOL_MODE;

        /*�������ʷ���*/
        if (1 == pst_smps_stub->uc_stub_type)
        {
            /*mcs5,11nΪ����*/
            past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 5;
            past_rate_param[0].rate_bit_stru.bit_tx_chain_selection = 0x1;
        }

        /*˫�����ʷ���*/
        if (2 == pst_smps_stub->uc_stub_type)
        {
            /*mcs10,11nΪ˫��*/
            past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 10;

             /* ����ͨ��ѡ�� (��ͨ��:0x1, ˫ͨ��:0x3, ��ͨ��:0x7, ��ͨ��:0xf) */
            past_rate_param[0].rate_bit_stru.bit_tx_chain_selection = 0x3;
        }

        past_rate_param[0].rate_bit_stru.bit_rts_cts_enable = (pst_smps_stub->uc_rts_en)?1:0;
        past_rate_param[1].rate_bit_stru.bit_tx_count = 0;
        past_rate_param[2].rate_bit_stru.bit_tx_count = 0;
        past_rate_param[3].rate_bit_stru.bit_tx_count = 0;
    }
    else
    {
         pst_txop_alg->ast_per_rate[0].ul_value = pst_smps_stub->ul_rate_real[0];
         pst_txop_alg->ast_per_rate[1].ul_value = pst_smps_stub->ul_rate_real[1];
         pst_txop_alg->ast_per_rate[2].ul_value = pst_smps_stub->ul_rate_real[2] ;
         pst_txop_alg->ast_per_rate[3].ul_value = pst_smps_stub->ul_rate_real[3];
    }

    return;

}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_txopps_en
 ��������  : TXOP PS���Կ���,��1ʱ,���ն˲Ż�ͳ�ƽ��յ��ò��Ա��ĵĸ��������عر�ʱ��
             ���������㡣
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_txopps_en(oal_uint8 uc_en)
{
    g_st_dmac_test_mng.uc_txop_ps_en = uc_en;
    if(0 == uc_en)
    {
        g_st_dmac_test_mng.us_txop_rx_cnt = 0;
    }

}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_txopps_rx_count()
 ��������  : TXOP PS���Կ�����1ʱ,���ն�ͳ�ƽ��յ��Ĳ��Ա��ĵĸ������������ͳ�Ƴ��ȴ���
             128�ֽڵı���,����ʱ��Ҫ��AP�෢128�����ֽڵı��ġ�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_txopps_rx_count(oal_uint16 us_pkt_len)
{
    if ((1 == g_st_dmac_test_mng.uc_txop_ps_en)&& (us_pkt_len>=128))
    {
        g_st_dmac_test_mng.us_txop_rx_cnt++;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_txopps_debug()
 ��������  : ��ӡ���ն�ͳ�ƽ��յ��Ĳ��Ա��ĵĸ������������ͳ�Ƴ��ȴ���
             128�ֽڵı���,����ʱ��Ҫ��AP�෢128�����ֽڵı��ġ�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_txopps_debug(oal_void)
{
   OAM_INFO_LOG1(0, OAM_SF_ANY, "Receive test pkt cnt = %d\n",g_st_dmac_test_mng.us_txop_rx_cnt);
}


/*****************************************************************************
 �� �� ��  : dmac_test_lpm_txopps_set_partial_aid
 ��������  : TXOP PS���Դ�׮����׮��ʼʱ����Partial AID��׮����׮����ʱ���ָ�ԭ����ֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_txopps_set_partial_aid(dmac_vap_stru         *pst_dmac_vap,
                                                          dmac_user_stru        *pst_dmac_user,
                                                          dmac_test_stub_opera_enum_uint8 en_opera)
{
    dmac_lpm_txopps_tx_stub_stru* pst_txop_stub;

    pst_txop_stub = &g_st_dmac_test_mng.st_lpm_txop_stub;

    /*0:off, 1:on*/
    if (0 == pst_txop_stub->uc_stub_on)
    {
        return;
    }

    /*��׮��ʼ������ԭʼ���ݣ���׮����*/
    if (DMAC_TEST_STUB_BEGIN == en_opera)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_txopps_set_partial_aid::start %d}\r\n",
                            pst_txop_stub->us_curr_num);
        pst_txop_stub->us_curr_num++;
        if (pst_txop_stub->us_begin_num != pst_txop_stub->us_curr_num)
        {
            return;
        }

        /*���ô����partial aid,STA���յ�PAID���Ǻ�����ƥ��󣬽���TXOP���� */
        pst_txop_stub->us_partial_aid_real =  pst_dmac_user->us_partial_aid;
        pst_dmac_user->us_partial_aid = 123;

     }
     else if (DMAC_TEST_STUB_END == en_opera)
     {
        /*��׮���������ݻָ�*/
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_txopps_set_partial_aid::end}\r\n");
        if (pst_txop_stub->us_begin_num == pst_txop_stub->us_curr_num)
        {
            pst_dmac_user->us_partial_aid = pst_txop_stub->us_partial_aid_real;
        }
     }

     return ;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_send_probe_requst
 ��������  : �������������������probe request���ģ�WOW������
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_lpm_send_probe_requst(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_positive,oal_uint8* puc_bssid)
{
    oal_int8    ac_ssid[4] = {'\0'};
    oal_uint32  ul_ret;

    /* ������ʽ��������ַΪ�㲥��ַ */
    if (0 == uc_positive)
    {

        ul_ret = dmac_scan_send_probe_req_frame(pst_dmac_vap, BROADCAST_MACADDR, ac_ssid);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_send_probe_requst::failed to send broadcast probe req! ul_ret=%d}\r\n", ul_ret);
        }
    }
    /* ������ʽ��������ַΪָ��BSSID */
    else
    {
        ul_ret = dmac_scan_send_probe_req_frame(pst_dmac_vap, puc_bssid, ac_ssid);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_send_probe_requst::failed to send bssid probe req! ul_ret=%d}\r\n", ul_ret);
        }
    }

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_int_proc
 ��������  : wow��CPU�����жϴ�����,���Խ�����,����֤wifiоƬ�Ƿ��˻����ź�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_wow_int_proc(oal_void)
{
    g_st_dmac_test_mng.ul_wow_int_cnt++;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_init
 ��������  : wow���Գ�ʼ��������CPU��ע�ỽ���жϴ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_wow_init(oal_void)
{
#ifdef _PRE_BOARD_SD5115
    hi_gpio_bit_attr_s          st_attr;

    /*WOW����GPIO�ܽ�ΪGPIO 62����ӦHI_GPIO_PORT1_E, HI_GPIO_BIT30_E*/
    HI_GPIO_PORT_E              em_port     = HI_GPIO_PORT1_E;
    HI_GPIO_BIT_E               em_bit      = HI_GPIO_BIT30_E;

    /*1. ��ȡ����*/
    hi_kernel_gpio_bit_attr_get(em_port, em_bit, &st_attr);

    /*��GPIO�ܽ�����ΪINPUTģʽ*/
    st_attr.em_mode = HI_GPIO_WORK_MODE_INPUT_E;

    hi_kernel_gpio_bit_attr_set(em_port, em_bit, &st_attr);


#endif
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_set_wow_en
 ��������  : ����ȫ��wowʹ�ܿ���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_set_wow_en(oal_uint8 uc_en)
{
     g_st_dmac_test_mng.uc_wow_en = uc_en;

     if(OAL_FALSE == uc_en)
     {
        g_st_dmac_test_mng.ul_wow_int_cnt = 0;
     }

}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_get_wow_en
 ��������  : ��ȡȫ��wowʹ�ܿ���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 dmac_test_lpm_get_wow_en(oal_void)
{
     return g_st_dmac_test_mng.uc_wow_en ;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_debug
 ��������  : WOW���ԣ���ʾ�жϴ���ͳ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_wow_debug(oal_void)
{

#ifdef _PRE_BOARD_SD5115

     hi_gpio_bit_attr_s          st_attr;

     /*WOW����GPIO�ܽ�ΪGPIO 62����ӦHI_GPIO_PORT1_E, HI_GPIO_BIT30_E*/
     HI_GPIO_PORT_E              em_port     = HI_GPIO_PORT1_E;
     HI_GPIO_BIT_E               em_bit      = HI_GPIO_BIT30_E;

     /*��ʼ��Ϊ�͵�ƽ*/
     HI_LEVEL_E                  em_level    = HI_LOW_LEVEL_E;

      /*��GPIO�ܽ�����ΪINPUTģʽ*/
     st_attr.em_mode = HI_GPIO_WORK_MODE_INPUT_E;

     hi_kernel_gpio_bit_attr_set(em_port, em_bit, &st_attr);

    /*��ȡ����*/
     hi_kernel_gpio_bit_attr_get(em_port, em_bit, &st_attr);

     OAM_INFO_LOG1(0, OAM_SF_ANY, "GPIO_62 attribute = %d\n",st_attr.em_mode);

     /*���ź�*/
     hi_kernel_gpio_bit_read( em_port,  em_bit, &em_level);

     if(HI_HIGH_LEVEL_E == em_level)
     {
        g_st_dmac_test_mng.ul_wow_int_cnt++;
     }
     OAM_INFO_LOG1(0, OAM_SF_ANY, "Current wow wakeup int count = %d\n",g_st_dmac_test_mng.ul_wow_int_cnt);

#endif
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_prepare_probe_resp
 ��������  : wow�����ã�׼��probe response֡
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_lpm_wow_prepare_probe_resp(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8       ast_dest_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};

    if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_probe_resp)
    {
        pst_dmac_vap->pst_wow_probe_resp = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
        if (OAL_PTR_NULL ==  pst_dmac_vap->pst_wow_probe_resp)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_wow_prepare_probe_resp::alloc mgmt buffer failed!}\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        OAL_NETBUF_PREV(pst_dmac_vap->pst_wow_probe_resp) = OAL_PTR_NULL;
        OAL_NETBUF_NEXT(pst_dmac_vap->pst_wow_probe_resp) = OAL_PTR_NULL;
    }

    /* ��װprobe response֡ */
    pst_dmac_vap->us_wow_probe_resp_len = dmac_mgmt_encap_probe_response(pst_dmac_vap, pst_dmac_vap->pst_wow_probe_resp, &ast_dest_addr[0], OAL_FALSE);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_release_probe_resp
 ��������  : �˳�wowģʽʱ���ͷ�Ϊmac׼����probe response֡��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_wow_release_probe_resp(dmac_vap_stru *pst_dmac_vap)
{
    if(OAL_PTR_NULL != pst_dmac_vap->pst_wow_probe_resp)
    {
        oal_netbuf_free(pst_dmac_vap->pst_wow_probe_resp);
        pst_dmac_vap->pst_wow_probe_resp    = OAL_PTR_NULL;
        pst_dmac_vap->us_wow_probe_resp_len = 0;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_prepare_null_data
 ��������  : WOW�����ã�Ϊmac׼����֡��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_lpm_wow_prepare_null_data(dmac_vap_stru *pst_dmac_vap)
{
    dmac_user_stru* pst_dmac_user;

    /*����ҪΪSTAģʽ��VAP׼��null data֡����keep alive*/
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            return OAL_FAIL;
        }

        if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_null_data)
        {
            /* ����net_buff */
            pst_dmac_vap->pst_wow_null_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
            if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_null_data)
            {
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_wow_prepare_null_data::alloc pst_net_buf fail!}\r\n");
                return OAL_ERR_CODE_ALLOC_MEM_FAIL;
            }

            OAL_NETBUF_PREV(pst_dmac_vap->pst_wow_null_data) = OAL_PTR_NULL;
            OAL_NETBUF_NEXT(pst_dmac_vap->pst_wow_null_data) = OAL_PTR_NULL;
        }

        /* ��д֡ͷ,����from dsΪ1��to dsΪ0�����frame control�ĵڶ����ֽ�Ϊ02 */
        mac_hdr_set_frame_control(oal_netbuf_header(pst_dmac_vap->pst_wow_null_data), (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | 0x0200);

        /* ����ADDR1ΪĿ�ĵ�ַ */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 4), pst_dmac_user->st_user_base_info.auc_user_mac_addr);

        /* ����ADDR2ΪSA */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 10),pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* ����ADDR3ΪBSSID */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 16), pst_dmac_vap->st_vap_base_info.auc_bssid);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_wow_release_null_data
 ��������  : �ͷ�ΪMAC׼����null data֡��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_lpm_wow_release_null_data(dmac_vap_stru *pst_dmac_vap)
{
    if (OAL_PTR_NULL != pst_dmac_vap->pst_wow_null_data)
    {
        oal_netbuf_free(pst_dmac_vap->pst_wow_null_data);
        pst_dmac_vap->pst_wow_null_data = OAL_PTR_NULL;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_test_lpm_tx_null_data
 ��������  : �����ã���������null data֡
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_lpm_send_nulldata(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_psm,oal_uint8* puc_da)
{
    oal_netbuf_stru             *pst_null_data;
    mac_tx_ctl_stru             *pst_tx_ctrl;
    oal_uint32                   ul_ret;
    mac_ieee80211_frame_stru    *pst_frame_hdr;
    dmac_user_stru              *pst_dmac_user;
    oal_uint16                   us_user_index;


    /* ����net_buff */
    pst_null_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_null_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata::alloc pst_net_buf fail!}\r\n");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_NETBUF_PREV(pst_null_data) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_null_data) = OAL_PTR_NULL;

    /* ��д֡ͷ,����from dsΪ1��to dsΪ0�����frame control�ĵڶ����ֽ�Ϊ02 */
    mac_hdr_set_frame_control(oal_netbuf_header(pst_null_data), (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | 0x0200);

    /* ����ADDR1ΪĿ�ĵ�ַ */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 4), puc_da);

    /* ����ADDR2ΪSA */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 10),pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ����ADDR3ΪBSSID */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 16), pst_dmac_vap->st_vap_base_info.auc_bssid);

    pst_frame_hdr = (mac_ieee80211_frame_stru*)oal_netbuf_header(pst_null_data);

    /* ���ý��ܱ��*/
    pst_frame_hdr->st_frame_control.bit_power_mgmt = uc_psm;

    /* ��дcb�ֶ� */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_null_data);
    OAL_MEMZERO(pst_tx_ctrl, OAL_NETBUF_CB_SIZE());

    /* ��дtx���� */
    pst_tx_ctrl->en_ack_policy            = WLAN_TX_NORMAL_ACK;
    pst_tx_ctrl->en_event_type            = FRW_EVENT_TYPE_WLAN_DTX;
    pst_tx_ctrl->en_is_bar                = OAL_FALSE;
    pst_tx_ctrl->uc_ac                    = WLAN_WME_AC_BE;
    pst_tx_ctrl->uc_is_first_msdu         = OAL_TRUE;
    pst_tx_ctrl->uc_retried_num           = 0;
    pst_tx_ctrl->uc_tid                   = WLAN_TID_FOR_DATA;
    pst_tx_ctrl->uc_tx_vap_index          = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_tx_ctrl->us_tx_user_idx       = pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id;

        pst_frame_hdr->st_frame_control.bit_from_ds = 0;
        pst_frame_hdr->st_frame_control.bit_to_ds   = 1;
    }
    else
    {
       /* ��ȡ�û���Ӧ������ */
        ul_ret = mac_vap_find_user_by_macaddr(&pst_dmac_vap->st_vap_base_info,puc_da, &us_user_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata:: not find user!");
            dmac_tx_excp_free_netbuf(pst_null_data);

            return ul_ret;
        }
        pst_dmac_user                     = (dmac_user_stru*)mac_res_get_dmac_user(us_user_index);
        pst_tx_ctrl->us_tx_user_idx       = pst_dmac_user->st_user_base_info.us_assoc_id;

        pst_frame_hdr->st_frame_control.bit_from_ds = 1;
        pst_frame_hdr->st_frame_control.bit_to_ds   = 0;

    }

    /* ��дtx rx�������� */
    //pst_tx_ctrl->en_frame_type             = WLAN_DATA_NULL;
    pst_tx_ctrl->en_ismcast                = OAL_FALSE;
    pst_tx_ctrl->en_is_amsdu               = OAL_FALSE;
    pst_tx_ctrl->en_is_get_from_ps_queue   = OAL_TRUE;
    pst_tx_ctrl->en_is_probe_data          = OAL_FALSE;
    pst_tx_ctrl->en_use_4_addr             = OAL_FALSE;
    pst_tx_ctrl->pst_frame_header          = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_null_data);
    pst_tx_ctrl->uc_frame_header_length    = OAL_SIZEOF(mac_ieee80211_frame_stru);
    pst_tx_ctrl->uc_mpdu_num               = 1;
    pst_tx_ctrl->uc_netbuf_num             = 1;
    pst_tx_ctrl->us_mpdu_len               = 0;

    ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_null_data);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata::sending null data fail!}\r\n");
        dmac_tx_excp_free_netbuf(pst_null_data);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_test_always_tx
 ��������  : �������������е�NEXT�������ֶ�ָ����
 �������  : pst_tx_dscr:������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_always_tx(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    /* ��ȡ�豸 */
    if (OAL_SWITCH_ON == pst_hal_device->uc_al_tx_flag)
    {
         hal_rf_test_enable_al_tx(pst_hal_device, pst_tx_dscr);
    }
}
/*****************************************************************************
 �� �� ��  : dmac_test_dfx_set_tx_cnt
 ��������  : �����ش�����Ϊ3
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_test_dfx_set_tx_cnt(hal_tx_txop_alg_stru *pst_txop_alg)
{
    hal_tx_txop_per_rate_params_union   *past_rate_param;

    if (OAL_SWITCH_OFF == g_st_dmac_test_mng.en_cfg_tx_cnt)
    {
        return;
    }

    past_rate_param = pst_txop_alg->ast_per_rate;

    past_rate_param[0].rate_bit_stru.bit_tx_count = 3;
    past_rate_param[1].rate_bit_stru.bit_tx_count = 0;
    past_rate_param[2].rate_bit_stru.bit_tx_count = 0;
    past_rate_param[3].rate_bit_stru.bit_tx_count = 0;
}


#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

