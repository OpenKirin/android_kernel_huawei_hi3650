

#ifndef __ATMSGPRINT_H__
#define __ATMSGPRINT_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "AtCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
enum
{
    AT_MSG_SERV_STATE_NOT_SUPPORT,
    AT_MSG_SERV_STATE_SUPPORT
};
typedef VOS_UINT8 AT_MSG_SERV_STATE_ENUM_U8;

enum AT_MSG_PARSE_STATUS
{
    AT_MSG_PARSE_STATUS_START,
    AT_MSG_PARSE_STATUS_LOWERDATA,
    AT_MSG_PARSE_STATUS_WAITUPPER,
    AT_MSG_PARSE_STATUS_UPPERDATA,
    AT_MSG_PARSE_STATUS_END,
    AT_MSG_PARSE_STATUS_BUTT
};
typedef VOS_UINT32 AT_MSG_PARSE_STATUS_UINT32;

typedef VOS_UINT32 (* AT_MSG_STATUS_CHK_FUNC)(TAF_UINT8);


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
typedef struct
{
    AT_MSG_SERV_STATE_ENUM_U8           enSmsMT;
    AT_MSG_SERV_STATE_ENUM_U8           enSmsMO;
    AT_MSG_SERV_STATE_ENUM_U8           enSmsBM;
}AT_MSG_SERV_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define AT_MAX_TIMEZONE_VALUE                               48

#define At_GetNumTypeFromAddrType(enNumType, ucAddrType) ((enNumType) = ((ucAddrType >> 4) & 0x07))
#define At_GetNumPlanFromAddrType(enNumPlan, ucAddrType) ((enNumPlan) = (ucAddrType & 0x0f))

#define AT_MSG_TP_MTI_DELIVER                               0x00                /* SMS-DELIVER       */
#define AT_MSG_TP_MTI_DELIVER_REPORT                        0x00                /* SMS-DELIVER-REPORT*/
#define AT_MSG_TP_MTI_STATUS_REPORT                         0x02                /* SMS-STATUS-REPORT */
#define AT_MSG_TP_MTI_COMMAND                               0x02                /* SMS-COMMAND       */
#define AT_MSG_TP_MTI_SUBMIT                                0x01                /* SMS-SUBMIT        */
#define AT_MSG_TP_MTI_SUBMIT_REPORT                         0x01                /* SMS-SUBMIT-REPORT */
#define AT_MSG_TP_MTI_RESERVE                               0x03                /* RESERVE           */

/*23040 9.2.3.1 bits no 0 and 1 of the first octet of all PDUs*/
#define AT_GET_MSG_TP_MTI(ucMti, ucFo)                         ((ucMti) = ((ucFo) & AT_MSG_TP_MTI_MASK))

#define AT_GET_MSG_TP_RD(bFlag, ucFo)                          ((bFlag) = ((ucFo) & 0x04) ? TAF_TRUE : TAF_FALSE)
/*23040 9.2.3.2 bit no 2 of the first octet of SMS DELIVER and SMS STATUS REPORT*/
#define AT_GET_MSG_TP_MMS(bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x04) ? TAF_FALSE : TAF_TRUE)

/*23040 9.2.3.26 bit no. 5 of the first octet of SMS STATUS REPORT*/
#define AT_GET_MSG_TP_SRQ(bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x20) ? TAF_TRUE : TAF_FALSE)

/*23040 9.2.3.4 bit no. 5 of the first octet of SMS DELIVER*/
#define AT_GET_MSG_TP_SRI( bFlag, ucFo)                        ((bFlag) = ((ucFo) & 0x20) ? TAF_TRUE : TAF_FALSE)

/*23040 9.2.3.5 bit no. 5 of the first octet of SMS SUBMIT and SMS COMMAND*/
#define AT_GET_MSG_TP_SRR( bFlag, ucFo)                        ((bFlag) = ((ucFo) & 0x20) ? TAF_TRUE : TAF_FALSE)

#define AT_GET_MSG_TP_UDHI( bFlag, ucFo)                       ((bFlag) = ((ucFo) & 0x40) ? TAF_TRUE : TAF_FALSE)

#define AT_GET_MSG_TP_RP( bFlag, ucFo)                         ((bFlag) = ((ucFo) & 0x80) ? TAF_TRUE : TAF_FALSE)


/*23040 9.2.3.1 bits no 0 and 1 of the first octet of all PDUs*/
#define AT_SET_MSG_TP_MTI(ucFo, ucMti)                         ((ucFo) |= ((ucMti) & 0x03))
/*23040 9.2.3.25  1 bit field located within bit 2 of the first octet of SMS SUBMIT*/
#define AT_SET_MSG_TP_RD(ucFo, bFlag)                          ((ucFo) |= (TAF_TRUE == (bFlag)) ? 0x04 : 0)
/*23040 9.2.3.2 bit no 2 of the first octet of SMS DELIVER and SMS STATUS REPORT*/
#define AT_SET_MSG_TP_MMS(ucFo, bFlag)                         ((ucFo) |= (TAF_TRUE == (bFlag)) ? 0 : 0x04)
/*23040 9.2.3.3 bit no 3 and 4 of the first octet of SMS SUBMIT*/
#define AT_SET_MSG_TP_VPF(ucFo, ucVpf)                         ((ucFo) |= (((ucVpf) << 3) & 0x18))
/*23040 9.2.3.26 bit no. 5 of the first octet of SMS STATUS REPORT*/
#define AT_SET_MSG_TP_SRQ(ucFo, bFlag)                         ((ucFo) |= (TAF_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.4 bit no. 5 of the first octet of SMS DELIVER*/
#define AT_SET_MSG_TP_SRI(ucFo, bFlag)                         ((ucFo) |= (TAF_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.5 bit no. 5 of the first octet of SMS SUBMIT and SMS COMMAND*/
#define AT_SET_MSG_TP_SRR(ucFo, bFlag)                         ((ucFo) |= (TAF_TRUE == (bFlag)) ? 0x20 : 0)
/*23040 9.2.3.23 1 bit field within bit 6 of the first octet of SMS SUBMIT SMS-SUBMIT-REPORT SMS DELIVER,SMS-DELIVER-REPORT SMS-STATUS-REPORT SMS-COMMAND.*/
#define AT_SET_MSG_TP_UDHI(ucFo, bFlag)                        ((ucFo) |= (TAF_TRUE == (bFlag))? 0x40 : 0)
/*23040 9.2.3.17 1 bit field, located within bit no 7 of the first octet of both SMS DELIVER and SMS SUBMIT,*/
#define AT_SET_MSG_TP_RP(ucFo, bFlag)                          ((ucFo) |= (TAF_TRUE == (bFlag))? 0x80 : 0)

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : At_SendDomainProtoToNvim
 ��������  : Э���еķ������ֵת��ΪNVIM�з������ֵ
 �������  :
 �������  : ��
 �� �� ֵ  : ת����ķ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��3��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SendDomainProtoToNvim(
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        enProtoSendDomain
);

/*****************************************************************************
 Prototype      : At_CheckEnd
 Description    : �Ƚϡ�ƥ�������
 Input          : Char---������ַ�
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
extern VOS_UINT32 At_CheckEnd( VOS_UINT8 Char );

/*****************************************************************************
 Prototype      : At_CheckJuncture
 Description    : �Ƚϡ�ƥ�����ӷ�
 Input          : Char---������ַ�
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
extern VOS_UINT32 At_CheckJuncture( VOS_UINT8 Char );

/*****************************************************************************
 �� �� ��  : At_ParseCsmpFo
 ��������  : AT����CSMP��FO�����Ľ���
 �������  : ��
 �������  : pucFo  - FO����ָ��
 �� �� ֵ  : AT_SUCCESS - �����ɹ�
             ����       - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��4��1��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
extern VOS_UINT32 At_ParseCsmpFo(
    VOS_UINT8                           *pucFo
);

/*****************************************************************************
 �� �� ��  : At_ParseCsmpVp
 ��������  : AT����CSMP��VP�����Ľ���
 �������  : ��
 �������  : pstVp      - VP����ָ��
 �� �� ֵ  : AT_SUCCESS - �����ɹ�
             ����       - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��4��1��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_ParseCsmpVp(
    VOS_UINT8                           ucIndex,
    MN_MSG_VALID_PERIOD_STRU           *pstVp
);

VOS_UINT32  AT_AsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
);

VOS_UINT32  AT_BcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
);

#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif  /* __ATMSGPRINT_H__ */

#endif /* end of AtSmsPrint.h */
