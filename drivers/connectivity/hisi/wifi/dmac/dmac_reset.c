/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_reset.c
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2013��11��7��
  ����޸�   :
  ��������   : �����λӲ������ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��11��7��
    ��    ��   : zourong 52447
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
#include "hal_ext_if.h"
#include "oal_net.h"
#include "oal_kernel_file.h"
#include "oal_mem.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_user.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_rx_data.h"
#include "dmac_tx_complete.h"
#include "dmac_11i.h"
#include "dmac_ext_if.h"
#include "dmac_reset.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "dmac_pm_sta.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RESET_C

#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC  oal_uint32 dmac_reset_lut_init(oal_void);
OAL_STATIC  oal_void dmac_reset_lut_destroy(oal_void);
OAL_STATIC oal_void dmac_reset_save_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array);
OAL_STATIC oal_void dmac_reset_restore_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array,oal_time_us_stru *pst_time_record);
#endif
oal_void dmac_reset_rx_dscr_queue_flush(hal_to_dmac_device_stru* pst_hal);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

oal_void dmac_reset_debug_init(oal_void);
oal_void dmac_reset_debug_close(oal_void);
oal_void dmac_reset_debug_to_file(oal_uint8* pst_str);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
#else
OAL_STATIC oal_uint32 dmac_reset_save_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut);
OAL_STATIC oal_uint32 dmac_reset_save_smartant_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_smartant_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_smartant_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_smartant_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_cipher_lut(mac_device_stru* pst_mac_device);
OAL_STATIC oal_uint32 dmac_reset_restore_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut);
OAL_STATIC oal_uint32 dmac_reset_save_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq);
OAL_STATIC oal_uint32 dmac_reset_save_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq);
OAL_STATIC oal_uint32 dmac_reset_save_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast);
OAL_STATIC oal_uint32 dmac_reset_restore_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast);
OAL_STATIC oal_uint32 dmac_reset_restore_peer_addr_lut(mac_device_stru* pst_mac_device);

#endif
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
dmac_reset_mng_stru g_st_dmac_reset_mng;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_reset_lut_init
 ��������  : ��λmac regʱ�����뱣��LUT���ֳ����ڴ�
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_init(oal_void)
{
   OAL_MEMZERO(&g_st_dmac_reset_mng, OAL_SIZEOF(dmac_reset_mng_stru));
#ifdef _PRE_WALN_FEATURE_LUT_RESET
    g_st_dmac_reset_mng.bit_pn_lut_reset         = 1;
    g_st_dmac_reset_mng.bit_key_lut_reset        = 1;
    g_st_dmac_reset_mng.bit_txbf_lut_reset       = 1;
    g_st_dmac_reset_mng.bit_smartant_lut_reset   = 1;
    g_st_dmac_reset_mng.bit_peer_addr_lut_reset  = 1;
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))|| (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
    g_st_dmac_reset_mng.bit_seq_lut_reset        = 1;
    g_st_dmac_reset_mng.bit_ba_lut_reset         = 1;
    g_st_dmac_reset_mng.bit_save_tx_fake_fifo    = 1;
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : dmac_reset_lut_init
 ��������  : ��λmac regʱ�����뱣��LUT���ֳ����ڴ�
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC  oal_uint32 dmac_reset_lut_init(oal_void)
{
   g_st_dmac_reset_mng.pst_tsf = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,(WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE+WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE)*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
   if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tsf)
   {
       dmac_reset_lut_destroy();
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
   }

   if(g_st_dmac_reset_mng.bit_seq_lut_reset)
   {
       g_st_dmac_reset_mng.pst_sequence_qos = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*WLAN_TID_MAX_NUM*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_sequence_qos)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_ba_lut_reset)
   {
       g_st_dmac_reset_mng.pst_ba_rx = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_MAX_RX_BA*WLAN_BA_LUT_ENTRY_SIZE*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_ba_rx)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_pn_lut_reset)
   {
       g_st_dmac_reset_mng.pst_rx_pn_ucast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_TID_MAX_NUM*WLAN_ACTIVE_USER_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_rx_pn_ucast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_tx_pn_ucast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tx_pn_ucast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_rx_pn_mcast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ASSOC_AP_MAX_NUM*WLAN_TID_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_rx_pn_mcast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_tx_pn_mcast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tx_pn_mcast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
   {
       g_st_dmac_reset_mng.pst_txbf = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_txbf)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }
   if(g_st_dmac_reset_mng.bit_smartant_lut_reset)
   {
       g_st_dmac_reset_mng.pst_smartant = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_smartant)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }
   return OAL_SUCC ;

}

/*****************************************************************************
 �� �� ��  : dmac_reset_lut_destroy
 ��������  : ��λmac regʱ���ͷű���LUT���ֳ����ڴ�
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  oal_void dmac_reset_lut_destroy(oal_void)
{

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tsf)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tsf, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tsf = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_sequence_qos)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_sequence_qos, OAL_TRUE);
       g_st_dmac_reset_mng.pst_sequence_qos = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_ba_rx)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_ba_rx, OAL_TRUE);
       g_st_dmac_reset_mng.pst_ba_rx = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_rx_pn_ucast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_rx_pn_ucast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_rx_pn_ucast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tx_pn_ucast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tx_pn_ucast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tx_pn_ucast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_rx_pn_mcast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_rx_pn_mcast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_rx_pn_mcast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tx_pn_mcast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tx_pn_mcast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tx_pn_mcast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_txbf)
   {
        OAL_MEM_FREE(g_st_dmac_reset_mng.pst_txbf, OAL_TRUE);
       g_st_dmac_reset_mng.pst_txbf = OAL_PTR_NULL;
   }
   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_smartant)
   {
        OAL_MEM_FREE(g_st_dmac_reset_mng.pst_smartant, OAL_TRUE);
       g_st_dmac_reset_mng.pst_smartant = OAL_PTR_NULL;
   }
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_reset_save_tx_queue
 ��������  : resetʱ���շ��Ͷ����е����ݵ�resetר����ٶ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC oal_uint32 dmac_reset_save_tx_queue(hal_to_dmac_device_stru *pst_hal_device)
{
    oal_netbuf_stru     *pst_fake_buf;

    hal_tx_dscr_queue_header_stru  *pst_fake_queue;

    if (OAL_FALSE == g_st_dmac_reset_mng.bit_save_tx_fake_fifo)
    {
        return OAL_SUCC;
    }

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_reset_save_tx_queue::pst_hal_device null.}");
        return OAL_FAIL;
    }

    /* ����fake_fifo_buff */
    pst_fake_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (HAL_TX_QUEUE_NUM * OAL_SIZEOF(hal_tx_dscr_queue_header_stru)), OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_fake_buf)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"dmac_reset_save_tx_queue::fake netbuff alloc error, device_id[%d]", pst_hal_device->uc_device_id);
        return OAL_ERR_CODE_HW_RESET_TX_QUEUE_MEMALLOC;
    }

    g_st_dmac_reset_mng.pst_fake_queue = pst_fake_buf;
    pst_fake_queue = (hal_tx_dscr_queue_header_stru *)OAL_NETBUF_PAYLOAD(pst_fake_buf);

    dmac_proc_save_tx_queue(pst_hal_device, pst_fake_queue);

    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : dmac_reset_restore_tx_queue
 ��������  : �ָ�Ӳ�����Ͷ����е�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_tx_queue(hal_to_dmac_device_stru *pst_hal_device)
{
    hal_tx_dscr_queue_header_stru   *pst_fake_queue;

    if (OAL_FALSE == g_st_dmac_reset_mng.bit_save_tx_fake_fifo)
    {
        return OAL_SUCC;
    }

    pst_fake_queue = (hal_tx_dscr_queue_header_stru *)OAL_NETBUF_PAYLOAD(g_st_dmac_reset_mng.pst_fake_queue);

    dmac_proc_restore_tx_queue(pst_hal_device, pst_fake_queue);
    oal_netbuf_free(g_st_dmac_reset_mng.pst_fake_queue);

    return OAL_SUCC;

}
#endif
/*****************************************************************************
 �� �� ��  : dmac_reset_hw
 ��������  : reset hw�����
 �������  : uc_type:
                 0x01����λmac
                 0x10����λphy
                 0x11:  ��λmac&phy
             sub_module:
                 ��uc_type = 0x01,����λMACʱ��
                 0: ȫ��ģ�鸴λ
                 1����λPAģ��
                 2����λTSFģ��
                 3����λmasterģ��
                 4����λCCMP/TKIPģ��
             uc_reset_reg:
                 �Ƿ�λ�Ĵ�����
                 0������λ�Ĵ���
                 1����λ�Ĵ���
             uc_reason:
                 ��λԭ��
                 0��error��λ
                 1���������λ
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_reset_hw(mac_device_stru* pst_device,oal_uint8* pst_param)
{
    oal_uint32                   ul_ret = OAL_SUCC;
#ifndef _PRE_WLAN_PROFLING_MIPS
    hal_to_dmac_device_stru     *pst_hal_device;
    dmac_reset_para_stru        *pst_reset_para;
    oal_uint                     ul_irq_flag;
    oal_time_us_stru             st_time_record =  {0,0};
    mac_reset_sys_stru           st_reset_sys;
    mac_vap_stru                *pst_mac_vap;
    mac_vap_stru                *pst_mac_sta;
    oal_uint8                    uc_vap_idx;

    /* ע���Ϊ�˻�ȡ����VAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->uc_cfg_vap_id);
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_reset_hw::Cannot find cfg_vap by vapID[%d],when devID[%d].}", pst_device->uc_cfg_vap_id, pst_device->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_device->en_reset_switch == OAL_FALSE)
    {
        //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_reset_hw::en_reset_switch is close.}");
        return OAL_SUCC;
    }

    pst_reset_para = (dmac_reset_para_stru*)pst_param;
    pst_hal_device = pst_device->pst_device_stru;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_BEGIN);

    /* ���ø�λ������true */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_TRUE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

     /* ����Ӳ������ */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* �ر�pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* ���жϣ��ڹ���Ӳ������֮�� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    if (pst_reset_para->uc_reset_mac_reg)
    {
       /*����LUT�ֳ������ڴ�����*/
       ul_ret = dmac_reset_lut_init();
       if(OAL_SUCC != ul_ret)
       {
            oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::dmac_reset_lut_init return error[%d]}", ul_ret);
            return  ul_ret ;
       }

       /* ����������¼����� */
       frw_event_flush_event_queue(FRW_EVENT_TYPE_WLAN_CRX);
       frw_event_flush_event_queue(FRW_EVENT_TYPE_WLAN_DRX);

       /* ���淢�Ͷ��е����� */
       dmac_reset_save_tx_queue(pst_hal_device);

       /*��λ�Ĵ���ǰ����,�巢�Ͷ��У�����LUT����*/
       dmac_tx_reset_flush(pst_hal_device);

       /*�����VAP��TSF��ֵ������¼��ǰʱ��*/
       dmac_reset_save_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf);
       oal_time_get_stamp_us(&st_time_record);
    }


    hal_reset_phy_machw(pst_hal_device,
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->uc_reset_mac_mod,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);

    if ((HAL_RESET_HW_TYPE_ALL == pst_reset_para->uc_reset_type) ||(HAL_RESET_HW_TYPE_RF == pst_reset_para->uc_reset_type))
    {
        hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_RF);

        for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
        {
          pst_mac_sta = mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
          if (OAL_PTR_NULL == pst_mac_sta)
          {
              oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
              OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_tsf::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
              return OAL_ERR_CODE_PTR_NULL;
          }

          if (WLAN_VAP_MODE_BSS_STA == pst_mac_sta->en_vap_mode)
          {

              /* ����hal�ӿ������ŵ��� */
              hal_set_primary_channel(pst_hal_device,
                                    pst_mac_sta->st_channel.uc_chan_number,
                                    pst_mac_sta->st_channel.en_band,
                                    pst_mac_sta->st_channel.uc_idx,
                                    pst_mac_sta->st_channel.en_bandwidth);
              break;
          }
        }

    }

    if(pst_reset_para->uc_reset_phy_reg)
    {
        hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_NORMAL_TYPE_PHY);
    }

    if(pst_reset_para->uc_reset_mac_reg)
    {
       /*��λ�Ĵ��������: �ָ��Ĵ�����LUT*/
       hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_NORMAL_TYPE_MAC);

       /*���⸴λ�����н��������������쳣�����³�ʼ����������������*/
       dmac_reset_rx_dscr_queue_flush(pst_hal_device);

       /* �ָ����Ͷ������� */
       dmac_reset_restore_tx_queue(pst_hal_device);

       /*��дTSF*/
       dmac_reset_restore_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf,&st_time_record);

       dmac_reset_lut_destroy();
    }


    /* ���ж� */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

    /* ʹ��pa */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* �ָ�Ӳ������ */
    hal_set_machw_tx_resume(pst_hal_device);

    /* ���ø�λ������false */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_FALSE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

    pst_device->us_device_reset_num++;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_END);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::current dmac reset num=%d.}", pst_device->us_device_reset_num);

    /*TBD:report reset event & reason to SDT*/

    OAM_WARNING_LOG4(0, OAM_SF_ANY, "{dmac_reset_hw::Here just performed a reset operation, reasen[%d], type[%d], phy_reg[%d], mac_reg[%d].}",
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->en_reason,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);
#endif
    return ul_ret;
}
#else
/*****************************************************************************
 �� �� ��  : dmac_reset_hw
 ��������  : reset hw�����
 �������  : uc_type:
                 0x01����λmac
                 0x10����λphy
                 0x11:  ��λmac&phy
             sub_module:
                 ��uc_type = 0x01,����λMACʱ��
                 0: ȫ��ģ�鸴λ
                 1����λPAģ��
                 2����λTSFģ��
                 3����λmasterģ��
                 4����λCCMP/TKIPģ��
             uc_reset_reg:
                 �Ƿ�λ�Ĵ�����
                 0������λ�Ĵ���
                 1����λ�Ĵ���
             uc_reason:
                 ��λԭ��
                 0��error��λ
                 1���������λ
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��3��1��
    ��    ��   : zourong
    �޸�����   : ��λMAC�ļĴ���������LUT��Ӱ�죬����LUT����Ӱ�졣
                 hi1151�ܸ�λӰ���lut��
                    key lut��
                    peer addr lut��
                    matrix info lut��
                    smart antenna lut
                 ���ܸ�λӰ���lut��
                    tx pn lut��
                    rx pn lut��
                    seq num lut��
                    dup det lut��
                    ba bitmap lut
   ���ԭ��ʵ�ֵ�PN LUT,SEQ LUT,BA LUT�ı�����ָ�������1151���࣬ͨ��ȫ�ֹ�������е�
   bitλ�����֡�
*****************************************************************************/
oal_uint32  dmac_reset_hw(mac_device_stru* pst_device,oal_uint8* pst_param)
{
    oal_uint32                   ul_ret = OAL_SUCC;
    oal_uint32                   ul_sequence_nonqos = 0;
    hal_to_dmac_device_stru     *pst_hal_device;
    dmac_reset_para_stru        *pst_reset_para;
    oal_uint                     ul_irq_flag;
    oal_time_us_stru             st_time_record =  {0,0};
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_reset_sys_stru           st_reset_sys;
    mac_vap_stru                *pst_mac_vap;

    /* ע���Ϊ�˻�ȡ����VAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(0);
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_reset_hw::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
    if (pst_device->en_reset_switch == OAL_FALSE)
    {
        return OAL_SUCC;
    }

    pst_reset_para = (dmac_reset_para_stru*)pst_param;

    pst_hal_device = pst_device->pst_device_stru;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_BEGIN);

    /* ���ø�λ������true */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_TRUE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

     /* ����Ӳ������ */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* �ر�pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* DTS2015122607368,�ر�PA���ӳ�1ms��λMAC����ֹMAC�쳣���� */
    oal_udelay(1000);

    /* ���жϣ��ڹ���Ӳ������֮�� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    if (pst_reset_para->uc_reset_mac_reg)
    {
       /*����LUT�ֳ������ڴ�����*/
       ul_ret = dmac_reset_lut_init();
       if(OAL_SUCC != ul_ret)
       {
            oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
            return  ul_ret ;
       }

       /*��λ�Ĵ���ǰ����,�巢�Ͷ��У�����LUT����*/
       dmac_tx_reset_flush(pst_hal_device);

       dmac_reset_save_seq_lut(pst_device,g_st_dmac_reset_mng.pst_sequence_qos,&ul_sequence_nonqos);

       dmac_reset_save_ba_lut(pst_device,g_st_dmac_reset_mng.pst_ba_rx);

       dmac_reset_save_pn_lut(pst_device,g_st_dmac_reset_mng.pst_rx_pn_ucast,
                                        g_st_dmac_reset_mng.pst_rx_pn_mcast,
                                        g_st_dmac_reset_mng.pst_tx_pn_ucast,
                                        g_st_dmac_reset_mng.pst_tx_pn_mcast);

       dmac_reset_save_txbf_lut(pst_device,g_st_dmac_reset_mng.pst_txbf);

       dmac_reset_save_smartant_lut(pst_device,g_st_dmac_reset_mng.pst_smartant);

       /*�����VAP��TSF��ֵ������¼��ǰʱ��*/
       dmac_reset_save_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf);
       oal_time_get_stamp_us(&st_time_record);
    }

    hal_reset_phy_machw(pst_hal_device,
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->uc_reset_mac_mod,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);

    if (pst_reset_para->uc_reset_rf_reg)
    {
        hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_RF);
    }

    if(pst_reset_para->uc_reset_phy_reg)
    {
        hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_TYPE_PHY);
    }

    if(pst_reset_para->uc_reset_mac_reg)
    {
       /*��λ�Ĵ��������: �ָ��Ĵ�����LUT*/
       hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_TYPE_MAC);

       /*���⸴λ�����н��������������쳣�����³�ʼ����������������*/
       dmac_reset_rx_dscr_queue_flush(pst_hal_device);

       /*LUT��Ļָ�*//* TBD zhongwen ��λlut����Ҫ��hal�ӿڷ�װ��������dmac��zourong */
       dmac_reset_restore_ba_lut(pst_device,g_st_dmac_reset_mng.pst_ba_rx);

       dmac_reset_restore_seq_lut(pst_device,g_st_dmac_reset_mng.pst_sequence_qos,&ul_sequence_nonqos);

       dmac_reset_restore_txbf_lut(pst_device,g_st_dmac_reset_mng.pst_txbf);

       dmac_reset_restore_smartant_lut(pst_device,g_st_dmac_reset_mng.pst_smartant);

       dmac_reset_restore_cipher_lut(pst_device);

       /*��Ϊ��������ԿӲ�����Զ�����PN�����Ա�������������Կ���ٻָ�pn*/
       dmac_reset_restore_pn_lut(pst_device,
                                 g_st_dmac_reset_mng.pst_rx_pn_ucast,
                                 g_st_dmac_reset_mng.pst_rx_pn_mcast,
                                 g_st_dmac_reset_mng.pst_tx_pn_ucast,
                                 g_st_dmac_reset_mng.pst_tx_pn_mcast);

       dmac_reset_restore_peer_addr_lut(pst_device);

       /*��дTSF*/
       dmac_reset_restore_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf,&st_time_record);

       dmac_reset_lut_destroy();
    }

    /* ���ж� */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

    /* ʹ��pa */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* �ָ�Ӳ������ */
    hal_set_machw_tx_resume(pst_hal_device);

    /* ���ø�λ������false */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_FALSE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

    pst_device->us_device_reset_num++;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_END);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::current dmac reset num=%d.}", pst_device->us_device_reset_num);

    /*TBD:report reset event & reason to SDT*/

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_save_seq_lut
 ��������  : ����sequnce lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq)
{

    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint8            uc_tid_loop;
    oal_uint32           *pst_reg_read;

    if(g_st_dmac_reset_mng.bit_seq_lut_reset)
    {
        /* ����device�������û������Ĵ���������ÿ��TID��Ӧ��sequence */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_seq_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_save_seq_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                if(pst_dmac_user_tmp->st_user_base_info.st_cap_info.bit_qos)
                {
                    for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
                    {
                         pst_reg_read = pst_qos_seq + (pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop;
                         hal_get_tx_sequence_num(pst_mac_device->pst_device_stru,
                                                pst_dmac_user_tmp->uc_lut_index,
                                                uc_tid_loop,
                                                1,
                                                pst_reg_read);
                     }
                }
            }
        }
    }
    /*non-qos,index��tidû������*/
    hal_get_tx_sequence_num(pst_mac_device->pst_device_stru,
                            0,
                            0,
                            0,
                            pst_nonqos_seq);


	return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_restore_seq_lut
 ��������  : ����sequnce lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq)
{

    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint8            uc_tid_loop;
    oal_uint32           ul_reg_value;


    if(g_st_dmac_reset_mng.bit_seq_lut_reset)
    {
        /* ����device�������û������Ĵ���������ÿ��TID��Ӧ��sequence */
        /* ҵ��VAP��0��ʼ*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_seq_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_seq_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                if(pst_dmac_user_tmp->st_user_base_info.st_cap_info.bit_qos)
                {
                    for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
                    {
                         ul_reg_value = *(pst_qos_seq + (pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop);
                         hal_set_tx_sequence_num(pst_mac_device->pst_device_stru,
                                                pst_dmac_user_tmp->uc_lut_index,
                                                uc_tid_loop,
                                                1,
                                                ul_reg_value);
                     }
                }

            }
        }
    }

    /*non-qos,index��tidû������*/
    hal_set_tx_sequence_num(pst_mac_device->pst_device_stru,
                            0,
                            0,
                            0,
                            *(pst_nonqos_seq));

	return  OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_reset_save_ba_lut
 ��������  : ����ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut)
{

    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_ba_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_MAX_RX_BA;uc_index_loop++)
        {
            pst_current_entry = pst_ba_lut + uc_index_loop*WLAN_BA_LUT_ENTRY_SIZE;
            hal_get_machw_ba_params(pst_hal_device,
                                    uc_index_loop,
                                    pst_current_entry,
                                    pst_current_entry + 1,
                                    pst_current_entry + 2);
        }
    }

    return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_restore_ba_lut
 ��������  : restore ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;


    if(g_st_dmac_reset_mng.bit_ba_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop = 0; uc_index_loop < WLAN_MAX_RX_BA; uc_index_loop++)
        {
            pst_current_entry = pst_ba_lut + uc_index_loop*WLAN_BA_LUT_ENTRY_SIZE;
            hal_restore_machw_ba_params(pst_hal_device,
                                        uc_index_loop,
                                        *(pst_current_entry),
                                        *(pst_current_entry + 1),
                                        *(pst_current_entry + 2));
        }
    }

    return  OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : dmac_reset_save_pn_lut
 ��������  : ����ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast)
{

    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_uint32              *pst_curr_entry;
    oal_uint8                uc_vap_idx;
    dmac_vap_stru            *pst_dmac_vap;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    dmac_user_stru          *pst_dmac_user_tmp;
    oal_uint8                uc_tid_loop;

    if(g_st_dmac_reset_mng.bit_pn_lut_reset)
    {
        /* ����device�������û������Ĵ��������浥��PN LUT */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_pn_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_reset_save_pn_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }

                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                {
                 /* ����tx pn */
                 st_pn_lut_cfg.uc_pn_key_type = 1;
                 st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                 hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);


                 /*�����ȡ��DBB mac��ֵ*/
                 pst_curr_entry         = pst_tx_pn_ucast + (pst_dmac_user_tmp->uc_lut_index)*2;
                *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
                }

                /* ����rx pn */
                for(uc_tid_loop = 0; uc_tid_loop < WLAN_TID_MAX_NUM; uc_tid_loop++)
                {
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                     hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                     /*�����ȡ��DBB mac��ֵ*/
                     pst_curr_entry         = pst_rx_pn_ucast + ((pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                    *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                    *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
                }
            }

        }

        /*�鲥 rx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
        {
            for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
            {
                 st_pn_lut_cfg.uc_pn_key_type = 0;
                 st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
                 st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                 hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                 /*�����ȡ��DBB mac��ֵ*/
                 pst_curr_entry         = pst_rx_pn_mcast + (uc_vap_idx*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
            }
        }

        /*�鲥 Tx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
        {
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

             /*�����ȡ��DBB mac��ֵ*/
             pst_curr_entry         = pst_tx_pn_mcast + uc_vap_idx*2;
            *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
            *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
        }
    }

    return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_restore_pn_lut
 ��������  : restore ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast)
{
    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_uint32              *pst_curr_entry;
    oal_uint8                uc_vap_idx;
    dmac_vap_stru            *pst_dmac_vap;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    dmac_user_stru          *pst_dmac_user_tmp;
    oal_uint8                uc_tid_loop;


    if(g_st_dmac_reset_mng.bit_pn_lut_reset)
    {
        /* ����device������VAP�Ļ�Ծ�û����ָ�����PN lut*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_pn_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_pn_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                {
                    /* ����tx pn */
                     pst_curr_entry               = pst_tx_pn_ucast + (pst_dmac_user_tmp->uc_lut_index)*2;
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
                     st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                     hal_set_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);
                }

                /* ����rx pn */
                for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
                {
                     pst_curr_entry               = pst_rx_pn_ucast + ((pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                     st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry ;
                     st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                     hal_set_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                }

            }

        }

        /*�鲥 rx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
        {
            for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
            {
                 pst_curr_entry               = pst_rx_pn_mcast + (uc_vap_idx*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                 st_pn_lut_cfg.uc_pn_key_type = 0;
                 st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
                 st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                 st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
                 st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                 hal_set_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

            }
        }

        /*�鲥 Tx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
        {
             pst_curr_entry               = pst_tx_pn_mcast + uc_vap_idx*2;
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
             st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

             hal_set_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

        }
    }

    return  OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_reset_restore_cipher_lut
 ��������  : restore ���� lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_cipher_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                            uc_vap_idx;
    dmac_vap_stru                       *pst_dmac_vap;
    mac_vap_stru                        *pst_mac_vap;
    oal_dlist_head_stru                 *pst_entry;
    mac_user_stru                       *pst_user;
    dmac_user_stru                      *pst_dmac_user;
    oal_uint8                            uc_key_idx;
    mac_user_stru                       *pst_multi_user;

    if(g_st_dmac_reset_mng.bit_key_lut_reset)
    {
        /* ����device�������û������Ĵ���������ÿ��TID��Ӧ��sequence */
        /* ҵ��VAP��WLAN_SERVICE_VAP_START_ID_PER_BOARD��ʼ*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_cipher_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }
            pst_mac_vap = &pst_dmac_vap->st_vap_base_info;
            /*������ģʽ����*/
            pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_multi_user))
            {
                OAM_ERROR_LOG1(0, OAM_SF_DBAC, "{dmac_reset_restore_cipher_lut::pst_mac_user[%d] is NULL!}", pst_mac_vap->us_multi_user_idx);
                continue;
            }
            if(WLAN_80211_CIPHER_SUITE_NO_ENCRYP == pst_multi_user->st_key_info.en_cipher_type)
            {
                continue;
            }

            /*wep key�ָ�*/
            if(OAL_TRUE == mac_is_wep_allowed(pst_mac_vap))
            {
                uc_key_idx = mac_get_wep_default_keyid(pst_mac_vap);
                dmac_11i_add_wep_key(pst_mac_vap,uc_key_idx);
            }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
            if (!mac_vap_is_vsta(pst_mac_vap))
#endif
            {
                /*GTK�ָ�*/
                uc_key_idx = pst_multi_user->st_key_info.uc_default_index;
                dmac_11i_add_gtk_key(pst_mac_vap, uc_key_idx);
            }

            /*PTK�ָ�*/
            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user = mac_res_get_dmac_user(pst_user->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_cipher_lut::pst_dmac_user null, assoc id=%d.", pst_user->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user->bit_active_user)
                {
                    continue;
                }

                uc_key_idx = pst_user->st_key_info.uc_default_index;
                dmac_11i_add_ptk_key(pst_mac_vap, pst_dmac_user->st_user_base_info.auc_user_mac_addr, uc_key_idx);
             }

        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_reset_save_txbf_lut
 ��������  : ����ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut)
{
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_txbf_lut + uc_index_loop;
            hal_get_txbf_lut_info(pst_hal_device,uc_index_loop,pst_current_entry);
        }
    }
 #endif
    return  OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_reset_restore_txbf_lut
 ��������  : ����ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut)
{
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_txbf_lut + uc_index_loop;
            hal_set_txbf_lut_info(pst_hal_device,uc_index_loop,*pst_current_entry);
        }
    }
#endif
    return  OAL_SUCC;
}

OAL_STATIC oal_uint32 dmac_reset_save_smartant_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_smartant_lut)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_smartant_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_smartant_lut + uc_index_loop;
            hal_get_smart_antenna_value(pst_hal_device,uc_index_loop,pst_current_entry);
        }
    }
    return  OAL_SUCC;
}

OAL_STATIC oal_uint32 dmac_reset_restore_smartant_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_smartant_lut)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_smartant_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_smartant_lut + uc_index_loop;
            hal_set_smart_antenna_value(pst_hal_device,uc_index_loop,(oal_uint16)*pst_current_entry);
        }
    }
    return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_restore_peer_addr_lut
 ��������  : restore ba lut��ֵ
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_peer_addr_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                            uc_vap_idx;
    dmac_vap_stru                       *pst_dmac_vap;
    mac_vap_stru                        *pst_mac_vap;
    oal_dlist_head_stru                 *pst_entry;
    mac_user_stru                       *pst_user;
    dmac_user_stru                      *pst_dmac_user;


    if(g_st_dmac_reset_mng.bit_peer_addr_lut_reset)
    {
        /* ����device�������û��� */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_peer_addr_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }
            pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user = mac_res_get_dmac_user(pst_user->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_peer_addr_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* �ǻ�Ծ�û���ֱ�ӷ��� */
                if (OAL_FALSE == pst_dmac_user->bit_active_user)
                {
                    continue;
                }


               hal_ce_add_peer_macaddr(pst_mac_device->pst_device_stru,pst_dmac_user->uc_lut_index,pst_dmac_user->st_user_base_info.auc_user_mac_addr);

             }
        }
    }

    return OAL_SUCC;

}

