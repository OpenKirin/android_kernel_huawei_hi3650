

#ifndef __ATPHYINTERFACE_H__
#define __ATPHYINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define W_AFC_INIT_VALUE                (0x959)           /* W_AFC״̬��ֵ */

#define WDSP_CTRL_TX_OFF                 2       /*��ʾDSPǿ������RF�ر�*/
#define WDSP_CTRL_TX_ON                  3       /*��ʾDSPǿ������RF��*/

#define WDSP_CTRL_TX_ONE_TONE            8       /* ��ʾ��ͬ�൥���ź� */
#define WDSP_CTRL_TX_TWO_TONE            9       /* ��ʾ�򿪷��൥���ź� */

#define GDSP_CTRL_TX_OFF                0xAAAA   /*��ʾDSPǿ������RF�ر�*/
#define GDSP_CTRL_TX_ON                 0x5555   /*��ʾDSPǿ������RF��*/

#define WDSP_MAX_TX_AGC                 2047
#define GDSP_MAX_TX_VPA                 1023

#define BBP_PA_HIGH_MODE                1       /*PA������ģʽ*/
#define BBP_PA_MID_MODE                 2       /*PA������ģʽ*/
#define BBP_PA_LOW_MODE                 3       /*PA������ģʽ*/
#define BBP_PA_AUTO_MODE                0       /*PA�Զ�����ģʽ*/

#define DSP_CTRL_RX_OFF                2       /*CPU���ƹر���ƵоƬ��*/
#define DSP_CTRL_RX_ANT1_ON            3       /*CPU���ƴ���ƵоƬ,����1��*/
#define DSP_CTRL_RX_ALL_ANT_ON         7       /*CPU���ƴ���ƵоƬ,����1��2 */

#define DSP_LNA_HIGH_GAIN_MODE          (0x2)     /* DSP�̶�LNAΪ������ģʽ */
#define DSP_LNA_LOW_GAIN_MODE           (0x1)     /* DSP�̶�LNAΪ������ģʽ */
#define DSP_LNA_NO_CTRL_GAIN_MODE       (0x0)     /* WBBP����LNAģʽ,�Զ�ģʽ */

#define AT_GDSP_AGC_GAIN1_75DB          (0)      /*GDSP AGC����,0��*/
#define AT_GDSP_AGC_GAIN2_63DB          (1)      /*GDSP AGC����,1��*/
#define AT_GDSP_AGC_GAIN3_43DB          (2)      /*GDSP AGC����,2��*/
#define AT_GDSP_AGC_GAIN4_23DB          (3)      /*GDSP AGC����,3��*/


#define AT_GDSP_RX_MODE_BURST           (0)      /*����*/
#define AT_GDSP_RX_MODE_CONTINOUS_BURST (1)      /*��������*/
#define AT_GDSP_RX_MODE_STOP            (2)      /*ֹͣ*/


#define AT_GDSP_RX_SLOW_AGC_MODE        (0)      /*Slow AGC*/
#define AT_GDSP_RX_FAST_AGC_MODE        (1)      /*fast AGC*/

#define AT_DSP_RF_AGC_STATE_ERROR       (-1)     /*ȡ�ò���ֵʱ������״̬��-1��ʾ���� */

#define AT_DSP_RSSI_MEASURE_NUM         (1)      /*RSSI�Ĳ�������*/
#define AT_DSP_RSSI_MEASURE_INTERVAL    (0)      /*RSSI�Ĳ������ʱ�䣬��λms */
#define AT_DSP_RSSI_VALUE_UINT          (0.125)  /*RSSI����ֵ����λ0.125dBm*/
#define AT_DSP_RSSI_VALUE_MUL_THOUSAND  (125)    /*RSSI����ֵ,��λ0.125dBm*1000*/

/*tyg*/
#define AT_DPS_NOISERSSI_MAX_NUM        (32)

