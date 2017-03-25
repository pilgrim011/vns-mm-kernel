/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccPreProcTbl.c
  �� �� ��   : ����
  ��    ��   : Y00213812
  ��������   : 2014��06��27��
  ��������   : 1X CC(call control)ģ�������ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "CnasXregPreProcTbl.h"
#include "CnasXregFsmMainTbl.h"
#include "CnasXregTimer.h"
#include "CnasXregSndInternalMsg.h"
#include "xsd_xreg_pif.h"
#include "CnasXregProcess.h"
#include "PsRrmInterface.h"
#include "UsimPsInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_PRE_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* Ԥ����״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXregPreFsmDesc;

/* ����״̬���������Ϣ ������ */
NAS_ACT_STRU        g_astCnasXregPreProcessActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_SYS_INFO_IND,
                      CNAS_XREG_RcvSysInfo_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_POWER_OFF_REQ,
                      CNAS_XREG_RcvPowerOffReq_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_DEREGISTER_IND,
                      CNAS_XREG_RcvXsdDeregisterInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_REDIRECTION_IND,
                      CNAS_XREG_RcvXsdRedirInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_PARA_NOT_CURRENT_IND,
                      CNAS_XREG_RcvNotCurrInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_TMSI_TIMER_EXPIRED_IND,
                      CNAS_XREG_RcvTMSITimeOut_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_UE_STATE_IND,
                      CNAS_XREG_RcvXsdStateInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      CNAS_XREG_RcvOrderRegDataInd_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_T57M,
                      CNAS_XREG_RcvT57TimeOut_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PERIOD_REG,
                      CNAS_XREG_RcvPrdRegTimeout_PreProc),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ZONELIST_PT,
                      CNAS_XREG_RcvZoneListTimeout_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_P_VER_IND,
                      CNAS_XREG_RcvProVerInd_PreProc),

    NAS_ACT_TBL_ITEM( UEPS_PID_RRM,
                      ID_RRM_PS_STATUS_IND,
                      CNAS_XREG_RcvStatusInd_L1Main),

    NAS_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_CDMA_REG_INFO_REPORT_REQ,
                      CNAS_XREG_RcvOmRegReportReq_PreProc),

    NAS_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_STKREFRESH_IND,
                      CNAS_XREG_RcvUsimRefreshInd_PreProc),

    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XREG_RcvUsimReadFileCnf_PreProc),
};

/* ����״̬���������Ϣ ״̬�� */
NAS_STA_STRU        g_astCnasXregPreProcessFsmTbl[]   =
{
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_PREPROC,
                      g_astCnasXregPreProcessActTbl )
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetPreProcessStaTblSize
 ��������  : ��ȡԤ����״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:Ԥ����״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetPreProcessStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregPreProcessFsmTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetPreFsmDescAddr
 ��������  : ��ȡԤ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��Ԥ����״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregPreFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

