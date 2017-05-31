/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_types.h
  �� �� ��   : ����
  ��    ��   : c59720
  ��������   : 2012��9��7��
  ����޸�   :
  ��������   : oal_types.h ��ͷ�ļ�,�����������Ͷ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��7��
    ��    ��   : c59720
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_TYPES_H__
#define __OAL_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "arch/oal_types.h"
/*****************************************************************************
  2 �����������Ͷ���
*****************************************************************************/
typedef float                   oal_float32;        /* ����ǰ׺:f */
typedef double                  oal_float64;        /* ����ǰ׺:d */

/*******************************************************************************
    ��ȷ�����ȣ���32λ������Ϊ32bits����64λ������Ϊ64bits
*******************************************************************************/
typedef unsigned long           oal_uint;           /* ����ǰ׺:ui */
typedef signed long             oal_int;            /* ����ǰ׺:i */
typedef unsigned long           oal_ulong;           /*��ָ�����͵ȳ�*/
typedef signed long             oal_long;            /*����ǰ׺:i */

/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define OAL_PTR_NULL        (0L)                        /* ��ָ�붨�壬ָ���ж��Ƿ�Ϊ��ʱ��OAL_PTR_NULL���бȽ� */

#ifndef NULL
#define NULL    OAL_PTR_NULL
#endif

#define OAL_REFERENCE(data)	((void)(data))

/* linux������ */
#define OAL_EFAIL               1   /* �ں�ͨ�ô��󷵻�ֵ -1 */
#define OAL_EIO                 5   /* I/O error */
#define OAL_ENOMEM              12  /* Out of memory */
#define OAL_EFAUL               14  /* Bad address */
#define OAL_EBUSY               16  /* Device or resource busy */
#define OAL_ENODEV              19  /* No such device */
#define OAL_EINVAL              22  /* Invalid argument */
#define OAL_ETIMEDOUT           110	/* Connection timed out */

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
typedef enum
{
    OAL_FALSE   = 0,
    OAL_TRUE    = 1,

    OAL_BUTT
}oal_bool_enum;
typedef oal_uint8 oal_bool_enum_uint8;

/* ����ҵ������ */
typedef enum
{
    OAL_TRAFFIC_NORMAL= 0,					/*һ��ҵ��*/
    OAL_TRAFFIC_MULTI_USER_MULTI_AC   = 1,	/*���û������ȼ�ҵ��*/
    OAL_TRAFFIC_MULTI_USER_ONLY_BE   = 2,		/*32�û������ȼ�ҵ��*/
    OAL_TRAFFIC_BUTT
}oal_traffic_type_enum;
typedef oal_uint8 oal_traffic_type_enum_uint8;

/* ���幦�ܿ��� */
typedef enum
{
    OAL_SWITCH_OFF  = 0,
    OAL_SWITCH_ON   = 1,

    OAL_SWITCH_BUTT
}oal_switch_enum;
typedef oal_uint8 oal_switch_enum_uint8;

typedef enum
{
    /**************************************************************************
        platform err code
    ***************************************************************************/
    ERR_CODE_PLATFORM_BASE  = 0x00000001,
    /**************************************************************************
        wifi err code
    ***************************************************************************/
    ERR_CODE_WIFI_BASE      = 0x10000000,
    /**************************************************************************
        bt device code
    ***************************************************************************/
    ERR_CODE_BT_BASE        = 0x20000000,
    /**************************************************************************
        fm err code
    ***************************************************************************/
    ERR_CODE_FM_BASE        = 0x30000000,
    /**************************************************************************
        gnss err code
    ***************************************************************************/
    ERR_CODE_GNSS_BASE      = 0x40000000,
    /**************************************************************************
        nfc err code
    ***************************************************************************/
    ERR_CODE_NFC_BASE       = 0x50000000,
    /**************************************************************************
        ir device code
    ***************************************************************************/
    ERR_CODE_IR_BASE        = 0x60000000,
}err_code_enum;
typedef oal_uint32 err_code_enum_uint32;

/* �����������붨�� */
typedef enum
{
    OAL_SUCC                                  = 0,                              /* �ɹ���û���쳣 */

    /**************************************************************************
        plat pm exception
    **************************************************************************/
    OAL_ERR_CODE_PM_BASE                     = 10,
    OAL_ERR_CODE_ALREADY_OPEN                = (OAL_ERR_CODE_PM_BASE + 0),    /* �Ѿ��� */
    OAL_ERR_CODE_ALREADY_CLOSE               = (OAL_ERR_CODE_PM_BASE + 1),    /* �Ѿ��ر� */

    /**************************************************************************
        system exception
    **************************************************************************/
    OAL_ERR_CODE_SYS_BASE                     = 100,
    OAL_ERR_CODE_PTR_NULL                     = (OAL_ERR_CODE_SYS_BASE + 0),    /* ָ����Ϊ�� */
    OAL_ERR_CODE_ARRAY_OVERFLOW               = (OAL_ERR_CODE_SYS_BASE + 1),    /* �����±�Խ�� */
    OAL_ERR_CODE_DIV_ZERO                     = (OAL_ERR_CODE_SYS_BASE + 2),    /* ��0���� */
    OAL_ERR_CODE_ALLOC_MEM_FAIL               = (OAL_ERR_CODE_SYS_BASE + 3),    /* �����ڴ�ʧ�� */
    OAL_ERR_CODE_FREE_MEM_FAIL                = (OAL_ERR_CODE_SYS_BASE + 4),
    OAL_ERR_CODE_START_TIMRE_FAIL             = (OAL_ERR_CODE_SYS_BASE + 5),    /* ������ʱ��ʧ�� */
    OAL_ERR_CODE_RESET_INPROGRESS             = (OAL_ERR_CODE_SYS_BASE + 6),    /* ��λ������ */
    OAL_ERR_CODE_MAC_DEVICE_NULL              = (OAL_ERR_CODE_SYS_BASE + 7),    /* mac_device_struz�Ҳ��� */
	OAL_ERR_CODE_MAGIC_NUM_FAIL               = (OAL_ERR_CODE_SYS_BASE + 8),    /* ħ�����ּ��ʧ�� */
	OAL_ERR_CODE_NETBUF_INDEX_CHANGE          = (OAL_ERR_CODE_SYS_BASE + 9),    /*netbuf ���۸� */
    OAL_ERR_CODE_CFG_REG_TIMEOUT              = (OAL_ERR_CODE_SYS_BASE + 10),   /* ���üĴ�����ʱ */
    OAL_ERR_CODE_CFG_REG_ERROR                = (OAL_ERR_CODE_SYS_BASE + 11),   /* ���üĴ������� */
    OAL_ERR_CODE_LIST_NOT_EMPTY_ERROR         = (OAL_ERR_CODE_SYS_BASE + 12),   /* ����Ϊ�գ�һ�������������������� */

    OAL_ERR_SYS_BUTT                          = (OAL_ERR_CODE_SYS_BASE + 999),        /* system error���ֵ*/

    /**************************************************************************
        config exception
    ***************************************************************************/
    OAL_ERR_CODE_CONFIG_BASE                  = 1000,
    OAL_ERR_CODE_INVALID_CONFIG               = (OAL_ERR_CODE_CONFIG_BASE + 0), /* ��Ч���� */
    OAL_ERR_CODE_CONFIG_UNSUPPORT             = (OAL_ERR_CODE_CONFIG_BASE + 1), /* ���ò�֧�� */
    OAL_ERR_CODE_CONFIG_EXCEED_SPEC           = (OAL_ERR_CODE_CONFIG_BASE + 2), /* ���ó������ */
    OAL_ERR_CODE_CONFIG_TIMEOUT               = (OAL_ERR_CODE_CONFIG_BASE + 3), /* ���ó�ʱ */
    OAL_ERR_CODE_CONFIG_BUSY                  = (OAL_ERR_CODE_CONFIG_BASE + 4),
    OAL_ERR_CODE_ADD_VAP_INDX_UNSYNC          = (OAL_ERR_CODE_CONFIG_BASE + 5), /* HMAC��DMAC����vapʱ��index��һ�� */
    OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC   = (OAL_ERR_CODE_CONFIG_BASE + 6), /* HMAC��DMAC����multi userʱ��index��һ�� */
    OAL_ERR_CODE_USER_RES_CNT_ZERO            = (OAL_ERR_CODE_CONFIG_BASE + 7), /* �û���Դ�Ѿ��ͷţ��ظ��ͷ� */

    OAL_ERR_CODE_CONFIG_BUTT                  = (OAL_ERR_CODE_CONFIG_BASE + 99),/* ���ô������ֵ*/

    /**************************************************************************
        MSG exception
    **************************************************************************/
    OAL_ERR_CODE_MSG_BASE                      = 1100,
    OAL_ERR_CODE_MSG_TYPE_ERR                  = (OAL_ERR_CODE_MSG_BASE + 0),   /* ��Ϣ���ͽ������� */
    OAL_ERR_CODE_MSG_NOT_CMPTBL_WITH_STATE     = (OAL_ERR_CODE_MSG_BASE + 1),   /* ��Ϣ��������״̬��һ�� */
    OAL_ERR_CODE_MSG_IE_MISS                   = (OAL_ERR_CODE_MSG_BASE + 2),   /* ��ϢIEȱʧ */
    OAL_ERR_CODE_MSG_IE_VALUE_ERR              = (OAL_ERR_CODE_MSG_BASE + 3),   /* ��ϢIE��ֵ���� */
    OAL_ERR_CODE_IPC_QUEUE_FULL                = (OAL_ERR_CODE_MSG_BASE + 4),   /* ipc�ڲ���Ϣ���Ͷ��������� */
    OAL_ERR_CODE_MSG_NOT_FIND_STA_TAB          = (OAL_ERR_CODE_MSG_BASE + 5),   /* ��Ϣ�Ҳ���״̬�� */
    OAL_ERR_CODE_MSG_NOT_FIND_ACT_TAB          = (OAL_ERR_CODE_MSG_BASE + 6),   /* ��Ϣ�Ҳ��������� */
    OAL_ERR_CODE_MSG_ACT_FUN_NULL              = (OAL_ERR_CODE_MSG_BASE + 7),   /* ��Ϣ��Ӧ�Ĵ�����ΪNULL */
    OAL_ERR_CODE_MSG_LENGTH_ERR                = (OAL_ERR_CODE_MSG_BASE + 8),   /* ��Ϣ���ȴ��� */

    OAL_ERR_CODE_MSG_BUTT                      = (OAL_ERR_CODE_MSG_BASE + 99),  /* ��Ϣ�������ֵ*/

    /**************************************************************************
        �ļ�����������
    **************************************************************************/
    OAL_ERR_CODE_FILE_BASE                     = 1200,
    OAL_ERR_CODE_OPEN_FILE_FAIL                = (OAL_ERR_CODE_FILE_BASE + 0),
    OAL_ERR_CODE_WRITE_FILE_FAIL               = (OAL_ERR_CODE_FILE_BASE + 1),
    OAL_ERR_CODE_READ_FILE_FAIL                = (OAL_ERR_CODE_FILE_BASE + 2),
    OAL_ERR_CODE_CLOSE_FILE_FAIL               = (OAL_ERR_CODE_FILE_BASE + 3),

    OAL_ERR_CODE_FILE_BUTT                     = (OAL_ERR_CODE_FILE_BASE + 99), /*�ļ������������ֵ*/

    /**************************************************************************
        ��ģ���Զ������
    **************************************************************************/
    /**************************** �������������� *****************************/
    OAL_ERR_CODE_DSCR_BASE                     = 10000,
    OAL_ERR_CODE_RX_DSCR_AMSDU_DISORDER        = (OAL_ERR_CODE_DSCR_BASE + 0),  /* AMSDU��Ӧ������������ */
    OAL_ERR_CODE_RX_DSCR_LOSE                  = (OAL_ERR_CODE_DSCR_BASE + 1),  /* ��������buf��Ŀ����Ӧ */

    OAL_ERR_CODE_DSCR_BUTT                     = (OAL_ERR_CODE_DSCR_BASE + 999),

    /**************************************************************************
        �������Զ������,��20000��ʼ��ÿ�����Է���100��
    **************************************************************************/
    /**************************** AMSDU���� ***********************************/
    OAL_ERR_CODE_HMAC_AMSDU_BASE               = 20000,
    OAL_ERR_CODE_HMAC_AMSDU_DISABLE            = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 0),  /* amsdu���ܹر� */
    OAL_ERR_CODE_HMAC_MSDU_LEN_OVER            = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 1),

    OAL_ERR_CODE_HMAC_AMSDU_BUTT               = (OAL_ERR_CODE_HMAC_AMSDU_BASE + 999),

    /********************************* ���� **********************************/
    /**************************** 11i ���� ***********************************/
    OAL_ERR_CODE_SECURITY_BASE               = 21000,
    OAL_ERR_CODE_SECURITY_KEY_TYPE           = (OAL_ERR_CODE_SECURITY_BASE + 0),
    OAL_ERR_CODE_SECURITY_KEY_LEN            = (OAL_ERR_CODE_SECURITY_BASE + 1),
    OAL_ERR_CODE_SECURITY_KEY_ID             = (OAL_ERR_CODE_SECURITY_BASE + 2),
    OAL_ERR_CODE_SECURITY_CHIPER_TYPE        = (OAL_ERR_CODE_SECURITY_BASE + 3),
    OAL_ERR_CODE_SECURITY_BUFF_NUM           = (OAL_ERR_CODE_SECURITY_BASE + 4),
    OAL_ERR_CODE_SECURITY_BUFF_LEN           = (OAL_ERR_CODE_SECURITY_BASE + 5),
    OAL_ERR_CODE_SECURITY_WRONG_KEY          = (OAL_ERR_CODE_SECURITY_BASE + 6),
    OAL_ERR_CODE_SECURITY_USER_INVAILD       = (OAL_ERR_CODE_SECURITY_BASE + 7),
    OAL_ERR_CODE_SECURITY_PARAMETERS         = (OAL_ERR_CODE_SECURITY_BASE + 8),
    OAL_ERR_CODE_SECURITY_AUTH_TYPE          = (OAL_ERR_CODE_SECURITY_BASE + 9),
    OAL_ERR_CODE_SECURITY_CAP                = (OAL_ERR_CODE_SECURITY_BASE + 10),
    OAL_ERR_CODE_SECURITY_CAP_MFP            = (OAL_ERR_CODE_SECURITY_BASE + 11),
    OAL_ERR_CODE_SECURITY_CAP_BSS            = (OAL_ERR_CODE_SECURITY_BASE + 12),
    OAL_ERR_CODE_SECURITY_CAP_PHY            = (OAL_ERR_CODE_SECURITY_BASE + 13),
    OAL_ERR_CODE_SECURITY_PORT_INVALID       = (OAL_ERR_CODE_SECURITY_BASE + 14),
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    OAL_ERR_CODE_SECURITY_MAC_INVALID        = (OAL_ERR_CODE_SECURITY_BASE + 15),
    OAL_ERR_CODE_SECURITY_MODE_INVALID       = (OAL_ERR_CODE_SECURITY_BASE + 16),
    OAL_ERR_CODE_SECURITY_LIST_FULL          = (OAL_ERR_CODE_SECURITY_BASE + 17),
    OAL_ERR_CODE_SECURITY_AGING_INVALID      = (OAL_ERR_CODE_SECURITY_BASE + 18),
    OAL_ERR_CODE_SECURITY_THRESHOLD_INVALID  = (OAL_ERR_CODE_SECURITY_BASE + 19),
    OAL_ERR_CODE_SECURITY_RESETIME_INVALID   = (OAL_ERR_CODE_SECURITY_BASE + 20),
