
#ifndef __MSP_L4A_H__
#define __MSP_L4A_H__

#include "vos.h"

/*****************************************************************************
 ��������: OSA_PostMessageToMsp
 ��������: Э��ջ���øýӿڷ�����Ϣ��MSP
           
 ����˵��:
   ulMsgId [in]: ��ϢID,����ϢID������MSP�����,�п�����PS�����
                
   ulParam1 [in]: �������Ϣ�ṹָ��,��Ϣ���ɵ�����(PS)�����ڴ�(ͨ��malloc), �������ͷ�(ͨ��free)
                 
   ulParam2 [in]:��͸��ָ��ʹ����,�ò���ΪulParam1�ṹ����
                 ,��Ϊ���͸��ʱ��,����������;
                 

 �� �� ֵ: 
    TODO: ...

 ����Ҫ��: ������:Э��ջ, ������Ϣ��MSP,�ú��������������������ء�
 ���þ���: TODO: ...
 ��    ��: ���ķ�/00149739 [2009-04-24]
*****************************************************************************/
extern VOS_UINT32 OSA_PostMessageToMsp(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);




/* ������Ϣ��PS,�ú��������������������ء�*/
/* ulParam1/2����Ϊָ��.*/
extern VOS_UINT32 OSM_PostMessageToPs(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

#endif