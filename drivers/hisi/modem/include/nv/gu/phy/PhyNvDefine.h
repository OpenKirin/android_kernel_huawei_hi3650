/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : PhyNvDefine.h
  Description     : PhyNvDefine.h header file
  History         :

******************************************************************************/
#ifndef __PHYNVDEFINE_H__
#define __PHYNVDEFINE_H__


#ifndef MS_VC6_PLATFORM
#ifndef TENSILICA_PLATFORM
#include "vos.h"
#endif
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(1)


/*****************************************************************************
  2 �궨��
*****************************************************************************/


#define UCOM_NV_EDGE_TX_TEMP_COMP_NUM           ( 16 )
#define UCOM_NV_EDGE_TX_RF_GAIN_CTRL_NUM        ( 20 )
#define UCOM_NV_INTERFERENCE_TABLE_MAX_NUM      ( 8 )                           /* ���Ź����������*/
#define UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM  ( 3 )                           /* ����ҵ�����͸���*/


#define UCOM_NV_G_RAMP_PWR_LEVEL_NUM        ( 7 )                               /* ������10dBm,20dBm����Ϊ3�����¹������� */
#define UCOM_NV_G_TX_REF_CHAN_NUM_MAX       ( 32 )                              /* TXƵ�ʲ���У׼Ƶ�������� */


#define UCOM_NV_G_TX_8PSK_PWR_CONT_NUM      ( 30 )                              /* (����)8PSK��ҪУ���ķ��书�ʵ�Ϊ30�� */
#define UCOM_NV_G_TX_PWR_CONT_NUM           ( 60 )                              /* ��ҪУ���ķ��书�ʵ�Ϊ60�� */


#define UCOM_NV_G_TEMP_LEVEL_NUM            ( 16 )                              /* [�¶ȵ�λ,��5��:-20~0,0~20,20~40,40~60,60~85] */
#define UCOM_NV_G_AGC_LEVEL_MAX_NUM         ( 8 )
#define UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM    ( UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 )  /* UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 */
#define UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM   ( UCOM_NV_G_AGC_LEVEL_MAX_NUM - 1 ) /* ��Ƶ������λDCRУ׼��� */


#define UCOM_NV_G_CHAN_GAIN_MAX_NUM         ( 8 )                               /* �������浵������AGC��λ�ʶ�Ӧ��ϵ */

#define UCOM_NV_G_TX_POWER_LEVEL_NUM        ( 3 )                               /* �����书�ʻ���Ϊ3���ȼ� */
#define UCOM_NV_G_TX_CHAN_COMP_NUM          ( 32 )                              /* 8PSK TXƵ�ʲ����ο���������� */
#define UCOM_NV_G_PCL_NUM                   ( 32 )                              /* ���ʵȼ����� */
#define UCOM_NV_G_TX_SLOT_MAX_NUM           ( 4 )                               /* ���ʵȼ����� */

#define UCOM_NV_G_TX_ATTEN_NUM              ( 55 )                              /* 8PSK ˥������ */

#define UCOM_NV_G_RX_CHAN_COMP_NUM          ( 16 )                              /* ��Ƶ�βο���������� */
#define UCOM_NV_G_HIGH_BAND_CHAN_COMP_NUM   ( 16 )                              /* ��Ƶ�βο���������� */

#define UCOM_NV_G_RX_GSM850_GAIN0_DCR_NUM   ( 42 )
#define UCOM_NV_G_RX_GSM900_GAIN0_DCR_NUM   ( 65 )
#define UCOM_NV_G_RX_DCS1800_GAIN0_DCR_NUM  ( 125 )
#define UCOM_NV_G_RX_PCS1900_GAIN0_DCR_NUM  ( 100 )
#define UCOM_G_RX_GAIN0_DCR_MAX_NUM         ( 125 )

#if ( FEATURE_ON == FEATURE_VIRTUAL_BAND )
#define UCOM_NV_G_BAND_NUM                  ( 5 )                               /* GSM Narrow Dcs�����Ƶ�� */
#else
#define UCOM_NV_G_BAND_NUM                  ( 4 )                               /* GSM���ĸ�Ƶ�� */
#endif
#define UCOM_NV_G_BAND_NUMBER               ( 4 )                               /* GSM���ĸ�Ƶ�� */
#define UCOM_NV_G_HIGH_BAND_NUM             ( 2 )                               /* ��Ƶ�ΰ���1800/1900����Ƶ�� */
#define UCOM_NV_G_LOW_BAND_NUM              ( 2 )                               /* ��Ƶ�ΰ���850/900����Ƶ�� */
#define UCOM_NV_G_HIGH_BAND_INDEX           ( 0 )                               /* ��Ƶ�ΰ���1800/1900����Ƶ�� */
#define UCOM_NV_G_LOW_BAND_INDEX            ( 1 )                               /* ��Ƶ�ΰ���850/900����Ƶ�� */
#define UCOM_NV_G_HIGH_LOW_BUTT             ( 2 )                               /* Gģ���ָߵ�BAND */
#define UCOM_NV_G_SUBBAND_NUM               ( 3 )                               /* ÿƵ������Ƶ�θ��� */
#define UCOM_NV_G_RAMP_COEF_NUM             ( 16 )                              /* ���µ��� */
#define UCOM_NV_G_LNA_GPIO_STEP_NUM         ( 4 )                               /* LNA GPIO���������λ�� */
#define UCOM_NV_G_LNA_MIPI_STEP_NUM         ( 4 )                               /* LNA MIPI���������λ�� */
#define UCOM_NV_G_LNA_GAIN_INDEX_NUM        ( 8 )                               /* LNA MIPI���������λ�� */
#define UCOM_NV_G_LNA_MIPI_CMD_MAX_NUM      ( 4 )                               /* LNA MIPIָ����������������Ŀ */
#define UCOM_NV_G_LNA_MIPI_DATA_MAX_NUM     ( 4 )                               /* LNA MIPIָ����������������Ŀ */

#define UCOM_NV_CROSS_MIPI_MEM_INDEX_MAX_NUM        ( 512 )                     /* NV_CROSS_MIPI_MEM_INDEX�д�ŵ������Ŀ */
#define UCOM_NV_CROSS_GPIO_TUNER_MEM_MAX_NUM        ( 192 )                     /* NV_CROSS_GPIO_TUNER_MEM�д�ŵ������Ŀ */

#define UCOM_NV_W_BAND_SECTION_NUM          ( 3 )                               /* W BAND SECTION */
#define UCOM_NV_WCDMA_PA_EN_LINE_NUM        ( 4 )                               /* w pa 4 line */

/* ���HSUPA ETFCI ������ */
#define UCOM_NV_HSUPA_ETFCI_TABLE_MAX_NUM   ( 6 )

#define UCOM_NV_W_TX_TEMP_COMP_NUM                  ( 16 )                      /* ÿ��RF Gain��λ���¶Ȳ�����Ŀ */

#define UCOM_NV_W_TX_RF_GAIN_CTRL_NUM               ( 20 )                      /* RF���浵λ������Ŀ */

#define UCOM_W_MAX_RF_GAIN_CTRL_NUM                 ( 20 )                      /* rf gain ctrl���λ�� */

#define UCOM_W_MAX_RF_BIAS_NUM                      ( 16 )                      /* rf BIAS���λ�� */
#define UCOM_W_MAX_RF_BB_GAIN_NUM                   ( 32 )                      /* rf BB GAIN���λ�� */

#define UCOM_NV_MAX_RF_VCO_CONFIG_NUM               ( 4 )                       /* RF VCO CONFIG */
#define UCOM_NV_W_TX_RF_BIAS_NUM                    ( 0x4 )                     /* RF TX BIAS */
#define UCOM_NV_W_TX_DPA_IQ_REDUCTION_NUM           ( 15 )                      /* DPAҵ�����ֻ��� */
#define UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_NUM         ( 26 )                      /* SC-UPAҵ�����ֻ��� */
#define UCOM_NV_W_TX_DPA_MPR_NUM                    ( 15 )                      /* DPAҵ��Ĺ��ʻ��� */
#define UCOM_NV_W_ANT_NUM                           ( 2 )                       /* 2���� */
#define UCOM_NV_W_TX_SCUPA_MPR_NUM                  ( 26 )                      /* SC-UPAҵ��Ĺ��ʻ��� */
#define UCOM_NV_W_TX_DCUPA_MPR_NUM                  ( 7 )                       /* SC-UPAҵ��Ĺ��ʻ��� */
#define UCOM_NV_SAR_BACKOFF_NUM                     ( 6 )                       /* ��SAR����6���ȼ��� */
#define UCOM_NV_SAR_MODEM_SCENE_NUM                 ( 3 )                       /* modem sar�ĳ�����(��Ϊ�Զ�modem�����䳡�����Զ�modem��Ƶ���䷢�䳡����
                                                                                   �Զ�modem��Ƶ���䷢�䳡�� ) */
#define UCOM_NV_W_SAR_SPECIAL_SCENE_NUM             ( 4 )                       /* WPHY֧��4�����ⳡ�������� */
#define UCOM_NV_W_PA_GAIN_SWITCH_COMP_BOUNDARY_NUM  ( 5 )                       /* W TX PA�����л��㲹��,ÿ��BAND����5������ */
#define UCOM_NV_APT_TABLE_MAX_LEN           ( 96 )                              /* APT��������� */
#define UCOM_NV_APT_STEP_0_8_NUM            ( 32 )                              /* 0.8db����ÿ����λ��APT������ */
#define UCOM_NV_APT_STEP_0_4_NUM            ( 48 )                              /* 0.4db����ÿ����λ��APT������ */
#define UCOM_NV_APT_MAX_NUM                 ( UCOM_NV_APT_STEP_0_4_NUM )        /* ÿ����λ��APT������������ */
#define UCOM_NV_W_PA_NONLINEAR_NUM          ( UCOM_NV_APT_TABLE_MAX_LEN )       /* PA�����Բ��� */

#define UCOM_NV_PA_GAIN_MAX_NUM             ( 3 )                               /* PA��λ���� */
#define UCOM_WCDMA_UARFCN_NUM               ( 0x10 )                            /* ÿ��Ƶ����UARFCN���� */
#define UCOM_NV_W_TX_PA_MODE_NUM            ( 3 )                               /* PA �������:���е� */
#define UCOM_NV_W_TEMP_NUM                  ( 0x10  )                           /* �¶Ȳ������õ��¶ȵ㣬ǰ5���ֱ���� -20,0,20,40,60����6�������ֽڶ��� */
#define UCOM_NV_W_TX_PA_TEMP_NUM            ( 0x10 )                            /* TX PA���¶Ȳ������õ��¶ȵ㣬�ɹ����·�����16�� */
#define UCOM_NV_W_TX_FREQ_COMP_NUM          ( 0x10 )                            /* TX PA���¶Ȳ������õ��¶ȵ㣬�ɹ����·�����16�� */


#define UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM             ( 0x8 )
#define UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM        ( UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM -1 )  /* 6361��AGC GAIN��λ�л����޵ĸ���
                                                         ��ֵ�����ڵ�λ=(UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM - 1) */

#define UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM               ( 0x8 )                                           /* NV����block��λ���� */
#define UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM          ( UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM - 1 )    /* 6361��AGC GAIN��λ�л����޵ĸ���
                                                                  UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM - 1 */

#define UCOM_NV_W_LNA_MIPI_CMD_MAX_NUM              ( 0x4 )                     /* LNA MIPIָ����������������Ŀ */
#define UCOM_NV_W_LNA_MIPI_DATA_MAX_NUM             ( 0x4 )                     /* LNA MIPI���ݿ��������������Ŀ */
#define UCOM_NV_W_LNA_GPIO_STEP_NUM                 ( 0x4 )                     /* LNA GPIO���õ�λ */
#define UCOM_NV_W_LNA_MIPI_STEP_NUM                 ( 0x4 )                     /* LNA MIPI���õ�λ */

#define UCOM_NV_W_TX_HDET_DPA_CM_COMP_NUM           ( 15 )                      /* DPAҵ��PD��CM���� */
#define UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_NUM         ( 26 )                      /* SC-UPAҵ��PD��CM���� */

#define UCOM_NV_W_APT_FREQ_COMP_NUM                 ( 16 )
#define UCOM_NV_W_APT_TEMP_COMP_NUM                 ( 16 )

#define UCOM_NV_W_CHANNEL_NUM               ( 3 )                               /* NV��ÿ��BAND���ָ��е������ŵ� */
#define UCOM_NV_W_PA_SWITCH_COMP_SLOT       ( 4 )                               /* Pa�л�����ʱ϶�� */
#define UCOM_NV_W_APC_ATTEN_NUM             ( 0x58 )
#define UCOM_NV_W_TX_HDET_PV_NUM            ( 0x10 )                            /* PA�Ĺ�����ѹ���� */
#define UCOM_NV_W_PA_GAIN_SWITCH_COMP_CHAN_NUM      ( 4 )                       /* W TX PA�����л��㲹����4���ֽ�Ƶ�� */
#define UCOM_NV_W_TX_APT_SCUPA_CM_COMP_NUM          ( 26 )                      /* SC-UPAҵ��APT��CM���� */

#define UCOM_NV_W_TX_APT_DPA_CM_COMP_NUM            ( 15 )                     /* DPAҵ��APT��CM���� */
#define UCOM_NV_W_TX_PA_VBIAS_NUM           ( 3 )                               /* pa vbias���� */


#define UCOM_NV_W_TOTAL_BAND_NUM            ( 0x06 )
#define UCOM_NV_W_RF_BAND_CONFIG_NUM            ( 10 )                          /* ext band config֧�ֵ�WƵ�� */

#define UCOM_NV_RFABB_INIT_REG_NUM              ( 60 )                          /* 6361��ʼ���Ĵ���������60�� */
#define UCOM_NV_RFABB_INIT_REG_NEW_RAM_NUM      ( 256 )                         /* 6362��ʼ���Ĵ���������256�� */

/* AP+Sensor�ֳ�״̬����,Ŀǰ֧��5��״̬ */
#define UCOM_NV_TUNER_HANDLE_STATUS_NUM         ( 5 )

/* activeʱ��w tuner֧�ֵ����MIPI���� */
#define UCOM_NV_W_TUNER_MIPI_CMD_MAX_NUM        ( 7 )
#define UCOM_NV_W_TUNER_MIPI_DATA_MAX_NUM       ( 8 )

/* G tuner֧�ֵ����MIPI���� */
#define UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM      ( 5 )
#define UCOM_NV_GSM_TUNER_MIPI_DATA_MAX_NUM     ( 6 )

/* WG PA֧�ֵ����MIPI���� */
#define UCOM_NV_PA_MIPI_CMD_MAX_NUM             ( 5 )
#define UCOM_NV_PA_MIPI_DATA_MAX_NUM            ( 6 )

/* ET֧�ֵ����MIPI���� */
#define UCOM_NV_ET_MIPI_CMD_MAX_NUM             ( 7 )
#define UCOM_NV_ET_MIPI_DATA_MAX_NUM            ( 8 )


#define UCOM_NV_MAX_MIPI_ANT_CMD_NUMBER         ( 4 )                           /* ant switch���������������Ŀ */
#define UCOM_NV_MAX_MIPI_ANT_DATA_NUMBER        ( 5 )                           /* ant switch���������������Ŀ */

#define UCOM_NV_MIPI_NOTCH_CMD_NUMBER           ( 3 )                           /* notch���������������Ŀ */
#define UCOM_NV_MIPI_NOTCH_DATA_NUMBER          ( 4 )                           /* notch�����������Ŀ */

#define UCOM_NV_W_MIPI_PA_TRIGGER_NUM           ( 2 )

#define UCOM_G_RX_GAIN0_DCR_CHAN_NUM            ( 16 )                          /*DCR channel NUM */
/* DCXO����ʽϵ���ĸ��� */
#define UCOM_DCXO_POLY_COEFF_NUM            ( 4 )

#define UCOM_NV_XO_TEMP_COMP_NUM            ( 32 )
#define UCOM_NV_BATT_TEMP_SENSOR_NUM        ( 8 )
/* ��� 144���¶�-Ƶ��������:����ʱ���� FIFOԭ�� */
#define UCOM_DCXO_TEMP_AFC_MAX_NUM          ( 144 )
#define UCOM_NV_PA_TEMP_SENSOR_NUM          ( 32 )

#define UCOM_NV_GSM_LINEAR_PA_GAIN_NUM                ( 4 )                       /* GSM ����PA������� */

#define UCOM_NV_GSM_LINEAR_PA_SWITCH_THRESHOLD_NUM    ( UCOM_NV_GSM_LINEAR_PA_GAIN_NUM - 1 )  /* GSM ����PA������� */

#define UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM       ( 5 )                   /* ��������AFCƫ�ü��������������� */

#define UCOM_NV_RCM_TAS_TABLE_NUM                      ( 20 )                   /* TAS�Ʒֱ��״̬�������¾ɼƷֱ���չΪ20 */


#define UCOM_NV_GSM_TX_HD35_ARFCN_NUM                 ( 3 )                     /* ÿ��Ƶ������У׼Ƶ�� */
#define UCOM_NV_GSM_TX_HD35_PCL_NUM                   ( 3 )                     /* ÿ��Ƶ������У׼PCL�� */
#define UCOM_NV_CDMA_RF_BB_GAIN_NUM                   ( 32 )                    /* RF BB��λΪ32�� */
#define UCOM_NV_CDMA_ANT_NUM                          ( 2 )                     /* 2���� */
#define UCOM_NV_CDMA_CHANNEL_NUM                      ( 3 )                     /* NV��ÿ��BAND���ָ��е������ŵ� */
#define UCOM_NV_CDMA_UARFCN_NUM                       ( 0x10 )                  /* ÿ��Ƶ����UARFCN���� */

#define UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM          ( UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM )                            /* NV����noblock��λ���� */
#define UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM     ( UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM -1 )  /* 6361��AGC GAIN��λ�л����޵ĸ���
                                                                                                      ��ֵ�����ڵ�λ=(CSDR_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM - 1) */
#define UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM            ( UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM )                                      /* NV����block��λ���� */
#define UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM       ( UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM - 1 )   /* 6361��AGC GAIN��λ�л����޵ĸ��� */
#define UCOM_NV_CDMA_TX_PA_MODE_NUM                   ( 3 )                     /* ���е͵�λ */
#define UCOM_NV_CDMA_TOTAL_BAND_NUM                   ( 0x06 )

#define UCOM_NV_CDMA_APC_ATTEN_NUM                    ( UCOM_NV_W_APC_ATTEN_NUM )
#define UCOM_NV_CDMA_BAND_SECTION_NUM                 ( UCOM_NV_W_BAND_SECTION_NUM ) /* W BAND SECTION */
#define UCOM_NV_CDMA_TX_HDET_PV_NUM                   ( UCOM_NV_W_TX_HDET_PV_NUM )
#define UCOM_NV_CDMA_TX_PA_TEMP_NUM                   ( UCOM_NV_W_TX_PA_TEMP_NUM )   /* TX PA���¶Ȳ������õ��¶ȵ㣬�ɹ����·�����16�� */
#define UCOM_NV_CDMA_TX_FREQ_COMP_NUM                 ( UCOM_NV_W_TX_FREQ_COMP_NUM ) /* TX PA���¶Ȳ������õ��¶ȵ㣬�ɹ����·�����16�� */
#define UCOM_NV_CDMA_TX_RF_GAIN_CTRL_NUM              ( UCOM_NV_W_TX_RF_GAIN_CTRL_NUM )
#define UCOM_NV_CDMA_TX_TEMP_COMP_NUM                 ( UCOM_NV_W_TX_TEMP_COMP_NUM )
#define UCOM_NV_CDMA_TEMP_NUM                         ( UCOM_NV_W_TEMP_NUM )
#define UCOM_NV_CDMA_MIPI_PA_TRIGGER_NUM              ( 1 )  /* pa trigger���� */
#define UCOM_NV_CDMA_MIPI_PA_VCC_VBIAS_NUM            ( 1 )  /* pa vcc cmd��data���� */

#define UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM        ( 8 )                     /* ����ȫ��ͨ���ص�ͨ�����ó�����Ŀ */

#define UCOM_NV_FEM_IO_CFG_MAX                        ( 16 )                    /* 18002 nv�����֧�ֵ����ø��� */

/* BBP�ӿ��ṩ8��DPD���л�����Ϊ9����ÿ�ű����Ϊ64 */
#define UCOM_NV_BBP_DPD_LUT_MAX_NUM                 ( 8 )
#define UCOM_NV_DPD_LUT_THERSHOLD_MAX_NUM           ( UCOM_NV_BBP_DPD_LUT_MAX_NUM + 1 )
#define UCOM_NV_DPD_LUT_MAX_LEN                     ( 64 )

/* NV���ж����9�ű��Ǳ�ʾ��3*3�����������ָ��е��ŵ���ÿ���ŵ�3�ű� */
#define UCOM_NV_DPD_LUT_MAX_NUM                     ( 9 )
#define UCOM_NV_ET_LUT_MAX_LEN                      ( 256 )

#define UCOM_NV_W_DPD_FREQ_COMP_NUM                 ( UCOM_NV_W_APT_FREQ_COMP_NUM )
#define UCOM_NV_W_DPD_TEMP_COMP_NUM                 ( UCOM_NV_W_APT_TEMP_COMP_NUM )

#define UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM          ( 8 )                       /* ET DELAY Ƶ�����ֵ */

#define UCOM_NV_HARMONIC_NUM                        ( 5 )                       /* ���ڵ�г����Ŀ */

/* W��FET��̬����SNR���޸��� */
#define UCOM_NV_W_FET_DYN_DEC_SNR_NUM               ( 22 )

/* W��FET��̬����ä���SNR����ʱ϶�ṹ����� */
#define UCOM_NV_W_FET_BLIND_DYN_DEC_SNR_NUM         ( 5 )

/* W��FET��̬�����ä���SNR����ʱ϶�ṹ����� */
#define UCOM_NV_W_FET_NOBLIND_DYN_DEC_SNR_NUM       ( 4 )
#define UCOM_NV_MAX_MIPI_TAS_CMD_NUMBER             ( 4 )                       /* tas mipi���������������Ŀ */
#define UCOM_NV_MAX_MIPI_TAS_DATA_NUMBER            ( 5 )                       /* tas mipi���������������Ŀ */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 ö����    :UCOM_NV_DC_SC_MODE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :�ز�ģʽ
*****************************************************************************/
enum UCOM_NV_DC_SC_MODE_ENUM
{
    UCOM_NV_SC_MODE                     = 0,                                    /* ���ز�ģʽ */
    UCOM_NV_DC_MODE                     = 1,                                    /* ˫�ز�ģʽ */
    UCOM_NV_DC_SC_MODE_BUTT             = 2
};
typedef VOS_UINT16 UCOM_NV_DC_SC_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : UCOM_NV_CHAN_CONNECT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : A/Bͨ���ı�ʶ
*****************************************************************************/
enum UCOM_NV_CHAN_CONNECT_ENUM
{
    UCOM_NV_CHAN_CONNECT_A                  = 0,                                /* Aͨ�� */
    UCOM_NV_CHAN_CONNECT_B                  = 1,                                   /* Bͨ�� */
    UCOM_NV_CHAN_CONNECT_BUTT               = 2
};
typedef VOS_UINT16 UCOM_NV_CHAN_CONNECT_ENUM_UINT16;


/*****************************************************************************
 ö����    : UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : г��������
*****************************************************************************/
enum UCOM_NV_WCDMA_SPUR_TYPE_ENUM
{
    UCOM_NV_WCDMA_SPUR_1920                  = 0,                               /* 19.20M */
    UCOM_NV_WCDMA_SPUR_1536                  = 1,                                  /* 15.36M */
    UCOM_NV_WCDMA_SPUR_6144                  = 2,                                  /* 61.44M */
    UCOM_NV_WCDMA_SPUR_BUTT                  = 3
};
typedef VOS_UINT16 UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_XO_TYPE_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :������������,0��ʾ DCXO,1��ʾ TCXO
*****************************************************************************/
enum UCOM_NV_XO_TYPE_ENUM
{
    UCOM_NV_XO_TYPE_DCXO                = 0,                                    /* ��ʾʹ�� DCXO */                                                           /* ���н�����DPCH */
    UCOM_NV_XO_TYPE_TCXO                = 1,                                    /* ��ʾʹ�� TCXO */                                                             /* ���д���RACH */
    UCOM_NV_XO_TYPE_BUTT                = 2
};
typedef VOS_UINT16 UCOM_NV_XO_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :DCXO���������¶Ȳɼ���·��һ�����ڲɼ����º͸��£���һ�����ڲɼ����ºͲ��ֳ���
*****************************************************************************/
enum UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM
{
    UCOM_NV_DCXO_TEMP_CIRCUIT_HIGH              = 0,                            /* ���µ�·  */
    UCOM_NV_DCXO_TEMP_CIRCUIT_NORMAL            = 0,                            /* ���º͸��µ�·��һ�� */                                                           /* ���н�����DPCH */
    UCOM_NV_DCXO_TEMP_CIRCUIT_LOW               = 1,                            /* ���µ�· */                                                             /* ���д���RACH */
    UCOM_NV_DCXO_TEMP_CIRCUIT_BUTT              = 2
};
typedef VOS_UINT16 UCOM_NV_DCXO_TEMP_CIRCUIT_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :��ʱ������
*****************************************************************************/
enum UCOM_NV_SINGLE_XO_TYPE_ENUM
{
    UCOM_NV_SINGLE_XO_TYPE_UNSUPPORT      = 0,                                    /* ��֧�ֵ�ʱ�� */                                                           /* ���н�����DPCH */
    UCOM_NV_SINGLE_XO_TYPE_TCXO           = 1,                                    /* ��TCXO */                                                           /* ���д���RACH */
    UCOM_NV_SINGLE_XO_TYPE_DCXO           = 2,                                    /* ��DCXO */
    UCOM_NV_SINGLE_XO_TYPE_BUTT
};
typedef VOS_UINT16 UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    :UCOM_NV_POWER_STEP_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :APT����������,0��ʾ 0.8db����,1��ʾ 0.4db����
*****************************************************************************/
enum UCOM_NV_APT_STEP_ENUM
{
    UCOM_NV_POWER_STEP_0_POINT_8_DB           = 0,                                /* ��ʾAPT��Ϊ0.8db���� */                                                           /* ���н�����DPCH */
    UCOM_NV_POWER_STEP_0_POINT_4_DB           = 1,                                /* ��ʾAPT��Ϊ0.4db���� */                                                             /* ���д���RACH */
    UCOM_NV_POWER_STEP_BUTT
};
typedef VOS_UINT16 UCOM_NV_POWER_STEP_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :HARQ������������,0��ʾ��֧������, 1��ʾ���Ƶ�DDR, 2��ʾ���Ƶ�Ƭ���ڴ�
*****************************************************************************/
enum UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM
{
    UCOM_NV_BBP_HARQ_OUT_NOT_SUPPORT       = 0,                                /* ��֧��HARQ���� */                                                           /* ���н�����DPCH */
    UCOM_NV_BBP_HARQ_OUT_IN_DDR            = 1,                                /* HARQ���Ƶ�DDR */                                                             /* ���д���RACH */
    UCOM_NV_BBP_HARQ_OUT_IN_CHIP           = 2,                                /* HARQ���Ƶ�Ƭ���ڴ� */
    UCOM_NV_BBP_HARQ_OUT_BUTT
};
typedef VOS_UINT16 UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :���߱ȽϽ׶�,��Ϊ�����׶�
*****************************************************************************/
enum UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM
{
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ONE                     = 0,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_TWO                     = 1,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_THREE                   = 2,
    UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT                    = 3
};
typedef VOS_UINT16 UCOM_NV_RCM_AGENTC_COMPARE_PHASE_ENUM_UINT16;


/*****************************************************************************
 ö����    :UCOM_NV_32K_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :32Kʱ������
*****************************************************************************/
enum UCOM_NV_32K_TYPE_ENUM
{
    UCOM_NV_32K_TYPE_32000              = 0,                                    /* 32kʱ�Ӹ���32000 */                                                           /* ���н�����DPCH */
    UCOM_NV_32K_TYPE_32764              = 1,                                    /* 32kʱ�Ӹ���32764 */                                                           /* ���д���RACH */
    UCOM_NV_32K_TYPE_32768              = 2,                                    /* 32kʱ�Ӹ���32768 */
    UCOM_NV_32K_TYPE_BUTT
};
typedef VOS_UINT16 UCOM_NV_32K_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_DRX_CTRL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :0��ʾ������˯�ߣ�1��ʾ����˯��
*****************************************************************************/
enum UCOM_NV_DRX_CTRL_ENUM
{
    UCOM_NV_DRX_CTRL_DISABLE                = 0,                                /* ������˯�� */                                                           /* ���н�����DPCH */
    UCOM_NV_DRX_CTRL_ENABLE                 = 1,                                /* ����˯�� */                                                             /* ���д���RACH */
    UCOM_NV_DRX_CTRL_BUTT
};
typedef VOS_UINT16 UCOM_NV_DRX_CTRL_ENUM_UINT16;

/*****************************************************************************
 ö����    : UCOM_NV_RFFE_CTRL_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ǰ���������ýӿ�����,Ŀǰ����ʹ��MIPI��GPIO
*****************************************************************************/
enum UCOM_NV_RFFE_CTRL_ENUM
{
    UCOM_NV_RFFE_CTRL_GPIO              = 0,                                    /* ʹ��GPIO���÷�ʽ */
    UCOM_NV_RFFE_CTRL_MIPI              = 1,                                    /* ʹ��MIPI���÷�ʽ */
    UCOM_NV_RFFE_CTRL_GPIO_AND_MIPI     = 2,                                    /* ʹ��GPIO+MIPI���÷�ʽ */
    UCOM_NV_RFFE_CTRL_BUTT
};
typedef VOS_UINT16 UCOM_NV_RFFE_CTRL_ENUM_UINT16;

/*****************************************************************************
 ö����    : UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : tuner֧�ֵ���ʽ��0:Ӳ����֧�֣�1:֧�ֿ�����2:֧��AP+Sensor,
             3:֧�ֶ�̬��г
*****************************************************************************/
enum UCOM_NV_TUNER_SUPPORT_MODE_ENUM
{
    UCOM_NV_TUNER_SUPPORT_NONE                  = 0,
    UCOM_NV_TUNER_SUPPORT_OPEN_LOOP             = 1,
    UCOM_NV_TUNER_SUPPORT_AP_SENSOR             = 2,
    UCOM_NV_TUNER_SUPPORT_CLOSED_LOOP           = 3,
    UCOM_NV_TUNER_SUPPORT_BUTT
};
typedef VOS_UINT16 UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :Rx EVM����
*****************************************************************************/
enum UCOM_NV_RX_EVM_TEST_EN_ENUM
{
    UCOM_NV_RX_EVM_TEST_DISABLE         = 0,                                    /* ��ʾ����ģʽ */                                                           /* ���н�����DPCH */
    UCOM_NV_RX_EVM_TEST_ENABLE          = 1,                                    /* ��ʾRx EVM����ģʽ */                                                             /* ���д���RACH */
    UCOM_NV_RX_EVM_TEST_BUTT            = 2
};
typedef VOS_UINT16 UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16;


/*****************************************************************************
 ö����    :UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum UCOM_NV_FEMIO_CTRL_MODE_ENUM
{
    UCOM_NV_FEMIO_CTRL_TOP              = 0,                                    /* �������� */                                                          /* ���н�����DPCH */
    UCOM_NV_GPIO_ONLY                   = 1,                                    /* ֻ����GPIO */                                                           /* ���д���RACH */
    UCOM_NV_MIPI_ONLY                   = 2,                                    /* ֻ����MIPI */
    UCOM_NV_GPIO_MIPI                   = 3,                                    /* ����GPIO��MIPI */
    UCOM_NV_FEMIO_CTRL_BUTT
};
typedef VOS_UINT32 UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    :UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM
{
    UCOM_NV_DCXO_TEMP_RISE_USE_AP       = 1,                                    /* ʹ��AP���� */                                                          /* ���н�����DPCH */
    UCOM_NV_DCXO_TEMP_RISE_USE_PA       = 2,                                    /* ʹ��PA���� */                                                           /* ���д���RACH */
    UCOM_NV_DCXO_TEMP_RISE_USE_APANDPA  = 3,                                    /* ʹ��AP��PA���� */
    UCOM_NV_DCXO_TEMP_RISE_BUTT
};
typedef VOS_UINT16 UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16;
/*****************************************************************************
 ö����    :UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :�����о�ҵ������
*****************************************************************************/
enum UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM
{
    UCOM_NV_INTERFE_BUSINESS_TYPE_IDLE     =0 ,                            /* Idle״̬ */
    UCOM_NV_INTERFE_BUSINESS_TYPE_PS          ,                            /* PSҵ��״̬ */
    UCOM_NV_INTERFE_BUSINESS_TYPE_CS          ,                            /* CSҵ��״̬ */
    UCOM_NV_INTERFE_BUSINESS_TYPE_BUTT

};
typedef VOS_UINT16 UCOM_NV_INTERFERENCE_BUSINESS_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_INTERFE_ACTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :�����о�����
*****************************************************************************/
enum UCOM_NV_INTERFE_ACTION_ENUM
{
    UCOM_NV_INTERFE_ACTION_NONE                        =   0,                   /* ��Чֵ */
    UCOM_NV_INTERFE_ACTION_CURRENT_RX_BLANKING         =   1,                   /* ��ǰģ��rxblanking */
    UCOM_NV_INTERFE_ACTION_CURRENT_TX_BLANKING         =   2,                   /* ��ǰģ��txblanking */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_RX_BLANKING        =   3,                   /* �Է�ģ��rxblanking */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_TX_BLANKING        =   4,                   /* �Է�ģ��txblanking */
    UCOM_NV_INTERFE_ACTION_CURRENT_G_AVOID_L           =   5,                   /* G��ǰģ RXBLANKING ����LTEѰ�� */
    UCOM_NV_INTERFE_ACTION_OPPOSITE_G_AVOID_L          =   6,                   /* G�Է�ģ RXBLANKING ����LTEѰ�� */
    UCOM_NV_INTERFE_ACTION_BUTT
};
typedef VOS_UINT16 UCOM_NV_INTERFE_ACTION_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :���Կ���
*****************************************************************************/
enum UCOM_NV_FEATURE_SWITCH_ENUM
{
    UCOM_NV_INTERFE_FEATURE_SWITCH_CLOSE                    =  0,               /* ���Կ��عر� */
    UCOM_NV_INTERFE_INTERFERENCE_OPEN                           ,               /* �������Կ��ش� */
    UCOM_NV_INTERFE_MAX_POWER_BACKOFF_OPEN                      ,               /* ����ʻ������Կ��ش� */
    UCOM_NV_INTERFE_INTERFERENCE_MAX_POWER_BACKOFF_OPEN         ,               /* ���ź�����ʻ������Կ��ض��� */
    UCOM_NV_INTERFE_FEATURE_SWITCH_BUTT
};
typedef VOS_UINT16 UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16;

/*****************************************************************************
 ö����    :UCOM_NV_W_HARMONIC_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :����г����������Դ
*****************************************************************************/
enum UCOM_NV_W_HARMONIC_TYPE_ENUM
{
    UCOM_NV_W_HARMONIC_TYPE_ABB                             = 0,                /* abb ������г�� */
    UCOM_NV_W_HARMONIC_TYPE_RF                                 ,                /* rf ���������г�� */
    UCOM_NV_W_HARMONIC_TYPE_BUTT
};
typedef VOS_UINT16 UCOM_NV_W_HARMONIC_TYPE_ENUM_UINT16;

/*****************************************************************************
  6 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/
/* xiongjiangjiang Begine */
/*****************************************************************************
 �ṹ��    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_XO_TYPE_ENUM_UINT16             enXoDefine;
}UCOM_NV_NV_ITEM_XO_DEFINE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_MIPI_CMD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIPI ָ����ƶζ��壬��żУ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwSlaveAddr    :4;                             /* Mipi Slave��ַ����Чֵ0-15 */
    VOS_UINT16                  uhwRegAddr      :9;                             /* �Ĵ�����ַ OR ��ʼ��ַ */
    VOS_UINT16                  uhwByteCnt      :3;                             /* ��Ҫд���byte(����)���� */
}UCOM_NV_MIPI_CMD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_MIPI_BYTE_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIPI ָ�����ݶζ��壬��żУ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwByteData     :8;                             /* ָ�����ݶζ��壬��żУ���������� */
    VOS_UINT16                  uhwMasterSel    :3;                             /* Mipi Masterָʾ */
    VOS_UINT16                  uhwReserved     :5;                             /* ���� */
}UCOM_NV_MIPI_BYTE_DATA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_MIPI_COMM_STRU
 Э����  :
 �ṹ˵��  : ����һЩmipi���ܹ���ָ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[5];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[6];
}UCOM_NV_MIPI_COMM_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_MIPI_INIT_WORD_STRU
 �ṹ˵��  : ������ģ��ʼ������,��ʼ��mipi�����Ľӿ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[15];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[16];
}UCOM_NV_WG_MIPI_INIT_WORD_STRU;