#endif

/*****************************************************************************
 �� �� ��  : dmac_reset_rx_dscr_queue_flush
 ��������  : ��λ�����ٽ������������в����³�ʼ����������������
 �������  : uc_type:
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_rx_dscr_queue_flush(hal_to_dmac_device_stru* pst_hal)
{
    hal_rx_destroy_dscr_queue(pst_hal,OAL_TRUE);
    hal_rx_init_dscr_queue(pst_hal,OAL_TRUE);
}

/*****************************************************************************
 �� �� ��  : dmac_reset_save_tsf
 ��������  : ��ȡ������ÿ��ҵ��VAP��time stamp��ֵ
 �������  : ��¼timestamp��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC oal_void dmac_reset_save_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array)
{
    oal_uint8                uc_vap_idx;
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32              *pst_tsf_entry;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_tsf::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
            return ;
        }
        /*ÿ��timestamp 64λ��ռ�������2����Ŀ*/
        pst_tsf_entry = pst_tsf_array + uc_vap_idx*2;

        hal_vap_tsf_get_64bit(pst_dmac_vap->pst_hal_vap, pst_tsf_entry, pst_tsf_entry + 1);

    }
}

/*****************************************************************************
 �� �� ��  : dmac_reset_restore_tsf
 ��������  : ����дÿ��ҵ��VAP��time stamp�ļĴ���
 �������  : ��¼timestamp��ָ��
             ����timstampʱ��ʱ���
 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_reset_restore_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array,oal_time_us_stru *pst_time_record)
{
    oal_uint8                uc_vap_idx;
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32              *pst_tsf_entry;
    oal_time_us_stru         st_now_time;
    oal_uint32               ul_diff_time_us;
    oal_uint32               ul_tsf_hi;
    oal_uint32               ul_tsf_lo;
    oal_uint32               ul_tsf_lo_plus;

    /*��ǰʱ��*/
    oal_time_get_stamp_us(&st_now_time);

    /*����ʱ��*/
    ul_diff_time_us = (oal_uint32)DMAC_TIME_USEC_DIFF(pst_time_record, &st_now_time);

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_tsf::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
            return ;
        }
        /*ÿ��timestamp 64λ��ռ�������2����Ŀ*/
        pst_tsf_entry = pst_tsf_array + uc_vap_idx*2;
        ul_tsf_hi     = *pst_tsf_entry;
        ul_tsf_lo     = *(pst_tsf_entry + 1);

        /*���ϲ�ֵ*/
        ul_tsf_lo_plus = ul_tsf_lo + ul_diff_time_us;
        if((ul_tsf_lo_plus < ul_tsf_lo )|| (ul_tsf_lo_plus < ul_diff_time_us))
        {
            ul_tsf_hi++ ;
            //OAM_INFO_LOG1(0, OAM_SF_ANY, "tsf ul_tsf_hi = %d\n",ul_tsf_hi);
        }

        hal_vap_tsf_set_64bit(pst_dmac_vap->pst_hal_vap, ul_tsf_hi, ul_tsf_lo_plus);
    }
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_reset_sys_event
 ��������  : host���и�λʱ��ͬ��device�¼�����
 �������  : pst_event_mem�¼�
 �������  : ��
 �� �� ֵ  : OAL_SUCC | OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : zhangyu 00241943
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 dmac_reset_sys_event(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru     *pst_mac_dev;
    mac_reset_sys_stru  *pst_reset_sys;

    pst_reset_sys = (mac_reset_sys_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_reset_sys_event::pst_mac_dev null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch(pst_reset_sys->en_reset_sys_type)
    {
        case MAC_RESET_STATUS_SYS_TYPE:
            /* �·���λ */
            break;
        case MAC_RESET_SWITCH_SYS_TYPE:
            pst_mac_dev->en_reset_switch = pst_reset_sys->uc_value;

            break;
        default:
            break;
    }

    return OAL_SUCC;
}
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : dmac_reset_debug_sequence_lut
 ��������  : ��ȡӲ����LUT����ʾ
 �������  :

 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_debug_sequence_lut(mac_device_stru* pst_device)
{

    oal_uint32           ul_reg_read;
    oal_uint8            uc_user_loop;
    oal_uint8            uc_tid_loop;
    oal_file             *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------sequence_lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
            hal_get_tx_sequence_num(pst_device->pst_device_stru,
                                    uc_user_loop,
                                    uc_tid_loop,
                                    1,
                                    &ul_reg_read);
           oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, sequence = %d\n",uc_user_loop,uc_tid_loop,ul_reg_read);
         }
    }

    dmac_reset_debug_close();

}

