

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmUatiRequest.h"
#include "nas_cttf_hrpd_rsnp_pif.h"
#include "nas_cttf_hrpd_rmac_ctrl_pif.h"
#include "CnasHsmCtx.h"
#include "CnasHsmEncode.h"
#include "CnasHsmDecode.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmSndTtf.h"
#include "cttf_hrpd_rmac_data_status_pif.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmSndHsd.h"
#include "CnasHsmComFunc.h"
#include "CnasMntn.h"
#include "CnasHsmMntn.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmSndAs.h"
#include "CnasHsmProcNvim.h"
#include "CnasTimerMgmt.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_UATI_REQUEST_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

CNAS_HSM_SCP_FAIL_REASON_MAP_UATI_FAIL_REASON_STRU g_astHsmScpFailReasonMapUatiFailReasonTbl[] =
{
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_FAILURE,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NEG_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_EXPIRED,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_AN_EXP,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_FAIL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_FAIL,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_GENERAL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_NW_BUSY,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_AUTH_BILL_FAIL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_PREF_CHAN_NOT_AVAIL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_PERSONALITY_INVALID,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_PERS_INVALID,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_RSP_EXPIRED,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_RSP_EXP,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_MSG_FAIL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_MSG_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_GAUP_FAIL,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_IRAT_TO_LTE,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_IRAT_TO_LTE,
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF,
        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NO_RF,
    },
};


/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*****************************************************************************
Function Name   :   CNAS_HSM_RcvInterUatiReq_UATIRequest_Init
Description     :   handle msg ID_CNAS_HSM_HSM_UATI_REQ in setup state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED--------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED----the current event need to further process

Modify History  :
1)  Date           : 2015-02-07
    Author         : y00174758
    Modify content : Create
2)  Date           : 2015-05-29
    Author         : y00346957
    Modify content : wait mac txended -> wait snp data cnf
3)  Date           : 2015-11-27
    Author         : m00312079
    Modify content : DTS2015111102189:����C.S0024Э��Ҫ��UATI reqֻ������AC�Ϸ��ͣ�CNAS����ӱ���
4)  Date           : 2016-01-05
    Author         : w00351686
    Modify content : DTS2015110200394 del UatiComplete SubState modify
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvInterUatiReq_UATIRequest_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_UATI_REQ_STRU                             *pstUatiReq;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;

    pstUatiReq  = (CNAS_HSM_HSM_UATI_REQ_STRU *)pstMsg;

    if (CNAS_HSM_UATI_REQ_TRIGGER_BY_AT == pstUatiReq->enTriggerReason)
    {
        if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_CONN == CNAS_HSM_GetHrpdConvertedCasStatus())
        {
            enMainState          = CNAS_HSM_GetCurrMainState();

            if (CNAS_HSM_L1_STA_OPEN != enMainState)
            {
                 CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvInterUatiReq_UATIRequest_Init: main state is not open state when conn exist");
            }

            /* ���AC�ŵ���������ֱ���˳�״̬�����ȴ�����ֱ��ָ��UATI assignment */
            CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_CANCEL,
                                    CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
        }
        else
        {
            /* �ܹ�����UATI���̿϶���������ģ������ߵ������֧CAS��״̬�϶�ΪIDLE���϶�������INIT */
            CNAS_HSM_SndUatiReqMsg_UatiReq();

            CNAS_HSM_VoteExitSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_UATI_REQ_PROCEDURE);

            CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF);
            CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);
        }

    }
    else
    {
        CNAS_HSM_SndUatiCmplMsg();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC, CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;

}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf
Description     :   handle msg ID_CTTF_CNAS_HRPD_SNP_DATA_CNF in setup state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED--------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED----the current event need to further process

Modify History  :
1)  Date           : 2015-02-07
    Author         : y00174758
    Modify content : Create
2)  Date           : 2015-05-29
    Author         : y00346957
    Modify content : wait mac txended -> wait snp data cnf
