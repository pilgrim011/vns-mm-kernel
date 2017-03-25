/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccCtx.h
  �� �� ��   : ����
  ��    ��   : Y00213812
  ��������   : 2014��7��4��
  ����޸�   :
  ��������   : CnasXccCtx.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��4��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XCC_CTX_H__
#define __CNAS_XCC_CTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "xcc_xcall_pif.h"
#include "CnasXccComFunc.h"





#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ״̬��ʵ��������: voice call, sms, ps call , agps */
#define CNAS_XCC_MAX_FSM_ENTITY_NUM                         (4)

/* ״̬��ջ����� */
#define CNAS_XCC_MAX_FSM_STACK_DEPTH                        (4)

/* ������Ϣ����󳤶� */
#define CNAS_XCC_MAX_MSG_BUFFER_LEN                         (1600)

/* �����ڲ���Ϣ���е������� */
#define CNAS_XCC_MAX_INT_MSG_QUEUE_NUM                      (8)

/* �����û�������Ϣ��Ŀ */
#define CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM                   (5)

/* QOS��󳤶ȣ�������CAS_CNAS_1X_QOS_MAX_LENGTH����һ�� */
#define CNAS_XCC_MAX_QOS_LENGTH                             (31)

#define CNAS_XCC_INVAILD_CON_ID                             (0xFF)

#define CNAS_XCC_INVAILD_CALL_ID                            (0)

#define CNAS_XCC_INVALID_CON_REF                            (0)

#define CNAS_XCC_MAX_UINT8                                  (255)

#define CNAS_XCC_OCTET_BIT_LEN                              (8)

/* If the service instance does not provide a service reference
identifier, the mobile station shall set this field to the
smallest unused service reference identifier value between 1
and 6 (inclusive). �������Э�飬�ݶ�SR_ID��������Ӧ����6 */
#define CNAS_XCC_MAX_SRID_NUM                               (6)

#define CNAS_XCC_INVALID_SR_ID                              (0)

/* ��ǰ������SR_ID����� */
#define CNAS_XCC_RESERVED_SR_ID                             (1)

#define CNAS_XCC_MS_ACK_PARA_LEN                            (2)

#define CNAS_XCC_INVAILD_CALL_INDEX                         (0xFF)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_XCC_FSM_ID_ENUM
 ö��˵��  : ״̬��IDö�ٶ���
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_XCC_FSM_ID_ENUM
{
    /***********************************************************************
     * XCC L1״̬����ʶ
     ***********************************************************************/
    /* CNAS XCC L1 main״̬���ı�ʶ */
    CNAS_XCC_FSM_L1_MAIN                                    =0x00,

    /***********************************************************************
     * XCC L2״̬���ı�ʶ
     ***********************************************************************/
    /* XCC����L2״̬�� */
    CNAS_XCC_FSM_MO_CALLING                                 =0x01,

    /* XCC����L2״̬�� */
    CNAS_XCC_FSM_MT_CALLING                                 =0x02,


    CNAS_XCC_FSM_BUTT

};
typedef VOS_UINT32 CNAS_XCC_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : CNAS_XCC_TX_ORDER_TYPE_ENUM
 ö��˵��  : ORDER��Ϣ����
 1.��    ��   : 2014��9��15��
   ��    ��   : h00246512
   �޸�����   : ����
*****************************************************************************/
enum CNAS_XCC_TX_ORDER_TYPE_ENUM
{
    CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,                       /* Connect Order */
    CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_START_ORDER,    /* Continuous DTMF Tone Start Order  */
    CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_STOP_ORDER,     /* Continuous DTMF Tone Stop Order */
    CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,                     /* Mobile Station Reject Order */
    CNAS_XCC_TX_ORDER_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_XCC_INIT_TYPE_ENUM
 ö��˵��  : ��ʼ������
 1.��    ��   : 2014��9��15��
   ��    ��   : y00245242
   �޸�����   : ����
*****************************************************************************/
enum CNAS_XCC_INIT_TYPE_ENUM
{
    CNAS_XCC_INIT_TYPE_POWER_ON,                                /* ��ʼ������Ϊ���� */
    CNAS_XCC_INIT_TYPE_POWER_DOWN,                              /* ��ʼ������Ϊ�ػ�  */
    CNAS_XCC_INIT_TYPE_POWER_SAVE,                              /* ��ʼ������Ϊ����  */

