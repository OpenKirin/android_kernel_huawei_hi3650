

#ifndef __ATPARSE_H__
#define __ATPARSE_H__

#include "hi_list.h"
#include "msp_at.h"
#include "AtParseCmd.h"
#include "MnClient.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */
#include "product_config.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/* Added by L60609 for AT Project��2011-10-09,  Begin*/
#define AT_CMD_MAX_LEN                          5000

#define AT_CMD_OUTPUT_MAX_LEN                   (1500)                          /* ����֧��AT�����ͨ��MODEM������СΪ1500BYTE
                                                                                   VCOMͨ������Ϊ4K������ͨ����DMSģ������Ϊ5120�ֽڣ�
                                                                                   �˴�����С��MODEM����
                                                                                */

#define AT_CMD_ECONF_DIAL_MAX_PARA_NUM          (11)
#define AT_CMD_ECONF_DIAL_MIN_PARA_NUM          (7)

#define AT_CMD_ECKMC_MAX_KMC_LENGTH             (96)
#define AT_CMD_ECKMC_MAX_VERSION                (255)
#define AT_CMD_ECCALL_MAX_NUM_LENGTH            (11)


/*******************************************************************************
 �ṹ��    : AT_DATE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʮ�������ּ�¼���ڵ����г�Ա��
             ������������ݣ��·ݣ����ڣ�Сʱ�����ӣ�����
             ��λ�ֱ�Ϊ�꣬�£��գ�Сʱ�����ӣ���
*******************************************************************************/
typedef struct
{
    TAF_UINT32                          ulYear;
    TAF_UINT32                          ulMonth;
    TAF_UINT32                          ulDay;
    TAF_UINT32                          ulHour;
    TAF_UINT32                          ulMunite;
    TAF_UINT32                          ulSecond;
}AT_DATE_STRU;

enum AT_RRETURN_CODE_ENUM
{
    AT_SUCCESS = 0,
    AT_FAILURE,
    AT_WAIT_SMS_INPUT,
    AT_WAIT_XML_INPUT,
    AT_WAIT_ASYNC_RETURN,

    AT_BASIC_CODE_ENUM_BEGAIN,               /* BASIC CODE ��ʼ */
    AT_OK,
    AT_CONNECT,
    AT_RING,
    AT_NO_CARRIER,
    AT_ERROR,
    AT_NO_DIALTONE,
    AT_BUSY,
    AT_NO_ANSWER,
    AT_BASIC_CODE_ENUM_END,                  /* BASIC CODE ���� */

    AT_CME_ERROR_ENUM_BEGAIN,                /* CME ERROR ��ʼ */

    AT_CME_PHONE_FAILURE,
    AT_CME_NO_CONNECTION_TO_PHONE,
    AT_CME_PHONE_ADAPTOR_LINK_RESERVED,
    AT_CME_OPERATION_NOT_ALLOWED,
    AT_CME_OPERATION_NOT_SUPPORTED,
    AT_CME_PH_SIM_PIN_REQUIRED,
    AT_CME_PH_FSIM_PIN_REQUIRED,
    AT_CME_PH_FSIM_PUK_REQUIRED,
    AT_CME_SIM_NOT_INSERTED,
    AT_CME_SIM_PIN_REQUIRED,
    AT_CME_SIM_PUK_REQUIRED,
    AT_CME_SIM_FAILURE,
    AT_CME_SIM_BUSY,
    AT_CME_SIM_WRONG,
    AT_CME_INCORRECT_PASSWORD,
    AT_CME_SIM_PIN2_REQUIRED,
    AT_CME_SIM_PUK2_REQUIRED,
    AT_CME_MEMORY_FULL,
    AT_CME_INVALID_INDEX,
    AT_CME_NOT_FOUND,
    AT_CME_MEMORY_FAILURE,
    AT_CME_TEXT_STRING_TOO_LONG,
    AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING,
    AT_CME_DIAL_STRING_TOO_LONG,
    AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING,

    AT_CME_SPN_FILE_CONTENT_ERROR,
    AT_CME_SPN_FILE_QUERY_REJECT,
    AT_CME_SPN_FILE_NOT_EXISTS,

    AT_CME_NO_NETWORK_SERVICE,
    AT_CME_NETWORK_TIMEOUT,
    AT_CME_NETWORK_NOT_ALLOWED_EMERGENCY_CALLS_ONLY,
    AT_CME_NETWORK_PERSONALIZATION_PIN_REQUIRED,
    AT_CME_NETWORK_PERSONALIZATION_PUK_REQUIRED,
    AT_CME_NETWORK_SUBSET_PERSONALIZATION_PIN_REQUIRED,
    AT_CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED,
    AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PIN_REQUIRED,
    AT_CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED,
    AT_CME_CORPORATE_PERSONALIZATION_PIN_REQUIRED,
    AT_CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED,
    AT_CME_HIDDEN_KEY_REQUIRED,
    AT_CME_EAP_METHOD_NOT_SUPPORTED,
    AT_CME_INCORRECT_PARAMETERS,
    AT_CME_RX_DIV_NOT_SUPPORTED,
    AT_CME_RX_DIV_OTHER_ERR,
    AT_CME_UNKNOWN,

    AT_CME_ILLEGAL_MS,
    AT_CME_ILLEGAL_ME,
    AT_CME_GPRS_SERVICES_NOT_ALLOWED,
    AT_CME_PLMN_NOT_ALLOWED,
    AT_CME_LOCATION_AREA_NOT_ALLOWED,
    AT_CME_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA,

    AT_CME_SERVICE_OPTION_NOT_SUPPORTED,
    AT_CME_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED,
    AT_CME_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER,
    AT_CME_PDP_AUTHENTICATION_FAILURE,

    AT_CME_INVALID_MOBILE_CLASS,
    AT_CME_UNSPECIFIED_GPRS_ERROR,

