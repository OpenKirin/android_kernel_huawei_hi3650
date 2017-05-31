/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wlan_spec.h
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2014��10��10��
  ����޸�   :
  ��������   : 1103 wlan��Ʒ���궨��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��10��
    ��    ��   : ��־��
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WLAN_SPEC_1103_H__
#define __WLAN_SPEC_1103_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))

/*****************************************************************************
  ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"


/*****************************************************************************
  0.0 ���ƻ���������
*****************************************************************************/
/*���ƻ������Ϊһ���ṹ�壬�������ṩ��������������̬��������Ԥ���������̬*/

/* �����û��������� */
extern oal_uint16   g_us_wlan_assoc_user_max_num;
extern oal_uint32   g_ul_wlan_vap_max_num_per_device;

/*****************************************************************************
  0.1.2 �ȵ���������
*****************************************************************************/
/* �����û��������� ����Proxy STAʱ��ap�������û���Ϊ15���ر�ʱΪ32*/
#define WLAN_ASSOC_USER_MAX_NUM_SPEC        g_us_wlan_assoc_user_max_num

/* ��ΪP2P GO �����������û��� */
#define WLAN_P2P_GO_ASSOC_USER_MAX_NUM_SPEC 4
/*****************************************************************************
  0.5.3 AMSDU����
*****************************************************************************/
#ifdef _PRE_WIFI_DMT
#define WLAN_AMSDU_MAX_NUM                  witp_dmt_get_amsdu_aggr_num()
#else
/* һ��amsdu������ӵ�е�msdu�������� */
#define WLAN_AMSDU_MAX_NUM                  25
#endif

/*****************************************************************************
  0.8.2 STA AP���
*****************************************************************************/
/* ÿ��device֧��vap��������=���ҵ��VAP��Ŀ+����VAP���� */
/* ������:P2P_dev/CL��STAģʽ���ڣ�P2P_GO��APģʽ����
    1)AP ģʽ:  2��ap + 1������vap
    2)STA ģʽ: 3��sta + 1������vap
    3)STA+P2P����ģʽ:  1��sta + 1��P2P_dev + 1��P2P_GO/Client + 1������vap
    4)STA+Proxy STA����ģʽ:  1��sta + 1��proxy STA + 1������vap
*/
#define WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC        g_ul_wlan_vap_max_num_per_device    /* VAP��������*/

/* ����BOARD֧�ֵ�����VAP��Ŀ */
#define WLAN_VAP_SUPPOTR_MAX_NUM_SPEC       (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)   /* 5������18�� */

/* ����BOARD֧�ֵ����ҵ��VAP����Ŀ */
#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_SPEC     (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * (WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC -1))

#define WLAN_MAX_MULTI_USER_NUM_SPEC              (WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_SPEC)


/*****************************************************************************
  1.0 WLANоƬ��Ӧ��spec
*****************************************************************************/
/* ÿ��board֧��chip������������ƽ̨ */
/* ÿ��chip֧��device������������ƽ̨ */
/* ���֧�ֵ�MACӲ���豸��������ƽ̨ */


/*****************************************************************************
  1.3 oam��ص�spec
*****************************************************************************/
/*oam ����ƽ̨ */

/*****************************************************************************
  1.4 mem��Ӧ��spec
*****************************************************************************/
/*****************************************************************************
  1.4.1 �ڴ�ع��
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.2 �����������ڴ��������Ϣ
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.3 �������֡�ڴ��������Ϣ
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */


/*****************************************************************************
  1.4.4 ��������֡�ڴ��������Ϣ
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.5 �����ڴ��������Ϣ
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.6 �¼��ṹ���ڴ��
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.7 �û��ڴ��
*****************************************************************************/
/*****************************************************************************
  1.4.8 MIB�ڴ��  TBD :���ո��ӳصĿռ��С��������Ҫ���¿���
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */

/*****************************************************************************
  1.4.9 netbuf�ڴ��  TBD :���ո��ӳصĿռ��С��������Ҫ���¿���
*****************************************************************************/

/*�ڴ� spec ����ƽ̨ */


/*****************************************************************************
  1.4.9.1 sdt netbuf�ڴ��
*****************************************************************************/
/*�ڴ� spec ����ƽ̨ */


/*****************************************************************************
 1.5 frw��ص�spec
*****************************************************************************/
/*�¼����� spec ����ƽ̨ */



