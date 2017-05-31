/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AppL2Interface.h
  �� �� ��   : ����
  ��    ��   : q00208938
  ��������   : 2014��6��10��
  ����޸�   :
  ��������   : L2��APP֮��ӿڶ���
  �����б�   :

  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   :
  2.��    ��   :
    ��    ��   :
    �޸�����   :

******************************************************************************/

#ifndef __APPL2INTERFACE_H__
#define __APPL2INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*CA���С����*/
#define CA_MAX_CELL_NUM             8

#ifndef VOS_MSG_HEADER
#define VOS_MSG_HEADER              VOS_UINT32  ulSenderCpuId;  \
                                    VOS_UINT32  ulSenderPid;    \
                                    VOS_UINT32  ulReceiverCpuId;\
                                    VOS_UINT32  ulReceiverPid;  \
                                    VOS_UINT32  ulLength;
#endif

#ifndef APP_MSG_HEADER
#define APP_MSG_HEADER              VOS_UINT16  usOriginalId;\
                                    VOS_UINT16  usTerminalId;\
                                    VOS_UINT32  ulTimeStamp; \
                                    VOS_UINT32  ulSN;
#endif

#define L2_APP_MSG_HDR              PS_MSG_ID_L2_TO_APP_BASE            /*0xe00*/
#define APP_L2_MSG_HDR              PS_MSG_ID_APP_TO_L2_BASE            /*0xe10*/

#define MAC_APP_MSG_HDR             PS_MSG_ID_MAC_TO_APP_BASE           /*0xe20*/
#define APP_MAC_MSG_HDR             PS_MSG_ID_APP_TO_MAC_BASE           /*0xe50*/

#define RLC_APP_MSG_HDR             PS_MSG_ID_RLC_TO_APP_BASE           /*0xe80*/
#define APP_RLC_MSG_HDR             PS_MSG_ID_APP_TO_RLC_BASE           /*0xea0*/

#define PDCP_APP_MSG_HDR            PS_MSG_ID_PDCP_TO_APP_BASE          /*0xec0*/
#define APP_PDCP_MSG_HDR            PS_MSG_ID_APP_TO_PDCP_BASE          /*0xee0*/
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 ö����    : LUP_OM_MSG_ID_SECTION_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE �û���OM��Ϣ�ֶ�
*****************************************************************************/
enum LUP_OM_MSG_ID_SECTION_ENUM
{
    LUP_OM_MSG_ID_CDS_BASE      = TL_PTL_MSG_ID_LTE_L2_BASE,
    LUP_OM_MSG_ID_LPDCP_BASE    = LUP_OM_MSG_ID_CDS_BASE   + 0x20,
    LUP_OM_MSG_ID_LRLC_BASE     = LUP_OM_MSG_ID_LPDCP_BASE + 0x20,
    LUP_OM_MSG_ID_LMAC_BASE     = LUP_OM_MSG_ID_LRLC_BASE  + 0x20,
    LUP_OM_MSG_ID_LMAC_END      = LUP_OM_MSG_ID_LMAC_BASE  + 0x1F,
    LUP_OM_MSG_ID_BUTT
};



/*****************************************************************************
 ö����    : APP_L2_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :L2�ڲ���APP ֮����ϢID����. ��Ϣ��Χ��������ʹ��.
*****************************************************************************/
enum APP_L2_MSG_TYPE_ENUM
{
    /* ͸������ */
    ID_APP_L2_TRANSPARENT_CMD_REQ           = (APP_L2_MSG_HDR + 0x01),
    ID_APP_L2_TRANSPARENT_CMD_CNF           = (L2_APP_MSG_HDR + 0x02),
    ID_APP_L2_TRANSPARENT_CMD_IND           = (L2_APP_MSG_HDR + 0x03),

    /*��ά�ɲ�-����������ͳ��  */
    ID_OM_L2_THROUGHPUT_CMD_REQ             = (APP_L2_MSG_HDR + 0x03),  /*0xe13*/
    ID_L2_OM_THROUGHPUT_CMD_CNF             = (L2_APP_MSG_HDR + 0x06),  /*0xe06*/

    /*��ά�ɲ�-����SDUͳ��  */
    ID_OM_L2_SDUCOUNT_CMD_REQ               = (APP_L2_MSG_HDR + 0x04),  /*0xe14*/
    ID_L2_OM_SDUCOUNT_CMD_CNF               = (L2_APP_MSG_HDR + 0x07),  /*0xe07*/

