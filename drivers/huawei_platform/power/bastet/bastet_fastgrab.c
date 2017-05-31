
/******************************************************************************

				  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bastet_fastgrab.c
  �� �� ��   : ����
  ��	��   : d00173029
  ��������   : 2015��09��30��
  ����޸�   :
  ��������   : �����������Kernel���߼�
  �����б�   :
  �޸���ʷ   :
  1.��	��   : 2015��09��30��
	��	��   : d00173029
	�޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/file.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/fdtable.h>
#include <linux/tcp.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/inet_sock.h>

#include <huawei_platform/power/bastet/bastet_utils.h>

/******************************************************************************
   2 �궨��
******************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_FG_APP_INFO_STRU g_FastGrabAppInfo[BST_FG_MAX_APP_NUMBER];
uid_t      g_CurrntAccUId;

/******************************************************************************
   6 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : BST_FG_Init
 ��������  : ��ʼ������������ؽṹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
void BST_FG_Init(void)
{
	uint16_t usLooper1;
	uint16_t usLooper2;

	for (usLooper1 = 0; usLooper1 < BST_FG_MAX_APP_NUMBER; usLooper1++) {
		g_FastGrabAppInfo[usLooper1].lUid = BST_FG_INVALID_UID;
		g_FastGrabAppInfo[usLooper1].usIndex = usLooper1;
		spin_lock_init(&g_FastGrabAppInfo[usLooper1].stLocker);
		for (usLooper2 = 0; usLooper2 < BST_FG_MAX_KW_NUMBER; usLooper2++)
			g_FastGrabAppInfo[usLooper1].pstKws[usLooper2] = NULL;
	}
	g_CurrntAccUId = BST_FG_INVALID_UID;
}

/*****************************************************************************
 �� �� ��  : BST_FG_ProcWXSock
 ��������  : ����΢�����Socket״̬�仯
 �������  : struct sock *pstSock,  sock�ṹ����
			 int state			  �µ�socket״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static void BST_FG_ProcWXSock(struct sock *pstSock, int state)
{
	/**
	 * If new socket is built, we think it to "waiting" state
	 */
	if (TCP_ESTABLISHED == state) {
		pstSock->fg_Spec = BST_FG_WECHAT_WAIT_HONGBAO;
		BASTET_LOGI("BST_FG_ProcWXSock Set To WAIT_HONGBAO, PTR=%p",
			pstSock);
	}
	/**
	 * Only out put a log. But now wx socket is using "RST" but "Close", so this
	 * can't be printed;
	 */
	else if (TCP_CLOSING == state) {
		if (BST_FG_WECHAT_HONGBAO == pstSock->fg_Spec)
			BASTET_LOGI("BST_FG_ProcWXSock Hongbao_socket is Removed");
	} else {
		return;
	}
}

/*****************************************************************************
 �� �� ��  : BST_FG_ProcWXMatchKeyWord_DL
 ��������  : ����΢��socket���й���������push�ŵ�������
 �������  :
    BST_FG_KEYWORD_STRU *pstKwdIns   ��Ҫƥ��Ĺؼ���
    uint8_t*    pData,   �յ�����������(����skbuff)
    uint32_t    ulLength,   ���ص������Ч���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��     ��   : 2016��12��19��
      ��     ��   : z00371705
     �޸�����   : �����ɺ���
*****************************************************************************/
static bool BST_FG_ProcWXMatchKeyWord_DL(
	BST_FG_KEYWORD_STRU *pstKwdIns,
	uint8_t *pData,
	uint32_t ulLength)
{
    uint64_t usTotLen;

	if (NULL == pstKwdIns)
		return false;
	/**
	* probe log, get the packet head
	*/


	/**
		* match the length of XML to dl packet
		*/
	if ((ulLength > pstKwdIns->stLenPorp.usMax)
		|| (ulLength < pstKwdIns->stLenPorp.usMin))
		return false;

	/**
		* match keywords
		*/
    usTotLen = pstKwdIns->stKeyWord.usTotLen;
	if (0 == memcmp(&pstKwdIns->stKeyWord.aucData[0],
	pData, usTotLen)) {
		return true;
	}
	return false;
}

