/************************************************************************
*                                                                      *
*                             chap.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/05                                      *
*  Author:             Zhu Fengzhi                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��CHAPЭ��ģ��                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������CHAPЭ��ģ���ȫ���ӿں������ڲ�������             *
*                                                                      *
************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "ppp_func.h"
#include "pppc_uim.h"
#include "pppc_md5.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CHAP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
PS_BOOL_ENUM_UINT8  g_enGetChapRespSelf = PS_TRUE;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP��ʼ��CHAP���ƿ�                                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_CHAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo;
    PPPCONFIGINFO_S *pstConfig;


    /* ��ʼ��Ϊ�Լ���Resposne */
    g_enGetChapRespSelf = PS_TRUE;

    if (pstPppInfo == 0)
    {
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((pstChapInfo == 0) || (pstConfig == 0))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_35);
        return;
    }

    PPP_MemSet((VOID*)pstChapInfo, 0, sizeof(PPPCHAPINFO_S));

    pstChapInfo->pstPppInfo = pstPppInfo;
    pstChapInfo->ucUsed = 1;
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    pstChapInfo->ulTimeOutTime  = pstConfig->ulNegTimeOut;
    pstChapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;

    /*����������֤���, �ݲ������˹���*/
    pstChapInfo->ulChalInterval = 0;

    /*����hash�㷨*/
    pstChapInfo->ucRespType = CHAP_DIGEST_MD5;
    pstChapInfo->ucChalType = CHAP_DIGEST_MD5;

    pstChapInfo->ulWaitAuthRspTimeout = CHAP_WAITAAARSPTIMEOUT;
    pstChapInfo->ulAuthMaxTransmits = CHAP_MAXAUTHTRANSMITS;
    pstChapInfo->ucAuthTransmits  = 0;
    pstChapInfo->pstAAAAuthReqMsg = NULL;
    pstChapInfo->ulWaitLnsAuthTimeOut = CHAP_WAITLNSAUTHTIME;

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�����ⲿ�¼�.�¼�������ClientUp��ServerUp��Down            *                                           Open��Close            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������, ����Ϊ����ֵ:                                *
*                    CHAP_EVENT_CLIENTLOWERUP:�����²�UP                        *
*                    CHAP_EVENT_SERVERLOWERUP:�Զ��²�UP                        *
*                    CHAP_EVENT_LOWERDOWN:�²�DOWN                            *
*                pPara:�¼��Ĳ���, ΪNULL                                   *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Core_ReceiveEventFromShell                                *
****************************************************************************/
VOID PPP_CHAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, CHAR *pPara)
{
    if (pstPppInfo == 0)
    {
        return;
    }

    switch (ulCmd)
    {
        case CHAP_EVENT_CLIENTLOWERUP:
            PPP_CHAP_ClientLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_SERVERLOWERUP:
            PPP_CHAP_ServerLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_LOWERDOWN:
            PPP_CHAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_36);

            /*������������Ϣ*/
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP Receive UNKNOWN Event!");
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP Client ��LowerUp,�ɶԶ���֤�Ҷ�                        *
*                 ����CHAP_STATE_LISTEN_CHALLENGE״̬, �ȴ��Զ��ͳ�CHALLENGE    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ClientLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;
    VOS_UINT32                          ulRet;


    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_37);
        return;
    }

    ulRet = PPP_GetConfigUserName(pstChapInfo->szHostName, pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get username fail when chap client up.");
    }

    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    /* ����¼�������Ϣ */
    CHAP_Debug_Event(pstPppInfo, CHAP_CLIENTLOWERUP);

    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_LISTEN_CHALLENGE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_LISTEN_CHALLENGE;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP Server ��LowerUp,���Ҷ���Զ˷���Challenge             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;

    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_38);
        return;
    }

    (VOID)VOS_StrCpy((VOS_CHAR *)pstChapInfo->szHostName, (VOS_CHAR *)pstConfig->cChapHostName);
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;

    /* ����¼�������Ϣ */
    CHAP_Debug_Event(pstPppInfo, CHAP_SERVERLOWERUP);

    PPP_CHAP_GenChallenge(pstChapInfo);        /* ����challenge */
    PPP_CHAP_SendChallenge(pstPppInfo);        /* �ͳ�challenge */

    PPP_PerfInc(&g_stPppPerfStatistic.ulChapTotal, PERF_TYPE_PPPC_CHAP_AUTHEN_NUM, pstPppInfo->bEhrpdUser);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAPLowerDown                                                *