    /*����·����Ϣ*/
    ID_OM_L2_DT_RA_INFO_CMD_REQ             = (APP_L2_MSG_HDR + 0x05),  /*0xe15*/
    ID_L2_OM_DT_RA_INFO_CMD_CNF             = (L2_APP_MSG_HDR + 0x08),  /*0xe08*/
    ID_OM_L2_DT_RB_INFO_CMD_REQ             = (APP_L2_MSG_HDR + 0x06),  /*0xe16*/
    ID_L2_OM_DT_RB_INFO_CMD_CNF             = (L2_APP_MSG_HDR + 0x09),  /*0xe09*/
    ID_OM_L2_DT_HO_LATENCY_CMD_REQ          = (APP_L2_MSG_HDR + 0x07),  /*0xe17*/
    ID_L2_OM_DT_HO_LATENCY_CMD_CNF          = (L2_APP_MSG_HDR + 0x0A),  /*0xe0A*/
    ID_OM_L2_DT_CONTENT_TMR_CMD_REQ         = (APP_L2_MSG_HDR + 0x08),  /*0xe18*/
    ID_L2_OM_DT_CONTENT_TMR_CMD_CNF         = (L2_APP_MSG_HDR + 0x0B),  /*0xe0B*/
    ID_OM_L2_DT_SR_STATUS_CMD_REQ           = (APP_L2_MSG_HDR + 0x09),  /*0xe19*/
    ID_L2_OM_DT_SR_STATUS_CMD_CNF           = (L2_APP_MSG_HDR + 0x0C),  /*0xe0C*/

    /*DCM logger, MAC PDU �ϱ�*/
    ID_OM_L2_DCM_MAC_PDU_RPT_CMD_REQ        = (APP_L2_MSG_HDR + 0x0A),  /*0xe1A*/
    ID_L2_OM_DCM_MAC_PDU_RPT_CMD_CNF        = (L2_APP_MSG_HDR + 0x0D),  /*0xe0D*/
    ID_L2_OM_DCM_DL_MAC_PDU_RPT_IND         = (L2_APP_MSG_HDR + 0x0E),  /*0xe0E*/
    ID_L2_OM_DCM_UL_MAC_PDU_RPT_IND         = (L2_APP_MSG_HDR + 0x01),  /*0xe01*/   /*not conflict with other ID*/

    ID_OM_L2_DCM_BSR_RPT_CMD_REQ            = (APP_L2_MSG_HDR + 0x0B),  /*0xe1B*/
    ID_L2_OM_DCM_BSR_RPT_CMD_CNF            = (L2_APP_MSG_HDR + 0x0F),  /*0xe0F*/
    ID_L2_OM_DCM_CA_CTRL_ELEMENT_IND        = (L2_APP_MSG_HDR + 0x04),  /*0xe04*/
    /*end DCM logger*/
    ID_APP_MAC_TRANSPARENT_CMD_REQ          = (APP_MAC_MSG_HDR + 0x01),
    ID_APP_MAC_TRANSPARENT_CMD_CNF          = (MAC_APP_MSG_HDR + 0x02),
    ID_APP_MAC_TRANSPARENT_CMD_IND          = (MAC_APP_MSG_HDR + 0x03),

    /*CA CELL״̬�ϱ�*/
    ID_APP_MAC_CA_CELL_CMD_REQ              = (APP_MAC_MSG_HDR + 0x02),
    ID_MAC_APP_CA_CELL_CMD_CNF              = (MAC_APP_MSG_HDR + 0x04),
    ID_MAC_APP_CA_CELL_CMD_IND              = (MAC_APP_MSG_HDR + 0x05),

    /* L2��������������ͳ�ƿ�ά�ɲ������Ϣ��m00280824 2014/12/09 BEGIN*/
    ID_PS_OM_MAC_RA_MSG1_INFO_IND             = (MAC_APP_MSG_HDR + 0x06),
    ID_PS_OM_MAC_RA_MSG2_INFO_IND             = (MAC_APP_MSG_HDR + 0x07),
    ID_PS_OM_MAC_RA_MSG3_INFO_IND             = (MAC_APP_MSG_HDR + 0x08),
    ID_PS_OM_MAC_RAMSG3_HARQ_RETX_IND         = (MAC_APP_MSG_HDR + 0x09),
    ID_PS_OM_MAC_RAMSG4_CCCH_INFO_IND         = (MAC_APP_MSG_HDR + 0x0A),
    ID_PS_OM_MAC_RAMSG4_CRNTI_INFO_IND        = (MAC_APP_MSG_HDR + 0x0B),
    ID_PS_OM_MAC_RAMSG4_PDCCH_INFO_IND        = (MAC_APP_MSG_HDR + 0x0C),
    /* L2��������������ͳ�ƿ�ά�ɲ������Ϣ��m00280824 2014/12/09 END*/

    ID_APP_RLC_TRANSPARENT_CMD_REQ          = (APP_RLC_MSG_HDR + 0x01),
    ID_APP_RLC_TRANSPARENT_CMD_CNF          = (RLC_APP_MSG_HDR + 0x02),
    ID_APP_RLC_TRANSPARENT_CMD_IND          = (RLC_APP_MSG_HDR + 0x03),

    ID_APP_PDCP_TRANSPARENT_CMD_REQ         = (APP_PDCP_MSG_HDR + 0x01),
    ID_APP_PDCP_TRANSPARENT_CMD_CNF         = (PDCP_APP_MSG_HDR + 0x02),
    ID_APP_PDCP_TRANSPARENT_CMD_IND         = (PDCP_APP_MSG_HDR + 0x03),

    ID_OM_L2_SWITCH_CONTROL_CMD_REQ         = (APP_PDCP_MSG_HDR + 0x02),  /*0xec2*/
    ID_L2_OM_SWITCH_CONTROL_CMD_CNF         = (PDCP_APP_MSG_HDR + 0x04),   /*0xee4*/
    /* DTS2014081204455 L2��λ��������������ӵ��⣬w00161397 2014/08/07 */

    ID_PS_OM_PDCP_UL_SRB_INFO_IND           = (PDCP_APP_MSG_HDR + 0x05),
    ID_PS_OM_PDCP_UL_RRC_CNF_INFO_IND       = (PDCP_APP_MSG_HDR + 0x06),
    ID_PS_OM_RLC_UL_SRB_PDU_INFO_IND        = (PDCP_APP_MSG_HDR + 0x07),
    ID_PS_OM_RLC_UL_TX_CTRL_PDU_INFO_IND    = (PDCP_APP_MSG_HDR + 0x08),
    ID_PS_OM_RLC_DL_RX_CTRL_PDU_INFO_IND    = (PDCP_APP_MSG_HDR + 0x09),
    ID_PS_OM_RLC_DL_SRB_PDU_INFO_IND        = (PDCP_APP_MSG_HDR + 0x0A)

    /* DTS2014081204455 L2��λ��������������ӵ��⣬w00161397 2014/08/07 */
};
typedef         VOS_UINT32          APP_L2_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LUP_OM_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE�û���OM��Ϣ�ϱ�
*****************************************************************************/
enum LUP_OM_MSG_TYPE_ENUM
{
    /*LTE PDCP*/
    ID_TL_OM_LPDCP_INTEGRITY_ERROR_IND      = (LUP_OM_MSG_ID_LPDCP_BASE + 0x00),
    ID_TL_OM_LTE_USERPLANE_HO_DELAY_IND     = (LUP_OM_MSG_ID_LPDCP_BASE + 0x01),

    /*LTE RLC*/
    ID_TL_OM_LRLC_RL_FAIL_INFO              = (LUP_OM_MSG_ID_LRLC_BASE + 0x00),
    ID_TL_OM_LRLC_DLTB_MEM_FULL_IND         = (LUP_OM_MSG_ID_LRLC_BASE + 0x01),
    ID_TL_OM_LRLC_POLL_RETX_TMR_EXPIRY_IND  = (LUP_OM_MSG_ID_LRLC_BASE + 0x02),