    AT_CME_VBS_VGCS_NOT_SUPPORTED_BY_THE_NETWORK,
    AT_CME_NO_SERVICE_SUBSCRIPTION_ON_SIM,
    AT_CME_NO_SUBSCRIPTION_FOR_GROUP_ID,
    AT_CME_GROUP_ID_NOT_ACTIVATED_ON_SIM,
    AT_CME_NO_MATCHING_NOTIFICATION,
    AT_CME_VBS_VGCS_CALL_ALREADY_PRESENT,
    AT_CME_CONGESTION,
    AT_CME_NETWORK_FAILURE,
    AT_CME_UPLINK_BUSY,
    AT_CME_NO_ACCESS_RIGHTS_FOR_SIM_FILE,
    AT_CME_NO_SUBSCRIPTION_FOR_PRIORITY,
    AT_CME_OPERATION_NOT_APPLICABLE_OR_NOT_POSSIBLE,
    AT_CME_FILE_NOT_EXISTS,

    AT_CME_SERVICE_NOT_PROVISIONED,

    AT_CME_PDP_ACT_LIMIT,
    AT_CME_NET_SEL_MENU_DISABLE,

    AT_CME_CS_SERV_EXIST,

    AT_CME_FDN_FAILED,
    AT_CME_CALL_CONTROL_FAILED,
    AT_CME_CALL_CONTROL_BEYOND_CAPABILITY,

    AT_CME_NO_RF,

    AT_CME_APN_LEN_ILLEGAL,
    AT_CME_APN_SYNTACTICAL_ERROR,
    AT_CME_SET_APN_BEFORE_SET_AUTH,
    AT_CME_AUTH_TYPE_ILLEGAL,
    AT_CME_USER_NAME_TOO_LONG,
    AT_CME_USER_PASSWORD_TOO_LONG,
    AT_CME_ACCESS_NUM_TOO_LONG,
    AT_CME_CALL_CID_IN_OPERATION,
    AT_CME_BEARER_TYPE_NOT_DEFAULT,
    AT_CME_CALL_CID_INVALID,
    AT_CME_CALL_CID_ACTIVE,
    AT_CME_BEARER_TYPE_ILLEGAL,
    AT_CME_MUST_EXIST_DEFAULT_TYPE_CID,
    AT_CME_PDN_TYPE_ILLEGAL,
    AT_CME_IPV4_ADDR_ALLOC_TYPE_ILLEGAL,
    AT_CME_LINK_CID_INVALID,
    AT_CME_NO_SUCH_ELEMENT,
    AT_CME_MISSING_RESOURCE,

    AT_CME_IMS_NOT_SUPPORT,
    AT_CME_IMS_SERVICE_EXIST,
    AT_CME_IMS_VOICE_DOMAIN_PS_ONLY,
    AT_CME_IMS_STACK_TIMEOUT,

    AT_CME_1X_RAT_NOT_SUPPORTED,

    AT_CME_OPERATION_NOT_ALLOWED_IN_CL_MODE,

    AT_CME_ERROR_ENUM_END,                   /* CME ERROR ���� */

    AT_DEVICE_ERROR_BEGIN,
    AT_DEVICE_MODE_ERROR,                 /* װ��AT�������ֵ ģʽ����*/
    AT_FCHAN_BAND_NOT_MATCH,
    AT_FCHAN_SET_CHANNEL_FAIL,
    AT_FCHAN_BAND_CHANNEL_NOT_MATCH,
    AT_FCHAN_OTHER_ERR,
    AT_FDAC_CHANNEL_NOT_SET,
    AT_FDAC_SET_FAIL,
    AT_CHANNEL_NOT_SET,
    AT_FTXON_SET_FAIL,
    AT_FTXON_OTHER_ERR,
    AT_DATA_UNLOCK_ERROR,
    AT_DPAUPA_ERROR,
    AT_SN_LENGTH_ERROR,
    AT_FRXON_OTHER_ERR,
    AT_FRXON_SET_FAIL,
    AT_FPA_OTHER_ERR,
    AT_FLNA_OTHER_ERR,
    AT_FRSSI_OTHER_ERR,
    AT_FRSSI_RX_NOT_OPEN,
    AT_SD_CARD_NOT_EXIST,
    AT_SD_CARD_INIT_FAILED,
    AT_SD_CARD_OPRT_NOT_ALLOWED,
    AT_SD_CARD_ADDR_ERR,
    AT_SD_CARD_OTHER_ERR,
    AT_DEVICE_OTHER_ERROR,
    AT_PHYNUM_LENGTH_ERR,
    AT_PHYNUM_NUMBER_ERR,
    AT_PHYNUM_TYPE_ERR,
    AT_SIMLOCK_PLMN_NUM_ERR,
    AT_SIMLOCK_PLMN_MNC_LEN_ERR,

    AT_DEVICE_NOT_SUPPORT,
    AT_DEVICE_ERR_UNKNOWN,
    AT_DEVICE_INVALID_PARAMETERS,
    AT_DEVICE_NV_NOT_SUPPORT_ID,                       /* 520  NV������ */
    AT_DEVICE_NV_READ_FAILURE,                         /* 521  NV��ȡʧ�� */
    AT_DEVICE_NV_WRITE_FAIL_OVERLEN,                   /* 522  NVдʧ�ܣ����ȹ��� */
    AT_DEVICE_NV_WRITE_FAIL_BADFLASH,                  /* 523  NVдʧ�ܣ�Flash���� */
    AT_DEVICE_NV_WRITE_FAIL_UNKNOWN,                   /* 524  NVдʧ�ܣ��������� */
    AT_DEVICE_VCTCXO_OVER_HIGH,
    AT_DEVICE_UE_MODE_ERR,
    AT_DEVICE_NOT_SET_CHAN,
    AT_DEVICE_OPEN_UL_CHAN_ERROR,
    AT_DEVICE_OPEN_DL_CHAN_ERROR,
    AT_DEVICE_OPEN_CHAN_ERROR,
    AT_DEVICE_CLOSE_CHAN_ERROR,
    AT_DEVICE_OPERATION_NOT_SUPPORT,
    AT_DEVICE_INVALID_OP,
    AT_DEVICE_CHAN_BAND_INVALID,
    AT_DEVICE_SET_CHAN_INFO_FAILURE,
    AT_DEVICE_CHAN_BAND_CHAN_NOT_MAP,
    AT_DEVICE_SET_TX_POWER_FAILURE,
    AT_DEVICE_SET_PA_LEVEL_FAILURE,
    AT_DEVICE_NOT_SET_CURRENT_CHAN,                    /* ��AT_CMD_NOT_SET_CHAN�ظ�������ȥ�� */
    AT_DEVICE_CUR_APC_UNAVAILABLE,
    AT_DEVICE_SET_APC_ERR,
    AT_DEVICE_RD_APC_ERR,
    AT_DEVICE_SET_LNA_ERR,
    AT_DEVICE_NOT_OPEN_DL_CHAN,
    AT_DEVICE_NOT_OPEN_UL_CHAN,
    AT_DEVICE_NO_SIGNAL,
    AT_DEVICE_PHYNUM_LEN_ERR,
    AT_DEVICE_PHYNUM_INVALID,
    AT_DEVICE_PHYNUM_TYPE_ERR,
    AT_DEVICE_PLATFORM_INFO_UNAVAILABLE,
    AT_DEVICE_DATA_LOCK,
    AT_DEVICE_PLMN_OVER_20,
    AT_DEVICE_MNC_NUM_INVALID,
    AT_DEVICE_GET_VER_ERR,
    AT_DEVICE_PORTLOCK_ERR,
    AT_DEVICE_PWD_ERR,
    AT_DEVICE_TIMEOUT_ERR,
    AT_DEVICE_NOT_ENOUGH_MEMORY,
    AT_DEVICE_SIMM_LOCK,
    AT_DEVICE_CLOSE_UL_CHAN_FAILURE,
    AT_DEVICE_CLOSE_DL_CHAN_FAILURE,
    AT_DEVICE_NV_DATA_INVALID,

