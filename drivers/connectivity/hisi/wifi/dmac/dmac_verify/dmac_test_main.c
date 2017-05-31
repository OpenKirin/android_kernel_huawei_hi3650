/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_test_main.c
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
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_test_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_MAIN_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define DMAC_TEST_OFFSET(type, member) ((long) &((type *) 0)->member)

dmac_test_mng_stru  g_st_dmac_test_mng;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_test_init
 ��������  :
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
oal_void  dmac_test_init(oal_void)
{
    OAL_MEMZERO(&g_st_dmac_test_mng, OAL_SIZEOF(dmac_test_mng_stru));

    dmac_test_encap_init(g_st_dmac_test_mng.ast_dmac_encap_frame);

    dmac_test_lpm_wow_init();
}

/*****************************************************************************
 �� �� ��  : dmac_test_get_encap_frame
 ��������  : ��ȡencap frame����ָ������ͷ
 �������  :
 �������  : ��
 �� �� ֵ  :encap frame����ָ������ͷ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
dmac_test_encap_frame *dmac_test_get_encap_frame(oal_void)
{
    return g_st_dmac_test_mng.ast_dmac_encap_frame;
}

/*****************************************************************************
 �� �� ��  : dmac_test_set_software_retry
 ��������  : ����������retryλ
 �������  : puc_param: �����ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_set_software_retry(oal_uint8 * puc_param)
{
    mac_cfg_set_soft_retry_stru *puc_soft_retry = (mac_cfg_set_soft_retry_stru *)puc_param;
    g_st_dmac_test_mng.uc_software_retry = puc_soft_retry->uc_software_retry;
    g_st_dmac_test_mng.uc_retry_test = puc_soft_retry->uc_retry_test;
}


/*****************************************************************************
 �� �� ��  : dmac_test_set_software_retry
 ��������  : ���üĴ���retryλ
 �������  : pst_hal_device: dev
             pst_tx_dscr:������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_set_dscr_software_retry(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    if (0 == g_st_dmac_test_mng.uc_retry_test)
    {
        return;
    }
    hal_tx_set_dscr_seqno_sw_generate(pst_hal_device, pst_tx_dscr, g_st_dmac_test_mng.uc_software_retry);
}


/*****************************************************************************
 �� �� ��  : dmac_test_open_addr4
 ��������  : ����4��ַ��macͷΪ4��ַ
 �������  : puc_add4_open: ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_open_addr4(oal_uint8 *puc_add4_open)
{
    g_st_dmac_test_mng.uc_add4_open = *puc_add4_open;
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_get_addr4
 ��������  : ��ȡ��ʶ
 �������  : puc_add4_open: ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_get_addr4(oal_uint8 *puc_add4_open)
{
    *puc_add4_open = g_st_dmac_test_mng.uc_add4_open ;
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_set_addr4
 ��������  : ������֡ͷת����4��ַģʽ��hmac����������ͷ�ռ��ʱ���Ѿ�����4��ַ
             ģʽ����ռ䣬������������ռ�
 �������  : pst_hal_device: dev
             pst_tx_dscr:������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_set_addr4(hal_tx_dscr_stru * pst_tx_dscr)
{
    mac_ieee80211_qos_frame_addr4_stru          st_qos_addr4;
    mac_ieee80211_qos_frame_stru               *pst_qos = NULL;
    oal_uint8                                  *pst_cb = NULL;
    mac_tx_ctl_stru                            *pst_tx_ctrl = NULL;
    oal_uint32                                  ul_len;
    oal_uint32                                  ul_left_len;
    if(0 == g_st_dmac_test_mng.uc_add4_open)
    {
       return;
    }

    pst_cb = OAL_NETBUF_CB(pst_tx_dscr->pst_skb_start_addr);
    pst_tx_ctrl = (mac_tx_ctl_stru *)pst_cb;
    pst_qos = (mac_ieee80211_qos_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctrl);

    oal_memset(&st_qos_addr4, 0, sizeof(mac_ieee80211_qos_frame_addr4_stru));
    /*lint -e413*/
    ul_len = DMAC_TEST_OFFSET(mac_ieee80211_qos_frame_addr4_stru, auc_address4);
    /*lint +e413*/
    ul_left_len = OAL_SIZEOF(mac_ieee80211_qos_frame_stru) - ul_len;
    /* ����addr4ǰ���ֶ� */
    oal_memcopy(&st_qos_addr4, pst_qos, ul_len);
    /* ����addr4�ֶ� */
    oal_memcopy(st_qos_addr4.auc_address4, pst_qos->auc_address3, OAL_MAC_ADDR_LEN);
    /* ����addr4����ֶ� */
    oal_memcopy((oal_uint8 *)&st_qos_addr4 + WLAN_MAC_ADDR_LEN + ul_len, (oal_uint8 *)pst_qos + ul_len, ul_left_len);

    /* ����TO DS��FROM DS */
    st_qos_addr4.st_frame_control.bit_from_ds = 1;
    st_qos_addr4.st_frame_control.bit_to_ds = 1;
    /* ������������֡ͷ����Ϊ4��ַ����  */
    oal_memcopy(mac_get_cb_frame_hdr(pst_tx_ctrl), &st_qos_addr4, OAL_SIZEOF(mac_ieee80211_qos_frame_addr4_stru));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl) = MAC_80211_QOS_4ADDR_FRAME_LEN;
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_set_chip_test
 ��������  : ��оƬ��֤���ܿ���
 �������  : puc_chip_test_open: ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_test_set_chip_test(oal_uint8 uc_chip_test_open)
{
    g_st_dmac_test_mng.uc_chip_test_open = uc_chip_test_open;
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_test_get_chip_test
 ��������  : ���оƬ��֤���ܿ���
 �������  :
 �������  : ��
 �� �� ֵ  : оƬ��֤���ܿ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_get_chip_test(oal_void)
{
    return g_st_dmac_test_mng.uc_chip_test_open;
}

/*****************************************************************************
 �� �� ��  : dmac_test_check_chip_test
 ��������  : ��֤�����DMAC_CHIP_TEST_CALL
 �������  :
 �������  : ��
 �� �� ֵ  : оƬ��֤���ܿ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_test_check_chip_test(oal_uint8 uc_value)
{
    DMAC_CHIP_TEST_CALL(dmac_test_set_chip_test(uc_value));
    return 0;
}

/*lint -e19*/
oal_module_symbol(g_st_dmac_test_mng);
oal_module_symbol(dmac_test_get_chip_test);
/*lint +e19*/

#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

