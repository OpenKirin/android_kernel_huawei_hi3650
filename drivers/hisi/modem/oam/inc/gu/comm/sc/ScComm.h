

/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ScComm.h
  �� �� ��   : ����
  ��    ��   : ��Ц��
  ��������   : 2012��4��16��
  ����޸�   :
  ��������   : SCģ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��4��16��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����

******************************************************************************/

#ifndef __SCCOMM_H__
#define __SCCOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "ScInterface.h"
#include "UsimPsInterface.h"
#include "msp_diag_comm.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define   SC_KEY_LEN                (32)                                        /* ��Կ�ĳ��� */

#define   SC_HASH_LEN               (32)                                        /* HASH���������� */

#define   SC_FILE_PATH_LEN          (128)

#define   SC_SSK_STRING             "Secure Storage Key"                        /* ����SSK���ַ��� */

#define   SC_SSK_STRLEN             (VOS_StrLen(SC_SSK_STRING))                 /* ����SSK���ַ������� */

#define   SC_DSSK_STRING            "Debug port protect Secure Storage Key"     /* ����DSSK���ַ��� */

#define   SC_DSSK_STRLEN            (VOS_StrLen(SC_DSSK_STRING))                /* ����DSSK���ַ������� */

#define   SC_IPK_STRING             "Integrity Protection Key"                  /* ����IPK���ַ��� */

#define   SC_IPK_STRLEN             (VOS_StrLen(SC_IPK_STRING))                 /* ����IPK���ַ������� */

#define   SC_ASSK_STRING            "AT Secure Storage Key"                     /* ����ASSK���ַ��� */

#define   SC_ASSK_STRLEN            (VOS_StrLen(SC_ASSK_STRING))                /* ����ASSK���ַ������� */

#define   SC_SATK_STRING            "Secure AT Key"                             /* ����SATK���ַ��� */

#define   SC_SATK_STRLEN            (VOS_StrLen(SC_SATK_STRING))                /* ����SATK���ַ������� */

#define   SC_FILE_EXIST_MAGIC       (0x37ab65cd)                                /* SC�����ļ����ڱ�� */

#define   SC_FILE_PACKET_MAGIC      (0xdeacb589)                                /* SC���������ڱ�� */

#define   SC_LOG_MAX_LEN            (512)

#define   SC_LOG_FILE_MAX_SIZE      (SC_LOG_MAX_LEN * 100 * 2)    /* the max size of log file. */

#define   SC_FILE_SEEK_END          (2)

#define   SC_FILE_SEEK_SET          (0)

#define   SC_FILE_EXIST_OK          (0)

#define   SC_MAX_RECORD_SLICE_INFO  (500)           /* ��д�ļ�����¼���� */

#define   SC_NV_IMEI_LENTH          (16)

#define   SC_RECORD_IMEI_MAGIC      (0x5a5a5a5a)                                /* SC���У���IMEI��� */

#if ((OSA_CPU_CCPU == VOS_OSA_CPU))
#define SC_GEN_LOG_MODULE(Level) (/*lint -e1011 -e778*/DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(MAPS_PB_PID), DIAG_MODE_COMM, Level)/*lint +e1011 +e778*/)

#define   SC_NORMAL_LOG(string)                     (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%s taskid:%d", string, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s taskid:%d.\r\n", string, SC_COMM_GetCurrentTaskID())

#define   SC_NORMAL_ASCII_LOG(string)               (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%02x ", string);\
                                                    SC_Printf("%02x ", string)

#define   SC_INFO1_LOG(string, para1)               (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d taskid:%d", string, para1, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s %d taskid:%d.\r\n", string, para1, SC_COMM_GetCurrentTaskID())

#define   SC_NORMAL1_LOG(string, para1)             (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d taskid:%d", string, para1, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s %d taskid:%d.\r\n", string, para1, SC_COMM_GetCurrentTaskID())

#define   SC_WARNING1_LOG(string, para1)            (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d taskid:%d", string, para1, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s %d taskid:%d.\r\n", string, para1, SC_COMM_GetCurrentTaskID())

#define   SC_ERROR_LOG(string)                      (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL), MAPS_PB_PID, __FILE__, __LINE__, "%s taskid:%d", string, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s  taskid:%d.\r\n", string, SC_COMM_GetCurrentTaskID())

#define   SC_ERROR1_LOG(string, para1)              (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d taskid:%d", string, para1, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s %d taskid:%d.\r\n", string, para1, SC_COMM_GetCurrentTaskID())

