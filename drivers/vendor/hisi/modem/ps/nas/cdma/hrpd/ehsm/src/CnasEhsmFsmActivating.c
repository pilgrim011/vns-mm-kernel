/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmFsmActivating.c
 Author          :
 Version         :
 Date            :   18/05/2015
 Description     :   This file has definition of each message handler in EHSM ACTIVATING FSM.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmFsmActivatingTbl.h"
#include "CnasEhsmMntn.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmFsmActivating.h"
#include "CnasEhsmSndHsm.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmSndAps.h"
#include "CnasEhsmSndEsm.h"
#include "ehsm_hsd_pif.h"
#include "CnasEhsmEncode.h"

/* To Do: Need to add EHSM to APS interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_ACTIVATING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all message handlers in EHSM activating FSM */


VOS_UINT32 CNAS_EHSM_RcvEhsmAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU     *pstAttachReq    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid ;

    pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)pstMsg;

    /* ����PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* After allocating PDNid in EHSM PDN info, need to allocate CID if the entry message reason is initial attach.
        If the entry message reason is hand over attach, get first used cid from LTE pdn info array */
    if (CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH == pstAttachReq->enAttachReason)
    {
        /* ��ʼ��Initial Attach��CidֵΪ0 */
        ucCid = 0;

        /* Need to find valid cid and save sdf param in local pdn info */
        CNAS_EHSM_GetSdfParaAndSaveLocalPdnInfo(ucPdnId, ucCid);
    }
    else
    {
        /* ����HandOver Attach����� */
        /*
            1. ehsm�յ�sync pdn info�󣬸���ctx ��astLtePdnBearInfo�Ƿ�ʹ�ô�Ÿ�pdn info
            ��������ȡʱ��Ҫ���Ȼ�ȡ��Ӧpdn info������ֵ
            2.handoverʱ��ͨ��pdnid��lte pdn info������ֵ���Ȱ�lte pdn info������local ehrpd pdn info�����У������ȡ
            3. cid����ͬpdnidֱ�Ӵ�ctx�е�astLocalPdnBearInfo�ж�ȡ
        */
        CNAS_EHSM_LoadLocalPdnInfoFromLteInfo(ucPdnId, CNAS_EHSM_GetLtePdnIndexWithMinEspbId());
        ucCid = CNAS_EHSM_GetCidByPdnId(ucPdnId);
    }

    /* Save the generated PDNid and CID in activating FSM ctx
        And save the generated CID in EHSM pdn info */
    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, ucCid);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstRconnReq  = VOS_NULL_PTR;

    pstRconnReq = (APS_EHSM_RECONN_REQ_STRU*)pstMsg;

    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    CNAS_EHSM_SetPdnIdCid_Activating(pstRconnReq->ucPdnId, CNAS_EHSM_GetCidByPdnId(pstRconnReq->ucPdnId));

    CNAS_EHSM_SndHsmConnEstReq();
    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstPdnActReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstPdnActReq = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstMsg;

    /* ����PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Save the generated PDNid and CID in activating FSM ctx */
    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, pstPdnActReq->ucCid);

    CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(ucPdnId);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();
        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init
 ��������  : EHSM����״̬������APS Attach����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��25��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_ATTACH_REQ_STRU       *pstAttachReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid ;

    pstAttachReq = (APS_EHSM_PDN_ATTACH_REQ_STRU*)pstMsg;

    /* ����PdnId */
    ucPdnId = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    ucCid = pstAttachReq->ucCid;

    /* ��ȡ����PDN��Ӧ����Ϣ*/
    CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(ucPdnId);

    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, ucCid);

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmPdnSetupReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU   *pstReEstReq = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdnId;

    pstReEstReq = (CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU *)pstMsg;

    /* ����PdnId */
    ucPdnId  = CNAS_EHSM_AllocPdnId();
    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    CNAS_EHSM_SaveCurEntryMsg(ulEventType, pstMsg);

    /* get PDN Info from LTE pdn info And set Cid in local bearer PDN info */
    CNAS_EHSM_LoadLocalPdnInfoFromLteInfo(ucPdnId, (VOS_UINT8)pstReEstReq->ulLtePdnIndex);

    CNAS_EHSM_SetPdnIdCid_Activating(ucPdnId, CNAS_EHSM_GetCidByPdnId(ucPdnId));

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_CONN_EST_CNF_STRU             *pstConnEstCnf   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                     *pstEntryMsg     = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                     *pstCtxAdrr      = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU   *pstRetryInfo    = VOS_NULL_PTR;
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU         *pstAttachReq    = VOS_NULL_PTR;
    VOS_UINT32                              ulConnRetryFlag;
    VOS_UINT8                               ucPdnId;
    VOS_UINT8                               ucCid;

    pstConnEstCnf   = (HSM_EHSM_CONN_EST_CNF_STRU *)pstMsg;
    pstEntryMsg     = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstCtxAdrr      = CNAS_EHSM_GetEhsmCtxAddr();
    pstRetryInfo    = CNAS_EHSM_GetRetryInfo_Activating();
    ucPdnId         = CNAS_EHSM_GetPdnId_Activating();
    ucCid           = CNAS_EHSM_GetCidByPdnId(ucPdnId);
    ulConnRetryFlag = VOS_FALSE;

    /* ֹͣ����������ʱ�� */
    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

    if (EHSM_HSM_RSLT_SUCCESS == pstConnEstCnf->enResult)
    {
        CNAS_EHSM_SetAirLinkExistFlag(VOS_TRUE);
    }

    /* �����ɹ��Ĵ��� */
    if (EHSM_HSM_RSLT_SUCCESS == pstConnEstCnf->enResult)
    {
        CNAS_EHSM_ResetConntRetryTimes_Activating();

        if (CNAS_EHSM_EHRPD_DORMANT_STA == CNAS_EHSM_GetEhrpdState())
        {
            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_ACTIVE_STA);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_SUCCESS, ucPdnId, ucCid);

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_TRUE);

            CNAS_EHSM_QuitFsmL2();

            return VOS_TRUE;
        }

        if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
        {
            /* ���PDN�Ѿ����ڼ�������У����ٷ���Attach_Req/Conn_Req */
            CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(CNAS_CTTF_EHRPD_LINK_CONNECTED);
        }
        else
        {
            if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
            {
                pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

                CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);
            }
            else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
            {
                CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
            }
            else
            {
                CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);
            }

            CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);
        }

        /* Update the currewnt FSM State */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }
    else
    {
        /* ����ʧ�ܵĴ��� */
        ulConnRetryFlag = CNAS_EHSM_IsCommonConnRetryNeeded(pstConnEstCnf->enResult);

        if ((VOS_TRUE == ulConnRetryFlag)
         && (pstRetryInfo->usCurConnEstRetryTimes < pstCtxAdrr->stRetryCtrlInfo.stRetryConnEstInfo.usMaxNoOfRetry))
        {
            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST, pstCtxAdrr->stRetryCtrlInfo.stRetryConnEstInfo.ulExpireTimerLen);
            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT);
        }
        else
        {
            if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
            {
                /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
                CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

                /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
                if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
                {
                    CNAS_EHSM_SndCttfEhrpdDetachInd();
                }
                else
                {
                    CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(ucPdnId);
                }
            }

            CNAS_EHSM_EstPdnFailureHandler_Activating(CNAS_EHSM_MapHsmCauseToAps(pstConnEstCnf->enResult),
                                                      pstEntryMsg->ulEventType);

            if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
             || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
            {
                CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
            }
            else
            {
                CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
            }

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }
    }

    /* ������ʱ�Ĵ��� */
    CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT, pstEntryMsg->ulEventType);

    if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
      ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
    }
    else
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
    }

    CNAS_EHSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvTiWaitConnRetryEst_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* retry time count increse */
    CNAS_EHSM_IncreConntRetryTimes_Activating();

    CNAS_EHSM_SndHsmConnEstReq();

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU      *pstAbortMsg    = VOS_NULL_PTR;

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

    pstAbortMsg = (CNAS_EHSM_EHSM_ABORT_REQ_STRU *)pstMsg;

    /* DORMANT״̬�����½��������� */
    if (CNAS_EHSM_EHRPD_DORMANT_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_SUSPEND_STA);
    }

    CNAS_EHSM_ProcAbortProcedure_Activating(pstAbortMsg->ulEventType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry
 ��������  : ��״̬CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT����
             ����ϢID_CTTF_CNAS_EHRPD_PDN_CONN_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��2��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_CONN_EST_FAIL,
                                                  pstEntryMsg->ulEventType);

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

        CNAS_EHSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry
 ��������  : ��״̬CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT����
             ����ϢID_CTTF_CNAS_EHRPD_ATTACH_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��2��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);
        /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(pStAttachCnf->enErrorCode));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry
 ��������  : ��״̬CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT����
             ����ʱ��TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��2��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                                  pstEntryMsg->ulEventType);

        if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
          ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);
        }
        else
        {
            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry
 ��������  : �ȴ���·�ؽ�ʱ�յ�HSM���͵�Session Info Ind��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstHsmSessionInd = VOS_NULL_PTR;

    pstHsmSessionInd = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    CNAS_EHSM_SetSessionType(pstHsmSessionInd->enSessionType);

    if (EHSM_HSM_SESSION_TYPE_EHRPD == pstHsmSessionInd->enSessionType)
    {
        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CONN_RETRY_EST);

        /* retry time count increse */
        CNAS_EHSM_IncreConntRetryTimes_Activating();

        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

        return VOS_TRUE;
    }
    else
    {
        /* �˴����뷵��VOS_FALSE,��EHRPDģʽ�����ᴦ��ΪAbort���ڲ���Ϣ */
        return VOS_FALSE;
    }
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnSetUpCnf = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo     = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    pstPdnSetUpCnf = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)pstMsg;
    pstPdnInfo     = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[pstPdnSetUpCnf->ucPdnId]);

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

    if (CNAS_CTTF_EHRPD_RSLT_SUCCESS == pstPdnSetUpCnf->enPdnConnRslt)
    {
        /* clean the retry pdn info */
        CNAS_EHSM_InitApnRetryInfo();

        /* update ehrpd local pdn info */
        CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromPdnConnCnf(pstPdnInfo, pstPdnSetUpCnf);

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnActivateCnf(pstPdnInfo->ucCid, EHSM_APS_CAUSE_SUCCESS);

            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_CONNECTED);
        }

        if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsLteHandOverToEhrpdInd(pstPdnSetUpCnf->ucPdnId, EHSM_APS_PDN_OPTION_MODIFIED);

            /* Incase of HAND OVER ATTACH send PDN option as EHSM_ESM_PDN_OPT_CONNECTED */
            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_CONNECTED);

            CNAS_EHSM_ClearLteLocalPdnInfo(pstPdnInfo->ucCid);
        }

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_FALSE);
        CNAS_EHSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_FALSE);

        CNAS_EHSM_PdnSetupFailureHandler_Activating(pstPdnSetUpCnf->ucPdnId, pstPdnSetUpCnf->enErrorCode, &(pstPdnInfo->stApn));
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;
    pstPdnInfo   = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[pStAttachCnf->ucPdnId]);
    pstEntryMsg  = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

    if (CNAS_CTTF_EHRPD_RSLT_SUCCESS == pStAttachCnf->enAttachRslt)
    {
        /* clean the retry pdn info */
        CNAS_EHSM_InitApnRetryInfo();

        CNAS_EHSM_UpdateEhrpdLocalPdnInfoFromAttachCnf(pstPdnInfo, pStAttachCnf);

        /* ����˴�Attach����ʱ�û������Լ������ģ���Ҫ���û��ϱ�Attach Cnf��� */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(pStAttachCnf->ucPdnId, EHSM_APS_CAUSE_SUCCESS);

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_TRUE);
        }
        else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            /* �Զ�������Initial Attach */
            if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pStAttachCnf->enAttachType)
            {
                CNAS_EHSM_SndApsPdnActivateInd(pStAttachCnf->ucPdnId);
            }

            /* LTE֮ǰ�����û�����������ҵ���л���EHRPDʱ����Ҫ��HandOver Attach */
            if (CNAS_CTTF_EHRPD_ATTACH_TYPE_HANDOVER == pStAttachCnf->enAttachType)
            {
                /* ���µ�ǰehrpd��IPV6��ַ��ˢ��ǰ׺ */
                if ((CNAS_EHSM_PDN_TYPE_IPV6 == pstPdnInfo->stPdnAddr.enPdnType)
                 || (CNAS_EHSM_PDN_TYPE_IPV4V6 == pstPdnInfo->stPdnAddr.enPdnType))
                {
                    CNAS_EHSM_SyncEhrpdIpv6PrfixWithLtePdnInfo(pStAttachCnf->ucPdnId);
                }

                CNAS_EHSM_SndApsLteHandOverToEhrpdInd(pStAttachCnf->ucPdnId, EHSM_APS_PDN_OPTION_MODIFIED);
                CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
            }

            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_SUCCESS, VOS_FALSE);
        }
        else
        {
            /* To Do */
        }

        CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_TRUE, EHSM_ESM_PDN_OPT_CONNECTED);

        CNAS_EHSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_FALSE);

        CNAS_EHSM_AttachFailureHandler_Activating(pStAttachCnf->ucPdnId, pStAttachCnf->enErrorCode, &(pstPdnInfo->stApn));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf
 ��������  : CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF��״̬���յ���
             ϢID_CTTF_CNAS_EHRPD_RECONN_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SndHsmConnEstReq();

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    if (CNAS_EHSM_EHRPD_ACTIVE_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);
    }

    CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(CNAS_CTTF_EHRPD_LINK_NOT_EXISTED);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
    if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
    {
        CNAS_EHSM_SndCttfEhrpdDetachInd();
    }
    else
    {
        CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
    }

    CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                              pstEntryMsg->ulEventType);

    CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvTiWaitRetryPdnSetup_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU     *pstAttachReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    ucPdnId     = CNAS_EHSM_GetPdnId_Activating();

    if (VOS_FALSE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndHsmConnEstReq();

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF, TI_CNAS_EHSM_WAIT_HSM_CONN_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF);
    }
    else
    {
        /* airlink exist case */
        if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            pstAttachReq = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

            CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, pstAttachReq->enAttachReason);
        }
        else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndCttfEhrpdAttachReq(ucPdnId, CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnConnReq(ucPdnId);
        }

        CNAS_EHSM_SetSendPdnActFlag_Activating(VOS_TRUE);

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF, TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF_LEN);

        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU      *pstAbortReq    = VOS_NULL_PTR;

    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP);

    pstAbortReq = (CNAS_EHSM_EHSM_ABORT_REQ_STRU*)pstMsg;

    CNAS_EHSM_ProcAbortProcedure_Activating(pstAbortReq->ulEventType);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���¿տ���·״̬ */
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    if (CNAS_EHSM_EHRPD_ACTIVE_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU         *pstRcvAbortMsg = VOS_NULL_PTR;

    pstRcvAbortMsg = (CNAS_EHSM_EHSM_ABORT_REQ_STRU *)pstMsg;

    CNAS_EHSM_ProcAbortProcedure_Activating(pstRcvAbortMsg->ulEventType);

    return VOS_TRUE;
}

