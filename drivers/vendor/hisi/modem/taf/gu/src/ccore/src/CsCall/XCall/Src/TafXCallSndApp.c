/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallSndApp.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF X CALL���͸�APP����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallSndApp.h"
#include "AtMnInterface.h"
#include "NasStkInterface.h"
#include "TafXCallCtx.h"
#include "TafSdcCtx.h"

#include "MmaAppLocal.h"

#include "TafXCallCtx.h"
#include "TafAppCall.h"
#include "Taf_Tafm_Remote.h"
#include "MnComm.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_APP_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCsEvtToAt
 ��������  : �ϱ�MN_CALL_EVT_CALL_ORIG_CNF��Ϣ��
 �������  : VOS_UINT32                          ulEvtId
             VOS_UINT16                          usClientId
             MN_CALL_INFO_STRU                  *pstCsCallInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCsEvtToAt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usLength,
    VOS_VOID                           *pData
)
{
    MN_AT_IND_EVT_STRU                 *pstMsg     = VOS_NULL_PTR;
    TAF_UINT32                          ulTmpAddr;
    TAF_UINT16                          usEventTypeLen;
    TAF_UINT16                          usMsgLength;

    usEventTypeLen                     = sizeof(ulEvtId);

    usMsgLength = (VOS_UINT16)((sizeof(MN_AT_IND_EVT_STRU) + usLength) - 4 + usEventTypeLen);

    /* �����ڴ� */
    pstMsg = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, usMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
         return;
    }

    /* �������ػ����ʵ��������pMsg->aucValue;*/
    pstMsg->ulReceiverPid              = WUEPS_PID_AT;
    pstMsg->usMsgName                  = (VOS_UINT16)MN_CALLBACK_CS_CALL;
    pstMsg->clientId                   = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);

    /* ��д����Ϣ���� */

    pstMsg->usLen                      = usMsgLength - VOS_MSG_HEAD_LENGTH;

    ulTmpAddr = (VOS_UINT32)pstMsg->aucContent;
    PS_MEM_CPY(pstMsg->aucContent, &ulEvtId, usEventTypeLen);
    PS_MEM_CPY((VOS_VOID *)(ulTmpAddr + usEventTypeLen),
               pData,
               usLength);

    /*������Ϣ��AT;*/
    PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCsEvtToStk
 ��������  : �ϱ�MN_CALL_EVT_CALL_ORIG_CNF��Ϣ��STK
 �������  : VOS_UINT32                          ulEvtId
             VOS_UINT32                          ulModuleId
             MN_CALL_INFO_STRU                  *pstCallInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCsEvtToStk(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulModuleId,
    MN_CALL_INFO_STRU                  *pstCallInfo
)
{
    MN_APP_CS_CALLINFO_MSG_STRU        *pstMsg;

    /* Ϊ�ظ�STK����ϢTAF_STK_CS_CALLINFO_EVENT_IND�����ڴ� */
    pstMsg   = (MN_APP_CS_CALLINFO_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                        sizeof(MN_APP_CS_CALLINFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid   = ulModuleId;
    pstMsg->ulMsgId         = TAF_STK_CS_CALLINFO_EVENT_IND;
    pstMsg->enEventType     = ulEvtId;
    pstMsg->ulLength        = sizeof(MN_APP_CS_CALLINFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY(&(pstMsg->stCsCallInfo), pstCallInfo, sizeof(MN_CALL_INFO_STRU));

    /*������Ϣ��STK;*/
    PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallOrigCnf
 ��������  : �ϱ�MN_CALL_EVT_CALL_ORIG_CNF��Ϣ
 �������  : ulResult       - ���д�����
             ucCallId       - call Id
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��5��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallOrigCnf(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientid,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    MN_CALL_INFO_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId                 = usClientid;
    stCallInfo.opId                     = 0;

    /* ����ʱ���ϲ�ֻ��ע�����Ƿ�ɹ� */
    stCallInfo.enCause                  = enCause;
    stCallInfo.enCallType               = enCallType;
    stCallInfo.enVoiceDomain            = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ����MN_CALL_EVT_CALL_ORIG_CNF��Ϣ */
    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_CALL_ORIG_CNF,
                               usClientid,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_CALL_ORIG_CNF,
                                ulModuleId,
                                &stCallInfo);
    }

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndSupsCmdCnf
 ��������  : �ϱ�MN_CALL_EVT_SUPS_CMD_CNF(SUPS����ʱ��Ӧ)
 �������  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndSupsCmdCnf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = usClientId;
    stCallInfo.opId          = ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCause       = enCause;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_SUPS_CMD_CNF,
                               usClientId,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_SUPS_CMD_CNF,
                                ulModuleId,
                                &stCallInfo);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndSupsResult
 ��������  : �ϱ�MN_CALL_EVT_SS_CMD_RSLT(SUPS�����ս��)
 �������  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             MN_CALL_SS_RESULT_ENUM_U8           enSsResult
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��16��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndSupsResult(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = usClientId;
    stCallInfo.opId          = ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enSsResult    = enSsResult;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    if (WUEPS_PID_AT == ulModuleId)
    {
        TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_SS_CMD_RSLT,
                               usClientId,
                               sizeof(MN_CALL_INFO_STRU),
                               &stCallInfo);
    }
    else
    {
        TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_SS_CMD_RSLT,
                                ulModuleId,
                                &stCallInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallIncomingInd
 ��������  : ����MN_CALL_EVT_INCOMING�¼�
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallIncomingInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCallState   = pstCallEntity->enCallState;

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_INCOMING,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_INCOMING,
                            MAPS_STK_PID,
                            &stCallInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallOrigInd
 ��������  : ����MN_CALL_EVT_ORIG�¼�
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallOrigInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = pstCallEntity->stClientInfo.usClientId;
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_ORIG,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_ORIG,
                            MAPS_STK_PID,
                            &stCallInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallConnectInd
 ��������  : ����MN_CALL_EVT_CONNECT�¼�
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallConnectInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCallDir     = pstCallEntity->enCallDir;
    PS_MEM_CPY(&(stCallInfo.stConnectNumber), &(pstCallEntity->stConnectNumber), sizeof(MN_CALL_BCD_NUM_STRU));

    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);


    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_CONNECT,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_CONNECT,
                            MAPS_STK_PID,
                            &stCallInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallReleaseInd
 ��������  : ����MN_CALL_EVT_RELEASED�¼�
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallReleaseInd(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(ucCallId);

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId      = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    stCallInfo.opId          = pstCallEntity->stClientInfo.ucOpId;
    stCallInfo.callId        = ucCallId;
    stCallInfo.enCallType    = pstCallEntity->enCallType;
    stCallInfo.enCause       = pstCallEntity->enCause;
    stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP2;



    /* ���������ϱ����ȫ�ֱ�����ֵ */
    pstCurcRptCtrl                 = TAF_SDC_GetCurcRptCtrl();
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
               pstCurcRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    pstUnsolicitedRptCtrl          = TAF_SDC_GetUnsolicitedRptCtrl();
    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
               pstUnsolicitedRptCtrl->aucRptCfg,
               MN_CALL_RPT_CFG_MAX_SIZE);

    /* release �㲥�ϱ� */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_RELEASED,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    TAF_XCALL_SndCsEvtToStk(MN_CALL_EVT_RELEASED,
                            MAPS_STK_PID,
                            &stCallInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallAllReleaseInd
 ��������  : ����MN_CALL_EVT_ALL_RELEASED�¼�
 �������  : VOS_UINT32                          ulModuleId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��17��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallAllReleaseInd(
    VOS_UINT32                          ulModuleId
)
{
    MN_CALL_INFO_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    /* Ŀǰֻ��AT�������Ϣ���������ulModuleIdԤ�� */
    TAF_XCALL_SndCsEvtToAt(MN_CALL_EVT_ALL_RELEASED,
                           MN_CLIENT_ALL,
                           sizeof(MN_CALL_INFO_STRU),
                           &stCallInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndBurstDTMFCnf
 ��������  : �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_CNF
 �������  : VOS_UINT16                                  usClientId,
             VOS_UINT8                                   ucOpId,
             TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 enResult,
             VOS_UINT8                                   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndBurstDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 enResult,
    VOS_UINT8                                   ucCallId
)
{
    TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU                   stSendBurstDTMFCnf;

    PS_MEM_SET(&stSendBurstDTMFCnf, 0 ,sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFCnf.enResult   = enResult;
    stSendBurstDTMFCnf.usClientId = usClientId;
    stSendBurstDTMFCnf.ucOpId     = ucOpId;
    stSendBurstDTMFCnf.ucCallId   = ucCallId;

    /* �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_BURST_DTMF_CNF,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_CNF_STRU),
                          &stSendBurstDTMFCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndBurstDTMFRslt
 ��������  : �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_RSLT
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndBurstDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU   stSendBurstDTMFRslt;

    PS_MEM_SET(&stSendBurstDTMFRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFRslt.usClientId  = usClientId;
    stSendBurstDTMFRslt.ucOpId      = ucOpId;
    stSendBurstDTMFRslt.ucResult    = ucResult;

    /* �ϱ�TAF_CALL_EVT_SEND_BURST_DTMF_RSLT�� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_BURST_DTMF_RSLT_STRU),
                           &stSendBurstDTMFRslt);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndFlashRslt
 ��������  : �ϱ�TAF_CALL_EVT_SEND_FLASH_RSLT
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucResult
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��10��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_VOID TAF_XCALL_SndFlashRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_FLASH_RSLT_STRU   stFlashRslt;

    PS_MEM_SET(&stFlashRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_FLASH_RSLT_STRU));

    /* ��д��Ϣ */
    stFlashRslt.ucResult   = ucResult;
    stFlashRslt.usClientId = usClientId;
    stFlashRslt.ucOpId     = ucOpId;

    /* �ϱ�TAF_CALL_EVT_SEND_FLASH_RSLT�¼� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_FLASH_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_FLASH_RSLT_STRU),
                           &stFlashRslt);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCalledNumInfoInd
 ��������  : �ϱ�TAF_CALL_EVT_CALLED_NUM_INFO_IND
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��9��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCalledNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU                   stCalledNum;

    if (VOS_TRUE != pstInfoRecInd->bitOpCalledNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CALLED_NUM_INFO_IND_STRU */
    stCalledNum.usClientId = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCalledNum.ucOpId     = MMA_OP_ID_INTERNAL;

    stCalledNum.ucCallId   = pstInfoRecInd->ucCallId;
    stCalledNum.enNumType  = pstInfoRecInd->stCalledNumInfo.enNumType;
    stCalledNum.enNumPlan  = pstInfoRecInd->stCalledNumInfo.enNumPlan;
    stCalledNum.ucDigitNum = pstInfoRecInd->stCalledNumInfo.ucDigitNum;
    PS_MEM_CPY(stCalledNum.aucDigit,
               pstInfoRecInd->stCalledNumInfo.aucDigit,
               pstInfoRecInd->stCalledNumInfo.ucDigitNum);



    /* ����TAF_CALL_EVT_CALLED_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CALLED_NUM_INFO_IND,
                           stCalledNum.usClientId,
                           sizeof(XCC_XCALL_CONNECTED_NUM_INFO_STRU),
                           &stCalledNum);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallingPratNumInfoInd
 ��������  : ����TAF_CALL_EVT_CALLING_NUM_INFO_IND��Ϣ
 �������  : VOS_UINT8                               ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallingPratNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU  stCallingNum;

    if (VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU */
    stCallingNum.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCallingNum.ucOpId      = MMA_OP_ID_INTERNAL;

    stCallingNum.ucCallId    = pstInfoRecInd->ucCallId;
    stCallingNum.ucPi        = pstInfoRecInd->stCallingNumInfo.ucPi;
    stCallingNum.ucSi        = pstInfoRecInd->stCallingNumInfo.ucSi;
    stCallingNum.enNumType   = pstInfoRecInd->stCallingNumInfo.enNumType;
    stCallingNum.enNumPlan   = pstInfoRecInd->stCallingNumInfo.enNumPlan;
    stCallingNum.ucDigitNum  = pstInfoRecInd->stCallingNumInfo.ucDigitNum;
    PS_MEM_CPY(stCallingNum.aucDigit,
               pstInfoRecInd->stCallingNumInfo.aucDigit,
               pstInfoRecInd->stCallingNumInfo.ucDigitNum);



    /* ����TAF_CALL_EVT_CALLING_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CALLING_NUM_INFO_IND,
                           stCallingNum.usClientId,
                           sizeof(TAF_CALL_EVT_CALLING_NUM_INFO_IND_STRU),
                           &stCallingNum);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndConnNumInfoInd
 ��������  : ����TAF_CALL_EVT_CONN_NUM_INFO_IND��Ϣ
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndConnNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU   stConnNum;
    if (VOS_TRUE != pstInfoRecInd->bitOpConnNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU */
    stConnNum.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stConnNum.ucOpId      = MMA_OP_ID_INTERNAL;

    stConnNum.ucCallId    = pstInfoRecInd->ucCallId;
    stConnNum.enNumType   = pstInfoRecInd->stConnNumInfo.enNumType;
    stConnNum.enNumPlan   = pstInfoRecInd->stConnNumInfo.enNumPlan;
    stConnNum.ucPi        = pstInfoRecInd->stConnNumInfo.ucPi;
    stConnNum.ucSi        = pstInfoRecInd->stConnNumInfo.ucSi;
    stConnNum.ucDigitNum  = pstInfoRecInd->stConnNumInfo.ucDigitNum;
    PS_MEM_CPY(stConnNum.aucDigit,
               pstInfoRecInd->stConnNumInfo.aucDigit,
               pstInfoRecInd->stConnNumInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_CONN_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CONN_NUM_INFO_IND,
                           stConnNum.usClientId,
                           sizeof(TAF_CALL_EVT_CONN_NUM_INFO_IND_STRU),
                           &stConnNum);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndRedirNumInfoInd
 ��������  : ����TAF_CALL_EVT_REDIR_NUM_INFO_IND��Ϣ
 �������  : VOS_UINT8                           ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndRedirNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU       stRedirNum;
    if (VOS_TRUE != pstInfoRecInd->bitOpRedirNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU */
    stRedirNum.usClientId       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stRedirNum.ucOpId           = MMA_OP_ID_INTERNAL;

    stRedirNum.ucCallId         = pstInfoRecInd->ucCallId;
    stRedirNum.bitOpPi          = pstInfoRecInd->stRedirNumInfo.bitOpPi;
    stRedirNum.bitOpSi          = pstInfoRecInd->stRedirNumInfo.bitOpSi;
    stRedirNum.bitOpRedirReason = pstInfoRecInd->stRedirNumInfo.bitOpRedirReason;
    stRedirNum.enNumType        = pstInfoRecInd->stRedirNumInfo.enNumType;
    stRedirNum.enNumPlan        = pstInfoRecInd->stRedirNumInfo.enNumPlan;
    stRedirNum.ucPi             = pstInfoRecInd->stRedirNumInfo.ucPi;
    stRedirNum.ucSi             = pstInfoRecInd->stRedirNumInfo.ucSi;
    stRedirNum.ucRedirReason    = pstInfoRecInd->stRedirNumInfo.enRedirReason;
    stRedirNum.ucDigitNum       = pstInfoRecInd->stRedirNumInfo.ucDigitNum;
    PS_MEM_CPY(stRedirNum.aucDigitNum,
               pstInfoRecInd->stRedirNumInfo.aucDigit,
               pstInfoRecInd->stRedirNumInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_REDIR_NUM_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_REDIR_NUM_INFO_IND,
                           stRedirNum.usClientId,
                           sizeof(TAF_CALL_EVT_REDIR_NUM_INFO_IND_STRU),
                           &stRedirNum);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndDisplayInfoInd
 ��������  : ����TAF_CALL_EVT_DISPLAY_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_DISPLAY_INFO_IND_STRU                      stDisPlayInfo;
    if (VOS_TRUE != pstInfoRecInd->bitOpDisplayInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_DISPLAY_INFO_IND_STRU */
    stDisPlayInfo.usClientId  = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stDisPlayInfo.ucOpId      = MMA_OP_ID_INTERNAL;

    stDisPlayInfo.ucCallId   = pstInfoRecInd->ucCallId;
    stDisPlayInfo.ucDigitNum = pstInfoRecInd->stDisplayInfo.ucDigitNum;
    PS_MEM_CPY(stDisPlayInfo.aucDigit,
               pstInfoRecInd->stDisplayInfo.aucDigit,
               pstInfoRecInd->stDisplayInfo.ucDigitNum);

    /* ����TAF_CALL_EVT_DISPLAY_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_DISPLAY_INFO_IND,
                           stDisPlayInfo.usClientId,
                           sizeof(TAF_CALL_EVT_DISPLAY_INFO_IND_STRU),
                           &stDisPlayInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndExtDisplayInfoInd
 ��������  : ����TAF_CALL_EVT_EXT_DISPLAY_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndExtDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU                 *pstExtDisPlayInfo = VOS_NULL_PTR;

    VOS_UINT32                                              ulLoop;

    if (VOS_TRUE != pstInfoRecInd->bitOpExtDisplay)
    {
        return;
    }

    pstExtDisPlayInfo = (TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                        sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstExtDisPlayInfo)
    {
        return;
    }

    PS_MEM_SET(pstExtDisPlayInfo, 0, sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU));

    /* ���TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU */
    pstExtDisPlayInfo->usClientId        = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstExtDisPlayInfo->ucOpId            = MMA_OP_ID_INTERNAL;

    pstExtDisPlayInfo->ucCallId          = pstInfoRecInd->ucCallId;
    pstExtDisPlayInfo->ucDisplayType     = pstInfoRecInd->stExtDisplayInfo.enDisplayType;
    pstExtDisPlayInfo->ucInfoRecsDataNum = pstInfoRecInd->stExtDisplayInfo.ucNumExtDispData;
    pstExtDisPlayInfo->ucExtDispInd      = pstInfoRecInd->stExtDisplayInfo.ucExtDispInd;
    for (ulLoop = 0; ulLoop < pstExtDisPlayInfo->ucInfoRecsDataNum; ulLoop++)
    {
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDispalyTag
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].enDisplayTag;
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDispalyLen
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDispalyLen;
        pstExtDisPlayInfo->aucInfoRecsData[ulLoop].ucDigitNum
                         = pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDigitNum;
        PS_MEM_CPY(pstExtDisPlayInfo->aucInfoRecsData[ulLoop].aucDigit,
                   pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].aucDigit,
                   pstInfoRecInd->stExtDisplayInfo.astExtDispData[ulLoop].ucDigitNum);
    }

    /* ����TAF_CALL_EVT_EXT_DISPLAY_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND,
                           pstExtDisPlayInfo->usClientId,
                           sizeof(TAF_CALL_EVT_EXT_DISPLAY_INFO_IND_STRU),
                           pstExtDisPlayInfo);


    PS_MEM_FREE(WUEPS_PID_TAF, pstExtDisPlayInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndLineCtrlInfoInd
 ��������  : ����TAF_CALL_EVT_LINE_CTRL_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndLineCtrlInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU                    stLineCtrlInfo;
    if (VOS_TRUE != pstInfoRecInd->bitOpLineCtrlInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU */
    stLineCtrlInfo.usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stLineCtrlInfo.ucOpId                    = MMA_OP_ID_INTERNAL;

    stLineCtrlInfo.ucCallId                  = pstInfoRecInd->ucCallId;
    stLineCtrlInfo.ucPolarityIncluded        = pstInfoRecInd->stLineCtrlInfo.ucPolarityIncluded;
    stLineCtrlInfo.ucToggleModePresent       = pstInfoRecInd->stLineCtrlInfo.ucToggleModePresent;
    stLineCtrlInfo.ucToggleMode              = pstInfoRecInd->stLineCtrlInfo.ucToggleMode;
    stLineCtrlInfo.ucReversePolarityPresent  = pstInfoRecInd->stLineCtrlInfo.ucReversePolarityPresent;
    stLineCtrlInfo.ucReversePolarity         = pstInfoRecInd->stLineCtrlInfo.ucReversePolarity;
    stLineCtrlInfo.ucPowerDenialTime         = pstInfoRecInd->stLineCtrlInfo.ucPowerDenialTime;

    /* ����TAF_CALL_EVT_LINE_CTRL_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_LINE_CTRL_INFO_IND,
                           stLineCtrlInfo.usClientId,
                           sizeof(TAF_CALL_EVT_LINE_CTRL_INFO_IND_STRU),
                           &stLineCtrlInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndSignalInfoInd
 ��������  : ����TAF_CALL_EVT_SIGNAL_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_SIGNAL_INFO_IND_STRU   stSignalInfo;
    if (VOS_TRUE != pstInfoRecInd->bitOpSignalInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_SIGNAL_INFO_IND_STRU */
    stSignalInfo.usClientId   = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stSignalInfo.ucOpId       = MMA_OP_ID_INTERNAL;

    stSignalInfo.ucCallId     = pstInfoRecInd->ucCallId;
    stSignalInfo.ucSignalType = pstInfoRecInd->stSignalInfo.ucSignalType;
    stSignalInfo.ucAlertPitch = pstInfoRecInd->stSignalInfo.ucAlertPitch;
    stSignalInfo.ucSignal     = pstInfoRecInd->stSignalInfo.ucSignal;

    /* ����TAF_CALL_EVT_SIGNAL_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SIGNAL_INFO_IND,
                           stSignalInfo.usClientId,
                           sizeof(TAF_CALL_EVT_SIGNAL_INFO_IND_STRU),
                           &stSignalInfo);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCCWACInfoInd
 ��������  : ����TAF_CALL_EVT_CCWAC_INFO_IND��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �����ɺ���
  2.��    ��   : 2015��1��17��
    ��    ��   : y00307564
    �޸�����   : ����PI, SI�ֶ�
  3.��    ��   : 2015��02��15��
    ��    ��   : y00307564
    �޸�����   : �޸�Ϊ�㲥ͨ�������ϱ�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCCWACInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_CALL_EVT_CCWAC_INFO_IND_STRU    stCCWAC;
    if (VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo)
    {
        return;
    }

    /* ���TAF_CALL_EVT_CCWAC_INFO_IND_STRU */
    stCCWAC.usClientId = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    stCCWAC.ucOpId     = MMA_OP_ID_INTERNAL;

    stCCWAC.ucCallId   = pstInfoRecInd->ucCallId;
    stCCWAC.enNumType  = pstInfoRecInd->stCallingNumInfo.enNumType;
    stCCWAC.enNumPlan  = pstInfoRecInd->stCallingNumInfo.enNumPlan;
    stCCWAC.ucDigitNum = pstInfoRecInd->stCallingNumInfo.ucDigitNum;

    stCCWAC.ucPi       = pstInfoRecInd->stCallingNumInfo.ucPi;
    stCCWAC.ucSi       = pstInfoRecInd->stCallingNumInfo.ucSi;

    PS_MEM_CPY(stCCWAC.aucDigit,
               pstInfoRecInd->stCallingNumInfo.aucDigit,
               pstInfoRecInd->stCallingNumInfo.ucDigitNum);

    if (VOS_TRUE == pstInfoRecInd->bitOpSignalInfo)
    {
        stCCWAC.ucSignalIsPresent = VOS_TRUE;
        stCCWAC.ucAlertPitch      = pstInfoRecInd->stSignalInfo.ucAlertPitch;
        stCCWAC.ucSignalType      = pstInfoRecInd->stSignalInfo.ucSignalType;
        stCCWAC.ucSignal          = pstInfoRecInd->stSignalInfo.ucSignal;
    }
    else
    {
        stCCWAC.ucSignalIsPresent = VOS_FALSE;
    }

    /* ����TAF_CALL_EVT_CCWAC_INFO_IND��Ϣ */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_CCWAC_INFO_IND,
                           stCCWAC.usClientId ,
                           sizeof(TAF_CALL_EVT_CCWAC_INFO_IND_STRU),
                           &stCCWAC);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndCallingNumSignalInfoInd
 ��������  : ����calling num signal or both
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��13��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �����ɺ���
  2.��    ��   : 2016��1��16��
    ��    ��   : t00323010
    �޸�����   : DTS2016011504052����ת���ϱ�������Я����Чcall id, �����߼�����
_____________________________________________________________________________
|call state      |    active                    |         inactive           |
|________________|______________________________|____________________________|
|bitOpcallingnum |     0        |       1       |       0     |     1        |
|________________|______________|_______________|_____________|______________|
|           |0   |   signal     |    ccwac      |      NA     |calling num   |
|BitOpSignal|____|______________|_______________|_____________|______________|
|           |1   |   signal     |    ccwac      |   signal    |    both      |
|___________|____|______________|_______________|_____________|______________|

*****************************************************************************/
VOS_VOID TAF_XCALL_SndCallingNumSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    VOS_UINT32                          ulRslt;

    if ((VOS_TRUE != pstInfoRecInd->bitOpCallingNumInfo) && (VOS_TRUE != pstInfoRecInd->bitOpSignalInfo))
    {
        return;
    }

    /* ���callIdΪ��Чֵ, ֱ��������ѯcallstate�ᵼ���������Խ��, ���ؽ�����ɿ� */
    ulRslt = TAF_XCALL_IsAvailCallId(pstInfoRecInd->ucCallId);

    if (VOS_TRUE == ulRslt)
    {
        enCallState = TAF_XCALL_GetCallState(pstInfoRecInd->ucCallId);
    }
    else
    {
        enCallState = MN_CALL_S_BUTT;
    }

    if (MN_CALL_S_ACTIVE == enCallState)
    {
        /* ����active̬,�ɱ��еĶ�Ӧ��ϵ��֪��������calling numberֱ�ӷ���ccwac������������signal */
        if (VOS_TRUE == pstInfoRecInd->bitOpCallingNumInfo)
        {
            TAF_XCALL_SndCCWACInfoInd(pstInfoRecInd);
        }
        else
        {
            TAF_XCALL_SndSignalInfoInd(pstInfoRecInd);
        }
    }
    else
    {
        /* ����inactive̬,�ɱ��еĶ�Ӧ��ϵ��֪,������calling number or signal��ֱ�ӷ��ͼ��� */
        TAF_XCALL_SndCallingPratNumInfoInd(pstInfoRecInd);

        TAF_XCALL_SndSignalInfoInd(pstInfoRecInd);

    }

}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndXlemaCnf
 ��������  : ����MN_CALL_EVT_XLEMA_CNF��Ϣ
 �������  : XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��11��
    ��    ��   : y00307564
    �޸�����   : 1X SS Project �޸�

*****************************************************************************/
VOS_VOID TAF_XCALL_SndXlemaCnf(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{

    /* ����MN_CALL_EVT_XLEMA_CNF��Ϣ */
    TAF_XCALL_SndCsEvtToAt(pstEccNumInfo->enEvent,
                           pstEccNumInfo->usClientId,
                           sizeof(MN_CALL_ECC_NUM_INFO_STRU)-sizeof(pstEccNumInfo->enEvent),
                           &pstEccNumInfo->usClientId);

    return;

}




/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndContDTMFCnf
 ��������  : �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_CNF
 �������  : VOS_UINT16                                  usClientId,
             VOS_UINT8                                   ucOpId,
             TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
             VOS_UINT8                                   ucCallId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndContDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
    VOS_UINT8                                   ucCallId
)
{
    TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU                    stSendContDTMFCnf;

    PS_MEM_SET(&stSendContDTMFCnf, 0 ,sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU));

    /* ��д��Ϣ */
    stSendContDTMFCnf.enResult   = enResult;
    stSendContDTMFCnf.usClientId = usClientId;
    stSendContDTMFCnf.ucOpId     = ucOpId;
    stSendContDTMFCnf.ucCallId   = ucCallId;

    /* �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_CNF */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_CONT_DTMF_CNF,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_CNF_STRU),
                           &stSendContDTMFCnf);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndContDTMFRslt
 ��������  : �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_RSLT
 �������  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
             VOS_UINT8                           ucCallId
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : Iter16 �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndContDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
)
{
    TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU                   stSendContDTMFRslt;

    PS_MEM_SET(&stSendContDTMFRslt, 0 ,sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU));

    /* ��д��Ϣ */
    stSendContDTMFRslt.usClientId  = usClientId;
    stSendContDTMFRslt.ucOpId      = ucOpId;
    stSendContDTMFRslt.ucResult    = ucResult;

    /* �ϱ�TAF_CALL_EVT_SEND_CONT_DTMF_RSLT�� */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT,
                           usClientId,
                           sizeof(TAF_CALL_EVT_SEND_CONT_DTMF_RSLT_STRU),
                           &stSendContDTMFRslt);
}




