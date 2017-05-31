/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_hcc_adapt.c
  �� �� ��   : ����
  ��    ��   : h00217255
  ��������   : 2014��10��8��
  ����޸�   :
  ��������   : HMACģ��HCC������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��8��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "mac_resource.h"
#include "dmac_hcc_adapt.h"
#include "dmac_vap.h"
#include "mac_device.h"
#include "oal_hcc_slave_if.h"
#include "oal_profiling.h"

#include "oal_hcc_slave_if.h"
#include "cali_data.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_HCC_ADAPT_C

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_release_tid_buffs(dmac_vap_stru     *pst_dmac_vap,
                                        mac_device_stru  *pst_device,
                                        oal_uint32       ul_nums);
#endif


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#define DMAC_HCC_EXTEND_TOTAL_SIZE      (MAX_MAC_HEAD_LEN + OAL_MAX_CB_LEN + (oal_int32)OAL_SIZEOF(struct frw_hcc_extend_hdr))
oal_uint32  g_hcc_sched_event_pkts[FRW_EVENT_TYPE_BUTT]={0};
oal_uint32  g_hcc_event_cnt = 0;
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*debug*/
oal_void dmac_event_pkts_dump(oal_void)
{
    oal_int32 i = 0;
    for(i = 0; i < FRW_EVENT_TYPE_BUTT;i++)
    {
        OAL_IO_PRINT("event:%d,pkts:%d\r\n",i,g_hcc_sched_event_pkts[i]);
    }
}

OAL_STATIC OAL_INLINE struct frw_hcc_extend_hdr* dmac_get_hcc_tx_extend_hdr_addr(oal_netbuf_stru  *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr =
                    (struct frw_hcc_extend_hdr*)hcc_get_extend_addr(pst_netbuf,DMAC_HCC_EXTEND_TOTAL_SIZE);
    OAL_BUG_ON(NULL == pst_hdr);
    return pst_hdr;
}

OAL_STATIC OAL_INLINE struct frw_hcc_extend_hdr* dmac_get_hcc_rx_extend_hdr_addr(oal_netbuf_stru  *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr =
                    (struct frw_hcc_extend_hdr*)hcc_get_extend_payload_addr(pst_netbuf);
    OAL_BUG_ON(NULL == pst_hdr);
    return pst_hdr;
}

OAL_STATIC OAL_INLINE oal_int32 dmac_hcc_adapt_extend_hdr_init(frw_event_mem_stru *pst_hcc_event_mem,oal_netbuf_stru *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr;
    frw_event_hdr_stru   *pst_event_hdr;
    if (OAL_PTR_NULL == pst_hcc_event_mem || OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{dmac_hcc_adapt_extend_hdr_init::pst_hcc_event_mem or pst_netbuf is null}");
        return OAL_ERR_CODE_PTR_NULL;        
    }
    pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hdr = dmac_get_hcc_tx_extend_hdr_addr(pst_netbuf);
    if (OAL_PTR_NULL == pst_hdr)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{dmac_hcc_adapt_extend_hdr_init::dmac_get_hcc_tx_extend_hdr_addr failed}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hdr->en_nest_type = pst_event_hdr->en_type;
    pst_hdr->uc_nest_sub_type = pst_event_hdr->uc_sub_type;
    pst_hdr->device_id = pst_event_hdr->uc_device_id;
    pst_hdr->chip_id = pst_event_hdr->uc_chip_id;
    pst_hdr->vap_id = pst_event_hdr->uc_vap_id;

    return OAL_SUCC;
}

oal_uint32 dmac_adapt_tx_param_and_netbuf_hdr_init(frw_event_mem_stru   *pst_event_mem,
                                                   struct hcc_transfer_param* pst_param,
                                                   oal_netbuf_stru  * pst_netbuf)
{
    OAL_BUG_ON(NULL == pst_netbuf);

    if (OAL_SUCC != dmac_hcc_adapt_extend_hdr_init(pst_event_mem,pst_netbuf))
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{dmac_adapt_tx_param_and_netbuf_hdr_init::dmac_hcc_adapt_extend_hdr_init failed}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hcc_hdr_param_init(pst_param,HCC_ACTION_TYPE_WIFI,0,DMAC_HCC_EXTEND_TOTAL_SIZE);
    return OAL_SUCC;
}

