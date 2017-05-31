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

#include "nv_msg.h"
#include "nv_comm.h"
#include "nv_debug.h"

struct nv_global_msg_info_stru g_msg_ctrl;
/*lint -save -e826 -e958 -e438*/
static const u32 nv_mid_droit[NV_MID_PRI_LEVEL_NUM] = {20,1,1,1,1,1,0};

/*****************************************************************************
  �� �� ��  : nv_get_free_reply
  ��������  :
  �������  : ��
  �� �� ֵ  : 0 ����ɹ� ��0����ʧ��
  �������  : ret������ sn ��Ϣ�����Ӧ��sn��
  ���ú���  :
  ��������  :
 *****************************************************************************/
nv_cmd_reply* nv_get_free_reply(void) {
    nv_cmd_reply *pNvCmdReply;

    pNvCmdReply = nv_malloc(sizeof(nv_cmd_reply));
    if (pNvCmdReply == NULL) {
        nv_printf("malloc fail\n");
        return NULL;
    }

    return pNvCmdReply;
}

nv_cmd_req* nv_get_free_req(void) {
    nv_cmd_req *pNvCmdReq;

    pNvCmdReq = nv_malloc(sizeof(nv_cmd_req));
    if (pNvCmdReq == NULL) {
        nv_printf("malloc fail\n");
        return NULL;
    }

    return pNvCmdReq;
}

/*****************************************************************************
  �� �� ��  : bsp_nvm_acore_msg_cb
  ��������  : ����acore��дNv��д�ļ�������ص�����,ע�ᵽnv_cmd_req�е�nv_msg_callback,
  nv_ap_task��������ɺ����õ��ú���
  ���������������Ϣ��Ҫ�ȴ��ظ�����ע�᱾�ص�������ע�᱾�ص���
  �������  : ��
  �� �� ֵ  : 0 ����ɹ� ��0����ʧ��
  �������  : ret������ sn ��Ϣ�����Ӧ��sn��
  ���ú���  :
  ��������  :
 *****************************************************************************/
u32 bsp_nvm_acore_msg_cb(u32 result, u32 sn)
{
    struct list_head *me = NULL;
    nv_cmd_reply *pNvCmdReply = NULL;
    unsigned long flags;
    msg_queue_t  *pMsgQueue;

    pMsgQueue = &g_msg_ctrl.req_list;

    /* nv icc process is probably access reply msg
     * add semaphore lock to prevent freeing reply msg
     */
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_for_each(me, &g_msg_ctrl.req_list.list)
    {
        pNvCmdReply = list_entry(me, nv_cmd_reply, stList);/* [false alarm] */
        if(pNvCmdReply->sn == sn)
        {
            pNvCmdReply->ret = result;
            osl_sem_up(&pNvCmdReply->sem_req);
            spin_unlock_irqrestore(&pMsgQueue->lock, flags);
            g_msg_ctrl.sync_wr_done_count++;
            return NV_OK;
        }
    }
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    nv_printf("Invalid nv cmd SN %d in reply list", sn);
    return NV_OK;
}


/*****************************************************************************
  �� �� ��  : bsp_nvm_ccore_msg_cb
  ��������  : ����ccore��дNv��д�ļ�������ص�����,��icc�ص���ע�ᵽnv_cmd_req��nv_msg_callback,
  nv_ap_task��������ɺ����õ��ú���
  msg_typeΪNV_ICC_REQ_INSTANT_FLUSH NV_ICC_REQ_FLUSH NV_ICC_REQ_RESUMEע�᱾�ص�
  msg_typeΪNV_ICC_REQ_DELAY_FLUSH ��ע�᱾�ص�
  �������  : ��
  �� �� ֵ  : 0 ����ɹ� ��0����ʧ��
  �������  : ret������ sn ��Ϣ�����Ӧ��sn��
  ���ú���  :
  ��������  :
 *****************************************************************************/
u32 bsp_nvm_ccore_msg_cb(u32 result, u32 sn)
{
    nv_icc_msg_t icc_cnf = {};
    u32 ret = 0;
    u32 chanid = 0;

    icc_cnf.msg_type        = NV_ICC_CNF;
    icc_cnf.send_slice      = bsp_get_slice_value();
    icc_cnf.sn              = sn;
    icc_cnf.ret             = result;
    chanid = ICC_CHN_NV << 16 | NV_RECV_FUNC_AC;
    ret = nv_icc_send(chanid, (u8*)&icc_cnf, sizeof(icc_cnf));
    if(ret)
    {
        nv_printf("send icc to ccore fail, sn:0x%x  errno:0x%x", sn, ret);
    }

    wake_unlock(&g_nv_ctrl.wake_lock);
    g_msg_ctrl.icc_cb_reply++;
    return ret;
}

/*****************************************************************************
  �� �� ��  : nv_get_task_workqueue_node
  ��������  : ��ȡnv_task_ap�е���Ϣ�ڵ���Ϣ ����ɾ��ԭ�нڵ�
  �������  : ��
  �� �� ֵ  : u32 0:�ɹ� ����:ʧ��
  �������  : node: ��Ż�ȡ������Ϣ
  ���ú���  :
  ��������  :
 *****************************************************************************/
nv_cmd_req* nv_get_cmd_req(void)
{
    unsigned long flags;
    nv_cmd_req *pNvCmdReq;
    msg_queue_t  *pMsgQueue;

    pNvCmdReq = NULL;
    pMsgQueue = &g_msg_ctrl.high_task_list;

    /* remove from current nv high/low cmd request list */
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    if (!list_empty(&pMsgQueue->list)) {
        pNvCmdReq = list_first_entry(&pMsgQueue->list, nv_cmd_req, stList);
        list_del(&pNvCmdReq->stList);
    }
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    if (pNvCmdReq)
        return pNvCmdReq;

    pMsgQueue = &g_msg_ctrl.low_task_list;
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    if (!list_empty(&pMsgQueue->list)) {
        pNvCmdReq = list_first_entry(&pMsgQueue->list, nv_cmd_req, stList);
        list_del(&pNvCmdReq->stList);
    }
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    return pNvCmdReq;
}

int nv_put_cmd_req(nv_cmd_req* pNvCmdReq)
{
    if(pNvCmdReq == NULL)
    {
        nv_printf("illegal function parameter \n");
        return BSP_ERR_NV_FREE_BUF_FAIL;
    }

    nv_free(pNvCmdReq);
    return 0;
}

/*****************************************************************************
  �� �� ��  : nv_send_msg_sync
  ��������  : ����ͬ��������Ϣ�����ȴ���Ϣ������ɺ󷵻ؽ��
  �������  : msgtype:��Ϣ����
           itemid :  nvid
modem_id: nv��modem id
�������  : ��
�� �� ֵ  : ��
 *****************************************************************************/
