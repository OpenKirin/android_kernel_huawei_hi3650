


#ifndef __DRV_MAILBOX_CFG_H__
#define __DRV_MAILBOX_CFG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "hifi_lpp.h"
#include "mdrv_ipc_enum.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ����ԴCPU �� Ŀ��CPU������ͨ��, ÿͨ����Ӧ���������仺�� */

/* ����������ö����ĺ궨�� */
#define MAILBOX_CHANNEL_BEGIN(src, dst) \
    enum MAILBOX_CHANNEL_##src##2##dst##_ENUM \
    { \
        MAILBOX_CHANNEL_##src##2##dst##_RSERVED = -1,

#define MAILBOX_CHANNEL_ITEM(src, dst, channel)  \
    MAILBOX_CHANNEL_##src##2##dst##_##channel

#define MAILBOX_CHANNEL_END(src, dst) \
        MAILBOX_CHANNEL_##src##2##dst##_BUTT \
    };

/* CCPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(CCPU, HIFI)
    /* ���¸�ö�����������, ����: MAILBOX_CHANNEL_CCPU2HIFI_DEFAULT */
    MAILBOX_CHANNEL_ITEM(CCPU, HIFI, MSG),
MAILBOX_CHANNEL_END(CCPU, HIFI)

/* CCPU -> MCU */
MAILBOX_CHANNEL_BEGIN(CCPU, MCU)
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, MCU, IFC),
MAILBOX_CHANNEL_END(CCPU, MCU)

/* CCPU -> ACPU */
MAILBOX_CHANNEL_BEGIN(CCPU, ACPU)
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(CCPU, ACPU, IFC),
MAILBOX_CHANNEL_END(CCPU, ACPU)

/* ACPU -> CCPU */
MAILBOX_CHANNEL_BEGIN(ACPU, CCPU)
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, CCPU, IFC),
MAILBOX_CHANNEL_END(ACPU, CCPU)

/* ACPU -> MCU */
MAILBOX_CHANNEL_BEGIN(ACPU, MCU)
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, MSG),
    MAILBOX_CHANNEL_ITEM(ACPU, MCU, IFC),
MAILBOX_CHANNEL_END(ACPU, MCU)

/* ACPU -> HIFI */
MAILBOX_CHANNEL_BEGIN(ACPU, HIFI)
    MAILBOX_CHANNEL_ITEM(ACPU, HIFI, MSG),
MAILBOX_CHANNEL_END(ACPU, HIFI)

/* HIFI -> ACPU */
MAILBOX_CHANNEL_BEGIN(HIFI, ACPU)
    MAILBOX_CHANNEL_ITEM(HIFI, ACPU, MSG),
MAILBOX_CHANNEL_END(HIFI, ACPU)

/* HIFI -> CCPU */
MAILBOX_CHANNEL_BEGIN(HIFI, CCPU)
    MAILBOX_CHANNEL_ITEM(HIFI, CCPU, MSG),
MAILBOX_CHANNEL_END(HIFI, CCPU)

/* HIFI -> BBE16 */
MAILBOX_CHANNEL_BEGIN(HIFI, BBE16)
    MAILBOX_CHANNEL_ITEM(HIFI, BBE16, MSG),
MAILBOX_CHANNEL_END(HIFI, BBE16)

/* MCU -> ACPU */
MAILBOX_CHANNEL_BEGIN(MCU, ACPU)
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, ACPU, IFC),
MAILBOX_CHANNEL_END(MCU, ACPU)

/* MCU -> CCPU */
MAILBOX_CHANNEL_BEGIN(MCU, CCPU)
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, MSG),
    MAILBOX_CHANNEL_ITEM(MCU, CCPU, IFC),
MAILBOX_CHANNEL_END(MCU, CCPU)

/* BBE16 -> HIFI */
MAILBOX_CHANNEL_BEGIN(BBE16, HIFI)
    MAILBOX_CHANNEL_ITEM(BBE16, HIFI, MSG),
MAILBOX_CHANNEL_END(BBE16, HIFI)

/* ����SI����, �����Ķ����� */
enum MAILBOX_GAP_FOR_SI_PARSE {MAILBOX_GAP_FOR_SI_BUTT};

#define MAILBOX_ID_SRC_CPU_OFFSET       (24)        /*�ʼ�ID�е�ԴCPU ID bitλƫ�Ƶ�ַ*/
#define MAILBOX_ID_DST_CPU_OFFSET       (16)        /*�ʼ�ID�е�ԴCPU ID bitλƫ�Ƶ�ַ*/
#define MAILBOX_ID_CHANNEL_OFFSET       (8)         /*�ʼ�ID�������ڴ�ͨ�� ID bitλƫ�Ƶ�ַ*/

