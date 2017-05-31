/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hal_common_ops.h
  �� �� ��   : ����
  ��    ��   : z00241943
  ��������   : 2014��10��23��
  ����޸�   :
  ��������   : hal������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��23��
    ��    ��   : z00241943
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __HAL_COMMOM_OPS_H__
#define __HAL_COMMOM_OPS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "wlan_spec.h"

/*****************************************************************************/
/*****************************************************************************/
/*                        HI1102 ��Ʒ�궨�塢ö��                            */
/*****************************************************************************/
/*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST)) || ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
#define HAL_PUBLIC_HOOK_FUNC(_func) \
         hi1102##_func
#endif
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))
#define HAL_PUBLIC_HOOK_FUNC(_func) \
         hi1103##_func
#endif


#define HAL_RX_DSCR_GET_SW_ADDR(_addr)     hal_rx_dscr_get_sw_addr(_addr)   /* һ���ֽ��а�����bit��Ŀ */
#define HAL_RX_DSCR_GET_REAL_ADDR(_addr)   hal_rx_dscr_get_real_addr(_addr)   /* һ���ֽ��а�����bit��Ŀ */

#define HAL_MAX_AP_NUM                     2      /* HAL AP���� */
#define HAL_MAX_STA_NUM                    3      /* HAL STA���� */
#define HAL_MAX_VAP_NUM                    (HAL_MAX_AP_NUM + HAL_MAX_STA_NUM)  /* HAL VAP???? */

#define HAL_VAP_ID_IS_VALID(_vap_id)      ((_vap_id == 0) || (_vap_id == 1) || (_vap_id == 4) || (_vap_id == 5) || (_vap_id == 6))
#define HAL_VAP_ID_IS_VALID_PSTA(_vap_id) ((uc_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_vap_id <= WLAN_PROXY_STA_END_ID)))

/*****************************************************************************
  3 ö��
*****************************************************************************/
typedef enum
{
    HAL_TX_QUEUE_BE        = 0,        /* ������Ϊҵ�� */
    HAL_TX_QUEUE_BK        = 1,        /* ����ҵ�� */
    HAL_TX_QUEUE_VI        = 2,        /* ��Ƶҵ�� */
    HAL_TX_QUEUE_VO        = 3,        /* ����ҵ�� */
    HAL_TX_QUEUE_HI        = 4,        /* �����ȼ�����(����֡/����֡�ô˶���) */
    HAL_TX_QUEUE_BUTT
}hal_tx_queue_type_enum;
typedef oal_uint8 hal_tx_queue_type_enum_uint8;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef enum
{
    BTCOEX_NOFRAME = 0,
    BTCOEX_SELFCTS = 1,
    BTCOEX_NULLDATA = 2,
    BTCOEX_QOSNULL = 3,
    BTCOEX_FRAME_NUTT
} coex_preempt_frame_enum;
typedef oal_uint8 coex_preempt_frame_enum_uint8;
#endif


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32*  hal_rx_dscr_get_real_addr(oal_uint32 *pul_rx_dscr)
{
    /* ע������2����hi1102_rx_buffer_addr_stru�ṹ���е�prevָ�룬�ƶ���nextָ��λ�� */
    if (OAL_PTR_NULL == pul_rx_dscr)
    {
        //OAL_IO_PRINT("[file = %s, line = %d], hal_rx_dscr_get_real_addr, dscr is NULL!\r\n",
        //             __FILE__, __LINE__);
        return pul_rx_dscr;
    }
    return pul_rx_dscr + 2;
}

OAL_STATIC OAL_INLINE oal_uint32*  hal_rx_dscr_get_sw_addr(oal_uint32 *pul_rx_dscr)
{
    /* ע������2����hi1102_rx_buffer_addr_stru�ṹ���е�prevָ�룬�ƶ���nextָ��λ�� */
    if (OAL_PTR_NULL == pul_rx_dscr)
    {
        OAL_IO_PRINT("[file = %s, line = %d], hal_rx_dscr_get_sw_addr, dscr is NULL!\r\n",
                     __FILE__, __LINE__);
        return pul_rx_dscr;
    }
    return pul_rx_dscr - 2;
}

#endif /* end of #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)*/

/*****************************************************************************/
/*****************************************************************************/
/*                        HI1151 ��Ʒ�궨�塢ö��                            */
/*****************************************************************************/
/*****************************************************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define HAL_PUBLIC_HOOK_FUNC(_func) \
         hi1151##_func

#define HAL_RX_DSCR_GET_SW_ADDR(_addr)    (_addr)
#define HAL_RX_DSCR_GET_REAL_ADDR(_addr)  (_addr)
#define HAL_TX_DSCR_GET_SW_ADDR(_addr)    (_addr)
#define HAL_TX_DSCR_GET_REAL_ADDR(_addr)  (_addr)

#define HAL_MAX_AP_NUM                     4       /* ֧�ֶ�BSSID���ԵĹ�����Ϊ4 AP*/
#define HAL_MAX_STA_NUM                    1      /* HAL STA���� */
#define HAL_MAX_VAP_NUM                    (HAL_MAX_AP_NUM + HAL_MAX_STA_NUM)  /* HAL VAP???? */
#define HAL_VAP_ID_IS_VALID(_vap_id)      ((_vap_id == 0) || (_vap_id == 1)|| (_vap_id == 2) || (_vap_id == 3) || (_vap_id == 4))
#define HAL_VAP_ID_IS_VALID_PSTA(_vap_id) ((uc_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_vap_id <= WLAN_PROXY_STA_END_ID)))

/*****************************************************************************
  3 ö��
*****************************************************************************/
typedef enum
{
    HAL_TX_QUEUE_BK        = 0,        /* ����ҵ�� */
    HAL_TX_QUEUE_BE        = 1,        /* ������Ϊҵ�� */
    HAL_TX_QUEUE_VI        = 2,        /* ��Ƶҵ�� */
    HAL_TX_QUEUE_VO        = 3,        /* ����ҵ�� */
    HAL_TX_QUEUE_HI        = 4,        /* �����ȼ�����(����֡/����֡�ô˶���) */
    HAL_TX_QUEUE_BUTT
}hal_tx_queue_type_enum;
typedef oal_uint8 hal_tx_queue_type_enum_uint8;

#endif  /* end of #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)*/

/*****************************************************************************/
/*****************************************************************************/
/*                        �����궨�塢ö�١��ṹ��                           */
/*****************************************************************************/
/*****************************************************************************/

/* ��ȡ��ǰ֡��ʹ�õ�Э��ģʽ */
#define HAL_GET_DATA_PROTOCOL_MODE(_val)      ((_val) >> 6)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* 2.4GHzƵ��: �ŵ��Ŷ�Ӧ���ŵ�����ֵ */
typedef enum
{
    HAL_2G_CHANNEL1  = 0,
    HAL_2G_CHANNEL2  = 1,
    HAL_2G_CHANNEL3  = 2,
    HAL_2G_CHANNEL4  = 3,
    HAL_2G_CHANNEL5  = 4,
    HAL_2G_CHANNEL6  = 5,
    HAL_2G_CHANNEL7  = 6,
    HAL_2G_CHANNEL8  = 7,
    HAL_2G_CHANNEL9  = 8,
    HAL_2G_CHANNEL10 = 9,
    HAL_2G_CHANNEL11 = 10,
    HAL_2G_CHANNEL12 = 11,
    HAL_2G_CHANNEL13 = 12,
    HAL_2G_CHANNEL14 = 13,

    HAL_CHANNEL_FREQ_2G_BUTT = 14
}hal_channel_freq_2g_enum;
typedef oal_uint8 hal_channel_freq_2g_enum_uint8;

typedef enum
{
    HAL_FCS_PROTECT_TYPE_NONE      = 0,    /* NONE        */
    HAL_FCS_PROTECT_TYPE_SELF_CTS,         /* SELF CTS    */
    HAL_FCS_PROTECT_TYPE_NULL_DATA,        /* NULL DATA   */

    HAL_FCS_PROTECT_TYPE_BUTT
}hal_fcs_protect_type_enum;
typedef oal_uint8 hal_fcs_protect_type_enum_uint8;

typedef enum
{
    HAL_FCS_PROTECT_CNT_1 = 1,    /* 1 */
    HAL_FCS_PROTECT_CNT_2 = 2,    /* 2 */
    HAL_FCS_PROTECT_CNT_3 = 3,    /* 3 */

    HAL_FCS_PROTECT_CNT_BUTT
}hal_fcs_protect_cnt_enum;
typedef oal_uint8 hal_fcs_protect_cnt_enum_uint8;

typedef enum
{
    HAL_OPER_MODE_NORMAL,
    HAL_OPER_MODE_HUT,

    HAL_OPER_MODE_BUTT
}hal_oper_mode_enum;
typedef oal_uint8 hal_oper_mode_enum_uint8;

/**** RF�����ã�����ָʾ����TX�������ֶ� ****/
typedef enum
{
    HAL_RF_TEST_DATA_RATE_ZERO,
    HAL_RF_TEST_BAND_WIDTH,
    HAL_RF_TEST_CHAN_CODE,
    HAL_RF_TEST_POWER,
    HAL_RF_TEST_BUTT
}hal_rf_test_sect_enum;
typedef oal_uint8 hal_rf_test_sect_enum_uint8;
/*****************************************************************************
  3.1 �������ö�ٶ���
*****************************************************************************/
#define HAL_AC_TO_Q_NUM(_ac) (       \
        ((_ac) == WLAN_WME_AC_VO) ? HAL_TX_QUEUE_VO : \
        ((_ac) == WLAN_WME_AC_VI) ? HAL_TX_QUEUE_VI : \
        ((_ac) == WLAN_WME_AC_BK) ? HAL_TX_QUEUE_BK : \
        ((_ac) == WLAN_WME_AC_BE) ? HAL_TX_QUEUE_BE : \
        ((_ac) == WLAN_WME_AC_MGMT) ? HAL_TX_QUEUE_HI : \
        HAL_TX_QUEUE_BK)

#define HAL_Q_NUM_TO_AC(_q) (       \
        ((_q) == HAL_TX_QUEUE_VO) ? WLAN_WME_AC_VO : \
        ((_q) == HAL_TX_QUEUE_VI) ? WLAN_WME_AC_VI : \
        ((_q) == HAL_TX_QUEUE_BK) ? WLAN_WME_AC_BK : \
        ((_q) == HAL_TX_QUEUE_BE) ? WLAN_WME_AC_BE : \
        ((_q) == HAL_TX_QUEUE_HI) ? WLAN_WME_AC_MGMT : \
        WLAN_WME_AC_BE)

#define HAL_TX_QUEUE_MGMT               HAL_TX_QUEUE_HI     /* 0~3����AC���Ͷ��У�4�������֡������֡���Ͷ��� */

/*****************************************************************************
  3.3 ���������ö�ٶ���
*****************************************************************************/
typedef enum
{
    HAL_TX_RATE_RANK_0 = 0,
    HAL_TX_RATE_RANK_1,
    HAL_TX_RATE_RANK_2,
    HAL_TX_RATE_RANK_3,

    HAL_TX_RATE_RANK_BUTT
}hal_tx_rate_rank_enum;
typedef oal_uint8 hal_tx_rate_rank_enum_uint8;
typedef enum
{
    HAL_DFS_RADAR_TYPE_NULL  = 0,
    HAL_DFS_RADAR_TYPE_FCC   = 1,
    HAL_DFS_RADAR_TYPE_ETSI  = 2,
    HAL_DFS_RADAR_TYPE_MKK   = 3,
    HAL_DFS_RADAR_TYPE_KOREA = 4,

    HAL_DFS_RADAR_TYPE_BUTT
}hal_dfs_radar_type_enum;
typedef oal_uint8 hal_dfs_radar_type_enum_uint8;

typedef enum
{
    HAL_RX_NEW                    = 0x0,
    HAL_RX_SUCCESS                = 0x1,
    HAL_RX_DUP_DETECTED           = 0x2,
    HAL_RX_FCS_ERROR              = 0x3,
    HAL_RX_KEY_SEARCH_FAILURE     = 0x4,
    HAL_RX_CCMP_MIC_FAILURE       = 0x5,
    HAL_RX_ICV_FAILURE            = 0x6,
    HAL_RX_TKIP_REPLAY_FAILURE    = 0x7,
    HAL_RX_CCMP_REPLAY_FAILURE    = 0x8,
    HAL_RX_TKIP_MIC_FAILURE       = 0x9,
    HAL_RX_BIP_MIC_FAILURE        = 0xA,
    HAL_RX_BIP_REPLAY_FAILURE     = 0xB,
    HAL_RX_MUTI_KEY_SEARCH_FAILURE= 0xC     /*�鲥�㲥*/
} hal_rx_status_enum;
typedef oal_uint8 hal_rx_status_enum_uint8;

/* ��������������״̬ */
typedef enum
{
    HAL_DSCR_QUEUE_INVALID  = 0,
    HAL_DSCR_QUEUE_VALID,
    HAL_DSCR_QUEUE_SUSPENDED,

    HAL_DSCR_QUEUE_STATUS_BUTT
}hal_dscr_queue_status_enum;
typedef oal_uint8 hal_dscr_queue_status_enum_uint8;

/* �������������к� */
typedef enum
{
    HAL_RX_DSCR_NORMAL_PRI_QUEUE = 0,
    HAL_RX_DSCR_HIGH_PRI_QUEUE,
    HAL_RX_DSCR_SMALL_QUEUE,

    HAL_RX_DSCR_QUEUE_ID_BUTT
}hal_rx_dscr_queue_id_enum;
typedef oal_uint8 hal_rx_dscr_queue_id_enum_uint8;

/* TX ������ 12�� b23:b22 phy����ģʽ */
typedef enum
{
    WLAN_11B_PHY_PROTOCOL_MODE              = 0,   /* 11b CCK */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE      = 1,   /* 11g/a OFDM */
    WLAN_HT_PHY_PROTOCOL_MODE               = 2,   /* 11n HT */
    WLAN_VHT_PHY_PROTOCOL_MODE              = 3,   /* 11ac VHT */

    WLAN_PHY_PROTOCOL_BUTT
}wlan_phy_protocol_enum;
typedef oal_uint8 wlan_phy_protocol_enum_uint8;

/* HALģ����Ҫ�׳���WLAN_DRX�¼������͵Ķ���
 ˵��:��ö����Ҫ��dmac_wlan_drx_event_sub_type_enum_uint8ö��һһ��Ӧ */
typedef enum
{
    HAL_WLAN_DRX_EVENT_SUB_TYPE_RX,     /* WLAN DRX ���� */

    HAL_WLAN_DRX_EVENT_SUB_TYPE_BUTT
}hal_wlan_drx_event_sub_type_enum;
typedef oal_uint8 hal_wlan_drx_event_sub_type_enum_uint8;

/* HALģ����Ҫ�׳���WLAN_CRX�¼������͵Ķ���
   ˵��:��ö����Ҫ��dmac_wlan_crx_event_sub_type_enum_uint8ö��һһ��Ӧ */
typedef enum
{
    HAL_WLAN_CRX_EVENT_SUB_TYPE_RX,    /* WLAN CRX ���� */

    HAL_WLAN_CRX_EVENT_SUB_TYPE_BUTT
}hal_wlan_crx_event_sub_type_enum;
typedef oal_uint8 hal_wlan_crx_event_sub_type_enum_uint8;

typedef enum
{
    HAL_TX_COMP_SUB_TYPE_TX,

    HAL_TX_COMP_SUB_TYPE_BUTT
}hal_tx_comp_sub_type_enum;
typedef oal_uint8 hal_tx_comp_sub_type_enum_uint8;

typedef enum
{
    HAL_EVENT_TBTT_SUB_TYPE,

    HAL_EVENT_TBTT_SUB_TYPE_BUTT
}hal_event_tbtt_sub_type_enum;
typedef oal_uint8 hal_event_tbtt_sub_type_enum_uint8;


/*****************************************************************************
  3.4 �ж����ö�ٶ���
*****************************************************************************/
/****3.4.1  оƬ�����ж����� ************************************************/
typedef enum
{
    HAL_EVENT_ERROR_IRQ_MAC_ERROR,      /* MAC�����ж�ʱ��*/
    HAL_EVENT_ERROR_IRQ_SOC_ERROR,      /* SOC�����ж��¼�*/

    HAL_EVENT_ERROR_IRQ_SUB_TYPE_BUTT
}hal_event_error_irq_sub_type_enum;
typedef oal_uint8 hal_event_error_irq_sub_type_enum_uint8;

/****3.4.2  MAC�����ж����� (ö��ֵ������ж�״̬�Ĵ�����λһһ��Ӧ!)********/
typedef enum
{
    HAL_MAC_ERROR_PARA_CFG_ERR                  = 0,        /*���������������쳣,����AMPDU�������ò�ƥ��,AMPDU��MPDU���ȳ���,sub msdu num����*/
    HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL          = 1,        /*���շ�AMSDU֡������RxBuff��С�쳣*/
    HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND            = 2,        /*δ�ҵ�BA�Ự�����쳣0*/
    HAL_MAC_ERROR_PHY_TRLR_TIME_OUT             = 3,        /*PHY_RX_TRAILER��ʱ*/
    HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN           = 4,        /*PHY_RX_FIFO��д�쳣*/
    HAL_MAC_ERROR_TX_DATAFLOW_BREAK             = 5,        /*����֡���ݶ���*/
    HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT             = 6,        /*RX_FSM״̬����ʱ*/
    HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT             = 7,        /*TX_FSM״̬����ʱ*/
    HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT         = 8,        /*RX_HANDLER״̬����ʱ*/
    HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT         = 9,        /*TX_HANDLER״̬����ʱ*/
    HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN          = 10,       /*TX �ж�FIFO��д*/
    HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN          = 11,       /*RX�ж� FIFO��д*/
    HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN        = 12,       /*HIRX�ж�FIFO��д*/
    HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY         = 13,       /*���յ���ͨ���ȼ�֡����ʱRX BUFFERָ��Ϊ��*/
    HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY       = 14,       /*���յ������ȼ�֡����ʱHI RX BUFFERָ��Ϊ��*/
    HAL_MAC_ERROR_BUS_RLEN_ERR                  = 15,       /*���߶����󳤶�Ϊ0�쳣*/
    HAL_MAC_ERROR_BUS_RADDR_ERR                 = 16,       /*���߶������ַ��Ч�쳣*/
    HAL_MAC_ERROR_BUS_WLEN_ERR                  = 17,       /*����д���󳤶�Ϊ0�쳣*/
    HAL_MAC_ERROR_BUS_WADDR_ERR                 = 18,       /*����д�����ַ��Ч�쳣*/
    HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN             = 19,       /*tx acbk����fifo��д*/
    HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN             = 20,       /*tx acbe����fifo��д*/
    HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN             = 21,       /*tx acvi����fifo��д*/
    HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN             = 22,       /*tx acv0����fifo��д*/
    HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN            = 23,       /*tx hipri����fifo��д*/
    HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT           = 24,       /*matrix���㳬ʱ*/
    HAL_MAC_ERROR_CCA_TIME_OUT                  = 25,       /*cca��ʱ*/
    HAL_MAC_ERROR_DCOL_DATA_OVERLAP             = 26,       /*����overlap�澯*/
    HAL_MAC_ERROR_BEACON_MISS                   = 27,       /*��������beaconʧ��*/
    HAL_MAC_ERROR_INTR_FIFO_UNEXPECTED_READ     = 28,       /*interrupt fifo�ն��쳣*/
    HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR       = 29,       /*rx desc��ַ�����쳣*/
    HAL_MAC_ERROR_RX_OVERLAP_ERR                = 30,       /*macû�д�����ǰһ֡,phy���ϱ���һ֡�쳣*/
    HAL_MAC_ERROR_RESERVED_31                   = 31,
    HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT       = 32,       /*����BE�����˱ܳ�ʱ*/
    HAL_MAC_ERROR_TX_ACBK_BACKOFF_TIMEOUT       = 33,       /*����BK�����˱ܳ�ʱ*/
    HAL_MAC_ERROR_TX_ACVI_BACKOFF_TIMEOUT       = 34,       /*����VI�����˱ܳ�ʱ*/
    HAL_MAC_ERROR_TX_ACVO_BACKOFF_TIMEOUT       = 35,       /*����VO�����˱ܳ�ʱ*/
    HAL_MAC_ERROR_TX_HIPRI_BACKOFF_TIMEOUT      = 36,       /*���͸����ȼ������˱ܳ�ʱ*/
    HAL_MAC_ERROR_RX_SMALL_Q_EMPTY              = 37,       /*������ͨ���е�С��������С������ָ��Ϊ��*/
    HAL_MAC_ERROR_PARA_CFG_2ERR                 = 38,       /*������������AMPDU��MPDU���ȹ���*/
    HAL_MAC_ERROR_PARA_CFG_3ERR                 = 39,       /*������������11a��11b��11g����ʱ��mpdu���ó��ȳ���4095*/
    HAL_MAC_ERROR_EDCA_ST_TIMEOUT               = 40,       /*CH_ACC_EDCA_CTRL״̬����ʱ*/

    HAL_MAC_ERROR_TYPE_BUTT
}hal_mac_error_type_enum;
typedef oal_uint8 hal_mac_error_type_enum_uint8;

