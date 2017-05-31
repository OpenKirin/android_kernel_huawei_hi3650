/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : util.h
  �� �� ��   : ����
  ��    ��   : ������ 00262566
  ��������   : 2015��1��23��
  ����޸�   :
  ��������   : �ṩ�Զ������Թ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��1��23��
    ��    ��   : ������ 00262566
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _AUDIO_AUTO_TEST_UTIL_H
#define _AUDIO_AUTO_TEST_UTIL_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include <linux/mm.h>
#include <linux/vmalloc.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define AT_SUCCESS  0
#define AT_FAILED  -1

#define at_util_mem_remap_writecombine(phys_addr, size)  at_util_mem_remap_type(phys_addr, size, pgprot_writecombine(PAGE_KERNEL))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* �Ĵ������� */
enum at_util_reg_type{
    WO = 0,
    RO,
    RW,
    RC,
    WC,
    RWC,
};

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

/* �Ĵ������� */
typedef struct at_util_reg_test_type
{
    unsigned int                        offset;                                 /* �Ĵ���ƫ��   */
    enum at_util_reg_type               rt;                                     /* �Ĵ�������   */
    unsigned int                        default_value;                          /* �Ĵ���Ĭ��ֵ */
    unsigned int                        value;                                  /* �Ĵ���ֵ     */
    unsigned int                        expect_value;                           /* �Ĵ�������ֵ */
}AT_REG_TEST_TYPE;

/*****************************************************************************
  5 ����ָ��
*****************************************************************************/


/*****************************************************************************
  6 OTHERS����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/


extern unsigned int at_util_reg_read_u32    (unsigned int pAddr);
extern void         at_util_reg_write_u32   (unsigned int pAddr, unsigned int value);
extern void        *at_util_mem_remap_type  (unsigned long phys_addr, size_t size, pgprot_t pgprot);
extern int          at_util_reg_test        (struct at_util_reg_test_type regs[], int size,
                                                int (*reg_read)     (unsigned int reg),
                                                void(*reg_write)    (unsigned int reg, unsigned int value));
extern struct file *at_util_log_file_open   (char *path, char *file_name);
extern int          at_util_log_file_close  (void);
extern int          at_util_log             (void *data_addr,unsigned int data_len);
extern void        *at_util_mem_remap_and_init (unsigned int phys_addr, size_t size,
                                                unsigned int init_value);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of _AUDIO_AUTO_TEST_UTIL_H */


