
#ifndef _ATDEVICECMD_H_
#define _ATDEVICECMD_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_typdef.h"
#include "ATCmdProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*����ʹ�õļ��ܽṹ*/

/* WIFI KEY�ַ������ȣ���NVIMģ��Ipcom_parameters_handle.h�ļ��� NV_WLKEY_LEN ����һ�� */
#define AT_NV_WLKEY_LEN                 (27)

/* ��Ȩģʽ�ַ������ȣ���NVIMģ��Ipcom_parameters_handle.h�ļ��� NV_WLAUTHMODE_LEN ����һ�� */
#define AT_NV_WLAUTHMODE_LEN            (16)

/* ����ģʽ�ַ������ȣ���NVIMģ��Ipcom_parameters_handle.h�ļ��� NV_ENCRYPTIONMODES_LEN ����һ�� */
#define AT_NV_ENCRYPTIONMODES_LEN       (5)

/* WPA�������ַ������ȣ���NVIMģ��Ipcom_parameters_handle.h�ļ��� NV_WLWPAPSK_LEN ����һ�� */
#define AT_NV_WLWPAPSK_LEN              (65)

/* NV��50012�����ݽṹnv_wifisec_type WIFI KEY��������ݳ��� */
#define AT_NV_WIFISEC_OTHERDATA_LEN     (72)

/* �����֧�ֵ�WIFI KEY���� */
#define AT_WIWEP_CARD_WIFI_KEY_TOTAL    (4)

/* ��λ��֧�ֵ�WIFI KEY���� */
#define AT_WIWEP_TOOLS_WIFI_KEY_TOTAL   (16)

/* PHYNUM�������������MAC������ų��� */
#define AT_PHYNUM_MAC_LEN               (12)

/* PHYNUM�������������MAC���������^WIFIGLOBAL����ƥ����Ҫ���ӵ�ð�Ÿ��� */
#define AT_PHYNUM_MAC_COLON_NUM         (5)

#define AT_TSELRF_PATH_TOTAL            (4)

#define AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS   (2)                             /* MAC��ַ��ð��֮����ַ�����*/


#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
#define AT_TDS_SCALIB_STR (VOS_UINT8 *)"(\"CACHE\",\"USE\",\"SAVE\",\"GET\",\"READ\",\"INI\",\"BEGIN\",\"END\",\"SET\",\"\"),(\"APCOFFSETFLAG\",\"APCOFFSET\",\"APC\",\"APCFREQ\",\"AGC\",\"AGCFREQ\",\"\"),(1,5,6),(@pram)"
#define AT_TDS_SCALIB_TEST_STR "(CACHE,USE,SAVE,GET,READ,INI,BEGIN,END,SET),(APCOFFSETFLAG,APCOFFSET,APC,APCFREQ,AGC,AGCFREQ),(1,5,6),(DATA)"
#endif

#define BAND_WIDTH_NUMS 6

#define UIMID_DATA_LEN                              (4)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : AT_TBAT_OPERATION_TYPE_ENUM
 �ṹ˵��  : ^TBAT�Ĳ�����Ŀ
             AT_TBAT_BATTERY_ANALOG_VOLTAGE         ���ģ���ѹ
             AT_TBAT_BATTERY_DIGITAL_VOLTAGE        ������ֵ�ѹ
             AT_TBAT_BATTERY_VOLUME                 ��ص���
  1.��    ��   : 2012��01��02��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
enum AT_TBAT_OPERATION_TYPE_ENUM
{
    AT_TBAT_BATTERY_ANALOG_VOLTAGE      = 0,
    AT_TBAT_BATTERY_DIGITAL_VOLTAGE     = 1,
    AT_TBAT_BATTERY_VOLUME              = 2,
    AT_TBAT_OPERATION_TYPE_BUTT
};
typedef VOS_UINT32  AT_TBAT_OPERATION_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_TBAT_OPERATION_DIRECTION_ENUM
 �ṹ˵��  : ^TBAT�Ĳ��Է���
            AT_TBAT_READ_FROM_UUT   �ӵ����(UUT)��ȡ
            AT_TBAT_SET_TO_UUT      ���õ������(UUT)
  1.��    ��   : 2012��01��02��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
enum AT_TBAT_OPERATION_DIRECTION_ENUM
{
    AT_TBAT_READ_FROM_UUT,
    AT_TBAT_SET_TO_UUT,
    AT_TBAT_OPERATION_DIRECTION_BUTT
};
typedef VOS_UINT32  AT_TBAT_OPERATION_DIRECTION_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_TSELRF_PATH_ENUM
 �ṹ˵��  : ^TSELRF����Ƶͨ·���
             AT_TSELRF_PATH_GSM       GSMͨ·������EDGE/GPRS/EGSM�ȵ�ȫ����
             AT_TSELRF_PATH_WCDMA_PRI WCDMA����
             AT_TSELRF_PATH_WCDMA_DIV WCDMA�ּ�
             AT_TSELRF_PATH_WIFI      WiFiͨ·
  1.��    ��   : 2012��01��02��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
enum AT_TSELRF_PATH_ENUM
{
    AT_TSELRF_PATH_GSM                  = 1,
    AT_TSELRF_PATH_WCDMA_PRI            = 2,
    AT_TSELRF_PATH_WCDMA_DIV            = 3,
    AT_TSELRF_PATH_TD					= 6,
    AT_TSELRF_PATH_WIFI                 = 7,
    AT_TSELRF_PATH_BUTT
};
typedef VOS_UINT32  AT_TSELRF_PATH_ENUM_UINT32;


/*****************************************************************************
 ö����    : AT_KEY_TYPE_ENUM
 �ṹ˵��  : ^SETKEY,^GETKEYINFO��ö������
             AT_KEY_TYPE_DIEID      ���ͨ��Ʒdieid������ö��
             AT_KEY_TYPE_TBOX_SMS   T-BOX��Ʒ���żӽ��ܣ�����ö��
             AT_KEY_TYPE_SOCID      оƬSOC ID��256bit
             AT_KEY_TYPE_AUTHKEY    оƬDFT���룬64bit������д��efuse
  1.��    ��   : 2016��04��14��
    ��    ��   : w00249971
    �޸�����   : ����
*****************************************************************************/
enum AT_KEY_TYPE_ENUM
{
    AT_KEY_TYPE_DIEID      = 1,
    AT_KEY_TYPE_TBOX_SMS   = 2,
    AT_KEY_TYPE_SOCID      = 3,
    AT_KEY_TYPE_AUTHKEY    = 4,
    AT_KEY_TYPE_BUTT
};

enum AT_SECURE_STATE_ENUM
{
    AT_NOT_SET_STATE            = 0,     /*δ����оƬģʽ��״̬*/
    AT_NO_DX_SECU_DISABLE_STATE = 0,     /*��DX��������ǰ�ȫģʽ��״̬*/
    AT_NO_DX_SECU_ENABLE_STATE  = 1,     /*��DX�������氲ȫģʽ��״̬*/
    AT_DX_RMA_STATE             = 2,     /*����DX��������ǰ�ȫģʽ��״̬*/
    AT_DX_SECURE_STATE          = 3,     /*����DX�������氲ȫģʽ��״̬*/
    AT_SECURE_STATE_BUTT
};

enum AT_DRV_RETURN_STATE_ENUM
{
    AT_DRV_NOT_SETTED_STATE = 0,         /*δ����оƬ״̬*/
    AT_DRV_STATE_SECURE     = 1,         /*��ȫ״̬*/
    AT_DRV_STATE_RMA        = 2,         /*�ǰ�ȫ״̬*/
    AT_DRV_STATE_BUTT
};

enum AT_SET_STATE_ENUM
{
    AT_SET_SECURE_STATE = 1,             /*����Ϊ��ȫ״̬*/
    AT_SET_RMA_STATE    = 2,             /*����Ϊ�ǰ�ȫ״̬*/
    AT_SET_STATE_BUTT
};

#define AT_AUTHKEY_LEN                  (8)     /* 64 Bits��AUTH KEY ��������*/
#define AT_KCE_LEN                      (16)    /* 128bit KCE�ӽ���keyֵ���� */
#define AT_SOCID_LEN                    (32)    /* 256Bits��SOCID�������� */
#define AT_KEY_HASH_LEN                 (32)    /* SOCID����AUTHKEY��hashֵ���� */
#define AT_KEYBUFF_LEN                  (32)

#define AT_SECUREDEBUG_VALUE            (3)     /* ���ð�ȫDEBUG��Ȩ�ɰ�ȫ֤�����*/
#define AT_SECDBGRESET_VALUE            (1)     /* �԰�ȫ�����Coresight ����ʱ����ʱ��λSecEngine*/
#define AT_CSRESET_VALUE                (1)     /* �԰�ȫ�����Coresight ����ʱ����ʱ��λSecEngine*/
#define AT_DFTSEL_VALUE                 (1)     /* ����ͨ��������֤��ʽ������ȫDFT����*/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/* ���� g_stATDislogPwd �е� DIAG�ڵ�״̬Ҫ���뱸��NV�б�; �����벻�ñ���
   �ʽ� g_stATDislogPwd �е��������, ��ʹ�����е� DIAG ��״̬;
   ���¶���NV��������������  */
extern VOS_INT8                         g_acATOpwordPwd[AT_OPWORD_PWD_LEN+1];


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
 �ṹ��    : AT_TBAT_BATTERY_ADC_INFO_STRU
 �ṹ˵��  : ^TBAT�������õ��У׼���������ݽṹ

  1.��    ��   : 2012��01��02��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMinAdc;
    VOS_UINT16                          usMaxAdc;
}AT_TBAT_BATTERY_ADC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : AT_WIFISEC_WIWEP_INFO_STRU
 �ṹ˵��  : WIWEP�����������: WIFI KEY�����ݽṹ
             ucwlKeys������Ϊ�ַ����ͣ����ַ���������'\0'��Ϊ���ݽ���
  1.��    ��   : 2012��01��02��
    ��    ��   : f62575
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucwlKeys[AT_NV_WLKEY_LEN];
}AT_WIFISEC_WIWEP_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 At_SetSecuBootPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QrySecuBootFeaturePara( VOS_UINT8 ucIndex );
VOS_UINT32 At_SetKeyPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_GetKeyInfoPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetTbatPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryTbatPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetPstandbyPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetWiwepPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryWiwepPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_TestWiwepPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_SetCmdlenPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryCmdlenPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_UpdateMacPara(
    VOS_UINT8                           aucMac[],
    VOS_UINT16                          usMacLength
);

VOS_UINT32 AT_SetTmodeAutoPowerOff(VOS_UINT8 ucIndex);

VOS_UINT32 AT_SetTseLrfPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryTseLrfPara(VOS_UINT8 ucIndex);

VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[]);

VOS_UINT32 AT_ExistSpecificPort(VOS_UINT8 ucPortType);

VOS_UINT32 AT_OpenDiagPort(VOS_VOID);
VOS_UINT32 AT_CloseDiagPort(VOS_VOID);
VOS_UINT32 AT_CheckSetPortRight(
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
);

VOS_UINT32 AT_TestHsicCmdPara(VOS_UINT8 ucIndex);

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 At_TestTdsScalibPara(VOS_UINT8 ucIndex);
#endif

VOS_UINT32 AT_TestSimlockUnlockPara( VOS_UINT8 ucIndex );

VOS_UINT32 AT_SetNVReadPara(VOS_UINT8 ucClientId);
VOS_UINT32 AT_SetNVWritePara(VOS_UINT8 ucClientId);

VOS_UINT32 AT_QryFPllStatusPara(VOS_UINT8 ucIndex);
VOS_VOID At_RfPllStatusCnfProc(PHY_AT_RF_PLL_STATUS_CNF_STRU *pstMsg);

VOS_UINT32 AT_QryFpowdetTPara(VOS_UINT8 ucIndex);
VOS_VOID At_RfFpowdetTCnfProc(PHY_AT_POWER_DET_CNF_STRU *pstMsg);

VOS_UINT32 AT_NVWRGetParaInfo( AT_PARSE_PARA_TYPE_STRU * pstPara, VOS_UINT8 * pu8Data, VOS_UINT32 * pulLen);


VOS_UINT32 AT_SetNvwrSecCtrlPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaNvwrSecCtrlSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_QryNvwrSecCtrlPara(VOS_UINT8 ucIndex);
VOS_BOOL AT_IsNVWRAllowedNvId(VOS_UINT16 usNvId);

extern VOS_UINT32 AT_AsciiToHex(
    VOS_UINT8                          *pucSrc,
    VOS_UINT8                          *pucDst
);

extern VOS_UINT32 AT_AsciiToHexCode_Revers(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDst
);

extern VOS_UINT32 AT_Hex2Ascii_Revers(
    VOS_UINT8                           aucHex[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32 AT_SetMeidPara(VOS_UINT8 ucIndex);

extern VOS_UINT32 AT_QryMeidPara(VOS_UINT8 ucIndex);
#endif

extern VOS_UINT32 AT_SetMipiWrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetMipiRdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSSIWrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSSIRdPara(VOS_UINT8 ucIndex);

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

#endif /* end of AtDeviceCmd.h */