    CNAS_XCC_INIT_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XCC_INIT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_XCC_INIT_CALLINFO_SCENE_ENUM
 ö��˵��  : ��ʼ������
 1.��    ��   : 2014��9��20��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
enum CNAS_XCC_INIT_CALLINFO_SCENE_ENUM
{
    CNAS_XCC_INIT_CALLINFO_SCENE_POWER_ON,                      /* ��ʼ������Ϊ���� */
    CNAS_XCC_INIT_CALLINFO_SCENE_ENDING,                        /* ��ʼ������ΪL1 MAIN״̬Ǩ�Ƶ�ENDING  */
    CNAS_XCC_INIT_CALLINFO_SCENE_ENDED,                         /* ��ʼ������ΪL1 MAIN״̬Ǩ�Ƶ�IDLE  */

    CNAS_XCC_INIT_CALLINFO_SCENE_BUTT
};
typedef VOS_UINT8  CNAS_XCC_INIT_CALLINFO_SCENE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM
 �ṹ˵��  : ���ڱ�Ƕ�ȡ���ļ��Ļظ���Ϣ
 1.��    ��   : 2014��9��19��
   ��    ��   : h00246512
   �޸�����   : ����

*****************************************************************************/
enum   CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM
{
    CNAS_XCC_SERVICE_SUSPEND_FLG_NULL                       = 0x00,

    CNAS_XCC_SERVICE_SUSPEND_FLG_XCALL                      = 0x01,

    CNAS_XCC_SERVICE_SUSPEND_FLG_SMS                        = 0x02,

    CNAS_XCC_SERVICE_SUSPEND_FLG_BUTT
};

typedef VOS_UINT8 CNAS_XCC_SERVICE_SUSPEND_FLG_ENUM_UINT8;

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
 �ṹ��    : CNAS_XCC_ENTRY_MSG_STRU
 �ṹ˵��  : XCC��Ϣ�ṹ��״̬������������Ϣ��CACHE��Ϣ��ʹ�ô˽ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[CNAS_XCC_MAX_MSG_BUFFER_LEN];
}CNAS_XCC_ENTRY_MSG_STRU;

/*****************************************************************************
�ṹ��    : CNAS_XCC_BUFFER_MSG_QUEUE_STRU
�ṹ˵��  : �������Ϣ���У�
1.��    ��   : 2014��09��15��
  ��    ��   : y00245242
  �޸�����   : �½�
2.��    ��   : 2015��09��08��
  ��    ��   : w00176964
  �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsgNum;                                /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastBufferMsg[CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM]; /* �����û���������Ϣ������ҵ�����ͻ��� */
}CNAS_XCC_BUFFER_MSG_QUEUE_STRU;

 /*****************************************************************************
 �ṹ��    : CNAS_XCC_INT_MSG_QUEUE_STRU
 �ṹ˵��  : �������Ϣ����
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_XCC_MAX_INT_MSG_QUEUE_NUM]; /* XCC����Ϣ�������飬�����Ϣָ�� */
}CNAS_XCC_INT_MSG_QUEUE_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_MO_CALLING_CTX_STRU
 �ṹ˵��  : ���MO CALLING״̬������������Ϣ
  1.��    ��   : 2014��11��19��
    ��    ��   : w00176964
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_MO_CALLING_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_MT_CALLING_CTX_STRU
 �ṹ˵��  : ���MT CALLING״̬������������Ϣ
  1.��    ��   : 2014��11��19��
    ��    ��   : w00176964
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_MT_CALLING_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_L1_MAIN_CTX_STRU
 �ṹ˵��  : ���L1 MAIN״̬������������Ϣ
  1.��    ��   : 2014��11��19��
    ��    ��   : w00176964
    �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];
}CNAS_XCC_FSM_L1_MAIN_CTX_STRU;



