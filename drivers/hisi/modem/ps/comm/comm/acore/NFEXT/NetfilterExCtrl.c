

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "v_typdef.h"
#include "PsTypeDef.h"
#include "IpsMntn.h"
#include "TtfOamInterface.h"
#include "TTFComm.h"
#include "NetfilterEx.h"
#include "TTFUtil.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_ACPU_NFEX_CTRL_C


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
NF_EXT_ENTITY_STRU                  g_stExEntity;

#if(NF_EXT_DBG == DBG_ON)
NF_EXT_STATS_STRU                   g_stNfExtStats = {{0}};
#endif

NF_EXT_FLOW_CTRL_ENTITY             g_stExFlowCtrlEntity;
NF_EXT_NV_STRU                      g_stNfExtNv;
NF_EXT_HOOK_MASK_NV_STRU            g_stExHookMask;

/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
/* ��չnetfilter����ӳ��� */
NF_EXT_MASK_OPS_STRU g_stNfExtMaskOps[]    =
{
    {
        NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrPreRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_PRE_ROUTING,
            .priority   = NF_BR_PRI_FILTER_OTHER,       /* ����hook���������ȼ� */
        }
    },
    {
        NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrPostRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_POST_ROUTING,
            .priority   = NF_BR_PRI_FILTER_OTHER,
        }
    },
    {
        NF_EXT_BR_FORWARD_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrForwardHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_FORWARD,
            .priority   = NF_BR_PRI_FILTER_OTHER,
        }
    },
    {
        NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrLocalInHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_LOCAL_IN,
            .priority   = NF_BR_PRI_FILTER_OTHER,
        }
    },
    {
        NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrLocalOutHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_LOCAL_OUT,
            .priority   = NF_BR_PRI_FILTER_OTHER,
        }
    },
    {
        NF_EXT_ARP_LOCAL_IN_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_ArpInHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_ARP,
            .hooknum    = NF_ARP_IN,
            .priority   = NF_IP_PRI_CONNTRACK,      /* ARP hook������ȼ� */
        }
    },
    {
        NF_EXT_ARP_LOCAL_OUT_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_ArpOutHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_ARP,
            .hooknum    = NF_ARP_OUT,
            .priority   = NF_IP_PRI_CONNTRACK,
        }
    },
    {
        NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip4PreRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV4,
            .hooknum    = NF_INET_PRE_ROUTING,
            .priority   = NF_IP_PRI_MANGLE,         /* ����DNAT hook������ȼ� */
        }
    },
    {
        NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip4PostRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV4,
            .hooknum    = NF_INET_POST_ROUTING,
            .priority   = NF_IP_PRI_SELINUX_LAST,   /* ����SNAT hook������ȼ� */
        }
    },
    {
        NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip4LocalInHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV4,
            .hooknum    = NF_INET_LOCAL_IN,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip4LocalOutHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV4,
            .hooknum    = NF_INET_LOCAL_OUT,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP4_FORWARD_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip4ForwardHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV4,
            .hooknum    = NF_INET_FORWARD,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip6PreRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV6,
            .hooknum    = NF_INET_PRE_ROUTING,
            .priority   = NF_IP_PRI_MANGLE,
        }
    },
    {
        NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip6PostRoutingHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV6,
            .hooknum    = NF_INET_POST_ROUTING,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip6LocalInHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV6,
            .hooknum    = NF_INET_LOCAL_IN,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip6LocalOutHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV6,
            .hooknum    = NF_INET_LOCAL_OUT,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_IP6_FORWARD_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_Ip6ForwardHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_IPV6,
            .hooknum    = NF_INET_FORWARD,
            .priority   = NF_IP_PRI_SELINUX_LAST,
        }
    },
    {
        NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK,
        {0,0,0,0},
        {
            .hook       = NFExt_BrForwardFlowCtrlHook,
            .owner      = THIS_MODULE,
            .priv       = NULL,
            .pf         = NFPROTO_BRIDGE,
            .hooknum    = NF_BR_FORWARD,
            .priority   = NF_BR_PRI_FILTER_BRIDGED,             /* ����������ȼ���ͬ,���ȼ������ﲻ��Ϊ0 */
        }
    }
};


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : NFExt_UnregHooks
 ��������  : ������Ҫֹͣץ��ģ������룬��ץ���Ĺ��Ӻ�������ں�ע��
 �������  : VOS_UINT32 ulMask    ���Ӻ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_VOID  NFExt_UnregHooks(VOS_UINT32 ulMask)
{
    VOS_UINT i;

    for ( i = 0; i < ARRAY_SIZE(g_stNfExtMaskOps); i++ )
    {
        if ( g_stNfExtMaskOps[i].ulHookMask == (ulMask & g_stNfExtMaskOps[i].ulHookMask) )
        {
            /*ж�ع��Ӻ���*/
            nf_unregister_hook(&(g_stNfExtMaskOps[i].stNfExtOps));

            /* ������Ӧ������λ */
            g_stExEntity.ulCurHookOnMask &= ~g_stNfExtMaskOps[i].ulHookMask;
        }
    }

}

