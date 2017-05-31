/******************************************************************************

				  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��	 : mlib_ringbuffer.h
  �� �� ��	 : ����
  ��	��	 : l00279082
  ��������	 : 2014��9��2��
  ����޸�	 :
  ��������	 : ��״Bufferʵ��
  �޸���ʷ	 :
  1.��	  ��   : 2014��9��1��
	��	  ��   : l00279082
	�޸�����   : �����ļ�
******************************************************************************/
#ifndef __MLIB_RINGBUFFER_H__
#define __MLIB_RINGBUFFER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//Return Code
enum RING_BUFFER_RET_CODE {
	RING_BUFFER_NORMAL,
	RING_BUFFER_BAD_PARAM,
	RING_BUFFER_ALLOCATE_FAIL,
	RING_BUFFER_EMPTY,
	RING_BUFFER_OVERWRITE,
	RING_BUFFER_NO_SKIP
};

struct _RingBuffer;
typedef struct _RingBuffer RingBuffer;

//#define RING_BUFFER_THREAD_SAFE

/*****************************************************************************
 �� �� ��  : RingBuffer_Init
 ��������  : ��ʼ��Ring Buffer�ṹ�岢�������memory��
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : element_size: Ring Buffer����Ԫ�ش�С
 �������  : element_count: Ring Buffer��Ԫ�ظ���
 �� �� ֵ  : RING_BUFFER_NORMAL��Success, RING_BUFFER_ALLOCATE_FAIL: Fail
*****************************************************************************/
extern RingBuffer *RingBuffer_Init(void * ringbufferAddr);

/*****************************************************************************
 �� �� ��  : RingBuffer_GetCount
 ��������  : ��ȡRing buffer�е�Ԫ�ظ���
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : Ԫ�ظ���
*****************************************************************************/
extern unsigned int RingBuffer_GetCount(RingBuffer *rb);

/*****************************************************************************
 �� �� ��  : RingBuffer_IsEmpty
 ��������  : �ж�Buffer�Ƿ�Ϊ��
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : True��Buffer�գ� FALSE��Buffer�ǿ�
*****************************************************************************/
extern int RingBuffer_IsEmpty(RingBuffer *rb);

/*****************************************************************************
 �� �� ��  : RingBuffer_IsFull
 ��������  : �ж�Buffer�Ƿ���
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : True��Buffer���� FALSE��Buffer����
*****************************************************************************/
extern int RingBuffer_IsFull(RingBuffer *rb);

extern int RingBuffer_GetTransFlag(RingBuffer *rb);

extern int RingBuffer_SetTransFlag(RingBuffer *rb, int transFlag);


/*****************************************************************************
 �� �� ��  : RingBuffer_Get
 ��������  : ��Ring Buffer�л�ȡһ��Ԫ�ء�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : element: ���Ԫ�ص�ָ��
 �� �� ֵ  : Return Code
*****************************************************************************/
extern int RingBuffer_Get(RingBuffer *rb, void *element);

/*****************************************************************************
 �� �� ��  : RingBuffer_Put
 ��������  : ��Ring Buffer��д��һ��Ԫ�ء�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : element: Ҫд���Ԫ�ص�ָ��
 �� �� ֵ  : ��
*****************************************************************************/
extern int RingBuffer_Put(RingBuffer *rb, void *element);

/*****************************************************************************
 �� �� ��  : RingBuffer_Get_FastData
 ��������  : ��Ring Buffer�п��ٶ�ȡ���ݡ�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
			dstAddr��Ŀ�ĵ�ַ
			stopFlag��������־
 �������  :
 �� �� ֵ  : ��
*****************************************************************************/
extern int RingBuffer_Compare(RingBuffer *rb,void *element,int compareCount);
extern int RingBuffer_Backspace(RingBuffer *rb, unsigned int skip_cnt);



/*****************************************************************************
 �� �� ��  : RingBuffer_Erase
 ��������  : ɾ��Ԫ��
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : eraze_count: Ҫɾ����Ԫ�ظ���
 �� �� ֵ  : ��
*****************************************************************************/
extern int RingBuffer_Skip(RingBuffer *rb, unsigned int skip_count);

/*****************************************************************************
 �� �� ��  : RingBuffer_DeInit
 ��������  : �ͷ�Ring Bufferʹ�õĶ�̬�ڴ�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : ��
*****************************************************************************/
extern void RingBuffer_DeInit(RingBuffer *rb);

#ifdef __cplusplus
	#if __cplusplus
		}
	#endif
#endif
#endif
