

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: vos_main.c                                                      */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement root function                                      */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/* 3. Date: 2007-03-10                                                       */
/*    Author: Xu Cheng                                                       */
/*    Modification: A32D07254                                                */
/*                                                                           */
/*****************************************************************************/

#include "v_typdef.h"
#include "v_root.h"
#include "vos_config.h"
#include "v_IO.h"
#include "v_blkMem.h"
#include "v_queue.h"
#include "v_sem.h"
#include "v_timer.h"
#include "vos_Id.h"
#include "v_int.h"
#include "NVIM_Interface.h"
#include "mdrv.h"

/* LINUX ��֧�� */



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_VOS_MAIN_C
/*lint +e767 modify:x51137; review:h59254; */

typedef struct
{
    VOS_UINT32 ulStartUpStage;
    VOS_UINT32 ulStep;
    VOS_UINT32 ulOutSideStep;
    VOS_UINT16 usFidInitStep;
    VOS_UINT16 usFidInitId;
    VOS_UINT16 usPidInitStep;
    VOS_UINT16 usPidInitId;
}VOS_START_ERR_STEP_STRU;

extern VOS_UINT32       g_ulOmFidInit ;
extern VOS_UINT32       g_ulOmPidInit ;
extern VOS_UINT32       g_ulVosOutsideStep;
extern VOS_UINT16       g_usFidInitStep;
extern VOS_UINT16       g_usFidInitId;
extern VOS_UINT16       g_usPidInitStep;
extern VOS_UINT16       g_usPidInitId;

extern VOS_UINT32 VOS_OutsideInit(VOS_VOID);

extern VOS_VOID OM_RecordMemInit(VOS_VOID);

VOS_UINT32 vos_StartUpStage = 0x00010000;
VOS_UINT32 g_ulVosStartStep = 0;

HTIMER  g_VosProtectInitTimer = VOS_NULL_PTR;

VOS_UINT32 *g_pulOsaLogTmp;

VOS_VOID V_LogInit(VOS_VOID)
{
    return;
}

VOS_VOID V_LogRecord(VOS_UINT32 ulIndex, VOS_UINT32 ulValue)
{
    return;
}

