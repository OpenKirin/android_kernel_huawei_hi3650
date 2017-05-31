/******************************************************************************

			  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
�� �� ��	 : drv_mailbox_platform.h
�� �� ��	 : ����
��	��	 : Ī�� 00176101
��������	 : 2012��9��24��
����޸�	 :
��������	 : mailbox ��ƽ̨ƽ̨ϵͳ����ӿڹ���ͷ�ļ�
�����б�	 :

�޸���ʷ	 :
1.��	  ��   : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ļ�

******************************************************************************/
#ifndef _DRV_MAILBOX_PLATFORM_H_
#define _DRV_MAILBOX_PLATFORM_H_

/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#if defined(BSP_CORE_MODEM) /*C�˵�ϵͳ����ͷ�ļ�*/
#include "drv_mailbox_port_vxworks.h"

#elif defined (BSP_CORE_APP) /*A�˵�ϵͳ����ͷ�ļ�*/
#include "drv_mailbox_port_linux.h"

#elif defined (BSP_CORE_CM3)  /*M�˵�ϵͳ����ͷ�ļ�*/
#include "drv_mailbox_port_mcu.h"

#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#ifndef MAILBOX_TRUE
#define MAILBOX_TRUE								(1)
#endif

#ifndef MAILBOX_FALSE
#define MAILBOX_FALSE								(0)
#endif

#ifndef MAILBOX_NULL
#define MAILBOX_NULL								(void*)(0)
#endif

/*����ӿ����Ͷ���*/
#ifdef _DRV_LLT_
#define MAILBOX_LOCAL											/*�ļ��ڲ����ýӿ�(PC����)*/
#else
#ifndef MAILBOX_LOCAL
#define MAILBOX_LOCAL								static		/*�ļ��ڲ����ýӿ�(����)*/
#endif
#endif

#ifndef MAILBOX_EXTERN
#define MAILBOX_EXTERN											/*ģ���ڲ����ýӿ�*/
#endif

#ifndef MAILBOX_GLOBAL
#define MAILBOX_GLOBAL											/*��ģ���ṩ���ⲿ�Ĺ��ܽӿ�*/
#endif

/*��������ͨ��������Ŀ������*/
#define MIALBOX_DIRECTION_INVALID					(0) 			/*��ʾͨ��������Ч*/
#define MIALBOX_DIRECTION_SEND						(1) 			/*��ʾ��ǰ�˷��͸������˵�ͨ��*/
#define MIALBOX_DIRECTION_RECEIVE					(2) 			/*��ʾ�����˷��͸���ǰ�˵�ͨ��*/

/*��Ч�ʼ���*/
#define  MAILBOX_MAILCODE_INVALID					(unsigned long)(0xffffffff)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : MAILBOX_DELAY_SCENE_E
 ��������  : �����ƽ̨���ӳٺ����ĳ����š�
*****************************************************************************/
enum MAILBOX_DELAY_SCENE_E
{
	MAILBOX_DELAY_SCENE_MSG_FULL ,			/*����msg�ʼ�ʱ����������������ʱ�ȴ���*/
	MAILBOX_DELAY_SCENE_IFC_FULL			/*����ifc�ʼ�ʱ����������������ʱ�ȴ���*/
};

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*�����ڲ��ļ�֮����õĽӿ�*/
extern MAILBOX_EXTERN void  mailbox_assert(unsigned int ErroNo);

extern MAILBOX_EXTERN int mailbox_mutex_lock(void **mutexId);

extern MAILBOX_EXTERN void mailbox_mutex_unlock(void **mutexId);

extern MAILBOX_EXTERN int mailbox_int_context(void);

extern MAILBOX_EXTERN int mailbox_get_timestamp(void);

extern MAILBOX_EXTERN int mailbox_process_register(
                unsigned int channel_id, 
                 int (*cb)(unsigned int channel_id),
                 void *priv);

extern MAILBOX_EXTERN int mailbox_channel_register(
                unsigned int ChannelID, 
                unsigned int IntNum,
                unsigned int DstID,
                unsigned int Direct,
                void   **mutex);

extern MAILBOX_EXTERN void *mailbox_memcpy(void *dst, const void *src, unsigned int size);

extern MAILBOX_EXTERN void *mailbox_memset(void * m, int c, unsigned int size);

extern MAILBOX_EXTERN int mailbox_delivery(unsigned int channel_id);

extern MAILBOX_EXTERN int mailbox_init_platform(void);

extern MAILBOX_EXTERN int mailbox_scene_delay(
                unsigned int scene_id,
                int *try_times);

extern MAILBOX_EXTERN void *mailbox_init_completion(void);

extern MAILBOX_EXTERN int mailbox_wait_completion(void **mutexId, unsigned int timeout);

extern MAILBOX_EXTERN void mailbox_complete(void **wait_id);

extern MAILBOX_EXTERN void mailbox_del_completion(void **wait);
extern void mailbox_ifc_test_init(void);

#if defined (BSP_CORE_CM3)
extern void mailbox_dpm_device_get(void);
extern void mailbox_dpm_device_put(void);
#else
#define mailbox_dpm_device_get()
#define mailbox_dpm_device_put()
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif	/*_DRV_MAILBOX_PLATFORM_H_*/

