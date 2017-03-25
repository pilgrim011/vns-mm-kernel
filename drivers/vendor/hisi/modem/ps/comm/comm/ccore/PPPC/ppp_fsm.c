/************************************************************************
*                                                                      *
*                             ppp_fsm.c                                *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��״̬��ģ������к���                       *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PPP��״̬��ģ������к���                            *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_FSM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

extern volatile HTIMER                  g_hRestartTimer;
extern PS_BOOL_ENUM_UINT8               g_ucLcpTermMask;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/* �ı�״̬,���ڲ���Ҫ��ʱ����״̬,ɾ����ʱ�� */
/* TO�¼���״̬ת��ͼ */

/*
 | State
 |    0         1         2         3         4         5           6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+------------------------------------------------------------------------------------------------------
  TO+ |    -         -         -         -       str/4     str/5      scr/6     scr/6     scr/8         -
  TO- |    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
 */

/* ���,Initial��Starting��Closed��Stopped��Opened״̬���ö�ʱ��,��Ҫɾ����ʱ��,
   ����״̬����ԭ���Ķ�ʱ�� */

/* �����ACKRCVD״̬����TO-�¼�����ô��˫������·��ʱʱ������̫��������ģ�Ӧ������negotiate timeʱ�� */
VOS_VOID PPP_FSM_ChangeState
(
    PPPFSM_S                           *pstFsm,
    VOS_UINT8                           ucNewState
)
{
    PPPC_EVENT_USER_DATA                stPppEventData;
    PPPINFO_S                          *pstPppInfo;


    if (VOS_NULL_PTR == pstFsm)
    {
        PPPC_WARNING_LOG1("Fsm is null!", ucNewState);
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG2("Ppp is null!", ucNewState, pstFsm->ucState);
        return;
    }

    PS_MEM_SET(&stPppEventData, 0, sizeof(stPppEventData));
    stPppEventData.ulOldState   = (VOS_UINT32)pstFsm->ucState;
    stPppEventData.ulNewState   = (VOS_UINT32)ucNewState;
    stPppEventData.ulPppId      = pstPppInfo->ulRPIndex;
    stPppEventData.ucPdnId      = 0xff;

    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:

            stPppEventData.enEntityId   = PPPC_ENTITY_ID_LCP;

            break;

        case PPP_IPCP:

            stPppEventData.enEntityId   = PPPC_ENTITY_ID_IPCP;

            break;

        case PPP_IPV6CP:

            stPppEventData.enEntityId   = PPPC_ENTITY_ID_IPV6CP;

            break;

        case PPP_VSNCP:

            stPppEventData.enEntityId   = PPPC_ENTITY_ID_VSNCP;

            break;

        default:

            stPppEventData.enEntityId   = PPPC_ENTITY_ID_BUTT;

            PPPC_WARNING_LOG3("Invalid protocol!",
                ucNewState, pstFsm->ucState, pstFsm->usProtocol);

            break;
    }

    /* �ϱ��¼� */
    PPPC_MNTN_SndEvent(MSPS_PID_PPPC, DIAG_MODE_COMM, PPPC_LOG_EVENT_STATE_UPDATE,
            &stPppEventData, sizeof(PPPC_EVENT_USER_DATA));

    pstFsm->ucState = ucNewState;
    switch (ucNewState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:
        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_OPENED:
            PPP_FSM_DelRetransmitTimer(pstFsm);
            break;
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
        default:
            break;
    }

    return;
}


VOID PPP_FSM_RleseCode(PPPFSM_S * pstFsm, VOS_UINT32 ulLcpCode, VOS_UINT32 ulIpcpCode, VOS_UINT32 ulIpv6cpCode, VOS_UINT32 ulVsncpCode)
{
    PPPINFO_S* pPppInfo = NULL;
    PPPVSNCPINFO_S *pstVsncpInfo = NULL;

    if(NULL == pstFsm)
    {
        PPPC_INFO_LOG("\r\n PPP_RleseCode: Input is Null ptr!");
        return;
    }

    pPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    pstVsncpInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;

    if (NULL == pPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_RleseCode: Input is Null ptr!");
        return;
    }

    /* �����lcp echo��ʱ���µ�Э��ʧ�ܣ�������ԭ��ֵ�����޸� */
    if (AM_RELCODE_PPP_LCP_ECHOTIMEOUT == pPppInfo->ucPppRleaseCode )
    {
        return ;
    }

    if ((PPP_LCP == pstFsm->usProtocol) && (0 == pPppInfo->ucPppRleaseCode))
    {
        pPppInfo->ucPppRleaseCode = (UCHAR)ulLcpCode;
    }
    if ((PPP_IPCP == pstFsm->usProtocol) && (0 == pPppInfo->ucV4NcpReleaseCode))
    {
        pPppInfo->ucV4NcpReleaseCode= (UCHAR)ulIpcpCode;
    }
    if ((PPP_IPV6CP == pstFsm->usProtocol) && (0 == pPppInfo->ucV6NcpReleaseCode))
    {
        pPppInfo->ucV6NcpReleaseCode = (UCHAR)ulIpv6cpCode;
    }

    if ((PPP_VSNCP == pstFsm->usProtocol) && (pstVsncpInfo != NULL))
    {
        if (0 == pstVsncpInfo->ulPDNRleaseCode)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1068);
            pstVsncpInfo->ulPDNRleaseCode = (UCHAR)ulVsncpCode;
        }
    }

    return;
}



/*****************************************************************************
 �� �� ��  : PPP_FSM_OpenedStateRenegoStart
 ��������  : LCP״̬����Opened״̬��ʼ��Э�̵Ĵ�����
 �������  : PPPFSM_S *pstFsm
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��16��
    ��    ��   : y00125257
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_FSM_OpenedStateRenegoStart(PPPFSM_S *pstFsm)
{
    PPPINFO_S* pstPppInfo = NULL;
    PPPIPCPINFO_S *pstIpcpInfo = NULL;
    PPPIPV6CPINFO_S *pstIpV6cpInfo = NULL;
    PPP_CCP_INFO_S *pstCcpInfo = NULL;
    PPPRENOGOINFO stPppRenegoInfo;
    AM_CM_PPP_RENEGO_MSG_S stPppRenego;
    VOS_UINT32 ulMemSize = 0;

    PPP_MemSet((VOID*)&stPppRenegoInfo, 0, sizeof(stPppRenegoInfo));
    PPP_MemSet((VOID*)&stPppRenego, 0, sizeof(AM_CM_PPP_RENEGO_MSG_S));

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /* h50774�޸ģ�PPP�����û���֧����Э�� */
    if ((0 == pstPppInfo->bPppClient) && (1 == pstPppInfo->bPppMode))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_427);
        return VOS_ERR;
    }

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);


    /* ����v4��v6��Э�̱�� */
    if ( pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6 )
    {
        pstPppInfo->bReNegoV6 = 1;
        pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
    }
    if ( pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4 )
    {
        pstPppInfo->bReNego = 1;
        pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;
    }


    //(VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
    (VOID)PPP_NodeAdd(pstPppInfo->ulRPIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_SetRenegoFlagForAllPDN(pstPppInfo);
#if 0
        /* ֪ͨdiam authɾ�����ƿ� */
        (VOID)Diam_AuthPPPRenegoRelCB(pstPppInfo->ulRPIndex);
#endif
        /* ����ڼ�Ȩ�ɹ�ǰ������������Э�̣���Ҫ֪ͨaaa�ͷŻỰ��
           �����޷�֪ͨ����ͷŵ�ǰ�Ự��������Ҫ��������ʱ��������¹����µ�session id */
#if 0
        if (VOS_TRUE != pstPppInfo->bEAPAuthFlag)
        {
            PPP_EAP_NotifyDiamAuthReleaseForRenego(pstPppInfo);
        }
#endif
        return VOS_OK;
    }

    pstIpcpInfo = pstPppInfo->pstIpcpInfo;
    if (pstIpcpInfo && (PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1069);

        stPppRenegoInfo.ucIpcpFlag = 1;
        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpOptions, (VOID*)&pstIpcpInfo->stGotOptions,
                           sizeof(PPP_IPCP_OPTION_S));
    }

    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if ( pstIpV6cpInfo && (PPP_STATE_OPENED == pstIpV6cpInfo->stFsm.ucState))
    {
        stPppRenegoInfo.ucIpV6cpFlag = 1;
        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpV6Options, (VOID*)&pstIpV6cpInfo->stGotOptions,
                           sizeof(PPP_IPV6CP_OPTION_S));
    }

    pstCcpInfo = pstPppInfo->pstCcpInfo;
    if (pstCcpInfo && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
    {
        stPppRenegoInfo.ucCcpFlag = 1;
        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stCcpOptions, (VOID*)&pstCcpInfo->stGotOptions,
                           sizeof(PPP_CCP_options_S));
    }

    if (stPppRenegoInfo.ucIpcpFlag || stPppRenegoInfo.ucCcpFlag ||stPppRenegoInfo.ucIpV6cpFlag)
    {
        if (!pstPppInfo->pstPppRenegoInfo)
        {

            ulMemSize = sizeof(PPPRENOGOINFO);
            pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(ulMemSize);
            if(NULL == pstPppInfo->pstPppRenegoInfo )
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_428);
                PPPC_WARNING_LOG("\r\n pstPppInfo->pstPppRenegoInfo PPP_Malloc Failed!~!!");
                return VOS_ERR;
            }
            PPP_MemSet((void*)pstPppInfo->pstPppRenegoInfo, 0, ulMemSize);


        }

        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)VOS_MemCpy(pstPppInfo->pstPppRenegoInfo, (VOID*)&stPppRenegoInfo, sizeof(PPPRENOGOINFO));
        }
    }


    pstPppInfo->bPpcAAAFlag = 0;

    return VOS_OK;
}

VOID PPP_FSM_SetRetransmitTimer( PPPFSM_S *pstFsm)
{
    VOS_UINT32 ulRetVal;
    VOS_UINT32 ulPdpIndex = 0;

    /* �����ʱ���Ѿ����������ô��� */
    if (NULL == pstFsm)
    {
        PPPC_INFO_LOG("\r\n PPP_FSM_SetRetransmitTimer: error pstFsm is NULL!");
        return;
    }

    /* VSNCP���⴦�� */
    if (PPP_VSNCP == pstFsm->usProtocol)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1070);
        PPP_VSNCP_FSM_SetRetransmitTimer(pstFsm);
        return;
    }

    if (pstFsm->ulTimeOutID == 0)
    {
        if (NULL == pstFsm->pPppInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_429);
            PPPC_INFO_LOG("\r\n PPP_FSM_SetRetransmitTimer: error pstFsm->pPppInfo is NULL!");
        }
        else
        {
            ((PPPINFO_S *)(pstFsm->pPppInfo))->pulCurrFsm = pstFsm;

            if (pstFsm->usProtocol != PPP_VSNCP)
            {
                ulPdpIndex = ((PPPINFO_S *)(pstFsm->pPppInfo))->ulRPIndex;

                /* ulPdpIndex���2Byte��ΪIPCP/CCP/LCP����λ,�����û����50000/SC ������Byte��ʹ��*/
                ulPdpIndex |= (VOS_UINT32)pstFsm->usProtocol << 16;
            }
            else
            {
                if (NULL == pstFsm->pProtocolInfo)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_430);
                    PPPC_WARNING_LOG("\r\n PPP_FSM_SetRetransmitTimer: error VSNCPINFO is NULL!");
                    return;
                }
                ulPdpIndex = ((PPPVSNCPINFO_S *)(pstFsm->pProtocolInfo))->ulPDNIndex;
                ulPdpIndex |= (VOS_UINT32)pstFsm->usProtocol << 16;
            }

            PPPC_WARNING_LOG1(
                          "\r\n [ppp]PPP_FSM_SetRetransmitTimer: ulPdpIndex = 0x%x ",
                          ulPdpIndex);

            ulRetVal = VOS_StartRelTimer((HTIMER *)&(pstFsm->ulTimeOutID),
                                        MID_PPPC,
                                        pstFsm->ulTimeOutTime,
                                        ulPdpIndex,
                                        PPPC_FSM_RETRANSMIT_TIMER,
                                        VOS_TIMER_NOLOOP,
                                        VOS_TIMER_PRECISION_0);
            if (ulRetVal != VOS_OK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_431);
            }

        }
    }
}


/*****************************************************************************
 �� �� ��  : PPP_FSM_StartRestartTimer
 ��������  : ����Restart Timer��ʱ��
 �������  : pstFsm   -- ״̬��
             ucPppId  -- PppId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��25��
    ��    ��   : d00314740
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_FSM_StartRestartTimer(VOS_UINT8 ucPppId)
{
    (VOS_VOID)VOS_StartRelTimer((HTIMER*)&(g_hRestartTimer), MID_PPPC, PPP_DEFTIMEOUTTIME,
        (VOS_UINT32)ucPppId, PPPC_LINK_RESTART_TIMER, VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

    g_ucLcpTermMask = PS_TRUE;

    return;
}

/* �ⲿ�¼����� */

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�������ⲿ�¼�.�¼�������Up��Down��Open��Close         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,����Ϊ����ֵ:                                 *
*                      PPP_EVENT_FSM_DOWN:�²�Down                          *
*                      PPP_EVENT_FSM_UP:�²�Up                              *
*                      PPP_EVENT_FSM_OPEN:Open�¼�                          *
*                      PPP_EVENT_FSM_CLOSE:Down�¼�                         *
*                pPara:�¼��Ĳ���,ΪNULL                                    *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ������Э����¼����պ���(��PPP_LCP_ReceiveEventFromCore)     *
****************************************************************************/

VOS_VOID PPP_FSM_ReceiveEvent (PPPFSM_S* pstFsm, VOS_UINT32 ulCmd, CHAR *pPara)
{
    PPP_Debug_FsmEvent(pstFsm, ulCmd);
    switch (ulCmd)
    {
        case PPP_EVENT_FSM_UP:
            PPP_FSM_LowerUp(pstFsm);
            break;

        case PPP_EVENT_FSM_DOWN:
            PPP_FSM_LowerDown(pstFsm);
            break;

        case PPP_EVENT_FSM_OPEN:
            PPP_FSM_Open(pstFsm);
            break;

        case PPP_EVENT_FSM_CLOSE:
            PPP_FSM_Close(pstFsm);
            break;

        default:
            break;
    }

    return;
}



/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�����յ�Up�¼�                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬�����ݽṹ                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent                                       *
****************************************************************************/
VOID PPP_FSM_LowerUp_TestStub(PPPFSM_S *pstFsm)
{
    /* ���¼���̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     Up   |    2     irc,scr/6     -         -         -         -          -         -         -           -
     */

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSED);
            break;

        case PPP_STATE_STARTING:
            if (pstFsm->usProtocol == PPP_LCP)
            {
                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKRCVD);

                /* irc */
                PPP_FSM_irc(pstFsm);

                /* scr */
                PPP_FSM_scr(pstFsm);
            }
            else if (pstFsm->usProtocol == PPP_IPCP)
            {
                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKRCVD);

                /* irc */
                PPP_FSM_irc(pstFsm);
                PPP_FSM_SendConfigReq(pstFsm);
                pstFsm->ucPktId++;
            }
            else
            {
                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_REQSENT);

                /* irc */
                PPP_FSM_irc(pstFsm);

                /* scr */
                PPP_FSM_scr(pstFsm);
            }

            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
        case PPP_STATE_OPENED:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_UP);
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�����յ�Up�¼�                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬�����ݽṹ                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent                                       *
****************************************************************************/
VOID PPP_FSM_LowerUp(PPPFSM_S *pstFsm)
{
    /* ���¼���̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     Up   |    2     irc,scr/6     -         -         -         -          -         -         -           -
     */

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPP_FSM_LowerUp_TestStub(pstFsm);

         return;
    }

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSED);
            break;

        case PPP_STATE_STARTING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_REQSENT);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);

            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
        case PPP_STATE_OPENED:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_UP);
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�����յ�Down�¼�                                       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬�����ݽṹ                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent                                       *
****************************************************************************/
VOID PPP_FSM_LowerDown(PPPFSM_S *pstFsm)
{
    /* ���¼���̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     Down |    -         -         0       tls/1       0         1          1         1         1         tld/1
     */

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_DOWN);
            break;

        case PPP_STATE_CLOSED:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_INITIAL);
            break;

        case PPP_STATE_STOPPED:

            /*���Reset��ʱ��,shiyong 2001/06/07*/

            /*{
               if (((PPPINFO_S*)(pstFsm->pPppInfo))->ulResetTimerId)
               {
                   if(VOS_Timer_Delete(((PPPINFO_S*)(pstFsm->pPppInfo))->ulResetTimerId)!=VOS_OK)
                   {
                       PPP_Debug_CoreEvent(((PPPINFO_S*)(pstFsm->pPppInfo)),PPP_LOG_ERROR,"Fail:Delete Reset  Timer");
                   }

                   ((PPPINFO_S*)(pstFsm->pPppInfo))->ulResetTimerId = 0;
               }
            }*/

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_STARTING);

            /* tls */
            PPP_FSM_tls(pstFsm);
            break;

        case PPP_STATE_CLOSING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_INITIAL);
            break;

        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_STARTING);
            break;

        case PPP_STATE_OPENED:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_STARTING);

            /* tld */
            PPP_FSM_tld(pstFsm);
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�����յ�Open�¼�                                       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬�����ݽṹ                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent                                       *
****************************************************************************/
VOID PPP_FSM_Open(PPPFSM_S *pstFsm)
{
    /* ���¼���̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     Open |  tls/1       1     irc,scr/6     3r        5r        5r         6         7         8           9r
     */

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_STARTING);

            /* ��ʼ��Э��ѡ�� */
            if (pstFsm->pstCallBacks->resetci)
            {
                (*pstFsm->pstCallBacks->resetci)(pstFsm);
                pstFsm->usNakloops = 0;
            }

            /* tls */
            PPP_FSM_tls(pstFsm);
            break;

        case PPP_STATE_STARTING:

            /* ��ʼ��Э��ѡ�� */
            if (pstFsm->pstCallBacks->resetci)
            {
                (*pstFsm->pstCallBacks->resetci)(pstFsm);
                pstFsm->usNakloops = 0;
            }

            /* nothing happened */
            break;

        case PPP_STATE_CLOSED:

            /* ��ʼ��Э��ѡ�� */
            if (pstFsm->pstCallBacks->resetci)
            {
                (*pstFsm->pstCallBacks->resetci)(pstFsm);
                pstFsm->usNakloops = 0;
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_REQSENT);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);
            break;

        case PPP_STATE_STOPPED:

            /* nothing happened */
            break;

        case PPP_STATE_CLOSING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_STOPPING);
            break;

        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
        case PPP_STATE_OPENED:

            /* nothing happened */
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬�����յ�Close�¼�                                      *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬�����ݽṹ                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveEvent                                       *
****************************************************************************/
VOID PPP_FSM_Close(PPPFSM_S *pstFsm)
{
    /* ���¼���̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     Close|    0       tlf/0       2         2         4         4      irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
     */

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:

            /* nothing happened */
            break;

        case PPP_STATE_STARTING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_INITIAL);

            /* tlf */
            PPP_FSM_tlf(pstFsm);    /* ���¼���core����LCP_UP�¼�ʧ�� ȥ������������д */
            PPP_DBG_OK_CNT(PPP_PHOK_1071);

            break;

        case PPP_STATE_CLOSED:

            /* nothing happened */
            break;

        case PPP_STATE_STOPPED:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSED);
            break;

        case PPP_STATE_CLOSING:

            /* nothing happened */
            break;

        case PPP_STATE_STOPPING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSING);
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSING);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* str */
            PPP_FSM_str(pstFsm);
            break;

        case PPP_STATE_OPENED:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (UCHAR)PPP_STATE_CLOSING);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* str */
            PPP_FSM_str(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);
            break;

        default:
            break;
    }

    return;
}

