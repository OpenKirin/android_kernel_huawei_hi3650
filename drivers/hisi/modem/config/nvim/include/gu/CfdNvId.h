/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CfdNvId.h
  �� �� ��   :
  ��    ��   : 
  ��������   : 2010��12��24��
  ����޸�   :
  ��������   : �����˻�Ҫ����NV��IDö�ٶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��12��24��
    ��    ��   : y00163779
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CFDNVID_H__
#define __CFDNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "NvIddef.h"

enum CFD_NV_ID_ENUM
{
/* 8267  */      en_NV_Item_CustomizeSimLockPlmnInfo = GU_PS_NV_ID_MIN + 74,
/* 8268  */      en_NV_Item_CardlockStatus,
/* 8269  */      en_NV_Item_CustomizeSimLockMaxTimes,
/* 8481  */      en_NV_Item_OperLock_Plmn_Info = 8481,
/* 8494  */      en_NV_Item_OPERLOCK_PLMN_INFO_WHITE = 8494,
                 en_NV_Item_BUTT
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __CFDNVID_H__ */
