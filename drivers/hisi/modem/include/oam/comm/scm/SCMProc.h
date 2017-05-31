/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _SCM_PROC_H_
#define _SCM_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "SOCPInterface.h"
#include "vos.h"
#include "BSP_SOCP_DRV.h"
#include "msp_debug.h"
#include "mdrv.h"


#if(VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**************************************************************************
  2 �궨��
**************************************************************************/
/* ����꿪�� */

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define SCM_ACORE
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define SCM_CCORE
#endif


/* ͨ���������ݺ����ݳ��� */
typedef VOS_VOID (*SCM_CODERDESTFUCN)(SOCP_CODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulSize);

/* ͨ���������ݡ����ݳ��ȡ��ؾ����ݡ��ؾ����ݳ��� */
typedef VOS_VOID (*SCM_DECODERDESTFUCN)(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize);


#if (OSA_CPU_CCPU == VOS_OSA_CPU)

#define SCM_CODER_SRC_NUM           (3)       /* ����Դͨ������ */

#endif  /* (OSA_CPU_CCPU == VOS_OSA_CPU) */

#if (OSA_CPU_ACPU == VOS_OSA_CPU)

#define SCM_CODER_SRC_NUM           (2)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (2)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */

#endif  /* (OSA_CPU_ACPU == VOS_OSA_CPU) */


/********************* DIAGͨ���ڴ����� **************************
* CCORE CNF BUFFER: 64K
* CCORE IND BUFFER: 1.5M
* ACORE CNF BUFFER: 64K
* ACORE IND BUFFER: 1M
****************************************************************/
#define DIAG_CODER_SRC_CNF_BUF_C_SIZE               (1024*64)
#define DIAG_CODER_SRC_IND_BUF_C_SIZE               (1536*1024)
#define DIAG_CODER_SRC_CNF_BUF_A_SIZE               (1024*64)
#define DIAG_CODER_SRC_IND_BUF_A_SIZE               (1024*1024)

#if (VOS_LINUX== VOS_OS_VER)

#define SCM_CODER_SRC_CNF_BUFFER_SIZE               (DIAG_CODER_SRC_CNF_BUF_A_SIZE)
#define SCM_CODER_SRC_IND_BUFFER_SIZE               (DIAG_CODER_SRC_IND_BUF_A_SIZE)

#define SCM_CODER_SRC_LOM_CNF                       (SOCP_CODER_SRC_LOM_CNF1)
#define SCM_CODER_SRC_LOM_IND                       (SOCP_CODER_SRC_LOM_IND1)

#else

#define SCM_CODER_SRC_CNF_BUFFER_SIZE               (DIAG_CODER_SRC_CNF_BUF_C_SIZE)
#define SCM_CODER_SRC_IND_BUFFER_SIZE               (DIAG_CODER_SRC_IND_BUF_C_SIZE)

#define SCM_CODER_SRC_LOM_CNF                       (SOCP_CODER_SRC_LOM_CNF2)
#define SCM_CODER_SRC_LOM_IND                       (SOCP_CODER_SRC_LOM_IND2)

#endif


#define SCM_CODER_SRC_MAX_LEN       (4*1024)        /* ����ͨ����������ݳ���  */

#define SCM_DECODER_SRC_SIZE        (8*1024)        /* ����Դͨ���ռ��С */
#define SCM_DECODER_DST_SIZE        (8*1024)        /* ����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_IND_SIZE      (1*1024*1024)   /* �����ϱ�����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_CNF_SIZE      (64*1024)       /* ����ظ�����Ŀ��ͨ���ռ��С */

#define SCM_CODE_SRC_BD_NUM         (4*1024)        /* ��ʽͨ��BD�ĸ��� */
#define SCM_CODE_SRC_RD_NUM         (4*1024)        /* ��ʽͨ��RD�ĸ��� */

#define SCM_CODER_SRC_BDSIZE        (sizeof(SOCP_BD_DATA_STRU)*SCM_CODE_SRC_BD_NUM)   /* ��ʽͨ����BD�ռ� */
#define SCM_CODER_SRC_RDSIZE        (sizeof(SOCP_RD_DATA_STRU)*SCM_CODE_SRC_RD_NUM)   /* ��ʽͨ����RD�ռ� */

#define SCM_CODER_DST_THRESHOLD     (4)             /* ����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_GTHRESHOLD    ((4*1024) + 8 + 128)    /* ����Դͨ���ٲ���ֵ + DMAһ����С�����ֽ� */

#define SCM_DECDOER_DST_THRESHOLD   (1)             /* ����Ŀ��ͨ����ֵ, ��λHDLC֡ */

#define SCM_CODER_SRC_RD_THRESHOLD  (0)             /* ����Դͨ��RD��ֵ */

#define SCM_DATA_SAVE_TAG           (0x5A)          /* SOCP�������ݵļ����� */

#define SCM_CODER_DST_CNF_CHANNEL   (0)             /* CNF����Ŀ��ͨ�� */
#define SCM_CODER_DST_IND_CHANNEL   (1)             /* IND����Ŀ��ͨ�� */


#define SCM_HISI_HEADER_MAGIC               (0x48495349) /*HISI*/
#define SCM_HISI_HEADER_LENGTH              (sizeof(SCM_CODER_SRC_PACKET_HEADER_STRU))

/*4�ֽڶ���*/
#define ALIGN_DDR_WITH_4BYTE(len)       (((len) + 3)&(~3))
/*8�ֽڶ���*/
#define ALIGN_DDR_WITH_8BYTE(len)       (((len) + 7)&(~7))

/**************************************************************************
  3 ö�ٶ���
**************************************************************************/
enum  SCM_CHANNEL_INIT_ENUM
{
    SCM_CHANNEL_UNINIT = 0,             /* δ��ʼ�� */
    SCM_CHANNEL_INIT_SUCC,              /* ��ʼ���ɹ� */
    SCM_CHANNEL_MEM_FAIL,               /* ��ʼ�������ڴ���� */
    SCM_CHANNEL_CFG_FAIL,               /* ��ʼ��ͨ������ */
    SCM_CHANNEL_START_FAIL,             /* ͨ���������� */
    SCM_CHANNEL_INIT_BUTT
};
typedef VOS_UINT32 SCM_CHANNEL_INIT_ENUM_U32;

enum SOCP_SOFT_DECODE_CB_ENUM
{
    SOCP_DECODER_DST_CB_TL_OM,
    SOCP_DECODER_DST_CB_GU_OM,
    SOCP_DECODER_DST_CB_GU_CBT,
    SOCP_DECODER_DST_CB_BUTT
};

typedef VOS_UINT32 SOCP_SOFT_DECODE_CB_ENUM_U32;

enum SCM_CHANNEL_ENUM
{
    SCM_LTE_CHANNEL,    /*LTEͨ��*/
    SCM_GU_CHANNEL,     /*GUͨ��*/
    SCM_CHANNEL_BUTT
};

typedef VOS_UINT32 SCM_CHANNEL_ENUM_U32;

enum
{
	SCM_CODER_TYPE_CNF = 0,     /*CNFͨ��*/
	SCM_CODER_TYPE_IND,         /*INDͨ��*/
	SCM_CODER_TYPE_BUTT
};

typedef VOS_UINT32 SCM_CODER_SRC_TYPE_ENUM_U32;

/**************************************************************************
  4 �ṹ�嶨��
**************************************************************************/
typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ��ʼ��״̬ */
    VOS_UINT32                  ulChannelID;    /* ͨ��ID */
}SCM_CHANNEL_CFG_HEAD;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32       enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_SRC_ENUM_U32         enChannelID;    /* ����Դͨ��ID���̶����� */
    SOCP_CODER_DST_ENUM_U32         enDstCHID;      /* ����Ŀ��ͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32       enDataType;     /* ������Դ���� */
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32  enCHMode;       /* ͨ������ */
    SOCP_CHAN_PRIORITY_ENUM_UIN32   enCHLevel;      /* ͨ�����ȼ� */
    VOS_UINT32                      ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                      ulRDBufLen;     /* ����Դͨ��RD���ݿռ��С */
    VOS_UINT8                       *pucSrcBuf;     /* ����Դͨ�����ݿռ��ڴ�ָ�� */
    VOS_UINT8                       *pucSrcPHY;
    VOS_UINT8                       *pucRDBuf;      /* ����Դͨ��RD���ݿռ��ڴ�ָ�� */
    VOS_UINT8                       *pucRDPHY;
}SCM_CODER_SRC_CFG_STRU;

typedef SOCP_BUFFER_RW_STRU SCM_CODER_SRC_BUFFER;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_DST_ENUM_U32     enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ��ͨ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ��ͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_CODERDESTFUCN           pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_CODER_DEST_CFG_STRU;

typedef struct
{
    VOS_UINT32                  ulHisiMagic;   /*"HISI"*/
    VOS_UINT32                  ulDataLen;      /*���ݳ���*/
    VOS_UINT8                   pucData[0];
}SCM_CODER_SRC_PACKET_HEADER_STRU;


typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_SRC_ENUM_U32   enChannelID;    /* ����Դͨ��ID���̶����� */
    VOS_UINT32                  ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                  ulRfu;
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
}SCM_DECODER_SRC_CFG_STRU;

typedef struct
{
    VOS_UINT32                  ulHisiMagic;   /*"HISI"*/
    VOS_UINT32                  ulDataLen;      /*���ݳ���*/
    VOS_UINT8                   pucData[0];
}SCM_DECODER_DEST_PACKET_HEADER_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_DST_ENUM_U32   enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    SOCP_DECODER_SRC_ENUM_U32   enSrcCHID;      /* ����Դͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32   enDataType;     /* ����������Դ���� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_DECODERDESTFUCN         pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_DECODER_DEST_CFG_STRU;


typedef struct
{
    VOS_UINT32                  aulBDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���Դͨ��BDʹ�����ֵ */
    VOS_UINT32                  aulRDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���ԴRDʹ�����ֵ */
    INNER_LOG_DATA_STRU         stCoderSrcLog;                      /* ��¼�ϲ���õķ��ͽӿ�log */
    INNER_LOG_DATA_STRU         stCoderSrcRDLog;                    /* ��¼�ϲ���õ��ͷ�RD�ӿ�log */
    INNER_LOG_DATA_STRU         stCoderSrcErr;                      /* ��¼����Դͨ���ص�����Log */
#ifdef SCM_ACORE
    INNER_LOG_DATA_STRU         stCoderDstLog;                      /* ��¼�ص��ϲ�ı���Ŀ��ͨ������Log */
    INNER_LOG_DATA_STRU         stCoderDstErr;                      /* ��¼����Ŀ��ͨ���ص�����Log */
    VOS_UINT32                  ulCoderDstIndLen;                   /* ��¼INDͨ������Ŀ�Ķ��ͳ������ֽ��� */
#endif
}SCM_INFODATA_STRU;

typedef struct{
    VOS_UINT32      ulFillFirstBuffNum;
    VOS_UINT32      ulFillFirstBuffMax;
    VOS_UINT32      ulFillNotEnough;
    VOS_UINT32      ulAfterFillNotEnough;

    VOS_UINT32      ulGetCoderBuffErr;
    VOS_UINT32      ulGetCoherentBuffErr;
    VOS_UINT32      ulGetWriteBufErr;

    VOS_UINT32      ulSendPacketNum;
    VOS_UINT32      ulSendDataLen;
    VOS_UINT32      ulSendFirstNotEnough;
    VOS_UINT32      ulSendAddrErr;
    VOS_UINT32      ulSendWriteDoneErr;
    VOS_UINT32      ulSendHeaderErr;

}SCM_CODER_SRC_DEBUG_STRU;


typedef struct
{
    VOS_VOID        *pHeader;           /* ֮ǰ��ȡ�ı���Դbuffer���׵�ַ(�����ַ) */
    VOS_VOID        *pSrc;              /* ��Ҫ���������ݻ�������ַ */
    VOS_UINT32      uloffset;           /* ��Ҫ��������ƫ�Ƶ�ַ */
    VOS_UINT32      ulLen;              /* ��Ҫ���������ݳ��� */
}SCM_CODER_SRC_MEMCPY_STRU;


/**************************************************************************
  5 Log��������
**************************************************************************/

#define SCM_CODER_SRC_LOG(pucStr, ulP1, ulP2)\
    /*vos_printf("SCM_CODER_SRC_LOG %s, %d, %d", pucStr, ulP1, ulP2)*/

#define SCM_CODER_SRCRD_LOG(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_CODER_SRCRD_LOG %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_CODER_SRCRESET_LOG(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_CODER_SRCRESET_LOG %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_CODER_SRC_ERR(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_CODER_SRC_ERR %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_CODER_DST_ERR %s, %d, %d", pucStr, ulP1, ulP2)
#ifdef SCM_ACORE
#define SCM_DECODER_SRC_LOG(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_DECODER_SRC_LOG %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_CODER_DST_LOG(pucStr, ulP1, ulP2)\
    /*vos_printf("SCM_CODER_DST_LOG %s, %d, %d", pucStr, ulP1, ulP2)*/

#define SCM_DECODER_DST_LOG(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_DECODER_DST_LOG %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_CODER_DST_ERR %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_DECODER_DST_ERR(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_DECODER_DST_ERR %s, %d, %d", pucStr, ulP1, ulP2)

#define SCM_DECODER_SRC_ERR(pucStr, ulP1, ulP2)\
    (VOS_VOID)vos_printf("SCM_DECODER_SRC_ERR %s, %d, %d", pucStr, ulP1, ulP2)

#endif



#define SCM_SPINLOCK_INTLOCK(ulLockLevel)               VOS_SpinLockIntLock(&g_stScmGetCoderSrcBuffSpinLock, ulLockLevel)
#define SCM_SPINUNLOCK_INTUNLOCK(ulLockLevel)           VOS_SpinUnlockIntUnlock(&g_stScmGetCoderSrcBuffSpinLock, ulLockLevel)
#define SCM_MAX(A,B)    (A>B?A:B)
#define SCM_MIN(A,B)    (A<B?A:B)

extern VOS_SPINLOCK                 g_stScmGetCoderSrcBuffSpinLock;
extern SCM_INFODATA_STRU            g_stSCMInfoData;    /* ���ڱ���log��Ϣ */
extern SCM_DECODERDESTFUCN          g_astSCMDecoderCbFunc[SOCP_DECODER_DST_CB_BUTT];

/**************************************************************************
  6 ��������
**************************************************************************/

extern VOS_UINT32  SCM_FindChannelCfg(VOS_UINT32 ulChannelID, VOS_UINT32 ulChMax, SCM_CHANNEL_CFG_HEAD *pstCfg, VOS_UINT32 ulStruLen, VOS_UINT32 *pulNum);

extern VOS_UINT32 SCM_CoderSrcChannelCfg(SCM_CODER_SRC_CFG_STRU *pstCfg);

extern VOS_UINT32 SCM_CoderSrcChannelInit(VOS_VOID);

extern VOS_UINT32 SCM_RlsSrcRDAll(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT_PTR *pDataPhyAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_RlsSrcRDFirst(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT_PTR *pDataPhyAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_GetBDFreeNum(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT32 *pulBDNum);

extern VOS_UINT32 SCM_GetCoderChnSrcBuff(SOCP_CODER_SRC_ENUM_U32 enChanlID,
                                            VOS_UINT32 ulDataLen,
                                            SCM_CODER_SRC_PACKET_HEADER_STRU** pstCoderHeader,
                                            SOCP_BUFFER_RW_STRU *pstSocpBuf);

extern VOS_UINT32 SCM_SendCoderSrc(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);

extern VOS_UINT32 SCM_SendHardDecoderSrc(SOCP_DECODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendDataVirt, VOS_UINT32 ulSendLen);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 SCM_RlsDestBuf(VOS_UINT32 ulChanlID, VOS_UINT32 ulReadSize);

extern VOS_UINT32 SCM_RegCoderDestProc(SOCP_CODER_DST_ENUM_U32 enChanlID,SCM_CODERDESTFUCN func);

extern VOS_UINT32 SCM_RegDecoderDestProc(SOCP_DECODER_DST_ENUM_U32 enChanlID,SCM_DECODERDESTFUCN func);

extern VOS_UINT32 COMM_Init(VOS_VOID);

#endif
extern VOS_VOID SCM_FlushCpuCache( VOS_VOID *pAddress, VOS_INT lSize );

extern VOS_VOID SCM_InvalidCpuCache( VOS_VOID *pAddress, VOS_INT lSize );

extern VOS_VOID SCM_CoderSrcMemcpy(SOCP_CODER_SRC_ENUM_U32 enChanlID, SCM_CODER_SRC_MEMCPY_STRU *pInfo, SOCP_BUFFER_RW_STRU *pstSocpBuf);

extern VOS_UINT32 SCM_CreateSrcBuffer(VOS_UINT8 **pBufVir, VOS_UINT8 **pBufPhy, VOS_UINT32 ulLen);
extern VOS_UINT32 SCM_CoderSrcChanMemInit(VOS_VOID);
extern VOS_UINT32 SCM_ChannelMemInit(VOS_VOID);
extern VOS_VOID SCM_ErrorChInfoSave(cb_buf_t *pstData);
extern VOS_UINT32 SCM_ChannelInit(VOS_VOID);
extern VOS_VOID SCM_ChannelInfoShow(VOS_VOID);
extern VOS_VOID SCM_CoderSrcCHShow(VOS_UINT32 ulCfgNum);
extern VOS_VOID SCM_StopAllSrcChan(VOS_VOID);
extern VOS_VOID SCM_SOCPBDRegShow(VOS_UINT32 ulCfgNum);
extern VOS_VOID SCM_SOCPRDRegShow(VOS_UINT32 ulCfgNum);
extern SCM_INFODATA_STRU* SCM_GetDebugLogInfo(VOS_VOID);
extern VOS_UINT32 SCM_GetDebugLogInfoLen(VOS_VOID);
extern VOS_UINT32 SCM_CoderDstCompressCfg(VOS_BOOL enable);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


