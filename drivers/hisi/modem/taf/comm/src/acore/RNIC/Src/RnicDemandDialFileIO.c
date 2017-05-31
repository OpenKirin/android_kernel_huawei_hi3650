

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "RnicDemandDialFileIO.h"
#include "RnicCtx.h"
#include "RnicLog.h"
#include "RnicProcMsg.h"
#include "PsLib.h"

#include "RnicSndMsg.h"


#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <asm/uaccess.h>
#include <asm-generic/errno-base.h>
#include <kernel.h>



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_DEMAND_DIAL_FILE_IO_C
/*lint +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

static const struct file_operations g_stOnDemandFileOps        =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteOnDemandFile,
    .read       = RNIC_ReadOnDemandFile,
};

static const struct file_operations g_stIdleTimerOutFileOps    =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteIdleTimerOutFile,
    .read       = RNIC_ReadIdleTimerOutFile,
};

static const struct file_operations g_stDialEventReportFileOps =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteDialEventReportFile,
    .read       = RNIC_ReadDialEventReportFile,
};
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : RNIC_TransferStringToInt
 ��������  : ��app������ִ�ת��Ϊ����
 �������  : VOS_CHAR *pcString
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��10��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_TransferStringToInt(VOS_CHAR *pcString)
{
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    ulStrLen                            = 0;
    ulRst                               = 0;

    ulStrLen = VOS_StrLen(pcString);


    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulRst = (ulRst * 10) + (pcString[i] - '0');
        }
    }

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : RNIC_ReadOnDemandFile
 ��������  : OnDemand�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
ssize_t RNIC_ReadOnDemandFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];
    VOS_UINT32                          ulDialModeLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:ppos is err!");
        return 0;
    }

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf((VOS_CHAR *)acModeTemp, "%d", pstDialMode->enDialMode);

    ulDialModeLen = VOS_StrLen(acModeTemp);

    len             = PS_MIN(len, ulDialModeLen);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acModeTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:copy_to_user fail!");
        return -EPERM;
    }
}


/*****************************************************************************
 �� �� ��  : RNIC_WriteOnDemandFile
 ��������  : OnDemand�����ļ�дʵ��
 �������  : file ----- �ļ����
             buf  ----- �û��ռ�����
             lLength -- �û����ݳ���
             ppos - ----�ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE������������
*****************************************************************************/
ssize_t RNIC_WriteOnDemandFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_ONDEMAND_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:len is!", len);
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    if (copy_from_user((VOS_VOID *)acModeTemp, (VOS_VOID *)buf, len)  > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acModeTemp[len] = '\0';

    PS_PRINTF("RNIC_WriteOnDemandFile:acModeTemp %s len is %d\r\n", acModeTemp, len);

    stDialMode.enDialMode = RNIC_TransferStringToInt(acModeTemp);

    /* ���貦�� */
    if (RNIC_DIAL_MODE_DEMAND_CONNECT == stDialMode.enDialMode)
    {
        RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
    }
    else
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    }

    /* ���沦��ģʽ�������� */
    pstDialMode->enDialMode             = stDialMode.enDialMode;


    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_DIAL_MODE_INFO);

    return (ssize_t)len;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitOnDemandFile
 ��������  : OnDemand�����ļ���ʼ��
 �������  : proc_dir_entry *pstParentFileDirEntry -- ��Ŀ¼�����
 �������  : ��
 �� �� ֵ  : ��ʼ�����

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_InitOnDemandFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstOnDemandEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*����OnDemand�����ļ�*/
        pstOnDemandEntry                   = proc_create("dial/ondemand",
                                                        /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }
    else
    {
        /*����OnDemand�����ļ�*/
        pstOnDemandEntry                   = proc_create("ondemand",
                                                        /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_ReadIdleTimerOutFile
 ��������  : ideltimerout�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
ssize_t RNIC_ReadIdleTimerOutFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];
    VOS_UINT32                          ulIdleTimeLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:ppos ERR!");
        return 0;
    }

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);


    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acIdleTimeTemp, "%d", pstDialMode->ulIdleTime);

    ulIdleTimeLen  = VOS_StrLen(acIdleTimeTemp);

    len            = PS_MIN(len, ulIdleTimeLen);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf,(VOS_VOID *)acIdleTimeTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:copy_to_user ERR!");
        return -EPERM;
    }
}


