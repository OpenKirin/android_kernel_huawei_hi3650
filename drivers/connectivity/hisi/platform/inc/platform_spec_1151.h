/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : platform_spec_1151.h
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2014��10��10��
  ����޸�   :
  ��������   : 1151 wlan��Ʒ���궨��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��10��
    ��    ��   : ��־��
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PLATFORM_SPEC_1151_H__
#define __PLATFORM_SPEC_1151_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*****************************************************************************
  1.1.1 �汾spec
*****************************************************************************/
/* оƬ�汾 */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510100
#else
/* hi1151V100H */
#define WLAN_CHIP_VERSION_HI1151V100H           0x11510100
#endif
/* hi1151V100L */
#define WLAN_CHIP_VERSION_HI1151V100L           0x11510102

/*���Host��Device�ж���Ԥ���룬1151��Ϊ��Ϊ֡��������ʱԤ���롣�������ṹ�����ĺ�ɾ��*/
#define IS_HOST 1
#define IS_DEVICE 1

/*****************************************************************************
  1.1.2 ��Core��Ӧspec
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    #define WLAN_FRW_MAX_NUM_CORES          2   /* CORE������ */
#else
    #define WLAN_FRW_MAX_NUM_CORES          1
#endif

/*****************************************************************************
  2.1 WLANоƬ��Ӧ��spec
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
#define WLAN_SERVICE_VAP_START_ID_PER_BOARD         2              /* ˫оƬ�£�ҵ��vap id��2��ʼ */
#define WLAN_CHIP_MAX_NUM_PER_BOARD         2                       /* ˫оƬboard��chip���� */
/* ˫оƬ����£�5G��2G��Ӧ��CHIP ID�궨��; ��ͬ��Ƭ��̬��5G��2G��Ӧ��CHIP ID��ͬ */
#if ((_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_VSPM310DMB)\
        ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_WS835DMB))
#define WLAN_DOUBLE_CHIP_5G_ID      0
#define WLAN_DOUBLE_CHIP_2G_ID      1
#else /* Ŀǰ��Ҫ��DMB�嶨�巽ʽ */
#define WLAN_DOUBLE_CHIP_5G_ID      1
#define WLAN_DOUBLE_CHIP_2G_ID      0
#endif
#else
#define WLAN_SERVICE_VAP_START_ID_PER_BOARD         1              /* ��оƬ�£�ҵ��vap id��1��ʼ */
#define WLAN_CHIP_MAX_NUM_PER_BOARD         1                       /* ��оƬboard��chip���� */
/* ��Ϊ��оƬ������chip idʼ�յ���0������hal��������üĴ�����Ҫ����оƬ����2G����5Gҵ���������ѡ����������ֵ
   ͬʱ��������չ�Ļ���Ҳ�Ǹ��ݲ�ͬ��Ʒ������2G��id����0����1 */
#define WLAN_SINGLE_CHIP_2G_ID      0
#define WLAN_SINGLE_CHIP_5G_ID      1
#endif

#define WLAN_DEVICE_MAX_NUM_PER_CHIP        1                       /* ÿ��chip֧��device�����������������ᳬ��8�� */
/* ����BOARD֧�ֵ�����device�� */
#define WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP)

#define WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE      4   /* AP�Ĺ�񣬽�֮ǰ��WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE�޸�*/
#define WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE     1   /* STA�Ĺ�� */
//#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     (OAL_MAX(WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE, WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE)) /* ҵ��VAP���� */

#define WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE     WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE /* ҵ��VAP���� */
#define WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE      1   /* ����VAP���� */
#define WLAN_AP_STA_COEXIST_VAP_NUM             5   /* ap sta����ʱvap��Ŀ 1��STA 4��AP */

/* PROXY STAģʽ��VAP���궨�� */
#define WLAN_PROXY_STA_MAX_NUM_PER_DEVICE             15   /* PROXY STA�ĸ��� */
/* ����device֧�ֵ�����ҵ��VAP��Ŀ */
#define WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE  (WLAN_PROXY_STA_MAX_NUM_PER_DEVICE + 1 + 4)  /* PROXY STAģʽ�����ҵ��VAP����:PROXY STA + 1��ҵ��STA + 4��ҵ��AP */
/* ����device֧�ֵ�����VAP��Ŀ */
#define WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT      (WLAN_CONFIG_VAP_MAX_NUM_PER_DEVICE + WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE) /* 21��:4��ap,1��sta,15��proxysta,1������vap */