*                 ����CHAP_STATE_SERVER_INITIAL ,CHAP_STATE_CLIENT_INITIAL״̬        *
*                 ͬʱɾ����ʱ��                                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_40);
        return;
    }

    /* ����¼�������Ϣ */
    CHAP_Debug_Event(pstPppInfo, CHAP_LOWERDOWN);

    /* ɾ����ʱ�� */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    /* ���������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_INITIAL, CHAP_CLIENT_STATE);
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_INITIAL, CHAP_SERVER_STATE);

    /* �ı�״̬ */
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ�chap ���ݰ�, ��������ͷ������Ӧ����                *
*                pHead:��ű����ڴ��ͷָ�����Э���, Ӧ�����ͷ�����ڴ�   *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_CHAP_ReceivePacket (PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S *pstChapInfo;
    UCHAR ucCode, ucId;
    VOS_UINT32 ulCiLen;

    PPPC_INFO_LOG("\r\n-------enter PPP_CHAP_ReceivePacket--------");
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_41);
        PPPC_INFO_LOG("pstPppInfo == 0");
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_42);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "pstChapInfo == 0");
        return;
    }

    /*����¼�������Ϣ*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_CHAP, 1);

    /*��������ͷ(ucCode,ucId, length)*/

    if (ulLen < FSM_HDRLEN)        /* ������İ�̫������ */
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_43);
        return;
    }

    /* ��ñ������ֶ�ֵ, ���ƶ�����ָ�� */
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if (ulCiLen < CHAP_HEADERLEN)
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_44);
        return;
    }

    ulCiLen -= CHAP_HEADERLEN;

    /* ���� ucCode ������Ӧ�Ķ��� */
    switch (ucCode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
            PPP_CHAP_ReceiveChallenge(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_RESPONSE:
            PPP_CHAP_ReceiveResponse(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_FAILURE:
            PPP_CHAP_ReceiveFailure(pstPppInfo);
            break;

        case CHAP_PACKET_CODE_SUCCESS:
            PPP_CHAP_ReceiveSuccess(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_45);
            PPP_CHAP_ReceiveUnknownCode(pstPppInfo);
            break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_CHAP_GetHrpdResponse
 ��������  : PPPCģ��֪ͨSIM������CHAP��Ȩresponseֵ,�����ݿ����;���ʹ��MD5����CAVE�㷨
 �������  : pstPppInfo    Я��PPP��Ϣ
             pstMsg        ���췢�͸�������response����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-08-27
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_CHAP_GetHrpdResponse
(
    PPPINFO_S                          *pstPppInfo,
    PPPC_AUTH_MSG_STRU                 *pstMsg
)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT32                          ulRandu = 0;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    PS_BOOL_ENUM_UINT8                  enIsMD5AlgorithmEnable;


    /* �����HRPDģʽ����USIM��������Response */
    enRatMode = PPPC_GetRatMode();
    if ((PPPC_RAT_MODE_HRPD == enRatMode) || (PPPC_RAT_MODE_EHRPD == enRatMode))
    {
        /*lint -e701*/
        ulRandu = ((VOS_UINT8)(pstMsg->szPwd[0]) << 24)
                 | ((VOS_UINT8)(pstMsg->szPwd[1]) << 16)
                 | ((VOS_UINT8)(pstMsg->szPwd[2]) << 8)
                 | ((VOS_UINT8)(pstMsg->szPwd[3]));
        /*lint +e701*/
        PPPC_SaveRunCaveRandu(ulRandu);

        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        enIsMD5AlgorithmEnable  = PPPC_MD5Active();
        /* ��֧��CAVE�㷨 �� ֧��CAVE�㷨��MD5�㷨���� ʱ��USIM��ʹ��MD5�㷨 */
        if ((PS_FALSE == enIsCaveAlgorithmEnable) || (PS_TRUE == enIsMD5AlgorithmEnable))
        {
            /* ʹ��MD5�㷨 */
            PPPC_UIM_MD5ChapAuthReq(pstPppInfo, pstMsg);
            return VOS_OK;
        }
        else
        {
            /* ʹ��CAVE�㷨 */
            PPPC_UIM_RunCaveAuthReq(ulRandu);
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG2("It is 1X mode,should not let sim compute response\r\n", enRatMode, ulRandu);

    return VOS_ERR;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ��Զ˵�Challenge��                                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveChallenge(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S                      *pstChapInfo;
    PPPC_AUTH_MSG_STRU                  stMsg;
    VOS_INT32                           lLen = (VOS_INT32)ulLen;
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (pstPppInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_46);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_47);
        return;
    }

    PPP_MemSet((VOID *)&stMsg, 0, sizeof(PPPC_AUTH_MSG_STRU));

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVECHALLENGE);
    if (pstChapInfo->ucClientState == CHAP_STATE_CLIENT_INITIAL)
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP receive Challenge packet on CHAP_STATE_CLIENT_INITIAL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_48);
        return;
    }

    /*ȡ��Challenge,���ڲ���Response*/
    PPP_GETCHAR(stMsg.ucPwdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )stMsg.szPwd, pPacket, (VOS_UINT32)stMsg.ucPwdLen);

    /*pPacketָ���ƶ�*/
    PPP_INCPTR(stMsg.ucPwdLen, pPacket);

    /* ����Name�򳤶� */
    lLen -= (LONG)sizeof (UCHAR) + (LONG)(stMsg.ucPwdLen);
    if (lLen < 0) /*�Ƿ����*/
    {
        /*������������Ϣ*/
        PPP_DBG_ERR_CNT(PPP_PHERR_49);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    if (lLen >= PPP_MAXUSERNAMELEN)   /*�Ƿ����*/
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_50);
        lLen = PPP_MAXUSERNAMELEN;
    }

    /*����Challenge ID*/
    pstChapInfo->ucRespId = ucId;

    /*ȡ�öԶ�Hostname,���ڲ���Response*/
    stMsg.ucUsrNameLen = (UCHAR )lLen;
    (VOID)VOS_MemCpy((CHAR * )stMsg.szUsrName, pPacket, (VOS_UINT32)lLen);

    /*ȡ��Challeng Id,���ڲ���Response */
    stMsg.ucPktID = ucId;

    /*ɾ���ȴ�RespTimeoutID��ʱ��ʱ��*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /* �����Ȩ����Ҫ�ӽڵ��ȡ���� */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        /* �����Ȩ������SIM����,�����ڲ���MD5/CAVE�㷨���߳ɹ�ʧ�ܶ�ֱ���˳� */
        (VOS_VOID)PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        return;
    }
    else
    {
        /*ȡ���ص�password,��Ϊ����Response�ı���secret */
        ulRet = PPP_GetConfigPassWord((VOS_UINT8 *)stMsg.szResponse);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG("Get pass word fail when when receive challenge.");
        }

        stMsg.ucResponseLen = (UCHAR )VOS_StrLen((VOS_CHAR *)(stMsg.szResponse));
    }

    if (PS_TRUE != g_enGetChapRespSelf)
    {
        ulRet = PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        if (VOS_OK == ulRet)
        {
            /* ����OK˵����HRPDģʽ,������SIM����,������ҪMS�Լ���MD5�㷨���� */
            return;
        }

    }
    else
    {
        g_enGetChapRespSelf = PS_FALSE;
    }

    /*����Challeng Id,Challenge,secret(�ɶԶ�Hostname�ó�)����Response */
    if (PPPC_MD5_GenResponse( &stMsg ))
    {
        /*����Response ������*/
        (VOID)VOS_MemCpy((CHAR *)pstChapInfo->szResponse, (UCHAR*)(stMsg.szResponse),
                           (VOS_UINT32 )stMsg.ucResponseLen );
        pstChapInfo->szResponse[stMsg.ucResponseLen] = 0;
        pstChapInfo->ucRespLen = stMsg.ucResponseLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Generate response error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_51);

        /* ɾ����ʱ�� */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* ���ں˱�CHAP��֤ʧ�� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ��Զ˵�Response��, ��AAA������֤                    *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveResponse(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    AAA_AUTHREQ_S *pstMsg;

    UCHAR ucValueSize;
    LONG lLen = (LONG)ulLen;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_52);
        return;
    }

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVERESPONSE);

    if ((pstChapInfo->ucServerState == CHAP_STATE_SERVER_INITIAL)
        || (pstChapInfo->ucServerState == CHAP_STATE_WAITING_AAA))
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING,
                         "CHAP receive Response ON CHAP_STATE_SERVER_INITIAL or CHAP_STATE_WAITING_AAA phase!");
        PPP_DBG_ERR_CNT(PPP_PHERR_53);
        return;
    }

    if (ucId != pstChapInfo->ucChalId)    /*ID ��ƥ�� */
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_19);
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "unmatched ID!");
        PPP_DBG_ERR_CNT(PPP_PHERR_54_RESP_CHAID_ERR);
        return;
    }

    /* �յ���λ�ٵ�Response��ȻҪ�������һ���յ�Responseһ����answer(Success/Failure)*/
    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
         /*Modified by liushuang for DTS2011112802965. L2TP�û��������ʱ�յ�
           �ն˵�response��Ϣ��ֱ�Ӷ���*/
        if ( ( 0 == pstPppInfo->bReNego )
                && (0 == pstPppInfo->bPppClient)
                 && (1 == pstPppInfo->bPppMode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_820);
        }
        else
        {
            PPP_CHAP_SendStatus(pstPppInfo, pstChapInfo->ucServerState); /* return auth-result */
        }
        return;
    }

    if ((pstPppInfo->ulPeerIPAddr) && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_821);
    }

    /*ɾ���ȴ�Response ��ʱ��ʱ��*/
    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    }
    else
    {
        pstMsg = (AAA_AUTHREQ_S *)PPP_Malloc(sizeof(AAA_AUTHREQ_S));
        if (!pstMsg)
        {
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
            PPP_DBG_ERR_CNT(PPP_PHERR_55);
            return;
        }

        pstChapInfo->pstAAAAuthReqMsg = pstMsg;
    }

    PPP_MemSet((VOID *)pstMsg, 0, sizeof(AAA_AUTHREQ_S));

    /* Response��Ϣ�е�ResponseLen��Response */
    PPP_GETCHAR(ucValueSize, pPacket);        /* ȡ��MD ���� */
    /* ������֤��Ϣ��stMsg  */
    if (ucValueSize > CHAP_MAX_RESPONSE_LENGTH)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_822);
        pstMsg->ucChapResponseLen = CHAP_MAX_RESPONSE_LENGTH;
    }
    else
    {
        pstMsg->ucChapResponseLen = ucValueSize;
    }

    /* ȡ�� response �е�secret�� msg */
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapResponse, pPacket, (VOS_UINT32 )pstMsg->ucChapResponseLen);
    pstMsg->ucChapResponse[pstMsg->ucChapResponseLen] = 0x0;

    /* ȡ�� CHAP ���ƿ��е� challenge �� msg */
    pstMsg->ucChapChallengeLen = pstChapInfo->ucChalLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapChallenge, pstChapInfo->szChallenge, (VOS_UINT32)pstMsg->ucChapChallengeLen);
    pstMsg->ucChapChallenge[pstMsg->ucChapChallengeLen] = 0x0;

    /* ȡ�� response �е�name�� msg */
    PPP_INCPTR(ucValueSize, pPacket);
    lLen -= (LONG)sizeof (UCHAR) + (LONG)ucValueSize;

    /* Modified start by lvyanfang 00110869 at 2008-05-12 PDSN9660V800R005C02B018SP04 for ����Chap Response��Ϣ�в����û������� */
    if ((0 == (g_ulSoftPara567 & 0x01)) && (lLen <= 0))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_20);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_56);
        return;
    }
    else
    {
        /* ����R1C3B047 �汾����Я���û������� */
        if (lLen < 0)
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
            PPP_DBG_ERR_CNT(PPP_PHERR_57);
            return;
        }
    }
    /* Modified end by lvyanfang 00110869 at 2008-05-12 PDSN9660V800R005C02B018SP04 for ����Chap Response��Ϣ�в����û������� */

    if (lLen > A11_MAX_NAI_LENGTH)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_21);
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        A11_ReqNumSubProc(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_58);
        PPPC_INFO_LOG1("\r\n PPP_CHAP_ReceiveResponse: NAI Len(%u) > 63", lLen);
        return;
    }

    pstMsg->ucUsernameLen = (UCHAR)lLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucUsername, pPacket, (VOS_UINT32)pstMsg->ucUsernameLen);
    pstMsg->ucUsername[pstMsg->ucUsernameLen] = 0x0;

    if ((0 != pstPppInfo->ucNAI[0]) && 0 != VOS_StrCmp((CHAR*)(pstMsg->ucUsername), (CHAR*)(pstPppInfo->ucNAI)))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_22);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "NAI != username");
        PPP_DBG_ERR_CNT(PPP_PHERR_59);
        return;
    }

  #ifdef    __PRODUCT_TYPE_PDSN80

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
               "\r\n PPP_CHAP_ReceiveResponse:the domainindex is (%u)(%u)",
               pstPppInfo->usCDBIndex,
               pstPppInfo->usVirtualDomainIdx);

    if ((pstPppInfo->usCDBIndex >= RM_MAX_APN_NUM)
       && (pstPppInfo->usVirtualDomainIdx >= RM_MAX_APN_NUM))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_823);
        if (VOS_OK != PPP_GetDomainInfoByName(pstPppInfo, pstMsg->ucUsername))
        {

            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_60);
            return;
        }
    }

    A11_UpdateDomainIndexAtEntryState(pstPppInfo->ulRPIndex, pstPppInfo->usCDBIndex, VOS_FALSE);

    (VOID)VOS_sprintf((char*)pstPppInfo->ucNAI, "%s", pstMsg->ucUsername);


    /* �ж�CPU�Ƿ����
    if (1 == g_ulSpuOverloadFlag)
    {
        DebugOut((VOS_UINT32)FSU_TID_PPPC, 1, "\r\nPPP_CHAP_ReceiveAuthReq:The cpu is over loading.");
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }*/

    /* ����LOCK��־�ж��Ƿ���������Ǳ�LOCK�����������������Э��ʧ�� */
    if ((PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
        || (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usVirtualDomainIdx].ucLock))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_23);
        PPP_DBG_ERR_CNT(PPP_PHERR_61);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_CHAP_ReceiveResponse:The domain is locked, the domainindex is (%u)(%u)",
                     pstPppInfo->usCDBIndex,
                     pstPppInfo->usVirtualDomainIdx);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }

    if(VOS_TRUE == pstPppInfo->bAuthFlag)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n [ppp]PPP_CHAP_ReceiveResponse: pstPppInfo->bAuthFlag is %u bPpcAAAFlag %d",
                            pstPppInfo->bAuthFlag,
                            pstPppInfo->bPpcAAAFlag);

        /* ����Ҫ��AAA��Ȩ */
        if (0 == pstPppInfo->bPpcAAAFlag)
        {
            PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_SUCCESS);
            PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

            if (NULL != pstChapInfo->pstAAAAuthReqMsg)
            {
                PPP_Free( pstChapInfo->pstAAAAuthReqMsg);
                pstChapInfo->pstAAAAuthReqMsg = NULL;
                pstMsg = NULL;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_824);
            pstPppInfo->bAuthServer = VRP_NO;
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, NULL);

            return;
        }
    }

  #endif
    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;
    pstMsg->usCDBIndex = pstPppInfo->usCDBIndex;
    /*pstMsg->usVPNID = pstPppInfo->usVPNID;*/
    pstMsg->ucPktID = ucId;
    pstMsg->stIMSI = pstPppInfo->stIMSI;

    /* Add by g00127633 for Ԥ������Э��*/
    pstMsg->ucRenegoFlag = pstPppInfo->bPpcAAAFlag;
    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_WAITING_AAA, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_WAITING_AAA;

