/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : kirin_partition.h
  �� �� ��   : ����
  ��        ��   : denghao 00221160
  ��������   : 2015��11��3��
  ����޸�   :
  ��������   : mmc_partition.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  ��    ��   : 2015��11��3��
  ��    ��   : denghao 00221160
  �޸�����   : �����ļ�

******************************************************************************/
#ifndef __KIRIN_PARTITION__
#define __KIRIN_PARTITION__

enum AB_PARTITION_TYPE{
	NO_SUPPORT_AB = 0,
	XLOADER_A = 1,
	XLOADER_B = 2,
	ERROR_VALUE = 3
};

extern enum AB_PARTITION_TYPE emmc_boot_partition_type;
extern enum AB_PARTITION_TYPE ufs_boot_partition_type;

extern int flash_find_ptn(const char* str, char* pblkname);
extern void flash_find_hisee_ptn(const char* str, char* pblkname);
extern int get_cunrrent_total_ptn_num(void);
extern int flash_get_ptn_index(const char* pblkname);
extern enum AB_PARTITION_TYPE get_device_boot_partition_type(void);
extern int set_device_boot_partition_type(char boot_partition_type);

#endif