/*****************************************************************************
  2 �궨�壬�����DR����һ��
*****************************************************************************/
/*****************************************************************************
  2.1 ����Э��/���������Э������spec
*****************************************************************************/
/*****************************************************************************
  2.1.1 ɨ���STA ����
*****************************************************************************/
/* TBD һ�ο���ɨ������BSS���������������Ժϲ�*/
#define WLAN_SCAN_REQ_MAX_BSSID                 2
#define WLAN_SCAN_REQ_MAX_SSID                  8

/* TBD ɨ���ӳ�,us δʹ�ã���ɾ��*/
#define WLAN_PROBE_DELAY_TIME                   10

/* ɨ��ʱ����С���ŵ�פ��ʱ�䣬��λms��������������*/
#define WLAN_DEFAULT_SCAN_MIN_TIME              110
/* ɨ��ʱ�������ŵ�פ��ʱ�䣬��λms��������������*/
#define WLAN_DEFAULT_SCAN_MAX_TIME              500

/*TBD  һ��device����¼��ɨ�赽�����BSS���������٣���Ҫ����200 */
#define WLAN_MAX_SCAN_BSS_NUM                   32
/*TBD  һ���ŵ��¼�¼ɨ�赽�����BSS���� �����٣���Ҫ����200 */
#define WLAN_MAX_SCAN_BSS_PER_CH                8
/* SSID��󳤶�, +1Ϊ\0Ԥ���ռ� */
#define WLAN_SSID_MAX_LEN                   (32 + 1)

#define WLAN_DEFAULT_FG_SCAN_COUNT_PER_CHANNEL         2       /* ǰ��ɨ��ÿ�ŵ�ɨ����� */
#define WLAN_DEFAULT_BG_SCAN_COUNT_PER_CHANNEL         1       /* ����ɨ��ÿ�ŵ�ɨ����� */
#define WLAN_DEFAULT_SEND_PROBE_REQ_COUNT_PER_CHANNEL  1       /* ÿ���ŵ�ɨ�跢��probe req֡�Ĵ��� */

#define WLAN_DEFAULT_MAX_TIME_PER_SCAN                 (3 * 1500)  /* ɨ���Ĭ�ϵ����ִ��ʱ�䣬������ʱ�䣬����ʱ���� */

/*TBD ɨ��ʱ��������ɨ�趨ʱʱ�䣬��λms��������������*/
#ifdef _PRE_WIFI_DMT
#define WLAN_DEFAULT_ACTIVE_SCAN_TIME           40
#define WLAN_DEFAULT_PASSIVE_SCAN_TIME          800
#else
#define WLAN_DEFAULT_ACTIVE_SCAN_TIME           20
#define WLAN_DEFAULT_PASSIVE_SCAN_TIME          60
#endif

#define WLAN_LONG_ACTIVE_SCAN_TIME              40             /* ָ��SSIDɨ���������3��ʱ,1��ɨ�賬ʱʱ��Ϊ40ms */

/*****************************************************************************
  2.1.1 STA��������
*****************************************************************************/
/* STA��ͬʱ���������AP����*/
#define WLAN_ASSOC_AP_MAX_NUM               2

/* TBD�������ӳ٣���λms��������Ҫ�޶�*/
#ifdef _PRE_WIFI_DMT
#define WLAN_JOIN_START_TIMEOUT                 10000
#define WLAN_AUTH_TIMEOUT                       500
#define WLAN_ASSOC_TIMEOUT                      500
#else
#define WLAN_JOIN_START_TIMEOUT                 10000
#define WLAN_AUTH_TIMEOUT                       300
#define WLAN_ASSOC_TIMEOUT                      300
#endif

/*****************************************************************************
  2.1.2 �ȵ���������
*****************************************************************************/
/* �����õ��������û��� */
#define WLAN_MAX_ASSOC_USER_CFG             200
/* �����û��������� */
#define WLAN_ASSOC_USER_MAX_NUM_LIMIT       8
//#define WLAN_ASSOC_USER_MAX_NUM             32                                      /* �����û��������� */

/* ��Ծ�û�������������ƽ̨ */

/* ��Ծ�û�����λͼ���� */
#define WLAN_ACTIVE_USER_IDX_BMAP_LEN       ((WLAN_ACTIVE_USER_MAX_NUM + 7)>> 3)
/* �����û�����λͼ���� */
#define WLAN_ASSOC_USER_IDX_BMAP_LEN       ((WLAN_ASSOC_USER_MAX_NUM_SPEC + 7)>> 3)
/* �����õ�RA LUT IDX */
#define WLAN_INVALID_RA_LUT_IDX             WLAN_ACTIVE_USER_MAX_NUM

