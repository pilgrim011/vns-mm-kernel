/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndXpds.c
  �� �� ��   : ����
  ��    ��   : y00314741
  ��������   : 2015��08��31��
  ����޸�   :
  ��������   : XCC���͸�XPDS����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_XPDS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXpdsOrigCallCnf
 ��������  : ��XPDS����ID_XCC_XPDS_ORIG_AGPS_CALL_CNF
 �������  : ucCallId    -- ����ʵ��
             enFailLayer -- TAF_XCC_FAIL_LAYER_ENUM_UINT8
             enCause     -- ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsOrigCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU   *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_ORIG_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_ORIG_AGPS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->enRslt                      = enCause;
    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enIsL2Err                   = enFailLayer;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXpdsEndCallCnf
 ��������  : ��XPDS����ID_XCC_XPDS_END_AGPS_CALL_CNF
 �������  : ucCallId    -- ����ʵ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsEndCallCnf(
    VOS_UINT8                           ucCallId
)
{
    XCC_XPDS_END_AGPS_CALL_CNF_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_END_AGPS_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_END_AGPS_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_END_AGPS_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXpdsIncomingCallInd
 ��������  : ��XPDS����ID_XCC_XPDS_INCOMING_CALL_IND
 �������  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_INCOMING_CALL_IND_STRU    *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_INCOMING_CALL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_INCOMING_CALL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_INCOMING_CALL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConnectId                 = pstCallInfo->ucConnectId;
    pstMsg->ucIsAlertAnsByPass          = pstCallInfo->ucIsByPassAlertAns;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCsmsCallConnectInd
 ��������  : ��XPDS����ID_XCC_XPDS_CALL_CONN_IND
 �������  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_CALL_CONN_IND_STRU        *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_CALL_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_CALL_CONN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_CALL_CONN_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_CALL_CONN_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXpdsAnswerCallCnf
 ��������  : ��XPDS����ID_XCC_XPDS_ANSWER_CALL_CNF
 �������  : VOS_UINT8                           ucCallId-- ����ʵ��
             TAF_XCC_CAUSE_ENUM_UINT32           enRslt
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsAnswerCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
)
{
    XCC_XPDS_ANSWER_CALL_CNF_STRU      *pstMsg           = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_ANSWER_CALL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_ANSWER_CALL_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_ANSWER_CALL_CNF;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = ucCallId;
    pstMsg->enRslt                      = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXpdsServiceConnectInd
 ��������  : ��XPDS����ID_XCC_XPDS_SERVICE_CONNECT_IND
 �������  : CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo-- ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXpdsServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    XCC_XPDS_SERVICE_CONNECT_IND_STRU  *pstMsg         = VOS_NULL_PTR;

    pstMsg = (XCC_XPDS_SERVICE_CONNECT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
              sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_XPDS);
    pstMsg->ulLength                    = sizeof(XCC_XPDS_SERVICE_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_XCC_XPDS_SERVICE_CONNECT_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucCallId                    = pstCallInfo->ucCallId;
    pstMsg->ucConRef                    = pstCallInfo->ucConRef;
    pstMsg->enSo                        = pstCallInfo->enCurrentSo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_XCC, pstMsg);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
