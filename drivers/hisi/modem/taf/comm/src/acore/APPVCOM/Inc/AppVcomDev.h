


#ifndef __APPVCOMDEV_H__
#define __APPVCOMDEV_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_typdef.h"
#include "PsTypeDef.h"
#include "AtAppVcomInterface.h"
#include "product_config.h"

#if (VOS_OS_VER == VOS_LINUX)
#include "linux/module.h"
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/signal.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/bitops.h>
#include <linux/wakelock.h>
#else
#include "Linuxstub.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define USE_SEM                         (0)
#define APP_VCOM_MEM_CLEAR              (0x1)                                   /* ����ȫ���ڴ� */

#define APP_VCOM_MAX_NUM                 (APP_VCOM_DEV_INDEX_BUTT)                /*VCOM������*/
#define APP_VCOM_ERROR                   (-1)

#define APP_VCOM_BUILD_DEV_ID(dev, type) (((unsigned int)(dev) << 8) | ((unsigned int)(type) & 0x00ff))
#define APP_VCOM_BUILD_CMD_ID(dev, cmd)  (((unsigned int)(dev) << 8) | ((unsigned int)(cmd) & 0xffff))
#define APP_VCOM_SET_BIT(n)              (1U << n)

#define APP_VCOM_RD_WAKE_LOCK_NAME_LEN  (32)

/* ���⴮���豸���� */
#define APP_VCOM_DEV_NAME_0              "appvcom"

/*�������⴮���豸����*/
#define APP_VCOM_DEV_NAME_1              "appvcom1"
#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define APP_VCOM_DEV_NAME_2              "appvcom2"
#define APP_VCOM_DEV_NAME_3              "appvcom3"
#define APP_VCOM_DEV_NAME_4              "appvcom4"
#define APP_VCOM_DEV_NAME_5              "appvcom5"
#define APP_VCOM_DEV_NAME_6              "appvcom6"
#define APP_VCOM_DEV_NAME_7              "appvcom7"
#define APP_VCOM_DEV_NAME_8              "appvcom8"
#define APP_VCOM_DEV_NAME_9              "appvcom9"
#define APP_VCOM_DEV_NAME_10             "appvcom10"
#define APP_VCOM_DEV_NAME_11             "appvcom11"
#define APP_VCOM_DEV_NAME_12             "appvcom12"
#define APP_VCOM_DEV_NAME_13             "appvcom13"
#define APP_VCOM_DEV_NAME_14             "appvcom14"
#define APP_VCOM_DEV_NAME_15             "appvcom15"
#define APP_VCOM_DEV_NAME_16             "appvcom16"
#define APP_VCOM_DEV_NAME_17             "appvcom17"
#define APP_VCOM_DEV_NAME_18             "appvcom18"
#define APP_VCOM_DEV_NAME_19             "appvcom19"
#define APP_VCOM_DEV_NAME_20             "appvcom20"
#define APP_VCOM_DEV_NAME_21             "appvcom21"
#define APP_VCOM_DEV_NAME_22             "appvcom22"
#define APP_VCOM_DEV_NAME_23             "appvcom23"
#define APP_VCOM_DEV_NAME_24             "appvcom24"
#define APP_VCOM_DEV_NAME_25             "appvcom25"
#define APP_VCOM_DEV_NAME_26             "appvcom26"
#define APP_VCOM_DEV_NAME_27             "appvcomCBT"
#define APP_VCOM_DEV_NAME_28             "appvcomTLLOG"
#define APP_VCOM_DEV_NAME_29             "appvcomERRLOG"
#define APP_VCOM_DEV_NAME_30             "appvcomLOG"
#define APP_VCOM_DEV_NAME_31             "appvcomLOG1"
#endif