/*
 * The 802.11 spec says at most 2007 stations may be
 * associated at once.  For most AP's this is way more
 * than is feasible so we use a default of 128.  This
 * number may be overridden by the driver and/or by
 * user configuration.
 */
#define WLAN_AID_MAX                        2007
#define WLAN_AID_DEFAULT                    128

/* ��Ծ��ʱ���������� */
#define WLAN_USER_ACTIVE_TRIGGER_TIME           1000
/* �ϻ���ʱ���������� */
#define WLAN_USER_AGING_TRIGGER_TIME            5000
/* ��λms */
#define WLAN_USER_ACTIVE_TO_INACTIVE_TIME       5000

#ifdef _PRE_WIFI_DMT
#define WLAN_AP_USER_AGING_TIME                  witp_dmt_get_user_aging_time()
#else
/* ��λms */
#define WLAN_AP_USER_AGING_TIME                 (300 * 1000)    /* AP �û��ϻ�ʱ�� 300S */
#define WLAN_P2PGO_USER_AGING_TIME              (60 * 1000)     /* GO �û��ϻ�ʱ�� 60S */
#endif

/* AP keepalive����,��λms */
#define WLAN_AP_KEEPALIVE_TRIGGER_TIME          (15 * 1000)       /* keepalive��ʱ���������� */
#define WLAN_AP_KEEPALIVE_INTERVAL              (WLAN_AP_KEEPALIVE_TRIGGER_TIME * 4)   /* ap����keepalive null֡��� */
#define WLAN_GO_KEEPALIVE_INTERVAL              (25*1000) /* P2P GO����keepalive null֡���  */

/* STA keepalive����,��λms */
#define WLAN_STA_KEEPALIVE_TIME                 (25*1000) /* wlan0����keepalive null֡���,ͬ1101 keepalive 25s */
#define WLAN_CL_KEEPALIVE_TIME                  (20*1000) /* P2P CL����keepalive null֡���,����CL��GO pvb����,P2P cl 20s */

/*****************************************************************************
  2.1.3 STA��������
*****************************************************************************/

#define WLAN_LINKLOSS_OFFSET_11H                5  /* ���ŵ�ʱ���ӳ� */
#define WLAN_LINKLOSS_MIN_THRESHOLD             10 /* linkloss������С���ֵ */



/* Beacon Interval���� */
/* max beacon interval, ms */
#define WLAN_BEACON_INTVAL_MAX              3500
/* min beacon interval */
#define WLAN_BEACON_INTVAL_MIN              40
/* min beacon interval */
#define WLAN_BEACON_INTVAL_DEFAULT          100
/*AP IDLE״̬��beacon intervalֵ*/
#define WLAN_BEACON_INTVAL_IDLE             1000


/*****************************************************************************
  2.1.6 ����ģʽ����
*****************************************************************************/
/*TBD RTS�������ޣ�ʵ�ʿ�ɾ��*/
#define WLAN_RTS_DEFAULT                    512
#define WLAN_RTS_MIN                        1
#define WLAN_RTS_MAX                        2346

/*****************************************************************************
  2.1.7 ��Ƭ����
*****************************************************************************/
/* Fragmentation limits */
/* default frag threshold */
#define WLAN_FRAG_THRESHOLD_DEFAULT         1544
/* min frag threshold */
#define WLAN_FRAG_THRESHOLD_MIN             200 /* Ϊ�˱�֤��Ƭ��С��16: (1472(�·���󳤶�)/16)+36(����֡���֡ͷ) = 128  */
/* max frag threshold */
#define WLAN_FRAG_THRESHOLD_MAX             2346
/*****************************************************************************
  2.1.14 �������ʹ���
*****************************************************************************/
/* ������ز��� */
/* һ��Э�飬һ��Ƶ���µ�������ʸ��� */
#define WLAN_RATE_MAXSIZE                   35
/* ��¼֧�ֵ����� */
#define WLAN_SUPP_RATES                         8
/* ���ڼ�¼ɨ�赽��ap֧�ֵ����������� */
#define WLAN_MAX_SUPP_RATES                     12
/* ÿ���û�֧�ֵ�������ʼ����� */
#define HAL_TX_RATE_MAX_NUM                4

