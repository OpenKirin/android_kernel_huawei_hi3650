

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "vos.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

/*lint -e767 -e960*/
#define THIS_FILE_ID                    PS_FILE_ID_DMS_ACM_AT_TX_C
/*lint +e767 +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

DMS_STATIC_BUF_STRU                     stDmsStaticBufInfo ;

VOS_UINT8                              *g_aucStaticBuf = NULL;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : DMS_WriteData
 ��������  : ATд���������
 �������  : ucPortNo: ͨ��ID
             pData: ��������ָ��
             uslength:���ͳ���
 �������  :
 �� �� ֵ  : ERR_MSP_FAILURE/ERR_MSP_SUCCESS
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function

   2.��    ��   : 2015��6��25��
     ��    ��   : l00198894
     �޸�����   : TSTS
*****************************************************************************/
VOS_INT32 DMS_WriteData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT8                          *pucSenBuf = NULL;
    VOS_INT32                           lRet      = VOS_ERROR;

    if ((NULL == pucData) || (0 == usLen))
    {
        return VOS_ERROR;
    }

    DMS_LOG_INFO("DMS_WriteData: PortNo = %d, len = %d, buf = %s\n", enPhyBear, usLen, pucData);

    if ( (DMS_PHY_BEAR_USB_PCUI == enPhyBear)
      || (DMS_PHY_BEAR_USB_CTRL == enPhyBear)
      || (DMS_PHY_BEAR_USB_PCUI2 == enPhyBear) )
    {
        pucSenBuf = Dms_GetStaticBuf(usLen);

        if (NULL == pucSenBuf)
        {
            return VOS_ERROR;
        }

        VOS_MemCpy(pucSenBuf, pucData, usLen);

        lRet = (VOS_INT32)DMS_VcomWriteAsync(enPhyBear, pucSenBuf, usLen);

        if (ERR_MSP_SUCCESS != lRet)
        {
            Dms_FreeStaticBuf(pucSenBuf);
        }

    }
    else if (DMS_PHY_BEAR_USB_NCM == enPhyBear)
    {
        pucSenBuf = Dms_GetStaticBuf(usLen);

        if (NULL == pucSenBuf)
        {
            return VOS_ERROR;
        }

        VOS_MemCpy(pucSenBuf, pucData, usLen);

        lRet = (VOS_INT32)DMS_NcmSendData(pucSenBuf, usLen);

        if (ERR_MSP_SUCCESS != lRet)
        {
            Dms_FreeStaticBuf(pucSenBuf);
        }
    }
    else
    {
        lRet = VOS_ERROR;
    }

    return lRet;
}

/*****************************************************************************
 �� �� ��  : Dms_StaticBufInit
 ��������  : AT���;�̬buf��ʼ��
 �������  :

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID Dms_StaticBufInit(VOS_VOID)
{
    VOS_UINT32 i = 0;
    VOS_UINT8 * pTemp = NULL;

    VOS_UINT32 ulBufSize;

    ulBufSize = (DMS_LOG_STATIC_ONE_BUF_SIZE*DMS_LOG_STATIC_BUF_NUM + 32);
    g_aucStaticBuf = kmalloc(ulBufSize, GFP_KERNEL|__GFP_DMA);

    if(g_aucStaticBuf == VOS_NULL)
    {
        return ;
    }


    /*ȡ32�ֽڶ���ĵ�ַ*/
    pTemp = g_aucStaticBuf + (32 - ((VOS_ULONG )g_aucStaticBuf%32));

    stDmsStaticBufInfo.enBufType      = DMS_BUF_TYP_DYMIC;

    /* ��ʼ��������Ϣ*/
    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        stDmsStaticBufInfo.stBufSta[i].pcuBuf = (VOS_UINT8 *)((VOS_ULONG)i * DMS_LOG_STATIC_ONE_BUF_SIZE + pTemp);
        stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_IDLE;
    }

    return ;

}
/*****************************************************************************
�� �� ��  : Dms_GetStaticBuf
��������  : AT���ͻ�ȡ��̬buf
�������  : ulLen :��Ҫbuf�ĳ���

�������  :
�� �� ֵ  : VOS_NULL/addr
���ú���  :
��������  :
�޸���ʷ  :
 1.��    ��  : 2012��8��27��
   ��    ��  : heliping
   �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT8* Dms_GetStaticBuf(VOS_UINT32 ulLen)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 *buf = NULL;

    /*���ݳ��ȳ�����̬buf���size����̬����buf*/
    if(ulLen >DMS_LOG_STATIC_ONE_BUF_SIZE )
    {

        buf = kmalloc(ulLen, GFP_KERNEL|__GFP_DMA);
        return (VOS_UINT8* )buf;
    }

    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        if (stDmsStaticBufInfo.stBufSta[i].enBusy == STATIC_BUF_STA_IDLE)
        {
            stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_BUSY;

            return  stDmsStaticBufInfo.stBufSta[i].pcuBuf;
        }
    }

    /*���޳����� �����̬buf���꣬���붯̬�ڴ�ʹ��*/
    buf = kmalloc(ulLen, GFP_KERNEL|__GFP_DMA);

    return (VOS_UINT8* )buf;

}

/*****************************************************************************
�� �� ��  : Dms_IsStaticBuf
��������  : �ж��Ƿ��Ǿ�̬��ַ
�������  : buf: buf��ַ

�������  :
�� �� ֵ  : TRUE/FALSE
���ú���  :
��������  :
�޸���ʷ  :
1.��    ��  : 2012��8��27��
  ��    ��  : heliping
  �޸�����  : Creat Function
*****************************************************************************/

 VOS_BOOL Dms_IsStaticBuf(VOS_UINT8 *buf)
 {

    if(( buf >= g_aucStaticBuf )
        &&(buf < g_aucStaticBuf +DMS_LOG_STATIC_ONE_BUF_SIZE * DMS_LOG_STATIC_BUF_NUM  +32))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

/*****************************************************************************
 �� �� ��  : Dms_FreeStaticBuf
 ��������  : �ͷž�̬�ռ�
 �������  : buf: ���ͷŵ�buf��ַ

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID Dms_FreeStaticBuf( VOS_UINT8 * buf)
{
    VOS_UINT32 i = 0;

    if (NULL == buf)
    {
        return ;
    }

    /*��̬buf�ͷ�*/
    for (i = 0; i < DMS_LOG_STATIC_BUF_NUM; i++)
    {
        if (stDmsStaticBufInfo.stBufSta[i].pcuBuf == buf)
        {
            stDmsStaticBufInfo.stBufSta[i].enBusy = STATIC_BUF_STA_IDLE;
            return ;
        }
    }

    /*��̬buf�ͷ�*/
    if(i == DMS_LOG_STATIC_BUF_NUM)
    {
        kfree(buf );
    }


    return ;
}
/*****************************************************************************
 �� �� ��  : DMS_VcomWriteAsync
 ��������  : USB�첽д�ӿ�
 �������  : VcomId: ͨ��ID
             pucDataBuf: ����ָ��
             slLen:���ͳ���
 �������  :
 �� �� ֵ  : ERR_MSP_FAILURE/ERR_MSP_SUCCESS
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��  : 2012��8��27��
     ��    ��  : heliping
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 DMS_VcomWriteAsync(
    DMS_PHY_BEAR_ENUM                   enPhyBear,
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulLen
)
{
    DMS_PHY_BEAR_PROPERTY_STRU         *pstPhyBearProp = NULL;
    ACM_WR_ASYNC_INFO                   stAcmInfo = {0};
    UDI_HANDLE                          lHandle = UDI_INVALID_HANDLE;
    VOS_INT32                           lRet = ERR_MSP_SUCCESS;
    struct device                       dev;
    VOS_UINT64                          dma_mask = 0xffffffffULL;

    VOS_MemSet(&dev, 0, (VOS_SIZE_T)sizeof(dev));

    dev.dma_mask = &(dma_mask);

    stAcmInfo.pVirAddr = (VOS_CHAR *)pucDataBuf;

    stAcmInfo.pPhyAddr = (VOS_CHAR *)DMS_CACHE_FLUSH_WITH_DEV(&dev, (VOS_CHAR *)pucDataBuf, ulLen);

    stAcmInfo.u32Size  = ulLen;

    pstPhyBearProp = DMS_GetPhyBearProperty(enPhyBear);

    lHandle = pstPhyBearProp->lPortHandle;
    if (UDI_INVALID_HANDLE == lHandle)
    {
        DMS_LOG_INFO("DMS_VcomWriteAsync[%d]: INVALID HANDLE.\n", enPhyBear);
        return ERR_MSP_FAILURE;
    }

    if (ACM_EVT_DEV_SUSPEND == pstPhyBearProp->ucChanStat)
    {
        DMS_LOG_INFO("DMS_VcomWriteAsync[%d]: DEV SUSPEND.\n", enPhyBear);
        return ERR_MSP_FAILURE;
    }

    DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_BEGIN + (VOS_UINT32)enPhyBear),\
                    ulLen, 0, 0);

    lRet = mdrv_udi_ioctl(lHandle, ACM_IOCTL_WRITE_ASYNC, &stAcmInfo);
    if (ERR_MSP_SUCCESS == lRet)
    {
        DMS_DBG_SDM_FUN((DMS_SDM_MSG_ID_ENUM)(DMS_SDM_VCOM_WRT_SUSS_BEGIN + (VOS_UINT32)enPhyBear),\
                        ulLen, 0, 0);
    }

    return (VOS_UINT32)lRet;
}