    AT_PERSONALIZATION_ERR_BEGIN,
    AT_PERSONALIZATION_IDENTIFY_FAIL,
    AT_PERSONALIZATION_SIGNATURE_FAIL,
    AT_PERSONALIZATION_DK_INCORRECT,
    AT_PERSONALIZATION_PH_PHYNUM_LEN_ERROR,
    AT_PERSONALIZATION_PH_PHYNUM_VALUE_ERROR,
    AT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR,
    AT_PERSONALIZATION_RSA_ENCRYPT_FAIL,
    AT_PERSONALIZATION_RSA_DECRYPT_FAIL,
    AT_PERSONALIZATION_GET_RAND_NUMBER_FAIL,
    AT_PERSONALIZATION_WRITE_HUK_FAIL,
    AT_PERSONALIZATION_FLASH_ERROR,
    AT_PERSONALIZATION_OTHER_ERROR,
    AT_PERSONALIZATION_ERR_END,

    AT_DEVICE_ERROR_END,

    AT_CMS_ERROR_ENUM_BEGAIN,                /* CMS ERROR ��ʼ */

    AT_CMS_UNASSIGNED_UNALLOCATED_NUMBER,
    AT_CMS_OPERATOR_DETERMINED_BARRING,
    AT_CMS_CALL_BARRED,
    AT_CMS_SHORT_MESSAGE_TRANSFER_REJECTED,
    AT_CMS_DESTINATION_OUT_OF_SERVICE,
    AT_CMS_UNIDENTIFIED_SUBSCRIBER,
    AT_CMS_FACILITY_REJECTED,
    AT_CMS_UNKNOWN_SUBSCRIBER,
    AT_CMS_NETWORK_OUT_OF_ORDER,
    AT_CMS_TEMPORARY_FAILURE,
    AT_CMS_CONGESTION,
    AT_CMS_RESOURCES_UNAVAILABLE_UNSPECIFIED,
    AT_CMS_REQUESTED_FACILITY_NOT_SUBSCRIBED,
    AT_CMS_REQUESTED_FACILITY_NOT_IMPLEMENTED,
    AT_CMS_INVALID_SHORT_MESSAGE_TRANSFER_REFERENCE_VALUE,
    AT_CMS_INVALID_MESSAGE_UNSPECIFIED,
    AT_CMS_INVALID_MANDATORY_INFORMATION,
    AT_CMS_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED,
    AT_CMS_MESSAGE_NOT_COMPATIBLE_WITH_SHORT_MESSAGE_PROTOCOL_STATE,
    AT_CMS_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED,
    AT_CMS_PROTOCOL_ERROR_UNSPECIFIED,
    AT_CMS_INTERWORKING_UNSPECIFIED,

    AT_CMS_TELEMATIC_INTERWORKING_NOT_SUPPORTED,
    AT_CMS_SHORT_MESSAGE_TYPE_0_NOT_SUPPORTED,
    AT_CMS_CANNOT_REPLACE_SHORT_MESSAGE,
    AT_CMS_UNSPECIFIED_TPPID_ERROR,
    AT_CMS_DATA_CODING_SCHEME_ALPHABET_NOT_SUPPORTED,
    AT_CMS_MESSAGE_CLASS_NOT_SUPPORTED,
    AT_CMS_UNSPECIFIED_TPDCS_ERROR,
    AT_CMS_COMMAND_CANNOT_BE_ACTIONED,
    AT_CMS_COMMAND_UNSUPPORTED,
    AT_CMS_UNSPECIFIED_TPCOMMAND_ERROR,
    AT_CMS_TPDU_NOT_SUPPORTED,
    AT_CMS_SC_BUSY,
    AT_CMS_NO_SC_SUBSCRIPTION,
    AT_CMS_SC_SYSTEM_FAILURE,
    AT_CMS_INVALID_SME_ADDRESS,
    AT_CMS_DESTINATION_SME_BARRED,
    AT_CMS_SM_REJECTEDDUPLICATE_SM,
    AT_CMS_TPVPF_NOT_SUPPORTED,
    AT_CMS_TPVP_NOT_SUPPORTED,
    AT_CMS_SIM_SMS_STORAGE_FULL,
    AT_CMS_NO_SMS_STORAGE_CAPABILITY_IN_SIM,
    AT_CMS_ERROR_IN_MS,
    AT_CMS_MEMORY_CAPACITY_EXCEEDED,
    AT_CMS_SIM_APPLICATION_TOOLKIT_BUSY,
    AT_CMS_SIM_DATA_DOWNLOAD_ERROR,
    AT_CMS_UNSPECIFIED_ERROR_CAUSE,