/*****************************************************************************

 �ṹ��    : UCOM_Tuner_Ctrl_Reg_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         uwTunerMipiMask    :4;                   /* TUNER_MIPI_MASK�Ĵ������� */
    VOS_UINT32                         uwGpioMask         :17;                  /* GPIO��ʽmask �Ĵ�������*/
    VOS_UINT32                         uwReserved3        :11;
}UCOM_NV_TUNER_CTRL_REG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CROSS_GPIO_MIPI_CTRL_STRU
 Э����  :
 �ṹ˵��  : ���ڴ洢CrossMipiTable
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         uwTunerEn;                               /* TUNER_EN�Ĵ�������ֵ */
    VOS_UINT32                         uwTunerRegEn;                            /* TUNER_REG_EN�Ĵ�������ֵ */
    VOS_UINT32                         uwGpioCrossEn;                           /* GPIO���������Ƿ�ʹ��*/
    VOS_UINT32                         uwTasIndEn;                              /* TAS IND ȡ������*/
    VOS_UINT32                         uwMipiTuner0Len;                         /* MIPI ��ʽModem0���ز�ʵ��buffer����*/
    VOS_UINT32                         uwMipiTuner1Len;                         /* MIPI ��ʽModem0���ز�ʵ��buffer����*/
    VOS_UINT32                         uwMipiTuner2Len;                         /* MIPI ��ʽModem0���ز�ʵ��buffer����*/
    VOS_UINT32                         uwGpioTunerLen;                          /* GPIO��ʽʵ��buffer����*/
    UCOM_NV_TUNER_CTRL_REG_STRU        stReg;
}UCOM_NV_CROSS_GPIO_MIPI_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CROSS_MIPI_MEM_INDEX
 Э����  :
 �ṹ˵��  : ���ڴ洢mipiָ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         auwMipiBuffer[UCOM_NV_CROSS_MIPI_MEM_INDEX_MAX_NUM];
}UCOM_NV_CROSS_MIPI_MEM_INDEX_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CROSS_GPIO_MEM_STRU
 Э����  :
 �ṹ˵��  : ���ڴ洢gpioָ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         auwGpioBuffer[UCOM_NV_CROSS_GPIO_TUNER_MEM_MAX_NUM];
}UCOM_NV_CROSS_GPIO_MEM_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_PHY_AUTO_INIT_FLAG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY�Ƿ��ϵ��Զ���ʼ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPhyAutoInitFlag;
}UCOM_NV_PHY_AUTO_INIT_FLAG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_NV_ITEM_XO_DEFINE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʱ�����Ͷ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_SINGLE_XO_TYPE_ENUM_UINT16      enSingleXoType;                     /* ��ʱ���Ƿ�ʹ��,0:��֧�֣�1:��tcxo��2:��dcxo */
    UCOM_NV_32K_TYPE_ENUM_UINT16            en32kType;                          /* 0:32000,1:32764��2:32768*/

}UCOM_NV_SINGLE_XO_DEFINE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_AFC_K_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʱ��Kֵ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwKValue;                          /* ��ʾBBP AFCÿ������λ��hz����Ĭ��Ϊ4 */
    VOS_UINT16                              uhwReserve;                         /* ���� */

}UCOM_NV_W_AFC_K_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : rf reg12 �¶�����NV_RFIC_TEMP_COMP_WEIGTH
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNvRficTempCompWeigh;
}UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_INIT_FREQUENCY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.2��ʾ��ͨ����ĳ�ʼƵƫ���¶�
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitFrequency;                       /* ��ͨ����ĳ�ʼƵƫ */
    VOS_INT16                           shwInitTemperature;                     /* ��ͨ����ĳ�ʼ�¶� */
}UCOM_NV_XO_INIT_FREQUENCY_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_DYNAMIC_FREQUENCY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.2��ʾƽ̨�ϴ�AFC����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDymamicFrequency;                    /* ƽ̨�ϴ�AFC����ֵ */
    VOS_INT16                           shwDymamicTemperature;                  /* ƽ̨�ϴ�AFC���¶� */
}UCOM_NV_DYNAMIC_FREQUENCY_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_TX_TEMP_DEFINE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.3 3G��2G���з��书������¶ȱ仯��Χ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxTempDefine[UCOM_NV_W_TX_PA_TEMP_NUM];
}UCOM_NV_WG_TX_TEMP_DEFINE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TEMP_SENCOR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :for UCOM_NV_PA_TEMP_SENSOR_STRU
                UCOM_NV_XO_TEMP_SENSOR_STRU
                UCOM_NV_USIM_BATT_TEMP_SENSOR_STRU
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaTempTemp;                          /* �¶�:0.1�� */
    VOS_UINT16                          uhwPaTempVol;                           /* �����������ѹ */
}UCOM_NV_TEMP_SENCOR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_PA_TEMP_SENSOR_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.1 PA���¶ȼ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astPaTempSensor[UCOM_NV_PA_TEMP_SENSOR_NUM];
}UCOM_NV_PA_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_TEMP_SENSOR_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.1 ��ͨ����ĳ�(��)�µ�ѹ-�¶ȱ�
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astXoTempSensor[UCOM_NV_XO_TEMP_COMP_NUM];
}UCOM_NV_XO_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_LOW_TEMP_SENSOR_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.1 ��ͨ����ĵ��µ�ѹ-�¶ȱ�
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astXoLowTempSensor[UCOM_NV_XO_TEMP_COMP_NUM];
}UCOM_NV_XO_LOW_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_BATT_TEMP_SENSOR_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.1 ��ص��¶ȼ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_TEMP_SENCOR_STRU            astBattTempSensor[UCOM_NV_BATT_TEMP_SENSOR_NUM];
}UCOM_NV_BATT_TEMP_SENSOR_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ʒ����NV����ͬ��Ʒ��Log����·����һ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwProductType;                         /* ��Ʒ���� */
    VOS_UINT16                          uhwReserve;                             /* ���� */
}UCOM_NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_LOW_TEMP_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : XO���¼���������NV,�������Կ������·�л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLowTempSupport;                      /* Ӳ���Ƿ�֧�ֵ��¼�⣬0-��֧�֣�1-֧�� */
    VOS_INT16                           shwSwitchDeltaTemp;                     /* ���µ�·��ԭ�е�·���л�����Ϊ(У׼�¶�+��ֵ)��
                                                                                   �������л������¶�ʱʹ�õ��µ�·��Ĭ��Ϊ0��
                                                                                   ���л�����ΪУ׼�¶�(���µ�·)����λ0.1�� */
    VOS_UINT16                          uhwTempDeltaThreshold;                  /* ������·У׼ֵ��ƫ�����ޣ�Ĭ��Ϊ10����λ0.1�� */
    VOS_UINT16                          uhwReserve;                             /* ���� */
}UCOM_NV_XO_LOW_TEMP_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_INIT_LOW_TEMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : У׼ʱ�����µ�·�ļ���¶ȣ����ݻָ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitLowTemp;                         /* У׼ʱ�����µ�·�ļ���¶ȣ���λ0.1�� */
    VOS_UINT16                          uhwReserve;                             /* ���� */
}UCOM_NV_XO_INIT_LOW_TEMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_IQ_REV_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IQ�ӷ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxAIRevSel;                          /* Rx A I·�ӷ� */
    VOS_UINT16                          uhwRxAQRevSel;                          /* Rx A Q·�ӷ� */
    VOS_UINT16                          uhwRxBIRevSel;                          /* Rx B I·�ӷ� */
    VOS_UINT16                          uhwRxBQRevSel;                          /* Rx B Q·�ӷ� */
    VOS_UINT16                          uhwTxIRevSel;                           /* Tx I·�ӷ� */
    VOS_UINT16                          uhwTxQRevSel;                           /* Tx Q·�ӷ� */
}UCOM_NV_WG_IQ_REV_CONTROL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_DCXO_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DCXO����ʽ�� 4��ϵ�����¶ȵ������Сֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwMantissaDefault[UCOM_DCXO_POLY_COEFF_NUM];  /* ���δ��a0,a1,a2,a3��β�� */
    VOS_UINT16                          auhwExponentDefault[UCOM_DCXO_POLY_COEFF_NUM]; /* ���δ��a0,a1,a2,a3��ָ�� */
    /* �ر�˵��:shwTmax/shwTminʵ�����Ǻ��������,��ϵ��������һ�𲻺���.��Ϊ������,����DSP�ڲ�
       ֻʹ��pstAfcContext->stDcxoPara.shwSampleTempMax/shwSampleTempMin */
    VOS_INT16                           shwTmax;                                /* �����¶����ֵ */
    VOS_INT16                           shwTmin;                                /* �����¶���Сֵ */
}UCOM_NV_DCXO_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_DCXO_AFC_VS_TEMP_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���һ��DCXO���¶�-Ƶ��(ʵ��ΪAFC����ֵ)����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTemp;                                /* �¶� */
    VOS_INT16                           shwFreqPpm;                              /* �����¶��¶�Ӧ�����Ƶƫ */
}UCOM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_TEMP_READ_PERIOD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO��ȡ�¶ȵ�����,����IDLE̬��DCH̬
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIdlePeriod;                          /* IDLE̬�¶�ȡ���� */
    VOS_UINT16                          uhwDchPeriod;                           /* IDLE̬�¶�ȡ���� */
}UCOM_NV_DCXO_TEMP_READ_PERIOD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO����ʽϵ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwLowMantissa[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT16                          auhwLowExponent[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT32                          auwHighMantissa[UCOM_DCXO_POLY_COEFF_NUM];
    VOS_UINT16                          auhwHighExponent[UCOM_DCXO_POLY_COEFF_NUM];
}UCOM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_DCXO_FREQ_VS_TEMP_ARRAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���DCXO���¶�-Ƶ��(ʵ��ΪAFC����ֵ)��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidNum;                             /* ��������Ч���� */
    VOS_INT16                           shwTmax;                                /* �����¶����ֵ */
    VOS_INT16                           shwTmin;                                /* �����¶���Сֵ */
    UCOM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU astAfcTempValue[UCOM_DCXO_TEMP_AFC_MAX_NUM]; /* �������� */
}UCOM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_SAMPLE_UPDATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO�������²�������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWcdmaPeriod;                          /* W DCXO����д��NV���ڣ���λ֡,Ĭ��30000 */
    VOS_UINT32                          uwGsmPeriod;                            /* G DCXO����д��NV���ڣ���λ֡,Ĭ��65000 */
    VOS_UINT16                          uhwUpdateLowThr;                        /* ��������������,Ĭ��644,��0.6ppm*2^30/10^6 */
    VOS_UINT16                          uhwUpdateHighThr;                       /* ��������������,Ĭ��2684,��2.5ppm*2^30/10^6 */
}UCOM_NV_DCXO_SAMPLE_UPDATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TAS_GPIO_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTasM2PowerCtrlWord;                   /* Tas TxBlankingʱM0˥��M2���ʵĿ����� */
}UCOM_NV_TAS_GPIO_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��SAR����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSarBackoffTestModeFlg;               /* ��SAR����ģʽ */
}UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU;

typedef UCOM_NV_SAR_BACKOFF_TEST_MODE_STRU  UCOM_NV_GUC_SAR_BACKOFF_TEST_MODE_STRU;
/*****************************************************************************
 ö����    : UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU
 Э����  :
 ö��˵��  : DC offset��ֱ��У׼����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDciLimit;                            /* I·��ֱ������,��λmV */
    VOS_INT16                           shwDcqLimit;                            /* Q·��ֱ������,��λmV */
}UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_CTRIM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO C1ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcxoCTrim;                           /*Range:[0,255]*/
}UCOM_NV_DCXO_CTRIM_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_C2_FIX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCXO C2У׼ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcxoC2fix;
}UCOM_NV_DCXO_C2_FIX_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_TCXO_AFC_SLOPE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UCOM_NV_TCXO_AFC_SLOPE_STRU
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAfcSlope;                             /* TCXO AFC??,??? */
}UCOM_NV_TCXO_AFC_SLOPE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_SEARCH_AFC_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ashwSearchAfc2��ashwSearchAfcDelta2���ɵڶ���������У׼����
             ashwSearchAfc3��ashwSearchAfcDelta3���ɵ�����������У׼����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwSearchAfc2[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM];      /* �ڶ�������AFCֵ */
    VOS_INT16                           ashwSearchAfcDelta2[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM]; /* �ڶ�������AFCƫ��ֵ */
    VOS_INT16                           ashwSearchAfc3[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM];      /* ����������AFCֵ */
    VOS_INT16                           ashwSearchAfcDelta3[UCOM_NV_DCXO_SEARCH_AFC_OFFSET_SAMPLE_NUM]; /* ����������AFCƫ��ֵ */
}UCOM_NV_DCXO_SEARCH_AFC_OFFSET_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_BUCK_VOLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BUCK��ѹֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBuck1Volt;                           /* buck1��ѹֵ,��λmV */
    VOS_UINT16                          uhwBuck2Volt;                           /* buck2��ѹֵ,��λmV */
}UCOM_NV_BUCK_VOLT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RFIC_SSI_WAIT_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BUCK��ѹֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRficSsiWaitTime;
}UCOM_NV_RFIC_SSI_WAIT_TIME_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNumber;
    VOS_INT16                           ashwGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_GSM_LINEAR_PA_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_LINEAR_PA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA������
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwNumber;
    VOS_INT16                           ashwGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_EDGE_LINEAR_PA_GAIN_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_PCL_PA_GAIN_INDEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           auhwPaGainIndex[UCOM_NV_G_PCL_NUM];     /* 32�����ʵȼ���Ӧ��PA�������� */
}UCOM_NV_GSM_TX_PCL_PA_GAIN_INDEX_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_PCL_PA_GAIN_INDEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           auhwPaGainIndex[UCOM_NV_G_PCL_NUM];     /* 32�����ʵȼ���Ӧ��PA�������� */
}UCOM_NV_EDGE_TX_PCL_PA_GAIN_INDEX_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TX_REF_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidChanNum;                                /* ��ЧƵ����� */
    VOS_UINT16                          auhwTxChan[UCOM_NV_G_TX_REF_CHAN_NUM_MAX];      /* �ο�Ƶ���б� */
}UCOM_NV_TX_CAL_CHAN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RAMP_INDEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampIndex[UCOM_NV_G_PCL_NUM];
}UCOM_NV_GSM_RAMP_INDEX_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_RAMP_INDEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampIndex[UCOM_NV_G_PCL_NUM];
}UCOM_NV_EDGE_RAMP_INDEX_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RAMP_COEFF_STRU
 Э����  :
 �ṹ˵��  : GSM/EDGE���������±�NV�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwRampUp[UCOM_NV_G_RAMP_COEF_NUM];    /* ���±� */
    VOS_UINT16                          auhwRampDown[UCOM_NV_G_RAMP_COEF_NUM];  /* ���±� */
}UCOM_NV_GSM_RAMP_COEFF_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RAMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM����ϵ���ṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_RAMP_COEFF_STRU         astRampCoeff[UCOM_NV_G_RAMP_PWR_LEVEL_NUM];     /* [������10dBm,20dBm����Ϊ3������] */
}UCOM_NV_GSM_RAMP_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_RAMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EDGE����ϵ���ṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_RAMP_COEFF_STRU         astRampCoeff[UCOM_NV_G_RAMP_PWR_LEVEL_NUM];     /* [������10dBm,20dBm����Ϊ3������] */
}UCOM_NV_EDGE_RAMP_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ע���ѹ�ͷ��书�ʵĶ�Ӧ��ϵ */
    VOS_UINT16                          auhwTxPower[UCOM_NV_G_TX_PWR_CONT_NUM];         /* ��ҪУ���ķ��书�� */
    VOS_UINT16                          auhwContVolt[UCOM_NV_G_TX_PWR_CONT_NUM];        /* ��ҪУ���ķ��书�ʶ�Ӧ�Ŀ��Ƶ�ѹ */
}UCOM_NV_GSM_PA_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

/* ����RF��8PSKͬ��ʹ�õ�ѹ�ֿ��� */
typedef struct
{
    VOS_UINT16                          auhwContVolt[UCOM_NV_G_TX_8PSK_PWR_CONT_NUM];   /* ��ҪУ���ķ��书�ʶ�Ӧ�Ŀ��Ƶ�ѹ */
    VOS_UINT16                          auhwTxPower[UCOM_NV_G_TX_8PSK_PWR_CONT_NUM];    /* ��ҪУ���ķ��书�� */
}UCOM_NV_EDGE_PA_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwGsmMaxTxVolt;
    VOS_UINT16                          uhwGsmMaxTxPower;
}UCOM_NV_GSM_MAX_TX_VOLT_POWER;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_TIMING_CTRL_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTimingCtrl;
}UCOM_NV_G_TIMING_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_RAMP_POINTS_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���µ����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRampPoints;                          /* ���µ��� */
}UCOM_NV_G_RAMP_POINTS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_PREMOD_SYMBOL_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ԥ���Ʒ��Žṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPreModSymbol;                        /* Ԥ���Ʒ��� */
}UCOM_NV_G_PREMOD_SYMBOL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_TX_BURST_OFFSET_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : burset offset�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxBurstOffset;                       /* GSM burst offset */
}UCOM_NV_G_TX_BURST_OFFSET_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_TX_PA_LENGTH_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA��������ѹ�ĳ��Ƚṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxPaLength;                          /* PA��������ѹ�ĳ��ȣ���λΪQb */
}UCOM_NV_G_TX_PA_LENGTH_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_PA_PRECHG_VOLT_CTRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA��������ѹ�ĳ��Ƚṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPaPrechgVolt;                        /*Range:[0,1023]*//* У׼���Ԥ���ѹ */
}UCOM_NV_G_PA_PRECHG_VOLT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_PA_FACTORY_PRECHARGE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwInit;
    VOS_INT16                           shwDelta;
}UCOM_NV_G_PA_FACTORY_PRECHARGE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RX_IP2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :I��Qͨ��ֱ����ΪNV����ͨ�õ�I��Qͨ��ƫ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIReg;                                /* I·�Ĵ���ȡֵ��ƴ�ӷ�ʽ = SN[0]+DATA[6:0] */
    VOS_INT16                           shwQReg;                                /* Q·�Ĵ���ȡֵ��ƴ�ӷ�ʽ = SN[0]+DATA[6:0] */
}UCOM_NV_RX_IP2_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_IP2_CAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :5.2 ÿ��BAND�ڸ��е�Ƶ���£���I��Q·�ĵ�·��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 astRxIp2Cal[3];
}UCOM_NV_GSM_RX_IP2_CAL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_AGC_FREQ_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :5.4 ��AGC������ͳһ��Ƶ������Ƶ�㲻ͬ�����������仯
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcFreqComp[UCOM_NV_G_RX_CHAN_COMP_NUM];  /*Rang:[-64,64]*//* һ��Ƶ����16��Ƶ�� */
}UCOM_NV_GSM_RX_AGC_FREQ_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_APC_RF_ATTEN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.1 RFоƬ�Ի����źŵ�˥������������RFоƬ�Ĵ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxApcRfAtten[UCOM_NV_G_TX_ATTEN_NUM];
}UCOM_NV_EDGE_TX_APC_RF_ATTEN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_APC_DBB_ATTEN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.1 DBBоƬ�Ի����źŵĲ�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwEdgeTxApcDbbAtten[UCOM_NV_G_TX_ATTEN_NUM];
}UCOM_NV_EDGE_TX_APC_DBB_ATTEN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_VBIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.3 �ڲ�ͬ���ʵȼ��£���ΪPA�����ѹ(����ƫ�õ�ѹ)�����½�������͵�ѹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwPaVbias[UCOM_NV_G_PCL_NUM];     /* 32��DA�任ǰ��ֵ */
}UCOM_NV_GSM_PA_VBIAS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_PA_VBIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.3 �ڲ�ͬ���ʵȼ��£���ΪPA�����ѹ(����ƫ�õ�ѹ)�����½�������͵�ѹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwPaVbias[UCOM_NV_G_PCL_NUM];     /* 32��DA�任ǰ��ֵ */
}UCOM_NV_EDGE_PA_VBIAS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_VBIAS_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.3 �ڲ�ͬ���ʵȼ��£���ΪPA�����ѹ(����ƫ�õ�ѹ)�½���������PA����仯�Ĵ�С��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           auhwPaVccVbiasComp[UCOM_NV_G_PCL_NUM];  /* 32�����ʲ���ֵ */
}UCOM_NV_GSM_PA_VCC_VBIAS_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_PA_VBIAS_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :6.3 �ڲ�ͬ���ʵȼ��£���ΪPA�����ѹ(����ƫ�õ�ѹ)�½���������PA����仯�Ĵ�С��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           auhwPaVccVbiasComp[UCOM_NV_G_PCL_NUM];  /* 32�����ʲ���ֵ */
}UCOM_NV_EDGE_PA_VCC_VBIAS_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GMSK(����PA) TX������¶ȱ仯�Ĳ���
*****************************************************************************/
typedef struct
{
    /* �¶ȷ�Χ��ȡֵȡ����UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwGsmTxTempComp[UCOM_NV_G_TEMP_LEVEL_NUM];   /*Range:[-100,100]*/
}UCOM_NV_GSM_TX_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.7 8PSK TX������¶ȱ仯�Ĳ���
*****************************************************************************/
typedef struct
{
    /* �¶ȷ�Χ��ȡֵȡ����UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwEdgeTxTempComp[UCOM_NV_G_TEMP_LEVEL_NUM];   /*Range:[-100,100]*/
}UCOM_NV_EDGE_TX_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ҪУ׼��GSM��Ƶ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                     /*Range:[0,16]*/
    VOS_UINT16                          auhwGsmRxCalChan[UCOM_NV_G_RX_CHAN_COMP_NUM];
}UCOM_NV_GSM_RX_CAL_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_AGC_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :5.3 AGCÿ��״̬������ֵ���ܹ��ֳ�8��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGain[UCOM_NV_G_CHAN_GAIN_MAX_NUM];
}UCOM_NV_GSM_RX_AGC_GAIN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_ EDGE_TX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾÿ����RF Gain��Ӧ���¶Ȳ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp10th[UCOM_NV_EDGE_TX_TEMP_COMP_NUM];      /* ��ʾĳһ��RF Gain��16�������¶��µ��¶Ȳ���ֵ����λΪ0.1dB */
}UCOM_NV_EDGE_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_RF_GAIN_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾ15��RF Gain��Ӧ���¶Ȳ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;
    UCOM_NV_EDGE_TEMP_COMP_STRU         astTempComp[UCOM_NV_EDGE_TX_RF_GAIN_CTRL_NUM];      /* ��ʾ15��RF Gain��16�������¶��µ��¶Ȳ���ֵ */
}UCOM_NV_EDGE_RF_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_VCC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ڲ�ͬ���ʵȼ��£�GSM��Ӧ��VCC��ѹ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmPaVcc[UCOM_NV_G_PCL_NUM];        /* 32��DA�任ǰ��ֵ */
}UCOM_NV_GSM_PA_VCC_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_PA_VCC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ڲ�ͬ���ʵȼ��£�EDGE��Ӧ��VCC��ѹ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgePaVcc[UCOM_NV_G_PCL_NUM];       /* 32��DA�任ǰ��ֵ */
}UCOM_NV_EDGE_PA_VCC_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : close vcc control
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               stClosePaVccMipiCmd;                    /* �ر�PaVcc��mipiָ��֡ */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stClosePaVccMipiData;                   /* �ر�PaVcc��Mipi����֡ */
}UCOM_NV_GSM_CLOSE_MIPI_PA_VCC_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DEV_AVOID_GSM_SLOT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GPS����GSMʱ϶
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPowerThreshold;                      /* �������ޣ����ڸ�����ʱ��������ģʽ����λΪ0.1dbm */
    VOS_UINT16                          uhwBandMask;                            /* ���ڱ��õ�Ƶ�����룬BIT0/1/2/3��Ӧ850/900/1800/1900M */
    VOS_UINT32                          uwIoMask;                               /* ���ڱ��õĹܽ� */
}UCOM_NV_DEV_AVOID_GSM_SLOT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_REDUCE_CURRENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwReduceCurrentEn;                     /* ��������ʹ�� */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16       enCtrlMode;                             /* ���Ʒ�ʽMIPI��GPIO */
    VOS_UINT32                          uwGpioMask;                             /* ��������ʹ�õĹܽ� */
    UCOM_NV_MIPI_CMD_STRU               stPmuMipiCmd;                           /* ����������Ӧ��PMU��ַ */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stDefaultMipiData;                      /* ȱʡʱ�ĵ���ֵ(��һ��ʱ϶) */
    UCOM_NV_MIPI_BYTE_DATA_STRU         stLimitMipiData;                        /* ����ʱ������ֵ(�ǵ�һ��ʱ϶) */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_GSM_REDUCE_CURRENT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_GSM_TX_APC_CAL_TEMP
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Gsm��APCУ׼�¶�
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGsmTxApcCalTemp;                 /*Range:[-300,1350]*/
}UCOM_GSM_TX_APC_CAL_TEMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_EDGE_TX_APC_CAL_TEMP
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Edge��APCУ׼�¶�
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwEdgeTxApcCalTemp;                /*Range:[-300,1350]*/
}UCOM_EDGE_TX_APC_CAL_TEMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_START_BYPASS_THRESHOLD
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Gģ��Bypass����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmStartBypassThreshold;
}UCOM_NV_GSM_START_BYPASS_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_POWER
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ���ķ��书��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxPower[UCOM_NV_G_TX_PWR_CONT_NUM];  /*Range:[-400,400]*//* ��ҪУ���ķ��书�� */
}UCOM_NV_GSM_TX_POWER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_POWER
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ���ķ��书�ʶ�Ӧ�Ŀ��Ƶ�ѹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmContVolt[UCOM_NV_G_TX_PWR_CONT_NUM]; /*Range:[0,1023]*//* ��ҪУ���ķ��书�ʶ�Ӧ�Ŀ��Ƶ�ѹ */
}UCOM_NV_GSM_CONT_VOLT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_POWER
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ͬƵ��ķ��书�ʵĲ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxFreqComp[UCOM_NV_G_TX_CHAN_COMP_NUM];  /*Range:[-100,100]*//* [Ƶ��][��ͬƵ��ķ��书�ʵĲ���ֵ] ����λ0.1dBm*/
}UCOM_NV_GSM_TX_FREQ_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_FREQ_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EdgeУ׼���书�ʵĲ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxFreqComp[UCOM_NV_G_TX_CHAN_COMP_NUM];  /*Range:[-100,100]*//* [Ƶ��][��ͬƵ��ķ��书�ʵĲ���ֵ] ����λ0.1dBm*/
}UCOM_NV_EDGE_TX_FREQ_COMP_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_TX_APC_DBB_ATTEN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : gsm linear pa apc dbb atten
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmLinearPaTxApcDbbAtten[UCOM_NV_G_TX_ATTEN_NUM];   /*Range:[-40,10]*//* gsm linear pa apc dbb atten */
}UCOM_NV_GSM_LINEAR_PA_TX_APC_DBB_ATTEN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_RF_ATTEN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF˥��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmTxRfAtten;   /* RF˥�� */
}UCOM_NV_GSM_TX_RF_ATTEN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_POWER_LEVEL
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 4Ƶ�ι��ʵȼ���dBm��ӳ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmTxPowerLevel[UCOM_NV_G_PCL_NUM]; /* 4Ƶ�ι��ʵȼ���dBm��ӳ��� */
}UCOM_NV_GSM_TX_POWER_LEVEL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_MAX_POWER_REDUCTION
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM����书�ʻ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmMaxPowerReduction[UCOM_NV_G_TX_SLOT_MAX_NUM];
}UCOM_NV_GSM_MAX_POWER_REDUCTION_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_WIRELESS_MAX_POWER
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM��������书��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmWirelessMaxPower[UCOM_NV_G_TX_SLOT_MAX_NUM]; /* ���� *//* 4Ƶ��GMSK�տڷ���ʱ�Ĺ���˥�� */
}UCOM_NV_GSM_WIRELESS_MAX_POWER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_SAR_BACK_OFF_POWER
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM�¸�ʱ϶SAR����ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwGsmSarBackoffPower[UCOM_NV_SAR_BACKOFF_NUM][UCOM_NV_SAR_MODEM_SCENE_NUM];
}UCOM_NV_GSM_SAR_BACK_OFF_POWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_PA_GAIN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ͳPA������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEdgeTxPaGain;                        /* ��ͳPA������ */
}UCOM_NV_EDGE_TX_PA_GAIN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_APC_RF_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GMSK(����PA)��APC RF������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmLinearPaApcRfCtrl[UCOM_NV_G_TX_ATTEN_NUM];    /* apc rf ctrl */
}UCOM_NV_GSM_LINEAR_PA_APC_RF_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_APC_RF_CTRL
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EDGE��APC RF������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxApcRfCtrl[UCOM_NV_G_TX_ATTEN_NUM];    /* apc rf ctrl */
}UCOM_NV_EDGE_TX_APC_RF_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_RF_GAIN_STATE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GMSK(����PA)��APC DBB˥��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwGsmLinearPaRfGainStateIndex[UCOM_NV_G_TX_ATTEN_NUM]; /* rf gain ���� */
}UCOM_NV_GSM_LINEAR_PA_RF_GAIN_STATE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_NONLINEAR_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GMSK(����PA)��APC DBB˥��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwComp[UCOM_NV_G_PCL_NUM];
}UCOM_NV_GSM_LINEAR_PA_NONLINEAR_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_LINEAR_PA_NONLINEAR_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EDGE(����PA)��APC DBB˥��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwComp[UCOM_NV_G_PCL_NUM];
}UCOM_NV_EDGE_LINEAR_PA_NONLINEAR_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_TX_RF_GAIN_STATE_INDEX
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EDGE��APC DBB˥��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwEdgeTxRfGainStateIndex[UCOM_NV_G_TX_ATTEN_NUM]; /* rf gain ���� */
}UCOM_NV_EDGE_TX_RF_GAIN_STATE_INDEX_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_RSSI_ARITHMETIC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Gģͨ���̶�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRssiArithmeticPara;
}UCOM_NV_G_RSSI_ARITHMETIC_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_RX_PLL_ADVANCE_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : rx pll��ǰ��ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxPllAdvanceTiming;
}UCOM_NV_G_RX_PLL_ADVANCE_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_AFC_FE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwAfcFeDelayFn;                        /* FE�ӳ�֡�� */
    VOS_UINT16                          uhwAfcFePowerDis;                       /*  */
    VOS_UINT16                          uhwAfcFeDchFcut0;                       /*  */
    VOS_UINT16                          uhwAfcFeDchFcut1;                       /*  */
}UCOM_NV_GSM_AFC_FE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_ADJ_CHAN_INTERFERE_EN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ����ʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAdjChanInterfereEn;                  /* ��Ƶ����ʹ�� */
}UCOM_NV_G_ADJ_CHAN_INTERFERE_EN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_LS_DCR_EN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ls dcrʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLsDcrEn;                             /* ls dcrʹ�� */
}UCOM_NV_G_LS_DCR_EN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_LINEAR_PA_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LinearPAʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLinearPaEnable;                      /* linear Paʹ�� */
}UCOM_NV_G_LINEAR_PA_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_LINEAR_PA_GAIN_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PA�����������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwWord[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
}UCOM_NV_GSM_LINEAR_PA_GAIN_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_APT_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LinearPAʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmAptEnable;                        /* 2G APTʹ�ܱ�־ */
}UCOM_NV_G_APT_ENABLE_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_SPUR_ACPR_OPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM SPUR ACPR�Ż�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwGsmSpurAcprOpt;                      /* 2G GSM SPUR �Ż� */
}UCOM_NV_GSM_SPUR_ACPR_OPT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_BY_PASS_GPIO_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Bypass��ͨʱ����GPIO�ڵ�bitλ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwBypassGpioMask;                       /* Bypass��ͨʱ����GPIO�ڵ�bitλ */
}UCOM_NV_G_BY_PASS_GPIO_MASK_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��PaVcc��mipiָ��֡
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               stPaVccMipiCmdFrame;                    /* ��PaVcc��mipiָ��֡ */
    VOS_UINT16                          uhwMipiMasterSel;
}UCOM_NV_G_PA_VCC_MIPI_CMD_FRAME_STRU;



/*****************************************************************************
 ö����    : UCOM_NV_GSM_RX_AGC_CTRL_STRU
 Э����  :
 ö��˵��  : 5.3G����AGC���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aunRxAgcCtrl[UCOM_NV_G_AGC_LEVEL_MAX_NUM];
}UCOM_NV_GSM_RX_AGC_CTRL_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU
 Э����  :
 ö��˵��  : AGC�����л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIncDelay;                                /* �л����� */
    VOS_INT16                           ashwDec[UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM];  /* �л����� */
}UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_GSM_AGC_FASTMEAS_THRESHOLD_STRU
 Э����  :
 ö��˵��  : ���ٲ���AGC�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwInitAgc;                                 /* ���ٲ�����ʼ��λ */
    VOS_INT16                           ashwDec[UCOM_NV_G_GAIN_THRESHOLD_MAX_NUM];  /* �л����� */
}UCOM_NV_GSM_AGC_FASTMEAS_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_ACPR_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTempThreshold;                       /* �¶����ޣ���λΪ�� */
    VOS_INT16                           shwPowerComp;                           /* ���ʲ�������λΪ0.1dbm */
}UCOM_NV_GSM_ACPR_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_EDGE_RF_TX_BIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwBiasHighTemp;                       /* �¶����ޣ���λΪ�� */
    VOS_INT16                           shwBiasRoomTemp;                           /* ���ʲ�������λΪ0.1dbm */
}UCOM_NV_EDGE_RF_TX_BIAS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_DCR_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :DCR ��ҪУ׼��GSM��Ƶ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uhwValidDcrChanNum;
    VOS_UINT16                          auhwGsmRxCalChan[ UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];
}UCOM_NV_GSM_RX_DCR_CHAN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM DC Offsetֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitDcoci;                           /* ��ʼֵ,RFIC����ֵΪ0x80��Ӧ��I·DCֵ */
    VOS_INT16                           shwInitDcocq;                           /* ��ʼֵ,RFIC����ֵΪ0x80��Ӧ��Q·DCֵ */
    VOS_INT16                           shwRfDci;                               /* У׼��,RFIC I·DC����ֵ */
    VOS_INT16                           shwRfDcq;                               /* У׼��,RFIC Q·DC����ֵ */
    VOS_INT16                           shwRemainDcoci;                         /* У׼��,I·����DCֵ */
    VOS_INT16                           shwRemainDcocq;                         /* У׼��,Q·����DCֵ */
}UCOM_NV_GSM_DC_OFFSET_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM DC Offsetֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;
    UCOM_NV_GSM_DC_OFFSET_STRU          astGain0DcOffset[ UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];
}UCOM_NV_GSM_RX_DC_OFFSET_GAIN0_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_DC_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM DC Offsetֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_DC_OFFSET_STRU           astGain0[UCOM_G_RX_GAIN0_DCR_CHAN_NUM ];             /* ��ƵGain0��λ��DCRУ׼��� */
    UCOM_NV_GSM_DC_OFFSET_STRU           astOtherGain[UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM];  /*��Ƶ������λDCRУ׼���:UCOM_NV_G_AGC_LEVEL_MAX_NUM -1 */
    UCOM_NV_GSM_DC_OFFSET_STRU           astCrossBandGain0[UCOM_G_RX_GAIN0_DCR_CHAN_NUM];     /* ��ƵGain0��λ��DCRУ׼��� */
    UCOM_NV_GSM_DC_OFFSET_STRU           astCrossBandOtherGain[UCOM_G_RX_OTHER_GAIN_DCR_CHAN_NUM]; /*��Ƶ������λDCRУ׼���:UCOM_NV_G_AGC_LEVEL_MAX_NUM -1 */
}UCOM_NV_GSM_RX_DC_OFFSET_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RF_GPIO_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF ���ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwGsmAntMask;                           /* ��ֵ��ʾW��BAND����Gģ��BAND��ʶ */
    VOS_UINT32                          uwPaEnMask;                             /* RF���ڵ�ͨ�� */
    VOS_UINT32                          uwPaBandMask;                           /* ����1�Ŀ���ֵ */
    VOS_UINT32                          uwPaModeMask;                           /* ����2�Ŀ���ֵ */
}UCOM_NV_GSM_RF_GPIO_MASK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TUNER_GPIO_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF TUNER GPIO���ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTunerMask;                            /* Tuner�����룬��TUNERʹ��BIT2,BIt3��Ϊ�߿أ�������ΪBIT2|BIT3 */
    VOS_UINT32                          uwReserved;                             /* ����λ */
}UCOM_NV_GSM_TUNER_GPIO_MASK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_NCELL_TASK_RANK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����������ȼ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwImmedExeRankRxlevThd;                /* ͻȻ��ǿ����Rxlev�о����� 10  */
    VOS_INT16                           shwLowRxlevRankRxlevThd;                /* ��Rxlev����Rxlev�о����� 108 */
    VOS_UINT16                          uhwBchTimerOutCntPeriod;                /* ����̬��ʱ����ʱ������������ 12 */
    VOS_UINT16                          uhwBchSBSuccRankLockLen;                /* ����̬SB�ɹ����ȼ�����ʱ�� 6 */
    VOS_UINT16                          uhwBchBlackListRankLockLen;             /* ����̬���������ȼ�����ʱ�� 6 */
    VOS_UINT16                          uhwDchTimerOutCntPeriod;                /* ר��̬��ʱ����ʱ������������ 12 */
    VOS_UINT16                          uhwDchSBSuccRankLockLen;                /* ר��̬SB�ɹ����ȼ�����ʱ�� 2 */
    VOS_UINT16                          uhwDchBlackListRankLockLen;             /* ר��̬���������ȼ�����ʱ�� 2 */
}UCOM_NV_GSM_NCELL_TASK_RANK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϵͳ����ֹ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWphyGapNum;                          /* WPHY�Ĺ��ĸ��� */
    VOS_UINT16                          uhwLphyGapNum;                          /* LPHY�Ĺ��ĸ��� */
    VOS_UINT16                          uhwTphyGapNum;                          /* TPHY�Ĺ��ĸ��� */
    VOS_UINT16                          uhwRsv;                                 /* rsv */
}UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ר��̬��ϵͳ�������ȼ����ֹ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwHighestRank;                         /* ר��̬��ϵͳ����������ȼ�Ĭ��ֵ5 */
    VOS_UINT16                          uhwLowestRank;                          /* ר��̬��ϵͳ����������ȼ�Ĭ��ֵ205 */
    VOS_UINT16                          uhwRankStep;                            /* ר��̬��ϵͳ�������ȼ��仯����Ĭ��ֵ30*/
    VOS_UINT16                          uhwOverMaxGapRank;                      /* ר��̬��ϵͳ�����Ѿ�����Ĺ�����Ŀ�������ֵ֮������ȼ�Ĭ��ֵ205 */
    UCOM_NV_GSM_INTERRAT_GAP_NUM_STRU   stMaxGapNum;                            /* ��ϵͳ�������ɷ��乵��ĿĬ��ֵ1�� */

}UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϵͳ�������ȼ��ṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stBchInterratRank;                  /* ����̬��ϵͳ���ȼ�115��115��0��115���ֵĹ�����Ϊ1 */
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stCsDchInterratRank;                /* cs ר��̬��ϵͳ��������ȼ��ṹ5,205,30,205,����5���� */
    UCOM_NV_GSM_INTERRAT_RANK_AND_GAP_STRU  stPsDchInterratRank;                /* ps ר��̬��ϵͳ��������ȼ��ṹ5,205,30,205,����12���� */
}UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_NCELL_SHEDULE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������Ȳ����ṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_NCELL_TASK_RANK_STRU        stNcellTaskRank;                    /* �����������ȼ� */
    UCOM_NV_GSM_INTERRAT_TASK_RANK_STRU     stInterratTaskRank;                 /* ��ϵͳ�������ȼ� */
}UCOM_NV_GSM_NCELL_SCHEDULE_CFG_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_MEA_RSSI_TO_AGC_GAIN_THD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������Ȳ����ṹ
��ʼ���ö��׿��ٲ���ģʽ�������β���ֵ<-56dBm���´����õ�λA���ֲ���ģʽ�������´����õ�λB���ֲ���ģʽ��
�����ǰ�ǵ�λA���ֲ���ģʽ���ҵ��β���ֵ>-53dBm���´����õ�λB���ֲ���ģʽ��
�����ǰ�ǵ�λB���ֲ���ģʽ���ҵ��β���ֵ<-59dBm���´����õ�λA���ֲ���ģʽ

