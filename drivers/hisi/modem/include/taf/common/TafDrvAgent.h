

#ifndef __ATAGENT_H__
#define __ATAGENT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"

#include "AtMnInterface.h"
#include "TafAppMma.h"
#include "mdrv.h"

#include "AtPhyInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define AT_MAX_VERSION_LEN              (128)                 /* �汾��Ϣ��󳤶� */


#define AT_MAX_PDM_VER_LEN              (16)                                    /* PDM�汾�ŵ���󳤶� */

#define TAF_DLOAD_INFO_LEN              (1024)

#define TAF_AUTH_ID_LEN                 (50)

#define AT_DLOAD_TASK_DELAY_TIME        (500)

#define TAF_MAX_VER_INFO_LEN            (6)

#define TAF_MAX_PROPLAT_LEN             (63)                                    /*���ƽ̨����汾����*/

#define TAF_AUTHORITY_LEN               (50)                                    /* AUTHORITYVER�������������� */

#define AT_AGENT_DRV_VERSION_TIME_LEN   (32)                                    /* ����ӿ�DRV_GET_VERSION_TIME����ʱ���ַ�����󳤶� */


/* Added by L60609 for AT Project��2011-10-09,  Begin*/
#define TAF_MAX_FLAFH_INFO_LEN          (255)

#define TAF_MAX_GPIO_INFO_LEN           (32)
/* Added by L60609 for AT Project��2011-10-09,  End*/

/*Ӳ���汾����󳤶�*/
#define DRV_AGENT_MAX_MODEL_ID_LEN      (31)
#define DRV_AGENT_MAX_REVISION_ID_LEN   (31)

/* MS֧�ֵĽ��շּ����Ͷ��� */
#define DRV_AGENT_MS_SUPPORT_RX_DIV_2100           (0x0001)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_1900           (0x0002)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_1800           (0x0004)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_AWS_1700       (0x0008)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_850            (0x0010)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_800            (0x0020)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_2600           (0x0040)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_900            (0x0080)
#define DRV_AGENT_MS_SUPPORT_RX_DIV_IX_1700        (0x0100)

#define DRV_AGENT_DSP_RF_SWITCH_ON      (1)

#define DRV_AGENT_SIMLOCK_MAX_ERROR_TIMES  (3)  /* Simlock�������ʧ�ܴ��� */

/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
#define  AT_PID_MEM_INFO_LEN                        (150) /* VOS�ڴ��ѯʱ֧�ֵ����PID���� */

#define  AT_KB_TO_BYTES_NUM                         (1024) /* KB���ֽ�ת�����1024 */
/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */



#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/* ��ǿSHELL�����뱣����ض��� */
#define AT_SHELL_PWD_LEN                (8)
#endif

/* �趨һ������ֵ100�����ǵ�PAD ��NANDΪ256MB������block sizeΪ128kB������2048�飬
   ������һ��Ҫ����5%��Ϊ�Ǻϸ��FLASH����2048*5%=102.4��ȡ100Ϊ����������ޣ���
   ���������������100������ֻ���ǰ100����������������������л���������
   �����ص�<totalNum>�԰���ʵ���ܿ��������
 */
#define DRV_AGENT_NAND_BADBLOCK_MAX_NUM (100)

#define DRV_AGENT_CHIP_TEMP_ERR         (65535)

#define DRV_AGENT_HUK_LEN                       (16)        /* HUKΪ128Bits������, ����Ϊ16Bytes */
#define DRV_AGENT_PUBKEY_LEN                    (520)       /* ��Ȩ��Կ����, ����Ϊ520Bytes */
#define DRV_AGENT_PUBKEY_SIGNATURE_LEN          (32)        /* ��Ȩ��ԿSSKǩ������ */
#define DRV_AGENT_RSA_CIPHERTEXT_LEN            (128)       /* RSA���ĳ���, ͳһΪ128Bytes */
#define DRV_AGENT_SUPPORT_CATEGORY_NUM          (3)         /* ֧�ֵ���������CATEGORY�������Ŀǰֻ֧������:network/network subset/SP */
#define DRV_AGENT_PH_LOCK_CODE_GROUP_NUM        (20)        /* ���������Ŷ����� */
#define DRV_AGENT_PH_LOCK_CODE_LEN              (4)         /* ���������Ŷγ��� */
#define DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN     (548)       /* ��������������������ṹ�峤�� */
#define DRV_AGENT_PH_PHYNUM_LEN                 (16)        /* ����ų��� */
#define DRV_AGENT_PH_PHYNUM_IMEI_LEN            (15)        /* IMEI�ų��� */
#define DRV_AGENT_PH_PHYNUM_IMEI_NV_LEN         (16)        /* IMEI��NV��� */
#define DRV_AGENT_PH_PHYNUM_SN_LEN              (16)        /* SN���� */
#define DRV_AGENT_PH_PHYNUM_SN_NV_LEN           (DRV_AGENT_PH_PHYNUM_SN_LEN+4)  /* SN��NV��� */
#define DRV_AGENT_PORT_PASSWORD_LEN             (16)        /* ����ͨ�Ŷ˿������볤�� */

#define DRV_AGENT_DH_PUBLICKEY_LEN              (128)       /* DH�㷨ʹ�õķ�������Կ��Modem�๫Կ���� */
#define DRV_AGENT_DH_PRIVATEKEY_LEN             (48)        /* DH�㷨ʹ�õ�Modem��˽Կ���� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : DRV_AGENT_TSELRF_SET_ERROR_ENUM
 �ṹ˵��  : ^TSELRF �������ò�������������б�
             0: DRV_AGENT_TSELRF_SET_ERROR_NO_ERROR ���ò����ɹ���
             1: DRV_AGENT_TSELRF_SET_ERROR_LOADDSP  ���ò���ʧ�ܣ�
*****************************************************************************/
enum DRV_AGENT_TSELRF_SET_ERROR_ENUM
{
    DRV_AGENT_TSELRF_SET_NO_ERROR      = 0,
    DRV_AGENT_TSELRF_SET_LOADDSP_FAIL,

    DRV_AGENT_TSELRF_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_TSELRF_SET_ERROR_ENUM_UINT32;


/*****************************************************************************
 ö����    : DRV_AGENT_HKADC_GET_ERROR_ENUM
 �ṹ˵��  : ��ȡHKADC��ѹ��������������б�
             0: DRV_AGENT_HKADC_GET_NO_ERROR�����ɹ���
             1: DRV_AGENT_HKADC_GET_FAIL         ����ʧ�ܣ�
*****************************************************************************/
enum DRV_AGENT_HKADC_GET_ERROR_ENUM
{
    DRV_AGENT_HKADC_GET_NO_ERROR      = 0,
    DRV_AGENT_HKADC_GET_FAIL,

    DRV_AGENT_HKADC_GET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HKADC_GET_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_USIMWRITESTUB_SET_ERROR_ENUM
 �ṹ˵��  : USIMWRITESTUB �������ò�������������б�
             0: ���ò����ɹ���
             1: ���ò���ʧ�ܣ�
*****************************************************************************/
enum DRV_AGENT_ERROR_ENUM
{
    DRV_AGENT_NO_ERROR      = 0,
    DRV_AGENT_ERROR,
    DRV_AGENT_PARAM_ERROR,
    DRV_AGENT_CME_ERROR,
    DRV_AGENT_CME_RX_DIV_OTHER_ERR,
    DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED,
    DRV_AGENT_CME_RX_DIV_BAND_ERR,

    DRV_AGENT_BUTT
};
typedef VOS_UINT32 DRV_AGENT_ERROR_ENUM_UINT32;


/*****************************************************************************
 ö����    : DRV_AGENT_MSID_QRY_ERROR_ENUM
 �ṹ˵��  : ���õ���ӿڲ�ѯMS ID����ö��

  1.��    ��   : 2011��10��22��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
enum DRV_AGENT_MSID_QRY_ERROR_ENUM
{
    DRV_AGENT_MSID_QRY_NO_ERROR                  = 0,
    DRV_AGENT_MSID_QRY_READ_PRODUCT_ID_ERROR     = 1,
    DRV_AGENT_MSID_QRY_READ_SOFT_VER_ERROR       = 2,
    DRV_AGENT_MSID_QRY_BUTT
};
typedef VOS_UINT32  DRV_AGENT_MSID_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_APPDMVER_QRY_ERROR_ENUM
 �ṹ˵��  : APPDMVER�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_APPDMVER_QRY_ERROR_ENUM
{
    DRV_AGENT_APPDMVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_APPDMVER_QRY_ERROR         = 1,

    DRV_AGENT_APPDMVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM
 �ṹ˵��  : DLOADINFO�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM
{
    DRV_AGENT_DLOADINFO_QRY_NO_ERROR      = 0,
    DRV_AGENT_DLOADINFO_QRY_ERROR         = 1,

    DRV_AGENT_DLOADINFO_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM
 �ṹ˵��  : AUTHORITYVER�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHORITYVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHORITYVER_QRY_ERROR         = 1,

    DRV_AGENT_AUTHORITYVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM
 �ṹ˵��  : AUTHORITYID�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHORITYID_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHORITYID_QRY_ERROR         = 1,

    DRV_AGENT_AUTHORITYID_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_GODLOAD_SET_ERROR_ENUM
 �ṹ˵��  : GODLOAD_�������ò�������������б�
             0: ���ò����ɹ���
             1: ���ò���ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_GODLOAD_SET_ERROR_ENUM
{
    DRV_AGENT_GODLOAD_SET_NO_ERROR      = 0,
    DRV_AGENT_GODLOAD_SET_ERROR         = 1,

    DRV_AGENT_GODLOAD_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_GODLOAD_SET_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_SDLOAD_SET_ERROR_ENUM
 �ṹ˵��  : SDLOAD_�������ò�������������б�
             0: ���ò����ɹ���
             1: ���ò���ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_SDLOAD_SET_ERROR_ENUM
{
    DRV_AGENT_SDLOAD_SET_NO_ERROR      = 0,
    DRV_AGENT_SDLOAD_SET_ERROR         = 1,

    DRV_AGENT_SDLOAD_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_SDLOAD_SET_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM
 �ṹ˵��  : HWNATQRY_�������ò�������������б�
             0: ���ò����ɹ���
             1: ���ò���ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM
{
    DRV_AGENT_HWNATQRY_QRY_NO_ERROR      = 0,
    DRV_AGENT_HWNATQRY_QRY_ERROR         = 1,

    DRV_AGENT_HWNATQRY_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM_UINT32;

/* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
/*****************************************************************************
 ö����    : DRV_AGENT_CPULOAD_QRY_ERROR_ENUM
 �ṹ˵��  : CPULOAD�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��11��12��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_CPULOAD_QRY_ERROR_ENUM
{
    DRV_AGENT_CPULOAD_QRY_NO_ERROR      = 0,
    DRV_AGENT_CPULOAD_QRY_ERROR         = 1,

    DRV_AGENT_CPULOAD_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_CPULOAD_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM
 �ṹ˵��  : MFREELOCKSIZE�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��11��12��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM
{
    DRV_AGENT_MFREELOCKSIZE_QRY_NO_ERROR      = 0,
    DRV_AGENT_MFREELOCKSIZE_QRY_ERROR         = 1,

    DRV_AGENT_MFREELOCKSIZE_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM_UINT32;

/* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */

/*****************************************************************************
 ö����    : DRV_AGENT_AUTHVER_QRY_ERROR_ENUM
 �ṹ˵��  : AUTHVER_�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_AUTHVER_QRY_ERROR_ENUM
{
    DRV_AGENT_AUTHVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_AUTHVER_QRY_ERROR         = 1,

    DRV_AGENT_AUTHVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_AUTHVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM
 �ṹ˵��  : FLASHINFO_�����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM
{
    DRV_AGENT_FLASHINFO_QRY_NO_ERROR      = 0,
    DRV_AGENT_FLASHINFO_QRY_ERROR         = 1,

    DRV_AGENT_FLASHINFO_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_PFVER_QRY_ERROR_ENUM
 �ṹ˵��  : PFVER_�����ѯ��������������б�
            0: ��ѯ�����ɹ���
            1: ��ȡ�汾��ʱ��ʧ��
            2: ��ȡ�汾ʧ��
1.��    ��   : 2011��10��4��
  ��    ��   : f62575
  �޸�����   : �����ɺ���
*****************************************************************************/
enum DRV_AGENT_PFVER_QRY_ERROR_ENUM
{
    DRV_AGENT_PFVER_QRY_NO_ERROR                 = 0,
    DRV_AGENT_PFVER_QRY_ERROR_GET_VERSION_TIME   = 1,
    DRV_AGENT_PFVER_QRY_ERROR_GET_VERSION        = 2,
    DRV_AGENT_PFVER_QRY_ERROR_ALLOC_MEM          = 3,

