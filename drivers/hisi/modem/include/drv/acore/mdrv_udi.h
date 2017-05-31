

#ifndef __MDRV_ACORE_UDI_H__
#define __MDRV_ACORE_UDI_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_icc.h"
#include "mdrv_udi_common.h"

#define UDI_BUILD_DEV_ID(dev, type) ((dev << 8) | (type & 0x00ff))

typedef int UDI_HANDLE;

typedef enum tagUDI_DEVICE_MAIN_ID_E
{
    UDI_DEV_USB_ACM = 0,
    UDI_DEV_USB_NCM,
    UDI_DEV_ICC,
    UDI_DEV_UART,
    UDI_DEV_HSUART,
    UDI_DEV_USB_ADC,
    UDI_DEV_MAX
}UDI_DEVICE_MAIN_ID_E;


typedef enum tagUDI_ACM_DEV_TYPE_E
{
    UDI_USB_ACM_CTRL,
    UDI_USB_ACM_AT,
    UDI_USB_ACM_SHELL,
    UDI_USB_ACM_LTE_DIAG,
    UDI_USB_ACM_OM,
    UDI_USB_ACM_MODEM,
    UDI_USB_ACM_GPS,
    UDI_USB_ACM_3G_GPS,
    UDI_USB_ACM_3G_PCVOICE,
    UDI_USB_ACM_PCVOICE,
    UDI_USB_ACM_SKYTONE,
    UDI_USB_HSIC_ACM0,
    UDI_USB_HSIC_ACM1,
    UDI_USB_HSIC_ACM2,
    UDI_USB_HSIC_ACM3,
    UDI_USB_HSIC_ACM4,
    UDI_USB_HSIC_ACM5,
    UDI_USB_HSIC_ACM6,
    UDI_USB_HSIC_ACM7,
    UDI_USB_HSIC_ACM8,
    UDI_USB_HSIC_ACM9,
    UDI_USB_HSIC_ACM10,
    UDI_USB_HSIC_ACM11,
    UDI_USB_HSIC_ACM12,
    UDI_USB_HSIC_ACM13,
    UDI_USB_HSIC_ACM14,
    UDI_USB_HSIC_MODEM0,
    UDI_USB_ACM_MAX
}UDI_ACM_DEV_TYPE_E;

typedef enum tagUDI_NCM_DEV_TYPE_E
{
    UDI_USB_NCM_NDIS,
    UDI_USB_NCM_CTRL,
    UDI_USB_NCM_NDIS1,
    UDI_USB_NCM_CTRL1,
	UDI_USB_NCM_NDIS2,
	UDI_USB_NCM_CTRL2,
	UDI_USB_NCM_NDIS3,
	UDI_USB_NCM_CTRL3,
    UDI_USB_NCM_BOTTOM,            /* ����MBB���������� */
    UDI_USB_HSIC_NCM0,
    UDI_USB_HSIC_NCM1,
    UDI_USB_HSIC_NCM2,

    UDI_USB_NCM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_NCM_DEV_TYPE_E;


/* �ܹ�����,���к궨�彫��ɾ������ֹ��������ʹ�����к� */
typedef enum tagUDI_ICC_DEV_TYPE
{
        UDI_ICC_GUOM0 = MDRV_ICC_GUOM0,
        UDI_ICC_GUOM1 = MDRV_ICC_GUOM1,
        UDI_ICC_GUOM2 = MDRV_ICC_GUOM2,
        UDI_ICC_GUOM3 = MDRV_ICC_GUOM3,
        UDI_ICC_GUOM4 = MDRV_ICC_GUOM4,
        UDI_ICC_GUOM5 = MDRV_ICC_GUOM5,
        UDI_ICC_GUOM6 = MDRV_ICC_GUOM6,
        UDI_ICC_GUOM7 = MDRV_ICC_GUOM7,

        UDI_ICC_MAX
}UDI_ICC_DEV_TYPE_E;

/* �ܹ�����,����궨�彫��ɾ������ֹ��������ʹ������� */

typedef enum tagUDI_ADC_DEV_TYPE_E
{
    UDI_USB_ADC0,
    UDI_USB_ADC_MAX
}UDI_ADC_DEV_TYPE_E;

typedef enum tagUDI_DEVICE_ID_E
{
    /* USB ACM */
    UDI_ACM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
    UDI_ACM_AT_ID =    UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
    UDI_ACM_SHELL_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
    UDI_ACM_LTE_DIAG_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
    UDI_ACM_OM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_OM),
    UDI_ACM_MODEM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
    UDI_ACM_GPS_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),     /*HISO*/
    UDI_ACM_3G_GPS_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_GPS),  /*ashell*/
    UDI_ACM_3G_PCVOICE_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_PCVOICE),
    UDI_ACM_PCVOICE_ID    = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_PCVOICE),
    UDI_ACM_SKYTONE_ID  = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SKYTONE),
    UDI_ACM_HSIC_ACM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM0),
    UDI_ACM_HSIC_ACM1_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM1),
    UDI_ACM_HSIC_ACM2_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM2),
    UDI_ACM_HSIC_ACM3_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM3),
    UDI_ACM_HSIC_ACM4_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM4),
    UDI_ACM_HSIC_ACM5_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM5),
    UDI_ACM_HSIC_ACM6_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM6),
    UDI_ACM_HSIC_ACM7_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM7),
    UDI_ACM_HSIC_ACM8_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM8),
    UDI_ACM_HSIC_ACM9_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM9),
    UDI_ACM_HSIC_ACM10_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM10),
    UDI_ACM_HSIC_ACM11_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM11),
    UDI_ACM_HSIC_ACM12_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM12),
    UDI_ACM_HSIC_ACM13_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM13),
    UDI_ACM_HSIC_ACM14_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM14),
    UDI_ACM_HSIC_MODEM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_MODEM0),
    /* USB NCM */
    UDI_NCM_NDIS_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS),
    UDI_NCM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL),
    UDI_NCM_HSIC_NCM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM0),
    UDI_NCM_HSIC_NCM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM1),
    UDI_NCM_HSIC_NCM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM2),

    /* UART */
    UDI_UART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 0),
    UDI_UART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 1),

    /* HSUART */
    UDI_HSUART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 0),
    UDI_HSUART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 1),

    /* ICC */
    UDI_ICC_IFC_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 0),
    UDI_ICC_IPM_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 1),
    UDI_ICC_LMSP_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 2),

    UDI_ICC_GUOM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM0),
    UDI_ICC_GUOM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM1),
    UDI_ICC_GUOM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM2),
    UDI_ICC_GUOM3_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM3),
    UDI_ICC_GUOM4_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM4),
    UDI_ICC_GUOM5_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM5),
    UDI_ICC_GUOM6_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM6),/*z00179562_check,?V9????*/
    UDI_ICC_GUOM7_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM7),/*y00145322_check,?V9????*/

    UDI_ADC_SND0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ADC, UDI_USB_ADC0),

    /* MUST BE LAST */
    UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID_E;


