/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : PsLib.h
  �� �� ��   : ����
  ��    ��   : ���� 00133115
  ��������   : 2008��9��22��
  ����޸�   :
  ��������   : Э��ջ������С����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��9��22��
    ��    ��   : ���� 00133115
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PS_LIB_H__
#define __PS_LIB_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* �Ȱ��������ļ�,��PC����ʹ�� */
#if (VOS_OS_VER == VOS_WIN32)
#include <stdlib.h>
#include <search.h>
#endif

#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (VOS_OS_VER == VOS_VXWORKS)
    #if VOS_YES == VOS_MEMORY_CHECK
    extern VOS_VOID VOS_FatalError(VOS_VOID);

    #define PS_FATAL_ERROR()                VOS_FatalError()
    #else
    #define PS_FATAL_ERROR()                (void)0
    #endif
#else
#define PS_FATAL_ERROR()                (void)0
#endif

#define PS_STATS

/*��ȡ[0, ulUpperLimit]���䷶Χ�ڵ������*/
#define PS_RAND(ulUpperLimit)\
        VOS_Rand(ulUpperLimit)

#define PS_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define PS_MAX(x, y)\
        (((x)>(y))?(x):(y))

#define PS_OFFSET_OF(s, m)         ((VOS_SIZE_T)(&(((s *)0)->m)))

#define PS_MOD_GET(x, y)\
        ((x) % (y))

#define PS_MOD_ADD(x, y, z)\
        (((x) + (y)) % (z))

#define PS_MOD_SUB(x, y, z)\
        ((((x) + (z)) - (y)) % (z))

/*============================*/    /*PS���Ժ궨�壬����ϵͳ�쳣���ж�*/



/*#define PS_ASSERT(Pid, c) \
        if(!(c))\
        {\
            LPS_LOG((Pid), 0, PS_PRINT_ERROR, "Fatal Error:PS_ASSERT\n");\
        }

#define PS_ASSERT_RTN(Pid, c, rtn) \
        if(!(c))\
        {\
            LPS_LOG((Pid), 0, PS_PRINT_ERROR, "Fatal Error:PS_ASSERT_RTN\n");\
            return rtn;\
        }*/

/*Ĭ��DEBUG*/
#ifndef PDCP_RELEASE
#define PDCP_DEBUG  1
#endif
#ifndef RLC_RELEASE
#define RLC_DEBUG  1
#endif
#ifndef MAC_RELEASE
#define MAC_DEBUG  1
#endif
#ifndef L2_RELEASE
#define L2_DEBUG  1
#endif
#ifndef PS_RELEASE
#define PS_DEBUG  1
#endif

#if (0 != PDCP_DEBUG)
#define PDCP_ASSERT_ON
#endif

#if (0 != RLC_DEBUG)
#define RLC_ASSERT_ON
#endif

#if (0 != MAC_DEBUG)
#define MAC_ASSERT_ON
#endif

#if (0 != L2_DEBUG)
#define L2_ASSERT_ON
#endif

#if (0 != PS_DEBUG)
#define PS_ASSERT_ON
#endif

#if (VOS_WIN32 == VOS_OS_VER)
//#define LPS_ASSERT vos_assert(__FILE__, __LINE__)
#define LPS_ASSERT  vos_printf("Assert, File: %s, Line:%d\n", __FILE__,__LINE__)
#else
#define LPS_ASSERT (VOS_VOID)LogPrint6("Assert, File: %s, Line: %d\n", (VOS_INT)__FILE__, __LINE__, 0, 0, 0, 0)
#endif


#ifdef PDCP_ASSERT_ON
/*#define PDCP_ASSERT(exp) ( (exp)?(VOS_VOID)0:vos_assert(__FILE__, __LINE__) )
 */
#define PDCP_ASSERT(exp) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return; }
#define PDCP_ASSERT_RTN(exp, ret) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return ret; }
#else
#define PDCP_ASSERT( exp ) ( (VOS_VOID)0 )
#define PDCP_ASSERT_RTN(exp, ret) ( (VOS_VOID)0 )
#endif

#ifdef RLC_ASSERT_ON
/*#define RLC_ASSERT(exp) ( (exp)?(VOS_VOID)0:vos_assert(__FILE__, __LINE__) )
 */
#define RLC_ASSERT(exp) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return; }
#define RLC_ASSERT_RTN(exp, ret) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return ret; }
#else
#define RLC_ASSERT( exp ) ( (VOS_VOID)0 )
#define RLC_ASSERT_RTN(exp, ret) ( (VOS_VOID)0 )
#endif

#ifdef MAC_ASSERT_ON
/*#define MAC_ASSERT(exp) ( (exp)?(VOS_VOID)0:vos_assert(__FILE__, __LINE__) )
 */
#define MAC_ASSERT(exp) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return; }
#define MAC_ASSERT_RTN(exp, ret) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return ret; }
#else
#define MAC_ASSERT( exp ) ( (VOS_VOID)0 )
#define MAC_ASSERT_RTN(exp, ret) ( (VOS_VOID)0 )
#endif

#ifdef L2_ASSERT_ON
/*#define L2_ASSERT(exp) ( (exp)?(VOS_VOID)0:vos_assert(__FILE__, __LINE__) )
 */
#define L2_ASSERT(exp) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return; }
#define L2_ASSERT_RTN(exp, ret) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return ret; }
#else
#define L2_ASSERT( exp ) ( (VOS_VOID)0 )
#define L2_ASSERT_RTN(exp, ret) ( (VOS_VOID)0 )
#endif

#ifdef PS_ASSERT_ON
/*#define PS_ASSERT(exp) ( (exp)?(VOS_VOID)0:vos_assert(__FILE__, __LINE__) )
 */
#define PS_ASSERT(exp) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return; }
#define PS_ASSERT_RTN(exp, ret) \
    if(!(exp))\
    {\
        LPS_ASSERT;\
        return ret; }
#else
#define PS_ASSERT( exp ) ( (VOS_VOID)0 )
#define PS_ASSERT_RTN(exp, ret) ( (VOS_VOID)0 )
#endif

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


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of PsLib.h */
