

#ifndef __TAF_COMMON_H__
#define __TAF_COMMON_H__


/******************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "v_id.h"
#include "product_config.h"
#include "TafApi.h"
#include "mdrv.h"
#include "errorlog.h"


/******************************************************************************/

/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*========================================================*/

/* ��־������ҵ��ı��뿪�أ����ⵥA32D12736 */
#define  TAF_FEATURE_NO_VOICE_SERVICE
/*TAFM�ϱ��ṹ��optionλ���ֽ��ܸ�����
��ģ����Դӽṹ��ʼ��ַmemset TAF_EVT_OP_LEN���ֽڴﵽ����ֵĿ��*/
#define   TAF_EVT_OP_LEN   4

/*----------TAFM�����ӿ�----------*/
/*TAF��ģ��ID*/
#ifndef SUBMOD_NULL
#define  SUBMOD_NULL 0
#endif
#define  TAF_CCA     1
#define  TAF_APS     2
#define  TAF_SMA     3
#define  TAF_SSA     4
#define  TAF_MMA     5
#define   TAF_ALL_SUBMODULE   0xFF    /*������ģ��*/

/*��ʱ��V200Ҫɾ��*/
#define   TAF_TAFM             0
#define   TAF_SPEECH           1
#define   TAF_STATUS           2
#define   TAF_MAX_SPEECH_TI    14


/*��ӡ��������ӳ�䵽OM����ĺ�*/
#define    INFO_PRINT      PS_LOG_LEVEL_INFO
#define    NORMAL_PRINT    PS_LOG_LEVEL_NORMAL
#define    WARNING_PRINT   PS_LOG_LEVEL_WARNING
#define    ERROR_PRINT     PS_LOG_LEVEL_ERROR



#define TAF_PRINT(  Module,  PrintLevel,  Str)     \
           TAF_LOG(Module, 0, PrintLevel, Str)

#define TAFM_PRINT(Str)     \
           TAF_LOG(TAF_TAFM, 0, ERROR_PRINT, Str)

#define TAFM_PRINT1(Str, Para1)     \
           TAF_LOG1(TAF_TAFM, 0, ERROR_PRINT, Str, Para1)

#define TAFM_PRINT2(Str, Para1, Para2)    \
           TAF_LOG2(TAF_TAFM, 0, ERROR_PRINT, Str, Para1, Para2)





/*�����ӿ�*/
/*�������ý���ϱ�*/
VOS_VOID Taf_ParaSetResult( VOS_UINT16           ClientId,
                        VOS_UINT8                  OpId,
                        TAF_PARA_SET_RESULT     Result,
                            TAF_PARA_TYPE     QueryPara,
                        VOS_VOID                    *pPara );


/*******************************************************************************/

#define SMA_INFO_LOG(String)            TAF_LOG(WUEPS_PID_TAF,  TAF_SMA, PS_LOG_LEVEL_INFO,    String)
#define SMA_NORM_LOG(String)            TAF_LOG(WUEPS_PID_TAF,  TAF_SMA, PS_LOG_LEVEL_NORMAL,  String)
#define SMA_WARN_LOG(String)            TAF_LOG(WUEPS_PID_TAF,  TAF_SMA, PS_LOG_LEVEL_WARNING, String)
#define SMA_ERR_LOG(String)             TAF_LOG(WUEPS_PID_TAF,  TAF_SMA, PS_LOG_LEVEL_ERROR,   String)
#define SMA_LOG1(String, Para1)         TAF_LOG1(WUEPS_PID_TAF, TAF_SMA, PS_LOG_LEVEL_INFO,    String, Para1)
#define SMA_LOG2(String, Para1, Para2)  TAF_LOG2(WUEPS_PID_TAF, TAF_SMA, PS_LOG_LEVEL_NORMAL,  String, Para1, Para2)

/*�з���ֵ����Ϣ�����궨��*/
#define PS_ALLOC_MSG_RTN_FAIL(pMsg, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMsg = (VOS_VOID *)PS_ALLOC_MSG((ulPid),(ulLen) - VOS_MSG_HEAD_LENGTH))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_AllocMsg ERR! len:",(VOS_INT32)(ulLen));\
        return  VOS_ERR;\
    }

/*δ������Ϣ�ṹ,������Ϣ�ڴ�,������ڴ泤�Ȳ�����Ϣ��ͷ����*/
#define PS_ALLOC_MSG_RTN_FAIL_WITHOUT_HEADER_LEN(pMsg, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMsg = (VOS_VOID *)PS_ALLOC_MSG((ulPid),(ulLen)))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_AllocMsg ERR! len:",(VOS_INT32)(ulLen));\
        return  VOS_ERR;\
    }

/*δ������Ϣ�ṹ,������Ϣ�ڴ�,������ڴ泤�Ȳ�����Ϣ��ͷ����*/
#define PS_ALLOC_MSG_WITHOUT_HEADER_LEN(pMsg, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMsg = (VOS_VOID *)PS_ALLOC_MSG((ulPid),(ulLen)))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_AllocMsg ERR! len:",(VOS_INT32)(ulLen));\
        return;\
    }

/*���˳���ǰ��������Ϣ�����궨��*/
#define PS_ALLOC_MSG_UNRTN(pMsg, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMsg = (VOS_VOID *)PS_ALLOC_MSG((ulPid),(ulLen) - VOS_MSG_HEAD_LENGTH))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_AllocMsg ERR! len:",(VOS_INT32)(ulLen));\
    }

/*���˳���ǰ������δ������Ϣ�ṹ,������Ϣ�ڴ�,������ڴ泤�Ȳ�����Ϣ��ͷ����*/
#define PS_ALLOC_MSG_UNRTN_WITHOUT_HEADER_LEN(pMsg, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMsg = (VOS_VOID *)PS_ALLOC_MSG((ulPid),(ulLen)))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_AllocMsg ERR! len:",(VOS_INT32)(ulLen));\
    }

/*��Ϣ�ͷź궨��*/
#define PS_FREEMSG(ulPID,pMsg)\
        VOS_FreeMsg((ulPID), (pMsg));

/*�з���ֵ�ڴ�����궨��*/
#define PS_MEM_ALLOC_RTN_FAIL(pMem, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMem = (VOS_VOID *)VOS_MemAlloc((ulPid), DYNAMIC_MEM_PT, (ulLen)))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_MemAlloc ERR! len:",(VOS_INT32)(ulLen));\
        return VOS_ERR;\
    }

/*���˳���ǰ�������ڴ�����궨��*/
#define PS_MEM_ALLOC_UNRTN(pMem, ulPid , ulLen) \
    if(VOS_NULL_PTR == (pMem = (VOS_VOID *)VOS_MemAlloc((ulPid), DYNAMIC_MEM_PT, (ulLen)))) \
    {\
        TAF_LOG1((ulPid), PS_SUBMOD_NULL, PS_LOG_LEVEL_ERROR," VOS_MemAlloc ERR! len:",(VOS_INT32)(ulLen));\
    }

#define TAF_COMM_BUILD_USIM_GET_FILE_INFO(pstGetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara) \
{ \
    (pstGetfileInfo)->usEfId       = usEfIdPara; \
    (pstGetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstGetfileInfo)->enAppType    = enAppTypePara; \
    (pstGetfileInfo)->ucRsv        = 0; \
}

#define TAF_COMM_BUILD_USIM_SET_FILE_INFO(pstSetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara, ulEfLenPara, pucEfPara) \
{ \
    (pstSetfileInfo)->usEfId       = usEfIdPara; \
    (pstSetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstSetfileInfo)->enAppType    = enAppTypePara; \
    (pstSetfileInfo)->ucRsv        = 0; \
    (pstSetfileInfo)->ulEfLen      = ulEfLenPara; \
    (pstSetfileInfo)->pucEfContent = pucEfPara; \
}

/*========================================================*/
#ifdef __cplusplus
}
#endif
/******************************************************************************/

/*============================================================================*/
#endif          /* __TAF_COMMON_H__ */

