/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcApp.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF X CALL��������APP����Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcApp.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "TafAgentInterface.h"
#include "MnComm.h"
#include "TafLog.h"

#include "TafSdcCtx.h"
#include "TafXCallProcXcc.h"

#include "TafCdmaPlusTranslate.h"

#include "TafMmaSndOm.h"

#include "TafStdlib.h"

#include "TafXCallProcEccSrv.h"

#include "TafXCallProcNvim.h"
#include "TafSpmComFunc.h"
#include "TafSdcLib.h"
#include "MnCallCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_APP_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppCallOrigReq
 ��������  : ����MN_CALL_APP_ORIG_REQ��Ϣ,(AT&STKͳһʹ�øú���)
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppCallOrigReq(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstCallOrig = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsSrvStatus;

    enCsSrvStatus                       = TAF_SDC_GetCsServiceStatus();

    ucCallId                            = 0;
    pstCallOrig                         = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;

    /* �жϵ�ǰ�Ƿ���Է������ */
    ulRet = TAF_XCALL_IsAllowMoCallInCurrentStatus(pstCallOrig->unParm.stOrig.enCallType);

    /* �ж��Ƿ���������� */
    if (VOS_FALSE == ulRet)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
#endif

        /* �ϱ�����ʧ�� */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NOT_ALLOW,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->clientId,
                                 pstCallOrig->unParm.stOrig.enCallType);

        return;
    }

    /* ����call Id */
    ulRet = TAF_XCALL_AllocCallId(&ucCallId);
    if (VOS_FALSE == ulRet)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
#endif

        /* �ϱ�����ʧ�� */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NO_CALL_ID,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->clientId,
                                 pstCallOrig->unParm.stOrig.enCallType);

        return;
    }

    /* �½�һ������ʵ�� */
    TAF_XCALL_CreateMoCallEntity(ucCallId, pstCallOrig);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* TO DO:��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    /* TAF_SendMtcCsSrvInfoInd(); */
