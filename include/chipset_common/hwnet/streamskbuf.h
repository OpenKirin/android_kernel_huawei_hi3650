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

/* 配置的index最小值，小于此值为错误码 */
#define NET_STREAM_CFG_INDEXT_MIN_VLAUE 100
/* 定义udp与tcp协议类型 */
#define NET_STREAM_UDP_TYPE 17
#define NET_STREAM_TCP_TYPE 6
/* 流跟踪的魔术字 */
#define NET_STREAM_FLAG_NUM 0xFFAA6688

/* 打印级别 */
#define STREM_KERN_EMERG	0	/* system is unusable */
#define STREM_KERN_ALERT	1	/* action must be taken immediately */
#define STREM_KERN_CRIT	2	/* critical conditions */
#define STREM_KERN_ERR	3	/* error conditions */
#define STREM_KERN_WARNING	4	/* warning conditions */
#define STREM_KERN_NOTICE	5	/* normal but significant condition */
#define STREM_KERN_INFO	6	/* informational */
#define STREM_KERN_DEBUG	7	/* debug-level messages */

/* 流跟踪宏定义 */
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
	unsigned int ulStreamSeq; /*	流跟踪序号	*/
	unsigned int ulRxAll; /*	接收到来自IP层的数据包	*/
	unsigned int ulRxOk; /*TCP输入总的成功包个数	*/
	unsigned int ulRxErr; /*TCP输入总的失败包个数*/
	unsigned int ulRxChkLocErr; /*101接收到非本地的数据包	*/
	unsigned int ulRxCpytoSKBErr; /*102接收分片复制到SKB中失败的数据包	*/
	unsigned int ulRxHeadLenErr; /*103接收TCP首部长度异常的数据包	*/
	unsigned int ulRxLenErr; /*104接收TCP整段长度异常的数据包*/
	unsigned int ulRxHeadChkSumErr; /*105接收TCP首部校验和异常的数据包	*/
	unsigned int ulRxFindTransErr; /*106接收未找到对应的传输控制块的数据包*/
	unsigned int ulRxFindIPSecErr; /*107接收查找IPSec策略数据库失败的数据包	*/
	unsigned int ulRxFilterErr; /*113接收到被过滤掉的数据包*/
	unsigned int ulRxAddBacklogErr; /*113接收到被过滤掉的数据包*/
	unsigned int ulRxLISTENErr; /*115接收到TCP_LISTEN状态下异常的数据包	*/
	unsigned int ulRxTcpListenOk;/*接收到TCP_LISTEN半连接状态下正常的数据包*/
	unsigned int ulRxCheckLenErr; /*119接收到验证报文的长度和校验码异常	*/
	/*108接收到TCP首部长度小于预期长度的数据包*/
	unsigned int ulRxbhashFindIPSecErr;
	unsigned int ulRxbhashLenErr;/*109接收bhash中检验长度和校验和失败的数据包*/
	unsigned int ulRxbhashSumErr;/*109接收bhash中检验长度和校验和失败的数据包*/
	unsigned int ulRxTWRSTErr;/*112接收实现TCP_TW_RST状态失败的数据包*/
	unsigned int ulRxTWACKOk;/*接收实现TCP_TW_SYN状态成功的数据包*/
	unsigned int ulRxTWSUCCESSOk;/*接收实现TCP_TW_SUCCESS状态成功的数据包*/
	unsigned int ulRxTWSYNOk;/*接收实现TCP_TW_SYN状态成功的数据包*/
	unsigned int ulRxEstablishErr;/* 接收到Establish状态下发生错误的数据包*/
	unsigned int ulRxEstablishOk;/* 接收到Establish状态下成功的数据包*/
	unsigned int ulRxEstablishLenErr;/*接收到TCP首部长度小于预期长度的数据包*/
	unsigned int ulRxEstablishCopyUserErr; /*接收到复制到用户空间失败的数据包*/
	unsigned int ulRxEstablishLenSumErr;/*接收到检验长度和校验和失败的数据包*/
	unsigned int ulRxEstablishChekPAWSErr;/*接收到PAWS检验失败的数据包*/
	unsigned int ulRxEstablishTcpAckErr;/*接收到调用TcpAck失败的数据包*/
	unsigned int ulRxEstablishSeqEqualErr;/*接收到调用seq==end_seq */
	unsigned int ulRxEstablishRxWindowIs0Err;/* 接收窗口为0 */
	/* 接收结束序号小于接收窗口的最小值  */
	unsigned int ulRxEstablishEndSeqBeforRcvNextErr;
	/* 接收结束序号小于接收窗口的最小值  */
	unsigned int ulRxEstablishSeqBeforRcvNextErr;
	unsigned int ulRxEstablishRcvWndCloseErr;/* 接收窗口关闭  */
	unsigned int ulRxProcessErr;/* 接收到其他状态下发生错误的数据包*/
	unsigned int ulRxEstablishRxMemErr;/* 接收到其他状态下发生内存错误*/
	unsigned int ulRxTcpSynSentErr;/*TCP_SYN_SENT状态下接收失败的数据包*/
	unsigned int ulRxTcpSynSentOk;/*TCP_SYN_SENT状态下接收成功的数据包*/
	unsigned int ulRxTcpListenSynErr;/*TCP_LISTEN状态下接收SYN失败的数据包*/
	unsigned int ulRxTcpListenSynOk;/*TCP_LISTEN状态下接收SYN成功的数据包*/
	unsigned int ulRxTcpListenRstErr;/*TCP_SYN_SENT状态下接收RST的数据包*/
	unsigned int ulRxTcpListentAck;/*TCP_SYN_SENT状态下接收ACK的数据包*/
	unsigned int ulRxTcpSynRecvErr;/*TCP_SYN_RECV状态下接收失败的数据包*/
	unsigned int ulRxTcpSynRecvOk;/*TCP_SYN_RECV状态下接收成功的数据包*/
	unsigned int ulRxTcpFinWait1Err;/*TCP_FIN_WAIT1状态下接收失败的数据包*/
	/*TCP_FIN_WAIT1状态下第一次接收成功的数据包*/
	unsigned int ulRxTcpFinWait1FirstOk;
	/*TCP_FIN_WAIT1状态下第二次接收成功的数据包*/
	unsigned int ulRxTcpFinWait1SecondOk;
	unsigned int ulRxTcpFinWait2Err;/*TCP_FIN_WAIT2状态下接收失败的数据包*/
	/*TCP_FIN_WAIT2状态下第二次接收成功的数据包*/
	unsigned int ulRxTcpFinWait2Ok;
	unsigned int ulRxTcpLastAckErr;/*TCP_LAST_ACK状态下接收失败的数据包*/
	unsigned int ulRxTcpLastAckOk;/*TCP_LAST_ACK状态下接收成功的数据包*/
	unsigned int ulRxTcpClosingErr;/*TCP_CLOSING状态下接收失败的数据包*/
	unsigned int ulRxTcpClosingOk;/*TCP_CLOSING状态下接收成功的数据包*/
	unsigned int ulRxTcpValidateIncomingOk;/*调用函数成功的数据包*/
	/*TCP_ESTABLISHED状态下接收成功的数据包*/
	unsigned int ulRxTcpEstablishedOk;
	unsigned int  ulRxTcpProessDataQueueOK; /* DataQueue包*/
	unsigned int  ulRxTcpProessAllOK; /* DataQueue包*/
	unsigned int ulTxAll; /*发送收到来自应用层的数据包	*/
	unsigned int ulTxOk; /*发送成功数	*/
	unsigned int ulTxErr; /*发送失败数	*/
	unsigned int ulTxSendmsgSynAloneErr; /*发送SYN消息失败*/
	unsigned int ulTxSendmsgSynAloneOk; /*发送SYN消息成功*/
	/* tcp环境问题，包括内存不够,socket异常等 */
	unsigned int ulTxTcpConditionError;
	unsigned int ulTxConnectErr; /*121发送建立连接超时的数据包*/
	unsigned int ulTxSocketErr; /*122发送套接字接口错误*/
	unsigned int ulTxbufferBeyondErr; /*123发送数据内存操作失败	*/
	unsigned int ulTxDistributeSKBErr; /*124发送分配SKB失败	*/
	unsigned int ulTxCopyToSKBErr; /*	125发送复制用户数据到SKB失败 */
	unsigned int ulTxMemoryBeyondSKBErr; /*126发送输出使用的缓存达到上限 */
	unsigned int ulTxNewStorageErr; /*127发送分配新的储存页面失败	*/
	unsigned int ulTxDataCopyErr; /*128发送数据复制异常*/
	unsigned int ulTxSegmentedPacketNum; /*发送全部需要分段的数据包的个数*/
	unsigned int ulTxSegmentedPacketSumNum;/*发送全部需要分段数据包所分的段数*/
	unsigned int ulTxMTUCheckErr; /*130发送MTU测试包失败*/
	unsigned int ulTxCWNDfullErr; /*132发送时拥塞窗口已满*/
	unsigned int ulTxSendwindowNoErr; /*133发送当前段不完全处在发送窗口内*/
	unsigned int ulTxNoTXIErr; /*134	发送当前段不能立即发送*/
	unsigned int ulTxDelySentErr; /*135发送当前段延时发送	*/
	unsigned int ulTxSectionErr; /*136发送当前段分段失败*/
	unsigned int ulTxCloneCpErr; /*138发送数据包复制或克隆时出错	*/
	unsigned int ulTxQueneXmitErr; /*	139发送调用queue_xmit发送失败 */
	unsigned int ulTxConnectDesAddressLenErr; /*140 目的地址长度错误 */
	unsigned int ulTxConnectProtocolErr; /*141协议族有效性有误*/
	unsigned int ulTxConnectDestAddressErr; /*142目的地址有问题*/
	unsigned int ulTxConnectFindRouteErr; /*143路由查找失败*/
	unsigned int ulTxConnectUseTypeErr; /*144TCP使用类型错误	*/
	unsigned int ulTxConnectAddEhashErr; /*145传输控制块加入ehash失败*/
	unsigned int ulTxConnectReFindRouteErr; /*146重新查找路由失败*/
	unsigned int ulTxSendSYNErr; /*147发送SYN段失败*/
	unsigned int ulTxConnectOk; /*发送SYN段成功*/
	unsigned int ulTxConnectMallocErr; /* 分配内存错误 */
	unsigned int ulTxTcpWriteWakeupOk; /*调用tcp_write_wakeup成功的数据包*/
	unsigned int ulTxTcpMtuProbeOk; /*调用tcp_mtu_probe成功的数据包*/
	/*调用tcp_send_active_reset成功的数据包*/
	unsigned int ulTxTcpSendActiveResetOk;
	unsigned int ulTxTcpSendSynackOk; /*调用tcp_send_synack成功的数据包*/
	unsigned int ulTxTcpSendSynDataOk; /*调用tcp_send_syn_data成功的数据包*/
	unsigned int ulTxTcpSendAckOk; /*调用tcp_send_ack成功的数据包*/
	unsigned int ulTxTcpXmitProbeSkbOk; /*调用tcp_xmit_probe_skb成功的数据包*/
	/*调用__tcp_retransmit_skb成功的数据包*/
	unsigned int ulTxTcpRetransmitSkbOk;
	unsigned int ulTcpWriteXmitOk; /*调用tcp_write_xmit成功的数据包*/
	unsigned int ulTxFragmentAll; /*tcp窗口分片次数*/
	unsigned int ulTxFinAll; /*tcp断链次数*/
} TCP_STAT_STRU;

