/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtaCommInterface.h
  �� �� ��   : ����
  ��    ��   : zwx247453
  ��������   : 2015��11��02��
  ����޸�   :
  ��������   : AT, MTA������֮�乫�õĽӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��02��
    ��    ��   : zwx247453
    �޸�����   : �����ļ�

 ******************************************************************************/

#ifndef __MTACOMMINTERFACE_H__
#define __MTACOMMINTERFACE_H__

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
/*network monitor GSM���� �ϱ������� */
#define NETMON_MAX_GSM_NCELL_NUM                (6)

/*network monitor UTRAN ���� �ϱ������� */
#define NETMON_MAX_UTRAN_NCELL_NUM              (16)

/*network monitor LTE ���� �ϱ������� */
#define NETMON_MAX_LTE_NCELL_NUM                (16)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : MTA_RRC_GSM_BAND_ENUM
 �ṹ˵��  : MTAģ����GAS֮���BANDֵö��

  1.��    ��   : 2014��04��25��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
enum MTA_RRC_GSM_BAND_ENUM
{
    MTA_RRC_GSM_BAND_850  = 0x00,
    MTA_RRC_GSM_BAND_900,
    MTA_RRC_GSM_BAND_1800,
    MTA_RRC_GSM_BAND_1900,

    MTA_RRC_GSM_BAND_BUTT
};
typedef VOS_UINT16 MTA_RRC_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_NETMON_CELL_INFO_TYPE_ENUM
 �ṹ˵��  : MTAģ����������network monitor ��ѯС������ö�ٶ���

  1.��    ��   : 2014��11��20��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
enum MTA_NETMON_CELL_TYPE_ENUM
{
    MTA_NETMON_SCELL_TYPE               = 0,
    MTA_NETMON_NCELL_TYPE               = 1,
    MTA_NETMON_CELL_TYPE_BUTT
};

typedef VOS_UINT32 MTA_NETMON_CELL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MTA_NETMON_UTRAN_TYPE_ENUM
 �ṹ˵��  : MTAģ����������network monitor UTRAN��������ö�ٶ���

  1.��    ��   : 2014��11��20��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
enum MTA_NETMON_UTRAN_TYPE_ENUM
{
    MTA_NETMON_UTRAN_FDD_TYPE           = 0,
    MTA_NETMON_UTRAN_TDD_TYPE           = 1,
    MTA_NETMON_UTRAN_TYPE_BUTT
};
typedef VOS_UINT32 MTA_NETMON_UTRAN_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MTA_NETMON_RESULT_ENUM
 �ṹ˵��  : MTAģ����������network monitor��ѯ�����ö��

  1.��    ��   : 2014��11��20��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
enum MTA_NETMON_RESULT_ENUM
{
    MTA_NETMON_RESULT_NO_ERR            = 0,
    MTA_NETMON_RESULT_ERR               = 1,
    MTA_NETMON_RESULT_BUTT
};
typedef VOS_UINT32 MTA_NETMON_RESULT_ENUM_UINT32;

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

/* ========�����ǽ������MTA֮�����Ϣ�ṹ��======== */

/**************************network monitor��ѯ������Ϣ�ṹ�岿��**********************************************************/

/* MTA������������Ϣ��ͨ�ã�������2G/3G/����С��/���� */
/*****************************************************************************
 �ṹ��    : MTA_RRC_NETMON_CELL_QRY_REQ_STRU
 �ṹ˵��  : MTA���͸�GSM����ѯС����Ϣ(��������С��������)����Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /* ��Ϣͷ*/              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /*��Ϣ����*/             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;    /*0:��ѯ����С����1:��ѯ����*/
}MTA_RRC_NETMON_CELL_QRY_REQ_STRU;


/*GSM �����ṹ*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_GSM_NCELL_INFO_STRU
 �ṹ˵��  : GSM ������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBsic     : 1;
    VOS_UINT32                          bitOpCellID   : 1;
    VOS_UINT32                          bitOpLAC      : 1;
    VOS_UINT32                          bitOpSpare    : 29;
    VOS_UINT32                          ulCellID;       /*С��ID*/
    VOS_UINT16                          usLAC;          /*λ������*/
    VOS_UINT16                          usAfrcn;        /*Ƶ��*/
    VOS_INT16                           sRSSI;          /* Ƶ���RSSI */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;         /* band 0-3 */
    VOS_UINT8                           ucBsic;         /*С����վ��*/
    VOS_UINT8                           aucReserved[3];
}MTA_NETMON_GSM_NCELL_INFO_STRU;


/*LTE �����ṹ,��ʱ��������ݽṹ��������Ҫ���е���*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_LTE_NCELL_INFO_STRU
 �ṹ˵��  : LTE ������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPID;            /*����С��ID*/
    VOS_UINT16                          usArfcn;          /*Ƶ��*/
    VOS_INT16                           sRSRP;            /* RSRP�ο��źŽ��չ���*/
    VOS_INT16                           sRSRQ;            /* RSRQ�ο��źŽ�������*/
    VOS_INT16                           sRSSI;            /* Receiving signal strength in dbm */
}MTA_NETMON_LTE_NCELL_INFO_STRU;


/*WCDMA �����ṹ*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU
 �ṹ˵��  : WCDMA ������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;          /*Ƶ��*/
    VOS_UINT16                          usPSC;            /*������*/
    VOS_INT16                           sECN0;            /*ECN0*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU;


/*TD_SCDMA �����ṹ,��ʱ����ṹ��������Ҫ��������*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU
 �ṹ˵��  : TD_SCDMA ������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;          /*Ƶ��*/
    VOS_UINT16                          usSC;             /*����*/
    VOS_UINT16                          usSyncID;         /*���е�Ƶ��*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU;


/*�������ݽṹ*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU
 �ṹ˵��  : network monitor ����������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                ucGsmNCellCnt;      /*GSM ��������*/
    VOS_UINT8                                ucUtranNCellCnt;    /*WCDMA ��������*/
    VOS_UINT8                                ucLteNCellCnt;      /*LTE ��������*/
    VOS_UINT8                                ucReserved;
    MTA_NETMON_GSM_NCELL_INFO_STRU           astGsmNCellInfo[NETMON_MAX_GSM_NCELL_NUM];          /*GSM �������ݽṹ*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32        enCellMeasTypeChoice;     /* NETMONƵ����Ϣ����:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU astFddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /* FDD�������ݽṹ */
        MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU astTddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /*  TDD�������ݽṹ */
    }u;
    MTA_NETMON_LTE_NCELL_INFO_STRU           astLteNCellInfo[NETMON_MAX_LTE_NCELL_NUM];      /*LTE �������ݽṹ*/
}RRC_MTA_NETMON_NCELL_INFO_STRU;


/*********************network monitor��ѯGSM С����Ϣ����************************************************/
/*****************************************************************************
 �ṹ��    : MTA_GRR_NETMON_TA_QRY_REQ_STRU
 �ṹ˵��  : MTA���͸�GSM����ѯTA����Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /* ��Ϣͷ */             /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /* ��Ϣ���� */           /*_H2ASN_Skip*/
}MTA_GRR_NETMON_TA_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GRR_MTA_NETMON_TA_QRY_CNF_STRU
 �ṹ˵��  : GAS����MTA TA��ѯ�������Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : jumingxuan
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;          /* ��Ϣ���� */      /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;           /* ���ؽ�� */
    VOS_UINT16                          usTa;               /* ���ص�TAֵ */
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ���ı���λ */
}GRR_MTA_NETMON_TA_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GRR_MTA_NETMON_SCELL_INFO_STRU
 �ṹ˵��  : MTA����ID_MTA_GRR_NETMON_CELL_QRY_REQ��GAS��GAS�ظ��ķ���С����Ϣ�Ľṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : w00146666
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;              /* �ƶ������� */
    VOS_UINT32                          ulMnc;              /* �ƶ������� */
    VOS_UINT32                          ulCellID;           /* С��ID */
    VOS_UINT16                          usLac;              /* λ������ */
    VOS_UINT16                          usArfcn;            /* ����Ƶ��� */
    VOS_INT16                           sRssi;              /* Receiving signal strength in dbm */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;             /* GSMƵ��(0-3) */
    VOS_UINT8                           ucBsic;             /* С����վ�� */
    VOS_UINT8                           ucRxQuality;        /* IDLE̬�»���PS����̬����Ч,ר��̬������ŵ�����ֵ����Χ[0,7] ,��Чֵ99*/
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ���ı���λ */
}GRR_MTA_NETMON_SCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GRR_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 �ṹ˵��  : MTA����ID_MTA_GRR_NETMON_CELL_QRY_REQ��GAS��GAS�ظ���ϢID_GRR_MTA_NETMON_CELL_QRY_CNF�Ľṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : w00146666
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /* ��Ϣ���� */          /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;     /* 0:��ѯ����С����1:��ѯ���� */
    union
    {
        GRR_MTA_NETMON_SCELL_INFO_STRU  stSCellinfo;    /* GSM�µķ���С����Ϣ */
        RRC_MTA_NETMON_NCELL_INFO_STRU  stNCellinfo;    /* GSM�µ�������Ϣ */
    }u;
}GRR_MTA_NETMON_CELL_QRY_CNF_STRU;

/******************************network monitor��ѯUTRAN С����Ϣ����****************************************************/