#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* ����PPP �� L2TP ͨ������ */
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* ������֤���� */
        pstOptionalPara->usAuthenType = L2TP_PPP_CHAP;

        /* ���ñ���֤�û��� */
        VOS_MemCpy(pstOptionalPara->szAuthenName,
                        pstMsg->ucUsername,
                        pstMsg->ucUsernameLen);
        pstOptionalPara->szAuthenName[pstMsg->ucUsernameLen] = 0x0;

        /* ����Challenge */
        pstOptionalPara->ulChallengeLen = pstMsg->ucChapChallengeLen;
        VOS_MemCpy(pstOptionalPara->szChallenge,
                        pstMsg->ucChapChallenge,
                        pstMsg->ucChapChallengeLen);
        pstOptionalPara->szChallenge[pstMsg->ucChapChallengeLen] = 0x0;

        /* ����Response */
        pstOptionalPara->ulResponseLen = pstMsg->ucChapResponseLen;
        VOS_MemCpy(pstOptionalPara->szResponse,
                        pstMsg->ucChapResponse,
                        pstMsg->ucChapResponseLen);
        pstOptionalPara->szResponse[pstMsg->ucChapResponseLen] = 0x0;

        pstOptionalPara->usAuthenID = pstChapInfo->ucChalId;
    }
#endif

    /*��AAA ������֤*/
    /*PPP_Shell_AuthRequest(pstPppInfo->ulIfIndex, &stMsg);*/
#if 0
    PPP_CHAP_SendAAAAuthReq(pstChapInfo);
#endif
    return;
}

#if 0
/*****************************************************************************
 �� �� ��  : PPP_CHAP_ReceiveAAAResult
 ��������  : Chapģ���յ�AAA��Ȩ��Ϣ
 �������  : AAA_AUTHRSP_S *pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CHAP_ReceiveAAAResult(AAA_AUTHRSP_S *pMsg)
{
    UCHAR ucResult;
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_ReceiveAAAResult---\r\n");

    /*�ж������������Ч��*/
    if (NULL == pMsg)
    {
        VOS_DBGASSERT(pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: Invalid input parameter!");
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_825);
    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (pstPppInfo == NULL)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d isn't exist!", pMsg->ulSDBIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_62);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_63);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d  pstChapInfo isn't exist!",
                     pMsg->ulSDBIndex);
        return;
    }

    /* ɾ����ʱ�� */
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    /* �ͷ�AAA��֤������Ϣ */
    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
        pstChapInfo->pstAAAAuthReqMsg = NULL;
    }

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULT);
    if (pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)    /* ״̬���¼����� */
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_64);
        return;
    }

    /* ��֤�ɹ� */
    if (pMsg->ucResult == 0)
    {
        PPP_PerfInc(g_stPppPerfStatistic.pulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

        /* ��֤ͨ�� */
        ucResult = CHAP_STATE_SERVER_SUCCESS;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);
        PPP_DBG_OK_CNT(PPP_PHOK_826);

        /* ɾ����ʱ�� */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        if (pstChapInfo->ulChalInterval != 0)
        {
            if (pstChapInfo->ulChalTimeoutID == 0)
            {
                /* �����´�chap��֤ʱ�� */
                (VOID)VOS_Timer_Create(g_ulPPPTaskId,
                                                       g_ulPppTimeQueID,
                                                       pstChapInfo->ulChalInterval,
                                                       PPP_CHAP_Rechallenge,
                                                       (VOID *) pstPppInfo->ulRPIndex,
                                                       &(pstChapInfo->ulChalTimeoutID), VOS_TIMER_LOOP );
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_65);
                VOS_DBGASSERT(0);
            }
        }

        /* ֪ͨ�ں� chap Server����֤ͨ�� */
        pstPppInfo->bAuthServer = VRP_NO;
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, (CHAR*)pMsg);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_66);

        /* ��֤δͨ�� */
        ucResult = CHAP_STATE_SERVER_FAILED;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);

        /* ���״̬ת��������Ϣ */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_SERVER_FAILED;/* �ı�״̬ */
        /* ɾ����ʱ�� */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* ������֤ʧ�ܴ���, ���ں˱�CHAP��֤ʧ�� */
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPP_CHAP_SendAAAAuthReq
 ��������  : ��AAA���ͼ�Ȩ����
 �������  : PPPCHAPINFO_S *pstChapInfo
             AAA_AUTHREQ_S *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��2��21��
    ��    ��   : gxf
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CHAP_SendAAAAuthReq(PPPCHAPINFO_S *pstChapInfo)
{
    AAA_AUTHREQ_S *pstMsg = NULL;
    VOS_UINT32 ulRet;
    PPPINFO_S *pstPppInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_SendAAAAuthReq---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_827);

    if (NULL == pstChapInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_67);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo=NULL");
        return;
    }

    pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    if (NULL == pstMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_68);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstMsg=NULL");
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_69);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo->pstPppInfo=NULL");
        return;
    }

    /* ���ڿ����Ƿ�NAIת����Сд��� */
    if (1 == M_SPM_USER_NAME_LOWERCASE)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_828);
        VOS_lowercase((CHAR*)(((AAA_AUTHREQ_S*)pstMsg)->ucUsername));
    }

    ((AAA_AUTHREQ_S*)pstMsg)->ucPPPFlag =1;
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                         g_ullPppAuthCsi,
                         AUTH_MSG_TYPE_PPP,
                         PPP_AUTH_FLAG,
                         (UCHAR *)pstMsg,
                         sizeof( AAA_AUTHREQ_S ));
    if ( VOS_OK != ulRet )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_70);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_CHAP_SendAAAAuthReq: OSS_Que_Write Err!!");
        return;
    }
    ///TODO:luofang �Ƿ���Ҫ�ڲ���Ϣ����
    /* �ڲ���Ϣ���� */
    /*  �Ƿ���Ҫ
    PPP_InternalMsgTrc(PPP_INNERTRC_AAA_REQ, pstMsg, pstPppInfo->ulRPIndex);
    */

    /* ���ó�ʱ��ʱ�� */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID == 0);
    ulRet = PGP_Timer_Create(PPP_SELF_CSI,
                             PPP_MSG_TYPE_TIMER,
                             pstChapInfo->ulWaitAuthRspTimeout,
                             PPP_CHAP_AuthRspTimeout,
                             (VOID*)pstPppInfo->ulRPIndex,
                             &(pstChapInfo->ulChalTimeoutID),
                             VOS_TIMER_LOOP);
    if (ulRet != VOS_OK)
    {
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "PGP_Timer_Create error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_71);
        /*PPP_CHAP_AAAAuthFailed(pstChapInfo);*/
    }
    PPP_DBG_OK_CNT(PPP_PHOK_829);

    ++pstChapInfo->ucAuthTransmits;
    return ;
}
#endif

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ��Զ���֤�ɹ���Ӧ, ������״̬����CHAP SUCCESS        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 ucId:����ID                                                *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveSuccess(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S                      *pstChapInfo = pstPppInfo->pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccesAuth;
    VOS_UINT32                          ulRet;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;


    if (pstChapInfo == NULL)
    {
        PPPC_WARNING_LOG1("chapinfo is null:pppId", pstPppInfo->ulRPIndex);
        return;
    }


    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        PPPC_WARNING_LOG1("Illegal event!:ucClientState", pstChapInfo->ucClientState);
        return;
    }

    /*ɾ���ȴ��Զ���֤�����ʱ��ʱ��*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_SUCCESS; /* �ı�״̬ */
    /*���ں˱� CHAP Client ����֤�ɹ� */
    pstPppInfo->bAuthClient = VRP_NO;

    /* ɾ����ʱ�� */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    /* ��ά�ɲ� */
    /* PPPC CHAP��Ȩ�ɹ����ĸ��� */
    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)pstPppInfo->ulRPIndex,
                PPP_CHAP, VOS_OK, &stPppAuthInfo);

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Stop timer fail!\r\n", pstPppInfo->ulRPIndex, enIsDoingAccesAuth);
        }

        /* �����Ȩ�����Ҫɾ��PPPʵ��Ľڵ� */
        PPP_NodeDelete(0);

        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* ��ʼ�����ȨֻҪ����һ�μ��� */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        /* �����Ȩ��־λ�ָ���Ҫ��ǰ�� */
        PPPC_AccessAuthSuccProc();

        /* ֪ͨRPA�����Ȩ���� */
        PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RCV_CHAP_SUCC);

        /* ������ڽ��н����Ȩ,���л���IPCP�׶� */
        PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));

        return;
    }

    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPSUCCESS, NULL);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ��Զ���֤ʧ�ܻ�Ӧ, ������״̬��                        *