/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_EXTRA_CTX_UNION
 �ṹ˵��  : ״̬��״̬�����ṹ,״̬����������Ϣ
 1.��    ��   : 2014��11��19��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef union
{
    CNAS_XCC_FSM_MO_CALLING_CTX_STRU    stMoCallingCtx;
    CNAS_XCC_FSM_MT_CALLING_CTX_STRU    stMtCallingCtx;
    CNAS_XCC_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;
}CNAS_XCC_FSM_EXTRA_CTX_UNION;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�

 2.��    ��   : 2014��11��19��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X��Ŀ����5�޸�:����״̬�������Ľṹ��

*****************************************************************************/
typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId;

    /* �ϲ�״̬����ʶ */
    CNAS_XCC_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* �ϲ�״̬�������Ϣ���� */
    VOS_UINT32                          ulParentEventType;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;

    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           ucReserved[3];

    /* �����ϢMSGID������  */
    CNAS_XCC_ENTRY_MSG_STRU             stEntryMsg;

    /* ״̬������ */
    CNAS_XCC_FSM_EXTRA_CTX_UNION        unFsmCtx;
}CNAS_XCC_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_STACK_STRU
 �ṹ˵��  : ״̬��ջ�����ṹ
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */
    VOS_UINT8                           aucReserved[2];
    CNAS_XCC_FSM_CTX_STRU               astFsmStack[CNAS_XCC_MAX_FSM_STACK_DEPTH];  /* ״̬��ջ����� */
}CNAS_XCC_FSM_STACK_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU
 �ṹ˵��  : ��WFO״̬�յ�AWI/EAWI����Ҫ�����������Info record
 1.��    ��   : 2014��11��12��
   ��    ��   : L00256032
   �޸�����   : 1X SS Project�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucIsBufferValid;            /* �����Ƿ���Ч:VOS_TRUE:��Ч; VOS_FALSE:��Ч */
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8  enMsgType;                  /* ��¼��Ϣ����ΪAWI��EAWI */
    VOS_UINT8                               aucReserve[2];
    union
    {
        CNAS_XCC_AWIM_STRU                  stAWIM;
        CNAS_XCC_EAWIM_STRU                 stEAWIM;
    }u;
}CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_EMERGENCY_CALL_CTRL_STRU
 �ṹ˵��  : emgency call ctrl info
 1.��    ��   : 2014��11��25��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWaitFlashMsgRspFlg;                 /* wait emgency call flash msg response flag */
    VOS_UINT8                           ucEmcCallId;                          /* related emgency call ID */
    VOS_UINT8                           ucMtVoiceCallId;                      /* current MT voice call ID */
    VOS_UINT8                           ucFlashMsgSeqNum;                     /* allocated sequence number while sending emgency call FWI/EFWI msg */
}CNAS_XCC_EMERGENCY_CALL_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU
 �ṹ˵��  : Prev hrpd net info
 1.��    ��   : 2015��7��9��
   ��    ��   : g00261581
   �޸�����   : CDMA DTS2015041700164
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPzid;
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT8                           aucReserved[2];
} CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_CALL_INFO_CTX_STRU
 �ṹ˵��  : ������Ϣ������
 1.��    ��   : 2014��09��09��
   ��    ��   : h00246512
   �޸�����   : �½�
 2.��    ��   : 2014��11��19��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X��Ŀ����5�޸�
 3.��    ��   : 2015��1��3��
   ��    ��   : y00245242
   �޸�����   : NDSS ORIG���ܿ���
 4.��    ��   : 2015��7��27��
   ��    ��   : l00324781
   �޸�����   : Iter16�޸�:ɾ������Ԫ�أ�����ucContDtmfSeqNum��ucIsContDtmfAckWait
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      bitOpCallingPartyNum:1;
    VOS_UINT32                                      bitOpCallingPartySubAddr:1;
    VOS_UINT32                                      bitOpCalledPartySubAddr:1;
    VOS_UINT32                                      bitOpQosInfo:1;
    VOS_UINT32                                      bitOpSpare:28;

    VOS_UINT8                                       ucIsEntityActive;           /* ��ǰ����ʵ���Ƿ񼤻� */
    VOS_UINT8                                       ucConnectId;                /* ����ID��XCC��ʵ����� */
    VOS_UINT8                                       ucCallId;                   /* ����ID��XCALL�õ� */
    VOS_UINT8                                       ucIsDataReady;

    VOS_UINT8                                       ucConRef;                   /* Con_Ref���������ģ��������ֺ���ʵ����һ�ֱ�־ */
    VOS_UINT8                                       ucIsMoCall;                 /* ��ǰ�Ƿ������� */
    VOS_UINT8                                       ucIsNullCc;                 /* �Ƿ���NULL��ʶ�������֪ͨ */
    VOS_UINT8                                       ucIsByPassAlertAns;         /* bypass��־�������֪ͨ������ָ���Ƿ�ֱ�ӽ���ͨ�� */

    /* ɾ��ucIsStartDtmfAckWait,ucIsStopDtmfAckWait������Ԫ�� */
    VOS_UINT8                                       ucIsBurstDtmfAckWait;
    VOS_UINT8                                       ucBurstDtmfSeqNum;
    VOS_UINT8                                       ucIsSendFlashAckWait;
    VOS_UINT8                                       ucSendFlashSeqNum;

    VOS_UINT8                                       ucIsCodecOpen;              /* �������Ƿ��Ѿ��� */
    VOS_UINT8                                       ucIsSoNegCmplt;             /* SOЭ���Ƿ���� */
    VOS_UINT8                                       ucMsgSeqNum;                /* �������ݵ����кţ�����ȷ��L2 ack */
    VOS_UINT8                                       ucContDtmfSeqNum;

    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16          enInitSo;                   /* ҵ���ʼ��ʼ��SO */
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16          enCurrentSo;                /* ҵ������У�so���ܷ����仯����¼��ǰ��SO */

    VOS_UINT8                                       ucQosInfoLen;               /* Qos�����ݺ�����Ҫ */
    VOS_UINT8                                       aucQosInfo[CNAS_XCC_MAX_QOS_LENGTH];

    CAS_CNAS_1X_ORIG_NUM_INFO_STRU                  stCalledPartyNum;           /* ���к��� */
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU           stCallingPartyNum;          /* ���к��� */
    XCC_XCALL_SUB_ADDRESS_INFO_STRU                 stCallingPartySubAddr;      /* �����ӵ�ַ */
    XCC_XCALL_SUB_ADDRESS_INFO_STRU                 stCalledPartySubAddr;       /* �����ӵ�ַ */

    VOS_UINT8                                       ucReOrigCount;              /* �ز����� */
    VOS_UINT8                                       ucIsL2ErrReOrig;            /* �Ƿ��ǲ���쳣���µ��ز� */
    VOS_UINT8                                       ucIsEmergencyCall;          /* ��ǰ�Ƿ��ǽ����� */

    VOS_UINT8                                       ucIsReOrigReason;
    VOS_UINT8                                       ucIsDormDataCall;           /* ��DORMANT״̬�����ORIG���� */
    VOS_UINT8                                       ucIsDataSrvConn;            /* ��¼��ǰ�Ƿ��Ѿ�����ҵ������ӽ��� */
    VOS_UINT8                                       ucSrId;                     /* ��¼��ǰʹ�õ�SR_ID */
    VOS_UINT8                                       ucIsContDtmfAckWait;        /* ��CAS����Cont DTMF Tone Order,���õĵȴ���־���յ�L2 ACKʱ��� */


    VOS_UINT32                                      ulIsPrevHrpdFlg;
    CNAS_XCC_PREV_HRPD_ACT_DATA_NET_INFO_STRU       stPrevHrpdActNetInfo;

    CNAS_XCC_AWI_EAWI_INFO_RECO_BUFFER_STRU         stAWIorEAWIInfoRecoBuffer;  /* ��WFO״̬�յ�AWI/EAWI�������������Info record */

    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8               enReqPrivacyMode;              /* �����privacy mode */
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8               enNegPrivacyMode;              /* Э�̺��privacy mode */
    VOS_UINT8                                       aucReserved[2];
}CNAS_XCC_CALL_INFO_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_FSM_ENTITY_STRU
 �ṹ˵��  : ״̬��ʵ�������ṹ
 1.��    ��   : 2014��07��09��
   ��    ��   : l60609
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    CNAS_XCC_FSM_CTX_STRU               stCurFsm;                              /* ״̬����ǰ��״̬������ */
    CNAS_XCC_FSM_STACK_STRU             stFsmStack;                            /* ״̬����״̬��ջ����   */

    CNAS_XCC_CALL_INFO_CTX_STRU         stCallInfoCtx;
}CNAS_XCC_FSM_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU
 �ṹ˵��  : ״̬��ʵ�������ṹ
 1.��    ��   : 2015��01��08��
   ��    ��   : y00245242
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallNum;                                  /* ��¼����ĺ�����Ŀ*/
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucCallIndex[CNAS_XCC_MAX_FSM_ENTITY_NUM];  /* ��¼����������˳��������Ϣ�������ȷ���ĺ��д�������0�±꣬
                                                                                       ��ĳ·�����ͷź󣬻��������� */
}CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_MAIN_CTRL_CTX_STRU
 �ṹ˵��  : main control��������Ϣ
 1.��    ��   : 2014��09��10��
   ��    ��   : y00245242
   �޸�����   : �½�
 2.��    ��   : 2014��11��26��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 5 Modified
 3.��    ��   : 2015��1��6��
   ��    ��   : y00245242
   �޸�����   : ����NDSS ORIG����

*****************************************************************************/
typedef struct
{
    CNAS_XCC_BUFFER_MSG_QUEUE_STRU                          stBufferMsgQueue;     /* �����û�������Ϣ */

    VOS_UINT8                                               ucSeqNum;

    VOS_UINT8                                               ucLatestCallIndex;    /* ��¼���һ·�������� */
    VOS_UINT8                                               aucReserve[2];

    CNAS_XCC_EMERGENCY_CALL_CTRL_STRU                       stEmcCallCtrl;      /* emgency call ctrl info */
}CNAS_XCC_MAIN_CTRL_CTX_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_SRID_INFO_STRU
 �ṹ˵��  : SR_ID����������Ϣ
 1.��    ��   : 2015��1��4��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsUsed;
    VOS_UINT8                                               ucSrid;
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  enSo;
    VOS_UINT8                                               ucConnectId;
    VOS_UINT8                                               aucReserved[3];
}CNAS_XCC_SRID_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_CALL_NVIM_CFG_STRU
 �ṹ˵��  : ����nv����
 1.��    ��   : 2015��6��15��
   ��    ��   : c00299063
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               ucPrivacyMode;      /* privacy mode flag: 0 - disable 1 - enable */

    VOS_UINT8                                               aucReserved[14];

    VOS_UINT8                                               ucEccSrvCap;        /* ECC��������: TRUE -- ֧��ECC����FALSE -- ��֧��ECC���� */
    VOS_UINT8                                               ucEccSrvStatus;     /* ECC����״̬: TRUE -- ECC����򿪣�FALSE -- ECC����ر� */

    VOS_UINT8                                               aucReserved1[2];
}CNAS_XCC_CALL_NVIM_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU
 �ṹ˵��  : 1x paging rsp�д�soֵ�Ŀ���
 1.��    ��   : 2015��11��02��
   ��    ��   : L00301449
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNoDataSrvRspSo33Flg;                  /* û������ҵ��ʱ��Paging rsp�Ļظ���0 - Paging Rsp��SO��0�� 1 - Paging Rsp��SO��33 */
    VOS_UINT8                           aucReserved[3];
}CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_XCC_CTX_STRU
 �ṹ˵��  : CNAS XCC ģ������������
 1.��    ��   : 2014��07��04��
   ��    ��   : Y00213812
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        CNAS XCC״̬��ʵ��
    **************************************************************************/
    CNAS_XCC_FSM_ENTITY_STRU                                astFsmEntity[CNAS_XCC_MAX_FSM_ENTITY_NUM];
    CNAS_XCC_FSM_ENTITY_STRU                               *pstCurFsmEntity;      /* ��ǰ��Ҫ�����״̬ */

    /* CNAS XCC�ڲ���Ϣ���� */
    CNAS_XCC_INT_MSG_QUEUE_STRU                             stIntMsgQueue;

    CNAS_XCC_MAIN_CTRL_CTX_STRU                             stMainCtrlCtx;

    CNAS_XCC_SRID_INFO_STRU                                 astSridInfo[CNAS_XCC_MAX_SRID_NUM + 1];

    CNAS_XCC_RECORD_ORIG_CALL_INDEX_ORDER_STRU              stOrigCallIndexOrder;   /* �������˳������ */

    CNAS_XCC_CALL_NVIM_CFG_STRU                             stCallNvimCfg;

    CNAS_XCC_1X_PAGING_RSP_SO_CFG_STRU                      stPagingRspSoCfg;
}CNAS_XCC_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

