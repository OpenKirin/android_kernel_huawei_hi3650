/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifndef __HDLC_HARDWARE_H__
#define __HDLC_HARDWARE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"

#include "PPP/Inc/hdlc_interface.h"
#include "TTFComm.h"
#include "soc_hdlc_interface.h"
#if (VOS_LINUX == VOS_OS_VER)
#include <linux/io.h>
#endif


#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (VOS_RTOSCK == VOS_OS_VER)
#define     PS_PID_PPP_HDLC                                     MSPS_PID_PPPC

#define     PPP_HDLC_WRITE_32REG(pAddr, value)                  TTF_WRITE_32REG(pAddr, value)
#define     PPP_HDLC_READ_32REG(pAddr)                          TTF_READ_32REG(pAddr)

#define     PPP_IO_ADDRESS(a)                                   (a)

#else
#define     PS_PID_PPP_HDLC                                     PS_PID_APP_PPP
#define     PPP_HDLC_WRITE_32REG(pAddr, value)                  writel(value, (volatile unsigned int *)pAddr)
#define     PPP_HDLC_READ_32REG(pAddr)                          readl((volatile unsigned int *)pAddr)

#define     PPP_HDLC_MEM_MAP_SIZE                               (4096)  /* һ��ҳ����С���� */
#define     PPP_IO_ADDRESS(a)                                    ioremap((a),PPP_HDLC_MEM_MAP_SIZE)
#endif

/* 1.============================================================================================ */
/* definitions of bit basic operations */
#define GET_HIGH_WORD_FROM_DWORD(l)           ((VOS_UINT16)((((VOS_UINT32)(l)) >> 16) & 0xFFFF))
#define GET_LOW_WORD_FROM_DWORD(l)           ((VOS_UINT16)(VOS_UINT32)(l))
#define GET_HIGH_BYTE_FROM_WORD(w)           ((VOS_UINT8)(((VOS_UINT16)(w) >> 8) & 0xFF))
#define GET_LOW_BYTE_FROM_WORD(w)           ((VOS_UINT8)(w))
#define HDLC_MAKE_DWORD(hi,low)    ((VOS_UINT32)(((VOS_UINT16)(low))|(((VOS_UINT32)((VOS_UINT16)(hi)))<<16)))
#define HDLC_MAKE_WORD(hi,low)    ((VOS_UINT16)(((VOS_UINT8)(low))|(((VOS_UINT16)((VOS_UINT8)(hi)))<<8)))

#define GET_BITS_FROM_DWORD(DWord, BitMask) ((DWord) & (BitMask))
#define GET_BITS_FROM_WORD(Word, BitMask) ((Word) & (BitMask))
#define GET_BITS_FROM_BYTE(Byte, BitMask)  ((Byte) & (BitMask))
#define SET_BITS_VALUE_TO_BYTE(ucValue, ucStartBitPosition)     ((VOS_UINT8)(((VOS_UINT32)(ucValue)) << (ucStartBitPosition)))

#define SET_BIT_TO_BYTE(ucByte, ucBitPosition)          ((ucByte) |= (0x01 << (ucBitPosition)))
#define CLEAR_BIT_TO_BYTE(ucByte, ucBitPosition)        ((ucByte) &= ~(0x01 << (ucBitPosition)))

#define SET_BIT_TO_WORD(usWord, ucBitPosition)          ((usWord) |= (0x0001 << (ucBitPosition)))
#define CLEAR_BIT_TO_WORD(usWord, ucBitPosition)        ((usWord) &= ~(0x0001 << (ucBitPosition)))

#define SET_BIT_TO_DWORD(ulDWord, ucBitPosition)        ((ulDWord) |= (0x00000001 << (ucBitPosition)))
#define CLEAR_BIT_TO_DWORD(ulDWord, ucBitPosition)      ((ulDWord) &= ~(0x00000001 << (ucBitPosition)))

#define INSERT_BYTE_LAST(pstMem, pstData, usLen, byte) \
{ \
    pstData[usLen]     = pstData[usLen - 1]; \
    pstData[usLen - 1] = byte; \
    PPP_ZC_SET_DATA_LEN(pstMem, 1); \
}

/* ----------------HDLC�Ż������ڴ� START---------------- */
/* HDLC Master�豸ʹ���ڴ����ַ */
/* ���װ�������������������ڵ���� */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM        (20)

/* ���װ��������ڴ��С�ͻ���ַ
   HDLC_DEF_INPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_BUF_LEN        (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM * 12)

/* ���װ��������������������ܳ��� */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE       (13*1024)


/* һ�ν��װ���IP��/��PPP֡������ = һ�ν��װ������볤��/��СIP������(20B) */
#define TTF_HDLC_DEF_OUTPUT_MAX_NUM                 (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE/20)

/* ���װ��Ϣ�ϱ������� */
#define TTF_HDLC_DEF_RPT_MAX_NUM                    (TTF_HDLC_DEF_OUTPUT_MAX_NUM)

/* ���װ��Ϣ�ϱ��ռ��ڴ��С�ͻ���ַ
   һ�ν��װ��������IP��/��PPP֡����*sizeof(HDLC_FRM_RPT_NODE) */
#define TTF_HDLC_DEF_RPT_BUF_LEN                    (TTF_HDLC_DEF_RPT_MAX_NUM*8)

/* ((TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE / 6 + 1) * 8)
 * 6Ϊռ�����ռ����С��Ч֡
 * 8Ϊ���ֽڶ���
 * +1 ΪС������ȡ��
*/

#define TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN            (18 * 1024)

    /* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��ȣ����ṹ��HDLC_DEF_BUFF_INFO_STRU�仯ʱ��
        �ú�Ӧ����Ӧ�仯 */
#define TTF_HDLC_MASTER_DEF_BUF_LEN                 (TTF_HDLC_DEF_INPUT_PARA_LINK_BUF_LEN + \
                                                        TTF_HDLC_DEF_RPT_BUF_LEN + \
                                                        TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN)

/* ��װ�������������������ڵ���� */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM        (20)