    DRV_AGENT_PFVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PFVER_QRY_ERROR_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_DLOADVER_QRY_ERROR_ENUM
 �ṹ˵��  : DLOADVER �����ѯ��������������б�
             0: ��ѯ�����ɹ���
             1: ��ѯ����ʧ�ܣ�
*****************************************************************************/
enum DRV_AGENT_DLOADVER_QRY_ERROR_ENUM
{
    DRV_AGENT_DLOADVER_QRY_NO_ERROR      = 0,
    DRV_AGENT_DLOADVER_QRY_ERROR         = 1,

    DRV_AGENT_DLOADVER_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DLOADVER_QRY_ERROR_ENUM_UINT32;


/*****************************************************************************
 ö����    : DRV_AGENT_PERSONALIZATION_ERROR_ENUM
 �ṹ˵��  : ���������������б�

  1.��    ��   : 2012��04��07��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_ERR_ENUM
{
    DRV_AGENT_PERSONALIZATION_NO_ERROR         = 0,             /* �����ɹ� */
    DRV_AGENT_PERSONALIZATION_IDENTIFY_FAIL,                    /* ���߼�Ȩʧ�� */
    DRV_AGENT_PERSONALIZATION_SIGNATURE_FAIL,                   /* ǩ��У��ʧ�� */
    DRV_AGENT_PERSONALIZATION_DK_INCORRECT,                     /* �˿�������� */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_LEN_ERROR,              /* ����ų��ȴ��� */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_VALUE_ERROR,            /* ���������� */
    DRV_AGENT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR,             /* ��������ʹ��� */
    DRV_AGENT_PERSONALIZATION_RSA_ENCRYPT_FAIL,                 /* RSA����ʧ�� */
    DRV_AGENT_PERSONALIZATION_RSA_DECRYPT_FAIL,                 /* RSA����ʧ�� */
    DRV_AGENT_PERSONALIZATION_GET_RAND_NUMBER_FAIL,             /* ��ȡ�����ʧ��(crypto_rand) */
    DRV_AGENT_PERSONALIZATION_WRITE_HUK_FAIL,                   /* HUKд����� */
    DRV_AGENT_PERSONALIZATION_FLASH_ERROR,                      /* Flash���� */
    DRV_AGENT_PERSONALIZATION_OTHER_ERROR,                      /* �������� */

    DRV_AGENT_PERSONALIZATION_ERR_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32;

/*****************************************************************************
ö����    : DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM
ö��˵��  : ����������category����

  1.��    ��   : 2012��04��07��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK                 = 0x00,          /* category:���� */
    DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET          = 0x01,          /* category:������ */
    DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER        = 0x02,          /* category:��SP */
    DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE               = 0x03,          /* category:������ */
    DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM                = 0x04,          /* category:��(U)SIM�� */

    DRV_AGENT_PERSONALIZATION_CATEGORY_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8;

/*****************************************************************************
ö����    : DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM
ö��˵��  : ָ�����������������Ƿ񼤻�

  1.��    ��   : 2012��04��07��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM
{
    DRV_AGENT_PERSONALIZATION_INDICATOR_INACTIVE               = 0x00,          /* δ���� */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE                 = 0x01,          /* �Ѽ��� */

    DRV_AGENT_PERSONALIZATION_INDICATOR_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8;

/*****************************************************************************
ö����    : DRV_AGENT_PERSONALIZATION_STATUS_ENUM
ö��˵��  : ָ���������������͵�״̬

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
enum DRV_AGENT_PERSONALIZATION_STATUS_ENUM
{
    DRV_AGENT_PERSONALIZATION_STATUS_READY      = 0x00,                         /* �Ѿ����� */
    DRV_AGENT_PERSONALIZATION_STATUS_PIN        = 0x01,                         /* δ����״̬������������� */
    DRV_AGENT_PERSONALIZATION_STATUS_PUK        = 0x02,                         /* Block״̬��������UnBlock�� */

    DRV_AGENT_PERSONALIZATION_STATUS_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PERSONALIZATION_STATUS_ENUM_UINT8;

/*****************************************************************************
ö����    : DRV_AGENT_PH_PHYNUM_TYPE_ENUM
ö��˵��  : ���������ö��

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum DRV_AGENT_PH_PHYNUM_TYPE_ENUM
{
    DRV_AGENT_PH_PHYNUM_IMEI            = 0x00,          /* IMEI */
    DRV_AGENT_PH_PHYNUM_SN              = 0x01,          /* SN */

    DRV_AGENT_PH_PHYNUM_BUTT
};
typedef VOS_UINT8 DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : DRV_AGENT_PORT_STATUS_ENUM
ö��˵��  : ͨ�Ŷ˿�״̬����ö��

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum DRV_AGENT_PORT_STATUS_ENUM
{
    DRV_AGENT_PORT_STATUS_OFF              = 0,         /* �˿ڹر� */
    DRV_AGENT_PORT_STATUS_ON               = 1,         /* �˿ڴ� */

    DRV_AGENT_PORT_STATUS_BUTT
};
typedef VOS_UINT32 DRV_AGENT_PORT_STATUS_ENUM_UINT32;

/*****************************************************************************
ö����    : DRV_AGENT_USIM_OPERATE_ENUM_UINT32
ö��˵��  : USIM��������ö��

  1.��    ��   : 2012��06��18��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012060804905, ����AT����AT^APSIMST
*****************************************************************************/
enum DRV_AGENT_USIM_OPERATE_ENUM
{
    DRV_AGENT_USIM_OPERATE_DEACT                = 0,         /* ȥ����USIM */
    DRV_AGENT_USIM_OPERATE_ACT                  = 1,         /* ����USIM */

    DRV_AGENT_USIM_OPERATE_BUTT
};
typedef VOS_UINT32 DRV_AGENT_USIM_OPERATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : DRV_AGENT_MSG_TYPE_ENUM
 �ṹ˵��  : AT��DRV AGENT��Ϣ�ӿ�ö��
  1.��    ��   : 2012��1��16��
    ��    ��   : f62575
    �޸�����   : SMALL IMAGE���Ժ���: ��������������Ϣ
                                DRV_AGENT_TSELRF_SET_REQ
                                DRV_AGENT_HKADC_GET_REQ
                                DRV_AGENT_TSELRF_SET_CNF
                                DRV_AGENT_HKADC_GET_CNF
  2.��    ��   : 2012��02��06��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : B050���Ժ���: ��������������Ϣ
                   DRV_AGENT_SECUBOOT_SET_REQ
                   DRV_AGENT_SECUBOOT_SET_CNF
  3.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : ɾ����DSDA c����Ŀ�е�������WAS��ص���ϢID
*****************************************************************************/
enum DRV_AGENT_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/      /* ��ע */
    /* AT����DRV AGENT����Ϣ */
    DRV_AGENT_MSID_QRY_REQ               = 0x0000,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_GCF_IND                    = 0x0002,
    DRV_AGENT_GAS_MNTN_CMD               = 0x0006,
    DRV_AGENT_GPIOPL_SET_REQ             = 0x000E,
    DRV_AGENT_GPIOPL_QRY_REQ             = 0x0010,
    DRV_AGENT_DATALOCK_SET_REQ           = 0x0012,
    DRV_AGENT_TBATVOLT_QRY_REQ           = 0x0014,
    DRV_AGENT_VERTIME_QRY_REQ            = 0x0016,
    DRV_AGENT_YJCX_SET_REQ               = 0x0020,
    DRV_AGENT_YJCX_QRY_REQ               = 0x0022,
    DRV_AGENT_APPDMVER_QRY_REQ           = 0x0024,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_DLOADINFO_QRY_REQ          = 0x0028,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_FLASHINFO_QRY_REQ          = 0x002A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHVER_QRY_REQ            = 0x002C,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHORITYVER_QRY_REQ       = 0x0030,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_AUTHORITYID_QRY_REQ        = 0x0032,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_GODLOAD_SET_REQ            = 0x0034,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_HWNATQRY_QRY_REQ           = 0x0036,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
    DRV_AGENT_CPULOAD_QRY_REQ            = 0x0038,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_MFREELOCKSIZE_QRY_REQ      = 0x003A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */

    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
    DRV_AGENT_MEMINFO_QRY_REQ            = 0x003B,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */

    DRV_AGENT_HARDWARE_QRY               = 0x003E, /*��ѯӲ���汾��*/
    DRV_AGENT_FULL_HARDWARE_QRY          = 0x0040, /*��ѯ������Ӳ���汾��*/
    DRV_AGENT_TMODE_SET_REQ              = 0x0046,
    DRV_AGENT_VERSION_QRY_REQ            = 0x0048,
    DRV_AGENT_SECUBOOT_QRY_REQ           = 0x004A,
    DRV_AGENT_SECUBOOTFEATURE_QRY_REQ    = 0x004C,
    DRV_AGENT_PFVER_QRY_REQ              = 0x004E,
    DRV_AGENT_FCHAN_SET_REQ              = 0x0052,
    DRV_AGENT_SDLOAD_SET_REQ             = 0x0056,
    DRV_AGENT_SFEATURE_QRY_REQ           = 0x0058,
    DRV_AGENT_PRODTYPE_QRY_REQ           = 0x0060,
    DRV_AGENT_SDREBOOT_REQ               = 0x0062,
    DRV_AGENT_RXDIV_SET_REQ              = 0x0064,
    DRV_AGENT_DLOADVER_QRY_REQ           = 0x0066,

