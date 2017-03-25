/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmCdataEsting.h
  �� �� ��   : ����
  ��    ��   : y00218312
  ��������   : 2014��10��16��
  ����޸�   :
  ��������   : TafApsFsmCdataEsting.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFAPSFSMCDATAESTING_H__
#define __TAFAPSFSMCDATAESTING_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"
#include "TafAppMma.h"
#include  "Taf_Aps.h"


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

extern VOS_VOID  R_ITF_SetFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvCdsServiceInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
);

VOS_UINT32 TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_ProcCdataEstFail_CdataEsting(
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
);


VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulDoQuickAcq
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting(
    VOS_UINT8                           ucPdpId
);


VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvMmaHrpdDataCallSysAcqInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPppDialOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnAttachCnf_CdataEsting_WaitEhsmAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
);


VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppReConnInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppReConnInd_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmDiscInd_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmConnectInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

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

#endif /* end of TafApsFsmCdataEsting.h */