/****3.4.3 SOC�����ж����� (��Ҫ��DMACģ����д����error irq�����Ͷ���)*****/
typedef enum
{
    /* SOC�����ж� */
    HAL_SOC_ERROR_BUCK_OCP,                                                 /* PMU BUCK�����ж� */
    HAL_SOC_ERROR_BUCK_SCP,                                                 /* PMU BUCK��·�ж� */
    HAL_SOC_ERROR_OCP_RFLDO1,                                               /* PMU RFLDO1�����ж� */
    HAL_SOC_ERROR_OCP_RFLDO2,                                               /* PMU RFLDO2�����ж� */
    HAL_SOC_ERROR_OCP_CLDO,                                                 /* PMU CLDO�����ж� */
    HAL_SOC_ERROR_RF_OVER_TEMP,                                             /* RF�����ж� */
    HAL_SOC_ERROR_CMU_UNLOCK,                                               /* CMU PLLʧ���ж� */
    HAL_SOC_ERROR_PCIE_SLV_ERR,                                             /* PCIE���ߴ����ж� */

    HAL_SOC_ERROR_TYPE_BUTT
}hal_soc_error_type_enum;
typedef oal_uint8 hal_soc_error_type_enum_uint8;


/* DMAC MISC ���¼�ö�ٶ��� */
typedef enum
{
    HAL_EVENT_DMAC_MISC_CH_STATICS_COMP,    /* �ŵ�ͳ��/��������ж� */
    HAL_EVENT_DMAC_MISC_RADAR_DETECTED,     /* ��⵽�״��ź� */
    HAL_EVENT_DMAC_MISC_DFS_AUTH_CAC,       /* DFS��֤CAC���� */
    HAL_EVENT_DMAC_MISC_DBAC,               /* DBAC */
    HAL_EVENT_DMAC_MISC_MWO_DET,            /* ΢��¯ʶ���ж� */
#ifdef _PRE_WLAN_DFT_REG
    HAL_EVENT_DMAC_REG_REPORT,
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    HAL_EVENT_DMAC_BT_A2DP,
    HAL_EVENT_DMAC_BT_SCO,
    HAL_EVENT_DMAC_BT_TRANSFER,
    HAL_EVENT_DMAC_BT_PAGE_SCAN,
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
    HAL_EVENT_DMAC_P2P_NOA_ABSENT_START,
    HAL_EVENT_DMAC_P2P_NOA_ABSENT_END,
    HAL_EVENT_DMAC_P2P_CTWINDOW_END,
#endif
    HAL_EVENT_DMAC_BEACON_TIMEOUT,          /* �ȴ�beacon֡��ʱ */
    HAL_EVENT_DMAC_CALI_TO_HMAC,            /* У׼���ݴ�dmac�׵�hmac */
    HAL_EVENT_DMAC_MISC_WOW_WAKE,

    HAL_EVENT_DMAC_MISC_GREEN_AP,           /* Green ap timer*/
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    HAL_EVENT_DMAC_DUAL_ANTENNA_SWITCH,
#endif
    HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT
}hal_dmac_misc_sub_type_enum;
typedef oal_uint8  hal_dmac_misc_sub_type_enum_uint8;

/*****************************************************************************
  3.5 ��λ���ö�ٶ���
*****************************************************************************/
/****3.5.1  ��λ�¼������Ͷ��� **********************************************/
typedef enum
{
    HAL_RESET_HW_TYPE_ALL = 0,
    HAL_RESET_HW_TYPE_PHY,
    HAL_RESET_HW_TYPE_MAC,
    HAL_RESET_HW_TYPE_RF,
    HAL_RESET_HW_TYPE_MAC_PHY,
    HAL_RESET_HW_TYPE_TCM,
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    HAL_RESET_HW_TYPE_MAC_TSF,
    HAL_RESET_HW_TYPE_MAC_CRIPTO,
    HAL_RESET_HW_TYPE_MAC_NON_CRIPTO,
    HAL_RESET_HW_TYPE_PHY_RADAR,
#endif
    HAL_RESET_HW_NORMAL_TYPE_PHY,
    HAL_RESET_HW_NORMAL_TYPE_MAC,
    HAL_RESET_HW_TYPE_DUMP_MAC,
    HAL_RESET_HW_TYPE_DUMP_PHY,

    HAL_RESET_HW_TYPE_BUTT
}hal_reset_hw_type_enum;
typedef oal_uint8 hal_reset_hw_type_enum_uint8;

/****3.5.1  ��λMAC��ģ�鶨�� **********************************************/
typedef enum
{
    HAL_RESET_MAC_ALL = 0,
    HAL_RESET_MAC_PA ,
    HAL_RESET_MAC_CE,
    HAL_RESET_MAC_TSF,
    HAL_RESET_MAC_DUP,
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    HAL_RESET_MAC_LOGIC,
#endif
    HAL_RESET_MAC_BUTT
}hal_reset_mac_submod_enum;
typedef oal_uint8 hal_reset_mac_submod_enum_uint8;

typedef enum
{
   HAL_LPM_SOC_BUS_GATING       = 0,
   HAL_LPM_SOC_PCIE_RD_BYPASS   = 1,
   HAL_LPM_SOC_MEM_PRECHARGE    = 2,
   HAL_LPM_SOC_PCIE_L0          = 3,
   HAL_LPM_SOC_PCIE_L1_PM       = 4,
   HAL_LPM_SOC_AUTOCG_ALL       = 5,
   HAL_LPM_SOC_ADC_FREQ         = 6,

   HAL_LPM_SOC_SET_BUTT
}hal_lpm_soc_set_enum;
typedef oal_uint8   hal_lpm_soc_set_enum_uint8;

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
typedef enum
{
    HAL_SMPS_MODE_DISABLE = 0,
    HAL_SMPS_MODE_STATIC ,
    HAL_SMPS_MODE_DYNAMIC,

    HAL_SMPS_MODE_BUTT
}hal_smps_mode_enum;
typedef oal_uint8 hal_smps_mode_enum_uint8;

#endif
typedef enum
{
    HAL_ALG_ISR_NOTIFY_DBAC,
    HAL_ALG_ISR_NOTIFY_MWO_DET,
    HAL_ALG_ISR_NOTIFY_ANTI_INTF,

    HAL_ALG_ISR_NOTIFY_BUTT,
}hal_alg_noify_enum;
typedef oal_uint8 hal_alg_noify_enum_uint8;

typedef enum
{
    HAL_ISR_TYPE_TBTT,
    HAL_ISR_TYPE_ONE_PKT,
    HAL_ISR_TYPE_MWO_DET,
    HAL_ISR_TYPE_NOA_START,
    HAL_ISR_TYPE_NOA_END,

    HAL_ISR_TYPE_BUTT,
}hal_isr_type_enum;
typedef oal_uint8 hal_isr_type_enum_uint8;



/*���ܲ������*/
typedef enum {
    HAL_ALWAYS_TX_DISABLE,         /* ���ó��� */
    HAL_ALWAYS_TX_RF,              /* ������RF���Թ㲥����*/
    HAL_ALWAYS_TX_AMPDU_ENABLE,    /* ʹ��AMPDU�ۺϰ����� */
    HAL_ALWAYS_TX_MPDU,            /* ʹ�ܷǾۺϰ����� */
    HAL_ALWAYS_TX_BUTT
}hal_device_always_tx_state_enum;
typedef oal_uint8 hal_device_always_tx_enum_uint8;


typedef enum {
    HAL_ALWAYS_RX_DISABLE,         /* ���ó��� */
    HAL_ALWAYS_RX_RESERVED,        /* ������RF���Թ㲥����*/
    HAL_ALWAYS_RX_AMPDU_ENABLE,    /* ʹ��AMPDU�ۺϰ����� */
    HAL_ALWAYS_RX_ENABLE,          /* ʹ�ܷǾۺϰ����� */
    HAL_ALWAYS_RX_BUTT
}hal_device_always_rx_state_enum;
typedef oal_uint8 hal_device_always_rx_enum_uint8;

typedef enum
{
    WLAN_PHY_RATE_1M                = 0,    /* 0000 */
    WLAN_PHY_RATE_2M                = 1,    /* 0001 */
    WLAN_PHY_RATE_5HALF_M           = 2,    /* 0010 */
    WLAN_PHY_RATE_11M               = 3,    /* 0011 */

    WLAN_PHY_RATE_48M               = 8,    /* 1000 */
    WLAN_PHY_RATE_24M               = 9,    /* 1001 */
    WLAN_PHY_RATE_12M               = 10,   /* 1010 */
    WLAN_PHY_RATE_6M                = 11,   /* 1011 */

    WLAN_PHY_RATE_54M               = 12,   /* 1100 */
    WLAN_PHY_RATE_36M               = 13,   /* 1101 */
    WLAN_PHY_RATE_18M               = 14,   /* 1110 */
    WLAN_PHY_RATE_9M                = 15,   /* 1111 */

    WLAN_PHY_RATE_BUTT
}wlan_phy_rate_enum;

#ifdef _PRE_WLAN_FEATURE_DFS
typedef enum
{
    HAL_RADAR_NOT_REPORT = 0,
    HAL_RADAR_REPORT,
}hal_radar_filter_enum;
typedef oal_uint8 hal_radar_filter_enum_uint8;
#endif
/*****************************************************************************
  3.6 �������ö�ٶ���
*****************************************************************************/
/****3.6.1  оƬ��Կ���Ͷ��� ************************************************/

typedef enum
{
    HAL_KEY_TYPE_TX_GTK              = 0,       /*Hi1102:HAL_KEY_TYPE_TX_IGTK */
    HAL_KEY_TYPE_PTK                 = 1,
    HAL_KEY_TYPE_RX_GTK              = 2,
    HAL_KEY_TYPE_RX_GTK2             = 3,       /* 02ʹ�� */
    HAL_KEY_TYPE_BUTT
} hal_cipher_key_type_enum;
typedef oal_uint8 hal_cipher_key_type_enum_uint8;

/****3.6.2  оƬ�����㷨���Ͷ�ӦоƬ�е�ֵ **********************************/
typedef enum
{
    HAL_WEP40                      = 0,
    HAL_TKIP                       = 1,
    HAL_CCMP                       = 2,
    HAL_NO_ENCRYP                  = 3,
    HAL_WEP104                     = 4,
    HAL_BIP                        = 5,
    HAL_CIPER_PROTOCOL_TYPE_BUTT
} hal_cipher_protocol_type_enum;
typedef oal_uint8 hal_cipher_protocol_type_enum_uint8;

/****3.6.3  оƬ��д���ܼĴ���CE_LUT_CONFIG AP/STA **************************/
typedef enum
{
    HAL_AUTH_KEY = 0,      /* �������豸Ϊ��֤�� */
    HAL_SUPP_KEY = 1,      /* �������豸Ϊ������ */

    HAL_KEY_ORIGIN_BUTT,
} hal_key_origin_enum;
typedef oal_uint8 hal_key_origin_enum_uint8;

#ifdef _PRE_WLAN_FEATURE_SMARTANT
typedef enum
{
    HAL_DUAL_ANTENNA_FEATURE_CHANGE = 0,
    HAL_DUAL_ANTENNA_TEMP_INTERRUPT = 1,
    HAL_DUAL_ANTENNA_BUTT,
} hal_dual_antenna_switch_type_enum;
typedef oal_uint8 hal_dual_antenna_switch_type_enum_uint8;
#endif
/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    hal_fcs_protect_type_enum_uint8     en_protect_type;
    hal_fcs_protect_cnt_enum_uint8      en_protect_cnt;
    oal_uint8                           auc_resv[2];
    oal_uint32                          ul_tx_mode;
    oal_uint32                          ul_tx_data_rate;
    oal_uint16                          us_duration;    /* ��λ us */
    oal_uint16                          us_timeout;
    oal_uint8                           auc_protect_frame[HAL_FCS_PROT_MAX_FRAME_LEN];
}hal_one_packet_cfg_stru;

typedef struct
{
    oal_bool_enum_uint8     en_mac_in_one_pkt_mode  : 1;
    oal_bool_enum_uint8     en_self_cts_success     : 1;
    oal_bool_enum_uint8     en_null_data_success    : 1;
    oal_uint32              ul_resv                 : 5;
}hal_one_packet_status_stru;

typedef struct
{
    oal_uint8     uc_pn_tid;          /* tid,0~7, ��rx pn lut��Ч */
    oal_uint8     uc_pn_peer_idx;     /* �Զ�peer����,0~31 */
    oal_uint8     uc_pn_key_type;     /* 1151 0:multicast,1:unicast */
                                      /* 1102 tx pn: 0x0��GTK(multicast) 0x1��PTK(unicast) 0x2��IGTK others��reserved*/
                                      /* 1102 rx pn: 0x0���鲥/�㲥����֡ 0x1������qos����֡ 0x2��������qos����֡
                                         0x3����������֡  0x4���鲥/�㲥����֡ others������ */
    oal_uint8     uc_all_tid;         /* 0:������TID,1:����TID ��rx pn lut��Ч*/
    oal_uint32    ul_pn_msb;          /* pnֵ�ĸ�32λ,д����ʱ����Σ�������ʱ������ֵ */
    oal_uint32    ul_pn_lsb;          /* pnֵ�ĵ�32λ��д����ʱ����Σ�������ʱ������ֵ */
}hal_pn_lut_cfg_stru;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct {
    oal_uint16  bit_bt_on            : 1,
               bit_bt_cali          : 1,
               bit_bt_ps            : 1,
               bit_bt_inquiry       : 1,
               bit_bt_page          : 1,
               bit_bt_acl           : 1,
               bit_bt_a2dp          : 1,
               bit_bt_sco           : 1,
               bit_bt_data_trans    : 1,
               bit_bt_acl_num       : 3,
               bit_bt_link_role     : 4;
} bt_status_stru;

typedef union {
    oal_uint16 us_bt_status_reg;
    bt_status_stru st_bt_status;
} btcoex_bt_status_union;

typedef struct {
    oal_uint16  bit_ble_on           : 1,
               bit_ble_scan         : 1,
               bit_ble_con          : 1,
               bit_ble_adv          : 1,
               bit_bt_transfer      : 1,
               bit_bt_6slot         : 2,
               bit_resv             : 8,
               bit_bt_ba            : 1;
} ble_status_stru;

typedef union {
    oal_uint16 us_ble_status_reg;
    ble_status_stru st_ble_status;
} btcoex_ble_status_union;

typedef struct hal_btcoex_btble_status {
    btcoex_bt_status_union un_bt_status;
    btcoex_ble_status_union un_ble_status;
} hal_btcoex_btble_status_stru;

typedef struct
{
    oal_uint32 ul_abort_start_cnt;
    oal_uint32 ul_abort_done_cnt;
    oal_uint32 ul_abort_end_cnt;
    oal_uint32 ul_preempt_cnt;
    oal_uint32 ul_post_preempt_cnt;
    oal_uint32 ul_post_premmpt_fail_cnt;
    oal_uint32 ul_abort_duration_on;
    oal_uint32 ul_abort_duration_start_us;
    oal_uint32 ul_abort_duration_us;
    oal_uint32 ul_abort_duration_s;
} hal_btcoex_statistics_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_SMARTANT
typedef struct
{
    oal_uint8 bit_lte_rx_act  : 1,
             bit_bt_on       : 1,
             bit_roam        : 1,
             bit_vap_mode    : 1,
             bit_ps_sleep    : 1,
             bit_ps_wake     : 1,
             bit_resv        : 2;
} hal_dual_antenna_check_status_stru;
#endif
typedef struct hal_wifi_channel_status {
    oal_uint8 uc_chan_number;     /* ��20MHz�ŵ��� */
    oal_uint8 uc_band;            /* Ƶ�� */
    oal_uint8 uc_bandwidth;       /* ����ģʽ */
    oal_uint8 uc_idx;             /* �ŵ������� */
} hal_wifi_channel_status_stru;

/*****************************************************************************
  7.0 �Ĵ������ýṹ
*****************************************************************************/
/*lint -e958*/
#if (_PRE_WLAN_CHIP_VERSION == _PRE_WLAN_CHIP_FPGA_HI1101RF)
struct witp_reg_cfg
{
    oal_uint16    us_soft_index;
    oal_uint8     uc_addr;
    oal_uint32    ul_val;
}__OAL_DECLARE_PACKED;
#elif(_PRE_WLAN_CHIP_VERSION == _PRE_WLAN_CHIP_FPGA_HI1151RF) /* End of _PRE_WLAN_CHIP_FPGA_HI1101RF*/
struct witp_reg16_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
typedef struct witp_reg16_cfg witp_reg16_cfg_stru;

struct witp_reg_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
#elif(_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)    /* End of _PRE_WLAN_CHIP_FPGA_HI1151RF*/
struct witp_reg16_cfg
{
    oal_uint16    us_addr;
    oal_uint16    us_val;
}__OAL_DECLARE_PACKED;
typedef struct witp_reg16_cfg witp_reg16_cfg_stru;

struct witp_reg_cfg
{
    oal_uint16   us_addr;
    oal_uint16   us_val;
}__OAL_DECLARE_PACKED;
#endif /* End of _PRE_WLAN_CHIP_ASIC */

typedef struct witp_reg_cfg witp_reg_cfg_stru;

struct witp_single_tune_reg_cfg
{
    oal_uint16    us_addr;
    oal_int32     ul_val;
}__OAL_DECLARE_PACKED;

typedef struct witp_single_tune_reg_cfg witp_single_tune_reg_cfg_stru;

/*lint +e958*/
/*****************************************************************************
  7.1 ��׼��������������
*****************************************************************************/
typedef struct tag_hal_tx_dscr_stru
{
    oal_dlist_head_stru                 st_entry;
    oal_netbuf_stru                    *pst_skb_start_addr;         /* Sub MSDU 0 Skb Address */
    oal_uint16                          us_original_mpdu_len;       /* mpdu���� ��֡ͷ */
    hal_tx_queue_type_enum_uint8        uc_q_num;                   /* ���Ͷ��ж��к� */
    oal_uint8                           bit_is_retried          :1; /* �ǲ����ش��� */
    oal_uint8                           bit_is_ampdu            :1; /* �ǲ���ampdu */
    oal_uint8                           bit_is_rifs             :1; /* �ǲ���rifs���� */
    oal_uint8                           bit_is_first            :1; /* ��־�Ƿ��ǵ�һ�������� */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_uint8                           bit_tx_hal_vap_id       :4; /* Proxy STA��tx hal_vap_id */
#else
    oal_uint8                           bit_resv                 : 4;
#endif
    oal_uint8                           data[4];
}hal_tx_dscr_stru;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define HAL_PSTA_ORI2ID(ori_id) ((ori_id) ? (ori_id) - HAL_PROXY_STA_START_IDX + 1 : 0)
#define HAL_PSTA_ID2ORI(id) ((id) + HAL_PROXY_STA_START_IDX - 1)
#endif
/*****************************************************************************
  7.2 ��׼��������������
*****************************************************************************/
typedef struct tag_hal_rx_dscr_stru
{
    oal_uint32                 *pul_prev_rx_dscr;           /* ǰһ���������ĵ�ַ           */
    oal_uint32                  ul_skb_start_addr;          /* �������б����netbuf���׵�ַ */
    oal_uint32                 *pul_next_rx_dscr;           /* ǰһ���������ĵ�ַ(�����ַ) */
}hal_rx_dscr_stru;

