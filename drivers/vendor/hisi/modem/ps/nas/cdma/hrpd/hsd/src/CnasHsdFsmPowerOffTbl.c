/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmPowerOffTbl.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��9��
  ��������   : HRPD L2 �ػ�״̬��״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasFsm.h"
#include "CnasHsdFsmPowerOff.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdComFunc.h"
#include "hsd_mscc_pif.h"
#include "hsm_hsd_pif.h"
#include "hsd_hlu_pif.h"
#include "CnasXsdTimer.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "ehsm_hsd_pif.h"

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
/* CNAS HSD״̬������:�ػ���״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasHsdPowerOffFsmDesc;

/* CNAS_HSD_POWER_OFF_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasHsdPoweroffInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_HSD_POWER_OFF_REQ,
                      CNAS_HSD_RcvMsccPowerOffReq_PowerOff_Init),
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF������ */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitEhsmPoweroffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_HSD_POWER_OFF_CNF,
                      CNAS_HSD_RcvEhsmPowerOffCnf_PowerOff_WaitEhsmPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitEhsmPowerOffCnfExpired_PowerOff_WaitEhsmPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF������ */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitHsmPoweroffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_HSD_POWEROFF_CNF,
                      CNAS_HSD_RcvHsmPowerOffCnf_PowerOff_WaitHsmPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitHsmPowerOffCnfExpired_PowerOff_WaitHsmPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF������ */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitHluPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HLU,
                      ID_HLU_HSD_POWER_OFF_CNF,
                      CNAS_HSD_RcvHluPowerOffCnf_PowerOff_WaitHluPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitHluPowerOffCnfExpired_PowerOff_WaitHluPowerOffCnf)
};

/* CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF������ */
NAS_ACT_STRU g_astCnasHsdPoweroffWaitCasPowerOffCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HALMP,
                      ID_CAS_CNAS_HRPD_POWER_OFF_CNF,
                      CNAS_HSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF,
                      CNAS_HSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf)
};

/* �ػ�״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasHsdPowerOffStaTbl[] =
{
    /*****************����ػ���ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_INIT,
                      g_astCnasHsdPoweroffInitActTbl),

    /*****************����EHSM�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_EHSM_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitEhsmPoweroffCnfActTbl ),


    /*****************����HSM�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_HSM_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitHsmPoweroffCnfActTbl ),

    /*****************����HLU�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_HLU_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitHluPowerOffCnfActTbl),

    /*****************����CAS�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_HSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF,
                      g_astCnasHsdPoweroffWaitCasPowerOffCnfActTbl)

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPowerOffStaTblSize
 ��������  : ��ȡ�ػ�״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:�ػ�״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetPowerOffStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasHsdPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetPowerOffFsmDescAddr
 ��������  : ��ȡ�ػ�״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��ػ�״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_HSD_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasHsdPowerOffFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