/* ���ձ��Ĵ��� */

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��FSM���ձ���                                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
*                pHead:��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�              *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ������Э��Ľ��ձ��ĺ���                                     *
****************************************************************************/
VOID PPP_FSM_ReceivePacket (PPPFSM_S* pstFsm,
                            UCHAR*    pHead,
                            UCHAR*    pPacket,
                            VOS_UINT32     ulLen,
                            VOS_UINT32     ulRPIndex /* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
)
{
    UCHAR ucCode;
    UCHAR ucId;
    VOS_UINT32 ulCiLen;
    VOS_UINT16 usRetVal = 0;




    if (ulLen < FSM_HDRLEN)
    {
        /* syslog error info */
        PPPC_WARNING_LOG1("PPP_FSM_ReceivePacket: length error, ulLen:%d\n", ulLen);

        return;
    }

    /* ������� */

    /*
     |------------------------- FSM Head ----------------------------|
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
    pPacket
     */

    /* ��ñ������ֶ�ֵ,���ƶ�����ָ�� */
    if (NULL == pPacket)
    {
        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPPC_INFO_LOG1("PPP_FSM_ReceivePacket: Receive Id[%d]", ucId);
    PPP_GETSHORT(ulCiLen, pPacket);

    /* ������� */

    /*
     |------------------------- FSM Head ----------------------------|
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
                                                                    pPacket
     */

    if (ulCiLen > ulLen)
    {
        /* syslog error info */
        PPP_DBG_ERR_CNT(PPP_PHERR_433);
        return;
    }

    /*
       �Ժ�ʹ��ulCiLen������ulLen,��Ϊʵ�ʵı��ĳ��ȿ��ܱ���Ч
       ���ĳ��ȴ�,��PPPOE��,��̫���������padding
     */

    if (ulCiLen < FSM_HDRLEN)
    {
        /* syslog error info */
        PPP_DBG_ERR_CNT(PPP_PHERR_434);
        return;
    }

    /* ���ĳ��ȼ�ȥFSMͷ�ĳ��� */
    ulCiLen -= FSM_HDRLEN;

    switch (ucCode)
    {
        case VEDRSPEC:
            PPP_FSM_ReceiveVendorSpecific(pstFsm, ucId, pHead, pPacket, ulCiLen);

            break;
        case CONFREQ:
            PPP_DBG_OK_CNT(PPP_PHOK_1072);

            /* RCR+ or RCR- event */
            PPP_FSM_ReceiveConfReq(pstFsm, ucId, pHead, pPacket, ulCiLen);
            break;

        case CONFACK:
            PPP_DBG_OK_CNT(PPP_PHOK_1073);

            /* RCA event */
            PPP_FSM_ReceiveConfAck(pstFsm, ucId, pPacket, ulCiLen);
#if  0
            /* �ͷű��� */
            (VOID)PPP_Free(pHead);
#endif
            break;

        case CONFNAK:
        case CONFREJ:

            /* RCN event */
            PPP_FSM_ReceiveConfNakRej(pstFsm, ucId, ucCode, pPacket, ulCiLen);
            PPP_DBG_OK_CNT(PPP_PHOK_1074);
            break;

        case CODEREJ:

            /* RXJ+ or RXJ- event */
            PPP_FSM_ReceiveCodeRej(pstFsm, ucId, pPacket, ulCiLen);
            PPP_DBG_OK_CNT(PPP_PHOK_1075);
            break;

        case TERMREQ:


            /* RTR event */
            PPP_FSM_ReceiveTermReq(pstFsm, ucId);
            break;

        case TERMACK:


            if (NULL == pstFsm)
            {
                break;
            }
            {
                /* RTA event */
                PPP_FSM_ReceiveTermAck(pstFsm, ucId);
            }
            break;

        case PROTREJ:

            /* RXJ+ or RXJ- event */
            PPP_FSM_ReceiveProtocolRej(pstFsm, pPacket, ulCiLen);
            break;

        default:
            PPPC_WARNING_LOG1("PPP_FSM_ReceivePacket: ucCode:0x%x.\n", ucCode);
            if (NULL == pstFsm)
            {
                break;
            }

            if (pstFsm->pstCallBacks->extcode)
            {
                PPPC_WARNING_LOG1("PPP_FSM_ReceivePacket: pstFsm->pstCallBacks->extcode is %p.\n", pstFsm->pstCallBacks->extcode);

                /* ������Э��˽�еı������� */
                usRetVal = (pstFsm->pstCallBacks->extcode)(pstFsm, ucCode, ucId, pHead, pPacket,
                                                         ulCiLen, ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */


            }
            else
            {
                PPPC_WARNING_LOG("PPP_FSM_ReceivePacket: pstFsm->pstCallBacks->extcode is null.\n");

                /* RUC event */
                PPP_FSM_ReceiveUnknownCode(pstFsm, ucId, pHead, pPacket, ulCiLen);
            }

            break;
    }
    (VOS_VOID)usRetVal;
    return;
}


/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCR+��RCR-�¼�(����Config Request����)������             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pHead:  ��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�            *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfReq_TestStub(PPPFSM_S *pstFsm,
                            UCHAR     ucId,
                            UCHAR *   pHead,
                            UCHAR *   pPacket,
                            VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCR+ |    -         -       sta/2 irc,scr,sca/8   4         5        sca/8   sca,tlu/9   sca/8   tld,scr,sca/8
     RCR- |    -         -       sta/2 irc,scr,scn/6   4         5        scn/6     scn/7     scn/6   tld,scr,scn/6
     */
    UCHAR ucCode;

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:
            PPP_DBG_OK_CNT(PPP_PHOK_1078);

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            break;

        case PPP_STATE_CLOSED:
            PPP_DBG_OK_CNT(PPP_PHOK_1079);

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */
            break;

        case PPP_STATE_STOPPED:
            PPP_DBG_OK_CNT(PPP_PHOK_1080);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* �������� */
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1081);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1082);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* sca or scn */
            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            /* state changed */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ״̬ת��ΪPPP_STATE_ACKSENT */
                PPP_DBG_OK_CNT(PPP_PHOK_1083);
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKSENT);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬ת��ΪPPP_STATE_REQSENT */
                PPP_DBG_OK_CNT(PPP_PHOK_1084);
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            }

            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            PPP_DBG_OK_CNT(PPP_PHOK_1085);

            /* state not changed */
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKSENT:

            /* �������� */
            PPP_DBG_OK_CNT(PPP_PHOK_1086);
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1087);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1088);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* sca or scn */
            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            /* state changed */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ״̬ת��ΪPPP_STATE_ACKSENT */
                PPP_DBG_OK_CNT(PPP_PHOK_1089);
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKSENT);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬ת��ΪPPP_STATE_REQSENT */
                PPP_DBG_OK_CNT(PPP_PHOK_1090);
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            }

            break;

        case PPP_STATE_ACKRCVD:

            /* �������� */
            PPP_DBG_OK_CNT(PPP_PHOK_1091);
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1092);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_DBG_OK_CNT(PPP_PHOK_1093);
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* sca or scn */
            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ע�⣺�������鶼�������򽻵�֮ǰ���꣬������ܲ�������
                   ���Ҫ�ȸı�״̬,Ȼ��up
                 */
                PPP_DBG_OK_CNT(PPP_PHOK_1094);

                /* ״̬ת��ΪPPP_STATE_OPENED */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_OPENED);

                /* tlu */
                PPP_FSM_tlu(pstFsm);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬���� */
            }

            break;

        case PPP_STATE_OPENED:
            /* Added start by g00127633 at 2010-12-02 PDSNC05 for DTS2010113004989 ���ݽ�������P90 POS�� */
            PPP_DBG_OK_CNT(PPP_PHOK_1095);
            break;
            /* Added end by g00127633 at 2010-12-02 PDSNC05 for DTS2010113004989 ���ݽ�������P90 POS�� */

        default:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            PPP_DBG_ERR_CNT(PPP_PHERR_443);
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCR+��RCR-�¼�(����Config Request����)������             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pHead:  ��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�            *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfReq(PPPFSM_S *pstFsm,
                            UCHAR     ucId,
                            UCHAR *   pHead,
                            UCHAR *   pPacket,
                            VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCR+ |    -         -       sta/2 irc,scr,sca/8   4         5        sca/8   sca,tlu/9   sca/8   tld,scr,sca/8
     RCR- |    -         -       sta/2 irc,scr,scn/6   4         5        scn/6     scn/7     scn/6   tld,scr,scn/6
     */
    UCHAR ucCode;
    PPPINFO_S* pstPppInfo = NULL;

    PPPC_WARNING_LOG("Recieve PPP_FSM_ReceiveConfReq.");

    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        return;
    }

    /* ���stream 1�յ�Lcp ConReq���ģ���Ҫ�������Ȩ */
    if (pstFsm->usProtocol == PPP_LCP)
    {
        PPPC_ActAccessAuth((PPPINFO_S*)pstFsm->pPppInfo);
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            PPPC_WARNING_LOG3("Illegal State:state,protocol,pppId", pstFsm->ucState, pstFsm->usProtocol, pstPppInfo->ulRPIndex);
            break;

        case PPP_STATE_CLOSED:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */
            break;

        case PPP_STATE_STOPPED:

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* �������� */
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* sca or scn */
            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            /* state changed */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ״̬ת��ΪPPP_STATE_ACKSENT */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKSENT);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬ת��ΪPPP_STATE_REQSENT */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            }

            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);

            /* state not changed */
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKSENT:

            /* �������� */
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* sca or scn */
            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            /* state changed */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ״̬ת��ΪPPP_STATE_ACKSENT */
                PPP_FSM_ChangeState(pstFsm, PPP_STATE_ACKSENT);
                PPPC_WARNING_LOG("Recieve RCR+ Event, State:PPP_STATE_ACKSENT");

            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬ת��ΪPPP_STATE_REQSENT */
                PPP_FSM_ChangeState(pstFsm, PPP_STATE_REQSENT);
                PPPC_WARNING_LOG("Recieve RCR- Event, State:PPP_STATE_REQSENT");
            }

            break;

        case PPP_STATE_ACKRCVD:

            /* �������� */
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            /* ���debug��Ϣ */
            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_PLUS);
            }
            else
            {
                /* ��RCR-�¼� */
                PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCR_SUB);
            }

            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ע�⣺�������鶼�������򽻵�֮ǰ���꣬������ܲ�������
                   ���Ҫ�ȸı�״̬,Ȼ��up
                 */

                /* ״̬ת��ΪPPP_STATE_OPENED */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_OPENED);

                /* tlu */
                PPP_FSM_tlu(pstFsm);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬���� */
            }

            break;

        case PPP_STATE_OPENED:
            PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode);

            if (PPP_LCP == pstFsm->usProtocol)
            {
                if ((PPP_PHASE_AUTHENTICATE == ((PPPINFO_S*)pstFsm->pPppInfo)->usPhase)
                    && (VOS_FALSE == ((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->bReqSendAck))
                {
                    if (ucCode != CONFACK)
                    {
                        (VOS_VOID)PPP_FSM_OpenedStateRenegoStart(pstFsm);
                    }
                }
                else
                {
                    (VOS_VOID)PPP_FSM_OpenedStateRenegoStart(pstFsm);
                }
            }
            else if (PPP_IPCP == pstFsm->usProtocol)
            {
                pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

                if (pstPppInfo != NULL)
                {
                    PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpTotal, PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                    PPPC_INFO_LOG1("****IpcpTotal: ****", g_stPppPerfStatistic.ulIpcpTotal);

                    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);
                }

            }
            else if (PPP_CCP == pstFsm->usProtocol)
            {
                PPP_PerfInc(&g_stPppPerfStatistic.ulCcpTotal, PERF_TYPE_PPPC_CCP_NEGO_ATTEMP, pstPppInfo->bEhrpdUser);
            }

            /* Added start by y00202564 at 2012-03-27 for ipv6����ͳ��,IPv6CPЭ�̳��Դ��� */
            else if (PPP_IPV6CP == pstFsm->usProtocol)
            {
                pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
                PPPC_INFO_LOG("\r\n PPP_FSM_ReceiveConfReq,IPV6_PerfStatistic Attempt: enter!");

                /*Added start by y00202564 at 2012-04-20 for PCF����ͳ��,IPv6CPЭ�̳��Դ���*/
                A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM, pstPppInfo->ulPcfIP);
                /*Added end by y00202564 at 2012-04-20 for PCF����ͳ��,IPv6CPЭ�̳��Դ���*/

            }
            /* Added end by y00202564 at 2012-03-27 for ipv6����ͳ��,IPv6CPЭ�̳��Դ��� */

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* ����sca��scn��ͬ,ֻ�Ƿ��ͱ��ĵ�code��ͬ */
            PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

            if (ucCode == CONFACK)
            {
                /* ��RCR+�¼� */
                /* ״̬ת��ΪPPP_STATE_ACKSENT */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKSENT);
            }
            else
            {
                /* ��RCR-�¼� */
                /* ״̬ת��ΪPPP_STATE_REQSENT */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            }

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            PPPC_WARNING_LOG3("Unkonw State:state,protocol,pppId", pstFsm->ucState, pstFsm->usProtocol, pstPppInfo->ulRPIndex);
            break;
    }

    return;
}


/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCA�¼�(����Config Ack����)������                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfAck_TestStub(PPPFSM_S *pstFsm,
                            UCHAR     ucId,
                            UCHAR *   pPacket,
                            VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCA  |    -         -       sta/2     sta/3       4         5        irc/7     scr/6x  irc,tlu/9   tld,scr/6x
     */
    PPPINFO_S* pstPppInfo = NULL;

    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_446);
        return;
    }

    if (pstFsm->usProtocol == PPP_LCP || pstFsm->usProtocol == PPP_IPCP)
    {
        return;
    }

    /* �Ƚϱ���ID */
    if ((UCHAR)(ucId + 1) != pstFsm->ucPktId)
    {
        /* wrong id, discard */
        PPPC_WARNING_LOG2("\r\n Wrong Id:Send Id :[%d], Receive Id[%d]", pstFsm->ucPktId, ucId);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Wrong id, packet discarded! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_447);
        return;
    }

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCA);

    /* ������������ */
    if (pstFsm->pstCallBacks->ackci)
    {
        if ((*pstFsm->pstCallBacks->ackci)(pstFsm, pPacket, ulLen) == VOS_ERR)
        {
            /* bad packet, discard */
            /* ��ʾ������Ϣ */
            PPP_DBG_ERR_CNT(PPP_PHERR_448);
            return;
        }
    }
    else
    {
        if (ulLen != 0)
        {
            /* bad packet, discard */
            /* ��ʾ������Ϣ */
            PPP_DBG_ERR_CNT(PPP_PHERR_449);
            return;
        }
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCA);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */

            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:

            /* state not changed */

            break;

        case PPP_STATE_REQSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKRCVD);

            /* irc */
            PPP_FSM_irc(pstFsm);
            break;

        case PPP_STATE_ACKRCVD:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            break;

        case PPP_STATE_ACKSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_OPENED);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* tlu */
            PPP_FSM_tlu(pstFsm);

            break;

        case PPP_STATE_OPENED:

            if (pstFsm->usProtocol == PPP_LCP)
            {
                if (VOS_OK != PPP_FSM_OpenedStateRenegoStart(pstFsm))
                {
                    return;
                }

                PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1123);
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    /* Added start by ZhangJun HT04406 at 2005-10-11   for PDSN�����Ż� */
 #ifdef __PRODUCT_TYPE_PDSN80
    /* Deleted start by dongenjie 28913 at 2008-03-31 PDSN V9R7 Demo for ��ֲ */
    /* Deleted end by dongenjie 28913 at 2008-03-31 PDSN V9R7 Demo for ��ֲ */
 #endif
    /* Added end by ZhangJun HT04406 at 2005-10-11   for PDSN�����Ż� */

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCA�¼�(����Config Ack����)������                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfAck(PPPFSM_S *pstFsm,
                            UCHAR     ucId,
                            UCHAR *   pPacket,
                            VOS_UINT32     ulLen)
{

    PPPINFO_S* pstPppInfo = NULL;
    PPPC_WARNING_LOG("\r\n PPP_FSM_ReceiveConfAck \r\n");

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
             PPP_FSM_ReceiveConfAck_TestStub(pstFsm, ucId, pPacket, ulLen);
             return;
    }

    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCA  |    -         -       sta/2     sta/3       4         5        irc/7     scr/6x  irc,tlu/9   tld,scr/6x
     */
    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_450);
        return;
    }

    /* �Ƚϱ���ID */
    if ((UCHAR)(ucId + 1) != pstFsm->ucPktId)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_15);
        /* wrong id, discard */
        PPPC_WARNING_LOG2("\r\n Wrong Id:Send Id :[%d], Receive Id[%d]", pstFsm->ucPktId, ucId);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Wrong id, packet discarded! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_451);
        return;
    }

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCA);

    /* ������������ */
    if (pstFsm->pstCallBacks->ackci)
    {
        if ((*pstFsm->pstCallBacks->ackci)(pstFsm, pPacket, ulLen) == VOS_ERR)
        {
            /* bad packet, discard */
            /* ��ʾ������Ϣ */
            PPP_DBG_ERR_CNT(PPP_PHERR_452);
            return;
        }
    }
    else
    {
        if (ulLen != 0)
        {
            /* bad packet, discard */
            /* ��ʾ������Ϣ */
            PPP_DBG_ERR_CNT(PPP_PHERR_453);
            return;
        }
    }

    PPPC_INFO_LOG1("\r\n PPP_FSM_ReceiveConfAck pstFsm->ucState\r\n", pstFsm->ucState);

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCA);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */

            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:

            /* state not changed */

            break;

        case PPP_STATE_REQSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKRCVD);
            PPPC_INFO_LOG1("\r\n state changed PPP_FSM_ReceiveConfAck pstFsm->ucState\r\n", pstFsm->ucState);

            /* irc */
            PPP_FSM_irc(pstFsm);
            break;

        case PPP_STATE_ACKRCVD:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            break;

        case PPP_STATE_ACKSENT:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_OPENED);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* tlu */
            PPP_FSM_tlu(pstFsm);

            break;

        case PPP_STATE_OPENED:

            if (pstFsm->usProtocol == PPP_LCP)
            {
                if (VOS_OK != PPP_FSM_OpenedStateRenegoStart(pstFsm))
                {
                    return;
                }

                PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1124);
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    return;
}



