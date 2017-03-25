/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndInternalMsg.h
  �� �� ��   : ����
  ��    ��   : C00299064
  ��������   : 2014��12��2��
  ����޸�   :
  ��������   : CnasHsdSndInternalMsg.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��2��
    ��    ��   : C00299064
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_HSD_SND_INTERNAL_MSG_H__
#define __CNAS_HSD_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CnasHsdCtx.h"
#include "CnasPrlApi.h"
#include "xsd_xreg_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "CnasHsdFsmSysAcq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_HSD_1X_MAX_REDIR_CHAN_NUM                      (16)

/* HSD�ڲ�ϵͳ���������д���Ƶ�������� */
#define CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM       (4)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_HSD_INTERNAL_MSG_TYPE_ENUM
 ö��˵��  : �ڲ���Ϣ��ö�ٶ���
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_HSD_HSD_ABORT_REQ                = 0x0000, /* _H2ASN_MsgChoice CNAS_HSD_HSD_ABORT_REQ_STRU*/
    ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF       = 0x0001, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_BSR_RSLT_CNF             = 0x0002, /* _H2ASN_MsgChoice CNAS_HSD_HSD_BSR_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF       = 0x0003, /* _H2ASN_MsgChoice CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_REDIRECTION_IND          = 0x0004, /* _H2ASN_MsgChoice CNAS_HSD_HSD_REDIRECTION_IND_STRU*/
    ID_CNAS_HSD_HSD_REDIRECTION_RSLT_CNF     = 0x0005, /* _H2ASN_MsgChoice CNAS_HSD_HSD_REDIRECTION_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ      = 0x0006, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU*/
    ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF = 0x0007, /* _H2ASN_MsgChoice CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*/

    ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF      = 0x0008, /* _H2ASN_MsgChoice CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU*/
    ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF       = 0x0009, /* _H2ASN_MsgChoice CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU*/

    ID_CNAS_XSD_HSD_SYS_ACQ_RSLT_IND         = 0x1000,



#ifdef DMT
    ID_CNAS_HSD_HSD_TEST_CFG_REQ,                      /* _H2ASN_MsgChoice CNAS_HSD_HSD_TEST_CFG_REQ_STRU*/
