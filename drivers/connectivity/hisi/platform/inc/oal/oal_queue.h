/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_data_stru.h
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��11��29��
  ����޸�   :
  ��������   : oal_bit.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��29��
    ��    ��   : t00231215
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_DATA_STRU_H__
#define __OAL_DATA_STRU_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_mem.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID 0

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define OAL_QUEUE_DESTROY

/* �ж�x�Ƿ���2�������� */
#define OAL_IS_NOT_POW_OF_2(_x)   (_x & (_x - 1))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
typedef struct
{
    oal_uint8           uc_element_cnt;    /* ���������Ѿ���ŵ�Ԫ�ظ��� */
    oal_uint8           uc_max_elements;   /* �����������ܴ�ŵ����Ԫ�ظ��� */
    oal_uint8           uc_tail_index;     /* ָ����һ��Ԫ�����λ�õ����� */
    oal_uint8           uc_head_index;     /* ָ��ǰԪ�س���λ�õ����� */
    oal_uint         	*pul_buf;           /* ���л��� */
}oal_queue_stru;

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
 �� �� ��  : oal_queue_set
 ��������  : ���ö��в���
 �������  : pst_queue      : ����ָ��
             pul_buf        : ָ����л�������ָ��
             us_max_elements: ���Ԫ�ظ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��23��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void oal_queue_set(oal_queue_stru *pst_queue, oal_uint *pul_buf, oal_uint8 uc_max_elements)
{
    pst_queue->pul_buf         = pul_buf;

    pst_queue->uc_tail_index   = 0;
    pst_queue->uc_head_index   = 0;
    pst_queue->uc_element_cnt  = 0;
    pst_queue->uc_max_elements = uc_max_elements;
}

/*****************************************************************************
 �� �� ��  : oal_queue_init
 ��������  : ���г�ʼ��, uc_max_events������2����������
 �������  : pst_queue      : ����ָ��
             uc_max_events: ���Ԫ�ظ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��23��
    ��    ��   : chenyan c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 oal_queue_init(oal_queue_stru *pst_queue, oal_uint8 uc_max_events)
{
    oal_uint *pul_buf;

    if (0 == uc_max_events)
    {
        return OAL_SUCC;
    }
    else
    {
        if (OAL_UNLIKELY(OAL_IS_NOT_POW_OF_2(uc_max_events)))
        {
            return OAL_ERR_CODE_CONFIG_UNSUPPORT;
        }
    
        pul_buf = (oal_uint *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(uc_max_events * OAL_SIZEOF(oal_uint)), OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pul_buf))
        {
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    
        OAL_MEMZERO(pul_buf, uc_max_events * sizeof(oal_uint));
        oal_queue_set(pst_queue, pul_buf, uc_max_events);
    
        return OAL_SUCC;
    }
}

/*****************************************************************************
 �� �� ��  : oal_queue_destroy
 ��������  : ���ٶ���
 �������  : pst_queue: ����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_queue_destroy(oal_queue_stru *pst_queue)
{
    if (OAL_PTR_NULL == pst_queue)
    {
        return;
    }

    if (OAL_PTR_NULL == pst_queue->pul_buf)
    {
        return;
    }

    OAL_MEM_FREE(pst_queue->pul_buf, OAL_TRUE);

    oal_queue_set(pst_queue, OAL_PTR_NULL, 0);
}

/*****************************************************************************
 �� �� ��  : oal_queue_enqueue
 ��������  : Ԫ�����
 �������  : pst_queue: ����ָ��
             p_element: Ԫ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  oal_queue_enqueue(oal_queue_stru *pst_queue, oal_void *p_element)
{
    oal_uint8   uc_tail_index;

    /* �쳣: �������� */
    if (pst_queue->uc_element_cnt == pst_queue->uc_max_elements)
    {
        return OAL_FAIL;
    }

    uc_tail_index = pst_queue->uc_tail_index;

    /* ��Ԫ�صĵ�ַ�����ڶ����� */
    pst_queue->pul_buf[uc_tail_index] = (oal_uint)p_element;

    uc_tail_index++;

    pst_queue->uc_tail_index = ((uc_tail_index >= pst_queue->uc_max_elements)? 0 : uc_tail_index);

    pst_queue->uc_element_cnt++;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_queue_dequeue
 ��������  : Ԫ�س���
 �������  : pst_queue: ����ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�: �¼�ָ��
             ʧ��: OAL_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void* oal_queue_dequeue(oal_queue_stru *pst_queue)
{
    oal_uint8    uc_head_index;
    oal_void     *p_element;

    /* �쳣: ����Ϊ�� */
    if (0 == pst_queue->uc_element_cnt)
    {
        return OAL_PTR_NULL;
    }

    uc_head_index = pst_queue->uc_head_index;

    p_element = (oal_void *)pst_queue->pul_buf[uc_head_index];

    uc_head_index++;

    pst_queue->uc_head_index = ((uc_head_index >= pst_queue->uc_max_elements)? 0 : uc_head_index);
    pst_queue->uc_element_cnt--;

    return p_element;
}

/*****************************************************************************
 �� �� ��  : oal_queue_get_length
 ��������  : ��ȡ�������Ѿ���ŵ�Ԫ�ظ���
 �������  : pst_queue: ����ָ��
 �������  : ��
 �� �� ֵ  : �����д�ŵ��¼�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  oal_queue_get_length(oal_queue_stru *pst_queue)
{
    if (OAL_PTR_NULL == pst_queue)
    {
        return 0;
    }

    return pst_queue->uc_element_cnt;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_data_stru.h */
