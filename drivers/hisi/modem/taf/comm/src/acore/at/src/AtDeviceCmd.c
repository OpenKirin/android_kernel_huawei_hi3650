

/*****************************************************************************
  1 ����???t�㨹o?
*****************************************************************************/
#include "AtParse.h"

#include "ATCmdProc.h"
#include "AtDeviceCmd.h"
#include "AtCheckFunc.h"
#include "mdrv.h"
#include "AtCmdMsgProc.h"

#include "phyoaminterface.h"

#include "AtInputProc.h"

#include "AtTestParaCmd.h"


//DTS2012041801532 w00182550 NV1����??�� start in 2012-04-12
#include "LNvCommon.h"
#include "RrcNvInterface.h"
#include "msp_nvim.h"
/* DTS2012041801532 w00182550 NV1����??�� start in 2012-04-12 */

/* Added by l00167671 for NV2e��????? , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV2e��????? , 2013-05-17, end*/

#include "AtCmdMiscProc.h"

#include "at_lte_common.h"

#include <linux/random.h>


/*****************************************************************************
    D-����??�䨰��?�䨰��?��?��???��?.C???to��?����?
*****************************************************************************/
/*lint -e767 -e960 DT??��?:?T?�� 107747;?��������?:??����?a65952;?-����:Log�䨰��?*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_DEVICECMD_C
/*lint +e767 +e960 DT??��?:?T?�� 107747;?��������?:sunshaohua*/


/*****************************************************************************
  2 ��???��?��??����?
*****************************************************************************/

/* ?����?����?T����??o��?����??��?��
#define CMD_TBL_E5_IS_LOCKED        (0x00000001)     2?����E5???��????��??����?
#define CMD_TBL_PIN_IS_LOCKED       (0x00000002)     2?����PIN?????��????��??����?
#define CMD_TBL_IS_E5_DOCK          (0x00000004)     E5 DOCK?����?
#define CMD_TBL_CLAC_IS_INVISIBLE   (0x00000008)     +CLAC?����??D2?��?3???��?��??����?
*/

VOS_UINT32                 g_ulNVRD = 0;
VOS_UINT32                 g_ulNVWR = 0;