typedef struct tagUDI_OPEN_PARAM_S
{
    UDI_DEVICE_ID_E devid;                           /* �豸ID */
    void   *pPrivate;                            /* ģ�����е����� */
} UDI_OPEN_PARAM_S;

typedef enum tagUDI_IOCTL_CMD_TYPE_E
{
    UDI_IOCTL_SET_WRITE_CB = 0xF001,            /* ����һ����ʼ��ֵ��ֹ��ϵͳ�����ͻ */
    UDI_IOCTL_SET_READ_CB,

    UDI_IOCTL_INVAL_CMD = -1
} UDI_IOCTL_CMD_TYPE_E;

/* ACM */
/* IOCTL CMD ���� */

/* UDI IOCTL ����ID */
#define UDI_ACM_IOCTL_SET_READ_CB           ACM_IOCTL_SET_READ_CB
#define UDI_ACM_IOCTL_GET_READ_BUFFER_CB    ACM_IOCTL_GET_RD_BUFF
#define UDI_ACM_IOCTL_RETUR_BUFFER_CB       ACM_IOCTL_RETURN_BUFF

#define UDI_ADC_IOCTL_SET_WRITE_CB          0X41000071
#define UDI_ADC_IOCTL_SET_READ_CB           0X41000072
#define UDI_ADC_IOCTL_GET_READ_BUFFER_CB    0X41000073
#define UDI_ADC_IOCTL_RETUR_BUFFER_CB       0X41000074

/* ACM MODEM SIG define */
#define SIGNALNOCH 0
#define SIGNALCH 1
#define RECV_ENABLE 1
#define RECV_DISABLE 0
#define SEND_ENABLE 1
#define SEND_DISABLE 0
#define HIGHLEVEL 1
#define LOWLEVEL 0