typedef struct {
	unsigned int ulStreamSeq;
	unsigned int ulRxUdpAll;   /*udp_rcv收到来自ip层的报文总数 */
	unsigned int ulRxUdpOK;
	unsigned int ulRxUdpErr;
	/*udp_rcv 调整udp头空间时空间不足异常*/
	unsigned int ulRxUdpInSpaceError;
	/*udp_rcv udp包头只是长度与skb指示长度不一致 */
	unsigned int ulRxUdpSkbLenErr;
	/*** udp_rcv 数据包总长度小于udp头长度*****/
	unsigned int ulRxUdpLengthTooShort;
	unsigned int ulRxUdpCsumInitErr; /****udp_rcv udp4_csum_init 错误 ****/
	unsigned int ulRxUdpInBcastMcast;  /****udp_rcv  广播或多播 ****/
	/****未找到对应传输块时，ipsec包策略检查失败****/
	unsigned int ulRxUdpNoSckXfrmInError;
	/***没有socket的情况下，udp报文的校验和错误****/
	unsigned int ulRxUdpNoSckCsumErrors;
	/*****没有对应的socket*****/
	unsigned int ulRxUdpPortNotListen;
	/*****udp_queue_rcv针对轻量级full coverage 失败****/
	unsigned int ulRxUdpLiteFullCoverageErr;
	unsigned int ulRxUdpLiteSmallCoverageErr;
	/****udp_queue_rcv_skb 中安全策略检查失败 ****/
	unsigned int ulRxUdpXfrmInError;
	/****udp_queue_rcv_skb  校验和失败****/
	unsigned int ulRxUdpQueueRcvSkbCsumErrors;
	/***数据添加到backlog对列时异常***/
	unsigned int ulRxUdpSkAddBacklogErr;
	/****_udp_queue_rcv_skb 添加队列时出错****/
	unsigned int ulRxUdpRcvBufErrors;
	/***udp_queue_rcv_skb添加队列成功****/
	unsigned int ulRxUdpQueueRcvSkbOk;
	/*****udp_rcvmsg 函数从队列中取出的skb数*****/
	unsigned int ulRxUdpRcvmsgInDataGrams;
	/***udp_queue_rcv_skb 挂接至队列时队列满***/
	unsigned int ulRxUdpRcvQueueFull;
	/****__udp_queue_rcv_skb调用sock_queue_rcv_skb返回值小于0****/
	unsigned int ulRxUdpSockQueueRcvSkbErr;
	/* udp_recvmsg queue错误***/
	unsigned int ulRxUdpMsgErrQueue;
	/***udp_recvmsg 中校验和出错***/
	unsigned int ulRxUdpRecvMsgCsumErrors;
	/***udp_recvmsg中数据拷贝及进行校验和时出错***/
	unsigned int ulRxUdpSkbCopyCsumErrors;
	/****udp_recvmsg中拷贝过程中不需要进行校验和，拷贝失败****/
	unsigned int ulRxUdpCopyDataGramErr;
	/****udp_recvmsg中拷贝过程中不需要进行校验和的错误报文并且!peeked类型***/
	unsigned int ulRxUdpCopyDataGramNotPeekedErr;
	unsigned int ulTxUdpSendMsgErr;
	/****udp层调用ip_send_skb的个数****/
	unsigned int ulTxUdpOK;
	/****udp层调用udp_send_skb发包的个数****/
	unsigned int ulTxUdpSkbAll;
	unsigned int ulTxUdpIpSendSkbErr;
	/****udp_sendmsg udp发送报文长度超过64k ****/
	unsigned int ulTxUdpMsgOverSize;
	/****udp_sendmsg 带外消息***/
	unsigned int ulTxBSDErrMsg;
	/****udp_sendmsg 发包时pend状态异常****/
	unsigned int ulTxUdpPendStaErr;
	/***socket name的length有问题 ****/
	unsigned int ulTxUdpMsgNameLenErr;
	/***socket中的协议族不支持***/
	unsigned int ulTxUdpAFNoSupport;
	unsigned int ulTxUdpDPortInval;  /***socket端口不可用***/
	unsigned int ulTxUdpDAddrInval; /***socket ip 不可用***/
	unsigned int ulTxUdpConStateError;  /****tcp 连接状态异常****/
	unsigned int ulTxUdpSendCmsgFail; /***udp控制信息发送失败*****/
	unsigned int ulTxIpOutNoRoutes;  /****未找到路由信息***/
	unsigned int ulTxUdpAppendDataErr;/****ip_append_data失败，释放skb****/
	unsigned int ulTxUdpSendNoBufs; /****udp_sendmsg 中内存不够错误*****/
	unsigned int ulTxIpSendSkNoBufs; /****ip_send_skb 内存不够****/

} UDP_STAT_STRU;