    DRV_AGENT_RXDIV_QRY_REQ              = 0x006A,
    DRV_AGENT_SIMLOCK_SET_REQ            = 0x006C,
    DRV_AGENT_IMSICHG_QRY_REQ            = 0x0072,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRESTORE_SET_REQ          = 0x0074,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_INFORBU_SET_REQ            = 0x0076,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRSTSTTS_QRY_REQ          = 0x0078,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_CPNN_TEST_REQ              = 0x007A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVBACKUP_SET_REQ           = 0x007C,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_CPNN_QRY_REQ               = 0x007E,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NVRESTORE_MANU_DEFAULT_REQ = 0x0080,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_ADC_SET_REQ                = 0x0082,                              /* _H2ASN_MsgChoice SPY_TEMP_THRESHOLD_PARA_STRU */
    DRV_AGENT_TSELRF_SET_REQ             = 0x0084,                              /* _H2ASN_MsgChoice DRV_AGENT_TSELRF_SET_REQ_STRU */
    DRV_AGENT_HKADC_GET_REQ              = 0x0086,                              /* _H2ASN_MsgChoice  */
    DRV_AGENT_TBAT_QRY_REQ               = 0x0088,
    DRV_AGENT_SECUBOOT_SET_REQ           = 0x008A,

    DRV_AGENT_SIMLOCK_NV_SET_REQ         = 0x008c,

    DRV_AGENT_SPWORD_SET_REQ             = 0x008e,

    DRV_AGENT_PSTANDBY_SET_REQ           = 0x0090,

    DRV_AGENT_NVBACKUPSTAT_QRY_REQ       = 0x0092,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NANDBBC_QRY_REQ            = 0x0094,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_NANDVER_QRY_REQ            = 0x0096,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_CHIPTEMP_QRY_REQ           = 0x0098,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */


    DRV_AGENT_HUK_SET_REQ                = 0x009A,                              /* _H2ASN_MsgChoice DRV_AGENT_HUK_SET_REQ_STRU */
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ      = 0x009C,                              /* _H2ASN_MsgChoice DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU */
    DRV_AGENT_IDENTIFYSTART_SET_REQ      = 0x009E,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_IDENTIFYEND_SET_REQ        = 0x00A0,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYEND_SET_REQ_STRU */
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ   = 0x00A2,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU */
    DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ   = 0x00A4,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ    = 0x00A6,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_PHONEPHYNUM_SET_REQ        = 0x00A8,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU */
    DRV_AGENT_PHONEPHYNUM_QRY_REQ        = 0x00AA,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_PORTCTRLTMP_SET_REQ        = 0x00AC,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU */
    DRV_AGENT_PORTATTRIBSET_SET_REQ      = 0x00AE,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU */
    DRV_AGENT_PORTATTRIBSET_QRY_REQ      = 0x00B0,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    DRV_AGENT_OPWORD_SET_REQ             = 0x00B2,                              /* _H2ASN_MsgChoice DRV_AGENT_OPWORD_SET_REQ_STRU */
    DRV_AGENT_SARREDUCTION_SET_REQ       = 0x00B4,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */

    /* Add by h00135900 for V7����ͬ��, 2012-04-07, Begin   */
    DRV_AGENT_INFORRS_SET_REQ            = 0x0100,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */
    /* Add by h00135900 for V7����ͬ��, 2012-04-07, End   */

    DRV_AGENT_MAX_LOCK_TIMES_SET_REQ     = 0x0102,

    DRV_AGENT_AP_SIMST_SET_REQ           = 0x0104,                              /* _H2ASN_MsgChoice DRV_AGENT_AP_SIMST_SET_REQ_STRU */

    DRV_AGENT_SWVER_SET_REQ              = 0x0106,                              /* _H2ASN_MsgChoice DRV_AGENT_SWVER_INFO_STRU */
    DRV_AGENT_QRY_CCPU_MEM_INFO_REQ      = 0x0108,

    DRV_AGENT_HVPDH_REQ                  = 0x010A,

    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, begin */
    DRV_AGENT_NVMANUFACTUREEXT_SET_REQ   = 0x010C,
    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, end */

    DRV_AGENT_ANTSWITCH_SET_REQ          = 0x010E,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_SET_STRU */
    DRV_AGENT_ANTSWITCH_QRY_REQ          = 0x0110,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU */

    /* DRV AGENT����AT����Ϣ */
    DRV_AGENT_MSID_QRY_CNF               = 0x0001,                              /* _H2ASN_MsgChoice DRV_AGENT_MSID_QRY_CNF_STRU */
    DRV_AGENT_GAS_MNTN_CMD_RSP           = 0x0005,
    DRV_AGENT_GPIOPL_SET_CNF             = 0x000D,
    DRV_AGENT_GPIOPL_QRY_CNF             = 0x000F,
    DRV_AGENT_DATALOCK_SET_CNF           = 0x0011,
    DRV_AGENT_TBATVOLT_QRY_CNF           = 0x0013,
    DRV_AGENT_VERTIME_QRY_CNF            = 0x0015,
    DRV_AGENT_YJCX_SET_CNF               = 0x001F,
    DRV_AGENT_YJCX_QRY_CNF               = 0x0021,
    DRV_AGENT_APPDMVER_QRY_CNF           = 0x0023,                              /* _H2ASN_MsgChoice DRV_AGENT_APPDMVER_QRY_CNF_STRU */
    DRV_AGENT_DLOADINFO_QRY_CNF          = 0x0027,                              /* _H2ASN_MsgChoice DRV_AGENT_DLOADINFO_QRY_CNF_STRU */
    DRV_AGENT_FLASHINFO_QRY_CNF          = 0x0029,                              /* _H2ASN_MsgChoice DRV_AGENT_FLASHINFO_QRY_CNF_STRU*/
    DRV_AGENT_AUTHVER_QRY_CNF            = 0x002B,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHVER_QRY_CNF_STRU*/
    DRV_AGENT_AUTHORITYVER_QRY_CNF       = 0x002F,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU*/
    DRV_AGENT_AUTHORITYID_QRY_CNF        = 0x0031,                              /* _H2ASN_MsgChoice DRV_AGENT_AUTHORITYID_QRY_CNF_STRU*/
    DRV_AGENT_GODLOAD_SET_CNF            = 0x0033,                              /* _H2ASN_MsgChoice DRV_AGENT_GODLOAD_SET_CNF_STRU*/
    DRV_AGENT_HWNATQRY_QRY_CNF           = 0x0035,                              /* _H2ASN_MsgChoice DRV_AGENT_HWNATQRY_QRY_CNF_STRU*/
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
    DRV_AGENT_CPULOAD_QRY_CNF            = 0x0037,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    DRV_AGENT_MFREELOCKSIZE_QRY_CNF      = 0x0039,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */

    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
    DRV_AGENT_MEMINFO_QRY_CNF            = 0x003A,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */

    DRV_AGENT_HARDWARE_QRY_RSP           = 0x003D, /*�ظ�Ӳ���汾��*/
    DRV_AGENT_FULL_HARDWARE_QRY_RSP      = 0x003F, /*�ظ�������Ӳ���汾��*/
    DRV_AGENT_VERSION_QRY_CNF            = 0x0047,
    DRV_AGENT_SECUBOOT_QRY_CNF           = 0x0049,
    DRV_AGENT_SECUBOOTFEATURE_QRY_CNF    = 0x004B,
    DRV_AGENT_PFVER_QRY_CNF              = 0x004D,                              /* _H2ASN_MsgChoice DRV_AGENT_PFVER_QRY_CNF_STRU */
    DRV_AGENT_FCHAN_SET_CNF              = 0x0053,
    DRV_AGENT_SDLOAD_SET_CNF             = 0x0057,
    DRV_AGENT_SFEATURE_QRY_CNF           = 0x0059,
    DRV_AGENT_PRODTYPE_QRY_CNF           = 0x0061,
    DRV_AGENT_RXDIV_SET_CNF              = 0x0063,
    DRV_AGENT_DLOADVER_QRY_CNF           = 0x0065,
    DRV_AGENT_RXDIV_QRY_CNF              = 0x0069,
    DRV_AGENT_SIMLOCK_SET_CNF            = 0x006B,
    DRV_AGENT_IMSICHG_QRY_CNF            = 0x0071,                              /* _H2ASN_MsgChoice DRV_AGENT_IMSICHG_QRY_CNF_STRU */
    DRV_AGENT_NVRESTORE_SET_CNF          = 0x0073,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_INFORBU_SET_CNF            = 0x0075,                              /* _H2ASN_MsgChoice DRV_AGENT_INFORBU_SET_CNF_STRU */
    DRV_AGENT_NVRSTSTTS_QRY_CNF          = 0x0077,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_CPNN_TEST_CNF              = 0x0079,                              /* _H2ASN_MsgChoice DRV_AGENT_CPNN_TEST_CNF_STRU */
    DRV_AGENT_NVBACKUP_SET_CNF           = 0x007B,                              /* _H2ASN_MsgChoice DRV_AGENT_NVBACKUP_SET_CNF_STRU */
    DRV_AGENT_CPNN_QRY_CNF               = 0x007D,                              /* _H2ASN_MsgChoice DRV_AGENT_CPNN_QRY_CNF_STRU */
    DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF = 0x007F,                              /* _H2ASN_MsgChoice DRV_AGENT_NVRESTORE_RST_STRU */
    DRV_AGENT_ADC_SET_CNF                = 0x0081,
    DRV_AGENT_TSELRF_SET_CNF             = 0x0083,                              /* _H2ASN_MsgChoice DRV_AGENT_TSELRF_SET_CNF_STRU */
    DRV_AGENT_HKADC_GET_CNF              = 0x0085,                              /* _H2ASN_MsgChoice DRV_AGENT_HKADC_GET_CNF_STRU */
    DRV_AGENT_TBAT_QRY_CNF               = 0x0087,
    DRV_AGENT_SECUBOOT_SET_CNF           = 0x0089,                              /* _H2ASN_MsgChoice DRV_AGENT_SECUBOOT_SET_CNF_STRU */
    DRV_AGENT_SPWORD_SET_CNF             = 0x008B,

    DRV_AGENT_NVBACKUPSTAT_QRY_CNF       = 0x008D,                              /* _H2ASN_MsgChoice DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU */
    DRV_AGENT_NANDBBC_QRY_CNF            = 0x008F,                              /* _H2ASN_MsgChoice DRV_AGENT_NANDBBC_QRY_CNF_STRU */
    DRV_AGENT_NANDVER_QRY_CNF            = 0x0091,                              /* _H2ASN_MsgChoice DRV_AGENT_NANDVER_QRY_CNF_STRU */
    DRV_AGENT_CHIPTEMP_QRY_CNF           = 0x0093,                              /* _H2ASN_MsgChoice DRV_AGENT_CHIPTEMP_QRY_CNF_STRU */


    DRV_AGENT_HUK_SET_CNF                = 0x0095,                              /* _H2ASN_MsgChoice DRV_AGENT_HUK_SET_CNF_STRU */
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF      = 0x0097,                              /* _H2ASN_MsgChoice DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU */
    DRV_AGENT_IDENTIFYSTART_SET_CNF      = 0x0099,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU */
    DRV_AGENT_IDENTIFYEND_SET_CNF        = 0x009B,                              /* _H2ASN_MsgChoice DRV_AGENT_IDENTIFYEND_SET_CNF_STRU */
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF   = 0x009D,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU */
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF   = 0x009F,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU */
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF    = 0x00A1,                              /* _H2ASN_MsgChoice DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU */
    DRV_AGENT_PHONEPHYNUM_SET_CNF        = 0x00A3,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU */
    DRV_AGENT_PHONEPHYNUM_QRY_CNF        = 0x00A5,                              /* _H2ASN_MsgChoice DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU */
    DRV_AGENT_PORTCTRLTMP_SET_CNF        = 0x00A7,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU */
    DRV_AGENT_PORTATTRIBSET_SET_CNF      = 0x00A9,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU */
    DRV_AGENT_PORTATTRIBSET_QRY_CNF      = 0x00AB,                              /* _H2ASN_MsgChoice DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU */
    DRV_AGENT_OPWORD_SET_CNF             = 0x00AD,                              /* _H2ASN_MsgChoice DRV_AGENT_OPWORD_SET_CNF_STRU */
    DRV_AGENT_ANTSTATE_QRY_IND           = 0x00AF,                              /* _H2ASN_MsgChoice AT_APPCTRL_STRU*/
    /* Add by h00135900 for V7����ͬ��, 2012-04-07, Begin   */
    DRV_AGENT_INFORRS_SET_CNF            = 0x0101,                              /* _H2ASN_MsgChoice DRV_AGENT_INFORRS_SET_CNF_STRU */

