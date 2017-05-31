


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "IpNdServer.h"
#include "AdsDeviceInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IPNDSERVER_C
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* ND SERVER������Ϣ */
IP_NDSERVER_ADDR_INFO_STRU              g_astNdServerAddrInfo[IP_NDSERVER_ADDRINFO_MAX_NUM];
IP_NDSERVER_TE_DETECT_BUF_STRU          g_astNdServerTeDetectBuf;

/* ND SERVER���ر�������ò��� */
VOS_UINT8                               g_ucMFlag;            /* M��ʶ */
VOS_UINT8                               g_ucOFlag;            /* O��ʶ */
VOS_UINT16                              g_usRouterLifetime;   /* Router Lifetime */
VOS_UINT32                              g_ulReachableTime;    /* Reachable Time */
VOS_UINT32                              g_ulRetransTimer;     /* Retrans Timer */

VOS_UINT32                              g_ulNsTimerLen;         /* ��������NS��ʱ��ʱ�� */
VOS_UINT32                              g_ulNsTimerMaxExpNum;   /* ��������NS���ʱ���� */
VOS_UINT32                              g_ulPeriodicNsTimerLen; /* ������NS��ʱ��ʱ�� */
VOS_UINT32                              g_ulPeriodicRaTimerLen; /* ������RA��ʱ��ʱ������ֹRouter���� */
VOS_UINT32                              g_ulFirstNsTimerLen;    /* �յ��ظ���ַ����ȴ��Ķ�ʱ��ʱ�� */
VOS_UINT32                              g_ulRaTimerLen;         /* �յ��ظ���ַ���ǰ���ڷ���RA��ʱ��ʱ�� */

/* �����Է���RAʱ������� */
VOS_UINT32                              g_aulPeriodicRaTimeCnt[IP_NDSERVER_ADDRINFO_MAX_NUM];

/* ���ڴ洢�������ND�������� */
IP_ND_MSG_STRU                          g_stNdMsgData;

/* ND SERVERʹ�õķ��������� */
VOS_UINT8                               g_aucSendMsgBuffer[IP_IPM_MTU];

/* ND SERVER����ͳ����Ϣ */
IP_NDSERVER_PACKET_STATISTICS_INFO_STRU g_astNdServerPktStatInfo[IP_NDSERVER_ADDRINFO_MAX_NUM];

VOS_UINT8 g_aucInvalidIpv6Addr[IP_IPV6_ADDR_LEN] = {0};

extern VOS_UINT32 g_ulNvMtu;

/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_UINT8* Ndis_GetMacAddr( VOS_VOID );
extern VOS_UINT32 Ndis_SendMacFrm(const VOS_UINT8  *pucBuf, VOS_UINT32 ulLen, VOS_UINT8 ucRabId);
extern VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);

/*****************************************************************************
 �� �� ��  : IP_NDSERVER_SaveTeDetectIp
 ��������  : ��ʱ����Te IP��ַ����TE�����ظ���ַ���������������ȡTE MAC��
             ַ
 �������  : VOS_UINT8* pucTeGlobalAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��17��
    ��    ��   : w00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IP_NDSERVER_SaveTeDetectIp( const VOS_UINT8* pucTeGlobalAddr )
{
    VOS_UINT32  ulIndex = g_astNdServerTeDetectBuf.ulHead;

    if ((IP_IPV6_IS_LINKLOCAL_ADDR(pucTeGlobalAddr))
            || (IP_IPV6_64BITPREFIX_EQUAL_ZERO(pucTeGlobalAddr))
            || (IP_IPV6_IS_MULTICAST_ADDR(pucTeGlobalAddr)))
    {
        /* ����Global IP */
        return;
    }

    /* ��ͬPrefix�ĵ�ַ�Ƿ��Ѿ����� */
    while(ulIndex != g_astNdServerTeDetectBuf.ulTail)
    {
        /*lint -e960*/
        if((IP_TRUE == g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid)
            && (0 == IP_MEM_CMP(pucTeGlobalAddr, g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, ND_IP_IPV6_PREFIX_LENGTH)))
        /*lint +e960*/
            {
            /* ��ͬPrefixֻ����һ����ַ */
            IP_MEM_CPY(g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, pucTeGlobalAddr, IP_IPV6_ADDR_LEN);
            return;
        }
        ulIndex = TTF_MOD_ADD(ulIndex, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    if(g_astNdServerTeDetectBuf.ulHead == TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulTail, 1, g_astNdServerTeDetectBuf.ulMaxNum))
    {
        /*IP_LOG1_WARN("IP_NDSERVER_SaveTeDetectIp: OverWrite TeAddr!", g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].ulValid);
 */
        /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
        /* BUF��ʱ�������ϵĵ�ַ */
        g_astNdServerTeDetectBuf.ulHead = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulHead, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    /* ����IP��ַ */
    IP_MEM_CPY(g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulTail].aucTeGlobalAddr, pucTeGlobalAddr, IP_IPV6_ADDR_LEN);
    g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulTail].ulValid = IP_TRUE;

    g_astNdServerTeDetectBuf.ulTail = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulTail, 1, g_astNdServerTeDetectBuf.ulMaxNum);
}

/*****************************************************************************
 �� �� ��  : IP_NDSERVER_GetTeDetectIp
 ��������  : ��ȡ��ʱ�����TE IP��ַ
 �������  : VOS_UINT8* pucPrefixAddr
 �������  : ��
 �� �� ֵ  : VOS_UINT8*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��17��
    ��    ��   : w00145177
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* IP_NDSERVER_GetTeDetectIp( const VOS_UINT8* pucPrefixAddr )
{
    VOS_UINT32  ulIndex = g_astNdServerTeDetectBuf.ulHead;
    while(ulIndex != g_astNdServerTeDetectBuf.ulTail)
    {
        /*lint -e960*/
        if((IP_TRUE == g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid)
            && (0 == IP_MEM_CMP(pucPrefixAddr, g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, ND_IP_IPV6_PREFIX_LENGTH)))
        /*lint +e960*/
        {
            g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid = IP_FALSE;

            /* Bufͷ����϶���� */
            while((g_astNdServerTeDetectBuf.ulHead != g_astNdServerTeDetectBuf.ulTail) &&
                (IP_FALSE == g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].ulValid))
            {
                g_astNdServerTeDetectBuf.ulHead = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulHead, 1, g_astNdServerTeDetectBuf.ulMaxNum);
            }

            return g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr;
        }
        ulIndex = TTF_MOD_ADD(ulIndex, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    return IP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SetLocalParam
 Description     : ���ñ����������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_SetLocalParam( VOS_VOID )
{
    /* M��ʶ��0����������ͨ��DHCPv6��ȡIPv6��ַ */
    g_ucMFlag = 0;

    /* O��ʶ��1����������ͨ����״̬DHCPv6��ȡ��������������DNS��������SIP�������� */
    g_ucOFlag = 1;

    /* Router Lifetime(��) */
    g_usRouterLifetime = 9000;

    /* Reachable Time(����) */
    g_ulReachableTime = 3600000;

    /* Retrans Timer(����)��0����ʾδ֪ */
    g_ulRetransTimer = 0;

    /* ��������NS��ʱ��ʱ��(����) */
    g_ulNsTimerLen = 4000;

    /* ��������NS���ʱ���� */
    g_ulNsTimerMaxExpNum = 3;

    /* ������NS��ʱ��ʱ��(����) */
    g_ulPeriodicNsTimerLen = 60000;

    /* ������RA����ֹRouter����(����) */
    g_ulPeriodicRaTimerLen = 3600000;

    /* �յ��ظ���ַ����ȴ��Ķ�ʱ��ʱ��(����) */
    g_ulFirstNsTimerLen = 2000;

    /* �յ��ظ���ַ���ǰ���ڷ���RA�Ķ�ʱ��ʱ��(����) */
    g_ulRaTimerLen = 15000;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DebugInit
 Description     : ���ͳ����Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_DebugInit(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM; ulIndex++)
    {
        IP_MEM_SET( IP_NDSERVER_GET_STATINFO_ADDR(ulIndex),
                    IP_NULL,
                    sizeof(IP_NDSERVER_PACKET_STATISTICS_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_IsTimerNameValid
 Description     : �ж϶�ʱ�����Ƿ�Ϸ�
 Input           : ulIndex     --- ND SERVER������������
                   enTimerType --- ��ʱ������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_IsTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
        case IP_ND_SERVER_TIMER_FIRST_NS:
        case IP_ND_SERVER_TIMER_RA:
        {
            if (ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
            {
                return IP_TRUE;
            }

            break;
        }
        default:
            break;
    }

    return IP_FALSE;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetTimer
 Description     : ��ȡ��ʱ��
 Input           : enTimerType------------------��ʱ������
                   ulIndex----------------------��ʱ��������
 Output          : None
 Return          : IP_TIMER_STRU*

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
IP_TIMER_STRU*  IP_NDSERVER_GetTimer
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*���ݶ�ʱ����ͬ���ͣ���ȡ��ʱ��*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
        case IP_ND_SERVER_TIMER_FIRST_NS:
        case IP_ND_SERVER_TIMER_RA:
            pstTimerInfo = IP_NDSERVER_ADDRINFO_GET_TIMER(ulIndex);
            break;
        default :
            break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetTimerLen
 Description     : ��ȡ��ʱ��ʱ��
 Input           : enTimerType------------------��ʱ������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_GetTimerLen
(
    NDSER_TIMER_ENUM_UINT32              enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = IP_NULL;

    /*���ݶ�ʱ����ͬ���ͣ���ʱ��ʱ����ͬ*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
            ulTimerLen = g_ulNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            ulTimerLen = g_ulPeriodicNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            ulTimerLen = g_ulFirstNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_RA:
            ulTimerLen = g_ulRaTimerLen;
            break;
        default :
            break;
    }

    return ulTimerLen;
}
/*lint -e550*/
/*****************************************************************************
 Function Name   : IP_NDSERVER_PrintTimeStartInfo
 Description     : ��ӡ��ʱ��������Ϣ
 Input           : enTimerType------------------��ʱ������
                   ulIndex----------------------��ʱ��������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2010-04-02  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_PrintTimeStartInfo
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32      ulEpsbId;

    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);
    /*���ݶ�ʱ����ͬ���ͣ���ӡ��Ӧ��Ϣ*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_PERIODIC_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_FIRST_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_RA", ulIndex, ulEpsbId);
            break;
        default :
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_PrintTimeStopInfo
 Description     : ��ӡ��ʱ���ر���Ϣ
 Input           : enTimerType------------------��ʱ������
                   ulIndex----------------------��ʱ��������
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2010-04-02  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_PrintTimeStopInfo
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32     ulEpsbId;

    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);
    /*���ݶ�ʱ����ͬ���ͣ���ӡ��Ӧ��Ϣ*/
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_PERIODIC_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_FIRST_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_RA", ulIndex, ulEpsbId);
            break;
        default :
            break;
    }

    return;
}
/*lint +e550*/
/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerStart
 Discription    : ����ĳһ���ص�ĳ�����͵Ķ�ʱ��
 Input          : VOS_UINT32             ulIndex
                  NDSER_TIMER_ENUM_UINT32 enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunli 00180715      2011-04-02  Draft Enact
*****************************************************************************/
VOS_VOID IP_NDSERVER_TimerStart
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32                          ulTimerLen   = IP_NULL;
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*��ulIndex�Ϸ����ж�*/
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart: WARN: Input Para(ulIndex) err !", ulIndex, enTimerType);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:ERROR: Get Timer failed.");
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimerInfo->hTm)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTm)))
        {
            /*��ӡ�쳣��Ϣ*/
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:WARN: stop reltimer error!");
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:(TimerType) Timer not close!",pstTimerInfo->ulName, ulIndex);
    }

    /*���ݶ�ʱ����ͬ���ͣ���ʱ����Ϣ��ͬ*/
    ulTimerLen = IP_NDSERVER_GetTimerLen(enTimerType);
    if (ulTimerLen == IP_NULL)
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:ERROR: start unreasonable reltimer.");
        return;
    }

    /*�趨��ʱ��NAME,enTimerType�趨��ʱ��Para����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTm),NDIS_NDSERVER_PID,\
                                ulTimerLen,(VOS_UINT32)enTimerType,\
                                ulIndex,VOS_RELTIMER_NOLOOP))
    {
          /*��ӡ�쳣��Ϣ*/
          IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:WARN: start reltimer error!");
          return;
    }

    /* ���¶�ʱ����� */
    pstTimerInfo->ulName = enTimerType;

    /* ��ӡ��ʱ��������Ϣ */
    IP_NDSERVER_PrintTimeStartInfo(ulIndex, enTimerType);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerStop
 Discription    : ֹͣĳһ����ĳ�����Ͷ�ʱ��
 Input          : VOS_UINT32             ulIndex
                  NDSER_TIMER_ENUM_UINT32 enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunli 00180715      2011-04-02  Draft Enact