VOS_UINT32 CNAS_EHSM_RcvAbortReq_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);
    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    CNAS_EHSM_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf
 ��������  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF״̬���յ���ϢID_CTTF_CNAS_EHRPD_PDN_CONN_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg    = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_CONN_EST_FAIL,
                                                  pstEntryMsg->ulEventType);

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

        CNAS_EHSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf
 ��������  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF�յ���ϢID_CTTF_CNAS_EHRPD_ATTACH_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pStAttachCnf   = VOS_NULL_PTR;

    pStAttachCnf = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        CNAS_EHSM_SndHsmDiscReq();

        /* ֹͣ������ʱ�� */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(pStAttachCnf->enErrorCode));
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf
 ��������  : CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF�յ���ʱ��TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg    = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_HSM_CONN_EST_CNF);

        /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }

        CNAS_EHSM_EstPdnFailureHandler_Activating(EHSM_APS_CAUSE_TIME_OUT,
                                                  pstEntryMsg->ulEventType);

        if ((CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == pstEntryMsg->ulEventType)
          ||(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ)   == pstEntryMsg->ulEventType))
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(EHSM_APS_CAUSE_TIME_OUT);
        }
        else
        {
            CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);

            CNAS_EHSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}


VOS_VOID CNAS_EHSM_IncreConntRetryTimes_Activating(VOS_VOID)
{
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;

    /*update conn est retry time +1*/
    pstRetryInfo = CNAS_EHSM_GetRetryInfo_Activating();

    pstRetryInfo->usCurConnEstRetryTimes++;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_ResetConntRetryTimes_Activating
 ��������  : ������·Retry��������Ϊ0
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��1��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_EHSM_ResetConntRetryTimes_Activating(VOS_VOID)
{
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;

    pstRetryInfo = CNAS_EHSM_GetRetryInfo_Activating();

    pstRetryInfo->usCurConnEstRetryTimes = 0;

    return;
}


VOS_VOID CNAS_EHSM_EstPdnFailureHandler_Activating(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause,
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucCid;

    ucPdnId  = CNAS_EHSM_GetPdnId_Activating();
    ucCid    = CNAS_EHSM_GetCidByPdnId(ucPdnId);

    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsReconnCnf(enCause, ucPdnId, ucCid);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsPdnActivateCnf(ucCid, enCause);

        /* ������صĲ�����������Ϣ */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, enCause);

        /* ������صĲ�����������Ϣ */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == ulEventType)
    {
        CNAS_EHSM_SndApsLteHandOverToEhrpdInd(ucPdnId, EHSM_APS_PDN_OPTION_DEACTIVED);

        /* ������صĲ�����������Ϣ */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);

        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
    }
    else if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_ATTACH_REQ) == ulEventType)
    {
        /* ������صĲ�����������Ϣ */
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
    }
    else
    {
    }

    return;
}


