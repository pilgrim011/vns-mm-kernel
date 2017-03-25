/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndInternalMsg.c
  �� �� ��   : ����
  ��    ��   : A00165503
  ��������   : 2010��5��9��
  ����޸�   :
  ��������   : APS����APS����Ϣ�Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��29��
    ��    ��   : A00165503
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafLog.h"
#include "Taf_Aps.h"
#include "TafApsCtx.h"
#include "TafApsSndInternalMsg.h"
#include "MnApsComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_INTERNALMSG_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterPdpDeactivateReq
 ��������  : �����ڲ�ȥ����PDP������Ϣ
 �������  : enCause                    - ȥ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndInterPdpDeactivateReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU   *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU));
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterDeactivateReq: Get internal message failed!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->enCause                     = enCause;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterDeactivateReq: Send internal message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndLocalPdpDeactivateInd
 ��������  : ���ͱ���ȥ����PDP������Ϣ
 �������  : ucSmCause                  - ȥ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndLocalPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU   *pstLocalMsg;

    /* ������Ϣ */
    pstLocalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU));
    if (VOS_NULL_PTR == pstLocalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndLocalPdpDeactivateInd: Get Local message failed!");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstLocalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstLocalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLocalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstLocalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLocalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstLocalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND;
    pstLocalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstLocalMsg->ucPdpId                     = ucPdpId;
    pstLocalMsg->enCause                     = enCause;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstLocalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndLocalPdpDeactivateInd: Send internal message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndLocalAllSecPdpDeactivateInd
 ��������  : ���ͱ������д�PDPȥ����ָʾ
 �������  : VOS_UINT8 ucPdpId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��29��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_VOID TAF_APS_SndLocalAllSecPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT8                           i;

    if (APS_PDP_ACT_PRI == TAF_APS_GetPdpEntActType(ucPdpId))
    {
        for (i = 0; i < TAF_APS_MAX_PDPID; i++)
        {
            if ((TAF_APS_GetPdpEntNsapi(ucPdpId) == TAF_APS_GetPdpEntLinkedNsapi(i))
             && (APS_PDP_ACT_SEC == TAF_APS_GetPdpEntActType(i))
             && (VOS_TRUE == TAF_APS_GetPdpEntUsedFlg(i)))
            {
                TAF_APS_SndLocalPdpDeactivateInd(i, enCause);
            }
        }
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterAttachBearerActivateInd
 ��������  : ����ע����ؼ���ָʾ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndInterAttachBearerActivateInd(VOS_VOID)
{
    TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU    *pstInternalMsg = VOS_NULL_PTR;

    /* �����ڲ���Ϣ */
    pstInternalMsg  = (TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU *)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Get internal message failed!");
        return;
    }

    /* ��д��Ϣͷ */
    TAF_APS_CFG_INTER_MSG_HDR(pstInternalMsg, (sizeof(TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    pstInternalMsg->enMsgId = ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterAttachBearerActivateInd: Send message failed.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterFsmEntryMsg
 ��������  : ����״̬�������Ϣ���ڲ���Ϣ����
 �������  : pstEntryMsg --- ״̬�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndInterFsmEntryMsg(TAF_APS_ENTRY_MSG_STRU *pstEntryMsg)
{
    VOS_VOID                           *pstInternalMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    pstMsgHeader = (MSG_HEADER_STRU *)(&pstEntryMsg->aucEntryMsgBuffer[0]);
    ulMsgLength  = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    pstInternalMsg  = (VOS_VOID *)TAF_APS_GetIntMsgSendBuf(ulMsgLength);
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Get internal message failed!");
        return;
    }

    /* ������Ϣ���� */
    PS_MEM_CPY(pstInternalMsg, (VOS_VOID *)pstMsgHeader, ulMsgLength);

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterFsmEntryMsg: Send internal message failed.");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndEnterDormantInd
 ��������  : �����ڲ�ID_MSG_TAF_PS_DISC_SO_REQ��Ϣ
 �������  : VOS_UINT8                           ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndEnterDormantInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstDormantInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstDormantInd  = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU));

    if (VOS_NULL_PTR == pstDormantInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEnterDormantInd: ALLOC MEMERY FAIL!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstDormantInd,
               0x00,
               sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU));

    /* ��д��Ϣͷ */
    pstDormantInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstDormantInd->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstDormantInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDormantInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstDormantInd->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND;
    pstDormantInd->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_ENTER_DORMANT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDormantInd->ucPdpId                     = ucPdpId;

    /* �����ڲ���Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstDormantInd);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterEndCdmaCallReq
 ��������  : DORMANT״̬���û�ȥ���������½�����ɣ��ٷ����ڲ�ȥ����
 �������  : TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8     enEndScene,
             TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8    enEndReason,
             VOS_UINT8                                   ucPdpId,
             VOS_UINT32                                  ulRemainTmrLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterEndCdmaCallReq(
    TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8     enEndScene,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8    enEndReason,
    VOS_UINT8                                   ucPdpId,
    VOS_UINT32                                  ulRemainTmrLen
)
{
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU   *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEndCdmaCallReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_END_CDMA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->ulRemainTmrLen              = ulRemainTmrLen;
    pstInternalMsg->enEndScene                  = enEndScene;
    pstInternalMsg->enEndReason                 = enEndReason;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEndCdmaCallReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterEpdszidReOrigReq
 ��������  : Send ID_MSG_TAF_PS_EPDSZID_REORIG_REQ msg
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterEpdszidReOrigReq(VOS_VOID)
{
    TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU    *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndHtExpiredInd
 ��������  : ����HT��ʱ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��8��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterHtExpiredInd(VOS_VOID)
{
    TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU  *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_HT_EXPIRED_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndEpdszidReOrigReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndHaiChangeInd
 ��������  : Send Internal ID_MSG_TAF_PS_HAI_CHANGE_IND Msg
 �������  : VOS_UINT8                           ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndHaiChangeInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_HAI_CHANGE_IND_STRU         *pstHaiChangeInd;

    /* ������Ϣ */
    pstHaiChangeInd  = (TAF_PS_HAI_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(TAF_PS_HAI_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstHaiChangeInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHaiChangeInd: ALLOC MEMERY FAIL!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstHaiChangeInd,
               0x00,
               sizeof(TAF_PS_HAI_CHANGE_IND_STRU));

    /* ��д��Ϣͷ */
    pstHaiChangeInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstHaiChangeInd->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstHaiChangeInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstHaiChangeInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstHaiChangeInd->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_HAI_CHANGE_IND;
    pstHaiChangeInd->stMsgHeader.ulLength        = sizeof(TAF_PS_HAI_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstHaiChangeInd->ucPdpId                     = ucPdpId;

    /* �����ڲ���Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstHaiChangeInd);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndInter1XToHrpdHandOffReq
 ��������  :
 �������  : VOS_UINT8                                   ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInter1XToHrpdHandOffReq(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU         *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInter1XToHrpdHandOffReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInter1XToHrpdHandOffReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterHrpdTo1XHandOffReq
 ��������  :
 �������  : VOS_UINT8                                   ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterHrpdTo1XHandOffReq(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU         *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterHrpdTo1XHandOffReq: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterHrpdTo1XHandOffReq: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterServiceStatusChangeInd
 ��������  : �յ�MMA��MMC��SERVICE_STATUS_IND��Ϣ��ת���ڲ���Ϣ
 �������  : TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
             TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType,
             VOS_UINT32                          ulPsSimRegStatus,
             VOS_UINT8                           ucPdpId,
             VOS_UINT8                           ucIsNewSession
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterServiceStatusChangeInd(
    VOS_UINT8                           ucPdpId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType,
    VOS_UINT32                          ulPsSimRegStatus,
    VOS_UINT8                           ucIsNewSession,
    TAF_APS_INTER_SERVICE_TYPE_ENUM_UINT8         ucServiceType
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU     *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterServiceStatusChangeInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstInternalMsg->ucPdpId                     = ucPdpId;
    pstInternalMsg->ucIsNewSession              = ucIsNewSession;
    pstInternalMsg->enRatType                   = enRatType;
    pstInternalMsg->enLastRatType               = enLastRatType;
    pstInternalMsg->ulPsSimRegStatus            = ulPsSimRegStatus;
    pstInternalMsg->ucServiceType               = ucServiceType;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterServiceStatusChangeInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterPsServiceModeModifyInd
 ��������  : ����ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND
 �������  : TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8 enPsOptionType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterPsServiceModeModifyInd(
    TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8 enPsOptionType
)
{
    TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU     *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU*)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterPsServiceModeModifyInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstInternalMsg->enPsOptionType              = enPsOptionType;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterPsServiceModeModifyInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndInterEnd1xServiceInDormantInd
 ��������  : ��DORMANT״̬�����ݷ���ģʽ�л�ʱ��ȥ����1X
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterEnd1xServiceInDormantInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU   *pstInternalMsg;

    /* ������Ϣ */
    pstInternalMsg  = (TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU *)TAF_APS_GetIntMsgSendBuf(
                            sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEnd1xServiceInDormantInd: Get internal message failed!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_UINT8 *)pstInternalMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstInternalMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pstInternalMsg->stMsgHeader.ulMsgName       = ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND;
    pstInternalMsg->stMsgHeader.ulLength        = sizeof(TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->ucPdpId                     = ucPdpId;

    /* �����ڲ���Ϣ */
    if (VOS_OK != TAF_APS_SndInternalMsg(pstInternalMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndInterEnd1xServiceInDormantInd: Send internal message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