/* ��װ��������������������ܳ��� */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE       (15*1024)

/* ��װ��������ڴ��С = TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_BUF_LEN        (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM * 12)

/* ��װ��Ϣ������ */
#define TTF_HDLC_FRM_RPT_MAX_NUM                    (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM)

/* ��װ��Ϣ�ϱ��ռ��ڴ��С�ͻ���ַ
   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_DEF_RPT_NODE) */
#define TTF_HDLC_FRM_RPT_BUF_LEN                    (TTF_HDLC_FRM_RPT_MAX_NUM * 8)

/* ��װ�������������������ڵ���� */
#define TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM       (40)

/* ��װ��������ڴ��С�ͻ���ַ
   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_FRM_OUTPUT_PARA_LINK_BUF_LEN       (TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * 12)

/* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��ȣ����ṹ��HDLC_FRM_BUFF_INFO_STRU�仯ʱ��
    �ú�Ӧ����Ӧ�仯 */
#define TTF_HDLC_MASTER_FRM_BUF_LEN                 (TTF_HDLC_FRM_INPUT_PARA_LINK_BUF_LEN + \
                                                        TTF_HDLC_FRM_RPT_BUF_LEN + \
                                                        TTF_HDLC_FRM_OUTPUT_PARA_LINK_BUF_LEN)

/* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define TTF_HDLC_MASTER_LINK_TOTAL_LEN              (TTF_GET_32BYTE_ALIGN_VALUE((TTF_HDLC_MASTER_DEF_BUF_LEN + \
                                                        TTF_HDLC_MASTER_FRM_BUF_LEN)))

/* ----------------HDLC�Ż������ڴ� END---------------- */

/* 2.============================================================================================ */

/* definition of bit positions and masks in a register */
/* ========================= 1.hdlc_frm_en (0x10) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_en��bit0;
*/
#define     HDLC_FRM_EN_BITPOS                                      (0UL)

/* ========================= 2.hdlc_def_en (0x60) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_en��bit0;
*/
#define     HDLC_DEF_EN_BITPOS                                      (0UL)

/* ========================= 3.hdlc_frm_cfg (0x20) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_in_lli_1dor2d��bit0;
        �Ĵ���frm_acfc��bit1;
*/
#define     HDLC_FRM_IN_LLI_1DOR2D_BITPOS                           (0UL)
#define     HDLC_FRM_ACFC_BITPOS                                    (1UL)
#define     HDLC_FRM_PFC_BITPOS                                     (2UL)

/*
   �Ĵ���frm_pfc(2bits)��ֵ����:
        00b: Ӳ��ģ�����P��, P����ѹ��;
        01b: Ӳ��ģ�����P��, P��ѹ��;
        11b: Ӳ��ģ�鲻���P��;
*/
#define     HDLC_PROTOCOL_ADD_WITHOUT_COMPRESS   (0x00)
#define     HDLC_PROTOCOL_ADD_WITH_COMPRESS      (0x01)
#define     HDLC_PROTOCOL_NO_ADD                 (0x03)

/* ========================= 4.hdlc_def_cfg (0x70) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_uncompleted_ago��bit0;
        �Ĵ���def_acfc��bit1;
*/
#define     HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS                      (0UL)
#define     HDLC_DEF_ACFC_BITPOS                                    (1UL)
#define     HDLC_DEF_PFC_BITPOS                                     (2UL)


/* �Ĵ���frm_protocol(16bits)��MASK�� */
#define     HDLC_FRM_PROTOCOL_MASK                       (0x0000FFFF)

/*
   �Ĵ���def_pfc(2bits)��ֵ����:
        00b: P����ѹ��, �����;
        01b: P��ѹ��, �����;
        11b: P�򲻰���;
*/
#define     HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS      (0x00)
#define     HDLC_PROTOCOL_REMOVE_WITH_COMPRESS         (0x01)
#define     HDLC_PROTOCOL_NO_REMOVE                    (0x03)

/* ========================= hdlc_prior_ctrl (0x04) begin ======================= */
/*
   �Ĵ���hdlc_prior_ctrl(2bits)��ֵ����:
        00b: ˭�ȱ�ʹ�����Ƚ�˭������;
        01b: ���з�װ���ȼ���;
        10b: ���н��װ���ȼ���;
        11b: ��Ч;
*/
#define     HDLC_PRIOR_FCFS               (0x00)
#define     HDLC_PRIOR_DL_FRM_HIGHER      (0x01)
#define     HDLC_PRIOR_UL_DEF_HIGHER      (0x02)
#define     HDLC_PRIOR_INVALID            (0x03)

/* ====================== ��װ״̬�Ĵ�����ַ hdlc_frm_status (0x28) begin ====================== */
/* ��װģ��״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x28 */

/* �Ĵ���frm_out_seg_num(16bits)��MASK�� */
#define     HDLC_FRM_OUT_SEG_NUM_MASK                       (0x0000FFFF)

/* �Ĵ���frm_valid_num(8bits)��MASK�� */
#define     HDLC_FRM_VALID_NUM_MASK                         (0x000000FF)

/* �Ĵ���frm_all_pkt_done(1bit)��MASK�� */
#define     HDLC_FRM_ALL_PKT_DONE_MASK                      (0x00000001)

/* ��ѯ��װ״̬��Ϣ������ */
#define     HDLC_FRM_STATUS_MASK                            (0x00000003)

/*
   �Ĵ���frm_block_done([0]λ)��ֵ����:
        0b: δ���һ���������ݴ���;
        1b: ���һ���������ݴ���;
*/
/*
   �Ĵ���frm_error_index([1]λ)��ֵ����:
        1b: ��װ��������;
*/
#define     HDLC_FRM_ALL_PKT_DOING                     (0x00)
#define     HDLC_FRM_ALL_PKT_DONE                      (0x01)
#define     HDLC_FRM_STOP_EXCEPTION_OCCUR              (0x02)
#define     HDLC_FRM_DONE_EXCEPTION_OCCUR              (0x03)




