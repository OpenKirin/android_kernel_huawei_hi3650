

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : SCMSoftDecode.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����

***************************************************************************** */

/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "PamOamSpecTaskDef.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "ombufmngr.h"
#include "OmHdlcInterface.h"



/* lint -e767  */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_SCM_SOFT_DECODE_C
/* lint +e767  */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
/* ��������������CBT���ݽ��յ��ٽ���Դ���� */
VOS_SPINLOCK             g_stCbtScmDataRcvSpinLock;

/* HDLC���ƽṹ */
OM_HDLC_STRU             g_stCbtScmHdlcSoftDecodeEntity;

/* SCM���ݽ������ݻ����� */
VOS_CHAR                 g_aucCbtScmDataRcvBuffer[SCM_DATA_RCV_PKT_SIZE];

/* SCM���ݽ���������ƽṹ */
SCM_DATA_RCV_CTRL_STRU   g_stCbtScmDataRcvTaskCtrlInfo;

SCM_SOFTDECODE_INFO_STRU   g_stCbtScmSoftDecodeInfo;


/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/
extern SCM_SOFTDECODE_INFO_STRU   g_stScmSoftDecodeInfo;

extern VOS_UINT32 CBT_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulSize);

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeDataRcvProc
 ��������  : SCM��������ݽ��պ���
 �������  : pucBuffer:��������
             ulLen:���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeDataRcvProc(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_INT32                           sRet;

    if (ulLen > (VOS_UINT32)OM_RingBufferFreeBytes(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId))
    {
        g_stCbtScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough++;

        return VOS_ERR;
    }

    sRet = OM_RingBufferPut(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                            (VOS_CHAR *)pucBuffer,
                            (VOS_INT)ulLen);



    if (ulLen == (VOS_UINT32)sRet)
    {
        if (VOS_OK == VOS_SmV(g_stCbtScmDataRcvTaskCtrlInfo.SmID))
        {
            g_stCbtScmSoftDecodeInfo.stPutInfo.ulDataLen += sRet;
            g_stCbtScmSoftDecodeInfo.stPutInfo.ulNum++;

            return VOS_OK;
        }
    }

    return VOS_ERR;

}

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeDataRcv
 ��������  : GU CBT���ݽ��պ���
 �������  : pucBuffer:��������
             ulLen:���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_UINT32                          ulRstl;
    VOS_ULONG                           ulLockLevel;

    VOS_SpinLockIntLock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

    ulRstl = CBTSCM_SoftDecodeDataRcvProc(pucBuffer, ulLen);

    VOS_SpinUnlockIntUnlock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

    return ulRstl;
}

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeAcpuRcvData
 ��������  : SCM�����CBT���ݽ��պ���
 �������  : pstHdlcCtrl: HDLC���ƽṹ
             pucData:   ��Ҫ���͵���������
             ulLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeAcpuRcvData(
    OM_HDLC_STRU                       *pstHdlcCtrl,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChar;

    ulResult = VOS_ERR;

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(pstHdlcCtrl, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulDataLen += pstHdlcCtrl->ulInfoLen;
            g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulNum++;

            /* GU CBT���ݲ���ҪDATATYPE�ֶΣ�ɾ�� */
            if (VOS_OK != CBT_AcpuRcvData(pstHdlcCtrl->pucDecapBuff + 1,
                            pstHdlcCtrl->ulInfoLen - 1))
            {
            }
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*����������֡,����HDLC���װ*/
        }
        else
        {
            g_stCbtScmSoftDecodeInfo.ulFrameDecapErr++;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeHdlcInit
 ��������  : CBT����SCM�����HDLC���װ��ʼ������
 �������  : pstHdlc:ָ��HDLC���ƽṹ��ָ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeHdlcInit(OM_HDLC_STRU *pstHdlc)
{
    /* ��������HDLC���װ�Ļ��� */
    pstHdlc->pucDecapBuff    = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_CBT, STATIC_MEM_PT, SCM_DATA_RCV_PKT_SIZE);

    if (VOS_NULL_PTR == pstHdlc->pucDecapBuff)
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeHdlcInit: Alloc Decapsulate buffer fail!");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* HDLC���װ���泤�ȸ�ֵ */
    pstHdlc->ulDecapBuffSize = SCM_DATA_RCV_PKT_SIZE;

    /* ��ʼ��HDLC���װ���������� */
    Om_HdlcInit(pstHdlc);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeReqRcvSelfTask
 ��������  : SCM�����CBT���ݽ�������
 �������  : ulPara1:����1
             ulPara2:����2
             ulPara3:����3
             ulPara4:����4
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID CBTSCM_SoftDecodeReqRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4)
{
    VOS_INT32                           sRet;
    VOS_INT32                           lLen;
    VOS_INT32                           lRemainlen;
    VOS_INT32                           lReadLen;
    VOS_UINT32                          ulPktNum;
    VOS_UINT32                          i;
    VOS_ULONG                           ulLockLevel;

    ulPara1 = ulPara1;
    ulPara2 = ulPara2;
    ulPara3 = ulPara3;
    ulPara4 = ulPara4;

    for (;;)
    {
        if (VOS_OK != VOS_SmP(g_stCbtScmDataRcvTaskCtrlInfo.SmID, 0))
        {
            continue;
        }

        lLen = OM_RingBufferNBytes(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId);

        if (lLen <= 0)
        {
            continue;
        }

        ulPktNum = (VOS_UINT32)((lLen + SCM_DATA_RCV_PKT_SIZE - 1) / SCM_DATA_RCV_PKT_SIZE);

        lRemainlen = lLen;

        for (i = 0; i < ulPktNum; i++)
        {
            if (SCM_DATA_RCV_PKT_SIZE < lRemainlen)
            {
                lReadLen = SCM_DATA_RCV_PKT_SIZE;

                sRet = OM_RingBufferGet(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                        SCM_DATA_RCV_PKT_SIZE);
            }
            else
            {
                lReadLen = lRemainlen;

                sRet = OM_RingBufferGet(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                        lRemainlen);
            }

            if (sRet != lReadLen)
            {
                VOS_SpinLockIntLock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

                OM_RingBufferFlush(g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId);

                VOS_SpinUnlockIntUnlock(&g_stCbtScmDataRcvSpinLock, ulLockLevel);

                g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush++;

                continue;
            }

            lRemainlen -= lReadLen;

            /* ����HDLC���װ���� */
            if (VOS_OK != CBTSCM_SoftDecodeAcpuRcvData(&g_stCbtScmHdlcSoftDecodeEntity,
                                                        (VOS_UINT8 *)g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer,
                                                        (VOS_UINT32)lReadLen))
            {
                /*lint -e534*/
                vos_printf("CBTSCM_SoftDecodeReqRcvSelfTask: CBTSCM_SoftDecodeAcpuRcvData Fail");
                /*lint +e534*/

                g_stCbtScmSoftDecodeInfo.stGetInfo.ulDataLen += lReadLen;
            }

        }

    }
}

/*****************************************************************************
 �� �� ��  : CBTSCM_SoftDecodeReqRcvTaskInit
 ��������  : SCM�����CBT���ݽ��պ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 CBTSCM_SoftDecodeReqRcvTaskInit(VOS_VOID)
{
    VOS_UINT32                              ulRslt;

    /* ע��CBT���ݽ����Դ������� */
    ulRslt = VOS_RegisterSelfTaskPrio(ACPU_FID_CBT,
                                      (VOS_TASK_ENTRY_TYPE)CBTSCM_SoftDecodeReqRcvSelfTask,
                                      SCM_DATA_RCV_SELFTASK_PRIO,
                                      SCM_CBT_REQ_TASK_STACK_SIZE);
    if ( VOS_NULL_BYTE == ulRslt )
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&g_stCbtScmSoftDecodeInfo, 0, sizeof(g_stCbtScmSoftDecodeInfo));
    /*lint +e534*/

    if (VOS_OK != VOS_SmCCreate("CBT", 0, VOS_SEMA4_FIFO, &(g_stCbtScmDataRcvTaskCtrlInfo.SmID)))
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, CBT semCCreate Fail");
        /*lint +e534*/

        g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemCreatErr++;

        return VOS_ERR;
    }

    if (VOS_OK != CBTSCM_SoftDecodeHdlcInit(&g_stCbtScmHdlcSoftDecodeEntity))
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, HDLC Init Fail");
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId = OM_RingBufferCreate(SCM_DATA_RCV_BUFFER_SIZE);

    if (VOS_NULL_PTR == g_stCbtScmDataRcvTaskCtrlInfo.rngOmRbufId)
    {
        /*lint -e534*/
        vos_printf("CBTSCM_SoftDecodeReqRcvTaskInit: Error, Creat CBT ringBuffer Fail");
        /*lint +e534*/

        g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr++;

        /*lint -e534*/
        VOS_MemFree(ACPU_PID_CBT, g_stCbtScmHdlcSoftDecodeEntity.pucDecapBuff);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stCbtScmDataRcvTaskCtrlInfo.pucBuffer = &g_aucCbtScmDataRcvBuffer[0];

    VOS_SpinLockInit(&g_stCbtScmDataRcvSpinLock);

    return VOS_OK;
}

VOS_VOID CBTSCM_SoftDecodeInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nSCM_SoftDecodeInfoShow:\r\n");

    vos_printf("\r\nSem Creat Error %d:\r\n",                   g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemCreatErr);
    vos_printf("\r\nSem Give Error %d:\r\n",                    g_stCbtScmSoftDecodeInfo.stRbInfo.ulSemGiveErr);
    vos_printf("\r\nRing Buffer Creat Error %d:\r\n",           g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr);
    vos_printf("\r\nTask Id Error %d:\r\n",                     g_stCbtScmSoftDecodeInfo.stRbInfo.ulTaskIdErr);
    vos_printf("\r\nRing Buffer not Enough %d:\r\n",            g_stCbtScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough);
    vos_printf("\r\nRing Buffer Flush %d:\r\n",                 g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush);
    vos_printf("\r\nRing Buffer Put Error %d:\r\n",             g_stCbtScmSoftDecodeInfo.stRbInfo.ulRingBufferPutErr);

    vos_printf("\r\nRing Buffer Put Success Times %d:\r\n",     g_stCbtScmSoftDecodeInfo.stPutInfo.ulNum);
    vos_printf("\r\nRing Buffer Put Success Bytes %d:\r\n",     g_stCbtScmSoftDecodeInfo.stPutInfo.ulDataLen);

    vos_printf("\r\nRing Buffer Get Success Times %d:\r\n",     g_stCbtScmSoftDecodeInfo.stGetInfo.ulNum);
    vos_printf("\r\nRing Buffer Get Success Bytes %d:\r\n",     g_stCbtScmSoftDecodeInfo.stGetInfo.ulDataLen);

    vos_printf("\r\nHDLC Decode Success Times %d:\r\n",         g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulNum);
    vos_printf("\r\nHDLC Decode Success Bytes %d:\r\n",         g_stCbtScmSoftDecodeInfo.stHdlcDecapData.ulDataLen);

    vos_printf("\r\nHDLC Decode Error Times %d:\r\n",           g_stCbtScmSoftDecodeInfo.ulFrameDecapErr);

    vos_printf("\r\nHDLC Init Error Times %d:\r\n",             g_stCbtScmSoftDecodeInfo.ulHdlcInitErr);

    vos_printf("\r\nHDLC Decode Data Type Error Times %d:\r\n", g_stCbtScmSoftDecodeInfo.ulDataTypeErr);
    /*lint +e534*/
}





