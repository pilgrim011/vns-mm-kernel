/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallMntn.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��9��20��
  ����޸�   :
  ��������   : TafXCallMntn.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��20��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_X_CALL_MNTN_H__
#define __TAF_X_CALL_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"


#include "TafMntn.h"
#include "TafXCallCtx.h"
#include "TafXCallKmcCommType.h"
#include "TafXCallProcEccSrv.h"
#include "TafSdcCtx.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_MNTN_LOG_KMC_MSG_MAX_KMC_PUB_KEY_LEN    (48)
#define TAF_XCALL_MNTN_LOG_MEID_LEN                       (7)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XCALL_MNTN_MSG_ID_ENUM
 �ṹ˵��  : TAF XCALL ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2014��09��20��
    ��    ��   : l60609
    �޸�����   : TAF XCALL ģ�鷢�͸�OM�Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
enum TAF_XCALL_MNTN_MSG_ID_ENUM
{
    ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND   = ID_TAF_MNTN_XCALL_BASE,             /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CALL_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT,                                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU*/
    ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD,
    ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU*/

    ID_TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION,                                /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_INFO,                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_INFO,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME,                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME,                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO,                              /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU */
    ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND,                               /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU */
    ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND,                                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND,                          /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP,                          /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO,                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO,                       /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO,                                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU */

    ID_TAF_XCALL_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32;


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
 �ṹ��    : TAF_XCALL_MNTN_LOG_CALL_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND����Ϣ�ṹ
 1.��    ��   : 2014��09��20��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
}TAF_XCALL_MNTN_LOG_CALL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT����Ϣ�ṹ
 1.��    ��   : 2014��09��20��
   ��    ��   : l60609
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
}TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT����Ϣ�ṹ
 1.��    ��   : 2015��08��09��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulEmcRedialPeriod;                      /* �������ز���ʱ��ʱ�� */
} TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL����Ϣ�ṹ
 1.��    ��   : 2015��08��18��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulStartAndStopContDtmfInterval;         /* Stop Cont DTMF ��Start Cont DTMF��Ϣ���ͼ����ʱ��ʱ�� */
} TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION����Ϣ�ṹ
 1.��    ��   : 2015��08��09��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_STD_TIME_ZONE_TYPE_STRU         stMsgTimeZone;                          /* ��Ϣ�д���ʱ�����ͽṹ�� */
    TAF_STD_TIME_ZONE_TYPE_STRU         stLastTimeZone;                         /* ϵͳ��¼�Ĳ���ʱ��ṹ�� */
    VOS_UINT64                          ullStdSysTimeInterval;                  /* ��ǰϵͳʱ���� */
    VOS_UINT64                          ullStdLastTimeInterval;                 /* ��ǰϵͳ��¼��ʱ���� */
    VOS_UINT64                          ullStdMsgTimeInterval;                  /* ��Ϣ�д���ʱ���� */
} TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPubKey[TAF_XCALL_MNTN_LOG_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
} TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucEccSrvCap;        /* ECC��������: TRUE -- ֧��ECC����FALSE -- ��֧��ECC���� */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC����״̬: TRUE -- ECC����򿪣�FALSE -- ECC����ر� */
    VOS_UINT8                           aucReserved[2];
} TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_LEN����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                          usDelayEncVoiceReqTimerlen;             /* �ӳ�ʱ�� */
    VOS_UINT16                          usRemoteCtrlAnswerTimerLen;             /* Զ�̿���Ӧ��ʱ�� */
} TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU              stMoKeyReq;                     /* ������Կ���� */
} TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU              stMoKeyRsp;                     /* ������Կ��Ӧ */
} TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU       stMtEncryptInd;                 /* ���м���֪ͨ��Ϣ */
} TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU              stMtKeyReq;                     /* ������Կ���� */
} TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU              stMtKeyRsp;                     /* ������Կ��Ӧ */
} TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_ERR_IND_STRU              stErrInd;                       /* ����֪ͨ */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU   stPubKeyUpdateInd;              /* KMC��Կ���� */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU   stPubKeyUpdateRsp;              /* KMC��Կ������Ӧ */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU   stPubKeyUpdateAck;              /* KMC��Կ����ȷ�� */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* ������ */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU  stRemoteCtrlInd;                /* Զ�̿���ָ�� */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU  stRemoteCtrlRsp;                /* Զ�̿���ָ����Ӧ */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* ״̬������ */
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32    enEventType;
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32               enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* ״̬������ */
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32 enEventType;
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                  enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* ״̬������ */
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32      enEventType;
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32             enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO����Ϣ�ṹ
  1.��    ��   : 2015��10��26��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32       enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT8                               aucImsi[TAF_SDC_MAX_IMSI_LEN];
    VOS_UINT8                               aucMeId[TAF_XCALL_MNTN_LOG_MEID_LEN];
    VOS_UINT32                              ulEsn;
    TAF_ECC_CALL_BCD_NUM_STRU               stCalledNum;
    TAF_XCALL_PLAIN_TEXT_INFO_STRU          stPlainTextInfo;
} TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU;

#endif

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
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_MsgChoice_Export TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XCALL_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_XCALL_MNTN_MSG_DATA             stMsgData;
}TAF_XCALL_MNTN_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID);
VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID);

VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID);

VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_MNTN_LogTimeStampValidation(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstMsgTimeZone,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastTimeZone,
    VOS_UINT64                          ullStdSysTimeInterval,
    VOS_UINT64                          ullStdLastTimeInterval,
    VOS_UINT64                          ullStdMsgTimeInterval
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncPubKeyAndVerInfo(
    VOS_UINT8                           ucVerNum,
    VOS_UINT8                          *pucPubKey
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptCapCfgPara(
    VOS_UINT8                           ucEccSrvCap,
    VOS_UINT8                           ucEccSrvStatus
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastInfoEraseTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastPassworResetTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptTimerCfgInfo(
    VOS_UINT16                                              usDelayEncVoiceReqTimerLen,
    VOS_UINT16                                              usRemoteCtrlAnswerTimerLen
);

VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMoKeyReq
);

VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMoKeyRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgMtEncryptInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU                  *pstMtEncryptInd
);

VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMtKeyReq
);

VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMtKeyRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgErrInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ERR_IND_STRU                         *pstErrInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU              *pstPubKeyUpdateInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateRsp(
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU              *pstPubKeyUpdateRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateAck(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU              *pstPubKeyUpdateAck
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU             *pstRemoteCtrlInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdRsp(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU             *pstRemoteCtrlRsp
);

VOS_VOID TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEventType,
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enState
);

VOS_VOID TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType,
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enState
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptState(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType,
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enState
);

VOS_VOID TAF_XCALL_MNTN_LogCipherText(
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstCipherInfo,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum
);

VOS_VOID TAF_XCALL_MNTN_LogKmcDecMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);

VOS_VOID TAF_XCALL_MNTN_LogKmcEncMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);
#endif

/* Deleted by wx270776 for OM�ں�, 2015-6-28, begin */
/* Deleted by wx270776 for OM�ں�, 2015-6-28, end */
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

#endif /* end of TafXCallMntn.h */