/* ======================= ���װ״̬�Ĵ�����ַdlc_def_status (0x88) begin ===================== */
/* �Ĵ���dlc_def_status(5bits)��MASK�� */
#define     HDLC_DEFRAMER_BLOCK_STATUS_MASK                     (0x0000001B)

/* ��ѯ���װ״̬��Ϣ������ */
#define     HDLC_DEF_STATUS_MASK                                (0x0000003B)

/*
   �Ĵ���dlc_def_status(5bits)��ֵ����:
        000000b: δ���һ�����ݴ���;
        010000b: δ���һ�����ݴ������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ;
        001000b: δ���һ�����ݴ���, ���װ�ⲿ����洢�ռ������ͣ;
        000001b: δ���һ�����ݴ���, �ѽ��LCP֡, Ӳ��������ͣ״̬;
        000010b: ���һ�����ݴ���, ����֡�ϱ�;
        000011b: ���һ�����ݴ���, ����֡�ϱ�;
        1xx0xxb: ���쳣����;
*/
#define     HDLC_DEF_STATUS_DOING                               (0x00)
#define     HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL                (0x10)
#define     HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL             (0x08)
#define     HDLC_DEF_STATUS_PAUSE_LCP                           (0x01)
#define     HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES                 (0x02)
#define     HDLC_DEF_STATUS_DONE_WITH_FRAMES                    (0x03)

/* 3.============================================================================================ */
/* definition of HDLC module: FRAMER, DEFRAMER */
#define     HDLC_FRM_MODULE                                     (0UL)
#define     HDLC_DEF_MODULE                                     (1UL)

/* definition of PPP Link type */
#define     HDLC_IP_MODE                                        (0UL)
#define     HDLC_PPP_MODE                                       (1UL)

/* ���װ�Ƿ��з�����֡��ʶ */
#define     HDLC_DEF_UNCOMPLETED_NOT_EXIST                      (0x0)
#define     HDLC_DEF_UNCOMPLETED_EXIST                          (0x1)

#define     HDLC_INPUT_PARA_LINK_MAX_SIZE                       (TTF_MAX(TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM, TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM))
#define     HDLC_OUTPUT_PARA_LINK_MAX_SIZE                      (TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM)

/* ����PPP ID��ȡ��Ӧ�ڴ棬��ʱֻ��һ·����Ϊ��ֵ�����������ж�· */
#define     HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId)              (&g_stUncompletedInfo)
#define     HDLC_DEF_GET_BUF_INFO(usPppId)                      (g_pstHdlcDefBufInfo)
#define     HDLC_FRM_GET_BUF_INFO(usPppId)                      (g_pstHdlcFrmBufInfo)

/* ���װ����ռ��ס�β��ַ�������ж��Ƿ��ƻ� */
#define     HDLC_DEF_OUTPUT_BUF_START_ADDR                      ((VOS_UINT8 *)(&g_pstHdlcDefBufInfo->aucOutputDataBuf[0]))
#define     HDLC_DEF_OUTPUT_BUF_END_ADDR                        (HDLC_DEF_OUTPUT_BUF_START_ADDR + TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN)

/* ��ѯ��װ����װ��ɵĴ��� */
#ifndef  __UT_CENTER__
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#else
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0x01)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0x01)
#endif

/* �ȴ���װ����װ��Ӧ�ж�ʱ��,�Ժ���Ϊ��λ */
#define     HDLC_FRM_MASTER_INT_TIMER_LEN                       (5000)
#define     HDLC_DEF_MASTER_INT_TIMER_LEN                       (5000)

/* Լ����Ӳ��, ��װһ������ύ1502�ֽڸ�Framer */
#define     HDLC_FRM_IN_PER_MAX_CNT                             (1502L)
#define     HDLC_FRM_OUT_PER_MAX_CNT                            (3013UL)

/* ���װ��󵥸����ݳ���,���HDLC BUG,��󳤶���Ҫ+1,����C����,���Ȳ������� */
#if (VOS_RTOSCK == VOS_OS_VER)
#define     PPP_ZC_MAX_DATA_LEN                                 (1536)            /* �������ڴ����󳤶� */
#define     HDLC_DEF_IN_PER_MAX_CNT                             (PPP_ZC_MAX_DATA_LEN)
#else
#define     HDLC_DEF_IN_PER_MAX_CNT                             (PPP_ZC_MAX_DATA_LEN + 1)
#endif

/* ���װ�ϱ�ÿ֡�1502�ֽ�, IPv4�1500�ֽ�, PPPģʽ����Э���ֶ�2�ֽ�, ��1502�ֽ� */
#define     HDLC_DEF_OUT_PER_MAX_CNT                            (1502UL)

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ��ʱ��,��λ���� */
#define     HDLC_FRM_TIME_INTERVAL                              (100)

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ������ */
#if (VOS_RTOSCK == VOS_OS_VER)
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (PPPC_HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL)
#else
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (10)
#endif

/* ��װ���ڴ����ֵ */
#define     HDLC_FRM_GET_MAX_FRAMED_LEN(usLen)                  (2*usLen + 13)

/* ������ѯ�����ж�ʹ�ܵ�ˮ�ߣ�Ĭ��ֵ */
#define     HDLC_DEF_INTERRUPT_LIMIT_DEFAULT                    (2*1024)
#define     HDLC_FRM_INTERRUPT_LIMIT_DEFAULT                    (2*1024)

/* ������ѯ�����ж�ʹ�ܵ�ˮ�� */
#if (VOS_OS_VER == VOS_WIN32)
/* PC���޷�ģ���жϣ���ʹ�ò�ѯ */
#define     HDLC_DEF_INTERRUPT_LIMIT                            (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE + 1)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE + 1)
#else
#define     HDLC_DEF_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcDefIntLimit)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcFrmIntLimit)
#endif

/* AXI���߶�д����ʱ���ж�ֵ����ֵ��SoC�ṩ������������� */
#define     HDLC_AXI_REQ_TIMEOUT_VALUE                          (255)

/* ���װ�������͸��� */
#define     HDLC_DEF_MAX_TYPE_CNT                               (7UL)

