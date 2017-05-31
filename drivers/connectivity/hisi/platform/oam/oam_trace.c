/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oam_trace.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��12��18��
  ����޸�   :
  ��������   : (1)���ڲ������̻��ߺ�������ʱ��Ľӿں�����Դ�ļ�
               (2)trace��ز�����Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��18��
    ��    ��   : huxiaotong
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
#include "oam_trace.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_TRACE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#ifdef _PRE_PROFILING_MODE
/*****************************************************************************
    2.1 profilingȫ�ֱ�������
*****************************************************************************/
/* ����tx profiling���Ե��������� */
oam_profiling_tx_statistic_stru g_oam_profiling_statistic_tx;

/* ����rx profiling���Ե��������� */
oam_profiling_rx_statistic_stru g_oam_profiling_statistic_rx;

/* ����tx profiling���Ե��������� */
oam_profiling_alg_statistic_stru g_oam_profiling_statistic_alg;

/* ����оƬstart time�������� */
oam_profiling_starttime_statistic_stru g_oam_profiling_statistic_starttime;

/* ����оƬ�ŵ��л��������� */
oam_profiling_chswitch_statistic_stru g_oam_profiling_statistic_chswitch;

/* ����profiling test��ȫ�ֿ��� */
oam_profiling_statistic_debug_stru g_oam_profiling_statistic_debug;


#endif

