


/*lint -save -e322 -e7 -e537*/
#include <stdarg.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/clk.h>
#include "mdrv_rfile_common.h"
#include <bsp_hardtimer.h>
#include <product_nv_id.h>
#include <product_nv_def.h>
#include <mdrv.h>
#include "nv_comm.h"
#include "nv_file.h"
#include "nv_ctrl.h"
#include "nv_xml_dec.h"
#include "nv_debug.h"
#include "nv_index.h"
#include "nv_crc.h"
#include "nv_partition_img.h"
#include "nv_partition_bakup.h"
#include "bsp_dump.h"
#include "NVIM_ResumeId.h"
#include "RfNvId.h"
#include "nv_debug.h"
#include "nv_msg.h"
/*lint -restore +e322 +e7 +e537*/

/*lint -save -e438 -e530 -e713 -e830 -e529*/
struct nv_global_ctrl_info_stru  g_nv_ctrl = {};

u16 g_NvSysList[] = { NV_ID_DRV_IMEI,
                      NV_ID_DRV_NV_FACTORY_INFO_I,
                      NV_ID_DRV_NV_DRV_VERSION_REPLACE_I,
                      NV_ID_DRV_SEC_BOOT_ENABLE_FLAG,
                      en_NV_Item_XO_TEMP_SENSOR_TABLE,
                      en_NV_Item_PA_TEMP_SENSOR_TABLE,
                      NV_ID_DRV_SOCP_LOG_CFG,
                      en_NV_Item_RF_ANT_DETECT};


u32 nv_ipc_sem_take(u32 sem, u32 timeout)
{
    u32 start = 0;
    u32 end = 0;

    osl_sem_down(&g_nv_ctrl.rw_sem);
    start = bsp_get_slice_value();
    if(bsp_ipc_sem_take(sem, timeout))
    {
        nv_mntn_record("[0x%x] 0x%x take ipc sem fail\n", bsp_get_slice_value(), start);
        return BSP_ERR_NV_TIME_OUT_ERR;
    }
    end = bsp_get_slice_value();
    nv_debug_record_delta_time(NV_DEBUG_DELTA_GET_IPC, start, end);
    return NV_OK;
}

void nv_ipc_sem_give(u32 sem)
{
    (void)bsp_ipc_sem_give(sem);
    osl_sem_up(&g_nv_ctrl.rw_sem);
    return;
}


/*����flag��־�ļ�,����д��֮ǰ����*/
void nv_create_flag_file(const s8* path)
{
    FILE* fp = NULL;

    if(!mdrv_file_access(path,0))
        return;
    fp = mdrv_file_open((char*)path, (char*)NV_FILE_WRITE);

    if(fp){
        mdrv_file_close(fp);
        return;
    }
    else
        return;
}

/*ɾ��flag��־�ļ�������д��֮�����*/
void nv_delete_flag_file(const s8* path)
{
    if(mdrv_file_access((char*)path,0))
        return;
    else
        mdrv_file_remove((char*)path);
}

/*�жϱ�־�ļ��Ƿ���� true :���ڣ� false :������*/
bool nv_flag_file_isExist(const s8* path)
{
    return (mdrv_file_access((char*)path,0) == 0)?true:false;
}

/*����֮�������������ϵͳ����flag�ļ����ڣ�����Ҫ����������д���Ӧ������*/
void nv_file_flag_check(void)
{
    if( !mdrv_file_access((char*)NV_BACK_FLAG_PATH,0)){
        nv_mntn_record("%s %s :last time [back file] write abnomal,rewrite !\n",__DATE__,__TIME__);
        (void)bsp_nvm_backup(NV_FLAG_NEED_CRC);
    }

    if( !mdrv_file_access((char*)NV_SYS_FLAG_PATH,0)){
        nv_mntn_record("%s %s :last time [sys file] write abnomal,rewrite !\n",__DATE__,__TIME__);
        (void)bsp_nvm_flushSys(NV_ERROR);
    }

    if( !mdrv_file_access((char*)NV_IMG_FLAG_PATH,0)){
        nv_mntn_record("%s %s :last time [img file] write abnomal,rewrite !\n",__DATE__,__TIME__);
        (void)nv_img_flush_all();
    }
}

/*�������쳣����½�����д���������*/
u32 nv_data_writeback(void)
{
    u32 ret;

    ret = nv_img_flush_all();
    if(ret)
    {
        nv_error_printf("write back to [img] fail! ret :0x%x\n",ret);
        return ret;
    }

    ret = bsp_nvm_backup(NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_error_printf("write back to [back] fail! ret :0x%x\n",ret);
        return ret;
    }

    ret = bsp_nvm_flushSys(NV_ERROR);
    if(ret)
    {
        nv_error_printf("write back to [system] fail! ret :0x%x\n",ret);
        return ret;
    }

    return NV_OK;
}

/*���������ݴӹ��������ָ�*/
u32 nv_load_err_proc(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u32 ret = NV_ERROR;
    FILE* fp = NULL;
    u32 datalen = 0;
    unsigned long nvflag = 0;

    nv_mntn_record("load error proc ...%s %s \n",__DATE__,__TIME__);

    nv_spin_lock(nvflag, IPC_SEM_NV);
    ddr_info->acore_init_state = NV_KERNEL_INIT_DOING;
    nv_spin_unlock(nvflag, IPC_SEM_NV);
    /*�������������������г��������Ľ����ָ�������ֱ�ӷ���ʧ��*/
    if(nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        nv_mntn_record("%s ,%s has no file\n",__func__,NV_DEFAULT_PATH);
        return BSP_ERR_NV_NO_FILE;
    }
    if(nv_file_access((s8*)NV_DLOAD_PATH,0))
    {
        nv_mntn_record("%s ,%s has no file\n",__func__,NV_DLOAD_PATH);
        return BSP_ERR_NV_NO_FILE;
    }

    nv_mntn_record("%s %s load from %s ...\n",__DATE__,__TIME__,NV_DLOAD_PATH);
    fp = nv_file_open((s8*)NV_DLOAD_PATH,(s8*)NV_FILE_READ);
    if(!fp)
    {
        nv_error_printf("open %s failed \n",NV_DLOAD_PATH);
        return BSP_ERR_NV_NO_FILE;
    }

    ret = nv_read_from_file(fp,(u8*)NV_GLOBAL_CTRL_INFO_ADDR,&datalen, NV_FILE_DLOAD);
    nv_file_close(fp);
    if(ret)
    {
        return ret;
    }
    if(false == nv_dload_file_check())
    {
        return BSP_ERR_NV_DELOAD_CHECK_ERR;
    }

    ret = bsp_nvm_xml_decode();
    if(ret)
    {
        return ret;
    }
    /*������������������������ݴӳ��������ָ�*/
    if(!nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        ret = nv_revertEx((s8*)NV_DEFAULT_PATH);
        if(ret)
        {
            return ret;
        }
    }

    (void)nv_crc_make_ddr();

    ret = nv_data_writeback();
    if(ret)
    {
        return ret;
    }

    nv_spin_lock(nvflag, IPC_SEM_NV);
    ddr_info->acore_init_state = NV_INIT_OK;
    nv_spin_unlock(nvflag, IPC_SEM_NV);
    nv_flush_cache((u8*)NV_GLOBAL_START_ADDR, SHM_MEM_NV_SIZE);

    nv_mntn_record("load error proc OK ...%s %s \n",__DATE__,__TIME__);
    return NV_OK;
}

