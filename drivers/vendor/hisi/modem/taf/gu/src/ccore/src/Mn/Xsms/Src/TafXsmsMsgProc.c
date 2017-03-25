/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsMsgProc.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service)������Ϣ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXsmsMsgProc.h"
#include "TafXsmsMoFsmMain.h"
#include "TafXsmsMtFsmMain.h"
#include "siapppih.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsUimProc.h"
#include "TafXsmsSndAt.h"
#include "TafXsmsEncode.h"
#include "NVIM_Interface.h"
#include "TafXsmsTimer.h"
#include "TafXsmsSndCas.h"
#include "csn1clib.h"
#include "TafXsmsSndXcc.h"
#include "TafXsmsStkInterface.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXsmsSndXcall.h"


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "UserDefinedDataTypes_cs0005.h"
#include "ed_c_cs0005.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MSG_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgHook
 ��������  : XSMS�ڲ���ά�ɲ⹳��������
 �������  : enMsgName:�ڲ���ά�ɲ���Ϣ��
             pucMsg:��ά�ɲ���Ϣ
             ulMsgLen:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 enMsgName, VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen)
{
    TAF_XSMS_MSG_HOOK_STRU             *pstMsg;

    pstMsg = (TAF_XSMS_MSG_HOOK_STRU *)VOS_AllocMsg(UEPS_PID_XSMS, sizeof(TAF_XSMS_MSG_HOOK_STRU) - VOS_MSG_HEAD_LENGTH + ulMsgLen - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MsgHook:WARNING:alloc msg failed.\n");

        return;
    }

    pstMsg->ulReceiverPid   = UEPS_PID_XSMS;
    pstMsg->enMsgId         = enMsgName;

    PS_MEM_CPY(pstMsg->aucMsg, pucMsg, ulMsgLen);


    DIAG_TraceReport(pstMsg);

    VOS_FreeMsg(UEPS_PID_XSMS, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtDeleteMsgProc
 ��������  : XSMS����AT������ɾ��������Ϣ������
 �������  : pstMsg:AT����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_AtDeleteMsgProc(TAF_XSMS_DELETE_MSG_REQ_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    VOS_UINT8                           ucIndex;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();
    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();

    /* ��ǰ�г�ʼ��δ��� */
    if (TAF_XSMS_INIT_STATUS_FINISH != pstInitCtrlInfoAddr->enSmsInitState)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:XSMS Init not finish");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* ��ǰ��AT�����ڴ��� */
    if (TAF_XSMS_UIM_LOCK_LOCKED == pstCtrlInfoAddr->enUimLock)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:XSMS At cmd Locked");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* AT���������ֵ��0��ʼ��UIM���е�����ֵ��1��������Ҫ��1���ٴ��� */
    ucIndex = pstMsg->ucIndex + 1;

    if (ucIndex > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:Index invalid");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* ��������Ϣ */
    pstCtrlInfoAddr->usClient     = pstMsg->usClientId;
    pstCtrlInfoAddr->ucOpID       = pstMsg->ucOpId;
    pstCtrlInfoAddr->enAppMsgType = pstMsg->ulMsgName;
    pstCtrlInfoAddr->enUimLock    = TAF_XSMS_UIM_LOCK_LOCKED;

    /* ɾ���ռ�¼�����ز����ɹ� */
    if (TAF_XSMS_EFSMS_STATUS_FREE == TAF_XSMS_GetBitFromBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex))
    {
        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_OK);
    }
    else
    {
        TAF_XSMS_AtSmsDeleteReq(ucIndex);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtWriteMsgProc
 ��������  : XSMS����AT������д������Ϣ������
 �������  : pstMsg:AT����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_AtWriteMsgProc(TAF_XSMS_WRITE_MSG_REQ_STRU *pstMsg)
{
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucIndex;

    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();
    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ��ǰ��ʼ��δ��� */
    if (TAF_XSMS_INIT_STATUS_FINISH != pstInitCtrlInfoAddr->enSmsInitState)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:XSMS Init not finish");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    /* ��ǰû��AT�����ڴ��� */
    if (TAF_XSMS_UIM_LOCK_LOCKED == pstCtrlInfoAddr->enUimLock)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:XSMS At cmd Locked");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    /* �����ǰ�����ڿ��еļ�¼�����ش���ͨ��AT�����ϱ��洢���� */
    if (VOS_OK != TAF_XSMS_FindFreeIndex(&ucIndex))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:Not find free index");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        TAF_XSMS_MsgUimFullInd();

        return;
    }

    /* ����MO�ı��뺯������TransportLayer���ݣ�Ԥ��ǰ�����ֽ����״̬��Ϣ�ͳ��ȣ�Reply Seq��ֵĬ�϶���0 */
    if (VOS_OK != TAF_XSMS_EncodeBearDataStruToSimRaw(&pstMsg->st1XSms,
                                                        aucData + 2,
                                                        VOS_NULL,
                                                        &ucLen,
                                                        pstMsg->enSmsStatus,
                                                        VOS_TRUE))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:TAF_XSMS_EncodeBearDataStruToSimRaw return fail");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    switch (pstMsg->enSmsStatus)
    {
        case TAF_XSMS_STATUS_REC_UNREAD:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_UNREAD;
            break;

        case TAF_XSMS_STATUS_REC_READ:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_READ;
            break;

        case TAF_XSMS_STATUS_STO_UNSEND:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_UNSEND;
            break;

        case TAF_XSMS_STATUS_STO_SEND:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_SEND;
            break;

        default:
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:Invalid SMS status");

            TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);
            return;
    }

    /* ��������Ϣ */
    pstCtrlInfoAddr->usClient     = pstMsg->usClientId;
    pstCtrlInfoAddr->ucOpID       = pstMsg->ucOpId;
    pstCtrlInfoAddr->enAppMsgType = pstMsg->ulMsgName;
    pstCtrlInfoAddr->enUimLock    = TAF_XSMS_UIM_LOCK_LOCKED;

    aucData[1] = ucLen;

    TAF_XSMS_AtSmsWriteReq(ucLen + 2, aucData, ucIndex);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtMsgProc
 ��������  : XSMS����AT��������Ϣ������
 �������  : pstMsg:AT����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_AtMsgProc(MsgBlock* pstMsg)
{
    VOS_UINT32                          ulRet;
    TAF_XSMS_SEND_MSG_REQ_STRU         *pstSendReqMsg;

    pstSendReqMsg   = (TAF_XSMS_SEND_MSG_REQ_STRU *)pstMsg;

    /* ��ΪA��PID����16λ����״̬������ʹ��XSMS�Լ���PID */
    pstSendReqMsg->ulSenderPid = UEPS_PID_XSMS;

    switch (pstSendReqMsg->ulMsgName)
    {
        /* AT������Ķ��ŷ������� */
        case TAF_XSMS_APP_MSG_TYPE_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* �ж��Ƿ���Խ�XCALL��������ڷ��ͳ����� */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_AT))
                {
                    if (VOS_OK != TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_AT,
                                                                 VOS_TRUE,
                                                                 0,
                                                                 &pstSendReqMsg->st1XSms))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_AtMsgProc:TAF_XSMS_IsRecCanInsertToPool fail");
                        TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_ERR);
                    }
                    else
                    {
                        TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_OK);
                    }

                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_AtMsgProc:can not insert to send pool");
                    TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_ERR);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);
            TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, ulRet);

            break;

        /* AT������Ķ���д������ */
        case TAF_XSMS_APP_MSG_TYPE_WRITE_REQ:

            TAF_XSMS_AtWriteMsgProc((TAF_XSMS_WRITE_MSG_REQ_STRU *)pstMsg);

            break;

        /* AT������Ķ���ɾ������ */
        case TAF_XSMS_APP_MSG_TYPE_DELETE_REQ:

            TAF_XSMS_AtDeleteMsgProc((TAF_XSMS_DELETE_MSG_REQ_STRU *)pstMsg);

            break;

        /* AT������Ķ��������� */
        case TAF_XSMS_APP_MSG_TYPE_UIM_MEM_SET_REQ:

            TAF_XSMS_AtApMemFullMsgProc((TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *)pstMsg);

            break;


        default:

            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtMsgProc:Invalid request");

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_StkProc
 ��������  : STK����Ϣ����
 �������  : pstMsg  ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��30��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_StkProc(MsgBlock *pstMsg)
{
    STK_XSMS_SEND_SMS_REQ_STRU         *pstSendReq;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usIsTlAckNeed  = VOS_TRUE;

    pstSendReq = (STK_XSMS_SEND_SMS_REQ_STRU*)pstMsg;

    if (VOS_TRUE == pstSendReq->ulIsUserAck)
    {
        usIsTlAckNeed  = VOS_FALSE;
    }

    switch (pstSendReq->enMsgId)
    {
        case ID_STK_XSMS_SEND_SMS_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* �ж��Ƿ���Խ�XCALL��������ڷ��ͳ����� */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_STK))
                {
                    if (VOS_OK != TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_STK,
                                                             usIsTlAckNeed,
                                                             0,
                                                             &pstSendReq->st1XSms))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_StkProc : TAF_XSMS_InsertRecToMoSendPool ERR");
                        TAF_XSMS_StkMsgSubmitCnf(VOS_ERR);
                    }
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_StkProc : can not insert to pool");
                    TAF_XSMS_StkMsgSubmitCnf(VOS_ERR);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_FALSE == pstSendReq->ulIsUserAck)
            {
                TAF_XSMS_StkMsgSubmitCnf(ulRet);
            }

            break;

        default:
            break;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TimeOutMsgProc
 ��������  : XSMS PID��ʱ����ʱ������
 �������  : pstRelTimerMsg:��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_TimeOutMsgProc(REL_TIMER_MSG *pstRelTimerMsg)
{
    TAF_XSMS_WARNING_LOG1("TAF_XSMS_TimeOutMsgProc: timer name is",pstRelTimerMsg->ulName);

    if (TI_TAF_XSMS_TIMER_INIT_PROTECT == pstRelTimerMsg->ulName)
    {
        TAF_XSMS_InitTimeOutMsgProc();
    }
    else if (TI_TAF_XSMS_TIMER_MO_POOL_REFRESH == pstRelTimerMsg->ulName)
    {
        TAF_XSMS_RefreshRecsInMoSendPool();
    }
    else
    {
        if (TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT == pstRelTimerMsg->ulName)
        {
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT,
                                      TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        /* MO��MT��״̬������ */
        if (TI_TAF_XSMS_TIMER_INIT_PROTECT > pstRelTimerMsg->ulName)
        {
            TAF_XSMS_MtFsmMainProc((MsgBlock*)pstRelTimerMsg);
        }
        else
        {
            TAF_XSMS_MoFsmMainProc((MsgBlock*)pstRelTimerMsg);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_XccEndCallCnfChooseStateMachine
 ��������  : �ж�END_CALL_CNF��Ϣ��ʲô״̬��(MO����MT)
 �������  : pstMsg:�յ���XCC��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_XccEndCallCnfChooseStateMachine(MsgBlock *pstMsg)
{
    XCC_CSMS_END_SMS_CALL_CNF_STRU     *pstEndCallMsg;

    pstEndCallMsg = (XCC_CSMS_END_SMS_CALL_CNF_STRU*)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO == pstEndCallMsg->ucCallId)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_SEND_XCC_CALL_ID_MT == pstEndCallMsg->ucCallId)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* �����CALL ID */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_XccEndCallCnfChooseStateMachine: Wrong Call Id");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_XccSoIndChooseStateMachine
 ��������  : �ж�SO_IND��Ϣ��ʲô״̬��(MO����MT)
 �������  : pstMsg:�յ�XCC����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID TAF_XSMS_XccSoIndChooseStateMachine(MsgBlock *pstMsg)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU *pstSoIndMsg;

    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO == pstSoIndMsg->ucCallId)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_SEND_XCC_CALL_ID_MT == pstSoIndMsg->ucCallId)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* �����CALLID */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_XccSoIndChooseStateMachine: Wrong Call Id");
    }

    return;

}
/*****************************************************************************
 �� �� ��  : TAF_XSMS_XccMsgProc
 ��������  : XCC��Ϣ�ַ�������
 �������  : pstMsg:�յ���XCC��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_XccMsgProc(MsgBlock *pstMsg)
{
    VOS_UINT16                          usMsgName;

    PS_MEM_CPY(&usMsgName, pstMsg->aucValue, 2);

    switch (usMsgName)
    {
        case ID_XCC_CSMS_ORIG_SMS_CALL_CNF:

            TAF_XSMS_MoFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_END_SMS_CALL_CNF:

            /* ����call ID����˭��������� */
            TAF_XSMS_XccEndCallCnfChooseStateMachine(pstMsg);

            break;

        case ID_XCC_CSMS_INCOMING_CALL_IND:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_CALL_CONN_IND:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_ANSWER_CALL_CNF:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_SERVICE_CONNECT_IND:

            /* ����call ID����˭������ */
            TAF_XSMS_XccSoIndChooseStateMachine(pstMsg);

            break;

        case ID_XCC_CSMS_MSG_WATING_IND:

            /* voice mail notification */
            TAF_XSMS_DealXccVoiceMailInd(pstMsg);
            break;


        default:

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_1xCasMsgProc
 ��������  : ����㷢��������Ϣ������
 �������  : pstMsg:����㷢��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_1xCasMsgProc(MsgBlock* pstMsg)
{
    VOS_UINT16                          usMsgName;

    PS_MEM_CPY(&usMsgName, pstMsg->aucValue, 2);

    /* �ж�msg name */
    switch (usMsgName)
    {
        case ID_CAS_CNAS_1X_DSCH_DATA_CNF:

            TAF_XSMS_CasDschCnfProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_DSCH_DATA_IND:

            TAF_XSMS_CasDschDataIndProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_CSCH_DATA_CNF:

            TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);

            TAF_XSMS_CasCschCnfProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_CSCH_DATA_IND:

            TAF_XSMS_CasCschDataIndProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_SMS_ABORT_IND:

            TAF_XSMS_CasAbortProc(pstMsg);

            break;

        default:
            break;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransCSCHDataToDbm
 ��������  : CAS���͵�cSCH����ת����DBM
 �������  : pstCschData:�յ���CSCH_DATA_IND
 �������  : pstDbm:DATA BURST MSG
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransCSCHDataToDbm
(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransCSCHDataToDbm: Msglen is ", pstCschData->usMsgDataLen);

    if (pstCschData->usMsgDataLen < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransCSCHDataToDbm: bit length error !");

        return VOS_ERR;
    }

    TAF_XSMS_TransAucDataToDbm(pstCschData->aucMsgData,pstDbm);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransCSCHDataToDbm: DBM NUMFIELDS is ", pstDbm->ucNumFields);

    if ((pstCschData->usMsgDataLen > ((pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        || (pstCschData->usMsgDataLen < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1("TAF_XSMS_TransCSCHDataToDbms: num fields bit length not matched !" ,pstDbm->ucNumFields);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransDbmToCSCHData
 ��������  : DBM����ת����CAS���͵�CSCH_DATA_REQ
 �������  : pstDbm:DATA BURST MSG
 �������  : pstCschData:Ҫ���͵�CSCH_DATA_IND
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToCSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschData
)
{
    VOS_UINT16                          usBitNum;

    usBitNum = (VOS_UINT16)TAF_XSMS_TransDbmToAucData(pstDbm, pstCschData->aucMsgData);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDbmToCSCHData:data req bit num is ", usBitNum);

    /* ���BIT ��С��32�� ���ߴ���DBM���ܳ��� ���ش��� */
    if ((usBitNum < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        ||(usBitNum > (pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE)
        ||(usBitNum < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1(" Bit Num error! dbm length is", pstDbm->ucNumFields);
        return VOS_ERR;
    }

    pstCschData->usMsgDataLen   = usBitNum;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransDSCHDataToDbm
 ��������  : CAS���͵�DSCH����ת����DBM
 �������  : pstDschData:����㷢������DATA_IND
 �������  : pstDbm:DATA BURST MSG
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDSCHDataToDbm
(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDSCHDataToDbm: Msglen is ", pstDschData->usMsgDataLen);

    if (pstDschData->usMsgDataLen < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransDSCHDataToDbm: bit length error !");

        return VOS_ERR;
    }

    TAF_XSMS_TransAucDataToDbm(pstDschData->aucMsgData,pstDbm);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDSCHDataToDbm: DBM NUMFIELDS is ", pstDbm->ucNumFields);

    if ((pstDschData->usMsgDataLen > ((pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        || (pstDschData->usMsgDataLen < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransDSCHDataToDbm: num fields bit length not matched !");
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransAucDataToDbm
 ��������  : DATA_Ind�� DATA�� ת����DBM
 �������  : paucData :DATA_Ind�� DATA��
 �������  : pstDbm::Data Burst MSGS
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_TransAucDataToDbm
(
    VOS_UINT8                          *paucData ,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{
    VOS_UINT8                           i                   =  0;
    VOS_UINT16                          usBitpos            =  0;


    /* ����MSG NUMS */
    pstDbm->ucMsgNum        =   paucData[0];
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����BURST TYPE */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucBurstType), usBitpos, 6);
    usBitpos               +=   6;

    /* ����NUM MSGS */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucNumMsgs), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����NUM FIELDS */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucNumFields), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;


    /* ����DBM DATA */
    for (i = 0; i < pstDbm->ucNumFields; i++)
    {
        TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->aucData[i]), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
        usBitpos          +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransDbmToDSCHData
 ��������  : DBM����ת����CAS���͵�DSCH_DATA_REQ
 �������  : pstDbm :Data Burst MSG
 �������  : pstDschData:Ҫ���ͳ�ȥ��DSCH_DATA_REQ
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToDSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDschData
)
{
    VOS_UINT16                          usBitNum;

    usBitNum = (VOS_UINT16)TAF_XSMS_TransDbmToAucData(pstDbm, pstDschData->aucMsgData);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDbmToDSCHData: data req bit num is ", usBitNum);

    /* ���BIT ��С��32�� ���ߴ���DBM���ܳ��� ���ش��� */
    if ((usBitNum < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        ||(usBitNum > (pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE)
        ||(usBitNum < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1(" Bit Num error! dbm length is", pstDbm->ucNumFields);
        return VOS_ERR;
    }

    pstDschData->usMsgDataLen   = usBitNum;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TransDbmToAucData
 ��������  : DBM����ת����CAS����DATA_REQ�� DATA��
 �������  : pstDbm :Data Burst MSG
 �������  : paucData:Ҫ���ͳ�ȥ��DATA_REQ��DATA��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��24��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToAucData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    VOS_UINT8                          *paucData
)
{

    VOS_UINT32                          i           = 0;
    VOS_UINT16                          usBitPos    = 0;

    /* ����MSG NUM  */
    paucData[0]     =   pstDbm->ucMsgNum;
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����BURST TYPE */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucBurstType, 6, usBitPos);
    usBitPos       +=   6;

    /* ����NUM MSGS */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucNumMsgs, TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����NUM FIELDS */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucNumFields, TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����DATA */
    for (i = 0; i < pstDbm->ucNumFields; i++)
    {
        TAF_XSMS_PackBitToByte(paucData, pstDbm->aucData[i], TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
        usBitPos   +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;
    }

    return usBitPos;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_CasDschCnfProc
 ��������  : ����MSG_SEQ_NUM �����ǽ�MO ����MT��״̬��
 �������  : pstMsg:CAS����������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_CasDschCnfProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstCnfMsg;

    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (TAF_XSMS_CAS_DATA_REQ_TYPE_MO == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_CAS_DATA_REQ_TYPE_MT == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* DATA_CNF ����SEQ NUM���� */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschCnfProc: Wrong seq num");
    }

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_XSMS_CasDschDataIndProc
 ��������  : ��DATA_INDת�����ڲ�����Ϣ����,
             ������DBM�����MSGTYPE�ж��ǽ�MO����MT��״̬��
 �������  : pstMsg:����㷢��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_CasDschDataIndProc(MsgBlock *pstMsg)
{

    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstCnfMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    TAF_XSMS_CAS_DATA_IND_MSG_STRU      stDataInd;

    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    PS_MEM_SET(&stDbm, 0, sizeof(TAF_XSMS_DATA_BURST_MSG_STRU));
    PS_MEM_SET(&stDataInd, 0, sizeof(TAF_XSMS_CAS_DATA_IND_MSG_STRU));

    if (VOS_OK != TAF_XSMS_TransDSCHDataToDbm(pstCnfMsg, &stDbm))
    {
        /* ����ʧ�� */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:TAF_XSMS_TransDSCHDataToDbm return fail");

        return;
    }

    if (VOS_TRUE != TAF_XSMS_CheckIsSmsDbm(&stDbm))
    {
        /* DBM������Ϣ����SMS */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:TAF_XSMS_CheckIsSmsDbm return false");

        return;
    }

    /* �����ڲ���Ϣ�ṹ�� */
    PS_MEM_CPY(&stDataInd, pstCnfMsg, VOS_MSG_HEAD_LENGTH + sizeof(pstCnfMsg->enMsgId) + sizeof(pstCnfMsg->usOpId));
    stDataInd.ucLen = stDbm.ucNumFields;
    PS_MEM_CPY(stDataInd.aucMsg, stDbm.aucData, stDataInd.ucLen);

    if (TAF_XSMS_TL_P2P_MSG == stDbm.aucData[0]) /* Э�� C.S0015 �½� 3.4.1*/
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock*)&stDataInd);
    }
    else if (TAF_XSMS_TL_ACK_MSG == stDbm.aucData[0])
    {
        TAF_XSMS_MoFsmMainProc((MsgBlock*)&stDataInd);
    }
    else
    {
        /* �����MSG TYPE */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:Wrong Msg type");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_CasCschCnfProc
 ��������  : �ַ�CAS��CSCH DATA CNF ��MO����MT��״̬������
 �������  : pstMsg:�յ��Ľ�����ڹ����ŵ����͹�����CNF��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_CasCschCnfProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU     *pstCnfMsg;

    pstCnfMsg = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU*)pstMsg;

    if (TAF_XSMS_CAS_DATA_REQ_TYPE_MO == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_CAS_DATA_REQ_TYPE_MT == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* error */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschCnfProc: Wrong seq num");;
    }

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_XSMS_CasDschDataIndProc
 ��������  : ��DATA_INDת�����ڲ�����Ϣ����,
             ������DBM�����MSGTYPE�ж��ǽ�MO����MT��״̬��
 �������  : pstMsg:�յ���CSCH_DATA_IND
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_CasCschDataIndProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstDataIndMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    TAF_XSMS_CAS_DATA_IND_MSG_STRU      stDataInd;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec      = TAF_XSMS_MtGetRecAddr();
    pstDataIndMsg = (CAS_CNAS_1X_CSCH_DATA_IND_STRU*)pstMsg;
    PS_MEM_SET(&stDbm, 0, sizeof(TAF_XSMS_DATA_BURST_MSG_STRU));
    PS_MEM_SET(&stDataInd, 0, sizeof(TAF_XSMS_CAS_DATA_IND_MSG_STRU));


    if (VOS_OK != TAF_XSMS_TransCSCHDataToDbm(pstDataIndMsg,&stDbm))
    {
        /* ����ʧ�� */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:TAF_XSMS_TransCSCHDataToDbm return fail");

        return;
    }

    if (VOS_TRUE != TAF_XSMS_CheckIsSmsDbm(&stDbm))
    {
        /* DBM������Ϣ����SMS */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:TAF_XSMS_CheckIsSmsDbm return false");

        return;
    }

    PS_MEM_CPY(&stDataInd, pstDataIndMsg, VOS_MSG_HEAD_LENGTH + sizeof(pstDataIndMsg->enMsgId) + sizeof(pstDataIndMsg->usOpId));
    stDataInd.ucLen  = stDbm.ucNumFields;
    PS_MEM_CPY(stDataInd.aucMsg, stDbm.aucData, stDataInd.ucLen);

    if (TAF_XSMS_TL_ACK_MSG == stDbm.aucData[0])
    {
        if (VOS_TRUE == pstDataIndMsg->enAckReqFlag)
        {
            TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
            TAF_XSMS_SndCasCschOrderMsg(0, pstDataIndMsg->enAckReqFlag, pstDataIndMsg->aucAckPara);
        }

        TAF_XSMS_MoFsmMainProc((MsgBlock*)&stDataInd);
    }
    else if (TAF_XSMS_TL_P2P_MSG == stDbm.aucData[0])
    {
        pstMtRec->enIsCasAckFlag    = pstDataIndMsg->enAckReqFlag;
        PS_MEM_CPY(pstMtRec->aucCasAckData, pstDataIndMsg->aucAckPara, 2);

        TAF_XSMS_MtFsmMainProc((MsgBlock*)&stDataInd);
    }
    else
    {
        /* �����MSG TYPE */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:Wrong Msg type");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_CasAbortProc
 ��������  : �յ�XCC��ABORT��Ϣ�ķַ�����
 �������  : pstMsg: XSMS�յ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_CasAbortProc(MsgBlock *pstMsg)
{
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT);
    TAF_XSMS_MtFsmMainProc(pstMsg);
    TAF_XSMS_MoFsmMainProc(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_CheckIsSmsDbm()
 ��������  : �ж��յ�DATA BURST MSG �ǲ���Э��涨��SMS����
             (Э��C.S0015 2.4.1.1.1.1�½�)
 �������  : pstDbm:DATA BURST MSG
 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_CheckIsSmsDbm(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm)
{
    /* Э�� C.S0015 2.4.1.1.1.1�½� */

    if ((TAF_XSMS_DBM_SMS_TYPE == pstDbm->ucBurstType)
     && (1 == pstDbm->ucMsgNum)
     && (1 == pstDbm->ucNumMsgs)
     && (VOS_NULL != pstDbm->ucNumFields))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PidMsgProc
 ��������  : TAF XSMS PID����Ϣ������
 �������  : pstMsg:����PID����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_PidMsgProc(MsgBlock* pstMsg)
{

    /* ��Ϣ�ķַ����� */
    switch (pstMsg->ulSenderPid)
    {
        case MAPS_PIH_PID:

            TAF_XSMS_PihMsgProc((TAF_XSMS_UIM_MSG_STRU *)pstMsg);

            break;

        case VOS_PID_TIMER:

            TAF_XSMS_TimeOutMsgProc((REL_TIMER_MSG*)pstMsg);

            break;

        case WUEPS_PID_AT:

            TAF_XSMS_AtMsgProc(pstMsg);

            break;

        case WUEPS_PID_USIM:

            TAF_XSMS_UsimmMsgProc((TAF_XSMS_UIM_MSG_STRU *)pstMsg);

            break;

        case UEPS_PID_XCC:

            TAF_XSMS_XccMsgProc(pstMsg);

            break;

        case UEPS_PID_1XCASM:

            TAF_XSMS_1xCasMsgProc(pstMsg);

            break;
        case WUEPS_PID_MMA:

            TAF_XSMS_MoFsmMainProc(pstMsg);

            break;

        case MAPS_STK_PID:
            TAF_XSMS_StkProc(pstMsg);
            break;

        case UEPS_PID_XPDS:
            TAF_XSMS_XpdsProc(pstMsg);
            break;

        case WUEPS_PID_TAF:
            TAF_XSMS_XcallProc(pstMsg);
            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_PidMsgProc : can not find pid");
            break;

    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_PidInit
 ��������  : XSMS PID��ʼ��������
 �������  : ip:��ʼ���׶�
 �������  : ��
 �� �� ֵ  : VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��2��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip)
{
    TAF_NVIM_1X_XSMS_CFG_STRU          stXsmsNv;

    switch (ip)
    {
        case VOS_IP_INITIAL:
            TAF_XSMS_ReqCtrlInfoClear();
            TAF_XSMS_InitCtrlInfoClear();

            if (VOS_OK != NV_Read(en_NV_Item_1X_SMS_CFG, &stXsmsNv, sizeof(TAF_NVIM_1X_XSMS_CFG_STRU)))
            {
                /* �й�����Ҫ����ר���ŵ��Ϸ����� */
                stXsmsNv.enXsmsChannelOption = TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN;
                stXsmsNv.ucResendMax         = TAF_XSMS_RESEND_TIMES_MAX;
                stXsmsNv.ucResendInterval    = TAF_XSMS_RESEND_INTERVAL_MAX;
                stXsmsNv.ucReconnectInterval = TAF_XSMS_RECONNECT_INTERVAL_MAX;
            }

            PS_MEM_CPY(&(TAF_XSMS_MoGetRecAddr()->stNvResend), &stXsmsNv, sizeof(stXsmsNv));
            PS_MEM_CPY(&(TAF_XSMS_MtGetRecAddr()->stResend), &stXsmsNv, sizeof(stXsmsNv));

            TAF_XSMS_MoGetRecAddr()->ucReplySeq   = VOS_NULL;

            TAF_XSMS_MoInitSendPool();

            TAF_XSMS_MoIdleInit();
            TAF_XSMS_MtIdleInit();
            TAF_XSMS_RegMoFsm();
            TAF_XSMS_RegMtFsm();
            break;

        case   VOS_IP_RESTART:

            /* ע�ᵽPIH��׼�����տ�״̬��Ϣ */
            PIH_RegUsimCardStatusIndMsg(UEPS_PID_XSMS);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : Taf_Xsms_EncodeCschOrderMsg
 ��������  : ��CSCH ��order msg ���б���
 �������  : ��
 �������  : pstCschDataReq
 �� �� ֵ  : VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��5��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeCschOrderMsg
(
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq
)
{
    c_r_csch_ORDM                                          *pstORDM;
    VOS_INT32                                               lEncodeRslt;
    CS0005E_Details                                         stCS0005Detail;
    c_r_csch_mini6                                          stEncodeData;
    TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32                 enErrType;

    /* ��ʼ���ڴ� */
    PS_MEM_SET(&stEncodeData, 0, sizeof(stEncodeData));

    /* ����ORDM�ṹ */
    SETPRESENT_c_r_csch_mini6_ORDM(&stEncodeData);

    pstORDM = stEncodeData.u.ORDM;

    if (VOS_NULL_PTR == pstORDM)
    {
        /* ��ֹ�����ָ���ٴ����ͷ� */
        stEncodeData.Present        = U_c_r_csch_mini6_NONE;

        return VOS_ERR;
    }

    /* �����ڴ� */
    SETPRESENT_c_R_Orders_parameters_p_R_Generic_Order(&stEncodeData.u.ORDM->order.parameters);

    if (VOS_NULL_PTR == stEncodeData.u.ORDM->order.parameters.u.p_R_Generic_Order)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeCschOrderMsg: allocate memory fail");

        stEncodeData.u.ORDM->order.parameters.Present = U_c_R_Orders_parameters_NONE;

        FREE_c_r_csch_mini6(&stEncodeData);

        return VOS_ERR;
    }

    /* �ȸ�ֵ order code ��orderq */
    pstORDM->order.ORDER                    = 0x10; /* CAS_1X_REV_ORDER_CODE_MS_ACKNOWLEDGMENT */
    pstORDM->order.parameters.u.p_R_Generic_Order->ORDQ = 0;

    TAF_XSMS_SetCS0005EDetailPara(&stCS0005Detail, 0x0002, 6, 0); /* 0x0002�� 6 ��ֵ��ҪCASȷ�� */

    /* ���� */
    lEncodeRslt = ENCODE_c_r_csch_mini6((char *)(pstCschDataReq->aucMsgData),
                                        0,
                                        &stEncodeData,
                                        &stCS0005Detail);

    if (lEncodeRslt < 0)
    {
        TAF_XSMS_ERROR_LOG("Taf_Xsms_EncodeCschOrderMsg: ENCODE_c_r_csch_mini6 fail");

        enErrType = TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_csch_mini6;

        TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_3RD_PARTY, (VOS_UINT8*)&enErrType, sizeof(TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32));

        FREE_c_r_csch_mini6(&stEncodeData);
        /* ��ӡ������� */
        return VOS_ERR;
    }

    pstCschDataReq->usMsgDataLen = (VOS_UINT16)lEncodeRslt;

    FREE_c_r_csch_mini6(&stEncodeData);

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_DealXccVoiceMailInd
 ��������  : ���յ���XCC waiting ind ���д���
 �������  : pstMsg-- XCC waiting ind
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��26��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_DealXccVoiceMailInd(MsgBlock* pstMsg)
{

    TAF_XSMS_MESSAGE_STRU               stDeliveryMsg;
    XCC_CSMS_MSG_WATING_IND_STRU       *pstMsgWaitInd;

    PS_MEM_SET(&stDeliveryMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstMsgWaitInd                       = (XCC_CSMS_MSG_WATING_IND_STRU*)pstMsg;

    stDeliveryMsg.ulTeleserviceID       = TAF_XSMS_VOICE_NOTIFICATION;
    stDeliveryMsg.bIsServicePresent     = VOS_FALSE;

    /* �̶���������12�ֽ� */
    stDeliveryMsg.ulBearerDataLen       = 12;

    /* ����Э��C.S0015 4.5.1 MSG_ID */
    stDeliveryMsg.aucBearerData[0]      = 0x00;
    stDeliveryMsg.aucBearerData[1]      = 0x03;
    stDeliveryMsg.aucBearerData[2]      = 0x10;
    stDeliveryMsg.aucBearerData[3]      = 0x00;
    stDeliveryMsg.aucBearerData[4]      = 0x00;

    /* ����Э��C.S0015 4.5.2 USER DATA */
    stDeliveryMsg.aucBearerData[5]      = 0x01;
    stDeliveryMsg.aucBearerData[6]      = 0x02;
    stDeliveryMsg.aucBearerData[7]      = 0x10;
    stDeliveryMsg.aucBearerData[8]      = 0x00;

    /* ����Э��C.S0015 4.5.12 MSG_COUNT */
    stDeliveryMsg.aucBearerData[9]      = 0x0b;
    stDeliveryMsg.aucBearerData[10]     = 0x01;

    /* ����Э��C.S0015 4.5.12 MSG_COUNT С�ڵ���99 */
    if (pstMsgWaitInd->ucMsgCnt > 99)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DealXccVoiceMailInd:ucMsgCnt > 99!");
        return;
    }
    else
    {
        /* MSG_COUNT ��ֵ */
        stDeliveryMsg.aucBearerData[11]   =  pstMsgWaitInd->ucMsgCnt;
    }

    TAF_XSMS_MsgDeliveryInd(&stDeliveryMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtApMemFullMsgProc
 ��������  : ���յ���XCC waiting ind ���д���
 �������  : pstMsg-- XCC waiting ind
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��26��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_AtApMemFullMsgProc(TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *pstApMemFullMsg)
{
    /* ����ȫ�ֱ��� */
    TAF_XSMS_SetApMemFullFlag(pstApMemFullMsg->enApMemFullFlag);

    /* �oAT�ظ�OK */
    (VOS_VOID)TAF_XSMS_SetAPFullCnf(pstApMemFullMsg->usClientId, pstApMemFullMsg->ucOpId, VOS_OK);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_HookSmsTlAck
 ��������  :
 �������  : pstMsg  ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��30��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
******************************************************************************/
VOS_VOID TAF_XSMS_HookSmsTlAck(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode
)
{
    TAF_XSMS_INT_TL_ACK_STRU            stTlAck;

    PS_MEM_SET(&stTlAck, 0, sizeof(TAF_XSMS_INT_TL_ACK_STRU));

    PS_MEM_CPY(&stTlAck.stCauseCode, pstCauseCode, sizeof(TAF_XSMS_CAUSE_CODE_STRU));


    TAF_XSMS_MsgHook(enMsgName, (VOS_UINT8*)(&stTlAck), sizeof(stTlAck));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_HookSmsContect
 ��������  : ��ȥ��ǰ�Ķ�������
 �������  : pstMsg  ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��30��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_HookSmsContect(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    VOS_UINT32                          ulReqSeq,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
)
{
    TAF_XSMS_INT_SMS_CONTENT_STRU       stXsmsContent;
    VOS_UINT16                          usUserDataStartByte = 0;
    VOS_UINT16                          usUserDataLen       = 0;

    PS_MEM_SET(&stXsmsContent, 0, sizeof(TAF_XSMS_INT_SMS_CONTENT_STRU));

    stXsmsContent.ulTeleserviceID       =  pstXsmsMsg->ulTeleserviceID;
    stXsmsContent.ulServiceCategory     =  pstXsmsMsg->ulServiceCategory;
    stXsmsContent.ulReplySeq            =  ulReqSeq;

    PS_MEM_CPY(&stXsmsContent.stAddr, &pstXsmsMsg->stAddr, sizeof(TAF_XSMS_ADDR_STRU));

    if ((TAF_XSMS_BEARER_DATA_MAX + 1) < pstXsmsMsg->ulBearerDataLen)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_HookSmsContect : pstXsmsMsg->ulBearerDataLen to large");
        return;
    }

    stXsmsContent.ulBearerDataLen       = pstXsmsMsg->ulBearerDataLen;

    PS_MEM_CPY(stXsmsContent.aucBearerData,
               pstXsmsMsg->aucBearerData,
               pstXsmsMsg->ulBearerDataLen);

    /* decode msg_Id and user data */
    TAF_XSMS_DecodeUserDataInBearerData(pstXsmsMsg->ulBearerDataLen,
                                        pstXsmsMsg->aucBearerData,
                                        &usUserDataStartByte,
                                        &usUserDataLen,
                                        &stXsmsContent.stUserData);

    TAF_XSMS_DecodeMsgId(pstXsmsMsg->ulBearerDataLen,
                         pstXsmsMsg->aucBearerData,
                         &stXsmsContent.stMsgId);

    TAF_XSMS_MsgHook(enMsgName, (VOS_UINT8*)(&stXsmsContent), sizeof(stXsmsContent));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_XcallProc
 ��������  : XCALL����Ϣ����
 �������  : pstMsg  ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��30��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_XcallProc(MsgBlock *pstMsg)
{
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU   *pstSendReq;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstSendReq = (XCALL_XSMS_KMC_MSG_SEND_REQ_STRU*)pstMsg;

    switch (pstSendReq->enMsgId)
    {
        case ID_XCALL_XSMS_KMC_MSG_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* �ж��Ƿ���Խ�XCALL��������ڷ��ͳ����� */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_XCALL))
                {
                    if (VOS_ERR == TAF_XSMS_EncodeXcallMsgBearDataByContext(pstSendReq->aucData,
                                                             pstSendReq->usDataLen,
                                                             &stXsmsMsg))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: encode user data fail");
                        TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_ENCODE_ERR, pstSendReq->usOpId);
                        return;
                    }

                    TAF_XSMS_GetKmcDefaultAddress(&stXsmsMsg.stAddr);

                    stXsmsMsg.ulTeleserviceID = TAF_XSMS_TELESERVICE_CDMACMT;

                    if (VOS_ERR == TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_XCALL,
                                                   VOS_TRUE,
                                                   pstSendReq->usOpId,
                                                   &stXsmsMsg))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: TAF_XSMS_InsertRecToMoSendPool fail");
                        TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_POOL_FULL, pstSendReq->usOpId);
                        return;
                    }
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: xcall req already in rec");
                    TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_POOL_FULL, pstSendReq->usOpId);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_ERR == ulRet)
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: handle err");
            }

            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: xcall msg id err");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_XpdsProc
 ��������  : Xpds����Ϣ����
 �������  : pstMsg  ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��14��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_XpdsProc(MsgBlock *pstMsg)
{
    TAF_XPDS_XSMS_SEND_REQ_STRU        *pstSendReq;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstSendReq = (TAF_XPDS_XSMS_SEND_REQ_STRU*)pstMsg;

    switch (pstSendReq->enMsgName)
    {
        case ID_XPDS_XSMS_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* �ж��Ƿ���Խ�Xpds��������ڷ��ͳ����� */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_XPDS))
                {
                    (VOS_VOID)TAF_XSMS_EncodeXsmsMsgBearDataByContext(pstSendReq->aucData,
                                                                      pstSendReq->usDataLen,
                                                                      &stXsmsMsg);
                    PS_MEM_CPY(&stXsmsMsg.stAddr,
                               &pstSendReq->stXsmsAddr,
                               sizeof(TAF_XSMS_ADDR_STRU));

                    stXsmsMsg.ulTeleserviceID = TAF_XSMS_TELESERVICE_AGPS_NI_SMS;

                    (VOS_VOID)TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_XPDS,
                                                             VOS_TRUE,
                                                             pstSendReq->usOpId,
                                                             &stXsmsMsg);
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: XPDS ALREAD  EXIST IN REC");
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_ERR == ulRet)
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: handle err");
            }

            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: xcall msg id err");
            break;
    }

    return;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



