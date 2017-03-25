/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregRegingProc.c
  �� �� ��   : ����
  ��    ��   : Y00213812
  ��������   : 2014��06��27��
  ��������   : 1X REGģ������ע������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasXregCtx.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndCas.h"
#include  "CnasXregSndInternalMsg.h"
#include  "CnasXregTimer.h"
#include  "CnasXregRegingProcTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "CnasXregSndAps.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_REGING_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
//extern VOS_VOID CNAS_XREG_SndApsRegBeginInd(VOS_VOID);
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvRegReq_Reging_Init
 ��������  : ����ע������Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvRegReq_Reging_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstRegReq;

    pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

    /* ���������Ϣ */
    CNAS_XREG_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����ע����Ϣ */
    CNAS_XREG_SndCASEstReq(pstRegReq->enRegType);

    if (VOS_TRUE == CNAS_XREG_IsNeedNotifyApsRegBegin(pstRegReq->enRegType))
    {
        CNAS_XREG_SndApsRegBeginInd();
    }

    /* ����EstReq������ʱ�� */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ESTCNF_PT, TI_CNAS_XREG_TIMER_ESTCNF_PT_LEN);


    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_EST_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf
 ��������  : �ڵȴ���ֹ״̬����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortFsm_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvRegReq_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    /* ���ݵ�ǰ��ע������ֹͣEstCnf������ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);

    /* ����ABORT��Ϣ��CAS */
    CNAS_XREG_SndCASAbortReq();

    /* ����������ʱ�����л�״̬��״̬ */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ABORTCNF_PT, TI_CNAS_XREG_TIMER_ABORTCNF_PT_LEN);

    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_ABORT_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf
 ��������  : ���յ�EstCnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnf;
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEstCnf   = (CAS_CNAS_1X_EST_CNF_STRU*)pstMsg;

    /* ���Ͳ���ȷֱ�ӷ��� */
    if (CAS_CNAS_1X_EST_TYPE_REGISTRATION != pstEstCnf->enEstType)
    {
        return VOS_TRUE;
    }

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvEstCnf_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* ֹͣEstCnf������ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);

    /* ��¼ע���� */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, pstEstCnf->enEstRslt);

    /* ע��ʧ�ܴ������� */
    if (CAS_CNAS_1X_EST_RSLT_NO_RF == pstEstCnf->enEstRslt)
    {
        CNAS_XREG_RegFailProc();

        CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_NORF, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

        /* �˳����״̬��*/
        CNAS_XREG_QuitFsmL2();

        return VOS_TRUE;
    }

    if (CAS_CNAS_1X_EST_RSLT_SUCCESS != pstEstCnf->enEstRslt)
    {
        CNAS_XREG_RegFailProc();

        CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

        /* �˳����״̬��*/
        CNAS_XREG_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ע��ɹ� */
    CNAS_XREG_RegSuccProc();

    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_SUCCESS, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* �˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf
 ��������  : �ȴ�EstCnfʱ���յ�AbortInd��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* ���ݵ�ǰ��ע������ֹͣEstCnf������ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);


    /* ��¼��ǰ�ǽ��յ�������ϱ���ABORT��Ϣ */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, CAS_CNAS_1X_EST_RSLT_BUTT);

    /* �����ڲ���Ϣ֪ͨ�˳����״̬�����״̬ */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* �˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf
 ��������  : ����EstCnf��ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* EST����ʱ��¼ */
    CNAS_XREG_RecordRegRslt(pstCurrRegReq->enRegType, CAS_CNAS_1X_EST_RSLT_BUTT + 1);

    /* ����ABORT��Ϣ��CAS */
    CNAS_XREG_SndCASAbortReq();

    /* ����������ʱ�����л�״̬��״̬ */
    CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_ABORTCNF_PT, TI_CNAS_XREG_TIMER_ABORTCNF_PT_LEN);

    CNAS_XREG_SetCurrFsmState(CNAS_XREG_REGING_WAIT_ABORT_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd
 ��������  : ���յ�AbortInd��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvAbortInd_Reging_WaitAbortInd: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* ֹͣABortInd������ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ABORTCNF_PT, 0);

    /* �����ڲ���Ϣ֪ͨ�˳����״̬�����״̬ */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_ABORT_IND, pstCurrRegReq->enRegType);

    /* �˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd
 ��������  : �ȴ�AbortInd��Ϣ�ĳ�ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvTimeOut_Reging_WaitAbortInd: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    /* �����ڲ���Ϣ֪ͨ�˳����״̬�����״̬ */
    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_FAILURE, CNAS_XREG_REGING_WAIT_ABORT_IND, pstCurrRegReq->enRegType);

    /* �˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PostProcessMsg_Reging
 ��������  : ������״̬���ĺ�����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_UINT32  CNAS_XREG_PostProcessMsg_Reging(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstRegReq;

    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) == ulEventType)
    {
        pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

        /* ���յ���POWERDOWN��ע����ֱ�Ӷ��� */
        if (CAS_CNAS_1X_POWER_DOWN_REGISTRATION != pstRegReq->enRegType)
        {
            return VOS_TRUE;
        }

        /* �����ڲ���Ϣ��ֹ��ǰ���� */
        CNAS_XREG_SndAbortFsmMsg();

        /* ������Ϣ */
        /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
        CNAS_XREG_SaveMsgToCache(ulEventType, (VOS_UINT8*)pstMsg);
        /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_IsNeedNotifyApsRegBegin
 ��������  : �ж��Ƿ���Ҫ֪ͨAPS������ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ֪ͨAPS�� VOS_FALSE:����Ҫ֪ͨAPS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_IsNeedNotifyApsRegBegin(
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8                enRegType
)
{
   /*
    If the mobile station enters the Registration Access Substate (see [16]) due to timer-
    based registration, distance-based registration, zone-based registration, parameter
    change registration, or user zone registration, and if the packet zone list contains an
    entry with an active hysteresis timer for the current packet zone, the mobile station
    shall cancel the entrys packet zone hysteresis timer and shall remove the entry from
    the packet zone list.4
    */

    switch (enRegType)
    {
        case CAS_CNAS_1X_TIMER_BASED_REGISTRATION:
        case CAS_CNAS_1X_ZONE_BASED_REGISTRATION:
        case CAS_CNAS_1X_PARAMETER_CHANGED_REGISTRATION:
        case CAS_CNAS_1X_DISTANCE_BASED_REGISTRATION:
        case CAS_CNAS_1X_USER_ZONE_BASED_REGISTRATION:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf
 ��������  : ����Poweroff��ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstCurrRegReq;
    CNAS_XREG_MSG_STRU                 *pstEntryMsg;

    pstEntryMsg   = CNAS_XREG_GetCurrFsmEntryMsgAddr();

    /* �ж���Ϣ�����Ƿ���ȷ */
    if (CNAS_BuildEventType(UEPS_PID_XREG, ID_CNAS_XREG_XREG_REG_REQ) != pstEntryMsg->ulEventType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XREG, "CNAS_XREG_RcvPwrOffTimeOut_Reging_WaitEstCnf: Entry Msg is incorrect.",
                            pstEntryMsg->ulEventType);
    }

    pstCurrRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)(pstEntryMsg->aucMsgBuffer);

    CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_PWROFF, CNAS_XREG_REGING_WAIT_EST_CNF, pstCurrRegReq->enRegType);

    /* �˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


