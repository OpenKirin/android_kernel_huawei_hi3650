

#ifndef __RNIC_TIMERMGMT_H__
#define __RNIC_TIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* RNIC��ͬʱ���еĶ�ʱ���������Ŀ */
#define RNIC_MAX_TIMER_NUM                      (TI_RNIC_TIMER_BUTT)

#define TI_RNIC_UNIT                            (1000)                          /* 1s = 1000ms */

#define TI_RNIC_DSFLOW_STATS_LEN                (2000)                          /* 2��ͳ��һ������ */
#define TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN      (10000)                         /* 10�벦�ŶϿ���ʱ�� */
#define TI_RNIC_DEMAND_DIAL_PROTECT_LEN         (1000)                          /* 1�벦�ű�����ʱ�� */

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if  (MULTI_MODEM_NUMBER == 3)
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_3 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_4 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_5 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_6 == (enTimerId)))
#else
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_3 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_4 == (enTimerId)))
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#else
#define RNIC_IS_DSFLOW_TIMER_ID(enTimerId)          \
            ((TI_RNIC_DSFLOW_STATS_0 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_1 == (enTimerId))   \
          || (TI_RNIC_DSFLOW_STATS_2 == (enTimerId)))
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RNIC_TIMER_ID_TYPE_ENUM
 ö��˵��  : RNIC�ڲ���ʱ������
  1.��    ��   : 2011��12��08��
    ��    ��   : f00179208
    �޸�����   : �½�
  2.��    ��   : 2012��11��23��
    ��    ��   : f00179208
    �޸�����   : DSDA Phase I: RNIC��ʵ��
  3.��    ��   : 2015��5��28��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
enum RNIC_TIMER_ID_TYPE_ENUM
{
    TI_RNIC_DEMAND_DIAL_DISCONNECT,                                             /* ���貦�ŶϿ���ʱ�� */
    TI_RNIC_DEMAND_DIAL_PROTECT,                                                /* ���貦�ű�����ʱ�� */
    TI_RNIC_DSFLOW_STATS_0,                                                     /* ����0��2�������ͳ�ƶ�ʱ�� */
    TI_RNIC_DSFLOW_STATS_1,                                                     /* ����1��2�������ͳ�ƶ�ʱ�� */
    TI_RNIC_DSFLOW_STATS_2,                                                     /* ����2��2�������ͳ�ƶ�ʱ�� */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    TI_RNIC_DSFLOW_STATS_3,                                                     /* ����3��2�������ͳ�ƶ�ʱ�� */
    TI_RNIC_DSFLOW_STATS_4,                                                     /* ����4��2�������ͳ�ƶ�ʱ�� */
#if  (MULTI_MODEM_NUMBER == 3)
    TI_RNIC_DSFLOW_STATS_5,                                                     /* ����5��2�������ͳ�ƶ�ʱ�� */
    TI_RNIC_DSFLOW_STATS_6,                                                     /* ����6��2�������ͳ�ƶ�ʱ�� */
#endif /* #if (MULTI_MODEM_NUMBER == 3) */
#endif
    TI_RNIC_TIMER_BUTT
};
typedef VOS_UINT16 RNIC_TIMER_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RNIC_TIMER_STATUS_ENUM
 �ṹ˵��  : RNIC��ʱ��״̬,ֹͣ������

 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : ����RNIC��ʱ��״̬
*****************************************************************************/
enum RNIC_TIMER_STATUS_ENUM
{
    RNIC_TIMER_STATUS_STOP,                                                     /* ��ʱ��ֹͣ״̬ */
    RNIC_TIMER_STATUS_RUNING,                                                   /* ��ʱ������״̬ */
    RNIC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 RNIC_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : RNIC_TIMER_OPERATION_TYPE_ENUM
 �ṹ˵��  : RNIC��ʱ��������ȡֵ

 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : RNIC��ʱ��������ȡֵ,����SDT����ʾ
*****************************************************************************/
enum RNIC_TIMER_OPERATION_TYPE_ENUM
{
    RNIC_TIMER_OPERATION_START,                                                 /* ������ʱ�� */
    RNIC_TIMER_OPERATION_STOP,                                                  /* ֹͣ��ʱ�� */
    RNIC_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8  RNIC_TIMER_OPERATION_TYPE_ENUM_UINT8;


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
 �ṹ��    : RNIC_TIMER_CTX_STRU
 �ṹ˵��  : RNIC��ʱ������������

 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : ����RNIC��ʱ������������
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucRsv[7];                              /* ���� */
} RNIC_TIMER_CTX_STRU;


/*****************************************************************************
 �ṹ��    : RNIC_TIMER_INFO_STRU
 �ṹ˵��  : RNIC��ʱ����Ϣ�ṹ������SDT����ʾ

 1.��    ��   : 2011��12��12��
   ��    ��   : ����/f00179208
   �޸�����   : ����RNIC��ʱ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RNIC_TIMER_ID_ENUM_UINT16               enTimerId;                          /* ��ʱ��ID */
    RNIC_TIMER_OPERATION_TYPE_ENUM_UINT8    enTimeAction;                       /* ��ʱ���������� */
    VOS_UINT8                               aucRsv[1];                          /* ���� */
    VOS_UINT32                              ulTimeLen;                          /* ��ʱ������ */
}RNIC_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
);

VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
);

VOS_VOID  RNIC_StopAllTimer( VOS_VOID );

RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
);

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

#endif /* end of RnicTimerMgmt.h */
