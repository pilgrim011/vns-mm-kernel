/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregFsmMainTbl.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��07��03��
  ��������   : XREG L1��״̬��table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXregFsmMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "xsd_xreg_pif.h"
#include  "CnasXregTimer.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndInternalMsg.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XREG ��״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXregL1MainFsmDesc;

/* XREG L1 FSM null״̬���¼������ */
NAS_ACT_STRU                            g_astCnasXregNullActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvStartReq_Null),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF,
                      CNAS_XREG_RcvSwitchOnRslt_Null),

};

/* XREG L1 FSM unreg״̬���¼������ */
NAS_ACT_STRU                            g_astCnasXregUnRegActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_XREG_START_REQ,
                      CNAS_XREG_RcvStartReq_UnReg),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      CNAS_XREG_RcvRegedDataInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_MSG_ACCESS_RSLT_IND,
                      CNAS_XREG_RcvAccessInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_CNF,
                      CNAS_XREG_RcvRegCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_L1Main),
};

/* XREG L1 FSM reged״̬���¼������ */
NAS_ACT_STRU                            g_astCnasXregRegedActTbl[] =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      CNAS_XREG_RcvRegedDataInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_MSG_ACCESS_RSLT_IND,
                      CNAS_XREG_RcvAccessInd_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_REQ,
                      CNAS_XREG_RcvRegReq_L1Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_CNAS_XREG_XREG_REG_CNF,
                      CNAS_XREG_RcvRegCnf_L1Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT,
                      CNAS_XREG_RcvPwrOffTimeOut_L1Main),
};

/* XREG L1 ��״̬��״̬����� */
NAS_STA_STRU                            g_astCnasXregL1MainStaTbl[] =
{
    /*****************�����ʼ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_NULL,
                      g_astCnasXregNullActTbl ),

    /*****************���忪��δע��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_UNREG,
                      g_astCnasXregUnRegActTbl ),

    /*****************�����Ѿ�ע��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( CNAS_XREG_L1_STA_REGED,
                      g_astCnasXregRegedActTbl ),
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetMainFsmDescAddr
 ��������  : 1X XREG L1��״̬����ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XREG_GetMainFsmDescAddr(VOS_VOID)
{
    return &g_stCnasXregL1MainFsmDesc;
}


/*****************************************************************************
 �� �� ��  : CNAS_XREG_GetL1MainStaTblSize
 ��������  : ��ȡ1X XREG L1��״̬��״̬���С
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_GetL1MainStaTblSize(VOS_VOID)
{
    return sizeof(g_astCnasXregL1MainStaTbl)/sizeof(NAS_STA_STRU);
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



