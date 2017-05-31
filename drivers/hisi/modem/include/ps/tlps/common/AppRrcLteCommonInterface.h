/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AppRrcInterface.h
  Description     : AppRrcInterface.h header file
  History         :
     1.XiaoJun 58160       2009-4-29     Draft Enact
	 2.lishangfeng  55206 2011-09-11 DTS2011091100356:����Ϣά�����ԸĽ��������ܹ�֧�ֶ�Bandʱ��ά��
******************************************************************************/

#ifndef __APPRRCLTECOMMONINTERFACE_H__
#define __APPRRCLTECOMMONINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#define LMAX_NEIGHBOR_CELL_NUM    (16)
#ifndef VOS_MSG_HEADER
#define VOS_MSG_HEADER  VOS_UINT32 uwSenderCpuId;  \
                        VOS_UINT32 uwSenderPid;    \
                        VOS_UINT32 uwReceiverCpuId;\
                        VOS_UINT32 uwReceiverPid;  \
                        VOS_UINT32 uwLength;
#endif
#ifndef APP_MSG_HEADER
#define APP_MSG_HEADER                  VOS_UINT16   usOriginalId;\
                                        VOS_UINT16   usTerminalId;\
                                        VOS_UINT32   ulTimeStamp; \
                                        VOS_UINT32   ulSN;
#endif

enum RRC_OM_GET_CELL_INFO_FLAG_ENUM
{
    EN_GET_SERVICE_CELL_INFO = 0,
    EN_GET_NEIGHBOR_CELL_INFO = 1
};

typedef VOS_UINT32 RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : APP_LRRC_GET_NCELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32   enCellFlag;   /*=0��ʾ��ȡ����С����=1��ʾ��ȡ����*/
}APP_LRRC_GET_NCELL_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����С����ͬƵ����ƵС����������ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;/* С��id */
    VOS_INT16                           sRsrp;/* RSRPֵ */
    VOS_INT16                           sRsrq;/* RSRqֵ */
    VOS_INT16                           sRssi;/* RSSIֵ */
}LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����С����ͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;/* ����С��Ƶ�� */
    VOS_UINT16                          enBandInd;/* Ƶ��ָʾ */
    LRRC_APP_SRVING_CELL_MEAS_RESULT_STRU     stMeasRslt;
}LRRC_APP_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_CELL_MEAS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����С����ͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulNCellNumber;
    LRRC_APP_CELL_INFO_STRU stCellMeasInfo[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_CELL_MEAS_INFO_STRU;

typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_SRV_CELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU;
typedef LRRC_APP_CELL_MEAS_INFO_STRU LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_BSIC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BSC��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usNcc;
    VOS_UINT16                                              usBcc;
}LRRC_APP_BSIC_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LRRC_GERAN_NCELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L��ģ�£�GSM ������Ϣ
*****************************************************************************/

typedef struct
{
    VOS_UINT16    usArfcn;
    VOS_INT16     sRSSI;
    LRRC_APP_BSIC_INFO_STRU     stBSIC;
}LRRC_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_UMTS_NCELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L��ģ�£�UMTS������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usARFCN;
    VOS_UINT16    usPrimaryScramCode;
    VOS_INT16     sCpichRscp;
    VOS_INT16     sCpichEcN0;
}LRRC_UMTS_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L��ģ�£�UMTS������Ϣ�б�
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulNCellNumber;
    LRRC_UMTS_NCELL_INFO_STRU stUMTSNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L��ģ�£�GSM ������Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulNCellNumber;
    LRRC_GERAN_NCELL_INFO_STRU stGeranNcellList[LMAX_NEIGHBOR_CELL_NUM];
}LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_NCELL_LIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����С����ͬƵ����Ƶ�Լ���ϵͳ�������
*****************************************************************************/
typedef struct
{
    RRC_OM_GET_CELL_INFO_FLAG_ENUM_UINT32      enCellFlag;   /*=0��ʾ��ȡ����С����=1��ʾ��ȡ����*/
    LRRC_APP_SRV_CELL_MEAS_INFO_STRU          stSevCellInfo; /*����С����Ϣ������Ƶ�㡢band��Phycial ID,RSRP,RSRQ,RSSI*/
    LRRC_APP_INTRA_FREQ_NCELL_MEAS_INFO_STRU  stIntraFreqNcellList;/* ͬƵ������Ϣ*/
    LRRC_APP_INTER_FREQ_NCELL_MEAS_INFO_STRU  stInterFreqNcellList;/* ��Ƶ������Ϣ*/
    LRRC_APP_INTER_RAT_UMTS_NCELL_LIST_STRU    stInterRATUMTSNcellList; /* WCDMA/TDSCDMA��ϵͳ����*/
    LRRC_APP_INTER_RAT_GERAN_NCELL_LIST_STRU  stInterRATGeranNcellList; /* GERAN��ϵͳ���� */
}LRRC_APP_NCELL_LIST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_GET_NCELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����С����ͬƵ����Ƶ�Լ���ϵͳ������Ϣ
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                       /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32             ulOpId;
    VOS_UINT32             enResult;
    LRRC_APP_NCELL_LIST_INFO_STRU stNcellListInfo;
}LRRC_APP_GET_NCELL_INFO_CNF_STRU;




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppRrcInterface.h */
