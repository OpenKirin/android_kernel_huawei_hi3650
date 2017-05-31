/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Oam_statistics.c
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2013��12��25��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��12��25��
    ��    ��   : z00237171
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
#include "oam_main.h"
#include "oam_statistics.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_STATISTICS_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151) || defined(_PRE_PRODUCT_ID_HI110X_HOST)
/* ͳ����Ϣȫ�ֱ��� */
oam_stat_info_stru g_st_stat_info;
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : oam_stats_report_irq_info_to_sdt
 ��������  : �ж�ͳ����Ϣ�ϱ�SDT
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_stats_report_irq_info_to_sdt(
                                    oal_uint8 *puc_irq_info_addr,
                                    oal_uint16  us_irq_info_len)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;


    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return ;
    }

    if (OAL_PTR_NULL == puc_irq_info_addr)
    {
        OAL_IO_PRINT("oam_stats_report_irq_info_to_sdt::puc_irq_info_addr is null!\n");
        return;
    }

    /* Ϊ�ϱ�����������ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_irq_info_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_irq_info_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_IRQ;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_irq_info_len;
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 2;
#else
    pst_ota_data->st_ota_hdr.auc_resv[0]    = 3;
#endif

    /* ��������,��дota���� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_irq_info_addr,
                (oal_uint32)us_irq_info_len);

    /* �·���sdt���ն��У����������򴮿���� */
    oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);
}