*****************************************************************************/
typedef struct
{
    VOS_INT16                       shwThreeModeToAorBGainThd;                  /* ��ʼ���ö��׿��ٲ���ģʽ�������β���ֵ<-56dBm���´����õ�λA���ֲ���ģʽ�������´����õ�λB���ֲ���ģʽ */
    VOS_INT16                       shwAGainToBGainThd;                         /* ��ǰ��A�� ���β���ֵ>-53dBm���´����õ�λB���ֲ���ģʽ */
    VOS_INT16                       shwBGainToAGainThd;                         /* ��ǰ�ǵ�λB���ֲ���ģʽ���ҵ��β���ֵ<-59dBm���´����õ�λA���ֲ���ģʽ */
    VOS_UINT16                      uhwRssiCompensation;                        /* ���ֲ�����RSSI�Ĳ�������ֵ��Ĭ��0.75dB */
}UCOM_NV_GSM_MEA_RSSI_TO_AGC_GAIN_THD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DSDA_POWER_LIMIT_STRU
 �ṹ˵��  : ˫�����书������NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwPowerLmtEnable;                          /* ���ƹ��ʿ��� */
    VOS_UINT16                      auhwPowerLmtLow[UCOM_NV_G_HIGH_LOW_BUTT];   /* ���ƹ�����Сֵ����λ0.1dBm */
    VOS_UINT16                      auhwPowerLmtHigh[UCOM_NV_G_HIGH_LOW_BUTT];  /* ���ƹ�����ֵ̬����λ0.1dBm */
    VOS_UINT16                      auhwPowerLmtMax[UCOM_NV_G_HIGH_LOW_BUTT];   /* ���ƹ������ֵ����λ0.1dBm */
}UCOM_NV_GSM_DSDA_POWER_LIMIT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RAMP_DAC_REV_STRU
 �ṹ˵��  : ˫�����书������NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwGsmRampDacRev;                           /* gsm����dac�Ƿ񽻲�,0:������,1:���� */
}UCOM_NV_GSM_RAMP_DAC_REV_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 �ṹ˵��  : ���ߵ�г�Ŀ��ƽṹ��,MIPI��tuner,���Ǽ��ݶ����ͺţ��ṩ���6��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* Ӳ���Ƿ�֧�����ߵ�г��0��֧�֣�1֧�� */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* ���ߵ�г��ͨ��MIPI���ƻ���GPIO,0��ʾGPIO,1��ʾMIPI */
    UCOM_NV_GSM_TUNER_GPIO_MASK_STRU        stTunerGpioMask;
    UCOM_NV_MIPI_COMM_STRU                  stTunerActiveReg;                   /* tuner�Ĺ�����ʼ�������֣�����һЩ�Ĵ���ֻ��Ҫģʽ��������һ�� */
    UCOM_NV_MIPI_COMM_STRU                  stTunerIdleReg;                     /* ����tunerΪIDLE̬��͹���̬�Ŀ����� */
} UCOM_NV_G_ANT_TUNER_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi lna ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                    astLnaMipiCmd[UCOM_NV_G_LNA_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU              astLnaMipiData[UCOM_NV_G_LNA_MIPI_DATA_MAX_NUM];
}UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_LNA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EXT LNA INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwGpioEnable;                              /* GPIOʹ���ź� */
    VOS_UINT32                               uwLnaGpioNumber;                           /* ֧�ֵĵ�λ��*/
    VOS_UINT32                               auwLnaGpio[UCOM_NV_G_LNA_GPIO_STEP_NUM];   /* 4��LNA GPIO������ */
    VOS_UINT32                               uwLnaGpioMask;                             /* ʹ�õ�LNA GPIO������ */
    VOS_UINT32                               uwMipiEnable;                              /* MIPIʹ���ź�*/
    VOS_UINT32                               uwLnaMipiNumber;                           /* ֧�ֵĵ�λ��*/
    UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU       astLnaMipi[UCOM_NV_G_LNA_MIPI_STEP_NUM];   /* MIPI LNA ���� */
    UCOM_NV_GSM_EXT_LNA_MIPI_WORD_STRU       stLnaOff;                                  /* LNA �ر�����*/
    VOS_UINT32                               auwGainIndex[UCOM_NV_G_LNA_GAIN_INDEX_NUM];/* BLOCK��AGC��λ��lna��������*/
}UCOM_NV_GSM_EXT_LNA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_LNA_COMMON_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EXT LNA COMMON INFO
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_EXT_LNA_INFO_STRU              stMainLnaInfo;       /* ����mipi lna ��Ϣ */
    UCOM_NV_GSM_EXT_LNA_INFO_STRU              stDivLnaInfo;        /* �ּ�mipi lna ��Ϣ  */
}UCOM_NV_GSM_EXT_LNA_COMMON_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_LNA_AGC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LNA��AGC������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_RX_AGC_CTRL_STRU                stAgcCtrlWord;          /* LNA ON��ʱ��ʹ�õ�AGC��������� */
}UCOM_NV_GSM_RX_AGC_CTRL_EXT_LNA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_LNA_AGC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LNA��AGC������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_AGC_SWITCH_THRESHOLD_STRU        stAgcThresholdAb; /* LNA ON��ʱ��ʹ�õ�AGC�л����� */
}UCOM_NV_GSM_RX_AGC_SWITCH_THRD_EXT_LNA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ANT_TUNER_CTRL_PARA_STRU
 �ṹ˵��  : ���ߵ�г������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCodeSearchStep;                  /* ��гʱ������������ */
    VOS_UINT16                              uhwBypassMaxCode;                   /* Bypassʱ��������֣���RF1108Ϊ0x40 */
    VOS_UINT16                              uhwBypassMinCode;                   /* Bypassʱ����С���֣���RF1108Ϊ0x5F */
    VOS_UINT16                              uhwUpperCode;                       /* ���ߵ�г�������ޣ���RF1108Ϊ0 */
    VOS_UINT16                              uhwLowerCode;                       /* ���ߵ�г�������ޣ���RF1108Ϊ31 */
    VOS_UINT16                              auhwReserve[3];                     /* ��ȷ�����ָ�ʽ�ʹ�С���ȱ��� */
} UCOM_NV_W_ANT_TUNER_CODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU
 �ṹ˵��  : �ջ�tuner�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwBandSupport;                      /* ��ӦbitΪ1��ʾ���band֧�ֶ�̬���ߵ�г,����֧�� */
    VOS_UINT32                              uwBandExten;                        /* �Ժ�band ID���ܳ���32 */
    VOS_UINT16                              uhwActiveTime;                      /* ���ߵ�г������ǰ֡ͷ�������������д򿪺�WBBPÿ����֡ͷ��ǰcpu_tx_sw_active_time�������ã���λΪchip */
    VOS_UINT16                              uhwSampleTime;                      /* ���ߵ�гƽ��������,Ĭ������Ϊ4 */
    VOS_UINT16                              uhwDelayFrame;                      /* ���һ�ֵ�г��ĵȴ�ʱ�䣬��λ֡ */
    VOS_UINT16                              uhwEchoLossThreshold;               /* ���ߵ�г�ز��������,����0.1dBm */
    VOS_UINT32                              uwForWardGpioWord;                  /* פ�����ǰ������ */
    VOS_UINT32                              uwReverseGpioWord;                  /* פ����ⷴ������ */
    UCOM_NV_MIPI_CMD_STRU                   stTunerMipiCmd;                     /* MIPI������ */
    VOS_UINT16                              uhwReserved;                        /* ���� */
    UCOM_NV_W_ANT_TUNER_CODE_STRU           stAntTunerCode;                     /* ���ߵ�г������Ϣ */
} UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_TUNER_CTRL_INFO_STRU
 �ṹ˵��  : ���ߵ�г�Ŀ��ƽṹ��,MIPI��tuner,���Ǽ��ݶ����ͺţ��ṩ���6��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TUNER_SUPPORT_MODE_ENUM_UINT16  enAntTunerMode;                     /* 0:Ӳ����֧�֣�1:֧�ֿ�����2:֧��AP+Sensor, 3:֧�ֶ�̬��г */
    UCOM_NV_RFFE_CTRL_ENUM_UINT16           enAntTunerCtrlType;                 /* ���ߵ�г��ͨ��MIPI���ƻ���GPIO,0��ʾGPIO,1��ʾMIPI */
    UCOM_NV_MIPI_COMM_STRU                  stTunerActiveReg;                   /* tuner�Ĺ�����ʼ�������֣�����һЩ�Ĵ���ֻ��Ҫģʽ��������һ�� */
    UCOM_NV_MIPI_COMM_STRU                  stTunerIdleReg;                     /* ����tunerΪIDLE̬��͹���̬�Ŀ����� */
    UCOM_NV_W_CLOSE_LOOP_TUNER_PARA_STRU    stCloseLoopTunerCtrl;               /* �ջ�tuner���� */
} UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU;

typedef UCOM_NV_W_ANT_TUNER_CTRL_INFO_STRU UCOM_NV_CDMA_ANT_TUNER_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_DIV_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ƿ�֧�ַּ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwWBand;
    VOS_UINT32          uwWbandExtRsv;
}UCOM_NV_W_RF_DIV_BAND_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF ���ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwBand;                                /* ��ֵ��ʾW��BAND����Gģ��BAND��ʶ */
    VOS_UINT16                          uhwRfChannel;                           /* RF���ڵ�ͨ�� */
    VOS_UINT32                          uwAntSwitch;                            /* ����1�Ŀ���ֵ */
    VOS_UINT32                          uwOtherSwitch;                          /* �������߿���ֵ */
    VOS_UINT32                          uwPaControlWord;                        /* WģPAʹ�� */
}UCOM_NV_RF_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BAND_RF_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾ֧�ֵ�3G��2GƵ�Ρ�3G�ּ�֧�������ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU              stRxMainRfBandCofig;                    /* ������2G��3G������Ƶ�� */

    UCOM_NV_RF_CONFIG_STRU              stRxDvtyRfBandCofig;                    /* ������2G��3G������Ƶ�� */

    UCOM_NV_RF_CONFIG_STRU              stTxRfBandCofig;                        /* ������2G��3G������Ƶ�� */
}UCOM_NV_W_BAND_RF_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_RF_BAND_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾ֧�ֵ�3G��2GƵ�Ρ�3G�ּ�֧�������ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU              astGsmRxRfBandConfig[UCOM_NV_G_BAND_NUMBER];        /* ������2G RX ����Ƶ�� */

    UCOM_NV_RF_CONFIG_STRU              astGsmTxRfBandConfig[UCOM_NV_G_BAND_NUMBER];        /* ������2G TX Ƶ�� */

    UCOM_NV_W_BAND_RF_CONFIG_STRU       astWcdmaRfBandConfig[UCOM_NV_W_TOTAL_BAND_NUM];     /* ������3G Ƶ�� */
}UCOM_NV_WG_RF_BAND_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_EXT_RF_BAND_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W��չband config
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_BAND_RF_CONFIG_STRU       astWcdmaRfBandConfig[UCOM_NV_W_RF_BAND_CONFIG_NUM];     /* ������3G Ƶ�� */
}UCOM_NV_W_RF_BAND_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_INIT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF��ʼ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwRfAddr;
    VOS_UINT16          uhwRfAddrValue;
}UCOM_NV_RF_INIT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_INIT_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF��ʼ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRfCount;
    UCOM_NV_RF_INIT_INFO_STRU               stConfigInfo[UCOM_NV_RFABB_INIT_REG_NUM];
}UCOM_NV_RF_INIT_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF��ʼ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwRfCount;
    UCOM_NV_RF_INIT_INFO_STRU               stConfigInfo[UCOM_NV_RFABB_INIT_REG_NEW_RAM_NUM];
}UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_PHY_SW_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ǰ�˲����Ե�NV�������ʱ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          stDrxTSysclk;
    VOS_UINT16                          uhwWcdmaIp2DataWidth;       /* W IP2��λ��,0:12bit,1:14bit */
    VOS_UINT16                          uhwReservedWord;            /* ���������Ժ�������չ */
    VOS_UINT32                          uwReservedWords[6];         /* ���������Ժ�������չ */
} UCOM_NV_PHY_SW_CFG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_MMMB_PA_SEL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIPI����NV��,PA����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwWBand;
    VOS_UINT32          uwWbandExtRsv;
    VOS_UINT32          uwGeBand;
}UCOM_NV_WG_MMMB_PA_SEL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_SWITCH_CONTROL_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIPI����NV��,���߿���ģʽ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWcdmaBandMainAnt;                    /* [0]-BAND1;[1]-BAND2;�Դ����� */
    VOS_UINT32                          uwWcdmaBandDvtyAnt;                    /* [0]-BAND1;[1]-BAND2;�Դ����� */
    VOS_UINT32                          uwWbandExtRsv;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwWbandExtRsv2;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwGsmBandRxAnt;                        /* [0]-GSM450;[1]-GSM480;... */
    VOS_UINT32                          uwGsmBandTxAnt;                        /* [0]-GSM450;[1]-GSM480;... */
}UCOM_NV_ANT_SWITCH_CONTROL_MODE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_DRX_RESUME_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WG DRX ˯�߻���ABB��RF�������ȶ�������ָ�ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAbbPwrRsmTime;                        /* ABB AD/DA���ֲ��ֵ�Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwRfPwrRsmTime;                         /* RF ģ�����Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwAntSwitchPwrRsmTime;                  /* ���߿��ص�Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwAbbWpllRsmTime;                       /* ABB WPLL�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwAbbGpllRsmTime;                       /* ABB GPLL�ȶ�ʱ�� ,��λus*/
    VOS_UINT32                          uwBbpPllRsmTime;                        /* SOC BBP PLL�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwPaStarRsmTime;                            /* �����ֶ� */
    VOS_UINT32                          uwSysProtectTime;                       /* ϵͳ�ָ�����ʱ�� */

    VOS_UINT32                          uwTcxoRsmTime;                          /* TCXO�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwDcxoRsmTime;                          /* DCXO�ȶ�ʱ��,��λus */
    VOS_UINT32                          uwSlowToMcpuRsmTime;                    /* ��SLOW��MCPU�ϵ�ָ�ʱ��,��λus */
    VOS_UINT32                          uwWphyRsmTime;                          /* W����㻽�ѻָ�ʱ��,��λus */
    VOS_UINT32                          uwGphyRsmTime;                          /* G����㻽�ѻָ�ʱ��,��λus */
    VOS_UINT32                          uwTaskSwitchTime;                       /* ����ϵͳ�����л�ʱ��,��λus */
    VOS_UINT32                          uwPaPwrRsmTime;                         /* PA��Դ�ȶ�ʱ��,��λus */
}UCOM_NV_WG_DRX_RESUME_TIME_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_DRX_ADVANCE_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WG DRX ��ǰ������,���ݴ�������ȡ��ͬ������.
             �滻����NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMcuTcxoRsumeTime;
    VOS_UINT32                          uwMcuDcxoRsumeTime;
    VOS_UINT32                          uwModemRsumeTime;
    VOS_UINT16                          auhwOamAdvanceTime[2][4];                  /* DSDA �±�0/DSDS 1:OAMģʽ��ǰ��:m0/m1/m2,��λus */
    VOS_UINT16                          auhwGphyAdvanceTime[2][4];                 /* DSDA �±�0/DSDS 1:GSMģʽ��ǰ��:m0/m1/m2,��λus */
    VOS_UINT16                          auhwWphyAdvanceTime[2][4];                 /* DSDA �±�0/DSDS 1:WCDMAģʽ��ǰ��:m0/m1/m2,��λus */
}UCOM_NV_WG_DRX_ADVANCE_TIME_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_SUPPORT_RATMODE_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : modem֧�ֵ�����ģʽ��Ϣ
             bit0:�Ƿ�֧��GSM;
             bit1:�Ƿ�֧��WCDMA;
             bit2:�Ƿ�֧��LTE;
             bit3:�Ƿ�֧��TDS;
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSupportRatMask;                      /* Modem֧�ֵ�����mode��Ϣ */
}UCOM_NV_SUPPORT_RATMODE_MASK_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_PA_DEFAULT_VOLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PAĬ�ϵ�ѹֵ,��ѹ��λ:1mV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaPaVolt;                         /* WCDMA PAĬ�ϵ�ѹ */
    VOS_UINT16                          uhwGsmPaVolt;                           /* GSM PAĬ�ϵ�ѹ */
}UCOM_NV_PA_DEFAULT_VOLT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_ABB_PLL_STABLE_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PLL�ȶ�ʱ��,�ȶ�ʱ�䵥λ:1us
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaPllStableTime;                  /* WCDMA PLL�ȶ�ʱ�� */
    VOS_UINT16                          uhwGsmPllStableTime;                    /* GSM PLL�ȶ�ʱ�� */
}UCOM_NV_WG_ABB_PLL_STABLE_TIME_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RCM_PARA_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM����NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwTimingCalThld;                    /* ʱ��У׼���� */
    VOS_UINT16                              uhwReserved1;
    VOS_UINT16                              uhwReserved2;
    VOS_UINT16                              uhwReserved3;
    VOS_UINT16                              uhwReserved4;
    VOS_UINT16                              uhwReserved5;
}UCOM_NV_RCM_PARA_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : UCOM_NV_RCM_RF_SHARE_CFG_STRU
�ṹ˵��  : UCOM_NV_RCM_RF_SHARE_CFG_STRU��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlag;      /*Range:[0,1]*//* �����Ƿ�֧�ֱ�� */
    VOS_UINT16                          usGSMRFID;          /* GSM����ģʽRFID��Ϣ */
    VOS_UINT16                          usWCDMARFID;        /* WCDMA����ģʽRFID��Ϣ */
    VOS_UINT16                          usTDSRFID;          /* TD-SCDMA����ģʽRFID��Ϣ */
    VOS_UINT16                          usLTERFID;          /* LTE����ģʽRFID��Ϣ */
    VOS_UINT16                          usCDMARFID;         /* CMDA����ģʽRFID��Ϣ */
    VOS_UINT16                          usEVDORFID;         /* CDMA EVDO����ģʽRFID��Ϣ */
    VOS_UINT16                          usReserved;
} UCOM_NV_RCM_RF_SHARE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RCM_TEST_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwRcmTestCtrl;                          /* RCM��������
                                                                                   BIT0��ʾ�ڲ��Կ������Ƿ�ǿ�ƴ�TAS,
                                                                                   BIT1��ʾ����ģʽ�����Ƿ�ǿ�ƴ�TAS */

    VOS_UINT32                          uwResvered;                             /* ���� */
}UCOM_NV_RCM_TEST_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_SVLTE_SUPPORT_FLAG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SVLTE����,�ṹ�μ�SVLTE_SUPPORT_FLAG_STRU,ID=60.�ļ�Ϊ"NasNvInterface.h"
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSvLte;
}UCOM_NV_SVLTE_SUPPORT_FLAG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TAS_FUNC_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM����NV�� uhwTasFuncEnable
             bit0: 0 - TAS Disabled
                   1 - TAS Enabled
             bit1: 0 - MAS Disabled
                   1 - MAS Enabled,����bit0=1ʱ����������1
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTasFuncEnable;                       /* TAS/MAS�����Ƿ���Ч */
}UCOM_NV_TAS_FUNC_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RCM_TAS_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM����NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwTasChoiceData[UCOM_NV_RCM_TAS_TABLE_NUM];    /* TAS�л������ */
    VOS_UINT32                  uwTasScoreData[UCOM_NV_RCM_TAS_TABLE_NUM];      /* TAS״̬�Ʒֱ� */
}UCOM_NV_RCM_TAS_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RCM_TAS_TABLE_TRI_MODEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ͨTAS����NV��
*****************************************************************************/
typedef UCOM_NV_RCM_TAS_TABLE_STRU  UCOM_NV_RCM_TAS_TABLE_TRI_MODEM_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RCM_TAS_CDMA_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM����NV����ڿ�������̬��CDMA�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwCompareNum[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];      /* ��������,����������� */
    VOS_UINT16                          auhwDeltaAveRxAGC[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];   /* ��ֵ����,��λdB */
    VOS_UINT16                          auhwFrozenNum[UCOM_NV_RCM_AGENTC_COMPARE_PHASE_BUTT];       /* ����ʱ�����������ʱ��=num*1X�����ϱ����� */
    VOS_UINT16                          uhwFinalFrozenNum;                                          /* �Ƚ������ӽ׶ζ��������쳣����ʱ����� */
    VOS_UINT16                          uhwSPassThreshold;                                          /* SPass�������� */
    VOS_UINT16                          uhwSFailThreshold;                                          /* SFail�������� */
}UCOM_NV_RCM_TAS_CDMA_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GUPHY_FUNC_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : v7r1c50 �͹��Ŀ��ƽṹ16λ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  CsOnlyAntCtrl           :1;                     /* CS ONLY�طּ����� */
    VOS_UINT16                  ScAbbCtrl               :1;                     /* SC ABB���� */
    VOS_UINT16                  AbbCtrl                 :1;                     /* CS ONLY abb���� */
    VOS_UINT16                  RficRegCtrl             :1;                     /* CS ONLY RF���Ĵ������� */
    VOS_UINT16                  RficVolCtrl             :1;                     /* CS ONLY RF����ѹ���� */
    VOS_UINT16                  GudspPowerDownCtrl      :1;                     /* GU ��ģ�µ���� */
    VOS_UINT16                  SimpleSlotIntCtrl       :1;                     /* W ����ʱ϶���� */
    VOS_UINT16                  LoopRfLowpowerCtrl      :1;                     /* ��������RF�͹��Ŀ��� 1���� 0������Ĭ�ϲ����� */

    VOS_UINT16                  LoopRxAnt2Ctrl          :1;                     /* ��������rx��̬�ּ����� 1���� 0������Ĭ�ϲ����� */
    VOS_UINT16                  PsR99RxAnt2Ctrl         :1;                     /* ps r99 rx�طּ����� DCM����*/
    VOS_UINT16                  PsRxAnt2Ctrl            :1;                     /* ps R99��DPA rx�طּ�����Ϊ1�൱�ڶ�̬�ּ���ش���ȫ���ر� */
    VOS_UINT16                  PsVoltLPCtrl            :1;                     /* PS ��ѹ�͹������Դ������λ, 1�� 0���򿪣�Ĭ�ϴ� */
    VOS_UINT16                  PsCsAntCtrl             :1;                     /* PS CS�����¹طּ����� */
    VOS_UINT16                  reserved                :1;
    VOS_UINT16                  DpaOpenIpc              :1;                     /* dpaҵ����E5776��860��Ʒ��̬��IPC�жϿ��ؿ��ƣ�Ĭ�ϲ��� */
    VOS_UINT16                  GphyCsInterferennceCtrl :1;                     /* GSM CSͬƵ���ŵ��������ܷ�������:1-��ʾ�򿪸ù���,�����ʾ�ر� */
}UCOM_NV_GUPHY_FUNC_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_TEMPPROTECT_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTempTypeId;                          /* 0-13 */
    VOS_UINT16                          uhwCloseAnt2Flag;                       /* �±��Ƿ񿪹طּ� */
    VOS_INT16                           shwCloseAnt2TempThresh;                 /* ���¹رշּ����� */
    VOS_INT16                           shwOpenAnt2TempThresh;                  /* ���´򿪷ּ����� */
    VOS_UINT16                          uhwMaxPowLimitFlag;                     /* �±��Ƿ���������书�� */
    VOS_INT16                           shwMaxPowLimitAlarmThresh;              /* �±���������书��,�������� */
    VOS_INT16                           shwMaxPowLimitResumeThresh;             /* �±���������书��,�ָ����� */
    VOS_INT16                           shwWMaxPowLimitValue;                   /* �±�����W����书�� */
    VOS_INT16                           shwGMaxPowLimitValue;                   /* �±�����G����书�� */
}UCOM_NV_WG_TEMPPROTECT_CTRL_STRU;

/* xiongjiangjiang Edn */

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF RX DELTA GAIN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxChanDelay;
}UCOM_NV_W_RF_TX_CHAN_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ANT_PERFORM_TEST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAntPerformanceTest;
}UCOM_NV_W_ANT_PERFORM_TEST_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_CQI_ANT2_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwCQICtrlFlag;
    VOS_UINT16                          uhwCQIThresh1;                          /* CQI������ */
    VOS_UINT16                          uhwCQIThresh2;                          /* CQI������ */
    VOS_UINT16                          uhwCQITime1;                            /* CQI���ڸ����޹طּ��ӳ�ʱ�� */
    VOS_UINT16                          uhwCQITime2;                            /* CQI���ڵ����޿��ּ��ӳ�ʱ�� */
}UCOM_NV_W_CQI_ANT2_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_UL_RF_GATE0_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwUlRfGate0;
}UCOM_NV_W_UL_RF_GATE0_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_UL_RF_GATE1_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwUlRfGate1;
}UCOM_NV_W_UL_RF_GATE1_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_INIT_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaInitDelay;
}UCOM_NV_W_PA_INIT_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_OFF_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaOffDelay;
}UCOM_NV_W_PA_OFF_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_INIT_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxInitDelay;
}UCOM_NV_W_TX_INIT_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_OFF_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxOffDelay;
}UCOM_NV_W_TX_OFF_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_IDLE_ON_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxIdleOnDelay;
}UCOM_NV_W_TX_IDLE_ON_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_IDLE_OFF_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxIdleOffDelay;
}UCOM_NV_W_TX_IDLE_OFF_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_ABB_INIT_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxAbbInitDelay;
}UCOM_NV_W_TX_ABB_INIT_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_ABB_OFF_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwTxAbbOffDelay;
}UCOM_NV_W_TX_ABB_OFF_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_GAIN_CTRL_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          shwTxGainOpenTime;                      /* ��ǰ������RF�����chip�� */
}UCOM_NV_W_TX_GAIN_CTRL_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ӱ��С���������ڵĲ����ȼ�����
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwClass1Factor;                        /* ������������������������ */
    VOS_UINT16                          uhwClass2Factor;                        /* �����������׼����ֻ�б�Ƶ����Ƶ */
    VOS_UINT16                          uhwClass3Factor;                        /* ֻ����С������ */
    VOS_UINT16                          uhwRsv;
}UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ӱ�������س��ȵĲ����ȼ�����
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwClass1Factor;                        /* ������������������������ */
    VOS_UINT16                          uhwClass2Factor;                        /* �����������׼����ֻ�б�Ƶ����Ƶ */
    VOS_UINT16                          uhwClass3Factor;                        /* ֻ����С������ */
    VOS_UINT16                          uhwRsv;
}UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ǿ����������Ϣ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwIntraStrongCellNum;                  /* ��Ƶǿ�������� */
    VOS_UINT16                          uhwIntraMeasReserveCellNum;             /* ÿ�α�Ƶ����������ǿС������ */
    VOS_UINT16                          uhwInterStrongCellNum;                  /* ��Ƶǿ�������� */
    VOS_UINT16                          uhwInterMeasReserveCellNum;             /* ÿ����Ƶ����������ǿС������ */
}UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_CTRL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwDrxMaxCsPeriodLenth;                 /* DRX̬������С���������� */
    VOS_UINT16                          uhwDrxMinMeasCorrLenth;                 /* DRX̬����С�Ĳ�����س��� */
    VOS_UINT16                          uhwDrxMaxMeasCorrLenth;                 /* DRX̬�����Ĳ�����س��� */
    VOS_UINT16                          uhwDrxMaxCsStep1Lenth;                  /* DRX̬������С������step1���� */
    VOS_UINT16                          uhwDrxMinCsStep1Lenth;                  /* DRX̬����С��С������step1���� */
    VOS_UINT16                          uhwRsv;
    UCOM_NV_W_DRX_CS_PERIOD_MEAS_CLASS_STRU         stDrxCsPeriodMeasClass;         /* Ӱ��С���������ڵĲ����ȼ����� */
    UCOM_NV_W_DRX_MEAS_CORR_LENTH_MEAS_CALSS_STRU   stDrxMeasCorrLenthMeasClass;    /* Ӱ�������س��ȵĲ����ȼ����� */
    UCOM_NV_W_DRX_STRONG_CELL_CTRL_INFO_STRU        stDrxStrongCellCtrlInfo;        /* ǿ����������Ϣ */
}UCOM_NV_W_DRX_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_CQI_CORRECT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCqiCorrectEnable;                     /* CQI��̬����ʹ�ܿ���,0 �رգ�1 �� */
    VOS_UINT32                          uwSblerHighThreshold;                   /* SBLER �߿�������,��λ0.01 */
    VOS_UINT32                          uwSblerLowThreshold;                    /* SBLER �Ϳ�������,��λ0.01 */
    VOS_UINT32                          uwScheduleRateThreshold;                /* �����ʿ�������,��λ0.01 */
}UCOM_NV_W_CQI_CORRECT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PSCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwPschLen;                             /* PSCH��������ɳ��� */
    VOS_UINT16                          uhwPschThd;                             /* PSCH�������������� */
}UCOM_NV_W_PSCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TOTOLPC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwOpenTotolpcFlg;                  /* �Ƿ�����Tot Olpc�㷨��־��Ĭ��ֵ1 */
    VOS_UINT16                              uhwOutageProbability;               /* Totolpc�㷨�еĲ�����Ĭ��ֵ15*/
    VOS_UINT16                              uhwSirErrorStep;                    /* Totolpc�㷨�еĲ�����Ĭ��ֵ1*/
    VOS_UINT16                              uhwCorrectionFactor;                /* Totolpc�㷨�еĲ�����Ĭ��ֵ10*/
    VOS_UINT16                              uhwSirOutageOffset;                 /* Totolpc�㷨�еĲ�����Ĭ��ֵ0*/
    VOS_INT16                               shwOutageIncrementThresUp;          /*TOT OLPC�㷨�еĲ���OutageIncrementThresholdUp��Ĭ��ֵ26*/
    VOS_INT16                               shwOutageIncrementThresDown;        /*TOT OLPC�㷨�еĲ���OutageIncrementThresholdDown��Ĭ��ֵ-19*/
    VOS_INT16                               shwOutagetargetStepUp;              /*TOT OLPC�㷨�еĲ���OutagetargetStepUp��Ĭ��ֵ10*/
    VOS_INT16                               shwOutagetargetStepDown;            /*TOT OLPC�㷨�еĲ���OutagetargetStepDown��Ĭ��ֵ-10*/
    VOS_INT16                               shwReserve;                             /*����λ��Ĭ��ֵ0*/
} UCOM_NV_W_TOTOLPC_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_CPC_DRX_STRU
 Э����  :
 ö��˵��  :CPC DRX��Ŀʹ�õ�NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfWorkMode;                          /* RF����͹���״̬ʱ������Idle̬���ǽ���StandBy̬*/
    VOS_UINT16                          uhwCpcDrxCtrlFlag;                      /* ����CPC DRX��ع��ܿ��صı�־*/
}UCOM_NV_W_CPC_DRX_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :IP2У׼����,�����ּ�����ͬһ���ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIp2TxRefPower;                  /* У׼ʱ����ͨ���Ĺ��ʣ���λΪ0.1dbm */
    VOS_INT16                           shwReserved;                       /* �ݲ�ʹ�ã����� */
}UCOM_NV_W_RX_IP2_CAL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_IQ_MISMATCH_CAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TX IQ MISMATCHУ׼��ʼ���ʺ�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxIqMismatch2RefPower;           /* У׼ʱ����ͨ���Ĺ��ʣ���λΪ0.1dbm */
    VOS_INT16                           shwAmpCorrThreshold;                /* У׼��IMD2�����ޣ���λdb */
    VOS_INT16                           shwDcCorrThreshold;                 /* У׼��IMD2�����ޣ���λdb */
}UCOM_NV_W_TX_IQ_MISMATCH_CAL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRssiArithmeticPara;
}UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_APT_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwWBand;                      /* bitλ��1����֧��APT */
    VOS_UINT32                          uwWBandExtRsv;                /* bitλ��1����֧��APT */
}UCOM_NV_W_TX_PA_APT_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_EEIC_EN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwEEICEn;
}UCOM_NV_W_EEIC_EN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_IPS_FLG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwIpsFlg;
}UCOM_NV_W_IPS_FLG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_SPUR_REMOVE_ALG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : г�������㷨
*****************************************************************************/
typedef struct
{
    UCOM_NV_WCDMA_SPUR_TYPE_ENUM_UINT16 enSpurType;                             /* г�������� */
    VOS_UINT16                          uhwMainRemoveEnable;                    /* ����ʹ�� */
    VOS_UINT16                          uhwDivRemoveEnable;                     /* �ּ�ʹ�� */
    VOS_INT16                           shwRssiThreshold;                       /* ����г�������㷨��rssi���� */
    VOS_UINT16                          uhwFilterCoeff;                         /* �˲����� */
}UCOM_NV_W_RX_SPUR_REMOVE_ALG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_M_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              auhwRfMValue[2];                    /* 0: usRfScMDaValue 1:usRfDcMDaValue */
}UCOM_NV_W_RF_M_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_LOWPOWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W�͹����������������Լ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAllocToUseExtraMpUnit;       /* ����ʹ��10~19��Ԫ,��Χ [0,1] ,�Ƽ� 0 */
    VOS_UINT16                          uhwAllocToUseExtraMpUnitInCPC;  /* CPC ����ʹ��10~15��Ԫ,��Χ [0,1],�Ƽ� 1 */
    VOS_UINT16                          uhwIntraFMSRUsing5msPerFrEn;    /* ��Ƶ5ms����, ��Χ [0,1]���Ƽ� 1 */

    /* �ر� EEIC */
    VOS_UINT16                          uhwThrptUppLmtPerCrNMThd;       /* ��Χ0~2000,����1(100Kbps),�Ƽ� 130 */
    VOS_UINT16                          uhwThrptUppLmtPerCrNonMimoEn;   /* ��Χ[0,1],�Ƽ� 1 */

    /* �رշּ� */
    VOS_UINT16                          uhwCorrCoefAccFrm;              /* �Ƚ�ͳ��֡������λ10֡����Χ0~1024,�Ƽ� 10 */
    VOS_UINT32                          uwCorrCoefShutDownThd;          /* �ر����ޣ�Ϊԭֵƽ����Ŵ�10000��,��Χ0~1000000,Ĭ�� 400, */
    VOS_UINT16                          uhwAntRssiShutDownThd;          /* �ر����ޣ���λ1dBm����Χ0~100���Ƽ�20 �Ƽ� 10 */
    VOS_UINT16                          uhwCorrCoefCalEn;               /* ��Χ[0,1],�Ƽ� 1 */
    VOS_UINT16                          uhwAntRssiCmprEn;               /* ��Χ[0,1],�Ƽ� 1 */
    VOS_UINT16                          uhwAntRssiCmprAccFrm;           /* ��Χ0~1024, �Ƽ� 10 */
    VOS_UINT16                          uhwCorrCoefReCalDelayFrm;       /* ��Χ0~1024, �Ƽ� 10 */
    VOS_UINT16                          uhwAntRssiReOpenDelayFrm;       /* ��Χ0~1024, �Ƽ� 10 */

    /* Wd��̬�ŵ���ʱ϶���� */
    VOS_UINT16                          uhwWdCalPerSlotEn;              /* ��Χ [0,1],    �Ƽ� 1 */
    VOS_UINT16                          uhwWdCalPerSlotThd;             /* ��Χ0~511,   �Ƽ� 251 */

}UCOM_NV_W_LOWPOWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_ENABLE_SELECT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : w pa en 4��ѡ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwLineSel[UCOM_NV_WCDMA_PA_EN_LINE_NUM];
}UCOM_NV_W_PA_ENABLE_SELECT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_HSUPA_MAX_POWER_TEST_MODE_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA����书�ʲ���ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnableFlag;
    VOS_UINT16                          auhwMinSetEtfci[UCOM_NV_HSUPA_ETFCI_TABLE_MAX_NUM];
}UCOM_NV_W_HSUPA_MAX_POWER_TEST_MODE_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_HDET_TIMING_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ʼ����ʹ�õ�NV��ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                              shwPaStableTiming;                   /* ���书�ʱ仯��RF��PA���ȶ�ʱ�䣬��λΪchip*/
    VOS_INT16                              shwPdHkadcChanSelTiming;             /*��Ȩ��Ч������HKADCͨ��������ʱ�̼������λΪchip*/
    VOS_INT16                              shwPdStartInterval;                  /* ABB��bypassΪ�͵�����start��ABB��ʼת������ʱ��������λΪchip*/
    VOS_INT16                              shwPdInterval;                       /* ���ι��ʼ��֮���ʱ��������λΪchip*/
    VOS_INT16                              shwPdsampleTiming;                   /* HKADC�����źŴ���ʱ�䣬��λΪchip*/
    VOS_INT16                              shwDcOffsetSampleNum;                /*WHKADC����ÿ��ʱ϶����dc offset���Ĵ���*/
    VOS_INT16                              shwPdSampleNum;                      /*W����ÿ��ʱ϶����PD���Ĵ���*/
} UCOM_NV_W_HDET_TIMING_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾÿ��RF Gain��Ӧ���¶Ȳ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_TX_TEMP_COMP_NUM];       /* ��ʾĳһ��RF Gain��16�������¶��µ��¶Ȳ���ֵ����λΪ0.1dB */
}UCOM_NV_W_TX_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾ15��RF Gain��Ӧ���¶Ȳ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCount;                                   /* ��Ч�ĵ�λ�� */
    UCOM_NV_W_TX_TEMP_COMP_STRU         astTempComp[UCOM_NV_W_TX_RF_GAIN_CTRL_NUM];     /* ��ʾ15��RF Gain��16�������¶��µ��¶Ȳ���ֵ */
}UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_VOICE_APC_SIG_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwVoiceApcSigEnable;               /* ��ʾ������ģʽ���Ƿ񼤻�Voiceģʽ��APC�� */
}UCOM_NV_W_VOICE_APC_SIG_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_VOICE_APC_CAL_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwVoiceApcCalEnable;               /* ��ʾ��У׼ģʽ���Ƿ�У׼Voiceģʽ��APC�� */
}UCOM_NV_W_VOICE_APC_CAL_ENABLE_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU
 Э����  :
 ö��˵��  : AGC��λ������NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAgcGainNoBlockNum;                   /* ��Blockģʽ��AGC������ */
    VOS_UINT16                          uhwAgcGainBlockNum;                     /* Blockģʽ��AGC������ */
}UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_RF_GAIN_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : rf gain ctrl ��λ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwValidCount;
    VOS_UINT16          auhwRfGainCtrl[UCOM_W_MAX_RF_GAIN_CTRL_NUM];
}UCOM_NV_W_TX_RF_GAIN_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_RF_BIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : rf BIAS ��λ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwValidCount;
    VOS_UINT16          auhwRfBias[UCOM_W_MAX_RF_BIAS_NUM];
}UCOM_NV_W_TX_RF_BIAS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BBÿ����λ��Ӧ��˥��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwBbGainCtrl;
    VOS_INT16           shwBbAtten10th;
}UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BB_GAIN_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BB�ĵ�λ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                             uwValidCount;
    UCOM_NV_W_BB_GAIN_VS_ATTEN_STRU        astBbGain[UCOM_W_MAX_RF_BB_GAIN_NUM];
}UCOM_NV_W_BB_GAIN_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ECIOR_CTRL_STRU
 �ṹ˵��  : ec/ior�Ŀ��ƽṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCqiLoadSwitchThreshold;          /* CQI�л����ޣ�Ĭ������Ϊ15;*/
    VOS_UINT16                          uhwLoadRateThreshold1;              /* ����������1��Ĭ������Ϊ6;*/
    VOS_UINT16                          uhwLoadRateThreshold2;              /* ����������2��Ĭ������Ϊ10; */
} UCOM_NV_W_ECIOR_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_VCO_REG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF VCO REG
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRegAddress;
    VOS_UINT16                          uhwRegValue;
}UCOM_NV_W_RF_VCO_REG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_VCO_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF VCO CONFIG
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCounter;
    UCOM_NV_W_RF_VCO_REG_STRU           astRegConfig[UCOM_NV_MAX_RF_VCO_CONFIG_NUM];
}UCOM_NV_W_RF_VCO_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_RF_TX_BIAS_REG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF TX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRegAddress;
    VOS_UINT16                          uhwRegValue;
}UCOM_NV_W_RF_TX_BIAS_REG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_TX_BIAS_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF TX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidCounter;
    UCOM_NV_W_RF_TX_BIAS_REG_STRU       astBias[UCOM_NV_W_TX_RF_BIAS_NUM];
}UCOM_NV_W_RF_TX_BIAS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_RFIC_BIAS_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRfRxAbBiasAddress;                                     /* RX AB BIAS��ַ */
    VOS_UINT16                              uhwRfRxCdBiasAddress;                                     /* RX CD BIAS��ַ */
    VOS_UINT32                              uwReserved;
}UCOM_NV_W_RX_RFIC_BIAS_CFG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_RX_BIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwNoBlockStateBias[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM]; /* no block bias��NV�� */
}UCOM_NV_W_RF_RX_BIAS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF RX DELTA GAIN
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockStateDeltaGain[UCOM_NV_W_ANT_NUM][UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM]; /* no block delta gain��NV�� */
}UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_RFIC_BIAS_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF RX BIAS
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RF_RX_BIAS_STRU                stRfRxBiasNormalMode;      /* ����ģʽ��, Rx Bias���� */
    UCOM_NV_W_RF_RX_BIAS_STRU                stRfRxBiasVoiceMode;       /* VOICEģʽ��,Rx Bias���� */
    UCOM_NV_W_RF_RX_BIAS_DELTA_GAIN_STRU     stRfRxBiasDeltaGain;       /* VOICEģʽ������ģʽ�µ������ */
}UCOM_NV_W_RX_RFIC_BIAS_CTRL_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU
 Э����  :
 ö��˵��  : VOICEģʽ�µ�AGC��λ�л����޵�NV�ֻ������BLOCK״̬��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
}UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RX_EXT_LNA_AGC_SWITCH_VOICE_MODE_STRU
 Э����  :
 ö��˵��  : ��LNA����£�VOICEģʽ�µ�AGC��λ�л����޵�NV�ֻ������BLOCK״̬��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwExtLnaNoBlockAgcThrdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwExtLnaNoBlockAgcThrdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
}UCOM_NV_W_RX_EXT_LNA_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_HDET_HKADC_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSeperatePaHdetChannel;           /* ����PA HDETͨ�� */
    VOS_UINT16                          uhwReserved;               /*��δʹ�ã����� */
}UCOM_NV_W_HDET_HKADC_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_DPA_IQ_REDUCTION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA���ֻ���
*****************************************************************************/

