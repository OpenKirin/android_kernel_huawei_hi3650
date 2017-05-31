

#ifndef __MDRV_ACORE_STUB_V7_H__
#define __MDRV_ACORE_STUB_V7_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * �� �� ��  : BSP_MALLOC
 *
 * ��������  : BSP ��̬�ڴ����
 *
 * �������  : sz: ����Ĵ�С(byte)
 *             flags: �ڴ�����(�ݲ�ʹ��,Ԥ��)
 * �������  : ��
 * �� �� ֵ  : ����������ڴ�ָ��
 *****************************************************************************/
static inline void* BSP_MALLOC(unsigned int u32Size, MEM_POOL_TYPE enFlags) {
    return 0;
}

/*****************************************************************************
 * �� �� ��  : BSP_FREE
 *
 * ��������  : BSP ��̬�ڴ��ͷ�
 *
 * �������  : ptr: ��̬�ڴ�ָ��
 * �������  : ��
 * �� �� ֵ  : ��
 *****************************************************************************/
static inline void  BSP_FREE(void* pMem) {
}

/*****************************************************************
Function: free_mem_size_get
Description:
    get mem size
Input:
    N/A
Output:
    N/A
Return:
    free mem size
*******************************************************************/
static inline unsigned int FREE_MEM_SIZE_GET(void)
{
    return 0;
}

static inline int BSP_DLOAD_GetDloadType(void)
{
    return 1;
}

/*liuyi++ only for nas marenkun temp*/

/*****************************************************************************
 Function   : BSP_PWC_SetTimer4WakeSrc
 Description: ����timer4��Ϊ����Դ
 Input      :
 Return     : void
 Other      :
*****************************************************************************/
static inline void BSP_PWC_SetTimer4WakeSrc(void)
{
    return;
}


/*****************************************************************************
 Function   : BSP_PWC_DelTimer4WakeSrc
 Description: ����timer4����Ϊ����Դ
 Input      :
            :
 Return     : void
 Other      :
*****************************************************************************/
static inline void BSP_PWC_DelTimer4WakeSrc(void)
{
    return;
}

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEPVOTE_LOCK
 ��������  : �����ֹ˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
static inline unsigned int  DRV_PWRCTRL_SLEEPVOTE_LOCK(PWC_CLIENT_ID_E enClientId)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 ��������  : ��������˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
static inline unsigned int  DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWC_CLIENT_ID_E enClientId)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 ��������  : AT^PSTANDBY
 �������  :
 �������  :
 ����ֵ��
*****************************************************************************/
static inline unsigned int DRV_PWRCTRL_STANDBYSTATEACPU(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0;
}

/*dload begin*/

#if 1
/* Begin: DRVΪOAMʵ��NV���ݻָ����̶��ṩ�Ľӿ� */

/********************************************************************************************************
 �� �� ��  : DRV_UPGRADE_NV_SET_RESULT
 ��������  : OAMͨ���ýӿڸ��ߵ���NV�����ɹ��˻���ʧ����
 �������  : status��0      ��ʾNV�����ɹ�
                     ����ֵ ��ʾNV����ʧ��
 �������  :
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ����ע��  : V3R3 SFT �� V9 BBIT ��׮
             V9 SFT  ʵ��
                ���NV�����ɹ���������fastboot�������óɹ���ʶ
                ���NV����ʧ�ܣ�������fastboot��������ʧ�ܱ�ʶ

 �޸���ʷ  :
 1.��    ��   : 2012��12��6��
   ��    ��   : ��ϲ 00220237
   �޸�����   : �����ɺ���
********************************************************************************************************/
static inline int DRV_UPGRADE_NV_SET_RESULT(int status)
{
    return 0;
}

