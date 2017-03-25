/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmMainTbl.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��09��
  ��������   : HRPD L1��״̬��table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��09��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasHsdFsmMain.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdSndInternalMsg.h"
#include "CnasHsdTimer.h"
#include "hsd_mscc_pif.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "cas_hrpd_overheadmsg_nas_pif.h"
#include "cas_hrpd_idlestate_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS HSD ��״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasHsdMainFsmDesc;

/* HSD L1 null״̬���¼������ */
NAS_ACT_STRU g_astCnasHsdNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF,
                      CNAS_HSD_RcvSwitchOnRsltCnf_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvPowerOffReq_Null),
};

/* HSD L1 INACTIVE״̬���¼������ */
NAS_ACT_STRU g_astCnasHsdInactiveActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Inactive),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_HSD_START_REQ,
                      CNAS_HSD_RcvStartReq_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_REQ_IND,
                      CNAS_HSD_RcvPilotSearch_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_HSD_RcvSysAcqReq_Inactive),

    /* �ڻ��ģʽ��1X��HSD����1X�����ɹ���Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ,
                     CNAS_HSD_RcvCasSubnetIdChkReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF,
                     CNAS_HSD_RcvCasIratFromLteNtf_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF,
                     CNAS_HSD_RcvInterSysRsltCnf_Inactive),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_Deactive),
};

/* HSD L1 initial״̬���¼������ */
NAS_ACT_STRU g_astCnasHsdInitialActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF,
                     CNAS_HSD_RcvSysAcqRsltCnfProc_Initial),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ,
                     CNAS_HSD_RcvInternalSysAcqReq_Initial),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),
};

/* HSD L1 idle״̬���¼������ */
NAS_ACT_STRU g_astCnasHsdIdleActTbl[] =
{
    /* �û����������� */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_Idle),

    /* �ڻ��ģʽ��1X��HSD����1X�����ɹ���Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLostIndProc_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_IND,
                     CNAS_HSD_RcvCasSuspendInd_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF,
                     CNAS_HSD_RcvInterSysRsltCnf_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_SESSION_NEG_RESULT_IND,
                      CNAS_HSD_RcvHsmSessionNegResultInd_Idle),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_CONN_OPEN_IND,
                      CNAS_HSD_RcvHsmConnOpenInd_Idle),
};

/* HSD L1 OOC״̬���¼������ */
NAS_ACT_STRU g_astCnasHsdOocActTbl[] =
{
    /* �û����������� */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvPowerOffReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF,
                     CNAS_HSD_RcvPowerOffRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailTimerExpired_Ooc),

    /* �ڻ��ģʽ��1X��HSD����1X�����ɹ���Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_1X_SYS_CHANGE_IND,
                     CNAS_HSD_Rcv1xSysChgInd_Ooc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_MRU0_TIMER,
                      CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvPowerSaveReq_L1Main),

    NAS_ACT_TBL_ITEM(UEPS_PID_HSD,
                     ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF,
                     CNAS_HSD_RcvPowerSaveRsltCnf_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_HSD_RcvRrmStatusInd_Ooc),
};

/* HSD L1 ��״̬��״̬����� */
NAS_STA_STRU g_astCnasHsdL1MainStaTbl[] =
{
    /*****************���弰�ػ���������ʼ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_NULL,
                      g_astCnasHsdNullActTbl ),

    /*****************������HRPD����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_INACTIVE,
                      g_astCnasHsdInactiveActTbl),

    /*****************����ϵͳѡ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_INITIAL,
                      g_astCnasHsdInitialActTbl ),

    /*****************������פ��������פ��ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_IDLE,
                      g_astCnasHsdIdleActTbl ),

    /*****************���������κ�����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_L1_STA_OOC,
                      g_astCnasHsdOocActTbl )
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetL1MainStaTblSize
 ��������  : ��ȡHRPD HSD��״̬��״̬���С
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����HSD��״̬��״̬��size
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��12��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMainFsmDescAddr
 ��������  : ��ȡMAIN״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��MAIN״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_HSD_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdMainFsmDesc);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



