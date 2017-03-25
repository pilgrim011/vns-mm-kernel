/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasMntn.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��7��4��
  ����޸�   :
  ��������   : CnasMntn.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��4��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_MNTN_H__
#define __CNAS_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "UsimPsInterface.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "msp_diag_comm.h"
#include  "NasOmInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ӡ��¼������ */
#define CNAS_MNTN_PRINT_MSG_MAX_NUM                         (10)

/* ��ȡMNTN�����ĵ�ַ */
#define CNAS_MNTN_GetCtxAddr()                              (&g_stCnasMntnCtx)

/* ��ȡ��ӡ������Ϣ��ַ */
#define CNAS_MNTN_GetPrintCtrlInfoAddr()                    (&((CNAS_MNTN_GetCtxAddr())->stPrintCtrlInfo))

/* ��ȡ��ӡ��Ϣ�����ַ */
#define CNAS_MNTN_GetPrintMsgAddr()                         (&((CNAS_MNTN_GetCtxAddr())->stPrintMsg))

/* ��ȡ��ӡ����: ���ڻ���SDT */
#define CNAS_MNTN_GetPrintType()                            ((CNAS_MNTN_GetPrintCtrlInfoAddr())->enPrintType)

/* ��ȡInfo�����ӡ���ƿ��� */
#define CNAS_MNTN_GetInfoPrintFlg()                         ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulInfoPrintFlg)

/* ��ȡNormal�����ӡ���ƿ��� */
#define CNAS_MNTN_GetNorPrintFlg()                          ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulNorPrintFlg)

/* ��ȡWARNING�����ӡ���ƿ��� */
#define CNAS_MNTN_GetWarnPrintFlg()                         ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulWarnPrintFlg)

/* ��ȡERR�����ӡ���ƿ��� */
#define CNAS_MNTN_GetErrPrintFlg()                          ((CNAS_MNTN_GetPrintCtrlInfoAddr())->ulErrPrintFlg)

#define CNAS_MNTN_LOG_AIR_MSG_OFFSET                        (4)

#define CNAS_INFO_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_INFO_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_INFO, &stPara);\
    }

#define CNAS_NORMAL_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_NORMAL_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_NORMAL, &stPara);\
    }

#define CNAS_WARNING_LOG(Mod,String)   { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_WARNING_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }


#define CNAS_WARNING_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_WARNING, &stPara);\
    }

#define CNAS_ERROR_LOG(Mod,String)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 0; \
    stPara.lPara1    = 0; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG1(Mod,String,Para1)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 1; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = 0; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG2(Mod,String,Para1,Para2)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 2; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = 0; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG3(Mod,String,Para1,Para2,Para3)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 3; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = 0; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

#define CNAS_ERROR_LOG4(Mod,String,Para1,Para2,Para3,Para4)    { \
    CNAS_MNTN_LOG_SAVE_PARA_STRU        stPara; \
    stPara.enFile    = THIS_FILE_ID; \
    stPara.ulLine    = __LINE__; \
    stPara.ulParaNum = 4; \
    stPara.lPara1    = (VOS_INT32)Para1; \
    stPara.lPara2    = (VOS_INT32)Para2; \
    stPara.lPara3    = (VOS_INT32)Para3; \
    stPara.lPara4    = (VOS_INT32)Para4; \
    CNAS_MNTN_LogSave(Mod, String, (LOG_LEVEL_EN)PS_LOG_LEVEL_ERROR, &stPara);\
    }