#define AT_RX_PRI_ON                    (0)      /*��������*/
#define AT_RX_DIV_ON                    (1)      /*�����ּ�*/
#define AT_RXON_OPEN                    (0)      /*���һ��ִ�е��Ǵ򿪽��ջ�RXON=1����*/
#define AT_TXON_OPEN                    (1)      /*���һ��ִ�е��Ǵ򿪷����TXON=1����*/

#define AT_BIT0                            0x00000001L
#define AT_BIT1                            0x00000002L
#define AT_BIT2                            0x00000004L
#define AT_BIT3                            0x00000008L
#define AT_BIT4                            0x00000010L
#define AT_BIT5                            0x00000020L
#define AT_BIT6                            0x00000040L
#define AT_BIT7                            0x00000080L
#define AT_BIT8                            0x00000100L
#define AT_BIT9                            0x00000200L
#define AT_BIT10                           0x00000400L
#define AT_BIT11                           0x00000800L
#define AT_BIT12                           0x00001000L
#define AT_BIT13                           0x00002000L
#define AT_BIT14                           0x00004000L
#define AT_BIT15                           0x00008000L

/* W_RF_CFG_REQ��������� */
#define W_RF_MASK_AFC                   AT_BIT0
#define W_RF_MASK_TX_ARFCN              AT_BIT1
#define W_RF_MASK_TX_TXONOFF            AT_BIT2
#define W_RF_MASK_TX_PAMODE             AT_BIT3
#define W_RF_MASK_TX_AGC                AT_BIT4
#define W_RF_MASK_TX_POWER              AT_BIT5
#define W_RF_MASK_RX_RXONOFF            AT_BIT6
#define W_RF_MASK_RX_ARFCN              AT_BIT7
#define W_RF_MASK_RX_ANTSEL             AT_BIT8
#define W_RF_MASK_RX_LNAMODE            AT_BIT9
#define W_RF_MASK_RX_PGC                AT_BIT10
#define W_RF_MASK_TX_POWDET             AT_BIT11

/* G_RF_RX_CFG_REQ_STRU�ṹ��uhwMask�ı���λ���� */
#define G_RF_MASK_RX_ARFCN              AT_BIT0            /* �·�Ƶ�� */
#define G_RF_MASK_RX_MODE               AT_BIT1            /* �·�����ģʽ */
#define G_RF_MASK_RX_AGCMODE            AT_BIT2            /* �·�����ģʽ */
#define G_RF_MASK_RX_AGCGAIN            AT_BIT3            /* �·�AGC��λ */

/* G_RF_TX_CFG_REQ_STRU�ṹ��uhwMask�ı���λ���� */
/* ע��: 1)��GMSK���Ʒ�ʽ�£�Ŀ�귢�书�ʿ�ͨ��G_RF_MASK_TX_GSMK_PA_VOLT
           ��G_RF_MASK_TX_POWER�·�,������ͬʱ�·�;
         2)��8PSK���Ʒ�ʽ��:Ŀ�깦��ֵֻ��ͨ��G_RF_MASK_TX_POWER�·�
         3)������λ����ͬʱ�·����������໥��ͻ */
#define G_RF_MASK_TX_AFC                AT_BIT0            /* �·�����Ƶ�ʿ���ֵ */
#define G_RF_MASK_TX_ARFCN              AT_BIT1            /* �·�����Ƶ�� */
#define G_RF_MASK_TX_TXEN               AT_BIT2            /* �·��������λ */
#define G_RF_MASK_TX_TXMODE             AT_BIT3            /* �·�����ģʽ */
#define G_RF_MASK_TX_MOD_TYPE           AT_BIT4            /* �·�����ģʽ */
#define G_RF_MASK_TX_GSMK_PA_VOLT       AT_BIT5            /* �·�GMSK����ʱ PAĿ����Ƶ�ѹ */
#define G_RF_MASK_TX_POWER              AT_BIT6            /* �·�Ŀ�귢�����ֵ,GMSK��8PSK���� */
#define G_RF_MASK_TX_8PSK_PA_VBIAS      AT_BIT7            /* �·�8PSK����ʱPAƫ�õ�ѹ */
#define G_RF_MASK_TX_TXOLC              AT_BIT8            /* �·�TXOLC�Ĵ���ֵ */
#define G_RF_MASK_TX_DATA_PATTERN       AT_BIT9