CNAS_XCC_CTX_STRU* CNAS_XCC_GetCtxAddr(VOS_VOID);

CNAS_XCC_FSM_STACK_STRU* CNAS_XCC_GetFsmStackAddr(VOS_VOID);

CNAS_XCC_FSM_CTX_STRU* CNAS_XCC_GetCurFsmAddr(VOS_VOID);

VOS_VOID CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_ENUM_UINT8 enInitType);

VOS_VOID CNAS_XCC_PushFsm(
    CNAS_XCC_FSM_STACK_STRU             *pstFsmStack,
    CNAS_XCC_FSM_CTX_STRU               *pstNewFsm
);

VOS_UINT16 CNAS_XCC_GetFsmStackDepth(VOS_VOID);


VOS_VOID CNAS_XCC_InitFsmL2(
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId
);

VOS_VOID CNAS_XCC_QuitFsmL2(VOS_VOID);

VOS_VOID CNAS_XCC_PopFsm(VOS_VOID);

VOS_UINT16 CNAS_XCC_GetFsmStackPopFlg(VOS_VOID);

VOS_UINT8 CNAS_XCC_GetBufferedMsgNum(VOS_VOID);

/* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-8, begin */
VOS_UINT8 *CNAS_XCC_GetNextBufferMsg(VOS_VOID);
/* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-8, end */

