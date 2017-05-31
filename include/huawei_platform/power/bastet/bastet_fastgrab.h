
/******************************************************************************

				  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : BastetFastGrab.h
  �� �� ��   : ����
  ��	��   : d00173029
  ��������   : 2015��09��30��
  ����޸�   :
  ��������   : ��������������Kernel���¼�
  �����б�   :
  �޸���ʷ   :
  1.��	��   : 2015��09��30��
	��	��   : d00173029
	�޸�����   : �����ļ�

******************************************************************************/
#ifndef __BST_FAST_GRAB_H__
#define __BST_FAST_GRAB_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_FG_MAX_APP_NUMBER	(0x01U)
#define BST_FG_MAX_KW_LEN		(0xFFU) // Current Max keyword lenght is 16
#define BST_FG_MAX_KW_NUMBER	(0x04U)
#define BST_FG_MAX_PID_NUMBER	(0x200U)

#define BST_FG_ROLE_SNDER	(0x01U)
#define BST_FG_ROLE_RCVER	(0x02U)

#define BST_FG_IDX_WECHAT	(0x00U)
#define BST_FG_IDX_ALIPAY	(0x01U)
#define BST_FG_IDX_GTGJ	(0x02U)
#define BST_FG_IDX_INVALID_APP	(0xFFU)
#define BST_FG_FLAG_APP_INFO	(0x01U)

#define BST_FG_FLAG_WECHAT_PUSH	(0x00U)
#define BST_FG_FLAG_WECHAT_RCVD	(0x01U)
#define BST_FG_FLAG_WECHAT_GET	(0x02U)
#define BST_FG_FLAG_WECHAT_PUSH_NEW (0x03U)


#define BST_FG_INVALID_UID	(0)
#define BST_FG_INVALID_INET_ADDR	(0)
#define BST_FG_FLAG_WECHAT_VALID \
	((BST_FG_FLAG_APP_INFO) |\
	(BST_FG_FLAG_WECHAT_RCVD) |\
	(BST_FG_FLAG_WECHAT_GET) |\
	(BST_FG_FLAG_WECHAT_VALID))

#define BST_FG_SetFlag(var, idx)	((var) |= (0x01<<(idx)))
#define BST_FG_ClrFlag(var)	((var)  = 0U)
#define BST_FG_IsUidValid(uid)	((uid) > 10000)
#define BST_FG_IsFlagValid(var, flag)	((var) == (flag))
#define BST_FG_IsAppIdxValid(idx)	((idx) < (BST_FG_MAX_APP_NUMBER))
#define BST_FG_IsKwdIdxValid(idx)	((idx) < (BST_FG_MAX_KW_NUMBER))
#define BST_FG_GetAppIns(idx)	(&g_FastGrabAppInfo[idx])
#define BST_FG_IsCaredSkState(state)	((TCP_CLOSING == (state)) || (TCP_ESTABLISHED == (state)))
#define BST_FG_InitSockSpec(pSock) \
	{ \
		(pSock)->fg_Spec = BST_FG_NO_SPEC; \
		(pSock)->fg_Step = BST_FG_INIT_STEP; \
	}

#define BST_FG_SetSockSpecial(sk, spec) \
	{ \
		bh_lock_sock(sk); \
		(sk)->fg_Spec = (spec); \
		bh_unlock_sock(sk); \
	}

#define BST_FG_SetAccState(sk, value) \
    { \
        (sk)->acc_state = (value); \
    }


#define BST_FG_HOOK_DL_STUB(sk, skb, hrd_len) \
	bastet_mark_hb_reply(sk, skb, hrd_len); \
	{ \
		if (BST_FG_NO_SPEC != (sk)->fg_Spec) { \
			if ((skb)->len > (hrd_len)) { \
				BST_FG_HookPacket((sk), (skb)->data+(hrd_len), (skb)->len-(hrd_len), BST_FG_ROLE_RCVER); \
			} \
		} \
	}