#endif

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_ORIG_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif

    /* ���ݵ�ǰ1X�ķ���״̬�ж��Ƿ���Ҫ���ͺ��������XCC,�����ǰ����������,
       ������XCC��������,�ز������ֱ��֪ͨXSD�����ز�;���򷢸�XCC */

    /* ֪ͨMMA CALL NTF */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, pstCallOrig->clientId, TAF_XCALL_BuildMmaCallType(pstCallOrig->unParm.stOrig.enCallType));

    /* �ظ����гɹ� */
    TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_SUCCESS,
                             pstCallOrig->ulSenderPid,
                             pstCallOrig->clientId,
                             pstCallOrig->unParm.stOrig.enCallType);

    /* �ϱ������¼� */
    TAF_XCALL_SndCallOrigInd(ucCallId);

    /* ����silent redial��ʱ�� */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TAF_XCALL_GetRedialPeriodTimerLen(ucCallId), ucCallId);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsSrvStatus)
    {
        /* ���ͺ�����Ϣ��XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);

        return;
    }

    if (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsSrvStatus)
    {
        /* ��������Limit Service��ֱ�ӷ������ */
        if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
        {
            /* ���ͺ�����Ϣ��XCC */
            TAF_XCALL_SndXccOrigCallReq(ucCallId);

            return;
        }

        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

        return;
    }

    if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
    {
        TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                     pstCallOrig->clientId,
                                     TAF_XCALL_BuildMmaCallType(pstCallOrig->unParm.stOrig.enCallType),
                                     TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE);
    }

    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppSupsCmdReq
 ��������  : ����MN_CALL_APP_SUPS_CMD_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSupsCmdReq(VOS_VOID *pMsg)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstAppCallSupsReq = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;
    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* 1����ǰ��һ·����active״̬��ͨ��:
        ������յ�APP��orig����ֱ�ӻظ�ʧ�ܣ�
        Ҳ�����յ�XCC��incoming��Ϣ��
        ֻ����flash��Ϣ
        ���Դ���active״̬��ͨ��ֻ��һ·�����Ҳ���������״̬��ͨ������

        2����ʱ������·ͨ���ĳ���:
        ��һ·����dialing״̬��ͨ������ʱ���յ�XCC��incoming��Ϣ
     */

    switch (pstCallSupsParam->enCallSupsCmd)
    {
        /* CHLD=0, Releases all held calls or sets User Determined User Busy (UDUB) for a waiting call */
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(pstAppCallSupsReq);
            break;

        /* CHLD=1, Releases all active calls (if any exist) and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(pstAppCallSupsReq);
            break;

        /* CHLD=1x, Releases a specific active call X*/
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            TAF_XCALL_ProcCallSupsCmdRelCallXReq(pstAppCallSupsReq);
            break;

        /* ATH, Release all calls */
        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            TAF_XCALL_ProcCallSupsCmdRelAllCallReq(pstAppCallSupsReq);
            break;

        /* CHLD=2, Places all active calls (if any exist) on hold and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(pstAppCallSupsReq);
            break;

        default:
            /* ���������ֱ�ӻظ�ʧ�� */
            TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                    pstAppCallSupsReq->clientId,
                                    pstAppCallSupsReq->opId,
                                    pstCallSupsParam->callId,
                                    TAF_CS_CAUSE_NOT_ALLOW);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppSendFlashReq
 ��������  : ����TAF_CALL_APP_SEND_FLASH_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��7��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
  3.��    ��   : 2015��07��23��
    ��    ��   : y00307564
    �޸�����   : ����"+"��ת���߼��޸�
  4.��    ��   : 2015��08��10��
    ��    ��   : y00307564
    �޸�����   : DTS2015080608576�޸�

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_CALL_APP_SEND_FLASH_REQ_STRU   *pstFlashReqMsg;
    VOS_UINT8                           ucDstDigitNum;
    VOS_UINT8                           aucDstDigit[TAF_CALL_MAX_FLASH_DIGIT_LEN + 1];

    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    VOS_UINT32                          ulRslt;

    pstFlashReqMsg = (TAF_CALL_APP_SEND_FLASH_REQ_STRU *)pMsg;

    /* ����״̬���Ҵ���ACTIVE״̬��call id��Ŀǰֻ֧����ACTIVE״̬�·���Flash */
    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    /* ����Active״̬��ʵ������ֻ����1�� */
    if (1 != ulNumOfCalls)
    {
        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);
        return;
    }

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    PS_MEM_SET(&(pstCallEntity->stFlashInfo), 0x00, sizeof(TAF_XCALL_FLASH_INFO_STRU));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(MN_CALL_CALLED_NUM_STRU));

    pstCallEntity->stFlashInfo.ucIsEmcCall = VOS_FALSE;

    if ('+' == pstFlashReqMsg->stFlashPara.aucDigit[0])
    {
        ulRslt = TAF_STD_ConvertAsciiNumberToBcd(((VOS_CHAR *)pstFlashReqMsg->stFlashPara.aucDigit) + 1,
                                                              stDialNumber.aucBcdNum,
                                                             &stDialNumber.ucNumLen);

        stDialNumber.enNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

    }
    else
    {

        ulRslt = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)pstFlashReqMsg->stFlashPara.aucDigit,
                                                             stDialNumber.aucBcdNum,
                                                            &stDialNumber.ucNumLen);

        stDialNumber.enNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    }

    if (MN_ERR_NO_ERROR != ulRslt)
    {
        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);

        return;
    }

    if (VOS_TRUE  == TAF_SPM_IsEmergencyNum_CDMA(&stDialNumber,
                                                 &stEmergencyCat.bExist,
                                                 &stEmergencyCat.ucEmergencyCat))
    {
        pstCallEntity->stFlashInfo.ucIsEmcCall = VOS_TRUE;
    }

    ucDstDigitNum = 0;
    PS_MEM_SET(aucDstDigit, 0x00, sizeof(aucDstDigit));

    TAF_XCALL_ReplaceFlashPlusWithDigit(pstFlashReqMsg->stFlashPara.ucDigitNum,
                                        pstFlashReqMsg->stFlashPara.aucDigit,
                                        &ucDstDigitNum,
                                        aucDstDigit);

    /* ��XCC����ID_XCALL_XCC_SEND_FLASH_REQ */
    if (VOS_OK != TAF_XCALL_SndXccFlashReq(aucCallIds[0],
                                           ucDstDigitNum,
                                           aucDstDigit,
                                           pstCallEntity->stFlashInfo.ucIsEmcCall))
    {
        PS_MEM_SET(&(pstCallEntity->stFlashInfo), 0x00, sizeof(TAF_XCALL_FLASH_INFO_STRU));

        TAF_XCALL_SndFlashRslt(pstFlashReqMsg->usClientId, pstFlashReqMsg->ucOpId, VOS_ERR);
        return;
    }

    pstCallEntity->stFlashInfo.stClientInfo.ulModuleId = pstFlashReqMsg->ulSenderPid;
    pstCallEntity->stFlashInfo.stClientInfo.usClientId = pstFlashReqMsg->usClientId;
    pstCallEntity->stFlashInfo.stClientInfo.ucOpId     = pstFlashReqMsg->ucOpId;

    if (VOS_TRUE == pstCallEntity->stFlashInfo.ucIsEmcCall)
    {
        PS_MEM_CPY(&pstCallEntity->stFlashInfo.stDialNumber, &stDialNumber, sizeof(MN_CALL_CALLED_NUM_STRU));

        TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_EMERGENCY_VOICE_CALL);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq
 ��������  : ����MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB����
 �������  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* �Ҷ�Incoming״̬�ĺ��У�Incoming״̬�ĺ���ֻ����һ�� */
    if (1 == ulNumOfCalls)
    {
        /* �Ҷϸú��� */
        TAF_XCALL_SndXccHangUpCallReq(aucCallIds[0], TAF_XCC_END_REASON_NORMAL_RELEASE);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ����client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        TAF_XCALL_UpdateCcCause(aucCallIds[0], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

        /* ��¼���йҶϵķ��� */
        TAF_XCALL_UpdateDiscCallDir(aucCallIds[0], VOS_TRUE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);
#endif

        /* �ظ������� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        /* �ظ�ʧ�� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq
 ��������  : ����MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH����
 �������  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    /* active call��incoming call������ͬʱ���ڣ����Ի��߹Ҷ�active call���߽���incoming call */
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    if (0 != ulNumOfCalls)
    {
        /* Ŀǰֻ������һ��active״̬�ĺ��� */
        for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
        {
            /* �Ҷϸú��� */
            TAF_XCALL_SndXccHangUpCallReq(aucCallIds[i], TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);

            /* ����client info */
            TAF_XCALL_UpdateClientInfo(aucCallIds[i],
                                       pstAppCallSupsReq->ulSenderPid,
                                       pstAppCallSupsReq->clientId,
                                       pstAppCallSupsReq->opId);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

            /* ��¼���йҶϵķ��� */
            TAF_XCALL_UpdateDiscCallDir(aucCallIds[i], VOS_TRUE);

        }

        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);

#endif

        /* �ظ������� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* Incoming״̬�ĺ���ֻ����һ�� */
    if (1 == ulNumOfCalls)
    {
        /* �����ú��� */
        TAF_XCALL_SndXccAnswerCallReq(aucCallIds[0]);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_ANS, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ����client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* �ظ������� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCallSupsCmdRelCallXReq
 ��������  : ����MN_CALL_SUPS_CMD_REL_ALL_CALL���󣬹Ҷ�ָ������
 �������  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelCallXReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;

    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* �ж�Call Id����Ч�� */
    if (VOS_TRUE != TAF_XCALL_IsAvailCallId(pstCallSupsParam->callId))
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstCallSupsParam->callId);

    if (MN_CALL_S_IDLE == enCallState)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

        return;
    }

    if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId))
    {
        /* ֹͣ��ʱ�� */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstCallSupsParam->callId);
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId);

        /* ֪ͨ������ֹ */
        enCallType = TAF_XCALL_GetCallType(pstCallSupsParam->callId);
        usClientId = TAF_XCALL_GetClientInfo(pstCallSupsParam->callId)->usClientId;
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        TAF_XCALL_UpdateCcCause(pstCallSupsParam->callId, TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

        /* ��¼���йҶϵķ��� */
        TAF_XCALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);
