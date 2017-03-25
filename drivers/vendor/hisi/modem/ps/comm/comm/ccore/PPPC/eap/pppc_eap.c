/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_eap.c
  �� �� ��   : ����
  ��    ��   : q00359829
  ��������   : 2015��11��12��
  ����޸�   :
  ��������   : EAP ��Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��12��
    ��    ��   : q00359829
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_md5.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_C
/*lint +e767*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : PPPC_EAP_ReceiveRequest
 ��������  : EAP�յ�Request��Ϣ, ��������ͷ������Ӧ����
 �������  : pstPppInfo     PPP���ƿ�ָ��
                            pPacket         ����ָ��
                            ucId               eap����Id
                            ulLen           eap���ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :PPPC_EAP_ReceivePacket

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : q00359829
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveRequest
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    VOS_UINT8                           ucPayloadType;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* Payload���Ȳ��Ϸ� */
    if ((EAP_PAYLOAD_MAX_LEN < ulLen) || (PPPC_EAP_HEADERLEN > ulLen))
    {
        /*������������Ϣ*/
        PPPC_WARNING_LOG1("EAP Payload err", ulLen);
        return;
    }

    /* ��ȡEAP�����е�Payload type */
    PPP_GET_EAP_TYPE(ucPayloadType, pPacket);

    /*���·��ͱ���ID��TYPE*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;
    pstEapInfo->enRequestType           = ucPayloadType;

    /* ID ����һ����� */
    if (ucId == pstEapInfo->usEAPLastReqID)
    {
        PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);
        return;
    }

    /*����TYPE��ͬ������Ӧ�¼�*/
    switch (ucPayloadType)
    {
        case PPPC_EAP_IDENTITY_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_IDENTITY_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_NOTIFY_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_NOTIFY_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_MD5_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_AKA_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_AKA_PRIME_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        default:
            /*δ֪��������NAK*/
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_NAK_EVENT, pPacket);
            break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_ReceiveSuccess
 ��������  : EAP�յ�Success��Ϣ�Ĵ���
 �������  : pstPppInfo     PPP���ƿ�ָ��
                            pPacket         ����ָ��
                            ucId               eap����Id
                            ulLen           eap���ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :PPPC_EAP_ReceivePacket

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : q00359829
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveSuccess
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    /*���·��ͱ���ID*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;


    PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_SUCCESS_EVENT, pPacket);
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_ReceiveFailure
 ��������  : EAP�յ�Failure��Ϣ�Ĵ���
 �������  : pstPppInfo     PPP���ƿ�ָ��
                            pPacket         ����ָ��
                            ucId               eap����Id
                            ulLen           eap���ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :PPPC_EAP_ReceivePacket

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : q00359829
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveFailure
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    /*���·��ͱ���ID*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;

    /*�ϱ�OM��ά�ɲ���Ϣ*/
    g_stPppcStatRpt.stPppcStatisticInfo.ulNameOrPwdAuthFailCnt++;
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_FAILURE_EVENT, pPacket);
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_ReceivePacket
 ��������  : EAP�յ���Ϣ�Ĵ���
 �������  : pstPppInfo     PPP���ƿ�ָ��
                            pPacket         ����ָ��
                            ucId               eap����Id
                            ulLen           eap���ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :PPPC_EAP_ReceivePacket

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : q00359829
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceivePacket
(
    PPPINFO_S                          *pstPppInfo,
    VOS_UINT8                          *pHead,
    VOS_UINT8                          *pPacket,
    VOS_UINT32                          ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    VOS_UINT8                           ucCode;
    VOS_UINT8                           ucId;
    VOS_UINT16                          usCiLen;
    VOS_UINT32                          ulRet;


    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pstPppInfo))
    {
        PPPC_WARNING_LOG("Input param invalid!");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* ������İ�̫������ */
    if (ulLen < FSM_HDRLEN)
    {
        PPPC_WARNING_LOG1("Too short packet", ulLen);
        return;
    }

    /* ��ñ������ֶ�ֵ, ���ƶ�����ָ��*/
    PPP_GET_EAP_CODE(ucCode, pPacket);
    PPP_GET_EAP_ID(ucId, pPacket);
    PPP_GET_EAP_LEN(usCiLen, pPacket);

    if ((PPPC_EAP_HEADERLEN > usCiLen) || (EAP_PAYLOAD_MAX_LEN <= usCiLen))
    {
        PPPC_WARNING_LOG1("Invalue EAP packet length", usCiLen);
        return;
    }

    /*������ʱ��*/
    if (VOS_NULL_PTR != pstEapInfo->hReqTimeoutID)
    {
        (VOS_VOID)VOS_StopRelTimer((HTIMER *)&(pstEapInfo->hReqTimeoutID));
    }

    ulRet   = VOS_StartRelTimer((HTIMER *)&(pstEapInfo->hReqTimeoutID), MSPS_PID_PPPC,
           PPPC_EAP_TIMEOUT_LENTH, pstPppInfo->ulRPIndex, PPPC_EAP_RCV_EAP_REQ_TIMER,
           VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRet)
    {
       PPPC_WARNING_LOG("EAP VOS_Timer_Create TIMER error!");
    }

    /*��������code�����ò�ͬ����*/
    switch (ucCode)
    {
        case PPPC_EAP_REQUEST_TYPE:
            PPPC_EAP_ReceiveRequest(pstPppInfo, pPacket, ucId, ulLen);
            break;

        case PPPC_EAP_SUCCESS_TYPE:
            PPPC_EAP_ReceiveSuccess(pstPppInfo, pPacket, ucId, ulLen);
            break;

        case PPPC_EAP_FAILURE_TYPE:
            PPPC_EAP_ReceiveFailure(pstPppInfo, pPacket, ucId, ulLen);
            break;

        default:
            {
                /*������������Ϣ*/
                PPPC_WARNING_LOG1("Illegal Packet Code", ucCode);
            }
            break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_RcvReqTimeout
 ��������  : ��ʱ����
 �������  : ulPppId     PPP���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EAP_RcvReqTimeout(VOS_UINT32 ulPppId)
{
    PPPC_EAP_PeerProcessEvent(ulPppId, PPPC_EAP_PEER_TIMEOUT_EVENT, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_MD5_CheckParam
 ��������  : ��μ��
 �������  : pstEAPInput         ����
 �������  : pstMethodOutput
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_EAP_MD5_CheckParam
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPInput
)
{
    if ((VOS_NULL_PTR == pstMethodOutput) || (VOS_NULL_PTR == pstEAPInput))
    {
        PPPC_WARNING_LOG("Input param is null!");
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pstMethodOutput->pucPktData)
        || (VOS_NULL_PTR == pstMethodOutput->pusRespLen)
        || (VOS_NULL_PTR == pstEAPInput->pucPktData))
    {
        PPPC_WARNING_LOG("Input sub param is null");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_MD5_ProcessPkt
 ��������  : EAP Md5���������Ȩ���
 �������  : pstEAPInfo     EAPʵ����Ϣ
             ucPpstEAPInput ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EAP_MD5_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPInput
)
{
    PPPC_AUTH_MSG_STRU                  stMsg;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucData;
    VOS_UINT16                          usPayloadLen;
    VOS_UINT16                          usRespLen;
    VOS_UINT16                          usNameLen;
    VOS_UINT8                           aucHostName[PPP_MAXUSERNAMELEN + 2]; /* ������ */


    ulRet   = PPPC_EAP_MD5_CheckParam(pstMethodOutput, pstEAPInput);
    if (VOS_OK != ulRet)
    {
        return;
    }

    PS_MEM_SET(&stMsg, 0, sizeof(stMsg));
    PS_MEM_SET(aucHostName, 0, sizeof(aucHostName));

    if (pstEAPInput->usEAPLen <= (PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN))
    {
        PPPC_WARNING_LOG1("Invalid md5 len!", pstEAPInput->usEAPLen);
        return;
    }

    /* ��ȡ����ID */
    stMsg.ucPktID   = pstEAPInput->ucEAPID;

    /* ��ȡ����ָ�� */
    pucData         = pstEAPInput->pucPktData;

    /* ��ȡpayload���� */
    usPayloadLen    = pstEAPInput->usEAPLen
                    - PPPC_EAP_HEADERLEN - PPPC_EAP_TYPE_FIELD_LEN;

    /* ƫ�Ƶ�TYPE-DATA�� */
    PPP_INCPTR(PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN, pucData);

    PPP_GETCHAR(stMsg.ucPwdLen, pucData);

    usPayloadLen--;

    if (usPayloadLen < stMsg.ucPwdLen)
    {
        PPPC_WARNING_LOG2("Invalid pwd len!", usPayloadLen, stMsg.ucPwdLen);
        return;
    }

    /* ��ȡ���� */
    PS_MEM_CPY(stMsg.szPwd, pucData, stMsg.ucPwdLen);

    /* �ƶ�ָ�� */
    PPP_INCPTR(stMsg.ucPwdLen, pucData);

    usPayloadLen       -= stMsg.ucPwdLen;
    stMsg.ucUsrNameLen  = (VOS_UINT8)usPayloadLen;

    if (stMsg.ucUsrNameLen >= PPP_MAXUSERNAMELEN)
    {
        PPPC_WARNING_LOG1("Invalid username len", stMsg.ucUsrNameLen);
        stMsg.ucUsrNameLen  = PPP_MAXUSERNAMELEN;
    }

    /* ��ȡ�û��� */
    PS_MEM_CPY(stMsg.szUsrName, pucData, stMsg.ucUsrNameLen);

    /*ȡ���ص�password,��Ϊ����Response�ı���secret */
    ulRet = PPP_GetConfigPassWord((VOS_UINT8 *)stMsg.szResponse);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get pass word fail when when receive challenge.",
            ulRet, pstMethodOutput->ulPppId);
    }

    stMsg.ucResponseLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)(stMsg.szResponse));

    /* ����MD5�㷨����Response */
    PPPC_MD5_GenResponse(&stMsg);

    /* ��Responseˢ�µ�EAPʵ���� */
    pucData     = pstMethodOutput->pucPktData
                + PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN;
    PPP_PUTCHAR(stMsg.ucResponseLen, pucData);
    PS_MEM_CPY(pucData, stMsg.szResponse, stMsg.ucResponseLen);
    pucData     += stMsg.ucResponseLen;

    /* ˢ��Response���� */
    usRespLen   = PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN
                + sizeof(stMsg.ucResponseLen) + stMsg.ucResponseLen;

    ulRet = PPP_GetConfigUserName(aucHostName, pstMethodOutput->ulPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get user name fail when when receive challenge.",
            ulRet, pstMethodOutput->ulPppId);
    }

    usNameLen = (VOS_UINT16) VOS_StrLen((CHAR *)aucHostName);
    if (PPPC_EAP_MAX_RESPONSE_LEN <= (usNameLen + usRespLen)
        || (PPP_MAXUSERNAMELEN < usNameLen))
    {
        PPPC_WARNING_LOG3("Invalid name len",
            usNameLen, usRespLen, pstMethodOutput->ulPppId);
        usNameLen   = PPP_MAXUSERNAMELEN;
    }

    PS_MEM_CPY(pucData, aucHostName, usNameLen);

    usRespLen   += usNameLen;

    PPPC_EAP_UpdateLen(pstMethodOutput->pucPktData, pstMethodOutput->pusRespLen, usRespLen);

    PPPC_EAP_SendResponse(pstMethodOutput->ulPppId);

    PPPC_EAP_PeerProcessEvent(pstMethodOutput->ulPppId,
            PPPC_EAP_PEER_AUTH_IND_EVENT, VOS_NULL_PTR);

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