EHSM_APS_CAUSE_ENUM_UINT32 CNAS_EHSM_GetAbortCauseByEventType_Activating(
    VOS_UINT32                          ulEventType
)
{

    if (CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ) == ulEventType)
    {
        return EHSM_APS_CAUSE_POWER_OFF;
    }
    else if (CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_EHRPD_SUSPEND;
    }
    else if (CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_PPP_DETACH;
    }
    else if (CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND) == ulEventType)
    {
        return EHSM_APS_CAUSE_NOT_SUPPORT_EHRPD;
    }
    else
    {
        return EHSM_APS_CAUSE_CONN_EST_FAIL;
    }

}



VOS_VOID CNAS_EHSM_ProcAbortProcedure_Activating(
    VOS_UINT32                          ulAbortEventType
)
{
    VOS_UINT32                          ulEntryEventType;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg      = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    ulEntryEventType = pstEntryMsg->ulEventType;

    if (VOS_TRUE == CNAS_EHSM_GetSendPdnActFlag_Activating())
    {
        /* ֮ǰ�Ѿ�����Attach_req/Pdn_Conn_Req */
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_WAIT_CTTF_PDN_SETUP_CNF);

        /* �����ǰ�����һ��PDN,ֱ�ӷ���Detach Ind */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            CNAS_EHSM_SndCttfEhrpdDetachInd();
        }
        else
        {
            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(CNAS_EHSM_GetPdnId_Activating());
        }
    }

    CNAS_EHSM_EstPdnFailureHandler_Activating(CNAS_EHSM_GetAbortCauseByEventType_Activating(ulAbortEventType),
                                              ulEntryEventType);

    if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ)    == ulAbortEventType)
     || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY) == ulAbortEventType))
    {
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_FALSE);
    }
    else
    {

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
    }

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_UINT8 CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode
)
{
    switch(enErrorCode)
    {
        case CNAS_CTTF_EHRPD_ERROR_CODE_GENERAL_ERROR:
        case CNAS_CTTF_EHRPD_ERROR_CODE_UNAUTHORIZED_APN:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDN_LIMIT_EXCEEDED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_NO_PGW_AVAILABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PGW_UNREACHABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PGW_REJECT:
        case CNAS_CTTF_EHRPD_ERROR_CODE_INSUFFICIENT_PARAMETERS:
        case CNAS_CTTF_EHRPD_ERROR_CODE_RESOURCE_UNAVAILABLE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_ADMIN_PROHIBITED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDNID_ALREADY_IN_USE:
        case CNAS_CTTF_EHRPD_ERROR_CODE_SUBSCRIPTION_LIMITATION:
        case CNAS_CTTF_EHRPD_ERROR_CODE_PDN_CONNECTION_ALREADY_EXISTS_FOR_THIS_APN:
        case CNAS_CTTF_EHRPD_ERROR_CODE_EMERGENCY_SERVICES_NOT_SUPPORTED:
        case CNAS_CTTF_EHRPD_ERROR_CODE_RECONNECT_TO_THIS_APN_NOT_ALLOWED:
             return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}


VOS_VOID CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx  = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstEhsmCtx  = CNAS_EHSM_GetEhsmCtxAddr();
    ucPdnId     = CNAS_EHSM_GetPdnId_Activating();

    CNAS_EHSM_SetSessionType(EHSM_HSM_SESSION_TYPE_NULL);

    /* clean the retry pdn info */
    CNAS_EHSM_InitApnRetryInfo();

    /* �������attach�����û�����ҵ�񴥷��ģ���Ҫ�ظ�����ʧ�� */
    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ظ�����Attach Cnf */
        if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucInUsed)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, enCause);
        }
    }

    CNAS_EHSM_SndHsmEhrpdNotAvailableInd();

    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    CNAS_EHSM_SndLocalDetachAllReq(enCause);

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_VOID CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating
(
    VOS_UINT8                           ucCid,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    CNAS_EHSM_InitApnRetryInfo();

    CNAS_EHSM_SndApsPdnActivateCnf(ucCid, enCause);

    CNAS_EHSM_SetSessionType(EHSM_HSM_SESSION_TYPE_NULL);

    CNAS_EHSM_SndHsmEhrpdNotAvailableInd();

    CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);

    /* ��״̬���󣬱���ȥ���� */
    CNAS_EHSM_SndLocalDetachAllReq(enCause);

    CNAS_EHSM_QuitFsmL2();

    return;
}