/* ����BOARD֧�ֵ�����VAP��Ŀ */
#define WLAN_VAP_SUPPORT_MAX_NUM_LIMIT      (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT)  /* device����*21��:1��ap,1��sta,15��proxysta,1������vap */
//#define WLAN_VAP_SUPPOTR_MAX_NUM            (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE)

/* ����BOARD֧�ֵ����ҵ��VAP����Ŀ */
#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_LIMIT    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT-1)) /* device����*20��:4��ap,1��sta,15��proxysta */
//#define WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM    (WLAN_CHIP_MAX_NUM_PER_BOARD * WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE)

#define WLAN_MULTI_USER_MAX_NUM_LIMIT             (WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM_LIMIT)
//#define WLAN_MAX_MULTI_USER_NUM             (WLAN_SERVICE_VAP_SUPPOTR_MAX_NUM)

#define WLAN_CHIP_DBSC_DEVICE_NUM       1

/*****************************************************************************
  2.2 WLANЭ���Ӧ��spec
*****************************************************************************/

/*****************************************************************************
  2.3 oam��ص�spec
*****************************************************************************/
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) || (_PRE_OS_VERSION_WINDOWS == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "C:\\OAM.log"                   /* WIN32��WINDOWS��,LOG�ļ�Ĭ�ϵı���λ�� */
#elif ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) || (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
#define WLAN_OAM_FILE_PATH      "\\home\\oam.log"               /* LINUX����ϵͳ��,LOG�ļ�Ĭ�ϵı���λ�� */
#endif

/*****************************************************************************
  2.4 mem��Ӧ��spec
*****************************************************************************/
/*****************************************************************************
  2.4.1
*****************************************************************************/

#define WLAN_MEM_MAX_BYTE_LEN               (32100 + 1)   /* �ɷ�������ڴ�鳤�� */
#define WLAN_MEM_MAX_SUBPOOL_NUM            8             /* �ڴ����������ڴ�ظ��� */
#define WLAN_MEM_MAX_USERS_NUM              4             /* ����ͬһ���ڴ������û��� */

/*****************************************************************************
  2.4.2 �����������ڴ��������Ϣ
*****************************************************************************/
#define WLAN_TID_MPDU_NUM_BIT               10
/* ����device����TID�����MPDU�������ƣ��ݶ�1024�����Է�ֹ���û������ȼ����� */
#define WLAN_TID_MPDU_NUM_LIMIT             (1 << WLAN_TID_MPDU_NUM_BIT)

#define WLAN_MEM_SHARED_RX_DSCR_SIZE        64             /*��ʵ�ʽ����������ṹ���Դ�Щ��Ԥ��������Խ������������޸�*/
#define WLAN_MEM_SHARED_RX_DSCR_CNT         (576 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ����512(����֡������) + 64(����֡������) */ /* ע��! ����һ�����ڴ��Ҫ����oal_mem.c���OAL_MEM_BLK_TOTAL_CNT */
#define WLAN_MEM_SHARED_TX_DSCR_SIZE1       128            /*��ʵ�ʷ����������ṹ���Դ�Щ��Ԥ��������Է������������޸�*/
#define WLAN_MEM_SHARED_TX_DSCR_CNT1        ((WLAN_TID_MPDU_NUM_LIMIT * 2) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ����������512 */
#define WLAN_MEM_SHARED_TX_DSCR_SIZE2       256                          /*��ʵ�ʷ����������ṹ���Դ�Щ��Ԥ��������Է������������޸�*/
#define WLAN_MEM_SHARED_TX_DSCR_CNT2        (256 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ����amsdu�������� */

/*****************************************************************************
  2.4.3 �������֡�ڴ��������Ϣ
*****************************************************************************/
#define WLAN_MEM_SHARED_MGMT_PKT_SIZE1      1300
#define WLAN_MEM_SHARED_MGMT_PKT_CNT1       (8 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)

/*****************************************************************************
  2.4.4 ��������֡�ڴ��������Ϣ
*****************************************************************************/
#define WLAN_MEM_SHARED_DATA_PKT_SIZE       44              /* 80211mac֡ͷ��С */
#define WLAN_MEM_SHARED_DATA_PKT_CNT        ((256 + 1024) * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* skb(���յ�֡ͷ����) + ��������������(���͵�֡ͷ����) 768 */

/*****************************************************************************
  2.4.5 �����ڴ��������Ϣ
*****************************************************************************/
#define WLAN_MEM_LOCAL_SIZE1                32
#define WLAN_MEM_LOCAL_CNT1                 (825 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 256(32*8)��dmac_alg_tid_stru + 256��alg_tid_entry_stru + 5���¼�����(NON_RESET_ERR)*/

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define WLAN_MEM_LOCAL_SIZE2                140
#define WLAN_MEM_LOCAL_CNT2                 (800 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* 200(����) */
#else
#define WLAN_MEM_LOCAL_SIZE2                100                                /* proxysta�Ƿ���Ҫ��800���󵽸��࣬������������û��������Ժ��ٶ� */
#define WLAN_MEM_LOCAL_CNT2                 (850 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* �����㷨�ṹ�����ڴ��(CCA�㷨ҪΪÿ���û�����76�ֽ��ڴ�)�������ؽṹ�����ڴ��� */
#endif

#define WLAN_MEM_LOCAL_SIZE3                260             /* �洢hmac_vap_cfg_priv_stru��ÿ��VAPһ�� + �¼����� 14 *�� */
#define WLAN_MEM_LOCAL_CNT3                 (WLAN_VAP_SUPPORT_MAX_NUM_LIMIT + 580)   /* ���������ؽṹ�����ڴ�飬32����¼����������ڴ��� */

#define WLAN_MEM_LOCAL_SIZE4                500
#define WLAN_MEM_LOCAL_CNT4                 (350 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)  /* 64����¼����������ڴ�顢��������alg_smartant_per_user_info_stru�����ڴ��� */

#define WLAN_MEM_LOCAL_SIZE5                2200
#define WLAN_MEM_LOCAL_CNT5                 (150 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* �㷨(TPC/autorate��)�����ڴ�顢���õ�(���ò��ֺ�������Ҫ�Ż�) */

#define WLAN_MEM_LOCAL_SIZE6                9500           /* autorate */
#define WLAN_MEM_LOCAL_CNT6                 (64 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /*  */


/*****************************************************************************
  2.4.6 �¼��ṹ���ڴ��
*****************************************************************************/
#define WLAN_MEM_EVENT_SIZE1                64              /* ע��: �¼��ڴ泤�Ȱ���4�ֽ�IPCͷ���� */
#define WLAN_MEM_EVENT_CNT1                 (180 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_EVENT_SIZE2                512              /* ע��: �¼��ڴ泤�Ȱ���4�ֽ�IPCͷ���� */
#define WLAN_MEM_EVENT_CNT2                 4

#define WLAN_WPS_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32��ʾ�¼�����ռ�õĿռ� */
#ifdef _PRE_WLAN_FEATURE_HILINK
#define WLAN_OKC_IE_MAX_SIZE                WLAN_MEM_EVENT_SIZE2 - 32   /* 32��ʾ�¼�����ռ�õĿռ� */
#endif
/*****************************************************************************
  2.4.7 �û��ڴ��
*****************************************************************************/


/*****************************************************************************
  2.4.8 MIB�ڴ��  TBD :���ո��ӳصĿռ��С��������Ҫ���¿���
*****************************************************************************/
#define WLAN_MEM_MIB_SIZE1                  32000           /* mib�ṹ���С */
#define WLAN_MEM_MIB_CNT1                   ((WLAN_VAP_SUPPORT_MAX_NUM_LIMIT - 1) * 2)    /* ����VAPû��MIB */

/*****************************************************************************
  2.4.9 netbuf�ڴ��  TBD :���ո��ӳصĿռ��С��������Ҫ���¿���
*****************************************************************************/
#define WLAN_MEM_NETBUF_SIZE1               0       /* ��¡��SKB */
#define WLAN_MEM_NETBUF_CNT1                (192 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC) /* ��������֡��AMSDU�����е�ÿ��MSDU��Ӧһ����¡netbuf */

#ifndef _PRE_WLAN_PHY_PERFORMANCE
#define WLAN_MEM_NETBUF_SIZE2               1600    /* 1500 + WLAN_MAX_FRAME_HEADER_LEN(36) + WLAN_HDR_FCS_LENGTH(4) + (����ʧ�ܵĻ�,�����ֶ�Ҳ���ϱ�(20)) */
#define WLAN_MEM_NETBUF_CNT2                (512 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)      /* ����192(��������֡) + 32(���չ���֡) + 32(���͹���֡) */
                                                        /* ���ǽ���wlan2wlanת��������������Ļ�����x2 */
#define WLAN_MEM_NETBUF_SIZE3               2500    /* ���Ƭ�����鱨�ĵ�skb */
#define WLAN_MEM_NETBUF_CNT3                (32 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)       /* ��Ծ�û�ÿ���û�һ�� */

#else
#define WLAN_MEM_NETBUF_SIZE2               5100
#define WLAN_MEM_NETBUF_CNT2                (512 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)

#define WLAN_MEM_NETBUF_SIZE3               5100    /* ���Ƭ�����鱨�ĵ�skb */
#define WLAN_MEM_NETBUF_CNT3                (32 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)       /* ��Ծ�û�ÿ���û�һ�� */
#endif


#define WLAN_MEM_NETBUF_ALIGN               4       /* netbuf���� */
#define WLAN_MEM_ETH_HEADER_LEN             14      /* ��̫��֡ͷ���� */

#define WLAN_LARGE_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2 /* NETBUF�ڴ�س�֡�ĳ��ȣ�ͳһ������� */
#define WLAN_MGMT_NETBUF_SIZE         WLAN_MEM_NETBUF_SIZE2 /* NETBUF�ڴ�ع���֡�ĳ��� �� ͳһ������� */
#define WLAN_SHORT_NETBUF_SIZE        WLAN_MEM_NETBUF_SIZE2 /* NETBUF�ڴ�ض�֡�ĳ��� ��ͳһ������� */
#define WLAN_MAX_NETBUF_SIZE          WLAN_LARGE_NETBUF_SIZE /* netbuf���֡����֡ͷ + payload */

/*****************************************************************************
  2.4.9.1 sdt netbuf�ڴ��
*****************************************************************************/

/*  sdt��ϢԤ������ڴ�飬��netbuf��Ӻ󣬹������г���ʱ����Ҫ���⴦��ֱ��send����
    �ⲿ�������볤��ΪPayload�ĳ���
*/
/************************* sdt report msg format*********************************/
/* NETLINK_HEAD     | SDT_MSG_HEAD  | Payload    | SDT_MSG_TAIL  |    pad       */
/* ---------------------------------------------------------------------------- */
/* NLMSG_HDRLEN     |    8Byte      |     ...    |   1Byte       |    ...       */
/********************************************************************************/
#define WLAN_SDT_SKB_HEADROOM_LEN       8
#define WLAN_SDT_SKB_TAILROOM_LEN       1
#define WLAN_SDT_SKB_RESERVE_LEN        (WLAN_SDT_SKB_HEADROOM_LEN + WLAN_SDT_SKB_TAILROOM_LEN)

/*
    SDT�ڴ����Ҫ����SDT��Ϣ��ʵ�ʽ��е���
*/
#define WLAN_MEM_SDT_NETBUF_PAYLOAD1            37          //��־��Ϣ����
#define WLAN_MEM_SDT_NETBUF_PAYLOAD2            100
#define WLAN_MEM_SDT_NETBUF_PAYLOAD3            512
#define WLAN_MEM_SDT_NETBUF_PAYLOAD4            1600

#define WLAN_SDT_NETBUF_MAX_PAYLOAD             WLAN_MEM_SDT_NETBUF_PAYLOAD4

#define WLAN_MEM_SDT_NETBUF_SIZE1       (WLAN_MEM_SDT_NETBUF_PAYLOAD1 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE1_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE2       (WLAN_MEM_SDT_NETBUF_PAYLOAD2 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE2_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE3       (WLAN_MEM_SDT_NETBUF_PAYLOAD3 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE3_CNT   (250 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)
#define WLAN_MEM_SDT_NETBUF_SIZE4       (WLAN_MEM_SDT_NETBUF_PAYLOAD4 + WLAN_SDT_SKB_RESERVE_LEN)
#define WLAN_MEM_SDT_NETBUF_SIZE4_CNT   (256 * WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC)

#define WLAN_SDT_MSG_FLT_HIGH_THD           800
#define WLAN_SDT_MSG_QUEUE_MAX_LEN          (WLAN_MEM_SDT_NETBUF_SIZE1_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE2_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE3_CNT + \
                                                 WLAN_MEM_SDT_NETBUF_SIZE4_CNT - 6)  /* ��������ڴ��Ҫ�٣��˴�ȡ��1000 */

