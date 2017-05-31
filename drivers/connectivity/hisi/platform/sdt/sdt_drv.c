/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Sdt_drv.c
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��1��23��
  ����޸�   :
  ��������   : SDT���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��23��
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
#include "oal_mem.h"
#include "sdt_drv.h"
#include "wal_ext_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_SDT_DRV_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
sdt_drv_mng_stru           g_st_sdt_drv_mng_entry;
oam_sdt_func_hook_stru     g_st_sdt_drv_func_hook;
#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
oal_uint8                  g_st_count = 0;
oal_uint32                 g_buf_offset = 0;

oal_netbuf_stru            *g_pst_copy_netbuf = NULL;
oal_nlmsghdr_stru          *g_pst_nlhdr = NULL;
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
OAL_STATIC oal_uint32  sdt_drv_netlink_send(oal_netbuf_stru *pst_netbuf, oal_uint32  ul_len);

/*****************************************************************************
 �� �� ��  : sdt_drv_set_mng_entry_usepid
 ��������  : ����sdt drv��Զ�netlink���̵�pid��
 �������  : oal_uint32  ulpid
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void sdt_drv_set_mng_entry_usepid(oal_uint32  ulpid)
{
    oal_uint    ui_irq_save;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    g_st_sdt_drv_mng_entry.ul_usepid = ulpid;

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
}

/*****************************************************************************
 �� �� ��  : sdt_drv_netbuf_add_to_list_tail
 ��������  : sdt�շ���Ϣ���
 �������  : oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  sdt_drv_netbuf_add_to_list(oal_netbuf_stru *pst_netbuf)
{
    oal_uint    ui_irq_save;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    oal_netbuf_add_to_list_tail(pst_netbuf, &g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);
}

/*****************************************************************************
 �� �� ��  : sdt_drv_netbuf_delist
 ��������  : sdt��Ϣ���г���
 �������  : ��
 �� �� ֵ  : oal_netbuf_stru*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_netbuf_stru* sdt_drv_netbuf_delist(oal_void)
{
    oal_uint                ui_irq_save;
    oal_netbuf_stru        *pst_netbuf;

    oal_spin_lock_irq_save(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    pst_netbuf = oal_netbuf_delist(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    oal_spin_unlock_irq_restore(&g_st_sdt_drv_mng_entry.st_spin_lock, &ui_irq_save);

    return pst_netbuf;
}
/*****************************************************************************
 �� �� ��  : sdt_drv_check_isdevlog
 ��������  : ����ϱ���־�Ƿ�Ϊdevice log
 �������  : oal_net
 �������  : ��
 �� �� ֵ  : int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : jwx222439
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 sdt_drv_check_isdevlog(oal_netbuf_stru *pst_netbuf)
{
    oal_uint8               *puc_pkt_tail;
    sdt_drv_pkt_hdr_stru    *pst_pkt_hdr;
    pst_pkt_hdr = (sdt_drv_pkt_hdr_stru *)oal_netbuf_data(pst_netbuf);
    puc_pkt_tail = (oal_uint8 *)pst_pkt_hdr + OAL_NETBUF_LEN(pst_netbuf);
    OAL_IO_PRINT("devlog {%s}\n", oal_netbuf_data(pst_netbuf));
    if (SDT_DRV_PKT_END_FLG == *puc_pkt_tail
        || SDT_DRV_PKT_START_FLG == pst_pkt_hdr->uc_data_start_flg)
    {
        OAL_IO_PRINT("check out is device log\n");
        return OAL_SUCC;
    }

    return -OAL_EFAIL;
}


/*****************************************************************************
 �� �� ��  : sdt_drv_add_pkt_head
 ��������  : ����������յ����ݣ�ǰ��������͵���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  sdt_drv_add_pkt_head(
                                      oal_netbuf_stru  *pst_netbuf,
                                      oam_data_type_enum_uint8  en_type,
                                      oam_primid_type_enum_uint8 en_prim_id)
{
    /*************************** buffer structure ****************************/
                    /**************************************/
                    /*   |data_hdr | data | data_tail |   */
                    /*------------------------------------*/
                    /*   |  8Byte  |      |    1Byte  |   */
                    /**************************************/

    /*************************************************************************/

    /************************ data header structure **************************/
    /* ucFrameStart | ucFuncType | ucPrimId | ucReserver | usFrameLen | usSN */
    /* --------------------------------------------------------------------- */
    /*    1Byte     |    1Byte   |  1Byte   |   1Byte    |  2Bytes    |2Bytes*/
    /*************************************************************************/

    oal_uint8               *puc_pkt_tail;
    sdt_drv_pkt_hdr_stru    *pst_pkt_hdr;
    oal_uint16               us_tmp_data;

    oal_netbuf_push(pst_netbuf, WLAN_SDT_SKB_HEADROOM_LEN);
    oal_netbuf_put(pst_netbuf, WLAN_SDT_SKB_TAILROOM_LEN);

    /* SDT�յ�����Ϣ��Ŀ��1 */
    g_st_sdt_drv_mng_entry.us_sn_num++;

    /* Ϊ����ͷ��ÿһ����Ա��ֵ */
    pst_pkt_hdr = (sdt_drv_pkt_hdr_stru *)oal_netbuf_data(pst_netbuf);

    pst_pkt_hdr->uc_data_start_flg = SDT_DRV_PKT_START_FLG;
    pst_pkt_hdr->en_msg_type       = en_type;
    pst_pkt_hdr->uc_prim_id        = en_prim_id;
    pst_pkt_hdr->uc_resv[0]        = 0;

    us_tmp_data = (oal_uint16)OAL_NETBUF_LEN(pst_netbuf);
    pst_pkt_hdr->uc_data_len_low_byte  = SDT_DRV_GET_LOW_BYTE(us_tmp_data);
    pst_pkt_hdr->uc_data_len_high_byte = SDT_DRV_GET_HIGH_BYTE(us_tmp_data);

    us_tmp_data = g_st_sdt_drv_mng_entry.us_sn_num;
    pst_pkt_hdr->uc_sequence_num_low_byte   = SDT_DRV_GET_LOW_BYTE(us_tmp_data);
    pst_pkt_hdr->uc_sequence_num_high_byte  = SDT_DRV_GET_HIGH_BYTE(us_tmp_data);

    /* Ϊ����β��ֵ0x7e */
    puc_pkt_tail = (oal_uint8 *)pst_pkt_hdr + OAL_NETBUF_LEN(pst_netbuf);
    puc_pkt_tail--;
   *puc_pkt_tail = SDT_DRV_PKT_END_FLG;
}