typedef struct
{
    VOS_INT16                           ashwDpaIqReduction[UCOM_NV_W_TX_DPA_IQ_REDUCTION_NUM];
}UCOM_NV_W_TX_DPA_IQ_REDUCTION_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SC-UPA���ֻ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwScUpaIqReduction[UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_NUM];
}UCOM_NV_W_TX_SCUPA_IQ_REDUCTION_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_DPA_MPR_STRU_HI6361
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA���ʻ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDpaMpr[UCOM_NV_W_TX_DPA_MPR_NUM];
}UCOM_NV_W_TX_DPA_MPR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_SCUPA_MPR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA���ʻ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwScUpaMpr[UCOM_NV_W_TX_SCUPA_MPR_NUM];
}UCOM_NV_W_TX_SCUPA_MPR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_DCUPA_MPR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA���ʻ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcUpaMpr[UCOM_NV_W_TX_DCUPA_MPR_NUM];
}UCOM_NV_W_TX_DCUPA_MPR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_HKADC_SSI_WAIT_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwHkadcSsiWaitTime;
}UCOM_NV_W_HKADC_SSI_WAIT_TIME_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_LTE_EVALUATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE�����������޲����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwLteEvaluateServCellReportCorr;       /* Lte����������ʱ����С�������ϱ�����ϵ��Ĭ��6����Χ0��30 */
    VOS_INT16                           shwLteEvaluateServCellRscpThres;        /* Lte���������о��ķ���С��RSCP����ֵ���ޣ���λ0.125db��Ĭ��-640����Χ-1040��-320 */
    VOS_UINT16                          uhwLteEvaluateServCellDeltaThres;       /* Lte���������о��ķ���С��rscp�仯ֵ���ޣ���λ0.125db��Ĭ��160����Χ0��480 */
}UCOM_NV_W_DRX_LTE_EVALUATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_VOLT_LOWPOWER_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ѹ�͹��Ŀ���NV
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwLowVoltDeltaPower;                   /* ��ѹ����书�ʲ�ֵ����,Ĭ��2dBm,,��Χ0~24dBm */
    VOS_UINT16                          uhwDataFrameThreshold;                  /* ��������֡��������,Ĭ��50,��λ10msOr2ms */
    VOS_UINT16                          uhwNoDataFrameThreshold;                /* ����������֡��������,Ĭ��80,��λ10ms */
    VOS_INT16                           shwLowRssiThreshold;                    /* ��ѹRSSI����,Ĭ��-95dBm */
    VOS_INT16                           shwHighRssiThreshold;                   /* ��ѹRSSI����,Ĭ��-85dBm */
    VOS_UINT16                          uhwTxPowerCntThreshold;                 /* ��ѹ���书��ͳ�Ƹ�������,Ĭ��8,��λ10ms */
    VOS_UINT16                          uhwHsupaRemainPowerCntThreshold;        /* ��ѹHSUPAʣ�๦�ʲ���ͳ�Ƹ�������,Ĭ��8,��λ10ms */
    VOS_UINT16                          uhwR99RemainPowerCntThreshold;          /* ��ѹR99ʣ�๦�ʲ���ͳ�Ƹ�������,Ĭ��8,��λ10ms */
    VOS_UINT16                          uhwForceConfigLowPowerThreshold;        /* ǿ�ƽ�ѹ��ʱ����,Ĭ��100,��λ10ms */
}UCOM_NV_VOLT_LOWPOWER_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ANT2_OFF_EVA_THRESH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����2�رյ��������޲����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTimeRxNoDataDpa;                     /* 80��160��320��640��1000��λms��Ĭ��160ms */
    VOS_UINT16                          uhwTimeRxNoDataR99Turbo;                /* 80��160��320��640��1000��λms��Ĭ��160ms */
    VOS_UINT16                          uhwTimeRxNoDataR99Vtb;                  /* 80��160��320��640��1000��λms��Ĭ��160ms */
}UCOM_NV_W_ANT2_OFF_EVA_THRESH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_RX_CAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ҪУ׼��WCDMA��Ƶ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;
    VOS_UINT16                          auhwRxCalChan[UCOM_WCDMA_UARFCN_NUM];        /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 auhwRxCalChan[UCOM_WCDMA_BAND_NUM][UCOM_NV_W_UARFCN_NUM]; */ /* RXƵ�����䣬3��Ƶ�Σ�ÿ��Ƶ��16��UARFCN */
}UCOM_NV_WCDMA_RX_CAL_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :3.3��Ҫ����IP2У׼��Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwHighFreq;
    VOS_UINT16                          uhwMidFreq;
    VOS_UINT16                          uhwLowFreq;
}UCOM_NV_W_RX_IP2_CAL_CHAN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_CAL_AT1_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����RXͨ��ÿ��BAND�ڸ��е�Ƶ��ּ��رպʹ���������£���I��Q·�ĵ�·��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetHDivyOn;                   /* ��Ƶ��ּ����� */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetHDivyOff;                  /* ��Ƶ��ּ��ر� */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetMDivyOn;                   /* ��Ƶ��ּ����� */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetMDivyOff;                  /* ��Ƶ��ּ��ر� */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetLDivyOn;                   /* ��Ƶ��ּ����� */
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetLDivyOff;                  /* ��Ƶ��ּ��ر� */
}UCOM_NV_W_RX_IP2_CAL_AT1_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_CAL_AT2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�ּ�RXͨ��ÿ��BAND�ڸ��е�Ƶ���£���I��Q·�ĵ�·��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetH;
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetM;
    UCOM_NV_RX_IP2_STRU                 stRxIp2OffsetL;
}UCOM_NV_W_RX_IP2_CAL_AT2_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :IP2У׼����,�����ּ�����ͬһ���ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwIp2StopThreshold;                    /* ֹͣ���� */
    VOS_INT16                           shwIp2FailThreshold;                    /* ʧ������ */
}UCOM_NV_W_RX_IP2_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwRxIp2CalEnableAt2;           /* 0��ʾ�����ּ�����IP2У׼��1��ʾ������ */
}UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :3.5 AGC������ͳһ��Ƶ������Ƶ�㲻ͬ�����������仯
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcFreqComp[UCOM_WCDMA_UARFCN_NUM];
}UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC GainУ׼ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGainNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];
    VOS_INT16                           ashwRxAgcGainBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC GainУ׼ֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_ANY_CARRIER_STRU            astAgcGain[UCOM_NV_DC_SC_MODE_BUTT];    /* AGC Gain,���������ز� */
}UCOM_NV_W_RX_AGC_GAIN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC GainУ׼ֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_STRU            astRxAgcGainAnt[UCOM_NV_W_ANT_NUM];    /* AGC Gain,���������ز� */
}UCOM_NV_W_RX_AGC_GAIN_DANT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC Gain Predefinedֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxAgcGainPreNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];
    VOS_INT16                           ashwRxAgcGainPreBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC Gain Predefinedֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_PRE_ANY_CARRIER_STRU
                                        astRxAgcGainPreCarrier[UCOM_NV_DC_SC_MODE_BUTT];         /* AGC Gain Preֵ,���������ز� */
}UCOM_NV_W_RX_AGC_GAIN_PRE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC Gain Predefinedֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_PRE_STRU
                                        astRxAgcGainPreAnt[UCOM_NV_W_ANT_NUM];         /* AGC Gain Preֵ,���������ز� */
}UCOM_NV_W_RX_AGC_GAIN_PRE_DANT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC Front End Predefinedֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwRxFrontEndGainPre[UCOM_NV_DC_SC_MODE_BUTT];   /* Front End Predefined */
}UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGC Front End Predefinedֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_STRU         astRxFrontEndGainPre[UCOM_NV_W_ANT_NUM];   /* Front End Predefined */
}UCOM_NV_W_RX_AGC_FRONT_END_GAIN_PRE_DANT_STRU;


/*****************************************************************************
 ö����    : RX_AGC_GAIN_SWITCH_THRESHOLD_STRU
 Э����  :
 ö��˵��  : AGC��λ�л����޵�NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwBlockAgcThresholdInc[UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM];             /* Block��ʽ�µ�λ���� */
    VOS_INT16                           ashwBlockAgcThresholdDec[UCOM_NV_W_AGC_GAIN_BLK_THRESHOLD_NUM];             /* Block��ʽ�µ�λ���� */
}UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RX_AGC_GAIN_PREDEFINED_ANYCARRIER_STRU
 Э����  :
 ö��˵��  : AGC��λ�л����޵�NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU      astRxAgcGainSwitchThreshold[UCOM_NV_DC_SC_MODE_BUTT];
}UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_DCARR_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_W_RX_AGC_CTRL_STRU
 Э����  :
 ö��˵��  : AGC�����ֵ�NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      unAgcCtrlNoBlock[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];                   /* ��Blockģʽ��AGC������ */
    VOS_UINT32                      unAgcCtrlBlock[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];                     /* Blockģʽ��AGC������ */
}UCOM_NV_W_RX_AGC_CTRL_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_RX_AGC_CTRL_STRU
 Э����  :
 ö��˵��  : AGC�����ֵ�NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_CTRL_STRU  astRxAgcCtrl[UCOM_NV_DC_SC_MODE_BUTT];
}UCOM_NV_W_RX_AGC_CTRL_DCARR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi lna ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                               uwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                    astLnaMipiCmd[UCOM_NV_W_LNA_MIPI_CMD_MAX_NUM ];
    UCOM_NV_MIPI_BYTE_DATA_STRU              astLnaMipiData[UCOM_NV_W_LNA_MIPI_DATA_MAX_NUM ];
}UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU;


typedef UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU UCOM_NV_CDMA_EXT_LNA_MIPI_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_EXT_LNA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EXT LNA INFO
*****************************************************************************/
typedef struct
{
    /* GPIO���� */
    VOS_UINT32                               uwGpioEnable;                              /* GPIOʹ���ź� */
    VOS_UINT32                               uwLnaGpioNumber;                           /* GPIO֧�ֵĵ�λ��*/
    VOS_UINT32                               auwLnaGpio[UCOM_NV_W_LNA_GPIO_STEP_NUM];   /* GPIO��ʽ��LNA���� */
    VOS_UINT32                               uwLnaGpioMask;                             /* ʹ�õ�LNA GPIO������ */

    /* MIPI���� */
    VOS_UINT32                               uwMipiEnable;                              /* MIPIʹ���ź�*/
    VOS_UINT32                               uwLnaMipiNumber;                           /* MIPI֧�ֵĵ�λ��*/
    UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU         astLnaMipi[UCOM_NV_W_LNA_MIPI_STEP_NUM];   /* MIPI LNA ���� */
    UCOM_NV_W_EXT_LNA_MIPI_WORD_STRU         stLnaOff;                                  /* LNA �ر�����*/

    /* LNA���������� */
    VOS_UINT32                               auwUnBlockGainIndex[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];/* BLOCK��AGC��λ��lna����*/
    VOS_UINT32                               auwBlockGainIndex[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];/* BLOCK��AGC��λ��lna��������*/
}UCOM_NV_W_EXT_LNA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_EXT_LNA_COMMON_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EXT LNA COMMON INFO
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_EXT_LNA_INFO_STRU              stMainLnaInfo;                     /* ����lna ��Ϣ */
    UCOM_NV_W_EXT_LNA_INFO_STRU              stDivLnaInfo;                      /* �ּ�lna ��Ϣ  */
}UCOM_NV_W_EXT_LNA_COMMON_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_CTRL_EXT_LNA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LNA��AGC������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_CTRL_DCARR_STRU         stAgcCtrlWord;       /* LNA ON��ʱ��ʹ�õ�AGC��������� */
}UCOM_NV_W_RX_AGC_CTRL_EXT_LNA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_AGC_SWITCH_THRD_EXT_LNA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LNA��AGC������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_GAIN_SWITCH_THRESHOLD_DCARR_STRU         stAgcThreshold; /* LNA ON��ʱ��ʹ�õ�AGC�л����� */
}UCOM_NV_W_RX_AGC_SWITCH_THRD_EXT_LNA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_TIME_DOMAIN_HARMONIC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʱ��г����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      uwHarmonicFlag;                         /* ��ǰband�Ƿ����г���������в������� */
    UCOM_NV_W_HARMONIC_TYPE_ENUM_UINT16             enHarmonicType;                         /* ��ǰbandг����Դ */
    VOS_UINT32                                      uwHarmonicNum;                          /* г����Ŀ */
    VOS_UINT16                                      auhwHarmonicFreq[UCOM_NV_HARMONIC_NUM]; /* г��Ƶ�ʣ���λ100khz */
    VOS_INT16                                       shwEnableRssi;                          /* ��г������������,��λ1db */
    VOS_INT16                                       shwDisableRssi;                         /* �ر�г������������,��λ1db */

}UCOM_NV_W_RX_TIME_DOMAIN_HARMONIC_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_DCOFFSET_STRU
 Э����  :
 ö��˵��  : DC offset�Ľṹ������
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDci;                                 /* I·��ֱ��ֵ */
    VOS_INT16                           shwDcq;                                 /* Q·��ֱ��ֵ */
}UCOM_NV_W_DCOFFSET_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU
 Э����  :
 ö��˵��  : DC offset�Ľṹ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_STRU             astNoBlockDcOffset[UCOM_NV_W_AGC_GAIN_BLK_STEP_NUM];       /* blockģʽ�¸���λ��DC offset */
    UCOM_NV_W_DCOFFSET_STRU             astBlockDcOffset[UCOM_NV_W_AGC_GAIN_NOBLK_STEP_NUM];         /* ��blockģʽ�¸���λ��DC offset */
}UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU;


/*****************************************************************************
 ö����    : W_DCOFFSET_ANT_STRU
 Э����  :
 ö��˵��  : DC offset�Ľṹ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_ANYCARRIER_STRU              astAnyCarrierDcOffset[UCOM_NV_DC_SC_MODE_BUTT];   /* SC\DC�ز�ģʽ�µ�DCֵ */
}UCOM_NV_W_DCOFFSET_ANT_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_DCOFFSET_ANT_STRU
 Э����  :
 ö��˵��  : DC offset�Ľṹ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DCOFFSET_ANT_STRU              astDcOffsetAnt[UCOM_NV_W_ANT_NUM];
}UCOM_NV_W_DCOFFSET_DANT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_FEM_CHAN_CONNECT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : A/Bͨ���Ե�ѡ��,ǰ��Ch0/CH1ͨ��ѡ��
*****************************************************************************/
typedef struct
{
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enRfConnect;                            /* RF~RFIC֮�������:0:����������RF_A��1:����������RF_B */
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enRfAbbConnect;                         /* RFIC��ABB֮�������,Ӳ������,����Ҫ������� */
    UCOM_NV_CHAN_CONNECT_ENUM_UINT16    enAbbBbpConnect;                        /* ABB��BBP COM1֮�������:0:����������ABB_A��1:����������ABB_B */
    VOS_UINT16                          uhwChanSwitch;                          /* ����ÿ��bandѡ��ͨ��0����1,ĿǰV9R1��Ĭ������ͨ����ѡ��0,����ͨ����ѡ��1. */

}UCOM_NV_FEM_CHAN_CONNECT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ҪУ׼��WCDMA��Ƶ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;
    VOS_UINT16                          auhwTxCalChan[UCOM_WCDMA_UARFCN_NUM];        /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 auhwRxCalChan[UCOM_WCDMA_BAND_NUM][UCOM_NV_W_UARFCN_NUM]; */ /* RXƵ�����䣬3��Ƶ�Σ�ÿ��Ƶ��16��UARFCN */
}UCOM_NV_WCDMA_TX_CAL_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_RACH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWiredMaxPowerRach;                             /* ����Ƶ�Σ����н�����DPCH�����RACHʱUE�����������书�ʣ���λ0.1dbm;��0��ΪRACH,��1��ΪDPCH, */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_RACH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_DPCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWiredMaxPowerDpch;                             /* ����Ƶ�Σ����н�����DPCH�����RACHʱUE�����������书�ʣ���λ0.1dbm;��0��ΪRACH,��1��ΪDPCH, */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_DPCH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxWiredMaxPowerTempComp[UCOM_NV_W_TEMP_NUM];    /* ����书�ʲ������棬��λ0.1dbm;3��Ƶ�Σ�5��Ԥ�ȶ�����¶ȵ�:-20,0,20,40,60,��6�������ڶ��룬��ʹ�� */
}UCOM_NV_WCDMA_TX_WIRED_MAX_POWER_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_MIN_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxMinPower;                                      /* UE�������С���书�ʣ���λ0.1dbm;3��Ƶ�Σ�5��Ԥ�ȶ�����¶ȵ�:-20,0,20,40,60,��6�������ڶ��룬��ʹ�� */
}UCOM_NV_WCDMA_TX_MIN_POWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_MIN_POWER_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxMinPowerTempComp[UCOM_NV_W_TEMP_NUM];         /* ��С���书���¶Ȳ��� */
}UCOM_NV_WCDMA_TX_MIN_POWER_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_VGA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxHdetVga;                                                   /* ��ʾPD��ǰ��˥�� ��VGAֵ*/
}UCOM_NV_W_TX_HDET_VGA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_DCOFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwTxHdetDcOffset;                                              /* ��ʾDCOFFSET */
}UCOM_NV_W_TX_HDET_DCOFFSET_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetContPower[UCOM_NV_W_TX_HDET_PV_NUM];                  /* ������ģʽ�£����Թ��ʺ͵�ѹ��ϵ�Ĺ��ʲ��Ե� */
}UCOM_NV_W_TX_HDET_POWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_HKADC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetVolt[UCOM_NV_W_TX_HDET_PV_NUM];                       /* ������ģʽ�£����Թ��ʺ͵�ѹ��ϵʱ��ѹ����ֵ */
}UCOM_NV_W_TX_HDET_HKADC_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_FREQ_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetFreqComp[UCOM_WCDMA_UARFCN_NUM];                       /* ��ͬƵ��Թ�������Ӱ�첻ͬ��Ƶ�ʲ���ֵ */
}UCOM_NV_W_TX_HDET_FREQ_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTxHdetTempComp[UCOM_NV_W_TEMP_NUM];  /* ��ͬ�¶ȶԹ�������Ӱ�첻ͬ���¶Ȳ���ֵ.���ָ��е��ŵ�,˳��Ϊ�иߵ� */
}UCOM_NV_W_TX_HDET_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_START_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxHdetStart;                                                 /* TX ���书�ʳ�����ֵʱ��BBP�Զ��������ʼ�� */
}UCOM_NV_W_TX_HDET_START_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_STOPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxHdetStop;                                                  /* TX ���书��С�ڸ�ֵʱ��BBP�Զ�ֹͣ���ʼ�� */
}UCOM_NV_W_TX_HDET_STOPT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_RACH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWirelessMaxPowerRach;                          /* ���� *//* �տڷ��书��:_UCOM_TX_PWR_CTRL_SWITCH */
}UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_RACH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_DPCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxWirelessMaxPowerDpch;                          /* ���� *//* �տڷ��书��:_UCOM_TX_PWR_CTRL_SWITCH */
}UCOM_NV_WCDMA_TX_WIRE_MAXPOWER_DPCH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_WIRELESS_POWER_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxWirelessPowerTempComp[UCOM_NV_W_TEMP_NUM];    /* �տڹ������¶Ȳ��� */
}UCOM_NV_WCDMA_TX_WIRELESS_POWER_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_GAIN_COMP_VS_PA_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwHighFreq;                            /* �����жϸ�Ƶ�������Ƶ�� */
    VOS_UINT16                          uhwLowFreq;                             /* �����жϵ�Ƶ�������Ƶ�� */
}UCOM_NV_W_TX_GAIN_COMP_VS_PA_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_GAIN_COMP_VS_PA_CH_STRU
 Э����  :
 �ṹ˵��  : W TX PA�����л��㲹��������ֽ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwValidNum;                             /* ��ʾ����Ƶ�㼸����Ч */
    VOS_UINT16                          auhwFreqChan[UCOM_NV_W_PA_GAIN_SWITCH_COMP_CHAN_NUM];
}UCOM_NV_W_TX_GAIN_COMP_VS_PA_CH_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU
 Э����  :
 �ṹ˵��  : W TX PA�����л�ʱ���ʲ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwH2MComp;                             /* PA����Ӹ��е��е����޲���,��λ0.1db */
    VOS_INT16                           shwM2HComp;                             /* PA��������е��ߵ����޲���,��λ0.1db */
    VOS_INT16                           shwM2LComp;                             /* PA��������е��͵����޲���,��λ0.1db */
    VOS_INT16                           shwL2MComp;                             /* PA����ӵ��е��е����޲���,��λ0.1db */
}UCOM_NV_W_PA_GAIN_SWITCH_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU
 Э����  :
 �ṹ˵��  : W TX 4��ʱ϶��PA�����л�ʱ���ʲ���ֵ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_PA_GAIN_SWITCH_COMP_STRU  astSlotComp[UCOM_NV_W_PA_SWITCH_COMP_SLOT];
}UCOM_NV_W_TX_PA_GAIN_SWITCH_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_APC_TEMP_STRU
 Э����  :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwTxApcTemp;                                       /* ����У׼ʱ���¶�ֵ:��������ŵ���,ÿ��BAND�ĸ��е�PA����ģʽ��У׼ʱ����¶�ֵ,�б�ʾ���е� */
}UCOM_NV_W_TX_APC_TEMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_GAIN_SWITH_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwPaGainThresH2M;                      /* PA�Ӹ����浽��������л����� */
    VOS_INT16                           shwPaGainThresM2H;                      /* PA�������浽��������л����� */
    VOS_INT16                           shwPaGainThresM2L;                      /* PA�������浽��������л����� */
    VOS_INT16                           shwPaGainThresL2M;                      /* PA�ӵ����浽��������л����� */
}UCOM_NV_W_PA_GAIN_SWITH_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_PA_GAIN_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          uwRfPaCtrlHighMode;                     /* PA������ģʽ������ */
    VOS_UINT32                          uwRfPaCtrlMediumMode;                   /* PA������ģʽ������ */
    VOS_UINT32                          uwRfPaCtrlLowMode;                      /* PA������ģʽ������ */
}UCOM_NV_W_RF_PA_GAIN_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwPaGainSwitchH2M;                     /* PA��������浽�������л�ʱ�� */
    VOS_INT16                           shwPaGainSwitchM2H;                     /* PA���������浽�������л�ʱ�� */
    VOS_INT16                           shwPaGainSwitchM2L;                     /* PA���������浽�������л�ʱ�� */
    VOS_INT16                           shwPaGainSwitchL2M;                     /* PA��������浽�������л�ʱ�� */
}UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TX_IQ_MISMATCH_DCR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.3 ÿ��NV��Ŀ��ʾ����IQ mismatch��DC offset
            ��������ʱ�����˲������ø�DBB����TXͨ������Ԥ����
            ���ֲ�����ͨ����IQ mismatch�Ͳ���DC��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAmplitude;                           /* ��ֵУ������ */
    VOS_INT16                           shwPhase;                               /* ��λУ������ */
    VOS_INT16                           shwDCI;                                 /* ֱ��У��ʵ�� */
    VOS_INT16                           shwDCQ;                                 /* ֱ��У���鲿 */
}UCOM_NV_TX_IQ_MISMATCH_DCR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾRFIC��DBB��˥��������£����е�3�����������ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwPaGain[UCOM_NV_W_TX_PA_MODE_NUM];           /* ��VOICEģʽ�£���ʾRFIC��DBB��˥��������£����е�3�����������ֵ����λΪ0.1dB */
}UCOM_NV_W_TX_PA_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ʾVOICEģʽ�£�RFIC��DBB��˥��������£����е�3�����������ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwPaGain[UCOM_NV_W_TX_PA_MODE_NUM];           /* ��ʾVOICEģʽ�£�RFIC��DBB��˥��������£����е�3�����������ֵ����λΪ0.1dB */
}UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PHASE_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :4.2 PAģʽ�Ӹ������л��������桢�������л��������桢�������л���
                �����桢�������л���������ʱ������TX��PA��Ի���IQ�źŲ�����λ
                ��ת��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaH2M;
    VOS_INT16                           shwPaM2H;
    VOS_INT16                           shwPaM2L;
    VOS_INT16                           shwPaL2M;

}UCOM_NV_W_TX_PHASE_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwTxPhaseCompTiming;
}UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_GAIN_FREQCOMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwTxGainFreqComp[UCOM_NV_W_TX_FREQ_COMP_NUM];     /* _H2ASN_Replace PHY_UINT16_ARRAY2_16 ashwHigh[W_BAND_NUM][W_UARFCN_NUM];*/ /* TX������Ƶ�ʲ���ֵ */
}UCOM_NV_W_TX_GAIN_FREQCOMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :7.4 PA���ڸ��е�����ģʽ�£�Ƶ���ڸߡ��С����ŵ��£�TX���书��������¶ȱ仯�Ĳ���
*****************************************************************************/
typedef struct
{
    /* �¶ȷ�Χ��ȡֵȡ����UCOM_NV_WG_TX_TEMP_DEFINE_STRU */
    VOS_INT16                           ashwTxGainTempComp[UCOM_NV_W_TX_PA_TEMP_NUM];
}UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_HSDPCCH_DELTA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTpcAlgo1UlPowGain;
    VOS_INT16                           shwTpcAlgo1HsDpaPowMode;
    VOS_INT16                           shwTpcAlgo2UlPowGain;
    VOS_INT16                           shwTpcAlgo2HsDpaPowMode;
}UCOM_NV_W_HSDPCCH_DELTA_GAIN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SAR_BACKOFF_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��SAR���ʻ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwWcdmaSarBackoffPower[UCOM_NV_SAR_BACKOFF_NUM][UCOM_NV_SAR_MODEM_SCENE_NUM];
}UCOM_NV_W_SAR_BACKOFF_POWER_STRU;

typedef UCOM_NV_W_SAR_BACKOFF_POWER_STRU UCOM_NV_CDMA_SAR_BACKOFF_POWER_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SAR_BACKOFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��SAR���ʻ���ֵ(DPDT״̬��modem������AT��λ)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwSupportBandBitmap;            /* �����ⳡ����Чʱ�����Ȳ鿴��Ӧ��Ƶ���Ƿ�֧�����ⳡ�������֧�֣���ʹ�ñ�NV����й��ʻ��ˡ� */
    UCOM_NV_W_SAR_BACKOFF_POWER_STRU            stDpdtPassThrough;              /* DPDT״̬Ϊֱ̬ͨʱ��SAR���� */
    UCOM_NV_W_SAR_BACKOFF_POWER_STRU            stDpdtSwap;                     /* DPDT״̬Ϊ����̬ʱ��SAR���� */
}UCOM_NV_W_SAR_BACKOFF_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SAR_SPECIAL_SCENE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SAR���ⳡ��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_SAR_BACKOFF_STRU                  astSpeceilScene[UCOM_NV_W_SAR_SPECIAL_SCENE_NUM];
                                                                                /* ���ⳡ����SAR���ˡ����֧��4�� */
}UCOM_NV_W_SAR_SPECIAL_SCENE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_SAR_BAND_ATTRIBUTE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM SAR���ܵ�Ƶ������(��Ƶ��/��Ƶ��)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwBandMask;                     /* ��Ӧ��bit��λ1�����Ƶ�Ρ�BIT0��ʾ850M,BIT1��ʾ900M,BIT2��ʾ1800M,BIT3��ʾ1900M, */
}UCOM_NV_GSM_SAR_BAND_ATTRIBUTE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SAR_BAND_PARTITION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W SAR���ܵ�Ƶ������(��Ƶ��/��Ƶ��)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwBandMask;                     /* ��Ӧ��bit��λ1�����Ƶ�Ρ�BIT0��ʾB1��BIT1��ʾB2��BIT2��ʾB3���Դ����� */
    VOS_UINT32                                  uwResvered;
}UCOM_NV_W_SAR_BAND_ATTRIBUTE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwApcRficCtrlGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwApcDbbAttenGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRfGainStateIndexGain[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwApcRficCtrlGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_DBB_ATTEN_GAIN_MODE_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   ashwApcDbbAttenGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU
 Э����  :
 �ṹ˵��  : APC table��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  auhwRfGainStateIndexGainVoiceMode[UCOM_NV_W_APC_ATTEN_NUM];

}UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_APT_STRU
 Э����  :
 �ṹ˵��  : APT���书�ʵĽṹ������
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower10th;                           /* ÿ����λ��APT���书�� */

    VOS_UINT16                          uhwPaVcc;                               /* ÿ����λ��APT��ѹ������ */
    VOS_UINT16                          uhwPaVbias;                             /* ÿ����λ��MmmbPaVbias��ѹ������ */
    VOS_UINT16                          uhwPaVbias2;                            /* ÿ����λ��MmmbPaVbias2 */
    VOS_UINT16                          uhwPaVbias3;                            /* ÿ����λ��MmmbPaVbias3 */
}UCOM_NV_W_TX_PA_APT_STRU;

typedef UCOM_NV_W_TX_PA_APT_STRU                UCOM_NV_CDMA_TX_PA_APT_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_PA_APT_TABLE_STRU
 Э����  :
 �ṹ˵��  : APT���书�ʵĽṹ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_POWER_STEP_ENUM_UINT16      enAptStepMode;
    VOS_UINT16                          auhwValidCount[UCOM_NV_PA_GAIN_MAX_NUM];
    UCOM_NV_W_TX_PA_APT_STRU            astAptTable[UCOM_NV_APT_TABLE_MAX_LEN];
}UCOM_NV_W_TX_PA_APT_TABLE_STRU;

typedef UCOM_NV_W_TX_PA_APT_TABLE_STRU UCOM_NV_CDMA_TX_PA_APT_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MIPI_PA_TIMING_CFG_STRU
 Э����  :
 �ṹ˵��  : PA�Ŀ�����Ϣ��ǰ��ʱ϶ͷ��Чʱ�䣬��λchip