/*****************************************************************************
  2.4.10 RFͨ�������
*****************************************************************************/

/*****************************************************************************
  2.4.11 TCP ACK�Ż�
*****************************************************************************/
#define DEFAULT_TX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_RX_TCP_ACK_OPT_ENABLE (OAL_FALSE)
#define DEFAULT_TX_TCP_ACK_THRESHOLD (1) /*��������ack ������*/
#define DEFAULT_RX_TCP_ACK_THRESHOLD (1) /*��������ack ������*/


/*****************************************************************************
  2.5 frw��ص�spec
*****************************************************************************/

/******************************************************************************
    �¼�����������Ϣ��
    ע��: ÿ�������������ɵ�����¼�����������2����������
*******************************************************************************/

#define FRW_EVENT_MAX_NUM_QUEUES    (FRW_EVENT_TYPE_BUTT * WLAN_VAP_SUPPORT_MAX_NUM_LIMIT)

#define WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    /* �¼�����       ����Ȩ��   �����������ɵ�����¼�����   �����������Ȳ��� */  \
    /* HIGH_PRIO */     {   1,               32,                      0, 0}, \
    /* HOST_CRX */      {   1,               64,                      1, 0}, \
    /* HOST_DRX */      {   1,               64,                      1, 0}, \
    /* HOST_CTX */      {   1,               64,                      1, 0}, \
    /* HOST_SDT */      {   1,               64,                      1, 0}, \
    /* WLAN_CRX */      {   1,               64,                      1, 0}, \
    /* WLAN_DRX */      {   1,               64,                      0, 0}, \
    /* WLAN_CTX */      {   1,               64,                      1, 0}, \
    /* WLAN_DTX */      {   1,               64,                      0, 0}, \
    /* WLAN_TX_COMP */  {   1,               64,                      0, 0}, \
    /* TBTT */          {   1,               64,                      1, 0}, \
    /* TIMEOUT */       {   1,                2,                      1, 0}, \
    /* HMAC MISC */     {   1,               64,                      1, 0}, \
    /* DMAC MISC */     {   1,               64,                      0, 0},
    /* DTS2015061601664����AP<->STA�����������Լ�STA<->STA�������ۺϳ����£���Ҫ���WLAN DTX��DRX��TX COMP�¼���������ȼ�����ֹϵͳ�����������ϵͳ�ڴ�й¶ */
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP /* ˫��˫оƬ���ñ� */

