

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
#include "AtTestParaCmd.h"


#include "at_lte_common.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_BASICCMD_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* �������ޱ�־�궨��

#define CMD_TBL_E5_IS_LOCKED        (0x00000001)     ����E5�������Ƶ�����
#define CMD_TBL_PIN_IS_LOCKED       (0x00000002)     ����PIN���������Ƶ�����
#define CMD_TBL_IS_E5_DOCK          (0x00000004)     E5 DOCK����
#define CMD_TBL_CLAC_IS_INVISIBLE   (0x00000008)     +CLAC�����в������ʾ������

*/

/* AT_PAR_CMD_ELEMENT_STRU g_astAtBasicCmdTbl[] = {}; */

/* ʾ��: ^CMDX �����ǲ���E5���뱣���������+CLAC�о���������ʱ����ʾ����һ�������ǲ���˫���ŵ��ַ���,
        �ڶ��������Ǵ�˫���ŵ��ַ����������������������Ͳ���

   !!!!!!!!!!!ע��: param1��param2��ʾ����ʵ�ʶ�������ʱӦ��������ļ��(����߽���Ч��)!!!!!!!!!!!!!

    {AT_CMD_CMDX,
    At_SetCmdxPara, AT_SET_PARA_TIME, At_QryCmdxPara, AT_QRY_PARA_TIME, At_TestCmdxPara, AT_NOT_SET_TIME,
    AT_ERROR, CMD_TBL_E5_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE,
    (VOS_UINT8*)"^CMDX", (VOS_UINT8*)"(@param1),(param2),(0-255)"},
*/

AT_PAR_CMD_ELEMENT_STRU g_astAtBasicCmdTbl[] =
{
    /* CS */
    {AT_CMD_H,
    At_SetHPara,    AT_DETACT_PDP_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,    At_CmdTestProcOK,   AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"H", (VOS_UINT8*)"(0)"},

    {AT_CMD_A,
    At_SetAPara,    AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"A", VOS_NULL_PTR},

    {AT_CMD_D,
    At_SetDPara,    AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"D", VOS_NULL_PTR},


    {AT_CMD_S0,
    At_SetS0Para,   AT_NOT_SET_TIME,    At_QryS0Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"S0", (VOS_UINT8*)"(0-255)"},

    /* ATC */
    {AT_CMD_S3,
    At_SetS3Para,   AT_NOT_SET_TIME,    At_QryS3Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"S3",   (VOS_UINT8*)"(0-127)"},

    {AT_CMD_S4,
    At_SetS4Para,   AT_NOT_SET_TIME,    At_QryS4Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"S4",   (VOS_UINT8*)"(0-127)"},

    {AT_CMD_S5,
    At_SetS5Para,   AT_NOT_SET_TIME,    At_QryS5Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"S5",   (VOS_UINT8*)"(0-127)"},

    {AT_CMD_S6,
    At_SetS6Para,   AT_NOT_SET_TIME,    At_QryS6Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"S6",   (VOS_UINT8*)"(2-10)"},

    {AT_CMD_S7,
    At_SetS7Para,   AT_NOT_SET_TIME,    At_QryS7Para,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"S7",   (VOS_UINT8*)"(1-255)"},

    {AT_CMD_E,
    At_SetEPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_E5_IS_LOCKED | CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"E",    (VOS_UINT8*)"(0,1)"},

    {AT_CMD_V,
    At_SetVPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"V",    (VOS_UINT8*)"(0,1)"},

    {AT_CMD_I,
    At_SetMsIdInfo, AT_SET_PARA_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_E5_IS_LOCKED | CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"I",    (VOS_UINT8*)"(0-255)"},

    {AT_CMD_T,
    At_SetTPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (TAF_UINT8*)"T",    TAF_NULL_PTR},

    {AT_CMD_P,
    At_SetPPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"P",    TAF_NULL_PTR},

    {AT_CMD_X,
    At_SetXPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"X",    (VOS_UINT8*)"(0-4)"},

    {AT_CMD_Z,
    At_SetZPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"Z",    (VOS_UINT8*)"(0)"},

    {AT_CMD_Q,
    At_SetQPara,    AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"Q",    (VOS_UINT8*)"(0,1)"},

    {AT_CMD_AMP_C,
    At_SetAmpCPara, AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"&C",    (VOS_UINT8*)"(0-2)"},

    {AT_CMD_AMP_D,
    At_SetAmpDPara, AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"&D",    (VOS_UINT8*)"(0-2)"},


    {AT_CMD_AMP_F,
    atSetNVFactoryRestore,    AT_NOT_SET_TIME,   VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"&F",    (VOS_UINT8*)"(0)"},


    {AT_CMD_L,
    AT_SetLPara, AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"L",    (VOS_UINT8*)"(0)"},

    {AT_CMD_M,
    AT_SetMPara, AT_NOT_SET_TIME,    VOS_NULL_PTR,   AT_NOT_SET_TIME,    VOS_NULL_PTR,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED | CMD_TBL_CLAC_IS_INVISIBLE_E5,
    (VOS_UINT8*)"M",    (VOS_UINT8*)"(1)"},



};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : At_RegisterBasicCmdTable
 ��������  : ע����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��21��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_RegisterBasicCmdTable(VOS_VOID)
{
    return AT_RegisterCmdTable(g_astAtBasicCmdTbl, sizeof(g_astAtBasicCmdTbl)/sizeof(g_astAtBasicCmdTbl[0]));
}