oal_uint32 g_dmac_hcc_tx_event_drop_buffs = 0;
oal_netbuf_stru  *  dmac_hcc_tx_event_convert_to_netbuf_alloc(frw_event_mem_stru   *pst_event_mem,
                                                                            oal_uint32         ul_size)
{
    oal_netbuf_stru  *pst_netbuf =
                      OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_NETBUF_PRIORITY_HIGH);
    if(NULL != pst_netbuf)
    {
        return pst_netbuf;
    }
    else
    {
        oal_uint32 ul_free_nums;
        frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_event_mem);
        dmac_vap_stru  *pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
        mac_device_stru  *pst_device =  mac_res_get_dev(pst_event_hdr->uc_device_id);
        /*��ֹ�ͷ����ڴ汻����ģ������*/
        oal_irq_disable();
        /*������5��netbuf �������ȼ�����ֹ�ͷŵ��ڴ涼�Ǹ����ȼ��ڴ棬ÿ���ͷ�6����*/
        ul_free_nums = dmac_release_tid_buffs(pst_dmac_vap, pst_device, (OAL_NETBUF_HIGH_PRIORITY_COUNT+1));
        if(ul_free_nums)
        {
            g_dmac_hcc_tx_event_drop_buffs += ul_free_nums;
            pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_NETBUF_PRIORITY_HIGH);
        }
        oal_irq_enable();
        return pst_netbuf;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_hcc_rx_netbuf_convert_to_event
 ��������  : Dmacģ�齫�¼��ڴ��е����ݸ��Ƶ�netbuf�У���hmac�����л�ԭ
 �������  : frw_event_mem_stru *pst_hcc_event_mem
             oal_int32 is_had_netbuf
             oal_uint32 event_size
             oal_uint32 payload_size
             oal_uint32 revert_size
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e801*/
oal_uint32 dmac_hcc_tx_event_convert_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                               oal_netbuf_stru      *pst_event_netbuf,
                                               oal_uint32            payload_size)
{
    oal_uint32 ret = OAL_SUCC;
    oal_uint8                      *pst_event_payload;
    oal_netbuf_stru                *pst_netbuf = NULL;
    oal_netbuf_stru                *pst_netbuf_tx;
    struct hcc_transfer_param param;

    /* �����Ϸ��Լ�� */
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_payload = frw_get_event_payload(pst_event_mem);

    /*If Null, we should alloc netbuf and copy from event to netbuf*/
    if(NULL == pst_event_netbuf)
    {
        frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_event_mem);
        pst_netbuf = dmac_hcc_tx_event_convert_to_netbuf_alloc(pst_event_mem, payload_size);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            ret = OAL_ERR_CODE_ALLOC_MEM_FAIL;
            OAM_WARNING_LOG4(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac2hmac event to netbuf alloc[%d] failed,main:%d,sub:%d,drop nums:%u}",
					 payload_size,pst_event_hdr->en_type,pst_event_hdr->uc_sub_type, g_dmac_hcc_tx_event_drop_buffs);
            goto failed_alloc_netbuf;
        }

        OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
        oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf)),
                    (oal_uint8 *)pst_event_payload,
                    payload_size);

    }

    if(NULL != pst_event_netbuf)
        pst_netbuf_tx       = pst_event_netbuf;
    else
        pst_netbuf_tx       = pst_netbuf;
#if 1
    dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_netbuf_tx);
#else
    hcc_hdr_param_init(&param,HCC_ACTION_TYPE_WIFI,0,0);
#endif

    hcc_slave_tx(pst_netbuf_tx, (oal_uint16)payload_size,&param);

    return OAL_SUCC;

failed_alloc_netbuf:
    return ret;
}

oal_uint32 dmac_hcc_tx_netbuf_convert_to_netbuf(frw_event_mem_stru *pst_event_mem,
                                                             oal_netbuf_stru   *pst_event_netbuf,
                                                              oal_uint32 payload_size)
{
    oal_uint32 ret;
    if(NULL != pst_event_netbuf)
    {
        ret = dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem,pst_event_netbuf,payload_size);
    }
    else
    {
        /*assert?*/
        ret = OAL_ERR_CODE_PTR_NULL;
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : dmac_hcc_rx_netbuf_convert_to_event
 ��������  : Dmacģ�齫netbuf�е��¼����ݻ�ԭ���¼��ڴ���
 �������  : frw_event_mem_stru *pst_hcc_event_mem
             oal_uint32 revert_size
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru * dmac_hcc_rx_netbuf_convert_to_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 revert_size)
{
    frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    frw_event_type_enum_uint8       en_type;
    oal_uint8                       uc_sub_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_vap_id;
    frw_event_mem_stru             *pst_event_mem;              /* ҵ���¼������Ϣ */

	if(NULL == pst_hcc_event_mem)
	{
			return NULL;
	}

    /* ��ȡHCC�¼���Ϣ */
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    en_type                 = pst_hcc_event_hdr->en_type;
    uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /* ����ҵ���¼� */
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)revert_size);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        /* �ͷ�hcc�¼��������netbuf�ڴ� */
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{dmac_hcc_rx_netbuf_convert_to_event:: pst_event_mem null. type = %d, sub_type= %d , cnt = %d}",
                       en_type,uc_sub_type,g_hcc_event_cnt++);
        OAL_MEM_NETBUF_FREE(pst_hcc_netbuf);
        return OAL_PTR_NULL;
    }

    /* ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       (oal_uint16)revert_size,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);
    if(revert_size)
        oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem),
                (oal_uint8 *)OAL_NETBUF_HCC_PAYLOAD(pst_hcc_netbuf), revert_size);

    /* �ͷ�hcc�¼��������netbuf�ڴ� */
    OAL_MEM_NETBUF_FREE(pst_hcc_netbuf);

    /* 2015.08.12 START ����ͬ���¼���ӡ��ȷ�Ͻ����Ƿ��¼� */
    if(HMAC_TO_DMAC_SYN_CFG == uc_sub_type)
    {
        hmac_to_dmac_cfg_msg_stru  *pst_syn_msg = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_ANY, "{dmac_hcc_rx_netbuf_convert_to_event::device recv event from host:type[%d],subtype[%d],cfgid[%d]}",
                       en_type, uc_sub_type, pst_syn_msg->en_syn_id);
    }
    /* 2015.08.12 END*/

    return pst_event_mem;
}
/*lint +e801*/