    AT_CMS_ME_FAILURE,
    AT_CMS_SMS_SERVICE_OF_ME_RESERVED,
    AT_CMS_OPERATION_NOT_ALLOWED,
    AT_CMS_OPERATION_NOT_SUPPORTED,
    AT_CMS_INVALID_PDU_MODE_PARAMETER,
    AT_CMS_INVALID_TEXT_MODE_PARAMETER,
    AT_CMS_U_SIM_NOT_INSERTED,
    AT_CMS_U_SIM_PIN_REQUIRED,
    AT_CMS_PH_U_SIM_PIN_REQUIRED,
    AT_CMS_U_SIM_FAILURE,
    AT_CMS_U_SIM_BUSY,
    AT_CMS_U_SIM_WRONG,
    AT_CMS_U_SIM_PUK_REQUIRED,
    AT_CMS_U_SIM_PIN2_REQUIRED,
    AT_CMS_U_SIM_PUK2_REQUIRED,
    AT_CMS_MEMORY_FAILURE,
    AT_CMS_INVALID_MEMORY_INDEX,
    AT_CMS_MEMORY_FULL,
    AT_CMS_SMSC_ADDRESS_UNKNOWN,
    AT_CMS_NO_NETWORK_SERVICE,
    AT_CMS_NETWORK_TIMEOUT,
    AT_CMS_NO_CNMA_ACKNOWLEDGEMENT_EXPECTED,
    AT_CMS_FDN_DEST_ADDR_FAILED,
    AT_CMS_FDN_SERVICE_CENTER_ADDR_FAILED,
    AT_CMS_MO_SMS_CONTROL_FAILED,
    AT_CMS_UNKNOWN_ERROR,

    AT_CMS_ERROR_ENUM_END,                  /* CME ERROR ���� */

    AT_CMOLRE_ERR_ENUM_BEGIN,               /* CMOLRE ERROR ��ʼ */
    AT_CMOLRE_METHOD_NOT_SUPPORTED,
    AT_CMOLRE_ADDITIONAL_ASSIS_DATA_REQIRED,
    AT_CMOLRE_NOT_ENOUGH_SATELLITES,
    AT_CMOLRE_UE_BUSY,
    AT_CMOLRE_NETWORK_ERROR,
    AT_CMOLRE_TOO_MANY_CONNECTIONS,
    AT_CMOLRE_TOO_MANY_USERS,
    AT_CMOLRE_FAILURE_DUE_TO_HANDOVER,
    AT_CMOLRE_INTERNET_CONN_FAILURE,
    AT_CMOLRE_MEMORY_ERROR,
    AT_CMOLRE_UNKNOWN_ERROR,
    AT_CMOLRE_ERR_ENUM_END,                 /* CMOLRE ERROR ���� */

    AT_CMD_NOT_SUPPORT,
    AT_TOO_MANY_PARA,
    AT_ABORT,

    AT_RRETURN_CODE_BUTT                    /* RETURN CODE ���� */
};

typedef VOS_UINT32 AT_RRETURN_CODE_ENUM_UINT32;


/* Added by L60609 for AT Project��2011-10-09,  End*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
�ṹ��      : AT_ENCRYPT_VOICE_STATUS_ENUM_UINT32
�ṹ˵��    : ecc�ܻ��������
  1.��    ��   : 2015��10��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
*****************************************************************************/
enum AT_ENCRYPT_VOICE_ERROR_ENUM
{

    AT_ENCRYPT_VOICE_SUCC                     = 0x0000,
    AT_ENCRYPT_VOICE_TIMEOUT,
    AT_ENCRYPT_VOICE_LOCAL_TERMINAL_NO_AUTHORITY,
    AT_ENCRYPT_VOICE_REMOTE_TERMINAL_NO_AUTHORITY,
    AT_ENCRYPT_VOICE_LOCAL_TERMINAL_ILLEGAL,
    AT_ENCRYPT_VOICE_REMOTE_TERMINAL_ILLEGAL,
    AT_ENCRYPT_VOICE_UNKNOWN_ERROR,
    AT_ENCRYPT_VOICE_SIGNTURE_VERIFY_FAILURE,
    AT_ENCRYPT_VOICE_INTERNAL_ERROR,
    AT_ENCRYPT_VOICE_MT_CALL_NOTIFICATION,

    /* XSMS����ʼԭ��ֵ */
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL     = 0x1000,
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_POOL_FULL,
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_LINK_ERR,
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_NO_TL_ACK,
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_ENCODE_ERR,
    AT_ENCRYPT_VOICE_XSMS_SEND_RESULT_UNKNOWN,

    /* ����XCALL�ڲ�ԭ��ֵ */
    AT_ENCRYPT_VOICE_SO_NEGO_FAILURE           = 0x2000,
    AT_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST,
    AT_ENCRYPT_VOICE_NO_MO_CALL,
    AT_ENCRYPT_VOICE_NO_MT_CALL,
    AT_ENCRYPT_VOICE_NO_CALL_EXIST,
    AT_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED,
    AT_ENCRYPT_VOICE_CALL_NUM_MISMATCH,
    AT_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH,
    AT_ENCRYPT_VOICE_MSG_ENCODE_FAILUE,
    AT_ENCRYPT_VOICE_MSG_DECODE_FAILUE,
    AT_ENCRYPT_VOICE_GET_TEMP_PUB_PIVA_KEY_FAILURE,
    AT_ENCRYPT_VOICE_FILL_CIPHER_TEXT_FAILURE,
    AT_ENCRYPT_VOICE_ECC_CAP_NOT_SUPPORTED,
    AT_ENCRYPT_VOICE_ENC_VOICE_MODE_UNKNOWN,
    AT_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
    AT_ENCRYPT_VOICE_CALL_RELEASED,
    AT_ENCRYPT_VOICE_CALL_ANSWER_REQ_FAILURE,
    AT_ENCRYPT_VOICE_DECRYPT_KS_FAILURE,
    AT_ENCRYPT_VOICE_FAILURE_CAUSED_BY_INCOMING_CALL,
    AT_ENCRYPT_VOICE_INIT_VOICE_FUNC_FAILURE,
    AT_ENCRYPT_VOICE_ERROR_ENUM_BUTT
};
typedef VOS_UINT32  AT_ENCRYPT_VOICE_ERROR_ENUM_UINT32;
#endif
#endif