*****************************************************************************/
VOS_VOID IP_NDSERVER_TimerStop
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*��ulIndex�Ϸ����ж�*/
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop: WARN: Input Para(ulIndex) err !", ulIndex, enTimerType);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop:ERROR:Get Timer failed.");
        return;
    }

    /*��ʱ�����ڴ�״̬����رգ����򣬺���*/
    if(VOS_NULL_PTR != pstTimerInfo->hTm)
    {
        if(enTimerType != pstTimerInfo->ulName)
        {
            /*��ӡ�쳣��Ϣ*/
            IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop: TimerType not match:", enTimerType, pstTimerInfo->ulName);
        }
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTm)))
        {
            /*��ӡ�쳣��Ϣ*/
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop:WARN: stop reltimer error!");
            return;
        }

        /* �����ʱ���� */
        pstTimerInfo->ucLoopTimes = 0;

        /* ��ӡ��ʱ���ر���Ϣ */
        IP_NDSERVER_PrintTimeStopInfo(ulIndex, enTimerType);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_Init
 Description     : ND SERVERģ��ĳ�ʼ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_Init( VOS_VOID )
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usPayLoad = IP_IPV6_PAYLOAD;
    VOS_UINT32                          ulRtn;

    IP_NDSERVER_SetLocalParam();
    IP_NDSERVER_DebugInit();

    for (ulIndex = 0; ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM; ulIndex++)
    {
        IP_MEM_SET( IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex),
                    IP_NULL,
                    sizeof(IP_NDSERVER_ADDR_INFO_STRU));

        PS_MEM_CPY( IP_NDSERVER_ADDRINFO_GET_MACADDR(ulIndex),
                   (VOS_VOID*)Ndis_GetMacAddr(),
                   IP_MAC_ADDR_LEN);

        PS_MEM_CPY((IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex) + IP_MAC_ADDR_LEN),
                   (VOS_VOID*)Ndis_GetMacAddr(),
                   IP_MAC_ADDR_LEN);

        PS_MEM_CPY((IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex) + 2*IP_MAC_ADDR_LEN),
                   (VOS_UINT8*)(&usPayLoad),
                   2);

        g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;

        /*��������IP���������*/
        ulRtn = LUP_CreateQue(NDIS_NDSERVER_PID, &(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex)), ND_IPV6_WAIT_ADDR_RSLT_Q_LEN);
        if (PS_SUCC != ulRtn)
        {
            vos_printf("IP_NDSERVER_Init, LUP_CreateQue DlPktQue fail.\n");
            return;
        }
    }

    IP_MEM_SET(&g_astNdServerTeDetectBuf,
                IP_NULL,
                sizeof(IP_NDSERVER_TE_DETECT_BUF_STRU));

    g_astNdServerTeDetectBuf.ulHead = 0;
    g_astNdServerTeDetectBuf.ulTail = 0;
    g_astNdServerTeDetectBuf.ulMaxNum = 2*IP_NDSERVER_ADDRINFO_MAX_NUM;

    return;
}

/*****************************************************************************
 �� �� ��  : APP_NdServer_Pid_InitFunc
 ��������  : ND SERVER PID��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ePhase
 �������  : ��
 �� �� ֵ  : extern VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : h00159435
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  APP_NdServer_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ePhase)
{
    switch( ePhase )
    {
        case   VOS_IP_LOAD_CONFIG:
            IP_NDSERVER_Init();
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
        default:
            break;
    }
    return 0;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_Stop
 Description     : ���ND SERVER�����Ϣ
 Input           : ulIndex --- ND SERVER�ṹ������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_Stop(VOS_UINT32 ulIndex)
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pstInfoAddr->ucValidFlag = IP_FALSE;

    pstInfoAddr->ucEpsbId = 0;

    IP_MEM_SET(&pstInfoAddr->stIpv6NwPara, IP_NULL, sizeof(ESM_IP_IPV6_NW_PARA_STRU));

    if (IP_NDSERVER_TE_ADDR_INEXISTENT != pstInfoAddr->stTeAddrInfo.enTeAddrState)
    {
        IP_NDSERVER_SaveTeDetectIp(pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr);
    }

    /* ���TE��ַ��¼ */
    IP_MEM_SET( &pstInfoAddr->stTeAddrInfo,
                IP_NULL,
                sizeof(IP_NDSERVER_TE_ADDR_INFO_STRU));

    IP_NDSERVER_TimerStop(ulIndex, pstInfoAddr->stTimerInfo.ulName);

    IP_MEM_SET(&pstInfoAddr->stIpSndNwMsg, IP_NULL, sizeof(IP_SND_MSG_STRU));

    g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ClearDlPktQue
 Description     : �ͷ����л�������е�PKT
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ClearDlPktQue(VOS_UINT32 ulIndex)
{
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_INT32                           lLockKey;

    while(PS_TRUE != (LUP_IsQueEmpty(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex))))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
        {
            VOS_Splx(lLockKey);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ClearDlPktQue, LUP_DeQue return fail!");
            return;
        }
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
    }

    return;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnRel
 Description     : ����NDIS������Ipv6PdnRel
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435 00159435      2011-12-09  Draft Enact
    2.h00218138 00218138      2013-1-16  DSDA

*****************************************************************************/
VOS_VOID NdSer_Ipv6PdnRel(VOS_UINT8 ucExRabId)
{
    VOS_UINT32                          ulIndex;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnRel is entered.");

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);

    if (ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IP_NDSERVER_Stop(ulIndex);

        IP_NDSERVER_ClearDlPktQue(ulIndex);           /*�ͷ�����PKT�������*/
    }
    else
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnRel: Invalid Input:", ulIndex, ucExRabId);
    }

    return;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnValid
 Description     : ��NDIS���ã���ѯ��Ӧ���ص�ND SERVERʵ���Ƿ���Ч
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_UINT32 NdSer_Ipv6PdnValid(VOS_UINT8 ucRabId)
{
    VOS_UINT32                          ulIndex;

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 Function Name   : NdSer_GetMacFrm
 Description     : ��NDIS���ã���ȡND SERVER��Ӧʵ�������MAC֡ͷ
 Input           : VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_UINT8*

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_UINT8* NdSer_GetMacFrm(VOS_UINT8 ucIndex, VOS_UINT8 *enTeAddrState)
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ucIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "pstInfoAddr ucValidFlag is not TRUE!", ucIndex);
        return VOS_NULL_PTR;
    }

    *enTeAddrState = pstInfoAddr->stTeAddrInfo.enTeAddrState;

    return IP_NDSERVER_ADDRINFO_GET_MACFRAME(ucIndex);
}

/*****************************************************************************
 Function Name   : NdSer_MacAddrInvalidProc
 Description     : ��NDIS���ã���δ���PC MAC��ַʱ����������IP��
 Input           : VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_UINT8*

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_VOID NdSer_MacAddrInvalidProc(IMM_ZC_STRU *pstImmZc, VOS_UINT8 ucIndex)
{
    IMM_ZC_STRU                        *pstQueHead;
    VOS_INT32                           lLockKey;

    IP_NDSERVER_AddMacInvalidPktNum(ucIndex);

    /***********************����IPV6���ݰ�����*********************************/
    if (PS_TRUE == LUP_IsQueFull(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex)))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex), (VOS_VOID**)(&pstQueHead)))
        {
            VOS_Splx(lLockKey);
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_MacAddrInvalidProc, LUP_DeQue return NULL");
            return;
        }
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstQueHead);                         /*�ͷ������IP��*/
        /*lint +e522*/
    }

    lLockKey = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex), pstImmZc))    /*�������µ�IP��*/
    {
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_MacAddrInvalidProc, LUP_EnQue return NULL");
        return;
    }
    VOS_Splx(lLockKey);

    IP_NDSERVER_AddEnquePktNum(ucIndex);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_FindIpv6EffectivePrefix
 Description    : ���ҵ�һ�����õ�IPv6ǰ׺
 Input          : pstConfigParaInd ---- ESM_IP_NW_PARA_IND_STRU��Ϣָ��
 Output         : pulPrefixIndex   ---- ǰ׺����ָ��
 Return Value   : VOS_UINT32

 History        :
      1.sunli 00180715     2011-04-05  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_FindIpv6EffectivePrefix