VOS_VOID CNAS_XCC_FreeCurrentBufferMsg(VOS_VOID);

/* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-8, begin */
VOS_UINT8 *CNAS_XCC_GetSpecifiedIndexBufferMsg(
    VOS_UINT8                           ucIndex
);
/* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-8, end */

VOS_VOID CNAS_XCC_FreeSpecifiedIndexBufferMsg(VOS_UINT8 ucIndex);

VOS_VOID CNAS_XCC_FreeAllBufferMsgInQueue(VOS_VOID);

VOS_VOID CNAS_XCC_BufferMsgInQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *CNAS_XCC_GetNextIntMsg(VOS_VOID);

VOS_UINT32 CNAS_XCC_GetIntMsgNum(VOS_VOID);

CNAS_XCC_INT_MSG_QUEUE_STRU* CNAS_XCC_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID CNAS_XCC_InitFsmCtx_L1Main(VOS_VOID);

CNAS_XCC_FSM_ID_ENUM_UINT32 CNAS_XCC_GetCurrFsmId(VOS_VOID);

NAS_FSM_DESC_STRU* CNAS_XCC_GetCurFsmDesc(VOS_VOID);

VOS_VOID  CNAS_XCC_InitCurrFsmCtx(
    CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
    CNAS_XCC_FSM_CTX_STRU              *pstCurrFsmCtx
)
;

VOS_VOID  CNAS_XCC_InitFsmStackCtx(
    CNAS_XCC_FSM_STACK_STRU            *pstFsmStack
);