#define   SC_ERROR2_LOG(string, para1, para2)       (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d,%d taskid:%d", string, para1, para2, SC_COMM_GetCurrentTaskID());\
                                                    SC_Printf("%s %d,%d taskid:%d.\r\n", string, para1, para2, SC_COMM_GetCurrentTaskID())

#define   SC_ERROR3_LOG(string, para1, para2, para3) (VOS_VOID)DIAG_LogReport(SC_GEN_LOG_MODULE(PS_LOG_LEVEL_NORMAL),MAPS_PB_PID, __FILE__, __LINE__, "%s,%d,%d,%d taskid:%d", string, para1, para2, para3, SC_COMM_GetCurrentTaskID());\
                                                     SC_Printf("%s %d,%d,%d taskid:%d.\r\n", string, para1, para2, para3, SC_COMM_GetCurrentTaskID())

#else
#define   SC_ERROR_LOG(string)                      SC_Printf(string)
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : SC_KEY_TYPE_ENUM
 ö��˵��  : ָ��KEY������

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ����ö��
*****************************************************************************/
enum SC_KEY_TYPE_ENUM
{
    SC_KEY_TYPE_SSK                     = 0x00,             /* SSK */
    SC_KEY_TYPE_DSSK                    = 0x01,             /* DSSK */
    SC_KEY_TYPE_IPK                     = 0x02,             /* IPK */
    SC_KEY_TYPE_BUTT
};
typedef VOS_UINT8 SC_KEY_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : SC_CRYPTO_PASSWORD_TYPE_ENUM
 ö��˵��  : ָ�����ĵ�����

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ����ö��
*****************************************************************************/
enum SC_CRYPTO_PASSWORD_TYPE_ENUM
{
    SC_CRYPTO_PASSWORD_TYPE_CK          = 0x00,             /* CK������ */
    SC_CRYPTO_PASSWORD_TYPE_DK          = 0x01,             /* DK������ */
    SC_CRYPTO_PASSWORD_TYPE_BUTT
};
typedef VOS_UINT8 SC_CRYPTO_PASSWORD_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : SC_RECORD_FUNC_ENUM
 �ṹ˵��  : ��ά�ɲ⺯����ö��

  1.��    ��   : 2016��03��01��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
enum SC_RECORD_FUNC_ENUM
{
    SC_PERS_VerifyNvReadImei_FUNC       = 0x00,
    SC_PERS_VerifyIMEI_FUNC             = 0x01,
    SC_PERS_CHECK_HUK_VAULE_FUNC        = 0x02,
    SC_COMM_ReadSCFileAndCmpSign_FUNC   = 0x03,
    SC_COMM_ReadFile_IMEI_FUNC          = 0x04,
    SC_COMM_GenerateSignCode_FUNC       = 0x05,
    SC_COMM_ReadSignFile_FUNC           = 0x06,
    SC_COMM_RsaDecrypt_FUNC             = 0x07,
    SC_RECORD_VOS_MemCmp_IMEI_FUNC      = 0x08,

    SC_RECORD_FUNC_BUTT
};
typedef VOS_UINT16 SC_RECORD_FUNC_ENUM_UINT16;

/*****************************************************************************
 ö����    : SC_SECRET_FILE_TYPE_ENUM
 �ṹ˵��  : ָ����ȫ�ļ�������

  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ����ö��

*****************************************************************************/
enum SC_SECRET_FILE_TYPE_ENUM
{
    SC_SECRET_FILE_TYPE_CK              = 0x00,             /* CK-FILE */
    SC_SECRET_FILE_TYPE_DK              = 0x01,             /* DK-FILE */
    SC_SECRET_FILE_TYPE_AK              = 0x02,             /* AK-FILE */
    SC_SECRET_FILE_TYPE_PI              = 0x03,             /* PI-FILE */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE ��0 */
    SC_SECRET_FILE_TYPE_IMEI_I1         = 0x05,             /* IMEI-FILE ��1 */
    SC_SECRET_FILE_TYPE_IMEI_I2         = 0x06,             /* IMEI-FILE ��2 */
#else
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE ��0 */
    SC_SECRET_FILE_TYPE_IMEI_I1         = 0x05,             /* IMEI-FILE ��1 */
#endif
#else
    SC_SECRET_FILE_TYPE_IMEI_I0         = 0x04,             /* IMEI-FILE ��0 */
#endif

