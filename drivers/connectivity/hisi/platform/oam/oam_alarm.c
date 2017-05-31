/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oam_alarm.c
  �� �� ��   : ����
  ��    ��   : c59720
  ��������   : 2012��9��26��
  ����޸�   :
  ��������   :  OAM��ά�ɲ���ALARM�ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��26��
    ��    ��   : c59720
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if 0
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oam_alarm.h"
#include "wlan_spec.h"
#include "oam_main.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : oam_alarm_get_switch
 ��������  : ��ȡALARMģ����ܿ���
 �������  : uc_vap_id       : ��ǰ�����VAP ID
 �������  : pen_switch_type : ALARMģ��Ŀ���״̬
 �� �� ֵ  : 1) OAL_ERR_CODE_PTR_NULL: ��ָ��
             2) OAL_SUCC: �ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_alarm_get_switch(
                oal_uint8              uc_vap_id,
                oal_switch_enum_uint8 *pen_switch_type)
{
    if (OAL_PTR_NULL == pen_switch_type)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    *pen_switch_type = g_st_oam_mng_ctx.ast_alarm_ctx[uc_vap_id].en_alarm_switch;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_set_switch
 ��������  : ����ALARMģ����ܿ���
 �������  : uc_vap_id       : ��ǰ�����VAP ID
             en_switch_type  : ALARM����״̬
 �������  : ��
 �� �� ֵ  : OAL_SUCC: ���óɹ�
             OAL_FAIL: ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_alarm_set_switch(
                oal_uint8              uc_vap_id,
                oal_switch_enum_uint8  en_switch_type)
{
    if (en_switch_type >= OAL_SWITCH_BUTT)
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    g_st_oam_mng_ctx.ast_alarm_ctx[uc_vap_id].en_alarm_switch = en_switch_type;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_format_string
 ��������  : ���ݸ�ʽ,���澯��Ϣд�뵽ָ�����ļ���
 �������  : 1) �������
             2) ��������
             3) VAP���
             4) �ļ�ID
             5) �к�
             6) ģ��ID
             7) �澯����
 �������  : ��
 �� �� ֵ  : OAL_SUCC :�ɹ�;������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  oam_alarm_format_string(
                oal_int8                       *pac_output_data,
                oal_uint16                      ul_data_len,
                oal_uint8                       uc_vap_id,
                oal_uint16                      us_file_no,
                oal_uint32                      ul_file_line_no,
                oam_module_id_enum_uint16       en_mod,
                oam_alarm_type_enum_uint16      en_alarm_type)
{
    oal_uint32 ul_tick;

    if (OAL_PTR_NULL == pac_output_data)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡϵͳTICKֵ */
    ul_tick = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ��ʽ��������� */
    OAL_SPRINTF(pac_output_data,
                ul_data_len,
                "��ALARM��:Tick=%u, FileId=%d, LineNo=%u, VAP =%d, ModId=%d,ALARM TYPE = %u\r\n",
                ul_tick,
                us_file_no,
                ul_file_line_no,
                uc_vap_id,
                en_mod,
                en_alarm_type);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_print_to_std
 ��������  : ��alarm��Ϣ��ӡ����׼�������
 �������  : uc_vap_id       : ��ǰ�����VAP ID
             us_file_no      : �ļ�ID
             ul_file_line_no : �к�
             en_mod          : ģ��
             en_alarm_type   : ��ǰVAP��Ҫ�ϱ��ĸ澯�¼���Ϣ
 �������  : ��
 �� �� ֵ  : �������سɹ�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  oam_alarm_print_to_std(
                oal_uint8                   uc_vap_id,
                oal_uint16                  us_file_no,
                oal_uint32                  ul_file_line_no,
                oam_module_id_enum_uint16   en_mod,
                oam_alarm_type_enum_uint16  en_alarm_type)
{
    oal_int8   ac_output_data[OAM_PRINT_FORMAT_LENGTH];  /* ���ڱ���д�뵽�ļ��е����� */
    oal_uint32 ul_rslt;

    ul_rslt = oam_alarm_format_string(ac_output_data,
                                      OAM_PRINT_FORMAT_LENGTH,
                                      uc_vap_id,
                                      us_file_no,
                                      ul_file_line_no,
                                      en_mod,
                                      en_alarm_type);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    ul_rslt = oam_print_to_console(ac_output_data);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_print_to_file
 ��������  : ��alarm��Ϣ��ӡ���ļ���
 �������  : uc_vap_id       : ��ǰ�����VAP ID
             us_file_no      : �ļ�ID
             ul_file_line_no : �к�
             en_mod          : ģ��
             en_alarm_type   : ��ǰVAP��Ҫ�ϱ��ĸ澯�¼���Ϣ
 �������  : ��
 �� �� ֵ  : �������سɹ�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  oam_alarm_print_to_file(
                oal_uint8                   uc_vap_id,
                oal_uint16                  us_file_no,
                oal_uint32                  ul_file_line_no,
                oam_module_id_enum_uint16   en_mod,
                oam_alarm_type_enum_uint16  en_alarm_type)
{
    oal_int8   ac_output_data[OAM_PRINT_FORMAT_LENGTH]; /* ���ڱ���д�뵽�ļ��е����� */
    oal_uint32 ul_rslt;

    ul_rslt = oam_alarm_format_string(ac_output_data,
                                      OAM_PRINT_FORMAT_LENGTH,
                                      uc_vap_id,
                                      us_file_no,
                                      ul_file_line_no,
                                      en_mod,
                                      en_alarm_type);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    ul_rslt = oam_print_to_file(ac_output_data);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_print_to_sdt
 ��������  : ��alarm��Ϣ��ӡ��PC���⹤��ƽ̨
 �������  : uc_vap_id       : ��ǰ�����VAP ID
             us_file_no      : �ļ�ID
             ul_file_line_no : �к�
             en_mod          : ģ��
             en_alarm_type   : ��ǰVAP��Ҫ�ϱ��ĸ澯�¼���Ϣ
 �������  : ��
 �� �� ֵ  : �������سɹ�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  oam_alarm_print_to_sdt(
                oal_uint8                   uc_vap_id,
                oal_uint16                  us_file_no,
                oal_uint32                  ul_file_line_no,
                oam_module_id_enum_uint16   en_mod,
                oam_alarm_type_enum_uint16  en_alarm_type)
{
    oal_int8   ac_output_data[OAM_PRINT_FORMAT_LENGTH]; /* ���ڱ���д�뵽�ļ��е����� */
    oal_uint32 ul_rslt;

    ul_rslt = oam_alarm_format_string(ac_output_data,
                                      OAM_PRINT_FORMAT_LENGTH,
                                      uc_vap_id,
                                      us_file_no,
                                      ul_file_line_no,
                                      en_mod,
                                      en_alarm_type);
    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    ul_rslt = oam_upload_log_to_sdt(ac_output_data);

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_report
 ��������  : �ϱ�ALARM�¼���
 �������  : uc_vap_id       : ��ǰ�����VAP ID
             us_file_no      : �ļ�ID
             ul_file_line_no : �к�
             en_mod          : ģ��
             en_alarm_type   : ��ǰVAP��Ҫ�ϱ��ĸ澯�¼���Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��26��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_alarm_report(
                oal_uint8                   uc_vap_id,
                oal_uint16                  us_file_no,
                oal_uint32                  ul_file_line_no,
                oam_module_id_enum_uint16   en_mod,
                oam_alarm_type_enum_uint16  en_alarm_type)
{
    oal_uint32 ul_rslt;

    if (en_alarm_type >= OAM_ALARM_TYPE_BUTT)
    {
        return OAL_FAIL;
    }

    if (uc_vap_id >= WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* ��ӦVAP����Ϊ���ϱ�ALARMģʽ */
    if (OAL_SWITCH_OFF == g_st_oam_mng_ctx.ast_alarm_ctx[uc_vap_id].en_alarm_switch)
    {
        return OAL_SUCC;
    }

    switch (g_st_oam_mng_ctx.en_output_type)
    {
        /* ���������̨ */
        case OAM_OUTPUT_TYPE_CONSOLE:
            ul_rslt = oam_alarm_print_to_std(uc_vap_id, us_file_no, ul_file_line_no, en_mod, en_alarm_type);

            break;

        /* ������ļ�ϵͳ�� */
        case OAM_OUTPUT_TYPE_FS:
            ul_rslt = oam_alarm_print_to_file(uc_vap_id, us_file_no, ul_file_line_no, en_mod, en_alarm_type);
            break;

        /* �����PC����⹤��ƽ̨ */
        case OAM_OUTPUT_TYPE_SDT:
            ul_rslt = oam_alarm_print_to_sdt(uc_vap_id, us_file_no, ul_file_line_no, en_mod, en_alarm_type);

            break;

        /* ��Ч���� */
        default:
            ul_rslt = OAL_ERR_CODE_INVALID_CONFIG;

            break;
    }

    if (OAL_SUCC != ul_rslt)
    {
        return ul_rslt;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_alarm_init
 ��������  : OAMģ��ALARM��ʼ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ���ɹ��򷵻�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��26��
    ��    ��   : c59720
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_alarm_init(oal_void)
{
    oal_uint32 ul_rslt;
    oal_uint32 ul_loop;

    /* ��ʼ������VAPĬ��ALARM����Ϊ�� */
    for (ul_loop = 0; ul_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; ul_loop++)
    {
        ul_rslt = oam_alarm_set_switch((oal_uint8)ul_loop, OAL_SWITCH_ON);
        if (OAL_SUCC != ul_rslt)
        {
            return ul_rslt;
        }
    }

    return OAL_SUCC;
}


/*lint -e19*/
oal_module_symbol(oam_alarm_set_switch);
oal_module_symbol(oam_alarm_get_switch);
oal_module_symbol(oam_alarm_report);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

