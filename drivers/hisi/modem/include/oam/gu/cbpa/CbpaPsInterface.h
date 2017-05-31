

/************************************************************************
  Copyright   : 2013-2015, Huawei Tech. Co., Ltd.
  File name   : CbpaPsInterface.h
  Author      : l00256032
  Version     : V900R001
  Date        : 2014-1-24
  Description : L+C��SIM����Ŀͷ�ļ���ض���
  History     :
   1.Date:2014-1-24
     Author: l00256032
     Modification:create

************************************************************************/

#ifndef __CBPA_PS_INTERFACE_H__
#define __CBPA_PS_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CBPCA_MSG_DATA_RSV_LEN          (4)                 /* CBPCA�շ�����Ϣ�ṹ���У�������ʱ���� */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ö����    : CBPCA_MSG_TYPE_ENUM
 ö��˵��  : CBPCA������ģ������ϢID����
*****************************************************************************/
enum CBPCA_MSG_TYPE_ENUM
{
    CSIMA_CBPCA_DATA_REQ                = 0x00000000,       /* CSIMA��CBPCA���͵��������� */
    CBPCA_CSIMA_DATA_IND                = 0x00001000,       /* CBPCA��CSIMAת�������� */

    CMMCA_CBPCA_DATA_REQ                = 0x00000001,       /* CMMCA��CBPCA���͵��������� */
    CBPCA_CMMCA_DATA_IND                = 0x00001001,       /* CBPCA��CMMCAת�������� */

    CSIMA_CBPCA_MODEM_RESET_IND         = 0x00001002,       /* CSIMA��CBPCA����VIA Modem��λ״ָ̬ʾ */

    CBPCA_MTC_DATA_IND                  = 0x00001003,       /* CBPCA��MTCת�������� */

    CBPCA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 CBPCA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : CSIMA_CBPCA_MODEM_RESET_ENUM
 ö��˵��  : CSIMA��CBPCA����VIA MODEM ��λ״ָ̬ʾʱ���õ�ö��
*****************************************************************************/
enum CSIMA_CBPCA_MODEM_RESET_ENUM
{
    CSIMA_CBPCA_MODEM_RESET_START       = 0x0000,           /* VIA Modem��ʼ��λ */
    CSIMA_CBPCA_MODEM_RESET_SUCC        = 0x0001,           /* VIA Modem��λ�ɹ� */
    CSIMA_CBPCA_MODEM_RESET_FAIL        = 0x0002,           /* VIA Modem��λʧ�� */

    CSIMA_CBPCA_MODEM_RESET_BUTT
};
typedef VOS_UINT32 CSIMA_CBPCA_MODEM_RESET_ENUM_UINT32;


/*******************************************************************************
  4 �ṹ����
*******************************************************************************/
/*****************************************************************************
 �ṹ��    : CBPCA_DATA_REQ_MSG_STRU
 �ṹ˵��  : CSIMA��CMMCA���ϲ�����ģ����CBPCA���͵�����������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* ��ϢID */
    VOS_UINT32                          ulDataLen;          /* ָʾaucData�����ݳ��ȣ�������aucData��Ԥ����ǰ6���ֽ� */
    VOS_UINT8                           aucData[CBPCA_MSG_DATA_RSV_LEN];
}CBPCA_DATA_REQ_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CBPCA_DATA_IND_MSG_STRU
 �ṹ˵��  : CBPCA��CSIMA��CMMCA���ϲ�����ģ�鷢�͵�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* ��ϢID */
    VOS_UINT32                          ulDataLen;          /* ָʾaucData�����ݳ��� */
    VOS_UINT8                           aucData[CBPCA_MSG_DATA_RSV_LEN];
}CBPCA_DATA_IND_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU
 �ṹ˵��  : CSIMA��CBPCA���͵�Modem��λ״ָ̬ʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* ��ϢID */
    CSIMA_CBPCA_MODEM_RESET_ENUM_UINT32 enModemReset;       /* ָʾModem��λ״̬ */
}CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/
extern VOS_UINT32 CBPCA_SndDataToCbpca(
    VOS_UINT32                          ulSndPid,
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength);



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

#endif /* end of CbpaPsInterface.h*/