typedef VOS_UINT8 AT_CMD_FORMAT_TYPE;
#define AT_EXTEND_CMD_TYPE          0
#define AT_BASIC_CMD_TYPE           1
#define AT_CMD_TYPE_BUTT            2


typedef VOS_UINT8 AT_CMD_OPT_TYPE;
#define AT_CMD_OPT_SET_CMD_NO_PARA  0
#define AT_CMD_OPT_SET_PARA_CMD     1
#define AT_CMD_OPT_READ_CMD         2
#define AT_CMD_OPT_TEST_CMD         3
#define AT_CMD_OPT_BUTT             4

#define AT_MAX_PARA_NUMBER                      (16)

#define AT_PARA_SCALE_MAX_LEN                   (24)
#define AT_CMD_NAME_LEN                         (50)

#if (VOS_WIN32 == VOS_OS_VER)
#define AT_PARA_MAX_LEN                         (1020)  /* +CGLA�������ַ����������Ϊ532 */
#else
#define AT_PARA_MAX_LEN                         (560)  /* +CGLA�������ַ����������Ϊ532 */
#endif

#define AT_FW_PARAM_MAX_LEN                     (40)

#define AT_FW_LEN_AT                            (2)

/* ���õ�ǰģʽΪ���ű༭ģʽ�������ģʽ */
#define AT_PARSE_SMS_CMD_MODE_SET(ucIndex, mode)     (g_stParseContext[ucIndex].ucMode = mode)

typedef struct
{
    VOS_UINT32 ulParaValue;
    VOS_UINT8  aucPara[AT_PARA_MAX_LEN + 1];     /* �������ý������Ĳ����ַ��� */
    VOS_UINT8  aucReserved[1];
    VOS_UINT16 usParaLen;                        /* ������ʶ�����ַ������� */
}AT_PARSE_PARA_TYPE_STRU;

typedef VOS_UINT32 (*pAtChkFuncType)(AT_PARSE_PARA_TYPE_STRU *pPara);

#define AT_STRCMP(Str1, Str2 )  VOS_StrCmp(Str1, Str2 )
#define AT_STRLEN(Str)          VOS_StrLen(Str)
#define AT_STRSTR(Str1, Str2 )  VOS_StrStr(Str1, Str2 )

/* ������� */
#define AT_MAX_NUM_COMBINE_CMD      40   /* һ��AT�������ɷֽ�Ϊ40���������(refer to Q) */
#define AT_MAX_LEN_COMBINE_CMD      545  /* һ���������������545���ַ�(refer to Q) */

#define AT_DIE_SN_LEN                  (20) /* DIE SN 16���� 20�ֽڳ��� */
#define AT_CHIP_SN_LEN                 (4)  /* CHIP SN 16���� 8�ֽڳ��� */

typedef struct
{
    VOS_UINT32 ulLen;
    VOS_UINT8  ucData[0];
}AT_FW_COMBINE_CMD_STRU;

typedef struct{
    AT_FW_COMBINE_CMD_STRU* pstCombCmd;
    HI_LIST_S stCombCmdList;
}AT_FW_COMBINE_CMD_NODE_STRU;


typedef struct{
    VOS_UINT16                          usTotalNum;
    VOS_UINT16                          usProcNum;
    VOS_UINT8                           aucReserved[4];
    HI_LIST_S                           stCombineCmdList;                       /* AT_FW_COMBINE_CMD_NODE_STRU */
}AT_FW_COMBINE_CMD_INFO_STRU;

typedef struct
{
    VOS_UINT32  ulSmall;
    VOS_UINT32  ulBig;
}AT_PARA_NUM_RANGE_STRU;

typedef struct
{
    VOS_UINT8                           aucCmdName[AT_CMD_NAME_LEN + 1];        /* �������ý�������������ԭ�ַ��� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usCmdNameLen;                           /* ������ʶ�����ַ������� */
}AT_PARSE_CMD_NAME_TYPE_STRU;

typedef struct
{
    VOS_UINT8 auStrRange[AT_MAX_PARA_NUMBER][AT_PARA_SCALE_MAX_LEN + 1];
    AT_PARA_NUM_RANGE_STRU      astParaNumRange[AT_MAX_PARA_NUMBER];
    AT_PARSE_CMD_NAME_TYPE_STRU stCmdName;

    VOS_UINT8 ucParaNumRangeIndex;
    VOS_UINT8 ucParaStrRangeIndex;
    VOS_UINT8 ucParaCheckIndex;
    VOS_UINT8 ucParaIndex;

    AT_CMD_OPT_TYPE     ucCmdOptType;
    AT_CMD_FORMAT_TYPE  ucCmdFmtType;
    VOS_UINT8                           aucReserved[2];
}AT_PARSECMD_STRU;


typedef VOS_UINT32 AT_STATUS;
#define AT_FW_CLIENT_STATUS_READY           (0)
#define AT_FW_CLIENT_STATUS_PEND            (1)

/* ����������� */
typedef VOS_UINT32 (*PFN_AT_FW_CMD_PROC)(VOS_UINT8 ucClientId);

/* �����첽���������� */
typedef VOS_UINT32 (*PFN_AT_FW_MSG_PROC)(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock);


#define CMD_TBL_E5_IS_LOCKED        (0x00000001)    /* ����E5�������Ƶ����� */
#define CMD_TBL_PIN_IS_LOCKED       (0x00000002)    /* ����PIN���������Ƶ����� */
#define CMD_TBL_IS_E5_DOCK          (0x00000004)    /* E5 DOCK���� */
#define CMD_TBL_CLAC_IS_INVISIBLE   (0x00000008)    /* +CLAC�����в������ʾ������ */

#define CMD_TBL_LIMITED_NULL        (0x00000000)    /* ��õ�,��E5 PIN�����Ƶ����� */

#define CMD_TBL_NO_LIMITED          (CMD_TBL_E5_IS_LOCKED|CMD_TBL_PIN_IS_LOCKED)    /* ���κ����Ƶ����� */

