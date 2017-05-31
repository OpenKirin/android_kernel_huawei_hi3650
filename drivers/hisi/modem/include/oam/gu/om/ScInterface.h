

/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ScInterface.h
  �� �� ��   : ����
  ��    ��   : ��Ц��
  ��������   : 2012��4��3��
  ����޸�   :
  ��������   : SCģ���ṩ���ⲿģ��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����

******************************************************************************/

#ifndef __SCINTERFACE_H__
#define __SCINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define   SC_MAX_SUPPORT_CATEGORY   (3)   /* ֧�ֵ���������CATEGORY�������Ŀǰֻ֧������:network/network subset/SP */

#define   SC_MAX_CODE_LEN           (4)   /* �Ŷε���󳤶�(����Ϊ3��������Ϊ4����SPΪ4��ȡ����) */

#define   SC_MAX_CODE_NUM           (20)  /* ���������Ŷ������� */

#define   SC_AUTH_PUB_KEY_LEN       (520) /* ��Ȩ��Կ���� */

#define   SC_SIGNATURE_LEN          (32)  /* ǩ������ */

#define   SC_RSA_ENCRYPT_LEN        (128) /* ����RSA���ܺ�����ĳ��� */

#define   SC_CRYPTO_PWD_LEN         (16)  /* ��������ĳ��� */

#define   SC_PERS_PWD_LEN           (16)  /* CK/UK/DK��������ĳ��� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : SC_ERROR_CODE_ENUM
ö��˵��  : SCģ�������ö�ٶ���

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_ERROR_CODE_ENUM
{
    SC_ERROR_CODE_NO_ERROR = 0,                     /* �����ɹ� */
    SC_ERROR_CODE_OPEN_FILE_FAIL,                   /* ���ļ�ʧ�� */
    SC_ERROR_CODE_READ_FILE_FAIL,                   /* ��ȡ�ļ�ʧ�� */
    SC_ERROR_CODE_WRITE_FILE_FAIL,                  /* д���ļ�ʧ�� */
    SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL,            /* ǩ��У��ʧ�� */
    SC_ERROR_CODE_DK_INCORRECT,                     /* DK���벻��ȷ */
    SC_ERROR_CODE_UNLOCK_KEY_INCORRECT,             /* CK/UK���벻��ȷ */
    SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL,           /* ����/UNBLOCKʱ��״̬����ȷ */
    SC_ERROR_CODE_RSA_ENCRYPT_FAIL,                 /* RSA����ʧ�� */
    SC_ERROR_CODE_RSA_DECRYPT_FAIL,                 /* RSA����ʧ�� */
    SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL,    /* ��Ȩ��Կ��ժҪǩ��У��ʧ�� */
    SC_ERROR_CODE_GET_RAND_NUMBER_FAIL,             /* ��ȡ�����ʧ��(crypto_rand) */
    SC_ERROR_CODE_IDENTIFY_FAIL,                    /* ���߼�Ȩʧ�� */
    SC_ERROR_CODE_IDENTIFY_NOT_FINISH,              /* ��δ��ɲ��߼�Ȩ */
    SC_ERROR_CODE_LOCK_CODE_INVALID,                /* �����Ŷα���ȡֵ����ȷ */
    SC_ERROR_CODE_CREATE_KEY_FAIL,                  /* ��Կ����ʧ��(create_crypto_key) */
    SC_ERROR_CODE_GENERATE_HASH_FAIL,               /* ����HASHʧ��(crypto_hash) */
    SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL,             /* AES ECB�㷨����ʧ��(crypto_encrypt) */
    SC_ERROR_CODE_WRITE_HUK_FAIL,                   /* HUKд����� */
    SC_ERROR_CODE_ALLOC_MEM_FAIL,                   /* �����ڴ�ʧ�� */
    SC_ERROR_CODE_PARA_FAIL,                        /* ����������� */
    SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL,             /* IMEI����д���ļ����� */
    SC_ERROR_CODE_CMP_IMEI_FAIL,                    /* �Ƚ�IMEI�ַ���ʧ�� */
    SC_ERROR_CODE_MODEM_ID_FAIL,                    /* ModemID ���� */
    SC_ERROR_CODE_NV_READ_FAIL,                     /* NV��ʧ�� */
    SC_ERROR_CODE_NV_WRITE_FAIL,                    /* NVдʧ�� */
    SC_ERROR_CODE_SCCONTENT_WRITE_FAIL,             /* SC�ļ�д�뱸����ʧ�� */
    SC_ERROR_CODE_SCBACKUP_READ_FAIL,               /* ��ȡSC������ʧ�� */
    SC_ERROR_CODE_MAGNUM_CMP_FAIL,                  /* �Ƚ�SC���������ʧ�� */
    SC_ERROR_CODE_SCFILE_RESTORE_FAIL,              /* SC�ļ�д��ʹ����ʧ�� */
    SC_ERROR_CODE_SC_NO_NEED_RESTORE,               /* SC�ļ�����Ҫ�ָ� */
    SC_ERROR_CODE_OTHER_ERROR,                      /* �������� */

    SC_ERROR_CODE_BUTT
};
typedef VOS_UINT32  SC_ERROR_CODE_ENUM_UINT32;

