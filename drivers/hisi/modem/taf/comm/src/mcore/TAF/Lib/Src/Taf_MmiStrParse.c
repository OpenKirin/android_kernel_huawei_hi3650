
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMI_STRPARSE_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "Taf_MmiStrParse.h"
#include  "TafAppSsa.h"
#include  "MnErrorCode.h"
/* A�˺�C�˱���붼Ҫ�õ� */
#include  "MnMsgTs.h"
#include "TafStdlib.h"


/*lint -e958*/

/*****************************************************************************
  2 ��������
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


#define MN_MMI_SC_MAX_ENTRY (sizeof(f_stMmiScInfo)/sizeof(MN_MMI_SC_TABLE_STRU))

#define MN_MMI_BS_MAX_ENTRY (sizeof(f_stMmiBSInfo)/sizeof(MN_MMI_BS_TABLE_STRU))

/* ͨ�ò���ҵ�������ӳ���: ��һ�в���ҵ��������Ӧ��MMI�ַ������ڶ��в���ҵ������� */
MN_MMI_SS_OP_Tbl_STRU                   g_astTafMmiOporationTypeTbl[] = {
                                                    {"**", TAF_MMI_REGISTER_SS,    {0, 0, 0, 0, 0, 0, 0}},
                                                    {"*",  TAF_MMI_ACTIVATE_SS,    {0, 0, 0, 0, 0, 0, 0}},
                                                    {"#",  TAF_MMI_DEACTIVATE_SS,  {0, 0, 0, 0, 0, 0, 0}},
                                                    {"*#", TAF_MMI_INTERROGATE_SS, {0, 0, 0, 0, 0, 0, 0}},
                                                    {"##", TAF_MMI_ERASE_SS,       {0, 0, 0, 0, 0, 0, 0}},
                                                  };

/*****************************************************************************
  4 ���Ͷ���
*****************************************************************************/



/*****************************************************************************
  5 ��������
*****************************************************************************/
MN_MMI_SC_TABLE_STRU     f_stMmiScInfo[] =

{
    {"",         TAF_ALL_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"30",       TAF_CLIP_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"31",       TAF_CLIR_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"76",       TAF_COLP_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"77",       TAF_COLR_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"21",       TAF_CFU_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"67",       TAF_CFB_SS_CODE,                       {0, 0, 0, 0, 0, 0, 0}},
    {"61",       TAF_CFNRY_SS_CODE,                     {0, 0, 0, 0, 0, 0, 0}},
    {"62",       TAF_CFNRC_SS_CODE,                     {0, 0, 0, 0, 0, 0, 0}},
    {"002",      TAF_ALL_FORWARDING_SS_CODE,            {0, 0, 0, 0, 0, 0, 0}},
    {"004",      TAF_ALL_COND_FORWARDING_SS_CODE,       {0, 0, 0, 0, 0, 0, 0}},
    {"43",       TAF_CW_SS_CODE,                        {0, 0, 0, 0, 0, 0, 0}},
    {"37",       TAF_CCBS_A_SS_CODE,                    {0, 0, 0, 0, 0, 0, 0}},
    {"33",       TAF_BAOC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"331",      TAF_BOIC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"332",      TAF_BOICEXHC_SS_CODE,                  {0, 0, 0, 0, 0, 0, 0}},
    {"35",       TAF_BAIC_SS_CODE,                      {0, 0, 0, 0, 0, 0, 0}},
    {"351",      TAF_BICROAM_SS_CODE,                   {0, 0, 0, 0, 0, 0, 0}},
    {"330",      TAF_ALL_BARRING_SS_CODE,               {0, 0, 0, 0, 0, 0, 0}},
    {"333",      TAF_BARRING_OF_OUTGOING_CALLS_SS_CODE, {0, 0, 0, 0, 0, 0, 0}},
    {"353",      TAF_BARRING_OF_INCOMING_CALLS_SS_CODE, {0, 0, 0, 0, 0, 0, 0}}
};



MN_MMI_BS_TABLE_STRU  f_stMmiBSInfo[] =
{
 {"10",     TAF_ALL_TELESERVICES_TSCODE,                    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"11",     TAF_ALL_SPEECH_TRANSMISSION_SERVICES_TSCODE,    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"12",     TAF_ALL_DATA_TELESERVICES_TSCODE,               TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"13",     TAF_ALL_FACSIMILE_TRANSMISSION_SERVICES_TSCODE, TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"16",     TAF_ALL_SMS_SERVICES_TSCODE,                    TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"19",     TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE,           TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"20",     TAF_ALL_BEARERSERVICES_BSCODE,                  TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"21",     TAF_ALL_ASYNCHRONOUS_SERVICES_BSCODE,           TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"22",     TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE,            TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"24",     TAF_ALL_DATA_CIRCUIT_SYNCHRONOUS_BSCODE,        TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"25",     TAF_ALL_DATA_CIRCUIT_ASYNCHRONOUS_BSCODE,       TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"50",     TAF_ALL_PLMN_SPECIFICTS_TSCODE,                 TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"51",     TAF_PLMN_SPECIFICTS_1_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"52",     TAF_PLMN_SPECIFICTS_2_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"53",     TAF_PLMN_SPECIFICTS_3_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"54",     TAF_PLMN_SPECIFICTS_4_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"55",     TAF_PLMN_SPECIFICTS_5_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"56",     TAF_PLMN_SPECIFICTS_6_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"57",     TAF_PLMN_SPECIFICTS_7_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"58",     TAF_PLMN_SPECIFICTS_8_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"59",     TAF_PLMN_SPECIFICTS_9_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"60",     TAF_PLMN_SPECIFICTS_A_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"61",     TAF_PLMN_SPECIFICTS_B_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"62",     TAF_PLMN_SPECIFICTS_C_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"63",     TAF_PLMN_SPECIFICTS_D_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"64",     TAF_PLMN_SPECIFICTS_E_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"65",     TAF_PLMN_SPECIFICTS_F_TSCODE,                   TAF_SS_TELE_SERVICE,   {0, 0, 0, 0, 0, 0}},
 {"70",     TAF_ALL_PLMN_SPECIFICBS_BSCODE,                 TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"71",     TAF_PLMN_SPECIFICBS_1_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"72",     TAF_PLMN_SPECIFICBS_2_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"73",     TAF_PLMN_SPECIFICBS_3_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"74",     TAF_PLMN_SPECIFICBS_4_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"75",     TAF_PLMN_SPECIFICBS_5_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"76",     TAF_PLMN_SPECIFICBS_6_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"77",     TAF_PLMN_SPECIFICBS_7_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"78",     TAF_PLMN_SPECIFICBS_8_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"79",     TAF_PLMN_SPECIFICBS_9_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"80",     TAF_PLMN_SPECIFICBS_A_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"81",     TAF_PLMN_SPECIFICBS_B_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"82",     TAF_PLMN_SPECIFICBS_C_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"83",     TAF_PLMN_SPECIFICBS_D_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"84",     TAF_PLMN_SPECIFICBS_E_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}},
 {"85",     TAF_PLMN_SPECIFICBS_F_BSCODE,                   TAF_SS_BEARER_SERVICE, {0, 0, 0, 0, 0, 0}}
};

MN_CALL_CLIR_CFG_ENUM_U8  f_enClirOperate = MN_CALL_CLIR_AS_SUBS;