/*****************************************************************************
 �� �� ��  : dmac_hcc_tx_convert_event_to_netbuf_uint16
 ��������  : dmac��Я��payload�¼��Ĺ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32 dmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,OAL_SIZEOF(oal_uint16));
}

/*****************************************************************************
 �� �� ��  : dmac_proc_event_del_ba_tx_adapt
 ��������  : DMAC_TO_HMAC_DEL_BA�¼���������(dmac����delba)
 �������  : pst_event_mem: �¼��ڴ�ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_proc_event_del_ba_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(dmac_to_hmac_ctx_event_stru));
}
/*****************************************************************************
 �� �� ��  : dmac_alg_syn_info_adapt
 ��������  : DMAC_TO_HMAC_ALG_INFO_SYN�¼���������(dmac֪ͨhmacЭ��ģʽ�ı�)
 �������  : pst_event_mem: �¼��ڴ�ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : j0019683
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_syn_info_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_alg_voice_aggr_adapt
 ��������  : DMAC_TO_HMAC_VOICE_AGGR�¼���������(dmac֪ͨhmacЭ��ģʽ�ı�)
 �������  : pst_event_mem: �¼��ڴ�ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : l0033043
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_voice_aggr_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_proc_event_config_syn_tx_adapt
 ��������  : config_synģ�鷢������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e413*/
oal_uint32 dmac_proc_event_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_to_hmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_syn_cfg_payload    = (dmac_to_hmac_cfg_msg_stru *)pst_event->auc_event_data;
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                        pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body));
}
/*lint +e413*/

#ifdef _PRE_WLAN_CHIP_TEST_ALG
/*****************************************************************************
 �� �� ��  : dmac_alg_test_result_tx_adapt
 ��������  : �㷨оƬ���Խ���ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_ct_result_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, pst_event->auc_event_data[0] + 1);

}
#endif

oal_uint32 dmac_proc_init_event_process_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_tx_event_stru              *pst_ctx_event;
    pst_event   = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_proc_init_event_process_tx_adapt.}");
    return  dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                       pst_ctx_event->us_frame_len);
}


/*****************************************************************************
 �� �� ��  : dmac_proc_wlan_drx_event_tx_adapt
 ��������  : wlan_drx_event��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_proc_wlan_drx_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_hdr_stru              *pst_event_hdr;
    oal_uint32                       ul_payload_len;

    dmac_wlan_drx_event_stru        *pst_wlan_rx;

    oal_netbuf_stru                 *pst_tmp_netbuf = NULL;
    oal_netbuf_stru                 *pst_curr_netbuf;

    oal_uint16                       us_loop;
    oal_uint16                       us_netbuf_num;

    mac_rx_ctl_stru                 *pst_rx_cb;

    oal_uint8                        uc_mac_header_len = MAX_MAC_HEAD_LEN;
    oal_uint8                        uc_mac_header[MAX_MAC_HEAD_LEN] = {0};

/*#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    struct oal_auto_freq_pps_process_func_handler* pst_pps_process = oal_get_dmac_auto_freq_pps_process_func();
#endif*/
    pst_event_hdr           = frw_get_event_hdr(pst_event_mem);

    pst_wlan_rx             = (dmac_wlan_drx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_curr_netbuf         = pst_wlan_rx->pst_netbuf;
    us_netbuf_num           = pst_wlan_rx->us_netbuf_num;

    for (us_loop = 0; us_loop < us_netbuf_num; us_loop++)
    {
        struct hcc_transfer_param param;
        if(NULL == pst_curr_netbuf)
        {
            /*netbuf list num < list head's num?*/
            OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac had post %d netbufs,but list num is:%d,miss %d}",
                                                                us_loop, us_netbuf_num, us_netbuf_num - us_loop);
            break;
        }

        /* for amsdu adapt */
        pst_rx_cb = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_curr_netbuf);
        if(OAL_TRUE == pst_rx_cb->bit_amsdu_enable)
        {
            if ((pst_rx_cb->bit_buff_nums > 1) && (OAL_TRUE == pst_rx_cb->bit_is_first_buffer))
            {
                uc_mac_header_len = pst_rx_cb->bit_mac_header_len;
                oal_memcopy(uc_mac_header, oal_netbuf_header(pst_curr_netbuf), uc_mac_header_len);
            }
            if (OAL_FALSE == pst_rx_cb->bit_is_first_buffer)
            {
                pst_rx_cb->bit_mac_header_len = uc_mac_header_len;
                pst_rx_cb->uc_mac_vap_id = pst_event_hdr->uc_vap_id;
                oal_memcopy(oal_netbuf_header(pst_curr_netbuf), uc_mac_header, uc_mac_header_len);
            }
            pst_rx_cb->us_frame_len = 0;
            //ul_payload_len = WLAN_LARGE_NETBUF_SIZE; //��Ϊû�е�buffer����(�����������ܳ���) SDIO������󳤶�
            pst_rx_cb->bit_buff_nums = 1;//host netbuf������ ��buffer����
        }

        if (pst_rx_cb->us_frame_len)
        {
            ul_payload_len = pst_rx_cb->us_frame_len - pst_rx_cb->bit_mac_header_len;//�����������е�payload len
            if(ul_payload_len > WLAN_LARGE_NETBUF_SIZE)
            {
                OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac invalid len:%d,frame:%d,mac hdr:%d}",
                                                                ul_payload_len,
                                                                pst_rx_cb->us_frame_len,
                                                                pst_rx_cb->bit_mac_header_len);
                ul_payload_len = WLAN_LARGE_NETBUF_SIZE;
            }
        }
        else
        {
            ul_payload_len = WLAN_LARGE_NETBUF_SIZE;
        }

        pst_tmp_netbuf = pst_curr_netbuf;

		/* ָ��netbuf�������һ��netbuf */
        pst_curr_netbuf = pst_curr_netbuf->next;

        if (OAL_SUCC != dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_tmp_netbuf))
        {
            OAM_ERROR_LOG0(0,OAM_SF_ANY,"{dmac_proc_wlan_drx_event_tx_adapt::dmac_adapt_tx_param_and_netbuf_hdr_init failed}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        hcc_slave_tx(pst_tmp_netbuf, (oal_uint16)ul_payload_len, &param);
    }

/*#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    pst_pps_process->p_auto_freq_count_func(us_netbuf_num);
#endif*/

    if(us_loop != us_netbuf_num)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac wlan drx mem leak,still reamin %d netbufs}",
                                                        us_netbuf_num - us_loop);
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_proc_tkip_mic_fail_tx_adapt
 ��������  : tkip mic fail�¼��ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_proc_tkip_mic_fail_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem,NULL, OAL_SIZEOF(dmac_to_hmac_mic_event_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_proc_crx_event_tx_adapt
 ��������  : crx_event��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32 dmac_proc_crx_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_wlan_crx_event_stru              *pst_ctx_event;
    mac_rx_ctl_stru    *pst_rx_cb;

    pst_event   = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_wlan_crx_event_stru *)pst_event->auc_event_data;

	if(NULL == pst_ctx_event->pst_netbuf)
	{
		OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_proc_crx_event_tx_adapt::netbuf = OAL_PTR_NULL!}");
		return OAL_ERR_CODE_PTR_NULL;
	}

    pst_rx_cb = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_ctx_event->pst_netbuf);
    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                       pst_rx_cb->us_frame_len);
}