/*���Ʒ�ʽ*/
#define G_MOD_TYPE_GMSK                 0       /* GMSK���Ʒ�ʽ */
#define G_MOD_TYPE_8PSK                 1       /* 8PSK���Ʒ�ʽ */

/* noise tool ����ϱ��Ľ������ */
#define PHY_NOISE_MAX_RESULT_NUMB       32

/* ��������·������й���Ϊ0xff��Ϊ�������� */
#define PHY_NOIST_TOOL_CLOSE_TX         0xff

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* �����ߵ�ģʽ */
enum AT_ANT_MODE_ENUM
{
    ANT_ONE  = 1,/*ֻ����������*/
    ANT_TWO  = 2,/*ͬʱ�������ͷּ�����*/
    ANT_BUTT
};
typedef VOS_UINT8 AT_ANT_MODE_UINT8;

/* WDSP ��ʽƵ�ζ���*/
enum AT_W_BAND_ENUM
{
    W_FREQ_BAND1 = 1,
    W_FREQ_BAND2,
    W_FREQ_BAND3,
    W_FREQ_BAND4,
    W_FREQ_BAND5,
    W_FREQ_BAND6,
    W_FREQ_BAND7,
    W_FREQ_BAND8,
    W_FREQ_BAND9,
    W_FREQ_BAND10,                                                              /*  BAND10 ��֧�� */
    W_FREQ_BAND11,
    W_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_WDSP_BAND_ENUM_UINT16;

/* GDSP Ƶ�ζ��� */
enum AT_GDSP_BAND_ENUM
{
    G_FREQ_BAND_GSM850 = 0,
    G_FREQ_BAND_GSM900,
    G_FREQ_BAND_DCS1800,
    G_FREQ_BAND_PCS1900,
    G_FREQ_BAND_BUTT
};
typedef VOS_UINT16 AT_GDSP_BAND_ENUM_UINT16;

/* AT HPA���ý�� 0:success, 1:fail */
enum AT_HPA_CFG_RLST_ENUM
{
    AT_HPA_RSLT_SUCC = 0,
    AT_HPA_RSLT_FAIL,
    AT_HPA_RSLT_BUTT
};
typedef VOS_UINT16 AT_HPA_CFG_RLST_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*#define ID_HPA_AT_TRANS_MSG_ID          0x8001            ͸����ϢID */

        /* W����У׼ԭ��ID*/
#define ID_AT_HPA_RF_CFG_REQ            0x2621
#define ID_HPA_AT_RF_CFG_CNF            0x62E0

#define ID_AT_HPA_RF_RX_RSSI_REQ        0x2622
#define ID_HPA_AT_RF_RX_RSSI_IND        0x62E1

        /* W PLL����״̬��ѯԭ��ID*/
#define ID_AT_WPHY_RF_PLL_STATUS_REQ    0x2623
#define ID_AT_WPHY_RF_PLL_STATUS_CNF    0x62E2

        /* G����У׼ԭ��ID*/
#define ID_AT_GHPA_RF_RX_CFG_REQ        0x2415          /*RX����У׼��������*/
#define ID_AT_GHPA_RF_TX_CFG_REQ        0x2418          /*TX����У׼��������*/
#define ID_GHPA_AT_RF_MSG_CNF           0x4212          /* ͨ�ûظ���Ϣԭ�� */

#define ID_AT_GHPA_RF_RX_RSSI_REQ       0x2416          /*RX����У׼��������*/
#define ID_GHPA_AT_RF_RX_RSSI_IND       0x4210          /*RX����У׼��������ϱ�*/