/*****************************************************************************
 �� �� ��  : sdt_drv_report_data2app
 ��������  : �ϱ��ں˲����Ϣ
 �������  : oal_netbuf_stru *pst_netbuf
             oam_data_type_enum_uint8 uc_type
             oam_primid_type_enum_uint8 uc_prim_id
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��11��,���ڶ�
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  sdt_drv_report_data2app(oal_netbuf_stru *pst_netbuf, oam_data_type_enum_uint8 en_type, oam_primid_type_enum_uint8 en_prim)
{
    /* ���ϲ���ýӿ��ж�ָ��ǿ� */
    oal_int32       l_ret;

    /*�����device log ����Ҫ��pkt ��ͷ*/
    if (OAM_DATA_TYPE_DEVICE_LOG != en_type)
    {
        sdt_drv_add_pkt_head(pst_netbuf, en_type, en_prim);
    }

    sdt_drv_netbuf_add_to_list(pst_netbuf);

    l_ret = oal_queue_work(g_st_sdt_drv_mng_entry.oam_rx_workqueue, &g_st_sdt_drv_mng_entry.rx_wifi_work);

    return l_ret;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_get_wq_len
 ��������  : ����sdt�������Ϣ�Ķ��г���
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��11��,���ڶ�
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32 sdt_drv_get_wq_len(oal_void)
{
    return (oal_int32)oal_netbuf_list_len(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);
}