AT_PAR_CMD_ELEMENT_STRU g_astAtDeviceCmdTbl[] = {
    {AT_CMD_GTIMER,
    AT_SetGTimerPara,    AT_NOT_SET_TIME,    AT_QryGTimerPara,      AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GTIMER",   (VOS_UINT8*)"(0-429496728)"},

    {AT_CMD_RSIM,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryRsimPara,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^RSIM",     VOS_NULL_PTR},

    {AT_CMD_PHYNUM,
    AT_SetPhyNumPara,    AT_NOT_SET_TIME,    AT_QryPhyNumPara,      AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHYNUM",   VOS_NULL_PTR},

    {AT_CMD_CSVER,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryCsVer,           AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CSVER",    VOS_NULL_PTR},

    {AT_CMD_QOS,
    At_SetQosPara,       AT_NOT_SET_TIME,    At_QryQosPara,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
   AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^QOS",      VOS_NULL_PTR},

    {AT_CMD_SDOMAIN,
    At_SetSDomainPara,   AT_NOT_SET_TIME,    At_QrySDomainPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SDOMAIN",  VOS_NULL_PTR},

    {AT_CMD_DPACAT,
    At_SetDpaCat,        AT_NOT_SET_TIME,    At_QryDpaCat,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DPACAT",   VOS_NULL_PTR},

    {AT_CMD_HSSPT,
    AT_SetHsspt  ,       AT_NOT_SET_TIME,    AT_QryHsspt,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HSSPT",    (VOS_UINT8*)"(0,1,2,6)"},

    {AT_CMD_PLATFORM,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryPlatForm,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PLATFORM", VOS_NULL_PTR},

    {AT_CMD_BSN,
    At_SetBsn,           AT_NOT_SET_TIME,    At_QryBsn,             AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^BSN",      VOS_NULL_PTR},

/* Modify by c00172979 for V7�䨲??��?2?, 2012-04-13, Begin   */
/* Modify by c00172979 for V7�䨲??��?2?, 2012-04-13, End   */
    {AT_CMD_SFM,
    At_SetSfm,          AT_SET_PARA_TIME,   At_QrySfm,            AT_NOT_SET_TIME,    VOS_NULL_PTR , AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SFM",     (VOS_UINT8*)"(0,1)"},

    {AT_CMD_TMODE,
    At_SetTModePara,     AT_SET_PARA_TIME,   At_QryTModePara,       AT_QRY_PARA_TIME ,  At_TestTmodePara , AT_TEST_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TMODE",    (VOS_UINT8*)"(0,1,2,3,4,11,12,13,14,15,16,17,18,19)"},

    /* DTS2012041801532 w00182550 NV1����??�� start in 2012-04-12 */
    {AT_CMD_FCHAN,
    At_SetFChanPara,     AT_SET_PARA_TIME,   At_QryFChanPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FCHAN_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FCHAN",    (VOS_UINT8*)"(0-7),(0-255),(0-65535)"},
    /* DTS2012041801532 w00182550 NV1����??�� end in 2012-04-12 */

    {AT_CMD_FTXON,
    At_SetFTxonPara,     AT_SET_PARA_TIME,   At_QryFTxonPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FTXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FTXON",    (VOS_UINT8*)"(0,1,2)"},

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, Begin   */
    {AT_CMD_FDAC,
    AT_SetFDac,          AT_SET_PARA_TIME,   AT_QryFDac,            AT_NOT_SET_TIME,    At_TestFdacPara , AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FDAC",     (VOS_UINT8*)"(0-65536)"},

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, End   */

    {AT_CMD_FRXON,
    At_SetFRxonPara,     AT_SET_PARA_TIME,   At_QryFRxonPara,       AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FRXON_OTHER_ERR  ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FRXON",    (VOS_UINT8*)"(0-1)"},

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, Begin   */
    {AT_CMD_FPA,
    At_SetFpaPara,       AT_SET_PARA_TIME,   At_QryFpaPara,         AT_NOT_SET_TIME,    VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FPA_OTHER_ERR  ,      CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPA",      (VOS_UINT8*)"(0-255)"},

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, End   */

    {AT_CMD_FLNA,
    At_SetFlnaPara,      AT_SET_PARA_TIME,   At_QryFlnaPara,        AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_FLNA_OTHER_ERR  ,     CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FLNA",     (VOS_UINT8*)"(0-255)"},

    {AT_CMD_FRSSI,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryFrssiPara,       AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FRSSI",    VOS_NULL_PTR},

    {AT_CMD_MDATE,
    AT_SetMDatePara,     AT_NOT_SET_TIME,    AT_QryMDatePara,       AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^MDATE",    (VOS_UINT8*)"(@time)"},

    {AT_CMD_FACINFO,
    AT_SetFacInfoPara,   AT_NOT_SET_TIME,    AT_QryFacInfoPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FACINFO",  (VOS_UINT8*)"(0,1),(@valueInfo)"},


    {AT_CMD_SD,
    At_SetSD,            AT_NOT_SET_TIME,    At_QrySD,              AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_SD_CARD_OTHER_ERR ,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SD",       (VOS_UINT8*)"(0-4),(0-429496728),(0-3)"},

    {AT_CMD_GPIOPL,
    At_SetGPIOPL,        AT_SET_PARA_TIME,   At_QryGPIOPL,          AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GPIOPL",   (VOS_UINT8*)"(@GPIOPL)"},

    /* Add by w00199382 for V7�䨲??��?2?, 2012-04-07, Begin   */
    /* DTS2012041801532 w00182550 NV1����??�� start in 2012-04-12 */
    {AT_CMD_GETEXBANDINFO,
    AT_SetExbandInfoPara,      AT_NOT_SET_TIME,  VOS_NULL_PTR,            AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GETEXBANDINFO",     (VOS_UINT8*)"(101-116)"},

    {AT_CMD_GETEXBANDTESTINFO,
    AT_SetExbandTestInfoPara,      AT_NOT_SET_TIME, VOS_NULL_PTR ,     AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GETEXBANDTESTINFO",      (VOS_UINT8*)"(101-116),(14,50,100,150,200)"},
    /* DTS2012041801532 w00182550 NV1����??�� end in 2012-04-12 */
    /* ����2��NV???�� */
    {AT_CMD_INFORRS,
    At_SetInfoRRS,       AT_SET_PARA_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^INFORRS",  VOS_NULL_PTR},
    /* Add by w00199382 for V7�䨲??��?2?, 2012-04-07, End   */

    {AT_CMD_INFORBU,
    atSetNVFactoryBack,  AT_SET_PARA_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^INFORBU",  VOS_NULL_PTR},

    {AT_CMD_DATALOCK,
    At_SetDataLock,      AT_SET_PARA_TIME,   At_QryDataLock,        AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DATALOCK", (VOS_UINT8*)"(@nlockCode)"},

    {AT_CMD_VERSION,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QryVersion,         AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^VERSION",  VOS_NULL_PTR},



    {AT_CMD_SIMLOCK,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    At_QrySimLockPlmnInfo, AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCK",  VOS_NULL_PTR},

    {AT_CMD_MAXLCK_TIMES,
    At_SetMaxLockTimes,  AT_SET_PARA_TIME,   At_QryMaxLockTimes,    AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^MAXLCKTMS",(VOS_UINT8*)"(0-429496728)"},

    {AT_CMD_CALLSRV,
    At_SetCallSrvPara,   AT_NOT_SET_TIME,    At_QryCallSrvPara,     AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CALLSRV",  (VOS_UINT8*)"(0,1)"},

    {AT_CMD_CSDFLT,
    At_SetCsdfltPara,    AT_NOT_SET_TIME,    At_QryCsdfltPara,      AT_QRY_PARA_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR,                       CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CSDFLT",   (VOS_UINT8*)"(0,1)"},

    {AT_CMD_SECUBOOTFEATURE,
    VOS_NULL_PTR,    AT_NOT_SET_TIME,    At_QrySecuBootFeaturePara, AT_NOT_SET_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECUBOOTFEATURE",  (VOS_UINT8*)"(0-3)"},

    {AT_CMD_SECUBOOT,
    At_SetSecuBootPara,  AT_SET_PARA_TIME,    At_QrySecuBootPara,    AT_QRY_PARA_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECUBOOT", (VOS_UINT8*)"(0-3)"},

    {AT_CMD_SETKEY,
    At_SetKeyPara,  AT_SET_PARA_TIME,    VOS_NULL_PTR,    AT_NOT_SET_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SETKEY", (VOS_UINT8*)"(1-4)"},

    {AT_CMD_GETKEYINFO,
    At_GetKeyInfoPara,  AT_SET_PARA_TIME,    VOS_NULL_PTR,    AT_NOT_SET_TIME,  VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^GETKEYINFO", (VOS_UINT8*)"(1-4)"},


    {AT_CMD_TMMI,
    AT_SetTmmiPara,      AT_NOT_SET_TIME,    AT_QryTmmiPara,        AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TMMI",  (VOS_UINT8*)"(0,1)"},

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�䨲??����o?*/
    /* V7R1��a?����1��?"=?"2��?��3?��?��1?�����䨬? */
    {AT_CMD_TCHRENABLE,
    AT_SetChrgEnablePara,AT_NOT_SET_TIME,    AT_QryChrgEnablePara,  AT_NOT_SET_TIME,   AT_TestChrgEnablePara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TCHRENABLE",(VOS_UINT8*)"(0,1,4)"},
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�䨲??����o?*/

    {AT_CMD_TCHRINFO,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryChrgInfoPara,    AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TCHRINFO",VOS_NULL_PTR},

    {AT_CMD_TSCREEN,
    AT_SetTestScreenPara,AT_NOT_SET_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TSCREEN",  (VOS_UINT8*)"(0-255),(0-255)"},

    {AT_CMD_BATVOL,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryBatVolPara,      AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^TBATVOLT",  VOS_NULL_PTR},

    {AT_CMD_WUPWD,
    AT_SetWebPwdPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WUPWD",  (VOS_UINT8*)"(0,1),(@WUPWD)"},

    {AT_CMD_PRODTYPE,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryProdTypePara,    AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PRODTYPE",  VOS_NULL_PTR},

    {AT_CMD_FEATURE,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryFeaturePara,     AT_QRY_PARA_TIME,  At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SFEATURE",  VOS_NULL_PTR},

    {AT_CMD_PRODNAME,
    AT_SetProdNamePara,  AT_NOT_SET_TIME,    AT_QryProdNamePara,    AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PRODNAME",  (VOS_UINT8*)"(@ProductName)"},

    {AT_CMD_FWAVE,
    AT_SetFwavePara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,          AT_NOT_SET_TIME,   At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FWAVE",  (VOS_UINT8*)"(0-7),(0-65535)"},

    {AT_CMD_EQVER,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,    AT_QryEqverPara,       AT_NOT_SET_TIME,   VOS_NULL_PTR,     AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^EQVER",  VOS_NULL_PTR},

    {AT_CMD_WIENABLE,
    AT_SetWiFiEnablePara, AT_NOT_SET_TIME, AT_QryWiFiEnablePara, AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIENABLE",(VOS_UINT8*)"(0,1,2)"},

    {AT_CMD_WIMODE,
    AT_SetWiFiModePara,   AT_NOT_SET_TIME, AT_QryWiFiModePara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIMODE",  (VOS_UINT8*)"(0,1,2,3,4)"},

    {AT_CMD_WIBAND,
    AT_SetWiFiBandPara,   AT_NOT_SET_TIME, AT_QryWiFiBandPara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIBAND",  (VOS_UINT8*)"(0,1)"},

    {AT_CMD_WIFREQ,
    AT_SetWiFiFreqPara,   AT_NOT_SET_TIME, AT_QryWiFiFreqPara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIFREQ",  (VOS_UINT8*)"(0-65535),(@offset)"},

    {AT_CMD_WIRATE,
    AT_SetWiFiRatePara,   AT_NOT_SET_TIME, AT_QryWiFiRatePara,   AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIDATARATE",  (VOS_UINT8*)"(0-65535)"},

    /* Modified by L00171473 for DTS2012020106679,AT WT1��?? 2012-01-17  Begin */
    {AT_CMD_WIPOW,
    AT_SetWiFiPowerPara,  AT_NOT_SET_TIME, AT_QryWiFiPowerPara,  AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIPOW",    (VOS_UINT8*)"(0-65535)"},
    /* Modified by L00171473 for DTS2012020106679,AT WT1��?? 2012-01-17  End */

    {AT_CMD_WITX,
    AT_SetWiFiTxPara,     AT_NOT_SET_TIME, AT_QryWiFiTxPara,     AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WITX",     (VOS_UINT8*)"(0,1)"},

    {AT_CMD_WIRX,
    AT_SetWiFiRxPara,     AT_NOT_SET_TIME, AT_QryWiFiRxPara,     AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIRX",     (VOS_UINT8*)"(0,1),(@smac),(@dmac)"},

    {AT_CMD_WIRPCKG,
    AT_SetWiFiPacketPara, AT_NOT_SET_TIME, AT_QryWiFiPacketPara, AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIRPCKG",  (VOS_UINT8*)"(0)"},

    {AT_CMD_SSID,
    AT_SetWiFiSsidPara,   AT_NOT_SET_TIME, AT_QryWiFiSsidPara,   AT_NOT_SET_TIME, AT_TestSsidPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SSID",  (VOS_UINT8*)"(0-3),(@SSID)"},

    {AT_CMD_WIKEY,
    AT_SetWiFiKeyPara,    AT_NOT_SET_TIME, AT_QryWiFiKeyPara,    AT_NOT_SET_TIME, AT_TestWikeyPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIKEY",  (VOS_UINT8*)"(0-3),(@WIKEY)"},

    {AT_CMD_WILOG,
    AT_SetWiFiLogPara,    AT_NOT_SET_TIME, AT_QryWiFiLogPara,    AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WILOG",  (VOS_UINT8*)"(0,1),(@content)"},

    {AT_CMD_WIINFO,
    AT_SetWifiInfoPara,   AT_NOT_SET_TIME, VOS_NULL_PTR,         AT_NOT_SET_TIME, At_CmdTestProcERROR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIINFO",  (VOS_UINT8*)"(0,1),(0,1)"},

    {AT_CMD_WIPARANGE,
    AT_SetWifiPaRangePara, AT_NOT_SET_TIME, AT_QryWifiPaRangePara, AT_NOT_SET_TIME, AT_TestWifiPaRangePara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^WIPARANGE",  (VOS_UINT8*)"(@gainmode)"},

    {AT_CMD_NVRD,
    AT_SetNVReadPara,     AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVRD",(VOS_UINT8*)"(0-65535)"},

    {AT_CMD_NVWR,
    AT_SetNVWritePara,    AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWR",(VOS_UINT8*)"(0-65535),(0-2048),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data)"},
    /* Added by ?�̨�3?y/f62575 for AT Project, SIM?������?�����??������?, 2011/11/15, begin */
	/* Added by s00217060 for ?��?����?����AT?����???????��??��Co?, 2013-4-3, begin */

    {AT_CMD_NVWRPART,
    AT_SetNVWRPartPara,       AT_SET_PARA_TIME,  VOS_NULL_PTR,        AT_NOT_SET_TIME,  VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWRPART",(VOS_UINT8*)"(0-65535),(0-2048),(0-2048),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data),(@data)"},


    {AT_CMD_CURC,
    At_SetCurcPara,      AT_NOT_SET_TIME,     At_QryCurcPara,     AT_QRY_PARA_TIME, VOS_NULL_PTR,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^CURC", (VOS_UINT8*)"(0-2)"},
	/* Added by s00217060 for ?��?����?����AT?����???????��??��Co?, 2013-4-3, end */
    /* Added by ?�̨�3?y/f62575 for AT Project, SIM?������?�����??������?, 2011/11/15, end */

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, Begin   */

    {AT_CMD_SN,
    At_SetSnPara,        AT_NOT_SET_TIME,    VOS_NULL_PTR,           AT_NOT_SET_TIME,    At_CmdTestProcOK, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_DEVICE_OTHER_ERROR, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SN",       VOS_NULL_PTR},

    /* Modify by w00199382 for V7�䨲??��?2?, 2012-04-07, End   */

    {AT_CMD_TBAT,
    AT_SetTbatPara,     AT_SET_PARA_TIME,   AT_QryTbatPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TBAT",    (VOS_UINT8 *)"(0,1),(0,1),(0-65535),(0-65535)"},

    {AT_CMD_PSTANDBY,
    AT_SetPstandbyPara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^PSTANDBY",    (VOS_UINT8 *)"(0-65535),(0-65535)"},

    {AT_CMD_WIWEP,
    AT_SetWiwepPara,        AT_SET_PARA_TIME,   AT_QryWiwepPara,  AT_QRY_PARA_TIME,  AT_TestWiwepPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^WIWEP",    (VOS_UINT8 *)"(0-3),(@wifikey),(0-3)"},

    {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"},

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�䨲??����o?*/
    {AT_CMD_TSELRF,
    AT_SetTseLrfPara,        AT_SET_PARA_TIME,   AT_QryTseLrfPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TSELRF",    (VOS_UINT8 *)"(0-255),(0-255)"},
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�䨲??����o?*/

    {AT_CMD_HUK,
    AT_SetHukPara,              AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HUK",         (VOS_UINT8 *)"(@huk)"},

    {AT_CMD_FACAUTHPUBKEY,
    VOS_NULL_PTR,               AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FACAUTHPUBKEY",       (VOS_UINT8 *)"(@Pubkey)"},

    {AT_CMD_IDENTIFYSTART,
    AT_SetIdentifyStartPara,    AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^IDENTIFYSTART",       (VOS_UINT8 *)"(@Rsa)"},

    {AT_CMD_IDENTIFYEND,
    AT_SetIdentifyEndPara,      AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^IDENTIFYEND",       VOS_NULL_PTR},

    {AT_CMD_SIMLOCKDATAWRITE,
    VOS_NULL_PTR,               AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKDATAWRITE",    (VOS_UINT8 *)"(@SimlockData)"},

    {AT_CMD_PHONESIMLOCKINFO,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryPhoneSimlockInfoPara, AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHONESIMLOCKINFO",    VOS_NULL_PTR},

    {AT_CMD_SIMLOCKDATAREAD,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QrySimlockDataReadPara,  AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKDATAREAD",     VOS_NULL_PTR},

    {AT_CMD_PHONEPHYNUM,
    AT_SetPhonePhynumPara,  AT_SET_PARA_TIME,    AT_QryPhonePhynumPara,  AT_QRY_PARA_TIME,   AT_TestHsicCmdPara,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PHONEPHYNUM",         (VOS_UINT8 *)"(@type),(@Phynum)"},

    {AT_CMD_PORTCTRLTMP,
    AT_SetPortCtrlTmpPara,          AT_SET_PARA_TIME,   AT_QryPortCtrlTmpPara,  AT_NOT_SET_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PORTCTRLTMP",    (VOS_UINT8 *)"(@password)"},

    {AT_CMD_PORTATTRIBSET,
    AT_SetPortAttribSetPara,          AT_SET_PARA_TIME,   AT_QryPortAttribSetPara,  AT_QRY_PARA_TIME,  AT_TestHsicCmdPara,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^PORTATTRIBSET",    (VOS_UINT8 *)"(0,1),(@password)"},

    {AT_CMD_SIMLOCKUNLOCK,
    AT_SetSimlockUnlockPara, AT_SET_PARA_TIME,  VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_TestSimlockUnlockPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SIMLOCKUNLOCK",    (VOS_UINT8 *)"(\"NET\",\"NETSUB\",\"SP\"),(pwd)"},

    {AT_CMD_FPLLSTATUS,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryFPllStatusPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPLLSTATUS",     (VOS_UINT8 *)"(0,1),(0,1)"},

    {AT_CMD_FPOWDET,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,    AT_QryFpowdetTPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR,  AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^FPOWDET",     VOS_NULL_PTR},

    {AT_CMD_NVWRSECCTRL,
    AT_SetNvwrSecCtrlPara,  AT_SET_PARA_TIME,   AT_QryNvwrSecCtrlPara,  AT_NOT_SET_TIME,   At_CmdTestProcOK,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^NVWRSECCTRL",   (VOS_UINT8*)"(0-2),(@SecString)"},


    {AT_CMD_MIPIWR,
    AT_SetMipiWrPara,  AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^MIPIWR",  (TAF_UINT8*)"(0-9),(0-15),(0-255),(0-65535),(0-3)"},/*mode, slave_id,  address, data,channel*/

   {AT_CMD_MIPIRD,
    AT_SetMipiRdPara,  AT_SET_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^MIPIRD",  (TAF_UINT8*)"(0-9),(0-1),(0-15),(0-255)"},

   {AT_CMD_SSIWR,
    AT_SetSSIWrPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_QRY_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SSIWR",  (TAF_UINT8*)"(0-9),(0-1),(0-255),(0-65535)"}, /*mode, channel, address, data*/

    {AT_CMD_SSIRD,
    AT_SetSSIRdPara, AT_SET_PARA_TIME, VOS_NULL_PTR, AT_QRY_PARA_TIME, VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^SSIRD",  (TAF_UINT8*)"(0-9),(0-1),(0-255)"},/*mode, channel, address*/



    {AT_CMD_SECURESTATE,
    AT_SetSecureStatePara,   AT_NOT_SET_TIME,   AT_QrySecureStatePara,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SECURESTATE", (VOS_UINT8*)"(0-2)"},

    {AT_CMD_KCE,
    AT_SetKcePara,   AT_NOT_SET_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^KCE", (VOS_UINT8*)"(@KceString)"},

    {AT_CMD_SOCID,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,   AT_QrySocidPara,   AT_NOT_SET_TIME,   VOS_NULL_PTR, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^SOCID", (VOS_UINT8*)"(@SocidString)"}

};


/* ��?��y: ^CMDX ?����?��?2?����E5?��??����?��?����?��??��?��+CLAC��D?��?����D?����?����2???��?��?�̨���???2?��y��?2?��???��yo?��?��?��?��?,
        �̨�?t??2?��y��?��???��yo?��?��?��?��?��?�̨���y??2?��y��???��yD��2?��y

   !!!!!!!!!!!���騰a: param1o��param2��?��?��y��?����?��?����??����?������|??��??����?��??��?��(?������???a??D��?��)!!!!!!!!!!!!!

    {AT_CMD_CMDX,
    At_SetCmdxPara, AT_SET_PARA_TIME, At_QryCmdxPara, AT_QRY_PARA_TIME, At_TestCmdxPara, AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_E5_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE,
    (VOS_UINT8*)"^CMDX", (VOS_UINT8*)"(@param1),(param2),(0-255)"},
*/


/*****************************************************************************
  3 o����y����??
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : At_QrySecuBootFeaturePara
 ��������  : ��ѯ��������Ƿ���Secure Boot �汾���Ƿ���Ҫ����Secure Boot ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OK��ѯ�����ɹ���AT_ERROR��ѯ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��6��
    ��    ��   : ����/w00181244
    �޸�����   : �����ع�����ֱ�ӵ��õ���API��Ϊ����Ϣ��C�˵��õ���API

  3.��    ��   : 2012��08��08��
    ��    ��   : y00213812
    �޸�����   : ����DTS2012082100431�޸ģ�ֱ�Ӷ�ȡNV��
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2014��12��15��
    ��    ��   : Z00306637
    �޸�����   : DTS2014120903868, ֱ�ӵ��õ���API
  6.��    ��   : 2016��01��26��
    ��    ��   : w00249971
    �޸�����   : DTS2016012510143, mbb��չ��AT��ʹ֧֮��DX��ȫ�������
*****************************************************************************/
VOS_UINT32 At_QrySecuBootFeaturePara( VOS_UINT8 ucIndex )
{
    VOS_UINT8                          usSecBootSupportedFlag;
    usSecBootSupportedFlag = 0;

    /* ���õ���ӿ� */
    if(MDRV_OK != mdrv_crypto_secboot_supported(&usSecBootSupportedFlag))
    {
        AT_WARN_LOG("At_QrySecuBootFeaturePara: get mdrv_crypto_secboot_supported() failed");
        return AT_ERROR;
    }


    /* ��ӡ��� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            usSecBootSupportedFlag);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetSecDbgState
 ��������  : ���հ�ȫ��Ʒ����ָ���飬������ӦdebugȨ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OK�����ɹ���AT_ERROR����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��14��
    ��    ��   : w00249971
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT32 AT_SetSecDbgState(VOS_VOID)
{
    VOS_INT32               usResult;

    /*1.ִ��SECUREDEBUG=3,���ð�ȫDEBUG��Ȩ�ɰ�ȫ֤�����*/
    usResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_SECUREDEBUG,
                                AT_SECUREDEBUG_VALUE,
                                NULL,
                                0);

    /*���ýӿ�ֻ�����ַ���ֵ��<0,ִ�д���=0��ִ����ȷ��=1���ظ����ã�
      ��������ֻ�жϷ��ش������*/
    if(MDRV_OK > usResult)
    {
        AT_WARN_LOG("AT_SetSecuState: set SECUREDEBUG state error.\n");
        return AT_ERROR;
    }

    /*2.ִ��SECDBGRESET=1��CSRESET=1,�ڶ԰�ȫ�����Coresight����ʱ��
        ��ʱ��λSecEngine*/
    usResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_CSRESET,
                                AT_CSRESET_VALUE,
                                NULL,
                                0);
    if(MDRV_OK > usResult)
    {
        AT_WARN_LOG("AT_SetSecuState: set CSRESET state error.\n");
        return AT_ERROR;
    }

    /*3.ִ��DFTSEL=1 ����ͨ��������֤��ʽ������ȫDFT����*/
    usResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_DFTSEL,
                                AT_DFTSEL_VALUE,
                                NULL,
                                0);
    if(MDRV_OK > usResult)
    {
        AT_WARN_LOG("AT_SetSecuState: set CSRESET state error.\n");
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_SetSecuBootPara
 ��������  : ʹ��Secure Boot ����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OKʹ�ܲ����ɹ���AT_ERRORʹ�ܲ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��3��21��
    ��    ��   : h44270
    �޸�����   : DTS2011031601921,ֻ������Ӳ�����ܵ�����£���������
  3.��    ��   : 2012��02��06��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ع�,��ֱ�ӵ��õ���API��Ϊ����Ϣ��C�˵��õ���API
  4.��    ��   : 2014��12��15��
    ��    ��   : Z00306637
    �޸�����   : DTS2014120903868, ֱ�ӵ��õ���API
  5.��    ��   : 2016��01��21��
    ��    ��   : w00249971
    �޸�����   : DTS2016012510143, mbb��չ��AT��ʹ֧֮��DX��ȫ�������
*****************************************************************************/
VOS_UINT32 At_SetSecuBootPara(VOS_UINT8 ucIndex)
{
    if ((1 != gucAtParaIndex)
        || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_DX_SECURE_STATE < gastAtParaList[0].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case AT_NO_DX_SECU_ENABLE_STATE:
        {
            if (MDRV_OK != mdrv_crypto_start_secure())
            {
                AT_WARN_LOG("At_SetSecuBootPara: mdrv_crypto_start_secure() failed");
                return AT_ERROR;
            }
            break;
        }
        case AT_DX_RMA_STATE:
        {
            /*�Ȼ�ȡ��оƬ״̬������Ѿ�����ΪRMA״̬��ֱ�ӷ���ok*/
            if(AT_DRV_STATE_RMA == mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE,
                                                    0, NULL, 0))
            {
                AT_WARN_LOG("At_SetSecuBootPara: chip is already set to RMA state");
                return AT_OK;
            }

            if (MDRV_OK != mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_SECURESTATE,
                                            AT_SET_RMA_STATE, NULL, 0))
            {
                AT_WARN_LOG("At_SetSecuBootPara: SET_SECURE_DISABLED_STATE  failed");
                return AT_ERROR;
            }
            break;
        }
        case AT_DX_SECURE_STATE:
        {
            /*��ȫ״̬�Ѿ���Fastboot�����ã�����check�£��Ա�֤��������OK*/
            if(AT_DRV_STATE_SECURE != mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_SECURESTATE,
                                                       0, NULL, 0))
            {
                AT_WARN_LOG("At_SetSecuBootPara: chip don't set to SECURE state");
                return AT_ERROR;
            }
            if (AT_OK != AT_SetSecDbgState())
            {
                return AT_ERROR;
            }
            break;
        }
        default:
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_QrySecuBootPara
 ��������  : ��ѯSecure Boot ����ʹ��״̬
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OK��ѯ�����ɹ���AT_ERROR��ѯ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��17��
    ��    ��   : ����/w00181244
    �޸�����   : �����ع�,��ֱ�ӵ��õ���API��Ϊ����Ϣ��C�˵��õ���API
  3.��    ��   : 2014��12��15��
    ��    ��   : Z00306637
    �޸�����   : DTS2014120903868, ֱ�ӵ��õ���API
  4.��    ��   : 2016��01��26��
    ��    ��   : w00249971
    �޸�����   : DTS2016012510143, mbb��չ��AT��ʹ֧֮��DX��ȫ�������
*****************************************************************************/
VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           usSecBootStartedFlag;

    usSecBootStartedFlag = 0;

    if(MDRV_OK != mdrv_crypto_sec_started(&usSecBootStartedFlag))
    {
        AT_WARN_LOG("At_QrySecuBootPara: get mdrv_crypto_sec_started() failed");
        return AT_ERROR;
    }

/*����֧��DX��ȫ����ģ���Ҫ��ѯоƬ״̬*/

    /* ��ӡ��� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            usSecBootStartedFlag);

     return AT_OK;

}

/*****************************************************************************
 �� �� ��  : At_SetKeyPara
 ��������  : ����key ֵ������key�ɲ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OK��ѯ�����ɹ���AT_ERROR��ѯ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��14��
    ��    ��   : w00249971
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 At_SetKeyPara(VOS_UINT8 ucIndex)
{
    VOS_INT32                           usRet;
    VOS_UINT8                           aulKeyBuf[AT_AUTHKEY_LEN];

    if ((1 != gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_KEY_TYPE_BUTT <= gastAtParaList[0].ulParaValue)
    {
        AT_WARN_LOG("At_SetKeyPara: not support the para,pls check\n");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(aulKeyBuf, 0, sizeof(aulKeyBuf));

    switch(gastAtParaList[0].ulParaValue)
    {
        case AT_KEY_TYPE_DIEID:
        case AT_KEY_TYPE_TBOX_SMS:
        case AT_KEY_TYPE_SOCID:
            break;
        case AT_KEY_TYPE_AUTHKEY:
        {
            get_random_bytes(aulKeyBuf, AT_AUTHKEY_LEN);

            usRet = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_SET_AUTHKEY,
                                     0,
                                     aulKeyBuf,
                                     AT_AUTHKEY_LEN);
            if(MDRV_OK != usRet)
            {
                AT_WARN_LOG("At_SetKeyPara: mdrv_set_authkey error.\n");
                return AT_ERROR;
            }
            break;
        }
        default:
        {
            AT_WARN_LOG("At_SetKeyPara: para is error,pls check.\n");
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_GetKeyInfoPara
 ��������  : ��ѯkey ֵ������key�ɲ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32 AT_OK��ѯ�����ɹ���AT_ERROR��ѯ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��14��
    ��    ��   : w00249971
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 At_GetKeyInfoPara(VOS_UINT8 ucIndex)
{
    VOS_INT                 iResult;
    VOS_UINT16              usLength;
    VOS_UINT16              usKeyLen;
    VOS_UINT8               auckeybuf[AT_KEYBUFF_LEN];
    VOS_UINT8               usHashbuf[AT_KEY_HASH_LEN];
    VOS_UINT32              i;


    if (1 != gucAtParaIndex || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_KEY_TYPE_BUTT <= gastAtParaList[0].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(usHashbuf, 0x00, AT_KEY_HASH_LEN);
    PS_MEM_SET(auckeybuf, 0x00, AT_KEYBUFF_LEN);

    switch(gastAtParaList[0].ulParaValue)
    {
        case AT_KEY_TYPE_DIEID:
        case AT_KEY_TYPE_TBOX_SMS:
        {
            /*��׮���ݲ�����*/
            return AT_OK;
        }
        case AT_KEY_TYPE_SOCID:
        {
            usKeyLen = AT_SOCID_LEN;
            iResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_SOCID,
                                       0,
                                       auckeybuf,
                                       AT_SOCID_LEN);

            /* �����쳣��ѯ��� */
            if (MDRV_OK != iResult)
            {
                AT_WARN_LOG("At_QryGetKeyInfoPara:get soc id error.\n");
                return AT_ERROR;
            }
            break;
        }
        case AT_KEY_TYPE_AUTHKEY:
        {
            usKeyLen = AT_AUTHKEY_LEN;
            iResult = mdrv_efuse_ioctl(MDRV_EFUSE_IOCTL_CMD_GET_AUTHKEY,
                                       0,
                                       auckeybuf,
                                       AT_AUTHKEY_LEN);
            if(MDRV_OK != iResult)
            {
                AT_WARN_LOG("At_QryGetKeyInfoPara:get authkey error.\n");
                return AT_ERROR;
            }
            break;
        }
        default:
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

    }

    /*����hashֵ,���ߴ�׮����Ʒ������*/
    /*
    iResult = mdrv_crypto_hash256(auckeybuf, usKeyLen, usHashbuf);
    if(MDRV_OK != iResult)
    {
        AT_WARN_LOG("At_QryGetKeyInfoPara:get hash error.\n");
        return AT_ERROR;
    } */

    /* ��ӡ���AT���� */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%s",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     gaucAtCrLf);

    /*key info*/
    for(i = 0; i < usKeyLen; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          auckeybuf[i]);

    }
    /*key len*/
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",%d,",
                                          usKeyLen * 2);
    /*key hash*/
    for(i = 0; i < AT_KEY_HASH_LEN; i++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02x",
                                          usHashbuf[i]);

    }
    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestTmodePara
 ��������  : TMODE���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 DT??��������      :
  1.��?    ?��   : 2011?��10??9��?
    ����    ??   : w00181244
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 At_TestTmodePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                  "%s: %d",
                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                  g_stAtDevCmdCtrl.ucCurrentTMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 o�� ��y ??  : At_TestFdacPara
 1|?��?����?  : FDAC2a��?o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2011?��10??9��?
    ����    ??   : w00181244
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 At_TestFdacPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength  = 0;

    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: (0-2047)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: (0-1023)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/*****************************************************************************
 o�� ��y ??  : At_RegisterDeviceCmdTable
 1|?��?����?  : ����2�������??����?����
 ��?��?2?��y  : VOS_VOID
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2011?��10??21��?
    ����    ??   : ?3��?/l60609
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 At_RegisterDeviceCmdTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtDeviceCmdTbl, sizeof(g_astAtDeviceCmdTbl)/sizeof(g_astAtDeviceCmdTbl[0]));
}


/*****************************************************************************
 o�� ��y ??  : AT_TestSsidPara
 1|?��?����?  : SSID2a��??����?
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2011?��10??28��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��9??17��?
    ����    ??   : z60575
    DT???����Y   : MULTI_SSIDDT??
*****************************************************************************/
VOS_UINT32 AT_TestSsidPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    AT_WIFI_MAX_SSID_NUM);
    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_TestWikeyPara
 1|?��?����?  : WIKEY2a��??����?
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2011?��10??28��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_TestWikeyPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    AT_WIFI_KEY_NUM);
    return AT_OK;
}


/*****************************************************************************
 o�� ��y ??  : AT_SetTbatPara
 1|?��?����?  : ^TBAT����???����?
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
 2.��?    ?��   : 2012?��03??03��?
   ����    ??   : s62952
   DT???����Y   : BalongV300R002 Build��??��????:��?3yFEATURE_CHARGEo��

*****************************************************************************/
VOS_UINT32 AT_SetTbatPara(VOS_UINT8 ucIndex)
{
    return atSetTBATPara(ucIndex);

    /*
    ?��?Y2?��y2?��???DD??��?2������:
    1.  ?��3?��??�쨺?��?AT^TBAT=1,0??��?��?3?��??1��y��??�̡�?
    �̡¨�?�̡�����/OM?��?��??��?��?3?��y��??��
    2.  ?��3?��??�쨺?��?AT^TBAT=1,1,<value1>,<value2>����??��?3?��??1��y��??�̡�?��?������?3?D���?��?
    D��D���?��??1��?NVID 90(en_NV_Item_BATTERY_ADC)��?��?��|��D����?����y������?��?
    en_NV_Item_BATTERY_ADC?D????��?��???��?��????�̡�???AT?����???��???2?��y��?��?o?��3��?
    3.4V ��??1??��|��?ADC?��
    4.2V ��??1??��|��?ADC?��
    */
}

/*****************************************************************************
 o�� ��y ??  : AT_QryTbatPara
 1|?��?����?  : ^TBAT2��?��?����?��?��?����??��?��?3?��?��2���㡤?��?
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_QryTbatPara(VOS_UINT8 ucIndex)
{
    /*
    �̡¨�?�̡�����?��?��??��?��?3?��2���㡤?��?:
    <mount type> ��?3?��2���㡤?��?
    0 ?T��?3?
    1 ?��?��??��?3?
    2 ?��??��?��??����?3?
    */
    /*?����?���䨬?����D��?��2��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               DRV_AGENT_TBAT_QRY_REQ,
                                               VOS_NULL_PTR,
                                               0,
                                               I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBAT_QRY;             /*����??�̡�?��2������?�꨺? */
        return AT_WAIT_ASYNC_RETURN;                                                              /* �̨���y����2?��??t����?? */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 o�� ��y ??  : AT_SetPstandbyPara
 1|?��?����?  : ����??�̣���???��?��?��y?�����䨬??��
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

  2.��?    ?��   : 2012?��2??21��?
    ����    ??   : w00199382
    DT???����Y   : B060???????���̡�����?��1??��?���̡¨�?
  3.��?    ?��   : 2012?��03??03��?
    ����    ??   : s62952
    DT???����Y   : BalongV300R002 Build��??��???? :��?3y��?D?o��
  4.��?    ?��   : 2012?��04??13��?
    ����    ??   : f62575
    DT???����Y   : V7�䨲??��?2?: ��?3yWIFI_POWER_SHUTDOWN��?oledPwrOffo��DRV_PWRCTRL_USB_LOWPOWER_ENTER��?�̡¨�?��?
                        ��????aDRV_PWRCTRL_STANDBYSTATEACPU (BSP_PWRCTRL_StandbyStateAcpu)
  5.��?    ?��   : 2014?��2??14��?
    ����    ??   : w00167002
    DT???����Y   : L-C?��2������????:?a1??��o����y�̡�??
*****************************************************************************/
VOS_UINT32 AT_SetPstandbyPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_PSTANDBY_REQ_STRU         stPstandbyInfo;


    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, begin */
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, end */


    /* ^PSTANDBY����???����?��D?��??��D2??2?��y: ??��?��y?�����䨬?��?����??3��?��o���̣���???��?��y?�����䨬?��??D??����?? */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (2 != gucAtParaIndex))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    At_FormatResultData(ucIndex, AT_OK); /*D����a?��???��OK*/

    /*����?�衤��??��y?Y����?������3��*/
    VOS_TaskDelay(10);

    /*
    �̡¨�?�̡�����o��OM?��?����1�̣���???��?��y?�����䨬?:
    ACPU��?����3����?2�����¡�o
    1?��??��?WIFI
    2?��LED??��?
    3?��USB PowerOff

    ����???���?Co?��???��?CCPU��?����3����?2�����¡�o
    1?�騪��D??��?��??��?
    2?��1??������?��
    3?��1??D??
    4?��̡¨�?�̡�����?��?��??��?��??��
    */
    /* Modify by f62575 for V7�䨲??��?2?, 2012-04-07, Begin   */
    stPstandbyInfo.ulStandbyTime = gastAtParaList[0].ulParaValue;
    stPstandbyInfo.ulSwitchTime   = gastAtParaList[1].ulParaValue;

    DRV_PWRCTRL_STANDBYSTATEACPU(stPstandbyInfo.ulStandbyTime, stPstandbyInfo.ulSwitchTime);

    /*����?��???���?co?*/
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                           gastAtClientTab[ucIndex].opId,
                           DRV_AGENT_PSTANDBY_SET_REQ,
                           &stPstandbyInfo,
                           sizeof(stPstandbyInfo),
                           I0_WUEPS_PID_DRV_AGENT))
    {
        AT_ERR_LOG("AT_SetPstandbyPara: AT_FillAndSndAppReqMsg fail.");
    }

    /* V7R22����?1??��??��?�̨�1|o?����3������3�� */

    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, begin */
    stPhoneModePara.PhMode = TAF_PH_MODE_MINI;

    if (VOS_TRUE == TAF_MMA_PhoneModeSetReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPhoneModePara))
    {
        /* Modified by zwx247453 for pc1��3����a3650, 2015-08-24, begin */
        /* ����??�̡�?��2�����¨���D�� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = (AT_CMD_CURRENT_OPT_ENUM)AT_CMD_PSTANDBY_SET;
        /* Modified by zwx247453 for pc1��3����a3650, 2015-08-24, end */

        return AT_WAIT_ASYNC_RETURN;    /* ����???����?��|����1��?e���䨬? */
    }
    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, end */

    return AT_SUCCESS;
}

/* DTS2012041801532 w00182550 NV1����??�� start in 2012-04-12 */
VOS_UINT32 AT_SetExbandInfoPara(VOS_UINT8 ucIndex)
{
    LTE_COMM_NON_STANDARD_BAND_COMM_STRU stLpsNonstandBand = {0};
    VOS_UINT32 ulRet  = AT_OK;
    VOS_UINT32 ulNvId = 0;

    /* 1?��AT?����?����D����?��??y���� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2?��2?��y??��y��?��?��?o?��a?�� */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulNvId = gastAtParaList[0].ulParaValue -LTE_COMM_NONSTANDARD_BAND_BEGIN  + EN_NV_ID_BANDNon1_BAND_INFO  ;
    if((ulNvId < EN_NV_ID_BANDNon1_BAND_INFO )||(ulNvId > EN_NV_ID_BANDNon16_BAND_INFO))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = NVM_Read(ulNvId, (VOS_VOID*) &stLpsNonstandBand, sizeof(LTE_COMM_NON_STANDARD_BAND_COMM_STRU));
     if(  NV_OK != ulRet)
     {
        (VOS_VOID)vos_printf("read non stand band nv fail,ulNvId = %d,ulRet = %d!\n",ulNvId,ulRet);
        return AT_ERROR;
     }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:BANDNO:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.ucBandID);


    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                     "%s:DUPLEX:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.enBandMode);

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:FREQ:%d,%d,%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUlFreqInfo.usFLow,
                                                    stLpsNonstandBand.stUlFreqInfo.usFHigh,
                                                    stLpsNonstandBand.stDlFreqInfo.usFLow,
                                                    stLpsNonstandBand.stDlFreqInfo.usFHigh
                                                 );

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:CHANNUM:%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUlFreqInfo.usRangOfNLow,
                                                    stLpsNonstandBand.stDlFreqInfo.usRangOfNLow);

     return AT_OK;
}

VOS_UINT32 AT_SetExbandTestInfoPara(VOS_UINT8 ucIndex)
{
    LTE_COMM_NON_STANDARD_BAND_COMM_STRU stLpsNonstandBand = {0};
    VOS_UINT32 ulRet  = AT_OK;
    VOS_UINT32 ulNvId = 0,ulArrayID=0 ,i=0;

    VOS_UINT32 BandWidthArray[BAND_WIDTH_NUMS]= {14,30,50,100,150,200};

    /* 1?��AT?����?����D����?��??y���� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2?��2?��y??��y��?��?��?o?��a?�� */
    if(2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulNvId = gastAtParaList[0].ulParaValue -LTE_COMM_NONSTANDARD_BAND_BEGIN  + EN_NV_ID_BANDNon1_BAND_INFO  ;

    if((ulNvId  < EN_NV_ID_BANDNon1_BAND_INFO ) ||(ulNvId > EN_NV_ID_BANDNon16_BAND_INFO))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = NVM_Read(ulNvId, (VOS_VOID*) &stLpsNonstandBand, sizeof(LTE_COMM_NON_STANDARD_BAND_COMM_STRU));

    if(  NV_OK != ulRet)
    {
        (VOS_VOID)vos_printf("read non stand band nv fail,ulRet = %d!\n",ulRet);
        return AT_ERROR;
    }

    ulArrayID = BandWidthArray[BAND_WIDTH_NUMS -1];

    for(i = 0 ; i < BAND_WIDTH_NUMS; i++)
    {
        if( BandWidthArray[i] == gastAtParaList[1].ulParaValue)
        {
            ulArrayID = i;
            break;
        }
    }

    gstAtSendData.usBufLen = 0 ;

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                     "%s:FREQS:%d,%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[0],
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[1],
                                                     stLpsNonstandBand.stTestInfo[ulArrayID].usTestFreqs[2]);

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:MAXPOWTOLERANCE:%d,%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stLpsNonstandBand.stUePowerClassInfo.sPowerToleranceHigh,
                                                    stLpsNonstandBand.stUePowerClassInfo.sPowerToleranceLow
                                                 );

    gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                   "%s:REFSENSPOW:%d\r\n",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stLpsNonstandBand.stTestInfo[ulArrayID].sRxRefSensPower);
      return AT_OK;
}
/* DTS2012041801532 w00182550 NV1����??�� end in 2012-04-12 */

/*****************************************************************************
 o�� ��y ??  : AT_WriteWiWep
 1|?��?����?  : D��WIFI KEY��?NV??
 ��?��?2?��y  : VOS_UINT32                          ulIndex        WIFI KEY?��NV???D��??�¨�y
             VOS_UINT32                          ulWiWepLen     WIFI KEY3��?��
             VOS_UINT8                           aucWiWep[]     WIFI KEY?����Y
             AT_WIFI_SEC_STRU                   *pstWifiSecInfo WIFI KEY?��?��NV��?��y?Y?��11
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??10��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

  2.��?    ?��   : 2012?��4??6��?
    ����    ??   : l60609
    DT???����Y   : DTS20120033007015:�̡�??NV50012��??��11??��??��????
*****************************************************************************/
VOS_UINT32 AT_WriteWiWep(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           aucWiWep[],
    VOS_UINT16                          usWiWepLen,
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo,
    VOS_UINT8                           ucGroup
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                          *paucWifiWepKey;

    /* ����?a??DT??en_NV_Item_WIFI_KEY?D��?WIFI KEY����??��??����?D����a?��??��?��?2?NV?�̡�?��?o��?��D?DT??2?��? */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_WriteWiWep: Fail to read en_NV_Item_WIFI_KEY.");
        return AT_ERROR;
    }

    /* ?��?Yindex??��?NV?D�����?��??��?? */
    paucWifiWepKey = ((0 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey1[ucGroup] :
                      ((1 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey2[ucGroup] :
                      ((2 == ulIndex) ? pstWifiSecInfo->aucWifiWepKey3[ucGroup] : pstWifiSecInfo->aucWifiWepKey4[ucGroup])));

    /* ?D??D?��?WIFI KEY��?NV?D????��?��?��?��??? */
    for (ulLoop = 0; ulLoop < AT_NV_WLKEY_LEN; ulLoop++)
    {
        if (paucWifiWepKey[ulLoop] != aucWiWep[ulLoop])
        {
            break;
        }
    }

    /* ?D??D?��?WIFI KEY��?NV?D????��?��????��?��?������??2�����¨���3��*/
    if (AT_NV_WLKEY_LEN == ulLoop)
    {
        return AT_OK;
    }

    /* ?��D?��y?Y��?NV??en_NV_Item_WIFI_KEY */
    PS_MEM_SET(paucWifiWepKey, 0, AT_NV_WLKEY_LEN);

    PS_MEM_CPY(paucWifiWepKey, aucWiWep, usWiWepLen);

    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
         AT_WARN_LOG("AT_WriteWiWep: Fail to write NV en_NV_Item_WIFI_KEY.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetWiwepPara
 1|?��?����?  : ����?????��INDEX��?WiFi WEP�ꡧWIFI��?KEY��??����Y
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

  2.��?    ?��   : 2012?��4??6��?
    ����    ??   : l60609
    DT???����Y   : DTS20120033007015:�̡�??NV50012��??��11??��??��????

  3.��?    ?��   : 2012?��9??17��?
    ����    ??   : z60575
    DT???����Y   : MULTI_SSIDDT??
*****************************************************************************/
VOS_UINT32 AT_SetWiwepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucGroup;
    VOS_UINT32                          ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo;

    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    /* ��?��?2?��y?��2��: ��D?��??��D< index >o��< content >��???2?��y */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (0 == gastAtParaList[2].usParaLen))
    {
        return AT_ERROR;
    }

    /* WIFI key 2�����¨���DATALOCK����?�� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }

    /* < index >��?D??��0-3��??��?����?< content >3��?��D?����NV_WLKEY_LEN */
    ulIndex = gastAtParaList[0].ulParaValue;
    if (ulIndex > AT_WIWEP_CARD_WIFI_KEY_TOTAL)
    {
        return AT_ERROR;
    }

    if (gastAtParaList[1].usParaLen > AT_NV_WLKEY_LEN)
    {
        return AT_ERROR;
    }

    ucGroup = (VOS_UINT8)gastAtParaList[2].ulParaValue;

    if (ucGroup >= AT_WIFI_MAX_SSID_NUM)
    {
        return AT_ERROR;
    }

    /* ��������WIFI KEY��?NV?��112��?��D?��y?Y��?NV??en_NV_Item_WIFI_KEY */
    pstWifiSecInfo = (TAF_AT_MULTI_WIFI_SEC_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                  sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (VOS_NULL_PTR == pstWifiSecInfo)
    {
        return AT_ERROR;
    }

    ulRet = AT_WriteWiWep(ulIndex,
                          gastAtParaList[1].aucPara,
                          gastAtParaList[1].usParaLen,
                          pstWifiSecInfo,
                          ucGroup);

    PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);

    return ulRet;
}

/*****************************************************************************
 o�� ��y ??  : AT_QryWiwepPara
 1|?��?����?  : WIFI KEYD??��2��?��
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

  2.��?    ?��   : 2012?��4??6��?
    ����    ??   : l60609
    DT???����Y   : DTS20120033007015:�̡�??NV50012��??��11??��??��????
  3.��?    ?��   : 2012?��9??17��?
    ����    ??   : z60575
    DT???����Y   : MULTI_SSIDDT??
*****************************************************************************/
VOS_UINT32 AT_QryWiwepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT16                          usLength;
    TAF_AT_MULTI_WIFI_SEC_STRU         *pstWifiSecInfo;
    VOS_UINT8                           aucWifiWepKey[AT_NV_WLKEY_LEN + 1];
    VOS_UINT8                           aucWepKeyLen1[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen2[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen3[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           aucWepKeyLen4[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT8                           ucWepKeyNum;

    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    /* ?a?����?WIFI KEY����???����?��??��NV??en_NV_Item_WIFI_KEY??��?WIFI KEYD??�� */
    pstWifiSecInfo = (TAF_AT_MULTI_WIFI_SEC_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                      sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (VOS_NULL_PTR == pstWifiSecInfo)
    {
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, pstWifiSecInfo, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryWiwepPara: Fail to read en_NV_Item_WIFI_KEY.");
        PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);
        return AT_ERROR;
    }

    ucWepKeyNum = 0;
    PS_MEM_SET(aucWepKeyLen1, 0, sizeof(aucWepKeyLen1));
    PS_MEM_SET(aucWepKeyLen2, 0, sizeof(aucWepKeyLen2));
    PS_MEM_SET(aucWepKeyLen3, 0, sizeof(aucWepKeyLen3));
    PS_MEM_SET(aucWepKeyLen4, 0, sizeof(aucWepKeyLen4));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        /* KEY1??��|��?NV2???������?KEY1��DD�� */
        aucWepKeyLen1[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey1[ulLoop]);
        if (0 != aucWepKeyLen1[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen2[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey2[ulLoop]);
        if (0 != aucWepKeyLen2[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen3[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey3[ulLoop]);
        if (0 != aucWepKeyLen3[ulLoop])
        {
            ucWepKeyNum++;
        }

        aucWepKeyLen4[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstWifiSecInfo->aucWifiWepKey4[ulLoop]);
        if (0 != aucWepKeyLen4[ulLoop])
        {
            ucWepKeyNum++;
        }
    }

    /* ?��?a??������?D����a����??��??��??0���� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        ucWepKeyNum = 0;
        PS_MEM_SET(aucWepKeyLen1, 0, sizeof(aucWepKeyLen1));
        PS_MEM_SET(aucWepKeyLen2, 0, sizeof(aucWepKeyLen2));
        PS_MEM_SET(aucWepKeyLen3, 0, sizeof(aucWepKeyLen3));
        PS_MEM_SET(aucWepKeyLen4, 0, sizeof(aucWepKeyLen4));
    }

    /*
    ?����?1��?????����a?����?D����a��?3?1��???��3?��?��?2?��y20??WiFi WEP�ꡧWIFI��?KEY��?
    �䨰��???�����̣���??��3?��?WIFI KEYD??��
    ��?3?16DD^WIWEP: <index>,��?1��??��a?����?20??��?WiFi WEP�ꡧWIFI��?KEY��?��???��?
    */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     "%s:%d%s",
                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                     ucWepKeyNum,
                                     gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucWepKeyLen1[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey1[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              0,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen2[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey2[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              1,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen3[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey3[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              2,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }

        if (0 != aucWepKeyLen4[ulLoop])
        {
            /* wifikey1 */
            PS_MEM_SET(aucWifiWepKey, 0, (VOS_SIZE_T)(AT_NV_WLKEY_LEN + 1));

            PS_MEM_CPY(aucWifiWepKey,
                       pstWifiSecInfo->aucWifiWepKey4[ulLoop],
                       AT_NV_WLKEY_LEN);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                              "%s:%d,%s,%d%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              3,
                                              aucWifiWepKey,
                                              ulLoop,
                                              gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength - (VOS_UINT16)VOS_StrLen((VOS_CHAR *)gaucAtCrLf);

    PS_MEM_FREE(WUEPS_PID_AT, pstWifiSecInfo);

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_TestWiwepPara
 1|?��?����?  : WIWEP��?2a��??����?��?��?3?1��???��3?��?WIFI KEY������y
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_TestWiwepPara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   AT_WIWEP_TOOLS_WIFI_KEY_TOTAL);

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_TestWifiPaRangePara
 1|?��?����?  : AT^WIPARANGE2a��?o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��02??02��?
    ����    ??   : l00198894
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_TestWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucWifiMode;

    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    /* 3?��??�� */
    ucWifiMode                          = (VOS_UINT8)WIFI_GET_PA_MODE();

    /* 2��?���̣���??��3?��??�꨺?��o��?1????��3?PA?�꨺?��???��DNO PA?�꨺?��??��??����??h?��?����?��?1?��????�꨺????��3?��??������??h,l?��*/
    if (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "h");
    }
    else if (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "l");
    }
    else if (AT_WIFI_MODE_PA_NOPA == ucWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                "%s:%s",
                                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                "h,l");
    }
    else
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_GetTseLrfLoadDspInfo
 1|?��?����?  : ^TSELRF?����?��?��?�䣤����LOAD DSP
 ��?��?2?��y  : AT_TSELRF_PATH_ENUM_UINT32          enPath     ��??�̨���?������o?
             VOS_BOOL                           *pbLoadDsp  ��?��?�䣤����LOAD DSP
                     VOS_FALSE                              2?�䣤����LOAD DSP2������
                     VOS_TRUE                               �䣤����LOAD DSP2������
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_VOID
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??10��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��01??16��?
    ����    ??   : m00217266
    DT???����Y   : DSDA Co??????��?��DT??(load mode DT??)

*****************************************************************************/
VOS_VOID AT_GetTseLrfLoadDspInfo(
    AT_TSELRF_PATH_ENUM_UINT32          enPath,
    VOS_BOOL                           *pbLoadDsp,
    DRV_AGENT_TSELRF_SET_REQ_STRU      *pstTseLrf
)
{
    /* ^TSELRF?����?����??��?��??�̨���?������o??aGSM?���̡�?�㨰??-LOAD��???����?����??TD��LOAD */
    if (AT_TSELRF_PATH_GSM == enPath)
    {
        if ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
         && (VOS_TRUE == g_stAtDevCmdCtrl.bDspLoadFlag))
        {
            *pbLoadDsp = VOS_FALSE;
        }
        else
        {
            pstTseLrf->ucLoadDspMode     = VOS_RATMODE_GSM;
            pstTseLrf->ucDeviceRatMode   = AT_RAT_MODE_GSM;
            *pbLoadDsp                   = VOS_TRUE;
        }
        return;
    }

    /* ^TSELRF?����?����??��?��??�̨���?������o??aWCDMA?��?��?���̡�?�㨰??-LOAD��???����?����??TD��LOAD */
    if (AT_TSELRF_PATH_WCDMA_PRI == enPath)
    {
        if (((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
          || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
         && (VOS_TRUE == g_stAtDevCmdCtrl.bDspLoadFlag))
        {
            *pbLoadDsp = VOS_FALSE;
        }
        else
        {
            pstTseLrf->ucLoadDspMode     = VOS_RATMODE_WCDMA;
            pstTseLrf->ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
            *pbLoadDsp                   = VOS_TRUE;
        }
        return;
    }

    *pbLoadDsp = VOS_FALSE;

    AT_WARN_LOG("AT_GetTseLrfLoadDspInfo: enPath only support GSM or WCDMA primary.");

    return;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetTseLrfPara
 1|?��?����?  : ^TSELRF��?����??2������
 ��?��?2?��y  : VOS_UINT8 ucIndex  ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32 ����???��DD?��1?3��1|?��?����|�䨪?��??
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??10��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��4??21��?
    ����    ??   : f62575
    DT???����Y   : V7�䨲??��?2?: ???��PATH2?��y����?��
  3.��?    ?��   : 2012?��05??04��?
    ����    ??   : f62575
    DT???����Y   : DTS2012040600347��??��3??��??��??��o���䨰?a?����??����?D?�����?����3��
  4.��?    ?��   : 2012?��05??05��?
    ����    ??   : f62575
    DT???����Y   : DTS2012050502003��??a??V7��?��?AT^TSELRF=1?����??T?����|?����a

*****************************************************************************/
VOS_UINT32 AT_SetTseLrfPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;
    VOS_BOOL                            bLoadDsp;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�䨲??����o?*/
    if ((AT_TSELRF_PATH_WCDMA_PRI!=gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_WCDMA_DIV!=gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_GSM !=gastAtParaList[0].ulParaValue))
    {
        return atSetTselrfPara(ucIndex);
    }
    /*DTS2012041102190 : h00135900 end in 2011-04-11 AT�䨲??����o?*/

    if(AT_TSELRF_PATH_TD == gastAtParaList[0].ulParaValue)
    {
        return atSetTselrfPara(ucIndex);
    }

    /* 2?��y2?��?o?��a?�� */
    if ((1 != gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    if (AT_TSELRF_PATH_WIFI == gastAtParaList[0].ulParaValue)
    {
        /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */
        if ( BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI) )
        {
            /*WIFI?��Enable?��?������??����㨹*/
            if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
            {
                return AT_ERROR;
            }

            g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WIFI;

            return AT_OK;
        }
        else
        {
            return AT_ERROR;
        }
        /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, end */
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_ERROR;
    }

    /* �䨰?a��??����?D??��FRXON??o����?2???RXDIV����?? */
    if (AT_TSELRF_PATH_WCDMA_DIV == gastAtParaList[0].ulParaValue)
    {
        if (DRV_AGENT_DSP_RF_SWITCH_ON != g_stAtDevCmdCtrl.ucRxOnOff)
        {
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
            return AT_OK;
        }
        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON, ucIndex))
        {
            return AT_ERROR;
        }

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TSELRF_SET;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;

        /* ����???����?��|����1��?e���䨬? */
        return AT_WAIT_ASYNC_RETURN;
    }

    /* Modify by f62575 for V7�䨲??��?2?, 2012-04-07, Begin   */
    if ((AT_TSELRF_PATH_GSM != gastAtParaList[0].ulParaValue)
     && (AT_TSELRF_PATH_WCDMA_PRI != gastAtParaList[0].ulParaValue))
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7�䨲??��?2?, 2012-04-07, End   */

    /* ��?��|?D??��?��?D����a??D??��??DSP: D����a?������???����?Co??��??DSP��?��??����??��?������??OK */
    AT_GetTseLrfLoadDspInfo(gastAtParaList[0].ulParaValue, &bLoadDsp, &stTseLrf);
    if (VOS_TRUE == bLoadDsp)
    {
        if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                   gastAtClientTab[ucIndex].opId,
                                                   DRV_AGENT_TSELRF_SET_REQ,
                                                   &stTseLrf,
                                                   sizeof(stTseLrf),
                                                   I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TSELRF_SET;             /*����??�̡�?��2������?�꨺? */
            return AT_WAIT_ASYNC_RETURN;                                           /* �̨���y����2?��??t����?? */
        }
        else
        {
            return AT_ERROR;
        }
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_QryTseLrfPara
 1|?��?����?  : 2��?��?����?��?���䡤��??�̣���??��3?��??����D?��??��??????��??��?DD??��?��?????<path>
             ����D��????��?��?DD��?
             ?����y����?�̡�?��??��3?2����WIFI����??��??��??��??a?��^TSELRF: 7,0,1?��
 ��?��?2?��y  : VOS_UINT8 ucIndex ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32 ����???��DD?��1?3��1|?��?����|�䨪?��??
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??10��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_QryTseLrfPara(VOS_UINT8 ucIndex)
{

    /*DTS2012041102190 : h00135900 start in 2011-04-11 AT�䨲??����o?*/
    return atQryTselrfPara(ucIndex);

}

/*****************************************************************************
 o�� ��y ??  : AT_SetCmdlenPara
 1|?��?����?  : ???a�̣���?PC��?��??����?����?����?��?��???��yo��PC?����?�̣���?��?��?����?����?��?��???��y
             ???����?��?����?��3?SIMLOCK��y?Y��?��???����?����?BALONG?T��?D��?����???����??OK����?��1��
             ??1����??������3��?y3��?��DD
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_SetCmdlenPara(VOS_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (2 != gucAtParaIndex))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[0].ulParaValue > (AT_COM_BUFF_LEN - sizeof("AT")))
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_QryCmdlenPara
 1|?��?����?  : 2��?���̣���?��?�䨮?����??��?��?����?AT?����?��?��???��y��?��??��̣���?����1yAT��?��?��?�䨮
             ?����??����|��?��?��???��y��???��?��???��y?��2?�㨹o?AT?a��???��?��??��
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??2��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_QryCmdlenPara(VOS_UINT8 ucIndex)
{
    /*
      ��?3?�̣���?��?�䨮?����??��?��?����?AT?����?��?��???��y(AT_CMD_MAX_LEN - sizeof("AT"))��?
      ??��?��???��y?��2?�㨹o?AT?a��???��?��?��?��??��̣���?����1yAT��?��?��?�䨮?����??����|��?��?��???��y��?
      BALONG2��?��?����|��?��?��?3��?��?����?��?
      ?����?��?������???��D��?�䨮?��????��?1��???????��?T��|������?��?��|��?3?��?��?��?������?��?�䨮?��AT_CMD_MAX_LEN?��
    */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    (AT_COM_BUFF_LEN - VOS_StrLen("AT")),
                                                    AT_CMD_MAX_LEN);

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_UpdateMacPara
 1|?��?����?  : ?��D?MAC��??����?NV
             ��?��??��3?2??MAC��y������?��?
 ��?��?2?��y  : VOS_UINT8                           aucMac[]   MAC��??����?��?��?������??��
             VOS_UINT16                          usMacLength    MAC��??����?��?��?3��?��
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
             2������3��1|��?����??AT_OK
             ??����o?3��?��2?o?��������??AT_PHYNUM_LENGTH_ERR
             MT?��2?�䨪?����?����??AT_ERROR
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_UpdateMacPara(
    VOS_UINT8                           aucMac[],
    VOS_UINT16                          usMacLength
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulWifiGlobalMacOffset;
    VOS_UINT32                          ulPhyNumMacOffset;
    VOS_UINT8                           aucWifiGlobalMac[AT_MAC_ADDR_LEN];

    /* MAC��??��3��?��?��2��: ��?D?12?? */
    if (AT_PHYNUM_MAC_LEN != usMacLength)
    {
        return AT_PHYNUM_LENGTH_ERR;
    }

    /* MAC��??��??��??��??: 7AFEE22111E4=>7A:FE:E2:21:11:E4*/
    ulWifiGlobalMacOffset = 0;
    ulPhyNumMacOffset     = 0;
    for (ulLoop = 0; ulLoop < (AT_PHYNUM_MAC_COLON_NUM + 1); ulLoop++)
    {
        PS_MEM_CPY(&aucWifiGlobalMac[ulWifiGlobalMacOffset],
                   &aucMac[ulPhyNumMacOffset],
                   AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulWifiGlobalMacOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulPhyNumMacOffset     += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        aucWifiGlobalMac[ulWifiGlobalMacOffset] = ':';
        ulWifiGlobalMacOffset++;
    }

    aucWifiGlobalMac[AT_PHYNUM_MAC_LEN + AT_PHYNUM_MAC_COLON_NUM] = '\0';

    /* ?��D?MAC��??����?NV */
    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucWifiGlobalMac, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
         AT_WARN_LOG("AT_UpdateMacPara: Fail to write NV.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetTmodeAutoPowerOff
 1|?��?����?  : ��??��1??����?�����??����?��???E52��?��D?��??��3?��?????2��?��D?��?����??ERROR
             2��??��a?��?������?a��??��AT?����?��??��DD��??����?2��??��?����D��D��?��
             ��??�쨪��1y?��2a???����?��???���쨤�䨨����?��???��?��??y����?��DD
 ��?��?2?��y  : VOS_UINT8 ucIndex      ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��12??13��?
    ����    ??   : L00171473
    DT???����Y   : DTS2012121802573, TQE??����
  3.��?    ?��   : 2014?��2??14��?
    ����    ??   : w00167002
    DT???����Y   : L-C?��2������????:?a1??��o����y�̡�??
*****************************************************************************/
VOS_UINT32 AT_SetTmodeAutoPowerOff(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, begin */

    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, begin */
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhModeSet;
    /* Modified by w00167002 for L-C?��2������????, 2014-2-14, end */

    VOS_UINT8                             *pucSystemAppConfig;


    PS_MEM_SET(&stPhModeSet, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));

    pucSystemAppConfig                    = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* ����???��??Co?����?a1??��2��??��? */
        /* ?������?a��??��AT?����?��??��DD��?��??�쨪��1y?��2a???����?��???���쨤�䨨����?��???��?��??y����?��DD
           ��??����??��DD����3��o����???��?��??TD���̨���y����2?����??
        */

        /* Modified by w00167002 for L-C?��2������????, 2014-2-14, begin */
        stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;

        if (VOS_TRUE == TAF_MMA_PhoneModeSetReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPhModeSet))
        {
            return AT_OK;
        }
        /* Modified by w00167002 for L-C?��2������????, 2014-2-14, end */
        else
        {
            return AT_ERROR;
        }

    }
    /* Modified by s62952 for BalongV300R002 Build��??��???? 2012-02-28, end */

    return AT_ERROR;

}

/* Add by w00199382 for V7�䨲??��?2?, 2012-04-07, Begin   */

/*****************************************************************************
 o�� ��y ??  : AT_SDParamErrCode
 1|?��?����?  : SD?����?2?��y�䨪?������??�䨪?��??��?��|����
 ��?��?2?��y  : ?T
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??19��?
    ����    ??   : c64416
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_SDParamErrCode(VOS_VOID)
{
    if(0 == g_stATParseCmd.ucParaCheckIndex)
    {
        return AT_SD_CARD_OPRT_NOT_ALLOWED;
    }
    else if(1 == g_stATParseCmd.ucParaCheckIndex)
    {
        return AT_SD_CARD_ADDR_ERR;
    }
    else
    {
        return AT_SD_CARD_OTHER_ERR;
    }
}

/* Add by w00199382 for V7�䨲??��?2?, 2012-04-07, End   */

/*****************************************************************************
 o�� ��y ??  : AT_GetSpecificPort
 1|?��?����?  : ??��????������D����????��
 ��?��?2?��y  : VOS_UINT8                           ucPortType ???������D��
 ��?3?2?��y  : VOS_UINT32                         *pulPortPos ???��?��NV???D��???��?
             VOS_UINT32                         *pulPortNum NV???D��????��������y
 ���� ?? ?��  : ?T
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_VOID AT_GetSpecificPort(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           aucRewindPortStyle[],
    VOS_UINT32                         *pulPortPos,
    VOS_UINT32                         *pulPortNum
)
{
    VOS_UINT32                          ulLoop;

    *pulPortPos = AT_DEV_NONE;
    for (ulLoop = 0; ulLoop < AT_SETPORT_PARA_MAX_LEN; ulLoop++)
    {
        if (0 == aucRewindPortStyle[ulLoop])
        {
            break;
        }

        /* ???��?��?aucPortType��?������??����????��???����?????ulLoop?a???��?��NV???D��???��? */
        if (ucPortType == aucRewindPortStyle[ulLoop])
        {
            *pulPortPos = ulLoop;
        }
    }

    /* ???��?��?a0?����?��??-?����??T��?ulLoop?��?a�̣���?��????��������y */
    *pulPortNum = ulLoop;

    return;
}

/*****************************************************************************
 o�� ��y ??  : AT_ExistSpecificPort
 1|?��?����?  : ��?��?��??��???������D����????��
 ��?��?2?��y  : VOS_UINT8              ucPortType ???������D��
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             VOS_TRUE    ��??��???������D����????��
                                    VOS_FALSE 2?��??��???������D����????��
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��8??10��?
    ����    ??   : L00171473
    DT???����Y   : DTS2012082204471, TQE??����
*****************************************************************************/
VOS_UINT32 AT_ExistSpecificPort(VOS_UINT8 ucPortType)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ?��NV??en_NV_Item_Huawei_Dynamic_PID_Type??��?�̡�?���????�����䨬? */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_WARN_LOG("AT_ExistSpecificPort: Read NV fail!");
        return VOS_FALSE;
    }

    /* ?D??DIAG???����?��?��??-�䨰?a: ��??-�䨰?a?��?��?������??AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* 2��?��NV??en_NV_Item_Huawei_Dynamic_PID_Type?D��?��?��??-��??��DIAG?�� */
        AT_GetSpecificPort(ucPortType,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE != ulPortPos)
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}


/*****************************************************************************
 o�� ��y ??  : AT_OpenDiagPort
 1|?��?����?  : �䨰?aDIAG???��
 ��?��?2?��y  : ?T
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��8??10��?
    ����    ??   : L00171473
    DT???����Y   : DTS2012082204471, TQE??����
*****************************************************************************/
VOS_UINT32 AT_OpenDiagPort(VOS_VOID)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ?��NV??en_NV_Item_Huawei_Dynamic_PID_Type??��?�̡�?���????�����䨬? */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_WARN_LOG("AT_OpenDiagPort: Read NV fail!");
        return AT_ERROR;
    }

    /* ?D??DIAG???����?��?��??-�䨰?a: ��??-�䨰?a?��?��?������??AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* 2��?��NV??en_NV_Item_Huawei_Dynamic_PID_Type?D��?��?��??-��??��DIAG?�� */
        AT_GetSpecificPort(AT_DEV_DIAG,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE != ulPortPos)
        {
            return AT_OK;
        }

    }
    else
    {
        AT_WARN_LOG("AT_OpenDiagPort: en_NV_Item_Huawei_Dynamic_PID_Type is inactive!");
        return AT_OK;
    }

    /* DIAG???��2�����¨���?T?��??��?: ?��?������??AT_OK */
    if (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag)
    {
        return AT_OK;
    }

    /* ����?��DIAG???����??D??o��???��?�� */
    if (AT_SETPORT_PARA_MAX_LEN == ulPortNum)
    {
        return AT_OK;
    }

    stDynamicPidType.aucRewindPortStyle[ulPortNum] = AT_DEV_DIAG;

    /* ?��D????��?��o?��y?Y��?NV??en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_OpenDiagPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

/*****************************************************************************
 o�� ��y ??  : AT_CloseDiagPort
 1|?��?����?  : 1?��?DIAG???��
 ��?��?2?��y  : ?T
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             ATC����????
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��8??10��?
    ����    ??   : L00171473
    DT???����Y   : DTS2012082204471, TQE??����
*****************************************************************************/
VOS_UINT32 AT_CloseDiagPort(VOS_VOID)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;
    VOS_UINT32                          ulLoop;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = 0;
    ulPortNum = 0;


    /* ?��NV??en_NV_Item_Huawei_Dynamic_PID_Type??��?�̡�?���????�����䨬? */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseDiagPort: Read NV fail!");
        return AT_ERROR;
    }

    /* ?D??DIAG???����?��?��??-�䨰?a: ��??-�䨰?a?��?��?������??AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* 2��?��NV??en_NV_Item_Huawei_Dynamic_PID_Type?D��?��?��??-��??��DIAG?�� */
        AT_GetSpecificPort(AT_DEV_DIAG,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE == ulPortPos)
        {
            return AT_OK;
        }
    }
    else
    {
        return AT_OK;
    }

    /* DIAG???��2�����¨���?T?��??��?: ?��?������??AT_OK */
    if (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag)
    {
        return AT_OK;
    }

    /* ��?3yNV???D��?DIAG???�� */
    stDynamicPidType.aucRewindPortStyle[ulPortPos] = 0;
    ulPortNum--;
    for (ulLoop = ulPortPos; ulLoop < ulPortNum; ulLoop++)
    {
        stDynamicPidType.aucRewindPortStyle[ulLoop] = stDynamicPidType.aucRewindPortStyle[ulLoop + 1UL];
    }
    stDynamicPidType.aucRewindPortStyle[ulPortNum] = 0;

    /* ???������3�꨺y?Y����?��: ?D??o����?������?D?��??D��?�̨���???������?2??��?aMASS������?(0xa1,0xa2) */
    if (0 != ulPortNum)
    {
        if ((AT_DEV_CDROM == stDynamicPidType.aucRewindPortStyle[0])
         || (AT_DEV_SD == stDynamicPidType.aucRewindPortStyle[0]))
        {
            return AT_OK;
        }
    }

    /* ?��D????��?��o?��y?Y��?NV??en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseDiagPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

/*****************************************************************************
 o�� ��y ??  : AT_ExistSpecificPortChange
 1|?��?����?  : ��?��?��??��???������D����????����??������?T
 ��?��?2?��y  : VOS_UINT8                           ucPortType ???������D��
             VOS_UINT8                           aucOldRewindPortStyle[]��??��?���????��?��o?
             VOS_UINT8                           aucNewRewindPortStyle[]��??��o����????��?��o?
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             VOS_TRUE    ��??��???������D����????����??��
                                    VOS_FALSE 2?��??��???������D����????����??��
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y
  2.��?    ?��   : 2012?��8??10��?
    ����    ??   : L00171473
    DT???����Y   : DTS2012082204471, TQE??����
*****************************************************************************/
VOS_UINT32 AT_ExistSpecificPortChange(
    VOS_UINT8                           ucPortType,
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
)
{
    VOS_UINT32                          ulOldPortPos;
    VOS_UINT32                          ulNewPortPos;
    VOS_UINT32                          ulPortNum;


    ulOldPortPos = 0;
    ulNewPortPos = 0;
    ulPortNum    = 0;

    AT_GetSpecificPort(ucPortType, aucOldRewindPortStyle, &ulOldPortPos, &ulPortNum);
    AT_GetSpecificPort(ucPortType, aucNewRewindPortStyle, &ulNewPortPos, &ulPortNum);

    /* D???��??????��???�� */
    if ((AT_DEV_NONE == ulOldPortPos)
     && (AT_DEV_NONE != ulNewPortPos))
    {
        return VOS_TRUE;
    }

    /* ��?3y��??????��???�� */
    if ((AT_DEV_NONE != ulOldPortPos)
     && (AT_DEV_NONE == ulNewPortPos))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 o�� ��y ??  : AT_CheckSetPortRight
 1|?��?����?  : ��?��?��??��???������D����????����??��
 ��?��?2?��y  : VOS_UINT8                           aucOldRewindPortStyle[]��??��?���????��?��o?
             VOS_UINT8                           aucNewRewindPortStyle[]��??��o����????��?��o?
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32             AT_OK       ����?T?��2������1y
                                    AT_ERROR    ����?T?��2��2?����1y
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��1??3��?
    ����    ??   : f62575
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_CheckSetPortRight(
    VOS_UINT8                           aucOldRewindPortStyle[],
    VOS_UINT8                           aucNewRewindPortStyle[]
)
{
    VOS_UINT32                          ulRet;

    ulRet = AT_ExistSpecificPortChange(AT_DEV_DIAG,
                                       aucOldRewindPortStyle,
                                       aucNewRewindPortStyle);

    if ((VOS_TRUE == ulRet)
     && (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


/*****************************************************************************
 o�� ��y ??  : AT_SetHsspt
 1|?��?����?  : ����??RRC��?��?D??��,o����y��?2?��y?y3��D??��2a��??��???��?����?.
 ��?��?2?��y  : ucIndex    - ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : ����??3?�䨪D??��?��OK
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��4??21��?
    ����    ??   : l60609
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_SetHsspt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;

    /* 2?��y?��2�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    /* 2?��y1y?�� */
    if (gucAtParaIndex != 1)
    {
        return AT_DPAUPA_ERROR;
    }

    /* ?��2����?��??a3y��y?Y����?��,?��?a3y��������??3?�䨪D??��:ErrCode:0 */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    ucRRCVer = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �̡¨�?D��NV?��?��o����y: AT_WriteRrcVerToNV,����??2������?��1? */
    if (VOS_OK == AT_WriteRrcVerToNV(ucRRCVer))
    {
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_SetHsspt:WARNING:Write NV failed!");
        return AT_DPAUPA_ERROR;
    }
}

/*****************************************************************************
 o�� ��y ??  : AT_QryHsspt
 1|?��?����?  : 2��?��RRC��?��?D??��
 ��?��?2?��y  : ucIndex - ��??��?�¨�y
 ��?3?2?��y  : ?T
 ���� ?? ?��  : ����??3?�䨪D??��?��OK
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��4??21��?
    ����    ??   : l60609
    DT???����Y   : D?����3��o����y
*****************************************************************************/
VOS_UINT32 AT_QryHsspt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* 2?��y?��2�� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    ulResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (VOS_OK == ulResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}

/*****************************************************************************
 o�� ��y ??  : AT_TestHsicCmdPara
 1|?��?����?  : HSIC�����̨�?����?2a��??����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��04??19��?
    ����    ??   : l00198894
    DT???����Y   : AP-Modem??��????��????D???o����y
  2.��?    ?��   : 2012?��8??13��?
    ����    ??   : l60609
    DT???����Y   : MUX:???��MUX�����̨���?��|����
*****************************************************************************/
VOS_UINT32 AT_TestHsicCmdPara(VOS_UINT8 ucIndex)
{
    /* �����̨�?��2�� */
    /* Modified by L60609 for MUX��?2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��?2012-08-13,  End */
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : At_TestTdsScalibPara
 1|?��?����?  : ^SCALIB2a��??����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��05??30��?
    ����    ??   : z00212940
    DT???����Y   : TDSD???o����y

*****************************************************************************/
VOS_UINT32 At_TestTdsScalibPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                           usLength;

    usLength = 0;
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s:%s", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        AT_TDS_SCALIB_TEST_STR);
    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_TestSimlockUnlockPara
 1|?��?����?  : ^SIMLOCKUNLOCK2a��??����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2012?��9??19��?
    ����    ??   : ��?��??��/00198894
    DT???����Y   : STK213?��?D??��DCMD��?��?a����????D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_TestSimlockUnlockPara( VOS_UINT8 ucIndex )
{
    /* �����̨�?��2�� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (\"NET\",\"NETSUB\",\"SP\")",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_String2Hex
 1|?��?����?  : ����3����?��?��?��a16????��y1|?��
 ��?��?2?��y  : nptr [in/out] ��?��?��?��?��?��??����Y????
             usLen [in] ��?��?��?��?��?��?3��?��
 ��?3?2?��y  : pRtn [in/out] ������?��?��?��a???����???D��?��
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
*****************************************************************************/
VOS_UINT32 AT_String2Hex( VOS_UINT8 *nptr,VOS_UINT16 usLen, VOS_UINT32 *pRtn)
{
    VOS_UINT32                          c     = 0;         /* current Char */
    VOS_UINT32                          total = 0;         /* current total */
    VOS_UINT8                           Length = 0;        /* current Length */

    c = (VOS_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else if( (c  >= 'a') && (c  <= 'f') )
        {
            c  = c  - 'a' + 10;
        }
        else if( (c  >= 'A') && (c  <= 'F') )
        {
            c  = c  - 'A' + 10;
        }
        else
        {
            return VOS_ERR;
        }

        if(total > 0x0FFFFFFF)              /* ���騦�������a */
        {
            return VOS_ERR;
        }
        else
        {
            total = (total << 4) + c;       /* accumulate digit */
            c = (VOS_UINT32)(*(nptr++));    /* get next Char */
        }
    }
     /* return result, negated if necessary */
    *pRtn = total;
    return AT_SUCCESS;
}

/*****************************************************************************
 o�� ��y ??  : AT_NVWRGetParaInfo
 1|?��?����?  : ??��?��?��?2?��yD??��
 ��?��?2?��y  : *pucPara  :
             *pucValue :
             **pucParaDst

 ��?3?2?��y  :
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
*****************************************************************************/
VOS_UINT32 AT_NVWRGetItemValue( VOS_UINT8 *pucPara,  VOS_UINT8 *pucValue,  VOS_UINT8 **pucParaDst)
{
    VOS_UINT32                          ulTmp = 0;
    VOS_UINT8                          *pucStart = pucPara;
    VOS_UINT16                          usLen = 0;
    VOS_UINT8                          *pucEnd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* �̡¨�?��?��?��?����?��pucPara,pucValue,pucParaDst2??aNULL */

    /* ?����?�̨���???2?��?' '��?��?��? */
    while(' ' == *pucStart)
    {
        pucStart++;
    }

    if(' ' == *(pucStart+1))
    {
        usLen = 1;
        pucEnd = pucStart+2;
    }
    else if(' ' == *(pucStart+2))
    {
        usLen = 2;
        pucEnd = pucStart+3;
    }
    else
    {
        return VOS_ERR;
    }

    ulRet = AT_String2Hex(pucStart, usLen, &ulTmp);
    if((VOS_OK != ulRet) || (ulTmp > 0xff))
    {
        return VOS_ERR;
    }

    *pucValue = (VOS_UINT8)ulTmp;
    *pucParaDst = pucEnd;

    return VOS_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_NVWRGetParaInfo
 1|?��?����?  : ^NVWRITE?����?��|����o����y
 ��?��?2?��y  :
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
*****************************************************************************/
VOS_UINT32 AT_NVWRGetParaInfo( AT_PARSE_PARA_TYPE_STRU * pstPara, VOS_UINT8 * pu8Data, VOS_UINT32 * pulLen)
{
    VOS_UINT32                          ulNum = 0;
    VOS_UINT8                          *pu8Start   = VOS_NULL_PTR;
    VOS_UINT8                          *pu8ParaTmp = VOS_NULL_PTR;
    VOS_UINT16                          usLen = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          i = 0;

    /* �̡¨�?��?��?��?����?��pstPara,pu8Data2??aNULL */

    pu8Start = pstPara->aucPara;
    usLen= pstPara->usParaLen;

    if(usLen < AT_PARA_MAX_LEN)
    {
        pstPara->aucPara[usLen] = ' ';
    }
    else
    {
        return VOS_ERR;
    }

    ulNum = 0;
    for(i = 0; i < usLen; )
    {
        ulRet = AT_NVWRGetItemValue(pu8Start, (pu8Data+ulNum), &pu8ParaTmp);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            return ulRet;
        }

        ulNum++;

        /* ��??��128?? */
        /*MAX_NV_NUM_PER_PARA */
        if(ulNum == 128)
        {
            break;
        }

        if(pu8ParaTmp >= (pu8Start+usLen))
        {
            break;
        }

        i += (VOS_UINT16)(pu8ParaTmp - pu8Start);
        pu8Start = pu8ParaTmp;
    }

    *pulLen = ulNum;
    return VOS_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetNVReadPara
 1|?��?����?  : ^NVREAD?����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
*****************************************************************************/
VOS_UINT32 AT_SetNVReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvId  = 0;
    VOS_UINT32                          ulNvLen = 0;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          i       = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    VOS_UINT32                          ulRet;

    /* 2?��y?��2�� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        g_ulNVRD = 1;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2?��y1y?�� */
    if(gucAtParaIndex > 1)
    {
        g_ulNVRD = 2;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2?��y?a?? */
    if(0 == gastAtParaList[0].usParaLen)
    {
        g_ulNVRD = 3;
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        usNvId = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    }

    ulRet = NV_GetLength(usNvId, &ulNvLen);

    if(VOS_OK != ulRet)
    {
        g_ulNVRD = 4;
        return AT_ERROR;
    }

    /* 3��?���䨮����128��???��??��128??��??��*/
    pucData = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, ulNvLen);
    if(VOS_NULL_PTR == pucData)
    {
        g_ulNVRD = 5;
        return AT_ERROR;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVReadPara:Get modem id fail");

        PS_MEM_FREE(WUEPS_PID_AT, pucData);

        g_ulNVWR =8;
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(enModemId, usNvId, (VOS_VOID*)pucData, ulNvLen);

    if(VOS_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);

        g_ulNVRD = 6;
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr,
        "^NVRD: %d,", ulNvLen);

    for(i = 0; i < ulNvLen; i++)
    {
        if(0 == i)
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,"%02X", pucData[i]);
        }
        else
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen," %02X", pucData[i]);
        }
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucData);
    g_ulNVRD = 7;
    return AT_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetNVReadPara
 1|?��?����?  : ^NVWRITE?����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
  2.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : NVWR?����?��2��?????
*****************************************************************************/
VOS_UINT32 AT_SetNVWritePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvId = 0;
    VOS_UINT16                          usNvTotleLen = 0;
    VOS_UINT32                          ulNvLen = 0; /* VOS_UINT16 -> VOS_UINT32 */
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulNvNum = 0; /* VOS_UINT16 -> VOS_UINT32 */
    VOS_UINT8                           au8Data[128] = {0};/* MAX_NV_NUM_PER_PARA */
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    VOS_UINT32                          i = 0;
    VOS_UINT32                          ulRet;

    gstAtSendData.usBufLen = 0;

    /* 2?��y?��2�� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        g_ulNVWR =1;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 2?��y?a?? */
    if((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (0 == gastAtParaList[2].usParaLen))
    {
        g_ulNVWR =2;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usNvId = (VOS_UINT16)gastAtParaList[0].ulParaValue;

    if (VOS_TRUE != AT_IsNVWRAllowedNvId(usNvId))
    {
        g_ulNVWR = 10;
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    (VOS_VOID)vos_printf("\n atSetNVWRPara usNvId = %d\n",usNvId);

    usNvTotleLen = (VOS_UINT16)gastAtParaList[1].ulParaValue;
    (VOS_VOID)vos_printf("\n atSetNVWRPara usNvTotleLen = %d\n",usNvTotleLen);

    pucData = PS_MEM_ALLOC(WUEPS_PID_AT, usNvTotleLen);
    if(VOS_NULL_PTR == pucData)
    {
        g_ulNVWR =3;
        return AT_ERROR;
    }

    i = 0;
    while(0 != gastAtParaList[2UL + i].usParaLen)
    {
        ulRet = AT_NVWRGetParaInfo((AT_PARSE_PARA_TYPE_STRU*)(&(gastAtParaList[2UL + i])), au8Data, &ulNvNum);

        if(VOS_OK != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =4;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ��?1?2?��y��?3��?���䨮����128��??������??����㨹 */
        /*MAX_NV_NUM_PER_PARA */
        if(ulNvNum > 128)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =5;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ��?1?��??����?2?��y??��y�䨮��������3��?�� */
        if((ulNvLen+ulNvNum) > usNvTotleLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucData);
            g_ulNVWR =6;
            return AT_CME_INCORRECT_PARAMETERS;
        }

        PS_MEM_CPY((pucData + ulNvLen), au8Data, ulNvNum);

        ulNvLen += ulNvNum;
        i++;

        if(i >= (AT_MAX_PARA_NUMBER-2))
        {
            break;
        }
    }

    /* ��?1?��??����?2?��y??��y��?����3��?��2??���̨� */
    if(ulNvLen != usNvTotleLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =7;
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVWritePara:Get modem id fail");
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =8;
        return AT_ERROR;
    }

    ulRet = NV_WriteEx(enModemId, usNvId, (VOS_VOID*)pucData, usNvTotleLen);

    if(VOS_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucData);
        g_ulNVWR =9;

        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucData);
    g_ulNVWR =10;

    return AT_OK;
}


/*****************************************************************************
 o�� ��y ??  : AT_SetNVWRPartPara
 1|?��?����?  : ^NVWRLEN����???����?��|����
 ��?��?2?��y  : VOS_UINT8 ucClientId
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��4??21��?
    ����    ??   : s00318873
    DT???����Y   : D?����3��o����y for DTS2015042202710

  2.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : NVWR?����?��2��?????

*****************************************************************************/
VOS_UINT32 AT_SetNVWRPartPara(VOS_UINT8 ucClientId)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usNVID;
    VOS_UINT32                          ulNVWrTotleLen;
    VOS_UINT32                          ulNVLen;
    VOS_UINT16                          usNVWrLen;
    VOS_UINT8                          *pucNvWrData = VOS_NULL_PTR;
    VOS_UINT32                          ulNVNum;
    VOS_UINT32                          i;
    VOS_UINT8                           aucData[128];
    VOS_UINT16                          usOffset;
    MODEM_ID_ENUM_UINT16                enModemId;

    i                       = 0;
    ulNVLen                 = 0;
    gstAtSendData.usBufLen  = 0;
    ulNVWrTotleLen          = 0;
    PS_MEM_SET(aucData,0,sizeof(aucData));

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if( (0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen)
     || (0 == gastAtParaList[2].usParaLen)
     || (0 == gastAtParaList[3].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usNVID       = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    usOffset     = (VOS_UINT16)gastAtParaList[1].ulParaValue;
    usNVWrLen    = (VOS_UINT16)gastAtParaList[2].ulParaValue;

    if (VOS_TRUE != AT_IsNVWRAllowedNvId(usNVID))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    /* check param#3 usNVWrLen */
    if (usNVWrLen == 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* get NV length */
    ulRet        = NV_GetLength(usNVID, &ulNVWrTotleLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* check param#2 usOffset */
    if(((VOS_UINT32)usOffset > (ulNVWrTotleLen - 1)) || ((VOS_UINT32)(usOffset + usNVWrLen) > ulNVWrTotleLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pucNvWrData = PS_MEM_ALLOC(WUEPS_PID_AT, usNVWrLen);
    if(NULL == pucNvWrData)
    {
        return AT_ERROR;
    }

    /* get NV value form param#4\5\...\#16 */
    while(0 != gastAtParaList[3UL + i].usParaLen)
    {
        ulRet = AT_NVWRGetParaInfo((AT_PARSE_PARA_TYPE_STRU*)(&(gastAtParaList[3UL + i])), aucData, (VOS_UINT32 *)&ulNVNum);
        if(ERR_MSP_SUCCESS != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(ulNVNum > 128)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if((ulNVLen+ulNVNum) > usNVWrLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        PS_MEM_CPY(((VOS_UINT8*)pucNvWrData + ulNVLen), (VOS_UINT8*)aucData, ulNVNum);

        ulNVLen += ulNVNum;
        i++;

        if(i >= (AT_MAX_PARA_NUMBER - 3))
        {
            break;
        }

    }

    /* check all the nv value have the exact length by param#3 */
    if(ulNVLen != usNVWrLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = AT_GetModemIdFromClient(ucClientId, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetNVWritePara:Get modem id fail");
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    if (enModemId >= MODEM_ID_BUTT)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    ulRet = NV_WritePartEx(enModemId, usNVID, usOffset, (VOS_VOID*)pucNvWrData, usNVWrLen);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);
        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucNvWrData);

    return AT_OK;
}


/*****************************************************************************
 o�� ��y ??  : AT_GetNvRdDebug
 1|?��?����?  : ??��?NV?��D��̡�2aD??��
 ��?��?2?��y  :
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_VOID
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��06??28��?
    ����    ??   : d00212987
    DT???����Y   : ��??2����???-��DAT ?����??��D��NV2������
*****************************************************************************/
VOS_VOID AT_GetNvRdDebug(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n g_ulNVRD=0x%x \n",g_ulNVRD);
    (VOS_VOID)vos_printf("\n g_ulNVWR=0x%x \n",g_ulNVWR);
}

/*****************************************************************************
 o�� ��y ??  : AT_QryFPllStatusPara
 1|?��?����?  : 2��?��G?��W PLL���䨬?
 ��?��?2?��y  : ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��11??29��?
    ����    ??   : L00256032
    DT???����Y   : Added for PLL status query
*****************************************************************************/
VOS_UINT32 AT_QryFPllStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulReceiverPid;
    AT_PHY_RF_PLL_STATUS_REQ_STRU      *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMsgId;
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
            ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFPllStatusPara(ucIndex);
    }
    /*?D??�̡�?��?����??�꨺?��????��3?G/W*/
    if (AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_WPHY);
        usMsgId       = ID_AT_WPHY_RF_PLL_STATUS_REQ;
    }
    else if ( (AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
            ||(AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode) )
    {
        ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
        usMsgId       = ID_AT_GPHY_RF_PLL_STATUS_REQ;
    }

    else
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ����??AT_PHY_RF_PLL_STATUS_REQ_STRU???�� */
    ulLength = sizeof(AT_PHY_RF_PLL_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_PHY_RF_PLL_STATUS_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_QryFPllStatusPara: Alloc msg fail!");
        return AT_ERROR;
    }

    /* ��?3????�� */
    pstMsg->ulReceiverPid = ulReceiverPid;
    pstMsg->usMsgID       = usMsgId;
    pstMsg->usRsv1        = 0;
    pstMsg->usDspBand     = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->usRsv2        = 0;

    /* ?��??��|PHY����?��???�� */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_QryFPllStatusPara: Send msg fail!");
        return AT_ERROR;
    }

    /* ����??�̡�?��2�����¨���D�� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPLLSTATUS_QRY;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    /* ����???����?��|����1��?e���䨬? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 o�� ��y ??  : At_RfPllStatusCnfProc
 1|?��?����?  : AT��|����GPHY/WPHY???���?PLL���䨬?2��?��?����|???��
 ��?��?2?��y  : pstMsg
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_VOID
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2013?��11??29��?
    ����    ??   : L00256032
    DT???����Y   : Added for PLL status query
*****************************************************************************/
VOS_VOID At_RfPllStatusCnfProc(PHY_AT_RF_PLL_STATUS_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ??��?��?��?�����?��?��??��?�¨�y */
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_FPLLSTATUS_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RfPllStatusCnfProc: CmdCurrentOpt is not AT_CMD_FPLLSTATUS_QRY!");
        return;
    }

    /* ?��??AT���䨬? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d,%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstMsg->usTxStatus,
                                       pstMsg->usRxStatus);

    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, AT_OK);

    return;
}

/*****************************************************************************
 o�� ��y ??  : AT_QryFpowdetTPara
 1|?��?����?  : ?��??��??��PDEG?��
 ��?��?2?��y  : ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2014?��5??6��?
    ����    ??   : d00212987
    DT???����Y   : Added for PDEA status query
*****************************************************************************/
VOS_UINT32 AT_QryFpowdetTPara(VOS_UINT8 ucIndex)
{
    AT_PHY_POWER_DET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

    /*?D??�̡�?��?����??�꨺?��????��3?W*/
    if (AT_RAT_MODE_WCDMA != g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ����??AT_PHY_POWER_DET_REQ_STRU???�� */
    ulLength = sizeof(AT_PHY_POWER_DET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_PHY_POWER_DET_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("AT_QryFpowdetTPara: Alloc msg fail!");
        return AT_ERROR;
    }

    /* ��?3????�� */
    pstMsg->ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_WPHY);
    pstMsg->usMsgID       = ID_AT_WPHY_POWER_DET_REQ;
    pstMsg->usRsv         = 0;

    /* ?��??��|PHY����?��???�� */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("AT_QryFpowdetTPara: Send msg fail!");
        return AT_ERROR;
    }

    /* ����??�̡�?��2�����¨���D�� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPOWDET_QRY;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    /* ����???����?��|����1��?e���䨬? */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 o�� ��y ??  : At_RfFPOWDETCnfProc
 1|?��?����?  : AT��|����WPHY???��?����?��???��??��PDEG?��
 ��?��?2?��y  : pstMsg
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_VOID

 DT??��������      :
  1.��?    ?��   : 2014?��5??6��?
    ����    ??   : d00212987
    DT???����Y   : Added for PDEA status query
*****************************************************************************/
VOS_VOID At_RfFpowdetTCnfProc(PHY_AT_POWER_DET_CNF_STRU *pstMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;

    /* ??��?��?��?�����?��?��??��?�¨�y */
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_CMD_FPOWDET_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RfFPOWDETCnfProc: CmdCurrentOpt is not AT_CMD_FPOWDET_QRY!");
        return;
    }

    /* ?��??AT���䨬? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��|??����2?��a?����?��?1?����???��?a0x7FFF?��?a?TD��?�̡�???2��?��??����??ERROR */
    if(0x7FFF == pstMsg->sPowerDet)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstMsg->sPowerDet);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}

/*****************************************************************************
 o�� ��y ??  : AT_SetNvwrSecCtrlPara
 1|?��?����?  : ^NVWRSECCTRL����???����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : D???o����y
*****************************************************************************/
VOS_UINT32 AT_SetNvwrSecCtrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_MTA_NVWRSECCTRL_SET_REQ_STRU     stNvwrSecCtrl;
    VOS_UINT16                          usLength;

    /* ??2?��?��?3?��??�� */
    PS_MEM_SET(&stNvwrSecCtrl, 0x00, sizeof(stNvwrSecCtrl));

    /* 2?��y?��2�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* 2?��y1y?�� */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ?��2��??����2?��y3��?�� */
    if (AT_NVWRSECCTRL_PARA_SECTYPE_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����??��2��?????����D�� */
    stNvwrSecCtrl.ucSecType = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ??��?��?��?2?��y��a???a??���� */
    usLength = gastAtParaList[1].usParaLen;
    if ( (2 == gucAtParaIndex)
      && (AT_RSA_CIPHERTEXT_PARA_LEN == usLength) )
    {
        if ( (AT_SUCCESS == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &usLength))
          && (AT_RSA_CIPHERTEXT_LEN == usLength) )
        {
            stNvwrSecCtrl.ucSecStrFlg = VOS_TRUE;
            PS_MEM_CPY(stNvwrSecCtrl.aucSecString, gastAtParaList[1].aucPara, AT_RSA_CIPHERTEXT_LEN);
        }
    }

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_NVWRSECCTRL_SET_REQ,
                                      &stNvwrSecCtrl,
                                      sizeof(stNvwrSecCtrl),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetNvwrSecCtrlPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����??AT?��?�����̨�?��?���䨬??a�̨���y����2?����?? */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVWRSECCTRL_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 o�� ��y ??  : AT_RcvMtaNvwrSecCtrlSetCnf
 1|?��?����?  : AT?��?����?��?MTA?��?��???���|����o����y
 ��?��?2?��y  : VOS_VOID *pMsg
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : D???o����y
*****************************************************************************/
VOS_UINT32 AT_RcvMtaNvwrSecCtrlSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_RESULT_CNF_STRU             *pstResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 3?��??�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstResult       = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ����1yClientId??��?ucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ?D??�̡�?��2�����¨���D����?��??aAT_CMD_NVWRSECCTRL_SET */
    if (AT_CMD_NVWRSECCTRL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaNvwrSecCtrlSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ?��??AT���䨬? */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ?D?????��???��?D��?�䨪?��?? */
    if (MTA_AT_RESULT_NO_ERROR == pstResult->enResult)
    {
        /* 3��1|��?��?3?OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* ����㨹��?��?3?ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* �̡¨�?At_FormatResultData����?��?����??��1? */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_QryNvwrSecCtrlPara
 1|?��?����?  : ^NWSECCTRL2��?��?����?��|����o����y
 ��?��?2?��y  : VOS_UINT8 ucIndex
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_UINT32
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : D???o����y
*****************************************************************************/
VOS_UINT32 AT_QryNvwrSecCtrlPara(VOS_UINT8 ucIndex)
{
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    VOS_UINT32                          ulResult;

    /* 2?��y3?��??�� */
    ulResult = AT_ERROR;
    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));

    /* DT??��2��?????NV */
    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvwrSecCtrlNV.ucSecType);
    }

    return ulResult;
}

/*****************************************************************************
 o�� ��y ??  : AT_IsNVWRAllowedNvId
 1|?��?����?  : ?D???����?^NVWR?��^NVWREX?����?DT??��?NV_ID
 ��?��?2?��y  : usNvId
 ��?3?2?��y  : ?T
 ���� ?? ?��  : VOS_TRUE   -- ?��D��DT??
             VOS_FLASE  -- 2??��D��DT??
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��04??04��?
    ����    ??   : l00198894
    DT???����Y   : D???o����y
*****************************************************************************/
VOS_BOOL AT_IsNVWRAllowedNvId(VOS_UINT16 usNvId)
{
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBlackListNum;

    /* 2?��y3?��??�� */
    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));

    /* ?����?��2��?????NV */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        AT_ERR_LOG("AT_IsNVWRAllowedNvId: NV_ReadEx fail!");
        return VOS_FALSE;
    }

    switch (stNvwrSecCtrlNV.ucSecType)
    {
        case AT_NVWR_SEC_TYPE_OFF:
            return VOS_TRUE;

        case AT_NVWR_SEC_TYPE_ON:
            return VOS_FALSE;

        case AT_NVWR_SEC_TYPE_BLACKLIST:
            ucBlackListNum = (stNvwrSecCtrlNV.ucBlackListNum <= TAF_NV_BLACK_LIST_MAX_NUM) ?
                             stNvwrSecCtrlNV.ucBlackListNum : TAF_NV_BLACK_LIST_MAX_NUM;
            for (ucLoop = 0; ucLoop < ucBlackListNum; ucLoop++)
            {
                if (usNvId == stNvwrSecCtrlNV.ausBlackList[ucLoop])
                {
                    return VOS_FALSE;
                }
            }
            return VOS_TRUE;

        default:
            AT_ERR_LOG1("AT_IsNVWRAllowedNvId: Error SecType:", stNvwrSecCtrlNV.ucSecType);
            break;
    }

    return VOS_FALSE;
}

/*****************************************************************************
o�� ��y ??  :AT_AsciiToHex
1|?��?����?  :��a??��?��?��???��?
��?��?2?��y  :

��?3?2?��y  :?T
���� ?? ?��  :VOS_OK    :����㨹
           VOS_ERR   :3��1|

DT??????  :
1. ��?    ?��   : 2015?��07??23��?
   ����    ??   : z00316370
   DT???����Y   : Creat
*****************************************************************************/

VOS_UINT32 AT_AsciiToHex(
    VOS_UINT8                          *pucSrc,
    VOS_UINT8                          *pucDst
)
{

    if (( *pucSrc >= '0') && (*pucSrc <= '9')) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - '0');
    }
    else if ( (*pucSrc >= 'a') && (*pucSrc <= 'f') ) /* the number is a-f */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - 'a') + 0x0a;
    }
    else if ( (*pucSrc >= 'A') && (*pucSrc <= 'F') ) /* the number is A-F */
    {
        *pucDst = (VOS_UINT8)(*pucSrc - 'A') + 0x0a;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
o�� ��y ??  :AT_AsciiToHexCode
1|?��?����?  :��a??��?��?��???��?��???D��,"1234"->0x3412
��?��?2?��y  :

��?3?2?��y  :?T
���� ?? ?��  :VOS_OK    :����㨹
           VOS_ERR   :3��1|

DT??????  :
1. ��?    ?��   : 2015?��7??23��?
   ����    ??   : z00316370
   DT???����Y   : Creat
*****************************************************************************/

VOS_UINT32 AT_AsciiToHexCode_Revers(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDst
)
{
    VOS_INT16                           sLoop1;
    VOS_UINT16                          usLoop2;
    VOS_UINT8                           ucTemp1;
    VOS_UINT8                           ucTemp2;
    VOS_UINT32                          ulRslt;

    sLoop1 = (VOS_INT16)(usDataLen - 1);
    for (usLoop2 = 0; sLoop1 >= 0; sLoop1--, usLoop2++)
    {
        ulRslt = AT_AsciiToHex(&(pucSrc[sLoop1]), &ucTemp1);
        if (VOS_ERR == ulRslt)
        {
            return VOS_ERR;
        }

        sLoop1--;

        ulRslt = AT_AsciiToHex(&(pucSrc[sLoop1]), &ucTemp2);
        if (VOS_ERR == ulRslt)
        {
            return VOS_ERR;
        }

        pucDst[usLoop2] = (VOS_UINT8)((ucTemp2 << 4) | ucTemp1);
    }

    return VOS_OK;
}

/*****************************************************************************
 o�� ��y ??  : AT_Hex2Ascii
 1|?��?����?  : ??��?����????��y��?��?��?��?��a??3��ASCII??������?��?��y��?��?��?��?,??D��,0x3412 --> "1234"
 ��?��?2?��y  : VOS_UINT8  aucHex[]��?????��y��?��?��?��?������??��
             VOS_UINT32 ulLength      ��?????��y��?��?��?��?3��?��
 ��?3?2?��y  : VOS_UINT8  aucAscii[]    ASCII??������?��?��y��?��?��?��?������??��
 ���� ?? ?��  : VOS_UINT32 ��a???��1?: VOS_OK��a??3��1|��?VOS_ERR��a??����㨹
 �̡¨�?o����y  :
 ��?�̡�o����y  :

 DT??��������      :
  1.��?    ?��   : 2015?��7??18��?
    ����    ??   : z00316370
    DT???����Y   : D?����3��o����y

*****************************************************************************/
VOS_UINT32 AT_Hex2Ascii_Revers(
    VOS_UINT8                           aucHex[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_INT32                           lLoopSrc;
    VOS_UINT32                          ulLoopDest;
    VOS_UINT8                           ucTemp;

    lLoopSrc = (VOS_INT32)(ulLength - 1);
    for (ulLoopDest = 0; lLoopSrc >= 0; lLoopSrc--, ulLoopDest++)
    {
        ucTemp = (aucHex[lLoopSrc]>>4) & 0x0F;
        if (ucTemp < 10)
        {
            /* 0~9 */
            aucAscii[ulLoopDest] = ucTemp + 0x30;
        }
        else
        {
            /* a~f */
            aucAscii[ulLoopDest] = ucTemp + 0x37;
        }

        ulLoopDest++;
        ucTemp = aucHex[lLoopSrc] & 0x0F;
        if (ucTemp < 10)
        {
            /* 0~9 */
            aucAscii[ulLoopDest] = ucTemp + 0x30;
        }
        else
        {
            /* a~f */
            aucAscii[ulLoopDest] = ucTemp + 0x37;
        }
    }

    return VOS_OK;
}





