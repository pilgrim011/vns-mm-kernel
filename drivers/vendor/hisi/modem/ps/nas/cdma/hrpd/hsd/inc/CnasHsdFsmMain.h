/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmMain.h
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��9��
  ����޸�   :
  ��������   : CnasHsdFsmMain.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��9��
    ��    ��   : g00256031
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_HSD_FSM_MAIN_H__
#define __CNAS_HSD_FSM_MAIN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdCtx.h"
#include "hsd_mscc_pif.h"
#include "hsm_hsd_pif.h"

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

extern VOS_UINT32 CNAS_HSD_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvPowerOffRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  CNAS_HSD_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvSwitchOnRsltCnf_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvInternalSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);

extern VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);

extern VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);

extern VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);

extern VOS_UINT32 CNAS_HSD_RcvSysAcqRsltCnfProc_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiAvailTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



extern VOS_UINT32 CNAS_HSD_RcvPilotSearch_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_HSD_RcvStartReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasOhmInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLostInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU *pstOocScheduleInfo
);

extern VOS_UINT16 CNAS_HSD_GetNextOocScheduleTimerLen(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
);

extern VOS_VOID CNAS_HSD_ProcOocSchedule(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
);

extern VOS_VOID CNAS_HSD_SetOocSearchScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
);

extern CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetOocSearchScene(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvPowerSaveRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_StartSysAcq_Inactive(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
);

extern VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_HSD_RcvCasSubnetIdChkReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasIratFromLteNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
);

extern VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_HrpdSubnetIdChkProc(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 CNAS_HSD_RcvCasNoRFInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_RcvCasNoRFInd_Proc(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);



extern HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32 CNAS_HSD_CovertSessionType_Proc(
    HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8                 enSessionRelType
);

extern VOS_UINT32 CNAS_HSD_RcvHsmSessionNegResultInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetAcqSceneBySysAcqStatus(VOS_VOID);

extern VOS_VOID CNAS_HSD_SetSysAcqStatusByAcqScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
);

extern VOS_UINT32 CNAS_HSD_RcvHsmConnOpenInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasHsdFsmMain.h */