/* E5��̬����Stick��̬��CLAC����ʾ�������ͬ����:
   E5:
   +CSIM ^CPDW ^CMLCK ^IMSICHG ^PDPSTUB ^CCC ^COMM ^CAATT ^CELLSRCH ^VMSET ^CDTMFS ^CDTMFE ^DOCK
   S6, S7, T, P, X, Q, &C, &D
   Stick:
   +CBC ^DIALMODE ^PORTSEL ^U2DIAG ^GETPORTMODE ^AT2OM

   ��ͬ����:
   +CEER +CTFR ^CMSTUB ^CMGSSEG ^CMMI ^FLOWRPTCTRL ^CCIN ^STPD   ^STMN  ^STTR ^STEN  ^CARD  ^CSND ^CMST ^TEST
   ^CMM  ^BOOT $QCDMG  ^CIMEI   ^DWINS ^USSDMODE   ^RSSI ^CVOICE ^DDSETEX ^YJCX ^ADCTEMP ^SETPID ^CGAUTH
*/
/* ����ʾ����������ͬ����Ȼʹ�� CMD_TBL_CLAC_IS_INVISIBLE����ʶ
   ����ʾ��������E5���е�ʹ�����涨��ĺ� CMD_TBL_CLAC_IS_INVISIBLE_E5
   ����ʾ��������STICK���е�ʹ�����涨��ĺ� CMD_TBL_CLAC_IS_INVISIBLE_STICK
*/

/*�������⣬CLAC�ڲ�ͬ��̬�����ʵ�� */
#define CMD_TBL_CLAC_IS_INVISIBLE_E5         CMD_TBL_LIMITED_NULL         /* E5��̬��+CLAC�����в������ʾ������ */
#define CMD_TBL_CLAC_IS_INVISIBLE_STICK      CMD_TBL_LIMITED_NULL          /* STICK��̬��+CLAC�����в������ʾ������ */

/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */

#if (FEATURE_ON == FEATURE_LTE)
#define CGDCONT_CMD_PARA_STRING         "(0-31),(\"IP\",\"IPV6\",\"IPV4V6\",\"PPP\",\"\"),(APN),(PdpAddr),(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)"
#else
#define CGDCONT_CMD_PARA_STRING         "(1-11),(\"IP\",\"IPV6\",\"IPV4V6\",\"PPP\",\"\"),(APN),(PdpAddr),(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define CGDSCONT_CMD_PARA_STRING        "(1-31),(0-31),(0-2),(0-3)"
#else
#define CGDSCONT_CMD_PARA_STRING        "(1-11),(0-11),(0-2),(0-3)"
#endif  /* FEATURE_ON == FEATURE_LTE */
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

#if (FEATURE_ON == FEATURE_LTE)
#define CGTFT_CMD_PARA_STRING           "(1-31),(1-16),(0-255),(IpMask),(0-255),(Dpr),(Spr),(0-4294967295),(TosM),(0-1048575),(0-3),(LocalIpMask)"
#else
#define CGTFT_CMD_PARA_STRING           "(1-11),(1-16),(0-255),(IpMask),(0-255),(Dpr),(Spr),(0-4294967295),(TosM),(0-1048575),(0-3)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define CGACT_CMD_PARA_STRING           "(0,1),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31)"
#else
#define CGACT_CMD_PARA_STRING           "(0,1),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define CGCMOD_CMD_PARA_STRING          "(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31)"
#else
#define CGCMOD_CMD_PARA_STRING          "(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define CGPADDR_CMD_PARA_STRING         "(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31)"
#else
#define CGPADDR_CMD_PARA_STRING         "(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define CGEQNEG_CMD_PARA_STRING         "(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31)"
#else
#define CGEQNEG_CMD_PARA_STRING         "(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */


#if (FEATURE_ON == FEATURE_LTE)
#define CGANS_CMD_PARA_STRING           "(0,1),(\"NULL\"),(1-31)"
#else
#define CGANS_CMD_PARA_STRING           "(0,1),(\"NULL\"),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#define CGANS_EXT_CMD_PARA_STRING       "(0,1)"

#if (FEATURE_ON == FEATURE_LTE)
#define CGDATA_CMD_PARA_STRING          "(\"NULL\"),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31),(1-31)"
#else
#define CGDATA_CMD_PARA_STRING          "(\"NULL\"),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11),(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#define AUTHDATA_CMD_PARA_STRING        "(0-31),(0-2),(PLMN),(PASSWORD),(USERNAME)"
#else
#define AUTHDATA_CMD_PARA_STRING        "(1-11),(0-2),(PLMN),(PASSWORD),(USERNAME)"
#endif  /* FEATURE_ON == FEATURE_LTE */


#if (FEATURE_ON == FEATURE_LTE)
#if (PS_UE_REL_VER < PS_PTL_VER_R5)
#define CGEQREQ_CMD_PARA_STRING         "(1-31),(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-31),(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#elif (PS_UE_REL_VER <= PS_PTL_VER_R6)
#define CGEQREQ_CMD_PARA_STRING         "(1-31),(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-31),(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#else
#define CGEQREQ_CMD_PARA_STRING         "(1-31),(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-31),(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#endif  /* PS_UE_REL_VER < PS_PTL_VER_R5 */

#else
#if (PS_UE_REL_VER < PS_PTL_VER_R5)
#define CGEQREQ_CMD_PARA_STRING         "(1-11),(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-11),(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#elif (PS_UE_REL_VER <= PS_PTL_VER_R6)
#define CGEQREQ_CMD_PARA_STRING         "(1-11),(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-11),(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#else
#define CGEQREQ_CMD_PARA_STRING         "(1-11),(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_CMD_PARA_STRING         "(1-11),(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#endif  /* PS_UE_REL_VER < PS_PTL_VER_R5 */

#endif  /* FEATURE_ON == FEATURE_LTE */


#if (PS_UE_REL_VER < PS_PTL_VER_R5)
#define CGEQREQ_TEST_CMD_PARA_STRING    "(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_TEST_CMD_PARA_STRING    "(0-4),(0-8640),(0-8640),(0-8640),(0-8640),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"

#elif (PS_UE_REL_VER <= PS_PTL_VER_R6)
#define CGEQREQ_TEST_CMD_PARA_STRING    "(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_TEST_CMD_PARA_STRING    "(0-4),(0-2048),(0-16000),(0-2048),(0-16000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"

#else
#define CGEQREQ_TEST_CMD_PARA_STRING    "(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#define CGEQMIN_TEST_CMD_PARA_STRING    "(0-4),(0-11480),(0-42000),(0-11480),(0-42000),(0-2),(0-1520),(\"0E0\",\"1E2\",\"7E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"1E1\"),(\"0E0\",\"5E2\",\"1E2\",\"5E3\",\"4E3\",\"1E3\",\"1E4\",\"1E5\",\"1E6\",\"6E8\"),(0-3),(0-4100),(0-3),(0-1),(0-1)"
#endif


#if (FEATURE_ON == FEATURE_LTE)
#define NDISDUP_TEST_CMD_PARA_STRING    "(1-20),(0,1),(apn),(username),(passwd),(0,1,2,3),(ipAddr),(0-63)"
#else
#define NDISDUP_TEST_CMD_PARA_STRING    "(1-16),(0,1),(apn),(username),(passwd),(0,1,2,3),(ipAddr),(0-63)"
#endif


#if (FEATURE_ON == FEATURE_LTE)
#define NDISCONN_TEST_CMD_PARA_STRING    "(1-20),(0,1),(apn),(username),(passwd),(0-65535)"
#else
#define NDISCONN_TEST_CMD_PARA_STRING    "(1-16),(0,1),(apn),(username),(passwd),(0-65535)"
#endif

#if (FEATURE_ON == FEATURE_LTE)
#define DNSQUERY_TEST_CMD_PARA_STRING   "(1-31)"
#else
#define DNSQUERY_TEST_CMD_PARA_STRING   "(1-11)"
#endif  /* FEATURE_ON == FEATURE_LTE */

#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (MULTI_MODEM_NUMBER == 3)
#define CHDATA_TEST_CMD_PARA_STRING   "(1-31),(1-7)"
#else
#define CHDATA_TEST_CMD_PARA_STRING   "(1-31),(1-5)"
#endif
#else
#define CHDATA_TEST_CMD_PARA_STRING   "(1-31),(1-3)"
#endif
#else
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (MULTI_MODEM_NUMBER == 3)
#define CHDATA_TEST_CMD_PARA_STRING   "(1-11),(1-7)"
#else
#define CHDATA_TEST_CMD_PARA_STRING   "(1-11),(1-5)"
#endif
#else
#define CHDATA_TEST_CMD_PARA_STRING   "(1-11),(1-3)"
#endif
#endif  /* FEATURE_ON == FEATURE_LTE */

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_IPV6)
#define PDPROFMOD_CMD_PARA_STRING       "(1-31),(\"IP\",\"IPV6\",\"IPV4V6\",\"\"),(APN),(username),(passwd),(0-2)"
#else
#define PDPROFMOD_CMD_PARA_STRING       "(1-31),(\"IP\",\"\"),(APN),(username),(passwd),(0-2)"
#endif  /* FEATURE_ON == FEATURE_IPV6 */
#else
#if (FEATURE_ON == FEATURE_IPV6)
#define PDPROFMOD_CMD_PARA_STRING       "(1-11),(\"IP\",\"IPV6\",\"IPV4V6\",\"\"),(APN),(username),(passwd),(0-2)"
#else
#define PDPROFMOD_CMD_PARA_STRING       "(1-31),(\"IP\",\"\"),(APN),(username),(passwd),(0-2)"
#endif  /* FEATURE_ON == FEATURE_IPV6 */
#endif  /* FEATURE_ON == FEATURE_LTE */
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں�*/

#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
#define MBMSCMD_CMD_PARA_STRING         "(\"MBMS_SERVICE_ENABLER\",\"ACTIVATE\",\"DEACTIVATE\",\"DEACTIVATE_ALL\",\"MBMS_PREFERENCE\",\"SIB16_GET_NETWORK_TIME\",\"BSSI_SIGNAL_LEVEL\",\"NETWORK_INFORMATION\",\"MODEM_STATUS\"),(@paramone),(paramtwo)"
#endif



#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (MULTI_MODEM_NUMBER == 3)
#define SCICHG_CMD_PARA_STRING          "(0-2),(0-2),(0-2)"
#else
#define SCICHG_CMD_PARA_STRING          "(0-1),(0-1)"
#endif
#else
#define SCICHG_CMD_PARA_STRING          "(0-1),(0-1)"
#endif

/* �����Ԫ�ض���
   --------------------ulChkFlag------------------------------------------
  | bit31......bit4 |    bit3    |    bit2    |    bit1    |    bit0    |
  |       ����      |CLAC�Ƿ���ʾ|E5 DOCK���� |SIM�������� | E5���뱣�� |
   -----------------------------------------------------------------------
 */
 /*lint -e958 �޸���:l60609;ԭ��:64bit*/
 typedef struct
{
    VOS_UINT32 ulCmdIndex;

    PFN_AT_FW_CMD_PROC   pfnSetProc;
    VOS_UINT32 ulSetTimeOut;

    PFN_AT_FW_CMD_PROC   pfnQryProc;
    VOS_UINT32 ulQryTimeOut;

    PFN_AT_FW_CMD_PROC   pfnTestProc;
    VOS_UINT32 ulTestTimeOut;

    PFN_AT_FW_CMD_PROC   pfnAbortProc;  /* ��Ϻ��� */
    VOS_UINT32 ulAbortTimeOut;          /* ��϶�ʱ�� */

    VOS_UINT32 ulParamErrCode;  /* ��������ʧ��ʱ�Ĵ����� */
    VOS_UINT32 ulChkFlag;

    const VOS_UINT8* pszCmdName;
    const VOS_UINT8* pszParam;
} AT_PAR_CMD_ELEMENT_STRU;
/*lint +e958 �޸���:l60609;ԭ��:64bit*/


