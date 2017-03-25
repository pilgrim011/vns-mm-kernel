/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSndInternalMsg.h
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��14��
  ����޸�   :
  ��������   : CnasXsdSndInternalMsg.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��14��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XSD_SND_INTERNAL_MSG_H__
#define __CNAS_XSD_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CnasXsdCtx.h"
#include "CnasPrlApi.h"
#include "xsd_xreg_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "CnasPrlMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef DMT
#define CNAS_XSD_MAX_MODIFIED_PRL_SYS_RECORD_NUM            (50)
#define CNAS_XSD_MAX_MODIFIED_PRL_ACQ_RECORD_NUM            (10)
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_XSD_INTERNAL_MSG_TYPE_ENUM
 ö��˵��  : �ڲ���Ϣ��ö�ٶ���
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_XSD_XSD_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_XSD_XSD_ABORT_REQ_STRU*/
    ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF       = 0x0001, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_BSR_RSLT_CNF             = 0x0002, /* _H2ASN_MsgChoice CNAS_XSD_XSD_BSR_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF       = 0x0003, /* _H2ASN_MsgChoice CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_REDIRECTION_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_XSD_XSD_REDIRECTION_IND_STRU*/
    ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF     = 0x0005, /* _H2ASN_MsgChoice CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU*/
    ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ      = 0x0006, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU*/
    ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF = 0x0007, /* _H2ASN_MsgChoice CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*/

#ifdef DMT
    ID_CNAS_XSD_XSD_TEST_CFG_REQ,                      /* _H2ASN_MsgChoice CNAS_XSD_XSD_TEST_CFG_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ,         /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU*/
    ID_CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ,          /* _H2ASN_MsgChoice CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU*/
#endif

    ID_CNAS_XSD_XSD_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : CNAS_XSD_BSR_RESULT_ENUM
 ö��˵��  : BSR�������
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_BSR_RESULT_ENUM
{
    CNAS_XSD_BSR_RESULT_SUCCESS         = 0x00000000,
    CNAS_XSD_BSR_RESULT_FAILURE         = 0x00000001,
    CNAS_XSD_BSR_RESULT_ABORTED         = 0x00000002,
    CNAS_XSD_BSR_RESULT_BUTT            = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_BSR_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XSD_ABORT_TYPE_ENUM
 ö��˵��  : Abort����
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_ABORT_TYPE_ENUM
{
    CNAS_XSD_ABORT_TYPE_IMMEDIATELY     = 0x00000000,
    CNAS_XSD_ABORT_TYPE_DELAY           = 0x00000001,
    CNAS_XSD_ABORT_TYPE_BUTT            = 0x00000002
};
typedef VOS_UINT32 CNAS_XSD_ABORT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XSD_SWITCH_ON_RESULT_ENUM
 ö��˵��  : �������
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_SWITCH_ON_RESULT_ENUM
{
    CNAS_XSD_SWITCH_ON_RESULT_SUCCESS   = 0x00000000,
    CNAS_XSD_SWITCH_ON_RESULT_FAILURE   = 0x00000001,
    CNAS_XSD_SWITCH_ON_RESULT_ABORTED   = 0x00000002,
    CNAS_XSD_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_SWITCH_ON_RESULT_ENUM_UINT32;


/* CNAS_XSD_REDIR_RESULT_ENUM_UINT32 */
/*****************************************************************************
 ö����    : CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM
 ö��˵��  : ϵͳ������
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM
{
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000003
};
typedef VOS_UINT32 CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;


enum CNAS_XSD_REDIRECTION_RESULT_ENUM
{
    CNAS_XSD_REDIRECTION_RESULT_SUCCESS                 = 0x00000000,
    CNAS_XSD_REDIRECTION_RESULT_FAILURE                 = 0x00000001,
    CNAS_XSD_REDIRECTION_RESULT_ABORTED                 = 0x00000002,
    CNAS_XSD_REDIRECTION_RESULT_NORF                    = 0x00000004,
    CNAS_XSD_REDIRECTION_RESULT_BUTT                    = 0x00000005
};
typedef VOS_UINT32 CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32;


enum CNAS_XSD_POWEROFF_RSLT_ENUM
{
    CNAS_XSD_POWEROFF_RSLT_SUCCESS,
    CNAS_XSD_POWEROFF_RSLT_FAIL,

    CNAS_XSD_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32;


enum CNAS_XSD_POWEROFF_REASON_ENUM
{
    CNAS_XSD_POWEROFF_REASON_POWER_OFF,
    CNAS_XSD_POWEROFF_REASON_POWER_SAVE,

    CNAS_XSD_POWEROFF_REASON_BUTT
};
typedef VOS_UINT32 CNAS_XSD_POWEROFF_REASON_ENUM_UINT32;


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
 �ṹ��    : CNAS_XSD_XSD_ABORT_REQ_STRU
 �ṹ˵��  : XSD������ֹ״̬����Ϣ�Ľṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_ABORT_TYPE_ENUM_UINT32                         enAbortType;
}CNAS_XSD_XSD_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU
 �ṹ˵��  : XSD���Ϳ���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_BSR_RSLT_CNF_STRU
 �ṹ˵��  : XSD����BSR���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_BSR_RESULT_ENUM_UINT32                         enRslt;
}CNAS_XSD_XSD_BSR_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU
 �ṹ˵��  : XSD���͹ػ�ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
 2. Date      : 2015-04-11
    Author    : a00295761
    Content   : Added POwer off result enum to indicate if Power Off message or Power Save message
                is put in the internal message queue.
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt;
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason;

}CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_REDIRECTION_IND_STRU
 �ṹ˵��  : XSD�����ض���ָʾ���ݽṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6 Modified
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_REDIRECTION_INFO_STRU                          stRedirectionInfo;
}CNAS_XSD_XSD_REDIRECTION_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU
 �ṹ˵��  : XSD�����ض�����ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6 Modified
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enRslt;
}CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU
 �ṹ˵��  : XSDϵͳ��ȡ�ڲ���Ϣ�ṹ
 1.��    ��   : 2014��8��7��
   ��    ��   : l60609
   �޸�����   : ϵͳ��ȡ�ڲ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    VOS_UINT32                                              ulFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM];
}CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU
 �ṹ˵��  : XSDϵͳ��ȡ���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : ״̬�����ȷ����Ϣ�Ľṹ
 2.��    ��   : 2014��12��2��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 5 Modfied
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;
    VOS_UINT8                                               ucImmediateSysAcq;
    VOS_UINT8                                               aucRsv[3];
}CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU;

#ifdef DMT
/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_TEST_CFG_REQ_STRU
 �ṹ˵��  : ����DMT�������ã�������صĲ�����Ϣ
 1.��    ��   : 2014��10��30��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulCurSlice;
}CNAS_XSD_XSD_TEST_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU
 �ṹ˵��  : ���޸ĵ�PRLϵͳ��¼��Ϣ
 1.��    ��   : 2014��12��11��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqRecordIndex;
    VOS_UINT8                                               aucReserved[2];
    CNAS_PRL_MNTN_ACQ_RECORD_STRU                           stAcqRecordInfo;
}CNAS_MODIFIED_PRL_ACQ_RECORD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU
 �ṹ˵��  : ����DMT����, �����޸�PRLϵͳ���в���record��Ϣ
 1.��    ��   : 2015��1��17��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usRecNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_MODIFIED_PRL_ACQ_RECORD_INFO_STRU                  astAcqRecord[CNAS_XSD_MAX_MODIFIED_PRL_ACQ_RECORD_NUM];
}CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU
 �ṹ˵��  : ���޸ĵ�PRLϵͳ��¼��Ϣ
 1.��    ��   : 2014��12��11��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSysRecordIndex;
    VOS_UINT8                                               aucReserved[2];
    CNAS_PRL_EXT_SYS_RECORD_STRU                            stSysRecordInfo;
}CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU
 �ṹ˵��  : ����DMT����, �����޸�PRLϵͳ����system record��Ϣ
 1.��    ��   : 2014��12��11��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT16                                              usRecNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_MODIFIED_PRL_SYS_RECORD_INFO_STRU                  astSysRecord[CNAS_XSD_MAX_MODIFIED_PRL_SYS_RECORD_NUM];
}CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU
 �ṹ˵��  : ����DMT����, �����޸�PRLͷ��Ϣ
 1.��    ��   : 2014��12��11��
   ��    ��   : y00245242
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucPreferOnly;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enDefRoamInd;
}CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU
 �ṹ˵��  : ����DMT����, �����޸�PRLͷ��Ϣ
 1.��    ��   : 2014��1��17��
   ��    ��   : c00299063
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* ��ͬ������ǰ�Ƿ������ǰפ��Ƶ�� */
    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;          /*Ƶ���ظ��������� */
    VOS_UINT8                                               aucReserved[2];
}CNAS_XSD_XSD_MODIFY_REPEAT_SCAN_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL
 �ṹ˵��  : ����DMT����, �����޸�PRLͷ��Ϣ
 1.��    ��   : 2014��1��17��
   ��    ��   : c00299063
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucDoTrafficFlag;
    VOS_UINT8                                               aucReserved[3];
    CNAS_XSD_OOC_CONFIG_INFO_STRU                           stOocCfgInfo;
}CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU;
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
    CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_XSD_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_XSD_INTERNAL_MSG_DATA          stMsgData;
}CNAS_XSD_INTERNAL_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XSD_SndPowerOffRslt(
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt,
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason
);

VOS_VOID CNAS_XSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
);

VOS_VOID CNAS_XSD_SndInternalSysAcqReq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_VOID CNAS_XSD_SndSysAcqRslt(
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    VOS_UINT8                                               ucImmediateSysAcq
);

VOS_VOID CNAS_XSD_SndInternalRedirInd(
    CNAS_XSD_REDIRECTION_INFO_STRU                          *pstRedirectionInfo
);

VOS_VOID CNAS_XSD_SndRedirRslt(
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enResult
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

#endif /* end of CnasXsdSndInternalMsg.h */