*                �����ں˱�CHAP Client ����֤ʧ��                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 pPacket:����ͷλ��                                            *
*                 ucId:����ID                                                *
*                ulLen:�������ݳ���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveFailure(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    CHAR cErrstr[100];
    PS_BOOL_ENUM_UINT8                  enIsDoingAccesAuth;
    CTTF_PPPC_AUTH_INFO_STRU            stPppAuthInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_74);
        return;
    }

    /*����OM��ά�ɲ���Ϣ*/
    g_stPppcStatRpt.stPppcStatisticInfo.ulNameOrPwdAuthFailCnt++;
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AUTHFAILURE);

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_75);
        return;
    }

    /*ɾ���ȴ��Զ���֤�����ʱ��ʱ��*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /*Client����֤ʧ�ܴ�����һ*/
    pstChapInfo->usAuthClientFailureTimes += 1;

    /*������������Ϣ*/
    (VOID)VOS_sprintf(cErrstr, "Client auth failed No. %2d !",
                      pstChapInfo->usAuthClientFailureTimes );
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    /* ��֤ʧ�ܴ�������, ���ϱ�CHAP DOWN */
    PPP_DBG_ERR_CNT(PPP_PHERR_76);
    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* �ı�״̬ */
    /* ɾ����ʱ�� */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)(pstPppInfo->ulRPIndex), PPP_CHAP,
                    VOS_ERR, &stPppAuthInfo);


    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* ��ʼ�����ȨֻҪ����һ�μ��� */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();

        /* ֪ͨRPA�����Ȩ���� */
        PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RCV_CHAP_REJECT);

        /* ������ڽ��н����Ȩ,�����־λ */
        PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));
    }
    else
    {
        /* ���Ź淶Ҫ��ҵ��Э��ʱChap��Ȩʧ����Ҫ����Lcp Terminate Req����PPP���� */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo,PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP��Զ˷�����֤challenge                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ServerLowerUp,PPP_CHAP_ChallengeTimeout,            *
*                 PPP_CHAP_ServerSuccess,PPP_CHAP_Rechallenge                *
****************************************************************************/
VOID PPP_CHAP_SendChallenge(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pHead, *pPacket;
    VOS_UINT16 usChal_len, usName_len;
    VOS_UINT16 usOutLen;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulErrorCode;

    PPPC_INFO_LOG("\r\n---Into PPP_CHAP_SendChallenge---\r\n");

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_77);
        return;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;

    /* ��ֹIPй¶�������쳣������ */
    if (pstPppInfo->ulPeerIPAddr && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_79);
    }

    pPacket = pHead + ulOffset;

    usChal_len = pstChapInfo->ucChalLen;
    usName_len = (VOS_UINT16 )VOS_StrLen((VOS_CHAR *)(pstChapInfo->szHostName));
    usOutLen = CHAP_HEADERLEN + 1 + usChal_len + usName_len;

    PPP_PUTCHAR(CHAP_PACKET_CODE_CHALLENGE, pPacket);            /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);        /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                    /*CHAP LENGTH */

    /* дchallege Length,challenge�Լ�Name*/
    PPP_PUTCHAR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szChallenge, (VOS_UINT32) usChal_len);
    PPP_INCPTR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szHostName, (VOS_UINT32)usName_len);
    PPP_INCPTR(usName_len, pPacket );
    pPacket -= usOutLen;

    /*���������Ϣ*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32) usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_80);
        /*���������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulChalTimeoutID == 0)
    {
        /* �����ش�chap��֤ʱ�� */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstChapInfo->ulChalTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_CHALLENGE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_81);
    }

    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_CHALLENGE, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_SEND_CHALLENGE; /* �ı�״̬ */

    ++pstChapInfo->ulChalTransmits;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP��Զ��ͳ���֤�ɹ�/ʧ�ܱ���                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                 ucResult: ��֤���                                            *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendStatus(PPPINFO_S *pstPppInfo, UCHAR ucResult)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    VOS_UINT16 usOutLen, usMsgLen;
    VOS_UINT32 ulOffset;
    CHAR msg[256];
    VOS_UINT32 ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_830);

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, ucResult, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = ucResult;    /* �ı�״̬ */

    if (ucResult == CHAP_PACKET_CODE_SUCCESS)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_831);
        (VOID)VOS_sprintf(msg, "Welcome to %s.", pstChapInfo->szHostName);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_832);
        (VOID)VOS_sprintf(msg, "Illegal user or password.");
    }

    usMsgLen = (VOS_UINT16)VOS_StrLen(msg);

    /*���㱨�ĳ��� */
    usOutLen = (VOS_UINT16)(CHAP_HEADERLEN + usMsgLen);

    PPP_PUTCHAR(ucResult, pPacket);                /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);    /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /*CHAP LENGTH */
    /* ����message */
    (VOID)VOS_MemCpy((CHAR *)pPacket, msg, (VOS_UINT32) usMsgLen);
    PPP_INCPTR(usMsgLen, pPacket);

    pPacket -= usOutLen; /* �ָ�ָ�� CHAP ����ͷ */

    /*������ĵ�����Ϣ*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32 )usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_83);
        /*���������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }
    PPP_DBG_OK_CNT(PPP_PHOK_833);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ������һ������ַ���, ͬʱ Challenge ID �� 1                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstChapInfo:CHAP���ƿ�ָ��                                 *
* OUTPUT       ������ַ�������pstChapInfo->szChallenge                        *
*                 ����ַ������ȷ���pstChapInfo->len                            *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_GenChallenge(PPPCHAPINFO_S *pstChapInfo)
{
    UCHAR ucChalLen;
    UCHAR *ptr;
    UCHAR i;
    VOS_UINT32 ulRand = 0;

    ptr = pstChapInfo->szChallenge;

    /* ѡ��һ������MIN_CHALLENGE_LENGTH��MAX_CHALLENGE_LENGTH֮���������� */
    ucChalLen = CHAP_MAX_CHALLENGE_LENGTH;
    pstChapInfo->ucChalLen = ucChalLen;

    /*CHAP ���ƿ� Challenge Id �� 1 */
    pstChapInfo->ucChalId++;

    /*add by y00125257 CR20110607034 DTS2012020303820: �������ʹ�ù̶���chap challenge*/
    /* ��������ַ��� */

    for (i = 0; i < ucChalLen; i++)
    {
        (VOID)PPPC_CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(VOS_UINT32));
        *ptr = (UCHAR )(ulRand * 0xff);
        ptr++;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP��Զ��ͳ�response����, ���ı�״̬                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendResponse(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    UCHAR  *pName;
    VOS_UINT16 usOutLen, usMdLen, usNameLen;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    pName     = pstChapInfo->szHostName;
    usMdLen   = pstChapInfo->ucRespLen;
    usNameLen = (VOS_UINT16) VOS_StrLen((VOS_CHAR *)pName);

    /* ����鲻���û������ٲ�һ�η�ֹSIM���ظ��������û���Ϊ�� */
    if (0 == usNameLen)
    {
        (VOS_VOID)PPP_GetConfigUserName((VOS_UINT8 *)pstChapInfo->szHostName, pstPppInfo->ulRPIndex);
        pName     = pstChapInfo->szHostName;
        usNameLen = (VOS_UINT16) VOS_StrLen((VOS_CHAR *)pName);
    }

    usOutLen = CHAP_HEADERLEN + sizeof (UCHAR) + usMdLen + usNameLen;

    PPP_PUTCHAR(CHAP_PACKET_CODE_RESPONSE, pPacket);        /* CHAP CODE -RESPONSE */
    PPP_PUTCHAR(pstChapInfo->ucRespId, pPacket);    /* CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /* CHAP LENGTH */

    /* secret���Ⱥ�secret  */
    PPP_PUTCHAR(usMdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )pPacket, pstChapInfo->szResponse, (VOS_UINT32)usMdLen);
    PPP_INCPTR(usMdLen, pPacket);

    /* ���NAME */
    (VOID)VOS_MemCpy((CHAR *)pPacket, pName, (VOS_UINT32)usNameLen);
    PPP_INCPTR(usNameLen, pPacket);
    pPacket -= usOutLen; /* �ָ�ָ�� CHAP ����ͷ */

    /*������ĵ�����Ϣ*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP, 0);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (VOS_UINT32)usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        /*���������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulRespTimeoutID == 0)
    {
        /* �����ش�responseʱ�� */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstChapInfo->ulRespTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_RESPONSE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_85);
    }

    ++pstChapInfo->ulRespTransmits;

    /* ���״̬ת��������Ϣ */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_RESPONSE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_SEND_RESPONSE;/* �ı�״̬ */
    PPP_DBG_OK_CNT(PPP_PHOK_834);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP����Challenge ��ʱ��������Ӧ����                        *
*                 ��������ش����������ں˱�CHAP ��֤ʧ��                    *
*                 �����ٴη���Challenge                                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��CHAP ��ʱ��ulChalTimeoutID����                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ChallengeTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_86);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_87);
        return;
    }

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CHALLENGETIMEOUT);

    /*�����ʱ��*/
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_88);
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /*������������Ϣ*/
    (VOID)VOS_sprintf(cErrstr, "Send Challenge No. %2lu !", pstChapInfo->ulChalTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulChalTransmits >= pstChapInfo->ulMaxTransmits)
    {
        pstChapInfo->ulChalTransmits = 0;

        /* ���״̬ת��������Ϣ */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucServerState = CHAP_STATE_SERVER_FAILED; /* �ı�״̬ */
        /* ɾ����ʱ�� */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_24);


        /*���ں˱�CHAP ��֤ʧ��*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_CHLTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);


        A11_ReqNumSubProc(pstPppInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_89);


        return;
    }

    pstChapInfo->ucChalId++;
    /*End of liushuang*/

    PPP_DBG_OK_CNT(PPP_PHOK_835);
    PPP_CHAP_SendChallenge(pstPppInfo);        /*�ش� challenge */
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP����Response ��ʱ��������Ӧ����                        *
*                 �ٴη���Response                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��CHAP ��ʱ��ulRespTimeoutID����                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ResponseTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_91);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_92);
        return;
    }

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RESPONSETIMEOUT);

    /*�����ʱ��*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
    pstChapInfo->ulRespTimeoutID = 0L;

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_93);
        return;
    }

    /*������������Ϣ*/
    (VOID)VOS_sprintf(cErrstr, "Send Response No. %2lu !", pstChapInfo->ulRespTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulRespTransmits >= pstChapInfo->ulMaxTransmits)
    {
        /* ���״̬ת��������Ϣ */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* �ı�״̬ */
        /* ɾ����ʱ�� */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /*���ں˱�CHAP ��֤ʧ��*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_RSPTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_CHAPFAILED, NULL);
        PPP_DBG_ERR_CNT(PPP_PHERR_94);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_836);

    PPP_CHAP_SendResponse(pstPppInfo);        /* �ش� response */

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_CHAP_AuthRspTimeout
 ��������  : CHAP�ȴ�AAA��֤�����ʱ
 �������  : VOID *pMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��2��21��
    ��    ��   : gxf
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CHAP_AuthRspTimeout(VOID *ulIndex)
{
#if 0
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo = NULL;
    AAA_AUTHREQ_S *pstAuthRspMsg = NULL;
    VOS_UINT32 ulIdxTmp = (VOS_UINT32)ulIndex;

    PPP_TRACE("\r\n---Into PPP_CHAP_AuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_837);

    GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulIndex);
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_95);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;
    if (NULL == pstChapInfo)
    {
        //VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_96);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo=NULL", ulIdxTmp);
        return;
    }

    pstAuthRspMsg = pstChapInfo->pstAAAAuthReqMsg;
    if(NULL == pstAuthRspMsg)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_97);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstAuthRspMsg=NULL", ulIdxTmp);
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if(NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_98);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    if(pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_99);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->ucServerState(%d)",
                         ulIdxTmp, pstChapInfo->ucServerState);
        return;
    }

    /* ����¼�������Ϣ */
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULTTIMEOUT);

    /* �����ʱ�� */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID);
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucAuthTransmits >= pstChapInfo->ulAuthMaxTransmits)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_25);
        PPP_DBG_ERR_CNT(PPP_PHERR_100);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        /*End of liushuang*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_AAATIMEOUT);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_838);
        PPP_CHAP_SendAAAAuthReq(pstChapInfo);
    }
#endif
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP��ʱ��Զ˷���challenge                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��CHAP ��ʱ��ulChalTimeoutID����                                *
****************************************************************************/
VOID PPP_CHAP_Rechallenge(VOID *ulIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo;

    GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_101);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;

    /*����¼�������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECHANLLENGE);

    /*�����ʱ��*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucServerState != CHAP_STATE_SERVER_SUCCESS)
    {
        /*������������Ϣ*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_102);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_839);

    /*���ں˱�CHAP ������֤*/
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_RECHALLENGE, NULL);

    PPP_CHAP_GenChallenge(pstChapInfo);    /*����challege */
    PPP_CHAP_SendChallenge(pstPppInfo);    /*����challege */

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/12                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��CHAP�յ�һ�Ƿ�Э��, ֪ͨ�ײ�DOWN                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��                                                            *
****************************************************************************/
VOID PPP_CHAP_ReceiveUnknownCode(PPPINFO_S *pstPppInfo)
{
    /*���������Ϣ*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CODEREJECT);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/09                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��ɾ����ʱ��                                                    *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                            *
* CALLED BY    ��                                                            *
****************************************************************************/
VOID PPP_CHAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_103);
        return;
    }

    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));   /* ɾ��challenge��ʱ�� */
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));    /* ɾ��Response ��ʱ�� */
        pstChapInfo->ulRespTimeoutID = 0;
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