#endif
    OAL_ERR_CODE_SECURITY_BUTT               = (OAL_ERR_CODE_SECURITY_BASE + 99),
    /* �����������Ȳ�ɾ��ԭ�ȵĴ����룬��ȫ��������Ժ���ɾ�� */
    OAL_ERR_CODE_HMAC_SECURITY_BASE               = 21100,
    OAL_ERR_CODE_HMAC_SECURITY_KEY_TYPE           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 0),
    OAL_ERR_CODE_HMAC_SECURITY_KEY_LEN            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 1),
    OAL_ERR_CODE_HMAC_SECURITY_KEY_ID             = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 2),
    OAL_ERR_CODE_HMAC_SECURITY_CHIPER_TYPE        = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 3),
    OAL_ERR_CODE_HMAC_SECURITY_BUFF_NUM           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 4),
    OAL_ERR_CODE_HMAC_SECURITY_BUFF_LEN           = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 5),
    OAL_ERR_CODE_HMAC_SECURITY_WRONG_KEY          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 6),
    OAL_ERR_CODE_HMAC_SECURITY_USER_INVAILD       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 7),
    OAL_ERR_CODE_HMAC_SECURITY_PARAMETERS         = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 8),
    OAL_ERR_CODE_HMAC_SECURITY_AUTH_TYPE          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 9),
    OAL_ERR_CODE_HMAC_SECURITY_CAP                = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 10),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_MFP            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 11),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_BSS            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 12),
    OAL_ERR_CODE_HMAC_SECURITY_CAP_PHY            = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 13),
    OAL_ERR_CODE_HMAC_SECURITY_PORT_INVALID       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 14),
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    OAL_ERR_CODE_HMAC_SECURITY_MAC_INVALID        = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 15),
    OAL_ERR_CODE_HMAC_SECURITY_MODE_INVALID       = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 16),
    OAL_ERR_CODE_HMAC_SECURITY_LIST_FULL          = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 17),
    OAL_ERR_CODE_HMAC_SECURITY_AGING_INVALID      = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 18),
    OAL_ERR_CODE_HMAC_SECURITY_THRESHOLD_INVALID  = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 19),
    OAL_ERR_CODE_HMAC_SECURITY_RESETIME_INVALID   = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 20),
#endif
    OAL_ERR_CODE_HMAC_SECURITY_BUTT               = (OAL_ERR_CODE_HMAC_SECURITY_BASE + 499),

