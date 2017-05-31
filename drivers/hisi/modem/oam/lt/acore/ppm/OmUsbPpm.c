


/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "SCMProc.h"
#include "ombufmngr.h"
#include "OmCommonPpm.h"
#include "cpm.h"
#include "OmUsbPpm.h"


/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_USB_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : XXXXXXXX
    �޸�����   : V8R1 OM_Optimize��Ŀ����

*****************************************************************************/

/*****************************************************************************
 �� �� ��  : PPM_UsbCfgSendData
 ��������  : �����������ͨ��USB(CFG��)���͸�PC��
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERROR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_UsbCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_USB_CFG_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}


/*****************************************************************************
 �� �� ��  : PPM_UsbCfgPortClose
 ��������  : USB���ص�OM CFG�˿��Ѿ���ʧ����Ҫ�ر�CFG�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbCfgPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_USB_CFG_PORT_HANDLE, CPM_CFG_PORT);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbCfgStatusCB
 ��������  : ����ACPU���洦��USB����˿ڶϿ����OM���ӶϿ�
 �������  : enPortState:�˿�״̬
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_UsbCfgStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_USB_CFG_PORT_HANDLE, CPM_CFG_PORT, enPortState);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbCfgWriteDataCB
 ��������  : ���ڴ���USB���ص�OM CFG�˿ڵ��첽�������ݵĻص�
 �������  : pucData:   ��Ҫ���͵���������
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_UsbCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    PPM_PortWriteAsyCB(OM_USB_CFG_PORT_HANDLE, pucVirData, lLen);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbCfgReadDataCB
 ��������  : ����ACPU��������USB���ص�OM CFG�˿�����ͨ��ICC���͸�OMģ��
 �������  : enPhyPort: ����˿�
             UdiHandle:�豸���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_INT32 PPM_UsbCfgReadDataCB(VOS_VOID)
{
    return PPM_ReadPortData(CPM_CFG_PORT, g_astOMPortUDIHandle[OM_USB_CFG_PORT_HANDLE], OM_USB_CFG_PORT_HANDLE);
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbCfgPortOpen
 ��������  : ���ڳ�ʼ��USB���ص�OM CFG�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbCfgPortOpen(VOS_VOID)
{
    PPM_ReadPortDataInit(CPM_CFG_PORT,
                            OM_USB_CFG_PORT_HANDLE,
                            PPM_UsbCfgReadDataCB,
                            PPM_UsbCfgWriteDataCB,
                            PPM_UsbCfgStatusCB);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_UsbIndStatusCB
 ��������  : ����ACPU���洦��USB����˿ڶϿ����OM���ӶϿ�
 �������  : enPortState:   �˿�״̬
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbIndStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_USB_IND_PORT_HANDLE, CPM_IND_PORT, enPortState);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbIndWriteDataCB
 ��������  : ���ڴ���USB OM�����ϱ��˿ڵ��첽�������ݵĻص�
 �������  : pucData:   ��Ҫ���͵���������
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    PPM_PortWriteAsyCB(OM_USB_IND_PORT_HANDLE, pucVirData, lLen);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUsbIndPortOpen
 ��������  : ���ڳ�ʼ��USB���ص�OM�����ϱ��˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbIndPortOpen(VOS_VOID)
{
    PPM_ReadPortDataInit(CPM_IND_PORT,
                            OM_USB_IND_PORT_HANDLE,
                            VOS_NULL_PTR,
                            PPM_UsbIndWriteDataCB,
                            PPM_UsbIndStatusCB);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_UsbIndPortClose
 ��������  : USB���ص�OM�����ϱ��˿��Ѿ���ʧ����Ҫ�ر�USB�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_UsbIndPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_USB_IND_PORT_HANDLE, CPM_IND_PORT);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_UsbIndSendData
 ��������  : �����������ͨ��USB�����ϱ��˿ڷ��͸�PC��
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERROR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_UsbIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_USB_IND_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
 �� �� ��  : PPM_UsbCfgPortInit
 ��������  : ����USB��OM���ö˿�ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR -- ��ʼ��ʧ��
             VOS_OK  -- ��ʼ���ɹ�
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_UsbCfgPortInit(VOS_VOID)
{
    /* USB���ص�OM CFG�˿ڣ����õ�����첽�ӿڷ������ݣ�������Ҫα���ͬ���ӿڣ������ź��� */
    if(VOS_OK != VOS_SmCCreate("UCFG", 0, VOS_SEMA4_FIFO, &g_stUsbCfgPseudoSync.ulPseudoSyncSemId))
    {
        /*lint -e534*/
        LogPrint("\r\nPPM_UsbCfgPortInit: create g_stUsbCnfPseudoSync.ulPseudoSyncSemId failedd\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)PPM_UsbCfgPortOpen);

    mdrv_usb_reg_disablecb((USB_UDI_DISABLE_CB_T)PPM_UsbCfgPortClose);

    CPM_PhySendReg(CPM_CFG_PORT,  PPM_UsbCfgSendData);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_UsbIndPortInit
 ��������  : ����USB ��OM�����ϱ��˿�ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR -- ��ʼ��ʧ��
             VOS_OK  -- ��ʼ���ɹ�
 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_UsbIndPortInit(VOS_VOID)
{
    /* USB���ص�OM IND�˿ڣ����õ�����첽�ӿڷ������ݣ�������Ҫα���ͬ���ӿڣ������ź��� */
    if(VOS_OK != VOS_SmCCreate("UIND", 0, VOS_SEMA4_FIFO, &g_stUsbIndPseudoSync.ulPseudoSyncSemId))
    {
        /*lint -e534*/
        LogPrint("\r\nPPM_UsbIndPortInit: create g_stUsbIndPseudoSync.ulPseudoSyncSemId failedd\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    mdrv_usb_reg_enablecb((USB_UDI_ENABLE_CB_T)PPM_UsbIndPortOpen);

    mdrv_usb_reg_disablecb((USB_UDI_DISABLE_CB_T)PPM_UsbIndPortClose);

    CPM_PhySendReg(CPM_IND_PORT,  PPM_UsbIndSendData);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPM_UsbPortInit
 ��������  : USB���ص�����˿�ͨ���ĳ�ʼ��:����OM IND��OM CNF�ȶ˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK   - ��ʼ���ɹ�
             VOS_ERR  - ��ʼ��ʧ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_UsbPortInit(VOS_VOID)
{
    /* USB ���ص�OM�����ϱ��˿ڵĳ�ʼ�� */
    if (VOS_OK != PPM_UsbIndPortInit())
    {
        return VOS_ERR;
    }

    /* USB ���ص�OM���ö˿ڵĳ�ʼ�� */
    if (VOS_OK != PPM_UsbCfgPortInit())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}





