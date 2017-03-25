/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdPreProcTbl.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : 1X SDԤ����table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdPreProcTbl.h"
#include  "CnasXsdPreProcAct.h"
#include  "CnasXsdTimer.h"
#include  "CnasXsdFsmMainTbl.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdPreProcAct.h"
#include  "xsd_mscc_pif.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include "PsRrmInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PRE_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* Ԥ����״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXsdPreFsmDesc;

/* Ԥ�������Ϣ������ */
NAS_ACT_STRU g_astCnasXsdPreProActTbl[] =
{
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                      CNAS_XSD_RcvSliceReverseProtectTimerExpired_PreProc),

#ifdef DMT
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_TEST_CFG_REQ,
                      CNAS_XSD_RcvXsdTestCfgREQ_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ,
                      CNAS_XSD_RcvXsdMofiyPrlSysRecordReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ,
                      CNAS_XSD_RcvXsdMofiyPrlHeadInfoReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ,
                      CNAS_XSD_RcvXsdMofiyPrlAcqRecordReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ,
                      CNAS_XSD_RcvXsdMofiyOocScanIntervalReq_PreProc),
#endif

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_START_NTF,
                      CNAS_XSD_RcvMsccMoCallStartNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_SUCCESS_NTF,
                      CNAS_XSD_RcvMsccMoCallSuccessNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CFREQLOCK_NTF,
                      CNAS_XSD_RcvMsccCFreqLockSetNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CDMACSQ_SET_REQ,
                      CNAS_XSD_RcvMsccCdmaCsqSetReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SET_SIGNAL_QUALITY_CNF,
                      CNAS_XSD_RcvCasCdmaCsqSetCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SIGNAL_QUALITY_IND,
                      CNAS_XSD_RcvCasCdmaCsqInd_PreProc),
#if 0
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_NEGATIVE_SYSTEM_QUERY_IND,
                      CNAS_XSD_RcvCasNegativeSystemQueryInd_PreProc),
#endif
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYNC_TIME_IND,
                      CNAS_XSD_RcvCas1xSyncTimeInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYS_CFG_REQ,
                      CNAS_XSD_RcvMsccSysCfgReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYS_CFG_CNF,
                      CNAS_XSD_RcvCas1xSysCfgCnf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_HANDSET_INFO_QRY_REQ,
                      CNAS_XSD_RcvMsccHandsetInfoQry_PreProc),
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_IND,
                      CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc),
    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XSD_RcvRrmStatusInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_BEGIN_SESSION_NOTIFY,
                      CNAS_XSD_RcvMsccBeginSessionNotify_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_SESSION_NOTIFY,
                      CNAS_XSD_RcvMsccEndSessionNotify_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndCallBackNtf_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiCallBackModeTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiCallBackSrchTimerExpired_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SET_CSIDLIST_REQ,
                      CNAS_XSD_RcvMsccCSidListReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CAS_STATE_IND,
                      CNAS_XSD_RcvCasStateInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_AVAILABLE_CAMP_QUERY_REQ,
                      CNAS_XSD_RcvCasAvailableCampQueryReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_XREG_XSD_REG_SUCCESS_IND,
                      CNAS_XSD_RcvXregRegSuccessInd_PreProc),
};

/* Ԥ�������Ϣ״̬�� */
NAS_STA_STRU g_astCnasXsdPreStaTbl[] =
{
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_PREPROC,
                      g_astCnasXsdPreProActTbl)
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetPreProcessStaTblSize
 ��������  : ��ȡԤ����״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:Ԥ����״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetPreProcessStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdPreStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetPreFsmDescAddr
 ��������  : ��ȡԤ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��Ԥ����״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU *CNAS_XSD_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdPreFsmDesc);
}


/*lint -save -e958*/


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