    SC_SECRET_FILE_TYPE_BUTT
};
typedef VOS_UINT8 SC_SECRET_FILE_TYPE_ENUM_UINT8;

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
 �ṹ��    : SC_BACKUP_EACH_FILE_INFO_STRU
 �ṹ˵��  : SCÿ�������ļ�����ϸ
 1.��    ��   : 2014��07��29��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFileMagicMUM;
    VOS_UINT32                          ulFileLen;
    VOS_UINT32                          ulFileOffset;
    VOS_CHAR                            acFilePath[SC_FILE_PATH_LEN];
}SC_BACKUP_EACH_FILE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : SC_BACKUP_FILE_INFO_STRU
 �ṹ˵��  : SC�����ļ�ƴ�ӳ�һ�飬ͳһˢ��FLASH
 1.��    ��   : 2014��06��10��
   ��    ��   : d00212987
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulBackMagicMUM;
    VOS_UINT32                         ulTotaleSize;
    SC_BACKUP_EACH_FILE_INFO_STRU      astSCEachFileInfo[SC_SECRET_FILE_TYPE_BUTT*2];
    VOS_CHAR                           aucFileData[4];
}SC_BACKUP_FILE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : SC_RECORD_INFO_STRU
 �ṹ˵��  : �������̼�¼

  1.��    ��   : 2016��04��01��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulTaskId;      /* ����ID */
    SC_RECORD_FUNC_ENUM_UINT16       enFuncID;      /* ����ID */
    MODEM_ID_ENUM_UINT16             enModemID;     /* ����modemID */
    VOS_UINT32                       ulOperateSn;   /* ����SN */
    VOS_UINT32                       ulSliceStart;  /* ��ֹʱ�� */
    VOS_UINT32                       ulSliceEnd;    /* ����ʱ�� */

}SC_RECORD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : SC_RECORD_INFO_CTX_STRU
 �ṹ˵��  : �������̼�¼

  1.��    ��   : 2016��04��01��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulOperateCount;
    SC_RECORD_INFO_STRU              stRecordInfo[SC_MAX_RECORD_SLICE_INFO];
}SC_RECORD_INFO_CTX_STRU;

/*****************************************************************************
 �ṹ��    : SC_RECORD_VERIFY_IMEI_INFO_CTX_STRU
 �ṹ˵��  : ���У�����IMEI

  1.��    ��   : 2016��04��01��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulStartFalg;   /* ��ʼFlag */
    VOS_UINT8                        ucImeiInfo[SC_NV_IMEI_LENTH];
    VOS_UINT32                       ulEndFalg;     /* ����Flag  */

}SC_RECORD_VERIFY_IMEI_INFO_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  10 ��������
*****************************************************************************/
#if ((OSA_CPU_CCPU == VOS_OSA_CPU))

/*****************************************************************************
 �� �� ��  : SC_COMM_AllocRecImeiMem
 ��������  : Ϊ���IMIE����ռ�
 �������  :

 �������  :

 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 SC_COMM_AllocRecImeiMem(MODEM_ID_ENUM_UINT16     enModemID);

/*****************************************************************************
 �� �� ��  : SC_COMM_CeckImeiRecordMem
 ��������  : �����IMIE�ռ�Ϸ���
 �������  :

 �������  :

 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_BOOL SC_COMM_CeckImeiRecordMemFlag(MODEM_ID_ENUM_UINT16   enModemID);

/*****************************************************************************
 �� �� ��  : SC_COMM_SetVerifyImeiValue
 ��������  : ����У��ͨ��IMEI
 �������  :

 �������  :

 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SC_COMM_SetVerifyImeiValue(
    MODEM_ID_ENUM_UINT16                    enModemID,
    VOS_UINT8                              *pucImie
);

/*****************************************************************************
 �� �� ��  : SC_COMM_CeckImeiRecordMem
 ��������  : �����IMIE�ռ�Ϸ���
 �������  :

 �������  :

 �� �� ֵ  : SC_RECORD_IMEI_INFO_CTX_STRU*
 ���ú���  :
 ��������  :
*****************************************************************************/
SC_RECORD_VERIFY_IMEI_INFO_CTX_STRU* SC_COMM_GetVerifyImeiValue(MODEM_ID_ENUM_UINT16   enModemID);

VOS_UINT32 SC_COMM_RecordSliceStart(
    SC_RECORD_FUNC_ENUM_UINT16          enFuncID,
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulTaskId
);

#define SC_COMM_RECORDSTART(enFuncID, enModemID) SC_COMM_RecordSliceStart(enFuncID, enModemID, SC_COMM_GetCurrentTaskID())