VOS_VOID TAF_XCALL_SndBurstDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDtmfInd
)
{
    TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU                    stSendBurstDTMFInd;

    PS_MEM_SET(&stSendBurstDTMFInd, 0 ,sizeof(TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU));

    /* ��д��Ϣ */
    stSendBurstDTMFInd.usClientId  = usClientId;
    stSendBurstDTMFInd.ucOpId      = ucOpId;
    stSendBurstDTMFInd.ucCallId    = pstBurstDtmfInd->ucCallId;
    stSendBurstDTMFInd.ucDigitNum  = pstBurstDtmfInd->ucDigitNum;

    PS_MEM_CPY(stSendBurstDTMFInd.aucDigit, pstBurstDtmfInd->aucDigit, sizeof(stSendBurstDTMFInd.aucDigit));

    stSendBurstDTMFInd.ulOnLength  = pstBurstDtmfInd->ulOnLength;
    stSendBurstDTMFInd.ulOffLength = pstBurstDtmfInd->ulOffLength;

    /* Send the Burst DTMF Ind to AT */
    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_RCV_BURST_DTMF_IND,
                           usClientId,
                           sizeof(TAF_CALL_EVT_RCV_BURST_DTMF_IND_STRU),
                          &stSendBurstDTMFInd);
    return;
}