/*****************************************************************************
 �� �� ��  : sdt_drv_send_data_to_wifi
 ��������  : ��app����յ����ݣ����������ݵ�ͷ����Ϣ��ȷ�������ݵ�ȥ��Ȼ��
             ������Ӧ��51������ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  sdt_drv_send_data_to_wifi(oal_uint8  *puc_param, oal_int32  l_len)
{
    oal_netbuf_stru         *pst_netbuf;
    oal_int8                *pc_buf;
    oal_int                  i_len;   /* SDIO CRC ERROR */
    oal_int32                l_ret = OAL_EFAIL;
    oal_uint8               *puc_data;

    if (OAL_PTR_NULL == puc_param)
    {
        OAL_IO_PRINT("sdt_drv_send_data_to_wifi::puc_param is null!\n");
        return -OAL_EFAIL;
    }

    i_len = (oal_int)l_len > 300 ? (oal_int)l_len: 300;

    /* ������Ϣ�������ͷ��ֱ��ʹ�� */
    pst_netbuf = oal_mem_sdt_netbuf_alloc((oal_uint16)i_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -OAL_EFAIL;
    }

    pc_buf = (oal_int8 *)oal_netbuf_put(pst_netbuf, (oal_uint32)l_len);
    oal_memcopy((oal_void *)pc_buf, (const oal_void *)puc_param, (oal_uint32)l_len);

    i_len = pc_buf[5]*MAX_NUM;
    i_len = pc_buf[4] + i_len;
    i_len = i_len - OAM_RESERVE_SKB_LEN;

    puc_data = oal_netbuf_data(pst_netbuf);

    switch(pc_buf[1])
    {
        case OAM_DATA_TYPE_MEM_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_mem_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_mem_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_REG_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_reg_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_reg_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_CFG:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_cfg_data_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_cfg_data_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        case OAM_DATA_TYPE_GVAR_RW:
            if (OAL_PTR_NULL != g_st_oam_wal_func_hook.p_wal_recv_global_var_func)
            {
                l_ret = g_st_oam_wal_func_hook.p_wal_recv_global_var_func(&puc_data[8], (oal_uint16)i_len);
            }
            break;

        default:
            OAL_IO_PRINT("sdt_drv_send_data_to_wifi::cmd is invalid!!-->%d\n", pc_buf[1]);
            break;
    }
#if (_PRE_OS_VERSION_RAW != _PRE_OS_VERSION)
    oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
