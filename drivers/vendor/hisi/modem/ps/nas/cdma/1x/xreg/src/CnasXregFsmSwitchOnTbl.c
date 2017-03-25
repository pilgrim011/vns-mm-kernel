/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregFsmSwitchOnTbl.c
  �� �� ��   : ����
  ��    ��   : g0025031
  ��������   : 2015��01��05��
  ��������   : 1X XREG L2����״̬���¼���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXregFsmSwitchOn.h"
#include "CnasXregFsmSwitchOnTbl.h"
#include "UsimPsInterface.h"
#include "xsd_xreg_pif.h"
#include "CnasXregTimer.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_SWITCH_ON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* CNAS XREG״̬������:������״̬������ */
NAS_FSM_DESC_STRU                       g_stCnasXregSwitchOnFsmDesc;

/* CNAS_XREG_SWITCH_ON_STA_INIT״̬�¶����� */
NAS_ACT_STRU g_astCnasXregSwitchOnInitActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvXsdStartReq_SwitchOn_Init),
};

/* CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF������ */
NAS_ACT_STRU g_astCnasXregSwitchOnWaitCardFileCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT,
                      CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf)

};


/* ����״̬����Ϣ ״̬�� */
NAS_STA_STRU g_astCnasXregSwitchOnStaTbl[] =
{
    /*****************���忪����ʼ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_SWITCH_ON_STA_INIT,
                      g_astCnasXregSwitchOnInitActTbl),

    /*****************����ȴ����ļ���Ϣ״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF,
                      g_astCnasXregSwitchOnWaitCardFileCnfActTbl )
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetSwitchOnStaTblSize
 ��������  : ��ȡ����״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:����״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXregSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetSwitchOnFsmDescAddr
 ��������  : ��ȡ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ�򿪻�״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���


*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XREG_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXregSwitchOnFsmDesc);
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */