


#ifndef __DRV_NV_DEF_H__
#define __DRV_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define LDO_GPIO_MAX        2
#define RSE_MIPI_SW_REG_NUM 8
#define RSE_MODEM_NUM       2
#define PASTAR_NUM   2

#ifndef s8
typedef signed char s8;
#endif
#ifndef u8
typedef unsigned char u8;
#endif
#ifndef s16
typedef signed short s16;
#endif
#ifndef u16
typedef unsigned short u16;
#endif
#ifndef s32
typedef signed int s32;
#endif
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef s64
typedef signed long long s64;
#endif
#ifndef u64
typedef unsigned long long u64;
#endif
/*******************************************************************/

/*****************************************************************************
 �ṹ��    : nv_protocol_base_type
 �ṹ˵��  : nv_protocol_base_type�ṹ ID= en_NV_Item_Modem_Log_Path 148
 			MBB��̬ modem log·��������������������̬��modem log·����
*****************************************************************************/
/*NV ID = 50018*/
#pragma pack(push)
#pragma pack(1)
	typedef struct
	{
		s32 	   nvStatus;
		s8		   nv_version_info[30];
	}NV_SW_VER_STRU;
#pragma pack(pop)
/*END NV ID = 50018*/

typedef struct
{
   char  ucModemLogPath[32];
   char  modemLogRsv[4];
}NV_MODEM_LOG_PATH;



/*NV ID = 0xd109*/
/*ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر�*/
typedef struct
{
	s32 buck2_switch;    /*[0, 1]*/
}NV_PASTAR_BUCK2_SWITCH_STRU;
/*end NV ID = 0xd109*/

/*NV ID  = 0xd10b*/

typedef struct ST_PWC_SWITCH_STRU_S {

	/*����NV���ڵ͹��ĵ�������ƣ�������ЩBIT��ʱδ�ã�������ʱ�������Ϊ׼ȷ������*/
 	u32 deepsleep  :1; /*bit0*/
    u32 lightsleep :1; /*bit1*/
    u32 dfs        :1; /*bit2*/
    u32 hifi       :1; /*bit3*/
    u32 drxAbb     :1; /*bit4*/
    u32 drxZspCore :1; /*bit5*/
    u32 drxZspPll  :1; /*bit6*/
    u32 drxWLBbpPll  :1; /*bit7*/
    u32 drxGBbpPll   :1; /*bit8*/
    u32 drxRf      :1; /*bit9*/
    u32 drxPa      :1; /*bit10*/
    u32 drxGuBbpPd   :1; /*bit11*/
    u32 drxDspPd     :1; /*bit12*/
    u32 drxLBbpPd    :1; /*bit13*/
    u32 drxPmuEco    :1; /*bit14*/
    u32 drxPeriPd    :1; /*bit15*/
    u32 l2cache_mntn  :1; /*bit16*/
    u32 bugChk     :1; /*bit17*/
    u32 pmuSwitch     :1; /*bit18*/
    u32 drxLdsp      :1;  /*bit 19*/
    u32 matserTDSpd  :1; /*bit20*/
    u32 tdsClk    :1;  /*bit21*/
    u32 slaveTDSpd   :1; /*bit22*/
    u32 slow	     :1;/*bit23*/
    u32 reserved    :8; /*bit24-31*/

	/*����NV����DEBUG���µ�Ϳ�����*/
	u32 drx_pa_pd        :1; /*bit0 ���ڿ���PA�����µ�*/
    u32 drx_rfic_pd      :1; /*bit1 ���ڿ���RFIC�����µ�*/
    u32 drx_rfclk_pd     :1; /*bit2 ���ڿ���RFIC CLK�����µ�*/
    u32 drx_fem_pd       :1; /*bit3 ���ڿ���FEM�����µ�*/
    u32 drx_cbbe16_pd    :1; /*bit4 ���ڿ���CBBE16�����µ�*/
    u32 drx_bbe16_pd     :1; /*bit5 ���ڿ���BBE16�����µ�*/
    u32 drx_abb_pd       :1; /*bit6 ���ڿ���ABB�����µ�*/
    u32 drx_bbp_init     :1; /*bit7 ���ڿ���BBPĬ�Ͻ��ӵ�ȫ������*/
    u32 drx_bbppwr_pd    :1; /*bit8 ���ڿ���BBP��Դ�е����µ�*/
    u32 drx_bbpclk_pd    :1; /*bit9 ���ڿ���BBPʱ���еĿ�����*/
    u32 drx_bbp_pll      :1; /*bit10 ���ڿ���BBP_PLL�Ŀ�����*/
    u32 drx_cbbe16_pll   :1; /*bit11 ���ڿ���CBBE16_PLL�Ŀ�����*/
    u32 drx_bbe16_pll    :1; /*bit12 ���ڿ���BBE16_PLL�Ŀ�����*/
    u32 drx_bbp_reserved :1; /*bit13 bbpԤ��*/
    u32 drx_abb_gpll     :1; /*bit14 ���ڿ���ABB_GPLL�Ŀ�����*/
    u32 drx_abb_scpll    :1; /*bit15 ���ڿ���ABB_SCPLL�Ŀ�����*/
    u32 drx_abb_reserved1:1;
    u32 drx_abb_reserved2:1;
    u32 reserved2        :14; /*bit18-31 δ��*/
}ST_PWC_SWITCH_STRU;

typedef struct ST_PWC_PM_DEBUG_CFG_STRU_S {
    u32 sr_time_ctrl :1;    /*bit0*/
	u32 bugon_reset_modem:1;/*bit1*/
	u32 print_to_ddr:1;/*bit2*/
    u32 reserved     :29;/*bit3-31*/
    /*����NV����PM ʱ����ֵ����*/
    u32 dpm_suspend_time_threshold ;/*���ڿ���dpm suspend��ֵ*/
    u32 dpm_resume_time_threshold  ;/*���ڿ���dpm resume��ֵ*/
    u32 pm_suspend_time_threshold  ;/*���ڿ���pm suspend��ֵ*/
    u32 pm_resume_time_threshold   ;/*���ڿ���pm resume��ֵ*/
}ST_PWC_PM_DEBUG_CFG_STRU;

/*NV ID = 0xd10c*/
typedef struct ST_PWC_DFS_STRU_S {
    u32 CcpuUpLimit;
	u32 CcpuDownLimit;
	u32 CcpuUpNum;
	u32 CcpuDownNum;
	u32 AcpuUpLimit;
	u32 AcpuDownLimit;
	u32 AcpuUpNum;
	u32 AcpuDownNum;
	u32 DFSTimerLen;
	u32 DFSHifiLoad;
 	u32 Strategy;/*ʹ�ú��ֲ���bit0:1->200ms���ؼ��,bit0:0->4s���ؼ��;bit1:1/0��/�رո���DDR��Ƶ*/
 	u32 DFSDdrUpLimit;
 	u32 DFSDdrDownLimit;
 	u32 DFSDdrprofile;
 	u32 reserved;
}ST_PWC_DFS_STRU;