/*****************************************************************************
 �� �� ��  : dmac_scan_report_scanned_bss_tx_adapt
 ��������  : dmac����hcc�¼���dmac�ϱ�ÿ��ɨ���bss��Ϣ�ķ�������ӿ�
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_scan_report_scanned_bss_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16 payload_len;
    frw_event_stru                 *pst_event;                /* ������ȡҵ���¼�����Ϣ */
    dmac_tx_event_stru             *pst_ctx_event;
	if(NULL == pst_event_mem)
	{
		return OAL_ERR_CODE_PTR_NULL;
	}
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    payload_len = (pst_ctx_event->us_frame_len > MAC_80211_FRAME_LEN)?
                    (pst_ctx_event->us_frame_len - MAC_80211_FRAME_LEN)
                    :MAC_80211_FRAME_LEN;

    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                         payload_len);
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

oal_uint32 dmac_dpd_data_cali_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                 *pst_event;
    dmac_tx_event_stru             *pst_ctx_event;

    if(NULL == pst_event_mem)
    {
       OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_cali_tx_adapt::pst_event_mem null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "dmac_dpd_data_cali_tx_adapt\n\r");

    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                         pst_ctx_event->us_frame_len);
}

#endif
/*****************************************************************************
 �� �� ��  : dmac_proc_mgmt_rx_delba_event_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��3��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_proc_mgmt_rx_delba_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                        OAL_SIZEOF(dmac_ctx_action_event_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_rx_send_event_tx_adapt
 ��������  : device����յ���֡������ȥ��֤����ȥ������Ϣ��host�࣬host����ж�Ӧ�Ĵ���
 �������  : frw_event_mem_stru *pst_event_mem
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��13��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_send_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(dmac_diasoc_deauth_event));
}

/*****************************************************************************
 �� �� ��  : dmac_switch_to_new_chan_complete_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��16��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_switch_to_new_chan_complete_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                     OAL_SIZEOF(dmac_set_chan_stru));
}

/*****************************************************************************
 �� �� ��  : dmac_dbac_status_notify_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dbac_status_notify_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                     OAL_SIZEOF(oal_bool_enum_uint8));
}

/*****************************************************************************
 �� �� ��  : dmac_hcc_scan_comp_event_tx_adapt
 ��������  : ͨ��SDIO�ϱ�ɨ������¼��ķ������亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_scan_proc_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(mac_scan_rsp_stru));
}

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
/*****************************************************************************
 �� �� ��  : dmac_alg_flowctl_backp_tx_adapt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   :x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_alg_flowctl_backp_tx_adapt(frw_event_mem_stru * pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(mac_ioctl_queue_backp_stru));
}

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : dmac_scan_proc_obss_scan_comp_event_tx_adapt
 ��������  : ͨ��SDIO�ϱ�OBSSɨ������¼��ķ������亯��
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_scan_proc_obss_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(dmac_obss_te_a_b_stru));
}
#endif

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_proc_chan_result_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_crx_chan_result_stru    *pst_event_payload;
    oal_netbuf_stru              *pst_scan_comp_netbuf;

    struct hcc_transfer_param param;

    /* �����Ϸ��Լ�� */
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_WARNING_LOG0(0,OAM_SF_SCAN,"dmac_proc_chan_result_event_tx_adapt:pst_event_mem null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�ŵ�ͳ�Ʋ�������ϱ�ҵ���¼��Ľṹ����Ϣ */
    pst_event_payload = (dmac_crx_chan_result_stru *)frw_get_event_payload(pst_event_mem);;

    /* ����netbuf�����ɨ���¼��ṹ����Я����ɨ�������Ϣ */
    pst_scan_comp_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_scan_comp_netbuf)
    {
        OAM_WARNING_LOG0(0,OAM_SF_SCAN,"dmac_proc_chan_result_event_tx_adapt:alloc pst_scan_comp_netbuf fail");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /*  ��ɨ������Ľṹ����Ϣ������netbuff������ */
    OAL_MEMZERO(oal_netbuf_cb(pst_scan_comp_netbuf), OAL_TX_CB_LEN);
    oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_scan_comp_netbuf)),
                (oal_uint8 *)pst_event_payload,
                OAL_SIZEOF(dmac_crx_chan_result_stru));

    if (OAL_SUCC != dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_scan_comp_netbuf))
    {
        OAM_WARNING_LOG0(0,OAM_SF_SCAN,"dmac_proc_chan_result_event_tx_adapt::dmac_adapt_tx_param_and_netbuf_hdr_init fail");
        oal_netbuf_free(pst_scan_comp_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hcc_slave_tx(pst_scan_comp_netbuf, OAL_SIZEOF(dmac_crx_chan_result_stru),&param);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_process_rx_data_event_adapt_default
 ��������  : tx_process_data_event��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��7��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru* dmac_process_rx_data_event_adapt_default(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;
    frw_event_hdr_stru              *pst_hcc_event_hdr;

    oal_uint8                        uc_chip_id;
    oal_uint8                        uc_device_id;
    oal_uint8                        uc_vap_id;

    frw_event_mem_stru              *pst_event_mem;
    dmac_tx_event_stru              *pst_dmac_tx_event_payload;
    mac_tx_ctl_stru                 *pst_tx_ctl;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START);

     /*step1 ȡHCC�¼�ͷ*/
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);

    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /*step2 ȡHCC�¼���Ϣ*/
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*step3 ����ҵ���¼�*/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
       OAL_MEM_NETBUF_FREE(pst_hcc_event_payload->pst_netbuf);
       return OAL_PTR_NULL;
    }

    /*step4 ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                   pst_hcc_event_hdr->en_type,
                   pst_hcc_event_hdr->uc_sub_type,
                   OAL_SIZEOF(dmac_tx_event_stru),
                   FRW_EVENT_PIPELINE_STAGE_1,
                   uc_chip_id,
                   uc_device_id,
                   uc_vap_id);

    /*step5 ��ҵ���¼���Ϣ*/
    pst_dmac_tx_event_payload               = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_dmac_tx_event_payload->pst_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_dmac_tx_event_payload->us_frame_len = (oal_uint16) pst_hcc_event_payload->ul_buf_len;

    /* pad��Ϊ0ʱ�Ž������ݰ��� */
    if (OAL_UNLIKELY(0 != ((struct hcc_header *)OAL_NETBUF_HCCHDR(pst_dmac_tx_event_payload->pst_netbuf))->pad_payload))
    {
        oal_memmove((oal_uint8 *)OAL_NETBUF_DATA(pst_dmac_tx_event_payload->pst_netbuf),
                    (oal_uint8 *)OAL_NETBUF_HCC_PAYLOAD(pst_dmac_tx_event_payload->pst_netbuf),
                    pst_dmac_tx_event_payload->us_frame_len);
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dmac_tx_event_payload->pst_netbuf);
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = pst_dmac_tx_event_payload->us_frame_len;

    pst_dmac_tx_event_payload->us_frame_len += MAC_80211_FRAME_LEN;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_END);

    return pst_event_mem;

}