/* ��װ�����¼���Ϣͷ */
#define CNAS_CFG_MSG_HDR(pstMsg, ulSendPid, ulReceiPid, enEventId, ulEventLen)\
        (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
        (pstMsg)->ulSenderPid     = ulSendPid;\
        (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
        (pstMsg)->ulReceiverPid   = ulReceiPid;\
        (pstMsg)->ulLength        = (ulEventLen);\
        (pstMsg)->enMsgId         = (enEventId)


#define CNAS_SoftReboot(stCnasRebootInfo) CNAS_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (stCnasRebootInfo))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_MNTN_MSG_ID_BASE_ENUM
 �ṹ˵��  : CNAS��ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2014��07��04��
    ��    ��   : l60609
    �޸�����   : CNAS��ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
enum CNAS_MNTN_MSG_ID_BASE_ENUM
{
    /* 0x6000 ~ 0x6FFFΪLOG���� */
    ID_CNAS_MNTN_LOG_MSG_BASE           = 0x6000,                                   /* LOGģ����ά�ɲ���Ϣ��ʼ */

    /* 0x7000 ~ 0x7FFFΪXSD���� */
    ID_CNAS_MNTN_XSD_MSG_BASE           = 0x7000,                                   /* XSDģ����ά�ɲ���Ϣ��ʼ */

    /* 0x8000 ~ 0x8FFFΪPRL���� */
    ID_CNAS_MNTN_PRL_MSG_BASE           = 0x8000,                                   /* PRLģ���ά�ɲ���Ϣ��ʼ */

    /* 0x9000 ~ 0x9FFFΪPRL���� */
    ID_CNAS_MNTN_HSD_MSG_BASE           = 0x9000,                                   /* HSDģ���ά�ɲ���Ϣ��ʼ */
    ID_CNAS_MNTN_HSM_MSG_BASE           = 0xa000,

    ID_CNAS_MNTN_MSG_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_MSG_ID_BASE_ENUM_UINT32;


/*****************************************************************************
 ö����    : CNAS_MNTN_TIMER_ACTION_ENUM
 �ṹ˵��  : timer����
  1.��    ��   : 2014��07��11��
    ��    ��   : y00245242
    �޸�����   : �½�
*****************************************************************************/
enum CNAS_MNTN_TIMER_ACTION_ENUM
{
    CNAS_MNTN_TIMER_ACTION_START,

    CNAS_MNTN_TIMER_ACTION_STOP,

    CNAS_MNTN_TIMER_ACTION_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_TIMER_ACTION_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_MNTN_MSG_ID_ENUM
 �ṹ˵��  : CNAS��ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2014��07��04��
    ��    ��   : l60609
    �޸�����   : CNAS��ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
enum CNAS_MNTN_MSG_ID_ENUM
{
    ID_CNAS_MNTN_LOG_FSM_INFO_IND   = ID_CNAS_MNTN_LOG_MSG_BASE,     /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_FSM_INFO_STRU */

    ID_CNAS_MNTN_LOG_MSG_INFO_IND,                                   /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_MSG_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_TIMER_INFO_IND,                                 /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_TIMER_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ,                         /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU */

    ID_CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND,                       /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND,                       /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU */

    ID_CNAS_DIAG_LOG_READ_NV_INFO_IND,                               /*_H2ASN_MsgChoice  CNAS_DIAG_LOG_NV_INFO_IND_STRU */

    ID_CNAS_DIAG_LOG_WRITE_NV_INFO_IND,                              /*_H2ASN_MsgChoice  CNAS_DIAG_LOG_NV_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND,                         /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU */

    ID_CNAS_MNTN_LOG_1X_CSCH_DATA_IND,                               /*_H2ASN_MsgChoice  CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU */

    ID_CNAS_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_MNTN_PRINT_TYPE_ENUM
 �ṹ˵��  : CNAS��ģ���ӡ����:���ڴ�ӡ���߹���(eg:SDT)���
  1.��    ��   : 2014��07��04��
    ��    ��   : l60609
    �޸�����   : CNAS��ģ���ӡ����
*****************************************************************************/
enum CNAS_MNTN_PRINT_TYPE_ENUM
{
    CNAS_MNTN_PRINT_TYPE_SDT,                                                   /* Ĭ�Ϲ���SDT�� */
    CNAS_MNTN_PRINT_TYPE_COM,

    CNAS_MNTN_PRINT_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_MNTN_PRINT_TYPE_ENUM_UINT32;



enum CNAS_REBOOT_SCENE_ENUM
{
    CNAS_REBOOT_SCENE_TI_XSD_WAIT_CAS_SUSPEND_CNF_EXPIRED,
    CNAS_REBOOT_SCENE_TI_HSD_WAIT_CAS_SUSPEND_CNF_EXPIRED,

    CNAS_REBOOT_SCENE_BUTT
};

typedef VOS_UINT8 CNAS_REBOOT_SCENE_ENUM_UINT8;


/*****************************************************************************
 ö����    : CNAS_HANDSET_INFO_TYPE_ENUM
 ö��˵��  : �ֻ���Ϣ����
 1.��    ��   : 2015��5��18��
   ��    ��   : z00316370
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HANDSET_INFO_TYPE_ENUM
{
    CNAS_HANDSET_INFO_TYPE_STATE,
    CNAS_HANDSET_INFO_TYPE_HVERSION,

    CNAS_HANDSET_INFO_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HANDSET_INFO_TYPE_ENUM_UINT32;

enum    CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM
{
    CNAS_HRPD_OM_AIR_MSG_UP,             /* UPWARD */
    CNAS_HRPD_OM_AIR_MSG_DOWN,             /* DOWNWARD */

    CNAS_HRPD_OM_AIR_MSG_BUTT
};
typedef VOS_UINT8   CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM_UINT8;
/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_FSM_INFO_STRU
 �ṹ˵��  : ID_CNAS_MNTN_LOG_FSM_INFO_IND����Ϣ�ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    VOS_UINT32                          ulCurFsmId;
    VOS_UINT32                          ulCurFsmState;
    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           aucReserved[3];
}CNAS_MNTN_LOG_FSM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_TIMER_INFO_STRU
 �ṹ˵��  : ID_CNAS_MNTN_LOG_TIMER_INFO_IND����Ϣ�ṹ
 1.��    ��   : 2014��07��11��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    VOS_UINT32                          ulTimerId;                              /* timer ID */
    VOS_UINT32                          ulParam;                                /* timer ID��Ӧ�Ľ��ױ�ʶ */
    VOS_UINT32                          ulTimerLen;                             /* timer ʱ�� */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;                             /* timer ״̬: start or stop */
}CNAS_MNTN_LOG_TIMER_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_PRINT_CTRL_INFO
 �ṹ˵��  : ��ӡ������Ϣ
 1.��    ��   : 2014��07��04��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType;
    VOS_UINT32                          ulInfoPrintFlg;                         /* VOS_TRUE: ��ӡ VOS_FALSE: ����ӡ Ĭ��ֵVOS_FALSE */
    VOS_UINT32                          ulNorPrintFlg;                          /* VOS_TRUE: ��ӡ VOS_FALSE: ����ӡ Ĭ��ֵVOS_FALSE */
    VOS_UINT32                          ulWarnPrintFlg;                         /* VOS_TRUE: ��ӡ VOS_FALSE: ����ӡ Ĭ��ֵVOS_TRUE */
    VOS_UINT32                          ulErrPrintFlg;                          /* VOS_TRUE: ��ӡ VOS_FALSE: ����ӡ Ĭ��ֵVOS_TRUE */
}CNAS_MNTN_PRINT_CTRL_INFO;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_PRINT_RECORD_STRU
 �ṹ˵��  : SDT��ӡһ����ӡ��Ϣ����
 1.��    ��   : 2014��07��04��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[4];
}CNAS_MNTN_PRINT_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_PRINT_MSG_STRU
 �ṹ˵��  : ��ӡ��Ϣ
 1.��    ��   : 2014��07��04��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    CNAS_MNTN_PRINT_RECORD_STRU         astPrintRecord[CNAS_MNTN_PRINT_MSG_MAX_NUM];
}CNAS_MNTN_PRINT_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_SAVE_PARA_STRU
 �ṹ˵��  : log save�Ĳ���
 1.��    ��   : 2014��07��11��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_UINT32                          ulParaNum;
    VOS_INT32                           lPara1;
    VOS_INT32                           lPara2;
    VOS_INT32                           lPara3;
    VOS_INT32                           lPara4;
}CNAS_MNTN_LOG_SAVE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_MSG_INFO_IND_STRU
 �ṹ˵��  : ��OM�����Ϣ�ṹ
 1.��    ��   : 2014��07��07��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    CNAS_MNTN_PRINT_MSG_STRU            stPrintMsg;
}CNAS_MNTN_LOG_MSG_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU
 �ṹ˵��  : ����USIMM_GetFileReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2014��07��17��
   ��    ��   : l60609
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulRslt;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucReserved;
}CNAS_MNTN_LOG_USIMM_API_GET_FILE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU
 �ṹ˵��  : ����encodix����API���б���ʧ�ܣ��ϱ���ά�ɲ���Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2014��11��17��
   ��    ��   : l00256032
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_INT32                               lRslt;                              /* ����API���صĽ�� */
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType;
    VOS_UINT8                               aucReserved[3];
}CNAS_MNTN_LOG_ENCODE_ABNORMAL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU
 �ṹ˵��  : ����encodix����API���н���ʧ�ܣ��ϱ���ά�ɲ���Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2014��11��17��
   ��    ��   : l00256032
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_INT32                               lRslt;                              /* ����API���صĽ�� */
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enDecodeMsgType;
    VOS_UINT8                               aucReserved[3];
}CNAS_MNTN_LOG_DECODE_ABNORMAL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_DIAG_LOG_NV_INFO_IND_STRU
 �ṹ˵��  : CNAS��ȡNV��Ϣ���ϱ���ά�ɲ���Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��07��07��
   ��    ��   : y00322978
   �޸�����   : ����
 2.��    ��   : 2015��10��08��
   ��    ��   : t00323010
   �޸�����   : DTS2015092201636�޸Ľ�ͷ������

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];/* NV���� */
}CNAS_DIAG_LOG_NV_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU
 �ṹ˵��  : ��ά�ɲ⹫��״̬��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��08��13��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32            enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT8                               ucCsimStatus;
    VOS_UINT8                               aucReserved[3];                     /* �����ֽ� */
}CNAS_MNTN_LOG_COMMON_STATUS_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_MNTN_CTX_STRU
 �ṹ˵��  : ��ά�ɲ�����������
 1.��    ��   : 2014��07��04��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_PRINT_CTRL_INFO           stPrintCtrlInfo;

    CNAS_MNTN_PRINT_MSG_STRU            stPrintMsg;
}CNAS_MNTN_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MNTN_TIMER_INFO_STRU
 �ṹ˵��  : CNAS��ʱ����Ϣ�ṹ

 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerId;          /* ��ʱ����ʶ */
    VOS_UINT32                          ulParam;            /* ��ʱ��������ʶ, ����ͬtimer ID��ͬ���ױ�ʶ */
    VOS_UINT32                          ulTimerLen;         /* ��ʱ��ʱ�� */
    CNAS_MNTN_TIMER_ACTION_ENUM_UINT32  enTimerAct;         /* ��ʱ������: ֹͣ������ */
}CNAS_MNTN_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_USIMM_GETFILE_INFO_STRU
 �ṹ˵��  : ��ȡ�ļ�

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}CNAS_MNTN_LOG_GETFILE_INFO_STRU;




typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulFsmId;
    VOS_UINT32                          ulFsmState;
    CNAS_REBOOT_SCENE_ENUM_UINT8        enRebootScene;
    VOS_UINT8                           aucReserved[3];
}CNAS_REBOOT_INFO_STRU;


/*****************************************************************************
 Name    : CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU
 Description  : ����xcc �յ��� CSCH DATA IND �տ���Ϣ
 History     :
  1.Date     : 2016-01-04
    Author   : y00322978
    Modify   : create
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                          /* ��Ϣͷ */    /* _H2ASN_Skip */
    CNAS_MNTN_MSG_ID_ENUM_UINT32                            enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                                              usMsgDataLen;
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enCschMsgType;
    VOS_UINT8                                               ucReserv;
    VOS_UINT8                                               aucData[4];

}CNAS_MNTN_LOG_1X_CSCH_DATA_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    CNAS_MNTN_MSG_ID_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_MNTN_MSG_DATA                  stMsgData;
}CNAS_MNTN_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_MNTN_InitCtx(VOS_VOID);
VOS_VOID CNAS_MNTN_InitPrintMsgBuff(VOS_VOID);

VOS_VOID CNAS_MNTN_LogFsmInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState,
    VOS_UINT8                           ucConnectId
);
VOS_VOID CNAS_MNTN_LogSave(
    VOS_UINT32                          ulPid,
    VOS_CHAR                           *pcString,
    LOG_LEVEL_EN                        enLevel,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
);
VOS_VOID CNAS_MNTN_PrintToCom(
    LOG_LEVEL_EN                        enLevel,
    VOS_CHAR                           *pcString,
    CNAS_MNTN_LOG_SAVE_PARA_STRU       *pstPara
);
VOS_VOID CNAS_MNTN_PrintToOm(VOS_VOID);
VOS_VOID CNAS_MNTN_SetPrintType(
    CNAS_MNTN_PRINT_TYPE_ENUM_UINT32    enPrintType
);

