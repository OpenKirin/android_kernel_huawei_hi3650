

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "PsLib.h"
#include "TafNvInterface.h"
#include "NVIM_Interface.h"
#include <product_config.h>




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_CORE_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

DMS_MAIN_INFO                           g_stDmsMainInfo = {0};

static const struct file_operations     g_stPortCfgOps =
{
    .owner      = THIS_MODULE,
    .write      = DMS_WritePortCfgFile,
    .read       = DMS_ReadPortCfgFile,
};

static const struct file_operations g_stGetSliceOps      =
{
    .owner      = THIS_MODULE,
    .read       = DMS_ReadGetSliceFile,
};

static const struct file_operations     g_stModemStatus =
{
    .owner      = THIS_MODULE,
    .read       = DMS_ReadModemStatusFile,
};

DMS_NLK_ENTITY_STRU                     g_stDmsNlkEntity = {0};

static struct netlink_kernel_cfg        g_stDmsNlkCfg =
{
    .input      = DMS_NLK_Input,
};

VOS_UINT8                               g_ucDmsPrintModemLogType = 0;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/

extern VOS_VOID At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern void *hisi_io_memcpy(void *dest, const void *src, unsigned int count);
/* ���pclint���� */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : DMS_ReadPortDebugCfgNV
 ��������  : ��ȡ�˿� Debug ������ص�NV��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��03��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_ReadPortDebugCfgNV(VOS_VOID)
{
    TAF_NV_PORT_DEBUG_CFG_STRU          stPortDebugNVCfg;
    VOS_UINT32                          ulAppVcomPortIdMask;
    VOS_UINT32                          ulDebugLevel;

    VOS_MemSet(&stPortDebugNVCfg, 0, sizeof(TAF_NV_PORT_DEBUG_CFG_STRU));

    /* ��ȡNV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_DMS_DEBUG_CFG,
                          &stPortDebugNVCfg,
                           sizeof(TAF_NV_PORT_DEBUG_CFG_STRU)))
    {
        return;
    }

    ulAppVcomPortIdMask = stPortDebugNVCfg.ulAppVcomPortIdMask;
    ulDebugLevel        = stPortDebugNVCfg.ulDebugLevel;

    APP_VCOM_SendDebugNvCfg(ulAppVcomPortIdMask, ulDebugLevel);

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_ReadGetModemLogCfgNV
 ��������  : ��ȡ�����Ƿ���Եõ�modem log��NV���е�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��17��
   ��    ��   : w00316404
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_ReadGetModemLogCfgNV(VOS_VOID)
{
    TAF_NV_PRINT_MODEM_LOG_TYPE_STRU    stPrintModemLogType;

    VOS_MemSet(&stPrintModemLogType, 0x00, sizeof(stPrintModemLogType));

    /* ��ȡNV�� */
    if (NV_OK != NV_Read(en_NV_Item_Print_Modem_Log_Type,
                         &stPrintModemLogType,
                         sizeof(TAF_NV_PRINT_MODEM_LOG_TYPE_STRU)))
    {
        return;
    }

    DMS_SET_PRINT_MODEM_LOG_TYPE(stPrintModemLogType.ucPrintModemLogType);

    return;
}

/*****************************************************************************
 �� �� ��  : initDmsMainInfo
 ��������  : ��ʼ��DMSȫ�ֱ���
 �������  :

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
   2.��    ��  : 2013��07��222��
     ��    ��  : j00177245
     �޸�����  : �������warning
   3.��    ��  : 2013��09��03��
     ��    ��  : z60575
     �޸�����  : DTS2013090208292,NVE��ʼ��ֻ��һ��
   4.��    ��  : 2014��08��25��
     ��    ��  : j00174725
     �޸�����  : DTS2014082200355 proc/portcfgȨ���޸�
   5.��    ��   : 2015��6��25��
     ��    ��   : l00198894
     �޸�����   : TSTS
   6.��    ��   : 2015��10��17��
     ��    ��   : w00316404
     �޸�����   : �����Ƿ��ӡmodem log
   7.��    ��   : 2016��01��22��
     ��    ��   : z00301431
     �޸�����   : DTS2015103001118,set modemstatus
*****************************************************************************/
VOS_VOID DMS_Init(VOS_VOID)
{
    VOS_UINT32                          ulport;

    VOS_MemSet(g_astDmsSdmInfoTable, 0, sizeof(g_astDmsSdmInfoTable));

    g_stDmsMainInfo.pfnRdDataCallback  = NULL;
    g_stDmsMainInfo.pfnConnectCallBack = NULL;

    /*��ʼ�����ж˿ڵ�handle*/
    for (ulport = 0; ulport < DMS_PHY_BEAR_LAST; ulport++)
    {
        g_stDmsMainInfo.stPhyProperty[ulport].lPortHandle = UDI_INVALID_HANDLE;
    }

    /*����ͨ��Ĭ�����ԣ����ڶ������ͨ����������Ӧһ���߼�ͨ��*/
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_PCUI].enLogicChan  = DMS_CHANNEL_AT;
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_CTRL].enLogicChan  = DMS_CHANNEL_AT;
    g_stDmsMainInfo.stPhyProperty[DMS_PHY_BEAR_USB_PCUI2].enLogicChan = DMS_CHANNEL_AT;



    /* ��ʼ��ATͨ��ʹ�õľ�̬�ڴ� */
    Dms_StaticBufInit();


    DMS_ReadPortDebugCfgNV();

    mdrv_usb_reg_enablecb(DMS_UsbEnableCB);
    mdrv_usb_reg_disablecb(DMS_UsbDisableCB);

    wake_lock_init(&g_stDmsMainInfo.stwakelock, WAKE_LOCK_SUSPEND, "dms_wakelock");

    DMS_ReadGetModemLogCfgNV();

    return;
}


