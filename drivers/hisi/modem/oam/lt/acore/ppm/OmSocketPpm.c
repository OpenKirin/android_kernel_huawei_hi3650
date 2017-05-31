



/*****************************************************************************
  1 头文件包含
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmSocketPpm.h"
#include "cpm.h"
#include "NVIM_Interface.h"


#include "hisocket.h"


/*lint -e767*/
#define  THIS_FILE_ID        PS_FILE_ID_OM_SOCKET_PPM_C
/*lint +e767*/


/* ****************************************************************************
  2 全局变量定义
**************************************************************************** */
COMM_SOCKET_CTRL_INFO_STRU g_astSockInfo[SOCKET_BUTT] =
            {{SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_IND_PORT, SOCK_OM_IND_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_CFG_PORT, SOCK_OM_CFG_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_AT_PORT,     SOCK_AT_SRC_PORT_NUM,           {0,}}
            };

/*****************************************************************************
  3 外部引用声明
*****************************************************************************/