#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#else /* ˫�˵�оƬ */
#define WLAN_FRW_EVENT_CFG_TABLE \
  { \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
    WLAN_FRW_EVENT_CFG_TABLE_PER_VAP \
  }
#endif

/*****************************************************************************
  2.8.0 ����OS����
*****************************************************************************/
/* 11i���� */
/*WPA ��Կ����*/
#define WLAN_WPA_KEY_LEN                    32
/*WPA ��ų���*/
#define WLAN_WPA_SEQ_LEN                    16

/*****************************************************************************
  2.9 DFT
*****************************************************************************/
/*****************************************************************************
  2.9.0 ��־
*****************************************************************************/
/*****************************************************************************
  2.9.15 WiFi�ؼ���Ϣ���
*****************************************************************************/
#define WLAN_MAC_ADDR_LEN                   6           /* MAC��ַ���Ⱥ� */
#define WLAN_MAX_FRAME_HEADER_LEN           36          /* ����MAC֡ͷ���ȣ�����֡36������֡Ϊ28 */
#define WLAN_MIN_FRAME_HEADER_LEN           10          /* ack��cts��֡ͷ����Ϊ10 */
#define WLAN_MAX_FRAME_LEN                  1600        /* ά���ã���ֹԽ�� */
#define WLAN_MGMT_FRAME_HEADER_LEN          24          /* ����֡��MAC֡ͷ���ȣ�����֡36������֡Ϊ28 */


