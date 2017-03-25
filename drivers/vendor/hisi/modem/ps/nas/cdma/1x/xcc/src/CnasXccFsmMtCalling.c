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
#include "CnasXccFsmMtCalling.h"
#include "CnasXccFsmMtCallingTbl.h"
#include "CnasXccSndAps.h"
#include "cas_1x_control_main_nas_pif.h"
#include "CnasXccComFunc.h"
#include "CnasXccCtx.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasMntn.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccSndCsms.h"
#include "CnasCcb.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "Nas_Mem.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MT_CALLING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsPagingInd_MtCalling_Init
 ��������  : �յ�ID_CAS_CNAS_1X_PAGING_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��12��24��
   ��    ��   : y00245242
   �޸�����   : privacy mode���Կ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsPagingInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_PAGING_IND_STRU        *pstAsPagingInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* ������Ϣ��� */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAsPagingInd = (CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ���汻��SO */
    CNAS_XCC_SetInitSo(pstAsPagingInd->enSo);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    CNAS_XCC_CovertVoiceCallPagingIndSo(&pstAsPagingInd->enSo);
#endif

    CNAS_XCC_SetCurrentSo(pstAsPagingInd->enSo);

    CNAS_XCC_ConvertSoToServiceType(pstAsPagingInd->enSo, &enServiceType);

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        pstCallInfoCtx->enReqPrivacyMode = (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)(CNAS_XCC_GetCtxAddr()->stCallNvimCfg.ucPrivacyMode);
    }

    /* ���Ż����������� */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* ֪ͨAPS���� */
        CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfoCtx->ucConnectId, enServiceType);

        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP);

        /* ����TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);
    }
    else
    {
        /* ��AS����EST REQ */
        CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfoCtx);

        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

        /* ����TI_CNAS_XCC_WAIT_AS_EST_CNF */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataInd_MtCalling_Init
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��12��
   ��    ��   : L00256032
   �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd;
    CNAS_XCC_AWIM_STRU                 *pstAWIM;
    CNAS_XCC_EAWIM_STRU                *pstEAWIM;

    /* ������Ϣ��� */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* ����Ϣ��������ֻ���յ�AWI����EAWI����MAINTANCE ORDERʱ�Ż���� */
    if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
    {
        CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
        return VOS_TRUE;
    }

    /* ��XCALL����INCOMING CALL IND */
    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        /* ��XCALL����INCOMING CALL IND */
        CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
    }


    /* SEND DATA CALL OR SMS incoming call ind */
    if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
    {
        /* ��CSMS����INCOMING CALL IND */
        CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
    }

    if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
    {
        CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
    }

    /* ��ά�ɲ⣬�ϱ�1x call state*/
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

#if 0
    if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
    {
        /* ��APS����INCOMING CALL IND */
        CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
    }