/*****************************************************************************
ö����    : SC_PERSONALIZATION_CATEGORY_ENUM
ö��˵��  : ����������category����

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_PERSONALIZATION_CATEGORY_ENUM
{
    SC_PERSONALIZATION_CATEGORY_NETWORK                     = 0x00, /* category:���� */
    SC_PERSONALIZATION_CATEGORY_NETWORK_SUBSET              = 0x01, /* category:������ */
    SC_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER            = 0x02, /* category:��SP */
    SC_PERSONALIZATION_CATEGORY_CORPORATE                   = 0x03, /* category:������ */
    SC_PERSONALIZATION_CATEGORY_SIM_USIM                    = 0x04, /* category:��(U)SIM�� */

    SC_PERSONALIZATION_CATEGORY_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_CATEGORY_ENUM_UINT8;


/*****************************************************************************
ö����    : SC_PERSONALIZATION_INDICATOR_ENUM
ö��˵��  : ָ�����������������Ƿ񼤻�

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_PERSONALIZATION_INDICATOR_ENUM
{
    SC_PERSONALIZATION_INDICATOR_INACTIVE                   = 0x00, /* δ���� */
    SC_PERSONALIZATION_INDICATOR_ACTIVE                     = 0x01, /* �Ѽ��� */

    SC_PERSONALIZATION_INDICATOR_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_INDICATOR_ENUM_UINT8;


/*****************************************************************************
ö����    : SC_PERSONALIZATION_STATUS_ENUM
ö��˵��  : ָ���������������͵�״̬

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_PERSONALIZATION_STATUS_ENUM
{
    SC_PERSONALIZATION_STATUS_READY     = 0x00, /* �Ѿ����� */
    SC_PERSONALIZATION_STATUS_PIN       = 0x01, /* δ����״̬������������� */
    SC_PERSONALIZATION_STATUS_PUK       = 0x02, /* Block״̬��������UnBlock�� */

    SC_PERSONALIZATION_STATUS_BUTT
};
typedef VOS_UINT8 SC_PERSONALIZATION_STATUS_ENUM_UINT8;


/*****************************************************************************
ö����    : SC_VERIFY_SIMLOCK_RESULT_ENUM
ö��˵��  : ����У��Ľ��

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_VERIFY_SIMLOCK_RESULT_ENUM
{
    SC_VERIFY_SIMLOCK_RESULT_READY            = 0x00, /* READY: MT is not pending for any simlock */
    SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN       = 0x01, /* PH-NET PIN: MT is waiting network personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK       = 0x02, /* PH-NET PUK: MT is waiting network personalization unblocking password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN    = 0x03, /* PH-NETSUB PIN: MT is waiting network subset personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK    = 0x04, /* PH-NETSUB PUK: MT is waiting network subset personalization unblocking password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN        = 0x05, /* PH-SP PIN: MT is waiting service provider personalization password to be given */
    SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK        = 0x06, /* PH-SP PUK: MT is waiting service provider personalization unblocking password to be given */

    SC_VERIFY_SIMLOCK_RESULT_BUTT
};
typedef VOS_UINT8 SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8;


