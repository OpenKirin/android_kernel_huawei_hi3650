


/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "OmHdlcInterface.h"
#include "ombufmngr.h"


/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_SCM_SOFT_DECODE_C
/*lint +e767 */
/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
/* ��������������OM���ݽ��յ��ٽ���Դ���� */
VOS_SPINLOCK             g_stScmSoftDecodeDataRcvSpinLock;

/* HDLC���ƽṹ */
OM_HDLC_STRU             g_stScmHdlcSoftDecodeEntity;

/* SCM���ݽ������ݻ����� */
VOS_CHAR                 g_aucSCMDataRcvBuffer[SCM_DATA_RCV_PKT_SIZE];

/* SCM���ݽ���������ƽṹ */
SCM_DATA_RCV_CTRL_STRU   g_stSCMDataRcvTaskCtrlInfo;

SCM_SOFTDECODE_INFO_STRU   g_stScmSoftDecodeInfo;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/

VOS_UINT32 SCM_SoftDecodeAcpuRcvData(
    OM_HDLC_STRU                       *pstHdlcCtrl,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen);


VOS_UINT32 SCM_SoftDecodeCfgHdlcInit(OM_HDLC_STRU *pstHdlc);

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : SCM_SoftDecodeCfgDataRcv
 ��������  : OM������Ϣ���պ���
 �������  : pucBuffer:��������
             ulLen:���ݳ���
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 SCM_SoftDecodeCfgDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_UINT32                          ulRstl;
    VOS_ULONG                           ulLockLevel;

    VOS_SpinLockIntLock(&g_stScmSoftDecodeDataRcvSpinLock, ulLockLevel);

    ulRstl = SCM_SoftDecodeDataRcv(pucBuffer, ulLen);

    VOS_SpinUnlockIntUnlock(&g_stScmSoftDecodeDataRcvSpinLock, ulLockLevel);

    return ulRstl;
}

/*****************************************************************************
 �� �� ��  : SCM_SoftDecodeDataRcv
 ��������  : SCM��������ݽ��պ���
 �������  : pucBuffer:��������
             ulLen:���ݳ���
             ulTaskId:SCM���������ID
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 SCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen)
{
    VOS_INT32                           sRet;

    diag_PTR(EN_DIAG_PTR_SCM_SOFTDECODE);

    if (ulLen > (VOS_UINT32)OM_RingBufferFreeBytes(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId))
    {
        g_stScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough++;
        diag_PTR(EN_DIAG_PTR_SCM_ERR1);

        return VOS_ERR;
    }

    sRet = OM_RingBufferPut(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId,
                            (VOS_CHAR *)pucBuffer,
                            (VOS_INT)ulLen);

    if (ulLen == (VOS_UINT32)sRet)
    {
        if (VOS_OK == VOS_SmV(g_stSCMDataRcvTaskCtrlInfo.SmID))
        {
            g_stScmSoftDecodeInfo.stPutInfo.ulDataLen += sRet;
            g_stScmSoftDecodeInfo.stPutInfo.ulNum++;

            return VOS_OK;
        }
    }

    g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferPutErr++;
    diag_PTR(EN_DIAG_PTR_SCM_ERR2);

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : SCM_RcvDataDispatch
 ��������  : OM�߼�ͨ���ķַ�
 �������  : ulTaskId:   ����ID
             pstHdlcCtrl:HDLC���ƽṹ
             ucDataType:GU/TL��������
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ  :
   1.��    ��  : 2014��5��24��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID SCM_RcvDataDispatch(
    OM_HDLC_STRU                       *pstHdlcCtrl,
    VOS_UINT8                           ucDataType)
{
    /* TL���� */
    if (SCM_DATA_TYPE_TL == ucDataType)
    {
        if (VOS_NULL_PTR != g_astSCMDecoderCbFunc[SOCP_DECODER_DST_CB_TL_OM])
        {
            diag_PTR(EN_DIAG_PTR_SCM_DISPATCH);

            /* TL����ҪDATATYPE�ֶΣ��ص�ʱɾ�� */
            g_astSCMDecoderCbFunc[SOCP_DECODER_DST_CB_TL_OM](SOCP_DECODER_DST_LOM,
                                                    pstHdlcCtrl->pucDecapBuff + sizeof(SOCP_DATA_TYPE_ENUM_UIN8),
                                                    pstHdlcCtrl->ulInfoLen - sizeof(SOCP_DATA_TYPE_ENUM_UIN8),
                                                    VOS_NULL_PTR,
                                                    VOS_NULL);
        }

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : SCM_SoftDecodeAcpuRcvData
 ��������  : SCM��������ݽ��պ���
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
VOS_UINT32 SCM_SoftDecodeAcpuRcvData(
    OM_HDLC_STRU                       *pstHdlcCtrl,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucGutlType;
    VOS_UINT8                           ucChar;

    ulResult = VOS_ERR;

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(pstHdlcCtrl, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            g_stScmSoftDecodeInfo.stHdlcDecapData.ulDataLen += pstHdlcCtrl->ulInfoLen;
            g_stScmSoftDecodeInfo.stHdlcDecapData.ulNum++;

            ucGutlType = pstHdlcCtrl->pucDecapBuff[0];

            diag_PTR(EN_DIAG_PTR_SCM_RCVDATA_SUCCESS);

            SCM_RcvDataDispatch(pstHdlcCtrl, ucGutlType);
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*����������֡,����HDLC���װ*/
        }
        else
        {
            g_stScmSoftDecodeInfo.ulFrameDecapErr++;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SCM_SoftDecodeCfgHdlcInit
 ��������  : SCM�����HDLC���װ��ʼ������
 �������  : pstHdlc:ָ��HDLC���ƽṹ��ָ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 SCM_SoftDecodeCfgHdlcInit(OM_HDLC_STRU *pstHdlc)
{
    /* ��������HDLC���װ�Ļ��� */
    pstHdlc->pucDecapBuff    = (VOS_UINT8 *)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, STATIC_MEM_PT, SCM_DATA_RCV_PKT_SIZE);

    if (VOS_NULL_PTR == pstHdlc->pucDecapBuff)
    {
        /*lint -e534*/
        vos_printf("SCM_SoftDecodeCfgHdlcInit: Alloc Decapsulate buffer fail!.\n");
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
 �� �� ��  : SCM_SoftDecodeCfgRcvSelfTask
 ��������  : SCM�����OM�������ݽ�������
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
VOS_VOID SCM_SoftDecodeCfgRcvSelfTask(
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
        if (VOS_OK != VOS_SmP(g_stSCMDataRcvTaskCtrlInfo.SmID, 0))
        {
            continue;
        }

        diag_PTR(EN_DIAG_PTR_SCM_SELFTASK);

        lLen = OM_RingBufferNBytes(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId);

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

                sRet = OM_RingBufferGet(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stSCMDataRcvTaskCtrlInfo.pucBuffer,
                                        SCM_DATA_RCV_PKT_SIZE);
            }
            else
            {
                lReadLen = lRemainlen;

                sRet = OM_RingBufferGet(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId,
                                        g_stSCMDataRcvTaskCtrlInfo.pucBuffer,
                                        lRemainlen);
            }

            if (sRet != lReadLen)
            {
                VOS_SpinLockIntLock(&g_stScmSoftDecodeDataRcvSpinLock, ulLockLevel);

                OM_RingBufferFlush(g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId);

                VOS_SpinUnlockIntUnlock(&g_stScmSoftDecodeDataRcvSpinLock, ulLockLevel);

                g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush++;
                diag_PTR(EN_DIAG_PTR_SCM_ERR3);

                continue;
            }

            lRemainlen -= lReadLen;

            g_stScmSoftDecodeInfo.stGetInfo.ulDataLen += lReadLen;

            diag_PTR(EN_DIAG_PTR_SCM_RCVDATA);

            /* ����HDLC���װ���� */
            if (VOS_OK != SCM_SoftDecodeAcpuRcvData(&g_stScmHdlcSoftDecodeEntity,
                                                    (VOS_UINT8 *)g_stSCMDataRcvTaskCtrlInfo.pucBuffer,
                                                    (VOS_UINT32)lReadLen))
            {
                /*lint -e534*/
                vos_printf("SCM_SoftDecodeCfgRcvSelfTask: SCM_SoftDecodeAcpuRcvData Fail.\n");
                /*lint +e534*/
            }
        }

    }
}


/*****************************************************************************
 �� �� ��  : SCM_SoftDecodeCfgRcvTaskInit
 ��������  : SCM�����OM�������ݽ��պ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ  :
   1.��    ��  : 2014��5��21��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 SCM_SoftDecodeCfgRcvTaskInit(VOS_VOID)
{
    VOS_UINT32                              ulRslt;

    if (VOS_OK != VOS_SmCCreate("OMCF", 0, VOS_SEMA4_FIFO, &(g_stSCMDataRcvTaskCtrlInfo.SmID)))
    {
        /*lint -e534*/
        vos_printf("SCM_SoftDecodeCfgRcvTaskInit: Error, OMCFG semCCreate Fail.\n");
        /*lint +e534*/

        g_stScmSoftDecodeInfo.stRbInfo.ulSemCreatErr++;

        return VOS_ERR;
    }

    /* ע��OM�������ݽ����Դ������� */
    ulRslt = VOS_RegisterSelfTaskPrio(MSP_FID_DIAG_ACPU,
                                      (VOS_TASK_ENTRY_TYPE)SCM_SoftDecodeCfgRcvSelfTask,
                                      SCM_DATA_RCV_SELFTASK_PRIO,
                                      8096);
    if ( VOS_NULL_BYTE == ulRslt )
    {
        vos_printf("SCM_SoftDecodeCfgRcvTaskInit: VOS_RegisterSelfTaskPrio Fail.\n");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&g_stScmSoftDecodeInfo, 0, sizeof(g_stScmSoftDecodeInfo));
    /*lint +e534*/

    if (VOS_OK != SCM_SoftDecodeCfgHdlcInit(&g_stScmHdlcSoftDecodeEntity))
    {
        /*lint -e534*/
        vos_printf("SCM_SoftDecodeCfgRcvTaskInit: Error, HDLC Init Fail.\n");
        /*lint +e534*/

        g_stScmSoftDecodeInfo.ulHdlcInitErr++;

        return VOS_ERR;
    }

    g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId = OM_RingBufferCreate(SCM_DATA_RCV_BUFFER_SIZE);

    if (VOS_NULL_PTR == g_stSCMDataRcvTaskCtrlInfo.rngOmRbufId)
    {
        /*lint -e534*/
        vos_printf("SCM_SoftDecodeCfgRcvTaskInit: Error, Creat OMCFG ringBuffer Fail.\n");
        /*lint +e534*/

        g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr++;

        /*lint -e534*/
        VOS_MemFree(MSP_PID_DIAG_APP_AGENT, g_stScmHdlcSoftDecodeEntity.pucDecapBuff);
        /*lint +e534*/

        return VOS_ERR;
    }

    g_stSCMDataRcvTaskCtrlInfo.pucBuffer = &g_aucSCMDataRcvBuffer[0];

    VOS_SpinLockInit(&g_stScmSoftDecodeDataRcvSpinLock);

    return VOS_OK;
}

VOS_VOID SCM_SoftDecodeInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nSCM_SoftDecodeInfoShow:\r\n");

    vos_printf("\r\nSem Creat Error %d:\r\n",                   g_stScmSoftDecodeInfo.stRbInfo.ulSemCreatErr);
    vos_printf("\r\nSem Give Error %d:\r\n",                    g_stScmSoftDecodeInfo.stRbInfo.ulSemGiveErr);
    vos_printf("\r\nRing Buffer Creat Error %d:\r\n",           g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferCreatErr);
    vos_printf("\r\nTask Id Error %d:\r\n",                     g_stScmSoftDecodeInfo.stRbInfo.ulTaskIdErr);
    vos_printf("\r\nRing Buffer not Enough %d:\r\n",            g_stScmSoftDecodeInfo.stRbInfo.ulBufferNotEnough);
    vos_printf("\r\nRing Buffer Flush %d:\r\n",                 g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferFlush);
    vos_printf("\r\nRing Buffer Put Error %d:\r\n",             g_stScmSoftDecodeInfo.stRbInfo.ulRingBufferPutErr);

    vos_printf("\r\nRing Buffer Put Success Times %d:\r\n",     g_stScmSoftDecodeInfo.stPutInfo.ulNum);
    vos_printf("\r\nRing Buffer Put Success Bytes %d:\r\n",     g_stScmSoftDecodeInfo.stPutInfo.ulDataLen);

    vos_printf("\r\nRing Buffer Get Success Times %d:\r\n",     g_stScmSoftDecodeInfo.stGetInfo.ulNum);
    vos_printf("\r\nRing Buffer Get Success Bytes %d:\r\n",     g_stScmSoftDecodeInfo.stGetInfo.ulDataLen);

    vos_printf("\r\nHDLC Decode Success Times %d:\r\n",         g_stScmSoftDecodeInfo.stHdlcDecapData.ulNum);
    vos_printf("\r\nHDLC Decode Success Bytes %d:\r\n",         g_stScmSoftDecodeInfo.stHdlcDecapData.ulDataLen);

    vos_printf("\r\nHDLC Decode Error Times %d:\r\n",           g_stScmSoftDecodeInfo.ulFrameDecapErr);

    vos_printf("\r\nHDLC Init Error Times %d:\r\n",             g_stScmSoftDecodeInfo.ulHdlcInitErr);

    vos_printf("\r\nHDLC Decode Data Type Error Times %d:\r\n", g_stScmSoftDecodeInfo.ulDataTypeErr);

    vos_printf("\r\nCPM Reg Logic Rcv Func Success Times %d:\r\n", g_stScmSoftDecodeInfo.ulCpmRegLogicRcvSuc);
    /*lint +e534*/
}






