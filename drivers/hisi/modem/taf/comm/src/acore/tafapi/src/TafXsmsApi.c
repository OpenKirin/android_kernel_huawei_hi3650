

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafAppXsmsInterface.h"
#include "MnClient.h"




#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_API_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
函 数 名  : TAF_XSMS_GetReceiverPid
功能描述  : 从Client ID到接收PID的转换
输入参数  : ClientId -- AT客户ID
输出参数  : pulReceiverPid -- 接收PID
返 回 值  : VOS_OK/VOS_ERR
调用函数  : 无
被调函数  :

修改历史      :
 1.日    期   : 2014年10月31日
   作    者   : h00300778
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid)
{
    MODEM_ID_ENUM_UINT16    enModemID;

    /* 调用接口获取Modem ID */
    if (VOS_OK != AT_GetModemIdFromClient(ClientId, &enModemID))
    {
        return VOS_ERR;
    }

    if (MODEM_ID_1 == enModemID)
    {
        *pulReceiverPid = I1_UEPS_PID_XSMS;
    }
    else if (MODEM_ID_2 == enModemID)
    {
        *pulReceiverPid = I2_UEPS_PID_XSMS;
    }
    else
    {
        *pulReceiverPid = I0_UEPS_PID_XSMS;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_SendSmsReq
 功能描述  : APP的短信发送请求
 输入参数  : usClientId:发起该请求的Client的ID
             ucOpId:标识本次操作
             enSndOption:发送选项
             pucData:要发送的短信内容
 输出参数  : 无
 返 回 值  : VOS_OK -- 消息发送成功
             VOS_ERR -- 消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SendSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_SEND_OPTION_ENUM_UINT8     enSndOption,
    VOS_UINT8                          *pucData)
{
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_SetXsmsApMemFullReq
 功能描述  : 通知短信模块 AP侧短信存储空间是不是满了 0 满 1 可用
 输入参数  : usClientId:发起该请求的Client的ID
             ucOpId:标识本次操作
             ucApMemFullFlag:短信存储空间是不是满了 0 满 1 可用s
 输出参数  : 无
 返 回 值  : VOS_OK -- 消息发送成功
             VOS_ERR -- 消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SetXsmsApMemFullReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucApMemFullFlag)
{
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_WriteSmsReq
 功能描述  : APP的短信写入请求
 输入参数  : usClientId:发起该请求的Client的ID
             ucOpId:标识本次操作
             enStatus:短信状态
             pucData:要发送的短信内容
 输出参数  : 无
 返 回 值  : VOS_OK -- 消息发送成功
             VOS_ERR -- 消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_WriteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_STATUS_ENUM_UINT8          enStatus,
    VOS_UINT8                          *pucData)
{
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DeleteSmsReq
 功能描述  : APP的短信删除请求
 输入参数  : usClientId:发起该请求的Client的ID
             ucOpId:标识本次操作
             ucIndex:删除的索引号
 输出参数  : 无
 返 回 值  : VOS_OK -- 消息发送成功
             VOS_ERR -- 消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_DeleteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucIndex)
{
    return VOS_ERR;
}