/*****************************************************************************
 �� �� ��  : nv_get_bin_file_len
 ��������  : ����nv.bin�ļ��Ĵ�С
 �������  : fp:��������ļ�
 �������  : ��
 �� �� ֵ  : �ļ���С
*****************************************************************************/
bool nv_check_file_validity(s8 * filePath, s8 *flagPath)
{
    u32 ret;

    /*�ļ�������*/
    if(nv_file_access((s8*)filePath,0))
    {
        nv_mntn_record("%s  in not exist !\n",filePath);
        return false;
    }
    /*��δд����ɵı�־ */
    if(true == nv_flag_file_isExist((s8*)flagPath))
    {
        nv_mntn_record("%s  last time write abornormal !\n",filePath);
        return false;
    }

    /*imei�ż��*/
    ret = nv_imei_data_comp((s8*)filePath);
    if(ret)
    {
        nv_mntn_record("%s imei compare with factory data is not same ret :0x%x!\n",filePath,ret);
        return false;
    }

    return true;
}


/*��Ҫ֧�����������ı��ݻָ���ָ����������*/
u32 nv_upgrade_revert_proc(void)
{
    u32 ret;

    /*��鹤�������ݵ���Ч��*/
    if(true == nv_check_file_validity((s8 *)NV_IMG_PATH, (s8 *)NV_IMG_FLAG_PATH))
    {
        ret = nv_revertEx((s8*)NV_IMG_PATH);
        if(ret)
        {
            nv_mntn_record("revert from %s fail,goto next err proc ret:0x%x!\n",NV_IMG_PATH,ret);
            goto revert_backup;
        }

        /*�ӹ������ָ����֮�󣬱��ݹ��������ݵ����ݷ���*/
        ret = nv_copy_img2backup();
        if(ret)/*�����쳣ֱ���˳�*/
        {
            nv_mntn_record("copy img to backup fail,ret :0x%x\n",ret);
            return ret;
        }
        return NV_OK;
    }

revert_backup:
    /*��鱸�������ݵ���Ч��*/
    if(true == nv_check_file_validity((s8 *)NV_BACK_PATH, (s8 *)NV_BACK_FLAG_PATH))
    {
        ret = nv_revertEx((s8*)NV_BACK_PATH);
        if(ret)
        {
            nv_mntn_record("revert from %s fail,goto next err proc ret:0x%x!\n",NV_BACK_PATH,ret);
            goto revert_factory;
        }

        return NV_OK;
    }

revert_factory:
    /*��������������ֱ�Ӵӳ��������ָ�*/
    if(!nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        ret = nv_revertEx((s8*)NV_DEFAULT_PATH);
        if(ret)
        {
            nv_mntn_record("revert from %s fail,return err! ret:0x%x\n",NV_DEFAULT_PATH,ret);
            return ret;
        }

    }

    /*��Ƭ�汾�����ݻָ���ֱ�ӷ���ok*/
    return NV_OK;
}
bool nv_check_update_default_right(void)
{
    /*�����ڣ���ֱ�ӷ���true*/
    if(nv_file_access((s8*)NV_DEFAULT_PATH,0))
    {
        return true;
    }
    /*��������д����ļ�*/
    if(!mdrv_file_access((char*)NV_FACTORY_RIGHT_PATH,0))
    {
        return true;
    }

    return false;
}

void nv_delete_update_default_right(void)
{
    if(!mdrv_file_access((char*)NV_FACTORY_RIGHT_PATH,0))
    {
        (void)mdrv_file_remove((char*)NV_FACTORY_RIGHT_PATH);
    }
}

/*
 * pick up the base info from the major info,then reg in base_info
 */
u32 nv_init_file_info(u8* major_info,u8* base_info)
{
    u32 i;
    struct nv_ctrl_file_info_stru * ctrl_file = (struct nv_ctrl_file_info_stru*)major_info;
    struct nv_global_ddr_info_stru* ddr_info  = (struct nv_global_ddr_info_stru*)base_info;
    struct nv_file_list_info_stru * file_info = (struct nv_file_list_info_stru *)((u8*)ctrl_file+NV_GLOBAL_CTRL_INFO_SIZE);

    ddr_info->file_num = ctrl_file->file_num;   /*reg file num*/
    ddr_info->file_len = ctrl_file->ctrl_size;  /*reg ctrl file size,then add file size*/

    for(i = 0;i<ctrl_file->file_num;i++)
    {
        /*check file id*/
        if((i+1) != file_info->file_id)
        {
            nv_printf("file id  %d error ,i: %d\n",file_info->file_id,i);
            return BSP_ERR_NV_FILE_ERROR;
        }
        ddr_info->file_info[i].file_id = file_info->file_id;
        ddr_info->file_info[i].size    = file_info->file_size;
        ddr_info->file_info[i].offset  = ddr_info->file_len;

        ddr_info->file_len            += file_info->file_size;

        file_info++;
    }
    if(ddr_info->file_len > NV_MAX_FILE_SIZE)
    {
        nv_mntn_record("[%s]: file len error 0x%x\n",__FUNCTION__,ddr_info->file_len);
        return BSP_ERR_NV_FILE_ERROR;
    }
    return NV_OK;

}

void nv_modify_print_sw(u32 arg)
{
    g_nv_ctrl.debug_sw = arg;
}

s32 nv_modify_pm_sw(s32 arg)
{
    g_nv_ctrl.pmSw = (bool)arg;
    return 0;
}
bool nv_isSysNv(u16 itemid)
{
    /*lint -save -e958*/
    u32 i;
    /*lint -restore*/
    if(itemid >= NV_ID_SYS_MIN_ID && itemid <= NV_ID_SYS_MAX_ID)
        return true;

    for(i = 0;i<sizeof(g_NvSysList)/sizeof(g_NvSysList[0]);i++)
    {
        if(itemid == g_NvSysList[i])
            return true;
    }
    return false;

}

/*
 * get nv read right,check the nv init state or upgrade state to read nv,
 * A core may read nv data after kernel init ,C core read nv data must behine the phase of
 *       acore kernel init or acore init ok
 */