/* �ʱ���ʼ��ź궨�� */
#define MAILBOX_MAILCODE_CHANNEL(src, dst, channel) \
    ( ((unsigned int)(src) << MAILBOX_ID_SRC_CPU_OFFSET) \
    | ((unsigned int)(dst) << MAILBOX_ID_DST_CPU_OFFSET) \
    | ((unsigned int)(channel) << MAILBOX_ID_CHANNEL_OFFSET) )

#define MAILBOX_CPUID(cpu)   MAILBOX_CPUID_##cpu

#define MAILBOX_MAILCODE_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_CHANNEL(MAILBOX_CPUID(src), \
                             MAILBOX_CPUID(dst), \
                            MAILBOX_CHANNEL_ITEM(src, dst, channel))

#define MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_RESERVED

#define MAILBOX_MAILCODE_ITEM_END(src, dst, channel)    \
    MAILBOX_MAILCODE_##src##2##dst##_##channel##_BUTT

#define MAILBOX_MAILCODE_ITEM_BEGIN(src, dst, channel)  \
    MAILBOX_MAILCODE_ITEM_RESERVED(src, dst, channel) = MAILBOX_MAILCODE_RESERVED(src, dst, channel)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : MAILBOX_CPUID_E
 ��������  : ���������漰CPU���
*****************************************************************************/
enum MAILBOX_CPUID_ENUM
{
    MAILBOX_CPUID_RESERVED  =   -1,
    MAILBOX_CPUID_ACPU      =   IPC_CORE_ACORE,
    MAILBOX_CPUID_CCPU      =   IPC_CORE_CCORE,
    MAILBOX_CPUID_MCU       =   IPC_CORE_ACORE,
    MAILBOX_CPUID_BBE16     =   IPC_CORE_LDSP,
    MAILBOX_CPUID_HIFI      =   IPC_CORE_HiFi,
    MAILBOX_CPUID_BUTT
};

/*****************************************************************************
 ʵ������  : MAILBOX_MAILCODE_ENUM
 ��������  : �ʱ�ö�ٶ���, �ʱ�Ψһ��ʶ�ʼ�����Ŀ��, Ҳ���ʼ����ݽ��մ�����
*****************************************************************************/
enum MAILBOX_MAILCODE_ENUM
{
    /* CCPU->MCU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, MSG),
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_CCPU_TO_MCU_MCA_CH,

    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, MSG),

    /* CCPU->MCU IFC���úŶ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, MCU, IFC),
    MAILBOX_IFC_CCPU_TO_MCU_TEST_CMP,
    MAILBOX_IFC_CCPU_TO_MCU_TEST,
    MAILBOX_IFC_CCPU_TO_MCU_MCA,
    MAILBOX_MAILCODE_ITEM_END(CCPU, MCU, IFC),

    /* CCPU->HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, HIFI, MSG),
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(CCPU, HIFI, MSG),

    /* CCPU->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, MSG),
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, MSG),

    /* CCPU->ACPU IFC��Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(CCPU, ACPU, IFC),
    MAILBOX_IFC_CCPU_TO_ACPU_TEST_CMP,
    MAILBOX_IFC_CCPU_TO_ACPU_TEST,
    MAILBOX_IFC_CCPU_TO_ACPU_PRINT,
    MAILBOX_IFC_CCPU_TO_ACPU_FOPEN,
    MAILBOX_IFC_CCPU_TO_ACPU_FCLOSE,
    MAILBOX_IFC_CCPU_TO_ACPU_FREAD,
    MAILBOX_IFC_CCPU_TO_ACPU_FWRITE,
    MAILBOX_IFC_CCPU_TO_ACPU_FSEEK,
    MAILBOX_IFC_CCPU_TO_ACPU_REMOVE,
    MAILBOX_IFC_CCPU_TO_ACPU_FTELL,
    MAILBOX_IFC_CCPU_TO_ACPU_RENAME,
    MAILBOX_IFC_CCPU_TO_ACPU_ACCESS,
    MAILBOX_IFC_CCPU_TO_ACPU_MKDIR,
    MAILBOX_IFC_CCPU_TO_ACPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT_REPO,
    MAILBOX_MAILCODE_ITEM_END(CCPU, ACPU, IFC),

    /* ACPU->MCU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, MSG),
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_TP_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_MCA_CH,
    BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, MSG),

    /* ACPU->MCU IFCԶ�̺��������ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, MCU, IFC),
    MAILBOX_IFC_ACPU_TO_MCU_TEST_CMP,
    MAILBOX_IFC_ACPU_TO_MCU_TEST,
    MAILBOX_IFC_ACPU_TO_MCU_HUTAF_HLT,
	MAILBOX_IFC_ACPU_TO_MCU_MCA,
    MAILBOX_IFC_ACPU_TO_MCU_MNTN,
    MAILBOX_IFC_ACPU_TO_MCU_RUN_CMD,
    MAILBOX_MAILCODE_ITEM_END(ACPU, MCU, IFC),


    /* ACPU->HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, HIFI, MSG),
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_AUDIO,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOICE,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_VOICE_RT,
    MAILBOX_MAILCODE_ACPU_TO_HIFI_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(ACPU, HIFI, MSG),

    /* ACPU->CCPU MSG�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, MSG),
    MAILBOX_IFC_ACPU_TO_CCPU_CSHELL_START,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, MSG),

    /* ACPU->CCPU IFC�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(ACPU, CCPU, IFC),
    MAILBOX_IFC_ACPU_TO_CCPU_TEST_CMP,
    MAILBOX_IFC_ACPU_TO_CCPU_TEST,
    MAILBOX_IFC_ACPU_TO_CCPU_PRINT,
    MAILBOX_IFC_ACPU_TO_CCPU_FOPEN,
    MAILBOX_IFC_ACPU_TO_CCPU_FCLOSE,
    MAILBOX_IFC_ACPU_TO_CCPU_FREAD,
    MAILBOX_IFC_ACPU_TO_CCPU_FWRITE,
    MAILBOX_IFC_ACPU_TO_CCPU_FSEEK,
    MAILBOX_IFC_ACPU_TO_CCPU_REMOVE,
    MAILBOX_IFC_ACPU_TO_CCPU_FTELL,
    MAILBOX_IFC_ACPU_TO_CCPU_RENAME,
    MAILBOX_IFC_ACPU_TO_CCPU_ACCESS,
    MAILBOX_IFC_ACPU_TO_CCPU_MKDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_RMDIR,
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST2,
    MAILBOX_IFC_ACPU_TO_CCPU_BASE_TEST1,
	MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT,
    MAILBOX_IFC_ACPU_TO_CCPU_READ_EFUSE,
    MAILBOX_IFC_ACPU_TO_CCPU_SYSTEMERROR,
    MAILBOX_MAILCODE_ITEM_END(ACPU, CCPU, IFC),

    /* HIFI->CCPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, CCPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, CCPU, MSG),

    /* HIFI->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, ACPU, MSG),
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_AUDIO,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_MISC,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_VOICE,
    MAILBOX_MAILCODE_HIFI_TO_ACPU_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(HIFI, ACPU, MSG),

    /* HIFI->BBE16 �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(HIFI, BBE16, MSG),
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_HIFI_TO_BBE16_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(HIFI, BBE16, MSG),

    /* MCU->CCPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_CCPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_CCPU_MCA_CH,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, MSG),

    /* MCU->CCPU ifc�ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, CCPU, IFC),
    MAILBOX_IFC_MCU_TO_CCPU_TEST_CMP,
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST2,
    MAILBOX_IFC_MCU_TO_CCPU_BASE_TEST1,
    MAILBOX_IFC_MCU_TO_CCPU_TEST,
    MAILBOX_MAILCODE_ITEM_END(MCU, CCPU, IFC),

    /* MCU->ACPU �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, MSG),
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_URGENT,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_IFC_RESPONSE_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_SENSOR_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_TP_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MCA_CH,
    BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_MNTN_CH,
    MAILBOX_IFC_MCU_TO_ACPU_HUTAF_HLT,
    MAILBOX_MAILCODE_MCU_TO_ACPU_CCORE_RESET_ID,
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, MSG),

    /* MCU->ACPU Զ�̺��������ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(MCU, ACPU, IFC),
    MAILBOX_IFC_MCU_TO_ACPU_TEST_CMP,
    MAILBOX_IFC_MCU_TO_ACPU_TEST,
    MAILBOX_IFC_MCU_TO_ACPU_PRINT,
    MAILBOX_MAILCODE_ITEM_END(MCU, ACPU, IFC),

    /* BBE16 -> HIFI �ʱ�Ŷ��������� */
    MAILBOX_MAILCODE_ITEM_BEGIN(BBE16, HIFI, MSG),
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_NORMAL,
    MAILBOX_MAILCODE_BBE16_TO_HIFI_VOS_MSG_URGENT,
    MAILBOX_MAILCODE_ITEM_END(BBE16, HIFI, MSG),
};

/*****************************************************************************
 ʵ �� ��  : MAILBOX_RET_ENUM
 ��������  : ����ӿڷ���ֵ
*****************************************************************************/
#define    MAILBOX_OK                       0
#define    MAILBOX_ERRO                     0xF7654321
#define    MAILBOX_FULL                     0xF7654322
#define    MAILBOX_NOT_READY                0xF7654323   /*Ŀ��CPU����δ��ʼ��*/
#define    MAILBOX_TARGET_NOT_READY         MAILBOX_NOT_READY   /*Ŀ��CPU����δ��ʼ��*/
#define    MAILBOX_TIME_OUT                 0xF7654324     /*���͵ȴ����س�ʱ*/

/* �ʼ����кŵĳ�ʼֵ */
#define MAILBOX_SEQNUM_START            (0)

/* ����ռ��memory����ַ */
#define MAILBOX_MEM_BASEADDR            (HIFI_AP_MAILBOX_BASE_ADDR)

/* ����ռ��memoryԤ���ܳ���, �����������ͷ��������л��� */
#define MAILBOX_MEM_LENGTH              (HIFI_AP_MAILBOX_TOTAL_SIZE)

/*****************************************************************************
 ʵ �� ��  : struct mb_head
 ��������  : �˼����仺��ͷ, ͨ���������ж�����ͨ����û�б���ʼ��, �˹�����Ҫ
             fastbootͬ���޸�:�ϵ��ʼ�������乲���ڴ�ͷ��������
*****************************************************************************/
typedef struct mb_head
{
    unsigned int       ulProtectWord1;     /*������ 0x55AA55AA*/
    unsigned int       ulProtectWord2;     /*������ 0x5A5A5A5A*/
    unsigned int       ulFront;            /*���д�д��Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned int       ulRear;             /*���д�����Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned int       ulFrontslice;       /*�������价�ζ��е�ͷָ��ϵͳʱ��*/
    unsigned int       ulRearslice;        /*�������价�ζ��е�βָ��ϵͳʱ��*/
    unsigned short      ausReserve[4];      /*����*/
    unsigned int       ulProtectWord3;     /*������ 0x55AA55AA*/
    unsigned int       ulProtectWord4;     /*������ 0x5A5A5A5A*/
} MAILBOX_HEAD_STRU;

/* ����ͷռ�ÿռ��ܳ��ȶ���*/
#define MAILBOX_HEAD_LEN                (sizeof(struct mb_head))
#define MAILBOX_MAX_CHANNEL             (30)
#define MAILBOX_MEM_HEAD_LEN            (MAILBOX_MAX_CHANNEL * MAILBOX_HEAD_LEN)

/* ���������ݶ��г��ȶ��� */
#define MAILBOX_QUEUE_SIZE(src, dst, channel) \
    MAILBOX_QUEUE_SIZE_##src##2##dst##_##channel