3)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log disacrd snp data cnf info
4)  Date           : 2015-11-27
    Author         : m00312079
    Modify content : DTS2015111102189:����C.S0024Э��Ҫ��UATI reqֻ������AC�Ϸ��ͣ�CNAS����ӱ���
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU                       *pstSnpDataCnf;
    VOS_UINT16                                              usUatiReqOpId;
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION              unDiscardMsgReason;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enCovertedCasStatus;

    pstSnpDataCnf   = (CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU *)pstMsg;
    usUatiReqOpId   = CNAS_HSM_GetUatiReqSnpDataReqOpId();

    unDiscardMsgReason.stDiscardSnpDataCnfReason.enMainState    = CNAS_HSM_GetCurrMainState();
    unDiscardMsgReason.stDiscardSnpDataCnfReason.enSubState     = CNAS_HSM_GetCurrSubState();
    unDiscardMsgReason.stDiscardSnpDataCnfReason.usRcvOpId      = pstSnpDataCnf->usOpId;
    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId      = usUatiReqOpId;

    /* If OpId not match, this message is not as expected, ignore it */
    if (usUatiReqOpId != pstSnpDataCnf->usOpId)
    {
        CNAS_HSM_LogDiscardMsgInfo(CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ERROR_SNP_DATA_CNF, &unDiscardMsgReason);

        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf: OpId not as expected");

        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    if (CTTF_HRPD_SNP_RLST_SUCC == pstSnpDataCnf->enRslt)
    {

        CNAS_HSM_ResetUATIReqFailedCnt();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN, CNAS_HSM_GetWaitUatiAssignTimerLen_UatiReq());

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_ASSIGN);
    }
    else
    {
        if (CTTF_HRPD_SNP_DATA_FAIL_REASON_AC_CHANNEL_NOT_EXIST == pstSnpDataCnf->enFailReason)
        {
            enMainState          = CNAS_HSM_GetCurrMainState();

            if (CNAS_HSM_L1_STA_OPEN != enMainState)
            {
                 CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf: main state is not open state when conn exist");
            }

            /* ���AC�ŵ���������ֱ���˳�״̬�����ȴ�����ֱ��ָ��UATI assignment */
            CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_CANCEL,
                                    CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_IncreaseUATIReqFailedCnt();

        if (CNAS_HSM_GetUATIReqFailedCnt() >= CNAS_HSM_UAIT_REQ_FAILED_MAX_CNT)
        {
            /* ����Session deactiveԭ��ֵ */
            CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                    CNAS_HSM_UATI_REQUEST_FAIL_REASON_REACH_MAX_CNT);
        }
        else
        {
            /* �������ӱ���,��ֹCAS��Ϣʱ���Ӱ��,���֮ǰ���������ﲻ������,�ȴ�
               HSD����פ�������½���Э�� */

            enCovertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

            if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enCovertedCasStatus)
            {
                CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                        CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);

                return CNAS_HSM_FSM_EVENT_HANDLED;
            }

            if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_CONN == enCovertedCasStatus)
            {
                enMainState          = CNAS_HSM_GetCurrMainState();

                if (CNAS_HSM_L1_STA_OPEN != enMainState)
                {
                     CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvInterUatiReq_UATIRequest_Init: main state is not open state when conn exist");
                }

                /* ���AC�ŵ���������ֱ���˳�״̬�����ȴ�����ֱ��ָ��UATI assignment */
                CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_CANCEL,
                                        CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

                return CNAS_HSM_FSM_EVENT_HANDLED;
            }

            CNAS_HSM_SndUatiReqMsg_UatiReq();
            CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiReqSnpDataCnf: timer out");

    CNAS_HSM_IncreaseUATIReqFailedCnt();

    if (CNAS_HSM_GetUATIReqFailedCnt() >= CNAS_HSM_UAIT_REQ_FAILED_MAX_CNT)
    {
        /* ����Session deactiveԭ��ֵ */
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_REACH_MAX_CNT);
    }
    else
    {
        /* �������ӱ���,��ֹCAS��Ϣʱ���Ӱ��,���֮ǰ���������ﲻ������,�ȴ�
           HSD����פ�������½���Э�� */
        if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
        {
            CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_SndUatiReqMsg_UatiReq();
        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_OFF);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstSnpDataInd;
    VOS_UINT32                          ulRslt;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU *)pstMsg;

    ulRslt = CNAS_HSM_FSM_EVENT_NOT_HANDLED;

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == pstSnpDataInd->enProtocolType)
    {
        ulRslt = CNAS_HSM_ProcAmpMsg_UATIRequest_WaitUATIAssign(pstSnpDataInd);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign: enProtocolType not as expected");
    }

    return ulRslt;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitUATIAssignTimerExpire_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    VOS_UINT8                                               ucUatiReqMaxTimes;
    VOS_UINT8                                               ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;

    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitUATIAssignTimerExpire_UatiReq_WaitUatiAssign: timer out");

    enMainState          = CNAS_HSM_GetCurrMainState();
    if  (CNAS_HSM_L1_STA_OPEN == enMainState)
    {
        ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen = CNAS_HSM_GetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen();

        /* uati req����ʹ���Ӧ������һ�η��� */
        ucUatiReqMaxTimes = ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen + 1;
    }
    else
    {
        ucUatiReqMaxTimes = CNAS_HSM_UATI_ASSIGN_TIMEOUT_MAX_CNT;
    }

    CNAS_HSM_IncreaseUATIAssignTimerExpiredCnt();

    if (CNAS_HSM_GetUATIAssignTimerExpiredCnt() >= ucUatiReqMaxTimes)
    {
        /* ����Session deactiveԭ��ֵ */
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_REACH_MAX_CNT);
    }
    else
    {

        /* �������ӱ���,��ֹCAS��Ϣʱ���Ӱ��,���֮ǰ���������ﲻ������,�ȴ�
            HSD����פ�������½���Э�� */
        if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
        {
            CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_ResetUATIReqFailedCnt();

        CNAS_HSM_SndUatiReqMsg_UatiReq();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_OFF);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

#if 0

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU                       *pstCttfSnpDataCnf;
    VOS_UINT16                                              usUatiCmplOpId;
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION              unDiscardMsgReason;

    pstCttfSnpDataCnf   = (CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU *)pstMsg;
    usUatiCmplOpId      = CNAS_HSM_GetUatiCmplSnpDataReqOpId();

    unDiscardMsgReason.stDiscardSnpDataCnfReason.enMainState    = CNAS_HSM_GetCurrMainState();
    unDiscardMsgReason.stDiscardSnpDataCnfReason.enSubState     = CNAS_HSM_GetCurrSubState();
    unDiscardMsgReason.stDiscardSnpDataCnfReason.usRcvOpId      = pstCttfSnpDataCnf->usOpId;
    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId      = usUatiCmplOpId;

    if (usUatiCmplOpId == pstCttfSnpDataCnf->usOpId)
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }
    else
    {
        CNAS_HSM_LogDiscardMsgInfo(CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ERROR_SNP_DATA_CNF, &unDiscardMsgReason);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiCmplSnpDataCnf: timer out");

    /* UATIComlete�����SNP_DATA_CNF������ʱ����ʱ�����ճɹ����� */
    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    /* UATI����ȴ�complete��SETUP�£�����ʧ�ܴ���
        OPEN�£����ճɹ�������ʱ�˳�����Ҫ����deactive���� */
    if (CNAS_HSM_L1_STA_SETUP == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_OFF);
    }
    else
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}
#endif


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SUSPEND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_SAVE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SUSPEND);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_SAVE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

#if 0

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    /* Because Setup State have no valid session, and the UATI is cannot be used after quit Slave State,
       So we consider this procedure is fail though we have rcv valid and fresh UATIAssignment */
    if (CNAS_HSM_L1_STA_SETUP == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SUSPEND);
    }
    else
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    /* Because Setup State have no valid session, and the UATI is cannot be used after quit Slave State,
       So we consider this procedure is fail though we have rcv valid and fresh UATIAssignment */
    if (CNAS_HSM_L1_STA_SETUP == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_SAVE);
    }
    else
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}
#endif

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiReqSnpDataCnf
Description     :   process the hsd OverHead message in UATIRequst WaitSnpDataCnf substate
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED--------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED----the current event need to further process

Modify History  :
1)  Date           : 2015-05-30
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-12-31
    Author         : m00312079
    Modify content : DTS2015123108077:UATI���¹����У����UE���˵�ԭС�������˳�UATI��������
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_UATI_INFO_STRU            *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU        *pstHprdSysInfo;
    VOS_UINT8                           ucQuotient;
    VOS_UINT8                           ucRemainder;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLeftMask;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();
    pstUatiInfo       = CNAS_HSM_GetUatiInfoAddr();

    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    /* C.S0024-A_v3.0 7.3.7.1.6.1 the access terminal shall disable T_ADMPATResponse if following conditions is true:
        1:the UATISubnetMask is equal to the SubnetMask of the sector in the active set, and
        2:the result of bitwise logical AND of the UATI and its subnet mask specified by
          UATISubnetMask is the same from the result of bitwise logical AND of SectorID and
          its subnet mask specified by SubnetMask(where SectorID and SubnetMask correspond to
          the sector in the active set) */

    /* Condition 1: */
    if (pstHprdSysInfo->ucSubNetMask == pstUatiInfo->ucUATISubnetMask)
    {
        /* Condition 2: */
        ucQuotient  = (pstHprdSysInfo->ucSubNetMask) / CNAS_HSM_BIT_LEN_PER_BYTE;
        ucRemainder = (pstHprdSysInfo->ucSubNetMask) % CNAS_HSM_BIT_LEN_PER_BYTE;

        for (ucLoop = 0; ucLoop < ucQuotient; ucLoop++)
        {
            /* pstUatiInfo->aucCurUATI[ucLoop] & 0xFF is equal to pstUatiInfo->aucCurUATI[ucLoop] */
            if ((pstUatiInfo->aucCurUATI[ucLoop])
             != (pstHprdSysInfo->aucSectorId[ucLoop]))
            {
                return CNAS_HSM_FSM_EVENT_HANDLED;
            }
        }

        if (0 == ucRemainder)
        {
           CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

           CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                   CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

           return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        ucLeftMask = (VOS_UINT8)(((VOS_UINT32)1) << ucRemainder);
        ucLeftMask -= 1;
        ucLeftMask = (VOS_UINT8)(((VOS_UINT32)ucLeftMask) << (CNAS_HSM_BIT_LEN_PER_BYTE - ucRemainder));

        if ((pstUatiInfo->aucCurUATI[ucLoop] & ucLeftMask)
         != (pstHprdSysInfo->aucSectorId[ucLoop] & ucLeftMask))
        {
            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

        return CNAS_HSM_FSM_EVENT_HANDLED;

    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiAssign
Description     :   process the hsd PowerSaveReq message in WaitUATIAssign substate
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED--------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED----the current event need to further process

Modify History  :
1)  Date           : 2015-05-30
    Author         : m00312079
    Modify content : Create

2.  ��    ��   : 2015��08��24��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_UATI_INFO_STRU            *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU        *pstHprdSysInfo;
    VOS_UINT8                           ucQuotient;
    VOS_UINT8                           ucRemainder;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLeftMask;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();
    pstUatiInfo       = CNAS_HSM_GetUatiInfoAddr();

    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    /* C.S0024-A_v3.0 7.3.7.1.6.1 the access terminal shall disable T_ADMPATResponse if following conditions is true:
        1:the UATISubnetMask is equal to the SubnetMask of the sector in the active set, and
        2:the result of bitwise logical AND of the UATI and its subnet mask specified by
          UATISubnetMask is the same from the result of bitwise logical AND of SectorID and
          its subnet mask specified by SubnetMask(where SectorID and SubnetMask correspond to
          the sector in the active set) */

    /* Condition 1: */
    if (pstHprdSysInfo->ucSubNetMask == pstUatiInfo->ucUATISubnetMask)
    {
        /* Condition 2: */
        ucQuotient  = (pstHprdSysInfo->ucSubNetMask) / CNAS_HSM_BIT_LEN_PER_BYTE;
        ucRemainder = (pstHprdSysInfo->ucSubNetMask) % CNAS_HSM_BIT_LEN_PER_BYTE;

        for (ucLoop = 0; ucLoop < ucQuotient; ucLoop++)
        {
            /* pstUatiInfo->aucCurUATI[ucLoop] & 0xFF is equal to pstUatiInfo->aucCurUATI[ucLoop] */
            if ((pstUatiInfo->aucCurUATI[ucLoop])
             != (pstHprdSysInfo->aucSectorId[ucLoop]))
            {
                return CNAS_HSM_FSM_EVENT_HANDLED;
            }
        }

        if (0 == ucRemainder)
        {
           CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

           CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                   CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

           return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        ucLeftMask = (VOS_UINT8)(((VOS_UINT32)1) << ucRemainder);
        ucLeftMask -= 1;
        ucLeftMask = (VOS_UINT8)(((VOS_UINT32)ucLeftMask) << (CNAS_HSM_BIT_LEN_PER_BYTE - ucRemainder));

        if ((pstUatiInfo->aucCurUATI[ucLoop] & ucLeftMask)
         != (pstHprdSysInfo->aucSectorId[ucLoop] & ucLeftMask))
        {
            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

        return CNAS_HSM_FSM_EVENT_HANDLED;

    }

   return CNAS_HSM_FSM_EVENT_HANDLED;
}

#if 0

VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}
#endif


VOS_VOID CNAS_HSM_SndUatiReqMsg_UatiReq(VOS_VOID)
{
    VOS_UINT8                                              *pucUATIReqMsgBuf = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgBufBitLen;
    VOS_UINT16                                              usMsgBufByteLen;
    VOS_UINT8                                               ucTransId;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;
    VOS_UINT16                                              usOpId;

    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstPubRcvATIList;


    usMsgBufByteLen = CNAS_HSM_UATI_REQ_MSG_OCTET_LEN;

    /* first alloc UATI request message buffer */
    pucUATIReqMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgBufByteLen);

    if (VOS_NULL_PTR == pucUATIReqMsgBuf)
    {
        return;
    }

    ucTransId = CNAS_HSM_GetUATITransId();
    CNAS_HSM_IncreaseUATITransId();

    NAS_MEM_SET_S(pucUATIReqMsgBuf, usMsgBufByteLen, 0, usMsgBufByteLen);

    /* Encode UATIRequest message */
    usMsgBufBitLen   = 0;
    CNAS_HSM_EncodeUATIReq((VOS_VOID *)&ucTransId,
                            &usMsgBufBitLen,
                            pucUATIReqMsgBuf);

    if (0 == usMsgBufBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);

        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndUatiReqMsg_UatiReq: After encode usMsgBitLen is 0");

        PS_MEM_FREE(UEPS_PID_HSM, pucUATIReqMsgBuf);

        return;
    }
    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_REQ,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBufBitLen,
                          pucUATIReqMsgBuf);

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(stSnpDataReqHeader));


    /* C.S0024-A_v3: 7.3.7.1.2 UATIAssignment Message Validation
    --------------------------------------------------------------------------------------------
    The access terminal shall initialize a receive pointer for the UATIAssignment message validation,
    V(R), to 255 when it sends a UATIRequest message and there exist an entry in the ReceiveATIList list
    whose ATIType field is equal to "11" (i.e., RATI).
    */

    pstPubRcvATIList    = CNAS_HSM_GetReceivedATIListAddr();

    if (CNAS_HSM_ATI_TYPE_RATI == pstPubRcvATIList->astATIEntry[1].enATIType)
    {
        /* Initialize receive pointer value for sequence number validation */
        CNAS_HSM_SetCurrUATIAssignMsgSeqNum(CNAS_HSM_UATI_ASSIGN_MSG_SEQ_NUM_INIT_VALUE);
    }

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC,
                                           CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT,
                                           CNAS_HSM_MSG_PRIORITY_UATI_REQ,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBufBitLen,
                                  pucUATIReqMsgBuf);

    CNAS_HSM_SaveUatiReqSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucUATIReqMsgBuf);
}

#if 0

VOS_VOID CNAS_HSM_SndUatiCmplMsg_UatiReq(VOS_VOID)
{
    VOS_UINT8                                              *pucUATICmpMsgBuf = VOS_NULL_PTR;
    CNAS_HSM_UATI_INFO_STRU                                *pstGlobalUait    = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgBufBitLen;
    VOS_UINT16                                              usMsgBufByteLen;
    CNAS_HSM_UATI_COMP_MSG_STRU                             stUaitCmpInput;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;

    VOS_UINT16                                              usOpId;

    pstGlobalUait = &(CNAS_HSM_GetSessionCtrlInfoAddr()->stUATIInfo);

    /* first alloc uati complete message */
    usMsgBufByteLen = CNAS_HSM_GET_UATI_COMPLETE_MSG_OCTET_LEN(pstGlobalUait->ucOldUATILen);

    pucUATICmpMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgBufByteLen);

    if (VOS_NULL_PTR == pucUATICmpMsgBuf)
    {
        return;
    }

    NAS_MEM_SET_S(pucUATICmpMsgBuf, 0, usMsgBufByteLen);

    NAS_MEM_SET_S(&stUaitCmpInput, 0, sizeof(stUaitCmpInput));

    /* Fullfill UATIComplte input paramters, C.S0024 7.3.7.2.3 UAIComplete */
    stUaitCmpInput.ucMsgSeq        = CNAS_HSM_GetCurrUATIAssignMsgSeqNum();
    stUaitCmpInput.ucOldUATILen    = pstGlobalUait->ucOldUATILen;

    NAS_MEM_CPY_S(stUaitCmpInput.aucOldUATI, pstGlobalUait->aucOldUATI, CNAS_HSM_UATI_OCTET_LENGTH);

    /* Encode UATIComplete message */
    usMsgBufBitLen = 0;
    CNAS_HSM_EncodeUATIComplete(&stUaitCmpInput,
                                &usMsgBufBitLen,
                                pucUATICmpMsgBuf);
    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_COMPLETE,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBufBitLen,
                          pucUATICmpMsgBuf);

    if (0 == usMsgBufBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndUatiCmplMsg_UatiReq: After encode usMsgBitLen is 0");

        PS_MEM_FREE(UEPS_PID_HSM, pucUATICmpMsgBuf);

        return;
    }

    NAS_MEM_SET_S(&stSnpDataReqHeader, 0, sizeof(stSnpDataReqHeader));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_RELIABLE,
                                           CNAS_HSM_MSG_PRIORITY_UATI_COMP,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBufBitLen,
                                  pucUATICmpMsgBuf);

    CNAS_HSM_SaveUatiCmplSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucUATICmpMsgBuf);
}
#endif


VOS_VOID CNAS_HSM_QuitFsmUatiReq(
    CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8                 enRslt,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enFailReason
)
{
    /* ��״̬�����Է�Ϊ���ֳ�����һ��������UATI����ɹ���һ����UATI����ʧ��
        �ɹ��˳�����: �ᷢ��UATIComplete��Ϣ, �˳�״̬����ʱ����Ҫ����session end notify
        ʧ���˳�����: UATI����ʧ��, ��Ҫ����session end notify */
    if (CNAS_HSM_UATI_REQUEST_RESULT_FAIL == enRslt)
    {
        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_UATI_REQ_PROCEDURE);

    /* reset UATI request context info */
    CNAS_HSM_InitUATIReqFsmCtx(CNAS_HSM_GetUATIRequestFsmCtxAddr());

    /* back to the initial substate */
    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_VACANT);

    CNAS_HSM_SndInternalUATIRequestResultInd(enRslt, enFailReason);
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

#if 0

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    if (CNAS_HSM_L1_STA_SETUP == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);
    }
    else
    {
        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;
    VOS_UINT8                                               ucMsgType;

    pstSnpDataInd  = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU*)pstMsg;

    enProtocolType = pstSnpDataInd->enProtocolType;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        if (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN == ucMsgType)
        {
            CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

            /* just cache the message */
            CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
        }

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }
    else
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }
}


VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsgInd;
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason;

    pstMsgInd = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)pstMsg;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    switch (pstMsgInd->enScene)
    {
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_KEEP_ALIVE_EXP;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP:
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND:

            enUatiFailReason = CNAS_HSM_ConvertScpFailReasonToUatiFailReason(
                                                         pstMsgInd->stSessionNegRsltInfo.enResult);

            if (PS_TRUE == pstMsgInd->stSessionNegRsltInfo.enProtocolTypeVaildFlag)
            {
                CNAS_HSM_SetScpActFailProcType(pstMsgInd->stSessionNegRsltInfo.usProtocolType);
                CNAS_HSM_SetScpActFailProcSubtype(pstMsgInd->stSessionNegRsltInfo.usProtocolSubType);
            }

            break;

        default:

            return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL, enUatiFailReason);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}
#endif

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiReqSnpDataCnf
Description     :   Process the hsm internal session close  message in wait snp data cnf state
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-06-03
    Author         : y00174758
    Modify content : Create
2)  Date           : 2016-01-25
    Author         : w00351686
    Modify content : DTS2016011700511:��ǰ��������OHM��Ϣ�����������Ϣ�������������෢��session close
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsgInd;
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason;

    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    /* �����������OHM��Ϣ������������е�OHM��Ϣ����Ϊ�����ڴ���session close ind��ʱ������½�����������,
        �˴����������OHM��Ϣ��������̬������ʱ���������෢������session close */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
    }

    pstMsgInd = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)pstMsg;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    switch (pstMsgInd->enScene)
    {
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_KEEP_ALIVE_EXP;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP:
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND:

            enUatiFailReason = CNAS_HSM_ConvertScpFailReasonToUatiFailReason(
                                                         pstMsgInd->stSessionNegRsltInfo.enResult);

            if (PS_TRUE == pstMsgInd->stSessionNegRsltInfo.enProtocolTypeVaildFlag)
            {
                CNAS_HSM_SetScpActFailProcType(pstMsgInd->stSessionNegRsltInfo.usProtocolType);
                CNAS_HSM_SetScpActFailProcSubtype(pstMsgInd->stSessionNegRsltInfo.usProtocolSubType);
            }

            break;

        default:

            return CNAS_HSM_FSM_EVENT_HANDLED;

    }

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL, enUatiFailReason);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiAssign
Description     :   Process hsm internal session close in wait uati assign state
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-06-03
    Author         : y00174758
    Modify content : Create
