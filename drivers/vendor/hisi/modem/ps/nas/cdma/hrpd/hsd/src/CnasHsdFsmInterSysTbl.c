/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmInterSysTbl.c
  �� �� ��   : ����
  ��    ��   : z00316370
  ��������   : 2015��06��03��
  ��������   : HRPD L2 ��ϵͳ״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmInterSys.h"
#include "CnasHsdFsmInterSysTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "CnasHsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "CnasHsdSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_INTER_SYS_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS HSD״̬������:INTER_SYS��״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasHsdInterSysFsmDesc;

/* CNAS_HSD_INTER_SYS_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasHsdInterSysInitActTbl[] =
{
    /* ��LTE�л���HRPD */
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF,
                      CNAS_HSD_RcvHsdIratFromLteNtf_InterSys_Init),

    /* ��HRPD�л���LTE */
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_IND,
                     CNAS_HSD_RcvCasSuspendInd_InterSys_Init),
};

/* �л���HRPDϵͳʱ�ȴ�CAS�ϱ�Ohm״̬�� */
NAS_ACT_STRU g_astCnasHsdInterSysWaitOhmIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSP,
                      ID_CAS_CNAS_HRPD_OVERHEAD_MSG_IND,
                      CNAS_HSD_RcvCasOhmInd_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_OHM_IND,
                      CNAS_HSD_RcvTiWaitCasOhmIndExpired_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitCasOhmInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitCasOhmInd),

    /* ������SYS_CFG���������̣����ÿ���SYS_CFG */

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitCasOhmInd),
};

NAS_ACT_STRU g_astCnasHsdInterSysWaitIratOrResumeActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF,
                     CNAS_HSD_RcvCasIratToLte_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_RESUME_IND,
                     CNAS_HSD_RcvCasResumeInd_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND,
                      CNAS_HSD_RcvTiWaitIratOrResumeExpired_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                      CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitIratOrResume),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitIratOrResume),
};

NAS_ACT_STRU g_astCnasHsdInterSysWaitSuspendRelCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_SUSPEND_REL_CNF,
                     CNAS_HSD_RcvCasSuspendRelCnf_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF,
                     CNAS_HSD_RcvCasIratToLte_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_HALMP,
                     ID_CAS_CNAS_HRPD_RESUME_IND,
                     CNAS_HSD_RcvCasResumeInd_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF,
                     CNAS_HSD_RcvTiWaitSuspendRelCnfExpired_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_POWER_OFF_REQ,
                     CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_MSCC,
                     ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ,
                     CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitSuspendRelCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_NETWORK_LOST_IND,
                      CNAS_HSD_RcvCasNetworkLost_InterSys_WaitSuspendRelCnf),
};

/* INTER_SYS״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasHsdInterSysStaTbl[] =
{
    /*****************������ϵͳ��ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_INIT,
                      g_astCnasHsdInterSysInitActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND,
                      g_astCnasHsdInterSysWaitOhmIndActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND,
                      g_astCnasHsdInterSysWaitIratOrResumeActTbl),

    NAS_STA_TBL_ITEM( CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF,
                      g_astCnasHsdInterSysWaitSuspendRelCnfActTbl),

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetInterSysStaTblSize
 ��������  : ��ȡInterSys״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:InterSys״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetInterSysStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdInterSysStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetInterSysFsmDescAddr
 ��������  : ��ȡInterSys״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ����ϵͳ״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetInterSysFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdInterSysFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