VOS_VOID CNAS_EHSM_AttachFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
)
{
    CNAS_EHSM_CTX_STRU                                     *pstCtxAdrr   = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                                     *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                                              ucIsRejectByNW;
    VOS_UINT16                                              usMaxNoOfRetry;
    VOS_UINT8                                               ucCurrApnRetryCnt;
    CNAS_EHSM_APN_STRU                                      stApn;

    NAS_MEM_SET_S(&stApn, sizeof(CNAS_EHSM_APN_STRU), 0x00, sizeof(CNAS_EHSM_APN_STRU));
    stApn.ucApnLen = pstApn->ucApnLen;
    NAS_MEM_CPY_S(stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pstApn->aucApn, CNAS_EHSM_MAX_APN_LEN);

    pstCtxAdrr        = CNAS_EHSM_GetEhsmCtxAddr();
    pstRetryInfo      = CNAS_EHSM_GetRetryInfo_Activating();
    ucIsRejectByNW    = CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(enErrorCode);
    ucCurrApnRetryCnt = CNAS_EHSM_GetSpecialApnRetryCnt(&stApn);
    usMaxNoOfRetry    = CNAS_EHSM_GetMaxNumOfApnRetry();
    pstEntryMsg       = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    if ((VOS_TRUE == ucIsRejectByNW)
     || (CNAS_CTTF_EHRPD_ERROR_CODE_TIMEROUT == enErrorCode))
    {
        /* ����NV���Ƶ����Դ��������䵽hrpd */
        if (ucCurrApnRetryCnt >= usMaxNoOfRetry)
        {
            CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }
        /*
             ��һ��pdn����ʧ��ʱ��ʧ��ԭ����NW���ԭ���VSNCPЭ�̳�ʱ������intial attach����handover attach����Ҫ����
             Ϊ��֤ ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ��  ���˴����usLcpOtherFailRetryTimes
         */
        pstRetryInfo->usLcpOtherFailRetryTimes = 0;

        CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

        /* ����һ��retry apn�ĳ��Դ��� */
        CNAS_EHSM_IncreSpecialApnRetryCnt(&stApn);
        return;
    }

    /*
         6.4.2.4  eHRPD PPP-LCP ʧ�ܴ���Ҫ��
             6.4.2.4.1  eHRPD ���˵� HRPD Ҫ��
        �ն�ѡ��eHRPD������룬�����eHRPD PPP�Ự������������������PPP-LCPʧ�ܣ�
        a)  �ն��յ�����෢�͵ġ�EAP-Failure ����Ϣ��EAP-AKA�� ��Ȩʧ�ܡ���Ҫ����Ϊ���������
        �ն˷��ͺ������루error code ���ġ�EAP Notify ����Ϣ�󣬷��͡�EAP-Failure����Ϣ����
        ����ȡֵ��Χ0��16384��
        b)  ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ�ܣ�ʧ��������������δ�ɹ���Ӧ��������
        ���������̳�ʱ��time out ����������Ȩ����time out ��
            ע��1��VSNCPʧ���������δ��ӦVSCNP�������VSCNP����time out ��������������ڣ�
        ������׼6.4.2.3  ��a)��VSNCPЭ�鲿�֡�
            ע��2��LCP��������LCP-Co nfig Request ���������趨�������ش�����ʧ�ܲű���Ϊ
        ��time out ��
        ��� <[��Ϊ]�й�����LTE�ֻ��ն˼���Ҫ�󣨵����ۣ��� 2014 SX-007 ��_20140922>
    */

    /* ��LCP Э���е�EAP-Failureʧ�ܻ����ദ��ʱ��ֱ�ӻ��˵�hrpd */
    else if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
    {
        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
        return;
    }

    /* b)  ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ�� (��������ʧ��3�λ��䵽hrpd) */
    else if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode)
    {
        if (pstRetryInfo->usLcpOtherFailRetryTimes < CNAS_EHSM_MAX_RETRY_PDN_SETUP_FOR_LCP_OTHER_FAIL)
        {
            CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

            pstRetryInfo->usLcpOtherFailRetryTimes++;
            return;
        }

        /* ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ�� */
        CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating(CNAS_EHSM_MapCttfErrCode(enErrorCode));
        return;
    }
    else
    {
        pstRetryInfo->usLcpOtherFailRetryTimes = 0;

        /* �������attach�����û�����ҵ�񴥷��ģ���Ҫ�ظ�����ʧ�� */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
        {
            CNAS_EHSM_SndApsPdnAttachCnf(ucPdnId, CNAS_EHSM_MapCttfErrCode(enErrorCode));
        }

        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());

        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
    }

    return;
}

/*****************************************************************************
Function Name   :   CNAS_EHSM_PdnSetupFailureHandler_Activating
Description     :  Ĭ�ϳ����������pdn����ʧ��ʱ�Ĵ���
Input parameters:       EHSM_APS_CAUSE_ENUM_UINT32          enCause,
                        VOS_UINT32                          ulEventType,
                        VOS_UINT8                           ucPdnId
Output parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-07-23
    Author         : f00279542
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_EHSM_PdnSetupFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
)
{
    CNAS_EHSM_CTX_STRU                                     *pstCtxAdrr   = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo   = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                                     *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_EHSM_ACTIVATING_RETRY_INFO_STRU                   *pstRetryInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usMaxNoOfRetry;
    VOS_UINT8                                               ucIsRejectByNW;
    VOS_UINT8                                               ucCurrApnRetryCnt;
    CNAS_EHSM_APN_STRU                                      stApn;

    NAS_MEM_SET_S(&stApn, sizeof(CNAS_EHSM_APN_STRU), 0x00, sizeof(CNAS_EHSM_APN_STRU));
    stApn.ucApnLen = pstApn->ucApnLen;
    NAS_MEM_CPY_S(stApn.aucApn, CNAS_EHSM_MAX_APN_LEN, pstApn->aucApn, CNAS_EHSM_MAX_APN_LEN);

    pstCtxAdrr           = CNAS_EHSM_GetEhsmCtxAddr();
    pstPdnInfo           = &(pstCtxAdrr->astLocalPdnBearInfo[ucPdnId]);
    ucIsRejectByNW       = CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(enErrorCode);
    ucCurrApnRetryCnt    = CNAS_EHSM_GetSpecialApnRetryCnt(&stApn);
    usMaxNoOfRetry       = CNAS_EHSM_GetMaxNumOfApnRetry();
    pstEntryMsg          = CNAS_EHSM_GetCurrFsmEntryMsgAddr();
    pstRetryInfo         = CNAS_EHSM_GetRetryInfo_Activating();

    /*
        ehrpd ���˵�hrpd�Ĳ���:
        һ��������ܾ���Ҳ����X.S0057   Table 5    Error Code values������ͼ�� �е�ԭ��ֵ�� VSNCP timeout
        1.Handover����
        1����һ��PDN����������ܾ�������NV���ƴ���(Ĭ������)����Ȼʧ�ܣ����˵�HRPD
        2���ǵ�һ��PDN����������ܾ��������ԣ�ֱ����APSָʾPDN�ָ�ʧ��

        2.Initial����
        PDN����������ܾ���ֱ�ӻظ�APS����ʧ�ܣ�����¼һ������(��Ը�APN),�������ԡ�����AP�ز��������Ȼʧ�ܣ��ۼӴ��������ۻ������ﵽNV���ƴ��������ҵ�ǰû�����������ɹ���PDNʱ���������ˡ�
        �ڸ�APN�Ͻ����ɹ�ʱ����������ۻ��Ĵ�����

        ���䣺
        1.��ĳ��apn�ۼƴ����ﵽ���ֵ����apn��ʧ�ܼ������壬�´�������ʱ�����ж��ۼƵĴ��������ʧ�ܾͻ��˵�hrpd
          ��һ��apn����ɹ�ʱ��������apn�ļ��������

        2.


        �����Ǳ�����ܾ���Ҳ���Ƿ�X.S0057   Table 5    Error Code values �е�ԭ��ֵ��������ż����ĵ��Ѿ�������ȷ˵���ˣ������ֲ��䡣
           ����apnȥ������������Դ
    */
    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
    {
        if ((VOS_TRUE == ucIsRejectByNW)
         || (CNAS_CTTF_EHRPD_ERROR_CODE_TIMEROUT == enErrorCode))
        {
            /*  �����ڶ���pdnʱ����ʧ�ܵ�ԭ��ֵΪNW��ԭ��ֵ��VSNCPЭ�̳�ʱ��ԭ��ֵ�������û����ݲ���ʱ�ż�¼retry info */
            if (ucCurrApnRetryCnt >= usMaxNoOfRetry)
            {
                CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
                return;
            }

            /* ����retry apn����Ϣ */
            CNAS_EHSM_IncreSpecialApnRetryCnt(&stApn);
        }

        /* ��LCP Э���е�EAP-Failureʧ�ܻ����ദ��ʱ��ֱ�ӻ��˵�hrpd */
        if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
        {
            CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }

        /* b)  ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ�� (��������ʧ��3�λ��䵽hrpd) */
        if (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode)
        {
            if (pstRetryInfo->usLcpOtherFailRetryTimes < CNAS_EHSM_MAX_RETRY_PDN_SETUP_FOR_LCP_OTHER_FAIL)
            {
                CNAS_EHSM_StartTimer(TI_CNAS_EHSM_WAIT_RETRY_PDN_SETUP, pstCtxAdrr->stRetryCtrlInfo.stRetryPdnSetupInfo.ulExpireTimerLen);
                CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY);

                pstRetryInfo->usLcpOtherFailRetryTimes++;
                return;
            }

            /* ��a ���м�Ȩʧ�ܵ�����������PPP-LCP��ʧ�� */
            CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
            return;
        }
        CNAS_EHSM_SndApsPdnActivateCnf(pstPdnInfo->ucCid, CNAS_EHSM_MapCttfErrCode(enErrorCode));
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
        return;
    }

    if (CNAS_BuildEventType(UEPS_PID_EHSM, ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ) == pstEntryMsg->ulEventType)
    {
        CNAS_EHSM_SndApsLteHandOverToEhrpdInd(ucPdnId, EHSM_APS_PDN_OPTION_DEACTIVED);


        CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_GetCid_Activating());
        CNAS_EHSM_ClearEhrpdLocalPdnInfo(CNAS_EHSM_GetPdnId_Activating());
        CNAS_EHSM_SndActivatingRslt(CNAS_EHSM_ACTIVATING_RESULT_FAILURE, VOS_TRUE);
        CNAS_EHSM_QuitFsmL2();
        return;
    }
}