/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCN�¼�(����Config Nak��Rej����)������                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfNakRej_TestStub(PPPFSM_S *pstFsm,
                               UCHAR     ucId,
                               UCHAR     ucCode,
                               UCHAR *   pPacket,
                               VOS_UINT32     ulLen)
{
    PPPINFO_S* pstPppInfo = NULL;
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCN  |    -         -       sta/2     sta/3       4         5      irc,scr/6   scr/6x  irc,scr/8   tld,scr/6x
     */
    VOS_UINT16 (*pfFunc)(PPPFSM_S *, UCHAR *, VOS_UINT32);


    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_454);
        return;
    }

    /* �Ƚϱ���ID */
    if ((UCHAR)(ucId + 1) != pstFsm->ucPktId)
    {
        /* wrong id, discard */
        PPPC_INFO_LOG2("\r\n Wrong Id:Send Id :[%d], Receive Id[%d]", pstFsm->ucPktId, ucId);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Wrong id, packet discarded! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_455);
        return;
    }

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCN);

    /* ������������ */
    pfFunc = (ucCode == CONFNAK) ? pstFsm->pstCallBacks->nakci :
             pstFsm->pstCallBacks->rejci;
    if (!pfFunc || pfFunc(pstFsm, pPacket, ulLen) == VOS_ERR)
    {
        /* bad packet, discard */
        /* ��ʾ������Ϣ */
        PPP_DBG_ERR_CNT(PPP_PHERR_456);
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_RCN);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */
            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKSENT:

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* state not changed */
            break;

        case PPP_STATE_ACKRCVD:
            /* state changed */
            if ((pstFsm->usProtocol == PPP_IPCP)|| (pstFsm->usProtocol == PPP_LCP))
            {
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_ACKRCVD);

                /* scr */
                PPP_FSM_SendConfigReq(pstFsm);
                pstFsm->ucPktId++;
            }
            else
            {
                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

                /* scr */
                PPP_FSM_scr(pstFsm);
            }

            break;

        case PPP_STATE_OPENED:

            if (pstFsm->usProtocol == PPP_LCP)
            {
                if (VOS_OK != PPP_FSM_OpenedStateRenegoStart(pstFsm))
                {
                    return;
                }

                PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1125);
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    return;
}


