/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcXcc.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF X CALL��������XCC����Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "xcc_xcall_pif.h"
#include "VcCallInterface.h"

#include "TafXCallProcXcc.h"
#include "TafXCallCtx.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndMma.h"
#include "TafXCallSndVc.h"
#include "TafXCallProcApp.h"
#include "TafXCallTimerMgmt.h"
#include "TafSdcCtx.h"

#include "TafSdcLib.h"

#include "TafMmaSndOm.h"
#include "TafLog.h"

#include "TafXCallProcEccSrv.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallOrigCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_ORIG_CALL_CNF��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallOrigCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_ORIG_CALL_CNF_STRU       *pstOrigCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulRemainTimeLen;
    TAF_XCALL_CALL_ENTITY_STRU         *pstOrigCallEntity = VOS_NULL_PTR;   /* ԭ����ʵ��ָ�� */
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
    TAF_XCALL_CONFIG_STRU              *pstXcallConfig = VOS_NULL_PTR;

    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();
    pstXcallConfig  = TAF_XCALL_GetConfigInfo();

    pstOrigCnf = (XCC_XCALL_ORIG_CALL_CNF_STRU *)pMsg;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstOrigCnf->ucCallId);
    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(pstOrigCnf->ucCallId);
    usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    enCallType          = TAF_XCALL_GetCallType(pstOrigCnf->ucCallId);

    pstCallEntity->sRssi = pstOrigCnf->sRssi;

    /* ����ԭ��ֵ */
    TAF_XCALL_UpdateCcCause(pstOrigCnf->ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));

    if (TAF_XCC_CAUSE_SUCCESS != pstOrigCnf->enCause)
    {
        /* ���ز�ԭ��ֵ�����������ز���ʱ��ʣ��ʱ�����ڻ�����ز������ʱ��ʱ��,�����ز�,�����ز� */
        ulRemainTimeLen = 0;
        TAF_XCALL_GetRemainTimerLen(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId, &ulRemainTimeLen);

        if (ulRemainTimeLen >= TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN)
        {
            TAF_XCALL_VoiceOrigRedialCount(pstOrigCnf->ucCallId, pstOrigCnf->enFailLayer);

            /* ������������������������֪ͨXSDģ�� */
            if (MN_CALL_TYPE_EMERGENCY == enCallType)
            {
                if (TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT == pstOrigCnf->enCause)
                {
                    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                    return;
                }
                else if ( (TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED == pstOrigCnf->enCause)
                       || (TAF_XCC_CAUSE_L2_ACK_TIME_OUT == pstOrigCnf->enCause)
                       || (TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE == pstOrigCnf->enCause) )
                {
                    /* �޸�ԭ���еĺ���ʵ����Type��Called Num��Ϣ */
                    if (TAF_XCC_CALLID_NULL != pstOrigCnf->ucOrigCallId)
                    {
                        /* ����ǰ�ĺ���ʵ����Ϣ���Ƶ�ԭ�к���ʵ���� */
                        pstOrigCallEntity               = TAF_XCALL_GetCallEntityAddr(pstOrigCnf->ucOrigCallId);

                        enCallType                      = TAF_XCALL_GetCallType(pstOrigCnf->ucOrigCallId);

                        pstOrigCallEntity->enCallType   = MN_CALL_TYPE_EMERGENCY;

                        PS_MEM_CPY(&(pstOrigCallEntity->stCalledNumber), &(pstCallEntity->stCalledNumber), sizeof(MN_CALL_CALLED_NUM_STRU));

                        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
                        /***************************************************************************
                         * ��������˵��������Ӧ�ò�֧���ܻ����ܣ����ڵ����ܻ�Э�鲢û����ȷ˵������
                         * modem��Ȼ��֧�ִ���
                         **************************************************************************/
                        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                                               pMsg,
                                               VOS_NULL_PTR);
#endif


                        TAF_XCALL_SndCallReleaseInd(pstOrigCnf->ucCallId);

                        /* ����ԭ�к��е�CallEnd */
                        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

                        /* �����µĽ�������Call Success */
                        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(MN_CALL_TYPE_EMERGENCY));

                        if (VOS_TRUE == pstXcallConfig->ulCallBackEnableFlg)
                        {
                            /* �ñ���������δ���������AT���� */
                            pstSdc1xSysInfo->ucIsEmcCallExistFlg = VOS_TRUE;
                        }

                        /* �ͷŵ�ǰ�ĺ���ʵ�� */
                        TAF_XCALL_FreeCallEntity(pstOrigCnf->ucCallId);

                        return;
                    }
                }
                else
                {
                    /* �ز�ǰ�����ز���ʱ�� */
                    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                    TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF, usClientId,TAF_XCALL_BuildMmaCallType(enCallType), TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));

                    return;
                }


            }
            else if (VOS_TRUE == TAF_XCALL_IsNeedSilentRedial(pstOrigCnf->enCause))
            {
                /* ֻ����Ҫ����������ԭ��ֵ���Ż�֪ͨXSDģ�飬����ֻ��������ʱ��������֪ͨMMAģ�� */
                TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                if (VOS_TRUE == TAF_XCALL_IsNeedRedialSystemAcquire(pstOrigCnf->enCause, pstCallEntity->sRssi))
                {
                    TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF, usClientId,TAF_XCALL_BuildMmaCallType(enCallType), TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));
                }

                return;
            }
            else
            {

            }

        }

        /* ֹͣ�ز���ʱ��,�����ʱ��δ������call id��һ�������� */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        /*******************************************************************************************
         * �����ǰ���в������ز�����֪ͨ�ܻ�״̬���������ͷ�
         ******************************************************************************************/
        TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               pMsg,
                               VOS_NULL_PTR);