2)  Date           : 2016-01-25
    Author         : w00351686
    Modify content : DTS2016011700511:��ǰ��������OHM��Ϣ�����������Ϣ�������������෢��session close
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsgInd;
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason;

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

    pstMsgInd = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)pstMsg;

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    switch (pstMsgInd->enScene)
    {
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_KEEP_ALIVE_EXP;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP:
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT:

            enUatiFailReason = CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND:

            enUatiFailReason = CNAS_HSM_ConvertScpFailReasonToUatiFailReason(
                                                         pstMsgInd->stSessionNegRsltInfo.enResult);

            if (PS_TRUE == pstMsgInd->stSessionNegRsltInfo.enProtocolTypeVaildFlag)
            {
                CNAS_HSM_SetScpActFailProcType(pstMsgInd->stSessionNegRsltInfo.usProtocolType);
                CNAS_HSM_SetScpActFailProcSubtype(pstMsgInd->stSessionNegRsltInfo.usProtocolSubType);
            }

            break;

        default:

            return CNAS_HSM_FSM_EVENT_HANDLED;

    }

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL, enUatiFailReason);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_ProcAmpMsg_UATIRequest_WaitUATIAssign
Description     :   Process the AMP message in uati request wait uati assign
Input parameters:   CTTF_CNAS_HRPD_SNP_DATA_IND_STRU    *pstSnpDataInd
Outout parameters:  None
Return Value    :   VOS_UINT8;

Modify History  :
1)  Date           : 2015-05-31
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-06-08
    Author         : y00346957
    Modify content : 1.UATI assign�ɹ���Ӧ��ֱ���˳�UATI״̬�����ǽ�״̬�л���uati comp wait snp data cnf
                     2.ֹͣ��ʱ��TI_CNAS_HSM_WAIT_UATI_ASSIGNӦ���ڴ���UATI����֮ǰ
3)  Date           : 2016-01-05
    Author         : w00351686
    Modify content : DTS2015110200394 del UatiComplete SubState modify
*****************************************************************************/
VOS_UINT8 CNAS_HSM_ProcAmpMsg_UATIRequest_WaitUATIAssign(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
)
{
    VOS_UINT8                                               ucMsgType;
    CNAS_HSM_UATI_ASSIGN_MSG_STRU                           stUatiAssignMsg;
    CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32                  ulDecodeRslt;
    VOS_UINT8                                               ucIsUatiAssignValidAndFresh;

    ucMsgType = CNAS_HSM_AMP_MESSAGE_TYPE_BUTT;

    ulDecodeRslt = CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                                          pstSnpDataInd->stMsgData.aucMsgData,
                                          &ucMsgType);

    if ((CNAS_HSM_DECODE_SUCCESS           != ulDecodeRslt)
     || (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN != ucMsgType))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcAmpMsgFromTtf_UATIRequest_WaitUATIAssign: Decode msg type fail or ucMsgType not as expected");

        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    NAS_MEM_SET_S(&stUatiAssignMsg, sizeof(stUatiAssignMsg), 0, sizeof(stUatiAssignMsg));

    ulDecodeRslt = CNAS_HSM_DecodeUATIAssignment(pstSnpDataInd->stMsgData.aucMsgData,
                                                 pstSnpDataInd->stMsgData.usMsgBitLen,
                                                 (VOS_VOID *)&stUatiAssignMsg);
    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_ASSIGN,
                          UEPS_PID_HSM,
                          (VOS_UINT32)pstSnpDataInd->stMsgData.usMsgBitLen,
                          pstSnpDataInd->stMsgData.aucMsgData);
    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcAmpMsgFromTtf_UATIRequest_WaitUATIAssign: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* check the uati assign valid&fresh */
    ucIsUatiAssignValidAndFresh = CNAS_HSM_IsUatiAssignValidAndFresh(&stUatiAssignMsg);

    if (VOS_FALSE == ucIsUatiAssignValidAndFresh)
    {
        /* just discard the message and still wait uati assignment */
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_HandleUatiAssignMsg(&stUatiAssignMsg);

    CNAS_HSM_SndUatiCmplMsg();

    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC, CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* just cache the message */
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiReqSnpDataCnf
Description     :   process ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND msg in substate
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-05-29
    Author         : x00314862
    Modify content : Create
2)  Date           : 2015-08-15
    Author         : y00307564
    Modify content : DTS2015081302622�޸�
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enLastSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                  stHsmHrpdPaRatModeNtf;
    VOS_UINT32                                              ulHsmEventType;

    enLastSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);
    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_UATIRequest_WaitSnpDataCnf,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD
       need fallback
     */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enLastSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType))
    {

        /* ��״̬�յ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF֮�󣬽���÷�֧�󣬻�ִ��deactive���̣�
           ��������inactive����Ҫ���½���uati��session�������̣������Ҫ����һ����Ϣ��inactive
           ̬�������ǣ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF�ڸ���״̬�¶������յ�������inactive̬��
           ������Ϣ��hsmӦ�ö�������Ϣ��������Ҫ������ת��Ϊһ���ڲ���Ϣ���ٽ��л��� */
        CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg(pstPaRatModeNtf, &stHsmHrpdPaRatModeNtf);

        ulHsmEventType = CNAS_BuildEventType(stHsmHrpdPaRatModeNtf.ulSenderPid, (VOS_UINT16)stHsmHrpdPaRatModeNtf.enMsgId);

        /* just cache the message */
        CNAS_HSM_SaveCacheMsg(ulHsmEventType, &stHsmHrpdPaRatModeNtf);

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_PA_MODE_NTF);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

     /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* just cache the message */
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiAssign
Description     :   process ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND msg in substate
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-05-29
    Author         : x00314862
    Modify content : Create
