
#ifndef __APPVCOM_LOG_H__
#define __APPVCOM_LOG_H__

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

#include "PsCommonDef.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define APPVCOM_LOG(String)\
    {\
        Print( (String) );\
        Print("\n");\
    }

#define APPVCOM_LOG1(String, Para1)\
    {\
        Print ( (String) );\
        Print1( ",%d\n",(VOS_INT32)(Para1));\
    }

#define APPVCOM_LOG2(String, Para1, Para2)\
    {\
        Print ( (String) );\
        Print2( ",%d,%d\n",(VOS_INT32)(Para1), (VOS_INT32)(Para2));\
    }

#define APPVCOM_LOG3(String, Para1, Para2, Para3)\
    {\
        Print ( (String) );\
        Print3 ( ",%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) );\
    }

#define APPVCOM_LOG4(String, Para1, Para2, Para3, Para4)\
    {\
        Print ( (String) );\
        Print4 ( ",%d,%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) );\
    }


#define    APPVCOM_INFO_LOG(Mod, String)                                    APPVCOM_LOG( (String) )
#define    APPVCOM_INFO_LOG1(Mod, String,Para1)                             APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_INFO_LOG2(Mod, String,Para1,Para2)                       APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_NORMAL_LOG(Mod, String)                                  APPVCOM_LOG ( (String) )
#define    APPVCOM_NORMAL_LOG1(Mod, String,Para1)                           APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_NORMAL_LOG2(Mod, String,Para1,Para2)                     APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_WARNING_LOG(Mod, String)                                 APPVCOM_LOG ( (String) )
#define    APPVCOM_WARNING_LOG1(Mod, String,Para1)                          APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_WARNING_LOG2(Mod, String,Para1,Para2)                    APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_ERROR_LOG(Mod, String)                                   APPVCOM_LOG ( (String) )
#define    APPVCOM_ERROR_LOG1(Mod, String,Para1)                            APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_ERROR_LOG2(Mod, String,Para1,Para2)                      APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

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

#endif /* AdsLog.h */