/*lint -save -e958 */

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/
/**********************************************************
 �� �� ��  : MMI_GetOporationTypeTblSize
 ��������  : ��ȡ����ҵ�������ӳ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ҵ�������ӳ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��
*************************************************************/

VOS_UINT32 MMI_GetOporationTypeTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiOporationTypeTbl) / sizeof(g_astTafMmiOporationTypeTbl[0]);

    return ulTblSize;
}

/**********************************************************
 �� �� ��  : MMI_GetOporationTypeTblAddr
 ��������  : ��ȡͨ�ò���ҵ�������ӳ���ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ͨ�ò���ҵ�������ӳ���ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��
*************************************************************/
MN_MMI_SS_OP_Tbl_STRU *MMI_GetOporationTypeTblAddr(VOS_VOID)
{
    return g_astTafMmiOporationTypeTbl;
}

/*****************************************************************************
 �� �� ��  : MMI_GetBSTblSize
 ��������  : ��ȡBS������
 �������  : ��
 �������  : ��
 �� �� ֵ  : BS������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MMI_GetBSTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(f_stMmiBSInfo) / sizeof(f_stMmiBSInfo[0]);

    return ulTblSize;
}

/*****************************************************************************
 �� �� ��  : MMI_GetBSTblAddr
 ��������  : ��ȡBS���ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : BS���ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MMI_BS_TABLE_STRU *MMI_GetBSTblAddr(VOS_VOID)
{
    return f_stMmiBSInfo;
}

/*****************************************************************************
 �� �� ��  : MMI_GetSCTblSize
 ��������  : ��ȡSC������
 �������  : ��
 �������  : ��
 �� �� ֵ  : SC������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MMI_GetSCTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(f_stMmiScInfo) / sizeof(f_stMmiScInfo[0]);

    return ulTblSize;
}

/*****************************************************************************
 �� �� ��  : MMI_GetSCTblSize
 ��������  : ��ȡSC���ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SC���ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_MMI_SC_TABLE_STRU *MMI_GetSCTblAddr(VOS_VOID)
{
    return f_stMmiScInfo;
}

/*****************************************************************************
 �� �� ��  : MMI_AtoI
 ��������  : �������ַ���ת���ɶ�Ӧ������
 �������  : pcSrc - ��ת���������ַ���
 �������  : ��
 �� �� ֵ  : ת���������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MMI_AtoI(
    const VOS_CHAR                      *pcSrc
)
{
    VOS_UINT32      i = 0;
    /*lint -e731*/
    while (MN_MMI_isdigit(*pcSrc))
    /*lint +e731*/
    {
        /*lint -e961*/
        i = (i * 10) + (*(pcSrc++) - '0');
        /*lint +e961*/
    }
    return i;
}



/*****************************************************************************
 �� �� ��  : MMI_StrChr
 ��������  : ��һ����Χ�ڵ��ַ����в���ָ�����ַ�
 �������  : pcFrom - �ַ�������ʼλ��
             pcTo   - �ַ�������ֹλ��
             char   - �����ҵ��ַ�
 �������  : ��
 �� �� ֵ  : �������ҵ����ַ����е��ַ��ĵ�ַ��δ���ҵ����򷵻ؿ�ָ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_CHAR* MMI_StrChr(
    const VOS_CHAR                      *pcFrom,
    const VOS_CHAR                      *pcTo,
    VOS_INT                              ichar
)
{
    if (VOS_NULL_PTR == pcFrom)
    {
        return VOS_NULL_PTR;
    }

    for(; (*pcFrom != (VOS_CHAR) ichar) && MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo); ++pcFrom)
    {
        if ('\0' == *pcFrom )
        {
            return VOS_NULL_PTR;
        }
    }

    if ((VOS_NULL_PTR != pcTo) && (pcFrom > pcTo))
    {
        return VOS_NULL_PTR;
    }

    return (VOS_CHAR*)pcFrom;
}



/*****************************************************************************
 �� �� ��  : MMI_Max
 ��������  : ȡ�������޷������������еĽϴ�ֵ
 �������  : ulNumbera
             ulNumberb
 �������  : ��
 �� �� ֵ  : ���������޷������������еĽϴ�ֵ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MMI_Max(const VOS_UINT32 ulNumbera, const VOS_UINT32 ulNumberb)
{
    return ((ulNumbera > ulNumberb) ? ulNumbera : ulNumberb);
}

/*****************************************************************************
 �� �� ��  : MMI_DecodeScAndSi
 ��������  : ��MMI�ַ����е�Sc��Si���н�������������������
 �������  : pInMmiStr   - ��������MMI�ַ���
             pMmiOpParam - ָʾ��Ӧ�Ĳ���
 �������  : pstScSiPara - �������Sc��Si����������
             ppOutMmiStr - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE    - �����ɹ�
             VOS_FALSE   - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL MMI_DecodeScAndSi(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutMmiStr
)
{
    VOS_CHAR                            aucTmpVal[MN_MMI_MAX_PARA_NUM][MN_MMI_MAX_BUF_SIZE];
    VOS_UINT16                          i = 0;
    VOS_UINT16                          j = 0;
    VOS_CHAR                            *pcNextStart;
    VOS_CHAR                            *pcEnd;
    VOS_CHAR                            *pcNextStop;
    VOS_BOOL                            bEndReached = VOS_FALSE;
    VOS_UINT16                          usOffset = 0;
    VOS_UINT32                          ulTmpMmiNum;

    ulTmpMmiNum  = 0;

    PS_MEM_SET(pstScSiPara, '\0', sizeof(MN_MMI_SC_SI_PARA_STRU));

    PS_MEM_SET(aucTmpVal, '\0', sizeof(aucTmpVal));


    if (TAF_MMI_REGISTER_PASSWD != pMmiOpParam->MmiOperationType)
    {
        /*������ʼ�ļ����ַ�*/
        for (i =0; (!MN_MMI_isdigit(pInMmiStr[i])) && (i < 2); i++)
        {
            usOffset++;
        }
    }

    pcNextStart = &pInMmiStr[i];

    if (VOS_NULL_PTR ==
           (pcEnd = MMI_StrChr(pcNextStart, VOS_NULL_PTR, MN_MMI_STOP_CHAR)))
    {
        return VOS_FALSE;
    }
    else
    {
        pcNextStop = MMI_StrChr(pcNextStart, pcEnd, MN_MMI_START_SI_CHAR);

        j = 0;
        while ((j < MN_MMI_MAX_PARA_NUM) && (VOS_FALSE == bEndReached))
        {
            if (VOS_NULL_PTR != pcNextStop)
            {
                ulTmpMmiNum = (VOS_UINT32)(pcNextStop - pcNextStart);
                if (ulTmpMmiNum > MN_MMI_MAX_BUF_SIZE)
                {
                    ulTmpMmiNum = MN_MMI_MAX_BUF_SIZE;
                }
                PS_MEM_CPY(&aucTmpVal[j][0],
                           pcNextStart,
                           ulTmpMmiNum);
                usOffset += (VOS_UINT16)((pcNextStop - pcNextStart) + 1);
                pcNextStart = pcNextStop + 1;
                pcNextStop = MMI_StrChr(pcNextStart, pcEnd, MN_MMI_START_SI_CHAR);
                j++;
            }
            else
            {
                ulTmpMmiNum = (VOS_UINT32)(pcEnd - pcNextStart);
                if (ulTmpMmiNum > MN_MMI_MAX_BUF_SIZE)
                {
                    ulTmpMmiNum = MN_MMI_MAX_BUF_SIZE;
                }
                PS_MEM_CPY(&aucTmpVal[j][0],
                           pcNextStart,
                           ulTmpMmiNum);
                usOffset += (VOS_UINT16)((pcEnd - pcNextStart) + 1);
                bEndReached = VOS_TRUE;
            }
        }
    }

    PS_MEM_CPY(pstScSiPara->acSsCode, &aucTmpVal[0][0], MN_MMI_MAX_SC_LEN);
    PS_MEM_CPY(pstScSiPara->acSia, &aucTmpVal[1][0], MN_MMI_MAX_SIA_LEN);
    PS_MEM_CPY(pstScSiPara->acSib, &aucTmpVal[2][0], MN_MMI_MAX_SIB_LEN);
    PS_MEM_CPY(pstScSiPara->acSic, &aucTmpVal[3][0], MN_MMI_MAX_SIC_LEN);

    *ppOutMmiStr = pInMmiStr + usOffset;

    return VOS_TRUE;


}


