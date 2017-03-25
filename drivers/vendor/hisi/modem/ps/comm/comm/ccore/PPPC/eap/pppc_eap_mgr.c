/************************************************************************
*                                                                      *
*                             Eap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2010/07/05                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��EAPЭ��ģ��                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������EAPЭ��ģ���ȫ���ӿں������ڲ�������              *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_MGR_C
/*lint +e767*/



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPPC_EAP_Init
 ��������  : EAPģ���ʼ��.
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
VOID PPPC_EAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    pstEapInfo  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL or pstConfig=NULL");
        return;
    }

    PPPC_EAP_InitMethod(pstEapInfo);

    PPPC_EAP_DeleteTimer(pstEapInfo);

    PPP_MemSet((VOID*)pstEapInfo, 0, sizeof(PPPC_EAP_INFO_STRU));

    pstEapInfo->pstPppInfo      = pstPppInfo;

    /* ��ʼ��Ϊ0xffff��ֹ��ʼ��ֵ�����緢�͵ĵ�һ��Request�ظ� */
    pstEapInfo->usEAPLastReqID  = 0xffff;

    return;
}


/****************************************************************************
* CREATE DATE  ��2010/07/12                                                 *
* CREATED BY   ��WANGYONG                                                   *
* FUNCTION     ��EAP�����ⲿ�¼�.�¼�������ServerUp��Down                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������, ����Ϊ����ֵ:                                *
*                EAP_EVENT_SERVERLOWERUP:�Զ��²�UP                         *
*                EAP_EVENT_LOWERDOWN:�²�DOWN                               *
*                pPara:�¼��Ĳ���, ΪNULL                                   *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Core_ReceiveEventFromShell                             *
****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveEventFromCore
(
    PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, VOS_UINT8 *pPara
)
{
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    switch (ulCmd)
    {
        case EAP_EVENT_LOWERDOWN:
            PPPC_EAP_LowerDown(pstPppInfo);
            break;

        default:
            /*������������Ϣ*/
            PPPC_WARNING_LOG1("EAP Receive UNKNOWN Event!", ulCmd);
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2010/07/12                                                 *
* CREATED BY   ��WANGYONG                                                   *
* FUNCTION     ��PPP_EAP_LowerDown                                          *
*                ����EAP_STATE_SERVER_INITIAL״̬                           *
*                ͬʱɾ����ʱ��                                             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��                                                           *
* CALLED BY    ��PPP_EAP_ReceiveEventFromCore                               *
****************************************************************************/
VOID PPPC_EAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo=NULL");
        return;
    }

    pstEapInfo = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* ɾ����ʱ�� */
    PPPC_EAP_DeleteTimer(pstEapInfo);

    PPPC_EAP_Init(pstPppInfo);

    /* �ı�״̬ */
    pstEapInfo->enEapPeerState  = PPPC_EAP_PEER_IDLE_STATE;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_SendResponse
 ��������  : ����EAP Response����
 �������  : pstPppInfo     PPPʵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��09��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_EAP_SendResponse(VOS_UINT32 ulPppId)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT8                          *pucHead;
    VOS_UINT8                          *pucPacket;
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulErrorCode;
    PPPC_EAP_HEADER_STRU               *pstPayload;


    if (PPP_MAX_USER_NUM < ulPppId)
    {
        PPPC_WARNING_LOG1("Invalid ppp id", ulPppId);
        return;
    }

    pstPppInfo                  = &g_astPppPool[ulPppId];
    pstEapInfo                  = (PPPC_EAP_INFO_STRU *)pstPppInfo->pstEapInfo;

    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    PS_MEM_SET(g_ucPppSendPacketHead, 0,
        sizeof(g_ucPppSendPacketHead));

    /* ��ȡ�ڴ� */
    pucHead     = g_ucPppSendPacketHead;
    pucPacket   = pucHead + ulOffset;

    if (pstEapInfo->usRespPktLen >= PPPC_EAP_MAX_RESPONSE_LEN)
    {
        PPPC_WARNING_LOG1("Invalid payload len!", pstEapInfo->usRespPktLen);
        return;
    }

    /* ��EAP����д�뷢���ڴ� */
    PS_MEM_CPY(pucPacket, pstEapInfo->aucRespPkt, pstEapInfo->usRespPktLen);

    pstPayload  = (PPPC_EAP_HEADER_STRU *)pstEapInfo->aucRespPkt;

    /* ���淢�͵�ID�������´��հ�ʱ���ظ�֡��� */
    pstEapInfo->usEAPLastReqID  = pstPayload->ucEAPID;

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((VOS_CHAR *)pstPppInfo,
                                              pucHead,
                                              pucPacket,
                                              pstEapInfo->usRespPktLen,
                                              PPP_EAP);
    if (VOS_OK != ulErrorCode)
    {
        /* ���ķ���ʧ�ܣ����Response��ر��� */
        PS_MEM_SET(pstEapInfo->aucRespPkt, 0, sizeof(pstEapInfo->aucRespPkt));
        pstEapInfo->usRespPktLen        = 0;
        pstEapInfo->usEAPLastReqID      = 0xffff;

        /*���������Ϣ*/
        PPPC_WARNING_LOG1("Send EAP response fail", ulErrorCode);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EAP_DeleteTimer
 ��������  : ͣ��ʱ��
 �������  : pstEapInfo     EAPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EAP_DeleteTimer(PPPC_EAP_INFO_STRU *pstEapInfo)
{
    VOS_UINT32                              ulRet;


    /* �ڲ����ñ�ָ֤��ǿ� */

    if (VOS_NULL_PTR != pstEapInfo->hReqTimeoutID)
    {
        /* ͣ��ʱ�� */
        ulRet = VOS_StopRelTimer((HTIMER*)&pstEapInfo->hReqTimeoutID);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
        }
    }

    pstEapInfo->hReqTimeoutID   = VOS_NULL_PTR;

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