/*****************************************************************************
ö����    : SC_PORT_STATUS_ENUM
ö��˵��  : �˿���״̬(HSIC��OM�˿�)

  1.��    ��   : 2012��4��4��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum SC_PORT_STATUS_ENUM
{
    SC_PORT_STATUS_OFF                  = 0x00, /* �˿ڹر� */
    SC_PORT_STATUS_ON                   = 0x01, /* �˿ڴ� */

    SC_PORT_STATUS_BUTT
};
typedef VOS_UINT32 SC_PORT_STATUS_ENUM_UINT32;

/*****************************************************************************
ö����    : SC_DH_KEY_TYPE_ENUM
ö��˵��  : DH�㷨ʹ�õ���Կ����

  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
enum SC_DH_KEY_TYPE_ENUM
{
    SC_DH_KEY_SERVER_PUBLIC_KEY         = 0x00,             /* ��������Կ */
    SC_DH_KEY_MODEM_PUBLIC_KEY          = 0x01,             /* MODEM�๫Կ */
    SC_DH_KEY_MODEM_PRIVATE_KEY         = 0x02,             /* MODEM��˽Կ */

    SC_DH_KEY_BUTT
};
typedef VOS_UINT32 SC_DH_KEY_TYPE_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
�ṹ��    : SC_PH_LOCK_CODE_STRU
�ṹ˵��  : ���������Ŷνṹ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            aucPhLockCodeBegin[SC_MAX_CODE_LEN];
   VOS_UINT8                            aucPhLockCodeEnd[SC_MAX_CODE_LEN];
}SC_PH_LOCK_CODE_STRU;


/*****************************************************************************
�ṹ��    : SC_SIMLOCK_CATEGORY_STRU
�ṹ˵��  : �ṩ��NAS��ȡSIMLOCK��Ϣ�Ļ������ݽṹ��
            ��������������Catetory����ӦIndicator����ӦStatus��������������ʣ���������
            �Ŷ������Ŷ������begin/end

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;                  /* ����������category��� */
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator;                 /* ���������ļ���ָʾ */
    SC_PERSONALIZATION_STATUS_ENUM_UINT8                    enStatus;                    /* ���������ĵ�ǰ״̬ */
    VOS_UINT8                                               ucMaxUnlockTimes;            /* �������������������� */
    VOS_UINT8                                               ucRemainUnlockTimes;         /* ����������ʣ��������� */
    VOS_UINT8                                               aucReserved[2];              /* �����ֽڣ��������ֽڶ��� */
    VOS_UINT8                                               ucGroupNum;                  /* �Ŷθ�����һ��begin/end��һ���Ŷ� */
    SC_PH_LOCK_CODE_STRU                                    astLockCode[SC_MAX_CODE_NUM];/* ���������ĺŶ�����*/
}SC_SIMLOCK_CATEGORY_STRU;

/*****************************************************************************
�ṹ��    : SC_WRITE_SIMLOCK_DATA_STRU
�ṹ˵��  : �ṩ��NAS����AT^SIMLOCKDATAWRITEд��SIMLOCK��Ϣ�����ݽṹ��

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8                  enCategory;                  /* ����������category��� */
    SC_PERSONALIZATION_INDICATOR_ENUM_UINT8                 enIndicator;                 /* ���������ļ���ָʾ */
    VOS_UINT8                                               ucMaxUnlockTimes;            /* �������������������� */
    VOS_UINT8                                               ucGroupNum;                  /* �Ŷθ�����һ��begin/end��һ���Ŷ� */
    SC_PH_LOCK_CODE_STRU                                    astLockCode[SC_MAX_CODE_NUM];/* ���������ĺŶ�����*/
    /* astLockCodeժҪ���ģ����ɹ��̣�aucSimlockRsaData����astLockCode�Ⱦ���MD5�㷨����ժҪ��
       Ȼ��ʹ��USB dog�е�˽Կ���м��ܵ�У�����ݡ� ��simlock code�Ϸ��Լ���ʱ����ʹ��AK-File��
       �Ĺ�Կ��aucSimlockRsaData���н��ܣ�Ȼ����astLockCodeʹ��MD5���ɵ�ժҪ���бȽϡ�*/
    VOS_UINT8                                               aucSimlockRsaData[SC_RSA_ENCRYPT_LEN];
    /* �����Ľ������룬��16λ��PIN��ʹ��USB dog�е�˽Կ���м��ܵ����� */
    VOS_UINT8                                               aucLockRsaPin[SC_RSA_ENCRYPT_LEN];
    /* ������UnBlock���룬��16λ��PUK��ʹ��USB dog�е�˽Կ���м��ܵ����� */
    VOS_UINT8                                               aucLockRsaPuk[SC_RSA_ENCRYPT_LEN];
}SC_WRITE_SIMLOCK_DATA_STRU;