    /*LTE MAC*/
    ID_TL_OM_LMAC_RA_CNF_TMR_EXPIRY         = (LUP_OM_MSG_ID_LMAC_BASE + 0x00),
    ID_TL_OM_LMAC_RA_RAR_TMR_EXPIRY         = (LUP_OM_MSG_ID_LMAC_BASE + 0x01),
    ID_TL_OM_LMAC_RA_CONTENT_TMR_EXPIRY     = (LUP_OM_MSG_ID_LMAC_BASE + 0x02),
    ID_TL_OM_LMAC_RA_RESULT_INFO_IND        = (LUP_OM_MSG_ID_LMAC_BASE + 0x03),
    ID_TL_OM_LMAC_RETX_BSR_TMR_EXPIRY       = (LUP_OM_MSG_ID_LMAC_BASE + 0x04),
    ID_TL_OM_LMAC_SR_OVER_MAX_TX_NUM        = (LUP_OM_MSG_ID_LMAC_BASE + 0x05),
    ID_TL_OM_LMAC_TA_TMR_EXPIRY             = (LUP_OM_MSG_ID_LMAC_BASE + 0x06),
    ID_TL_OM_LMAC_SCELL_ACT_DEACT_MCE_INFO  = (LUP_OM_MSG_ID_LMAC_BASE + 0x07),
    ID_TL_OM_LMAC_SCELL_DEACT_TMR_EXPIRY    = (LUP_OM_MSG_ID_LMAC_BASE + 0x08),
    ID_TL_OM_LMAC_PDCCH_REL_UL_SPS_IND      = (LUP_OM_MSG_ID_LMAC_BASE + 0x0A),
    ID_TL_OM_LMAC_RAR_GRANT_SCHED_FAIL      = (LUP_OM_MSG_ID_LMAC_BASE + 0x0B),
    ID_TL_OM_LMAC_RA_ACK_INFO_IND           = (LUP_OM_MSG_ID_LMAC_BASE + 0x0C),

    ID_TL_OM_MSG_TYPE_END
};
typedef VOS_UINT32 LRRC_LMAC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : LMAC_APP_SCELL_CONFIG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCELL������/δ����״̬ö��
*****************************************************************************/
enum LMAC_APP_SCELL_CONFIG_TYPE_ENUM
{
    LMAC_APP_SCELL_NOT_CONFIGED                    = 0x0,                           /*SCELLδ������*/
    LMAC_APP_SCELL_CONFIGED                        = 0x1,                           /*SCELL�ѱ�����*/
    LMAC_APP_SCELL_CONFIG_TYPE_BUTT
};
typedef         VOS_UINT8           LMAC_APP_SCELL_CONFIG_TYPE_ENUM_UINT8;
/*****************************************************************************
 �ṹ��    : LMAC_APP_SCELL_STATUS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCELL�ļ���/ȥ����״̬ö��
*****************************************************************************/
enum LMAC_APP_SCELL_STATUS_TYPE_ENUM
{
    LMAC_APP_SCELL_DEACTIVED                       = 0x0,                           /*SCELL����ȥ����̬*/
    LMAC_APP_SCELL_ACTIVED                         = 0x1,                           /*SCELL���ڼ���̬*/
    LMAC_APP_SCELL_STATUS_TYPE_BUTT
};
typedef         VOS_UINT8           LMAC_APP_SCELL_STATUS_TYPE_ENUM_UINT8;
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
 �ṹ��    :CA_CELL_STATUS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucUlConfigured;     /*CA�����Ƿ����ã�0:δ���ã�1:������*/
    VOS_UINT8                   ucDlConfigured;     /*CA�����Ƿ����ã�0:δ���ã�1:������*/
    VOS_UINT8                   ucActived;          /*SCell�Ƿ񱻼��0:ȥ���1:����*/
    VOS_UINT8                   ucRsv;
}CA_CELL_STATUS_STRU;
/*****************************************************************************
 �ṹ��    :APP_L2_CA_CELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /*_H2ASN_Skip*/
    VOS_UINT32                  ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32 ulOpId;
}APP_L2_CA_CELL_INFO_REQ_STRU;
/*****************************************************************************
 �ṹ��    :L2_APP_CA_CELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /*_H2ASN_Skip*/
    VOS_UINT32                  ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                  ulOpId;
    CA_CELL_STATUS_STRU         astCellStatus[CA_MAX_CELL_NUM];
}L2_APP_CA_CELL_INFO_CNF_STRU;
/*****************************************************************************
 �ṹ��    :L2_APP_CA_CELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                              /*_H2ASN_Skip*/
    VOS_UINT32                  ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                  ulOpId;
    CA_CELL_STATUS_STRU         astCellStatus[CA_MAX_CELL_NUM];
}L2_APP_CA_CELL_INFO_IND_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of AppL2Interface.h */