#endif


        /* �ϱ�����ʧ�� */
        TAF_XCALL_SndCallReleaseInd(pstOrigCnf->ucCallId);

        /* ��MMA����TAF_MMA_1X_CALL_END_NTF��Ϣ */
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

        /* �ͷź���ʵ�� */
        TAF_XCALL_FreeCallEntity(pstOrigCnf->ucCallId);

        return;
    }

    /* ֹͣ�ز���ʱ��,�����ʱ��δ������call id��һ�������� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

    /* ���º���״̬��1Xģʽ�£�Э��涨���н������״̬Ϊactive */
    TAF_XCALL_UpdateCallState(pstOrigCnf->ucCallId, MN_CALL_S_ACTIVE);

    /* �ϱ����гɹ� */
    TAF_XCALL_SndCallConnectInd(pstOrigCnf->ucCallId);

    /* ��MMA����TAF_MMA_1X_CALL_SUCCESS_NTF��Ϣ */
    TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

    if ( (MN_CALL_TYPE_EMERGENCY == enCallType)
      && (VOS_TRUE == pstXcallConfig->ulCallBackEnableFlg) )
    {
        /* �ñ���������δ���������AT���� */
        pstSdc1xSysInfo->ucIsEmcCallExistFlg = VOS_TRUE;
    }



    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallHangUpCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_HANGUP_CALL_CNF��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallHangUpCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_HANGUP_CALL_CNF_STRU                         *pstHangUpCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;

    pstHangUpCnf = (XCC_XCALL_HANGUP_CALL_CNF_STRU *)pMsg;

    enEvt        = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp   = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstHangUpCnf->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstHangUpCnf->ucCallId);

    /* �ж��Ƿ�Ϊidle̬ */
    if (MN_CALL_S_IDLE == enCallState)
    {
        return;
    }

    /* ���浱ǰcall id��module id������release all�ϱ� */
    ulModuleId = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->ucOpId;

    if (MN_CALL_DIR_MO == TAF_XCALL_GetCallDir(pstHangUpCnf->ucCallId))
    {
        enCallType  = TAF_XCALL_GetCallType(pstHangUpCnf->ucCallId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
    }

    /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
    TAF_XCALL_SndCallReleaseInd(pstHangUpCnf->ucCallId);

    TAF_XCALL_GetSsKeyEvent(pstHangUpCnf->ucCallId, &enEvt, &enSubseqOp);

    if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
    {
        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId, pstHangUpCnf->ucCallId, MN_CALL_SS_RES_SUCCESS);

        TAF_XCALL_DeRegSsKeyEvent(pstHangUpCnf->ucCallId, TAF_XCALL_SS_PROG_EVT_REL);
    }

    /* ��ն�Ӧ��ʵ����Ϣ */
    TAF_XCALL_FreeCallEntity(pstHangUpCnf->ucCallId);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    /* ���û�к���ʵ�� */
    if (0 == ulNumOfCalls)
    {
        /* ��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallDiscInd
 ��������  : �յ�XCC��ID_XCC_XCALL_CALL_DISC_IND��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��1��3��
    ��    ��   : y00245242
    �޸�����   : NDSS ORIG���ܿ���
  4.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
  5.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : iteration 16����
  6.��    ��   : 2015��8��24��
    ��    ��   : l00324781
    �޸�����   : DTS2015081708770�޸�
  7.��    ��   : 2015��10��24��
    ��    ��   : y00245242
    �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallDiscInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CALL_DISC_IND_STRU                           *pstCallDiscInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    VOS_UINT8                                               ucCallId;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    pstCallDiscInd = (XCC_XCALL_CALL_DISC_IND_STRU *)pMsg;

    enEvt          = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp     = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallDiscInd->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        /* �ݴ��ж�: XCC���յ�XCALL��incoming rsp֮ǰ����յ�AS��terminal ind��XCC��֪��call id */
        ulRslt = TAF_XCALL_GetCallIdFromConnectId(pstCallDiscInd->ucConnectId, &ucCallId);

        if (VOS_TRUE != ulRslt)
        {
            return;
        }
    }
    else
    {
        ucCallId = pstCallDiscInd->ucCallId;
    }

    enCallState = TAF_XCALL_GetCallState(ucCallId);

    /* �ж��Ƿ�Ϊ��idle̬ */
    if (MN_CALL_S_IDLE == enCallState)
    {
        return;
    }

    /* ���浱ǰcall id��client info */
    ulModuleId = TAF_XCALL_GetClientInfo(ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(ucCallId)->ucOpId;

    /* ����ԭ��ֵ */
    TAF_XCALL_UpdateCcCause(ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstCallDiscInd->enCause));

    /* ���¹ҶϷ��� */
    TAF_XCALL_UpdateDiscCallDir(ucCallId, VOS_FALSE);

    enCallType = TAF_XCALL_GetCallType(ucCallId);

    if ((MN_CALL_DIR_MO         == TAF_XCALL_GetCallDir(ucCallId))
     || (MN_CALL_TYPE_EMERGENCY == enCallType))
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
    }

    /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
    TAF_XCALL_SndCallReleaseInd(ucCallId);

    TAF_XCALL_GetSsKeyEvent(ucCallId, &enEvt, &enSubseqOp);

    /* ������ڹҶϹ����У�����Ҷϣ���APP�ظ��Ҷϳɹ� */
    if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
    {
        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId, ucCallId, MN_CALL_SS_RES_SUCCESS);

        TAF_XCALL_DeRegSsKeyEvent(ucCallId, TAF_XCALL_SS_PROG_EVT_REL);
    }

    /* ������ڽ��������У�����Ҷϣ���APP�ظ�����ʧ�� */
    if (TAF_XCALL_SS_PROG_EVT_ANS == enEvt)
    {
        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                ucCallId, MN_CALL_SS_RES_FAIL);

        TAF_XCALL_DeRegSsKeyEvent(ucCallId, TAF_XCALL_SS_PROG_EVT_ANS);
    }

    /* ���dtmf���� */
    TAF_XCALL_CleanDtmfBuff(ucCallId);

    TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, ucCallId);


    if (TAF_XCC_CAUSE_NDSS_REDIAL_IND == pstCallDiscInd->enCause)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        /* �����ǰ�����������ܻ����У���֧��NDSS OFF�ڽ���̬�µĺ����ز����� */
        if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE == TAF_XCALL_GetVoiceEncryptNegotiateState())