        /* G PLL����״̬��ѯԭ��ID*/
#define ID_AT_GPHY_RF_PLL_STATUS_REQ    0x2419
#define ID_AT_GPHY_RF_PLL_STATUS_CNF    0x4219

        /* PD���״̬��ѯԭ��ID*/
#define ID_AT_WPHY_POWER_DET_REQ        0x2624
#define ID_AT_WPHY_POWER_DET_CNF        0x62e3

/* noise tool ��wphy�Ľӿ� */
#define ID_AT_HPA_RF_NOISE_CFG_REQ      0x2625
#define ID_HPA_AT_RF_NOISE_RSSI_IND     0x62e4
/**/
/* �ظ���NOISE TOOL����Ϣԭ�� ԭ��ID */
#define ID_AT_GHPA_RF_NOISE_CFG_REQ     0x241A
#define ID_GHPA_AT_RF_NOISE_RSSI_IND    0x421A

#define ID_AT_HPA_MIPI_WR_REQ           0x2490
#define ID_HPA_AT_MIPI_WR_CNF           0x4290
#define ID_AT_HPA_MIPI_RD_REQ           0x2491
#define ID_HPA_AT_MIPI_RD_CNF           0x4291

#define ID_AT_HPA_SSI_WR_REQ            0x2492
#define ID_HPA_AT_SSI_WR_CNF            0x4292
#define ID_AT_HPA_SSI_RD_REQ            0x2493
#define ID_HPA_AT_SSI_RD_CNF            0x4293

#define ID_AT_HPA_PDM_CTRL_REQ          0x2494
#define ID_HPA_AT_PDM_CTRL_CNF          0x4294

        /* CDMA����У׼ԭ��ID*/
#define ID_AT_CHPA_RF_CFG_REQ            0x6300
#define ID_CHPA_AT_RF_CFG_CNF            0x6301

#define ID_AT_CHPA_RF_RX_RSSI_REQ        0x6302
#define ID_CHPA_AT_RF_RX_RSSI_IND        0x6303

/*****************************************************************************
 �ṹ��    : C_RF_CFG_PARA_STRU
 �ṹ˵��  : RF���ò����ṹ
 1.��    ��   : 2011��11��16��
   ��    ��   : f62575
   �޸�����   : ����ṹע��
*****************************************************************************/
typedef struct
{
    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /* ��λ��ʶ�������� */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,Э���е�band���,ע�ⲻ��BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TXͨ��ʹ�ܿ��� */
    VOS_UINT16                          usTxPAMode;                             /* PAģʽ���� */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RXͨ��ʹ�ܿ��� */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,Э���е�band���*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRsv;             /* ����λ */

}C_RF_CFG_PARA_STRU;

/* AT_HPA ��������ԭ��ӿ� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
    C_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF���ò����ṹ */
}AT_CHPA_RF_CFG_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
    VOS_UINT16                          usMeasNum;             /* RSSI�Ĳ������� */
    VOS_UINT16                          usInterval;            /* RSSI�Ĳ������ʱ�䣬��λms */
}AT_CHPA_RF_RX_RSSI_REQ_STRU;



