


/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
//#include "AtAppVcomInterface.h"
#include "OmVcomPpm.h"
#include "cpm.h"
#include "dms.h"



/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_VCOM_PPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
/* ���ڼ�¼ VCOM ͨ�����͵�ͳ����Ϣ */
OM_VCOM_DEBUG_INFO                      g_stVComDebugInfo[3];

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : XXXXXXXX
    �޸�����   : V8R1 OM_Optimize��Ŀ����

*****************************************************************************/

/*****************************************************************************
 �� �� ��  : PPM_VComCfgSendData
 ��������  : ��VCOM�˿ڷ�����������
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen: ���ݳ���
 �������  : ��
 �� �� ֵ  : CPM_SEND_ERR/CPM_SEND_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_UINT32 PPM_VComCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendLen += ulDataLen;

    if (VOS_OK != DMS_WriteOmData(DMS_VCOM_OM_CHAN_CTRL, pucVirAddr, ulDataLen))
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrLen += ulDataLen;

        return CPM_SEND_ERR;
    }

    return CPM_SEND_OK;
}
/*****************************************************************************
 �� �� ��  : PPM_VComCfgEvtCB
 ��������  : ����VCOMͨ���򿪹رջص�
 �������  : ulChan :ͨ����
             ulEvent:   �򿪻��߹ر�
 �������  : ��
 �� �� ֵ  : CPM_SEND_ERR/CPM_SEND_OK
 �޸���ʷ  :
   1.��    ��  : 2014��5��26��
     ��    ��  : h59254
     �޸�����  : Creat Function
*****************************************************************************/
VOS_VOID PPM_VComEvtCB(VOS_UINT32 ulChan, VOS_UINT32 ulEvent)
{
    OM_LOGIC_CHANNEL_ENUM_UINT32        enChannel;
    VOS_BOOL                            ulSndMsg;


    if(ulChan == DMS_VCOM_OM_CHAN_CTRL)
    {
        enChannel = OM_LOGIC_CHANNEL_CNF;
    }
    else if(ulChan == DMS_VCOM_OM_CHAN_DATA)
    {
        enChannel = OM_LOGIC_CHANNEL_IND;
    }
    else
    {
        vos_printf("[%s] Error channel NO %d\n",__FUNCTION__,ulChan);
        return;
    }

    /*�򿪲���ֱ�ӷ���*/
    if(ulEvent == DMS_CHAN_EVT_OPEN)
    {
        return;
    }
    else if(ulEvent == DMS_CHAN_EVT_CLOSE)
    {
        ulSndMsg  = VOS_FALSE;

        if((CPM_VCOM_CFG_PORT == CPM_QueryPhyPort(CPM_OM_CFG_COMM)) &&
           (CPM_VCOM_IND_PORT == CPM_QueryPhyPort(CPM_OM_IND_COMM)))
        {
            ulSndMsg = TRUE;
        }
        if(ulSndMsg == TRUE)
        {
            PPM_DisconnectAllPort(enChannel);
        }
    }
    else
    {
        vos_printf("[%s] Error Event State %d\n",__FUNCTION__,ulEvent);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : GU_OamVComCfgReadData
 ��������  : NAS���յ����ݵ���OM �ӿڷ���
 �������  :  ucDevIndex: ����˿�
              pData    : �յ�����
              uslength : ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_VComCfgReadData(VOS_UINT32 ulDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength)
{
    if (ulDevIndex != DMS_VCOM_OM_CHAN_CTRL)
    {
        vos_printf("\r\n PPM_VComCfgReadData:PhyPort port is error: %d\n", ulDevIndex);

        return VOS_ERR;
    }

    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvLen += uslength;

    if ((VOS_NULL_PTR == pData) || (0 == uslength))
    {
        vos_printf("\r\n PPM_VComCfgReadData:Send data is NULL\n");

        return VOS_ERR;
    }


    if(VOS_OK != CPM_ComRcv(CPM_VCOM_CFG_PORT, pData, uslength))
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrLen += uslength;

        vos_printf("\r\n Info: PPM_VComCfgReadData:Call CPM_ComRcv is fail, PhyPort is CPM_VCOM_IND_PORT \n");
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPM_VComIndSendData
 ��������  : Vcom�ڳ��ص�OM IND�˿��յ����ݣ���NAS����
 �������  : pucVirAddr:   �������ַ
             pucPhyAddr:   ����ʵ��ַ
             ulDataLen:    ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 PPM_VComIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen)
{
    VOS_UINT32          ulInSlice;
    VOS_UINT32          ulOutSlice;
    VOS_UINT32          ulWriteSlice;
    VOS_UINT32          ret;
    
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendNum++;
    g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendLen += ulDataLen;

    ulInSlice = mdrv_timer_get_normal_timestamp();

    ret = DMS_WriteOmData(DMS_VCOM_OM_CHAN_DATA, pucVirAddr, ulDataLen);

    ulOutSlice = mdrv_timer_get_normal_timestamp();

    ulWriteSlice = (ulInSlice > ulOutSlice) ? (0xffffffff - ulInSlice + ulOutSlice) : (ulOutSlice - ulInSlice);

    if(ulWriteSlice > g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulMaxTimeLen)
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulMaxTimeLen = ulWriteSlice;
    }
    
    if (VOS_OK != ret)
    {
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrNum++;
        g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrLen += ulDataLen;

        return CPM_SEND_ERR;
    }

    return CPM_SEND_OK;
}


OM_VCOM_DEBUG_INFO *PPM_VComGetIndInfo(VOS_VOID)
{
    return &g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND];
}


/*****************************************************************************
 �� �� ��  : PPM_VComCfgPortInit
 ��������  : ���� Vcom ��OM CFGͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_VComCfgPortInit(VOS_VOID)
{
    /* ����������VCOM28�����������·� */
    DMS_RegOmChanDataReadCB(DMS_VCOM_OM_CHAN_CTRL, PPM_VComCfgReadData);
    /*CTRL���¼��ص�*/
    DMS_RegOmChanEventCB(DMS_VCOM_OM_CHAN_CTRL, PPM_VComEvtCB);

    CPM_PhySendReg(CPM_VCOM_CFG_PORT, PPM_VComCfgSendData);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_VComIndPortInit
 ��������  : ���� Vcom ��OM INDͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_VComIndPortInit(VOS_VOID)
{
    /* ��ά�ɲ����������ϱ���VCOM31�������������·� */
    DMS_RegOmChanDataReadCB(DMS_VCOM_OM_CHAN_DATA, VOS_NULL_PTR);
    /*DATA���¼��ص�*/
    DMS_RegOmChanEventCB(DMS_VCOM_OM_CHAN_DATA, PPM_VComEvtCB);

    CPM_PhySendReg(CPM_VCOM_IND_PORT, PPM_VComIndSendData);

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_VComPortInit
 ��������  : ���� Vcom �ڸ�ͨ���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_VComPortInit(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stVComDebugInfo[0], 0, sizeof(g_stVComDebugInfo));
    /*lint +e534*/

    /* Vcom ��OM INDͨ���ĳ�ʼ�� */
    PPM_VComIndPortInit();

    /* Vcom ��OM CNFͨ���ĳ�ʼ�� */
    PPM_VComCfgPortInit();

    /* Vcom ��errorlogͨ���ĳ�ʼ�� */
    GU_OamErrLogVComPortInit();

    return;
}

/*****************************************************************************
 �� �� ��  : PPM_VComInfoShow
 ��������  : ���ڴ�ӡ Vcom ��ͨ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ  :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID PPM_VComInfoShow(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nVCom30 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendNum);
    vos_printf("\r\nVCom30 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendLen);

    vos_printf("\r\nVCom30 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendErrNum);
    vos_printf("\r\nVCom30 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMSendErrLen);

    vos_printf("\r\nVCom30 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvNum);
    vos_printf("\r\nVCom30 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvLen);

    vos_printf("\r\nVCom30 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom30 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CBT].ulVCOMRcvErrLen);



    vos_printf("\r\nVCom28 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendNum);
    vos_printf("\r\nVCom28 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendLen);

    vos_printf("\r\nVCom28 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrNum);
    vos_printf("\r\nVCom28 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMSendErrLen);

    vos_printf("\r\nVCom28 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvNum);
    vos_printf("\r\nVCom28 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvLen);

    vos_printf("\r\nVCom28 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom28 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_CNF].ulVCOMRcvErrLen);



    vos_printf("\r\nVCom31 Send num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendNum);
    vos_printf("\r\nVCom31 Send Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendLen);

    vos_printf("\r\nVCom31 Send Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrNum);
    vos_printf("\r\nVCom31 Send Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMSendErrLen);

    vos_printf("\r\nVCom31 receive num is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvNum);
    vos_printf("\r\nVCom31 receive Len is           %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvLen);

    vos_printf("\r\nVCom31 receive Error num is         %d", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvErrNum);
    vos_printf("\r\nVCom31 receive Error Len is         %d\r\n", g_stVComDebugInfo[OM_LOGIC_CHANNEL_IND].ulVCOMRcvErrLen);
    /*lint +e534*/

    return;
}