VOS_VOID SC_COMM_RecordEndSlice(VOS_UINT32 ulIndex);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateKey(
    VOS_CHAR                           *pcData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucKey,
    VOS_UINT32                          ulKeyLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadSCFileAndCmpSign(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteSecretFile(
    SC_SECRET_FILE_TYPE_ENUM_UINT8      enFileType,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateCryptoPwd(
    SC_CRYPTO_PASSWORD_TYPE_ENUM_UINT8  enPwdType,
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                          *pucCryptoPwd,
    VOS_UINT32                          ulCryptoPwdLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaEncrypt(
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                         *pulCipherLen
);

extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_RsaDecrypt(
    VOS_UINT8                          *pucPwd,
    VOS_UINT32                          ulCipherLen,
    VOS_UINT8                          *pucPubContent,
    VOS_UINT32                         *pulPubLen
);

/*****************************************************************************
 �� �� ��  : SC_COMM_GenerateSignCode
 ��������  : �ļ�ǩ���ļ���
 �������  : pucContent: �ļ�����
             ucContentLen: �ļ����ݳ���
             ucSignCodeLen: �ļ�ǩ������

 �������  : pucSignCode: �ļ�ǩ������

 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��07��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
SC_ERROR_CODE_ENUM_UINT32 SC_COMM_GenerateSignCode(
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen,
    VOS_UINT8                          *pucSignCode,
    VOS_UINT32                          ulSignCodeLen
);

/*****************************************************************************
 �� �� ��  : SC_COMM_WriteFile
 ��������  : ��ȡ�ļ��ӿ�
 �������  : pcFilePath: �ļ�·��
             ulContentLen: �ļ�����

 �������  : pucContent: �ļ�����

 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��18��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_WriteFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

/*****************************************************************************
 �� �� ��  : SC_COMM_ReadFile
 ��������  : ��ȡ�ļ��ӿ�
 �������  : pcFilePath: �ļ�·��
             ulContentLen: �ļ�����

 �������  : pucContent: �ļ�����

 �� �� ֵ  : SC_ERROR_CODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��18��
    ��    ��   : w00184875
    �޸�����   : AP-Modem����������Ŀ��������

*****************************************************************************/
extern SC_ERROR_CODE_ENUM_UINT32 SC_COMM_ReadFile(
    VOS_CHAR                           *pcFilePath,
    VOS_UINT8                          *pucContent,
    VOS_UINT32                          ulContentLen
);

/*****************************************************************************
 �� �� ��  : SC_COMM_GetUsimmCachedFile
 ��������  : SCģ���ȡUSIMMģ�黺���ļ���װ�ӿ�
 �������  :enModemID:Modem ID
 �������  :pucFilePath:��ȡ���ļ�ID��·��
            pulDataLen:�����ļ������ݳ���
            ppucData:�����ļ����ݵĵ�ַ
            enAppType:Ӧ������
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ      :
  1.��    ��   : 2013��8��15��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
extern VOS_UINT32 SC_COMM_GetUsimmCachedFile(
    VOS_CHAR                           *pucFilePath,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    MODEM_ID_ENUM_UINT16                enModemID);

/*****************************************************************************
�� �� ��  :SC_COMM_IsUsimServiceAvailable
��������  :��ȡ������״̬��
�������  :enModemID:Modem ID
           enService:����ID
�������  :��
�� �� ֵ  :PS_USIM_SERVICE_NOT_AVAILIABLE
           PS_USIM_SERVICE_NOT_AVAILIABLE
��������  :
�޶���¼  :
1.��    ��   : 2013��8��15��
  ��    ��   : h59254
  �޸�����   : ��ʼ����
*****************************************************************************/
extern VOS_UINT32 SC_COMM_IsUsimServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService,
    MODEM_ID_ENUM_UINT16            enModemID);

/*****************************************************************************
�� �� ��  : SC_COMM_GetCurrentTaskID
��������  : SC��ȡ��ǰtask id
�������  :

�������  : ��
�� �� ֵ  : VOS_UINT32

��������  :
�޶���¼  :
1.��    ��   : 2016��5��27��
  ��    ��   : d00212987
  �޸�����   :
*****************************************************************************/
VOS_UINT32 SC_COMM_GetCurrentTaskID(VOS_VOID);
#endif

#if ((OSA_CPU_ACPU == VOS_OSA_CPU))

/*****************************************************************************
�� �� ��  : SC_COMM_Restore
��������  : SC�ļ��ָ�
�������  : ��

�������  : ��
�� �� ֵ  : VOS_UINT32

��������  :
�޶���¼  :
1.��    ��   : 2015��8��10��
  ��    ��   : d00212987
  �޸�����   : SC���ݵ�����NV���ݵ���չ����
*****************************************************************************/
VOS_UINT32 SC_COMM_Restore(VOS_VOID);

extern VOS_VOID SC_Printf(VOS_CHAR *pcData);

#else
/*lint -e960 */
extern VOS_VOID SC_Printf(const VOS_CHAR *pcformat, ...);
/*lint +e960 */
#endif

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