/*****************************************************************************
 �� �� ��  : NFExt_RegHooks
 ��������  : ������Ҫ����ץ��ģ������룬��ץ���Ĺ��Ӻ���ע�ᵽ�ں�
 �������  : VOS_UINT32 ulMask        ���Ӻ�������
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_INT  NFExt_RegHooks(VOS_UINT32 ulMask)
{
    VOS_INT iRet;
    VOS_UINT i;

    for ( i = 0; i < ARRAY_SIZE(g_stNfExtMaskOps); i++ )
    {
        if ( g_stNfExtMaskOps[i].ulHookMask != (ulMask & g_stNfExtMaskOps[i].ulHookMask) )
        {
            continue;
        }

        /*ע����Ӧ�Ĺ��Ӻ���*/
        iRet = nf_register_hook(&(g_stNfExtMaskOps[i].stNfExtOps));
        if ( 0 != iRet )
        {
            TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"register_hook error!!\n");

            /*����һ��ע��ʧ����ж�ص�ǰ�����Ѿ�ע���ϵĹ��Ӻ���*/
            NFExt_UnregHooks(g_stExEntity.ulCurHookOnMask);
            return iRet;
        }

        g_stExEntity.ulCurHookOnMask |= g_stNfExtMaskOps[i].ulHookMask;
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : NFExt_ReRegHooks
 ��������  : ����ע�ṳ�Ӻ���
 �������  : VOS_UINT32 ulMask    ���Ӻ�������
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_INT  NFExt_ReRegHooks(VOS_UINT32 ulMask)
{
    VOS_INT iRet;

    /*����ע��ǰ��ж�ص�ǰ���еĹ��Ӻ���*/
    if ( 0 != g_stExEntity.ulCurHookOnMask )
    {
        NFExt_UnregHooks(g_stExEntity.ulCurHookOnMask);
    }

    iRet = NFExt_RegHooks(ulMask);

    return iRet;
}

/*****************************************************************************
 �� �� ��  : NFExt_ConfigEffective
 ��������  : ��������ע���Ӧ�Ĺ��Ӻ���
 �������  : NF_EXT_TRACE_CONFIG_REQ_STRU *pRcvMsg
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
PS_BOOL_ENUM_UINT8 NFExt_ConfigEffective(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    VOS_INT             iRet;
    VOS_UINT32          ulMask = 0;

    /* ����hook��Ĭ�Ϲ��� */
    ulMask |= NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK;

    if ( (pRcvMsg->stBridgeArpTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stBridgeArpTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN) )
    {
        ulMask |= NF_EXT_DEF_BR_ARP_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stPreRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stPreRoutingTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_PRE_ROUTING_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stPostRoutingTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stPostRoutingTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_POST_ROUTING_HOOK_ON_MASK;
    }

    if ( (pRcvMsg->stLocalTraceCfg.ulChoice > IPS_MNTN_TRACE_NULL_CHOSEN)
        && (pRcvMsg->stLocalTraceCfg.ulChoice <= IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN))
    {
        ulMask |= NF_EXT_DEF_LOCAL_HOOK_ON_MASK;
    }

    iRet = NFExt_ReRegHooks(ulMask);

    if (iRet < 0)
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_ConfigEffective: NFExt_ReRegHooks failed!\n");
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NFExt_Get1stInetIpv4Addr
 ��������  : ��ȡ�豸��һ��Ipv4��ַ
 �������  : struct net_device *pstDev ��Ҫ��ȡIP��ַ���豸
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32  NFExt_Get1stInetIpv4Addr(struct net_device *pstDev)
{
    struct in_device   *pinDev;

    /* ʹ��Linux�ں˽ṹ��ʹ��Linux��� */
    if (NULL == pstDev)
    {
        return 0;
    }

    if (NULL == pstDev->ip_ptr)
    {
        return 0;
    }

    pinDev = (struct in_device*)(pstDev->ip_ptr);

    if (NULL == pinDev->ifa_list)
    {
        return 0;
    }

    return (VOS_UINT32)htonl((VOS_ULONG)pinDev->ifa_list->ifa_address);
}

/*****************************************************************************
 �� �� ��  : NFExt_ReadNvCfg
 ��������  : ��ȡNV����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_OK, VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��27��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NFExt_ReadNvCfg(VOS_VOID)
{
    VOS_UINT32                     ulRet;

    /* ��ȡ���Ӻ���ע������� */
    ulRet = NV_Read (en_NV_Item_NETFILTER_HOOK_MASK, &g_stNfExtNv , sizeof(NF_EXT_NV_STRU));
    if (NV_OK != ulRet)
    {
        TTF_LOG1(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_ReadNvCfg Fail, Read NV FAIL, Error Code %d\n", (VOS_INT32)ulRet);
        return VOS_ERR;
    }

    /* ��NV�ṹ�ж��������븳��g_stExHookMask*/
    g_stExHookMask.ulBrArpHookValue         = g_stNfExtNv.ulNetfilterPara1;
    g_stExHookMask.ulInHookValue            = g_stNfExtNv.ulNetfilterPara2;
    g_stExHookMask.ulOutHookValue           = g_stNfExtNv.ulNetfilterPara3;
    g_stExHookMask.ulFlowCtrlHookValue      = g_stNfExtNv.ulNetfilterPara4;
    g_stExHookMask.ulLocalHookValue         = g_stNfExtNv.ulNetfilterPara5;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NFExt_SetDefaultNvCfg
 ��������  : ����Ĭ��NV����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��27��
    ��    ��   : c00191211
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NFExt_SetDefaultNvCfg(VOS_VOID)
{
    g_stExHookMask.ulBrArpHookValue     = (  NF_EXT_ARP_LOCAL_IN_ON_MASK
                                           | NF_EXT_ARP_LOCAL_OUT_ON_MASK );

    g_stExHookMask.ulInHookValue        = (  NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK
                                           | NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK );

    g_stExHookMask.ulOutHookValue       = (  NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK
                                           | NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK );

    g_stExHookMask.ulFlowCtrlHookValue  = 0;

    g_stExHookMask.ulLocalHookValue     = (  NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK
                                           | NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK
                                           | NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK
                                           | NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK);

    return;
}

/*****************************************************************************
 �� �� ��  : NFExt_EntityInit
 ��������  : NFExtģ��ʵ��ȫ�ֱ�����ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_EntityInit(VOS_VOID)
{
    g_stExEntity.ulCurHookOnMask    = 0;
    g_stExEntity.ulIsBlkflag        = NF_EXT_FLAG_BLOCKED;
    g_stExEntity.ulIsDeviceOpen     = 0;
    g_stExEntity.ulOmIp             = 0;
}

/*****************************************************************************
 �� �� ��  : NFExt_Init
 ��������  : ģ���ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_INT NFExt_Init(VOS_VOID)
{
    VOS_UINT32  ulRet;

    ulRet = NFExt_ReadNvCfg();
    if (VOS_ERR == ulRet)
    {
        NFExt_SetDefaultNvCfg();
    }

    /* NFExtģ��ʵ��ȫ�ֱ�����ʼ�� */
    NFExt_EntityInit();

    /* ������Ϣ��ʼ�� */
    NFExt_FlowCtrlInit();

    return 0;
}

/*****************************************************************************
 �� �� ��  : NFExt_Uninit
 ��������  : ģ��ж�غ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
void NFExt_Uninit(VOS_VOID)
{
    /*ȥע�ṳ�Ӻ���*/
    NFExt_UnregHooks(g_stExEntity.ulCurHookOnMask);
}

/*****************************************************************************
                        ���ع���
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NFExt_FlowCtrlInit
 ��������  : ����ʵ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_FlowCtrlInit(VOS_VOID)
{
    if (NFExt_RegHooks(NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK))
    {
        vos_printf("NFExt_FlowCtrlInit NFExt_RegHooks fail");

        return;
    }

    g_stExFlowCtrlEntity.ulFlowCtrlMsk = 0;
    g_stExFlowCtrlEntity.pstBrDev      = NULL;

    PSACORE_MEM_SET(g_stExFlowCtrlEntity.aulTxBytesCnt, sizeof(g_stExFlowCtrlEntity.aulTxBytesCnt), 0, sizeof(g_stExFlowCtrlEntity.aulTxBytesCnt));
}

/*****************************************************************************
 �� �� ��  : NFExt_BrSetFlowCtrl
 ��������  : ��������״̬����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
/*lint -e550*/
VOS_VOID  NFExt_BrSetFlowCtrl(VOS_VOID)
{
    VOS_ULONG       ulFlags = 0UL;

    local_irq_save(ulFlags);
    g_stExFlowCtrlEntity.ulFlowCtrlMsk |= NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;
    local_irq_restore(ulFlags);

    /* for lint 438 */
    (VOS_VOID)ulFlags;

    IPS_MNTN_FlowCtrl(NF_EXT_BR_FORWARD_FLOW_CTRL_MASK, ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START);
}
/*lint +e550*/

/*****************************************************************************
 �� �� ��  : NFExt_BrStopFlowCtrl
 ��������  : ��������״̬���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
/*lint -e550*/
VOS_VOID  NFExt_BrStopFlowCtrl(VOS_VOID)
{
    VOS_ULONG       ulFlags = 0UL;

    local_irq_save(ulFlags);
    g_stExFlowCtrlEntity.ulFlowCtrlMsk &= ~NF_EXT_BR_FORWARD_FLOW_CTRL_MASK;
    local_irq_restore(ulFlags);

    /* for lint 438 */
    (VOS_VOID)ulFlags;

    IPS_MNTN_FlowCtrl(NF_EXT_BR_FORWARD_FLOW_CTRL_MASK, ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP);
}
/*lint +e550*/

/*****************************************************************************
 �� �� ��  : NFExt_GetBrBytesCnt
 ��������  : ��ȡ��ǰ���ŷ��ͽ�������ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ���ŷ��ͽ�������ͳ����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 NFExt_GetBrBytesCnt(VOS_VOID)
{
    return 0;
}


/*****************************************************************************
 �� �� ��  : NFExt_SaveBrDev
 ��������  : ���浱ǰ������ʹ�õ������豸
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 NFExt_SaveBrDev(VOS_VOID)
{
    struct net_device   *dev;
    dev = dev_get_by_name(&init_net, NF_EXT_BR_NAME);

    if (NULL == dev)
    {
        return VOS_ERR;
    }

    g_stExFlowCtrlEntity.pstBrDev   = dev;

    /* ֻ��ȡ��һ��IPv4��ַ */
    g_stExEntity.ulOmIp             = NFExt_Get1stInetIpv4Addr(dev);

    return VOS_OK;
}

#if(NF_EXT_DBG == DBG_ON)
/*****************************************************************************
 �� �� ��  : NFExt_StatsShow
 ��������  : Netfilter ex debug������ӡ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_StatsShow(VOS_VOID)
{
    vos_printf("����forward���ض����������� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BR_FC_DROP]);
    vos_printf("��������forward hook�������� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BR_FC_ENTER]);
    vos_printf("����buf��֮���¶������� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_BUF_FULL_DROP]);
    vos_printf("�뻷��bufʧ�ܴ��� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_PUT_BUF_FAIL]);
    vos_printf("������bufʧ�ܴ��� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_GET_BUF_FAIL]);
    vos_printf("�����ڴ�ʧ�ܴ��� %ld \n", g_stNfExtStats.aulStats[NF_EXT_STATS_ALLOC_MEM_FAIL]);

    vos_printf("��ǰ���λ�����δ����������� %ld \n", ((VOS_UINT32)OM_RingBufferNBytes(g_stExEntity.pRingBufferId) / sizeof(NF_EXT_DATA_RING_BUF_STRU)));
    vos_printf("��ǰ��Hook Mask %ld \n", g_stExEntity.ulCurHookOnMask);
    vos_printf("��ǰ������״̬Mask %ld \n", g_stExFlowCtrlEntity.ulFlowCtrlMsk);
    vos_printf("��ǰOM WIFI��ʹ�õ�IP��ַ %x \n", g_stExEntity.ulOmIp);
    vos_printf("��ǰ����ת���ֽ��� %x \n", g_stExFlowCtrlEntity.aulTxBytesCnt[NF_EXT_TX_BYTES_CNT_BR]);
}

/*****************************************************************************
 �� �� ��  : NFExt_ResetPri
 ��������  : ����netfilter ex hook�����ȼ�����,Debugʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��11��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_ResetPri(VOS_UINT32 ulHookNode, VOS_INT32 iPri)
{
    VOS_UINT32  ulCurHookMask = 0;

    if (ulHookNode > (ARRAY_SIZE(g_stNfExtMaskOps) - 1))
    {
        return;
    }

    ulCurHookMask = g_stExEntity.ulCurHookOnMask;
    g_stNfExtMaskOps[ulHookNode].stNfExtOps.priority = iPri;

    NFExt_ReRegHooks(ulCurHookMask);

    vos_printf("Current ulHookNode %d pri = %d\n", ulHookNode, iPri);
}
#endif


/*****************************************************************************
 �� �� ��  : NFExt_SelfTaskInit
 ��������  : NFExtģ���Դ��������ʼ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_SelfTaskInit(VOS_VOID)
{
    g_stExEntity.pRingBufferId = OM_RingBufferCreate(NF_EXT_RING_BUF_SIZE);

    if ( VOS_NULL_PTR == g_stExEntity.pRingBufferId )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_SelfTaskInit : ERROR : Create ring buffer Failed!" );

        return;
    }

    /* ��ʼ���Դ�������ĵȴ�����ͷ */
    init_waitqueue_head(&g_stExEntity.stWaitHeadTxTask);
    spin_lock_init(&g_stExEntity.stLockTxTask);
}

/*****************************************************************************
 �� �� ��  : NFExt_RingBufferPut
 ��������  : �����ݷŵ�ring buffer��
 �������  : OM_RING_ID rngId:      ����buff
             VOS_CHAR *buffer:      �����뻷��buff������ͷָ��
             VOS_INT nbytes:        �����뻷��buff�����ݳ���
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_INT NFExt_RingBufferPut( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT nbytes )
{
    VOS_ULONG   ulFlags = 0UL;
    VOS_INT     iRst;

    iRst = 0;

    spin_lock_irqsave(&g_stExEntity.stLockTxTask, ulFlags);
    if ((VOS_UINT32)OM_RingBufferFreeBytes(g_stExEntity.pRingBufferId) >= sizeof(NF_EXT_DATA_RING_BUF_STRU) )
    {
        iRst = OM_RingBufferPut(rngId, buffer, nbytes);
    }
    spin_unlock_irqrestore(&g_stExEntity.stLockTxTask, ulFlags);

    return iRst;
}

/*****************************************************************************
 �� �� ��  : NFExt_RingBufferGet
 ��������  : �����ݴ�ring buffer��ȡ��
 �������  : OM_RING_ID rngId:      ����buff
             VOS_CHAR *buffer:      ����buff�д�ȡ��������ͷָ��
             VOS_INT nbytes:        ����buff�д�ȡ�������ݳ���
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_INT NFExt_RingBufferGet( OM_RING_ID rngId, VOS_CHAR *buffer, VOS_INT maxbytes )
{
    VOS_ULONG   ulFlags = 0UL;
    VOS_INT     iRst;

    iRst = 0;

    spin_lock_irqsave(&g_stExEntity.stLockTxTask, ulFlags);
    if (!OM_RingBufferIsEmpty(rngId))
    {
        iRst = OM_RingBufferGet(rngId, buffer, maxbytes );
    }
    spin_unlock_irqrestore(&g_stExEntity.stLockTxTask, ulFlags);

    return iRst;
}

/*****************************************************************************
 �� �� ��  : NFExt_FlushRingBuffer
 ��������  : ��RingBuffer��������ݶ����
 �������  : OM_RING_ID rngId OM ringbuffer id
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_FlushRingBuffer(OM_RING_ID rngId)
{
    NF_EXT_DATA_RING_BUF_STRU   stData;
    VOS_ULONG                   ulFlags = 0UL;
    VOS_INT                     iRst = 0;

    while (!OM_RingBufferIsEmpty(rngId))
    {
        iRst = NFExt_RingBufferGet(rngId, (VOS_CHAR*)(&stData), sizeof(NF_EXT_DATA_RING_BUF_STRU));
        if (iRst == sizeof(NF_EXT_DATA_RING_BUF_STRU))
        {
            NF_EXT_MEM_FREE(ACPU_PID_NFEXT, stData.pData);
        }
        else
        {
            TTF_LOG1(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                    "NFExt_FlushRingBuffer : ERROR : Get data error from ring buffer!", iRst);

            break;
        }
    }

    spin_lock_irqsave(&g_stExEntity.stLockTxTask, ulFlags);
    OM_RingBufferFlush(rngId);
    spin_unlock_irqrestore(&g_stExEntity.stLockTxTask, ulFlags);
}


/*****************************************************************************
 �� �� ��  : NFExt_AddDataToRingBuf
 ��������  : ����Ҫͨ��OAM���͵����ݷŵ��Դ��������RingBuf���棬���Դ��������ͳ�ȥ
 �������  : NF_EXT_DATA_RING_BUF_STRU *pstData ����ringbuffer�е�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
  2.��    ��   :  2015��10��31��
    ��    ��   :  g00178567
    �޸�����   :  �������죬���͹��������л�Ƶ��
*****************************************************************************/
VOS_UINT32 NFExt_AddDataToRingBuf(NF_EXT_DATA_RING_BUF_STRU *pstData)
{
    VOS_UINT32                  ulRst           = VOS_OK;
    VOS_UINT32                  ulNeedWakeUp    = VOS_FALSE;
    VOS_INT                     iRst;
    NF_EXT_DATA_RING_BUF_STRU   stData;

    if ( VOS_NULL_PTR == g_stExEntity.pRingBufferId )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_AddDataToRingBuf: Warning : g_stExEntity.pRingBufferId is null!\n");
        return VOS_ERR;
    }

    /* �յ��ǿգ������������� */
    if (OM_RingBufferIsEmpty(g_stExEntity.pRingBufferId))
    {
        ulNeedWakeUp = VOS_TRUE;
    }

    iRst = NFExt_RingBufferPut(g_stExEntity.pRingBufferId, (VOS_CHAR *)pstData, (VOS_INT)(sizeof(NF_EXT_DATA_RING_BUF_STRU)));
    if (sizeof(NF_EXT_DATA_RING_BUF_STRU) == iRst)
    {
        if (VOS_TRUE == ulNeedWakeUp)
        {
            wake_up_interruptible(&g_stExEntity.stWaitHeadTxTask);
        }

        ulRst = VOS_OK;
    }
    else if (0 == iRst)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_BUF_FULL_DROP);

        /* �������������������� */
        wake_up_interruptible(&g_stExEntity.stWaitHeadTxTask);

        ulRst = VOS_ERR;
    }
    else
    {
        TTF_LOG2(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "RingBufferPut Fail found ulRst = %u, sizeof=%u \r\n", iRst, sizeof(NF_EXT_DATA_RING_BUF_STRU));

        (VOS_VOID)NFExt_RingBufferGet(g_stExEntity.pRingBufferId, (VOS_CHAR *)(&stData), iRst);

        NF_EXT_STATS_INC(1, NF_EXT_STATS_PUT_BUF_FAIL);

        ulRst = VOS_ERR;
    }

    return ulRst;
}
/*****************************************************************************
 �� �� ��  : NFExt_AddDataToRingBuf
 ��������  : NFEXT�Դ������񣬸������OAM��Ϣ���ͽӿڣ�������Ϣ��SDT
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : t00148005
    �޸�����   : Created
  2.��    ��   :  2015��10��31��
    ��    ��   :  g00178567
    �޸�����   :  �������죬���͹��������л�Ƶ��
*****************************************************************************/
VOS_VOID NFExt_CtrlTxMsgTask(VOS_VOID)
{
    NF_EXT_DATA_RING_BUF_STRU   stData;
    VOS_INT                     iRst;
    DIAG_TRANS_IND_STRU        *pstDiagTransData;
    VOS_UINT32                  ulDealCntOnce;

/* ���UT��ѭ������ */

/* ���UT��ѭ������ */
    for ( ; ; )
    {
        if (VOS_NULL_PTR == g_stExEntity.pRingBufferId)
        {
            TTF_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                "NFExt_CtrlSendTask : ERROR : pRingBufferId is NULL!" );
            break;
        }

        /*lint -e{522,666} */
        wait_event_interruptible(g_stExEntity.stWaitHeadTxTask, (!OM_RingBufferIsEmpty(g_stExEntity.pRingBufferId)));

        ulDealCntOnce = 0;

        while (!OM_RingBufferIsEmpty(g_stExEntity.pRingBufferId))
        {
            /* һ��������ȣ���ദ��200������ */
            if (200 <= ulDealCntOnce)
            {
                break;
            }

            iRst = NFExt_RingBufferGet(g_stExEntity.pRingBufferId, (VOS_CHAR *)&stData, sizeof(NF_EXT_DATA_RING_BUF_STRU));
            if (sizeof(NF_EXT_DATA_RING_BUF_STRU) == iRst)
            {
                pstDiagTransData = (DIAG_TRANS_IND_STRU *)(stData.pData);
                if ( VOS_OK != DIAG_TransReport(pstDiagTransData))
                {
                    TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_ERROR,
                        "IPS, DIAG_TransReport, ERROR, Call DIAG_TransReport fail!");
                }

                NF_EXT_MEM_FREE(ACPU_PID_NFEXT, stData.pData);
            }
            else if (0 == iRst)
            {
                TTF_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                    "NFExt_CtrlSendTask : ERROR : Get null from ring buffer!");

                break;
            }
            else
            {
                TTF_LOG2(ACPU_PID_NFEXT, 0, PS_PRINT_WARNING,
                    "NFExt_CtrlSendTask : ERROR : Get data error from ring buffer!", iRst, sizeof(NF_EXT_DATA_RING_BUF_STRU));

                NF_EXT_STATS_INC(1, NF_EXT_STATS_GET_BUF_FAIL);

                NFExt_FlushRingBuffer(g_stExEntity.pRingBufferId);

                break;
            }

            ulDealCntOnce++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NFExt_RcvNfExtInfoCfgReq
 ��������  : ���յ�OM���ÿ�ά�ɲ���Ϣ������������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_RcvNfExtInfoCfgReq(VOS_VOID *pMsg)
{
    OM_IPS_MNTN_INFO_CONFIG_REQ_STRU    *pstNfExtCfgReq;
    IPS_OM_MNTN_INFO_CONFIG_CNF_STRU    stNfExtCfgCnf;
    IPS_MNTN_RESULT_TYPE_ENUM_UINT32    enResult;

    pstNfExtCfgReq  = (OM_IPS_MNTN_INFO_CONFIG_REQ_STRU *)pMsg ;

    enResult        = IPS_MNTN_RESULT_OK;

    /*================================*/
    /*�����ظ���Ϣ*/
    /*================================*/

    /* Fill DIAG trans msg header */
    stNfExtCfgCnf.stDiagHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stNfExtCfgCnf.stDiagHdr.ulSenderPid     = ACPU_PID_NFEXT;
    stNfExtCfgCnf.stDiagHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stNfExtCfgCnf.stDiagHdr.ulReceiverPid   = MSP_PID_DIAG_APP_AGENT;   /* ��Ӧ����Ϣ���͸�DIAG����DIAG��͸������Ĵ��������͸�HIDS����*/
    stNfExtCfgCnf.stDiagHdr.ulLength        = sizeof(IPS_OM_MNTN_INFO_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stNfExtCfgCnf.stDiagHdr.ulMsgId         = ID_IPS_OM_MNTN_INFO_CONFIG_CNF;

    /* DIAG͸�������е��ض���Ϣ*/
    stNfExtCfgCnf.stDiagHdr.usOriginalId  = pstNfExtCfgReq->stDiagHdr.usOriginalId;
    stNfExtCfgCnf.stDiagHdr.usTerminalId  = pstNfExtCfgReq->stDiagHdr.usTerminalId;
    stNfExtCfgCnf.stDiagHdr.ulTimeStamp   = pstNfExtCfgReq->stDiagHdr.ulTimeStamp;
    stNfExtCfgCnf.stDiagHdr.ulSN          = pstNfExtCfgReq->stDiagHdr.ulSN;

    /* ���ظ�OM�����ȷ����Ϣ */
    stNfExtCfgCnf.stIpsMntnCfgCnf.enCommand  = pstNfExtCfgReq->stIpsMntnCfgReq.enCommand;
    stNfExtCfgCnf.stIpsMntnCfgCnf.enRslt     = enResult;

    /* ����OM͸����Ϣ */
    IPS_MNTN_SndCfgCnf2Om( ID_IPS_OM_MNTN_INFO_CONFIG_CNF,
        sizeof(IPS_OM_MNTN_INFO_CONFIG_CNF_STRU), &stNfExtCfgCnf );

    return;

}

/*****************************************************************************
 �� �� ��  : NFExt_RcvOmMsg
 ��������  : NFExt���յ�����OMģ�����Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_RcvOmMsg(VOS_VOID *pMsg)
{
    VOS_UINT16          usMsgId;

    usMsgId = (VOS_UINT16)(*((VOS_UINT32 *)((VOS_UINT8 *)(pMsg) + VOS_MSG_HEAD_LENGTH)));

    switch ( usMsgId )
    {
        case ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ:
            IPS_MNTN_TraceAdvancedCfgReq(pMsg);
            break;

        case ID_OM_IPS_MNTN_INFO_CONFIG_REQ:
            NFExt_RcvNfExtInfoCfgReq(pMsg);
            break;

        default:
            TTF_LOG1(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "NFExt_RcvConfig:Receive Unkown Type Message !\n", usMsgId);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NFExt_MsgProc
 ��������  : NFExt��ά�ɲ������Ϣ������
 �������  : struct MsgCB * pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_VOID NFExt_MsgProc( struct MsgCB * pMsg )
{
    if ( VOS_NULL_PTR == pMsg )
    {
        TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_MsgProc: Message is NULL !" );
        return;
    }

    switch ( pMsg->ulSenderPid )
    {
        case MSP_PID_DIAG_APP_AGENT:      /* ����OM��͸����Ϣ���� */
            NFExt_RcvOmMsg( (void *)pMsg );
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NFExt_PidInit
 ��������  : NFExt_Pid��ʼ��
 �������  : ip - ��ʼ��״̬
 �������  : ��
 �� �� ֵ  : �ɹ�VOS_OK, ʧ��VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 NFExt_PidInit( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:

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
            break;
        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : NFExt_FidInit
 ��������  : NFExt_Fid��ʼ��
 �������  : ip - ��ʼ��״̬
 �������  : ��
 �� �� ֵ  : �ɹ�VOS_OK, ʧ��VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��22��
    ��    ��   : caikai
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 NFExt_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                          ulRslt;
    VOS_INT                             iRet;

    switch ( ip )
    {
        case   VOS_IP_LOAD_CONFIG:

            /* �����ģ���ʼ�� */
            iRet    = NFExt_Init();

            if ( 0 != iRet )
            {
                TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"NFExt_FidInit: NFExt_Init FAIL!\n");
                return PS_FAIL;
            }

            /*�Դ��������ʼ��*/
            NFExt_SelfTaskInit();

            /* ��ά�ɲ�ģ��ע��PID */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_NFEXT,
                                (Init_Fun_Type)NFExt_PidInit,
                                (Msg_Fun_Type)NFExt_MsgProc);

            if( VOS_OK != ulRslt )
            {
                TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"reg UEPS_PID_NFEXT VOS_RegisterPIDInfo FAIL!\n");
                return PS_FAIL;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_NFEXT, VOS_PRIORITY_M4);
            if( VOS_OK != ulRslt )
            {
                TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"VOS_RegisterTaskPrio Failed!\n");
                return PS_FAIL;
            }

            ulRslt = VOS_RegisterSelfTask(ACPU_FID_NFEXT,
                                    (VOS_TASK_ENTRY_TYPE)NFExt_CtrlTxMsgTask,
                                    VOS_PRIORITY_BASE,
                                    NF_TX_MSG_TASK_STACK_SIZE);

            if ( VOS_NULL_BYTE == ulRslt )
            {
                TTF_LOG(ACPU_PID_NFEXT, DIAG_MODE_COMM, PS_PRINT_WARNING,"Self Task Regist fail!\n");
            }

            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return PS_SUCC;
}