/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RCN�¼�(����Config Nak��Rej����)������                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveConfNakRej(PPPFSM_S *pstFsm,
                               UCHAR     ucId,
                               UCHAR     ucCode,
                               UCHAR *   pPacket,
                               VOS_UINT32     ulLen)
{
    PPPINFO_S* pstPppInfo = NULL;
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RCN  |    -         -       sta/2     sta/3       4         5      irc,scr/6   scr/6x  irc,scr/8   tld,scr/6x
     */
    VOS_UINT16 (*pfFunc)(PPPFSM_S *, UCHAR *, VOS_UINT32);

    PPPC_WARNING_LOG("\r\n PPP_FSM_ReceiveConfNakRej. \r\n");

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPP_FSM_ReceiveConfNakRej_TestStub(pstFsm, ucId, ucCode, pPacket, ulLen);

         return;
    }


    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_457);
        return;
    }

    /* �Ƚϱ���ID */
    if (ucId >= pstFsm->ucPktId)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_16);
        /* wrong id, discard */
        PPPC_INFO_LOG2("\r\n Wrong Id:Send Id :[%d], Receive Id[%d]", pstFsm->ucPktId, ucId);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Wrong id, packet discarded! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_458);
        return;
    }

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RCN);

    /* ������������ */
    pfFunc = (ucCode == CONFNAK) ? pstFsm->pstCallBacks->nakci :
             pstFsm->pstCallBacks->rejci;
    if (!pfFunc || pfFunc(pstFsm, pPacket, ulLen) == VOS_ERR)
    {
        /* bad packet, discard */
        /* ��ʾ������Ϣ */
        PPP_DBG_ERR_CNT(PPP_PHERR_459);
        return;
    }

    PPPC_INFO_LOG1("\r\n pstFsm->ucState\r\n", pstFsm->ucState);

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_RCN);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */
            break;

        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKSENT:

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* scr */
            PPP_FSM_scr(pstFsm);
            PPPC_INFO_LOG1("\r\n case pstFsm->ucState\r\n", pstFsm->ucState);

            /* state not changed */
            break;

        case PPP_STATE_ACKRCVD:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            break;

        case PPP_STATE_OPENED:

            if (pstFsm->usProtocol == PPP_LCP)
            {
                if (VOS_OK != PPP_FSM_OpenedStateRenegoStart(pstFsm))
                {
                    return;
                }

                PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1126);
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RXJ+��RXJ-�¼�(����Code Rej����)������                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveCodeRej(PPPFSM_S *pstFsm,
                            UCHAR     ucId,
                            UCHAR *   pPacket,
                            VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RXJ+ |    -         -         2         3         4         5          6         6         8           9
     RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3      tlf/3     tlf/3     tlf/3   tld,irc,str/5
     */
    UCHAR ucRejectedCode, ucRejectedId;

    /* ucEvent == 0��ʾRXJ-�¼�,ucEvent == 1��ʾRXJ+�¼�,*/
    UCHAR ucEvent;


    /* ������� */

    /*
                      0                   1
                      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     ...  FSM Head   |     Code      |  Identifier   |
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                    /|\
                     |
                     pPacket
     */

    /* �����������ݣ��ж���RXJ-�¼�����RXJ+�¼� */
    if (ulLen >= 2)
    {
        if (NULL == pPacket)
        {
            PPPC_WARNING_LOG("pPacket is Null_PTR");
            return;
        }

        PPP_GETCHAR(ucRejectedCode, pPacket);
        PPP_GETCHAR(ucRejectedId, pPacket);

        /* ������� */

        /*
                          0                   1
                          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
        -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         ...  FSM Head   |     Code      |  Identifier   |
        -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                                                        /|\
                                                         |
                                                         pucPacket
         */
        if (NULL == pstFsm)
        {
            PPPC_WARNING_LOG("pstFsm is Null_PTR");
            return;
        }

        /*
           RFC1661, 4.3 Events, Page 20
           Receive-Code-Reject, Receive-Protocol-Reject (RXJ+,RXJ-)
              This event occurs when a Code-Reject or a Protocol-Reject packet
              is received from the peer.

              The RXJ+ event arises when the rejected value is acceptable, such
              as a Code-Reject of an extended code, or a Protocol-Reject of a
              NCP.  These are within the scope of normal operation.  The
              implementation MUST stop sending the offending packet type.

              The RXJ- event arises when the rejected value is catastrophic,
              such as a Code-Reject of Configure-Request, or a Protocol-Reject
              of LCP!  This event communicates an unrecoverable error that
              terminates the connection.
        */
        if ((ucRejectedCode == CONFREQ) || (ucRejectedId != pstFsm->ucPktId - 1))
        {
            /* Reject�ҵ�Config Request����,��reject�Ĳ������ϴη��ı���ID */
            /* ��RXJ-�¼� */
            ucEvent = 0;
        }
        else
        {
            /* Reject��������,��RXJ+�¼� */
            ucEvent = 1;
        }
    }
    else
    {
        /* ������,��Ϊ��RXJ-�¼� */
        ucEvent = 0;
    }

    if (ucEvent == 1)   /* RXJ+�¼� */
    {
        /* ���debug��Ϣ */
        PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_PLUS);

        switch (pstFsm->ucState)
        {
            case PPP_STATE_INITIAL:
            case PPP_STATE_STARTING:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_PLUS);
                break;

            case PPP_STATE_CLOSED:
            case PPP_STATE_STOPPED:
            case PPP_STATE_CLOSING:
            case PPP_STATE_STOPPING:
            case PPP_STATE_REQSENT:
            case PPP_STATE_ACKSENT:
            case PPP_STATE_OPENED:

                /* state not changed */
/* EAP-dev */
                /* "If the MS receives the Code-Reject, the MS shall stop resending
                   the Version/Capability Indication packet."
                   from X.S0011-002-D_v2.0, 8.2 MS Requirement */
                if (VOS_NULL_PTR != pstFsm->hVendorSpecificTimeID)
                {
                    (VOS_VOID)VOS_StopRelTimer(&(pstFsm->hVendorSpecificTimeID));
                    pstFsm->hVendorSpecificTimeID = VOS_NULL_PTR;
                }

                break;

            case PPP_STATE_ACKRCVD:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
                break;

            default:
                break;
        }
    } /* ucEvent == 1 */
    else    /* RXJ-�¼� */
    {
        /* ���debug��Ϣ */
        PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_SUB);
        if (NULL == pstFsm)
        {
            PPPC_WARNING_LOG("pstFsm is Null_PRT");
            return;
        }

        switch (pstFsm->ucState)
        {
            case PPP_STATE_INITIAL:
            case PPP_STATE_STARTING:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_SUB);
                break;

            case PPP_STATE_CLOSED:
            case PPP_STATE_CLOSING:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_CLOSED);

                /* tlf */
                PPP_FSM_RleseCode(pstFsm,
                                  AM_RELCODE_PPP_LCP_NEGONAK,
                                  AM_RELCODE_PPP_IPCP_NEGONAK,
                                  AM_RELCODE_PPP_IPV6CP_NEGONAK,
                                  AM_RELCODE_PPP_VSNCP_NEGONAK);
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1127);

                break;

            case PPP_STATE_STOPPED:
            case PPP_STATE_STOPPING:
            case PPP_STATE_REQSENT:
            case PPP_STATE_ACKRCVD:
            case PPP_STATE_ACKSENT:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPED);

                /* tlf */
                PPP_FSM_RleseCode(pstFsm,
                                  AM_RELCODE_PPP_LCP_NEGONAK,
                                  AM_RELCODE_PPP_IPCP_NEGONAK,
                                  AM_RELCODE_PPP_IPV6CP_NEGONAK,
                                  AM_RELCODE_PPP_VSNCP_NEGONAK);
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1128);

                break;

            case PPP_STATE_OPENED:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPING);

                /* irc */
                PPP_FSM_irc(pstFsm);

                /* str */
                PPP_FSM_str(pstFsm);

                /* tld */
                PPP_FSM_tld(pstFsm);

                break;

            default:
                break;
        }
    } /* ucEvent == 0 */
    (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RXJ+��RXJ-�¼�(����Protocol Rej����)������               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveProtocolRej(PPPFSM_S *pstFsm,
                                UCHAR *   pPacket,
                                VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RXJ+ |    -         -         2         3         4         5          6         6         8           9
     RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3      tlf/3     tlf/3     tlf/3   tld,irc,str/5
     */
    VOS_UINT16 usRejectedProtocol = 0;

    /* ucEvent == 0��ʾRXJ-�¼�,ucEvent == 1��ʾRXJ+�¼�,*/
    UCHAR ucEvent;

    PPPFSM_S *pstRejectedFsm;


    /* ������� */

    /*
                      0                   1
                      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     ...  FSM Head   |       Rejected Protocol       |
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
                     pPacket
     */

    /* �����������ݣ��ж���RXJ-�¼�����RXJ+�¼� */
    if (ulLen >= 2)
    {
        if (NULL == pPacket)
        {
            return;
        }

        PPP_GETSHORT(usRejectedProtocol, pPacket);

        /* ������� */

        /*
                          0                   1
                          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
        -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         ...  FSM Head   |      Rejected Protocol        |
        -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |
                                                         pPacket
         */
        if (usRejectedProtocol == PPP_LCP)
        {
            /* Reject�ҵ�LCPЭ��,��RXJ+�¼� */
            ucEvent = 0;
        }
        else
        {
            /* Reject����Э��,�Ƕ�ӦЭ���RXJ-�¼� */
            if (NULL == pstFsm)
            {
                return;
            }

            pstRejectedFsm = PPP_Core_GetFsmByProtocol(pstFsm->pPppInfo, usRejectedProtocol);
            if (pstRejectedFsm)
            {
                /* �ҵ���ӦЭ���״̬��, �Ƕ�ӦЭ���RXJ-�¼� */
                ucEvent = 1;
                pstFsm = pstRejectedFsm;
            }
            else
            {
                /* �Ҳ�����Э���״̬��,������PAP / CHAP�� */
                PPP_Core_RejectProtocol(pstFsm->pPppInfo, usRejectedProtocol);
                return;
            }
        }
    }
    else
    {
        /* ������,��Ϊ��LCP��RXJ+�¼� */
        ucEvent = 0;
    }

    if (ucEvent == 1)
    {
        /* RXJ- */
        PPP_FSM_RXJ_Sub(pstFsm);
    }
    else
    {
        /* RXJ+ */
        PPP_FSM_RXJ_Plus(pstFsm);
    }
    (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RXJ+�¼�(LCP Protocol Rej������ָ���ܾ���Э��)������     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
VOID PPP_FSM_RXJ_Plus(PPPFSM_S *pstFsm)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RXJ+ |    -         -         2         3         4         5          6         6         8           9
     */

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_PLUS);

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_PLUS);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKSENT:

            /* state not changed */
            break;

        case PPP_STATE_ACKRCVD:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            break;

        case PPP_STATE_OPENED:

            /* state not changed */
            break;
        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RXJ-�¼�((LCP Protocol Rej������ָ���ܾ���Э��))������   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
VOID PPP_FSM_RXJ_Sub(PPPFSM_S *pstFsm)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3      tlf/3     tlf/3     tlf/3   tld,irc,str/5
     */

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_SUB);

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RXJ_SUB);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_CLOSING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_CLOSED);

            /* tlf */
            PPP_FSM_tlf(pstFsm);
            PPP_DBG_OK_CNT(PPP_PHOK_1129);

            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:

            /* ��������ԭ��ֵ */
            PPP_FSM_RleseCode(pstFsm,
                      AM_RELCODE_PPP_LCP_NEGONAK,
                      AM_RELCODE_PPP_IPCP_NEGONAK,
                      AM_RELCODE_PPP_IPV6CP_NEGONAK,
                      AM_RELCODE_PPP_VSNCP_NEGONAK);
         //lint -fallthrough
        case PPP_STATE_STOPPED:
        case PPP_STATE_STOPPING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPED);

            /* tlf */
            PPP_FSM_tlf(pstFsm);
            PPP_DBG_OK_CNT(PPP_PHOK_1130);
           //lint -fallthrough
            break;

        case PPP_STATE_OPENED:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPING);

            /* irc */
            PPP_FSM_irc(pstFsm);

            /* ��������ԭ��ֵ */
            PPP_FSM_RleseCode(pstFsm,
                      AM_RELCODE_PPP_LCP_NEGONAK,
                      AM_RELCODE_PPP_IPCP_NEGONAK,
                      AM_RELCODE_PPP_IPV6CP_NEGONAK,
                      AM_RELCODE_PPP_VSNCP_NEGONAK);
            /* str */
            PPP_FSM_str(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RTR�¼�(����Terminate Req����)������                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveTermReq(PPPFSM_S *pstFsm, UCHAR ucId)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RTR  |    -         -       sta/2     sta/3     sta/4     sta/5      sta/6     sta/6     sta/6   tld,zrc,sta/5
     */

    PPPINFO_S *pstPppInfo = NULL;     /* ADD BY QUQIN for BYHD4207 */

    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        return;
    }

    /* SNMP������: ��������ͳ��ԭ��ֵ: ms����ȥ�� */
    PPP_SNMP_PERF_SET_FAILREASON_MS_RELEASE(pstPppInfo, pstFsm);

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RTR);

    /* ��������ԭ��ֵ */
    PPP_FSM_RleseCode(pstFsm,
              AM_RELCODE_PPP_LCP_USERDEL,
              AM_RELCODE_PPP_IPCP_USERDEL,
              AM_RELCODE_PPP_IPV6CP_USERDEL,
              AM_RELCODE_PPP_VSNCP_USERDEL);

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RTR);
            /* sta */
            PPP_FSM_sta(pstFsm, ucId);
            /* tlf */
            PPP_FSM_tlf(pstFsm);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* state not changed */
            break;

        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
            ((PPPINFO_S*)pstFsm->pPppInfo)->bFailFlag = PPPUSERDOWN;
            /* tld,zrc,sta/5 */

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPING);
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, 0x20);

            PPP_DBG_OK_CNT(PPP_PHOK_1131);

            /* zrc */
            PPP_FSM_zrc(pstFsm);

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* ������ʱ�� */

            /* ��Ϊ��ACKRCVD״̬��û��������ʱ����״̬�����������
               �޷�������ת��
             */
            PPP_FSM_SetRetransmitTimer(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);
            /*End of liushuang*/
            break;

        case PPP_STATE_OPENED:

            ((PPPINFO_S*)pstFsm->pPppInfo)->bFailFlag = PPPUSERDOWN;

            /* tld,zrc,sta/5 */

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPING);


            /* zrc */
            PPP_FSM_zrc(pstFsm);

            /* sta */
            PPP_FSM_sta(pstFsm, ucId);

            /* ������ʱ�� */

            /* ע��!!!!�˴�������ʱ��,��Ϊ�˵�һ��ʱ��,
               ���Է�һ���յ�Terminate Ack�Ļ��� */
            if (PPP_LCP == pstFsm->usProtocol)
            {
                PPP_FSM_SetRetransmitTimer(pstFsm);

                /* BEGIN: Added for PN:���pppЭ�̶�ʱ����Դ�������� by wangyong 00138171, 2013/12/21 */
                (VOID)PPP_NodeAdd(pstPppInfo->ulRPIndex, 0, PPP_NEGO_LIST_NODE_MS_RELEASE_START);
                /* END:   Added for PN:���pppЭ�̶�ʱ����Դ�������� by wangyong 00138171, 2013/12/21 */

                /* ����restart timer */
                if (PPPC_PPP_ID_FOR_ACCESS_AUTH == pstPppInfo->ulRPIndex)
                {
                    /* ֪ͨRPA�����Ȩ���� */
                    PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_ACCESS_AUTH_RCV_LCP_TERMINATE);

                    /* ������ڽ��н����Ȩ,�����־λ */
                    PPPC_ChangeAccessAuthState(PS_FALSE, (VOS_UINT8)(pstPppInfo->ulRPIndex));

                }
                else
                {
                    PPP_FSM_StartRestartTimer((VOS_UINT8)(pstPppInfo->ulRPIndex));
                }
            }

            /* tld */
            PPP_FSM_tld(pstFsm);
            if ( PPP_IPCP == pstFsm->usProtocol)
            {
                /* ֧��ͨ��IPCP terminate reqɾ����ջ���� */
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1132);
            }

            if ( PPP_IPV6CP == pstFsm->usProtocol)
            {
                /* ֧��ͨ��IPV6CP terminate reqɾ����ջ���� */
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1133);

            }

            if (PPP_VSNCP == pstFsm->usProtocol)
            {
                /* ֧��ͨ��vsncp terminate reqɾ����ջ���� */
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1134);

                g_ucLcpTermMask = PS_TRUE;
            }

            if (PPP_CCP == pstFsm->usProtocol)
            {
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1135);
            }


            PPP_DBG_OK_CNT(PPP_PHOK_1136);
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RTA�¼�(����Terminate Ack����)������                     *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveTermAck(PPPFSM_S *pstFsm, UCHAR ucId)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RTA  |    -         -         2         3       tlf/2     tlf/3        6         6         8       tld,scr/6
     */
    PPPINFO_S *pstPppInfo = NULL;     /* ADD BY QUQIN for BYHD4207 */


    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RTA);
    if (NULL == pstFsm)
    {
        return;
    }


    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_461);
        return;
    }

    /* �Ƚϱ���ID */
    if ((UCHAR)(ucId + 1) != pstFsm->ucPktId)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_17);
        /* wrong id, discard */
        PPPC_WARNING_LOG4(
                     "\r\n PPP_FSM_ReceiveTermAck:: Wrong Id:Send Id :[%d], Receive Id[%d], protocol[%x], state[%d] ",
                     pstFsm->ucPktId, ucId, pstFsm->usProtocol, pstFsm->ucState);

        PPPC_WARNING_LOG1("sRetransmits[%u] ",  pstFsm->sRetransmits);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Wrong id, packet discarded! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_462);
        return;
    }


    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RTA);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:

            /* state not changed */
            break;

        case PPP_STATE_CLOSING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_CLOSED);

            /* tlf */
            PPP_FSM_tlf(pstFsm);     /* �˴��ǵ���PPP_Lcp_NegotiationDown������ȥ����Ϣ������������ */
            PPP_DBG_OK_CNT(PPP_PHOK_1137);

            break;

        case PPP_STATE_STOPPING:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPED);

            /* tlf */
            PPP_FSM_tlf(pstFsm);      /* �˴����յ�CodeRej��Ϣ */
            PPP_DBG_OK_CNT(PPP_PHOK_1138);

            break;

        case PPP_STATE_REQSENT:

            /* state not changed */
            break;

        case PPP_STATE_ACKRCVD:

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);
            break;

        case PPP_STATE_ACKSENT:

            /* state not changed */
            break;

        case PPP_STATE_OPENED:

            if (pstFsm->usProtocol == PPP_LCP)
            {
                if (VOS_OK != PPP_FSM_OpenedStateRenegoStart(pstFsm))
                {
                    return;
                }

                PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1139);
            }

            /* state changed */
            PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

            /* scr */
            PPP_FSM_scr(pstFsm);

            /* tld */
            PPP_FSM_tld(pstFsm);

            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��RUC�¼�(���յ���֧�ֻ���ʶ��ı���)������              *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pHead:  ��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�            *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOID PPP_FSM_ReceiveUnknownCode(PPPFSM_S *pstFsm,
                                UCHAR     ucId,
                                UCHAR *   pHead,
                                UCHAR *   pPacket,
                                VOS_UINT32     ulLen)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
     RUC  |    -         -       scj/2     scj/3     scj/4     scj/5      scj/6     scj/7     scj/8       scj/9
     */

    /* ���debug��Ϣ */
    PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RUC);

    if (NULL == pstFsm)
    {
        return;
    }

    switch (pstFsm->ucState)
    {
        case PPP_STATE_INITIAL:
        case PPP_STATE_STARTING:

            /* Illegal Event */
            PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_RUC);
            break;

        case PPP_STATE_CLOSED:
        case PPP_STATE_STOPPED:
        case PPP_STATE_CLOSING:
        case PPP_STATE_STOPPING:
        case PPP_STATE_REQSENT:
        case PPP_STATE_ACKRCVD:
        case PPP_STATE_ACKSENT:
        case PPP_STATE_OPENED:

            /* scj */
            PPP_FSM_scj(pstFsm, pHead, pPacket, ulLen);

            /* state not changed */
            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ʱ����ʱ������,����TO+��TO-�¼�                        *
* MODIFY DATE  ��                                                           *
* INPUT        ��pFsm: ״̬��                                               *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ����ʱ��                                                     *
****************************************************************************/
//[EBCC]2542
VOID PPP_FSM_TimeOut(VOID *pFsm)
{
    /* ���¼���״̬ת��ͼ */

    /*
     | State
     |    0         1         2         3         4         5           6         7         8           9
    Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
    ------+------------------------------------------------------------------------------------------------------
      TO+ |    -         -         -         -       str/4     str/5      scr/6     scr/6     scr/8         -
      TO- |    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
     */

    /* ucEvent == 0��ʾTO-�¼�,ucEvent == 1��ʾTO+�¼�,*/
    UCHAR ucEvent;
    PPPFSM_S *pstFsm = NULL;
    VOS_UINT32 ulRPIndex;
    PPPINFO_S *pstPppInfo = NULL;
    VOS_UINT16  usProtocol = 0;
    VOS_UINT32 ulPDNIndex = 0;
    VOS_UINT32 enResult = VOS_OK;
    PDN_CONTEXT_S *pstPDNContext = NULL;
    PPPVSNCPINFO_S stVSNCPInfo = {0};

    extern PPPFSMCALLBACK_S g_stIpcpCallbacks;
    extern PPPFSMCALLBACK_S g_stLcpCallbacks;
    extern PPPFSMCALLBACK_S g_stCcpCallbacks;
    extern PPPFSMCALLBACK_S g_stIpv6cpCallbacks;

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPPC_WARNING_LOG("SHOULD NEVER HAPPEN");

         return;
    }

    ulRPIndex = (VOS_UINT32)pFsm;

    PPPC_INFO_LOG1(
                          "\r\n [ppp]PPP_FSM_TimeOut: ulRPIndex = %x",
                          ulRPIndex);

    /* ��ȡ��Э���,ȡ���2bits */
    usProtocol = (ulRPIndex & 0xffff0000) >> 16;

    /* �ָ�RpIndex */
    ulRPIndex &= 0x0000ffff;

    PPPC_INFO_LOG2(
                          "\r\n [ppp]PPP_FSM_TimeOut: ulPdpIndex = %d ucProtocol %x",
                          ulRPIndex,
                          usProtocol);

    /* BEGIN: Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
    if (usProtocol == PPP_VSNCP)
    {
        ulPDNIndex = ulRPIndex;
        enResult = PPP_GetPDNContextByPDNID((UCHAR)ulPDNIndex,
                                            &pstPDNContext);
        if ((VOS_OK != enResult) || (VOS_NULL == pstPDNContext))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_474);
            PPPC_WARNING_LOG2(
                         "\r\n PPP_FSM_TimeOut: ulPdnIndex(%d) is ERR! pstPDNContext(%x)",
                         ulPDNIndex,
                         pstPDNContext);
            return;
        }
        enResult = PPPC_GetPppIdByPdn((VOS_UINT8)ulPDNIndex, (VOS_UINT8 *)&ulRPIndex);
        if (VOS_OK != enResult)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_474);
            PPPC_WARNING_LOG2(
                         "\r\n PPP_FSM_TimeOut: ulPdnIndex(%d) is ERR! ulRPIndex(%d)",
                         ulPDNIndex,
                         ulRPIndex);
            return;
        }
    }
    /* END:   Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */

    if (ulRPIndex <= PPP_MAX_USER_NUM)
    {
        GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulRPIndex);
        if (NULL == pstPppInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_475);
            PPPC_WARNING_LOG2("\r\n[ppp]: excp rpindex[%lu] Protocol[%lu] NULL!",
                          ulRPIndex, usProtocol);
            return;
        }
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_476);
        PPPC_WARNING_LOG1("\r\n PPP_FSM_TimeOut :ulRPIndex is invalid! error, %d", ulRPIndex);
        return;
    }


    /* ֻ����NCP�׶ε�Э��1:IPCP,2:CCP */
    if (PPP_LCP == usProtocol)
    {
        if (NULL == pstPppInfo->pstLcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_477);
            PPPC_WARNING_LOG1("\r\n PPP_FSM_TimeOut :g_pstPppPool[%d] lcp cb not exist", ulRPIndex);

            return;
        }
        pstFsm = &(((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stFsm);
    }
    else if (PPP_IPCP == usProtocol)
    {
        if (NULL == pstPppInfo->pstIpcpInfo)
        {
            PPPC_WARNING_LOG1("\r\n [ppp]PPP_FSM_TimeOut :g_pstPppPool[%d] ipcp cb not existr",
                          ulRPIndex);
            return;
        }
        pstFsm = &(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stFsm);
    }
    else if (PPP_IPV6CP == usProtocol)
    {
        if ( NULL == pstPppInfo->pstIpV6cpInfo )
        {
            PPPC_WARNING_LOG1("\r\n [ppp]PPP_FSM_TimeOut :g_pstPppPool[%d] ipv6cp cb not existr",
                          ulRPIndex);
            return;
        }
        pstFsm = &(((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stFsm);
    }
    /* BEGIN: Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
    else if (PPP_VSNCP == usProtocol)
    {
        /*lint -e613*/
        pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
        /* ��ʼ��VSNCP���ƿ� */
        PPP_VSNCP_Init(pstPppInfo,
                       &stVSNCPInfo,
                       pstPDNContext,
                       pstPDNContext->stEhrpd.stVSNCP.ucPDNID);
        /*lint +e613*/
        pstFsm = &(stVSNCPInfo.stFsm);
    }
    /* END:   Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
    else if (PPP_CCP == usProtocol)
    {
        if (NULL == pstPppInfo->pstCcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_480);
            PPPC_WARNING_LOG1("\r\n [ppp]PPP_FSM_TimeOut :g_pstPppPool[%d] lcp cb not existr",
                          ulRPIndex);
            return;
        }

        pstFsm = &(((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->stFsm);
    }


    /* Modified start by g34667 at 2004-07-20 R001B03D005 for D03087
       �ڶ�ʱ����Ϣ����л�û�д����ڼ�PPP���ƿ���ܱ�ɾ��, ��ʱ����Ϣ������
     */
    if (VOS_NULL_PTR == pstFsm)
    {
        PPPC_WARNING_LOG2("pstFsm is NULL", usProtocol, ulRPIndex);
        return;
    }

    /* caihaitao for D09949 start */

    /* ���ڳ�ʱ��Ϣ����ʱ��PPP���ƿ�����Ѿ����ͷš����pstFsm->pPppInfo��ָ��Ҳ�Ѿ�
    ��Ч�����ֱ�ӷ��ʿ��ܳ���DA�쳣��������������������Ҫ���Ӷ�pstFsm��ָ
    ������ݽ��кϷ��Լ�顣�˴�ʹ��pstCallBacks��usProtocol��Ϊ��������������Ч���ж�*/
    if (((pstFsm->usProtocol != PPP_IPCP) || (pstFsm->pstCallBacks != (&g_stIpcpCallbacks)) || (PPP_IPCP != usProtocol))
       && ((pstFsm->usProtocol != PPP_LCP) || (pstFsm->pstCallBacks != (&g_stLcpCallbacks)) || (PPP_LCP != usProtocol))
       && ((pstFsm->usProtocol != PPP_CCP) || (pstFsm->pstCallBacks != (&g_stCcpCallbacks)) || (PPP_CCP != usProtocol))
       && ((pstFsm->usProtocol != PPP_IPV6CP) || (pstFsm->pstCallBacks != (&g_stIpv6cpCallbacks)) || (PPP_IPV6CP != usProtocol))
       && ((pstFsm->usProtocol != PPP_VSNCP) || (pstFsm->pstCallBacks != (&g_stVsncpCallbacks)) || (PPP_VSNCP != usProtocol)))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_481);
        PPPC_WARNING_LOG2("\r\n [ppp]PPP_FSM_TimeOut sub protocol type isnot matched protocol=%x fsm type=%x",
                    pstFsm->usProtocol,
                    usProtocol);

        return;
    }

    if (NULL == pstFsm->pPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_482);
        PPPC_WARNING_LOG1("\r\n [patch]PPP_FSM_TimeOut pppindex=%d:NULL == pstFsm->pPppInfo",
                    ulRPIndex);

        return;
    }

    pstFsm->ulTimeOutID = 0;
    /* caihaitao for D09949 end */


    /* �ش���������1 */
    pstFsm->sRetransmits--;

    if (pstFsm->sRetransmits > 0)
    {
        /* ��TO+�¼� */
        ucEvent = 1;
    }
    else
    {
        /* ��TO-�¼� */
        ucEvent = 0;

        /* PPPЭ�̽׶Σ��ն�����Ӧ���µ�ʧ�ܡ�������δ��ȷ�ų��������������ʹ����ο��ƣ�Ĭ�ϼ�ȥ�� */
        /*lint -e{506,774}*/
        if ((0 == SOFTPARA_BIT1383)
            && (pstFsm->ucState != PPP_STATE_CLOSING) && (pstFsm->ucState != PPP_STATE_STOPPING))
        {
            A11_ReqNumSubProc(pstPppInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_483);
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_484);
        }
        /*lint -restore*/
        /* ��������ͳ��ԭ��ֵ: ms����Ӧ */
        PPP_SNMP_PERF_SET_FAILREASON_MS_NO_RSP(pstPppInfo, pstFsm);

        /* ��������ԭ��ֵ */
        PPP_FSM_RleseCode(pstFsm,
                  AM_RELCODE_PPP_LCP_NEGOTIMEOUT,
                  AM_RELCODE_PPP_IPCP_NEGOTIMEOUT,
                  AM_RELCODE_PPP_IPV6CP_NEGOTIMEOUT,
                  AM_RELCODE_PPP_VSNCP_NEGOTIMEOUT);

        /* �����ǰPPP����ESTABLISH�׶�,����Attachʧ��ԭ��ֵ */
        if (PPP_PHASE_ESTABLISH == pstPppInfo->usPhase)
        {
            PPPC_SetAttachErrorCode(CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE);
        }

    }

    if (ucEvent == 1)

    /* TO+�¼� */
    {
        /* ���debug��Ϣ */
        PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_TO_PLUS);

        switch (pstFsm->ucState)
        {
            case PPP_STATE_INITIAL:
            case PPP_STATE_STARTING:
            case PPP_STATE_CLOSED:
            case PPP_STATE_STOPPED:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_TO_PLUS);
                break;

            case PPP_STATE_CLOSING:
            case PPP_STATE_STOPPING:

                /* str */
                PPP_FSM_str(pstFsm);

                break;

            case PPP_STATE_REQSENT:


            case PPP_STATE_ACKRCVD:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_REQSENT);

                /* scr */
                PPP_FSM_scr(pstFsm);

                break;

            case PPP_STATE_ACKSENT:

                /* scr */
                PPP_FSM_scr(pstFsm);

                /* state not changed */
                break;

            case PPP_STATE_OPENED:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_TO_PLUS);
                break;

            default:
                break;
        }
    } /* ucEvent == 1 */
    else

    /* TO-�¼� */
    {
        /* ���debug��Ϣ */
        PPP_Debug_FsmEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_TO_SUB);

        if(PPPUSERDOWN != ((PPPINFO_S*)pstFsm->pPppInfo)->bFailFlag)
        {
            if (PPP_VSNCP == usProtocol)
            {
                HSGW_EmsTraceByPdnIndex(ulPDNIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_18);
            }
            else
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_18);
            }
        }

        switch (pstFsm->ucState)
        {
            case PPP_STATE_INITIAL:
            case PPP_STATE_STARTING:
            case PPP_STATE_CLOSED:
            case PPP_STATE_STOPPED:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, (VOS_UINT32)PPP_EVENT_FSM_TO_SUB);
                break;

            case PPP_STATE_CLOSING:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_CLOSED);

                /* tlf */
                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1142);

                break;

            case PPP_STATE_STOPPING:
            case PPP_STATE_REQSENT:
            case PPP_STATE_ACKRCVD:
            case PPP_STATE_ACKSENT:

                /* state changed */
                PPP_FSM_ChangeState(pstFsm, (VOS_UINT32)PPP_STATE_STOPPED);

                /* tlf */

                PPP_FSM_tlf(pstFsm);
                PPP_DBG_OK_CNT(PPP_PHOK_1143);

                break;

            case PPP_STATE_OPENED:

                /* Illegal Event */
                PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_TO_SUB);
                break;

            default:
                break;
        }
    } /* ucEvent == 0 */

    /* BEGIN: Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
    if (PPP_VSNCP == usProtocol)
    {
        /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
        PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);
    }
    /* END:   Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_FSM_VSTimeOut
 ��������  : �汾����ָʾ���Ķ�ʱ����ʱ������
 �������  : VOID *pFsm
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��15��
    ��    ��   : z00129699
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_FSM_VSTimeOut(VOS_VOID *pFsm)
{
    VOS_UINT32      ulMagic     = 0;
    VOS_UINT32      ulRPIndex   = (VOS_UINT32)pFsm;
    PPPFSM_S   *pstFsm     = NULL;
    PPPINFO_S  *pstPppInfo = NULL;


    if (ulRPIndex <= PPP_MAX_USER_NUM)
    {
        GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo)
        {
            PPPC_INFO_LOG1("PPP_FSM_VSTimeOut :pstPppPool is NULL!", ulRPIndex);
            return;
        }
    }
    else
    {
        PPPC_INFO_LOG1("PPP_FSM_VSTimeOut :ulRPIndex is invalid!", ulRPIndex);
        return;
    }

    if (VOS_NULL_PTR == pstPppInfo->pstLcpInfo)
    {
        PPPC_INFO_LOG1("PPP_FSM_VSTimeOut :pstLcpInfo is null!", ulRPIndex);
        return;
    }

    pstFsm = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stFsm);

/* EAP-dev */
#if 1
    /* �ط��Ͱ汾����ָʾ����*/
    ulMagic = PPP_GetMagicNumber();
    PPP_FSM_SendVendorSpecific(pstFsm, pstFsm->ucVSId, ulMagic, VENDORSPECIFIC_INDICTE);