/*****************************************************************************
 �� �� ��  : At_CheckIfDCmdValidChar
 ��������  : ���ָ���ַ��Ƿ�ΪD�����пɳ��ֵĺϷ��ַ�(copy from balong V3R1)
 �������  : VOS_UINT8 ucChar
 �������  : ��
 �� �� ֵ  : PRIVATE VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��23��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CheckIfDCmdValidChar(VOS_UINT8 ucChar)
{
    /* LINUXϵͳ�µĲ��������ʽΪ:ATDT"*99#"���ȹ淶�Ĳ�������������ţ������Ų���
       27007��ITUT-V.250�淶�еĲ�������Ϸ��ַ����У���Ϊ�˱�֤LINUX���ųɹ�������
       ����Ϊ��������ĺϷ��ַ� */
    VOS_UINT8 aucDCmdValidChar[] = {'1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', '*', '#', '+', 'A', 'B', 'C', ',', 'T', 'P', '!', 'W', '@',
        '>', 'I', 'i', 'G', 'g', '"'};

    VOS_UINT8 ucIndex = 0;

    while (ucIndex < sizeof(aucDCmdValidChar))
    {
        if (ucChar == aucDCmdValidChar[ucIndex])
        {
            return AT_SUCCESS;
        }

        ucIndex++;
    }

    return AT_FAILURE;
}


/*****************************************************************************
 �� �� ��  : At_GetFirstBasicCmdAddr
 ��������  : ��ȡ��ϻ��������е�һ����������ĵ�ַ
 �������  : VOS_UINT8 *pData
             VOS_UINT32* pulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT8*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��23��
    ��    ��   : c64416
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* At_GetFirstBasicCmdAddr(VOS_UINT8 *pData, VOS_UINT32* pulLen)
{
    VOS_UINT32 i = 0, j = 0;
    VOS_UINT8* pucAddr = NULL;
    VOS_UINT8* pucCurAddr = NULL;
    VOS_UINT32 ulDCmdLen = 0;
    VOS_UINT32 ulBasicCmdNum = sizeof(g_astAtBasicCmdTbl)/sizeof(AT_PAR_CMD_ELEMENT_STRU);

    for(i = 0; i < ulBasicCmdNum; i++)
    {
        if(NULL == g_astAtBasicCmdTbl[i].pszCmdName)
        {
            break;
        }

        pucCurAddr = (VOS_UINT8*)strstr((VOS_CHAR*)pData, (VOS_CHAR*)(g_astAtBasicCmdTbl[i].pszCmdName));
        if(NULL != pucCurAddr)
        {
            if((NULL == pucAddr) || (pucCurAddr < pucAddr))
            {
                if(AT_CMD_D == g_astAtBasicCmdTbl[i].ulCmdIndex)  /* D�����п����������ַ�����Ҫ���⴦�� */
                {
                    ulDCmdLen = strlen((VOS_CHAR*)pucCurAddr);

                    /* ���μ��D����������Ч�ַ���1��ʾ'D'�ַ������ */
                    for(j = 1; j < ulDCmdLen; j++)
                    {
                        if(AT_SUCCESS != At_CheckIfDCmdValidChar(*(pucCurAddr+j)))
                        {
                            /* ������D����Ĳ����ַ����˳� */
                            break;
                        }
                    }

                    *pulLen = j;
                }
                else
                {
                    *pulLen = strlen((VOS_CHAR*)(g_astAtBasicCmdTbl[i].pszCmdName));
                }

                pucAddr = pucCurAddr;
            }
        }
    }

    return pucAddr;
}