/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* W��RF���ýṹ */
/* RF���ò����ṹ */
/*****************************************************************************
 �ṹ��    : W_RF_CFG_PARA_STRU
 �ṹ˵��  : RF���ò����ṹ
 1.��    ��   : 2011��11��16��
   ��    ��   : f62575
   �޸�����   : ����ṹע��
 2.��    ��   : 2011��11��16��
   ��    ��   : f62575
   �޸�����   : ���������ӿڱ��
                ����sRrcWidth, sDbbAtten, usRxCarrMode, usPaVbias
                �ƶ�sTxPower,
                ɾ��sRxPGC
*****************************************************************************/
typedef struct
{
    /* TX RX��ʹ�� */
    VOS_INT16                           sRrcWidth;                              /* �ñ�����ʱ����,˫�ز�ģʽʱ,��ֵΪRRC����,��Χ[-5,5]MHz */

    /* Tx Cfg */
    VOS_UINT16                          usMask;                                 /* ��λ��ʶ�������� */
    VOS_UINT16                          usTxAFCInit;                            /* AFC */
    VOS_UINT16                          usTxBand;                               /* 1,2,3...,Э���е�band���,ע�ⲻ��BandId */
    VOS_UINT16                          usTxFreqNum;                            /* Arfcn */
    VOS_UINT16                          usTxEnable;                             /* TXͨ��ʹ�ܿ��� */
    VOS_UINT16                          usTxPAMode;                             /* PAģʽ���� */
    VOS_INT16                           sTxPower;                               /* 0.1dBm */
    VOS_INT16                           sDbbAtten;                              /* DBB���ź�˥���Ŀ����� ӳ�䵽usTxAGC???�������岻һ�£�������ȷ�� */
    VOS_UINT16                          usRfAtten;                              /* RF���ź�˥���Ŀ����� */
    VOS_UINT16                          usTxAGC;                                /* ����AGC���� */
    VOS_UINT16                          usPaVbias;                              /* W PA Vbias �Ŀ����� */

    /* Rx Cfg */
    VOS_UINT16                          usRxEnable;                             /* RXͨ��ʹ�ܿ��� */
    VOS_UINT16                          usRxBand;                               /* 1,2,3...,Э���е�band���*/
    VOS_UINT16                          usRxFreqNum;                            /* Arfcn*/
    VOS_UINT16                          usRxAntSel;                             /* Ant1/Ant2*/
    VOS_UINT16                          usRxLNAGainMode;                        /* LNAģʽ���� */


    VOS_UINT16                          usRxCarrMode;                           /* 0:���ز�;1:˫�ز� */
}W_RF_CFG_PARA_STRU;


/* AT_HPA ��������ԭ��ӿ� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
    W_RF_CFG_PARA_STRU                  stRfCfgPara;            /* RF���ò����ṹ */
}AT_HPA_RF_CFG_REQ_STRU;

/* G��RF���ýṹ */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
    VOS_UINT16                          usMask;        /* Reference MASK_CAL_RF_G_RX_* section */
    VOS_UINT16                          usFreqNum;     /* (Band << 12) | Arfcn */
    VOS_UINT16                          usRxMode;      /* 0:burst����; 1:��������;, */
    VOS_UINT16                          usAGCMode;     /* Fast AGC,Slow AGC */
    VOS_UINT16                          usAgcGain;     /* AGC��λ�����ĵ�,ȡֵΪ0-3*/
    VOS_UINT16                          usRsv2;
}AT_GHPA_RF_RX_CFG_REQ_STRU;