/********************************************************************************************************
 �� �� ��  : DRV_NV_FILE_SEC_CHECK
 ��������  : ���ļ�����У��
 �������  : pnvFilePath����У���ļ���·��
 �������  :
 �� �� ֵ  : 0 :    �ļ�У����ȷ
             -1��   �ļ�У��ʧ��
 ����ע��  : Ŀǰ�������߱���ֱ�Ӵ�׮���Ժ�ʵ��

 �޸���ʷ  :
 1.��    ��   : 2012��12��6��
   ��    ��   : ��ϲ 00220237
   �޸�����   : �����ɺ���
********************************************************************************************************/
static inline int DRV_NV_FILE_SEC_CHECK(char * pnvFilePath)
{
    return 0;
}

/********************************************************************************************************
 �� �� ��  : BSP_DLOAD_NVBackupRead
 ��������  : ��Flash�е�NV�������ȡ���ݣ�ʵ��NV��Ļָ����ܡ�
 �������  : len����NV�������ʼ����ʼ����Ҫ��ȡ��NV��ȣ��ֽ�������
 �������  : pRamAddr��Ŀ��RAM��ַ�����ڴ�Ŷ�����NV�����ݡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ����ע��  : V3R3 SFT �� V9 BBIT ����ԭ��
             V9 SFT  ������nand�ӿ��޸�Ϊ����emmc�ӿڶ�дNV������

 �޸���ʷ  :
 1.��    ��   : 2012��12��6��
   ��    ��   : ��ϲ 00220237
   �޸�����   : �޸ĺ���
********************************************************************************************************/
static inline int DRV_NVBACKUP_READ(unsigned char *pRamAddr, unsigned int len)
{
    return 0;
}

/********************************************************************************************************
 �� �� ��  : BSP_DLOAD_NVBackupWrite
 ��������  : ���ض�����д��Flash�е�NV�������ʵ��NV��ı��ݹ��ܡ�
 �������  : pRamAddr��ԴRAM��ַ�����ڴ����Ҫд���NV�����ݡ�
             len����NV�������ʼ����ʼ����Ҫд���NV��ȣ��ֽ�������
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ����ע��  : V3R3 SFT �� V9 BBIT ����ԭ��
             V9 SFT  ������nand�ӿ��޸�Ϊ����emmc�ӿڶ�дNV������

 �޸���ʷ  :
 1.��    ��   : 2012��12��6��
   ��    ��   : ��ϲ 00220237
   �޸�����   : �޸ĺ���
********************************************************************************************************/

static inline int DRV_NVBACKUP_WRITE(unsigned char *pRamAddr, unsigned int len)
{
    return 0;
}





#endif


#define UART_IOCTL_GET_RD_BUFF       0x7F001011
#define UART_IOCTL_SET_READ_CB       0x7F001001

typedef enum
{
    WWAN_WCDMA    = 1,/*WCDMAģʽ*/
    WWAN_CDMA    = 2  /*CDMAģʽ*/
}NDIS_WWAN_MODE;

/*�ܽ��źŵĶ���*/
#define IO_CTRL_FC                      (0x02)
#define IO_CTRL_DSR                     (0x20)
#define IO_CTRL_DTR                     (0x01)
#define IO_CTRL_RFR                     (0x04)
#define IO_CTRL_CTS                     (0x10)
#define IO_CTRL_RI                      (0x40)
#define IO_CTRL_DCD                     (0x80)

#define DRV_GPIO_USB_SWITCH     200
#define DRV_GPIO_HIGH           1
#define DRV_GPIO_LOW            0

#define AT_USB_SWITCH_SET_VBUS_INVALID          2

/* �豸ö�����˿ڸ��� */
#define DYNAMIC_PID_MAX_PORT_NUM        17

/* NV��50091�ṹ�������豸��Ҫö�ٵĶ˿���̬ */
typedef struct
{
    unsigned int ulStatus;
    unsigned char aucFirstPortStyle[DYNAMIC_PID_MAX_PORT_NUM];  /* �豸�л�ǰ�˿���̬ */
    unsigned char aucRewindPortStyle[DYNAMIC_PID_MAX_PORT_NUM]; /* �豸�л���˿���̬ */
    unsigned char reserved[22];
}DRV_DYNAMIC_PID_TYPE_STRU;

typedef void(* USB_NET_DEV_SWITCH_GATEWAY)(void);

static inline int DRV_OS_STATUS_SWITCH(int enable)
{
    return 0;
}

static inline int DRV_GET_LINUXSYSTYPE(void)
{
    return -1;
}

static inline unsigned int DRV_SET_PORT_QUIRY(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType)
{
    return 0;
}

static inline int DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC(USB_NET_DEV_SWITCH_GATEWAY switchGwMode)
{
    return 0;
}

static inline unsigned int DRV_GET_U2DIAG_DEFVALUE(void)
{
    return 0;
}

static inline int DRV_GET_DIAG_MODE_VALUE(unsigned char *pucDialmode,
                                          unsigned char *pucCdcSpec)
{
    return 0;
}

static inline int DRV_USB_PHY_SWITCH_SET(unsigned char ucValue)
{
    return 0;
}

static inline int DRV_USB_PORT_TYPE_VALID_CHECK(unsigned char *pucPortType,
                                                unsigned int ulPortNum)
{
    return 0;
}

static inline int DRV_UDIAG_VALUE_CHECK(unsigned int DiagValue)
{
    return 0;
}

static inline int DRV_U2DIAG_VALUE_CHECK(unsigned int DiagValue)
{
    return 0;
}

static inline unsigned char DRV_GET_PORT_MODE(char*PsBuffer, unsigned int*Length)
{
    return 0;
}

static inline int DRV_SET_PID(unsigned char u2diagValue)
{
    return 0;
}

static inline int DRV_GPIO_SET(unsigned char ucGroup, unsigned char ucPin, unsigned char ucValue)
{
    return 0;
}

static inline void DRV_AT_SETAPPDAILMODE(unsigned int ulStatus)
{
    return;
}
/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ���ص�ǰ��Ʒ����
 �������   : ��
 �������   : ��
 �� �� ֵ   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
static inline unsigned int BSP_MNTN_ProductTypeGet(void)
{
	return 0;
}
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

static inline int DRV_SDMMC_GET_STATUS(void)
{
    return 0;
}

/*om use begin*/
/*VERSIONINFO_I���ݽṹ�а汾�ַ��������Ч�ַ�����*/
#define VER_MAX_LENGTH                  30

typedef struct
{
    unsigned char CompId;              /* ����ţ��μ�COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* ���汾���� 30 �ַ�+ \0 */
}VERSIONINFO_I;

typedef enum{
    ADDRTYPE8BIT,
    ADDRTYPE16BIT,
    ADDRTYPE32BIT
}ENADDRTYPE;

typedef struct tagBSP_OM_NET_S
{
    unsigned int u32NetRxStatOverFlow;       /* ����FIFO���ͳ�Ƽ��� */
    unsigned int u32NetRxStatPktErr;         /* �����ܴ������ */
    unsigned int u32NetRxStatCrcErr;         /* ����CRC������� */
    unsigned int u32NetRxStatLenErr;         /* ������Ч���Ȱ����� */
    unsigned int u32NetRxNoBufInt;           /* ����û��BUFFER�жϼ��� */
    unsigned int u32NetRxStopInt;            /* ����ֹͣ�жϼ��� */
    unsigned int u32NetRxDescErr;            /* �������������� */

    unsigned int u32NetTxStatUnderFlow;      /* ����FIFO����ͳ�Ƽ��� */
    unsigned int u32NetTxUnderFlowInt;       /* ����FIFO�����жϼ��� */
    unsigned int u32NetTxStopInt;            /* ����ֹͣ�жϼ��� */
    unsigned int u32NetTxDescErrPs;          /* ��������������(Ps) */
    unsigned int u32NetTxDescErrOs;          /* ��������������(Os) */
    unsigned int u32NetTxDescErrMsp;         /* ��������������(Msp) */

    unsigned int u32NetFatalBusErrInt;      /* ���ߴ���*/
}BSP_OM_NET_S;

/*om use end*/