#endif

        /* �ظ������� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
        TAF_XCALL_SndCallReleaseInd(pstCallSupsParam->callId);

        /* ��ն�Ӧ��ʵ����Ϣ */
        TAF_XCALL_FreeCallEntity(pstCallSupsParam->callId);

        return;

    }

    /* ֹͣ�ز���ʱ��,�����ʱ��δ������call id��һ�������� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstCallSupsParam->callId);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, pstCallSupsParam->callId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           (VOS_VOID *)pstAppCallSupsReq,
                           VOS_NULL_PTR);
#endif

    /* �Ҷϸú��� */
    TAF_XCALL_SndXccHangUpCallReq(pstCallSupsParam->callId, TAF_XCC_END_REASON_NORMAL_RELEASE);

    TAF_XCALL_RegSsKeyEvent(pstCallSupsParam->callId, TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

    /* ����client info */
    TAF_XCALL_UpdateClientInfo(pstCallSupsParam->callId,
                               pstAppCallSupsReq->ulSenderPid,
                               pstAppCallSupsReq->clientId,
                               pstAppCallSupsReq->opId);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    TAF_XCALL_UpdateCcCause(pstCallSupsParam->callId, TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

    /* ��¼���йҶϵķ��� */
    TAF_XCALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

    /* �ظ������� */
    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCallSupsCmdRelAllCallReq
 ��������  : ����MN_CALL_SUPS_CMD_REL_ALL_CALL���󣬹Ҷ����к���
 �������  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��7��23��
    ��    ��   : c00299063
    �޸�����   : DTS2015072309638
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdRelAllCallReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    /* ��ʱ������·ͨ���ĳ���:
        ��һ·����dialing״̬��ͨ������ʱ���յ�XCC��incoming��Ϣ
     */
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    VOS_UINT8                           i;

    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulModuleId;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    ulModuleId = pstAppCallSupsReq->ulSenderPid;

    /* ѭ���Ҷ����з�idle�ĺ��� */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstAppCallSupsReq,
                               VOS_NULL_PTR);
#endif

        /* ֹͣ�ز�ʱ����ʱ�� */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, aucCallIds[i]);

        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]))
        {
            /* ֹͣ�ز������ʱ�� */
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]);

            /* ֪ͨ������ֹ */
            enCallType = TAF_XCALL_GetCallType(aucCallIds[i]);
            usClientId = TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId;
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

            /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
            TAF_XCALL_SndCallReleaseInd(aucCallIds[i]);

            /* ��ն�Ӧ��ʵ����Ϣ */
            TAF_XCALL_FreeCallEntity(aucCallIds[i]);

            /* ��¼ulModuleId*/
            ulModuleId = TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId;
        }
        else
        {
            /* �Ҷϸú��� */
            TAF_XCALL_SndXccHangUpCallReq(aucCallIds[i], TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);

            /* ����client info */
            TAF_XCALL_UpdateClientInfo(aucCallIds[i],
                                       pstAppCallSupsReq->ulSenderPid,
                                       pstAppCallSupsReq->clientId,
                                       pstAppCallSupsReq->opId);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_MS_NORMAL_RELEASE);

            /* ��¼���йҶϵķ��� */
            TAF_XCALL_UpdateDiscCallDir(aucCallIds[i], VOS_TRUE);
        }
    }

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* ���SDC��CS���б�־ */
            TAF_XCALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        }

        /* ��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
    else
    {

        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);
    }


    /* �ظ������� */
    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq
 ��������  : ����MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH����
 �������  : MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;

    pstCallSupsParam  = &(pstAppCallSupsReq->unParm.stCallMgmtCmd);

    /* ����active״̬��ͨ��ֻ��һ·�����Ҳ���������״̬��ͨ������

        ������·ͨ���ĳ���:
        ��һ·����dialing״̬��ͨ������ʱ���յ�XCC��incoming��Ϣ */

    /* 3GPP2��hold��������ͨ��FLASH��Ϣ�������յ�������ֻ�жϵ�ǰ�Ƿ���incoming call */

    /* ���û��incoming call����һ��active�ģ�����bypassΪtrue���ظ��ɹ� */

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    if (1 == ulNumOfCalls)
    {
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], MN_CALL_SS_RES_SUCCESS);

        /* ����Ҫ��APP�ϱ�MN_CALL_EVT_CONNECT�¼������յ�XCC��connect indʱ���ϱ� */

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aucCallIds);

    /* Incoming״̬�ĺ���ֻ����һ�� */
    if (1 == ulNumOfCalls)
    {
        /* �����ú��� */
        TAF_XCALL_SndXccAnswerCallReq(aucCallIds[0]);

        TAF_XCALL_RegSsKeyEvent(aucCallIds[0], TAF_XCALL_SS_PROG_EVT_ANS, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ����client info */
        TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                   pstAppCallSupsReq->ulSenderPid,
                                   pstAppCallSupsReq->clientId,
                                   pstAppCallSupsReq->opId);

        /* �ظ������� */
        TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                                pstAppCallSupsReq->clientId,
                                pstAppCallSupsReq->opId,
                                aucCallIds[0], TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_XCALL_SndSupsCmdCnf(pstAppCallSupsReq->ulSenderPid,
                            pstAppCallSupsReq->clientId,
                            pstAppCallSupsReq->opId,
                            pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppSendBurstDTMFReq
 ��������  : ����TAF_CALL_SEND_BURST_DTMF_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16�޸ģ�Cont DTMF��Burst DTMF�ĵȴ�XCC��Ӧ����һ����־
  3.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : DTS2015081708770�޸ģ���xcc������Ϣǰ��
                �ж϶�ʱ��StopAndStartContDtmfInterval�Ƿ�������̬
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendBurstDTMFReq(VOS_VOID *pMsg)
{
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU                       *pstBurstDTMFReqMsg;
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8             enResult;

    pstBurstDTMFReqMsg = (TAF_CALL_BURST_DTMF_REQ_MSG_STRU *)pMsg;

    /* �жϸ�call_id��Ӧ��״̬�Ƿ�ΪACTIVE,Ŀǰֻ֧���ڸ�״̬�·���Burst DTMF  */
    if(MN_CALL_S_ACTIVE != TAF_XCALL_GetCallState(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
    {
        /* send TAF_CALL_EVT_SEND_BURST_DTMF_CNF */
        TAF_XCALL_SndBurstDTMFCnf(pstBurstDTMFReqMsg->usClientId,
                                  pstBurstDTMFReqMsg->ucOpId,
                                  TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ABNORMAL_STATE,
                                  pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId);
        return;
    }

    /*����ȴ�XCC�ظ���Burst DTMF CNF��Ϣ�ı�ʶΪVOS_FALSE��XCALL���Ը�XCC����ID_XCALL_XCC_BURST_DTMF_REQ��Ϣ
      ����ȴ�XCC�ظ���Burst DTMF CNF��Ϣ�ı�ʶΪVOS_TRUE,XCALL��Ҫ�ȴ������е�ID_XCALL_XCC_BURST_DTMF_REQ�Ļظ���Ϣ��
      ͬʱ�������յ���TAF_CALL_SEND_BURST_DTMF_REQ��Ϣ��������
    */
    if(TAF_XCALL_WAIT_NO_XCC_CNF == TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
    {
        /* �����ʱ״̬Ϊ:�յ�Start Cont Dtmf Req����Ӧ�����Ƕ�ʱ����������̬����ʱ�յ���Ϣ��Ӧ�û���
            �ȴ���ʱ����ʱ���ٴ���
        */
        if (TAF_XCALL_TIMER_STATUS_RUNING
            == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId))
        {
            enResult = TAF_XCALL_SaveBurstDtmfInfo(pstBurstDTMFReqMsg);
        }
        else
        {
            enResult = TAF_XCALL_SndXccBurstDTMFReq(&pstBurstDTMFReqMsg->stBurstDTMFPara);

            TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF);
        }

    }
    else
    {
        enResult = TAF_XCALL_SaveBurstDtmfInfo(pstBurstDTMFReqMsg);
    }

    /* �ظ�XCALL TAF_CALL_EVT_SEND_BURST_DTMF_CNF (ucResult)*/
    TAF_XCALL_SndBurstDTMFCnf(pstBurstDTMFReqMsg->usClientId,
                              pstBurstDTMFReqMsg->ucOpId,
                              enResult,
                              pstBurstDTMFReqMsg->stBurstDTMFPara.ucCallId);

    return;
}

/* Buffer����������XCallProcAppŲ��XCallCtx.c�� */


/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetRedialPeriodTimerLen
 ��������  : ��ȡ�ز���ʱ��ʱ��
 �������  : VOS_UINT8    ucCallIds
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetRedialPeriodTimerLen(
    VOS_UINT8                           ucCallId
)
{
    if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(ucCallId))
    {
        return TAF_XCALL_GetConfigInfo()->ulEmcRedialPeriod;
    }
    else
    {
        return TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN;
    }
}

/* ɾ����Ч�ĺ��� */

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppGetCallInfoReq
 ��������  : ����ID_TAFAGENT_MN_GET_CALL_INFO_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAgentGetCallInfoReq(VOS_VOID *pMsg)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU                    *pstCnf;
    VOS_UINT8                                               ucCallId;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity = VOS_NULL_PTR;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_XCALL_RcvAppGetCallInfoReq:alloc msg failed.");
        return;
    }

    PS_MEM_SET(pstCnf, 0x00, sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));


    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_S_IDLE != pstXcallEntity->enCallState))

        {
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].callId       = ucCallId;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallType   = pstXcallEntity->enCallType;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallState  = pstXcallEntity->enCallState;

            (pstCnf->ucNumOfCalls)++;
        }
    }

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;

    PS_SEND_MSG(WUEPS_PID_TAF, pstCnf);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppGetCallInfoReq
 ��������  : ����MN_CALL_APP_GET_INFO_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppGetCallInfoReq(VOS_VOID *pMsg)
{
    MN_CALL_INFO_QRY_CNF_STRU          *pstAppCnfMsg   = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCallId;


    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;

    /* ��ʼ�� */
    usLength     = 0;

    pstAppCnfMsg = (MN_CALL_INFO_QRY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                    sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAppCnfMsg)
    {
        return;
    }
    /* ��ȡ��ǰ����״̬��ΪIDLE�ĺ�����Ϣ */
    /*�������к��п���ʵ��*/
    VOS_MemSet(pstAppCnfMsg, 0x00, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_S_IDLE != pstXcallEntity->enCallState))

        {
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].callId      = ucCallId;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallDir   = pstXcallEntity->enCallDir;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallState = pstXcallEntity->enCallState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enMptyState = MN_CALL_NOT_IN_MPTY;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallType  = pstXcallEntity->enCallType;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCallNumber),
                       &(pstXcallEntity->stCallNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stConnectNumber),
                       &(pstXcallEntity->stConnectNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCalledNumber),
                       &(pstXcallEntity->stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            (pstAppCnfMsg->ucNumOfCalls)++;
        }
    }

    /* ��д�¼����� */
    pstAppCnfMsg->enEvent  = MN_CALL_EVT_CLCC_INFO;
    pstAppCnfMsg->clientId = MN_GetRealClientId(pstCallMsg->clientId, WUEPS_PID_TAF);

    /* ȷ����Ϣ���� */
    usLength = (TAF_UINT16)sizeof(MN_CALL_INFO_QRY_CNF_STRU);

    /* ͨ���첽��Ϣ���͸�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstAppCnfMsg, usLength);

    PS_MEM_FREE(WUEPS_PID_TAF, pstAppCnfMsg);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppXlemaReq
 ��������  : �����������ѯ����
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��6��
    ��    ��   : h0246512
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppXlemaReq(VOS_VOID *pMsg)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg      = VOS_NULL_PTR;
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo   = VOS_NULL_PTR;

    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU*)pMsg;

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_XCALL_RcvAppXlemaReq: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_XLEMA_CNF;
    pstEccNumInfo->usClientId = pstCallMsg->clientId;

    /* ��ȡ�������б� */
    TAF_XCALL_GetEccNumList(pstEccNumInfo);

    TAF_XCALL_SndXlemaCnf(pstEccNumInfo);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstEccNumInfo);
    return;
}



