

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
/*lint --e{7,537,305,322}*/
#include "AtParse.h"
#include "ATCmdProc.h"
#include "AtDeviceCmd.h"
#include "AtCheckFunc.h"
#include "mdrv.h"
#include "AtCmdMsgProc.h"
#include "LNvCommon.h"
#include "at_lte_common.h"

/* 定义了LTE与TDS私有装备AT命令 */
AT_PAR_CMD_ELEMENT_STRU g_astAtDeviceCmdTLTbl[] = {
    /*BEGIN: LTE 快速校准装备AT命令 */
	{AT_CMD_NVRDLEN,
	 atSetNVRDLenPara,		 AT_SET_PARA_TIME,	VOS_NULL_PTR,		 AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
	 VOS_NULL_PTR,		  AT_NOT_SET_TIME,
	 AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
	 (VOS_UINT8*)"^NVRDLEN",(VOS_UINT8*)"(0-65535)"},

	 {AT_CMD_NVRDEX,
	 atSetNVRDExPara,		AT_SET_PARA_TIME,  VOS_NULL_PTR,		AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
	 VOS_NULL_PTR,		  AT_NOT_SET_TIME,
	 AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
	 (VOS_UINT8*)"^NVRDEX",(VOS_UINT8*)"(0-65535),(0-2048),(0-2048)"},

    {AT_CMD_NVWREX,
    atSetNVWRExPara,       AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWREX",(VOS_UINT8*)"(0-65535),(0-2048),(0-2048),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data)"},
    /*END: LTE 快速校准装备AT命令 */


    {AT_CMD_LTCOMMCMD,
    atSetLTCommCmdPara,     AT_SET_PARA_TIME,     atQryLTCommCmdPara,     AT_QRY_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^LTCOMMCMD",  (VOS_UINT8*)"(0-65535),(0-2000),(0-65535),(0-65535),(@data),(@data),(@data),(@data)"},    

};

/*****************************************************************************
 函 数 名  : At_RegisterDeviceCmdTLTable
 功能描述  : 注册装备命令表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 At_RegisterDeviceCmdTLTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtDeviceCmdTLTbl, sizeof(g_astAtDeviceCmdTLTbl)/sizeof(g_astAtDeviceCmdTLTbl[0]));
}