bool nv_read_right(u32 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info= (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    if( NV_KERNEL_INIT_DOING > ddr_info->acore_init_state)
    {
        return false;
    }
    return true;
}

bool nv_write_right(u32 itemid)
{
    struct nv_global_ddr_info_stru* ddr_info= (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    if(NV_INIT_OK != ddr_info->acore_init_state)
    {
        return false;
    }

    /*TMODE CHECK*/

    return true;
}
/*
 * get file len
 * return : file len
 */
u32 nv_get_file_len(FILE* fp)
{
    s32 ret = -1;
    u32 seek = 0;

    ret = nv_file_seek(fp,0,SEEK_END);
    if(ret)
    {
        goto out;
    }

    seek = (u32)nv_file_ftell(fp);

    ret = nv_file_seek(fp,0,SEEK_SET);
    if(ret)
    {
        goto out;
    }

    return seek;

out:
    nv_printf("seek file fail\n");
    return NV_ERROR;
}

/*
 * check the dload file validity
 *
 */
bool nv_dload_file_check(void )
{
    u32 i;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_file_list_info_stru* file_info = (struct nv_file_list_info_stru*)(NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE);
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)(NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);

    struct nv_ref_data_info_stru* ref_info_next = ref_info+1;

    /*check ref list id sort */
    for(i = 0;i<ctrl_info->ref_count-1;i++)
    {
        if(ref_info->itemid >=ref_info_next->itemid)
        {
            nv_printf("i %d,itemid 0x%x,itemid_next 0x%x\n",i,ref_info->itemid,ref_info_next->itemid);
            return false;
        }
        ref_info ++;
        ref_info_next ++;
    }

    /*check file id sort*/
    for(i = 0;i<ctrl_info->file_num;i++)
    {
        if(file_info->file_id != (i+1))
        {
            nv_printf("i %d,file_id %d",i,file_info->file_id);
            return false;
        }
        file_info ++;
    }


    return true;
}
/*
 * xml decode
 * path     :xml path
 * map_path :xml map file path
 */
u32 nv_xml_decode(s8* path,s8* map_path,u32 card_type)
{
    u32 ret = NV_ERROR;
    FILE* fp = NULL;

    nv_debug(NV_FUN_XML_DECODE,0,0,0,0);
    fp = nv_file_open(path,(s8*)NV_FILE_READ);
    if(NULL == fp)
    {
        ret = BSP_ERR_NV_NO_FILE;
        nv_debug(NV_FUN_XML_DECODE,1,ret,0,0);
        return ret;
    }
    nv_mntn_record("enter to decode  %s \n",path);
    ret = xml_decode_main(fp,map_path,card_type);
    nv_file_close(fp);
    fp = NULL;
    if(ret)
    {
        nv_debug(NV_FUN_XML_DECODE,2,ret,0,0);
        goto xml_decode_err;
    }

    return NV_OK;
xml_decode_err:
    nv_mntn_record("file path :%s card type %d\n",path,card_type);
    nv_help(NV_FUN_XML_DECODE);
    return ret;
}


u32 nv_read_file(s8* path, u32 offset, u8* ptr, u32* len)
{
    u32 ret     = NV_ERROR;
    FILE* fp    = NULL;

    fp = nv_file_open(path,(s8*)NV_FILE_READ);
    if(!fp)
    {
        nv_debug(NV_FUN_READ_FILE,1,0,0,0);
        return BSP_ERR_NV_READ_FILE_FAIL;
    }

    nv_file_seek(fp,offset,SEEK_SET);
    ret = (u32)nv_file_read((u8*)ptr,1,(*len),fp);
    nv_file_close(fp);
    if(ret != (*len))
    {
        nv_debug(NV_FUN_READ_FILE,2,ret,*len,0);
        nv_mntn_record("[%s]:  ret 0x%x, datalen 0x%x\n",__func__,ret,*len);
        return BSP_ERR_NV_READ_FILE_FAIL;
    }

    return NV_OK;
}

/*
 * read file to ddr,include download,backup,workaround,default
 */

u32 nv_read_from_file(FILE* fp,u8* ptr,u32* datalen, u32 type)
{
    u32 ret = NV_ERROR;
    struct nv_global_ddr_info_stru * ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    /* coverity[var_decl] */
    struct nv_ctrl_file_info_stru ctrl_info;
    u32 len = 0;

    *datalen = nv_get_file_len(fp);

    if((*datalen > NV_MAX_FILE_SIZE)||(*datalen == 0))
    {
        nv_mntn_record("[%s]:  datalen 0x%x\n",__func__,*datalen);
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }
    /*add file head magic num check */
    ret = (u32)nv_file_read((u8*)&ctrl_info,1,sizeof(ctrl_info),fp);
    if(ret != sizeof(ctrl_info))
    {
        nv_mntn_record("[%s]:  ret 0x%x\n",__func__,ret);
        goto out;
    }
    /* coverity[uninit_use] */
    if(ctrl_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        /*add file head mntn info*/
        nv_mntn_record("[%s]:  ctrl_info.magicnum 0x%x\n",__func__,ctrl_info.magicnum);
		ret = BSP_ERR_NV_HEAD_MAGIC_ERR;
        goto out;
    }
    nv_file_seek(fp,0,SEEK_SET);

    ret = (u32)nv_file_read((u8*)ptr,1,(*datalen),fp);
    if(ret != (*datalen))
    {
        nv_mntn_record("[%s]:  ret 0x%x, datalen 0x%x\n",__func__,ret,*datalen);
        goto out;
    }

    ret = nv_init_file_info((u8*)NV_GLOBAL_CTRL_INFO_ADDR,(u8*)NV_GLOBAL_INFO_ADDR);
    if(ret)
    {
        nv_mntn_record("[%s]:  ret 0x%x\n",__func__,ret);
        goto out;
    }

    len = ddr_info->file_len;

    if(*datalen != len)
    {
        nv_mntn_record("[%s]:%d,ddr len:0x%x datalen:0x%x\n",__func__,__LINE__,len, *datalen);
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }
    nv_flush_cache((void*)NV_GLOBAL_CTRL_INFO_ADDR,(u32)NV_MAX_FILE_SIZE);
    return NV_OK;
out:
    nv_mntn_record("ret : 0x%x,datalen 0x%x\n",ret,*datalen);
    return NV_ERROR;
}

u32 nv_revert_item(nv_revert_file_s * file, u32 itemid, u32 mkcrc, u8* temp_buff, u32 buff_size)
{
    u32 ret;
    FILE* fp = file->fp;
    nv_global_info_s *file_global   = (nv_global_info_s*)file->global_info;
    /* coverity[tainted_data_downcast] *//* coverity[var_assign_var] */
    nv_ctrl_info_s   *file_ctrl     = (nv_ctrl_info_s*)file->ctrl_data;
    nv_item_info_s    file_item;
    nv_file_info_s    file_file;
    nv_ctrl_info_s   *mem_ctrl      = (nv_ctrl_info_s*)NV_GLOBAL_CTRL_INFO_ADDR;
    nv_item_info_s    mem_item;
    nv_file_info_s    mem_file;
    u32 file_offset;
    u8* item_base;
    u8* mdm_base;
    u32 item_size;
    u32 mdm_size;
    u32 rd_len;
    u32 i;
    u8* crc_data;
    u32 *pcrc;
    u32 mdm_num;

    /* coverity[tainted_data] */
    ret = nv_search_byid(itemid, (u8*)file_ctrl,&file_item,&file_file);
    if(ret)
    {
        /* �ļ�������������Ӧ��NV��������������������ش��� */
        g_nv_ctrl.revert_search_err++;
        nv_debug(NV_FUN_REVERT_DATA,10,ret,itemid,0);
//        nv_printf("nvid 0x%x is not exist in file, skip it!\n", itemid);
        return NV_OK;
    }

    /*search nv from global ddr data*/
    ret = nv_search_byid(itemid,(u8*)mem_ctrl,&mem_item,&mem_file);
    if(ret)
    {
        /* �ڴ�������������Ӧ��NV�������쳣��������ش��� */
        g_nv_ctrl.revert_search_err++;
        nv_debug(NV_FUN_REVERT_DATA,11,ret,itemid,0);
        nv_printf("nvid 0x%x is not exist in memory, skip it!\n", itemid);
        return BSP_ERR_NV_NO_THIS_ID;
    }

    if((mem_item.nv_len != file_item.nv_len))
    {
        nv_mntn_record("nv item len err, skip it! itemid :0x%x,new len:0x%x, old len :0x%x\n",\
            itemid,mem_item.nv_len,file_item.nv_len);
        g_nv_ctrl.revert_len_err++;
        nv_debug(NV_FUN_REVERT_DATA,12,itemid,mem_item.nv_len,file_item.nv_len);
        return BSP_ERR_NV_ITEM_LEN_ERR;
    }

    file_offset = nv_get_item_fileoffset(&file_item, file_global);
    item_base   = nv_get_item_base(&mem_item);
    item_size   = nv_get_item_len(&mem_item, NULL);
    mdm_size    = nv_get_item_mdmlen(&mem_item, NULL);
    mdm_num     = file_item.modem_num < mem_item.modem_num?file_item.modem_num:mem_item.modem_num;
    if(item_size > buff_size)
    {
        g_nv_ctrl.revert_len_err++;
        nv_debug(NV_FUN_REVERT_DATA,13,itemid,item_size,buff_size);
        nv_printf("nv length is too large, skip it! nvid:0x%x nvsize:0x%x, buffsize:0x%x\n",
                    itemid, item_size, buff_size);
        return BSP_ERR_NV_OVER_MEM_ERR;
    }

    for(i=1; i<=mdm_num; i++)
    {
        u32 mdm_len;

        file_offset = nv_get_item_filemdmoffset(&file_item, i, file_global, file_ctrl);
        mdm_len    = mem_item.nv_len;
        if(NV_MODEM_CRC_CHECK_YES)
        {
            mdm_base = temp_buff + (i - NV_USIMM_CARD_1)*(mdm_len+4);
        }
        else
        {
            mdm_base = temp_buff + (i - NV_USIMM_CARD_1)*(mdm_len);
        }

        nv_file_seek(fp,(s32)file_offset,SEEK_SET);
        rd_len = (u32)nv_file_read(mdm_base, 1, mdm_len, fp);
        if(rd_len != mdm_len)
        {
            nv_printf("read nv %d %d from file , len error, rd_len=0x%x item_size=0x%x!\n", itemid, i, rd_len, mdm_len);
            g_nv_ctrl.revert_len_err++;
            nv_debug(NV_FUN_REVERT_DATA,14,ret,itemid,0);
            return BSP_ERR_NV_READ_FILE_FAIL;
        }
    }

    /* nvid crc */
    if(mkcrc && (NV_ITEM_CRC_CHECK_YES))
    {
        pcrc      = (u32*)(temp_buff + item_size - 4);
        *pcrc     = nv_cal_crc32(temp_buff, (item_size - 4));

        nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        memcpy((void*)item_base, (void*)temp_buff, item_size);
        nv_flush_cache(item_base, item_size);
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
    }
    else if(mkcrc && (NV_MODEM_CRC_CHECK_YES))
    {
        for(i=1; i<=mdm_num; i++)
        {
            mdm_base  = nv_get_item_mdmbase(&mem_item, i, NULL);
            crc_data  = temp_buff + mdm_size*(i-1);

            pcrc      = (u32*)(crc_data + mdm_size - 4);
            *pcrc     = nv_cal_crc32(crc_data, (mdm_size - 4));

            nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
            memcpy((void*)mdm_base, (void*)crc_data, mdm_size);
            nv_flush_cache(mdm_base, mdm_size);
            nv_ipc_sem_give(IPC_SEM_NV_CRC);
        }
    }
    else
    {
        nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        memcpy((void*)item_base, (void*)temp_buff, item_size);
        nv_flush_cache(item_base, item_size);
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
    }

    return NV_OK;
}

/*
 * revert nv data,suport double sim card
 */
u32 nv_revert_data(s8* path,const u16* revert_data,u32 len, u32 crc_mark)
{
    FILE* fp            = NULL;
    u32 ret             = NV_ERROR;
    u32 i               = 0;
    u32 rd_len          = 0;        /*read file len*/
    u8* file_ctrl_data  = NULL;
    u8* temp_buff       = NULL;           /*single nv data ,max len 2048byte*/
    u32 buff_size       = 0;
    nv_ctrl_info_s      file_ctrl = {0};   /*bak file ctrl file head*/
    nv_global_info_s *  file_global_info   = NULL;
    u16* pidlist  = (u16*)revert_data;
    nv_item_info_s*     item_tbl;

    nv_debug(NV_FUN_REVERT_DATA,0,0,0,0);
    fp = nv_file_open(path,(s8*)NV_FILE_READ);
    if(NULL == fp)
    {
        nv_printf("nv_file_open failed!\n");
        nv_debug(NV_FUN_REVERT_DATA,1,0,0,0);
        return BSP_ERR_NV_NO_FILE;
    }

    rd_len = (u32)nv_file_read((u8*)(&file_ctrl),1,sizeof(file_ctrl),fp);
    if(rd_len != sizeof(file_ctrl))
    {
        nv_printf("nv_file_read len error 0x%x 0x%x!\n", sizeof(file_ctrl), rd_len);
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_REVERT_DATA,2,(u32)(unsigned long)fp,rd_len,ret);
        goto close_file;
    }
    nv_file_seek(fp,0,SEEK_SET); /*jump to file head*/
    if(file_ctrl.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        nv_printf("file magic number is invalid 0x%x!\n", file_ctrl.magicnum);
        ret = BSP_ERR_NV_FILE_ERROR;
        nv_debug(NV_FUN_REVERT_DATA,3,0,0,0);
        goto close_file;
    }

    file_ctrl_data = (u8*)vmalloc(file_ctrl.ctrl_size+1);
    if(NULL == file_ctrl_data)
    {
        nv_printf("vmalloc failed!\n");
        ret = BSP_ERR_NV_MALLOC_FAIL;
        nv_debug(NV_FUN_REVERT_DATA,4,file_ctrl.ctrl_size,0,ret);
        goto close_file;
    }

    rd_len = (u32)nv_file_read(file_ctrl_data,1,file_ctrl.ctrl_size,fp);
    nv_file_seek(fp,0,SEEK_SET); /*jump to file head*/
    if(rd_len != file_ctrl.ctrl_size)
    {
        nv_printf("nv_file_read ctrl data len error 0x%x 0x%x!\n", file_ctrl.ctrl_size, rd_len);
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        nv_debug(NV_FUN_REVERT_DATA,5,file_ctrl.ctrl_size,rd_len,ret);
        goto free_pdata;
    }

    file_global_info = (nv_global_info_s*)vmalloc(sizeof(nv_global_info_s));
    if(!file_global_info)
    {
        nv_printf("vmalloc 2 failed!\n");
        nv_debug(NV_FUN_REVERT_DATA,6,0,0,ret);
        goto free_pdata;
    }
    ret = nv_init_file_info((u8*)file_ctrl_data,(u8*)file_global_info);
    if(ret)
    {
        nv_printf("init file failed 0x%x!\n", ret);
        ret = BSP_ERR_NV_MEM_INIT_FAIL;
        nv_debug(NV_FUN_REVERT_DATA,7,0,0,ret);
        goto free_pdata;
    }

    /* ��С�з��գ����ܲ��� */
    buff_size = 3*NV_MAX_UNIT_SIZE;
    temp_buff = (u8*)vmalloc(buff_size);
    if(temp_buff == NULL)
    {
        nv_printf("vmalloc 3 failed!\n");
        ret = BSP_ERR_NV_MALLOC_FAIL;
        nv_debug(NV_FUN_REVERT_DATA,8 , NV_MAX_UNIT_SIZE,0,ret);
        goto free_pdata;
    }

    /* ��������pidlistΪ0����ָ��ļ��е�����NV */
    if(NULL == pidlist)
    {
        nv_printf("file_ctrl.ref_count = 0x%x!\n", file_ctrl.ref_count);
        len      = file_ctrl.ref_count;
    }
    item_tbl = (nv_item_info_s*)((u8*)file_ctrl_data
                + NV_GLOBAL_CTRL_INFO_SIZE
                + NV_GLOBAL_FILE_ELEMENT_SIZE*file_ctrl.file_num);

    for(i = 0;i<len ;i++)
    {
        nv_revert_file_s revert_file;
        u32 itemid;

        if(NULL != pidlist)
        {
            itemid = pidlist[i];
        }
        else
        {
            itemid = item_tbl[i].itemid;
        }
        revert_file.fp = fp;
        revert_file.global_info = (u8*)file_global_info;
        revert_file.ctrl_data   = (u8*)file_ctrl_data;
        ret = nv_revert_item(&revert_file, itemid, crc_mark, temp_buff, buff_size);
        g_nv_ctrl.revert_count ++;
        if(ret)
        {
            nv_mntn_record("revert nvid failed, itemid :0x%x ret: 0x%x\n", itemid,ret);
            g_nv_ctrl.revert_len_err++;
            nv_debug(NV_FUN_REVERT_DATA,9,itemid, ret, crc_mark);
            continue;
        }
    }

    if(file_ctrl_data)  {vfree(file_ctrl_data);}
    if(temp_buff)       {vfree(temp_buff);}
    if(file_global_info){vfree(file_global_info);}
    if(fp){nv_file_close(fp);}

    return NV_OK;

free_pdata:
    if(file_ctrl_data)  {vfree(file_ctrl_data);}
    if(file_global_info){vfree(file_global_info);}
close_file:
    if(fp){nv_file_close(fp);}
    fp = NULL;
    nv_mntn_record("\n[%s]\n",__FUNCTION__);
    nv_help(NV_FUN_REVERT_DATA);
    return ret;
}


