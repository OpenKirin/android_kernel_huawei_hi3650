

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"

#include "PppInterface.h"
#include "AtUsbComItf.h"
#include "AtInputProc.h"
#include "AtCsdInterface.h"
#include "AtTafAgentInterface.h"
#include "TafAgentInterface.h"
#include "cpm.h"
#include "AtCmdMsgProc.h"
#include "AtDataProc.h"
#include "ImmInterface.h"
#include "mdrv.h"

#include "AtMntn.h"
#include "AcpuReset.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

#include "AtInternalMsg.h"
#include  "product_config.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_INPUTPROC_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
VOS_UINT32                              g_ulAtUsbDebugFlag = VOS_FALSE;

/*****************************************************************************
 ȫ�ֱ�����   : g_astAtHsicCtx
 ȫ�ֱ������� : HSIC ATͨ��������
                ���������ע������н��պ������ͷŻص������У���ڲ�������ͨ��������
                �޷��������ĸ�ͨ���������ݣ����Զ�ÿһ��HSIC ATͨ�������ṩһ������
                ���ռ������ͷŻص����Դ������ֲ�ͬ��ͨ��

1. ��    ��   : 2012��2��24��
   ��    ��   : L47619
   �޸�����   : �����ṹ��
2. ��    ��   : 2012��6��28��
   ��    ��   : L47619
   �޸�����   : ����UDI_ACM_HSIC_ACM10_ID��HSICͨ��4��������
3. ��    ��   : 2012��8��30��
   ��    ��   : l00198894
   �޸�����   : �޸�UDI_ACM_HSIC_ACM10_IDΪUDI_ACM_HSIC_ACM12_ID

*****************************************************************************/

/* AT/DIAGͨ������·���� */
VOS_UINT8                               gucOmDiagIndex    = AT_MAX_CLIENT_NUM;

/* USB NCM��UDI��� */
UDI_HANDLE                              g_ulAtUdiNdisHdl  = UDI_INVALID_HANDLE;

/* �ñ���Ŀǰֻ����USB-MODEM, HSIC-MODEM��HS-UART�ľ����������Ҫ�����Ҫ��PL���� */
UDI_HANDLE                              g_alAtUdiHandle[AT_CLIENT_BUTT] = {UDI_INVALID_HANDLE};

/* AT֡�ṹ��DRV ֵ֮��Ķ�Ӧ��ϵ */
AT_UART_FORMAT_PARAM_STRU               g_astAtUartFormatTab[] =
{
    /* auto detect (not support) */

    /* 8 data 2 stop */
    {AT_UART_FORMAT_8DATA_2STOP,            AT_UART_DATA_LEN_8_BIT,
     AT_UART_STOP_LEN_2_BIT,                AT_UART_PARITY_LEN_0_BIT},

    /* 8 data 1 parity 1 stop*/
    {AT_UART_FORMAT_8DATA_1PARITY_1STOP,    AT_UART_DATA_LEN_8_BIT,
     AT_UART_STOP_LEN_1_BIT,                AT_UART_PARITY_LEN_1_BIT},

    /* 8 data 1 stop */
    {AT_UART_FORMAT_8DATA_1STOP,            AT_UART_DATA_LEN_8_BIT,
     AT_UART_STOP_LEN_1_BIT,                AT_UART_PARITY_LEN_0_BIT},

    /* 7 data 2 stop */
    {AT_UART_FORMAT_7DATA_2STOP,            AT_UART_DATA_LEN_7_BIT,
     AT_UART_STOP_LEN_2_BIT,                AT_UART_PARITY_LEN_0_BIT},

    /* 7 data 1 parity 1 stop */
    {AT_UART_FORMAT_7DATA_1PARITY_1STOP,    AT_UART_DATA_LEN_7_BIT,
     AT_UART_STOP_LEN_1_BIT,                AT_UART_PARITY_LEN_1_BIT},

    /* 7 data 1 stop */
    {AT_UART_FORMAT_7DATA_1STOP,            AT_UART_DATA_LEN_7_BIT,
     AT_UART_STOP_LEN_1_BIT,                AT_UART_PARITY_LEN_0_BIT}
};


/*****************************************************************************
   3 ��������������
*****************************************************************************/

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : AT_GetAtMsgStruMsgLength
 ��������  : ��ȡ�ṹΪAT_MSG_STRU����Ϣ���ȣ���Ϊ������Ϣ�ڴ��ĳ�������
 �������  : VOS_UINT32 ulInfoLength   ��Ϣ����Ϣ�ֶγ��ȣ����ṹAT_MSG_STRU��usLen��¼�ĳ���
             VOS_UINT32 *pulMsgLength  �ṹΪAT_MSG_STRU����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��22��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���, DTS2011041502672

*****************************************************************************/
VOS_VOID AT_GetAtMsgStruMsgLength(
    VOS_UINT32                          ulInfoLength,
    VOS_UINT32                         *pulMsgLength
)
{
    if (ulInfoLength > 4)
    {
        *pulMsgLength = (sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH)
                      + (ulInfoLength - 4);
    }
    else
    {
        *pulMsgLength = sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetUserTypeFromIndex
 ��������  : ͨ���˿ڿͻ�������ȡע��ö˿ڵĿͻ�����
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pucUserType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��22��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���, DTS2011041502672

*****************************************************************************/
VOS_VOID AT_GetUserTypeFromIndex(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucUserType
)
{
    if (ucIndex < AT_MAX_CLIENT_NUM)
    {
        *pucUserType    = gastAtClientTab[ucIndex].UserType;
    }
    else
    {
        *pucUserType    = AT_BUTT_USER;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_VcomCmdStreamEcho
 ��������  : Vcom AT�ڵĻ��Դ���
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��5��
    ��    ��   : l00227485
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID AT_VcomCmdStreamEcho(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    /* E5��̬������� */
    /* AGPSͨ��������� */
    if ( (SYSTEM_APP_WEBUI != *pucSystemAppConfig)
      && (AT_CLIENT_TAB_APP9_INDEX != ucIndex)
      && (AT_CLIENT_TAB_APP12_INDEX != ucIndex)
      && (AT_CLIENT_TAB_APP24_INDEX != ucIndex)
    )
    {
        APP_VCOM_Send(gastAtClientTab[ucIndex].ucPortNo, pData, usLen);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetAts3Value
 ��������  : �ڵ���ģʽ������ATS3��ֵ
 �������  : VOS_UINT8 ucValue
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��10��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetAts3Value(VOS_UINT8 ucValue)
{
    if (VOS_TRUE == g_ulAtUsbDebugFlag)
    {
        ucAtS3 = ucValue;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CmdStreamEcho
 ��������  : ATͨ���������
 �������  : VOS_UINT8         ucIndex
             VOS_UINT8*        pData
             VOS_UINT16        usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_CmdStreamEcho(
    VOS_UINT8                           ucIndex,
    VOS_UINT8*                          pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulMuxUserFlg;
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT16                          usEchoLen;

    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);

    /* �ж�pData�����Ľ�β�Ƿ�Ϊ<CR><LF>��ʽ��������2Ϊ�س����������ַ����� */
    if ((usLen > 2) && (ucAtS3 == pData[usLen - 2]) && (ucAtS4 == pData[usLen - 1]))
    {
        /* ɾȥ��β��<LF>�ַ� */
        usEchoLen = usLen - 1;
    }
    else
    {
        usEchoLen = usLen;
    }

    if(AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        /*��USB COM�ڷ�������*/
        DMS_COM_SEND(AT_USB_COM_PORT_NO, pData, usEchoLen);
        AT_MNTN_TraceCmdResult(ucIndex, pData, usEchoLen);
    }
    else if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        DMS_COM_SEND(AT_CTR_PORT_NO, pData, usEchoLen);
        AT_MNTN_TraceCmdResult(ucIndex, pData, usEchoLen);
    }
    else if(AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
    {
        /*��PCUI2�ڷ�������*/
        DMS_COM_SEND(AT_PCUI2_PORT_NO, pData, usEchoLen);
        AT_MNTN_TraceCmdResult(ucIndex, pData, usEchoLen);
    }
    else if (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
    {
        AT_SendDataToModem(ucIndex, pData, usEchoLen);
    }
    else if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* VCOM AT�ڵĻ��Դ��� */
        AT_VcomCmdStreamEcho(ucIndex, pData, usEchoLen);
    }
    else if (AT_SOCK_USER == gastAtClientTab[ucIndex].UserType)
    {
        if ( BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
        {
            CPM_ComSend(CPM_AT_COMM, pData, VOS_NULL_PTR, usEchoLen);
        }
    }
    else if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* NDIS AT��������� */
        AT_WARN_LOG("AT_CmdStreamEcho:WARNING: NDIS AT");
    }
    else if (VOS_TRUE == ulHsicUserFlg)
    {
/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  Begin */
/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  End */
    }
    else if (VOS_TRUE == ulMuxUserFlg)
    {
        /* MUX user */
        AT_MuxCmdStreamEcho(ucIndex, pData, usEchoLen);
    }
    else
    {
        AT_LOG1("AT_CmdStreamEcho:WARNING: Abnormal UserType,ucIndex:",ucIndex);
    }

    return;
}

/*****************************************************************************
 Prototype      : At_CmdStreamPreProc
 Description    :
 Input          : ucChar --- �ַ�
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  3.��    �� : 2010-07-09
    ��    �� : S62952
    �޸����� : ���ⵥ��:DTS2010071000707
  4.��    �� : 2010-08-05
    ��    �� : S62952
    �޸����� : ���ⵥ��:DTS2010080401112
  5.��    �� : 2010-12-23
    ��    �� : S62952
    �޸����� : ���ⵥ��:DTS2010122002081,E5���Թر�
  6.��    �� : 2011��02��24��
    ��    �� : A00165503
    �޸����� : ���ⵥ��: DTS2011022404828��MODEM���·�AT������ؽ��������
  7.��    ��   : 2011��10��3��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ֱ�ӵ���DRV/DMS��˿ڷ�������
  8.��    ��   : 2011��10��19��
    ��    ��   : S62952
    �޸�����   : AT Project: �޸�modem�ڷ�ʽ�ӿ�
  9.��    ��   : 2012��2��24��
    ��    ��   : L47619
    �޸�����   : V7R1C50 IPC��Ŀ:����HSIC ATͨ��������Ե��߼�
 10.��    ��   : 2012��5��29��
    ��    ��   : f62575
    �޸�����   : DTS2012052902986��ɾ���������Ķ�λ��Ϣ
 11.��    ��   : 2012��8��6��
    ��    ��   : l60609
    �޸�����   : MUX������muxͨ������
 12.��    ��   : 2012��11��28��
    ��    ��   : l00227485
    �޸�����   : DSDA:����VCOM ATͨ��������Ե��߼�
 13.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
 14.��    ��   : 2014��4��22��
    ��    ��   : A00165503
    �޸�����   : DTS2014042208020: ȥ��APPVCOM9��APPVCOM12�������ϱ�����
 15.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 At_CmdStreamPreProc(VOS_UINT8 ucIndex, VOS_UINT8* pData, VOS_UINT16 usLen)
{
    VOS_UINT8                          *pHead = TAF_NULL_PTR;
    VOS_UINT16                          usCount = 0;
    VOS_UINT16                          usTotal = 0;

    pHead = pData;

    if (VOS_TRUE == g_ulAtUsbDebugFlag)
    {
        (VOS_VOID)vos_printf("At_CmdStreamPreProc: AtEType = %d, UserType = %d, ucAtS3 = %d\r\n",
                   gucAtEType, gastAtClientTab[ucIndex].UserType, ucAtS3);
    }

    /* ����ͨ������ */
    if( AT_E_ECHO_CMD == gucAtEType )
    {
        AT_CmdStreamEcho(ucIndex, pData, usLen);
    }

    /* MACϵͳ�ϵ�MP��̨����:AT+CMGS=**<CR><^z><Z>(��AT+CMGW=**<CR><^z><Z>)
       Ϊ�˹�ܸ����⣬��Ҫ�ڽ��յ�������ʽ��������
       ��Ҫ����������Ч�ַ�<^z><Z>ɾȥ */
    AT_DiscardInvalidCharForSms(pData, &usLen);

    /* �����������ַ��Ž���������Ϣ��ʽ���͵�AT����Ϣ������: <CR>/<ctrl-z>/<ESC> */
    while(usCount++ < usLen)
    {
        /*lint -e960 Note -- Violates MISRA 2004 Required Rule 4.1, Prohibited escape sequence used (hexadecimal)*/
        if (At_CheckSplitChar((*((pData + usCount) - 1))))
        /*lint +e960*/
        {
            if(g_aucAtDataBuff[ucIndex].ulBuffLen > 0)
            {
                if((g_aucAtDataBuff[ucIndex].ulBuffLen + usCount) >= AT_COM_BUFF_LEN)
                {
                    g_aucAtDataBuff[ucIndex].ulBuffLen = 0;
                    return AT_FAILURE;
                }
                PS_MEM_CPY(&g_aucAtDataBuff[ucIndex].aucDataBuff[g_aucAtDataBuff[ucIndex].ulBuffLen], pHead, usCount);
                At_SendCmdMsg(ucIndex,g_aucAtDataBuff[ucIndex].aucDataBuff, (TAF_UINT16)(g_aucAtDataBuff[ucIndex].ulBuffLen + usCount), 0);
                pHead   = pData + usCount;
                usTotal = usCount;
                g_aucAtDataBuff[ucIndex].ulBuffLen = 0;
            }
            else
            {
                At_SendCmdMsg(ucIndex, pHead, usCount - usTotal, AT_NORMAL_TYPE_MSG);
                pHead   = pData + usCount;
                usTotal = usCount;
            }
        }
    }

    if(usTotal < usLen)
    {
        if((g_aucAtDataBuff[ucIndex].ulBuffLen + (usLen - usTotal)) >= AT_COM_BUFF_LEN)
        {
            g_aucAtDataBuff[ucIndex].ulBuffLen = 0;
            return AT_FAILURE;
        }
        PS_MEM_CPY(&g_aucAtDataBuff[ucIndex].aucDataBuff[g_aucAtDataBuff[ucIndex].ulBuffLen], pHead, (TAF_UINT32)(usLen - usTotal));
        g_aucAtDataBuff[ucIndex].ulBuffLen += (VOS_UINT16)((pData - pHead) + usLen);
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : AT_StopFlowCtrl
 Description    : AT��������
 Input          : ucIndex
 Output         : ---
 Return Value   : VOS_VOID

 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-09-25
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �޸Ĺܽ��ź����ú���
*****************************************************************************/
VOS_VOID AT_StopFlowCtrl(VOS_UINT8 ucIndex)
{
    switch (gastAtClientTab[ucIndex].UserType)
    {
        case AT_MODEM_USER:
            AT_MNTN_TraceStopFlowCtrl(ucIndex, AT_FC_DEVICE_TYPE_MODEM);
            AT_CtrlCTS(ucIndex, AT_IO_LEVEL_HIGH);
            break;

        case AT_HSUART_USER:
            AT_MNTN_TraceStopFlowCtrl(ucIndex, AT_FC_DEVICE_TYPE_HSUART);
            AT_CtrlCTS(ucIndex, AT_IO_LEVEL_HIGH);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : At_OmDataProc
 ��������  : ����OM�ṩ�ĸ��˿ڽ������ݺ����������ݣ�����Ҫ����������ģʽ
 �������  : VOS_UINT8                           ucPortNo
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 At_OmDataProc (
    VOS_UINT8                           ucPortNo,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          ulRst;

    /*OMֻ����UART PCUI CTRL�ڵ�����*/
    switch(ucPortNo)
    {
        case AT_UART_PORT_NO:
            if (VOS_NULL_PTR == g_apAtPortDataRcvFuncTab[AT_UART_PORT])
            {
                AT_ERR_LOG("At_OmDataProc: Uart port proc func is NULL!");
                return VOS_ERR;
            }

            ulRst = g_apAtPortDataRcvFuncTab[AT_UART_PORT](pData, usLen);
            break;

        case AT_USB_COM_PORT_NO:
            if (VOS_NULL_PTR == g_apAtPortDataRcvFuncTab[AT_PCUI_PORT])
            {
                AT_ERR_LOG("At_OmDataProc: PCUI proc func is NULL!");
                return VOS_ERR;
            }

            ulRst = g_apAtPortDataRcvFuncTab[AT_PCUI_PORT](pData, usLen);
            break;

        case AT_CTR_PORT_NO:
            if (VOS_NULL_PTR == g_apAtPortDataRcvFuncTab[AT_CTRL_PORT])
            {
                AT_ERR_LOG("At_OmDataProc: CTRL proc func is NULL!");
                return VOS_ERR;
            }

            ulRst = g_apAtPortDataRcvFuncTab[AT_CTRL_PORT](pData, usLen);
            break;

        case AT_PCUI2_PORT_NO:
            if (VOS_NULL_PTR == g_apAtPortDataRcvFuncTab[AT_PCUI2_PORT])
            {
                AT_ERR_LOG("At_OmDataProc: PCUI2 proc func is NULL!");
                return VOS_ERR;
            }

            ulRst = g_apAtPortDataRcvFuncTab[AT_PCUI2_PORT](pData, usLen);
            break;

        case AT_HSUART_PORT_NO:
            if (VOS_NULL_PTR == g_apAtPortDataRcvFuncTab[AT_HSUART_PORT])
            {
                AT_ERR_LOG("At_OmDataProc: HSUART proc func is NULL!");
                return VOS_ERR;
            }

            ulRst = g_apAtPortDataRcvFuncTab[AT_HSUART_PORT](pData, usLen);
            break;

        default:
            AT_WARN_LOG("At_OmDataProc: don't proc data of this port!");
            return VOS_ERR;
    }

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : At_DataStreamPreProc
 ��������  : AT����Ԥ������
 �������  : TAF_UINT8 ucIndex
             TAF_UINT8 DataMode
             TAF_UINT8* pData
             TAF_UINT16 usLen
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �޸�OM�Ľ������ݺ���

*****************************************************************************/
TAF_UINT32 At_DataStreamPreProc (TAF_UINT8 ucIndex,TAF_UINT8 DataMode,TAF_UINT8* pData, TAF_UINT16 usLen)
{

    AT_LOG1("At_DataStreamPreProc ucIndex:",ucIndex);
    AT_LOG1("At_DataStreamPreProc usLen:",usLen);
    AT_LOG1("At_DataStreamPreProc DataMode:",DataMode);

    switch(DataMode)    /* ��ǰ�û����������� */
    {
        case AT_CSD_DATA_MODE:
            break;

        /* Modified by L60609 for AT Project��2011-10-04,  Begin*/
        /*����OM�ṩ�ĸ��˿ڽ������ݺ����������ݣ�����Ҫ����������ģʽ*/
        case AT_DIAG_DATA_MODE:
        case AT_OM_DATA_MODE:
            At_OmDataProc(gastAtClientTab[ucIndex].ucPortNo, pData,usLen);
            break;
        /* Modified by L60609 for AT Project��2011-10-04,  End*/

        default:
            AT_WARN_LOG("At_DataStreamPreProc DataMode Wrong!");
            break;
    }
    return AT_SUCCESS;
}

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/*****************************************************************************
 �� �� ��  : AT_CsdDataModeRcvModemMsc
 ��������  : ������CS���ӵ绰������£��յ��ܽ��źź�Ҷϵ绰
 �������  : ucIndex -- �û�����
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��18��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��7��28��
    ��    ��   : z00161729
    �޸�����   : DTS2010082602962:�յ������ܽ��źű仯ָʾʱ�����ιҶϵ绰����
  3.��    ��   : 2011��10��24��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ,��VP����������
  3.��    ��   : 2011��12��28��
    ��    ��   : w00199382
    �޸�����   : PS�ں���Ŀ���ͬ��API
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32  AT_CsdDataModeRcvModemMsc(
    VOS_UINT8                           ucIndex
)
{
    /* Modified by w00199382 for PS Project��2011-12-06,  Begin*/
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM];
    VOS_UINT32                          i;
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT32                          ulRlst;


    PS_MEM_SET(astCallInfos, 0x00, sizeof(astCallInfos));


    /* ��ѯ��ǰ�ĺ���״̬��Ϣ�������VIDEO���͵ĺ��У���Ҷϸú��У�Ŀǰ���ڲ�����ڶ��VIDEO���У�
       ����ҵ�һ��VIDEO���͵ĺ���ִ����Ϻ󣬼����˳� */

    ulRlst          = TAF_AGENT_GetCallInfoReq(ucIndex, &ucNumOfCalls, astCallInfos);

    if(VOS_OK == ulRlst)
    {
        for (i = 0; i < ucNumOfCalls; i++)
        {
            if (MN_CALL_TYPE_VIDEO == astCallInfos[i].enCallType)
            {
                /* δ�ҶϹ��绰 */
                if (gastAtClientTab[ucIndex].CmdCurrentOpt != AT_CMD_END_SET)
                {
                    TAF_LOG1(WUEPS_PID_AT, 0, PS_LOG_LEVEL_INFO, "At_SetHPara: ulNumOfCalls is ",(TAF_INT32)ucNumOfCalls);

                    if(AT_SUCCESS == MN_CALL_End(gastAtClientTab[ucIndex].usClientId,
                                                 0,
                                                 astCallInfos[i].callId,
                                                 VOS_NULL_PTR))
                    {
                        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_END_SET;
                        return AT_SUCCESS;
                    }
                    else
                    {
                        return AT_ERROR;
                    }
                }
                else
                {
                    /* ֮ǰ�������Ҷϵ绰���������յ�����DTR�ܽ��ź���Ϣ���������� */
                    return AT_SUCCESS;
                }
            }
        }
    }

    /* Modified by w00199382 for PS Project��2011-12-06,  End*/

    return AT_CME_UNKNOWN;
}

/*****************************************************************************
 �� �� ��  : AT_PppDataModeRcvModemMsc
 ��������  : ������PPP���ŵ�����£��յ��ܽ��źź���ȥ����
 �������  : ucIndex -- �û�����
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��18��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT��ֲ��Ŀ, �޸ĶϿ����ŵĽӿ�
*****************************************************************************/
VOS_UINT32  AT_PppDataModeRcvModemMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                     *pMscStru
)
{
    /* 1.�ж�(AT_CMD_PS_DATA_CALL_END_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
         ��Ŀ��:�������Ͽ�����֮ǰ�Ѿ�ִ����PDP DEACTIVE���̣���ʱ��������DTR����
         ������ִ�и��쳣����
        2.�÷�֧�Ĵ�����:����������״̬��,�û�����PPP�Ͽ�����ʱPPP�����޷�������
          ֻ�����������DTR�źŵ�ʱ��ִ��PPP�Ͽ�����
    */
    if (pMscStru->OP_Dtr && (0 == pMscStru->ucDtr))
    {
        if ( (AT_CMD_PS_DATA_CALL_END_SET      == gastAtClientTab[ucIndex].CmdCurrentOpt)
          || (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
        {
            return AT_SUCCESS;
        }

        /* ����������״̬�£���PPP�Ͽ���Э�̱������޷�����UE��ģ�
           UEֻ����DTR�ź����͵�ʱ��,ִ��PPP���ŶϿ�����*/
        if (0 == (gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS))
        {
            AT_StopFlowCtrl((TAF_UINT8)ucIndex);
        }

        /*��PPP�����ͷ�PPP����*/
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_REQ);

        /*��PPP����HDLCȥʹ�ܲ���*/
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        /* ֹͣModem�ڵ�AT��ʱ���Լ�AT��·�ĵ�ǰ����ָʾ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /*EVENT - RCV Down DTR to Disconnect PPP in Abnormal procedure(PDP type:IP) ;index*/
        AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DTE_DOWN_DTR_RELEASE_PPP_IP_TYPE,
                        &ucIndex, sizeof(ucIndex));

        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                      0,
                                      gastAtClientTab[ucIndex].ucCid) )
        {
            /* ����ʱ�� */
            if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
            {
                AT_ERR_LOG("At_UsbModemStatusPreProc:ERROR:Start Timer");
                return AT_FAILURE;
            }

            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;
        }
        else
        {
            return AT_FAILURE;
        }
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_IpDataModeRcvModemMsc
 ��������  : ������IP���ŵ�������յ��ܽ��źź���ȥ����
 �������  : ucIndex -- �û�����
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��18��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT��ֲ��Ŀ, �޸ĶϿ����ŵĽӿ�
*****************************************************************************/
VOS_UINT32  AT_IpDataModeRcvModemMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                     *pMscStru
)
{
    if (pMscStru->OP_Dtr && (0 == pMscStru->ucDtr))
    {
        /*��ԭ�ȿ��������أ�����ֹͣ����*/
        if (0 == (gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS))
        {
            AT_StopFlowCtrl((TAF_UINT8)ucIndex);
        }

        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

        /*��PPP����HDLCȥʹ�ܲ���*/
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId, PPP_AT_CTRL_HDLC_DISABLE);

        /* ֹͣModem�ڵ�AT��ʱ���Լ�AT��·�ĵ�ǰ����ָʾ */
        AT_STOP_TIMER_CMD_READY(ucIndex);;

        /*EVENT - RCV Down DTR to Disconnect PPP in Abnormal procedure(PDP type:PPP) ;index*/
        AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DTE_DOWN_DTR_RELEASE_PPP_PPP_TYPE,
                        &ucIndex, sizeof(ucIndex));

        if ( VOS_OK == TAF_PS_CallEnd(WUEPS_PID_AT,
                                      AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                      0,
                                      gastAtClientTab[ucIndex].ucCid) )
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PS_DATA_CALL_END_SET;
            return AT_SUCCESS;
        }
        else
        {
            return AT_FAILURE;
        }
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_MODEM_ProcDtrChange
 ��������  : Modem DTR�ܽŴ���
 �������  : ucIndex   --- �˿�����
             pstDceMsc --- �ܽ��ź�(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_MODEM_ProcDtrChange(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    if (1 == pstDceMsc->ucDtr)
    {
        /*����DSR��CTS�ź�*/
        AT_CtrlDSR(ucIndex, AT_IO_LEVEL_HIGH);
        AT_StopFlowCtrl(ucIndex);
    }
    else
    {
        /* �ο�Qʵ�֣�DSR�ź����ϵ��һֱ��������״̬����ʹ�յ�DTRҲ������DSR��
           ͬʱ��PC������������һ�㲻������DTR�źţ����쳣�����лὫ֮���ͣ�
           ����UE���յ�DTR���� ��ʱ����Ҫ��DCD���� */
        if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
          && (AT_CSD_DATA_MODE == gastAtClientTab[ucIndex].DataMode) )
        {
            g_ucDtrDownFlag = VOS_TRUE;
        }

        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
    }

}

/*****************************************************************************
 �� �� ��  : AT_MODEM_WriteMscCmd
 ��������  : ��װMODEM�ܽ��ź�д�ӿ�
 �������  : ucIndex    - �˿�����
             pstDceMsc  - �ܽ��źŽṹ(�ɵ����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : AT_SUCCESS - �ɹ�
             AT_FAILURE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_MODEM_WriteMscCmd(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    UDI_HANDLE                          lUdiHandle;
    VOS_INT32                           lResult;

    /* ���UDI�����Ч�� */
    lUdiHandle = g_alAtUdiHandle[ucIndex];
    if (UDI_INVALID_HANDLE == lUdiHandle)
    {
        AT_ERR_LOG("AT_MODEM_WriteMscCmd: Invalid UDI handle!");
        return AT_FAILURE;
    }

    /* д�ܽ��ź� */
    lResult = mdrv_udi_ioctl(lUdiHandle, ACM_MODEM_IOCTL_MSC_WRITE_CMD, pstDceMsc);
    if (VOS_OK != lResult)
    {
        AT_ERR_LOG("AT_MODEM_WriteMscCmd: Write failed!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : AT_MODEM_StartFlowCtrl
 Description    : AT��������
 Input          :
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.��    ��   : 2007-09-25
    ��    ��   : L47619
    �޸�����   : Created function

  2.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ���޸��������

  3.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �޸Ĺܽ��ź����ú���
*****************************************************************************/
VOS_UINT32 AT_MODEM_StartFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < AT_MAX_CLIENT_NUM; ucIndex++)
    {
        if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
          && (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode) )
        {
            if ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
              || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
              || (AT_CSD_DATA_MODE == gastAtClientTab[ucIndex].DataMode) )
            {
                AT_MNTN_TraceStartFlowCtrl(ucIndex, AT_FC_DEVICE_TYPE_MODEM);
                AT_CtrlCTS(ucIndex, AT_IO_LEVEL_LOW);
            }
        }
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : AT_MODEM_StopFlowCtrl
 Description    : AT�������
 Input          :
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.��    ��   : 2007-09-25
    ��    ��   : L47619
    �޸�����   : Created function

  2.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ���޸��������

  3.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �޸Ĺܽ��ź����ú���
*****************************************************************************/
VOS_UINT32 AT_MODEM_StopFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
)
{
    VOS_UINT8                           ucIndex;

    for(ucIndex = 0; ucIndex < AT_MAX_CLIENT_NUM; ucIndex++)
    {
        if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
          && (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode) )
        {
            if ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
                || (AT_CSD_DATA_MODE == gastAtClientTab[ucIndex].DataMode) )
            {
                AT_MNTN_TraceStopFlowCtrl(ucIndex, AT_FC_DEVICE_TYPE_MODEM);
                AT_CtrlCTS(ucIndex, AT_IO_LEVEL_HIGH);
            }
        }
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : AT_ModemStatusPreProc
 Description    : �ܽ��ź�Ԥ����
 Input          : ucIndex    --- �˿�����
                  pMscStru   --- �ܽ��źŽṹ(�ɵ����߱�֤�ǿ�)
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-11-14
    Author      : s62952
    Modification: Created function

  3.��    ��   : 2010��12��29��
    ��    ��   : z00161729
    �޸�����   : ���ⵥDTS2010123000175:TME��̨���������Ҷϵ绰֮��������ǰ������ʾno number

  4.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����UART�˿�֧��

  5.��    ��   : 2013��12��20��
    ��    ��   : A00165503
    �޸�����   : DTS2013121910186: DTR�ź�����ʱ, ����online-cmdģʽ�ж�
*****************************************************************************/
VOS_UINT32 AT_ModemStatusPreProc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pMscStru
)
{

    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId;




    if (VOS_NULL_PTR == pMscStru)
    {
        return AT_FAILURE;
    }

    if (pMscStru->OP_Dtr)
    {
        enEventId = (0 != pMscStru->ucDtr) ?
                    NAS_OM_EVENT_DTE_UP_DTR : NAS_OM_EVENT_DTE_DOWN_DTR;

        AT_EventReport(WUEPS_PID_AT, enEventId, &ucIndex, sizeof(VOS_UINT8));

        if (VOS_TRUE == AT_CheckModemUser(ucIndex))
        {
            AT_MODEM_ProcDtrChange(ucIndex, pMscStru);
        }

    }

    /* ����ģʽ��ӦMSC���� */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      || (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode) )
    {
        switch (gastAtClientTab[ucIndex].DataMode)
        {
        case AT_CSD_DATA_MODE:
            if ((pMscStru->OP_Dtr) && (0 == pMscStru->ucDtr))
            {
                AT_CsdDataModeRcvModemMsc(ucIndex);
            }
            return AT_SUCCESS;

        case AT_PPP_DATA_MODE:
            return AT_PppDataModeRcvModemMsc(ucIndex, pMscStru);

        case AT_IP_DATA_MODE:
            return AT_IpDataModeRcvModemMsc(ucIndex, pMscStru);

        default:
            AT_WARN_LOG("At_UsbModemStatusPreProc: DataMode Wrong!");
            break;
        }
    }
    else
    {
         /* �п����ڻ�û������ʱ�����͹ܽ��źţ���ʱ����������״̬��
            Ŀǰ��˵ֻ��CSDģʽ�»������������ */
         if ((pMscStru->OP_Dtr) && (0 == pMscStru->ucDtr))
         {
             AT_CsdDataModeRcvModemMsc(ucIndex);
         }
    }

    return AT_SUCCESS;
}
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

/*****************************************************************************
 �� �� ��  : AT_ModemSetCtlStatus
 ��������  : ����ܽ��ź�
 �������  : pMscStru --- ָ��ܽ��źŵ�ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��22��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID AT_ModemSetCtlStatus(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pMscStru
)
{
    if (TAF_NULL_PTR == pMscStru)
    {
        return;
    }

    /*����dsr�ź�*/
    if ( pMscStru->OP_Dsr )
    {
        if ( 1 == pMscStru->ucDsr )
        {
            gastAtClientTab[ucIndex].ModemStatus |= IO_CTRL_DSR;
        }
        else
        {
            gastAtClientTab[ucIndex].ModemStatus &= ~IO_CTRL_DSR;
        }
    }

    /*����CTS�ź�*/
    if ( pMscStru->OP_Cts )
    {
        if ( 1 == pMscStru->ucCts )
        {
            gastAtClientTab[ucIndex].ModemStatus |= IO_CTRL_CTS;
        }
        else
        {
            gastAtClientTab[ucIndex].ModemStatus &= ~IO_CTRL_CTS;
        }
    }

    /*����RI�ź�*/
    if ( pMscStru->OP_Ri )
    {
        if ( 1 == pMscStru->ucRi )
        {
            gastAtClientTab[ucIndex].ModemStatus |= IO_CTRL_RI;
        }
        else
        {
            gastAtClientTab[ucIndex].ModemStatus &= ~IO_CTRL_RI;
        }
    }

    /*����DCD�ź�*/
    if ( pMscStru->OP_Dcd )
    {
        if ( 1 == pMscStru->ucDcd )
        {
            gastAtClientTab[ucIndex].ModemStatus |= IO_CTRL_DCD;
        }
        else
        {
            gastAtClientTab[ucIndex].ModemStatus &= ~IO_CTRL_DCD;
        }
    }

    /*����FC�ź�*/
    if ( pMscStru->OP_Fc )
    {
        if ( 1 == pMscStru->ucFc )
        {
            gastAtClientTab[ucIndex].ModemStatus |= IO_CTRL_FC;
        }
        else
        {
            gastAtClientTab[ucIndex].ModemStatus &= ~IO_CTRL_FC;
        }
    }

}

/*****************************************************************************
 �� �� ��  : AT_SetModemStatus
 ��������  : �ظ��ܽ��ź�
 �������  : ucIndex  --- ����
             pMscStru --- ָ��ܽ��źŵ�ָ��
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  3.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����UART�˿�֧��
*****************************************************************************/
VOS_UINT32 AT_SetModemStatus(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstMsc
)
{
    VOS_UINT32                          ulResult;

    if (VOS_NULL_PTR == pstMsc)
    {
        return AT_FAILURE;
    }

    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return AT_FAILURE;
    }

    /* ���±��عܽ��ź�*/
    AT_ModemSetCtlStatus(ucIndex, pstMsc);

    /* ����ܽ��źſ�ά�ɲ� */
    AT_MNTN_TraceOutputMsc(ucIndex, pstMsc);

    /* д��ܽ��źŲ��� */
    switch (gastAtClientTab[ucIndex].UserType)
    {
        case AT_MODEM_USER:
            ulResult = AT_MODEM_WriteMscCmd(ucIndex, pstMsc);
            break;


        default:
            ulResult = AT_SUCCESS;
            break;
    }

    return ulResult;
}

/* ɾ��At_SetModemStatusForFC����, ���ܺ�At_SetModemStatus�ظ� */

/*****************************************************************************
 �� �� ��  : At_ModemEst
 ��������  : Modem��·�Ľ���
 �������  : VOS_UINT8                           ucIndex
             AT_CLIENT_ID_ENUM_UINT16            usClientId
             VOS_UINT8                           ucPortType
             AT_USER_TYPE                        ucUserType
             VOS_UINT8                           ucDlci
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             AT_SUCCESS
             AT_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2007-11-14
    Author      : 62952
    Modification: Created function
  2.��    ��   : 2011��9��30��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id
  3.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 At_ModemEst (
    VOS_UINT8                           ucIndex,
    AT_CLIENT_ID_ENUM_UINT16            usClientId,
    VOS_UINT8                           ucPortNo
)
{

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = usClientId;
    gastAtClientTab[ucIndex].ucPortType      = ucPortNo;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    AT_LOG1("At_ModemEst ucIndex:",ucIndex);

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : At_ModemMscInd
 ��������  : Modem Msc Ind
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                           ucDlci
             AT_DCE_MSC_STRU                    *pMscStru
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2007-11-14
    Author      : s62952
    Modification: Created function
  2.��    ��   : 2011��10��17��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project
  3.��    ��   : 2013��05��22��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 At_ModemMscInd (
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucDlci,
    AT_DCE_MSC_STRU                    *pMscStru
)
{
    AT_PPP_MODEM_MSC_IND_MSG_STRU      *pMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT_PTR                        ulTmpAddr;

    ulLength = (sizeof(AT_PPP_MODEM_MSC_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH)
               + (sizeof(AT_DCE_MSC_STRU) - 2);

    pMsg = ( AT_PPP_MODEM_MSC_IND_MSG_STRU * )PS_ALLOC_MSG( PS_PID_APP_PPP, ulLength );
    if ( VOS_NULL_PTR == pMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        AT_WARN_LOG("At_ModemMscInd: Alloc AT_PPP_MODEM_MSC_IND_MSG_STRU msg fail!");
        return AT_FAILURE;
    }

    /*��д��Ϣͷ:*/
    pMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_AT;
    pMsg->MsgHeader.ulLength        = ulLength;
    pMsg->MsgHeader.ulMsgName       = AT_PPP_MODEM_MSC_IND_MSG;

    /*��д��Ϣ��*/
    pMsg->ucIndex                   = ucIndex;
    pMsg->ucDlci                    = ucDlci;

    /* ��д�ܽ����� */
    ulTmpAddr = (VOS_UINT_PTR)(pMsg->aucMscInd);

    PS_MEM_CPY((VOS_VOID *)ulTmpAddr, (VOS_UINT8 *)pMscStru, sizeof(AT_DCE_MSC_STRU));

    /* ������Ϣ */
    if ( VOS_OK != PS_SEND_MSG( PS_PID_APP_PPP, pMsg ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        AT_WARN_LOG( "At_ModemMscInd:WARNING:SEND AT_PPP_MODEM_MSC_IND_MSG_STRU msg FAIL!" );
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/******************************************************************************
�� �� ��  : AT_UsbModemGetUlDataBuf
��������  : ��ȡmodem�豸�������ݴ洢�ռ�
�������  :  ppstBuf    ----      ��������ָ��
�������  : ��
�� �� ֵ  : AT_SUCCESS ----      �ɹ���
            AT_FAILURE ----      ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��8��
    ��    ��   : ³��/l60609
    �޸�����   : Buf�����޸�ΪIMM_ZC_STRU
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2013��05��27��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 AT_ModemGetUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                       **ppstBuf
)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;


    PS_MEM_SET(&stCtlParam, 0x00, sizeof(stCtlParam));


    /* Modified by L60609 for PS Project��2011-12-06,  Begin*/

    /* ��ȡ������������buffer */
    ulResult = mdrv_udi_ioctl(g_alAtUdiHandle[ucIndex], ACM_IOCTL_GET_RD_BUFF, &stCtlParam);

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_ModemGetUlDataBuf, WARNING, Get modem buffer failed code %d!",
                  ulResult);
        AT_MODEM_DBG_UL_GET_RD_FAIL_NUM(1);
        return AT_FAILURE;
    }

    if (VOS_NULL_PTR == stCtlParam.pVirAddr)
    {
        AT_ERR_LOG("AT_ModemGetUlDataBuf, WARNING, Data buffer error");
        AT_MODEM_DBG_UL_INVALID_RD_NUM(1);
        return AT_FAILURE;
    }

    AT_MODEM_DBG_UL_GET_RD_SUCC_NUM(1);

    *ppstBuf = (IMM_ZC_STRU *)stCtlParam.pVirAddr;

    /* Modified by L60609 for PS Project��2011-12-06,  End*/
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : At_ModemDataInd
 ��������  : USB Modem���ݴ���
 �������  : VOS_UINT8                           ucPortType,
             VOS_UINT8                           ucDlci,
             IMM_ZC_STRU                        *pstData,
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             AT_SUCCESS
             AT_SUCCESS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.Date        : 2007-11-14
    Author      : s62952
    Modification: Created function
  2.��    ��   : 2011��10��15��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬���� client id
  3.��    ��   : 2011��12��8��
    ��    ��   : ³��/l60609
    �޸�����   : Buf�����޸�ΪIMM_ZC_STRU
  4.��    ��   : 2011��12��8��
    ��    ��   : w00199382
    �޸�����   : ���CSD�ӿ�
  5.��    ��   : 2013��05��22��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 At_ModemDataInd(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucDlci,
    IMM_ZC_STRU                        *pstData
)
{
    /* Modified by L60609 for PS Project��2011-12-06,  Begin*/
    AT_DCE_MSC_STRU                     stMscStru;
    VOS_UINT32                          ulRet;
    /* pDataΪ��������ָ�� */
    VOS_UINT8                          *pData;
    /* usLenΪ�������ݵĳ��� */
    VOS_UINT16                          usLen;

    /* ���index��Dlci�Ƿ���ȷ */
    if (AT_CLIENT_TAB_MODEM_INDEX != ucIndex)
    {
        /*�ͷ��ڴ�*/
        AT_ModemFreeUlDataBuf(ucIndex, pstData);
        return AT_FAILURE;
    }

    /* ��pstData(IMM_ZC_STRU����)��ȡ���������ݺͳ��ȣ��ֱ𱣴���pData��usLen�� */
    pData = pstData->data;
    usLen = (VOS_UINT16)pstData->len;

    if ( AT_CMD_MODE == gastAtClientTab[ucIndex].Mode )
    {
        /*��Modemͨ���Ѿ���������̬������ʱ��Ȼ�յ�PPP֡����ֱ�Ӷ���*/
        if ((usLen > 0) && (0x7e == pData[0]) && (0x7e == pData[usLen - 1]))
        {
            /*�ͷ�BSP�ڴ�*/
            AT_ModemFreeUlDataBuf(ucIndex, pstData);
            return AT_SUCCESS;
        }

        ulRet = At_CmdStreamPreProc(ucIndex,pData,usLen);

        /*�ͷ�BSP�ڴ�*/
        AT_ModemFreeUlDataBuf(ucIndex, pstData);
        return ulRet;
    }

    /* ����modem�ڵ�״̬���зַ�*/
    switch ( gastAtClientTab[ucIndex].DataMode )
    {
        case AT_PPP_DATA_MODE:

            /* (AT2D17549)���MAC 10.6.2ϵͳ���ŹҶ�ʧ������.���ձ�˵ķ�ʽ��
               ����������Ϊ"+++"����ģ������DTR�źŵĴ���ʽ
            */
            if (3 == usLen)
            {
                if (('+' == pData[0]) && ('+' == pData[1]) && ('+' == pData[2]))
                {
                    /*ģ������DTR�ź�*/
                    VOS_MemSet(&stMscStru, 0x00, sizeof(stMscStru));
                    stMscStru.OP_Dtr = 1;
                    stMscStru.ucDtr  = 0;
                    At_ModemMscInd(ucIndex, ucDlci, &stMscStru);
                    break;
                }
            }
            /* PPP�����ͷ������ڴ� */
            PPP_PullPacketEvent(gastAtClientTab[ucIndex].usPppId, pstData);
            return AT_SUCCESS;

        case AT_IP_DATA_MODE:
            if (3 == usLen)
            {
                if (('+' == pData[0]) && ('+' == pData[1]) && ('+' == pData[2]))
                {
                    /*ģ������DTR�ź�*/
                    VOS_MemSet(&stMscStru, 0x00, sizeof(stMscStru));
                    stMscStru.OP_Dtr = 1;
                    stMscStru.ucDtr  = 0;
                    At_ModemMscInd(ucIndex, ucDlci, &stMscStru);
                    break;
                }
            }
            /* PPP�����ͷ������ڴ� */
            PPP_PullRawDataEvent(gastAtClientTab[ucIndex].usPppId, pstData);
            return AT_SUCCESS;

        /* Modified by s62952 for AT Project��2011-10-17,  Begin*/
        case AT_CSD_DATA_MODE:
            /* Added by w00199382 for PS Project��2011-12-06,  Begin*/
            /* Added by w00199382 for PS Project��2011-12-06,  End*/
         /* Modified by s62952 for AT Project��2011-10-17,  end*/

        default:
            AT_WARN_LOG("At_ModemDataInd: DataMode Wrong!");
            break;
    }

    /*�ͷ��ڴ�*/
    AT_ModemFreeUlDataBuf(ucIndex, pstData);
    /* Modified by L60609 for PS Project��2011-12-06,  End*/
    return AT_SUCCESS;
}

/*****************************************************************************
�� �� ��  : AT_ModemInitUlDataBuf
��������  : ��װMODEM�豸�ܽ��ź�д�ӿ�
�������  : ucIndex        ----   ������
            ulEachBuffSize ----   �����������ݿ�BUFFER��С��
            ulTotalBuffNum ----   �����������ݿ�BUFFER����
�������  : ��
�� �� ֵ  : AT_SUCCESS     ----   �ɹ���
            AT_FAILURE     ----   ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��28��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 AT_ModemInitUlDataBuf(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulEachBuffSize,
    VOS_UINT32                          ulTotalBuffNum
)
{
    ACM_READ_BUFF_INFO                  stReadBuffInfo;
    VOS_INT32                           ulResult;


    /* ��д��Ҫ�ͷŵ��ڴ�ָ�� */
    stReadBuffInfo.u32BuffSize = ulEachBuffSize;
    stReadBuffInfo.u32BuffNum  = ulTotalBuffNum;

    ulResult= mdrv_udi_ioctl(g_alAtUdiHandle[ucIndex], ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo);

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_ModemInitUlDataBuf, WARNING, Initialize data buffer failed code %d!\r\n",
                  ulResult);

        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
