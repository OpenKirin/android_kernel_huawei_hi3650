/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : plat_firmware.h
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : plat_firmware.cͷ�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PLAT_FIRMWARE_H__
#define __PLAT_FIRMWARE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "plat_type.h"
#include "oal_net.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_exception_rst.h"
#endif
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* string */
#define OS_MEM_SET(dst, data, size)         memset(dst, data, size)
#define OS_MEM_CPY(dst, src, size)          memcpy(dst, src, size)
#define OS_MEM_CMP(dst, src, size)          memcmp(dst, src, size)
#define OS_STR_CMP(dst, src)                strcmp(dst, src)
#define OS_STR_LEN(s)                       strlen(s)
#define OS_STR_CHR(str, chr)                strchr(str, chr)
#define OS_STR_STR(dst, src)                strstr(dst, src)

/* memory */
#define OS_MEM_KFREE(p)                     kfree(p)
#define OS_KMALLOC_GFP(size)                kmalloc(size, GFP_KERNEL)
#define OS_KZALLOC_GFP(size)                kzalloc(size, GFP_KERNEL)
#define OS_VMALLOC_GFP(size)                vmalloc(size)
#define OS_MEM_VFREE(p)                     vfree(p)

#define READ_MEG_TIMEOUT            (200)      /* 200ms */
#define READ_MEG_JUMP_TIMEOUT       (15000)   /* 15s */

#define FILE_CMD_WAIT_TIME_MIN      (5000)     /* 5000us */
#define FILE_CMD_WAIT_TIME_MAX      (5100)     /* 5100us */

#define SEND_BUF_LEN                (520)
#define RECV_BUF_LEN                (512)
#define VERSION_LEN                 (64)

#define READ_CFG_BUF_LEN            (2048)

#define DOWNLOAD_CMD_LEN            (32)
#define DOWNLOAD_CMD_PARA_LEN       (800)

#define HOST_DEV_TIMEOUT            (3)
#define INT32_STR_LEN               (32)

#define SHUTDOWN_TX_CMD_LEN         (64)

#define CMD_JUMP_EXEC_RESULT_SUCC   (0)
#define CMD_JUMP_EXEC_RESULT_FAIL   (1)

#define WIFI_MODE_2_4G              (0)
#define WIFI_MODE_5G                (1)

#define SOFT_WCPU_EN_ADDR           "0x50000c00"
#define SOFT_BCPU_EN_ADDR           "0x50000c04"
#define BCPU_DE_RESET_ADDR          "0x50000094"

/*�����Ƿ���device����Ĺؼ���*/
#define VER_CMD_KEYWORD             "VERSION"
#define JUMP_CMD_KEYWORD            "JUMP"
#define FILES_CMD_KEYWORD           "FILES"
#define SETPM_CMD_KEYWORD           "SETPM"
#define SETBUCK_CMD_KEYWORD         "SETBUCK"
#define SETSYSLDO_CMD_KEYWORD       "SETSYSLDO"
#define SETNFCRETLDO_CMD_KEYWORD    "SETNFCRETLDO"
#define SETPD_CMD_KEYWORD           "SETPD"
#define SETNFCCRG_CMD_KEYWORD       "SETNFCCRG"
#define SETABB_CMD_KEYWORD          "SETABB"
#define SETTCXODIV_CMD_KEYWORD      "SETTCXODIV"
#define RMEM_CMD_KEYWORD            "READM"
#define WMEM_CMD_KEYWORD            "WRITEM"
#define QUIT_CMD_KEYWORD            "QUIT"

/*���������ֲ��ᷢ��device�����ڿ���У׼���̣����ǻ�������cfg�ļ���*/
#define CALI_COUNT_CMD_KEYWORD      "CALI_COUNT"
#define CALI_BFGX_DATA_CMD_KEYWORD  "CALI_BFGX_DATA"
#define SHUTDOWN_WIFI_CMD_KEYWORD   "SHUTDOWN_WIFI"
#define SHUTDOWN_BFGX_CMD_KEYWORD   "SHUTDOWN_BFGX"