    /* Add by h00135900 for V7����ͬ��, 2012-04-07, End   */

    DRV_AGENT_MAX_LOCK_TIMES_SET_CNF     = 0x0103,                              /* _H2ASN_MsgChoice DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU */

    DRV_AGENT_AP_SIMST_SET_CNF           = 0x0105,                              /* _H2ASN_MsgChoice DRV_AGENT_AP_SIMST_SET_CNF_STRU */

    DRV_AGENT_SWVER_SET_CNF              = 0x0107,                              /* _H2ASN_MsgChoice DRV_AGENT_SWVER_SET_CNF_STRU */

    DRV_AGENT_HVPDH_CNF                  = 0x0109,

    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, begin */
    DRV_AGENT_NVMANUFACTUREEXT_SET_CNF   = 0x010B,
    /* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, end */

    DRV_AGENT_ANTSWITCH_SET_CNF          = 0x010D,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_SET_CNF_STRU */
    DRV_AGENT_ANTSWITCH_QRY_CNF          = 0x010F,                              /* _H2ASN_MsgChoice DRV_AGENT_ANTSWITCH_QRY_CNF_STRU */
    DRV_AGENT_MSG_TYPE_BUTT              = 0xFFFF
};
typedef VOS_UINT32 DRV_AGENT_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_DEVICE_CMD_RAT_MODE_ENUM
 �ṹ˵��  : װ��AT����ģʽö��

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
enum AT_DEVICE_CMD_RAT_MODE_ENUM
{
    AT_RAT_MODE_WCDMA = 0,
    AT_RAT_MODE_CDMA,
    AT_RAT_MODE_TDSCDMA,
    AT_RAT_MODE_GSM,
    AT_RAT_MODE_EDGE,
    AT_RAT_MODE_AWS,
    AT_RAT_MODE_FDD_LTE,
    AT_RAT_MODE_TDD_LTE,
    AT_RAT_MODE_WIFI,
    AT_RAT_MODE_BUTT
};
typedef VOS_UINT8 AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8;

/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */

/* ��ѯ����ڴ���������  */
enum AT_MEMQUERY_PARA_ENUM
{
    AT_MEMQUERY_VOS = 0,  /* ��ѯVOS�İ뾲̬�ڴ�ʵ�ʵ�ռ����� */
    AT_MEMQUERY_TTF,      /* ��ѯTTF�İ뾲̬�ڴ�ʵ�ʵ�ռ����� */
    AT_MEMQUERY_BUTT
};
typedef VOS_UINT32  AT_MEMQUERY_PARA_ENUM_UINT32;

/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */

/*****************************************************************************
ö����    : DRV_AGENT_DH_KEY_TYPE_ENUM
ö��˵��  : DH�㷨ʹ�õ���Կ����

  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
enum DRV_AGENT_DH_KEY_TYPE_ENUM
{
    DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY  = 0x00,          /* ��������Կ */
    DRV_AGENT_DH_KEY_MODEM_PUBLIC_KEY   = 0x01,          /* MODEM�๫Կ */
    DRV_AGENT_DH_KEY_MODEM_PRIVATE_KEY  = 0x02,          /* MODEM��˽Կ */

    DRV_AGENT_DH_KEY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_DH_KEY_TYPE_ENUM_UINT32;

/*****************************************************************************
ö����    : DRV_AGENT_HVPDH_ERR_ENUM
ö��˵��  : ����DH�㷨����Կ���

  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
enum DRV_AGENT_HVPDH_ERR_ENUM
{
    DRV_AGENT_HVPDH_NO_ERROR            = 0x00,          /* �����ɹ� */
    DRV_AGENT_HVPDH_AUTH_UNDO           = 0x01,          /* ��ʱ��δ���й����߼�Ȩ */
    DRV_AGENT_HVPDH_NV_READ_FAIL        = 0x02,          /* NV��ȡʧ�� */
    DRV_AGENT_HVPDH_NV_WRITE_FAIL       = 0x03,          /* NVд��ʧ�� */
    DRV_AGENT_HVPDH_OTHER_ERROR         = 0x04,          /* �������� */

    DRV_AGENT_HVPDH_ERR_BUTT
};
typedef VOS_UINT32 DRV_AGENT_HVPDH_ERR_ENUM_UINT32;




/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_PSTANDBY _REQ_STRU
 �ṹ˵��  : AT��AT AGENT AT^PSTANDBY��������ṹ

  1.��    ��   : 2012��04��12��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStandbyTime;                          /* ����������״̬��ʱ�䳤�ȣ�(��λΪms),ȡֵ��Χ 0~65535,Ĭ��Ϊ5000�� */
    VOS_UINT32                          ulSwitchTime;                           /* ����ָ��PC�·������������������״̬���л�ʱ�䡣����λΪms����ȡֵ��ΧΪ 0~65535��Ĭ��Ϊ500�� */
} DRV_AGENT_PSTANDBY_REQ_STRU;
/* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */


/*****************************************************************************
 �ṹ��    : DRV_AGENT_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT����Ϣ�ṹ

  1.��    ��   : 2011��10��29��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: DRV AGENT��AT����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           aucContent[4];
} DRV_AGENT_MSG_STRU;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
 ö����    : GAS_AT_CMD_ENUM
 �ṹ˵��  : GAS������������ö�ٽṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
typedef enum
{
    GAS_AT_CMD_GAS_STA          =   0,  /* GAS״̬ */
    GAS_AT_CMD_NCELL            =   1,  /* ����״̬ */
    GAS_AT_CMD_SCELL            =   2,  /* ����С��״̬ */
    GAS_AT_CMD_MEASURE_DOWN     =   3,  /* �������� */
    GAS_AT_CMD_MEASURE_UP       =   4,  /* �������� */
    GAS_AT_CMD_FREQ_LOCK        =   5,  /* ��Ƶ�㣬��������ѡ */
    GAS_AT_CMD_FREQ_UNLOCK      =   6,  /* ���� */
    GAS_AT_CMD_FREQ_SPEC_SEARCH =   7,  /* ָ��Ƶ������ */
    GAS_AT_CMD_BUTT
}GAS_AT_CMD_ENUM;

typedef VOS_UINT8 GAS_AT_CMD_ENUM_U8;

/*****************************************************************************
 ö����    : GAS_AT_CMD_ENUM
 �ṹ˵��  : GAS��������ṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    GAS_AT_CMD_ENUM_U8                  ucCmd;
    VOS_UINT8                           ucParaNum;
    VOS_UINT16                          usReserve;
    VOS_UINT32                          aulPara[10];
}GAS_AT_CMD_STRU;

/*****************************************************************************
 ö����    : GAS_AT_CMD_ENUM
 �ṹ˵��  : GAS�����������ṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[20];
}GAS_AT_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_MSID_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯMS ID��Ϣ��Ϣ�ظ��ṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                      stAtAppCtrl;                                   /* AT�û����ƽṹ */
    DRV_AGENT_MSID_QRY_ERROR_ENUM_UINT32 ulResult;                                      /* ��Ϣ������ */
    VOS_INT8                             acModelId[TAF_MAX_MODEL_ID_LEN + 1];           /* ģ����Ϣ */
    VOS_INT8                             acSoftwareVerId[TAF_MAX_REVISION_ID_LEN + 1];  /* ����汾��Ϣ */
    VOS_UINT8                            aucImei[TAF_PH_IMEI_LEN];
} DRV_AGENT_MSID_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_TSELRF_SET_REQ_STRU
 �ṹ˵��  : ^TSELRF��������������DSP
             ucLoadDspMode  ������ص�DSPģʽ
 1.��    ��   : 20112��1��10��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLoadDspMode;
    VOS_UINT8                           ucDeviceRatMode;
} DRV_AGENT_TSELRF_SET_REQ_STRU;

/* Added by f62575 for AT Project��2011-10-04,  Begin*/
/*****************************************************************************
 �ṹ��    : DRV_AGENT_APPDMVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯAP PDMVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_INT8                                 acPdmver[AT_MAX_PDM_VER_LEN + 1];
    VOS_UINT8                                aucReserved1[3];
} DRV_AGENT_APPDMVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DLOADINFO_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯDLOADINFO��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_DLOADINFO_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UCHAR                                 aucDlodInfo[TAF_DLOAD_INFO_LEN];
} DRV_AGENT_DLOADINFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯAUTHORITYVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                              stAtAppCtrl;
    DRV_AGENT_AUTHORITYVER_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT8                                    aucAuthority[TAF_AUTHORITY_LEN + 1];
    VOS_UINT8                                    aucReserved1[1];
} DRV_AGENT_AUTHORITYVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_AUTHORITYID_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯDLOADINFO��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                             stAtAppCtrl;
    DRV_AGENT_AUTHORITYID_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT8                                   aucAuthorityId[TAF_AUTH_ID_LEN + 1];
    VOS_UINT8                                   aucReserved1[1];
} DRV_AGENT_AUTHORITYID_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PFVER_REQ_STRU
 �ṹ˵��  : ƽ̨����汾��
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPfVer[TAF_MAX_PROPLAT_LEN + 1];
    VOS_CHAR                            acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];
}DRV_AGENT_PFVER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PFVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯPFVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_PFVER_QRY_ERROR_ENUM_UINT32 enResult;
    DRV_AGENT_PFVER_INFO_STRU             stPfverInfo;
} DRV_AGENT_PFVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SDLOAD_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����SDLOAD ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                               stAtAppCtrl;
    DRV_AGENT_SDLOAD_SET_ERROR_ENUM_UINT32        enResult;
} DRV_AGENT_SDLOAD_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DLOADVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯDLOADVER ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                               stAtAppCtrl;
    DRV_AGENT_DLOADVER_QRY_ERROR_ENUM_UINT32      enResult;
    VOS_CHAR                                      aucVersionInfo[TAF_MAX_VER_INFO_LEN + 1];
    VOS_UINT8                                     ucReserved1;
} DRV_AGENT_DLOADVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DLOADINFO_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����GODLOAD ��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_GODLOAD_SET_ERROR_ENUM_UINT32  enResult;
} DRV_AGENT_GODLOAD_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_HWNATQRY_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯHWNATQRY��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_HWNATQRY_QRY_ERROR_ENUM_UINT32 enResult;
    VOS_UINT                                 ulNetMode;
} DRV_AGENT_HWNATQRY_QRY_CNF_STRU;

/* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_CPULOAD_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯCPULOAD��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��11��12��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_CPULOAD_QRY_ERROR_ENUM_UINT32  enResult;
    VOS_UINT32                               ulCurACpuLoad;
    VOS_UINT32                               ulCurCCpuLoad;
} DRV_AGENT_CPULOAD_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_MFREELOCKSIZE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯMFREELOCKSIZE��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��11��12��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;
    DRV_AGENT_MFREELOCKSIZE_QRY_ERROR_ENUM_UINT32   enResult;
    VOS_INT32                                       lMaxFreeLockSize;
}DRV_AGENT_MFREELOCKSIZE_QRY_CNF_STRU;
/* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DLOAD_FLASH_STRU
 �ṹ˵��  :����Flash��Ϣ;�ýṹ��DLOAD_FLASH_STRU_Sһ��

 1.��    ��   : 2011��11��1��
   ��    ��   : l60609
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulBlockCount;                       /*Block����*/
    VOS_UINT32                              ulPageSize;                         /*pageҳ��С*/
    VOS_UINT32                              ulPgCntPerBlk;                      /*һ��Block�е�page����*/
}DRV_AGENT_DLOAD_FLASH_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_FLASHINFO_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯFLASHINFO��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_FLASHINFO_QRY_ERROR_ENUM_UINT32 enResult;
    DRV_AGENT_DLOAD_FLASH_STRU                stFlashInfo;
} DRV_AGENT_FLASHINFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_AUTHVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯAUTHVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                           stAtAppCtrl;
    DRV_AGENT_AUTHVER_QRY_ERROR_ENUM_UINT32   enResult;
    VOS_UINT32                                ulSimLockVersion;
} DRV_AGENT_AUTHVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_APPDMVER_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯAP PDMVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2011��10��4��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    DRV_AGENT_APPDMVER_QRY_ERROR_ENUM_UINT32 enResult;
} DRV_AGENT_SDLOAD_QRY_CNF_STRU;
/* Added by f62575 for AT Project��2011-10-04,  End*/

/* Added by o00132663 for AT Project��2011-10-04,  Begin */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_VERSION_CTRL_STRU
 �ṹ˵��  : AT��AT AGENT�汾��ѯ����ƽṹ

1.��    ��   : 2011��10��15��
  ��    ��   : o00132663
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucType;                                 /* �������: COMP_TYPE_I */
    VOS_UINT8                           ucMode;                                 /* ����ģʽ: ������д */
    VOS_UINT8                           aucReserved[1];                         /* ����ָ�� */
    VOS_UINT8                           ucLen;                                  /* ���ݳ��� */
    VOS_CHAR                            aucData[AT_MAX_VERSION_LEN];
} DRV_AGENT_VERSION_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_GAS_MNTN_CMD_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^CGAS����ظ��ṹ

1.��    ��   : 2011��10��15��
  ��    ��   : o00132663
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    GAS_AT_CMD_ENUM_U8                  ucCmd;
    VOS_UINT8                           aucReserved[3];
    GAS_AT_RSLT_STRU                    stAtCmdRslt;
} DRV_AGENT_GAS_MNTN_CMD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_DRV_AGENT_RXDIV_SET_STRU
 �ṹ˵��  : AT��AT AGENT AT^RXDIV��������ṹ

�޸���ʷ      :
 1.��    ��   : 2011��10��5��
   ��    ��   : C00173809
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDspBand;       /*DSP��ʽ��Ƶ��ֵ*/
    VOS_UINT8                           ucRxOnOff;       /* Rx on offֵ*/
    VOS_UINT8                           ucReserve;       /*����λ*/
    VOS_UINT32                          ulSetLowBands;   /*ת��λ���ָ�ʽ�ķּ���λ*/
    VOS_UINT32                          ulSetHighBands;  /*ת��λ���ָ�ʽ�ķּ���λ*/
} AT_DRV_AGENT_RXDIV_SET_STRU;
/*****************************************************************************
 �ṹ��    : DRV_AGENT_RXDIV_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^RXDIV����ظ��ṹ

�޸���ʷ      :
 1.��    ��   : 2011��10��5��
   ��    ��   : C00173809
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;        /*��Ϣͷ*/
    VOS_UINT32                          ulResult;           /*���ؽ��*/
    VOS_UINT8                           ucRxOnOff;          /*RX�Ƿ��Ѿ���*/
    VOS_UINT8                           ucReserve;          /*����λ*/
    VOS_UINT16                          usSetDivBands;      /*Ҫ���õ�BAND*/
} DRV_AGENT_AT_RXDIV_CNF_STRU;
/*****************************************************************************
 �ṹ��    : DRV_AGENT_QRY_RXDIV_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^RXDIV����ظ��ṹ

�޸���ʷ      :
 1.��    ��   : 2011��10��22��
   ��    ��   : C00173809
   �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;        /*��Ϣͷ*/
    VOS_UINT32                          ulResult;           /*���ؽ��*/
    VOS_UINT16                          usDrvDivBands;      /*֧�ֵ�BAND*/
    VOS_UINT16                          usCurBandSwitch;    /*��ǰ���õ�BAND*/
} DRV_AGENT_QRY_RXDIV_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SIMLOCK_SET_REQ_STRU
 �ṹ˵��  : DRV��AT AGENT simlock��У�����Ϣ�ṹ

 1.��    ��   : 2011��11��3��
    ��    ��   : C00173809
    �޸�����   : �����ṹ��
 2.��    ��   : 2012��02��20��
    ��    ��   : L60609
    �޸�����   : �ṹ��ɾ�����������ֱ����C�˼�¼

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPwdLen;
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +4];
}DRV_AGENT_SIMLOCK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SET_SIMLOCK_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT simlock��У�����Ϣ�ṹ

 1.��    ��   : 2011��11��3��
    ��    ��   : C00173809
    �޸�����   : �����ṹ��
  2.��    ��   : 2012��2��20��
    ��    ��   : l60609
    �޸�����   : B060 Prj:AT����Ҫ��¼SIMLOCK���������ɾ��ȫ�ֱ���g_ucAtSi-
                 mLockErrTimes
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*��Ϣͷ*/
    VOS_UINT32                          ulResult;                               /*���ؽ��*/
}DRV_AGENT_SET_SIMLOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DRV_AGENT_HARDWARE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^HWVER����ظ��ṹ

1.��    ��   : 2011��10��15��
  ��    ��   : c00173809
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*��Ϣͷ*/
    VOS_UINT32                          ulResult;                               /*���ؽ��*/
    VOS_UINT8                           aucHwVer[DRV_AGENT_MAX_HARDWARE_LEN+1]; /*Ӳ���汾��*/
} DRV_AGENT_HARDWARE_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^FHVER����ظ��ṹ

1.��    ��   : 2011��10��15��
  ��    ��   : c00173809
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                                        /*��Ϣͷ*/
    VOS_UINT32                          ulResult;                                           /*���ؽ��*/
    VOS_UINT8                           aucModelId[DRV_AGENT_MAX_MODEL_ID_LEN + 1];         /*MODE ID��*/
    VOS_UINT8                           aucRevisionId[DRV_AGENT_MAX_REVISION_ID_LEN + 1];   /*����汾��*/
    VOS_UINT8                           aucHwVer[DRV_AGENT_MAX_HARDWARE_LEN+1];             /*Ӳ���汾��*/
} DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_NVRESTORE_RST_STRU
 �ṹ˵��  : AT��AT AGENT AT^NVRESTORE��������ظ��ṹ

  1.��    ��   : 2011��11��03��
    ��    ��   : f00179208
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /*��Ϣͷ*/
    VOS_UINT32                          ulResult;                               /*���ؽ��*/
} DRV_AGENT_NVRESTORE_RST_STRU;

/* Added by o00132663 for AT Project��2011-10-04,  End */

#define AT_SD_DATA_UNIT_LEN             (512)
#define AT_GPIOPL_MAX_LEN               (20)


/*****************************************************************************
 �ṹ��    : DRV_AGENT_GPIOPL_SET_REQ_STRU
 �ṹ˵��  : DRV��AT AGENT����GPIO��ƽ��Ϣ������ṹ

 1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enGpioOper;
    VOS_UINT8                           aucGpiopl[AT_GPIOPL_MAX_LEN];

}DRV_AGENT_GPIOPL_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_GPIOPL_SET_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT����GPIO��ƽ��Ϣ������ṹ

 1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;

}DRV_AGENT_GPIOPL_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_GPIOPL_QRY_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT��ѯGPIO��ƽ��Ϣ�Ļظ��ṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           aucGpiopl[AT_GPIOPL_MAX_LEN];

}DRV_AGENT_GPIOPL_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_DATALOCK_SET_REQ_STRU
 �ṹ˵��  : DRV��AT AGENT datalock��У�����Ϣ�ṹ

 1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];

}DRV_AGENT_DATALOCK_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_DATALOCK_SET_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT datalock��У�����Ϣ�ظ��ṹ

 1.��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;           /* DATALOCKУ���Ƿ�ɹ� */

}DRV_AGENT_DATALOCK_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_TBATVOLT_QRY_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT ��ѯ��ص�ѹ����Ϣ�ظ��ṹ

1.��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{

    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_INT32                           lBatVol;

}DRV_AGENT_TBATVOLT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_TMODE_SET_CNF
 �ṹ˵��  : AT��AT AGENT ����������־λ����Ϣ�ṹ

1.��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;

}DRV_AGENT_TMODE_SET_CNF_STRU;

/*****************************************************************************
 ö����    : DRV_AGENT_VERSION_QRY_ERROR_ENUM
 �ṹ˵��  : ^VERSION�����ѯ��������������б�

 1. ��    ��   : 2011��10��15��
    ��    ��   : w00181244
    �޸�����   : ����ö��

*****************************************************************************/
enum DRV_AGENT_VERSION_QRY_ERROR_ENUM
{
    DRV_AGENT_VERSION_QRY_NO_ERROR              = 0,
    DRV_AGENT_VERSION_QRY_VERTIME_ERROR         = 1,

    DRV_AGENT_VERSION_QRY_BUTT
};
typedef VOS_UINT32 DRV_AGENT_VERSION_QRY_ERROR_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_VERSION_QRY_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT ��ѯ�汾��Ϣ�Ļظ���Ϣ�ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                          stAtAppCtrl;
    TAF_PH_REVISION_ID_STRU                  stSoftVersion;                                 /*����汾��*/
    TAF_PH_HW_VER_STRU                       stFullHwVer;                                   /*�ⲿӲ���汾��*/
    TAF_PH_HW_VER_STRU                       stInterHwVer;                                  /*�ڲ�Ӳ���汾��*/
    TAF_PH_MODEL_ID_STRU                     stModelId;                                     /*�ⲿ��ƷID */
    TAF_PH_MODEL_ID_STRU                     stInterModelId;                                /*�ڲ���ƷID */
    TAF_PH_CDROM_VER_STRU                    stIsoVer;                                      /*��̨����汾��*/
    DRV_AGENT_VERSION_QRY_ERROR_ENUM_UINT32  enResult;                                      /*������ö�� */
    VOS_CHAR                                 acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];      /*����ʱ��*/

}DRV_AGENT_VERSION_QRY_CNF_STRU;

