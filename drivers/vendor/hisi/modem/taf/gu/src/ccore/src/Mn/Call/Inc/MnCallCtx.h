/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallCtx.h
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��03��03��
  ����޸�   :
  ��������   : MnCallCtx.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _MN_CALL_CTX_H_
#define _MN_CALL_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "MnCallApi.h"
#include  "NasCcAirMsg.h"

#include "NasMncc.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#include "VcCallInterface.h"
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define  MN_CALL_MAX_SS_CMD_KEY_EVT_NUM    (10)                                  /* ����ҵ���������ṹ */

#define  MN_CALL_ENTITY_MAX_NUM            (1)                                  /*CALLģ��֧�ֵ�ʵ������Ŀǰֻ��һ��*/
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */
#define  MN_CALL_INVALID_CATEGORY          (128)                                /* �û����ƵĽ���������������� */

#define MN_CALL_ONE_THOUSAND_MILLISECOND                    (1000)              /* 1000MS */



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* ����ҵ��������� */
typedef enum
{
    MN_CALL_SS_SUBSEQ_OP_RPT_SUCC,                                              /* ��Ӧ�ò��ϱ������ɹ� */
    MN_CALL_SS_SUBSEQ_OP_RPT_FAIL,                                              /* ��Ӧ�ò��ϱ�����ʧ�� */
    MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH                                              /* ������һ������ */
} MN_CALL_SS_SUBSEQ_OP_ENUM;

/* ����ҵ��������� */
typedef enum
{
    MN_CALL_CTRL_NULL,                                                          /* ��Ӧ�ò��ϱ������ɹ� */
    MN_CALL_CTRL_PROCEEDING,                                                    /* ��Ӧ�ò��ϱ�����ʧ�� */
    MN_CALL_CTRL_END,                                                           /* ������һ������ */
    MN_CALL_CTRL_MAX
} MN_CALL_CTRL_STATE_ENUM;
typedef TAF_UINT32    MN_CALL_CTRL_STATE_ENUM_U32;

/* ����ҵ���չ�¼� */
typedef enum
{
    MN_CALL_SS_PROG_EVT_REL,                                                    /* �к��б��Ҷ� */
    MN_CALL_SS_PROG_EVT_SETUP_COMPL,                                            /* ���������� */
    MN_CALL_SS_PROG_EVT_HOLD_CNF,                                               /* ���б��ֳɹ� */
    MN_CALL_SS_PROG_EVT_HOLD_REJ,                                               /* ���б��ֱ��ܾ� */
    MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,                                           /* ���лָ��ɹ� */
    MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,                                           /* ���лָ����ܾ� */
    MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,                                         /* ����MPTY�ɹ� */
    MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,                                         /* ����MPTY���ܾ� */
    MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,                                         /* ����MPTY�ɹ� */
    MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,                                         /* ����MPTY���ܾ� */
    MN_CALL_SS_PROG_EVT_DEFLECT_CNF,                                            /* ����ƫת�ɹ� */
    MN_CALL_SS_PROG_EVT_DEFLECT_REJ,                                            /* ����ƫת���ܾ� */
    MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,                                           /* ����CCBS�ɹ� */
    MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,                                           /* ����CCBS���ܾ� */
    MN_CALL_SS_PROG_EVT_ECT_CNF,                                                /* ECT�����ɹ� */
    MN_CALL_SS_PROG_EVT_ECT_REJ,                                                /* ECT�������ܾ� */
    MN_CALL_SS_PROG_EVT_MAX
} MN_CALL_SS_PROGRESS_EVT_ENUM;