/*****************************************************************************
 �� �� ��  : MMI_JudgePinOperation
 ��������  : �ж��ַ�����Ӧ�Ĳ����ǲ��ǽ���pin������������pin���������д��Ӧ�Ĳ���
 �������  : pMmiStr         - ���������ַ���
 �������  : ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pMmiOpParam     - pin������صĲ���
             pulErrorNo      - �ڽ�������pin�����������£��������Ĳ����д���
                               ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
 �� �� ֵ  : VOS_TRUE        - ��pin�����
             VOS_FALSE       - ����pin�����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgePinOperation(
    VOS_CHAR                            *pMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiPinStrOpTbl[] = {
                                                              {"**042*", TAF_MMI_CHANGE_PIN2,  {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**04*",  TAF_MMI_CHANGE_PIN,   {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**052*", TAF_MMI_UNBLOCK_PIN2, {0, 0, 0, 0, 0, 0, 0}},
                                                              {"**05*",  TAF_MMI_UNBLOCK_PIN,  {0, 0, 0, 0, 0, 0, 0}},
                                                              {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                             };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stMmiPinStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pMmiStr,
                            stMmiPinStrOpTbl[i].pString,
                            VOS_StrLen(stMmiPinStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiPinStrOpTbl[i].enOperationType;
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stMmiPinStrOpTbl[i].pString)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == MMI_DecodeScAndSi(pMmiStr, pMmiOpParam, &stScSiPara, ppOutRestMmiStr))
    {
        if (0 == VOS_MemCmp(stScSiPara.acSib,
                            stScSiPara.acSic,
                            MMI_Max(VOS_StrLen(stScSiPara.acSib), VOS_StrLen(stScSiPara.acSic))))
        {
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->PinReq.aucOldPin,
                        (VOS_CHAR*)stScSiPara.acSia,
                        VOS_StrLen(stScSiPara.acSia) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->PinReq.aucNewPin,
                        (VOS_CHAR*)stScSiPara.acSib,
                        VOS_StrLen(stScSiPara.acSib) + 1);
            switch(pMmiOpParam->MmiOperationType)
            {
            case TAF_MMI_CHANGE_PIN2:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_CHANGE;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN2;
                break;

            case TAF_MMI_CHANGE_PIN:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_CHANGE;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN;
                break;

            case TAF_MMI_UNBLOCK_PIN2:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_UNBLOCK;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN2;
                break;

            case TAF_MMI_UNBLOCK_PIN:
                pMmiOpParam->PinReq.CmdType = TAF_PIN_UNBLOCK;
                pMmiOpParam->PinReq.PinType = TAF_SIM_PIN;
                break;

            default:
                /*�÷�֧��Զ�����ߵ�*/
                break;
            }

            *pulErrCode = MN_ERR_NO_ERROR;
        }
        else
        {
            *pulErrCode = MN_ERR_INVALIDPARM;
        }
    }
    else
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MMI_JudgePwdOperation
 ��������  : �ж��ַ�����Ӧ�Ĳ����ǲ��ǽ����������������������������д��Ӧ�Ĳ���
 �������  : pMmiStr         - ���������ַ���
 �������  : ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pMmiOpParam     - ���������صĲ���
             pulErrorNo      - �ڽ��������������������£��������Ĳ����д���
                               ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
 �� �� ֵ  : VOS_TRUE        - ���������
             VOS_FALSE       - �����������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgePwdOperation(
    VOS_CHAR                            *pMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiPwdStrOpTbl[] = {
                                                              {"**03*", TAF_MMI_REGISTER_PASSWD, {0, 0, 0, 0, 0, 0, 0}},
                                                              {"*03*",  TAF_MMI_REGISTER_PASSWD, {0, 0, 0, 0, 0, 0, 0}},
                                                              {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                             };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stMmiPwdStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pMmiStr,
                            stMmiPwdStrOpTbl[i].pString,
                            VOS_StrLen(stMmiPwdStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiPwdStrOpTbl[i].enOperationType;
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stMmiPwdStrOpTbl[i].pString)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == MMI_DecodeScAndSi(pMmiStr + VOS_StrLen(stMmiPwdStrOpTbl[i].pString),
                                      pMmiOpParam,
                                      &stScSiPara,
                                      ppOutRestMmiStr))
    {
            if(0 == VOS_StrLen(stScSiPara.acSsCode))  /*for a common password for all appropriate services, delete the ZZ*/
            {
                pMmiOpParam->RegPwdReq.SsCode = TAF_ALL_SS_CODE;
            }
            else
            {
                i = 0;
                while (i < MN_MMI_SC_MAX_ENTRY)
                {
                    if (0 == VOS_MemCmp(f_stMmiScInfo[i].pcMmiSc,
                                        stScSiPara.acSsCode,
                                        MMI_Max(VOS_StrLen(stScSiPara.acSsCode), VOS_StrLen(f_stMmiScInfo[i].pcMmiSc))))
                    {
                        pMmiOpParam->RegPwdReq.SsCode = f_stMmiScInfo[i].ucNetSc;
                        break;
                    }
                    i++;
                }

                if (i >= MN_MMI_SC_MAX_ENTRY)
                {
                    *pulErrCode = MN_ERR_INVALIDPARM;
                    return VOS_TRUE;
                }
            }

            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucOldPwdStr,
                        (VOS_CHAR*)stScSiPara.acSia,
                        VOS_StrLen(stScSiPara.acSia) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucNewPwdStr,
                        (VOS_CHAR*)stScSiPara.acSib,
                        VOS_StrLen(stScSiPara.acSib) + 1);
            (VOS_VOID)VOS_StrNCpy((VOS_CHAR*)pMmiOpParam->RegPwdReq.aucNewPwdStrCnf,
                        (VOS_CHAR*)stScSiPara.acSic,
                        VOS_StrLen(stScSiPara.acSic) + 1);

            *pulErrCode = MN_ERR_NO_ERROR;
    }
    else
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MMI_JudgeTmpModeClirOp
 ��������  : �ж��ַ�����Ӧ�Ĳ����ǲ���CLIR��ʱģʽ�µ����ƻ���ò�����
 �������  : pMmiStr         - ���������ַ���
 �������  : ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pMmiOpParam     - ���������صĲ���
 �� �� ֵ  : VOS_TRUE        - ����·��ز���
             VOS_FALSE       - ������·��ز���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgeTmpModeClirOp(
    VOS_CHAR                            *pInMmiStr,
    VOS_CHAR                            **ppOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_STR_OPERATION_Tbl_STRU       stMmiLiStrOpTbl[]={
                                                            {"*31#", TAF_MMI_SUPPRESS_CLIR, {0, 0, 0, 0, 0, 0, 0}},
                                                            {"#31#", TAF_MMI_INVOKE_CLIR, {0, 0, 0, 0, 0, 0, 0}},
                                                            {VOS_NULL_PTR, TAF_MMI_NULL_OPERATION, {0, 0, 0, 0, 0, 0, 0}}
                                                          };
    while (VOS_NULL_PTR != stMmiLiStrOpTbl[i].pString)
    {
        if (0 == VOS_MemCmp(pInMmiStr,
                            stMmiLiStrOpTbl[i].pString,
                            VOS_StrLen(stMmiLiStrOpTbl[i].pString)))
        {
            pMmiOpParam->MmiOperationType = stMmiLiStrOpTbl[i].enOperationType;
            *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(stMmiLiStrOpTbl[i].pString);
            return VOS_TRUE;
        }
        i++;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : MMI_JudgeImeiOperation
 ��������  : �ж��ַ�����Ӧ�Ĳ����Ƿ�����ʾIMEI
 �������  : pMmiStr         - ���������ַ���
 �������  : ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pMmiOpParam     - ���������صĲ���
 �� �� ֵ  : VOS_TRUE        - ����ʾIMEI����
             VOS_FALSE       - ������ʾIMEI����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL  VOS_BOOL MMI_JudgeImeiOperation(
    VOS_CHAR                            *pcInMmiStr,
    VOS_CHAR                            **ppcOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
)
{
    VOS_CHAR                            *pcImeiStr = "*#06#";

    if (0 == VOS_MemCmp(pcInMmiStr, pcImeiStr, VOS_StrLen(pcImeiStr)))
    {
        pstMmiOpParam->MmiOperationType = TAF_MMI_DISPLAY_IMEI;
        *ppcOutRestMmiStr = pcInMmiStr + VOS_StrLen(pcImeiStr);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MMI_JudgeUssdOperation
 ��������  : �ж��ַ�����Ӧ�Ĳ����Ƿ���USSD����
 �������  : pMmiStr         - ���������ַ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE        - ����ʾIMEI����
             VOS_FALSE       - ������ʾIMEI����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
 VOS_BOOL MMI_JudgeUssdOperation(
    VOS_CHAR                            *pcMmiStr
)
{
    VOS_UINT32       ulStrLen = VOS_StrLen(pcMmiStr);

    /*�ж�����*/
    /*
    3) #-string:
    Input of the form.
    "Entry of any characters defined in the 3GPP TS 23.038 [8] Default Alphabet
    (up to the maximum defined in 3GPP TS 24.080 [10]), followed by #SEND".
    */
    if ((ulStrLen >= MN_MMI_MIN_USSD_LEN)
      &&(MN_MMI_STOP_CHAR == pcMmiStr[ulStrLen - 1]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MMI_TransMmiSsCodeToNetSsCode
 ��������  : ��Mmi�ִ��е�Ss Codeת�������綨���Ss Code
 �������  : pstScSiPara  - MMI�����Sc��Si�Ķ���
 �������  : pucNetSsCode - ת��������綨���Ss Code
 �� �� ֵ  : VOS_OK       - ת���ɹ�
             VOS_ERR    - ת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MMI_TransMmiSsCodeToNetSsCode(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_UINT8                           *pucNetSsCode
)
{
    VOS_UINT8       i = 0;

    /*ת��SS Code*/
    while(i < MN_MMI_SC_MAX_ENTRY)
    {
        if (0 == VOS_MemCmp(f_stMmiScInfo[i].pcMmiSc,
                            pstScSiPara->acSsCode,
                            MMI_Max(VOS_StrLen(f_stMmiScInfo[i].pcMmiSc), VOS_StrLen(pstScSiPara->acSsCode))))
        {
            *pucNetSsCode = f_stMmiScInfo[i].ucNetSc;
            break;
        }
        i++;
    }

    if (i >= MN_MMI_SC_MAX_ENTRY)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MMI_TransMmiBsCodeToNetBsCode
 ��������  : ��Mmi�ִ��е�Bs Codeת�������綨���Bs Code
 �������  : pstScSiPara  - MMI�����Sc��Si�Ķ���
             ucNetSsCode  - ���綨���Ss Code
 �������  : pucNetBsCode - ת��������綨���Bs Code
             pucNetBsType - ת��������綨���Bs Type
 �� �� ֵ  : VOS_OK       - ת���ɹ�
             VOS_ERR    - ת��ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MMI_TransMmiBsCodeToNetBsCode(
    VOS_UINT8                           ucNetSsCode,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_UINT8                           *pucNetBsCode,
    VOS_UINT8                           *pucNetBsType

)
{
    VOS_CHAR                            acBs[MN_MMI_MAX_SIA_LEN + 1];
    VOS_UINT16                          i;

    /*�ǲ�����Ҫ�趨��Щ��Ҫ���ô˺������޶�?*/

    /*��һ����ת����Ӧ��BS code*/
    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0)))
    {
        PS_MEM_CPY(acBs, pstScSiPara->acSib, VOS_StrLen(pstScSiPara->acSib) + 1);
    }
    else if (TAF_CW_SS_CODE == ucNetSsCode)
    {
        PS_MEM_CPY(acBs, pstScSiPara->acSia, VOS_StrLen(pstScSiPara->acSia) + 1);
    }
    else
    {
        acBs[0] = '\0';
    }


    i = 0;
    while(i < MN_MMI_BS_MAX_ENTRY)
    {
        if (0 == VOS_MemCmp(f_stMmiBSInfo[i].pcMmiBs,
                            acBs,
                            MMI_Max(VOS_StrLen(f_stMmiBSInfo[i].pcMmiBs), VOS_StrLen(acBs))))
        {
            *pucNetBsCode = f_stMmiBSInfo[i].ucNetBsCode;
            *pucNetBsType = f_stMmiBSInfo[i].ucNetBsType;
            break;
        }
        i++;
    }

    if (MN_MMI_BS_MAX_ENTRY == i)
    {
        return VOS_ERR;
    }

    return VOS_OK;

    /* BS Code ��ת����� */
}

/*****************************************************************************
 �� �� ��  : MMI_FillInRegisterSSPara
 ��������  : ��дRegisterSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - RegisterSS����������Ӧ�Ĳ���
             pucErrCode    - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��09��02��
    ��    ��   : h44270
    �޸�����   : AT2D05318
  3.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
*****************************************************************************/
VOS_UINT32 MMI_FillInRegisterSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_REGISTERSS_REQ_STRU          *pstRegisterSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;

    pstRegisterSsReq = &pMmiOpParam->RegisterSsReq;

    PS_MEM_SET(pstRegisterSsReq, 0, sizeof(TAF_SS_REGISTERSS_REQ_STRU));

    pstRegisterSsReq->SsCode = ucNetSsCode;

    if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
    {
        pstRegisterSsReq->OP_FwdToNum = 1;
        pstRegisterSsReq->OP_NumType = 1;
        /*����Ǵ�'+'�ţ���Ϊ�ǹ��ʺ��룬�������͵�ֵΪ0x91*/
        if ('+' == pstScSiPara->acSia[0])
        {
            /*ȥ��ͷ����'+'��*/
            pstRegisterSsReq->NumType = 0x91;
            PS_MEM_CPY(pstRegisterSsReq->aucFwdToNum,
                      pstScSiPara->acSia + 1,
                      VOS_StrLen(pstScSiPara->acSia));

        }
        else
        {
            pstRegisterSsReq->NumType = 0x81;
            PS_MEM_CPY(pstRegisterSsReq->aucFwdToNum,
                      pstScSiPara->acSia,
                      VOS_StrLen(pstScSiPara->acSia) + 1);
        }

        if ('\0' != pstScSiPara->acSic[0])
        {
            pstRegisterSsReq->OP_NoRepCondTime = 1;
            pstRegisterSsReq->NoRepCondTime = (VOS_UINT8)MMI_AtoI(pstScSiPara->acSic);
        }
    }


    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_ALL_BARRING_SS_CODE������ز��� */
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }

        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstRegisterSsReq->OP_BsService = 1;
        pstRegisterSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstRegisterSsReq->BsService.BsType = ucNetBsType;
    }



    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_FillInEraseSSPara
 ��������  : ��дEraseSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - EraseSS����������Ӧ�Ĳ���
             pucErrCode    - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
*****************************************************************************/
VOS_UINT32 MMI_FillInEraseSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ERASESS_REQ_STRU             *pstEraseSsReq;

    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;


    pstEraseSsReq = &pstMmiOpParam->EraseSsReq;

    PS_MEM_SET(pstEraseSsReq, 0, sizeof(TAF_SS_ERASESS_REQ_STRU));

    pstEraseSsReq->SsCode = ucNetSsCode;


    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_ALL_BARRING_SS_CODE������ز��� */
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstEraseSsReq->OP_BsService = 1;
        pstEraseSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstEraseSsReq->BsService.BsType = ucNetBsType;
    }


    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_FillInActivateSSPara
 ��������  : ��дActivateSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - ActivateSS����������Ӧ�Ĳ���
             pucErrCode    - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
*****************************************************************************/
VOS_UINT32 MMI_FillInActivateSSPara(
    MN_MMI_SC_SI_PARA_STRU             *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU        *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ACTIVATESS_REQ_STRU          *pstActivateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;
    VOS_UINT32                          ulPasswordLen;

    /*
        ����ת��ҵ��ע��ǰ׺��*�Ҵ��ڲ���A�����Ҫ��ע�ᴦ��
        �ο�Э��3GPP 22030 6.5.2 struct of MMI
    */
    if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & TAF_SS_CODE_MASK))
    {
        if (0 != VOS_StrLen((VOS_CHAR *)pstScSiPara->acSia))
        {
            pMmiOpParam->MmiOperationType = TAF_MMI_REGISTER_SS;
            return MMI_FillInRegisterSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        }

    }

    pstActivateSsReq = &pMmiOpParam->ActivateSsReq;

    PS_MEM_SET(pstActivateSsReq, 0, sizeof(TAF_SS_ACTIVATESS_REQ_STRU));

    pstActivateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* �������뵽������Ϣ�����ṹ */
            ulPasswordLen = VOS_StrLen(pstScSiPara->acSia);
            if (TAF_SS_MAX_PASSWORD_LEN != ulPasswordLen)
            {
                return MN_ERR_INVALIDPARM;
            }

            PS_MEM_CPY(pMmiOpParam->ActivateSsReq.aucPassword,
                       pstScSiPara->acSia,
                       TAF_SS_MAX_PASSWORD_LEN);
            pMmiOpParam->ActivateSsReq.OP_Password = VOS_TRUE;

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }

        }

        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstActivateSsReq->OP_BsService = 1;
        pstActivateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstActivateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_FillInDeactivateCCBSPara
 ��������  : ��дDeactivateSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - DeactivateSS����������Ӧ�Ĳ���
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MMI_FillInDeactivateCCBSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_ERASECC_ENTRY_REQ_STRU       *pstCcbsEraseReq;
    VOS_UINT32                          ulCcbsIndex;

    pstCcbsEraseReq = &pMmiOpParam->stCcbsEraseReq;

    PS_MEM_SET(pstCcbsEraseReq, 0, sizeof(TAF_SS_ERASECC_ENTRY_REQ_STRU));
    ulCcbsIndex = MMI_AtoI(pstScSiPara->acSia);
    if (0 != ulCcbsIndex)
    {
        if ((ulCcbsIndex > 5 )
        || (ulCcbsIndex < 1))
        {
            return MN_ERR_INVALIDPARM;
        }
        else
        {
            pstCcbsEraseReq->OP_CcbsIndex = VOS_TRUE;
            pstCcbsEraseReq->CcbsIndex = (TAF_UINT8)(ulCcbsIndex);
        }
    }
    pstCcbsEraseReq->SsCode = ucNetSsCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_FillInDeactivateSSPara
 ��������  : ��дDeactivateSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - DeactivateSS����������Ӧ�Ĳ���
             pucErrCode    - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
