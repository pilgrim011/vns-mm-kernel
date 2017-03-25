/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmSwitchOnTbl.c
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
#include "CnasXsdFsmSwitchOn.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdComFunc.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "xsd_xcc_pif.h"
#include "UsimPsInterface.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SWITCH_ON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XSD״̬������:������״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasXsdSwitchOnFsmDesc;

/* CNAS_XSD_SWITCH_ON_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasXsdSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvMsccStartReq_SwitchOn_Init),

    NAS_ACT_TBL_ITEM( I1_UEPS_PID_MSCC,
                      ID_MSCC_XSD_START_REQ,
                      CNAS_XSD_RcvMsccStartReq_SwitchOn_Init),
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF������ */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitCardFileCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CARD_FILE_CNF,
                      CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf)

};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF������ */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitXccStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_XSD_START_CNF,
                      CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XCC_START_CNF,
                      CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf)
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF������ */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitXregStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_XREG_XSD_START_CNF,
                      CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_XREG_START_CNF,
                      CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf)
};

/* CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF������ */
NAS_ACT_STRU g_astCnasXsdSwitchOnWaitCasStartCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_START_CNF,
                      CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XSD_WAIT_CAS_START_CNF,
                      CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf)
};

/* �ػ�״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasXsdSwitchOnStaTbl[] =
{
    /*****************���忪����ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_INIT,
                      g_astCnasXsdSwitchOnInitActTbl),

    /*****************����ȴ����ļ���Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF,
                      g_astCnasXsdSwitchOnWaitCardFileCnfActTbl ),

    /*****************����ȴ�XCC���������Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF,
                      g_astCnasXsdSwitchOnWaitXccStartCnfActTbl),

    /*****************����ȴ�XREG���������Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF,
                      g_astCnasXsdSwitchOnWaitXregStartCnfActTbl),

    /*****************����ȴ�CAS���������Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF,
                      g_astCnasXsdSwitchOnWaitCasStartCnfActTbl)

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSwitchOnStaTblSize
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
VOS_UINT32 CNAS_XSD_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXsdSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSwitchOnFsmDescAddr
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
NAS_FSM_DESC_STRU * CNAS_XSD_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXsdSwitchOnFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