/* SMS����ű����� */
/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    VOS_UINT32 ulCmdIndex;

    PFN_AT_FW_CMD_PROC   pfnSetProc;
    VOS_UINT32 ulSetTimeOut;

    PFN_AT_FW_CMD_PROC   pfnTestProc;
    VOS_UINT32 ulTestTimeOut;

    PFN_AT_FW_CMD_PROC      pfnAbortProc;
    VOS_UINT32              ulAbortTimeOut;

    VOS_UINT32 ulParamErrCode;      /* ��������ʧ��ʱ�Ĵ����� */
    VOS_UINT32 ulChkFlag;

    const VOS_UINT8* pszCmdName;
    const VOS_UINT8* ParaText;           /* �ı������ű� */
    const VOS_UINT8* ParaPDU;            /* PDU�����ű� */
}AT_SMS_CMD_TAB_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/


typedef struct tagAT_PAR_CMDTBL_LIST_STRU
{
    VOS_UINT16                          usCmdNum;
    VOS_UINT16                          usReserved;
    VOS_UINT8                           aucReserved[4];
    AT_PAR_CMD_ELEMENT_STRU*            pstCmdElement;
    HI_LIST_S                           stCmdTblList;
} AT_PAR_CMDTBL_LIST_STRU;

/*lint -e958 -e959 �޸���:l60609;ԭ��:64bit*/
typedef struct
{
    VOS_UINT8 ucClientStatus;    /* AT_FW_CLIENT_STATUS_READY/PEND */

    VOS_UINT8 ucMode;            /* AT_CMD_MODE/AT_SMS_MODE  */

    VOS_UINT16 usReserved1;

    VOS_UINT16 usDataLen;                        /* ָʾ��ǰAT����泤�� */
    VOS_UINT16 usCmdLineLen;                     /* CMD line����buffer���� */

    VOS_UINT8 aucDataBuff[AT_CMD_MAX_LEN];       /* ָʾ��ǰAT������� */

    VOS_UINT8* pucCmdLine;                       /* CMD line����buffer������"A/"�ظ�ִ����һ������ */

    AT_FW_COMBINE_CMD_INFO_STRU stCombineCmdInfo;   /* ���������Ϣ��¼ */

    VOS_UINT8* pBlockCmd;                        /* ������������Ļ����� */
    VOS_UINT16 usBlockCmdLen;                    /* ������������Ļ��泤�� */

    VOS_UINT16 usReserved2;

    AT_PAR_CMD_ELEMENT_STRU* pstCmdElement;

    HTIMER hTimer;
} AT_PARSE_CONTEXT_STRU;
/*lint +e958 +e959 �޸���:l60609;ԭ��:64bit*/

#define AT_PARA_MAX_NUM                         AT_MAX_PARA_NUMBER

/*extern HI_LIST_S g_stCmdTblList; */

/* Added by L60609 for AT Project��2011-10-09,  Begin*/
extern TAF_UINT32   At_UpString(TAF_UINT8 *pData,TAF_UINT16 usLen);
extern TAF_UINT32   At_Auc2ul(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn);

extern AT_PARSECMD_STRU                     g_stATParseCmd;
extern AT_PARSE_CONTEXT_STRU                g_stParseContext[AT_MAX_CLIENT_NUM];
extern AT_PARSE_PARA_TYPE_STRU              gastAtParaList[AT_MAX_PARA_NUMBER];
extern TAF_UINT8                            gucAtParaIndex;


/* ��ܺ��Ľӿ� */
extern VOS_UINT32 AT_RegisterCmdTable(const AT_PAR_CMD_ELEMENT_STRU* pstCmdTblEntry, VOS_UINT16 usCmdNum);

/* sprintf */
/*lint -e960 �޸���:l60609;ԭ��:64bit*/
extern VOS_INT32 atSprintf(VOS_INT32 MaxLength, VOS_UINT8 *pHeadAddr, VOS_UINT8 *pCurrAddr, const VOS_UINT8 *fmt,...);
/*lint +e960 �޸���:l60609;ԭ��:64bit*/

extern VOS_UINT32 atParseExtendCmd( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 ParseDCmdPreProc( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 atParseSCmd( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 atParseBasicCmd( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 atParsePara( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 atParseDMCmd( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 At_CombineCmdChkProc(VOS_UINT8 ucClientId,  VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);

extern VOS_UINT32 CmdParseProc(VOS_UINT8 ucClientId,  VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);

extern VOS_UINT32 AT_ParseCmdType( VOS_UINT8 * pData, VOS_UINT16 usLen);

extern VOS_UINT32 atMatchCmdName (VOS_UINT8 ucClientId, VOS_UINT32 CmdType);
extern VOS_VOID At_CombCmdProcAfterCmd(VOS_UINT8 ucClientId);

extern VOS_BOOL At_CombCmdisFinal(VOS_UINT8 ucIndex);

extern VOS_VOID At_ResetCombinCmdInfo(HI_LIST_S* pstCombList);

extern VOS_VOID At_ResetCombinParseInfo(VOS_UINT8 ucIndex);

extern VOS_UINT32 At_CombineCmdProc(VOS_UINT8 ucClientId);

extern VOS_VOID At_ParseInit(VOS_VOID);

extern VOS_VOID AT_ParseCmdOver(VOS_UINT8 ucIndex);

extern VOS_VOID AT_CheckProcBlockCmd(VOS_VOID);

extern VOS_UINT32 AT_FwSendClientMsg(VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgId, VOS_UINT16 usMsgParamSize, VOS_VOID* pMsgParam);

extern VOS_UINT8* At_GetFirstBasicCmdAddr(VOS_UINT8 *pData, VOS_UINT32* pulLen);

extern VOS_VOID AT_BlockCmdTimeOutProc(VOS_UINT8 ucIndex);

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
extern VOS_UINT32 AT_SDParamErrCode(VOS_VOID);
/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */


VOS_UINT32 AT_IsAbortCmdStr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

VOS_VOID AT_AbortCmdProc(
    VOS_UINT8                           ucIndex
);


VOS_VOID AT_SaveCmdElementInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
);


VOS_VOID AT_ClearBlockCmdInfo(VOS_UINT8 ucIndex);

VOS_UINT32 AT_IsAnyParseClientPend(VOS_VOID);

VOS_UINT32 AT_IsAllClientDataMode(VOS_VOID);


extern VOS_UINT8 atCmdIsSupportedByCLMode(VOS_UINT8 ucIndex);
#if ((VOS_OS_VER == VOS_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*__ATPARSE_H__*/