�� �� ��  : AT_ModemFreeUlDataBuf
��������  : �ͷ������ڴ�
�������  : pstBuf     ----      ��������ָ��
�������  : ��
�� �� ֵ  : AT_SUCCESS ----      �ɹ���
            AT_FAILURE ----      ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��8��
   ��    ��   : ³��/l60609
   �޸�����   : Buf�����޸�ΪIMM_ZC_STRU
 3.��    ��   : 2013��05��28��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_UINT32 AT_ModemFreeUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstBuf
)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;

    /* Modified by L60609 for PS Project��2011-12-06,  Begin*/
    /* ��д��Ҫ�ͷŵ��ڴ�ָ�� */
    stCtlParam.pVirAddr = (VOS_CHAR*)pstBuf;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;
    stCtlParam.u32Size  = 0;
    stCtlParam.pDrvPriv = VOS_NULL_PTR;
    /* Modified by L60609 for PS Project��2011-12-06,  End*/

    ulResult = mdrv_udi_ioctl(g_alAtUdiHandle[ucIndex], ACM_IOCTL_RETURN_BUFF, &stCtlParam);

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_ModemFreeUlDataBuf, ERROR, Return modem buffer failed, code %d!\r\n",
                  ulResult);
        AT_MODEM_DBG_UL_RETURN_BUFF_FAIL_NUM(1);
        return AT_FAILURE;
    }

    AT_MODEM_DBG_UL_RETURN_BUFF_SUCC_NUM(1);

    return AT_SUCCESS;
}

/*****************************************************************************
�� �� ��  : AT_ModemFreeDlDataBuf
��������  : �ͷ�PPPģ�����������ڴ棬ע�������ʹ��
�������  : pstBuf     ----      ��������ָ��
�������  : ��
�� �� ֵ  : AT_SUCCESS ----      �ɹ���
            AT_FAILURE ----      ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��8��
   ��    ��   : ³��/l60609
   �޸�����   : Buf�����޸�ΪIMM_ZC_STRU
*****************************************************************************/
VOS_VOID AT_ModemFreeDlDataBuf(
    IMM_ZC_STRU                        *pstBuf
)
{
    AT_MODEM_DBG_DL_FREE_BUFF_NUM(1);

    /* Modified by L60609 for PS Project��2011-12-06,  Begin*/
    /* �ͷ�pstBuf */
    IMM_ZcFree(pstBuf);
    /* Modified by L60609 for PS Project��2011-12-06,  End*/
    return;
}

/*****************************************************************************
 �� �� ��  : AT_ModemWriteData
 ��������  : ��װMODEM�豸����д�ӿ�
 �������  : ucIndex    ----      ������
             pstBuf     ----      ��������ָ��
 �������  : ��
 �� �� ֵ  : AT_SUCCESS ----      �ɹ���
             AT_FAILURE ----      ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��8��
    ��    ��   : ³��/l60609
    �޸�����   : Buf�����޸�ΪIMM_ZC_STRU

  3.��    ��   : 2013��05��28��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  4.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ��װдʧ�ܺ���ڴ��ͷ�����
*****************************************************************************/
VOS_UINT32 AT_ModemWriteData(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstBuf
)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;

    /* ��д�������ڴ��ַ */
    stCtlParam.pVirAddr                 = (VOS_CHAR*)pstBuf;
    stCtlParam.pPhyAddr                 = VOS_NULL_PTR;
    stCtlParam.u32Size                  = 0;
    stCtlParam.pDrvPriv                 = VOS_NULL_PTR;

    if (UDI_INVALID_HANDLE == g_alAtUdiHandle[ucIndex])
    {
        AT_ModemFreeDlDataBuf(pstBuf);
        return AT_FAILURE;
    }

    /* �첽��ʽд����*/
    ulResult = mdrv_udi_ioctl(g_alAtUdiHandle[ucIndex], ACM_IOCTL_WRITE_ASYNC, &stCtlParam);

    if (VOS_OK != ulResult)
    {
        AT_WARN_LOG("AT_ModemWriteData: Write data failed with code!\r\n");
        AT_MODEM_DBG_DL_WRITE_ASYNC_FAIL_NUM(1);
        AT_ModemFreeDlDataBuf(pstBuf);
        return AT_FAILURE;
    }

    AT_MODEM_DBG_DL_WRITE_ASYNC_SUCC_NUM(1);

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_SendDataToModem
 ��������  : ���з������ݸ�modem��
 �������  : pucDataBuf   ----    ���������������ڴ�ָ��
             usLen        ----    ���ݳ���
 �������  :
 �� �� ֵ  : AT_SUCCESS ----      �ɹ���
             AT_FAILURE ----      ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��8��
    ��    ��   : ³��/l60609
    �޸�����   : Buf�����޸�ΪIMM_ZC_STRU

  3.��    ��   : 2012��8��31��
    ��    ��   : l60609
    �޸�����   : AP������Ŀ���޸�IMM�ӿ�

  4.��    ��   : 2013��05��28��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  5.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ɾ��дʧ�ܺ���ͷ��ڴ�����, ��д�����ڲ���װ