/*taf used*/
enum SECURE_ENABLE_STATUS_I
{
    SECURE_DISABLE = 0,
    SECURE_ENABLE = 1
};

static inline int DRV_FILE_GET_DISKSPACE(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}
/*liuyi--*/

#if 1  /*drv_timer.h*/
extern unsigned int omTimerGet(void);
#define DRV_GET_SLICE() omTimerGet()
#endif

#if 1  /*drv_oled.h*/

/*****************************************************************************
*  Function:  DRV_OLED_CLEAR_WHOLE_SCREEN
*  Description: oled clear *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern void DRV_OLED_CLEAR_WHOLE_SCREEN(void);

/*****************************************************************************
*  Function:  DRV_OLED_UPDATE_STATE_DISPLAY
*  Description: oled display right or not right  *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern  void DRV_OLED_UPDATE_STATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 �� �� ��  : DRV_OLED_UPDATE_DISPLAY
 ��������  : SD����Ƭ�汾������OLED��ʾ
 �������  : BOOL UpdateStatus
 �������  : �ޡ�
 ����ֵ��   ��
 ����:  �����ɹ���NV������ɺ���øú�����
        ����ʧ�ܺ���øú������
*****************************************************************************/
extern void DRV_OLED_UPDATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 �� �� ��  : DRV_OLED_STRING_DISPLAY
 ��������  : oled�ַ�����ʾ����
 �������  :
 *           Ҫ��ʾ�ַ�������ʼ����
 *           Ҫ��ʾ���ַ���
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
extern void DRV_OLED_STRING_DISPLAY(unsigned char ucX, unsigned char ucY, unsigned char *pucStr);

#endif

#if 1  /*drv_nve.h*/
#define BSP_NVE_NAME_LENGTH          8       /*NV name maximum length*/
#define BSP_NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define BSP_NV_READ                 1       /*NV read  operation*/
#define BSP_NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	unsigned int nv_operation;              /*0-write,1-read*/
	unsigned int nv_number;                 /*NV number you want to visit*/
	char nv_name[BSP_NVE_NAME_LENGTH];
	unsigned int valid_size;
	unsigned char nv_data[BSP_NVE_NV_DATA_SIZE];
}NVE_INFO_S;

/*****************************************************************************
* �� �� ��  : DRV_NVE_ACCESS
*
* ��������  : ����LINUX NVE
*
* �������  : nve  ID
*
* �������  : ��
*
* �� �� ֵ  : OK& ERROR
*
* �޸ļ�¼ :  2013��6��27��  v1.00  yuanqinshun  ����
*****************************************************************************/
int DRV_NVE_ACCESS(NVE_INFO_S *nve);
#endif

#if 1  /*drv_nv.h*/
/*****************************************************************************
 �� �� ��  : DRV_COPY_NVUSE_TO_NVBACKUP
 ��������  : ��NV��ʹ����������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : int��0�ɹ�������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��21��
    ��    ��   : ��� y00186965
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int DRV_COPY_NVUSE_TO_NVBACKUP ( void );


/*****************************************************************************
 �� �� ��  : DRV_COPY_NVUPGRADE_TO_NVUSE
 ��������  : ��NV��������������ʹ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : int��0�ɹ�������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��21��
    ��    ��   : ��� y00186965
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int DRV_COPY_NVUPGRADE_TO_NVUSE( void );
#endif

typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
#define EXCH_CB_NAME_SIZE           (32)
typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char *pucData;
    unsigned int  ulDataLen;
}cb_buf_t;

typedef int  (*exchCBReg)(cb_buf_t *);

/*liuyi++ �ýӿ����ĵ���δ���� ++*/
/*******************************************************************************
 �� �� ��: DRV_EXCH_CUST_FUNC_REG
 ��������: ��������ģ���ṩ����ӿڣ����ϲ�ע��ص������ڸ�λʱ�����ϲ�ָ����Ϣ
 �������: cb �ϲ�ָ���ص��ӿ�
 �������: ��
 �� �� ֵ: 0-��ӳɹ�������-���ʧ��
 ˵��    :  pucData :ָ����¼��Ϣ��ַ����ע�ⲻҪָ��ջ����ʱ���������ѿռ����ݣ�
                     ʹ�����Լ�ά���������ռ�ʹ���꣬�Լ��ͷš�����ȫ�ֱ�����
            aucName :����
            ulDataLen: ���ݳ���

����ֵ�б�:
    CUST_REG_OK = 0,                        ��ӳɹ�
    CUST_REG_PARM_NULL,                     ���Ϊ��
    CUST_REG_EXCH_NOT_READY,                EXCHģ����δ��ʼ��
    CUST_REG_EXCH_REBOOT_CONTEXT,           �Ѿ����븴λ����
    CUST_REG_EXCH_QUEUE_NOT_INIT,           ע�������δ��ʼ��
    CUST_REG_EXCH_QUEUE_FULL,               ��������
    CUST_REG_EXCH_ALREADY_IN_QUEUE,         �ظ�ע��
    CUST_REG_EXCH_MUTEX_REJECT,             MUTEX REJECT
    CUST_REG_EXCH_QUEUE_IN_ERR              �����ʧ��

��ͨ������ֵ��λ�������

*******************************************************************************/
extern int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb);
/*liuyi++ �ýӿ����ĵ���δ���� --*/

