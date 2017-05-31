

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsCtx.h"
#include "AdsLog.h"
#include "AdsFilter.h"
/* Modified by m00217266 for L-C��������Ŀ, 2014-2-11, begin */
#include "AdsInterface.h"
/* Modified by m00217266 for L-C��������Ŀ, 2014-2-11, end */
#include "NVIM_Interface.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_FILTER_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ADS���˹��������� */
ADS_FILTER_CTX_STRU                     g_stAdsFilterCtx;

/* ADS���˹���ͳ����Ϣ: �����и�Ԫ���������ͳ������������:
   ��������        ͳ����
      0         ����IPv4 TCP
      1         ����IPv4 UDP
      2         ����IPv4 ECHO REQ
      3         ���в�֧�ֵ�IPv4����
      4         ����IPv6����
      5         ����IPv4 TCP
      6         ����IPv4 UDP
      7         ����IPv4 ECHO REPLY
      8         ����IPv4 ICMP�����
      9         ����IPv4 ��Ƭ��(��Ƭ)
      10        ����IPv4 ��Ƭ��(����Ƭ)
      11        ����IPv6�� */
VOS_UINT32                              g_aulAdsFilterStats[ADS_FILTER_ORIG_PKT_BUTT]  = {0};

/* ADS��������ICMP�������õĺ���ָ��ṹ�壬��ǰֻ֧��Echo Reply��ICMP����� */
ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU     g_astAdsFilterDecodeDlIcmpFuncTbl[] =
    {         /*ICMP Type*/                            /* pFunc */                               /* enOrigPktType */
        /*  0:Echo Reply              */   {ADS_FILTER_DecodeDlIPv4EchoReplyPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY},
        /*  1:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  2:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  3:Destination Unreachable */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  4:Source Quench           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  5:Redirect (change route) */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  6:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  7:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  8:Echo Request            */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  9:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 10:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 11:Time Exceeded           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /* 12:Parameter Problem       */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /* 13:Timestamp Request       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 14:Timestamp Reply         */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 15:Information Request     */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 16:Information Reply       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 17:Address Mask Request    */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 18:Address Mask Reply      */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             }
    };


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : ADS_FILTER_ResetIPv6Addr
 ��������  : ���ù��˵�IPv6��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetIPv6Addr(VOS_VOID)
{
    PS_MEM_SET(ADS_FILTER_GET_IPV6_ADDR(), 0, sizeof(ADS_IPV6_ADDR_UN));

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_InitListsHead
 ��������  : ��ʼ��ADS�������ݹ��˱�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_InitListsHead(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;

    /* ѭ����ʼ��ÿһ�����˱��ͷ�ڵ� */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);

        /*lint -e717*/
        HI_INIT_LIST_HEAD(pstListHead);
        /*lint -e717*/
    }
    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_InitCtx
 ��������  : ��ʼ��ADS������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : �������warning
*****************************************************************************/
VOS_VOID ADS_FILTER_InitCtx(VOS_VOID)
{
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdp;
    VOS_UINT32                          ulTimeLen;

    PS_MEM_SET(&g_stAdsFilterCtx, 0, sizeof(g_stAdsFilterCtx));

    /* ��ʼ�����˱�ͷ�ڵ� */
    ADS_FILTER_InitListsHead();

    /* ��ʼ���ϻ����� */
    /* ��ȡNV���ȡ���˽ڵ��ϻ�ʱ�� */
    PS_MEM_SET(&stSharePdp, 0, sizeof(stSharePdp));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_SHARE_PDP_INFO,
                           &stSharePdp,
                           sizeof(stSharePdp)))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_DL, "ADS_FILTER_InitCtx: NV Read Failed!");
        stSharePdp.usAgingTimeLen = ADS_FILTER_DEFAULT_AGING_TIMELEN;
    }

    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * stSharePdp.usAgingTimeLen;
    ADS_FILTER_SET_AGING_TIME_LEN(ulTimeLen);

    /* ��ʼ��IPv6���˵�ַ */
    ADS_FILTER_ResetIPv6Addr();

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_HeapAlloc
 ��������  : ADS������ϵͳ�ڴ����뺯��
 �������  : VOS_UINT32 ulSize  -- �����ڴ��С
 �������  : ��
 �� �� ֵ  : VOS_VOID*          -- �����ڴ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID* ADS_FILTER_HeapAlloc(VOS_UINT32 ulSize)
{
    VOS_VOID                           *ret = VOS_NULL_PTR;

    if ((ulSize == 0) || (ulSize > 1024))
    {
        return VOS_NULL_PTR;
    }

    ret = (VOS_VOID *)kmalloc(ulSize, GFP_KERNEL);

    return ret;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_HeapFree
 ��������  : ADS������ϵͳ�ڴ��ͷź���
 �������  : VOS_VOID *pAddr    -- ��Ҫ�ͷŵ��ڴ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_HeapFree(VOS_VOID *pAddr)
{
    if (pAddr == NULL)
    {
        return;
    }

    kfree(pAddr);

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_AddFilter
 ��������  : ���ӹ����������˱�
 �������  : ADS_FILTER_IPV4_INFO_STRU *pstFilter   -- �����Ĺ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_AddFilter(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* ������˱�ڵ��ڴ� */
    pstNode = (ADS_FILTER_NODE_STRU *)ADS_FILTER_MALLOC(sizeof(ADS_FILTER_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_FILTER_AddFilter: Malloc Failed!");
        return;
    }

    pstNode->stFilter = *pstFilter;

    /* ��ȡ��ʾ��Ϣ��Ӧ�Ĺ��˱������� */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /* ͨ�������Ż�ȡ��Ӧ���������ͷ��� */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /* ���ڵ����ӵ����˱������� */
    msp_list_add_tail(&pstNode->stList, pstListHead);

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ResetLists
 ��������  : ����ADS�������ݹ��˱�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetLists(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;

    /* ѭ���������й��˱����ͷŹ��˱�����нڵ� */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);
        msp_list_for_each_safe(pstMe, pstTmp, pstListHead)
        {
            pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

            /* �ӹ��˱���ɾ���ڵ� */
            msp_list_del(&pstNode->stList);

            /* �ͷŽڵ��ڴ� */
            ADS_FILTER_FREE(pstNode);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_Reset
 ��������  : ���ù�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_Reset(VOS_VOID)
{
    /* ����IPv6���˵�ַ */
    ADS_FILTER_ResetIPv6Addr();

    /* ���ù��˱� */
    ADS_FILTER_ResetLists();

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_Match
 ��������  : �ڹ��˱�ƥ���ʾ��Ϣ����ƥ�佫ˢ���ϻ�����
 �������  : HI_LIST_S                 *pstListHead     -- ���˱��׽ڵ�
             ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- ����ƥ��ı�ʾ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- ������Ϣƥ��
             VOS_FALSE  -- ������Ϣ��ƥ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_IsInfoMatch(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter1,
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter2)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_FALSE;

    /* ƥ��Դ��ַ��Ŀ�ĵ�ַ��Э������ */
    if ( !ADS_FILTER_IS_IPHDR_MATCH(&pstFilter1->stIPHeader, &pstFilter2->stIPHeader) )
    {
        return ulRet;
    }

    /* ���ձ������ͽ���ƥ�� */
    switch(pstFilter1->enPktType)
    {
        case ADS_FILTER_PKT_TYPE_TCP:
            /* ����TCP���ͽ���ƥ�� */
            if (ADS_FILTER_IS_TCP_PKT_MATCH(&pstFilter1->unFilter.stTcpFilter,
                                            &pstFilter2->unFilter.stTcpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_UDP:
            /* ����UDP���ͽ���ƥ�� */
            if (ADS_FILTER_IS_UDP_PKT_MATCH(&pstFilter1->unFilter.stUdpFilter,
                                            &pstFilter2->unFilter.stUdpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_ICMP:
            /* ����ICMP���ͽ���ƥ�� */
            if (ADS_FILTER_IS_ICMP_PKT_MATCH(&pstFilter1->unFilter.stIcmpFilter,
                                             &pstFilter2->unFilter.stIcmpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_FRAGMENT:
            /* ���շ�Ƭ�����ͽ���ƥ�� */
            if (ADS_FILTER_IS_FRAGMENT_MATCH(&pstFilter1->unFilter.stFragmentFilter,
                                             &pstFilter2->unFilter.stFragmentFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_Match
 ��������  : �ڹ��˱�ƥ���ʾ��Ϣ����ƥ�佫ˢ���ϻ�����
 �������  : ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- ����ƥ��ı�ʾ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- ������Ϣƥ��
             VOS_FALSE  -- ������Ϣ��ƥ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_Match(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListTmp  = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ulRet   = VOS_FALSE;

    /* ��ȡ��ʾ��Ϣ��Ӧ�Ĺ��˱������� */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /* ͨ�������Ż�ȡ��Ӧ���������ͷ��� */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /* ѭ��������������ƥ���� */
    msp_list_for_each_safe(pstMe, pstListTmp, pstListHead)
    {
        pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

        /* �жϽڵ��Ƿ���� */
        if (ADS_FILTER_IS_AGED(pstNode->stFilter.ulTmrCnt))
        {
            /* �������в���ýڵ� */
            msp_list_del(&pstNode->stList);

            /* �ͷŽڵ��ڴ� */
            ADS_FILTER_FREE(pstNode);

            continue;
        }

        /* �жϱ��������Ƿ�ƥ�� */
        if ( (pstFilter->enPktType != pstNode->stFilter.enPktType)
          || (VOS_TRUE == ulRet) )
        {
            /* �����Ͳ�ƥ����Ѿ��ҵ�ƥ���������������һ���ڵ� */
            continue;
        }

        /* ���Ĺ�����Ϣƥ�� */
        ulRet = ADS_FILTER_IsInfoMatch(pstFilter, &pstNode->stFilter);

        /* ������Ϣƥ�䣬ˢ���ϻ�ʱ�� */
        if (VOS_TRUE == ulRet)
        {
            pstNode->stFilter.ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
        }
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_SaveIPAddrInfo
 ��������  : ����IP���˵�ַ��Ϣ
 �������  : ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr    -- IP��ַ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_SaveIPAddrInfo(
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr)
{
    /* IPv6���ͣ�����Ҫ��IPv6��ַ���浽ȫ�ֹ�����Ϣ�� */
    if (VOS_TRUE == pstFilterIpAddr->bitOpIpv6Addr)
    {
        PS_MEM_CPY(ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr,
                   pstFilterIpAddr->aucIpv6Addr,
                   ADS_IPV6_ADDR_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeUlPacket
 ��������  : ADS�������������ݰ����룬ֻ֧��TCP\UDP\ICMP
 �������  : IMM_ZC_STRU                *pstData       -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU  *pstIPv4Filter -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_OK     -- �������ݰ�����ɹ�
             VOS_ERR    -- �������ݰ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* ����IP�ײ� */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* ��Ƭ���ķ���Ƭ����ֱ�ӷ��ͣ�����Ҫ���й�����Ϣ��ȡ���������б���������(��Ƭ������Ƭ�жϷ���: OffsetΪ��0):
                         MF      Offset
        �Ƿ�Ƭ��         0         0
        ��Ƭ����Ƭ       1         0
        ��Ƭ���м�Ƭ     1         ��0
        ��Ƭ��βƬ       0         ��0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /* ��ά�ɲ�ͳ�� */
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT, 1);
        return VOS_ERR;
    }


    /* ��ȡ��ǰϵͳʱ�� */
    pstIPv4Filter->ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();

    pstIPv4Filter->stIPHeader.ulSrcAddr     = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr     = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol    = pstIPv4Hdr->ucProtocol;

    /* �жϱ��������Ƿ�ΪTCP\UDP\ICMP��ע��:��Ƭ����ƬΪTCP��UDP��ͳһ����TCP/UDP�����ͽ��д��� */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            /* Ŀǰ����ֻ֧��PING ECHO REQ����ICMP���ģ����յ���������ICMP���ģ��������˴���ֱ�ӷ��� */
            if (ADS_ICMP_ECHOREQUEST != pstIcmpHdr->ucType)
            {
                /* ��������ICMP���ģ���������ά�ɲ�ͳ�� */
                ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
                return VOS_ERR;
            }

            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
            pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
            pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum     = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

            /* ��ά�ɲ�ͳ�� */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ, 1);
            return VOS_OK;

        case ADS_IPPROTO_TCP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
            pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;

            /* ��ά�ɲ�ͳ�� */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP, 1);
            return VOS_OK;

        case ADS_IPPROTO_UDP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
            pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;

            /* ��ά�ɲ�ͳ�� */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP, 1);
            return VOS_OK;

        default:
            /* ��֧�ֵ�IPv4���������� */
            /* ��ά�ɲ�ͳ�� */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
            break;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ProcUlPacket
 ��������  : ADS�������������ݰ�����
 �������  : IMM_ZC_STRU               *pstData     -- �������ݰ�
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- �������ݰ�IP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ProcUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    PS_MEM_SET(&stIPv4Filter, 0 ,sizeof(stIPv4Filter));

    /* ������IPv4�������ݰ���IPv6����ֱ�ӷ��� */
    if (ADS_PKT_TYPE_IPV4 != enIpType)
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT, 1);
        return;
    }

    /* �����������ݰ�������ȡ��Ӧ���������еĹ��˱�ʾ��Ϣ */
    ulDecodeRet = ADS_FILTER_DecodeUlPacket(pstData, &stIPv4Filter);
    if (VOS_OK != ulDecodeRet)
    {
        /* ����ʧ�ܻ�֧�ֵı������Ͳ����� */
        return;
    }

    /* �ڹ��˱���ƥ���ʾ��Ϣ */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE != ulRet)
    {
        /* ûƥ�䵽�ڵ㣬��IP��ʾ��Ϣ��ӵ����˱� */
        ADS_FILTER_AddFilter(&stIPv4Filter);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4NotFirstFragPacket
 ��������  : ���з�Ƭ����(����Ƭ)�Ĺ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    PS_MEM_SET(pstIPv4Filter, 0, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    /* ��ȡ��Ƭ��������Ϣ */
    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_FRAGMENT;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stFragmentFilter.usIdentification = pstIPv4Hdr->usIdentification;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4EchoReplyPacket
 ��������  : ����ECHO REPLY���ĵĹ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_OK     -- �������ݰ�����ɹ�
             VOS_ERR    -- �������ݰ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4EchoReplyPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* ��ȡICMP�����ײ� */
    pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
    pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4IcmpErrorPacket
 ��������  : ����ICMP����ĵĹ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_OK     -- �������ݰ�����ɹ�
             VOS_ERR    -- �������ݰ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4IcmpErrorPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIcmpIPv4Hdr  = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* ��ȡICMP������������ԭʼ���ݰ���IP�ײ�ָ�� */
    pstIcmpIPv4Hdr = (ADS_IPV4_HDR_STRU *)(((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN + ADS_FILTER_ICMP_HDR_LEN));

    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIcmpIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIcmpIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIcmpIPv4Hdr->ucProtocol;

    if (ADS_IPPROTO_TCP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
        pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;
    }
    else if (ADS_IPPROTO_UDP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
        pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;
    }
    else
    {
        /* ��TCP/UDP�����˳���ֱ�ӽ���HOST���� */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4TcpPacket
 ��������  : ����TCP���ĵĹ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4TcpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;

    /* ��ȡTCP�����ײ� */
    pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usDstPort;
    pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usSrcPort;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4UdpPacket
 ��������  : ����UDP���ĵĹ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4UdpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* ��ȡUDP�����ײ� */
    pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usDstPort;
    pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usSrcPort;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4FragPacket
 ��������  : ���з�Ƭ���ĵĹ�����Ϣ��ȡ
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- �������ݰ�ԭʼ����
 �� �� ֵ  : VOS_OK     -- �������ݰ�����ɹ�
             VOS_ERR    -- �������ݰ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��18��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4FragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    VOS_UINT32                          ulRet;

    /* �жϷ�Ƭ���Ƿ�Ϊ��Ƭ(��Ƭ�����Ƭ����������Offset�Ƿ�Ϊ0).
        �������б���������:
                         MF      Offset
        ��Ƭ����Ƭ       1         0
        ��Ƭ���м�Ƭ     1         ��0
        ��Ƭ��βƬ       0         ��0 */
    if (0 == (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /* ��Ƭ�Ĵ���(��ǰֻ֧��TCP��UDP����Э������) */
        switch (pstIPv4Hdr->ucProtocol)
        {
            case ADS_IPPROTO_TCP:
                /* ��¼����ԭʼ���� */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* ��ȡTCP���Ĺ�����Ϣ */
                ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            case ADS_IPPROTO_UDP:
                /* ��¼����ԭʼ���� */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* ��ȡUDP���Ĺ�����Ϣ */
                ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            default:
                /* �������ͱ��ģ�������ֱ�ӽ���HOST���� */
                ulRet = VOS_ERR;
                break;
        }
    }
    else
    {
        /* ����Ϊ"����Ƭ",��¼����ԭʼ���� */
        *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT;

        /* ��ȡ����Ƭ�Ĺ�����Ϣ */
        ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, pstIPv4Filter);

        ulRet = VOS_OK;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_DecodeDlIPv4Packet
 ��������  : �жϱ��������Ƿ�ΪTCP\UDP\ICMP(ECHO REPLY��ICMP�����)\��Ƭ������Ƭ��
             ����ȡ��Ӧ���������еĹ��˱�ʾ��Ϣ
             ע��: Դ��Ŀ���ǵ����ģ���Ϊ���˱���Ϣ�ǰ����з�������д��
 �������  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr,    -- �������ݰ�
 �������  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- ���˱�־�ṹ��ָ��
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- �������ݰ�ԭʼ����
 �� �� ֵ  : VOS_OK     -- �������ݰ�����ɹ�
             VOS_ERR    -- �������ݰ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��13��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4Packet(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    ADS_ICMP_HDR_STRU                                      *pstIcmpHdr           = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC                          pDecodeDlIcmpFunc    = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU                    *pDecodeDlIcmpFuncTbl = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet                = VOS_ERR;

    /* ����"��Ƭ��".�������б���������:
                         MF      Offset
        �Ƿ�Ƭ��         0         0
        ��Ƭ����Ƭ       1         0
        ��Ƭ���м�Ƭ     1         ��0
        ��Ƭ��βƬ       0         ��0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_MF | ADS_IP_OFFSET)))
    {
        return ADS_FILTER_DecodeDlIPv4FragPacket(pstIPv4Hdr, pstIPv4Filter, penOrigPktType);
    }

    /* ����TCP\UDP\ICMP(ECHO REPLY��ICMP�����) */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            if (pstIcmpHdr->ucType < ADS_FILTER_GET_DL_ICMP_FUNC_TBL_SIZE())
            {
                pDecodeDlIcmpFuncTbl = ADS_FILTER_GET_DL_ICMP_FUNC_TBL_ADDR(pstIcmpHdr->ucType);
                pDecodeDlIcmpFunc = pDecodeDlIcmpFuncTbl->pFunc;
                if (VOS_NULL_PTR != pDecodeDlIcmpFunc)
                {
                    /* ��¼����ԭʼ���� */
                    *penOrigPktType = pDecodeDlIcmpFuncTbl->enOrigPktType;

                    /* ��ȡICMP���Ĺ�����Ϣ */
                    ulRet = pDecodeDlIcmpFunc(pstIPv4Hdr, pstIPv4Filter);
                }
            }
            break;

        case ADS_IPPROTO_TCP:
            /* ��¼����ԭʼ���� */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_TCP;

            /* ��ȡTCP���Ĺ�����Ϣ */
            ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        case ADS_IPPROTO_UDP:
            /* ��¼����ԭʼ���� */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_UDP;

            /* ��ȡUDP���Ĺ�����Ϣ */
            ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ProcDlIPv4Packet
 ��������  : ADS���˴���IPv4�����������ݰ�����
 �������  : IMM_ZC_STRU               *pstData     -- �������ݰ�
 �������  : ��
 �� �� ֵ  : VOS_OK   -- ���ݰ��������
             VOS_ERR  -- ���ݰ�δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv4Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;
    ADS_FILTER_ORIG_PKT_ENUM_UINT32     enOrigPktType;

    /* ��ȡIPV4�����ײ���ַ */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* �жϱ������Ͳ���ȡ���˱�ʾ��Ϣ */
    PS_MEM_SET(&stIPv4Filter, 0, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    ulDecodeRet = ADS_FILTER_DecodeDlIPv4Packet(pstIPv4Hdr, &stIPv4Filter, &enOrigPktType);
    if (VOS_OK != ulDecodeRet)
    {
        /* ����ʧ�ܻ�֧�ֵı������Ͳ���������HOST���� */
        return VOS_ERR;
    }

    /* �ڹ��˱���ƥ���ʾ��Ϣ */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE == ulRet)
    {
        /* �ҵ���ƥ��ڵ㣬����Ƿ�Ƭ����Ƭ������Ҫ����Ƭ�е������Ϣ��ȡ��������ӵ����˱��У�
            ��Ϊ��������Ƭ��Ƭ���Ĺ������� */
        if (ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT == enOrigPktType)
        {
            ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, &stIPv4Filter);

            /* ����Ƭ��������Ϣ��ӵ����˱��� */
            ADS_FILTER_AddFilter(&stIPv4Filter);
        }

        ADS_FILTER_DBG_STATISTIC(enOrigPktType, 1);

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ProcDlIPv6Packet
 ��������  : ADS���˴���IPv6�����������ݰ�����
 �������  : IMM_ZC_STRU               *pstData     -- �������ݰ�
 �������  : ��
 �� �� ֵ  : VOS_OK   -- ���ݰ��������
             VOS_ERR  -- ���ݰ�δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv6Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV6_HDR_STRU                  *pstIPv6Hdr      = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ��ȡIPV6�ײ�ָ�� */
    pstIPv6Hdr = (ADS_IPV6_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* �ж����а��е�Ŀ�ĵ�ַ�Ƿ���DEVICE�˵�ַ��ͬ */
    if (ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(ADS_FILTER_GET_IPV6_ADDR(), &(pstIPv6Hdr->unDstAddr)))
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT, 1);

        ulRet = VOS_OK;
    }
    else
    {
        ulRet = VOS_ERR;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ProcDlPacket
 ��������  : ADS�������������ݰ�����
 �������  : IMM_ZC_STRU               *pstData     -- �������ݰ�
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- �������ݰ�IP����
 �������  : ��
 �� �� ֵ  : VOS_OK     -- ���ݰ��������
             VOS_ERR    -- ���ݰ�δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    ulRet   = VOS_ERR;

    /* ����IP����ѡ����˴���ʽ */
    switch (enIpType)
    {
        case ADS_PKT_TYPE_IPV4:
            /* IPv4������Ҫƥ����˱� */
            ulRet = ADS_FILTER_ProcDlIPv4Packet(pstData);
            break;

        case ADS_PKT_TYPE_IPV6:
            /* IPv6������Ҫƥ��IP��ַ�Ƿ���ͬ */
            ulRet = ADS_FILTER_ProcDlIPv6Packet(pstData);
            break;

        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ADS_Ipv4AddrItoa
 ��������  : ��IPV4��ַ�����ָ�ʽת�����ַ�����ʽ
 �������  : pucNumber [in] ���ָ�ʽ��IP��ַ,char pucNumber[4]={192,168,0,1}
 �������  : pcString [out] �ַ�����ʽ��IP��ַ,char * pcString="192.168.0.1"
 �� �� ֵ  : VOS_OK     -- ת���ɹ�
             VOS_ERR    -- ת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber)
{
    VOS_UINT32                          ret = VOS_OK;
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        ret = VOS_ERR;
    }
    else
    {
        PS_MEM_SET(pcString, 0, ADS_MAX_IPV4_ADDR_LEN);
        sprintf(astringTmp, "%d", pucNumber[0]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[1]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[2]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[3]);
        strcat(pcString, astringTmp);
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ShowStatisticInfo
 ��������  : ��ά�ɲ��ӡ��������ӡ�����б���ͳ�Ƹ���
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowStatisticInfo(VOS_VOID)
{
    PS_PRINTF("\n********************ADS FILTER ����ͳ����Ϣ************************\n");
    PS_PRINTF("����IPv4����TCP���ĸ���ͳ��              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    PS_PRINTF("����IPv4����UDP���ĸ���ͳ��              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP));
    PS_PRINTF("����IPv4����Echo Req���ĸ���ͳ��         %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ));
    PS_PRINTF("����IPv4���ͷ�Ƭ����(����Ƭ)����ͳ��     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("����IPv4���Ͳ�֧�ֹ��˵ı��ĸ���ͳ��     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));
    PS_PRINTF("����IPv6���ͱ��ĸ���ͳ��                 %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT));

    PS_PRINTF("********************ADS FILTER ����ͳ����Ϣ************************\n");
    PS_PRINTF("����IPv4����TCPƥ�䱨�ĸ���ͳ��          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));
    PS_PRINTF("����IPv4����UDPƥ�䱨�ĸ���ͳ��          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));
    PS_PRINTF("����IPv4����Echo Replyƥ�䱨�ĸ���ͳ��   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY));
    PS_PRINTF("����IPv4����ICMP�����ƥ�䱨�ĸ���ͳ�� %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));
    PS_PRINTF("����IPv4������Ƭ��Ƭƥ�䱨�ĸ���ͳ��     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    PS_PRINTF("����IPv4���ͷ���Ƭ��Ƭƥ�䱨�ĸ���ͳ��   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("����IPv6����ƥ�䱨�ĸ���ͳ��             %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT));

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ResetStatisticInfo
 ��������  : �����ά�ɲ���Ϣ
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��14��
    ��    ��   : L47619
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetStatisticInfo(VOS_VOID)
{
    PS_MEM_SET(ADS_FILTER_DBG_GET_STATS_ARRAY_ADDR(), 0, (VOS_SIZE_T)(sizeof(VOS_UINT32) * ADS_FILTER_ORIG_PKT_BUTT));
    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ShowFilterLists
 ��������  : ��ά�ɲ��ӡ��������ӡ�����еĹ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowFilterLists(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListTmp  = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead  = VOS_NULL_PTR;
    VOS_CHAR                            acIPv4Addr[ADS_MAX_IPV4_ADDR_LEN + 1];

    PS_PRINTF("*************************** ADS FILTER �������б� ******************************\n");
    PS_PRINTF("  ����  ��������    �ϻ�����       Դ��ַ       Ŀ�ĵ�ַ        ��ʾ1   ��ʾ2\n");
    PS_PRINTF("********************************************************************************\n");

    for (ulIndex = 0; ulIndex < ADS_FILTER_MAX_LIST_NUM; ulIndex++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulIndex);

        /* ѭ��������������ƥ���� */
        msp_list_for_each_safe(pstMe, pstListTmp, pstListHead)
        {
            pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

            /* ��ӡ���� */
            PS_PRINTF(" [%3d] ", ulIndex);

            /* ��ӡ�������� */
            switch (pstNode->stFilter.enPktType)
            {
                case ADS_FILTER_PKT_TYPE_TCP:
                    PS_PRINTF("   TCP   ");
                    break;
                case ADS_FILTER_PKT_TYPE_UDP:
                    PS_PRINTF("   UDP   ");
                    break;
                case ADS_FILTER_PKT_TYPE_ICMP:
                    PS_PRINTF("   ICMP  ");
                    break;
                case ADS_FILTER_PKT_TYPE_FRAGMENT:
                    PS_PRINTF("   FRAG  ");
                    break;
                default:
                    PS_PRINTF("  OTHER  ");
                    break;
            }

            /* ��ӡ�ϻ����� */
            PS_PRINTF("%11d  ", pstNode->stFilter.ulTmrCnt);

            /* ��ӡԴ��ַ */
            ADS_Ipv4AddrItoa(acIPv4Addr, (VOS_UINT8*)&pstNode->stFilter.stIPHeader.ulSrcAddr);
            PS_PRINTF("%-16s", acIPv4Addr);

            /* ��Ŀ�ĵ�ַ */
            ADS_Ipv4AddrItoa(acIPv4Addr, (VOS_UINT8*)&pstNode->stFilter.stIPHeader.ulDstAddr);
            PS_PRINTF("%-16s", acIPv4Addr);

            /* ��ӡ��ʾ1 */
            PS_PRINTF("%8d", VOS_NTOHS(pstNode->stFilter.unFilter.stTcpFilter.usSrcPort));

            /* ��ӡ��ʾ2 */
            PS_PRINTF("%8d\n", VOS_NTOHS(pstNode->stFilter.unFilter.stTcpFilter.usDstPort));
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_FILTER_ShowIPv6Addr
 ��������  : ��ά�ɲ��ӡ��������ӡIPv6��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : V3R3 Share-PDP��Ŀ��������
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowIPv6Addr(VOS_VOID)
{
    VOS_UINT8                          *pucIPv6Addr = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;

    pucIPv6Addr = ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr;

    for (ucLoop = 0; ucLoop < ADS_IPV6_ADDR_LEN; ucLoop++)
    {
        if ( (0 != ucLoop) && (0 == ucLoop % 2) )
        {
            PS_PRINTF(":");
        }
        PS_PRINTF("%02x", pucIPv6Addr[ucLoop]);
    }

    PS_PRINTF("\n");

    return;
}

