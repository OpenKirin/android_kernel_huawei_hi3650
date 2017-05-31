


/*lint -save -e537*/
#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <osl_thread.h>
#include <bsp_nvim.h>
#include "nv_comm.h"
#include "nv_file.h"
#include "nv_ctrl.h"
#include "bsp_blk.h"
#include "nv_xml_dec.h"
#include "nv_debug.h"
#include "nv_index.h"
#include "nv_crc.h"
#include "nv_partition_img.h"
#include "nv_partition_bakup.h"
#include "NVIM_ResumeId.h"
#include "bsp_dump.h"
#include "nv_msg.h"

/*lint -restore +e537*/

/*lint -save -e713 -e830*/

u32 nv_readEx(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    u32 ret = NV_ERROR;
    nv_file_info_s file_info;
    nv_item_info_s item_info;
    nv_rd_req      rreq;
    nv_ctrl_info_s* ctrl_info = (nv_ctrl_info_s*)NV_GLOBAL_CTRL_INFO_ADDR;

    nv_debug(NV_FUN_READ_EX,0,itemid,modem_id,datalen);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_READ_EX,1,itemid,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    ret = nv_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&item_info,&file_info);
    if(ret)
    {
        nv_printf("can not find 0x%x !\n",itemid);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    if((offset + datalen) > item_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_READ_EX,3,offset,datalen,item_info.nv_len);
        goto nv_readEx_err;
    }

    if((modem_id == 0) || (modem_id > ctrl_info->modem_num))
    {
        ret = BSP_ERR_NV_INVALID_MDMID_ERR;
        nv_debug(NV_FUN_READ_EX,4,ret,itemid,modem_id);
        goto nv_readEx_err;
    }

    if(modem_id > item_info.modem_num)
    {
        modem_id = 1;
    }

    rreq.itemid  = itemid;
    rreq.modemid = modem_id;
    rreq.offset  = offset;
    rreq.pdata   = pdata;
    rreq.size    = (datalen < item_info.nv_len) ? datalen : item_info.nv_len;
    (void)nv_read_from_mem(&rreq, &item_info);

    /*lint -save -e578 -e530*/
    nv_debug_trace(pdata, datalen);
    /*lint -restore +e578 +e530*/

    return NV_OK;

nv_readEx_err:
    nv_mntn_record("\n[%s]:[0x%x]:[%d] 0x%x\n",__FUNCTION__,itemid,modem_id, ret);
    nv_help(NV_FUN_READ_EX);
    return ret;
}

u32 nv_writeEx(u32 modem_id, u32 itemid, u32 offset, u8* pdata, u32 datalen)
{
    u32 ret = NV_ERROR;
    nv_file_info_s  file_info;
    nv_item_info_s  item_info;
    nv_wr_req       wreq;
    u8  test_byte;
    nv_ctrl_info_s* ctrl_info = (nv_ctrl_info_s*)NV_GLOBAL_CTRL_INFO_ADDR;

    nv_debug(NV_FUN_WRITE_EX,0,itemid,modem_id,datalen);
    nv_debug_record(NV_DEBUG_WRITEEX_START|itemid<<16);

    if((NULL == pdata)||(0 == datalen))
    {
        nv_debug(NV_FUN_WRITE_EX,1,itemid,datalen,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    /* test pdata is accessable */
    test_byte = *pdata;
    UNUSED(test_byte);

    ret = nv_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&item_info,&file_info);
    if(ret)
    {
        nv_printf("can not find 0x%x !\n",itemid);
        nv_debug(NV_FUN_WRITE_EX,2,itemid,modem_id,offset);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    /*lint -save -e578 -e530*/
    nv_debug_trace(pdata, datalen);
    /*lint -restore +e578 +e530*/

    if((datalen + offset) >item_info.nv_len)
    {
        ret = BSP_ERR_NV_ITEM_LEN_ERR;
        nv_debug(NV_FUN_WRITE_EX,3,itemid,datalen,item_info.nv_len);
        goto nv_writeEx_err;
    }

    if((modem_id == 0) || (modem_id > ctrl_info->modem_num))
    {
        ret = BSP_ERR_NV_INVALID_MDMID_ERR;
        nv_debug(NV_FUN_WRITE_EX,4,itemid,datalen,item_info.nv_len);
        goto nv_writeEx_err;
    }

    if(modem_id > item_info.modem_num)
    {
        modem_id = 1;
    }

    /* check crc before write */
    if(nv_crc_need_check_inwr(&item_info, datalen))
    {
        ret = nv_crc_check_item(&item_info, modem_id);
        if(ret)
        {
            nv_debug(NV_FUN_WRITE_EX, 6, itemid,datalen,ret);
            ret = nv_resume_item(&item_info, itemid, modem_id);
            if(ret)
            {
                nv_debug(NV_FUN_WRITE_EX,7, itemid, modem_id, ret);
                goto nv_writeEx_err;
            }
        }
    }

    wreq.itemid    = itemid;
    wreq.modemid   = modem_id;
    wreq.offset    = offset;
    wreq.pdata     = pdata;
    wreq.size      = datalen;
    nv_debug_record(NV_DEBUG_WRITEEX_MEM_START);
    ret = nv_write_to_mem(&wreq, &item_info);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,8,itemid,datalen,0);
        goto nv_writeEx_err;
    }

    nv_debug_record(NV_DEBUG_WRITEEX_FILE_START);
    ret = nv_write_to_file(&wreq, &item_info);
    if(ret)
    {
        nv_debug(NV_FUN_WRITE_EX,9,itemid,datalen,ret);
        goto nv_writeEx_err;
    }
    nv_debug_record(NV_DEBUG_WRITEEX_END|itemid<<16);

    return NV_OK;

nv_writeEx_err:
    nv_mntn_record("\n[%s]:[0x%x]:[%d]\n",__FUNCTION__,itemid,modem_id);
    nv_help(NV_FUN_WRITE_EX);
    return ret;
}



u32 bsp_nvm_get_nv_num(void)
{
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    return ctrl_info->ref_count;
}

u32 bsp_nvm_get_nvidlist(NV_LIST_INFO_STRU*  nvlist)
{
    u32 i;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)(NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);

    if(NULL == nvlist)
    {
        return NV_ERROR;
    }

    for(i = 0;i<ctrl_info->ref_count;i++)
    {
        nvlist[i].usNvId       = ref_info[i].itemid;
        nvlist[i].ucNvModemNum = ref_info[i].modem_num;
    }
    return NV_OK;
}

u32 bsp_nvm_get_len(u32 itemid,u32* len)
{
    u32 ret  = NV_ERROR;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};

    nv_debug(NV_API_GETLEN,0,itemid,0,0);
    if(NULL == len)
    {
        nv_debug(NV_API_GETLEN,1,itemid,0,0);
        return BSP_ERR_NV_INVALID_PARAM;
    }

    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        nv_debug(NV_API_GETLEN,3,itemid,0,0);
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }
    ret = nv_search_byid(itemid,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info, &file_info);
    if(NV_OK == ret)
    {
        *len = ref_info.nv_len;
        return NV_OK;
    }
    return ret;
}

u32 bsp_nvm_authgetlen(u32 itemid,u32* len)
{
    return bsp_nvm_get_len(itemid,len);
}



u32 bsp_nvm_dcread_direct(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return nv_readEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_dcread(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_readEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_auth_dcread(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return bsp_nvm_dcread(modem_id,itemid,pdata,datalen);
}

u32 bsp_nvm_dcreadpart(u32 modem_id,u32 itemid,u32 offset,u8* pdata,u32 datalen)
{
    /*check init state*/
    if(false == nv_read_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_readEx(modem_id,itemid,offset,pdata,datalen);
}

u32 bsp_nvm_dcwrite(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    if(false == nv_write_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_writeEx(modem_id,itemid,0,pdata,datalen);
}

u32 bsp_nvm_auth_dcwrite(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return bsp_nvm_dcwrite(modem_id,itemid,pdata,datalen);
}

u32 bsp_nvm_dcwritepart(u32 modem_id,u32 itemid, u32 offset,u8* pdata,u32 datalen)
{
    if(false == nv_write_right(itemid))
    {
        return BSP_ERR_NV_MEM_INIT_FAIL;
    }

    return nv_writeEx(modem_id,itemid,offset,pdata,datalen);
}

u32 bsp_nvm_dcwrite_direct(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return nv_writeEx(modem_id,itemid,0,pdata,datalen);
}


/*lint -restore +e529*/

u32 bsp_nvm_flush(void)
{
    u32 ret;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    ret = nv_flush_wrbuf(ddr_info);
    if (ret) {
        nv_printf("Fail to flush low priority write buffer \n");
    }

    ret = nv_send_msg_sync(NV_TASK_MSG_FLUSH, 0, 0);
    return ret;
}


u32 bsp_nvm_flushSys(u32 itemid)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 ulTotalLen = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_create_flag_file((s8*)NV_SYS_FLAG_PATH);

    nv_debug(NV_FUN_FLUSH_SYS,0,0,0,0);
    if(nv_file_access((s8*)NV_FILE_SYS_NV_PATH,0))
    {
        fp = nv_file_open((s8*)NV_FILE_SYS_NV_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_FILE_SYS_NV_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        nv_debug(NV_FUN_FLUSH_SYS,1,ret,0,0);
        ret = BSP_ERR_NV_NO_FILE;
        goto nv_flush_err;
    }
    ulTotalLen = ddr_info->file_len;
    /*ϵͳ�������ݲ���CRCУ�飬��˻�дʱ������CRCУ����Ĵ��λ��*/
    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,ulTotalLen,fp);
    nv_file_close(fp);
    if(ret != ulTotalLen)
    {
        nv_debug(NV_FUN_FLUSH_SYS,3,ret,ulTotalLen,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_flush_err;
    }

    nv_delete_flag_file((s8*)NV_SYS_FLAG_PATH);
    return NV_OK;

nv_flush_err:
    nv_mntn_record("\n[%s]\n",__func__);
    nv_help(NV_FUN_FLUSH_SYS);
    return ret;
}


/*
* Function   : bsp_nvm_backup
* Discription: backup the memory to file/flash/rfile
* Parameter  : none
* Output     : result
* History    : yuyangyang  00228784  create
* ��ע       : ���ڱ����ڴ�nv���������Ĺ����У���Ҫ��֤�ڴ��е�NV���ݲ�����д�����ݹ�������Ҫ��ס�ڴ棬
*              ��ô�Ըýӿڵ�ʹ�ã�Ҫ�г����ϵ����ƣ�Ŀǰʹ�ó�������:
*              1. �ṩ���û��ӿ�mdrv_nv_backupʹ�ã�Ŀǰû��ʹ�ã�
*              2. bsp_nvm_update_default������ר�ýӿڣ�����at����^inforbu�������в���д������
*              3. nv_file_flag_check�����������м��д������ԵĲ����������в���д������
*              4. nv_data_writeback, �������֮�󣬽������������д�ر������������в���д������
*                                    �������ع����У���img�����ͱ��ݷ���������ʧ�ܣ���Ҫ�ӳ������������ָ���
*                                    �ָ���ɺ�д�ر������������в���д������
*               �����г�������bsp_nvm_backup�ӿڹ��������ڴ治��������գ�ά��ʱ��Ҫ������ע��
*/
u32 bsp_nvm_backup(u32 crc_flag)
{
    u32 ret = NV_ERROR;
    nv_global_info_s* ddr_info = (nv_global_info_s*)NV_GLOBAL_INFO_ADDR;
    FILE* fp = NULL;
    u32 writeLen = 0;

    nv_debug(NV_API_BACKUP,0,0,0,0);

    if( (ddr_info->acore_init_state != NV_INIT_OK)&&
        (ddr_info->acore_init_state != NV_KERNEL_INIT_DOING))
    {
        return NV_ERROR;
    }

    nv_create_flag_file((s8*)NV_BACK_FLAG_PATH);

    if(nv_file_access((s8*)NV_BACK_PATH,0))
    {
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_API_BACKUP,1,ret,0,0);
        goto nv_backup_fail;
    }

    writeLen = ddr_info->file_len;

    if(NV_FLAG_NEED_CRC == crc_flag)
    {
        ret = nv_crc_check_ddr(NV_RESUME_NO);
        if(ret)
        {
            nv_debug(NV_API_BACKUP,2,ret,0, 0);
            (void)nv_debug_store_ddr_data();
            goto nv_backup_fail;
        }
    }

    /* �����Ҫ����CRCУ��, �������ݵ����������ڴ��е����ݽϱ��������£�����crc check���ܴ��Զ��ָ�,
       Ҫ��֤д�뱸���������ݣ�crcУ����ȷ��ͬʱ���ݹ������ڴ����ݲ�����д��������Ҫ��ס�ڴ� */
    nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    ret = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,writeLen,fp);
    (void)nv_ipc_sem_give(IPC_SEM_NV_CRC);
    nv_file_close(fp);
    fp = NULL;
    if(ret != writeLen)
    {
        nv_debug(NV_API_BACKUP,3,ret,writeLen,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_backup_fail;
    }

    (void)nv_bakup_info_reset();

    if(nv_file_update(NV_BACK_PATH))
    {
        nv_debug(NV_API_BACKUP, 4 , 0, 0, 0);
    }

    nv_delete_flag_file((s8*)NV_BACK_FLAG_PATH);

    return NV_OK;
nv_backup_fail:
    if(fp){nv_file_close(fp);}
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_API_BACKUP);
    return ret;

}


/*
* Function   : bsp_nvm_update_default
* Discription: update mem data to default section
* Parameter  : none
* Output     : result
* History    : yuyangyang  00228784  create
* ��ע       : ����ר�ýӿڣ�����at����^inforbu����ʱҪ��֤û������дNV�Ķ�����
*              ���ݳ��������Ĺ����л���סNV�ڴ治��д��
*              �����ʱ��дNV���������ܻᵼ�»�ȡ�ڴ�дȨ��ʱ�䳬��������δ֪�ĳ������
*/
u32 bsp_nvm_update_default(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    NV_SELF_CTRL_STRU self_ctrl = {};

    nv_debug(NV_FUN_UPDATE_DEFAULT,0,0,0,0);

    if(ddr_info->acore_init_state != NV_INIT_OK)
    {
        return NV_ERROR;
    }

    if(false == nv_check_update_default_right())
    {
        nv_printf("no right to write factory data!\n");
    }

    ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL, (u8*)&self_ctrl, sizeof(NV_SELF_CTRL_STRU));
    if(ret)
    {
        nv_printf("read nv 0x%x fail,ret = 0x%x\n", NV_ID_DRV_SELF_CTRL, ret);
        return NV_ERROR;
    }
    self_ctrl.ulResumeMode = NV_MODE_USER;
    ret = bsp_nvm_write(NV_ID_DRV_SELF_CTRL, (u8*)&self_ctrl, sizeof(NV_SELF_CTRL_STRU));
    if(ret)
    {
        nv_printf("write nv 0x%x fail,ret = 0x%x\n", NV_ID_DRV_SELF_CTRL, ret);
        return NV_ERROR;
    }

    /*��д���ļ�ǰ����CRCУ�飬�Է����ݲ���ȷ*/
    ret = nv_crc_check_ddr(NV_RESUME_NO);
    if(ret)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT,3,ret,ddr_info->file_len,0);
        (void)nv_debug_store_ddr_data();
        goto nv_update_default_err;
    }

    if(nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        fp = nv_file_open((s8*)NV_DEFAULT_PATH,(s8*)NV_FILE_WRITE);
    }
    else
    {
        fp = nv_file_open((s8*)NV_DEFAULT_PATH,(s8*)NV_FILE_RW);
    }
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_FUN_UPDATE_DEFAULT,2,ret,0,0);
        goto nv_update_default_err;
    }

    /* ��סNV�ڴ棬��д���ļ�ǰ����CRCУ�飬�Է����ݲ���ȷ��
       ͬʱҪ��֤��ǰ��crc check�����Զ��ָ������Զ��ָ���crc check���ڻָ������л�ȡipc semaphore����������*/
    ret = nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
    if(ret)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT, 3, ret,0,0);
        goto nv_update_default_err;
    }
    datalen = (u32)nv_file_write((u8*)NV_GLOBAL_CTRL_INFO_ADDR,1,ddr_info->file_len,fp);
    (void)nv_ipc_sem_give(IPC_SEM_NV_CRC);

    nv_file_close(fp);
    if(datalen != ddr_info->file_len)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT,6,ret,ddr_info->file_len,0);
        ret = BSP_ERR_NV_WRITE_FILE_FAIL;
        goto nv_update_default_err;
    }

    ret = bsp_nvm_backup(NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_debug(NV_FUN_UPDATE_DEFAULT,7,ret,0,0);
        goto nv_update_default_err;
    }

    nv_delete_update_default_right();

    return NV_OK;
nv_update_default_err:
    /* coverity[deref_arg] */
    if(fp){nv_file_close(fp);}
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_UPDATE_DEFAULT);
    return ret;
}



u32 bsp_nvm_revert_default(void)
{
    u32 ret;

    /* �Ȱѳ���������NV��ָ����� */
    ret = nv_revert_data((s8*)NV_DEFAULT_PATH, NULL, 0, NV_FLAG_NEED_CRC);
    if(ret)
    {
        nv_mntn_record("revert from default partition failed, ret=0x%x\n!", ret);
        return ret;
    }

    /*��Ҫnv��ָ�,���»ָ���img����������ݣ���Ҫ��������CRCУ����*/
    ret = nv_revert_data(NV_IMG_PATH,g_ausNvResumeSecureIdList,\
        bsp_nvm_getRevertNum(NV_SECURE_ITEM), NV_FLAG_NEED_CRC);
    if(ret)
    {
        nv_mntn_record("revert keeping secure list failed, ret=0x%x\n!", ret);
        return ret;
    }

    ret = nv_img_flush_all();
    ret |= bsp_nvm_flushSys(NV_ERROR);

    nv_mntn_record("bsp_nvm_revert_default success!\n!");

    return ret;
}

u32 nv_write2file_handle(nv_cmd_req *msg)
{
    u32 ret     = 0;
    nv_item_info_t *nv_info;
    nv_flush_item_s flush_item;

    nv_info = &msg->nv_item_info;
    flush_item.itemid = nv_info->itemid;
    flush_item.modemid = nv_info->modem_id;
    ret = nv_flushItem(&flush_item);
    if (ret)
    {
        return ret;
    }

    if (true == nv_isSysNv(nv_info->itemid))
    {
        ret = bsp_nvm_flushSys(nv_info->itemid);
    }

    return ret;
}

s32 bsp_nvm_icc_task(void* parm)
{
    s32 ret = -1;
    nv_cmd_req *msg;
    nv_item_info_t *nv_info;

    /* coverity[no_escape] */
    for(;;)
    {
        osl_sem_down(&g_nv_ctrl.task_sem);

        g_nv_ctrl.opState = NV_OPS_STATE;

        /*�����ǰ����˯��״̬����ȴ����Ѵ���*/
        if(g_nv_ctrl.pmState == NV_SLEEP_STATE)
        {
            printk("%s cur state in sleeping,wait for resume end!\n",__func__);
            osl_sem_down(&g_nv_ctrl.suspend_sem);
        }

        msg = nv_get_cmd_req();
        if (msg == NULL) {
            g_nv_ctrl.opState = NV_IDLE_STATE;
            continue;
        }

        nv_debug_printf("msg type:0x%x\n", msg->msg_type);
        nv_info = &msg->nv_item_info;
        switch (msg->msg_type) {
            case NV_TASK_MSG_WRITE2FILE:
                ret = nv_write2file_handle(msg);
                break;

            case NV_TASK_MSG_FLUSH:
                /* there is no actual nv operation, return NV_OK and notify
                           * NV writing process the result actually
                           */
                 ret = NV_OK;
                break;

            case NV_TASK_MSG_RESUEM:
                ret = nv_resume_ddr_from_img();
                break;

            case NV_TASK_MSG_RESUEM_ITEM:
                ret = nv_resume_item(NULL, nv_info->itemid, nv_info->modem_id);
                break;

            default:
                nv_printf("msg type invalid, msg type;0x%x\n", msg->msg_type);
                break;
        }

        nv_debug_printf("deal msg ok\n");
        if (ret) {
            nv_mntn_record("flush nv to file fail, msg type:0x%x errno:0x%x\n", msg->msg_type, ret);
        }

        if (msg->nv_msg_callback) {
            msg->nv_msg_callback(ret, msg->sn);
        }

        nv_put_cmd_req(msg);
        g_nv_ctrl.task_proc_count++;
        g_nv_ctrl.opState = NV_IDLE_STATE;
    }
}


u32 bsp_nvm_xml_decode(void)
{
    u32 ret = NV_ERROR;

    if(!nv_file_access(NV_XNV_CARD1_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD1_PATH,NV_XNV_CARD1_MAP_PATH,NV_USIMM_CARD_1);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_XNV_CARD2_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD2_PATH,NV_XNV_CARD2_MAP_PATH,NV_USIMM_CARD_2);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_XNV_CARD3_PATH,0))
    {
        ret = nv_xml_decode(NV_XNV_CARD3_PATH, NV_XNV_CARD3_MAP_PATH, NV_USIMM_CARD_3);
        if(ret)
        {
            return ret;
        }
    }

    /*CUST XML �޶�ӦMAP�ļ��������ֵ����*/
    if(!nv_file_access(NV_CUST_CARD1_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD1_PATH,NULL,NV_USIMM_CARD_1);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_CUST_CARD2_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD2_PATH,NULL,NV_USIMM_CARD_2);
        if(ret)
        {
            return ret;
        }
    }

    if(!nv_file_access(NV_CUST_CARD3_PATH,0))
    {
        ret = nv_xml_decode(NV_CUST_CARD3_PATH, NULL, NV_USIMM_CARD_3);
        if(ret)
        {
            return ret;
        }
    }

    return NV_OK;
}


u32 bsp_nvm_upgrade(void)
{
    u32 ret;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    nv_debug(NV_FUN_UPGRADE_PROC,0,0,0,0);
    nv_mntn_record("Balong nv upgrade start!\n");

    /*�ж�fastboot�׶�xml �����Ƿ��쳣���������쳣������Ҫ���½���xml*/
    if(ddr_info->xml_dec_state != NV_XML_DEC_SUCC_STATE)
    {
        nv_mntn_record("fastboot xml decode fail ,need kernel decode again!\n");
        ret = bsp_nvm_xml_decode();
        if(ret)
        {
            nv_mntn_record("kernel xml decode failed 0x%x!\n", ret);
            nv_debug(NV_FUN_UPGRADE_PROC,1,ret,0,0);
            goto upgrade_fail_out;
        }
    }


    /*�����ָ�������Ƭ�汾ֱ�ӷ���ok*/
    ret = nv_upgrade_revert_proc();
    if(ret)
    {
        nv_mntn_record("upgrade revert failed 0x%x!\n", ret);
        nv_debug(NV_FUN_UPGRADE_PROC,4,ret,0,0);
        goto upgrade_fail_out;
    }
    else
    {
        nv_mntn_record("upgrade revert success!\n");
    }

    (void)nv_crc_make_ddr();
    nv_mntn_record("upgrade mkddr crc success!\n");

    /*����������д���������*/
    ret = nv_data_writeback();
    if(ret)
    {
        nv_mntn_record("upgrade writeback failed 0x%x!\n", ret);
        nv_debug(NV_FUN_UPGRADE_PROC,7,ret,0,0);
        goto upgrade_fail_out;
    }
    else
    {
        nv_mntn_record("upgrade writeback success!\n");
    }

    /*����������Ч*/
    ret = (u32)nv_modify_upgrade_flag(false);/*lint !e747 */
    if(ret)
    {
        nv_mntn_record("upgrade set dload packet invalid failed 0x%x!\n", ret);
        nv_debug(NV_FUN_UPGRADE_PROC,8,ret,0,0);
        goto upgrade_fail_out;
    }

    ret = nv_file_update(NV_DLOAD_PATH);
    if(ret)
    {
        nv_mntn_record("upgrade nv_file_update failed 0x%x!\n", ret);
        nv_debug(NV_FUN_UPGRADE_PROC, 9,ret,0,0);
        goto upgrade_fail_out;
    }

    return NV_OK;
upgrade_fail_out:
    nv_mntn_record("\n%s\n",__func__);
    nv_help(NV_FUN_UPGRADE_PROC);
    return NV_ERROR;
}

/*
* Function   : bsp_nvm_resume_bakup
* Discription: resume all nv data from bakup partition, when image partition is invalid
* Parameter  : none
* Output     : result
* History    : yuyangyang  00228784  create
* ��ע       : reload�ڳ�ʼ�������У���Ҫ�������ϱ�֤��ʱ������дNV�Ĳ�����
               �Ӷ���crc check��ʱ���ڴ治�ᱻ��д��
*/
u32 bsp_nvm_resume_bakup(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;

    if(true == nv_check_file_validity((s8 *)NV_BACK_PATH, (s8 *)NV_BACK_FLAG_PATH))
    {
        nv_mntn_record("load from %s\n",NV_BACK_PATH);
        fp = nv_file_open((s8*)NV_BACK_PATH,(s8*)NV_FILE_READ);
        if(!fp)
        {
            nv_debug(NV_FUN_MEM_INIT,5,0,0,0);
            goto load_err_proc;
        }

        ret = nv_read_from_file(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen, NV_FILE_BACKUP);
        nv_file_close(fp);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,6,0,0,0);
            goto load_err_proc;
        }

        ret = nv_crc_check_ddr(NV_RESUME_NO);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,8,ret,0,0);
            goto load_err_proc;
        }

        /*�ӱ�����������Ҫ����д�빤����*/
        ret = nv_img_flush_all();
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,9,0,0,0);
            goto load_err_proc;
        }

        return NV_OK;
    }

load_err_proc:
    ret = nv_load_err_proc();
    if(ret)
    {
        nv_mntn_record("%s %d ,err revert proc ,ret :0x%x\n",__func__,__LINE__,ret);
        nv_help(NV_FUN_MEM_INIT);
    }

    return ret;
}


/*
* Function   : bsp_nvm_reload
* Discription: init mem,include first load the file to dload section,
*              this step ensure the nv data copy to ddr,enhance the dload file check
* Parameter  : none
* Output     : result
* History    : yuyangyang  00228784  create
* ��ע       : reload�ڳ�ʼ�������У���Ҫ�������ϱ�֤��ʱ������дNV�Ĳ�����
               �Ӷ���crc check��ʱ���ڴ治�ᱻ��д��
*/
u32 bsp_nvm_reload(void)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;

    nv_debug(NV_FUN_MEM_INIT,0,0,0,0);

    /*�����������ݴ��ڣ�����δд����ɵı�־�ļ�*/
    if( true == nv_check_file_validity((s8 *)NV_IMG_PATH, (s8 *)NV_IMG_FLAG_PATH))
    {
        nv_mntn_record("load from %s ...%s %s \n",NV_IMG_PATH,__DATE__,__TIME__);
        fp = nv_file_open((s8*)NV_IMG_PATH,(s8*)NV_FILE_READ);
        if(!fp)
        {
            nv_debug(NV_FUN_MEM_INIT,1,0,0,0);
            goto load_bak;
        }

        ret = nv_read_from_file(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen, NV_FILE_SYS_NV);
        nv_file_close(fp);
        if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,2,ret,0,0);
            goto load_bak;
        }

        /*reload�ڳ�ʼ�������У���Ҫ�������ϱ�֤��ʱ������дNV�Ĳ������Ӷ���crc check��ʱ���ڴ治�ᱻ��д
          ���Զ��ָ���crc check�����ڻָ������л�ȡcrc ipc semaphore�����Բ�����ס�ڴ���crc check*/
        ret = nv_crc_check_ddr(NV_RESUME_BAKUP);
        if(BSP_ERR_NV_CRC_RESUME_SUCC == ret)
        {
            ret = nv_img_flush_all();
            if(ret)
            {
                nv_mntn_record("nv resume write back failed 0x%x\n", ret);
                return ret;
            }
            nv_printf("img check crc error, but resume success, write back to img!\n");
        }
        else if(ret)
        {
            nv_debug(NV_FUN_MEM_INIT,4,ret,0,0);
            nv_mntn_record("nv image check crc failed %d...%s %s \n", ret, __DATE__,__TIME__);

            /* ���������Ȼ���bakup�����ָ� */
            (void)nv_debug_store_file(NV_IMG_PATH);
            if(nv_debug_is_resume_bakup())
            {
                ret = bsp_nvm_resume_bakup();
                if(ret)
                {
                    nv_mntn_record("nv resume bakup failed %d...%s %s \n", ret, __DATE__,__TIME__);
                }
            }
            else
            {
                nv_mntn_record("config don't resume bakup...%s %s \n",__DATE__,__TIME__);
            }

            /* ��λϵͳ */
            if(nv_debug_is_reset())
            {
                system_error(DRV_ERRNO_NV_CRC_ERR, NV_FUN_MEM_INIT, 3, NULL, 0);
            }
        }

        return ret;
    }

load_bak:

    return bsp_nvm_resume_bakup();
}
/*****************************************************************************
 �� �� ��  : bsp_nvm_write_buf_init
 ��������  : ��ʼ��д��NVʱʹ�õ�buf���ź���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
u32 bsp_nvm_buf_init(void)
{
    /*create sem*/
    osl_sem_init(1,&g_nv_ctrl.nv_list_sem);
    INIT_LIST_HEAD(&g_nv_ctrl.nv_list);

    return NV_OK;
}

s32 bsp_nvm_kernel_init(void)
{
    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    nv_debug(NV_FUN_KERNEL_INIT,0,0,0,0);

    /*sem & lock init*/
    spin_lock_init(&g_nv_ctrl.spinlock);
    osl_sem_init(0,&g_nv_ctrl.task_sem);
    osl_sem_init(0,&g_nv_ctrl.suspend_sem);
    osl_sem_init(1,&g_nv_ctrl.rw_sem);
    osl_sem_init(0,&g_nv_ctrl.cc_sem);
    wake_lock_init(&g_nv_ctrl.wake_lock,WAKE_LOCK_SUSPEND,"nv_wakelock");
    g_nv_ctrl.shared_addr = (struct nv_global_ddr_info_stru *)NV_GLOBAL_INFO_ADDR;

    nv_mntn_record("Balong nv init  start! %s %s\n",__DATE__,__TIME__);

    (void)nv_debug_init();

    /*file info init*/
    ret = nv_file_init();
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,1,ret,0,0);
        goto out;
    }
    if(ddr_info->acore_init_state != NV_BOOT_INIT_OK)
    {
        nv_mntn_record("fast boot nv init fail !\n");
        nv_show_fastboot_err();
        memset(ddr_info,0,sizeof(struct nv_global_ddr_info_stru));
    }

    ddr_info->acore_init_state = NV_KERNEL_INIT_DOING;
    nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);

    ret = bsp_ipc_sem_create(IPC_SEM_NV_CRC);
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT, 2, ret, 0, 0);
        goto out;
    }

    if((ddr_info->mem_file_type == NV_MEM_DLOAD) &&
       (!nv_file_access((s8*)NV_DLOAD_PATH,0)) &&/*����������������*/
       (true == nv_get_upgrade_flag())/*�����ļ���Ч*/
       )
    {
        ret = bsp_nvm_upgrade();
        if(ret)
        {
            nv_mntn_record("upgrade faided! 0x%x\n", ret);
            nv_debug(NV_FUN_KERNEL_INIT,3,ret,0,0);
            goto out;
        }
        else
        {
            nv_mntn_record("upgrade success!\n");
        }

        /*��ȡNV�Թ�������*/
        ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL,(u8*)(&(g_nv_ctrl.nv_self_ctrl)),sizeof(NV_SELF_CTRL_STRU));
        if(ret)
        {
            g_nv_ctrl.nv_self_ctrl.ulResumeMode = NV_MODE_USER;
            nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_DRV_SELF_CTRL,ret);
        }
    }
    else
    {
        /*��ȡNV�Թ�������*/
        ret = bsp_nvm_read(NV_ID_DRV_SELF_CTRL,(u8*)(&(g_nv_ctrl.nv_self_ctrl)),sizeof(NV_SELF_CTRL_STRU));
        if(ret)
        {
            g_nv_ctrl.nv_self_ctrl.ulResumeMode = NV_MODE_USER;
            nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_DRV_SELF_CTRL,ret);
        }

        /*���¼�����������*/
        ret = bsp_nvm_reload();
        if(ret)
        {
            nv_debug(NV_FUN_KERNEL_INIT,4,ret,0,0);
            goto out;
        }
        else
        {
            nv_printf("reload success!\n");
        }
    }

    /*��ʼ��˫��ʹ�õ�����*/
    nv_flushListInit();

    ret = bsp_nvm_buf_init();
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,10,ret,0,0);
        goto out;
    }

    /*�ó�ʼ��״̬ΪOK*/
    ddr_info->acore_init_state = NV_INIT_OK;
    nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, (u32)NV_GLOBAL_INFO_SIZE);

    /*��֤��������������д��*/
    nv_file_flag_check();

    INIT_LIST_HEAD(&g_nv_ctrl.stList);
/*lint -save -e740*/
    ret = (u32)osl_task_init("drv_nv",15,1024,(OSL_TASK_FUNC)bsp_nvm_icc_task,NULL,(OSL_TASK_ID*)&g_nv_ctrl.task_id);
    if(ret)
    {
        nv_mntn_record("[%s]:nv task init err! ret :0x%x\n",__func__,ret);
        goto out;
    }
/*lint -restore +e740*/
    ret = nv_icc_chan_init(NV_RECV_FUNC_AC);
    if(ret)
    {
        nv_debug(NV_FUN_KERNEL_INIT,5,ret,0,0);
        goto out;
    }

    ret = nv_msg_init();
    if (ret) {
        nv_debug(NV_FUN_KERNEL_INIT,6,ret,0,0);
        goto out;
    }

    /*to do:nv id use macro define*/
    ret = bsp_nvm_read(NV_ID_MSP_FLASH_LESS_MID_THRED,(u8*)(&(g_nv_ctrl.mid_prio)),sizeof(u32));
    if(ret)
    {
        g_nv_ctrl.mid_prio = 20;
        nv_printf("read 0x%x fail,use default value! ret :0x%x\n",NV_ID_MSP_FLASH_LESS_MID_THRED,ret);
    }

    nv_mntn_record("Balong nv init ok!\n");

//    nv_show_ddr_info();

    return NV_OK;

out:
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    ddr_info->acore_init_state = NV_INIT_FAIL;
    nv_help(NV_FUN_KERNEL_INIT);
    nv_show_ddr_info();
    return -1;
}

/*lint -save -e529*/
static void bsp_nvm_exit(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    /*�ػ�д����*/
    (void)bsp_nvm_flush();
    /*�����־*/
    memset(ddr_info,0,sizeof(struct nv_global_ddr_info_stru));
}
/*lint -restore +e529*/


u32 nvm_read_rand(u32 nvid)
{
    u32 ret;
    u8* tempdata;
    u32 i= 0;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};

    ret = nv_search_byid(nvid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
    if(NV_OK != ret)
    {
        return ret;
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV,"[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);

    tempdata = (u8*)nv_malloc((u32)(ref_info.nv_len) +1);
    if(NULL == tempdata)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    ret = bsp_nvm_read(nvid,tempdata,ref_info.nv_len);
    if(NV_OK != ret)
    {
        nv_free(tempdata);
        return BSP_ERR_NV_READ_DATA_FAIL;
    }

    for(i=0;i<ref_info.nv_len;i++)
    {
        if((i%32) == 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_NV, "\n");
        }
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV, "%02x ",(u8)(*(tempdata+i)));
    }
    nv_free(tempdata);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_NV,"\n\n");
    return 0;
}


u32 nvm_read_randex(u32 nvid,u32 modem_id)
{
	u32 ret;    u8* tempdata;    u32 i= 0;
	struct nv_ref_data_info_stru ref_info = {0};
	struct nv_file_list_info_stru file_info = {0};

	ret = nv_search_byid(nvid, (u8*)NV_GLOBAL_CTRL_INFO_ADDR,&ref_info,&file_info);
	if(NV_OK != ret)
	{
		return ret;
	}
	if(ref_info.nv_len == 0)
	{
		return NV_ERROR;
	}

	nv_printf("[0x%x]:len 0x%x,off 0x%x,file id %d\n",nvid,ref_info.nv_len,ref_info.nv_off,ref_info.file_id);
	nv_printf("[0x%x]:dsda 0x%x\n",nvid,ref_info.modem_num);

	tempdata = (u8*)nv_malloc((u32)(ref_info.nv_len) +1);
	if(NULL == tempdata)
	{
		return BSP_ERR_NV_MALLOC_FAIL;
	}
	ret = bsp_nvm_dcread(modem_id,nvid,tempdata,ref_info.nv_len);
	if(NV_OK != ret)
	{
		nv_free(tempdata);
		return BSP_ERR_NV_READ_DATA_FAIL;
	}

	for(i=0;i<ref_info.nv_len;i++)
	{
		if((i%32) == 0)
		{
			printf("\n");
		}
		printf("%02x ",(u8)(*(tempdata+i)));
	}

	printf("\n\n");
	nv_free(tempdata);

	return 0;

}

/*lint -save -e537*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/printk.h>
#include "mdrv_rfile_common.h"
//#include <drv_sync.h>
/*lint -restore +e537*/
/*lint -save -e537*/
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
/*lint -restore +e537*/
/*lint -save -e26*/
static ssize_t Modem_NvRead(struct file *file,char __user *buf, size_t len, loff_t *ppos)
{
    return len;
}
/*lint -restore +e26*/
static ssize_t Modem_NvWrite(struct file *file,const char __user *buf, size_t len, loff_t *ppos)
{
    signed int ret;
    ret = nv_modify_upgrade_flag(true);
    if(ret)
        return ret;
    nv_mntn_record("%s %s modify upgrade flag success !\n",__DATE__,__TIME__);
    return len;
}
static const struct file_operations g_ModemNv ={
    .owner    = THIS_MODULE,
    .read     = Modem_NvRead,
    .write    = Modem_NvWrite,
};
/*lint -save -e745*/
int modemNv_ProcInit(void)
{
    if(NULL == proc_create("ModemNv", 0660, NULL, &g_ModemNv))
    {
        return -1;
    }
    return 0;
}

/*lint -restore +e745*/
void modem_nv_delay(void)
{
    u32  blk_size;
    char *blk_label;
    int i, ret = -1;

    /*��ȴ�ʱ��10s*/
    for(i=0;i<10;i++)
    {
        nv_printf("modem nv wait for nv block device %d s\n",i);

        blk_label = (char*)NV_BACK_SEC_NAME;
        ret = bsp_blk_size(blk_label, &blk_size);
        if (ret) {
            nv_taskdelay(1000);
            nv_printf("get block device %s fail\n", blk_label);
            continue;
        }

        blk_label = (char*)NV_DLOAD_SEC_NAME;
        ret = bsp_blk_size(blk_label, &blk_size);
        if (ret) {
            nv_taskdelay(1000);
            nv_printf("get block device %s fail\n", blk_label);
            continue;
        }

        blk_label = (char*)NV_SYS_SEC_NAME;
        ret = bsp_blk_size(blk_label, &blk_size);
        if (ret) {
            nv_taskdelay(1000);
            nv_printf("get block device %s fail\n", blk_label);
            continue;
        }

        blk_label = (char*)NV_DEF_SEC_NAME;
        ret = bsp_blk_size(blk_label, &blk_size);
        if (ret) {
            nv_taskdelay(1000);
            nv_printf("get block device %s fail\n", blk_label);
            continue;
        }
        return;
    }
}


static int  modem_nv_probe(struct platform_device *dev)
{
    int ret = -1;

    g_nv_ctrl.pmState = NV_WAKEUP_STATE;
    g_nv_ctrl.opState = NV_IDLE_STATE;

    ret = nv_emmc_area_name_init();
    if(ret)
    {
        return ret;
    }
    modem_nv_delay();

	/* coverity[Event check_return] *//* coverity[Event unchecked_value] */
    if(mdrv_file_access("/modem_log/modem_nv/",0))
        (void)mdrv_file_mkdir("/modem_log/modem_nv/");


    ret = bsp_nvm_kernel_init();

    ret |= modemNv_ProcInit();

    return ret;
}

#define NV_SHUTDOWN_STATE   NV_BOOT_INIT_OK
static void modem_nv_shutdown(struct platform_device *dev)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    printk("%s shutdown start %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n",__func__);

    /*read only*/
    ddr_info->acore_init_state = NV_SHUTDOWN_STATE;
    ddr_info->ccore_init_state = NV_SHUTDOWN_STATE;
    ddr_info->mcore_init_state = NV_SHUTDOWN_STATE;

}
static s32 modem_nv_suspend(struct device *dev)
{
    static int count = 0;
    if(g_nv_ctrl.opState == NV_OPS_STATE)
    {
        printk(KERN_ERR"%s Modem nv in doing !\n",__func__);
        return -1;
    }
    g_nv_ctrl.pmState = NV_SLEEP_STATE;
    printk(KERN_ERR"Modem nv enter suspend! %d times\n",++count);
    return 0;
}
static s32 modem_nv_resume(struct device *dev)
{
    static int count;
    g_nv_ctrl.pmState = NV_WAKEUP_STATE;
    if(NV_OPS_STATE== g_nv_ctrl.opState)
    {
        printk(KERN_ERR"%s need to enter task proc!\n",__func__);
        osl_sem_up(&g_nv_ctrl.suspend_sem);
    }
    printk(KERN_ERR"Modem nv enter resume! %d times\n",++count);
    return 0;
}
static const struct dev_pm_ops modem_nv_pm_ops ={
	.suspend = modem_nv_suspend,
    .resume  = modem_nv_resume,
};

#define MODEM_NV_PM_OPS (&modem_nv_pm_ops)

static struct platform_driver modem_nv_drv = {
    .shutdown   = modem_nv_shutdown,
    .driver     = {
        .name     = "modem_nv",
        .owner    = THIS_MODULE,
        .pm       = MODEM_NV_PM_OPS,
    },
};


static struct platform_device modem_nv_device = {
    .name = "modem_nv",
    .id = 0,
    .dev = {
    .init_name = "modem_nv",
    },
};
extern void dump_show_stack(void);

int  modem_nv_init(void)
{
    struct platform_device *dev = NULL;
    int ret;
    if(0 == g_nv_ctrl.initStatus)
    {
        g_nv_ctrl.initStatus = 1;
    }
    else
    {
        dump_show_stack();
    }

    ret = modem_nv_probe(dev);

    return ret;
}
/*�����ڳ�ʼ��nv�豸*/
int nv_init_dev(void)
{
    u32 ret = 0;
    ret = platform_device_register(&modem_nv_device);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_nv_device fail !\n");
        return -1;
    }

    ret = platform_driver_register(&modem_nv_drv);
    if(ret)
    {
        printk(KERN_ERR"platform_device_register modem_nv_drv fail !\n");
        platform_device_unregister(&modem_nv_device);
        return -1;
    }
    return NV_OK;
}
void  modem_nv_exit(void)
{
    bsp_nvm_exit();
    platform_device_unregister(&modem_nv_device);
    platform_driver_unregister(&modem_nv_drv);
}

device_initcall(nv_init_dev);
//module_exit(modem_nv_exit);


EXPORT_SYMBOL(bsp_nvm_backup);
EXPORT_SYMBOL(bsp_nvm_dcread);
EXPORT_SYMBOL(bsp_nvm_kernel_init);
EXPORT_SYMBOL(bsp_nvm_update_default);
EXPORT_SYMBOL(bsp_nvm_revert_default);
EXPORT_SYMBOL(bsp_nvm_dcreadpart);
EXPORT_SYMBOL(bsp_nvm_get_len);
EXPORT_SYMBOL(bsp_nvm_dcwrite);
EXPORT_SYMBOL(bsp_nvm_flush);
EXPORT_SYMBOL(bsp_nvm_reload);
EXPORT_SYMBOL(nvm_read_rand);
EXPORT_SYMBOL(nvm_read_randex);
EXPORT_SYMBOL(bsp_nvm_dcread_direct);
EXPORT_SYMBOL(bsp_nvm_dcwrite_direct);
EXPORT_SYMBOL(bsp_nvm_auth_dcread);
EXPORT_SYMBOL(bsp_nvm_auth_dcwrite);
EXPORT_SYMBOL(bsp_nvm_dcwritepart);
EXPORT_SYMBOL(bsp_nvm_get_nvidlist);
EXPORT_SYMBOL(bsp_nvm_authgetlen);
EXPORT_SYMBOL(bsp_nvm_xml_decode);

/*lint -restore*/




