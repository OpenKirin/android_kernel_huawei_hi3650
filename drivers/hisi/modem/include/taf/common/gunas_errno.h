/******************************************************************************

                  ��Ȩ���� (C), 2003-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : gunas_errno.h
  �� �� ��   : ����
  ��    ��   : ��ˮ��/wx247453
  ��������   : 2015��8��25��
  ����޸�   :
  ��������   : gunas���������ӿڵ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��25��
    ��    ��   : ��ˮ��/wx247453
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __GUNAS_ERRNO_H__
#define __GUNAS_ERRNO_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(push)
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_REBOOT_MOD_ID_ENUM
 ö��˵��  : ��ǰ������ID����
 1.��    ��   : 2011��12��13��
   ��    ��   : w00167002
   �޸�����   : �½�
 2.��    ��   : 2011��12��04��
   ��    ��   : z00359541
   �޸�����   : DTS2015112803743: ����24 Bit��λ�Ա�������FID������ջ��Ϣ
*****************************************************************************/
enum NAS_REBOOT_MOD_ID_ENUM
{
    NAS_REBOOT_MOD_ID_MML     = 0X61000000,

    NAS_REBOOT_MOD_ID_MSCC    = 0X62000000,

    NAS_REBOOT_MOD_ID_DYNLOAD = 0X63000000,

    NAS_REBOOT_MOD_ID_XSD     = 0X64000000,
    NAS_REBOOT_MOD_ID_HSD     = 0X65000000,

    NAS_REBOOT_MOD_ID_RILD    = 0x66000000, /*RILD���𵥶���λ��DRV����*/
    NAS_REBOOT_MOD_ID_RESET   = 0x67000000, /*������λʧ�������DRV����*/

    NAS_REBOOT_MOD_ID_MEM     = 0x68000000,

    NAS_REBOOT_MOD_ID_USER    = 0x69000000, /* �û����������������λ */
    NAS_REBOOT_MOD_ID_MMA     = 0x6A000000,
    
    NAS_REBOOT_MOD_ID_BUTT    = 0X6FFFFFFF
};
typedef unsigned int NAS_REBOOT_MOD_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MML_REBOOT_SCEAN_ENUM
 ö��˵��  : MM��λ����
 1.��    ��   : 2015��1��27��
   ��    ��   : wx270776
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_REBOOT_SCEAN_ENUM
{
    NAS_MML_OTHER_REBOOT_SCENE                                                  = 0X00,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED                       = 0X01,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED                       = 0X02,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED                        = 0X03,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED                       = 0X04,

    NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED                     = 0X05,
    NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED                     = 0X06,
    NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED                      = 0X07,
    NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED                     = 0X08,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED                      = 0X09,

    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_LMM_RESUME_IND              = 0X0A,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_WAS_RESUME_IND              = 0X0B,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_TD_RESUME_IND               = 0X0C,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_GAS_RESUME_IND              = 0X0D,

    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_LMM_SUSPEND_IND                 = 0X0E,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_WAS_SUSPEND_IND                 = 0X0F,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_TD_SUSPEND_IND                  = 0X10,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_GAS_SUSPEND_IND                 = 0X11,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE                        = 0X12,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE                        = 0X13,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE                         = 0X14,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE                        = 0X15,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_ERR_IND                                = 0X16,
    NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE                           = 0X17,
    NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE                 = 0X18,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED                = 0x19,

    NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_START_CNF_EXPIRED                         = 0x1A,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_START_CNF_EXPIRED                         = 0x1B,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_TDS_START_CNF_EXPIRED                         = 0x1C,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_START_CNF_EXPIRED                         = 0x1D,

    NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_START_CNF_FAIL                            = 0x1E,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_START_CNF_FAIL                            = 0x1F,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_TDS_START_CNF_FAIL                            = 0x20,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_START_CNF_FAIL                            = 0x21,
    NAS_MML_REBOOT_SCENE_MMA_WAIT_PHY_INIT_FAIL                                 = 0x22,
    NAS_MML_REBOOT_SCENE_MMA_WAIT_PHY_INIT_EXPIRED                              = 0x23,

    NAS_MML_REBOOT_SCENE_MMC_WAIT_SLAVE_MODE_UTRAN_MODE_CNF_EXPIRED             = 0x24,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_MASTER_MODE_UTRAN_MODE_CNF_EXPIRED            = 0x25,

    NAS_MML_REBOOT_SCENE_MMA_WAIT_MSCC_START_CNF_EXPIRED                        = 0x26,
    NAS_MML_REBOOT_SCENE_MMA_WAIT_MSCC_POWER_OFF_CNF_EXPIRED                    = 0x27,    
};
typedef unsigned char NAS_MML_REBOOT_SCENE_ENUM_UINT8;

#pragma pack(pop)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of gunas_errno.h */
