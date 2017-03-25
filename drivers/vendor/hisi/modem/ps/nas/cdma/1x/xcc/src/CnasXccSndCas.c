/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndCas.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��09��15��
  ��������   : 1X CC����CAS����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��15��
    ��    ��   : h00246512
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "CnasXccSndCas.h"
#include  "CnasMain.h"
#include  "CnasXccCtx.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "CnasCcb.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include  "CnasMntn.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"

#include  "xcc_aps_pif.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasCallRelReq
 ��������  : ��CASģ�鷢��ID_CNAS_CAS_1X_CALL_REL_REQ��Ϣ
 �������  : pstCallInfo -- ������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasCallRelReq(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                           ucConRef,
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason,
    VOS_UINT8                           ucIsRelAll
)
{
    CNAS_CAS_1X_CALL_REL_REQ_STRU      *pstRelReq = VOS_NULL_PTR;

    /* ������Ϣ */
    pstRelReq = (CNAS_CAS_1X_CALL_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(CNAS_CAS_1X_CALL_REL_REQ_STRU));

    if (VOS_NULL_PTR == pstRelReq)
    {
        return;
    }

    pstRelReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstRelReq->ulReceiverPid    = UEPS_PID_1XCASM;
    pstRelReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstRelReq->ulSenderPid      = UEPS_PID_XCC;

    /* �����Ϣ */
    pstRelReq->enMsgId          = ID_CNAS_CAS_1X_CALL_REL_REQ;
    pstRelReq->usOpId           = 0;
    pstRelReq->ucIsRelAll       = ucIsRelAll;
    pstRelReq->ucConnectId      = ucConnectId;
    pstRelReq->ucConRef         = ucConRef;
    pstRelReq->enRelReason      = enRelReason;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstRelReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstRelReq);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasEstReq
 ��������  : ��CASģ�鷢��ID_CNAS_CAS_1X_EST_REQ��Ϣ
 �������  : enEstType : CAS_CNAS_1X_EST_TYPE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

  3.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasEstReq(
    CAS_CNAS_1X_EST_TYPE_ENUM_UINT8     enEstType,
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
)
{
    CNAS_CAS_1X_EST_REQ_STRU                       *pstEstReq = VOS_NULL_PTR;
    CAS_CNAS_1X_PAGING_RSP_INFO_STRU                stPagingRspInfo;
    CAS_CNAS_1X_CALLING_PARTY_NUM_INFO_STRU        *pstCallingPartyNum = VOS_NULL_PTR;
    CAS_CNAS_1X_SUB_ADDRESS_INFO_STRU              *pstCallingPartySubAddr = VOS_NULL_PTR;
    CAS_CNAS_1X_SUB_ADDRESS_INFO_STRU              *pstCalledPartySubAddr = VOS_NULL_PTR;

    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32               enServiceType;

    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8             enCnas1xReturnCause;

    VOS_UINT8                                       ucNoDataSrvRspSo33Flg;
    VOS_UINT32                                      ulIsExist1xDataOpt;

    /* ������Ϣ */
    pstEstReq = (CNAS_CAS_1X_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(CNAS_CAS_1X_EST_REQ_STRU));

    if (VOS_NULL_PTR == pstEstReq)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstEstReq + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_CAS_1X_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(CNAS_CAS_1X_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ */
    pstEstReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEstReq->ulReceiverPid    = UEPS_PID_1XCASM;
    pstEstReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEstReq->ulSenderPid      = UEPS_PID_XCC;

    pstEstReq->enMsgId          = ID_CNAS_CAS_1X_EST_REQ;
    pstEstReq->usOpId           = 0;
    pstEstReq->enEstType        = enEstType;

    CNAS_XCC_ConvertSoToServiceType((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)pstCallInfo->enCurrentSo, &enServiceType);

    if ( CAS_CNAS_1X_EST_TYPE_PAGING_RSP == enEstType )
    {
        NAS_MEM_SET_S(&stPagingRspInfo, sizeof(stPagingRspInfo), 0x00, sizeof(stPagingRspInfo));

        /* ��װCAS_CNAS_1X_PAGING_RSP_INFO_STRU */

        pstEstReq->stPagingRspInfo.ucConnectId            = pstCallInfo->ucConnectId;
        pstEstReq->stPagingRspInfo.ucIsMtCallInRoamingAcc = CNAS_CCB_GetMtCallInRoamingAccFlg();

        ucNoDataSrvRspSo33Flg = CNAS_XCC_IsPagingRspSo33InNoDataSrv();

        ulIsExist1xDataOpt    = CNAS_XCC_IsExist1xDataOperation(pstCallInfo->enCurrentSo);

        /* ��������ݱ��е���ǰû��������·������so����Ϊ0*/
        if ((VOS_FALSE == ucNoDataSrvRspSo33Flg)
         && (VOS_FALSE == ulIsExist1xDataOpt)
         && (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType))
        {
            pstEstReq->stPagingRspInfo.stSoInfo.enSo      = 0;
        }
        else
        {
            pstEstReq->stPagingRspInfo.stSoInfo.enSo      = pstCallInfo->enCurrentSo;
        }


        if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
        {
            pstEstReq->stPagingRspInfo.enPM = (VOS_UINT8)pstCallInfo->enReqPrivacyMode;
        }
    }
    else if ( CAS_CNAS_1X_EST_TYPE_ORIGINATION == enEstType )
    {

        /* Ŀǰ��ʱ����Щ���� */
        pstEstReq->stOriginationInfo.stOrigNumInfo.enDigitMode = pstCallInfo->stCalledPartyNum.enDigitMode;
        pstEstReq->stOriginationInfo.stOrigNumInfo.enNumType   = pstCallInfo->stCalledPartyNum.enNumType;
        pstEstReq->stOriginationInfo.stOrigNumInfo.enNumPlan   = pstCallInfo->stCalledPartyNum.enNumPlan;
        pstEstReq->stOriginationInfo.stOrigNumInfo.ucDigitNum  = pstCallInfo->stCalledPartyNum.ucDigitNum;
        NAS_MEM_CPY_S(pstEstReq->stOriginationInfo.stOrigNumInfo.aucDigit,
                      sizeof(pstEstReq->stOriginationInfo.stOrigNumInfo.aucDigit),
                      pstCallInfo->stCalledPartyNum.aucDigit,
                      sizeof(pstCallInfo->stCalledPartyNum.aucDigit));

        pstEstReq->stOriginationInfo.bitOpCalledPartySubAddr   = pstCallInfo->bitOpCalledPartySubAddr;
        pstEstReq->stOriginationInfo.bitOpCallingPartyNum      = pstCallInfo->bitOpCallingPartyNum;
        pstEstReq->stOriginationInfo.bitOpCallingPartySubAddr  = pstCallInfo->bitOpCallingPartySubAddr;
        pstEstReq->stOriginationInfo.bitOpQosInfo              = pstCallInfo->bitOpQosInfo;
        pstEstReq->stOriginationInfo.bitOpSpare                = 0;


        pstCalledPartySubAddr               = (&pstEstReq->stOriginationInfo.stCalledPartySubAddr);
        pstCallingPartySubAddr              = (&pstEstReq->stOriginationInfo.stCallingPartySubAddr);
        pstCallingPartyNum                  = (&pstEstReq->stOriginationInfo.stCallingPartyNum);

        pstCalledPartySubAddr->ucIsExtBit    = pstCallInfo->stCalledPartySubAddr.ucIsExtBit;
        pstCalledPartySubAddr->enSubAddrType = pstCallInfo->stCalledPartySubAddr.enSubAddrType;
        pstCalledPartySubAddr->enEoInd       = pstCallInfo->stCalledPartySubAddr.enEo;
        pstCalledPartySubAddr->ucNumLen      = pstCallInfo->stCalledPartySubAddr.ucNumLen;
        NAS_MEM_CPY_S(pstCalledPartySubAddr->aucDigitNum,
                      sizeof(pstCalledPartySubAddr->aucDigitNum),
                      pstCallInfo->stCalledPartySubAddr.aucCharNum,
                      sizeof(pstCallInfo->stCalledPartySubAddr.aucCharNum));

        pstCallingPartySubAddr->ucIsExtBit    = pstCallInfo->stCallingPartySubAddr.ucIsExtBit;
        pstCallingPartySubAddr->enSubAddrType = pstCallInfo->stCallingPartySubAddr.enSubAddrType;
        pstCallingPartySubAddr->enEoInd       = pstCallInfo->stCallingPartySubAddr.enEo;
        pstCallingPartySubAddr->ucNumLen      = pstCallInfo->stCallingPartySubAddr.ucNumLen;
        NAS_MEM_CPY_S(pstCallingPartySubAddr->aucDigitNum,
                      sizeof(pstCallingPartySubAddr->aucDigitNum),
                      pstCallInfo->stCallingPartySubAddr.aucCharNum,
                      sizeof(pstCallInfo->stCallingPartySubAddr.aucCharNum));

        pstCallingPartyNum->enNumType         = pstCallInfo->stCallingPartyNum.enNumType;
        pstCallingPartyNum->enNumPlan         = pstCallInfo->stCallingPartyNum.enNumPlan;
        pstCallingPartyNum->ucNumLen          = pstCallInfo->stCallingPartyNum.ucDigitNum;
        NAS_MEM_CPY_S(pstCallingPartyNum->aucDigitNum,
                      sizeof(pstCallingPartyNum->aucDigitNum),
                      pstCallInfo->stCallingPartyNum.aucDigit,
                      sizeof(pstCallInfo->stCallingPartyNum.aucDigit));


        pstEstReq->stOriginationInfo.stSoInfo.enSo          = pstCallInfo->enCurrentSo;
        pstEstReq->stOriginationInfo.ucConnectId            = pstCallInfo->ucConnectId;
        pstEstReq->stOriginationInfo.ucIsMtCallInRoamingAcc = CNAS_CCB_GetMtCallInRoamingAccFlg();

        pstEstReq->stOriginationInfo.ucIsDataReady                 = pstCallInfo->ucIsDataReady;
        pstEstReq->stOriginationInfo.ucIsEmergencyCall             = pstCallInfo->ucIsEmergencyCall;
        pstEstReq->stOriginationInfo.stOrigQosInfo.ucQosParaLength = pstCallInfo->ucQosInfoLen;
        NAS_MEM_CPY_S(pstEstReq->stOriginationInfo.stOrigQosInfo.aucQosPara,
                      sizeof(pstEstReq->stOriginationInfo.stOrigQosInfo.aucQosPara),
                      pstCallInfo->aucQosInfo,
                      sizeof(pstEstReq->stOriginationInfo.stOrigQosInfo.aucQosPara));

        /* ORIG_REASON - The mobile station shall set this field to '0' if the mobile station initiates a silent-retry, i.e. an autonomous
                         access re-attempt to re-originate this call without user interaction, after the mobile station received an access
                         attempt failure from the ARQ Sublayer for a user initiated origination; otherwise, the mobile station shall set this
                         field to '0'.

           ORIG_COUNT -  If the ORIG_REASON is set to '1', the mobile station shall set this field to the number of consecutive silent-retry,
                         i.e. an autonomous access re-attempt that were made to re-originate the call, without user interaction, that were due
                         to the mobile receiving an access attempt failure from the ARQ Sublayer. If the number of consecutive silent-retry is
                         greater than three,the mobile station shall set this field to '11'. */

        if (VOS_TRUE == pstCallInfo->ucIsL2ErrReOrig)
        {
            pstEstReq->stOriginationInfo.ucIsReOrigReason  = VOS_TRUE;

            if (pstCallInfo->ucReOrigCount > CNAS_XCC_L2_ERR_MAX_RE_ORIG_COUNT)
            {
                pstEstReq->stOriginationInfo.ucReOrigCount = CNAS_XCC_L2_ERR_MAX_RE_ORIG_COUNT;
            }
            else
            {
                pstEstReq->stOriginationInfo.ucReOrigCount = pstCallInfo->ucReOrigCount;
            }
        }
        else
        {
            pstEstReq->stOriginationInfo.ucIsReOrigReason  = VOS_FALSE;

            if (VOS_TRUE == CNAS_XCC_IsL3ErrReOrigCount())
            {
                /*�ز�����ת�� */
                pstEstReq->stOriginationInfo.ucReOrigCount = CNAS_XCC_ConvertL3ErrReOrigCount(pstCallInfo->ucReOrigCount);
            }
            else
            {
                pstEstReq->stOriginationInfo.ucReOrigCount = 0;
            }
        }


        pstEstReq->stOriginationInfo.ucSrId                     = pstCallInfo->ucSrId;

        if (VOS_TRUE == pstCallInfo->ulIsPrevHrpdFlg)
        {
            pstEstReq->stOriginationInfo.stLastActDataNetInfo.enDataSysMode = CAS_CNAS_1X_DATA_SYS_MODE_HRPD;
            pstEstReq->stOriginationInfo.stLastActDataNetInfo.usSid         = pstCallInfo->stPrevHrpdActNetInfo.usSid;
            pstEstReq->stOriginationInfo.stLastActDataNetInfo.usNid         = pstCallInfo->stPrevHrpdActNetInfo.usNid;
            pstEstReq->stOriginationInfo.stLastActDataNetInfo.usPzid        = pstCallInfo->stPrevHrpdActNetInfo.usPzid;
        }

        pstEstReq->stOriginationInfo.enDormantDataCall = pstCallInfo->ucIsDormDataCall;

        enCnas1xReturnCause = CNAS_CCB_Get1xReturnCause();

        pstEstReq->stOriginationInfo.enReturnCause          = CNAS_CCB_CovertReturnCause(enCnas1xReturnCause);

        if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
        {
            pstEstReq->stOriginationInfo.enPM = (VOS_UINT8)pstCallInfo->enReqPrivacyMode;
        }
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_SndCasEstReq Wrong type", enEstType);
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEstReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstEstReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasDschDataReq
 ��������  : ��CASģ�鷢��ID_CNAS_CAS_1X_DSCH_DATA_REQ��Ϣ
 �������  : pstCallInfo -- ������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasDschDataReq(
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8                  enTxcDschMsgType,
    CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8                       enOrderType,
    VOS_UINT8                                               ucMsgSeqNum,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucMsgData
)
{
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDataReq = VOS_NULL_PTR;
    VOS_UINT16                          usOctetLen;
    VOS_UINT32                          ulMsgLen;

    /* ������Ϣ */
    usOctetLen =(usMsgDataLen / CNAS_XCC_OCTET_BIT_LEN);

    if ((usMsgDataLen % CNAS_XCC_OCTET_BIT_LEN) > 0)
    {
        usOctetLen++;
    }

    ulMsgLen   = sizeof(CNAS_CAS_1X_DSCH_DATA_REQ_STRU) + usOctetLen - sizeof(pstDataReq->aucMsgData);

    pstDataReq = (CNAS_CAS_1X_DSCH_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC, ulMsgLen);

    if (VOS_NULL_PTR == pstDataReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstDataReq, ulMsgLen, 0, ulMsgLen);

    /* �����Ϣ */
    pstDataReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstDataReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstDataReq->ulSenderPid      = UEPS_PID_XCC;
    pstDataReq->ulReceiverPid    = UEPS_PID_1XCASM;
    pstDataReq->ulLength         = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstDataReq->enMsgId           = ID_CNAS_CAS_1X_DSCH_DATA_REQ;
    pstDataReq->usOpId            = 0;
    pstDataReq->enTxDschMsgType   = enTxcDschMsgType;
    pstDataReq->ucMsgSeqNum       = ucMsgSeqNum;

    /* ��Ҫ��һ��Order��Ϣ�����ͣ�Reject Order����Ҫȷ�� */
    if ( ( CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER == enOrderType )
      || ( CAS_CNAS_1X_TX_TCH_SERVICE_OPTION_CONTROL_MSG == enTxcDschMsgType ))
    {
        pstDataReq->enIsAmDataReq = VOS_FALSE;
    }
    else
    {
        pstDataReq->enIsAmDataReq = VOS_TRUE;
    }

    /*���order��Ϣ������*/
    pstDataReq->usMsgDataLen      = usMsgDataLen;
    NAS_MEM_CPY_S(pstDataReq->aucMsgData, usOctetLen, pucMsgData, usOctetLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDataReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstDataReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_NotifyCasEnterTchSubstate
 ��������  : ֪ͨCASģ�����Tch substate
 �������  : pstCallInfo -- ������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��15��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyCasEnterTchSubstate(VOS_VOID)
{
    CNAS_CAS_1X_ENTER_TCH_SUBSTATE_NOTIFY_STRU             *pstDataReq = VOS_NULL_PTR;

    /* ������Ϣ */
    pstDataReq = (CNAS_CAS_1X_ENTER_TCH_SUBSTATE_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(CNAS_CAS_1X_ENTER_TCH_SUBSTATE_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDataReq)
    {
        return;
    }

    /* �����Ϣ */
    pstDataReq->ulReceiverPid     = UEPS_PID_1XCASM;
    pstDataReq->enMsgId           = ID_CNAS_CAS_1X_ENTER_TCH_SUBSTATE_NOTIFY;
    pstDataReq->usOpId            = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDataReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstDataReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasCschDataReq
 ��������  : ��CASģ�鷢��ID_CNAS_CAS_1X_CSCH_DATA_REQ��Ϣ
 �������  : enTxCschMsgType -- ��Ϣ����
             enAckReqFlag    -- ȷ�ϱ�־
             pucAckPara      -- ȷ�ϰ�������
             usMsgDataLen    -- ����ĳ���
             pucMsgData      -- ���������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasCschDataReq(
    CAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM_UINT8               enTxCschMsgType,
    PS_BOOL_ENUM_UINT8                                      enAckReqFlag,
    VOS_UINT8                                              *pucAckPara,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucMsgData
)
{
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstDataReq = VOS_NULL_PTR;
    VOS_UINT16                          usOctetLen;
    VOS_UINT32                          ulMsgLen;

    /* ������Ϣ */
    usOctetLen =(usMsgDataLen / CNAS_XCC_OCTET_BIT_LEN);

    if ((usMsgDataLen % CNAS_XCC_OCTET_BIT_LEN) > 0)
    {
        usOctetLen++;
    }

    ulMsgLen   = sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) + usOctetLen - sizeof(pstDataReq->aucMsgData);

    pstDataReq = (CNAS_CAS_1X_CSCH_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC, ulMsgLen);

    if (VOS_NULL_PTR == pstDataReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstDataReq, ulMsgLen, 0, ulMsgLen);

    /* �����Ϣ */
    pstDataReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstDataReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstDataReq->ulSenderPid      = UEPS_PID_XCC;
    pstDataReq->ulReceiverPid    = UEPS_PID_1XCASM;
    pstDataReq->ulLength         = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstDataReq->enMsgId           = ID_CNAS_CAS_1X_CSCH_DATA_REQ;
    pstDataReq->usOpId            = 0;
    pstDataReq->enTxCschMsgType   = enTxCschMsgType;
    pstDataReq->enAckReqFlag      = enAckReqFlag;

    /* ��ǰ��ΪCNAS�����Ķ���response��Ϣ�������������ٸ� */
    pstDataReq->enMsgDataType     = CAS_CNAS_1X_DATA_TYPE_RESPONSE;

    NAS_MEM_CPY_S(pstDataReq->aucAckPara, sizeof(pstDataReq->aucAckPara), pucAckPara, CNAS_XCC_MS_ACK_PARA_LEN);

    /*���order��Ϣ������*/
    pstDataReq->usMsgDataLen      = usMsgDataLen;
    NAS_MEM_CPY_S(pstDataReq->aucMsgData, usOctetLen, pucMsgData, usOctetLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDataReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstDataReq);

    return;
}

/*lint -restore*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasBeginSessionNotify
 ��������  : XCC��CAS����Session����
 �������  : CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16
             enSessionType : Session����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00133353
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                        enSessionType
)
{
    CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU                         *pstBeginSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                                  ulMsgLength;

    ulMsgLength                                                 = sizeof(CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XCC, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_XCC;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_1XCASM;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_1X_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->usOpId           = 0x00;
    pstBeginSessionNotify->enSessionType    = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBeginSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasEndSessionNotify
 ��������  : XCC��CAS����Session�ͷ�
 �������  : CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16
             enSessionType : Session����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00133353
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
)
{
    CNAS_CAS_1X_SESSION_END_NTF_STRU                       *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_1X_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_1X_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XCC, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstEndSessionNotify->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid        = UEPS_PID_XCC;
    pstEndSessionNotify->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid      = UEPS_PID_1XCASM;
    pstEndSessionNotify->ulLength           = ulMsgLength;
    pstEndSessionNotify->enMsgId            = ID_CNAS_CAS_1X_SESSION_END_NTF;
    pstEndSessionNotify->usOpId             = 0x00;
    pstEndSessionNotify->enSessionType      = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEndSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstEndSessionNotify);

    return;
}
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasEccServiceReq
 ��������  : XCC��CAS�����ܻ�SOЭ��������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasEccServiceReq(VOS_VOID)
{
    CNAS_CAS_1X_ECC_SERVICE_REQ_STRU                       *pstEccSrvReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_1X_ECC_SERVICE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEccSrvReq = (CNAS_CAS_1X_ECC_SERVICE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                                sizeof(CNAS_CAS_1X_ECC_SERVICE_REQ_STRU));

    if (VOS_NULL_PTR == pstEccSrvReq)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstEccSrvReq + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstEccSrvReq->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstEccSrvReq->ulSenderPid           = UEPS_PID_XCC;
    pstEccSrvReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstEccSrvReq->ulReceiverPid         = UEPS_PID_1XCASM;
    pstEccSrvReq->ulLength              = ulMsgLength;
    pstEccSrvReq->enMsgId               = ID_CNAS_CAS_1X_ECC_SERVICE_REQ;
    pstEccSrvReq->usOpId                = 0x00;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEccSrvReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstEccSrvReq);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndCasLongCodeTransitionNtf
 ��������  : XCC��CAS����privacy mode��������

 �������  : ucUsePrivateLongCodeFlag -- privacy mode����
 �������  : ��
 �� �� ֵ  : VOS_VOID

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_SndCasLongCodeTransitionNtf(VOS_UINT8 ucUsePrivateLongCodeFlag)
{
    CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU              *pstLongCodeNtf = VOS_NULL_PTR;

    pstLongCodeNtf = (CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                        sizeof(CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU));

    if (VOS_NULL_PTR == pstLongCodeNtf)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstLongCodeNtf + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstLongCodeNtf->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstLongCodeNtf->ulSenderPid              = UEPS_PID_XCC;
    pstLongCodeNtf->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstLongCodeNtf->ulReceiverPid            = UEPS_PID_1XCASM;
    pstLongCodeNtf->ulLength                 = sizeof(CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLongCodeNtf->enMsgId                  = ID_CNAS_CAS_1X_LONG_CODE_TRANSITION_NTF;
    pstLongCodeNtf->usOpId                   = 0x00;
    pstLongCodeNtf->enUsePrivateLongCodeFlag = (PS_BOOL_ENUM_UINT8)ucUsePrivateLongCodeFlag;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstLongCodeNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstLongCodeNtf);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





