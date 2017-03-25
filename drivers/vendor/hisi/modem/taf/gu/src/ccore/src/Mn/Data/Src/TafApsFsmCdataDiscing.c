/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmCdataDiscing.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��10��14��
  ����޸�   :
  ��������   : CdataDiscing״̬����������APSģ�鴦��Ͽ�data call����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��14��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsFsmCdataDiscing.h"
#include  "TafApsFsmCdataDiscingTbl.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "xcc_taf_pif.h"
#include  "MnApsComm.h"
#include  "TafApsSndInternalMsg.h"
#include  "TafApsSndXcc.h"
#include  "TafApsSndPpp.h"
#include  "xcc_aps_pif.h"
#include  "TafApsFsmMainTbl.h"
#include  "TafApsComFunc.h"
#include  "TafApsSndCds.h"
#include  "taf_aps_ppp_pif.h"
#include  "TafApsFsmCdataEstingTbl.h"
#include  "TafApsProcIpFilter.h"
#include  "TafApsSndHsm.h"
#include  "TafApsProcEpdszid.h"
#include  "TafApsSndEhsm.h"
#include  "TafApsSndNd.h"
#include  "TafApsSndDhcp.h"

#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafSdcLib.h"
#include "TafApsSndRlp.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_DISCING_C


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_APS_ProcCdataDisc_CdataDiscing_Init
 ��������  : CDMA��Ӧģ��ȥ�Ͽտ���·
 �������  : TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��17��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing_Init(
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ������״̬ */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_DISCONNECTING);

    switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        case TAF_APS_RAT_TYPE_HRPD:
        

            /* ��HSM������ϢID_APS_HSM_DISC_REQ */
            TAF_APS_SndHsmDiscReq(ucPdpId);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF);

            break;

        case TAF_APS_RAT_TYPE_1X:
            /* ��XCC������ϢID_APS_XCC_HANGUP_DATA_CALL_REQ */
            TAF_APS_SndXccHangUpDataCallReq(pstPdpEntity->stCdataInfo.ucCallId,
                                            enEndReason);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF);

            break;

        case TAF_APS_RAT_TYPE_EHRPD:
            /* EHRPDģʽ�²�����ȥע���������ݵĻص����� */

            /* ��EHSM������ϢID_APS_EHSM_PDN_DEACTIVATE_REQ */
            TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
            TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
            /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
            if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
             && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
            {
                TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }
#endif

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

            break;

        default:
            /* Ǩȥ����Suspend״̬ */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

            break;
    }

    /* ������ʱ��TI_TAF_APS_CDATA_DISCING */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING,
                       TI_TAF_APS_CDATA_DISCING_LEN,
                       ucPdpId);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_INIT״̬��
             �յ�ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��17��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_INIT״̬��
             �յ�ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��17��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulPppDeactTiLen;

    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState      = TAF_APS_GetPdpEntPppState(ucPdpId);
    ulPppDeactTiLen = TAF_APS_GetCdataPppDeactTimerLen();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* ������״̬ */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    /* ����ģʽ����ǰ��PPP״̬�Ǽ���ģ������ڼ�����������ȶϿ�PPP */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
    {
        if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            /* ����PS״̬ */
            TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

            /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

            /* ������ʱ��TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                               ulPppDeactTiLen,
                               ucPdpId);

            return VOS_TRUE;
        }
    }

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEndReq_CdataDiscing_Init
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_INIT״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������


 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �޸��û�ȥ����������Ϣ�����߼�
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulPppDeactTiLen;

    /* ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    ulPppDeactTiLen = TAF_APS_GetCdataPppDeactTimerLen();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* Dormant״̬��ȥ���������Ҫ�Ƚ���·���ɹ� */
    if (TAF_APS_STA_DORMANT == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
    {
        switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            case TAF_APS_RAT_TYPE_HRPD:

                TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_FALSE);

                break;

            case TAF_APS_RAT_TYPE_1X:

                TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallEndReq_CdataDiscing_Init: Wrong RAT type!");
                break;
        }

        /* Dormant״̬��ȥ����ȳ��Խ��� */
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

        /* ������״̬ */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

        /* Dormant״̬��ȥ������Ҫ�Ƚ�����������Ŀ������PPPȥ����Э�̣�����PPPȥ����Э�̵��ܶ�ʱ������ */
        /* ������ʱ��TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                           ulPppDeactTiLen,
                           ucPdpId);

        return VOS_TRUE;
    }

    /* ����ģʽ����ǰ��PPP״̬�Ǽ���ģ������ڼ�����������ȶϿ�PPP */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);
    if ((TAF_APS_CDATA_PPP_STATE_ACTIVE     == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVATING == enPppState))
    {
        if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
            {
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
            }

            /* ������״̬ */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

            /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

            /* ������ʱ��TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                               ulPppDeactTiLen,
                               ucPdpId);

            return VOS_TRUE;
        }
    }

    /* �տ���·�������� */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactNtf_CdataDiscing_Init
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_INIT״̬��
             �յ�ID_PPP_APS_DEACT_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������


 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactNtf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* ������״̬ */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF״̬��
             �յ�ID_XCC_APS_HANGUP_DATA_CALL_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��17��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF״̬��
             �յ�ID_XCC_APS_DATA_CALL_DISC_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��17��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ����ԭ��ֵ��PPP״̬�ж��Ƿ���Ҫ֪ͨPPPֱ�ӶϿ� */
    if ((TAF_XCC_CAUSE_SO_REJ == pstDiscInd->enCause)
      &&(TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_APS_MapXccCause(pstDiscInd->enCause));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��PPP״̬�Ǽ���� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��Ҫ֪ͨPPPȥ���� */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2014��10��17��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf
 ��������  : In TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF
             state, Rcv msg ID_MSG_TAF_PS_EPDSZID_REORIG_REQ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;

    /* Get Pdp Entity */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* If Discing is not caused by ID_MSG_TAF_PS_CALL_END_REQ and ID_PPP_APS_DEACT_NTF, Set  Epdszid Re-orig secne */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) != pstEntryMsg->ulEventType)
     && (TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_NTF)    != pstEntryMsg->ulEventType))
    {
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_ENTER_DORMANT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcCdataDisc_CdataDiscing
 ��������  : CDATA���ݷ���Ͽ��Ĵ���
 �������  : TAF_PS_CAUSE_ENUM_UINT32                enCause
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��30��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU   *pstEndCdmaCall;
    VOS_UINT32                              ulNeedStartTimer;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstEndCdmaCall  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;

    /* �ж��Ƿ�����Dormant TI */
    ulNeedStartTimer  = VOS_FALSE;

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* ������û�����ĹҶϣ��ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
     || ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
      && (TAF_APS_INTER_END_CALL_SCENE_USER_END == pstEndCdmaCall->enEndScene)))
    {
        /* ���õ�ǰ���ݷ���ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_GetCurrPdpEntityRatType());

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL == pstEndCdmaCall->enEndScene))
    {
        /* ����ʱ��Ҫ���û��ϱ�REJ��Ϣ */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));
    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_HANDOFF == pstEndCdmaCall->enEndScene))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ���õ�ǰ���ݷ���ģʽ */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

    }
    else
    {
        if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
        {
            /* ���֮ǰ��Active״̬��20sû������������Dormant״̬����Ҫ����Dormant Timer */
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND) == pstEntryMsg->ulEventType)
            {
                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
                {
                    ulNeedStartTimer = VOS_TRUE;
                }
                else
                {
                    ulNeedStartTimer = VOS_FALSE;
                }
            }

            TAF_APS_PdpEntityEnterDormant(ucPdpId, ulNeedStartTimer);

            /* ����Dormant״̬�󣬴����ڲ���Ϣ�������ز�*/
            if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
            {
                TAF_APS_SndInterEpdszidReOrigReq();

                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            return VOS_TRUE;
        }
        else
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));

        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�ID_HSM_APS_DISC_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf = VOS_NULL_PTR;

    /* ��ȡʵ����Ϣ */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscCnf            = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscCnf->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��PPP״̬�Ǽ���� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��Ҫ֪ͨPPPȥ���� */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�ID_HSM_APS_DISC_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* ��ȡʵ����Ϣ */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd            = (HSM_APS_DISC_IND_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_EHSM_APS_PDN_DEACTIVATE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstDeactCnf;

    /* ��ȡʵ����Ϣ */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    if (EHSM_APS_CAUSE_LAST_PDN == pstDeactCnf->enCause)
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��������PDNȥ���EHSM��ܾ������ݴ��ض�ԭ��ֵ�������⴦����ʱ
           ��ʵ�岻��ʵ��ȥ������ǻ�ˢ�³�Ĭ�ϳ��أ�ʵ��״̬����Ϊ����״̬ */

        /* ˢ�³�Ĭ�ϳ��ص�CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);
        /* ֪ͨEHSM��ǰ��Cidˢ�� */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;

    }
    else if(EHSM_APS_CAUSE_EHRPD_SUSPEND == pstDeactCnf->enCause)
    {
        /* Ǩȥ����Suspend״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

    }
    else
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* �������ӶϿ����� */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֪ͨehsm����ȥ���� */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��6��6��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* �������Ϣ�е�3GPP״̬������ */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType )
    {
        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ���½�ȥ���������ͳ�������������3GPP״̬������ */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
    {
        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ���½��ڲ�ȥ���������ͳ�������������3GPP״̬������ */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);

    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend
 ��������  : �յ�ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��16��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* ��EHSM������ϢID_APS_EHSM_PDN_DEACTIVATE_REQ */
    TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
    TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
     && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��6��6��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��06��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        /* ��EHSM������ϢID_APS_EHSM_PDN_DEACTIVATE_REQ */
        TAF_APS_SndEhsmPdnDeactReq(ucPdpId);

        /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

        /* �������Ϣ�е�3GPP״̬������ */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
        {
            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            /* ���½�ȥ���������ͳ�������������3GPP״̬������ */
            TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        }

        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
        {
            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            /* ���½��ڲ�ȥ���������ͳ�������������3GPP״̬������ */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);
        }
    }
    else
    {
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
        }

        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcPppDeactInd_CdataDiscing
 ��������  : ���������л��ߵȴ�PPPȥ����Э��ʱ�յ�PPP��������PPP Deact Ind��
             Ϣ
 �������  : VOS_UINT8                           ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcPppDeactInd_CdataDiscing(
    VOS_UINT8                           ucPdpId
)
{
    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF״̬���յ���ϢID_PPP_APS_DEACT_CNF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ȡPdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
    if (VOS_OK != pstDeactCnf->ulResult)
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* �����ǰ��·�����ڣ����ڽ��������У�����Ҫ��ȥ�Ͽտ���· */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* �������ӶϿ����� */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF���յ���ϢID_PPP_APS_DEACT_NTF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡPdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �����ǰ��·�����ڣ����ڽ��������У�����Ҫ��ȥ�Ͽտ���· */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* ֹͣ���̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* �������ӶϿ����� */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode
 ��������  : ȥ������������Ҫ����HRPD�����Ͻ����ɹ�����·���ڲ�����PPPȥ����Э��
 �������  : VOS_UINT8                           ucPdpId
             VOS_UINT32                          ulNeedSearchSys
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulDoQuickAcq
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;
    VOS_UINT32                          ulClDelaySearch;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ���Ų��� */
    pstPdpEntity->stCdataInfo.ucCallId = ucPdpId + 1;

    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

    /* ����30s�ز����ڶ�ʱ�� */
    if (TAF_APS_TIMER_STATUS_RUNING != TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId))
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN,
                           ucPdpId);
    }

    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
    {
        /* ���ͼ������� */
        TAF_APS_SndHsmOrigReq(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);
    }
    else
    {
        enSdcServiceStatus = TAF_APS_GetHrpdServiceStatus();
        ulClDelaySearch    = TAF_APS_GetClDelaySearch();

        /* Send Redial Ntf to MMA */
        if ((VOS_FALSE == ulClDelaySearch)
         && ((VOS_TRUE == ulDoQuickAcq) || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enSdcServiceStatus)))
        {
            /* ����HRPD������MRU[0] */
            TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                     0,
                                                     TAF_MMA_DO_NORMAL_DATA_CALL,
                                                     TAF_PS_CAUSE_HRPD_NO_SERVICE);
        }

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode
 ��������  : ȥ������������Ҫ����1X�����Ͻ����ɹ�����·���ڲ�����PPPȥ����Э��
 �������  : VOS_UINT8                           ucIsDormDataCall
             VOS_UINT8                           ucDrsFlg
             VOS_UINT8                           ucHrpdHandOff1xFlg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* Get Pdp Fsm Entity */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId         = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo             = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg         = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall = ucIsDormDataCall;
    pstPdpEntity->stCdataInfo.ucIsL2ErrReOrig  = VOS_FALSE;
    pstPdpEntity->stCdataInfo.ucReOrigCount    = 0;

    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    if (TAF_APS_TIMER_STATUS_RUNING != TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId))
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN, ucPdpId);
    }

    /* �ж��Ƿ���Է���1X���� */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
    {
        /* ���ͼ���������XCC */
        TAF_APS_SndXccOrigDataCallReq(ucPdpId, ucHrpdHandOff1xFlg);

        /* ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF);
    }
    else
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode
 ��������  : 1X�����·����ز�
 �������  : VOS_UINT8                           ucIsDormDataCall
             VOS_UINT8                           ucDrsFlg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ȡAPSʵ������ */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId              = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo                  = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg              = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall      = ucIsDormDataCall;

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    /* ��1X�������ݷ������ӽ������� */
    TAF_APS_SndXccOrigDataCallReq(ucPdpId, VOS_FALSE);

    /* ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF״̬���յ�PPPͨ
             ֪��������Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* ���֧��HYBRIDģʽ��������HPRDģʽ�½��г��Խ��� */
    if (VOS_FALSE == TAF_SDC_Is1xOnlyMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                /* DOǿ�ź�ȥHRPD������DO���ź�ȥ1X���� */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /* DOǿ�ź�ȥHRPD������DO���ź�ȥ1X���� */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* �����֧��Hybrid����ֻ֧��1X������1X�³��Խ��� */
        TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF״̬���յ���ϢID_XCC_APS_DATA_CALL_DISC_IND
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity         = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd           = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* SO Rej ��Ҫ���⴦������ȥ���� */
    if (TAF_PS_CAUSE_XCC_AS_SO_REJ == pstPdpEntity->enCause)
    {
        /* ֹͣ���̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ֮ǰ��ȥ����������δ������PPPȥ����Э����δ��ɣ���ʱ�ϱ�ȥ�����¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }
    else
    {
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

        /* ֪ͨPPP��ǰ��·������ */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        /* ״̬����ά����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF */
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF״̬���յ���ϢID_HSM_APS_DISC_IND��
             ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd            = (HSM_APS_DISC_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* ֪ͨPPP��ǰ��·������,APS��״̬����״̬ά�ֲ��� */
    TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF״̬���յ���ϢTI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡPdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֪ͨPPPֱ�ӶϿ� */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* �����ǰ��·�����ڣ����ڽ��������У�����Ҫ��ȥ�Ͽտ���· */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* �������ӶϿ����� */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF���յ���ϢID_XCC_APS_ORIG_DATA_CALL_CNF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    pstOirgCallCnf  = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (TAF_XCC_CAUSE_SUCCESS == pstOirgCallCnf->enRslt)
    {
        TAF_APS_SetPdpEntConRef(ucPdpId, pstOirgCallCnf->ucConRef);
        TAF_APS_SetPdpEntConnectId(ucPdpId, pstOirgCallCnf->ucConnectId);

        /* ����ز����ڶ�ʱ�������У���Ҫ�ر��ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ��¼��ǰ�������ݷ����ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_1X);

        /* Ǩ��TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }
    else
    {
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstOirgCallCnf->enRslt);

        pstPdpEntity->sRssi   = pstOirgCallCnf->sRssi;

        /* �ж��Ƿ���Ҫ����Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_1X))
        {
            TAF_APS_CdataOrigRedialCount(ucPdpId, pstOirgCallCnf->enFailLayer);

            if (VOS_TRUE == TAF_APS_IsNeedRedial1xSystemAcquire(pstPdpEntity->enCause, pstPdpEntity->sRssi))
            {
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                         0,
                                                         TAF_MMA_1X_NORMAL_DATA_CALL,
                                                         pstPdpEntity->enCause);
            }

            /* ��SILENT_REDIAL_WAIT 4s��ʱ��������˶�ʱ����ʱ���᳢���ز� */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* Ǩ��TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL��״̬ */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
            {
                /* ֹͣPPPȥ����Э�����̶�ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
            }

            /* ֹͣ����ͳ�� */
            TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            /* Dormant״̬��ȥ������Ľ���/PPP�������ؽ����������ʧ�ܣ���Ҫ֪ͨPPP����ȥ����*/
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* ���û�����DEACTIVE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ����IP���� */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF��״̬���յ���ϢID_PPP_APS_DEACT_CNF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* ���֮ǰ��δ�����PPPȥ����Э�̣��򲻴���return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ֹͣPPPȥ����Э�����̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF��״̬���յ���Ϣ
             ID_PPP_APS_DEACT_NTF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡPdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF��״̬���յ���ʱ����ϢTI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡPdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ȥ����ı�����ʱ����ʱ��PPP��״ֻ̬������ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF��״̬���յ���ϢID_HSM_APS_ORIG_CNF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    pstOirgCallCnf  = (HSM_APS_ORIG_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (HSM_APS_CAUSE_SUCCESS == pstOirgCallCnf->enResult)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ��¼��ǰ�������ݷ����ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* ��·�ؽ�����PPPCģ�鴥����֮ǰ��PPPȥ����Э�̻�δ����,֪ͨPPPC��·���ؽ��ɹ� */
            TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);
        }
        else
        {
            /***************************************************************************/
            /*   Dormant״̬��ȥ�����Ҫ����·�����ɹ�֮���ٷ���PPPȥ����Э������  */
            /***************************************************************************/

            /* ����ID_APS_PPP_DEACT_REQ��Ϣ��PPPģ�� */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* ����Ҫ������TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ����֮ǰ�����Ϣ�Ѿ����� */
        }

        /* Ǩ��TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);
    }
    else
    {
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstOirgCallCnf->enResult);

        /* �ж��Ƿ���Ҫ����Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_HRPD))
        {
            /* ��SILENT_REDIAL_WAIT 4s��ʱ��������˶�ʱ����ʱ���᳢���ز� */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL��״̬ */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
            {
                /* ֹͣPPPȥ����Э�����̶�ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
            }

            /* ֹͣ����ͳ�� */
            TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

            /* Dormant״̬��ȥ������Ľ���/PPP�������ؽ����������ʧ�ܣ���Ҫ֪ͨPPP����ȥ����*/
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* ���û�����DEACTIVE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ����IP���� */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF��״̬���յ���ϢID_PPP_APS_DEACT_CNF
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* ���֮ǰ��δ�����PPPȥ����Э�̣��򲻴���return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ֹͣPPPȥ����Э�����̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF��״̬���յ���Ϣ-
             ID_PPP_APS_DEACT_NTF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡPdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF��״̬���յ���ʱ��TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ��Ϣ
             �Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡPdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ȥ����ı�����ʱ����ʱ��PPP��״ֻ̬������ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED���յ�
             ��ϢID_XCC_APS_DATA_SERVICE_CONNECT_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstSoInd;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();
    pstSoInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

    /* ����SO��CONREF��PPP ID��Ϣ */
    TAF_APS_SetPdpEntSo(ucPdpId, pstSoInd->enSo);
    TAF_APS_SetPdpEntConRef(ucPdpId, pstSoInd->ucConRef);

    /* ����SR ID��Ϣ */
    TAF_APS_SetPdpEntSrId(ucPdpId, pstSoInd->ucSrId);

    /* ֪ͨRLP����ʼ�� */
    TAF_APS_SndRlpInitReq(ucPdpId);

    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��·�ؽ�����PPPCģ�鴥����֮ǰ��PPPȥ����Э�̻�δ����,֪ͨPPPC��·���ؽ��ɹ� */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);
    }
    else
    {
        /***************************************************************************/
        /*   Dormant״̬��ȥ�����Ҫ����·�����ɹ�֮���ٷ���PPPȥ����Э������  */
        /***************************************************************************/
        /* ����ID_APS_PPP_DEACT_REQ��Ϣ��PPPģ�� */
        TAF_APS_SndPppDeactReq(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);
    }

    /* Ǩ��TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF��״̬ */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬�յ���
             ϢID_XCC_APS_DATA_CALL_DISC_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���û�����DEACTIVE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
    {
        /* ֹͣPPPȥ����Э�����̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
    }

    if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* PPP��״̬��Ҫ��TAF_APS_CDATA_PPP_STATE_ACTIVE / TAF_APS_CDATA_PPP_STATE_DEACTIVATING������� */
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* �˳���״̬״̬�� */
    TAF_APS_QuitCurrSubFsm();

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬�յ���
             ϢID_PPP_APS_DEACT_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* ���֮ǰ��δ�����PPPȥ����Э�̣��򲻴���return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ֹͣPPPȥ����Э�����̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬�յ���
             ϢID_PPP_APS_DEACT_NTF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬�յ�TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ��
             Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡPdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ȥ����ı�����ʱ����ʱ��PPP��״ֻ̬������ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* PPP��·�Ͽ�����ȥ�Ͽ��տ���· */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL���յ�
             TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlag;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;

    ucDrsFlag           = VOS_TRUE;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();
    enSdcServiceStatus  = TAF_APS_GetHrpdServiceStatus();

    if ((VOS_FALSE == TAF_APS_GetClDelaySearch())
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enSdcServiceStatus))
    {
        /* �ж��Ƿ���Է���HRPD���� */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
        {
            /* Send Orig Data Call Req To HSM */
            TAF_APS_SndHsmOrigReq(ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }
            TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

            /* Sub Fsm State transfer to TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);

            return VOS_TRUE;
        }

        /* �ж��Ƿ���Է���1X���� */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
        {
            ucDrsFlag        = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
            ucIsDormDataCall = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

            TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(ucIsDormDataCall, ucDrsFlag);

            return VOS_TRUE;
        }
    }

    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                              ucPdpId,
                              &ulRemainTimeLen);

    if (ulRemainTimeLen >= TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
    else
    {
        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֪ͨ����ģ��������� */
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ���û�����DEACTIVE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            /* ֹͣPPPȥ����Э�����̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
        }

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL���յ���ϢID_PPP_APS_DEACT_CNF�Ĵ�
             ��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;

    /* ��ʼ�� */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* ���֮ǰ�Ѿ����͹�PPPȥ����Э�̣��������������ֱ��return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ���û�����DEACTIVE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ֹͣPPPȥ����Э�����̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* ֹͣ�ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֹͣ�ز������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

        /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL���յ���ϢID_PPP_APS_DEACT_NTF�Ĵ�
             ��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
    }

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* ���û�����DEACTIVE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ֹͣPPPȥ����Э�����̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* ֹͣ�ز����ڶ�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    /* ֹͣ�ز������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL���յ�
             TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡPdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ȥ����ı�����ʱ����ʱ��PPP��״ֻ̬������ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* ֹͣ����ͳ�� */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* ���û�����DEACTIVE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ֹͣ�ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֹͣ�ز������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial
 ��������  : ��״̬TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL���յ�
             ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��17��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucIsDormDataCall;
    VOS_UINT8                                               ucDrsFlag;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstSvcStaChangeReq = VOS_NULL_PTR;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ��ȡ��Ϣ���� */
    pstSvcStaChangeReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    switch(pstSvcStaChangeReq->enRatType)
    {
        /* �ж�HRPD�з��� */
        case TAF_APS_RAT_TYPE_HRPD:
            /* �ж��Ƿ���Է���HRPD���� */
            if(VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
            {
                /* ֹͣ��ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                /* Send Orig Data Call Req To HSM */
                TAF_APS_SndHsmOrigReq(ucPdpId);

                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
                {
                    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
                }

                TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

                /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);
            }

            break;

        /* �ж�1X���� */
        case TAF_APS_RAT_TYPE_1X:
            /* �ж��Ƿ���Է���1X���� */
            if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
            {
                /* ֹͣ��ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
                {
                    /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                    TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
                }

                ucDrsFlag           = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
                ucIsDormDataCall    = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

                TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(ucIsDormDataCall, ucDrsFlag);
            }

            break;

        case TAF_APS_RAT_TYPE_EHRPD:
        case TAF_APS_RAT_TYPE_LTE:
            /* ֹͣ���̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
            }
            else
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }

            /* �������ӶϿ����� */
            TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            /* ֪ͨ�ⲿģ��PSģʽ�л� */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            break;

        default:
            break;
    }

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