#endif
    //oal_netbuf_free(pst_netbuf);
    return l_ret;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_netlink_send
 ��������  : SDT������ͨ��netlink��SDT APP��������
             ��¼�����͵������뷢��ʧ�ܵ����ݣ�ͨ�����кż�¼
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  sdt_drv_netlink_send(oal_netbuf_stru *pst_netbuf, oal_uint32  ul_len)
{
#if (_PRE_OS_VERSION_RAW != _PRE_OS_VERSION)
#if((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    oal_int32                   l_ret_len = 0;
    sdt_drv_pkt_hdr_stru       *p_sdt_hdr;
#endif
    oal_netbuf_stru            *pst_copy_netbuf;
    oal_nlmsghdr_stru          *pst_nlhdr;

    oal_uint32                  ul_nlmsg_len;
    oal_int32                   l_unicast_bytes  = 0;

    /* ���ϲ㱣֤�����ǿ� */

    /* ���û����app�������ӣ���ֱ�ӷ��أ�ÿ500�δ�ӡһ����ʾ��Ϣ */
    if (0 == g_st_sdt_drv_mng_entry.ul_usepid)
    {
        if (0 == (oal_atomic_read(&g_st_sdt_drv_mng_entry.ul_unconnect_cnt) % SDT_DRV_REPORT_NO_CONNECT_FREQUENCE))
        {
            OAL_IO_PRINT("Info:waitting app_sdt start...\r\n");
            oal_atomic_inc(&g_st_sdt_drv_mng_entry.ul_unconnect_cnt);
        }

        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        //oal_netbuf_free(pst_netbuf);

        return OAL_FAIL;
    }

#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    // ���ݰ�����
    p_sdt_hdr =  (sdt_drv_pkt_hdr_stru*)oal_netbuf_data(pst_netbuf);
    if (OAM_DATA_TYPE_LOG == p_sdt_hdr->en_msg_type || OAM_DATA_TYPE_OTA == p_sdt_hdr->en_msg_type)
    {
        if (0 == g_st_count)
        {
            ul_nlmsg_len = OAL_NLMSG_LENGTH(MAX_NLMSG_LEN);
            g_pst_copy_netbuf = oal_netbuf_alloc(ul_nlmsg_len, 0, WLAN_MEM_NETBUF_ALIGN);
            if (OAL_UNLIKELY(OAL_PTR_NULL == g_pst_copy_netbuf))
            {
                oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
                //oal_netbuf_free(pst_netbuf);

                OAL_IO_PRINT("oal_netbuf_alloc failed. \r\n");
                return OAL_FAIL;
            }

            g_pst_nlhdr = oal_nlmsg_put(g_pst_copy_netbuf, 0, 0, 0, (oal_int32)MAX_NLMSG_LEN, 0);
        }

        if (NULL != g_pst_nlhdr)
        {
            l_ret_len = MAX_NLMSG_LEN - g_buf_offset - ul_len;
            if (l_ret_len > 0)
            {
                oal_memcopy((oal_void *)OAL_NLMSG_DATA(g_pst_nlhdr) + g_buf_offset, (const oal_void *)oal_netbuf_data(pst_netbuf), ul_len);
                g_st_count++;
                g_buf_offset += ul_len;
            }
        }

        if (MAX_QUEUE_COUNT == g_st_count || g_buf_offset > MAX_CO_SIZE || l_ret_len < 0)
        {
            g_st_count = 0;
            g_buf_offset = 0;

            l_unicast_bytes = oal_netlink_unicast(g_st_sdt_drv_mng_entry.pst_nlsk, g_pst_copy_netbuf, g_st_sdt_drv_mng_entry.ul_usepid, 0);
            oal_msleep(300);

            OAM_SDT_STAT_INCR(ul_nlk_sd_cnt);
            if (l_unicast_bytes <= 0)
            {
                oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
                //oal_netbuf_free(pst_netbuf);
                oal_msleep(500);
                OAM_SDT_STAT_INCR(ul_nlk_sd_fail);
                return OAL_FAIL;
            }
        }

        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        return OAL_SUCC;
    }
#endif

   /* ��дnetlink��Ϣͷ */
    ul_nlmsg_len = OAL_NLMSG_SPACE(ul_len);
    pst_copy_netbuf = oal_netbuf_alloc(ul_nlmsg_len, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_copy_netbuf))
    {
        oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
        //oal_netbuf_free(pst_netbuf);

        OAL_IO_PRINT("oal_netbuf_alloc failed. \r\n");
        return OAL_FAIL;
    }

    pst_nlhdr = oal_nlmsg_put(pst_copy_netbuf, 0, 0, 0, (oal_int32)ul_len, 0);
    oal_memcopy((oal_void *)OAL_NLMSG_DATA(pst_nlhdr), (const oal_void *)oal_netbuf_data(pst_netbuf), ul_len);

    l_unicast_bytes = oal_netlink_unicast(g_st_sdt_drv_mng_entry.pst_nlsk, pst_copy_netbuf, g_st_sdt_drv_mng_entry.ul_usepid, OAL_MSG_DONTWAIT);

    oal_mem_sdt_netbuf_free(pst_netbuf, OAL_TRUE);
    //oal_netbuf_free(pst_netbuf);

    OAM_SDT_STAT_INCR(ul_nlk_sd_cnt);
    if (l_unicast_bytes <= 0)
    {
        OAM_SDT_STAT_INCR(ul_nlk_sd_fail);
        return OAL_FAIL;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_netlink_recv
 ��������  : ��SDT APP����յ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  sdt_drv_netlink_recv(oal_netbuf_stru  *pst_netbuf)
{
    oal_netbuf_stru                *pst_net_buf = OAL_PTR_NULL;
    oal_nlmsghdr_stru              *pst_nlhdr = OAL_PTR_NULL;
    sdt_drv_netlink_msg_hdr_stru    st_msg_hdr;
    oal_int32                       l_len;
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAL_IO_PRINT("sdt_drv_netlink_recv::pst_netbuf is null!\n");
        return;
    }
    pst_net_buf = oal_netbuf_get(pst_netbuf);
    OAL_MEMZERO(g_st_sdt_drv_mng_entry.puc_data, DATA_BUF_LEN);
    if (OAL_NETBUF_LEN(pst_net_buf) >= OAL_NLMSG_SPACE(0))
    {
        pst_nlhdr = oal_nlmsg_hdr((OAL_CONST oal_netbuf_stru *)pst_net_buf);
        l_len   = (oal_int32)OAL_NLMSG_PAYLOAD(pst_nlhdr, 0);

        if(l_len <= DATA_BUF_LEN)
        {
            oal_memcopy((oal_void *)g_st_sdt_drv_mng_entry.puc_data,
                        (const oal_void *)OAL_NLMSG_DATA(pst_nlhdr),
                        (oal_uint32)l_len);
        }
        else
        {
            /*overflow*/
            OAL_IO_PRINT("[ERROR]invaild netlink buff len:%u,max len:%u\n",(oal_uint32)l_len,DATA_BUF_LEN);
            oal_mem_sdt_netbuf_free(pst_net_buf, OAL_TRUE);
            return;
        }

        oal_memcopy((oal_void *)&st_msg_hdr,
                    (const oal_void *)g_st_sdt_drv_mng_entry.puc_data,
                    (oal_uint32)OAL_SIZEOF(st_msg_hdr));

        if (NETLINK_MSG_HELLO == st_msg_hdr.ul_cmd)
        {
            g_st_sdt_drv_mng_entry.ul_usepid = pst_nlhdr->nlmsg_pid;   /*pid of sending process */
            OAL_IO_PRINT("%s pid is-->%d \n", OAL_FUNC_NAME, g_st_sdt_drv_mng_entry.ul_usepid);
        }
#if defined(PLATFORM_DEBUG_ENABLE) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        else
        {
            sdt_drv_send_data_to_wifi(&g_st_sdt_drv_mng_entry.puc_data[OAL_SIZEOF(st_msg_hdr)], l_len - (oal_int32)OAL_SIZEOF(st_msg_hdr));
        }
#else
        OAL_IO_PRINT("user mode not accept msg except hello from sdt!\n");
#endif
    }

	oal_mem_sdt_netbuf_free(pst_net_buf, OAL_TRUE);
    //oal_netbuf_free(pst_net_buf);
}

/*****************************************************************************
 �� �� ��  : sdt_drv_netlink_create
 ��������  : ����netlink
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  sdt_drv_netlink_create(oal_void)
{
    g_st_sdt_drv_mng_entry.pst_nlsk = oal_netlink_kernel_create(&OAL_INIT_NET, NETLINK_TEST,
                                                          0, sdt_drv_netlink_recv,
                                                          OAL_PTR_NULL, OAL_THIS_MODULE);
    if (OAL_PTR_NULL == g_st_sdt_drv_mng_entry.pst_nlsk)
    {
        OAL_IO_PRINT("sdt_drv_netlink_create return fail!\n");
        return -OAL_EFAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_push_wifi_log_work
 ��������  : oam rx wifi skb log data
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  sdt_drv_push_wifi_log_work(oal_work_stru *work)
{
    oal_netbuf_stru  *pst_netbuf;

    pst_netbuf = sdt_drv_netbuf_delist();

    while (OAL_PTR_NULL != pst_netbuf)
    {
        sdt_drv_netlink_send(pst_netbuf, OAL_NETBUF_LEN(pst_netbuf));

        pst_netbuf = sdt_drv_netbuf_delist();
    }
    return;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_func_hook_init
 ��������  : sdt����ģ�鹳�Ӻ�����ʼ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void sdt_drv_func_hook_init(oal_void)
{
    g_st_sdt_drv_func_hook.p_sdt_report_data_func = sdt_drv_report_data2app;
    g_st_sdt_drv_func_hook.p_sdt_get_wq_len_func  = sdt_drv_get_wq_len;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_main_init
 ��������  : sdt_drv��ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��23��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  sdt_drv_main_init(oal_void)
{
    oal_int32   l_nl_return_val;

    OAL_MEMZERO((void *)&g_st_sdt_drv_mng_entry, OAL_SIZEOF(g_st_sdt_drv_mng_entry));

    g_st_sdt_drv_mng_entry.puc_data = oal_memalloc(DATA_BUF_LEN);
    if (OAL_PTR_NULL == g_st_sdt_drv_mng_entry.puc_data)
    {
        OAL_IO_PRINT("alloc g_st_sdt_drv_mng_entry.puc_data fail!\n");
        return -OAL_EFAIL;
    }

    OAL_MEMZERO(g_st_sdt_drv_mng_entry.puc_data, DATA_BUF_LEN);

    l_nl_return_val = sdt_drv_netlink_create();
    if (0 > l_nl_return_val)
    {
        OAL_IO_PRINT("sdt_drv_main_init::create netlink returns fail! l_nl_return_val--> \
                      %d\n", l_nl_return_val);
        return -l_nl_return_val;
    }

    g_st_sdt_drv_mng_entry.oam_rx_workqueue = oal_create_singlethread_workqueue("oam_rx_queue");
    OAL_INIT_WORK(&g_st_sdt_drv_mng_entry.rx_wifi_work, sdt_drv_push_wifi_log_work);
    oal_spin_lock_init(&g_st_sdt_drv_mng_entry.st_spin_lock);
    oal_netbuf_list_head_init(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    /* sdtģ�鹳�Ӻ�����ʼ�� */
    sdt_drv_func_hook_init();

    /* ��sdt���Ӻ���ע����oamģ�� */
    oam_sdt_func_fook_register(&g_st_sdt_drv_func_hook);

    /* sdt��������֮�������ʽ��ΪOAM_OUTPUT_TYPE_SDT */
    if (OAL_SUCC != oam_set_output_type(OAM_OUTPUT_TYPE_SDT))
    {
        OAL_IO_PRINT("oam set output type fail!");
        return -OAL_EFAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : sdt_drv_main_exit
 ��������  : sdt_drvж��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��23��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  sdt_drv_main_exit(oal_void)
{
   	oam_sdt_func_fook_unregister();

    if (OAL_PTR_NULL != g_st_sdt_drv_mng_entry.pst_nlsk)
    {
        oal_netlink_kernel_release(g_st_sdt_drv_mng_entry.pst_nlsk);
    }

    if (OAL_PTR_NULL != g_st_sdt_drv_mng_entry.puc_data)
    {
        oal_free(g_st_sdt_drv_mng_entry.puc_data);
    }

    oal_destroy_workqueue(g_st_sdt_drv_mng_entry.oam_rx_workqueue);
    oal_netbuf_queue_purge(&g_st_sdt_drv_mng_entry.rx_wifi_dbg_seq);

    return;
}

/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(sdt_drv_main_init);
oal_module_exit(sdt_drv_main_exit);
#endif

oal_module_symbol(sdt_drv_main_init);
oal_module_symbol(sdt_drv_main_exit);


oal_module_license("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