/*****************************************************************************
  7.3 ���ⲿ�����ṩ�ӿ��������ݽṹ
*****************************************************************************/

/*****************************************************************************
  �ṹ��  : hal_channel_matrix_dsc_stru
  �ṹ˵��: ������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    /*(��10 23��) */
    oal_uint8                            bit_codebook              : 2;
    oal_uint8                            bit_grouping              : 2;
    oal_uint8                            bit_row_num               : 4;

    oal_uint8                            bit_column_num            : 4;
    oal_uint8                            bit_response_flag         : 1;     /* ��Tx �������в�����д���ֶ�;��������жϺ󣬽������ŵ�������Ϣ�洢�ڴ� */
    oal_uint8                            bit_reserve1              : 3;

    oal_uint16                           us_channel_matrix_length;          /*�ŵ���������ֽ�(Byte)�� */
    oal_uint32                           ul_steering_matrix;                /* txbf��Ҫʹ�õľ����ַ,��д����������ʱ��ʹ�� */
}hal_channel_matrix_dsc_stru;

typedef struct
{
    /* PHY TX MODE 1(��13��) */
    /* (1) ��������Ӧ��д */
    oal_uint8                               uc_extend_spatial_streams;      /* ��չ�ռ������� */
    wlan_channel_code_enum_uint8            en_channel_code;                /* �ŵ�����(BCC��LDPC) */

    /* (2) ACS��д */
    hal_channel_assemble_enum_uint8         uc_channel_bandwidth;           /* �������� */

    oal_uint8                               bit_lsig_txop       : 1;        /* L-SIG TXOP���� 0:������������1: ��������*/
    oal_uint8                               bit_reserved        : 7;

    oal_uint8                               dyn_bandwidth_in_non_ht;        /* ����Ǳ��豸���߶Զ��豸����VHT�豸�����߼Ĵ������õ�����Ϊnon-HT���ʣ���ô���ֶ������壨����0)*/
    oal_uint8                               dyn_bandwidth_in_non_ht_exist;  /* ������豸�ͶԶ��豸��ΪVHT�豸�����ҼĴ������õ�����Ϊnon-HT���ʣ���ô���ֶ���1 */
    oal_uint8                               ch_bandwidth_in_non_ht_exist;   /* ������豸�ͶԶ��豸��ΪVHT�豸�����ҼĴ������õ�����Ϊnon-HT���ʣ���ô���ֶ���1 */


#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    oal_uint8                               bit_lpf_gain_level             : 2;
    oal_uint8                               bit_upc_gain_level             : 4;
    oal_uint8                               bit_pa_gain_level              : 2;

    oal_uint8                               bit_dpd_enable                 : 1;
    oal_uint8                               auc_reserve1                   : 7;

    /* 02оƬ������ӿ����ű�����Ϊtx��������ֵ */
    oal_uint8                               bit_anti_intf_1thr              : 2;
    oal_uint8                               bit_anti_intf_0thr              : 2;
    oal_uint8                               bit_anti_intf_en                : 1;
    oal_uint8                               bit_reserve                     : 3;
#else
    oal_uint8                               bit_upc_gain_level             : 1;  /*UPC���漶��*/
    oal_uint8                               bit_pa_gain_level              : 1;  /*PA���漶��*/
    oal_uint8                               bit_micro_tx_power_gain_level  : 4;  /*Micro Tx power���漶��*/
    oal_uint8                               bit_dac_gain_level             : 2;  /*DAC���漶��*/

    oal_uint8                               auc_reserve1[2];
#endif

    oal_uint8                               uc_smoothing;                   /* ֪ͨ���ն��Ƿ���ŵ�������ƽ�� */

    wlan_sounding_enum_uint8                en_sounding_mode;               /* soundingģʽ */
}hal_tx_txop_rate_params_stru;

typedef union
{
    oal_uint32  ul_value;
    /* (��14 19 20 21��) */
    struct
    {
    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        oal_uint8   bit_tx_count              : 2;                      /* ������� */
        oal_uint8   bit_stbc_mode             : 2;                      /* ��ʱ������� */
    #else
        oal_uint8   bit_tx_count              : 4;                      /* ������� */
    #endif
        oal_uint8   bit_tx_chain_selection    : 4;                      /* ����ͨ��ѡ�� (��ͨ��:0x1, ˫ͨ��:0x3, ��ͨ��:0x7, ��ͨ��:0xf) */
        oal_uint8   uc_tx_data_antenna;                                 /* ��������ʹ�õ�������� */

        union
        {
            struct
            {
                oal_uint8   bit_vht_mcs       : 4;
                oal_uint8   bit_nss_mode      : 2;                       /* �����ʶ�Ӧ�Ŀռ���ö��ֵ */
                oal_uint8   bit_protocol_mode : 2;                       /* Э��ģʽ */
            } st_vht_nss_mcs;
            struct
            {
                oal_uint8   bit_ht_mcs        : 6;
                oal_uint8   bit_protocol_mode : 2;                       /* Э��ģʽ */
            } st_ht_rate;
            struct
            {
                oal_uint8   bit_legacy_rate   : 4;
                oal_uint8   bit_reserved1     : 2;
                oal_uint8   bit_protocol_mode : 2;                       /* Э��ģʽ */
            } st_legacy_rate;
        } un_nss_rate;

        oal_uint8   bit_rts_cts_enable        : 1;                      /* �Ƿ�ʹ��RTS */
        oal_uint8   bit_txbf_mode             : 2;                      /* txbfģʽ */
        oal_uint8   bit_preamble_mode         : 1;                      /* ǰ���� */
        oal_uint8   bit_short_gi_enable       : 1;                      /* �̱������ */
        oal_uint8   bit_reserve               : 3;
    }rate_bit_stru;
}hal_tx_txop_per_rate_params_union;

typedef struct
{
    /* PHY TX MODE 2 (��15��) */
    oal_uint8                               uc_tx_rts_antenna;          /* ����RTSʹ�õ�������� */
    oal_uint8                               uc_rx_ctrl_antenna;         /* ����CTS/ACK/BAʹ�õ�������� */
    oal_uint8                               auc_reserve1[1];            /* TX VAP index �����㷨��д�����ڴ�Ҳ��0 */
    oal_uint8                               bit_txop_ps_not_allowed: 1; /* 0��������TXOP POWER save��1��������TXOP POWER save */
    oal_uint8                               bit_long_nav_enable:     1; /* NAV����enable�ֶΣ�1����Long nav������0����non long nav���� */
    oal_uint8                               bit_group_id:            6; /* ����ֶ���ʱ�������д�����տ������㷨��д�������г� */

}hal_tx_txop_antenna_params_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
typedef struct
{
    /* TX POWER (��22��) */
    oal_uint8                               bit_lpf_gain_level0           : 1;
    oal_uint8                               bit_pa_gain_level0            : 1;
    oal_uint8                               bit_upc_gain_level0           : 4;
    oal_uint8                               bit_dac_gain_level0           : 2;

    oal_uint8                               bit_lpf_gain_level1           : 1;
    oal_uint8                               bit_pa_gain_level1            : 1;
    oal_uint8                               bit_upc_gain_level1           : 4;
    oal_uint8                               bit_dac_gain_level1           : 2;

    oal_uint8                               bit_lpf_gain_level2           : 1;
    oal_uint8                               bit_pa_gain_level2            : 1;
    oal_uint8                               bit_upc_gain_level2           : 4;
    oal_uint8                               bit_dac_gain_level2           : 2;

    oal_uint8                               bit_lpf_gain_level3           : 1;
    oal_uint8                               bit_pa_gain_level3            : 1;
    oal_uint8                               bit_upc_gain_level3           : 4;
    oal_uint8                               bit_dac_gain_level3           : 2;

}hal_tx_txop_tx_power_stru;
#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_TEST_MODE != _PRE_TEST_MODE_OFF) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST)||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))
typedef struct
{
    /* TX POWER (��14��) */
    oal_uint8                               bit_lpf_gain_level0           : 2;
    oal_uint8                               bit_upc_gain_level0           : 4;
    oal_uint8                               bit_pa_gain_level0            : 2;

    oal_uint8                               bit_lpf_gain_level1           : 2;
    oal_uint8                               bit_upc_gain_level1           : 4;
    oal_uint8                               bit_pa_gain_level1            : 2;

    oal_uint8                               bit_lpf_gain_level2           : 2;
    oal_uint8                               bit_upc_gain_level2           : 4;
    oal_uint8                               bit_pa_gain_level2            : 2;

    oal_uint8                               bit_lpf_gain_level3           : 2;
    oal_uint8                               bit_upc_gain_level3           : 4;
    oal_uint8                               bit_pa_gain_level3            : 2;
}hal_tx_txop_tx_power_stru;
#endif

typedef struct
{
    wlan_tx_ack_policy_enum_uint8           en_ack_policy;     /* ACK ���� */
    oal_uint8                               uc_tid_no;        /* ͨ�ű�ʶ�� */
    oal_uint8                               uc_qos_enable;    /* �Ƿ���QoS */
    oal_uint8                               auc_resv[1];
}hal_wmm_txop_params_stru;

/* ��12 17�� */
typedef struct
{
    oal_uint16                              us_tsf_timestamp;
    oal_uint8                               uc_mac_hdr_len;
    oal_uint8                               uc_num_sub_msdu;
}hal_tx_mpdu_mac_hdr_params_stru;

typedef struct
{
    oal_uint32                              ul_mac_hdr_start_addr;
    oal_netbuf_stru                        *pst_skb_start_addr;
}hal_tx_mpdu_address_params_stru;

typedef struct
{
    oal_uint8                               uc_ra_lut_index;
    oal_uint8                               uc_tx_vap_index;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_uint8                               uc_ori_tx_vap_index;
    oal_uint8                               auc_resv[1];
#else
    oal_uint8                               auc_resv[2];
#endif
}hal_tx_ppdu_addr_index_params_stru;


typedef struct
{
    oal_uint32                              ul_msdu_addr0;
    oal_uint16                              us_msdu0_len;
    oal_uint16                              us_msdu1_len;
    oal_uint32                              ul_msdu_addr1;
}hal_tx_msdu_address_params;


typedef struct
{
    oal_uint8                            uc_long_retry;
    oal_uint8                            uc_short_retry;
    oal_uint8                            uc_rts_succ;
    oal_uint8                            uc_cts_failure;
    oal_int8                             c_last_ack_rssi;
    oal_uint8                            uc_mpdu_num;
    oal_uint8                            uc_error_mpdu_num;
    oal_uint8                            uc_last_rate_rank;
    oal_uint8                            uc_tid;
    hal_tx_queue_type_enum_uint8         uc_ac;
    oal_uint16                           us_mpdu_len;
    oal_uint8                            uc_is_retried;
    oal_uint8                            uc_bandwidth;
    oal_uint8			                 uc_sounding_mode;           /* ��ʾ��֡sounding���� */
    oal_uint8                            uc_status;                  /* ��֡�ķ��ͽ�� */
    oal_uint64                           ull_ampdu_result;
    hal_channel_matrix_dsc_stru          st_tx_dsc_chnl_matrix;      /*�����������е��ŵ�������Ϣ*/
    hal_tx_txop_per_rate_params_union    ast_per_rate[HAL_TX_RATE_MAX_NUM];
    oal_uint32                           ul_ampdu_length;
    hal_tx_txop_tx_power_stru            st_tx_power;

}hal_tx_dscr_ctrl_one_param;

typedef struct
{
    /* �ɰ�ȫ���Ը��� */
    wlan_security_txop_params_stru           *pst_security;         /* ��16�� MAC TX MODE 2 */

    /* groupid��partial_aid */
    wlan_groupid_partial_aid_stru            st_groupid_partial_aid;  /* ��12��15�в��� */

}hal_tx_txop_feature_stru;
/*****************************************************************************
  �ṹ��  : hal_tx_txop_alg_stru
  �ṹ˵��: DMACģ��TXOP���Ϳ��ƽṹ
*****************************************************************************/
typedef struct
{
    /*tx dscr���㷨��д�Ĳ��� */
    hal_channel_matrix_dsc_stru          st_txbf_matrix;                     /* ��10 23��  */
    hal_tx_txop_rate_params_stru         st_rate;                            /* ��13��(HY TX MODE 1)*/
    hal_tx_txop_per_rate_params_union    ast_per_rate[HAL_TX_RATE_MAX_NUM];  /* ��14(PHY TX RATA 1) 19 20 21 ��*/
    hal_tx_txop_antenna_params_stru      st_antenna_params;                  /* ��15��(PHY TX MODE 2) */
    hal_tx_txop_tx_power_stru            st_tx_power;                        /* ��22��(TX POWER)*/

}hal_tx_txop_alg_stru;

/*****************************************************************************
  �ṹ��  : hal_tx_ppdu_feature_stru
  �ṹ˵��: DMACģ��PPDU���Ϳ��ƽṹ
*****************************************************************************/
typedef struct
{
    /* ��15 16�� TX VAP index �� RA LUT Index */
    hal_tx_ppdu_addr_index_params_stru  st_ppdu_addr_index;

    /* ��16 17�� */
    oal_uint32                          ul_ampdu_length;         /* ������null data��ampdu�ܳ��� */
    oal_uint16                          us_min_mpdu_length;      /* �������ʲ��õ���ampdu��Сmpdu�ĳ��� */

    /* ��13�� */
    oal_uint8                           uc_ampdu_enable;         /* �Ƿ�ʹ��AMPDU */

    oal_uint8                           uc_rifs_enable;          /* rifsģʽ�·���ʱ��MPDU������Ƿ��һ��BAR֡ */
    /* ��12��  MAC TX MODE 1 */
    oal_uint16                          us_tsf;
    oal_uint8                           en_retry_flag_hw_bypass;
    oal_uint8                           en_duration_hw_bypass;
    oal_uint8                           en_seq_ctl_hw_bypass;
    oal_uint8                           en_timestamp_hw_bypass;
    oal_uint8                           en_addba_ssn_hw_bypass;
    oal_uint8                           en_tx_pn_hw_bypass;
    oal_uint8                           en_long_nav_enable;
    oal_uint8                           uc_mpdu_num;             /* ampdu��mpdu�ĸ��� */
    oal_uint8                           auc_resv[2];
}hal_tx_ppdu_feature_stru;

/*****************************************************************************
  �ṹ��  : hal_tx_mpdu_stru
  �ṹ˵��: DMACģ��MPDU���Ϳ��ƽṹ
*****************************************************************************/
typedef struct
{
    /* ��11MAC֡ͷ�л�ȡ ���MPDU*/
    hal_wmm_txop_params_stru              st_wmm;
    hal_tx_mpdu_mac_hdr_params_stru       st_mpdu_mac_hdr;                          /* ��12 17��(PHY TX MODE 2) */
    hal_tx_mpdu_address_params_stru       st_mpdu_addr;                             /* ��18��(MAC TX MODE 2)*/
    hal_tx_msdu_address_params            ast_msdu_addr[WLAN_DSCR_SUBTABEL_MAX_NUM];/* ��24,25...��*/
}hal_tx_mpdu_stru;

/* Beacon֡���Ͳ��� */
typedef struct
{
    oal_uint32              ul_pkt_ptr;
    oal_uint32              us_pkt_len;
    hal_tx_txop_alg_stru   *pst_tx_param;
    oal_uint32              ul_tx_chain_mask;

    //dmac���������������������Ĵ�����ֵ�ŵ�hal
    //oal_uint32  ul_phy_tx_mode;     /* ͬtx������ phy tx mode 1 */
    //oal_uint32  ul_tx_data_rate;    /* ͬtx������ data rate 0 */

}hal_beacon_tx_params_stru;

/*****************************************************************************
  �ṹ��  : hal_security_key_stru
  �ṹ˵��: DMACģ�鰲ȫ��Կ���ýṹ��
*****************************************************************************/
typedef struct
{
    oal_uint8                           uc_key_id;
    wlan_cipher_key_type_enum_uint8     en_key_type;
    oal_uint8                           uc_lut_idx;
    wlan_ciper_protocol_type_enum_uint8 en_cipher_type;
    oal_bool_enum_uint8                 en_update_key;
    wlan_key_origin_enum_uint8          en_key_origin;
    oal_uint8                           auc_reserve[2];
    oal_uint8                           *puc_cipher_key;
    oal_uint8                           *puc_mic_key;
}hal_security_key_stru;

/*****************************************************************************
  7.4 ��׼VAP��Device�ṹ
*****************************************************************************/
typedef struct tag_hal_to_dmac_vap_stru
{
    oal_uint8                            uc_chip_id;                                 /* оƬID */
    oal_uint8                            uc_device_id;                               /* �豸ID */
    oal_uint8                            uc_vap_id;                                  /* VAP ID */
    wlan_vap_mode_enum_uint8             en_vap_mode;                                /* VAP����ģʽ */
    oal_uint8                            uc_mac_vap_id;                              /* ����mac vap id */
    oal_uint8                            uc_dtim_cnt;                                /* dtim count */
    oal_uint8                            uc_service_id;
    oal_uint8                            uc_resv[1];
}hal_to_dmac_vap_stru;


/*****************************************************************************
  7.5 ���ⲿ�����ṩ�ӿ��������ݽṹ
*****************************************************************************/
typedef struct
{
    oal_int8            c_rssi_dbm;
    union
    {
        struct
        {
            oal_uint8   bit_vht_mcs       : 4;
            oal_uint8   bit_nss_mode      : 2;
            oal_uint8   bit_protocol_mode : 2;
        } st_vht_nss_mcs;                                   /* 11ac�����ʼ����� */
        struct
        {
            oal_uint8   bit_ht_mcs        : 6;
            oal_uint8   bit_protocol_mode : 2;
        } st_ht_rate;                                       /* 11n�����ʼ����� */
        struct
        {
            oal_uint8   bit_legacy_rate   : 4;
            oal_uint8   bit_reserved1     : 2;
            oal_uint8   bit_protocol_mode : 2;
        } st_legacy_rate;                                   /* 11a/b/g�����ʼ����� */
    } un_nss_rate;

    oal_uint8           uc_short_gi;
    oal_uint8           uc_bandwidth;
}hal_rx_statistic_stru;



#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
/* ��ϵͳ�£�������Ҫ�����HMACģ�����Ϣ����mac_rx_ctl_stru�ṹ�屣��һ��*/
/*hal_rx_ctl_stru�ṹ���޸�Ҫ����hi1102_rx_get_info_dscr�����е��Ż�
���ҽṹ�޸�Ҫ���ļ�dmac_ext_if.h��hmac_ext_if.h �е��޸�һ��*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_da_user_idx       :4;
    oal_uint8                   bit_ta_user_idx       :4;
    oal_uint8                   bit_mac_header_len    :6;   /* mac header֡ͷ���� */
    oal_uint8                   bit_reserved1         :2;
    /*word 1*/
    oal_uint16                  us_frame_len;               /* ֡ͷ��֡����ܳ��� */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4;   /* ÿ��MPDUռ�õ�buf�� */
}hal_rx_ctl_stru;
#else
/* ������Ҫ�����HMACģ�����Ϣ����mac_rx_ctl_stru�ṹ�屣��һ��*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;   /* ��Ӧhal vap id */
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_buff_nums         :4;   /* ÿ��MPDUռ�õ�buf��Ŀ */
    oal_uint8                   bit_reserved1         :4;
    oal_uint8                   uc_mac_header_len;          /* mac header֡ͷ���� */
    /*word 1*/
    oal_uint16                  us_frame_len;               /* ֡ͷ��֡����ܳ��� */
    oal_uint16                  us_da_user_idx;             /* Ŀ�ĵ�ַ�û����� */
    /*word 2*/
    oal_uint32                 *pul_mac_hdr_start_addr;     /* ��Ӧ��֡��֡ͷ��ַ,�����ַ */
}hal_rx_ctl_stru;