2)  Date           : 2015-08-15
    Author         : y00307564
    Modify content : DTS2015081302622�޸�
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enLastSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                  stHsmHrpdPaRatModeNtf;
    VOS_UINT32                                              ulHsmEventType;

    enLastSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);
    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_UATIRequest_WaitUATIAssign,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD
       need fallback
     */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enLastSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD  == enSessionType))
    {

        /* ��״̬�յ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF֮�󣬽���÷�֧�󣬻�ִ��deactive���̣�
           ��������inactive����Ҫ���½���uati��session�������̣������Ҫ����һ����Ϣ��inactive
           ̬�������ǣ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF�ڸ���״̬�¶������յ�������inactive̬��
           ������Ϣ��hsmӦ�ö�������Ϣ��������Ҫ������ת��Ϊһ���ڲ���Ϣ���ٽ��л��� */
        CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg(pstPaRatModeNtf, &stHsmHrpdPaRatModeNtf);

        ulHsmEventType = CNAS_BuildEventType(stHsmHrpdPaRatModeNtf.ulSenderPid, (VOS_UINT16)stHsmHrpdPaRatModeNtf.enMsgId);

        /* just cache the message */
        CNAS_HSM_SaveCacheMsg(ulHsmEventType, &stHsmHrpdPaRatModeNtf);

        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_UATI_ASSIGN);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_PA_MODE_NTF);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

     /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

#if 0

VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* just cache the message */
    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

    CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                            CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiCmplSnpDataCnf
Description     :   process ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND msg in substate
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-05-29
    Author         : x00314862
    Modify content : Create
2)  Date           : 2015-08-15
    Author         : y00307564
    Modify content : DTS2015081302622�޸�
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enLastSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                  stHsmHrpdPaRatModeNtf;
    VOS_UINT32                                              ulHsmEventType;

    enLastSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);
    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_UATICmpl_WaitSnpDataCnf,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD
       need fallback
     */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enLastSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType))
    {

        /* ��״̬�յ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF֮�󣬽���÷�֧�󣬻�ִ��deactive���̣�
           ��������inactive����Ҫ���½���uati��session�������̣������Ҫ����һ����Ϣ��inactive
           ̬�������ǣ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF�ڸ���״̬�¶������յ�������inactive̬��
           ������Ϣ��hsmӦ�ö�������Ϣ��������Ҫ������ת��Ϊһ���ڲ���Ϣ���ٽ��л��� */
        CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg(pstPaRatModeNtf, &stHsmHrpdPaRatModeNtf);

        ulHsmEventType = CNAS_BuildEventType(stHsmHrpdPaRatModeNtf.ulSenderPid, (VOS_UINT16)stHsmHrpdPaRatModeNtf.enMsgId);

        /* just cache the message */
        CNAS_HSM_SaveCacheMsg(ulHsmEventType, &stHsmHrpdPaRatModeNtf);

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
                                CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

     /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}
#endif



/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCttfHrpdSnpDataInd_UatiReq_WaitUatiReqSnpDataCnf
Description     :   Process the uati assignment message which the AN originate
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-06-11
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029:�ڵ�cttf��snpDataCnfʱ�յ�UATI assingmentͬ����Ϊ��Ч���˳�UATI��������
3)  Date           : 2015-01-05
    Author         : w000351686
    Modify content : DTS2015110200394 del UatiComplete SubState modify
*****************************************************************************/

VOS_UINT32 CNAS_HSM_RcvCttfHrpdSnpDataInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU            *pstSnpDataInd;
    VOS_UINT32                                   ulRslt;
    VOS_UINT8                                    ucMsgType;
    CNAS_HSM_UATI_ASSIGN_MSG_STRU                stUatiAssignMsg;
    CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32       ulDecodeRslt;
    VOS_UINT8                                    ucIsUatiAssignValidAndFresh;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU *)pstMsg;

    ulRslt = CNAS_HSM_FSM_EVENT_NOT_HANDLED;

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == pstSnpDataInd->enProtocolType)
    {
        ucMsgType = CNAS_HSM_AMP_MESSAGE_TYPE_BUTT;

        ulDecodeRslt = CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                                              pstSnpDataInd->stMsgData.aucMsgData,
                                              &ucMsgType);

        if ((CNAS_HSM_DECODE_SUCCESS           != ulDecodeRslt)
         || (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN != ucMsgType))
        {
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcAmpMsgFromTtf_UATIRequest_WaitUATIAssign: Decode msg type fail or ucMsgType not as expected");

            return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
        }

        NAS_MEM_SET_S(&stUatiAssignMsg, sizeof(stUatiAssignMsg), 0, sizeof(stUatiAssignMsg));

        ulDecodeRslt = CNAS_HSM_DecodeUATIAssignment(pstSnpDataInd->stMsgData.aucMsgData,
                                                     pstSnpDataInd->stMsgData.usMsgBitLen,
                                                     (VOS_VOID *)&stUatiAssignMsg);

        CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                              NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_ASSIGN,
                              UEPS_PID_HSM,
                              (VOS_UINT32)pstSnpDataInd->stMsgData.usMsgBitLen,
                              pstSnpDataInd->stMsgData.aucMsgData);

        if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcAmpMsgFromTtf_UATIRequest_WaitUATIAssign: Decode msg content fail");

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        /* check the uati assign valid&fresh */
        ucIsUatiAssignValidAndFresh = CNAS_HSM_IsUatiAssignValidAndFresh(&stUatiAssignMsg);

        if (VOS_FALSE == ucIsUatiAssignValidAndFresh)
        {
            /* just discard the message and still wait uati assignment */
            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        /* �ڵ�cttf��snpDataCnfʱ�յ�UATI assingmentͬ����Ϊ��Ч���˳�UATI�������� */
        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF);

        CNAS_HSM_HandleUatiAssignMsg(&stUatiAssignMsg);

        CNAS_HSM_SndUatiCmplMsg();

        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

        CNAS_HSM_QuitFsmUatiReq(CNAS_HSM_UATI_REQUEST_RESULT_SUCC, CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT);
    }

    return ulRslt;
}



VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsDiscReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetAbortFlag_UatiReq(VOS_TRUE);

    CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_VOID CNAS_HSM_HandleUatiAssignMsg_SetupState(
     CNAS_HSM_UATI_ASSIGN_MSG_STRU                         *pstUatiAssignMsg
)
{
    CNAS_HSM_ATI_RECORD_STRU                               *pstPubTransATI;
    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstPubRcvATIList;
    CNAS_HSM_UATI_INFO_STRU                                *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo;

    /* Update TransmitATI and send to MAC*/
    /* C.S0024 7.3.7.1.5.1: ATIType = '10', ATI = (UATIColorCode | UATI[23:0]) */
    pstPubTransATI                 = CNAS_HSM_GetTransmitATIAddr();
    pstUatiInfo                    = CNAS_HSM_GetUatiInfoAddr();
    pstPubTransATI->enATIType      = CNAS_HSM_ATI_TYPE_UATI;

    pstUatiInfo->ucUATIColorCode   = pstUatiAssignMsg->ucUATIColorCode;
    pstUatiInfo->ucOldUATILen      = pstUatiAssignMsg->ucOldUATILen;

    if (1 == pstUatiAssignMsg->ucSubnetIncluded)
    {/* uati assignment msg include UATI104 and UATI subnetmask field */
        pstUatiInfo->ucUATISubnetMask = pstUatiAssignMsg->ucUATISubnetMask;

        /* UATI = UATI104 | UATI024 */
        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI,
                      sizeof(pstUatiInfo->aucCurUATI),
                      pstUatiAssignMsg->aucUati104,
                      CNAS_HSM_UATI104_OCTET_LENGTH);

        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                      (CNAS_HSM_UATI_OCTET_LENGTH - CNAS_HSM_UATI104_OCTET_LENGTH),
                      pstUatiAssignMsg->aucUati024,
                      CNAS_HSM_UATI024_OCTET_LENGTH);
    }
    else
    {
        pstHrpdSysInfo = CNAS_HSM_GetHrpdSysInfoAddr();

        pstUatiInfo->ucUATISubnetMask = pstHrpdSysInfo->ucSubNetMask;

        /* UATI = sectorID[127:24] | UATI024 */
        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI,
                      sizeof(pstUatiInfo->aucCurUATI),
                      pstHrpdSysInfo->aucSectorId,
                      CNAS_HSM_UATI104_OCTET_LENGTH);

        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                      (CNAS_HSM_UATI_OCTET_LENGTH - CNAS_HSM_UATI104_OCTET_LENGTH),
                      pstUatiAssignMsg->aucUati024,
                      CNAS_HSM_UATI024_OCTET_LENGTH);

    }

    pstPubTransATI->aucATIValue[0] = pstUatiAssignMsg->ucUATIColorCode;
    NAS_MEM_CPY_S(&(pstPubTransATI->aucATIValue[1]),
                  (CNAS_HSM_ATI_VALUE_LENGTH - 1),
                  &(pstUatiAssignMsg->aucUati024[0]),
                  CNAS_HSM_UATI024_OCTET_LENGTH);

    CNAS_HSM_SndMacTransmitAtiNotify(pstPubTransATI);

    /* Update ReciveATIList and send to MAC */
    /* C.S0024 7.3.7.1.5.1 Access Terminal Requirements
      Delete any entry in the ReceiveATIList list whose ATIType is equal to "11" (i.e., RATI).
      Add the following entry to the ReceiveATIList list
      <ATIType = '10', ATI = ATI = (UATIColorCode | UATI[23:0])>
    */

    /* In iteration 8, the second record is RATI, so just overwrite the second record with UATI,
       then RATI is deleted, also UATI is added
    */
    pstPubRcvATIList    = CNAS_HSM_GetReceivedATIListAddr();

    pstPubRcvATIList->ulATIRecordNum            = 2;
    pstPubRcvATIList->astATIEntry[1].enATIType  = CNAS_HSM_ATI_TYPE_UATI;

    pstPubRcvATIList->astATIEntry[1].aucATIValue[0] = pstUatiAssignMsg->ucUATIColorCode;
    NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[1].aucATIValue[1]),
                  (CNAS_HSM_ATI_VALUE_LENGTH - 1),
                  &(pstUatiAssignMsg->aucUati024[0]),
                  CNAS_HSM_UATI024_OCTET_LENGTH);

    CNAS_HSM_SndMacReceiveAtiNotify(pstPubRcvATIList);

}


