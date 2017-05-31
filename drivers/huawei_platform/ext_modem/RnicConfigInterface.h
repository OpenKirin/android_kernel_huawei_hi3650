/******************************************************************************

					��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RnicConfigInterface.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��1��8��
  ����޸�   :
  ��������   : RNIC�����ṩ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��8��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __RNICCONFIGINTERFACE_H__
#define __RNICCONFIGINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define RNIC_MODEM_TYPE_IS_VALID(enModemType)\
    (((enModemType) == RNIC_MODEM_TYPE_INSIDE)\
  || ((enModemType) == RNIC_MODEM_TYPE_OUTSIDE))

#define RNIC_RMNET_STATUS_IS_VALID(enRmnetStatus)\
    (((enRmnetStatus) == RNIC_RMNET_STATUS_UP) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_DOWN) \
  || ((enRmnetStatus) == RNIC_RMNET_STATUS_SWITCH))

#define RNIC_IP_TYPE_IS_VALID(enIpType)\
    (((enIpType) == RNIC_IP_TYPE_IPV4) \
  || ((enIpType) == RNIC_IP_TYPE_IPV6) \
  || ((enIpType) == RNIC_IP_TYPE_IPV4V6))

/*****************************************************************************
   3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : RNIC_MODEM_TYPE_ENUM_UINT8
 �ṹ˵��  : RNICģ��Խ�MODEM������ö��
 1.��    ��   : 2014��01��27��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
	enum RNIC_MODEM_TYPE_ENUM {
		RNIC_MODEM_TYPE_INSIDE,	/* �ڲ�modem */
		RNIC_MODEM_TYPE_OUTSIDE,	/* �ⲿmodem */

		RNIC_MODEM_TYPE_BUTT
	};

	typedef unsigned char RNIC_MODEM_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RNIC_RMNET_STATUS_ENUM_UINT8
 �ṹ˵��  : RNIC������״̬��������ö��
 1.��    ��   : 2014��01��27��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
	enum RNIC_RMNET_STATUS_ENUM {
		RNIC_RMNET_STATUS_UP,	/* PDP�����������up״̬ */
		RNIC_RMNET_STATUS_DOWN,	/* PDPȥ�����������down״̬ */
		RNIC_RMNET_STATUS_SWITCH,	/* ����modem PDP״̬�л�����������switch״̬ */

		RNIC_RMNET_STATUS_BUTT
	};

	typedef unsigned char RNIC_RMNET_STATUS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RNIC_IP_TYPE_ENUM_UINT8
 �ṹ˵��  : RNIC������״̬���õ�IP����ö��
			ipv4v6���ͼ���ɹ�ʱ��Ҫ�ֱ��·�ipv4��ipv6 config����������Я����
			ip���ͷֱ�Ϊipv4��ipv6��
			ipv4v6����ȥ����ʱ��ֻ�·�һ��config����������Я����ip����Ϊipv4v6
 1.��    ��   : 2014��01��27��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
	enum RNIC_IP_TYPE_ENUM {
		RNIC_IP_TYPE_IPV4 = 0x01,
		RNIC_IP_TYPE_IPV6 = 0x02,
		RNIC_IP_TYPE_IPV4V6 = 0x03,

		RNIC_IP_TYPE_BUTT = 0xFF
	};

	typedef unsigned char RNIC_IP_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RNIC_RMNET_CONFIG_STRU
 �ṹ˵��  : �ⲿģ�����RNIC_ConfigRmnetStatus�ӿ�����RNIC�����������ṹ
 1.��    ��   : 2014��01��21��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
	typedef struct {
		RNIC_MODEM_TYPE_ENUM_UINT8 enModemType;
		unsigned char ucRmNetId;
		unsigned short usModemId;
		unsigned char ucPdnId;
		unsigned char ucRabId;
		RNIC_RMNET_STATUS_ENUM_UINT8 enRmnetStatus;
		RNIC_IP_TYPE_ENUM_UINT8 enIpType;
	} RNIC_RMNET_CONFIG_STRU;

/*****************************************************************************
   10 ��������
*****************************************************************************/

/* RNIC����״̬���ú��������ⲿģ����� */
	unsigned long RNIC_ConfigRmnetStatus(RNIC_RMNET_CONFIG_STRU *
					     pstConfigInfo);

/*****************************************************************************
 �� �� ��  : RNIC_StartFlowCtrl
 ��������  : ������������
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  : VOS_OK     - �������سɹ�
			VOS_ERR    - ��������ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
	unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId);

/*****************************************************************************
 �� �� ��  : RNIC_StopFlowCtrl
 ��������  : ֹͣ��������
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  : VOS_OK     - ֹͣ���سɹ�
			VOS_ERR    - ֹͣ����ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
	unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId);

#pragma pack(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif				/* end of RnicConfigInterface.h */