/* ACM MODEM �ܽ��źŽṹ�嶨��*/
typedef struct tagMODEM_MSC_STRU
{
    unsigned int OP_Dtr     :    1;          /*DTR CHANGE FLAG*/
    unsigned int OP_Dsr     :    1;          /*DSR CHANGE FLAG*/
    unsigned int OP_Cts     :    1;          /*CTSCHANGE FLAG*/
    unsigned int OP_Rts     :    1;          /*RTS CHANGE FLAG*/
    unsigned int OP_Ri      :    1;          /*RI CHANGE FLAG*/
    unsigned int OP_Dcd     :    1;          /*DCD CHANGE FLAG*/
    unsigned int OP_Fc      :    1;          /*FC CHANGE FLAG*/
    unsigned int OP_Brk     :    1;          /*BRK CHANGE FLAG*/
    unsigned int OP_Spare   :    24;         /*reserve*/
    unsigned char   ucDtr;                   /*DTR  VALUE*/
    unsigned char   ucDsr;                   /*DSR  VALUE*/
    unsigned char   ucCts;                   /*DTS VALUE*/
    unsigned char   ucRts;                   /*RTS  VALUE*/
    unsigned char   ucRi;                    /*RI VALUE*/
    unsigned char   ucDcd;                   /*DCD  VALUE*/
    unsigned char   ucFc;                    /*FC  VALUE*/
    unsigned char   ucBrk;                   /*BRK  VALUE*/
    unsigned char   ucBrkLen;                /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;

typedef void (*ACM_MODEM_MSC_READ_CB_T)(MODEM_MSC_STRU* pModemMsc);


/* NCM */
/* ������·�հ�����ָ�� */
typedef void (*USBUpLinkRxFunc)(UDI_HANDLE handle, void * pPktNode);

/* USB IOCTLö�� */
typedef enum tagNCM_IOCTL_CMD_TYPE_E
{
    NCM_IOCTL_NETWORK_CONNECTION_NOTIF,      /* 0x0,NCM�����Ƿ�������*/
    NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, /* 0x1,NCM�豸Э�̵������ٶ�*/
    NCM_IOCTL_SET_PKT_ENCAP_INFO,            /* 0x2,���ð���װ��ʽ*/
    NCM_IOCTL_REG_UPLINK_RX_FUNC,            /* 0x3,ע�������հ��ص�����*/
    NCM_IOCTL_REG_FREE_PKT_FUNC,             /* 0x4,ע���ͷŰ���װ�ص�����*/
    NCM_IOCTL_FREE_BUFF,                     /* 0x5,�ͷŵ���buffer*/
    NCM_IOCTL_GET_USED_MAX_BUFF_NUM,         /* 0x6,��ȡ�ϲ�������ռ�õ�ncm buffer����*/
    NCM_IOCTL_GET_DEFAULT_TX_MIN_NUM,        /* 0x7,��ȡĬ�Ϸ���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_TIMEOUT,        /* 0x8,��ȡĬ�Ϸ�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_MAX_SIZE,       /* 0x9,��ȡĬ�Ϸ����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_MIN_NUM,                /* 0xa,���÷���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_TIMEOUT,                /* 0xb,���÷�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_SET_TX_MAX_SIZE,               /* 0xc,�������ֲ���ʹ�á����÷����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_RX_BUF_SIZE,               /* 0xd,��ȡ�հ�buffer��С*/
    NCM_IOCTL_FLOW_CTRL_NOTIF,               /* 0xe,���ؿ��ƿ���*/
    NCM_IOCTL_REG_AT_PROCESS_FUNC,           /* 0xf,ע��AT�����ص�����*/
    NCM_IOCTL_AT_RESPONSE,                   /* 0x10,AT�����Ӧ*/
    NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC,     /* 0x11,ע������״̬�ı�֪ͨ�ص�����*/
    NCM_IOCTL_SET_PKT_STATICS,               /* 0x12,����ͳ����Ϣ*/
    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 ��ѯNCM����״̬*/

    NCM_IOCTL_GET_CUR_TX_MIN_NUM,            /* 0x14 ��ȡ��ǰ����������ֵ*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,            /* 0x15 ��ȡ��ǰ������ʱʱ��*/
    NCM_IOCTL_IPV6_DNS_NOTIF,                /*0x16 IPV6 DNS�����ϱ�*/
    NCM_IOCTL_SET_IPV6_DNS,                  /* 0x16 ����IPV6 DNS*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                /* 0x17 ���IPV6 DNS�ڰ�˵Ļ���,param�ڴ�������û�����壬�����ָ�뼴��*/
    NCM_IOCTL_GET_NCM_STATUS,                /* 0x18 ��ȡNCM����״̬ enable:TRUE(1);disable:FALSE(0) */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

	NCM_IOCTL_SET_RX_MIN_NUM,		         /*�����հ�������ֵ*/
	NCM_IOCTL_SET_RX_TIMEOUT,			     /*�����հ���ʱʱ��*/

    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC      /* NDISͨ��AT����״̬����ص����� */
}NCM_IOCTL_CMD_TYPE_E;

/* NCM����״̬ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECTION_STATUS_E
{
    NCM_IOCTL_CONNECTION_LINKDOWN,      /* NCM����Ͽ�����*/
    NCM_IOCTL_CONNECTION_LINKUP         /* NCM��������*/
}NCM_IOCTL_CONNECTION_STATUS_E;