/*****************************************************************************
 �� �� ��  : DMS_GetConnStaFun
 ��������  : ��ȡͨ�����Ӵ�����
 �������  :

 �������  :
 �� �� ֵ  : VOS_NULL/�ص�����
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
DMS_CONNECT_STA_PFN DMS_GetConnStaFun(VOS_VOID)
{
    return (DMS_GetMainInfo()->pfnConnectCallBack);
}

/*****************************************************************************
 �� �� ��  : DMS_SetConnStaCB
 ��������  : ͨ�������¼�����ע�ắ��
 �������  : pfnReg: �ص�����ָ��

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID DMS_SetConnStaCB(DMS_CONNECT_STA_PFN pfnReg)
{
    DMS_MAIN_INFO                      *pstMainInfo = DMS_GetMainInfo();

    if (NULL == pfnReg)
    {
        return;
    }

    pstMainInfo->pfnConnectCallBack = pfnReg;
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_GetDataReadFun
 ��������  : ��ȡ���ص�����
 �������  :
 �������  :
 �� �� ֵ  : �ص�����ָ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
DMS_READ_DATA_PFN DMS_GetDataReadFun(VOS_VOID)
{
    return g_stDmsMainInfo.pfnRdDataCallback;
}

/*****************************************************************************
 �� �� ��  : DMS_GetMainInfo
 ��������  : ��ȡDMSȫ�ֱ���ָ��
 �������  :
 �������  :
 �� �� ֵ  : ȫ�ֱ���ָ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
DMS_MAIN_INFO* DMS_GetMainInfo(VOS_VOID)
{
    return &g_stDmsMainInfo;
}

/*****************************************************************************
 �� �� ��  : DMS_GetPhyBearProperty
 ��������  : ��ȡ����ͨ�����ݽṹָ��
 �������  :
 �������  :
 �� �� ֵ  : �ṹ��ָ��
 ���ú���  :
 ��������  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
 DMS_PHY_BEAR_PROPERTY_STRU* DMS_GetPhyBearProperty(DMS_PHY_BEAR_ENUM enPhyBear)
{
    return &(DMS_GetMainInfo()->stPhyProperty[enPhyBear]);
}

/*****************************************************************************
 �� �� ��  : DMS_UsbDisableCB
 ��������  : USB�γ��¼�������
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
   2.��    ��  : 2012��8��27��
     ��    ��  : marenkun
     �޸�����  : ��ȡat server nv��ж��Ƿ�ر�pcui&Ctrl��
   3.��    ��  : 2013��09��03��
     ��    ��  : z60575
     �޸�����  : DTS2013090208292,NVE��ʼ��ֻ��һ��
   4.��    ��   : 2015��5��22��
     ��    ��   : l00198894
     �޸�����   : TSTS
*****************************************************************************/
VOS_VOID DMS_UsbDisableCB(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE, 0, 0, 0);

    /* nvֵΪ1��ʾ��at sever����1��ʾ��at sever����at sever�ر�pcui��ctrl�� */
    if (VOS_TRUE == g_stDmsMainInfo.bPortOpenFlg)
    {
        /* �ر�PCUIͨ�� */
        ulRet = DMS_VcomPcuiClose();
        if(ERR_MSP_SUCCESS!=ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 3);
        }

        /* �ر�CTRLͨ�� */
        ulRet = DMS_VcomCtrlClose();
        if(ERR_MSP_SUCCESS!=ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 5);
        }

        /* �ر�PCUI2ͨ�� */
        ulRet = DMS_VcomPcui2Close();
        if(ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 6);
        }

    }

    /* �ر�NDIS CTRLͨ�� */
    ulRet =  DMS_NcmClose();
    if(ERR_MSP_SUCCESS!=ulRet)
    {
        DMS_DBG_SDM_FUN(DMS_SDM_USB_DISABLE_ERR,0, 0, 4);
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : DMS_UsbEnableCB
 ��������  : USBö����ɴ�����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
   2.��    ��  : 2012��8��27��
     ��    ��  : marenkun
     �޸�����  : ��ȡat server nv��ж��Ƿ��pcui&Ctrl��
   3.��    ��  : 2013��09��03��
     ��    ��  : z60575
     �޸�����  : DTS2013090208292,NVE��ʼ��ֻ��һ��
   4.��    ��   : 2015��5��22��
     ��    ��   : l00198894
     �޸�����   : TSTS
*****************************************************************************/
VOS_VOID DMS_UsbEnableCB(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    NVE_INFO_S                          stAtServerNv;

    VOS_MemSet(&stAtServerNv, 0, sizeof(NVE_INFO_S));
    VOS_MemCpy(stAtServerNv.nv_name, "ATSERV", sizeof("ATSERV"));
    stAtServerNv.nv_number      = NVE_AT_SERVER_INDEX;
    stAtServerNv.nv_operation   = NVE_READ_OPERATE;
    stAtServerNv.valid_size     = 1;

    DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE, 0, 0, 0);

    /* NVEֻ��ȡһ�Σ���ȡ���ٶ�ȡ */
    if (VOS_FALSE == g_stDmsMainInfo.bPortCfgFlg)
    {
        g_dms_debug_atserv_nv_info.ulNvValue        = stAtServerNv.nv_data[0];

        g_stDmsMainInfo.bPortCfgFlg                 = VOS_TRUE;

        /* nvֵΪ1��ʾ��at sever����1��ʾ��at sever����at sever��pcui��ctrl�� */
        if ((1 != stAtServerNv.nv_data[0])
            )
        {
            g_stDmsMainInfo.ulPortCfgValue = DMS_TEST_MODE;
        }
        else
        {
            g_stDmsMainInfo.ulPortCfgValue = DMS_NORMAL_MODE;
        }
    }

    if (DMS_TEST_MODE == g_stDmsMainInfo.ulPortCfgValue)
    {
        g_stDmsMainInfo.bPortOpenFlg = VOS_TRUE;

        /*�� AT PCUI ͨ��*/
        ulRet = DMS_VcomPcuiOpen();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 3);
        }

        /*�� AT CTRL ͨ��*/
        ulRet = DMS_VcomCtrlOpen();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 5);
        }

        /*�� AT PCUI2 ͨ��*/
        ulRet = DMS_VcomPcui2Open();
        if (ERR_MSP_SUCCESS != ulRet)
        {
            DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 6);
        }
    }

    /*�� NDIS CTRL ͨ��*/
    ulRet = DMS_NcmOpen();
    if (ERR_MSP_SUCCESS != ulRet)
    {
        DMS_DBG_SDM_FUN(DMS_SDM_USB_ENABLE_ERR, 0, 0, 4);
    }

    g_ulNdisCfgFlag = 1;

    return ;
}

