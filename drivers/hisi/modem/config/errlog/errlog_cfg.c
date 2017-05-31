/******************************************************************************

                  ��Ȩ���� (C), 2001-2016, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : errlog_cfg.c
  �� �� ��   : ����
  ��    ��   : d00212987
  ��������   : 2016��2��19��
  ����޸�   :
  ��������   : Errlog�����б�ģ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��2��19��
    ��    ��   : d00212987
    �޸�����   : Errlo�����б�����

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "errlog_cfg.h"


/*lint -e767 �޸���:d00212987;ԭ��:Log��ӡ */
//#define    THIS_FILE_ID        PS_FILE_ID_ERRLOG_CFG_C
/*lint +e767 �޸���:d00212987;*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* Warning�������Զ��������򣬲����ֹ��Ķ� begin */
/* TODO: g_aulModemErrRept hash_value:001e13bf53cc4cff835a0c12e5a166fc */
/* TODO: python search flag satrt */
int g_aulModem0ErrRept[][3]=
{
    /* GU ErrLog �ϱ���� Item:13 */
    {FAULT_ID_GU_ERR_LOG_REPT, I0_WUEPS_PID_MMC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I0_UEPS_PID_MTA, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I0_WUEPS_PID_USIM, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I0_UEPS_PID_GAS, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I0_UEPS_PID_SN, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, WUEPS_PID_WRR, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I0_DSP_PID_APM, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, PS_PID_ERRC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, TPS_PID_RRC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, PS_PID_MM, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, TPS_PID_MAC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, PS_PID_MAC_UL, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, TLPHY_PID_RTTAGENT, 0},



};

int g_aulModem1ErrRept[][3]=
{
    /* GU ErrLog �ϱ���� Item:6 */
    {FAULT_ID_GU_ERR_LOG_REPT, I1_WUEPS_PID_MMC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I1_UEPS_PID_MTA, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I1_WUEPS_PID_USIM, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I1_UEPS_PID_GAS, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I1_UEPS_PID_SN, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I1_DSP_PID_APM, 0},



};

int g_aulModem2ErrRept[][3]=
{
    /* GU ErrLog �ϱ���� Item:6 */
    {FAULT_ID_GU_ERR_LOG_REPT, I2_WUEPS_PID_MMC, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I2_UEPS_PID_MTA, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I2_WUEPS_PID_USIM, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I2_UEPS_PID_GAS, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I2_UEPS_PID_SN, 0},
    {FAULT_ID_GU_ERR_LOG_REPT, I2_DSP_PID_APM, 0},



};
/* TODO: python search flag end */
/* Warning�������Զ��������򣬲����ֹ��Ķ� end */

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : ErrLog_GetErrReptAddrAndSize
 ��������  : ��ȡErrlogȫ�ֱ�����ַ
 �������  : ulModemId ��modem/��modem��id

 �������  : pulErrLogAddr
             pulsize

 �� �� ֵ  : 0��success  ������fail
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��02��19��
    ��    ��   : d00212987
    �޸�����   :  ERR LOG FAULT ID������Ŀ����
*****************************************************************************/
VOS_INT32 ErrLog_GetErrReptAddrAndSize(
    VOS_UINT32                           ulModemId,
    VOS_UINT_PTR                        *pulErrLogAddr,
    VOS_UINT32                          *pulsize
)
{
    if (MODEM_ID_0 == ulModemId)
    {
        *pulErrLogAddr = (VOS_UINT_PTR)g_aulModem0ErrRept;
        *pulsize = sizeof(g_aulModem0ErrRept);
    }
    else if (MODEM_ID_1 == ulModemId)
    {
        *pulErrLogAddr = (VOS_UINT_PTR)g_aulModem1ErrRept;
        *pulsize = sizeof(g_aulModem1ErrRept);

    }
    else if (MODEM_ID_2 == ulModemId)
    {
        *pulErrLogAddr = (VOS_UINT_PTR)g_aulModem2ErrRept;
        *pulsize = sizeof(g_aulModem2ErrRept);
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;


}

/*****************************************************************************
 �� �� ��  : ErrLog_GetPidAndAlarmId
 ��������  : ulFaultId������pid/alarm_id��ѯ�ӿ�
 �������  : ulModemId ��modem/��modem��id
             ulFaultId fault id

 �������  : paustAlarmArray fault id�������pid alarm_id���飬�ڴ�ռ���diag_om�ṩ����󳤶�2048��֧��һ��faultid����256��alarm_id��
             pulAlarmNum     fault id�������pid alarm_id�����Ա���������256��

 �� �� ֵ  : 0��success  ������fail
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��02��19��
    ��    ��   : d00212987
    �޸�����   : ERR LOG FAULT ID������Ŀ����
*****************************************************************************/
VOS_INT32 ErrLog_GetPidAndAlarmId(
    VOS_UINT32                          ulModemId,
    VOS_UINT32                          ulFaultId,
    ERR_LOG_ALARM_STRU                 *paustAlarmArray,
    VOS_UINT32                         *pulAlarmNum
)
{
    VOS_UINT_PTR                        ulErrLogAddr = VOS_NULL;
    VOS_UINT32                          ulsize;
    VOS_UINT32                          ulCount = 0;
    VOS_UINT32                          i;
    VOS_UINT32                          (*pulErrLogArry)[3];

    if (VOS_NULL_PTR == paustAlarmArray)
    {
        return VOS_ERR;
    }

    if (VOS_OK != ErrLog_GetErrReptAddrAndSize(ulModemId, &ulErrLogAddr, &ulsize))
    {
        return VOS_ERR;
    }

    pulErrLogArry = (VOS_UINT32(*)[])ulErrLogAddr;

    for (i=0; i < (ulsize / (3 * sizeof(VOS_UINT32))); i++)
    {
        if (ulFaultId == pulErrLogArry[i][0])
        {
            if (FAULT_ID_CONTAIN_ALARM_ID_MAX_NUM <= ulCount)
            {
                return VOS_ERR;
            }

            paustAlarmArray[ulCount].ulPid      = pulErrLogArry[i][1];
            paustAlarmArray[ulCount].ulAlarmID  = pulErrLogArry[i][2];
            ulCount++;
        }
    }

    *pulAlarmNum = ulCount;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ErrLog_IsContainPID
 ��������  : ���PID�Ƿ��Ѿ�����
 �������  : PID�����Ѽ���С

 �������  : �Ƿ����

 �� �� ֵ  : VOS_TRUE������  ������VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��02��19��
    ��    ��   : d00212987
    �޸�����   : ERR LOG FAULT ID������Ŀ����
*****************************************************************************/
VOS_BOOL ErrLog_IsContainPID(
    VOS_UINT32                         *PaulPidArray,
    VOS_UINT32                          ulPidArrayLen,
    VOS_UINT32                          ulDstPid
)
{
    VOS_UINT32                          i;

    for (i=0; i < ulPidArrayLen; i++)
    {
        if (ulDstPid == PaulPidArray[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : ErrLog_GetErrlogPid
 ��������  : �ṩerrlog��ص�pid�б�����errlog���ؿ��Ƹ���pid������Ϣ
 �������  : ulModemId ��modem/��modem��id

 �������  : PaulPidArray   errlog�������pid���飬�ڴ�ռ���diag_om�ṩ����󳤶�1024��֧��256��pid��
             pulPidNum      errlog�������pid�����Ա���������256��

 �� �� ֵ  : 0��success  ������fail
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��02��19��
    ��    ��   : d00212987
    �޸�����   :  ERR LOG FAULT ID������Ŀ����
*****************************************************************************/
VOS_INT32 ErrLog_GetErrlogPid(
    VOS_UINT32                          ulModemId,
    VOS_UINT32                         *PaulPidArray,
    VOS_UINT32                         *pulPidNum
)
{
    VOS_UINT_PTR                        ulErrLogAddr = VOS_NULL;
    VOS_UINT32                          ulsize;
    VOS_UINT32                          ulCount = 0;
    VOS_UINT32                          i;
    VOS_UINT32                          (*pulErrLogArry)[3];

    if (VOS_NULL_PTR == PaulPidArray)
    {
        return VOS_ERR;
    }

    if (VOS_OK != ErrLog_GetErrReptAddrAndSize(ulModemId, &ulErrLogAddr, &ulsize))
    {
        return VOS_ERR;
    }

    pulErrLogArry = (VOS_UINT32(*)[])ulErrLogAddr;

    for (i=0; i < (ulsize / (3 * sizeof(VOS_UINT32))); i++)
    {
        if (0 == i)
        {
            PaulPidArray[0] = pulErrLogArry[i][1];
            ulCount++;
            continue;
        }

        if (VOS_TRUE != ErrLog_IsContainPID(PaulPidArray, ulCount, pulErrLogArry[i][1]))
        {
            if (ERR_LOG_PID_MAX_NUM <= ulCount)
            {
                return VOS_ERR;
            }

            PaulPidArray[ulCount] = pulErrLogArry[i][1];
            ulCount++;
        }
    }

    *pulPidNum = ulCount;

    return VOS_OK;
}