/*****************************************************************************
 ö����    : AT_GHPA_RF_CTRLMODE_TYPE_ENUM
 �ṹ˵��  : ������Ʒ�ʽ��
             0��GMSK��ѹ����,�˷�ʽ��usTxVpaҪ���ã�
             1�����ʿ���,�˷�ʽ��usTxPowerҪ���ã�
             2��8PSK PaVbias��ѹ&DBB Atten&RF Atten���ƣ�usPAVbias��usRfAtten,sDbbAtten����������Ҫ���ã�
1.��    ��   : 2011��11��17��
  ��    ��   : f62575
  �޸�����   : ������
*****************************************************************************/
enum AT_GHPA_RF_CTRLMODE_TYPE_ENUM
{
    AT_GHPA_RF_CTRLMODE_TYPE_GMSK,
    AT_GHPA_RF_CTRLMODE_TYPE_TXPOWER,
    AT_GHPA_RF_CTRLMODE_TYPE_8PSK,
    AT_GHPA_RF_CTRLMODE_TYPE_BUTT
};
typedef VOS_UINT8 AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : AT_GHPA_RF_TX_CFG_REQ_STRU
 �ṹ˵��  :
 1.��    ��   : 2011��11��16��
   ��    ��   : f62575
   �޸�����   : ����ע��
 2.��    ��   : 2011��11��16��
   ��    ��   : f62575
   �޸�����   : ���������ӿڱ��
                ����enCtrlMode, uhwRfAtten
                �ƶ�usModType,
                ɾ��usTxolc
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /* ����λ */
    VOS_UINT16                          usMask;                                 /* Reference MASK_CAL_RF_G_TX_* section*/
    VOS_UINT16                          usAFC;                                  /* AFC */
    VOS_UINT16                          usModType;                              /* ������Ʒ�ʽ:0��ʾGMSK����;1��ʾ8PSK���Ʒ�ʽ */
    VOS_UINT16                          usFreqNum;                              /* (Band << 12) | Arfcn */
    VOS_UINT16                          usTxEnable;                             /* ����ʹ�ܿ���:0x5555-ʹ�ܷ���;0xAAAA-ֹͣ����;TSC 0; TxData: ����� */
    VOS_UINT16                          usTxMode;                               /* 0:burst����; 1:�������� */
    AT_GHPA_RF_CTRLMODE_TYPE_ENUM_UINT8 enCtrlMode;                             /* ������Ʒ�ʽ��
                                                                                    0��GMSK��ѹ����,�˷�ʽ��usTxVpaҪ���ã�
                                                                                    1�����ʿ���,�˷�ʽ��usTxPowerҪ���ã�
                                                                                    2��8PSK PaVbias��ѹ&DBB Atten&RF Atten���ƣ�
                                                                                    usPAVbias��usRfAtten,sDbbAtten����������Ҫ���ã�*/
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          uhwRfAtten;
    VOS_UINT16                          usTxPower;                              /* Ŀ�귢�书��,��λΪ0.1dBm,GSM��EDGE���� */
    VOS_UINT16                          usTxVpa;                                /* GSM PA���书�ʿ��Ƶ�ѹ,ȡֵ��Χ: */
    VOS_INT16                           shwDbbAtten;
    VOS_UINT16                          usPAVbias;                              /* EDGE PA Vbais ��ѹ */
}AT_GHPA_RF_TX_CFG_REQ_STRU;


/*Response Head Struct    W/Gͨ�� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usTransPrimID;     /* 0x8001 */
    VOS_UINT16                          usRsv1;            /* ����λ */
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
}HPA_AT_HEADER_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* ���յ�����ϢID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_RF_CFG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
    VOS_UINT16                          usMeasNum;             /* RSSI�Ĳ������� */
    VOS_UINT16                          usInterval;            /* RSSI�Ĳ������ʱ�䣬��λms */
}AT_HPA_RF_RX_RSSI_REQ_STRU;

/* ���յ����������ϱ�������ϱ�ǰһ�ν��յ�RSSI�������  G/Wͨ�� */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI����ֵ [-2048,+2047]����λ0.125dBm*/
    VOS_INT16                           sAGCGain;         /* ȡ�ò���ֵʱ������״̬��-1��ʾ���� */
}HPA_AT_RF_RX_RSSI_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_NOISE_RESULT_STRU
 �ṹ˵��  : PHY��AT�ϱ��ĵ�������Ľṹ
 1.��    ��   : 2014��12��29��
   ��    ��   : tianyige
   �޸�����   : Noise tool PHY�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLFreq;                               /*PHY�ϱ���ǰ����Ƶ��*/
    VOS_INT16                           sDLPriRssi;                             /*PHY�ϱ���Ӧ����RSSI*/
    VOS_INT16                           sDLDivRssi;                             /*PHY�ϱ���Ӧ�ּ�RSSI*/
    VOS_UINT16                          usRsv;
}PHY_NOISE_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : HPA_NOISE_RSSI_IND_STRU
 �ṹ˵��  : WPHY��GPHY��AT�ϱ�����Ϣ�ṹ
 1.��    ��   : 2014��12��29��
   ��    ��   : tianyige
   �޸�����   : Noise tool PHY�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDLRssiNum;                            /*PHY�ϱ�����RSSI����*/
    VOS_UINT16                          usMeaStatus;                            /*PHY�ϱ�����״̬��0��ʾ�ɹ���1��ʾ��������2��ʾ��ʱ */
    PHY_NOISE_RESULT_STRU               astDlRssiResult[AT_DPS_NOISERSSI_MAX_NUM];
}HPA_NOISE_RSSI_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHY_AT_RF_NOISE_RSSI_IND_STRU
 �ṹ˵��  : WPHY��GPHY��AT�ϱ�����Ϣ�ṹ
 1.��    ��   : 2014��12��29��
   ��    ��   : tianyige
   �޸�����   : Noise tool PHY�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;                            /* ��׼ͷ */
    HPA_NOISE_RSSI_IND_STRU             stRssiInd;                              /* ��� */
}PHY_AT_RF_NOISE_RSSI_IND_STRU;