#endif
        {
            pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

            /* ����Ǩ����״̬��dialing״̬ */
            pstCallEntity->enCallState = MN_CALL_S_DIALING;

            /* �ϱ����з����¼� */
            TAF_XCALL_SndCallOrigInd(ucCallId);

            return;
        }
    }

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_DISC_IND,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif

    /* ��ն�Ӧ��ʵ����Ϣ */
    TAF_XCALL_FreeCallEntity(ucCallId);

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    /* ���û�к���ʵ�壬��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
    if (0 == ulNumOfCalls)
    {
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallIncomingInd
 ��������  : �յ�XCC��ID_XCC_XCALL_INCOMING_CALL_IND��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallIncomingInd(VOS_VOID *pMsg)
{
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd = VOS_NULL_PTR;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRslt;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;

    pstIncomingCallInd = (XCC_XCALL_INCOMING_CALL_IND_STRU *)pMsg;

    /* �ж�SO����Ч�� */
    if (VOS_TRUE != TAF_XCALL_IsAvailVoiceCallSo(TAF_XCALL_ConvertXccSoToXcallSo(pstIncomingCallInd->enSo)))
    {
        TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    /* ��ǰ����һ·dialing״̬�Ľ������У�XCC�Ὣ��MOת��flash��Ϣ����ȥ��XCALL�����ж�
        ��ǰ����һ·dialing״̬����ͨ���У�XCC�Ὣ��MO�ܵ���XCALL�����ж�
        ��ǰ����һ·active״̬�ĺ��У�������µ�����callid��ͬ���ϱ�incoming������״̬��Ϊincoming״̬��������Ϊ�쳣 */
    if (0 != ulNumOfCalls)
    {
        if (aucCallIds[0] == pstIncomingCallInd->ucCallId)
        {
            /* ��¼����callҵ���û�����Ϣ(AT/STK) */
            TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                       WUEPS_PID_AT,
                                       MN_CLIENT_ID_BROADCAST,
                                       0);
            /* ����SO */
            TAF_XCALL_UpdateSo(aucCallIds[0], TAF_XCALL_ConvertXccSoToXcallSo(pstIncomingCallInd->enSo));

            /* ����By pass Flag */
            TAF_XCALL_UpdateAlertAnsByPassFlg(aucCallIds[0], pstIncomingCallInd->ucIsAlertAnsByPass);

            /* ����Connect Reference */
            TAF_XCALL_UpdateConnectRef(aucCallIds[0], pstIncomingCallInd->ucConRef);

            /* ����Connect Id */
            TAF_XCALL_UpdateConnectId(aucCallIds[0], pstIncomingCallInd->ucConRef);

            /* ���º���״̬ */
            TAF_XCALL_UpdateCallState(aucCallIds[0], MN_CALL_S_INCOMING);

            /* ���º������� */
            TAF_XCALL_UpdateCallType(aucCallIds[0], MN_CALL_TYPE_VOICE);

            /* ���·������Dir */
            TAF_XCALL_UpdateCallDir(aucCallIds[0], MN_CALL_DIR_MT);

            /* ����������� */
            TAF_XCALL_UpdateCallingNum(aucCallIds[0], &(pstIncomingCallInd->stCallingPartyNum));

            /* ����TAF��privacy mode */
            TAF_XCALL_UpdatePrivacyMode(aucCallIds[0], (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstIncomingCallInd->enPrivacyMode);

            /* ��APP�ϱ�MN_CALL_EVT_INCOMING�¼� */
            TAF_XCALL_SndCallIncomingInd(aucCallIds[0]);

            /* ��APP�ϱ�privacy mode  */
            TAF_XCALL_ProcPrivacyModeInd(aucCallIds[0],(TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstIncomingCallInd->enPrivacyModeSetting);
        }
        else
        {
            TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);
        }

        return;
    }

    /* ���������������ֹ���в�ֹͣ����ز���ʱ��,Ȼ����䱻�е�call id */
    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));
    TAF_XCALL_GetCallsByState(MN_CALL_S_DIALING, &ulNumOfCalls, aucCallIds);

    if (0 != ulNumOfCalls)
    {
        pstCallEntity       = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);
        usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);

        /* ������ڽ������ز����ܾ��ñ���*/
        if (MN_CALL_TYPE_EMERGENCY == TAF_XCALL_GetCallType(aucCallIds[0]))
        {
            TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);

            return;
        }

        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[0]))
        {
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD,   aucCallIds[0]);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[0]);

            enCallType          = TAF_XCALL_GetCallType(aucCallIds[0]);

            TAF_XCALL_UpdateCcCause(aucCallIds[0], TAF_CS_CAUSE_XCALL_UNKNOWN);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
            TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                                   TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                                   pMsg,
                                   VOS_NULL_PTR);