/*
* Function   : nv_revertEx
* Discription: �ָ�nv
* Parameter  : path �ļ�·��
* Output     : read result
* History    : yuyangyang  00228784  create
*/
u32 nv_revertEx(const s8* path)
{
    u32 ret = NV_ERROR;

    nv_mntn_record("start to revert nv from %s!\n",path);
    ret = nv_revert_data((s8*)path,g_ausNvResumeUserIdList,\
        bsp_nvm_getRevertNum(NV_USER_ITEM), NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_error_printf("ret = 0x%x\n",ret);
        return ret;
    }
    ret = nv_revert_data((s8*)path,g_ausNvResumeManufactureIdList,\
        bsp_nvm_getRevertNum(NV_MANUFACTURE_ITEM), NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_error_printf("ret = 0x%x\n",ret);
        return ret;
    }
    ret = nv_revert_data((s8*)path,g_ausNvResumeSecureIdList,\
        bsp_nvm_getRevertNum(NV_SECURE_ITEM), NV_FLAG_NO_CRC);
    if(ret)
    {
        nv_error_printf("ret = 0x%x\n",ret);
        return ret;
    }
    nv_mntn_record("end of revert nv from %s!\n",path);

    return NV_OK;
}

/*
 * copy user buff to global ddr,used to write nv data to ddr
 * &file_id :file id
 * &offset  :  offset of global file ddr
 */
