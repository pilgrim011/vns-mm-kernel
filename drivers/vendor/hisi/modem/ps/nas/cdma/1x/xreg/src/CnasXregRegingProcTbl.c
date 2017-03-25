/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregRegingProcTbl.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : 1X SD L2����״̬���¼���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXregRegingProcTbl.h"
#include "CnasXregSndInternalMsg.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "CnasXregTimer.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_REGING_PROC_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XREG״̬������:�ػ���״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasXregRegingFsmDesc;

/* CNAS_XREG_REGING_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasXregRegingInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_Reging_Init),
};

/* CNAS_XREG_REGING_WAIT_EST_CNF������ */
NAS_ACT_STRU g_astCnasXregRegingWaitEstCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_ABORT_FSM_REQ,
                      CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_EST_CNF,
                      CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_REG_ABORT_IND,
                      CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ESTCNF_PT,
                      CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf),
};

/* CNAS_XREG_REGING_WAIT_ABORT_IND������ */
NAS_ACT_STRU g_astCnasXregRegingWaitAbortIndActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_REG_ABORT_IND,
                      CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_ABORTCNF_PT,
                      CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf),
};

/* Reging״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasXregRegingStaTbl[] =
{
    /*****************���忪����ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_STA_INIT,
                      g_astCnasXregRegingInitActTbl),

    /*****************����ȴ�XREG�ȴ�EST�ظ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_WAIT_EST_CNF,
                      g_astCnasXregRegingWaitEstCnfActTbl ),

    /*****************����ȴ�XREG�ȴ�ABORT�ظ���Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_REGING_WAIT_ABORT_IND,
                      g_astCnasXregRegingWaitAbortIndActTbl)
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetRegingStaTblSize
 ��������  : ��ȡ����״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:����״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetRegingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregRegingStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetRegingFsmDescAddr
 ��������  : ��ȡ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ�򿪻�״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetRegingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregRegingFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