#endif




    /*
        �������Ч��call id����ʱ��Ϊ��һ���µĺ��еĵ�����������������̣������ߵ���Ǩ�ص�wait for
        answer״̬
     */
    if ( CNAS_XCC_INVAILD_CALL_ID == pstCallInfoCtx->ucCallId )
    {
        /* ���AWI/EAWI�Ľ��벢���� */
        CNAS_XCC_BufferAWIOrEAWIInfoReco((CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg, pstCallInfoCtx);

        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

        /* ����TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
    }
    else
    {
        /* ����AWI��EAWI��������ϱ� */
        if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
        {
            pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
            if (VOS_NULL_PTR == pstAWIM)
            {
                return VOS_ERR;
            }

            if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
                return VOS_ERR;
            }

            CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)pstAWIM);

            PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
        }
        else if (CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
        {
            pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
            if (VOS_NULL_PTR == pstEAWIM)
            {
                return VOS_ERR;
            }

            if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
                return VOS_ERR;
            }

            CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)pstEAWIM);

            PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
        }
        else
        {

        }

        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));

        /* ����TI_CNAS_XCC_T53M */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp
 ��������  : �յ�ID_APS_XCC_DATA_CALL_SUSPEND_RSP��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��AS����EST REQ */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfo);

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

    /* ����TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp
 ��������  : ����ID_CNAS_XCC_XCC_ABORT_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ��AS����EST REQ */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfo);

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

    /* ����TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp
 ��������  : XCC���ڵȴ�APS����ظ�״̬ʱ���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    /* ֪ͨAPS ȡ������APS������ID_XCC_APS_DATA_CALL_RESUME_IND */
    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf
 ��������  : �յ�ID_CAS_CNAS_1X_EST_CNF��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnfMsg   = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstEstCnfMsg   = (CAS_CNAS_1X_EST_CNF_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* ֹͣTI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    if ( CAS_CNAS_1X_EST_RSLT_SUCCESS == pstEstCnfMsg->enEstRslt )
    {
        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT);

        /* ����TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN);
    }
    else
    {
        if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
          || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
          || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
        {
            /* ֪ͨAPS RESUME IND */
            CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
        }

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
        CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf
 ��������  : �յ�ID_CNAS_XCC_XCC_ABORT_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬���յ������terminate ind
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* SOת����service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS�ָ�APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* ֪ͨAPS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf
 ��������  : XCC���ڵȴ�����㽨���ظ�״̬���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_INIT_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_INIT_IND_STRU     *pstCallInitInd = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInitInd = (CAS_CNAS_1X_CALL_INIT_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* bypass��isnull��qos������¼��ȫ�ֱ��� */
    /* ������Ϣ�е�connect id��CALL INIT�е�connect id����ͬ�� */
    pstCallInfoCtx->ucConRef           = pstCallInitInd->ucConRef;
    pstCallInfoCtx->ucIsByPassAlertAns = (VOS_UINT8)pstCallInitInd->enBypassAlertAns;
    pstCallInfoCtx->ucIsNullCc         = pstCallInitInd->enIsNullCcFlag;
    pstCallInfoCtx->ucQosInfoLen       = pstCallInitInd->ucQosInfoLen;

    NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstCallInitInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));

    if ( VOS_TRUE == pstCallInfoCtx->ucIsByPassAlertAns )
    {
        /* ����ǻ���ģʽ��ֱ�ӽ�conversation״̬����״̬�� */
        if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
        {
            /* ��״̬������conversation״̬ */
            CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                                      CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                      CNAS_XCC_MT_CALLING_END_REASON_BUTT);

            CNAS_XCC_QuitFsmL2();
            return VOS_TRUE;
        }


        if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
        {
            /* ��XCALL����INCOMING CALL IND */
            CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
        }

        /* SEND DATA CALL OR SMS incoming call ind */
        if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
        {
            CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
        }

        if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
        {
            CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
        }

        if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
        {
            CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
        }

        /* ��ά�ɲ⣬�ϱ�1x call state*/
        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

        /* ����TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
    }
    else
    {
        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ORDER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));

        /* ����TI_CNAS_XCC_T52M */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M, TI_CNAS_XCC_T52M_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit
 ��������  : �յ�ID_CNAS_XCC_XCC_ABORT_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_INIT_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* SOת����service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS�ָ�APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* ֪ͨAPS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ������call init ind״̬��������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֪ͨAS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit
 ��������  : XCC���ڵȴ������call init ind״̬���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder
 ��������  : �յ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��1��
   ��    ��   : c00299063
   �޸�����   : ������װ
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_UpdateMtCallInfoInd
 ��������  : ���±���call info ind
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��1��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_UpdateMtCallInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx       = VOS_NULL_PTR;
    CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU                  *pstUpdateCallInfoInd = VOS_NULL_PTR;

    pstUpdateCallInfoInd            = (CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU *)pstMsg;
    pstCallInfoCtx                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ����CALL��Ϣ */
    pstCallInfoCtx->ucConRef        = pstUpdateCallInfoInd->ucConRef;
    pstCallInfoCtx->ucIsNullCc      = pstUpdateCallInfoInd->enIsNullCcFlag;
    pstCallInfoCtx->enCurrentSo     = pstUpdateCallInfoInd->enSo;

    CNAS_XCC_UpdateSrIdUsed(pstUpdateCallInfoInd->enSo,
                            pstUpdateCallInfoInd->ucSrId,
                            pstUpdateCallInfoInd->ucConnectId);
    pstCallInfoCtx->ucSrId          = pstUpdateCallInfoInd->ucSrId;


    /* ��ǰ��Ϊ������ϱ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��ʱ�򣬽�����Ѿ�SOЭ����ɣ����
        ��ʱSO��Э����ɱ���ó�VOS_TRUE */
    pstCallInfoCtx->ucIsSoNegCmplt  = VOS_TRUE;

    if ( VOS_TRUE == pstUpdateCallInfoInd->ucQosParaFlag )
    {
        pstCallInfoCtx->bitOpQosInfo       = VOS_TRUE;
        pstCallInfoCtx->ucQosInfoLen       = pstUpdateCallInfoInd->ucQosInfoLen;
        NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstUpdateCallInfoInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��1��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��1��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��1��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder
 ��������  : �յ�ID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx       = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ����������ʱ�� */
    CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M, TI_CNAS_XCC_T52M_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));


    /*
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
        1. Alert With Information Message: If the message contains a Signal information
        record, the mobile station should alert the user in accordance with the Signal
        information record; otherwise, the mobile station should use standard alert as
        defined in 3.7.5.5. The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate (see 2.6.10.1.2).
        2. Extended Alert with Information Message: If the message contains a Signal
        information record, the mobile station should alert the user in accordance with
        the Signal information record; otherwise, the mobile station should use
        standard alert as defined in 3.7.5.5. The Call Control instance shall enter the
        Waiting for Mobile Station Answer Substate (see 2.6.10.1.2).
        3. Maintenance Order: The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate.
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */
    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            /* ���AWI/EAWI�Ľ��벢���� */
            CNAS_XCC_BufferAWIOrEAWIInfoReco(pstDschDataInd, pstCallInfoCtx);

            /* ͣT52M */
            CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

            /* ����ǻ���ģʽ�����Զ����� */
            if ( CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
            {
                CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
                return VOS_TRUE;
            }

            /* ��XCALL����INCOMING CALL IND */
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                /* ��XCALL����INCOMING CALL IND */
                CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
            }

            /* SEND DATA CALL OR SMS incoming call ind */
            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                /* ��CSMS����INCOMING CALL IND */
                CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                /* ��APS����INCOMING CALL IND */
                CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
            }

            /* ��ά�ɲ⣬�ϱ�1x call state*/
            CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                    CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
            CNAS_XCC_SndXcc1xCallStateUpdateInd();

            /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

            /* ����TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
            CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_MtCalling_WaitForOrder(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG:
            /* ����REJ ORDER */
            pstCallInfoCtx              = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            stRejInfo.ucConRef          = pstCallInfoCtx->ucConRef;
            stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
            stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
            stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
            stRejInfo.ulL3PduBitLen     = 0;
            stRejInfo.pucPdudata        = aucPduData;
            CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

            /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
            CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                       0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder: Wrong MSG", pstDschDataInd->enDschMsgType);
            break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder
 ��������  : �յ�ID_CNAS_XCC_XCC_ABORT_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T52M);

    /* ֪ͨAS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ͣT52M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* SOת����service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS�ָ�APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* ֪ͨAPS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ͣT52M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder
 ��������  : TI_CNAS_XCC_T52M������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ��AS����Rel Req */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder
 ��������  : WAIT FOR ORDER״̬���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣ��ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_XCALL_XCC_INCOMING_CALL_RSP��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_INCOMING_CALL_RSP_STRU   *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (XCALL_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP���ʧ�ܣ�֪ͨCAS����״̬�� */
    if ( XCC_XCALL_RESULT_FAIL == pstIncomingCallRsp->enRslt )
    {
        /* ֪ͨ�����REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* ���AWI/EAWI��info record���� */
        CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING, CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ͬ��call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    if ( VOS_TRUE == pstCallInfo->ucIsByPassAlertAns )
    {
        /* ��XCALLģ�鷢��XCC_XCALL_CALL_CONNECT_IND */
        CNAS_XCC_SndXcallCallConnectInd(pstCallInfo);

        /* ��״̬������conversation״̬ */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();
    }
    else
    {
        /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

        /* ����TI_CNAS_XCC_T53M */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
    }

    /* ���AWI/EAWI����Ϣ��¼��֪ͨXCALL */
    if (VOS_TRUE == pstCallInfo->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid)
    {
        if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstCallInfo->stAWIorEAWIInfoRecoBuffer.enMsgType)
        {
            CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)&(pstCallInfo->stAWIorEAWIInfoRecoBuffer.u.stAWIM));
        }
        else
        {
            CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)&(pstCallInfo->stAWIorEAWIInfoRecoBuffer.u.stEAWIM));
        }

        /* ���AWI/EAWI��info record���� */
        CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_APS_XCC_INCOMING_CALL_RSP��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_INCOMING_CALL_RSP_STRU     *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (APS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP���ʧ�ܣ�֪ͨCAS����״̬�� */
    if (XCC_APS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* ֪ͨ�����REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_SERVICE_INACTIVE,
                                  VOS_FALSE);

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ͬ��call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* ���BYPASSΪTRUE��ֱ�ӽ�CONVERSATION״̬ */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* ��APSģ�鷢��ID_XCC_APS_DATA_CALL_CONN_IND */
        CNAS_XCC_SndApsDataCallConnectInd(pstCallInfo);

        /* ��״̬������conversation״̬ */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* ����TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    /* ��ȷ��:TO DO: ���AWI/EAWI����Ϣ��¼��֪ͨAPS */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_CSMS_XCC_INCOMING_CALL_RSP��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (CSMS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP���ʧ�ܣ�֪ͨCAS����״̬�� */
    if (XCC_CSMS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* ֪ͨ�����REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ͬ��call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* ���BYPASSΪTRUE��ֱ�ӽ�CONVERSATION״̬ */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* ��SMSģ�鷢��CONN_IND */
        CNAS_XCC_SndCsmsCallConnectInd(pstCallInfo);

        /* ��״̬������conversation״̬ */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* ����TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    /* ��ȷ��:TO DO: ���AWI/EAWI����Ϣ��¼��֪ͨSMS */

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_XPDS_XCC_INCOMING_CALL_RSP��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo        = VOS_NULL_PTR;

    pstIncomingCallRsp = (XPDS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP���ʧ�ܣ�֪ͨCAS����״̬�� */
    if (XCC_CSMS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* ֪ͨ�����REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ͬ��call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* ���BYPASSΪTRUE��ֱ�ӽ�CONVERSATION״̬ */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* ��XPDSģ�鷢��CONN_IND */
        CNAS_XCC_SndXpdsCallConnectInd(pstCallInfo);

        /* ��״̬������conversation״̬ */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);


    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* ����TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp
 ��������  : ID_CNAS_XCC_XCC_ABORT_REQ������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* ͨ��DISC IND��֪ͨXCALL/APS/SMS�绰������ */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, pstAbortReq->enAbortCause, VOS_FALSE);

    /* ֪ͨ����� REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx      = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* ֪ͨTAF���н��� */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                         VOS_TRUE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId, \
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* ֪ͨTAF��ģ�飬���н��� */
    /* TO DO:������rel ind����û������ԭ��ֵ */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp
 ��������  : TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֪ͨTAF��ģ�飬���н��� */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_INCOMING_RSP_TIME_OUT, VOS_FALSE);

    /* ֪ͨ����� REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ���AWI/EAWI��info record���� */
    CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp
 ��������  : TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* ֪ͨTAF��ģ�飬���н��� */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* ֪ͨ��1��״̬�����ΪCNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_XCALL_XCC_ANSWER_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_APS_XCC_ANSWER_DATA_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CSMS_XCC_ANSWER_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_XPDS_XCC_ANSWER_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* ֪ͨTAF���н��� */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                         VOS_TRUE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* TO DO:������rel ind����û������ԭ��ֵ */
    /* ֪ͨTAF���н�����REL IND����ԭ��ֵ��ΪTAF_XCC_CAUSE_NORMAL_RELEASE */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_XCALL_XCC_HANGUP_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ֪ͨ�����REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ֪ͨXCALL�������� */
    if (VOS_TRUE == pstCallInfoCtx->ucIsCodecOpen)
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfoCtx->ucIsCodecOpen = VOS_FALSE;
    }

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CSMS_XCC_END_SMS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* ֪ͨ�����REL REQ */
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��APSģ�鷢��ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer
 ��������  : �յ�ID_XPDS_XCC_END_AGPS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��06��
   ��    ��   : y00314741
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* ֪ͨ�����REL REQ */
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);


    /*
       If the Call Control instance receives a message from layer 3Layer 3 which is
        included in the following list and every message field value is within its permissible
        range, the Call Control instance shall process the message as described below and
        in accordance with the message action time (see 2.6.4.1.5).
            1. Alert With Information Message: The Call Control instance shall reset the
            substate timer for T53m seconds. If this message does not contain a Signal
            information record, the mobile station should use standard alert as defined in
            3.7.5.5.
            2. Extended Alert With Information Message: The Call Control instance shall reset
            the substate timer for T53m seconds. If this message does not contain a Signal
            information record, the mobile station should use standard alert as defined in
            3.7.5.5.
            3. Maintenance Order: The mobile station shall reset the substate timer for T53m
            seconds.
         If the Call Control instance receives a message that is not included in the above list,
        cannot be processed, or requires a capability which is not supported, the Call
        Control instance shall discard the message and send a message rejected indication
        to the layer 3Layer 3, with the reject reason indicated.
    */

    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            /* ���AWI��EAWI�Ľ��� */
            pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
            if (VOS_NULL_PTR == pstAWIM)
            {
                return VOS_FALSE;
            }

            if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
                return VOS_FALSE;
            }

            /* ����T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

            /* ��XCALL����ID_XCC_XCALL_INFO_REC_IND*/
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                            CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                            (VOS_UINT8 *)pstAWIM);
            }

            /* ��ȷ�� TO DO: ��SMS/DATA CALL����ID_XCC_XCALL_INFO_REC_IND */

            PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            /* ���AWI��EAWI�Ľ��� */
            pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
            if (VOS_NULL_PTR == pstEAWIM)
            {
                return VOS_FALSE;
            }

            if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
                return VOS_FALSE;
            }

            /* ����T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

            /* ��XCALL����ID_XCC_XCALL_INFO_REC_IND*/
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                            CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                            (VOS_UINT8 *)pstEAWIM);
            }

            /* ��ȷ�� TO DO: ��SMS/DATA CALL����ID_XCC_XCALL_INFO_REC_IND */

            PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_MtCalling_WaitForAnswer(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG:
            /* ����REJ ORDER */
            NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

            pstCallInfoCtx              = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            stRejInfo.ucConRef          = pstCallInfoCtx->ucConRef;
            stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
            stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
            stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
            stRejInfo.ulL3PduBitLen     = 0;
            stRejInfo.pucPdudata        = aucPduData;
            CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

            /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
            CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                       0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer Wrong Msg type", pstDschDataInd->enDschMsgType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer
 ��������  : TI_CNAS_XCC_T53M������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ��AS����CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED,
                              VOS_FALSE);

    /* ֪ͨTAF���н�����REL IND����ԭ��ֵ��ΪTAF_XCC_CAUSE_NORMAL_RELEASE */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_T53M_TIME_OUT, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer
 ��������  : �ȴ�����ʱ���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* ֪ͨTAF���н��� */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer
 ��������  : ID_CNAS_XCC_XCC_ABORT_REQ������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* ����service type ��TAF����ҵ����ָֹʾ */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* ֪ͨAS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* ֪ͨTAF���н��� */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfoCtx,
                                              CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                              TAF_XCC_FAIL_LAYER_L3);

    /* �����VOICE CALL����SMS������Ҫ��APS���ָ� */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }


    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_CNF��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ���ر����segnum��AS�ϱ������Ĳ�һ�£����ӵ�������Ϣ */
    if ( pstCallInfo->ucMsgSeqNum != pstDataCnf->ucMsgSeqNum )
    {
        return VOS_TRUE;
    }

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstDataCnf->enRslt)
    {

        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* ����SO�����жϣ�����Ӧģ��ظ�ANSWER CNF */
        CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_SUCCESS, TAF_XCC_FAIL_LAYER_BUTT);

        if (VOS_TRUE == pstCallInfo->ucIsSoNegCmplt)
        {
            /* ֪ͨXCALL��CODEC */
            if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
              && (VOS_FALSE == pstCallInfo->ucIsCodecOpen) )
            {
                CNAS_XCC_SndXcallCodecOpenInd(pstCallInfo);
                pstCallInfo->ucIsCodecOpen = VOS_TRUE;
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                CNAS_XCC_SndApsDataServiceConnectInd(pstCallInfo);
            }

            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                CNAS_XCC_SndCsmsServiceConnectInd(pstCallInfo);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsServiceConnectInd(pstCallInfo);
            }
        }

        /* ��״̬����L1״̬��Ǩ��CONVERSATION״̬ */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();
    }
    else
    {
        /* ERROR LOG */
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack: unexpected result !",
                          pstDataCnf->enRslt);

        /* ֪ͨ�����REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* ֪ͨTAF��ģ�飬���н��� */
        CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_CONNECT_ORDER_ACK_FAILURE, TAF_XCC_FAIL_LAYER_L3);

        /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* �˳���2״̬�� */
        CNAS_XCC_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* ֪ͨTAF��ģ�飬���н��� */
    /* TO DO:������rel ind����û������ԭ��ֵ */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, TAF_XCC_FAIL_LAYER_L3);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_XCALL_XCC_HANGUP_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ֪ͨ�����REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ֪ͨXCALL�������� */
    if (VOS_TRUE == pstCallInfo->ucIsCodecOpen)
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfo->ucIsCodecOpen = VOS_FALSE;
    }

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_APS_XCC_HANGUP_DATA_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��APSģ�鷢��ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_CSMS_XCC_END_SMS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��SMSģ�鷢��ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack
 ��������  : �յ�ID_XPDS_XCC_END_AGPS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��06��
   ��    ��   : y00314741
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfoCtx->ucCallId);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack
 ��������  : TI_CNAS_XCC_WAIT_CONN_L2_ACK������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();


    /* ֪ͨTAF��ģ�飬���н��� */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_L2_ACK_TIME_OUT, TAF_XCC_FAIL_LAYER_L3);

    /* ֪ͨAS REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack
 ��������  : ID_CNAS_XCC_XCC_ABORT_REQ������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣ������ʱ�� */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* ֪ͨAS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack
 ��������  : �ȴ�L2 ACKʱ���յ��ػ�����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֹͣTI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* ֪ͨTAF��ģ�飬���н��� */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3);

    /* ֪ͨ��1��״̬�����CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* �˳���2״̬�� */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : CNAS_XCC_NotifyTafCallDisc_MtCalling
 ��������  : ֪ͨTAF��ģ�飬���н���
 �������  : pstCallInfo -- ״̬���ĺ�����Ϣ
             enCause     -- ����ԭ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyTafCallDisc_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_BOOL                            isNeedToResumeAps
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch(enServiceType)
    {
        case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            /* ֪ͨXCALL�������� */
            if (VOS_TRUE == pstCallInfo->ucIsCodecOpen)
            {
                CNAS_XCC_SndXcallCodecCloseInd();

                pstCallInfo->ucIsCodecOpen = VOS_FALSE;
            }

            /* ֪ͨXCALL���н��� */
            CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);

            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_VOICE_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* ֪ͨAPS���н��� */
            CNAS_XCC_SndApsDataCallDiscInd(pstCallInfo, enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* ����ط�ò��ȱ��SMS�ӿ� */
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_SMS);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafCallDisc_MtCalling: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling
 ��������  : ֪ͨTAF��ģ�飬���е�Ӧ����
 �������  : pstCallInfo -- ״̬���ĺ�����Ϣ
             enCause     -- ����ԭ��ֵ
             enFailLayer -- �쳣�Ĳ㼶
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32        enServiceType;

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch(enServiceType)
    {
        case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            CNAS_XCC_SndXcallAnswerCallCnf(pstCallInfo->ucCallId,
                                           pstCallInfo->ucConRef,
                                           pstCallInfo->enCurrentSo,
                                           enFailLayer,
                                           enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* ֪ͨAPS���н��� */
            CNAS_XCC_SndApsAnswerDataCallCnf(pstCallInfo->ucCallId,
                                             enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* ֪ͨsms���н��� */
            CNAS_XCC_SndCsmsAnswerCallCnf(pstCallInfo->ucCallId,
                                          enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            /* ֪ͨXPDS���н��� */
            CNAS_XCC_SndXpdsAnswerCallCnf(pstCallInfo->ucCallId,
                                          enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcOrderMsg_L1Main_WaitForOrder
 ��������  : ����տڵ�Order��Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��25��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForOrder(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: Decode FAIL ");
        return;
    }

    /* ��ȡ�����order��Ϣ���� */
    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: CAS_1X_MAIN_GetOrderSpecificMsgType FAIL ", ulRslt);

        return ;
    }

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* ͣT52M */
            CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

            /* ����ǻ���ģʽ�����Զ����� */
            if ( CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
            {
                CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
                return ;
            }

            /* ��XCALL����INCOMING CALL IND */
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                /* ��XCALL����INCOMING CALL IND */
                CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
            }

            /* SEND DATA CALL OR SMS incoming call ind */
            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                /* ��CSMS����INCOMING CALL IND */
                CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                /* ��APS����INCOMING CALL IND */
                CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
            }

            /* ��ά�ɲ⣬�ϱ�1x call state*/
            CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                    CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
            CNAS_XCC_SndXcc1xCallStateUpdateInd();

            /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

            /* ����TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
            CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
            break;

        default:
            CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation Wrong enOrderType", enOrderType);
            break;
    }

    return;

}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcOrderMsg_L1Main_WaitForAnswer
 ��������  : ����տڵ�Order��Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��25��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForAnswer(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: Decode FAIL ");
        return;
    }

    /* ��ȡ�����order��Ϣ���� */
    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: CAS_1X_MAIN_GetOrderSpecificMsgType FAIL ", ulRslt);

        return ;
    }

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* ����T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
            break;

        case CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL:
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_WaitForAnswer Ordertype", enOrderType);
            break;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer
 ��������  : ����XCALL/APS/CSMS�����Ľ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��25��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer(VOS_VOID)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucMsgSeqNum;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ֹͣTI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M);

    /* ����SEQ NUM */
    pstCallInfo->ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum              = pstCallInfo->ucMsgSeqNum;

    /* ��AS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(connect order) */
    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    CNAS_XCC_EncodeTxTchConnectOrderMsg(pstCallInfo->ucConRef, aucPduData, &ulPduDataLen);

    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,
                               ucMsgSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK);

    /* ����TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK, TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_AutoAnswerLoopBackService_MtCalling
 ��������  : ����ҵ����Զ�Ӧ����
 �������  : pstCallInfoCtx - ����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��20��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_AutoAnswerLoopBackService_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
)
{
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucMsgSeqNum;

    /* ����SEQ NUM */
    pstCallInfoCtx->ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum                 = pstCallInfoCtx->ucMsgSeqNum;

    /* ��AS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(connect order) */
    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    CNAS_XCC_EncodeTxTchConnectOrderMsg(pstCallInfoCtx->ucConRef, aucPduData, &ulPduDataLen);

    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,
                               ucMsgSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    /* ״̬Ǩ�Ƶ�CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK);

    /* ����TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK, TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN);
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : CNAS_XCC_CovertVoiceCallPagingIndSo
 ��������  : ������������ʱ��ǿ�ƽ������������͵�SO ת��ΪCAS_CNAS_1X_SO_3_EVRC
 �������  : struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��11��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_CovertVoiceCallPagingIndSo(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                 *enSo
)
{
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg   = VOS_NULL_PTR;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    /*����Э����Ҫ��"�����ն�Ӧ�ر���������ͨ����������ͨͨ���ͼ���ͨ������EVRC-B ����"������ǿ��ת��SO */
    if ((VOS_TRUE == pstCallNvimCfg->ucEccSrvCap)
     && (VOS_TRUE == pstCallNvimCfg->ucEccSrvStatus))
    {
        if ((CAS_CNAS_1X_SO_3_EVRC       == (*enSo))
         || (CAS_CNAS_1X_SO_17_VOICE_13K == (*enSo))
         || (CAS_CNAS_1X_SO_68_EVRC_B    == (*enSo))
         || (CAS_CNAS_1X_SO_73_EVRC_NW   == (*enSo))
         || (CAS_CNAS_1X_SO_18_OTASP     == (*enSo)))
        {
            *enSo = CAS_CNAS_1X_SO_3_EVRC;
        }
    }
}
#endif


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





