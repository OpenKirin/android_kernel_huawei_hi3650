


#include <linux/device.h> 
#include <linux/clk.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <of.h>
#include <osl_thread.h>
#include <osl_malloc.h>
#include <linux/cdev.h>
//#include "diag_frame.h"
#include "applog_balong.h"


struct cdev applog_cdev;
static unsigned int applogchar_major;
static struct class* applog_class;
struct applog_ctrl_info g_strApplogDebug={0};

s32 applog_open(struct inode * inode, struct file * file);
ssize_t applog_write(struct file *file, const char __user *buf, size_t count,
			loff_t *ppos);
s32 applog_release(struct inode * inode, struct file * file);

static struct file_operations applog_fops = {
    .open    = applog_open,
    .owner   = THIS_MODULE,
    .write   = applog_write,
    .release = applog_release,
};


#define APPLOGCHAR_DEVICE_NAME    "applog"
#define APPLOGCHAR_DEVICE_CLASS   "applog_class"
u32 g_AppLogSocpBufCnt = 0;
u8  *g_pAppLogSocpBuf[1000];
u32 g_applog_conn   = false;
u32 g_applog_enable = false;
u32 g_applog_level  = 0;
u32 g_applog_pkgnum =0;
u32 g_applog_transId=0;
u32 g_applog_init_state=APPLOG_CHN_UNINIT;
applog_data_stru* g_applog_kbuf = NULL;
applog_send_buff* g_applog_sendbuf = NULL;
/*****************************************************************************
* 函 数 名  : bsp_applog_cfg
*
* 功能描述  :打印级别设置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
u32 bsp_applog_cfg(u32 enable,u32 level)
{   
    if(enable)
    {
        g_applog_enable=true;
        
    }
    else
    {
        g_applog_enable=false;
    }
    if((level<=0)||(level>4))
    {
       applog_printf("print level err %d\n",level);
       return APPLOG_ERR;
    }
    g_applog_level=level;
    
    return APPLOG_OK;
}
/*****************************************************************************
* 函 数 名  : bsp_applog_conn
*
* 功能描述  :与工具连接状态设置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
u32 bsp_applog_conn(void)
{
    g_applog_conn=true;
    return APPLOG_OK;

}
/*****************************************************************************
* 函 数 名  : applog_src_chan_cfg
*
* 功能描述  :APP LOG数据送入socp源通道配置
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
u32 applog_src_chan_cfg(void)
{    
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    u8 *p=0;
    dma_addr_t  ulAddress;
    p = (u8 *)dma_alloc_coherent(APPLOG_NULL, APPLOG_SRC_BUF_LEN, &ulAddress, GFP_KERNEL);
    if(APPLOG_NULL == p)
    {            
        applog_printf("applog src chan malloc fail!\n");
        return APPLOG_ERR;
    }         
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_2;
    EncSrcAttr.u32BypassEn = 0;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DST_OM_IND;
    
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8 *)ulAddress;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8 *)(ulAddress +APPLOG_SRC_BUF_LEN - 1);

    if(APPLOG_OK != bsp_socp_coder_set_src_chan(SOCP_CODER_SRC_APPLOG_IND, &EncSrcAttr))
    {

        applog_printf("src channel set failed!\n");
        return APPLOG_ERR;
    }

    bsp_socp_start(SOCP_CODER_SRC_APPLOG_IND);     
    return APPLOG_OK;
}



s32 applog_open(struct inode *inode, struct file *file)
{
    if(!g_applog_init_state)
    {
        return -1;
    }
    return 0;
}
s32 applog_release(struct inode *inode, struct file *file)
{
    inode = inode;
    file  = file;
    return 0;
}

u32 applog_send_data(u8* data,u32 len)
{
    
    SOCP_BUFFER_RW_STRU wbuf = {NULL,};
    if( APPLOG_OK != bsp_socp_get_write_buff(SOCP_CODER_SRC_APPLOG_IND, &wbuf))
    {
       applog_printf(" buffer write fail ,chan=0x%x len=0x%x\n",  SOCP_CODER_SRC_APPLOG_IND, len);
       return -1;
    }
   
    if(wbuf.u32Size >= len)
    {  
        memcpy((void*)APPLOG_PHYS_TO_VIRT(wbuf.pBuffer), data, len);
        APPLOG_FLUSH_CACHE(APPLOG_PHYS_TO_VIRT(wbuf.pBuffer), len);

        bsp_socp_write_done(SOCP_CODER_SRC_APPLOG_IND, len);
    }
    else if(wbuf.u32Size + wbuf.u32RbSize >= len)
    {
        memcpy((void*)APPLOG_PHYS_TO_VIRT(wbuf.pBuffer),data,wbuf.u32Size);
        APPLOG_FLUSH_CACHE(APPLOG_PHYS_TO_VIRT(wbuf.pBuffer),   wbuf.u32Size);
        memcpy((void*)APPLOG_PHYS_TO_VIRT(wbuf.pRbBuffer), data+wbuf.u32Size, (len-wbuf.u32Size));
        APPLOG_FLUSH_CACHE(APPLOG_PHYS_TO_VIRT(wbuf.pRbBuffer), len-wbuf.u32Size);

        bsp_socp_write_done(SOCP_CODER_SRC_APPLOG_IND, len);
    }
    else
    {
        applog_warning_printf(" the buffer space not enough!\n");
        return APPLOG_ERR;
    }

    return APPLOG_OK;
}
/*****************************************************************************
* 函 数 名  : applog_report
*
* 功能描述  :APP LOG数据上报到工具
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
u32 applog_report(applog_send_buff *pstAppLogData,u32 datalen, u8 level)
{
    u32 ret =0;
    u32 socp_packet_len  = 0;
    u32 diag_packet_len  = 0;
    u32 print_packet_len = 0;
    
    diag_print_head_stru *print_head= &pstAppLogData->print_head;
    diag_frame_head_stru *diag_head = &pstAppLogData->diag_head;
    diag_socp_head_stru  *socp_head = &pstAppLogData->socp_head;    

    print_packet_len = datalen          + DIAG_PRINT_HEAD_SIZE;
    diag_packet_len  = print_packet_len + DIAG_FRAME_HEAD_SIZE;
    socp_packet_len  = diag_packet_len  + DIAG_SOCP_HEAD_SIZE;

    /*fill print head*/
    /* 1:error, 2:warning, 3:normal, 4:info */
    /* (0|ERROR|WARNING|NORMAL|INFO|0|0|0) */
    print_head->u32level     = (0x80000000) >> level;
    print_head->u32module    = 0xFFFFF;
    print_head->u32no        = g_applog_pkgnum++;

    /*fill diag head*/    
    bsp_diag_frame_head_init(diag_head);
   
    diag_head->stID.cmdid19b=0;
    diag_head->stID.sec5b =DIAG_FRAME_MSG_PRINT;
    diag_head->stID.mode4b=DIAG_FRAME_MODE_COMM;
    diag_head->stID.pri4b =DIAG_FRAME_MSG_TYPE_APP;
  
    diag_head->stService.MsgTransId  = g_applog_transId;  
    diag_head->u32MsgLen             = print_packet_len;

    /*fill socp head*/
    bsp_diag_fill_socp_head(socp_head,diag_packet_len);
   // memcpy(&pstAppLogData->data,&g_applog_sendbuf->data,datalen);

    ret = applog_send_data((u8*)pstAppLogData, socp_packet_len);
    if(ret)
    {
        applog_printf("send data error!\n");
        g_strApplogDebug.u32ApplogSendData ++;
        return ret;
    }

    /* trans_id++, only if send data successfully*/
    g_applog_transId++;
    
    return APPLOG_OK;   
}
/*****************************************************************************
* 函 数 名  : applog_write
*
* 功能描述  :字符设备数据写入
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
ssize_t applog_write(struct file *file,const char __user *buf, size_t count, loff_t *ppos)
{
    ssize_t ret;
    u32 len=0;
    u8 level=0;
    u32 paramlen =0;
    
    if((0 == g_applog_conn)||(0 == g_applog_enable))
    {
         g_strApplogDebug.u32ApplogSwitchOnOff ++;
        return 0;   
    }
     
    if((NULL == buf)||(count <= APPLOG_HEAD_LEN))
    {
        g_strApplogDebug.u32ApplogInvalidParameter ++;
        return 0;
    }
    
    len = (count > sizeof(applog_data_stru)) ? sizeof(applog_data_stru) : count;
  
    if(copy_from_user(&level, buf, 1))
    {
        applog_printf("copy from user fail!\n");
        return 0;
    }
    
    level=level-'0';
    
    if((level>4)||(level > g_applog_level))
    {
        g_strApplogDebug.u32ApplogLevel ++;
        return 0;
    }
    
    paramlen = snprintf(g_applog_sendbuf->data, APPLOG_MAX_HIDS_BUFF_LEN,"%s[%d]", "applog", 0); 
    if(paramlen>APPLOG_MAX_FILENAME_LINENO_LEN)
    {
       g_strApplogDebug.u32ApplogLength++;
       return 0;
    }
    if(copy_from_user(g_applog_sendbuf->data+paramlen, buf+1, len-1))
    {
        applog_printf("copy from user fail ,read_buf = %s\n", g_applog_sendbuf->data);
        return  0;
    }

    ret=applog_report(g_applog_sendbuf, len-1+paramlen,level);
    if(ret)
    {
        applog_printf("send data fail!\n");
        g_strApplogDebug.u32ApplogReport ++;
        return 0;
    }
 
 
    return len;
}
/*****************************************************************************
* 函 数 名  : applog_setup_cdev
*
* 功能描述  :字符设备创建
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
u32 applog_setup_cdev(struct cdev *cdev,struct file_operations* fops)

{
    int ret;
    dev_t devno = MKDEV(applogchar_major,0);
    
    cdev_init(cdev,fops);
    cdev->owner= THIS_MODULE;
    cdev->ops = fops;

    ret = cdev_add(cdev,devno,1);
    if(ret)
    {
        applog_printf("add applog fail!\n");
        return ret  ;
    }

    applog_class = class_create(THIS_MODULE,APPLOGCHAR_DEVICE_CLASS);
    if(IS_ERR(applog_class))
    {

        applog_printf("class create failed!\n");
        return  APPLOG_ERR;
    }

    device_create(applog_class, NULL, devno, NULL, APPLOGCHAR_DEVICE_NAME);
    return APPLOG_OK;
}
/*****************************************************************************
* 函 数 名  : applog_init
*
* 功能描述  :初始化函数
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 成功与否标识码

 修改历史	:
 日    期	: 2016年4月8日
 作    者	: x00346372
 修改内容	:
*****************************************************************************/
s32 applog_init(void)
{
   
    int ret;
    dev_t dev = 0;
    /*动态获取设备号*/
    ret = alloc_chrdev_region(&dev,0,1,APPLOGCHAR_DEVICE_NAME);
    if(ret)
    {
        applog_printf("applog chrdev failed alloc :%d\n",applogchar_major);
        return ret;
    }
    applogchar_major = MAJOR(dev);
    
    /*创建字符驱动设备*/
    ret=applog_setup_cdev(&applog_cdev,&applog_fops);
    if(ret)
    {
        applog_printf("setup chrdev failed !\n");
        return ret;
    }
    /*APP LOG的SOCP通道*/
    
    ret=applog_src_chan_cfg();
    if(ret)
    {
        applog_printf("src chan fail !\n");
    }
    
    /*申请数据buffer*/
    g_applog_sendbuf = ( applog_send_buff*)osl_malloc(sizeof(applog_send_buff));
    if(NULL == g_applog_sendbuf)
    {
        applog_printf("kbuf malloc fail!\n");
        return APPLOG_ERR;
    }
    memset(g_applog_sendbuf,0,sizeof(applog_send_buff));
    
    g_applog_init_state=APPLOG_CHN_INIT;
    return APPLOG_OK;
} 
void applog_exit(void)
{   
    osl_free(g_applog_sendbuf);
    cdev_del(&(applog_cdev));
    class_destroy(applog_class);
    unregister_chrdev_region(MKDEV(applogchar_major,0),1);
    
}
u32 applog_show_debug(void)
{  
    applog_printf("开关状态                                                   :0x%x\n", 
           g_strApplogDebug.u32ApplogSwitchOnOff);
    applog_printf(" 无效参数                                                  :0x%d\n", 
           g_strApplogDebug.u32ApplogInvalidParameter);
    applog_printf("打印级别错误                                               :0x%x\n", 
           g_strApplogDebug.u32ApplogLevel);
    applog_printf("长度太长                                                   :0x%x\n", 
           g_strApplogDebug.u32ApplogLength);
    applog_printf("数据上报                                                   :0x%x\n", 
           g_strApplogDebug.u32ApplogReport);
    applog_printf("SOCP 数据发送                                              :0x%x\n",
           g_strApplogDebug.u32ApplogSendData);
    return APPLOG_OK;
}
module_init(applog_init);
module_exit(applog_exit);