/*****************************************************************************
 �� �� ��  : BST_FG_ProcWXPacket_DL
 ��������  : ����΢��socket���й���������push�ŵ�������
 �������  :
	struct sock	*pstSock,	sock����
	uint8_t*		pData,	  �յ�����������(����skbuff)
	uint32_t		ulLength,   ���ص������Ч���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket_DL(
	struct sock *pstSock,
	uint8_t *pData,
	uint32_t ulLength)
{
	BST_FG_KEYWORD_STRU *pstKwdIns;
	BST_FG_KEYWORD_STRU *pstKwdInsNew;
	bool         bFound;

	if (BST_FG_WECHAT_PUSH != pstSock->fg_Spec)
		return 0;
	/**
		 * Set the "PUSH"( 0 0 4 ) SIP-Command to be compared object.
		*/
	pstKwdIns = BST_FG_GetAppIns(BST_FG_IDX_WECHAT)
		->pstKws[BST_FG_FLAG_WECHAT_PUSH];
	bFound = BST_FG_ProcWXMatchKeyWord_DL(pstKwdIns,pData,ulLength);
	if( bFound )
	{
		return 1;
	}

	pstKwdInsNew = BST_FG_GetAppIns(BST_FG_IDX_WECHAT)
		->pstKws[BST_FG_FLAG_WECHAT_PUSH_NEW];
	bFound = BST_FG_ProcWXMatchKeyWord_DL(pstKwdInsNew,pData,ulLength);
	if( bFound )
	{
		return 1;
	}
	return 0;
}

/*****************************************************************************
 �� �� ��  : BST_FG_ProcWXPacket_UL
 ��������  : ����΢���������ݹ���
 �������  :
	struct sock *pstSock, sock����
	uint8_t* pData, �յ�����������(ǿ��ת��msg��iov�û��ռ�����)
	uint32_t ulLength, ���ص������Ч���ݳ���
 �������  : ��
 �� �� ֵ  :
	0			   û�йؼ�������Ϣ
	1			   �йؼ�������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket_UL(
	struct sock *pstSock,
	uint8_t *pData,
	uint32_t ulLength)
{
	BST_FG_KEYWORD_STRU *pstKwdIns = NULL;
	char *pcFound = NULL;
	char *pUsrData = NULL;
	struct msghdr *pUsrMsgHdr = NULL;

	/**
	 * If this sock has been matched tob HONGBAO-Server connection,
	 * return 1 direction to let HP data sending.
	 */
	if (BST_FG_WECHAT_HONGBAO == pstSock->fg_Spec) {
		BASTET_LOGI("BST_FG_ProcWXPacket_UL Hongbao_socket is sending");
		return 1;
	}
	/**
	 * If this sock is "WAITING" to be matched state, here will Match the first sending packet
	 * of this sock to find "hongbao"-URL message.
	 * ATENTION: This function only execute matching one time per sock.
	 */
	if (BST_FG_WECHAT_WAIT_HONGBAO == pstSock->fg_Spec) {
		/**
		 * Set the "hongbao"-URL to be compared object.
		 */
		pstKwdIns = BST_FG_GetAppIns(BST_FG_IDX_WECHAT)
			->pstKws[BST_FG_FLAG_WECHAT_GET];
		if (NULL == pstKwdIns)
			return 0;

		/**
		 * too short.
		 */
		if (ulLength < pstKwdIns->stLenPorp.usCopy) {
			BST_FG_SetSockSpecial(pstSock, BST_FG_NO_SPEC);
			return 0;
		}
		/**
		 * Think it to be a common sock firstly.
		 */
		pstSock->fg_Spec = BST_FG_NO_SPEC;
		pUsrData = (char *)kmalloc(
			pstKwdIns->stLenPorp.usCopy, GFP_ATOMIC);
		if (NULL == pUsrData)
			return 0;
		/**
		 * Copy data from usr space. Set the last byte to '0' for strstr input.
		 */
		pUsrMsgHdr = (struct msghdr *)pData;
#if defined(CONFIG_PPPOLAC) || defined(CONFIG_PPPOPNS)
		if (copy_from_user(pUsrData, pUsrMsgHdr->msg_iter.iov->iov_base,
			pstKwdIns->stLenPorp.usCopy)) {
			kfree(pUsrData);
			return 0;
		}
#endif
		pUsrData[pstKwdIns->stLenPorp.usCopy - 1] = 0;
		pcFound = strstr((const char *)pUsrData,
			(const char *)&pstKwdIns->stKeyWord.aucData[0]);
		kfree(pUsrData);

		if (NULL == pcFound) {
			pstSock->fg_Spec = BST_FG_NO_SPEC;
			return 0;
		} else {
			BST_FG_SetSockSpecial(pstSock, BST_FG_WECHAT_HONGBAO);
			BASTET_LOGI("BST_FG_ProcWXPacket_UL Find New Hongbao_socket");
			return 1;
		}
	}
	return 0;
}

