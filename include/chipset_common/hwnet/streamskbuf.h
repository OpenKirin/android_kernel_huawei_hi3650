/*
 * streamskbuf.h
 *
 * for stream track,define the external parameter
 *
 * Copyright (c) 2001-2021, Huawei Tech. Co., Ltd. All rights reserved.
 *
 * yangmingcheng <yangmingcheng@huawei.com>
*/


#ifndef _LINUX_STREAM_SKBUFF_H
#define _LINUX_STREAM_SKBUFF_H


#define CONFIG_NET_STREAM

/* ���õ�index��Сֵ��С�ڴ�ֵΪ������ */
#define NET_STREAM_CFG_INDEXT_MIN_VLAUE 100
/* ����udp��tcpЭ������ */
#define NET_STREAM_UDP_TYPE 17
#define NET_STREAM_TCP_TYPE 6
/* �����ٵ�ħ���� */
#define NET_STREAM_FLAG_NUM 0xFFAA6688

/* ��ӡ���� */
#define STREM_KERN_EMERG	0	/* system is unusable */
#define STREM_KERN_ALERT	1	/* action must be taken immediately */
#define STREM_KERN_CRIT	2	/* critical conditions */
#define STREM_KERN_ERR	3	/* error conditions */
#define STREM_KERN_WARNING	4	/* warning conditions */
#define STREM_KERN_NOTICE	5	/* normal but significant condition */
#define STREM_KERN_INFO	6	/* informational */
#define STREM_KERN_DEBUG	7	/* debug-level messages */

/* �����ٺ궨�� */
/* tcp start */
#define TCP_STREAM_COUNT_PAR1(a) \
{if (likely(NULL != g_pstTcpStat)) {\
	g_pstTcpStat->a++;\
} }


#define TCP_STREAM_COUNT_PAR2(a, b) \
{if (likely(NULL != g_pstTcpStat)) {\
	g_pstTcpStat->a++;\
	g_pstTcpStat->b++;\
} }

#define TCP_STREAM_TRACK_PAR1(a, b, c, d) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_tcp(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
	} \
} }

#define TCP_STREAM_TRACK_PAR2(a, b, c, d, e) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_tcp(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
		c->e++;\
	} \
} }

/* tcp end */

/* udp start */
#define UDP_STREAM_COUNT_PAR1(a) \
{if (likely(NULL != g_pstUdpStat)) {\
	g_pstUdpStat->a++;\
} }

#define UDP_STREAM_COUNT_PAR2(a, b) \
{if (likely(NULL != g_pstUdpStat)) {\
	g_pstUdpStat->a++;\
	g_pstUdpStat->b++;\
} }
#define UDP_STREAM_TRACK_PAR1(a, b, c, d) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_udp(b, (void **)&c);\
	if ((NULL != c)) {\
		c->d++;\
	} \
} }

#define UDP_STREAM_TRACK_PAR2(a, b, c, d, e) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_udp(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
		c->e++;\
	} \
} }

/* udp end */

/* ip start */
#define IP_STREAM_COUNT_PAR1(a) \
{if (likely(NULL != g_pstIpStat)) {\
	g_pstIpStat->a++;\
} }

#define IP_STREAM_COUNT_PAR2(a, b) \
{if (likely(NULL != g_pstIpStat)) {\
	g_pstIpStat->a++;\
	g_pstIpStat->b++;\
} }

#define IP_STREAM_TRACK_PAR1(a, b, c, d) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_ip(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
	} \
} }

#define IP_STREAM_TRACK_PAR2(a, b, c, d, e) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_ip(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
		c->e++;\
	} \
} }

/* ip end */

/* MAC start */
#define MAC_STREAM_COUNT_PAR1(a) \
{if (likely(NULL != g_pstMacMesgStat)) {\
	g_pstMacMesgStat->a++;\
} }

#define MAC_STREAM_COUNT_PAR2(a, b) \
{if (likely(NULL != g_pstMacMesgStat)) {\
	g_pstMacMesgStat->a++;\
	g_pstMacMesgStat->b++;\
} }


#define MAC_STREAM_TRACK_PAR1(a, b, c, d) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_mac(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
	} \
} }

#define MAC_STREAM_TRACK_PAR2(a, b, c, d, e) \
{if (unlikely((NET_STREAM_FLAG_NUM == a) && (b > NET_STREAM_CFG_INDEXT_MIN_VLAUE))) {\
	net_stream_get_follow_location_in_mac(b, (void **)&c);\
	if (likely(NULL != c)) {\
		c->d++;\
		c->e++;\
	} \
} }

/* MAC end */

