
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmMsModifying.c
  �� �� ��   : ����
  ��    ��   : S62952
  ��������   : 2011��12��14��
  ����޸�   :
  ��������   : Modifying״̬��������
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��14��
    ��    ��   : S62952
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifying.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsProcIpFilter.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsFsmMsDeactivating.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "TafApsSndSm.h"
#include "TafApsSndEsm.h"
#endif
#include "TafApsComFunc.h"
#include "MnComm.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"

#include "TafApsSndEhsm.h"
#include "TafSdcLib.h"

#include "TafApsSndPpp.h"
#include "TafApsSndNd.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSMODIFYING_C

/******************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   3 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬��
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

  2.��    ��   : 2014��6��28��
    ��    ��   : A00165503
    �޸�����   : DSDS III ��Ŀ, ����NO RF��������ʱ, ������������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    /* ��ʼ��, ��ȡ��Ϣ���� */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��ȡPDPId */
    ucPdpId                             = (VOS_UINT8)TAF_APS_GetCurrFsmEntityPdpId();

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
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    /*--------------------------------------------------------------------------
       ��ǰģΪG/W:  ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF
       ��ǰģΪLTE:  ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF
       ��ǰģΪNULL: ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND
    --------------------------------------------------------------------------*/
    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND);

            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                               TI_TAF_APS_MS_MODIFYING_LEN,
                               ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpModifyInd_MsModifying_Init
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬��
             �յ�D_PMC_SMREG_PDP_MODIFY_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��4��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvSmPdpModifyInd_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��ȡPDPId */
    ucPdpId                             = (VOS_UINT8)TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    /* ֻ��GSMģʽ�²Ŵ������Ϣ������ģʽ�����յ�����Ϣ */
    if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
    {
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);

        /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);

        /* �𱣻���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                           TI_TAF_APS_MS_MODIFYING_LEN,
                           ucPdpId);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSmPdpModifyInd_MsModifying_Init: Wrong RAT type!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MMC_APS_SERVICE_STATUS_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT
           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  : ������Ϣʧ��
             VOS_TRUE   : ������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_Suepend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�D_PMC_SMREG_PDP_DEACTIV_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��3��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ͬ��PDP״̬&��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ��
       ���SNDCPû�м���, ֱ���ϱ�PDPȥ����ɹ��¼� */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2012��06��07��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��08��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012080604402, ת����Ϣ����ȷ
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

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

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ��
       ���SNDCPû�м���, ֱ���ϱ�PDPȥ����ɹ��¼� */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /* GUģ�·���PDP�޸����� */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* LTEģ�·���EPS�����޸����� */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
    }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* ����ȥ�����״̬�� */
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /* ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ͬ��PDP״̬&��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                 SM_ESM_PDP_OPT_DEACTIVATE);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)

        /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
        }
#endif

        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpTransId)
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
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend:rev msg err!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
             �յ�D_PMC_SMREG_PDP_MODIFY_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstPdpModifyCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_MDFCNF_PARA_ST                  stParam;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstPdpModifyCnf                     = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    /* �������Ĳ��� */
    ulRet = Aps_PdpMdfCnfParaCheck(pstPdpModifyCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ������ȥ���������״̬����Ǩ�ƣ�ֱ���ڵ�ǰ״̬���� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /*���QOS�Ƿ�����MIN*/
    if (VOS_TRUE == pstPdpModifyCnf->bitOpNegotiatedQos)
    {
        /*MDF_CNF��Ϣ����QOS,����MIN_QOS���бȽ� */
        if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
        {
            /*����MINQOS*/
            Aps_PdpMdfCnfQosSatisfy(ucPdpId, &stParam, pstPdpModifyCnf);

#if (FEATURE_ON == FEATURE_LTE)
            /* ͬ��PDP��Ϣ��ESM */
            MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                    SM_ESM_PDP_OPT_MODIFY);
#endif
        }
        else
        {
            /* �ϱ��¼� */
            TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

            /* �����ڲ���Ϣ������ȥ���������״̬����ת����ֱ���ڵ�ǰ״̬���� */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

            /* ����ȥ�����¼��ϱ���ʶ, �ڲ�ȥ�����, ���ݸñ�ʶ�����Ƿ��ϱ� */
            pstPdpEntity->ucInterDeactNotifyFlg = VOS_TRUE;

            return VOS_TRUE;
        }
    }
    else
    {
        /*��SM���ص�MDF_CNF��Ϣ���� QOS, ���ʾUE�����QOS��������,����û���޸�QOS*/
        Aps_PdpMdfCnfQosSatisfy(ucPdpId, &stParam, pstPdpModifyCnf);

#if (FEATURE_ON == FEATURE_LTE)

        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif
    }

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:

            /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);
            break;

        case TAF_APS_RAT_TYPE_WCDMA:

            /* ֹͣȫ����״̬��������ʱ��*/
            TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
             �յ�D_PMC_SMREG_PDP_MODIFY_REJ��Ϣ�Ĵ���
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmMsg                            = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapSmCause(pstSmMsg->enCause));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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

  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  4.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ͬ��PDP״̬&��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ��
       ���SNDCPû�м���, ֱ���ϱ�PDPȥ����ɹ��¼� */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
             �յ�ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2012��06��07��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��08��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012080604402, ת����Ϣ����ȷ

  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ͬ��PDP״̬&��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* ����Ѿ�����SNDCP, ��Ҫ��SNDCP����ȥ����ָʾ, ���ȴ�SNDCP����Ӧ��
       ���SNDCPû�м���, ֱ���ϱ�PDPȥ����ɹ��¼� */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* �������ָʾ */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND);
    }
    else
    {
        /* ��ʱ��LģӦ����һ���쳣��Ϣ */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF״̬���յ�
             ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��30��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   : ��Ϣ����ɹ�
             VOS_FALSE  : ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡPDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

    /* �����ڲ���Ϣ������ȥ���������״̬����Ǩ�ƣ�ֱ���ڵ�ǰ״̬���� */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡPDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
           ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
       ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

   return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
             �յ�D_PMC_SMREG_PDP_MODIFY_REJ��Ϣ�Ĵ���
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmMsg                            = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapSmCause(pstSmMsg->enCause));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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

  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: PDPȥ����δ����IPF

  4.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ����˵��,��״̬���в���Ҫ��TEARDOWN
       �ٽ����жϴ���,APS���յ�ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ���Ƚ���Ԥ��
       ��,�����Ϣ�д���TEARDOWN,Ԥ�������ҳ�������ЩPDP��ȥ����,Ȼ��,��
       ID_PMC_SMREG_PDP_DEACTIV_IND�ַ�����Ӧ��ʵ��״̬��,����,��״̬���в���
       ��ID_PMC_SMREG_PDP_DEACTIV_IND�е�TEARDOWN�������� */

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