#else
    if (pstFsm->usVSRetransmits > 0)
    {
        /* �ش���������1 */
        pstFsm->usVSRetransmits--;

        /* �ط� �Ͱ汾����ָʾ����*/
        ulMagic = PPP_GetMagicNumber();
        PPP_FSM_SendVendorSpecific(pstFsm, pstFsm->ucVSId, ulMagic,VENDORSPECIFIC_INDICTE);
        pstFsm->ucVSId++;
    }

    if ( 0 == pstFsm->usVSRetransmits )
    {
        /*�ﵽ����ط�������ɾ��ѭ����ʱ��*/
        if (pstFsm->hVendorSpecificTimeID)
        {
            (VOID)VOS_StopRelTimer(&(pstFsm->hVendorSpecificTimeID));
            pstFsm->hVendorSpecificTimeID= 0;
        }
    }
#endif

    return;
}

/* ���ͱ��ĺ��� */

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������һ���Ѿ���װ�����ݵı���.��������                      *
*                PPP_Shell_GetPacketFromCore�������ͱ���,                   *
*                һ����Ҫǰ����:pPacketǰ��Ԥ�����㹻�Ŀռ�(8�ֽ�)          *
*                ���ڴ���ͷ                                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
*                ucCode    :���Ĵ���,��CONFREQ��                            *
*                ucId      :����ID                                          *
*                pHead     :���������ڴ���׵�ַ                            *
*                pPacket   :�ַ�������ʽ���ڵı���                          *
*                ulLen     :���ĳ���                                        *
*                usProtocol:PPPЭ���                                       *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_SendPacketByCode��PPP_FSM_SendConfigReq��          *
*                PPP_LCP_SendEchoRequest��PPP_Core_ReceiveUnknownProtocol   *
****************************************************************************/
VOID PPP_FSM_SendPacket(PPPFSM_S *pstFsm,
                        UCHAR     ucCode,
                        UCHAR     ucId,
                        UCHAR *   pHead,
                        UCHAR *   pPacket,
                        VOS_UINT32     ulLen)
{
    VOS_UINT32 ulErrorCode;
    PPPINFO_S *pstPppInfo;

    /* ������� */

    /*
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |   Identifier  |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ <-pPacket
     | Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */
    if (NULL == pPacket)
    {
        return;
    }

    pPacket -= FSM_HDRLEN;
    ulLen += FSM_HDRLEN;

    PPP_PUTCHAR(ucCode, pPacket);
    PPP_PUTCHAR(ucId, pPacket);
    PPP_PUTSHORT((VOS_UINT16)ulLen, pPacket);

    pPacket -= FSM_HDRLEN;

    /*
                0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
      pPacket-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                |     Code      |   Identifier  |            Length             |
                +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                | Data ...
                +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */

    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    /* ���������Ϣ */
    switch (pstFsm->usProtocol)
    {
        case PPP_LCP:

            /* ���������Ϣ */
            if (NULL == pstPppInfo)
            {
                return;
            }

            if (pstPppInfo->stPppDebugInfo.bDebug_Lcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket((PPPINFO_S*)pstFsm->pPppInfo,
                                    pPacket,
                                    ulLen,
                                    pstFsm->usProtocol,
                                    PPP_DEBUG_PACKET_OUT
                );
            }

            break;

        case PPP_IPCP:

            /* ���������Ϣ */
            if (NULL == pstPppInfo)
            {
                return;
            }

            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket((PPPINFO_S*)pstFsm->pPppInfo,
                                    pPacket,
                                    ulLen,
                                    pstFsm->usProtocol,
                                    PPP_DEBUG_PACKET_OUT
                );
            }

            break;

        case PPP_IPV6CP:
        {
            /* ���������Ϣ */
            if (NULL == pstPppInfo)
            {
                return;
            }

            if (pstPppInfo->stPppDebugInfo.bDebug_Ipv6cp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket((PPPINFO_S*)pstFsm->pPppInfo,
                                    pPacket,
                                    ulLen,
                                    pstFsm->usProtocol,
                                    PPP_DEBUG_PACKET_OUT
                );
            }

            break;
        }

        case PPP_CCP:

            /* ���������Ϣ */
            if (NULL == pstPppInfo)
            {
                return;
            }

            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket((PPPINFO_S*)pstFsm->pPppInfo,
                                    pPacket,
                                    ulLen,
                                    pstFsm->usProtocol,
                                    PPP_DEBUG_PACKET_OUT
                );
            }

            break;

        case PPP_PAP:
            break;

        case PPP_CHAP:
            break;

        default:
            break;
    }

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore(pstFsm->pPppInfo, pHead,
                                              pPacket, ulLen, pstFsm->usProtocol);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_485);
        /*���������Ϣ*/
        PPP_Debug_Error(pstFsm, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����Э��Ŵ���������һ������                                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
*                ucCode    :���Ĵ���,��CONFREQ��                            *
*                ucId      :����ID                                          *
*                pHead     :���������ڴ���׵�ַ                            *
*                pPacket   :�ַ�������ʽ���ڵı���                          *
*                ulLen     :���ĳ���                                        *
*                usProtocol:PPPЭ���                                       *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_str��PPP_FSM_sta                                   *
****************************************************************************/
VOID PPP_FSM_SendPacketByCode(PPPFSM_S *pstFsm,
                              UCHAR     ucCode,
                              UCHAR     ucId)
{
    UCHAR *pHead = NULL;
    UCHAR *pPacket;
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset;

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    /* ������� */

    /*
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |            ...                |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|
    pHead                           pPacket
     */
    /* BEGIN: Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
    if (PPP_VSNCP == pstFsm->usProtocol)
    {
        /* ��֯�������� */
        ulLen = (VSNCP_OPTION_PDNID_LEN + VSNCP_3GPP2_OUI_LEN);
        PPP_VSNCP_Termaddci(pstFsm, pPacket);
    }
    /* END:   Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */

    PPP_FSM_SendPacket(pstFsm, ucCode, ucId, pHead, pPacket, ulLen);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������������һ��Config Request����                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��ִ��scr�����ĺ�PPP_FSM_scr                                 *
****************************************************************************/
VOID PPP_FSM_SendConfigReq(PPPFSM_S *pstFsm)
{
    UCHAR *pPacket;
    UCHAR *pHead = NULL;
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset;

    if (NULL == pstFsm)
    {
        return;
    }

    /* ���ﲻ��ʼ��,tls�����г�ʼ�� */

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;

    /* ������� */

    /*
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |           reserved            |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|
    pHead                           pPacket
     */

    /* ��֯�������� */
    if (pstFsm->pstCallBacks->cilen && pstFsm->pstCallBacks->addci)
    {
        ulLen = (*pstFsm->pstCallBacks->cilen)(pstFsm);
        (*pstFsm->pstCallBacks->addci)(pstFsm, pPacket);
    }
    else
    {
        ulLen = 0;
    }

    /* ������� */
    if (NULL != pstFsm->pPppInfo)
    {
        if ((PPP_LCP == pstFsm->usProtocol)
            && (((PPPINFO_S*)pstFsm->pPppInfo)->ulPeerIPAddr)
            && (0 == ((PPPINFO_S*)pstFsm->pPppInfo)->bReNego))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1144);
        }
    }
    /*
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |           reserved            |  data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|
    pHead                           pPacket
     */

    /* ���ͱ��� */
    PPP_FSM_SendPacket(pstFsm, CONFREQ,
                       pstFsm->ucPktId, pHead,
                       pPacket, ulLen);

    return;
}

/* EAP-dev */