/*FDD ����С����Ϣ�ṹ*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU
 �ṹ˵��  : WCDAM����С����Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDRX      : 1;
    VOS_UINT32                          bitOpURA      : 1;
    VOS_UINT32                          bitOpSpare    : 30;
    VOS_UINT32                          ulDrx;          /* Discontinuous reception cycle length */
    VOS_INT16                           sECN0;          /*ECN0*/
    VOS_INT16                           sRSSI;          /* Receiving signal strength in dbm */
    VOS_INT16                           sRSCP;          /*Received Signal Code Power in dBm�������ź��빦��*/
    VOS_UINT16                          usPSC;          /*������*/
    VOS_UINT16                          usURA;          /* UTRAN Registration Area Identity */
    VOS_UINT8                           aucReserved[2];

} MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU;


/*TDD ����С����Ϣ�ṹԤ������ȷ�Ϻ����*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU
 �ṹ˵��  :  TD_SCDAM����С����Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrx;              /* Discontinuous reception cycle length */
    VOS_UINT16                          usSC;               /*����*/
    VOS_UINT16                          usSyncID;           /*���е�Ƶ��*/
    VOS_UINT16                          usRac;              /*RAC*/
    VOS_INT16                           sRSCP;              /*RSCP*/
} MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU;



 /*UTRAN ����С���ṹ*/
 /*****************************************************************************
  �ṹ��    : RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU
  �ṹ˵��  : UTRAN����С����Ϣ�ṹ��

   1.��    ��   : 2014��10��27��
     ��    ��   : j00204253
     �޸�����   : ����
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpCellID  : 1;
    VOS_UINT32                                  bitOpLAC     : 1;
    VOS_UINT32                                  bitOpSpare   : 30;
    VOS_UINT32                                  ulMcc;                  /*�ƶ�������*/
    VOS_UINT32                                  ulMnc;                  /*�ƶ�������*/
    VOS_UINT32                                  ulCellID;               /*С��ID*/
    VOS_UINT16                                  usArfcn;                /*Ƶ��*/
    VOS_UINT16                                  usLAC;                  /*λ������*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32           enCellMeasTypeChoice;   /* NETMONƵ����Ϣ����:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU    stCellMeasResultsFDD;    /* FDD */
        MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU    stCellMeasResultsTDD;    /*  TDD */
    }u;
}RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 �ṹ˵��  : MTA����ID_MTA_RRC_NETMON_CELL_QRY_REQ��WAS��WAS�ظ���ϢID_RRC_MTA_NETMON_CELL_QRY_CNF�Ľṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : w00146666
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*��Ϣ����*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:��ѯ����С����1:��ѯ����*/
    union
    {
        RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU  stSCellinfo;      /* UTRAN�µķ���С����Ϣ */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* UTRAN�µ�������Ϣ */
    }u;
}RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;

/*LTE ����С���ṹ*/
/*****************************************************************************
 �ṹ��    : MTA_NETMON_EUTRAN_SCELL_INFO_STRU
 �ṹ˵��  : LTE����С����Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : j00204253
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulMcc;                  /*�ƶ�������*/
    VOS_UINT32                                  ulMnc;                  /*�ƶ�������*/
    VOS_UINT32                                  ulCellID;               /*С��ID*/
    VOS_UINT32                                  ulPID;                  /*����С��ID*/
    VOS_UINT16                                  usArfcn;                /*Ƶ��*/
    VOS_UINT16                                  usTAC;
    VOS_INT16                                   sRSRP;
    VOS_INT16                                   sRSRQ;
    VOS_INT16                                   sRSSI;
    VOS_UINT8                                   aucReserved[2];
} MTA_NETMON_EUTRAN_SCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MTA_LRRC_NETMON_CELL_QRY_REQ_STRU
 �ṹ˵��  : MTA����ID_MTA_LRRC_NETMON_CELL_QRY_REQ��LRR��Ϣ�ṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : w00146666
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* ��Ϣͷ */                /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;   /* ��Ϣ���� */             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;  /* 0����ѯ����С����1����ѯ���� */
}MTA_LRRC_NETMON_CELL_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 �ṹ˵��  : MTA����ID_MTA_LRRC_NETMON_CELL_QRY_REQ��LRR��WAS�ظ���ϢID_LRRC_MTA_NETMON_CELL_QRY_CNF�Ľṹ��

  1.��    ��   : 2014��10��27��
    ��    ��   : w00146666
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*��Ϣ����*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:��ѯ����С����1:��ѯ����*/
    union
    {
        MTA_NETMON_EUTRAN_SCELL_INFO_STRU     stSCellinfo;      /* LTE�µķ���С����Ϣ */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* LTE�µ�������Ϣ */
    }u;
}LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;


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

#endif /* end of MtaCommInterface.h */