#endif

/* ��DMAC SCAN ģ���ṩ��Ӳ��MAC/PHY�ŵ���������ṹ�� */
typedef struct
{
    /* �ŵ�ͳ�� */
    oal_uint32  ul_ch_stats_time_us;
    oal_uint32  ul_pri20_free_time_us;
    oal_uint32  ul_pri40_free_time_us;
    oal_uint32  ul_pri80_free_time_us;
    oal_uint32  ul_ch_rx_time_us;
    oal_uint32  ul_ch_tx_time_us;

    /* �ŵ����� */
    oal_uint8  uc_ch_estimate_time_ms;
    oal_int8   c_pri20_idle_power;
    oal_int8   c_pri40_idle_power;
    oal_int8   c_pri80_idle_power;

    oal_uint32 ul_stats_cnt;
    oal_uint32 ul_meas_cnt;
    oal_uint32 ul_test_cnt;
}hal_ch_statics_irq_event_stru;

/* ��DMAC SCANģ���ṩ��Ӳ���״�����Ϣ�ṹ�� */
typedef struct
{
    oal_uint8   uc_radar_type;
    oal_uint8   uc_radar_freq_offset;
    oal_uint8   uc_radar_bw;
    oal_uint8   uc_band;
    oal_uint8   uc_channel_num;
    oal_uint8   uc_working_bw;
    oal_uint8   auc_resv[2];
}hal_radar_det_event_stru;

typedef struct
{
    oal_uint32      ul_reg_band_info;
    oal_uint32      ul_reg_bw_info;
    oal_uint32      ul_reg_ch_info;
}hal_radar_irq_reg_list_stru;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
/*
 *��ϵͳ����Խ��գ��ṩ��ȡ�ӿ�
 * frame_len����
 * 802.11֡ͷ����(uc_mac_hdr_len)
*/
#pragma pack(push,1)

typedef struct
{
    /*word 0*/


    oal_uint8   bit_cipher_protocol_type  : 4;      /* ?????? */
    oal_uint8   bit_dscr_status           : 4;      /* ??????? */
    /*word 1*/


    oal_uint8   bit_channel_code          : 1;
    oal_uint8   bit_STBC                  : 2;
    oal_uint8   bit_GI                    : 1;
    oal_uint8   bit_rsvd                  : 1;
    oal_uint8   bit_AMPDU                 : 1;
    oal_uint8   bit_sounding_mode         : 2;
    /*word 2*/


    oal_uint8   bit_ext_spatial_streams   : 2;
    oal_uint8   bit_smoothing             : 1;
    oal_uint8   bit_freq_bandwidth_mode   : 4;
    oal_uint8   bit_preabmle              : 1;
    //oal_uint16  us_rx_frame_length;     /* ??hcc?? */
    /*word 3*/
    //oal_uint8   bit_amsdu_flag            : 1;              /* AMSDU?? */
    //oal_uint8   bit_buffer_start_flag     : 1;              /* AMSDU?,??MSDU?? */
    //oal_uint8   bit_frag_flag             : 1;              /* MSDU???? */
    oal_uint8   bit_reserved2             : 3;
    oal_uint8   bit_rsp_flag              : 1;


    oal_uint8   bit_column_number         : 4;

    /*word 4?5*/
    oal_uint16  us_channel_matrix_len;

    /* word 6 */

    oal_uint8   bit_code_book             : 2;   /* ???????? */
    oal_uint8   bit_grouping              : 2;
    oal_uint8   bit_row_number            : 4;
}hal_rx_status_stru;
#pragma pack(pop)

#else
/*
 *��Խ��գ��ṩ��ȡ�ӿ�
 * frame_len����
 * 802.11֡ͷ����(uc_mac_hdr_len)
*/
typedef struct
{
    /*word 0*/
    oal_uint8   bit_dscr_status           : 4;     /* ����������״̬ */
    oal_uint8   bit_cipher_protocol_type  : 4;  /* ֡�ļ�������*/
    oal_uint8   bit_ext_spatial_streams   : 2;
    oal_uint8   bit_smoothing             : 1;
    oal_uint8   bit_freq_bandwidth_mode   : 4;
    oal_uint8   bit_preabmle              : 1;
    oal_uint8   bit_channel_code          : 1;
    oal_uint8   bit_STBC                  : 2;
    oal_uint8   bit_GI                    : 1;
    oal_uint8   bit_reserved1             : 1;
    oal_uint8   bit_AMPDU                 : 1;
    oal_uint8   bit_sounding_mode         : 2;
    oal_uint8   uc_reserved1;
    /*word 1*/
    oal_uint8   bit_code_book             : 2;              /* �ŵ����������Ϣ */
    oal_uint8   bit_grouping              : 2;
    oal_uint8   bit_row_number            : 4;
    oal_uint8   bit_column_number         : 4;
    oal_uint8   bit_rsp_flag              : 3;
    oal_uint8   bit_reserved2             : 1;
    oal_uint16  us_channel_matrix_len;                   /* �ŵ����󳤶� */
    /*word 2*/
    oal_uint32  ul_tsf_timestamp;                        /* TSFʱ��� */
    /*word 3*/

}hal_rx_status_stru;
#endif
/*
 * ��Խ��գ��ṩ��ȡ�ӿ�
 *
*/
typedef struct
{
    oal_uint32                    ul_skb_start_addr;
}hal_rx_addr_stru;

/*��Է��ͣ��ṩ���ýӿ�*/
typedef struct
{
    oal_uint32                    ul_mac_hdr_start_addr;
    oal_uint32                    ul_skb_start_addr;
}hal_rx_ctrl_stru;

/*****************************************************************************
  7.6 ���ⲿ������VAP���ӿ��б������ⲿ����ֱ�ӵ��ã����ǵ��ö�Ӧ����������
*****************************************************************************/
typedef struct
{
    hal_to_dmac_vap_stru    st_vap_base;
    oal_uint32              ul_vap_base_addr;
}hal_vap_stru;

/*****************************************************************************
  �ṹ��  : hal_rx_dscr_queue_header_stru
  �ṹ˵��: ��������������ͷ�Ľṹ��
*****************************************************************************/
typedef struct
{
    oal_uint32                             *pul_element_head;   /* ָ���������������ĵ�һ��Ԫ�� */
    oal_uint32                             *pul_element_tail;   /* ָ�������������������һ��Ԫ�� */
    oal_uint16                              us_element_cnt;     /* ����������������Ԫ�صĸ��� */
    hal_dscr_queue_status_enum_uint8        uc_queue_status;    /* �������������е�״̬ */
    oal_uint8                               auc_resv[1];
}hal_rx_dscr_queue_header_stru;
/*****************************************************************************
  �ṹ��  : dmac_tx_dscr_queue_header_stru
  �ṹ˵��: ��������������ͷ�Ľṹ��
*****************************************************************************/
typedef struct
{
    oal_dlist_head_stru                     st_header;          /* ��������������ͷ��� */
    hal_dscr_queue_status_enum_uint8        en_queue_status;    /* ��������������״̬ */
    oal_uint8                               uc_ppdu_cnt;     /* ����������������Ԫ�صĸ��� */
    oal_uint8                               auc_resv[2];
}hal_tx_dscr_queue_header_stru;

/*****************************************************************************
  �ṹ��  : dmac_tx_dscr_queue_header_stru
  �ṹ˵��: ��������������ͷ�Ľṹ��
*****************************************************************************/
typedef struct
{
    oal_uint8         uc_nulldata_awake;              /* APʱ�յ�����λΪ0��null data�Ƿ���*/
    oal_uint8         uc_nulldata_phy_mode;           /* STAʱ����null data��phy mode */
    oal_uint8         uc_nulldata_rate;               /* STAʱ����null data������*/
    oal_uint8         uc_rsv[1];
    oal_uint32        ul_nulldata_interval;           /* STAʱ����null data�ļ��*/
    oal_uint32        ul_nulldata_address;            /* STAʱ����null data������*/
    oal_uint32        ul_ap0_probe_resp_address;      /* AP0��probe response�ڴ��ַ*/
    oal_uint32        ul_ap0_probe_resp_len;          /* AP0��probe response����*/
    oal_uint32        ul_ap1_probe_resp_address;      /* AP1��probe response�ڴ��ַ*/
    oal_uint32        ul_ap1_probe_resp_len;          /* AP1��probe response����*/
    oal_uint8         uc_ap0_probe_resp_phy;          /* AP0��probe response����phyģʽ*/
    oal_uint8         uc_ap0_probe_resp_rate;         /* AP0��probe response����reate*/
    oal_uint8         uc_ap1_probe_resp_phy;          /* AP1��probe response����phyģʽ*/
    oal_uint8         uc_ap1_probe_resp_rate;         /* AP1��probe response����reate*/

    oal_uint32        ul_set_bitmap;                  /* wow���� */
}hal_wow_param_stru;

typedef enum
{
    HAL_WOW_PARA_EN                    = BIT0,
    HAL_WOW_PARA_NULLDATA              = BIT1,
    HAL_WOW_PARA_NULLDATA_INTERVAL     = BIT2,
    HAL_WOW_PARA_NULLDATA_AWAKE        = BIT3,
    HAL_WOW_PARA_AP0_PROBE_RESP        = BIT4,
    HAL_WOW_PARA_AP1_PROBE_RESP        = BIT5,

    HAL_WOW_PARA_BUTT
} hal_wow_para_set_enum;
typedef oal_uint32 hal_tx_status_enum_uint32;

/*****************************************************************************
  �ṹ��  : hal_lpm_chip_state
  �ṹ˵��: оƬ�͹���״̬ö��
*****************************************************************************/
typedef enum
{
    HAL_LPM_STATE_POWER_DOWN,
    HAL_LPM_STATE_IDLE,
    HAL_LPM_STATE_LIGHT_SLEEP,
    HAL_LPM_STATE_DEEP_SLEEP,
    HAL_LPM_STATE_NORMAL_WORK,
    HAL_LPM_STATE_WOW,

    HAL_LPM_STATE_BUTT
}hal_lpm_state_enum;
typedef oal_uint8 hal_lpm_state_enum_uint8;

/*****************************************************************************
  �ṹ��  : hal_lpm_state_para
  �ṹ˵��: оƬ�͹���״̬���ò���
*****************************************************************************/
typedef struct
{
    oal_uint8         uc_dtim_count;              /* ��ǰ��DTIM countֵ��STA����ʱ������λ*/
    oal_uint8         uc_dtim_period;
    oal_uint8         bit_gpio_sleep_en:1,        /* soc˯�߻��ѵķ�ʽ,GPIO�ܽŷ�ʽʹ��*/
                      bit_soft_sleep_en:1,        /* soc˯��˯�ߵķ�ʽ,��˯�߷�ʽʹ��*/
                      bit_set_bcn_interval:1,     /* �Ƿ����beacon inter*/
                      bit_rsv          :6;
    oal_uint8         uc_rx_chain;               /* ����ͨ��ֵ*/
    oal_uint32        ul_idle_bcn_interval;      /* idle״̬��beaon inter*/
    oal_uint32        ul_sleep_time;             /* ��ʱ˯��ʱ�䣬��λms*/
}hal_lpm_state_param_stru;


/*****************************************************************************
  �ṹ��  : hal_cfg_rts_tx_param_stru
  �ṹ˵��: RTS���÷��Ͳ���
*****************************************************************************/
typedef struct
{
    wlan_legacy_rate_value_enum_uint8   auc_rate[HAL_TX_RATE_MAX_NUM];           /*�������ʣ���λmpbs*/
    wlan_phy_protocol_enum_uint8        auc_protocol_mode[HAL_TX_RATE_MAX_NUM] ; /*Э��ģʽ, ȡֵ�μ�wlan_phy_protocol_enum_uint8*/
    wlan_channel_band_enum_uint8        en_band;
    oal_uint8                           auc_recv[3];
}hal_cfg_rts_tx_param_stru;


/*****************************************************************************
  7.7 ���ⲿ�������豸���ӿ��б������ⲿ����ֱ�ӵ��ã����ǵ��ö�Ӧ����������
*****************************************************************************/
typedef oal_void (* p_hal_alg_isr_func)(oal_uint8 uc_vap_id, oal_void *p_hal_to_dmac_device);
typedef oal_void (* p_hal_gap_isr_func)(oal_uint8 uc_vap_id, oal_void *p_hal_to_dmac_device);


typedef struct
{

    oal_uint32      ul_phy_addr;
    oal_uint8       uc_status;
    oal_uint8       uc_q;
    oal_uint8       auc_resv[2];
    oal_uint32      ul_timestamp;

    oal_uint32      ul_arrive_time;     /* �°벿����ʱ�� */
    oal_uint32      ul_handle_time;     /* �°벿����ʱ�� */
    oal_uint32      ul_irq_cnt;
    oal_cpu_usage_stat_stru st_cpu_state;
}hal_rx_dpart_track_stru;

/* ����Ӳ���ϱ������ж���Ϣ�ṹ */
typedef struct
{
    oal_dlist_head_stru         st_dlist_head;
    oal_uint32                 *pul_base_dscr;      /* �����ж���������ַ */
    oal_uint16                  us_dscr_num;        /* ���յ����������ĸ��� */
    //oal_bool_enum_uint8         en_used;
    oal_uint8                   uc_channel_num;     /* �����ж�ʱ�����ڵ��ŵ��� */
    oal_uint8                   uc_queue_id;
}hal_hw_rx_dscr_info_stru;
typedef struct tag_hal_to_dmac_chip_stru
{
    oal_uint8   uc_chip_id;
}hal_to_dmac_chip_stru;

typedef enum
{
    HAL_DFR_TIMER_STEP_1 = 0,
    HAL_DFR_TIMER_STEP_2 = 1,

}hal_dfr_timer_step_enum;
typedef oal_uint8 hal_dfr_timer_step_enum_uint8;

typedef struct
{
    frw_timeout_stru                 st_tx_prot_timer;        /* ����޷�������ж϶�ʱ�� */
    hal_dfr_timer_step_enum_uint8    en_tx_prot_timer_step;   /* ��ʱ��־�������ڼ��γ�ʱ */
    oal_uint16                       us_tx_prot_time;         /* ��ʱʱ�� */
    oal_uint8                        auc_resv[1];
}hal_dfr_tx_prot_stru;

typedef struct
{
    oal_uint16    us_tbtt_cnt;   /* TBTT�жϼ�����ÿ10��TBTT�жϣ���us_err_cnt���� */
    oal_uint16    us_err_cnt;    /* ÿ10��TBTT�жϣ�������MAC�����жϸ��� */
}hal_dfr_err_opern_stru;

typedef struct
{
    oal_uint32                      ul_error1_val; /* ����1�ж�״̬ */
    oal_uint32                      ul_error2_val; /* ����2�ж�״̬ */
}hal_error_state_stru;

typedef struct
{
    oal_dlist_head_stru   st_entry;
    oal_uint32            ul_phy_addr;    /* ���������������ַ */
}witp_rx_dscr_recd_stru;