enum MAILBOX_QUEUE_SIZE_ENUM
{
    /* ���¸�ö�����������, ����: MAILBOX_QUEUE_SIZE_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_SIZE(MCU,  ACPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU,  MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(MCU, ACPU, IFC)  = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, MCU, IFC)  = 0x00000000,

    MAILBOX_QUEUE_SIZE(MCU,  CCPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU,  MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(MCU, CCPU, IFC)  = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, MCU, IFC)  = 0x00000000,

    MAILBOX_QUEUE_SIZE(ACPU, CCPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(ACPU, CCPU, IFC) = 0x00000000,
    MAILBOX_QUEUE_SIZE(CCPU, ACPU, IFC) = 0x00000000,

    MAILBOX_QUEUE_SIZE(ACPU, HIFI, MSG) = 0x00001800,
    MAILBOX_QUEUE_SIZE(HIFI, ACPU, MSG) = 0x00001800,

    MAILBOX_QUEUE_SIZE(CCPU, HIFI, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(HIFI, CCPU, MSG) = 0x00000000,

    MAILBOX_QUEUE_SIZE(BBE16, HIFI, MSG) = 0x00000000,
    MAILBOX_QUEUE_SIZE(HIFI, BBE16, MSG) = 0x00000000
};

/* ���������ͷ��ַ���� */
#define MAILBOX_HEAD_ADDR(src, dst, channel) \
    MAILBOX_HEAD_ADDR_##src##2##dst##_##channel
enum MAILBOX_HEAD_ADDR_ENUM
{
    /* ���¸�ö�����������, ����: MAILBOX_HEAD_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG)  = MAILBOX_MEM_BASEADDR,
    MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(ACPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG)  = MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG)  = MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG)  = MAILBOX_HEAD_ADDR(MCU,  CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG)  = MAILBOX_HEAD_ADDR(CCPU, MCU,  MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG)  = MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG)  = MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG)  = MAILBOX_HEAD_ADDR(ACPU, CCPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC)  = MAILBOX_HEAD_ADDR(CCPU, ACPU, MSG) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC)  = MAILBOX_HEAD_ADDR(CCPU, ACPU, IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(CCPU, MCU, IFC)   = MAILBOX_HEAD_ADDR(ACPU, CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, CCPU, IFC)   = MAILBOX_HEAD_ADDR(CCPU, MCU,  IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(ACPU, MCU, IFC)   = MAILBOX_HEAD_ADDR(MCU,  CCPU, IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(MCU, ACPU, IFC)   = MAILBOX_HEAD_ADDR(ACPU, MCU,  IFC) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_ADDR(BBE16, HIFI, MSG) = MAILBOX_HEAD_ADDR(MCU, ACPU,  IFC) + MAILBOX_HEAD_LEN,
    MAILBOX_HEAD_ADDR(HIFI, BBE16, MSG) = MAILBOX_HEAD_ADDR(BBE16,HIFI, MSG) + MAILBOX_HEAD_LEN,

    MAILBOX_HEAD_BOTTOM_ADDR            = MAILBOX_HEAD_ADDR(HIFI, BBE16,MSG) + MAILBOX_HEAD_LEN

};

/* ���������ݶ��е�ַ���� */
#define MAILBOX_QUEUE_ADDR(src, dst, channel) \
    MAILBOX_QUEUE_ADDR_##src##2##dst##_##channel
#define MAILBOX_QUEUE_BOTTOM_ADDR(src, dst, channel) \
    (MAILBOX_QUEUE_ADDR(src, dst, channel) + MAILBOX_QUEUE_SIZE(src, dst, channel))
enum MAILBOX_QUEUE_ADDR_ENUM
{
    /* ���¸�ö�����������, ����: MAILBOX_QUEUE_ADDR_MCU2ACPU_DEFAULT */
    MAILBOX_QUEUE_ADDR(MCU,  ACPU, MSG)  = MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN,
    MAILBOX_QUEUE_ADDR(ACPU, MCU,  MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, HIFI, MSG),

    MAILBOX_QUEUE_ADDR(MCU,  CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, ACPU, MSG) ,
    MAILBOX_QUEUE_ADDR(CCPU, MCU,  MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(MCU,  CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, HIFI, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU,  MSG),
    MAILBOX_QUEUE_ADDR(HIFI, CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, HIFI, MSG),

    MAILBOX_QUEUE_ADDR(ACPU, CCPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, MSG)  = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, MSG),
    MAILBOX_QUEUE_ADDR(CCPU, ACPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, MSG),
    MAILBOX_QUEUE_ADDR(ACPU, CCPU, IFC)  = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, ACPU, IFC),

