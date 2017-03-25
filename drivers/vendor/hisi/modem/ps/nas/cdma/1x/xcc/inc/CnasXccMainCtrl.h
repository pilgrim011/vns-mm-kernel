/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccMainCtrl.h
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��09��13��
  ��������   : CnasXccMainCtrl.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _CNAS_XCC_MAIN_CTRL_H_
#define _CNAS_XCC_MAIN_CTRL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "xcc_xcall_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "xcc_aps_pif.h"
#include "CnasXccCtx.h"

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

VOS_VOID CNAS_XCC_ClearBufferedUseReq(VOS_VOID);

VOS_VOID CNAS_XCC_ProcBufferedMsgUponPowerDown(VOS_VOID);

TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsXcallOrigCallReqAllowed(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
);

TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsApsOrigDataCallReqAllowed(VOS_VOID);

VOS_UINT8 CNAS_XCC_IsPaginMsgAllowed(
    CAS_CNAS_1X_PAGING_IND_STRU        *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
);

VOS_UINT32 CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8                       enPrivacyMode
);

VOS_UINT32 CNAS_XCC_ProcessXsdStartReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessApsOrigDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XCC_ProcessCas1xPagingInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessMsgInMainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 CNAS_XCC_ProcessPagingCollision(
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enPagingService,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
);

VOS_UINT32 CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl(VOS_VOID);

extern VOS_UINT32 CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessXccPowerDownInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
);

extern VOS_UINT32 CNAS_XCC_SndBurstDTMF_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq
);

extern VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(
    VOS_UINT8                           ucIndex
);

extern VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 CNAS_XCC_ProcessFlashL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
);

extern VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_FLASH_REQ_STRU      *pstXcallFlashReq
);


VOS_UINT32 CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_MainCtrl(
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);
VOS_VOID CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);


VOS_UINT32 CNAS_XCC_ProcessXcallEmergencyCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl(
    VOS_UINT8                           ucCurInstanceIndex
);

VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucMsgSeqNum,
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq
);

VOS_UINT32 CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupReq
);

VOS_UINT32 CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
);

VOS_UINT32 CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XCC_ProcessOrderMsg_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
);

VOS_VOID CNAS_XCC_ProcessCas1xTchSndBurstDtmfMsgInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_SndContDTMFToneOrder_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq
);

VOS_UINT32 CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
);

VOS_UINT32 CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(
    VOS_UINT8                           ucIndex
);

VOS_UINT32 CNAS_XCC_ProcessXCallStateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
);

VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
);

VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
);

VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
);


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT32 CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeSetReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
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

