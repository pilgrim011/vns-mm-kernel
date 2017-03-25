/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccFsmMoCallingTbl.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��4��
  ��������   : MO CALLING L2״̬��table��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��4��
    ��    ��   : w00242748
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "xsd_xcc_pif.h"
#include "CnasXccFsmMoCalling.h"
#include "CnasXccFsmMoCallingTbl.h"
#include "xcc_xcall_pif.h"
#include "xcc_aps_pif.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccTimer.h"
#include "CnasXccSndInternalMsg.h"
#include "xcc_sms_pif.h"
#include  "xcc_xpds_pif.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MO_CALLING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS XCC ��״̬�� */
NAS_FSM_DESC_STRU                       g_stCnasXccMoCallingFsmDesc;

/* ���ε������漰 */

/* MO CALLING INIT״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMoCallingInitActTbl[] =
{
    /* VOICE CALL������ */
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_RcvXcallOrigReq_MoCalling_Init),

    /* DATA CALL������ */
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init),

    /* SMS������ */
    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init),

    /* AGPS������ */
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init),
};

/* MO CALLING WAIT APS SUSPEND RSP״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMoCallingWaitApsSuspendRspActTbl[] =
{

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_DATA_CALL_SUSPEND_RSP,
                     CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP,
                     CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp),
};

/* MO CALLING WAIT AS EST CNF״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMoCallingWaitAsEstCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_EST_CNF,
                     CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_EST_CNF,
                     CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf),
};

/* MO CALLING WAIT AS CALL INIT״̬���¼������ */
NAS_ACT_STRU g_stCnasXccMoCallingWaitAsCallInitActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_INIT_IND,
                     CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHandupReq_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND,
                     CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit)
};

/* XCC MO CALLING L2 ״̬��״̬����� */
NAS_STA_STRU g_astCnasXccMoCallingStaTbl[] =
{

    NAS_STA_TBL_ITEM( CNAS_XCC_MO_CALLING_STA_INIT,
                      g_stCnasXccMoCallingInitActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP,
                      g_stCnasXccMoCallingWaitApsSuspendRspActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF,
                      g_stCnasXccMoCallingWaitAsEstCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MO_CALLING_STA_WAIT_AS_CALL_INIT,
                      g_stCnasXccMoCallingWaitAsCallInitActTbl ),

};


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetMoCallingStaTblSize
 ��������  : ��ȡMO CALLING L2״̬��״̬���С
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����MO CALLING L2״̬��״̬��size
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetMoCallingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXccMoCallingStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetMoCallingFsmDescAddr
 ��������  : ��ȡMO CALLING״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��MO CALLING״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XCC_GetMoCallingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXccMoCallingFsmDesc);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




