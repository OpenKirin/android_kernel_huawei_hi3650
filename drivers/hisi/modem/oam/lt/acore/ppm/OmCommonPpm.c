



/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "OmCommonPpm.h"
#include "cpm.h"
#include "omprivate.h"
#include "SCMProc.h"
#include "diag_debug.h"
#include "msp_diag.h"
#include "diag_common.h"



/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_COMMON_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
/* ����ACPU��USB�豸��UDI��� */
UDI_HANDLE                              g_astOMPortUDIHandle[OM_PORT_HANDLE_BUTT];

/* USB���ص�OM IND�˿��У�α��Ϊͬ���ӿ�ʹ�õ����ݽṹ�� */
OM_PSEUDO_SYNC_STRU                     g_stUsbIndPseudoSync;

/* USB���ص�OM CNF�˿��У�α��Ϊͬ���ӿ�ʹ�õ����ݽṹ�� */
OM_PSEUDO_SYNC_STRU                     g_stUsbCfgPseudoSync;

VOS_UINT32                              g_ulUSBSendErrCnt   = 0;

/* �˿��л���Ϣ�����ݽṹ�� */
PPM_PORT_CFG_INFO_STRU                  g_stPpmPortSwitchInfo;

/* ��������������AT����˿��л����ٽ���Դ���� */
VOS_SPINLOCK                            g_stPpmPortSwitchSpinLock;

VOS_BOOL                                g_bPpmLogCompress   = VOS_FALSE;


OM_ACPU_DEBUG_INFO                      g_stAcpuDebugInfo;

VOS_UINT32                              g_ulOmAcpuDbgFlag = VOS_FALSE;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/
extern OM_CHANNLE_PORT_CFG_STRU         g_stPortCfg;
extern VOS_SPINLOCK                     g_stScmSoftDecodeDataRcvSpinLock;
extern VOS_SPINLOCK                     g_stCbtScmDataRcvSpinLock;
/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : PPM_DisconnectGUPort
 ��������  : GU�Ͽ�OM�˿�
 �������  : ucCpuId:CpuId
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��05��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel)
{

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_DisconnectTLPort
 ��������  : TL�Ͽ�OM�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��05��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_DisconnectTLPort(VOS_VOID)
{
    DIAG_DATA_MSG_STRU                 *pstMsg;

    pstMsg = (DIAG_DATA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, sizeof(DIAG_DATA_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
    pstMsg->ulMsgId       = ID_MSG_DIAG_HSO_DISCONN_IND;

    (VOS_VOID)VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstMsg);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_DisconnectAllPort
 ��������  : GUTL�Ͽ�OM�˿�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��05��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel)
{
    PPM_DisconnectTLPort();

    PPM_DisconnectGUPort(enChannel);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_GetSendDataLen
 ��������  : PPM�����ݷ��ͳ��Ƚ��д���
 �������  : ulDataLen: SOCPͨ�������ݳ���
             enChanID:  SOCP channel ID
 �������  : pulSendDataLen:ʵ�ʷ��ͳ�ȥ�����ݳ���
             penPhyport:ָ������˿ں�
 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_GetSendDataLen(SOCP_CODER_DST_ENUM_U32 enChanID, VOS_UINT32 ulDataLen, VOS_UINT32 *pulSendDataLen, CPM_PHY_PORT_ENUM_UINT32 *penPhyport)
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyport;

    if (SOCP_CODER_DST_OM_CNF == enChanID)
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_CFG_COMM);
    }
    else
    {
        enPhyport = CPM_QueryPhyPort(CPM_OM_IND_COMM);
    }


    /*��������ͨ��USB���ҷ��ͳ��ȴ���60k��ʱ����Ҫ���Ʒ��ͳ���*/
    if (((CPM_IND_PORT == enPhyport) || (CPM_CFG_PORT == enPhyport))
        &&(ulDataLen > USB_MAX_DATA_LEN))
    {
        /*lint -e534*/
        LogPrint1("PPM_GetSendDataLen: Change the send Data Len %d", (VOS_INT)ulDataLen);
        /*lint +e534*/

        *pulSendDataLen = USB_MAX_DATA_LEN;
    }
    else
    {
        *pulSendDataLen = ulDataLen;  /*��������²���Ҫ������ǰ�Ĵ�С������sd��wifi*/
    }

    *penPhyport = enPhyport;
    return;
}

