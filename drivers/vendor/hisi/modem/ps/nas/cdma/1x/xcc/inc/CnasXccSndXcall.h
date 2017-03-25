/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndXcall.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��9��15��
  ����޸�   :
  ��������   : CnasXccSndXcall.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��15��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNASXCCSNDXCALL_H__
#define __CNASXCCSNDXCALL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasXccCtx.h"
#include  "xcc_taf_pif.h"
#include  "CnasXccComFunc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


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

extern VOS_VOID CNAS_XCC_SndXcallAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef,
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enCurrentSo,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);

extern VOS_VOID CNAS_XCC_SndXcallCallConnectInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

extern VOS_VOID CNAS_XCC_SndXcallCallDiscInd(
   VOS_UINT8                            ucCallId,
   VOS_UINT8                            ucConnectId,
   TAF_XCC_CAUSE_ENUM_UINT32            enCause
);

extern VOS_VOID CNAS_XCC_SndXcallCodecChangedInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

extern VOS_VOID CNAS_XCC_SndXcallCodecCloseInd( VOS_VOID );

extern VOS_VOID CNAS_XCC_SndXcallCodecOpenInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

extern VOS_VOID CNAS_XCC_SndXcallHangUpCallCnf(
   VOS_UINT8                           ucCallId
);

extern VOS_VOID CNAS_XCC_SndXcallIncomingCallInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

extern VOS_VOID CNAS_XCC_SndXcallOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucOrigCallId,
    VOS_INT16                           sRssi
);

extern VOS_VOID CNAS_XCC_SndXcallSoCtrlMsgInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
   VOS_UINT8                          *pucSoCtrlData,
   VOS_UINT8                           ucDataLen,
   VOS_UINT8                           ucActTime
);

extern VOS_VOID CNAS_XCC_SndXcallSoCtrlOrderInd(
   CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
   VOS_UINT8                           ucORDQ
);

extern VOS_VOID CNAS_XCC_SndXcallSendFlashCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);

extern VOS_VOID CNAS_XCC_SndXcallSendBurstDTMFCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);

extern VOS_VOID CNAS_XCC_FillInfoRecIndWithAWIM(
    CNAS_XCC_AWIM_STRU                 *pstAWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID CNAS_XCC_FillInfoRecIndWithEAWIM(
    CNAS_XCC_EAWIM_STRU                *pstEAWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID CNAS_XCC_SndXcallInfoRecInd(
    VOS_UINT8                                                   ucCallId,
    CAS_CNAS_1X_RX_TCH_MSG_TYPE_ENUM_UINT8                      enRxTcMsgType,
    VOS_UINT8                                                  *pucInfoRecData
);

extern VOS_VOID CNAS_XCC_FillInfoRecIndWithFWIM(
    CNAS_XCC_FWIM_STRU                 *pstFWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID CNAS_XCC_FillInfoRecIndWithEFWIM(
    CNAS_XCC_EFWIM_STRU                *pstEFWIM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID CNAS_XCC_FillInfoRecIndInfoRecs(
    CNAS_XCC_INFO_RECS_STRU            *pstInfoRes,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);
VOS_VOID CNAS_XCC_SndXcallCschInfoRecInd(
    VOS_UINT8                                               ucCallId,
    CAS_CNAS_1X_RX_COMMON_MSG_TYPE_ENUM_UINT8               enRxCommMsgType,
    VOS_UINT8                                              *pucInfoRecData
);
VOS_VOID CNAS_XCC_FillInfoRecIndWithFNM(
    CNAS_XCC_FNM_STRU                  *pstFNM,
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);


VOS_VOID CNAS_XCC_SndXcallNdssResultInd(
    XCC_XCALL_NDSS_RESULT_ENUM_UINT8    enNsddResult
);
VOS_VOID CNAS_XCC_SndXcallContDTMFInd(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigit,
    VOS_UINT8                           ucSwitch
);

VOS_VOID CNAS_XCC_SndXcallBurstDtmfInd(
    VOS_UINT8                           ucCallId,
    CNAS_XCC_SEND_BURST_DTMF_STRU      *pstBurstDtmfVal
);

VOS_VOID CNAS_XCC_SndXcallSendContDTMFCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID CNAS_XCC_SndXcallEccServiceCnf(
    XCC_XCALL_ECC_SERVICE_RESULT_ENUM_UINT8           enRslt
);

VOS_VOID CNAS_XCC_SndXcallTchAssignCmplInd(VOS_VOID);
#endif

VOS_VOID CNAS_XCC_SndXcallPrivacyModeSetCnf(
    XCC_XCALL_RESULT_ENUM_UINT32        enResult,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usOpId
);

VOS_VOID CNAS_XCC_SndXcallPrivacyModeQryCnf(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyMode,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usOpId
);

VOS_VOID CNAS_XCC_SndXcallPrivacyModeInd(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyModeSetting,
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enCallPrivacyMode,
    VOS_UINT8                           ucCallId
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

#endif /* end of CnasXccSndXcall.h */