/*****************************************************************************
    2.2 traceȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#ifdef _PRE_PROFILING_MODE
/*****************************************************************************
 �� �� ��  : oam_profiling_switch_test_process
 ��������  : procָ����õ���ں���
 �������  : (1)��������
             (2)����ֵ
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_profiling_switch_test_process(oal_uint8  uc_config_type, oal_uint8 uc_config_value)
{
    switch (uc_config_type)
    {
        case OAM_PROFILING_SWITCH_DEBUG_CONFIG:
        {
            //oal_spin_lock(&g_oam_profiling_statistic_ping_data.st_spin_lock);

            if (OAM_PROFILING_STATISTIC_TX_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = OAL_FALSE;
            }

            if (OAM_PROFILING_STATISTIC_RX_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = OAL_FALSE;
            }
            if (OAM_PROFILING_STATISTIC_ALG_DEBUG & uc_config_value)
            {
                g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = OAL_TRUE;
            }
            else
            {
                g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = OAL_FALSE;
            }
        }

        break;

        default:

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_compute_time_offset
 ��������  : ��������ʱ��֮���ƫ�Ʋ�
 �������  : (1)ʱ��ֵһ
             (2)ʱ��ֵ��
 �������  : ����ʱ���ʱ���
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_compute_time_offset(
                oal_time_us_stru    st_time_first,
                oal_time_us_stru    st_time_second,
                oal_time_us_stru   *pst_time_offset)
{
    /* δ��Խ1sec */
    if (st_time_first.i_sec == st_time_second.i_sec)
    {
        pst_time_offset->i_sec     = 0;
        pst_time_offset->i_usec    = st_time_second.i_usec - st_time_first.i_usec;
    }
    /* ��Խ1sec */
    else
    {
        pst_time_offset->i_sec     = 0;
        pst_time_offset->i_usec    = 1000 * (st_time_second.i_sec - st_time_first.i_sec) - st_time_first.i_usec + st_time_second.i_usec;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_rx_init
 ��������  : ��ʼ���������̵�ȫ�ֲ��Ա���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_rx_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_RX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* ע�⣬netbuf�Ķ�Ӧ��SKB_ID����Ҫ��0��ʼ������ */
        g_oam_profiling_statistic_rx.aus_rx_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_rx.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_rx.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_rx.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_RX_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_rx.ast_rx_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_rx.aus_rx_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_rx_save_data
 ��������  : ����ʱ����skb id��ʱ���,��׼ʱ��,���������������浽skb_run_time_offset
 �������  : ��������
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oam_profiling_rx_save_data(oam_profiling_rx_func_enum_uint8 en_func_index)
{
    /* �����ж� */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable)
    {
        return;
    }*/

    if (0 == g_oam_profiling_statistic_rx.ast_rx_func_stand_time[g_oam_profiling_statistic_rx.uc_skb_id_idx][en_func_index])
    {
        g_oam_profiling_statistic_rx.ast_rx_func_stand_time[g_oam_profiling_statistic_rx.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }
}

/*****************************************************************************
 �� �� ��  : oam_profiling_rx_show_offset
 ��������  : ��ӡ���պ�������ʱ������д���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_rx_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_RX_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("RX time show:\n");

        /* ��ӡ������tid���е�ʱ�� */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_RX_COMP_IRQ_START; ul_func_idx <= OAM_PROFILING_FUNC_RX_DMAC_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_RX_COMP_IRQ_START)
            {
                ul_time_offset = g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_RX_COMP_IRQ_START] -  g_oam_profiling_statistic_rx.ast_rx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_RX_DMAC_END];
        OAL_IO_PRINT("\nRX total time is: %d (10ns)   \n\n", ul_time_offset);

    }

    /* ���� */
    oam_profiling_rx_init();

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_tx_init
 ��������  : ��ʼ���������̵�ȫ�ֲ��Ա���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_tx_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_TX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* ע�⣬netbuf�Ķ�Ӧ��SKB_ID����Ҫ��0��ʼ������ */
        g_oam_profiling_statistic_tx.aus_tx_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_tx.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_tx.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_tx.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_TX_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_tx.ast_tx_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_tx.aus_tx_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_tx_save_data
 ��������  : ����ʱ����skb id��ʱ���,��׼ʱ��,���������������浽skb_run_time_offset
 �������  : (1)ָ��Ҫ������netbuf
             (2)��������
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oam_profiling_tx_save_data(
                oal_void                    *pst_netbuf,
                oam_profiling_tx_func_enum_uint8    en_func_index)
{
    /* �����ж� */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable)
    {
        return;
    }*/

    /*ԭֵ����0�ż����� ����ȥ�����Ѿ���¼�õ�ֵ*/
    if (0 == g_oam_profiling_statistic_tx.ast_tx_func_stand_time[g_oam_profiling_statistic_tx.uc_skb_id_idx][en_func_index])
    {
       g_oam_profiling_statistic_tx.ast_tx_func_stand_time[g_oam_profiling_statistic_tx.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_tx_show_offset
 ��������  : ��ӡ���ͺ�������ʱ������д���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_tx_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_TX_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("TX time show:\n");
        /* ��ӡ������tid���е�ʱ�� */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_CONFIG_XMIT_START; ul_func_idx <= OAM_PROFILING_FUNC_CONFIG_XMIT_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_CONFIG_XMIT_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_CONFIG_XMIT_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_CONFIG_XMIT_END];
        OAL_IO_PRINT("\ntid enqueue total time is: %d (10ns)   \n\n", ul_time_offset);

        /* ��ӡampdu���Ȳ����Ͷ��е�ʱ�� */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_SCHEDULE_START; ul_func_idx <= OAM_PROFILING_FUNC_SCHEDULE_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_SCHEDULE_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }
        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_SCHEDULE_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_SCHEDULE_END];
        OAL_IO_PRINT("\nampdu schedule total time is: %d (10ns)     \n\n", ul_time_offset);


        /* ��ӡampdu��������ж��°벿����ʱ�� */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_FUNC_TX_COMP_IRQ_START; ul_func_idx <= OAM_PROFILING_FUNC_TX_COMP_DMAC_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_FUNC_TX_COMP_IRQ_START)
            {
                ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }
        }
        ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_TX_COMP_IRQ_START] -  g_oam_profiling_statistic_tx.ast_tx_func_stand_time[ul_packet_idx][OAM_PROFILING_FUNC_TX_COMP_DMAC_END];
        OAL_IO_PRINT("\nampdu tx complete total time is: %d (10ns)     \n\n", ul_time_offset);

    }

    ul_time_offset = g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_CONFIG_XMIT_START]
		             - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_CONFIG_XMIT_END]
                     + g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_SCHEDULE_START]
					 - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_SCHEDULE_END]
                     + g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_TX_COMP_IRQ_START]
					 - g_oam_profiling_statistic_tx.ast_tx_func_stand_time[0][OAM_PROFILING_FUNC_TX_COMP_DMAC_END];


    OAL_IO_PRINT("TX total time is: %d (10ns)     \n", ul_time_offset);

    /* ���� */
    oam_profiling_tx_init();

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : oam_profiling_alg_init
 ��������  : ��ʼ���������̵�ȫ�ֲ��Ա���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��29��
    ��    ��   : liwendong 291193
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_alg_init(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_func_idx;

    for(ul_packet_idx = 0; ul_packet_idx < OAM_PROFILING_ALG_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        /* ע�⣬netbuf�Ķ�Ӧ��SKB_ID����Ҫ��0��ʼ������ */
        g_oam_profiling_statistic_alg.aus_alg_skb_id_list[ul_packet_idx] = OAM_PROFILING_PACKET_INVALID_VALUE;
        g_oam_profiling_statistic_alg.uc_skb_id_idx      = 0;
        g_oam_profiling_statistic_alg.uc_idx_for_array   = 0;
        g_oam_profiling_statistic_alg.us_abnormal_index  = 0;

        for (ul_func_idx = 0; ul_func_idx < OAM_PROFILING_ALG_FUNC_BUTT; ul_func_idx++)
        {
            g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx]  = 0;
            g_oam_profiling_statistic_alg.ast_alg_func_time_offset[ul_packet_idx][ul_func_idx] = 0;
            g_oam_profiling_statistic_alg.aus_alg_pass_count[ul_packet_idx][ul_func_idx] = 0;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_alg_save_data
 ��������  : ����ʱ����skb id��ʱ���,��׼ʱ��,���������������浽skb_run_time_offset
 �������  : (1)ָ��Ҫ������netbuf
             (2)��������
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��29��
    ��    ��   : liwendong 291193
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oam_profiling_alg_save_data(oam_profiling_alg_func_enum_uint8    en_func_index)
{
    /* �����ж� */
    /*if (OAM_PROFILING_SWITCH_OFF == g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable)
    {
        return;
    }*/

    /*ԭֵ����0�ż����� ����ȥ�����Ѿ���¼�õ�ֵ*/
    if (0 == g_oam_profiling_statistic_alg.ast_alg_func_stand_time[g_oam_profiling_statistic_alg.uc_skb_id_idx][en_func_index])
    {
       g_oam_profiling_statistic_alg.ast_alg_func_stand_time[g_oam_profiling_statistic_alg.uc_skb_id_idx][en_func_index] = oal_5115timer_get_10ns();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_alg_show_offset
 ��������  : ��ӡ���ͺ�������ʱ������д���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���سɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��29��
    ��    ��   : liwendong 291193
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_alg_show_offset(oal_void)
{
    oal_uint32      ul_packet_idx;
    oal_uint32      ul_func_idx;
    oal_uint32      ul_time_offset = 0;

    for(ul_packet_idx = 0; ul_packet_idx < 1/*OAM_PROFILING_ALG_PACKET_MAX_COUNT*/; ul_packet_idx++)
    {
        OAL_IO_PRINT("ALG time show:\n");
        /* ��ӡXX��ʱ�� */
        OAL_IO_PRINT("      arrive_time      offset  ");
        for(ul_func_idx = OAM_PROFILING_ALG_START; ul_func_idx <= OAM_PROFILING_ALG_END; ul_func_idx++)
        {
            OAL_IO_PRINT("\nNo%3d ", ul_func_idx);
            OAL_IO_PRINT("%10u  ", g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx]);

            if (ul_func_idx != OAM_PROFILING_ALG_START)
            {
                ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx-1] -  g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][ul_func_idx];
                OAL_IO_PRINT("%10u ", ul_time_offset);
            }

        }

        ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][OAM_PROFILING_ALG_START] -  g_oam_profiling_statistic_alg.ast_alg_func_stand_time[ul_packet_idx][OAM_PROFILING_ALG_END];
        OAL_IO_PRINT("\nALG stage 1 total time is: %d (10ns)   \n\n", ul_time_offset);



    }

    ul_time_offset = g_oam_profiling_statistic_alg.ast_alg_func_stand_time[0][OAM_PROFILING_ALG_START]
		             - g_oam_profiling_statistic_alg.ast_alg_func_stand_time[0][OAM_PROFILING_ALG_END];



    OAL_IO_PRINT("ALG total time is: %d (10ns)     \n", ul_time_offset);

    /* ���� */
    oam_profiling_alg_init();

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_statistic_init
 ��������  : ��ʼ��оƬ����ʱ��ͳ��ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_statistic_init(oal_void)
{
    OAL_MEMZERO(&g_oam_profiling_statistic_starttime, OAL_SIZEOF(g_oam_profiling_statistic_starttime));

    OAL_MEMZERO(&g_oam_profiling_statistic_chswitch, OAL_SIZEOF(g_oam_profiling_statistic_chswitch));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_starttime_save_timestamp
 ��������  : оƬ�������̴�ʱ�������
 �������  : en_func_idx: ��ʱ�����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_profiling_starttime_save_timestamp(oam_profiling_starttime_func_enum_uint8 en_func_idx)
{
    g_oam_profiling_statistic_starttime.aul_timestamp[en_func_idx] = oal_5115timer_get_10ns();

    return;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_starttime_show_offset
 ��������  : ��ӡоƬ��ģ������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_profiling_starttime_show_offset(oal_void)
{
    oal_uint32 ul_idx;

    /* ��ӡ���м�¼��ʱ��� */
    OAL_IO_PRINT("Print all chip start timestamps: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_STARTTIME_FUNC_BUTT; ul_idx++)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx]);
    }

    OAL_IO_PRINT("Print chip start timestamp offset: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_STARTTIME_FUNC_BUTT; ul_idx += 2)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx] - g_oam_profiling_statistic_starttime.aul_timestamp[ul_idx + 1]);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : oam_profiling_chswitch_save_timestamp
 ��������  : оƬ�������̴�ʱ�������
 �������  : en_func_idx: ��ʱ�����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_profiling_chswitch_save_timestamp(oam_profiling_chswitch_func_enum_uint8 en_func_idx)
{
    g_oam_profiling_statistic_chswitch.aul_timestamp[en_func_idx] = oal_5115timer_get_10ns();

    return;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_chswitch_show_offset
 ��������  : ��ӡ�ŵ��л�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_profiling_chswitch_show_offset(oal_void)
{
    oal_uint32 ul_idx;

    /* ��ӡ���м�¼��ʱ��� */
    OAL_IO_PRINT("Print all chswitch timestamps: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_CHSWITCH_FUNC_BUTT; ul_idx++)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx]);
    }

    OAL_IO_PRINT("Print chswitch timestamp offset: \n");
    for (ul_idx = 0; ul_idx < OAM_PROFILING_CHSWITCH_FUNC_BUTT; ul_idx += 2)
    {
        OAL_IO_PRINT("%-16u \n", g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx] - g_oam_profiling_statistic_chswitch.aul_timestamp[ul_idx + 1]);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : oam_profiling_set_switch
 ��������  : ����profiling�Ŀ��ƿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��25��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_set_switch(oam_profiling_enum_uint8 en_profiling_type, oam_profiling_swith_enum_uint8 en_profiling_switch)
{

    if ((en_profiling_switch >= OAL_SWITCH_BUTT) || (en_profiling_type >= OAM_PROFILING_BUTT))
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    switch (en_profiling_type)
    {
        /* �������� */
        case OAM_PROFILING_RX:
            g_oam_profiling_statistic_debug.i_profiling_rx_debuging_enable = en_profiling_switch;

            break;

        /* �������� */
        case OAM_PROFILING_TX:
            g_oam_profiling_statistic_debug.i_profiling_tx_debuging_enable = en_profiling_switch;

            break;

        /* ALG���� */
        case OAM_PROFILING_ALG:
            g_oam_profiling_statistic_debug.i_profiling_alg_debuging_enable = en_profiling_switch;

            break;

        default:

            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_profiling_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��20��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_profiling_init(oal_void)
{
    /* ��ʼ����ʱ�� */
    oal_5115timer_init();

    /* ��ʼ����������profiling�ṹ */
    oam_profiling_rx_init();

    /* ��ʼ����������profiling�ṹ */
    oam_profiling_tx_init();

     /* ��ʼ����������profiling�ṹ */
    oam_profiling_alg_init();

    /* ��ʼ��оƬ����profiling�ṹ */
    oam_profiling_statistic_init();

    /* profiling��ʼ��:Ĭ�ϲ��� */
    oam_profiling_set_switch(OAM_PROFILING_RX, OAM_PROFILING_SWITCH_OFF);
    oam_profiling_set_switch(OAM_PROFILING_TX, OAM_PROFILING_SWITCH_OFF);
    oam_profiling_set_switch(OAM_PROFILING_ALG, OAM_PROFILING_SWITCH_OFF);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_PROFILING_MODE
oal_module_symbol(g_oam_profiling_statistic_tx);
oal_module_symbol(g_oam_profiling_statistic_rx);
oal_module_symbol(oam_profiling_set_switch);

oal_module_symbol(oam_profiling_rx_save_data);
oal_module_symbol(oam_profiling_rx_show_offset);
oal_module_symbol(oam_profiling_tx_save_data);
oal_module_symbol(oam_profiling_tx_show_offset);
oal_module_symbol(oam_profiling_alg_save_data);
oal_module_symbol(oam_profiling_alg_show_offset);


oal_module_symbol(oam_profiling_starttime_save_timestamp);
oal_module_symbol(oam_profiling_starttime_show_offset);

oal_module_symbol(oam_profiling_chswitch_save_timestamp);
oal_module_symbol(oam_profiling_chswitch_show_offset);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