/*****************************************************************************
 �� �� ��  : PPP_FSM_SendVendorSpecific
 ��������  : ����������һ���汾����Э�̱���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��15��
    ��    ��   : z00129699
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_FSM_SendVendorSpecific(PPPFSM_S *pstFsm , UCHAR ucid,VOS_UINT32 ulMagic, UCHAR ucKind)
{
    UCHAR *pHead, *pPacket;
    VOS_UINT32  ulPppIndex;
    UCHAR ucVersion = 0;                    /* X.S0011-002-E_v1.0, P83
                                               0 for Version D
                                               1 for Version E
                                               2-255 reserved for later versions */
    UCHAR aucOui[3] = {0xCF,0x0,0x2};    /* X.S0057-A v2.0, P123 */

    /*
    from X.S0011-002-D_v2.0, Table 8 - List of MS Capabilities,
    X.S0011-002-E_v1.0, Table 8 - List of MS Capabilities,
    and X.S0011-002-D_v2.0, Table 20 - List of MS Capabilities

    Bit MS Capability
    C0 Simple IPv4
    C1 MIP4
    C2 Simple IPv6
    C3 MIP6
    C4 Max PPP inactivity timer
    C5 NCP inactivity timer
    C6 PPP Additional Authentication
    C7 Network Initiated QoS
    C8 Stale PDN Handling
    C9 IPCP NAK Handling
    C10 to C23 Reserved

    ĿǰMS֧�ֵ�������Simple IPv4��Simple IPv6
    ����Э��Ҫ���ն�Ӧ����MS�������е�C4Ϊ0
    */
    UCHAR aucCapality[3] = {0xA0,0x0,0x0};

    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset = PPP_RESERVED_PACKET_HEADER;
    VOS_UINT32 ulErrorCode = VOS_ERR;

    if (NULL == pstFsm)
    {
        PPPC_WARNING_LOG("PPP_FSM_SendVendorSpecific pstFsm is null");
        return;
    }

    /* ��ȡ�ڴ� */
    pHead = g_ucPppSendPacketHead;

    VOS_MemSet(pHead, 0, PPP_DEFAULT_NEGO_PACKET_LEN + ulOffset);
    pPacket = pHead + ulOffset;

    /* ���ݱ��������֯��������, ����FSM Head���� */
    /*
     |------------------------- FSM Head ----------------------------|
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ <-pPacket
     */
    /* ��������� */
    if ((VENDORSPECIFIC_RESPONSE == ucKind) || (VENDORSPECIFIC_INACTIVE_TIMER_RESPONSE == ucKind))
    {
        /*
         0                   1                   2                   3
         0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |     Code      |  Identifier   |            Length             |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                             Magic Number                      |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                        OUI                    |      Kind     |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         */

        pPacket -= FSM_HDRLEN;
        ulLen += 12; /* 8(BODY) + FSM_HDRLEN: ��Response Packet���� */

        /*��Ϣͷ*/
        PPP_PUTCHAR(VEDRSPEC, pPacket);
        PPP_PUTCHAR(ucid, pPacket);
        PPP_PUTSHORT((VOS_UINT16)ulLen, pPacket);

        /*��Ϣ��*/
        PPP_PUTLONG(ulMagic, pPacket);
        PPP_PUTCHARPTR(aucOui, pPacket, 3);
        PPP_PUTCHAR(ucKind, pPacket);

        pPacket -= 12;  /* pPacket����ָ����ͷ */
    }

    if (VENDORSPECIFIC_INDICTE == ucKind)
    {
        /*
         0                   1                   2                   3
         0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |     Code      |  Identifier   |            Length             |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                             Magic Number                      |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                        OUI                    |      Kind     |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |    Version    |              List of Capabilities             |
         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         */

        pPacket -= FSM_HDRLEN;
        ulLen += 16; /* 12(BODY) + FSM_HDRLEN: ��Indication Packet���� */

        /*��Ϣͷ*/
        PPP_PUTCHAR(VEDRSPEC, pPacket);
        PPP_PUTCHAR(ucid, pPacket);
        PPP_PUTSHORT((VOS_UINT16)ulLen, pPacket);

        /*��Ϣ��*/
        PPP_PUTLONG(ulMagic, pPacket);
        PPP_PUTCHARPTR(aucOui, pPacket, 3);
        PPP_PUTCHAR(ucKind, pPacket);
        PPP_PUTCHAR(ucVersion, pPacket);
        PPP_PUTCHARPTR(aucCapality, pPacket, 3);

        pPacket -= 16;    /* pPacket����ָ����ͷ */
    }

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore(pstFsm->pPppInfo, pHead,
                                      pPacket, ulLen, pstFsm->usProtocol);

    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_489);
        /*���������Ϣ*/
        PPPC_WARNING_LOG2("PPP_FSM_SendVendorSpecific Send Packet Failed!",
            ulErrorCode, ucKind);

        return;   /* ʧ���򷵻�, ���ټ��� */
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1145);

    if (VENDORSPECIFIC_INDICTE == ucKind)
    {
        /*
           "The Identifier field shall be changed for each vendor
            specific packet sent." from X.S0011-002-D_v2.0
        */
        pstFsm->ucVSId++;   /* �ɹ���ID++ */

        pstFsm->sVSTransmits--;

        if (pstFsm->sVSTransmits > 0)
        {
            ulPppIndex = ((PPPINFO_S *)(pstFsm->pPppInfo))->ulRPIndex;

            /* �ж�һ�¶�ʱ���Ƿ������� */
            if (VOS_NULL_PTR != pstFsm->hVendorSpecificTimeID)
            {
                /* ��ֹͣ��ʱ�� */
                (VOS_VOID)VOS_StopRelTimer(&(pstFsm->hVendorSpecificTimeID));
                pstFsm->hVendorSpecificTimeID = VOS_NULL_PTR;
            }

            /* start non-loop timer */
            VOS_StartRelTimer(&(pstFsm->hVendorSpecificTimeID),
                              MID_PPPC,
                              PPP_DEFTIMEOUTTIME,
                              ulPppIndex,
                              PPPC_VENDOR_SPECIFIC_SEND_CAPABILITY_TIMER,
                              VOS_TIMER_NOLOOP,
                              VOS_TIMER_PRECISION_0);
        }
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2010/01/06                                                 *
* CREATED BY   ��zhaichao                                                *
* FUNCTION     ��������յ�������Э�̱���             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucId:   ����ID                                             *
*                pHead:  ��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�            *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
VOS_VOID PPP_FSM_ReceiveVendorSpecific(PPPFSM_S *pstFsm,
                                                UCHAR     ucId,
                                                UCHAR *   pHead,
                                                UCHAR *   pPacket,
                                                VOS_UINT32     ulLen)
{
    /* �汾����Э�̱��ĸ�ʽ
     |Magic-Number (4 bytes)  | OUI (3bytes 0xCF0002) |  Kind(1 byte) |  Version(1 byte) |List of Capabilities(3 bytes) |
     ��kindֵΪ3ʱ��û��version��List of Capabilities����
    */
    UCHAR ucKind = 0 ;
    UCHAR aucOui[3] = {0x0, 0x0, 0x0};
    VOS_UINT32 ulLoop = 0;
    UCHAR ucVersion = 0;
    UCHAR aucCapality[3] = {0x0, 0x0, 0x0};
    PPPINFO_S* pstPppInfo = NULL;
    const VOS_UINT8 ucMinBody = 8;    /* 8ΪMagic-Number + OUI + Kind�ֶγ��� */
    const VOS_UINT8 ucIndiceBody = 12;    /* Magic-Number + OUI + Kind + version + capabilities */
    VOS_UINT8                          *pucVendorData;
    VOS_UINT32                          ulPktMagicNum = 0;
    VOS_UINT32                          ulMagicNum = 0;
    PPPLCPINFO_S                       *pstLcpInfo;
    VOS_UINT32                          ulTimerLen;


    if ((VOS_NULL_PTR == pstFsm) || (VOS_NULL_PTR == pPacket) )
    {
        PPPC_WARNING_LOG2("PPP_FSM_ReceiveVendorSpecific: pstFsm or/both pPacket is null",
            pstFsm, pPacket);

        return;
    }

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("PPP_FSM_ReceiveVendorSpecific: pstPppInfo is null.");

        return;
    }

    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ <-pPacket
     |                             Magic Number                      |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */

    if (ulLen < ucMinBody)/* 8ΪMagic-Number + OUI + Kind�ֶγ��� */
    {
        PPPC_WARNING_LOG1("PPP_FSM_ReceiveVendorSpecific: packet length err[%d].\n", ulLen);

        return;
    }

    pucVendorData = pPacket;

    /* ��ȡ���е�magic num */
    PPP_GETLONG(ulPktMagicNum, pPacket);
    /* ���Ǽ������磬���ж�����magic num�Ƿ�Ϸ������ӽ�׳�� */

    /* ��ȡЭ�̵�magic num */
    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);
    ulMagicNum = pstLcpInfo->stGotOptions.magicnumber;

    /* ��ȡOUI(Organizationally Unique Identifier) */
    for (ulLoop = 0; ulLoop < 3; ulLoop++)
    {
        PPP_GETCHAR(aucOui[ulLoop], pPacket);
    }

    /* ���ݵ��Ų��Թ淶��OUI�̶�Ϊ0xCF0002��OUI����ֱ�Ӷ��������κδ��� */
    if ((0x02 != aucOui[2]) || (0x00 != aucOui[1]) || (aucOui[0] != 0xcf))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_440);
        PPPC_WARNING_LOG3("\r\n PPP_FSM_ReceiveVendorSpecific: oui err[0x%x%x%x]",
                            aucOui[0], aucOui[1], aucOui[2] );

        return;
    }

    /* ��ȡKind */
    PPP_GETCHAR(ucKind, pPacket);

    PPPC_INFO_LOG2("PPP_FSM_ReceiveVendorSpecific: ucKind ulLen",
                 ucKind, ulLen);

    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                             Magic Number                      |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                        OUI                    |      Kind     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ <-pPacket
     */

    switch (ucKind)
    {
        case VENDORSPECIFIC_INDICTE:/*�汾����ָʾ����*/
        {
            /*
             0                   1                   2                   3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |     Code      |  Identifier   |            Length             |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |                             Magic Number                      |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |                        OUI                    |      Kind     |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |    Version    |              List of Capabilities             |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             */


            /* ���KindֵΪ2���汾/����ָʾ����Ӧ�ð���Version��List of Capabilities�ֶΣ�
               ��˱��ĳ���Ϊ8 + 4 */
            if (ucIndiceBody > ulLen) /* ���ĳ��Ȳ��Ϸ� */
            {
                /* ֱ�Ӷ��� */
                PPP_DBG_ERR_CNT(PPP_PHERR_441);
                PPPC_WARNING_LOG2("PPP_FSM_ReceiveVendorSpecific: ulLen err[%d] kind %d",
                                    ulLen, ucKind);

                break;
            }

            /* ��ȡVersion */
            PPP_GETCHAR(ucVersion, pPacket);

            /*
               Version  0 for Version D
                        1 for Version E
                        2-255 reserved for later versions
            */
            if ((VENDOR_SPECIFIC_VERSION_D != ucVersion)
                && (VENDOR_SPECIFIC_VERSION_E != ucVersion))
            {
                /* ֱ�Ӷ��� */
                PPP_DBG_ERR_CNT(PPP_PHERR_441);
                PPPC_WARNING_LOG2("unexpected vendor specific packet version, kind",
                    ucVersion, ucKind);
            }
            else
            {
                /* ��ȡCapality */
                PPP_GETCHAR(aucCapality[0], pPacket);
                PPP_GETCHAR(aucCapality[1], pPacket);
                PPP_GETCHAR(aucCapality[2], pPacket);

                PPPC_INFO_LOG4("\r\n PPP_FSM_ReceiveVendorSpecific: ucVersion[%u] Capality[%x][%x][%x]",
                             ucVersion, aucCapality[0], aucCapality[1], aucCapality[2]);
                /* for pc-lint, lint��ʾcapalityδ����, ������ΪPPPC_INFO_LOG��defineΪ���� */
                (VOS_VOID)aucCapality;

                /* MSû��IPCP NAK HANDLING����, Ҳû���ϱ���������
                   ���յ������������, Ҳ���� */
                pstPppInfo->bIPCPNakHandFlag = VOS_FALSE;

                /*���Ͱ汾������Ӧ����*/
                PPP_FSM_SendVendorSpecific(pstFsm, ucId, ulMagicNum, VENDORSPECIFIC_RESPONSE);
            }

            break;
        }
        case VENDORSPECIFIC_RESPONSE:/*�汾/������Ӧ����*/
        {
            if (VOS_NULL_PTR != pstFsm->hVendorSpecificTimeID)
            {
                /* stop VStimer */
                (VOS_VOID)VOS_StopRelTimer(&(pstFsm->hVendorSpecificTimeID));
                pstFsm->hVendorSpecificTimeID = VOS_NULL_PTR;
            }

            break;
        }
        case VENDORSPECIFIC_REJECT:
        {
            /* ֱ���ͷű��ģ������κδ��� */
            break;
        }
        case VENDORSPECIFIC_INACTIVE_TIMER:
        {
            /* ���ĳ��Ȳ��Ϸ� */
            if (ucIndiceBody > ulLen)
            {
                /* ֱ�Ӷ��� */
                PPP_DBG_ERR_CNT(PPP_PHERR_441);
                PPPC_WARNING_LOG2("PPP_FSM_ReceiveVendorSpecific: ulLen err[%d] kind %d",
                                    ulLen, ucKind);

                return;
            }

            /* ��ȡdata */
            PPP_GETLONG(ulTimerLen, pPacket);

            if (0 == ulTimerLen)
            {
                /* ֱ�Ӷ��� */
                PPP_DBG_ERR_CNT(PPP_PHERR_441);
                PPPC_WARNING_LOG2("PPP_FSM_ReceiveVendorSpecific: ulTimerLen err[%d] kind %d",
                                    ulTimerLen, ucKind);

                return;
            }

            /* �յ�VENDORSPECIFIC_INACTIVE_TIMER���ĺ�������ж�ʱ��������¶�ʱ��ʱ��ΪЭ��ֵ������������ʱ����
            ����ֻ���¶�ʱ��ʱ�� */

            /* ����MAX PPP Inactive Timerʱ�� */
            pstPppInfo->ulPppInactTimerLen = ulTimerLen*1000;

            /* ����MAX PPP Inactive Timer */
            PPPC_StartPppInactiveTimer((VOS_UINT8)pstPppInfo->ulRPIndex);

            /*���Ͱ汾������Ӧ����*/
            PPP_FSM_SendVendorSpecific(pstFsm, ucId, ulMagicNum, VENDORSPECIFIC_INACTIVE_TIMER_RESPONSE);
            break;
        }
        case VENDORSPECIFIC_INACTIVE_TIMER_RESPONSE:
        {
            PPPC_WARNING_LOG1("not support Kind", ucKind);

            /* ֱ���ͷű��ģ������κδ��� */
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_442);
            PPPC_WARNING_LOG1("PPP_FSM_ReceiveVendorSpecific: Kind err[%d]", ucKind);

            /* "If the MS (or PDSN) receives an unknown 3GPP2 vendor specific packet,
               it shall send the 3GPP2 vendor specific Reject packet containing
               the rejected 3GPP2 vendor specific packet."
               from X.S0011-002-D_v2.0, section 9 */

            /*
               reject packet�ĳ��Ⱦ����ñ��ܾ��ı��ĵĳ���(ǰ����lenͨ���˺Ϸ��Լ��)
               reject����ֻ��Ҫ����Id�ֶ�(Ϊ�Լ���Id)��kind�ֶ�, �����ֶα���Ϊԭ���ĵ��ֶ�
            */

            /*
             0                   1                   2                   3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |     Code      |  Identifier   |            Length             |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |                             Magic Number                      |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |                        OUI                    |      Kind     |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             |                              Value...                         |
             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
             */

            /* �����ߵ�default��֧, pPacketָ��kind��һ���ֽ� */
            pPacket -= sizeof(ucKind);  /* pPacket����ָ��kind, kindռ��1B */
            PPP_PUTCHAR(VENDORSPECIFIC_REJECT, pPacket);

            /* ��packetָ�ر���ͷ */
            pPacket -= ucMinBody;    /* 8ΪMagic-Number + OUI + Kind�ֶγ��� */

            PPP_FSM_SendPacket(pstFsm, VEDRSPEC, pstFsm->ucVSId, pHead, pPacket, ulLen);

            /*
               "The Identifier field shall be changed for each vendor
                specific packet sent." from X.S0011-002-D_v2.0
            */
            pstFsm->ucVSId++;   /* ������Ϻ�, Id++ */

            break;
        }
    }
    (VOS_VOID)pPacket;
    (VOS_VOID)pucVendorData;
    (VOS_VOID)ulPktMagicNum;
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬����ʼ��                                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ������Э��ĳ�ʼ������(��PPP_LCP_Init)                       *
****************************************************************************/
VOID PPP_FSM_Init(PPPFSM_S *pstFsm)
{
    PPPINFO_S *pstPppInfo;

    if (NULL == pstFsm)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)(pstFsm->pPppInfo);
    if (NULL == pstPppInfo)
    {
        return;
    }

    pstFsm->ucPktId = 0;           /* XXX Start with random id? */
    pstFsm->sRetransmits = 0;
    if (pstPppInfo->pstUsedConfigInfo == NULL)
    {
        pstFsm->ulTimeOutTime = PPP_DEFTIMEOUTTIME;
    }
    else
    {
        pstFsm->ulTimeOutTime = pstPppInfo->pstUsedConfigInfo->ulNegTimeOut;
    }

    pstFsm->ulTimeOutID = 0;

    pstFsm->ucState = (UCHAR)PPP_STATE_INITIAL;

/* EAP-dev */
#if 1
    pstFsm->hVendorSpecificTimeID = VOS_NULL_PTR;
    pstFsm->sVSTransmits = PPP_MAX_VENDER_CAPABILITY_INDICATION_TIMES;
#endif

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