*****************************************************************************/
typedef struct
{
    VOS_UINT16              uhwPaVccActiveTime;
    VOS_UINT16              uhwPaBias1ActiveTime;
    VOS_UINT16              uhwPaBias2ActiveTime;
    VOS_UINT16              uhwPaBias3ActiveTime;
    VOS_UINT16              uhwTrigger1ActiveTime;
    VOS_UINT16              uhwTrigger2ActiveTime;
}UCOM_NV_W_MIPI_APT_TIMING_CFG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APT_CTRL_STRU
 Э����  :
 �ṹ˵��  : APT����PA������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAptPaVbias1En         :1;             /* APT���� PaVbias�Ƿ���Ч */
    VOS_UINT32                          uwAptPaVbias2En         :1;             /* APT���� PaVbias1�Ƿ���Ч */
    VOS_UINT32                          uwAptPaVbias3En         :1;             /* APT���� PaVbias2�Ƿ���Ч */
    VOS_UINT32                          uwAptMipiTrigger1En     :1;             /* Mipi Trigger[0]�Ƿ���Ч */
    VOS_UINT32                          uwAptMipiTrigger2En     :1;             /* Mipi Trigger[1]�Ƿ���Ч */
    VOS_UINT32                          uwAptPaVccCtrlType      :2;             /* APT���� pa Vcc��������,0:PDM,1:MIPI */
    VOS_UINT32                          uwAptPaVbiasCtrlType    :2;             /* APT���� pa Vbias��������,0:DAC,1:MIPI */
    VOS_UINT32                          uwAptPaVccMipiChSel     :3;             /* APT���� pa VccΪMipi��ʱ��ѡ��MIPIͨ�� */
    VOS_UINT32                          uwAptPaVbias1MipiChSel  :3;             /* APT���� pa VbiasΪMipi��ʱ��ѡ��MIPIͨ�� */
    VOS_UINT32                          uwAptPaVbias2MipiChSel  :3;             /* APT���� pa Vbias1ΪMipi��ʱ��ѡ��MIPIͨ�� */
    VOS_UINT32                          uwAptPaVbias3MipiChSel  :3;             /* APT���� pa Vbias2ΪMipi��ʱ��ѡ��MIPIͨ�� */
    VOS_UINT32                          uwReserve               :11;            /* ���� */
}UCOM_NV_W_APT_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU
 Э����  :
 �ṹ˵��  : Mipi PA trigger��mipi����ָ��
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU               astPaTriggerMipiCmd[UCOM_NV_W_MIPI_PA_TRIGGER_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU         astPaTriggerMipiData[UCOM_NV_W_MIPI_PA_TRIGGER_NUM];
}UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APT_CTRL_PARA_STRU
 Э����  :
 �ṹ˵��  : APT������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_APT_CTRL_STRU             stAptCtrlInfo;
    UCOM_NV_MIPI_CMD_STRU               stPaVccMipiCmd;                                 /* PA Vcc��mipi����ָ��,������APT�� */
    UCOM_NV_MIPI_CMD_STRU               astPaVbiasMipiCmd[UCOM_NV_W_TX_PA_VBIAS_NUM];   /* ����PA Vbias�Ŀ���ָ�������APT�� */
    UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU  stMipiPaTrigger;                                /* Mipi PA Triggerָ���֤APT����Paָ��ͬʱ��Ч�������ٽ����  */
    UCOM_NV_W_MIPI_APT_TIMING_CFG_STRU  stMipiAptTimingInfo;                            /* PA�Ŀ�����Ϣ��ǰ��ʱ϶ͷ��Чʱ�䣬��λchip */
}UCOM_NV_W_APT_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ANT_TUNER_BAND_PARA_STRU
 Э����  :
 �ṹ˵��  : ���ߵ�гBAND���ƽṹ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAntTunerCode;                   /* ��ǰBAND���ߵ�гĬ��ֵ */
    VOS_UINT16                              uhwReserve;
    VOS_UINT16                              uhwAntTunerStart;                  /* ��ǰBANDפ�������������,BBPδ�ṩ�ӿڣ��ݺ�PD������һ�� */
    VOS_INT16                               shwAntTunerComp;                   /* �����ʲ���������0.1dbm */
}UCOM_NV_W_ANT_TUNER_BAND_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU
 Э����  :
 �ṹ˵��  : Tuner������֡
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_BYTE_DATA_STRU         astTunerMipiData[UCOM_NV_W_TUNER_MIPI_DATA_MAX_NUM];
}UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU
 Э����  :
 �ṹ˵��  : Tuner������֡
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_GSM_TUNER_MIPI_DATA_MAX_NUM];
}UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU
 Э����  :
 ö��˵��  : W��������,���֧������״̬
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiTunnerCmd[UCOM_NV_W_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_W_TUNER_MIPI_DATA_FRAME_STRU    astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU;

typedef UCOM_NV_W_TUNER_MIPI_CTRL_WORD_STRU UCOM_NV_CDMA_TUNER_MIPI_CTRL_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_TUNER_MIPI_TX_CTRL_WORD_STRU
 Э����  :
 �ṹ˵��  : GģTxĬ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                       astMipiTunnerCmd[UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU      astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_G_TUNER_MIPI_TX_CTRL_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TUNER_MIPI_DATA_RX_STRU
 Э����  :
 �ṹ˵��  : GģRxĬ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                       astMipiTunnerCmd[UCOM_NV_GSM_TUNER_MIPI_CMD_MAX_NUM];
    UCOM_NV_GSM_TUNER_MIPI_DATA_FRAME_STRU      astMipiDataStatus[UCOM_NV_TUNER_HANDLE_STATUS_NUM];
}UCOM_NV_G_TUNER_MIPI_RX_CTRL_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SC-UPA��CMֵ����
*****************************************************************************/

typedef struct
{
    VOS_INT16                           ashwScUpaPdComp[UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_NUM];
}UCOM_NV_W_TX_HDET_SCUPA_CM_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_HDET_DPA_CM_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPA��CMֵ����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwDpaPdComp[UCOM_NV_W_TX_HDET_DPA_CM_COMP_NUM];
}UCOM_NV_W_TX_HDET_DPA_CM_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_APT_CM_SCUPA_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SC-UPAҵ���APTģʽscupa����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptCmScupaComp[UCOM_NV_W_TX_APT_SCUPA_CM_COMP_NUM];
}UCOM_NV_W_TX_APT_CM_SCUPA_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_APT_CM_DPA_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SC-UPAҵ���APTģʽdpa����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptCmDpaComp[UCOM_NV_W_TX_APT_DPA_CM_COMP_NUM];
}UCOM_NV_W_TX_APT_CM_DPA_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_APT_TEMP_COMP_STRU_HI6361
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APTƵ�ʲ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptTempComp[UCOM_NV_W_APT_FREQ_COMP_NUM][UCOM_NV_W_APT_TEMP_COMP_NUM];                                /* ��ֵ��ʾW��BAND����Gģ��BAND��ʶ */
}UCOM_NV_W_APT_TEMP_COMP_STRU;

typedef UCOM_NV_W_APT_TEMP_COMP_STRU UCOM_NV_CDMA_APT_TEMP_COMP_STRU;

/*****************************************************************************
 ö����    : UCOM_NV_W_APT_COMP_STRU
 Э����  :
 ö��˵��  : APT��ѹ�����Ľṹ������
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptComp[UCOM_NV_APT_TABLE_MAX_LEN];       /* ÿ����λ��APT���� */
}UCOM_NV_W_APT_COMP_STRU;

typedef UCOM_NV_W_APT_COMP_STRU UCOM_NV_CDMA_APT_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_NONLINEAR_STRU_HI6361
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA�����Բ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower;
    VOS_INT16                           shwNonLinearComp;
}UCOM_NV_W_PA_NONLINEAR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_NONLINEAR_COMP_STRU_HI6361
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA�����Բ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_POWER_STEP_ENUM_UINT16      enPowerStepMode;
    VOS_UINT16                          auhwValidCount[UCOM_NV_PA_GAIN_MAX_NUM];
    UCOM_NV_W_PA_NONLINEAR_STRU         astNonLinear[UCOM_NV_W_PA_NONLINEAR_NUM];
}UCOM_NV_W_PA_NONLINEAR_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_INT16                           shwStartPower;                          /* ��ѹ����,Ĭ��16dBm,��Χ0~22dBm */
    VOS_INT16                           shwStopPower;                           /* ��ѹ����,Ĭ��18dBm,��Χ0~22dBm */
}UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAIL_BOX_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwWcdmaMailBoxFlag;                 /* W���䷽����1:���䷽����Ч��0:��Ч */
    VOS_UINT16                          uhwReserved;                /* �����ֽ� */
}UCOM_NV_W_MAIL_BOX_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TX_LOW_VOLT_SWITCH_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwSlaveSampleNum;                      /* ��ģ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ1 */
    VOS_UINT16                          uhwDrxIntraSampleNum;                   /* DRX��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ1 */
    VOS_UINT16                          uhwDrxInterSampleNum;                   /* DRX��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ1 */
    VOS_UINT16                          uhwFachIntraSampleNum;                  /* FACH��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ2 */
    VOS_UINT16                          uhwFachInterSampleNum;                  /* FACH��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ1 */
    VOS_UINT16                          uhwDchIntraSampleNum;                   /* DCH��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ10 */
    VOS_UINT16                          uhwDchInterSampleNum;                   /* DCH��Ƶ�ּ�ģʽ�л��Ĳ�������,Ĭ��Ϊ1 */
    VOS_INT16                           shwMain2ScndThreshold;                  /* ���������з���ּ������ޣ�TX_MAIN_RSCP - TX_SCND_RSCP <= ���ޣ��л�������ּ���-48(-6dB,1/8dB����) */
    VOS_INT16                           shwScnd2MainThreshold;                  /* ���������з���ּ������ޣ�TX_MAIN_RSCP - TX_SCND_RSCP > ���ޣ��л�������ּ���-16(-2dB,1/8dB����) */
    VOS_INT16                           shwMeasValidThreshold;                  /* ����ֵ��Ч���ޣ�-960(-120dB,1/8dB����) */
    VOS_INT16                           uhwMeasNonEqualThreshold;               /* ����ֵ��Ч���ޣ�|TX_MAIN_RSCP - TX_SCND_RSCP| > ���ޣ�˵������������������������,24(3dB,1/8dB����) */
    VOS_UINT16                          uhwEvaTxEnable;                         /* ��������ּ�ʹ�ܵı�ǣ�1��ʾʹ�ܡ�0��ʾ��ʹ�� */
}UCOM_NV_W_TX_DIV_MODE_EVALUATE_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������NV����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwRssiThreshold;                       /* ����˫���߲�����RSSI����(��λΪ0.125dbm) */
    VOS_INT16                           shwRscpThreshold;                       /* ����˫���߲�����RSCP����(��λΪ0.125dbm) */
    VOS_UINT16                          uhwEstimateTime;                        /* ����ʱ��(��λΪ1ms) */
    VOS_UINT16                          uhwReserved;                            /* ���ֽڶ��� */
}UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_DUAL_ANT_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫���߱Ƚ�״̬NV����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwRscpThreshold[3];                    /* �����׶������л���RSCP����(��λΪ0.125dbm) */
    VOS_UINT16                          uhwCompareTime[3];                      /* �����׶ε�˫���߱Ƚ�ʱ��(��λΪ1ms) */
}UCOM_NV_W_DUAL_ANT_COMPARE_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_ANT_PROTECT_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߱���״̬NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFrozenTime;                          /* ��������������״̬�Ķ���ʱ��(��λΪ1ms) */
}UCOM_NV_W_ANT_PROTECT_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BLIND_STATE_ONE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ä�л��׶�һ����NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* �׶�һ�Ƚ�ʱ�� */
    VOS_INT16                               shwWorstRscpValue;                  /* ���RSCP�ź�����ֵ */
    VOS_INT16                               shwWorseRscpValue;                  /* �ϲ�RSCP�ź�����ֵ */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* ���յ����ź�ǿ���½��о����� */
}UCOM_NV_W_BLIND_STATE_ONE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߽���DPDT���ر���ʱ�������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaOffToAntExchangeTime;          /* �ر�PA�����DPDT�ź�ʱ�� */
    VOS_UINT16                              uhwAntExchangeToPaOnTime;           /* ���DPDT�źŵ���PAʱ�� */
}UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_W_BLIND_STATE_TWO_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ä�л��׶ζ�����NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateTwoTime;                    /* �׶ζ��Ƚ�ʱ�� */
    VOS_UINT16                              uhwReserved;                        /* �����ֶ� */
    VOS_UINT16                              auhwFrozenTime[4];                   /* �����л����ᱣ��ʱ�� */
}UCOM_NV_W_BLIND_STATE_TWO_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߽���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwWcdmaAntPassThroughCtrlWord;      /* ����ֱͨʱ��GPIO������ */
    VOS_UINT32                              uwWcdmaAntSwapCtrlWord;             /* ���߽���ʱ��GPIO������ */
}UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߽���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwWcdmaAntMasPassThroughTasPassThroughCtrlWord;      /* ����MAS=0,TAS=0ʱ��GPIO������ */
    VOS_UINT32                              uwWcdmaAntMasPassThroughTasSwapCtrlWord;             /* ����MAS=0,TAS=1ʱʱ��GPIO������ */
    VOS_UINT32                              uwWcdmaAntMasSwapTasPassThroughCtrlWord;             /* ����MAS=1,TAS=0ʱ��GPIO������ */
    VOS_UINT32                              uwWcdmaAntMasSwapTasSwapCtrlWord;                    /* ����MAS=1,TAS=1ʱʱ��GPIO������ */
}UCOM_NV_W_TAS_CTRL_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_NONBLIND_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS���в����Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAlpha;                           /* alpha�˲����ӣ��˲���ʽ:shwFilterValue = shwFilterValue*(1-shwAlpha/10) + shwCurrentValue*shwAlpha/10; ����shwAlpha = ( PHY_INT16)uhwAlpha*/
    VOS_UINT16                              uhwEvaluateTime;                    /* ����ʱ��(��λΪ1ms) */
    VOS_INT16                               shwRscpHighThd;                     /* ������ */
    VOS_INT16                               shwRscpLowThd;                      /* ������ */
    VOS_UINT16                              uhwCountLowThd;                     /* Low Count ���� */
    VOS_UINT16                              uhwCountHighThd;                    /* High Count ���� */
    VOS_UINT16                              uhwCountTotalThd;                   /* Total Count ����  */
    VOS_UINT16                              uhReserve;                          /* 4�ֽڶ��� */

}UCOM_NV_W_TAS_NONBLIND_MEAS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_NONBLIND_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS���в����Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwAlpha;                           /* alpha�˲����� */
    UCOM_NV_W_ANT_PROTECT_PARA_STRU         stAntProtect;                       /* ���߱����׶β��� */
    UCOM_NV_W_MAIN_ANT_ESTIMATE_PARA_STRU   stAntEstimate;                      /* �������������� */
    UCOM_NV_W_DUAL_ANT_COMPARE_PARA_STRU    stAntCompare;                       /* ˫���߱Ƚϲ��� */
}UCOM_NV_W_TAS_NONBLIND_MEAS_PRE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_BLIND_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TASä�в����Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* �׶�һ�Ƚ�ʱ�� */
    VOS_INT16                               shwWorstRscpValue;                  /* ���RSCP�ź�����ֵ */
    VOS_INT16                               shwWorseRscpValue;                  /* �ϲ�RSCP�ź�����ֵ */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* ���յ����ź�ǿ���½��о����� */
    VOS_UINT16                              uhwStateTwoTime;                    /* �׶ζ��Ƚ�ʱ�� */
    VOS_UINT16                              uhwDeltaRscpValuetest;                  /* �����ֶ� */
    VOS_UINT16                              auhwFrozenTime[4];                  /* �����л����ᱣ��ʱ�� */
}UCOM_NV_W_TAS_BLIND_MEAS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_PHY_STATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS�����״̬�ϱ���������ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRscpThres;                   /* ���ں��ź�RSCP����ֵ(��λΪ0.125dbm) */
    VOS_INT16                               shwPoorRscpThres;                   /* ���ڲ��ź�RSCP����ֵ(��λΪ0.125dbm) */
    VOS_UINT16                              uhwSFailNum;                        /* S׼������ʧ�ܴ��� */
    VOS_UINT16                              uhwSPassNum;                        /* S׼�������ɹ����� */
    VOS_UINT16                              uhwRachFailNum;                     /* �漴��������ʧ�ܴ��� */
    VOS_UINT16                              uhwFachEstimateTime;                /* fach̬�������������1msΪ��λ */
}UCOM_NV_W_TAS_PHY_STATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS�����Searching̬����
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRssiThres;                   /* ���ں��ź�RSSI����ֵ(��λΪ0.125dbm) */
    VOS_INT16                               shwPoorRssiThres;                   /* ���ڲ��ź�RSSI����ֵ(��λΪ0.125dbm) */
    VOS_UINT16                              uhwDeltaRssiValue;                  /* ���߱Ƚ�������ֵ(��λΪ0.125dbm)�����ڵ��ڴ����������л� */
    VOS_UINT16                              uhwReserved;                        /* �����ֶ� */
}UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS�㷨���Ʋ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* �����״̬�ϱ��������� */
    UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingPara;                 /* ����������㷨���� */
    UCOM_NV_W_TAS_NONBLIND_MEAS_PRE_STRU    stTasNotBlindCtrl;                  /* TAS���в����Ŀ��Ʋ��� */
    UCOM_NV_W_TAS_BLIND_MEAS_STRU           stTasBlindCtrl;                     /* TASä�в����Ŀ��Ʋ���*/
}UCOM_NV_W_TAS_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_RF_CTRL_STRU
 Э����  :
 ASN.1���� : auwBandBlindSwitchMap�����ÿ��band�Ƿ�ʹ��TASä���㷨����bitmap��
             auwBandBlindSwitchMap[0]bit0����band1��bit1����band2���Դ����ơ�
             auwBandBlindSwitchMap[1]bit0����band33��bit1����band34���Դ����ơ�
             bitλΪ1�������bandʹ��ä���㷨������֮��
 �ṹ˵��  : TAS��Ƶ��ؿ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              auwBandBlindSwitchMap[2];           /* BAND�Ƿ�����ä�� */
    UCOM_NV_W_TAS_CTRL_WORD_PRE_STRU        stTasCtrlWord;                      /* �����л������� */
}UCOM_NV_W_TAS_RF_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_HARQ_OUT_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HARQ��������NV�ṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_BBP_HARQ_OUT_TYPE_ENUM_UINT16   enHarqOutType;                      /* HARQ�������� */
    VOS_UINT16                              uwReserve;
}UCOM_NV_HARQ_OUT_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DRX_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMA����ģDRX����
*****************************************************************************/
typedef struct
{
    UCOM_NV_DRX_CTRL_ENUM_UINT16           enMasterDrxEnableFlag;               /* ��ģDRX���Ʊ�־ */
    UCOM_NV_DRX_CTRL_ENUM_UINT16           enSlaveDrxEnableFlag;                /* ��ģDRX���Ʊ�־ */
}UCOM_NV_W_DRX_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_GCF_INIT_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫���߲����Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmRssiAgcSwitch;                /* GSM RSSI����AGC��ʼ���濪�� */
    VOS_UINT16                              uhwGsmRssiAgcGain;                  /* GSM RSSI AGC��ʼ��λ */
}UCOM_NV_GSM_GCF_INIT_GAIN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_VIRTUAL_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM ����Ƶ��ʹ�ܱ�־���ٽ�Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmVirtualBand;                     /* 0-��֧������Ƶ�η���; 1-�ɵ�����Ƶ�η�����2-�µ�����Ƶ�η��� */
    VOS_UINT16                           uhwGsmFreqBound;                       /* B3L��B3HƵ��ŷֽ�� */
}UCOM_NV_GSM_VIRTUAL_BAND_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_CTUNE_LUT_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM����Ctune����Lut����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmTxCtuneLutCtrl;
}UCOM_NV_GSM_TX_CTUNE_LUT_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_EXT_STRONG_NCELL_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM����������ǿ�����ĵ�ƽ����
*****************************************************************************/
typedef struct
{
    VOS_INT16                            shwGsmExtStrongNcellThresh;            /* GSM����������ǿ�����ĵ�ƽ���� */
}UCOM_NV_GSM_EXT_STRONG_NCELL_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_SSC_CONFIG_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM SSC NV ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                            uhwGsmSscSupportFlag;                /* GSM SSC���ؿ��� */
    VOS_UINT16                            uhwBlackThreshold;                   /* ������С����õ���ֵ */
    VOS_UINT16                            uhwC2Threshold;                      /* ����C2ֵ���ڷ���С����ֵ */
    VOS_UINT16                            uhwC1Threshold;                      /* ����С��C1��ֵ */
    VOS_UINT16                            uhwRxlevAThreshold;                  /* ����С�����յ�ƽ��ֵ */
    VOS_UINT16                            uhwReserved;
}UCOM_NV_GSM_SSC_CONFIG_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_TX_CTUNE_LUT_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMA����Ctune����Lut����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwWcdmaTxCtuneLutCtrl;
}UCOM_NV_WCDMA_TX_CTUNE_LUT_CTRL_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_CHANNEL_WBBP_GAP_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC����NV��,WBBP Gap����ͨ�����ò���,��ӦWBBP�ӿ�˵����"��ͨ������"
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwT1ForIdlePch;                                         /* idlepch̬T1�ӳ�����,��λchip */
    VOS_UINT16          uhwT2ForIdlePch;                                         /* idlepch̬T2�ӳ�����,��λchip */
    VOS_UINT16          uhwT3ForIdlePch;                                         /* idlepch̬T3�ӳ�����,��λchip */
    VOS_UINT16          uhwT4ForIdlePch;                                         /* idlepch̬T4�ӳ�����,��λchip */
    VOS_UINT16          uhwT1ForFach;                                            /* FACH̬T1�ӳ�����,��λchip */
    VOS_UINT16          uhwT2ForFach;                                            /* FACH̬T2�ӳ�����,��λchip */
    VOS_UINT16          uhwT3ForFach;                                            /* FACH̬T3�ӳ�����,��λchip */
    VOS_UINT16          uhwT4ForFach;                                            /* FACH̬T4�ӳ�����,��λchip */
    VOS_UINT16          uhwT1ForDch;                                             /* DCH̬T1�ӳ�����,��λchip */
    VOS_UINT16          uhwT2ForDch;                                             /* DCH̬T2�ӳ�����,��λchip */
    VOS_UINT16          uhwT3ForDch;                                             /* DCH̬T3�ӳ�����,��λchip */
    VOS_UINT16          uhwT4ForDch;                                             /* DCH̬T4�ӳ�����,��λchip */

}UCOM_NV_CHANNEL_WBBP_GAP_CONFIG_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_WCDMA_CHANNEL_SWITCH_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC����NV��,ͨ����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwRfSignalSwitch;                                      /* RF�źŽ��� */
    VOS_UINT16          uhwMipiSignalSwitch;                                    /* MIPI�źŽ��� */
    VOS_UINT16          uhwAbbTxSignalSwitch;                                   /* ABB TX�źŽ��� */
    VOS_UINT16          uhwAbbRxSignalSwitch;                                   /* ABB RX�źŽ��� */
    VOS_UINT16          uhwPmuSignalSwitch;                                     /* PMU�źŽ��� */
    VOS_UINT16          uhwAptSignalSwitch;                                     /* APT�źŽ��� */
}UCOM_NV_CHANNEL_SWITCH_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CHANNEL_UNBIND_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC����NV��,ͨ��BAND��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwMipiUnbindEn;                                         /* MIPI�ǰ�ʹ�� */
    VOS_UINT16          uhwMipiCh0Select;                                        /* MIPIͨ��0ѡ�� */
    VOS_UINT16          uhwMipiCh1Select;                                        /* MIPIͨ��1ѡ�� */
    VOS_UINT16          uhwAfcCh0Select;                                         /* AFCͨ��0ѡ�� */
    VOS_UINT16          uhwAfcCh1Select;                                         /* AFCͨ��1ѡ�� */
    VOS_UINT16          uhwAptCh0Select;                                         /* APTͨ��0ѡ�� */
    VOS_UINT16          uhwAptCh1Select;                                         /* APTͨ��1ѡ�� */
    VOS_UINT16          uhwPmuCh0Select;                                         /* PMUͨ��0ѡ�� */
    VOS_UINT16          uhwPmuCh1Select;                                         /* PMUͨ��1ѡ�� */
    VOS_UINT16          uhwAbbTxCh0Select;                                       /* ABB TXͨ��0ѡ��,6363ʹ�� */
    VOS_UINT16          uhwAbbTxCh1Select;                                       /* ABB TXͨ��1ѡ�� 6363ʹ��*/

}UCOM_NV_CHANNEL_UNBIND_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_MIPI_NOTCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi NOTCH �Ĵ�����ַ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;                     /* Nothc Mipi�����ָ�����uhwNotchControlMode=2����3ʱ��Ч */
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_MIPI_NOTCH_CMD_NUMBER];/* Nothc MipiCmd��uhwNotchControlMode=2����3ʱ��Ч */
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_MIPI_NOTCH_DATA_NUMBER];     /* Nothc MipiData��uhwNotchControlMode=2����3ʱ��Ч */
}UCOM_NV_GSM_MIPI_NOTCH_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_NOTCH_POWER_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  NOTCH POWER COMP
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwNotchPowerThreshold;             /* Notch���书�ʴ��ڸ�ֵʱ�����з��书�ʲ��� */
    VOS_INT16                               shwNotchPowerComp;                  /* Notch���书�ʲ���ֵ */
}UCOM_NV_GSM_NOTCH_POWER_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߿����˲���ͨ���Ŀ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwNotchSupportFlag;                /* DCS1800 TX NOTCH����֧�ֱ�־��1��ʾ֧�֣�0��ʾ��֧�� */
    VOS_UINT16                              uhwNotchControlMode;                /* NOTCH���Ʒ�ʽ:1��ʾGPIOģʽ��2��ʾMipi��ʽ��3��ʾGPIO+MIPI��Ϸ�ʽ */
    VOS_UINT32                              uwNotchGpioSetValue;                /* Nothc GPIO����ֵ��uhwNotchControlMode=1����3ʱ��Ч */
    VOS_UINT32                              uwNotchGpioDefaultValue;            /* Nothc GPIO����ֵ��uhwNotchControlMode=1����3ʱ��Ч */
    UCOM_NV_GSM_MIPI_NOTCH_STRU             stNotchMipi;                        /* ����NOTCHͨ��MIPI�ӿڿ��Ƶ�ַ */
    UCOM_NV_GSM_NOTCH_POWER_COMP_STRU       stNotchPowerComp;                   /* Notch���书�ʲ��� */
}UCOM_NV_GSM_NOTCH_CHAN_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DFS����NV��,��̬��Ƶ����,ֻ�޸ĺ���V7R2��V9R1
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uwDdrFreq;                                        /* DDRƵ������(��λKHz)  */
    VOS_UINT32          uwCcpuFreq;                                       /* CCPUƵ������(��λKHz) */
    VOS_UINT32          uwBusFreq;                                        /* ����Ƶ������(��λKHz) */

}UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MODEM_DFS_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DFS����NV��,ֻ�޸ĺ���V7R2��V9R1
*****************************************************************************/
typedef struct
{
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stCsCfg;                                          /* ����ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stDrxCfg;                                         /* ����ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stFachCfg;                                        /* FACH̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stHspaCfg;                                        /* HSPA����ҵ��ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stR99PsCfg;                                       /* R99����ҵ��ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveWorkCfg;                                   /* ��ģ����״̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveSleepCfg;                                  /* ��ģ˯��״̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stMinCfg;                                         /* ��С��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stNoSignalCfg;                                    /* �������Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stReserved;                                       /* ������Profile����ֵ */
}UCOM_NV_W_MODEM_DFS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_CS_INTRA_STEP23_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ������С����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCsStep23SlotNum;                 /* DRX̬��Ƶ������С������step23��ʱ϶ͷ��������ʼֵΪ1 */
    VOS_UINT16                              uhwCsStep23Period;                  /* DRX̬��Ƶ������С���������ڣ���ʼֵΪ3072֡����30.72s */
}UCOM_NV_W_CS_INTRA_STEP23_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_QPC_REGDEFAULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : QPC NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwDefaultCloseTime;                 /* Ĭ�Ϲر�ʱ��     Ĭ��80(��λ ֡)��0����QPCδʹ�� */
    VOS_UINT16                      uhwDefaultGuardTime;                 /* Ĭ�ϱ�������ʱ�� Ĭ��20(��λ ֡) */
    VOS_UINT16                      uhwDefaultOpenTime;                 /* Ĭ�����ݴ���ʱ�� Ĭ��40(��λ ֡) */

    VOS_UINT16                      uhwReserve;
}UCOM_NV_QPC_REGDEFAULT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_MODEM_DFS_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DFS����NV��,ֻ�޸ĺ���V7R2��V9R1
*****************************************************************************/
typedef struct
{
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stCsCfg;                                          /* ����ҵ��ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stPsCfg;                                          /* ����ҵ��ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stDrxCfg;                                         /* ����ģʽ��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stTuningCfg;                                      /* tuning dch״̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSearchingCfg;                                   /* ����ģʽ������ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveWorkCfg;                                   /* ��ģ����״̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stSlaveSleepCfg;                                  /* ��ģ˯��״̬��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stMinCfg;                                         /* ��С��Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stNoSignalCfg;                                    /* �������Profile����ֵ */
    UCOM_NV_SYS_MODEM_DFS_CONFIG_STRU          stReserved;                                       /* ������Profile����ֵ */

}UCOM_NV_G_MODEM_DFS_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TUNER_GPIO_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϊgpio tunerʹ�ã��ݲ�����Tx/Rx��Ԥ��resvered bit������չ��
             ��Ч��ʱ��(Tx:Nv�����ã�RX:��ǰ150us)��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwGpio;                         /* ��Ӧǰ���߿� */
    VOS_UINT32                                  uwResvered;
}UCOM_NV_GSM_TUNER_GPIO_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PHASE_ERROR_STANDARD_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CMUʹ��standardģʽ����gmsk phase errorʱ����Ҫ���ô�NV��Ϊ1��
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwMode;                                                /* CMUʹ��standardģʽ����gmsk phase errorʱ����Ҫ���ô�NV��Ϊ1 */
}UCOM_NV_GSM_PHASE_ERROR_STANDARD_MODE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RF_INTERFERE_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TDS/LTE�����߿���,Ŀ���Ǳ���B39��B3H�ĸ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwFuncOn;                      /* 0-��ʹ�ܣ�1-ʹ�� */
    VOS_UINT32                                  uwGpioMask;                     /* �߿���� */
    VOS_UINT32                                  uwGpioRxValue;                  /* �ر�TDS/LTE������߿� */
    VOS_UINT32                                  uwGpioDefaultValue;             /* TDS/LTE������߿�Ĭ��ֵ */
}UCOM_NV_GSM_RF_INTERFERE_CONTROL_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_PA_MIPI_WORD_STRU
 Э����  :
 �ṹ˵��  : ����һЩmipi���ܹ���ָ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_PA_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_PA_MIPI_DATA_MAX_NUM];
}UCOM_NV_PA_MIPI_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU
 Э����  :
 �ṹ˵��  : PA��MIPIָ��
*****************************************************************************/
typedef struct
{
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOn;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOff;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainH;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainM;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaGainL;
}UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ET_MIPI_WORD_STRU
 Э����  :
 �ṹ˵��  : ����һЩmipi���ܹ���ָ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU                   astMipiCmd[UCOM_NV_ET_MIPI_CMD_MAX_NUM];
    UCOM_NV_MIPI_BYTE_DATA_STRU             astMipiData[UCOM_NV_ET_MIPI_DATA_MAX_NUM];
}UCOM_NV_ET_MIPI_WORD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU
 Э����  :
 �ṹ˵��  : Et��MIPIָ��
*****************************************************************************/
typedef struct
{
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOn;                         /* ET������mipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtOff;                        /* ET�����ر�mipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiEtMode;                       /* ET��������ΪET ģʽmipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiMAptMode;                     /* ET��������ΪM APT ģʽmipi������ */
    UCOM_NV_ET_MIPI_WORD_STRU               stMipiLAptMode;                     /* ET��������ΪL APT ģʽmipi������ */
}UCOM_NV_W_RFFE_MIPI_ET_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_MIPI_SINGLE_CMD_STRU
 Э����  :
 �ṹ˵��  : ָ��һ��MIPIָ��Ľṹ
*****************************************************************************/
typedef struct
{
    UCOM_NV_MIPI_CMD_STRU                   stMipiCmd;
    UCOM_NV_MIPI_BYTE_DATA_STRU             stMipiData;
}UCOM_NV_MIPI_SINGLE_CMD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_G_MIPI_PA_TIMING_STRU
 Э����  :
 �ṹ˵��  : MIPI PA timing
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  uhwMipiPaInitTiming;
    VOS_UINT16                  uhwMipiPaGainSetTiming;
    VOS_UINT16                  uhwMipiPaTrigTiming;
    VOS_UINT16                  uhwMipiPaOffTiming;
    VOS_UINT16                  uhwMipiPaMultiSlotGainSetTiming;
    VOS_UINT16                  uhwMipiPaMultiSlotTrigTiming;
    VOS_UINT16                  uhwResvered3;
    VOS_UINT16                  uhwResvered2;
    VOS_UINT16                  uhwResvered1;
    VOS_UINT16                  uhwResvered0;
}UCOM_NV_G_MIPI_PA_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_RFFE_MIPI_PA_CTRL_STRU
 Э����  :
 �ṹ˵��  : PA��MIPIָ��
*****************************************************************************/
typedef struct
{
    UCOM_NV_G_MIPI_PA_TIMING_STRU           stGsmMipiPaTiming;
    UCOM_NV_G_MIPI_PA_TIMING_STRU           stEdgeMipiPaTiming;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaInit;
    UCOM_NV_PA_MIPI_WORD_STRU               astGsmMipiPaPclGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
    UCOM_NV_PA_MIPI_WORD_STRU               astEdgeMipiPaPclGain[UCOM_NV_GSM_LINEAR_PA_GAIN_NUM];
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaTrigger;
    UCOM_NV_PA_MIPI_WORD_STRU               stMipiPaOff;
}UCOM_NV_G_RFFE_MIPI_PA_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi ant �Ĵ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU               astAntMipiCmd[UCOM_NV_MAX_MIPI_ANT_CMD_NUMBER];
    UCOM_NV_MIPI_BYTE_DATA_STRU         astAntMipiData[UCOM_NV_MAX_MIPI_ANT_DATA_NUMBER];
}UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ANT_SWITCH_MIPI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi ant �Ĵ���������
*****************************************************************************/
typedef struct
{
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stMainAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stDivAntMipiCtrl;
}UCOM_NV_W_ANT_SWITCH_MIPI_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_ANT_SWITCH_MIPI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : mipi ant �Ĵ���������
*****************************************************************************/
typedef struct
{
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stOpenRxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stOpenTxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stCloseRxAntMipiCtrl;
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU      stCloseTxAntMipiCtrl;
}UCOM_NV_G_ANT_SWITCH_MIPI_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DSDS_PS_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : V8R1 DSDS����NV���������DSDSģʽ��GSM����������RCM����RF��Դʱ��������ռ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwPsPrmptPeriod;                /* PS���޳��������ռͳ�����ڣ���λ32Kϵͳʱ��CLK������Ĭ��ֵ:0x1fffffff */
    VOS_UINT32                                  uwPsPrmptTimeThd;               /* PS���޳����񵥴α���ռʱ�����ޣ���λ32Kϵͳʱ��CLK������Ĭ��ֵ:0x1fffffff */
    VOS_UINT32                                  uwPsTotalPrmptTimeThd;          /* PS���޳������������ۼƱ���ռʱ�����ޣ���λ32Kϵͳʱ��CLK������Ĭ��ֵ:0x1fffffff */
    VOS_UINT32                                  uwReserved1;                    /* ����1 */
    VOS_UINT16                                  uhwReserved2;                   /* ����2 */
    VOS_UINT16                                  uhwReserved3;                   /* ����3 */
}UCOM_NV_GSM_DSDS_PS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_PHY_MODE_DSDS_FLAG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : V8R1 DSDS����NV��,�������������Ϊ0��˫���������������DSDA��DSDS
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 uhwGsmDsdsFlag;                  /* ������������Ϊ0��˫�������� 0:����DSDA,1:����DSDS */
    VOS_UINT16                                 uhwWcdmaDsdsFlag;                /* ������������Ϊ0��˫�������� 0:����DSDA,1:����DSDS */
    VOS_UINT16                                 uhwRsvDsdsFlag;                  /* ���� */
}UCOM_NV_PHY_MODE_DSDS_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_ANT_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ʹ�ܱ�־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwAntShareEn;                  /* 0-��֧��; 1-֧�� */
}UCOM_NV_ANT_SHARE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_VIRTUAL_BAND_ANT_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ƶ�ε����߿�������
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU                      stGsmVirtualBandRfConfig;       /* ����Ƶ�ε����߿������� */
}UCOM_NV_GSM_VIRTUAL_BAND_ANT_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_PHY_MODE_DSDS_FLAG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : V8R1 DSDS����NV��,���е��������˲�ʹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 uhwGsmTxLpfEn;                   /* ���е��������˲�ʹ�� 0:����ʹ��,1:����ʹ�� */
    VOS_UINT16                                 uhwRsv;                          /* ���� */
}UCOM_NV_GSM_TX_LPF_EN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM˫�����л�GPIO������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           uwGsmAntThroughCtrlWord;               /* �����ߵ�GPIO������ */
    VOS_UINT32                           uwGsmAntSwapCtrlWord;                  /* �����ߵ�GPIO������ */
    VOS_UINT32                           uwGsmDualAntClearMask;                 /* ���߿���������� */
}UCOM_NV_GSM_TAS_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM˫�����л�TAS+MAS GPIO������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           uwGsmAntTasOnlyThroughCtrlWord;        /* ����00(TAS=0 MAS=0)��GPIO������ */
    VOS_UINT32                           uwGsmAntTasOnlySwapCtrlWord;           /* ����01(TAS=1 MAS=0)��GPIO������ */
    VOS_UINT32                           uwGsmAntMasThroughCtrlWord;            /* ����10(TAS=0 MAS=1)��GPIO(G0��G1��ͬ) */
    VOS_UINT32                           uwGsmAntMasSwapCtrlWord;               /* ����11(TAS=1 MAS=1)��GPIO������(G0��G1��ͬ) */
    VOS_UINT32                           uwGsmDualAntClearMask;                 /* ���߿����������(G0��G1��ͬ) */
}UCOM_NV_GSM_TAS_MAS_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ���Ƿ�֧��Ia��Ib(IaָTAS_DPDT=passthrough��MAS�Ƚ�״̬,IbָTAS_DPDT=swap��MAS�Ƚ�״̬)
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwGsmMasBandSupportIa;                /* Ƶ���Ƿ�֧��Ia(��4 bit��ʾGSM�ĸ�Ƶ�� 0-��֧�� 1-֧��) */
    VOS_UINT16                           uhwGsmMasBandSupportIb;                /* Ƶ���Ƿ�֧��Ib(��4 bit��ʾGSM�ĸ�Ƶ�� 0-��֧�� 1-֧��) */
}UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_RF_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM˫�����л�Rf����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_CTRL_WORD_STRU      stGsmTasMasCtrlWord;                /* TAS MAS DPDT GPIO������ */
    UCOM_NV_GSM_MAS_BAND_SUPPORT_STRU       stGsmMasBandSupport;                /* Ƶ���Ƿ�֧��Ia��Ib */
}UCOM_NV_GSM_TAS_RF_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫�����л����������������׶β���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmAntEstimatePeriodNum;         /* ͳ�����ڸ��� */
    VOS_INT16                               shwGsmAntEstimatePowerCmpThreshold; /* �����о����� */
}UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫�����л��������������ȽϽ׶β���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGsmAntCompareCollectTime;         /* �ɼ�ʱ�� */
    VOS_UINT16                              uhwGsmAntCompareFirstPeriodNum;     /* ״̬1��ͳ�����ڸ��� */
    VOS_UINT16                              uhwGsmAntCompareSecondPeriodNum;    /* ״̬2��ͳ�����ڸ��� */
    VOS_UINT16                              uhwGsmAntCompareThirdPeriodNum;     /* ״̬3��ͳ�����ڸ��� */
    VOS_INT16                               shwGsmAntCompareFirstPowerCmpThreshold;  /* ״̬1�������о����� */
    VOS_INT16                               shwGsmAntCompareSecondPowerCmpThreshold; /* ״̬2�������о����� */
    VOS_INT16                               shwGsmAntCompareThirdPowerCmpThreshold;  /* ״̬3�������о����� */
}UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CS_DCH˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmDualAntAlphaPara;             /* ˫�����л�ƽ���˲�ϵ�� */
    VOS_UINT16                              uhwRsv;
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU  stGsmPriAntEstimatePara;            /* ˫�����л����������������׶β��� */
    UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU  stGsmDualAntComparePara;            /* ˫�����л��������������ȽϽ׶β��� */
    VOS_UINT32                              uwGsmAntHandleDelayPara;            /* ˫�����л���ĳ��Ͳ��� */
}UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ACCESS̬˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwRaCntThreshold;                  /* RA�������� */
    VOS_UINT16                              uhwRsv;
}UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IDLE̬˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwC1FailCntThreshold;              /* C1_fail�¼��о��������� */
    VOS_UINT16                              uhwC1PassCntThreshold;              /* C1_pass�¼��о��������� */
}UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SEARCHING̬˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                              shwQualityLowThreshold;              /* TAS_SEARCHING̬������������� */
    VOS_INT16                              shwQualityHighThreshold;             /* TAS_SEARCHING̬������������� */
    VOS_INT16                              shwDiffValue;                        /* TAS_SEARCHING̬���������ֵ */
    VOS_UINT16                             uhwRsv;
}UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwSignalPoorThreshold;             /* �ϱ�RCM�ź�POOR���� */
    VOS_INT16                               shwSignalGoodThreshold;             /* �ϱ�RCM�ź�GOOD���� */
    UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU   stGsmDualAntCsDchPara;              /* ˫�����л�CSDCH���� */
    UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU   stGsmDualAntAccessPara;             /* ˫�����л�ACCESS���� */
    UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU     stGsmDualAntIdlePara;               /* ˫�����л�IDLE���� */
    UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU     stGsmDualAntSearchingPara;          /* ˫�����л�SEARCHING���� */
}UCOM_NV_GSM_TAS_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_ESTIMATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫�����л����������������׶β���
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU      stActiveTasEstimate;            /* ���ص������׶β��� */
    UCOM_NV_GSM_PRI_ANT_ESTIMATE_PARA_STRU      stPassiveMasEstimate;           /* ����MAS�������׶β��� */
}UCOM_NV_GSM_TAS_MAS_ESTIMATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : compare�׶β������������� Ia Ib II IIa������Ia Ib
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGsmAntCompareCollectTime;         /* �ɼ�ʱ�� */
    VOS_UINT16                              uhwGsmDualAntAlphaPara;             /* ˫�����л�ƽ���˲�ϵ�� */
    VOS_UINT16                              uhwCountTotalNum;                   /* �ܵ��ϱ����ڼ������� */
    VOS_UINT16                              uhwCountHighNum;                    /* ��ֵ�����޼������� */
    VOS_UINT16                              uhwCountLowNum;                     /* �ܵ��ϱ����ڼ������� */
    VOS_INT16                               shwCountHighPowerDletaThreshold;    /* �����޼�����������ֵ���� */
    VOS_INT16                               shwCountLowPowerDletaThreshold;     /* �����޼�����������ֵ���� */
}UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TAS�ıȽϽ׶�NV����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIaPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIbPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stTasStateIIPara;
}UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MAS�ıȽϽ׶�NV����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIaPara;
    UCOM_NV_GSM_TAS_MAS_SUB_COMPARE_PARA_STRU  stMasStateIbPara;
}UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_COMPARE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : compare�л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwGoodEnoughPowerThreshold;    /* �����㹻���������� */
    VOS_UINT16                                  uhwRsv;
    UCOM_NV_GSM_ACTIVE_TAS_COMPARE_PARA_STRU    stActiveTasComparePara;         /* ����TAS�ıȽϽ׶β��� */
    UCOM_NV_GSM_PASSIVE_MAS_COMPARE_PARA_STRU   stPassiveMasComparePara;        /* ����MAS�ıȽϽ׶β��� */
}UCOM_NV_GSM_TAS_MAS_COMPARE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_DELAY_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DELAY����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwActiveTasDelayPara;              /* ����TAS�ĳ��Ͳ���,��λms */
    VOS_UINT16                              uhwPassiveMasDelayPara;             /* ����MAS�ĳ��Ͳ���,��λms */
}UCOM_NV_GSM_TAS_MAS_DELAY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DUAL_ANT_CS_DCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CS_DCH˫�����л�����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_TAS_MAS_ESTIMATE_PARA_STRU  stGsmPriAntEstimatePara;            /* ˫�����л����������������׶β��� */
    UCOM_NV_GSM_TAS_MAS_COMPARE_PARA_STRU   stGsmDualAntComparePara;            /* ˫�����л��������������ȽϽ׶β��� */
    UCOM_NV_GSM_TAS_MAS_DELAY_PARA_STRU     stGsmDualAntDelayPara;              /* ˫�����л���ĳ��Ͳ��� */
}UCOM_NV_GSM_TAS_MAS_CS_DCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TAS_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˫�����л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwSignalPoorThreshold;             /* �ϱ�RCM�ź�POOR���� */
    VOS_INT16                               shwSignalGoodThreshold;             /* �ϱ�RCM�ź�GOOD���� */
    UCOM_NV_GSM_TAS_MAS_CS_DCH_PARA_STRU    stGsmDualAntCsDchPara;              /* TAS+MAS˫�����л�CSDCH����(TAS MAS�ڲ�����) */
    UCOM_NV_GSM_DUAL_ANT_ACCESS_PARA_STRU   stGsmDualAntAccessPara;             /* ˫�����л�ACCESS����(TAS MAS����) */
    UCOM_NV_GSM_DUAL_ANT_IDLE_PARA_STRU     stGsmDualAntIdlePara;               /* ˫�����л�IDLE����(TAS MAS����) */
    UCOM_NV_GSM_TAS_SEARCHING_PARA_STRU     stGsmDualAntSearchingPara;          /* ˫�����л�SEARCHING����(TAS MAS����) */
}UCOM_NV_GSM_TAS_MAS_SCHL_PARA_STRU;

/*****************************************************************************
�ṹ��    : UCOM_NV_W_CS_ANT2_CTRL_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2014��12��30��
    ��    ��   : z68255
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCsAnt2AutoSwitch;                    /* ������̬�ּ����� */
    VOS_UINT16                          uhwFrameThreshold;                      /* Frame�о�����  */
    VOS_INT16                           shwSirOpenThreshold;                    /* SIRͳ�Ʒ�Open�о����ޣ���λ0.01db */
    VOS_INT16                           shwTpcOpenThreshold;                    /* TPCͳ�Ʒ�Open�о����ޣ��ٷֱ�*100 */
    VOS_INT16                           shwSirCloseThreshold;                   /* SIRͳ�Ʒ�Close�о����ޣ���λ0.01db  */
    VOS_UINT16                          uhwErrBlocksToClose;                    /*BLER�����طּ��о�ʱ�����ﵽĿ�������������ޣ��ٷֱ�*100*/
    VOS_UINT16                          uhwErrBlocksToOpen;                     /*BLER�������ּ��о�ʱ�����ﵽĿ�������������ޣ��ٷֱ�*100*/
    VOS_UINT16                          uhwSnapNumberToJudge;                   /*BLER�����о�ʱ����������Сͳ�ƿ���*/
    VOS_UINT16                          uhwBlerJudgeFlag;                       /*1ΪBLER������0ΪSIR����*/
    VOS_UINT16                          uhwErrorSnapClose;                      /*BLER�����طּ��о�ʱ��������������*/
    VOS_UINT16                          uhwErrorSnapOpen;                       /*BLER�������ּ��о�ʱ��������������*/
    VOS_UINT16                          uhwRsv0;                                /*����*/
}UCOM_NV_W_CS_ANT2_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_IDLE_ANT2_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMA��̬�ּ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwIdleAnt2AutoSwitch;                  /* IDLE��̬�ּ����� */
    VOS_INT16                           shwRSCPThreshold;                       /* RSCP����,����1/8�����޷� */
    VOS_INT16                           shwECN0Threshold;                       /* ECN0����,����1/8�����޷� */
    VOS_UINT16                          uhwAlphaThreshold;                      /* Alpha filter ���� */
}UCOM_NV_W_IDLE_ANT2_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_T313_BACK_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : T313����ֵ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwT313BackEn;                          /* T313���˿��ƿ��� */
    VOS_UINT16                          uhwT313BackValue;                       /* T313����ֵ����λ10ms */
    VOS_UINT16                          uhwT313MinValue;                        /* T313��Сֵ����λ10ms */
    VOS_UINT16                          uhwReserved;                            /* ���� */
}UCOM_NV_W_T313_BACK_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SYNC_MODULE_OPTIMIZE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͬʧ��ģ���Ż�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCloseUlDelayTime;                    /* ʧ�����ӳٹر����е�ʱ�䣬��λΪ10ms��0Ϊ�Ż��ر� */
    VOS_UINT16                          uhwQinQoutOptimizeSwitch;               /* QinQout�����Ż�����,0Ϊ�Ż��أ�1Ϊ�Ż��� */
}UCOM_NV_W_SYNC_MODULE_OPTIMIZE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_FET_DYN_DECODE_SNR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FET��̬��������ʱ϶����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwFetDecodeStartSlot;                  /* FET��̬��������ʱ϶ */
    VOS_UINT16                          uhwFetDecodeSnrThre;                    /* FET��̬��������ʱ϶��ӦSNR���� */
}UCOM_NV_W_FET_DYN_DECODE_SNR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_FET_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FET����NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                uhwFetEnable;                     /* FET���Կ���:�ر�Ϊ0,��Ϊ1 */
    VOS_UINT16                                uhwTestEnable;                    /* FET���Կ���:�ر�Ϊ0,��Ϊ1,�򿪵�����¿����ڲ���ģʽ�´�FET */
    VOS_UINT16                                uhwForceOpenRxEnable;             /* ����ǿ������:��ǿ��Ϊ0,ǿ��Ϊ1 */
    VOS_INT16                                 shwRxOpenPowerThresh;             /* ���д򿪹�������, ��λ0.1dBm */
    VOS_INT16                                 shwRxClosePowerThresh;            /* ���йرչ�������, ��λ0.1dBm */
    VOS_UINT16                                uhwRxOpenPowerEvaCntThresh;       /* ���йرյ��򿪹��ʳ���������������, ��λ֡ */
    VOS_INT16                                 shwRxOpenRscpThresh;              /* ���д�RSCP����, ��λ0.125dBm */
    VOS_INT16                                 shwRxCloseRscpThresh;             /* ���йر�RSCP����, ��λ0.125dBm */
    VOS_INT16                                 shwRxOpenEcn0Thresh;              /* ���д�Ecn0����, ��λ0.125dBm */
    VOS_INT16                                 shwRxCloseEcn0Thresh;             /* ���йر�Ecn0����, ��λ0.125dBm */
    VOS_UINT16                                uhwRxOpenEnergyEvaCntThresh;      /* ���йرյ�����������������������, ��λ֡ */
    VOS_INT16                                 shwOlpcSirTargetDelta;            /* �⻷����SirTarget����ֵ, ��λ0.01dBm */
    VOS_UINT16                                uhwFetBlindDynDecodeEnable;       /* ä����¶�̬����FET��������ʱ϶���أ���Ϊ1���ر�Ϊ0 */
    VOS_UINT16                                uhwFetNoBlindDynDecodeEnable;     /* ��ä����¶�̬����FET��������ʱ϶���أ���Ϊ1���ر�Ϊ0 */
    VOS_UINT16                                uhwCodedLenSrb;                   /* �������鳤�� */
    VOS_UINT16                                uhwSrbRmLocal;                    /* �����ŵ��������� */
    VOS_UINT16                                uhwTrch0RmLocal;                  /* �����ŵ�0�Ĵ������� */
    VOS_UINT16                                uhwReserved;                      /* ���� */
    VOS_UINT16                                auhwAbsTh[UCOM_NV_W_FET_DYN_DEC_SNR_NUM];
                                                                                /* ��ͬ���ʱ϶ʹ�õľ������� */
    VOS_UINT16                                auhwRelTh[UCOM_NV_W_FET_DYN_DEC_SNR_NUM];
                                                                                /* ��ͬ���ʱ϶ʹ�õ�������� */
    UCOM_NV_W_FET_DYN_DECODE_SNR_STRU         astBlindSnr1stDecTh[UCOM_NV_W_FET_BLIND_DYN_DEC_SNR_NUM];
                                                                                /* ä��ⲻͬ��������ʱ϶SNR���� */
    UCOM_NV_W_FET_DYN_DECODE_SNR_STRU         astNoBlindSnr1stDecTh[UCOM_NV_W_FET_NOBLIND_DYN_DEC_SNR_NUM];
                                                                                /* ��ä��ⲻͬ��������ʱ϶SNR���� */
}UCOM_NV_W_FET_CTRL_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PCH_DUMMY_DETECT_FLAG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : V8R1 dummy_pch�����ƽṹ��flag=0ʱ ������dummyPch��� =1ʱ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwGsmPchDummyDetectFlag;           /* dummy_pch��⿪����־λ */

}UCOM_NV_GSM_PCH_DUMMY_DETECT_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W PA�¶ȼ��ͨ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sChannel;
    VOS_UINT16                              usResvered;
}UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU;

typedef UCOM_NV_W_PA_TEMP_DET_CHANNEL_STRU UCOM_NV_CDMA_PA_TEMP_DET_CHANNEL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PA_TEMP_DET_CHANNEL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : G PA�¶ȼ��ͨ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sChannel;
    VOS_UINT16                              usResvered;
}UCOM_NV_GSM_PA_TEMP_DET_CHANNEL_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_DRX_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM����ģDRX����
*****************************************************************************/
typedef struct
{
    UCOM_NV_DRX_CTRL_ENUM_UINT16       enMasterDrxEnableFlag;               /* ��ģ����˯�� */
    UCOM_NV_DRX_CTRL_ENUM_UINT16       enSlaveDrxEnableFlag;                /* ��ģ����˯�� */
}UCOM_NV_GSM_DRX_CTRL_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_RX_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾ֧�ֵ�3G��2GƵ�Ρ�3G�ּ�֧�������ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          uhwRfSsiChannel;                        /* RFICѡ��*/

    VOS_UINT16                          uhwRfOutPortGroup;                      /* RFIC������ּ�ͨ��ѡ��*/

    VOS_UINT16                          uhwRfMainPort;                          /* RFIC����������ڶ˿�ѡ��*/

    VOS_UINT16                          uhwAbbChannel;                          /* ABBͨ��ѡ�� */

    VOS_UINT16                          uhwAbbMainPath;                         /* ABBͨ���ڣ����ּ�·��ѡ��*/

    VOS_UINT16                          uhwMixerSel;                            /* Mixerѡ��ͨ��ѡgroup��ʵ��*/

    VOS_UINT16                          uhwPllSel;                              /* PLLѡ�� */

    VOS_UINT16                          uhwReserved;

}UCOM_NV_RF_RX_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_TX_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾ֧�ֵ�3G��2GƵ�Ρ�3G�ּ�֧�������ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwAbbChannel;                      /* ABBͨ��ѡ�� */

    VOS_UINT16                          uhwRfSsiChannel;                    /* RFICѡ��*/

    VOS_UINT16                          uhwFbPin;                           /* RFIC��Tx�󶨣�FB Band pin,0:FB1,1:FB2 */

    VOS_UINT16                          uhwReserved;
}UCOM_NV_RF_TX_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_TRX_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾ֧�ֵ�3G��2GƵ�Ρ�3G�ּ�֧�������ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_RX_CONFIG_STRU           stRfRxConfig;

    UCOM_NV_RF_TX_CONFIG_STRU           stRfTxConfig;

}UCOM_NV_RF_TRX_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_RX_IQ_MISMATCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM�������У�����ӣ���λУ������
             ��������ʱ�����˲������ø�DBB����RXͨ������Ԥ�������ֲ�����ͨ��
             ��IQ mismatch��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwAmplitude;                           /* ���У�����ӣ�+-511 */
    VOS_INT16                           shwPhase;                               /* ��λУ�����ӣ�+-1023 */
}UCOM_NV_GSM_RX_IQ_MISMATCH_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_HD3_HD5_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���һ�����HD3/HD5У׼ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwBr;                                  /* HD3У׼ֵʵ�� */
    VOS_INT16                           shwBi;                                  /* HD3У׼ֵ�鲿 */
    VOS_INT16                           shwCr;                                  /* HD5У׼ֵʵ�� */
    VOS_INT16                           shwCi;                                  /* HD5У׼ֵ�鲿 */
}UCOM_NV_GSM_HD3_HD5_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_HD3_HD5_PCL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���һ��Ƶ���HD3/HD5У׼ֵ
*****************************************************************************/
typedef struct
{
    /* �ֱ���Max_PCL��Max_PCL+1��Max_PCL+2�������ʵȼ���HD3/HD5У׼��� */
    UCOM_NV_GSM_HD3_HD5_STRU            astPclHd3Hd5[UCOM_NV_GSM_TX_HD35_PCL_NUM];
}UCOM_NV_GSM_HD3_HD5_PCL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_HD35_ARFCN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���һ��Ƶ�ε�HD3/HD5У׼ֵ
            Br = 1/(A^2) ��(AΪ�����źŵĸ����ֵ)���㷨���ж��㻯��ʽ���£�
            ��������źŵ�RMSֵΪ282mv�������ֵA = 282*sqrt(2)mv
            ����HD3��Br =1/(A^2)=2^11/((0.282*��2)^2)=12877
            ����HD5��Cr =1/(A^4)=2^8/((0.282*��2))^4)=10121
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          auhwArfcn[UCOM_NV_GSM_TX_HD35_ARFCN_NUM];           /* �źŵ��и�����Ƶ��,����Ƶ�� */
    VOS_UINT16                          uhwReserved;

}UCOM_NV_GSM_HD35_ARFCN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_HD3_HD5_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���һ��Ƶ�ε�HD3/HD5У׼ֵ
            Br = 1/(A^2) ��(AΪ�����źŵĸ����ֵ)���㷨���ж��㻯��ʽ���£�
            ��������źŵ�RMSֵΪ282mv�������ֵA = 282*sqrt(2)mv
            ����HD3��Br =1/(A^2)=2^11/((0.282*��2)^2)=12877
            ����HD5��Cr =1/(A^4)=2^8/((0.282*��2))^4)=10121
*****************************************************************************/
typedef struct
{

    UCOM_NV_GSM_HD3_HD5_PCL_STRU        astChannelHd3Hd5[UCOM_NV_GSM_TX_HD35_ARFCN_NUM];    /* �ֱ��ŵ͡��С�������Ƶ���У׼��� */

}UCOM_NV_GSM_TX_HD3_HD5_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TX_IQ_SELF_CAL_6362_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Tx ��У׼NV
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxLoLeakageDciFixed;                 /*У׼Lo Leakageʱ�����õ�I·ֱ��ֵ*/

    VOS_UINT16                          uhwTxIqMismatchCalCntMax;               /*IQ Mismatch���У׼����*/

    VOS_UINT32                          uwTxLoLeakageCorrErrThrd;               /*У׼Lo Leakageʱ���ʧ������*/

    VOS_UINT32                          uwTxIqMismatchIrStopThrd;               /*IQ MismatchУ׼ֹͣ����*/

    VOS_UINT32                          uwTxIqMismatchIrFailThrd;               /*IQ MismatchУ׼ʧ������*/

}UCOM_NV_TX_IQ_SELF_CAL_6362_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_HD35_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Hd35��У׼��ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCouplerEn;                           /* Coupler�ⲿ���ػ���Rfic�ڲ����أ�1--Coupler�ⲿ���أ�0--Rfic�ڲ����� */
    VOS_UINT16                          uhwLowBandScale;                        /* ��Ƶ��У׼ֵ��Ϊ���ղ���ֵ��Ҫ��˵�ϵ������Ӳ����Ա��ȡ */
    VOS_INT16                           shwHd3FixedBrValue;                     /* Ĭ��ֵ12877 ����˵�����ṹ��ע�� */
    VOS_INT16                           shwHd5FixedCrValue;                     /* Ĭ��ֵ10121 ����˵�����ṹ��ע�� */
    VOS_UINT32                          uwHd3JudgeThd;                          /* Ĭ��ֵ24318 Hd3,Step3���о�����,�㷨˵������� */
    VOS_UINT32                          uwHd5JudgeThd;                          /* Ĭ��ֵ618 Hd5,Step3���о�����,�㷨˵������� */
    VOS_UINT32                          uwHd3Step2Thd;                          /* Ĭ��ֵ24318,Hd3��У׼Step2���о����� */
    VOS_UINT32                          uwHd5Step2Thd;                          /* Ĭ��ֵ618,Hd5��У׼Step2���о����� */
    VOS_UINT16                          uhwMrxRegValue;                         /* Mrx�Ĵ���������ֵ */
    VOS_UINT16                          uhwHighBandScale;                       /* ��Ƶ��У׼ֵ��Ϊ���ղ���ֵ��Ҫ��˵�ϵ������Ӳ����Ա��ȡ */
}UCOM_NV_GSM_HD35_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_VERSION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :RF�汾��NV��
*****************************************************************************/
typedef struct
{

    VOS_UINT32                          uwRfVersion;                            /* 0:RF6361;1:RF6362 */
}UCOM_NV_RF_VERSION_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_RF_CTRL_PORT_SEL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC����NV��,ͨ��BAND��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwAfcPortSelect    :4;                                    /* AFC�˿�ѡ�� */
    VOS_UINT32                          uwAptPortSelect    :4;                                    /* APT�˿�ѡ�� */
    VOS_UINT32                          uwRampPortSelect   :4;                                    /* PMU�˿�ѡ�� */
    VOS_UINT32                          uwReserved         :20;                                    /* ���� */
}UCOM_NV_RF_CTRL_PORT_SEL_STRU;

typedef UCOM_NV_RF_CTRL_PORT_SEL_STRU  UCOM_NV_CDMA_RF_CTRL_PORT_SEL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TCXO_CTRL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TCXO���������ص�NV��,

*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTcxoSrchTempHigh;                    /* ������������ĸ������� */
    VOS_INT16                           shwTcxoSrchTempLow;                     /* ������������ĵ������� */
    VOS_INT16                           shwUpdateTcxoTempHigh;                  /* �ϱ�AFC�ĸ������� */
    VOS_INT16                           shwUpdateTcxoTempLow;                   /* �ϱ�AFC�ĵ�������,�������Χ�ڲ��ϱ�AFC��ֵ */
    VOS_UINT16                          uhwTcxoDynamicMax;                      /* �����ϻ���TCXO��������������仯�� */
    VOS_UINT16                          uhwReserve;                             /* �����ֶ� */
}UCOM_NV_TCXO_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TCXO_AGING_THR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TCXO���������ص�NV��,

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          uhwGsmAfcCIThres;                       /* GSM��ΪAFC����������ֵ */
    VOS_UINT16                          uhwCompWithDynMax;                      /* �Ƿ񱣴�dynamic�ĸ��������ڿ�����һ�� */
    VOS_UINT16                          uhwCompWithDynMin;                      /* �Ƿ񱣴�dynamic�ĵ��������ڿ�����һ�� */
    VOS_UINT16                          uhwCompWithDynMax2;                     /* �Ƿ񱣴�dynamic�ĸ��������ڷǿ�����һ�� */
    VOS_UINT16                          uhwCompWithDynMin2;                     /* �Ƿ񱣴�dynamic�ĸ��������ڷǿ�����һ��  */
    VOS_UINT16                          uhwReserve;                             /* �����ֶ� */
}UCOM_NV_TCXO_AGING_THR_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_OPTIMIZE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Gģ�Ż��ṹ��ר��̬�����Ż����ƽṹ��flag=0ʱ ������Ĭ��ʹ��ԭ�з�����flag=1ʱ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwGsmDchFastSrchFlag   :1;              /* ר��̬�����Ż�������־λ lag=0ʱ ������Ĭ��ʹ��ԭ�з�����flag=1ʱ���� */
    VOS_UINT32                          uwGsmBchFast101Flag    :1;              /* ����״̬�¿���101�ı�־λ */
    VOS_UINT32                          uwGsmCellFastSrchFlag  :1;              /* ���������Ż� */
    VOS_UINT32                          uwGsmBchPageRptFlag    :1;              /* ����̬Ѱ����Ϣ�Ƿ��ϱ�GAS�Ŀ���;1-�������ϱ�;0-�⵽������Ϣ�ϱ� */
    VOS_UINT32                          uwGsmAdrxFlag          :1;              /* ADRX���� */
    VOS_UINT32                          uwSlaveGsmNcoFlag      :1;              /* ��ģNCO��ƫ���� */
    VOS_UINT32                          uwReserved2            :26;
}UCOM_NV_GSM_OPTIMIZE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_ANT_IDLE_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GPIO idleʱ϶���ߵ�����״̬
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwAntSwitch;                    /* ����ʱ϶ʱ���ߵĿ���ֵ */
    VOS_UINT32                                  uwReserved5;                    /* �����ֶ� */
    VOS_UINT32                                  uwReserved4;                    /* �����ֶ� */
    VOS_UINT32                                  uwReserved3;                    /* �����ֶ� */
    VOS_UINT32                                  uwReserved2;                    /* �����ֶ� */
    VOS_UINT32                                  uwReserved1;                    /* �����ֶ� */
    VOS_UINT32                                  uwReserved0;                    /* �����ֶ� */
}UCOM_NV_GSM_ANT_IDLE_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_WG_IQMISMATCH_CAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ˵��RFIC�Ļ���·��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfic0MrxAbbChannel    :8;                               /* RFIC0�������ӵ�ABBͨ��ѡ�� */
    VOS_UINT16                          uhwRfic0MrxAbbPath       :8;                               /* RFIC0�������ӵ�ABBͨ����ABB_A��ABB_Bѡ�� */
    VOS_UINT16                          uhwRfic1MrxAbbChannel    :8;                               /* RFIC1�������ӵ�ABBͨ��ѡ�� */
    VOS_UINT16                          uhwRfic1MrxAbbPath       :8;                               /* RFIC1�������ӵ�ABBͨ����ABB_A��ABB_Bѡ�� */
}UCOM_NV_WG_IQMISMATCH_CAL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_FEATURE_XPASS_EN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : XPASS��������ʹ��NV��0Ϊ�رգ�1Ϊ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         uhwXpassEnFlag;                          /* XPASS��������ʹ��NV��0Ϊ�رգ�1Ϊ�� */
    VOS_UINT16                         uhwReserve;
}UCOM_NV_GSM_FEATURE_XPASS_EN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_MAX_MIN_COEFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���̸�����dcxo�����С����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwMantissaMax[3];                      /* ���δ�����ֵa1,a2,a3��β�� */
    VOS_UINT32                          auwMantissaMin[3];                      /* ���δ����Сֵa1,a2,a3��β�� */
    VOS_UINT16                          auhwExponentMax[3];                     /* ���δ�����ֵa1,a2,a3��ָ�� */
    VOS_UINT16                          auhwExponentMin[3];                     /* ���δ����Сֵa1,a2,a3��ָ�� */
}UCOM_NV_DCXO_MAX_MIN_COEFF_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_EN_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET �Ƿ�֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwEtBandMask;                           /* bit0Ϊ1��ʾ֧��band1, ���� */
    VOS_UINT32                          uwEtBandMaskEx;
}UCOM_NV_W_ET_EN_MASK_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_EN_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD�Ƿ�֧��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwDpdBandMask;                          /* bit0Ϊ1��ʾ֧��band1, ���� */
    VOS_UINT32                          uwDpdBandMaskEx;
}UCOM_NV_W_DPD_EN_MASK_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_LUT_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT�л�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCnt;                            /* ��Ч���� */
    VOS_UINT16                          auhwLutSwitchThreshold[UCOM_NV_DPD_LUT_THERSHOLD_MAX_NUM]; /* �л�����,����ǹ���ģʽ����λ0.1dB�������APC Indexģʽ����0��ʼӳ��
                                                                                                       ����ֵ������0������8��С���� */
}UCOM_NV_W_DPD_LUT_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_STEP_V_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BBP��DPD LUT����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwDpdStepV[UCOM_NV_BBP_DPD_LUT_MAX_NUM];
}UCOM_NV_W_DPD_STEP_V_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DPD_CTRL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BBP���ݸ�NV��ȷ��ÿ��DPD���ʹ�ó���,BBP�ӿ��ṩ8��DPD���л�����Ϊ9����ÿ�ű����Ϊ64
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDpdIndexMode;                        /* 0: ����ģʽ; 1:Apc setting  */
    VOS_UINT16                          uhwReserved;
    UCOM_NV_W_DPD_LUT_THRESHOLD_STRU    stDpdThreshold;                         /* DPD LUT�л����� */
    UCOM_NV_W_DPD_STEP_V_STRU           stDpdStepV;
}UCOM_NV_W_DPD_LUT_THRESHOLD_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_LUT_CAL_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD��У׼ʱ�Ĺ��ʻ�RF������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCnt;                             /* ��Ч���� */
    VOS_INT16                           ashwDpdCalPower[UCOM_NV_DPD_LUT_MAX_NUM]; /* ÿ��DPD��У׼ʱ�Ĺ��ʻ�RF������,����ǹ���ģʽ����λ0.1dB�������APC Indexģʽ */
}UCOM_NV_W_DPD_LUT_CAL_POWER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DPD_MRX_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET DPD��У׼MRX������Ϣ,FbPin��PD��ͬ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMrxGain       :2;                     /* mrx gain */
    VOS_UINT32                          uwMrxVgaGain    :4;                     /* Rx_A Vga Gain */
    VOS_UINT32                          uwReserved1     :1;                     /*  */
    VOS_UINT32                          uwMrxDcAdjust   :2;                     /* MRXֱ������ */
    VOS_UINT32                          uwReserved2     :23;
}UCOM_NV_W_ET_DPD_MRX_CFG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_SELF_CAL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_LUT_CAL_POWER_STRU    stDpdCalPower;                          /* DPD��У׼��������ҪУ׼�Ĺ��ʵ� */
    VOS_UINT16                          auhwDpdLinearGainIndex[UCOM_NV_BBP_DPD_LUT_MAX_NUM];  /* DPD��У׼�����ж�Ӧÿ��DPD�������gain index,��Чֵ0-63���㷨�Ƽ�8����PA�й� */
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stReserved;                             /* ET ��DPDУ׼ʱ��MRX���ò��� */
    UCOM_NV_MIPI_COMM_STRU              stMipiReserved;                         /* ET ��DPDУ׼ʱ��ET����������Ҫ���� */
}UCOM_NV_W_DPD_SELF_CAL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_ET_DPD_MRX_CFG_STRU       stMrxCfgInfo;                           /* ET ��DPDУ׼ʱ��MRX���ò��� */
    UCOM_NV_MIPI_COMM_STRU              stEtDpdCalMipiCfg;                      /* ET ��DPDУ׼ʱ��ET����������Ҫ���� */
}UCOM_NV_W_ET_DPD_SELF_CAL_FE_CFG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_INT_TIME_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ֻ��ҪУ׼����ͨ·������ʱ�����Զ���������ʱĬ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwDataPathIntDelay;                    /* ����ͨ·������ʱ */
    VOS_UINT16                          uhwEtPathIntDelay;                      /* ����ͨ·������ʱ */
}UCOM_NV_W_ET_INT_TIME_DELAY_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_COMP_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDpdCompI;
    VOS_INT16                           shwDpdCompQ;
}UCOM_NV_W_DPD_COMP_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT ÿ�ű����Ϊ64
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_COMP_PARA_STRU        astDpdPara[UCOM_NV_DPD_LUT_MAX_LEN];
}UCOM_NV_W_DPD_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_LUT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT BBP�ӿ��ṩ8��DPD���л�����Ϊ9����ÿ�ű����Ϊ64
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_TABLE_STRU            astDpdLut[UCOM_NV_BBP_DPD_LUT_MAX_NUM];
}UCOM_NV_W_DPD_LUT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_PA_VCC_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPower;                                /* ���ʻ�APC index */
    VOS_INT16                           shwPaVcc;                                /* ��ѹ������ */
}UCOM_NV_W_ET_PA_VCC_DATA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_PA_VCC_LUT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Pa Vcc LUT
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_ET_PA_VCC_DATA_STRU       astEtPaVccLut[UCOM_NV_ET_LUT_MAX_LEN];  /* LUT���� */
}UCOM_NV_W_ET_PA_VCC_LUT_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD LUT���¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_TX_PA_TEMP_NUM];      /* P-Vcc LUT���¶Ȳ��� */
}UCOM_NV_W_ET_TIME_DELAY_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_ENVELOP_TIME_DELAY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time DelayУ׼���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnvelopTimeDelay;                    /* Et ����ͨ·Time Delay */
    VOS_UINT16                          uhwRslv;                                /* ���� */
}UCOM_NV_W_ET_ENVELOP_TIME_DELAY_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time Delay��ȡ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFreqChan;                             /* Ƶ�� */
    VOS_INT16                           shwEtDelayFreqComp;                     /* delay comp */
    VOS_UINT16                          uhwReserved;                            /* reserved; */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_TIME_DELAY_FREQ_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time DelayƵ����ȡ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEtTimeDelayCalEnable;
    VOS_UINT16                          uhwChannelNum;                          /* ÿ��Band��Ч���� */
    VOS_UINT32                          auwFreqChan[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et ����ͨ·Time Delay */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_CAL_CHAN_STRU;



/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_TIME_DELAY_FREQ_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time DelayƵ����ȡ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwChannelNum;                           /* ÿ��Band��Ч���� */
    UCOM_NV_W_ET_TIME_DELAY_FREQ_STRU   astEtTimeDelayFreq[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et ����ͨ·Time Delay */
}UCOM_NV_W_ET_TIME_DELAY_FREQ_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DELAY_FREQ_COMP_DEFAULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time DelayƵ����ȡ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwEtTimeDelayFreq[UCOM_NV_ET_DELAY_FREQ_COMP_MAX_NUM];/* Et ����ͨ·Time Delay */
}UCOM_NV_W_ET_DELAY_FREQ_COMP_DEFAULT_STRU;