/*liuyi++ �ýӿ����ĵ���δ����*/
/*****************************************************************************
* �� �� ��  : DRV_MSP_PROC_REG
*
* ��������  : DRV�ṩ��OM��ע�ắ��
*
* �������  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*
*****************************************************************************/
#define DRV_MSP_PROC_REG(eFuncID, pFunc)
/*liuyi++ �ýӿ����ĵ���δ����--*/


/************************* �����ýṹ��(����ɾ��) ***************************/

/*TCP/IPЭ��ջ��ά�ɲⲶ�����Ϣ��ʶ*/
enum IPS_MNTN_TRACE_IP_MSG_TYPE_ENUM
{
    /* IP ���ݰ���ά�ɲ��ϱ� */
    ID_IPS_TRACE_IP_ADS_UL                  = 0xD030,
    ID_IPS_TRACE_IP_ADS_DL                  = 0xD031,
    ID_IPS_TRACE_IP_USB_UL                  = 0xD032,
    ID_IPS_TRACE_IP_USB_DL                  = 0xD033,

    ID_IPS_TRACE_IP_MSG_TYPE_BUTT
};

static inline unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOutTimeout)
{
    return 0;
}

static inline unsigned long USB_ETH_DrvSetDeviceAssembleParam(
    unsigned long ulEthTxMinNum,
    unsigned long ulEthTxTimeout,
    unsigned long ulEthRxMinNum,
    unsigned long ulEthRxTimeout)
{
    return 0;
}

static inline unsigned int DRV_USB_GET_AVAILABLE_PORT_TYPE(unsigned char *pucPortType,
                            unsigned int *pulPortNum, unsigned int ulPortMax)
{
    return 0;
}

static inline int USB_otg_switch_get(unsigned char *pucValue)
{
    return 0;
}
#define DRV_USB_PHY_SWITCH_GET(value) USB_otg_switch_get(value)
#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2
#define USB_SWITCH_ON       1
#define USB_SWITCH_OFF      0


typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
static inline unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc)
{
    return 0;
}
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
static inline unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc)
{
    return 0;
}
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)

static inline unsigned int BSP_GetHsicEnumStatus(void)
{
    return 0;
}
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()


/************************* �����ýṹ�� END *********************************/

//struct sk_buff;
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
static inline unsigned int DRV_USB_REG_IPS_TRACECB(USB_IPS_MNTN_TRACE_CB_T pFunc)
{
    if (!pFunc)
    {
        return 1;
    }

    return 0;
}

unsigned int DRV_UTRACE_START(unsigned char * pData);
unsigned int DRV_UTRACE_TERMINATE(unsigned char * pData);

#ifdef __cplusplus
}
#endif
#endif