VOS_VOID  CNAS_XCC_InitInternalBuffer(
    CNAS_XCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_UINT32 CNAS_XCC_GetFsmTopState(VOS_VOID);

CNAS_XCC_MAIN_CTRL_CTX_STRU* CNAS_XCC_GetMainCtrlCtx(VOS_VOID);

VOS_VOID  CNAS_XCC_LoadSubFsm(
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XCC_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID CNAS_XCC_InitFsmCtx_MoCalling(VOS_VOID);

VOS_VOID CNAS_XCC_InitFsmCtx_MtCalling(VOS_VOID);

VOS_VOID  CNAS_XCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

CNAS_XCC_CALL_INFO_CTX_STRU*  CNAS_XCC_GetCurrFsmEntityCallInfoCtx( VOS_VOID );

VOS_VOID  CNAS_XCC_InitCallInfoCtx(
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo,
    CNAS_XCC_INIT_CALLINFO_SCENE_ENUM_UINT8                 enScene
);

CNAS_XCC_ENTRY_MSG_STRU* CNAS_XCC_GetCurrFsmMsgAddr(VOS_VOID);

CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetInitSo(VOS_VOID);

VOS_VOID CNAS_XCC_SetInitSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo);

CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 CNAS_XCC_GetCurrentSo(VOS_VOID);

VOS_VOID CNAS_XCC_SetCurrentSo(CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16 enSo);

VOS_VOID CNAS_XCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 CNAS_XCC_AllocSeqNum(VOS_VOID);

VOS_VOID CNAS_XCC_InitMainCtrlCtx(
                                  CNAS_XCC_INIT_TYPE_ENUM_UINT8       enInitType,
                                  CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrlCtx
                                  );

VOS_VOID  CNAS_XCC_InitIntMsgQueue(
    CNAS_XCC_INT_MSG_QUEUE_STRU      *pstIntMsgQueue
);

VOS_UINT32 CNAS_XCC_BufferAWIOrEAWIInfoReco(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd,
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
);

VOS_VOID CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer(VOS_VOID);

VOS_VOID CNAS_XCC_SetWaitEmcFlashMsgRspFlg(
    VOS_UINT8                           ucFlg
);
VOS_UINT8 CNAS_XCC_GetWaitEmcFlashMsgRspFlg(VOS_VOID);
VOS_VOID  CNAS_XCC_SaveEmcCallId(
    VOS_UINT8                           ucCallId
);
VOS_UINT8 CNAS_XCC_GetEmcCallId(VOS_VOID);
VOS_VOID  CNAS_XCC_SaveEmcFlashMsgSeqNum(
    VOS_UINT8                           ucSeqNum
);

VOS_UINT8 CNAS_XCC_GetEmcFlashMsgSeqNum(VOS_VOID);

VOS_VOID CNAS_XCC_SaveMtVoiceCallId(
    VOS_UINT8                           ucCallId
);
VOS_UINT8 CNAS_XCC_GetMtVoiceCallId(VOS_VOID);

VOS_VOID CNAS_XCC_InitEmergencyCallCtrlCtx(
    CNAS_XCC_EMERGENCY_CALL_CTRL_STRU  *pstEmcCtrl
);

VOS_UINT32   CNAS_XCC_AllocSrId(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16  enSo,
    VOS_UINT8                              *pucSrId,
    VOS_UINT8                               ucConnectId
);
VOS_UINT32   CNAS_XCC_UpdateSrIdUsed(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16  enSo,
    VOS_UINT8                               ucSrId,
    VOS_UINT8                               ucConnectId
);


VOS_VOID CNAS_XCC_SetOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
);

VOS_VOID CNAS_XCC_ClearSpecificedOrigCallOrderIndex(
    VOS_UINT8                           ucCallIndex
);

VOS_VOID CNAS_XCC_ClearAllOrigCallOrderIndex(VOS_VOID);

VOS_UINT8 CNAS_XCC_GetLastCallIndex(VOS_VOID);
VOS_VOID CNAS_XCC_INIT_SRID_INFO( VOS_VOID );
VOS_VOID CNAS_XCC_ClearSpecificedSrIdByConnectId(
    VOS_UINT8                           ucConnectId
);

VOS_VOID CNAS_XCC_InitCallNvimCfg(
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg
);


VOS_UINT32 CNAS_XCC_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
extern VOS_UINT32 I1_TAF_APS_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);

#if (3 == MULTI_MODEM_NUMBER)
extern VOS_UINT32 I2_TAF_APS_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
);
#endif

#endif

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

#endif /* end of CnasXccCtx.h */