/*****************************************************************************
 Function   : root
 Description: main function
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID root( VOS_VOID)
{
    /*lint -e534*/
    Print("\n!!!!! VOS_Startup Begin !!!!!\n");
    /*lint +e534*/


    /* 2016.03.14:����ӿ��޸ģ��ȵ���register���������ڴ棬����ʹ��get field������ȡ�ڴ��ַ */
    (VOS_VOID)mdrv_om_register_field(DUMP_SAVE_MOD_OSA_MEM, "OAM", VOS_NULL_PTR, VOS_NULL_PTR, VOS_DUMP_MEM_ALL_SIZE, 0);

    V_LogInit();

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_INIT_DOPRA_SOFEWARE_RESOURCE ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 0: Error.\n");
        /*lint +e534*/
    }

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_SET_TIME_INTERRUPT ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 1: Error.\n");
        /*lint +e534*/
    }

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_CREATE_TICK_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase2: Error.\n");
        /*lint +e534*/
    }

    if( VOS_OK != VOS_Startup( VOS_STARTUP_CREATE_ROOT_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 3: Error\n");
        /*lint +e534*/
    }

    if ( VOS_OK != VOS_Startup( VOS_STARTUP_SUSPEND_MAIN_TASK ) )
    {
        /*lint -e534*/
        Print("VOS_Startup Phase 4: Error\n");
        /*lint +e534*/
    }

    /*lint -e534*/
    Print("\n!!!!! VOS_Startup End !!!!!\n");
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : VOS_ProtectInit
 Description: reboot if OSA can't init
 Calls      :
 Called By  : root
 Input      : None
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ProtectInit(VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    VOS_START_ERR_STEP_STRU stStep;

    stStep.ulStartUpStage = vos_StartUpStage;
    stStep.ulStep         = g_ulVosStartStep;
    stStep.ulOutSideStep  = g_ulVosOutsideStep;
    stStep.usFidInitStep  = g_usFidInitStep;
    stStep.usFidInitId    = g_usFidInitId;
    stStep.usPidInitStep  = g_usPidInitStep;
    stStep.usPidInitId    = g_usPidInitId;


    VOS_ProtectionReboot(OSA_EXPIRE_ERROR, 0, 0, (VOS_CHAR *)&stStep, sizeof(VOS_START_ERR_STEP_STRU) );
}

/*****************************************************************************
 Function   : VOS_Startup
 Description: startup function
 Calls      :
 Called By  : root
 Input      : None
 Return     : VOS_OK or VOS_ERROR
 Other      :

��    ��   : 2010��12��22��
��    ��   : j00174725
�޸�����   : �������ⵥ��:DTS2010122401828
            ��������USB���ֻ�ɫ��̾�ţ����������������
            ����VOS��FID����֮ǰ��������ɺ������
            ��Resume����ǰ��������Resume�������

 *****************************************************************************/
VOS_UINT32 VOS_Startup( enum VOS_STARTUP_PHASE ph )
{
    VOS_UINT32      ulReturnValue;
    VOS_UINT32      ulStartUpFailStage = 0;

    switch(ph)
    {
        case VOS_STARTUP_INIT_DOPRA_SOFEWARE_RESOURCE :
            vos_StartUpStage    = 0x00010000;
            V_LogRecord(0, 0x00010000);

            if ( VOS_OK != VOS_MemInit() )
            {
                ulStartUpFailStage |= 0x0001;

                break;
            }

            VOS_SemCtrlBlkInit();

            VOS_QueueCtrlBlkInit();

            VOS_TaskCtrlBlkInit();

            if ( VOS_OK != VOS_TimerCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0010;
            }

            OM_RecordMemInit();

            if ( VOS_OK != RTC_TimerCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0100;
            }


            if ( VOS_OK != VOS_PidCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0400;
            }

            if ( VOS_OK != VOS_FidCtrlBlkInit() )
            {
                ulStartUpFailStage |= 0x0800;
            }

            if ( VOS_OK != CreateFidsQueque() )
            {
                ulStartUpFailStage |= 0x1000;
            }
            break;

        case VOS_STARTUP_SET_TIME_INTERRUPT:
            vos_StartUpStage = 0x00020000;
            V_LogRecord(0, 0x00020000);
            break;

        case VOS_STARTUP_CREATE_TICK_TASK:
            vos_StartUpStage = 0x00040000;
            V_LogRecord(0, 0x00040000);

            /* create soft timer task */
            if ( VOS_OK != VOS_TimerTaskCreat() )
            {
                ulStartUpFailStage |= 0x0001;
            }

            if ( VOS_OK != RTC_TimerTaskCreat() )
            {
                ulStartUpFailStage |= 0x0002;
            }


            break;

        case VOS_STARTUP_CREATE_ROOT_TASK:
            vos_StartUpStage = 0x00080000;
            V_LogRecord(0, 0x00080000);
            /*
            if ( VOS_OK !=
                    VOS_StartCallBackRelTimer(&g_VosProtectInitTimer,
                        DOPRA_PID_TIMER, 20000, 0, 0,
                        VOS_RELTIMER_NOLOOP, VOS_ProtectInit, VOS_TIMER_PRECISION_5) )
            {
                ulStartUpFailStage |= 0x0001;
            }
            */

            g_ulVosStartStep = 0x0000;
            V_LogRecord(1, 0x0000);

            ulReturnValue = VOS_OutsideInit();

            if(VOS_OK != ulReturnValue)
            {
                ulStartUpFailStage |= ulReturnValue;
            }

            g_ulVosStartStep = 0x0008;
            V_LogRecord(1, 0x0008);

            if ( VOS_OK != VOS_FidsInit() )
            {
                ulStartUpFailStage |= 0x0008;
            }


            g_ulVosStartStep = 0x0020;
            V_LogRecord(1, 0x0020);

            /* create FID task & selftask task */
            if ( VOS_OK != CreateFidsTask() )
            {
                ulStartUpFailStage |= 0x0020;
            }

            g_ulVosStartStep = 0x0100;
            V_LogRecord(1, 0x0100);

            if ( VOS_OK != VOS_PidsInit() )
            {
                ulStartUpFailStage |= 0x0100;
            }
            break;

        case VOS_STARTUP_SUSPEND_MAIN_TASK:
            vos_StartUpStage = 0x00100000;
            V_LogRecord(0, 0x00100000);

            g_ulVosStartStep = 0x0008;
            V_LogRecord(1, 0x0008);

            /* stop protect timer */
            /*VOS_StopRelTimer(&g_VosProtectInitTimer);*/


            VOS_RunTask();


            break;

        default:
            break;
    }

    /* calculate return value */
    if( 0 != ulStartUpFailStage )
    {
        ulReturnValue = vos_StartUpStage;
        ulReturnValue |= ulStartUpFailStage;
        /*lint -e534*/
        Print1("startup retuen value is %x.\r\n",ulReturnValue);
        /*lint +e534*/

        /* reboot */
        VOS_ProtectionReboot(OSA_INIT_ERROR, (VOS_INT)ulReturnValue,
            (VOS_INT)g_ulOmPidInit, (VOS_CHAR *)&g_ulOmFidInit, sizeof(VOS_UINT32));

        return(ulReturnValue);
    }
    else
    {
        return(VOS_OK);
    }
}


/*****************************************************************************
 Function   : VOS_ModuleInit
 Description:
 Input      :
 Output     :
 Return     :
 *****************************************************************************/
extern VOS_INT RNIC_InitNetCard(VOS_VOID);
extern VOS_INT APP_VCOM_Init(VOS_VOID);


VOS_INT VOS_ModuleInit(VOS_VOID)
{

    root();

    return 0;
}


/*when flash less on, VOS_ModuleInit should be called by bsp drv.*/