/*****************************************************************************
 �� �� ��  : dmac_hcc_rx_convert_netbuf_to_event_default
 ��������  : dmac rx �¼�ͳһ�Ľ������亯��
 �������  : frw_event_mem_stru *
 �������  : ��
 �� �� ֵ  : frw_event_mem_stru*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��21��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/

frw_event_mem_stru* dmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru * pst_hcc_event_mem)
{
    frw_event_stru                  *pst_hcc_event;
    hcc_event_stru                  *pst_hcc_event_payload;
    pst_hcc_event           = (frw_event_stru *)pst_hcc_event_mem->puc_data;
    pst_hcc_event_payload   = (hcc_event_stru *)pst_hcc_event->auc_event_data;
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,pst_hcc_event_payload->ul_buf_len);
}

/*****************************************************************************
 �� �� ��  : dmac_scan_proc_scan_req_event_rx_adapt
 ��������  : ͨ��SDIO�·�ɨ��������Ϣ
             dmac���ղ࣬��Ҫ��hcc�¼����ݾ���ת��Ϊ����ҵ���¼�
 �������  : frw_event_mem_stru *pst_hcc_event_mem��ԭ�ȵ�hcc�¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru* dmac_scan_proc_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    frw_event_hdr_stru         *pst_hcc_event_hdr;
    hcc_event_stru             *pst_hcc_event_payload;
    oal_netbuf_stru            *pst_scan_req_netbuf;
    frw_event_type_enum_uint8   en_type;
    oal_uint8                   uc_sub_type;
    oal_uint8                   uc_chip_id;
    oal_uint8                   uc_device_id;
    oal_uint8                   uc_vap_id;
    frw_event_mem_stru         *pst_event_mem;              /* ҵ���¼������Ϣ */
    mac_scan_req_stru          *pst_h2d_scan_req_params;    /* ɨ��������� */

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hcc_event_mem))
    {
        return OAL_PTR_NULL;
    }

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_scan_proc_scan_req_event_rx_adapt:: scan req, enter into rx adapt.}");

    /* ��ȡHCC�¼���Ϣ */
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_scan_req_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);
    en_type               = pst_hcc_event_hdr->en_type;
    uc_sub_type           = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id            = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id          = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id             = pst_hcc_event_hdr->uc_vap_id;

    /* ����ҵ���¼� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_scan_req_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
       OAL_MEM_NETBUF_FREE(pst_scan_req_netbuf);
       return OAL_PTR_NULL;
    }

    /* ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       OAL_SIZEOF(mac_scan_req_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    /* ��ɨ��������ݿ������¼��ڴ�data���� */
    pst_h2d_scan_req_params = (mac_scan_req_stru *)frw_get_event_payload(pst_event_mem);
    oal_memcopy(pst_h2d_scan_req_params, OAL_NETBUF_HCC_PAYLOAD(pst_scan_req_netbuf), OAL_SIZEOF(mac_scan_req_stru));

    /* �ͷ�hcc�¼������netbuf�ڴ� */
    OAL_MEM_NETBUF_FREE(pst_scan_req_netbuf);

    /*���ҵ���¼�������ʵ�ʺ�������*/
    return pst_event_mem;
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
frw_event_mem_stru*   dmac_dpd_data_processed_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
   frw_event_hdr_stru         *pst_hcc_event_hdr;
   oal_netbuf_stru            *pst_dpd_data_netbuf;
   frw_event_mem_stru         *pst_event_mem;
   dmac_tx_event_stru         *pst_dmac_tx_event;


   if (OAL_PTR_NULL == pst_hcc_event_mem)
   {
       //OAM_INFO_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_hcc_event_mem null.}");
       return OAL_PTR_NULL;
   }

   OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: dpd enter into rx adapt.}");

   pst_dpd_data_netbuf   = ((hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->pst_netbuf;
   pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);

   pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
   if (OAL_PTR_NULL == pst_event_mem)
   {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_event_mem null.}");
      OAL_MEM_NETBUF_FREE(pst_dpd_data_netbuf);
      return OAL_PTR_NULL;
   }

   FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       pst_hcc_event_hdr->en_type,
                       pst_hcc_event_hdr->uc_sub_type,
                       OAL_SIZEOF(dpd_cali_data_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hcc_event_hdr->uc_chip_id,
                       pst_hcc_event_hdr->uc_device_id,
                       pst_hcc_event_hdr->uc_vap_id);


   pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
   pst_dmac_tx_event->pst_netbuf = pst_dpd_data_netbuf;
   pst_dmac_tx_event->us_frame_len = OAL_SIZEOF(dpd_cali_data_stru);

   return pst_event_mem;
}
#endif

