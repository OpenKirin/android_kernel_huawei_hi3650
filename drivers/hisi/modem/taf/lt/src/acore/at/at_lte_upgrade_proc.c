
/******************************************************************************
 *//* PROJECT   : MSP
 *//* SUBSYSTEM : MSP
 *//* MODULE    : AT
 *//* OWNER     :
 *//******************************************************************************
 */
/*lint --e{537,322,7,958,732,813,718,746,734}*/
#include "msp_upgrade_proc.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"
#include "ScInterface.h"
#include "mdrv.h"
#include <osm.h>
/*lint -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_UPGRADE_PROC_C
/*lint +e767 */
VOS_UINT32 g_atNvBackupFlag = 0;

/*bootrom�İ汾��ѯ*/
VOS_UINT32 atQryBootRomVer(VOS_UINT8 ucClientId)
{
    return AT_ERROR;
}

#include "msp_nv_id.h"
#include "drv_nv_id.h"



#define AT_NV_IMEI_LEN              15

VOS_UINT32 At_GetNvRevertState(VOS_VOID)
{
    VOS_UINT32 ret = (VOS_UINT32)-1;
    VOS_UINT16 resume_flag = 0;

    ret = NVM_Read(NV_ID_DRV_RESUME_FLAG,&resume_flag,sizeof(VOS_UINT16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return ((VOS_UINT32)-1);
    }
    return 0;
}

VOS_UINT32 At_GetNvAuthorityType(VOS_UINT32 * pdata)
{
    VOS_UINT32 ulRst;
    VOS_UINT8 *pucData = NULL;
    if(pdata==NULL)
    {
        return 0;
    }
    pucData = (VOS_UINT8 *)pdata;
    ulRst = NVM_Read(NV_ID_MSP_AUTHORITY_TYPE, pdata, sizeof(VOS_UINT32));

    if(ulRst != 0)
    {
        pucData[0] = 1;
        pucData[1] = 0;
        pucData[2] = 0;
        pucData[3] = 0;
        return ulRst;
    }

    return  0;
}

VOS_UINT32 At_GetNvAuthorityVer(VOS_UINT32 * pdata)
{
    VOS_UINT32 ulRst;

    if(pdata == NULL)
    {
        return ((VOS_UINT32)-1);
    }

    ulRst = NVM_Read(NV_ID_MSP_AUTHORITY_VER, pdata, sizeof(VOS_UINT32));

    if(ulRst != 0)
    {
        *pdata = 0;
    }

    return 0;
}



VOS_UINT32 At_GetImei(VOS_CHAR szimei [ 16 ])
{
    VOS_UINT32  ret;
    VOS_UINT32  uslen = 0;
    VOS_UINT32  subscript = 0;
    VOS_CHAR   checkdata = 0;
    VOS_CHAR   auctemp[AT_NV_IMEI_LEN+1] = {0};

    uslen = AT_NV_IMEI_LEN+1;

    ret = NVM_Read(0, auctemp, uslen);

    if(ret != 0)
    {
        return ret;
    }
    else
    {
        for (subscript = 0; subscript < (AT_NV_IMEI_LEN - 1); subscript += 2)
        {
            checkdata += (VOS_CHAR)(((auctemp[subscript])
                           +((auctemp[subscript + 1] * 2) / 10))
                           +((auctemp[subscript + 1] * 2) % 10));
        }
        checkdata = (10 - (checkdata%10)) % 10;

        for (subscript = 0; subscript < uslen; subscript++)
        {
            *(szimei + subscript) = *(auctemp + subscript) + 0x30; /*�ַ�ת��*/
        }

        szimei[AT_NV_IMEI_LEN - 1] = checkdata + 0x30;
        szimei[AT_NV_IMEI_LEN] = 0;
    }

    return 0;
}

VOS_UINT32 atQryDLoadVer(VOS_UINT8 ucClientId)
{
    DLOAD_VER_INFO_S                   *pstDloadVerInfo;

    pstDloadVerInfo = mdrv_dload_get_info();

    if(NULL == pstDloadVerInfo)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    if(NULL == pstDloadVerInfo->dloadver)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%s\r",
                                           pstDloadVerInfo->dloadver);

    return AT_OK;
}

/*�������û���ѯ������Ϣ�����ڷ��ص���ͺ�̨�汾�š���Ʒ�ͺ����ơ�����������Ϣ*/
VOS_UINT32 atQryDLoadInfo(VOS_UINT8 ucClientId)
{
    DLOAD_VER_INFO_S                   *pstDloadVerInfo;

    pstDloadVerInfo = mdrv_dload_get_info();

    if(NULL == pstDloadVerInfo)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    if ((NULL == pstDloadVerInfo->softwarever)
     || (NULL == pstDloadVerInfo->productname)
     || (NULL == pstDloadVerInfo->isover))
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                            "\rswver:%s\r\n",
                                            pstDloadVerInfo->softwarever);

    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr+ gstAtSendData.usBufLen),
                                            "\r\nisover:%s\r\n",
                                            pstDloadVerInfo->isover);

    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr+ gstAtSendData.usBufLen),
                                            "\r\nproduct name:%s\r\n",
                                            pstDloadVerInfo->productname);

    return AT_OK;
}

/*NV��������*/
VOS_UINT32 atSetNVBackup(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = NVM_UpgradeBackup(EN_NVM_BACKUP_FILE);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    g_atNvBackupFlag ++;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;
}

/*NV�ָ�����*/
VOS_UINT32 atSetNVRestore(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = NVM_UpgradeRestore();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;
}

VOS_UINT32 atQryAuthorityVer(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    VOS_UINT32 ulAuthorityVer = 0;
    VOS_UINT8  ucVer[4] ={0};
    VOS_UINT32 i = 0;

    ulRst = At_GetNvAuthorityVer(&ulAuthorityVer);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    MSP_MEMCPY(ucVer,&ulAuthorityVer,sizeof(VOS_UINT32));

    for(i = 0;i < 4;i++)
    {
        ucVer[i] = (ucVer[i] > 9 ? 0 : ucVer[i]) + '0';  /**/
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR*)pgucAtSndCodeAddr,
                                                "\r%s\r",
                                                ucVer
                                                );
    return AT_OK;
}

VOS_UINT32 atQryAuthorityID(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst;
    VOS_UINT8 pData[NV_ITEM_IMEI_SIZE] = {0};
    gstAtSendData.usBufLen = 0;


    ulRst = At_GetImei((VOS_CHAR *)pData);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%s\r",
                                           pData
                                         );

    return AT_OK;
}

//�л�������ģʽ����������󽫽�������ģʽ
VOS_UINT32 atSetGodLoad(VOS_UINT8 ucClientId)
{
    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "OK"
                                         );
    mdrv_dload_set_curmode(DLOAD_MODE_DOWNLOAD);

    VOS_TaskDelay(500);

    mdrv_dload_set_softload(true);

    mdrv_sysboot_shutdown();

    return AT_OK;
}

// *****************************************************************************
// ��������: atSetReset
// ��������: ������������ "^RESET"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
// ��    ��: �ѩ��/c00172979 [2010-11-29]

//  2.��    ��   : 2015��01��26��
//    �޸�����   : �޸����ⵥDTS2015011307352��AT^RESET�����ӡOK

// *****************************************************************************
VOS_UINT32 atSetReset(VOS_UINT8 ucClientId)
{
    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucClientId, AT_OK);

    VOS_TaskDelay(300); /*wait 300 tick*/

    mdrv_sysboot_restart();

    return AT_SUCCESS;
}

//�Զ��ָ�״̬��ѯ
VOS_UINT32 atSetNVRstSTTS(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = At_GetNvRevertState();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;

}

VOS_UINT32 atSetNVFactoryRestore(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;

    /*��ΪMODEN���Ż��·������������moden�ڲ�����NV�ָ���ֱ�ӷ���OK*/
    if ( AT_MODEM_USER == gastAtClientTab[ucClientId].UserType )
    {
        return AT_OK;
    }

    ulRst = NVM_RevertFNV();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );
    return AT_OK;
}


VOS_UINT32 atSetNVFactoryBack(VOS_UINT8 ucClientId)
{
    VOS_UINT32                          ulRst;

    ulRst = NVM_BackUpFNV();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        printk("atSetNVFactoryBack:nv Backup faile! %d", ulRst);

        CmdErrProc(ucClientId, ulRst, 0, NULL);

        return AT_ERROR;
    }

    /* Added by d00212987 �ڸ�AT����������SC�ı��ݡ� 2015-08-10, begin */
    ulRst = SC_COMM_Backup();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        printk("atSetNVFactoryBack:SC Backup faile! %d", ulRst);

        CmdErrProc(ucClientId, ulRst, 0, NULL);

        return AT_ERROR;
    }
    /* Added by d00212987 �ڸ�AT����������SC�ı��ݡ� 2015-08-10, end */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );
    return AT_OK;

}

VOS_UINT32  AT_SetLteSdloadPara(VOS_UINT8 ucClientId)
{
    FTM_RD_SDLOAD_REQ_STRU stSdloadSetReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_SDLOAD_REQ, ucClientId, (VOS_VOID*)(&stSdloadSetReq),
        sizeof(stSdloadSetReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_SDLOAD_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/* BEGIN: To_Be_Deleted_V7R2 */
VOS_UINT32 atQryBootRomVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_BOOTROMVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_BOOTROMVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
                                                    AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                    (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
                                                    "\r\n%s\r\n",
                                                    pstCnf->szSendStr
                                                    );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}
VOS_UINT32 atQryDLoadVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_DLOADVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_DLOADVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
              AT_CMD_MAX_LEN,
              (VOS_CHAR *)(pgucLAtSndCodeAddr),
              (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
              "\r\n%s\r\n",
              pstCnf->cVer
              );

	    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }

    return AT_OK;
}

VOS_UINT32 atQryDLoadInfoCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_DLOADINFO_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_DLOADINFO_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = 0;
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
                                                "\r\nswver:%s\r\n",
                                                pstCnf->szSendSW
                                              );

        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nisover:%s\r\n",
                                                pstCnf->szSendISO
                                              );
        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nproduct name:%s\r\n",
                                                pstCnf->szSendProductID
                                              );
        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\ndload type:%s\r\n",
                                                pstCnf->szSendDloadType
                                              );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVBackupCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVBACKUP_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVBACKUP_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        g_atNvBackupFlag++;

        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                               pstCnf->ulRetValue
                                             );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVRestoreCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVRESTORE_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVRESTORE_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                               pstCnf->ulRetValue
                                             );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atQryAuthorityVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_AUTHORITYVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_AUTHORITYVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = 0;
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucLAtSndCodeAddr,
                                                    "\r\n%s\r\n",
                                                    pstCnf->szAuthorityVer
                                                    );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atQryAuthorityIDCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_AUTHORITYID_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_AUTHORITYID_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%s,%s\r\n",
                                               pstCnf->szAuthorityID,pstCnf->szAuthorityType
                                             );

	    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVRstSTTSCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVRSTSTTS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;
/*  VOS_BOOL bRet = TRUE;
 */
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVRSTSTTS_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%s\r\n",
                                               pstCnf->szNVRst
                                             );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetSdloadCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_SDLOAD_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;
/*  VOS_BOOL bRet = TRUE;
 */
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_SDLOAD_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
    	return AT_OK;
    }

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_OK;
}
/* END: To_Be_Deleted_V7R2 */