/*****************************************************************************
 �ṹ��    : AT_PHY_RF_PLL_STATUS_REQ_STRU
 �ṹ˵��  : AT��WPHY��GPHY��ѯPLL״̬����Ϣ�ṹ
 1.��    ��   : 2013��11��29��
   ��    ��   : L00256032
   �޸�����   : Added for PLL status query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv1;            /* ����λ */
    VOS_UINT16                          usDspBand;         /* DSP��ʽ��Ƶ��ֵ */
    VOS_UINT16                          usRsv2;            /* ����λ */
}AT_PHY_RF_PLL_STATUS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_PHY_RF_PLL_STATUS_REQ_STRU
 �ṹ˵��  : WPHY��GPHY��AT����PLL״̬����Ϣ�ṹ
 1.��    ��   : 2013��11��29��
   ��    ��   : L00256032
   �޸�����   : Added for PLL status query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usTxStatus;        /* 0:PLLʧ��, 1:PLL���� */
    VOS_UINT16                          usRxStatus;        /* 0:PLLʧ��, 1:PLL���� */
}PHY_AT_RF_PLL_STATUS_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_PHY_POWER_DET_REQ_STRU
 �ṹ˵��  : AT��WPHY��ѯ���ʼ�����Ϣ�ṹ
 1.��    ��   : 2014��05��06��
   ��    ��   : c00242732
   �޸�����   : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;           /* Msg ID */
    VOS_UINT16                          usRsv;             /* ����λ */
}AT_PHY_POWER_DET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_AT_POWER_DET_CNF_STRU
 �ṹ˵��  : WPHY��AT���ع��ʼ��������Ϣ�ṹ
 1.��    ��   : 2014��05��06��
   ��    ��   : c00242732
   �޸�����   : Added for Power_Detect query
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sPowerDet;         /* ���ʼ������0.1dBm���� */
    VOS_UINT16                          usRsv;             /* ����λ */
}PHY_AT_POWER_DET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : AT_HPA_RF_NOISE_CFG_REQ_STRU
 �ṹ˵��  : AT��GPHY�·�noise tool����
 1.��    ��   : 2014��12��19��
   ��    ��   : tianyige
   �޸�����   : Added for noise tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usMode;                                 /* UE ģʽ */
    VOS_UINT16                          usBand;                                 /* band��Ϣ */
    VOS_UINT16                          usDlStartFreq;                          /* ���п�ʼƵ�� */
    VOS_UINT16                          usDlEndFreq;                            /* ���н���Ƶ�� */
    VOS_UINT16                          usFreqStep;                             /* ���� */
    VOS_INT16                           sTxPwr;                                 /* ���书�� */
    VOS_UINT16                          usRsv;                                  /* ����λ */
}AT_HPA_RF_NOISE_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : AT_HPA_MIPI_WR_REQ_STRU
 �ṹ˵��  : ����MIPI �Ĵ�������ṹ��

 1.��    ��   : 2015��9��10��
    ��    ��   : l00227485
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usSlaveAddr;
    VOS_UINT16                          usRegAddr;
    VOS_UINT16                          usRegData;
    VOS_UINT16                          usMipiChannel;
    VOS_UINT16                          usRsv;
}AT_HPA_MIPI_WR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : HPA_AT_MIPI_WR_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����MIPI �Ĵ�������ṹ��
1.��    ��   : 2015��9��10��
   ��    ��   :l00227485
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;          /* 0:success, 1:fail */
}HPA_AT_MIPI_WR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_HPA_MIPI_RD_REQ_STRU
 �ṹ˵��  :��ѯMIPI �Ĵ�������ṹ��
 1.��    ��   : 2015��9��10��
    ��    ��   : l00227485
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          uhwSlaveAddr;                           /* ���ն˵�ַ */
    VOS_UINT16                          uhwReg;                                 /* �Ĵ������� */
    VOS_UINT16                          uhwChannel;                             /* ��ʼ�ļĴ��� */
}AT_HPA_MIPI_RD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : HPA_AT_MIPI_RD_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����MIPI �Ĵ�������ṹ��
1.��    ��   : 2015��9��10��
   ��    ��   :l00227485
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_MIPI_RD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_HPA_SSI_WR_REQ_STRU
 �ṹ˵��  : AT��PHY�·�SSI����
 1.��    ��   : 2015��09��19��
   ��    ��   : x00316382
   �޸�����   : Added for ssi tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;
    VOS_UINT16                          usRficSsi;                              /* Mipi */
    VOS_UINT16                          usRegAddr;                              /* ��ʼ�ļĴ��� */
    VOS_UINT16                          usData;                                 /* ���� */
}AT_HPA_SSI_WR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : HPA_AT_SSI_WR_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����MIPI �Ĵ�������ṹ��
1.��    ��   : 2015��9��10��
   ��    ��   :l00227485
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          usErrFlg;                               /* 0:success, 1:fail */
}HPA_AT_SSI_WR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_HPA_SSI_RD_REQ_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��09��19��
   ��    ��   : x00316382
   �޸�����   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usChannelNo;                            /* ���ն˵�ַ */
    VOS_UINT32                          uwRficReg;
}AT_HPA_SSI_RD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : HPA_AT_SSI_RD_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����MIPI �Ĵ�������ṹ��
1.��    ��   : 2015��9��10��
   ��    ��   :l00227485
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulValue;
    VOS_UINT32                          ulResult;
}HPA_AT_SSI_RD_CNF_STRU;

