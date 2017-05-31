/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hisi_tele_mntn.h
  �� �� ��   : ����
  ��    ��   : hisi_tele_mntn.h
  ��������   : 2014��11��22��
  ����޸�   :
  ��������   : bsp_tele_mntn.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��22��
    ��    ��   : hisi_tele_mntn.h
    �޸�����   : �����ļ�
  2.ע    ��   : ���¼����ļ����ݱ�����ȫ��ͬ
                 vendor\hisi\confidential\lpmcu\include\hisi_tele_mntn.h
                 bootable\bootloader\legacy\include\hisi_tele_mntn.h
                 kernel\include\linux\hisi\hisi_tele_mntn.h

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __HISI_TELE_MNTN_H__
#define __HISI_TELE_MNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ACORE_CPUIDLE_CUR_CPU_NUM       (8)
#define PERI_SLEEP_CUR_STATE_NUM        (5)
#define VOTE_STAT_LOCK                  (1)   /*ͶƱ��������˯*/
#define VOTE_STAT_UNLOCK                (0)   /*ȥͶƱ������˯*/
#define LPMCU_TICKMARK_BUF_SIZE         (32)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*

˵��:

extern int DRV_TELE_MNTN_WRITE_LOG(
            TELE_MNTN_TYPE_ID type_id,
            unsigned int len,
            void *data);

def type_id ��  ���len���� data�������� �Ķ�Ӧ��ϵ:

    TELE_MNTN_DEF_STR ��Ӧ��data�������� �� ���len����:
            U8 tmp[64]
            len = 64 Bytes

    TELE_MNTN_DEF_U8 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U8 tmp0;
                U8 tmp1;
                U8 tmp2;
                U8 tmp3;
                U8 tmp4;
                U8 tmp5;
                U8 tmp6;
                U8 tmp7;
            }
            len = 8 Bytes

    TELE_MNTN_DEF_U16 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U16 tmp0;
                U16 tmp1;
                U16 tmp2;
                U16 tmp3;
                U16 tmp4;
                U16 tmp5;
                U16 tmp6;
                U16 tmp7;
            }
            len = 16 Bytes

    TELE_MNTN_DEF_U32 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U32 tmp0;
                U32 tmp1;
                U32 tmp2;
                U32 tmp3;
                U32 tmp4;
                U32 tmp5;
                U32 tmp6;
                U32 tmp7;
            }
            len = 32 Bytes

    TELE_MNTN_DEF_U64 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U64 tmp0;
                U64 tmp1;
                U64 tmp2;
                U64 tmp3;
            }
            len = 32 Bytes