/*****************************************************************************
  2.1.16 TXBF����
*****************************************************************************/
/* TXBF��beamformer��������*/
#define WLAN_TXBF_NSS_SPEC		2
#define WLAN_TXBF_SU_BFMER_DEFAULT_VALUE      0
#define WLAN_BFER_ACTIVED		OAL_FALSE
#define WLAN_TXSTBC_ACTIVED		OAL_FALSE
#define WLAN_MU_BFEE_ACTIVED	OAL_TRUE

/*****************************************************************************
  2.2 ����Э��/����MAC ��Э������spec
*****************************************************************************/
/*****************************************************************************
  2.2.8 �����빦��
*****************************************************************************/
/* ������������ */
#define WLAN_MAX_RC_NUM                         20
/* ������λͼ���� */
#define WLAN_RC_BMAP_WORDS                      2
/* wifi 5G 2.4Gȫ���ŵ����� */
#define WLAN_MAX_CHANNEL_NUM                    (29 + 14)

/*****************************************************************************
  2.2.9 WMM����
*****************************************************************************/
/* EDCA���� */
/*STA����WLAN_EDCA_XXX����ͬWLAN_QEDCA_XXX */
/*
#define WLAN_QEDCA_TABLE_INDEX_MIN           1
#define WLAN_QEDCA_TABLE_INDEX_MAX           4*/

#define WLAN_QEDCA_TABLE_CWMIN_MIN           1
#define WLAN_QEDCA_TABLE_CWMIN_MAX           10
#define WLAN_QEDCA_TABLE_CWMAX_MIN           1
#define WLAN_QEDCA_TABLE_CWMAX_MAX           10
#define WLAN_QEDCA_TABLE_AIFSN_MIN           2
#define WLAN_QEDCA_TABLE_AIFSN_MAX           15
#define WLAN_QEDCA_TABLE_TXOP_LIMIT_MIN      1
#define WLAN_QEDCA_TABLE_TXOP_LIMIT_MAX      65535
#define WLAN_QEDCA_TABLE_MSDU_LIFETIME_MAX   500

/* TID��������ƽ̨SPEC */

/* Ĭ�ϵ���������ҵ���TID */
#define WLAN_TID_FOR_DATA                   0

/* ���ն��еĸ��� ��HAL_RX_DSCR_QUEUE_ID_BUTT��� */
#define HAL_RX_QUEUE_NUM                3
/* ���Ͷ��еĸ��� */
#define HAL_TX_QUEUE_NUM                5
/* �洢Ӳ�������ϱ���������������Ŀ(ping pongʹ��) */
#define HAL_HW_RX_DSCR_LIST_NUM         2


/*****************************************************************************
  2.2.10 Э�����STA�๦��
*****************************************************************************/
/* PSM���Թ��*/
/*TBD 1*/
/* default DTIM period */
#define WLAN_DTIM_DEFAULT                   3

/* DTIM Period���� */
/* beacon interval�ı��� */
#define WLAN_DTIM_PERIOD_MAX                255
#define WLAN_DTIM_PERIOD_MIN                1

/*****************************************************************************
  2.2.11 Э�����AP�๦��
*****************************************************************************/

/*****************************************************************************
  2.3 У׼����spec
*****************************************************************************/
#ifdef _PRE_WLAN_PHY_PLL_DIV
/* ֧���ֶ����÷�Ƶϵ���ĸ��� */
#define WITP_RF_SUPP_NUMS                  4
#endif

/*****************************************************************************
  2.4 ��ȫЭ������spec
*****************************************************************************/
#define WLAN_NUM_TK             4
#define WLAN_NUM_IGTK           2
#define WLAN_MAX_IGTK_KEY_INDEX 5
#define WLAN_MAX_WEP_KEY_COUNT  4

/*****************************************************************************
  2.4.7 PMF STA����
*****************************************************************************/
/* SA Query���̼��ʱ��,�ϻ�ʱ�������֮һ*/
#define WLAN_SA_QUERY_RETRY_TIME                (WLAN_AP_USER_AGING_TIME / 3)
/* SA Query���̳�ʱʱ��,С���ϻ�ʱ��*/
#define WLAN_SA_QUERY_MAXIMUM_TIME              (WLAN_SA_QUERY_RETRY_TIME * 3)

/*****************************************************************************
  2.4.9 WPA����
*****************************************************************************/
/* ������صĺ궨�� */
/* Ӳ��MAC ���ȴ�32us�� ����ȴ�40us */
#define HAL_CE_LUT_UPDATE_TIMEOUT          4



/*****************************************************************************
  2.5 ��������spec
*****************************************************************************/
/*****************************************************************************
  2.5.1 ��ȷ�Ϲ���
*****************************************************************************/