/*****************************************************************************
  �ṹ��  : hal_phy_tpc_param_stru
  �ṹ˵��: PHY TPC�Ĵ�������, ��2.4G/5GƵ���л�ʱʹ��
*****************************************************************************/
typedef struct
{
    oal_uint32                      ul_pa_bias_addr;                             /* PA_BIAS��ַ */
    oal_uint32                      aul_pa_bias_gain_code[WLAN_BAND_BUTT];       /* 2G/5G PA_BIAS CODE */
    oal_uint32                      ul_pa_addr;                             /* PA��ַ */
    oal_uint32                      aul_pa_gain_code[WLAN_BAND_BUTT];       /* 2G/5G PAIN CODE */
    oal_uint32                      aul_2g_upc_addr[WLAN_2G_SUB_BAND_NUM];  /* 2G UPC��ַ */
    oal_uint32                      aul_5g_upc_addr[WLAN_5G_SUB_BAND_NUM];  /* 5G UPC��ַ */
    oal_uint32                      aul_2g_upc1_data[WLAN_2G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 2G ͨ��1 UPC DATA */
    oal_uint32                      aul_2g_upc2_data[WLAN_2G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 2G ͨ��2 UPC DATA */
    oal_uint32                      aul_5g_upc1_data[WLAN_5G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 5G ͨ��1 UPC DATA */
    oal_uint32                      aul_5g_upc2_data[WLAN_5G_SUB_BAND_NUM][WLAN_UPC_DATA_REG_NUM];/* 5G ͨ��2 UPC DATA */
    oal_uint32                      ul_dac_addr;                            /* DAC��ַ */
    oal_uint32                      aul_dac_data[WLAN_BAND_BUTT];           /* 2G/5G DAC DATA */
    oal_uint32                      ul_lpf_addr;                            /* DAC��ַ */
    oal_uint32                      aul_lpf_data[WLAN_BAND_BUTT];           /* 2G/5G LPF DATA */
    oal_uint8                       auc_2g_cali_upc_code[2][WLAN_2G_SUB_BAND_NUM];/* 2GУ׼��UPC Code */
    oal_uint8                       auc_5g_cali_upc_code[2][WLAN_5G_CALI_SUB_BAND_NUM];  /* 5GУ׼��UPC Code(����20M��80M) */
    oal_uint8                       auc_reserve_addr[2];

    /*��ͬ֡��tpc code*/
    oal_uint32                      aul_2g_ofdm_ack_cts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint32                      aul_5g_ack_cts_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_dsss_ack_cts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_rts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_one_pkt_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_selfcts_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_cfend_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_abort_null_data_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_2g_cfend_tpc_code[WLAN_2G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_rts_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_one_pkt_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_abort_cfend_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_cfend_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_ndp_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_vht_report_tpc_code[WLAN_5G_SUB_BAND_NUM];
    oal_uint8                       auc_5g_abort_null_data_tpc_code[WLAN_5G_SUB_BAND_NUM];
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint8                       auc_reserve[2];
#endif
    /*��ȡ��ͬ֡��ʽ������*/
    oal_uint32                      ul_rate_ofdm_ack_cts;
    oal_uint8                       uc_rate_rts;
    oal_uint8                       uc_rate_one_pkt;
    oal_uint8                       uc_rate_abort_selfcts;
    oal_uint8                       uc_rate_abort_cfend;
    oal_uint8                       uc_rate_cfend;
    oal_uint8                       uc_rate_ndp;
    oal_uint8                       uc_rate_vht_report;
    oal_uint8                       uc_rate_abort_null_data;
}hal_phy_tpc_param_stru;

#ifdef _PRE_WLAN_FEATURE_DFS
typedef struct
{
    oal_bool_enum_uint8  en_chirp_enable;
    oal_uint8            auc_resv[3];
    oal_uint32           ul_chirp_time_threshold;
    oal_uint32           ul_chirp_cnt_threshold;
    oal_uint32           ul_time_threshold;
    oal_uint32           ul_last_burst_timestamp;
    oal_uint32           ul_last_burst_timestamp_for_chirp;
}hal_dfs_radar_filter_stru;
#endif

#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
typedef struct
{
    oal_uint16     us_max_offset_tsf;     /* ���ʱ��ʱ�� */
    oal_uint16     us_mpdu_len;           /* ���ʱ��mpdu���� */
    oal_uint16     us_tx_excp_cnt;        /* ������ɺ�ʱ�쳣ͳ�� */
    oal_uint8      uc_q_num;              /* ���ʱ��q_num*/
    oal_uint8      auc_resv;
}hal_tx_excp_info_stru;
#endif

typedef struct
{
    oal_uint32          ul_tkipccmp_rep_fail_cnt;    /* �طŹ���������TKIP + CCMP */
    oal_uint32          ul_tx_mpdu_cnt;              /* ���ͼ�����ampdu�����ȼ� + ��ͨ���ȼ� + ampdu��mpdu */
    oal_uint32          ul_rx_passed_mpdu_cnt;       /* ����AMPDU MPDU��FCS��ȷ��MPDU���� */
    oal_uint32          ul_rx_failed_mpdu_cnt;       /* ����AMPDU MPDU��FCS�����MPDU���� */
    oal_uint32          ul_rx_tkipccmp_mic_fail_cnt; /* kip mic + ccmp mic fail��֡�� */
    oal_uint32          ul_key_search_fail_cnt;      /* ����key serach fail��֡�� */
    oal_uint32          ul_phy_rx_dotb_ok_frm_cnt;       /* PHY����dotb ok��֡���� */
    oal_uint32          ul_phy_rx_htvht_ok_frm_cnt;      /* PHY����vht ht ok��֡���� */
    oal_uint32          ul_phy_rx_lega_ok_frm_cnt;       /* PHY����legace ok��֡���� */
    oal_uint32          ul_phy_rx_dotb_err_frm_cnt;      /* PHY����dotb err��֡���� */
    oal_uint32          ul_phy_rx_htvht_err_frm_cnt;     /* PHY����vht ht err��֡���� */
    oal_uint32          ul_phy_rx_lega_err_frm_cnt;      /* PHY����legace err��֡���� */

}hal_mac_key_statis_info_stru;

typedef struct tag_hal_to_dmac_device_stru
{
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_mac_device_id;                           /* ����mac device id */
    hal_lpm_state_enum_uint8        uc_curr_state;                              /*��ǰоƬ�ĵ͹���״̬*/
    oal_uint32                      ul_core_id;


    oal_dlist_head_stru             ast_rx_dscr_hash[HAL_RX_MAX_BUFFS];   /*  */

    hal_dfr_tx_prot_stru            st_dfr_tx_prot;                             /* �����޷�������жϼ�⼰�ָ� */
    hal_dfr_err_opern_stru          st_dfr_err_opern[HAL_MAC_ERROR_TYPE_BUTT];  /* ����MAC�쳣�жϻָ� */

    hal_rx_dscr_queue_header_stru   ast_rx_dscr_queue[HAL_RX_QUEUE_NUM];
    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue[HAL_TX_QUEUE_NUM];

#ifdef _PRE_DEBUG_MODE
    /* ��¼���������������У������������ĵ�ַ */
    witp_rx_dscr_recd_stru          st_nor_rx_dscr_recd[HAL_NORMAL_RX_MAX_BUFFS];
    witp_rx_dscr_recd_stru          st_hi_rx_dscr_recd[HAL_HIGH_RX_MAX_BUFFS];
#endif

    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue_fake[HAL_TX_FAKE_QUEUE_NUM][HAL_TX_QUEUE_NUM];

    oal_uint32                      ul_rx_normal_dscr_cnt;

    oal_uint32                      ul_track_stop_flag;
    oal_uint8                       uc_al_tx_flag;
    oal_uint8                       uc_fcc_country;            /* 0:��ʾ��FCC��֤���ң�1:��ʾFCC��֤���� */
    oal_uint8                       uc_full_phy_freq_user_cnt; //device����Ҫ��Ƶ��vap(ap)/sta(user) ����
    oal_uint8                       uc_over_temp;
    oal_uint32                      bit_al_tx_flag        :3;  /*0: �رճ���; 1:������RF����; 2: ampdu�ۺ�֡����; 3:�Ǿۺ�֡����*/
    oal_uint32                      bit_al_rx_flag        :3;  /*0: �رճ���; 1:������RF���ԣ�2: ampdu�ۺ�֡����; 3:�Ǿۺ�֡����*/
    oal_uint32                      bit_one_packet_st     :1;  /* 0��ʾDBC���� 1��ʾDBAC����ִ�� */
    oal_uint32                      bit_clear_fifo_st     :1;  /* 0��ʾ��clear fifo״̬��1��ʾclear fifo״̬ */
    oal_uint32                      bit_al_txrx_ampdu_num :8;  /*ָʾ���ڳ������յľۺ�֡��Ŀ*/
    oal_uint32                      bit_track_cnt         :8;  /* ����qempty ʣ���¼��Ŀ�� */
    oal_uint32                      bit_track_cnt_down    :8;  /* ʣ���¼��Ŀ���ٱ�־ */
    oal_netbuf_stru *               pst_alrx_netbuf;           /* ��¼����ʱ�������������õ��ڴ� */
    oal_uint32                      ul_rx_normal_mdpu_succ_num;
    oal_uint32                      ul_rx_ampdu_succ_num;
    oal_uint32                      ul_tx_ppdu_succ_num;
    oal_uint32                      ul_rx_ppdu_fail_num;
    oal_uint32                      ul_tx_ppdu_fail_num;
#ifdef _PRE_DEBUG_MODE
    oal_uint32                      ul_dync_txpower_flag;
#endif

    oal_dlist_head_stru             ast_rx_isr_info_list[HAL_HW_RX_DSCR_LIST_NUM];
    hal_hw_rx_dscr_info_stru        ast_rx_isr_info_member[HAL_HW_RX_ISR_INFO_MAX_NUMS];
    oal_dlist_head_stru             st_rx_isr_info_res_list;  /* �����ж���Ϣ�洢��Դ���� */
    oal_uint8                       uc_current_rx_list_index;
    oal_uint8                       uc_current_chan_number;
    wlan_p2p_mode_enum_uint8        en_p2p_mode;               /* ָʾ��ǰ������P2P �Ǵ���CL/GO ģʽ������P2P �жϲ�����ֻ��ͨ��������P2P �豸��CL ����GO ����ȡ��Ӧ��hal_vap_id���������Ӹñ��� */
    oal_bool_enum_uint8             en_rx_intr_fifo_resume_flag;    /* RX INTR FIFO OVERRUN�Ƿ�ָ���ʶ */

#ifdef _PRE_DEBUG_MODE
    /* ԭʼ�����������ַ */
    oal_uint32                      aul_nor_rx_dscr[HAL_NORMAL_RX_MAX_BUFFS];
    oal_uint32                      aul_hi_rx_dscr[HAL_HIGH_RX_MAX_BUFFS];

    oal_uint32                      ul_dpart_save_idx;
    oal_uint32                      ul_rx_irq_loss_cnt;
    hal_rx_dpart_track_stru         ast_dpart_track[HAL_DOWM_PART_RX_TRACK_MEM];

    /* �������쳣����ͳ�� */
    oal_uint32                      ul_exception_free;
    oal_uint32                      ul_irq_cnt;

#endif
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    oam_user_track_rx_ampdu_stat    st_user_track_rx_ampdu_stat;
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
    hal_dfs_radar_filter_stru       st_dfs_radar_filter;
#endif

    /* TPC���PHY����*/
    hal_phy_tpc_param_stru          st_phy_tpc_param;

    /* RTS������ز��� */
    wlan_legacy_rate_value_enum_uint8   auc_rts_rate[WLAN_BAND_BUTT][HAL_TX_RATE_MAX_NUM];      /* ����Ƶ�ε�RTS�������� */
    wlan_phy_protocol_enum_uint8        auc_rts_protocol[WLAN_BAND_BUTT][HAL_TX_RATE_MAX_NUM] ; /* ����Ƶ�ε�RTSЭ��ģʽ */

    /* �ֽڶ��� */
    p_hal_alg_isr_func  pa_hal_alg_isr_func_table[HAL_ISR_TYPE_BUTT][HAL_ALG_ISR_NOTIFY_BUTT];

    p_hal_gap_isr_func  pa_hal_gap_isr_func_table[HAL_ISR_TYPE_BUTT];

    oal_uint8                     *puc_mac_reset_reg;
    oal_uint8                     *puc_phy_reset_reg;
    oal_uint16                     uc_cali_check_hw_status;    /*FEM&PAʧЧ���*/
    oal_int16                      s_always_rx_rssi;

    hal_wifi_channel_status_stru   st_wifi_channel_status;
    oal_uint32                          ul_rx_rate;
    oal_int32                           l_rx_rssi;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_btble_status_stru   st_btcoex_btble_status;
    hal_btcoex_statistics_stru    st_btcoex_statistics;
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
    oal_uint32                     ul_lte_coex_status;
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    hal_dual_antenna_check_status_stru st_dual_antenna_check_status;
    oal_uint32 ul_dual_antenna_status;
#endif
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
    hal_tx_excp_info_stru          st_tx_excp_info;
#endif

#ifdef _PRE_WLAN_FEATURE_DFR
#ifdef _PRE_DEBUG_MODE
    oal_uint32                     ul_cfg_loss_tx_comp_cnt;              /* ͨ�����������ֶ���ʧ��������ж� */
#endif
	oal_bool_enum_uint8            en_dfr_enable;                        /* dfr�Ƿ�enable */
#endif
} hal_to_dmac_device_stru;




/* HALģ���DMACģ�鹲�õ�WLAN RX�ṹ�� */
typedef struct
{
    oal_uint32                 *pul_base_dscr;      /* ����������ַ */
    oal_bool_enum_uint8         en_sync_req;        /* ����ͬ����ʶ */
    oal_uint16                  us_dscr_num;        /* ���յ����������ĸ��� */
    oal_uint8                   uc_queue_id;        /* ���ն��к� */
    hal_to_dmac_device_stru    *pst_hal_device;
    oal_uint8                   uc_channel_num;
    oal_uint8                   auc_resv[3];
}hal_wlan_rx_event_stru;

typedef struct
{
    hal_tx_dscr_stru        *pst_base_dscr;/* ��������ж�Ӳ�����ϱ���������ָ�� */
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint8                uc_dscr_num; /* Ӳ��һ�η��������������������� */

    oal_uint8                auc_resv[3];
}hal_tx_complete_event_stru;

typedef struct
{
    hal_error_state_stru            st_error_state;
    hal_to_dmac_device_stru        *pst_hal_device;
}hal_error_irq_event_stru;

typedef struct
{
    oal_uint8                       p2p_noa_status; /* 0: ��ʾnoa ��ʱ��ֹͣ��1: ��ʾnoa ��ʱ�����ڹ��� */
    oal_uint8                       auc_resv[3];
}hal_p2p_pm_event_stru;


/*****************************************************************************
  10.2 ���Ⱪ¶�����ýӿ�
*****************************************************************************/
/************************  1151  ********************************************/
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_void  hi1151_set_pcie_pm_level(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_pcie_pm_level);
#define HAL_CHIP_LEVEL_FUNC_EXTERN
extern oal_uint32 hal_chip_get_device_num_impl(oal_bus_dev_stru * pst_bus_stru, oal_uint8 * puc_device_nums);
#define HAL_DEVICE_LEVEL_FUNC_EXTERN
extern oal_uint32 hal_chip_get_device_impl(oal_bus_dev_stru * pst_bus_stru, oal_uint8 uc_device_id, hal_to_dmac_device_stru **ppst_device_stru);
extern oal_void hi1151_get_chip_version(hal_to_dmac_chip_stru *pst_hal_chip, oal_uint32 *pul_chip_ver);
extern oal_void hi1151_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_hal_device,oal_uint8 uc_set_hw);
extern oal_void  hi1151_rx_dscr_add_netbuf(hal_to_dmac_device_stru *pst_device, oal_uint32  *pul_ret);
extern oal_void  hi1151_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_buff);
extern oal_void hi1151_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device,oal_uint8 uc_destroy_netbuf);
extern oal_void hi1151_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1151_al_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_device);

extern oal_void hi1151_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_tx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1151_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_free_rx_isr_list(oal_dlist_head_stru  *pst_rx_isr_list);
extern oal_void hi1151_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_get_tx_dscr_queue_total_ppdu_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 *pus_ppdu_cnt);
extern oal_void hi1151_tx_fill_basic_ctrl_dscr(hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu);
extern oal_void hi1151_tx_ctrl_dscr_link(hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1151_get_tx_dscr_next(hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next);
extern oal_void hi1151_tx_ctrl_dscr_unlink(hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1151_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1151_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1151_tx_set_dscr_modify_mac_header_length(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length);
extern oal_void hi1151_tx_set_dscr_seqno_sw_generate(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate);
extern oal_void hi1151_tx_get_size_dscr(oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size);
extern oal_void hi1151_tx_get_vap_id(hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id);
extern oal_void hi1151_tx_get_dscr_ctrl_one_param(hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param);
extern oal_void hi1151_tx_get_dscr_seq_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num);
extern oal_void  hi1151_tx_get_dscr_tx_cnt(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count);
extern oal_void hi1151_tx_get_dscr_mpdu_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_mpdu_num);
extern oal_void hi1151_tx_set_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status);
extern oal_void hi1151_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id);
extern oal_void hi1151_tx_get_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status);
extern oal_void  hi1151_tx_get_dscr_send_rate_rank(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank);
extern oal_void hi1151_tx_get_dscr_ba_ssn(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn);
extern oal_void hi1151_tx_get_dscr_ba_bitmap(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap);
extern oal_void hi1151_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr);
extern oal_void hi1151_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum);
extern oal_void hi1151_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_void hi1151_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode);
#endif
extern oal_void hi1151_rx_get_size_dscr(oal_uint32 * pul_dscr_size);
extern oal_void hi1151_rx_get_info_dscr(oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics);
extern oal_void hi1151_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap);
extern oal_void hi1151_rx_get_netbuffer_addr_dscr(oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr);
extern oal_void hi1151_rx_get_mac_hdr_addr_dscr(oal_uint32 *pul_rx_dscr, oal_uint32 ** ppul_mac_hdr_address_dscr);
extern oal_void hi1151_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type);
extern oal_void hi1151_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num);
extern oal_void hi1151_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr);
extern oal_void hi1151_dump_rx_dscr(oal_uint32 *pul_rx_dscr);
extern oal_void hi1151_dump_tx_dscr(oal_uint32 *pul_tx_dscr);
extern oal_void hi1151_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val);
extern oal_void hi1151_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void hi1151_resume_mac_rx_dscr_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_uint32 hi1151_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device,
                                                        oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void hi1151_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                     oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg);
extern oal_void hi1151_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_initialize_machw(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth);

#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1151_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1151_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num,wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#endif
extern oal_void hi1151_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1151_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_HW_TEST
extern oal_void hi1151_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_void hi1151_freq_adjust(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_pll_int, oal_uint16 us_pll_frac);
#endif

extern oal_void hi1151_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain);
extern oal_void hi1151_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size);
extern oal_void hi1151_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1151_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
										 oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para);
extern oal_void hi1151_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                             oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para);
extern oal_void hi1151_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag);
extern oal_void hi1151_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write);
extern oal_void hi1151_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read);
extern oal_void hi1151_reset_init(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_reset_destroy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1151_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1151_reset_reg_dma_save(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1151_reset_reg_dma_restore(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1151_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_initialize_phy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain);
extern oal_void hi1151_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device);
#ifdef _PRE_WLAN_REALTIME_CALI
extern oal_void hi1151_rf_cali_realtime(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_freq, oal_uint8 uc_chn_idx, oal_uint8 uc_bandwidth, oal_uint8 uc_protocol);
#endif
extern oal_void  hi1151_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status);

extern oal_void hi1151_initialize_soc(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status);
extern oal_void hi1151_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1151_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state);
extern oal_void hi1151_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1151_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1151_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1151_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param);
extern oal_void hi1151_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_irq_stat(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 *puc_param, oal_uint32 ul_len, oal_uint8 uc_type);
extern oal_void hi1151_get_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1151_add_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1151_del_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void hi1151_set_proxysta_enable(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable);
#endif
extern oal_void hi1151_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol);
extern oal_void hi1151_register_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                           hal_alg_noify_enum_uint8 en_alg_notify,p_hal_alg_isr_func p_func);
extern oal_void hi1151_unregister_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                             hal_alg_noify_enum_uint8 en_alg_notify);
extern oal_void hi1151_register_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,p_hal_alg_isr_func p_func);
extern oal_void hi1151_unregister_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type);
extern oal_void hi1151_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg);
extern oal_void hi1151_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status);
extern oal_void hi1151_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1151_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1151_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1151_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val);
extern oal_void hi1151_get_all_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_val);
extern oal_void hi1151_get_ampdu_bytes(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes);
extern oal_void hi1151_get_rx_err_count(hal_to_dmac_device_stru* pst_hal_device,
                                        oal_uint32* pul_cnt1,
                                        oal_uint32* pul_cnt2,
                                        oal_uint32* pul_cnt3,
                                        oal_uint32* pul_cnt4,
                                        oal_uint32* pul_cnt5,
                                        oal_uint32* pul_cnt6);
extern oal_void hi1151_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type);
extern oal_void hi1151_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr);
extern oal_void hi1151_disable_ce(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1151_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
extern oal_void hi1151_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr);
extern oal_void hi1151_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx);
extern oal_void hi1151_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1151_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
extern oal_void hi1151_tx_get_dscr_phy_mode_one(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_phy_mode_one);
extern oal_void hi1151_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index);
extern oal_void hi1151_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
#endif
extern oal_void hi1151_get_rate_80211g_table(oal_void **pst_rate);
extern oal_void hi1151_get_rate_80211g_num(oal_uint32 *pst_data_num);
extern oal_void hi1151_get_hw_addr(oal_uint8 *puc_addr);
extern oal_void hi1151_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period);
extern oal_void hi1151_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period);
extern oal_void hi1151_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1151_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1151_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1151_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void hi1151_set_improve_ce_threshold(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void hi1151_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info);
extern oal_void hi1151_update_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param);
extern oal_void hi1151_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1151_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp);
extern oal_void hi1151_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode);
extern oal_void  hi1151_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code, oal_int8 *pac_tpc_level_table,
        oal_uint8 uc_tpc_level_num, oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table, oal_int16 *pas_other_gain_table,wlan_channel_band_enum_uint8 en_freq_band);
extern oal_void  hi1151_get_bcn_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_data_rate);
extern oal_void hi1151_set_bcn_phy_tx_mode(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_tpc_code);
extern oal_void  hi1151_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1151_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param);
extern oal_void hi1151_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2);
extern oal_void hi1151_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2);
extern oal_void hi1151_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void hi1151_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void  hi1151_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1151_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx);
extern oal_void  hi1151_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate,
       oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx);
#ifdef _PRE_WLAN_REALTIME_CALI
extern oal_void  hi1151_get_tpc_cali_upc_gain_in_rf_list(oal_int8* pac_upc_gain_in_rf_list);
#endif
#endif
extern oal_void hi1151_irq_affinity_init(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_core_id);
extern oal_void hi1151_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_mac_addr,oal_uint8 uc_lut_index);
#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hi1151_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix);
extern oal_void hi1151_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix);
extern oal_void hi1151_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1151_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1151_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1151_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1151_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time);
extern oal_void hi1151_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration);
extern oal_void hi1151_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_group_id);
extern oal_void hi1151_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1151_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1151_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1151_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1151_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);
extern oal_void hi1151_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_val);
extern oal_void hi1151_set_mu_aid_matrix_info(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_aid, oal_uint8  *p_matrix);
extern oal_void hi1151_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1151_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1151_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);

#endif

extern oal_void hi1151_enable_smart_antenna_gpio_set_default_antenna(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_delete_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1151_set_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1151_get_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
extern oal_void hi1151_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_device, oal_int32 l_reg_val);
extern oal_void hi1151_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val);
extern oal_void hi1151_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint16 us_obss_dur);
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
extern oal_void hi1151_set_counter1_clear(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1151_get_txrx_frame_time(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_reg_val);
extern oal_void hi1151_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable);
#endif
extern oal_void hi1151_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis);


#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_void hi1151_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *pl_ed_high_reg_val);
extern oal_void hi1151_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val);
extern oal_void hi1151_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val);
extern oal_void hi1151_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val);
extern oal_void hi1151_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val);