*/
typedef enum
{
    TELE_MNTN_TYPE_RESERVED = -1,
    /*������;������*/
    TELE_MNTN_NVME_LOGCAT = 0,
    TELE_MNTN_NVME_WAKEUP_ACPU,

    /*Ĭ��type_id ��Ӧ�̶������ݽ������ͺ�Ĭ�ϵ�������󳤶ȣ�
    ������Ĭ�ϵ����ݽ������ͽ�������ģ����ظ�ʹ��*/
    TELE_MNTN_DEF_STR = 5,    /*��˵��*/
    TELE_MNTN_DEF_U8,         /*��˵��*/
    TELE_MNTN_DEF_U16,        /*��˵��*/
    TELE_MNTN_DEF_U32,        /*��˵��*/
    TELE_MNTN_DEF_U64,        /*��˵��*/

    /*��ģ���Զ���type_id ��Ӧ�����ݽ������ͺ����ݳ����ɸ�ģ���Լ�����Ľṹ�������
    ���û�нṹ�嶨�壬������������ʽ����*/
    TELE_MNTN_SLEEPWAKE_CCPU = 15,
    TELE_MNTN_NOTSLEEPREASON_CCPU,
    TELE_MNTN_SLEEPWAKE_MCU,
    TELE_MNTN_NOTSLEEPREASON_MCU,
    TELE_MNTN_PUPD_CCPU,
    TELE_MNTN_WFIFAIL_CCPU,  /*20*/
    TELE_MNTN_PUPD_ACPU,
    TELE_MNTN_WFIFAIL_ACPU,
    TELE_MNTN_PUPD_HIFI,
    TELE_MNTN_WFIFAIL_HIFI,
    TELE_MNTN_CPUIDLE,  /*25*/
    TELE_MNTN_VOTE_CCPU,
    TELE_MNTN_VOTE_MCU,
    TELE_MNTN_ICC_WAKE_ACPU,
    TELE_MNTN_ICC_WAKE_CCPU,
    TELE_MNTN_IPC_MCU,  /*30*/
    TELE_MNTN_DFS_DDR,
    TELE_MNTN_PLI_DDR,
    TELE_MNTN_MAXFREQ_REQ_DDR,
    TELE_MNTN_MINFREQ_REQ_DDR,
    TELE_MNTN_QOS_DDR_MCU,  /*35*/
    TELE_MNTN_QOS_DDR_CCPU,
    TELE_MNTN_QOS_DDR_ACPU,
    TELE_MNTN_DFS_CCPU,
    TELE_MNTN_PLI_CCPU,
    TELE_MNTN_QOS_CCPU,  /*40*/
    TELE_MNTN_DFS_ACPU,
    TELE_MNTN_DRX,
    TELE_MNTN_PLI_ACPU,
    TELE_MNTN_SR_ACPU,
	TELE_MNTN_DFS_GPU,
	TELE_MNTN_RESET_HIFI,
    TELE_MNTN_PUPD_IOMCU,
    TELE_MNTN_WFIFAIL_IOMCU,
    TELE_MNTN_PUPD_REGULATOR,

    TELE_MNTN_TEMPERATURE = 52,

	TELE_MNTN_LPREG_SAVE = 62,
    TELE_MNTN_LPREG_DUMP = 63,
    TELE_MNTN_TYPE_BUTT
}TELE_MNTN_TYPE_ID;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*************************LPMCU telemntn log begin***************************/
typedef struct LPMCU_TELE_MNTN_PU_STRU_S
{
    unsigned int wakeCount;
    unsigned int wakeSrc;
}LPMCU_TELE_MNTN_PU_STRU;

typedef struct LPMCU_TELE_MNTN_PD_STRU_S
{
    unsigned int sleepCount;
    unsigned int sleepFlag;
}LPMCU_TELE_MNTN_PD_STRU;

typedef struct LPMCU_TELE_MNTN_WFIFAIL_STRU_S
{
    unsigned int WFIFailCount;
}LPMCU_TELE_MNTN_WFIFAIL_STRU;

typedef struct LPMCU_TELE_MNTN_PUPD_STRU_S
{
    LPMCU_TELE_MNTN_PD_STRU pdStat;
    LPMCU_TELE_MNTN_PU_STRU puStat;
    LPMCU_TELE_MNTN_WFIFAIL_STRU WFIFailStat;
    unsigned int pdSliceTime;
    unsigned int puSliceTime;
    unsigned int WFIFailSliceTime;
}LPMCU_TELE_MNTN_PUPD_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU_S
{
    int sX;
    unsigned int sleepCount;
    unsigned int wakeCount;
    unsigned int sleepSliceTime;
    unsigned int wakeSliceTime;
    unsigned int wakeSrc0;
    unsigned int wakeSrc1;
}LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU;

typedef struct LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU_S
{
    int canSleepRet;
}LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU_S
{
    LPMCU_TELE_MNTN_SLEEPWAKESTAT_STRU stat;
    LPMCU_TELE_MNTN_NOTSLEEPREASON_STRU notSleepReason;
}LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU;

typedef struct LPMCU_TELE_MNTN_SLEEPWAKE_STRU_S
{
    int sX;
    LPMCU_TELE_MNTN_SLEEPWAKEINFO_STRU info;
}LPMCU_TELE_MNTN_SLEEPWAKE_STRU;