/*****************************************************************************
 ö����    : MN_CALL_SRVCC_STATE_ENUM_UINT8
 ö��˵��  : SRVCC״̬
 1.��    ��   : 2013��12��25��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum MN_CALL_SRVCC_STATE_ENUM
{
    MN_CALL_SRVCC_STATE_START,
    MN_CALL_SRVCC_STATE_SUCCESS,
    MN_CALL_SRVCC_STATE_FAIL,

    MN_CALL_SRVCC_STATE_BUTT
};
typedef VOS_UINT8 MN_CALL_SRVCC_STATE_ENUM_UINT8;

/* Modified by z00234330 for PCLINT����, 2014-07-03, begin */
/* VP���ܵ�NV����״̬ */
enum MN_CALL_VP_NV_CFG_STATE_ENUM
{
    MN_CALL_VP_MO_MT_BOTH               = 0,                                    /* ������Ƶ����(�������кͱ���) */
    MN_CALL_VP_NONE                     = 1,                                    /* ��ֹ��Ƶ���кͱ��� */
    MN_CALL_VP_MO_ONLY                  = 2,                                    /* ������Ƶ���У���ֹ��Ƶ���� */
    MN_CALL_VP_MT_ONLY                  = 3,                                    /* ��ֹ��Ƶ���У�������Ƶ���� */
    MN_CALL_VP_BUTT
};
typedef VOS_UINT8   MN_CALL_VP_NV_CFG_STATE_ENUM_U8;
/* Modified by z00234330 for PCLINT����, 2014-07-03, end */

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
 �ṹ��    : TAF_CALL_REDIAL_CFG_STRU
 �ṹ˵��  : ��¼�����ؽ�������Ϣ
  1.��    ��   : 2015��8��24��
    ��    ��   : n00355355
    �޸�����   : �½�
  2.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : NAS���������Ż�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallRedialSupportFlg;                 /* ֧�ֺ����ؽ����ܱ�־��VOS_TRUE:֧�֣�VOS_FALSE:��֧��*/

    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulCallRedialPeriod;                     /* �����ؽ����Դ�ʱ�������ؽ����ʱ������λ���� */
    VOS_UINT32                          ulCallRedialInterval;                   /* �����ؽ����Դ�ʱ�������ز������λ���� */
    TAF_CALL_REDIAL_CM_SRV_REJ_CFG_STRU         stCallRedialCmSrvRejCfg;
    TAF_CALL_REDIAL_DISC_CFG_STRU                     stCallRedialDiscCfg;
}TAF_CALL_REDIAL_CFG_STRU;

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
/*****************************************************************************
 �ṹ��    : MN_CALL_REDIAL_CFG_INFO_STRU
 �ṹ˵��  : ��¼�����ز�������Ϣ
 1.��    ��   : 2014��04��03��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
*****************************************************************************/
typedef struct
{
    TAF_CALL_REDIAL_CFG_STRU            stCallRedialCfg;            /* call����������Ϣ */
    MN_CALL_REDIAL_CFG_STRU             stEcallRedialCfg;           /* ecall�����ز�������Ϣ */
}MN_CALL_REDIAL_CFG_INFO_STRU;
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

/*****************************************************************************
 �ṹ��    : MN_CALL_CUSTOM_CFG_INFO_STRU
 �ṹ˵��  : NVIM���е�MS����������Ϣ
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�
 2.��    ��   : 2012��06��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ���Ӷ��ƽ���������
 3.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 4.��    ��   : 2013��12��09��
   ��    ��   : f62575
   �޸�����   : DTS2013120411878���ն˲�֧��VOICE/VIDEO CALL���ظ�RELEASE COMPLETE
��Ϣԭ����ֵ
 5.��    ��   : 2014��04��15��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature����
 6.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /*CCBS(��æ�������)ҵ��*/
    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */
    VOS_UINT8                           ucCallDeflectionSupportFlg;             /*֧�ֺ���ƫתҵ�� */
    VOS_UINT8                           ucAlsSupportFlg;                        /*֧����·�л�ҵ��*/

    VOS_UINT8                           ucReportEccNumFlg;

    VOS_UINT8                           ucVoiceCallNotSupportedCause;
    VOS_UINT8                           ucVideoCallNotSupportedCause;

    /* Modified by z00234330 for PCLINT����, 2014-07-03, begin */
    VOS_UINT8                           ucTafCallStatusControl;
    VOS_UINT8                           ucTafMultiSimCallStatusControl;
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpNvCfgState;  /* NV��ÿ����Ƿ�֧�ֿ��ӵ绰������ */
    /* Modified by z00234330 for PCLINT����, 2014-07-03, end */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           ucAtaReportOkAsyncFlag;


    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    MN_CALL_REDIAL_CFG_INFO_STRU         stCallRedialCfgInfo;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;
}MN_CALL_CUSTOM_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_CALL_APP_CFG_INFO_STRU
 �ṹ˵��  : AP���õ���Ϣ
 1.��    ��   : 2015��08��24��
   ��    ��   : n00269697
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /* ��VOLTE������(NV2340����CCWA����ģʽ��UE����)��Ĭ��֧�ֺ��еȴ� */
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT8                           aucReserve[3];

}TAF_CALL_APP_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_MS_CFG_INFO_STRU
 �ṹ˵��  : MS֧�ֵ�MS��������
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        stCustomCfg;                            /* NVIM�еĶ�����Ϣ */
    TAF_CALL_APP_CFG_INFO_STRU          stAppCfg;                                /* AP���õ���Ϣ */
}MN_CALL_MS_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_MGMT_STRU
 �ṹ˵��  : ���й���ṹ
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�
 2.��    ��   : 2012��09��20��
   ��    ��   : f62575
   �޸�����   : STK&DCM ��Ŀ, ɾ��enCallCtrlState�� dataCfg
 3.��    ��   : 2012��10��11��
   ��    ��   : h44270
   �޸�����   : STK&DCM ��Ŀ, ����ulDtmfInProc������Ƿ����DTMF����
 4.��    ��   : 2013��07��11��
   ��    ��   : l00198894
   �޸�����   : V9R1 STK������Ŀ
****************************************************************************/
typedef struct
{
    VOS_BOOL                            bUsed;                                  /* �Ƿ��ѱ�ʹ�� */
    VOS_UINT32                          ulTi;                                   /* �ú��ж�Ӧ��CCʵ���Ti */
    MN_CALL_CLIR_CFG_ENUM_U8            enClirCfg;                              /* ���к������Ƶ����� */
    VOS_UINT8                           ucSrvccLocalAlertedFlag;                /* ��alerting״̬SRVCCʱ���Ƿ��Ѿ��������� */
    VOS_UINT8                           aucReserved[2];
    MN_CALL_CUG_CFG_STRU                stCugCfg;                               /* CUG������ */
    VOS_BOOL                            bRbSet;
    VOS_UINT32                          ulRbId;
    VOS_BOOL                            bVpChannelOpenFlg;                      /*��¼��������Ϊ���ӵ绰�����ҵ���ŵ��Ƿ��Ѵ�*/
    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */
    MN_CALL_INFO_STRU                   stCallInfo;                             /* ������Ϣ */
} MN_CALL_MGMT_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU
 �ṹ˵��  : ����ע�Ĳ���ҵ������¼� �ṹ
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�

****************************************************************************/
typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* �����¼��ĺ���ID */
    VOS_UINT8                           aucReserved[3];
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt;                                  /* �¼������� */
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp;                             /* �յ����¼��ĺ������� */
} MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU
 �ṹ˵��  : ����ҵ�����ṹ
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�

****************************************************************************/
typedef struct
{
    VOS_UINT8                               bInProgress;                        /* �Ƿ��в������ڽ��� */
    MN_CALL_SUPS_CMD_ENUM_U8                enCallSupsCmd;                      /* ��ǰ�Ĳ��� */
    MN_CLIENT_ID_T                          clientId;                           /* ���������Client��ID */
    MN_OPERATION_ID_T                       opId;
    VOS_UINT8                               ucNumOfKeyEvt;                      /* ��ע���¼����� */
    VOS_UINT8                               ucInvokeId;
    VOS_UINT8                               aucReserved[1];
    MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU   astKeyEvts[MN_CALL_MAX_SS_CMD_KEY_EVT_NUM];  /* ��ע���¼� */
} MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU;

/*****************************************************************************
 �ṹ��    : MN_CALL_MSG_BUFF_STRU
 �ṹ˵��  : ������ͨ���л��������setup��Ϣ��rel��Ϣ
 1.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : ֧�ֺ����ؽ������ṹ
 2.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : NAS���������Ż�
****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBufferedSetupMsg : 1;
    VOS_UINT32                          bitOpBufferedRejIndMsg : 1;
    VOS_UINT32                          bitOpBufferedRelCnfMsg : 1;
    VOS_UINT32                          bitSpare : 29;
    MNCC_REQ_PRIM_MSG_STRU              stBufferedSetupMsg;
    MNCC_IND_PRIM_MSG_STRU              stBufferedRejIndMsg;
    MNCC_IND_PRIM_MSG_STRU              stBufferedRelCnfMsg;
} MN_CALL_MSG_BUFF_STRU;


/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
/*****************************************************************************
 �ṹ��    : MN_CALL_ECALL_CTX_STRU
 �ṹ˵��  : eCall��ص����������ݽṹ
 1.��    ��   : 2014��04��08��
   ��    ��   : y00245242
   �޸�����   : Ϊecall���Թ�������
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucWaitMtEcallFlag;            /* �ȴ�mt eCall��� */
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8                   enEcallTransStatus;           /* eCall MSD��ǰ����״̬ */
    VOS_UINT8                                               ucInternalHangUpFlag;         /* �ڲ��һ���־ */
    VOS_UINT8                                               aucReserved[1];               /* ����λ */
    VOS_UINT32                                              ulEcallPeriodTimerLen;        /* ��¼eCall periodʣ��ʱ�� */
}MN_CALL_ECALL_CTX_STRU;
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

/*****************************************************************************
 �ṹ��    : MN_CALL_CONTEXT_STRU
 �ṹ˵��  : MN CALL ģ������������
 1.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : �½�
 2.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 3.��    ��   : 2014��04��08��
   ��    ��   : y00245242
   �޸�����   : Ϊecall���Թ����޸�
 4.��    ��   : 2016��03��08��
   ��    ��   : l00356716
   �޸�����   : NAS���������Ż�
*****************************************************************************/
typedef struct
{
    MN_CALL_MGMT_STRU                         stCallMgmtInfo;                   /* ���й�����Ϣ */
    MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU     stSimInfo;                        /*����ע�Ĳ���ҵ������¼�*/
    MN_CALL_MS_CFG_INFO_STRU                  stMsCfgInfo;                      /* MS��������Ϣ */
    MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU        stNetworkInfo;                    /* ����ҵ�����ṹ*/

    MN_CALL_MSG_BUFF_STRU                     stMnCallBufferedMsg;              /* �����ؽ�������Ҫ������ͨ���л��������set up��Ϣ */

    MN_CALL_SRVCC_STATE_ENUM_UINT8            enSrvccState;

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
    MN_CALL_ECALL_CTX_STRU                    stEcallCtx;                       /* ���ӱ���eCall ��������Ϣ */
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
    NAS_CC_CAUSE_VALUE_ENUM_U32         enDiscCause;     /*��������ʱ��¼����disconnect�Ҷϵ�ԭ��ֵ*/
}MN_CALL_CONTEXT_STRU;

/* �����طŵ���ȫ�ֱ���ʹ��*/
typedef struct
{
    MN_CALL_MGMT_STRU                   pc_g_f_astCallMgmtEntities[MN_CALL_MAX_NUM];
    MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU  pc_g_f_stCallSupsCmdMgmt;

    /*CCBS���ܴ�ʱ,������Setup��Ϣ */
    NAS_CC_MSG_SETUP_MO_STRU            pc_g_f_stCcbsSetup;

    MN_CALL_ALS_LINE_NO_ENUM_U8         pc_g_f_enAlsLineNo;
    VOS_UINT8                           pc_g_gucTafCallStatusControl;
    VOS_UINT8                           pc_g_gucTafMultiSimCallStatusControl;
    VOS_UINT8                           pc_g_g_enVpNvCfgState;
} NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST;

