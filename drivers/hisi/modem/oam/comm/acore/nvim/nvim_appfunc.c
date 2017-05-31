


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "nvim_internalfunc.h"
#include "mdrv.h"
#include "NvIdList.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#endif

/* Macro of log */
/*lint -e767 �޸���:������ 00105005;������:���� 51137;ԭ��:Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_NVIM_AFUNC_C
/*lint +e767 �޸���:������ 00105005;������:���� 51137; */

/*NV Memory ADDR*/
VOS_UINT_PTR                     g_ulNVMemAddr       = 0;

/* ���NV���ݵ��ڴ�� */
NV_CONTROL_FILE_INFO_STRU       *g_pstNVDataBuf = VOS_NULL_PTR;

/* NV's ID coms from 1 to 20 */
NV_FILE_HANDLE_STRU             g_astNvFileHandle[NV_BACKUP_FILE_MAX_NUM+1];

VOS_UINT32                      g_ulNVInitStartSlice = 0;

VOS_UINT32                      g_ulNVInitEndSlice   = 0;

VOS_SEM                         g_ulNVInitSem        = 0;

/* NV д�����Ƿ���Ҫ��¼slice��� */
extern  VOS_UINT32              g_ulRecordNvFlag;

/* ����NVд�����Ļ����ź��� */
VOS_SEM                         g_ulNVWriteSem;

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )

VOS_CHAR *g_aucNvFolderPath = ".\\NvimUse\\"; /* NV File path */
/*FlashLess�ļ��ӿڶ���*/
const VOS_CHAR g_aucNvFilePath[]   = "Nvim.bin";  /* NV Ctrl File */

#else


/* Absolute Path for Operating NV file */
const VOS_CHAR g_aucNvFolderPath[]   = "/mnvm2:0/NvimUse/"; /* NV File path */

/*FlashLess�ļ��ӿڶ���*/ /* V9R1 SFT���ļ�ϵͳ�������flashbess����ʱû�ж����·�� */
const VOS_CHAR g_aucNvFilePath[]     = "/yaffs0/Nvim/Nvim.bin";  /* NV Ctrl File */

#endif

#if (VOS_LINUX == VOS_OS_VER)

/* A C ��ͬ���ȴ��ź��� */
struct semaphore               g_stCoreNvSem;

/* NV д�����ź��� */
struct semaphore               g_stNvWriteSem;

/*****************************************************************************
 �� �� ��  : _VOS_SmMCreate
 ��������  : ���������ź�������
 �������  : acSmName: �ź�������
             ulSmInit: �ź�����ʼ��ֵ
             ulFlags: �ź�������
             pulSmID: �����ź���ID�ĵ�ַ

 �������  : pulSmID: �����ź���ID�ĵ�ַ

 �� �� ֵ  : VOS_OK:�ɹ���VOS_ERR:ʧ��

 �޸���ʷ      :
 1.��    ��    : 2013��5��2��
   ��    ��    : j00168360
   �޸�����    : C�˵�����λ��Ŀ����
*****************************************************************************/
VOS_UINT32 _VOS_SmMCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM *pulSmID)
{
    sema_init(&g_stNvWriteSem, 1);

    *pulSmID = (VOS_SEM)(&g_stNvWriteSem);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : _VOS_SmCCreate
 ��������  : �����ź�������
 �������  : acSmName: �ź�������
             ulSmInit: �ź�����ʼ��ֵ
             ulFlags: �ź�������
             pulSmID: �����ź���ID�ĵ�ַ

 �������  : pulSmID: �����ź���ID�ĵ�ַ

 �� �� ֵ  : VOS_OK:�ɹ���VOS_ERR:ʧ��

 �޸���ʷ      :
 1.��    ��    : 2012��13��26��
   ��    ��    : d00212987
   �޸�����    : A��ѭ���ȴ��޸�Ϊ��C���ź���ͬ����������
*****************************************************************************/
VOS_UINT32 _VOS_SmCCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_SEM   *pulSmID)
{
    sema_init(&g_stCoreNvSem, 0);

    *pulSmID = (VOS_SEM)(&g_stCoreNvSem);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : _VOS_SmP
 ��������  : �ȴ��ź���
 �������  : ulSemId: �ź���ID
             ulTimeOutInMillSec: ��ʱʱ��(ms)

 �������  : ��

 �� �� ֵ  : VOS_OK:�ɹ���VOS_ERR:ʧ��

 �޸���ʷ      :
 1.��    ��    : 2012��13��26��
   ��    ��    : d00212987
   �޸�����    : A��ѭ���ȴ��޸�Ϊ��C���ź���ͬ����������
*****************************************************************************/
VOS_UINT32 _VOS_SmP(VOS_SEM ulSemId, VOS_UINT32 ulTimeOutInMillSec)
{
    down((struct semaphore *)ulSemId);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : _VOS_SmV
 ��������  : �ͷ��ź���
 �������  : ulSemId: �ź���ID

 �������  : ��

 �� �� ֵ  : VOS_OK:�ɹ���VOS_ERR:ʧ��

 �޸���ʷ      :
 1.��    ��    : 2012��13��26��
   ��    ��    : d00212987
   �޸�����    : A��ѭ���ȴ��޸�Ϊ��C���ź���ͬ����������
*****************************************************************************/
VOS_UINT32 _VOS_SmV(VOS_SEM ulSemId)
{
    up((struct semaphore *)ulSemId);

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : NV_ACoreInitIpcIsr
 ��������  : C ��NV��ʼ������жϴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ�����

 �޸���ʷ      :
  1.��    ��   : 2013��03��26��
    ��    ��   : d00212987
    �޸�����   : A��ѭ���ȴ��޸�Ϊ��C���ź���ͬ����������

*****************************************************************************/
VOS_VOID NV_ACoreInitIpcIsr(VOS_VOID)
{
    mdrv_ipc_int_disable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);

    /*�յ�C�˳�ʼ������жϣ��ͷ��ź���*/
    /*lint -e534*/
    VOS_SmV(g_ulNVInitSem);
    /*lint +e534*/

    mdrv_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);
}

/*****************************************************************************
 �� �� ��  : NV_ACoreInitSync
 ��������  : NV A���ź���ͬ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2013��03��26��
    ��    ��   : d00212987
    �޸�����   : A��ѭ���ȴ��޸�Ϊ��C���ź���ͬ����������

*****************************************************************************/
VOS_VOID NV_ACoreInitSync(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    /* �����ź��� */
    VOS_SmCCreate("NVOK", 0, 0, &g_ulNVInitSem);
#endif
    /* ע���C���ж� */
    mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM, (VOIDFUNCPTR)NV_ACoreInitIpcIsr, 0);

    mdrv_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);
}