/* Deleted by wx270776 for OM�ں�, 2015-08-21, begin */
/* Deleted by wx270776 for OM�ں�, 2015-08-21, end */

VOS_VOID CNAS_MNTN_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulRslt,
    CNAS_MNTN_LOG_GETFILE_INFO_STRU    *pstGetFileInfo
);


VOS_VOID  CNAS_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pMsg
);

VOS_VOID CNAS_MNTN_TraceTimerMsg(
    VOS_UINT32                          ulModuleId,
    CNAS_MNTN_TIMER_INFO_STRU          *pstMntnTimerInfo
);

VOS_UINT32 CNAS_MNTN_GetPrintCtrlFlg(
    LOG_LEVEL_EN                        enLevel
);

VOS_VOID CNAS_MNTN_LogEncodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8  enEncodeMsgType
);

VOS_VOID CNAS_MNTN_LogDecodeAbnormalInfoInd(
    VOS_UINT32                              ulModuleId,
    VOS_INT32                               lRslt,
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enDecodeMsgType
);

VOS_VOID CNAS_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo
);

extern VOS_VOID CNAS_HandsetInfoQry_Proc(
    VOS_UINT32                          ulInfoType
);

extern VOS_VOID CNAS_HandsetStateInfo_Proc(
    VOS_UINT32                          ulInfoType
);

