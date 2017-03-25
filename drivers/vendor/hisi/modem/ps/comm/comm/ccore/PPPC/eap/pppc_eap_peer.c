/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_eap_peer.c
  �� �� ��   : ����
  ��    ��   : c00184031
  ��������   : 2015��11��7��
  ����޸�   :
  ��������   : EAP Peer״̬������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��7��
    ��    ��   : c00184031
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "ppp_inc.h"
#include "pppc_eap_aka.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_PEER_C
/*lint +e767*/



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
/* �¼�״̬������ */
PPPC_EAP_PEER_EVENT_PROC_FUNC g_pfunEventProc[PPPC_EAP_PEER_STATE_BUTT][PPPC_EAP_PEER_EVENT_BUTT] =
{
    /* PPPC_EAP_PEER_IDLE_STATE */
    {
        PPPC_EAP_PeerIdleIdentityReq,
        PPPC_EAP_PeerNotifyReq,
        PPPC_EAP_PeerIdleNak,
        PPPC_EAP_PeerIdleAuthReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerIdleSuccess,
        PPPC_EAP_PeerIdleFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_AUTHENTICATING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerAuthAuthReq,
        PPPC_EAP_PeerAuthNotifyAuthInd,
        PPPC_EAP_PeerAuthNotifySuccess,
        PPPC_EAP_PeerAuthNotifyFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_NOTIFYING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerNotifyAuthReq,
        PPPC_EAP_PeerAuthNotifyAuthInd,
        PPPC_EAP_PeerAuthNotifySuccess,
        PPPC_EAP_PeerAuthNotifyFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_CLOSING_STATE */
    {
        VOS_NULL_PTR,
        PPPC_EAP_PeerClosingNotifyReq,
        VOS_NULL_PTR,
        PPPC_EAP_PeerClosingAuthReq,
        PPPC_EAP_PeerClosingAuthInd,
        PPPC_EAP_PeerClosingSuccess,
        PPPC_EAP_PeerClosingFailure,
        PPPC_EAP_PeerTimeout,
    },
    /* PPPC_EAP_PEER_CLOSED_STATE */
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
    }
};

