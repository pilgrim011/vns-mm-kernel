/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallPorcVc.c
  �� �� ��   : ����
  ��    ��   : Y00213812
  ��������   : 2014��09��13��
  ��������   : TAF X CALL����VC����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��13��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "TafXCallCtx.h"
#include "TafCsCallCommDef.h"
#include "VcCallInterface.h"
#include "TafXCallProcEccSrv.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "MnComm.h"
#include "TafSdcCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_VC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvVcEndCall
 ��������  : ����VC_CALL_END_CALL��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��22��
    ��    ��   : l00359089
    �޸�����   : ʵ�ֺ�������
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvVcEndCall(VOS_VOID *pMsg)
{
    VC_CALL_MSG_STRU                   *pstRcvMsg = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           i;

    pstRcvMsg    = (VC_CALL_MSG_STRU*)pMsg;
    enEndCause   = TAF_CALL_ConvertVcCauseToTafCsCause(pstRcvMsg->enCause);

    ulNumOfCalls = 0;
    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);
    ulModuleId = pstRcvMsg->ulSenderPid;

    /* ѭ���Ҷ����з�idle�ĺ��� */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        TAF_XCALL_ProcEccEvent(TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,
                               TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                               (VOS_VOID *)pstRcvMsg,
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
            TAF_XCALL_UpdateCcCause(aucCallIds[i], enEndCause);

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

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            TAF_XCALL_UpdateCcCause(aucCallIds[i], enEndCause);

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
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        /* ��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
    else
    {
        TAF_XCALL_RegSsKeyEvent(aucCallIds[ulNumOfCalls - 1], TAF_XCALL_SS_PROG_EVT_REL, TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC);
    }
    return;
}


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


