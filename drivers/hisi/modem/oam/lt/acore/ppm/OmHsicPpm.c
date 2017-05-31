



/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmHsicPpm.h"
#include "cpm.h"
#include "TafOamInterface.h"


/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_HSIC_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
/* HSIC��OM����״̬��Ĭ��Ϊ������ */
OM_HSIC_PORT_STATUS_ENUM_UINT32         g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

/*�����ź�������������OM HSIC���� */
VOS_SEM                                 g_ulOmAcpuHsicSem;

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
 �� �� ��  : PPM_GetHsicPortStatus
 ��������  : OM�ں�HSIC����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ״̬״̬
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
OM_HSIC_PORT_STATUS_ENUM_UINT32 PPM_GetHsicPortStatus(VOS_VOID)
{
    /* ����OM�ں�HSIC����״̬ */
    return g_ulOmHsicConnectStatus;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicIndWriteDataCB
 ��������  : ���ڴ���Hsic �ڵ��첽�������ݵĻص�
 �������  : pucData:   ��Ҫ���͵���������
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��2��2��
     ��    ��  : zhuli
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_HsicIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*��ǰֻ����OM����*/
    PPM_PortWriteAsyCB(OM_HSIC_IND_PORT_HANDLE, pucVirData, lLen);

    return;
}


/*****************************************************************************
 �� �� ��  : PPM_HsicCfgReadDataCB
 ��������  : ����ACPU��������HSIC CFG������ͨ��ICC���͸�OMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_INT32 PPM_HsicCfgReadDataCB(VOS_VOID)
{
    if (OM_HSIC_PORT_STATUS_OFF == PPM_GetHsicPortStatus())
    {
        return VOS_OK;
    }

    return PPM_ReadPortData(CPM_HSIC_CFG_PORT, g_astOMPortUDIHandle[OM_HSIC_CFG_PORT_HANDLE], OM_HSIC_CFG_PORT_HANDLE);
}

/*****************************************************************************
 �� �� ��  : PPM_HsicCfgWriteDataCB
 ��������  : ���ڴ���Hsic CFG�ڵ��첽�������ݵĻص�
 �������  : pucData:   ��Ҫ���͵���������
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen)
{
    /*��ǰֻ����OM����*/
    PPM_PortWriteAsyCB(OM_HSIC_CFG_PORT_HANDLE, pucVirData, lLen);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicCfgPortOpen
 ��������  : ���ڳ�ʼ��OMʹ�õ�Hsic CFG�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicCfgPortOpen(VOS_VOID)
{

    PPM_ReadPortDataInit(CPM_HSIC_CFG_PORT,
                           OM_HSIC_CFG_PORT_HANDLE,
                           PPM_HsicCfgReadDataCB,
                           PPM_HsicCfgWriteDataCB,
                           VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicIndPortOpen
 ��������  : ���ڳ�ʼ��OMʹ�õ�Hsic IND�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicIndPortOpen(VOS_VOID)
{
    /* HSIC IND �˿ڲ��������ݣ�û�жϿ����� */
    PPM_ReadPortDataInit(CPM_HSIC_IND_PORT,
                           OM_HSIC_IND_PORT_HANDLE,
                           VOS_NULL_PTR,
                           PPM_HsicIndWriteDataCB,
                           VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicIndPortClose
 ��������  : Hsic IND�˿��Ѿ���ʧ����Ҫ�ر�USB�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicIndPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicCfgPortClose
 ��������  : Hsic IND�˿��Ѿ���ʧ����Ҫ�ر�USB�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicCfgPortClose(VOS_VOID)
{
    PPM_PortCloseProc(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT);

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamHsicIndSendData
 ��������  : �����������ͨ��Hsic IND���͸�PC��
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERROR/VOS_OK
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_HsicIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_IND_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
 �� �� ��  : PPM_HsicCfgSendData
 ��������  : �����������ͨ��Hsic CFG���͸�PC��
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERROR/VOS_OK
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_HsicCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    return PPM_PortSend(OM_HSIC_CFG_PORT_HANDLE, pucVirAddr, pucPhyAddr, ulDataLen);
}

/*****************************************************************************
 �� �� ��  : PPM_HsicIndStatusCB
 ��������  : ����ACPU���洦��HSIC IND�˿ڶϿ����OM���ӶϿ�
 �������  : enPortState:   �˿�״̬
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicIndStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_IND_PORT_HANDLE, CPM_HSIC_IND_PORT, enPortState);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicIndStatusCB
 ��������  : ����ACPU���洦��HSIC CFG�˿ڶϿ����OM���ӶϿ�
 �������  : enPortState:   �˿�״̬
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicCfgStatusCB(ACM_EVT_E enPortState)
{
    PPM_PortStatus(OM_HSIC_CFG_PORT_HANDLE, CPM_HSIC_CFG_PORT, enPortState);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_HsicPortInit
 ��������  : ����HSIC��ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_HsicPortInit(VOS_VOID)
{
    /* ��Ʒ��֧��HSIC���ԣ�ֱ�ӷ��� */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /* ���HSICͨ���Ѿ�ö�ٳɹ�������Э��ջִ�г�ʼ�����������򽫳�ʼ������ע��������
        �ɵ�����HSICö�ٳɹ�������Խ��г�ʼ��*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        PPM_HsicIndPortOpen();
        PPM_HsicCfgPortOpen();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicIndPortOpen);
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)PPM_HsicCfgPortOpen);
    }

    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicIndPortClose);
    DRV_HSIC_REGUDI_DISABLECB((HSIC_UDI_DISABLE_CB_T)PPM_HsicCfgPortClose);

    CPM_PhySendReg(CPM_HSIC_IND_PORT,  PPM_HsicIndSendData);
    CPM_PhySendReg(CPM_HSIC_CFG_PORT,  PPM_HsicCfgSendData);

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicConnectProc
 Description     : OM�ں�HSIC����
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem����������Ŀ��������
 *****************************************************************************/
VOS_VOID PPM_HsicConnectProc(VOS_VOID)
{
    if (VOS_OK != VOS_SmP(g_ulOmAcpuHsicSem, 0))
    {
        return;
    }

    /* ��Ʒ��֧��HSIC���ԣ�ֱ�ӳ�ʼ���ɹ� */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        /*lint -e534*/
        VOS_SmV(g_ulOmAcpuHsicSem);
        /*lint +e534*/

        return;
    }

    /* ����Ѿ������ϲ������� */
    if (OM_HSIC_PORT_STATUS_ON == g_ulOmHsicConnectStatus)
    {
        /*lint -e534*/
        VOS_SmV(g_ulOmAcpuHsicSem);
        /*lint +e534*/

        return;
    }

    /* ��ȫ�ֱ�������Ϊ�ѹ����� */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_ON;

    /*lint -e534*/
    VOS_SmV(g_ulOmAcpuHsicSem);
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Prototype       : PPM_HsicDisconnectProc
 Description     : OM�ں�HSIC�������
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem����������Ŀ��������
 *****************************************************************************/
VOS_VOID PPM_HsicDisconnectProc(VOS_VOID)
{
    /* ��Ʒ��֧��HSIC���ԣ�ֱ�ӳ�ʼ���ɹ� */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return;
    }

    /* ����Ѿ���δ����״̬��������������� */
    if (OM_HSIC_PORT_STATUS_OFF == g_ulOmHsicConnectStatus)
    {
        return;
    }

    /* ��ȫ�ֱ�������Ϊ�ѽ�������� */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

    return;
}