*****************************************************************************/
VOS_UINT32 MMI_FillInDeactivateSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_DEACTIVATESS_REQ_STRU        *pstDeactivateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;
    VOS_UINT32                          ulPasswordLen;

    pstDeactivateSsReq = &pMmiOpParam->DeactivateSsReq;

    PS_MEM_SET(pstDeactivateSsReq, 0, sizeof(TAF_SS_DEACTIVATESS_REQ_STRU));

    pstDeactivateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* �������뵽ȥ������Ϣ�����ṹ */
            ulPasswordLen = VOS_StrLen(pstScSiPara->acSia);
            if (TAF_SS_MAX_PASSWORD_LEN != ulPasswordLen)
            {
                return MN_ERR_INVALIDPARM;
            }

            PS_MEM_CPY(pMmiOpParam->DeactivateSsReq.aucPassword,
                       pstScSiPara->acSia,
                       TAF_SS_MAX_PASSWORD_LEN);
            pMmiOpParam->DeactivateSsReq.OP_Password = VOS_TRUE;

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
         }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstDeactivateSsReq->OP_BsService = 1;
        pstDeactivateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstDeactivateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_FillInInterrogateSSPara
 ��������  : ��дInterrogateSS������Ҫ�Ĳ���
 �������  : pstScSiPara   - ����������Sc��Si����������
 �������  : pstMmiOpParam - InterrogateSS����������Ӧ�Ĳ���
             pucErrCode    - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MMI_FillInInterrogateSSPara(
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT8                           ucNetSsCode
)
{
    TAF_SS_INTERROGATESS_REQ_STRU       *pstInterrogateSsReq;
    VOS_UINT8                           ucNetBsCode;
    VOS_UINT8                           ucNetBsType;

    pstInterrogateSsReq = &pstMmiOpParam->InterrogateSsReq;

    PS_MEM_SET(pstInterrogateSsReq, 0, sizeof(TAF_SS_INTERROGATESS_REQ_STRU));

    pstInterrogateSsReq->SsCode = ucNetSsCode;

    if ((TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_ALL_BARRING_SS_CODE == (ucNetSsCode & 0xF0))
      ||(TAF_CW_SS_CODE == ucNetSsCode))
    {
        if (TAF_ALL_FORWARDING_SS_CODE == (ucNetSsCode & 0xF0))
        {
            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else if (TAF_CW_SS_CODE == ucNetSsCode)
        {
            if (0 == VOS_StrLen(pstScSiPara->acSia))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        else
        {
            /* Delete TAF_MMI_GET_PASSWD������ز��� */

            if (0 == VOS_StrLen(pstScSiPara->acSib))
            {
                return MN_ERR_NO_ERROR;
            }
        }
        if (VOS_OK != MMI_TransMmiBsCodeToNetBsCode(ucNetSsCode,
                                                    pstScSiPara,
                                                    &ucNetBsCode,
                                                    &ucNetBsType))
        {
            return MN_ERR_INVALIDPARM;
        }

        pstInterrogateSsReq->OP_BsService = 1;
        pstInterrogateSsReq->BsService.BsServiceCode = ucNetBsCode;
        pstInterrogateSsReq->BsService.BsType = ucNetBsType;
    }

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 �� �� ��  : MMI_FillInProcessUssdReqPara
 ��������  : ��дProcessUssdReq������Ҫ�Ĳ���
 �������  : pcInMmiStr       - MMI�ִ�
 �������  : pstMmiOpParam    - ProcessUssdReq����������Ӧ�Ĳ���
             ppcOutRestMmiStr - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : VOS_TRUE      - ��д�����ɹ�
             ����ֵ        - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
*****************************************************************************/
VOS_UINT32 MMI_FillInProcessUssdReqPara(
    VOS_CHAR                            *pcInMmiStr,
    VOS_CHAR                            **ppcOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
)
{
    TAF_SS_PROCESS_USS_REQ_STRU         *pstProcessUssdReq;
    VOS_UINT32                          ulStrLen;

    pstProcessUssdReq = &pstMmiOpParam->ProcessUssdReq;

    ulStrLen =  VOS_StrLen(pcInMmiStr);
    if ( ulStrLen > TAF_SS_MAX_USSDSTRING_LEN )
    {
        return MN_ERR_INVALIDPARM;
    }

    PS_MEM_SET(pstProcessUssdReq, 0, sizeof(TAF_SS_PROCESS_USS_REQ_STRU));


    pstProcessUssdReq->DatacodingScheme = pstMmiOpParam->ProcessUssdReq.DatacodingScheme;

    pstProcessUssdReq->UssdStr.usCnt = (VOS_UINT8)VOS_StrLen(pcInMmiStr);

    if (pstProcessUssdReq->UssdStr.usCnt > (TAF_SS_MAX_USSDSTRING_LEN*2))
    {
        pstProcessUssdReq->UssdStr.usCnt = (TAF_SS_MAX_USSDSTRING_LEN*2);
    }

    PS_MEM_CPY(pstProcessUssdReq->UssdStr.aucUssdStr,
               pcInMmiStr,
               pstProcessUssdReq->UssdStr.usCnt);

    *ppcOutRestMmiStr = pcInMmiStr + VOS_StrLen(pcInMmiStr);

    return MN_ERR_NO_ERROR;

}

/*****************************************************************************
 �� �� ��  : MMI_FillInCallOrigPara
 ��������  : ��д�����������Ҫ����ز���
 �������  : pcMmiStr        - �����MMI�ִ�
 �������  : pstMmiOpParam   - �������ͼ�����Ӧ�Ĳ���
             ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
 �� �� ֵ  : MN_ERR_NO_ERROR - ��д�����ɹ�
             ����ֵ          - �����д���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��09��05��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D05508
  3.��    ��   : 2011��10��26��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ, ʹ��A�˵�API:AT_AsciiNumberToBcd�滻֮ǰ��MN_AsciiNumberToBcd
  4.��    ��   : 2013��12��24��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
LOCAL VOS_UINT32 MMI_FillInCallOrigPara(
    VOS_CHAR                            *pcMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_CHAR                            **ppOutRestMmiStr
)
{
    VOS_UINT32                          ulRslt;


    /*������ִ����ܳ������������������󳤶�*/
    if (VOS_StrLen(pcMmiStr) >  (MN_CALL_MAX_BCD_NUM_LEN*2))
    {
        return MN_ERR_INVALIDPARM;
    }

    if ('+' == pcMmiStr[0])
    {
        /*��Ascii��ת���ɶ�Ӧ��BCD��*/
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr + 1,
                                     pstMmiOpParam->MnCallOrig.stDialNumber.aucBcdNum,
                                     &pstMmiOpParam->MnCallOrig.stDialNumber.ucNumLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
        pstMmiOpParam->MnCallOrig.stDialNumber.enNumType =
                             (VOS_UINT8)(0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);
    }
    else
    {
        /*��Ascii��ת���ɶ�Ӧ��BCD��*/
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr,
                                 pstMmiOpParam->MnCallOrig.stDialNumber.aucBcdNum,
                                 &pstMmiOpParam->MnCallOrig.stDialNumber.ucNumLen);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
        pstMmiOpParam->MnCallOrig.stDialNumber.enNumType =
                             (VOS_UINT8)(0x80 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    }




    if (MN_ERR_NO_ERROR != ulRslt)
    {
        return ulRslt;
    }

    /*��д������Ҫ�Ĳ���*/
    pstMmiOpParam->MmiOperationType = TAF_MMI_CALL_ORIG;
    pstMmiOpParam->MnCallOrig.enCallType = MN_CALL_TYPE_VOICE;

    pstMmiOpParam->MnCallOrig.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_AUTO;

    pstMmiOpParam->MnCallOrig.enClirCfg = f_enClirOperate;
    pstMmiOpParam->MnCallOrig.stCugCfg.bEnable = VOS_FALSE;
    pstMmiOpParam->MnCallOrig.enCallMode = MN_CALL_MODE_SINGLE;

    *ppOutRestMmiStr = pcMmiStr + VOS_StrLen(pcMmiStr);

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MMI_JudgeMmiOperationType
 ��������  : �ж�MMI�ִ���������
 �������  : pInMmiStr  - �����MMI�ִ�
 �������  : pstMmiOpParam - �������ͼ�����Ӧ�Ĳ���
             pstScSiPara - �������Sc��Si����������
             ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pulErrCode    - �ڽ�������CHLD����������£��������Ĳ����д���
                             ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
             pucNetSsCode - ת��������綨���Ss Code
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ�����Ժ�
*****************************************************************************/
 VOS_VOID MMI_JudgeMmiOperationType(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           ucNetSsCode
)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    switch(pMmiOpParam->MmiOperationType)
    {
    case TAF_MMI_REGISTER_SS:
        *pulErrCode = MMI_FillInRegisterSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_ERASE_SS:
        *pulErrCode = MMI_FillInEraseSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_ACTIVATE_SS:
        *pulErrCode = MMI_FillInActivateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_DEACTIVATE_SS:
        *pulErrCode = MMI_FillInDeactivateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_INTERROGATE_SS:
    case TAF_MMI_INTERROGATE_CCBS:
        *pulErrCode = MMI_FillInInterrogateSSPara(pstScSiPara, pMmiOpParam, ucNetSsCode);
        break;

    case TAF_MMI_PROCESS_USSD_REQ:
        *pulErrCode = MMI_FillInProcessUssdReqPara(pInMmiStr,
                                                   ppOutRestMmiStr,
                                                   pMmiOpParam);
        break;

     /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
     case TAF_MMI_DEACTIVATE_CCBS:
        *pulErrCode = MMI_FillInDeactivateCCBSPara(pstScSiPara,
                                                   pMmiOpParam,
                                                   ucNetSsCode);
        break;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    default:
        break;

    }
    return;
}

/*****************************************************************************
 �� �� ��  : MMI_MatchSsOpTbl
 ��������  : �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���(register password����),
             ������������
 �������  : pInMmiStr  - �����MMI�ִ�
 �������  : pstMmiOpParam - �������ͼ�����Ӧ�Ĳ���
             pstScSiPara - �������Sc��Si����������
             ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pulErrCode    - �ڽ�������CHLD����������£��������Ĳ����д���
                             ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
             pucNetSsCode - ת��������綨���Ss Code
 �� �� ֵ  : VOS_TRUE - �ɹ�
             VOS_FALSE - ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
*****************************************************************************/
 VOS_BOOL MMI_MatchSsOpTbl(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           *pucNetSsCode
)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /* ��ȡ���Կ���NV��ַ */
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if (VOS_FALSE == MMI_DecodeScAndSi(pInMmiStr, pMmiOpParam, pstScSiPara, ppOutRestMmiStr))
    {
        *pulErrCode = MN_ERR_INVALIDPARM;
        return VOS_FALSE;
    }

    if (VOS_OK != MMI_TransMmiSsCodeToNetSsCode(pstScSiPara, pucNetSsCode))
    {
        if (VOS_FALSE == MMI_JudgeUssdOperation(pInMmiStr))
        {
            *pulErrCode = MN_ERR_INVALIDPARM;
            return VOS_FALSE;
        }
        pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ((TAF_MMI_DEACTIVATE_SS == pMmiOpParam->MmiOperationType) && (TAF_CCBS_A_SS_CODE == *pucNetSsCode))
    {
        pMmiOpParam->MmiOperationType = TAF_MMI_DEACTIVATE_CCBS;
    }
    else if ((TAF_MMI_INTERROGATE_SS == pMmiOpParam->MmiOperationType) && (TAF_CCBS_A_SS_CODE == *pucNetSsCode))
    {
        pMmiOpParam->MmiOperationType = TAF_MMI_INTERROGATE_CCBS;
    }
    else
    {
        ;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : MMI_JudgeChldOperation
 ��������  : �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���(register password����)
 �������  : pcInMmiStr    - �����MMI�ִ�
 �������  : pstMmiOpParam - �������ͼ�����Ӧ�Ĳ���
             pucErrCode    - �ڽ�������CHLD����������£��������Ĳ����д���
                             ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
 �� �� ֵ  : VOS_TRUE      - ��CHLD����
             VOS_FALSE     - ����CHLD����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : Ȧ���Ӷ��޸�
  3.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��
*****************************************************************************/
 VOS_BOOL MMI_JudgeSsOperation(
    VOS_CHAR                            *pInMmiStr,
    VOS_CHAR                            **ppOutRestMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_BOOL                            bMatch = VOS_FALSE;
    VOS_CHAR                            acOpType[3];
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;
    VOS_UINT16                          i = 0;
    VOS_UINT32                          ulTableSize;
    MN_MMI_SS_OP_Tbl_STRU              *pstOperationType    = VOS_NULL_PTR;

    *pulErrCode = MN_ERR_NO_ERROR;
    PS_MEM_SET(acOpType, '\0', sizeof(acOpType));


    for (i =0; (!MN_MMI_isdigit(pInMmiStr[i])) && (i < 2); i++)
    {
        acOpType[i] = pInMmiStr[i];
    }

    ulTableSize         = MMI_GetOporationTypeTblSize();
    pstOperationType  = MMI_GetOporationTypeTblAddr();
    for (i = 0; i < ulTableSize; i++)
    {
        if (0 == VOS_MemCmp(pstOperationType->pcSsOpStr,
                             acOpType,
                             MMI_Max(VOS_StrLen(pstOperationType->pcSsOpStr), VOS_StrLen(acOpType))))
        {
            pMmiOpParam->MmiOperationType = pstOperationType->enSsOpType;
            bMatch = VOS_TRUE;
            break;
        }

        pstOperationType++;
    }

    if (VOS_FALSE == bMatch)
    {
        if (VOS_FALSE == MMI_JudgeUssdOperation(pInMmiStr))
        {
            return VOS_FALSE;
        }
        pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
    }
    else
    {
        if (VOS_FALSE == MMI_MatchSsOpTbl(pInMmiStr, pMmiOpParam, &stScSiPara, ppOutRestMmiStr,pulErrCode,&ucNetSsCode))
        {
            return VOS_FALSE;
        }
    }

    MMI_JudgeMmiOperationType(pInMmiStr, pMmiOpParam, &stScSiPara,ppOutRestMmiStr,pulErrCode,ucNetSsCode);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MMI_JudgeChldOperation
 ��������  : �ж��Ƿ���CHLD����
 �������  : pcInMmiStr    - �����MMI�ִ�
 �������  : pstMmiOpParam - �������ͼ�����Ӧ�Ĳ���
             pucErrCode    - �ڽ�������CHLD����������£��������Ĳ����д���
                             ��ô�����Ӧ�Ĵ����룬�޴���ʱ����MN_ERR_NO_ERROR
 �� �� ֵ  : VOS_TRUE      - ��CHLD����
             VOS_FALSE     - ����CHLD����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_BOOL MMI_JudgeChldOperation(
    VOS_CHAR                            *pcInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
    VOS_UINT32                          *pulErrCode
)
{
    VOS_UINT16                          i = 0;
    MN_MMI_CHLD_OP_Tbl_STRU             stChldOpTbl[] = {
                                                         {"0",           MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"1",           MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"10",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"11",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"12",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"13",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"14",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"15",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"16",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"17",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"18",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"19",          MN_CALL_SUPS_CMD_REL_CALL_X,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"2",           MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH, {0, 0, 0, 0, 0, 0, 0}},
                                                         {"20",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"21",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"22",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"23",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"24",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"25",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"26",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"27",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"28",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"29",          MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X,  {0, 0, 0, 0, 0, 0, 0}},
                                                         {"3",           MN_CALL_SUPS_CMD_BUILD_MPTY,        {0, 0, 0, 0, 0, 0, 0}},
                                                         {"4",           MN_CALL_SUPS_CMD_ECT,               {0, 0, 0, 0, 0, 0, 0}},
                                                         {"4*",          MN_CALL_SUPS_CMD_DEFLECT_CALL,      {0, 0, 0, 0, 0, 0, 0}},
                                                         {"5",           MN_CALL_SUPS_CMD_ACT_CCBS,          {0, 0, 0, 0, 0, 0, 0}},
                                                         {VOS_NULL_PTR,  0,                                 {0, 0, 0, 0, 0, 0, 0}}
                                                        };

    *pulErrCode = MN_ERR_NO_ERROR;

    while (VOS_NULL_PTR != stChldOpTbl[i].pcMmiChldStr)
    {
        if(0 == VOS_MemCmp(pcInMmiStr,
                            stChldOpTbl[i].pcMmiChldStr,
                            MMI_Max(VOS_StrLen(pcInMmiStr), VOS_StrLen(stChldOpTbl[i].pcMmiChldStr))))
        {
            break;
        }
        i++;
    }

    if (VOS_NULL_PTR == stChldOpTbl[i].pcMmiChldStr)
    {
        return VOS_FALSE;
    }

    pstMmiOpParam->MmiOperationType = TAF_MMI_CALL_CHLD_REQ;

    switch(stChldOpTbl[i].enChldOpType)
    {
    case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB;
        break;

    case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH;
        break;

    case MN_CALL_SUPS_CMD_REL_CALL_X:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_CALL_X;
        pstMmiOpParam->MnCallSupsReq.callId = (VOS_UINT8)(pcInMmiStr[1] - '0');
        break;

    case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;
        break;

    case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X;
        pstMmiOpParam->MnCallSupsReq.callId = (VOS_UINT8)(pcInMmiStr[1] - '0');
        break;

    case MN_CALL_SUPS_CMD_BUILD_MPTY:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_BUILD_MPTY;
        break;

    case MN_CALL_SUPS_CMD_ECT:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_ECT;
        break;

    case MN_CALL_SUPS_CMD_DEFLECT_CALL:
        pstMmiOpParam->MnCallSupsReq.enCallSupsCmd = MN_CALL_SUPS_CMD_DEFLECT_CALL;
        break;

    default:
        /*��Ϊ��CCBS,��ΪĿǰ��֧��CCBS,��ʱûд�������*/
        *pulErrCode = MN_ERR_INVALIDPARM;
        break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MN_MmiStringParse
 ��������  : ��Mmi�ִ����н���������ǰ��MMI�ִ������ɶ�Ӧ�Ĳ������Լ�������Ҫ�Ĳ���
 �������  : pInMmiStr       - �����MMI�ִ�
             inCall          - ��ǰ���е�״̬���Ǵ��ں���״̬�����Ǵ��ڿ���״̬
 �������  : ppOutRestMmiStr - ʣ���ַ�������ʼ��ַ
             pMmiOpParam     - �������ͼ�����Ӧ�Ĳ���
 �� �� ֵ  : MN_ERR_NO_ERROR - �����ɹ�
             ���෵��ֵ      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ:������f_enClirOperate�ĸ�ֵ�Ƶ���������
  3.��    ��   : 2012��02��23��
    ��    ��   : l65478
    �޸�����   : DTS2012021604543,GCF���ԣ�CMMI��������ݴ���
  4.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
  5.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
*****************************************************************************/
TAF_UINT32 MN_MmiStringParse(
    TAF_CHAR                            *pInMmiStr,
    TAF_BOOL                            inCall,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    TAF_CHAR                            **ppOutRestMmiStr
)
{
    TAF_UINT32                          ulRslt = MN_ERR_NO_ERROR;
    TAF_UINT32                          ulRtrnRslt;
    TAF_UINT32                          ulStrLen;


    if (VOS_NULL_PTR == pInMmiStr)
    {
        MN_ERR_LOG("MN_MmiStringParse: Input Invalid Param");
        return MN_ERR_INVALIDPARM;
    }

    ulStrLen = VOS_StrLen(pInMmiStr);
    if (   (0 == ulStrLen)
        || ((VOS_TRUE != inCall) && (VOS_FALSE != inCall))
        || (VOS_NULL_PTR == pMmiOpParam) || (VOS_NULL_PTR == ppOutRestMmiStr))
    {
        MN_ERR_LOG("MN_MmiStringParse: Input Invalid Param");
        return MN_ERR_INVALIDPARM;
    }

    PS_MEM_SET(pMmiOpParam, 0, sizeof(MN_MMI_OPERATION_PARAM_STRU));

    /*�жϵ�ǰ�ǲ�����ʾIMEI����*/
    if (VOS_TRUE == MMI_JudgeImeiOperation(pInMmiStr,
                                           ppOutRestMmiStr,
                                           pMmiOpParam))
    {
        return MN_ERR_NO_ERROR;
    }

    /*�жϵ�ǰ�ǲ�����ʱģʽ�����ƻ��߼���CLIR����*/
    if (VOS_TRUE == MMI_JudgeTmpModeClirOp(pInMmiStr,
                                           ppOutRestMmiStr,
                                           pMmiOpParam))
    {
        /* ��Ϊ�����Ľ��뺯������Ӧ��ATģ���ҵ������ϣ�ɾ��ATģ��ҵ��ȫ�ֱ����ĸ�ֵ���� */
        return MN_ERR_NO_ERROR;
    }

    /*�жϵ�ǰ�Ĳ��������ǲ���PIN�������� */
    if (VOS_TRUE == MMI_JudgePinOperation(pInMmiStr,
                                          pMmiOpParam,
                                          ppOutRestMmiStr,
                                          &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*�жϵ�ǰ�Ĳ��������ǲ����޸�������� */
    if (VOS_TRUE == MMI_JudgePwdOperation(pInMmiStr,
                                          pMmiOpParam,
                                          ppOutRestMmiStr,
                                          &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*�жϵ�ǰ�Ĳ��������ǲ���������֪�ĺ����޹ز���ҵ�����*/
    if (VOS_TRUE == MMI_JudgeSsOperation(pInMmiStr,
                                         ppOutRestMmiStr,
                                         pMmiOpParam,
                                         &ulRtrnRslt))
    {
        return ulRtrnRslt;
    }

    /*
    ���ڶ��ִ��Ĵ�������Э��22.030�еĹ涨:
    "Entry of 1 or 2 characters defined in the 3GPP TS 23.038 [8] Default Alphabet followed by SEND"
    �Լ�22.030�еĶ�Ӧ������ͼ����
    */
    if ((2 == ulStrLen) || (1 == ulStrLen))
    {
        if (VOS_TRUE == inCall)
        {
            /*�ж��ǲ���CHLD����*/
            if (VOS_TRUE == MMI_JudgeChldOperation(pInMmiStr, pMmiOpParam, &ulRtrnRslt))
            {
                *ppOutRestMmiStr = pInMmiStr + VOS_StrLen(pInMmiStr);
                return ulRtrnRslt;
            }

            /* �������CHLD�����ô��Ϊ��USSD��������д��Ӧ�Ĳ��� */
            pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
            return MMI_FillInProcessUssdReqPara(pInMmiStr, ppOutRestMmiStr, pMmiOpParam);
        }
        else
        {
            /*����������£������'1'��ͷ����ô��ΪӦ�÷���һ������*/
            if ('1' == pInMmiStr[0])
            {
                ulRslt = MMI_FillInCallOrigPara(pInMmiStr,
                                                pMmiOpParam,
                                                ppOutRestMmiStr);
                if (MN_ERR_NO_ERROR != ulRslt)
                {
                    return ulRslt;
                }
                return MN_ERR_NO_ERROR;
            }
            else
            {
                /*�������'1'��ͷ����ôҲ����ΪUSSD�ִ������� */
                pMmiOpParam->MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;
                return MMI_FillInProcessUssdReqPara(pInMmiStr, ppOutRestMmiStr, pMmiOpParam);
            }
        }


    }

    return MMI_FillInCallOrigPara(pInMmiStr, pMmiOpParam, ppOutRestMmiStr);

    /* ��ɾ���������ַ�'P','W'�Ĵ����Ƿ��������д����ۣ�
       ��ʱ��֧�֣� */


}

/*lint -restore */