/*������device������ִ�гɹ����صĹؼ��֣�host�յ�һ�¹ؼ���������ִ�гɹ�*/
#define MSG_FROM_DEV_WRITEM_OK      "WRITEM OK"
#define MSG_FROM_DEV_READM_OK       ""
#define MSG_FROM_DEV_FILES_OK       "FILES OK"
#define MSG_FROM_DEV_READY_OK       "READY"
#define MSG_FROM_DEV_JUMP_OK        "JUMP OK"
#define MSG_FROM_DEV_SET_OK         "SET OK"
#define MSG_FROM_DEV_QUIT_OK        ""

/*������cfg�ļ���������Ĳ���ͷ��һ���Ϸ���cfg�����ʽΪ:����ͷ+����ؼ���(QUIT�������)*/
#define FILE_TYPE_CMD_KEY           "ADDR_FILE_"
#define NUM_TYPE_CMD_KEY            "PARA_"

#define COMPART_KEYWORD             ' '
#define CMD_LINE_SIGN               ';'

#define CFG_INFO_RESERVE_LEN        (8)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum return_type
{
    SUCC = 0,
    EFAIL,
};

enum FIRMWARE_CFG_CMD_ENUM
{
    ERROR_TYPE_CMD = 0,            /* ��������� */
    FILE_TYPE_CMD,                 /* �����ļ������� */
    NUM_TYPE_CMD,                  /* �������ò��������� */
    QUIT_TYPE_CMD,                 /* �˳����� */
    SHUTDOWN_WIFI_TYPE_CMD,        /* SHUTDOWN WCPU���� */
    SHUTDOWN_BFGX_TYPE_CMD         /* SHUTDOWN BCPU���� */
};

/*
*1.�״ο���ʱ��ʹ��BFGN_AND_WIFI_CFG������״ο���У׼��host����У׼���ݣ���ɺ�device�µ�
*2.deivce�µ�״̬����wifi��ʹ��BFGN_AND_WIFI_CFG
*3.deivce�µ�״̬����bt��ʹ��BFGX_CFG
*4.bt�������ٿ�wifi��ʹ��WIFI_CFG
*5.wifi�������ٿ�bt��ͨ��sdio�⸴λBCPU
*/
enum FIRMWARE_CFG_FILE_ENUM
{
    BFGX_AND_WIFI_CFG = 0,         /*����BFGIN��wifi fimware����������index��ִ�ж���У׼*/
    WIFI_CFG,                      /*ֻ����wifi firmware����������������ִ�ж���У׼*/
    BFGX_CFG,                      /*ֻ����bfgx firmware������������������ִ�ж���У׼*/
    RAM_REG_TEST_CFG,              /*���߲���mem reg����ʹ��*/

    CFG_FILE_TOTAL
};

enum FIRMWARE_SUBSYS_ENUM
{
    DEV_WCPU = 0,
    DEV_BCPU,
    DEV_CPU_BUTT,
};

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct cmd_type_st
{
    int32       cmd_type;
    uint8       cmd_name[DOWNLOAD_CMD_LEN];
    uint8       cmd_para[DOWNLOAD_CMD_PARA_LEN];

}CMD_TYPE_STRUCT;

typedef struct firmware_globals_st
{
    int32            al_count[CFG_FILE_TOTAL];      /*�洢ÿ��cfg�ļ���������Ч���������*/
    CMD_TYPE_STRUCT *apst_cmd[CFG_FILE_TOTAL];      /*�洢ÿ��cfg�ļ�����Ч����*/
    uint8            auc_CfgVersion[VERSION_LEN];   /*�洢cfg�ļ������õİ汾����Ϣ*/
    uint8            auc_DevVersion[VERSION_LEN];   /*�洢����ʱdevice���ϱ��İ汾����Ϣ*/
}FIRMWARE_GLOBALS_STRUCT;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
typedef struct file OS_KERNEL_FILE_STRU;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern int32 firmware_download(uint32 ul_index);
extern int32 firmware_cfg_init(void);
extern int32 firmware_cfg_clear(void);
extern int32 sdio_device_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count);
extern void save_nfc_lowpower_log_2_sdt(void);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of plat_firmware.h */