/*****************************************************************************
 �� �� ��  : BST_FG_ProcWXPacket
 ��������  : ����΢�ŵĹ���
 �������  :
	struct sock	*pstSock,	sock����
	uint8_t*		pData,	  �յ�������
	uint32_t		ulLength,   ���ص������Ч���ݳ���
	uint32_t		ulRole	  �շ�����
 �������  : ��
 �� �� ֵ  :
	0			   û�йؼ�������Ϣ
	1			   �йؼ�������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket(
	struct sock *pstSock,
	uint8_t *pData,
	uint32_t ulLength,
	uint32_t ulRole)
{
	uint8_t ucRtn = 0;
	/**
	 * Call UL/DL packet proc, according to ROLE
	 */
	if (BST_FG_ROLE_RCVER == ulRole)
		ucRtn = BST_FG_ProcWXPacket_DL(pstSock, pData, ulLength);

	else if (BST_FG_ROLE_SNDER == ulRole)
		ucRtn = BST_FG_ProcWXPacket_UL(pstSock, pData, ulLength);

	return ucRtn;
}

/*****************************************************************************
 �� �� ��  : BST_FG_HookPacket
 �������  : ����ӿڣ������ⲿsocket�շ����ݹ���
	struct sock	*pstSock,	sock����
	uint8_t*		pData,	  �յ�������
	uint32_t		ulLength,   ���ص������Ч���ݳ���
	uint32_t		ulRole	  �շ�����
 �������  : ��
 �� �� ֵ  :
	0			   û�йؼ�������Ϣ
	1			   �йؼ�������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
uint8_t BST_FG_HookPacket(
	struct sock *pstSock,
	uint8_t *pData,
	uint32_t ulLength,
	uint32_t ulRole)
{
	uid_t lSockUid = 0;
	uint8_t ucRtn = 0;
	uint16_t usIdx = BST_FG_IDX_INVALID_APP;

	/**
	 * Get and find the uid in fast-grab message information list.
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 10)
	lSockUid = sock_i_uid(pstSock).val;
#else
	lSockUid = sock_i_uid(pstSock);
#endif
	for (usIdx = 0; usIdx < BST_FG_MAX_APP_NUMBER; usIdx++) {
		if (lSockUid == g_FastGrabAppInfo[usIdx].lUid)
			break;
	}
	if (!BST_FG_IsAppIdxValid(usIdx))
		return 0;

	BASTET_LOGI("BST_FG_Hook1  Length=%d, Role=%d, sk_state=%d",
				 ulLength, ulRole, pstSock->fg_Spec);
	/**
	 * Call different packet proc according the Application Name(Index).
	 */
	switch (usIdx) {
	case BST_FG_IDX_WECHAT:
		ucRtn = BST_FG_ProcWXPacket(pstSock, pData, ulLength, ulRole);
		if (ucRtn)
			post_indicate_packet(BST_IND_FG_KEY_MSG,
				&lSockUid, sizeof(uid_t));
		break;

	default:
		break;
	}
	return ucRtn;
}

