/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccFsmMainTbl.c
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��07��03��
  ��������   : XCC L1��״̬��table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "xsd_xcc_pif.h"
#include "CnasXccFsmMain.h"
#include "CnasXccFsmMainTbl.h"
#include "xcc_xcall_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasXccTimer.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include  "xcc_xpds_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XCC ��״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXccMainFsmDesc;


/* XCC L1 IDLE״̬���¼������ */
NAS_ACT_STRU g_stCnasXccIdleActTbl[] =
{
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_RcvOrigCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_RcvPagingInd_L1Main_Idle)
};

/* XCC L1 MO CALLING״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMoCallingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF,
                     CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling),
};

/* XCC L1 MT CALLING״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMtCallingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF,
                     CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling)
};

/* XCC L1 ENDING״̬���¼������ */
NAS_ACT_STRU g_stCnasXccEndingActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_L1Main_Ending),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                     CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending),


    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_L1Main_Ending),
};

/* XCC L1 CONVERSATION״̬���¼������ */
NAS_ACT_STRU g_stCnasXccConversationActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_L1Main_Conversation),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_NDSS_REDIAL_IND,
                     CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation),
};

/* XCC L1 ��״̬��״̬����� */
NAS_STA_STRU g_astCnasXccL1MainStaTbl[] =
{

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_IDLE,
                      g_stCnasXccIdleActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_MT_CALLING,
                      g_stCnasXccMtCallingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_MO_CALLING,
                      g_stCnasXccMoCallingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_ENDING,
                      g_stCnasXccEndingActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_L1_STA_CONVERSATION,
                      g_stCnasXccConversationActTbl ),
};


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetL1MainStaTblSize
 ��������  : ��ȡ1X XCC��״̬��״̬���С
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����XCC��״̬��״̬��size
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��23��
   ��    ��   : y00213812
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetL1MainStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXccL1MainStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_XCC_GetMainFsmDescAddr
 ��������  : ��ȡMAIN״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��MAIN״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XCC_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXccMainFsmDesc);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