/* ���������� */
PPPC_EAP_METHOD_CB_STRU g_stMethodProcCB[PPPC_EAP_INTERNAL_TYPE_BUTT] =
{
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
    },
    {
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        VOS_NULL_PTR,
        PPPC_EAP_MD5_ProcessPkt,
        VOS_NULL_PTR,
    },
    {
        PPPC_EAP_AKA_Init,
        PPPC_EAP_AKA_InitState,
        PPPC_EAP_AKA_NotifyResult,
        PPPC_EAP_AKA_ProcessPkt,
        PPPC_EAP_AKA_PreProcessPkt,
    },
    {
        PPPC_EAP_AKA_Init,
        PPPC_EAP_AKA_InitState,
        PPPC_EAP_AKA_NotifyResult,
        PPPC_EAP_AKA_ProcessPkt,
        PPPC_EAP_AKA_PreProcessPkt,
    }
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : PPPC_EAP_PreferIdenType
 ��������  : ��ȡIdentity�Ĳ��ԣ�Ŀǰֻ�᷵��AKA'���ͣ��ӿں�������չʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : PPPC_EAP_METHODS_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PPPC_EAP_METHODS_TYPE_ENUM_UINT8 PPPC_EAP_PreferIdenType(VOS_VOID)
{
    return PPPC_EAP_AKA_PRIME_TYPE;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_InitState
 ��������  : ��ʼ��������PEER��״̬
 �������  : pstEapInfo     EAPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_InitState
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    /* ��ȨЭ�̽���,��ʼ��������״̬  */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethodState)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethodState();
    }

    /* ��ʼ��PEER��״̬ */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_IDLE_STATE;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_SyncState
 ��������  : ��������ļ�Ȩ��������Ƿ�ȷ�ϵģ���������п��ܱ�������������
             ��Ȩ״̬��һ�£�������˼�Ȩ�����OK����û���յ�����ļ�Ȩ�ɹ�
             ����ȴ�յ���VSNCP���ģ�˵�������Ѿ���Ȩͨ���ˣ�ֱ�ӽ�״̬Ǩ��
             ��PPP_PHASE_NETWORK
 �������  : pstPppInfo     PPPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EAP_SyncState(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                  *pstEapInfo;


    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create");
        return;
    }

    /* ɾ����ʱ�� */
    PPPC_EAP_DeleteTimer(pstEapInfo);

    if ((VOS_OK == pstEapInfo->ulLocalResult)
        && (PPPC_EAP_PEER_CLOSING_STATE == pstEapInfo->enEapPeerState))
    {
        PPPC_EAP_InitState(pstEapInfo);

        pstPppInfo->bAuthClient = VOS_NO;

        pstPppInfo->usPhase = (VOS_UINT16)PPP_PHASE_NETWORK;
    }
    else
    {
        PPPC_WARNING_LOG2("Enter VSNCP without auth result of AN",
            pstEapInfo->ulLocalResult, pstEapInfo->enEapPeerState);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_InitMethod
 ��������  : ��ʼ������
 �������  : pstEapInfo     EAPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_InitMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    if ((pstEapInfo->enInterType < PPPC_EAP_INTERNAL_MD5_TYPE)
        || (pstEapInfo->enInterType >= PPPC_EAP_INTERNAL_TYPE_BUTT))
    {
        /* LCP UPʱ�ڲ�ӳ�����Ϳ���Ϊ��ʼֵ����ʱ����Ҫ��ʼ������ */
        return;
    }

    /* ������ʼ�� */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod(pstEapInfo->enSelectMethod);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_FillPayload
 ��������  : ���TYPE-DATA��
 �������  : pstEapInfo     EAPʵ����Ϣ
             aucTypeData    TYPE-DATA��
             usTypeDataLen  TYPE-DATA�򳤶�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_FillPayload
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    VOS_UINT8                           aucTypeData[],
    VOS_UINT16                          usTypeDataLen
)
{
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    VOS_UINT16                          usPktLen;


    /* ���payload�� */
    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;
    pstRespPayload->enEAPType   = pstEapInfo->enRequestType;

    usPktLen    = (VOS_UINT16)(PPPC_EAP_HEADERLEN
                + PPPC_EAP_TYPE_FIELD_LEN + usTypeDataLen);

    /* EAP���ĳ������ */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    /* ƫ�ƹ�Code+Id+Len+Type����TYPE-DATA��ʼ���� */
    PS_MEM_CPY(pstEapInfo->aucRespPkt + PPPC_EAP_HEADERLEN
            + PPPC_EAP_TYPE_FIELD_LEN, aucTypeData, usTypeDataLen);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_GetSupportMethodList
 ��������  : ��ȡIdentity�Ĳ��ԣ�Ŀǰֻ�᷵��AKA'���ͣ��ӿں�������չʹ��
 �������  : aenMethod          ָʾ����ķ���
 �������  : pucMethodNum       �����ĸ���
 �� �� ֵ  : PPPC_EAP_METHODS_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_GetSupportMethodList
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethod[],
    VOS_UINT8                          *pucMethodNum
)
{
    aenMethod[0]    = PPPC_EAP_AKA_PRIME_TYPE;
    aenMethod[1]    = PPPC_EAP_AKA_TYPE;
    aenMethod[2]    = PPPC_EAP_MD5_TYPE;

    *pucMethodNum   = 3;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_GetMethod
 ��������  : ��ȡѡ�еķ���
 �������  : pstEapInfo         EAPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK:��ѡ�кϷ��ķ��� VOS_ERR:δѡ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_GetMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    /* �ڲ����ã���֤��ηǿ� */

    if ((pstEapInfo->enSelectMethod <= PPPC_EAP_NAK_TYPE)
        || (PPPC_EAP_EXPAND_NAK_TYPE == pstEapInfo->enSelectMethod))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_MappingMethodType
 ��������  : ��Init״̬���յ�Identity Req�Ĵ���
 �������  : enType             Э��涨�ķ�������
 �������  : penInternalType    �ڲ�ӳ��ķ�������
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_MappingMethodType
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8            enType,
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8  *penInternalType
)
{
    VOS_UINT32                          ulRet = VOS_OK;


    switch (enType)
    {
        case PPPC_EAP_MD5_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_MD5_TYPE;

            break;

        case PPPC_EAP_AKA_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_AKA_TYPE;

            break;

        case PPPC_EAP_AKA_PRIME_TYPE:

            *penInternalType = PPPC_EAP_INTERNAL_AKA_PRIME_TYPE;

            break;

        default:

            ulRet   = VOS_ERR;
            PPPC_WARNING_LOG1("Invalid input type", enType);

            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_SelectMethod
 ��������  : ѡ�񷽷�
 �������  : pstEapInfo     EAPʵ����Ϣ
             enMethod       ��Ҫѡ��ķ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_SelectMethod
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethod
)
{
    PPPC_EAP_METHODS_INTERNAL_TYPE_ENUM_UINT8   enInterType;
    VOS_UINT32                                  ulRet;


    /* �ڲ����ã���֤��κϷ� */

    /* ӳ�䵽�ڲ����� */
    ulRet   = PPPC_EAP_MappingMethodType(enMethod, &enInterType);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    pstEapInfo->enSelectMethod  = enMethod;

    pstEapInfo->enInterType = enInterType;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_MethodProc
 ��������  : ���÷����Ļص�����������
 �������  : pstEapInfo     EAPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EAP_MethodProc
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_HEADER_STRU               *pstPayload;
    PPPC_EAP_HEADER_STRU               *pstRespPkt;
    PPPINFO_S                          *pstPppInfo;
    PPPC_EAP_METHOD_OUTPUT_STRU         stMethodOutput;
    PPPC_EAP_METHOD_INPUT_STRU          stMethodInput;
    VOS_UINT16                          usPktLen;
    PS_BOOL_ENUM_UINT8                  enPreProcResult = PS_FALSE;


    /* �ڲ����ñ�ָ֤��ǿ� */

    pstPppInfo   = pstEapInfo->pstPppInfo;
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("PPP did not create!");
        return PS_FALSE;
    }

    pstPayload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enInterType >= PPPC_EAP_INTERNAL_TYPE_BUTT)
    {
        PPPC_WARNING_LOG2("Invalid method type",
                pstEapInfo->enInterType, pstEapInfo->enSelectMethod);
        return PS_FALSE;
    }

    /* ���ö�Ӧ���������� */
    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncProcMethodPkt)
    {
        /* ���Response����ͷ */
        pstRespPkt  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
        pstRespPkt->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
        pstRespPkt->ucEAPID     = pstPayload->ucEAPID;
        pstRespPkt->enEAPType   = pstPayload->enEAPType;

        usPktLen    = PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN;

        /* EAP���ĳ������ */
        PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

        /* ��װ�������� */
        stMethodOutput.ulPppId      = pstPppInfo->ulRPIndex;
        stMethodOutput.pucPktData   = pstEapInfo->aucRespPkt;
        stMethodOutput.pusRespLen   = &(pstEapInfo->usRespPktLen);

        /* ��䷽����� */
        stMethodInput.ucEAPID   = pstPayload->ucEAPID;
        stMethodInput.usEAPLen  = VOS_NTOHS(pstPayload->usEAPLen);
        stMethodInput.enEAPType = pstPayload->enEAPType;
        stMethodInput.pucPktData= (VOS_UINT8 *)pstPayload;

        /* ����Ԥ�����������Ƿ���Ҫ�е�Auth״̬ */
        if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncPreProc)
        {
            enPreProcResult = g_stMethodProcCB[pstEapInfo->enInterType].pfuncPreProc(&stMethodInput);
        }

        g_stMethodProcCB[pstEapInfo->enInterType].pfuncProcMethodPkt(&stMethodOutput, &stMethodInput);
    }

    return enPreProcResult;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_FillNakResponse
 ��������  : ���NAK Response��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_FillNakResponse
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethodList[PPPC_EAP_TYPE_BUTT];
    VOS_UINT16                          usPktLen;
    VOS_UINT8                           ucMethodNum;


    /* ��ȡ������֧�ֵķ����б� */
    ulRet = PPPC_EAP_GetSupportMethodList(aenMethodList, &ucMethodNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get method list fail!", ulRet);
        return VOS_ERR;
    }

    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;
    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;
    pstRespPayload->enEAPType   = PPPC_EAP_NAK_TYPE;

    usPktLen    = PPPC_EAP_HEADERLEN
                + PPPC_EAP_TYPE_FIELD_LEN + ucMethodNum;

    /* EAP���ĳ������ */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    PS_MEM_CPY(pstEapInfo->aucRespPkt + PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN,
            aenMethodList, ucMethodNum);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_FillExpandNakResponse
 ��������  : �����չNAK Response��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_EAP_FillExpandNakResponse
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_HEADER_STRU               *pstRespPayload;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    aenMethodList[PPPC_EAP_TYPE_BUTT];
    PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU *pstExpandNakData;
    VOS_UINT8                           ucMethodNum;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulType;
    VOS_UINT16                          usPktLen;


    /* ��ȡ������֧�ֵķ����б� */
    ulRet = PPPC_EAP_GetSupportMethodList(aenMethodList, &ucMethodNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get method list fail!", ulRet);
        return VOS_ERR;
    }

    pstRespPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;

    pstRespPayload->ucEAPCode   = PPPC_EAP_RESPONSE_TYPE;
    pstRespPayload->ucEAPID     = pstEapInfo->ucRequestID;

    /* Э��ο�RFC3748,chapter 5.3 */
    /*0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     2         |  Identifier   |           Length=28           |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                3 (Nak)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                4 (MD5)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                23(AKA)                        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |   Type=254    |                0 (IETF)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                                50(AKA')                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    usPktLen    = (VOS_UINT16)(PPPC_EAP_HEADERLEN
                + (PPPC_EAP_EXPAND_NAK_ELEM_LEN * (ucMethodNum + 1)));

    /* EAP���ĳ������ */
    PPPC_EAP_UpdateLen(pstEapInfo->aucRespPkt, &(pstEapInfo->usRespPktLen), usPktLen);

    pstExpandNakData = (PPPC_EAP_EXPAND_NAK_TYPE_DATA_STRU *)(((VOS_UINT8 *)pstRespPayload) + PPPC_EAP_HEADERLEN);
    pstExpandNakData->enEAPType = PPPC_EAP_EXPAND_NAK_TYPE;
    ulType                      = PPPC_EAP_NAK_TYPE;
    pstExpandNakData->ulType    = VOS_HTONL(ulType);
    pstExpandNakData++;

    for (ulLoop = 0; ulLoop < ucMethodNum; ulLoop++)
    {
        pstExpandNakData->enEAPType = PPPC_EAP_EXPAND_NAK_TYPE;
        ulType                      = aenMethodList[ulLoop];
        pstExpandNakData->ulType    = VOS_HTONL(ulType);
        PS_MEM_SET(pstExpandNakData->aucIETF, 0, sizeof(pstExpandNakData->aucIETF));
        pstExpandNakData++;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerTransferState
 ��������  : PEER״̬״̬����
 �������  : pstEapInfo     EAPʵ��
             enEvent        �¼�֪ͨ
             pData          ���Ļ���������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerTransferState
(
    PPPC_EAP_INFO_STRU                 *pstEapInfo,
    PPPC_EVENT_USER_DATA               *pstPppEventData
)
{
    /* ״̬Ǩ�� */
    pstEapInfo->enEapPeerState  = (PPPC_EAP_PEER_STATE_MACHINE_ENUM_UINT16)pstPppEventData->ulNewState;

    /* �ϱ��¼� */
    PPPC_MNTN_SndEvent(MSPS_PID_PPPC, DIAG_MODE_COMM, PPPC_LOG_EVENT_STATE_UPDATE,
            pstPppEventData, sizeof(PPPC_EVENT_USER_DATA));

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerProcessEvent
 ��������  : PEER״̬���¼�֪ͨ
 �������  : pstEapInfo     EAPʵ��
             enEvent        �¼�֪ͨ
             pData          ���Ļ���������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerProcessEvent
(
    VOS_UINT32                          ulPppId,
    PPPC_EAP_PEER_EVENT_ENUM_UINT16     enEvent,
    VOS_VOID                           *pData
)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* ָ���ڵ��ô��Ѿ��пռ�� */

    if (PPP_MAX_USER_NUM < ulPppId)
    {
        PPPC_WARNING_LOG1("Invalid input ppp id", ulPppId);
        return;
    }

    pstPppInfo                  = &g_astPppPool[ulPppId];
    pstEapInfo                  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG1("EAP did not create", ulPppId);
        return;
    }

    /* ������ */
    if (enEvent >= PPPC_EAP_PEER_EVENT_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid input param!", enEvent);
        return;
    }

    if (pstEapInfo->enEapPeerState >= PPPC_EAP_PEER_STATE_BUTT)
    {
        PPPC_WARNING_LOG2("Invalid state", pstEapInfo->enEapPeerState, enEvent);
        return;
    }

    /* PEER״̬�������� */
    if (VOS_NULL_PTR != g_pfunEventProc[pstEapInfo->enEapPeerState][enEvent])
    {
        g_pfunEventProc[pstEapInfo->enEapPeerState][enEvent](pstPppInfo, pData);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerIdleIdentityReq
 ��������  : ��Idle״̬���յ�Identity Req�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleIdentityReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucIdentity[PPPC_EAP_ID_MAX_LEN];
    VOS_UINT16                          usIdentityLen;
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* ��ȡIdenity�Ĳ��ԣ�Ŀǰֻ���ȡAKA'���� */
    enMethodType    = PPPC_EAP_PreferIdenType();

    /* ��ȡIdentity */
    ulRet   = PPPC_EAP_GetIdentity(enMethodType, aucIdentity, &usIdentityLen);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get identity fail!", ulRet);
        return;
    }

    if ((usIdentityLen >= PPPC_EAP_ID_MAX_LEN) || (0 == usIdentityLen))
    {
        PPPC_WARNING_LOG1("Get identity len invalid!", usIdentityLen);
        return;
    }

    /* Stay in Init State */

    /* ���TYPE-DATA�� */
    /*  TYPE  |  TYPE-DATA */
    /* 1Byte  |  type-data len */
    PPPC_EAP_FillPayload(pstEapInfo, aucIdentity, usIdentityLen);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerNotifyReq
 ��������  : ��Init״̬���յ�Notify Req�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Stay in Init State */

    /* ��дRESPONSE */
    PPPC_EAP_FillPayload(pstEapInfo, VOS_NULL_PTR, 0);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerIdleNak
 ��������  : ��Idle״̬���յ�NAK�¼��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleNak
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstpktPayload;
    VOS_UINT32                          result;


    /* PPPʵ���п��Ѿ��ڵ��ô�������� */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Stay in Init State */

    pstpktPayload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (PPPC_EAP_EXPAND_NAK_TYPE == pstpktPayload->enEAPType)
    {
        result = PPPC_EAP_FillExpandNakResponse(pstEapInfo);
    }
    else
    {
        result = PPPC_EAP_FillNakResponse(pstEapInfo);
    }

    if (VOS_OK == result)
    {
        PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);
    }
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerIdleAuthReq
 ��������  : ��Idle״̬���յ���Ȩ���ĵĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    VOS_UINT32                          ulRet;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPPʵ���п��Ѿ��ڵ��ô�������� */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    /* ��ȡ��ѡ�񷽷�,ͬʱ��ʼ����Ӧ�����Ĵ����� */
    ulRet       = PPPC_EAP_GetMethod(pstEapInfo);
    if (VOS_OK != ulRet)
    {
        ulRet   = PPPC_EAP_SelectMethod(pstEapInfo, pstPaload->enEAPType);
        if (VOS_OK != ulRet)
        {
            return;
        }

        /* ��ʼ����Ȩ��� */
        pstEapInfo->ulLocalResult   = VOS_ERR;
        pstEapInfo->ulRemoteResult  = VOS_ERR;

        /* ��ʼ������ */
        if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod)
        {
            g_stMethodProcCB[pstEapInfo->enInterType].pfuncInitMethod(pstEapInfo->enSelectMethod);
        }
    }

    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* Ǩ�Ƶ�Authenticating״̬ */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerIdleSuccess
 ��������  : ��Idle״̬���յ�SUCCESS���ĵĴ���
 �������  : pstPppInfo     PPPʵ����Ϣ
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    /* �ڲ����ñ�֤��ηǿ� */

    /* ��ʱ��ҪǨ�Ƶ�CLOSED״̬��Ȼ��Э�̳ɹ���PEER����Ҫ�ָ���INIT״̬
        ���״̬������ҪǨ�ƣ��Ծɱ�����INIT״̬ */

    /* ���ͼ�Ȩ�ɹ��¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, NULL);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerIdleFailure
 ��������  : ��Init״̬���յ�FAILURE���ĵĴ���
 �������  : pstPppInfo     PPPʵ����Ϣ
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerIdleFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    /* �ڲ����ñ�֤��ηǿ� */

    /* ��ʱ��ҪǨ�Ƶ�CLOSED״̬��Ȼ��Э��ʧ�ܺ�PEER����Ҫ�ָ���INIT״̬
        ���״̬������ҪǨ�ƣ��Ծɱ�����INIT״̬ */

    PPPC_EAP_Init(pstPppInfo);

    /* ���ͼ�Ȩʧ���¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, NULL);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerTimeout
 ��������  : ��ȨЭ�̳�ʱ����
 �������  : ulPppId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerTimeout(PPPINFO_S *pstPppInfo, VOS_VOID *pData)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;

    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("Did not create EAP!");
    }

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

    PPPC_EAP_Init(pstPppInfo);

    /* ���ͼ�Ȩʧ���¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerAuthAuthReq
 ��������  : ��AUTH״̬���յ���Ȩ�����ı���
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;


    /* PPPʵ���п��Ѿ��ڵ��ô�������� */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }

    /* ��ͣ����AUTH״̬ */

    (VOS_VOID)PPPC_EAP_MethodProc(pstEapInfo, pData);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerAuthNotifyAuthInd
 ��������  : ��AUTH/NOTIFY״̬���յ������ĳɹ���ʧ��ָʾ
 �������  : pstPppInfo     PPPʵ��
             pData          ���˼�Ȩ�ɹ���ʧ��ָʾ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifyAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;


    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Input data is null!");
        return;
    }

    /* PPPʵ���Ѿ��ڵ��ô��п� */
    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulLocalResult   = *(VOS_UINT32 *)pData;

    /* Ǩ�Ƶ�CLOSING״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerAuthNotifySuccess
 ��������  : ��AUTH/NONTIFY״̬���յ�����ļ�Ȩ�ɹ���Ϣ
 �������  : pstPppInfo     PPPʵ��
             pData          ���˼�Ȩ�ɹ���ʧ��ָʾ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifySuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Ǩ�Ƶ�CLOSING״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = pstEapInfo->enEapPeerState;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    /* �洢����ļ�Ȩ��� */
    pstEapInfo->ulRemoteResult  = VOS_OK;

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_OK);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerAuthNotifyFailure
 ��������  : ��AUTH/NOTIFY״̬���յ������ʧ����Ϣ
 �������  : pstPppInfo     PPPʵ��
             pData          ���˼�Ȩ�ɹ���ʧ��ָʾ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerAuthNotifyFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* �洢����ļ�Ȩ��� */
    pstEapInfo->ulRemoteResult  = VOS_ERR;

    /* Ǩ�Ƶ�CLOSED״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_ERR, &stPppAuthInfo);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_ERR);
    }

    PPPC_EAP_Init(pstPppInfo);

    /* ���ͼ�Ȩʧ���¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerNotifyAuthReq
 ��������  : ��NOTIFY״̬���յ�����ļ�Ȩ��Ϣ
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerNotifyAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPPʵ���п��Ѿ��ڵ��ô�������� */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }

    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* Ǩ�Ƶ�AUTH״̬ */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = PPPC_EAP_PEER_NOTIFYING_STATE;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerClosingNotifyReq
 ��������  : ��CLOSING״̬���յ�NOTIFY��Ϣ
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingNotifyReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Ǩ�Ƶ�NOTIFYING״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_NOTIFYING_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    /* ���TYPE-DATA�� */
    /* ����һ���ֽڵ�TYPE�� */
    pstEapInfo->enRequestType   = PPPC_EAP_NOTIFY_TYPE;
    PPPC_EAP_FillPayload(pstEapInfo, VOS_NULL_PTR, 0);

    PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);

    /* Ǩ�Ƶ�CLOSING״̬ */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_CLOSING_STATE;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerClosingAuthReq
 ��������  : ��CLOSING״̬���յ�AUTH��Ϣ
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingAuthReq
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EAP_HEADER_STRU               *pstPaload;
    PPPC_EVENT_USER_DATA                stPppEventData;
    PS_BOOL_ENUM_UINT8                  enPreProcResult;


    /* PPPʵ���п��Ѿ��ڵ��ô�������� */

    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Data is null!");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstPaload   = (PPPC_EAP_HEADER_STRU *)pData;

    if (pstEapInfo->enSelectMethod != pstPaload->enEAPType)
    {
        PPPC_WARNING_LOG2("Method mismach!",
                pstEapInfo->enSelectMethod, pstPaload->enEAPType);
        return;
    }


    enPreProcResult = PPPC_EAP_MethodProc(pstEapInfo, pData);
    if (PS_TRUE == enPreProcResult)
    {
        /* Ǩ�Ƶ�AUTH״̬ */
        PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
        stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
        stPppEventData.ulNewState   = PPPC_EAP_PEER_AUTHENTICATING_STATE;
        stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
        stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
        stPppEventData.ucPdnId      = 0xff;
        PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerClosingAuthInd
 ��������  : ��CLOSING״̬���յ����˼�Ȩ���
 �������  : pstPppInfo     PPPʵ��
             pData          ���˼�Ȩ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingAuthInd
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    if (VOS_NULL_PTR == pData)
    {
        PPPC_WARNING_LOG("Input data is null!");
        return;
    }

    /* PPPʵ���Ѿ��ڵ��ô��п� */
    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulLocalResult   = *(VOS_UINT32 *)pData;

    /* Ǩ�Ƶ�CLOSED״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    if ((VOS_OK == pstEapInfo->ulLocalResult) && (VOS_OK == pstEapInfo->ulRemoteResult))
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                        PPP_EAP, VOS_OK, &stPppAuthInfo);

        /* ɾ����ʱ�� */
        PPPC_EAP_DeleteTimer(pstEapInfo);

        /* ��Ȩ�ɹ���ʼ��PEER�ͷ�����״̬ */
        PPPC_EAP_InitState(pstEapInfo);

        /* ���ͼ�Ȩ�ɹ��¼� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, VOS_NULL_PTR);
    }
    else
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

        /* ��Ȩʧ����ȫ��� */
        PPPC_EAP_Init(pstPppInfo);

        /* ���ͼ�Ȩʧ���¼� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerClosingSuccess
 ��������  : ��CLOSING״̬���յ�����ĳɹ�����
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingSuccess
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    /* Ǩ�Ƶ�CLOSED״̬,���ϱ���ά�ɲ� */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_OK);
    }

    pstEapInfo->ulRemoteResult  = VOS_OK;
    if ((VOS_OK == pstEapInfo->ulLocalResult) && (VOS_OK == pstEapInfo->ulRemoteResult))
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_OK, &stPppAuthInfo);

        /* ɾ����ʱ�� */
        PPPC_EAP_DeleteTimer(pstEapInfo);

        /* ��Ȩ�ɹ���ʼ��PEER�ͷ�����״̬ */
        PPPC_EAP_InitState(pstEapInfo);

        /* ���ͼ�Ȩ�ɹ��¼� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPSUCCESS, VOS_NULL_PTR);
    }
    else
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                    PPP_EAP, VOS_ERR, &stPppAuthInfo);

        /* ��Ȩʧ����ȫ��� */
        PPPC_EAP_Init(pstPppInfo);

        /* ���ͼ�Ȩʧ���¼� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_PeerClosingFailure
 ��������  : ��CLOSING״̬���յ������ʧ�ܱ���
 �������  : pstPppInfo     PPPʵ��
             pData          ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_PeerClosingFailure
(
    PPPINFO_S                          *pstPppInfo,
    VOS_VOID                           *pData
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo  = VOS_NULL_PTR;
    PPPC_EVENT_USER_DATA                stPppEventData;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    /* �ڲ����ñ�֤��ηǿ� */

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("EAP did not create!");
        return;
    }

    pstEapInfo->ulRemoteResult  = VOS_ERR;

    /* Ǩ�Ƶ�CLOSED״̬ */
    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = PPPC_EAP_PEER_CLOSING_STATE;
    stPppEventData.ulNewState   = PPPC_EAP_PEER_CLOSED_STATE;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP;
    stPppEventData.ucPdnId      = 0xff;
    PPPC_EAP_PeerTransferState(pstEapInfo, &stPppEventData);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_EAP, VOS_ERR, &stPppAuthInfo);

    if (VOS_NULL_PTR != g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes)
    {
        g_stMethodProcCB[pstEapInfo->enInterType].pfuncNotifyMethodRes(VOS_ERR);
    }

    PPPC_EAP_Init(pstPppInfo);

    /* ���ͼ�Ȩʧ���¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_EAPFAILED, VOS_NULL_PTR);

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
