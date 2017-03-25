/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndCsms.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��10��14��
  ����޸�   :
  ��������   : XCC���͸�CSMS����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasXccSndCsms.h"
#include  "xcc_sms_pif.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_CSMS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsOrigCallCnf
 ��������  : ��CSMS����ID_XCC_CSMS_ORIG_SMS_CALL_CNF
 �������  : ucCallId    -- ����ʵ��
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_ORIG_SMS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC, sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_ORIG_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_ORIG_SMS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->enRslt                      = enCause;
    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsHangupCallCnf
 ��������  : ��CSMS����ID_XCC_CSMS_END_SMS_CALL_CNF
 �������  : ucCallId    -- ����ʵ��
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsHangupCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_CSMS_END_SMS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_END_SMS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_END_SMS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_END_SMS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsHangupCallCnf
 ��������  : ��CSMS����ID_XCC_CSMS_END_SMS_CALL_CNF
 �������  : ucCallId    -- ����ʵ��
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
)
{
    XCC_CSMS_ANSWER_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_ANSWER_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_ANSWER_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enRslt                      = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsIncomingCallInd
 ��������  : ��CSMS����ID_XCC_CSMS_INCOMING_CALL_IND
 �������  : pstCallInfo    -- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_INCOMING_CALL_IND_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_INCOMING_CALL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucIsAlertAnsByPass          = pstCallInfo->ucIsByPassAlertAns;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsCallConnectInd
 ��������  : ��CSMS����ID_XCC_CSMS_CALL_CONN_IND
 �������  : pstCallInfo    -- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_CALL_CONN_IND_STRU        *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_CALL_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_CALL_CONN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_CALL_CONN_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsServiceConnectInd
 ��������  : ��CSMS����ID_XCC_CSMS_SERVICE_CONNECT_IND��SOЭ����ɺ�֪ͨSMS
 �������  : pstCallInfo    -- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU                      *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_SERVICE_CONNECT_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsMsgWaitingInd
 ��������  : ��CSMS����ID_XCC_CSMS_MSG_WATING_IND
 �������  : pstCallInfo    -- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCsmsMsgWaitingInd(
    VOS_UINT8                           ucMsgCnt
)
{
    XCC_CSMS_MSG_WATING_IND_STRU       *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_CSMS_MSG_WATING_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_CSMS_MSG_WATING_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XSMS);
    pstMsg->ulLength                    = sizeof(XCC_CSMS_MSG_WATING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId                     = ID_XCC_CSMS_MSG_WATING_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucMsgCnt                    = ucMsgCnt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