/*****************************************************************************
�ṹ��    : SC_SET_FAC_AUTH_PUB_KEY_STRU
�ṹ˵��  : �ṩ��NAS����AT^FACAUTHPUBKEYд���Ȩ��Կ�����ݽṹ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8       aucAuthPubKey[SC_AUTH_PUB_KEY_LEN];   /* ��Ȩ��Կ */
    VOS_UINT8       aucSignature[SC_SIGNATURE_LEN];       /* ��Ȩ��Կ��ժҪ��AES-ECB�㷨(��ԿΪSSK)�������ɵ�ժҪǩ�� */
}SC_SET_FAC_AUTH_PUB_KEY_STRU;


/*****************************************************************************
�ṹ��    : SC_IDENTIFY_START_RESPONSE_STRU
�ṹ˵��  : �ṩ��NAS����AT^IDENTIFYSTART���ڻ�ȡ<identify_start_response>���������ݽṹ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    /* SC��ȡ����������ù�Կ����RSA���ܺ������ */
    VOS_UINT8       aucIdentifyStartRsp[SC_RSA_ENCRYPT_LEN];
}SC_IDENTIFY_START_RESPONSE_STRU;


/*****************************************************************************
�ṹ��    : SC_IDENTIFY_END_REQUEST_STRU
�ṹ˵��  : NAS������AT^IDENTIFYEND�е�<identify_end_request>�����ύ��SCʱʹ�õ����ݽṹ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    /* ��̨ͨ��˽Կ��<identify_start_response>�������������������˽Կ���������������<identify_end_request>��
       ͨ������^IDENTIFYEND����<identify_end_request>���͸�Э��ջ��Э��ջʹ�ø����ݺͲ��߼�Ȩ��Կ��ԭ�������
       ����ԭ�������ԭ�����һ�����Ȩͨ�������򣬼�Ȩʧ�� */
    VOS_UINT8       aucIdentifyEndReq[SC_RSA_ENCRYPT_LEN];
}SC_IDENTIFY_END_REQUEST_STRU;


/*****************************************************************************
�ṹ��    : SC_SET_PORT_ATTRIBUTE_STRU
�ṹ˵��  : NAS������AT^PORTATTRSET�е�<onoff>��<port_passwd>�ύ��SCʱʹ�õ����ݽṹ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    /* AT����^IDENTIFYEND�еĲ���<onoff>��ֵ */
    SC_PORT_STATUS_ENUM_UINT32          enStatus;

    /* AT����^IDENTIFYEND�еĲ���<port_passwd>��ֵ��<port_passwd>Ϊ16λ���루���볤��
       Ϊ�̶���16����0��-��9���ַ�������RSA�������ɵ�128�ֽ����� */
    VOS_UINT8                           aucRsaPwd[SC_RSA_ENCRYPT_LEN];
}SC_SET_PORT_ATTRIBUTE_STRU;

/*****************************************************************************
 �ṹ��    : SC_CK_CATEGORY_STRU
 �ṹ˵��  : ÿһ������CK/UK���뱣�淽ʽ

  1.��    ��   : 2012��4��7��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucCKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* CK���� */
    VOS_UINT8                           aucUKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* UK���� */
}SC_CK_CATEGORY_STRU;


/*****************************************************************************
 �ṹ��    : SC_PI_FILE_STRU
 �ṹ˵��  : PI�ļ������ݽṹ

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/

typedef struct
{
    /* Ŀǰ֧��3��category���ṹ�����鰴��network->network subset->SP��˳������ */
    SC_SIMLOCK_CATEGORY_STRU            astSimlockCategory[SC_MAX_SUPPORT_CATEGORY];
}SC_PI_FILE_STRU;

/*****************************************************************************
 �ṹ��    : SC_CK_FILE_STRU
 �ṹ˵��  : CK-FILE�Ĵ洢�ṹ
             ����3��Category����Ӧ��CK/UK���룬���Ĵ洢

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    /* Ŀǰ֧��3��category���ṹ�����鰴��network->network subset->SP��˳������ */
    SC_CK_CATEGORY_STRU                 astCKCategory[SC_MAX_SUPPORT_CATEGORY];
}SC_CK_FILE_STRU;

/*****************************************************************************
 �ṹ��    : SC_DK_FILE_STRU
 �ṹ˵��  : DK�ļ������ݽṹ

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    SC_PORT_STATUS_ENUM_UINT32          enPortStatus;       /* �˿���״̬������ */
    VOS_UINT8                           aucDKCryptoPwd[SC_CRYPTO_PWD_LEN]; /* DK���� */
}SC_DK_FILE_STRU;


/*****************************************************************************
 �ṹ��    : SC_AK_FILE_STRU
 �ṹ˵��  : AK�ļ������ݽṹ

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAuthPubKey[SC_AUTH_PUB_KEY_LEN];    /* AK���� */
}SC_AK_FILE_STRU;


/*****************************************************************************
 �ṹ��    : SC_SIGN_FILE_STRU
 �ṹ˵��  : ǩ���ļ������ݽṹ

  1.��    ��   : 2012��04��09��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSignature[SC_SIGNATURE_LEN];    /* ǩ���ļ����� */
}SC_SIGN_FILE_STRU;

/*****************************************************************************
�ṹ��    : SC_SIMLOCK_INFO_STRU
�ṹ˵��  : �ṩ��NAS��ȡSIMLOCK��Ϣ�����ݽṹ��
            ����3��Category����Ӧ����������Ϣ

  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ�����ṹ
*****************************************************************************/
typedef SC_PI_FILE_STRU SC_SIMLOCK_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : SC_PERS_GetSimlockInfo
 ��������  : NASͨ���ýӿڻ�ȡSIMLOCK��Ϣ
 �������  : pstSimlockInfo:��ȡSIMLOCK��Ϣ�����ݽṹ���ɵ����������ڴ�
 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_GetSimlockInfo(SC_SIMLOCK_INFO_STRU *pstSimlockInfo);