#ifdef _PRE_WIFI_DMT
/* ��RSP��һ�£��������ĳ��������ʱʱ�� */
#define WLAN_ADDBA_TIMEOUT                      10000
#define WLAN_TX_PROT_TIMEOUT                    60000
#else
#define WLAN_ADDBA_TIMEOUT                      500
#define WLAN_TX_PROT_TIMEOUT                    6000
#endif

/* TBD RX BA LUT�����������޶�Ϊ2*/
/* ֧�ֵĽ���ba���������� */
#define WLAN_MAX_RX_BA                      4

/* ֧�ֵķ���ba���������� */
#define WLAN_MAX_TX_BA                      2

/*****************************************************************************
  2.5.2 AMPDU����
*****************************************************************************/
#define WLAN_AMPDU_RX_BUFFER_SIZE       64  /* AMPDU���ն˽��ջ�������buffer size�Ĵ�С */
#define WLAN_AMPDU_RX_BA_LUT_WSIZE      64  /* AMPDU���ն�������дBA RX LUT���win size,
                                               Ҫ����ڵ���WLAN_AMPDU_RX_BUFFER_SIZE */

#define WLAN_AMPDU_TX_MAX_NUM           32  /* AMPDU���Ͷ����ۺ���MPDU���� */
#define WLAN_AMPDU_TX_MAX_BUF_SIZE      64  /* ���Ͷ˵�buffer size */

#define WLAN_AMPDU_TX_SCHD_STRATEGY     2   /* 02���ۺ�����Ϊ���ڴ�С��һ�� */

/*TBD �����޶�Ϊ2*/
#define HAL_MAX_BA_LUT_SIZE                32
/*TBD �����޶�Ϊ2*/
#define HAL_MAX_AMPDU_LUT_SIZE             128

/*TBD �����޶�Ϊ2*/
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define HAL_PROXYSTA_MAX_BA_LUT_SIZE    16
#endif

/*****************************************************************************
  2.5.3 AMSDU����
*****************************************************************************/
#define AMSDU_ENABLE_ALL_TID                0xFF
/* amsdu����msdu����󳤶� */
#define WLAN_MSDU_MAX_LEN                   128
/* 1103 spec amsdu��󳤶ȣ���ӦWLAN_LARGE_NETBUF_SIZE��������һ��buffer���� */
#define WLAN_AMSDU_FRAME_MAX_LEN            7935

/* >= WLAN_AMSDU_MAX_NUM/2  */
#define WLAN_DSCR_SUBTABEL_MAX_NUM          1

/*****************************************************************************
  2.5.6 С���Ż�
*****************************************************************************/
/* ����֡����  */
#define HAL_RX_MGMT_FRAME_LEN              WLAN_MGMT_NETBUF_SIZE
/* �̰����� */
/*�̰����л������������,�ȹص�*/
//#define HAL_RX_SMALL_FRAME_LEN             WLAN_SHORT_NETBUF_SIZE
#define HAL_RX_SMALL_FRAME_LEN             180

/* ���������������ĺ궨�� */
/* С�����ݽ��������������������������� */
#define HAL_SMALL_RX_MAX_BUFFS             52
/* TBD 32 ��ͨ���ȼ����������������������������� 32*2*3(amsduռ��buf����Ŀ) */
#define HAL_NORMAL_RX_MAX_BUFFS            24
/* TBD 4 �����ȼ�����������������������������:ȡ���ڲ����û���(32) */
#define HAL_HIGH_RX_MAX_BUFFS              4

#define HAL_NORMAL_RX_MAX_RX_OPT_BUFFS     54
/* ��ͨ���ȼ��������Ż���� */