/*****************************************************************************
 �� �� ��  : DMS_GetPortHandle
 ��������  : ��ȡ����˿ھ��
 �������  : enPhyBear --- ����˿ں�
 �������  : ��
 �� �� ֵ  : UDI_HANDLE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��4��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
UDI_HANDLE DMS_GetPortHandle(DMS_PHY_BEAR_ENUM enPhyBear)
{
    return (DMS_GetMainInfo()->stPhyProperty[enPhyBear].lPortHandle);
}

/*****************************************************************************
 �� �� ��  : DMS_DsFidInit
 ��������  : dms FID ��ʼ������
 �������  :

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 DMS_DsFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal = 0;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:

        DMS_Init();

        ulRelVal = VOS_RegisterPIDInfo(WUEPS_PID_AT, (Init_Fun_Type) At_PidInit, (Msg_Fun_Type) At_MsgProc);
        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterTaskPrio(MSP_APP_DS_FID, DMS_APP_DS_TASK_PRIORITY);
        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }

        break;

    default:
        break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_InitPorCfgFile
 ��������  : OnDemand�����ļ���ʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : z60575
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��08��25��
    ��    ��   : j00174725
    �޸�����   : DTS2014082200355
*****************************************************************************/
VOS_INT __init DMS_InitPorCfgFile(VOS_VOID)
{
    printk("DMS_InitPorCfgFile,entry,%u",VOS_GetSlice());

    g_stDmsMainInfo.bPortCfgFlg     = VOS_FALSE;
    g_stDmsMainInfo.bPortOpenFlg    = VOS_FALSE;
    g_stDmsMainInfo.ulPortCfgValue  = DMS_TEST_MODE;

    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("portcfg", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stPortCfgOps))
    {
        DMS_LOG_ERROR("DMS_InitPorCfgFile: proc_create return NULL.\n");
        return -ENOMEM;
    }
    /*lint +e960 */

    printk("DMS_InitPorCfgFile,exit,%u",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 �� �� ��  : DMS_ReadPortCfgFile
 ��������  : PortCfg�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : z6057
    �޸�����   : �����ɺ���
*****************************************************************************/
ssize_t DMS_ReadPortCfgFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_PORTCFG_FILE_LEN];
    VOS_UINT32                          ulLength;

    if (*ppos > 0)
    {
        return 0;
    }

    VOS_MemSet(acModeTemp, 0x00, DMS_PORTCFG_FILE_LEN);

    VOS_sprintf((VOS_CHAR *)acModeTemp, "%d", g_stDmsMainInfo.ulPortCfgValue);

    ulLength        = VOS_StrLen(acModeTemp);
    len             = PS_MIN(len, ulLength);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        return -EPERM;
    }

}

/*****************************************************************************
 �� �� ��  : DMS_WritePortCfgFile
 ��������  : PortCfg�����ļ�дʵ��
 �������  : file ----- �ļ����
             buf  ----- �û��ռ�����
             lLength -- �û����ݳ���
             ppos - ----�ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : z6057
    �޸�����   : �����ɺ���
*****************************************************************************/
ssize_t DMS_WritePortCfgFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_PORTCFG_FILE_LEN];
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulValue;

    ulValue = 0;
    VOS_MemSet(acModeTemp, 0x00, DMS_PORTCFG_FILE_LEN);

    if (NULL == buf)
    {
        return -EFAULT;
    }

    if (len >= DMS_PORTCFG_FILE_LEN)
    {
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    if (copy_from_user((VOS_VOID *)acModeTemp, (VOS_VOID *)buf, (VOS_ULONG)len) > 0)
    {
        return -EFAULT;
    }

    acModeTemp[len] = '\0';

    ulStrLen = VOS_StrLen(acModeTemp);

    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (acModeTemp[i] >= '0') && (acModeTemp[i] <= '9') )
        {
            ulValue = (ulValue * 10) + (acModeTemp[i] - '0');
        }
    }

    g_stDmsMainInfo.ulPortCfgValue  = ulValue;

    /* ����Ѿ�д������ļ�������д��ֵΪ׼����������Ҫ�ٶ�NVE */
    g_stDmsMainInfo.bPortCfgFlg     = TRUE;

    return (ssize_t)len;
}

module_init(DMS_InitPorCfgFile);
module_init(DMS_InitGetSliceFile);

/*****************************************************************************
 �� �� ��  : DMS_RegOmChanDataReadCB
 ��������  : ע��OMͨ�����ݽ��ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanDataReadCB(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc
)
{
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;

    /* ���ͨ���źͺ���ָ�� */
    if ((enChan >= DMS_OM_CHAN_BUTT) || (VOS_NULL_PTR == pFunc))
    {
        printk(KERN_ERR "[%s][LINE: %d] Invalid channel %d.\n",
            __func__, __LINE__, (VOS_INT)enChan);
        return VOS_ERR;
    }

    /* ����ͨ�����ݻص����� */
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);
    pstOmChanProp->pDataFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_RegOmChanEventCB
 ��������  : ע��OMͨ���¼����ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanEventCB(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc
)
{
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;

    /* ���ͨ���� */
    if ((enChan >= DMS_OM_CHAN_BUTT) || (VOS_NULL_PTR == pFunc))
    {
        printk(KERN_ERR "[%s][LINE: %d] Invalid channel %d.\n",
            __func__, __LINE__, (VOS_INT)enChan);
        return VOS_ERR;
    }

    /* ����ͨ���¼��ص����� */
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);
    pstOmChanProp->pEvtFunc = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_WriteOmData
 ��������  : дOMͨ������
 �������  : enChan   --- �߼�ͨ��
             pucData  --- ���ݵ�ַ
             ulLength --- ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��17��
    ��    ��   : W00316404
    �޸�����   : �����Ƿ��ӡmodem log