    MAILBOX_QUEUE_ADDR(CCPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, CCPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(CCPU, MCU, IFC),
    MAILBOX_QUEUE_ADDR(ACPU, MCU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, CCPU, IFC),
    MAILBOX_QUEUE_ADDR(MCU, ACPU, IFC)   = MAILBOX_QUEUE_BOTTOM_ADDR(ACPU, MCU, IFC),

    MAILBOX_QUEUE_ADDR(BBE16, HIFI, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(MCU, ACPU, IFC),
    MAILBOX_QUEUE_ADDR(HIFI, BBE16, MSG) = MAILBOX_QUEUE_BOTTOM_ADDR(BBE16, HIFI, MSG),

    MAILBOX_MEMORY_BOTTOM_ADDR           = MAILBOX_QUEUE_BOTTOM_ADDR(HIFI, BBE16, MSG)
};

/*�����ڴ��еı����ֶ���*/
#define MAILBOX_PROTECT1                (0x55AA55AA)    /* ���䱣����1����������ͷ������, ͬʱ��ʾ����ճ�ʼ��û�н��չ�����*/
#define MAILBOX_PROTECT2                (0x5A5A5A5A)    /* ���䱣����2����������ͷ������ */
#define MAILBOX_PROTECT_LEN             (sizeof(int))  /* ���䱣���ֳ��ȣ���λbyte������ͷ������ͷ��β�������������ı����� */
#define MAILBOX_MSGHEAD_NUMBER          (0xA5A5A5A5)    /* �����Ϣ��Ϣ�ָ��� */

#define MAILBOX_DATA_BASE_PROTECT_NUM         (2)    /* ����ͨ�������ڴ����������׵�ַ��ʼ�ı����ָ���*/
#define MAILBOX_DATA_TAIL_PROTECT_NUM         (2)    /* ����ͨ�������ڴ���������β��ַ�����ı����ָ���*/

/* ����ͨ�������ڴ������������а����ı����ֵĸ����������׵�ַ��ʼ��2�������֣���ĩ��ַ������2��������*/
#define MAILBOX_DATA_LEN_PROTECT_NUM          (MAILBOX_DATA_BASE_PROTECT_NUM + MAILBOX_DATA_TAIL_PROTECT_NUM)


/* hifi�����ַ��Ϣ������ */
#define HIFI_MB_ADDR_PROTECT            (0x5a5a5a5a)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  ������������֮���IPC�жϺ�
*****************************************************************************/
#define MAILBOX_IPC_INT_NUM(src, dst, channel) \
    MAILBOX_IPC_INT_##src##2##dst##_##channel
enum IPC_MAILBOX_INT_ENUM
{
#if 0
    /* ���¸�ö�����������, ����: MAILBOX_IPC_INT_CCPU2MCU_DEFAULT */
    MAILBOX_IPC_INT_NUM(CCPU, MCU, MSG)  = IPC_MCU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, MSG)  = IPC_CCPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, HIFI, MSG) = IPC_HIFI_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, CCPU, MSG) = IPC_CCPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, MSG)  = IPC_MCU_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, MSG)  = IPC_ACPU_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, HIFI, MSG) = IPC_HIFI_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, ACPU, MSG) = IPC_ACPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(HIFI, MCU, MSG)  = IPC_MCU_INT_SRC_HIFI_MSG,
    MAILBOX_IPC_INT_NUM(MCU, HIFI, MSG)  = IPC_HIFI_INT_SRC_MCU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, MSG)    = IPC_ACPU_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, MSG)    = IPC_CCPU_INT_SRC_ACPU_MSG,

    MAILBOX_IPC_INT_NUM(CCPU, ACPU, IFC)    = IPC_ACPU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(ACPU, CCPU, IFC)    = IPC_CCPU_INT_SRC_ACPU_IFC,

    MAILBOX_IPC_INT_NUM(CCPU, MCU, IFC)    = IPC_MCU_INT_SRC_CCPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, CCPU, IFC)    = IPC_CCPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(ACPU, MCU, IFC)    = IPC_MCU_INT_SRC_ACPU_IFC,
    MAILBOX_IPC_INT_NUM(MCU, ACPU, IFC)    = IPC_ACPU_INT_SRC_MCU_IFC,

    MAILBOX_IPC_INT_NUM(BBE16, HIFI, MSG) = IPC_HIFI_INT_SRC_BBE_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, BBE16, MSG) = IPC_BBE16_INT_SRC_HIFI_MSG

#else
    MAILBOX_IPC_INT_NUM(CCPU, HIFI, MSG) = IPC_HIFI_INT_SRC_CCPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, CCPU, MSG) = IPC_CCPU_INT_SRC_HIFI_MSG,

    MAILBOX_IPC_INT_NUM(ACPU, HIFI, MSG) = IPC_HIFI_INT_SRC_ACPU_MSG,
    MAILBOX_IPC_INT_NUM(HIFI, ACPU, MSG) = IPC_ACPU_INT_SRC_HIFI_MSG,
#endif
};

/* ���������ݵ����ʼ���󳤶ȶ��� */
#define MAILBOX_MAILSIZE_MAX(src, dst, channel) \
    MAILBOX_MAILSIZE_MAX_##src##2##dst##_##channel
enum MAILBOX_MAILSIZE_MAX_ENUM
{
    /* ���¸�ö�����������, ����: MAILBOX_MAILSIZE_MAX_MCU2ACPU_DEFAULT */
    MAILBOX_MAILSIZE_MAX(MCU,  ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU,  ACPU ,MSG)/4, //DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(ACPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, MCU  ,MSG)/4, //DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(ACPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU ,HIFI ,MSG)/4, //DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(HIFI, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,ACPU ,MSG)/4, //DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(MCU , CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(MCU  ,CCPU ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(CCPU, MCU  ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,MCU  ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(CCPU, HIFI ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU ,HIFI ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(HIFI, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(HIFI ,CCPU ,MSG)/4,//DOTO:����ֵ��Ҫ����

    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,MSG)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,MSG)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(CCPU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, ACPU ,IFC)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(ACPU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, CCPU ,IFC)/4,//DOTO:����ֵ��Ҫ����

    MAILBOX_MAILSIZE_MAX(CCPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(CCPU, MCU ,IFC)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(MCU, CCPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, CCPU ,IFC)/4,//DOTO:����ֵ��Ҫ����

    MAILBOX_MAILSIZE_MAX(ACPU, MCU ,IFC)  = MAILBOX_QUEUE_SIZE(ACPU, MCU ,IFC)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(MCU, ACPU ,IFC)  = MAILBOX_QUEUE_SIZE(MCU, ACPU ,IFC)/4,//DOTO:����ֵ��Ҫ����

    MAILBOX_MAILSIZE_MAX(BBE16, HIFI ,MSG) = MAILBOX_QUEUE_SIZE(BBE16 ,HIFI ,MSG)/4,//DOTO:����ֵ��Ҫ����
    MAILBOX_MAILSIZE_MAX(HIFI, BBE16 ,MSG) = MAILBOX_QUEUE_SIZE(HIFI ,BBE16 ,MSG)/4,//DOTO:����ֵ��Ҫ����
};

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : struct mb_mail
 ��������  : �˼��ʼ�ͷ