VOS_VOID CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(
    VOS_UINT8                           ucPdnId
)
{

    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo           = VOS_NULL_PTR;
    CNAS_EHSM_MSG_STRU                 *pstEntryMsg          = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstApsPdnActivateReq = VOS_NULL_PTR;
    APS_EHSM_PDN_ATTACH_REQ_STRU       *pstApsPdnAttachReq   = VOS_NULL_PTR;

    pstEntryMsg = CNAS_EHSM_GetCurrFsmEntryMsgAddr();

    pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    pstPdnInfo->ucPdnId   = ucPdnId;
    pstPdnInfo->ulEpsbId  = ucPdnId + CNAS_EHSM_MIN_EPSB_ID;

    if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == pstEntryMsg->ulEventType)
    {
        pstApsPdnActivateReq = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

        pstPdnInfo->ucCid         = pstApsPdnActivateReq->ucCid;
        pstPdnInfo->enPdnType     = CNAS_EHSM_MapApsPdnTypeToEhsm(pstApsPdnActivateReq->enPdnType);

        pstPdnInfo->enAuthType    = CNAS_EHSM_MapApsAuthTypeToEhsm(pstApsPdnActivateReq->enAuthType);
        pstPdnInfo->ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnActivateReq->aucUserName);
        pstPdnInfo->ucPwdLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnActivateReq->aucPassword);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucUserName[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN, 
                      &(pstApsPdnActivateReq->aucUserName[0]), 
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucPwd[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_PASSWORD_LEN,
                      &(pstApsPdnActivateReq->aucPassword[0]), 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        /* EHSM���������APN */
        CNAS_EHSM_EncodeApn((CNAS_EHSM_APN_STRU *)&(pstApsPdnActivateReq->stApn),
                            pstPdnInfo->stApn.aucApn,
                            &pstPdnInfo->stApn.ucApnLen);
    }
    else if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ATTACH_REQ) == pstEntryMsg->ulEventType)
    {
        pstApsPdnAttachReq   = (APS_EHSM_PDN_ATTACH_REQ_STRU*)pstEntryMsg->aucMsgBuffer;

        pstPdnInfo->ucCid     = pstApsPdnAttachReq->ucCid;
        pstPdnInfo->enPdnType = CNAS_EHSM_MapApsPdnTypeToEhsm(pstApsPdnAttachReq->enPdnType);

        pstPdnInfo->enAuthType    = CNAS_EHSM_MapApsAuthTypeToEhsm(pstApsPdnAttachReq->enAuthType);
        pstPdnInfo->ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnAttachReq->aucUserName);
        pstPdnInfo->ucPwdLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstApsPdnAttachReq->aucPassword);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucUserName[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_USERNAME_LEN,
                      &(pstApsPdnAttachReq->aucUserName[0]), 
                      EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        NAS_MEM_CPY_S(&(pstPdnInfo->aucPwd[0]), 
                      CNAS_EHSM_MAX_AUTHDATA_PASSWORD_LEN,
                      &(pstApsPdnAttachReq->aucPassword[0]), 
                      EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        /* EHSM���������APN */
        CNAS_EHSM_EncodeApn((CNAS_EHSM_APN_STRU *)&(pstApsPdnAttachReq->stApn),
                            pstPdnInfo->stApn.aucApn,
                            &pstPdnInfo->stApn.ucApnLen);
    }
    else
    {
    }

    return;
}

#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


