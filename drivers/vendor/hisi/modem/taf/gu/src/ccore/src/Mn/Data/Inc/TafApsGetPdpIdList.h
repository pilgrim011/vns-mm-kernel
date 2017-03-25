/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsGetPdpIdList.h
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2011��12��23��
  ����޸�   :
  ��������   : TafApsGetPdpIdList.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��23��
    ��    ��   : h44270
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFAPS_PDPID_ENTITY_H__
#define __TAFAPS_PDPID_ENTITY_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsCtx.h"
#include "Taf_Aps.h"


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
 �ṹ��    : TAF_APS_PDPID_LIST_STRU
 �ṹ˵��  : ���浱ǰ��Ҫ������״̬��ʵ������Ӧ��PDP ID
 1.��    ��   : 2012��12��17��
   ��    ��   : h44270
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdpNum;
    VOS_UINT8                           aucPdpId[TAF_APS_MAX_PDPID];
} TAF_APS_PDPID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : TAF_APS_GET_FSM_PDPID_FUNC_PTR
 �ṹ˵��  : ��ȡPDP ID�����б�Ĵ�����ָ��
  1.��    ��   : 2011��6��27��
    ��    ��   : l00130025
    �޸�����   : ����
*****************************************************************************/
typedef VOS_VOID (*TAF_APS_GET_FSM_PDPID_FUNC_PTR)(struct MsgCB *pstMsg, TAF_APS_PDPID_LIST_STRU *pstPdpOperationList);

/*****************************************************************************
 �ṹ��    : TAF_APS_GET_FSM_PDPID_LIST_STRU
 �ṹ˵��  : ���ÿ�����̲�������ϢID����ȡ��ӦPDP ID�����б�
   1.��    ��   : 2011��12��18��
    ��    ��   : h44270
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    TAF_APS_GET_FSM_PDPID_FUNC_PTR      pGetPdpIdFsmProcFunc;
}TAF_APS_GET_FSM_PDPID_LIST_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtCallEndReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtCallHangupReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtCallAnswerReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtCallModifyReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtCallOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithAtPppDialOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID  TAF_APS_GetPdpIdListWithSmPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpSetupCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmNdisconnCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpManageInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmReleaseCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmSetupInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithL4aSetCgansCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
#endif

VOS_VOID TAF_APS_GetPdpIdListWithAttachBearerActivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSndcpActRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpActivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID  TAF_APS_GetFsmPdpIdList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccOrigDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccHangUpDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccIncomingCallInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccDataSrvConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccAnswerDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithCdsCdataServiceInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPsCallEnterDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPppActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPppDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPppDeactNtf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPppModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithPppReconnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);


VOS_VOID TAF_APS_GetPdpIdListWithEpdszidReOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallResumeInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHsmOrigCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHsmConnectInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHsmLocChangedInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithHsm1XToHrpdHandOffCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithServiceStatusChangeReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);


VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnAttachCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);

VOS_VOID TAF_APS_GetPdpIdListWithHrpdDataCallSysAcqInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
);
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
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

#endif /* end of TafApsCtx.h */