/*****************************************************************************
 �� �� ��  : RNIC_WriteIdleTimerOutFile
 ��������  : idel_timerout�����ļ�дʵ��
 �������  : file ----- �ļ����
             buf  ----- �û��ռ�����
             lLength -- �û����ݳ���
             ppos - ----�ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE������������
*****************************************************************************/
ssize_t RNIC_WriteIdleTimerOutFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_IDLETIMEROUT_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:len is!", len);
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    if (copy_from_user((VOS_VOID *)acIdleTimeTemp, (VOS_VOID *)buf, len) > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acIdleTimeTemp[len]= '\0';

    stDialMode.ulIdleTime = RNIC_TransferStringToInt(acIdleTimeTemp);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    if (RNIC_DIAL_MODE_DEMAND_DISCONNECT == pstDialMode->enDialMode)
    {

        /* PDP��������ϴ����õ�ʱ����һ�£���Ҫ�������ŶϿ���ʱ�� */
        if ( pstDialMode->ulIdleTime != stDialMode.ulIdleTime)
        {
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
            RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
        }
    }

    pstDialMode->ulIdleTime             = stDialMode.ulIdleTime;


    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_IDLE_TIMEOUT_INFO);

    return (ssize_t)len;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIdleTimerOutFile
 ��������  : ideltimerout�����ļ���ʼ��
 �������  : proc_dir_entry *pstParentFileDirEntry -- ��Ŀ¼�����
 �������  : ��
 �� �� ֵ  : ��ʼ�����

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_InitIdleTimerOutFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstIdleTimeOutEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry )
    {
        /*����IdleTimeOut�����ļ�*/
        pstIdleTimeOutEntry                 = proc_create("dial/idle_timeout",
                                                         /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }
    else
    {
        /*����IdleTimeOut�����ļ�*/
        pstIdleTimeOutEntry                 = proc_create("idle_timeout",
                                                         /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_ReadDialEventReportFile
 ��������  : dial_event_report�����ļ���ʵ��
 �������  : file --- �ļ����
             buf  --- �û��ռ�
             ppos --- �ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
ssize_t RNIC_ReadDialEventReportFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];
    VOS_UINT32                          ulDialEventLen;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:ppos err!");
        return 0;
    }

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);


    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acDialEventTemp, "%d", pstDialMode->enEventReportFlag);

    ulDialEventLen = VOS_StrLen(acDialEventTemp);

    len            = PS_MIN(len, ulDialEventLen);

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    if (0 == copy_to_user(buf, (VOS_VOID *)acDialEventTemp, len))
    {
        *ppos += (loff_t)len;

        return (ssize_t)len;
    }
    else
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:copy_to_user err!");
        return -EPERM;
    }

}


/*****************************************************************************
 �� �� ��  : RNIC_WriteDialEventReportFile
 ��������  : dialeventreport�����ļ�дʵ��
 �������  : file ----- �ļ����
             buf  ----- �û��ռ�����
             lLength -- �û����ݳ���
             ppos - ----�ļ�ƫ�ƣ�����δʹ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : y00213812
    �޸�����   : DTS2012082204471, TQE������������
*****************************************************************************/
ssize_t RNIC_WriteDialEventReportFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);

    if (NULL == buf)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:buff is null");
        return -EFAULT;
    }

    if (len >= RNIC_EVENTFLAG_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:len is!",len);
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    if (copy_from_user((VOS_VOID *)acDialEventTemp, (VOS_VOID *)buf, len) > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acDialEventTemp[len] = '\0';

    PS_PRINTF("RNIC_WriteDialEventReportFile:acDialEventTemp %s len is %d\r\n", acDialEventTemp, len);

    stDialMode.enEventReportFlag    = RNIC_TransferStringToInt(acDialEventTemp);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    /* ���沦��ģʽ���������� */
    pstDialMode->enEventReportFlag      = stDialMode.enEventReportFlag;

    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_EVENT_REPORT_INFO);

    return (ssize_t)len;
}
/*****************************************************************************
 �� �� ��  : RNIC_InitDialEventReportFiles
 ��������  : proc_dir_entry *pstParentFileDirEntry -- ��Ŀ¼�����
 �������  : proc_dir_entry *pstParentFileDirEntry
 �������  : ��
 �� �� ֵ  : ��ʼ�����

 �޸���ʷ      :
  1.��    ��   : 2012��01��30��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_InitDialEventReportFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstDialEventReportEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*����dial_event_report�����ļ�*/
        pstDialEventReportEntry             = proc_create("dial/dial_event_report",
                                                          /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }

    }
    else
    {

        /*����dial_event_report�����ļ�*/
        pstDialEventReportEntry             = proc_create("dial_event_report",
                                                          /*lint -e960 �޸���:l60609;ԭ��:64bit*/
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          /*lint +e960 �޸���:l60609;ԭ��:64bit*/
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitDemandDialFile
 ��������  : ��ʼ�����貦�ļ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��1��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_InitDemandDialFile(VOS_VOID)
{
    struct proc_dir_entry              *stProcDemandDialDir;
    VOS_UINT32                          ulRlst;
    struct path                         path;
    int                                 error = 0;

    error = kern_path("/proc/dial", LOOKUP_FOLLOW, &path);
    if (error)
    {

        stProcDemandDialDir = proc_mkdir("dial", VOS_NULL_PTR);
        if (VOS_NULL_PTR == stProcDemandDialDir)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:proc_mkdir Fail!");
            return VOS_ERR;
        }
    }
    else
    {
        stProcDemandDialDir = VOS_NULL_PTR;
        RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:kern_path proc/dial is exist!");
    }

    ulRlst                              = RNIC_InitOnDemandFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitOnDemandFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitIdleTimerOutFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {


        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitIdleTimerOutFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitDialEventReportFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitDialEventReportFile err!");

        return VOS_ERR;
    }

    return VOS_OK;
}


