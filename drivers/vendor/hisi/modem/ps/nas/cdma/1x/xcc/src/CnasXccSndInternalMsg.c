/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndInternalMsg.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��6��
  ����޸�   :
  ��������   : XCC���͸�XCC����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��6��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasXccSndInternalMsg.h"
#include  "CnasXccCtx.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */
/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndMoCallingRslt
 ��������  : MO CALLING L2״̬����ɽ����Ϣ
 �������  : ucConnId : VOS_UINT8
             enRslt   : CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndMoCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason
)
{
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enRslt;
    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->enEndReason                 = enEndReason;


    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndMtCallingRslt
 ��������  : MT CALLING L2״̬����ɽ����Ϣ
 �������  : ucConnId : VOS_UINT8
             enRslt   : CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndMtCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason
)
{
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->enRslt                      = enRslt;
    pstMsg->enEndReason                 = enEndReason;

    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXccAbortReq
 ��������  : ��ֹ��ǰ�ĺ��н�չ
 �������  : ucConnId    : VOS_UINT8
             enAbortType : CNAS_XCC_ABORT_TYPE_ENUM_UINT32
             enAbortCause: abort cause
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��16��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : ��Ϣ������abort cause
*****************************************************************************/
VOS_VOID CNAS_XCC_SndXccAbortReq(
    VOS_UINT8                           ucConnId,
    VOS_UINT32                          ulEventType,
    TAF_XCC_CAUSE_ENUM_UINT32           enAbortCause
)
{
    CNAS_XCC_XCC_ABORT_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_ABORT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_ABORT_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->ulEventType                 = ulEventType;

    pstMsg->enAbortCause                = enAbortCause;

    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXccPowerDownInd
 ��������  : �ػ�ָʾ��Ϣ
 �������  : ucConnId   : VOS_UINT8

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��16��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXccPowerDownInd(
    VOS_UINT8                           ucConnId
)
{
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_POWER_DOWN_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_POWER_DOWN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_POWER_DOWN_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_POWER_DOWN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;

    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXccNdssRedialInd
 ��������  : NDSS�ز�ָʾ
 �������  : ucConnId   : VOS_UINT8

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXccNdssRedialInd(
    VOS_UINT8                           ucConnId
)
{
    CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_NDSS_REDIAL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->aucReserved[0]              = 0;
    pstMsg->aucReserved[1]              = 0;
    pstMsg->aucReserved[2]              = 0;


    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndXcc1xCallStateUpdateInd
 ��������  : call״̬�����仯��ʱ�����ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndXcc1xCallStateUpdateInd(
    VOS_VOID
)
{
    CNAS_XCC_XCC_CALL_STATE_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_CALL_STATE_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_CALL_STATE_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_CALL_STATE_IND;
    pstMsg->usOpId                      = 0;

    /* ����Ϣ���ڲ����� */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*lint -restore*/

#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