#endif

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
            TAF_XCALL_SndCallReleaseInd(aucCallIds[0]);

            /* ��ն�Ӧ��ʵ����Ϣ */
            TAF_XCALL_FreeCallEntity(aucCallIds[0]);

        }
    }

    /* ����һ������ʵ�� */
    ucCallId = 0;

    ulRslt   = TAF_XCALL_AllocCallId(&ucCallId);

    /* ʵ�����ʧ�ܣ��ظ�rspʧ�� */
    if (VOS_TRUE != ulRslt)
    {
        TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);

        return;
    }

    TAF_XCALL_CreateMtCallEntity(ucCallId, WUEPS_PID_AT, pstIncomingCallInd);

    /* ��XCC�ظ�ID_XCALL_XCC_INCOMING_CALL_RSP��Ϣ */
    TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_SUCC, ucCallId, pstIncomingCallInd->ucConnectId);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INCOMING_CALL_IND,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif

    /* ��APP�ϱ�MN_CALL_EVT_INCOMING�¼� */
    TAF_XCALL_SndCallIncomingInd(ucCallId);

    /* ��APP�ϱ�privacy mode  */
    TAF_XCALL_ProcPrivacyModeInd(ucCallId,(TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstIncomingCallInd->enPrivacyModeSetting);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallAnswerCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_ANSWER_CALL_CNF��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallAnswerCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_ANSWER_CALL_CNF_STRU     *pstCallAnsCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MN_CALL_STATE_ENUM_U8               enCallState;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                          ulModuleId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    pstCallAnsCnf = (XCC_XCALL_ANSWER_CALL_CNF_STRU *)pMsg;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallAnsCnf->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    /* �ж�SO����Ч�� */
    if (TAF_XCALL_GetSo(pstCallAnsCnf->ucCallId) != TAF_XCALL_ConvertXccSoToXcallSo(pstCallAnsCnf->enSo))
    {
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstCallAnsCnf->ucCallId);

    /* �ж��Ƿ�Ϊincoming״̬ */
    if (MN_CALL_S_INCOMING != enCallState)
    {
        return;
    }

    /* ���浱ǰcall id��client info */
    ulModuleId = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->ucOpId;

    TAF_XCALL_DeRegSsKeyEvent(pstCallAnsCnf->ucCallId, TAF_XCALL_SS_PROG_EVT_ANS);

    /* ����ԭ��ֵ */
    TAF_XCALL_UpdateCcCause(pstCallAnsCnf->ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstCallAnsCnf->enCause));

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_ANSWER_CALL_CNF,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif

    if (TAF_XCC_CAUSE_SUCCESS == pstCallAnsCnf->enCause)
    {
        /* ���º���״̬ */
        TAF_XCALL_UpdateCallState(pstCallAnsCnf->ucCallId, MN_CALL_S_ACTIVE);

        /* ����connect ref */
        TAF_XCALL_UpdateConnectRef(pstCallAnsCnf->ucCallId, pstCallAnsCnf->ucConRef);

        /* ����SO */
        TAF_XCALL_UpdateSo(pstCallAnsCnf->ucCallId, TAF_XCALL_ConvertXccSoToXcallSo(pstCallAnsCnf->enSo));

        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                pstCallAnsCnf->ucCallId, MN_CALL_SS_RES_SUCCESS);

        /* ��APP�ϱ�MN_CALL_EVT_CONNECT�¼� */
        TAF_XCALL_SndCallConnectInd(pstCallAnsCnf->ucCallId);

    }
    else
    {
        /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
        TAF_XCALL_SndCallReleaseInd(pstCallAnsCnf->ucCallId);

        /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                pstCallAnsCnf->ucCallId, MN_CALL_SS_RES_FAIL);

        /* ��ն�Ӧ��ʵ����Ϣ */
        TAF_XCALL_FreeCallEntity(pstCallAnsCnf->ucCallId);

        ulNumOfCalls = 0;

        PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

        TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

        /* ���û�к���ʵ�� */
        if (0 == ulNumOfCalls)
        {
            /* ��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
            TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCallConnectInd
 ��������  : �յ�XCC��ID_XCC_XCALL_CALL_CONNECT_IND��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCallConnectInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CALL_CONNECT_IND_STRU    *pstCallConnectInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MN_CALL_STATE_ENUM_U8               enCallState;
    VOS_UINT8                           ucIsAlertAnsByPass;

    pstCallConnectInd = (XCC_XCALL_CALL_CONNECT_IND_STRU *)pMsg;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallConnectInd->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    /* �ж�SO����Ч�� */
    if (TAF_XCALL_GetSo(pstCallConnectInd->ucCallId) != TAF_XCALL_ConvertXccSoToXcallSo(pstCallConnectInd->enSo))
    {
        return;
    }

    enCallState        = TAF_XCALL_GetCallState(pstCallConnectInd->ucCallId);

    ucIsAlertAnsByPass = TAF_XCALL_GetAlertAnsByPassFlg(pstCallConnectInd->ucCallId);

    /* ֻ��bypassΪVOS_TRUE����connect ind: ��Ӧ��״̬Ϊincoming����bypassΪVOS_TRUE */
    if ((MN_CALL_S_INCOMING != enCallState)
     || (VOS_FALSE == ucIsAlertAnsByPass))
    {
        return;
    }

    /* ���º���״̬ */
    TAF_XCALL_UpdateCallState(pstCallConnectInd->ucCallId, MN_CALL_S_ACTIVE);

    /* ��APP�ϱ�MN_CALL_EVT_CONNECT�¼� */
    TAF_XCALL_SndCallConnectInd(pstCallConnectInd->ucCallId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccSendFlashCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_SEND_FLASH_CNF��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��08��11��
    ��    ��   : y00307564
    �޸�����   : DTS2015080608576�޸�
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_SEND_FLASH_CNF_STRU      *pstSndFlashCnf  = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_XCALL_CONFIG_STRU              *pstXcallConfig  = VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;

    pstSndFlashCnf = (XCC_XCALL_SEND_FLASH_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndFlashCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stFlashInfo.stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stFlashInfo.stClientInfo.ucOpId;

    /* ��Ӧ�ûظ�TAF_CALL_EVT_SEND_FLASH_RSLT��Ϣ */
    if (TAF_XCC_CAUSE_SUCCESS == pstSndFlashCnf->enCause)
    {
        TAF_XCALL_SndFlashRslt(usClientId, ucOpId, VOS_OK);

        if (VOS_TRUE == pstCallEntity->stFlashInfo.ucIsEmcCall)
        {
            TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_EMERGENCY_VOICE_CALL);

            pstCallEntity->enCallType   = MN_CALL_TYPE_EMERGENCY;

            PS_MEM_CPY(&(pstCallEntity->stCalledNumber),
                       &(pstCallEntity->stFlashInfo.stDialNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            pstXcallConfig  = TAF_XCALL_GetConfigInfo();
            pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

            if (VOS_TRUE == pstXcallConfig->ulCallBackEnableFlg)
            {
                pstSdc1xSysInfo->ucIsEmcCallExistFlg = VOS_TRUE;
            }
        }
    }
    else
    {
        TAF_XCALL_SndFlashRslt(usClientId, ucOpId, VOS_ERR);

        if (VOS_TRUE == pstCallEntity->stFlashInfo.ucIsEmcCall)
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_EMERGENCY_VOICE_CALL);
        }
    }

    /* ���ʵ�������Ϣ */
    PS_MEM_SET(&(pstCallEntity->stFlashInfo), 0x00, sizeof(TAF_XCALL_FLASH_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccInfoRecInd
 ��������  : �յ�XCC��ID_XCC_XCALL_INFO_REC_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg)
{
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd = VOS_NULL_PTR;

    pstInfoRecInd = (XCC_XCALL_INFO_REC_IND_STRU *)pMsg;



    /* ����display info */
    TAF_XCALL_SndDisplayInfoInd(pstInfoRecInd);

    /* ����ext display info */
    TAF_XCALL_SndExtDisplayInfoInd(pstInfoRecInd);

    /* ����connected num */
    TAF_XCALL_SndConnNumInfoInd(pstInfoRecInd);

    /* ����called num */
    TAF_XCALL_SndCalledNumInfoInd(pstInfoRecInd);

    /* ����redirection num */
    TAF_XCALL_SndRedirNumInfoInd(pstInfoRecInd);

    /* ����line ctrl */
    TAF_XCALL_SndLineCtrlInfoInd(pstInfoRecInd);

    /* ����calling num or signal��or CCWA */
    TAF_XCALL_SndCallingNumSignalInfoInd(pstInfoRecInd);

    if (VOS_TRUE == pstInfoRecInd->bitOpCallingNumInfo)
    {
        TAF_XCALL_UpdateCallingNum(pstInfoRecInd->ucCallId, &(pstInfoRecInd->stCallingNumInfo));
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCodecOpenInd
 ��������  : �յ�XCC��ID_XCC_XCALL_CODEC_OPEN_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCodecOpenInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;
    XCC_XCALL_CODEC_OPEN_IND_STRU      *pstCodecOpen = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));
    pstCodecOpen = (XCC_XCALL_CODEC_OPEN_IND_STRU *)pMsg;

    stChannelInfo.bChannelEnable            = VOS_TRUE;
    stChannelInfo.stChannelParam.enMode     = CALL_VC_MODE_CDMA;
    stChannelInfo.stChannelParam.enCallType = CALL_VC_CALL_TYPE_NORMAL_CALL;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstCodecOpen->enSo,
                                        &stChannelInfo.stChannelParam.enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��VC����CALL_VC_CHANNEL_OPEN��Ϣ */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_OPEN,
                                  &stChannelInfo);


    /* ����SO */
    for (i = 1; i <= TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == TAF_XCALL_GetCallEntityAddr(i)->ulUsed)
        {
            TAF_XCALL_UpdateSo(i, (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCodecOpen->enSo);
        }
    }

    /* TO DO:��Ҫȷ���Ƿ���Ҫ��AT�ϱ�channel info */
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCodecCloseInd
 ��������  : �յ�XCC��ID_XCC_XCALL_CODEC_CLOSE_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCodecCloseInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));

    stChannelInfo.bChannelEnable        = VOS_FALSE;
    stChannelInfo.stChannelParam.enMode = CALL_VC_MODE_CDMA;

    /* ��VC����CALL_VC_CHANNEL_CLOSE��Ϣ */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_CLOSE,
                                  &stChannelInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccCodecChangedInd
 ��������  : �յ�XCC��ID_XCC_XCALL_CODEC_CHANGED_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccCodecChangedInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;
    XCC_XCALL_CODEC_CHANGED_IND_STRU   *pstCodecChange = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));
    pstCodecChange = (XCC_XCALL_CODEC_CHANGED_IND_STRU *)pMsg;

    stChannelInfo.bChannelEnable            = VOS_TRUE;
    stChannelInfo.stChannelParam.enMode     = CALL_VC_MODE_CDMA;
    stChannelInfo.stChannelParam.enCallType = CALL_VC_CALL_TYPE_NORMAL_CALL;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstCodecChange->enSo,
                                        &stChannelInfo.stChannelParam.enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��VC����CALL_VC_CHANNEL_PARA_CHANGE��Ϣ */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_PARA_CHANGE,
                                  &stChannelInfo);

    /* ����SO */
    for (i = 1; i <= TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == TAF_XCALL_GetCallEntityAddr(i)->ulUsed)
        {
            TAF_XCALL_UpdateSo(i, (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCodecChange->enSo);
        }
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccSoCtrlMsgInd
 ��������  : �յ�XCC��ID_XCC_XCALL_SO_CTRL_MSG_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccSoCtrlMsgInd(VOS_VOID *pMsg)
{
    XCC_XCALL_SO_CTRL_MSG_IND_STRU     *pstSoCtrlMsg = VOS_NULL_PTR;
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;
    VOS_UINT32                          ulRslt;

    pstSoCtrlMsg = (XCC_XCALL_SO_CTRL_MSG_IND_STRU *)pMsg;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstSoCtrlMsg->enSo,
                                        &enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��VC����VC_CALL_SO_CTRL_MSG_IND��Ϣ */
    TAF_XCALL_SndVcSoCtrlMsgInd(enCodecType,
                                pstSoCtrlMsg->ucRateReduc,
                                pstSoCtrlMsg->ucMobileToMobile,
                                pstSoCtrlMsg->ucInitCodec);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccSoCtrlOrderInd
 ��������  : �յ�XCC��ID_XCC_XCALL_SO_CTRL_ORDER_IND��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccSoCtrlOrderInd(VOS_VOID *pMsg)
{
    XCC_XCALL_SO_CTRL_ORDER_IND_STRU   *pstSoCtrlOrder = VOS_NULL_PTR;
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;
    VOS_UINT32                          ulRslt;

    pstSoCtrlOrder = (XCC_XCALL_SO_CTRL_ORDER_IND_STRU *)pMsg;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstSoCtrlOrder->enSo,
                                        &enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* ��VC����VC_CALL_SO_CTRL_ORDER_IND��Ϣ */
    TAF_XCALL_SndVcSoCtrlOrderInd(enCodecType, pstSoCtrlOrder->ucORDQ);

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_MapSoToCodecType
 ��������  : ��SO����ӳ��ΪCODEC����
 �������  : TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
             CALL_VC_CODEC_TYPE_ENUM_U8         *penCodecType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XCALL_MapSoToCodecType(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo,
    CALL_VC_CODEC_TYPE_ENUM_U8         *penCodecType
)
{
    if (TAF_CDMA_SO_3_EVRC == enSo)
    {
        *penCodecType = CALL_VC_CODEC_TYPE_EVRC;
    }
    else if (TAF_CDMA_SO_68_EVRC_B == enSo)
    {
        *penCodecType = CALL_VC_CODEC_TYPE_EVRCB;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ConvertXccSoToXcallSo
 ��������  : ��XCC�ϱ���SOת��XCALL��SO
 �������  : TAF_CDMA_SO_TYPE_ENUM_UINT16        enXccSo
 �������  : ��
 �� �� ֵ  : TAF_XCALL_SO_TYPE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_ConvertXccSoToXcallSo(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enXccSo
)
{
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enXcallSo;

    if (TAF_CDMA_SO_3_EVRC == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_3_EVRC;
    }
    else if (TAF_CDMA_SO_68_EVRC_B == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_68_EVRC_B;
    }
    else if (TAF_CDMA_SO_73_EVRC_NW == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_73_EVRC_NW;
    }
    else
    {
        enXcallSo = TAF_XCALL_SO_BUTT;
    }

    return enXcallSo;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccSendBurstDTMFCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_BURST_DTMF_CNF��Ϣ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �޸�, ����TAF_XCC_CAUSE_L2_ACK_FAIL��
                  TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE�޸�Ϊ�������
                CONT DTMF��BURST DTMF�����һ
  3.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : DTS2015081708770 �޸�
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccSendBurstDTMFCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_BURST_DTMF_CNF_STRU      *pstSndBurstDTMFCnf = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucRslt;
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;

    pstSndBurstDTMFCnf = (XCC_XCALL_BURST_DTMF_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndBurstDTMFCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    /* ����ȴ�XCC�ظ��ı�ʶ */
    enWaitForXCCDTMFCnfFlag = TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstSndBurstDTMFCnf->ucCallId);
    if (TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF != enWaitForXCCDTMFCnfFlag)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                         "TAF_XCALL_RcvXccSendBurstDTMFCnf():Current WaitForXCCDTMFCnfFlag is error",
                         enWaitForXCCDTMFCnfFlag);
        return;
    }

    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndBurstDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);

    /* DTMF���洦�� �������ʱ����ʱ�����ʧ�ܣ�����DTMF���洦������Ǻ����ͷŻ�״̬�쳣�����建��  */
    switch (pstSndBurstDTMFCnf->enCause)
    {
        case TAF_XCC_CAUSE_SUCCESS:
            ucRslt = VOS_OK;
            TAF_XCALL_ProcDtmfBuffer(pstSndBurstDTMFCnf->ucCallId);
            break;

        /* Move TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE to clean buffer
            add new cause TAF_XCC_CAUSE_L2_ACK_FAIL
        */
        case TAF_XCC_CAUSE_ENCODE_FAIL:
        case TAF_XCC_CAUSE_L2_ACK_TIME_OUT:
        case TAF_XCC_CAUSE_L2_ACK_FAIL:

            ucRslt = VOS_ERR;
            TAF_XCALL_ProcDtmfBuffer(pstSndBurstDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE:
        case TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE:
        case TAF_XCC_CAUSE_ABNORMAL_STATE:

            ucRslt = VOS_ERR;
            TAF_XCALL_CleanDtmfBuff(pstSndBurstDTMFCnf->ucCallId);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstSndBurstDTMFCnf->ucCallId);
            break;

        default:
            ucRslt = VOS_ERR;
            break;
    }

    TAF_XCALL_SndBurstDTMFRslt(usClientId, ucOpId, ucRslt);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsNeedSilentRedial
 ��������  : ����ʧ��ԭ��ֵ�ж��Ƿ���Ҫ�����ز�
 �������  : enCause-------------ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��26��
    ��    ��   : w00242748
    �޸�����   : DTS2015012804417:����RSSI��ֵ�����ز�
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsNeedSilentRedial(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    /* ���ж�ԭ��ֵ�Ƿ������ز����� */
    switch (enCause)
    {
        case TAF_XCC_CAUSE_NO_SERVICE:
        case TAF_XCC_CAUSE_MAX_ACCESS_PROBES:
        case TAF_XCC_CAUSE_REORDER:
        case TAF_XCC_CAUSE_ACCESS_DENYIED:
        case TAF_XCC_CAUSE_ACCT_BLOCK:
        case TAF_XCC_CAUSE_NDSS:
        case TAF_XCC_CAUSE_REDIRECTION:
        case TAF_XCC_CAUSE_ACCESS_IN_PROGRESS:
        case TAF_XCC_CAUSE_ACCESS_FAIL:
        case TAF_XCC_CAUSE_ABORT:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH:
        case TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT:
        case TAF_XCC_CAUSE_CCS_NOT_SUPPORT:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL:
        case TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH:
        case TAF_XCC_CAUSE_MS_NORMAL_RELEASE:
        case TAF_XCC_CAUSE_NW_NORMAL_RELEASE:
        case TAF_XCC_CAUSE_SO_REJ:
            return VOS_TRUE;

        default:
        /* TAF_XCC_CAUSE_INTERCEPT����Ҫ�����ز� */
            return VOS_FALSE;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsNeedRedialSystemAcquire
 ��������  : ����ʧ��ԭ��ֵ�ж��Ƿ���Ҫ�����ز�
 �������  : enCause-------------ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsNeedRedialSystemAcquire(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_INT32                           lRssi
)
{
    /* ���ж�ԭ��ֵ�Ƿ������ز������������ز��������ſ�����Ҫ�������� */
    if (VOS_FALSE == TAF_XCALL_IsNeedSilentRedial(enCause))
    {
        return VOS_FALSE;
    }


    /* ����CDG 143������ԭ��ֵ�����ز�ʱ���� */
    switch (enCause)
    {
        case TAF_XCC_CAUSE_REORDER:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_ACH:
        case TAF_XCC_CAUSE_SIGNAL_FADE_IN_TCH:
        case TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT:
        /* RSSIֵ���С�ڵ���-100�Ļ�����Ҫ��������������-100�Ļ������ô������� */
            if (lRssi > -100)
            {
                return VOS_FALSE;
            }
        case TAF_XCC_CAUSE_MAX_ACCESS_PROBES:
        case TAF_XCC_CAUSE_ACCESS_DENYIED:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_VoiceOrigRedialCount
 ��������  : ���������ز�����
 �������  : VOS_UINT8                           ucPdpId,
             TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_VoiceOrigRedialCount(
    VOS_UINT8                           ucPdpId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucPdpId);


    if (TAF_XCC_FAIL_LAYER_L2 == enFailLayer)
    {
        pstCallEntity->ucIsL2ErrReOrig = VOS_TRUE;

        if (TAF_XCC_FAIL_LAYER_L3 != pstCallEntity->enLastReOrigErr)
        {
            /*ԭ��ֵ��ͬ, ���ߵ�һ���ز�ʧ�ܣ����ز������ۼ� */
            if (pstCallEntity->ucReOrigCount < TAF_XCALL_MAX_ORIG_REDIAL_COUNT)
            {
                pstCallEntity->ucReOrigCount++;
            }

        }
        else
        {
            /*ԭ��ֵ��ͬ��������1��ʼ����*/
            pstCallEntity->ucReOrigCount   = 1;

        }

        pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_L2;

    }
    else
    {
        pstCallEntity->ucIsL2ErrReOrig = VOS_FALSE;

        if (TAF_XCC_FAIL_LAYER_L2 != pstCallEntity->enLastReOrigErr)
        {
            if (pstCallEntity->ucReOrigCount < TAF_XCALL_MAX_ORIG_REDIAL_COUNT)
            {
                pstCallEntity->ucReOrigCount++;
            }
        }
        else
        {
            pstCallEntity->ucReOrigCount   = 1;
        }

        pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_L3;

    }

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccNdssResultInd
 ��������  : �յ�XCC��ID_XCC_XCALL_NDSS_RESULT_IND��Ϣ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccNdssResultInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallFound;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           ucCallId;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity   = VOS_NULL_PTR;
    XCC_XCALL_NDSS_RESULT_IND_STRU     *pstNdssResultInd = VOS_NULL_PTR;

    pstNdssResultInd = (XCC_XCALL_NDSS_RESULT_IND_STRU *)pMsg;

    ucCallId    = 0;
    ucCallFound = VOS_FALSE;

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        if ((VOS_TRUE                           == pstXcallEntity->ulUsed)
         && (TAF_CS_CAUSE_XCALL_NDSS_REDIAL_IND == pstXcallEntity->enCause))
        {
            ucCallFound = VOS_TRUE;
            break;
        }
    }

    if (VOS_FALSE == ucCallFound)
    {
        /* �ز�����δ�ҵ� */
        return;
    }

    if (XCC_XCALL_NDSS_RESULT_SUCCESS == pstNdssResultInd->enNsddResult)
    {
        /* �����ز� */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);
    }
    else
    {
        /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
        TAF_XCALL_SndCallReleaseInd(ucCallId);

        /* ��ն�Ӧ��ʵ����Ϣ */
        TAF_XCALL_FreeCallEntity(ucCallId);

        ulNumOfCalls = 0;

        PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

        TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

        /* ���û�к���ʵ�壬��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
        if (0 == ulNumOfCalls)
        {
            TAF_XCALL_SndCallAllReleaseInd(TAF_XCALL_GetClientInfo(ucCallId)->ulModuleId);
        }
    }

    return;
}

/****************s*************************************************************
 �� �� ��  : TAF_XCALL_RcvXccSendContDTMFCnf
 ��������  : �յ�XCC��ID_XCC_XCALL_CONT_DTMF_CNF��Ϣ������
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
    �޸�����   : DTS2015081708770 �޸ģ��յ�Start Cont Dtmf Req��Cnf��������ʱ������ʱ���ٷ���Stop
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccSendContDTMFCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_SEND_CONT_DTMF_CNF_STRU  *pstSndContDTMFCnf = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucRslt;
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;

    pstSndContDTMFCnf = (XCC_XCALL_SEND_CONT_DTMF_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndContDTMFCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    /* ����ȴ�XCC�ظ�CONT DTMF CNF�ı�ʶ */
    /* �����Start Contf Dtmf Req��cnf����ʱ�������棬������ʱ������ʱ����ʱ���ٴ����棬����Stop
        ������ջ����ԭ��ֵ�����ڴ��У�ֱ����ջ��档
    */
    enWaitForXCCDTMFCnfFlag = TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId);
    if (TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF == enWaitForXCCDTMFCnfFlag)
    {
        /* �յ�Start Cont DTMF����Ӧ������ȴ���־λ */
        TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);

        if (TAF_XCC_CAUSE_SUCCESS == pstSndContDTMFCnf->enCause)
        {
            /* ������ʱ������ʱ����ʱ���ٴ����� */
            ulStartAndStopContDtmfIntervalLen = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();
            TAF_XCALL_StartTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                ulStartAndStopContDtmfIntervalLen,
                                pstSndContDTMFCnf->ucCallId);

            /* ���ؽ�����˳� */
            TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, VOS_OK);

            return;
        }
        else if ((TAF_XCC_CAUSE_L2_ACK_FAIL == pstSndContDTMFCnf->enCause)
              || (TAF_XCC_CAUSE_ENCODE_FAIL == pstSndContDTMFCnf->enCause)
              || (TAF_XCC_CAUSE_L2_ACK_TIME_OUT == pstSndContDTMFCnf->enCause))
        {
            /* ������ʱ������ʱ����ʱ���ٴ����� */
            ulStartAndStopContDtmfIntervalLen = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();
            TAF_XCALL_StartTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                ulStartAndStopContDtmfIntervalLen,
                                pstSndContDTMFCnf->ucCallId);

            /* ���ؽ�����˳� */
            TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, VOS_ERR);

            return;
        }
        else /* ����ԭ����ջ��棬����Ҫ������ʱ�� */
        {
            /* do nothing */
        }
    }
    else if (TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF == enWaitForXCCDTMFCnfFlag)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                        "TAF_XCALL_RcvXccSendContDTMFCnf():Current WaitForXCCDTMFCnfFlag is error",
                        enWaitForXCCDTMFCnfFlag);
        return;
    }
    else
    {
        /* �յ�Stop Cont DTMF����Ӧ������ȴ���־λ */
        TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);
    }

    /* CONT DTMF���洦�� �������ʱ����ʱ�����ʧ�ܣ�����CONT DTMF���洦������Ǻ����ͷŻ�״̬�쳣�����建��  */
    switch (pstSndContDTMFCnf->enCause)
    {
        case TAF_XCC_CAUSE_SUCCESS:
            ucRslt = VOS_OK;
            TAF_XCALL_ProcDtmfBuffer(pstSndContDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_L2_ACK_FAIL:
        case TAF_XCC_CAUSE_ENCODE_FAIL:
        case TAF_XCC_CAUSE_L2_ACK_TIME_OUT:
            ucRslt = VOS_ERR;
            TAF_XCALL_ProcDtmfBuffer(pstSndContDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE:
        case TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE:
        case TAF_XCC_CAUSE_ABNORMAL_STATE:
            ucRslt = VOS_ERR;
            TAF_XCALL_CleanDtmfBuff(pstSndContDTMFCnf->ucCallId);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstSndContDTMFCnf->ucCallId);

            break;

        default:
            ucRslt = VOS_ERR;
            break;
    }

    TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, ucRslt);

    return;
}