*****************************************************************************/
typedef struct mb_mail
{
    unsigned int       ulPartition;    /*��Ϣ�ָ��� 0xA5A5A5A5*/
    unsigned int       ulWriteSlice;   /*��Ϣд��ϵͳʱ����Ϣ */
    unsigned int       ulReadSlice;    /*��Ϣ����ϵͳʱ����Ϣ */
    unsigned int       ulSeqNum;       /*��Ϣ���к� */
    unsigned int       ulPriority;     /*��Ϣ���ȼ�����������ͨ, ����*/
    unsigned int       ulMailCode;     /*�ʱ�*/
    unsigned int       ausReserve[2];  /*����*/
    unsigned int       ulMsgLength;    /*��ulMsgLength�ֶ�(��������)�������Ϣ����*/
} MAILBOX_MSG_HEADER;

/************************************************************************
 �ṹ��    : IPC_MAILBOX_QUEUE_STRU
 �ṹ˵��  : �˼����仺��
 ************************************************************************/
/* ����ṹʾ��:
typedef struct
{
    unsigned int      ulProtectWord1;     //������ 0x55aa55aa
    unsigned int      ulProtectWord2;     //������ 0a5a5a5a5a
    unsigned int      aulMsgQueue[���г���-4];//���ζ��д�����ɷ��ʼ�
    unsigned int      ulProtectWord3;     //������ 0x55aa55aa
    unsigned int      ulProtectWord4;     //������ 0x5a5a5a5a
} MAILBOX_QUEUE_STRU;
*/
enum
{
	HI_SYSCTRL_BASE_ADDR_ID = 0,
	HI_SOCP_REGBASE_ADDR_ID,
	SOC_IPC_S_BASE_ADDR_ID,
	SOC_AP_EDMAC_BASE_ADDR_ID,
	SOC_UART3_BASE_ADDR_ID,
	SOC_Watchdog1_BASE_ADDR_ID,
	SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR_0_ID,
	SOC_HIFI_Timer00_BASE_ADDR_ID,
	SOC_HIFI_Timer08_BASE_ADDR_ID,
	DDR_HIFI_ADDR_ID,
	SOC_BBP_TDS_BASE_ADDR_ID,
};

typedef struct
{
	unsigned int enID;				/*��ַö��ֵ*/
	unsigned int uwAddress; 			/*��ַ����ֵ*/
} SOC_HIFI_ADDR_ITEM_STRU;

typedef struct
{
	unsigned int uwProtectWord; 				/*0x5a5a5a5a*/
	SOC_HIFI_ADDR_ITEM_STRU 	astSocAddr[64]; /*��ַ���*/
} SOC_HIFI_ADDR_SHARE_STRU;


typedef struct
{
	unsigned int uwProtectWord;
	unsigned int uwAddrPhy;
	unsigned int uwSize;
	unsigned int uwReserve;

}MODEM_HIFI_NV_SHARE_STRU;

typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2AarmMailBoxLen;        /* hifi��Aarm������䳤�� */
    unsigned int uwAarm2HifiMailBoxLen;        /* Aarm��hifi������䳤�� */
    unsigned int uwHifiAarmHeadAddr;
    unsigned int uwHifiAarmBodyAddr;
    unsigned int uwAarmHifiHeadAddr;
    unsigned int uwAarmHifiBodyAddr;
    unsigned int uwReserved[2];
}AARM_HIFI_MAILBOX_STRU;

