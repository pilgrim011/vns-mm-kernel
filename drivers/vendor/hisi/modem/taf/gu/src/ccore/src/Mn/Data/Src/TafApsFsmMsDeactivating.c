
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmDeactivating.c
  �� �� ��   : ����
  ��    ��   : S62952
  ��������   : 2011��12��14��
  ����޸�   :
  ��������   : Inactivating״̬��������
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��14��
    ��    ��   : S62952
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndSm.h"
#include "TafApsSndAt.h"
#include "TafApsSndInternalMsg.h"
#include "TafFsm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "MmcApsInterface.h"
#include "TafSmInterface.h"
#include "TafApsComFunc.h"
#include "TafApsSndEsm.h"
#endif
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "MnApsComm.h"
#include "TafApsComFunc.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"
#include "TafApsSndEhsm.h"
#include "TafSdcLib.h"


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSDEACTIVATING_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR

  3.��    ��   : 2014��6��28��
    ��    ��   : A00165503
    �޸�����   : DSDS III ��Ŀ, ����NO RF��������ʱ, ������������

  4.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : DTS2014122908593: CMCC VoLTE��������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�PDPȥ����������Ӧ�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF����, ��������*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
            {
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
            }
            else
            {
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
                TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode();
            }
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND);

            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);

            break;

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR

  3.��    ��   : 2014��6��28��
    ��    ��   : A00165503
    �޸�����   : DSDS III ��Ŀ, ����NO RF��������ʱ, ������������

  4.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : DTS2014122908593: CMCC VoLTE��������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    pstCallEndReq = (TAF_PS_CALL_END_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF����, ��������*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_RcvAtPsCallEndReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
            {
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
            }
            else
            {
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode();
            }
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND);

            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);

            break;

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
             �յ�ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : DTS2014122908593: CMCC VoLTE��������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrRatType;
    VOS_UINT8                               ucPdpId;

    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode(pstInternalMsg->enCause);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
            {
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
            }
            else
            {
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
                TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_LteMode();
            }
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND);

            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);

            break;

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /*��ȡ����ģʽ*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_DEACTIVATING);
            TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_LteMode();
            break;
#endif

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : DTS2014122908593: CMCC VoLTE��������

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �����Ϣ�޸�

  4.��    ��   : 2016��03��03��
    ��    ��   : w00316404
    �޸�����   : ���뼼����ΪNULL����pdp activate ind��ND Client
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU                  *pstInternalMsg;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                               ucPdpId;
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
#if (FEATURE_ON == FEATURE_LTE)
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �����ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
      && (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        if (VOS_TRUE != pstPdpEntity->ulNdClientActiveFlg)
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
    }
#endif


    /* ���������£���Ӧ��������������˴���Ȼ����ȥ������� */
    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        switch(pstEntryMsg->ulEventType)
        {
            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ):
                TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ):
                pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;
                TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode(pstInternalMsg->enCause);
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvMmcServiceStatusInd_MsDeactivating_WaitL4aDeactivateCnfSuspend:Wrong Msg Entry");
                break;
        }
    }
#if (FEATURE_ON == FEATURE_LTE)
    else
    {
        if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
        {
            switch(pstEntryMsg->ulEventType)
            {
                case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ):
                    if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
                    {
                        TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
                    }
                    else
                    {
                        TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode();
                    }
                    break;

                case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
                    if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
                    {
                        TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
                    }
                    else
                    {
                        TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode();
                    }
                    break;

                case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ):
                    TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_LteMode();
                    break;

                default:
                    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvMmcServiceStatusInd_MsDeactivating_WaitL4aDeactivateCnfSuspend:Wrong Msg Entry");
                    break;
            }
        }
    }
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

        if ((pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ))
         || (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ)))
        {
            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            /* ���½�ȥ���������ͳ�������������3GPP2״̬������ */
            TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);
        }
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* 1Xģʽ�£�����ȥ����, hrpd����EHSM���б���ȥ���� */
        /* ����ȥ����ο���ʱ����ʱ�Ĵ��� */
        TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode();
    }
    else
    {

    }
#endif


    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_SMREG_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��13��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND);
    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��13��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucPdpId;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity  = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����EPS����ȥ����ָʾ */
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��13��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��8��21��
    ��    ��   : A00165503
    �޸�����   : DTS2014081803666: ����SNDCP����״̬�ж�, ���SNDCP���ڼ���
                 ״̬, �轫��ȥ����

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_Suspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : �ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں󣬵���С���ź�
                 ���´������SDT������PDȥ�����Խ��������ϱ�

  3.��   ��    : 2013-01-08
    ��   ��    : Y00213812
    �޸�����   : FOR DTS2013010906738,���𱾵�ȥ����ǰ������Ѿ�����SNDCP, ��Ҫ��
                 SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  4.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ͬ��PDP״̬&��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* ��SM���ͱ���ȥ�������� */
    TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* ��Ϊ����ȥ����ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�D_PMC_SMREG_PDP_DEACTIV_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : DTS2012060200787, ȥ����Ĭ�ϳ��أ��ҽӵ�ר�г���Ҳ��Ҫһ��ȥ����

  3.��    ��   : 2012��06��29��
    ��    ��   : f00179208
    �޸�����   : DTS2012062902425, IPV4V6���ţ�IPV4�ɹ�IPV6ʧ�ܣ����ڲ�ȥ�����IPV4��PDP

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);
    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* ���ȥ���������PDP,�ҽ�������Ĵ�PDP����Ҫ����ȥ���� */
        TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�D_PMC_SMREG_PDP_DEACTIV_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);

    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);

    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �����Ϣ�޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* Ǩ����״̬����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf: Wrong RatType");
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��   ��    : 2013-01-08
    ��   ��    : Y00213812
    �޸�����   : FOR DTS2013010906738,���𱾵�ȥ����ǰ������Ѿ�����SNDCP, ��Ҫ��
                 SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  4.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* ��SM���ͱ���ȥ�������� */
    TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();
    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�D_PMC_SMREG_PDP_DEACTIV_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��26��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDPȥ�����ֹͣ����ͳ��

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);
    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�D_PMC_SMREG_PDP_DEACTIV_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);

    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��07��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ */
    if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
      && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* ��SNDCP����ȥ����ָʾʧ��, ֱ���ϱ�PDPȥ����ɹ��¼�, �ͷ���Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);

    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucPdpId;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity  = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����EPS����ȥ����ָʾ */
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  3.��    ��   : 2014��8��21��
    ��    ��   : A00165503
    �޸�����   : DTS2014081803666: ����SNDCP����״̬�ж�, ���SNDCP���ڼ���
                 ״̬, �轫��ȥ����

  4.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStaChangeInd_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : DTS2014122908593: CMCC VoLTE��������

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �����Ϣ�޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStaChangeInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
#endif

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {

        /*GUģ�� ,����Ҫ����,������SM�Ļظ�,״̬�ص�
          TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF);
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* ��ʼ��, ��ȡ��Ϣ���� */
        pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();

        switch(pstEntryMsg->ulEventType)
        {
            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ):
                if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
                {
                    TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
                }
                else
                {
                    TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode();
                }
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
                if (VOS_FALSE == TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_GetPdpEntInfoAddr(ucPdpId)))
                {
                    TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef();
                }
                else
                {
                    TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode();
                }
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ):
                TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_LteMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvMmcServiceStatusInd_MsDeactivating_WaitL4aDeactivateCnfSuspend:Wrong Msg Entry");
                break;

        }
    }
    else
    {
        ;
    }
