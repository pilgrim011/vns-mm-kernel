/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmSysAcqTbl.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��07��28��
  ��������   : 1X SD L2 SYSTEM ACQUIRE״̬���¼���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��28��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXsdFsmSysAcq.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasXsdComFunc.h"
#include "CnasXsdSndInternalMsg.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "cas_1x_control_main_nas_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SYS_ACQ_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XSD״̬������:SYSTEM ACQUIRE��״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasXsdSysAcqFsmDesc;

/* CNAS_XSD_SYS_ACQ_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasXsdSysAcqInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init),
};

/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF������ */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf),
};


/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND������ */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_OHM_IND,
                      CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND,
                      CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_OHM_IND,
                      CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd),
};

/* CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF������ */
NAS_ACT_STRU g_astCnasXsdSysAcqWaitCasStopSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_OFF_REQ,
                      CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                      CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_AVAILABLE_TIMER,
                      CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_POWER_SAVE_REQ,
                      CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_SRV_ACQ_REQ,
                      CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_MO_CALL_END_NTF,
                      CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER,
                      CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_END_EMC_CALLBACK_NTF,
                      CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf),
};


/* System Acquire״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasXsdSysAcqStaTbl[] =
{
    /*****************����SYSTEM ACQUIRE��ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_INIT,
                      g_astCnasXsdSysAcqInitActTbl),

    /*****************����ȴ�CAS�ظ�ͬ��ȷ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF,
                      g_astCnasXsdSysAcqWaitCasSyncCnfActTbl ),

    /*****************����ȴ�CAS�ϱ�OHMָʾ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND,
                      g_astCnasXsdSysAcqWaitCasOhmIndActTbl),

    /*****************����ȴ�CAS�ظ�ֹͣͬ��ȷ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF,
                      g_astCnasXsdSysAcqWaitCasStopSyncCnfActTbl),

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSysAcqStaTblSize
 ��������  : ��ȡSYSTEM ACQUIRE״̬���Ĵ�С
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSysAcqStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdSysAcqStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSysAcqFsmDescAddr
 ��������  : ��ȡSYSTEM ACQUIRE״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XSD_GetSysAcqFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdSysAcqFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