/**************************** wapi ���� ***********************************/
    OAL_ERR_CODE_WAPI_BASE                          = 21600,
    OAL_ERR_CODE_WAPI_NETBUFF_LEN_ERR               = (OAL_ERR_CODE_WAPI_BASE + 0),
    OAL_ERR_CODE_WAPI_DECRYPT_FAIL                  = (OAL_ERR_CODE_WAPI_BASE + 1),
    OAL_ERR_CODE_WAPI_MIC_CALC_FAIL                 = (OAL_ERR_CODE_WAPI_BASE + 2),
    OAL_ERR_CODE_WAPI_ENRYPT_FAIL                   = (OAL_ERR_CODE_WAPI_BASE + 3),
    OAL_ERR_CODE_WAPI_MIC_CMP_FAIL                  = (OAL_ERR_CODE_WAPI_BASE + 4),

    OAL_ERR_CODE_WAPI_BUTT                          = (OAL_ERR_CODE_WAPI_BASE + 99),
    /********************************* ���� **********************************/
    /**************************** 11w ���� ***********************************/
    OAL_ERR_CODE_PMF_BASE                         = 22000,
    OAL_ERR_CODE_PMF_ACTIVE_DOWN                  = (OAL_ERR_CODE_PMF_BASE + 0), /* user��bit_pmf_active����û��ʹ�ܿ��� */
    OAL_ERR_CODE_PMF_SA_QUERY_REQ_SEND_FAIL       = (OAL_ERR_CODE_PMF_BASE + 1), /* hmac_send_sa_query_req��������sa query req����ʧ�� */
    OAL_ERR_CODE_PMF_DISABLED                     = (OAL_ERR_CODE_PMF_BASE + 2), /* dot11RSNAProtectedManagementFramesActivated ֵΪ0 */
    OAL_ERR_CODE_PMF_SA_QUERY_START_FAIL          = (OAL_ERR_CODE_PMF_BASE + 3), /* hmac_start_sa_query�������ؽ��ʧ�� */
    OAL_ERR_CODE_PMF_SA_QUERY_DEL_USER_FAIL       = (OAL_ERR_CODE_PMF_BASE + 4), /* hmac_sa_query_del_user����,SA query����ɾ���û�ʧ�� */
    OAL_ERR_CODE_PMF_BIP_AES_CMAC_ENCRYPT_FAIL    = (OAL_ERR_CODE_PMF_BASE + 5), /* oal_crypto_aes_cmac_encrypt������AES_CMAC����ʧ�� */
    OAL_ERR_CODE_PMF_BIP_CRIPTO_FAIL              = (OAL_ERR_CODE_PMF_BASE + 6), /* dmac_bip_crypto������bip����ʧ�� */
    OAL_ERR_CODE_PMF_BIP_DECRIPTO_FAIL            = (OAL_ERR_CODE_PMF_BASE + 7), /* oal_crypto_bip_demic������bip����ʧ�� */
    OAL_ERR_CODE_PMF_IGTK_INDX_FAIL               = (OAL_ERR_CODE_PMF_BASE + 8), /* ����igtk_index ���� */
    OAL_ERR_CODE_PMF_VAP_CAP_FAIL                 = (OAL_ERR_CODE_PMF_BASE + 9), /* VAP��mfpc&mfpr���ô��� */
    OAL_ERR_CODE_PMF_VAP_ACTIVE_DOWN              = (OAL_ERR_CODE_PMF_BASE + 10), /* VAP��mib dot11RSNAActived����ΪOAL_FALES */
    OAL_ERR_CODE_PMF_IGTK_NOT_EXIST               = (OAL_ERR_CODE_PMF_BASE + 11), /* igtk�����ڻ���igtk_idֵ���� */
    OAL_ERR_CODE_PMF_ALIGN_ERR                    = (OAL_ERR_CODE_PMF_BASE + 12), /* bip�ӽ��ܹ��̴��� */
    OAL_ERR_CODE_PMF_REPLAY_ATTAC                 = (OAL_ERR_CODE_PMF_BASE + 13), /* bip�طŹ��� */
    OAL_ERR_CODE_PMF_MMIE_ERR                     = (OAL_ERR_CODE_PMF_BASE + 14), /* bip������У����ʧ�� */
    OAL_ERR_CODE_PMF_NO_PROTECTED_ERROR           = (OAL_ERR_CODE_PMF_BASE + 15), /* PMFʹ���յ�δ���ܵĵ���ǿ������֡ */

    OAL_ERR_CODE_PMF_BUTT                         = (OAL_ERR_CODE_PMF_BASE + 999),
    /********************************* ���� **********************************/
    /***************hostapd/wpa_supplicant�¼��ϱ����·����� *****************/
    OAL_ERR_CODE_CFG80211_BASE               = 23000,
    OAL_ERR_CODE_CFG80211_SKB_MEM_FAIL       = (OAL_ERR_CODE_CFG80211_BASE + 0),  /* skb�����޷�����Ϣͷ������ */
    OAL_ERR_CODE_CFG80211_EMSGSIZE           = (OAL_ERR_CODE_CFG80211_BASE + 1),  /* ��Ϣ̫��,�����޷���� */
    OAL_ERR_CODE_CFG80211_MCS_EXCEED         = (OAL_ERR_CODE_CFG80211_BASE + 2),  /* MCS����32 */
    OAL_ERR_CODE_CFG80211_ENOBUFS            = (OAL_ERR_CODE_CFG80211_BASE + 3),

    OAL_ERR_CODE_CFG80211_BUTT               = (OAL_ERR_CODE_CFG80211_BASE + 999),

    /********************************* OAL **********************************/
    OAL_ERR_CODE_OAL_BASE                    = 24000,

    /**************************** OAL --- �ڴ�� ****************************/
    OAL_ERR_CODE_OAL_MEM_BASE                = (OAL_ERR_CODE_OAL_BASE + 0),
    OAL_ERR_CODE_OAL_MEM_GET_POOL_FAIL       = (OAL_ERR_CODE_OAL_MEM_BASE + 0),   /* ��ȡ�ڴ��ȫ��ָ��ʧ�� */
    OAL_ERR_CODE_OAL_MEM_ALLOC_CTRL_BLK_FAIL = (OAL_ERR_CODE_OAL_MEM_BASE + 1),   /* ������ڴ�ʧ�� */
    OAL_ERR_CODE_OAL_MEM_SKB_SUBPOOL_ID_ERR  = (OAL_ERR_CODE_OAL_MEM_BASE + 2),   /* ��ȡnetbuf subpool idʧ�� */
    OAL_ERR_CODE_OAL_MEM_GET_CFG_TBL_FAIL    = (OAL_ERR_CODE_OAL_MEM_BASE + 3),   /* ��ȡ�ڴ��������Ϣʧ�� */
    OAL_ERR_CODE_OAL_MEM_EXCEED_MAX_LEN      = (OAL_ERR_CODE_OAL_MEM_BASE + 4),   /* �ڴ����󳤶ȳ������� */
    OAL_ERR_CODE_OAL_MEM_EXCEED_SUBPOOL_CNT  = (OAL_ERR_CODE_OAL_MEM_BASE + 5),   /* ���ڴ�ظ����������� */
    OAL_ERR_CODE_OAL_MEM_DOG_TAG             = (OAL_ERR_CODE_OAL_MEM_BASE + 6),   /* �ڴ汻�� */
    OAL_ERR_CODE_OAL_MEM_ALREADY_FREE        = (OAL_ERR_CODE_OAL_MEM_BASE + 7),   /* �ͷ���һ���Ѿ����ͷŵ��ڴ� */
    OAL_ERR_CODE_OAL_MEM_USER_CNT_ERR        = (OAL_ERR_CODE_OAL_MEM_BASE + 8),   /* �ͷ�һ�����ü���Ϊ0���ڴ� */
    OAL_ERR_CODE_OAL_MEM_EXCEED_TOTAL_CNT    = (OAL_ERR_CODE_OAL_MEM_BASE + 9),   /* �����ڴ����Ŀ�����������ڴ�����ڴ���� */
#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
    /**************************** OAL --- �¼� ****************************/
    OAL_ERR_CODE_OAL_EVENT_BASE              = (OAL_ERR_CODE_OAL_BASE + 100),
    OAL_ERR_CODE_OAL_EVENT_Q_EMPTY           = (OAL_ERR_CODE_OAL_EVENT_BASE + 0),
#endif
    OAL_ERR_CODE_OAL_BUTT                    = (OAL_ERR_CODE_OAL_BASE + 999),

    /********************************* OAM **********************************/
    OAL_ERR_CODE_OAM_BASE                    = 25000,

    /**************************** OAM --- event *****************************/
    OAL_ERR_CODE_OAM_EVT_BASE               = (OAL_ERR_CODE_OAM_BASE + 0),
    OAL_ERR_CODE_OAM_EVT_USER_IDX_EXCEED    = (OAL_ERR_CODE_OAM_EVT_BASE + 0),    /* �û������������ֵ */
    OAL_ERR_CODE_OAM_EVT_FRAME_DIR_INVALID  = (OAL_ERR_CODE_OAM_EVT_BASE + 1),    /* �Ȳ��Ƿ������̣�Ҳ���ǽ������� */
    OAL_ERR_CODE_OAM_EVT_FR_HDR_LEN_INVALID = (OAL_ERR_CODE_OAM_EVT_BASE + 2),    /* ֡ͷ�����쳣 */
    OAL_ERR_CODE_OAM_EVT_FR_LEN_INVALID     = (OAL_ERR_CODE_OAM_EVT_BASE + 3),    /* ֡��(����֡ͷ)�����쳣 */
    OAL_ERR_CODE_OAM_EVT_DSCR_LEN_INVALID   = (OAL_ERR_CODE_OAM_EVT_BASE + 4),    /* �����������쳣 */

    OAL_ERR_CODE_OAM_BUTT                    = (OAL_ERR_CODE_OAM_BASE + 999),

    /********************************* KeepAlive **********************************/
    OAL_ERR_CODE_KEEPALIVE_BASE             = 26000,
    /**************************** KeepAlive --- event *****************************/
    OAL_ERR_CODE_KEEPALIVE_CONFIG_VAP       = (OAL_ERR_CODE_KEEPALIVE_BASE + 1),
    OAL_ERR_CODE_KEEPALIVE_BIG_INTERVAL     = (OAL_ERR_CODE_KEEPALIVE_BASE + 2),
    OAL_ERR_CODE_KEEPALIVE_SMALL_LIMIT      = (OAL_ERR_CODE_KEEPALIVE_BASE + 3),
    OAL_ERR_CODE_KEEPALIVE_INVALID_VAP      = (OAL_ERR_CODE_KEEPALIVE_BASE + 4),
    OAL_ERR_CODE_KEEPALIVE_PTR_NULL         = (OAL_ERR_CODE_KEEPALIVE_BASE + 5),

    OAL_ERR_CODE_KEEPALIVE_BUTT             = (OAL_ERR_CODE_KEEPALIVE_BASE + 999),


    /******* PROXY ARP���� COMP--skb�������; INCOMP--skbû�д�����ɣ�������������******/
    OAL_ERR_CODE_PROXY_ARP_BASE                     = 27000,
    OAL_ERR_CODE_PROXY_ARP_INVLD_SKB_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 0), /* ���յ���SKB�쳣 */
    OAL_ERR_CODE_PROXY_ARP_LEARN_USR_NOTEXIST_COMP  = (OAL_ERR_CODE_PROXY_ARP_BASE + 1), /* GARPԴ��ַ�Ǳ�BSS */
    OAL_ERR_CODE_PROXY_ARP_LEARN_USR_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 2), /* GARPԴ��ַѧϰ�ɹ� */
    OAL_ERR_CODE_PROXY_ARP_REPLY2BSS_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 3), /* �� arp reply����BSS */
    OAL_ERR_CODE_PROXY_ARP_REPLY2ETH_COMP           = (OAL_ERR_CODE_PROXY_ARP_BASE + 4), /* �� arp reply��ETH */
    OAL_ERR_CODE_PROXY_ARP_CREATE_FAIL_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 5), /* ����SKBʧ�� */
    OAL_ERR_CODE_PROXY_ND_INVLD_SKB1_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 6), /* ���յ���SKB�쳣 */
    OAL_ERR_CODE_PROXY_ND_INVLD_SKB2_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 7), /* ���յ���SKB�쳣 */
    OAL_ERR_CODE_PROXY_ARP_REPLY_MCAST_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 8), /* ���յ��鲥��arp reply */
    OAL_ERR_CODE_PROXY_ARP_REPLY_INCOMP             = (OAL_ERR_CODE_PROXY_ARP_BASE + 9), /* ���յ�arp reply��ת�� */
    OAL_ERR_CODE_PROXY_ARP_NOT_REQ_REPLY_INCOMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 10),/* ����arp req����reply */

    OAL_ERR_CODE_PROXY_ND_LEARN_USR_NOTEXIST_COMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 11),/* ͨ��NSѧϰ��ַ��ap���ָ�ns��Դmac������ */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_ALREADY_EXIST_INCOMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 12),/* ͨ��NSѧϰ��ַ��ap���ָ�ipv6��ַ�Ѿ���¼��hash�� */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_SUCC_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 13),/* ͨ��NSѧϰ��ַ���� */
    OAL_ERR_CODE_PROXY_ND_LEARN_USR_FAIL_INCOMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 14),/* ͨ��NSѧϰ��ַʧ�� */
    OAL_ERR_CODE_PROXY_ND_NS_OPT_INVLD_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 15),/* ��NS��icmpv6 opt�л�ȡllʧ�� */
    OAL_ERR_CODE_PROXY_ND_NS_FINDUSR_ERR_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 16),/* NS icmpv6�е�target ipv6��ַ����hash����*/
    OAL_ERR_CODE_PROXY_ND_NS_CREATE_NA_FAIL_COMP    = (OAL_ERR_CODE_PROXY_ARP_BASE + 17),/* ����NAʧ�� */
    OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2BSS_COMP      = (OAL_ERR_CODE_PROXY_ARP_BASE + 18),/* �յ�NS��AP�����ظ�NA��BSS */
    OAL_ERR_CODE_PROXY_ND_NA_INVLD_COMP             = (OAL_ERR_CODE_PROXY_ARP_BASE + 19),/* �Ƿ���NA*/
    OAL_ERR_CODE_PROXY_ND_NA_MCAST_NOT_LLA_COMP     = (OAL_ERR_CODE_PROXY_ARP_BASE + 20),/* ���鲥��Ӧ��NA�� icmpv6 opt��ȡllʧ��*/
    OAL_ERR_CODE_PROXY_ND_NA_UCAST_NOT_LLA_INCOMP   = (OAL_ERR_CODE_PROXY_ARP_BASE + 21),/* �ӵ�����Ӧ��NA�� icmpv6 opt��ȡllʧ��*/
    OAL_ERR_CODE_PROXY_ND_NA_DUP_ADDR_INCOMP        = (OAL_ERR_CODE_PROXY_ARP_BASE + 22),/* NA��Я����ipv6��ַ��ͻ */
    OAL_ERR_CODE_PROXY_ND_NA_UNSOLICITED_COMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 23),/* NA��S��־Ϊ0 */
    OAL_ERR_CODE_PROXY_ND_NA_SOLICITED_INCOMP       = (OAL_ERR_CODE_PROXY_ARP_BASE + 24),/* NA��S��־Ϊ1 */
    OAL_ERR_CODE_PROXY_ND_NOT_ICMPV6_INCOMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 25),/* û��Я��icmpv6 */
    OAL_ERR_CODE_PROXY_ND_ICMPV6_NOT_NSNA_INCOMP    = (OAL_ERR_CODE_PROXY_ARP_BASE + 26),/* ����NS����NA */
    OAL_ERR_CODE_PROXY_ARP_FINDUSR_ERR_COMP         = (OAL_ERR_CODE_PROXY_ARP_BASE + 27),/* arp�е�target ipv4��ַ����hash����*/
    OAL_ERR_CODE_PROXY_OTHER_INCOMP                 = (OAL_ERR_CODE_PROXY_ARP_BASE + 28),/* ������proxy �����֡ */
    OAL_ERR_CODE_PROXY_ND_NS_REPLY_NA2ETH_COMP      = (OAL_ERR_CODE_PROXY_ARP_BASE + 29),/* �յ�NS��AP�����ظ�NA��ETH */
    OAL_ERR_CODE_PROXY_ARP_BUTT                     = (OAL_ERR_CODE_PROXY_ARP_BASE + 499),


    /********************************* ����ģ�� **********************************/
    OAL_ERR_CODE_QUEUE_BASE                             = 28000,
    OAL_ERR_CODE_QUEUE_CNT_ZERO                         = (OAL_ERR_CODE_QUEUE_BASE + 0),    /* ����Ϊ�� */

    /********************************* SWP CBBģ�� *******************************/
    OAL_ERR_CODE_SWP_CBB_BASE                           = 28100,
    OAL_ERR_CODE_SWP_CBB_ALREADY_ACTIVE                 = (OAL_ERR_CODE_SWP_CBB_BASE + 0),  /* ��ǰCBB�ӿ��Ѿ����� */
    OAL_ERR_CODE_SWP_CBB_INT_REGISTER_FAIL              = (OAL_ERR_CODE_SWP_CBB_BASE + 1),  /* �жϴ�����ע��ʧ�� */
    OAL_ERR_CODE_SWP_CBB_LENGTH_INVALID                 = (OAL_ERR_CODE_SWP_CBB_BASE + 2),  /* ���ݳ�����Ч */
    OAL_ERR_CODE_SWP_CBB_BUFFUR_FULL                    = (OAL_ERR_CODE_SWP_CBB_BASE + 3),  /* SWP CBB RX��TX�������� */

    /********************************* Type Aģ�� ********************************/
    OAL_ERR_CODE_TYPE_A_BASE                            = 28200,
    OAL_ERR_CODE_UID_ERR                                = (OAL_ERR_CODE_TYPE_A_BASE  + 0),  /* UID ����  */
    OAL_ERR_TIME_OUT_TIMES_BEYOND                       = (OAL_ERR_CODE_TYPE_A_BASE  + 1),  /* ��ʱ�������� */
    OAL_ERR_LEVEL_BEYOND                                = (OAL_ERR_CODE_TYPE_A_BASE  + 2),  /* ������������ */

    /********************************* Type A LISTEN NFC-DEPģ�� ********************************/
    OAL_ERR_CODE_NFC_DEP_LISTEN_BASE                    = 28300,

    /********************************* Type A POLL NFC-DEPģ�� ********************************/
    OAL_ERR_CODE_NFC_DEP_POLL_BASE                      = 28400,

    /********************************* NFC-DEPЭ��ģ�� ********************************/
    OAL_ERR_CODE_NFC_DEP_BASE                           = 28500,
    OAL_ERR_CODE_NFC_DEP_FRAME_TYPE_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 0),  /* ֡���ʹ��� */
    OAL_ERR_CODE_NFC_DEP_FRAME_OPCODE_ERR               = (OAL_ERR_CODE_NFC_DEP_BASE + 1),  /* ֡��������� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DID_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 2),  /* DID ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_GEN_INFO_FLAG_ERR       = (OAL_ERR_CODE_NFC_DEP_BASE + 3),  /* GEN INFO flag ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DSI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 4),  /* DSI ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_DRI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 5),  /* DRI ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_FSL_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 6),  /* FSL ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_MI_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 7),  /* MI ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_NAD_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 8),  /* NAD ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_PNI_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 9),  /* PNI ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_PAYLOAD_ERR             = (OAL_ERR_CODE_NFC_DEP_BASE + 10), /* PAYLOAD ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_SENS_RES_ERR            = (OAL_ERR_CODE_NFC_DEP_BASE + 11), /* sens_res  ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_TAG1_PLT_SUCC           = (OAL_ERR_CODE_NFC_DEP_BASE + 12), /* sens_res ��������tag1����ͻ�������� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CL_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 13), /* SDD_REQ ����ֵ���� */
    OAL_ERR_CODE_NFC_DEP_NFCID_ERR                      = (OAL_ERR_CODE_NFC_DEP_BASE + 14), /* NFCID���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CASCADE_ERR             = (OAL_ERR_CODE_NFC_DEP_BASE + 15), /* Cascade��ʶ���� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_BCC_ERR                 = (OAL_ERR_CODE_NFC_DEP_BASE + 16), /* BCCУ����� */
    OAL_ERR_CODE_NFC_DEP_TYPE_A_CT_ERR                  = (OAL_ERR_CODE_NFC_DEP_BASE + 17), /* CTλ���� */

    /********************************* NFC CBB ģ��**********************************/
    OAL_ERR_CODE_NFC_CBB_BASE                           = 28600,
    OAL_ERR_CODE_NFC_RX_CRC_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 0),  /* CRC ���� */
    OAL_ERR_CODE_NFC_RX_PTY_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 1),  /* PTY ���� */
    OAL_ERR_CODE_NFC_RX_BCC_ERR                         = (OAL_ERR_CODE_NFC_CBB_BASE + 2),  /* BCC ���� */
    OAL_ERR_CODE_NFC_CRPLL_UNLOCK_FLAG_ERR              = (OAL_ERR_CODE_NFC_CBB_BASE + 3),  /* CRPLL ʧ�� ���� */
    OAL_ERR_CODE_NFC_LSTNA_FALLING_FALL_ERR             = (OAL_ERR_CODE_NFC_CBB_BASE + 4),  /* FAILING EDGE ����*/
    OAL_ERR_CODE_NFC_RX_BUFF_ERR                        = (OAL_ERR_CODE_NFC_CBB_BASE + 5),  /* BUFF ���� */
    OAL_ERR_CODE_NFC_RX_BUFF_FRAME_TYPE_ERR             = (OAL_ERR_CODE_NFC_CBB_BASE + 6),  /* FRAME TYPE ���� */
    OAL_ERR_CODE_CBB_INT_REGISTER_FAIL                  = (OAL_ERR_CODE_NFC_CBB_BASE + 7),  /* INT_REGISTER_FAIL ���� */
    OAL_ERR_CODE_CBB_LSTN_RX2TX_TO                      = (OAL_ERR_CODE_NFC_CBB_BASE + 8),  /* Listenģʽ�����ݷ��ͳ�ʱ */
    OAL_ERR_CODE_NFC_RX_LSTN_RATE_ERR                   = (OAL_ERR_CODE_NFC_CBB_BASE + 9),  /* type f Listenģʽ���������ݶ�Ӧ���������ʴ��� */

    /********************************* ����ģ�� **********************************/
    OAL_ERR_CODE_SCHED_BASE                             = 28700,
    OAL_ERR_CODE_SCHED_FSM_EXCEPT_FUN_NULL              = (OAL_ERR_CODE_SCHED_BASE + 0),    /* ״̬���쳣������ΪNULL */
    OAL_ERR_CODE_SCHED_FSM_STA_TAB_NULL                 = (OAL_ERR_CODE_SCHED_BASE + 1),    /* ״̬��״̬��ΪNULL�������� */
    OAL_ERR_CODE_SCHED_PUSH_QUEUE_ID_INVALID            = (OAL_ERR_CODE_SCHED_BASE + 2),    /* �������ID��Ч */

    /********************************* Tag4Bģ�� **********************************/
    OAL_ERR_CODE_TAG4B_BASE                             = 28800,
    OAL_ERR_CODE_TAG4B_NOT_COMPLIANT_14443              = (OAL_ERR_CODE_TAG4B_BASE + 0),    /* ������14443Э����� */
    OAL_ERR_CODE_TAG4B_OPCODE_ERR                       = (OAL_ERR_CODE_TAG4B_BASE + 1),    /* ATTRIB��������� */
    OAL_ERR_CODE_TAG4B_TYPE_B_DID_ERR                   = (OAL_ERR_CODE_TAG4B_BASE + 2),    /* DID���� */
    OAL_ERR_CODE_TAG4B_NFCID_ERR                        = (OAL_ERR_CODE_TAG4B_BASE + 3),    /* NFCID���� */
    OAL_ERR_CODE_TAG4B_BR_ERR                           = (OAL_ERR_CODE_TAG4B_BASE + 4),    /* ���ʴ��� */
    OAL_ERR_CODE_TAG4B_PARAM3_MSB_ERR                   = (OAL_ERR_CODE_TAG4B_BASE + 5),    /* PARAM3 b8-b4��Ϊ0 */

    /********************************* ISO-DEPЭ��ģ�� **********************************/
    OAL_ERR_CODE_ISO_DEP_BASE                           = 28900,
    OAL_ERR_CODE_ISO_DEP_IBLOCK_RETRY_ERR               = (OAL_ERR_CODE_ISO_DEP_BASE + 0),  /* IBLOCK�ش��������ֵ���� */
    OAL_ERR_CODE_ISO_DEP_OVER_FSC_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 1),  /* ���ͽ���block���ȴ���FSC���� */
    OAL_ERR_CODE_ISO_DEP_OVER_FSD_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 2),  /* ���ͽ���block���ȴ���FSD���� */
    OAL_ERR_CODE_ISO_DEP_BLOCK_TYPE_ERR                 = (OAL_ERR_CODE_ISO_DEP_BASE + 3),  /* BLOCK���ʹ��� */
    OAL_ERR_CODE_ISO_DEP_DID_ERR                        = (OAL_ERR_CODE_ISO_DEP_BASE + 4),  /* DID���� */
    OAL_ERR_CODE_ISO_DEP_NAD_ERR                        = (OAL_ERR_CODE_ISO_DEP_BASE + 5),  /* NAD���� */
    OAL_ERR_CODE_ISO_DEP_BN_ERR                         = (OAL_ERR_CODE_ISO_DEP_BASE + 6),  /* BLOCK NUM���� */
    OAL_ERR_CODE_ISO_DEP_ACK_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 7),  /* R_ACK�ش��������ֵ����*/
    OAL_ERR_CODE_ISO_DEP_NAK_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 8),  /* R_NAK�ش��������ֵ����*/
    OAL_ERR_CODE_ISO_DEP_WTX_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 9),  /* S_WTX�ش��������ֵ����*/
    OAL_ERR_CODE_ISO_DEP_DSL_RETRY_ERR                  = (OAL_ERR_CODE_ISO_DEP_BASE + 10), /* S_DSL�ش��������ֵ����*/
    OAL_ERR_CODE_ISO_DEP_PCB_FIX_NUM_ERR                = (OAL_ERR_CODE_ISO_DEP_BASE + 11), /* PBC��fix num���� */
    OAL_ERR_CODE_ISO_DEP_WTXM_ERR                       = (OAL_ERR_CODE_ISO_DEP_BASE + 12), /* WTXM���� */
    OAL_ERR_CODE_ISO_DEP_PROTOCOL_ERR                   = (OAL_ERR_CODE_ISO_DEP_BASE + 13), /* Э����� */
    OAL_ERR_CODE_ISO_DEP_UNRECOVERABLE_EXCEPTIOM        = (OAL_ERR_CODE_ISO_DEP_BASE + 14), /* ���ɻָ��쳣 */

    /********************************* TYPE BЭ��ģ�� **********************************/
    OAL_ERR_CODE_TYPE_B_BASE                            = 29000,
    OAL_ERR_CODE_CUR_SLOT_NUM_ERR                       = (OAL_ERR_CODE_TYPE_B_BASE + 1),   /* ʱ��������� */
    OAL_ERR_CODE_SLOT_NUM_ERR                           = (OAL_ERR_CODE_TYPE_B_BASE + 2),   /* ʱ����������� */
    OAL_ERR_CODE_TYPE_B_SENSB_RES_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_B_BASE + 3),   /* SENSB_RES��������� */
    OAL_ERR_CODE_TYPE_B_CR_AFI_ERR                      = (OAL_ERR_CODE_TYPE_B_BASE + 4),   /* AFI��һ�µĴ��� */
    OAL_ERR_CODE_DID_OVER_ERR                           = (OAL_ERR_CODE_TYPE_B_BASE + 5),   /* didֵ������Χ */
    OAL_ERR_CODE_FSD_FSC_TR0_TR1_TR2_VALUE_ERR          = (OAL_ERR_CODE_TYPE_B_BASE + 6),   /* FSD����FSCȡֵ���� */
    OAL_ERR_CODE_MBL_ERR                                = (OAL_ERR_CODE_TYPE_B_BASE + 7),   /* MBLȡֵ����ȷ */
    /********************************* TAG4Aģ�� **********************************/
    OAL_ERR_CODE_TAG4A_BASE                             = 29100,
    OAL_ERR_CODE_TAG4A_ATS_TL_ERR                       = (OAL_ERR_CODE_SCHED_BASE + 0),    /* ATS TL���� */
    OAL_ERR_CODE_TAG4A_PPS_RES_ERR                      = (OAL_ERR_CODE_SCHED_BASE + 1),    /* PPS_RES���� */
    OAL_ERR_CODE_TAG4A_PPS_DID_ERR                      = (OAL_ERR_CODE_SCHED_BASE + 2),    /* PPS_RES DID���� */
    OAL_ERR_CODE_TAG4A_RATS_OPCODE_ERR                  = (OAL_ERR_CODE_SCHED_BASE + 3),    /* RATS ֡ͷ���� */
    OAL_ERR_CODE_TAG4A_RATS_DID_ERR                     = (OAL_ERR_CODE_SCHED_BASE + 4),    /* RATS DID���� */
    /********************************* TYPE FЭ��ģ�� **********************************/
    OAL_ERR_CODE_TYPE_F_BASE                            = 29200,
    OAL_ERR_CODE_TYPE_F_SENSF_RES_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_F_BASE + 1),   /* SENSF_RES��������� */
    OAL_ERR_CODE_TYPE_F_SENSF_REQ_OPCODE_ERR            = (OAL_ERR_CODE_TYPE_F_BASE + 2),   /* SENSF_REQ��������� */
    OAL_ERR_CODE_TYPE_F_SENSF_RES_WITH_RD_ERR           = (OAL_ERR_CODE_TYPE_F_BASE + 3),   /* SENSF_RES����RD���� */
    /********************************* TAG3Э��ģ�� **********************************/
    OAL_ERR_CODE_TAG3_BASE                              = 29300,
    OAL_ERR_CODE_TAG3_CUP_CMD_OPCODE_ERR                = (OAL_ERR_CODE_TAG3_BASE + 1),     /* CUP_CMD֡ͷ���� */
    OAL_ERR_CODE_TAG3_CUP_RES_OPCODE_ERR                = (OAL_ERR_CODE_TAG3_BASE + 2),     /* CUP_RES֡ͷ���� */
    OAL_ERR_CODE_TAG3_PAYLOAD_ERR                       = (OAL_ERR_CODE_TAG3_BASE + 3),     /* PAYLOAD���� */

    /********************************* NCIЭ��RF DISCOVERYģ�� **********************************/
    OAL_ERR_CODE_RF_DISCOVERY_BASE                      = 29400,
    OAL_ERR_CODE_RF_DISCOVERY_TECH_TYPE_ERR             = (OAL_ERR_CODE_RF_DISCOVERY_BASE + 1), /* �������ʹ��� */
    OAL_ERR_CODE_RF_DISCOVERY_MODE_ERR                  = (OAL_ERR_CODE_RF_DISCOVERY_BASE + 2), /* ���õ�ģʽ���� */

    /********************************* TECH DETECT ACTģ�� **********************************/
    OAL_ERR_CODE_TECH_DETECT_ACT_BASE                   = 29500,
    OAL_ERR_CODE_TECH_DETECT_ACT_TECH_TYPE_ERR          = (OAL_ERR_CODE_TECH_DETECT_ACT_BASE + 1), /* �������Ͷ����������Ĵ��� */

    /********************************* NCIЭ��ģ��**********************************/
    OAL_ERR_CODE_NCI_BASE                               = 29600,
    OAL_ERR_CODE_NCI_CONFIG_PARAM_INVALID               = (OAL_ERR_CODE_NCI_BASE + 1),      /* ��Ч�Ĳ��� */
    OAL_ERR_CODE_NCI_UNKNOWN_MSG                        = (OAL_ERR_CODE_NCI_BASE + 2),      /* ����ʶ������� */
    OAL_ERR_CORE_NCI_PAYLOAD_ERR                        = (OAL_ERR_CODE_NCI_BASE + 3),      /* PAYLOAD���� */
    OAL_ERR_CODE_NCI_DISPATCH_FUN_NULL                  = (OAL_ERR_CODE_NCI_BASE + 4),      /* Dispatch�еĺ���ΪNULL */
    OAL_ERR_CODE_NCI_VAL_LEN_TOO_SHORT                  = (OAL_ERR_CODE_NCI_BASE + 5),      /* �洢�����Ŀռ䲻�� */
    OAL_ERR_CODE_NCI_RECV_MSG_TOO_BIG                   = (OAL_ERR_CODE_NCI_BASE + 6),      /* ���յ���Ϣ��װ��治�� */
    OAL_ERR_CODE_NCI_PARAM_ID_TOO_BIG                   = (OAL_ERR_CODE_NCI_BASE + 7),      /* ������ID������Χ */
    OAL_ERR_CODE_NCI_GID_OID_INVALID                    = (OAL_ERR_CODE_NCI_BASE + 8),      /* NCI��Ϣ��GID��OID��Ч */
    OAL_ERR_CODE_NCI_PACKET_INVALID                     = (OAL_ERR_CODE_NCI_BASE + 9),      /* ���յ���NCI Packet����Ч�� */

    /********************************* SHDLCЭ��ģ��**********************************/
    OAL_ERR_CODE_SHDLC_BASE                             = 29700,
    OAL_ERR_RECV_FRAME_TYPE_DIF_FSM                     = (OAL_ERR_CODE_SHDLC_BASE + 1),    /* ���յ���֡�����뵱ǰ״̬���� */
    OAL_ERR_RECV_RSET_LENGTH                            = (OAL_ERR_CODE_SHDLC_BASE + 2),    /* ���յ���RSET֡��payload���ȳ����޶���Χ */
    OAL_ERR_RECV_FRAME_TYPE_UNKNOWN                     = (OAL_ERR_CODE_SHDLC_BASE + 3),    /* ���յ�֡������δ֪ */
    OAL_ERR_RECV_I_FRAME_LENGTH                         = (OAL_ERR_CODE_SHDLC_BASE + 4),    /* ���յ�֡��I֡��payload���ȳ����޶���Χ */