#endif

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��    ��   : 2013��04��24��
    ��    ��   : z60575
    �޸�����   : ���ⵥ:DTS2013042001439,��Ҫ����ȥ���ͬ��SM״̬

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  5.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* ͬ��PDP��Ϣ */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                             SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��SM���ͱ���ȥ�������� */
    TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* ��Ϊ����ȥ����ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�APS_SN_DEACT_RSP_MSG_TYPE��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: Gģ����ʱ�����Ͽ�����, ����ͳ���쳣,
                 PDPȥ����δ����IPF

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ����ָʾ����ʱӦ����Ǩ����״̬��TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* Ǩ����״̬����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp: Wrong RatType");
    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRsp
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��Ϊ����ȥ���� */

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��Ϊ����ȥ����ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�APS_SN_DEACT_RSP_MSG_TYPE��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  4.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU                  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    VOS_UINT8                               ucPdpId;


    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( TAF_APS_RAT_TYPE_GSM == pstServStaChangeInd->enRatType )
    {
        /*Gģ�� ,����Ҫ����,������SM�Ļظ�,״̬�ص�
          TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF);
    }

    /* WCDMA��LTE����£���Ϊȥ�����Ѿ��ɹ��������ϱ� */
    if ( ( TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType )
#if (FEATURE_ON == FEATURE_LTE)
       ||( TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType )
#endif
       )
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* ��Ϊ����ȥ����ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP������ */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRspSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��Ϊ����ȥ����ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitL4aDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitL4aDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitL4aDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_CNF_STRU       *pstEsmReleaseCnf;

    pstEsmReleaseCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    if(APP_SUCCESS == pstEsmReleaseCnf->ulRslt)
    {
        return TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnf(ulEventType, pstMsg);
    }
    else
    {
        return TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnf(ulEventType, pstMsg);
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��26��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDPȥ�����ֹͣ����ͳ��

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  4.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : DTS2012060200787, �յ�L4A���ܺ���Ҫ����Ӧȥ����PDP�µ�ר�г���
                 ����Ϣͬ����SM����Ϊ���ʱ��SM�Ѿ�����Щ�������

  3.��    ��   : 2012��7��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012071105614: ȱʡ����ΪIPv4, ˫ջ���ųɹ���Ͽ�����,
                 �ٴ�˫ջ����ֻ��IPv6���ųɹ�, ���ٷ���IPv4���Ͳ���

  4.��    ��   : 2012��7��19��
    ��    ��   : A00165503
    �޸�����   : DTS2012071805127: APS����EPS���ر���ԭ��ֵ"LAST_PDN_DISCON-
                 N_NOT_ALLOWED"ʱ, û���ٴ�ͬ��PDP��Ϣ��SM, ���ܻᵼ��SMά��
                 ��PDP��Ϣ��APS��һ��

  5.��    ��   : 2012��8��10��
    ��    ��   : z60575
    �޸�����   : DTS2012081006711: ���IPV6�����

  6.��    ��   : 2012��8��13��
    ��    ��   : z60575
    �޸�����   : DTS2012081300271: ��SMͬ����Ϣǰ�ж��Ƿ����TransId

  7.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  8.��    ��   : 2014��3��20��
    ��    ��   : A00165503
    �޸�����   : DTS2014032005866: ���һ��PDN����ȥ����ܺ�, �޸�Ϊע���
                 ��, ��Ҫ����ע����ر�ע

  9.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    APP_ESM_PDP_RELEASE_CNF_STRU           *pstPdpRej;
    VOS_UINT8                               ucPdpId;

    /* ��ǰLTE���п��ܻ����ȥ����ʧ�ܣ�Ŀǰ��˵������յ�L�µ�ȥ����ʧ�ܣ�ֱ��
       �ϱ�ȥ����ɹ�����Ӧ��״̬��� */

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡAPSʵ���ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);


    pstPdpRej = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;
    if (APP_ERR_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED == pstPdpRej->ulRslt)
    {
        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* ��������PDPȥ���Lģ��ܾ������ݴ��ض�ԭ��ֵ�������⴦����ʱ
           ��ʵ�岻��ʵ��ȥ������ǻ�ˢ�³�Ĭ�ϳ��أ�ʵ��״̬����Ϊ����״̬ */


        /* ˢ�³�Ĭ�ϳ��ص�CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);

        TAF_APS_SetPdpEntAttachBearerFlag(ucPdpId, VOS_TRUE);

        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);

        /* ͬ��PDP��Ϣ��SM */
        if (VOS_TRUE == pstPdpEntity->bitOpTransId)
        {
            MN_APS_SndSmBearerActivateInd(pstPdpEntity);
        }

        /* ��Ҫ����Ӧȥ����PDP�µ�ר�г��ص���Ϣͬ����SM��
           ��Ϊ���ʱ��SM�Ѿ�����Щ����� */
        MN_APS_SndSmAllSecPdpActivateInd(pstPdpEntity);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��    ��   : 2013��04��24��
    ��    ��   : z60575
    �޸�����   : ���ⵥ:DTS2013042001439,��Ҫ����ȥ���ͬ��SM״̬

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  5.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��Ϊ����ȥ���� */

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                             SM_ESM_PDP_OPT_DEACTIVATE);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM���ͱ���ȥ�������� */
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitEsmDeactivateCnf
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* Ǩ����״̬����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND);
    }
    else
    {
        /* ��ʱ�յ�����ָʾ����Ϊ��һ���쳣��Ϣ */
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitEsmDeactivateCnf: err msg");
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnf(
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitL4aDeactivateCnfSuspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �ټ����ȥ�����APSʵ�����õ�CID,�ϱ�ERROR�¼� */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_OPERATION_CONFLICT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: �Ͽ������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq           = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �̳�ԭ�жϿ����� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                          pstCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitL4aDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitL4aDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, Ӧ��MT����, ����ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitL4aDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitL4aDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ����ȥ�����APSʵ��, �Ҷ�MT����, ����ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_CNF_STRU       *pstEsmReleaseCnf;

    pstEsmReleaseCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    if(APP_SUCCESS == pstEsmReleaseCnf->ulRslt)
    {
        return TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend(ulEventType, pstMsg);
    }
    else
    {
        return TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnfSuspend(ulEventType, pstMsg);
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��26��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDPȥ�����ֹͣ����ͳ��

  3.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  4.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : DTS2012060200787, �յ�L4A���ܺ���Ҫ����Ӧȥ����PDP�µ�ר�г���
                 ����Ϣͬ����SM����Ϊ���ʱ��SM�Ѿ�����Щ�������

  3.��    ��   : 2012��7��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012071105614: ȱʡ����ΪIPv4, ˫ջ���ųɹ���Ͽ�����,
                 �ٴ�˫ջ����ֻ��IPv6���ųɹ�, ���ٷ���IPv4���Ͳ���

  4.��    ��   : 2012��7��19��
    ��    ��   : A00165503
    �޸�����   : DTS2012071805127: APS����EPS���ر���ԭ��ֵ"LAST_PDN_DISCON-
                 N_NOT_ALLOWED"ʱ, û���ٴ�ͬ��PDP��Ϣ��SM, ���ܻᵼ��SMά��
                 ��PDP��Ϣ��APS��һ��

  5.��    ��   : 2012��8��10��
    ��    ��   : z60575
    �޸�����   : DTS2012081006711: ���IPV6�����

  6.��    ��   : 2012��8��13��
    ��    ��   : z60575
    �޸�����   : DTS2012081300271: ��SMͬ����Ϣǰ�ж��Ƿ����TransId

  7.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  8.��    ��   : 2014��3��20��
    ��    ��   : A00165503
    �޸�����   : DTS2014032005866: ���һ��PDN����ȥ����ܺ�, �޸�Ϊע���
                 ��, ��Ҫ����ע����ر�ע

  9.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    APP_ESM_PDP_RELEASE_CNF_STRU           *pstPdpRej;
    VOS_UINT8                               ucPdpId;

    /* ��ǰLTE���п��ܻ����ȥ����ʧ�ܣ�Ŀǰ��˵������յ�L�µ�ȥ����ʧ�ܣ�ֱ��
       �ϱ�ȥ����ɹ�����Ӧ��״̬��� */

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡAPSʵ���ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);


    pstPdpRej = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    /* ��ǰL4A��APS֮����Ҫ����ô������ֵĿǰ��δ���壬��������������ȷ�� */
    /* �������Ϊ�����µ�ȥ����ʧ�ܣ���Һ���Ҫ���·���ȥ���������Ŀǰ��ʱ
       ��һ��ֵ������ */
    if (APP_ERR_SM_SUSPENDED == pstPdpRej->ulRslt)
    {
        /*
          Ǩ����״̬����TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND����Һ��ٴη���ȥ�������
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND);

        return VOS_TRUE;
    }
    else if (APP_ERR_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED == pstPdpRej->ulRslt)
    {
        /* ��������PDPȥ���Lģ��ܾ������ݴ��ض�ԭ��ֵ�������⴦����ʱ
           ��ʵ�岻��ʵ��ȥ������ǻ�ˢ�³�Ĭ�ϳ��أ�ʵ��״̬����Ϊ����״̬ */

        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* ˢ�³�Ĭ�ϳ��ص�CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);

        TAF_APS_SetPdpEntAttachBearerFlag(ucPdpId, VOS_TRUE);

        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);

        /* ͬ��PDP��Ϣ��SM */
        if (VOS_TRUE == pstPdpEntity->bitOpTransId)
        {
            MN_APS_SndSmBearerActivateInd(pstPdpEntity);
        }

        /* ��Ҫ����Ӧȥ����PDP�µ�ר�г��ص���Ϣͬ����SM��
           ��Ϊ���ʱ��SM�Ѿ�����Щ����� */
        MN_APS_SndSmAllSecPdpActivateInd(pstPdpEntity);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
        pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
        pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
        if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
            {
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
            }
        }

        /* �ͷ���Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_RELEASE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  3.��    ��   : 2014��8��21��
    ��    ��   : A00165503
    �޸�����   : DTS2014081803666: ����SNDCP����״̬�ж�, ���SNDCP���ڼ���
                 ״̬, �轫��ȥ����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU                  *pstInternalMsg;

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ���������£���Ӧ��������������˴���Ȼ����ȥ������� */
    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        switch(pstEntryMsg->ulEventType)
        {
            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ):
                TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
                TAF_APS_RcvAtPsCallEndReq_MsDeactivating_GuMode(SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
                break;

            case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ):
                pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;
                TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode(pstInternalMsg->enCause);
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend:Wrong Msg Entry");
                break;
        }
    }
    if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* Ǩ����״̬����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF);
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* ����ȥ����ο���ʱ����ʱ�Ĵ��� */
        TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode();
    }
#endif

    else
    {
         TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend: Wrong Msg");
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : Wait ESM Deactivate Cnf Suspend State, Rcv Pdn Irat Hrpd Ind
             Msg
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
    VOS_UINT8                                               ucPdpId;

    pstLteHandoverInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    if (EHSM_APS_PDN_OPTION_MODIFIED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd);
    }

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* TO DO: ���������Ϣ */
    if (pstEntryMsg->ulEventType == TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ))
    {
        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ���½�ȥ���������ͳ�������������3GPP2״̬������ */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);
    }

    /* �����ڲ���Ϣ���������ڼ�������е�״̬����Ҫ�������Ϣ */
    TAF_APS_SndInterAttachBearerActivateInd();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnfSuspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnfSuspend
 ��������  : TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF_SUSPEND��״̬��
             �յ�TI_TAF_APS_MS_DEACTIVATING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��30��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012031306944,�ڿ���ע��PDP�������PING���壬�Ͽ�OM�ں�
                 ����С���ź����´������SDT������PDȥ�����Խ��������ϱ�

  3.��    ��   : 2013��04��24��
    ��    ��   : z60575
    �޸�����   : ���ⵥ:DTS2013042001439,��Ҫ����ȥ���ͬ��SM״̬

  4.��    ��   : 2013��7��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013071905717: MODIFY���̵��µ��ڲ�ȥ������Ҫ�ϱ�����ȥ
                 �����¼�

  5.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    VOS_UINT8                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��Ϊ����ȥ���� */

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                             SM_ESM_PDP_OPT_DEACTIVATE);

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM���ͱ���ȥ�������� */
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode
 ��������  : DEACTIVATEING��״̬���յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : SM_TAF_CAUSE_ENUM_UINT16            enCause                -ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT8                           ucErrCode;
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* ��ʼ�� */
    ucErrCode = TAF_ERR_NO_ERROR;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId   = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����PDPȥ�������� */
    Aps_PsCallEnd(enCause, ucPdpId, &ucErrCode);

    if (TAF_ERR_NO_ERROR != ucErrCode)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode: End call failed!");
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtCallEndReq_MsActivating_GuMode
 ��������  : DEACTIVATEING��״̬���յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : SM_TAF_CAUSE_ENUM_UINT16            enCause                -ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT8                           ucErrCode;
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* ��ʼ�� */
    ucErrCode = TAF_ERR_NO_ERROR;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId   = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����PDPȥ�������� */
    Aps_PsCallEnd(enCause, ucPdpId, &ucErrCode);

    if (TAF_ERR_NO_ERROR != ucErrCode)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvAtCallEndReq_MsActivating_GuMode: End call failed!");
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode
 ��������  : DEACTIVATEING��״̬���յ��ڲ�ȥ������Ϣ�Ĵ���
 �������  : SM_TAF_CAUSE_ENUM_UINT16            enCause                -ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT8                           ucErrCode;
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* ��ʼ�� */
    ucErrCode = TAF_ERR_NO_ERROR;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId   = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����PDPȥ�������� */
    Aps_PsCallEnd(enCause, ucPdpId, &ucErrCode);

    if (TAF_ERR_NO_ERROR != ucErrCode)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode: End call failed!");
    }
    else
    {
        /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF);

        /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                               TI_TAF_APS_MS_DEACTIVATING_LEN,
                               ucPdpId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_GuMode
 ��������  : DEACTIVATEING��״̬���յ��ڲ�ȥ������Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_GuMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ȡ������Ϣ���� */
    pstEntryMsg      = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg        = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallHangupReq = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId          = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* �ϱ�PDP������� */
        TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                                 TAF_PS_CAUSE_SIM_INVALID);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    /* ���缤���ֶ�Ӧ����",�����Ϣʵ��Ϊ: APP�ܾ����緢��ļ���
       �����ڲ�������Ϣ��״̬��Ǩ�ƣ��ڱ�״̬���д���
    */
    Aps_ActIndRejRsp(ucPdpId);

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode
 ��������  : DEACTIVATEING��״̬���յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* ��ȡ������Ϣ���� */
    pstEntryMsg          = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ESM����ȥ����EPS���� */
    TAF_APS_SndEsmSetCgactMsgDistr(ucPdpId, pstSetPdpCtxStateReq);

    /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* �𱣻���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                           TI_TAF_APS_MS_DEACTIVATING_LEN,
                           ucPdpId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtCallEndReq_MsActivating_LteMode
 ��������  : DEACTIVATEING��״̬���յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��23��
    ��    ��   : A00165503
    �޸�����   : DTS2012052302198: �Ͽ�����������APS�����, û�������ϱ�����
                 ������, ����ATδ�ܼ�ʱ�ϱ�OK, AT��ʱ���ϱ�ERROR

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ������Ϣ���� */
    pstEntryMsg   = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg     = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ESM����ID_APP_ESM_PDP_RELEASE_REQ_REQ��Ϣ, ȥ����EPS���� */
    TAF_APS_SndEsmPdpReleaseReq(pstCallEndReq);

    /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* �𱣻���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                           TI_TAF_APS_MS_DEACTIVATING_LEN,
                           ucPdpId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtCallEndReq_MsActivating_LteMode
 ��������  : DEACTIVATEING��״̬���յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_LteMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_PS_CALL_END_REQ_STRU            stCallEndReq;

    PS_MEM_SET(&stCallEndReq, 0, sizeof(TAF_PS_CALL_END_REQ_STRU));
    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId                           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����Ͽ����Ų��� */
    stCallEndReq.ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    stCallEndReq.stCtrl.ulModuleId = TAF_APS_GetPdpEntModuleId(ucPdpId, stCallEndReq.ucCid);
    stCallEndReq.stCtrl.usClientId = TAF_APS_GetPdpEntClientId(ucPdpId, stCallEndReq.ucCid );
    stCallEndReq.stCtrl.ucOpId     = TAF_APS_GetPdpEntOpId(ucPdpId, stCallEndReq.ucCid);

    /* ��ESM����ID_APP_ESM_PDP_RELEASE_REQ_REQ��Ϣ, ȥ����EPS���� */
    TAF_APS_SndEsmPdpReleaseReq(&stCallEndReq);

    /* ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_ESM_DEACTIVATE_CNF);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫ�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* �𱣻���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_MS_DEACTIVATING,
                           TI_TAF_APS_MS_DEACTIVATING_LEN,
                           ucPdpId);
    }

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_LteMode
 ��������  : DEACTIVATEING��״̬���յ��ڲ�ȥ������Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_LteMode( VOS_VOID )
{
    VOS_UINT8                           ucPdpId;

    /*��ȡPDP ID*/
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    /*��LTE���͹Ҷ�����Lģ��֤�Ҷϲ���ʧ��*/
    TAF_APS_SndEsmPdpManagerRsp(APS_ESM_BEARER_ACT_REJ, 0);

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef
 ��������  : Lģ�²�ȥ����Ĭ�ϳ��أ�ֱ�Ӹ��û��ϱ�ȥ����ɹ���ͬʱ�������ͳ�Ƶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef(VOS_VOID)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg     = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity    = VOS_NULL_PTR;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    TAF_APS_TIMER_STATUS_ENUM_U8            enTimerStatus;

    /* ��ȡ������Ϣ���� */
    pstEntryMsg   = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡAPSʵ���ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* ��鶨ʱ���Ƿ���������, �����������, ����Ҫֹͣ��ʱ�� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_DEACTIVATING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING,
                          ucPdpId);
    }

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ˢ�³�Ĭ�ϳ��ص�CID */
    TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                TAF_APS_DEFAULT_CID,
                                TAF_APS_INVALID_MODULEID,
                                TAF_APS_INVALID_CLIENTID,
                                TAF_APS_INVALID_OPID);

    /* ͬ��PDP��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);

    /* ͬ��PDP��Ϣ��SM */
    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        MN_APS_SndSmBearerActivateInd(pstPdpEntity);
    }

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode
 ��������  : ��LTEģʽ�µȴ�LNAS�ظ�ȥ��������У�����ȥ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU                  *pstInternalMsg;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;
    VOS_UINT8                                               ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ��ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                             SM_ESM_PDP_OPT_DEACTIVATE);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityRatType())
    {
        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstInternalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ����ڲ�������PDPȥ��������ϱ�ȥ������¼� */
    if (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->ucInterDeactNotifyFlg)
        {
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstInternalMsg->enCause));
        }
    }

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM���ͱ���ȥ�������� */
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

    /* ����ȥ�����뵱ǰȱʡ���ع�����ר�ó��� */
    TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

}

#endif

/*lint +e958*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



