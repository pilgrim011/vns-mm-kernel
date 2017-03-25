/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsCtx.h
  �� �� ��   : ����
  ��    ��   : h00300778S
  ��������   : 2014��10��31��
  ��������   : TafXsmsCtx.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_CTX_H_
#define _TAF_XSMS_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"

#include "TafXsmsUimProc.h"
#include "TafXsmsDecode.h"
#include "TafXsmsMoFsmMainTbl.h"
#include "TafXsmsMtFsmMainTbl.h"
#include "xcc_sms_pif.h"
#include "TafSdcCtx.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#pragma pack(4)
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if 1
#define TAF_XSMS_INFO_LOG(string)            TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_INFO,   string)
#define TAF_XSMS_NORMAL_LOG(string)          TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_NORMAL, string)
#define TAF_XSMS_WARNING_LOG(string)         TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_WARNING,string)
#define TAF_XSMS_ERROR_LOG(string)           TAF_LOG(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_ERROR,  string)

#define TAF_XSMS_INFO_LOG1(string, para1)    TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_INFO,   string, para1)
#define TAF_XSMS_NORMAL_LOG1(string, para1)  TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_NORMAL, string, para1)
#define TAF_XSMS_WARNING_LOG1(string, para1) TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_WARNING,string, para1)
#define TAF_XSMS_ERROR_LOG1(string, para1)   TAF_LOG1(UEPS_PID_XSMS, 0, PS_LOG_LEVEL_ERROR,  string, para1)
#else
#define TAF_XSMS_INFO_LOG(string)            vos_printf("\r\nXSMS INFO:%s",   string)
#define TAF_XSMS_NORMAL_LOG(string)          vos_printf("\r\nXSMS NORMAL:%s", string)
#define TAF_XSMS_WARNING_LOG(string)         vos_printf("\r\nXSMS WARNING:%s",string)
#define TAF_XSMS_ERROR_LOG(string)           vos_printf("\r\nXSMS ERROR:%s",  string)

#define TAF_XSMS_INFO_LOG1(string, para1)    vos_printf("\r\nXSMS INFO:%s,para1=%d",    string, para1)
#define TAF_XSMS_NORMAL_LOG1(string, para1)  vos_printf("\r\nXSMS NORMAL:%s,para1=%d",  string, para1)
#define TAF_XSMS_WARNING_LOG1(string, para1) vos_printf("\r\nXSMS WARNING:%s,para1=%d", string, para1)
#define TAF_XSMS_ERROR_LOG1(string, para1)   vos_printf("\r\nXSMS ERROR:%s,para1=%d",   string, para1)
#endif

#define TAF_XSMS_BEAER_SEQ_NUM_MAX          (64)
#define TAF_XSMS_MILLISECS_IN_SECOND        (1000)
#define TAF_XSMS_HUNDRED_MILLISECS          (100)

#define TAF_XSMS_GET_MCC(NUM)             (100 * ((NUM  % 1000 / 100 + 1) % 10) \
                                        + 10* ((NUM % 100 / 10 + 1) % 10) \
                                        + (NUM % 10 + 1) % 10)


#define TAF_XSMS_POOL_REC_MAX_TIME          (6) /* 10 * 6 = 60S */
#define TAF_XSMS_MAX_REC_IN_POOL            (5)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum TAF_XSMS_ACTIVE_CHANNEL_ENUM
{
    TAF_XSMS_ACTIVE_DSCH   = 0x01,
    TAF_XSMS_ACTIVE_CSCH   = 0x02,

    TAF_XSMS_ACTIVE_CH_BUTT
};
typedef VOS_UINT8 TAF_XSMS_ACTIVE_CHANNEL_ENUM8;

enum TAF_XSMS_SMS_ORIGPID_ENUM
{
    TAF_XSMS_SMS_ORIGPID_AT    = 0x7F01,
    TAF_XSMS_SMS_ORIGPID_STK   = 0x7F02,
    TAF_XSMS_SMS_ORIGPID_XPDS  = 0x7F03,
    TAF_XSMS_SMS_ORIGPID_XCALL = 0x7F04,

    TAF_XSMS_SMS_ORIGPID_BUTT
};
typedef VOS_UINT16 TAF_XSMS_SMS_ORIGPID_ENUM_UINT16;


enum TAF_XSMS_CCF_AP_MEM_FULL_ENUM
{
    TAF_XSMS_CCF_AP_MEM_FULL        = 0xAA,
    TAF_XSMS_CCF_AP_MEM_NOT_FULL    = 0x55,