(
    AT_NDIS_IPV6_PDN_INFO_STRU            *pstConfigParaInd,
    VOS_UINT32                            *pulPrefixIndex
)
{
    VOS_UINT32                          ulIndex         = IP_NULL;
    ND_IP_IPV6_PREFIX_STRU            *pstIpv6Prefix   = IP_NULL_PTR;

    /* ����ǰ׺�б�����A��ʶΪ1��ǰ׺����Ϊ64��ǰ׺ */
    for (ulIndex = IP_NULL; ulIndex < pstConfigParaInd->ulPrefixNum; ulIndex++)
    {
        pstIpv6Prefix = (ND_IP_IPV6_PREFIX_STRU*)&pstConfigParaInd->astPrefixList[ulIndex];
        if ((IP_IPV6_OP_TRUE == pstIpv6Prefix->ulBitA)
            && ((ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)*8 == pstIpv6Prefix->ulBitPrefixLen)
            && (!IP_IPV6_64BITPREFIX_EQUAL_ZERO(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_LINKLOCAL_ADDR(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstIpv6Prefix->aucPrefix)))
        {
            *pulPrefixIndex = ulIndex;
            return IP_SUCC;
        }
    }

    return IP_FAIL;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetNwPara
 Description     : ��ID_ESM_IP_NW_PARA_IND�л�ȡ�������
 Input           : pstNwParaInd--------------��Ϣָ��
 Output          : pstNwParamTmp-------------�������ָ��
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-05  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_GetNwPara
(
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwParamTmp,
    AT_NDIS_IPV6_PDN_INFO_STRU         *pstNwParaInd
)
{
    VOS_UINT32                          ulPrefixIndex       = IP_NULL;
    VOS_UINT32                          ulRslt              = IP_NULL;

    IP_MEM_SET(pstNwParamTmp, IP_NULL, sizeof(ESM_IP_IPV6_NW_PARA_STRU));

    /* ��ȡHOP LIMIT */
    pstNwParamTmp->ucCurHopLimit = pstNwParaInd->ulBitCurHopLimit;

    /* ��ȡMTU */
    if (IP_IPV6_OP_TRUE == pstNwParaInd->ulBitOpMtu)
    {
        pstNwParamTmp->ulBitOpMtu = pstNwParaInd->ulBitOpMtu;
        pstNwParamTmp->ulMtu = pstNwParaInd->ulMtu;
    }

    /* ��ȡ�ӿڱ�ʶ�� */
    IP_MEM_CPY( pstNwParamTmp->aucInterfaceId,
                pstNwParaInd->aucInterfaceId,
                ND_IP_IPV6_IFID_LENGTH);

    /* �����ַǰ׺�б�Ŀǰֻ�����ʹ�õ�һ�����õ�IPv6ǰ׺ */
    ulRslt = IP_NDSERVER_FindIpv6EffectivePrefix(pstNwParaInd, &ulPrefixIndex);

    if (IP_SUCC != ulRslt)
    {
        return IP_FAIL;
    }

    IP_MEM_CPY( &pstNwParamTmp->astPrefixList[IP_NULL],
                &pstNwParaInd->astPrefixList[ulPrefixIndex],
                sizeof(ND_IP_IPV6_PREFIX_STRU));

    pstNwParamTmp->ulPrefixNum = 1;

    /* ��ȡDNS�������б� */
    IP_MEM_CPY( pstNwParamTmp->stDnsSer.aucPriDnsServer,
                pstNwParaInd->stDnsSer.aucPriServer,
                IP_IPV6_ADDR_LEN);
    IP_MEM_CPY( pstNwParamTmp->stDnsSer.aucSecDnsServer,
                pstNwParaInd->stDnsSer.aucSecServer,
                IP_IPV6_ADDR_LEN);
    pstNwParamTmp->stDnsSer.ucDnsSerNum = pstNwParaInd->stDnsSer.ucSerNum;

    /* ��ȡSIP�������б� */
    IP_MEM_CPY( pstNwParamTmp->stSipSer.aucPriSipServer,
                pstNwParaInd->stPcscfSer.aucPriServer,
                IP_IPV6_ADDR_LEN);
    IP_MEM_CPY( pstNwParamTmp->stSipSer.aucSecSipServer,
                pstNwParaInd->stPcscfSer.aucSecServer,
                IP_IPV6_ADDR_LEN);
    pstNwParamTmp->stSipSer.ucSipSerNum = pstNwParaInd->stPcscfSer.ucSerNum;

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaHeaderMsg
 Description     : RA����ͷ�̶���������
 Input           : ulIndex --- ND SERVERʵ������
 Output          : pucData --- ���Ļ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaHeaderMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucData
)
{
    ESM_IP_IPV6_NW_PARA_STRU         *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    /* ���� */
    *pucData = IP_ICMPV6_TYPE_RA;
    pucData++;

    /* ���� */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* ����У��� */
    pucData += 2;

    /* ��ǰ������ */
    *pucData = pstNwPara->ucCurHopLimit;
    pucData++;

    /* �����ַ���ñ�־��������״̬���ñ�־ */
    *pucData = (VOS_UINT8)(((g_ucMFlag & 0x1)<<7) | ((g_ucOFlag & 0x1)<<6));
    pucData++;

    /* ·�������� */
    IP_SetUint16Data(pucData, g_usRouterLifetime);
    pucData += 2;

    /* �ɴ�ʱ�� */
    IP_SetUint32Data(pucData, g_ulReachableTime);
    pucData += 4;

    /* �ط���ʱ�� */
    IP_SetUint32Data(pucData, g_ulRetransTimer);
    pucData += 4;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaOptMsg
 Description     : RA����ѡ�������
 Input           : ulIndex --- ND SERVERʵ������
                   pucMacAddr- Դ��·���ַ
 Output          : pucData --- ���Ļ���ָ��
                   pulLen ---- ���ĳ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaOptMsg
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    ESM_IP_IPV6_NW_PARA_STRU         *pstNwPara  = IP_NULL_PTR;
    VOS_UINT32                        ulCount    = IP_NULL;
    VOS_UINT32                        ulTmpMtu   = IP_NULL;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    /* ���� */
    *pucData = IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR;
    pucData++;

    /* ���� */
    *pucData = 1;
    pucData++;

    /* ��·���ַ */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    if (IP_IPV6_OP_TRUE == pstNwPara->ulBitOpMtu)
    {
        /* ���� */
        *pucData = IP_ICMPV6_OPT_MTU;
        pucData++;

        /* ���� */
        *pucData = 1;
        pucData++;

        /* ���� */
        pucData += 2;

        /*MTU: ȡNV�е�MTU��RA�е�MTU����Сֵ��Ϊ����PC��MTU*/
        ulTmpMtu = PS_MIN(g_ulNvMtu, pstNwPara->ulMtu);
        IP_SetUint32Data(pucData, ulTmpMtu);
        pucData += 4;

        (*pulLen) += IP_ND_OPT_UNIT_LEN;
    }

    for (ulCount = 0; ulCount < pstNwPara->ulPrefixNum; ulCount++)
    {
        /* ���� */
        *pucData = IP_ICMPV6_OPT_PREFIX_INFO;
        pucData++;

        /* ���� */
        *pucData = 4;
        pucData++;

        /* ǰ׺���� */
        *pucData = (VOS_UINT8)(pstNwPara->astPrefixList[ulCount].ulBitPrefixLen);
        pucData++;

        /* ��·�ϱ�־�����α�־ */
        *pucData = (VOS_UINT8)(((pstNwPara->astPrefixList[ulCount].ulBitL & 0x1)<<7)
                                | ((pstNwPara->astPrefixList[ulCount].ulBitA & 0x1)<<6));
        pucData++;

        /* ��Ч������ */
        IP_SetUint32Data(pucData, pstNwPara->astPrefixList[ulCount].ulValidLifeTime);
        pucData += 4;

        /* ѡ�������� */
        IP_SetUint32Data(pucData, pstNwPara->astPrefixList[ulCount].ulPreferredLifeTime);
        pucData += 4;

        /* �����ֶ� */
        pucData += 4;

        /* ǰ׺ */
        IP_MEM_CPY(pucData, pstNwPara->astPrefixList[ulCount].aucPrefix, IP_IPV6_ADDR_LEN);
        pucData += IP_IPV6_ADDR_LEN;

        (*pulLen) += (4 * IP_ND_OPT_UNIT_LEN);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormEtherHeaderMsg
 Description     : IPv6��ͷ����
 Input           : aucSrcMacAddr --- ԴMAC��ַ
                   aucDstMacAddr --- Ŀ��MAC��ַ
 Output          : pucData --- ���Ļ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormEtherHeaderMsg
(
    const VOS_UINT8                    *aucSrcMacAddr,
    const VOS_UINT8                    *aucDstMacAddr,
    VOS_UINT8                          *pucData
)
{
    /* Ŀ��MAC */
    IP_MEM_CPY( pucData,
                aucDstMacAddr,
                IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    /* ԴMAC */
    IP_MEM_CPY( pucData,
                aucSrcMacAddr,
                IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    /* ���� */
    IP_SetUint16Data(pucData, (VOS_UINT16)IP_GMAC_PAYLOAD_TYPE_IPV6);
    pucData += 2;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaMsg
 Description     : ����·�ɹ�����Ϣ
 Input           : ulIndex ------- ����RA����ʵ������
                   pstNdMsgData -- Ŀ����Ϣ����
 Output          : pucSendBuff --- ����RA���Ļ���
                   pulSendLen ---- ���ͱ��ĳ���

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;

    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg is entered.");

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* ����RA��ͷ */
    IP_NDSERVER_FormRaHeaderMsg(ulIndex, pucData);

    ulPacketLen += IP_ICMPV6_RA_HEADER_LEN;

    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    IP_MEM_CPY(pstInfoAddr->aucUeLinkLocalAddr, aucSrcIPAddr, IP_IPV6_ADDR_LEN);

    /* ����RA����ѡ�� */
    IP_NDSERVER_FormRaOptMsg(ulIndex, aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    /* ȷ���������鲥��ʽ */
    if ((VOS_NULL_PTR != pstNdMsgData)
            && (IP_IPV6_IS_LINKLOCAL_ADDR(pstNdMsgData->aucSrcIp))
            && (1 == pstNdMsgData->uNdMsgStru.stRs.ucBitOpSrcLinkLayerAddr))
    {
        IP_MEM_CPY( aucDstIPAddr,
                    pstNdMsgData->aucSrcIp,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    pstNdMsgData->uNdMsgStru.stRs.aucSrcLinkLayerAddr,
                    IP_MAC_ADDR_LEN);
    }
    else
    {
        IP_MEM_CPY( aucDstIPAddr,
                    g_aucNdAllNodesMulticaseAddr,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    g_aucNdAllNodesMacAddr,
                    IP_MAC_ADDR_LEN);
    }

    pucData -= IP_IPV6_HEAD_LEN;

    /* ����IPv6��ͷ */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* ����ICMPv6��ͷУ��� */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* ������̫��ͷ */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* ���ر��ĳ��� */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendRaMsg
 Description     : ����·�ɹ�����Ϣ
 Input           : ulIndex ------- ����RA����ʵ������
                   pstNdMsgData -- Ŀ����Ϣ����
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendRaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* �����γ�RA��Ϣ���� */
    IP_NDSERVER_FormRaMsg(ulIndex, pstNdMsgData, pucSendBuff, &ulSendLen);

    IP_NDSERVER_AddTransRaPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    /* ��RA��Ϣ���͵�PC */
    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);

}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaHeaderMsg
 Description     : NA����ͷ�̶���������
 Input           : pucTargetIPAddr --- Ŀ��IP��ַ
                   ucSolicitFlag   --- �����־
 Output          : pucData --- ���Ļ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaHeaderMsg
(
    const VOS_UINT8                    *pucTargetIPAddr,
    VOS_UINT8                           ucSolicitFlag,
    VOS_UINT8                          *pucData
)
{
    /* ���� */
    *pucData = IP_ICMPV6_TYPE_NA;
    pucData++;

    /* ���� */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* ����У��� */
    pucData += 2;

    /* ·������־�������־�����Ǳ�־ */
    *pucData = (VOS_UINT8)(0xa0 | ((ucSolicitFlag & 0x1)<<6));
    pucData++;

    /* ���� */
    pucData += 3;

    /* Ŀ���ַ */
    IP_MEM_CPY( pucData,
                pucTargetIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaOptMsg
 Description     : NA����ѡ�������
 Input           : pucMacAddr- Դ��·���ַ
 Output          : pucData --- ���Ļ���ָ��
                   pulLen ---- ���ĳ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaOptMsg
(
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    /* ���� */
    *pucData = IP_ICMPV6_OPT_TGT_LINK_LAYER_ADDR;
    pucData++;

    /* ���� */
    *pucData = 1;
    pucData++;

    /* ��·���ַ */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaMsg
 Description     : �����ھӹ�����Ϣ
 Input           : ulIndex ------- ����NA����ʵ������
                   pstNdMsgData -- Ŀ����Ϣ����
 Output          : pucSendBuff --- ����NA���Ļ���
                   pulSendLen ---- ���ͱ��ĳ���

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaMsg
(
    const IP_ND_MSG_STRU               *pstNdMsgData,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           ucSolicitFlag = IP_NULL;

    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNaMsg is entered.");

    /* ��������MAC��ַ��ΪԴMAC */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);

    if (VOS_NULL_PTR == pstNdMsgData)
    {
        /* ��������MAC��ַ����link-local��ַ */
        IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
        IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    }
    else
    {
        /* ʹ��Ŀ���ַ��ΪԴIP */
        IP_MEM_CPY( aucSrcIPAddr,
                    pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr,
                    IP_IPV6_ADDR_LEN);
    }


    /* ȷ���������鲥��ʽ */
    if ((VOS_NULL_PTR != pstNdMsgData)
            && (!IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstNdMsgData->aucSrcIp))
            && (1 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
    {
        IP_MEM_CPY( aucDstIPAddr,
                    pstNdMsgData->aucSrcIp,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    pstNdMsgData->uNdMsgStru.stNs.aucSrcLinkLayerAddr,
                    IP_MAC_ADDR_LEN);

        ucSolicitFlag = 1;
    }
    else
    {
        IP_MEM_CPY( aucDstIPAddr,
                    g_aucNdAllNodesMulticaseAddr,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    g_aucNdAllNodesMacAddr,
                    IP_MAC_ADDR_LEN);
    }

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* ����NA��ͷ */
    IP_NDSERVER_FormNaHeaderMsg(aucSrcIPAddr, ucSolicitFlag, pucData);

    ulPacketLen += IP_ICMPV6_NA_HEADER_LEN;

    /* ����NA��ѡ�� */
    IP_NDSERVER_FormNaOptMsg(aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    pucData -= IP_IPV6_HEAD_LEN;

    /* ����IPv6��ͷ */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* ����ICMPv6У��� */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNaMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* ������̫��ͷ */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* ���ر��ĳ��� */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendNaMsg
 Description     : �����ھӹ�����Ϣ
 Input           : ulIndex ------- ����NA����ʵ������
                   pstNdMsgData -- Ŀ����Ϣ����
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendNaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* �����γ�NA��Ϣ���� */
    IP_NDSERVER_FormNaMsg(pstNdMsgData, pucSendBuff, &ulSendLen);

    IP_NDSERVER_AddTransNaPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsHeaderMsg
 Description     : NS����ͷ�̶���������
 Input           : ulIndex --- ND SERVERʵ������
 Output          : pucData --- ���Ļ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsHeaderMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucData,
    const VOS_UINT8                    *pstDstAddr
)
{
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    /* ���� */
    *pucData = IP_ICMPV6_TYPE_NS;
    pucData++;

    /* ���� */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* ����У��� */
    pucData += 2;

    /* ���� */
    pucData += 4;

    /* Ŀ���ַ */
    IP_MEM_CPY( pucData,
                pstDstAddr,
                IP_IPV6_ADDR_LEN);

    pucData += IP_IPV6_ADDR_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsOptMsg
 Description     : NS����ѡ�������
 Input           : pucMacAddr- Դ��·���ַ
 Output          : pucData --- ���Ļ���ָ��
                   pulLen ---- ���ĳ���ָ��
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsOptMsg
(
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    /* ���� */
    *pucData = IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR;
    pucData++;

    /* ���� */
    *pucData = 1;
    pucData++;

    /* ��·���ַ */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsMsg
 Description     : ���ɵ�ַ�����ھ�������Ϣ
 Input           : ulIndex ------- ����NS����ʵ������
 Output          : pucSendBuff --- ����NS���Ļ���
                   pulSendLen ---- ���ͱ��ĳ���

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen,
    const VOS_UINT8                    *pstDstAddr
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};

    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNsMsg is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /* ����Ŀ��IP��������ڵ��鲥��ַ */
    IP_ProduceSolicitedNodeMulticastIPAddr(aucDstIPAddr, pstDstAddr);
    IP_ProduceSolicitedNodeMulticastMacAddr(aucDstMacAddr, pstDstAddr);

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* ����NS��ͷ */
    IP_NDSERVER_FormNsHeaderMsg(ulIndex, pucData, pstDstAddr);

    ulPacketLen += IP_ICMPV6_NS_HEADER_LEN;

    /* ����NS��ѡ�� */
    IP_NDSERVER_FormNsOptMsg(aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    pucData -= IP_IPV6_HEAD_LEN;

    /* ����IPv6��ͷ */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* ����ICMPv6У��� */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNsMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* ������̫��ͷ */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* ���ر��ĳ��� */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendNsMsg
 Description     : ���͵�ַ�����ھ�������Ϣ
 Input           : ulIndex ------- ����NS����ʵ������
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendNsMsg
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *pstDstAddr
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* �����γ�NS��Ϣ���� */
    IP_NDSERVER_FormNsMsg(ulIndex, pucSendBuff, &ulSendLen, pstDstAddr);

    IP_NDSERVER_AddTransNsPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);
}


/*****************************************************************************
 �� �� ��  : NdSer_GetAddrInfoIdx
 ��������  : ����ExRabId����NDSERVERʵ�������
 �������  : VOS_UINT8 ucExRabId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : h00218138
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NdSer_GetAddrInfoIdx(VOS_UINT8 ucExRabId)
{
    VOS_UINT32 i = 0;

    /* ��ѯ�Ƿ��Ѵ�����ӦEntity */
    do{
        if((PS_TRUE == g_astNdServerAddrInfo[i].ucValidFlag) && (ucExRabId == g_astNdServerAddrInfo[i].ucEpsbId))
        {
            /*�ҵ���Ӧʵ��*/
            return i;
        }

    }while((++i) < IP_NDSERVER_ADDRINFO_MAX_NUM);

    return IP_NDSERVER_ADDRINFO_MAX_NUM;
}

/*****************************************************************************
 �� �� ��  : NdSer_AllocAddrInfo
 ��������  : ����һ�����е�NDSERVERʵ��
 �������  : ��
 �������  : ulIndex
 �� �� ֵ  : IP_NDSERVER_ADDR_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : h00218138
    �޸�����   : �����ɺ���

*****************************************************************************/
IP_NDSERVER_ADDR_INFO_STRU* NdSer_AllocAddrInfo(VOS_UINT32* pUlIndex)
{
    VOS_UINT32 i = 0;

    if(IP_NULL_PTR == pUlIndex)
    {
        return IP_NULL_PTR;
    }

    *pUlIndex = IP_NDSERVER_ADDRINFO_MAX_NUM;

    do{
        if(PS_FALSE == g_astNdServerAddrInfo[i].ucValidFlag)
        {
            /*�ҵ�����ʵ��*/
            *pUlIndex = i;
            return &g_astNdServerAddrInfo[i];
        }

    }while((++i) < IP_NDSERVER_ADDRINFO_MAX_NUM);

    return IP_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : NdSer_CheckIpv6PdnInfo
 ��������  : PDN IPV6��ַ��Ϣ���
 �������  : AT_NDIS_IPV6_PDN_INFO_STRU
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��11��
    ��    ��   : h00159435
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��1��15��
    ��    ��   : h00218138
    �޸�����   : DSDA������ʹ��ExRabId��ӳ��NdSerʵ��

*****************************************************************************/
VOS_UINT32 NdSer_CheckIpv6PdnInfo(AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo)
{
    VOS_UINT32                          ulIndex       = IP_NULL;
    ND_IP_IPV6_PREFIX_STRU             *pstIpv6Prefix = IP_NULL_PTR;

    /* ����ǰ׺�б�����A��ʶΪ1��ǰ׺����Ϊ64��ǰ׺ */
    for (ulIndex = IP_NULL; ulIndex < pstIpv6PdnInfo->ulPrefixNum; ulIndex++)
    {
        pstIpv6Prefix = (ND_IP_IPV6_PREFIX_STRU*)&pstIpv6PdnInfo->astPrefixList[ulIndex];
        if ((PS_TRUE == pstIpv6Prefix->ulBitA)
            && ((ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)*8 == pstIpv6Prefix->ulBitPrefixLen)
            && (!IP_IPV6_64BITPREFIX_EQUAL_ZERO(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_LINKLOCAL_ADDR(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstIpv6Prefix->aucPrefix)))
        {
            return PS_SUCC;
        }
    }

    return PS_FAIL;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnInfoCfg
 Description     : ����NDIS������Ipv6PdnInfoCfg
 Input           : VOS_UINT8 ucRabId, AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact
    1.houguoqiang 00218138      2013-1-16  Modified for DSDA
*****************************************************************************/
VOS_VOID NdSer_Ipv6PdnInfoCfg(VOS_UINT8 ucExRabId, AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo)
{
    VOS_UINT32                          ulIndex       = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr   = IP_NULL_PTR;
    ESM_IP_IPV6_NW_PARA_STRU            stNwParamTmp  = {IP_NULL};

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcEsmIpNwParaInd is entered.");

    /*ͨ����չRabId����NDSERVERʵ�壬������Ҳ����������һ�����е�*/
    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    }
    else
    {
        /*����һ��AddrInfo�ṹ�壬���һ��Index*/
        pstInfoAddr = NdSer_AllocAddrInfo(&ulIndex);
    }

    if(IP_NULL_PTR == pstInfoAddr)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Get ND Server Entity failed.", ucExRabId);
        return;
    }

    /* ��ȡ������� */
    if (IP_SUCC != IP_NDSERVER_GetNwPara(&stNwParamTmp, pstIpv6PdnInfo))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Get Nw Param fail.");
        return;
    }

    /* �ж��Ƿ�δ�����·��ǰ׺ */
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        VOS_UINT8* pucIpV6;
        pucIpV6 = IP_NDSERVER_GetTeDetectIp(stNwParamTmp.astPrefixList[0].aucPrefix);

        /* MT�ػ��ٿ�����ND SERVER�յ�����RAǰ���������յ�TE���ظ���ַ���NS */
        if(IP_NULL_PTR != pucIpV6)
        {
            IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Using saved TeAddr to get MAC.");

            IP_MEM_CPY(pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr, pucIpV6, ND_IP_IPV6_ADDR_LENGTH);
            pstInfoAddr->stTeAddrInfo.enTeAddrState = IP_NDSERVER_TE_ADDR_INCOMPLETE;

            /* �����յ��ظ���ַ����ĵȴ���ʱ�� */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_FIRST_NS);
        }
        else
        {
            IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: None saved TeAddr.");

            /* ����·�ɹ��涨ʱ�� */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);
        }
    }
    /* �ж��Ƿ�·��ǰ׺�����˱仯 */
    else if (0 != IP_MEM_CMP(    pstInfoAddr->stIpv6NwPara.astPrefixList[0].aucPrefix,
                                stNwParamTmp.astPrefixList[0].aucPrefix,
                                (ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)))
    {
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Valid ND Server get new Nw Param.");

        /* ���TE��ַ��¼ */
        IP_MEM_SET( &pstInfoAddr->stTeAddrInfo,
                    IP_NULL,
                    sizeof(IP_NDSERVER_TE_ADDR_INFO_STRU));

        /* ����·�ɹ��涨ʱ�� */
        IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);
    }

    /* ��stNwParamTmp�е����ݿ�����pstInfoAddr->stIpv6NwPara�� */
    IP_MEM_CPY( &pstInfoAddr->stIpv6NwPara,
                &stNwParamTmp,
                sizeof(ESM_IP_IPV6_NW_PARA_STRU));


    /* ���ó��غ� */
    pstInfoAddr->ucEpsbId = ucExRabId;

    /* ��λND SERVER�ṹ����Ч��־ */
    pstInfoAddr->ucValidFlag = IP_TRUE;

    /* ����RA��Ϣ��PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);/* [false alarm]:���뱣֤�˲���Խ�� */
        IPND_ERROR_LOG(NDIS_NDSERVER_PID,"NdSer_Ipv6PdnInfoCfg:Send RA Msg failed.");
    }

    return;
}


/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeRsData
 Description     : ��RS�����и�ʽת��
 Input           : pucSrcData ----------- Դ����ָ��
                   pstDestData ---------- Ŀ��ת���ṹָ��
                   ulIcmpv6HeadOffset --- ICMPv6��ͷƫ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeRsData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_RS_STRU                  *pstRs = &pstDestData->uNdMsgStru.stRs;

    /* ��ȡPAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_RS_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_RS_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstRs->ucBitOpSrcLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstRs->aucSrcLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstRs->ucBitOpSrcLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Redundant Source Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid Source Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_RsMsgProc
 Description     : ����RS��Ϣ
 Input           : ulIndex  -------------- ������Ϣʵ������
                   pucSrcData ------------ IP���ݱ�
                   ulIcmpv6HeadOffset ---- ICMPv6����ͷƫ����
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-06  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_RsMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvRsPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrRsPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc: ND Server info flag is invalid!");
        return ;
    }

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeRsData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrRsPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcessRsMsg: Invalid IPV6 RS Msg:!");
        return ;
    }

    /* ����RA��Ϣ��PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, pstNdMsgData))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc:Send RA Msg failed.");
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeNsData
 Description     : ��NS�����и�ʽת��
 Input           : pucSrcData ----------- Դ����ָ��
                   pstDestData ---------- Ŀ��ת���ṹָ��
                   ulIcmpv6HeadOffset --- ICMPv6��ͷƫ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeNsData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_NS_STRU                  *pstNs = &pstDestData->uNdMsgStru.stNs;

    /* ��ȡPAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_NS_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    IP_MEM_CPY( pstNs->aucTargetAddr,
                pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_TARGET_ADDR_OFFSET,
                IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_NS_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstNs->ucBitOpSrcLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstNs->aucSrcLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstNs->ucBitOpSrcLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Redundant Source Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid Source Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_IsSelfIPAddr
 Description     : �ж��Ƿ����Լ���IP��ַ
 Input           : ulIndex  -------------- ������Ϣʵ������
                   aucIPAddr ------------  IP��ַָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_IsSelfIPAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    VOS_UINT8                           aucLinkLocalIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucGlobalIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);

    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucLinkLocalIPAddr, aucMacAddr);
    IP_SetUint16Data(aucLinkLocalIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    IP_ProduceIfaceIdFromMacAddr(aucGlobalIPAddr, aucMacAddr);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);
    IP_MEM_CPY( aucGlobalIPAddr,
                pstNwPara->astPrefixList[0].aucPrefix,
                ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH);

    /*lint -e960*/
    if ((IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                 aucLinkLocalIPAddr,
                                 IP_IPV6_ADDR_LEN))
        || (IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                    aucGlobalIPAddr,
                                    IP_IPV6_ADDR_LEN)))

    /*lint +e960*/
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EqualAdvertisedPrefix
 Description     : �ж��Ƿ�����ѹ����ȫ��ǰ׺
 Input           : ulIndex  -------------- ������Ϣʵ������
                   aucIPAddr ------------  IP��ַָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_EqualAdvertisedPrefix
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    if (IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                pstNwPara->astPrefixList[0].aucPrefix,
                                ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH))
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_RcvTeDetectionAddr
 Description     : �յ��ظ���ַ����ַ
 Input           : ulIndex  -------------- ND SERVERʵ������
                   aucIPAddr ------------  IP��ַָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_RcvTeDetectionAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    /*lint -e960*/
    if ((IP_NDSERVER_TE_ADDR_REACHABLE == pstTeInfo->enTeAddrState)
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeGlobalAddr, aucIPAddr, IP_IPV6_ADDR_LEN)))
    /*lint +e960*/
    {
        return;
    }

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_RcvTeDetectionAddr: Old Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
    IP_MEM_CPY( pstTeInfo->aucTeGlobalAddr,
                aucIPAddr,
                IP_IPV6_ADDR_LEN);
    pstTeInfo->enTeAddrState = IP_NDSERVER_TE_ADDR_INCOMPLETE;

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_RcvTeDetectionAddr: New Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_NsMsgProc
 Description     : ����NS��Ϣ
 Input           : ulIndex  -------------- ������Ϣʵ������
                   pucSrcData ------------ IP���ݱ�
                   ulIcmpv6HeadOffset ---- ICMPv6����ͷƫ����
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_NsMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc is entered.");
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvNsPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeNsData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrNsPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: Invalid IPV6 NS Msg:!");
        return ;
    }

    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        /* MT�ػ��ٿ�����ND SERVER�յ�����RAǰ���������յ�TE���ظ���ַ���NS */
        if ((IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
                && (0 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
        {
            IP_NDSERVER_SaveTeDetectIp(pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: receive DAD NS packet before RA.");
        }
        else
        {
            IP_NDSERVER_AddErrNsPktNum(ulIndex);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: ND Server info flag is invalid!");
        }
        return ;
    }

    if (IP_TRUE == IP_NDSERVER_IsSelfIPAddr(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr))
    {
        /* ����NA��Ϣ��PC */
        if (PS_SUCC != IP_NDSERVER_SendNaMsg(ulIndex, pstNdMsgData))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Send NA Msg failed.");
        }
    }
    else
    {
        /* �ж��Ƿ����ظ���ַ���NS */
        if ((IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
                && (0 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
        {
            if (IP_TRUE == IP_NDSERVER_EqualAdvertisedPrefix(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr))
            {
                IP_NDSERVER_RcvTeDetectionAddr(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr);

                /* �����յ��ظ���ַ����ĵȴ���ʱ�� */
                IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_FIRST_NS);

                IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Receive duplicate addr detection packet.");
                return ;
            }
            else
            {
                IP_NDSERVER_AddErrNsPktNum(ulIndex);
                IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Duplicate addr detection IP don't equal Advertised Prefix, discard!");
                return ;
            }
        }
        else
        {
            IP_NDSERVER_AddErrNsPktNum(ulIndex);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Target IP is not self addr, discard!");
            return ;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeNaData
 Description     : ��NA�����и�ʽת��
 Input           : pucSrcData ----------- Դ����ָ��
                   pstDestData ---------- Ŀ��ת���ṹָ��
                   ulIcmpv6HeadOffset --- ICMPv6��ͷƫ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeNaData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_NA_STRU                  *pstNa = &pstDestData->uNdMsgStru.stNa;

    /* ��ȡPAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_NA_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pstNa->ucBitR = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 7) & 0x01;
    pstNa->ucBitS = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 6) & 0x01;
    pstNa->ucBitO = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 5) & 0x01;

    IP_MEM_CPY( pstNa->aucTargetAddr,
                pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_TARGET_ADDR_OFFSET,
                IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_NA_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_TGT_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstNa->ucBitOpTargetLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstNa->aucTargetLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstNa->ucBitOpTargetLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Redundant Target Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid Target Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EqualSavedTeAddr
 Description     : �ж��Ƿ����ѱ����TE��ַ
 Input           : ulIndex  -------------  ND SERVERʵ������
                   aucIPAddr ------------  IP��ַָ��
                   aucMACAddr -----------  MAC��ַָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_EqualSavedTeAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr,
    const VOS_UINT8                    *aucMACAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    /*lint -e960*/
    if ((IP_NDSERVER_TE_ADDR_REACHABLE == pstTeInfo->enTeAddrState)
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeGlobalAddr, aucIPAddr, IP_IPV6_ADDR_LEN))
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeLinkLayerAddr, aucMACAddr, IP_MAC_ADDR_LEN)))
    /*lint +e960*/
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}
/*****************************************************************************
 Function Name   : IP_NDSERVER_SendDlPkt
 Description     : �������л����IPV6���ݰ�
 Input           : ulIndex  -------------  ND SERVERʵ������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_SendDlPkt(VOS_UINT32 ulIndex)
{
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_UINT8                           ucRabId     = 0;
    ADS_PKT_TYPE_ENUM_UINT8             ucPktType   = 0;
    VOS_UINT16                          usApp       = 0;
    VOS_INT32                           lLockKey;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    while(PS_TRUE != (LUP_IsQueEmpty(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex))))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
        {
            VOS_Splx(lLockKey);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDlPkt, LUP_DeQue return fail!");
            return;
        }
        VOS_Splx(lLockKey);

        /*�� ImmZc��ȡ��RabId��enPdpType*/
        /*lint -e522*/
        usApp     = IMM_ZcGetUserApp(pstImmZc);
        ucRabId   = (VOS_UINT8)(usApp & 0xFF);  /*�����ֵʵ���� ��չRabId*/
        ucPktType = (VOS_UINT8)(usApp >> 8);

        if (PS_SUCC != Ndis_DlSendNcm(ucRabId, ucPktType, pstImmZc))
        {
            IMM_ZcFree(pstImmZc);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDlPkt, Ndis_DlSendNcm fail!");
        }
        /*lint +e522*/

        IP_NDSERVER_AddSendQuePktNum(ulIndex);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_UpdateTeAddrInfo
 Description     : �յ��ظ���ַ����ַ
 Input           : ulIndex  -------------  ND SERVERʵ������
                   aucGlobalIPAddr ------  ȫ��IP��ַָ��
                   aucMACAddr -----------  MAC��ַָ��
                   aucLinkLocalIPAddr ---  ��·����IP��ַָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_UpdateTeAddrInfo
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucGlobalIPAddr,
    const VOS_UINT8                    *aucMACAddr,
    const VOS_UINT8                    *aucLinkLocalIPAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_UpdateTeAddrInfo: Old Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
    IP_MEM_CPY( pstTeInfo->aucTeGlobalAddr,
                aucGlobalIPAddr,
                IP_IPV6_ADDR_LEN);

    IP_MEM_CPY( pstTeInfo->aucTeLinkLayerAddr,
                aucMACAddr,
                IP_MAC_ADDR_LEN);

    /*��������MAC֡ͷ�е�Ŀ��MAC��ַ*/
    IP_MEM_CPY( IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex),
                aucMACAddr,
                IP_MAC_ADDR_LEN);

    if (IP_IPV6_IS_LINKLOCAL_ADDR(aucLinkLocalIPAddr))
    {
        IP_MEM_CPY( pstTeInfo->aucTeLinkLocalAddr,
                    aucLinkLocalIPAddr,
                    IP_IPV6_ADDR_LEN);
    }
    else
    {
        IP_MEM_SET( pstTeInfo->aucTeLinkLocalAddr,
                    IP_NULL,
                    IP_IPV6_ADDR_LEN);

    }

    pstTeInfo->enTeAddrState = IP_NDSERVER_TE_ADDR_REACHABLE;

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_UpdateTeAddrInfo: New Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */

    /*��������IP��������е����ݰ�*/
    IP_NDSERVER_SendDlPkt(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_NaMsgProc
 Description     : ����NA��Ϣ
 Input           : ulIndex  -------------- ������Ϣʵ������
                   pucSrcData ------------ IP���ݱ�
                   ulIcmpv6HeadOffset ---- ICMPv6����ͷƫ����
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_NaMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc is entered.");
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvNaPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc: ND Server info flag is invalid!");
        return ;
    }

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeNaData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc: Invalid IPV6 NS Msg:!");
        return ;
    }

    if (0 == pstNdMsgData->uNdMsgStru.stNa.ucBitOpTargetLinkLayerAddr)
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Packet don't contain Target Linklayer Addr, discard!");
        return ;
    }

    if ((IP_TRUE != IP_NDSERVER_IsSelfIPAddr(ulIndex, pstNdMsgData->aucDesIp))
        && (!IP_IPV6_IS_MULTICAST_ADDR(pstNdMsgData->aucDesIp)))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Destination IP don't contain self Addr, discard!");
        return ;
    }

    if (IP_TRUE != IP_NDSERVER_EqualAdvertisedPrefix(ulIndex, pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Target IP don't equal Advertised Prefix, discard!");
        return ;
    }

    if (IP_TRUE != IP_NDSERVER_EqualSavedTeAddr(    ulIndex,
                                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr))
    {
        IP_NDSERVER_UpdateTeAddrInfo(   ulIndex,
                                        pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                        pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr,
                                        pstNdMsgData->aucSrcIp);

        /*MAC��ֱַ�Ӵ�ND SERVERʵ�����ã�����Ҫ������APRģ��*/
        /*IP_NDSERVER_ConfigArpInfo(  ulIndex,
                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr);*/

    }

    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_PERIODIC_NS);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_BuildTooBigICMPPkt
 Description     : �γ���PC�ظ��ĳ�������Ӧ
 Input           : pucSrcData ----------- Դ����ָ��
                   pstDestData ---------- Ŀ��ת���ṹָ��
                   ulIcmpv6HeadOffset --- ICMPv6��ͷƫ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_BuildTooBigICMPPkt
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pstDestData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    if  (ulDataLen <= (IP_IPV6_HEAD_LEN + IP_ICMPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_BuildTooBigICMPPkt: ulDataLen is too short.", ulDataLen);
        return IP_FAIL;
    }

    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*�õ�Ŀ��IPV6��ַ*/
    IP_MEM_CPY(aucDstIPAddr, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*�õ�Ŀ��MAC��ַ*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    /*ָ��ICMP�ײ� */
    pucData  = pstDestData + IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /*ICMP type��*/
    *pucData = IP_ICMPV6_PACKET_TOO_BIG;
    pucData++;

    /*ICMP code��*/
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /*ICMP У�����*/
    *(VOS_UINT16 *)(VOS_VOID*)pucData = 0;
    pucData += 2;

    /*MTU ��*/
    /*lint -e960*/
    *(VOS_UINT32 *)(VOS_VOID*)pucData = VOS_HTONL(ulDataLen);
    /*lint +e960*/
    pucData += 4;

    /*��дICMP PayLoad����*/
    IP_MEM_CPY(pucData, pucIpMsg,((ulDataLen-IP_IPV6_HEAD_LEN)- IP_ICMPV6_HEAD_LEN));

    /*ָ��IPV6�ײ�*/
    pstDestData += IP_ETHERNET_HEAD_LEN;
    /*��дIPV6ͷ��*/
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, (ulDataLen-IP_IPV6_HEAD_LEN), pstDestData, IP_HEAD_PROTOCOL_ICMPV6);

    /* ����ICMPv6��ͷУ��� */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pstDestData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg: Build ICMPv6 Checksum failed.");
        return IP_FAIL;
    }

    /* ������̫��ͷ */
    pstDestData -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pstDestData);

    return IP_SUCC;
}