#if (FEATURE_ON == FEATURE_LTE)

    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* ���SNDCP�Ѿ�����, ��ȥ����SNDCP */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot))
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2012��08��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012080604402, ת����Ϣ����ȷ
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* ֹͣȫ����״̬��������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

#if (FEATURE_ON == FEATURE_LTE)

    /* ͬ��PDP״̬&��Ϣ��ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* ���SNDCP�Ѿ�����, ��ȥ����SNDCP */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot))
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : �����ɺ���

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucPdpId;
#endif

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /*GUģ�� ,����Ҫ����,������SM�Ļظ�,״̬�ص�
          TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF);
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /*��SM����abort��Ϣ*/
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* LTEģ�·���EPS�����޸����� */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
    }
#endif
    else
    {
        ;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡPDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �޸ĸ�APSʵ��, ����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
             �յ�APS_SN_MDF_RSP_MSG_TYPE��Ϣ�Ĵ���
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_MODIFY_RSP_ST            *pstSnModifyRsp;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSnModifyRsp                      = &((APS_SNDCP_MODIFY_RSP_MSG*)pstMsg)->ApsSnMdfRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ���ݴ������̵������Ϣ�жϻظ���Ϣ���� */
    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):
            /* ������û������MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
            TAF_APS_SndPdpModifyCnf(ucPdpId);
            break;

        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

            /* ��������緢���MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND�¼� */
            TAF_APS_SndPdpModifyInd(ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp: invalid message!");
            return VOS_TRUE;
    }

    /* ����RABM�Ĵ���ģʽ */
    Aps_SnMsgModSnMdfRsp(pstSnModifyRsp);

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
             �յ�APS_SN_STATUS_REQ_MSG_TYPE��Ϣ�Ĵ���
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

  2.��    ��   : 2014��8��4��
    ��    ��   : A00165503
    �޸�����   : DTS2014080401792: LLCȷ��ģʽ��, ����SN_STATUS_REQ��Ϣ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��SAPI���м�� */
    ulRet = Aps_SnMsgModSnStatusReqParaCheck(pstSnStatusReq);
    if ( APS_PARA_VALID != ulRet )
    {
        MN_WARN_LOG("TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp:Aps_SnMsgModSnStatusReqParaCheck ERR ");
        return VOS_TRUE;
    }

    /* ��鵱ǰAPSʵ���е�SAPI�Ƿ�����SN STATUS��Ϣ��ָ����SAPI������ʱת��ȥ���� */
    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ������ȥ���������״̬����Ǩ�ƣ�ֱ���ڵ�ǰ״̬���� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
             �յ�ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* �������ָʾ */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND);
    }
    else
    {
        /* ��ʱ��LģӦ����һ���쳣��Ϣ */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSetPdpCtxStateReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* ���ڼ����APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl), pstCallOrigReq->stDialParaInfo.ucCid, TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �쳣��Ϣ, ֱ�����û�����OK */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
             �յ�APS_SN_MDF_RSP_MSG_TYPE��Ϣ�Ĵ���
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2014��10��28��
    ��    ��   : j00174725
    �޸�����   : DTS2014102204179
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_MODIFY_RSP_ST            *pstSnModifyRsp;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSnModifyRsp                      = &((APS_SNDCP_MODIFY_RSP_MSG*)pstMsg)->ApsSnMdfRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ���ݴ������̵������Ϣ�жϻظ���Ϣ���� */
    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):
            /* ������û������MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
            TAF_APS_SndPdpModifyCnf(ucPdpId);
            break;

        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

            /* ��������緢���MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND�¼� */
            TAF_APS_SndPdpModifyInd(ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp: invalid message!");
            return VOS_TRUE;
    }

    /* ����RABM�Ĵ���ģʽ */
    Aps_SnMsgModSnMdfRsp(pstSnModifyRsp);

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
             �յ�APS_SN_STATUS_REQ_MSG_TYPE��Ϣ�Ĵ���
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

  2.��    ��   : 2014��8��4��
    ��    ��   : A00165503
    �޸�����   : DTS2014080401792: LLCȷ��ģʽ��, ����SN_STATUS_REQ��Ϣ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    ulRet = Aps_SnMsgModSnStatusReqParaCheck(pstSnStatusReq);
    if (APS_PARA_VALID != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend: Check para failed! ");

        return VOS_TRUE;
    }

    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ������ȥ���������״̬����Ǩ�ƣ�ֱ���ڵ�ǰ״̬���� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg         = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
    {
        /* GUģ�� ,����Ҫ����,������SNDCP�Ļظ�,״̬�ص�
           TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);
    }
    else if ( (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType)
#if (FEATURE_ON == FEATURE_LTE)
           || (TAF_APS_RAT_TYPE_LTE   == pstServStaChangeInd->enRatType)
#endif
    )
    {
        /* �ͷ�SNDCP��Դ */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* ���ݴ������̵������Ϣ�жϻظ���Ϣ���� */
        switch (pstEntryMsg->ulEventType)
        {
            case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):

                /* ������û������MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
                TAF_APS_SndPdpModifyCnf(ucPdpId);
                break;

            case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

                /* ��������緢���MODIFY���ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND�¼� */
                TAF_APS_SndPdpModifyInd(ucPdpId);
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend: invalid message!");
                break;
        }

        /* ֹͣȫ����״̬��������ʱ��*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvMmcServiceStatusInd_MsModifying_WaitSndcpModifyRspSuspend:rev msg err!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND״̬���յ�
             ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��30��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode
 ��������  : MODIFYING��״̬���յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode(VOS_VOID)
{
    VOS_UINT8                           ucErrCode;
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucErrCode                           = TAF_ERR_NO_ERROR;
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg                           = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �޸�PS CALL����: QOS�� */
    Aps_PsCallModify(pstCallModifyReq->stCtrl.usClientId,
                     pstCallModifyReq->stCtrl.ucOpId,
                     ucPdpId,
                     &ucErrCode);
    if (TAF_ERR_NO_ERROR != ucErrCode)
    {
        /* ����PDP������� */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_UNKNOWN);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ����PDP������� */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_SUCCESS);

        /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF);

        /* ���ڿ���GU��LTE�䷴������л�������п��ܶ�ʱ��֮ǰ�Ѿ��������˴�����
           ���������ֻ�ж�ʱ��δ����ʱ������ */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_MODIFYING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* �𱣻���ʱ�� */
            TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                               TI_TAF_APS_MS_MODIFYING_LEN,
                               ucPdpId);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��SM����ABORT����, ȡ����ǰ������� */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �쳣��Ϣ, ֱ�����û�����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpModifyCnfRst_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
             �յ�ID_APP_ESM_PDP_MODIFY_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU        *pstEsmPdpModifyCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstEsmPdpModifyCnf                  = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;

    if (APP_SUCCESS == pstEsmPdpModifyCnf->ulRslt)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
        TAF_APS_SndPdpModifyCnf(ucPdpId);
    }
    else
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpModifyCnf->ulRslt));
    }

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�

  3.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf(
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf(
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
    else if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnf: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �Ѿ������APSʵ��, �ټ����APSʵ�����õ�CID,�ϱ�ERROR�¼�,
       ����,����ȥ����״̬����Ǩ�� */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* �ϱ�PDP��������¼� */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING,
                          ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��SM����ABORT����, ȡ����ǰ������� */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �����޸ĸ�APSʵ��, �����APSʵ�����õ�CID, ����ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl), pstCallOrigReq->stDialParaInfo.ucCid, TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ�����PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
       ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* �쳣��Ϣ, ֱ�����û�����ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
             �յ�ID_APP_ESM_PDP_MODIFY_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU        *pstEsmPdpModifyCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstEsmPdpModifyCnf                  = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣȫ����״̬��������ʱ��*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    if (APP_SUCCESS == pstEsmPdpModifyCnf->ulRslt)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF�¼� */
        TAF_APS_SndPdpModifyCnf(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ��������벻����ϵͳ, ����޸�������ֹ */
        if (APP_ERR_SM_SUSPENDED != pstEsmPdpModifyCnf->ulRslt)
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
            TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpModifyCnf->ulRslt));

            /* ֹͣȫ����״̬��������ʱ��*/
            TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���2״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
        }
        else
        {
            /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : zhangyizhan 60575
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif
    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /* ��GU�����·���MODIFY */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /*Lģ�� ,����Ҫ����,������L4A�Ļظ�,״̬�ص�
          TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* 1Xģʽ�£�����ȥ����, hrpd����EHSM���б���ȥ���� */
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /* ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ͬ��PDP״̬&��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                 SM_ESM_PDP_OPT_DEACTIVATE);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)

        /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
        }
#endif

        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpTransId)
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
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnfSuspend:rev msg err!");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend(
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend(
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
    else if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnfSuspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend
 ��������  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND��״̬��
             �յ�TI_TAF_APS_WAIT_MS_MODIFYING_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ�¼� */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode
 ��������  : MODIFYING��״̬���յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��29��
    ��    ��   : z60575
    �޸�����   : PS�ںϼ�������޸�
  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg                           = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ESM����modify���� */
    TAF_APS_SndEsmPdpModifyReq(pstCallModifyReq);

    /* ����PDP������� */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_SUCCESS);

    /* ��״̬Ǩ����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF);

    /* ���ڿ���GU��LTE�䷴������л�������п��ܶ�ʱ��֮ǰ�Ѿ��������˴�����
       ���������ֻ�ж�ʱ��δ����ʱ������ */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_MODIFYING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* �𱣻���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                           TI_TAF_APS_MS_MODIFYING_LEN,
                           ucPdpId);
    }

    return;
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