/* ��ά�ɲ�������ڴ���󳤶ȣ���ֹ��Ϊ��ά�ɲ����벻���ڴ浼�µ��帴λ */
#define     HDLC_MNTN_ALLOC_MEM_MAX_SIZE                        (2*1024)

/*
   �����쳣��Ϣbitλ��:
        bit0�����Ƿ�����쳣����(1�ǽ����쳣����0��û�н����쳣����);
        bit1�����Ƿ����жϴ���(1���жϴ���0����ѯ����);
        bit2�����Ƿ�ȴ��ź�����ʱ(1�ǣ�0��);
        bit3�����Ƿ���ѯ��ʱ(1�ǣ�0��);
*/
#define     HDLC_EXCEPTION_IND_BITPOS                           (0UL)
#define     HDLC_INTERRUPT_IND_BITPOS                           (1UL)
#define     HDLC_SEM_TIMEOUT_IND_BITPOS                         (2UL)
#define     HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS                 (3UL)

#define     PPP_HDLC_CACHE_INVALID(data, len)                   dma_map_single(0, data, len, DMA_FROM_DEVICE)
#define     PPP_HDLC_CACHE_FLUSH(data, len)                     dma_map_single(0, data, len, DMA_TO_DEVICE)

/* =========V3R3��ʹ��: HDLCʱ���ڼĴ���SC_PERIPH_CLKEN0 �� C_PERIPH_CLKDIS0 16bit��λ��======== */
#define     HDLC_PERIPH_CLK_BITPOS                              (16UL)

#if (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
/* =========dallas��ʹ��: HDLCʱ���ڼĴ���CRG_CLKEN4 �� CRG_CLKDIS4 24bit��λ��======== */
#define     HDLC_CRG_CLK_BITPOS                                 (24UL)

#else
/* =========V7R2��ʹ��: HDLCʱ���ڼĴ���CRG_CLKEN4 �� CRG_CLKDIS4 10bit��λ��======== */
#define     HDLC_CRG_CLK_BITPOS                                 (10UL)

#endif

#if (SC_CTRL_MOD_P532 == SC_CTRL_MOD)
#define     HDLC_CRG_CLKEN_OFFSET                               (0x24)      /* HDLCʱ��ʹ��OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x28)      /* HDLCʱ�ӹر�OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x2C)      /* HDLCʱ��״̬OFFSET */

#elif ((SC_CTRL_MOD_6950_SFT == SC_CTRL_MOD) || (SC_CTRL_MOD_6932_SFT == SC_CTRL_MOD))
#define     HDLC_CRG_CLKEN_OFFSET                               (0x30)      /* HDLCʱ��ʹ��OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x34)      /* HDLCʱ�ӹر�OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x38)      /* HDLCʱ��״̬OFFSET */

#elif (SC_CTRL_MOD_6250_SFT == SC_CTRL_MOD)
/* =========dallas��ʹ��: HDLCʱ��ʹ�ܿ��ƼĴ���MDM_CRG_CLKEN0��
                          HDLCʱ�ӹرտ��ƼĴ���MDM_CRG_CLKDIS0��
                          HDLCʱ�ӿ���״̬MDM_CRG_CLKSTAT0��Ի���ַ��ƫ��======== */
#define     HDLC_CRG_CLKEN_OFFSET                               (0x00)      /* HDLCʱ��ʹ��OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x04)      /* HDLCʱ�ӹر�OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x08)      /* HDLCʱ��״̬OFFSET */

#else
#define     HDLC_CRG_CLKEN_OFFSET                               (0x30)      /* HDLCʱ��ʹ��OFFSET */
#define     HDLC_CRG_CLKDIS_OFFSET                              (0x34)      /* HDLCʱ�ӹر�OFFSET */
#define     HDLC_CRG_CLKSTAT_OFFSET                             (0x38)      /* HDLCʱ��״̬OFFSET */

#endif

/* =========ʱ��ʹ�ܼĴ���======== */
#define     HDLC_CRG_CLKEN4_ADDR(base)                          ((base) + (HDLC_CRG_CLKEN_OFFSET))

/* =========ʱ�ӹرռĴ���======== */
#define     HDLC_CRG_CLKENDIS4_ADDR(base)                       ((base) + (HDLC_CRG_CLKDIS_OFFSET))

/* =========ʱ��״̬�Ĵ���======== */
#define     HDLC_CRG_CLKSTA4_ADDR(base)                         ((base) + (HDLC_CRG_CLKSTAT_OFFSET))

#define     HDLC_DMA_VIRT_TO_PHY(ulVirtAddr)                    ((ulVirtAddr) - (g_ulPppVirtAddr) + (g_ulPppPhyAddr))
#define     HDLC_DMA_PHY_TO_VIRT(ulPhyAddr)                     ((ulPhyAddr) - (g_ulPppPhyAddr) + (g_ulPppVirtAddr))


#if (VOS_RTOSCK== VOS_OS_VER)
#define PPP_HDLC_INFO_LOG(String) \
            PPPC_INFO_LOG(String)
#define PPP_HDLC_INFO_LOG1(String, Para1) \
            PPPC_INFO_LOG1(String, Para1)
#define PPP_HDLC_INFO_LOG2(String, Para1, Para2) \
            PPPC_INFO_LOG2(String, Para1, Para2)
#define PPP_HDLC_INFO_LOG3(String, Para1, Para2, Para3) \
            PPPC_INFO_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_INFO_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_INFO_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_NORMAL_LOG(String) \
            PPPC_WARNING_LOG(String)
#define PPP_HDLC_NORMAL_LOG1(String, Para1) \
            PPPC_WARNING_LOG1(String, Para1)
#define PPP_HDLC_NORMAL_LOG2(String, Para1, Para2) \
            PPPC_WARNING_LOG2(String, Para1, Para2)
#define PPP_HDLC_NORMAL_LOG3(String, Para1, Para2, Para3) \
            PPPC_WARNING_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_NORMAL_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_WARNING_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_WARNING_LOG(String) \
            PPPC_WARNING_LOG(String)