/*****************************************************************************
  2.5.7 �Զ���Ƶ
*****************************************************************************/
/*δ�����ۺ�ʱpps����*/
#define NO_BA_PPS_VALUE_0              (0)
#define NO_BA_PPS_VALUE_1              (500)
#define NO_BA_PPS_VALUE_2              (1000)
#define NO_BA_PPS_VALUE_3              (1500)
/*mate7���*/
/*pps����       CPU��Ƶ����     DDR��Ƶ����*/
/*mate7 pps����*/
#define PPS_VALUE_0              (0)
#define PPS_VALUE_1              (1000)
#define PPS_VALUE_2              (8000)
#define PPS_VALUE_3              (16000)
/*mate7 CPU��Ƶ����*/
#define CPU_MIN_FREQ_VALUE_0              (403200)
#define CPU_MIN_FREQ_VALUE_1              (604800)
#define CPU_MIN_FREQ_VALUE_2              (806400)
#define CPU_MIN_FREQ_VALUE_3              (1305600)
/*mate7 DDR��Ƶ����*/
#define DDR_MIN_FREQ_VALUE_0              (0)
#define DDR_MIN_FREQ_VALUE_1              (3456)
#define DDR_MIN_FREQ_VALUE_2              (6403)
#define DDR_MIN_FREQ_VALUE_3              (9216)
/*****************************************************************************
  2.6 �㷨����spec
*****************************************************************************/
/*****************************************************************************
  2.6.15 TPC����
*****************************************************************************/
/* TPC����DB�� */
#define WLAN_TPC_STEP                       3
/* TBD 23 ����书�ʣ���λdBm */
#define WLAN_MAX_TXPOWER                    30

/*****************************************************************************
  2.6.22 STA P2P��Ƶ����
*****************************************************************************/
/*  ��ٶ��и�������������һ���ŵ�ʱ����ԭ�ŵ��Ϸŵ�Ӳ���������֡��������
��ǰֻ��2������: DBAC �� ����ɨ�� DBACռ��2�����У����0 1; ����ɨ��ռ��һ�������2 */
/*HAL ��ͷ���޶�ΪWLAN*/
#define HAL_TX_FAKE_QUEUE_NUM              3
#define HAL_TX_FAKE_QUEUE_BGSCAN_ID        2
#define HAL_FCS_PROT_MAX_FRAME_LEN         24

/*****************************************************************************
  2.8 �ܹ���̬����spec
*****************************************************************************/
/*****************************************************************************
  2.8.1 оƬ������
*****************************************************************************/
/* RFͨ�������*/
/* ͨ��0 */
#define WITP_RF_CHANNEL_ZERO        0
/* ͨ��1 */
#define WITP_RF_CHANNEL_ONE         1
/* ˫ͨ�� */
#define WITP_RF_CHANNEL_NUMS        1

/* ˫ͨ������ */
#define WITP_TX_CHAIN_DOUBLE        3
/*  ͨ��0 ����*/
#define WITP_TX_CHAIN_ZERO          1
/*  ͨ��1 ����*/
#define WITP_TX_CHAIN_ONE           2

/*оƬ�汾�ѷ���ƽ̨�Ķ��ƻ�*/


/*****************************************************************************
  2.8.2 STA AP���
*****************************************************************************/
#if 0
#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     2
#endif
 /* AP VAP�Ĺ��STA VAP�Ĺ��STA P2P����Ĺ�����ƽ̨*/
/* PROXY STAģʽ��VAP���궨�����ƽ̨ */

/* ÿ��device֧��vap���������ѷ���ƽ̨
*/
//#define WLAN_VAP_MAX_NUM_PER_DEVICE         (WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE + 1)

#define WLAN_HAL_OHTER_BSS_ID                   14   /* ����BSS��ID */
#define WLAN_HAL_OTHER_BSS_UCAST_ID             7    /* ��������bss�ĵ�������֡������֡��ά���� */
#define WLAN_VAP_MAX_ID_PER_DEVICE_LIMIT        5    /* hal�㣬0 1 2 3 4 */
/* MAC�ϱ���tbtt�ж�������ֵ��2��ap��tbtt�ж�(0-1)+3��sta��tbtt�ж�(4-6) */
#define WLAN_MAC_REPORT_TBTT_IRQ_MAX            7
/* ����BOARD֧�ֵ�����device��Ŀ����ƽ̨ */


/* ����BOARD֧�ֵ�����VAP��Ŀ�ѷ���ƽ̨ */

/* ����BOARD֧�ֵ����ҵ��VAP����Ŀ �ѷ���ƽ̨*/


/*****************************************************************************
  2.8.3 �ͳɱ�Լ��
*****************************************************************************/
/* ���������������ĺ궨�� */
/*HAL ��ͷ���޶�ΪWLAN*/
/* ���ն��������������� */
#define HAL_RX_MAX_BUFFS                  (HAL_NORMAL_RX_MAX_BUFFS + HAL_SMALL_RX_MAX_BUFFS + HAL_HIGH_RX_MAX_BUFFS)
/*������������ping pong����*/
#define HAL_HW_MAX_RX_DSCR_LIST_IDX        1
/* ���ڴ洢��������ж������� */
#define HAL_HW_RX_ISR_INFO_MAX_NUMS       (HAL_NORMAL_RX_MAX_BUFFS + HAL_SMALL_RX_MAX_BUFFS)
#define HAL_DOWM_PART_RX_TRACK_MEM         200
#ifdef _PRE_DEBUG_MODE
/* ��������������ɼ�Ϊ��14�У����ڴ�ʱ����������� */
#define HAL_DEBUG_RX_DSCR_LINE            (12 + 2)
#endif