typedef struct {
	unsigned int ulStreamSeq; /*	���������	*/
	unsigned int ulRxAll; /*	���յ�����IP������ݰ�	*/
	unsigned int ulRxOk; /*TCP�����ܵĳɹ�������	*/
	unsigned int ulRxErr; /*TCP�����ܵ�ʧ�ܰ�����*/
	unsigned int ulRxChkLocErr; /*101���յ��Ǳ��ص����ݰ�	*/
	unsigned int ulRxCpytoSKBErr; /*102���շ�Ƭ���Ƶ�SKB��ʧ�ܵ����ݰ�	*/
	unsigned int ulRxHeadLenErr; /*103����TCP�ײ������쳣�����ݰ�	*/
	unsigned int ulRxLenErr; /*104����TCP���γ����쳣�����ݰ�*/
	unsigned int ulRxHeadChkSumErr; /*105����TCP�ײ�У����쳣�����ݰ�	*/
	unsigned int ulRxFindTransErr; /*106����δ�ҵ���Ӧ�Ĵ�����ƿ�����ݰ�*/
	unsigned int ulRxFindIPSecErr; /*107���ղ���IPSec�������ݿ�ʧ�ܵ����ݰ�	*/
	unsigned int ulRxFilterErr; /*113���յ������˵������ݰ�*/
	unsigned int ulRxAddBacklogErr; /*113���յ������˵������ݰ�*/
	unsigned int ulRxLISTENErr; /*115���յ�TCP_LISTEN״̬���쳣�����ݰ�	*/
	unsigned int ulRxTcpListenOk;/*���յ�TCP_LISTEN������״̬�����������ݰ�*/
	unsigned int ulRxCheckLenErr; /*119���յ���֤���ĵĳ��Ⱥ�У�����쳣	*/
	/*108���յ�TCP�ײ�����С��Ԥ�ڳ��ȵ����ݰ�*/
	unsigned int ulRxbhashFindIPSecErr;
	unsigned int ulRxbhashLenErr;/*109����bhash�м��鳤�Ⱥ�У���ʧ�ܵ����ݰ�*/
	unsigned int ulRxbhashSumErr;/*109����bhash�м��鳤�Ⱥ�У���ʧ�ܵ����ݰ�*/
	unsigned int ulRxTWRSTErr;/*112����ʵ��TCP_TW_RST״̬ʧ�ܵ����ݰ�*/
	unsigned int ulRxTWACKOk;/*����ʵ��TCP_TW_SYN״̬�ɹ������ݰ�*/
	unsigned int ulRxTWSUCCESSOk;/*����ʵ��TCP_TW_SUCCESS״̬�ɹ������ݰ�*/
	unsigned int ulRxTWSYNOk;/*����ʵ��TCP_TW_SYN״̬�ɹ������ݰ�*/
	unsigned int ulRxEstablishErr;/* ���յ�Establish״̬�·�����������ݰ�*/
	unsigned int ulRxEstablishOk;/* ���յ�Establish״̬�³ɹ������ݰ�*/
	unsigned int ulRxEstablishLenErr;/*���յ�TCP�ײ�����С��Ԥ�ڳ��ȵ����ݰ�*/
	unsigned int ulRxEstablishCopyUserErr; /*���յ����Ƶ��û��ռ�ʧ�ܵ����ݰ�*/
	unsigned int ulRxEstablishLenSumErr;/*���յ����鳤�Ⱥ�У���ʧ�ܵ����ݰ�*/
	unsigned int ulRxEstablishChekPAWSErr;/*���յ�PAWS����ʧ�ܵ����ݰ�*/
	unsigned int ulRxEstablishTcpAckErr;/*���յ�����TcpAckʧ�ܵ����ݰ�*/
	unsigned int ulRxEstablishSeqEqualErr;/*���յ�����seq==end_seq */
	unsigned int ulRxEstablishRxWindowIs0Err;/* ���մ���Ϊ0 */
	/* ���ս������С�ڽ��մ��ڵ���Сֵ  */
	unsigned int ulRxEstablishEndSeqBeforRcvNextErr;
	/* ���ս������С�ڽ��մ��ڵ���Сֵ  */
	unsigned int ulRxEstablishSeqBeforRcvNextErr;
	unsigned int ulRxEstablishRcvWndCloseErr;/* ���մ��ڹر�  */
	unsigned int ulRxProcessErr;/* ���յ�����״̬�·�����������ݰ�*/
	unsigned int ulRxEstablishRxMemErr;/* ���յ�����״̬�·����ڴ����*/
	unsigned int ulRxTcpSynSentErr;/*TCP_SYN_SENT״̬�½���ʧ�ܵ����ݰ�*/
	unsigned int ulRxTcpSynSentOk;/*TCP_SYN_SENT״̬�½��ճɹ������ݰ�*/
	unsigned int ulRxTcpListenSynErr;/*TCP_LISTEN״̬�½���SYNʧ�ܵ����ݰ�*/
	unsigned int ulRxTcpListenSynOk;/*TCP_LISTEN״̬�½���SYN�ɹ������ݰ�*/
	unsigned int ulRxTcpListenRstErr;/*TCP_SYN_SENT״̬�½���RST�����ݰ�*/
	unsigned int ulRxTcpListentAck;/*TCP_SYN_SENT״̬�½���ACK�����ݰ�*/
	unsigned int ulRxTcpSynRecvErr;/*TCP_SYN_RECV״̬�½���ʧ�ܵ����ݰ�*/
	unsigned int ulRxTcpSynRecvOk;/*TCP_SYN_RECV״̬�½��ճɹ������ݰ�*/
	unsigned int ulRxTcpFinWait1Err;/*TCP_FIN_WAIT1״̬�½���ʧ�ܵ����ݰ�*/
	/*TCP_FIN_WAIT1״̬�µ�һ�ν��ճɹ������ݰ�*/
	unsigned int ulRxTcpFinWait1FirstOk;
	/*TCP_FIN_WAIT1״̬�µڶ��ν��ճɹ������ݰ�*/
	unsigned int ulRxTcpFinWait1SecondOk;
	unsigned int ulRxTcpFinWait2Err;/*TCP_FIN_WAIT2״̬�½���ʧ�ܵ����ݰ�*/
	/*TCP_FIN_WAIT2״̬�µڶ��ν��ճɹ������ݰ�*/
	unsigned int ulRxTcpFinWait2Ok;
	unsigned int ulRxTcpLastAckErr;/*TCP_LAST_ACK״̬�½���ʧ�ܵ����ݰ�*/
	unsigned int ulRxTcpLastAckOk;/*TCP_LAST_ACK״̬�½��ճɹ������ݰ�*/
	unsigned int ulRxTcpClosingErr;/*TCP_CLOSING״̬�½���ʧ�ܵ����ݰ�*/
	unsigned int ulRxTcpClosingOk;/*TCP_CLOSING״̬�½��ճɹ������ݰ�*/
	unsigned int ulRxTcpValidateIncomingOk;/*���ú����ɹ������ݰ�*/
	/*TCP_ESTABLISHED״̬�½��ճɹ������ݰ�*/
	unsigned int ulRxTcpEstablishedOk;
	unsigned int  ulRxTcpProessDataQueueOK; /* DataQueue��*/
	unsigned int  ulRxTcpProessAllOK; /* DataQueue��*/
	unsigned int ulTxAll; /*�����յ�����Ӧ�ò�����ݰ�	*/
	unsigned int ulTxOk; /*���ͳɹ���	*/
	unsigned int ulTxErr; /*����ʧ����	*/
	unsigned int ulTxSendmsgSynAloneErr; /*����SYN��Ϣʧ��*/
	unsigned int ulTxSendmsgSynAloneOk; /*����SYN��Ϣ�ɹ�*/
	/* tcp�������⣬�����ڴ治��,socket�쳣�� */
	unsigned int ulTxTcpConditionError;
	unsigned int ulTxConnectErr; /*121���ͽ������ӳ�ʱ�����ݰ�*/
	unsigned int ulTxSocketErr; /*122�����׽��ֽӿڴ���*/
	unsigned int ulTxbufferBeyondErr; /*123���������ڴ����ʧ��	*/
	unsigned int ulTxDistributeSKBErr; /*124���ͷ���SKBʧ��	*/
	unsigned int ulTxCopyToSKBErr; /*	125���͸����û����ݵ�SKBʧ�� */
	unsigned int ulTxMemoryBeyondSKBErr; /*126�������ʹ�õĻ���ﵽ���� */
	unsigned int ulTxNewStorageErr; /*127���ͷ����µĴ���ҳ��ʧ��	*/
	unsigned int ulTxDataCopyErr; /*128�������ݸ����쳣*/
	unsigned int ulTxSegmentedPacketNum; /*����ȫ����Ҫ�ֶε����ݰ��ĸ���*/
	unsigned int ulTxSegmentedPacketSumNum;/*����ȫ����Ҫ�ֶ����ݰ����ֵĶ���*/
	unsigned int ulTxMTUCheckErr; /*130����MTU���԰�ʧ��*/
	unsigned int ulTxCWNDfullErr; /*132����ʱӵ����������*/
	unsigned int ulTxSendwindowNoErr; /*133���͵�ǰ�β���ȫ���ڷ��ʹ�����*/
	unsigned int ulTxNoTXIErr; /*134	���͵�ǰ�β�����������*/
	unsigned int ulTxDelySentErr; /*135���͵�ǰ����ʱ����	*/
	unsigned int ulTxSectionErr; /*136���͵�ǰ�ηֶ�ʧ��*/
	unsigned int ulTxCloneCpErr; /*138�������ݰ����ƻ��¡ʱ����	*/
	unsigned int ulTxQueneXmitErr; /*	139���͵���queue_xmit����ʧ�� */
	unsigned int ulTxConnectDesAddressLenErr; /*140 Ŀ�ĵ�ַ���ȴ��� */
	unsigned int ulTxConnectProtocolErr; /*141Э������Ч������*/
	unsigned int ulTxConnectDestAddressErr; /*142Ŀ�ĵ�ַ������*/
	unsigned int ulTxConnectFindRouteErr; /*143·�ɲ���ʧ��*/
	unsigned int ulTxConnectUseTypeErr; /*144TCPʹ�����ʹ���	*/
	unsigned int ulTxConnectAddEhashErr; /*145������ƿ����ehashʧ��*/
	unsigned int ulTxConnectReFindRouteErr; /*146���²���·��ʧ��*/
	unsigned int ulTxSendSYNErr; /*147����SYN��ʧ��*/
	unsigned int ulTxConnectOk; /*����SYN�γɹ�*/
	unsigned int ulTxConnectMallocErr; /* �����ڴ���� */
	unsigned int ulTxTcpWriteWakeupOk; /*����tcp_write_wakeup�ɹ������ݰ�*/
	unsigned int ulTxTcpMtuProbeOk; /*����tcp_mtu_probe�ɹ������ݰ�*/
	/*����tcp_send_active_reset�ɹ������ݰ�*/
	unsigned int ulTxTcpSendActiveResetOk;
	unsigned int ulTxTcpSendSynackOk; /*����tcp_send_synack�ɹ������ݰ�*/
	unsigned int ulTxTcpSendSynDataOk; /*����tcp_send_syn_data�ɹ������ݰ�*/
	unsigned int ulTxTcpSendAckOk; /*����tcp_send_ack�ɹ������ݰ�*/
	unsigned int ulTxTcpXmitProbeSkbOk; /*����tcp_xmit_probe_skb�ɹ������ݰ�*/
	/*����__tcp_retransmit_skb�ɹ������ݰ�*/
	unsigned int ulTxTcpRetransmitSkbOk;
	unsigned int ulTcpWriteXmitOk; /*����tcp_write_xmit�ɹ������ݰ�*/
	unsigned int ulTxFragmentAll; /*tcp���ڷ�Ƭ����*/
	unsigned int ulTxFinAll; /*tcp��������*/
} TCP_STAT_STRU;

typedef struct {
	unsigned int ulStreamSeq;
	unsigned int ulRxUdpAll;   /*udp_rcv�յ�����ip��ı������� */
	unsigned int ulRxUdpOK;
	unsigned int ulRxUdpErr;
	/*udp_rcv ����udpͷ�ռ�ʱ�ռ䲻���쳣*/
	unsigned int ulRxUdpInSpaceError;
	/*udp_rcv udp��ͷֻ�ǳ�����skbָʾ���Ȳ�һ�� */
	unsigned int ulRxUdpSkbLenErr;
	/*** udp_rcv ���ݰ��ܳ���С��udpͷ����*****/
	unsigned int ulRxUdpLengthTooShort;
	unsigned int ulRxUdpCsumInitErr; /****udp_rcv udp4_csum_init ���� ****/
	unsigned int ulRxUdpInBcastMcast;  /****udp_rcv  �㲥��ಥ ****/
	/****δ�ҵ���Ӧ�����ʱ��ipsec�����Լ��ʧ��****/
	unsigned int ulRxUdpNoSckXfrmInError;
	/***û��socket������£�udp���ĵ�У��ʹ���****/
	unsigned int ulRxUdpNoSckCsumErrors;
	/*****û�ж�Ӧ��socket*****/
	unsigned int ulRxUdpPortNotListen;
	/*****udp_queue_rcv���������full coverage ʧ��****/
	unsigned int ulRxUdpLiteFullCoverageErr;
	unsigned int ulRxUdpLiteSmallCoverageErr;
	/****udp_queue_rcv_skb �а�ȫ���Լ��ʧ�� ****/
	unsigned int ulRxUdpXfrmInError;
	/****udp_queue_rcv_skb  У���ʧ��****/
	unsigned int ulRxUdpQueueRcvSkbCsumErrors;
	/***������ӵ�backlog����ʱ�쳣***/
	unsigned int ulRxUdpSkAddBacklogErr;
	/****_udp_queue_rcv_skb ��Ӷ���ʱ����****/
	unsigned int ulRxUdpRcvBufErrors;
	/***udp_queue_rcv_skb��Ӷ��гɹ�****/
	unsigned int ulRxUdpQueueRcvSkbOk;
	/*****udp_rcvmsg �����Ӷ�����ȡ����skb��*****/
	unsigned int ulRxUdpRcvmsgInDataGrams;
	/***udp_queue_rcv_skb �ҽ�������ʱ������***/
	unsigned int ulRxUdpRcvQueueFull;
	/****__udp_queue_rcv_skb����sock_queue_rcv_skb����ֵС��0****/
	unsigned int ulRxUdpSockQueueRcvSkbErr;
	/* udp_recvmsg queue����***/
	unsigned int ulRxUdpMsgErrQueue;
	/***udp_recvmsg ��У��ͳ���***/
	unsigned int ulRxUdpRecvMsgCsumErrors;
	/***udp_recvmsg�����ݿ���������У���ʱ����***/
	unsigned int ulRxUdpSkbCopyCsumErrors;
	/****udp_recvmsg�п��������в���Ҫ����У��ͣ�����ʧ��****/
	unsigned int ulRxUdpCopyDataGramErr;
	/****udp_recvmsg�п��������в���Ҫ����У��͵Ĵ����Ĳ���!peeked����***/
	unsigned int ulRxUdpCopyDataGramNotPeekedErr;
	unsigned int ulTxUdpSendMsgErr;
	/****udp�����ip_send_skb�ĸ���****/
	unsigned int ulTxUdpOK;
	/****udp�����udp_send_skb�����ĸ���****/
	unsigned int ulTxUdpSkbAll;
	unsigned int ulTxUdpIpSendSkbErr;
	/****udp_sendmsg udp���ͱ��ĳ��ȳ���64k ****/
	unsigned int ulTxUdpMsgOverSize;
	/****udp_sendmsg ������Ϣ***/
	unsigned int ulTxBSDErrMsg;
	/****udp_sendmsg ����ʱpend״̬�쳣****/
	unsigned int ulTxUdpPendStaErr;
	/***socket name��length������ ****/
	unsigned int ulTxUdpMsgNameLenErr;
	/***socket�е�Э���岻֧��***/
	unsigned int ulTxUdpAFNoSupport;
	unsigned int ulTxUdpDPortInval;  /***socket�˿ڲ�����***/
	unsigned int ulTxUdpDAddrInval; /***socket ip ������***/
	unsigned int ulTxUdpConStateError;  /****tcp ����״̬�쳣****/
	unsigned int ulTxUdpSendCmsgFail; /***udp������Ϣ����ʧ��*****/
	unsigned int ulTxIpOutNoRoutes;  /****δ�ҵ�·����Ϣ***/
	unsigned int ulTxUdpAppendDataErr;/****ip_append_dataʧ�ܣ��ͷ�skb****/
	unsigned int ulTxUdpSendNoBufs; /****udp_sendmsg ���ڴ治������*****/
	unsigned int ulTxIpSendSkNoBufs; /****ip_send_skb �ڴ治��****/

} UDP_STAT_STRU;

typedef struct {
	unsigned int ulStreamSeq;
	/****  ip_rcv�����յ����ܰ�������ȥ�ǻ���ģʽ ****/
	unsigned int ulRxIpAll;
	/****   ip�㴫�ݸ�L4  �ı��� ****/
	unsigned int ulRxIpOK;
	/****   ip��ĺ����յ����쳣����****/
	unsigned int ulRxIpErr;
	/*****ip_defrag�еķ�Ƭ��ɵĳ������ĵĸ���****/
	unsigned int ulRxIpFragments;
	/****  ���з�Ƭ���ĵķ��ϳ��ȵķ�Ƭ����****/
	unsigned int ulRxIpFragmentsAll;
	/***����ģʽ���յ�Ŀ�Ĳ��Ǳ��صı��ģ�������ip�����������������****/
	unsigned int ulRxIpToOtherHost;
	/****���������ݰ�������skb_share_check����****/
	unsigned int ulRxIpSkbShareCheckErr;
	/***ip_rcv�����е���pskb_may_pull ���¼��ip���ݰ��Ƿ���Ч����****/
	unsigned int ulRxIpInHdrPskbPullErr;
	/***ip_rcv������ipͷ���ȴ���20���߰汾�Ų�Ϊ4 ****/
	unsigned int ulRxIpInHdrVerOrShortLengthErr;
	/***ip_rcv�����е���pskb_may_pull ��ipͷʵ�ʳ������¼�����ݱ��Ƿ���Ч****/
	unsigned int ulRxIpInHdrRealLengthPskbPullErr;
	/***ip_rcv�����б���ͷУ���ʧ�� ******/
	unsigned int ulRxIpHeadCsumErrors;
	/******ip_rcv �����б���skbָʾ���Ⱥͱ���ͷ���Ȳ�һ��*****/
	unsigned int ulRxIpInTruncatedPkts;
	/*****ip_rcv�����б����ܳ���С�ڱ���ͷ���ȴ���*****/
	unsigned int ulRxIpInLengthTooShort;
	/***ip_rcv�����б���У���ʧ�� ******/
	unsigned int ulRxIpAllLenthCsumErrors;
	unsigned int ulRxIpRouteInputNorefErr;/***ip_route_input_noref���ش���***/
	/***ip_rcv_finish����ip_route_input_noref����·�ɷ��ش���Ϊcross device link *****/
	unsigned int ulRxIpRpFilter;
	/***ip_rcv_finsh���� ipͷ���ȴ���20�ֽ� ****/
	unsigned int ulRxIpInHdrLongLengthErr;
	/****ip_rcv_finish ����·�ɺ�Ϊ�ಥ ******/
	unsigned int ulRxIpInMcast;
	/****ip_rcv_finish ����·�ɺ�Ϊ�ಥ ******/
	unsigned int ulRxIpInBcast;
	/***ip��������·�ɻ����������ת��������ip_forward������ת���ɹ���ʧ�ܵ�����ͳ�� ****/
	unsigned int ulRxIpInForwardAll;
	/****�������ݰ����Ƴ���****/
	unsigned int ulRxIpForwardSkbCowErr;
	unsigned int ulRxIpForErr;
	/***ip_forward������sk����****/
	unsigned int ulRxIpForwardSkErr;
	/****skb_warn_if_lro���ش���*****/
	unsigned int ulRxIpForwardLroErr;
	/***ת��ʱ��ȫУ��ʧ��******/
	unsigned int ulRxIpForwardXfrmCheckErr;
	/****ת��ʱ���ظ���̫��֡��Ŀ�ĵ�ַ���յ����������豸mac��ַ�����****/
	unsigned int ulRxIpForwardPacketHostErr;
	/***����·�ɸ澯ѡ��ok ,�ɹ�����ת������***/
	unsigned int ulRxIpForwardCallRaChain;
	/***��ת�������ݱ�����ʱ��Ϊ0�������ð�*****/
	unsigned int ulRxIpForwardTooManyHops;
	/****����IPsec·��ѡ·��ת������ʧ��****/
	unsigned int ulRxIpXfrm4RouteForwardFail;
	/****���ݰ������ϸ�·��ѡ������ݰ�����һ����������****/
	unsigned int ulRxIpForwardSrFailed;
	/*****���ݰ�����Ŀ��ip��mtu��С����������IP_DF��־λ****/
	unsigned int ulRxIpForwardFragFails;
	/****ip_local_deliver���ϲ㴫��ʱ����ֶα���ʧ�� ******/
	unsigned int ulRxIpReasmFails;
	/****ip_local_deliver_finish ���İ�ȫ����У����� ****/
	unsigned int ulRxXfrmInErrors;
	/*****ip_local_deliver_finish���ϲ㴫�ݱ��ĺ��ϲ㴦��ʧ�� *****/
	unsigned int ulRxIpIpprotHandlerErr;
	/****�ϲ�Э��δע�ᣬ���ұ��ģ�rawʱ***/
	unsigned int ulRxIpNoIpportNotRaw;
	unsigned int ulRxIpRawInDelivers;
	/***ip�����²㷢�͵ı�����****/
	unsigned int ulTxIpOK;
	/*����ip_push_pendingframes��������ip����,����icmp,unicastyreply ping raw*/
	unsigned int ulTxIpPushPendingFrames;
	/****ip_queue_xmit ������ip���ں�������·�ɷ���ʧ��*****/
	unsigned int ulTxIpRouteOutputPortsErr;
	/*****ip_queue_xmit �����У��ϸ�·��Դվ�޷�����*****/
	unsigned int ulTxIpStrictRouteErr;
	unsigned int ulTxIpErr;
	/****ip_fragment �� ��Ƭ���ȹ��� ****/
	unsigned int ulTxIpMsgTooLongFragFails;
	/****����ͳ�ƣ�������ip��Ƭ�������������ĺ�slow_path  �µ�***/
	unsigned int ulTxIpFragCreates;
	/****����У���������� ***/
	unsigned int ulTxIpFragChecksumsCleanupErr;
	/****ip_fragment��Ƭ�����output����ʧ��***/
	unsigned int ulTxIpOutputFragFails;
	unsigned int ulTxSlowPathFragFails;/***slowpath�����з�Ƭ����****/
	unsigned int ulTxIpFragOks; /****���ͷ�Ƭ�ɹ���*****/
	unsigned int ulTxIpFragFails;  /****��Ƭ����ʧ����*****/
	unsigned int ulTxIpOutMcast;  /**ip_finish_output2 �Ķಥͳ��****/
	unsigned int ulTxIpOutBcast;/**ip_finish_output2 �Ĺ㲥ͳ��****/
	/*****ip_finish_output2 ���뱨��ͷ�ռ䲻��****/
	unsigned int ulTxIpSkbHeadroomOutBufErrors;
	unsigned int ulTxIpNoHeaderCaheAndNeighbour;
	unsigned int ulTxIpOut;
	/****������ip_local_out�������㴦��������δ��dst->ouput���õĸ���***/
	unsigned int ulTxIpDstOutputNotHandle;
	unsigned int ulTxIpOutBufErrors; /***��Ƭ�������ڴ治��*****/
	unsigned int ulTxIpIgmpv3All; /***Igmpv3 ������Ŀ*****/
	unsigned int ulTxIpIgmpAll; /***Igmp ������Ŀ*****/
	unsigned int ulTxIpSendResetAll; /***SendReset ������Ŀ*****/
	unsigned int ulTxIpSendPktAll; /***ip_build_and_send_pkt ������Ŀ*****/
	unsigned int ulTxIpQueueXmitAll; /***QueueXmit ������Ŀ*****/
	unsigned int ulTxIpSendSkbAll; /***ip_send_skb ������Ŀ*****/
	unsigned int ulTxIpTunnelXmitAll; /***iptunnel_xmit ������Ŀ*****/
	unsigned int ulTxIpVsTunnelXmitAll; /***ip_vs_tunnel_xmit ������Ŀ*****/
	unsigned int ulTxTeeTg4All; /***tee_tg4 ������Ŀ*****/
	unsigned int ulTxIpPptpXmitAll;
	unsigned int ulTxDnNspSendAll; /***dn_nsp_send ������Ŀ*****/
	unsigned int ulTxDnNspDoDiscAll; /***dn_nsp_do_disc ������Ŀ*****/
	unsigned int ulTxIp6MrForward2All; /***ip6mr_forward2_finish������Ŀ*****/
	unsigned int ulTxIp6LocalOutAll; /***ip6_local_out ������Ŀ*****/
	unsigned int ulTxIp6XmitAll; /***ip6_xmit ������Ŀ*****/
	unsigned int ulTxIp6ForwardAll; /***ip6_forward_finish ������Ŀ*****/
	unsigned int ulTxIpmrForwardAll; /***ipmr_forward_finish ������Ŀ*****/
	/***ip_forward_finish_gso ������Ŀ*****/
	unsigned int ulTxIpForwardFinishGsoAll;
	unsigned int ulTxIpForwardFinishAll; /***ip_forward_finish ������Ŀ*****/
	unsigned int ulTxIpLocalOutAll; /***ip_local_out ������Ŀ*****/
	unsigned int ulTxIpFinishOutPutAll; /***ip_finish_output ������Ŀ*****/
	/***ip_vs_nat_send_or_cont ������Ŀ*****/
	unsigned int ulTxIpVsNatSendOrContAll;
	unsigned int ulTxIpVsSendOrContAll; /***ip_vs_send_or_cont ������Ŀ*****/
	unsigned int ulTxVtiTunnelXmitAll; /***vti_tunnel_xmit ������Ŀ*****/
	unsigned int ulTxMldSendPackAll; /***mld_sendpack ������Ŀ*****/
	unsigned int ulTxIgmp6SendAll; /***igmp6_send ������Ŀ*****/
	unsigned int ulTxNdiscSendSkbAll; /***ndisc_send_skb ������Ŀ*****/
	unsigned int ulTxRawSendHdrincAll; /***raw_send_hdrinc ������Ŀ*****/
	unsigned int ulTxRawv6SendHdrincAll; /***rawv6_send_hdrinc ������Ŀ*****/
	/***xfrm4_output_finish ������Ŀ*****/
	unsigned int ulTxXfrm4OutputFinishAll;
	unsigned int ulTxXfrmOutputResumeAll; /***xfrm_output_resume ������Ŀ*****/
	/***xfrm_policy_queue_process ������Ŀ*****/
	unsigned int ulTxXfrmPolicyQueueProcessAll;
	/***ip_route_input_slow������·�ɲ��ɵ��input��������ֵΪip_err*****/
	unsigned int ulRxRouteUnreachable;
} IP_STAT_STRU;

typedef struct {
	/*���������*/
	unsigned int ulStreamSeq;
	/*��������:���ճɹ����������ܰ���*/
	unsigned int ulRxMacAll;
	/*��������:����IP�ܰ���*/
	unsigned int ulRxAll;
	/*��������:���ճɹ���IP����*/
	unsigned int ulRxOk;
	/*��������:����ʧ���ܰ���*/
	unsigned int ulRxErr;
	/*��������:dpc bus״̬down�Ĵ����*/
	unsigned int ulRxDpcBusDownErr;
	/*��������:dpc bus״̬suspend�Ĵ����*/
	unsigned int ulRxDpcBusSuspendErr;
	/*��������:src��ַΪ�յĴ����*/
	unsigned int ulRxSrcAddrNullErr;
	/*��������:msg���ȵ���0�Ĵ����*/
	unsigned int ulRxMsgLenErr;
	/*��������:pktlenС��msglen�Ĵ����*/
	unsigned int ulRxPktLenErr;
	/*��������:pkt bufferΪ�յĴ����*/
	unsigned int ulRxPktBufNullErr;
	/*��������:ifpΪ�յĴ����*/
	unsigned int ulRxIfpNullErr;
	/*��������:net device not registered�Ĵ����*/
	unsigned int ulRxNetDevNotRegistedErr;
	/*��������:WLFC����header_only���ĵĴ����*/
	unsigned int ulRxWlfcHeaderOnlyPktErr;
	/*��������:Block ping is enable�Ĵ����*/
	unsigned int ulRxBlockPingEnabledErr;
	/*��������:Pkt is taken by WMF�Ĵ����*/
	unsigned int ulRxPktTakenByWmfErr;
	/*��������:Pkt is dropped by WMF�Ĵ����*/
	unsigned int ulRxWmfDropErr;
	/*��������:find sta�Ĵ����*/
	unsigned int ulRxFindStaErr;
	/*��������:DHD_DONOT_FORWARD_BCMEVENT_AS_NETWORK_PKT�Ĵ����*/
	unsigned int ulRxBcmEventNotForwErr;
	/*��������:dump dataΪNDISC_ROUTER_ADVERTISEMENT�Ĵ����*/
	unsigned int ulRxIcmpRouterErr;
	/*��������:dump dataΪNDISC_NEIGHBOUR_ADVERTISEMENT�Ĵ����*/
	unsigned int ulRxIcmpNeighbourErr;
	/*��������:dump dataΪNDISC_NEIGHBOUR_SOLICITATION�Ĵ����*/
	unsigned int ulRxIcmpSolisatationErr;
	/*��������:dhd_rx_frame�ж�ģʽ���ܳɹ��İ���*/
	unsigned int ulRxFrameInterruptOk;
	/*��������:rxthread_enabledʹ������½��ܳɹ��İ���*/
	unsigned int ulRxThreadEnableOk;
	/*��������:dhd_rx_frame NIģʽ���ܳɹ��İ���*/
	unsigned int ulRxFrameNetIfNiOk;
	/*��������:dhd_rx_frame һ��ģʽ���ܳɹ��İ���*/
	unsigned int ulRxNormalNetIfOk;
	/*��������:��rxthread_enabledʹ������¹����ɹ��İ���*/
	unsigned int ulRxSchedRxfOk;
	/*��������:rx��������ɹ��İ���*/
	unsigned int ulRxEnqueueRxfOk;
	/*��������:rx���������ɹ��İ���*/
	unsigned int ulRxDenqueueRxfOk;
	/*��������:rx����NI��ѯģʽ���ܳɹ��İ���*/
	unsigned int ulRxfThreadNetifNiOk;
	/*��������:��ѯ���ܳɹ��İ���*/
	unsigned int ulRxNetIfNiOk;
	/*��������:��wifi�����ݰ�ֱ�ӵ��ù�������netif_rx*/
	unsigned int ulRxNotWifiPktErr;
	/*��������:netpoll_rx����Ϊfalse�Ĵ����*/
	unsigned int ulRxNetpollFalseErr;
	/*��������:netif_rx��static_key_false����������ܳɹ��İ���*/
	unsigned int ulRxNetIfKeyFalseOk;
	/*��������:netif_rx��static_key_false���ؼٽ��ܳɹ��İ���*/
	unsigned int ulRxNetIfKeyTrueOk;
	/*��������:skb��queue���Ȳ���ָ����Χ�ڵĴ����*/
	unsigned int ulRxQueueLenErr;
	/*��������:skb_queue_tail���ܳɹ��İ���*/
	unsigned int ulRxQueueTailOk;
	/*��������:��ʱ�Ĵ����*/
	unsigned int ulRxTimeoutErr;
	/*��������:net_rx_action���ܳɹ��İ���*/
	unsigned int ulRxNetActionOk;
	/*��������:process_backlog���ܳɹ��İ���*/
	unsigned int ulRxProcBacklogOk;
	/*��������:__netif_receive_skb���ܳɹ��İ���*/
	unsigned int ulRxNetifSkbCoreFalseOk;
	/*��������:PfmemallocΪtrue��skb��Э��Ϊȷ�����͵Ĵ����*/
	unsigned int ulRxPfmemlcReserveErr;
	/*��������:netif_receive_skb��skb_orphan_frags�Ĵ����*/
	unsigned int ulRxNetifSkbOrphanFragErr;
	/*��������:netif_receive_skb���ܳɹ����ܰ���*/
	unsigned int ulRxNetifSkbCoreOk;
	/*��������:netif_receive_skb��pt_prevΪ�յĴ����*/
	unsigned int ulRxPtprevNullErr;
	/*�������:���ͳɹ��ܰ���*/
	unsigned int ulTxAll;
	/*�������:���ͳɹ���MAC����*/
	unsigned int ulTxOk;
	/*�������:����ʧ���ܰ���*/
	unsigned int ulTxErr;
	/*�������:���Ͷ���Ϊ�մ����*/
	unsigned int ulTxEnqueueNullErr;
	/*�������:QDISC״̬δ��������*/
	unsigned int ulTxQdiscDeactiveErr;
	/*�������:ֱ��xmit skb�ɹ��İ���*/
	unsigned int ulTxDirectlyXmitOk;
	/*�������:����Ϊ�رջ��߶���Ĵ����*/
	unsigned int ulTxQueueFrozenOrStoppedErr;
	/*�������:pub bus״̬suspend�����*/
	unsigned int ulTxPubBusSuspendErr;
	/*�������:pub bus״̬down��hang_was_sent�����*/
	unsigned int ulTxPubBusDownErr;
	/*�������:bad interface�����*/
	unsigned int ulTxIfIdxBadErr;
	/*�������:skb_realloc_headroomʧ�ܴ����*/
	unsigned int ulTxSkbReallocHeadroomFailErr;
	/*�������:convert to packetʧ�ܴ����*/
	unsigned int ulTxPktFrmNativeFailErr;
	/*�������:clone packetʧ�ܴ����*/
	unsigned int ulTxPktCloneFailErr;
	/*�������:�Ƿ��Ͷ���wmfת���ɹ��İ���*/
	unsigned int ulTxWmfForwardOkErr;
	/*�������:WMF_DROP�����*/
	unsigned int ulTxWmfDropErr;
	/*�������:dhd_start_xmit���ͳɹ�����*/
	unsigned int ulTxStartXmitOk;
	/*�������:����ʱbus״̬down�����*/
	unsigned int ulSendPktBusDownErr;
	/*�������:����ʱbus״̬suspend�����*/
	unsigned int ulSendPktBusSuspendErr;
	/*�������:packet��buffer����С��ETHER_HDR_LEN�����*/
	unsigned int ulTxPktbufLenErr;
	/*�������:packet���滻�����*/
	unsigned int ulTxPktReplacedErr;
	/*�������:���ĵ�flow id����ʧ�ܴ����*/
	unsigned int ulTxFlowidUpdateErr;
	/*�������:����״̬������dhd_sendpkt���ݷ��ͳɹ�����*/
	unsigned int ulTxSendPktPropOk;
	/*�������:����״̬�����·�BCMPCIE��dhd_sendpkt���ݷ��ͳɹ�����*/
	unsigned int ulTxSendPktDataOk;
	/*�������:����״̬�Ǿ�����dhd_sendpkt���ݷ��ͳɹ�����*/
	unsigned int ulTxSendPktOk;
	/*�������:��data����ת������������ʧ�� */
	unsigned int ulTxPutTagErr;
	/*�������:Gso �˲�ʧ�� */
	unsigned int ulTxGsoCheckErr;
	/*�������:Line�˲�ʧ�� */
	unsigned int ulTxLineCheckErr;
	/*�������:Soft�˲�ʧ�� */
	unsigned int ulTxSoftCheckErr;
	/*�������:hard dev ���ʹ��� */
	unsigned int ulTxHardDevSendErr;
	/*�������:Flow ring not intited yet�����*/
	unsigned int ulTxFlowringNotIntitedErr;
	/*�������:Flowid����RingNode״̬�����*/
	unsigned int ulTxFlowidOrRingNodeStateErr;
	/*�������:��flowring status���������equeue a packetʧ�ܴ����*/
	unsigned int ulEqPktStaTxPendErr;
	/*�������:equeue a packetʧ�ܴ����*/
	unsigned int ulEqPktTxPendErr;
	/*�������:dhd_bus_txdata���ݷ��ͳɹ�����*/
	unsigned int ulTxBusDataOk;
	/*�������:���ĵ�flow id�������������кŴ����*/
	unsigned int ulTxFlowidInvalidErr;
	/*�������:flow ring statue not open�����*/
	unsigned int ulTxFlowringStateNotOpenErr;
	/*�������:dhd_bus_schedule_queue�������ݷ��ͳɹ�����*/
	unsigned int ulTxBusScheduleQueueOk;
	/*�������:packet id��Ч�����*/
	unsigned int ulTxPktIdInvalidErr;
	/*�������:HostTx Msgbuf Not available�����*/
	unsigned int ulHostTxBufNotAvailableErr;
	/*�������:dhd_prot_txdataͨ��flowring�����ݷ��ͳɹ�����*/
	unsigned int ulTxProtDataOk;
	/*�������:dhd_bus_txdata(�������ȼ����з���)��Դ����Ĵ����*/
	unsigned int ulTxNoResourceErr;
	/*�������:dhd_bus_txdata(�����ȼ����з���)��Դ�㹻���ͳɹ��ı���*/
	unsigned int ulTxDeqretOk;
	/*�������:dhdstdio_txpkt����ʧ�ܵĴ����*/
	unsigned int ulTxStdioPktFailErr;
	/*�������:dhdstdio_txpkt���ͳɹ�����*/
	unsigned int ulTxStdioPktOk;
	/*�������:dhdstdio_txpkt��BCME_NOTREADY�����*/
	unsigned int ulTxBcmeNotReadyErr;
	/*�������:dhdstdio_txpkt�ı��ĳ���С��0�����*/
	unsigned int ulTxStdioPktLenErr;
	/*�������:dhd_bcmsdh_send_buf���ͳɹ�����*/
	unsigned int ulTxStdioSendBufOk;
	/*�������:dhd_bcmsdh_send_buf����ʧ�ܰ���*/
	unsigned int ulTxStdioSendBufFailErr;
	/*�������:dhd_txcomplete���ͳɹ�����*/
	unsigned int ulTxStdioPktCompleteOk;
	/*�������:dhd_bcmsdh_send_buf�м�⵽���豸�Ĵ����*/
	unsigned int ulTxSendBufNoDevErr;

} MAC_AND_WIFI_STAT_STRU;

#define STREAM_TRACK_FINDSTA_ERR                    1001
#define STREAM_TRACK_BCMEVENT_NOTFORW_ERR           1002
#define STREAM_TRACK_NETPOLL_FAULSE                 1003
#define STREAM_TRACK_QUEUELEN_ERR                   1004
#define STREAM_TRACK_PFMEMLCRESERVE_ERR             1005
#define STREAM_TRACK_NETIFORPHANFRAG_ERR            1006
#define STREAM_TRACK_PTPREVNULL_ERR                 1007
#define STREAM_TRACK_ENQUEUENULL_ERR                1008
#define STREAM_TRACK_QDISCDEACTIVE_ERR              1009
#define STREAM_TRACK_QUEUEFROZENORSTOPPED_ERR       1010
#define STREAM_TRACK_PUBBUSSUSPEND_ERR              1015
#define STREAM_TRACK_PUBBUSDOWN_ERR                 1016
#define STREAM_TRACK_IFIDX_BAD                      1017
#define STREAM_TRACK_SKBREALLOCHEAD_FAIL            1018
#define STREAM_TRACK_PKTFRMNATIVE_FAIL              1019
#define STREAM_TRACK_PKTCLONE_FAIL                  1020
#define STREAM_TRACK_WMFFORWARDOK_ERR               1021
#define STREAM_TRACK_WMFDROP_ERR                    1022
#define STREAM_TRACK_SDPKTBUSDOWN_ERR               1023
#define STREAM_TRACK_SDPKTBUSSUSPEND_ERR            1024
#define STREAM_TRACK_PKTBUFLEN_ERR                  1025
#define STREAM_TRACK_PKTREPLACED_ERR                1026
#define STREAM_TRACK_FLOWIDUPDATED_ERR              1027
#define STREAM_TRACK_RINGNOTINTITED_ERR             1028
#define STREAM_TRACK_FLOWIDRINGSTATE_ERR            1029
#define STREAM_TRACK_EQUEUEPKTSTA_FAIL              1030
#define STREAM_TRACK_EQUEUEPKT_FAIL                 1031
#define STREAM_TRACK_PKTID_INVALID                  1032
#define STREAM_TRACK_HTODMSGBUF_NOTAVAIL            1033
#define STREAM_TRACK_NORESOURCE_ERR                 1034
#define STREAM_TRACK_SRDIOTXPKT_FAIL                1035


extern TCP_STAT_STRU *g_pstTcpStat; /* TCPͳ�Ʊ��� */
extern UDP_STAT_STRU *g_pstUdpStat; /* UDPͳ�Ʊ��� */
extern IP_STAT_STRU *g_pstIpStat; /* Ipͳ�Ʊ��� */
extern MAC_AND_WIFI_STAT_STRU *g_pstMacMesgStat; /* MacAndWifiͳ�Ʊ��� */
extern char *g_pdev;


extern bool net_rcv_stream_judge_follow_in_mac(struct sk_buff *skb,
									unsigned int *puiNetStreamFollowIndex);
extern bool net_rcv_stream_judge_follow_in_tcp(struct sk_buff *skb,
									unsigned int *puiNetStreamFollowIndex);
extern bool net_rcv_stream_judge_follow_in_udp(struct sk_buff *skb,
									unsigned int *puiNetStreamFollowIndex);
extern bool net_out_stream_judge_follow (unsigned int uiLocalIp,
					unsigned int uiLocalPort, unsigned int uiRemoteIp,
					unsigned int uiRemotePort, unsigned int uiProtocolType,
					unsigned int *puiNetStreamFollowIndex);
extern int net_count_data_add(unsigned short usState, unsigned long uiAddNum);
extern int net_count_stream_add(unsigned int uiSteamSeq,
						unsigned short usState, unsigned long uiAddNum);
extern int net_stream_get_follow_location_in_tcp(unsigned int uiSteamSeq,
													void **pvlocation);
extern int net_stream_get_follow_location_in_udp(unsigned int uiSteamSeq,
													void **pvPrintLocal);
extern int net_stream_get_follow_location_in_ip(unsigned int uiSteamSeq,
												void **pvPrintLocal);
extern int net_stream_get_follow_location_in_mac(unsigned int uiSteamSeq,
													void **pvPrintLocal);
extern int net_stream_get_count_location_in_tcp(void **pvlocation);
extern int net_stream_get_count_location_in_udp(void **pvPrintLocal);
extern int net_stream_get_count_location_in_ip(void **pvPrintLocal);
extern int net_stream_get_count_location_in_mac(void **pvPrintLocal);
extern int net_stream_print(int iLevel,  char *format, ...);
extern void net_stream_follow_clear_all(void);


#endif