/*******************************************************************************
 �ṹ��    : WCDMA_PREF_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : union WCDMA_BAND_SET_UN��ԱBitBand����
             bitλ��1��ʾ��Ƶ����Ч

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
2. ��    ��   : 2012��5��10��
   ��    ��   : f62575
   �޸�����   : DTS2012051007817 ���SFEATURE��ѯ����û��WCDMA ��BAND11�������
3. ��    ��   : 2012��11��12��
   ��    ��   : t00212959
   �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪUINT32,AT����һ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare1            :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}AT_WCDMA_PREF_BAND_STRU;

/*******************************************************************************
 �ṹ��    :GSM_PREF_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : union GSM_BAND_SET_UN��ԱBitBand����
             bitλ��1��ʾ��Ƶ����Ч

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
2. ��    ��   : 2012��11��12��
   ��    ��   : t00212959
   �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪUINT32,AT����һ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;

}AT_GSM_PREF_BAND_STRU;

/*******************************************************************************
 �ṹ��    : WCDMA_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMAƵ��union����

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
2. ��    ��   : 2012��11��12��
   ��    ��   : t00212959
   �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪUINT32,AT����һ��
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    AT_WCDMA_PREF_BAND_STRU             BitBand;
}AT_WCDMA_BAND_SET_UN;

/*******************************************************************************
 �ṹ��    : GSM_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSMƵ��union����

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
2. ��    ��   : 2012��11��12��
   ��    ��   : t00212959
   �޸�����   : DTS2012103101740,MMA��Band�ṹ��ΪUINT32,AT����һ��
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;
    AT_GSM_PREF_BAND_STRU               BitBand;
}AT_GSM_BAND_SET_UN;


/*******************************************************************************
 �ṹ��    : AT_UE_BAND_CAPA_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����֧��Ƶ����Ϣ

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    AT_WCDMA_BAND_SET_UN                unWRFSptBand;
    AT_GSM_BAND_SET_UN                  unGRFSptBand;
}AT_UE_BAND_CAPA_ST;

/*****************************************************************************
 ö����    : AT_FEATURE_DRV_TYPE_ENUM
 Э����  :
 ö��˵��  : ����֧�����Ե�ö��

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
enum AT_FEATURE_DRV_TYPE_ENUM
{
    AT_FEATURE_LTE = 0,
    AT_FEATURE_HSPAPLUS,
    AT_FEATURE_HSDPA,
    AT_FEATURE_HSUPA,
    AT_FEATURE_DIVERSITY,
    AT_FEATURE_UMTS,
    AT_FEATURE_EVDO,
    AT_FEATURE_EDGE,
    AT_FEATURE_GPRS,
    AT_FEATURE_GSM,
    AT_FEATURE_CDMA,
    AT_FEATURE_WIMAX,
    AT_FEATURE_WIFI,
    AT_FEATURE_GPS,
    AT_FEATURE_TDSCDMA
};
typedef VOS_UINT32  AT_FEATURE_DRV_TYPE_ENUM_UINT32;

#define AT_FEATURE_NAME_LEN_MAX       (16)
#define AT_FEATURE_CONTENT_LEN_MAX    (56)


/*****************************************************************************
 �ṹ��    : AT_PRO_FEA_INFO_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ӧ����֧�ֵ�����

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucFeatureFlag;
    VOS_UINT8        aucFeatureName[AT_FEATURE_NAME_LEN_MAX];
    VOS_UINT8        aucContent[AT_FEATURE_CONTENT_LEN_MAX];
}AT_FEATURE_SUPPORT_ST;

/*****************************************************************************
 �ṹ��    : AT_RF_CAPA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF ������Ϣ

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPowerClass;       /* UE���ʼ���                      */
    VOS_UINT8                           enTxRxFreqSeparate; /* Tx/Rx Ƶ������                  */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬����                 */
} AT_RF_CAPA_STRU;


/*****************************************************************************
 �ṹ��    : AT_UE_CAPA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : en_NV_Item_WAS_RadioAccess_Capa NV���Ӧ�Ľṹ��
             ���ڱ����Ƿ�ʹ����HSDPA��HSUPA��HSDPA�����ȼ�

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHspaStatus;       /* 0��ʾδ����,��ôDPA��UPA��֧��;1��ʾ����           */
    VOS_UINT8                           ucMacEhsSupport;
    VOS_UINT8                           ucHSDSCHPhyCat;
    VOS_UINT8                           aucReserve1[2];     /* ����һ��������ulHspaStatus���п��ƣ��˱�������ʹ�� */
    AT_RF_CAPA_STRU                     stRfCapa;           /* RF ������Ϣ  */
    VOS_UINT8                           enDlSimulHsDschCfg; /* ENUMERATED  OPTIONAL  */
    VOS_UINT8                           enAsRelIndicator;   /* Access Stratum Release Indicator  */
    VOS_UINT8                           ucHSDSCHPhyCategory; /* ֧��HS-DSCH���������ͱ�־ */
    VOS_UINT8                           enEDCHSupport;       /* �Ƿ�֧��EDCH�ı�־ */
    VOS_UINT8                           ucEDCHPhyCategory;   /* ֧��UPA�ĵȼ� */
    VOS_UINT8                           enFDPCHSupport;      /* �Ƿ�֧��FDPCH�ı�־  */
    VOS_UINT8                           ucV690Container;     /* V690Container��д */
    VOS_UINT8                           enHSDSCHSupport;     /* �Ƿ�֧��enHSDSCHSupport�ı�־  */
} AT_UE_CAPA_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SFEATURE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯ�汾Ƶ����Ϣ����Ϣ�ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    AT_UE_BAND_CAPA_ST                  stBandFeature;

}DRV_AGENT_SFEATURE_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SECUBOOT_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ʹ��Secure Boot ���ܵ���Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��06��
   ��    ��   : f62575
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
}DRV_AGENT_SECUBOOT_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SECUBOOT_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯSecure Boot ����ʹ��״̬����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           ucSecuBootEnable;
    VOS_UINT8                           aucReserve1[3];                          /* 4�ֽڶ��룬���� */
}DRV_AGENT_SECUBOOT_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_SECUBOOTFEATURE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯSecure Boot �汾����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bFail;
    VOS_UINT8                           ucSecuBootFeature;
    VOS_UINT8                           aucReserve1[7];                          /* 4�ֽڶ��룬���� */
}DRV_AGENT_SECUBOOTFEATURE_QRY_CNF_STRU;

/*****************************************************************************
 ö����    : AT_DEVICE_CMD_BAND_ENUM
 ö��˵��  : װ��Ƶ����Ϣ

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
enum AT_DEVICE_CMD_BAND_ENUM
{
    AT_BAND_2100M = 0,
    AT_BAND_1900M,
    AT_BAND_1800M,
    AT_BAND_1700M,
    AT_BAND_1600M,
    AT_BAND_1500M,
    AT_BAND_900M,
    AT_BAND_850M,
    AT_BAND_800M,
    AT_BAND_450M,
    AT_BAND_2600M,
    AT_BAND_1X_BC0,
    AT_BAND_WIFI = 15,
    AT_BAND_BUTT
};
typedef VOS_UINT8 AT_DEVICE_CMD_BAND_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : AT_DSP_BAND_ARFCN_STRU
 �ṹ˵��  : �ŵ���Ϣ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlArfcn;  /*���е�Channel No*/
    VOS_UINT16                          usDlArfcn;  /*���е�Channel No*/
    VOS_UINT16                          usDspBand;  /*DSP��ʽ��Ƶ��ֵ*/
    VOS_UINT8                           aucReserved[2];
}AT_DSP_BAND_ARFCN_STRU;

/*****************************************************************************
 �ṹ��    : AT_ARFCN_RANGE_STRU
 �ṹ˵��  :ÿ���ŵ���Ӧ��Afrcn�����ֵ����Сֵ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16             usArfcnMin;
    VOS_UINT16             usArfcnMax;
}AT_ARFCN_RANGE_STRU;

/*****************************************************************************
 ö����    : AT_TMODE_ENUM
 ö��˵��  : װ��ģʽ��Ϣ

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
2.��    ��   : 2012��1��3��
  ��    ��   : f62575
  �޸�����   : SMALL IMAGE���Ժ���: �����Զ��ػ��µ���̣�
               ԭ<TESTMODE>4���ϲ�������ƶ�7����ֵ����11��ʼ
*****************************************************************************/
enum AT_TMODE_ENUM
{
    AT_TMODE_NORMAL = 0,   /*����ģʽ,��������״̬*/
    AT_TMODE_FTM ,         /*������ģʽ,У׼ģʽ*/
    AT_TMODE_UPGRADE ,     /*����ģʽ,�汾����ʱʹ�� */
    AT_TMODE_RESET,        /* ��������  */
    AT_TMODE_POWEROFF,
    AT_TMODE_SIGNALING = 11,
    AT_TMODE_OFFLINE,
#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
    AT_TMODE_F_NONESIGNAL   = 13,
    AT_TMODE_SYN_NONESIGNAL = 14,
    AT_TMODE_SET_SLAVE      = 15,
    AT_TMODE_GU_BT          = 16,
    AT_TMODE_TDS_FAST_CT    = 17,
    AT_TMODE_TDS_BT         = 18,
    AT_TMODE_COMM_CT        = 19,
#endif
    AT_TMODE_BUTT
};
typedef VOS_UINT8  TAF_PH_TMODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_FCHAN_SET_REQ_STRU
 �ṹ˵��  : DRV��AT AGENT ���� FCHAN ����Ϣ�ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLoadDspMode;
    VOS_UINT8                           ucCurrentDspMode;
    VOS_UINT16                          usChannelNo;
    AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8   ucDeviceRatMode;
    AT_DEVICE_CMD_BAND_ENUM_UINT8       ucDeviceAtBand;
    VOS_UINT8                           aucReserved[2];
    VOS_BOOL                            bDspLoadFlag;
    AT_DSP_BAND_ARFCN_STRU              stDspBandArfcn;
}DRV_AGENT_FCHAN_SET_REQ_STRU;


/*****************************************************************************
 ö����    : DRV_AGENT_FCHAN_SET_ERROR_ENUM
 �ṹ˵��  : FCHAN_�������ò�������������б�

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : ����ö��
*****************************************************************************/
enum DRV_AGENT_FCHAN_SET_ERROR_ENUM
{
    DRV_AGENT_FCHAN_SET_NO_ERROR                            = 0,
    DRV_AGENT_FCHAN_BAND_NOT_MATCH                          = 1,
    DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH                  = 2,
    DRV_AGENT_FCHAN_OTHER_ERR                               = 3,

    DRV_AGENT_FCHAN_SET_BUTT
};
typedef VOS_UINT32 DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_FCHAN_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ���� FCHAN ����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_FCHAN_SET_REQ_STRU          stFchanSetReq;
    DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32 enResult;

}DRV_AGENT_FCHAN_SET_CNF_STRU;


/*****************************************************************************
  ����˵��  :  MS֧�ֵĽ��շּ����Ͷ���

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
#define AT_MS_SUPPORT_RX_DIV_2100           0x0001
#define AT_MS_SUPPORT_RX_DIV_1900           0x0002
#define AT_MS_SUPPORT_RX_DIV_1800           0x0004
#define AT_MS_SUPPORT_RX_DIV_AWS_1700       0x0008
#define AT_MS_SUPPORT_RX_DIV_850            0x0010
#define AT_MS_SUPPORT_RX_DIV_800            0x0020
#define AT_MS_SUPPORT_RX_DIV_2600           0x0040
#define AT_MS_SUPPORT_RX_DIV_900            0x0080
#define AT_MS_SUPPORT_RX_DIV_IX_1700        0x0100


/*****************************************************************************
 ö����    : AT_DSP_RF_ON_OFF_ENUM_UINT8
 Э����  :
 ö��˵��  : RF����

1. ��    ��   : 2011��10��18��
   ��    ��   : w00181244
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
enum AT_DSP_RF_ON_OFF_ENUM
{
    AT_DSP_RF_SWITCH_OFF = 0,
    AT_DSP_RF_SWITCH_ON,
    AT_DSP_RF_SWITCH_BUTT
};
typedef VOS_UINT8 AT_DSP_RF_ON_OFF_ENUM_UINT8;

/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
/*****************************************************************************
 ö����    : AT_PID_MEM_INFO_PARA_STRU
 Э����  :
 ö��˵��  : ÿ��PID���ڴ�ռ������Ľṹ��

1. ��    ��   : 2011��11��30��
   ��    ��   : l00171473
   �޸�����   : �� AtCmdProc.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulPid;
    VOS_UINT32                          ulMsgPeakSize;
    VOS_UINT32                          ulMemPeakSize;
}AT_PID_MEM_INFO_PARA_STRU;
/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */

/*****************************************************************************
 �ṹ��    : DRV_AGENT_RXPRI_SET_REQ_STRU
 �ṹ˵��  : AT��AT AGENT ���� RXPRI ����Ϣ�ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetLowBands;
    VOS_UINT32                          ulSetHighBands;
    AT_DSP_BAND_ARFCN_STRU              stDspBandArfcn;
}DRV_AGENT_RXPRI_SET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_RXPRI_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ���� RXPRI ����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    DRV_AGENT_ERROR_ENUM_UINT32         enResult;
    DRV_AGENT_RXPRI_SET_REQ_STRU        stRxpriSetReq;
    VOS_UINT16                          usWPriBands;
    VOS_UINT16                          usGPriBands;
    VOS_UINT16                          usSetPriBands;
    VOS_UINT8                           aucReserved[2];
}DRV_AGENT_RXPRI_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_PRODTYPE_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯ PRODTYPE ����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulProdType;

}DRV_AGENT_PRODTYPE_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_TBAT_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯ TBAT ����Ϣ�ظ��ṹ

1. ��    ��   : 2012��1��13��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulTbatType;

}DRV_AGENT_TBAT_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_RXPRI_QRY_CNF_STRU
 �ṹ˵��  : DRV��AT AGENT  ��ȡ����֧�ֵ�RX�ּ�

1. ��    ��   : 2011��10��22��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                      stAtAppCtrl;
    VOS_UINT16                           usWDrvPriBands;
    VOS_UINT16                           usGDrvPriBands;
    VOS_BOOL                             bFail;
}DRV_AGENT_RXPRI_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_ADC_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT ���� ADC ����Ϣ����ṹ

1. ��    ��   : 2011��11��5��
   ��    ��   : w00181244
   �޸�����   : ��monitorps.h����ֲ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulIsEnable;           /*�Ƿ���Ҫ������������, 0Ϊ�رգ�1Ϊ����*/
    VOS_INT32                   lCloseAdcThreshold;   /*����͹���ģʽ���¶�����*/
    VOS_INT32                   lAlarmAdcThreshold;   /*��Ҫ���и����������¶�����*/
    VOS_INT32                   lResumeAdcThreshold;  /*�ָ�������ģʽ���¶�����*/
}SPY_TEMP_THRESHOLD_PARA_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_ADC_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT ���� RXPRI ����Ϣ�ظ��ṹ

1. ��    ��   : 2011��10��15��
   ��    ��   : w00181244
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                        stAtAppCtrl;
    VOS_BOOL                               bFail;

}DRV_AGENT_ADC_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_VERSION_TIME_STRU
 �ṹ˵��  : AT��AT AGENT�汾��ѯ����ƽṹ

  1.��    ��   : 2011��10��15��
    ��    ��   : o00132663
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucReserved[2];
    VOS_CHAR                            aucData[AT_AGENT_DRV_VERSION_TIME_LEN+1];
} DRV_AGENT_VERSION_TIME_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_YJCX_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^YJCX��������ظ��ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UCHAR                           aucflashInfo[TAF_MAX_FLAFH_INFO_LEN + 1];
} DRV_AGENT_YJCX_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_YJCX_QRY_CNF_STRU
 �ṹ˵��  : AT��AT AGENT AT^YJCX��������ظ��ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UCHAR                           aucgpioInfo[TAF_MAX_GPIO_INFO_LEN + 1];
    VOS_UINT8                           aucReserved[3];
} DRV_AGENT_YJCX_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_IMSICHG_QRY_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT��ѯIMSICHG�ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulCurImsiSign;
    VOS_UINT16                          usDualIMSIEnable;
    VOS_UINT8                           aucReserved[2];
}DRV_AGENT_IMSICHG_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_INFORBU_SET_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT����INFORBU�ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_INFORBU_SET_CNF_STRU;

/* Add by h00135900 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_INFORRS_SET_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT����INFORRU�ظ��ṹ

1. ��    ��   : 2012��04��11��
   ��    ��   : H00135900
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_INFORRS_SET_CNF_STRU;

/* Add by h00135900 for V7����ͬ��, 2012-04-07, End   */

/*****************************************************************************
 �ṹ��    : DRV_AGENT_CPNN_TEST_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT CPNN��������ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bNormalSrvStatus;
    VOS_UINT32                          ulPnnExistFlg;
    VOS_UINT32                          ulOplExistFlg;

}DRV_AGENT_CPNN_TEST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_CPNN_TEST_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT CPNN��������ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_NVBACKUP_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_CPNN_QRY_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT CPNN��ѯ����ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_BOOL                            bNormalSrvStatus;
}DRV_AGENT_CPNN_QRY_CNF_STRU;

/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  begin */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_MEMINFO_QRY_RSP_STRU
 �ṹ˵��  : DRV��TAF AGENT AT^MEMINFO����ظ��ṹ

  1.��    ��   : 2011��11��29��
    ��    ��   : l00171473
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                         stAtAppCtrl;
    VOS_UINT32                              ulResult;
    AT_MEMQUERY_PARA_ENUM_UINT32            ulMemQryType;                       /* ��ѯ�����ͣ�0:VOS�ڴ�, 1: TTF�ڴ� */
    VOS_UINT32                              ulPidNum;                           /* PID�ĸ��� */
    VOS_UINT8                               aucData[4];                         /* ÿ��PID���ڴ�ʹ����� */
}DRV_AGENT_MEMINFO_QRY_RSP_STRU;
/* Added by l00171473 for �ڴ���AT����, 2011-11-29,  end */

/*****************************************************************************
 �ṹ��    : DRV_AGENT_TSELRF_SET_CNF_STRU
 �ṹ˵��  : DRV��TAF DRV AGENT TSELRF��������ظ��ṹ

1. ��    ��   : 20112��01��10��
   ��    ��   : f62575
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                         stAtAppCtrl;
    DRV_AGENT_TSELRF_SET_ERROR_ENUM_UINT32  enResult;
    VOS_UINT8                               ucDeviceRatMode;
    VOS_UINT8                               aucReserved[3];
}DRV_AGENT_TSELRF_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_HKADC_GET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT ��ȡHKADC��ѹ ����Ϣ�ظ��ṹ

1. ��    ��   : 20112��01��10��
   ��    ��   : f62575
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                             stAtAppCtrl;
    DRV_AGENT_HKADC_GET_ERROR_ENUM_UINT32  enResult;
    VOS_INT32                                                   TbatHkadc;
}DRV_AGENT_HKADC_GET_CNF_STRU;



#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*****************************************************************************
 �ṹ��    : DRV_AGENT_SPWORD_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT ��ȡSPWORD����Ϣ����ṹ

1. ��    ��   : 2012��02��21��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acShellPwd[AT_SHELL_PWD_LEN];
}DRV_AGENT_SPWORD_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SPWORD_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT ��ȡSPWORD����Ϣ�ظ��ṹ

1. ��    ��   : 2012��02��21��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_SPWORD_SET_CNF_STRU;
#endif

/*****************************************************************************
 �ṹ��    : DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯNV����״̬��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��16��
   ��    ��   : l00198894
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /* ��Ϣͷ */
    VOS_UINT32                          ulResult;                               /* ���ؽ�� */
    VOS_UINT32                          ulNvBackupStat;                         /* NV����״̬ */
}DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_NANDBBC_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯNAND FLASH�����л��������б���Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��16��
   ��    ��   : l00198894
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                            /* ��Ϣͷ */
    VOS_UINT32                          ulResult;                               /* ���ؽ�� */
    VOS_UINT32                          ulBadBlockNum;                          /* �������� */
    VOS_UINT32                          aulBadBlockIndex[0];                    /* ���������� */
} DRV_AGENT_NANDBBC_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_NAND_DEV_INFO_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯNAND FLASH���豸��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��16��
   ��    ��   : l00198894
   �޸�����   : �����ṹ
*****************************************************************************/
#define DRV_AGENT_NAND_MFU_NAME_MAX_LEN     16                                  /* ����������󳤶� */
#define DRV_AGENT_NAND_DEV_SPEC_MAX_LEN     32                                  /* �豸�����󳤶� */

typedef struct
{
    VOS_UINT32      ulMufId;                                                    /* ����ID */
    VOS_UINT8       aucMufName[DRV_AGENT_NAND_MFU_NAME_MAX_LEN];                /* ���������ַ��� */
    VOS_UINT32      ulDevId;                                                    /* �豸ID */
    VOS_UINT8       aucDevSpec[DRV_AGENT_NAND_DEV_SPEC_MAX_LEN];                /* �豸����ַ��� */
} DRV_AGENT_NAND_DEV_INFO_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_NANDVER_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯNAND FLASH���ͺ���Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��16��
   ��    ��   : l00198894
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* ��Ϣͷ */
    VOS_UINT32                          ulResult;                    /* ���ؽ�� */
    DRV_AGENT_NAND_DEV_INFO_STRU        stNandDevInfo;               /* �豸��Ϣ */
} DRV_AGENT_NANDVER_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_CHIPTEMP_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯPA��SIM���͵�ص��¶���Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2012��02��16��
   ��    ��   : l00198894
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* ��Ϣͷ */
    VOS_UINT32                          ulResult;                    /* ���ؽ�� */
    VOS_INT                             lGpaTemp;                    /* G PA�¶� */
    VOS_INT                             lWpaTemp;                    /* W PA�¶� */
    VOS_INT                             lLpaTemp;                    /* L PA�¶� */
    VOS_INT                             lSimTemp;                    /* SIM���¶� */
    VOS_INT                             lBatTemp;                    /* ����¶� */
} DRV_AGENT_CHIPTEMP_QRY_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_ANTSWITCH_SET_STRU
 �ṹ˵��  : AT��DRV AGENT����������Ϣ
 1.��    ��   : 2013��11��11��
   ��    ��   : y00258578
   �޸�����   : �����ṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulState;                    /* ����״̬ */

} DRV_AGENT_ANTSWITCH_SET_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_ANTSWITCH_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��������Ӧ����Ϣ
 1.��    ��   : 2013��11��11��
   ��    ��   : y00258578
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* ��Ϣͷ */
    VOS_UINT32                          ulResult;                    /* ���ؽ�� */

} DRV_AGENT_ANTSWITCH_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_ANTSWITCH_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯ����Ӧ����Ϣ
 1.��    ��   : 2013��11��11��
   ��    ��   : y00258578
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* ��Ϣͷ */
    VOS_UINT32                          ulState;                     /* ����״̬ */
    VOS_UINT32                          ulResult;                    /* ���ؽ�� */

} DRV_AGENT_ANTSWITCH_QRY_CNF_STRU;