typedef struct {
	unsigned int ulStreamSeq;
	/****  ip_rcv函数收到的总包数，除去非混杂模式 ****/
	unsigned int ulRxIpAll;
	/****   ip层传递给L4  的报文 ****/
	unsigned int ulRxIpOK;
	/****   ip层的函数收到的异常包数****/
	unsigned int ulRxIpErr;
	/*****ip_defrag中的分片组成的超长报文的个数****/
	unsigned int ulRxIpFragments;
	/****  所有分片报文的符合长度的分片总数****/
	unsigned int ulRxIpFragmentsAll;
	/***混杂模式下收到目的不是本地的报文，不计入ip总数、错包、丢包中****/
	unsigned int ulRxIpToOtherHost;
	/****处理共享数据包出错，由skb_share_check返回****/
	unsigned int ulRxIpSkbShareCheckErr;
	/***ip_rcv函数中调用pskb_may_pull 重新检测ip数据包是否有效错误****/
	unsigned int ulRxIpInHdrPskbPullErr;
	/***ip_rcv函数中ip头长度大于20或者版本号不为4 ****/
	unsigned int ulRxIpInHdrVerOrShortLengthErr;
	/***ip_rcv函数中调用pskb_may_pull 以ip头实际长度重新检测数据报是否有效****/
	unsigned int ulRxIpInHdrRealLengthPskbPullErr;
	/***ip_rcv函数中报文头校验和失败 ******/
	unsigned int ulRxIpHeadCsumErrors;
	/******ip_rcv 函数中报文skb指示长度和报文头长度不一致*****/
	unsigned int ulRxIpInTruncatedPkts;
	/*****ip_rcv函数中报文总长度小于报文头长度错误*****/
	unsigned int ulRxIpInLengthTooShort;
	/***ip_rcv函数中报文校验和失败 ******/
	unsigned int ulRxIpAllLenthCsumErrors;
	unsigned int ulRxIpRouteInputNorefErr;/***ip_route_input_noref返回错误***/
	/***ip_rcv_finish函数ip_route_input_noref查找路由返回错误为cross device link *****/
	unsigned int ulRxIpRpFilter;
	/***ip_rcv_finsh函数 ip头长度大于20字节 ****/
	unsigned int ulRxIpInHdrLongLengthErr;
	/****ip_rcv_finish 查找路由后为多播 ******/
	unsigned int ulRxIpInMcast;
	/****ip_rcv_finish 查找路由后为多播 ******/
	unsigned int ulRxIpInBcast;
	/***ip根据输入路由缓存决定报文转发，调用ip_forward，包含转发成功和失败的所有统计 ****/
	unsigned int ulRxIpInForwardAll;
	/****共享数据包复制出错****/
	unsigned int ulRxIpForwardSkbCowErr;
	unsigned int ulRxIpForErr;
	/***ip_forward调用中sk错误****/
	unsigned int ulRxIpForwardSkErr;
	/****skb_warn_if_lro返回错误*****/
	unsigned int ulRxIpForwardLroErr;
	/***转发时安全校验失败******/
	unsigned int ulRxIpForwardXfrmCheckErr;
	/****转发时承载该以太网帧的目的地址与收到它的网络设备mac地址不相等****/
	unsigned int ulRxIpForwardPacketHostErr;
	/***处理路由告警选项ok ,成功后不再转发数据***/
	unsigned int ulRxIpForwardCallRaChain;
	/***带转发的数据报生存时间为0，丢弃该包*****/
	unsigned int ulRxIpForwardTooManyHops;
	/****进行IPsec路由选路和转发处理失败****/
	unsigned int ulRxIpXfrm4RouteForwardFail;
	/****数据包启用严格路由选项，且数据包的下一跳不是网关****/
	unsigned int ulRxIpForwardSrFailed;
	/*****数据包大于目的ip的mtu大小，且设置了IP_DF标志位****/
	unsigned int ulRxIpForwardFragFails;
	/****ip_local_deliver向上层传递时重组分段报文失败 ******/
	unsigned int ulRxIpReasmFails;
	/****ip_local_deliver_finish 报文安全策略校验错误 ****/
	unsigned int ulRxXfrmInErrors;
	/*****ip_local_deliver_finish向上层传递报文后上层处理失败 *****/
	unsigned int ulRxIpIpprotHandlerErr;
	/****上层协议未注册，并且报文！raw时***/
	unsigned int ulRxIpNoIpportNotRaw;
	unsigned int ulRxIpRawInDelivers;
	/***ip层向下层发送的报文数****/
	unsigned int ulTxIpOK;
	/*调用ip_push_pendingframes函数进行ip发包,包括icmp,unicastyreply ping raw*/
	unsigned int ulTxIpPushPendingFrames;
	/****ip_queue_xmit 函数中ip出口函数查找路由返回失败*****/
	unsigned int ulTxIpRouteOutputPortsErr;
	/*****ip_queue_xmit 函数中，严格路由源站无法满足*****/
	unsigned int ulTxIpStrictRouteErr;
	unsigned int ulTxIpErr;
	/****ip_fragment 中 分片长度过长 ****/
	unsigned int ulTxIpMsgTooLongFragFails;
	/****正常统计，构建的ip分片数，包含正常的和slow_path  下的***/
	unsigned int ulTxIpFragCreates;
	/****净荷校验和重新清除 ***/
	unsigned int ulTxIpFragChecksumsCleanupErr;
	/****ip_fragment分片后调用output发包失败***/
	unsigned int ulTxIpOutputFragFails;
	unsigned int ulTxSlowPathFragFails;/***slowpath过程中分片错误****/
	unsigned int ulTxIpFragOks; /****发送分片成功数*****/
	unsigned int ulTxIpFragFails;  /****分片发送失败数*****/
	unsigned int ulTxIpOutMcast;  /**ip_finish_output2 的多播统计****/
	unsigned int ulTxIpOutBcast;/**ip_finish_output2 的广播统计****/
	/*****ip_finish_output2 申请报文头空间不够****/
	unsigned int ulTxIpSkbHeadroomOutBufErrors;
	unsigned int ulTxIpNoHeaderCaheAndNeighbour;
	unsigned int ulTxIpOut;
	/****报文在ip_local_out中因不满足处理条件，未被dst->ouput调用的个数***/
	unsigned int ulTxIpDstOutputNotHandle;
	unsigned int ulTxIpOutBufErrors; /***分片过程中内存不够*****/
	unsigned int ulTxIpIgmpv3All; /***Igmpv3 发送数目*****/
	unsigned int ulTxIpIgmpAll; /***Igmp 发送数目*****/
	unsigned int ulTxIpSendResetAll; /***SendReset 发送数目*****/
	unsigned int ulTxIpSendPktAll; /***ip_build_and_send_pkt 发送数目*****/
	unsigned int ulTxIpQueueXmitAll; /***QueueXmit 发送数目*****/
	unsigned int ulTxIpSendSkbAll; /***ip_send_skb 发送数目*****/
	unsigned int ulTxIpTunnelXmitAll; /***iptunnel_xmit 发送数目*****/
	unsigned int ulTxIpVsTunnelXmitAll; /***ip_vs_tunnel_xmit 发送数目*****/
	unsigned int ulTxTeeTg4All; /***tee_tg4 发送数目*****/
	unsigned int ulTxIpPptpXmitAll;
	unsigned int ulTxDnNspSendAll; /***dn_nsp_send 发送数目*****/
	unsigned int ulTxDnNspDoDiscAll; /***dn_nsp_do_disc 发送数目*****/
	unsigned int ulTxIp6MrForward2All; /***ip6mr_forward2_finish发送数目*****/
	unsigned int ulTxIp6LocalOutAll; /***ip6_local_out 发送数目*****/
	unsigned int ulTxIp6XmitAll; /***ip6_xmit 发送数目*****/
	unsigned int ulTxIp6ForwardAll; /***ip6_forward_finish 发送数目*****/
	unsigned int ulTxIpmrForwardAll; /***ipmr_forward_finish 发送数目*****/
	/***ip_forward_finish_gso 发送数目*****/
	unsigned int ulTxIpForwardFinishGsoAll;
	unsigned int ulTxIpForwardFinishAll; /***ip_forward_finish 发送数目*****/
	unsigned int ulTxIpLocalOutAll; /***ip_local_out 发送数目*****/
	unsigned int ulTxIpFinishOutPutAll; /***ip_finish_output 发送数目*****/
	/***ip_vs_nat_send_or_cont 发送数目*****/
	unsigned int ulTxIpVsNatSendOrContAll;
	unsigned int ulTxIpVsSendOrContAll; /***ip_vs_send_or_cont 发送数目*****/
	unsigned int ulTxVtiTunnelXmitAll; /***vti_tunnel_xmit 发送数目*****/
	unsigned int ulTxMldSendPackAll; /***mld_sendpack 发送数目*****/
	unsigned int ulTxIgmp6SendAll; /***igmp6_send 发送数目*****/
	unsigned int ulTxNdiscSendSkbAll; /***ndisc_send_skb 发送数目*****/
	unsigned int ulTxRawSendHdrincAll; /***raw_send_hdrinc 发送数目*****/
	unsigned int ulTxRawv6SendHdrincAll; /***rawv6_send_hdrinc 发送数目*****/
	/***xfrm4_output_finish 发送数目*****/
	unsigned int ulTxXfrm4OutputFinishAll;
	unsigned int ulTxXfrmOutputResumeAll; /***xfrm_output_resume 发送数目*****/
	/***xfrm_policy_queue_process 发送数目*****/
	unsigned int ulTxXfrmPolicyQueueProcessAll;
	/***ip_route_input_slow中由于路由不可到达，input函数被赋值为ip_err*****/
	unsigned int ulRxRouteUnreachable;
} IP_STAT_STRU;

typedef struct {
	/*流跟踪序号*/
	unsigned int ulStreamSeq;
	/*数据输入:接收成功所有类型总包数*/
	unsigned int ulRxMacAll;
	/*数据输入:接收IP总包数*/
	unsigned int ulRxAll;
	/*数据输入:接收成功的IP包数*/
	unsigned int ulRxOk;
	/*数据输入:接收失败总包数*/
	unsigned int ulRxErr;
	/*数据输入:dpc bus状态down的错包数*/
	unsigned int ulRxDpcBusDownErr;
	/*数据输入:dpc bus状态suspend的错包数*/
	unsigned int ulRxDpcBusSuspendErr;
	/*数据输入:src地址为空的错包数*/
	unsigned int ulRxSrcAddrNullErr;
	/*数据输入:msg长度等于0的错包数*/
	unsigned int ulRxMsgLenErr;
	/*数据输入:pktlen小于msglen的错包数*/
	unsigned int ulRxPktLenErr;
	/*数据输入:pkt buffer为空的错包数*/
	unsigned int ulRxPktBufNullErr;
	/*数据输入:ifp为空的错包数*/
	unsigned int ulRxIfpNullErr;
	/*数据输入:net device not registered的错包数*/
	unsigned int ulRxNetDevNotRegistedErr;
	/*数据输入:WLFC发送header_only报文的错包数*/
	unsigned int ulRxWlfcHeaderOnlyPktErr;
	/*数据输入:Block ping is enable的错包数*/
	unsigned int ulRxBlockPingEnabledErr;
	/*数据输入:Pkt is taken by WMF的错包数*/
	unsigned int ulRxPktTakenByWmfErr;
	/*数据输入:Pkt is dropped by WMF的错包数*/
	unsigned int ulRxWmfDropErr;
	/*数据输入:find sta的错包数*/
	unsigned int ulRxFindStaErr;
	/*数据输入:DHD_DONOT_FORWARD_BCMEVENT_AS_NETWORK_PKT的错包数*/
	unsigned int ulRxBcmEventNotForwErr;
	/*数据输入:dump data为NDISC_ROUTER_ADVERTISEMENT的错包数*/
	unsigned int ulRxIcmpRouterErr;
	/*数据输入:dump data为NDISC_NEIGHBOUR_ADVERTISEMENT的错包数*/
	unsigned int ulRxIcmpNeighbourErr;
	/*数据输入:dump data为NDISC_NEIGHBOUR_SOLICITATION的错包数*/
	unsigned int ulRxIcmpSolisatationErr;
	/*数据输入:dhd_rx_frame中断模式接受成功的包数*/
	unsigned int ulRxFrameInterruptOk;
	/*数据输入:rxthread_enabled使能情况下接受成功的包数*/
	unsigned int ulRxThreadEnableOk;
	/*数据输入:dhd_rx_frame NI模式接受成功的包数*/
	unsigned int ulRxFrameNetIfNiOk;
	/*数据输入:dhd_rx_frame 一般模式接受成功的包数*/
	unsigned int ulRxNormalNetIfOk;
	/*数据输入:在rxthread_enabled使能情况下挂链成功的包数*/
	unsigned int ulRxSchedRxfOk;
	/*数据输入:rx任务挂链成功的包数*/
	unsigned int ulRxEnqueueRxfOk;
	/*数据输入:rx任务脱链成功的包数*/
	unsigned int ulRxDenqueueRxfOk;
	/*数据输入:rx任务NI轮询模式接受成功的包数*/
	unsigned int ulRxfThreadNetifNiOk;
	/*数据输入:轮询接受成功的包数*/
	unsigned int ulRxNetIfNiOk;
	/*数据输入:非wifi的数据包直接调用公共函数netif_rx*/
	unsigned int ulRxNotWifiPktErr;
	/*数据输入:netpoll_rx返回为false的错包数*/
	unsigned int ulRxNetpollFalseErr;
	/*数据输入:netif_rx中static_key_false返回真而接受成功的包数*/
	unsigned int ulRxNetIfKeyFalseOk;
	/*数据输入:netif_rx中static_key_false返回假接受成功的包数*/
	unsigned int ulRxNetIfKeyTrueOk;
	/*数据输入:skb的queue长度不在指定范围内的错包数*/
	unsigned int ulRxQueueLenErr;
	/*数据输入:skb_queue_tail接受成功的包数*/
	unsigned int ulRxQueueTailOk;
	/*数据输入:超时的错包数*/
	unsigned int ulRxTimeoutErr;
	/*数据输入:net_rx_action接受成功的包数*/
	unsigned int ulRxNetActionOk;
	/*数据输入:process_backlog接受成功的包数*/
	unsigned int ulRxProcBacklogOk;
	/*数据输入:__netif_receive_skb接受成功的包数*/
	unsigned int ulRxNetifSkbCoreFalseOk;
	/*数据输入:Pfmemalloc为true且skb的协议为确定类型的错包数*/
	unsigned int ulRxPfmemlcReserveErr;
	/*数据输入:netif_receive_skb中skb_orphan_frags的错包数*/
	unsigned int ulRxNetifSkbOrphanFragErr;
	/*数据输入:netif_receive_skb接受成功的总包数*/
	unsigned int ulRxNetifSkbCoreOk;
	/*数据输入:netif_receive_skb中pt_prev为空的错包数*/
	unsigned int ulRxPtprevNullErr;
	/*数据输出:发送成功总包数*/
	unsigned int ulTxAll;
	/*数据输出:发送成功的MAC包数*/
	unsigned int ulTxOk;
	/*数据输出:发送失败总包数*/
	unsigned int ulTxErr;
	/*数据输出:发送队列为空错包数*/
	unsigned int ulTxEnqueueNullErr;
	/*数据输出:QDISC状态未激活错包数*/
	unsigned int ulTxQdiscDeactiveErr;
	/*数据输出:直接xmit skb成功的包数*/
	unsigned int ulTxDirectlyXmitOk;
	/*数据输出:队列为关闭或者冻结的错包数*/
	unsigned int ulTxQueueFrozenOrStoppedErr;
	/*数据输出:pub bus状态suspend错包数*/
	unsigned int ulTxPubBusSuspendErr;
	/*数据输出:pub bus状态down或hang_was_sent错包数*/
	unsigned int ulTxPubBusDownErr;
	/*数据输出:bad interface错包数*/
	unsigned int ulTxIfIdxBadErr;
	/*数据输出:skb_realloc_headroom失败错包数*/
	unsigned int ulTxSkbReallocHeadroomFailErr;
	/*数据输出:convert to packet失败错包数*/
	unsigned int ulTxPktFrmNativeFailErr;
	/*数据输出:clone packet失败错包数*/
	unsigned int ulTxPktCloneFailErr;
	/*数据输出:非发送而是wmf转发成功的包数*/
	unsigned int ulTxWmfForwardOkErr;
	/*数据输出:WMF_DROP错包数*/
	unsigned int ulTxWmfDropErr;
	/*数据输出:dhd_start_xmit发送成功包数*/
	unsigned int ulTxStartXmitOk;
	/*数据输出:发包时bus状态down错包数*/
	unsigned int ulSendPktBusDownErr;
	/*数据输出:发包时bus状态suspend错包数*/
	unsigned int ulSendPktBusSuspendErr;
	/*数据输出:packet的buffer长度小于ETHER_HDR_LEN错包数*/
	unsigned int ulTxPktbufLenErr;
	/*数据输出:packet被替换错包数*/
	unsigned int ulTxPktReplacedErr;
	/*数据输出:报文的flow id更新失败错包数*/
	unsigned int ulTxFlowidUpdateErr;
	/*数据输出:发送状态就绪下dhd_sendpkt数据发送成功包数*/
	unsigned int ulTxSendPktPropOk;
	/*数据输出:发送状态就绪下非BCMPCIE的dhd_sendpkt数据发送成功包数*/
	unsigned int ulTxSendPktDataOk;
	/*数据输出:发送状态非就绪下dhd_sendpkt数据发送成功包数*/
	unsigned int ulTxSendPktOk;
	/*数据输出:将data数据转换成线性数据失败 */
	unsigned int ulTxPutTagErr;
	/*数据输出:Gso 核查失败 */
	unsigned int ulTxGsoCheckErr;
	/*数据输出:Line核查失败 */
	unsigned int ulTxLineCheckErr;
	/*数据输出:Soft核查失败 */
	unsigned int ulTxSoftCheckErr;
	/*数据输出:hard dev 发送错误 */
	unsigned int ulTxHardDevSendErr;
	/*数据输出:Flow ring not intited yet错包数*/
	unsigned int ulTxFlowringNotIntitedErr;
	/*数据输出:Flowid或者RingNode状态错包数*/
	unsigned int ulTxFlowidOrRingNodeStateErr;
	/*数据输出:在flowring status正常情况下equeue a packet失败错包数*/
	unsigned int ulEqPktStaTxPendErr;
	/*数据输出:equeue a packet失败错包数*/
	unsigned int ulEqPktTxPendErr;
	/*数据输出:dhd_bus_txdata数据发送成功包数*/
	unsigned int ulTxBusDataOk;
	/*数据输出:报文的flow id大于最大二级队列号错包数*/
	unsigned int ulTxFlowidInvalidErr;
	/*数据输出:flow ring statue not open错包数*/
	unsigned int ulTxFlowringStateNotOpenErr;
	/*数据输出:dhd_bus_schedule_queue队列数据发送成功包数*/
	unsigned int ulTxBusScheduleQueueOk;
	/*数据输出:packet id无效错包数*/
	unsigned int ulTxPktIdInvalidErr;
	/*数据输出:HostTx Msgbuf Not available错包数*/
	unsigned int ulHostTxBufNotAvailableErr;
	/*数据输出:dhd_prot_txdata通过flowring的数据发送成功包数*/
	unsigned int ulTxProtDataOk;
	/*数据输出:dhd_bus_txdata(不按优先级队列发送)资源不足的错包数*/
	unsigned int ulTxNoResourceErr;
	/*数据输出:dhd_bus_txdata(按优先级队列发送)资源足够发送成功的报文*/
	unsigned int ulTxDeqretOk;
	/*数据输出:dhdstdio_txpkt发送失败的错包数*/
	unsigned int ulTxStdioPktFailErr;
	/*数据输出:dhdstdio_txpkt发送成功包数*/
	unsigned int ulTxStdioPktOk;
	/*数据输出:dhdstdio_txpkt的BCME_NOTREADY错包数*/
	unsigned int ulTxBcmeNotReadyErr;
	/*数据输出:dhdstdio_txpkt的报文长度小于0错包数*/
	unsigned int ulTxStdioPktLenErr;
	/*数据输出:dhd_bcmsdh_send_buf发送成功包数*/
	unsigned int ulTxStdioSendBufOk;
	/*数据输出:dhd_bcmsdh_send_buf发送失败包数*/
	unsigned int ulTxStdioSendBufFailErr;
	/*数据输出:dhd_txcomplete发送成功包数*/
	unsigned int ulTxStdioPktCompleteOk;
	/*数据输出:dhd_bcmsdh_send_buf中检测到无设备的错包数*/
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


extern TCP_STAT_STRU *g_pstTcpStat; /* TCP统计变量 */
extern UDP_STAT_STRU *g_pstUdpStat; /* UDP统计变量 */
extern IP_STAT_STRU *g_pstIpStat; /* Ip统计变量 */
extern MAC_AND_WIFI_STAT_STRU *g_pstMacMesgStat; /* MacAndWifi统计变量 */
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