extern VOS_VOID CNAS_HandsetHighVerInfo_Proc(
    VOS_UINT32                          ulInfoType
);


VOS_VOID CNAS_MNTN_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
);

VOS_VOID CNAS_MNTN_LogWriteNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
);

VOS_VOID CNAS_MNTN_LogKeyEvent(
    NAS_OM_EVENT_ID_ENUM                enEvent,
    VOS_UINT32                          ulSendPid
);

VOS_VOID CNAS_MNTN_LogOmAirMsg(
    CNAS_HRPD_OM_AIR_MSG_UP_DOWN_ENUM_UINT8                 ulDir,
    VOS_UINT16                                              ulAirMsgId,
    VOS_UINT32                                              ulSendPid,
    VOS_UINT32                                              ulLength,
    VOS_UINT8                                              *pucData
);

VOS_VOID CNAS_MNTN_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
);
VOS_VOID CNAS_MNTN_UpdateMsgExitTime( VOS_VOID );
VOS_VOID CNAS_MNTN_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
);



VOS_VOID CNAS_MNTN_LogCommonStatusInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT8                           ucCardStatus
);
VOS_VOID CNAS_MNTN_Log1xCschDataIndMsg(
    VOS_UINT32                                              ulPid,
    VOS_UINT16                                              usMsgDataLen,
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enCschMsgType,
    VOS_UINT8                                              *pucData
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasMntn.h */