#ifdef _PRE_WLAN_PHY_PERFORMANCE
/* PHY���ܲ���ʹ��֡���� */
    #define HAL_RX_FRAME_LEN               5100
    #define HAL_RX_FRAME_MAX_LEN       8000
#else
/* 80211֡��󳤶�:������Ϊ1600����20�ֽڵ���������ֹӲ������Խ�� */
    #define HAL_RX_FRAME_LEN               WLAN_LARGE_NETBUF_SIZE
    #define HAL_RX_FRAME_MAX_LEN           8000
#endif
/*****************************************************************************
  RX��������̬����
*****************************************************************************/
#define WLAN_PKT_MEM_PKT_OPT_LIMIT   2000
#define WLAN_PKT_MEM_PKT_RESET_LIMIT 500
#define WLAN_PKT_MEM_OPT_TIME_MS     1000
#define WLAN_PKT_MEM_OPT_MIN_PKT_LEN HAL_RX_SMALL_FRAME_LEN

/*****************************************************************************
  2.8.7 ����Ĭ�Ͽ����رն���
*****************************************************************************/
/*TBD Feature��̬��ǰδʹ�ã�����������û��ʹ��*/
#define WLAN_FEATURE_AMPDU_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_AMSDU_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_WME_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_DSSS_CCK_IS_OPEN           OAL_FALSE
#define WLAN_FEATURE_UAPSD_IS_OPEN              OAL_TRUE
#define WLAN_FEATURE_PSM_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_WPA_IS_OPEN                OAL_TRUE
#define WLAN_FEATURE_TXBF_IS_OPEN               OAL_TRUE
#define WLAN_FEATURE_MSDU_DEFRAG_IS_OPEN        OAL_TRUE


/*****************************************************************************
  2.9 WiFiӦ������spec
*****************************************************************************/
/*****************************************************************************
  2.9.4 P2P����
*****************************************************************************/
/* Hi1103 P2P������P2P vap�豸�Ĵ�С����(PER_DEVICE) */
#ifdef _PRE_WLAN_FEATURE_P2P
#define WLAN_MAX_SERVICE_P2P_DEV_NUM          1
#define WLAN_MAX_SERVICE_P2P_GOCLIENT_NUM     1
#define WLAN_MAX_SERVICE_CFG_VAP_NUM          1
#endif

/*****************************************************************************
  2.9.12 ˽�а�ȫ��ǿ
*****************************************************************************/

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define WLAN_BLACKLIST_MAX                  32
#endif

/*****************************************************************************
  2.9.18 Proxy STA����
*****************************************************************************/
/* ÿ��DEVICE֧�ֵ����ҵ��VAP��Ŀ: ����һ��4��AP VAP����������1��AP VAP + 1��STA VAP */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MAX_PROXY_STA_NUM                  15
#define WLAN_STA0_HAL_VAP_ID                    4
#define WLAN_PROXY_STA_START_ID                 16
#define WLAN_PROXY_STA_END_ID                   31
#define WLAN_PROXY_STA_MAX_REP                  2
#endif
/*****************************************************************************
  2.10 MAC FRAME����
*****************************************************************************/
/*****************************************************************************
  2.10.1 ht cap info
*****************************************************************************/
#define HT_GREEN_FILED_DEFAULT_VALUE            0
#define HT_TX_STBC_DEFAULT_VALUE                0
/*****************************************************************************
  2.10.2 vht cap info
*****************************************************************************/
#define VHT_TX_STBC_DEFAULT_VALUE               0