/*****************************************************************************
 �� �� ��  : BST_FG_SetHongbaoPushSock
 ��������  : �ҵ�������΢�ŵ�PUSH-Sock
 �������  :
	int32_t	 tid_num,	�����ٸ�pid��Ҫƥ��
	int32_t	*tids		pid������Ϣ�б�
 �������  : ��
 �� �� ֵ  : ƥ����������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static int BST_FG_SetHongbaoPushSock(int32_t tid_num, int32_t *tids)
{
	struct task_struct *pstTask = NULL;
	struct files_struct *pstFiles = NULL;
	struct fdtable *pstFdt = NULL;
	struct sock *pstSock = NULL;
	struct sock *pstSockReg = NULL;
	struct inet_sock *pstInet = NULL;
	uint16_t usLooper = 0;
	int fd = -1;
	uint16_t usFoundPort = 0;
	int lFoundFd = -1;

	/**
	 * use pid to proc.
	 */
	for (usLooper = 0; usLooper < tid_num; usLooper++) {
		/**
		 * Find task message head
		 */
		pstTask = find_task_by_vpid(tids[usLooper]);
		if (NULL == pstTask) {
			BASTET_LOGE("BST_FG_SetHongbaoPushSock pstTask error");
			return -EFAULT;
		}
		/**
		 * Find File sys head according to task
		 */
		pstFiles = pstTask->files;
		if (NULL == pstFiles) {
			BASTET_LOGE("BST_FG_SetHongbaoPushSock pstFiles error");
			return -EFAULT;
		}

		/**
		 * list the fd table
		 */
		pstFdt = files_fdtable(pstFiles);
		for (fd = 0; fd < pstFdt->max_fds; fd++) {
			/**
			 * check the state, ip-addr, port-num of this sock
			 */
			pstSock = get_sock_by_fd_pid(fd, tids[usLooper]);
			if (NULL == pstSock)
				continue;

			if (pstSock->sk_state != TCP_ESTABLISHED) {
				sock_put(pstSock);
				continue;
			}
			if (pstSock->sk_socket->type != SOCK_STREAM) {
				sock_put(pstSock);
				continue;
			}
			pstInet = inet_sk(pstSock);
			if (NULL == pstInet) {
				sock_put(pstSock);
				continue;
			}
			if ((BST_FG_INVALID_INET_ADDR == pstInet->inet_daddr)
				&& (BST_FG_INVALID_INET_ADDR == pstInet->inet_dport)) {
				sock_put(pstSock);
				continue;
			}

			/**
			 * If there no sock be found, set the ptr to tmp-ptr,
			 */
			if (NULL == pstSockReg) {
				lFoundFd = fd;
				usFoundPort = pstInet->inet_sport;
				pstSockReg = pstSock;
			} else {
				/**
				 * If there is a sock has been recorded,we will
				 * check fd/port to judge if it is the same one.
				 * If it's another one, it means that there is
				 * not only one sock in this uid, unsuccessful.
				 */
				if ((fd == lFoundFd)
					&& (usFoundPort == pstInet->inet_sport)) {
					sock_put(pstSock);
					continue;
				} else {
					sock_put(pstSock);
					sock_put(pstSockReg);
					BASTET_LOGI("BST_FG_SetHongbaoPushSock More than One Push Socket Found");
					return 0;
				}
			}
		}
	}
	if (NULL != pstSockReg) {
		/**
		 * record the PUSH special flag to this sock
		 */
		BST_FG_SetSockSpecial(pstSockReg, BST_FG_WECHAT_PUSH);
		sock_put(pstSockReg);
		BASTET_LOGI("BST_FG_SetHongbaoPushSock Found Success!");
	}
	return 0;
}