typedef struct
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType;
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType;
}MN_CALL_MATCH_MSG_TYPE_STRU;


/*****************************************************************************
 Structure      : NAS_CC_SDT_MSG_ST
 Description    : PC�طŹ��̣�CC��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_CALL_SDT_MSG_ST;

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */


/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCustomCfgInfo
 ��������  : ��ȡCALL�б������Զ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CALL�б������Զ���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��3��
   ��    ��   : s62952
   �޸�����   : �����ɺ���
 2.��    ��   : 2016��3��8��
   ��    ��   : l00356716
   �޸�����   : NAS���������Ż�
*****************************************************************************/
MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID );

VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID);
MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID );
VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID);
VOS_VOID MN_CALL_InitCtx(VOS_VOID);


VOS_UINT32 TAF_CALL_GetCallRedialForDiscSupportFlg(VOS_VOID);

TAF_CALL_CCWA_CTRL_MODE_ENUM_U8 TAF_CALL_GetCcwaCtrlMode(VOS_VOID);
VOS_VOID TAF_CALL_SetCcwaCtrlMode(
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode
);
TAF_CALL_APP_CFG_INFO_STRU* MN_CALL_GetAppCfgInfo(VOS_VOID);
VOS_VOID TAF_CALL_SetCcwaiMode(
    VOS_UINT8                           bCcwaiFlg
);

TAF_CALL_CCWAI_MODE_ENUM_UINT8 TAF_CALL_GetCcwaiMode(VOS_VOID);

VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
);
VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID);

TAF_CALL_REDIAL_CFG_STRU *MN_CALL_GetCallRedialCfg(VOS_VOID);
VOS_VOID TAF_CALL_SetDiscCause(NAS_CC_CAUSE_VALUE_ENUM_U32 enDiscCause);
NAS_CC_CAUSE_VALUE_ENUM_U32 TAF_CALL_GetDiscCause(VOS_VOID);
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState);

MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID);
#endif

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
MN_CALL_REDIAL_CFG_STRU *TAF_CALL_GetEcallRedialCfg(VOS_VOID);
VOS_UINT8 TAF_CALL_GetEcallRedialSupportFlg(VOS_VOID);
VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 TAF_CALL_GetEcallMsdTransStatus(VOS_VOID);
VOS_VOID TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8 enEcallTransStatus);
VOS_UINT8 TAF_CALL_GetWaitingMtEcallFlag(VOS_VOID);
VOS_VOID TAF_CALL_SetWaitingMtEcallFlag(VOS_UINT8 ucWaitMtEcallFlag);
VOS_VOID TAF_CALL_SetInternalHangUpFlag(VOS_UINT8 ucIntHangUpFlag);
VOS_UINT8 TAF_CALL_GetInternalHangUpFlag(VOS_VOID);
VOS_VOID TAF_CALL_ResetEcallPeriodRemainTimerLen(VOS_VOID);
VOS_VOID TAF_CALL_UpdateEcallPeriodRemainTimerLen(VOS_UINT32 ulEcallPeriodTimerLen);
VOS_UINT32 TAF_CALL_GetEcallPeriodRemainTimerLen(VOS_VOID);
#endif

VOS_UINT32 TAF_CALL_GetRedialSupportFlg(VOS_UINT8 ucCallId);
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

/* Modified by z00234330 for PCLINT����, 2014-07-03, begin */

VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
);

VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  );

VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
);

VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  );

VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
);

MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  );



/* Modified by z00234330 for PCLINT����, 2014-07-03, end */

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

#endif /* end of MnCallCtx.h */