/*****************************************************************************
  2.10.3 RSSI
*****************************************************************************/
#define WLAN_NEAR_DISTANCE_RSSI        (-35)             /*Ĭ�Ͻ������ź�����-35dBm*/
#define WLAN_CLOSE_DISTANCE_RSSI       (-25)             /*����ǰ�����ж�����-25dBm*/
#define WLAN_FAR_DISTANCE_RSSI         (-73)             /*Ĭ��Զ�����ź�����-73dBm*/
#define WLAN_NORMAL_DISTANCE_RSSI_UP   (-42)             /*�ź�ǿ��С��-42dBmʱ������Ϊ�ǳ�������*/
#define WLAN_NORMAL_DISTANCE_RSSI_DOWN (-66)             /*�ź�ǿ�ȴ���-66dBmʱ������Ϊ�Ƿǳ�Զ����*/
#define WLAN_NEAR_DISTANCE_IMPROVE_RSSI_UP      (-40)    /*improve 1*1������,Ҫ��������ж�������Ϊ-44dBm*/
#define WLAN_NEAR_DISTANCE_IMPROVE_RSSI_DOWN    (-48)    /*improve 1*1������,Ҫ��������ж�������Ϊ-50dBm*/


/*****************************************************************************

  2.11 ������ƫ��
*****************************************************************************/
#define WLAN_RX_DSCR_SIZE                       (56)



/*****************************************************************************
  2.12 COEX FEATURE
*****************************************************************************/
#define BTCOEX_RSSI_THRESHOLD               (WLAN_FAR_DISTANCE_RSSI)

#define BTCOEX_RX_WINDOW_SIZE_INDEX_0       (0)
#define BTCOEX_RX_WINDOW_SIZE_INDEX_1       (1)
#define BTCOEX_RX_WINDOW_SIZE_INDEX_2       (2)
#define BTCOEX_RX_WINDOW_SIZE_INDEX_3       (3)
#define BTCOEX_RX_WINDOW_SIZE_INDEX_MAX     (4)

#define BTCOEX_RX_WINDOW_SIZE_LITTLE        (0)
#define BTCOEX_RX_WINDOW_SIZE_LARGE         (1)
#define BTCOEX_RX_WINDOW_SIZE_GRADES        (2)

#define BTCOEX_BT_NUM_OF_ACTIVE_MODE        (3)

#define BTCOEX_RX_WINDOW_SIZE_HOLD          (0)
#define BTCOEX_RX_WINDOW_SIZE_DECREASE      (1)
#define BTCOEX_RX_WINDOW_SIZE_INCREASE      (2)

#define BTCOEX_RX_LOW_RATE_TIME             (5000)
#define BTCOEX_RX_STATISTICS_TIME           (2000)
#define BTCOEX_SCO_CALCULATE_TIME           (500)

#define ALL_MID_PRIO_TIME                   (10)    // 5s / BTCOEX_SCO_CALCULATE_TIME
#define ALL_HIGH_PRIO_TIME                  (4)     // 2s / BTCOEX_SCO_CALCULATE_TIME

#define BTCOEX_RATE_STATE_SL                (3)
#define BTCOEX_RATE_STATE_L                 (2)
#define BTCOEX_RATE_STATE_M                 (1)
#define BTCOEX_RATE_STATE_H                 (0)

#define BTCOEX_RX_COUNT_LIMIT               (128)

#define BTCOEX_MAC_HDR                      (32)

#define BT_POSTPREEMPT_MAX_TIMES            (15)
#define BT_PREEMPT_MAX_TIMES                (1)
#define BT_POSTPREEMPT_TIMEOUT_US           (150)
#define BT_ABORT_RETRY_TIMES_MAX            (10)

#define BT_PREEMPT_TIMEOUT_US               (50)
#define BLE_PREEMPT_TIMEOUT_US              (10)

#define BTCOEX_BT_SCO_DURATION
#define BTCOEX_BT_DATATRANS_DURATION
#define BTCOEX_BT_A2DP_DURATION
#define BTCOEX_BT_DEFAULT_DURATION          (0xFF)

#define BTCOEX_PHY_TXRX_ALL_EN              (0x0000000F)
#define BTCOEX_BT2WIFI_RF_STABLE_TIME_US    (50)

#define BT_WLAN_COEX_UNAVAIL_PAYLOAD_THRES  (8)
#define BT_WLAN_COEX_SMALL_PKT_THRES        (200)
#define BT_WLAN_COEX_SMALL_FIFO_THRES       (1023)

#define BTCOEX_PRIO_TIMEOUT_100MS           (100)
#define BTCOEX_PRIO_TIMEOUT_60MS            (60)

#define OCCUPIED_TIMES                      (3)
#define OCCUPIED_INTERVAL                   (60)
#define OCCUPIED_PERIOD                     (60000)

#define COEX_LINKLOSS_OCCUP_TIMES           (15)
#define COEX_LINKLOSS_OCCUP_PERIOD          (20000)

#endif /* #if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_HOST))*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __WLAN_SPEC_1103_H__ */



