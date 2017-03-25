/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmPowerOffTbl.c
  �� �� ��   : ����
  ��    ��   : z00316370
  ��������   : 2015��04��09��
  ��������   : HRPD L2 �ػ�״̬��״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��04��09��
    ��    ��   : z00316370
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmPowerSave.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "CnasHsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "hsm_hsd_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_POWER_OFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS HSD״̬������:POWER_SAVE��״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasHsdPowerSaveFsmDesc;

/* CNAS_HSD_POWER_SAVE_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasHsdPowerSaveInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_SAVE_REQ,
                      CNAS_HSD_RcvMsccPowerSaveReq_PowerSave_Init),
};


/* CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_OOC_CNF������ */
NAS_ACT_STRU g_astCnasHsdPowerSavewaitCasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_SUSPEND_CNF,
                      CNAS_HSD_RcvCasSuspendCnf_PowerSave_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF,
                      CNAS_HSD_RcvTiWaitCasSuspendCnfExpired_PowerSave_WaitCasSuspendCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_PowerSave),
};

NAS_ACT_STRU g_astCnasHsdPowerSavewaitHsmPowerSaveCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_POWER_SAVE_CNF,
                      CNAS_HSD_RcvHsmPowerSaveCnf_PowerSave_WaitHsmPowerSaveCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF,
                      CNAS_HSD_RcvTiWaitHsmPowerSaveCnfExpired_PowerSave_WaitHsmPowerSaveCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_RRM,
                     ID_RRM_PS_STATUS_IND,
                     CNAS_HSD_RcvRrmStatusInd_PowerSave),
};

/* POWER_SAVE״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasHsdPowerSaveStaTbl[] =
{

    /*****************����ػ���ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_INIT,
                      g_astCnasHsdPowerSaveInitActTbl),

    /*****************����CAS�ظ�Suspend״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_WAIT_CAS_SUSPEND_CNF,
                      g_astCnasHsdPowerSavewaitCasSuspendCnfActTbl),

    /*****************����CAS�ظ�Suspend״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_SAVE_STA_WAIT_HSM_POWERSAVE_CNF,
                      g_astCnasHsdPowerSavewaitHsmPowerSaveCnfActTbl),

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPowerSaveStaTblSize
 ��������  : ��ȡPowerSave״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:PowerSave״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��09��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetPowerSaveStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdPowerSaveStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPowerSaveFsmDescAddr
 ��������  : ��ȡPowerSave״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��ػ�״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��09��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetPowerSaveFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdPowerSaveFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