*****************************************************************************/
VOS_UINT32 DMS_WriteOmData(
    DMS_OM_CHAN_ENUM_UINT32             enChan,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                          *pucMem = VOS_NULL_PTR;
    VOS_UINT32                          ulMemNum;
    VOS_UINT32                          ulLastMemSize;
    VOS_UINT32                          ulCnt;

    if (DMS_GET_PRINT_MODEM_LOG_TYPE())
    {
        DMS_DBG_NLK_UL_UNSUPPORT_WRITE_LOG_NUM(1);
        return VOS_ERR;
    }

    DMS_DBG_NLK_DL_TOTAL_PKT_NUM(1);

    /* ���ͨ�� */
    if (enChan >= DMS_OM_CHAN_BUTT)
    {
        DMS_DBG_NLK_DL_ERR_CHAN_PKT_NUM(1);
        return VOS_ERR;
    }

    /* ������� */
    if ((VOS_NULL_PTR == pucData) || (0 == ulLength))
    {
        DMS_DBG_NLK_DL_ERR_PARA_PKT_NUM(1);
        return VOS_ERR;
    }

    DMS_DBG_NLK_DL_NORM_CHAN_PKT_NUM(enChan, 1);

    /* �����ݷֿ�, ����һ�η��͹������� */
    pucMem        = pucData;
    ulMemNum      = (ulLength >= DMS_GET_NLK_THRESH_SIZE())?(ulLength / DMS_GET_NLK_DATA_SIZE()):0;
    ulLastMemSize = (ulLength >= DMS_GET_NLK_THRESH_SIZE())?(ulLength % DMS_GET_NLK_DATA_SIZE()):ulLength;

    wake_lock(&g_stDmsMainInfo.stwakelock);

    /* ���͹̶���С���ݿ� */
    for (ulCnt = 0; ulCnt < ulMemNum; ulCnt++)
    {
        DMS_NLK_Send(DMS_GET_NLK_PHY_BEAR(enChan), DMS_GET_NLK_MSG_TYPE(enChan), pucMem, DMS_GET_NLK_DATA_SIZE());
        pucMem += DMS_GET_NLK_DATA_SIZE();
    }

    /* �������һ�����ݿ� */
    if (0 != ulLastMemSize)
    {
        DMS_NLK_Send(DMS_GET_NLK_PHY_BEAR(enChan), DMS_GET_NLK_MSG_TYPE(enChan), pucMem, ulLastMemSize);
    }

    wake_unlock(&g_stDmsMainInfo.stwakelock);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_InitEntity
 ��������  : ��ʼ�� netlink ʵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��8��
    ��    ��   : A00165503
    �޸�����   : DTS2015050806031: ɾ������ָ���ʼ��, ��ֹ�������
*****************************************************************************/
VOS_VOID DMS_NLK_InitEntity(VOS_VOID)
{
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    pstNlkEntity = DMS_GET_NLK_ENTITY();

    /* netlink socket */
    pstNlkEntity->pstSock    = VOS_NULL_PTR;

    /* netlink ��Ϣ���ݿ��С */
    pstNlkEntity->ulDataSize   = DMS_NLK_DEFUALT_DATA_SIZE;

    /* netlink ��Ϣ���ݿ��С */
    pstNlkEntity->ulThreshSize = DMS_NLK_DEFUALT_DATA_SIZE * 2;

    /* netlink ������ؽ��̺� */
    pstNlkEntity->astPhyBearProp[DMS_NLK_PHY_BEAR_LTE].lPid     = DMS_NLK_INVALID_PID;
    pstNlkEntity->astPhyBearProp[DMS_NLK_PHY_BEAR_GU].lPid      = DMS_NLK_INVALID_PID;

    /* netlink �߼�ͨ������(LTE CLTR) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_CTRL].enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_CTRL].enMsgType = DMS_NLK_MSG_TYPE_LTE_CTRL;

    /* netlink �߼�ͨ������(LTE DATA) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_DATA].enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_LTE_DATA].enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;

    /* netlink �߼�ͨ������(GU DATA) */
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_GU_DATA].enPhyBear  = DMS_NLK_PHY_BEAR_GU;
    pstNlkEntity->astOmChanProp[DMS_OM_CHAN_GU_DATA].enMsgType  = DMS_NLK_MSG_TYPE_GU_DATA;

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_CfgOpen
 ��������  : ���߼�ͨ��
 �������  : pstNlkHdr --- netlink ��Ϣ
             enBear    --- �������
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_NLK_CfgOpen(
    struct nlmsghdr                    *pstNlkHdr,
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear
)
{
    DMS_NLK_PHY_BEAR_PROPERTY_STRU     *pstPhyBearProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pEvtFunc       = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;

    /* �����غ� */
    if (enPhyBear >= DMS_NLK_PHY_BEAR_BUTT)
    {
        printk("[%s][LINE: %d] Invalid PHY bearer %d.\n",
            __func__, __LINE__, (VOS_INT)enPhyBear);
        return VOS_ERR;
    }

    /* ���ó���PID */
    pstPhyBearProp = DMS_GET_NLK_PHY_BEAR_PROP(enPhyBear);
    pstPhyBearProp->lPid = pstNlkHdr->nlmsg_pid;

    /* ����������ó��ع�����ͨ�� */
    for (enChan = 0; enChan < DMS_OM_CHAN_BUTT; enChan++)
    {
        pEvtFunc = DMS_GET_NLK_OM_CHAN_EVT_CB_FUNC(enChan);

        /* ֪ͨ���������ͬ���߼�ͨ��ʹ����ͨ���� */
        if ((enPhyBear == DMS_GET_NLK_PHY_BEAR(enChan)) && (VOS_NULL_PTR != pEvtFunc))
        {
            pEvtFunc(enChan, DMS_CHAN_EVT_OPEN);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_CfgClose
 ��������  : �ر��߼�ͨ��
 �������  : pstNlkHdr --- netlink ��Ϣ
             enBear    --- �������
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DMS_NLK_CfgClose(
    struct nlmsghdr                    *pstNlkHdr,
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enBear
)
{
    DMS_NLK_PHY_BEAR_PROPERTY_STRU     *pstPhyBearProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pEvtFunc       = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;

    /* �����غ� */
    if (enBear >= DMS_NLK_PHY_BEAR_BUTT)
    {
        printk("[%s][LINE: %d] Invalid PHY bearer %d.\n",
            __func__, __LINE__, (VOS_INT)enBear);
        return VOS_ERR;
    }

    /* ���ó���PID */
    pstPhyBearProp = DMS_GET_NLK_PHY_BEAR_PROP(enBear);
    pstPhyBearProp->lPid = DMS_NLK_INVALID_PID;

    /* ����������ó��ع�����ͨ�� */
    for (enChan = 0; enChan < DMS_OM_CHAN_BUTT; enChan++)
    {
        pEvtFunc = DMS_GET_NLK_OM_CHAN_EVT_CB_FUNC(enChan);

        /* ֪ͨ���������ͬ���߼�ͨ��ʹ����ͨ���ر� */
        if ((enBear == DMS_GET_NLK_PHY_BEAR(enChan)) && (VOS_NULL_PTR != pEvtFunc))
        {
            pEvtFunc(enChan, DMS_CHAN_EVT_CLOSE);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_ProcLteCfgMsg
 ��������  : ����LTE CFG��Ϣ
 �������  : pstNlkHdr --- netlink ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteCfgMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = nlmsg_data(pstNlkHdr);

    switch (pstMsg->enCfg)
    {
        case DMS_NLK_CFG_TYPE_OPEN:
            (VOS_VOID)DMS_NLK_CfgOpen(pstNlkHdr, DMS_NLK_PHY_BEAR_LTE);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        case DMS_NLK_CFG_TYPE_CLOSE:
            (VOS_VOID)DMS_NLK_CfgClose(pstNlkHdr, DMS_NLK_PHY_BEAR_LTE);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        default:
            DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_ProcGuCfgMsg
 ��������  : ����GU CFG��Ϣ
 �������  : pstNlkHdr --- netlink ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_NLK_ProcGuCfgMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = nlmsg_data(pstNlkHdr);

    switch (pstMsg->enCfg)
    {
        case DMS_NLK_CFG_TYPE_OPEN:
            (VOS_VOID)DMS_NLK_CfgOpen(pstNlkHdr, DMS_NLK_PHY_BEAR_GU);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        case DMS_NLK_CFG_TYPE_CLOSE:
            (VOS_VOID)DMS_NLK_CfgClose(pstNlkHdr, DMS_NLK_PHY_BEAR_GU);
            DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;

        default:
            DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_ProcLteCtrlMsg
 ��������  : ����LTE CTRL��Ϣ
 �������  : pstNlkHdr --- netlink ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteCtrlMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc  = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* ��ȡͨ��ע��Ļص� */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_LTE_CTRL);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* ͸���������� */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_LTE_CTRL, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_ProcLteDataMsg
 ��������  : ����LTE DATA��Ϣ
 �������  : pstNlkHdr --- netlink ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_NLK_ProcLteDataMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc  = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* ��ȡͨ��ע��Ļص� */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_LTE_DATA);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* ͸���������� */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_LTE_DATA, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_ProcGuDataMsg
 ��������  : ����GU DATA��Ϣ
 �������  : pstNlkHdr --- netlink ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_NLK_ProcGuDataMsg(struct nlmsghdr *pstNlkHdr)
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPayload = VOS_NULL_PTR;

    /* ��ȡͨ��ע��Ļص� */
    pDataFunc = DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(DMS_OM_CHAN_GU_DATA);
    if (VOS_NULL_PTR != pDataFunc)
    {
        /* ͸���������� */
        pstPayload = nlmsg_data(pstNlkHdr);
        (VOS_VOID)pDataFunc(DMS_OM_CHAN_GU_DATA, pstPayload->aucData, pstPayload->ulLength);
        DMS_DBG_NLK_UL_SEND_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }
    else
    {
        DMS_DBG_NLK_UL_FREE_MSG_NUM(pstNlkHdr->nlmsg_type, 1);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_Send
 ��������  : ���� netlink ��Ϣ
 �������  : enPhyBear --- ������غ�
             enMsgType --- ��Ϣ����
             pucData   --- ����ָ��
             ulLength  --- ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT DMS_NLK_Send(
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear,
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
)
{
    struct sk_buff                     *pstSkb      = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr   = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstPlayload = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_INT                             lRet;

    DMS_DBG_NLK_DL_TOTAL_MSG_NUM(1);

    /* ��� netlink socket */
    if (VOS_NULL_PTR == DMS_GET_NLK_SOCK())
    {
        DMS_DBG_NLK_DL_ERR_SOCK_MSG_NUM(1);
        return -EIO;
    }

    /* ����������״̬ */
    if (DMS_NLK_INVALID_PID == DMS_GET_NLK_PHY_PID(enPhyBear))
    {
        DMS_DBG_NLK_DL_ERR_PID_MSG_NUM(1);
        return -EINVAL;
    }

    /* ���� netlink ��Ϣ */
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulLength;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);

    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    if (VOS_NULL_PTR == pstSkb)
    {
        DMS_DBG_NLK_DL_ALLOC_MSG_FAIL_NUM(1);
        return -ENOBUFS;
    }

    /* ��� netlink ��Ϣͷ */
    /* Use "ulMsgSize - sizeof(*pstNlkHdr)" here (incluing align pads) */
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)enMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);
    if (VOS_NULL_PTR == pstNlkHdr)
    {
        kfree_skb(pstSkb);
        DMS_DBG_NLK_DL_PUT_MSG_FAIL_NUM(1);
        return -EMSGSIZE;
    }

    /* ��� netlink ��Ϣ����PID */
    /*lint -e545*/
    NETLINK_CB(pstSkb).portid = DMS_GET_NLK_PHY_PID(enPhyBear);
    NETLINK_CB(pstSkb).dst_group = 0;
    /*lint +e545*/

    /* ��� netlink ��Ϣ���� */
    pstPlayload = nlmsg_data(pstNlkHdr);
    pstPlayload->ulLength = ulLength;

    memcpy(pstPlayload->aucData, pucData, ulLength);

    /* ���� netlink ��Ϣ */
    /*lint -e545*/
    lRet = netlink_unicast(DMS_GET_NLK_SOCK(), pstSkb, NETLINK_CB(pstSkb).portid, 0);

    /*lint +e545*/
    if (lRet < 0)
    {
        DMS_DBG_NLK_DL_UNICAST_MSG_FAIL_NUM(1);
        return lRet;
    }

    DMS_DBG_NLK_DL_UNICAST_MSG_SUCC_NUM(1);
    return 0;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_Input
 ��������  : netlink ��Ϣ���
 �������  : pstSkb --- skb buff
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��17��
    ��    ��   : W00316404
    �޸�����   : �����Ƿ��ӡmodem log
*****************************************************************************/
VOS_VOID DMS_NLK_Input(struct sk_buff *pstSkb)
{
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    if (DMS_GET_PRINT_MODEM_LOG_TYPE())
    {
        DMS_DBG_NLK_UL_UNSUPPORT_INPUT_LOG_NUM(1);
        return;
    }

    DMS_DBG_NLK_UL_TOTAL_MSG_NUM(1);

    /* ��ȡ netlink ��Ϣ */
    pstNlkHdr = nlmsg_hdr(pstSkb);

    /* ��� netlink ��Ϣ�Ƿ�Ϸ� */
    if (!NLMSG_OK(pstNlkHdr, pstSkb->len))
    {
        DMS_DBG_NLK_UL_ERR_MSG_NUM(1);
        return;
    }

    /* ���� netlink ��Ϣ */
    switch (pstNlkHdr->nlmsg_type)
    {
        case DMS_NLK_MSG_TYPE_LTE_CFG:
            DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_LTE_CTRL:
            DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_LTE_DATA:
            DMS_NLK_ProcLteDataMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_GU_CFG:
            DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
            break;

        case DMS_NLK_MSG_TYPE_GU_DATA:
            DMS_NLK_ProcGuDataMsg(pstNlkHdr);
            break;

        default:
            DMS_DBG_NLK_UL_UNKNOWN_MSG_NUM(1);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_Init
 ��������  : netlink ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_INT __init
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT __init DMS_NLK_Init(VOS_VOID)
{
    struct sock                        *pstSock      = VOS_NULL_PTR;
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    printk("DMS_NLK_Init,entry,%u",VOS_GetSlice());

    /* ��ʼ�� netlink ʵ�� */
    DMS_NLK_InitEntity();

    /* ���ں�̬����һ�� netlink socket */
    pstSock = netlink_kernel_create(&init_net, NETLINK_HW_LOGCAT, &g_stDmsNlkCfg);

    if (VOS_NULL_PTR == pstSock)
    {
        printk(KERN_ERR "[%s][LINE: %d] Fail to create netlink socket.\n",
            __func__, __LINE__);
        DMS_DBG_NLK_CREATE_SOCK_FAIL_NUM(1);
        return -ENOMEM;
    }

    /* ���� socket */
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = pstSock;

    printk("DMS_NLK_Init,exit,%u",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 �� �� ��  : DMS_NLK_Exit
 ��������  : netlink ж��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID __exit
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID __exit DMS_NLK_Exit(VOS_VOID)
{
    /* �ͷ� netlink socket */
    netlink_kernel_release(DMS_GET_NLK_SOCK());
    DMS_NLK_InitEntity();
    return;
}

/*****************************************************************************
 �� �� ��  : DMS_InitGetSliceFile
 ��������  : Get Slice�����ļ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2015��1��04��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT __init DMS_InitGetSliceFile(VOS_VOID)
{
    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("getslice", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stGetSliceOps))
    {
        DMS_LOG_ERROR("DMS_InitGetSliceFile: proc_create return NULL.\n");
        return VOS_ERR;
    }
    /*lint +e960 */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DMS_ReadGetSliceFile
 ��������  : getslice�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

�޸���ʷ      :
 1.��    ��   : 2015��1��04��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
ssize_t DMS_ReadGetSliceFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acModeTemp[DMS_GET_SLICE_FILE_LEN];
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulHigh32bitValue;
    VOS_UINT32                          ulLow32bitValue;

    if (*ppos > 0)
    {
        return 0;
    }

    /* ��ʼ�� */
    ulLength            = 0;
    ulHigh32bitValue    = 0;
    ulLow32bitValue     = 0;

    VOS_MemSet(acModeTemp, 0x00, DMS_GET_SLICE_FILE_LEN);

    /* ��ȡʱ��  Seattle �� Portland��һ�� */
    (VOS_VOID)mdrv_timer_get_accuracy_timestamp(&ulHigh32bitValue, &ulLow32bitValue);

    if (ulHigh32bitValue != 0)
    {
        VOS_sprintf((VOS_CHAR *)acModeTemp, "%x%08x", ulHigh32bitValue, ulLow32bitValue);
    }
    else
    {
        VOS_sprintf((VOS_CHAR *)acModeTemp, "%x", ulLow32bitValue);
    }

    ulLength        = VOS_StrLen(acModeTemp);
    len             = PS_MIN(len, ulLength);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        return -EPERM;
    }

}

/*****************************************************************************
 �� �� ��  : DMS_InitModemStatusFile
 ��������  : ModemStatus�ڵ��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VIOD

 �޸���ʷ      :
  1.��    ��   : 2016��1��20��
    ��    ��   : z00301431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT __init DMS_InitModemStatusFile(VOS_VOID)
{
    DMS_LOG_INFO("DMS_InitModemStatusFile,entry,%u \n",VOS_GetSlice());

    DMS_InitModemStatus();

    /*lint -e960 */
    if (VOS_NULL_PTR == proc_create("modemstatus", DMS_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stModemStatus))
    {
        DMS_LOG_ERROR("DMS_InitModemStatusFile: proc_create return NULL.\n");
        return -ENOMEM;
    }
    /*lint +e960 */

    DMS_LOG_INFO("DMS_InitModemStatusFile,exit,%u \n",VOS_GetSlice());

    return 0;
}

/*****************************************************************************
 �� �� ��  : DMS_ReadModemStatusFile
 ��������  : ModemStatusFile0�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

�޸���ʷ      :
 1.��    ��   : 2016��1��20��
   ��    ��   : z00301431
   �޸�����   : �����ɺ���
*****************************************************************************/
ssize_t DMS_ReadModemStatusFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    VOS_CHAR                            acStatus[DMS_MODEM_STATUS_FILE_LEN];
    VOS_UINT32                          ulStatusLen;

    if (*ppos > 0)
    {
        return 0;
    }

    VOS_MemSet(acStatus, 0x00, DMS_MODEM_STATUS_FILE_LEN);

    DMS_LOG_INFO("DMS_ReadModemStatusFile entry,time: %u, status: %d, %d, %d\n",
                 VOS_GetSlice(),
                 g_stDmsMainInfo.aucModemStatus[0],
                 g_stDmsMainInfo.aucModemStatus[1],
                 g_stDmsMainInfo.aucModemStatus[2]);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    VOS_sprintf((VOS_CHAR *)acStatus, "%s", g_stDmsMainInfo.aucModemStatus);

    ulStatusLen = VOS_StrLen(acStatus);

    len = PS_MIN(len, ulStatusLen);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acStatus, (VOS_ULONG)len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        DMS_LOG_ERROR("DMS_ReadModemStatusFile copy to user fail %u \n",VOS_GetSlice());
        return -EPERM;
    }
}

/*****************************************************************************
 �� �� ��  : DMS_SetModemStatus
 ��������  : ����MODEM ID����ModemStatus
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_VOID

�޸���ʷ      :
 1.��    ��   : 2016��1��20��
   ��    ��   : z00301431
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_SetModemStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= MODEM_ID_BUTT)
    {
        DMS_LOG_ERROR("DMS_SetModemStatus ModemId error %d \n",enModemId);
        return;
    }

    g_stDmsMainInfo.aucModemStatus[enModemId] = VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : DMS_GetModemStatus
 ��������  : ��ȡModemStatus
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : VOS_UINT32

�޸���ʷ      :
 1.��    ��   : 2016��1��20��
   ��    ��   : z00301431
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 DMS_GetModemStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (enModemId >= MODEM_ID_BUTT)
    {
        DMS_LOG_ERROR("DMS_GetModemStatus ModemId error %d \n",enModemId);
        return g_stDmsMainInfo.aucModemStatus[0];
    }

    return g_stDmsMainInfo.aucModemStatus[enModemId];
}

/*****************************************************************************
 �� �� ��  : DMS_InitModemStatus
 ��������  : ��ʼ�����е�ModemStatus
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID

�޸���ʷ      :
 1.��    ��   : 2016��1��20��
   ��    ��   : z00301431
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DMS_InitModemStatus(VOS_VOID)
{
    VOS_MemSet(g_stDmsMainInfo.aucModemStatus, 0x00, sizeof(g_stDmsMainInfo.aucModemStatus));
}


/* This function is called on driver initialization and exit */
module_init(DMS_InitModemStatusFile);
module_init(DMS_NLK_Init);
module_exit(DMS_NLK_Exit);