VOS_VOID TAF_XCALL_RcvXccBurstDtmfInd(VOS_VOID *pMsg)
{
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDTMFInd = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CBURSTDTMF at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_CBURSTDTMF))
    {
        return;
    }

    pstBurstDTMFInd = (XCC_XCALL_BURST_DTMF_IND_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstBurstDTMFInd->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    if (MN_CALL_S_ACTIVE == TAF_XCALL_GetCallState(pstBurstDTMFInd->ucCallId))
    {
        /* send TAF_CALL_EVT_RCV_BURST_DTMF_IND */
        TAF_XCALL_SndBurstDTMFInd(usClientId, ucOpId, pstBurstDTMFInd);

        return;
    }

    /* If current call state is not MN_CALL_S_ACTIVE, the message is discarded. */
    return;
}



VOS_VOID TAF_XCALL_RcvXccContDtmfInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDTMFInd  = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CCONTDTMF at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg, TAF_SDC_CMD_RPT_CTRL_BY_CURC, TAF_SDC_RPT_CMD_CCONTDTMF))
    {
        return;
    }

    pstContDTMFInd = (XCC_XCALL_CONT_DTMF_IND_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstContDTMFInd->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    if(MN_CALL_S_ACTIVE == TAF_XCALL_GetCallState(pstContDTMFInd->ucCallId))
    {
        TAF_XCALL_SndContDTMFInd(usClientId, ucOpId, pstContDTMFInd);
        return;
    }

    /* If current call state is not MN_CALL_S_ACTIVE, the message is discarded. */
    return;
}



/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccTchAssignCmplInd
 ��������  : �����յ�����XCC��TCHָ�����ָʾ
 �������  : pMsg  -- TCH�ŵ�ָ�����ָʾ��Ϣ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccTchAssignCmplInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulCallIdNum;
    VOS_UINT32                          i;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(aucCallIds);

    /* ���º���ʵ���еĺ���ʵ����Ϣ */
    for (i = 0; i < ulCallIdNum; i++)
    {
        pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[i]);

        /* ���ﲻ�жϺ���״̬�����д��ڶ�����£������ɺ���ʵ���ͷ�ʱ������ñ��� */

        pstCallEntity->ucTchAssignInd = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_TCH_ASSIGN_CMPL_IND,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
#endif
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccEccServiceCnf
 ��������  : �����յ�����XCC��ECCҵ��Э�̽��
 �������  : pMsg  -- ECCҵ��Э�̽����Ϣ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccEccServiceCnf(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_ECC_SERVICE_CNF,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}
#endif


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccPrivacyModeSetCnf
 ��������  : �����յ�����XCC��privacy mode���ý��
 �������  : pMsg  -- privacy mode confirm��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccPrivacyModeSetCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU                    *pstPmSetCnf = VOS_NULL_PTR;
    TAF_CCA_CTRL_STRU                                       stCtrl;

    pstPmSetCnf = (XCC_XCALL_PRIVACY_MODE_SET_CNF_STRU *)pMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CCA_CTRL_STRU));
    stCtrl.ucOpId     = (VOS_UINT8)pstPmSetCnf->usOpId;
    stCtrl.ulModuleId = pstPmSetCnf->ulModuleId;
    stCtrl.usClientId = pstPmSetCnf->usClientId;

    TAF_XCALL_SndAppPrivacyModeSetCnf(&stCtrl,
                                      (TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32)pstPmSetCnf->enResult);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccPrivacyModeQryCnf
 ��������  : �����յ�����XCC��privacy mode��ѯ���
 �������  : pMsg  -- privacy mode confirm��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccPrivacyModeQryCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU                    *pstPmQryCnf   = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CCA_CTRL_STRU                                       stCtrl;
    VOS_UINT32                                              ulCallNums;
    VOS_UINT32                                              i;
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                    astCallVoicePrivacyInfo[TAF_XCALL_MAX_NUM];

    pstPmQryCnf = (XCC_XCALL_PRIVACY_MODE_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CCA_CTRL_STRU));
    stCtrl.ucOpId     = (VOS_UINT8)pstPmQryCnf->usOpId;
    stCtrl.ulModuleId = pstPmQryCnf->ulModuleId;
    stCtrl.usClientId = pstPmQryCnf->usClientId;

    ulCallNums = 0;
    PS_MEM_SET(&(astCallVoicePrivacyInfo[0]), 0, sizeof(astCallVoicePrivacyInfo));

    for (i = 0; i < TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        pstCallEntity = TAF_XCALL_GetCallEntityAddr((VOS_UINT8)(i + 1));

        if (VOS_TRUE == pstCallEntity->ulUsed)
        {
            astCallVoicePrivacyInfo[i].ucCallId      = (VOS_UINT8)(i + 1);
            astCallVoicePrivacyInfo[i].enPrivacyMode = pstCallEntity->enPrivacyMode;
            ulCallNums++;
        }
    }

    TAF_XCALL_SndAppPrivacyModeQryCnf(&stCtrl,
                                      pstPmQryCnf->enPrivacyMode,
                                      (VOS_UINT8)ulCallNums,
                                      &astCallVoicePrivacyInfo[0]);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvXccPrivacyModeInd
 ��������  : �����յ�����XCC��privacy mode����ָʾ
 �������  : pMsg  -- privacy mode indication

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccPrivacyModeInd(VOS_VOID *pMsg)
{
    XCC_XCALL_PRIVACY_MODE_IND_STRU    *pstPrivacyModeInd = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntityAddr = VOS_NULL_PTR;

    pstPrivacyModeInd = (XCC_XCALL_PRIVACY_MODE_IND_STRU *)pMsg;

    /* �жϴ�������call id�Ƿ�Ϸ� */
    if (VOS_FALSE == TAF_XCALL_IsAvailCallId(pstPrivacyModeInd->ucCallId))
    {
        return;
    }

    pstCallEntityAddr = TAF_XCALL_GetCallEntityAddr(pstPrivacyModeInd->ucCallId);

    /* ����TAF��privacy mode */
    pstCallEntityAddr->enPrivacyMode = (TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstPrivacyModeInd->enCallPrivacyMode;

    /* ��APP�ϱ�privacy mode  */
    TAF_XCALL_ProcPrivacyModeInd(pstPrivacyModeInd->ucCallId,(TAF_CALL_PRIVACY_MODE_ENUM_UINT8)pstPrivacyModeInd->enPrivacyModeSetting);

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcPrivacyMode
 ��������  : ����Privacy Mode �����ϱ�
 �������  :  VOS_UINT8                           ucCallId,
              TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyModeSetting

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-1-6
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPrivacyModeInd(
    VOS_UINT8                           ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyModeSetting
)
{
    TAF_CCA_CTRL_STRU                   stCtrl;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntityAddr = VOS_NULL_PTR;

    pstCallEntityAddr = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CCA_CTRL_STRU));
    stCtrl.usClientId = MN_GetRealClientId(MN_CLIENT_ID_BROADCAST, WUEPS_PID_TAF);
    stCtrl.ulModuleId = WUEPS_PID_AT;
    stCtrl.ucOpId     = 0;

    TAF_XCALL_SndAppPrivacyModeInd(&stCtrl,
                                   ucCallId,
                                   pstCallEntityAddr->enPrivacyMode,
                                   enPrivacyModeSetting);
    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