#endif
extern oal_void hi1151_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle);
extern oal_void hi1151_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void  hi1151_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count);
extern oal_void  hi1151_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval);
extern oal_void  hi1151_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1151_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);

#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1151_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void hi1151_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
#endif
#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1151_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1151_set_txop_ps_partial_aid(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint16 us_partial_aid);
#endif
extern oal_void hi1151_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para);
extern oal_void hi1151_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para, oal_void* pst_wow_para);
extern oal_void hi1151_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en);
extern oal_void hi1151_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl);
extern oal_void hi1151_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num);
extern oal_void hi1151_psm_rf_sleep (hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
extern oal_void hi1151_psm_rf_awake (hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg);

#ifdef _PRE_DEBUG_MODE
extern oal_void hi1151_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_get_cali_data(hal_to_dmac_device_stru * pst_hal_device);
#endif

extern oal_void hi1151_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect);
extern oal_void hi1151_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1151_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
extern oal_void hi1151_al_tx_set_agc_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
#endif

#ifdef _PRE_WLAN_PHY_PLL_DIV
extern oal_void hi1151_rf_set_freq_skew(oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[]);
#endif
extern oal_void hi1151_rf_adjust_ppm(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_ppm, wlan_channel_bandwidth_enum_uint8  en_bandwidth, oal_uint8 uc_clock);
extern oal_void hi1151_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth);
extern oal_void hi1151_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1151_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value);
extern oal_void hi1151_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value);
#ifdef _PRE_WLAN_HW_TEST
extern oal_void hi1151_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
#endif
extern oal_void hi1151_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val);
extern oal_void hi1151_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
extern oal_void  hi1151_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value);
extern oal_void  hi1151_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period);
extern oal_void  hi1151_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val);
extern oal_void  hi1151_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device);

#define HAL_VAP_LEVEL_FUNC_EXTERN
extern oal_void hi1151_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo);
extern oal_void hi1151_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo);
extern oal_void hi1151_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo);
extern oal_void hi1151_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo);
extern oal_void hi1151_vap_send_beacon_pkt(hal_to_dmac_vap_stru *pst_hal_vap, hal_beacon_tx_params_stru *pst_params);
extern oal_void hi1151_vap_set_beacon_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_rate);
extern oal_void hi1151_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate);
extern oal_void hi1151_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr);
extern oal_void hi1151_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);

extern oal_void hi1151_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);
extern oal_void hi1151_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo);
extern oal_void hi1151_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                            wlan_wme_ac_type_enum_uint8   en_ac,
                                            oal_uint8                     uc_aifs);
extern oal_void hi1151_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ac_type);
extern oal_void hi1151_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ac_type);
#if 0
extern oal_void hi1151_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1151_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1151_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
#endif
extern oal_void hi1151_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1151_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1151_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1151_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1151_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1151_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1151_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1151_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1151_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable);
extern oal_void hi1151_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value);
extern oal_void hi1151_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value);
extern oal_void hi1151_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1151_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1151_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period);
extern oal_void  hi1151_sta_tsf_save(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_need_restore);
extern oal_void  hi1151_sta_tsf_restore(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void  hi1151_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void  hi1151_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window);
extern oal_void hi1151_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru * pst_hal_vap,
                oal_bool_enum_uint8 en_suspend_enable);
#endif
extern oal_void hi1151_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte);
extern oal_void  hi1151_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim);
extern oal_void hi1151_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period);
extern oal_void hi1151_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period);

extern oal_void  hi1151_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *uc_dtim_count);
extern oal_void  hi1151_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count);
extern oal_void hi1151_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count);
extern oal_void  hi1151_pm_wlan_servid_register(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint32 *pul_ret);
extern oal_void hi1151_pm_wlan_servid_unregister(hal_to_dmac_vap_stru  *pst_hal_vap);
extern oal_void hi1151_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1151_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_keyid);
extern oal_void hi1151_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val);
extern oal_void  hi1151_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void  hi1151_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void  hi1151_get_beacon_miss_status(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1151_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_void hi1151_set_txrx_chain(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_void hi1151_cfg_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_get_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_revert_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1151_check_test_value_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value, oal_uint32 *pul_result);
extern oal_void hi1151_config_always_rx(hal_to_dmac_device_stru *pst_hal_device_base, oal_uint8 uc_switch);

extern oal_uint32 hi1151_rf_get_pll_div_idx(wlan_channel_band_enum_uint8        en_band,
                                               oal_uint8                           uc_channel_idx,
                                               wlan_channel_bandwidth_enum_uint8   en_bandwidth,
                                               oal_uint8                           *puc_pll_div_idx);

#ifdef _PRE_WLAN_RF_CALI
extern oal_void hi1151_rf_cali_set_vref(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_chain_idx,
                                    oal_uint8  uc_band_idx, oal_uint16 us_vref_value);
extern oal_void hi1151_rf_auto_cali(hal_to_dmac_device_stru * pst_hal_device);
#endif

#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))

/************************  1102  CHIP********************************************/
#define HAL_CHIP_LEVEL_FUNC_EXTERN
extern oal_void hi1102_get_chip_version(hal_to_dmac_chip_stru *pst_hal_chip, oal_uint32 *pul_chip_ver);
/************************  1102  DEVICE********************************************/
#define HAL_DEVICE_LEVEL_FUNC_EXTERN
extern oal_void hi1102_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_set_hw);
extern oal_void hi1102_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device,oal_uint8 uc_destroy_netbuf);
extern oal_void hi1102_al_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_device);

extern oal_void hi1102_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1102_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_tx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1102_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_free_rx_isr_list(oal_dlist_head_stru  *pst_rx_isr_list);
extern oal_void hi1102_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);

extern oal_void hi1102_tx_fill_basic_ctrl_dscr(hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu);
extern oal_void hi1102_tx_ctrl_dscr_link(hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1102_get_tx_dscr_next(hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next);
extern oal_void hi1102_tx_ctrl_dscr_unlink(hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1102_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1102_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1102_tx_set_dscr_modify_mac_header_length(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length);
extern oal_void hi1102_tx_set_dscr_seqno_sw_generate(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate);
extern oal_void hi1102_tx_get_size_dscr(oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size);
extern oal_void hi1102_tx_get_vap_id(hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id);
extern oal_void hi1102_tx_get_dscr_ctrl_one_param(hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param);
extern oal_void hi1102_tx_get_dscr_seq_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num);
extern oal_void hi1102_tx_get_dscr_tx_cnt(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count);
extern oal_void hi1102_tx_dscr_get_rate3(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_rate);
extern oal_void hi1102_tx_set_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status);
extern oal_void hi1102_tx_get_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status);
extern oal_void  hi1102_tx_get_dscr_send_rate_rank(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank);
extern oal_void hi1102_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id);
extern oal_void hi1102_tx_get_dscr_ba_ssn(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn);
extern oal_void hi1102_tx_get_dscr_ba_bitmap(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap);
extern oal_void hi1102_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr);
extern oal_void hi1102_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum);
extern oal_void hi1102_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len);
#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_void hi1102_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode);
#endif
extern oal_void hi1102_rx_get_info_dscr(oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics);
extern oal_void hi1102_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap);
extern oal_void hi1102_rx_get_netbuffer_addr_dscr(oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr);
extern oal_void hi1102_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type);
extern oal_void hi1102_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num);
extern oal_void hi1102_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr);
extern oal_void hi1102_dump_tx_dscr(oal_uint32 *pul_tx_dscr);
extern oal_void hi1102_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val);
extern oal_void hi1102_reg_write16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 us_val);
extern oal_void hi1102_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_uint32 hi1102_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void  hi1102_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_dscr_num);
extern oal_void hi1102_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                     oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg);
extern oal_void hi1102_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1102_initialize_machw(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1102_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1102_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num);
#endif
extern oal_void hi1102_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1102_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_PHY_PERFORMANCE
extern oal_void hi1102_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac);
#endif

extern oal_void hi1102_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain);
extern oal_void hi1102_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size);
extern oal_void hi1102_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                        oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para);
extern oal_void hi1102_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                             oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para);
extern oal_void hi1102_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag);
extern oal_void hi1102_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write);
extern oal_void hi1102_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read);
extern oal_void hi1102_reset_init(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_reset_destroy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1102_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1102_reset_reg_dma_save(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1102_reset_reg_dma_restore(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1102_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_initialize_phy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain);
extern oal_void hi1102_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device);
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
extern oal_void hi1102_set_rf_custom_reg(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_void hi1102_cali_send_func(oal_uint8* puc_cali_data, oal_uint16 us_frame_len, oal_uint16 us_remain);
extern oal_void hi1102_psm_rf_sleep (hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
extern oal_void hi1102_psm_rf_awake (hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg);
extern oal_void hi1102_initialize_soc(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status);
extern oal_void hi1102_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1102_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state);
extern oal_void hi1102_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1102_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1102_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1102_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param);
extern oal_void hi1102_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device);

extern oal_void hi1102_get_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1102_add_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1102_del_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id);

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_void hi1102_dpd_cali_func(oal_uint8 u_functype, oal_uint32* pul_status, oal_uint32* hi1102_dpd_cal_data_read, oal_uint32* hi1102_dpd_cal_data_write);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void hi1102_set_proxysta_enable(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable);
#endif
extern oal_void hi1102_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol);
extern oal_void hi1102_register_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                           hal_alg_noify_enum_uint8 en_alg_notify,p_hal_alg_isr_func p_func);
extern oal_void hi1102_unregister_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                             hal_alg_noify_enum_uint8 en_alg_notify);
extern oal_void hi1102_register_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type, p_hal_gap_isr_func p_func);
extern oal_void hi1102_unregister_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type);
extern oal_void hi1102_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg);
extern oal_void hi1102_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status);
extern oal_void hi1102_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1102_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1102_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val);
extern oal_void hi1102_reg_info16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 *pus_val);
extern oal_void hi1102_get_all_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_val);
extern oal_void hi1102_get_ampdu_bytes(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes);
extern oal_void hi1102_get_rx_err_count(hal_to_dmac_device_stru* pst_hal_device,
                                        oal_uint32* pul_cnt1,
                                        oal_uint32* pul_cnt2,
                                        oal_uint32* pul_cnt3,
                                        oal_uint32* pul_cnt4,
                                        oal_uint32* pul_cnt5,
                                        oal_uint32* pul_cnt6);
extern oal_void hi1102_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type);
extern oal_void hi1102_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_non_frame_mgmt_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_pmf_crypto(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_crypto);
extern oal_void hi1102_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr);
extern oal_void hi1102_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
extern oal_void hi1102_disable_ce(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1102_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr);
extern oal_void hi1102_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx);
extern oal_void hi1102_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1102_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
extern oal_void hi1102_tx_get_dscr_phy_mode_one(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_phy_mode_one);
extern oal_void hi1102_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index);
extern oal_void hi1102_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
#endif
extern oal_void hi1102_get_rate_80211g_table(oal_void **pst_rate);
extern oal_void hi1102_get_rate_80211g_num(oal_uint32 *pst_data_num);
extern oal_void hi1102_get_hw_addr(oal_uint8 *puc_addr);
extern oal_void hi1102_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period);
extern oal_void hi1102_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period);
extern oal_void hi1102_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1102_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1102_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1102_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void  hi1102_set_improve_ce_threshold(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_val);
extern oal_void hi1102_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info);
extern oal_void hi1102_update_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param);
extern oal_void hi1102_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void  hi1102_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp);
extern oal_void  hi1102_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode);
extern oal_void  hi1102_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code,
            oal_int8  *pac_tpc_level_table, oal_uint8 uc_tpc_level_num,
            oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table,
            oal_int16 *pas_other_gain_table,wlan_channel_band_enum_uint8 en_freq_band);

extern oal_void  hi1102_get_bcn_rate(hal_to_dmac_vap_stru *pst_hal_vap,oal_uint8 *puc_data_rate);
extern oal_void  hi1102_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_bcn_phy_tx_mode(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_tpc_code);
extern oal_void hi1102_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1102_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param);
extern oal_void hi1102_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2);
extern oal_void hi1102_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2);
extern oal_void hi1102_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void hi1102_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
      oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
      oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void  hi1102_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1102_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx);
extern oal_void  hi1102_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate,
       oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx);

#endif
extern oal_void hi1102_irq_affinity_init(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_core_id);

#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hi1102_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix);
extern oal_void hi1102_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix);
extern oal_void hi1102_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1102_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1102_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1102_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1102_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time);
extern oal_void hi1102_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration);
extern oal_void hi1102_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_group_id);
extern oal_void hi1102_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1102_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1102_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1102_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);
extern oal_void hi1102_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1102_set_mu_aid_matrix_info(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_aid, oal_uint8  *p_matrix);
extern oal_void hi1102_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1102_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1102_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);

#endif
extern oal_void hi1102_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_mac_addr,oal_uint8 uc_lut_index);

extern oal_void hi1102_enable_smart_antenna_gpio_set_default_antenna(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_delete_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_set_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1102_get_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
extern oal_void hi1102_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_device, oal_int32 l_reg_val);
extern oal_void hi1102_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val);
extern oal_void hi1102_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint32 us_obss_dur);
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
extern oal_void hi1102_set_counter1_clear(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1102_get_txrx_frame_time(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * ul_reg_val);
extern oal_void hi1102_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable);
#endif
extern oal_void hi1102_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis);

#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_void hi1102_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *l_ed_high_reg_val);
extern oal_void hi1102_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val);
extern oal_void hi1102_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val);
extern oal_void hi1102_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val);
extern oal_void hi1102_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val);
#endif
extern oal_void  hi1102_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle);
extern oal_void hi1102_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void  hi1102_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval);
extern oal_void  hi1102_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count);
extern oal_void hi1102_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1102_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1102_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period);
extern oal_void hi1102_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val);
#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1102_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void hi1102_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
#endif
#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1102_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1102_set_txop_ps_partial_aid(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint16 us_partial_aid);
#endif
extern oal_void hi1102_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para);
extern oal_void hi1102_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para, oal_void* pst_wow_para);
extern oal_void hi1102_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en);
extern oal_void hi1102_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl);
extern oal_void hi1102_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num);

#ifdef _PRE_DEBUG_MODE
extern oal_void hi1102_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_get_cali_data(hal_to_dmac_device_stru * pst_hal_device);
#endif
extern oal_void hi1102_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect);
extern oal_void hi1102_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
extern oal_void hi1102_al_tx_set_agc_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
#endif

#ifdef _PRE_WLAN_PHY_PLL_DIV
extern oal_void hi1102_rf_set_freq_skew(oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[]);
#endif
extern oal_void hi1102_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth);
extern oal_void hi1102_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1102_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value);
extern oal_void hi1102_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value);

#ifdef _PRE_WLAN_ASIC_RF_TEST
extern oal_void hi1102_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
#endif

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void hi1102_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
extern oal_void hi1102_get_pwr_comp_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tx_ratio, oal_int16 * ps_pwr_comp_val);
extern oal_void hi1102_over_temp_handler(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1102_agc_threshold_handle(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_rssi);

#endif

extern oal_void hi1102_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val);
extern oal_void hi1102_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
extern oal_void  hi1102_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value);
extern oal_void  hi1102_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device);

#define HAL_VAP_LEVEL_FUNC_EXTERN
extern oal_void hi1102_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo);
extern oal_void hi1102_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo);
extern oal_void hi1102_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo);
extern oal_void hi1102_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo);
extern oal_void hi1102_vap_send_beacon_pkt(hal_to_dmac_vap_stru *pst_hal_vap, hal_beacon_tx_params_stru *pst_params);
extern oal_void hi1102_vap_set_beacon_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_rate);
extern oal_void hi1102_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate);


extern oal_void hi1102_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr);
extern oal_void hi1102_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);

extern oal_void hi1102_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);
extern oal_void hi1102_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo);
extern oal_void hi1102_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                            wlan_wme_ac_type_enum_uint8   en_ac,
                                            oal_uint8                     uc_aifs);
extern oal_void  hi1102_vap_set_machw_aifsn_ac_wfa(hal_to_dmac_vap_stru         *pst_hal_vap,
                                      wlan_wme_ac_type_enum_uint8   en_ac,
                                      oal_uint8                     uc_aifs,
                                      wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1102_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ac_type);
extern oal_void  hi1102_vap_set_edca_machw_cw_wfa(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmaxmin, oal_uint8 uc_ac_type, wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1102_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ac_type);
#if 0
extern oal_void hi1102_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1102_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1102_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
#endif
extern oal_void hi1102_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);


extern oal_void hi1102_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1102_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1102_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1102_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1102_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1102_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1102_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1102_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable);
extern oal_void hi1102_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value);
extern oal_void hi1102_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value);
extern oal_void hi1102_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1102_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void  hi1102_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period);
extern oal_void  hi1102_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);

extern oal_void  hi1102_sta_tsf_restore(hal_to_dmac_vap_stru   *pst_hal_vap);
extern oal_void  hi1102_sta_tsf_save(hal_to_dmac_vap_stru   *pst_hal_vap, oal_bool_enum_uint8 en_need_restore);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void  hi1102_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window);
extern oal_void  hi1102_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_bool_enum_uint8     en_suspend_enable);
#endif
extern oal_void hi1102_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte);
extern oal_void hi1102_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period);
extern oal_void hi1102_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period);
extern oal_void hi1102_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count);
extern oal_void  hi1102_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *uc_dtim_count);
extern oal_void  hi1102_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count);
extern oal_void  hi1102_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim);
extern oal_void hi1102_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1102_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val);
extern oal_void hi1102_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1102_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type);
extern oal_void hi1102_cfg_rsp_dyn_bw(oal_bool_enum_uint8 en_set, wlan_bw_cap_enum_uint8 en_dyn_bw);
extern oal_void hi1102_get_cfg_rsp_rate_mode(oal_uint32 *pul_rsp_rate_cfg_mode);
extern oal_void hi1102_set_rsp_rate(oal_uint32 ul_rsp_rate_val);

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void  hi1102_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status);

extern oal_void hi1102_pm_wlan_servid_register(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint32 *pul_ret);

extern oal_void hi1102_pm_wlan_servid_unregister(hal_to_dmac_vap_stru  *pst_hal_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_void hi1102_coex_irq_en_set(oal_uint8 uc_intr_en);
extern oal_void hi1102_coex_sw_irq_clr_set(oal_uint8 uc_irq_clr);
extern oal_void hi1102_coex_sw_irq_set(oal_uint8 uc_irq_en);
extern oal_void hi1102_coex_sw_irq_status_get(oal_uint8 *uc_irq_status);
extern oal_void hi1102_get_btcoex_abort_qos_null_seq_num(oal_uint32 *ul_qosnull_seq_num);
extern oal_void hi1102_get_btcoex_occupied_period(oal_uint16 *ul_occupied_period);
extern oal_void hi1102_get_btcoex_pa_status(oal_uint32 *ul_pa_status);
extern oal_void hi1102_update_btcoex_btble_status(hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32 hi1102_btcoex_init(oal_void *p_arg);
extern oal_void hi1102_get_btcoex_statistic(oal_bool_enum_uint8 en_enable_abort_stat);
extern oal_uint32 hi1102_mpw_soc_write_reg(oal_uint32 ulQuryRegAddrTemp, oal_uint16 usQuryRegValueTemp);
extern oal_void hi1102_btcoex_update_ap_beacon_count(oal_uint32 *pul_beacon_count);
extern oal_void hi1102_btcoex_post_event(hal_to_dmac_device_stru *pst_hal_device, hal_dmac_misc_sub_type_enum_uint8 uc_sub_type);
extern oal_void hi1102_btcoex_have_small_ampdu(hal_to_dmac_device_stru *pst_hal_base_device, oal_uint32 *pul_have_ampdu);
extern oal_void hi1102_btcoex_process_bt_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_print);
#ifdef _PRE_WLAN_FEATURE_LTECOEX
extern oal_void  hi1102_ltecoex_req_mask_ctrl(oal_uint16 req_mask_ctrl);
#endif
extern oal_void hi1102_set_btcoex_abort_null_buff_addr(oal_uint32 ul_abort_null_buff_addr);
extern oal_void hi1102_set_btcoex_abort_qos_null_seq_num(oal_uint32 ul_qosnull_seq_num);
extern oal_void hi1102_set_btcoex_hw_rx_priority_dis(oal_uint8 uc_hw_rx_prio_dis);
extern oal_void hi1102_set_btcoex_hw_priority_en(oal_uint8 uc_hw_prio_en);
extern oal_void hi1102_set_btcoex_occupied_period(oal_uint16 ul_occupied_period);
extern oal_void hi1102_btcoex_get_rf_control(oal_uint16 ul_occupied_period, oal_uint32 *pul_wlbt_mode_sel, oal_uint16 us_wait_cnt);
extern oal_void hi1102_set_btcoex_sw_all_abort_ctrl(oal_uint8 uc_sw_abort_ctrl);
extern oal_void hi1102_set_btcoex_sw_priority_flag(oal_uint8 uc_sw_prio_flag);
extern oal_void hi1102_set_btcoex_soc_gpreg0(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
extern oal_void hi1102_set_btcoex_soc_gpreg1(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
extern oal_void hi1102_dual_antenna_switch(oal_uint8 uc_value, oal_uint8 uc_by_alg, oal_uint32 *pul_result);
extern oal_void hi1102_dual_antenna_switch_at(oal_uint8 uc_value, oal_uint32 *pul_result);
extern oal_void hi1102_dual_antenna_check(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_result);
extern oal_void hi1102_dual_antenna_init(oal_void);
#endif
extern oal_void hi1102_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_keyid);
#ifdef _PRE_WLAN_DFT_STAT
extern oal_void  hi1102_dft_get_machw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_machw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_set_phy_stat_node(hal_to_dmac_device_stru * pst_hal_device,oam_stats_phy_node_idx_stru *pst_phy_node_idx);
extern oal_void  hi1102_dft_get_phyhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_phyhw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_get_rfhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_rfhw_stat, oal_uint32 *pul_len);
extern oal_void hi1102_dft_get_sochw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint16 *pst_sochw_stat, oal_uint32 *pul_len);
extern oal_void  hi1102_dft_print_machw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_print_phyhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_print_rfhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1102_dft_report_all_reg_state(hal_to_dmac_device_stru   *pst_hal_device);

#endif
extern oal_void hi1102_set_lte_gpio_mode(oal_uint32 ul_mode_value);

extern oal_void hi1102_cfg_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_get_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_revert_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1102_check_test_value_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value, oal_uint32 *pul_result);
extern oal_void hi1102_config_always_rx(hal_to_dmac_device_stru *pst_hal_device_base, oal_uint8 uc_switch);

extern oal_uint32 hi1102_rf_get_pll_div_idx(wlan_channel_band_enum_uint8 en_band,oal_uint8  uc_channel_idx,
                                            wlan_channel_bandwidth_enum_uint8 en_bandwidth,oal_uint8  *puc_pll_div_idx);

#elif ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))

/************************  1103  CHIP********************************************/
#define HAL_CHIP_LEVEL_FUNC_EXTERN
extern oal_void hi1103_get_chip_version(hal_to_dmac_chip_stru *pst_hal_chip, oal_uint32 *pul_chip_ver);
/************************  1103  DEVICE********************************************/
#define HAL_DEVICE_LEVEL_FUNC_EXTERN
extern oal_void hi1103_rx_init_dscr_queue(hal_to_dmac_device_stru *pst_device,oal_uint8 uc_set_hw);
extern oal_void hi1103_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device,oal_uint8 uc_destroy_netbuf);
extern oal_void hi1103_al_rx_init_dscr_queue(hal_to_dmac_device_stru * pst_device);

extern oal_void hi1103_al_rx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1103_tx_init_dscr_queue(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1103_tx_destroy_dscr_queue(hal_to_dmac_device_stru * pst_device);
extern oal_void hi1103_init_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1103_free_rx_isr_list(oal_dlist_head_stru  *pst_rx_isr_list);
extern oal_void hi1103_destroy_hw_rx_isr_list(hal_to_dmac_device_stru *pst_device);

extern oal_void hi1103_tx_fill_basic_ctrl_dscr(hal_tx_dscr_stru * p_tx_dscr, hal_tx_mpdu_stru *pst_mpdu);
extern oal_void hi1103_tx_ctrl_dscr_link(hal_tx_dscr_stru *pst_tx_dscr_prev, hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1103_get_tx_dscr_next(hal_tx_dscr_stru *pst_tx_dscr, hal_tx_dscr_stru **ppst_tx_dscr_next);
extern oal_void hi1103_tx_ctrl_dscr_unlink(hal_tx_dscr_stru *pst_tx_dscr);
extern oal_void hi1103_tx_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1103_tx_non_ucast_data_set_dscr(hal_to_dmac_device_stru     *pst_hal_device,
                                                   hal_tx_dscr_stru            *pst_tx_dscr,
                                                   hal_tx_txop_feature_stru   *pst_txop_feature,
                                                   hal_tx_txop_alg_stru       *pst_txop_alg,
                                                   hal_tx_ppdu_feature_stru   *pst_ppdu_feature);
extern oal_void hi1103_tx_set_dscr_modify_mac_header_length(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_mac_header_length);
extern oal_void hi1103_tx_set_dscr_seqno_sw_generate(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_sw_seqno_generate);
extern oal_void hi1103_tx_get_size_dscr(oal_uint8 us_msdu_num, oal_uint32 * pul_dscr_one_size, oal_uint32 * pul_dscr_two_size);
extern oal_void hi1103_tx_get_vap_id(hal_tx_dscr_stru * pst_tx_dscr, oal_uint8 *puc_vap_id);
extern oal_void hi1103_tx_get_dscr_ctrl_one_param(hal_tx_dscr_stru * pst_tx_dscr, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one_param);
extern oal_void hi1103_tx_get_dscr_seq_num(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_seq_num);
extern oal_void hi1103_tx_get_dscr_tx_cnt(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_tx_count);
extern oal_void hi1103_tx_dscr_get_rate3(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_rate);
extern oal_void hi1103_tx_set_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 uc_status);
extern oal_void hi1103_tx_get_dscr_status(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_status);
extern oal_void  hi1103_tx_get_dscr_send_rate_rank(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_send_rate_rank);
extern oal_void hi1103_tx_get_dscr_chiper_type(hal_tx_dscr_stru *pst_tx_dscr, oal_uint8 *puc_chiper_type, oal_uint8 *puc_chiper_key_id);
extern oal_void hi1103_tx_get_dscr_ba_ssn(hal_tx_dscr_stru *pst_tx_dscr, oal_uint16 *pus_ba_ssn);
extern oal_void hi1103_tx_get_dscr_ba_bitmap(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_ba_bitmap);
extern oal_void hi1103_tx_put_dscr(hal_to_dmac_device_stru * pst_hal_device, hal_tx_queue_type_enum_uint8 en_tx_queue_type, hal_tx_dscr_stru *past_tx_dscr);
extern oal_void hi1103_get_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * pul_status, oal_uint8 uc_qnum);
extern oal_void hi1103_tx_get_ampdu_len(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_ampdu_len);
#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_void hi1103_tx_get_protocol_mode(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_protocol_mode);
#endif
extern oal_void hi1103_rx_get_info_dscr(oal_uint32 *pul_rx_dscr, hal_rx_ctl_stru * pst_rx_ctl, hal_rx_status_stru * pst_rx_status, hal_rx_statistic_stru * pst_rx_statistics);
extern oal_void hi1103_get_hal_vap(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_vap_id, hal_to_dmac_vap_stru **ppst_hal_vap);
extern oal_void hi1103_rx_get_netbuffer_addr_dscr(oal_uint32 *pul_rx_dscr, oal_netbuf_stru ** ppul_mac_hdr_addr);
extern oal_void hi1103_rx_show_dscr_queue_info(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_rx_dscr_type);
extern oal_void hi1103_rx_sync_invalid_dscr(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_dscr, oal_uint8 en_queue_num);
extern oal_void hi1103_rx_free_dscr_list(hal_to_dmac_device_stru * pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint32 *pul_rx_dscr);
extern oal_void hi1103_dump_tx_dscr(oal_uint32 *pul_tx_dscr);
extern oal_void hi1103_reg_write(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 ul_val);
extern oal_void hi1103_reg_write16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 us_val);
extern oal_void hi1103_set_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_machw_rx_buff_addr(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_uint32 hi1103_set_machw_rx_buff_addr_sync(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_dscr, hal_rx_dscr_queue_id_enum_uint8 en_queue_num);
extern oal_void  hi1103_rx_add_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_rx_dscr_queue_id_enum_uint8 en_queue_num, oal_uint16 us_rx_dscr_num);
extern oal_void hi1103_set_machw_tx_suspend(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_machw_tx_resume(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_reset_phy_machw(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type,
                                     oal_uint8 sub_mod,oal_uint8 uc_reset_phy_reg,oal_uint8 uc_reset_mac_reg);
extern oal_void hi1103_disable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_machw_phy_and_pa(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1103_initialize_machw(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_freq_band(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1103_set_bandwidth_mode(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void hi1103_set_upc_data(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1103_set_tpc_params(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_channel_num);
#endif
extern oal_void hi1103_process_phy_freq(hal_to_dmac_device_stru *pst_hal_device);

extern oal_void hi1103_set_primary_channel(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_channel_num,
                oal_uint8                uc_band,
                oal_uint8                uc_channel_idx,
                wlan_channel_bandwidth_enum_uint8 en_bandwidth);
#ifdef _PRE_WLAN_PHY_PERFORMANCE
extern oal_void hi1103_set_phy_tx_scale(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_2g_11ac);
#endif

extern oal_void hi1103_set_rx_multi_ant(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rx_chain);
extern oal_void hi1103_add_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8 uc_lut_index, oal_uint8 *puc_dst_addr, oal_uint8 uc_tid,
                oal_uint16 uc_seq_no, oal_uint8 uc_win_size);
extern oal_void hi1103_remove_machw_ba_lut_entry(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1103_get_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                        oal_uint32* pst_addr_h,oal_uint32* pst_addr_l,oal_uint32* pst_ba_para);
extern oal_void hi1103_restore_machw_ba_params(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_index,
                                             oal_uint32 ul_addr_h,oal_uint32 ul_addr_l,oal_uint32 ul_ba_para);
extern oal_void hi1103_machw_seq_num_index_update_per_tid(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint8 uc_qos_flag);
extern oal_void hi1103_set_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 ul_val_write);
extern oal_void hi1103_get_tx_sequence_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index,oal_uint8 uc_tid, oal_uint8 uc_qos_flag,oal_uint32 *pst_val_read);
extern oal_void hi1103_reset_init(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_reset_destroy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_reset_reg_restore(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1103_reset_reg_save(hal_to_dmac_device_stru * pst_hal_device,hal_reset_hw_type_enum_uint8 en_type);
extern oal_void hi1103_reset_reg_dma_save(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1103_reset_reg_dma_restore(hal_to_dmac_device_stru* pst_hal,oal_uint8* uc_dmach0,oal_uint8* uc_dmach1,oal_uint8* uc_dmach2);
extern oal_void hi1103_disable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_machw_ack_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_disable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_machw_cts_trans(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_initialize_phy(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_radar_config_reg(hal_to_dmac_device_stru *pst_hal_device, hal_dfs_radar_type_enum_uint8 en_dfs_domain);
extern oal_void hi1103_initialize_rf_sys(hal_to_dmac_device_stru * pst_hal_device);
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
extern oal_void hi1103_set_rf_custom_reg(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_void hi1103_cali_send_func(oal_uint8* puc_cali_data, oal_uint16 us_frame_len, oal_uint16 us_remain);
extern oal_void hi1103_psm_rf_sleep (hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_restore_reg);
extern oal_void hi1103_psm_rf_awake (hal_to_dmac_device_stru  *pst_hal_device,oal_uint8 uc_restore_reg);
extern oal_void hi1103_initialize_soc(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_get_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_status);
extern oal_void hi1103_clear_mac_int_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1103_get_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_state);
extern oal_void hi1103_clear_mac_error_int_status(hal_to_dmac_device_stru *pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1103_unmask_mac_error_init_status(hal_to_dmac_device_stru * pst_hal_device, hal_error_state_stru *pst_status);
extern oal_void hi1103_unmask_mac_init_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_status);
extern oal_void hi1103_show_irq_info(hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_param);
extern oal_void hi1103_dump_all_rx_dscr(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_clear_irq_stat(hal_to_dmac_device_stru * pst_hal_device);

extern oal_void hi1103_get_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1103_add_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 uc_mac_vap_id, hal_to_dmac_vap_stru ** ppst_hal_vap);
extern oal_void hi1103_del_vap(hal_to_dmac_device_stru *pst_hal_device, wlan_vap_mode_enum_uint8 vap_mode, oal_uint8 vap_id);

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_void hi1103_dpd_cali_func(oal_uint8 u_functype, oal_uint32* pul_status, oal_uint32* hi1103_dpd_cal_data_read, oal_uint32* hi1103_dpd_cal_data_write);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_void hi1103_set_proxysta_enable(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable);
#endif
extern oal_void hi1103_config_eifs_time(hal_to_dmac_device_stru *pst_hal_device, wlan_protocol_enum_uint8 en_protocol);
extern oal_void hi1103_register_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                           hal_alg_noify_enum_uint8 en_alg_notify,p_hal_alg_isr_func p_func);
extern oal_void hi1103_unregister_alg_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,
                                             hal_alg_noify_enum_uint8 en_alg_notify);
extern oal_void hi1103_register_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type,p_hal_alg_isr_func p_func);
extern oal_void hi1103_unregister_gap_isr_hook(hal_to_dmac_device_stru *pst_hal_device, hal_isr_type_enum_uint8 en_isr_type);
extern oal_void hi1103_one_packet_start(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_cfg_stru *pst_cfg);
extern oal_void hi1103_one_packet_stop(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_one_packet_get_status(struct tag_hal_to_dmac_device_stru *pst_hal_device, hal_one_packet_status_stru *pst_status);
extern oal_void hi1103_reset_nav_timer(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_clear_hw_fifo(struct tag_hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_mask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1103_unmask_interrupt(struct tag_hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_offset);
extern oal_void hi1103_reg_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint32 *pul_val);
extern oal_void hi1103_reg_info16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_addr, oal_uint16 *pus_val);
extern oal_void hi1103_get_all_tx_q_status(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_val);
extern oal_void hi1103_get_ampdu_bytes(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 *pul_tx_bytes, oal_uint32 *pul_rx_bytes);
extern oal_void hi1103_get_rx_err_count(hal_to_dmac_device_stru* pst_hal_device,
                                        oal_uint32* pul_cnt1,
                                        oal_uint32* pul_cnt2,
                                        oal_uint32* pul_cnt3,
                                        oal_uint32* pul_cnt4,
                                        oal_uint32* pul_cnt5,
                                        oal_uint32* pul_cnt6);
extern oal_void hi1103_show_fsm_info(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_mac_error_msg_report(hal_to_dmac_device_stru *pst_hal_device, hal_mac_error_type_enum_uint8 en_error_type);
extern oal_void hi1103_en_soc_intr(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_disable_beacon_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_non_frame_filter(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_disable_monitor_mode(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_pmf_crypto(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_crypto);
extern oal_void hi1103_ce_add_key(hal_to_dmac_device_stru *pst_hal_device,hal_security_key_stru *pst_security_key,oal_uint8 *puc_addr);
extern oal_void hi1103_ce_del_key(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
extern oal_void hi1103_disable_ce(hal_to_dmac_device_stru *pst_device);
extern oal_void hi1103_ce_add_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx,oal_uint8 * puc_addr);
extern oal_void hi1103_ce_del_peer_macaddr(hal_to_dmac_device_stru *pst_hal_device,oal_uint8 uc_lut_idx);
extern oal_void hi1103_set_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1103_get_rx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1103_set_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
extern oal_void hi1103_get_tx_pn(hal_to_dmac_device_stru *pst_hal_device,hal_pn_lut_cfg_stru* pst_pn_lut_cfg);
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
extern oal_void hi1103_tx_get_dscr_phy_mode_one(hal_tx_dscr_stru *pst_tx_dscr, oal_uint32 *pul_phy_mode_one);
extern oal_void hi1103_tx_get_ra_lut_index(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru *pst_dscr, oal_uint8 *puc_ra_lut_index);
extern oal_void hi1103_init_ptk_tx_pn(hal_to_dmac_device_stru *pst_hal_device, hal_security_key_stru *pst_security_key);
#endif
extern oal_void hi1103_get_rate_80211g_table(oal_void **pst_rate);
extern oal_void hi1103_get_rate_80211g_num(oal_uint32 *pst_data_num);
extern oal_void hi1103_get_hw_addr(oal_uint8 *puc_addr);
extern oal_void hi1103_enable_ch_statics(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1103_set_ch_statics_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_period);
extern oal_void hi1103_set_ch_measurement_period(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_period);
extern oal_void hi1103_get_ch_statics_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1103_get_ch_measurement_result(hal_to_dmac_device_stru *pst_hal_device, hal_ch_statics_irq_event_stru *pst_ch_statics);
extern oal_void hi1103_enable_radar_det(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1103_enable_sigB(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1103_enable_improve_ce(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_enable);
extern oal_void hi1103_set_acc_symb_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_num);
extern oal_void  hi1103_set_improve_ce_threshold(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_val);
extern oal_void hi1103_get_radar_det_result(hal_to_dmac_device_stru *pst_hal_device, hal_radar_det_event_stru *pst_radar_info);
extern oal_void hi1103_update_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1103_set_rts_rate_params(hal_to_dmac_device_stru *pst_hal_device, hal_cfg_rts_tx_param_stru *pst_hal_rts_tx_param);
extern oal_void hi1103_set_rts_rate_selection_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_rts_rate_select_mode);
#ifdef _PRE_WLAN_FEATURE_TPC
extern oal_void  hi1103_get_rf_temp(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_cur_temp);
extern oal_void  hi1103_set_tpc_init_rate_dac_lpf_table(oal_uint8 *pauc_rate_pow_table_2G, oal_uint8 *pauc_rate_pow_table_5G,
                        oal_uint8 *pauc_mode_len, oal_uint8 uc_pow_mode);
extern oal_void  hi1103_set_dac_lpc_pa_upc_level(oal_uint8 uc_dac_lpf_code,
            oal_int8  *pac_tpc_level_table, oal_uint8 uc_tpc_level_num,
            oal_uint8 *pauc_dac_lpf_pa_code_table, oal_int16 *pas_upc_gain_table,
            oal_int16 *pas_other_gain_table,wlan_channel_band_enum_uint8 en_freq_band);

extern oal_void  hi1103_get_bcn_rate(hal_to_dmac_vap_stru *pst_hal_vap,oal_uint8 *puc_data_rate);
extern oal_void  hi1103_get_spec_frm_rate(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_bcn_phy_tx_mode(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_tpc_code);
extern oal_void hi1103_set_spec_frm_phy_tx_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_band, oal_uint8 uc_subband_idx);
extern oal_void hi1103_set_tpc_ctrl_reg_param(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tpc_ctrl_param);
extern oal_void hi1103_get_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 *pul_phy_tx_up_down_time_reg,  oal_uint32 *pul_phy_rx_up_down_time_reg,
            oal_uint32 *pul_rf_reg_wr_delay1, oal_uint32 *pul_rf_reg_wr_delay2);
extern oal_void hi1103_set_tpc_delay_reg_param(hal_to_dmac_device_stru *pst_hal_device,
            oal_uint32 ul_phy_tx_up_down_time_reg,  oal_uint32 ul_phy_rx_up_down_time_reg,
            oal_uint32 ul_rf_reg_wr_delay1, oal_uint32 ul_rf_reg_wr_delay2);
extern oal_void hi1103_get_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
        oal_uint16 *pus_dac_val, oal_uint16 *pus_pa_val, oal_uint16 *pus_lpf_val,
        oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void hi1103_set_tpc_rf_reg_param(hal_to_dmac_device_stru *pst_hal_device,
      oal_uint16 us_dac_val, oal_uint16 us_pa_val, oal_uint16 us_lpf_val,
      oal_uint16* paus_2g_upc_val, oal_uint16* paus_5g_upc_val, oal_uint8 uc_chain_idx);
extern oal_void  hi1103_set_tpc_phy_reg_param(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void  hi1103_get_subband_index(wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel_num, oal_uint8 *puc_subband_idx);
extern oal_void  hi1103_set_dpd_by_power(hal_tx_txop_rate_params_stru *pst_rate,
       oal_uint8 uc_power_level, oal_uint32 ul_dpd_configure, oal_uint32 ul_rate_idx);

#endif
extern oal_void hi1103_irq_affinity_init(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 ul_core_id);

#ifdef _PRE_WLAN_FEATURE_TXBF
extern oal_void hi1103_set_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_matrix);
extern oal_void hi1103_get_legacy_matrix_buf_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_matrix);
extern oal_void hi1103_set_vht_report_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1103_set_vht_report_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1103_set_ndp_rate(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rate);
extern oal_void hi1103_set_ndp_phy_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_phy_mode);
extern oal_void hi1103_set_ndp_max_time(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ndp_time);
extern oal_void hi1103_set_ndpa_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_ndpa_duration);
extern oal_void hi1103_set_ndp_group_id(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_group_id);
extern oal_void hi1103_set_ndp_partial_aid(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1103_set_phy_legacy_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_set_phy_txbf_legacy_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_set_phy_pilot_bf_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_set_ht_buffer_num(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 ul_reg_value);
extern oal_void hi1103_set_ht_buffer_step(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 ul_reg_value);
extern oal_void hi1103_set_ht_buffer_pointer(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_delete_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1103_set_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1103_get_txbf_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);
extern oal_void hi1103_set_h_matrix_timeout(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_set_dl_mumimo_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1103_set_mu_aid_matrix_info(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_aid, oal_uint8  *p_matrix);
extern oal_void hi1103_set_sta_membership_status_63_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 value);
extern oal_void hi1103_set_sta_membership_status_31_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1103_set_sta_user_p_63_48(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1103_set_sta_user_p_47_32(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1103_set_sta_user_p_31_16(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
extern oal_void hi1103_set_sta_user_p_15_0(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);

#endif
extern oal_void hi1103_set_peer_lut_info(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 *puc_mac_addr,oal_uint8 uc_lut_index);

extern oal_void hi1103_enable_smart_antenna_gpio_set_default_antenna(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_delete_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1103_set_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint16 ul_reg_value);
extern oal_void hi1103_get_smart_antenna_value(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index, oal_uint32*  pst_reg_value);

#ifdef _PRE_WLAN_FEATURE_ANTI_INTERF
extern oal_void hi1103_set_weak_intf_rssi_th(hal_to_dmac_device_stru *pst_device, oal_int32 l_reg_val);
extern oal_void hi1103_set_agc_unlock_min_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_tx_reg_val, oal_int32 l_rx_reg_val);
extern oal_void hi1103_set_nav_max_duration(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_bss_dur, oal_uint32 us_obss_dur);
#endif
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT
extern oal_void hi1103_set_counter1_clear(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void hi1103_get_txrx_frame_time(hal_to_dmac_device_stru * pst_hal_device, oal_uint32 * ul_reg_val);
extern oal_void hi1103_set_mac_clken(hal_to_dmac_device_stru *pst_hal_device, oal_bool_enum_uint8 en_wctrl_enable);
#endif
extern oal_void hi1103_get_mac_statistics_data(hal_to_dmac_device_stru *pst_hal_device, hal_mac_key_statis_info_stru *pst_mac_key_statis);

#ifdef _PRE_WLAN_FEATURE_CCA_OPT
extern oal_void hi1103_get_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *l_ed_high_reg_val);
extern oal_void hi1103_set_ed_high_th(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_ed_high_20_reg_val, oal_int32 l_ed_high_40_reg_val);
extern oal_void hi1103_enable_sync_error_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_cnt_reg_val);
extern oal_void hi1103_get_sync_error_cnt(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_reg_val);
extern oal_void hi1103_set_sync_err_counter_clear(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_get_cca_reg_th(hal_to_dmac_device_stru *pst_hal_device, oal_int8 *ac_reg_val);
#endif
extern oal_void  hi1103_set_soc_lpm(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_soc_set_enum_uint8 en_type ,oal_uint8 uc_on_off,oal_uint8 uc_pcie_idle);
extern oal_void hi1103_set_psm_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1103_set_psm_wakeup_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void  hi1103_set_psm_listen_interval(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval);
extern oal_void  hi1103_set_psm_listen_interval_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_interval_count);
extern oal_void hi1103_set_psm_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1103_set_psm_ext_tbtt_offset(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_offset);
extern oal_void  hi1103_set_psm_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_period);
extern oal_void hi1103_set_psm_tsf_ctrl(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_ctrl_val);
#if defined(_PRE_WLAN_FEATURE_SMPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1103_set_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_mode);
extern oal_void hi1103_get_smps_mode(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
#endif
#if defined(_PRE_WLAN_FEATURE_TXOPPS) || defined(_PRE_WLAN_CHIP_TEST)
extern oal_void hi1103_set_txop_ps_enable(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1103_set_txop_ps_condition1(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1103_set_txop_ps_condition2(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_on_off);
extern oal_void hi1103_set_txop_ps_partial_aid(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint16 us_partial_aid);
#endif
extern oal_void hi1103_set_wow_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_set_bitmap,hal_wow_param_stru* pst_para);
extern oal_void hi1103_set_lpm_state(hal_to_dmac_device_stru *pst_hal_device,hal_lpm_state_enum_uint8 uc_state_from, hal_lpm_state_enum_uint8 uc_state_to,oal_void* pst_para, oal_void* pst_wow_para);
extern oal_void hi1103_disable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_enable_machw_edca(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_set_tx_abort_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_abort_en);
extern oal_void hi1103_set_coex_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_mac_ctrl, oal_uint32 ul_rf_ctrl);
extern oal_void hi1103_get_hw_version(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_hw_vsn, oal_uint32 *pul_hw_vsn_data,oal_uint32 *pul_hw_vsn_num);

#ifdef _PRE_DEBUG_MODE
extern oal_void hi1103_get_all_reg_value(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_get_cali_data(hal_to_dmac_device_stru * pst_hal_device);
#endif
extern oal_void hi1103_set_tx_dscr_field(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_data, hal_rf_test_sect_enum_uint8 en_sect);
extern oal_void hi1103_rf_test_disable_al_tx(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_rf_test_enable_al_tx(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
extern oal_void hi1103_al_tx_set_agc_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_value);
#endif

#ifdef _PRE_WLAN_PHY_PLL_DIV
extern oal_void hi1103_rf_set_freq_skew(oal_uint16 us_idx, oal_uint16 us_chn, oal_int16 as_corr_data[]);
#endif
extern oal_void hi1103_set_daq_mac_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pul_addr, oal_uint16 us_unit_len, oal_uint16 us_unit_num, oal_uint16 us_depth);
extern oal_void hi1103_set_daq_phy_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_reg_value);
extern oal_void hi1103_set_daq_en(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_reg_value);
extern oal_void hi1103_get_daq_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *pul_reg_value);

#ifdef _PRE_WLAN_ASIC_RF_TEST
extern oal_void hi1103_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
#endif

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void hi1103_set_dac_lpf_gain(hal_to_dmac_device_stru *pst_hal_device,
                                    oal_uint8 en_band, oal_uint8 en_bandwidth,oal_uint8 en_protocol_mode,oal_uint8 en_rate);
extern oal_void hi1103_get_pwr_comp_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_tx_ratio, oal_int16 * ps_pwr_comp_val);
extern oal_void hi1103_over_temp_handler(hal_to_dmac_device_stru *pst_hal_device);
extern oal_void hi1103_agc_threshold_handle(hal_to_dmac_device_stru *pst_hal_device, oal_int8 c_rssi);

#endif

extern oal_void hi1103_set_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_rx_filter_val);
extern oal_void hi1103_get_rx_filter(hal_to_dmac_device_stru *pst_hal_device, oal_uint32* pst_reg_value);
extern oal_void  hi1103_set_beacon_timeout_val(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value);
extern oal_void  hi1103_psm_clear_mac_rx_isr(hal_to_dmac_device_stru *pst_hal_device);

#define HAL_VAP_LEVEL_FUNC_EXTERN
extern oal_void hi1103_vap_tsf_get_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_lo);
extern oal_void hi1103_vap_tsf_set_32bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_lo);
extern oal_void hi1103_vap_tsf_get_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_tsf_hi, oal_uint32 *pul_tsf_lo);
extern oal_void hi1103_vap_tsf_set_64bit(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_tsf_hi, oal_uint32 ul_tsf_lo);
extern oal_void hi1103_vap_send_beacon_pkt(hal_to_dmac_vap_stru *pst_hal_vap, hal_beacon_tx_params_stru *pst_params);
extern oal_void hi1103_vap_set_beacon_rate(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_beacon_rate);
extern oal_void hi1103_vap_beacon_suspend(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_vap_beacon_resume(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_vap_set_machw_prot_params(hal_to_dmac_vap_stru *pst_hal_vap, hal_tx_txop_rate_params_stru *pst_phy_tx_mode, hal_tx_txop_per_rate_params_union *pst_data_rate);


extern oal_void hi1103_vap_set_macaddr(hal_to_dmac_vap_stru * pst_hal_vap, oal_uint8 *puc_mac_addr);
extern oal_void hi1103_vap_set_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);

extern oal_void hi1103_vap_clr_opmode(hal_to_dmac_vap_stru *pst_hal_vap, wlan_vap_mode_enum_uint8 en_vap_mode);
extern oal_void hi1103_vap_set_machw_aifsn_all_ac(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               uc_bk,
                oal_uint8               uc_be,
                oal_uint8               uc_vi,
                oal_uint8               uc_vo);
extern oal_void hi1103_vap_set_machw_aifsn_ac(hal_to_dmac_vap_stru         *pst_hal_vap,
                                            wlan_wme_ac_type_enum_uint8   en_ac,
                                            oal_uint8                     uc_aifs);
extern oal_void  hi1103_vap_set_machw_aifsn_ac_wfa(hal_to_dmac_vap_stru         *pst_hal_vap,
                                      wlan_wme_ac_type_enum_uint8   en_ac,
                                      oal_uint8                     uc_aifs,
                                      wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1103_vap_set_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin, oal_uint8 uc_ac_type);
extern oal_void  hi1103_vap_set_edca_machw_cw_wfa(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmaxmin, oal_uint8 uc_ac_type, wlan_wme_ac_type_enum_uint8   en_wfa_lock);
extern oal_void hi1103_vap_get_edca_machw_cw(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin, oal_uint8 uc_ac_type);
#if 0
extern oal_void hi1103_vap_set_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1103_vap_get_machw_cw_bk(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1103_vap_set_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1103_vap_get_machw_cw_be(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1103_vap_set_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1103_vap_get_machw_cw_vi(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
extern oal_void hi1103_vap_set_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_cwmax, oal_uint8 uc_cwmin);
extern oal_void hi1103_vap_get_machw_cw_vo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_cwmax, oal_uint8 *puc_cwmin);
#endif
extern oal_void hi1103_vap_set_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);


extern oal_void hi1103_vap_get_machw_txop_limit_bkbe(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1103_vap_set_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1103_vap_get_machw_txop_limit_vivo(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1103_vap_set_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_be, oal_uint16 us_bk);
extern oal_void hi1103_vap_get_machw_edca_bkbe_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_be, oal_uint16 *pus_bk);
extern oal_void hi1103_vap_set_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_vo, oal_uint16 us_vi);
extern oal_void hi1103_vap_get_machw_edca_vivo_lifetime(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_vo, oal_uint16 *pus_vi);
extern oal_void hi1103_vap_set_machw_prng_seed_val_all_ac(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_vap_start_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_bool_enum_uint8 en_dbac_enable);
extern oal_void hi1103_vap_read_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_value);
extern oal_void hi1103_vap_write_tbtt_timer(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_value);
extern oal_void hi1103_vap_set_machw_tsf_disable(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_vap_set_machw_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void hi1103_vap_update_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_beacon_period);
extern oal_void  hi1103_vap_get_beacon_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_beacon_period);
extern oal_void  hi1103_vap_set_noa(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);

extern oal_void  hi1103_sta_tsf_restore(hal_to_dmac_vap_stru   *pst_hal_vap);
extern oal_void  hi1103_sta_tsf_save(hal_to_dmac_vap_stru   *pst_hal_vap, oal_bool_enum_uint8 en_need_restore);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_void  hi1103_vap_set_ops(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_uint8               en_ops_ctrl,
                oal_uint8               uc_ct_window);
extern oal_void  hi1103_vap_enable_p2p_absent_suspend(
                hal_to_dmac_vap_stru   *pst_hal_vap,
                oal_bool_enum_uint8     en_suspend_enable);
#endif
extern oal_void hi1103_set_sta_bssid(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *puc_byte);
extern oal_void hi1103_set_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_period);
extern oal_void hi1103_get_sta_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 *pul_dtim_period);
extern oal_void hi1103_set_sta_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint32 ul_dtim_count);
extern oal_void  hi1103_get_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 *uc_dtim_count);
extern oal_void  hi1103_set_psm_dtim_count(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_count);
extern oal_void  hi1103_set_psm_dtim_period(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint8 uc_dtim_period,
                                                oal_uint8 uc_listen_intvl_to_dtim_times, oal_bool_enum_uint8 en_receive_dtim);
extern oal_void hi1103_enable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_disable_sta_tsf_tbtt(hal_to_dmac_vap_stru *pst_hal_vap);
extern oal_void hi1103_mwo_det_enable_mac_counter(hal_to_dmac_device_stru *pst_hal_device, oal_int32 l_enable_reg_val);
extern oal_void hi1103_tx_enable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1103_tx_disable_peer_sta_ps_ctrl(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_lut_index);
extern oal_void hi1103_cfg_slottime_type(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 ul_slottime_type);
#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
extern oal_void  hi1103_get_hw_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint32 *ul_cali_check_hw_status);

extern oal_void hi1103_pm_wlan_servid_register(hal_to_dmac_vap_stru  *pst_hal_vap, oal_uint32 *pul_ret);

extern oal_void hi1103_pm_wlan_servid_unregister(hal_to_dmac_vap_stru  *pst_hal_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_void hi1103_coex_irq_en_set(oal_uint8 uc_intr_en);
extern oal_void hi1103_coex_sw_irq_clr_set(oal_uint8 uc_irq_clr);
extern oal_void hi1103_coex_sw_irq_set(oal_uint8 uc_irq_en);
extern oal_void hi1103_coex_sw_irq_status_get(oal_uint8 *uc_irq_status);
extern oal_void hi1103_get_btcoex_abort_qos_null_seq_num(oal_uint32 *ul_qosnull_seq_num);
extern oal_void hi1103_get_btcoex_occupied_period(oal_uint16 *ul_occupied_period);
extern oal_void hi1103_get_btcoex_pa_status(oal_uint32 *ul_pa_status);
extern oal_void hi1103_update_btcoex_btble_status(hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32 hi1103_btcoex_init(oal_void *p_arg);
extern oal_void hi1103_get_btcoex_statistic(oal_bool_enum_uint8 en_enable_abort_stat);
extern oal_uint32 hi1103_mpw_soc_write_reg(oal_uint32 ulQuryRegAddrTemp, oal_uint16 usQuryRegValueTemp);
extern oal_void hi1103_btcoex_update_ap_beacon_count(oal_uint32 *pul_beacon_count);
extern oal_void hi1103_btcoex_post_event(hal_to_dmac_device_stru *pst_hal_device, hal_dmac_misc_sub_type_enum_uint8 uc_sub_type);
extern oal_void hi1103_btcoex_have_small_ampdu(hal_to_dmac_device_stru *pst_hal_base_device, oal_uint32 *pul_have_ampdu);
extern oal_void hi1103_btcoex_process_bt_status(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_print);
#ifdef _PRE_WLAN_FEATURE_LTECOEX
extern oal_void  hi1103_ltecoex_req_mask_ctrl(oal_uint16 req_mask_ctrl);
#endif
extern oal_void hi1103_set_btcoex_abort_null_buff_addr(oal_uint32 ul_abort_null_buff_addr);
extern oal_void hi1103_set_btcoex_abort_qos_null_seq_num(oal_uint32 ul_qosnull_seq_num);
extern oal_void hi1103_set_btcoex_hw_rx_priority_dis(oal_uint8 uc_hw_rx_prio_dis);
extern oal_void hi1103_set_btcoex_hw_priority_en(oal_uint8 uc_hw_prio_en);
extern oal_void hi1103_set_btcoex_occupied_period(oal_uint16 ul_occupied_period);
extern oal_void hi1103_btcoex_get_rf_control(oal_uint16 ul_occupied_period, oal_uint32 *pul_wlbt_mode_sel, oal_uint16 us_wait_cnt);
extern oal_void hi1103_set_btcoex_sw_all_abort_ctrl(oal_uint8 uc_sw_abort_ctrl);
extern oal_void hi1103_set_btcoex_sw_priority_flag(oal_uint8 uc_sw_prio_flag);
extern oal_void hi1103_set_btcoex_soc_gpreg0(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
extern oal_void hi1103_set_btcoex_soc_gpreg1(oal_uint8 uc_val, oal_uint16 us_mask, oal_uint8 uc_offset);
#endif

extern oal_void hi1103_tx_get_dscr_iv_word(hal_tx_dscr_stru *pst_dscr, oal_uint32 *pul_iv_ms_word, oal_uint32 *pul_iv_ls_word, oal_uint8 uc_chiper_type, oal_uint8 uc_chiper_keyid);
#ifdef _PRE_WLAN_DFT_STAT
extern oal_void  hi1103_dft_get_machw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_machw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1103_dft_set_phy_stat_node(hal_to_dmac_device_stru * pst_hal_device,oam_stats_phy_node_idx_stru *pst_phy_node_idx);
extern oal_void  hi1103_dft_get_phyhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_phyhw_stat,oal_uint8 us_bank_select, oal_uint32 *pul_len);
extern oal_void  hi1103_dft_get_rfhw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint32 *pst_rfhw_stat, oal_uint32 *pul_len);
extern oal_void hi1103_dft_get_sochw_stat_info(hal_to_dmac_device_stru * pst_hal_device,oal_uint16 *pst_sochw_stat, oal_uint32 *pul_len);
extern oal_void  hi1103_dft_print_machw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1103_dft_print_phyhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1103_dft_print_rfhw_stat(hal_to_dmac_device_stru * pst_hal_device);
extern oal_void  hi1103_dft_report_all_reg_state(hal_to_dmac_device_stru   *pst_hal_device);

#endif
extern oal_void hi1103_set_lte_gpio_mode(oal_uint32 ul_mode_value);

extern oal_void hi1103_cfg_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1103_get_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,
                    oal_uint8 uc_chain_idx, wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1103_revert_cw_signal_reg(hal_to_dmac_device_stru *pst_hal_device,wlan_channel_band_enum_uint8 en_band);
extern oal_void hi1103_check_test_value_reg(hal_to_dmac_device_stru *pst_hal_device, oal_uint16 us_value, oal_uint32 *pul_result);
extern oal_void hi1103_config_always_rx(hal_to_dmac_device_stru *pst_hal_device_base, oal_uint8 uc_switch);
extern oal_uint32 hi1103_rf_get_pll_div_idx(wlan_channel_band_enum_uint8 en_band,oal_uint8  uc_channel_idx,
                                            wlan_channel_bandwidth_enum_uint8 en_bandwidth,oal_uint8  *puc_pll_div_idx);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