/*****************************************************************************
 �� �� ��  : BST_FG_SaveKeyword
 ��������  : ����Ӧ��ƥ��ؼ�����Ϣ
 �������  : unsigned long arg  �û��ռ�iovָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static void BST_FG_SaveKeyword(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	BST_FG_APP_INFO_STRU *pstAppIns = NULL;
	BST_FG_KEYWORD_STRU *pstKwdSrc = NULL;
	BST_FG_KEYWORD_STRU *pstKwdDst = NULL;
	BST_FG_KWS_COMM_STRU stKwsComm = {0};
	uint16_t usCopyed = 0;
	uint16_t usLooper = 0;

	/**
	 * Get keyword head information from usr space
	 */
	if (copy_from_user(&stKwsComm, argp, sizeof(BST_FG_KWS_COMM_STRU))) {
		BASTET_LOGE("BST_FG_SaveKeyword copy_from_user stKwsComm error");
		return;
	}
	if (!BST_FG_IsAppIdxValid(stKwsComm.usIndex))
		return;

	BASTET_LOGI("BST_FG_SaveKeyword stKwsComm.usIndex=%d",
		stKwsComm.usIndex);
	pstKwdSrc = (BST_FG_KEYWORD_STRU *)kmalloc(
		sizeof(BST_FG_KEYWORD_STRU), GFP_ATOMIC);
	if (NULL == pstKwdSrc)
		return;

	pstAppIns = BST_FG_GetAppIns(stKwsComm.usIndex);
	usLooper = 0;
	spin_lock_bh(&pstAppIns->stLocker);
	while (1) {
		/**
		 * Get keyword data structure from usr space
		 */
		if (copy_from_user(pstKwdSrc,
			(uint8_t *)argp + usCopyed
			+ sizeof(BST_FG_KWS_COMM_STRU),
			sizeof(BST_FG_KEYWORD_STRU))) {
			BASTET_LOGE("BST_FG_SaveKeyword copy_from_user pstKwdSrc error");
			break;
		}
		pstKwdDst = (BST_FG_KEYWORD_STRU *)kmalloc(
			sizeof(BST_FG_KEYWORD_STRU)
			+ pstKwdSrc->stKeyWord.usTotLen,
			GFP_ATOMIC);
		if (NULL == pstKwdDst)
			break;

		memcpy(pstKwdDst, pstKwdSrc, sizeof(BST_FG_KEYWORD_STRU));
		usCopyed += sizeof(BST_FG_KEYWORD_STRU);
		if (pstKwdSrc->stKeyWord.usTotLen > 0) {
			/**
			 * Get keyword data block from usr space
			 */
			if (pstKwdSrc->stKeyWord.usTotLen > BST_FG_MAX_KW_LEN) {
				break;
			}
			if (copy_from_user(&pstKwdDst->stKeyWord.aucData[0],
				(uint8_t *)argp + usCopyed
				+ sizeof(BST_FG_KWS_COMM_STRU),
				pstKwdSrc->stKeyWord.usTotLen)) {
				BASTET_LOGE("BST_FG_SaveKeyword copy_from_user aucData error");
				kfree(pstKwdDst);
				break;
			}
			usCopyed += pstKwdSrc->stKeyWord.usTotLen;
		}
		if (NULL != pstAppIns->pstKws[usLooper])
			kfree(pstAppIns->pstKws[usLooper]);

		pstAppIns->pstKws[usLooper] = pstKwdDst;
		usLooper += 1;
		if (usLooper >= (uint16_t)BST_FG_MAX_KW_NUMBER)
			break;

		if (usCopyed >= stKwsComm.usKeyLength)
			break;
	}
	kfree(pstKwdSrc);
	spin_unlock_bh(&pstAppIns->stLocker);
}

/*****************************************************************************
 �� �� ��  : BST_FG_SaveUidInfo
 ��������  : �����ӦӦ�õ�UID������Ϣ
 �������  : unsigned long arg  �û��ռ�iovָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static void BST_FG_SaveUidInfo(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	BST_FG_APP_INFO_STRU *pstAppIns = NULL;
	BST_FG_UID_COMM_STRU stUidComm = {0};

	/**
	 * Get uid message structure from usr space
	 */
	if (copy_from_user(&stUidComm, argp, sizeof(BST_FG_UID_COMM_STRU))) {
		BASTET_LOGE("BST_FG_SaveUidInfo copy_from_user error");
		return;
	}
	if (!BST_FG_IsAppIdxValid(stUidComm.usIndex))
		return;

	pstAppIns = BST_FG_GetAppIns(stUidComm.usIndex);
	spin_lock_bh(&pstAppIns->stLocker);
	pstAppIns->lUid = stUidComm.lUid;
	BASTET_LOGI("BST_FG_SaveUidInfo app_index=%d, uid=%d",
		pstAppIns->usIndex, pstAppIns->lUid);
	spin_unlock_bh(&pstAppIns->stLocker);
}

/*****************************************************************************
 �� �� ��  : BST_FG_SaveTidInfo
 ��������  : ��ȡ����UID�йؼ�PID��Ϣ�б�
 �������  : unsigned long arg  �û��ռ�iovָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
static void BST_FG_SaveTidInfo(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	BST_FG_APP_INFO_STRU *pstAppIns = NULL;
	int32_t *plTids = NULL;
	BST_FG_TID_COMM_STRU stTidComm = {0};
	int32_t lTotlen = 0;

	/**
	 * Get tid message structure from usr space
	 */
	if (copy_from_user(&stTidComm, argp, sizeof(BST_FG_TID_COMM_STRU))) {
		BASTET_LOGE("BST_FG_SaveTidInfo copy_from_user stTidComm error");
		return;
	}
	if (!BST_FG_IsAppIdxValid(stTidComm.usIndex))
		return;
	if ((uint32_t)stTidComm.usTotle > BST_FG_MAX_PID_NUMBER) { /*lint !e571*/
		return;
	}

	lTotlen = stTidComm.usTotle * sizeof(int32_t);
	plTids = (int32_t *)kmalloc(lTotlen, GFP_ATOMIC);
	if (NULL == plTids)
		return;

	/**
	 * Get tid list from usr space
	 */
	if (copy_from_user(plTids, (uint8_t *)argp
		+ sizeof(BST_FG_TID_COMM_STRU), lTotlen)) {
		BASTET_LOGE("BST_FG_SaveTidInfo copy_from_user plTids error");
		kfree(plTids);
		return;
	}
	pstAppIns = BST_FG_GetAppIns(stTidComm.usIndex);
	spin_lock_bh(&pstAppIns->stLocker);

	if (!BST_FG_IsUidValid(pstAppIns->lUid)) {
		spin_unlock_bh(&pstAppIns->stLocker);
		kfree(plTids);
		return;
	}
	switch (stTidComm.usIndex) {
	case BST_FG_IDX_WECHAT:
		/**
		 * If wechat, find the push socket according the pid message
		 */
		BST_FG_SetHongbaoPushSock(stTidComm.usTotle, plTids);
		break;

	default:
		break;
	}
	kfree(plTids);
	spin_unlock_bh(&pstAppIns->stLocker);
}

/*****************************************************************************
 �� �� ��  : BST_FG_SaveTidInfo
 ��������  : ��ȡ��ǰdscpֵ
 �������  : unsigned long arg  �û��ռ�iovָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2016��06��14��
	  ��	��   : l00180987
	  �޸�����   : �����ɺ���
*****************************************************************************/
extern int g_FastGrabDscp;
static void BST_FG_SaveDscpInfo(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int lDscp = 0;

	/**
	 * Get dscp message from usr space
	 */
	if (copy_from_user(&lDscp, argp, sizeof(lDscp))) {
		BASTET_LOGE("BST_FG_SaveDscpInfo copy_from_user for dscp error");
		return;
	}

	g_FastGrabDscp = lDscp;

	return;
}

/*****************************************************************************
 �� �� ��  : BST_FG_Update_Acc
 ��������  : �ϲ�֪ͨ����
 �������  : lUid Ӧ�õ�uid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��     ��   : 2016��12��13��
      ��     ��   : z00371705
      �޸�����   : �����ɺ���
*****************************************************************************/

static void BST_FG_Update_Acc(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	uid_t      lUid = 0;

	/**
	 * Get dscp message from usr space
	 */
	if (copy_from_user(&lUid, argp, sizeof(lUid))) {
		BASTET_LOGE("BST_FG_Add_AccUId copy_from_user for uid error\n");
		return;
	}

	g_CurrntAccUId = lUid;


	return;
}



/*****************************************************************************
 �� �� ��  : BST_FG_Check_AccUid
 ��������  : ����������ݰ��Ƿ�Ҫ����
 �������  : lUid Ӧ�õ�uid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��     ��   : 2016��12��13��
      ��     ��   : z00371705
      �޸�����   : �����ɺ���
*****************************************************************************/

static bool BST_FG_Check_AccUid(uid_t lUid)
{
	if(!BST_FG_IsUidValid(lUid))
	{
		return false;
	}

	if( g_CurrntAccUId == lUid )
	{
		return true;
	}
	return false;
}


#if defined(CONFIG_PPPOLAC) || defined(CONFIG_PPPOPNS)
/*****************************************************************************
 �� �� ��  : BST_FG_Hook_Ul_Stub
 ��������  : ��ȡ�������ݰ�
 �������  : struct sock *pstSock  socket����
                           struct msghdr *msg   ���͵���Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��12��13��
      ��    ��   : z00371705
      �޸�����   : �����ɺ���
*****************************************************************************/

void BST_FG_Hook_Ul_Stub(struct sock *pstSock, struct msghdr *msg)
{
	uid_t lSockUid;
	bool  bFound;

	if(( NULL == pstSock ) || ( NULL == msg ))
	{
		return ;
	}

	/*if the socket has matched keyword, keep acc always until socket destruct*/
	if ( BST_FG_WECHAT_HONGBAO == pstSock->fg_Spec )
	{
		BST_FG_SetAccState( pstSock,BST_FG_ACC_HIGH );
		return;
	}

	/*if matched keyword, accelerate socket*/
	if (BST_FG_NO_SPEC != pstSock->fg_Spec) 
	{
		if (BST_FG_HookPacket(pstSock, (uint8_t *)msg, (uint32_t)(msg->msg_iter.iov->iov_len), BST_FG_ROLE_SNDER)) 
		{
			BST_FG_SetAccState( pstSock, BST_FG_ACC_HIGH );
			return;
		}
	}

	/**
	 * if uid equals current acc uid, accelerate it,else stop it
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 10)
	lSockUid = sock_i_uid(pstSock).val;
#else
	lSockUid = sock_i_uid(pstSock);
#endif
	bFound  = BST_FG_Check_AccUid(lSockUid);
	if(bFound)
	{
		BST_FG_SetAccState(pstSock, BST_FG_ACC_HIGH );
	}
	else
	{
		BST_FG_SetAccState(pstSock, BST_FG_ACC_NORMAL );
	}
	return;
}

#endif


/*****************************************************************************
 �� �� ��  : BST_FG_IoCtrl
 ��������  : Fast-grab��������IoCtrl�ӿ�
 �������  : unsigned long arg  �û��ռ�iovָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
void BST_FG_IoCtrl(unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	fastgrab_info stIoCmd;

	if (NULL == argp)
		return;

	/**
	 * Copy io ctrl message of fast-grab from usr space.
	 */
	if (copy_from_user(&stIoCmd, argp, sizeof(fastgrab_info))) {
		BASTET_LOGE("BST_FG_IoCtrl copy_from_user error");
		return;
	}
	BASTET_LOGI("BST_FG_IoCtrl command=%d, msg_len=%d",
		stIoCmd.cmd, stIoCmd.len);

	/**
	 * Call branched function according to the fast-grab command.
	 */
	switch (stIoCmd.cmd) {
	case CMD_LOAD_KEYWORDS:
		BST_FG_SaveKeyword(arg + sizeof(fastgrab_info));
		break;
	case CMD_UPDATE_UID:
		BST_FG_SaveUidInfo(arg + sizeof(fastgrab_info));
		break;
	case CMD_UPDATE_TID:
		BST_FG_SaveTidInfo(arg + sizeof(fastgrab_info));
		break;
	case CMD_UPDATE_DSCP:
		BST_FG_SaveDscpInfo(arg + sizeof(fastgrab_info));
		break;
	case CMD_UPDATE_ACC_UID:
		BST_FG_Update_Acc(arg + sizeof(fastgrab_info));
		break;
	default:
		break;
	}
}

/*****************************************************************************
 �� �� ��  : BST_FG_CheckSockUid
 ��������  : ����uid��ص�socket״̬�仯��Ϣ
 �������  : struct sock *pstSock,  sock�ṹ����
			 int state			  �µ�socket״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
	1.��	��   : 2015��09��30��
	  ��	��   : d00173029
	  �޸�����   : �����ɺ���
*****************************************************************************/
void BST_FG_CheckSockUid(struct sock *pstSock, int state)
{
	uid_t lUid = BST_FG_INVALID_UID;
	uint16_t usIdx = BST_FG_IDX_INVALID_APP;

	/**
	 * Judge the state if it's should be cared.
	 */
	if (!BST_FG_IsCaredSkState(state))
		return;

	/**
	 * Reset the sock fg special flag to inited state.
	 */
	BST_FG_InitSockSpec(pstSock);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 10)
	lUid = sock_i_uid(pstSock).val;
#else
	lUid = sock_i_uid(pstSock);
#endif
	if (!BST_FG_IsUidValid(lUid))
		return;

	/**
	 * Find the application name(index) according to uid.
	 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 1, 10)
	lUid = sock_i_uid(pstSock).val;
#else
	lUid = sock_i_uid(pstSock);
#endif
	for (usIdx = 0; usIdx < BST_FG_MAX_APP_NUMBER; usIdx++) {
		if (lUid == g_FastGrabAppInfo[usIdx].lUid) {
			BASTET_LOGI("BST_FG_CheckSockUid Cared Uid Found, uid=%d",
				lUid);
			post_indicate_packet(BST_IND_FG_UID_SOCK_CHG,
				&lUid, sizeof(uid_t));
			break;
		}
	}
	if (!BST_FG_IsAppIdxValid(usIdx))
		return;

	BASTET_LOGI("BST_FG_CheckSockUid AppIdx=%d ", usIdx);
	/**
	 * Call branched function of different application.
	 */
	switch (usIdx) {
	case BST_FG_IDX_WECHAT:
		BST_FG_ProcWXSock(pstSock, state);
		break;

	default:
		break;
	}
}