/*�豸�ź�������*/
#define APP_VCOM_SEM_NAME_0               "SEM"
#define APP_VCOM_SEM_NAME_1               "SEM1"
#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define APP_VCOM_SEM_NAME_2               "SEM2"
#define APP_VCOM_SEM_NAME_3               "SEM3"
#define APP_VCOM_SEM_NAME_4               "SEM4"
#define APP_VCOM_SEM_NAME_5               "SEM5"
#define APP_VCOM_SEM_NAME_6               "SEM6"
#define APP_VCOM_SEM_NAME_7               "SEM7"
#define APP_VCOM_SEM_NAME_8               "SEM8"
#define APP_VCOM_SEM_NAME_9               "SEM9"
#define APP_VCOM_SEM_NAME_10              "SEM10"
#define APP_VCOM_SEM_NAME_11              "SEM11"
#define APP_VCOM_SEM_NAME_12              "SEM12"
#define APP_VCOM_SEM_NAME_13              "SEM13"
#define APP_VCOM_SEM_NAME_14              "SEM14"
#define APP_VCOM_SEM_NAME_15              "SEM15"
#define APP_VCOM_SEM_NAME_16              "SEM16"
#define APP_VCOM_SEM_NAME_17               "SEM17"
#define APP_VCOM_SEM_NAME_18               "SEM18"
#define APP_VCOM_SEM_NAME_19               "SEM19"
#define APP_VCOM_SEM_NAME_20               "SEM20"
#define APP_VCOM_SEM_NAME_21               "SEM21"
#define APP_VCOM_SEM_NAME_22               "SEM22"
#define APP_VCOM_SEM_NAME_23               "SEM23"
#define APP_VCOM_SEM_NAME_24               "SEM24"
#define APP_VCOM_SEM_NAME_25               "SEM25"
#define APP_VCOM_SEM_NAME_26               "SEM26"
#define APP_VCOM_SEM_NAME_27               "SEM27"
#define APP_VCOM_SEM_NAME_28               "SEM28"
#define APP_VCOM_SEM_NAME_29               "SEM29"
#define APP_VCOM_SEM_NAME_30               "SEM30"
#define APP_VCOM_SEM_NAME_31               "SEM31"
#endif


/* E5�������AT�����һ�㳤�� */
#define APP_VCOM_NORMAL_CMD_LEN         (100)

/* ���⴮���豸���Ƴ���*/
#define APP_VCOM_DEV_NAME_MAX_LEN       (16)
#define APP_VCOM_SEM_NAME_MAX_LEN       (8)

#define APP_VCOM_READ_WAKE_LOCK_LEN     (100)

#define APP_VCOM_TRACE_BUF_LEN 	            (256)

#define APP_VCOM_TRACE_LEVEL_INFO           (0x00000001)
#define APP_VCOM_TRACE_LEVEL_NORM           (0x00000002)
#define APP_VCOM_TRACE_LEVEL_ERR            (0x00000004)
#define APP_VCOM_TRACE_LEVEL_DEBUG          (APP_VCOM_TRACE_LEVEL_INFO | APP_VCOM_TRACE_LEVEL_NORM | APP_VCOM_TRACE_LEVEL_ERR)

#define APP_VCOM_LOG_FORMAT(ulPrintLength, pcBuf, ulBufSize, pcFmt)\
            {\
                va_list pArgList;\
                va_start(pArgList, pcFmt);\
                ulPrintLength += vsnprintf(pcBuf + ulPrintLength,\
                                    ulBufSize - ulPrintLength, pcFmt, pArgList);\
                va_end(pArgList);\
                if (ulPrintLength > (ulBufSize - 1))\
                {\
                    ulPrintLength = ulBufSize - 1;\
                }\
                *(pcBuf + ulPrintLength) = '\0';\
            }

#if (VOS_OS_VER == VOS_WIN32) || defined(_lint)
#define APP_VCOM_DBG_PRINT(lvl, index, fmt, ...)\
            (VOS_VOID)vos_printf(fmt, index, ##__VA_ARGS__)
#else
#define APP_VCOM_DBG_PRINT(lvl, index, fmt, ...)\
            do\
            {\
                if ((lvl == (g_stAppVcomDebugCfg.ulDebugLevel & lvl))\
                   && (0 != (g_stAppVcomDebugCfg.ulPortIdMask & APP_VCOM_SET_BIT(index))))\
                {\
                    APP_VCOM_MNTN_LogPrintf("[VCOM:%2d][TICK:%u][%s][LINE:%d] "fmt"\n", index, VOS_GetTick(), __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                }\
            }while(0)
#endif

#define APP_VCOM_TRACE_INFO(index, ...)\
            APP_VCOM_DBG_PRINT(APP_VCOM_TRACE_LEVEL_INFO, index, __VA_ARGS__)

#define APP_VCOM_TRACE_NORM(index, ...)\
            APP_VCOM_DBG_PRINT(APP_VCOM_TRACE_LEVEL_NORM, index, __VA_ARGS__)

#define APP_VCOM_TRACE_ERR(index, ...)\
            APP_VCOM_DBG_PRINT(APP_VCOM_TRACE_LEVEL_ERR, index, __VA_ARGS__)

#define APP_VCOM_ERR_LOG(Index, String)\
            AT_ERR_LOG1(String, Index)

#define APP_VCOM_MAX_DATA_LENGTH        (64 * 1024)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ����: APP_VCOM_RESULT_ENUM
 Э����:
 �ṹ˵��: �豸ʵ������
 1.��    ��   : 2011��10��17��
   ��    ��   : s62952
   �޸�����   : �����ļ�
*****************************************************************************/
enum APP_VCOM_RESULT_ENUM
{
    APP_VCOM_OK                         =  0,                                             /*NORMAL COMPLETION*/
    APP_VCOM_NOTSTARTED                 =  1,                                             /*OPERATION NOT STARTED*/
    APP_VCOM_INPROGRESS                 =  2,                                             /*OPERATION IN PROGRESS*/
    APP_VCOM_PERM                       =  3,                                             /*OPERATION NOT PERMITTED*/
    APP_VCOM_NOENT                      =  4,                                             /*NO SUCH ENTRY*/
    APP_VCOM_IO                         =  5,                                             /*INPUT/OUTPUT ERROR*/
    APP_VCOM_NXIO                       =  6,                                             /*DEVICE NOT CONFIGURED*/
    APP_VCOM_NOMEM                      =  7,                                             /*FAILED ALLOCATING MEMORY*/
    APP_VCOM_BUSY                       =  8,                                             /*RESOURCE IS BUSY*/
    APP_VCOM_NODEV                      =  9,                                             /*NO SUCH DEVICE*/
    APP_VCOM_INVAL                      = 10,                                             /*INVALID ARGUMENT*/
    APP_VCOM_NOTSUP                     = 11,                                             /*OPERATION NOT SUPPORTED*/
    APP_VCOM_TIMEDOUT                   = 12,                                             /*OPERATION TIMED OUT*/
    APP_VCOM_SUSPENDED                  = 13,                                             /*DEVICE IS SUSPENDED*/
    APP_VCOM_UNKNOWN                    = 14,                                             /*GENERAL-PURPOSE ERROR*/
    APP_VCOM_TEST_FAILED                = 15,                                             /*LOGICAL TEST FAILURE*/
    APP_VCOM_STATE                      = 16,                                             /*INCORRECT STATE*/
    APP_VCOM_STALLED                    = 17,                                             /*PIPE IS STALLED*/
    APP_VCOM_PARAM                      = 18,                                             /*INVALID PARAMETER*/
    APP_VCOM_ABORTED                    = 19,                                             /*OPERATION ABORTED*/
    APP_VCOM_SHORT                      = 20,                                             /*SHORT TRANSFER*/
    APP_VCOM_EXPIRED                    = 21,                                             /*EVALUATION TIME EXPIRED*/
    APP_VCOM_BUTT
};
typedef unsigned int APP_VCOM_RESULT_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: APP_VCOM_ERR_ENUM_UINT32
 Э����:
 �ṹ˵��: �豸���ش�����
 1.��    ��   : 2011��10��17��
   ��    ��   : s62952
   �޸�����   : �����ļ�
*****************************************************************************/
enum APP_VCOM_ERR_ENUM
{
    APP_VCOM_EPERM                      =  0,                                             /* Operation not permitted */
    APP_VCOM_ENOENT                     =  1,                                             /* No such file or directory */
    APP_VCOM_ESRCH                      =  2,                                             /* No such process */
    APP_VCOM_EINTR                      =  3,                                             /* Interrupted system call */
    APP_VCOM_EIO                        =  4,                                             /* I/O error */
    APP_VCOM_ENXIO                      =  5,                                             /* No such device or address */
    APP_VCOM_E2BIG                      =  6,                                             /* Argument list too long */
    APP_VCOM_ENOEXEC                    =  7,                                             /* Exec format error */
    APP_VCOM_EBADF                      =  8,                                             /* Bad file number */
    APP_VCOM_ECHILD                     =  9,                                             /* No child processes */
    APP_VCOM_EAGAIN                     = 10,                                             /* Try again */
    APP_VCOM_ENOMEM                     = 11,                                             /* Out of memory */
    APP_VCOM_EACCES                     = 12,                                             /* Permission denied */
    APP_VCOM_EFAULT                     = 13,                                             /* Bad address */
    APP_VCOM_ENOTBLK                    = 14,                                             /* Block device required */
    APP_VCOM_EBUSY                      = 15,                                             /* Device or resource busy */
    APP_VCOM_EEXIST                     = 16,                                             /* File exists */
    APP_VCOM_EXDEV                      = 17,                                             /* Cross-device link */
    APP_VCOM_ENODEV                     = 18,                                             /* No such device */
    APP_VCOM_ENOTDIR                    = 19,                                             /* Not a directory */
    APP_VCOM_EISDIR                     = 20,                                             /* Is a directory */
    APP_VCOM_EINVAL                     = 21,                                             /* Invalid argument */
    APP_VCOM_ENFILE                     = 23,                                             /* File table overflow */
    APP_VCOM_EMFILE                     = 24,                                             /* Too many open files */
    APP_VCOM_ENOTTY                     = 25,                                             /* Not a typewriter */
    APP_VCOM_ETXTBSY                    = 26,                                             /* Text file busy */
    APP_VCOM_EFBIG                      = 27,                                             /* File too large */
    APP_VCOM_ENOSPC                     = 28,                                             /* No space left on device */
    APP_VCOM_ESPIPE                     = 29,                                             /* Illegal seek */
    APP_VCOM_EROFS                      = 30,                                             /* Read-only file system */
    APP_VCOM_EMLINK                     = 31,                                             /* Too many links */
    APP_VCOM_EPIPE                      = 32,                                             /* Broken pipe */
    APP_VCOM_EDOM                       = 33,                                             /* Math argument out of domain of func */
    APP_VCOM_ERANGE                     = 34,                                             /* Math result not representable */
    APP_VCOM_ERR_BUTT
};
typedef unsigned int APP_VCOM_ERR_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : APP_VCOM_DEV_MAJORDEVID
 �ṹ˵��  : APP VCOM �����豸�豸��

 1.��    ��   : 2012��11��23��
   ��    ��   : z00220246
   �޸�����   : DSDA Phase I:
*****************************************************************************/
enum APP_VCOM_DEV_MAJORDEVID
{
    APP_VCOM_MAJOR_DEV_ID                  = 247,
    APP_VCOM_MAJOR_DEV_ID_1                = 248,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_MAJOR_DEV_ID_2                = 249,
    APP_VCOM_MAJOR_DEV_ID_3                = 250,
    APP_VCOM_MAJOR_DEV_ID_4                = 251,
    APP_VCOM_MAJOR_DEV_ID_5                = 252,
    APP_VCOM_MAJOR_DEV_ID_6                = 253,
    APP_VCOM_MAJOR_DEV_ID_7                = 254,
    APP_VCOM_MAJOR_DEV_ID_8                = 255,
    APP_VCOM_MAJOR_DEV_ID_9                = 256,
    APP_VCOM_MAJOR_DEV_ID_10               = 257,
    APP_VCOM_MAJOR_DEV_ID_11               = 258,
    APP_VCOM_MAJOR_DEV_ID_12               = 259,
    APP_VCOM_MAJOR_DEV_ID_13               = 260,
    APP_VCOM_MAJOR_DEV_ID_14               = 261,
    APP_VCOM_MAJOR_DEV_ID_15               = 262,
    APP_VCOM_MAJOR_DEV_ID_16               = 263,
    APP_VCOM_MAJOR_DEV_ID_17               = 264,
    APP_VCOM_MAJOR_DEV_ID_18               = 265,
    APP_VCOM_MAJOR_DEV_ID_19               = 266,
    APP_VCOM_MAJOR_DEV_ID_20               = 267,
    APP_VCOM_MAJOR_DEV_ID_21               = 268,
    APP_VCOM_MAJOR_DEV_ID_22               = 269,
    APP_VCOM_MAJOR_DEV_ID_23               = 270,
    APP_VCOM_MAJOR_DEV_ID_24               = 271,
    APP_VCOM_MAJOR_DEV_ID_25               = 272,
    APP_VCOM_MAJOR_DEV_ID_26               = 273,
    APP_VCOM_MAJOR_DEV_ID_27               = 274,
    APP_VCOM_MAJOR_DEV_ID_28               = 275,
    APP_VCOM_MAJOR_DEV_ID_29               = 276,
    APP_VCOM_MAJOR_DEV_ID_30               = 277,
    APP_VCOM_MAJOR_DEV_ID_31               = 278,
#endif
    APP_VCOM_MAJOR_DEV_ID_BUTT
};
typedef unsigned int APP_VCOM_DEV_MAJORDEVID_UINT32;

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
 �ṹ����: APP_VCOM_DEV_ENTITY_STRU
 Э����:
 �ṹ˵��: �豸ʵ������
 1.��    ��   : 2011��10��17��
   ��    ��   : s62952
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    struct cdev                         stAppVcomDev;                           /* ���⴮�ڽṹ�� */
    VOS_UINT8                          *pucAppVcomMem;                          /* �豸�ڴ� */
    wait_queue_head_t                   Read_Wait;                              /* �������õĵȴ�����ͷ */
    wait_queue_head_t                   Write_Wait;                             /* ����д�õĵȴ�����ͷ */
    struct semaphore                    stMsgSendSem;
    struct semaphore                    stWrtSem;
    VOS_UINT8                          *pucWrtBuffer;                           /* д���� */
    VOS_UINT32                          ulWrtBufferLen;
    size_t                              current_len;                            /* fifo��Ч���ݳ��� */
    VOS_UINT32                          ulReadWakeUpFlg;
    VOS_UINT32                          ulIsDeviceOpen ;
    struct wake_lock                    stRdWakeLock;
    VOS_CHAR                            acWakeLockName[APP_VCOM_RD_WAKE_LOCK_NAME_LEN];
}APP_VCOM_DEV_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : APP_VCOM_DEV_CTX_STRU
 �ṹ˵��  : APP VCOMģ������������

 1.��    ��   : 2012��11��23��
   ��    ��   : z00220246
   �޸�����   : DSDA Phase I:
*****************************************************************************/
typedef struct
{
    APP_VCOM_DEV_ENTITY_STRU           *pstAppVcomDevEntity;                       /* �豸ʵ�� */
    SEND_UL_AT_FUNC                     pSendUlAtFunc;                             /*��Ӧ������At�������ͺ���*/
    VOS_UINT32                          ulAppVcomMajorId;                          /* �豸�� */
    VOS_CHAR                            aucAppVcomName[APP_VCOM_DEV_NAME_MAX_LEN]; /* �豸����*/
    VOS_CHAR                            aucSendSemName[APP_VCOM_SEM_NAME_MAX_LEN]; /*�ź�������*/
    VOS_UINT8                           aucReserved[4];
    EVENT_FUNC                          pEventFunc;                                /* �¼�����ص� */
}APP_VCOM_DEV_CTX_STRU;

/*****************************************************************************
 �ṹ��    : APP_VCOM_DEV_CONFIG_STRU
 �ṹ˵��  : APP VCOM�豸��������Ϣ

 1.��    ��   : 2013��6��17��
   ��    ��   : l60609
   �޸�����   :
*****************************************************************************/

typedef struct
{
    VOS_CHAR                           *pcAppVcomName;
    VOS_CHAR                           *pcSendSemName;
    VOS_UINT32                          ulAppVcomMemSize;                       /* �豸�����С */
    VOS_UINT32                          ulReserved;
}APP_VCOM_DEV_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : APP_VCOM_DEBUG_INFO_STRU
 �ṹ˵��  : APP VCOM��ά�ɲ���Ϣ

 1.��    ��   : 2013��6��17��
   ��    ��   : l60609
   �޸�����   :
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulDevIndexErr;                          /* �豸Index���� */
    VOS_UINT32                          ulVcomDevErr[APP_VCOM_MAX_NUM];         /* ����豸ʵ��ָ����� */
    VOS_UINT32                          ulMemFullErr[APP_VCOM_MAX_NUM];         /* �豸���������� */
    VOS_UINT32                          ulSendLenErr[APP_VCOM_MAX_NUM];         /* �������ݳ���Ϊ0 */
    VOS_UINT32                          ulReadLenErr[APP_VCOM_MAX_NUM];         /* ��ȡ���ݳ���Ϊ0 */
    VOS_UINT32                          ulAtCallBackErr[APP_VCOM_MAX_NUM];      /* AT�ص�����������ʧ�� */
}APP_VCOM_DEBUG_INFO_STRU;


/*******************************************************************************
 �ṹ��    : APP_VCOM_DEBUG_CFG_STRU
 �ṹ˵��  : VCOM DEBUG�������NV��
  1.��    ��   : 2014��06��03��
    ��    ��   : n00269697
    �޸�����   : VCOM DEBUG����
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPortIdMask;                           /* VCOM�˿�ID���� */
    VOS_UINT32                          ulDebugLevel;                           /* VCOM DEBUG����:ERR,NORMAL,INFO,DEBUG */
} APP_VCOM_DEBUG_CFG_STRU;

extern APP_VCOM_DEBUG_CFG_STRU          g_stAppVcomDebugCfg;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


int APP_VCOM_Open(struct inode *inode, struct file *filp );
int APP_VCOM_Release(struct inode *inode, struct file *filp );
ssize_t APP_VCOM_Read(struct file *stFilp, char __user *buf, size_t count, loff_t *ppos);
ssize_t APP_VCOM_Write(struct file *stFilp, const char __user *buf, size_t count, loff_t *ppos);
unsigned int APP_VCOM_Poll(struct file *fp, struct poll_table_struct *wait);
APP_VCOM_DEV_CTX_STRU* APP_VCOM_GetVcomCtxAddr(VOS_UINT8 ucIndex);
APP_VCOM_DEV_ENTITY_STRU* APP_VCOM_GetAppVcomDevEntity(VOS_UINT8 ucIndex);
VOS_UINT8 APP_VCOM_GetIndexFromMajorDevId(VOS_UINT ulMajorDevId);
VOS_VOID  APP_VCOM_InitSpecCtx(VOS_UINT8 ucDevIndex);
VOS_VOID APP_VCOM_Setup(APP_VCOM_DEV_ENTITY_STRU *pstDev, VOS_UINT8 ucIndex);
VOS_INT APP_VCOM_Init(VOS_VOID);

#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID APP_VCOM_FreeMem(VOS_VOID);
#endif

VOS_VOID APP_VCOM_SendDebugNvCfg(
    VOS_UINT32                          ulPortIdMask,
    VOS_UINT32                          ulDebugLevel
);

/*lint -esym(960,69)*/
VOS_VOID APP_VCOM_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...);
/*lint +esym(960,69)*/

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

#endif