u32 nv_write_to_mem(nv_wr_req *wreq, nv_item_info_s *item_info)
{
    u32 ret = 0;
    u8* mdm_base  = NULL;
    u8* crc_data  = NULL;
    u8* temp_buff = NULL;
    u32 buff_size = 0;

    mdm_base  = nv_get_item_mdmbase(item_info, wreq->modemid, NULL);

    if(nv_crc_need_make_inwr())
    {
        ret = nv_crc_make_item_wr(wreq, item_info, &crc_data, &temp_buff, &buff_size);
        if(NV_OK != ret)
        {
            nv_show_ddr_info();
            nv_printf("make crc fail, nvid 0x%x, nvsize 0x%x\n", item_info->itemid, item_info->nv_len);
            return ret;
        }

        if(NULL != temp_buff)
        {
            nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
            memcpy(crc_data, temp_buff, buff_size);
            nv_flush_cache((u8*)crc_data, buff_size);
            nv_ipc_sem_give(IPC_SEM_NV_CRC);

            vfree(temp_buff);
        }
        else
        {
            nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
            memcpy(mdm_base + wreq->offset, wreq->pdata, wreq->size);
            nv_flush_cache((u8*)(mdm_base + wreq->offset), buff_size);
            nv_ipc_sem_give(IPC_SEM_NV_CRC);
        }
    }
    else
    {
        nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        memcpy(mdm_base + wreq->offset, wreq->pdata, wreq->size);
        nv_flush_cache((u8*)(mdm_base + wreq->offset), buff_size);
        nv_ipc_sem_give(IPC_SEM_NV_CRC);
    }

    return NV_OK;
}


