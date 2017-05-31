

#ifndef __RNICDEBUG_H__
#define __RNICDEBUG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "RnicLinuxInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define RNIC_DBG_NET_TX_RMNETID_ERR_NUM(n)          (g_stRnicMntnStats.ulNetTxRmNetIdErrNum += (n))
#define RNIC_DBG_SPE_TX_PORTID_ERR_NUM(n)           (g_stRnicMntnStats.ulSpeTxPortIdErrNum += (n))

/* ����ͳ����Ϣ */
#define  RNIC_DBG_RECV_UL_IPV4_PKT_NUM(n, index)       (g_astRnicStats[index].ulUlRecvIpv4PktNum += (n))
#define  RNIC_DBG_RECV_UL_IPV6_PKT_NUM(n, index)       (g_astRnicStats[index].ulUlRecvIpv6PktNum += (n))
#define  RNIC_DBG_RECV_UL_IPV4V6_PKT_NUM(n, index)     (g_astRnicStats[index].ulUlRecvIpv4v6PktNum += (n))
#define  RNIC_DBG_RECV_UL_UNDIAL_PKT_NUM(n, index)     (g_astRnicStats[index].ulUlRecvUndiaPktNum += (n))
#define  RNIC_DBG_SEND_UL_PKT_NUM(n, index)            (g_astRnicStats[index].ulUlSendPktNum += (n))
#define  RNIC_DBG_SEND_UL_PKT_FAIL_NUM(n, index)       (g_astRnicStats[index].ulUlSendPktFailNum += (n))
#define  RNIC_DBG_UL_RECV_IPV4_BROADCAST_NUM(n, index) (g_astRnicStats[index].ulUlIpv4BrdcstPktNum += (n))
#define  RNIC_DBG_UL_CHANGE_IMMZC_FAIL_NUM(n, index)   (g_astRnicStats[index].ulUlImmzcFailPktNum += (n))
#define  RNIC_DBG_UL_RMV_MAC_HDR_FAIL_NUM(n, index)    (g_astRnicStats[index].ulUlRmvMacHdrFailPktNum += (n))
#define  RNIC_DBG_NETCAED_UL_DISCARD_NUM(n, index)     (g_astRnicStats[index].ulUlNetCardDiscardNum += (n))
#define  RNIC_DBG_FLOW_CTRL_UL_DISCARD_NUM(n, index)   (g_astRnicStats[index].ulUlFlowCtrlDiscardNum += (n))
#define  RNIC_DBG_RECV_UL_ERR_PKT_NUM(n, index)        (g_astRnicStats[index].ulUlRecvErrPktNum += (n))
#define  RNIC_DBG_RAB_ID_ERR_NUM(n, index)             (g_astRnicStats[index].ulUlRabIdErr += (n))
#define  RNIC_DBG_SEND_APP_DIALUP_SUCC_NUM(n, index)   (g_astRnicStats[index].ulUlSendAppDialUpSucc += (n))
#define  RNIC_DBG_SEND_APP_DIALUP_FAIL_NUM(n, index)   (g_astRnicStats[index].ulUlSendAppDialUpFail += (n))
#define  RNIC_DBG_SEND_APP_DIALDOWN_SUCC_NUM(n, index) (g_astRnicStats[index].ulUlSendAppDialDownSucc += (n))
#define  RNIC_DBG_SEND_APP_DIALDOWN_FAIL_NUM(n, index) (g_astRnicStats[index].ulUlSendAppDialDownFail += (n))
#define  RNIC_DBG_NET_ID_UL_DISCARD_NUM(n, index)      (g_astRnicStats[index].ulUlNetIdDiscardNum += (n))
#define  RNIC_DBG_MODEM_ID_UL_DISCARD_NUM(n, index)    (g_astRnicStats[index].ulUlModemIdDiscardNum += (n))
#define  RNIC_DBG_PDN_ID_ERR_NUM(n, index)             (g_astRnicStats[index].ulUlPdnIdErr += (n))

/* ����ͳ����Ϣ */
#define  RNIC_DBG_RECV_DL_IPV4_PKT_NUM(n, index)       (g_astRnicStats[index].ulDlRecvIpv4PktNum += (n))
#define  RNIC_DBG_RECV_DL_IPV6_PKT_NUM(n, index)       (g_astRnicStats[index].ulDlRecvIpv6PktNum += (n))
#define  RNIC_DBG_SEND_DL_PKT_NUM(n, index)            (g_astRnicStats[index].ulDlSendPktNum += (n))
#define  RNIC_DBG_SEND_DL_PKT_FAIL_NUM(n, index)       (g_astRnicStats[index].ulDlSendPktFailNum += (n))
#define  RNIC_DBG_RECV_DL_BIG_PKT_NUM(n, index)        (g_astRnicStats[index].ulDlRecvBigPktNum += (n))
#define  RNIC_DBG_DISCARD_DL_PKT_NUM(n, index)         (g_astRnicStats[index].ulDlDiscardPktNum += (n))
#define  RNIC_DBG_ADD_DL_MACHEAD_FAIL_NUM(n, index)    (g_astRnicStats[index].ulDlAddMacHdFailNum += (n))
#define  RNIC_DBG_NETCAED_DL_DISCARD_NUM(n, index)     (g_astRnicStats[index].ulDlNetCardDiscardNum += (n))
#define  RNIC_DBG_RECV_DL_ERR_PKT_NUM(n, index)        (g_astRnicStats[index].ulDlRecvErrPktNum += (n))
#define  RNIC_DBG_NETID_DL_DISCARD_NUM(n, index)       (g_astRnicStats[index].ulDlNetIdDiscardNum += (n))

#define RNIC_DBG_SET_SEM_INIT_FLAG(flag)               (g_astRnicStats[0].ulSemInitFlg = (flag))
#define RNIC_DBG_SAVE_BINARY_SEM_ID(sem_id)            (g_astRnicStats[0].hBinarySemId = (sem_id))
#define RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)         (g_astRnicStats[0].ulCreateBinarySemFailNum += (n))
#define RNIC_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)           (g_astRnicStats[0].ulLockBinarySemFailNum += (n))
#define RNIC_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)      (g_astRnicStats[0].ulLastBinarySemErrRslt = (rslt))
#define RNIC_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)        (g_astRnicStats[0].ulResetSucessNum += (n))

#define RNIC_DBG_CONFIGCHECK_ADD_TOTLA_NUM()            (g_stRnicRmnetConfigCheckInfo.ucTotlaCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_MODEMTYPE_ERR_NUM()    (g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_IPTYPE_ERR_NUM()       (g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_MODEMID_ERR_NUM()      (g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_PDNID_ERR_NUM()        (g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RABID_ERR_NUM()        (g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RMNETID_ERR_NUM()      (g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RMNETSTATUS_ERR_NUM()  (g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_SND_ERR_NUM()          (g_stRnicRmnetConfigCheckInfo.ucSendErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_SUCC_NUM()             (g_stRnicRmnetConfigCheckInfo.ucSuccCnt++)

#define RNIC_DBG_PRINT_UL_DATA(skb) \
            if (VOS_TRUE == g_ulRnicPrintUlDataFlg) \
            { \
                RNIC_ShowDataFromIpStack(skb); \
            }

#if (VOS_OS_VER == VOS_LINUX)
#define RNIC_DEV_ERR_PRINTK(pcString)     printk(KERN_ERR "%s", pcString);
#else
#define RNIC_DEV_ERR_PRINTK(pcString)     PS_PRINTF("%s", pcString);
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulNetTxRmNetIdErrNum;
    VOS_UINT32                          ulSpeTxPortIdErrNum;

} RNIC_MNTN_STATS_STRU;

/*****************************************************************************
 �ṹ��    : RNIC_STATS_INFO_STRU
 �ṹ˵��  : RNICͳ����
  1.��    ��   : 2012��1��20��
    ��    ��   : S62952
    �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    /* ����ͳ����Ϣ */
    VOS_UINT32              ulUlRecvIpv4PktNum;                                 /* RNIC�յ�����IPV4���ݵĸ��� */
    VOS_UINT32              ulUlRecvIpv6PktNum;                                 /* RNIC�յ�����IPV6���ݵĸ��� */
    VOS_UINT32              ulUlRecvIpv4v6PktNum;                               /* IPV4V6���ͼ���ʱRNIC�յ��������ݵĸ���(IPV4��IPV6) */
    VOS_UINT32              ulUlRecvUndiaPktNum;                                /* RNICδ����ʱ�յ��������ݵĸ��� */
    VOS_UINT32              ulUlSendPktNum;                                     /* RNIC���з��͸�ADS���ݵĸ��� */
    VOS_UINT32              ulUlSendPktFailNum;                                 /* RNIC��ADS������������ʧ�ܵĸ��� */
    VOS_UINT32              ulUlIpv4BrdcstPktNum;                               /* RNICδ���Ϻ�ǰ�����յ�IPV4�㲥���ĸ��� */
    VOS_UINT32              ulUlImmzcFailPktNum;                                /* RNIC����ת��ΪIMM_ZCʧ�ܵĸ��� */
    VOS_UINT32              ulUlRmvMacHdrFailPktNum;                            /* RNIC����ȥ��MACͷʧ�ܵĸ��� */
    VOS_UINT32              ulUlNetCardDiscardNum;                              /* RNIC����˽�����ݴ��󶪵��������ݰ��ĸ��� */
    VOS_UINT32              ulUlFlowCtrlDiscardNum;                             /* RNIC�������ض����������ݰ��ĸ��� */
    VOS_UINT32              ulUlRecvErrPktNum;                                  /* RNIC�յ��������ݰ��ĸ���(��ipv4��ipv6��) */
    VOS_UINT32              ulUlSendAppDialUpSucc;                              /* RNIC�ɹ��ϱ�APP���貦�� */
    VOS_UINT32              ulUlSendAppDialUpFail;                              /* RNIC�ϱ�APP���貦��ʧ�� */
    VOS_UINT32              ulUlSendAppDialDownSucc;                            /* RNIC�ɹ��ϱ�APP�Ͽ����� */
    VOS_UINT32              ulUlSendAppDialDownFail;                            /* RNIC�ϱ�APP�Ͽ�����ʧ�� */
    VOS_UINT32              ulUlRabIdErr;                                       /* Rab id���� */
    VOS_UINT32              ulUlNetIdDiscardNum;                                /* RNIC����ID���󶪵��������ݰ��ĸ��� */
    VOS_UINT32              ulUlModemIdDiscardNum;                              /* RNIC Modem ID���󶪵��������ݰ��ĸ��� */

    /* ����ͳ����Ϣ */
    VOS_UINT32              ulDlRecvIpv4PktNum;                                 /* RNIC�յ�����IPV4���ݵĸ��� */
    VOS_UINT32              ulDlRecvIpv6PktNum;                                 /* RNIC�յ�����IPV6���ݵĸ��� */
    VOS_UINT32              ulDlSendPktNum;                                     /* RNIC�����������ݵĸ��� */
    VOS_UINT32              ulDlSendPktFailNum;                                 /* RNIC������������ʧ�ܵĸ��� */
    VOS_UINT32              ulDlRecvBigPktNum;                                  /* RNIC�յ��������ݰ�����MTU�ĸ��� */
    VOS_UINT32              ulDlDiscardPktNum;                                  /* RNIC����δ����������ݸ��� */
    VOS_UINT32              ulDlAddMacHdFailNum;                                /* RNIC���м�MACͷʧ�ܵĸ��� */
    VOS_UINT32              ulDlNetCardDiscardNum;                              /* RNIC����˽�����ݴ��󶪵��������ݰ��ĸ��� */
    VOS_UINT32              ulDlRecvErrPktNum;                                  /* RNIC�յ��������ݰ��ĸ���(��ipv4��ipv6��) */
    VOS_UINT32              ulDlNetIdDiscardNum;                                /* RNIC����ID���󶪵��������ݰ��ĸ��� */
    VOS_UINT8               aucReserved[4];

    /* ��λ�ź�����Ϣ */
    VOS_SEM                 hBinarySemId;                                       /* �������ź���ID */
    VOS_UINT32              ulSemInitFlg;                                       /* ��ʼ����ʶ, VOS_TRUE: �ɹ�; VOS_FALSE: ʧ�� */
    VOS_UINT32              ulCreateBinarySemFailNum;                           /* �����������ź���ʧ�ܴ��� */
    VOS_UINT32              ulLockBinarySemFailNum;                             /* ���������ź���ʧ�ܴ��� */
    VOS_UINT32              ulLastBinarySemErrRslt;                             /* ���һ�����������ź���ʧ�ܽ�� */
    VOS_UINT32              ulResetSucessNum;                                   /* C�˸�λ�ɹ��Ĵ��� */

    VOS_UINT32              ulUlPdnIdErr;                                       /* Pdn id���� */
}RNIC_STATS_INFO_STRU;

/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
/*****************************************************************************
 �ṹ��    : RNIC_RMNET_CONFIG_CHECK_INFO_STRU
 �ṹ˵��  : RNIC �������ü�����Ϣͳ��
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotlaCnt;
    VOS_UINT8                           ucModemTypeErrCnt;
    VOS_UINT8                           ucRmNetIdErrCnt;
    VOS_UINT8                           ucModemIdErrCnt;
    VOS_UINT8                           ucPdnIdErrCnt;
    VOS_UINT8                           ucRabIdErrCnt;
    VOS_UINT8                           ucRmnetStatusErrCnt;
    VOS_UINT8                           ucIpTypeErrCnt;
    VOS_UINT8                           ucSendErrCnt;
    VOS_UINT8                           ucSuccCnt;
}RNIC_RMNET_CONFIG_CHECK_INFO_STRU;

/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

/*****************************************************************************
  8 ȫ�ֱ�������
*****************************************************************************/

extern RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats;
extern RNIC_STATS_INFO_STRU                    g_astRnicStats[];
extern RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
extern VOS_UINT32                              g_ulRnicPrintUlDataFlg;
extern VOS_UINT32                              g_ulRnicPrintDlDataFlg;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
);

VOS_VOID RNIC_ShowResetStats(VOS_VOID);
VOS_VOID RNIC_Help(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AdsTest.h */