/*****************************************************************************
 �� �� ��  : PPM_PortStatus
 ��������  : ����ACPU���洦������˿ڶϿ����OM���ӶϿ�
 �������  : enHandle:   UDI�豸���
             enPhyPort:  ����˿�
             enPortState:�˿�״̬
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_PortStatus(OM_PROT_HANDLE_ENUM_UINT32 enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort,ACM_EVT_E enPortState)
{
    VOS_ULONG                           ulLockLevel;
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;
    VOS_UINT32 ulSlicehigh, ulSlicelow;
    

    if (ACM_EVT_DEV_SUSPEND == enPortState)
    {
        (VOS_VOID)mdrv_timer_get_accuracy_timestamp(&ulSlicehigh, &ulSlicelow);

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime = ulSlicelow;

        diag_printf("Receive USB disconnect (chan %d) callback at slice 0x%x %x!\n",enHandle, ulSlicehigh, ulSlicelow);

        VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        ulSndMsg  = VOS_FALSE;
        enChannel = OM_LOGIC_CHANNEL_BUTT;

        /* CFG�˿ڴ���GU��TL�Ķ˿ڶϿ�������Ϣ��GU��TLȥ���������Ͽ�CPM�Ĺ��� */
        if (OM_USB_CFG_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
            {
                ulSndMsg  = VOS_TRUE;
                enChannel = OM_LOGIC_CHANNEL_CNF;
            }
        }
        /* IND�˿ڶϿ�ʱ����Ϣ��GU��TLȥ���� */
        else if (OM_USB_IND_PORT_HANDLE == enHandle)
        {
            if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
            {
                ulSndMsg  = VOS_TRUE;
                enChannel = OM_LOGIC_CHANNEL_IND;
            }
        }
        else
        {

        }

        VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

        if (VOS_TRUE == ulSndMsg)
        {
            PPM_DisconnectAllPort(enChannel);
        }
    }
    else if(ACM_EVT_DEV_READY == enPortState)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime = mdrv_timer_get_normal_timestamp();
    }
    else
    {
        /*lint -e534*/
        LogPrint2("PPM_PortStatus: The USB Port %d State %d is Unknow", (VOS_INT)enPhyPort, (VOS_INT)enPortState);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum++;

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime = mdrv_timer_get_normal_timestamp();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_PortCloseProc
 ��������  : OM�˿��Ѿ���ʧ����Ҫ�ر�USB�˿�
 �������  : enHandle: �˿ھ��ö�ٶ��壬�رպ�˿�����ΪVOS_ERROR
             enPhyPort:����˿�
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_PortCloseProc(OM_PROT_HANDLE_ENUM_UINT32  enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    VOS_ULONG                           ulLockLevel;
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        return;
    }

    mdrv_udi_close(g_astOMPortUDIHandle[enHandle]);

    g_astOMPortUDIHandle[enHandle] = VOS_ERROR;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice = mdrv_timer_get_normal_timestamp();

    VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    ulSndMsg  = VOS_FALSE;
    enChannel = OM_LOGIC_CHANNEL_BUTT;

    /* CFG�˿ڴ���GU��TL�Ķ˿ڶϿ�������Ϣ��GU��TLȥ���������Ͽ�CPM�Ĺ��� */
    if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_CFG_COMM))
        {
            ulSndMsg  = VOS_TRUE;
            enChannel = OM_LOGIC_CHANNEL_CNF;
        }
    }
    /* IND�˿ڶϿ�ʱ����Ϣ��GU��TLȥ���������Ͽ�CPM�Ĺ��� */
    else if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        if (enPhyPort == CPM_QueryPhyPort(CPM_OM_IND_COMM))
        {
            ulSndMsg  = VOS_TRUE;
            enChannel = OM_LOGIC_CHANNEL_IND;
        }
    }
    else
    {

    }

    VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    if (VOS_TRUE == ulSndMsg)
    {
        PPM_DisconnectAllPort(enChannel);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamUSBReadData
 ��������  : ����ACPU������������ͨ��ICC���͸�OMģ��
 �������  : enPhyPort: ����˿�
             UdiHandle:�豸���
             enHandle: UDI�豸�������ƫ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_INT32 PPM_ReadPortData(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, UDI_HANDLE UdiHandle, OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{
    ACM_WR_ASYNC_INFO                   stInfo;

    diag_PTR(EN_DIAG_PTR_PPM_READDATA);

    if (VOS_ERROR == UdiHandle)
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_PortCloseProc: Input HANDLE  is err. \n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr++;

        diag_PTR(EN_DIAG_PTR_PPM_ERR1);

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stInfo, 0, sizeof(stInfo));
    /*lint +e534*/

    /* ��ȡUSB��IO CTRL�ڵĶ����� */
    if (VOS_OK != mdrv_udi_ioctl(UdiHandle, UDI_ACM_IOCTL_GET_READ_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortData:Call mdrv_udi_ioctl is Failed\n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr++;
        diag_PTR(EN_DIAG_PTR_PPM_ERR2);

        return VOS_ERR;
    }

    /*lint -e40*/
    OM_ACPU_DEBUG_CHANNEL_TRACE(enPhyPort, (VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size, OM_ACPU_USB_CB);
    /*lint +e40*/

    if(VOS_OK != CPM_ComRcv(enPhyPort, (VOS_UINT8*)stInfo.pVirAddr, stInfo.u32Size))
    {
        /*lint -e534*/
        LogPrint1("\r\n Info: PPM_ReadPortData:Call CPM_ComRcv is NULL, PhyPort is %d\n", (VOS_INT)enPhyPort);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr++;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte += stInfo.u32Size;

    if(VOS_OK != mdrv_udi_ioctl(UdiHandle, UDI_ACM_IOCTL_RETUR_BUFFER_CB, &stInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortData:Call mdrv_udi_ioctl UDI_ACM_IOCTL_RETUR_BUFFER_CB is Failed\n");
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr++;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPM_PortPseudoSyncGetSmp
 ��������  : αͬ���ӿڣ���Ҫ�ڵ��õ����첽д�����󣬻�ȡ�ź���
 �������  : enHandle:UDI�豸���
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_PortPseudoSyncGetSmp(OM_PROT_HANDLE_ENUM_UINT32 enHandle)
{

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_QueryLogPort
 ��������  : �ṩ��NAS����Log�˿ڲ�ѯ
 �������  : ��
 �������  : pulLogPort��ǰLog����˿�

 �� �� ֵ  : VOS_ERR/VOS_OK

 �޸���ʷ  :
   1.��    ��  : 2014��06��3��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_QueryLogPort(VOS_UINT32  *pulLogPort)
{
    if (VOS_NULL_PTR == pulLogPort)
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_QueryLogPort: para is NULL !!\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    *pulLogPort = g_stPortCfg.enPortNum;

    if ((CPM_OM_PORT_TYPE_USB != *pulLogPort) && (CPM_OM_PORT_TYPE_VCOM != *pulLogPort))
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_QueryLogPort: log prot is not support. port:%d!!\n", *pulLogPort);
        /*lint +e534*/
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_LogPortSwitch
 ��������  : �ṩ��NAS���ж˿��л�
 �������  : enPhyPort: ���л�����˿�ö��ֵ
             ulEffect:�Ƿ�������Ч
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK

 �޸���ʷ  :
   1.��    ��  : 2014��6��3��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_LogPortSwitch(VOS_UINT32  ulPhyPort, VOS_BOOL ulEffect)
{
    CPM_PHY_PORT_ENUM_UINT32            enPhyCfgPort;
    CPM_PHY_PORT_ENUM_UINT32            enPhyIndPort;
    VOS_ULONG                           ulLockLevel;
    VOS_BOOL                            ulSndMsg;

    if ((CPM_OM_PORT_TYPE_USB != ulPhyPort) && (CPM_OM_PORT_TYPE_VCOM != ulPhyPort))
    {
        /*lint -e534*/
        vos_printf("\r\n PPM_LogPortSwitch: enPhyPort is error.port %d\n", ulPhyPort);
        /*lint +e534*/

        g_stPpmPortSwitchInfo.ulPortTypeErr++;

        return VOS_ERR;
    }

    /* �л��Ķ˿��뵱ǰ�˿�һ�²��л� */
    if (ulPhyPort == g_stPortCfg.enPortNum)
    {
        /* �л���VCOM���ʱ��LOG�ӳ�д�뿪���������Ҫ��������SOCP�ĳ�ʱ�ж� */
        if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
        {
            mdrv_socp_set_log_int_timeout();
        }

        /* Ϊ�˹��USB���ʱ��������ʱд���޷����ӹ���,�л���USB���ʱ��Ҫ��������SOCP�ĳ�ʱ�жϵ�Ĭ��ֵ */
        if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
        {
            mdrv_socp_set_log_int_default_timeout();
        }
        return VOS_OK;
    }

    g_stPpmPortSwitchInfo.ulStartSlice = mdrv_timer_get_normal_timestamp();

    enPhyCfgPort = CPM_QueryPhyPort(CPM_OM_CFG_COMM);
    enPhyIndPort = CPM_QueryPhyPort(CPM_OM_IND_COMM);

    ulSndMsg = VOS_FALSE;

    VOS_SpinLockIntLock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    /* �л���VCOM��� */
    if (CPM_OM_PORT_TYPE_VCOM == ulPhyPort)
    {
        /* ��ǰ��USB��� */
        if ((CPM_CFG_PORT == enPhyCfgPort) && (CPM_IND_PORT == enPhyIndPort))
        {
            /* ��Ҫ�Ͽ����� */
            ulSndMsg = VOS_TRUE;

            CPM_DisconnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
            CPM_DisconnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);
        }

        /* ��ǰOM��VCOM�ϱ� */
        CPM_ConnectPorts(CPM_VCOM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_VCOM_IND_PORT, CPM_OM_IND_COMM);

        g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_VCOM;
    }
    /* �л���USB��� */
    else
    {
        /* ��ǰ��VCOM��� */
        if ((CPM_VCOM_CFG_PORT == enPhyCfgPort) && (CPM_VCOM_IND_PORT == enPhyIndPort))
        {
            /* �Ͽ����� */
            ulSndMsg = VOS_TRUE;

            CPM_DisconnectPorts(CPM_VCOM_CFG_PORT, CPM_OM_CFG_COMM);
            CPM_DisconnectPorts(CPM_VCOM_IND_PORT, CPM_OM_IND_COMM);
        }

        /* OM��USB�ϱ� */
        CPM_ConnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);

        g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_USB;
    }

    VOS_SpinUnlockIntUnlock(&g_stPpmPortSwitchSpinLock, ulLockLevel);

    if (VOS_TRUE == ulSndMsg)
    {
        PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);
    }
    /* �л���VCOM���ʱ��LOG�ӳ�д�뿪���������Ҫ��������SOCP�ĳ�ʱ�ж� */
    if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
    {
        mdrv_socp_set_log_int_timeout();
    }

    /* Ϊ�˹��USB���ʱ��������ʱд���޷����ӹ���,�л���USB���ʱ��Ҫ��������SOCP�ĳ�ʱ�жϵ�Ĭ��ֵ */
    if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
    {
        mdrv_socp_set_log_int_default_timeout();
    }
    g_stPpmPortSwitchInfo.ulSwitchSucc++;
    g_stPpmPortSwitchInfo.ulEndSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_TRUE == ulEffect)
    {
        if (VOS_OK != NV_Write(en_NV_Item_Om_Port_Type, &g_stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
        {
            /*lint -e534*/
            vos_printf("\r\n PPM_LogPortSwitch: NV_Write fail\n");
            /*lint +e534*/
        }
    }

    return VOS_OK;
}

VOS_UINT32 PPM_LogCompressCfg(VOS_BOOL enable)
{
    if(g_bPpmLogCompress != enable)
    {
        g_bPpmLogCompress = enable;
        if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
        {
            SCM_CoderDstCompressCfg(enable);
        }
        /*Ϊ��оƬ��֤����ʱ��׮����USB�˿�Ҳ��ѹ����ʽ*/
        if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
        {
            SCM_CoderDstCompressCfg(enable);
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPM_UdiRegCallBackFun
 ��������  : ����ע��UDI�豸�Ļص�����
 �������  : enHandle: �˿ڵľ��
             ulCmdType: ��������
             pFunc: ע��Ļص�����ָ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_UdiRegCallBackFun(UDI_HANDLE enHandle, VOS_UINT32 ulCmdType, VOS_VOID* pFunc)
{
    if (VOS_NULL_PTR == pFunc)
    {
        return VOS_OK;
    }

    if (VOS_OK != mdrv_udi_ioctl(enHandle, ulCmdType, pFunc))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_UdiRegCallBackFun, mdrv_udi_ioctl Failed\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    return VOS_OK;
}



#define OM_SOCP_CNF_BUFFER_SIZE          (8*1024)
#define OM_SOCP_CNF_BUFFER_NUM           (8)

#define OM_SOCP_IND_BUFFER_SIZE          (2*1024)
#define OM_SOCP_IND_BUFFER_NUM           (2)


/*****************************************************************************
 �� �� ��  : PPM_ReadPortDataInit
 ��������  : ���ڳ�ʼ��OMʹ�õ��豸
 �������  : enPhyPort: ����˿ں�
             enHandle: �˿ڵľ��
             pReadCB: �ö˿�����Ķ�ȡ�ص�����
             pWriteCB: �ö˿�������첽д�ص�����
             pStateCB: �ö˿������״̬�ص�����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_ReadPortDataInit(CPM_PHY_PORT_ENUM_UINT32        enPhyPort,
                                    OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                    VOS_VOID                            *pReadCB,
                                    VOS_VOID                            *pWriteCB,
                                    VOS_VOID                            *pStateCB)
{
    UDI_OPEN_PARAM_S                    stUdiPara;
    ACM_READ_BUFF_INFO                  stReadBuffInfo;
    VOS_BOOL                            isCnf = VOS_TRUE;

    /*��ʼ����ǰʹ�õ�USBͨ��*/
    if (CPM_IND_PORT == enPhyPort)
    {
        isCnf                      = VOS_FALSE;
        stUdiPara.devid            = UDI_ACM_LTE_DIAG_ID;
    }
    else if (CPM_CFG_PORT == enPhyPort)
    {
        isCnf                      = VOS_TRUE;
        stUdiPara.devid            = UDI_ACM_GPS_ID;
    }
    else if (CPM_HSIC_IND_PORT == enPhyPort)
    {
        isCnf                      = VOS_FALSE;
        stUdiPara.devid            = UDI_ACM_HSIC_ACM7_ID;
    }
    else if (CPM_HSIC_CFG_PORT == enPhyPort)
    {
        isCnf                      = VOS_TRUE;
        stUdiPara.devid            = UDI_ACM_HSIC_ACM8_ID;
    }
    else
    {
        /*lint -e534*/
        LogPrint1("\r\n PPM_ReadPortDataInit: Open Wrong Port %d!", (VOS_INT)enPhyPort);
        /*lint +e534*/

        return;
    }

    if(isCnf == VOS_TRUE)
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_CNF_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_CNF_BUFFER_NUM;
    }
    else
    {
        stReadBuffInfo.u32BuffSize = OM_SOCP_IND_BUFFER_SIZE;
        stReadBuffInfo.u32BuffNum  = OM_SOCP_IND_BUFFER_NUM;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice = mdrv_timer_get_normal_timestamp();

    if (VOS_ERROR != g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit: The UDI Handle is not Null !");
        /*lint +e534*/

        return;
    }

    /* ��OMʹ�õ�USBͨ�� */
    g_astOMPortUDIHandle[enHandle] = mdrv_udi_open(&stUdiPara);

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit: Open UDI ACM failed!");
        /*lint +e534*/

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice = mdrv_timer_get_normal_timestamp();

    /* ����OMʹ�õ�USBͨ������ */
    if (VOS_OK != mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_RELLOC_READ_BUFF, &stReadBuffInfo))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_RELLOC_READ_BUFF Failed\r\n");
        /*lint +e534*/

        return;
    }

    /* ע��OMʹ�õ�USB�����ݻص����� */
    if (VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], UDI_ACM_IOCTL_SET_READ_CB, pReadCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl UDI_ACM_IOCTL_SET_READ_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_WRITE_CB, pWriteCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if(VOS_OK != PPM_UdiRegCallBackFun(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_SET_EVT_CB, pStateCB))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_SET_WRITE_CB Failed\r\n");
        /*lint +e534*/

        return;
    }

    if (VOS_OK != mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_DO_COPY, VOS_NULL_PTR))
    {
        /*lint -e534*/
        LogPrint("\r\n PPM_ReadPortDataInit, mdrv_udi_ioctl ACM_IOCTL_WRITE_DO_COPY Failed\r\n");
        /*lint +e534*/

        return;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num++;
    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice = mdrv_timer_get_normal_timestamp();

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_PortSend
 ��������  : �����������ͨ���첽���͸�PC��
 �������  :  enHandle: ���Ͷ˿ھ����ö�ٶ���
              pucVirAddr:   �������ַ
              pucPhyAddr:   ����ʵ��ַ
              ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERROR/VOS_OK
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_PortSend(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_INT32           lRet;
    ACM_WR_ASYNC_INFO   stVcom;
    VOS_UINT32          ulInSlice;
    VOS_UINT32          ulOutSlice;
    VOS_UINT32          ulWriteSlice;
//    VOS_CHAR            aucUsbLog[100];

    if((OM_USB_CFG_PORT_HANDLE == enHandle)
        || (OM_HSIC_CFG_PORT_HANDLE == enHandle))
    {
        diag_PTR(EN_DIAG_PTR_PPM_PORTSEND);
    }

    if ((VOS_NULL_PTR == pucVirAddr) || (VOS_NULL_PTR == pucPhyAddr))
    {
        /* ��ӡ���� */
        /*lint -e534*/
        LogPrint("\r\nPPM_PortSend: Vir or Phy Addr is Null \n");
        /*lint +e534*/

        return CPM_SEND_PARA_ERR;
    }

    stVcom.pVirAddr = (VOS_CHAR*)pucVirAddr;
    stVcom.pPhyAddr = (VOS_CHAR*)pucPhyAddr;
    stVcom.u32Size  = ulDataLen;
    stVcom.pDrvPriv = VOS_NULL_PTR;

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1++;

    if (VOS_ERROR == g_astOMPortUDIHandle[enHandle])
    {
        /*lint -e534*/
        LogPrint("\r\nPPM_PortSend: USB HANDLE  is err. \n");
        /*lint +e534*/

        return CPM_SEND_ERR;
    }

    ulInSlice = mdrv_timer_get_normal_timestamp();

    if(OM_USB_IND_PORT_HANDLE == enHandle)
    {
        g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendLen += ulDataLen;
    }

    /* ����д�����ݳ��ȴ���д�����ɹ� */
    lRet = mdrv_udi_ioctl(g_astOMPortUDIHandle[enHandle], ACM_IOCTL_WRITE_ASYNC, &stVcom);

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2++;

    ulOutSlice = mdrv_timer_get_normal_timestamp();

    if(ulInSlice > ulOutSlice)
    {
        ulWriteSlice = (0xffffffff - ulInSlice) + ulOutSlice;
    }
    else
    {
        ulWriteSlice = ulOutSlice - ulInSlice;
    }

    if(ulWriteSlice > g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime)
    {
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime = ulWriteSlice;
    }

    if (MDRV_OK == lRet)     /*��ǰ���ͳɹ�*/
    {
        /* αͬ���ӿڣ���ȡ�ź��� */
        PPM_PortPseudoSyncGetSmp(enHandle);

        return CPM_SEND_AYNC;

    }
    else if(MDRV_OK > lRet)    /*��ʱ����*/
    {
        /*��ӡ��Ϣ������UDI�ӿڵĴ�����Ϣ*/
        /*lint -e534*/
        LogPrint1("\r\nPPM_PortSend: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum++;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen    += ulDataLen;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue  = (VOS_UINT32)lRet;
        g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime   = mdrv_timer_get_normal_timestamp();


        g_ulUSBSendErrCnt++;

        return CPM_SEND_FUNC_NULL; /*������ʱ������Ҫ����NULL��������*/
    }
    else    /*����������Ҫ��λ����*/
    {
        /*��ӡ��Ϣ������UDI�ӿ�*/
        /*lint -e534*/
        LogPrint1("\r\nPPM_PortSend: mdrv_udi_ioctl Send Data return Error %d\n", lRet);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_USB_SEND_ERROR, lRet, (VOS_INT)enHandle,
                             (VOS_CHAR *)&g_stAcpuDebugInfo, (VOS_INT)sizeof(OM_ACPU_DEBUG_INFO));

        return CPM_SEND_ERR;
    }
}

/*****************************************************************************
 �� �� ��  :GU_OamPortWriteAsyCB
 ��������  :OM�첽���ͻص�����
 �������  :enHandle:UDI���
            pucData:��Ҫ���͵���������
            lLen:���ݳ���
 �������  :��
 �� �� ֵ  :��
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_PortWriteAsyCB(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8* pucData, VOS_INT lLen)
{
    VOS_UINT32      ulRlsLen;

    if(lLen < 0)
    {
        ulRlsLen = 0;
    }
    else
    {
        ulRlsLen = (VOS_UINT32)lLen;
    }

    /* ͳ������ͨ���������� */
    if(OM_USB_IND_PORT_HANDLE == enHandle)
    {
        diag_ThroughputSave(EN_DIAG_THRPUT_DATA_CHN_CB, lLen);
    }

    /* αͬ���ӿڣ��ͷ��ź��� */
    if (OM_USB_IND_PORT_HANDLE == enHandle)
    {
        g_stUsbIndPseudoSync.ulLen          = ulRlsLen;
        g_stUsbIndPseudoSync.pucAsyncCBData = pucData;

        SCM_RlsDestBuf(SOCP_CODER_DST_OM_IND, ulRlsLen);
    }
    else if (OM_USB_CFG_PORT_HANDLE == enHandle)
    {
        g_stUsbCfgPseudoSync.ulLen          = ulRlsLen;
        g_stUsbCfgPseudoSync.pucAsyncCBData = pucData;

        SCM_RlsDestBuf(SOCP_CODER_DST_OM_CNF, ulRlsLen);
    }
    else
    {
        ;
    }

    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum++;

    return;
}


OM_PSEUDO_SYNC_STRU * PPM_ComPpmGetSyncInfo(VOS_VOID)
{
    return &g_stUsbIndPseudoSync;
}

OM_ACPU_DEBUG_INFO * PPM_ComPpmGetDebugInfo(VOS_VOID)
{
    return &g_stAcpuDebugInfo;
}


/*****************************************************************************
 �� �� ��  : PPM_InitPhyPort
 ��������  : ��ʼ������ͨ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��
 �޸���ʷ:
     1. ����:2012-01-21
         �޸���:s00207770
         �޸�ԭ��:���SOCKET�˿ڳ�ʼ��
     2. ����:2013-12-29
         �޸���:s00207770
         �޸�ԭ��:�޸�LOG�����ʼ���ӿ�
*****************************************************************************/
VOS_UINT32 PPM_InitPhyPort(VOS_VOID)
{
    if (VOS_OK != PPM_PortInit())
    {
        vos_printf("PPM_InitPhyPort: PPM_PortInit failed.\n");
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_PortInit
 ��������  : �˿�ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK   - ��ʼ���ɹ�
             VOS_ERR  - ��ʼ��ʧ��

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_PortInit(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stAcpuDebugInfo, 0, sizeof(g_stAcpuDebugInfo));

    VOS_MemSet(g_astOMPortUDIHandle, VOS_ERROR, sizeof(g_astOMPortUDIHandle));

    VOS_MemSet(&g_stPpmPortSwitchInfo, 0, sizeof(g_stPpmPortSwitchInfo));
    /*lint +e534*/

    VOS_SpinLockInit(&g_stPpmPortSwitchSpinLock);

    /* USB���ص�����˿�ͨ���ĳ�ʼ�� */
    PPM_UsbPortInit();

    /* Hsic���ص�����˿�ͨ���ĳ�ʼ�� */
    PPM_HsicPortInit();

    /* Vcom���ص�����˿�ͨ���ĳ�ʼ�� */
    PPM_VComPortInit();

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : OmOpenLog
 ��������  : ��ӡ��ǰOMͨ����״̬
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2009��5��18��
     ��    ��  : g47350
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID OmOpenLog(VOS_UINT32 ulFlag)
{
    g_ulOmAcpuDbgFlag = ulFlag;

    return;
}


/*****************************************************************************
 �� �� ��  : PPM_OmPortInfoShow
 ��������  : ���ڴ�ӡ��ǰͨ����ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2011��3��10��
     ��    ��  : l46160
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_OmPortInfoShow(OM_PROT_HANDLE_ENUM_UINT32  enHandle)
{
    /*lint -e534*/
    vos_printf("\r\nInvalidchanel num is             %d",   g_stAcpuDebugInfo.ulInvaldChannel);
    
    vos_printf("\r\nThe Port Write num 1 is          %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum1);
    vos_printf("\r\nThe Port Write num 2 is          %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteNum2);
    vos_printf("\r\nThe Port Write Max Time is       0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteMaxTime);

    vos_printf("\r\nThe Port Write CB Num is         %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteCBNum);

    vos_printf("\r\nThe Port Write Err Time is       %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrTime);
    vos_printf("\r\nThe Port Write Err Num  is       %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrNum);
    vos_printf("\r\nThe Port Write Err Value is      0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrValue);
    vos_printf("\r\nThe Port Write Err Len is        0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBWriteErrLen);

    vos_printf("\r\nThe Port In CB Num is            %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINNum);
    vos_printf("\r\nThe Port In CB Time is           0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBINTime);
    vos_printf("\r\nThe Port Out CB Num is           %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutNum);
    vos_printf("\r\nThe Port Out CB Time is          0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOutTime);
    vos_printf("\r\nThe Port State CB Err Num is     %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrNum);
    vos_printf("\r\nThe Port State CB Err Time is    0x%x", g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBStateErrTime);

    vos_printf("\r\nThe Port Open num is            %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenNum);
    vos_printf("\r\nThe Port Open slice is          0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenSlice);

    vos_printf("\r\nThe Port Open OK num is         %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkNum);
    vos_printf("\r\nThe Port Open OK slice is       0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOkSlice);

    vos_printf("\r\nThe Port Open OK2 num is        %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Num);
    vos_printf("\r\nThe Port Open OK2 slice is      0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBOpenOk2Slice);

    vos_printf("\r\nThe Port Close num is           %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseNum);
    vos_printf("\r\nThe Port Close slice is         0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseSlice);

    vos_printf("\r\nThe Port Close OK num is        %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkNum);
    vos_printf("\r\nThe Port Close OK slice is      0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCloseOkSlice);

    vos_printf("\r\nUSB IND Pseudo sync fail num is   %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailNum);
    vos_printf("\r\nUSB IND Pseudo sync fail slice is 0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBIndPseudoSyncFailSlice);
    vos_printf("\r\nUSB CFG Pseudo sync fail num is   %d",    g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailNum);
    vos_printf("\r\nUSB CFG Pseudo sync fail slice is 0x%x",  g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBCnfPseudoSyncFailSlice);

    vos_printf("\r\nThe Port UDI Handle Err num is %d",                 g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleErr);
    vos_printf("\r\nThe Port UDI Handle Get Buffer Err num is %d",      g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadGetBufferErr);
    vos_printf("\r\nThe Port UDI Handle Comm Rcv Null Ptr num is %d",   g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiCommRcvNullPtrErr);
    vos_printf("\r\nThe Port UDI Handle Read Buffer Free Err num is %d",g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBUdiHandleReadBufferFreeErr);

    vos_printf("\r\nThe Port UDI Handle Total Rcv Pkt num is %d",       g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktNum);
    vos_printf("\r\nThe Port UDI Handle Total Rcv Byte is %d",          g_stAcpuDebugInfo.astPortInfo[enHandle].ulUSBRcvPktByte);
    /*lint +e534*/

    return;
}


/*****************************************************************************
 �� �� ��  : PPM_OmPortDebugInfoShow
 ��������  : ���ڴ�ӡCNF\INDͨ����ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2015��11��2��
     ��    ��  : c00326366
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_OmPortDebugInfoShow(VOS_VOID)
{
    vos_printf("IND ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d.\r\n",
    g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stIndDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stIndDebugInfo.ulUSBSendLen);

    vos_printf("CNF ulOmDiscardNum %d, len %d; ulUSBSendErrNum %d, Len %d; ulUSBSendNum %d, len %d.\r\n",
    g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulOmDiscardLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendErrLen,
    g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendNum, g_stAcpuDebugInfo.stCnfDebugInfo.ulUSBSendLen);
}

/*****************************************************************************
 �� �� ��  : PPM_PortSwitchInfoShow
 ��������  : ���ڴ�ӡ�˿��л���ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2014��6��10��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_PortSwitchInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n Port Type Err num is %d", g_stPpmPortSwitchInfo.ulPortTypeErr);

    vos_printf("\r\n Port Switch Fail time is %d", g_stPpmPortSwitchInfo.ulSwitchFail);

    vos_printf("\r\n Port Switch Success time is %d", g_stPpmPortSwitchInfo.ulSwitchSucc);

    vos_printf("\r\n Port Switch Start slice is 0x%x", g_stPpmPortSwitchInfo.ulStartSlice);

    vos_printf("\r\n Port Switch End slice is 0x%x", g_stPpmPortSwitchInfo.ulEndSlice);
    /*lint +e534*/

    return;
}