/* ���յ����������ϱ�������ϱ�ǰһ�ν��յ�RSSI�������  G/Wͨ�� */
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_INT16                           sRSSI;            /* RSSI����ֵ [-2048,+2047]����λ0.125dBm*/
    VOS_INT16                           sAGCGain;         /* ȡ�ò���ֵʱ������״̬��-1��ʾ���� */
}CHPA_AT_RF_RX_RSSI_IND_STRU;

typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT16                          usCfgMsgID;        /* ���յ�����ϢID */
    VOS_UINT16                          usErrFlg;          /* 0:success, 1:fail */
}CHPA_AT_RF_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : AT_HPA_PDM_CTRL_REQ_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��10��20��
   ��    ��   : x00316382
   �޸�����   : Added for tool
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* Msg ID */
    VOS_UINT16                          usRsv;                                  /* ����λ */
    VOS_UINT16                          usPdmRegValue;
    VOS_UINT16                          usPaVbias;
    VOS_UINT16                          usPaVbias2;
    VOS_UINT16                          usPaVbias3;
}AT_HPA_PDM_CTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : HPA_AT_PDM_CTRL_CNF_STRU
 �ṹ˵��  : AT��AT AGENT ����PDM �Ĵ�������ṹ��
1.��    ��   : 2015��10��20��
  ��    ��   : x00316382
  �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    HPA_AT_HEADER_STRU                  stMsgHeader;
    VOS_UINT32                          ulResult;
}HPA_AT_PDM_CTRL_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of AtPhyInterface.h */