/*****************************************************************************
 �� �� ��  : NV_Init
 ��������  : Acpu Nv ��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ�����

 �޸���ʷ      :
  1.��    ��   : 2011��10��03��
    ��    ��   : zhuli 00168360
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NV_Init(VOS_VOID)
{
    VOS_UINT8           aucMagicNum[NV_MAGIC_NUM_LEN];
    VOS_UINT8           aucTemp[NV_MAGIC_NUM_LEN];
    BSP_DDR_SECT_INFO_S   stNVMemInfo;
    BSP_DDR_SECT_QUERY_S  stNVMemQuery;

    g_ulNVInitStartSlice = mdrv_timer_get_normal_timestamp();

    /*lint -e534*/
    VOS_MemSet(g_astNvFileHandle, 0, sizeof(g_astNvFileHandle));

    vos_printf("\r\n---------------------NV_Init Start-----------------------------\r\n");

    VOS_MemSet(aucMagicNum, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);
    /*lint +e534*/

    stNVMemQuery.enSectType = BSP_DDR_SECT_TYPE_NV;
    stNVMemQuery.ulSectSize = NV_BACKUP_BUFFER_SIZE;
    stNVMemQuery.enSectAttr = BSP_DDR_SECT_ATTR_NONCACHEABLE;

    if(MDRV_OK != mdrv_get_fix_ddr_addr(&stNVMemQuery, &stNVMemInfo))
    {
        /*lint -e534*/
        vos_printf("\r\nNV_Init: Acpu mdrv_get_fix_ddr_addr Failed\r\n");
        /*lint +e534*/

        mdrv_om_system_error(NV_INIT_ERROR, NV_GET_DRV_FIX_DDR_ADDR_FAIL,
                              0, (VOS_CHAR *)VOS_NULL_PTR, 0);

        return NV_INIT_FAIL;
    }

    g_ulNVMemAddr = (VOS_UINT_PTR)mdrv_phy_to_virt(MEM_DDR_MODE, stNVMemInfo.pSectPhysAddr);     /*�ϲ�ʹ�����ַ*/

    /* ����NVд���������ź��� */
    if(VOS_OK != VOS_SmMCreate("NV", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE,
                                &g_ulNVWriteSem))
    {
        return VOS_ERR;
    }

    if(MDRV_OK != mdrv_ipc_sem_create(IPC_SEM_NVIM))
    {
        NV_Printf("NV_Init: Acpu mdrv_ipc_sem_create Failed\r\n");

        return NV_INIT_FAIL;
    }

    /* �ȴ�C ��NV��ʼ����� */
    (VOS_VOID)VOS_SmP(g_ulNVInitSem, 0);

    NV_MEMCPY(aucTemp, (VOS_VOID*)NV_MAGICNUM_ADDR, NV_MAGIC_NUM_LEN);  /*��share memory��ȡ��־�ֽ�*/

    if(VOS_OK != VOS_MemCmp(aucMagicNum, aucTemp, NV_MAGIC_NUM_LEN))    /*Ccpu��Nv���Ѿ���ʼ���ɹ�*/
    {
        /* ���帴λ */
        mdrv_om_system_error(NV_INIT_ERROR, NV_GET_CCORE_MAGIC_NUM_FAIL,
                             0, (VOS_CHAR *)VOS_NULL_PTR, 0);
    }

    NV_BuildGlobalVar();

    /*lint -e534*/
    vos_printf("\r\n---------------------NV_Init End-----------------------------\r\n");
    /*lint +e534*/

    g_ulNVInitEndSlice = mdrv_timer_get_normal_timestamp();

    DRV_MSP_PROC_REG(OM_READ_NV_PROC, (BSP_MspProc)NV_ReadEx);

    /* ����Ƿ���NVд������¼���� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Write_Slice_Record_Flag, (VOS_VOID*)&g_ulRecordNvFlag, sizeof(g_ulRecordNvFlag)))
    {
        g_ulRecordNvFlag = 0;
    }

    return NV_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



