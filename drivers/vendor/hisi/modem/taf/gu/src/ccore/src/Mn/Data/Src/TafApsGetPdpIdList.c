/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsGetPdpIdList.c
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2011��12��23��
  ����޸�   :
  ��������   : �յ���ģ����Ϣ�󣬻�ȡ�����״̬��ʵ������Ӧ��PDP ID
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��23��
    ��    ��   : h44270
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsCtx.h"
#include "TafApsGetPdpIdList.h"
#include "TafLog.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "ExtAppCmInterface.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsApi.h"
#include "ApsL4aInterface.h"
#include "Taf_ApsForRabm.h"
#include "Taf_ApsForSndcp.h"
#include "MmcApsInterface.h"
#include "Taf_Aps.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsComFunc.h"
#include "TafApsSndInternalMsg.h"
#include "xcc_aps_pif.h"
#include "ApsCdsInterface.h"
#include "taf_aps_ppp_pif.h"
#include "MnApsComm.h"
#include "TafMmaInterface.h"
#include "hsm_aps_pif.h"
#include "ehsm_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_GET_PDPID_LIST_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
 ȫ�ֱ�����    : gastApsGetPdpIdList
 ȫ�ֱ���˵��  : ��ȡ��ǰ��Ϣ����Ӧ��״̬��ʵ��PDP ID�Ĵ������б�
 1.��    ��   : 2011��12��16��
   ��    ��   : h44270
   �޸�����   : �½�
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��AT���ΪTAF

*****************************************************************************/
TAF_APS_GET_FSM_PDPID_LIST_STRU gastApsGetPdpIdList[] =
{
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ), TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_MODIFY_REQ),           TAF_APS_GetPdpIdListWithAtCallModifyReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ),             TAF_APS_GetPdpIdListWithAtCallOrigReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ),         TAF_APS_GetPdpIdListWithAtPppDialOrigReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ),              TAF_APS_GetPdpIdListWithAtCallEndReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ANSWER_REQ),           TAF_APS_GetPdpIdListWithAtCallAnswerReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_HANGUP_REQ),           TAF_APS_GetPdpIdListWithAtCallHangupReq},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_CNF),               TAF_APS_GetPdpIdListWithSmPdpActCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_REJ),               TAF_APS_GetPdpIdListWithSmPdpActRej},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_IND),               TAF_APS_GetPdpIdListWithSmPdpActInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF),                 TAF_APS_GetPdpIdListWithSmPdpModifyCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND),                 TAF_APS_GetPdpIdListWithSmPdpModifyInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_REJ),                 TAF_APS_GetPdpIdListWithSmPdpModifyRej},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_DEACTIVATE_IND),             TAF_APS_GetPdpIdListWithSmPdpDeactivInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_DEACTIVATE_CNF),             TAF_APS_GetPdpIdListWithSmPdpDeactivCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_SEC_CNF),           TAF_APS_GetPdpIdListWithSmPdpActSecCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_SEC_REJ),           TAF_APS_GetPdpIdListWithSmPdpActSecRej},
#if (FEATURE_ON == FEATURE_LTE)
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_SETUP_CNF),              TAF_APS_GetPdpIdListWithEsmPdpSetupCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_NDISCONN_CNF),               TAF_APS_GetPdpIdListWithEsmNdisconnCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_MANAGER_IND),            TAF_APS_GetPdpIdListWithEsmPdpManageInd},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_MODIFY_CNF),             TAF_APS_GetPdpIdListWithEsmPdpModifyCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_MODIFY_IND),             TAF_APS_GetPdpIdListWithEsmPdpModifyInd},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_RELEASE_CNF),            TAF_APS_GetPdpIdListWithEsmReleaseCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_RELEASE_IND),            TAF_APS_GetPdpIdListWithEsmDeactivateInd},
    {TAF_BuildEventType(PS_PID_ESM,     ID_APP_ESM_PDP_SETUP_IND),              TAF_APS_GetPdpIdListWithEsmSetupInd},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_SET_CGANS_CNF),              TAF_APS_GetPdpIdListWithL4aSetCgansCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_ESM_SM_EPS_BEARER_INFO_IND),         TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd},
#endif
    {TAF_BuildEventType(WUEPS_PID_RABM, ID_RABM_APS_SYS_CHG_TO_GPRS_IND),       TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd},
    {TAF_BuildEventType(WUEPS_PID_RABM, RABM_APS_LOCAL_PDP_DEACT_REQ_MSG),      TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_ACT_RSP_MSG_TYPE),                  TAF_APS_GetPdpIdListWithSndcpActRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_MDF_RSP_MSG_TYPE),                  TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_DEACT_RSP_MSG_TYPE),                TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_STATUS_REQ_MSG_TYPE),               TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ), TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND),    TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd},

    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND), TAF_APS_GetPdpIdListWithAttachBearerActivateInd},

    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND), TAF_APS_GetPdpIdListWithServiceStatusChangeReq},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_ORIG_DATA_CALL_CNF),           TAF_APS_GetPdpIdListWithXccOrigDataCnf},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_HANGUP_DATA_CALL_CNF),         TAF_APS_GetPdpIdListWithXccHangUpDataCnf},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_DISC_IND),           TAF_APS_GetPdpIdListWithXccDataCallDiscInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND),            TAF_APS_GetPdpIdListWithXccIncomingCallInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_CONN_IND),           TAF_APS_GetPdpIdListWithXccDataCallConnInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_SERVICE_CONNECT_IND),     TAF_APS_GetPdpIdListWithXccDataSrvConnInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_ANSWER_DATA_CALL_CNF),         TAF_APS_GetPdpIdListWithXccAnswerDataCnf},
    {TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND),            TAF_APS_GetPdpIdListWithCdsCdataServiceInd},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND),   TAF_APS_GetPdpIdListWithPsCallEnterDormantInd},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ),  TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_ACT_CNF),                     TAF_APS_GetPdpIdListWithPppActCnf},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_CNF),                   TAF_APS_GetPdpIdListWithPppDeactCnf},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_NTF),                TAF_APS_GetPdpIdListWithPppDeactNtf},

     {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_MODIFY_IND),                 TAF_APS_GetPdpIdListWithPppModifyInd},

    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_RECONN_IND),                  TAF_APS_GetPdpIdListWithPppReconnInd},


    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ), TAF_APS_GetPdpIdListWithEpdszidReOrigReq},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_RESUME_IND),         TAF_APS_GetPdpIdListWithXccDataCallResumeInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND),    TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_ORIG_CNF),    TAF_APS_GetPdpIdListWithHsmOrigCnf},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_DISC_CNF),    TAF_APS_GetPdpIdListWithHsmDiscCnf},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_DISC_IND),    TAF_APS_GetPdpIdListWithHsmDiscInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_CONNECT_IND), TAF_APS_GetPdpIdListWithHsmConnectInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF),    TAF_APS_GetPdpIdListWithHsm1XToHrpdHandOffCnf},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ),    TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ),    TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_ACTIVATE_CNF),    TAF_APS_GetPdpIdListWithEhsmPdnActCnf},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_ATTACH_CNF),      TAF_APS_GetPdpIdListWithEhsmPdnAttachCnf},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_DEACTIVATE_CNF),  TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_DEACTIVATE_IND),  TAF_APS_GetPdpIdListWithEhsmPdnDeactInd},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_ACTIVATE_IND),    TAF_APS_GetPdpIdListWithEhsmPdnActInd},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND),    TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_INFO_CHANGE_IND),    TAF_APS_GetPdpIdListWithEhsmPdnModifyInd},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND),   TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd},

    {TAF_BuildEventType(WUEPS_PID_MMA, ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND),    TAF_APS_GetPdpIdListWithHrpdDataCallSysAcqInd},

