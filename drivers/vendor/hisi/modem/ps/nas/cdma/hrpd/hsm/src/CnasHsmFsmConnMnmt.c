

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmConnMnmt.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmCtx.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmKeepAlive.h"
#include "cttf_hrpd_fsps_ctrl_callback_pif.h"
#include "CnasHsmFsmSessionAct.h"
#include "hsm_aps_pif.h"
#include "ehsm_hsm_pif.h"
#include "CnasHsmSndRrm.h"
#include "CnasHsmSndEhsm.h"
#include "CnasCcb.h"
#include "CnasHsmSndAps.h"
#include "CnasMntn.h"
#include "CnasHsmTimer.h"
#include "CnasHsmSndHsd.h"
#include "CnasHsmSndAs.h"
#include "CnasHsmDecode.h"
#include "CnasHsmEncode.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmMntn.h"
#include "cas_hrpd_idlestate_nas_pif.h"
#include "CnasTimerMgmt.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_CONN_MNMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/


VOS_UINT32 CNAS_HSM_RcvInterConnMnmtReq_ConnMnmt_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_CONN_MNMT_REQ_STRU         *pstConnMnmtReq;

    pstConnMnmtReq = (CNAS_HSM_HSM_CONN_MNMT_REQ_STRU *)pstMsg;

    CNAS_HSM_SetConnMnmtTriggerScene_ConnMnmt(pstConnMnmtReq->enTriggerScene);

    if ((CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN  == pstConnMnmtReq->enTriggerScene)
     || (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == pstConnMnmtReq->enTriggerScene))
    {
        CNAS_HSM_SndCasHrpdConnOpenReq(CNAS_CAS_HRPD_CONN_OPEN_TYPE_MO);
        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND,
                            TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND_LEN);

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND  == pstConnMnmtReq->enTriggerScene)
    {
        CNAS_HSM_SndCasHrpdConnOpenReq(CNAS_CAS_HRPD_CONN_OPEN_TYPE_MT);
        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND,
                            TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND_LEN);

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND);
    }
    else
    {
        CNAS_HSM_SndCasHrpdConnCloseReq();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                            TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasConnOpenInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_CONN_OPEN_IND_STRU                       *pstConnOpenInd;
    VOS_UINT8                                               ucCallId;
    HSM_APS_CAUSE_ENUM_UINT32                               enApsCallRslt;
    EHSM_HSM_RSLT_ENUM_UINT32                               enEhsmRlst;

    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    pstConnOpenInd = (CAS_CNAS_HRPD_CONN_OPEN_IND_STRU *)pstMsg;

    ucCallId        = CNAS_HSM_GetHsmCallId();
    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        if (CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC != pstConnOpenInd->enRslt)
        {
            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }

        enApsCallRslt = CNAS_HSM_MapApsCause(pstConnOpenInd->enRslt);

        CNAS_HSM_SndApsOrigCnf(ucCallId, enApsCallRslt);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND == enTriggerScene)
    {
        if (CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC == pstConnOpenInd->enRslt)
        {
            enSessionType  = CNAS_HSM_GetNegoSessionType();

            if (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType)
            {
                if (CNAS_HSM_CALL_ID_INVALID == ucCallId)
                {
                    CNAS_HSM_SndApsConnInd(ucCallId);
                }
            }
            else
            {
                CNAS_HSM_SndEhsmConnInd();
            }
        }
    }
    else /* trigger scene is CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN */
    {
        enEhsmRlst = CNAS_HSM_MapEhsmCause(pstConnOpenInd->enRslt);

        CNAS_HSM_SndEhsmConnEstCnf(enEhsmRlst);
    }

    if (CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC == pstConnOpenInd->enRslt)
    {
        CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_SUCC);
    }
    else
    {
        CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);
    }


    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitConnOpenIndTimerExp_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitConnOpenTimerExp_PreProc: timer out");

    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        ucCallId        = CNAS_HSM_GetHsmCallId();

        CNAS_HSM_SndApsOrigCnf(ucCallId, HSM_APS_CAUSE_TIMEOUT);

        /* ���call id */
        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_TIMEOUT);
    }
    else
    {
        /* page ind ����Ľ���ʧ�ܺ�֪ͨAPS/EHSM */
    }

    /* send hsd conn open ind */
    CNAS_HSM_SndHsdConnOpenInd(HSM_HSD_HRPD_CONN_OPEN_RSLT_FAIL);

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasConnCloseInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    CAS_CNAS_HRPD_CONN_CLOSE_IND_STRU                      *pstConnCloseInd;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND);
    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    pstConnCloseInd = (CAS_CNAS_HRPD_CONN_CLOSE_IND_STRU *)pstMsg;

    CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE);

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN == enTriggerScene)
    {
        ucCallId = CNAS_HSM_GetHsmCallId();

        if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == CNAS_HSM_ConvertCasCloseReasonToHsmCause(pstConnCloseInd->enConnCloseReason))
        {
            CNAS_HSM_SndApsDiscCnf(ucCallId, HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X);
        }
        else
        {
            CNAS_HSM_SndApsDiscCnf(ucCallId, HSM_APS_CAUSE_SUCCESS);
        }

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmDiscCnf();
    }
    /* not APS/EHSM invoke Conn Close, then only can be HSM power save invoke */
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE == enTriggerScene)
    {
        CNAS_HSM_SndHsdPowerSaveCnf();
        CNAS_HSM_SndEhsmSuspendInd();

        if (CNAS_HSM_SESSION_TYPE_HRPD == CNAS_HSM_GetNegoSessionType())
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
    }
    else
    {
        /* ����÷�֧�ĳ�����:page/aps/ehsm��������ʱ���յ���pa rat mode�ȴ����Ϣ */
    }

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_SUCC);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitConnCloseIndTimerExp_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitConnCloseTimerExp_PreProc: timer out");

    /* �ȴ�������ʱ���轫��ǰ������״̬����Ϊclose������ص�open̬��aps/ehsm���½���ʱ��
       hsm���ֵ�ǰ����״̬��ȻΪopen��ֱ����״̬�������ᷢ��conn open req��cas��֪ͨ�佨�� */
    CNAS_HSM_SetConnStatus(CNAS_HSM_HRPD_CONN_STATUS_CLOSE);

    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN == enTriggerScene)
    {
        ucCallId = CNAS_HSM_GetHsmCallId();

        CNAS_HSM_SndApsDiscCnf(ucCallId, HSM_APS_CAUSE_TIMEOUT);

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmDiscCnf();
    }
    /* not APS/EHSM invoke Conn Close, then only can be HSM power save invoke */
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE == enTriggerScene)
    {
        CNAS_HSM_SndHsdPowerSaveCnf();

        CNAS_HSM_SndEhsmSuspendInd();

        if (CNAS_HSM_SESSION_TYPE_HRPD == CNAS_HSM_GetNegoSessionType())
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
    }
    else
    {
        /* ����÷�֧�ĳ�����:page/aps/ehsm��������ʱ���յ���pa rat mode�ȴ����Ϣ */
    }

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    enTriggerScene = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        ucCallId = CNAS_HSM_GetHsmCallId();

        CNAS_HSM_SndApsOrigCnf(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_HRPD_SLAVE);
    }
    else
    {
        /* PAGE ����Ľ�����ʱ����ʧ�ܣ�����Ҫ֪ͨEHSM/APS */
    }

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;
    CNAS_HSM_CACHE_MSG_QUEUE_STRU                          *pstMsgQueue;
    APS_HSM_ORIG_REQ_STRU                                  *pstCallOrigMsg;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT8                                               ucCallId;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    ucCallId        = CNAS_HSM_GetHsmCallId();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);

        CNAS_HSM_SndApsOrigCnf(ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);
    }
    else /* trigger scene is CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND */
    {
        /* page�����Ľ���δ�ɹ�������Ҫ��aps/ehsm����ind��Ϣ */
    }

    /* �����EHSM�������󣬸�EHSMֱ�ӻظ�EHSM_HSM_RSLT_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_EHSM, (VOS_UINT16)ID_EHSM_HSM_CONN_EST_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����aps�������󣬸�EHSMֱ�ӻظ�HSM_APS_CAUSE_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(WUEPS_PID_TAF, (VOS_UINT16)ID_APS_HSM_ORIG_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        /* ��ȡ�����APS_HSM_ORIG_REQ��Ϣ */
        pstMsgQueue    = CNAS_HSM_GetCacheMsgAddr();
        pstCallOrigMsg = (APS_HSM_ORIG_REQ_STRU *)(&(pstMsgQueue->astCacheMsg[ucIndex]));

        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);;

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����page����������Ϊpage�Ľ������󲻳ɹ������ø�aps/ehsm����ind���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSP, (VOS_UINT16)ID_CAS_CNAS_HRPD_PAGE_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_SndCasHrpdConnCloseReq();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                        TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    /* Only for exception protect, for normal should not rcv suspend ind in this substate */
    CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvHsdSuspendInd_WaitConnCloseInd: Rcv Suspend Ind");

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND);

    enTriggerScene = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN == enTriggerScene)
    {
        ucCallId = CNAS_HSM_GetHsmCallId();

        CNAS_HSM_SndApsDiscCnf(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN == enTriggerScene)
    {
        /* �����ֻ֧����EHSM����Ķ������󣬲�������power save����Ķ�����
           ��ΪHSM�������ڻظ�power save cnf֮ǰ�յ�suspend ind */
        CNAS_HSM_SndEhsmDiscCnf();
    }
    else
    {
        /* ����÷�֧�ĳ�����:page/aps/ehsm��������ʱ���յ���pa rat mode�ȴ����Ϣ */
    }

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND);

    enTriggerScene = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN == enTriggerScene)
    {
        ucCallId = CNAS_HSM_GetHsmCallId();

        CNAS_HSM_SndApsDiscCnf(ucCallId, HSM_APS_CAUSE_HRPD_NETWORK_LOST);

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmDiscCnf();
    }
    /* not APS/EHSM invoke Conn Close, then only can be HSM power save invoke */
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE == enTriggerScene)
    {
        CNAS_HSM_SndHsdPowerSaveCnf();

        CNAS_HSM_SndEhsmSuspendInd();

        if (CNAS_HSM_SESSION_TYPE_HRPD == CNAS_HSM_GetNegoSessionType())
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
    }
    else
    {
        /* ����÷�֧�ĳ�����:page/aps/ehsm��������ʱ���յ���pa rat mode�ȴ����Ϣ */
    }

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd;
    VOS_UINT8                                               ucMsgType;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU *)pstMsg;
    ucMsgType = CNAS_HSM_SMP_MESSAGE_TYPE_BUTT;

    enProtocolType = pstSnpDataInd->enProtocolType;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        if (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN == ucMsgType)
        {
             CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
             CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstHrpdNetworkLostInd = VOS_NULL_PTR;
    HSM_APS_CAUSE_ENUM_UINT32                               enHsmApsCause;
    EHSM_HSM_RSLT_ENUM_UINT32                               enHsmEhsmRslt;
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTiggerScene;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    ucCallId = CNAS_HSM_GetHsmCallId();

    enTiggerScene = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    pstHrpdNetworkLostInd = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU *)pstMsg;

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTiggerScene)
    {
        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);

        /* �轫CAS_CNAS_HRPD_NETWORK_LOST_REDIRECTװ��ΪHSM_APS_CAUSE_REDIRECT��
           CAS_CNAS_HRPD_NETWORK_LOST_NO_RFװ��ΪHSM_APS_CAUSE_NO_RF��
           ����ԭ��ֵת��ΪHSM_APS_CAUSE_SIGNAL_FADE */
        enHsmApsCause = CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmApsErrCode(pstHrpdNetworkLostInd->enNetworkLostReason);

        CNAS_HSM_SndApsOrigCnf(ucCallId, enHsmApsCause);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTiggerScene)
    {
        /* �轫CAS_CNAS_HRPD_NETWORK_LOST_REDIRECTװ��ΪEHSM_HSM_RSLT_REDIRECT��
           CAS_CNAS_HRPD_NETWORK_LOST_NO_RFװ��ΪEHSM_HSM_RSLT_NO_RF��
           ����ԭ��ֵת��ΪEHSM_HSM_RSLT_SIGNAL_FADE */
        enHsmEhsmRslt = CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmEhsmErrCode(pstHrpdNetworkLostInd->enNetworkLostReason);

        CNAS_HSM_SndEhsmConnEstCnf(enHsmEhsmRslt);
    }
    else
    {
        /* page�����Ľ�����ʱ����δ�ɹ�������Ҫ֪ͨEHSM/APS */
    }

    CNAS_HSM_QuitFsmConnMnmtReq(CNAS_HSM_CONN_MNMT_RESULT_FAIL);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucMsgType;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU *)pstMsg;

    ucMsgType = CNAS_HSM_SMP_MESSAGE_TYPE_BUTT;

    enProtocolType = pstSnpDataInd->enProtocolType;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        if (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN == ucMsgType)
        {
             CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
             CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;
    CNAS_HSM_CACHE_MSG_QUEUE_STRU                          *pstMsgQueue;
    APS_HSM_ORIG_REQ_STRU                                  *pstCallOrigMsg;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT8                                               ucCallId;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    ucCallId        = CNAS_HSM_GetHsmCallId();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);

        CNAS_HSM_SndApsOrigCnf(ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);
    }
    else /* trigger scene is CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND */
    {
        /* page�����Ľ�����ʱ����δ�ɹ�������Ҫ֪ͨEHSM/APS */
    }

    /* �����EHSM�������󣬸�EHSMֱ�ӻظ�EHSM_HSM_RSLT_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_EHSM, (VOS_UINT16)ID_EHSM_HSM_CONN_EST_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����aps�������󣬸�EHSMֱ�ӻظ�HSM_APS_CAUSE_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(WUEPS_PID_TAF, (VOS_UINT16)ID_APS_HSM_ORIG_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        /* ��ȡ�����APS_HSM_ORIG_REQ��Ϣ */
        pstMsgQueue    = CNAS_HSM_GetCacheMsgAddr();
        pstCallOrigMsg = (APS_HSM_ORIG_REQ_STRU *)(&(pstMsgQueue->astCacheMsg[ucIndex]));

        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);;

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����page����������Ϊpage�Ľ������󲻳ɹ������ø�aps/ehsm����ind���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSP, (VOS_UINT16)ID_CAS_CNAS_HRPD_PAGE_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �Ż���: �����������OHM��Ϣ������������е�OHM��Ϣ����Ϊ�����ڴ���session close ind��ʱ����������Э�̣��˴���������
                OHM��Ϣ���������һЩ����Ҫ�Ĳ���(����UATI���̣�ȥ�������̵�)���˷ѿտ���Դ */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_SndCasHrpdConnCloseReq();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                        TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_ConnMnmt_WaitConnCloseInd
Description     :   process the internal session close message in wait conn close ind state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED--------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED----the current event need to further process

Modify History  :
1)  Date           : 2015-06-03
    Author         : y00307564
    Modify content : Create
2)  Date           : 2016-01-25
    Author         : w00351686
    Modify content : DTS2016011700511:��ǰ��������OHM��Ϣ�����������Ϣ�������������෢��session close
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    /* �����������OHM��Ϣ������������е�OHM��Ϣ����Ϊ�����ڴ���session close ind��ʱ������½���UATI,
        �˴����������OHM��Ϣ��������̬������ʱ���������෢������session close */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;
    CNAS_HSM_CACHE_MSG_QUEUE_STRU                          *pstMsgQueue;
    APS_HSM_ORIG_REQ_STRU                                  *pstCallOrigMsg;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT8                                               ucCallId;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    ucCallId        = CNAS_HSM_GetHsmCallId();

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);

        CNAS_HSM_SndApsOrigCnf(ucCallId, HSM_APS_CAUSE_CONN_FAIL);
    }
    else if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_CONN_FAIL);
    }
    else /* trigger scene is CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND */
    {
        /* page�����Ľ���δ�ɹ�������Ҫ��aps/ehsm����ind��Ϣ */
    }

    /* �����EHSM�������󣬸�EHSMֱ�ӻظ�EHSM_HSM_RSLT_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_EHSM, (VOS_UINT16)ID_EHSM_HSM_CONN_EST_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_CONN_FAIL);

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����aps�������󣬸�EHSMֱ�ӻظ�HSM_APS_CAUSE_SESSION_NOT_EXIST���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(WUEPS_PID_TAF, (VOS_UINT16)ID_APS_HSM_ORIG_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        /* ��ȡ�����APS_HSM_ORIG_REQ��Ϣ */
        pstMsgQueue    = CNAS_HSM_GetCacheMsgAddr();
        pstCallOrigMsg = (APS_HSM_ORIG_REQ_STRU *)(&(pstMsgQueue->astCacheMsg[ucIndex]));

        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_CONN_FAIL);;

        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����page����������Ϊpage�Ľ������󲻳ɹ������ø�aps/ehsm����ind���������ǰ����Ľ������� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSP, (VOS_UINT16)ID_CAS_CNAS_HRPD_PAGE_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_SndCasHrpdConnCloseReq();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                        TI_CNAS_HSM_REVISE_WAIT_HRPD_CONN_CLOSE_IND_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsDiscReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;
    APS_HSM_DISC_REQ_STRU                                  *pstApsDiscReq;

    /* �����aps�������������ǰ����Ľ������󣬲���Ҫ�ظ������ظ� */
    ulHsmEventType = CNAS_BuildEventType(WUEPS_PID_TAF, (VOS_UINT16)ID_APS_HSM_ORIG_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);
    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����page�����Ľ������������̲����� */
    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND == enTriggerScene)
    {
        pstApsDiscReq = (APS_HSM_DISC_REQ_STRU*)pstMsg;

        CNAS_HSM_SndApsDiscCnf(pstApsDiscReq->ucCallId, HSM_APS_CAUSE_SUCCESS);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    CNAS_HSM_SetConnMnmtTriggerScene_ConnMnmt(CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN);

    CNAS_HSM_SndCasHrpdConnCloseReq();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                        TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    /* �����EHSM�������������ǰ����Ľ������󣬲���Ҫ�ظ������ظ� */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_EHSM, (VOS_UINT16)ID_EHSM_HSM_CONN_EST_REQ);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    /* �����page�����Ľ������������̲����� */
    enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND == enTriggerScene)
    {
        CNAS_HSM_SndEhsmDiscCnf();

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

    CNAS_HSM_SetConnMnmtTriggerScene_ConnMnmt(CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN);

    CNAS_HSM_SndCasHrpdConnCloseReq();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                        TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvApsOrigReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN != CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt())
    {
        CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRemainLen;

    /* hsm�ڵȴ�conn close indʱ���յ�power off req��Ϣ, ����ǰ��Ķ�ʱ��ʱ��С��1.5s����������ʱ����
       �����ȴ������������ȴ�conn close ind��ʱ�� */
    ulRemainLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSM, TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND, 0);
    if (TI_CNAS_HSM_REVISE_WAIT_HRPD_CONN_CLOSE_IND_LEN < ulRemainLen)
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND);

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND ,
                            TI_CNAS_HSM_REVISE_WAIT_HRPD_CONN_CLOSE_IND_LEN);
    }

    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsOrigReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvApsDiscReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnOpenInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enNegoSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;



    enNegoSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);

    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnOpenInd,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enNegoSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD  == enSessionType))
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND);

        enTriggerScene  = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();
        if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN == enTriggerScene)
        {
            CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);
        }

        /* �����EHSM�������󣬸�EHSMֱ�ӻظ�EHSM_HSM_RSLT_SESSION_NOT_EXIST���������ǰ����Ľ������� */
        ulHsmEventType = CNAS_BuildEventType(UEPS_PID_EHSM, (VOS_UINT16)ID_EHSM_HSM_CONN_EST_REQ);

        ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

        if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
        {
            CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);

            CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
        }

        /* �����page����������Ϊpage�Ľ������󲻳ɹ������ø�aps/ehsm����ind���������ǰ����Ľ������� */
        ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSP, (VOS_UINT16)ID_CAS_CNAS_HRPD_PAGE_IND);

        ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

        if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
        {
            CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
        }

        CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);

        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

        CNAS_HSM_SndCasHrpdConnCloseReq();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,
                            TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND_LEN);

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enNegoSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;

    enNegoSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);

    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_ConnMnmt_WaitConnCloseInd,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enNegoSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD  == enSessionType))
    {
        CNAS_HSM_SetAbortFlag_ConnMnmt(VOS_TRUE);
        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_QuitFsmConnMnmtReq
Description     :   Connetion managment procedure quit process
Input parameters:   enRslt---------------Conn Managment quit result
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-06-09
    Author         : m00312079
    Modify content : Create

2)  ��    ��       : 2015��08��20��
    ��    ��       : t00323010
    �޸�����       : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_HSM_QuitFsmConnMnmtReq(
    CNAS_HSM_CONN_MNMT_RESULT_ENUM_UINT8                 enRslt
)
{
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;

    enTriggerScene = CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt();

    /* reset connetion manament context info */
    CNAS_HSM_InitConnMnmtFsmCtx(CNAS_HSM_GetConnMnmtFsmCtxAddr());

    /* back to the initial substate */
    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_VACANT);

    if (CNAS_HSM_CONN_MNMT_TRIGGER_BUTT == enTriggerScene)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_QuitFsmConnMnmtReq, ConnMnmt trigger scene is BUTT!");
    }

    (VOS_VOID)CNAS_HSM_SndInternalConnMnmtResultInd(enRslt, enTriggerScene);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
