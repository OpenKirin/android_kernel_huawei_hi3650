/******************************************************************************

				  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��	 : mlib_ringbuffer.c
  �� �� ��	 : ����
  ��	��	 : l00279082
  ��������	 : 2014��9��1��
  ����޸�	 :
  ��������	 : ��״Bufferʵ��
  �޸���ʷ	 :
  1.��	  ��   : 2014��9��1��
	��	  ��   : l00279082
	�޸�����   : �����ļ�

******************************************************************************/

#include <linux/slab.h>
#include "mlib_ringbuffer.h"
#include "soundtrigger_log.h"




// Ring Buffer Structure
struct _RingBuffer {
   unsigned int size;
   unsigned int start;
   unsigned int count;
   unsigned int element_size;
   int			transFlag;
   char buffer[0];
};

#undef NULL
#define NULL ((void *)0)

#define   ELEMENT_SIZE	   320
#define   ELEMENT_CNT	   200
#define   HEAD_SIZE   20
#define   RINGBUFFER_SIZE	 ((ELEMENT_SIZE)*(ELEMENT_CNT))


/*****************************************************************************
 �� �� ��  : RingBuffer_Init
 ��������  : ��ʼ��Ring Buffer�ṹ�岢�������memory��
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : size: Ring BufferԪ�ظ���
 �� �� ֵ  : Ring Buffer Return Code

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
RingBuffer *RingBuffer_Init(void * ringbufferAddr)
{
	RingBuffer *rb;

	rb = ringbufferAddr;

	if (NULL == rb)
	{
		return NULL;
	}

	memset(rb,0X00,HEAD_SIZE+RINGBUFFER_SIZE);

	rb->element_size = ELEMENT_SIZE;
	rb->size = ELEMENT_CNT;
	rb->start = 0;
	rb->count = 0;
	rb->transFlag = 0;

	return rb;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_GetCount
 ��������  : ��ȡRing buffer�е�Ԫ�ظ���
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : Ring Buffer��ǰԪ�ظ���
 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
unsigned int RingBuffer_GetCount(RingBuffer *rb)
{
	return rb->count;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_IsEmpty
 ��������  : �ж�Buffer�Ƿ�Ϊ��
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : 1��Buffer�գ� 0��Buffer�ǿ�

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_IsEmpty(RingBuffer *rb)
{
	return (rb->count == 0);
}

/*****************************************************************************
 �� �� ��  : RingBuffer_IsFull
 ��������  : �ж�Buffer�Ƿ���
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : True��Buffer���� FALSE��Buffer����

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_IsFull(RingBuffer *rb)
{
	return (rb->count == rb->size);
}

int RingBuffer_GetTransFlag(RingBuffer *rb)
{
	return rb->transFlag;
}

int RingBuffer_SetTransFlag(RingBuffer *rb, int transFlag)
{
	rb->transFlag = transFlag;
	return 0;
}


/*****************************************************************************
 �� �� ��  : RingBuffer_Get
 ��������  : ��Ring Buffer�л�ȡһ��Ԫ�ء�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : Ԫ�ش�ŵ�ַ

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_Get(RingBuffer *rb, void *element)
{
	int retval;

	if (!RingBuffer_IsEmpty(rb))
	{
		memcpy(element, rb->buffer + rb->start * rb->element_size, rb->element_size);
		rb->start = (rb->start + 1) % rb->size;
		--rb->count;
		retval = 320;
	}
	else
	{
		retval = 0;
	}

	return retval;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_Put
 ��������  : ��Ring Buffer��д��һ��Ԫ�ء�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : element: Ԫ�ص�ַ
 �� �� ֵ  : Ring Buffer Return Code

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_Put(RingBuffer *rb, void *element)
{
	int end, retval;

	end = (rb->start + rb->count) % rb->size;
	memcpy(rb->buffer + end * rb->element_size, element, rb->element_size);
	if (RingBuffer_IsFull(rb))
	{
		rb->start = (rb->start + 1) % rb->size; /* full, overwrite */
		retval = RING_BUFFER_OVERWRITE;
	}
	else
	{
		++rb->count;
		retval = RING_BUFFER_NORMAL;
	}

	return retval;
}


int RingBuffer_Compare(RingBuffer *rb,void *element,int compareCount)
{
	int i = 0;
	int ret = 0;

	for(i = 0 ; i < compareCount ; i++)
	{
		if (!RingBuffer_IsEmpty(rb))
		{
			ret = memcmp((char *)element + rb->element_size*i, rb->buffer + rb->start * rb->element_size, rb->element_size);

			if(0 == ret)
			{
				rb->start = (rb->start + 1) % rb->size;
				--rb->count;
			}else{
				ret = 0;
			}

		}
		else
		{
			ret = -1;
		}
	}

	return 0;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_Skip
 ��������  : ɾ��Ԫ��(��ͷ������)
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : skip_cnt: Ҫɾ����Ԫ�ظ���
 �� �� ֵ  : Ring Buffer Return Code

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_Skip(RingBuffer *rb, unsigned int skip_cnt)
{
	int retval;

	if (RingBuffer_GetCount(rb) < skip_cnt)
	{
		retval = RING_BUFFER_NO_SKIP;
	}
	else
	{
		rb->start = (rb->start + skip_cnt) % rb->size;
		rb->count -= skip_cnt;
		retval = RING_BUFFER_NORMAL;
	}

	return retval;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_Backspace
 ��������  : ɾ��Ԫ��(��β������)
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �������  : skip_cnt: Ҫ���˵�Ԫ�ظ���
 �� �� ֵ  : Ring Buffer Return Code

 �޸���ʷ	   :
  1.��	  ��   : 2014��10��11��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
int RingBuffer_Backspace(RingBuffer *rb, unsigned int skip_cnt)
{
	int retval;

	if (RingBuffer_GetCount(rb) < skip_cnt)
	{
		retval = RING_BUFFER_NO_SKIP;
	}
	else
	{
		rb->start = (rb->start + rb->count - skip_cnt) % rb->size;
		rb->count = skip_cnt;
		retval =  RING_BUFFER_NORMAL;
	}

	return retval;
}

/*****************************************************************************
 �� �� ��  : RingBuffer_DeInit
 ��������  : �ͷ�Ring Bufferʹ�õĶ�̬�ڴ�
 �������  : rb: ָ��RingBuffer�ṹ���ָ��
 �� �� ֵ  : ��

 �޸���ʷ	   :
  1.��	  ��   : 2014��9��1��
	��	  ��   :
	�޸�����   : �����ɺ���

*****************************************************************************/
void RingBuffer_DeInit(RingBuffer *rb)
{
	if (rb)
	{
		memset(rb, 0, RINGBUFFER_SIZE + HEAD_SIZE);
		rb = NULL;
	}
}