#endif

    ID_CNAS_HSD_HSD_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : CNAS_HSD_BSR_RESULT_ENUM
 ö��˵��  : BSR�������
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_BSR_RESULT_ENUM
{
    CNAS_HSD_BSR_RESULT_SUCCESS         = 0x00000000,
    CNAS_HSD_BSR_RESULT_FAILURE         = 0x00000001,
    CNAS_HSD_BSR_RESULT_ABORTED         = 0x00000002,
    CNAS_HSD_BSR_RESULT_BUTT            = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_BSR_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_HSD_ABORT_TYPE_ENUM
 ö��˵��  : Abort����
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_ABORT_TYPE_ENUM
{
    CNAS_HSD_ABORT_TYPE_IMMEDIATELY     = 0x00000000,
    CNAS_HSD_ABORT_TYPE_DELAY           = 0x00000001,
    CNAS_HSD_ABORT_TYPE_BUTT            = 0x00000002
};
typedef VOS_UINT32 CNAS_HSD_ABORT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_HSD_SWITCH_ON_RESULT_ENUM
 ö��˵��  : �������
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_SWITCH_ON_RESULT_ENUM
{
    CNAS_HSD_SWITCH_ON_RESULT_SUCCESS   = 0x00000000,
    CNAS_HSD_SWITCH_ON_RESULT_FAILURE   = 0x00000001,
    CNAS_HSD_SWITCH_ON_RESULT_ABORTED   = 0x00000002,
    CNAS_HSD_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_SWITCH_ON_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : CNAS_HSD_REDIR_RESULT_ENUM
 ö��˵��  : �ض��������������
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/

enum CNAS_HSD_REDIR_RESULT_ENUM
{
    CNAS_HSD_REDIR_RESULT_SUCCESS       = 0x00000000,
    CNAS_HSD_REDIR_RESULT_FAILURE       = 0x00000001,
    CNAS_HSD_REDIR_RESULT_ABORTED       = 0x00000002,
    CNAS_HSD_REDIR_RESULT_BUTT          = 0x00000003
};
typedef VOS_UINT32 CNAS_HSD_REDIR_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM
 ö��˵��  : ϵͳ������
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�

 2.��    ��   : 2015��08��02��
   ��    ��   : x00306642
   �޸�����   : ��������������ض���Ľ��
*****************************************************************************/
enum CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM
{
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF                    = 0x00000003,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION             = 0x00000004,
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000005
};
typedef VOS_UINT32 CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM
 ö��˵��  : 1Xϵͳ������
 1.��    ��   : 2014��12��2��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM
{
    CNAS_XSD_HSD_SYS_ACQ_RSLT_SUCCESS                 = 0x00000000,
    CNAS_XSD_HSD_SYS_ACQ_RSLT_FAILURE                 = 0x00000001,
    CNAS_XSD_HSD_SYS_ACQ_RSLT_BUTT                    = 0x00000002
};
typedef VOS_UINT32 CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8
 ö��˵��  : ����ʧ��֮����Ϊ����
 1.��    ��   : 2014��12��16��
   ��    ��   : h00300778
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM
{
    CNAS_HSD_SYS_ACQ_FAIL_ACT_WAIT_TIMEOUT = 0,             /* ����ʧ��֮��ȴ���ʱ����ʱ�ٷ������� */
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE= 1,             /* ����ʧ��֮�������ٴη������� */
    CNAS_HSD_SYS_ACQ_FAIL_ACT_BUTT
};

typedef VOS_UINT8 CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8;

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
 �ṹ��    : CNAS_HSD_HSD_ABORT_REQ_STRU
 �ṹ˵��  : HSD������ֹ״̬����Ϣ�Ľṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : C00299064
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;    /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_ABORT_TYPE_ENUM_UINT32                         enAbortType;
}CNAS_HSD_HSD_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU
 �ṹ˵��  : HSD���Ϳ���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��12��10��
   ��    ��   : h00300778
   �޸�����   : HSD�������CNF��Ϣ�Ľṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_BSR_RSLT_CNF_STRU
 �ṹ˵��  : HSD����BSR���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : C00299064
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_BSR_RESULT_ENUM_UINT32                         enRslt;
}CNAS_HSD_HSD_BSR_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU
 �ṹ˵��  : HSD���͹ػ�ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : C00299064
   �޸�����   : ��ֹ״̬����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU
 �ṹ˵��  : HSDϵͳ��ȡ�ڲ���Ϣ�ṹ
 1.��    ��   : 2014��8��7��
   ��    ��   : g00256031
   �޸�����   : ϵͳ��ȡ�ڲ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
    VOS_UINT32                                              ulFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM];
}CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU
 �ṹ˵��  : HSDϵͳ��ȡ���ȷ����Ϣ�ṹ
 1.��    ��   : 2014��7��15��
   ��    ��   : C00299064
   �޸�����   : ״̬�����ȷ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq;
    VOS_UINT8                                               aucRsved[3];
}CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XSD_HSD_SYS_ACQ_RSLT_IND_STRU
 �ṹ˵��  : HSD���XSD���������
 1.��    ��   : 2014��7��15��
   ��    ��   : C00299064
   �޸�����   : ״̬�����ȷ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_XSD_HSD_SYS_ACQ_RSLT_ENUM_UINT32                   enRlst;
    CNAS_PRL_1X_SYSTEM_STRU                                 st1xSys;
}CNAS_XSD_HSD_SYS_ACQ_RSLT_IND_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU
 �ṹ˵��  : HSD����POWER_SAVEȷ����Ϣ�ṹ
 1.��    ��   : 2015��04��03��
   ��    ��   : z00316370
   �޸�����   : ״̬�����ȷ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU
 �ṹ˵��  : HSD����INTER_SYSȷ����Ϣ�ṹ
 1.��    ��   : 2015��06��03��
   ��    ��   : z00316370
   �޸�����   : ״̬�����ȷ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode;
    VOS_UINT8                                               ucRslt;
    VOS_UINT8                                               aucRsved[1];
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason;
}CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU;




#ifdef DMT
/*****************************************************************************
 �ṹ��    : CNAS_HSD_HSD_TEST_CFG_REQ_STRU
 �ṹ˵��  : ����DMT�������ã�������صĲ�����Ϣ
 1.��    ��   : 2015��01��29��
   ��    ��   : x00306642
   �޸�����   : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulCurSlice;
}CNAS_HSD_HSD_TEST_CFG_REQ_STRU;
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
    CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_HSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_HSD_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_HSD_INTERNAL_MSG_DATA          stMsgData;
}CNAS_HSD_INTERNAL_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_HSD_SndPowerOffRslt(VOS_VOID);

VOS_VOID CNAS_HSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
);

VOS_VOID CNAS_HSD_SndInternalSysAcqReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_VOID CNAS_HSD_SndSysAcqRslt(
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq
);

extern VOS_VOID CNAS_HSD_SndPowerSaveRslt(VOS_VOID);

extern VOS_VOID CNAS_HSD_SndInterSysRslt(
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode,
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
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

#endif /* end of CnasHsdSndInternalMsg.h */