/*****************************************************************************
 �ṹ��    : DRV_AGENT_ANT_STATE_IND_STRU
 �ṹ˵��  : AT��DRV AGENT ����ANT STATE IND����Ϣ�ظ��ṹ

1. ��    ��   : 2012��12��25��
   ��    ��   : l00227485
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;                 /* ��Ϣͷ */
    VOS_UINT16                          usAntState;
    VOS_UINT8                           aucRsv[2];
} DRV_AGENT_ANT_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT ����MAX LOCK TIMES����Ϣ�ظ��ṹ

1. ��    ��   : 2012��03��19��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_AP_SIMST_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT����APSIMST����Ϣ����ṹ

1. ��    ��   : 2012��06��18��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsimState;
}DRV_AGENT_AP_SIMST_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_AP_SIMST_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT ����APSIMST����Ϣ�ظ��ṹ

1. ��    ��   : 2012��06��18��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}DRV_AGENT_AP_SIMST_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_HUK_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT����HUK����Ϣ����ṹ

  1.��    ��   : 2012��04��07��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucHUK[DRV_AGENT_HUK_LEN];  /* HUK���� 128Bits */
}DRV_AGENT_HUK_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_HUK_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT����HUK����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��07��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_HUK_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT���ü�Ȩ��Կ����Ϣ����ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    /* ��Ȩ��Կ���� */
    VOS_UINT8                           aucPubKey[DRV_AGENT_PUBKEY_LEN];
    /* ��Ȩ��ԿSSKǩ������ */
    VOS_UINT8                           aucPubKeySign[DRV_AGENT_PUBKEY_SIGNATURE_LEN];
}DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT���ü�Ȩ��Կ����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT������߼�Ȩ����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
    /* ʹ�ù�Կ����RSA���ܺ������ */
    VOS_UINT8                                       aucRsaText[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_IDENTIFYEND_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT��ɲ��߼�Ȩ����Ϣ����ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    /* ʹ��˽Կ����RSA���ܺ������ */
    VOS_UINT8                           aucRsaText[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_IDENTIFYEND_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_IDENTIFYEND_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ɲ��߼�Ȩ����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_IDENTIFYEND_SET_CNF_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU
�ṹ˵��  : AT��DRV AGENT��������������Ϣ����Ϣ����ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    /* �ṹ������, �����������������͵İ���״̬, �����Ŷ�, CK, UK��������Ϣ */
    VOS_UINT8       aucCategoryData[DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN];
}DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��������������Ϣ����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_PH_LOCK_CODE_STRU
�ṹ˵��  : ���������Ŷνṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
   VOS_UINT8        aucPhLockCodeBegin[DRV_AGENT_PH_LOCK_CODE_LEN];
   VOS_UINT8        aucPhLockCodeEnd[DRV_AGENT_PH_LOCK_CODE_LEN];
}DRV_AGENT_PH_LOCK_CODE_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU
�ṹ˵��  : ����������ȫ���ݵ������͵����ݽṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8           enCategory;             /* ����������category��� */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8          enIndicator;            /* ���������ļ���ָʾ */
    DRV_AGENT_PERSONALIZATION_STATUS_ENUM_UINT8             enStatus;
    VOS_UINT8                                               ucMaxUnlockTimes;       /* �������������������� */
    VOS_UINT8                                               ucRemainUnlockTimes;    /* ����������ʣ��������� */
    VOS_UINT8                                               aucRsv[3];              /* �����ֽڣ��������ֽڶ��� */
}DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU
�ṹ˵��  : AT��DRV AGENT��ѯ����������ȫ���ݵ���Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
    /* Ŀǰ֧��3��category���ṹ�����鰴��network->network subset->SP��˳������ */
    DRV_AGENT_SIMLOCK_DATA_CATEGORY_STRU            astCategoryData[DRV_AGENT_SUPPORT_CATEGORY_NUM];
}DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU
�ṹ˵��  : ����������Ϣ�������͵����ݽṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8           enCategory;             /* ����������category��� */
    DRV_AGENT_PERSONALIZATION_INDICATOR_ENUM_UINT8          enIndicator;            /* ���������ļ���ָʾ */
    VOS_UINT8                                               ucGroupNum;             /* �Ŷθ�����һ��begin/end��һ���Ŷ� */
    VOS_UINT8                                               ucRsv;                  /* 4�ֽڶ���, ����λ */
    /* ���������ĺŶ�����*/
    DRV_AGENT_PH_LOCK_CODE_STRU                             astLockCode[DRV_AGENT_PH_LOCK_CODE_GROUP_NUM];
}DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU;

/*****************************************************************************
�ṹ��    : DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU
�ṹ˵��  : AT��DRV AGENT��ѯ����������Ϣ����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
    /* Ŀǰ֧��3��category���ṹ�����鰴��network->network subset->SP��˳������ */
    DRV_AGENT_SIMLOCK_INFO_CATEGORY_STRU            astCategoryInfo[DRV_AGENT_SUPPORT_CATEGORY_NUM];
}DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT��������ŵ���Ϣ����ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8 enPhynumType;                                   /* ��������� */
    VOS_UINT8                           aucPhynumValue[DRV_AGENT_RSA_CIPHERTEXT_LEN];   /* �����RSA�������� */
}DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��������ŵ���Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯ����ŵ���Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
    VOS_UINT8                                       aucImeiRsa[DRV_AGENT_RSA_CIPHERTEXT_LEN];
    VOS_UINT8                                       aucSnRsa[DRV_AGENT_RSA_CIPHERTEXT_LEN];
}DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT��ʱ��ͨ�Ŷ˿ڵ���Ϣ����ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucPortPassword[DRV_AGENT_PORT_PASSWORD_LEN];               /* ͨ�Ŷ˿������� */
}DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ʱ��ͨ�Ŷ˿ڵ���Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT����ͨ�Ŷ˿ڿ�����ʼ״̬���˿����������Ϣ����ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    DRV_AGENT_PORT_STATUS_ENUM_UINT32   enPortStatus;                                   /* ͨ�Ŷ˿�״̬ */
    VOS_UINT8                           aucPortPassword[DRV_AGENT_RSA_CIPHERTEXT_LEN];  /* ͨ�Ŷ˿������� */
}DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT����ͨ�Ŷ˿ڿ�����ʼ״̬���˿����������Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ѯͨ�Ŷ˿ڿ�����ʼ״̬����Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
    DRV_AGENT_PORT_STATUS_ENUM_UINT32               enPortStatus;               /* ͨ�Ŷ˿�״̬ */
}DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_OPWORD_SET_REQ_STRU
 �ṹ˵��  : AT��DRV AGENT��ȡ����DIAG�ںͿ���SHELL�ڵ�Ȩ�޵���Ϣ����ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucPortPassword[DRV_AGENT_PORT_PASSWORD_LEN];               /* ͨ�Ŷ˿������� */
}DRV_AGENT_OPWORD_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_OPWORD_SET_CNF_STRU
 �ṹ˵��  : AT��DRV AGENT��ȡ����DIAG�ںͿ���SHELL�ڵ�Ȩ�޵���Ϣ�ظ��ṹ

  1.��    ��   : 2012��04��10��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32       enResult;                   /* ����ִ�н�� */
}DRV_AGENT_OPWORD_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_HVPDH_REQ_STRU
 �ṹ˵��  : ����Ԥ��DH��Կ��AT��SC������Կ��Ϣ���õ����ݽṹ

  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
typedef struct
{
    DRV_AGENT_DH_KEY_TYPE_ENUM_UINT32   enKeyType;                              /* DH��Կ���� */
    VOS_UINT32                          ulKeyLen;                               /* DH��Կ���� */
    VOS_UINT8                           aucKey[DRV_AGENT_DH_PUBLICKEY_LEN];     /* DH��Կ������󳤶����������飬�Ա����ڴ洢��Կ��˽Կ */
}DRV_AGENT_HVPDH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DRV_AGENT_HVPDH_CNF_STRU
 �ṹ˵��  : SC��AT����д��Ԥ��DH��Կ����Ӧ���

  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                                 stAtAppCtrl;                /* ��Ϣͷ */
    DRV_AGENT_HVPDH_ERR_ENUM_UINT32                 enResult;                   /* ����ִ�н�� */
}DRV_AGENT_HVPDH_CNF_STRU;

/* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, begin */
/*****************************************************************************
 �ṹ��    : DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU
 �ṹ˵��  : AT��TAF DRV AGENT ��ȡNVǿ�ƻָ��������õ���Ϣ�ظ��ṹ

1. ��    ��   : 2011��11��3��
   ��    ��   : l60609
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulRslt;
}DRV_AGENT_NVMANUFACTUREEXT_SET_CNF_STRU;
/* Added by d00212987 for BalongV9R1 NV�������ݶ�ʧ�ݴ�&�ָ� ��Ŀ 2013-10-24, end */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32      ulMsgId;   /*_H2ASN_MsgChoice_Export DRV_AGENT_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          DRV_AGENT_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}DRV_AGENT_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    DRV_AGENT_MSG_DATA                  stMsgData;
}TafDrvAgent_MSG;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_SWVER_INFO_STRU
 �ṹ˵��  : ƽ̨����汾��
 1.��    ��   : 2012��11��24��
   ��    ��   : s00190137
   �޸�����   : �ֻ���Ʒ��ѯmodem�汾�Žӿ������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSWVer[TAF_MAX_REVISION_ID_LEN + 1];
    VOS_CHAR                            acVerTime[AT_AGENT_DRV_VERSION_TIME_LEN];
}DRV_AGENT_SWVER_INFO_STRU;


/*****************************************************************************
 �ṹ��    : DRV_AGENT_SWVER_SET_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ��ѯSWVER��Ϣ��Ϣ�ظ��ṹ
 1.��    ��   : 2012��11��24��
   ��    ��   : s00190137
   �޸�����   : �ֻ���Ʒ��ѯmodem�汾�Žӿ������ṹ
*****************************************************************************/
typedef struct
{
    AT_APPCTRL_STRU                       stAtAppCtrl;
    DRV_AGENT_ERROR_ENUM_UINT32           enResult;
    DRV_AGENT_SWVER_INFO_STRU             stSwverInfo;
} DRV_AGENT_SWVER_SET_CNF_STRU;



/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32   GAS_AtCmd(GAS_AT_CMD_STRU *pstAtCmd,GAS_AT_RSLT_STRU *pstAtCmdRslt);

extern VOS_VOID MMA_GetProductionVersion(VOS_CHAR *pcDest);
extern VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
extern VOS_UINT32 AT_GetWcdmaBandStr(VOS_UINT8 *pucGsmBandstr, AT_UE_BAND_CAPA_ST *pstBandCapa);
extern VOS_UINT32 AT_GetGsmBandStr(VOS_UINT8 *pucGsmBandstr , AT_UE_BAND_CAPA_ST *pstBandCapa);
extern VOS_UINT32 At_SendRfCfgAntSelToHPA(
    VOS_UINT8                           ucDivOrPriOn,
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 At_DelCtlAndBlankCharWithEndPadding(VOS_UINT8 *pucData, VOS_UINT16  *pusCmdLen);
extern VOS_UINT32 Spy_SetTempPara(SPY_TEMP_THRESHOLD_PARA_STRU *stTempPara);

/* Add by w00184875 For L��SAR begin */
#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID L_ExtSarPowerReductionPRI(VOS_UINT32 para);
#endif
/* Add by w00184875 For L��SAR end */


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafDrvAgent.h */