/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPD�¶Ȳ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwTempComp[UCOM_NV_W_DPD_TEMP_COMP_NUM]; /*  */
}UCOM_NV_W_DPD_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_DPD_FREQ_TEMP_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DPDƵ��-�¶Ȳ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_DPD_TEMP_COMP_STRU        astTempCompFreqIndex[UCOM_NV_W_DPD_FREQ_COMP_NUM]; /*  */
}UCOM_NV_W_DPD_FREQ_TEMP_COMP_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_TIME_DELAY_CTRL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ET Time DelayУ׼����ϵ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDelayCalPower;                       /* ET Time DelayУ׼�Ĺ��� */
    VOS_INT16                           shwLowerOffset;                         /* ET Time Delay���� */
    VOS_INT16                           shwUpperOffset;                         /* ET Time Delay���� */
    VOS_INT16                           shwSweepOffset;                         /* ET Time DelayУ׼����ֵ */
}UCOM_NV_W_ET_TIME_DELAY_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_DELAY_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Et DelayУ׼��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCenterEnvelopTimeDelay;              /* delay������ֵ */
    VOS_UINT16                          uhwBinarySearchRangeOffset;             /* ���ַ�������offset */
    VOS_UINT16                          uhwSweepRange;                          /* ɨ�跶Χ */
    VOS_UINT16                          uhwSweepStep;                           /* ɨ�貽�� */
}UCOM_NV_W_ET_DELAY_CAL_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ET_GAIN_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���չ��ʲ������ʱ�����Խ�����Ϊ���ʺ͵�ѹ���������й�ϵV = P*Gain+GainOffet��
 ��ͬ����ģ�Gain, GainOffset������ͨ��У׼��ã�ͨ������뾲̬����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwGain;                                /* ET LUT ����б�� */
    VOS_INT16                           shwGainOffset;                          /* ET LUT ����ƫ�� */
}UCOM_NV_W_ET_GAIN_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TAS_DPDT_MIPI_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : tas mipi�Ĵ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwCmdValidCnt;
    UCOM_NV_MIPI_CMD_STRU               astTasDpdtMipiCmd[UCOM_NV_MAX_MIPI_TAS_CMD_NUMBER];   /* ������ */
    UCOM_NV_MIPI_BYTE_DATA_STRU         astTasDpdtMipiData[UCOM_NV_MAX_MIPI_TAS_DATA_NUMBER]; /* ���� */
}UCOM_NV_TAS_DPDT_MIPI_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TAS_DPDT_MIPI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : tas mipi�Ĵ���������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TAS_DPDT_MIPI_CTRL_WORD_STRU stTasDpdtThrough;                      /* ֱ̬ͨ������ */
    UCOM_NV_TAS_DPDT_MIPI_CTRL_WORD_STRU stTasDpdtSwap;                         /* ����̬������ */
}UCOM_NV_TAS_DPDT_MIPI_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NV parameters for CPROC 1x.
*****************************************************************************/
typedef struct
{
    /**
     * RF settling time in number of PCGs (1.25 ms)
     */
    VOS_INT32  slCproc1xRfSettlingTime;

    /**
     * Maximum number of pilots in the active set.
     * Does not really belong in NV but should be a common define for CAS, CPROC and CSDR.
     */
    VOS_INT32  slSupportActiveSetNum;

    /**
     * Size of the measurement window in q-chips
     */
    VOS_INT32  slCproc1xSmMeasWindowSize;

    /**
     * Size of the MPS window in q-chips
     */
    VOS_INT32  slCproc1xSmMpsWindowSize;

    /**
     * Size of the pilot search window in q-chips
     */
    VOS_INT32  slCproc1xSmPilotSearchWindowSize;

    /**
     * Maximum number of q-chips uwDelaySpreadRMS may change between two samples
     * if it shall be considered reliable.
     */
    VOS_INT32  slCproc1xSmMpsMaxChangeRmsThreshold;

    /**
     * Front and back guard interval length in q-chips
     */
    VOS_INT32  slCproc1xSmMpsGuardIntervalLength;

    /**
     * Threshold for selecting MPS window sliding algorithm in q-chips
     * if uwDelaySpreadRMS > CPROC_1X_SM_MPS_ALGORITHM_SELECT_THRESHOLD
     * then rule 1
     * else rule 2
     */
    VOS_INT32  slCproc1xSmMpsAlgorithmSelectThreshold;

    /**
     * How far to adjust the MPS window when rule 1 is selected, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule1SlideStep;

    /**
     * How far to adjust the MPS window when rule 2 is selected, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule2SlideStep;

    /**
     * Threshold for when to slide window when adjusting according to rule 2, in q-chip.
     */
    VOS_INT32  slCproc1xSmMpsRule2DeltaThreshold;

    /**
     * Level where a pilot is considered as valid.
     */
    VOS_INT32  slCproc1xPdbDetectedThreshold;
    VOS_INT32  slPsGoodPilotThreshold;

    /**
     * Number of times a pilot may be below CPROC_1X_PDB_DETECTED_THRESHOLD before it is removed from PDB.
     */
    VOS_INT32  slCproc1xPdbMaxAgeBelowThreshold;

    /**
     * Maximum number of CF neighbors to measure in one CF gap.
     */
    VOS_INT32  slCproc1xNumCfNeighToMeasure;

    /**
     * Maximum number of pilot searches in one CF gap.
     */
    VOS_INT32  slCproc1xNumCfNeighSearches;

    /**
     * Threshold to add IC pilot to IC in db.
     */
    VOS_INT32  slCproc1xIcAddMargin;

    /**
     * Threshold to remove IC pilot to IC in db.
     */
    VOS_INT32  slCproc1xIcRemoveMargin;

    /**
     * Does the platform support diversity antenna
     */
    VOS_INT32  slCproc1xDiversityAntenna;

    /**
     * Does the platform support interference cancellation
     */
    VOS_INT32  slCproc1xIcSupported;

    /**
     * ESS priorities for measurements
     */
    VOS_INT32  slCproc1xMeasSfPriority;
    VOS_INT32  slCproc1xMeasCfPriority;


}UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_HRPD_CPROC_GENERAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NV parameters for CPROC HRPD.
*****************************************************************************/
typedef struct
{
    VOS_INT32 slKalle;
}UCOM_NV_CDMA_HRPD_CPROC_GENERAL_STRU;


/*******************************************************
CDMA NV begin
*********************************************************/

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_MAIN_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����֧�ֵ�band������Bitλ��ʾBC0~BC21�Ƿ�֧�֣�1��ʾ֧�֡�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSupportBand;
}UCOM_NV_CDMA_RF_MAIN_BAND_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_DIV_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ּ�֧�ֵ�band������Bitλ��ʾBC0~BC21�Ƿ�֧�֣�1��ʾ֧�֡�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSupportBand;
}UCOM_NV_CDMA_RF_DIV_BAND_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_BAND_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :2.1��ʾCDMA֧�ֵ�ÿ��Ƶ����RF
            ͨ����Ӧ��ϵ���߿����л�ѡ��DBB��3GPA�Ŀ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandMainRxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];     /* ������CDMA����Ƶ�� */
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandDvtyRxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];     /* ������CDMA����Ƶ�� */
    UCOM_NV_RF_CONFIG_STRU       astCdmaRfBandTxConfig[UCOM_NV_CDMA_TOTAL_BAND_NUM];         /* ������CDMA����Ƶ�� */
}UCOM_NV_CDMA_RF_BAND_CONFIG_STRU;

typedef UCOM_NV_W_RX_AGC_GAIN_VALID_COUNT_STRU  UCOM_NV_CDMA_RX_AGC_GAIN_VALID_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_IP2_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Xģ Rx IP2У׼�����ú�У׼���ޡ�
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxRefPower;                          /* У׼ʱ����ͨ���Ĺ��ʣ���λΪ0.1dBm */
    VOS_INT16                           shwImd2Threshold;                       /* У׼��IMD2�����ޣ���λdB */
}UCOM_NV_CDMA_RX_IP2_CAL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Xģ ���з���ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwPaOnDelay;                           /* ��ǰ������PA��chip����Ĭ��ֵ25 */
    VOS_UINT16                          uhwPaOffDelay;                          /* �Ӻ�ر�����PA��chip����*/
    VOS_UINT16                          uhwRfTxEnOnDelay;                       /* ��ǰ������RF TX EN���߿�chip��,Ĭ��ֵ220 */
    VOS_UINT16                          uhwRfTxEnOffDelay;                      /* �Ӻ�ر�����RF TX EN���߿�chip��,Ĭ��ֵ220 */
    VOS_UINT16                          uhwRfIdleOnDelay;                       /* ��ǰ������RF IDLE->On״̬��chip��,Ĭ��ֵ220 */
    VOS_UINT16                          uhwRfOnIdleDelay;                       /* �Ӻ�����RF On->IDLE״̬�رյ�chip��  */
    VOS_UINT16                          uhwTxAbbOnDelay;                        /* ��ǰ������ABB En �߿ص�chip����Ĭ��ֵ164 */
    VOS_UINT16                          uhwTxAbbOffDelay;                       /* �Ӻ�ر�����ABB��chip����*/
    VOS_UINT16                          uhwBbpDbbAttenActiveTime;               /* ����dbb��������ǰʱ϶ͷ��Чλ�� ��λ1/4chip Ĭ��ֵ0 */
    VOS_UINT16                          uhwBbpPhaseCompActiveTime;              /* ��ʾ������λ������ǰʱ϶ͷ��Чλ�ã���λ1/4chip Ĭ��ֵ0 */
    VOS_UINT16                          uhwBbpSlotOffset;                       /* ����ʱ϶ͷ���sys_cntʱ϶�߽���ǰ������λ1/4chip Ĭ��ֵ0x97 */
    VOS_UINT16                          uhwRfTxAgcActiveTime;                   /* �������۹�����Ч��ǰ������λchip��Ĭ��ֵ22 */
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwReserve1;
    VOS_UINT16                          uhwReserve2;
    VOS_UINT16                          uhwReserve3;
}UCOM_NV_CDMA_TX_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_HDET_TIMING_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ʼ����ʹ�õ�NV��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPaStableTiming;                  /* ���书�ʱ仯��RF��PA���ȶ�ʱ�䣬��λΪchip*/
    VOS_UINT16                              uhwPdHkadcChanSelTiming;            /*��Ȩ��Ч������HKADCͨ��������ʱ�̼������λΪchip*/
    VOS_UINT16                              uhwPdStartInterval;                 /* ABB��bypassΪ�͵�����start��ABB��ʼת������ʱ��������λΪchip*/
    VOS_UINT16                              uhwPdInterval;                      /* ���ι��ʼ��֮���ʱ��������λΪchip*/
    VOS_UINT16                              uhwPdsampleTiming;                  /* HKADC�����źŴ���ʱ�䣬��λΪchip*/
    VOS_UINT16                              uhwDcOffsetSampleNum;               /*WHKADC����ÿ��ʱ϶����dc offset���Ĵ���*/
    VOS_UINT16                              uhwPdSampleNum;                     /*W����ÿ��ʱ϶����PD���Ĵ���*/
    VOS_UINT16                              uhwReserved1;                       /*����λ*/
    VOS_UINT16                              uhwReserved2;                       /*����λ*/
    VOS_UINT16                              uhwReserved3;                       /*����λ*/
} UCOM_NV_CDMA_HDET_TIMING_CONFIG_STRU;

typedef UCOM_NV_W_ANT_PERFORM_TEST_STRU         UCOM_NV_CDMA_ANT_PERFORM_TEST_STRU;

//RX_RSSI_ARITHMETIC_PARAMETER
typedef UCOM_NV_W_TX_RF_GAIN_TEMP_COMP_STRU     UCOM_NV_UC_TX_RF_GAIN_TEMP_COMP_STRU;        /* RFIC�¶Ȳ����� */
typedef UCOM_NV_W_RX_AGC_SWITCH_VOICE_MODE_STRU UCOM_NV_CDMA_RX_AGC_SWITCH_VOICE_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_PA_APT_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����bitλ��ʾ�Ƿ�ʹ��APT
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwCdmaBand;                             /* bitλ��1����֧��APT */
}UCOM_NV_CDMA_TX_PA_APT_ENABLE_STRU;

typedef UCOM_NV_W_TX_RF_GAIN_CTRL_STRU          UCOM_NV_CDMA_TX_RF_GAIN_CTRL_STRU;
typedef UCOM_NV_W_TX_RF_BIAS_STRU               UCOM_NV_CDMA_TX_RF_BIAS_STRU;
typedef UCOM_NV_W_BB_GAIN_TABLE_STRU            UCOM_NV_CDMA_BB_GAIN_TABLE_STRU;
typedef UCOM_NV_W_CPC_DRX_STRU                  UCOM_NV_CDMA_CPC_DRX_STRU;    /* �͹��Ĺ���ģʽѡ�� */
/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_IQ_MISMATCH_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TX IQ MISMATCHУ׼��ʼ���ʺ�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwTxIqMismatch2RefPower;           /* У׼ʱ����ͨ���Ĺ��ʣ���λΪ0.1dbm */
    VOS_INT16                           shwAmpCorrThreshold;                /* У׼��IMD2�����ޣ���λdb */
    VOS_INT16                           shwDcCorrThreshold;                 /* У׼��IMD2�����ޣ���λdb */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_CDMA_TX_IQ_MISMATCH_CAL_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_IP2_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪIP2У׼ʱ��Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwFrequencyKHz[UCOM_NV_CDMA_CHANNEL_NUM];           /* 0 - High Channel; 1 - Mid Channel; 2 - Low Chan */
}UCOM_NV_CDMA_RX_IP2_CAL_FREQ_STRU;

typedef UCOM_NV_W_RX_IP2_CAL_AT1_STRU           UCOM_NV_CDMA_RX_IP2_CAL_AT1_STRU;
typedef UCOM_NV_W_RX_IP2_CAL_AT2_STRU           UCOM_NV_CDMA_RX_IP2_CAL_AT2_STRU;
typedef UCOM_NV_W_RX_IP2_THRESHOLD_STRU         UCOM_NV_CDMA_RX_IP2_THRESHOLD_STRU;
typedef UCOM_NV_W_RX_IP2_CAL_ENABLE_AT2_STRU    UCOM_NV_CDMA_RX_IP2_CAL_ENABLE_AT2_STRU;  /* 0��ʾ�����ּ�����IP2У׼��1��ʾ������ */

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_IQ_DC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IQֱ��ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwDcICode;                             /* I·��ֱ����ֵ */
    VOS_INT16                           shwDcQCode;                             /* Q·��ֱ����ֵ */
}UCOM_NV_CDMA_RX_IQ_DC_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_DC_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BLOCK��NOBLOCKֱ����
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_IQ_DC_STRU          astNoBlockDcOffset[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM];
    UCOM_NV_CDMA_RX_IQ_DC_STRU          astBlockDcOffset[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM];
}UCOM_NV_CDMA_BLK_NBLK_DC_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_DCOFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_BLK_NBLK_DC_STRU       astDcOffsetAnt[UCOM_NV_CDMA_ANT_NUM];   /* ����ѡ�� */
}UCOM_NV_CDMA_RX_DCOFFSET_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_CAL_FREQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ҪУ׼��CDMA��Ƶ�������Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                          /* Ƶ�ʸ��� */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          auwRxFrequencyKHz[UCOM_NV_CDMA_UARFCN_NUM];  /* Ƶ�ʱ���λKHz */
}UCOM_NV_CDMA_RX_CAL_FREQ_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU
 Э����  :
 ö��˵��  : AGC��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwNoBlockAgcFastSwitchThrd;           /* NOBLOCK�¿������� */
    VOS_UINT16                           uhwBlockAgcFastSwitchThrd;             /* BLOCK�¿������� */
}UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU
 Э����  :
 ö��˵��  : ������ģʽ��������LNA�£�AGC��λ�л����޵�NV�����BLOCK�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcThresholdInc[UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwNoBlockAgcThresholdDec[UCOM_NV_CDMA_AGC_GAIN_NOBLK_THRESHOLD_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwBlockAgcThresholdInc[UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM];               /* Block��ʽ�µ�λ���� */
    VOS_INT16                           ashwBlockAgcThresholdDec[UCOM_NV_CDMA_AGC_GAIN_BLK_THRESHOLD_NUM];               /* Block��ʽ�µ�λ���� */
}UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_CDMA_RX_AGC_CTRL_STRU
 Э����  :
 ö��˵��  : ������LNAʱ��AGC�����֣�����BLOKC�ͷ�BLOCK
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_CTRL_STRU      stRxAgcCtrl;

}UCOM_NV_CDMA_RX_AGC_CTRL_STRU;


/*****************************************************************************
 ö����    : UCOM_NV_CDMA_RX_AGC_GAIN_BLK_NBLK_STRU
 Э����  :
 ö��˵��  : AGC�����ֶ�Ӧ����ֵ������BLOKC�ͷ�BLOCK,��λ0.125dbm.
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNoBlockAgcGain[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM];           /* NoBlock��ʽ�µ�λ���� */
    VOS_INT16                           ashwBlockAgcGain[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM];               /* NoBlock��ʽ�µ�λ���� */
}UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGCĬ������ֵ����������
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU   astAgcGainAnt[UCOM_NV_CDMA_ANT_NUM];    /* ����ѡ�� */
}UCOM_NV_CDMA_RX_AGC_GAIN_DEFAULT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_GAIN_ANT_DEF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AGCĬ������ֵ����������
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_RX_AGC_GAIN_ANT_STRU   astAgcGainAnt[UCOM_NV_CDMA_ANT_NUM];    /* ����ѡ�� */
}UCOM_NV_CDMA_RX_AGC_GAIN_STRU;

typedef UCOM_NV_W_RX_AGC_FREQ_COMP_ANT_STRU     UCOM_NV_CDMA_RX_AGC_FREQ_COMP_ANT_STRU;    /* AGCƵ�ʲ�����16�������㣬�������� */
typedef UCOM_NV_FEM_CHAN_CONNECT_STRU           UCOM_NV_CDMA_FEM_CHAN_CONNECT_STRU;

/*****************************************************************************
 �ṹ��    : CSDR_NV_CDMA_RF_PA_GAIN_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          auwRfPaCtrlMode[UCOM_NV_CDMA_TX_PA_MODE_NUM];   /* PA��/��/������ģʽ������ */
}UCOM_NV_CDMA_RF_PA_GAIN_CTRL_WORD_STRU;

/*****************************************************************************
 �ṹ��    : CSDR_NV_CDMA_PA_GAIN_SWITCH_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PA��λ�л�����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwPaGainThresH2M;                      /* PA�Ӹ����浽��������л����� */
    VOS_INT16                           shwPaGainThresM2H;                      /* PA�������浽��������л����� */
    VOS_INT16                           shwPaGainThresM2L;                      /* PA�������浽��������л����� */
    VOS_INT16                           shwPaGainThresL2M;                      /* PA�ӵ����浽��������л����� */
}UCOM_NV_CDMA_PA_GAIN_SWITCH_THRESHOLD_STRU;

typedef UCOM_NV_W_PA_GAIN_SWITH_TIMING_STRU     UCOM_NV_CDMA_PA_GAIN_SWITCH_TIMING_STRU;  /* PA��λ�л�ʱ�� */
typedef UCOM_NV_W_TX_PHASE_COMP_STRU            UCOM_NV_CDMA_TX_PHASE_COMP_STRU;           /* PA�л���λ���� */
typedef UCOM_NV_W_TX_PHASE_COMP_TIMING_STRU     UCOM_NV_CDMA_TX_PHASE_COMP_TIMING_STRU;   /* PA�л���λ����ʱ�� */
typedef UCOM_NV_TX_IQ_MISMATCH_DCR_STRU         UCOM_NV_CDMA_TX_IQ_MISMATCH_STRU;          /* У׼��ķ���У�����Ӻ�ֱ��У������ */
typedef UCOM_NV_TX_IQ_SELF_CAL_6362_STRU        UCOM_NV_CDMA_TX_IQ_SELF_CAL_6362_STRU;     /* DC offset��ֱ��У׼���� */

/*****************************************************************************
 �ṹ��    : CSDR_NV_CDMA_TX_CAL_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ҪУ׼��CDMA��Ƶ�������Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwValidCalChanNum;                          /* Ƶ�ʸ��� */
    VOS_UINT16                          uhwReserved;
    VOS_UINT32                          auwTxFrequencyKHz[UCOM_NV_CDMA_UARFCN_NUM];  /* Ƶ��ֵ,��λKHz */
}UCOM_NV_CDMA_TX_CAL_FREQ_STRU;

typedef UCOM_NV_W_TX_APC_TEMP_STRU                        UCOM_NV_CDMA_TX_APC_TEMP_STRU;            /* У׼ʱ���¶� */
typedef UCOM_NV_W_TX_PA_GAIN_STRU                         UCOM_NV_CDMA_TX_PA_GAIN_STRU;             /* PA����λ�µ�����ֵ */
typedef UCOM_NV_W_APC_GAIN_STATE_INDEX_STRU               UCOM_NV_CDMA_RF_GAIN_STATE_INDEX_STRU;   /* APC������ֵ */
typedef UCOM_NV_W_APC_RFIC_CTRL_GAIN_STRU                 UCOM_NV_CDMA_APC_RFIC_CTRL_GAIN_STRU;    /* APC������� */
typedef UCOM_NV_W_APC_DBB_ATTEN_GAIN_STRU                 UCOM_NV_CDMA_APC_DBB_ATTEN_GAIN_STRU;    /* DBB����ֵ */

typedef UCOM_NV_W_TX_PA_GAIN_VOICE_MODE_STRU              UCOM_NV_CDMA_TX_PA_GAIN_VOICE_MODE_STRU;           /* ����ģʽ��PA��������ֵ */
typedef UCOM_NV_W_APC_STATE_INDEX_GAIN_VOICE_MODE_STRU    UCOM_NV_CDMA_RF_STATE_INDEX_GAIN_VOICE_MODE_STRU; /* ����ģʽ��APC������ֵ */
typedef UCOM_NV_W_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU      UCOM_NV_CDMA_APC_RFIC_CTRL_GAIN_VOICE_MODE_STRU;  /* ����ģʽ��APC������ */
typedef UCOM_NV_W_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU      UCOM_NV_CDMA_APC_DBB_ATTEN_GAIN_VOICE_MODE_STRU;  /* ����ģʽ��DBB����ֵ */

typedef UCOM_NV_W_TX_HDET_VGA_STRU                        UCOM_NV_CDMA_TX_HDET_VGA_STRU;       /* PD VGA��У׼������� */
typedef UCOM_NV_W_TX_HDET_DCOFFSET_STRU                   UCOM_NV_CDMA_TX_HDET_DCOFFSET_STRU;  /* PD DC Offset��У׼��� */
typedef UCOM_NV_W_TX_HDET_POWER_STRU                      UCOM_NV_CDMA_TX_HDET_POWER_STRU;     /* ������ģʽ�£����Թ��ʺ͵�ѹ��ϵ�Ĺ��ʲ��Ե� */
typedef UCOM_NV_W_TX_HDET_HKADC_STRU                      UCOM_NV_CDMA_TX_HDET_HKADC_STRU;     /* ������ģʽ�£����Թ��ʺ͵�ѹ��ϵʱ��ѹ����ֵ */
typedef UCOM_NV_W_TX_HDET_START_STRU                      UCOM_NV_CDMA_TX_HDET_START_STRU;     /* TX ���书�ʳ�����ֵʱ��BBP�Զ��������ʼ�� */
typedef UCOM_NV_W_TX_HDET_STOPT_STRU                      UCOM_NV_CDMA_TX_HDET_POWER_OFFSET_STRU; /* TX ���书�ʳ�����ֵʱ��BBP�Զ��������ʼ�� */
typedef UCOM_NV_W_HDET_HKADC_CHAN_STRU                    UCOM_NV_CDMA_HDET_HKADC_CHAN_STRU;   /* ����PA HDETͨ�� */
typedef UCOM_NV_W_TX_HDET_FREQ_COMP_STRU                  UCOM_NV_CDMA_TX_HDET_FREQ_COMP_STRU; /* ��ͬƵ��Թ�������Ӱ�첻ͬ��Ƶ�ʲ���ֵ */
typedef UCOM_NV_W_TX_HDET_TEMP_COMP_STRU                  UCOM_NV_CDMA_TX_HDET_TEMP_COMP_STRU; /* ��ͬ�¶ȶԹ�������Ӱ�첻ͬ���¶Ȳ���ֵ.���ָ��е��ŵ�,˳��Ϊ�иߵ� */
typedef UCOM_NV_W_TX_GAIN_FREQCOMP_STRU                   UCOM_NV_CDMA_TX_GAIN_FREQ_COMP_STRU; /* PAƵ�ʲ������ָ��е����� */
typedef UCOM_NV_W_TX_GAIN_TEMP_COMP_STRU                  UCOM_NV_CDMA_TX_GAIN_TEMP_COMP_STRU; /* PA�¶Ȳ������ָ��е͵�λ�͸��е��ŵ� */
typedef UCOM_NV_W_RFFE_MIPI_PA_CTRL_STRU                  UCOM_NV_CDMA_RFFE_MIPI_PA_CTRL_STRU;  /* MIPI PAָ�� */
typedef UCOM_NV_W_ANT_SWITCH_MIPI_STRU                    UCOM_NV_CDMA_ANT_SWITCH_MIPI_STRU;    /* MIPI ���߿���ָ�� */
typedef UCOM_NV_DUAL_ANT_DPDT_PROTECT_TIME_STRU           UCOM_NV_CDMA_DUAL_ANT_DPDT_PROTECT_TIME_STRU; /* DPDT�л�����ʱ�� */

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_GAIN_COMP_VS_PA_CHAN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwHighFreq;                             /* �����жϸ�Ƶ�������Ƶ�� */
    VOS_UINT32                          uwLowFreq;                              /* �����жϵ�Ƶ�������Ƶ�� */
}UCOM_NV_CDMA_TX_GAIN_COMP_VS_PA_CHAN_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TX_PA_APT_EVDO_COMP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ݲ�ͬ���ŵ�������ò�ͬ�Ĳ���ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwAptEvdoComp[16];                    /* ����EVDOģʽAPT���ʲ��� */
 }UCOM_NV_CDMA_TX_PA_APT_EVDO_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_ALG_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�㷨ά����NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      uhwDagcInit;                /* DAGC,��ʼֵ����Ҫ�㷨����NV���� */
    VOS_UINT16                                      uhwAagcCoeff;               /* AAGC Alpha�˲�ϵ��,��NV���� */
    VOS_UINT16                                      uhwDagcCoeff;               /* DAGC Alpha�˲�ϵ��,��NV���� */
    VOS_INT16                                       shwIqMismatchInit;          /* CBBP IQ MISMATCH��ֵ,��NV���� */
    VOS_INT16                                       shwDcrInit;                 /* CBBP DCR��ֵ,��NV���� */
    VOS_INT16                                       shwAagcGainInit;            /* CBBP AAGC��λ�����ֵ,��NV���� */

    UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU  stAgcFastSwitchThrd;       /* normal+������LNA�¿������� */
    UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU  stAgcFastSwitchThrdVoiceLna;/* ����+����LNA�¿������� */
    UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU  stAgcFastSwitchThrdLna;    /*  normal+����LNA�¿������� */
    UCOM_NV_CDMA_RX_AGC_FAST_SWITCH_THRESHOLD_STRU  stAgcFastSwitchThrdVoice;  /* ����+������LNA�¿������� */
}UCOM_NV_CDMA_ALG_CFG_STRU;


typedef UCOM_NV_W_UL_RF_GATE0_STRU              UCOM_NV_CDMA_UL_RF_GATE0_STRU;       /* ��������0 */
typedef UCOM_NV_W_UL_RF_GATE1_STRU              UCOM_NV_CDMA_UL_RF_GATE1_STRU;       /* ��������1 */
typedef UCOM_NV_WG_IQ_REV_CONTROL_STRU          UCOM_NV_CDMA_IQ_REV_CONTROL_STRU;    /* IQ���ݷ������� */
typedef UCOM_NV_RF_INIT_CONFIG_STRU             UCOM_NV_GUC_RF_INIT_CONFIG_STRU;     /* RFIC�Ĵ�����ʼ���� */
typedef UCOM_NV_RF_INIT_CONFIG_NEW_RAM_STRU     UCOM_NV_GUC_RF_INIT_CONFIG_NEW_RAM_STRU;     /* RFIC�Ĵ�����ʼ���� */
typedef UCOM_NV_XO_INIT_FREQUENCY_STRU          UCOM_NV_GUC_XO_INIT_FREQUENCY_STRU;  /* �����ʼƵƫ���¶� */
typedef UCOM_NV_DYNAMIC_FREQUENCY_STRU          UCOM_NV_GUC_DYNAMIC_FREQUENCY_STRU;  /* Ƶƫ������һ�α����Ƶƫ���¶� */
typedef UCOM_NV_W_RSSI_ARITHMETIC_PARA_STRU     UCOM_NV_UC_RSSI_ARITHMETIC_PARA_STRU;
typedef UCOM_NV_W_AFC_K_VALUE_STRU              UCOM_NV_GUC_AFC_K_VALUE_STRU;         /* AFCÿ�������ֵ�����Ƶƫ��������λhz��Ŀǰ4hz */
typedef UCOM_NV_RFIC_TEMP_COMP_WEIGH_STRU       UCOM_NV_GUC_RFIC_TEMP_COMP_WEIGH_STRU;
typedef UCOM_NV_WG_TX_TEMP_DEFINE_STRU          UCOM_NV_GUC_TX_TEMP_DEFINE_STRU;      /* �¶ȷ�Χ����λ0.1�ȣ�16�������� */
typedef UCOM_NV_W_TX_TEMP_COMP_STRU             UCOM_NV_CDMA_TX_TEMP_COMP_STRU;       /* RFIC 15����λ�£�ÿ����λ��Ӧ16���¶Ȳ����� */
typedef UCOM_NV_RF_TRX_CONFIG_STRU              UCOM_NV_CDMA_RF_TRX_CONFIG_STRU;
typedef UCOM_NV_SINGLE_XO_DEFINE_STRU           UCOM_NV_GUC_SINGLE_XO_DEFINE_STRU;   /* ʱ������NV */
typedef UCOM_NV_RF_VERSION_STRU                 UCOM_NV_GUC_RF_VERSION_STRU;   /* RF�汾�� */
typedef UCOM_NV_WG_IQMISMATCH_CAL_STRU          UCOM_NV_GUC_RF_MRX_CONNECT_STRU; /* ��RF MRX��������ͨ����ABB��������� */
typedef UCOM_NV_WG_DCOFFSET_THRESHOLD_STRU      UCOM_NV_GUC_DCOFFSET_THRESHOLD_STRU;     /* DC offset��ֱ��У׼���� */

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Bitλ��ʾBC0~BC21 ���ּ����߿��ؿ��Ʒ�ʽΪGPIO��MIPI��0��ʾGPIO,1��ʾMIPI��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwMainAntCtrlModeBitMap;
    VOS_UINT32                          uwDvtyAntCtrlModeBitMap;
}UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_ANT_SWITCH_CONTROL_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Bitλ��ʾBC0~BC21 PA���Ʒ�ʽΪGPIO��MIPI��0��ʾGPIO,1��ʾMIPI��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwPaCtrlModeBitMap;
}UCOM_NV_CDMA_PA_CONTROL_MODE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TRI_MODE_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ��ͨ����ʹ�ܿ���(0:�ر� 1:��)
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwEnable;                          /* ȫ��ͨ���Կ��� */
    VOS_UINT16                              uhwReserved;
}UCOM_NV_TRI_MODE_ENABLE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ָʾʹ��ȫ��ͨ����Profile Id��NV��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwProfileId;                        /* ����ʹ�ó���������ǰ�����������µ磨ABB��TCXO��RF���Լ�RFͨ���Ŀ��ơ�
                                                                                   ��AT�����·����á�Ĭ��ֵΪ0��ȡֵ��Χ0-7�� */
    VOS_UINT32                              auwReserved[3];                     /* ������������չʹ�� */
}UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU;


/*****************************************************************************
�ṹ��    : UCOM_NV_MODE_BASIC_PARA_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2014��12��30��
    ��    ��   : z68255
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwABBSwitch;                       /* ����ABB PLL���صĿ��ơ�0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1���� */
    VOS_UINT16                              uhwRFSwitch;                        /* ����RFIC��Դ���صĿ��ơ�0:RFICʹ��MIPI0���ƹ��緽ʽ 1��RFICʹ��MIPI1���ƹ��緽ʽ 2��ͬʱ����·��Դ��*/
    VOS_UINT16                              uhwTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              uhwReserved;                     /* ������������չʹ�� */
}UCOM_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_TRI_MODE_CHAN_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ��ͨͨ���������ò���  (���ܸı�)
*****************************************************************************/
typedef struct
{
    UCOM_NV_MODE_BASIC_PARA_STRU           stModeBasicPara[2];                  /* �±�[0]:��ʾGSMģʽ�µ�ǰ�����������µ���ơ�
                                                                                   �±�[1]:��ʾWCDMAģʽ�µ�ǰ�����������µ���ơ�
                                                                                    ע������ʱ����ʹ��WCDMAģʽ�����á�*/
    VOS_UINT32                              uwRfSwitch;                         /* ���ڿ��ƹ��ּ��Ŀ��� */
    VOS_UINT32                              uwGsmRficSel;                       /* ����ģʽ�µ�ǰʹ�õ�ͨ����0��RF0,1��RF1�� */
    VOS_UINT32                              uwGpioCtrl;                         /* �Ƿ���Ҫʱ���л�(0:����Ҫ, 1:��Ҫ )*/
    VOS_UINT32                              auwReserved[14];                    /* ������������չʹ�� */
}UCOM_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 8�ֳ�����ͨ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TRI_MODE_CHAN_PARA_STRU        astPara[UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* ���֧��8������������ */
}UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;