frw_event_mem_stru*   dmac_cali_hmac2dmac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
   frw_event_hdr_stru         *pst_hcc_event_hdr;
   oal_netbuf_stru            *pst_dpd_data_netbuf;
   frw_event_mem_stru         *pst_event_mem;
   dmac_tx_event_stru         *pst_dmac_tx_event;


   if (OAL_PTR_NULL == pst_hcc_event_mem)
   {
       //OAM_INFO_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_hcc_event_mem null.}");
       return OAL_PTR_NULL;
   }
   //OAL_IO_PRINT("dmac_cali_hmac2dmac_rx_adapt: start\r\n");
   //OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: dpd enter into rx adapt.}");

   pst_dpd_data_netbuf   = ((dmac_tx_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->pst_netbuf;
   pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);

   pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
   if (OAL_PTR_NULL == pst_event_mem)
   {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_event_mem null.}");
      OAL_MEM_NETBUF_FREE(pst_dpd_data_netbuf);
      return OAL_PTR_NULL;
   }

   FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       pst_hcc_event_hdr->en_type,
                       pst_hcc_event_hdr->uc_sub_type,
                       OAL_WIFI_CALI_DATA_DOWNLOAD_LEN,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hcc_event_hdr->uc_chip_id,
                       pst_hcc_event_hdr->uc_device_id,
                       pst_hcc_event_hdr->uc_vap_id);


   pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
   pst_dmac_tx_event->pst_netbuf = pst_dpd_data_netbuf;
   pst_dmac_tx_event->us_frame_len = ((dmac_tx_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->us_frame_len;
   pst_dmac_tx_event->us_remain = ((dmac_tx_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->us_remain;

   return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : dmac_scan_proc_sched_scan_req_event_rx_adapt
 ��������  : ͨ��SDIO�·�PNO����ɨ��������Ϣ
             dmac���ղ࣬��Ҫ��hcc�¼����ݾ���ת��Ϊ����ҵ���¼�
 �������  : frw_event_mem_stru *pst_hcc_event_mem��ԭ�ȵ�hcc�¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru* dmac_scan_proc_sched_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    frw_event_hdr_stru            *pst_hcc_event_hdr;
    hcc_event_stru                *pst_hcc_event_payload;
    frw_event_mem_stru            *pst_event_mem;              /* ҵ���¼������Ϣ */
    oal_netbuf_stru               *pst_pno_scan_req_netbuf;
    mac_device_stru               *pst_mac_device;
    frw_event_type_enum_uint8      en_type;
    oal_uint8                      uc_sub_type;
    oal_uint8                      uc_chip_id;
    oal_uint8                      uc_device_id;
    oal_uint8                      uc_vap_id;
    mac_pno_sched_scan_mgmt_stru  *pst_pno_sched_scan_mgmt;

    /* ��ȡHCC�¼���Ϣ */
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_pno_scan_req_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);
    en_type               = pst_hcc_event_hdr->en_type;
    uc_sub_type           = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id            = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id          = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id             = pst_hcc_event_hdr->uc_vap_id;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::pst_mac_device is null.}");
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        return OAL_PTR_NULL;
    }

    /* ����ҵ���¼� */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::alloc event mem failed.}");
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        return OAL_PTR_NULL;
    }

    /* ��ҵ���¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       0,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    if (OAL_PTR_NULL != pst_mac_device->pst_pno_sched_scan_mgmt)
    {
        OAL_MEM_FREE(pst_mac_device->pst_pno_sched_scan_mgmt, OAL_TRUE);
        pst_mac_device->pst_pno_sched_scan_mgmt = OAL_PTR_NULL;
    }

    /* �������ڹ���PNO����ɨ����ڴ棬��̬���룬��ʡ�ڴ�(564K,ֻ��һƬ) */
    pst_pno_sched_scan_mgmt =(mac_pno_sched_scan_mgmt_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_pno_sched_scan_mgmt_stru), OAL_FALSE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_pno_sched_scan_mgmt))
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::alloc pno sched scan mem size[%d]failed}",OAL_SIZEOF(mac_pno_sched_scan_mgmt_stru));
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_PTR_NULL;
    }

    pst_mac_device->pst_pno_sched_scan_mgmt = pst_pno_sched_scan_mgmt;

    /* ��PNO����ɨ���������ֱ�ӿ�����device�ṹ���£�����netbuf������ȥ */
    oal_memcopy(&(pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params),
                OAL_NETBUF_HCC_PAYLOAD(pst_pno_scan_req_netbuf), OAL_SIZEOF(mac_pno_scan_stru));

    /* ��ӡPNO����ɨ����� */
    OAM_WARNING_LOG4(0, OAM_SF_SCAN,
                 "{dmac_scan_proc_sched_scan_req_event_rx_adapt::pno scan params ssid_count[%d],rssi_thold[%d],interval[%d],repeat_times[%d].}",
                 pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.l_ssid_count,
                 pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.l_rssi_thold,
                 pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval,
                 pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.uc_pno_scan_repeat);

    /* �ͷ�hcc�¼������netbuf�ڴ� */
    OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);

    /*���ҵ���¼�������ʵ�ʺ�������*/
    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : dmac_proc_disasoc_misc_event_tx_adapt
 ��������  : dmac����hcc�¼���dmac�ϱ�ÿ��ȥ�����¼���������ӿ�
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_proc_disasoc_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, OAL_SIZEOF(dmac_disasoc_misc_stru));
}

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 �� �� ��  : dmac_proc_roam_trigger_event_tx_adapt
 ��������  : dmac����hcc�¼���dmac�ϱ�ÿ��ȥ�����¼���������ӿ�
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_proc_roam_trigger_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, OAL_SIZEOF(oal_int8));
}
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 �� �� ��  : dmac_proc_disasoc_misc_event_tx_adapt
 ��������  : dmac����hcc�¼���dmac�ϱ�ÿ��ȥ�����¼���������ӿ�
 �������  : frw_event_mem_stru *pst_event_mem��ԭ�ȵ�ҵ���¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC�� ����ǰ����ɹ�
             ������     ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��19��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_cali2hmac_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_netbuf_stru                 *pst_tmp_netbuf = NULL;
    oal_netbuf_stru                 *pst_curr_netbuf;

    oal_uint16                       us_loop;
    oal_uint16                       us_netbuf_num;
    oal_uint16                       us_remained_netbuf_num;
    hal_cali_hal2hmac_event_stru   *pst_cali_tx_event;      /* wlan rx�¼� */

    pst_cali_tx_event             = (hal_cali_hal2hmac_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_curr_netbuf         = pst_cali_tx_event->pst_netbuf;
    us_netbuf_num           = pst_cali_tx_event->us_netbuf_num;
    us_remained_netbuf_num  = us_netbuf_num;
    //OAL_IO_PRINT("dmac_cali2hmac_misc_event_tx_adapt start\r\n");

    for (us_loop = 0; (us_loop < us_netbuf_num) && (us_remained_netbuf_num > 0); us_loop++)
    {
        struct hcc_transfer_param param;
        if(NULL == pst_curr_netbuf)
        {
            /*netbuf list num < list head's num?*/
            OAL_IO_PRINT("[ERROR]had post %d netbufs,but list num is:%d,miss %d\r\n",
                                    us_loop,us_netbuf_num,us_netbuf_num - us_loop);
            break;
        }

        pst_tmp_netbuf = pst_curr_netbuf;

		/* ָ��netbuf�������һ��netbuf */
        pst_curr_netbuf = pst_curr_netbuf->next;
        us_remained_netbuf_num--;
        //OAL_IO_PRINT("dmac_cali2hmac_misc_event_tx_adapt loop:%d\r\n",us_loop);
        if (OAL_SUCC != dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_tmp_netbuf))
        {
            OAM_WARNING_LOG0(0,OAM_SF_SCAN,"dmac_proc_chan_result_event_tx_adapt::dmac_adapt_tx_param_and_netbuf_hdr_init fail");
            return OAL_ERR_CODE_PTR_NULL;
        }

        hcc_slave_tx(pst_tmp_netbuf, (oal_uint16)WLAN_LARGE_NETBUF_SIZE, &param);
    }

    if(0 != us_remained_netbuf_num)
    {
        OAL_IO_PRINT("[WARN]wlan drx mem leak,still reamin %d netbufs\r\n",us_remained_netbuf_num);
    }

    return OAL_SUCC;

}

oal_int32 dmac_rx_extend_hdr_vaild_check(struct frw_hcc_extend_hdr* pst_extend_hdr)
{
    if(OAL_UNLIKELY(pst_extend_hdr->en_nest_type >= FRW_EVENT_TYPE_BUTT))
    {
        return OAL_FALSE;
    }
#if 0
    if(OAL_UNLIKELY(pst_extend_hdr->vap_id > WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}

oal_int32 dmac_rx_wifi_post_action_function(oal_uint8 stype,
                                             hcc_netbuf_stru* pst_hcc_netbuf, oal_uint8 *pst_context)
{
    oal_int32 ret;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_vap_stru                  *pst_dmac_vap;
    frw_event_hdr_stru             *pst_dmac_event_hdr;
#endif
    frw_event_mem_stru  *pst_event_mem;
    if (OAL_PTR_NULL == pst_context)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{dmac_rx_wifi_post_action_function::pst_hcc_netbuf and pst_context NULL}");
        return -OAL_EINVAL;
    }

    pst_event_mem = (frw_event_mem_stru *)pst_context;

    OAL_BUG_ON(NULL == pst_event_mem);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_dmac_event_hdr = frw_get_event_hdr(pst_event_mem);
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_dmac_event_hdr->uc_vap_id);
    if(OAL_UNLIKELY(NULL == pst_dmac_vap))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "dmac rx adapt ignored,pst vap is null, vap id:%u", pst_dmac_event_hdr->uc_vap_id);
        OAL_MEM_NETBUF_FREE(pst_hcc_netbuf->pst_netbuf);
        FRW_EVENT_FREE(pst_event_mem);
        return -OAL_EINVAL;
    }

    if(OAL_UNLIKELY(MAC_VAP_VAILD != pst_dmac_vap->st_vap_base_info.uc_init_flag))
    {
        if((FRW_EVENT_TYPE_HOST_CRX == pst_dmac_event_hdr->en_type && HMAC_TO_DMAC_SYN_CREATE_CFG_VAP == pst_dmac_event_hdr->uc_sub_type)
            ||(FRW_EVENT_TYPE_HOST_CRX == pst_dmac_event_hdr->en_type && HMAC_TO_DMAC_SYN_CFG == pst_dmac_event_hdr->uc_sub_type)
            || (0 == pst_dmac_event_hdr->uc_vap_id))
        {
            /*1.��VAP�����¼��·�ʱ�����ˣ���Ϊ��ʱDMAC VAP��û�г�ʼ��,
              2.cfg vap ������*/
        }
        else
        {
            /*����δ��ʼ����VAP�¼�*/
            OAM_WARNING_LOG2(pst_dmac_event_hdr->uc_vap_id, OAM_SF_ANY,
                                "dmac rx adapt ignored,main:%u,sub:%u", pst_dmac_event_hdr->en_type, pst_dmac_event_hdr->uc_sub_type);
            OAL_MEM_NETBUF_FREE(pst_hcc_netbuf->pst_netbuf);
            FRW_EVENT_FREE(pst_event_mem);
            return -OAL_ENOMEM;
        }
    }
