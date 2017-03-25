/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccFsmMoCalling.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��4��
  ��������   : MO CALLING L2״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : w00242748
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXccFsmMoCalling.h"
#include "CnasXccFsmMoCallingTbl.h"
#include "xcc_xcall_pif.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "CnasXccCtx.h"
#include "CnasXccComFunc.h"
#include "CnasXccSndAps.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasXccSndInternalMsg.h"
#include "cas_1x_control_main_nas_pif.h"
#include "CnasMntn.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "CnasXccSndCsms.h"
#include "CnasCcb.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MO_CALLING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallOrigReq_MoCalling_Init
 ��������  : XCC���յ���������XCALL_XCC_ORIG_CALL_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��24��
    ��    ��   : y00245242
    �޸�����   : privacy mode���Կ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallOrigReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (XCALL_XCC_ORIG_CALL_REQ_STRU*)pstMsg;

    /* ���������Ϣ */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �洢������ص���Ϣ��ȫ�ֱ����У����õ�ǰ����Ϊ���� */
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo                    =   pstOrigCallReq->stSoInfo.enSo;
    pstCallInfo->ucCallId                       =   pstOrigCallReq->ucCallId;
    pstCallInfo->enInitSo                       =   pstOrigCallReq->stSoInfo.enSo;
    pstCallInfo->ucIsMoCall                     =   VOS_TRUE;

    /* �˴����� privacy mode��ucIsL2ErrReOrig��ucReOrigCount  */
    pstCallInfo->ucReOrigCount                  =   pstOrigCallReq->ucReOrigCount;
    pstCallInfo->ucIsL2ErrReOrig                =   pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucIsEmergencyCall              =   pstOrigCallReq->ucIsEmergencyCall;

    pstCallInfo->enReqPrivacyMode               =   (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)(CNAS_XCC_GetCtxAddr()->stCallNvimCfg.ucPrivacyMode);

    /* ��¼���� */
    pstCallInfo->stCalledPartyNum.enDigitMode   = pstOrigCallReq->enDigitMode;
    pstCallInfo->stCalledPartyNum.enNumPlan     = (CAS_CNAS_1X_NUMBER_PLAN_ENUM_UINT8)pstOrigCallReq->stCalledPartyNum.enNumPlan;
    pstCallInfo->stCalledPartyNum.enNumType     = (CAS_CNAS_1X_NUMBER_TYPE_ENUM_UINT8)pstOrigCallReq->stCalledPartyNum.enNumType;
    pstCallInfo->stCalledPartyNum.ucDigitNum    = pstOrigCallReq->stCalledPartyNum.ucDigitNum;
    NAS_MEM_CPY_S(pstCallInfo->stCalledPartyNum.aucDigit,
                  sizeof(pstCallInfo->stCalledPartyNum.aucDigit),
                  pstOrigCallReq->stCalledPartyNum.aucDigit,
                  sizeof(pstCallInfo->stCalledPartyNum.aucDigit));

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCalledPartySubAddr)
    {
        pstCallInfo->stCalledPartySubAddr       =   pstOrigCallReq->stCalledPartySubAddr;
        pstCallInfo->bitOpCalledPartySubAddr    =   VOS_TRUE;
    }

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCallingPartyNum)
    {
        pstCallInfo->stCallingPartyNum          =   pstOrigCallReq->stCallingPartyNum;
        pstCallInfo->bitOpCallingPartyNum       =   VOS_TRUE;
    }

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCallingPartySubAddr)
    {
        pstCallInfo->stCallingPartySubAddr      =   pstOrigCallReq->stCallingPartySubAddr;
        pstCallInfo->bitOpCallingPartySubAddr   =   VOS_TRUE;
    }

    /* �������б�Ȼ�����·���һ��SR_ID */
    /* ���SR_ID����ʧ�ܣ�����Ϊ���κ����쳣��ֱ��������ʧ�ܴ��� */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* ֪ͨ��1��״̬����� CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType))
    {
        /* ���͹���APS��ϢID_XCC_APS_DATA_CALL_SUSPEND_IND */
        CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

        /* Ǩ�� CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP��ʱ��TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP_LEN */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    }
    else
    {
        /* ����ID_CNAS_CAS_1X_EST_REQ������� */
        CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* Ǩ��CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF��2��״̬*/
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

        /* ����������ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF��ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init
 ��������  : XCC���յ�APS�����DATA CALL����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU*)pstMsg;

    /* ���������Ϣ */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����APS���͹�����������Ϣ */
    pstCallInfo                   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo      = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo         = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId         = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsDormDataCall = pstOrigCallReq->ucIsDormDataCall;
    pstCallInfo->ucIsDataReady    = pstOrigCallReq->ucDrsFlg;
    pstCallInfo->ucIsL2ErrReOrig  = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount    = pstOrigCallReq->ucReOrigCount;
    pstCallInfo->ucIsMoCall       = VOS_TRUE;

    pstCallInfo->stCalledPartyNum.enDigitMode = pstOrigCallReq->stDialNumInfo.enDigitMode;
    pstCallInfo->stCalledPartyNum.ucDigitNum  = pstOrigCallReq->stDialNumInfo.ucDigitNum;
    NAS_MEM_CPY_S(pstCallInfo->stCalledPartyNum.aucDigit, sizeof(pstCallInfo->stCalledPartyNum.aucDigit),
                  pstOrigCallReq->stDialNumInfo.aucDigit, sizeof(pstCallInfo->stCalledPartyNum.aucDigit));

    if (0 != pstOrigCallReq->stQosInfo.ucQosParaLength)
    {
        pstCallInfo->bitOpQosInfo     = VOS_TRUE;
        pstCallInfo->ucQosInfoLen     = pstOrigCallReq->stQosInfo.ucQosParaLength;
        NAS_MEM_CPY_S(pstCallInfo->aucQosInfo, sizeof(pstCallInfo->aucQosInfo),
                      pstOrigCallReq->stQosInfo.aucQosPara, sizeof(pstCallInfo->aucQosInfo));
    }

    if (VOS_TRUE == pstOrigCallReq->ulIsPrevHrpdMode)
    {
        pstCallInfo->ulIsPrevHrpdFlg             = VOS_TRUE;
        pstCallInfo->stPrevHrpdActNetInfo.usSid  = pstOrigCallReq->stPrevHrpdActInfo.usSid;
        pstCallInfo->stPrevHrpdActNetInfo.usNid  = pstOrigCallReq->stPrevHrpdActInfo.usNid;
        pstCallInfo->stPrevHrpdActNetInfo.usPzid = pstOrigCallReq->stPrevHrpdActInfo.usPzid;
    }
    else
    {
        pstCallInfo->ulIsPrevHrpdFlg             = VOS_FALSE;
    }

    /* ���APSЯ��������Ч��SR_ID����ֱ�ӽ��з��䣬����ʹ��APSЯ����SR_ID */
    /* ���SR_ID����ʧ�ܣ�����Ϊ���κ����쳣��ֱ��������ʧ�ܴ��� */
    if (CNAS_XCC_INVALID_SR_ID == pstOrigCallReq->ucSrId)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* ֪ͨ��1��״̬����� CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }

        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = pstOrigCallReq->ucSrId;
        CNAS_XCC_UpdateSrIdUsed(pstCallInfo->enInitSo,
                                pstOrigCallReq->ucSrId,
                                pstCallInfo->ucConnectId);

    }


    /* ��CAS���ͽ������� */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* Ǩ��CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF��2��״̬*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* ����������ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF��ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init
 ��������  : XCC���յ�SMS�����SMS CALL����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg;

    /* ���������Ϣ */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����SMS���͹�����������Ϣ */
    pstCallInfo                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo     = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo        = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId        = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsL2ErrReOrig = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount   = pstOrigCallReq->ucL2ErrReOrigCount;

    /* ���ź��б�Ȼ�����·���һ��SR_ID */
    /* ���SR_ID����ʧ�ܣ�����Ϊ���κ����쳣��ֱ��������ʧ�ܴ��� */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* ֪ͨ��1��״̬����� CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstOrigCallReq->enSo, &enServiceType);

    /* ���͹���APS��ϢID_XCC_APS_DATA_CALL_SUSPEND_IND */
    CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

    /* Ǩ�� CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

    /* ����������ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP��ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init
 ��������  : XCC���յ�AGPS�����AGPS CALL����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg;

    /* ���������Ϣ */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����XPDS���͹�����������Ϣ */
    pstCallInfo                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo     = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo        = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId        = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsL2ErrReOrig = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount   = pstOrigCallReq->ucL2ErrReOrigCount;

    /* AGPS���б�Ȼ�����·���һ��SR_ID */
    /* ���SR_ID����ʧ�ܣ�����Ϊ���κ����쳣��ֱ��������ʧ�ܴ��� */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* ֪ͨ��1��״̬����� CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstOrigCallReq->enSo, &enServiceType);

    /* ���͹���APS��ϢID_XCC_APS_DATA_CALL_SUSPEND_IND */
    CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

    /* Ǩ�� CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

    /* ����������ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP��ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ�����յ�APS���͵�ID_APS_XCC_DATA_CALL_SUSPEND_RSP
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ����ID_CNAS_CAS_1X_EST_REQ������� */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* Ǩ��CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF��2��״̬*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* ����������ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF��ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHangUpReq_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ�����յ�XCALL���͵�ID_XCALL_XCC_HANGUP_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ��TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_VOICE_CALL);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ�����յ�SMS���͵�ID_CSMS_XCC_END_SMS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��CSMSģ�鷢��ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_SMS);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ�����յ�XPDS���͵�ID_XPDS_XCC_END_AGPS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ�����յ�SMS���͵�ID_CNAS_XCC_XCC_ABORT_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ��TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ���ݺ������ͣ�֪ͨTAF�����н��� */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_TRUE, 0);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp:time out");

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ����ID_CNAS_CAS_1X_EST_REQ������� */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* Ǩ��CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF��2��״̬*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* ����������ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF��ʱ��TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�����ظ�״̬���յ��ػ�ָ��
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */
    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��XCALL���� ID_XCALL_XCC_ORIG_CALL_CNF (FAIL) */
    CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_CALLID_NULL, 0);

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬�����յ� ID_CAS_CNAS_1X_EST_CNF
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstEstCnf   =   (CAS_CNAS_1X_EST_CNF_STRU*)pstMsg;
    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*ֹͣ������ʱ��*/
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);


    if (CAS_CNAS_1X_EST_RSLT_SUCCESS == pstEstCnf->enEstRslt)
    {
        /* Ǩ��CNAS_XCC_MO_CALLING_STA_WAIT_AS_CALL_INIT״̬�� */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_CALL_INIT);

        /* ����������ʱ��*/
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN);
        return VOS_TRUE;
    }

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      CNAS_XCC_ConvertEstReasonToTafCause(pstEstCnf->enEstRslt),
                                      pstEstCnf->enFailLayer,
                                      VOS_TRUE,
                                      pstEstCnf->sCdmaRssi);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHandUpReq_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬���յ�XCALL���͵�ID_XCALL_XCC_HANGUP_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    /* ֹͣ������ʱ�� */
    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬�����յ�ID_CSMS_XCC_END_SMS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* ��SMSģ�鷢��ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬�����յ�ID_XPDS_XCC_END_AGPS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬�����յ�ID_APS_XCC_HANGUP_DATA_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* ��APSģ�鷢��ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬�����յ�ID_CNAS_XCC_XCC_ABORT_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ���ݺ������ͣ�֪ͨTAF���н��� */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf:time out");

    /* ֪ͨAS REL_REQ*/
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                         TAF_XCC_CAUSE_ACCESS_CNF_TIMEOUT,
                                         TAF_XCC_FAIL_LAYER_L3,
                                         VOS_FALSE,
                                         0);

    /* ֪ͨ��1��״̬����� CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬���յ�������TERMINATE��Ϣ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                             *pstCallInfo        =   VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                     *pstTerminateInd    =   VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstTerminateInd =   (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ��AS��liuyinȷ��:�ȴ������ظ�ʱ,AS�쳣ʱ���ϱ�terminate indָʾMS END,��ʱNAS��Ҫ�����ز�,ת��ԭ��ֵΪabort */
    if (CAS_CNAS_1X_TERMINATE_REASON_MS_END == pstTerminateInd->enTerminateReason)
    {
        enCause = TAF_XCC_CAUSE_ABORT;
    }
    else
    {
        /* ��ͬ��Ϣ���͵�ӳ�� */
        enCause = CNAS_XCC_ConvertTerminateReasonToTafCause(pstTerminateInd->enTerminateReason);
    }

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      enCause,
                                      TAF_XCC_FAIL_LAYER_L3,
                                      VOS_TRUE,
                                      pstTerminateInd->sCdmaRssi);

    /* ���1������CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬���յ��ػ�ָ��
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ��XCALL���� ID_XCALL_XCC_ORIG_CALL_CNF (FAIL) */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit
 ��������  : ���յ�AS��INIT_IND��Ϣ��Ǩ��CONVERASTION
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_INIT_IND_STRU     *pstCallInd  = VOS_NULL_PTR;

    /* bypass��isnull��qos������¼��ȫ�ֱ��� */
    pstCallInd  =   (CAS_CNAS_1X_CALL_INIT_IND_STRU*)pstMsg;


    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucConRef               =   pstCallInd->ucConRef;
    pstCallInfo->ucIsByPassAlertAns     =   (VOS_UINT8)pstCallInd->enBypassAlertAns;
    pstCallInfo->ucQosInfoLen           =   pstCallInd->ucQosInfoLen;
    pstCallInfo->ucIsNullCc             =   pstCallInd->enIsNullCcFlag;


    NAS_MEM_CPY_S(pstCallInfo->aucQosInfo, sizeof(pstCallInfo->aucQosInfo), pstCallInd->aucQosInfo, sizeof(pstCallInd->aucQosInfo));

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_SUCCESS */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_SUCCESS, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_SUCCESS,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit
 ��������  : �յ� ID_CAS_CNAS_1X_CALL_TERMINATE_IND
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo        = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstTerminateInd    = VOS_NULL_PTR;

    pstTerminateInd     =   (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU*)pstMsg;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstTerminateInd->enTerminateReason),
                                         TAF_XCC_FAIL_LAYER_L3,
                                         VOS_TRUE,
                                         pstTerminateInd->sCdmaRssi);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHandUpReq_MoCalling_WaitAsCallInit
 ��������  : �յ�XCALL���͵�ID_XCALL_XCC_HANGUP_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��6��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHandupReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1������״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ�CALL INIT״̬�����յ�ID_CSMS_XCC_END_SMS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��SMSģ�鷢��ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1������״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ�CALL INIT״̬�����յ�ID_APS_XCC_HANGUP_DATA_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��APSģ�鷢��ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1������״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ�CALL INIT״̬�����յ�ID_XPDS_XCC_END_AGPS_CALL_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1������״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ�CALL INIT״̬�����յ�ID_CNAS_XCC_XCC_ABORT_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ���ݺ������ͣ�֪ͨTAF���н��� */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1������״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֪ͨAS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      TAF_XCC_CAUSE_ACCESS_TCH_TIMEOUT,
                                      TAF_XCC_FAIL_LAYER_L3,
                                      VOS_FALSE,
                                      0);

    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ������INIT�ظ�״̬���յ��ػ�ָ��
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ���ݲ�ͬSO���ظ���ͬORIG CNF */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndOrigCallCnf_MoCalling
 ��������  : XCC�����յ�TERMINATE ����REL_IND֮����APS����XCALL������Ϣ�Ĵ�������
 �������  : VOS_UINT32 isNeedToResumeAps Ϊ VOS_TRUE ʱ����Ҫ����APS

 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndOrigCallCnf_MoCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    VOS_BOOL                            isNeedToResumeAps,
    VOS_INT16                           sRssi
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32      enServiceType;
    CNAS_XCC_ConvertSoToServiceType((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)pstCallInfo->enCurrentSo, &enServiceType);

    switch (enServiceType)
    {
       case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            /* ����ҵ�� */
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
            }
            CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, TAF_XCC_CALLID_NULL, sRssi);
            break;

       case CNAS_XCC_SERVICE_TYPE_SMS:
           if (VOS_TRUE   ==  isNeedToResumeAps)
           {
               CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
           }

           /* SMS ����ҵ�� */
           CNAS_XCC_SndCsmsOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause);
           break;

       case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* ���ݺ���ҵ�� */
            CNAS_XCC_SndApsOrigDataCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, pstCallInfo->ucConRef, pstCallInfo->ucConnectId, sRssi);
            break;

       case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
           if (VOS_TRUE   ==  isNeedToResumeAps)
           {
               CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
           }

           /* AGPS ����ҵ�� */
           CNAS_XCC_SndXpdsOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause);
            break;

       default:
            CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, TAF_XCC_CALLID_NULL, 0);

            CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_NotifyTafCallDisc_MoCalling: enServiceType is not found!",
                          enServiceType);
            break;
    }

}




/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





