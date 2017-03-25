/******************************************************************************

                   ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmCdataEstingTbl.c��
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��10��14��
  ����޸�   :
  ��������   : DORMANT״̬�µ�״̬����
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00213812
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
#include "ehsm_aps_pif.h"

#endif


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_ESTING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/* TAF APS״̬������:CDATA ESTIVATING ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataEstingFsmDesc;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

/* TAF_APS_CDATA_ESTING_SUBSTA_INIT������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvPsCallOrigReq_CdataEsting_Init),

    /* Dormant״̬��ȥ��������ȥ�����״̬��ȥ�Ƚ��� */

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(UEPS_PID_CDS,
                     ID_CDS_APS_CDATA_SERVICE_IND,
                     TAF_APS_RcvCdsServiceInd_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_RECONN_IND,
                     TAF_APS_RcvPppReConnInd_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvPppDialOrigReq_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ,
                     TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND,
                     TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccOrigCallCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_ORIG_DATA_CALL_CNF,
                     TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccOrigCallCnf),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccSoConnectedActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_SERVICE_CONNECT_IND,
                     TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccSoConnected),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccAnsCallCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_ANSWER_DATA_CALL_CNF,
                     TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccCallConnectedIndActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_CONN_IND,
                     TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitIntervalRedialActTbl[]   =
{
    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                     TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial),


    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_CONNECT_IND,
                     TAF_APS_RcvHsmConnectInd_CdataEsting_WaitRedial),
    TAF_ACT_TBL_ITEM(WUEPS_PID_MMA,
                     ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND,
                     TAF_APS_RcvMmaHrpdDataCallSysAcqInd_CdataEsting_WaitRedial),

};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitHsmActCnfActTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_ORIG_CNF,
                     TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitHsmOrigCnf),

};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitEhsmPdnActCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_ACTIVATE_CNF,
                     TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf),

};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitEhsmPdnAttachCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_ATTACH_CNF,
                     TAF_APS_RcvEhsmPdnAttachCnf_CdataEsting_WaitEhsmAttachCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmAttachCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmAttachCnf),

};


/* TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubstaSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND,
                     TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend),

};


/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitPppActCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_RECONN_IND,
                     TAF_APS_RcvPppReConnInd_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_IND,
                     TAF_APS_RcvHsmDiscInd_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitPppActCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitPppActCnf),
};

TAF_STA_STRU g_astTafApsCdataEstingStaTbl[] =
{
    /*****************����TAF_APS_MS_ACTIVATING_SUBSTA_INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_INIT,
                      g_astTafApsCdataEstingSubStaInitTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitXccOrigCallCnfActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED,
                      g_astTafApsCdataEstingSubStaWaitXccSoConnectedActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitXccAnsCallCnfActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND,
                      g_astTafApsCdataEstingSubStaWaitXccCallConnectedIndActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL,
                      g_astTafApsCdataEstingSubStaWaitIntervalRedialActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitHsmActCnfActTbl ),
    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF,
                      g_astTafApsCdataEstingSubStaWaitEhsmPdnActCnfActTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF,
                      g_astTafApsCdataEstingSubStaWaitEhsmPdnAttachCnfActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND,
                      g_astTafApsCdataEstingSubstaSuspendActTbl ),

    /*****************����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF,
                      g_astTafApsCdataEstingSubStaWaitPppActCnfActTbl ),
};

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCdataEstingStaTblSize
 ��������  : ��ȡCDATA ESTING״̬���Ĵ�С
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_GetCdataEstingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataEstingStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCdataEstingFsmDescAddr
 ��������  : ��ȡCDATA ESTIVATING״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_FSM_DESC_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_APS_GetCdataEstingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataEstingFsmDesc);
}


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