#endif

    ret = (oal_int32)frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return ret;
}

oal_int32 dmac_rx_wifi_pre_action_function(oal_uint8 stype, hcc_netbuf_stru* pst_hcc_netbuf,
                                                  oal_uint8  **pre_do_context)
{
    /*Ԥ�������¼��ڴ棬����¼��ڴ�����ʧ�ܣ�netbuf����ͣ����HCC�����У�
      ��ֹfrw event ������HCC�϶���*/
    frw_event_mem_stru    *pst_event_mem;
    hcc_event_stru        *pst_hcc_event_payload;
    struct frw_hcc_extend_hdr* pst_hdr;
/*#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    struct oal_auto_freq_pps_process_func_handler* pst_pps_process = oal_get_dmac_auto_freq_pps_process_func();
#endif*/

	pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        /*alloc failed,keep the netbuf in the rx queue!*/
        return -OAL_ENOMEM;
    }

    pst_hdr = dmac_get_hcc_rx_extend_hdr_addr(pst_hcc_netbuf->pst_netbuf);
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);

    //OAL_IO_PRINT("pst_hdr->en_nest_type:%u,pst_hdr->uc_nest_sub_type:%u\r\n",pst_hdr->en_nest_type,pst_hdr->uc_nest_sub_type);
    /*��д�¼�ͷ*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
    				  pst_hdr->en_nest_type,
                      pst_hdr->uc_nest_sub_type,
                      OAL_SIZEOF(hcc_event_stru),
                      FRW_EVENT_PIPELINE_STAGE_1,
                      pst_hdr->chip_id,
                      pst_hdr->device_id,
                      pst_hdr->vap_id);

    g_hcc_sched_event_pkts[pst_hdr->en_nest_type]++;

/*#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    pst_pps_process->p_auto_freq_count_func(1);
#endif*/

    pst_hcc_event_payload->pst_netbuf = pst_hcc_netbuf->pst_netbuf;
    pst_hcc_event_payload->ul_buf_len = (oal_uint32)pst_hcc_netbuf->len;

    *pre_do_context = (oal_uint8*)pst_event_mem;
    return OAL_SUCC;
}

oal_int32 dmac_hcc_adapt_init(oal_void)
{
    OAL_MEMZERO(g_hcc_sched_event_pkts, OAL_SIZEOF(g_hcc_sched_event_pkts));
    return hcc_rx_register(hcc_get_default_handler(), HCC_ACTION_TYPE_WIFI,
                        dmac_rx_wifi_post_action_function, dmac_rx_wifi_pre_action_function);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