VOS_VOID CNAS_HSM_HandleUatiAssignMsg_OpenState(
     CNAS_HSM_UATI_ASSIGN_MSG_STRU                         *pstUatiAssignMsg
)
{
    CNAS_HSM_ATI_RECORD_STRU                               *pstPubTransATI;
    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstPubRcvATIList;
    CNAS_HSM_UATI_INFO_STRU                                *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo;
    VOS_UINT32                                              ulAddrTimerLeft;
    VOS_UINT8                                               ucLoop;
    VOS_UINT32                                              ulTimerRunLen;

    /* Update TransmitATI and send to MAC*/
    /* C.S0024 7.3.7.1.5.1: ATIType = '10', ATI = (UATIColorCode | UATI[23:0]) */
    pstPubTransATI                 = CNAS_HSM_GetTransmitATIAddr();
    pstUatiInfo                    = CNAS_HSM_GetUatiInfoAddr();
    pstPubTransATI->enATIType      = CNAS_HSM_ATI_TYPE_UATI;

    pstUatiInfo->ucUATIColorCode   = pstUatiAssignMsg->ucUATIColorCode;
    pstUatiInfo->ucOldUATILen      = pstUatiAssignMsg->ucOldUATILen;

    if (1 == pstUatiAssignMsg->ucSubnetIncluded)/* uati assignment msg include UATI104 and UATI subnetmask field */
    {
        pstUatiInfo->ucUATISubnetMask = pstUatiAssignMsg->ucUATISubnetMask;

        /* UATI = UATI104 | UATI024 */
        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI,
                      sizeof(pstUatiInfo->aucCurUATI),
                      pstUatiAssignMsg->aucUati104,
                      CNAS_HSM_UATI104_OCTET_LENGTH);

        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                      (CNAS_HSM_UATI_OCTET_LENGTH - CNAS_HSM_UATI104_OCTET_LENGTH),
                      pstUatiAssignMsg->aucUati024,
                      CNAS_HSM_UATI024_OCTET_LENGTH);
    }
    else
    {
        pstHrpdSysInfo = CNAS_HSM_GetHrpdSysInfoAddr();

        pstUatiInfo->ucUATISubnetMask = pstHrpdSysInfo->ucSubNetMask;

        /* UATI = sectorID[127:24] | UATI024 */
        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI,
                      sizeof(pstUatiInfo->aucCurUATI),
                      pstHrpdSysInfo->aucSectorId,
                      CNAS_HSM_UATI104_OCTET_LENGTH);

        NAS_MEM_CPY_S(pstUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                      (CNAS_HSM_UATI_OCTET_LENGTH - CNAS_HSM_UATI104_OCTET_LENGTH),
                      pstUatiAssignMsg->aucUati024,
                      CNAS_HSM_UATI024_OCTET_LENGTH);

    }

    pstPubTransATI->aucATIValue[0] = pstUatiAssignMsg->ucUATIColorCode;
    NAS_MEM_CPY_S(&(pstPubTransATI->aucATIValue[1]),
                  (CNAS_HSM_ATI_VALUE_LENGTH - 1),
                  &(pstUatiAssignMsg->aucUati024[0]),
                  CNAS_HSM_UATI024_OCTET_LENGTH);

    CNAS_HSM_SndMacTransmitAtiNotify(pstPubTransATI);

    /* Update ReciveATIList and send to MAC */
    /* C.S0024 7.3.7.1.5.1 Access Terminal Requirements
      Delete any entry in the ReceiveATIList list whose ATIType is equal to "11" (i.e., RATI).
      Add the following entry to the ReceiveATIList list
      <ATIType = '10', ATI = ATI = (UATIColorCode | UATI[23:0])>
    */

    pstPubRcvATIList    = CNAS_HSM_GetReceivedATIListAddr();

    if (CNAS_HSM_MAX_UATI_REC_NUM == pstPubRcvATIList->ulATIRecordNum)
    {
        ulAddrTimerLeft = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSM, TI_CNAS_HSM_ADDRESS_TIMER, 0);

        CNAS_HSM_StopTimer(TI_CNAS_HSM_ADDRESS_TIMER);

        ulTimerRunLen = pstPubRcvATIList->astATIEntry[2].ulAddrTimerLen - ulAddrTimerLeft;

        /* The receive ATI list is full, so we should remove the older ATI form ReceiveATI list */
        for (ucLoop = 1 ; ucLoop < pstPubRcvATIList->ulATIRecordNum - 1; ucLoop++)
        {
            NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[ucLoop]),
                          sizeof(CNAS_HSM_ATI_RECORD_STRU),
                          &(pstPubRcvATIList->astATIEntry[ucLoop + 1]),
                          sizeof(CNAS_HSM_ATI_RECORD_STRU));

            /* update addr timer */
            pstPubRcvATIList->astATIEntry[ucLoop].ulAddrTimerLen -= ulTimerRunLen;
        }

        /* reset the timer */
        pstPubRcvATIList->astATIEntry[1].ulAddrTimerLen = 0;

        /* restart the address timer */
        CNAS_HSM_StartTimer(TI_CNAS_HSM_ADDRESS_TIMER, pstPubRcvATIList->astATIEntry[2].ulAddrTimerLen);
    }
    else
    {
        if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_ADDRESS_TIMER, 0))
        {
            ulAddrTimerLeft = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSM, TI_CNAS_HSM_ADDRESS_TIMER, 0);

            ulTimerRunLen = pstPubRcvATIList->astATIEntry[2].ulAddrTimerLen - ulAddrTimerLeft;

            pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum].ulAddrTimerLen = TI_CNAS_HSM_ADDRESS_TIMER_LEN + ulTimerRunLen;
        }
        else
        {
            pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum].ulAddrTimerLen = TI_CNAS_HSM_ADDRESS_TIMER_LEN;
            CNAS_HSM_StartTimer(TI_CNAS_HSM_ADDRESS_TIMER, TI_CNAS_HSM_ADDRESS_TIMER_LEN);
        }
    }

    if (CNAS_HSM_MAX_UATI_REC_NUM != pstPubRcvATIList->ulATIRecordNum)
    {
        pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum].enATIType  = CNAS_HSM_ATI_TYPE_UATI;

        pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum].aucATIValue[0] = pstUatiAssignMsg->ucUATIColorCode;

        NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum].aucATIValue[1]),
                      (CNAS_HSM_ATI_VALUE_LENGTH - 1),
                      &(pstUatiAssignMsg->aucUati024[0]),
                      CNAS_HSM_UATI024_OCTET_LENGTH);

        pstPubRcvATIList->ulATIRecordNum++;
    }
    else
    {
        pstPubRcvATIList->astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM - 1].enATIType  = CNAS_HSM_ATI_TYPE_UATI;

        pstPubRcvATIList->astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM - 1].aucATIValue[0] = pstUatiAssignMsg->ucUATIColorCode;

        NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM - 1].aucATIValue[1]),
                      (CNAS_HSM_ATI_VALUE_LENGTH - 1),
                      &(pstUatiAssignMsg->aucUati024[0]),
                      CNAS_HSM_UATI024_OCTET_LENGTH);

        /* refresh the addr timer */
        pstPubRcvATIList->astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM - 1].ulAddrTimerLen = TI_CNAS_HSM_ADDRESS_TIMER_LEN;
    }

    CNAS_HSM_SndMacReceiveAtiNotify(pstPubRcvATIList);
}




CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8
CNAS_HSM_ConvertScpFailReasonToUatiFailReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpFailReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;

    ulReasonCnt = sizeof(g_astHsmScpFailReasonMapUatiFailReasonTbl) /
                            sizeof(CNAS_HSM_SCP_FAIL_REASON_MAP_UATI_FAIL_REASON_STRU);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (g_astHsmScpFailReasonMapUatiFailReasonTbl[ulLoop].enScpFailReason
                                                                         == enScpFailReason)
        {
            return g_astHsmScpFailReasonMapUatiFailReasonTbl[ulLoop].enUatiFailReason;
        }
    }

    return CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT;
}


VOS_UINT32 CNAS_HSM_GetWaitUatiAssignTimerLen_UatiReq(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU          *pstWaitUatiAssignTimerLenInfoAddr;
    VOS_UINT32                                              ulWaitUatiAssignTimerLen;

    enMainState          = CNAS_HSM_GetCurrMainState();

    pstWaitUatiAssignTimerLenInfoAddr = CNAS_HSM_GetWaitUatiAssignTimerLenInfoAddr();

    if (CNAS_HSM_L1_STA_SETUP == enMainState)
    {
        ulWaitUatiAssignTimerLen =  pstWaitUatiAssignTimerLenInfoAddr->ucWaitUatiAssignTimerLenInAmpSetup;
    }
    else
    {
        ulWaitUatiAssignTimerLen =  pstWaitUatiAssignTimerLenInfoAddr->ucWaitUatiAssignTimerLenInAmpOpen;
    }

    return (ulWaitUatiAssignTimerLen * CNAS_HSM_SEC_TO_MILLISEC);

}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