/*****************************************************************************
 �� �� ��  : SC_PERS_WriteSimLockData
 ��������  : NAS�յ�AT^SIMLOCKDATAWRITE���ͨ���ýӿ�д��SIMLOCK��Ϣ
 �������  : pstWriteSimLockData: ��д��PI-FILE��CK-File��SIMLOCK��Ϣ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_WriteSimLockData(SC_WRITE_SIMLOCK_DATA_STRU *pstWriteSimLockData);

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifySimLock
 ��������  : ������������У��
 �������  : enModemID:Modem ID

 �������  : pucSimLockResult:��������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifySimLock(
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
);

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifyIMEI
 ��������  : Android��̬�£��ṩ��NAS���IMEI�Ƿ���֤ͨ��API��
 �������  :  enModemID    : ��0 ���߿�1

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyIMEI(MODEM_ID_ENUM_UINT16 enModemID);

/*****************************************************************************
 �� �� ��  : SC_PERS_NoVerifyNvReadImei
 ��������  : ��ȡ����NV���IMEI
             ˵��:��ȥУ�飬ֱ��ȥ��NV,������NV_Read�ӿڣ�SC_PERS_NoVerifyNvReadImei�ӿ���modem2 IMEIûд������£���ȡmodem0
 �������  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv ����

 �������  : *pItem    : ��ȡNV ����
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_NoVerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 �� �� ��  : SC_PERS_VerifyNvReadImei
 ��������  : ��ȡ����NV���IMEI,����IMEI��֤(����ֵΪ:SC_ERROR_CODE_NO_ERROR,��ȡ��NV���ݿ��ã����򲻿���)
             ˵��:��У��IMEI�ŵĺϷ��ԣ�Ȼ���ٶ�ȡNV�����IMEI�ŷǷ�����ȫ0 IMEI,������modem2 imei ûд������£���ȡmodem0
 �������  : enModemID : Modem ID
             usID      : Nv id
             ulLength  : Nv ����

 �������  : *pItem    : ��ȡNV ����
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32

 �޸���ʷ      :
  1.��    ��   : 2013��5��25��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_PERS_VerifyNvReadImei(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT16                          usID,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 �� �� ��  : SC_PERS_UnLock
 ��������  : ������UNBLOC����
 �������  : pcPwd: ��������
             ucLen: ���볤��
             enModemID:Modem ID
 �������  : pucSimLockResult:�������������������״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_PERS_UnLock(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen,
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 *penVerifySimlockRslt,
    MODEM_ID_ENUM_UINT16                enModemID
);

/*****************************************************************************
 �� �� ��  : SC_FAC_SetFacAuthPubKey
 ��������  : NAS�յ�AT^FACAUTHPUBKEY��ͨ���ýӿ�д���Ȩ��Կ
 �������  : pstSetFacAuthPubKey: ��Ȩ��Կ���ݽṹ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetFacAuthPubKey(SC_SET_FAC_AUTH_PUB_KEY_STRU *pstSetFacAuthPubKey);


/*****************************************************************************
 �� �� ��  : SC_FAC_StartIdentify
 ��������  : NAS�յ�AT^IDENTIFYSTART��ͨ���ýӿڻ�ȡ<identify_start_response>����
 �������  : NA

 �������  : pstIdentifyStartRsp: ���ڻ�ȡ<identify_start_response>���������ݽṹ��
             �ɵ����������ڴ�
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_StartIdentify(SC_IDENTIFY_START_RESPONSE_STRU *pstIdentifyStartRsp);


/*****************************************************************************
 �� �� ��  : SC_FAC_EndIdentify
 ��������  : NAS�յ�AT^IDENTIFYEND�����ͨ���ýӿڽ�<identify_end_request>�����ύ��SC
 �������  : pstIdentifyEndReq: ���ڴ洢<identify_end_request>���������ݽṹ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_EndIdentify(SC_IDENTIFY_END_REQUEST_STRU *pstIdentifyEndReq);


/*****************************************************************************
 �� �� ��  : SC_FAC_RsaEncrypt
 ��������  : NAS�յ�AT^PHONEPHYNUM?��ѯ���ͨ���ýӿڶ�����Ž���RSA����
 �������  : pcRawData: ����ţ����Ĵ洢
             ulLen: ����ų���
             pcCipherData: RSA���ܺ������
             pulCipherLen: RSA���ܺ�����ĳ���

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaEncrypt(
    VOS_UINT8   *pucRawData,
    VOS_UINT32   ulLen,
    VOS_UINT8   *pucCipherData,
    VOS_UINT32  *pulCipherLen
);


/*****************************************************************************
 �� �� ��  : SC_FAC_RsaDecrypt
 ��������  : NAS�յ�AT^PHONEPHYNUM�������ͨ���ýӿڶ�����Ž���RSA����
 �������  : pcCipherData: ����ţ����Ĵ洢
             ucCipherLen: ��������ĳ���
             pcRawData: RSA���ܺ�����������
             pucLen: RSA���ܺ����������ĳ���

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaDecrypt(
    VOS_UINT8  *pucCipherData,
    VOS_UINT32  ulCipherLen,
    VOS_UINT8  *pucRawData,
    VOS_UINT32 *pulLen
);

/*****************************************************************************
 �� �� ��  : SC_FAC_WriteHUK
 ��������  : NAS�յ�AT^HUK���ͨ����SC��װ�Ľӿ�д��HUK
 �������  : pcHuk: HUK������128bit
             ucLen: HUK��������

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteHUK(VOS_UINT8 *pucHuk, VOS_UINT32 ulLen);

/*****************************************************************************
 �� �� ��  : SC_FAC_WriteIMEI
 ��������  : NAS�յ�AT^PHONEPHYNUM�ͨ����SC��װ�Ľӿڰ�IMEI����д��IMEIFile.bin������ǩ��
 �������  : enModemID    : ��0 ���߿�1
             pucCipherData: IMEI��������
             ulCipherLen  : IMEI������������

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : d00212987
    �޸�����   : IMEI��֤
*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteIMEI(MODEM_ID_ENUM_UINT16    enModemID,
                                                  VOS_UINT8              *pucCipherData,
                                                  VOS_UINT32              ulCipherLen);

/*****************************************************************************
 �� �� ��  : SC_FAC_SetPortAttrib
 ��������  : NAS�յ�AT^PORTATTRIBSET���������ͨ���ýӿڽ��˿���������Ϣ�ύ��SC
 �������  : pstSetPortAttrib: �˿������������Ϣ

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetPortAttrib(SC_SET_PORT_ATTRIBUTE_STRU *pstSetPortAttrib);


/*****************************************************************************
 �� �� ��  : SC_FAC_GetPortAttrib
 ��������  : �ú�������������������:
             1.NAS�յ�AT^PORTATTRIBSET��ѯ�����ͨ���ýӿڶ�ȡ�˿���������Ϣ�еĶ˿���״̬
             2.�ϵ��ʼ��ʱ��C��OMͨ���ýӿڻ�ȡ�˿���״̬��֪ͨA��OM���ݶ˿���״̬�����Ƿ�ҽ�HSIC OM��
 �������  : NA

 �������  : penStatus: �˿�״̬
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_GetPortAttrib(SC_PORT_STATUS_ENUM_UINT32   *penStatus);

/*****************************************************************************
 �� �� ��  : SC_FAC_VerifyPortPassword
 ��������  : NAS�յ�AT^PORTCTRLTMP������øýӿڽ��ж˿�������У��
 �������  : pcPwd: �˿������룬����Ϊ���Ĵ���(����Ϊ16����0��-��9���ַ����)
             ucLen: �˿������볤��

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    ��    ��   : w00184875
    �޸�����   : ��ʼ����

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_FAC_VerifyPortPassword(VOS_UINT8 *pucPwd, VOS_UINT8 ucLen);

/*****************************************************************************
 �� �� ��  : SC_APSEC_ParseSecPacket
 ��������  : ������ȫ���
 �������  : VOS_UINT32 *pulSPLen       -- ��ȫ��������ֽ���
             VOS_UINT8  *pucSecPacket   -- ��ȫ�������������
 �������  : VOS_UINT32 *pulSPLen       -- �ظ���ȫ��������ֽ���
             VOS_UINT8  *pucSecPacket   -- �ظ���ȫ�������������
 �� �� ֵ  : VOS_OK     -- ��ȫ��������ɹ�
             VOS_ERR    -- ��ȫ�������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
extern VOS_UINT32 SC_APSEC_ParseSecPacket(
    VOS_UINT32                         *pulSPLen,
    VOS_UINT8                          *pucSecPacket );

/*****************************************************************************
 �� �� ��  : SC_PERS_SimlockUnlock
 ��������  : ����Simlock��������
 �������  : enCategory         -- ������������
             *pucPwd            -- ��������
 �������  : ��
 �� �� ֵ  : VOS_OK     -- �����ɹ�
             VOS_ERR    -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
extern VOS_UINT32 SC_PERS_SimlockUnlock(
    SC_PERSONALIZATION_CATEGORY_ENUM_UINT8  enCategory,
    VOS_UINT8                              *pucPwd );

/*****************************************************************************
 �� �� ��  : SC_COMM_InitVerifyRecordImeiMem
 ��������  : ��ʼ���洢У��IMIE�ռ�
 �������  :

 �������  :

 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 SC_COMM_InitVerifyRecordImeiMem(VOS_VOID);

#if (FEATURE_ON == FEATURE_VSIM)
/*****************************************************************************
 �� �� ��  : SC_FAC_SetDhKey
 ��������  : NAS�յ�AT^HVPDH���������ͨ���ýӿڽ�DH KEY�ύ��SC
 �������  : MODEM_ID_ENUM_UINT16         enModemID,
             SC_DH_KEY_TYPE_ENUM_UINT32   enKeyType,
             VOS_UINT32                   ulKeyLen,
             VOS_UINT8                   *pucKey

 �������  : NA
 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : L47619
    �޸�����   : V9R1 vSIM��Ŀ�޸�

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetDhKey(
    MODEM_ID_ENUM_UINT16                enModemID,
    SC_DH_KEY_TYPE_ENUM_UINT32          enKeyType,
    VOS_UINT32                          ulKeyLen,
    VOS_UINT8                          *pucKey
);
#endif

/*****************************************************************************
�� �� ��  :SC_COMM_Backup
��������  : SC�ļ����ݴ���
�������  :

�������  :��
�� �� ֵ  :

��������  :
�޶���¼  :
1.��    ��   : 2014��6��5��
  ��    ��   : d00212987
  �޸�����   : ��ʼ����
*****************************************************************************/
VOS_UINT32 SC_COMM_Backup(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif



