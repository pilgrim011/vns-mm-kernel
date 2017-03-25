/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmSndInternalMsg.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��9��
  ����޸�   :
  ��������   : spm����spm����Ϣ�Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafLog.h"
#include "TafSpmCtx.h"
#include "TafSpmSndInternalMsg.h"
#include "TafInternalInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_INTERNAL_MSG_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_SPM_SndServiceCtrlRsltInd
 ��������  : ����service ctrl�����Ϣ
 �������  : enRslt                     - ״̬���˳����
             ulCause                    - ʧ��ʱЯ����caueֵ
             usClientId                 - ��ǰ����FDN CALL CTRL����client ID
             pstEntryMsg                - �޸Ĺ��������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
    VOS_UINT32                                              ulCause,
    VOS_UINT16                                              usClientId,
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU      *pstServiceCtrlRstInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstServiceCtrlRstInd = (TAF_SPM_SERVICE_CTRL_RSLT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU));
    if (VOS_NULL_PTR == pstServiceCtrlRstInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_INT8*)pstServiceCtrlRstInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstServiceCtrlRstInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstServiceCtrlRstInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstServiceCtrlRstInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_SERVICE_CTRL_RSLT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstServiceCtrlRstInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND;

    /* ��д��Ϣ���� */
    pstServiceCtrlRstInd->enResult                  = enRslt;
    pstServiceCtrlRstInd->ulCause                   = ulCause;
    pstServiceCtrlRstInd->usClientId                = usClientId;
    pstServiceCtrlRstInd->stEntryMsg.ulEventType    = pstEntryMsg->ulEventType;

    PS_MEM_CPY(pstServiceCtrlRstInd->stEntryMsg.aucEntryMsgBuffer,
                pstEntryMsg->aucEntryMsgBuffer,
                sizeof(pstEntryMsg->aucEntryMsgBuffer));

    /* �����ڲ���Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstServiceCtrlRstInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SndServiceCtrlRsltInd: Send message failed.");
    }

    return;
}

/* �ŵ�IMS�꿪�����湫��ʹ�� */
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_SndInternalDomainSelectionInd
 ��������  : ����ҵ����ѡ��ָʾ��SPM������������Ϣ����ѡ��
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��24��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_IND_STRU        *pstDomainSelInd = VOS_NULL_PTR;

    /* allocate memory for message */
    pstDomainSelInd = (TAF_SPM_DOMAIN_SEL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_TAF,
                                                        sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU));
    /* return if memory allocation is failure */
    if (VOS_NULL_PTR == pstDomainSelInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Memory allocation is failure!");

        return;
    }

    /* initialize message */
    PS_MEM_SET(((VOS_INT8*)pstDomainSelInd) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* fill message header */
    pstDomainSelInd->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulSenderPid                 = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstDomainSelInd->MsgHeader.ulReceiverPid               = WUEPS_PID_TAF;
    pstDomainSelInd->MsgHeader.ulLength                    = sizeof(TAF_SPM_DOMAIN_SEL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDomainSelInd->MsgHeader.ulMsgName                   = TAF_SPM_INTERNAL_DOMAIN_SEL_IND;

    /* send domain selection indication message to self */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstDomainSelInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SPM_SndInternalDomainSelectionInd: ERROR: Send message failed.");
    }

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendMsgSmmaRsp
 ��������  : SPM��MSGģ�鷢��SMMA RSP��Ϣ,Я����������
 �������  : enMsgSignallingType---��������
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��17��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaRsp = VOS_NULL_PTR;
    TAF_SPM_SMMA_IND_STRU              *pstSmmaInd = VOS_NULL_PTR;

    pstSmmaRsp = (TAF_SPM_SMMA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(TAF_SPM_SMMA_RSP_STRU));

    if (VOS_NULL_PTR == pstSmmaRsp)
    {
        MN_WARN_LOG("TAF_SPM_SendMsgSmmaRsp:ERROR: VOS_AllocMsg fail.");
        return;
    }

    pstSmmaInd  = (TAF_SPM_SMMA_IND_STRU *)pstMsg;
    
    PS_MEM_SET(pstSmmaRsp, 0, sizeof(TAF_SPM_SMMA_RSP_STRU));

    pstSmmaRsp->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulSenderPid          = WUEPS_PID_TAF;
    pstSmmaRsp->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSmmaRsp->ulReceiverPid        = WUEPS_PID_TAF;
    pstSmmaRsp->ulLength             = sizeof(TAF_SPM_SMMA_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSmmaRsp->ulMsgId              = ID_TAF_SPM_SMMA_RSP;
    pstSmmaRsp->clientId             = pstSmmaInd->clientId;
    pstSmmaRsp->opId                 = pstSmmaInd->opId;
    pstSmmaRsp->enMsgSignallingType  = enMsgSignallingType;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmmaRsp ) )
    {
        MN_WARN_LOG( "TAF_SPM_SendMsgSmmaRsp:WARNING:SEND ID_TAF_SPM_SMMA_RSP msg FAIL!" );
    }

    return;
}
#endif
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-25, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_SPM_SndTafRelCallReq
 ��������  : ������Ϣ֪ͨCALLģ���ͷ���������������������н������д��ڣ���
             ��������ʧ�ܣ�

 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE                     - �����ڲ���Ϣ�ɹ�
             VOS_FASLE                    - �����ڲ���Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��24��
    ��    ��   : y00245242
    �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
)
{
    TAF_CALL_TAF_REL_CALL_REQ_STRU     *pstRelCallReq = VOS_NULL_PTR;

    pstRelCallReq = (TAF_CALL_TAF_REL_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                        sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstRelCallReq)
    {
        MN_WARN_LOG("TAF_SPM_SndTafRelCallReq:ERROR: VOS_AllocMsg fail.");
        return;
    }

    PS_MEM_SET(pstRelCallReq, 0, sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU));

    pstRelCallReq->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstRelCallReq->ulSenderPid          = WUEPS_PID_TAF;
    pstRelCallReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstRelCallReq->ulReceiverPid        = WUEPS_PID_TAF;
    pstRelCallReq->ulLength             = sizeof(TAF_CALL_TAF_REL_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRelCallReq->ulMsgId              = TAF_CALL_TAF_REL_CALL_REQ;

    pstRelCallReq->usClientId           = usClientId;
    pstRelCallReq->ucOpId               = ucOpId;
    pstRelCallReq->enRelType            = enRelType;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstRelCallReq))
    {
        MN_WARN_LOG( "TAF_SPM_SndTafRelCallReq:WARNING:SEND TAF_SPM_SndTafRelCallReq msg FAIL!" );
    }

    return;
}
#endif
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