typedef void(*BST_FG_PKT_PROC_T)(struct sock *, uint8_t*, uint32_t uint32_t);

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum {
	CMD_LOAD_KEYWORDS = 0,
	CMD_UPDATE_UID,
	CMD_UPDATE_TID,
	CMD_UPDATE_DSCP,
	CMD_UPDATE_ACC_UID,
} fastgrab_cmd;

typedef enum {
	BST_FG_NO_SPEC = 0,
	BST_FG_WECHAT_PUSH,
	BST_FG_WECHAT_WAIT_HONGBAO,
	BST_FG_WECHAT_HONGBAO,
	BST_FG_SOCK_BUTT,
} bastet_fg_sock_prop;

typedef enum {
	BST_FG_INIT_STEP = 0,
	BST_FG_STEP_BUTT,
} bastet_fg_sock_step;

typedef enum {
	BST_FG_ACC_NORMAL = 0,
	BST_FG_ACC_HIGH,
} bastet_fg_acc_state;


/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
typedef struct {
	uint16_t usCopy; /* The length should be copied from Packet */
	uint16_t usMin; /* The min length of this key packet */
	uint16_t usMax; /* The max length of this key packet */
} BST_FG_PACKET_LEN_STRU;

typedef struct {
	uint16_t usOfst; /* The offset address of the keyworks */
	uint16_t usTotLen; /* The totle length of this keyworks */
	uint8_t aucData[0]; /* The content */
} BST_FG_KEY_WORDS_STRU;

typedef struct {
	uint16_t usRole; /* The comm role of this packet */
	uint16_t usIndex; /* The Keyword Index Name, co. with Kernel */
	BST_FG_PACKET_LEN_STRU stLenPorp; /* Packet length message */
	BST_FG_KEY_WORDS_STRU stKeyWord; /* The keywords of this one */
} BST_FG_KEYWORD_STRU;


typedef struct {
	uid_t lUid; /* The uid of Wechat Application */
	uint16_t usIndex; /* The App Index Name, co. with Kernel */
	BST_FG_KEYWORD_STRU * pstKws[BST_FG_MAX_KW_NUMBER]; /* Keywords arry */
	spinlock_t stLocker; /* The Guard Lock of this unit */
	BST_FG_PKT_PROC_T pfProc; /* The Packet Process Function */
} BST_FG_APP_INFO_STRU;

typedef struct {
	uint16_t usIndex; /* The App Index Name, co. with Kernel */
	uint16_t usKeyLength; /* The Number of key words */
	uint8_t aucKeywords[0]; /* The Arry of keywords */
} BST_FG_KWS_COMM_STRU;

typedef struct {
	uint16_t usIndex; /* The App Index Name, co. with Kernel */
	uid_t lUid; /* The uid of Wechat Application */
} BST_FG_UID_COMM_STRU;

typedef struct {
	uint16_t usIndex; /* The App Index Name, co. with Kernel */
	int16_t usTotle; /* The numberof tids */
	int32_t lTids[0]; /* Tid List */
} BST_FG_TID_COMM_STRU;

typedef struct {
	fastgrab_cmd cmd;
	uint16_t len;
	uint8_t pData[0];
} fastgrab_info;

struct bastet_fg_sock_stru {
	bastet_fg_sock_prop enSpec;
	bastet_fg_sock_step enStep;
};
/*****************************************************************************
  5 �ඨ��
*****************************************************************************/

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
void BST_FG_Init(void);
void BST_FG_IoCtrl(unsigned long arg);
void BST_FG_CheckSockUid(struct sock *pstSock, int state);
uint8_t BST_FG_HookPacket(struct sock *pstSock, uint8_t *pData,
		uint32_t ulLength, uint32_t ulRole);
#if defined(CONFIG_PPPOLAC) || defined(CONFIG_PPPOPNS)
void BST_FG_Hook_Ul_Stub(struct sock *pstSock, struct msghdr *msg);
#endif

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#endif
