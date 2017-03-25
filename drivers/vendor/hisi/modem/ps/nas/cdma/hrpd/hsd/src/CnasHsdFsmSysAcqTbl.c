/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmSysAcqTbl.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��17��
  ��������   : HRPD L2 SYSTEM ACQUIRE״̬���¼���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasHsdFsmSysAcq.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasHsdComFunc.h"
#include "CnasHsdSndInternalMsg.h"
#include "hsd_mscc_pif.h"
#include "cas_hrpd_overheadmsg_nas_pif.h"
#include "hsm_hsd_pif.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SYS_ACQ_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS HSD״̬������:SYSTEM ACQUIRE��״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasHsdSysAcqFsmDesc;

/* CNAS_HSD_SYS_ACQ_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasHsdSysAcqInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ,
                      CNAS_HSD_RcvMsccSysAcqReq_SysAcq_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ,
                      CNAS_HSD_RcvHsdSysAcqReq_SysAcq_Init),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF������ */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitCasSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasSysSyncCnf),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF������ */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitCasStopSyncCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_STOP_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvCasSyncCnf_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
                      CNAS_HSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasStopSysSyncCnf),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND������ */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOverheadInd_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_OHM_IND,
                      CNAS_HSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitCasIndProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_PILOT_SEARCH_STOP_IND,
                      CNAS_HSD_RcvCasPilotSearchStopInd_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitCasInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitCasInd),
};

/* CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SESSION_IND������ */
NAS_ACT_STRU g_astCnasHsdSysAcqWaitSessionNegRsltIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_SESSION_NEG_RESULT_IND,
                      CNAS_HSD_RcvSessionNegRsltInd_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND,
                      CNAS_HSD_RcvTiWaitSessionNegIndExpired_SysAcq_WaitSessionNegInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_AVAILABLE_TIMER,
                      CNAS_HSD_RcvTiAvailableTimerExpired_WaitMru0),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_SysAcq_WaitSessionIndProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_SysAcq_WaitSessionInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_CONN_OPEN_IND,
                      CNAS_HSD_RcvHsmConnOpenInd_WaitSessionInd),
};

/* System Acquire״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasHsdSysAcqStaTbl[] =
{
    /*****************����SYSTEM ACQUIRE��ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_INIT,
                      g_astCnasHsdSysAcqInitActTbl),

    /*****************����ȴ�CAS�ظ�ͬ��ȷ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF,
                      g_astCnasHsdSysAcqWaitCasSyncCnfActTbl ),

    /*****************����ȴ�CAS�ظ�ֹͣ����ȷ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF,
                      g_astCnasHsdSysAcqWaitCasStopSyncCnfActTbl),

    /*****************����ȴ�CAS�ϱ�OHM�ϱ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_IND,
                      g_astCnasHsdSysAcqWaitOhmIndActTbl),

    /*****************����ȴ�HSM�ϱ�SESSION̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_SYS_ACQ_STA_WAIT_SESSION_NEG_RSLT_IND,
                      g_astCnasHsdSysAcqWaitSessionNegRsltIndActTbl),
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysAcqStaTblSize
 ��������  : ��ȡSYSTEM ACQUIRE״̬���Ĵ�С
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetSysAcqStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdSysAcqStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysAcqFsmDescAddr
 ��������  : ��ȡSYSTEM ACQUIRE״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetSysAcqFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdSysAcqFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