typedef struct LPMCU_TELE_MNTN_DFS_QOSINFO_STRU_S
{
    short cmd_id;
    short qos_id;
    int req_id;
    int ret;
    unsigned int task_id;  /*CCPU:task_id; MCU:core_id*/
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int max_freq;
    unsigned int min_freq;
}LPMCU_TELE_MNTN_DFS_QOSINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_QOS_STRU_S
{
    LPMCU_TELE_MNTN_DFS_QOSINFO_STRU info;
    unsigned int qosSliceTime;
}LPMCU_TELE_MNTN_DFS_QOS_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU_S
{
    unsigned int load;
    unsigned int target_freq;
}LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_POLICY_STRU_S
{
    LPMCU_TELE_MNTN_DFS_POLICYINFO_STRU info;
    unsigned int policySliceTime;
}LPMCU_TELE_MNTN_DFS_POLICY_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU_S
{
    char old_freq;
    char new_freq;
    char tag_freq;
    char id;
}LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_TARGET_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGETINFO_STRU info;
    unsigned int targetSliceTime;
}LPMCU_TELE_MNTN_DFS_TARGET_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_DDR_STRU_S
{
    LPMCU_TELE_MNTN_DFS_QOS_STRU qos;
    LPMCU_TELE_MNTN_DFS_POLICY_STRU policy;
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_DDR_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_ACPU_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_ACPU_STRU;

typedef struct LPMCU_TELE_MNTN_DFS_GPU_STRU_S
{
    LPMCU_TELE_MNTN_DFS_TARGET_STRU target;
}LPMCU_TELE_MNTN_DFS_GPU_STRU;

typedef struct LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU_S
{
    unsigned char ipc_id;
    unsigned char mailbox_id;
    unsigned char obj;  /*��ʾĿ�귽�������շ�*/
    unsigned char mode; /*��ʾ����ģʽ����ͬ�����ջ��첽����*/
    unsigned int data0;
    unsigned int data1;
    unsigned int handle_slice;
}LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU_S
{
    unsigned char ipc_id;
    unsigned char mailbox_id;
    unsigned char obj;  /*��ʾĿ�귽��������Ŀ�ĵ�*/
    unsigned char mode; /*��ʾ����ģʽ*/
    unsigned int msg;
}LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU_S
{
    unsigned char ipc;
    unsigned char mbx;
    unsigned char iclr;
    unsigned char mode;
    unsigned int data0;
    unsigned int data1;
}LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU;

typedef struct LPMCU_TELE_MNTN_IPCSTAT_STRU_S
{
    LPMCU_TELE_MNTN_IPCRECVSTATINFO_STRU recv;
    LPMCU_TELE_MNTN_IPCSENDSTATINFO_STRU send;
    LPMCU_TELE_MNTN_IPCSENDEXCEPTION_STRU exp;
    unsigned int recvSliceTime;
    unsigned int sendSliceTime;
}LPMCU_TELE_MNTN_IPCSTAT_STRU;



typedef struct LPMCU_TELE_MNTN_TICKMARK_STRU_S
{
    unsigned int tick[LPMCU_TICKMARK_BUF_SIZE];

}LPMCU_TELE_MNTN_TICKMARK_STRU;

typedef struct LPMCU_TELE_MNTN_NCORE_PU_STRU_S
{
    unsigned int  state;
    unsigned int  up_cnt;
    unsigned short wake_irq;
    unsigned char wake_mbx_id;
    unsigned char wake_mbx_mode;
    unsigned int wake_mbx_data0;
} LPMCU_TELE_MNTN_NCORE_PU_STRU;

typedef struct LPMCU_TELE_MNTN_NCORE_PD_STRU_S
{
    unsigned int  state;
    unsigned int  dn_cnt;
} LPMCU_TELE_MNTN_NCORE_PD_STRU;

/*hifi/iomcu etc*/
typedef struct LPMCU_TELE_MNTN_NCORE_PUPD_STRU_S
{
    LPMCU_TELE_MNTN_NCORE_PU_STRU pu;
    LPMCU_TELE_MNTN_NCORE_PD_STRU pd;
}LPMCU_TELE_MNTN_NCORE_PUPD_STRU;

typedef struct LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU_S
{
	unsigned char source;
	unsigned char dstatus;
	unsigned char mode;
	unsigned char iclr;
	unsigned int data0;
	unsigned int data1;
} LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU;

typedef struct LPMCU_TELE_MNTN_IOMCU_RESET_STRU_S
{
    LPMCU_TELE_MNTN_MBX_EXP_STATE_STRU mailbox;
    //add vote peri\sys_state state
} LPMCU_TELE_MNTN_IOMCU_RESET_STRU;

typedef struct LPMCU_TELE_MNTN_VOTESTAT_STRU_S
{
    unsigned char stat;             /*VOTE_STAT_LOCK ���� VOTE_STAT_UNLOCK*/
    unsigned char clientId;
    unsigned char stateId;
    unsigned char reserved;
    unsigned int voteMap;
}LPMCU_TELE_MNTN_VOTESTAT_STRU;

typedef struct LPMCU_TELE_MNTN_VOTE_STRU_S
{
    LPMCU_TELE_MNTN_VOTESTAT_STRU voteStat;
    unsigned int sliceTime;
}LPMCU_TELE_MNTN_VOTE_STRU;

typedef struct LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU_S
{
    unsigned short vol;
    short tem;
    unsigned int chan;
}LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU;

typedef struct LPMCU_TELE_MNTN_TEMPERATURE_STRU_S
{
    LPMCU_TELE_MNTN_TEMPERATURE_INFO_STRU info;
    unsigned int temSliceTime;
}LPMCU_TELE_MNTN_TEMPERATURE_STRU;

typedef struct LPMCU_TELE_MNTN_STRU_S
{
    LPMCU_TELE_MNTN_TICKMARK_STRU tickMask;
    LPMCU_TELE_MNTN_PUPD_STRU ccore;
    LPMCU_TELE_MNTN_PUPD_STRU acore;
    LPMCU_TELE_MNTN_SLEEPWAKE_STRU mcu;
    LPMCU_TELE_MNTN_DFS_DDR_STRU dfsDdr;
    LPMCU_TELE_MNTN_DFS_ACPU_STRU dfsAcpu;
    LPMCU_TELE_MNTN_DFS_GPU_STRU dfsGpu;
    LPMCU_TELE_MNTN_IPCSTAT_STRU ipc;
    LPMCU_TELE_MNTN_NCORE_PUPD_STRU hifi;
    LPMCU_TELE_MNTN_NCORE_PUPD_STRU iomcu;
    LPMCU_TELE_MNTN_VOTE_STRU vote[PERI_SLEEP_CUR_STATE_NUM];
    LPMCU_TELE_MNTN_TEMPERATURE_STRU tem;
    LPMCU_TELE_MNTN_IOMCU_RESET_STRU iomcu_rst;
    /*���ڴ˴�����µĽṹ��*/
}LPMCU_TELE_MNTN_STRU;

/*************************LPMCU telemntn log end*****************************/


/*************************ACORE telemntn log begin***************************/
typedef struct ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU_S
{
    unsigned int cpu;
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int min_freq;
    unsigned int max_freq;
}ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU;


typedef struct ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU_S
{
    unsigned int cpu;
    unsigned int tag_freq;
    unsigned int new_freq;
    unsigned int min_freq;
    unsigned int max_freq;
    unsigned char load[ACORE_CPUIDLE_CUR_CPU_NUM];
}ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_BOOSTINFO_STRU info;
    unsigned int boostSliceTime;
}ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_POLICYINFO_STRU info;
    unsigned int policySliceTime;
}ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU;

typedef struct ACORE_TELE_MNTN_DFS_ACPU_STRU_S
{
    ACORE_TELE_MNTN_DFS_ACPU_BOOST_STRU boost;
    ACORE_TELE_MNTN_DFS_ACPU_POLICY_STRU policy;
}ACORE_TELE_MNTN_DFS_ACPU_STRU;

typedef struct ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU_S
{
    short           cmd_id;
    short           qos_id;
    unsigned short  pid;
    unsigned short  ppid;
    int             tag_val;
    unsigned int    new_freq;
    unsigned int    min_freq;
    unsigned int    max_freq;
}ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU;


typedef struct PWC_TELE_MNTN_DFS_DDR_QOS_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_QOSINFO_STRU info;
    unsigned int qosSliceTime;
}ACORE_TELE_MNTN_DFS_DDR_QOS_STRU;

typedef struct ACORE_TELE_MNTN_DFS_DDR_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_QOS_STRU qos;
}ACORE_TELE_MNTN_DFS_DDR_STRU;

typedef struct ACORE_TELE_MNTN_STRU_S
{
    ACORE_TELE_MNTN_DFS_DDR_STRU dfsDdr;
    ACORE_TELE_MNTN_DFS_ACPU_STRU dfsAcpu;
}ACORE_TELE_MNTN_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
/*ע��: ʹ��ǰ�����ж�ָ���Ƿ�Ϊ��*/
extern LPMCU_TELE_MNTN_STRU *p_lpmcu_tele_mntn;
extern LPMCU_TELE_MNTN_STRU *p_fastboot_lpmcu_tele_mntn;
extern ACORE_TELE_MNTN_STRU *p_acore_tele_mntn;
/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : tele_mntn_write_log
 ��������  : ����log�ӿ�
 �������  : TELE_MNTN_TYPE_ID type_id
             u32_t len
             void_t * data
 �������  : ��
 �� �� ֵ  : s32_t
 ���ú���  :
 ��������  :
 ˵    ��  : �ú���һ�δ���len���ֵΪ64�ֽڣ�����lenΪ8�ֽڶ��롣
             δ�����ε���Ӱ�����ܣ�����һ��type_idһ�����̵����ݷ�װ�ɽṹ�壬һ���Դ���telemntn
 ��    ��  : hifi�ϵ磬���������̵�log��¼

             hifi���µ��typeidΪ TELE_MNTN_PUPD_HIFI ��ʾ�ϵ���µ磬���Էֽ�Ϊ�������̣��ϵ���µ硣
             �����ϵ����̣����齫PWC_TELE_MNTN_PU_STRU��������ٵ���ִ��tele_mntn_write_log�ӿڣ�
             ������һ�����̵���ִ�ж��tele_mntn_write_log�ӿڡ�


             typedef struct PWC_TELE_MNTN_PU_STRU_S
             {
                 u32_t  wakeCount;
                 u32_t  wakeSrc0;
                 u32_t  wakeSrc1;
                 u32_t  wakeSrcIPC;
                 u8_t   wakeSrcGPIO[8];
             }PWC_TELE_MNTN_PU_STRU;

     	     typedef struct PWC_TELE_MNTN_PD_STRU_S
     	     {
     	         u32_t  sleepCount;
     	     }PWC_TELE_MNTN_PD_STRU;

             typedef struct PWC_TELE_MNTN_PUPD_STRU_S
             {
                 PWC_TELE_MNTN_PD_STRU pdStat;
                 PWC_TELE_MNTN_PU_STRU puStat; //�ýṹ������log���¼��telemntn��
                 u32_t pdSliceTime;
                 u32_t puSliceTime;  //��ʱ��Ϊ���ؼ�¼ʱ��
             }PWC_TELE_MNTN_PUPD_STRU;

             g_hifi_log = (PWC_TELE_MNTN_PUPD_STRU *)0x25000; //ȫ�ֱ�����ָ��̶��ڴ�ռ�
             s32_t  pwc_power_up_hifi( void_t )
             {
                 //��ά�ɲⲿ�֣��Ƚ�һ���������̵�log��¼������
                 g_hifi_log->puStat.wakeCount++;

                 �ϵ紦����

                 //��ά�ɲⲿ�֣��Ƚ�һ���������̵�log��¼������
                 g_hifi_log->puStat.wakeSrc0 = xxx;
                 g_hifi_log->puStat.wakeSrcIPC = xxx;
                 g_hifi_log->puStat.wakeSrcGPIO = xxx;
                 g_hifi_log->puSliceTime = get_slice_time();

                 //���ô��������̼�¼��telemntn�У�����ʱ����Ϣ
                 (void)tele_mntn_write_log(TELE_MNTN_PUPD_HIFI,sizeof(g_hifi_log->puStat),&(g_hifi_log->puStat));

                 return RET_OK;
             }

 �޸���ʷ      :
  1.��    ��   : 2014��5��19��
    ��    ��   : ���� 00186593
    �޸�����   : �����ɺ���

*****************************************************************************/
#if (defined FASTBOOT_MNTN)
#else
extern int tele_mntn_write_log(TELE_MNTN_TYPE_ID type_id, unsigned int len, const void *data);
#if defined(__CMSIS_RTOS)
extern int tele_mntn_init(void);
extern int tele_mntn_wake_up_acore(void);
#endif
#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hi6xxx_tele_mntn.h */