    TAF_XSMS_CCF_AP_MEM_FULL_BUTT
};
typedef VOS_UINT8 TAF_XSMS_CCF_AP_MEM_FULL_ENUM8;


/*****************************************************************************
 �ṹ��    : TAF_XSMS_MT_FSM_ID_ENUM
 �ṹ˵��  :
 1.��    ��   : 2014��11��1��
   ��    ��   : l00208516
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XSMS_MT_FSM_ID_ENUM
{
    TAF_XSMS_MT_IDLE_STATE                     = 0,
    TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE    = 1,
    TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE     = 2,
    TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE       = 3,
    TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE    = 4,
    TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE    = 5,
    TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE     = 6,
    TAF_XSMS_MT_WAITING_AS_CNF_STATE           = 7,
    TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE   = 8,

    TAF_XSMS_MT_STATE_BUTT

};
typedef VOS_UINT32 TAF_XSMS_MT_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_MO_FSM_ID_ENUM
 �ṹ˵��  :
 1.��    ��   : 2014��11��1��
   ��    ��   : l00208516
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XSMS_MO_FSM_ID_ENUM
{
    TAF_XSMS_MO_IDLE_STATE                     = 0,
    TAF_XSMS_MO_WAITING_FDN_CNF                = 1,
    TAF_XSMS_MO_WAITING_CC_CNF                 = 2,
    TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF      = 3,
    TAF_XSMS_MO_WAITING_XCC_SO_IND             = 4,
    TAF_XSMS_MO_WAITING_AS_CNF                 = 5,
    TAF_XSMS_MO_WAITING_TL_ACK                 = 6,
    TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF       = 7,
    TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND      = 8,

    TAF_XSMS_MO_STATE_BUTT
};
typedef VOS_UINT32 TAF_XSMS_MO_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_BD_SMS_PRIO_ENUM
 �ṹ˵��  :
 1.��    ��   :
   ��    ��   :
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XSMS_BD_SMS_PRIO_ENUM
{
    TAF_XSMS_BD_SMS_PRIO_NORMAL         = 0,
    TAF_XSMS_BD_SMS_PRIO_INTERACTIVE    = 1,
    TAF_XSMS_BD_SMS_PRIO_URGENT         = 2,
    TAF_XSMS_BD_SMS_PRIO_EMERGENCY      = 3,


    TAF_XSMS_BD_SMS_PRIO_BUTT
};
typedef VOS_UINT8 TAF_XSMS_BD_SMS_PRIO_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern TAF_XSMS_INIT_CTRL_INFO_STRU     g_stTafXsmsInitCtrlInfo;
extern TAF_XSMS_CTRL_INFO_STRU          g_stTafXsmsReqCtrlInfo;


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
 �ṹ��    : TAF_XSMS_MSG_MO_REC_STRU
 �ṹ˵��  : MO���ż�¼�ṹ
 1.��    ��   : 2014��11��3��
   ��    ��   : l00208516
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* NV��Ľṹ�� */
    TAF_NVIM_1X_XSMS_CFG_STRU           stNvResend;
    /* reply_seq */
    VOS_UINT8                           ucReplySeq;
    VOS_UINT8                           ucIsRcvSmsWhenSndSms;  /* VOS_TRUE : �ڷ��Ͷ��ŵĹ������յ��˶��� VOS_FALSE: û���յ����� */
    VOS_UINT16                          usOpId;
    /* AT�·��Ķ������� */
    TAF_XSMS_MESSAGE_STRU               st1xSms;
    /* ���ɵ�DBM */
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    /* message id */
    VOS_UINT16                          usMessageId;
    /* ��ǰ����ʹ�õ��ŵ� */
    TAF_XSMS_ACTIVE_CHANNEL_ENUM8       enActiveSndChannel;
    /* �ŵ��Ƿ��Ƕ��Ž����� */
    VOS_UINT8                           ucIsSmsOrigChannel;
    /* ʵ�����Դ��� */
    VOS_UINT8                           ucResendTimes;
    /**<  reason of re orig is L2 error */
    VOS_UINT8                           ucIsL2ErrReOrig;
    /**<  coutinous count */
    VOS_UINT8                           ucL2ErrReOrigCount;
    VOS_UINT8                           ucWaitRedirCompleteFlag;
    /* ������Դ��־λ AT SMS*/
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid;
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastErrType;
    VOS_UINT8                           ucIsOrigReqSendFlag;  /* VOS_TRUE: �Ѿ���������VOS_FALSE:û�з��� */
    VOS_UINT16                          usIsTlAckNeed;
    VOS_UINT8                           aucRsv1[2];
    /* �յ�TL_ACK��cause code */
    TAF_XSMS_CAUSE_CODE_STRU            stCauseCode;
}TAF_XSMS_MSG_MO_REC_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XSMS_MSG_MT_REC_STRU
 �ṹ˵��  : MT���ż�¼�ṹ
 1.��    ��   : 2014��11��3��
   ��    ��   : l00208516
   �޸�����   : �½�

*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_XSMS_MSG_MT_REC_STRU
 �ṹ˵��  : MT���ż�¼�ṹ
 1.��    ��   : 2014��11��3��
   ��    ��   : l00208516
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* ����NV */
    TAF_NVIM_1X_XSMS_CFG_STRU           stResend;
    /*���ԣ�_���ãˡ�*/
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;
    /* ���յĶ���*/
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTLP2PMsg;

    /* ���ɵ�DBM */
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    /* call id*/
    VOS_UINT8                           ucCallId;
    /* ���ն���ʹ�õ��ŵ� */
    TAF_XSMS_ACTIVE_CHANNEL_ENUM8       enActiveRevChannel;
    /* �ŵ��Ƿ��Ƕ��Ž����� */
    VOS_UINT8                           ucIsSmsOrigChannel;
    /* ʵ�����Դ��� */
    VOS_UINT8                           ucReSendTimes;
    VOS_UINT8                           ucIsMtCreatLink;    /* FALSE ���Ǳ�����·��TRUE �Ǳ�����· */
    PS_BOOL_ENUM_UINT8                  enIsCasAckFlag;
    VOS_UINT8                           aucCasAckData[2];
    VOS_UINT32                          ulIsTlAckSndToCas;  /* VOS_FALSE: ��û�з���TL_ACK VOS_TRUE:�Ѿ�����TL_ACK�ȴ�CNF�� */
}TAF_XSMS_MSG_MT_REC_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2014��11��1��
   ��    ��   : l00208516
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_STA_STRU                       *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enFsmId;
}TAF_XSMS_MT_FSM_CTX_STRU;

typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_STA_STRU                       *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enFsmId;
}TAF_XSMS_MO_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_CTX_STRU
 �ṹ˵��  : XSMS��������
 1.��    ��   : 2014��11��1��
   ��    ��   : l00208516
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        TAF XSMS MO״̬��״̬����״̬ջ
     **************************************************************************/
    TAF_XSMS_MO_FSM_CTX_STRU           stCurFsm;                               /* ״̬����ǰ��״̬������ */
}TAF_XSMS_MO_CTX_STRU;


typedef struct
{
    /**************************************************************************
                        TAF XSMS MT״̬��״̬
     **************************************************************************/
    TAF_XSMS_MT_FSM_CTX_STRU           stCurFsm;                               /* ״̬����ǰ��״̬������ */
}TAF_XSMS_MT_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_MO_SEND_POOL_ITEM_STRU
 �ṹ˵��  : MO���ż�¼��
 1.��    ��   : 2015��10��13��
   ��    ��   : c00299064
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsRecExist;  /* VOS_TRUE:���ڼ�¼ */
    VOS_UINT8                           ucRecTimeLeft; /* ���Ӽ�¼��ʱ��ʱ�����ó�60s �����0֮��ɾ����ǰ��¼*/
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid;
    VOS_UINT16                          usIsTlAckNeeded; /* TRUE: need ; FALSE :no NEED TL_ACK*/
    VOS_UINT16                          usOpId;
    TAF_XSMS_MESSAGE_STRU              *pst1xSms;      /* ���ż�¼ */
}TAF_XSMS_MO_SEND_POOL_ITEM_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XSMS_MO_SEND_MSG_POOL_STRU
 �ṹ˵��  : MO���ż�¼��
 1.��    ��   : 2015��10��13��
   ��    ��   : c00299064
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCurItemNumInPool;
    TAF_XSMS_MO_SEND_POOL_ITEM_STRU     stPoolItem[TAF_XSMS_MAX_REC_IN_POOL];
}TAF_XSMS_MO_SEND_MSG_POOL_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern TAF_XSMS_MO_SEND_MSG_POOL_STRU          g_stXsmsMoSendPool;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern TAF_XSMS_MSG_MO_REC_STRU * TAF_XSMS_MoGetRecAddr(VOS_VOID);
extern TAF_XSMS_MSG_MT_REC_STRU * TAF_XSMS_MtGetRecAddr(VOS_VOID);

extern TAF_XSMS_MO_CTX_STRU* TAF_XSMS_MoGetCtxAddr(VOS_VOID);
extern TAF_XSMS_MT_CTX_STRU* TAF_XSMS_MtGetCtxAddr(VOS_VOID);
extern TAF_XSMS_MT_FSM_CTX_STRU* TAF_XSMS_MtGetCurFsmAddr(VOS_VOID);

extern TAF_XSMS_MO_FSM_CTX_STRU* TAF_XSMS_MoGetCurFsmAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtSetCurrFsmState(VOS_UINT32 ulCurrState);
extern VOS_VOID TAF_XSMS_MoSetCurrFsmState(VOS_UINT32 ulCurrState);
extern TAF_XSMS_MO_FSM_ID_ENUM_UINT32 TAF_XSMS_MoGetCurrFsmId(VOS_VOID);
extern TAF_XSMS_MT_FSM_ID_ENUM_UINT32 TAF_XSMS_MtGetCurrFsmId(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoIdleInit(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtIdleInit(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoStopAllTimer(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtStopAllTimer(VOS_VOID);
extern VOS_VOID TAF_XSMS_MoInitGobal(VOS_VOID);
extern VOS_VOID TAF_XSMS_MtInitGobal(VOS_VOID);
extern TAF_XSMS_CTRL_INFO_STRU * TAF_XSMS_GetReqCtrlInfoAddr(VOS_VOID);
extern TAF_XSMS_INIT_CTRL_INFO_STRU * TAF_XSMS_GetInitCtrlInfoAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_ReqCtrlInfoClear(VOS_VOID);
extern VOS_VOID TAF_XSMS_InitCtrlInfoClear(VOS_VOID);
extern VOS_UINT8 TAF_XSMS_MoGetBearSeqNum(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec);
extern TAF_STA_STRU* TAF_XSMS_MtGetStaTblAddr(VOS_VOID);
extern TAF_STA_STRU* TAF_XSMS_MoGetStaTblAddr(VOS_VOID);
extern VOS_VOID TAF_XSMS_InitFsmCtx_Main(VOS_VOID);
extern VOS_VOID TAF_XSMS_RegMoFsm(VOS_VOID);
extern VOS_VOID TAF_XSMS_RegMtFsm(VOS_VOID);
extern VOS_VOID TAF_XSMS_SetApMemFullFlag(
    TAF_XSMS_AP_MEM_FULL_ENUM_UINT8     enAPMemFullFlag
);
extern TAF_XSMS_CCF_AP_MEM_FULL_ENUM8 TAF_XSMS_GetApMemFullFlag(VOS_VOID);
VOS_VOID TAF_XSMS_TranslatePlusToNum(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr
);

VOS_UINT32 TAF_XSMS_GetHomeMcc(
    VOS_VOID
);

VOS_VOID TAF_XSMS_TransAsciiToDtmf(
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pucDestData,
    VOS_UINT8                           ucLen
);

VOS_VOID TAF_XSMS_MoInitSendPool(VOS_VOID);

VOS_UINT32 TAF_XSMS_IsMoSendPoolFull(VOS_VOID);

VOS_UINT32 TAF_XSMS_InsertRecToMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid,
    VOS_UINT16                          usIsTlAckNeeded,
    VOS_UINT16                          usOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
);

VOS_UINT32 TAF_XSMS_DeleteRecInMoSendPool
(
    VOS_UINT32                          ulRecIndex
);

VOS_UINT32 TAF_XSMS_GetRecFromMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16   *pusOrigPid,
    VOS_UINT16                         *pusIsTlAckNeeded,
    VOS_UINT16                         *pusOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
);

VOS_VOID TAF_XSMS_RefreshRecsInMoSendPool
(
    VOS_VOID
);

VOS_UINT32 TAF_XSMS_IsRecCanInsertToPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid
);

VOS_VOID TAF_XSMS_GetKmcDefaultAddress
(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
);
VOS_UINT32 TAF_XSMS_IsMoSendPoolEmpty(VOS_VOID);

VOS_UINT32 TAF_XSMS_IsMtKmcSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
);

extern VOS_UINT32 TAF_XSMS_RcvSendPoolMsgReq_MoIdle(VOS_VOID);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __TAF_XSMS_CTX_H__ */