/*****************************************************************************
 �� �� ��  : oam_stats_report_timer_info_to_sdt
 ��������  : �������ʱ������Ϣ�ϱ�SDT
 �������  : puc_timer_addr:��ʱ���ṹ�ĵ�ַ
             uc_timer_len  :��ʱ���ṹ�ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_report_timer_info_to_sdt(
                                    oal_uint8 *puc_timer_addr,
                                    oal_uint8  uc_timer_len)
{
    oal_uint32 ul_ret = OAL_SUCC;

    if (NULL != puc_timer_addr)
    {
        ul_ret = oam_ota_report(puc_timer_addr, uc_timer_len, 0, 0, OAM_OTA_TYPE_TIMER);
        return ul_ret;
    }
    else
    {
        OAL_IO_PRINT("oam_stats_report_timer_info_to_sdt::puc_timer_addr is NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }


#if 0
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == puc_timer_addr)
    {
        OAL_IO_PRINT("oam_stats_report_timer_info_to_sdt::puc_timer_addr is null!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAM_TIMER_MAX_LEN < uc_timer_len)
    {
        OAL_IO_PRINT("oam_stats_report_timer_info_to_sdt::uc_timer_len-->%d\n",
                      uc_timer_len);
        return OAL_FAIL;
    }

    /* Ϊ�ϱ�����������ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = uc_timer_len + OAL_SIZEOF(oam_ota_hdr_stru);

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_TIMER;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = uc_timer_len;

    /* ��������,��дota���� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_timer_addr,
                (oal_uint32)uc_timer_len);

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
    #endif
}

/*****************************************************************************
 �� �� ��  : oam_stats_report_mempool_info_to_sdt
 ��������  : ���ڴ�ص�ĳһ���ӳ��ڴ���ʹ������ϱ�sdt
 �������  : uc_pool_id            :�ڴ��id
             us_pool_total_cnt     :���ڴ��һ�������ڴ��
             us_pool_used_cnt      :���ڴ�������ڴ��
             uc_subpool_id         :�ӳ�id
             us_subpool_total_cnt  :���ӳ��ڴ������
             us_subpool_free_cnt   :���ӳؿ����ڴ�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 oam_stats_report_mempool_info_to_sdt(
                                        oal_uint8           uc_pool_id,
                                        oal_uint16          us_pool_total_cnt,
                                        oal_uint16          us_pool_used_cnt,
                                        oal_uint8           uc_subpool_id,
                                        oal_uint16          us_subpool_total_cnt,
                                        oal_uint16          us_subpool_free_cnt)
{
    oam_stats_mempool_stru        st_device_mempool_info;
    oal_netbuf_stru              *pst_netbuf;
    oam_ota_stru                 *pst_ota_data;
    oal_uint16                    us_skb_len;        /* skb�ܳ��� */
    oal_uint32                    ul_tick;
    oal_uint32                    ul_ret    = OAL_SUCC;
    oal_uint16                    us_stru_len;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��дҪ�ϱ���sdt���ڴ����Ϣ�ṹ�� */
    st_device_mempool_info.uc_mem_pool_id          = uc_pool_id;
    st_device_mempool_info.uc_subpool_id           = uc_subpool_id;
    st_device_mempool_info.us_mem_pool_total_cnt   = us_pool_total_cnt;
    st_device_mempool_info.us_mem_pool_used_cnt    = us_pool_used_cnt;
    st_device_mempool_info.us_subpool_total_cnt    = us_subpool_total_cnt;
    st_device_mempool_info.us_subpool_free_cnt     = us_subpool_free_cnt;

    us_stru_len = OAL_SIZEOF(oam_stats_mempool_stru);
    /* Ϊota��Ϣ�ϱ�SDT����ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_stru_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_stru_len = us_skb_len - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_MEMPOOL;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_stru_len;

    /* ��������,��дota���� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)&st_device_mempool_info,
                (oal_uint32)us_stru_len);

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : oam_stats_report_memblock_info_to_sdt
 ��������  : ����׼�ڴ�����Ϣ�ϱ�SDT
 �������  : puc_origin_data:�ڴ�����ʼ��ַ
             uc_user_cnt    :���ڴ�����ü���
             uc_pool_id     :�������ڴ��id
             uc_subpool_id  :�������ӳ�id
             us_len         :���ڴ�鳤��
             ul_file_id     :������ڴ����ļ�id
             ul_alloc_line_num :������ڴ����к�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_report_memblock_info_to_sdt(
                                     oal_uint8  *puc_origin_data,
                                     oal_uint8   uc_user_cnt,
                                     oal_uint8   uc_pool_id,
                                     oal_uint8   uc_subpool_id,
                                     oal_uint16  us_len,
                                     oal_uint32  ul_file_id,
                                     oal_uint32  ul_alloc_line_num)
{
    oam_memblock_info_stru        st_memblock_info;
    oal_uint16                    us_memblock_info_len;
    oal_netbuf_stru              *pst_netbuf;
    oam_ota_stru                 *pst_ota_data;
    oal_uint16                    us_skb_len;        /* skb�ܳ��� */
    oal_uint32                    ul_tick;
    oal_uint32                    ul_ret    = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == puc_origin_data)
    {
        OAL_IO_PRINT("oam_stats_report_memblock_info_to_sdt:puc_origin_data is null!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_memblock_info_len = OAL_SIZEOF(oam_memblock_info_stru);

    /* ��дҪ�ϱ���sdt���ڴ����Ϣ�ṹ�� */
    st_memblock_info.uc_pool_id         = uc_pool_id;
    st_memblock_info.uc_subpool_id      = uc_subpool_id;
    st_memblock_info.uc_user_cnt        = uc_user_cnt;
    st_memblock_info.ul_alloc_line_num  = ul_alloc_line_num;
    st_memblock_info.ul_file_id         = ul_file_id;

    /* Ϊota��Ϣ�ϱ�SDT����ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_memblock_info_len + us_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        if ((us_memblock_info_len + OAL_SIZEOF(oam_ota_hdr_stru)) < us_skb_len)
        {
            us_len = us_skb_len - us_memblock_info_len - (oal_uint16)OAL_SIZEOF(oam_ota_hdr_stru);
        }
        else
        {
            us_memblock_info_len = us_skb_len - OAL_SIZEOF(oam_ota_hdr_stru);
            us_len = 0;
        }
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick          = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type      = OAM_OTA_TYPE_MEMBLOCK;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = (oal_uint8)us_memblock_info_len;
    pst_ota_data->st_ota_hdr.us_ota_data_len  = us_memblock_info_len + us_len;

    /* ��дota���ݲ���,���ȸ����ڴ�����Ϣ�ṹ�� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)&st_memblock_info,
                (oal_uint32)us_memblock_info_len);

    /* �����ڴ��ľ������� *//*lint -e416*/
    oal_memcopy((oal_void *)(pst_ota_data->auc_ota_data + us_memblock_info_len),
                (const oal_void *)puc_origin_data,
                (oal_uint32)us_len);

    /*lint +e416*/
    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : oam_stats_report_event_queue_info_to_sdt
 ��������  : ���¼�������ÿ���¼����¼�ͷ��Ϣ�ϱ�SDT
 �������  : puc_event_queue_addr:�¼�������Ϣ��ַ
             uc_event_queue_info_len:�¼�������Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_report_event_queue_info_to_sdt(
                                    oal_uint8   *puc_event_queue_addr,
                                    oal_uint16    us_event_queue_info_len)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == puc_event_queue_addr)
    {
        OAL_IO_PRINT("oam_stats_report_event_queue_info_to_sdt::puc_event_queue_addr is null!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* Ϊ�ϱ�����������ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_event_queue_info_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_event_queue_info_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_EVENT_QUEUE;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_event_queue_info_len;

    /* ��������,��дota���� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)puc_event_queue_addr,
                (oal_uint32)us_event_queue_info_len);

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)|| defined(_PRE_PRODUCT_ID_HI110X_HOST)
/*****************************************************************************
 �� �� ��  : oam_report_vap_pkt_stat_to_sdt
 ��������  : ��ĳһ��vap�µ��շ���ͳ����Ϣ�ϱ�sdt
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��10��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_report_vap_pkt_stat_to_sdt(oal_uint8 uc_vap_id)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;
    oal_uint16           us_stat_info_len;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_stat_info_len = OAL_SIZEOF(oam_vap_stat_info_stru);

    /* Ϊ�ϱ�ͳ����Ϣ����ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_stat_info_len + OAL_SIZEOF(oam_ota_hdr_stru);

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_VAP_STAT_INFO;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_stat_info_len;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    oal_set_mac_addr(pst_ota_data->st_ota_hdr.auc_user_macaddr, BROADCAST_MACADDR);

    /* ��������,��дota���� */
    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                        (const oal_void *)&g_st_stat_info.ast_vap_stat_info[uc_vap_id],
                        us_stat_info_len);

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : oam_stats_report_stat_info_to_sdt
 ��������  : ������ά��ͳ����Ϣ�ϱ�SDT����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_report_info_to_sdt(oam_ota_type_enum_uint8 en_ota_type)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;
    oal_uint16           us_stat_info_len;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch (en_ota_type)
    {
        case OAM_OTA_TYPE_DEV_STAT_INFO:
            us_stat_info_len = OAL_SIZEOF(oam_device_stat_info_stru) * WLAN_DEVICE_MAX_NUM_PER_CHIP;

            break;

        case OAM_OTA_TYPE_VAP_STAT_INFO:
            us_stat_info_len = (oal_uint16)(OAL_SIZEOF(oam_vap_stat_info_stru) * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT);

            break;

        default:
            us_stat_info_len = 0;

            break;
    }

    if (0 == us_stat_info_len)
    {
        OAL_IO_PRINT("oam_stats_report_info_to_sdt::ota_type invalid-->%d!\n", en_ota_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* Ϊ�ϱ�ͳ����Ϣ����ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_stat_info_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_stat_info_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = en_ota_type;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_stat_info_len;

    /* ��������,��дota���� */
    if (OAM_OTA_TYPE_DEV_STAT_INFO == en_ota_type)
    {
            oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                        (const oal_void *)g_st_stat_info.ast_dev_stat_info,
                        us_stat_info_len);
    }
    else
    {
            oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                        (const oal_void *)g_st_stat_info.ast_vap_stat_info,
                        us_stat_info_len);



    }

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : oam_stats_report_usr_info
 ��������  : ��ĳ���û���ͳ����Ϣ�ϱ�sdt
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_report_usr_info(oal_uint16  us_usr_id)
{
    oal_uint32           ul_tick;
    oal_uint16           us_skb_len;        /* skb�ܳ��� */
    oal_netbuf_stru     *pst_netbuf;
    oam_ota_stru        *pst_ota_data;
    oal_uint32           ul_ret         = OAL_SUCC;
    oal_uint16           us_stat_info_len;

    if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (us_usr_id >= WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    us_stat_info_len = OAL_SIZEOF(oam_device_stat_info_stru);

    /* Ϊ�ϱ�ͳ����Ϣ����ռ�,ͷ��Ԥ��8�ֽڣ�β��Ԥ��1�ֽڣ���sdt_drv�� */
    us_skb_len = us_stat_info_len + OAL_SIZEOF(oam_ota_hdr_stru);
    if (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD)
    {
        us_skb_len = WLAN_SDT_NETBUF_MAX_PAYLOAD;
        us_stat_info_len = WLAN_SDT_NETBUF_MAX_PAYLOAD - OAL_SIZEOF(oam_ota_hdr_stru);
    }

    pst_netbuf = oam_alloc_data2sdt(us_skb_len);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ota_data = (oam_ota_stru *)oal_netbuf_data(pst_netbuf);

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��дota��Ϣͷ�ṹ�� */
    pst_ota_data->st_ota_hdr.ul_tick     = ul_tick;
    pst_ota_data->st_ota_hdr.en_ota_type = OAM_OTA_TYPE_USER_STAT_INFO;
    pst_ota_data->st_ota_hdr.uc_frame_hdr_len = 0;
    pst_ota_data->st_ota_hdr.us_ota_data_len = us_stat_info_len;

    oal_memcopy((oal_void *)pst_ota_data->auc_ota_data,
                (const oal_void *)&g_st_stat_info.ast_user_stat_info[us_usr_id],
                us_stat_info_len);

    /* �·���sdt���ն��У����������򴮿���� */
    ul_ret = oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_OTA, OAM_PRIMID_TYPE_OUTPUT_CONTENT);

    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : oam_stats_clear_stat_info
 ��������  : ������ͳ����Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_stats_clear_stat_info(oal_void)
{
    OAL_MEMZERO(&g_st_stat_info, OAL_SIZEOF(oam_stat_info_stru));
}

/*****************************************************************************
 �� �� ��  : oam_stats_clear_vap_stat_info
 ��������  : vap������ʱ�������Ӧ��ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_clear_vap_stat_info(oal_uint8   uc_vap_id)
{
    if (uc_vap_id >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    OAL_MEMZERO(&g_st_stat_info.ast_vap_stat_info[uc_vap_id], OAL_SIZEOF(oam_vap_stat_info_stru));

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : oam_stats_clear_user_stat_info
 ��������  : �û�������ʱ�������Ӧ��ͳ����Ϣ����Ϊuser_id�Ǹ��õ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_stats_clear_user_stat_info(oal_uint16   us_usr_id)
{
    if (us_usr_id >= WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC * WLAN_ACTIVE_USER_MAX_NUM)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    OAL_MEMZERO(&g_st_stat_info.ast_user_stat_info[us_usr_id], OAL_SIZEOF(oam_user_stat_info_stru));

    return OAL_SUCC;
}

#endif
/*****************************************************************************
 �� �� ��  : oam_statistics_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_statistics_init(oal_void)
{
#if ((_PRE_OS_VERSION_RAW != _PRE_OS_VERSION) && (_PRE_OS_VERSION_WIN32_RAW != _PRE_OS_VERSION))
    oal_mempool_info_to_sdt_register(oam_stats_report_mempool_info_to_sdt,
                                     oam_stats_report_memblock_info_to_sdt);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)
    OAL_MEMZERO(&g_st_stat_info, OAL_SIZEOF(oam_stat_info_stru));
#endif
#endif
    return OAL_SUCC;
}

/*lint -e19*/

oal_module_symbol(oam_stats_report_irq_info_to_sdt);
oal_module_symbol(oam_stats_report_timer_info_to_sdt);
oal_module_symbol(oam_stats_report_mempool_info_to_sdt);
oal_module_symbol(oam_statistics_init);
oal_module_symbol(oam_stats_report_memblock_info_to_sdt);
oal_module_symbol(oam_stats_report_event_queue_info_to_sdt);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)|| defined(_PRE_PRODUCT_ID_HI110X_HOST)
oal_module_symbol(g_st_stat_info);
oal_module_symbol(oam_stats_report_info_to_sdt);
oal_module_symbol(oam_stats_clear_stat_info);
oal_module_symbol(oam_stats_clear_user_stat_info);
oal_module_symbol(oam_stats_clear_vap_stat_info);
oal_module_symbol(oam_stats_report_usr_info);
oal_module_symbol(oam_report_vap_pkt_stat_to_sdt);
#endif











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

