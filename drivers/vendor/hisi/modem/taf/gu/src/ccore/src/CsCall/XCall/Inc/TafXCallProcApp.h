/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcApp.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��9��3��
  ����޸�   :
  ��������   : TafXCallProcApp.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��3��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_APP_H__
#define __TAF_X_CALL_PROC_APP_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_ECC_RANDOM_LEN                            (16)

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
VOS_VOID TAF_XCALL_RcvAppCallOrigReq(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvAppSupsCmdReq(VOS_VOID *pMsg);

#if 0
VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelCallXReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelAllCallReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);


extern VOS_VOID TAF_XCALL_RcvAppSendBurstDTMFReq(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);

/* Buffer����������XCallProcAppŲ��XCallCtx.c�� */


VOS_VOID TAF_XCALL_RcvAgentGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppXlemaReq(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_RcvAppCustomDialReq(VOS_VOID *pMsg);

VOS_UINT32 TAF_XCALL_GetRedialPeriodTimerLen(
    VOS_UINT8                           ucCallId
);


VOS_VOID TAF_XCALL_RcvAppSendContDTMFReq(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_ReplaceFlashPlusWithDigit(
    VOS_UINT8                           ucSrcDigitNum,
    VOS_UINT8                          *pucSrcDigit,
    VOS_UINT8                          *pucDstDigitNum,
    VOS_UINT8                          *pucDstDigit
);

VOS_VOID TAF_XCALL_RcvAtCclprGetReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccNumSetReq(
    VOS_VOID                           *pMsg
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_RcvAppEncryptVoiceReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppRemoteCtrlAnswerReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccSrvCapCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccSrvCapQryReq(VOS_VOID *pstMsg);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_VOID TAF_XCALL_RcvAppEccTestModeCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccTestModeQryReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccKmcKeyCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccKmcKeyQryReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccRandomQryReq(VOS_VOID *pstMsg);
#endif
#endif

VOS_VOID TAF_XCALL_RcvAppPrivacyModeSetReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppPrivacyModeQryReq(VOS_VOID *pstMsg);
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

#endif /* end of TafXCallProcApp.h */