/*NV ID = 0xd10f begin������PMU�����쳣ʱ�Ĵ�������*/
typedef struct
{
    u8  VoltId;         /*��Ҫ�������õĵ�ѹԴ��id��*/
    u8  VoltOcpIsOff;   /*���õ�ѹԴ�����Ļ��Ƿ�رո�·��ѹԴ*/
    u8  VoltOcpIsRst;   /*���õ�ѹԴ�����Ļ��Ƿ�����ϵͳ*/
    u8  VoltOtpIsOff;   /*��PMU������Ҫ�رշǺ��ĵ�Դ�Ļ����Ƿ��ܹرո�·��ѹԴ*/
} PMU_VOLT_PRO_STRU;
typedef struct
{
    u8    ulOcpIsOn;        /*�����ĵ�Դ�ܷ����´�:0:���ܱ����´򿪣�1:�ܱ����´򿪣�Ĭ��Ϊ���ܴ�--0*/
    u8    ulOcpIsOff;       /*�����ĵ�Դ�Ƿ�ر�:0:���رգ�1:�رգ�Ĭ��Ϊ�ر�--1*/
    u8    ulOtpCurIsOff;    /*����(�����¶�Ԥ��ֵ)ʱ�Ƿ�رշǺ��ĵ�Դ:0:���رշǺ��ģ�1:�رշǺ��ĵ�Դ��Ĭ��Ϊ�رշǺ��ĵ�Դ--1*/
    u8    ulOtpIsRst;       /*����(�����¶�Ԥ��ֵ)ʱ�Ƿ�����ϵͳ:0:��������1:����ϵͳ��Ĭ��Ϊ������ϵͳ--0*/

    u8    ulOtpIsOff;       /*PMUоƬ���³���150��ʱPMU�Ƿ��µ�(����ʱ������):0:PMU���µ磬1:PMU�µ硣Ĭ��ΪPMU�µ�--1*/
    u8    ulUvpIsRst;       /*ǷѹԤ��ʱ�Ƿ�����ϵͳ��Ĭ��Ϊ0:������*/
    u16   reserved2;

    u16   ulOtpLimit;       /*�¶�Ԥ����ֵ����:105:105�棬115:115�棬125:125�� ��135:135�� (HI6559����֧��135)��Ĭ��Ϊ125��--125 */
    u16   ulUvpLimit;       /*ǷѹԤ����ֵ���ã���λmv:3000:3v; 2700:2.7v(2850:2.85v.HI6559֧��2.85,HI6551֧��2.7) ��Ĭ��Ϊ3v--3000*/

    PMU_VOLT_PRO_STRU VoltProConfig[50];/*ÿ·��ѹԴ���쳣�����������ã���ͬ��Ʒ��̬��Ҫ�������õĵ�ѹԴ����*/
} PMU_EXC_PRO_NV_STRU;

/*NV ID = 0xd10f end*/

/*ID=0xd110*/
typedef struct
{
    u32    u32CalcTime;        /* ����ʱ������(10ms) */
    u32    u32PktNum;          /* �ۼư����� */
    u32    u32SwichFlag;       /* netif���������俪�� */
} NETIF_INIT_PARM_T;

/*ID=0xd111 begin */
typedef struct
{
    u32 dump_switch    : 2; /* 00: excdump, 01: usbdump, 1x: no dump */
    u32 ARMexc         : 1; /* 2 ARM�쳣��⿪��*/
    u32 stackFlow      : 1; /* 3 ��ջ�����⿪��*/
    u32 taskSwitch     : 1; /* 4 �����л���¼����*/
    u32 intSwitch      : 1; /* 5 �жϼ�¼����*/
    u32 intLock        : 1; /* 6 ���жϼ�¼����*/
    u32 appRegSave1    : 1; /* 7 �Ĵ�����1��¼���� */
    u32 appRegSave2    : 1; /* 8 �Ĵ�����2��¼����*/
    u32 appRegSave3    : 1; /* 9 �Ĵ�����3��¼����*/
    u32 commRegSave1   : 1; /* 10 �Ĵ�����1��¼���� */
    u32 commRegSave2   : 1; /* 11 �Ĵ�����2��¼����*/
    u32 commRegSave3   : 1; /* 12 �Ĵ�����3��¼����*/
    u32 sysErrReboot   : 1; /* 13 systemError��λ����*/
    u32 reset_log      : 1; /* 14 ǿ�Ƽ�¼���أ���δʹ��*/
    u32 fetal_err      : 1; /* 15 ǿ�Ƽ�¼���أ���δʹ��*/
	u32 log_ctrl       : 2; /* bsp_trsce �������*/
    u32 reserved1      : 14;
} DUMP_CFG_STRU;

typedef struct
{
    union
    {
        u32         uintValue;
        DUMP_CFG_STRU   Bits;
    } dump_cfg;

    u32 appRegAddr1;	/* ACORE����Ĵ������ַ1*/
    u32 appRegSize1;	/* ACORE����Ĵ����鳤��1*/
    u32 appRegAddr2;	/* ACORE����Ĵ������ַ2*/
    u32 appRegSize2;	/* ACORE����Ĵ����鳤��2*/
    u32 appRegAddr3;	/* ACORE����Ĵ������ַ3*/
    u32 appRegSize3;	/* ACORE����Ĵ����鳤��3*/

    u32 commRegAddr1;	/* CCORE����Ĵ������ַ1*/
    u32 commRegSize1;	/* CCORE����Ĵ����鳤��1*/
    u32 commRegAddr2;	/* CCORE����Ĵ������ַ2*/
    u32 commRegSize2;	/* CCORE����Ĵ����鳤��2*/
    u32 commRegAddr3;	/* CCORE����Ĵ������ַ3*/
    u32 commRegSize3;	/* CCORE����Ĵ����鳤��3*/

    u32 traceOnstartFlag;           /* 0:��������Trace, ��0:����������Trace */
    u32 traceCoreSet;               /* 0:�ɼ�A��Trace, 1:�ɼ�C��Trace, 2:�ɼ�˫��Trace */
    u32 busErrFlagSet;             /* 0:���������������߹�������, ��0:�������������߹������� */
} NV_DUMP_STRU;
/*ID=0xd111 end */

/*NV ID = 0xd114 begin,����PMU��ʼ��ʱӦ�������ʵ�ֵĻ�������*/
#define NUM_OF_PMU_NV  50
typedef struct
{
    u8  VoltId;     /*��Դid��*/
    u8  IsNeedSet;  /*�Ƿ���Ҫ�������:0:����Ҫ��1:��Ҫ*/
    u8  IsOnSet;    /*Ĭ���Ƿ���Ҫ������ѹԴ:0:����Ҫ��1:��Ҫ*/
    u8  IsOffSet;   /*Ĭ���Ƿ���Ҫ�رյ�ѹԴ:0:����Ҫ��1:��Ҫ*/

    u8  IsVoltSet;  /*�Ƿ���Ҫ���õ�ѹ:0:����Ҫ��1:��Ҫ*/
    u8  IsEcoSet;   /*�Ƿ���Ҫ����ECOģʽ:0:����Ҫ��1:��Ҫ*/
    u8  EcoMod;     /*��Ҫ���õ�ecoģʽ:0:normal;2:force_eco;3:follow_eco*/
    u8  reserved3;  /*Ĭ��*/

    u32 Voltage;    /*��Ҫ���õ�Ĭ�ϵ�ѹ*/
} PMU_INIT_CON_STRU;
typedef struct
{
    PMU_INIT_CON_STRU InitConfig[NUM_OF_PMU_NV];
} PMU_INIT_NV_STRU;
/*NV ID = 0xd114 end*/

/*NV ID = 0xd115 start*/

typedef struct {
    u32	index;           /*Ӳ���汾����ֵ(��汾��1+��汾��2)�����ֲ�ͬ��Ʒ*/
    u32	hwIdSub;        /*Ӳ���Ӱ汾�ţ����ֲ�Ʒ�Ĳ�ͬ�İ汾*/
	char  name[32];           /*�ڲ���Ʒ��*/
    char	namePlus[32];       /*�ڲ���Ʒ��PLUS*/
    char	hwVer[32];          /*Ӳ���汾����*/
    char	dloadId[32];        /*������ʹ�õ�����*/
    char	productId[32];      /*�ⲿ��Ʒ��*/
}PRODUCT_INFO_NV_STRU;

/*NV ID =0xd115 end*/

/*NV ID =0xd116 start,mipi0_chn*/
typedef struct{
	u32 mipi_chn;
}MIPI0_CHN_STRU;
/*NV ID =0xd116 end,mipi0_chn*/

/*NV ID =0xd117 start,mipi1_chn*/
typedef struct{
	u32 mipi_chn;
}MIPI1_CHN_STRU;
/*NV ID =0xd117 end,mipi1_chn*/

/*NV ID =0xd12e start, rf power control, pastar config*/
typedef struct{
	u32 rfpower_m0;/*[0, 1,2]*//*modem0,����ͨ��0�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾLDO����*/
	u32 rfpower_m1;/*[0, 1,2]*//*modem1,����ͨ��1�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾLDO����*/
}NV_RFPOWER_UNIT_STRU;
/*NV ID =0xd12e start, pastar config*/

/* NV ID =0xd13A start, pa power control, pastar config */
typedef struct{
	u32 papower_m0;/*[0,1,2]*//*modem0,����ͨ��0�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع���*/
	u32 papower_m1;/*[0,1,2]*//*modem1,����ͨ��1�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع���*/
}NV_PAPOWER_UNIT_STRU;
/* NV ID =0xd13A start, pastar config */

typedef struct
{
    u32   nvSysTimeValue;   /* ��õ���ϵͳ����ʱ�� */
}SYS_TIME;

typedef struct
{
    u32  ulIsEnable;				/*�¶ȱ���ʹ��*/
    u32    lCloseAdcThreshold;
    u32  ulTempOverCount;
}CHG_BATTERY_HIGH_TEMP_PROT_NV;

typedef struct
{
    u32  ulIsEnable;			/*�¶ȱ���ʹ��*/
    u32    lCloseAdcThreshold;
    u32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTE_NV;

/* ����ģʽnv��,0 : �ǹ���ģʽ 1: ����ģʽ**/
typedef struct
{
    u32 ulFactoryMode;
}FACTORY_MODE_TYPE;

/* �����������Դ��� */
typedef struct
{
    u32 ulTryTimes;
}BOOT_TRY_TIMES_STRU;

/* ������������ʱ�� */
typedef struct
{
    u32 ulPowKeyTime;
}POWER_KEY_TIME_STRU;

typedef struct
{
    u16 temperature;
    u16 voltage;
}CHG_TEMP_ADC_TYPE;

typedef struct
{
    CHG_TEMP_ADC_TYPE g_adc_batt_therm_map[31];
}NV_BATTERY_TEMP_ADC;


/*Ӳ��汾nv��,1 : Ӳ��汾 0: ��Ӳ��汾*/
typedef struct
{
    u32 ulHwVer;
}E5_HW_TEST_TYPE;

/*�Ƿ�֧��APT����nv��,1 : ֧�� 0: ��֧��*/
typedef struct
{
    u32 ulIsSupportApt;
}NV_SUPPORT_APT_TYPE;

/*PMU�쳣����nv��*/
typedef struct
{
    u8 TemppmuLimit;  /*PMU�¶���ֵ:0:105��;1:115��;2:125��;3:135��*/
	u8 ulCurIsOff;  /*����ʱ����Դ�Ƿ��µ磺0���µ磻1�����µ�*/
	u8 ulOcpIsRst;  /*����ʱ�Ƿ������λ: 0:����λ 1:��λ*/
	u8 PmuproIsOn;  /*PMU�쳣���������Ƿ�����0����������1������*/
}PMU_PRO_NV;

typedef struct
{
    u32 u32SciGcfStubFlag;   /* 1: GCF����ʹ�ܣ�0��GCF���Բ�ʹ�� */
}SCI_NV_GCF_STUB_FLAG;

/*���ٿ��ػ������Ƿ�ʹ��NV��*/
typedef struct
{
    u32 ulEnable;   /*���ٿ��ػ��Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
}NV_SHORT_ONOFF_ENABLE_TYPE;

/*���ٿ��ػ�����������ϢNV��*/
typedef struct NV_SHORT_ONOFF_TYPE_S
{
    u32 ulPowerOffMaxTimes;   /*֧�ֵ����ٹػ�����*/
	u32 ulMaxTime;            /*�ٹػ���ʷ�ۼ�ʱ����ڵ��ڴ�ʱ���Զ���ػ�����λСʱ*/
	u32 ulVoltLevel1;         /*���ű�����һ����ѹ����*/
	u32 ulVoltLevel2;         /*���ű����ڶ�����ѹ����*/
	u32 ulRTCLevel1;          /*С�ڵ�һ����ѹ��Ӧ��RTC����ʱ��*/
	u32 ulRTCLevel2;          /*��һ���͵ڶ���֮���ѹ��Ӧ��RTC����ʱ��*/
	u32 ulRTCLevel3;          /*���ڵ��ڵڶ�����ѹ��Ӧ��RTC����ʱ��*/
}NV_SHORT_ONOFF_TYPE;

/*ʡ��ģʽ���ã���ʶ�������Ƿ�ʹ��NV��*/
typedef struct
{
        u32 ulLEDEnable;   /*������LED �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
        u32 ulReserved1;   /*����Ԥ��  �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
        u32 ulReserved2;   /*����Ԥ��  �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
}NV_POWER_SAVE_TYPE;

/*���ؼƵ�ѹ������У׼����*/
typedef struct
{
    u32 v_offset_a;         /* ��ѹУ׼���Բ��� */
    s32 v_offset_b;         /* ��ѹУ׼����ƫ��*/
    u32 c_offset_a;         /* ����У׼���Բ��� */
    s32 c_offset_b;         /* ����У׼����ƫ�� */
}COUL_CALI_NV_TYPE;

/*�¶ȱ���HKADC����ͨ�������� NV_ID_DRV_TEMP_HKADC_CONFIG            = 0xd120 */

typedef struct
{
    u32 out_config;         /* bit0-bit1 0:����� 1:������� 2:ѭ����� */
                                /* bit2 1:������� 0:�ǻ������ */
                                /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                /* bit8: A����� */
                                /* bit9: C����� */
    u32 have_config;
    u16 out_period;         /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    u16 convert_list_len;   /* �¶�ת������ */
    u16 convert_list_id;    /* �¶�ת����NV��־��ʵ�ʳ��Ȳμ�usTempDataLen */
    u16 reserved;
}TEMP_HKADC_CHAN_CONFIG;

typedef struct
{
    TEMP_HKADC_CHAN_CONFIG chan_config[16];

}TEMP_HKADC_CHAN_CONFIG_ARRAY;

/*�¶ȱ���HKADC����ͨ�������� NV_ID_DRV_TEMP_TSENS_CONFIG            = 0xd121 */
typedef struct
{
    u16 enable;         /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    u16 high_thres;     /* оƬ���±����ĵ�ѹ��ֵ  */
    u16 high_count;     /* оƬ���±����������ޣ�ϵͳ�ػ� */
    u16 reserved;
    /*u32 low_thres;*/  /* оƬ���±����ĵ�ѹ��ֵ */
    /*u32 low_count;*/  /* оƬ���±����������ޣ�ϵͳ�ػ� */

}TEMP_TSENS_REGION_CONFIG;

typedef struct
{
    TEMP_TSENS_REGION_CONFIG region_config[3];

}TEMP_TSENS_REGION_CONFIG_ARRAY;



/*�¶ȱ�����ظߵ��±���  NV_ID_DRV_TEMP_BATTERY_CONFIG          = 0xd122 */
typedef struct
{
    u16 enable;        /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    u16 hkadc_id;      /* ϵͳ�ŵ��¶ȱ�����hkadcͨ��ID */
    u16 high_thres;    /* ϵͳ�ŵ���±������¶ȷ�ֵ */
    u16 high_count;    /* ϵͳ�ŵ���±����������� */
    s16 low_thres;     /* ϵͳ�ŵ���±������¶ȷ�ֵ */
    u16 low_count;     /* ϵͳ�ŵ���±������� */

    u32 reserved[2];   /*����*/
} DRV_SYS_TEMP_STRU;

/*�¶ȱ��������߼�ת����  NV_ID_DRV_TEMP_CHAN_MAP          = 0xd126 */
typedef struct
{
    u8 chan_map[32];

}TEMP_HKADC_PHY_LOGIC_ARRAY;

/* USB Feature for usb id:50075 */
typedef struct
{
    u8 flags;                 
    u8 reserve1; 
    u8 hibernation_support;/**/
    u8 pc_driver;
    u8 detect_mode;/*0=pmu detect; 1=no detect(for fpga&cpe); 2=car module vbus detect */
    u8 enable_u1u2_workaround;
    u8 otg_gpio_detect;
    u8 reserved7;
} NV_USB_FEATURE;


typedef struct
{
    u32 sci_dsda_select;        /* 0: sim0, 1:sim1*/
} DRV_SCI_DSDA_SELECT;
/* SIM gcf test flage*/
typedef struct
{
    u32 sci_gcf_sub_flag;        /* 0: open, 1:close */
} DRV_SCI_GCF_STUB_FLAG;

/*E5���ڸ���*/
typedef struct
{
	u32 wait_usr_sele_uart : 1;//[bit 0-0]1: await user's command for a moment; 0: do not wait
	u32 a_core_uart_num    : 2;//[bit 1-2]the number of uart used by a core
	u32 c_core_uart_num    : 2;//[bit 3-4]the number of uart used by c core
	u32 m_core_uart_num    : 2;//[bit 5-6]the number of uart used by m core
	u32 a_shell            : 1;//[bit 7-7]0:ashell is not used; 1:ashell is used
	u32 c_shell            : 1;//[bit 8-8]0:cshell is not used; 1:cshell is used
	u32 uart_at            : 1;//[bit 9-9]uart at control
	u32 extendedbits       : 22;//[b00]1:open cshell_auart; 0:close
}DRV_UART_SHELL_FLAG;

/* product support module nv define */
typedef struct
{
	u32 sdcard 		: 1;//1: support; 0: not support
	u32 charge 		: 1;
	u32 wifi    	: 1;
	u32 oled    	: 1;
	u32 hifi        : 1;
	u32 onoff       : 1;
	u32 hsic        : 1;
	u32 localflash  : 1;
	u32 reserved    : 24;
} DRV_MODULE_SUPPORT_STRU;

/* TEST support module nv define */
typedef struct
{
	u32 lcd 		: 1;//1: support; 0: not support
	u32 emi 		: 1;
	u32 pwm     	: 1;
	u32 i2c    	    : 1;
	u32 leds        : 1;
	u32 reserved    : 27;
} DRV_MODULE_TEST_STRU;

typedef struct
{
	u8 normalwfi_flag;
	u8 deepsleep_flag;
	u8 buck3off_flag;
	u8 peridown_flag;
	u32 deepsleep_Tth;
	u32 TLbbp_Tth;
}DRV_NV_PM_TYPE;


/* NV_ID_DRV_DDR_AUTOREF    = 0Xd152, */


/*
rank_num
ʵ��ʹ�õĵ�λ����,���� �¶ȹ��ߡ��¶ȹ��͡������������¶ȵ�λ��
�¶ȹ��� Ϊ��λ 0, �¶ȹ��� Ϊ���λ rank_num-1
��λ <=0 �� >=(rank_num-1)  ��Ϊ��Ч��λ

ddr_autoref_t
8���¶ȵ�λ����,�¶�<=[n]Ϊ n����
��λ0�¶ȹ���,7�¶ȹ���;����6������Ϊ��Ч��λ��
�����λ��������8�������������Ϊ�����

ddr_autoref_t2
ʹ���¶���Ϊ��λʱ����ֹ�ڵ�λ�¶ȸ�������ʱ Ƶ���л���λ
���¶ȴ� >ddr_autoref_t[n]�� n+1��λ������ <=ddr_autoref_t[n]��
��ͬʱ >ddr_autoref_t2[n]ʱ���򲻽��͵�n�����Ա���Ϊn+1��

ddr_autoref_cfg
8���¶ȵ�λ���� ��bitΪ0��ʾ�� ��bitΪ1��ʾ��
��λ0 7Ϊ��Ч��λ ��Ϊ0
�����λ��������8�������������Ϊ0

*/

/*
t(a,b] ��ʾ ddr_autoref_t[a]<�¶�<=ddr_autoref_t[b]
�¶ȵ�λ0  t(-,0] - ���õ�λ cfg[0] �¶ȹ�����Ч��λ
�¶ȵ�λ1  t(0,1] - ���õ�λ cfg[1]
�¶ȵ�λ2  t(1,2] - ���õ�λ cfg[2]
�¶ȵ�λ3  t(2,3] - ���õ�λ cfg[3]
�¶ȵ�λ4  t(3,4] - ���õ�λ cfg[4]
�¶ȵ�λ5  t(4,5] - ���õ�λ cfg[5]
�¶ȵ�λ6  t(5,6] - ���õ�λ cfg[6]
�¶ȵ�λ7  t(6,7] - ���õ�λ cfg[7] �¶ȹ�����Ч��λ
*/
    
#define DDR_AUTOREF_RANK_NUM 8
#define DDR_AUTOREF_ERR_CFG 0

typedef struct
{
    u32 enable_flag;
    u32 timeout;/* ms */
    u32 sleep_timeout;/* ms */
    u32 rank_num;       /* ʵ��ʹ�õĵ�λ���� */
    s32 ddr_autoref_t[DDR_AUTOREF_RANK_NUM];
    s32 ddr_autoref_t2[DDR_AUTOREF_RANK_NUM];
    u32 ddr_autoref_cfg[DDR_AUTOREF_RANK_NUM];
}DDR_AUTOREF_NV_STRU;


/* NV_ID_DRV_TSENS_TABLE = 0xd129*/
typedef struct
{
    s16 temp[256];

}DRV_TSENS_TEMP_TABLE;

typedef struct
{
    u8 ucABBSwitch; /*��Ӧģʽʹ�õ�ABB����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    u8 ucRFSwitch;  /*��Ӧģʽʹ�õ�RF����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    u8 ucTCXOSwitch; /*��Ӧģʽʹ�õ�TCXO ID 0 TCXO0, 1: TCXO1*/
    u8 reserve;
}NV_TLMODE_BASIC_PARA_STRU;

typedef struct
{
    NV_TLMODE_BASIC_PARA_STRU stModeBasicParam[2];/*�±�Ϊ0:LTE, 1:TDS*/
}NV_TLMODE_CHAN_PARA_STRU;

typedef struct
{
    u32 clkdis1; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis1*/
    u32 clkdis2; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis2*/
    u32 clkdis3; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis3*/
    u32 clkdis4;  /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis4*/
	u32 clkdis5;  /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis5*/
    u32 mtcmosdis; /*��ʼ�ر�MTCMOS�Ĵ�������Ӧcrg mtcmosdis*/
}DRV_NV_PM_CLKINIT_STRU;

typedef struct
{
    u32 ucBBPCh0TcxoSel:1; 	    /* bit 0,CH0 19.2Mʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x90000148 */
    u32 ucBBPCh1TcxoSel:1;  	/* bit 1,CH1 19.2Mʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x90000148 */
    u32 ucABBCh0TcxoSel:1; 		/* bit 2,ABB Ch0 ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��ӦABB�Ĵ��� 0x94 */
    u32 ucABBCh1TcxoSel:1; 		/* bit 3,ABB Ch1 ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x94 */
	u32 ucBbpPllTcxoSel:1; 		/* bit 4,BBP PLL ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1;*/
	u32 ucG1bp104mTcxoSel:1; 	/* bit 5,G1BBP 104M ʹ�õ�ABBͨ����0��ͨ��0, 1: ͨ��1;*/
	u32 ucG2bp104mTcxoSel:1; 	/* bit 6,G1BBP 104M ʹ�õ�ABBͨ����0��ͨ��0, 1: ͨ��1;*/
	u32 reserve:25;             /* bit 7-31*/
}DRV_TCXO_SEL_PARA_STRU;

typedef struct
{
    u32 u32UsbDbg;   /* usbģ�������Ϣ���� */
}DRV_USB_DBG_STRU;

typedef struct
{
	u32 wdt_enable;
	u32 wdt_timeout;
	u32 wdt_keepalive_ctime;
	u32 wdt_suspend_timerout;
	u32 wdt_reserve;
}DRV_WDT_INIT_PARA_STRU;


/*�¶ȱ��������߼�ת����  NV_ID_DRV_TSENSOR_TRIM          = 0xd12f */
typedef struct
{
    u16 tsensor_trim[16];

}DRV_TSENSOR_TRIM_STRU;

/* axi monitor���ID���� */
typedef struct
{
    u32 reset_flag;     /* ��λ��־��ƥ�䵽��������Ƿ�λ */
    u32 opt_type;       /* ������ͣ�01:����10:д��11:��д������ֵ:����� */
    u32 port;           /* ��ض˿� */
    u32 master_id;      /* ���masterid */
    u32 start_addr;     /* �����ʼ��ַ */
    u32 end_addr;       /* ��ؽ�����ַ */
} AMON_CONFIG_T;

/* axi monitor����NV�� NV_ID_DRV_AMON = 0xd130 */
typedef struct
{
    u32         en_flag;            /* ʹ�ܱ�־��00:ȥʹ�ܣ�01:SOC��10:CPUFAST��11:SOC,CPUFAST */
    AMON_CONFIG_T   soc_config[8];      /* SOC���ã�8�����ID */
    AMON_CONFIG_T   cpufast_config[8];  /* CPUFAST���ã�8�����ID */
} DRV_AMON_CONFIG_STRU;


/* SOCP���迪����������NV�� = 0xd132 */
typedef struct
{
    u32         en_flag;            /* ʹ�ܱ�־��00:ȥʹ�ܣ�01:ʹ�� */
} DRV_SOCP_ON_DEMAND_STRU;

/* drx delay flag */
typedef struct
{
    u8         lpm3_flag;         /* 0x11 ����lpm3 */
    u8         lpm3_0;            /* 1��delay,�����ر�delay */
    u8         lpm3_1;
    u8         lpm3_2;
    u8         lpm3_3;
    u8         lpm3_4;
    u8         lpm3_5;
    u8         drv_flag;          /* 0x22 ����drv */
    u8         drv_0;             /* 1��delay,�����ر�delay */
    u8         drv_1;
    u8         drv_2;
    u8         drv_3;
    u8         drv_4;
    u8         drv_5;
    u8         msp_flag;          /* 0x33 ����msp */
    u8         msp_0;             /* 1��delay,�����ر�delay */
    u8         msp_1;
    u8         msp_2;
    u8         msp_3;
    u8         msp_4;
}DRV_DRX_DELAY_STRU;

/* C�˵�����λ���迪����������NV�� = 0xd134 */
typedef struct
{
    u32 is_feature_on:1;         /* bit0, ����C�˵�����λ�����Ƿ�� */
    u32 is_connected_ril:1;      /* bit1, �Ƿ��RIL�Խ� */
	u32 reserve:30;              /* bit 2-31*/
} DRV_CCORE_RESET_STRU;

/* NV ID = 0xd135 */
/* ���ڱ�ʾÿ·LDO��BUCK�Ƿ�� */
typedef struct
{
	u32 ldo1_switch     :1;         /* ��0bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	u32 ldo2_switch     :1;         /* ��1bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	u32 buckpa_switch   :1;         /* ��2bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	u32 buck1_switch    :1;         /* ��3bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	u32 buck2_switch    :1;         /* ��4bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	u32 reserved        :27;        /* ��5~31bit��Ԥ����Ĭ��ֵΪ0 */
}NV_PASTAR_SWITCH_STRU_BITS;

typedef struct
{
    union
    {
        u32 u32;
        NV_PASTAR_SWITCH_STRU_BITS bits;
    }cont;
}NV_PASTAR_SWITCH_STRU;
/* end NV ID = 0xd135 */


/* log2.0 2014-03-19 Begin:*/
typedef struct
{
    u32 ulSocpDelayWriteFlg;/* SOCP�ӳ�д�빦��������� */
    u32 ulGuSocpLevel;      /* GU SOCPĿ��BUFFER����ˮ�� */
    u32 ulLSocpLevel;       /* L SOCPĿ��BUFFER����ˮ�� */
    u32 ulTimeOutValue;     /* SOCPĿ��BUFFER�ĳ�ʱʱ�� */
}DRV_NV_SOCP_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/
typedef struct
{
    u32  enUartEnableCfg;
	u32  enUartlogEnableCfg;
	u32  AwakeTmer;
	u32  DoSleepTimer;
}DRV_DUAL_MODEM_STR;

typedef struct
{
	u32 enUart5IrqCfg;
	u32 dmInitCfg;
	u32 ex1_param;
	u32 ex2_param;
	u32 ex3_param;
	u32 ex4_param;
}DRV_DM_UART5_STR;

/* GPIO����LDO���� NV�� = 0xd137 */
typedef struct
{
    u32 gpio;      /* LDO��ӦGPIO��� */
    u32 used;      /* GPIO�Ƿ�ʹ�� */
} DRV_DRV_LDO_GPIO_CFG;

typedef struct
{
    DRV_DRV_LDO_GPIO_CFG ldo_gpio[LDO_GPIO_MAX];/*0Ϊfem��1Ϊ����rf*/
}DRV_DRV_LDO_GPIO_STRU;

/* RSE POWER GPIO���� NV�� = 0xd139 */
typedef struct
{
    u32 ulRsePowerOnIds;
    u32 ulFemCtrlInfo;
    u32 ulRfGpioBitMask;
    u32 ulRfGpioOutValue;
    u16 usFemMipiCmdAddr;
    u16 usFemMipiCmdData;
}RF_NV_RSE_CFG_STRU;

/*���߿��ز��µ�����NV*/
/*NVID = 0xd13b��0Ϊ��ʹ�ܸ����ԣ�1Ϊʹ��*/
typedef struct
{
	u32 is_enable;/*Range:[0,1]*/
}DRV_ANT_SW_UNPD_ENFLAG;

typedef struct
{
	u32 gpio_num;	/*GPIO���    */
	u32 is_used;	/*Range:[0,1]*//*�Ƿ�ʹ��*/
	u32 value;		/*����ֵ */
}DRV_ANT_GPIO_CFG;

/*nvID = 0xd13c*/
/*���ּ����鿪��+��modem��һ�����߿��ص����ã�ÿ�����8������zhaojunȷ��*/
/*0��ʾ���ּ�1�飬1��ʾ���ּ�2�飬2��ʾ��modem���߿���*/
typedef struct
{
	DRV_ANT_GPIO_CFG 	antn_switch[8];
}DRV_ANT_SW_UNPD_CFG;

typedef struct
{
	DRV_ANT_SW_UNPD_CFG all_switch[3];
}NV_DRV_ANT_SW_UNPD_CFG;
/*End ���߿��ز��µ�����NV*/

/*�����������߹���Դ�����Ƿ�ʹ��*/
typedef struct
{
	u32 en_flag;
}NV_DRV_FEM_SHARE_POWER;

/*rse mipi ���÷�ʽ*/
typedef struct
{
	u32 en_flag;
}DRV_ANT_SW_MIPI_ENFLAG;

typedef struct
{
    u32 is_invalid;/*��ǰmipiָ���Ƿ���Ҫ����*/
    u8  mipi_chn;  /*mipiͨ����*/
    u8  slave_id;  /*���߿��ص�slave id*/
    u8  reg_offset;/*���õļĴ���ƫ��*/
    u8  value;     /*���õ�ֵ*/
}DRV_ANT_SW_MIPI;

typedef struct
{
    DRV_ANT_SW_MIPI modem_switch[RSE_MIPI_SW_REG_NUM];     /*ÿ��modem���õ�mipiָ��������Ϊ8��*/
}DRV_ANT_SW_MIPI_CONFIG;

typedef struct
{
    DRV_ANT_SW_MIPI_CONFIG all_switch[RSE_MODEM_NUM];/*0��ӦΪmodem0��1��ӦΪmodem1*/
}DRV_DRV_ANT_SW_MIPI_CONFIG;

/*end rse mipi ���÷�ʽ*/
typedef struct
{
	u32 DialupEnableCFG;
	u32 DialupACShellCFG;
}DRV_DIALUP_HSUART_STRU;


/*
*nvid = 0xd13d
*for mmc support or not
*/
typedef struct
{
	u32 support;
}DRV_MMC_SUPPORT_STRU;

/* PA/RF����ʵ���Ƿ�ʹ�ÿ��أ�������EM_MODEM_CONSUMER_IDö���е�˳�򱣳�һ�� */
/*ͨ��ģ�鹩��� CONSUMER��idö��
typedef enum EM_MODEM_CONSUMER_ID_E
{
    MODEM_PA0,
    MODEM_RFIC0_ANALOG0,
    MODEM_RFIC0_ANALOG1,
    MODEM_FEM0,
    MODEM_PA_VBIAS0,
    MODEM_PA1,
    MODEM_RFIC1_ANALOG0,
    MODEM_RFIC1_ANALOG1,
    MODEM_FEM1,
    MODEM_PA_VBIAS1,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;
*/
typedef struct
{
	u32 pa0 				: 1;	//1: Ӳ����ʵ�ʹ�������; 0: Ӳ����ʵ�ʹ�������
	u32 rfic0_analog0 		: 1;
	u32 rfic0_analog1    	: 1;
	u32 fem0    			: 1;
	u32 pa_vbias0       	: 1;
	u32 pa1 				: 1;
	u32 rfic1_analog0 		: 1;
	u32 rfic1_analog1    	: 1;
	u32 fem1    			: 1;
	u32 pa_vbias1       	: 1;
    u32 gpa                 : 1;
	u32 reserved    : 21;
}PARF_SWITCH_BITS;

typedef struct
{
    union
    {
        u32 u32;
        PARF_SWITCH_BITS bits;
    }cont;
} NV_DRV_PARF_SWITCH_STRU;

/* NVID=0xd144 begin */
typedef struct
{
    u32 mdm_dump    :1;     /* modem_dump.bin */
    u32 mdm_sram    :1;     /* modem_sram.bin */
    u32 mdm_share   :1;     /* modem_share.bin */
    u32 mdm_ddr     :1;     /* modem_ddr.bin */
    u32 lphy_tcm    :1;     /* lphy_tcm.bin */
    u32 lpm3_tcm    :1;     /* lpm3_tcm.bin */
    u32 ap_etb      :1;     /* ap_etb.bin */
    u32 mdm_etb     :1;     /* modem_etb.bin */
    u32 reset_log   :1;     /*reset.log*/
    u32 cphy_tcm     :1;     /* cphy_tcm.bin */
    u32 reserved2   :22;
}DUMP_FILE_BITS;

typedef struct
{
    union
    {
        u32         file_value;
        DUMP_FILE_BITS  file_bits;
    } file_list;
    u32             file_cnt; /* ��¼�쳣�ļ����� */
}DUMP_FILE_CFG_STRU;

/*nvID = 0xd140*/
typedef struct
{
    u32 mipi_chn[2];/*pastar��Ӧ��mipiͨ����*/
}NV_PASTAR_MIPI_CHN_STRU;

/* pm om���� NV�� = 0xd145 */
typedef struct
{
	u32 mem_ctrl:1;       /* ����bitλ:ʹ���������͵�memory */
    u32 reserved:31;      /* ����bitλ:���� */
	u8  log_threshold[4]; /* acore/ccore/mcore����д�ļ��ķ�ֵ, ��ֵ��ʾ�ٷֱ� */
    u8  mod_sw[8];        /* ����ģ��log���ܿ��ƿ��� */
}DRV_PM_OM_CFG_STRU;
/* NVID=0xd13d end */

/* DSP PLL Ctrl = 0xd146 */
typedef struct
{
    u32 app_a9_en   :1;
    u32 mdm_a9_en   :1;
    u32 reserved    :30;
}NV_DSP_PLL_CTRL_STRU;

typedef struct
{
    u32 tuner_mipi_mask         :4; /* TUNER_MIPI_MASK�Ĵ������� */
    u32 mipi_primary_bank0_en   :1; /* MIPI��ʽ��Modem0���ز�bank0��Ч */
    u32 mipi_primary_bank1_en   :1; /* MIPI��ʽ��Modem0���ز�bank1��Ч */
    u32 mipi_primary_bank2_en   :1; /* MIPI��ʽ��Modem0���ز�bank2��Ч */
    u32 mipi_primary_bank3_en   :1; /* MIPI��ʽ��Modem0���ز�bank3��Ч */
    u32 mipi_secondary_bank0_en :1; /* MIPI��ʽ��Modem0���ز�bank0��Ч */
    u32 mipi_secondary_bank1_en :1; /* MIPI��ʽ��Modem0���ز�bank1��Ч */
    u32 mipi_secondary_bank2_en :1; /* MIPI��ʽ��Modem0���ز�bank2��Ч */
    u32 mipi_secondary_bank3_en :1; /* MIPI��ʽ��Modem0���ز�bank3��Ч */
    u32 mipi_modem1_bank0_en    :1; /* MIPI��ʽ��Modem1 bank0��Ч */
    u32 mipi_modem1_bank1_en    :1; /* MIPI��ʽ��Modem1 bank1��Ч */
    u32 mipi_modem1_bank2_en    :1; /* MIPI��ʽ��Modem1 bank2��Ч */
    u32 mipi_modem1_bank3_en    :1; /* MIPI��ʽ��Modem1 bank3��Ч */
    u32 gpio_primary_en         :1; /* GPIO��ʽ��Modem0���ز���Ч */
    u32 gpio_secondary_en       :1; /* GPIO��ʽ��Modem0���ز���Ч */
    u32 gpio_modem1_en          :1; /* GPIO��ʽ��Modem1��Ч */
    u32 reserved3               :13;
} mipi_ctrl_reg;
typedef struct
{
    u32 tuner_en;               /* TUNER_EN�Ĵ�������ֵ */
    u32 tuner_req_en;           /* TUNER_REG_EN�Ĵ�������ֵ */
    mipi_ctrl_reg reg;
}NV_CROSS_MIPI_CTRL;

typedef struct
{
    u32 mipi_buffer[12][96];    /* MIPI��ʽ��buffer���� */
    u32 gpio_buffer[3][8];      /* GPIO��ʽ��buffer���� */
}NV_CROSS_MIPI_MEM;


/*=================NEW CROSS MIPI=====================*/
typedef struct
{
    u32 tuner_mipi_mask         :4; /* TUNER_MIPI_MASK�Ĵ������� */
    u32 gpio_mask               :17; /* GPIO��ʽmask �Ĵ�������*/
    u32 reserved3               :11;
} tuner_ctrl_reg;
typedef struct
{
    u32 tuner_en;               /* TUNER_EN�Ĵ�������ֵ */
    u32 tuner_req_en;           /* TUNER_REG_EN�Ĵ�������ֵ */
    u32 gpio_cross_en;          /* GPIO���������Ƿ�ʹ��*/
    u32 tas_ind_en;             /* TAS IND ȡ������*/
    u32 mipi_tuner0_len;        /* MIPI ��ʽModem0���ز�ʵ��buffer����*/
    u32 mipi_tuner1_len;        /* MIPI ��ʽModem0���ز�ʵ��buffer����*/
    u32 mipi_tuner2_len;        /* MIPI ��ʽModem1ʵ��buffer����*/
    u32 gpio_tuner_len;         /* GPIO��ʽʵ��buffer����*/
    tuner_ctrl_reg reg;
}NV_CROSS_MIPI_GPIO_CTRL;

typedef struct
{
    u32 mipi_buffer[1024];     /* MIPI��ʽModem0���ز�buffer���� */
}NV_MIPI_TUNER0_MEM;

typedef struct
{
    u32 mipi_buffer[1024];     /* MIPI��ʽModem0���ز�buffer���� */
}NV_MIPI_TUNER1_MEM;

typedef struct
{
    u32 mipi_buffer[1536];     /* MIPI��ʽModem1buffer���� */
}NV_MIPI_TUNER2_MEM;

typedef struct
{
    u32 gpio_buffer[192];      /* GPIO��ʽ��buffer���� */
}NV_GPIO_TUNER_MEM;

/*=================end NEW CROSS MIPI======================*/

/* watchpoint = 0xd148 begin */
typedef struct
{
    u32 enable;     /* ʹ�ܱ�־��0��ȥʹ�ܣ�1��ʹ�ܣ� ����ñ�־Ϊȥʹ�ܣ����ý�ֱ�Ӻ��� */
    u32 type;       /* �������: 1������2��д��3����д */
    u32 start_addr; /* �����ʼ��ַ */
    u32 end_addr;   /* ��ؽ�����ַ */
}WATCHPOINT_CFG;

typedef struct
{
    WATCHPOINT_CFG  ap_cfg[4];  /* A�����ã����֧��4��watchpoint */
    WATCHPOINT_CFG  cp_cfg[4];  /* A�����ã����֧��4��watchpoint */
}DRV_WATCHPOINT_CFG_STRU;
/* watchpoint = 0xd148 end */

typedef struct
{
	u32 enable;        /*ʹ�ܱ�־, 0, ȥʹ��;  1, ʹ��*/
	u32 reset_enable;  /*��λʹ�ܱ�־, 0, ȥʹ��; 1, ʹ��*/
}DRV_PDLOCK_CFG_STRU;
/* pdlock = 0xd14a */


typedef struct
{
    u32 ulResumeMode;       /*��NV���ݳ��ִ���ʱ�Ĵ���ʽ,1:����ģʽ,2:�û�ģʽ*/
}NV_SELF_CTRL_STRU;

/* 0xD14C */
#define ABB_INIT_NV_NUM     (200)

typedef struct
{
    u16 addr;
    u8  value;
    u8  reserved;
}NV_ABB_INIT_STRU;

typedef struct
{
    NV_ABB_INIT_STRU cfg[ABB_INIT_NV_NUM];
}NV_ABB_INIT_CFG;

/* 0xD14d */
typedef struct
{
    u32 product         :2;
    u32 reset           :1;
    u32 save_bakup      :1;
    u32 save_image      :1;
    u32 save_ddr        :1;
    u32 resume_bakup    :1;  /*Range:[0,1]*/
    u32 resume_img      :1;  /*Range:[0,1]*/
    u32 reserved        :24;
}NV_DEBUG_CFG_STRU;

/* 0xD14d */
typedef struct
{
	u8  pll_mon_moudle;  /* ��Ҫ��ص�pllԴ:0,A9PLL; 1,DSPPLL; 2,USBPLL; 3,PERIPLL; 4,TCX0,�ɼĴ����Ų�˳����� */
	u8  pll_mon_mode;    /* ��Ҫ��ص�pll�쳣ģʽ: 0x00, ʲô�������; 0x01, ֹͣģʽ; 0x10, ������׼ģʽ; 0x11ͬʱ��������쳣 */
	u16 pll_mon_cnt_min; /* clk_monitorģ��ʱ�Ӽ�����Сֵ���üĴ��� */
	u16 pll_mon_cnt_max; /* clk_monitorģ��ʱ�Ӽ������ֵ���üĴ��� */
	u8  pll_stop_timeout;/* ��λ125ms */
	u8  reserved;
}DRV_NV_CLK_MONITOR_CFG_STRU;
/* 0xD14F, for tsensor */
typedef struct
{
    s32 high_temp;
    s32 low_temp;
}DRV_TSENSOR_TEMP_THRESHOLD;

/* DSPDVS = 0xd150*/
typedef struct
{
    u32 enable;         /*ʹ�ܱ�־, 0, ȥʹ��;  1, ʹ��*/ 
}DRV_DSPDVFS_CFG_STRU;

/******************************************************************************************

                 ����Ϊ��Ƶnv,18000��ʼ������nv��Ҫ��������

*******************************************************************************************/

/*****************************************************************************
 �ṹ��       : FEMIO_PIN_CFG_STRU
 �ṹ˵��  : ��Ƶ�ܽ�bitλö�٣�����Ƶ�߿����nvʹ��
*****************************************************************************/
typedef struct
{
	u32 pin_00    : 1; /*1 is select, 0 is not select*/
	u32 pin_01    : 1; /*1 is select, 0 is not select*/
	u32 pin_02    : 1; /*1 is select, 0 is not select*/
	u32 pin_03    : 1; /*1 is select, 0 is not select*/
	u32 pin_04    : 1; /*1 is select, 0 is not select*/
	u32 pin_05	  : 1; /*1 is select, 0 is not select*/
	u32 pin_06 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_07    : 1; /*1 is select, 0 is not select*/
	u32 pin_08    : 1; /*1 is select, 0 is not select*/
	u32 pin_09    : 1; /*1 is select, 0 is not select*/
	u32 pin_10    : 1; /*1 is select, 0 is not select*/
	u32 pin_11    : 1; /*1 is select, 0 is not select*/
	u32 pin_12    : 1; /*1 is select, 0 is not select*/
	u32 pin_13    : 1; /*1 is select, 0 is not select*/
	u32 pin_14    : 1; /*1 is select, 0 is not select*/
	u32 pin_15	  : 1; /*1 is select, 0 is not select*/
	u32 pin_16 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_17    : 1; /*1 is select, 0 is not select*/
	u32 pin_18    : 1; /*1 is select, 0 is not select*/
	u32 pin_19    : 1; /*1 is select, 0 is not select*/
	u32 pin_20    : 1; /*1 is select, 0 is not select*/
	u32 pin_21    : 1; /*1 is select, 0 is not select*/
	u32 pin_22    : 1; /*1 is select, 0 is not select*/
	u32 pin_23    : 1; /*1 is select, 0 is not select*/
	u32 pin_24    : 1; /*1 is select, 0 is not select*/
	u32 pin_25	  : 1; /*1 is select, 0 is not select*/
	u32 pin_26 	  : 1; /*1 is select, 0 is not select*/
	u32 pin_27    : 1; /*1 is select, 0 is not select*/
	u32 pin_28    : 1; /*1 is select, 0 is not select*/
	u32 pin_29    : 1; /*1 is select, 0 is not select*/
	u32 pin_30    : 1; /*1 is select, 0 is not select*/
	u32 pin_31    : 1; /*1 is select, 0 is not select*/
}FEMIO_PIN_CFG_STRU;

/*****************************************************************************
 �ṹ��    	: RF_NV_MIPI_CMD_STRU
 �ṹ˵��  	: MIPI ָ����ƶζ��壬��żУ����������
*****************************************************************************/
typedef struct
{
    u16              SlaveAddr    :4;   /* Mipi Slave��ַ����Чֵ0-15 */
    u16              RegAddr      :9;   /* �Ĵ�����ַ OR ��ʼ��ַ */
    u16              ByteCnt      :3;   /*Range:[0,4]*//* ��Ҫд���byte���� */
}RF_NV_MIPI_CMD_STRU;

/*****************************************************************************
 �ṹ��    : RF_NV_MIPI_BYTE_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIPI ָ�����ݶζ��壬��żУ����������
*****************************************************************************/
typedef struct
{
    u16              ByteData     :8;   /* ָ�����ݶζ��壬��żУ���������� */
    u16              MasterSel    :3;   /* Mipi Masterָʾ */
    u16              Reserved     :5;   /* ���� */
}RF_NV_MIPI_BYTE_DATA_STRU;

/*****************************************************************************
 �ṹ��       : RFFE_PIN_ALL_CFG
 �ṹ˵��  : ��Ƶ�ܽ����ýṹ�嶨��
*****************************************************************************/
#define  NV_BALONG_MODEM_NUM 3/*Balong modem����˵��*/
typedef struct
{
    u32 mask;              /*��Ƶ�ܽ�����,0��ʾ��bitλ����Ҫ����*/
    u32 level;             /*��Ƶ�ܽ������ƽ ֵ,0��ʾ�õ͵�ƽ��1��ʾ�ߵ�ƽ*/

}RFFE_GPIO_VALUE_STRU;

typedef struct{
    u32 mask;              /*��Ƶ�ܽ�����,0��ʾ��bitλ����Ҫ����*/
    u32 mux;               /*��Ƶ�ܽŸ���,1��ʾ�߿أ�0��ʾGPIO*/
    u32 level;             /*��Ƶ�ܽ������ƽ ֵ,0��ʾ�õ͵�ƽ��1��ʾ�ߵ�ƽ*/
}RFFE_PIN_STRU;

typedef struct{
	u32           valid;/*Ĭ�Ϲر�*/
	RFFE_PIN_STRU modem_pwron [NV_BALONG_MODEM_NUM]; /*modem��������*/
	RFFE_PIN_STRU modem_pwroff[NV_BALONG_MODEM_NUM]; /*modem�ػ�����*/
	RFFE_PIN_STRU allmodem_pwroff; /*˫modem�ػ�����*/
}RFFE_PIN_ALL_CFG;

/*****************************************************************************
 �ṹ��       :  NV_FEM_GPIO_MIPI_CTRL_STRU
 �ṹ˵��  :  ��Ƶͨ��io�ӿڽṹ�嶨��
 NV ID               : 18002
*****************************************************************************/
#define FEM_MIPI_CMD_MAX  4  /*mipiָ��������*/
#define FEM_IO_CFG_MAX    16 /*18002 nv�����֧�ֵ����ø���*/
#define FEM_PIN_MAX       32 /*��Ƶ�ܽŸ���*/
#define GPIO_NUM_INVAILId 0xffff

typedef enum{
	FEMIO_CTRL_TOP = 0,/*��������*/
	GPIO_ONLY = 1,     /*ֻ����GPIO*/
	MIPI_ONLY = 2,     /*ֻ����MIPI*/
	GPIO_MIPI = 3,     /*����GPIO��MIPI*/
	FEMIO_CTRL_BUTT
}FEMIO_CTRL_MODE;

typedef struct
{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[4];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[5];
}FEMIO_MIPI_CTRL_STRU;

typedef struct
{
	FEMIO_CTRL_MODE       mode;     /*����ģʽ*/
	RFFE_GPIO_VALUE_STRU  gpio_ctrl;/*GPIO ����  */
	FEMIO_MIPI_CTRL_STRU  mipi_ctrl;/*MIPI  ����  */
}FEM_GPIO_MIPI_CTRL_STRU;

typedef struct
{
	FEM_GPIO_MIPI_CTRL_STRU cfg[FEM_IO_CFG_MAX];
}NV_FEM_GPIO_MIPI_CTRL_STRU;

/*****************************************************************************
 �ṹ��       :  NV_FEMPIN_TO_GPIO_STRU
 �ṹ˵��  :  ��Ƶ�ܽű�ź�gpio��Ŷ�Ӧ��ϵnv����
 NV ID               : 18003
*****************************************************************************/
typedef struct{
	u32 cfg[FEM_PIN_MAX];
}NV_FEMPIN_TO_GPIO_STRU;

/*****************************************************************************
 �ṹ��       :  RF_ANTEN_DETECT_GPIO_STRU
 �ṹ˵��  :  ���߲��nv����
 NV ID               :
*****************************************************************************/
#define RF_ANTEN_NUM 2
#define ANT_DETECT_STUB_GPIO 0XFFFF

typedef struct
{
    u32 anten[RF_ANTEN_NUM];  /* ANTEN��ӦGPIO��� */
	u32 div_anten;
} RF_ANTEN_DETECT_GPIO_STRU;

/*****************************************************************************
 �ṹ��		: RF_ANT_SHARE_STRU
 �ṹ˵��	: �������ߡ���������˵��
NV ID			:
*****************************************************************************/
#define RF_SWITCH_INOUT_GPIO_NUM     16
typedef struct
{
	u8 rf_pin    :7;
	u8 gpio_level:1;  /*Range:[0,1]*/
}RF_ANT_SHARE_GPIO_CFG;

typedef struct
{
    u32                     num;	/*��Ч����*/
    RF_ANT_SHARE_GPIO_CFG   gpio[16];   /*gpio����*/
}RF_ANT_SHARE_CFG;

typedef struct
{
    RF_ANT_SHARE_CFG inside;
    RF_ANT_SHARE_CFG outside;
}RF_ANT_SHARE_STRU;


#define CHANNEL_NUM 3

/*****************************************************************************
 �ṹ��     : RF_NV_MIPI_ALL_CFG
 �ṹ˵��   : ��������Ƶ�ܽ�mipi���ƽӿ�ʹ�õ�nv
 NVID       :
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : RF_NV_MIPI_INIT_COMM_STRU
 Э����  :
 �ṹ˵��  : ����mipi���ܹ���ָ���
*****************************************************************************/
typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[4];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[5];
}RF_NV_MIPI_04CMD;

typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[8];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[9];
}RF_NV_MIPI_08CMD;

typedef struct{
    u16                          CmdValidCnt;
    RF_NV_MIPI_CMD_STRU          MipiCmd[16];
    RF_NV_MIPI_BYTE_DATA_STRU    MipiData[17];
}RF_NV_MIPI_16CMD;

typedef struct
{
    RF_NV_MIPI_08CMD pa;
    RF_NV_MIPI_08CMD rfswitch;
    RF_NV_MIPI_08CMD tunner;
    RF_NV_MIPI_16CMD usrid;
    RF_NV_MIPI_16CMD reserved;
}RF_NV_MIPI_INIT_COMM_STRU;

typedef RF_NV_MIPI_16CMD RF_NV_MIPI_MDM_PWROFF_COMM_STRU;

typedef RF_NV_MIPI_16CMD RF_NV_MIPI_ALL_MDM_PWROFF_COMM_STRU;

typedef RF_NV_MIPI_08CMD RF_NV_MIPI_MDM_PWRON_COMM_STRU;

typedef RF_NV_MIPI_08CMD RF_NV_MIPI_MDM_DPM_COMM_STRU;

typedef struct
{
    RF_NV_MIPI_INIT_COMM_STRU            init;
    RF_NV_MIPI_MDM_PWRON_COMM_STRU       pwron [CHANNEL_NUM];/*todo:����Ƶȷ�ϱ��*/
    RF_NV_MIPI_MDM_PWROFF_COMM_STRU      pwroff[CHANNEL_NUM];
    RF_NV_MIPI_ALL_MDM_PWROFF_COMM_STRU  all_pwroff;

}RF_NV_MIPI_ALL_CFG;

/*18000*/
typedef struct
{
    u16 gpio_and_or_en; /*Range:[0,1]*/
    u16 abb_tx_index;   /*Range:[0,1,2,3]*/
}RF_NV_GSM_GPIO_ABBTX_FUNC_SEL;
/*end 18000*/

/*18020*/
typedef struct
{
    u32 abb0_tx_reg;
    u32 abb1_tx_reg;
}RF_NV_ABB_TX_STRU;

typedef struct
{

    u32 gpio_and_or_cfg;
    u32 reserved;
    RF_NV_ABB_TX_STRU  abb_tx_cfg[4];
}RF_NV_GSM_GPIO_ABBTX_CFG;
/*end 18020*/

/*18022\18023*/
typedef struct
{
    u32 enable:1;
    u32 gpio_num:16; /*gpio ���*/
    u32 function:1;  /*�ܽŹ���, 0Ϊgpio,1Ϊ�߿�*/
    u32 level:1;     /*�ܽŵ�ƽ, 0Ϊ�ߵ�ƽ,1Ϊ�͵�ƽ*/
  u32 reserved:13; /*����*/
}RF_GPIO_CONFIG_STRU;

typedef struct
{
    RF_GPIO_CONFIG_STRU profile[32];
}RF_GPIO_COMM_STRU;

typedef struct
{
    RF_NV_MIPI_04CMD profile[32];
}RF_MIPI_COMM_STRU;

typedef enum
{
    OUTER_MODEM_SPDT_SUSPEND = 0,

    RF_GPIO_COMM_MAX
}RF_GPIO_COMM_ENUM;

typedef enum
{
    OUTER_MODEM_TUNER_SUSPEND = 0,
    OUTER_MODEM_TUNER_RESUME = 1,

    RF_MIPI_COMM_MAX
}RF_MIPI_COMM_ENUM;

/*end 18022\ 18023*/
/**********************************END RF NV ***********************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