/*****************************************************************************
 �� �� ��  : dmac_reset_debug_ba_lut
 ��������  : ��ȡӲ����LUT����ʾ
 �������  :

 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_debug_ba_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32               ul_addr_h;
    oal_uint32               ul_addr_l;
    oal_uint32               ul_ba_para;
    oal_uint32               ul_tid ;
    oal_uint32               ul_winstart ;
    oal_uint32               ul_winsize ;
    oal_file                *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------ba_lut--------------------------\n");

    pst_hal_device = pst_mac_device->pst_device_stru;
    for(uc_index_loop=0;uc_index_loop < WLAN_MAX_RX_BA;uc_index_loop++)
    {
        hal_get_machw_ba_params(pst_hal_device,
                                uc_index_loop,
                                &ul_addr_h,
                                &ul_addr_l,
                                &ul_ba_para);

        ul_tid      = (ul_ba_para&0x0000000f);
        ul_winstart = (ul_ba_para&0x000000f0)>>4;
        ul_winsize  = (ul_ba_para&0x00003f00)>>8;
        oal_kernel_file_print(pst_fs," addr hi = %x,addr lo = %x,param = %d,TID = %d, winstart = %d,winsize = %d\n",
                            ul_addr_h, ul_addr_l,ul_ba_para,ul_tid,
                            ul_winstart,ul_winsize);
    }

    dmac_reset_debug_close();
 }

/*****************************************************************************
 �� �� ��  : dmac_reset_debug_ba_lut
 ��������  : ��ȡӲ����LUT����ʾ
 �������  :

 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_debug_pn_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                uc_user_loop;
    oal_uint8                uc_tid_loop;
    oal_uint8                uc_vap_idx;
    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_file                *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------rx_pn_ucast lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
            st_pn_lut_cfg.uc_pn_key_type = 1;
            st_pn_lut_cfg.uc_pn_peer_idx = uc_user_loop;
            st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
            hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

           oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                        uc_user_loop,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);

         }
    }


    oal_kernel_file_print(pst_fs,"------------------------rx_pn_mcast lut--------------------------\n");
    for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
    {
        for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
             hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

             oal_kernel_file_print(pst_fs,"uc_pn_peer_idx index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                        uc_vap_idx,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);
        }
    }


    oal_kernel_file_print(pst_fs,"------------------------tx_pn_ucast lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        st_pn_lut_cfg.uc_pn_key_type = 1;
        st_pn_lut_cfg.uc_pn_peer_idx = uc_user_loop;
        hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

        oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                    uc_user_loop,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);
    }


    oal_kernel_file_print(pst_fs,"------------------------tx_pn_mcast lut--------------------------\n");
    for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
    {
         st_pn_lut_cfg.uc_pn_key_type = 0;
         st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
         hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

         oal_kernel_file_print(pst_fs,"uc_pn_peer_idx index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                      uc_vap_idx,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);

    }

    dmac_reset_debug_close();
}


/*****************************************************************************
 �� �� ��  : dmac_reset_debug_init
 ��������  : resetά��ʹ�ã�ά��ʱһ��ʼ���ñ���������һ���ļ�����չ�ں˿ռ䵽�û��ռ�
 �������  : ��:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_void dmac_reset_debug_init(oal_void)
{

    g_st_dmac_reset_mng.pst_debug_file = oal_kernel_file_open(DMAC_RESET_DUMP_LUT_PATH,OAL_O_RDWR|OAL_O_CREAT|OAL_O_APPEND);
    if(g_st_dmac_reset_mng.pst_debug_file)
    {
        g_st_dmac_reset_mng.old_fs = oal_get_fs();
        oal_set_fs(OAL_KERNEL_DS);                  //��չ�ں˿ռ䵽�û��ռ�
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "open file fail\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_reset_debug_close
 ��������  : resetά��ʹ�ã�ά�����ʱ���ñ��������رմ򿪵��ļ����ָ����ں˿ռ�
 �������  : ��:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_void dmac_reset_debug_close(oal_void)
{
    oal_kernel_file_close(g_st_dmac_reset_mng.pst_debug_file);
    oal_set_fs(g_st_dmac_reset_mng.old_fs);  //�ָ��ں˿ռ�
}

/*****************************************************************************
 �� �� ��  : dmac_reset_debug_close
 ��������  : resetά��ʹ�ã����ַ���д���򿪵��ļ�
 �������  : pst_str: �ַ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_debug_to_file(oal_uint8 *pst_str)
{
    oal_kernel_file_write(g_st_dmac_reset_mng.pst_debug_file,pst_str,OAL_STRLEN(pst_str));
}

/*****************************************************************************
 �� �� ��  : dmac_reset_debug_all
 ��������  : ��ȡӲ����LUT����ʾ
             ��ȡ���еļĴ�������ʾ
 �������  :

 �������  :
 �� �� ֵ  : OAL_SUCC | OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_reset_debug_all(mac_device_stru* pst_device,dmac_reset_para_stru* pst_debug_para)
{

    /* debug��ʾlut��ͼĴ���:hipriv "Hisilicon0 reset_hw 3(debug) 0|1|2(all|mac reg|phy reg|lut) "*/

    if(pst_debug_para->uc_debug_type == 0)
    {
        /*������е�*/
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_MAC);
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_PHY);
        dmac_reset_debug_sequence_lut(pst_device);
        dmac_reset_debug_ba_lut(pst_device);
        dmac_reset_debug_pn_lut(pst_device);

    }
    else if(pst_debug_para->uc_debug_type == 1)
    {
         /*���mac�Ĵ���*/
       hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_MAC);

    }
    else if(pst_debug_para->uc_debug_type == 2)
    {
        /*���phyָ��bank��reg*/
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_PHY);
    }
    else if(pst_debug_para->uc_debug_type == 3)
    {
        dmac_reset_debug_sequence_lut(pst_device);
        dmac_reset_debug_ba_lut(pst_device);
        dmac_reset_debug_pn_lut(pst_device);
    }

}

#else /*win32*/
oal_void dmac_reset_debug_all(mac_device_stru* pst_device,dmac_reset_para_stru* pst_debug_para)
{
    return;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