u32 nv_send_msg_sync(u32 msgtype, u32 itemid, u32 modem_id)
{
    nv_cmd_req *pNvCmd = NULL;
    nv_cmd_reply *pNvCmdReply = NULL;
    u32 ret = NV_ERROR, priority;
    msg_queue_t  *pMsgQueue;
    unsigned long flags;

    /*������Ϣ*/
    pNvCmd = nv_get_free_req();
    if(!pNvCmd)
    {
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    if (msgtype == NV_TASK_MSG_FLUSH) {
        priority = LOW_PRIORITY_MSG_QUEUE;
    }else {
        priority = HIGH_PRIORITY_MSG_QUEUE;
    }
    pNvCmd->msg_type   = msgtype;
    pNvCmd->priority   = priority;
    pNvCmd->sn         = ++g_msg_ctrl.req_sn;
    pNvCmd->nv_item_info.itemid    = itemid;
    pNvCmd->nv_item_info.modem_id  = modem_id;
    pNvCmd->nv_msg_callback        = bsp_nvm_acore_msg_cb;


    pNvCmdReply = nv_get_free_reply();
    if (pNvCmdReply == NULL)
    {
        nv_put_cmd_req(pNvCmd);
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    /* �������������ź��� */
    osl_sem_init(0, &(pNvCmdReply->sem_req));
    pNvCmdReply->ret       = NV_ERROR;
    pNvCmdReply->sn        = pNvCmd->sn;

    /* first to add msg reply queue */
    pMsgQueue = &g_msg_ctrl.req_list;
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_add_tail(&pNvCmdReply->stList, &pMsgQueue->list);
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    /* second to add cmd handling queue */
    if (msgtype == NV_TASK_MSG_FLUSH) {
        pMsgQueue = &g_msg_ctrl.low_task_list;
    } else {
        pMsgQueue = &g_msg_ctrl.high_task_list;
    }
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_add_tail(&pNvCmd->stList, &pMsgQueue->list);
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    g_msg_ctrl.sync_wr_count++;
    nv_debug_record(NV_DEBUG_REQ_FLUSH_START | (itemid<<16));
    osl_sem_up(&g_nv_ctrl.task_sem);
    if (osl_sem_downtimeout(&pNvCmdReply->sem_req, NV_MAX_WAIT_TICK))
    {
        nv_printf("down time out\n");
        ret = BSP_ERR_NV_TIME_OUT_ERR;
        g_msg_ctrl.wr_timeout_count++;
        goto del_req_msg_node;
    }

    ret = pNvCmdReply->ret;
    if (ret)
    {
        nv_printf("deal msg 0x%x fail, errno: 0x%x\n", msgtype, ret);
    }

    nv_debug_record(NV_DEBUG_REQ_FLUSH_END | (itemid<<16));
del_req_msg_node:

    /* nv icc process is probably access reply msg
      * add semaphore lock to prevent freeing reply msg
      */

    /* �ͷ���Ϣ�ظ�����������*/
    pMsgQueue = &g_msg_ctrl.req_list;
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_del(&pNvCmdReply->stList);
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    nv_free(pNvCmdReply);
    return ret;
}

/*****************************************************************************
  �� �� ��  : nv_send_msg_async
  ��������  : ����ͬ��������Ϣ�����ȴ���Ϣ������ɺ󷵻ؽ��
  �������  : msgtype:��Ϣ����
           itemid :  nvid
modem_id: nv��modem id
�������  : ��
�� �� ֵ  : ��
 *****************************************************************************/

u32 nv_send_msg_async(u32 msgtype, u32 itemid, u32 modem_id) {
    nv_cmd_req * pNvCmd = NULL;
    msg_queue_t  *pMsgQueue;
    unsigned long flags;

    /*������Ϣ*/
    pNvCmd = nv_get_free_req();
    if (pNvCmd == NULL)
    {
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    pNvCmd->msg_type   = msgtype;
    pNvCmd->priority   = HIGH_PRIORITY_MSG_QUEUE;
    pNvCmd->sn         = ++g_msg_ctrl.req_sn;
    pNvCmd->nv_item_info.itemid    = itemid;
    pNvCmd->nv_item_info.modem_id  = modem_id;
    pNvCmd->nv_msg_callback        = NULL;

    /*������Ϣ����*/
    pMsgQueue = &g_msg_ctrl.high_task_list;
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_add_tail(&pNvCmd->stList, &pMsgQueue->list);
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    g_msg_ctrl.async_wr_count++;
    nv_debug_record(NV_DEBUG_REQ_ASYNC_WRITE | (itemid<<16));
    osl_sem_up(&g_nv_ctrl.task_sem);
    return NV_OK;

}



/*****************************************************************************
  �� �� ��  : nv_send_rmsg_sync
  ��������  : ����ͬ��������Ϣ�����ȴ���Ϣ������ɺ󷵻ؽ��
  �������  : msgtype:��Ϣ����
           itemid :  nvid
modem_id: nv��modem id
�������  : ��
�� �� ֵ  : ��
 *****************************************************************************/

u32 nv_send_rmsg(int msg_type, u32 req_sn, u32 itemid, u32 modem_id) {
    nv_cmd_req * pNvCmd = NULL;
    msg_queue_t  *pMsgQueue;
    unsigned long flags;
    u8 type, priority;
    nv_cb_func func;


    switch (msg_type) {
        case NV_ICC_REQ_PRIORITY_HIGH_FLUSH:
            type = NV_TASK_MSG_WRITE2FILE;
            priority = HIGH_PRIORITY_MSG_QUEUE;
            func = bsp_nvm_ccore_msg_cb;
            pMsgQueue = &g_msg_ctrl.high_task_list;
            break;

        case NV_ICC_REQ_PRIORITY1_FLUSH:
            type = NV_TASK_MSG_WRITE2FILE;
            priority = HIGH_PRIORITY_MSG_QUEUE;
            func = NULL;
            pMsgQueue = &g_msg_ctrl.high_task_list;
            break;

        case NV_ICC_REQ_SHUT_DOWN_FLUSH:
            type = NV_TASK_MSG_FLUSH;
            priority = LOW_PRIORITY_MSG_QUEUE;
            func = bsp_nvm_ccore_msg_cb;
            pMsgQueue = &g_msg_ctrl.low_task_list;
            break;

        case NV_ICC_REQ_RESUME_ITEM:
            type = NV_TASK_MSG_RESUEM_ITEM;
            priority = HIGH_PRIORITY_MSG_QUEUE;
            func = bsp_nvm_ccore_msg_cb;
            pMsgQueue = &g_msg_ctrl.high_task_list;
            break;

        default:
            nv_printf("invalid nv icc msg type %d \n", msg_type);
            return BSP_ERR_NV_ICC_CHAN_ERR;

    };


    /*������Ϣ*/
    pNvCmd = nv_get_free_req();
    if(!pNvCmd)
    {
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    pNvCmd->msg_type   = type;
    pNvCmd->priority   = priority;
    pNvCmd->sn         = req_sn;
    pNvCmd->nv_item_info.itemid    = itemid;
    pNvCmd->nv_item_info.modem_id  = modem_id;
    pNvCmd->nv_msg_callback        = func;

    /*������Ϣ����*/
    spin_lock_irqsave(&pMsgQueue->lock, flags);
    list_add_tail(&pNvCmd->stList, &pMsgQueue->list);
    spin_unlock_irqrestore(&pMsgQueue->lock, flags);

    nv_debug_record(NV_DEBUG_REQ_REMOTE_WRITE | (itemid<<16));
    
    osl_sem_up(&g_nv_ctrl.task_sem);
    g_msg_ctrl.remote_wr_count++;
    return NV_OK;
}


/*****************************************************************************
  �� �� ��  : nv_send_flush_msg_async
  ��������  : ����ͬ��������Ϣ�����ȴ���Ϣ������ɺ󷵻ؽ��
  �������  : msgtype:��Ϣ����
           itemid :  nvid
  modem_id: nv��modem id
  �������  : ��
  �� �� ֵ  : ��
 *****************************************************************************/

u32 nv_send_flush_msg_async(u32 req_sn, nv_flush_list *flush_info) {
    nv_cmd_req * pNvCmd = NULL;
    msg_queue_t  *pMsgQueue;
    unsigned long flags;
    int i;

    pMsgQueue = &g_msg_ctrl.low_task_list;
    for (i=0; i<flush_info->count; i++) {
        /*������Ϣ*/
        pNvCmd = nv_get_free_req();
        if (!pNvCmd)
        {
            nv_printf("malloc fail\n");
            continue;
        }

        pNvCmd->msg_type   = NV_TASK_MSG_WRITE2FILE;
        pNvCmd->priority   = LOW_PRIORITY_MSG_QUEUE;
        pNvCmd->sn         = req_sn;
        pNvCmd->nv_item_info.itemid    = flush_info->list[i].itemid;
        pNvCmd->nv_item_info.modem_id  = flush_info->list[i].modemid;
        pNvCmd->nv_msg_callback        = NULL;

        /*������Ϣ����*/
        spin_lock_irqsave(&pMsgQueue->lock, flags);
        list_add_tail(&pNvCmd->stList, &pMsgQueue->list);
        spin_unlock_irqrestore(&pMsgQueue->lock, flags);

        nv_debug_record(NV_DEBUG_REQ_ASYNC_WRITE | (flush_info->list[i].itemid<<16));
        g_msg_ctrl.async_wr_count++;
        osl_sem_up(&g_nv_ctrl.task_sem);
    }

    return NV_OK;
}

/*****************************************************************************
  �� �� ��  : nv_send_flush_rmsg_async
  ��������  : ����ͬ��������Ϣ�����ȴ���Ϣ������ɺ󷵻ؽ��
  �������  : msgtype:��Ϣ����
           itemid :  nvid
  modem_id: nv��modem id
  �������  : ��
  �� �� ֵ  : ��
 *****************************************************************************/

u32 nv_send_flush_rmsg_async(u32 req_sn) {
    nv_cmd_req * pNvCmd = NULL;
    msg_queue_t  *pMsgQueue;
    unsigned long flags;
    int i, len;
    nv_flush_list *pFlushInfo, *pDestFlushInfo;
    struct nv_global_ddr_info_stru* ddr_info = (nv_global_info_s*)NV_GLOBAL_INFO_ADDR;

    pFlushInfo = &ddr_info->flush_info;
    pDestFlushInfo = g_msg_ctrl.flush_info;
    pMsgQueue = &g_msg_ctrl.low_task_list;
    
    osl_sem_down(&g_msg_ctrl.flush_sem);
    nv_spin_lock(flags, IPC_SEM_NV);
    len = sizeof(nv_flush_list) + sizeof(nv_flush_item_s) * pFlushInfo->count;
    memcpy((void *)pDestFlushInfo, (void*)pFlushInfo, len);
    ddr_info->priority = 0;
    pFlushInfo->count = 0;
    nv_flush_cache((void*)ddr_info, sizeof(nv_global_info_s));
    nv_spin_unlock(flags, IPC_SEM_NV);

    for (i=0; i<pDestFlushInfo->count; i++) {
        /*������Ϣ*/
        pNvCmd = nv_get_free_req();
        if (!pNvCmd)
        {
            nv_printf("malloc fail\n");
            continue;
        }

        pNvCmd->msg_type   = NV_TASK_MSG_WRITE2FILE;
        pNvCmd->priority   = LOW_PRIORITY_MSG_QUEUE;
        pNvCmd->sn         = req_sn;
        pNvCmd->nv_item_info.itemid    = pDestFlushInfo->list[i].itemid;
        pNvCmd->nv_item_info.modem_id  = pDestFlushInfo->list[i].modemid;
        pNvCmd->nv_msg_callback        = NULL;
        /*������Ϣ����*/
        spin_lock_irqsave(&pMsgQueue->lock, flags);
        list_add_tail(&pNvCmd->stList, &pMsgQueue->list);
        spin_unlock_irqrestore(&pMsgQueue->lock, flags);

        nv_debug_record(NV_DEBUG_REQ_REMOTE_WRITE | (pDestFlushInfo->list[i].itemid<<16));
        g_msg_ctrl.remote_wr_count++;
        osl_sem_up(&g_nv_ctrl.task_sem);
    }

    pDestFlushInfo->count = 0;
    osl_sem_up(&g_msg_ctrl.flush_sem);

    return NV_OK;
}

/*  Function:    nv_flush_wrbuf
 *  Description: Flush low priority write cmd to cmd request list
 *  Input:
 *              ddr_info: nv ddr control info
 *  Output:     O for success, other for failure
 */
u32 nv_flush_wrbuf(struct nv_global_ddr_info_stru* ddr_info) {
    unsigned long nvflag;
    int len;
    unsigned int ret;

    osl_sem_down(&g_msg_ctrl.flush_sem);
    nv_spin_lock(nvflag, IPC_SEM_NV);
    len = sizeof(nv_flush_list) + sizeof(nv_flush_item_s) * ddr_info->flush_info.count;
    memcpy((void *)g_msg_ctrl.flush_info, &(ddr_info->flush_info), len);
    ddr_info->priority = 0;
    ddr_info->flush_info.count = 0;
    nv_flush_cache((void*)ddr_info, sizeof(struct nv_global_ddr_info_stru));
    nv_spin_unlock(nvflag, IPC_SEM_NV);

    ret = nv_send_flush_msg_async(++g_msg_ctrl.req_sn, g_msg_ctrl.flush_info);
    g_msg_ctrl.flush_info->count = 0;
    osl_sem_up(&g_msg_ctrl.flush_sem);
    return ret;
}

/*  Function:    nv_add_wrbuf
 *  Description: Flush low priority write cmd to cmd request list
 *  Input:
 *              ddr_info: nv ddr control info
 *              itemid  : nv id number
 *              modem_id: modem id number
 *              priority: priority for the nv id
 *  Output:     O for success, other for failure
 */
u32 nv_add_wrbuf(struct nv_global_ddr_info_stru* ddr_info, u32 itemid, u32 modem_id, u32 priority) {
    u32 ret = NV_OK;
    unsigned long nvflag;
    int i, index, len, need_flush;
    nv_flush_list *pFlushInfo;

    pFlushInfo = &ddr_info->flush_info;
    osl_sem_down(&g_msg_ctrl.flush_sem);
    need_flush = 0;
    nv_spin_lock(nvflag, IPC_SEM_NV);
    index = pFlushInfo->count;

    /* check whether there is duplicated nv item in write buffer */
    for (i=0; i<index; i++) {
        if ((pFlushInfo->list[i].itemid == itemid) && (pFlushInfo->list[i].modemid == modem_id))
           break;
    }

    /* do not find match nvid in low priotiry write history */
    if (i == index) {
        if (i < NV_FLUSH_LIST_SIZE) {
            pFlushInfo->list[index].itemid = itemid;
            pFlushInfo->list[index].modemid = modem_id;
            pFlushInfo->count++;
        } else {
            nv_printf("NV write size overflow \n");
        }
    }

    /* update the priority, check whether it should be flushed out */
    ddr_info->priority += nv_mid_droit[priority - NV_MID_PRIORITY1];
    if ((ddr_info->priority >= g_nv_ctrl.mid_prio) || (pFlushInfo->count >= NV_FLUSH_LIST_OVER_SIZE)) {
        len = sizeof(nv_flush_list) + sizeof(nv_flush_item_s) * pFlushInfo->count;
        /* coverity[overrun-buffer-arg] */
        memcpy((void *)g_msg_ctrl.flush_info, (void*)pFlushInfo, len);
        ddr_info->priority = 0;
        pFlushInfo->count = 0;
        need_flush = 1;
    }
    nv_flush_cache((void*)ddr_info, sizeof(struct nv_global_ddr_info_stru));
    nv_spin_unlock(nvflag, IPC_SEM_NV);

    if (need_flush) {
        ret = nv_send_flush_msg_async(++g_msg_ctrl.req_sn, g_msg_ctrl.flush_info);
        g_msg_ctrl.flush_info->count = 0;
    }
    osl_sem_up(&g_msg_ctrl.flush_sem);
    return ret;
}


void nv_msg_dump(void) {
    nv_printf("icc_cb_count %d \n",  g_msg_ctrl.icc_cb_count);
    nv_printf("icc_cb_reply %d \n",  g_msg_ctrl.icc_cb_reply);
    nv_printf("sync_wr_count %d \n",      g_msg_ctrl.sync_wr_count);
    nv_printf("sync_wr_done_count %d \n", g_msg_ctrl.sync_wr_done_count);
    nv_printf("async_wr_count %d \n",      g_msg_ctrl.async_wr_count);
    nv_printf("wr_timeout_count %d \n",      g_msg_ctrl.wr_timeout_count);
    nv_printf("remote_wr_count %d \n",      g_msg_ctrl.remote_wr_count);
    nv_printf("req_sn %d \n",        g_msg_ctrl.req_sn);
    nv_printf("task_proc_count %d \n", g_nv_ctrl.task_proc_count);
    nv_printf("wake_lock_active status %d \n", wake_lock_active(&g_nv_ctrl.wake_lock));
}

/*
 *  acore callback of icc msg.only accept req message
 */
s32 nv_handle_icc_rmsg(u32 chanid, u32 len, void* pdata)
{
    int ret                 = NV_OK;
    nv_icc_msg_single_t   icc_req;

    g_msg_ctrl.icc_cb_count++;
    if (len != sizeof(nv_icc_msg_single_t)) {
        nv_printf("Illegal nv icc msg size %d, should be %d \n", len, sizeof(nv_icc_msg_single_t));
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    ret = bsp_icc_read(chanid, (u8*)&icc_req, len);
    if (len != ret) {
        nv_printf("read icc fail, errno:0x%x\n", ret);
        return BSP_ERR_NV_ICC_CHAN_ERR;
    }

    nv_pm_trace(icc_req);
    switch (icc_req.msg_type) {
        case NV_ICC_REQ_PRIORITY_HIGH_FLUSH:
            wake_lock(&g_nv_ctrl.wake_lock);
            ret = nv_send_rmsg(icc_req.msg_type, icc_req.sn, icc_req.data.itemid, icc_req.data.modem_id);
            break;

        case NV_ICC_REQ_PRIORITY1_FLUSH:
            ret = nv_send_rmsg(icc_req.msg_type, icc_req.sn, icc_req.data.itemid, icc_req.data.modem_id);
            break;

        case NV_ICC_REQ_PRIORITY_MID_LOW_FLUSH:
            ret = nv_send_flush_rmsg_async(icc_req.sn);
            break;

        case NV_ICC_REQ_SHUT_DOWN_FLUSH:
            wake_lock(&g_nv_ctrl.wake_lock);
            ret = nv_send_rmsg(icc_req.msg_type, icc_req.sn, icc_req.data.itemid, icc_req.data.modem_id);
            break;

        case NV_ICC_REQ_RESUME_ITEM:
            wake_lock(&g_nv_ctrl.wake_lock);
            ret = nv_send_rmsg(icc_req.msg_type, icc_req.sn, icc_req.data.itemid, icc_req.data.modem_id);
            break;

        default:
            nv_printf("invalid nv icc msg type %d \n", icc_req.msg_type);
            ret = BSP_ERR_NV_ICC_CHAN_ERR;
    }

    nv_debug_record(NV_DEBUG_RECEIVE_ICC | (icc_req.msg_type<<16));
    return ret;
}


/*****************************************************************************
  �� �� ��  : nv_msg_init
  ��������  : ��ʼ��nv��Ϣ����
  �������  : ��
  �������  : ��
  �� �� ֵ     : 0 ������ȷ�����򷵻ش�������
 *****************************************************************************/

int nv_msg_init(void)
{
    int len;

    memset((void*)&g_msg_ctrl, 0, sizeof(struct nv_global_msg_info_stru));
    g_msg_ctrl.req_sn = 0;

    spin_lock_init(&g_msg_ctrl.high_task_list.lock);
    INIT_LIST_HEAD(&g_msg_ctrl.high_task_list.list);

    spin_lock_init(&g_msg_ctrl.low_task_list.lock);
    INIT_LIST_HEAD(&g_msg_ctrl.low_task_list.list);

    spin_lock_init(&g_msg_ctrl.req_list.lock);
    INIT_LIST_HEAD(&g_msg_ctrl.req_list.list);

    osl_sem_init(1, &g_msg_ctrl.flush_sem);
    g_msg_ctrl.flush_info = NULL;
    len = sizeof(nv_flush_list) + sizeof(nv_flush_item_s) * NV_FLUSH_LIST_SIZE;
    g_msg_ctrl.flush_info = (nv_flush_list *) nv_malloc(len);
    if (g_msg_ctrl.flush_info == NULL) {
        nv_printf("malloc fail\n");
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    return NV_OK;
}

/* vim set ts=4 sw=4 */
