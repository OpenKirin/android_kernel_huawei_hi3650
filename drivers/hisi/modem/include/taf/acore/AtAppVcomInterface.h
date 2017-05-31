

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifndef _ATAPPVCOMINTERFACE_H_
#define _ATAPPVCOMINTERFACE_H_


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
/*�ṩ��OM ���豸����*/
#if (FEATURE_ON == FEATURE_VCOM_EXT)
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_27)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_28)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_29)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_30)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_31)
#else
#define APP_VCOM_DEV_INDEX_CBT            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_TLLOG          (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_ERRLOG         (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG            (APP_VCOM_DEV_INDEX_BUTT)
#define APP_VCOM_DEV_INDEX_LOG1           (APP_VCOM_DEV_INDEX_BUTT)
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : APP_VCOM_DEV_INDEX
 �ṹ˵��  : APP VCOM �����豸������

 1.��    ��   : 2012��11��23��
   ��    ��   : z00220246
   �޸�����   : DSDA Phase I:
*****************************************************************************/
enum APP_VCOM_DEV_INDEX
{
    APP_VCOM_DEV_INDEX_0                 = 0,
    APP_VCOM_DEV_INDEX_1                 = 1,
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    APP_VCOM_DEV_INDEX_2                 = 2,
    APP_VCOM_DEV_INDEX_3                 = 3,
    APP_VCOM_DEV_INDEX_4                 = 4,
    APP_VCOM_DEV_INDEX_5                 = 5,
    APP_VCOM_DEV_INDEX_6                 = 6,
    APP_VCOM_DEV_INDEX_7                 = 7,
    APP_VCOM_DEV_INDEX_8                 = 8,
    APP_VCOM_DEV_INDEX_9                 = 9,
    APP_VCOM_DEV_INDEX_10                = 10,
    APP_VCOM_DEV_INDEX_11                = 11,
    APP_VCOM_DEV_INDEX_12                = 12,
    APP_VCOM_DEV_INDEX_13                = 13,
    APP_VCOM_DEV_INDEX_14                = 14,
    APP_VCOM_DEV_INDEX_15                = 15,
    APP_VCOM_DEV_INDEX_16                = 16,
    APP_VCOM_DEV_INDEX_17                = 17,
    APP_VCOM_DEV_INDEX_18                = 18,
    APP_VCOM_DEV_INDEX_19                = 19,
    APP_VCOM_DEV_INDEX_20                = 20,
    APP_VCOM_DEV_INDEX_21                = 21,
    APP_VCOM_DEV_INDEX_22                = 22,
    APP_VCOM_DEV_INDEX_23                = 23,
    APP_VCOM_DEV_INDEX_24                = 24,
    APP_VCOM_DEV_INDEX_25                = 25,
    APP_VCOM_DEV_INDEX_26                = 26,
    APP_VCOM_DEV_INDEX_27                = 27,
    APP_VCOM_DEV_INDEX_28                = 28,
    APP_VCOM_DEV_INDEX_29                = 29,
    APP_VCOM_DEV_INDEX_30                = 30,
    APP_VCOM_DEV_INDEX_31                = 31,
#endif
    APP_VCOM_DEV_INDEX_BUTT
};
typedef VOS_UINT8 APP_VCOM_DEV_INDEX_UINT8;

enum APP_VCOM_EVT
{
    APP_VCOM_EVT_RELEASE   = 0,     /* �˿ڹر��¼� */
    APP_VCOM_EVT_OPEN      = 1,     /* �˿ڴ��¼� */
    APP_VCOM_EVT_BUTT
};
typedef VOS_UINT32 APP_VCOM_EVT_UINT32;
/*****************************************************************************
  2 ȫ�ֱ�������
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


typedef int (*SEND_UL_AT_FUNC)(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
typedef int (*EVENT_FUNC)(APP_VCOM_EVT_UINT32 event);

/*****************************************************************************
 �� �� ��  : APP_VCOM_RegDataCallback
 ��������  : �ṩ�ϲ�Ӧ�ó���ע�����ݽ��ջص�����ָ���API�ӿں�����
 �������  : uPortNo������ʵ���š�
             pCallback���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegDataCallback(VOS_UINT8 ucDevIndex, SEND_UL_AT_FUNC pFunc);
/*****************************************************************************
 �� �� ��  : APP_VCOM_RegEvtCallback
 ��������  : VCOMΪ�ⲿģ���ṩ��ע��˿��¼��������ӿڡ�
 �������  : uPortNo������ʵ���š�
             pCallback���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern VOS_UINT32 APP_VCOM_RegEvtCallback(VOS_UINT8 ucDevIndex, EVENT_FUNC pFunc);
/*****************************************************************************
 �� �� ��  : APP_VCOM_Send
 ��������  : ʵ�����⴮��ͨ�������ݷ��͹��ܣ����ϲ�������ݵĴ���������
              ֱ�Ӵ�����APP��
 �������  : uPortNo�����⴮��ʵ���š�
             pData��������ָ�롣
             uslength�������ֽ�����
 �������  : �ޡ�
 �� �� ֵ  : 0�������ɹ���
             ����ֵ������ʧ��

*****************************************************************************/
extern VOS_UINT32 APP_VCOM_Send (VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);
#define APP_VCOM_SEND(ucDevIndex,pData,uslength) APP_VCOM_Send(ucDevIndex,pData,uslength)


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