/* NCM�����ٶȽṹ,NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_IOCTL_CONNECTION_SPEED_S
{
    unsigned int u32DownBitRate;
    unsigned int u32UpBitRate;
}NCM_IOCTL_CONNECTION_SPEED_S;

/* AT����ظ�����ָ�뼰���� NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    unsigned char* pu8AtAnswer;
    unsigned int u32Length;
} NCM_AT_RSP_S;

/* AT������պ���ָ�룬�ú���Ϊͬ���ӿڣ���ӦNCM_IOCTL_REG_AT_PROCESS_FUNC������*/
typedef void (*USBNdisAtRecvFunc)(unsigned char * pu8Buf, unsigned int u32Len);

/* NCM���ؿ���ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_FLOW_CTRL_E
{
    NCM_IOCTL_FLOW_CTRL_ENABLE,      /* ������*/
    NCM_IOCTL_FLOW_CTRL_DISABLE      /* �ر�����*/
}NCM_IOCTL_FLOW_CTRL_E;

/* NCM����״̬�ı�֪ͨö��,NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECT_STUS_E
{
    NCM_IOCTL_STUS_CONNECT,      /* ����*/
    NCM_IOCTL_STUS_BREAK         /* �����Ͽ�,����*/
}NCM_IOCTL_CONNECT_STUS_E;

/* ����״̬�л�֪ͨ��������ӦNCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC������*/
typedef void (*USBNdisStusChgFunc)(NCM_IOCTL_CONNECT_STUS_E enStatus, void * pBuffer);

/* NDISͨ��AT����״̬����ص����� */
typedef void (*USBNdisRespStatusCB)(void *pBuffer, unsigned int status);

#define BSP_NCM_IPV6_DNS_LEN     32
typedef struct tagNCM_IPV6DNS_S  /* 0x16 ����IPV6 DNS*/
{
    unsigned char * pu8Ipv6DnsInfo;/* 32�ֽڣ���16�ֽڱ�ʾprimaryDNS����16�ֽڱ�ʾSecondaryDNS��*/
    unsigned int u32Length;
} NCM_IPV6DNS_S;

typedef int (*UDI_ADP_INIT_CB_T)(void);
typedef unsigned int (*UDI_GET_CAPABILITY_CB_T)(UDI_DEVICE_ID_E devId);
typedef int (*UDI_OPEN_CB_T)(UDI_OPEN_PARAM_S *param, UDI_HANDLE handle);
typedef int (*UDI_CLOSE_CB_T)(void* pPrivate);
typedef int (*UDI_WRITE_CB_T)(void* pPrivate, void* pMemObj, unsigned int u32Size);
typedef int (*UDI_READ_CB_T)(void* pPrivate, void* pMemObj, unsigned int u32Size);
typedef int (*UDI_IOCTL_CB_T) (void* pPrivate, unsigned int u32Cmd, void* pParam);


/* �������亯��ָ��� */
typedef struct tagUDI_DRV_INTEFACE_TABLE
{
	/* capability */
	UDI_ADP_INIT_CB_T		udi_get_capability_cb;

	/* data interfaces */
	UDI_OPEN_CB_T			udi_open_cb;
	UDI_CLOSE_CB_T			udi_close_cb;
	UDI_WRITE_CB_T			udi_write_cb;
	UDI_READ_CB_T			udi_read_cb;
	UDI_IOCTL_CB_T			udi_ioctl_cb;
}UDI_DRV_INTEFACE_TABLE;

/*****************************************************************************
* �� �� ��  : mdrv_udi_open
*
* ��������  : ���豸(����ͨ��)
*
* �������  : pParam: �豸�Ĵ����ò���
* �������  : ��
* �� �� ֵ  : -1:ʧ�� / ����:�ɹ�
*****************************************************************************/
UDI_HANDLE mdrv_udi_open(UDI_OPEN_PARAM_S *pParam);


/*****************************************************************************
* �� �� ��  : mdrv_udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
int mdrv_udi_close(UDI_HANDLE handle);

/*****************************************************************************
* �� �� ��  : mdrv_udi_write
*
* ��������  : ����д
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ����д�ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
int mdrv_udi_write(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size);


/*****************************************************************************
* �� �� ��  : mdrv_udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ���ݶ��ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
int mdrv_udi_read(UDI_HANDLE handle, void* pMemObj, unsigned int u32Size);


/*****************************************************************************
* �� �� ��  : mdrv_udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int mdrv_udi_ioctl(UDI_HANDLE handle, unsigned int u32Cmd, void* pParam);

#ifdef __cplusplus
}
#endif

#endif
