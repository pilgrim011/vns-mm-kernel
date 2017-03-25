/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUtranCtrlFsmPlmnSelectionTbl.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2012��7��12��
  ����޸�   :
  ��������   : UTRAN����ģ��״̬ת�Ʊ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��4��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmPlmnSelection.h"
#include "MsccMmcInterface.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* UTRANCTRLģ���ѡ��״̬�� */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlPlmnSelectionFsmDesc;

/**************************************************************************/
/* ����״̬��������� */
/**************************************************************************/

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init),


    /* �յ�MMC���͵���������W��Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init),


    /* �յ�MMC���͵���������TDS��Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_TDS_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init),

    /* �յ�WAS�������ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init),

    /* ����ʱ�յ�WAS�Ľ���㸴λ��Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init),

    /* �յ�TD�������ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfSearchTDActTbl[]   =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

 /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),
 /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfSearchWActTbl[]   =
{

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),
   /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),
   /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
   /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf),

};



/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    /* �쳣�ظ���Ϣ���� */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ,
                     NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf),


    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                     ID_MSCC_MMC_POWER_OFF_REQ,
                     NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),
   /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf),

};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfActTbl[]   =
{

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),

     /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf),

     /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),

#endif
     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfBackTDActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                     ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                     NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),

     NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD),
};

/* NAS_UTRANCTRL_PLMN_SELECTION_STA_TDRRC_SUSPEND_CNF_BACK_W ������ */
NAS_ACT_STRU        g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnBackWfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_POWER_OFF_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_SYS_CFG_SET_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_LIST_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
#if (FEATURE_ON == FEATURE_CSG)
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_CSG_LIST_ABORT_REQ,
                      NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                       ID_MSCC_MMC_PLMN_USER_RESEL_REQ,
                       NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf),
   /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW),
};



/* ����״̬���������Ϣ ״̬�� */
NAS_STA_STRU        g_astNasUtranCtrlPlmnSelectionStaTbl[]   =
{
    /* ����״̬����ʼ��״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT,
                      g_astNasUtranCtrlPlmnSelectionInitActTbl ),

    /* ����״̬���ȴ�was����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfSearchTDActTbl ),

    /* ����״̬���ȴ�TDRRC����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfSearchWActTbl ),

    /* ����״̬���ȴ�was����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfActTbl ),

    /* ����״̬���ȴ�TDRRC����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnfActTbl ),

    /* ����״̬���ȴ�WAS�����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnSearchCnfActTbl ),

    /* ����״̬���ȴ�TDRRC�����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnSearchCnfActTbl ),

    /* ����״̬���ȴ�WASֹͣ�����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitWasPlmnStopCnfActTbl ),

    /* ����״̬���ȴ�TDRRCֹͣ�����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF,
                      g_astNasUtranCtrlPlmnSelectionWaitTdPlmnStopCnfActTbl ),

    /* ����״̬���ȴ��ص�TDʱWAS�Ĺ���ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD,
                      g_astNasUtranCtrlPlmnSelectionWaitWasSuspendCnfBackTDActTbl ),

    /* ����״̬���ȴ��ص�WʱTDRRC����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W,
                      g_astNasUtranCtrlPlmnSelectionWaitTdSuspendCnBackWfActTbl ),
};

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetPlmnSelectionStaTblSize
 ��������  : ��ȡ���������״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:���������״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetPlmnSelectionStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlPlmnSelectionStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr
 ��������  : ��ȡ���������״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ�����������״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlPlmnSelectionFsmDesc);
}
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