#define PPP_HDLC_WARNING_LOG1(String, Para1) \
            PPPC_WARNING_LOG1(String, Para1)
#define PPP_HDLC_WARNING_LOG2(String, Para1, Para2) \
            PPPC_WARNING_LOG2(String, Para1, Para2)
#define PPP_HDLC_WARNING_LOG3(String, Para1, Para2, Para3) \
            PPPC_WARNING_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_WARNING_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_WARNING_LOG4(String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_ERROR_LOG(String) \
            PPPC_ERROR_LOG(String)
#define PPP_HDLC_ERROR_LOG1(String, Para1) \
            PPPC_ERROR_LOG1(String, Para1)
#define PPP_HDLC_ERROR_LOG2(String, Para1, Para2) \
            PPPC_ERROR_LOG2(String, Para1, Para2)
#define PPP_HDLC_ERROR_LOG3(String, Para1, Para2, Para3) \
            PPPC_ERROR_LOG3(String, Para1, Para2, Para3)
#define PPP_HDLC_ERROR_LOG4(String, Para1, Para2, Para3, Para4) \
            PPPC_ERROR_LOG4(String, Para1, Para2, Para3, Para4)
#else
#define PPP_HDLC_INFO_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String)
#define PPP_HDLC_INFO_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1)
#define PPP_HDLC_INFO_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2)
#define PPP_HDLC_INFO_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2, Para3)
#define PPP_HDLC_INFO_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_INFO, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_NORMAL_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String)
#define PPP_HDLC_NORMAL_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1)
#define PPP_HDLC_NORMAL_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2)
#define PPP_HDLC_NORMAL_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2, Para3)
#define PPP_HDLC_NORMAL_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_NORMAL, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_WARNING_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String)
#define PPP_HDLC_WARNING_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1)
#define PPP_HDLC_WARNING_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2)
#define PPP_HDLC_WARNING_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2, Para3)
#define PPP_HDLC_WARNING_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_WARNING, String, Para1, Para2, Para3, Para4)
#define PPP_HDLC_ERROR_LOG(String) \
            PPP_MNTN_LOG(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String)
#define PPP_HDLC_ERROR_LOG1(String, Para1) \
            PPP_MNTN_LOG1(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1)
#define PPP_HDLC_ERROR_LOG2(String, Para1, Para2) \
            PPP_MNTN_LOG2(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2)
#define PPP_HDLC_ERROR_LOG3(String, Para1, Para2, Para3) \
            PPP_MNTN_LOG3(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2, Para3)
#define PPP_HDLC_ERROR_LOG4(String, Para1, Para2, Para3, Para4) \
            PPP_MNTN_LOG4(PS_PID_PPP_HDLC, 0, PS_PRINT_ERROR, String, Para1, Para2, Para3, Para4)
#endif


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum PPP_HDLC_PARA_CHECK_RESULT_ENUM
{
    PPP_HDLC_PARA_CHECK_PASS            = 0,      /* ��������Ҫ�󣬽������ݳ��� */
    PPP_HDLC_PARA_CHECK_FAIL_DISCARD    = 1,      /* ���ݰ�����������Ҫ����Ҫ���������Ǽ���������һ�����ݰ� */
    PPP_HDLC_PARA_CHECK_FAIL_KEEP       = 2,      /* ���ݰ�����������Ҫ�󣬵���Ҫ�����������´δ��� */

    PPP_HDLC_PARA_CHECK_BUTT
};
typedef VOS_UINT32   PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32;

enum HDLC_MNTN_EVENT_TYPE_ENUM
{
    ID_HDLC_MNTN_FRM_REG_BEFORE_EN     = 101,     /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_FRM_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_FRM_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_REG_BEFORE_EN,               /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_DEF_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_DEF_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,            /* _H2ASN_MsgChoice HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU */

    ID_HDLC_MNTN_EVENT_TYPE_BUTT         = 0xFFFF
};
typedef VOS_UINT32 HDLC_MNTN_EVENT_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����Ϣ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  5 STRUCT����
*****************************************************************************/
/* һ�����ݽ���Ĵ���֡��ͳ�� */
typedef struct
{
    VOS_UINT16  usFCSErrCnt;          /* FCS���� */
    VOS_UINT16  usLenLongCnt;         /* ֡���ȹ���, ����1502�ֽ� */
    VOS_UINT16  usLenShortCnt;        /* ֡���ȹ���, ����4�ֽ� */
    VOS_UINT16  usErrProtocolCnt;     /* Э���ֶβ�����xxxxxxx0, xxxxxxx1����ʽ */
    VOS_UINT16  usErrCtrlCnt;         /* �����ֶβ�Ϊ0xFF */
    VOS_UINT16  usErrAddrCnt;         /* ��ַ�ֶβ�Ϊ0x03 */
    VOS_UINT16  usFlagPosErrCnt;      /* 0x7D�������0x7E */
    VOS_UINT8   aucReserve[2];
} HDLC_DEF_ERR_FRAMES_CNT_STRU;

/*
   ��������ڵ�ṹ:
   �����֤���װ�������������ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
   ���ϵ��£���ַ���ӣ��ֱ�Ϊ�ڵ��ڴ�ָ�롢�ڵ㳤�ȡ��¸��ڵ��ַ��
   ����LEN��Ч16bits���ڵ�Half_Word����ַADDR 32bits
*/
typedef struct _HDLC_PARA_LINK_NODE_STRU
{
    VOS_UINT8                          *pucDataAddr;            /* �ò����ڵ�ָ���ڴ��ַ */
    VOS_UINT16                          usDataLen;              /* �ڴ泤�ȣ���λByte */
    VOS_UINT8                           aucReserve[2];
    struct _HDLC_PARA_LINK_NODE_STRU   *pstNextNode;            /* ָ����һ�������ڵ��ָ�� */
} HDLC_PARA_LINK_NODE_STRU;

#if (VOS_RTOSCK == VOS_OS_VER)
/* ���������������Ϣ */
typedef struct _HDLC_PARA_LINK_BUILD_PARA_STRU
{
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;             /* �������� */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usPppId;                /* PPP ID */
    VOS_UINT16                          usProtocol;             /* Э�����ͣ���װ��ʱ��ʹ�� */
    TTF_LINK_ST                        *pstDlDataQ;             /* �������ݶ��� */
    TTF_LINK_ST                        *pstUlDataQ;             /* �������ݶ��� */
} HDLC_PARA_LINK_BUILD_PARA_STRU;

/* ���������������Ϣ */
/*lint -e506*/
typedef struct _HDLC_PARA_LINK_BUILD_INFO_STRU
{
    VOS_UINT32                          ulDealCnt;              /* ���ι���������̴����ݶ������ܹ���������ݰ����� */
    VOS_UINT8                           ucRatMode;              /* ����ģʽ1X/HRPD */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulInputLinkNodeCnt;     /* �����������ڵ���� */
    VOS_UINT32                          ulInputLinkTotalSize;   /* �����������ڵ����ݰ��ܳ��� */
    PPPC_DATA_LINK_NODE_STRU           *apstInputLinkNode[HDLC_INPUT_PARA_LINK_MAX_SIZE];   /* �����������ڵ��Ӧ���㿽���ڴ� */
    VOS_UINT32                          ulOutputLinkNodeCnt;                                /* �����������ڵ������ֻ�ڷ�װ��Ч */
    VOS_UINT32                          ulOutputLinkTotalSize;                              /* �����������ڵ����ݰ��ܳ��ȣ�ֻ�ڷ�װ��Ч */
    PPPC_DATA_LINK_NODE_STRU           *apstOutputLinkNode[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* �����������ڵ��Ӧ���㿽���ڴ棬ֻ�ڷ�װ��Ч */
} HDLC_PARA_LINK_BUILD_INFO_STRU;
/*lint +e506*/
#else
/* ���������������Ϣ */
typedef struct _HDLC_PARA_LINK_BUILD_PARA_STRU
{
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;             /* �������� */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usPppId;                /* PPP ID */
    VOS_UINT16                          usProtocol;             /* Э�����ͣ���װ��ʱ��ʹ�� */
    PPP_ZC_QUEUE_STRU                  *pstDataQ;               /* ���ݶ��� */
} HDLC_PARA_LINK_BUILD_PARA_STRU;

/* ���������������Ϣ */
/*lint -e506*/
typedef struct _HDLC_PARA_LINK_BUILD_INFO_STRU
{
    VOS_UINT32                          ulDealCnt;              /* ���ι���������̴����ݶ������ܹ���������ݰ����� */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* �����������ڵ���� */
    VOS_UINT32                          ulInputLinkTotalSize;   /* �����������ڵ����ݰ��ܳ��� */
    PPP_ZC_STRU *                       apstInputLinkNode[HDLC_INPUT_PARA_LINK_MAX_SIZE];   /* �����������ڵ��Ӧ���㿽���ڴ� */
    VOS_UINT32                          ulOutputLinkNodeCnt;                                /* �����������ڵ������ֻ�ڷ�װ��Ч */
    VOS_UINT32                          ulOutputLinkTotalSize;                              /* �����������ڵ����ݰ��ܳ��ȣ�ֻ�ڷ�װ��Ч */
    PPP_ZC_STRU *                       apstOutputLinkNode[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* �����������ڵ��Ӧ���㿽���ڴ棬ֻ�ڷ�װ��Ч */
} HDLC_PARA_LINK_BUILD_INFO_STRU;
/*lint +e506*/
#endif
/*
��װ�ϱ��ռ���ṹ:
�����֤��װ�ϱ��ռ���ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
���ϵ��£���ַ���ӣ��ֱ�Ϊ���������ʼ��ַ�����ݳ��ȣ�
����LEN��Ч16bits���ڵ�Half_Word����ַADDR 32bits
*/
typedef struct
{
    VOS_UINT8                          *pucFrmOutOneAddr;       /* ָ���װ������Ч֡������洢��ʼ��ַ */
    VOS_UINT16                          usFrmOutOneLen;         /* ��Ч֡�ĳ��� */
    VOS_UINT8                           aucReserve[2];
} HDLC_FRM_RPT_NODE_STRU;

/* �����װʹ�õ��ڴ� */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM];  /* ��װ�����������ʹ�õ��ڴ� */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* ��װ�����������ʹ�õ��ڴ� */
} HDLC_FRM_BUFF_INFO_STRU;


/*
���װ�ϱ��ռ���ṹ:
�����֤���װ�ϱ��ռ���ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
���ϵ��£���ַ���ӣ��ֱ�Ϊ�������Э�����͡����Ⱥʹ洢��ַ��
����LEN��Ч16bits���ڵ�Half_Word��Э��PRO��Ч16bits���ڸ�Half-Word����ַADDR 32bits
*/
typedef struct
{
    VOS_UINT16                          usDefOutOneLen;         /* ��Ч֡�ĳ��� */
    VOS_UINT16                          usDefOutOnePro;         /* ��Ч֡��Э�� */
    VOS_UINT8                          *pucDefOutOneAddr;       /* ָ����װ������Ч֡����洢����ʼ��ַ */
} HDLC_DEF_RPT_NODE_STRU;


/* ���װ������֡��Ϣ�洢�ṹ */
typedef struct
{
    VOS_UINT8                           ucExistFlag;            /* ������֡�Ƿ���ڱ�ʶ */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usDefOutOnePro;         /* ������֡��Э�� */
    VOS_UINT16                          usDefOutOneLen;         /* ������֡�ĳ��� */
    VOS_UINT8                          *pucDefOutOneAddr;       /* ָ����װ���ķ�����֡����洢����ʼ��ַ */
    VOS_UINT32                          ulDefStAgo;             /* ���ڱ���def_uncomplet_st_now�Ĵ���ֵ */
    VOS_UINT32                          ulDefInfoFrlCntAgo;     /* ���ڱ���def_info_frl_cnt_ago�Ĵ���ֵ */
} HDLC_DEF_UNCOMPLETED_INFO_STRU;

/* ������װʹ�õ��ڴ� */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM];/* ���װ�����������ʹ�õ��ڴ� */
    HDLC_DEF_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_DEF_RPT_MAX_NUM];                      /* ���װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
    VOS_UINT8                           aucOutputDataBuf[TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN];           /* ���װĿ�Ŀռ�ʹ�õ��ڴ� */
} HDLC_DEF_BUFF_INFO_STRU;