/*****************************************************************************
�ṹ��    : UCOM_NV_MODE_BASIC_EXT_PARA_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2014��12��30��
    ��    ��   : z68255
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwABBSwitch;                       /* ����ABB PLL���صĿ��ơ�0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1���� */
    VOS_UINT16                              uhwRFSwitch;                        /* ����RFIC��Դ���صĿ��ơ�0:RFICʹ��MIPI0���ƹ��緽ʽ 1��RFICʹ��MIPI1���ƹ��緽ʽ 2��ͬʱ����·��Դ��*/
    VOS_UINT16                              uhwTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              uhwRfClk;                           /* 1:��ģʽ��RFIC������PMURF0_CLK_19M2
                                                                                   0: ��ʾδʹ�� */
    VOS_UINT16                              uhwReserved[4];                     /* ������������չʹ�� */
}UCOM_NV_MODE_BASIC_EXT_PARA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ��ͨͨ���������ò���  (���ܸı�)
*****************************************************************************/
typedef struct
{
    UCOM_NV_MODE_BASIC_EXT_PARA_STRU        stModeBasicPara[8];                  /* �±�[0]:��ʾGSMģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[1]:��ʾWCDMAģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[2]:��ʾLTEģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[3]:��ʾTDSģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[4]:��ʾ1Xģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[5]:��ʾHRPDģʽ�µ�ǰ�����������µ����;
                                                                                    �±�[6]:Ԥ��;
                                                                                    �±�[7]:Ԥ��  */
    VOS_UINT32                              uwRfSwitch;                         /* ���ڿ��ƹ��ּ��Ŀ��� */
    VOS_UINT32                              uwGsmRficSel;                       /* ����ģʽ�µ�ǰʹ�õ�ͨ����0��RF0,1��RF1�� */
    VOS_UINT32                              uwGpioCtrl;                         /* �Ƿ���Ҫʱ���л�(0:����Ҫ, 1:��Ҫ )*/
    VOS_UINT32                              uwCdmaRficSel;                      /* ����ģʽ�µ�ǰʹ�õ�ͨ����0��RF0,1��RF1�� */
    VOS_UINT32                              auwReserved[13];                    /* ������������չʹ�� */
}UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_FEM_CHAN_PROFILE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 8�ֳ�����ͨ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_TRI_MODE_CHAN_PARA_EXT_STRU    astPara[UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* ���֧��8������������ */
}UCOM_NV_FEM_CHAN_PROFILE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RF_RX_EVM_TEST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Wcdma RxEvm����ѡ��NV
*****************************************************************************/
typedef struct
{
    UCOM_NV_RX_EVM_TEST_EN_ENUM_UINT16  enRxEvmTestEn;                          /* RxEvm����ʹ�ܣ�0:����ģʽ,1:����ģʽ */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_W_RF_RX_EVM_TEST_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_DCXO_C_TRIM_DEFAULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Wcdma AfcУ׼
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwInitCfix;                            /* AfcУ׼��ʽ ѡ��  */
    VOS_UINT16                          uhwFreqErrThr;                          /*C1�Ƿ���Ҫ��У׼*/
    VOS_UINT16                          uhwCfixLowerLimit;                      /*C1�Ƿ���Ҫ��У׼*/
    VOS_UINT16                          uhwCfixUpperLimit;                      /*C1�Ƿ���Ҫ��У׼*/

}UCOM_NV_DCXO_C_TRIM_DEFAULT_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_M_DA_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Mֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRfMDaValue;                          /* Mֵ */
    VOS_UINT16                          uhwReserved;
}UCOM_NV_CDMA_M_DA_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_MAXMIN_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����С����
*****************************************************************************/
typedef struct
{
    VOS_INT16                          shwTxWirelessMaxPowerAch;                /* ����ACHͨ������� */
    VOS_INT16                          shwTxWirelessMaxPowerTch;                /* ����TCHͨ������� */
    VOS_INT16                          shwTxWireMaxPowerAch;                    /* ����ACHͨ������� */
    VOS_INT16                          shwTxWireMaxPowerTch;                    /* ����TCHͨ������� */
    VOS_INT16                          shwTxMinPower;                           /* ��С���� */
    VOS_INT16                          shwHrpdMaxPowerBackoff;
}UCOM_NV_CDMA_TX_POWER_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TEST_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WCDMA��������ר�ÿ��أ�Ĭ�ϲ������Զ�Ϊ�رա�0��ʾ���عر� 1��ʾ���ش�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwTestDrxIgnorePiValue:1;               /* ������piֵ������������PCH����Ĵ��� */
    VOS_UINT32                          uwTestDrxSccpchAlwaysOpen:1;            /* ������piֵ����SCCPCH��������PCH����Ĵ��� */
    VOS_UINT32                          uwTestCpcMntnInfo:1;                    /* cpc��ά�ɲ⿪��,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwTestRxPart:1;                         /* RFIC1 Rx�������Կ���,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwReserve:28;
}UCOM_NV_W_TEST_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_G_TEST_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM��������ר�ÿ��أ�Ĭ�ϲ������Զ�Ϊ�رա�0��ʾ���عر� 1��ʾ���ش�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwReserve1:3;
    VOS_UINT32                          uwTestRxPart:1;     /* DSDS2.0 RFIC1 RX�������Կ��أ�1-�򿪣�0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwReserve2:28;
}UCOM_NV_G_TEST_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_VIA_C_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Via CUse����nv��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwViaCSupportEn;                   /* ����VIA C ֧��ʹ�ܣ�0-��ʹ�ܣ�1--ʹ�� */
    VOS_UINT16                              uhwViaCActiveIndGpio;               /* ����VIA C ����ָʾGPIO */
    VOS_UINT32                              uwViaCLineCtrlMask;                 /* ����VIA C BandָʾMask */
    VOS_UINT32                              uwViaCLineCtrl;                     /* ����VIA C Bandָʾ�߿�ֵ */
}UCOM_NV_VIA_C_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_B26_ANT_SHARE_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : B26����������nv��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwFeatureB26AntShareEn;            /* B26������ʹ�ܣ�0-��ʹ�ܣ�1--ʹ�� */
    VOS_UINT16                              uhwReserved;                        /* ����λ */
    VOS_UINT32                              uwB26AntShareDpdt;                  /* B26�����л�DPDT�߿�ֵ */
    VOS_UINT32                              uwB26TxDisableLineCtrl;             /* B26 TX�ر�ʹ���߿�ֵ */
    VOS_UINT32                              uwB26VoLTESupportLineCtrl;          /* VoLTEָʾ�ܽ��߿�ֵ */
}UCOM_NV_B26_ANT_SHARE_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_FEM_PIN_TO_GPIO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �߿�������GPIO�ܽźŵ�ӳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwFemPinToGpio[32];                 /* GPIOת���� */
}UCOM_NV_FEM_PIN_TO_GPIO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_RX_FE_NF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ���н�������ϵ��NF�Ͳ���FE��ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                          shwRxFeNfValue;                      /* ��Ƶ���н�������ϵ��NF�Ͳ���FE��ֵ, ��λΪ0.1dbm*/
    VOS_INT16                          shwReserved;
}UCOM_NV_W_RX_FE_NF_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_RFFE_GPIO_VALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwGpioMask;                         /* ��Ƶ�ܽ�����,0��ʾ��bitλ����Ҫ���� */
    VOS_UINT32                              uwGpioValue;                        /* ��Ƶ�ܽ������ƽ ֵ,0��ʾ�õ͵�ƽ��1��ʾ�ߵ�ƽ */
}UCOM_NV_RFFE_GPIO_VALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GPIO_MIPI_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    UCOM_NV_FEMIO_CTRL_MODE_ENUM_UINT32     enMode;                             /* ����ģʽ */
    UCOM_NV_RFFE_GPIO_VALUE_STRU            stGpioCtrl;                         /* GPIO ���� */
    UCOM_NV_ANT_SWITCH_MIPI_CTRL_WORD_STRU  stMipiCtrl;                         /* MIPI ���� */
}UCOM_NV_GPIO_MIPI_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_FEM_GPIO_MIPI_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߿������ã��ýṹ��drv�Ѿ�����
*****************************************************************************/
typedef struct
{
    UCOM_NV_GPIO_MIPI_CTRL_STRU             stFemGpioMipiCtrl[UCOM_NV_FEM_IO_CFG_MAX];
}UCOM_NV_FEM_GPIO_MIPI_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATE�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateEvaluateTime;               /* �׶�����ʱ�䣬��λ:ms */
    VOS_INT16                               shwStateRscpDeltaThd;               /* Delta����ֵ����λ:dB */
}UCOM_NV_W_MAS_STATE_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATEI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATEI�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateITime;                      /* �׶�I����ʱ�䣬��λ:ms */
    VOS_INT16                               shwWorstRscpValue;                  /* ���RSCP�ź�����ֵ����λ:dB */
    VOS_INT16                               shwWorseRscpValue;                  /* �ϲ�RSCP�ź�����ֵ����λ:dB */
    VOS_INT16                               shwDeltaRscpValue;                  /* ���յ����ź�ǿ���½��о����� */

}UCOM_NV_W_MAS_STATEI_COM_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATEI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATEI�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATEI_COM_STRU         stStateIActive;                       /* ����StateI��Ϣ */
    UCOM_NV_W_MAS_STATEI_COM_STRU         stStateIPassive;                      /* ����StateI��Ϣ */

}UCOM_NV_W_MAS_STATEI_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATEI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATEIAIB�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATE_STRU                      stStateIaIbActiveInfo;        /* ����StateIaIb��Ϣ */
    UCOM_NV_W_MAS_STATE_STRU                      stStateIaIbPassiveInfo;       /* ����StateIaIb��Ϣ */

}UCOM_NV_W_MAS_STATEIAIB_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATEII_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATEII�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_MAS_STATE_STRU                              stStateIIBlindInfo;   /* �׶�IIä����Ϣ */
    UCOM_NV_W_TAS_NONBLIND_MEAS_STRU                      stStateIINonBlindInfo;/* �׶�II������Ϣ */

}UCOM_NV_W_MAS_STATEII_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_MAS_STATEIII_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAS STATEII�Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwActiveFrozenTime;                /* ���ؽ׶�III����ʱ�� */
    VOS_UINT16                              uhwPassiveFrozenTime;               /* ���ؽ׶�III����ʱ�� */

}UCOM_NV_W_MAS_STATEIII_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_BLIND_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TASä�в����Ŀ��Ʋ���
*****************************************************************************/
typedef struct
{
   UCOM_NV_W_MAS_STATEI_STRU                              stInfoStateI;         /* �׶�I��Ϣ */
   UCOM_NV_W_MAS_STATEIAIB_STRU                           stInfoStateIa;        /* �׶�IaIb��Ϣ */
   UCOM_NV_W_MAS_STATEIAIB_STRU                           stInfoStateIb;        /* �׶�IaIb��Ϣ */
   UCOM_NV_W_MAS_STATEII_STRU                             stInfoStateII;        /* �׶�II��Ϣ */
   UCOM_NV_W_MAS_STATEIII_STRU                            stInfoStateIII;       /* �׶�III��Ϣ */
   VOS_INT16                                              shwAntGoodEnoughThd;  /* ���������㹻��RSCP����ֵ(��λΪ0.125dbm) */
   VOS_INT16                                              uhwReserve;
}UCOM_NV_W_MAS_SCHDL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_MAS_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAS�㷨���Ʋ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* �����״̬�ϱ��������� */
    UCOM_NV_W_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingPara;                 /* ����������㷨���� */
    UCOM_NV_W_MAS_SCHDL_STRU                stMasPara;                          /* MAS���� */

}UCOM_NV_W_TAS_MAS_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_W_TAS_MAS_RF_CTRL_STRU
 Э����  :
 ASN.1���� : auwBandBlindSwitchMap�����ÿ��band�Ƿ�ʹ��TASä���㷨����bitmap��
             auwBandBlindSwitchMap[0]bit0����band1��bit1����band2���Դ����ơ�
             auwBandBlindSwitchMap[1]bit0����band33��bit1����band34���Դ����ơ�
             bitλΪ1�������bandʹ��ä���㷨������֮��
 �ṹ˵��  : TAS��Ƶ��ؿ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              auwBandBlindSwitchMap[2];           /* BAND�Ƿ�����ä�� */
    UCOM_NV_W_TAS_CTRL_WORD_STRU            stTasCtrlWord;                      /* �����л������� */
    VOS_UINT32                              auwBandIaEnable[2];                 /* ��һ�ֽ�uwBandIaEnable[0]�ӵ͵��߷ֱ����Band0~Band31�Ƿ�֧��Ia:0,��֧�֣�1��֧��*/
                                                                                /* �ڶ��ֽ�uwBandIaEnable[1]�ӵ͵��߷ֱ����Band32~Band63�Ƿ�֧��Ia:0,��֧�֣�1��֧��*/
    VOS_UINT32                              auwBandIbEnable[2];                 /* ��һ�ֽ�uwBandIbEnable[0]�ӵ͵��߷ֱ����Band0~Band31�Ƿ�֧��Ib:0,��֧�֣�1��֧��*/
                                                                                /* �ڶ��ֽ�uwBandIbEnable[1]�ӵ͵��߷ֱ����Band32~Band63�Ƿ�֧��Ib:0,��֧�֣�1��֧��*/
}UCOM_NV_W_TAS_MAS_RF_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Search״̬��,��������ʱ��ȡϵͳ��Ϣ����ǰͬ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwDsdaBcchNum;                     /* DSDA����²��ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdaSyncNum;                     /* DSDA����²��ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
    VOS_UINT16                              uhwDsdsIdleBcchNum;                 /* DSDS����¶Է�����DCH̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdsIdleSyncNum;                 /* DSDS����¶Է�����DCH̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
    VOS_UINT16                              uhwDsdsDchBcchNum;                  /* DSDS����¶Է���DCH̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdsDchSyncNum;                  /* DSDS����¶Է���DCH̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
}UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_IDLE_PARALLEL_NUM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��פ��״̬��,��������ʱ��ȡϵͳ��Ϣ����ǰͬ������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwDsdaIdleBcchNum;                 /* DSDA����±���IDLE̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdaIdleSyncNum;                 /* DSDA����±���IDLE̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
    VOS_UINT16                              uhwDsdaDchBcchNum;                  /* DSDA����±���DCH̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdaDchSyncNum;                  /* DSDA����±���DCH̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
    VOS_UINT16                              uhwDsdsIdleBcchNum;                 /* DSDS����¶Է�����DCH̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdsIdleSyncNum;                 /* DSDS����¶Է�����DCH̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
    VOS_UINT16                              uhwDsdsDchBcchNum;                  /* DSDS����¶Է���DCH̬���ж�ȡϵͳ��Ϣ�ĸ��� */
    VOS_UINT16                              uhwDsdsDchSyncNum;                  /* DSDS����¶Է���DCH̬���ж�ȡϵͳ��Ϣ֮����ǰͬ������ */
}UCOM_NV_GSM_PSRCH_IDLE_PCELL_STRU;




/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_PSRCH_PCELL_NUM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Search״̬��,��������ʱ��ȡϵͳ��Ϣ����ǰͬ������
*****************************************************************************/
typedef struct
{
    UCOM_NV_GSM_PSRCH_SEARCH_PCELL_STRU     stSearchPcellNum;                   /* ����Search״̬��,���ж� */
    UCOM_NV_GSM_PSRCH_IDLE_PCELL_STRU       stIdlePcellNum;                     /* ����idle״̬��,���ж� */
}UCOM_NV_GSM_PSRCH_PCELL_NUM_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_LPC_SWITCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSDR�͹��Ŀ��أ���ʼ�汾Ĭ�϶��ر�
*****************************************************************************/
typedef struct
{
    VOS_UINT32          uhwDeepSleepEnable:1;          /* bit0:CSDR��˯�����־ */
    VOS_UINT32          uhw1xMasterDrxEnable:1;        /* bit1:1X��ģ˯�������־  */
    VOS_UINT32          uhw1xSlaveDrxEnable:1;         /* bit2:1X��ģ˯�������־  */
    VOS_UINT32          uhwHrpdMasterDrxEnable:1;      /* bit3:HRPD��ģ˯�������־  */
    VOS_UINT32          uhwHrpdSlaveDrxEnable:1;       /* bit4:HRPD��ģ˯�������־  */
    VOS_UINT32          uhwResverd:27;                 /* bit5~31 */
}UCOM_NV_CDMA_LPC_SWITCH_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_LPC_ADV_WAKEUP_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSDR�͹��ģ����ø��������ǰ����ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      uhwMcuStableTime;    /* MCU�ϵ��ȶ���Ҫ��ʱ�䣬��λus */
    VOS_UINT16                      uhwDrvStableTime;    /* DRV�ϵ��ȶ���Ҫ��ʱ�䣬��λus */
    VOS_UINT16                      uhwOamStableTime;    /* OAM�ϵ��ȶ���Ҫ��ʱ�䣬��λus */
    VOS_UINT16                      uhwCphyStableTime;   /* PHY�ϵ��ȶ���Ҫ��ʱ�䣬��λus */
    VOS_UINT16                      uhwResverd1;
    VOS_UINT16                      uhwResverd2;
}UCOM_NV_CDMA_LPC_ADV_WAKEUP_TIME_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_CF_GAP_LENGTH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD ��Ƶ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwCfGapLength;                 /* HRPD ��Ƶ��������λslot */
    VOS_UINT16          uhwResverd;                     /* ����λ */
}UCOM_NV_CDMA_CF_GAP_LENGTH_STRU;




/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU
 Э����  :
 �ṹ˵��  : access̬��,�������ʧ�ܴ����ж�����N_FAIL
*****************************************************************************/
typedef struct
{

   VOS_UINT16           uhwAccessNFailThreshold;                                /* ACCESS̬���������ʧ�ܴ����ж�����,��ӦCTTF�ӿ���usSeqNum�ֶ� */
   VOS_UINT16           uhwRsv;                                                 /* ���� */

}UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU
 Э����  :
 �ṹ˵��  : RSCP Report T1ֵ����
*****************************************************************************/
typedef struct
{

   VOS_UINT16           uhwHighSpeedT1;                                         /* �ٶȹ���Ϊ���ٵ�ʱ��RSCP�ϱ�����T1ȡֵ��Ĭ��160ms */
   VOS_UINT16           uhwMidSpeedT1;                                          /* �ٶȹ���Ϊ���ٵ�ʱ��RSCP�ϱ�����T1ȡֵ��Ĭ��320ms */
   VOS_UINT16           uhwLowSpeedT1;                                          /* �ٶȹ���Ϊ���ٵ�ʱ��RSCP�ϱ�����T1ȡֵ��Ĭ��640ms */
   VOS_UINT16           uhwRsv;                                                 /* 4�ֽڶ��� */
}UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TAS_CTRL_STRU
 Э����  :
 �ṹ˵��  : cdma 1x tas���Կ���NV����
*****************************************************************************/
typedef struct
{
   UCOM_NV_CDMA_TAS_ACCESS_PARA_STRU        stTasAccessPara;                    /* Access̬�£�Tas���ò����ṹ�� */
   UCOM_NV_CDMA_TAS_RSCP_REPORT_T1_STRU     stTasTchRspcT1Para;                 /* TCH̬�£�Rscp T1����          */
}UCOM_NV_CDMA_TAS_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_RX_BIAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC RX��BIAS�����֣�����BLK,NBLK
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          auhwBlockStateBias[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM]; /* block bias��NV�� */
    VOS_UINT16                          auhwNoBlockStateBias[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM]; /* no block bias��NV�� */
}UCOM_NV_CDMA_RF_RX_BIAS_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RF_RX_BIAS_DELTA_GAIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ�µ�AGC���油��������BLK,NBLK
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwBlockStateDeltaGain[UCOM_NV_CDMA_AGC_GAIN_BLK_STEP_NUM]; /* block delta gain��NV�� */
    VOS_INT16                           ashwNoBlockStateDeltaGain[UCOM_NV_CDMA_AGC_GAIN_NOBLK_STEP_NUM]; /* no block delta gain��NV�� */
}UCOM_NV_CDMA_RF_RX_BIAS_DELTA_GAIN_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_RFIC_BIAS_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RFIC BIAS������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwRxBiasEnable;                 /* �Ƿ�֧�������͹���, 0 ��֧�֣�1-֧�� */
    UCOM_NV_CDMA_RF_RX_BIAS_STRU                stRfRxBiasNormalMode;           /* ����ģʽ��, Rx Bias���� */
    UCOM_NV_CDMA_RF_RX_BIAS_STRU                stRfRxBiasVoiceMode;             /* VOICEģʽ��,Rx Bias���� */
    UCOM_NV_CDMA_RF_RX_BIAS_DELTA_GAIN_STRU     stRfRxBiasDeltaGain;       /* VOICEģʽ������ģʽ�µ������ */
}UCOM_NV_CDMA_RX_RFIC_BIAS_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_VIA_C_SEC_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Via CUse��������nv��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwViaCSecSupportEn;                /* ����VIA C ����֧��ʹ�ܣ�0-��ʹ�ܣ�1--ʹ�� */
    VOS_UINT16                              uhwReserved;                        /* ����λ */
    VOS_UINT32                              uwViaCSpdt;                         /* �ϵ��ʼ��Cdmaͨ���л��߿�ֵ��֧�ֶ��bit���� */
    VOS_UINT32                              uwViaCSecLineCtrlMask;              /* ��������VIA C BandָʾMask */
    VOS_UINT32                              uwViaCSecLineCtrl;                  /* ��������VIA C Bandָʾ�߿�ֵ */
}UCOM_NV_VIA_C_SEC_CONFIG_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_UPRAISE_POWER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ�£���ʼ���볡���������书��NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwUpraisePowerEnable;                  /* �����������Կ���:�ر�Ϊ0,��Ϊ1 */
    VOS_UINT16                          uhwUpraisePowerLevel;                   /* ��������������(����̧��1~2��PCL)����λ: PCL */
}UCOM_NV_GSM_UPRAISE_POWER_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_TIME_AVG_SAR_FUNC_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ��ƽ����SAR����NV
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  uhwTimeAvgSarFuncEnable;        /* ʱ��ƽ����SAR���ܿ��� */
    VOS_UINT16                                  uhwReserved;                    /* �����ֶ� */
}UCOM_NV_TIME_AVG_SAR_FUNC_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_SAR_TIME_AVG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSMʱ��ƽ����SAR NV�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwGsmSarDprOnThd;              /* GSM������̬���ʻ��˵Ĺ������ޣ���λ0.1 dBm */
    VOS_INT16                                   shwGsmSarDprOffThd;             /* GSM�رն�̬���ʻ��˵Ĺ������ޣ���λ0.1 dBm */
    VOS_INT16                                   ashuwGmskSarLimitedMaxPwr[UCOM_NV_G_TX_SLOT_MAX_NUM];   /* GMSK���Ʒ�ʽ1-4������ʱ϶������DPR��������ƹ��ʣ���λ0.1 dBm */
    VOS_INT16                                   ashuw8pskSarLimitedMaxPwr[UCOM_NV_G_TX_SLOT_MAX_NUM];   /* 8PSK���Ʒ�ʽ1-4������ʱ϶������DPR��������ƹ��ʣ���λ0.1 dBm */
    VOS_UINT16                                  uhwGsmTimeAvgSarPeriod;         /* GSMʱ��ƽ��SAR���о�����(����400��ͳ������),��λs */
    VOS_UINT16                                  uhwRsv;                         /* ����ֵ */
}UCOM_NV_GSM_SAR_TIME_AVG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_SAR_TIME_AVG_SAR_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Wcdmaʱ��ƽ��SAR����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwWcdmaSarDprOnThd;                    /* WPHY������̬���ʻ��˹�������,��λ0.1dbm */
    VOS_INT16                           shwWcdmaSarDprOffThd;                   /* WPHYȡ����̬���ʻ��˹�������,��λ0.1dbm */
    VOS_INT16                           shwWcdmaSarLimitedPwr;                  /* WPHY�������ʻ��˺��������ƹ���,��λ0.1dbm */
    VOS_UINT16                          uhwWcdmaSarAdjudgePeriod;               /* WPHYʱ��ƽ��SAR���о�����,��3���ӻ�6����,��λs */
}UCOM_NV_W_SAR_TIME_AVG_SAR_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_SELF_CAL_ENABLE
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ƿ�ʹ���·���У׼XO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwXoCalEnable;                         /* �Ƿ�ʹ���·���У׼ */
    VOS_UINT16                          uhwReserve;
}UCOM_NV_XO_SELF_CAL_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_SELF_CAL_DONE
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ƿ���ʹ���·���У׼XO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwXoCalDone;                           /* �Ƿ���ʹ���·���У׼ */
    VOS_UINT16                          uhwReserve;
}UCOM_NV_XO_SELF_CAL_DONE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_REF_TEMP_COMP
 Э����  :
 ASN.1���� :
 �ṹ˵��  : XOУ׼�������
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwXoRefTemp;                           /* XO�ο��¶� */
    VOS_UINT16                          uhwReserve;
    VOS_UINT16                          uhwA2Exponent;                          /* ���δ��a2��ָ�� */
    VOS_UINT16                          uhwA3Exponent;                          /* ���δ��a3��ָ�� */
    VOS_UINT32                          uwA2Mantissa;                           /* ���δ��a2��β�� */
    VOS_UINT32                          uwA3Mantissa;                           /* ���δ��a3��β�� */
    VOS_UINT16                          uhwA2ExponentDefault;                   /* ���δ��a2��ָ�� */
    VOS_UINT16                          uhwA3ExponentDefault;                   /* ���δ��a3��ָ�� */
    VOS_UINT32                          uwA2MantissaDefault;                    /* ���δ��a2��β�� */
    VOS_UINT32                          uwA3MantissaDefault;                    /* ���δ��a3��β�� */
    VOS_INT16                           shwTmax;                                /* XO������¶� */
    VOS_INT16                           shwTmin;                                /* XO��С�����¶� */
}UCOM_NV_XO_REF_TEMP_COMP_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_SELF_CAL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : XOУ׼����
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   shwC1C2Temp;                    /* ��λ0.1�ȣ�C1C2У׼�������¶�����   */
    VOS_INT16                                   shwA0A1Temp;                    /* ��λ0.1�ȣ�a0��a1У׼��������¶����ޣ������һ����������¶� */
    VOS_UINT16                                  uhwA0A1Time;                    /*��λms��У׼a0��a1ʱ��ʱ������ */
    UCOM_NV_DCXO_TEMP_RISE_METHOD_ENUM_UINT16   enTempRiseMethod;               /*���·�����1��ʾAP���£�2��ʾPA���£�3��ʾAP��PAһ������ */
    VOS_INT16                                   shwTempRiseStep;                /* ��λ0.1��, У׼a0��a1ʱ��ÿ�����³������ٶȲɼ�һ��Ƶƫ��� */
    VOS_UINT16                                  uhwTempVsFreqNum;               /*�ɼ�����Ƶƫ��������a0��a1���� */
    VOS_UINT16                                  uhwGetTempTimeStep;             /*��λms��ÿ���¶ȶ�ȡ��� */
    VOS_UINT16                                  uhwRiseTimeStable;              /*��λms��AP��PA���º󣬵ȴ�����ʱ���ʼ�ɼ��¶�Ƶƫ��� */
    VOS_UINT16                                  uhwTotalCoreNum;                /*AP�ܹ��ĺ��� */
    VOS_UINT16                                  uhwRiseTempCoreNum;             /*AP���·�ʽ����ʼ�յ�AP�˵ĸ���  */
}UCOM_NV_XO_SELF_CAL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_XO_CAL_AGC_GAIN_INDEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : XOУ׼ʱRx AGC��λ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwRxLevel;                             /* ���е�λ */
    VOS_INT16                           shwToneLevel;                           /* ���������ź�ǿ�� */
}UCOM_NV_XO_CAL_AGC_GAIN_INDEX_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CSDR_HRPD_FIX_DRCVALUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : cdma hrpd csdr�̶�drcvalue��NV����
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwFixDrcValueFlag;                                     /* ����̶�drc value��־ */
    VOS_UINT16          uhwFixedDrcValue;                                       /* �̶���drc valueֵ */
}UCOM_NV_CSDR_HRPD_FIX_DRCVALUE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_JUDGE_BUSINESS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����о�ҵ�����Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uhwIdle         :4;                             /* ����״̬ UCOM_NV_INTERFE_BUSINESS_TYPE_IDLE */
    VOS_UINT32                  uhwData         :4;                             /* ����ҵ��״̬ UCOM_NV_INTERFE_BUSINESS_TYPE_PS*/
    VOS_UINT32                  uhwVoice        :4;                             /* ����ҵ��״̬ UCOM_NV_INTERFE_BUSINESS_TYPE_CS*/
    VOS_UINT32                  uhwReversed     :20;                            /* ���� */
}UCOM_NV_INTERFE_JUDGE_BUSINESS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ҵ�����Ͷ���
*****************************************************************************/
typedef union
{
    VOS_UINT32                              uhwInterJudgeBusiness;              /* �����о�ҵ������ */
    UCOM_NV_INTERFE_JUDGE_BUSINESS_STRU     stInterfeJudgeBusiness;             /* �����о�ҵ�����Ͷ���ֵ */
} UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION;

/*****************************************************************************
 �ṹ��    : UCOM_NV_POWER_BACKOFF_BUSINESS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʻ���ҵ�����Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uwOppositeIdle          :5;                            /* �Է�ģ����״̬ */
    VOS_UINT32                  uwCurrentIdle           :5;                            /* ��ǰģ����״̬ */
    VOS_UINT32                  uwOppositeData          :5;                            /* �Է�ģ����ҵ��״̬ */
    VOS_UINT32                  uwCurrentData           :5;                            /* ��ǰģ����ҵ��״̬ */
    VOS_UINT32                  uwOppositeVoice         :5;                            /* �Է�ģ����ҵ��״̬ */
    VOS_UINT32                  uwCurrentVoice          :5;                            /* ��ǰģ����ҵ��״̬ */
    VOS_UINT32                  uwReversed              :2;                            /* ���� */
}UCOM_NV_POWER_BACKOFF_BUSINESS_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_POWER_BACKOFF_BUSINESS_UNION
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʻ��˶���
*****************************************************************************/
typedef union
{
    VOS_UINT32                                      uwPowerBackoffBusiness;    /* ����ʻ���ҵ������ */
    UCOM_NV_POWER_BACKOFF_BUSINESS_STRU             stPowerBackoffBusines;     /* ����ʻ���ҵ�����Ͷ���ֵ */
} UCOM_NV_POWER_BACKOFF_BUSINESS_UNION;
/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_BAND_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ƶ�κ�ģʽ���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  uwCurrentBand           :8;                     /* ��ǰģƵ�� */
    VOS_UINT32                  uwCurrentMode           :8;                     /* ��ǰģģʽ����,0:GSM;1:WCDMA;2:LTE;3:TDS;4:CDMA */
    VOS_UINT32                  uwOppositeBand          :8;                     /* �Է�ģƵ�� */
    VOS_UINT32                  uwOppositeMode          :8;                     /* �Է�ģģʽ����,0:GSM;1:WCDMA;2:LTE;3:TDS;4:CDMA */
}UCOM_NV_INTERFE_BAND_MODE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_RULE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����о�һ�����ݶ���
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_BAND_MODE_STRU              stInterfeBandMode;              /* ��ǰ�Է�ģƵ�κ�ģʽ���Ͷ��� */

    UCOM_NV_INTERFE_JUDGE_BUSINESS_UNION        aunBusinessType[UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM];/* ҵ������ */

	VOS_UINT16                                  uhwGRxBlankingPower     : 12;   /* ��BAND\mode����£�Gִ��RX BLANKING�Ĺ������ޣ���λ0.1 DB */
	VOS_UINT16                                  uhwHarmonicTxBlanking   : 4;    /* г�����ӣ�0 ������г�����ţ�1 ����г������ */

    VOS_UINT16                                  uhwRxBlankLowFreq;              /* Rx Blanking��Χ��Ƶ�� */
    VOS_UINT16                                  uhwRxBlankHighFreq;             /* Rx Blanking��Χ��Ƶ�� */
    VOS_UINT16                                  uhwTxBlankLowFreq;              /* Tx Blanking��Χ��Ƶ�� */
    VOS_UINT16                                  uhwTxBlankHighFreq;             /* Tx Blanking��Χ��Ƶ�� */
} UCOM_NV_INTERFE_RULE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_RULE_TABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����о�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwValidCount;
    UCOM_NV_INTERFE_RULE_STRU                   stInterferenceRule[UCOM_NV_INTERFERENCE_TABLE_MAX_NUM]; /* �����о��� */
} UCOM_NV_INTERFE_RULE_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_BACKOFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʻ��˶���
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_BAND_MODE_STRU              stInterfeBandMode;              /* ��ǰ�Է�ģƵ�κ�ģʽ���Ͷ��� */
    UCOM_NV_POWER_BACKOFF_BUSINESS_UNION        aunBusinessType[UCOM_NV_INTERFERENCE_BUSINESS_TYPE_NUM];/* ҵ������ */
} UCOM_NV_INTERFE_BACKOFF_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_INTERFE_POWER_BACKOFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʻ��˱���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  uwValidCount;
    UCOM_NV_INTERFE_BACKOFF_STRU                stInterfePowerBackoff[UCOM_NV_INTERFERENCE_TABLE_MAX_NUM];/* ����ʻ��˱� */
} UCOM_NV_INTERFE_POWER_BACKOFF_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_FEATURE_INTERFE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Կ��ض���
*****************************************************************************/
typedef struct
{
    UCOM_NV_INTERFE_FEATURE_SWITCH_ENUM_UINT16          enInterfeSwitch;        /* ���Կ��� */
    VOS_UINT16                                          uhwReversed;            /* ����*/
} UCOM_NV_FEATURE_INTERFE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TAS_CTRL_WORD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���߽���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwCdmaAntMasPassThroughTasPassThroughCtrlWord;      /* ����MAS=0,TAS=0ʱ��GPIO������ */
    VOS_UINT32                              uwCdmaAntMasPassThroughTasSwapCtrlWord;             /* ����MAS=0,TAS=1ʱʱ��GPIO������ */
    VOS_UINT32                              uwCdmaAntMasSwapTasPassThroughCtrlWord;             /* ����MAS=1,TAS=0ʱ��GPIO������ */
    VOS_UINT32                              uwCdmaAntMasSwapTasSwapCtrlWord;                    /* ����MAS=1,TAS=1ʱʱ��GPIO������ */
}UCOM_NV_CDMA_TAS_CTRL_WORD_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_TAS_MAS_RF_CTRL_STRU
 Э����  :
 ASN.1���� : auwBandBlindSwitchMap�����ÿ��band�Ƿ�ʹ��TASä���㷨����bitmap��
             bitλΪ1�������bandʹ��ä���㷨������֮��
 �ṹ˵��  : TAS��Ƶ��ؿ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwBandBlindSwitchMap;               /* BAND�Ƿ�����ä�� */
    UCOM_NV_CDMA_TAS_CTRL_WORD_STRU         stTasCtrlWord;                      /* �����л������� */
    VOS_UINT32                              uwBandIaEnable;                     /* uwBandIaEnable �ӵ͵��߷ֱ����Bc0~Bc10�Ƿ�֧��Ia:0,��֧�֣�1��֧��*/
    VOS_UINT32                              uwBandIbEnable;                     /* uwBandIbEnable �ӵ͵��߷ֱ����Bc0~Bc10�Ƿ�֧��Ib:0,��֧�֣�1��֧��*/

}UCOM_NV_CDMA_TAS_MAS_RF_CTRL_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_HPRD_DRX_PAGING_OFFSET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : hrpd drxѰ��������ǰ������λslot
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          uhwHrpdDrxPagingOffset; /* hrpd drxѰ��������ǰ�� */
    VOS_UINT16                                          uhwReversed;            /* ����*/
} UCOM_NV_CDMA_HPRD_DRX_PAGING_OFFSET_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_1X_OCCUPY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1X�Ƿ�֧����ռ���أ�Ĭ�ϲ�֧����ռ
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwIs1xOccupyFlag;     /* �Ƿ�֧��1X��ռ���أ�����SVLTE,SRLTEʹ��ģʽ�ж� */
    VOS_UINT8           ucReserve[2];
} UCOM_NV_1X_OCCUPY_INFO_STRU;


typedef UCOM_NV_W_EXT_LNA_INFO_STRU           UCOM_NV_CDMA_EXT_LNA_INFO_STRU;
/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_EXT_LNA_COMMON_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LNA������Ϣ���������ּ�
*****************************************************************************/
typedef struct
{
    UCOM_NV_CDMA_EXT_LNA_INFO_STRU              astExtLnaInfo[UCOM_NV_CDMA_ANT_NUM];  /* ���ּ�LNA���� */
}UCOM_NV_CDMA_EXT_LNA_COMMON_INFO_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_CTRL_EXT_LNA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA����LNAʱ��AGC������
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_RX_AGC_CTRL_STRU      stRxAgcCtrl;

}UCOM_NV_CDMA_RX_AGC_CTRL_EXT_LNA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_VOICE_EXT_LNA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ+����LNA��AGC��λ�л�����
*****************************************************************************/
typedef UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU  UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_VOICE_EXT_LNA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_EXT_LNA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ģʽ+����LNA��AGC��λ�л�����
*****************************************************************************/
typedef UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU   UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_EXT_LNA_STRU;


/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_VOICE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ+������LNA��AGC��λ�л�����
*****************************************************************************/
typedef UCOM_NV_CDMA_RX_AGC_GAIN_SWITCH_THRESHOLD_STRU  UCOM_NV_CDMA_RX_AGC_SWITCH_THRD_VOICE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_HRPD_GAP_WORK_AROUND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : hrpd�Ƿ���"������300ms����ʱ����A9-AL Disconnected"��Ĭ�Ϲ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwGap300msWorkAroundEnable;                       /* ���ʹ��: 1 ʹ�ܣ�0 ��ʹ�� */
    VOS_UINT16          uhwReserved;
}UCOM_NV_CDMA_HRPD_GAP_WORK_AROUND_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_TX_HIGH_POWER_PROTECT_GPIO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Gģ���ʱ�����ؿ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              uwEnable;                           /* 1:��ʾ���ݹ��������ͬ���߿� */
    VOS_UINT32                              uwPowerThrd;                        /* �������ޣ�0.1dbm */
    VOS_UINT32                              uwHighPoweGpioValue;                /* ����ʱ������߿� */
    VOS_UINT32                              uwHighPoweGpioMask;                 /* ����ʱ������߿�mask */
}UCOM_NV_GSM_TX_HIGH_POWER_PROTECT_GPIO_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_C_TEST_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMA��������ר�ÿ��أ�Ĭ�ϲ������Զ�Ϊ�رա�0��ʾ���عر� 1��ʾ���ش�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwReserve1:3;
    VOS_UINT32                          uwTestRxPart:1;                         /* RFIC1 Rx�������Կ���,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwRfResetOpen:1;                        /* RFIC ʧ����λ�������Կ���,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwRfRecoveryOpen:1;                     /* RF Recovery�ؼ��Ĵ����ָ��������Կ���,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwRelAllOpen:1;                         /* Release All�������Կ���,1-��,0-�رգ�Ĭ�Ϲر� */
    VOS_UINT32                          uwReserve2:25;
}UCOM_NV_C_TEST_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_MIPI_APT_TIMING_CFG_STRU
 Э����  :
 �ṹ˵��  : PA�Ŀ�����Ϣ��ǰ��ʱ϶ͷ��Чʱ�䣬��λchip
*****************************************************************************/
typedef struct
{
    VOS_UINT16              auhwPaVccAndVbiasActiveTime[UCOM_NV_CDMA_TX_PA_MODE_NUM];
    VOS_UINT16              uhwTrigger1ActiveTime;
    VOS_UINT16              uhwTrigger2ActiveTime;
    VOS_UINT16              uhwReserved;
}UCOM_NV_CDMA_MIPI_APT_TIMING_CFG_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_APT_CTRL_PARA_STRU
 Э����  :
 �ṹ˵��  : APT������Ϣ
*****************************************************************************/
typedef struct
{
    UCOM_NV_W_APT_CTRL_STRU                stAptCtrlInfo;
    UCOM_NV_MIPI_CMD_STRU                  astPaVccMipiCmdPaStatus[UCOM_NV_CDMA_TX_PA_MODE_NUM];     /* PA Vcc��mipi����ָ��,������APT��,���е����� */
    UCOM_NV_MIPI_CMD_STRU                  astPaVbias1MipiCmdPaStatus[UCOM_NV_CDMA_TX_PA_MODE_NUM];  /* ����PA Vbias1�Ŀ���ָ�������APT�� */
    UCOM_NV_MIPI_CMD_STRU                  astPaVbias2MipiCmdPaStatus[UCOM_NV_CDMA_TX_PA_MODE_NUM];  /* ����PA Vbias2�Ŀ���ָ�������APT�� */
    UCOM_NV_MIPI_CMD_STRU                  astPaVbias3MipiCmdPaStatus[UCOM_NV_CDMA_TX_PA_MODE_NUM];  /* ����PA Vbias3�Ŀ���ָ�������APT�� */
    UCOM_NV_W_APT_MIPI_PA_TRIGGER_STRU     stMipiPaTrigger;                                  /* Mipi PA Triggerָ���֤APT����Paָ��ͬʱ��Ч�������ٽ����  */
    UCOM_NV_CDMA_MIPI_APT_TIMING_CFG_STRU  stMipiAptTimingInfo;                              /* PA�Ŀ�����Ϣ��ǰ��ʱ϶ͷ��Чʱ�䣬��λchip */
}UCOM_NV_CDMA_APT_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_ABB_HARMONY_OPT_ENABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : abbг�����Ż�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                   uwEnable;                      /* 0:�رչ��� 1:��ABBг�����Ż����� */
    VOS_UINT16                                   uhwReserved;                   /* ���� */
}UCOM_NV_W_ABB_HARMONY_OPT_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_GSM_CS_TX_PCL_OPTI_CTRL_STRU
 �ṹ˵��  : GSM��Ƶ�����з��书���쳣�������Ż����ò���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwPclOptiEn;                       /* �������з��书��ʹ�ܿ��� 0--�ر� 1--�� */
    VOS_UINT16                              uhwReserved;                        /* �����ֶ� */
    VOS_UINT16                              uhwPclOptiThd;                      /* ͨ��·��������з��书�ʷ�������Ч���� */
    VOS_UINT16                              uhwTxPclMaxStep;                    /* ͨ��·��������з��书��̧�����PCL���� */
    VOS_INT16                               shwDlTxLevel;                       /* ��վ��������书�� */
    VOS_INT16                               shwUlRxRefSensLevel;                /* ��վ���н��������ȵ�ƽ */
}UCOM_NV_GSM_CS_TX_PCL_OPTI_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_CDMA_HRPD_DRC_LEN_MISMATCH_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������õ�DRC LengthΪ2��slots����8��slotsʱ��
             ��⵽DRC Length��ƥ����Ƿ���DRC LengthΪ4��slots��
             Ĭ��ʹ�ܳ��ԡ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16          uhwDrcLenMismatchEnable;                                /* ʹ�ܳ���4 slots: 1; ��ʹ��: 0 */
    VOS_UINT16          uhwReserved;
}UCOM_NV_CDMA_HRPD_DRC_LEN_MISMATCH_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : UCOM_NV_W_FDPCH_SYNC_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FDPCHͬʧ��FDPCH TPC BER����NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwFDpchQin;                        /* FDPCHͬ������ */
    VOS_UINT16                              uhwFDpchQout;                       /* FDPCHʧ������ */
}UCOM_NV_W_FDPCH_SYNC_THRESHOLD_STRU;

/****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/







#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of PhyNvDefine.h */


