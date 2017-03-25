/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmMainTbl.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : XSD L1��״̬��table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXsdFsmMain.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdSndInternalMsg.h"
#include "CnasXsdTimer.h"
#include "xsd_mscc_pif.h"

#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_idlectrl_proc_nas_pif.h"

#include "PsRrmInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XSD ��״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXsdMainFsmDesc;

/* XSD L1 null״̬���¼������ */
NAS_ACT_STRU g_astCnasXsdNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF,
                      CNAS_XSD_RcvSwitchOnRsltCnf_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_Null)
};

/* XSD L1 initial״̬���¼������ */
NAS_ACT_STRU g_astCnasXsdInitialActTbl[] =
{
    /* If XSD receives a Start request from MSCC */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Initial),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvStartReq_Initial),

    /* �û����������� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvInternalSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF,
                      CNAS_XSD_RcvSysAcqRsltCnf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_REDIRECTION_IND,
                      CNAS_XSD_RcvInternalRedirectionInd_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF,
                      CNAS_XSD_RcvRedirectionRsltCnf_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Initial),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_BREAK_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackSrchBreakTimerExpired_Initial),
};

/* XSD L1 idle״̬���¼������ */
NAS_ACT_STRU g_astCnasXsdIdleActTbl[] =
{
    /* �û����������� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvSysDeterminInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvInternalSysAcqReq_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Idle),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Idle),
};

/* XSD L1 OOC״̬���¼������ */
NAS_ACT_STRU g_astCnasXsdOocActTbl[] =
{
    /* �û����������� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvPowerOffReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                      CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_MRU0_TIMER,
                      CNAS_XSD_RcvTiAvailMru0TimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XSD_RcvRrmStatusInd_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccMoCallEndNtf_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackNtf_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvMsccXsdSysAcq_Ooc),
};

/* XSD L1 DEACTIVE Act Table */
NAS_ACT_STRU g_astCnasXsdDeactiveActTbl[] =
{

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                     CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_POWER_OFF_REQ,
                     CNAS_XSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF,
                     CNAS_XSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_POWER_SAVE_REQ,
                     CNAS_XSD_RcvMsccPowerSaveReq_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_XSD_RcvRrmStatusInd_Deactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_XSD_SRV_ACQ_REQ,
                     CNAS_XSD_RcvMsccSrvAcqReq_Deactive),

};


/* XSD L1 ��״̬��״̬����� */
NAS_STA_STRU g_astCnasXsdL1MainStaTbl[] =
{
    /*****************���弰�ػ���������ʼ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_NULL,
                      g_astCnasXsdNullActTbl ),

    /*****************����ϵͳѡ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_INITIAL,
                      g_astCnasXsdInitialActTbl ),

    /*****************������פ��������פ��ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_IDLE,
                      g_astCnasXsdIdleActTbl ),

    /*****************���������κ�����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_OOC,
                      g_astCnasXsdOocActTbl ),

    /*****************���������κ�����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_L1_STA_DEACTIVE,
                      g_astCnasXsdDeactiveActTbl)
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetL1MainStaTblSize
 ��������  : ��ȡ1X XSD��״̬��״̬���С
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����XSD��״̬��״̬��size
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMainFsmDescAddr
 ��������  : ��ȡMAIN״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��MAIN״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XSD_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdMainFsmDesc);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