/* ������������ά�ɲ�ṹ */
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ */
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname;
}HDLC_MNTN_TRACE_HEAD_STRU;

/* ��װ��ؼĴ�����ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcFrmEn;
    VOS_UINT32                          ulHdlcFrmRawInt;
    VOS_UINT32                          ulHdlcFrmIntStatus;
    VOS_UINT32                          ulHdlcFrmIntClr;
    VOS_UINT32                          ulHdlcFrmCfg;
    VOS_UINT32                          ulHdlcFrmAccm;
    VOS_UINT32                          ulHdlcFrmStatus;
    VOS_UINT32                          ulFrmInLliAddr;
    VOS_UINT32                          ulFrmInSublliAddr;
    VOS_UINT32                          ulFrmInPktLen;
    VOS_UINT32                          ulFrmInBlkAddr;
    VOS_UINT32                          ulFrmInBlkLen;
    VOS_UINT32                          ulFrmOutLliAddr;
    VOS_UINT32                          ulFrmOutSpaceAddr;
    VOS_UINT32                          ulFrmOutSpaceDep;
    VOS_UINT32                          ulFrmRptAddr;
    VOS_UINT32                          ulFrmRptDep;
} HDLC_MNTN_FRM_REG_CONFIG_STRU;

/* ���װ��ؼĴ�����ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcDefEn;
    VOS_UINT32                          ulHdlcDefRawInt;
    VOS_UINT32                          ulHdlcDefIntStatus;
    VOS_UINT32                          ulHdlcDefIntClr;
    VOS_UINT32                          ulHdlcDefCfg;
    VOS_UINT32                          ulDefUncompletedLen;
    VOS_UINT32                          ulDefUncompletedPro;
    VOS_UINT32                          ulDefUncompletedAddr;
    VOS_UINT32                          ulDefUncompleteStAgo;
    VOS_UINT32                          ulHdlcDefGoOn;
    VOS_UINT32                          ulHdlcDefStatus;
    VOS_UINT32                          ulDefUncompletStNow;
    VOS_UINT32                          ulDefInLliAddr;
    VOS_UINT32                          ulDefInPktAddr;
    VOS_UINT32                          ulDefInPktLen;
    VOS_UINT32                          ulDefInPktLenMax;
    VOS_UINT32                          ulDefOutSpcAddr;
    VOS_UINT32                          ulDefOutSpaceDep;
    VOS_UINT32                          ulDefRptAddr;
    VOS_UINT32                          ulDefRptDep;
    VOS_UINT32                          ulHdlcDefErrInfor0;
    VOS_UINT32                          ulHdlcDefErrInfor1;
    VOS_UINT32                          ulHdlcDefErrInfor2;
    VOS_UINT32                          ulHdlcDefErrInfor3;
    VOS_UINT32                          ulDefInfoFr1CntAgo;
    VOS_UINT32                          ulDefInfoFr1CntNow;
} HDLC_MNTN_DEF_REG_CONFIG_STRU;

/* ���������������ݹ���*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usNodeIndex;
    VOS_UINT16                          usLen;
    /* VOS_UINT8[usLen]�������ݷ�����������ʱ����ͷ�����������ݳ��� */
}HDLC_MNTN_NODE_DATA_STRU;

/* ������������ά�ɲ�ṹ */
/*lint -e506*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* �����������ڵ���� */
    VOS_UINT32                          ulInputLinkTotalSize;   /* �����������ڵ����ݰ��ܳ��� */
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[HDLC_INPUT_PARA_LINK_MAX_SIZE];
}HDLC_MNTN_INPUT_PARA_LINK_STRU;
/*lint +e506*/

/* ��װ��������ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT8                           ucReserve1[1];
    VOS_UINT16                          usOutputNodeUsedCnt;
    VOS_UINT32                          ulOutputLinkNodeCnt;    /* �����������ڵ������ֻ�ڷ�װ��Ч */
    VOS_UINT32                          ulOutputLinkTotalSize;  /* �����������ڵ����ݰ��ܳ��ȣ�ֻ�ڷ�װ��Ч */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* ��װ�����������ʹ�õ��ڴ� */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
}HDLC_MNTN_FRM_OUTPUT_PARA_STRU;

/* ���װ������֡��ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    HDLC_DEF_UNCOMPLETED_INFO_STRU      stUncompletedInfo;
}HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU;

/* ���װ��������ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usDefValidNum;
    VOS_UINT16                          usTraceNum;
    /* HDLC_DEF_RPT_NODE_STRU[usDefValidNum]�˴�Ϊ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ棬
       �����ڴ�ʱ�ɽṹ���ȼ��ϱ��ռ���Ҫ���ڴ��С */
}HDLC_MNTN_DEF_OUTPUT_PARA_STRU;

/* HDLC���������Ϣ�ṹ */
typedef struct
{
    VOS_UINT_PTR                        ulHDLCIPBaseAddr;      /* �ӵ����ȡ��HDLC����ַ */
    VOS_UINT32                          ulHdlcDefMasterSem;    /* ���װ�ź��� */
    VOS_UINT32                          ulHdlcFrmMasterSem;    /* ��װ�ź��� */
    VOS_INT32                           slHdlcISRDef;          /* ���װ�жϺ� */
    VOS_INT32                           slHdlcISRFrm;          /* ��װ�жϺ� */
    VOS_UINT32                          ulHdlcDefIntLimit;     /* ���װ�ж�ˮ�� */
    VOS_UINT32                          ulHdlcFrmIntLimit;     /* ��װ�ж�ˮ�� */
    HTIMER                              stHdlcFrmTimerHandle;  /* �����װĿ�Ŀռ�ʧ�ܶ�ʱ����� */
    VOS_UINT32                          ulHdlcMntnTraceCfg;    /* ��ά�ɲ�ȼ����� */
}HDLC_CONFIG_INFO_STRU;

/* ͳ����Ϣ */
typedef struct
{
    VOS_UINT32                  ulDefIpDataProcCnt;             /* ���װIP���ݰ�������� */
    VOS_UINT32                  ulDefPppDataProcCnt;            /* ���װ��PPP֡������� */
    VOS_UINT32                  ulDefUncompleteCnt;             /* ���װ�з�����֡������� */
    VOS_UINT32                  ulDefWaitIntCnt;                /* ���װ�ȴ��жϴ��� */
    VOS_UINT32                  ulDefWaitQueryCnt;              /* ���װ�ȴ���ѯ���� */
    VOS_UINT32                  ulDefLcpPauseCnt;               /* ���װLCP��ͣ���� */
    VOS_UINT32                  ulDefFullPauseCnt;              /* ���װ����ռ���ϱ��ռ�����ͣ���� */
    VOS_UINT32                  ulDefInputDiscardCnt;           /* ���װ�������ݰ����� */

    VOS_UINT32                  ulFrmIpDataProcCnt;             /* ��װIP���ݰ�������� */
    VOS_UINT32                  ulFrmPppDataProcCnt;            /* ��װ��PPP֡������� */
    VOS_UINT32                  ulFrmWaitIntCnt;                /* ��װ�ȴ��жϴ��� */
    VOS_UINT32                  ulFrmWaitQueryCnt;              /* ��װ�ȴ���ѯ���� */
    VOS_UINT32                  ulFrmAllocOutputMemFailCnt;     /* ��װ����Ŀ���ڴ�ʧ�ܴ��� */
    VOS_UINT32                  ulFrmAllocFirstMemFailCnt;      /* ��װ�����һ���ڵ�Ŀ���ڴ�ʧ�ܴ��� */
    VOS_UINT32                  ulFrmOutputLinkFullCnt;         /* ��װ������������� */
    VOS_UINT32                  ulFrmInputDiscardCnt;           /* ��װ�������ݰ����� */

    VOS_UINT32                  ulDefMaxInputCntOnce;           /* ���װһ������������ݸ��� */
    VOS_UINT32                  ulDefMaxInputSizeOnce;          /* ���װһ��������������ܳ��� */
    VOS_UINT32                  ulDefMaxValidCntOnce;           /* ���װһ����������Ч֡���� */
    VOS_UINT32                  ulDefMaxQueryCnt;               /* ���װ��ѯ������ */

    VOS_UINT32                  ulFrmMaxInputCntOnce;           /* ��װһ������������ݸ��� */
    VOS_UINT32                  ulFrmMaxInputSizeOnce;          /* ��װһ��������������ܳ��� */
    VOS_UINT32                  ulFrmMaxOutputCntOnce;          /* ��װһ��������ʹ�ýڵ������� */
    VOS_UINT32                  ulFrmMaxOutputSizeOnce;         /* ��װһ��������ʹ�ýڵ��ܳ��� */
    VOS_UINT32                  ulFrmMaxQueryCnt;               /* ��װ��ѯ������ */

    VOS_UINT32                  ulMaxCntOnce;                   /* PPPһ����ദ��Ľ����� */
    VOS_UINT32                  ulHdlcHardProcCnt;              /* PPPһ����ദ��Ľ����� */

    VOS_UINT32                  ulDefIsrCnt;                    /* ���װ�жϷ��������ô��� */
    VOS_UINT32                  ulFrmIsrCnt;                    /* ��װ�жϷ��������ô��� */
    VOS_UINT32                  ulContinueCnt;                  /* �����е�������Ҫ�ֶ�δ���Ĵ��� */
    VOS_UINT16                  usDefExpInfo;                   /* ���װ�쳣��Ϣ */
    VOS_UINT16                  usFrmExpInfo;                   /* ��װ�쳣��Ϣ */
    VOS_UINT32                  ulForbidHdlcBugNoCpy;           /* ���HDLC BUG,���������� */
    VOS_UINT32                  ulForbidHdlcBugCpy;             /* ���HDLC BUG,��Ҫ�������� */
} PPP_HDLC_HARD_DATA_PROC_STAT_ST;

/* HDLC�ؼ��Ĵ�����ά�ɲ���Ϣ����ṹ */
typedef struct
{
    VOS_UINT32                          ulHdlcFrmRawInt;        /* ��װԭʼ�жϼĴ���ֵ */
    VOS_UINT32                          ulHdlcFrmStatus;        /* ��װ״̬�Ĵ���ֵ */
    VOS_UINT32                          ulHdlcDefRawInt;        /* ���װԭʼ�жϼĴ���ֵ */
    VOS_UINT32                          ulHdlcDefStatus;        /* ���װ״̬�Ĵ���ֵ */
}HDLC_REG_SAVE_INFO_STRU;

/*****************************************************************************
  6 ȫ�ֱ�������
*****************************************************************************/
extern HDLC_CONFIG_INFO_STRU                          g_stHdlcConfigInfo;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID);

extern VOS_VOID   PPP_HDLC_HARD_SetUp(VOS_UINT16 usPppId);

extern VOS_VOID   PPP_HDLC_HARD_Disable(VOS_VOID);

extern VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID);

extern VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID);

VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID);


#if (VOS_RTOSCK != VOS_OS_VER)
extern PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

extern VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32       ulPri,
    VOS_UINT16      ulProtocol
);

extern VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);


extern VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT_PTR PPP_VIRT_TO_PHY(VOS_UINT_PTR ulVAddr);

extern VOS_UINT32 PPP_HDLC_NODE_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT32 PPP_HDLC_NODE_VIRT_TO_PHY(unsigned int ulVAddr);

#endif

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

#endif /* end of hdlc_hardware.h */