VOS_VOID TAF_XCALL_SndContDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDtmfInd
)
{
    TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU                     stSendContDTMFInd;

    PS_MEM_SET(&stSendContDTMFInd, 0 ,sizeof(TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU));

    stSendContDTMFInd.usClientId    = usClientId;
    stSendContDTMFInd.ucOpId        = ucOpId;
    stSendContDTMFInd.ucCallId      = pstContDtmfInd->ucCallId;
    stSendContDTMFInd.enSwitch      = pstContDtmfInd->enSwitch;
    stSendContDTMFInd.ucDigit       = pstContDtmfInd->ucDigit;

    TAF_XCALL_SndCsEvtToAt(TAF_CALL_EVT_RCV_CONT_DTMF_IND,
                           usClientId,
                           sizeof(TAF_CALL_EVT_RCV_CONT_DTMF_IND_STRU),
                          &stSendContDTMFInd);
    return;
}


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppEncryptVoiceCnf
 ��������  : �����ܻ�����ȷ�Ͻ��
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enEncVoiceStatus -- �ܻ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppEncryptVoiceCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus
)
{
    TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU                    *pstAppEncVoiceCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppEncVoiceCnf = (TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU));

    if (VOS_NULL_PTR == pstAppEncVoiceCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppEncVoiceCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppEncVoiceCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppEncVoiceCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstAppEncVoiceCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppEncVoiceCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppEncVoiceCnf->ulLength         = sizeof(TAF_CALL_APP_ENCRYPT_VOICE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppEncVoiceCnf->enMsgName        = ID_TAF_CALL_APP_ENCRYPT_VOICE_CNF;
    pstAppEncVoiceCnf->enEccVoiceStatus = enEncVoiceStatus;
    PS_MEM_CPY(&pstAppEncVoiceCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppEncVoiceCnf);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppEncryptVoiceInd
 ��������  : �����ܻ�ָʾ�������յ�KMC���ܻ�ָʾ��ǰ���ܻ�״̬
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enEncVoiceStatus -- �ܻ�״̬
             pstCallingNumber -- ���з����룬�����ǶԶ˵ĺ��룻
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppEncryptVoiceInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCallingNumber
)
{

    TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU                    *pstAppEncVoiceInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppEncVoiceInd = (TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU));

    if (VOS_NULL_PTR == pstAppEncVoiceInd)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppEncVoiceInd + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppEncVoiceInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppEncVoiceInd->ulSenderPid      = WUEPS_PID_TAF;
    pstAppEncVoiceInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppEncVoiceInd->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppEncVoiceInd->ulLength         = sizeof(TAF_CALL_APP_ENCRYPT_VOICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppEncVoiceInd->enMsgName        = ID_TAF_CALL_APP_ENCRYPT_VOICE_IND;
    pstAppEncVoiceInd->enEccVoiceStatus = enEncVoiceStatus;
    PS_MEM_CPY(&pstAppEncVoiceInd->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    if (VOS_NULL_PTR != pstCallingNumber)
    {
        PS_MEM_CPY(&pstAppEncVoiceInd->stCallingNumber, pstCallingNumber, sizeof(TAF_ECC_CALL_BCD_NUM_STRU));
    }

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppEncVoiceInd);

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppRemoteCtrlInd
 ��������  : �յ�KMC��Զ�̿���ָʾ���ϱ���APP
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enRemoteCtrlType -- KMCԶ�̿�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppRemoteCtrlInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlType
)
{

    TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU                   *pstAppRemoteCtrlInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppRemoteCtrlInd = (TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU));

    if (VOS_NULL_PTR == pstAppRemoteCtrlInd)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppRemoteCtrlInd + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppRemoteCtrlInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppRemoteCtrlInd->ulSenderPid      = WUEPS_PID_TAF;
    pstAppRemoteCtrlInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppRemoteCtrlInd->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppRemoteCtrlInd->ulLength         = sizeof(TAF_CALL_APP_EC_REMOTE_CTRL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppRemoteCtrlInd->enMsgName        = ID_TAF_CALL_APP_EC_REMOTE_CTRL_IND;
    pstAppRemoteCtrlInd->enRemoteCtrlType = enRemoteCtrlType;
    PS_MEM_CPY(&pstAppRemoteCtrlInd->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppRemoteCtrlInd);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppRemoteCtrlAnswerCnf
 ��������  : ����Զ�̿���Ӧ��������������ulResult��ʶԶ�̿���Ӧ����
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             ulResult         -- Զ�̿���Ӧ������ִ�н��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppRemoteCtrlAnswerCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32            enResult
)
{
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU               *pstAppRemoteCtrlAnswerCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppRemoteCtrlAnswerCnf = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU));

    if (VOS_NULL_PTR == pstAppRemoteCtrlAnswerCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppRemoteCtrlAnswerCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppRemoteCtrlAnswerCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppRemoteCtrlAnswerCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstAppRemoteCtrlAnswerCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppRemoteCtrlAnswerCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppRemoteCtrlAnswerCnf->ulLength         = sizeof(TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppRemoteCtrlAnswerCnf->enMsgName        = ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_CNF;
    pstAppRemoteCtrlAnswerCnf->enResult         = enResult;
    PS_MEM_CPY(&pstAppRemoteCtrlAnswerCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppRemoteCtrlAnswerCnf);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppEccSrvCapCfgCnf
 ��������  : ֪ͨAPP ECC������������ȷ�Ͻ��
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enResult         -- ECC������������ȷ�Ͻ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppEccSrvCapCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32         enResult
)
{
    TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU                  *pstAppEccSrvCapCfgCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppEccSrvCapCfgCnf = (TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU));

    if (VOS_NULL_PTR == pstAppEccSrvCapCfgCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppEccSrvCapCfgCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppEccSrvCapCfgCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppEccSrvCapCfgCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstAppEccSrvCapCfgCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppEccSrvCapCfgCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppEccSrvCapCfgCnf->ulLength         = sizeof(TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppEccSrvCapCfgCnf->enMsgName        = ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_CNF;
    pstAppEccSrvCapCfgCnf->enResult         = enResult;
    PS_MEM_CPY(&pstAppEccSrvCapCfgCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppEccSrvCapCfgCnf);

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppEccSrvCapQryCnf
 ��������  : ����APP��ѯECC���������Լ�״̬���
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enEccSrvCap      -- ECC������������
             enEccSrvStatus   -- ECC����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppEccSrvCapQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap,
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus
)
{
    TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU                  *pstAppEccSrvCapQryCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstAppEccSrvCapQryCnf = (TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                            sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAppEccSrvCapQryCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAppEccSrvCapQryCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstAppEccSrvCapQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstAppEccSrvCapQryCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstAppEccSrvCapQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstAppEccSrvCapQryCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstAppEccSrvCapQryCnf->ulLength         = sizeof(TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstAppEccSrvCapQryCnf->enMsgName        = ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_CNF;
    pstAppEccSrvCapQryCnf->enEccSrvCap      = enEccSrvCap;
    pstAppEccSrvCapQryCnf->enEccSrvStatus   = enEccSrvStatus;
    PS_MEM_CPY(&pstAppEccSrvCapQryCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstAppEccSrvCapQryCnf);

}
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndTestModeCfgCnf
 ��������  : ���Ͳ���ģʽ���ý��
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             ucResult         -- ����ģʽ����ȷ�Ͻ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndTestModeCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT32                                              ulResult
)
{
    TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU                 *pstSetEcTestModeCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSetEcTestModeCnf = (TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU));
    if (VOS_NULL_PTR == pstSetEcTestModeCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSetEcTestModeCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_SET_EC_TEST_MODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSetEcTestModeCnf->ulReceiverPid  = pstCtrl->ulModuleId;
    pstSetEcTestModeCnf->enMsgName      = ID_TAF_CALL_APP_SET_EC_TEST_MODE_CNF;
    pstSetEcTestModeCnf->stCtrl         = *pstCtrl;
    pstSetEcTestModeCnf->ulResult       = ulResult;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstSetEcTestModeCnf);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndTestModeQryCnf
 ��������  : ���ص�ǰ����ģʽ����
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             enTestMode       -- ��ǰ����ģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndTestModeQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode,
    VOS_UINT32                                              ulResult
)
{
    TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU                 *pstGetEcTestModeCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstGetEcTestModeCnf = (TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU));
    if (VOS_NULL_PTR == pstGetEcTestModeCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstGetEcTestModeCnf + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(TAF_CALL_APP_GET_EC_TEST_MODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstGetEcTestModeCnf->ulReceiverPid                      = pstCtrl->ulModuleId;
    pstGetEcTestModeCnf->enMsgName                          = ID_TAF_CALL_APP_GET_EC_TEST_MODE_CNF;
    pstGetEcTestModeCnf->stCtrl                             = *pstCtrl;
    pstGetEcTestModeCnf->enEccTestModeStatus                = enTestMode;
    pstGetEcTestModeCnf->ulResult                           = ulResult;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstGetEcTestModeCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndKmcKeyCfgCnf
 ��������  : ����KMC��Կ���ý��
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             ucResult         -- KMC��Կ���ý��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndKmcKeyCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT32                                              ulResult
)
{
    TAF_CALL_APP_SET_EC_KMC_CNF_STRU                       *pstSetKmcKeyCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSetKmcKeyCnf = (TAF_CALL_APP_SET_EC_KMC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(TAF_CALL_APP_SET_EC_KMC_CNF_STRU));
    if (VOS_NULL_PTR == pstSetKmcKeyCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSetKmcKeyCnf + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(TAF_CALL_APP_SET_EC_KMC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSetKmcKeyCnf->ulReceiverPid      = pstCtrl->ulModuleId;
    pstSetKmcKeyCnf->enMsgName          = ID_TAF_CALL_APP_SET_EC_KMC_CNF;
    pstSetKmcKeyCnf->stCtrl             = *pstCtrl;
    pstSetKmcKeyCnf->ulResult           = ulResult;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstSetKmcKeyCnf);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndKmcKeyCfgCnf
 ��������  : ���ص�ǰKMC��Կ����
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             ucCipherKeyLen   -- KMC��Կ����
             pucCipherKey     -- KMC��Կ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndKmcKeyQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo,
    VOS_UINT32                                              ulResult
)
{
    TAF_CALL_APP_GET_EC_KMC_CNF_STRU                        *pstGetKmcKeyCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstGetKmcKeyCnf = (TAF_CALL_APP_GET_EC_KMC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(TAF_CALL_APP_GET_EC_KMC_CNF_STRU));
    if (VOS_NULL_PTR == pstGetKmcKeyCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstGetKmcKeyCnf + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(TAF_CALL_APP_GET_EC_KMC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstGetKmcKeyCnf->ulReceiverPid            = pstCtrl->ulModuleId;
    pstGetKmcKeyCnf->enMsgName                = ID_TAF_CALL_APP_GET_EC_KMC_CNF;
    pstGetKmcKeyCnf->stCtrl                   = *pstCtrl;
    pstGetKmcKeyCnf->stKmcData.ucEccKmcVer    = pstEccPubKeyInfo->ucVerNum;
    pstGetKmcKeyCnf->stKmcData.usEccKmcLength = TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN;

    PS_MEM_CPY(pstGetKmcKeyCnf->stKmcData.aucEccKmcData,
               pstEccPubKeyInfo->aucPubKey,
               TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    pstGetKmcKeyCnf->ulResult           = ulResult;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstGetKmcKeyCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndRandomQryCnf
 ��������  : ����32����������ظ�APP
 �������  : pstCtrl          -- ��Ϣ���շ������Ϣ
             ucEccRandomSize  -- ���������
             pstEccRandom     -- ������ṹ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndRandomQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT8                                               ucEccRandomSize,
    TAF_CALL_APP_EC_RANDOM_DATA_STRU                       *pstEccRandom,
    VOS_UINT32                                              ulResult
)
{
    TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU                    *pstGetRandomCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstGetRandomCnf = (TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                           sizeof(TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU));
    if (VOS_NULL_PTR == pstGetRandomCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstGetRandomCnf + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(TAF_CALL_APP_GET_EC_RANDOM_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstGetRandomCnf->ulReceiverPid      = pstCtrl->ulModuleId;
    pstGetRandomCnf->enMsgName          = ID_TAF_CALL_APP_GET_EC_RANDOM_CNF;
    pstGetRandomCnf->stCtrl             = *pstCtrl;
    pstGetRandomCnf->ulResult           = ulResult;

    if (VOS_TRUE == ulResult)
    {
        PS_MEM_CPY((VOS_UINT8 *)pstGetRandomCnf->stEccRandom,
                   (VOS_UINT8 *)pstEccRandom,
                    ucEccRandomSize * sizeof(TAF_CALL_APP_EC_RANDOM_DATA_STRU));
    }

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstGetRandomCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndEncryptedVoiceDataInd
 ��������  : ����ģʽ�� �������ݷ��͸�APP
 �������  : usDataLen      -- �������ݳ���
             pData          -- ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : c00177591
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndEncryptedVoiceDataInd(
    VOS_INT8                                               *pscData,
    VOS_UINT32                                              ulDataLen
)
{
    TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU             *pstEncryptVoiceDataInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstEncryptVoiceDataInd = (TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                sizeof(TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU));
    if (VOS_NULL_PTR == pstEncryptVoiceDataInd)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstEncryptVoiceDataInd + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEncryptVoiceDataInd->ulReceiverPid      = WUEPS_PID_AT;
    pstEncryptVoiceDataInd->stCtrl.usClientId  = MN_GetRealClientId(TAF_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstEncryptVoiceDataInd->stCtrl.ucOpId      = 0;

    pstEncryptVoiceDataInd->enMsgName          = ID_TAF_CALL_APP_ENCRYPTED_VOICE_DATA_IND;
    pstEncryptVoiceDataInd->usLength           = (VOS_UINT16)TAF_XCALL_MIN(ulDataLen, TAF_CALL_APP_ENCRYPTED_VOICE_DATA_MAX_LENGTH);

    PS_MEM_CPY((VOS_UINT8 *)pstEncryptVoiceDataInd->aucData,
                pscData,
                pstEncryptVoiceDataInd->usLength);

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstEncryptVoiceDataInd);

    return;
}

#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE*/
#endif /*FEATURE_CHINA_TELECOM_VOICE_ENCRYPT*/

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppPrivacyModeSetCnf
 ��������  : ����privacy mode����ȷ����Ϣ
 �������  : pstCtrl  -- ��Ϣ���շ������Ϣ
             enResult -- ִ�н��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppPrivacyModeSetCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32                    enResult
)
{
    TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU                 *pstPrivacyModeSetCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPrivacyModeSetCnf = (TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                                  sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeSetCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPrivacyModeSetCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstPrivacyModeSetCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstPrivacyModeSetCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstPrivacyModeSetCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstPrivacyModeSetCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstPrivacyModeSetCnf->ulLength         = sizeof(TAF_CALL_APP_PRIVACY_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(&pstPrivacyModeSetCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));
    pstPrivacyModeSetCnf->enMsgName        = ID_TAF_CALL_APP_PRIVACY_MODE_SET_CNF;

    pstPrivacyModeSetCnf->enResult         = enResult;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstPrivacyModeSetCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppPrivacyModeQryCnf
 ��������  : ����privacy mode��ѯȷ����Ϣ
 �������  : pstCtrl        -- ��Ϣ���շ������Ϣ
             enPrivacyMode  -- privacy mode
             ucCallNums     -- ��ǰ������Ŀ
             pstCallPrivacyModeInfo -- privacy mode��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppPrivacyModeQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode,
    VOS_UINT8                                               ucCallNums,
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                   *pstCallPrivacyModeInfo
)
{
    TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU                 *pstPrivacyModeQryCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPrivacyModeQryCnf = (TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                                  sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeQryCnf)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPrivacyModeQryCnf + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstPrivacyModeQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstPrivacyModeQryCnf->ulSenderPid      = WUEPS_PID_TAF;
    pstPrivacyModeQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstPrivacyModeQryCnf->ulReceiverPid    = pstCtrl->ulModuleId;
    pstPrivacyModeQryCnf->ulLength         = sizeof(TAF_CALL_APP_PRIVACY_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(&pstPrivacyModeQryCnf->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));
    pstPrivacyModeQryCnf->enMsgName        = ID_TAF_CALL_APP_PRIVACY_MODE_QRY_CNF;
    pstPrivacyModeQryCnf->enPrivacyMode    = enPrivacyMode;

    if (0 != ucCallNums)
    {
        pstPrivacyModeQryCnf->ucCallNums       = ucCallNums;

        PS_MEM_CPY(&(pstPrivacyModeQryCnf->astCallVoicePrivacyInfo[0]),
                   pstCallPrivacyModeInfo,
                   sizeof(TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU) * ucCallNums);
    }

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstPrivacyModeQryCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SndAppPrivacyModeInd
 ��������  : ����privacy mode��ѯȷ����Ϣ
 �������  : pstCtrl              -- ��Ϣ���շ������Ϣ
             ucCallId             -- ��ǰ���е�call id
             enCallPrivacyMode    -- ��ǰ���е�privacy mode
             enPrivacyModeSetting -- �û����õ�privacy mode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SndAppPrivacyModeInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT8                                               ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enCallPrivacyMode,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyModeSetting
)
{
    TAF_CALL_APP_PRIVACY_MODE_IND_STRU                     *pstPrivacyModeInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPrivacyModeInd = (TAF_CALL_APP_PRIVACY_MODE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                                           sizeof(TAF_CALL_APP_PRIVACY_MODE_IND_STRU));
    if (VOS_NULL_PTR == pstPrivacyModeInd)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPrivacyModeInd + VOS_MSG_HEAD_LENGTH,
               0,
               sizeof(TAF_CALL_APP_PRIVACY_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstPrivacyModeInd->ulSenderCpuId                        = VOS_LOCAL_CPUID;
    pstPrivacyModeInd->ulSenderPid                          = WUEPS_PID_TAF;
    pstPrivacyModeInd->ulReceiverCpuId                      = VOS_LOCAL_CPUID;
    pstPrivacyModeInd->ulReceiverPid                        = pstCtrl->ulModuleId;
    pstPrivacyModeInd->ulLength                             = sizeof(TAF_CALL_APP_PRIVACY_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(&pstPrivacyModeInd->stCtrl, pstCtrl, sizeof(TAF_CCA_CTRL_STRU));
    pstPrivacyModeInd->enMsgName                            = ID_TAF_CALL_APP_PRIVACY_MODE_IND;

    pstPrivacyModeInd->enPrivacyMode                        = enPrivacyModeSetting;
    pstPrivacyModeInd->stCallVoicePrivacyInfo.enPrivacyMode = enCallPrivacyMode;
    pstPrivacyModeInd->stCallVoicePrivacyInfo.ucCallId      = ucCallId;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstPrivacyModeInd);

    return;
}

#endif
/*lint -restore*/



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