/*****************************************************************************
 �ṹ��    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :CARM��HIFI�Ĺ����ַ��OAM��Ҫ��ֵ��������Hifi���������е���Ӧ�ṹ��
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;                /*0x5a5a5a5a*/
    unsigned int uwHifi2CarmMailBoxLen;        /* hifi��Carm������䳤�� */
    unsigned int uwCarm2HifiMailBoxLen;        /* Carm��hifi������䳤�� */
    unsigned int uwHifiCarmHeadAddr;
    unsigned int uwHifiCarmBodyAddr;
    unsigned int uwCarmHifiHeadAddr;
    unsigned int uwCarmHifiBodyAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_MAILBOX_STRU;

typedef struct
{
    unsigned int uwProtectWord;
    unsigned int uwHifi2CarmIccChannelLen;
    unsigned int uwHifi2TphyIccChannelLen;
    unsigned int uwHifi2CarmIccChannelAddr;
    unsigned int uwCarm2HifiIccChannelAddr;
    unsigned int uwHifi2TphyIccChannelAddr;
    unsigned int uwTphy2HifiIccChannelAddr;
    unsigned int uwReserved[2];
}CARM_HIFI_ICC_STRU;

/*****************************************************************************
 �ṹ��    : AARM_HIFI_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :AARM��HIFI�Ĺ����ַ��OAM��Ҫ��ֵ��������Hifi���������е���Ӧ�ṹ��
*****************************************************************************/
typedef struct
{
	unsigned int uwProtectWord; 		   /*0x5a5a5a5a*/
	CARM_HIFI_ICC_STRU stCarmHifiMB;	/*CARM��HIFI�����乲��������*/
	AARM_HIFI_MAILBOX_STRU stAarmHifiMB;	/*AARM��HIFI�����乲��������*/
	unsigned int uwNvBaseAddrPhy;		   /*DDR��NV�������׵�ַ�������ַ*/
	unsigned int uwNvBaseAddrVirt;		   /*DDR��NV�������׵�ַ��ARM�����ַ*/
	MODEM_HIFI_NV_SHARE_STRU stNVShare;  /*Modem NV����������*/
	SOC_HIFI_ADDR_SHARE_STRU	stSoCShare;  /*SoC����������*/
	unsigned int uwReserved[2];
}CARM_HIFI_DYN_ADDR_SHARE_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mb_msg_cb
 ��������  : �������ݽ��մ���ص�����, Ŀ���������ʼ����ݵ���ʱ������
             �����û�ʵ�ֲ�ͨ��MAILBOX_RegisterRecvFuncע��
 �������  : UserHandle -- �û����
             MailHandle -- ������
             MailLen    -- ���ε����ʼ����ݳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
typedef void (*mb_msg_cb)(
                void                   *user_handle,
                void                   *mail_handle,
                unsigned int           mail_len);

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_SENDMAIL
 ��������  : �����û������ʼ�����
 �������  : MailCode   -- �ʱ�, ָ���ʼ�����Ŀ��
             pData      -- ָ���ʼ����ݵ�ָ��
             Length     -- ���������ݳ���, ��λbyte
 �������  : ��
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��28��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length);

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_REGISTERRECVFUNC
 ��������  : ע���ʼ����ݽ��պ���
 �������  : MailCode   -- ���ݽ��պ�������Ķ����ʱ�
             pFun       -- �ʼ����ݽ��մ�����ָ��
             UserHandle -- �û�������, ���ݽ��պ���������ʱ����Ϊ���, �������
 �������  : ��
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��29��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle);

/*****************************************************************************
 �� �� ��  : DRV_MAILBOX_READMAILDATA
 ��������  : �����û������ݽ��ջص������е���, �������ж�ȡһ�����ȵ�����ʼ�
 �������  : MailHandle -- ������, ���ݽ��ջص��������
             pData      -- ������������ݵĻ����ַ
             *pSize     -- ���泤��, ��λbyte, ��Ҫ���ڴ���ȡ�ʼ�����
 �������  : *pSize     -- ʵ�ʶ�ȡ����, ��λbyte
 �� �� ֵ  : ��ȷ:MAILBOX_OK / ����:MAILBOX_ERRO��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��26��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize);

/*****************************************************************************
 �� �� ��  : drv_hifi_fill_mb_info
 ��������  : ������Ϣ���ýӿ�
 �������  : addr ����Ϣ��ַ(��HIFI����ģ�鴫��)
 �������  :
 �� �� ֵ  : void
 ���ú���  : V9R1����fastboot�е��ã�V7R2����DSPһ����ص���
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��4��
    ��    ��   : �޾�ǿ 64416
    �޸�����   : �����ɺ���

*****************************************************************************/
void drv_hifi_fill_mb_info(unsigned int addr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox_cfg.h */