/*****************************************************************************
 �� �� ��  : IP_NDSERVER_ProcTooBigPkt
 ��������  : ����PC���͵ĳ�����
 �������  : VOS_VOID  *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��9��
    ��    ��   : 00159435
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTooBigPkt(VOS_UINT8 ucRabId, VOS_UINT8 *pucSrcData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                           ulIndex;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt: ND Server info flag is invalid!");
        return ;
    }

    IP_NDSERVER_AddRcvBooBigPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    if (IP_SUCC != IP_NDSERVER_BuildTooBigICMPPkt(ulIndex, pucIpMsg, pucSendBuff, ulDataLen))
    {
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt: IP_NDSERVER_BuildTooBigICMPPkt FAIL!");
        return;
    }

    /* ����������Ӧ���͵�PC */
    if (PS_FAIL == Ndis_SendMacFrm(pucSendBuff, ulDataLen+IP_ETHERNET_HEAD_LEN, pstInfoAddr->ucEpsbId))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt:Send TooBigPkt failed.");
        return;
    }

    IP_NDSERVER_AddTransTooBigPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormEchoReply
 Description     : �γ���PC�ظ���ECHO REPLY
 Input           : pucSrcData ----------- Դ����ָ��
                   pstDestData ---------- Ŀ��ת���ṹָ��
                   ulIcmpv6HeadOffset --- ICMPv6��ͷƫ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_FormEchoReply
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pstDestData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    if (ulDataLen <= IP_IPV6_HEAD_LEN)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_FormEchoReply: ulDataLen is too short.", ulDataLen);
        return IP_FAIL;
    }

    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*�õ�Ŀ��IPV6��ַ*/
    IP_MEM_CPY(aucDstIPAddr, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*�õ�Ŀ��MAC��ַ*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    /*ָ��ICMP�ײ� */
    pucData  = pstDestData + IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /*��дICMP����*/
    pucIpMsg += IP_IPV6_HEAD_LEN;
    IP_MEM_CPY(pucData, pucIpMsg,(ulDataLen-IP_IPV6_HEAD_LEN));

    /*ICMP type��*/
    *pucData = IP_ICMPV6_TYPE_ECHOREPLY;
    pucData++;

    /*ICMP code��*/
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /*ICMP У�����*/
    *(VOS_UINT16 *)(VOS_VOID*)pucData = 0;

    /*ָ��IPV6�ײ�*/
    pstDestData += IP_ETHERNET_HEAD_LEN;
    /*��дIPV6ͷ��*/
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, (ulDataLen-IP_IPV6_HEAD_LEN), pstDestData, IP_HEAD_PROTOCOL_ICMPV6);

    /* ����ICMPv6��ͷУ��� */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pstDestData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormEchoReply: Build ICMPv6 Checksum failed.");
        return IP_FAIL;
    }

    /* ������̫��ͷ */
    pstDestData -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pstDestData);

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EchoRequestMsgProc
 Description     : ����ECHO REQUEST��Ϣ
 Input           : ulIndex  -------------- ������Ϣʵ������
                   pucSrcData ------------ IP���ݱ�
                   ulIcmpv6HeadOffset ---- ICMPv6����ͷƫ����
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_EchoRequestMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    VOS_UINT8                           aucPktAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvEchoPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrEchoPktNum(ulIndex);
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc: ND Server info flag is invalid!");
        return ;
    }

    IP_MEM_CPY(aucPktAddr, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    if (IP_TRUE != IP_NDSERVER_IsSelfIPAddr(ulIndex, aucPktAddr))
    {
        IP_NDSERVER_AddErrEchoPktNum(ulIndex);
        return;
    }

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    if (IP_SUCC != IP_NDSERVER_FormEchoReply(ulIndex,pucIpMsg, pucSendBuff, ulDataLen))
    {
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc: IP_NDSERVER_FormEchoReply fail!");
        return ;
    }

    /* ��ECHO REPLY���͵�PC */
    if (PS_FAIL == Ndis_SendMacFrm(pucSendBuff, ulDataLen+IP_ETHERNET_HEAD_LEN, pstInfoAddr->ucEpsbId))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc:Send ECHO REPLY failed.");
        return;
    }

    IP_NDSERVER_AddTransEchoPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : NdSer_NdAndEchoPktProc
 Description     : ����PC���͵�ND��ECHO REQUEST����
 Input           : pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact
    2.h00218138          2013-1-15  DSDA

*****************************************************************************/
VOS_VOID NdSer_NdAndEchoPktProc(VOS_VOID *pRcvMsg)
{
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT32                          ulIcmpv6HeadOffset = IP_NULL;
    IP_ICMPV6_TYPE_ENUM_UINT32          enIcmpv6MsgType = IP_ICMPV6_TYPE_BUTT;
    VOS_UINT32                          ulIndex         = IP_NULL;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           ucExRabId;
    IP_NDSERVER_ADDR_INFO_STRU*         pstNDSerAddrInfoTmp;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc is entered.");

    ulDataLen = IMM_ZcGetUsedLen(pstAdsNdisMsg->pstSkBuff);
    pucData   = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc, IMM_ZcGetDataPtr return NULL");
        return;
    }

    ucExRabId = ND_FORM_EXEPSID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);

    if (IP_SUCC != ND_CheckEpsIdValid(ucExRabId))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc, IMM_ZcGetDataPtr return NULL", ucExRabId);
        return;
    }

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        /* MT�ػ��ٿ�����ND SERVER�յ�����RAǰ���������յ�TE���ظ���ַ���NS ��Ϊ���ܹ����������Ϣ��
        �˴���ʱ����һ��ND Ser Addr Info*/
        IPND_INFO_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Get Addr Info, will alloc new addr info for NS msg", pstAdsNdisMsg->ucRabId);
        pstNDSerAddrInfoTmp = NdSer_AllocAddrInfo(&ulIndex);
        if(IP_NULL_PTR == pstNDSerAddrInfoTmp)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_AllocAddrInfo: return NULL!");
            return;
        }
        pstNDSerAddrInfoTmp->ucValidFlag = IP_FALSE;
    }

    IP_NDSERVER_AddRcvPktTotalNum(ulIndex);

    /* �ж���Ϣ�Ƿ�Ϸ���ND��Ϣ */
    if (IP_TRUE != IP_IsValidNdMsg(pucData, ulDataLen, &ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddDiscPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Invalid ND Msg!");
        return ;
    }

    /* ȡICMPV6��Ϣ�е�TYPE�ֶ� */
    enIcmpv6MsgType = *(pucData + ulIcmpv6HeadOffset);

    switch(enIcmpv6MsgType)
    {
        case IP_ICMPV6_TYPE_RS:
            IP_NDSERVER_RsMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_NS:
            IP_NDSERVER_NsMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_NA:
            IP_NDSERVER_NaMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_ECHOREQUEST:
            IP_NDSERVER_EchoRequestMsgProc(ulIndex, pucData, ulDataLen);
            break;

        default:
            IP_NDSERVER_AddDiscPktNum(ulIndex);
            IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Ignored IPV6 ND Msg:!", enIcmpv6MsgType);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendDhcp6Reply
 Description     : ��װ������DHCPV6����
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435          2011-12-6  Draft Enact

*****************************************************************************/
/*lint -e778*/
/*lint -e572*/
VOS_UINT32  IP_NDSERVER_SendDhcp6Reply
(
    VOS_UINT32                          ulIndex,
    const ND_IP_IPV6_DNS_SER_STRU      *pstDnsSer,
    VOS_UINT8                          *pDhcpInfoReqData,
    VOS_UINT16                          usReqIp6PktLen
)
{
    NDIS_IP6_HDR_STRU                  *pstDhcpReplyIpv6Hdr;
    UDP_HEAD_ST                        *pstDhcpReplyUdpHdr;
    IPV6_DHCP_DNS_OPTION_STRU           stIpv6DhcpDnsOpt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstDhcpClientIdOpt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstDhcpRequestOpt;
    IPV6_PKT_DHCP_DUID_LL_OPT_STRU      stDhcpDuidLLOpt;
    VOS_UINT8                          *pDhcpReplyDhcpHdrOffset;/* �ƶ�ָ�� */
    VOS_UINT16                          usReplyUdpDataLen;
    VOS_UINT16                          usDhcpReplyPktLen;
    VOS_UINT16                          usDnsOptLen             = 0;
    VOS_UINT16                          usReqDhcpOptLen;
    VOS_UINT16                          usDhcpClientIdOptLen    = 0;
    VOS_UINT16                          usDhcpRequestDnsOptLen  = 0;
    VOS_UINT32                          usDhcpReqOptCodeLoopCnt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstReqDhcpOptHdr;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;
    VOS_UINT8                          *pucSendBuff = VOS_NULL_PTR;
    VOS_UINT8                           ucEpsId;

    if ( usReqIp6PktLen <= ((IP_IPV6_HEAD_LEN + IP_UDP_HEAD_LEN) + IP_UDP_DHCP_HDR_SIZE))
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
             "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, ERROR, No Option Len!");*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, No Option Len!");
        return PS_FAIL;
    }

    /*20160122 V722 coverity --begin*/
    IP_MEM_SET(&stIpv6DhcpDnsOpt, 0, sizeof(IPV6_DHCP_DNS_OPTION_STRU));
    IP_MEM_SET(&stDhcpDuidLLOpt, 0, sizeof(IPV6_PKT_DHCP_DUID_LL_OPT_STRU));
    /*20160122 V722 coverity --end*/

    usReqDhcpOptLen     = usReqIp6PktLen - ((IP_IPV6_HEAD_LEN + IP_UDP_HEAD_LEN) + IP_UDP_DHCP_HDR_SIZE) ;
    usReplyUdpDataLen   = IP_UDP_HEAD_LEN
                            + IP_UDP_DHCP_HDR_SIZE
                            + IP_IPV6_DHCP_OPT_CLIENT_ID_LEN;
    pstReqDhcpOptHdr    = (IPV6_PKT_DHCP_OPT_HDR_STRU *)(VOS_VOID*)(pDhcpInfoReqData
                            + IP_IPV6_HEAD_LEN
                            + IP_UDP_HEAD_LEN
                            + IP_UDP_DHCP_HDR_SIZE);


    /* ��ȡ DHCP Client ID Option */
    (VOS_VOID)TTF_NDIS_Ipv6GetDhcpOption(pstReqDhcpOptHdr,
                            usReqDhcpOptLen,
                            IP_IPV6_DHCP_OPT_CLIEND_ID,
                            (IPV6_PKT_DHCP_OPT_HDR_STRU **)&pstDhcpClientIdOpt,
                            0 );

    if ( VOS_NULL_PTR != pstDhcpClientIdOpt )
    {
        usDhcpClientIdOptLen    = VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen);
        usReplyUdpDataLen      += (usDhcpClientIdOptLen + 4);
    }

    /* ��ȡ DHCP Request Option */
    (VOS_VOID)TTF_NDIS_Ipv6GetDhcpOption(pstReqDhcpOptHdr,
                            usReqDhcpOptLen,
                            IP_IPV6_DHCP_OPT_REQUEST,
                            (IPV6_PKT_DHCP_OPT_HDR_STRU **)&pstDhcpRequestOpt,
                            0);

    if ( VOS_NULL_PTR != pstDhcpRequestOpt )
    {
        for (usDhcpReqOptCodeLoopCnt = 0; usDhcpReqOptCodeLoopCnt < (pstDhcpRequestOpt->usDhcpOptLen); usDhcpReqOptCodeLoopCnt +=2 )
        {
            if ( IP_IPV6_DHCP6_OPT_DNS_SERVERS == VOS_NTOHS(*((VOS_UINT16 *)(&(pstDhcpRequestOpt->aucDhcpOptData[usDhcpReqOptCodeLoopCnt])))) )
            {
                usDnsOptLen     = pstDnsSer->ucDnsSerNum;
                if ( (0 == usDnsOptLen) || (IP_IPV6_MAX_DNS_NUM < usDnsOptLen) )
                {
                    /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
                         "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, ERROR, DNS Option is err!");*/
                    IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, DNS Option is err!");
                    return PS_FAIL;
                }

                usDhcpRequestDnsOptLen  = (VOS_UINT16)(usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU));
                usReplyUdpDataLen      += (usDhcpRequestDnsOptLen +4);
                break;
            }
        }
    }

    if ( usReplyUdpDataLen <= (IP_UDP_HEAD_LEN + IP_UDP_DHCP_HDR_SIZE + IP_IPV6_DHCP_DUID_LL_OPT_LEN))
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_ERROR,
             "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, No content need to reply!");*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, No content need to reply!");
        return PS_SUCC;
    }

    usDhcpReplyPktLen    = IP_IPV6_HEAD_LEN + usReplyUdpDataLen;


    /* ��������MAC��ַ����link-local��ַ */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*�õ�Ŀ��IPV6��ַ*/
    IP_MEM_CPY(aucDstIPAddr, pDhcpInfoReqData + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*�õ�Ŀ��MAC��ַ*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /*ָ��IPV6�ײ�*/
    pucSendBuff += IP_ETHERNET_HEAD_LEN;

    pstDhcpReplyIpv6Hdr     = (NDIS_IP6_HDR_STRU*)(pucSendBuff);
    pstDhcpReplyUdpHdr      = (UDP_HEAD_ST*)(pstDhcpReplyIpv6Hdr + 1);
    pDhcpReplyDhcpHdrOffset = (VOS_UINT8 *)(pstDhcpReplyUdpHdr+1);

    /*=====================*//* ��� IP ͷ */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr,
                                  usReplyUdpDataLen, (VOS_UINT8 *)pstDhcpReplyIpv6Hdr, IP_HEAD_PROTOCOL_UDP);

    /*=====================*//* ��� UDP ͷ */
    (VOS_VOID)TTF_NDIS_InputUDPHead((VOS_UINT8 *)pstDhcpReplyUdpHdr,
                            IP_IPV6_DHCP6_UE_PORT,
                            IP_IPV6_DHCP6_PC_PORT,
                            usReplyUdpDataLen);

    /*=====================*//* ��� DHCP reply ͷ */
    (*pDhcpReplyDhcpHdrOffset) = IP_IPV6_DHCP6_TYPE_REPLY;
    pDhcpReplyDhcpHdrOffset   += 1;
    PS_MEM_CPY( pDhcpReplyDhcpHdrOffset,
                            ((pDhcpInfoReqData + IP_IPV6_HEAD_LEN) + IP_UDP_HEAD_LEN) + 1,
                            IP_IPV6_DHCP6_TRANS_ID_LEN );

    pDhcpReplyDhcpHdrOffset   += IP_IPV6_DHCP6_TRANS_ID_LEN;

    /*=====================*//* ��� DHCP ServerID option (DUID ʹ�õ����ַ�ʽ�� DUID-LL)*/
    stDhcpDuidLLOpt.usDhcpDuidType      = VOS_HTONS(IP_IPV6_DHCP_DUID_LL_OPT_TYPE);
    stDhcpDuidLLOpt.usDhcpDuidHWType    = VOS_HTONS(IP_IPV6_HW_TYPE);
    PS_MEM_CPY(stDhcpDuidLLOpt.aucLinkLayerAddr,
                            aucSrcMacAddr,
                            IP_IPV6_DHCP_OPT_LINKADDR_SIZE);

    (*(VOS_UINT16 *)pDhcpReplyDhcpHdrOffset) = VOS_HTONS(IP_IPV6_DHCP_OPT_SERVER_ID);
    pDhcpReplyDhcpHdrOffset   += sizeof(VOS_UINT16);
    (*(VOS_UINT16 *)pDhcpReplyDhcpHdrOffset) = VOS_HTONS(IP_IPV6_DHCP_DUID_LL_OPT_LEN);
    pDhcpReplyDhcpHdrOffset   += sizeof(VOS_UINT16);
    PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)(&stDhcpDuidLLOpt),
                            IP_IPV6_DHCP_DUID_LL_OPT_LEN);

    pDhcpReplyDhcpHdrOffset   += IP_IPV6_DHCP_DUID_LL_OPT_LEN;


    /*=====================*//* ��� DHCP CLient ID option */
    if ( VOS_NULL_PTR != pstDhcpClientIdOpt )
    {
        PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)pstDhcpClientIdOpt,
                            (VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen) + 4));
        pDhcpReplyDhcpHdrOffset += (VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen) + 4);
    }

    /*=====================*//* ��� DHCP DNS OPTION */
    if ( 0 != usDhcpRequestDnsOptLen )
    {
        stIpv6DhcpDnsOpt.usOptionCode = VOS_HTONS(IP_IPV6_DHCP6_OPT_DNS_SERVERS);
        PS_MEM_CPY(&stIpv6DhcpDnsOpt.astIpv6DNS[0],
                            pstDnsSer->aucPriDnsServer,
                            (sizeof(NDIS_IP6_ADDR_STRU)));

        if (IP_IPV6_MAX_DNS_NUM == usDnsOptLen)
        {
            PS_MEM_CPY(&stIpv6DhcpDnsOpt.astIpv6DNS[1],
                                pstDnsSer->aucSecDnsServer,
                                (sizeof(NDIS_IP6_ADDR_STRU)));
        }
        stIpv6DhcpDnsOpt.usOptionLen  = VOS_HTONS((VOS_UINT16)(IP_IPV6_ADDR_LEN * usDnsOptLen)) ;
        PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)&stIpv6DhcpDnsOpt,
                            (4 + (usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU))));

        pDhcpReplyDhcpHdrOffset += (4 + (usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU)));

    }

    pstDhcpReplyUdpHdr->usCheck = TTF_NDIS_Ipv6_CalcCheckSum( (VOS_UINT8 *)pstDhcpReplyUdpHdr,
                            usReplyUdpDataLen,
                            &pstDhcpReplyIpv6Hdr->stSrc,
                            &pstDhcpReplyIpv6Hdr->stDst,
                            IP_HEAD_PROTOCOL_UDP);

    /*ָ����̫���ײ�*/
    pucSendBuff -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucSendBuff);

    usDhcpReplyPktLen += IP_ETHERNET_HEAD_LEN;

    IP_NDSERVER_AddTransDhcpv6PktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    ucEpsId = IP_NDSERVER_ADDRINFO_GET_EPSID(ulIndex);

    /* ��DHCPV6 REPLY��Ϣ���͵�PC */
    return Ndis_SendMacFrm(pucSendBuff, usDhcpReplyPktLen, ucEpsId);
}
/*lint +e778*/
/*lint +e572*/

/*****************************************************************************
 Function Name   : NdSer_DhcpV6PktProc
 Description     : ����DHCPV6����
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435          2011-12-6  Draft Enact
    2.h00218138          2013-1-15  DSDA

*****************************************************************************/
VOS_VOID NdSer_DhcpV6PktProc(VOS_VOID *pRcvMsg)
{
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                          *pucUdpData;

    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT32                          ulIndex         = IP_NULL;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    ND_IP_IPV6_DNS_SER_STRU            *pstDnsSer;
    VOS_UINT8                           ucExRabId;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc is entered.");

    ulDataLen = IMM_ZcGetUsedLen(pstAdsNdisMsg->pstSkBuff);
    pucData   = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, IMM_ZcGetDataPtr return NULL!");
        return;
    }

    ucExRabId = ND_FORM_EXEPSID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);

    if (IP_SUCC != ND_CheckEpsIdValid(ucExRabId))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, ucRabId is Invalid!", ucExRabId);
        return;
    }

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID,"NdSer_DhcpV6PktProc: Invalid Input:", ucExRabId, ulIndex);
        return;
    }

    IP_NDSERVER_AddRcvDHCPV6PktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucUdpData  = pucData + IP_IPV6_HEAD_LEN;
    usSrcPort   = *(VOS_UINT16 *)(VOS_VOID*)pucUdpData;
    usDstPort   = *(VOS_UINT16 *)(VOS_VOID*)(pucUdpData + 2);

    if ( (IP_IPV6_DHCP6_PC_PORT != VOS_NTOHS(usSrcPort)) || (IP_IPV6_DHCP6_UE_PORT != VOS_NTOHS(usDstPort)) )
    {
        /*PS_LOG2(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "NdSer_DhcpV6PktProc, WARNING, usSrcPort<1>, usDstPort<2> is err.",
            usSrcPort, usDstPort);*/
        IP_NDSERVER_AddErrDhcpv6PktNum(ulIndex);
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, usSrcPort, usDstPort is err!", usSrcPort, usDstPort);
        return;
    }

    ucMsgType   = *(pucUdpData + IP_UDP_HEAD_LEN);
    if ( IP_IPV6_DHCP6_INFOR_REQ != ucMsgType )
    {
        /*PS_LOG1(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_INFO,
            "NdSer_DhcpV6PktProc, WARNING, ucMsgType<1> is err.",
            ucMsgType);*/
        IP_NDSERVER_AddErrDhcpv6PktNum(ulIndex);
        IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, ucMsgType is err!", ucMsgType);
        return;
    }

    pstDnsSer = &(pstInfoAddr->stIpv6NwPara.stDnsSer);

    /* Nd Serverû��DNS������յ�Dhcpv6 information request,�����ñ��� */
    if ( 0 == pstDnsSer->ucDnsSerNum )
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_INFO,
            "NDIS, TTF_NDIS_Ipv6RouterLanEthInputDhcp6InfoReq, WARNING, No DNS information exists");*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, No DNS information exists");
        return;
    }

    (VOS_VOID)IP_NDSERVER_SendDhcp6Reply(ulIndex, pstDnsSer, pucData, (VOS_UINT16)ulDataLen);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgNsExp
 Description    : �����ھ�����󣬵ȴ��ھӹ��泬ʱ
 Input          : pMsg -------- ��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp is entered.");

    /* ����Ϣ��ȡ��ND SERVER���� */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp: ND Server state err!");
        return ;
    }

    /* �ж���ʱ�����Ƿ�С�ڹ涨��ʱ���� */
    if (pstInfoAddr->stTimerInfo.ucLoopTimes < g_ulNsTimerMaxExpNum)
    {
        /* ����NS��Ϣ��PC */
        if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp:Send NS Msg failed.");
        }

        /* ����ʱ����ʱ������1 */
        pstInfoAddr->stTimerInfo.ucLoopTimes++;

        /* �����ھ�����ʱ�� */
        IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);
    }
    else
    {
        /* �����ʱ����Ϣ */
        pstInfoAddr->stTimerInfo.ucLoopTimes = 0;

        /* ���δ���״̬��TE��ַ����Ӧ��ַ�������������TE��ַ���ط�RA */
        if (IP_NDSERVER_TE_ADDR_INCOMPLETE == pstInfoAddr->stTeAddrInfo.enTeAddrState)
        {
            pstInfoAddr->stTeAddrInfo.enTeAddrState = IP_NDSERVER_TE_ADDR_INEXISTENT;

            /* ����RA��Ϣ��PC */
            if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
            {
                IP_NDSERVER_AddTransPktFailNum(ulIndex);
                IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp:Send RA Msg failed.");
            }

            /* ����·�ɹ��涨ʱ�� */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);

            IP_NDSERVER_ClearDlPktQue(ulIndex);          /*������л�������е�PKT*/
        }
        else
        {
            /* �����������ھ�����ʱ�� */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_PERIODIC_NS);
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgPeriodicNsExp
 Description    : �������ھ�����ʱ
 Input          : pMsg -------- ��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgPeriodicNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* ��ӡ����ú��� */
    IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp is entered.");

    /* ����Ϣ��ȡ��ND SERVER���� */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp: ND Server state err!");
        return ;
    }

    /* ���������Է���RA��ʱ����ֹRouter���� */
    if (0 == g_aulPeriodicRaTimeCnt[ulIndex]--)
    {
        g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;;

        /* ����RA��Ϣ��PC */
        if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp:Send RA Msg failed.");
        }
    }

    /* ����NS��Ϣ��PC */
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp:Send NS Msg failed.");
    }

    /* �����ʱ����Ϣ */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* �����ھ�����ʱ�� */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgPeriodicNsExp
 Description    : �յ��ظ���ַ����ȴ���ʱ����ʱ
 Input          : pMsg -------- ��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgFirstNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp is entered.");

    /* ����Ϣ��ȡ��ND SERVER���� */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp: ND Server state err!");
        return ;
    }

    /* ����NS��Ϣ��PC */
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp:Send NS Msg failed.");
    }

    /* �����ʱ����Ϣ */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* �����ھ�����ʱ�� */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgRaExp
 Description    : �յ��ظ���ַ���ǰ���ڷ���·�ɹ��泬ʱ
 Input          : pMsg -------- ��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgRaExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_UINT8                          *pucData;
    VOS_INT32                           lLockKey;
    /* ��ӡ����ú��� */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp is entered.");

    /* ����Ϣ��ȡ��ND SERVER���� */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp: ND Server state err!");
        return ;
    }

    /* ����RA��Ϣ��PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp:Send RA Msg failed.");
    }

    /* �����ʱ����Ϣ */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* ����·�ɹ��涨ʱ�� */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);

    /************ ����IP����Ŀ�ĵ�ַ��ΪNS����Ŀ���ַ�����е�ַ���� **********/
    /* send NS for Address Resolution */
    lLockKey = VOS_SplIMP();
    if (PS_SUCC != LUP_PeekQueHead(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
    {
        VOS_Splx(lLockKey);
        return;
    }
    VOS_Splx(lLockKey);

    pucData   = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp, IMM_ZcGetDataPtr return NULL");
        return;
    }

    /*�õ�Ŀ��IPV6��ַ������NS����*/
    IP_MEM_CPY(aucDstIPAddr, pucData + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, aucDstIPAddr))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp, IP_NDSERVER_SendNsMsg return NULL");
        return;
    }

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerMsgDistr
 Description    : ND SERVER TIMER��Ϣ�ַ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : NDSER_TIMER_ENUM_UINT32

 History        :
      1.sunli 00180715     2011-04-02  Draft Enact
*****************************************************************************/
NDSER_TIMER_ENUM_UINT32 IP_NDSERVER_TimerMsgDistr(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulIndex         = IP_NULL;
    NDSER_TIMER_ENUM_UINT32             enTimerType     = IP_ND_SERVER_TIMER_BUTT;
    IP_TIMER_STRU                      *pstTimerInfo    = VOS_NULL_PTR;

    /* ����Ϣ��ȡ��ulIndex��enTimerType */
    ulIndex = IP_GetTimerPara(pRcvMsg);
    enTimerType = (NDSER_TIMER_ENUM_UINT32)IP_GetTimerName(pRcvMsg);

    /* �жϺϷ��� */
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Invalid Timer Name or Para !");
        return IP_MSG_DISCARD;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Get Timer failed.");
        return IP_MSG_DISCARD;
    }

    /* �ж���Ϣ�����붨ʱ�������Ƿ�һ�� */
    if(enTimerType != pstTimerInfo->ulName)
    {
        /*��ӡ�쳣��Ϣ*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: TimerType not match:", enTimerType, pstTimerInfo->ulName);
        return IP_MSG_DISCARD;
    }

    /*��ʱ����ʱ����*/
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
            IP_NDSERVER_ProcTimerMsgNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IP_NDSERVER_ProcTimerMsgPeriodicNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IP_NDSERVER_ProcTimerMsgFirstNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IP_NDSERVER_ProcTimerMsgRaExp(pRcvMsg);
            break;
        default:
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Illegal Timer Type!");
            break;
    }

    return IP_MSG_HANDLED;
}

/*****************************************************************************
 �� �� ��  : APP_NdServer_PidMsgProc
 ��������  : PP NDIS����PID��Ϣ������
 �������  : MsgBlock* pMsgBlock
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��9��
    ��    ��   : h00159435
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID APP_NdServer_PidMsgProc(const MsgBlock *pRcvMsg)
{
    if (VOS_NULL_PTR == pRcvMsg)
    {
        vos_printf("Error:APP_Ndis_DLPidMsgProc Parameter pRcvMsg is NULL!");
        return ;
    }
    switch (pRcvMsg->ulSenderPid)
    {
        case DOPRA_PID_TIMER:
            (VOS_VOID)IP_NDSERVER_TimerMsgDistr(pRcvMsg);
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_CmdHelp
 Description     : IP NDSERVERģ��������ʾ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact
*****************************************************************************/
VOS_VOID  IP_NDSERVER_CmdHelp( VOS_VOID )
{
    vos_printf("\r\n");
    vos_printf("********************** IP NDSERVER ��������б� *********************\r\n");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowLocalNwParamInfo","��ʾ���ر�������������Ϣ");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowAddrInfo(index)","��ʾĳʵ���ַ������Ϣ(0)");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowStatInfo(index)","��ʾĳʵ�屨��ͳ����Ϣ(0)");
    vos_printf("*******************************************************************\r\n");
    vos_printf("\r\n");

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowLocalNwParamInfo
 Description     : ��ʾ���ر�������������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowLocalNwParamInfo( VOS_VOID )
{
    vos_printf("************************���ر�������������Ϣ***********************\r\n");
    vos_printf("�����ַ���ñ�ʶ: %d\r\n",g_ucMFlag);
    vos_printf("������״̬���ñ�ʶ: %d\r\n",g_ucOFlag);
    vos_printf("·����������(��): %d\r\n",g_usRouterLifetime);
    vos_printf("�ɴ�ʱ��(����): %d\r\n",g_ulReachableTime);
    vos_printf("�ط���ʱ��(����): %d\r\n",g_ulRetransTimer);
    vos_printf("�ھ�����ʱ��ʱ��(����): %d\r\n",g_ulNsTimerLen);
    vos_printf("�ھ��������ʱ����: %d\r\n",g_ulNsTimerMaxExpNum);
    vos_printf("�������ھ�����ʱ��ʱ��(����): %d\r\n",g_ulPeriodicNsTimerLen);
    vos_printf("������·�ɹ��涨ʱ��ʱ��(����): %d\r\n",g_ulPeriodicRaTimerLen);
    vos_printf("�յ��ظ���ַ����ȴ��Ķ�ʱ��ʱ��(����): %d\r\n",g_ulFirstNsTimerLen);
    vos_printf("�յ��ظ���ַ���ǰ·�ɹ��涨ʱ��ʱ��(����): %d\r\n",g_ulRaTimerLen);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowAddrInfo
 Description     : ��ʾĳʵ���ַ������Ϣ
 Input           : ulIndex --- ʵ������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowAddrInfo( VOS_UINT32 ulIndex )
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;
    VOS_UINT32                          ulCnt       = IP_NULL;
    VOS_UINT32                          ulTmp       = IP_NULL;

    if (ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        ulTmp = IP_NDSERVER_ADDRINFO_MAX_NUM;
        vos_printf("IP_NDSERVER_ShowAddrInfo:��������ķ�Χ:0-%d\r\n", ulTmp-1);
        return ;
    }

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    vos_printf("**************************ND SERVERʵ����Ϣ(%d)*************************\r\n", ulIndex);
    vos_printf("��Ч��־: %d\r\n",pstInfoAddr->ucValidFlag);
    vos_printf("���غ�: %d\r\n",pstInfoAddr->ucEpsbId);

    vos_printf("************�������ò���************\r\n");
    vos_printf("MTU: %d\r\n",pstInfoAddr->stIpv6NwPara.ulBitOpMtu?pstInfoAddr->stIpv6NwPara.ulMtu:0);
    vos_printf("��ǰ������: %d\r\n",pstInfoAddr->stIpv6NwPara.ucCurHopLimit);
    vos_printf("�ӿ�ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[0],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[1],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[2],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[3],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[4],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[5],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[6],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[7]);

    vos_printf("************ǰ׺�б�************\r\n");
    vos_printf("ǰ׺����: %d\r\n",pstInfoAddr->stIpv6NwPara.ulPrefixNum);
    for (ulCnt = 0; ulCnt < pstInfoAddr->stIpv6NwPara.ulPrefixNum; ulCnt++)
    {
        vos_printf("ǰ׺����: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitPrefixLen);
        vos_printf("���α�־: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitA);
        vos_printf("��·�ϱ�־: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitL);
        vos_printf("��Ч������: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulValidLifeTime);
        vos_printf("ѡ��������: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulPreferredLifeTime);
        vos_printf("ǰ׺: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[0],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[1],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[2],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[3],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[4],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[5],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[6],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[7],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[8],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[9],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[10],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[11],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[12],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[13],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[14],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[15]);
    }

    vos_printf("************DNS SERVER�б�************\r\n");
    vos_printf("DNS SERVER����: %d\r\n",pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum);
    if (pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum >= 1)
    {
        vos_printf("Prime DNS SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[0],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[1],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[2],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[3],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[4],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[5],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[6],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[7],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[8],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[9],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[10],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[11],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[12],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[13],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[14],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[15]);
    }
    if (pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum >= 2)
    {
        vos_printf("Second DNS SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[0],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[1],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[2],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[3],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[4],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[5],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[6],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[7],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[8],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[9],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[10],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[11],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[12],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[13],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[14],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[15]);
    }
    vos_printf("************SIP SERVER�б�************\r\n");
    vos_printf("SIP SERVER����: %d\r\n",pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum);
    if (pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum >= 1)
    {
        vos_printf("Prime SIP SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[0],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[1],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[2],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[3],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[4],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[5],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[6],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[7],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[8],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[9],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[10],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[11],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[12],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[13],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[14],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[15]);
    }
    if (pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum >= 2)
    {
        vos_printf("Second SIP SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[0],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[1],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[2],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[3],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[4],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[5],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[6],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[7],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[8],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[9],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[10],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[11],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[12],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[13],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[14],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[15]);
    }

    vos_printf("************TE��ַ��Ϣ************\r\n");
    vos_printf("TE��ַ״̬: %d\r\n",pstInfoAddr->stTeAddrInfo.enTeAddrState);
    vos_printf("ȫ���ַ: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[5],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[6],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[7],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[8],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[9],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[10],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[11],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[12],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[13],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[14],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[15]);
    vos_printf("��·���ַ: %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[5]);
    vos_printf("��·���ص�ַ: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[5],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[6],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[7],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[8],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[9],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[10],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[11],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[12],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[13],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[14],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[15]);

    vos_printf("************��ʱ��״̬************\r\n");
    vos_printf("ϵͳ��ʱ����ַ: %p\r\n",pstInfoAddr->stTimerInfo.hTm);
    vos_printf("��ʱ������: %d\r\n",pstInfoAddr->stTimerInfo.ulName);
    vos_printf("��ʱ����ʱ����: %d\r\n",pstInfoAddr->stTimerInfo.ucLoopTimes);
    vos_printf("������·�ɹ���ʱ�����: %d\r\n",g_aulPeriodicRaTimeCnt[ulIndex]);

    vos_printf("************�������Ϣ************\r\n");
    vos_printf("����౾����·��ַ: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->aucUeLinkLocalAddr[0],
                                pstInfoAddr->aucUeLinkLocalAddr[1],
                                pstInfoAddr->aucUeLinkLocalAddr[2],
                                pstInfoAddr->aucUeLinkLocalAddr[3],
                                pstInfoAddr->aucUeLinkLocalAddr[4],
                                pstInfoAddr->aucUeLinkLocalAddr[5],
                                pstInfoAddr->aucUeLinkLocalAddr[6],
                                pstInfoAddr->aucUeLinkLocalAddr[7],
                                pstInfoAddr->aucUeLinkLocalAddr[8],
                                pstInfoAddr->aucUeLinkLocalAddr[9],
                                pstInfoAddr->aucUeLinkLocalAddr[10],
                                pstInfoAddr->aucUeLinkLocalAddr[11],
                                pstInfoAddr->aucUeLinkLocalAddr[12],
                                pstInfoAddr->aucUeLinkLocalAddr[13],
                                pstInfoAddr->aucUeLinkLocalAddr[14],
                                pstInfoAddr->aucUeLinkLocalAddr[15]);
    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowStatInfo
 Description     : ��ʾ����ͳ����Ϣ
 Input           : ulIndex --- ʵ������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowStatInfo( VOS_UINT32 ulIndex )
{
    IP_NDSERVER_PACKET_STATISTICS_INFO_STRU    *pstPktStatInfo = IP_NULL_PTR;
    VOS_UINT32                                  ulTmp          = IP_NULL;

    if (ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        ulTmp = IP_NDSERVER_ADDRINFO_MAX_NUM;
        vos_printf("IP_NDSERVER_ShowStatInfo:��������ķ�Χ:0-%d\r\n", ulTmp-1);
        return ;
    }

    pstPktStatInfo = IP_NDSERVER_GET_STATINFO_ADDR(ulIndex);

    vos_printf("****************************����ͳ����Ϣ(%d)****************************\r\n", ulIndex);
    vos_printf("�յ���������:           %d\r\n", pstPktStatInfo->ulRcvPktTotalNum);
    vos_printf("����������:             %d\r\n", pstPktStatInfo->ulDiscPktNum);
    vos_printf("�յ�NS������:           %d\r\n", pstPktStatInfo->ulRcvNsPktNum);
    vos_printf("�յ�NA������:           %d\r\n", pstPktStatInfo->ulRcvNaPktNum);
    vos_printf("�յ�RS������:           %d\r\n", pstPktStatInfo->ulRcvRsPktNum);
    vos_printf("�յ�ECHO REQ������:     %d\r\n", pstPktStatInfo->ulRcvEchoPktNum);
    vos_printf("�յ�IPV6����������:     %d\r\n", pstPktStatInfo->ulRcvTooBigPktNum);
    vos_printf("�յ�DHCPV6������:       %d\r\n", pstPktStatInfo->ulRcvDhcpv6PktNum);
    vos_printf("�յ�����NS������:       %d\r\n", pstPktStatInfo->ulErrNsPktNum);
    vos_printf("�յ�����NA������:       %d\r\n", pstPktStatInfo->ulErrNaPktNum);
    vos_printf("�յ�����RS������:       %d\r\n", pstPktStatInfo->ulErrRsPktNum);
    vos_printf("�յ�����ECHO REQ������: %d\r\n", pstPktStatInfo->ulErrEchoPktNum);
    vos_printf("�յ�����IPV6����������: %d\r\n", pstPktStatInfo->ulErrTooBigPktNum);
    vos_printf("�յ�����DHCPV6������:   %d\r\n", pstPktStatInfo->ulErrDhcpv6PktNum);
    vos_printf("���ͱ�������:           %d\r\n", pstPktStatInfo->ulTransPktTotalNum);
    vos_printf("���ͱ���ʧ����:         %d\r\n", pstPktStatInfo->ulTransPktFailNum);
    vos_printf("����NS������:           %d\r\n", pstPktStatInfo->ulTransNsPktNum);
    vos_printf("����NA������:           %d\r\n", pstPktStatInfo->ulTransNaPktNum);
    vos_printf("����RA������:           %d\r\n", pstPktStatInfo->ulTransRaPktNum);
    vos_printf("����ECHO REPLY������:   %d\r\n", pstPktStatInfo->ulTransEchoPktNum);
    vos_printf("���ͳ�������Ӧ������:   %d\r\n", pstPktStatInfo->ulTransTooBigPktNum);
    vos_printf("����DHCPV6 REPLY������: %d\r\n", pstPktStatInfo->ulTransDhcpv6PktNum);
    vos_printf("����IP������ʱPC MAC��ַ��Ч��ͳ����: %d\r\n", pstPktStatInfo->ulMacInvalidPktNum);
    vos_printf("���гɹ������IP������:               %d\r\n", pstPktStatInfo->ulEnquePktNum);
    vos_printf("���гɹ����ͻ����IP������:           %d\r\n", pstPktStatInfo->ulSendQuePktNum);

    return;
}