*****************************************************************************/
VOS_UINT32 AT_SendDataToModem(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT16                          usLen
)
{
    IMM_ZC_STRU                        *pstData;
    VOS_CHAR                           *pstZcPutData;

    pstData = VOS_NULL_PTR;

    pstData = IMM_ZcStaticAlloc((VOS_UINT16)usLen);

    if (VOS_NULL_PTR == pstData)
    {
        return AT_FAILURE;
    }

    /*�˲��費���٣�����ƫ������βָ��*/
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 Begin */
    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstData, usLen);
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 End */

    PS_MEM_CPY(pstZcPutData, pucDataBuf, usLen);

    /*������д��MODEM�豸��д�ɹ����ڴ��ɵ������ͷ�*/
    if (AT_SUCCESS != AT_ModemWriteData(ucIndex, pstData))
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_SendZcDataToModem
 ��������  : ���з���SK_buff���ݸ�modem��
 �������  : pucDataBuf   ----    ���������������ڴ�ָ��
             usLen        ----    ���ݳ���
 �������  :
 �� �� ֵ  : AT_SUCCESS ----      �ɹ���
             AT_FAILURE ----      ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��8��
    ��    ��   : ³��/l60609
    �޸�����   : Buf�����޸�ΪIMM_ZC_STRU

  3.��    ��   : 2013��05��28��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  4.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����֧��UART�˿�

  5.��    ��   : 2015��3��31��
    ��    ��   : A00165503
    �޸�����   : DTS2015032704953: HSUART�˿��л���CMD/ONLINE_CMDģʽʱ,
                 ��Ҫ���HSUART�Ļ����������, ��ֹ��ǰ���������ʱ, ������
                 �������ʧ
*****************************************************************************/
VOS_UINT32 AT_SendZcDataToModem(
    VOS_UINT16                          usPppId,
    IMM_ZC_STRU                        *pstDataBuf
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    ucIndex = gastAtPppIndexTab[usPppId];

    if ( (AT_CMD_MODE        == gastAtClientTab[ucIndex].Mode)
      || (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode) )
    {
        IMM_ZcFree(pstDataBuf);
        return AT_FAILURE;
    }

    switch (gastAtClientTab[ucIndex].UserType)
    {
        case AT_MODEM_USER:
            ulResult = AT_ModemWriteData(ucIndex, pstDataBuf);
            break;


        default:
            IMM_ZcFree(pstDataBuf);
            ulResult = AT_FAILURE;
            break;
    }

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : AT_SendCsdZcDataToModem
 ��������  : ���з���SK_buff���ݸ�modem��
 �������  : pucDataBuf   ----    ���������������ڴ�ָ��
             usLen        ----    ���ݳ���
 �������  :
 �� �� ֵ  : AT_SUCCESS ----      �ɹ���
             AT_FAILURE ----      ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��28��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT

  2.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ɾ��дʧ�ܺ���ͷ��ڴ�����, ��д�����ڲ���װ
*****************************************************************************/
VOS_UINT32 AT_SendCsdZcDataToModem(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstDataBuf
)
{
    /*������д��MODEM�豸��д�ɹ����ڴ��ɵ������ͷ�*/
    if (AT_SUCCESS != AT_ModemWriteData(ucIndex, pstDataBuf))
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
�� �� ��  : AT_UsbModemEnableCB
��������  : MODEM�豸ʹ��֪ͨ�ص���ע�������
�������  : ucEnable    ----  �Ƿ�ʹ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��27��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID AT_UsbModemEnableCB(PS_BOOL_ENUM_UINT8 ucEnable)
{
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    AT_ModemeEnableCB(ucIndex, ucEnable);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_UsbModemReadDataCB
 ��������  : MODEM�豸���ݶ��ص���ע�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��18��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��8��
   ��    ��   : ³��/l60609
   �޸�����   : Buf�����޸�ΪIMM_ZC_STRU
 3.��    ��   : 2013��05��25��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID AT_UsbModemReadDataCB( VOS_VOID )
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;
    IMM_ZC_STRU                        *pstBuf;

    pstBuf          = VOS_NULL_PTR;

    /* HSIC MODEM������ */
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;

    AT_MODEM_DBG_UL_DATA_READ_CB_NUM(1);

    /* Modified by L60609 for PS Project��2011-12-06,  Begin*/
    if (AT_SUCCESS == AT_ModemGetUlDataBuf(ucIndex, &pstBuf))
    {

        /*MODEM��·�� */
        ucDlci      = AT_MODEM_USER_DLCI;

        /* �����豸��ǰģʽ���ַ��������� */
        At_ModemDataInd(ucIndex, ucDlci, pstBuf);
    }
    /* Modified by L60609 for PS Project��2011-12-06,  End*/

    return;
}

/*****************************************************************************
�� �� ��  : AT_UsbModemReadMscCB
��������  : �ܽ��źŴ���
�������  : pstRcvedMsc ----      ����֪ͨ�ܽ��ź�ָ��
�������  : ��
�� �� ֵ  : AT_SUCCESS  ----      �ɹ���
            AT_FAILURE  ----      ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��25��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/
VOS_VOID AT_UsbModemReadMscCB(AT_DCE_MSC_STRU *pstRcvedMsc)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucDlci;

    if (VOS_NULL_PTR == pstRcvedMsc)
    {
        AT_WARN_LOG("AT_UsbModemReadMscCB, WARNING, Receive NULL pointer MSC info!");

        return;
    }

    /* MODEM������ */
    ucIndex     = AT_CLIENT_TAB_MODEM_INDEX;

    /*MODEM��·�� */
    ucDlci      = AT_MODEM_USER_DLCI;

     /* ����ܽ��źſ�ά�ɲ� */
    AT_MNTN_TraceInputMsc(ucIndex, pstRcvedMsc);

    At_ModemMscInd(ucIndex, ucDlci, pstRcvedMsc);

    return;
}

/*****************************************************************************
�� �� ��  : AT_UsbModemInit
��������  : MODEM�豸��ʼ��
�������  : VOS_VOID
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��10��17��
   ��    ��   : sunshaohua
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��27��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
 3.��    ��   : 2013��11��06��
   ��    ��   : j00174725
   �޸�����   : V3R3 �ڴ�ü�
 4.��    ��   : 2015��10��22��
   ��    ��   : y00213812
   �޸�����   : ��ʽ�������������ݲ���Ҫcopy
*****************************************************************************/
VOS_VOID AT_UsbModemInit( VOS_VOID )
{
    UDI_OPEN_PARAM_S                    stParam;
    VOS_UINT8                           ucIndex;

    ucIndex         = AT_CLIENT_TAB_MODEM_INDEX;
    stParam.devid   = UDI_ACM_MODEM_ID;

    /* ��Device�����ID */
    g_alAtUdiHandle[ucIndex] = mdrv_udi_open(&stParam);

    if (UDI_INVALID_HANDLE == g_alAtUdiHandle[ucIndex])
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Open usb modem device failed!");

        return;
    }

    /* ע��MODEM�豸�������ݽ��ջص� */
    if (VOS_OK != mdrv_udi_ioctl (g_alAtUdiHandle[ucIndex], ACM_IOCTL_SET_READ_CB, AT_UsbModemReadDataCB))
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Set data read callback for modem failed!");

        return;
    }

    /* ע��MODEM���������ڴ��ͷŽӿ� */
    if (VOS_OK != mdrv_udi_ioctl (g_alAtUdiHandle[ucIndex], ACM_IOCTL_SET_FREE_CB, AT_ModemFreeDlDataBuf))
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Set memory free callback for modem failed!");

        return;
    }

    /* ע��MODEM�������ݲ���Ҫ���� */
    if (VOS_OK != mdrv_udi_ioctl (g_alAtUdiHandle[ucIndex], ACM_IOCTL_WRITE_DO_COPY, (void *)0))
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Set not do copy for modem failed!");

        return;
    }

    /* ע��ܽ��ź�֪ͨ�ص� */
    if (VOS_OK != mdrv_udi_ioctl (g_alAtUdiHandle[ucIndex], ACM_MODEM_IOCTL_SET_MSC_READ_CB, AT_UsbModemReadMscCB))
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Set msc read callback for modem failed!");

        return;
    }

    /* ע��MODEM�豸ʹ�ܡ�ȥʹ��֪ͨ�ص� */
    if (VOS_OK != mdrv_udi_ioctl (g_alAtUdiHandle[ucIndex], ACM_MODEM_IOCTL_SET_REL_IND_CB, AT_UsbModemEnableCB))
    {
        AT_ERR_LOG("AT_UsbModemInit, ERROR, Set enable callback for modem failed!");

        return;
    }

    /* ����MODEM�豸��������buffer��� */
    AT_ModemInitUlDataBuf(ucIndex, AT_MODEM_UL_DATA_BUFF_SIZE, AT_MODEM_UL_DATA_BUFF_NUM);

    /* ��ʼ��MODMEͳ����Ϣ */
    AT_InitModemStats();

    /*ע��client id*/
    At_ModemEst(ucIndex, AT_CLIENT_ID_MODEM, AT_USB_MODEM_PORT_NO);

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_MODEM, ID_AT_MNTN_RESULT_MODEM);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_UsbModemClose
 ��������  : USB�γ�ʱ���ر�MODEM�豸
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��6��
    ��    ��   : ��� l00171473
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��22��
    ��    ��   : f00179208
    �޸�����   : DTS2012052205142, ����VIDEO PHONE������
*****************************************************************************/
VOS_VOID AT_UsbModemClose(VOS_VOID)
{
    AT_CLIENT_TAB_INDEX_UINT8           ucIndex;

    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;

    /* ȥע��MODEM���ص�(��TTFȷ��δע�����ص�Ҳ����ȥע�����ص�)�� */
    AT_DeRegModemPsDataFCPoint(ucIndex, gastAtClientTab[ucIndex].ucPsRabId);

    if (UDI_INVALID_HANDLE != g_alAtUdiHandle[ucIndex])
    {
        mdrv_udi_close(g_alAtUdiHandle[ucIndex]);

        g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;

        (VOS_VOID)vos_printf("AT_UsbModemClose....\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_SetUsbDebugFlag
 ��������  : ���õ���ģʽ
 �������  : VOS_UINT32 ulFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��10��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetUsbDebugFlag(VOS_UINT32 ulFlag)
{
    g_ulAtUsbDebugFlag = ulFlag;
}

/*****************************************************************************
 Prototype      : At_RcvFromUsbCom
 Description    : ATע���USB COM�����Ļص����������ڴӴ����л�ȡ����
 Input          : ucPortNo     --    �˿ں�
                  pucData      --    AT�Ӵ��ڽ��յ�����ָ��
                  uslength��   --    AT�Ӵ��ڽ��յ����ݳ���
 Output         : ---
 Return Value   : AT_DRV_FAILURE --- �ɹ�
                  AT_DRV_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-06-09
    Author      : L47619
    Modification: Created function
  2.Date        : 2012-02-24
    Author      : L47619
    Modification: V7R1C50 IPC��Ŀ:����HSIC ATͨ������AT������߼�
  3.��    ��   : 2012��8��3��
    ��    ��   : L60609
    �޸�����   : MUX��Ŀ������MUX ATͨ������AT������߼�
*****************************************************************************/

VOS_INT At_RcvFromUsbCom(
    VOS_UINT8                           ucPortNo,
    VOS_UINT8                          *pData,
    VOS_UINT16                          uslength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    /* Added by L60609 for MUX��2012-08-08,  Begin */
    VOS_UINT32                          ulMuxUserFlg;
    VOS_UINT32                          ulHsicUserFlg;
    /* Added by L60609 for MUX��2012-08-08,  End */

    if (VOS_TRUE == g_ulAtUsbDebugFlag)
    {
        (VOS_VOID)vos_printf("At_RcvFromUsbCom: PortNo = %d, length = %d, data = %s\r\n", ucPortNo, uslength, pData);
    }

    if (VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("At_RcvFromUsbCom: pData is NULL PTR!");
        return AT_DRV_FAILURE;
    }

    if (0 == uslength)
    {
        AT_WARN_LOG("At_RcvFromUsbCom: uslength is 0!");
        return AT_DRV_FAILURE;
    }

    /*PCUI��CTRL����*/
    for (ucIndex = 0; ucIndex < AT_MAX_CLIENT_NUM; ucIndex++)
    {
        /* Modified by L60609 for MUX��2012-08-03,  Begin */
        ulMuxUserFlg = AT_CheckMuxUser(ucIndex);
        ulHsicUserFlg = AT_CheckHsicUser(ucIndex);

        if ((AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
         || (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
         || (AT_PCUI2_USER == gastAtClientTab[ucIndex].UserType)
         || (AT_UART_USER == gastAtClientTab[ucIndex].UserType)
         || (VOS_TRUE == ulMuxUserFlg)
         || (VOS_TRUE == ulHsicUserFlg))
        {
            if (AT_CLIENT_NULL != gastAtClientTab[ucIndex].ucUsed)
            {
                if (gastAtClientTab[ucIndex].ucPortNo == ucPortNo)
                {
                    break;
                }
            }
        }
        /* Modified by L60609 for MUX��2012-08-03,  End */
    }

    if (VOS_TRUE == g_ulAtUsbDebugFlag)
    {
        (VOS_VOID)vos_printf("At_RcvFromUsbCom: ucIndex = %d\r\n", ucIndex);
    }

    if (ucIndex >= AT_MAX_CLIENT_NUM)
    {
        AT_WARN_LOG("At_RcvFromUsbCom (ucIndex >= AT_MAX_CLIENT_NUM)");
        return AT_DRV_FAILURE;
    }

    if (VOS_TRUE == g_ulAtUsbDebugFlag)
    {
        (VOS_VOID)vos_printf("At_RcvFromUsbCom: CmdMode = %d\r\n", gastAtClientTab[ucIndex].Mode);
    }

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        ulRet = At_CmdStreamPreProc(ucIndex,pData,uslength);
    }
    else
    {
        ulRet = At_DataStreamPreProc(ucIndex,gastAtClientTab[ucIndex].DataMode,pData,uslength);
    }

    if ( AT_SUCCESS == ulRet )
    {
        return AT_DRV_SUCCESS;
    }
    else
    {
        return AT_DRV_FAILURE;
    }
}


/*****************************************************************************
 �� �� ��  : At_UsbPcuiEst
 ��������  : USB PCUI��·�Ľ���
 �������  : TAF_UINT8 ucPortNo
 �������  : ��
 �� �� ֵ  : VOS_OK
             VOS_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008-06-09
    ��    ��   : L47619
    �޸�����   : Created function
  2.��    ��   : 2010��7��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ�ţ�DTS2010071402189��֧��ATģ���CLIENT ID�Ļط�
  3.��    ��   : 2010��9��14��
    ��    ��   : z00161729
    �޸�����   : DTS2010090901291:PC VOICEͨ��������,PC����/����/�ػ�/����ʱ�绰�޷��Ҷ�
  4.��    ��   : 2011��9��30��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id;DRV->DMS
  5.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_UINT32 At_UsbPcuiEst(VOS_UINT8 ucPortNo)
{
    /* Modified by L60609 for AT Project��2011-10-04,  Begin*/
    VOS_UINT8                           ucIndex;

    if (AT_USB_COM_PORT_NO != ucPortNo)
    {
        AT_WARN_LOG("At_UsbPcuiEst the PortNo is error)");
        return VOS_ERR;
    }

    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex],0x00,sizeof(AT_CLIENT_MANAGE_STRU));

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_PCUI, ID_AT_MNTN_RESULT_PCUI);

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    /* Modified by L60609 for AT Project��2011-10-14,  Begin*/
    /*��DMSע��Ӵ����л�ȡ���ݵĻص�����*/
    (VOS_VOID)DMS_COM_RCV_CALLBACK_REGI(ucPortNo, (pComRecv)At_RcvFromUsbCom);

    /* Modify by z60575 for DTS2012053100001,��������ͬ����PCLINT�޸�, 2012-5-31 begin */
    /* Modify by z60575 for DTS2012053100001,��������ͬ����PCLINT�޸�, 2012-5-31 end */

    /* Modified by L60609 for AT Project��2011-10-14,  End*/

    AT_LOG1("At_UsbPcuiEst ucIndex:",ucIndex);

    /* Modified by L60609 for AT Project��2011-10-04,  End*/
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : At_UsbCtrEst
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��control ��·�ĳ�ʼ������
 �������  : ucPortNo    - �˿ں�
 �������  : ��
 �� �� ֵ  : VOS_OK
             VOS_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��12��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��03��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id;DRV->DMS

  3.��    ��   : 2011��11��15��
    ��    ��   : o00132663
    �޸�����   : AT�ں���Ŀ�����ݼ�������޸�M2���Ժ�ʹ���߼�

  4.��    ��  : 2013��03��13��
    ��    ��  : z00214637
    �޸�����  : BodySAR��Ŀ

  5.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_UINT32 At_UsbCtrEst(VOS_UINT8 ucPortNo)
{
    /* Modified by L60609 for AT Project��2011-10-04,  Begin*/
    VOS_UINT8                           ucIndex;


    if (AT_CTR_PORT_NO != ucPortNo)
    {
        AT_WARN_LOG("At_UsbCtrEst the PortNo is error)");
        return VOS_ERR;
    }

    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_CTRL, ID_AT_MNTN_RESULT_CTRL);

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_CTRL;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_CTR_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;


    /*�����DMS�Ӵ����л�ȡ���ݵĻص�����*/
    (VOS_VOID)DMS_COM_RCV_CALLBACK_REGI(ucPortNo, (pComRecv)At_RcvFromUsbCom);
    /* Modified by L60609 for AT Project��2011-10-14,  End*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : At_UsbPcui2Est
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��PCUI2��·�ĳ�ʼ������
 �������  : ucPortNo    - �˿ں�
 �������  : ��
 �� �� ֵ  : VOS_OK
             VOS_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 At_UsbPcui2Est(VOS_UINT8 ucPortNo)
{
    VOS_UINT8                           ucIndex;

    if (AT_PCUI2_PORT_NO != ucPortNo)
    {
        AT_WARN_LOG("At_UsbPcui2Est the PortNo is error)");
        return VOS_ERR;
    }

    ucIndex = AT_CLIENT_TAB_PCUI2_INDEX;

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_PCUI2, ID_AT_MNTN_RESULT_PCUI2);

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI2;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_PCUI2_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    /*�����DMS�Ӵ����л�ȡ���ݵĻص�����*/
    (VOS_VOID)DMS_COM_RCV_CALLBACK_REGI(ucPortNo, (pComRecv)At_RcvFromUsbCom);

    return VOS_OK;
}

/******************************************************************************
 �� �� ��  : AT_UART_GetUlDataBuff
 ��������  : ��ȡUART�豸�������ݴ洢�ռ�
 �������  : ucIndex    - �˿�����
 �������  : ppucData   - ������Ϣ�ռ�
             pulLen     - ���ݳ���
 �� �� ֵ  : AT_SUCCESS - �ɹ�
             AT_FAILURE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  3.��    ��   : 2013��9��25��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ����UDI�����Ч�Լ��
*****************************************************************************/
VOS_UINT32 AT_UART_GetUlDataBuff(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                         **ppucData,
    VOS_UINT32                         *pulLen
)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    UDI_HANDLE                          lUdiHandle;
    VOS_INT32                           lResult;

    lUdiHandle = g_alAtUdiHandle[ucIndex];
    if (UDI_INVALID_HANDLE == lUdiHandle)
    {
        AT_ERR_LOG("AT_UART_GetUlDataBuff: Invalid UDI handle!\r\n");
        return AT_FAILURE;
    }

    /* ��ȡ������������BUFFER */
    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;
    stCtlParam.u32Size  = 0;
    stCtlParam.pDrvPriv = VOS_NULL_PTR;

    lResult = mdrv_udi_ioctl(lUdiHandle, UART_IOCTL_GET_RD_BUFF, &stCtlParam);
    if (VOS_OK != lResult)
    {
        AT_ERR_LOG("AT_UART_GetUlDataBuff: Get buffer failed!\r\n");
        return AT_FAILURE;
    }

    if ( (VOS_NULL_PTR == stCtlParam.pVirAddr)
      || (AT_INIT_DATA_LEN == stCtlParam.u32Size) )
    {
        AT_ERR_LOG("AT_UART_GetUlDataBuff: Data buffer error!\r\n");
        return AT_FAILURE;
    }

    *ppucData = (VOS_UINT8 *)stCtlParam.pVirAddr;
    *pulLen   = stCtlParam.u32Size;

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_UART0_WriteDlDataSync
 ��������  : ��װUART�豸ͬ��д���ݽӿ�
 �������  : ucIndex    - �˿�����
             pucData    - ��������ָ��
             ulLen      - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS - �ɹ�
             AT_FAILURE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��7��
    ��    ��   : ��� l00171473
    �޸�����   : DTS2011120801675 ֧��UARTͨ��У׼�޸�

  3.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ͳһUDI�����ά��
*****************************************************************************/
VOS_UINT32 AT_UART_WriteDataSync(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    UDI_HANDLE                          lUdiHandle;
    VOS_INT32                           lResult;

    /* ���UDI�����Ч�� */
    lUdiHandle = g_alAtUdiHandle[ucIndex];
    if (UDI_INVALID_HANDLE == lUdiHandle)
    {
        AT_ERR_LOG("AT_UART_WriteDataSync: Invalid UDI handle!\r\n");
        return AT_FAILURE;
    }

    /* ���������Ч�� */
    if ((VOS_NULL_PTR == pucData) || (0 == ulLen))
    {
        AT_ERR_LOG("AT_UART_WriteDataSync: DATA is invalid!\r\n");
        return AT_FAILURE;
    }

    lResult = mdrv_udi_write(lUdiHandle, pucData, ulLen);
    if (VOS_OK != lResult)
    {
        AT_HSUART_DBG_DL_WRITE_SYNC_FAIL_LEN(ulLen);
        AT_ERR_LOG("AT_UART_WriteDataSync: Write buffer failed!\r\n");
        return AT_FAILURE;
    }

    AT_HSUART_DBG_DL_WRITE_SYNC_SUCC_LEN(ulLen);

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_UART_SendDlData
 ��������  : д������UART�豸
 �������  : ucIndex    - �˿�����
             pucData    - ���ݵ�ַ
             usLen      - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS - �ɹ�
             AT_FAILURE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_UART_SendDlData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    /* ͬ��дUART�豸, ���������ͷ� */
    return AT_UART_WriteDataSync(ucIndex, pucData, usLen);
}

/*****************************************************************************
 �� �� ��  : AT_UART_SendRawDataFromOm
 ��������  : ���з���OM���ݸ�UART��, �ṩ��OM�Ľӿ�
 �������  : pucVirAddr - �����������������ַ
             pucPhyAddr - ��������������ʵ��ַ
             usLen   - ���ݳ���
 �������  :
 �� �� ֵ  : VOS_OK  - �ɹ�
             VOS_ERR - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: ���÷�װ��UARTͬ��д�ӿ�
*****************************************************************************/
VOS_UINT32 AT_UART_SendRawDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    ucIndex  = AT_CLIENT_TAB_UART_INDEX;

    ulResult = AT_UART_WriteDataSync(ucIndex, pucVirAddr, (VOS_UINT16)ulLen);
    if (AT_SUCCESS != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_HSUART_UlDataReadCB
 ��������  : UART�豸���ݶ��ص���ע�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_UART_UlDataReadCB(VOS_VOID)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           ucIndex;

    ulLen   = 0;
    ucIndex = AT_CLIENT_TAB_UART_INDEX;

    if (AT_SUCCESS == AT_UART_GetUlDataBuff(ucIndex, &pucData, &ulLen))
    {
        /* �����豸��ǰģʽ���ַ��������� */
        At_RcvFromUsbCom(AT_UART_PORT_NO, pucData, (VOS_UINT16)ulLen);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_UART_InitLink
 ��������  : ����NV������UART�˿ڵĹ���ģʽ
 �������  : ucIndex ---- �˿�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��28��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��24��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬����client id

  3.��    ��   : 2011��12��7��
    ��    ��   : ��� l00171473
    �޸�����   : DTS2011120801675, UARTͨ��У׼�޸�

  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  5.��    ��   : 2013��05��17��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_VOID AT_UART_InitLink(VOS_UINT8 ucIndex)
{
    TAF_AT_NVIM_DEFAULT_LINK_OF_UART_STRU    stDefaultLinkType;


    stDefaultLinkType.enUartLinkType = AT_UART_LINK_TYPE_BUTT;


    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex],0x00,sizeof(AT_CLIENT_MANAGE_STRU));

    gastAtClientTab[ucIndex].ucPortNo  = AT_UART_PORT_NO;
    gastAtClientTab[ucIndex].UserType  = AT_UART_USER;
    gastAtClientTab[ucIndex].ucUsed    = AT_CLIENT_USED;


    /* ��ȡUART�˿�Ĭ�Ϲ���ģʽNV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_DEFAULT_LINK_OF_UART,
                        &stDefaultLinkType.enUartLinkType,
                        sizeof(stDefaultLinkType.enUartLinkType)))
    {
        /* NV���ȡʧ�ܣ���UART�˿ڵĹ���ģʽ����ΪOMģʽ */
        AT_ERR_LOG("AT_UART_InitLink:Read NV failed!");

        /*��¼AT/OMͨ������Ӧ��������*/
        gucAtOmIndex = ucIndex;

        /* �л���OM����ģʽ */
        At_SetMode(ucIndex, AT_DATA_MODE, AT_OM_DATA_MODE);
        gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

        AT_AddUsedClientId2Tab(AT_CLIENT_TAB_UART_INDEX);

        /* ֪ͨOAM�л�UART��OMģʽ */
        CBTCPM_NotifyChangePort(AT_UART_PORT);
    }
    else
    {
        /* NV��ȡ�ɹ������UART�˿ڵ�Ĭ�Ϲ���ģʽ */
        if (AT_UART_LINK_TYPE_AT != stDefaultLinkType.enUartLinkType)
        {
            AT_NORM_LOG("AT_UART_InitLink:DEFAULT UART LINK TYPE is OM!");

            /*��¼AT/OMͨ������Ӧ��������*/
            gucAtOmIndex = ucIndex;

            /* �л���OM����ģʽ */
            At_SetMode(ucIndex, AT_DATA_MODE, AT_OM_DATA_MODE);
            gastAtClientTab[ucIndex].DataState = AT_DATA_START_STATE;

            AT_AddUsedClientId2Tab(AT_CLIENT_TAB_UART_INDEX);

            /* ֪ͨOAM�л�UART��OMģʽ */
            CBTCPM_NotifyChangePort(AT_UART_PORT);
        }
        else
        {
            /* ��д�û����� */
            gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_UART;

            /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
            gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
            gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
            gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
            gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
            gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : AT_HSUART_InitPort
 ��������  : Uart�豸��ʼ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��7��
    ��    ��   : ��� l00171473
    �޸�����   : DTS2011120801675: UARTͨ��У׼�޸ģ�����UART��ʵ�ַ�ʽ�޸�
                 �ˣ�AT���ù���Buffer

  3.��    ��   : 2013��9��21��
    ��    ��   : j00174725
    �޸�����   : UART-MODEM: ͳһUDI�����ά��

  4.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_VOID AT_UART_InitPort(VOS_VOID)
{
    UDI_OPEN_PARAM_S                    stParam;
    UDI_HANDLE                          lUdiHandle;
    VOS_UINT8                           ucIndex;

    stParam.devid = UDI_UART_0_ID;
    ucIndex       = AT_CLIENT_TAB_UART_INDEX;

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_UART, ID_AT_MNTN_RESULT_UART);

    lUdiHandle = mdrv_udi_open(&stParam);
    if (UDI_INVALID_HANDLE != lUdiHandle)
    {
        /* ע��UART�豸�������ݽ��ջص� */
        if (VOS_OK != mdrv_udi_ioctl (lUdiHandle, UART_IOCTL_SET_READ_CB, AT_UART_UlDataReadCB))
        {
            AT_ERR_LOG("AT_UART_InitPort: Reg data read callback failed!\r\n");
        }

        /* ��ʼ��UART��· */
        AT_UART_InitLink(ucIndex);
        g_alAtUdiHandle[ucIndex] = lUdiHandle;
    }
    else
    {
        AT_ERR_LOG("AT_UART_InitPort: Open UART device failed!\r\n");
        g_alAtUdiHandle[ucIndex] = UDI_INVALID_HANDLE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : AT_CtrlDCD
 ��������  : ����DCD�ź�
 �������  : ucIndex   - �˿�����
             enIoLevel - �źŵ�ƽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_CtrlDCD(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId;

    PS_MEM_SET(&stDceMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    stDceMsc.OP_Dcd = VOS_TRUE;
    stDceMsc.ucDcd  = enIoLevel;

    AT_SetModemStatus(ucIndex, &stDceMsc);

    enEventId = (AT_IO_LEVEL_HIGH == enIoLevel) ?
                NAS_OM_EVENT_DCE_UP_DCD : NAS_OM_EVENT_DCE_DOWN_DCD;

    AT_EventReport(WUEPS_PID_AT, enEventId, &ucIndex, sizeof(VOS_UINT8));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CtrlDSR
 ��������  : ����DSR�ź�
 �������  : ucIndex   - �˿�����
             enIoLevel - �źŵ�ƽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_CtrlDSR(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId;

    PS_MEM_SET(&stDceMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    stDceMsc.OP_Dsr = VOS_TRUE;
    stDceMsc.ucDsr  = enIoLevel;

    AT_SetModemStatus(ucIndex, &stDceMsc);

    enEventId = (AT_IO_LEVEL_HIGH == enIoLevel) ?
                NAS_OM_EVENT_DCE_UP_DSR: NAS_OM_EVENT_DCE_DOWN_DSR;

    AT_EventReport(WUEPS_PID_AT, enEventId, &ucIndex, sizeof(VOS_UINT8));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CtrlCTS
 ��������  : ����CTS�ź�
 �������  : ucIndex   - �˿�����
             enIoLevel - �źŵ�ƽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_CtrlCTS(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId;

    PS_MEM_SET(&stDceMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    stDceMsc.OP_Cts = VOS_TRUE;
    stDceMsc.ucCts  = enIoLevel;

    AT_SetModemStatus(ucIndex, &stDceMsc);

    enEventId = (AT_IO_LEVEL_HIGH == enIoLevel) ?
                NAS_OM_EVENT_DCE_UP_CTS: NAS_OM_EVENT_DCE_DOWN_CTS;

    AT_EventReport(WUEPS_PID_AT, enEventId, &ucIndex, sizeof(VOS_UINT8));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CtrlRI
 ��������  : ����RI�ź�
 �������  : ucIndex   - �˿�����
             enIoLevel - �źŵ�ƽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_CtrlRI(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
)
{
    AT_DCE_MSC_STRU                     stDceMsc;
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId;

    PS_MEM_SET(&stDceMsc, 0x00, sizeof(AT_DCE_MSC_STRU));

    stDceMsc.OP_Ri = VOS_TRUE;
    stDceMsc.ucRi  = enIoLevel;

    AT_SetModemStatus(ucIndex, &stDceMsc);

    enEventId = (AT_IO_LEVEL_HIGH == enIoLevel) ?
                NAS_OM_EVENT_DCE_UP_RI: NAS_OM_EVENT_DCE_DOWN_RI;

    AT_EventReport(WUEPS_PID_AT, enEventId, &ucIndex, sizeof(VOS_UINT8));

    return;
}

/*****************************************************************************
 �� �� ��  : AT_GetIoLevel
 ��������  : ��ȡָ���źŵ�ƽ
 �������  : ucIndex          - �˿�����
             ucIoCtrl         - �ܽ��źŶ���:
                                IO_CTRL_FC
                                IO_CTRL_DSR
                                IO_CTRL_DTR
                                IO_CTRL_RFR
                                IO_CTRL_CTS
                                IO_CTRL_RI
                                IO_CTRL_DCD
 �������  : ��
 �� �� ֵ  : AT_IO_LEVEL_LOW  - �͵�ƽ
             AT_IO_LEVEL_HIGH - �ߵ�ƽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
AT_IO_LEVEL_ENUM_UINT8 AT_GetIoLevel(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucIoCtrl
)
{
    if (0 == (gastAtClientTab[ucIndex].ModemStatus & ucIoCtrl))
    {
        return AT_IO_LEVEL_LOW;
    }

    return AT_IO_LEVEL_HIGH;
}

/*****************************************************************************
 �� �� ��  : App_VcomRecvCallbackRegister
 ��������  : ע��ص�����
 �������  : uPortNo
             pCallback
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���
*****************************************************************************/
int  App_VcomRecvCallbackRegister(unsigned char  uPortNo, pComRecv pCallback)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : At_RcvFromAppCom
 ��������  : ע���Ӧ�õĽӿڣ����ڽ���AT����
 �������  : ucVcomId    - VCOM�豸������
             *pData      - ָ�����ݵ�ָ��
             uslength    - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��20��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬���� client id
  3.��    ��   : 2012��11��28��
    ��    ��   : l00227485
    �޸�����   : DSDA:����8��VCOMͨ����Ĵ���
*****************************************************************************/
VOS_INT AT_RcvFromAppCom(
    VOS_UINT8                           ucVcomId,
    VOS_UINT8                          *pData,
    VOS_UINT16                          uslength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    if (ucVcomId >= APP_VCOM_DEV_INDEX_BUTT)
    {
        AT_WARN_LOG("AT_RcvFromAppCom: Port No ERR!");
        return VOS_ERR;
    }
    /* APPVCOM��󼸸�����ATͨ�� */
    if (ucVcomId >= AT_VCOM_AT_CHANNEL_MAX)
    {
        AT_WARN_LOG("AT_RcvFromAppCom: Port No ERR!");
        return VOS_ERR;
    }
    if (VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("AT_RcvFromAppCom: pData is NULL PTR!");
        return VOS_ERR;
    }

    if (0 == uslength)
    {
        AT_WARN_LOG("AT_RcvFromAppCom: uslength is 0!");
        return VOS_ERR;
    }

    /* ���ݶ˿ں�ȷ��Index��ֵ */
    ucIndex = AT_CLIENT_TAB_APP_INDEX + ucVcomId;

    /* �ж��Ƿ���APPͨ�� */
    if ((AT_APP_USER != gastAtClientTab[ucIndex].UserType)
     || (AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed))
    {
        AT_WARN_LOG("AT_RcvFromAppCom: APP client is unused!");
        return VOS_ERR;
    }

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        ulRet = At_CmdStreamPreProc(ucIndex, pData, uslength);
    }
    else
    {
        ulRet = At_DataStreamPreProc(ucIndex, gastAtClientTab[ucIndex].DataMode, pData, uslength);
    }

    if ( AT_SUCCESS == ulRet )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_AppComEst
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��APP��·�ĳ�ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��10��
    ��    ��   : l60609
    �޸�����   : AP������Ŀ������CHDATA��ʼ��
  3.��    ��   : 2012��11��29��
    ��    ��   : l00227485
    �޸�����   : DSDA:����VCOM ATͨ������·��ʼ��
  4.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_INT32 AT_AppComEst(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucLoop;

    for (ucLoop = 0; ucLoop < AT_VCOM_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_CLIENT_TAB_APP_INDEX + ucLoop;

        /* ��ն�Ӧ���� */
        PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

        AT_ConfigTraceMsg(ucIndex, (ID_AT_CMD_APP + ucLoop), (ID_AT_MNTN_RESULT_APP + ucLoop));

        gastAtClientTab[ucIndex].usClientId     = AT_CLIENT_ID_APP + ucLoop;

        /* ��д�û����� */
        gastAtClientTab[ucIndex].ucPortNo        = APP_VCOM_DEV_INDEX_0 + ucLoop;
        gastAtClientTab[ucIndex].UserType        = AT_APP_USER;
        gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
        gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
        gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
        gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
        gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

        /* ע��ص����� */
        APP_VCOM_RegDataCallback(gastAtClientTab[ucIndex].ucPortNo, (SEND_UL_AT_FUNC)AT_RcvFromAppCom);

    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvFromSock
 ��������  : AT����SOCK������
 �������  : ucPortNo    - �˿ں�
             *pData      - ָ�����ݵ�ָ��
             uslength    - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��13��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��18��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬���� client id

*****************************************************************************/
VOS_INT AT_RcvFromSock(
    VOS_UINT8                          *pData,
    VOS_UINT32                         uslength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;

    if (VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("AT_RcvFromSock: pData is NULL PTR!");
        return VOS_ERR;
    }
    if (0 == uslength)
    {
        AT_WARN_LOG("AT_RcvFromSock: uslength is 0!");
        return VOS_ERR;
    }

    if ((AT_SOCK_USER != gastAtClientTab[ucIndex].UserType)
        ||(AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed))
    {
        AT_WARN_LOG("AT_RcvFromSock: SOCK client is unused!");
        return VOS_ERR;
    }

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        ulRet = At_CmdStreamPreProc(ucIndex,pData,(VOS_UINT16)uslength);
    }
    else
    {
        ulRet = At_DataStreamPreProc(ucIndex,gastAtClientTab[ucIndex].DataMode,pData,(VOS_UINT16)uslength);
    }
    if ( AT_SUCCESS == ulRet )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SockComEst
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��sock��·�ĳ�ʼ������
 �������  : ucPortNo    - �˿ں�
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��3��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id

  3.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_INT32 AT_SockComEst(VOS_UINT8 ucPortNo)
{

    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;

    if (AT_SOCK_PORT_NO != ucPortNo)
    {
        AT_WARN_LOG("At_SockComEst the PortNo is error)");
        return VOS_ERR;
    }

    PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_SOCK, ID_AT_MNTN_RESULT_SOCK);

    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_SOCK;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    /* Modified by s62952 for AT Project��2011-10-17,  Begin*/
    /*��DMSע��Ӵ����л�ȡ���ݵĻص�����*/
    (VOS_VOID)CPM_LogicRcvReg(CPM_AT_COMM,(CPM_RCV_FUNC)AT_RcvFromSock);
    /* Modified by s62952 for AT Project��2011-10-17,  end*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvFromAppSock
 ��������  : ע���Ӧ�õĽӿڣ����ڽ���AT����
 �������  : ucPortNo    - �˿ں�
             *pData      - ָ�����ݵ�ָ��
             uslength    - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��18��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬���� client id

*****************************************************************************/
VOS_INT AT_RcvFromAppSock(
    VOS_UINT8                           ucPortNo,
    VOS_UINT8                          *pData,
    VOS_UINT16                          uslength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;

    if (VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("AT_RcvFromAppSock: pData is NULL PTR!");
        return VOS_ERR;
    }

    if (0 == uslength)
    {
        AT_WARN_LOG("AT_RcvFromAppSock: uslength is 0!");
        return VOS_ERR;
    }

    if (AT_APP_SOCK_PORT_NO != ucPortNo)
    {
        AT_WARN_LOG("AT_RcvFromAppSock: Port No ERR!");
        return VOS_ERR;
    }

    if ( (AT_APP_SOCK_USER != gastAtClientTab[ucIndex].UserType)
       ||(AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed))
    {
        AT_WARN_LOG("AT_RcvFromAppSock: SOCK client is unused!");
        return VOS_ERR;
    }

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        ulRet = At_CmdStreamPreProc(ucIndex,pData,uslength);
    }
    else
    {
        ulRet = At_DataStreamPreProc(ucIndex,gastAtClientTab[ucIndex].DataMode,pData,uslength);
    }

    if ( AT_SUCCESS == ulRet )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_AppSockComEst
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��E5 sock��·�ĳ�ʼ������
 �������  : ucPortNo    - �˿ں�
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��3��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id

  3.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_INT32 AT_AppSockComEst(VOS_UINT8 ucPortNo)
{
    /* Modified by L60609 for AT Project��2011-10-04,  Begin*/
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;

    if (AT_APP_SOCK_PORT_NO != ucPortNo)
    {
         AT_WARN_LOG("AT_E5SockComEst the PortNo is error)");
        return VOS_ERR;
    }

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_APPSOCK, ID_AT_MNTN_RESULT_APPSOCK);

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_APPSOCK;
    gastAtClientTab[ucIndex].ucPortNo        = ucPortNo;
    gastAtClientTab[ucIndex].UserType        = AT_APP_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    /* Modified by s62952 for AT Project��2011-10-17,  Begin*/
    /*��DMSע��Ӵ����л�ȡ���ݵĻص�����*/
    (VOS_VOID)App_VcomRecvCallbackRegister(ucPortNo, (pComRecv)AT_RcvFromAppSock);
    /* Modified by s62952 for AT Project��2011-10-17,  end*/

    /* Modified by L60609 for AT Project��2011-10-04,  End*/

    return VOS_OK;
}

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/******************************************************************************
 �� �� ��  : At_UsbGetWwanMode
 ��������  : �����ȡNDIS��ǰģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1 : WCDMA
             2 : CDMA

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_UINT32 At_UsbGetWwanMode(VOS_VOID)
{
    return WWAN_WCDMA;
}

/*****************************************************************************
 �� �� ��  : AT_UsbNcmConnStatusChgCB
 ��������  : NDIS��������״̬���ص�
 �������  : enStatus --- ����״̬
             pBuffer  --- ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_UsbNcmConnStatusChgCB(NCM_IOCTL_CONNECT_STUS_E enStatus, VOS_VOID *pBuffer)
{
    AT_MSG_STRU                        *pstMsg = VOS_NULL_PTR;

    /*
     * ���������Ͽ��ڲ���Ϣ, �����������
     */

    if (NCM_IOCTL_STUS_BREAK == enStatus)
    {
        /* ����OSA��Ϣ */
        pstMsg = (AT_MSG_STRU *)AT_ALLOC_MSG_WITH_HDR(sizeof(AT_MSG_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            AT_ERR_LOG("AT_UsbNcmConnStatusChgCB: Alloc message failed!");
            return;
        }

        /* �����Ϣ���� */
        PS_MEM_SET(AT_GET_MSG_ENTITY(pstMsg), 0x00, AT_GET_MSG_LENGTH(pstMsg));

        /* ��д��Ϣͷ */
        AT_CFG_INTRA_MSG_HDR(pstMsg, ID_AT_NCM_CONN_STATUS_CMD);

        /* ��д��Ϣ���� */
        pstMsg->ucType  = AT_NCM_CONN_STATUS_MSG;
        pstMsg->ucIndex = AT_CLIENT_TAB_NDIS_INDEX;

        /* ������Ϣ */
        AT_SEND_MSG(pstMsg);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : At_RcvFromNdisCom
 ��������  : NDISע���Ӧ�õĽӿڣ����ڽ���AT����
 �������  : ucPortNo    - �˿ں�
             *pucData    - ָ�����ݵ�ָ��
             uslength    - ���ݳ���
 �������  : ��
 �� �� ֵ  : AT_SUCCESS --- �ɹ�
             AT_FAILURE --- ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��3��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT AT_RcvFromNdisCom(
    VOS_UINT8                           *pucData,
    VOS_UINT16                          uslength
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ������� */
    if (VOS_NULL_PTR == pucData)
    {
        AT_WARN_LOG("At_RcvFromNdisCom: pData is NULL PTR!");
        return VOS_ERR;
    }

    /* ������� */
    if (0 == uslength)
    {
        AT_WARN_LOG("At_RcvFromNdisCom: uslength is 0!");
        return VOS_ERR;
    }

    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;

    /* NDIS��·û�н��� */
    if ( (AT_NDIS_USER != gastAtClientTab[ucIndex].UserType)
       ||(AT_CLIENT_NULL == gastAtClientTab[ucIndex].ucUsed))
    {
        AT_WARN_LOG("At_RcvFromNdisCom: NDIS is unused");
        return VOS_ERR;
    }

    /*����NDISͨ��״̬Ϊ���ϱ�����*/
    DMS_SetNdisChanStatus(ACM_EVT_DEV_READY);

    if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        ulRet = At_CmdStreamPreProc(ucIndex,pucData,uslength);
    }
    else
    {
        ulRet = At_DataStreamPreProc(ucIndex,gastAtClientTab[ucIndex].DataMode,pucData,uslength);
    }

    if ( AT_SUCCESS == ulRet )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_UsbNdisEst
 ��������  : AT PID�ڳ�ʼ��ʱ����Ҫִ��6.2 �汾NDIS AT��·�ĳ�ʼ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             AT_SUCCESS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-08-31
    ��    ��   : L47619
    �޸�����   : Created function

  2.��    ��   : 2011��10��3��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ɾ��At_RegTafCallBackFunc;��̬���� client id

  3.��    ��   : 2013��11��06��
    ��    ��   : j00174725
    �޸�����   : V3R3 �ڴ�ü�
*****************************************************************************/
VOS_UINT32 AT_UsbNdisEst(VOS_VOID)
{
    /* Modified by L60609 for AT Project��2011-10-04,  Begin*/
    VOS_UINT8                           ucIndex;

    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;

    /* ��ն�Ӧ���� */
    PS_MEM_SET(&gastAtClientTab[ucIndex],0x00,sizeof(AT_CLIENT_MANAGE_STRU));

    AT_ConfigTraceMsg(ucIndex, ID_AT_CMD_NDIS, ID_AT_MNTN_RESULT_NDIS);

    /* ��д�û����� */
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_NDIS;
    gastAtClientTab[ucIndex].ucPortNo        = AT_NDIS_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* ���¿��Բ�����д��ǰ��PS_MEMSET�Ѿ���ʼ����ֻΪ�ɿ���� */
    gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
    gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
    gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
    gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;

    /*��ʼ��NDIS ADDR����*/
    PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : AT_OpenUsbNdis
��������  : ��NCM�豸
�������  : VOS_VOID
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��22��
   ��    ��   : c00173809
   �޸�����   : PS�ں���Ŀ���� NCM �豸
*****************************************************************************/
VOS_VOID AT_OpenUsbNdis(VOS_VOID)
{
    UDI_OPEN_PARAM_S                    stParam;
    VOS_UINT32                          ulRst;

    stParam.devid   = UDI_NCM_NDIS_ID;

    /* ��Device�����ID */
    g_ulAtUdiNdisHdl = mdrv_udi_open(&stParam);

    if (UDI_INVALID_HANDLE == g_ulAtUdiNdisHdl)
    {
        AT_ERR_LOG("AT_OpenUsbNdis, ERROR, Open usb ndis device failed!");

        return;
    }

    /* ע��DMS�ص�����ָ�� */
    /*lint -e732   ���Ͳ�ͳһ����ʱע����ȷ�Ͻӿ��ٽ��*/
    ulRst =  DMS_USB_NAS_REGFUNC((USBNdisStusChgFunc)AT_UsbNcmConnStatusChgCB,
                                 (USB_NAS_AT_CMD_RECV)AT_RcvFromNdisCom,
                                 (USB_NAS_GET_WWAN_MODE)At_UsbGetWwanMode);
    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG("AT_OpenUsbNdis, ERROR, Reg NCM failed!");

        return;
    }
    /*lint +e732*/
    /* Modified by L60609 for AT Project��2011-10-04,  End*/

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CloseUsbNdis
 ��������  : �ر�NCM�豸
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ���ر� NCM �豸

  2.��    ��   : 2015��9��5��
    ��    ��   : A00165503
    �޸�����   : DTS2015090105100: NDIS���������޷��Ͽ�����
*****************************************************************************/
VOS_VOID AT_CloseUsbNdis(VOS_VOID)
{
    /* �Ͽ�NDIS�������� */
    AT_UsbNcmConnStatusChgCB(NCM_IOCTL_STUS_BREAK, VOS_NULL_PTR);

    if (UDI_INVALID_HANDLE != g_ulAtUdiNdisHdl)
    {
        mdrv_udi_close(g_ulAtUdiNdisHdl);

        g_ulAtUdiNdisHdl = UDI_INVALID_HANDLE;
    }

    return;
}

/* Added by L60609 for MUX��2012-08-03,  Begin */
/*****************************************************************************
 �� �� ��  : AT_GetMuxSupportFlg
 ��������  : ��ȡ�Ƿ�֧��MUX�ı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��9��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT8 AT_GetMuxSupportFlg(VOS_VOID)
{
    return AT_GetCommCtxAddr()->stMuxCtx.ucMuxSupportFlg;
}

/*****************************************************************************
 �� �� ��  : AT_SetMuxSupportFlg
 ��������  : �����Ƿ�֧��MUX�ı�־
 �������  : VOS_UINT8 ucMuxSupportFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��9��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_VOID AT_SetMuxSupportFlg(VOS_UINT8 ucMuxSupportFlg)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    pstCommCtx->stMuxCtx.ucMuxSupportFlg = ucMuxSupportFlg;
}

/*****************************************************************************
 �� �� ��  : AT_CheckMuxDlci
 ��������  : ���DLCI����Ч��
 �������  : AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckMuxDlci(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci)
{
    /* �˴ο���ֻ֧��8��ͨ����DLCI��1��8����1-8��Χ�ķ���VOS_OK�����򷵻�VOS_ERR */
    if ((enDlci >= AT_MUX_DLCI1_ID)
     && (enDlci < (AT_MUX_DLCI1_ID + AT_MUX_AT_CHANNEL_MAX)))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : AT_CheckMuxUser
 ��������  : ��鵱ǰ�����·��˿��Ƿ�ΪMUXͨ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��3��
    ��    ��   : L60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckMuxUser(VOS_UINT8 ucIndex)
{
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_IsHsicOrMuxUser
 ��������  : �ж��Ƿ�ΪHSIC�˿ڻ���MUX�˿�
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_IsHsicOrMuxUser(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;

    ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
    ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);

    /* �Ȳ���HSIC�˿ڣ�Ҳ����MUX�˿� */
    if ((VOS_FALSE == ulHsicUserFlg)
     && (VOS_FALSE == ulMuxUserFlg))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : AT_GetMuxDlciFromClientIdx
 ��������  : ����client index��ȡMUX��dlciֵ
 �������  : VOS_UINT8                           ucIndex
             AT_MUX_DLCI_TYPE_ENUM_UINT8        *penDlci
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��4��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_GetMuxDlciFromClientIdx(
    VOS_UINT8                           ucIndex,
    AT_MUX_DLCI_TYPE_ENUM_UINT8        *penDlci
)
{
    VOS_UINT8                           ucLoop;

    for (ucLoop = 0; ucLoop < AT_MUX_AT_CHANNEL_MAX; ucLoop++)
    {
        if (ucIndex == AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].enAtClientTabIdx)
        {
            *penDlci = AT_GetCommCtxAddr()->stMuxCtx.astMuxClientTab[ucLoop].enDlci;
            break;
        }
    }

    if (ucLoop >= AT_MUX_AT_CHANNEL_MAX)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : AT_CheckPcuiCtrlConcurrent
 ��������  : �ж�PCUI��CTRL���Ƿ񲢷�
 �������  : VOS_UINT8
             VOS_UINT8
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : z00220246
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 AT_CheckPcuiCtrlConcurrent(
    VOS_UINT8                           ucIndexOne,
    VOS_UINT8                           ucIndexTwo
)
{
    VOS_UINT32                          ulUserFlg1;
    VOS_UINT32                          ulUserFlg2;

    ulUserFlg1 = AT_CheckUserType(ucIndexOne, AT_USBCOM_USER);
    ulUserFlg1 |= AT_CheckUserType(ucIndexOne, AT_CTR_USER);
    ulUserFlg1 |= AT_CheckUserType(ucIndexOne, AT_PCUI2_USER);

    if (VOS_TRUE != ulUserFlg1)
    {
        return VOS_FALSE;
    }

    ulUserFlg2 = AT_CheckUserType(ucIndexTwo, AT_USBCOM_USER);
    ulUserFlg2 |= AT_CheckUserType(ucIndexTwo, AT_CTR_USER);
    ulUserFlg2 |= AT_CheckUserType(ucIndexTwo, AT_PCUI2_USER);

    if (VOS_TRUE != ulUserFlg2)
    {
        return VOS_FALSE;
    }

    if (gastAtClientTab[ucIndexOne].UserType != gastAtClientTab[ucIndexTwo].UserType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_IsConcurrentPorts
 ��������  : �ж������˿��Ƿ���Բ���
 �������  : VOS_UINT8                           ucIndexOne
             VOS_UINT8                           ucIndexTwo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��3��
    ��    ��   : L60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��29��
    ��    ��   : f00179208
    �޸�����   : DSDA:���� VCOM ATͨ���Ĳ���ִ��
*****************************************************************************/
VOS_UINT32 AT_IsConcurrentPorts(
    VOS_UINT8                           ucIndexOne,
    VOS_UINT8                           ucIndexTwo
)
{
    VOS_UINT32                          ulMuxUserFlg1;
    VOS_UINT32                          ulHsicUserFlg1;
    VOS_UINT32                          ulAppUserFlg1;
    VOS_UINT32                          ulMuxUserFlg2;
    VOS_UINT32                          ulHsicUserFlg2;
    VOS_UINT32                          ulAppUserFlg2;

    /* ͬһ��ͨ����֧�ֲ���������㺯����֤ */
    ulMuxUserFlg1  = AT_CheckMuxUser(ucIndexOne);
    ulHsicUserFlg1 = AT_CheckHsicUser(ucIndexOne);
    ulAppUserFlg1  = AT_CheckAppUser(ucIndexOne);

    ulMuxUserFlg2  = AT_CheckMuxUser(ucIndexTwo);
    ulHsicUserFlg2 = AT_CheckHsicUser(ucIndexTwo);
    ulAppUserFlg2  = AT_CheckAppUser(ucIndexTwo);

    /* ͨ��1��HSICͨ����MUXͨ��,ͨ��2Ҳ��HSICͨ����MUXͨ�� */
    if ((VOS_TRUE == ulMuxUserFlg1)
     || (VOS_TRUE == ulHsicUserFlg1))
    {
        if ((VOS_TRUE == ulMuxUserFlg2)
         || (VOS_TRUE == ulHsicUserFlg2))
        {
            return VOS_TRUE;
        }
    }

    /* ͨ��1��APPͨ��,ͨ��2Ҳ��APPͨ�� */
    if (VOS_TRUE == ulAppUserFlg1)
    {
        if (VOS_TRUE == ulAppUserFlg2)
        {
            return VOS_TRUE;
        }
    }

    /* PCUI��CTRL�ڲ����жϣ����������� */
    if (VOS_TRUE == AT_GetPcuiCtrlConcurrentFlag())
    {
        if (VOS_TRUE == AT_CheckPcuiCtrlConcurrent(ucIndexOne, ucIndexTwo))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_MuxCmdStreamEcho
 ��������  : MUXͨ������Ԥ�������
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID AT_MuxCmdStreamEcho(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;
    VOS_UINT32                          ulRslt;

    enDlci = AT_MUX_DLCI_TYPE_BUTT;

    ulRslt = AT_GetMuxDlciFromClientIdx(ucIndex, &enDlci);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    MUX_DlciDlDataSend(enDlci, pData, usLen);
    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    return;
}

/*****************************************************************************
 �� �� ��  : AT_MemSingleCopy
 ��������  : ��ȡ�����ڴ浥Ԫʵ��ʹ�õ����ֽ�������������������
 �������  : pMemSrc  -- Ҫ��ȡ���ݵ�TTF�ڴ��ͷָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_MemSingleCopy(
    VOS_UINT8                          *pucDest,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulLen
)
{
    /* ʹ�õ��ڴ����Ϊ����Cache������ʹ��DM */
    mdrv_memcpy(pucDest, pucSrc, (unsigned long)ulLen);

    return;
}

/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  Begin */

/*****************************************************************************
 �� �� ��  : AT_SendMuxSelResultData
 ��������  : AT��MUX���������ϱ�������
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA Phase III
*****************************************************************************/
VOS_UINT32 AT_SendMuxSelResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT8                           ucLoop;
    AT_COMM_CTX_STRU                   *pCommCtx = VOS_NULL_PTR;

    pCommCtx = AT_GetCommCtxAddr();

    /* ƥ���Ƿ�ΪMUX��index */
    for (ucLoop = 0; ucLoop < AT_MUX_AT_CHANNEL_MAX; ucLoop++)
    {
        if (ucIndex == pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enAtClientTabIdx)
        {
            break;
        }
    }

    if (ucLoop >= AT_MUX_AT_CHANNEL_MAX)
    {
        return VOS_ERR;
    }

    /* ��ͨ�������������ϱ�AT���� */
    if (AT_HSIC_REPORT_OFF == pCommCtx->stMuxCtx.astMuxClientTab[ucLoop].enRptType)
    {
        return VOS_ERR;
    }

    AT_SendMuxResultData(ucIndex, pData, usLen);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SendMuxResultData
 ��������  : AT��MUX���ͽ������
 �������  : VOS_UINT8                           ucIndex
             VOS_UINT8                          *pData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SendMuxResultData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;
    VOS_UINT32                          ulRslt;

    enDlci = AT_MUX_DLCI_TYPE_BUTT;

    /* MUX�����Ƿ�֧�֣���֧��ֱ�ӷ���ʧ�� */
    if (VOS_TRUE != AT_GetMuxSupportFlg())
    {
        return AT_FAILURE;
    }

    /* ��ȡDlci */
    ulRslt = AT_GetMuxDlciFromClientIdx(ucIndex, &enDlci);

    if (VOS_TRUE != ulRslt)
    {
        return AT_FAILURE;
    }

    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    /* ��MUX�������� */
    MUX_DlciDlDataSend(enDlci, pData, usLen);

    return AT_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : AT_SndDipcPdpActInd
 ��������  : AT��DIPCͨ������PDP������Ϣ
 �������  : ucCid          ----  CID
             ucRabId        ----  RABID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SndDipcPdpActInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                      ulLength;
    AT_DIPC_PDP_ACT_STRU           *pstAtDipcPdpAct;
    AT_MODEM_PS_CTX_STRU           *pstPsModemCtx = VOS_NULL_PTR;

    ulLength        = sizeof( AT_DIPC_PDP_ACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpAct = ( AT_DIPC_PDP_ACT_STRU *)PS_ALLOC_MSG( WUEPS_PID_AT, ulLength );

    if ( VOS_NULL_PTR == pstAtDipcPdpAct )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        AT_WARN_LOG( "AT_SndDipcPdpActInd:ERROR:Allocates a message packet for AT_DIPC_PDP_ACT_STRU FAIL!" );
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    /*��д��Ϣͷ:*/
    pstAtDipcPdpAct->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpAct->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpAct->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpAct->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pstAtDipcPdpAct->enMsgType       = ID_AT_DIPC_PDP_ACT_IND;
    pstAtDipcPdpAct->ucRabId         = ucRabId;
    pstAtDipcPdpAct->enUdiDevId      = (UDI_DEVICE_ID_E)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_AT, pstAtDipcPdpAct ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        AT_WARN_LOG( "AT_SndDipcPdpActInd:WARNING:SEND AT_DIPC_PDP_ACT_STRU msg FAIL!" );
    }

    return;
}



/*****************************************************************************
 �� �� ��  : AT_SndDipcPdpDeactInd
 ��������  : AT��DIPCͨ������PDPȥ������Ϣ
 �������  : ucRabId        ----  RABID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SndDipcPdpDeactInd(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                      ulLength;
    AT_DIPC_PDP_DEACT_STRU         *pstAtDipcPdpDeact;

    ulLength          = sizeof( AT_DIPC_PDP_DEACT_STRU ) - VOS_MSG_HEAD_LENGTH;
    pstAtDipcPdpDeact = ( AT_DIPC_PDP_DEACT_STRU *)PS_ALLOC_MSG( WUEPS_PID_AT, ulLength );

    if ( VOS_NULL_PTR == pstAtDipcPdpDeact )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        AT_WARN_LOG( "AT_SndDipcPdpDeactInd:ERROR:Allocates a message packet for AT_DIPC_PDP_DEACT_STRU FAIL!" );
        return;
    }

    /*��д��Ϣͷ:*/
    pstAtDipcPdpDeact->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulSenderPid     = WUEPS_PID_AT;
    pstAtDipcPdpDeact->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAtDipcPdpDeact->ulReceiverPid   = PS_PID_APP_DIPC;
    pstAtDipcPdpDeact->ulLength        = ulLength;
    /*��д��Ϣ��:*/
    pstAtDipcPdpDeact->enMsgType       = ID_AT_DIPC_PDP_REL_IND;
    pstAtDipcPdpDeact->ucRabId         = ucRabId;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_AT, pstAtDipcPdpDeact ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        AT_WARN_LOG( "AT_SndDipcPdpDeactInd:WARNING:SEND AT_DIPC_PDP_DEACT_STRU msg FAIL!" );
    }

    return;
}


/*****************************************************************************
 �� �� ��  : AT_SetAtChdataCidActStatus
 ��������  : AP-MODEM��̬������g_astAtChdataCfg��ָ��CID��PDP�ļ���״̬
 �������  : ucCid      ----      ָ��CID
             ulIsCidAct ----      ָ��CID��PDP�ļ���״̬
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_SetAtChdataCidActStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulIsCidAct
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* ���CID�Ϸ��� */
    if ( ucCid > TAF_MAX_CID_NV)
    {
        AT_ERR_LOG1("AT_SetAtChdataCidActStatus, WARNING, CID error:%d\r\n", ucCid);
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    /* ���CID������ͨ����ӳ���ϵ */
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg = ulIsCidAct;

    return;
}



/*****************************************************************************
 �� �� ��  : AT_CleanAtChdataCfg
 ��������  : AP-MODEM��̬����CID������ͨ����ӳ���ϵ���
 �������  :
             ucCid      ----      ָ��CID
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��17��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_CleanAtChdataCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
)
{
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* ���CID�Ϸ��� */
    if ( ucCid > TAF_MAX_CID_NV)
    {
        AT_ERR_LOG1("AT_CleanAtChdataCfg, WARNING, CID error:%d\r\n", ucCid);
        return;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(usClientId);

    /* ���CID������ͨ����ӳ���ϵ */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = AT_PS_INVALID_RMNET_ID;

    /* ��ָ��CID��PDP�ļ���״̬����Ϊδ����̬ */
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
 �� �� ��  : AT_CheckHsicUser
 ��������  : ��鵱ǰ�����·��˿��Ƿ�ΪHSICͨ��
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��18��
    ��    ��   : l00198894
    �޸�����   : AP-Modem����������Ŀ�޸�
  3.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32 AT_CheckHsicUser(VOS_UINT8 ucIndex)
{
    return VOS_FALSE;

}

/* Added by l60609 for AP������Ŀ ��2012-09-10 Begin */
/*****************************************************************************
 �� �� ��  : AT_CheckAppUser
 ��������  : ��鵱ǰ�����·��˿��Ƿ�ΪAPPͨ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��10��
    ��    ��   : L60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_CheckAppUser(VOS_UINT8 ucIndex)
{
    if (AT_APP_USER != gastAtClientTab[ucIndex].UserType)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}
/* Added by l60609 for AP������Ŀ ��2012-09-10 End */

/*****************************************************************************
 �� �� ��  : AT_CheckNdisUser
 ��������  : ��鵱ǰ�����·��˿��Ƿ�ΪNDISͨ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��2��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckNdisUser(VOS_UINT8 ucIndex)
{
    if (AT_NDIS_USER != gastAtClientTab[ucIndex].UserType)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : AT_CheckHsUartUser
 ��������  : �ж��Ƿ�ΪUART�˿�
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : z00189113
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AT_CheckHsUartUser(VOS_UINT8 ucIndex)
{

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : AT_CheckModemUser
 ��������  : �ж��Ƿ�ΪMODEM�˿�
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : z00189113
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AT_CheckModemUser(VOS_UINT8 ucIndex)
{
    if (AT_MODEM_USER != gastAtClientTab[ucIndex].UserType)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : AT_CheckUserType
 ��������  : ���Indexͨ����UserType
 �������  : VOS_UINT8            ucIndex
             AT_USER_TYPE         enUserType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckUserType(
    VOS_UINT8                               ucIndex,
    AT_USER_TYPE                            enUserType
)
{
    if (enUserType != gastAtClientTab[ucIndex].UserType)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : AT_InitFcMap
��������  : ��ʼ��g_stFcIdMaptoFcPri
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2012��2��17��
   ��    ��   : L47619
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : C�˵�����λ��Ŀ
*****************************************************************************/
VOS_VOID AT_InitFcMap(VOS_VOID)
{
    VOS_UINT8       ucLoop;

    /* ��ʼ��g_stFcIdMaptoFcPri */
    for (ucLoop = 0; ucLoop < FC_ID_BUTT; ucLoop++)
    {
        g_stFcIdMaptoFcPri[ucLoop].ulUsed  = VOS_FALSE;
        g_stFcIdMaptoFcPri[ucLoop].enFcPri = FC_PRI_BUTT;
        g_stFcIdMaptoFcPri[ucLoop].ulRabIdMask  = 0;
        g_stFcIdMaptoFcPri[ucLoop].enModemId    = MODEM_ID_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SendDiagCmdFromOm
 ��������  : UE���OM���øýӿ��������PC�๤�߷���DIAG����Ĺ���
 �������  : VOS_UINT8    ucPortNo  --    �˿ں�
             VOS_UINT8    ucType    --    ����ģʽ
             VOS_UINT8   *pData     --    ����DIAG���������ָ��
             VOS_UINT16   uslength  --    ����DIAG��������ݳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 1.��    ��   : 2008��6��09��
   ��    ��   : L47619
   �޸�����   : �����ɺ���

 2.��    ��   : 2010��9��27��
   ��    ��   : A00165503
   �޸�����   : ���ӷ������ݶ˿ڲ���

 3.��    ��   : 2011��10��24��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: ��̬���� client id

*****************************************************************************/
VOS_UINT32 AT_SendDiagCmdFromOm(
    VOS_UINT8                           ucPortNo,
    VOS_UINT8                           ucType,
    VOS_UINT8                          *pData,
    VOS_UINT16                          uslength
)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SendPcuiDataFromOm
 ��������  : �ṩ��OM��PCUI�ڷ������ݽӿ�
 �������  : pucVirAddr - �����������������ַ
             pucPhyAddr - ��������������ʵ��ַ
             ulLength   - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SendPcuiDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
)
{
    if (AT_SUCCESS != At_SendData(AT_CLIENT_TAB_PCUI_INDEX,
                                  gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].DataMode,
                                  pucVirAddr,
                                  (VOS_UINT16)ulLength))
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SendCtrlDataFromOm
 ��������  : �ṩ��OM��CTRL�ڷ������ݽӿ�
 �������  : pucVirAddr - �����������������ַ
             pucPhyAddr - ��������������ʵ��ַ
             ulLength   - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SendCtrlDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
)
{
    if (AT_SUCCESS != At_SendData(AT_CLIENT_TAB_CTRL_INDEX,
                                  gastAtClientTab[AT_CLIENT_TAB_CTRL_INDEX].DataMode,
                                  pucVirAddr,
                                  (VOS_UINT16)ulLength))
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SendPcui2DataFromOm
 ��������  : �ṩ��OM��Pcui2�ڷ������ݽӿ�
 �������  : pucVirAddr - �����������������ַ
             pucPhyAddr - ��������������ʵ��ַ
             ulLength   - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 AT_SendPcui2DataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
)
{
    if (AT_SUCCESS != At_SendData(AT_CLIENT_TAB_PCUI2_INDEX,
                                  gastAtClientTab[AT_CLIENT_TAB_PCUI2_INDEX].DataMode,
                                  pucVirAddr,
                                  (VOS_UINT16)ulLength))
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}


/*****************************************************************************
 �� �� ��  : AT_QuerySndFunc
 ��������  : �ṩ��OM��ѯ�������ݵĺ����ӿ�
 �������  : AT_PHY_PORT_ENUM_UINT32 ulPhyPort
 �������  : ��
 �� �� ֵ  : pAtDataSndFunc
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��10��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��12��02��
    ��    ��   : j00174725
    �޸�����   : ����UARTУ׼
*****************************************************************************/
CPM_SEND_FUNC AT_QuerySndFunc(AT_PHY_PORT_ENUM_UINT32 ulPhyPort)
{
    switch(ulPhyPort)
    {
        case AT_UART_PORT:
            return AT_UART_SendRawDataFromOm;

        case AT_PCUI_PORT:
            return AT_SendPcuiDataFromOm;

        case AT_CTRL_PORT:
            return AT_SendCtrlDataFromOm;


        default:
            AT_WARN_LOG("AT_QuerySndFunc: don't proc data of this port!");
            return VOS_NULL_PTR;
    }
}

/*****************************************************************************
 Prototype      : At_SendCmdMsg
 Description    : AT���������ַ���
 Input          : ucIndex --- �û�ID
                  pData   --- ����
                  usLen   --- ����
                  ucType  --- ��Ϣ����
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_SendCmdMsg (TAF_UINT8 ucIndex,TAF_UINT8* pData, TAF_UINT16 usLen,TAF_UINT8 ucType)
{
    AT_MSG_STRU                        *pMsg = TAF_NULL_PTR;
    AT_CMD_MSG_NUM_CTRL_STRU           *pstMsgNumCtrlCtx = VOS_NULL_PTR;
    VOS_UINT_PTR                        ulTmpAddr;
    VOS_UINT32                          ulLength;
    VOS_ULONG                           ulLockLevel;

    pstMsgNumCtrlCtx = AT_GetMsgNumCtrlCtxAddr();

    if (VOS_NULL_PTR == pData)
    {
        AT_WARN_LOG("At_SendCmdMsg :pData is null ptr!");
        return AT_FAILURE;
    }

    if (0 == usLen)
    {
        AT_WARN_LOG("At_SendCmdMsg ulLength = 0");
        return AT_FAILURE;
    }

    if (AT_COM_BUFF_LEN < usLen)
    {
        AT_WARN_LOG("At_SendCmdMsg ulLength > AT_COM_BUFF_LEN");
        return AT_FAILURE;
    }

    /* �����Զ����ITEM����4���ֽ� */
    AT_GetAtMsgStruMsgLength(usLen, &ulLength);
    pMsg = (AT_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);
    if ( pMsg == TAF_NULL_PTR )
    {
        AT_ERR_LOG("At_SendCmdMsg:ERROR:Alloc Msg");
        return AT_FAILURE;
    }

    if (AT_NORMAL_TYPE_MSG == ucType)
    {
        /* ���м��� */
        /*lint -e571*/
        VOS_SpinLockIntLock(&(pstMsgNumCtrlCtx->stSpinLock), ulLockLevel);
        /*lint +e571*/

        if (pstMsgNumCtrlCtx->ulMsgCount > AT_MAX_MSG_NUM)
        {
            VOS_SpinUnlockIntUnlock(&(pstMsgNumCtrlCtx->stSpinLock), ulLockLevel);

            /* �ͷŷ�����ڴ�ռ� */
            PS_FREE_MSG(WUEPS_PID_AT, pMsg);

            return AT_FAILURE;
        }

        pstMsgNumCtrlCtx->ulMsgCount++;

        VOS_SpinUnlockIntUnlock(&(pstMsgNumCtrlCtx->stSpinLock), ulLockLevel);
    }

    /* �������ػ����ʵ��������pMsg->aucValue;*/
    pMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid       = WUEPS_PID_AT;
    pMsg->ulReceiverPid     = WUEPS_PID_AT;

    if (AT_COMBIN_BLOCK_MSG == ucType)
    {
        pMsg->enMsgId = ID_AT_COMBIN_BLOCK_CMD;
    }
    else
    {
        pMsg->enMsgId = AT_GetCmdMsgID(ucIndex);
    }

    pMsg->ucType            = ucType;     /* ���� */
    pMsg->ucIndex           = ucIndex;    /* ���� */
    pMsg->usLen             = usLen;    /* ���� */

    PS_MEM_SET(pMsg->aucValue, 0, sizeof(pMsg->aucValue));
    AT_GetUserTypeFromIndex(ucIndex, &pMsg->ucUserType);
    PS_MEM_SET(pMsg->aucReserved, 0x00, sizeof(pMsg->aucReserved));

    /* ��д����Ϣ���� */
    ulTmpAddr = (VOS_UINT_PTR)(pMsg->aucValue);
    PS_MEM_CPY((VOS_VOID*)ulTmpAddr, pData, usLen);  /* ���� */

    /*������Ϣ��AT_PID;*/
    if ( 0 != PS_SEND_MSG( WUEPS_PID_AT, pMsg ) )
    {
        AT_ERR_LOG("At_SendCmdMsg:ERROR:VOS_SendMsg");

        /* ������Ϣ����ʧ��ʱ���ᴥ��������λ���ʴ˴�����ulMsgCount--���� */

        return AT_FAILURE;
    }
    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_IsApPort
 ��������  : �ж��Ƿ�ΪHSIC�˿ڡ�MUX�˿ڻ���VCOMͨ������APPʹ�õ�ͨ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��14��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_IsApPort(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulHsicUserFlg;
    VOS_UINT32                          ulMuxUserFlg;
    VOS_UINT32                          ulVcomUserFlg;
    VOS_UINT8                          *pucSystemAppConfig;

    if (0 == g_stAtDebugInfo.ucUnCheckApPortFlg)
    {
        /* ��ʼ�� */
        pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

        ulHsicUserFlg = AT_CheckHsicUser(ucIndex);
        ulMuxUserFlg  = AT_CheckMuxUser(ucIndex);
        ulVcomUserFlg = AT_CheckAppUser(ucIndex);

        if (SYSTEM_APP_ANDROID == *pucSystemAppConfig)
        {
            /* ������ֻ���̬����Ҫ�ж�HSIC�˿ڣ�MUX�˿ڣ�VCOM�˿� */
            if ((VOS_FALSE == ulHsicUserFlg)
             && (VOS_FALSE == ulMuxUserFlg)
             && (VOS_FALSE == ulVcomUserFlg))
            {
                return VOS_FALSE;
            }
        }
        else
        {
            /* ������ֻ���̬����Ҫ�ж�HSIC�˿ڣ�MUX�˿� */
            if ((VOS_FALSE == ulHsicUserFlg)
             && (VOS_FALSE == ulMuxUserFlg))
            {
                return VOS_FALSE;
            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : AT_ProcCCpuResetBefore
 ��������  : C�˵�����λǰ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��13��
   ��    ��   : j00174725
   �޸�����   : ������ϢID
 3.��    ��   : 2016��01��22��
   ��    ��   : z00301431
   �޸�����   : DTS2015103001118,set modemstatus
*****************************************************************************/
VOS_INT AT_ProcCCpuResetBefore(VOS_VOID)
{
    AT_MSG_STRU                        *pstMsg = VOS_NULL_PTR;

    printk("\n AT_ProcCCpuResetBefore enter, %u \n", VOS_GetSlice());

    /* ���ô��ڸ�λǰ�ı�־ */
    AT_SetResetFlag(VOS_TRUE);

    DMS_InitModemStatus();

    /* ���TAFAGENT���е��ź��� */
    TAF_AGENT_ClearAllSem();

    /* ������Ϣ */
    pstMsg = (AT_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                                         sizeof(AT_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        printk("\n AT_ProcCCpuResetBefore alloc msg fail, %u \n", VOS_GetSlice());
        return VOS_ERROR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;
    pstMsg->ucType                      = ID_CCPU_AT_RESET_START_IND;

    pstMsg->enMsgId                     = ID_AT_COMM_CCPU_RESET_START;

    /* ����Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        printk("\n AT_ProcCCpuResetBefore send msg fail, %u \n", VOS_GetSlice());
        return VOS_ERROR;
    }

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ���Ϣ��������ź��������� */
    if (VOS_OK != VOS_SmP(AT_GetResetSem(), AT_RESET_TIMEOUT_LEN))
    {
        printk("\n AT_ProcCCpuResetBefore VOS_SmP fail, %u \n", VOS_GetSlice());
        AT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        return VOS_ERROR;
    }

    /* ��¼��λǰ�Ĵ��� */
    AT_DBG_SAVE_CCPU_RESET_BEFORE_NUM(1);

    printk("\n AT_ProcCCpuResetBefore succ, %u \n", VOS_GetSlice());

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_ProcCCpuResetAfter
 ��������  : C�˵�����λǰ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��13��
   ��    ��   : j00174725
   �޸�����   : ������ϢID
*****************************************************************************/
VOS_INT AT_ProcCCpuResetAfter(VOS_VOID)
{
    AT_MSG_STRU                        *pstMsg = VOS_NULL_PTR;

    printk("\n AT_ProcCCpuResetAfter enter, %u \n", VOS_GetSlice());

    /* ������Ϣ */
    pstMsg = (AT_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                                         sizeof(AT_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        printk("\n AT_ProcCCpuResetAfter alloc msg fail, %u \n", VOS_GetSlice());
        return VOS_ERROR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;
    pstMsg->ucType                      = ID_CCPU_AT_RESET_END_IND;

    pstMsg->enMsgId                     = ID_AT_COMM_CCPU_RESET_END;

    /* ����Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        printk("\n AT_ProcCCpuResetAfter send msg fail, %u \n", VOS_GetSlice());
        return VOS_ERROR;
    }

    /* ��¼��λ��Ĵ��� */
    AT_DBG_SAVE_CCPU_RESET_AFTER_NUM(1);

    printk("\n AT_ProcCCpuResetAfter succ, %u \n", VOS_GetSlice());

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_CCpuResetCallback
 ��������  : C�˵�����λʱAT�Ļص�������
 �������  : enParam    -- 0��ʾ��λǰ�� ������ʾ��λ��
             iUserData  -- �û�����
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��17��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT AT_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             iUserData
)
{
    /* ��λǰ */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        return AT_ProcCCpuResetBefore();
    }
    /* ��λ�� */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        return AT_ProcCCpuResetAfter();
    }
    else
    {
        return VOS_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_HifiResetCallback
 ��������  : HIFI������λʱAT�Ļص�������
 �������  : lResetId -- 0��ʾ��λǰ�� ������ʾ��λ��
             iUserData
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��08��
   ��    ��   : L47619
   �޸�����   : Modified for HIFI Reset End Report
 3.��    ��   : 2013��11��13��
   ��    ��   : j00174725
   �޸�����   : ������ϢID
*****************************************************************************/
VOS_INT AT_HifiResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             iUserData
)
{
    AT_MSG_STRU                        *pstMsg = VOS_NULL_PTR;

    /* ����Ϊ0��ʾ��λǰ���� */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        printk("\n AT_HifiResetCallback before reset enter, %u \n", VOS_GetSlice());
        /* ������Ϣ */
        pstMsg = (AT_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                                             sizeof(AT_MSG_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            printk("\n AT_HifiResetCallback before reset alloc msg fail, %u \n", VOS_GetSlice());
            return VOS_ERROR;
        }

        /* ��ʼ����Ϣ */
        PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   0x00,
                   (VOS_SIZE_T)(sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
        pstMsg->ulReceiverPid               = WUEPS_PID_AT;
        pstMsg->ucType                      = ID_HIFI_AT_RESET_START_IND;

        pstMsg->enMsgId                     = ID_AT_COMM_HIFI_RESET_START;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
        {
            printk("\n AT_HifiResetCallback after reset alloc msg fail, %u \n", VOS_GetSlice());
            return VOS_ERROR;
        }

        return VOS_OK;
    }
    /* ��λ�� */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        printk("\n AT_HifiResetCallback after reset enter, %u \n", VOS_GetSlice());
        /* ������Ϣ */
        pstMsg = (AT_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                                             sizeof(AT_MSG_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            printk("\n AT_HifiResetCallback after reset alloc msg fail, %u \n", VOS_GetSlice());
            return VOS_ERROR;
        }

        /* ��ʼ����Ϣ */
        PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
                   0x00,
                   (VOS_SIZE_T)(sizeof(AT_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
        pstMsg->ulReceiverPid               = WUEPS_PID_AT;
        pstMsg->ucType                      = ID_HIFI_AT_RESET_END_IND;

        pstMsg->enMsgId                     = ID_AT_COMM_HIFI_RESET_END;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
        {
            printk("\n AT_HifiResetCallback after reset send msg fail, %u \n", VOS_GetSlice());
            return VOS_ERROR;
        }
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}


/*****************************************************************************
�� �� ��  : AT_ModemeEnableCB
��������  : MODEM�豸ʹ��֪ͨ
�������  : ucEnable    ----  �Ƿ�ʹ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��05��25��
    ��    ��   : ����/00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID AT_ModemeEnableCB(
    VOS_UINT8                           ucIndex,
    PS_BOOL_ENUM_UINT8                  ucEnable
)
{
    /* �豸Ĭ�ϴ�����Ч״̬�������ݾ�ͨ�����ص����գ�
    �� �豸ʧЧʱ�����ݵ�ǰ״̬��֪ͨPPP���紦������̬��
       ��֪ͨATȥ����PDP.
    */
    if (PS_FALSE == ucEnable)
    {
        if (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        {
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_REQ);

            /* ��ԭ�ȿ��������أ�����ֹͣ���� */
            if (0 == (gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS))
            {
                AT_StopFlowCtrl(ucIndex);
            }

            /* �Ͽ����� */
            if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                         AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                         0,
                                         gastAtClientTab[ucIndex].ucCid))
            {
                AT_ERR_LOG("AT_ModemeEnableCB: TAF_PS_CallEnd failed in <AT_PPP_DATA_MODE>!");
                return;
            }
        }
        else if (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        {
            PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                                   PPP_AT_CTRL_REL_PPP_RAW_REQ);

            /* ��ԭ�ȿ��������أ�����ֹͣ���� */
            if (0 == (gastAtClientTab[ucIndex].ModemStatus & IO_CTRL_CTS))
            {
                AT_StopFlowCtrl(ucIndex);
            }

            /* �Ͽ����� */
            if ( VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                          AT_PS_BuildExClientId(gastAtClientTab[ucIndex].usClientId),
                                          0,
                                          gastAtClientTab[ucIndex].ucCid) )
            {
                AT_ERR_LOG("AT_ModemeEnableCB: TAF_PS_CallEnd failed in <AT_IP_DATA_MODE>!");
                return;
            }
        }
        else
        {
            /* �յ�else��֧������PCLINT���� */
        }

        /* ��PPP����HDLCȥʹ�ܲ��� */
        PPP_RcvAtCtrlOperEvent(gastAtClientTab[ucIndex].usPppId,
                               PPP_AT_CTRL_HDLC_DISABLE);

        /* ֹͣ��ʱ�� */
        AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);

        /* �ܽ��ź��޸ĺ�At_ModemRelInd����ֻ������USB���γ���ʱ����ã�
           Ϊ�˴ﵽModem��always-on��Ŀ�ģ���ʱ��Ҫ����AT��·��״̬Ǩ��
           ������������״̬:
        */
        gastAtClientTab[ucIndex].Mode            = AT_CMD_MODE;
        gastAtClientTab[ucIndex].IndMode         = AT_IND_MODE;
        gastAtClientTab[ucIndex].DataMode        = AT_DATA_BUTT_MODE;
        gastAtClientTab[ucIndex].DataState       = AT_DATA_STOP_STATE;
        gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_CURRENT_OPT_BUTT;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;
    }
}