/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppCallOrigReq
 ��������  : ����MN_CALL_APP_ORIG_REQ��Ϣ,(AT&STKͳһʹ�øú���)
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppCustomDialReq(VOS_VOID *pMsg)
{
    VOS_UINT32                                    ulRet;
    VOS_UINT8                                     ucCallId;
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU       *pstCallOrig = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU                   *pstCallEntity = VOS_NULL_PTR;

    ucCallId                            = 0;
    pstCallOrig                         = (TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *)pMsg;

    /* �жϵ�ǰ�Ƿ���Է������ */
    ulRet = TAF_XCALL_IsAllowMoCallInCurrentStatus(pstCallOrig->stCustomDialPara.enCallType);

    /* �ж��Ƿ���������� */
    if (VOS_FALSE == ulRet)
    {
        /* �ϱ�����ʧ�� */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NOT_ALLOW,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->usClientId,
                                 pstCallOrig->stCustomDialPara.enCallType);

        return;
    }

    /* ����call Id */
    ulRet = TAF_XCALL_AllocCallId(&ucCallId);
    if (VOS_FALSE == ulRet)
    {
        /* �ϱ�����ʧ�� */
        TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_NO_CALL_ID,
                                 pstCallOrig->ulSenderPid,
                                 pstCallOrig->usClientId,
                                 pstCallOrig->stCustomDialPara.enCallType);

        return;
    }

    /* �½�һ������ʵ�� */
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    /* ��¼����callҵ���û�����Ϣ(AT/STK) */
    TAF_XCALL_UpdateClientInfo(ucCallId,
                               pstCallOrig->ulSenderPid,
                               pstCallOrig->usClientId,
                               pstCallOrig->ucOpId);
    /* ��ʼ�����в��� */
    pstCallEntity->enCallDir            = MN_CALL_DIR_MO;
    pstCallEntity->enCallState          = MN_CALL_S_DIALING;
    pstCallEntity->enCallType           = pstCallOrig->stCustomDialPara.enCallType;
    pstCallEntity->enCause              = TAF_CS_CAUSE_SUCCESS;
    pstCallEntity->ucConnectId          = 0;
    pstCallEntity->ucConRef             = 0;
    pstCallEntity->enSo                 = (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCallOrig->stCustomDialPara.ulSo;
    pstCallEntity->ucIsAlertAnsByPass   = VOS_FALSE;


    /* ��ʼ�����к��� */
    PS_MEM_CPY(&pstCallEntity->stCalledNumber,
               &pstCallOrig->stCustomDialPara.stDialNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    /* TO DO:����SDC��CS���б�־ */
    /* TAF_SDC_SetCsCallExistFlg(VOS_TRUE); */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* TO DO:��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    /* TAF_SendMtcCsSrvInfoInd(); */
#endif

    /* ���ݵ�ǰ1X�ķ���״̬�ж��Ƿ���Ҫ���ͺ��������XCC,�����ǰ����������,
       ������XCC��������,�ز������ֱ��֪ͨXSD�����ز�;���򷢸�XCC */

    /* ֪ͨMMA CALL NTF */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, pstCallOrig->usClientId, TAF_XCALL_BuildMmaCallType(pstCallOrig->stCustomDialPara.enCallType));

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        /* ���ͺ�����Ϣ��XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);

        /* ����silent redial��ʱ�� */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN, ucCallId);
    }
    else
    {


        /* ����silent redial��ʱ�� */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN, ucCallId);

        TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);
    }

    /* �ظ����гɹ� */
    TAF_XCALL_SndCallOrigCnf(TAF_CS_CAUSE_SUCCESS,
                             pstCallOrig->ulSenderPid,
                             pstCallOrig->usClientId,
                             pstCallOrig->stCustomDialPara.enCallType);

    /* �ϱ������¼� */
    TAF_XCALL_SndCallOrigInd(ucCallId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppSendContDTMFReq
 ��������  : ����ATģ�鷢����TAF_CALL_SEND_CONT_DTMF_REQ��Ϣ������XCCת�����򻺴�
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
  2.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : DTS2015081708770�޸ģ���xcc������Ϣǰ��
                �ж϶�ʱ��StopAndStartContDtmfInterval�Ƿ�������̬
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppSendContDTMFReq(VOS_VOID *pMsg)
{
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU                        *pstContDTMFReqMsg;
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8              enResult;
    MN_CALL_STATE_ENUM_U8                                   enCallState;

    pstContDTMFReqMsg = (TAF_CALL_CONT_DTMF_REQ_MSG_STRU *)pMsg;

    /* �жϸ�call_id��Ӧ��״̬�Ƿ�ΪACTIVE,Ŀǰֻ֧���ڸ�״̬�·���CONT DTMF  */
    enCallState = TAF_XCALL_GetCallState(pstContDTMFReqMsg->stContDTMFPara.ucCallId);
    if (MN_CALL_S_ACTIVE != enCallState)
    {
        TAF_ERROR_LOG2(WUEPS_PID_TAF,"TAF_XCALL_RcvAppSendContDTMFReq: Call State is error. CallID:, State:",
                      pstContDTMFReqMsg->stContDTMFPara.ucCallId, enCallState);

        /* ����ACTIVE̬����AT����TAF_CALL_EVT_SEND_CONT_DTMF_CNF */
        TAF_XCALL_SndContDTMFCnf(pstContDTMFReqMsg->usClientId,
                                 pstContDTMFReqMsg->ucOpId,
                                 TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ABNORMAL_STATE,
                                 pstContDTMFReqMsg->stContDTMFPara.ucCallId);
        return;
    }

    /*����ȴ�XCC�ظ���Cont DTMF CNF��Ϣ�ı�ʶΪVOS_FALSE��XCALL���Ը�XCC����ID_XCALL_XCC_CONT_DTMF_REQ��Ϣ
      ����ȴ�XCC�ظ���Cont DTMF CNF��Ϣ�ı�ʶΪVOS_TRUE,XCALL��Ҫ�ȴ������е�ID_XCALL_XCC_CONT_DTMF_REQ�Ļظ���Ϣ��
      ͬʱ�������յ���TAF_CALL_SEND_CONT_DTMF_REQ��Ϣ��������
    */
    if (TAF_XCALL_WAIT_NO_XCC_CNF == TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId))
    {
        /* �����ʱ״̬Ϊ:�յ�Start Cont Dtmf Req����Ӧ�����Ƕ�ʱ����������̬����ʱ�յ���Ϣ��Ӧ�û���,
            �ȴ���ʱ����ʱ���ٴ���
        */
        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                                                      pstContDTMFReqMsg->stContDTMFPara.ucCallId))
        {
            enResult = TAF_XCALL_SaveContDtmfInfo(pstContDTMFReqMsg);
        }
        else
        {
            enResult = TAF_XCALL_SndXccContDTMFReq(&pstContDTMFReqMsg->stContDTMFPara);

            /* ��XCC����ID_XCALL_XCC_SEND_CONT_DTMF_REQ�����ñ�ʶ,������start����stop */
            if (TAF_CALL_CONT_DTMF_START == pstContDTMFReqMsg->stContDTMFPara.enSwitch)
            {
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF);
            }
            else
            {
                TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstContDTMFReqMsg->stContDTMFPara.ucCallId, TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF);
            }
        }
    }
    else
    {
        enResult = TAF_XCALL_SaveContDtmfInfo(pstContDTMFReqMsg);
    }

    /* �ظ�XCALL TAF_CALL_EVT_SEND_CONT_DTMF_CNF (ucResult)*/
    TAF_XCALL_SndContDTMFCnf(pstContDTMFReqMsg->usClientId,
                             pstContDTMFReqMsg->ucOpId,
                             enResult,
                             pstContDTMFReqMsg->stContDTMFPara.ucCallId);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReplaceFlashPlusWithDigit
 ��������  : ��^CFSH�����к���Я���ļӺ�ת��Ϊ����
 �������  : VOS_UINT8      ucSrcDigitNum ---�·���^CFSH������Я���ĺ������
             VOS_UINT8     *pucSrcDigit   ---�·���^CFSH������Я���ĺ���
 �������  : VOS_UINT8      ucDstDigitNum ---ת����ĺ������
             VOS_UINT8     *pucDstDigit   ---ת����ĺ���
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��23��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��31��
    ��    ��   : h00313353
    �޸�����   : DTS2015122804554
*****************************************************************************/
VOS_VOID TAF_XCALL_ReplaceFlashPlusWithDigit(
    VOS_UINT8                           ucSrcDigitNum,
    VOS_UINT8                          *pucSrcDigit,
    VOS_UINT8                          *pucDstDigitNum,
    VOS_UINT8                          *pucDstDigit
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    MN_CALL_NUM_TYPE_ENUM_U8            enCurNumType;
    VOS_INT32                           lSid;

    if (0 != ucSrcDigitNum)
    {
        /* ���мӺţ���¼�ú���Ϊ���ʺ��룬����Ϊunknown */
        if ('+' == pucSrcDigit[0])
        {
            enCurNumType = (VOS_UINT8)(0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

            i = 1;
        }
        else
        {
            enCurNumType = (VOS_UINT8)(0x80 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);

            i = 0;
        }

        j = 0;
        for (; i < ucSrcDigitNum; i++)
        {
            pucDstDigit[j] = pucSrcDigit[i];

            j++;
        }

        *pucDstDigitNum = j;

        lSid              = TAF_SDC_GetSdcCtx()->stNetworkInfo.lSid;

        /* �Ӻ�ת�� */
        TAF_TranslatePlusToNum(lSid, TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE, &enCurNumType, pucDstDigit, pucDstDigitNum);
    }
    else
    {
        *pucDstDigitNum = 0;
        pucDstDigit[0]  = '\0';
    }
}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAtCclprGetReq
 ��������  : ����TAF_CALL_APP_SND_CCLPR_REQ��Ϣ,����Դ�����������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAtCclprGetReq(VOS_VOID *pstMsg)
{
    TAF_CALL_EVT_CCLPR_GET_CNF_STRU                         stAppCnfMsg;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity = VOS_NULL_PTR;
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU                        *pstCallMsg = VOS_NULL_PTR;

    pstCallMsg = (TAF_CALL_SND_CCLPR_REQ_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stAppCnfMsg, 0x00, sizeof(TAF_CALL_EVT_CCLPR_GET_CNF_STRU));

    pstXcallEntity = TAF_XCALL_GetCallEntityAddr(pstCallMsg->ucCallId);
    if ((VOS_TRUE == pstXcallEntity->ulUsed)
     && (MN_CALL_DIR_MT == pstXcallEntity->enCallDir))

    {
        stAppCnfMsg.enPI = pstXcallEntity->ucPi;
    }
    else
    {
        stAppCnfMsg.enPI = TAF_CALL_PRESENTATION_BUTT;
    }

    stAppCnfMsg.ucCallId        = pstCallMsg->ucCallId;
    stAppCnfMsg.ulRet           = TAF_ERR_NO_ERROR;

    /* �ϱ�TAF_CALL_EVT_CCLPR_SET_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CCLPR_SET_CNF,
                           pstCallMsg->usClientId,
                           sizeof(TAF_CALL_EVT_CCLPR_GET_CNF_STRU),
                          &stAppCnfMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReportEccNumList
 ��������  : ��AT�ϱ��������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : h00313353
    �޸�����   : Ecc List Report
*****************************************************************************/
VOS_VOID TAF_XCALL_ReportEccNumList(VOS_VOID)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();

    /* �ж������ϱ��Ƿ�� */
    if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                               TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                               TAF_SDC_RPT_CMD_XLEMA))
    {
        return;
    }

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("TAF_XCALL_ReportEccNumList: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0x00, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    pstEccNumInfo->usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    /* ��ȡ�������б� */
    TAF_XCALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /*  �ϱ�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF,pstEccNumInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SaveCustomEccNum
 ��������  : ��APP���ƵĽ��������뱣�浽ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : h00313353
    �޸�����   : Save Custom Ecc Num

*****************************************************************************/
VOS_VOID TAF_XCALL_SaveCustomEccNum(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT8                               ucIndex;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum            = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* ��ǰPLMN�����ڶ��ƽ��������룬�����ǰ�б� */
    if ((1 == pstCustomEccNumReq->ucIndex)
     && (1 == pstCustomEccNumReq->ucTotal)
     && (MN_CALL_INVALID_CATEGORY == pstCustomEccNumReq->ucCategory))
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0x00, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));
    }
    else
    {
        /* ���涨�ƺ��뵽ȫ�ֱ��� */
        ucIndex         = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;
        pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[ucIndex]);

        pstCustomEccNum->ucCategory             = pstCustomEccNumReq->ucCategory;
        pstCustomEccNum->ucValidSimPresent      = pstCustomEccNumReq->ucSimPresent;
        pstCustomEccNum->ulMcc                  = pstCustomEccNumReq->ulMcc;
        pstCustomEccNum->ucEccNumLen            = pstCustomEccNumReq->stEccNum.ucNumLen;
        pstCustomEccNum->ucAbnormalServiceFlg   = pstCustomEccNumReq->ucAbnormalServiceFlg;

        PS_MEM_CPY(pstCustomEccNum->aucEccNum,
                   pstCustomEccNumReq->stEccNum.aucBcdNum,
                   pstCustomEccNumReq->stEccNum.ucNumLen);

        (pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount)++;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppEccNumSetReq
 ��������  : ����ATģ�鷢����MN_CALL_APP_CUSTOM_ECC_NUM_REQ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��26��
    ��    ��   : h00313353
    �޸�����   : ���������ƺ�������
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccNumSetReq(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                              ulRst;
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stNvimCustomEccNumList;
    VOS_UINT8                               i;
    MN_CALL_CUSTOM_CFG_INFO_STRU           *pstCustomCfg            = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum         = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx = VOS_NULL_PTR;
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU    *pstCustomEccNumReq      = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU               *pstAppReq               = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pMsg;
    pstCustomEccNumReq      = (MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU *)&(pstAppReq->unParm.stEccNumReq);
    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    /* ���indexΪ1,��ն����б�, ��Ƕ��ƿ�ʼ */
    if (1 == pstCustomEccNumReq->ucIndex)
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0x00, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));

        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_TRUE;
    }

    /* ��ǰ���ڶ��ƹ��� */
    if (VOS_FALSE == pstCustomCallEmerNumCtx->ucCustomSetFlg)
    {
        /* ���������� */
        return;
    }

    /* ���涨�ƺ��뵽ȫ�ֱ��� */
    TAF_XCALL_SaveCustomEccNum(pstCustomEccNumReq);

    /* ��INDEX = TOTAL���߶��ƺ��������ﵽ�����Ϊ���ζ��ƽ��� */
    if ((pstCustomEccNumReq->ucIndex == pstCustomEccNumReq->ucTotal)
     || (TAF_SDC_MAX_CUSTOM_ECC_NUM == pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount))
    {
        PS_MEM_SET(&stNvimCustomEccNumList, 0, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));

        stNvimCustomEccNumList.ucEccNumCount = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;

        for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
        {
            pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i]);

            stNvimCustomEccNumList.astCustomEccNumList[i].ucCategory
                = pstCustomEccNum->ucCategory;
            stNvimCustomEccNumList.astCustomEccNumList[i].ulMcc
                = pstCustomEccNum->ulMcc;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
                = pstCustomEccNum->ucValidSimPresent;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg
                = pstCustomEccNum->ucAbnormalServiceFlg;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
                = pstCustomEccNum->ucEccNumLen;

            PS_MEM_CPY(stNvimCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomEccNum->aucEccNum,
                       pstCustomEccNum->ucEccNumLen);
        }

        /* ��Ƕ��ƽ��� */
        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_FALSE;

        /* ��ȫ�ֱ���������б�д��NV */
        ulRst = NV_Write(en_NV_Item_CUSTOM_ECC_NUM_LIST,(VOS_VOID *)&stNvimCustomEccNumList, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("TAF_XCALL_RcvAppEccNumSetReq:Write NVIM Error");
        }

        /* �������ϱ�����NV���ش� */
        if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
        {
            /* ��AT�ϱ���ǰ���еĽ��������� */
            TAF_XCALL_ReportEccNumList();
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppEncryptVoiceReq
 ��������  : �յ��û����ܻ�������Ϣ
 �������  : pstMsg -- �ܻ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEncryptVoiceReq(VOS_VOID *pstMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_ENC_VOICE_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pstMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppRemoteCtrlAnswerReq
 ��������  : �յ��û��·����Զ��ܻ�����Ӧ������
 �������  : pstMsg -- �ܻ�����Ӧ��������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppRemoteCtrlAnswerReq(VOS_VOID *pstMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_REMOTE_CTRL_ANSWER_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,
                           pstMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppEccSrvCapCfgReq
 ��������  : �յ��û��·�ECC����������������
 �������  : pstMsg -- ECC������������������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccSrvCapCfgReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU                  *pstAppSetEccSrvCap = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap       = VOS_NULL_PTR;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;

    enEccSrvCap                                             = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    pstAppSetEccSrvCap                                      = (TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ_STRU*)pstMsg;
    pstEccSrvCap                                            = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvCap)
    {
        enEccSrvCap = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    /*����������*/
    if (TAF_CALL_APP_ECC_SRV_CAP_DISABLE == pstAppSetEccSrvCap->enEccSrvCap)
    {
        pstEccSrvCap->ucEccSrvCap                           = VOS_FALSE;
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    }

    if (TAF_CALL_APP_ECC_SRV_CAP_ENABLE == pstAppSetEccSrvCap->enEccSrvCap)
    {
        pstEccSrvCap->ucEccSrvCap                           = VOS_TRUE;
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    if (TAF_CALL_APP_ECC_SRV_STATUS_CLOSE == pstAppSetEccSrvCap->enEccSrvStatus)
    {
        pstEccSrvCap->ucEccSrvStatus                        = VOS_FALSE;
    }

    if (TAF_CALL_APP_ECC_SRV_STATUS_OPEN == pstAppSetEccSrvCap->enEccSrvStatus)
    {
        pstEccSrvCap->ucEccSrvStatus                        = VOS_TRUE;
    }

    /*����NV*/
    TAF_XCALL_WriteVoiceEncryptCapCfgPara(enEccSrvCap, pstAppSetEccSrvCap->enEccSrvStatus);

    /*�ظ�APP���ý��*/
    TAF_XCALL_SndAppEccSrvCapCfgCnf(&pstAppSetEccSrvCap->stCtrl, TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_SUCC);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppEccSrvCapQryReq
 ��������  : �յ��û��·�ECC����������ѯ����
 �������  : pstMsg -- ECC����������ѯ������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppEccSrvCapQryReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU                  *pstAppGetEccSrvCap = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap       = VOS_NULL_PTR;
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap;
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus;

    enEccSrvCap                                             = TAF_CALL_APP_ECC_SRV_CAP_DISABLE;
    enEccSrvStatus                                          = TAF_CALL_APP_ECC_SRV_STATUS_CLOSE;
    pstAppGetEccSrvCap                                      = (TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ_STRU*)pstMsg;
    pstEccSrvCap                                            = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvCap)
    {
        enEccSrvCap                                         = TAF_CALL_APP_ECC_SRV_CAP_ENABLE;
    }

    if (VOS_TRUE == pstEccSrvCap->ucEccSrvStatus)
    {
        enEccSrvStatus                                      = TAF_CALL_APP_ECC_SRV_STATUS_OPEN;
    }

    TAF_XCALL_SndAppEccSrvCapQryCnf(&pstAppGetEccSrvCap->stCtrl,
                                    enEccSrvCap,
                                    enEccSrvStatus);

}
#endif

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppPrivacyModeSetReq
 ��������  : �����û��·���privacy mode��������
 �������  : pstMsg -- privacy mode��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppPrivacyModeSetReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU                 *pstPrivacyModeReq = VOS_NULL_PTR;
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8                       enPrivacyMode;

    pstPrivacyModeReq = (TAF_CALL_APP_PRIVACY_MODE_SET_REQ_STRU *)pstMsg;

    enPrivacyMode     = (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)pstPrivacyModeReq->enPrivacyMode;

    TAF_XCALL_SendPrivacyModeSetReq(enPrivacyMode,
                                    pstPrivacyModeReq->stCtrl.ulModuleId,
                                    pstPrivacyModeReq->stCtrl.usClientId,
                                    pstPrivacyModeReq->stCtrl.ucOpId);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvAppPrivacyModeQryReq
 ��������  : �����û��·���privacy mode��ѯ����
 �������  : pstMsg -- privacy mode��ѯ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvAppPrivacyModeQryReq(VOS_VOID *pstMsg)
{
    TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU                 *pstPrivacyModeQryReq = VOS_NULL_PTR;

    pstPrivacyModeQryReq = (TAF_CALL_APP_PRIVACY_MODE_QRY_REQ_STRU *)pstMsg;

    TAF_XCALL_SendPrivacyModeQryReq(pstPrivacyModeQryReq->stCtrl.ulModuleId,
                                    pstPrivacyModeQryReq->stCtrl.usClientId,
                                    pstPrivacyModeQryReq->stCtrl.ucOpId);
}
/*lint -restore*/

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