/*
 * copy global ddr to user buff,used to read nv data from ddr
 * &file_id : file id
 * &offset:  offset of the file
 */
u32 nv_read_from_mem(nv_rd_req *rreq, nv_item_info_s *item_info)
{
    u8* mdm_base = NULL;

    mdm_base = nv_get_item_mdmbase(item_info, rreq->modemid, NULL);

    memcpy(rreq->pdata, mdm_base+rreq->offset, rreq->size);

    return NV_OK;
}


/*
 *  acore callback of icc msg.only accept req message
 */
s32 nv_icc_msg_proc(u32 chanid ,u32 len,void* pdata)
{
    return nv_handle_icc_rmsg(chanid , len, pdata);
}

/*
 *  nv use this inter to send data through the icc channel
 */
u32 nv_icc_send(u32 chanid,u8* pdata,u32 len)
{
    s32  ret ;
    u32  fun_id = chanid & 0xffff;/*get fun id*/
    u32  core_type ;
    u32  i = 0;

    if(fun_id == NV_RECV_FUNC_AC)
    {
        core_type = ICC_CPU_MODEM;
    }
    else
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }
    /*lint -save -e578 -e530*/
    nv_debug_trace(pdata, len);
    /*lint -restore +e578 +e530*/
    for(i = 0;i<NV_ICC_SEND_COUNT;i++)
    {
        ret = bsp_icc_send(core_type,chanid,pdata,len);
        if(ICC_INVALID_NO_FIFO_SPACE == ret)/*��Ϣ������,��50ms֮�����·���*/
        {
            nv_taskdelay(50);
            continue;
        }
        else if(ret != (s32)len)
        {
            printf("[%s]:ret :0x%x,len 0x%x\n",__FUNCTION__,ret,len);
            return BSP_ERR_NV_ICC_CHAN_ERR;
        }
        else
        {
            nv_debug_record(NV_DEBUG_SEND_ICC|(((nv_icc_msg_t*)pdata)->msg_type<<16));
            return NV_OK;
        }
    }
    system_error(DRV_ERRNO_NV_ICC_FIFO_FULL,core_type,chanid,(char*)pdata,len);
    return NV_ERROR;
}

/*
 *  init icc channel used by nv module
 */
u32 nv_icc_chan_init(u32 fun_id)
{
    u32 chanid;
    if(fun_id == NV_RECV_FUNC_AC)
    {
        chanid = ICC_CHN_NV << 16 | fun_id;
    }
    else
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }

     /*reg icc debug proc*/
    (void)bsp_icc_debug_register(chanid,nv_modify_pm_sw,(s32)true);

    return (u32)bsp_icc_event_register(chanid,nv_icc_msg_proc,NULL,NULL,NULL);
}
u32 nv_request_flush(void)
{
    g_nv_ctrl.acore_flush_req = NV_REQ_ACORE_DELAY_FLUSH;
    g_nv_ctrl.acore_flush_count++;

    wake_lock(&g_nv_ctrl.wake_lock);
    osl_sem_up(&g_nv_ctrl.task_sem);

    return NV_OK;
}

/*
 *  write data to file/flash/rfile,base the nv priority,inner packing write to ddr
 *  &pdata:    user buff
 *  &offset:   offset of nv in ddr
 *  &len :     data length
 */
u32 nv_write_to_file(nv_wr_req *wreq, nv_item_info_s* item_info)
{
    u32 ret = NV_OK;
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;

    if(NV_HIGH_PRIORITY == item_info->priority)
    {
        nv_debug_record(NV_DEBUG_FLUSH_START | wreq->itemid<<16);
        ret = nv_send_msg_sync(NV_TASK_MSG_WRITE2FILE, wreq->itemid, wreq->modemid);
        if (ret) {
            nv_printf("write nv to file fail, errno:0x%x\n", ret);
            nv_printf("nvid:0x%x  modem_id: 0x%x \n", wreq->itemid, wreq->modemid);
        }

        nv_debug_record(NV_DEBUG_FLUSH_END | wreq->itemid<<16);
        return ret;
    } else if(NV_MID_PRIORITY1 == item_info->priority) {

        nv_debug_record(NV_DEBUG_FLUSH_START | wreq->itemid<<16);
        ret = nv_send_msg_async(NV_TASK_MSG_WRITE2FILE, wreq->itemid, wreq->modemid);
        if (ret) {
            nv_printf("req write to file fail, errno:0x%x\n", ret);
            nv_printf("nvid:0x%x  modem_id: 0x%x  ", wreq->itemid, wreq->modemid);
        }

        nv_debug_record(NV_DEBUG_FLUSH_END | wreq->itemid<<16);
        return ret;
    }

    return nv_add_wrbuf(ddr_info, wreq->itemid, wreq->modemid, item_info->priority);
}


/* nv_get_key_data
 * �Ӷ�Ӧ�����и���nv id��ȡ����
 * path : �ļ�·��
 * itemid: nv id
 * buffer: ���ݻ���,����/���
 * len   : buffer len
 */
u32 nv_get_key_data(const s8* path,u32 itemid,void* buffer,u32 len)
{
    FILE* fp = NULL;
    u32 ret = NV_ERROR;
    u32 file_offset = 0;
    u8* ctrl_head = NULL;
    struct nv_ctrl_file_info_stru    ctrl_head_info = {0};   /*bak file ctrl file head*/
    struct nv_global_ddr_info_stru   *file_base_info = {0};
    struct nv_file_list_info_stru file_info = {0};
    struct nv_ref_data_info_stru ref_info  = {0};


    fp = nv_file_open(path,(s8*)NV_FILE_READ);
    if(!fp)
        return BSP_ERR_NV_NO_FILE;

    ret = (u32)nv_file_read((u8*)(&ctrl_head_info),1,sizeof(ctrl_head_info),fp);
    if(ret != sizeof(ctrl_head_info))
    {
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        goto out;
    }

    if(ctrl_head_info.magicnum != NV_CTRL_FILE_MAGIC_NUM)
    {
        ret = BSP_ERR_NV_FILE_ERROR;
        goto out;
    }

    if(ctrl_head_info.ctrl_size > NV_MAX_FILE_SIZE)
    {
        nv_printf("ctrl size is:0x%x too large\n", ctrl_head_info.ctrl_size);
        ret = BSP_ERR_NV_INVALID_PARAM;
        goto out;
    }

    ctrl_head = (u8*)vmalloc(ctrl_head_info.ctrl_size+1);
    if(NULL == ctrl_head)
    {
        ret = BSP_ERR_NV_MALLOC_FAIL;
        goto out;
    }

    nv_file_seek(fp,0,SEEK_SET); /*jump to file head*/
    ret = (u32)nv_file_read(ctrl_head,1,ctrl_head_info.ctrl_size,fp);
    if(ret != ctrl_head_info.ctrl_size)
    {
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        goto out1;
    }
    file_base_info = (struct nv_global_ddr_info_stru *)nv_malloc(sizeof(struct nv_global_ddr_info_stru));
    if(!file_base_info)
    {
        nv_printf("malloc fail\n");
        ret = BSP_ERR_NV_MALLOC_FAIL;
        goto out1;
    }
    ret = nv_init_file_info((u8*)ctrl_head,(u8*)file_base_info);
    if(ret)
        goto out1;

    ret = nv_search_byid(itemid,(u8*)ctrl_head,&ref_info,&file_info);
    if(ret)
        goto out1;
    file_offset = file_base_info->file_info[ref_info.file_id-1].offset +ref_info.nv_off;

    nv_file_seek(fp,(s32)file_offset,SEEK_SET);
    ret = (u32)nv_file_read(buffer,1, len,fp);
    if(ret != len)
    {
        ret = BSP_ERR_NV_READ_FILE_FAIL;
        goto out1;
    }

    if(ctrl_head){vfree(ctrl_head);}
    if(file_base_info){nv_free(file_base_info);}
    if(fp){nv_file_close(fp);}
    return NV_OK;

out1:
    if(ctrl_head){vfree(ctrl_head);}
    if(file_base_info){nv_free(file_base_info);}
out:
    if(fp){nv_file_close(fp);}
    return ret;
}

/* nv_imei_data_comp
 * ָ�������е�imei����������е����ݶԱ�
 * path : ָ�������ļ�·��
 */
u32 nv_imei_data_comp(const s8* path)
{
    u32 ret;
    char fac_imei[16];
    char path_imei[16];
    int  len = 0;

    memset(fac_imei,0,sizeof(fac_imei));
    memset(path_imei,0,sizeof(path_imei));

    /*���������е�imei�Ż�ȡʧ�ܵ����������Ƚ�*/
    ret = nv_get_key_data((s8*)NV_DEFAULT_PATH,NV_ID_DRV_IMEI,fac_imei,sizeof(fac_imei));
    if(ret)
    {
//        nv_printf("there is no useable factory nv ,don't need compare imei with it 0x%x\n",ret);
        return NV_OK;
    }

    /*��������imei�����ȫ0Ϊ��Ч���ݣ��򲻱Ƚ�*/
    ret = (u32)memcmp(fac_imei,path_imei,sizeof(fac_imei));
    if(!ret)
    {
        nv_printf("factory imei all 0,return direct !\n");
        return NV_OK;
    }

    ret = nv_get_key_data((s8*)path,NV_ID_DRV_IMEI,path_imei,sizeof(path_imei));
    if(BSP_ERR_NV_MALLOC_FAIL == ret)/*�����ڴ�ʧ������Ƚ�*/
    {
        nv_printf("mem malloc failed ,no compare!\n");
        return NV_OK;
    }
    if(ret)
    {
        nv_printf("get imei from %s fail ,ret :0x%x\n",path,ret);
        return ret;
    }

    ret = (u32)memcmp(fac_imei,path_imei,sizeof(fac_imei));
    if(ret)
    {
        nv_modify_print_sw(1);
        len = sizeof(fac_imei);
        nv_debug_trace(fac_imei, len);
        len = sizeof(path_imei);
        nv_debug_trace(path_imei, len);
        nv_modify_print_sw(0);
        return ret;
    }

    return NV_OK;
}


/*****************************************************************************
 �� �� ��  : nv_get_bin_file_len
 ��������  : ����nv.bin�ļ��Ĵ�С
 �������  : fp:��������ļ�
 �������  : ��
 �� �� ֵ  : �ļ���С
*****************************************************************************/
u32 nv_get_bin_file_len(struct nv_ctrl_file_info_stru* ctrl_info,struct nv_file_list_info_stru* file_info,u32 * file_len)
{
    u32 i;
    *file_len = ctrl_info->ctrl_size;

    for(i = 0;i<ctrl_info->file_num;i++)
    {
        *file_len += file_info->file_size;
        file_info ++;
    }
    if(*file_len >= NV_MAX_FILE_SIZE)
    {
        printf("[%s]:file len 0x%x,MAX size 0x%x\n",__func__,*file_len,NV_MAX_FILE_SIZE);
        return BSP_ERR_NV_ITEM_LEN_ERR;
    }
    return NV_OK;
}


u32 nv_resume_item(nv_item_info_s *item_info, u32 itemid, u32 modemid)
{
    u32 ret;
    nv_file_info_s      file_info;
    nv_item_info_s      item_temp;

    if(NULL == item_info)
    {
        ret = nv_search_byid(itemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&item_temp,&file_info);
        if(ret)
        {
            nv_debug(NV_FUN_RESUME_ITEM, 1, itemid, ret, modemid);
            nv_printf("can not find 0x%x!\n",itemid);
            return BSP_ERR_NV_NO_THIS_ID;
        }
        item_info = &item_temp;
    }

    nv_mntn_record("resume from %s item id 0x%x modem %d!\n",NV_IMG_PATH,item_info->itemid, modemid);
    ret = nv_img_resume_item(item_info, modemid);
    if(ret)
    {
        nv_debug(NV_FUN_RESUME_ITEM, 2, item_info->itemid, ret, modemid);
        nv_mntn_record("resume from %s failed, resume from %s, item id 0x%x modem %d!\n",
                       NV_IMG_PATH,
                       NV_BACK_PATH,
                       item_info->itemid,
                       modemid);

        ret = nv_bakup_resume_item(item_info, modemid);
        if(ret)
        {
            nv_mntn_record("resume from %s failed, item id 0x%x modem %d!\n",
                           NV_BACK_PATH, item_info->itemid, modemid);
            nv_debug(NV_FUN_RESUME_ITEM, 3, item_info->itemid, ret, modemid);
            return ret;
        }
    }

    return NV_OK;
}

/*****************************************************************************
 �� �� ��  : nv_resume_ddr_from_img
 ��������  : �ӹ������߱��ݷ������������ָ�NV����
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
u32 nv_resume_ddr_from_img(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    u32 ret = NV_ERROR;
    unsigned long nvflag = 0;

    nv_debug(NV_CRC32_DDR_RESUME_IMG,0,0,0,0);
    if(!nv_debug_is_resume_img())
    {
        nv_mntn_record("nv resume cfg not %s ...%s %s \n",NV_IMG_PATH,__DATE__,__TIME__);
        return NV_OK;
    }
    else
    {
        nv_mntn_record("nv resume %s ...%s %s \n",NV_IMG_PATH,__DATE__,__TIME__);
    }

	/*lock write right*/
    nv_spin_lock(nvflag, IPC_SEM_NV);
    ddr_info->acore_init_state = NV_KERNEL_INIT_DOING;
    nv_spin_unlock(nvflag, IPC_SEM_NV);
    nv_flush_cache((u8*)NV_GLOBAL_START_ADDR, SHM_MEM_NV_SIZE);

    (void)nv_debug_store_ddr_data();

    ret = bsp_nvm_reload();
    if(ret)
    {
        nv_mntn_record("NV resume fail ...%s %s \n",__DATE__,__TIME__);
    }
    else
    {
        /*unlock wirte right*/
        nv_spin_lock(nvflag, IPC_SEM_NV);
        ddr_info->acore_init_state = NV_INIT_OK;
        nv_spin_unlock(nvflag, IPC_SEM_NV);
        nv_flush_cache((u8*)NV_GLOBAL_START_ADDR, SHM_MEM_NV_SIZE);
        nv_mntn_record("NV resume OK ...%s %s \n",__DATE__,__TIME__);
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : nv_flushList
 ��������  : ��ʼ���ػ�д������
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void nv_flushListInit(void)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    memset(&(ddr_info->flush_info), 0, sizeof(struct nv_flush_list_stru));
    nv_flush_cache((void*)NV_GLOBAL_INFO_ADDR, sizeof(struct nv_global_ddr_info_stru*));
    return;
}

u32 nv_flushItem(nv_flush_item_s *flush_item)
{
    nv_ctrl_info_s*   ctrl_info   = (nv_ctrl_info_s*)NV_GLOBAL_CTRL_INFO_ADDR;
    nv_item_info_s    item_info;
    nv_file_info_s    file_info;
    u32 ret;
    u8* data;
    u32 file_offset;
    u32 len;
    bool need_crc;

    ret = nv_search_byid(flush_item->itemid, (u8*)ctrl_info, &item_info, &file_info);
    if(ret)
    {
        nv_printf("there is not this nvid 0x%x, modemid 0x%x\n", flush_item->itemid, flush_item->modemid);
        return ret;
    }

    if((0 == flush_item->modemid) || (flush_item->modemid > item_info.modem_num))
    {
        nv_printf("modemid is invalid! nvid: 0x%x, modemid: 0x%x\n", flush_item->itemid, flush_item->modemid);
        return BSP_ERR_NV_INVALID_MDMID_ERR;
    }

    /* ����crcУ�� */
    if(NV_ITEM_CRC_CHECK_YES)
    {
        data   = nv_get_item_base(&item_info);
        len    = nv_get_item_len(&item_info, NULL);
        file_offset = nv_get_item_fileoffset(&item_info, NULL);
        need_crc = true;
    }
    else if(NV_MODEM_CRC_CHECK_YES)
    {
        data   = nv_get_item_mdmbase(&item_info, flush_item->modemid, NULL);
        len    = nv_get_item_mdmlen(&item_info, NULL);
        file_offset = (u32)nv_get_item_filemdmoffset(&item_info, flush_item->modemid, NULL, NULL);
        need_crc = true;
    }
    else
    {
        data   = nv_get_item_mdmbase(&item_info, flush_item->modemid, NULL);
        len    = nv_get_item_mdmlen(&item_info, NULL);
        file_offset = (u32)nv_get_item_filemdmoffset(&item_info, flush_item->modemid, NULL, NULL);
        need_crc = false;
    }

    if(need_crc)
    {
        u8* buff;
        u32 crc_code;

        buff = vmalloc(len);
        if(NULL == buff)
        {
            nv_printf("malloc mem failed 0x%x\n", flush_item->itemid, len);
            return BSP_ERR_NV_MALLOC_FAIL;
        }

        ret = nv_ipc_sem_take(IPC_SEM_NV_CRC, IPC_SME_TIME_OUT);
        if(ret)
        {
            vfree(buff);
            nv_printf("take ipc sem timeout\n");
            return ret;
        }
        memcpy(buff, data, len);
        nv_ipc_sem_give(IPC_SEM_NV_CRC);

        crc_code = *(u32*)(buff + len - (u32)4);
        /* coverity[overflow] *//* coverity[overflow_sink] *//* coverity[overflow_const] */
        ret = nv_crc_check(buff, len - (u32)4, crc_code);
        if(ret)
        {
            /* ��¼���󣬷�����NVд�� */
            vfree(buff);
            nv_mntn_record("nvid check crc failed, give up write to file 0x%x\n", flush_item->itemid, flush_item->modemid);
            /* coverity[overflow_sink] */
            return ret;
        }

        ret = nv_img_write(buff, len, file_offset);

        vfree(buff);
    }
    else
    {
        ret = nv_img_write(data, len, file_offset);
    }

    return ret;
}

/*lint -restore*/
/*****************************************************************************
 �� �� ��  : nv_check_item_len
 ��������  : ���nv id��start��end֮��ĸ���nv��ĳ���
             ���������ֽڶ����nv id�͸�nv��ĳ��ȴ�ӡ����
 �������  : start:  nv id����ʼֵ
             end  :  nv id�Ľ���ֵ
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
u32 nv_check_item_len(u32 start, u32 end)
{
    u32 i;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)NV_GLOBAL_CTRL_INFO_ADDR;
    struct nv_ref_data_info_stru* ref_info   = (struct nv_ref_data_info_stru*)(NV_GLOBAL_CTRL_INFO_ADDR+NV_GLOBAL_CTRL_INFO_SIZE\
        +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num);
    u32 item_num = 0;

    nv_printf("==================================\n");
    for(i = 0;i<ctrl_info->ref_count;i++)
    {

        if(((ref_info->nv_len)%4 != 0)&&(start <= ref_info->itemid)&&(end >= ref_info->itemid))
        {
           item_num++;
           nv_printf("nv id = 0x%x nv len = 0x%x\n ", ref_info->itemid, ref_info->nv_len);
        }
        ref_info++;
    }
    nv_printf("==========num = 0x%x ===============\n", item_num);

    return NV_OK;
}

EXPORT_SYMBOL(nv_data_writeback);
EXPORT_SYMBOL(nv_resume_ddr_from_img);
EXPORT_SYMBOL(nv_imei_data_comp);
EXPORT_SYMBOL(nv_check_item_len);
EXPORT_SYMBOL(nv_load_err_proc);
EXPORT_SYMBOL(nv_upgrade_revert_proc);
EXPORT_SYMBOL(nv_check_update_default_right);
EXPORT_SYMBOL(nv_delete_update_default_right);
EXPORT_SYMBOL(nv_modify_print_sw);
EXPORT_SYMBOL(nv_modify_pm_sw);
EXPORT_SYMBOL(nv_dload_file_check);
EXPORT_SYMBOL(nv_xml_decode);



