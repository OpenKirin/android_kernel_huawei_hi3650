

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CbtPpm.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : CBT������˿ڹ���ģ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��31��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����

***************************************************************************** */

/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "AtAppVcomInterface.h"
#include "CbtPpm.h"
#include "CbtCpm.h"
#include "pamappom.h"
#include "SCMSoftDecode.h"
#include "omprivate.h"
#include "cbtapprl.h"
#include "PamOamSpecTaskDef.h"


/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
VOS_SEM                            g_ulCbtUsbPseudoSyncSemId;   /* α��Ϊͬ���ӿ���ʹ�õ��ź��� */

CBT_ACPU_VCOM_DEBUG_INFO           g_stCbtVComAcpuDebugInfo;

/* ����ACPU��CBT�˿ڵ�UDI��� */
UDI_HANDLE                         g_ulCbtPortUDIHandle    = VOS_ERROR;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/
extern  CBTCPM_RCV_FUNC                 g_pCbtRcvFunc;
extern  CBTCPM_SEND_FUNC                g_pCbtSndFunc;

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CBTPPM_OamCbtPortDataSnd
 ��������  : ����CBT����
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen:    ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamCbtPortDataSnd(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    CBTCPM_SEND_FUNC                    pFunc;

    pFunc = CBTCPM_GetSndFunc();

    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    return pFunc(pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtSendData
 ��������  : �����������ͨ��USB(APP��)���͸�PC��
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen:    ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2011��10��8��
     ��    ��  : g47350
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_INT32                           lRet;
    ACM_WR_ASYNC_INFO                   stVcom;
    /*VOS_UINT32                          ulInSlice;
    VOS_UINT32                          ulOutSlice;
    VOS_UINT32                          ulWriteSlice;*/

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /* ��ӡ���� */
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtSendData: Vir or Phy Addr is Null \n");
        /*lint +e534*/

        return CPM_SEND_PARA_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR*)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum1++;

    ulInSlice = OM_GetSlice();*/

    lRet = mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_ASYNC, &stVcom);

    /*g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteNum2++;

    ulOutSlice = OM_GetSlice();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = ulInSlice - ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }*/

    /*if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteMaxTime = ulWriteSlice;
    }*/


    if (MDRV_OK == lRet)     /*��ǰ���ͳɹ�*/
    {
        if (VOS_OK != VOS_SmP(g_ulCbtUsbPseudoSyncSemId, 0))
        {
            /*lint -e534*/
            LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
            /*lint +e534*/
            return VOS_ERR;
        }

        return VOS_OK;
    }
    else if (MDRV_OK > lRet)    /*��ʱ����*/
    {
        /*��ӡ��Ϣ������UDI�ӿڵĴ�����Ϣ*/
        /*lint -e534*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/


        /*        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[OM_USB_CBT_PORT_HANDLE].ulUSBWriteErrTime   = OM_GetSlice();*/

        return VOS_ERR; /*������ʱ������Ҫ����NULL��������*/
    }
    else    /*����������Ҫ��λ����*/
    {
        /*��ӡ��Ϣ������UDI�ӿ�*/
        /*lint -e534*/
        LogPrint1("\r\n CBTPPM_OamUsbCbtSendData: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__,
                             (VOS_CHAR *)&lRet, sizeof(VOS_INT32));

        return VOS_ERR;
    }

}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtPortClose
 ��������  : ���ڹر�USBУ׼�˿ڵĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortClose(VOS_VOID)
{
    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        return;
    }

    /*lint -e534*/
    mdrv_udi_close(g_ulCbtPortUDIHandle);
    /*lint +e534*/

    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBT�˿ڴ�USB��VCOM�л���UARTʱ���պ���ָ��Ϊ�գ��յ�USB״̬���ʱ�����Ͽ����� */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    /*lint -e534*/
    PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtWriteDataCB
 ��������  : USB���ص�CBT�˿��첽�������ݵĻص�
 �������  : pucData:   ���͵���������
             ulDataLen: ʵ�ʷ������ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    if (lLen < 0)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtWriteDataCB: lLen < 0. \n");
        /*lint +e534*/
    }

    /* αͬ���ӿڣ��ͷ��ź��� */
    /*lint -e534*/
    VOS_SmV(g_ulCbtUsbPseudoSyncSemId);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtStatusCB
 ��������  : ����ACPU���洦��USB����˿ڶϿ����У׼�Ͽ�
 �������  : enPortState:   �˿�״̬
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtStatusCB(ACM_EVT_E enPortState)
{
    /* CBT�˿ڴ�USB��VCOM�л���UARTʱ���պ���ָ��Ϊ�գ��յ�USB״̬���ʱ�����Ͽ����� */
    if (VOS_NULL_PTR == CBTCPM_GetRcvFunc())
    {
        return;
    }

    /* CBT�˿�ֻ����GU�Ķ˿ڶϿ� */
    /*lint -e534*/
    PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_CBT);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtPortOpen
 ��������  : ���ڳ�ʼ��USB���ص�CBTʹ�õĶ˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamUsbCbtPortOpen(VOS_VOID)
{
    CBTPPM_OamCbtPortDataInit(OM_USB_CBT_PORT_HANDLE,
                              CBTPPM_OamUsbCbtReadDataCB,
                              CBTPPM_OamUsbCbtWriteDataCB,
                              CBTPPM_OamUsbCbtStatusCB);

    return;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamUsbCbtReadDataCB
 ��������  : ����ACPU��������USB���ص�CBT������ͨ��ICC���͸�OMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_INT32 CBTPPM_OamUsbCbtReadDataCB(VOS_VOID)
{
    ACM_WR_ASYNC_INFO                   stInfo;
    CBTCPM_RCV_FUNC                     pFunc;

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB: Input HANDLE  is err. \n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stInfo, 0, sizeof(stInfo));
    /*lint +e534*/

    /* ��ȡUSB��IO CTRL�ڵĶ����� */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_GET_READ_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl is Failed\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e40 -e534*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size, CBT_ACPU_USB_CB);
    /*lint +e40 +e534*/

    /* ���ݽ��պ��� */
    pFunc = CBTCPM_GetRcvFunc();

    if (VOS_NULL_PTR != pFunc)
    {
        if (VOS_OK != pFunc((VOS_UINT8 *)stInfo.pVirAddr, stInfo.u32Size))
        {
            /* ���ӿ�ά�ɲ���� */
        }
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_RETUR_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtReadDataCB:Call mdrv_udi_ioctl UDI_ACM_IOCTL_RETUR_BUFFER_CB is Failed\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamCbtPortDataInit
 ��������  : ���ڳ�ʼ��CBTʹ�õĶ˿��豸
 �������  : enHandle: �˿ڵľ��
             pReadCB: �ö˿�����Ķ�ȡ�ص�����
             pWriteCB: �ö˿�������첽д�ص�����
             pStateCB: �ö˿������״̬�ص�����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortDataInit(OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                        VOS_VOID                            *pReadCB,
                                        VOS_VOID                            *pWriteCB,
                                        VOS_VOID                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;


    stUdiPara.devid            = UDI_ACM_OM_ID;

    stReadBuffInfo.u32BuffSize = OM_ICC_BUFFER_SIZE;
    stReadBuffInfo.u32BuffNum  = OM_DRV_MAX_IO_COUNT;

    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = OM_GetSlice();*/


    if (VOS_ERROR != g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: The UDI Handle is not Null !");
        /*lint +e534*/

        return;
    }

    /* ��CBTʹ�õ�USBͨ�� */
    g_ulCbtPortUDIHandle = mdrv_udi_open(&stUdiPara);

    if (VOS_ERROR == g_ulCbtPortUDIHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit: Open UDI ACM failed!");
        /*lint +e534*/

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = OM_GetSlice();*/

    /* ����CBTʹ�õ�USBͨ������ */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_RELLOC_READ_BUFF Failed\r\n");
        /*lint +e534*/

        return;
    }

    /* ע��OMʹ�õ�USB�����ݻص����� */
    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, UDI_ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl UDI_ACM_IOCTL_SET_READ_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_EVT_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != mdrv_udi_ioctl(g_ulCbtPortUDIHandle, ACM_IOCTL_WRITE_DO_COPY, VOS_NULL_PTR))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamCbtPortDataInit, mdrv_udi_ioctl ACM_IOCTL_WRITE_DO_COPY Failed\r\n");
        /*lint +e534*/

        return;
    }


    /*g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = OM_GetSlice();*/

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbCbtPortInit
 ��������  : ����USB ��CBT�˿�ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��25��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamUsbCbtPortInit(VOS_VOID)
{
    /* CBT�˿���PCVOICE���ã���̬ע�����ݽ��պ��� */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /* ��̬ע�����ݷ��ͺ��� */
    CBTCPM_PortSndReg(CBTPPM_OamUsbCbtSendData);

    /* USB���ص�CBT�˿ڣ����õ�����첽�ӿڷ������ݣ�������Ҫα���ͬ���ӿڣ������ź��� */
    if(VOS_OK != VOS_SmCCreate("UCBT", 0, VOS_SEMA4_FIFO, &g_ulCbtUsbPseudoSyncSemId))
    {
        /*lint -e534*/
        LogPrint("\r\n CBTPPM_OamUsbCbtPortInit: create g_ulCbtUsbPseudoSyncSemId failedd\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* USB���ص�CBT�˿ڳ�ʼ��UDI�豸��� */
    g_ulCbtPortUDIHandle = VOS_ERROR;

    /* CBT�˿�ͨ��CBT��CPM������ע�������ͺ��� */
    /*lint -e534*/
    mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)CBTPPM_OamUsbCbtPortOpen);

    mdrv_usb_reg_disablecb((USB_UDI_DISABLE_CB_T)CBTPPM_OamUsbCbtPortClose);
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamVComCbtReadData
 ��������  : ��VCOM�˿ڶ�ȡCBT������
 �������  :  ucDevIndex: ����˿�
              pData    : �յ�����
              ullength : ���ݳ���

 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_INT CBTPPM_OamVComCbtReadData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 ullength)
{
    CBTCPM_RCV_FUNC                     pFunc;

    if (ucDevIndex != APP_VCOM_DEV_INDEX_LOG)
    {
        /*lint -e534*/
        vos_printf("\r\n CBTPPM_OamVComCbtReadData:PhyPort port is error: %d\n", ucDevIndex);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtVComAcpuDebugInfo.ulVCOMRcvNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMRcvLen += ullength;

    if ((VOS_NULL_PTR == pData) || (0 == ullength))
    {
        /*lint -e534*/
        vos_printf("\r\n CBTPPM_OamVComCbtReadData:Send data is NULL\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e40 -e534*/
    CBT_ACPU_DEBUG_TRACE((VOS_UINT8*)pData, ullength, CBT_ACPU_VCOM_CB);
    /*lint +e40 +e534*/

    pFunc = CBTCPM_GetRcvFunc();

    /* ���ݽ��պ��� */
    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_ERR;
    }

    if (VOS_OK != pFunc((VOS_UINT8*)pData, ullength))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMRcvErrLen += ullength;

        /*lint -e534*/
        vos_printf("\r\n Info: CBTPPM_OamVComCbtReadData:Call CBT Data Rcv Func fail\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamVComCbtSendData
 ��������  : ��VCOM�˿ڷ���CBT����
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen:    ���ݳ���
 �������  : ��
 �� �� ֵ  : CPM_SEND_ERR/CPM_SEND_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_OamVComCbtSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    g_stCbtVComAcpuDebugInfo.ulVCOMSendNum++;
    g_stCbtVComAcpuDebugInfo.ulVCOMSendLen += ulDataLen;

    if (VOS_OK != APP_VCOM_Send(APP_VCOM_DEV_INDEX_LOG, pucVirAddr, ulDataLen))
    {
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrNum++;
        g_stCbtVComAcpuDebugInfo.ulVCOMSendErrLen += ulDataLen;

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamVComCbtPortInit
 ��������  : ���� Vcom CBT�˿ڵĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTPPM_OamVComCbtPortInit(VOS_VOID)
{
    /* CBT�˿���PCVOICE���ã���̬ע�����ݽ��պ��� */
    CBTCPM_PortRcvReg(CBTSCM_SoftDecodeDataRcv);

    /* У׼��VCOM28�����������·������ݵĻظ�����CPM��ֱ�ӷ��� */
    /*lint -e534*/
    APP_VCOM_RegDataCallback(APP_VCOM_DEV_INDEX_LOG, CBTPPM_OamVComCbtReadData);
    /*lint +e534*/

    CBTCPM_PortSndReg(CBTPPM_OamVComCbtSendData);

    return;
}

/*****************************************************************************
 �� �� ��  : CBTPPM_OamCbtPortInit
 ��������  : CBT�˿ڳ�ʼ��
 �������  : enCbtPort:CBT����˿�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID CBTPPM_OamCbtPortInit(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU            stPortCfg;

    /* ��ʼ������ */
    /*lint -e534*/
    VOS_MemSet(&g_stCbtVComAcpuDebugInfo, 0, sizeof(g_stCbtVComAcpuDebugInfo));
    /*lint +e534*/

    /* ��ȡOM���������ͨ�� */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        stPortCfg.enCbtPortNum = CPM_CBT_PORT_VCOM;
    }

    if (CPM_CBT_PORT_USB == stPortCfg.enCbtPortNum)
    {
        /* USB ���ص�CBT�˿ڵĳ�ʼ�� */
        /*lint -e534*/
        CBTPPM_OamUsbCbtPortInit();
        /*lint +e534*/
    }
    else if (CPM_CBT_PORT_SOCKET == stPortCfg.enCbtPortNum)
    {
        CBTPPM_SocketPortInit();
    }
    /* Ĭ�϶���VCOM��CBT */
    else
    {
        /* Vcom ��CBTͨ���ĳ�ʼ�� */
        CBTPPM_OamVComCbtPortInit();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CBTPPM_SocketTaskInit
 ��������  : CBT�˿ڳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
  1.��    ��   : 2015��12��21��
    ��    ��   : x51137
    �޸�����   :  Creat Function
*****************************************************************************/
VOS_UINT32 CBTPPM_SocketTaskInit(VOS_VOID)
{
    return VOS_OK;
}

VOS_VOID CBTPPM_SocketPortInit(VOS_VOID)
{
    return;
}






