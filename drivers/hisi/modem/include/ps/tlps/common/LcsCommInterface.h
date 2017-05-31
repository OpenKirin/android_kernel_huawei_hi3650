/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : LcsCommInterface.h
  �� �� ��   : ����
  ��    ��   : l00198894
  ��������   : 2015��9��14��
  ����޸�   :
  ��������   : LCS���Թ������ݽṹ�����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��14��
    ��    ��   : l00198894
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __LCSCOMMINTERFACE_H__
#define __LCSCOMMINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
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
#define LCS_CLIENT_EXID_MAX_LEN         (20)
#define LCS_CLIENT_NAME_MAX_LEN         (160)
#define LCS_MOLR_TIMEOUT_DEFAULT        (180)
#define LCS_MOLR_INTERVAL_DEFAULT       (180)
#define LCS_HOR_ACC_DEFAULT_VALUE       (60)
#define LCS_VER_ACC_DEFAULT_VALUE       (60)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*******************************************************************************
 ö����    : LCS_PLANE_ENUM
 �ṹ˵��  : LCS����MO-LR����PLANEö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_PLANE_ENUM
{
    LCS_PLANE_CONTROL                   = 0,
    LCS_PLANE_SECURE_USER,

    LCS_PLANE_BUTT
};
typedef VOS_UINT8 LCS_PLANE_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_MOLR_METHOD_ENUM
 �ṹ˵��  : LCS����MO-LR���̶�λ����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_MOLR_METHOD_ENUM
{
    LCS_MOLR_METHOD_GPS                 = 0,                                    /* Unassisted GPS */
    LCS_MOLR_METHOD_AGPS,                                                       /* Assisted GPS */
    LCS_MOLR_METHOD_AGNSS,                                                      /* Assisted GANSS */
    LCS_MOLR_METHOD_AGPS_AGNSS,                                                 /* Assisted GPS and GANSS */
    LCS_MOLR_METHOD_BASIC_SELF,                                                 /* Basic self location */
    LCS_MOLR_METHOD_TRANSFER_TP_ADDR,                                           /* Transfer to third party */
    LCS_MOLR_METHOD_RETRIEVAL_TP_ADDR,                                          /* Retrieval from third party */

    LCS_MOLR_METHOD_BUTT
};
typedef VOS_UINT8 LCS_MOLR_METHOD_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_HOR_ACC_SET_ENUM
 �ṹ˵��  : LCS����MO-LR����ˮƽ�������ñ�־ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_HOR_ACC_SET_ENUM
{
    LCS_HOR_ACC_NOT_SET                 = 0,
    LCS_HOR_ACC_SET_PARAM,

    LCS_HOR_ACC_SET_BUTT
};
typedef VOS_UINT8 LCS_HOR_ACC_SET_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_VER_REQ_ENUM
 �ṹ˵��  : LCS����MO-LR���̴�ֱ��������ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_VER_REQ_ENUM
{
    LCS_VER_NOT_REQUESTED               = 0,
    LCS_VER_REQUESTED,

    LCS_VER_REQ_BUTT
};
typedef VOS_UINT8 LCS_VER_REQ_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_VER_ACC_SET_ENUM
 �ṹ˵��  : LCS����MO-LR���̴�ֱ�������ñ�־ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_VER_ACC_SET_ENUM
{
    LCS_VER_ACC_NOT_SET                 = 0,
    LCS_VER_ACC_SET_PARAM,

    LCS_VER_ACC_SET_BUTT
};
typedef VOS_UINT8 LCS_VER_ACC_SET_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_VEL_REQ_ENUM
 �ṹ˵��  : LCS����MO-LR�����ٶ�����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_VEL_REQ_ENUM
{
    LCS_VEL_NOT_REQUESTED               = 0,                                    /* Velocity not requested */
    LCS_VEL_REQ_HOR,                                                            /* Horizontal velocity requested */
    LCS_VEL_REQ_HOR_VER,                                                        /* Horizontal velocity and vertical velocity requested */
    LCS_VEL_REQ_HOR_ACC,                                                        /* Horizontal velocity with uncertainty requested */
    LCS_VEL_REQ_HOR_ACC_VER_ACC,                                                /* Horizontal velocity with uncertainty and vertical velocity with uncertainty requested */

    LCS_VEL_REQ_BUTT
};
typedef VOS_UINT8 LCS_VEL_REQ_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_REP_MODE_ENUM
 �ṹ˵��  : LCS����MO-LR�����ϱ�ģʽö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_REP_MODE_ENUM
{
    LCS_REP_MODE_SINGLE_RPT             = 0,
    LCS_REP_MODE_PERIODIC_RPT,

    LCS_REP_MODE_BUTT
};
typedef VOS_UINT8 LCS_REP_MODE_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_MTLRA_OP_ENUM
 �ṹ˵��  : LCS����MT-LR�û���Ӧ���綨λ�������ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_MTLRA_OP_ENUM
{
    LCS_MTLRA_ALLOW                     = 0,
    LCS_MTLRA_NOT_ALLOW,

    LCS_MTLRA_OP_BUTT
};
typedef VOS_UINT8 LCS_MTLRA_OP_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_NOTIFICATION_TYPE_ENUM
 �ṹ˵��  : LCS����MT-LR���綨λ�����е��û���˽��Ϣ����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_NOTIFICATION_TYPE_ENUM
{
    LCS_NOTIFICATION_ALLOW_THIRD_PARTY          = 0,
    LCS_NOTIFICATION_PERMIT_IF_USER_IGNORE,
    LCS_NOTIFICATION_FORBIDDEN_IF_USER_IGNORE,

    LCS_NOTIFICATION_TYPE_BUTT
};
typedef VOS_UINT8 LCS_NOTIFICATION_TYPE_ENUM_UINT8;

/*******************************************************************************
 ö����    : LCS_LOCATION_TYPE_ENUM
 �ṹ˵��  : LCS����MT-LR���綨λ�����е��û���˽��Ϣ����ö��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*******************************************************************************/
enum LCS_LOCATION_TYPE_ENUM
{
    LCS_LOCATION_CURRENT                = 0,
    LCS_LOCATION_CURR_OR_LAST,
    LCS_LOCATION_INITIAL,

    LCS_LOCATION_TYPE_BUTT
};
typedef VOS_UINT8 LCS_LOCATION_TYPE_ENUM_UINT8;






/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  5 STRUCT����
*****************************************************************************/

/*******************************************************************************
 �ṹ��    : LCS_SHAPE_REP_STRU
 �ṹ˵��  : LCS����MO-LR���̲���shape-rep��Ӧ�ṹ��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           bitEllipPoint               :1;
    VOS_UINT8                           bitEllipPointUncertCircle   :1;
    VOS_UINT8                           bitEllipPointUncertEllip    :1;
    VOS_UINT8                           bitPolygon                  :1;
    VOS_UINT8                           bitEllipPointAlt            :1;
    VOS_UINT8                           bitEllipPointAltUncertEllip :1;
    VOS_UINT8                           bitEllipArc                 :1;
    VOS_UINT8                           bitSpare                    :1;
} LCS_SHAPE_REP_STRU;

/*******************************************************************************
 �ṹ��    : LCS_CLIENT_EXTERNAL_ID_STRU
 �ṹ˵��  : LCS���Կͻ�����չID�ṹ��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucValue[LCS_CLIENT_EXID_MAX_LEN];
    /***************************************************************************
            _H2ASN_Array2String
    ***************************************************************************/
}LCS_CLIENT_EXTERNAL_ID_STRU;

/*******************************************************************************
 �ṹ��    : LCS_CLIENT_NAME_STRU
 �ṹ˵��  : LCS���Կͻ������ƽṹ��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucValue[LCS_CLIENT_NAME_MAX_LEN];
    /***************************************************************************
            _H2ASN_Array2String
    ***************************************************************************/
}LCS_CLIENT_NAME_STRU;

/*******************************************************************************
 �ṹ��    : LCS_MOLR_PARA_STRU
 �ṹ˵��  : LCS����MO-LR���̲����ṹ��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    LCS_MOLR_METHOD_ENUM_UINT8          enMethod;
    LCS_HOR_ACC_SET_ENUM_UINT8          enHorAccSet;
    VOS_UINT8                           ucHorAcc;                               /* horizontal-accuracy */

    LCS_VER_REQ_ENUM_UINT8              enVerReq;                               /* verticalCoordinate Request */
    LCS_VER_ACC_SET_ENUM_UINT8          enVerAccSet;
    VOS_UINT8                           ucVerAcc;                               /* vertical-accuracy */
    LCS_VEL_REQ_ENUM_UINT8              enVelReq;                               /* velocityRequest */

    LCS_REP_MODE_ENUM_UINT8             enRepMode;                              /* MO-LR�ȴ�����ظ���ʱ��ʱ�� */
    VOS_UINT16                          usTimeOut;                              /* �����ϱ�ʱ���ϱ����ʱ�� */
    VOS_UINT16                          usInterval;

    union
    {
        VOS_UINT8                       ucShapeRep;
        LCS_SHAPE_REP_STRU              stShapeRep;
    } u;

    VOS_UINT8                           aucReserved[3];
    LCS_CLIENT_EXTERNAL_ID_STRU         stTPAddr;                               /* Third Party Address */
}LCS_MOLR_PARA_STRU;

/*******************************************************************************
 �ṹ��    : LCS_MTLR_PARA_STRU
 �ṹ˵��  : LCS����MT-LR���̲����ṹ��
  1.��    ��   : 2015��8��25��
    ��    ��   : l00198894
    �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpClientExId     : 1;
    VOS_UINT32                          bitOpClientName     : 1;
    VOS_UINT32                          bitOpPlane          : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucHandleId;
    LCS_NOTIFICATION_TYPE_ENUM_UINT8    enNtfType;
    LCS_LOCATION_TYPE_ENUM_UINT8        enLocationType;
    LCS_PLANE_ENUM_UINT8                enPlane;

    LCS_CLIENT_EXTERNAL_ID_STRU         stClientExId;
    LCS_CLIENT_NAME_STRU                stClientName;
}LCS_MTLR_PARA_STRU;




/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 OTHERS����
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/








#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LcsCommInterface.h */

