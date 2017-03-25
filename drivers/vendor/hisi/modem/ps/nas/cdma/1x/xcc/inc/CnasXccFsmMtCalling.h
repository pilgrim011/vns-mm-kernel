/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccFsmMoCalling.h
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��4��
  ��������   : CnasXccFsmMoCalling.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��4��
    ��    ��   : w00242748
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _CNAS_XCC_FSM_MT_CALLING_H_
#define _CNAS_XCC_FSM_MT_CALLING_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "xcc_taf_pif.h"
#include "CnasXccCtx.h"
#include "cas_1x_control_main_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 CNAS_XCC_RcvAsPagingInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_NotifyTafCallDisc_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_BOOL                            isNeedToResumeAps
);

VOS_VOID CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
);

VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForOrder(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);

VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForAnswer(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
);
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer(VOS_VOID);

VOS_VOID CNAS_XCC_AutoAnswerLoopBackService_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
);

VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_UpdateMtCallInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID CNAS_XCC_CovertVoiceCallPagingIndSo(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                 *enSo
);
#endif
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif


