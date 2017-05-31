

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "vos.h"
#include "mdrv.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_ACM_AT_RX_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

pComRecv                                pfnAcmReadData = VOS_NULL_PTR;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : Dms_AtReadData
 ��������  : AT�����������
 �������  : enPhyBear: �˿ں�
              pDataBuf: ����ָ��
              ulLen:���ݳ���
 �������  :
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_INVALID_PARAMETER
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2012��8��27��
    ��    ��   : heliping
    �޸�����   : Creat Function

  2.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 Dms_AtReadData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pDataBuf, VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = 0;

    if ((VOS_NULL == pfnAcmReadData) || (VOS_NULL == pDataBuf))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if ( (DMS_PHY_BEAR_USB_PCUI != enPhyBear)
      && (DMS_PHY_BEAR_USB_CTRL != enPhyBear)
      && (DMS_PHY_BEAR_USB_PCUI2 != enPhyBear))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    DMS_LOG_INFO("Dms_AtReadData: PortNo = %d, len = %d, buf = %s\n", enPhyBear, ulLen, pDataBuf);

    ulRet = (VOS_UINT32)pfnAcmReadData((VOS_UINT8)enPhyBear, pDataBuf, (VOS_UINT16)ulLen);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : DMS_ACMRecvFuncReg
 ��������  : AT���ݽ��պ���ע��ӿ�
 �������  : pCallback: �ص�����ָ��

 �������  :
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_INVALID_PARAMETER
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback)
{
    DMS_MAIN_INFO * pstMainInfo = DMS_GetMainInfo();

    if (VOS_NULL == pCallback)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstMainInfo->pfnRdDataCallback = Dms_AtReadData;
    pfnAcmReadData = pCallback;

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbPortOpen
 ��������  : ��USB�˿�
 �������  : enPhyBear  --- ����˿ں�
             enDeviceId --- �豸��
             pReadCB    --- ��ȡ�ص�
             pWriteCB   --- д��ص�
             pStateCB   --- �¼��ص�
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_UsbPortOpen(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    UDI_DEVICE_ID_E                     enDeviceId,
    VOS_VOID                           *pReadCB,
    VOS_VOID                           *pWriteCB,
    VOS_VOID                           *pStateCB
)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    UDI_OPEN_PARAM_S                    stOpenParam;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;

    DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open Enter.\n", enPhyBear);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (UDI_INVALID_HANDLE != pstPhyBearProp->lPortHandle)
    {
        DMS_LOG_WARNING("DMS_UsbPortOpen[%d]: Already open.\n", enPhyBear);
        return ERR_MSP_SUCCESS;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_BEGIN + (VOS_UINT32)enPhyBear),\
                      0, 0, 0);

    stOpenParam.devid = enDeviceId;

    stReadBuffInfo.u32BuffSize = DMS_UL_DATA_BUFF_SIZE;
    stReadBuffInfo.u32BuffNum  = DMS_UL_DATA_BUFF_NUM;

    lHandle = mdrv_udi_open(&stOpenParam);
    if (UDI_INVALID_HANDLE != lHandle)
    {
        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_RELLOC_READ_BUFF fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                              (VOS_UINT32)lHandle, 0, 0);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_READ_CB, pReadCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_READ_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 2);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_WRITE_CB, pWriteCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_WRITE_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 3);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_WRITE_DO_COPY, (void *)0))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_WRITE_DO_COPY fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 4);
        }

        if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_SET_EVT_CB, pStateCB))
        {
            DMS_LOG_ERROR("DMS_UsbPortOpen[%d]: ACM_IOCTL_SET_EVT_CB fail.\n", enPhyBear);
            DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                            (VOS_UINT32)lHandle, 0, 5);
        }

        DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open success.\n", enPhyBear);
        pstPhyBearProp->lPortHandle = lHandle;
        return ERR_MSP_SUCCESS;
    }

    DMS_LOG_INFO("DMS_UsbPortOpen[%d]: Open fail.\n", enPhyBear);
    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_OPEN_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)lHandle, 0, 6);
    return ERR_MSP_FAILURE;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbPortClose
 ��������  : �ر�USB�˿�
 �������  : enPhyBear --- ����˿ں�
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_UsbPortClose(DMS_PHY_BEAR_ENUM enPhyBear)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    VOS_INT32                           lRet = ERR_MSP_SUCCESS;

    DMS_LOG_INFO("DMS_UsbPortClose[%d]: Enter.\n", enPhyBear);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (UDI_INVALID_HANDLE == pstPhyBearProp->lPortHandle)
    {
        DMS_LOG_WARNING("DMS_UsbPortClose[%d]: Already close.\n", enPhyBear);
        return ERR_MSP_SUCCESS;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_CLOSE_BEGIN + (VOS_UINT32)enPhyBear),\
                    0, 0, 0);

    lRet = mdrv_udi_close(pstPhyBearProp->lPortHandle);
    if (lRet == ERR_MSP_SUCCESS)
    {
        DMS_LOG_INFO("DMS_UsbPortClose[%d]: Close success.\n", enPhyBear);
        pstPhyBearProp->lPortHandle = UDI_INVALID_HANDLE;
        pstPhyBearProp->ucChanStat   = ACM_EVT_DEV_SUSPEND;
        return (VOS_UINT32)lRet;
    }

    DMS_LOG_INFO("DMS_UsbPortClose[%d]: Close fail.\n", enPhyBear);
    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_CLOSE_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)lRet, 0, 0);
    return ERR_MSP_FAILURE;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbPortReadCB
 ��������  : USB�˿����ݶ��ص�
 �������  : enPhyBear --- ����˿ں�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��30��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_VOID DMS_UsbPortReadCB(DMS_PHY_BEAR_ENUM enPhyBear)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    DMS_READ_DATA_PFN                   pRdDataFun = NULL;
    ACM_WR_ASYNC_INFO                   stAcmInfo;
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;

    DMS_LOG_INFO("DMS_UsbPortReadCB[%d]: Read begin.\n", enPhyBear);


    VOS_MemSet(&stAcmInfo, 0x0, sizeof(stAcmInfo));

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    lHandle = pstPhyBearProp->lPortHandle;
    if (UDI_INVALID_HANDLE == lHandle)
    {
        DMS_LOG_ERROR("DMS_UsbPortReadCB[%d]: UDI_INVALID_HANDLE.\n", enPhyBear);
        return;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_RD_CB_BEGIN + (VOS_UINT32)enPhyBear),\
                    0, 0, 0);

    if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_GET_RD_BUFF, &stAcmInfo))
    {
        DMS_LOG_ERROR("DMS_UsbPortReadCB[%d]: ACM_IOCTL_GET_RD_BUFF fail.\n", enPhyBear);
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_RD_CB_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                        (VOS_UINT32)lHandle, 0, 0);
        return;
    }

    pstPhyBearProp->ucChanStat = ACM_EVT_DEV_READY;

    pRdDataFun = DMS_GetDataReadFun();
    if (NULL != pRdDataFun)
    {
        (VOS_VOID)pRdDataFun(enPhyBear, (VOS_UINT8 *)stAcmInfo.pVirAddr, stAcmInfo.u32Size);
    }

    if (MDRV_OK != mdrv_udi_ioctl(lHandle, ACM_IOCTL_RETURN_BUFF, &stAcmInfo))
    {
        DMS_LOG_INFO("DMS_UsbPortReadCB[%d]: ACM_IOCTL_RETURN_BUFF fail.\n", enPhyBear);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbPortWrtCB
 ��������  : USB�˿�����д��ɻص�
 �������  : enPhyBear --- ����˿ں�
             pcVirAddr --- дָ��(�����ַ)
             pcPhyAddr --- дָ��(�����ַ)
             lDoneSize --- д�볤��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_UsbPortWrtCB(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    VOS_UINT_PTR                        ptrDebugVirAddr;
    VOS_UINT_PTR                        ptrDebugPhyAddr;

    ptrDebugVirAddr = (VOS_UINT_PTR)pcVirAddr;
    ptrDebugPhyAddr = (VOS_UINT_PTR)pcPhyAddr;

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_CB_BEGIN + (VOS_UINT32)enPhyBear),\
                    (VOS_UINT32)(ptrDebugVirAddr & (~0U)), (VOS_UINT32)(ptrDebugPhyAddr & (~0U)), (VOS_UINT32)lDoneSize);

    if (lDoneSize < 0)
    {
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_CB_ERR_BEGIN + (VOS_UINT32)enPhyBear),\
                        (VOS_UINT32)(ptrDebugVirAddr & (~0U)), (VOS_UINT32)(ptrDebugPhyAddr & (~0U)), (VOS_UINT32)lDoneSize);
    }

    if (VOS_TRUE == Dms_IsStaticBuf((VOS_UINT8 *)pcVirAddr))
    {
        Dms_FreeStaticBuf((VOS_UINT8 *)pcVirAddr);
    }
    else
    {
        if (NULL != pcVirAddr)
        {
            kfree(pcVirAddr);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbPortEvtCB
 ��������  : USB�˿��¼�����ص�����
 �������  : enPhyBear --- ����˿ں�
             enEvt     --- ACM�豸�¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_UsbPortEvtCB(DMS_PHY_BEAR_ENUM enPhyBear, ACM_EVT_E enEvt)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_EVT_BEGIN + (VOS_UINT32)enPhyBear),\
                    enEvt, 0, 0);

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    if (ACM_EVT_DEV_READY == enEvt)
    {
        pstPhyBearProp->ucChanStat  = ACM_EVT_DEV_READY;
    }
    else
    {
        pstPhyBearProp->ucChanStat  = ACM_EVT_DEV_SUSPEND;
        pstPhyBearProp->enLogicChan = DMS_CHANNEL_AT;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcuiOpen
 ��������  : ��PCUI�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_VcomPcuiOpen(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_PCUI,
                           UDI_ACM_AT_ID,
                           DMS_VcomPcuiReadCB,
                           DMS_VcomPcuiWrtCB,
                           DMS_VcomPcuiEvtCB);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcuiClose
 ��������  : �ر�PCUI�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_VcomPcuiClose(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_PCUI);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcuiReadCB
 ��������  : PCUI�˿ڶ�ȡ�ص�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomPcuiReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_PCUI);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcuiWrtCB
 ��������  : PCUI��д��ɻص�
 �������  : pcVirAddr --- дָ��(�����ַ)
             pcPhyAddr --- дָ��(�����ַ)
             lDoneSize --- д�볤��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomPcuiWrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_PCUI, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcuiEvtCB
 ��������  : PCUI�˿��¼�����ص�
 �������  : enEvt --- ACM�豸�¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomPcuiEvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_PCUI, enEvt);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomCtrlOpen
 ��������  : ��CTRL�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_VcomCtrlOpen(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_CTRL,
                           UDI_ACM_CTRL_ID,
                           DMS_VcomCtrlReadCB,
                           DMS_VcomCtrlWrtCB,
                           DMS_VcomCtrlEvtCB);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomCtrlClose
 ��������  : �ر�CTRL�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_VcomCtrlClose(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_CTRL);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomCtrlReadCB
 ��������  : CTRL�˿ڶ�ȡ�ص�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomCtrlReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_CTRL);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomCtrlWrtCB
 ��������  : CTRL��д��ɻص�
 �������  : pcVirAddr --- дָ��(�����ַ)
             pcPhyAddr --- дָ��(�����ַ)
             lDoneSize --- д�볤��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomCtrlWrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_CTRL, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomCtrlEvtCB
 ��������  : CTRL�˿��¼�����ص�
 �������  : enEvt --- ACM�豸�¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_VcomCtrlEvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_CTRL, enEvt);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcui2Open
 ��������  : ��PCUI2�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 DMS_VcomPcui2Open(VOS_VOID)
{
    return DMS_UsbPortOpen(DMS_PHY_BEAR_USB_PCUI2,
                           UDI_ACM_SKYTONE_ID,
                           DMS_VcomPcui2ReadCB,
                           DMS_VcomPcui2WrtCB,
                           DMS_VcomPcui2EvtCB);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcui2Close
 ��������  : �ر�PCUI2�˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS/ERR_MSP_FAILURE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 DMS_VcomPcui2Close(VOS_VOID)
{
    return DMS_UsbPortClose(DMS_PHY_BEAR_USB_PCUI2);
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcui2ReadCB
 ��������  : PCUI2�˿ڶ�ȡ�ص�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2ReadCB(VOS_VOID)
{
    DMS_UsbPortReadCB(DMS_PHY_BEAR_USB_PCUI2);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcui2WrtCB
 ��������  : PCUI2��д��ɻص�
 �������  : pcVirAddr --- дָ��(�����ַ)
             pcPhyAddr --- дָ��(�����ַ)
             lDoneSize --- д�볤��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2WrtCB(
    VOS_CHAR                           *pcVirAddr,
    VOS_CHAR                           *pcPhyAddr,
    VOS_INT                             lDoneSize
)
{
    DMS_UsbPortWrtCB(DMS_PHY_BEAR_USB_PCUI2, pcVirAddr, pcPhyAddr, lDoneSize);
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_VcomPcui2EvtCB
 ��������  : PCUI2�˿��¼�����ص�
 �������  : enEvt --- ACM�豸�¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID DMS_VcomPcui2EvtCB(ACM_EVT_E enEvt)
{
    DMS_UsbPortEvtCB(DMS_PHY_BEAR_USB_PCUI2, enEvt);
    return;
}