#endif
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdOperationList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��16��
    ��    ��   : A00165503
    �޸�����   : DTS2012040100697: �Զ�Ӧ��ģʽ��, ���ཨ����ESP����, �û���
                 ���޸ĺ�ȥ����
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;

    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ü����� */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ�� */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpStateReq->stCidListStateInfo.aucCid);

    /* Ԥ�����Ѿ����������ȡ����PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(ucCidValue);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtCallEndReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_CALL_END_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtCallEndReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ǰ�Ȳ�֧��һ����ȥ������PDP�ĳ�����һ��ȥ����һ�� */
    pstAppMsg     = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* Ԥ�����Ѿ����������ȡ����PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstCallEndReq->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtCallAnswerReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtCallAnswerReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    if (VOS_NULL_PTR == pstNwActFsm)
    {
        pstPdpIdList->ucPdpNum = 0;
    }
    else
    {
        pstPdpIdList->aucPdpId[0] = pstNwActFsm->ucPdpId;
        pstPdpIdList->ucPdpNum = 1;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtCallHangupReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtCallHangupReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    if (VOS_NULL_PTR == pstNwActFsm)
    {
        pstPdpIdList->ucPdpNum = 0;
    }
    else
    {
        pstPdpIdList->aucPdpId[0] = pstNwActFsm->ucPdpId;
        pstPdpIdList->ucPdpNum = 1;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtCallModifyReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��16��
    ��    ��   : A00165503
    �޸�����   : DTS2012040100697: �Զ�Ӧ��ģʽ��, ���ཨ����ESP����, �û���
                 ���޸ĺ�ȥ����
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtCallModifyReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;

    ulBearerActivateFlg = VOS_FALSE;
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ǰ�Ȳ�֧��һ����Moidify���PDP�ĳ�����һ��Moidfyһ�� */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstCallModifyReq->stCidListInfo.aucCid);

    /* Ԥ�����Ѿ����������ȡ����PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(ucCidValue);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtCallOrigReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtCallOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ�� */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* Ԥ�����Ѿ����������ȡ����PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstCallOrigReq->stDialParaInfo.ucCid);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAtPppDialOrigReq
 ��������  : ��ȡ��ǰID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAtPppDialOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ�� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* Ԥ�����Ѿ����������ȡ����PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpActCnf
 ��������  : ��ȡ��ǰSM �ظ���Act Cnf��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum    = 1;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpActRej
 ��������  : ��ȡ��ǰSM �ظ���Act Rej��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpActInd
 ��������  : ��ȡ��ǰSM �ظ���Act Ind��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)pstMsg;


    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpModifyCnf
 ��������  : ��ȡ��ǰSM �ظ���Modify Cnf��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpModifyInd
 ��������  : ��ȡ��ǰSM ��Modify IND��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��4��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_GetPdpIdListWithSmPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_IND_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpModifyRej
 ��������  : ��ȡ��ǰSM �ظ���Modify Rej��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;


}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpDeactivInd
 ��������  : ��ȡ��ǰSM �ظ���Deactiv Ind��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : DTS2012060200787, ȥ����Ĭ�ϳ��أ��ҽӵ�ר�г���Ҳ��Ҫһ��ȥ����

  3.��    ��   : 2012��7��24��
    ��    ��   : A00165503
    �޸�����   : DTS2012072302387: APS����SM��DEACTIVATE_IND��Ϣʹ������ά��
                 ��NSAPI, ��ʹ��SM�ϱ���NSAPI
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmMsg;
    VOS_UINT8                           i;
    VOS_UINT8                           ucTearDownInd;
    VOS_UINT32                          ulOP_TearDownInd;

    pstSmMsg         = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    ucTearDownInd    = pstSmMsg->ucTearDownInd;
    ulOP_TearDownInd = pstSmMsg->bitOpTearDownInd;

    /* Deactive Ind��Ϣ���������TearDown,
       ��PDP�¹ҽӵ�����ר��PDPҲ����Ҫ����ȥ����� */
    if ((VOS_TRUE == ulOP_TearDownInd)
     && (TAF_PDP_TEAR_DOWN == ucTearDownInd))
    {
        if (APS_PDP_ACT_PRI == g_PdpEntity[pstSmMsg->ucConnectId].ActType)
        {
            /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum    = 1;

            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucNsapi);
        }
        else
        {
            /* ��ͨ����Ҫȥ����SecPDP��Ӧ��LinkedNsapi(��PDP)�����ҵ����йҽ���
               ��PDP�µô�PDP ID�����ҵ���PDP��Ӧ��PDP ID */
            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucLinkedNsapi);

            for (i = 0; i < TAF_APS_MAX_PDPID; i++)
            {
                if (g_PdpEntity[pstSmMsg->ucConnectId].ucLinkedNsapi == g_PdpEntity[i].ucNsapi)
                {
                    pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = i;
                    pstPdpIdList->ucPdpNum++;
                }
            }
        }
    }
    /* ����TearDownʱ, �����PriPDP��Ҫȥ�������PDP�¹ҽӵ�SecPdp
       ���򵥶�ȥ�����PDP */
    else
    {
        if (APS_PDP_ACT_PRI == g_PdpEntity[pstSmMsg->ucConnectId].ActType)
        {
            /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum = 1;

            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucNsapi);
        }
        else
        {
            /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum = 1;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpDeactivCnf
 ��������  : ��ȡ��ǰSM �ظ���Deactiv Cnf��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpActSecCnf
 ��������  : ��ȡ��ǰSM �ظ���ActSec Cnf��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSmPdpActSecRej
 ��������  : ��ȡ��ǰSM �ظ���ActSec Rej��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU*)pstMsg;

    /* pstSmMsg->ucCr��Ϊ��Ӧ��Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmPdpSetupCnf
 ��������  : ��ȡ��ǰESM �ϱ���Pdp Setup Cnf����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpSetupCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_SETUP_CNF_STRU         *pstCnf;

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmNdisconnCnf
 ��������  : ��ȡ��ǰESM �ϱ���Ndidconn Cnf����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmNdisconnCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_NDISCONN_CNF_STRU          *pstCnf;

    pstCnf = (APP_ESM_NDISCONN_CNF_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid);
    pstPdpIdList->ucPdpNum = 1;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmPdpManageInd
 ��������  : ��ȡ��ǰESM �ϱ���ID_APP_ESM_PDP_MANAGER_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpManageInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_MANAGER_IND_STRU       *pstEsmManageInd;

    pstEsmManageInd = (APP_ESM_PDP_MANAGER_IND_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstEsmManageInd->ulCid);
    pstPdpIdList->ucPdpNum = 1;
}



/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmPdpModifyCnf
 ��������  : ��ȡ��ǰESM �ϱ���Pdp Modify Cnf����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU        *pstEsmModifyCnf;

    pstEsmModifyCnf = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstEsmModifyCnf->ulCid);
    pstPdpIdList->ucPdpNum = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmPdpModifyInd
 ��������  : ��ȡ��ǰESM �ϱ���Pdp Modify Ind����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_MODIFY_IND_STRU        *pstEsmModifyInd;

    pstEsmModifyInd = (APP_ESM_PDP_MODIFY_IND_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstEsmModifyInd->ulCid);
    pstPdpIdList->ucPdpNum = 1;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmReleaseCnf
 ��������  : ��ȡ��ǰESM �ϱ���Pdp Release Cnf����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmReleaseCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_RELEASE_CNF_STRU       *pstEsmReleaseCnf;

    pstEsmReleaseCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    /* ����Ϣ�� ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstEsmReleaseCnf->ulCid);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmDeactivateInd
 ��������  : ��ȡ��ǰL4A �ϱ���Pdp Deactivate Ind����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��  : 2015��5��29��
    ��    ��  : a00165503
    �޸�����  :  MODIFY for DTS2015051204781

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_RELEASE_IND_STRU       *pstEsmDeactivateInd;

    pstEsmDeactivateInd = (APP_ESM_PDP_RELEASE_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstEsmDeactivateInd->bitOpLinkCid)
    {
        /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstEsmDeactivateInd->ulCid);
        pstPdpIdList->ucPdpNum = 1;
    }
    else
    {
        /* ����Ϣ��������EpsbId�����Ҷ�Ӧ��PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByEpsbId(pstEsmDeactivateInd->ulEpsbId);
        pstPdpIdList->ucPdpNum = 1;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmSetupInd
 ��������  : ��ȡ��ǰESM �ϱ���PDP SETUP IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmSetupInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APP_ESM_PDP_SETUP_IND_STRU         *pstPdpSetupInd;

    pstPdpSetupInd = (APP_ESM_PDP_SETUP_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstPdpSetupInd->bitOpLinkCid)
    {
        /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
        pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpSetupInd->ulCid);
        pstPdpIdList->ucPdpNum      = 1;
    }
    else
    {
        /* ����Ϣ��������RabId�����Ҷ�Ӧ��PDP ID */
        pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByEpsbId(pstPdpSetupInd->ulRabId);
        pstPdpIdList->ucPdpNum      = 1;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd
 ��������  : ��ȡ��ǰESM �ϱ���Bear info Ind����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��  : 2015��5��29��
    ��    ��  : a00165503
    �޸�����  :  MODIFY for DTS2015051204781
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucCid;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    /* ǰ��Ԥ�����Ѿ��������ﲻ���ܳ���CID�ǲ��������쳣�� */
    ucCid = TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid);

    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID��Ԥ�������Ѿ����, ucCidһ����ֵ */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(ucCid);
        pstPdpIdList->ucPdpNum = 1;
    }
    else
    {
        /* ����Ϣ��������EpsbId�����Ҷ�Ӧ��PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByEpsbId(pstBearerInfo->ulEpsbId);
        pstPdpIdList->ucPdpNum = 1;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithL4aSetCgansCnf
 ��������  : ��ȡ��ǰL4A �ϱ���Set Cgans Cnf����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��30��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithL4aSetCgansCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpIdList->ucPdpNum    = 1;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithAttachBearerActivateInd
 ��������  : ��ȡ��ǰ�ڲ���ϢID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg       --- ��Ϣָ��
             pstPdpIdList --- PDP�����б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithAttachBearerActivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* ע����ؼ���ָʾ��Ϣ��Ҫ���뵽���е�ʵ��״̬���� */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd
 ��������  : ��ȡ��ǰRABM�ϱ���ID_RABM_APS_SYS_CHG_TO_GPRS_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* ��ǰ���ۣ�RABM��Ϣ�����ⲿ��飬��ͬMMC����Ϣ��Ҫ���뵽���е�ʵ��״̬���� */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg
 ��������  : ��ȡ��ǰRabm �ϱ���ApsLocalPdpDeactReqMsg��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* ��ǰ���ۣ�RABM��Ϣ�����ⲿ��飬��ͬMMC����Ϣ��Ҫ���뵽���е�ʵ��״̬���� */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSndcpActRspMsgType
 ��������  : ��ȡ��ǰSndcp �ϱ���APS_SN_ACT_RSP_MSG_TYPE��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSndcpActRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_SNDCP_ACTIVATE_RSP_MSG         *pstSnActRsp;

    pstSnActRsp = (APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnActRsp->ApsSnActRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType
 ��������  : ��ȡ��ǰSndcp �ϱ���APS_SN_MDF_RSP_MSG_TYPE��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    APS_SNDCP_MODIFY_RSP_MSG           *pstSnModifyRsp;

    pstSnModifyRsp = (APS_SNDCP_MODIFY_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnModifyRsp->ApsSnMdfRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType
 ��������  : ��ȡ��ǰSndcp �ϱ���APS_SN_DEACT_RSP_MSG_TYPE��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    APS_SNDCP_DEACTIVATE_RSP_MSG       *pstSnDeactivateRsp;

    pstSnDeactivateRsp = (APS_SNDCP_DEACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnDeactivateRsp->ApsSnDeActRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType
 ��������  : ��ȡ��ǰSndcp �ϱ���APS_SN_STATUS_REQ_MSG_TYPE��Ϣ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* SNDCP��Ϣ��Ҫ���뵽���е�ʵ��״̬���� */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq
 ��������  : ��ȡ��ǰ�ڲ���ϢID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd
 ��������  : ��ȡ��ǰ�ڲ���ϢID_APS_APS_LOCAL_PDP_DEACTIVATE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��06��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithApsInternalPdpActivateReq
 ��������  : ��ȡ��ǰ�ڲ���ϢID_APS_APS_INTERNAL_PDP_ACTIVATE_REQ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpActivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetFsmPdpIdList
 ��������  : ���õ�ǰPdp Id����Ӧ��Lay2״̬����ҪǨ�Ƶ�״̬
 �������  : ulState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_APS_GetFsmPdpIdList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                              i;
    VOS_UINT32                              ulTblSize;
    TAF_APS_GET_FSM_PDPID_FUNC_PTR          pGetPdpIdFsmProcFunc;
    REL_TIMER_MSG                          *pstTimerMsg;

    if ( VOS_PID_TIMER == pstMsg->ulSenderPid )
    {
        pstTimerMsg = (REL_TIMER_MSG*)pstMsg;
        pstPdpIdList->ucPdpNum = 1;
        pstPdpIdList->aucPdpId[0] = (VOS_UINT8)pstTimerMsg->ulPara;
        return;
    }


    ulTblSize = sizeof(gastApsGetPdpIdList)/sizeof(gastApsGetPdpIdList[0]);

    /*��ulEventType�У����Ҷ�Ӧ�Ĵ�����*/
    pGetPdpIdFsmProcFunc = VOS_NULL_PTR;
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (ulEventType == gastApsGetPdpIdList[i].ulEventType)
        {
            pGetPdpIdFsmProcFunc = gastApsGetPdpIdList[i].pGetPdpIdFsmProcFunc;

            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pGetPdpIdFsmProcFunc)
    {
        /* ������Ϣ���ͷ�����Ϣ��Я����CR,CID��ȡ����ǰ��Ϣ
           ��Ӧ��ѡ�õ�״̬��ʵ�� */
        pGetPdpIdFsmProcFunc(pstMsg, pstPdpIdList);

    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithServiceStatusChangeReq
 ��������  : ��ȡID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithServiceStatusChangeReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU     *pstSvcStatusChgReq;


    pstSvcStatusChgReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstSvcStatusChgReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccOrigDataCnf
 ��������  : ��ȡID_XCC_APS_ORIG_DATA_CALL_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccOrigDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstCallCnf;

    pstCallCnf = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccHangUpDataCnf
 ��������  : ��ȡID_XCC_APS_HANGUP_DATA_CALL_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccHangUpDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU  *pstCallCnf;

    pstCallCnf = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccDataCallDiscInd
 ��������  : ��ȡID_XCC_APS_DATA_CALL_DISC_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  �޸���ʷ      :
   1.��    ��   : 2014��10��24��
     ��    ��   : h00246512
     �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstCallDiscInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstCallDiscInd = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstCallDiscInd->ucConnectId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }


}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccIncomingCallInd
 ��������  : ��ȡID_XCC_APS_INCOMING_CALL_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccIncomingCallInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstIncomingInd = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }


        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.enSo == pstIncomingInd->enSo)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccDataCallConnInd
 ��������  : ��ȡID_XCC_APS_DATA_CALL_CONN_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstConnInd;

    pstConnInd = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstConnInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccDataSrvConnInd
 ��������  : ��ȡID_XCC_APS_DATA_SERVICE_CONNECT_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccDataSrvConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstConnInd;

    pstConnInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstConnInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccAnswerDataCnf
 ��������  : ��ȡID_XCC_APS_ANSWER_DATA_CALL_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccAnswerDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU      *pstCallCnf;

    pstCallCnf = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithCdsCdataServiceInd
 ��������  : ��ȡID_CDS_APS_CDATA_SERVICE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithCdsCdataServiceInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    CDS_APS_CDATA_SERVICE_IND_STRU         *pstSrvInd;
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity   = VOS_NULL_PTR;

    pstSrvInd = (CDS_APS_CDATA_SERVICE_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }
        pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->ucNsapi == pstSrvInd->ucRabId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPsCallEnterDormantInd
 ��������  : ��ȡID_MSG_TAF_PS_ENTER_DORMANT_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPsCallEnterDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstEnterDormInd;


    pstEnterDormInd = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstEnterDormInd->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq
 ��������  : ��ȡID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU     *pstExtCallEndReq;


    pstExtCallEndReq = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstExtCallEndReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPppActCnf
 ��������  : ��ȡID_PPP_APS_ACT_CNF����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf = VOS_NULL_PTR;

    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppActCnf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPppDeactCnf
 ��������  : ��ȡID_PPP_APS_DEACT_CNF����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_DEACT_CNF_STRU             *pstPppDeactCnf = VOS_NULL_PTR;

    pstPppDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppDeactCnf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPppDeactNtf
 ��������  : ��ȡID_PPP_APS_DEACT_IND����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppDeactNtf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_DEACT_NTF_STRU             *pstPppDeactNtf = VOS_NULL_PTR;

    pstPppDeactNtf = (PPP_APS_DEACT_NTF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppDeactNtf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPppModifyInd
 ��������  : ��ȡID_PPP_APS_MODIFY_IND����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_MODIFY_IND_STRU            *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (PPP_APS_MODIFY_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppModifyInd->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithPppReconnInd
 ��������  : ��ȡID_PPP_APS_RECONN_IND��Ϣ��Ҫ������PDPID�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppReconnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_RECONN_IND_STRU            *pstPppReconnInd = VOS_NULL_PTR;

    pstPppReconnInd = (PPP_APS_RECONN_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppReconnInd->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEpdszidReOrigReq
 ��������  : After Rcv Epdszid Re-Orig Req Msg ,Get PdpIds Which need to Proc this Msg
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEpdszidReOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulMainfsmState;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        ulMainfsmState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

        if ((TAF_APS_STA_DORMANT        == ulMainfsmState)
         || (TAF_APS_STA_ACTIVE         == ulMainfsmState)
         || (TAF_APS_STA_CDATA_DISCING  == ulMainfsmState))
        {
            pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = ucPdpId;
            pstPdpIdList->ucPdpNum++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccDataCallResumeInd
 ��������  : After Receiving ID_XCC_APS_DATA_CALL_RESUME_IND ,
             Getting PdpId List Which need to Process this Msg
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallResumeInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU  *pstResumeInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstResumeInd = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstResumeInd->ucConnectId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd
 ��������  : After Receiving ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND ,
             Getting PdpId List Which need to Process this Msg
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInfoInd;

    pstDataCallInfoInd = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDataCallInfoInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsmOrigCnf
 ��������  : ��ȡID_HSM_APS_ORIG_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmOrigCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOrigCnf;

    pstOrigCnf = (HSM_APS_ORIG_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstOrigCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsmConnectInd
 ��������  : ��ȡID_HSM_APS_CONNECT_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmConnectInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_STA_ENUM_UINT32             enStatus;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* ��ǰֻ֧��dormant״̬�£����緢���Ѱ���������Ч��PDP ID��ֱ������ */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ���缤��ֻ����DORMANT��TAF_APS_STA_CDATA_ESTING״̬�µ����� */
        enStatus = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ((TAF_APS_STA_DORMANT == enStatus)
          ||(TAF_APS_STA_CDATA_ESTING == enStatus))
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;

            /* ��״̬������ */
            return ;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsmDiscCnf
 ��������  : ��ȡID_HSM_APS_DISC_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf;

    pstDiscCnf = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDiscCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsmDiscInd
 ��������  : ��ȡID_HSM_APS_DISC_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_DISC_IND_STRU              *pstDiscInd;

    pstDiscInd = (HSM_APS_DISC_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDiscInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsmOrigCnf
 ��������  : ��ȡID_HSM_APS_LOC_CHANGED_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmLocChangedInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
/*    HSM_APS_LOC_CHANGED_IND_STRU       *pstLocChangedInd;

    pstLocChangedInd = (HSM_APS_LOC_CHANGED_IND_STRU *)pstMsg;
*/
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHsm1XHrpdHandOff
 ��������  : ��ȡID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsm1XToHrpdHandOffCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpIdList->aucPdpId[0] = ucPdpId;
        pstPdpIdList->ucPdpNum    = 1;

        /* ��״̬������ */
        return ;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq
 ��������  : ��ȡID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU     *pst1XToHrpdReq;


    pst1XToHrpdReq = (TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pst1XToHrpdReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq
 ��������  : ��ȡID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU        *pstHrpdTo1XReq;


    pstHrpdTo1XReq = (TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstHrpdTo1XReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnActCnf
 ��������  : ��ȡID_EHSM_APS_PDN_ACTIVATE_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstEhsmPdnActCnf;

    pstEhsmPdnActCnf          = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnActCnf->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnAttachCnf
 ��������  : ��ȡID_EHSM_APS_PDN_ATTACH_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnAttachCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstEhsmPdnAttachCnf;

    pstEhsmPdnAttachCnf = (EHSM_APS_PDN_ATTACH_CNF_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnAttachCnf->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf
 ��������  : ��ȡID_EHSM_APS_PDN_DEACTIVATE_CNF����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstEhsmPdnDeactCnf;

    pstEhsmPdnDeactCnf        = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnDeactCnf->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf
 ��������  : ��ȡID_EHSM_APS_PDN_DEACTIVATE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstEhsmPdnDeactInd;

    pstEhsmPdnDeactInd        = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstEhsmPdnDeactInd->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnActInd
 ��������  : ��ȡID_EHSM_APS_PDN_ACTIVATE_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    EHSM_APS_PDN_ACTIVATE_IND_STRU   *pstEhsmPdnActInd;

    pstEhsmPdnActInd          = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnActInd->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmPdnModifyInd
 ��������  : ��ȡID_EHSM_APS_PDN_INFO_CHANGE_IND����Ӧ��Ҫ������PDP�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��8��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstEhsmPdnChgInd;

    pstEhsmPdnChgInd          = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU *)pstMsg;

    /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnChgInd->ucCid);
    pstPdpIdList->ucPdpNum    = 1;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd
 ��������  : ��ȡID_EHSM_APS_PDN_IRAT_HRPD_IND����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU   *pstEhsmHandoverInd;

    pstEhsmHandoverInd          = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByCid(pstEhsmHandoverInd->ucCid);
    pstPdpIdList->ucPdpNum      = 1;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd
 ��������  : ��ȡID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND����Ӧ��Ҫ������PDP�б�
 �������  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU   *pstEnd1xSvcInd;

    pstEnd1xSvcInd              = (TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0]   = pstEnd1xSvcInd->ucPdpId;
    pstPdpIdList->ucPdpNum      = 1;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPdpIdListWithHrpdDataCallSysAcqInd
 ��������  : ��ȡID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND����Ӧ��Ҫ������PDP�б�
 �������  : pstMsg:�������Ϣ
 �������  : pstPdpIdList - PDP�����б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��17��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHrpdDataCallSysAcqInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpIdList->aucPdpId[0] = ucPdpId;
        pstPdpIdList->ucPdpNum    = 1;

        /* ��״̬������ */
        return ;
    }

}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