/* #ifdef _PRE_WLAN_FEATURE_ROAM */
    /********************************* ����ģ��**********************************/
    OAL_ERR_CODE_ROAM_BASE                              = 29800,
    OAL_ERR_CODE_ROAM_DISABLED                          = (OAL_ERR_CODE_ROAM_BASE + 0),      /* ����δʹ��   */
    OAL_ERR_CODE_ROAM_INVALID_VAP                       = (OAL_ERR_CODE_ROAM_BASE + 1),      /* ��Ч��VAP    */
    OAL_ERR_CODE_ROAM_INVALID_USER                      = (OAL_ERR_CODE_ROAM_BASE + 2),      /* ��Ч��USER   */
    OAL_ERR_CODE_ROAM_NO_VALID_BSS                      = (OAL_ERR_CODE_ROAM_BASE + 3),      /* �޿��õ�BSS  */
    OAL_ERR_CODE_ROAM_STATE_UNEXPECT                    = (OAL_ERR_CODE_ROAM_BASE + 4),      /* ״̬����     */
    OAL_ERR_CODE_ROAM_EVENT_UXEXPECT                    = (OAL_ERR_CODE_ROAM_BASE + 5),      /* �¼�����     */
    OAL_ERR_CODE_ROAM_FRAMER_SUB_TYPE                   = (OAL_ERR_CODE_ROAM_BASE + 6),      /* ֡���ʹ���   */
    OAL_ERR_CODE_ROAM_FRAMER_LEN                        = (OAL_ERR_CODE_ROAM_BASE + 7),      /* ֡���ȴ���   */
    OAL_ERR_CODE_ROAM_INVALID_VAP_STATUS                = (OAL_ERR_CODE_ROAM_BASE + 8),      /* ��Ч��VAP״̬*/
    OAL_ERR_CODE_ROAM_HANDSHAKE_FAIL                    = (OAL_ERR_CODE_ROAM_BASE + 9),      /* ��Կ����ʧ��*/
/* #endif //_PRE_WLAN_FEATURE_ROAM */

    /********************************* VoWiFiģ��**********************************/
    OAL_ERR_CODE_VOWIFI_BASE                            = 29900,
    OAL_ERR_CODE_VOWIFI_SET_INVALID                     = (OAL_ERR_CODE_VOWIFI_BASE + 0),      /* ���ò���������Ч   */


    /********************************* HW RESET ģ��*************************************/
    OAL_ERR_CODE_HW_RESET_BASE                          = 30600,
    OAL_ERR_CODE_HW_RESET_PHY_SAVE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 0),
    OAL_ERR_CODE_HW_RESET_MAC_SAVE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 1),
    OAL_ERR_CODE_HW_RESET_MAC_SAVE_SIZELIMIT            = (OAL_ERR_CODE_HW_RESET_BASE + 2),
    OAL_ERR_CODE_HW_RESET_PHY_SAVE_SIZELIMIT            = (OAL_ERR_CODE_HW_RESET_BASE + 3),
    OAL_ERR_CODE_HW_RESET_TX_QUEUE_MEMALLOC             = (OAL_ERR_CODE_HW_RESET_BASE + 4),    /* reset����������tx fake queueʧ�� */

    OAL_FAIL,                                                                   /* ͨ���쳣�����������쳣�޷�ƥ����д��ֵ */

    OAL_ERR_CODE_BUTT
}oal_err_code_enum;
typedef oal_uint32 oal_err_code_enum_uint32;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  8 STRUCT����
*****************************************************************************/


/*****************************************************************************
  9 UNION����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_types.h */