/* ����֡������ */
typedef enum
{
    WLAN_ASSOC_REQ              = 0,    /* 0000 */
    WLAN_ASSOC_RSP              = 1,    /* 0001 */
    WLAN_REASSOC_REQ            = 2,    /* 0010 */
    WLAN_REASSOC_RSP            = 3,    /* 0011 */
    WLAN_PROBE_REQ              = 4,    /* 0100 */
    WLAN_PROBE_RSP              = 5,    /* 0101 */
    WLAN_TIMING_AD              = 6,    /* 0110 */
    WLAN_MGMT_SUBTYPE_RESV1     = 7,    /* 0111 */
    WLAN_BEACON                 = 8,    /* 1000 */
    WLAN_ATIM                   = 9,    /* 1001 */
    WLAN_DISASOC                = 10,   /* 1010 */
    WLAN_AUTH                   = 11,   /* 1011 */
    WLAN_DEAUTH                 = 12,   /* 1100 */
    WLAN_ACTION                 = 13,   /* 1101 */
    WLAN_ACTION_NO_ACK          = 14,   /* 1110 */
    WLAN_MGMT_SUBTYPE_RESV2     = 15,   /* 1111 */

    WLAN_MGMT_SUBTYPE_BUTT      = 16,   /* һ��16�ֹ���֡������ */
}wlan_frame_mgmt_subtype_enum;

/*TBD����Ӧ��BUTT��������ö��*/
typedef enum
{
    WLAN_WME_AC_BE = 0,    /* best effort */
    WLAN_WME_AC_BK = 1,    /* background */
    WLAN_WME_AC_VI = 2,    /* video */
    WLAN_WME_AC_VO = 3,    /* voice */

    WLAN_WME_AC_BUTT = 4,
    WLAN_WME_AC_MGMT = WLAN_WME_AC_BUTT   /* ����AC��Э��û��,��ӦӲ�������ȼ�����*/
}wlan_wme_ac_type_enum;
typedef oal_uint8 wlan_wme_ac_type_enum_uint8;

/* TID����Ϊ8,0~7 */
#define WLAN_TID_MAX_NUM                    WLAN_TIDNO_BUTT

/* TID������ */
typedef enum
{
    WLAN_TIDNO_BEST_EFFORT              = 0, /* BEҵ�� */
    WLAN_TIDNO_BACKGROUND               = 1, /* BKҵ�� */
    WLAN_TIDNO_UAPSD                    = 2, /* U-APSD */
    WLAN_TIDNO_ANT_TRAINING_LOW_PRIO    = 3, /* �������ߵ����ȼ�ѵ��֡ */
    WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   = 4, /* �������߸����ȼ�ѵ��֡ */
    WLAN_TIDNO_VIDEO                    = 5, /* VIҵ�� */
    WLAN_TIDNO_VOICE                    = 6, /* VOҵ�� */
    WLAN_TIDNO_BCAST                    = 7, /* �㲥�û��Ĺ㲥�����鲥���� */

    WLAN_TIDNO_BUTT
}wlan_tidno_enum;
typedef oal_uint8 wlan_tidno_enum_uint8;

/* ��Ծ�û��������� */
#define WLAN_ACTIVE_USER_MAX_NUM            32

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#endif /* #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* #ifndef __PLATFORM_SPEC_1151_H__ */




