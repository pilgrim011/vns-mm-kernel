/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcTimer.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2014��11��17��
  ����޸�   :
  ��������   : ����timer��ʱ��Ϣ���ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcTimer.h"
#include "TafXCallCtx.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXCallSndMma.h"
#include "TafXCallSndApp.h"
#include "TafXCallProcXcc.h"
#include "TafMmaSndOm.h"

#include "TafXCallProcEccSrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_TIMER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiWaitCallRedialPeriodExpired
 ��������  : �����ز���ʱ���ĳ�ʱ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiWaitCallRedialPeriodExpired(VOS_VOID *pMsg)
{
    /* nothing to do here */

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiWaitCallRedialIntervalExpired
 ��������  : �����ز������ʱ���ĳ�ʱ��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiWaitCallRedialIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulRemainTimeLen;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    enCallType          = TAF_XCALL_GetCallType(ucCallId);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        /* ���ͺ�����Ϣ��XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);
    }
    else
    {
        if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == TAF_SDC_GetCsServiceStatus())
         && (MN_CALL_TYPE_EMERGENCY                 == enCallType))
        {
            /* ���ͺ�����Ϣ��XCC */
            TAF_XCALL_SndXccOrigCallReq(ucCallId);

            return;
        }

        ulRemainTimeLen = 0;
        TAF_XCALL_GetRemainTimerLen(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId, &ulRemainTimeLen);

        if (ulRemainTimeLen >= TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN)
        {


            TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

        }
        else
        {
            /* ֹͣ�ز���ʱ��,�����ʱ��δ������call id��һ�������� */
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId);

            TAF_XCALL_UpdateCcCause(ucCallId, TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
            TAF_XCALL_ProcEccEvent(TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,
                                   TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                                   pMsg,
                                   VOS_NULL_PTR);
#endif

            /* �ϱ�����ʧ�� */
            TAF_XCALL_SndCallReleaseInd(ucCallId);


            /* ��MMA����TAF_MMA_1X_CALL_END_NTF��Ϣ */
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* �ͷź���ʵ�� */
            TAF_XCALL_FreeCallEntity(ucCallId);

        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired
 ��������  : Start Cont Dtmf������Ӧ��������ʱ������ʱ������,��ȡCallID,������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��18��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;

    /* �����棬�����ϣ���һ����Ϣ��Stop Cont Dtmf */
    TAF_XCALL_ProcDtmfBuffer(ucCallId);
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiVoiceEncryptWaitOrigReqExpired
 ��������  : ����ȴ�����������Ϣ��ʱ
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiVoiceEncryptWaitOrigReqExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_WAIT_ORIG_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiDelayEncryptReqExpired
 ��������  : ������ʱ������Կ�����Ͷ�ʱ����ʱ����
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiDelayEncryptReqExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_DELAY_SEND_ENCRYPT_REQ,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiTx01Expired
 ��������  : ����TX01��ʱ����ʱ
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiTx01Expired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_TX01,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiTx02Expired
 ��������  : ����TX02��ʱ����ʱ
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiTx02Expired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_TX02,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,
                           pMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiRemoteCtrlWaitApAnswerExpired
 ��������  : ����TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER��ʱ����ʱ
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiRemoteCtrlWaitApAnswerExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_REMOTE_CTRL_WAIT_AP_ANSWER,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,
                           pMsg,
                           VOS_NULL_PTR);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiPubKeyUpdateWaitAckExpired
 ��������  : ����ȴ���Կ����ȷ����Ϣ��ʱ����ʱ
 �������  : pMsg -- ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-10
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiPubKeyUpdateWaitAckExpired(VOS_VOID *pMsg)
{
    TAF_XCALL_ProcEccEvent(TAF_XCALL_TIMER_MSG_EVENT_PUB_KEY_UPDATE_WAIT_ACK,
                           TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE,
                           pMsg,
                           VOS_NULL_PTR);
}

#endif

#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




