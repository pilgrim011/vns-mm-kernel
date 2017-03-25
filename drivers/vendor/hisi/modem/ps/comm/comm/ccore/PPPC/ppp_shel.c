/******************************************************************************

                    ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

*******************************************************************************

  ��    ��  ��     : ppp_shel.c
  ��    ��  ��     : VRP3.0
  ��             ��     : Deng Yi Ou
  ��������     : 2000-04-04
  ����޸�     :
  ��������     : PPP�����(shell)ģ��
  �����б�     :

*
*       1.                GGSN_PathProcess
*       2.                GTPC_ASNSwitchChange
*       3.                GTPC_BatchDeletePdpContextByPath
*       4.                GTPC_BatchDelTaskByPath
*       5.                GTPC_CalculateHashValue
*       6.                GTPC_CMNotifyVolumetoAM
*       7.                GTPC_CompareSgsnRecovery
*       8.                GTPC_CreatDeletePdpTaskByPath
*       9.                GTPC_CreateNode
*       10.                GTPC_CreatePath
*       11.                GTPC_DeactiveConSgsnRestart
*

  �޸���ʷ     :
  1.��    ��   : 2010-05-13
    ��    ��   : c00127007
    �޸�����   : ɾ��������롢�������������Ӻ���ע�͡����Ӵ�ӡ���ȡ�
******************************************************************************/



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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_SHEL_C

/* PPPC�����ݶ���ͳ����Ϣ�ṹ�� */
extern PPP_DATA_Q_STAT_STRU             g_stPppcDataQueueStats;

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPP_USMStartVsncp
 ��������  : USM֪ͨPPP��ʼVSNCP������
 �������  : PPP_A11MSG_S *pstA11Msg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_USMStartVsncp(UCHAR *pucVsncpMsg, VOS_UINT32 ulRpIndex)
{
    VOS_UINT32 ulLen = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_774);
        PPPC_INFO_LOG1(
                     "\r\n PPP_USMStartVsncp: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    ulLen = *((VOS_UINT32 *)pucVsncpMsg);
    pHead = pucVsncpMsg + sizeof(VOS_UINT32);
    pPacket = pucVsncpMsg + sizeof(VOS_UINT32) + PPP_RESERVED_PACKET_HEADER;

    PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, CONFREQ);
    PPP_DBG_OK_CNT(PPP_PHOK_1472);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_USMNotifyRelease
 ��������  : USM֪ͨPPPɾ����Դ������Ҫ����LCP
 �������  : PPP_A11MSG_S *pstA11Msg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_USMNotifyRelease(PPP_A11MSG_S *pstA11Msg)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, pstA11Msg->ulRPIndex);

    PPP_DBG_OK_CNT(PPP_PHOK_1292);
    if (VOS_NULL_PTR != pstPppInfo)
    {
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;
    }

    (VOID)PPP_Shell_ISLIoCtl(pstA11Msg->ulRPIndex, PPP_ISLDOWN, (CHAR *)&pstA11Msg->ulL2tpType);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_IpcpTimeOutProcForPdn
 ��������  : pdn ipcp��ʱ����ʱ�����øú���
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : y00138047
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_IpcpTimeOutProcForPdn(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_567);
        return;
    }

    A11_ReqNumSubProc(pstPppInfo);

    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_UpdatePcfInfo
 ��������  : pppˢ��pcfip��pcfindex���ṩ��a11����
 �������  : VOS_UINT32 ulRpIndex
             VOS_UINT32 ulPcfIp
             VOS_UINT16 usPcfIndex
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : y00138047
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_UpdatePcfInfo(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPcfIp, VOS_UINT16 usPcfIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_568);
        PPPC_INFO_LOG1("\r\n PPP_UpdatePcfInfo: User %d isn't exist!", ulRpIndex);
        return;
    }

    pstPppInfo->ulPcfIP = ulPcfIp;
    pstPppInfo->usPcfIndex = usPcfIndex;
    PPP_DBG_OK_CNT(PPP_PHOK_1293);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_StartIPV4CP
 ��������  :
             ���û��PPP���ƿ飬����ʧ��
             �����PPP���ƿ飬û��IPCP���ƿ飬��Ҫ�ж��Ƿ�����Э�̣����򱣴��ַ�����򷵻�ʧ��
             �����IPCP���ƿ飬�򱣴��ַ������IPCPЭ��
             ȡ�����ƿ��л�����Ϣ������IPCP Request ��Ϣ��Ȼ�����յ������е�IPCP Request ��Ϣ

 �������  : VOS_UINT32 ulRpIdx
             VOS_UINT32 ulIpAddr
             VOS_UINT32 ulPriDns
             VOS_UINT32 ulSecDns
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StartIPV4CP(VOS_UINT32 ulRpIdx, VOS_UINT32 ulIpAddr, VOS_UINT32 ulPriDns, VOS_UINT32 ulSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_569);
        PPPC_INFO_LOG1("\r\n PPP_StartIPV4CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (0 != pstPppInfo->ulPeerIPAddr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_570);
        PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: User IP is exist!");
        return VOS_ERR;
    }

    /* �����ַ*/
    pstPppInfo->ulPeerIPAddr = ulIpAddr;
    pstPppInfo->ulDNSAddr1 = ulPriDns;
    pstPppInfo->ulDNSAddr2 = ulSecDns;
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

    /* ��Э�̣�ֱ�ӱ����ַ �˴���Э�̱�ǿ��Ʋ�ס ʹ��Э�̽׶ο��� */
    if ((VOS_UINT16)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1294);
        PPPC_WARNING_LOG("\r\n PPP_StartIPV4CP: Renego!");
        return VOS_OK;
    }

    /* û���ƿ� */
    if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
    {
        /* ���򴴽����ƿ飬����Э�� */
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_571);
            PPPC_WARNING_LOG(" \r\n PPP_StartIPV4CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

        PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: active ipcp negoation !");
    }

    /* �п��ƿ� */
    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;

    /* �ж��Ƿ���ҪЭ��VJѹ�� */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    /* ��ʼ��IPCP���ƿ� ȡ��IPCP���ƿ������ݣ��ȷ�Request��Ϣ */
    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
    /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* ��������Ϣ*/
    if (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1295);
        pHead    = pstIpcpInfo->pucIpv4cpMsg;
        pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

        /* �յ��ն˷����ļ�Ȩ���� */
        PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulMsgLen);
        (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
        pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
        pstIpcpInfo->ulIpv4cpLen = 0;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1296);
    PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: Done!");
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : PPP_StartIPV6CP
 ��������  :
          ���û��PPP���ƿ飬����ʧ��
          �����PPP���ƿ飬û��IPCP���ƿ飬��Ҫ�ж��Ƿ�����Э�̣����򱣴��ַ�����򷵻�ʧ��
          �����IPCP���ƿ飬�򱣴��ַ������IPCPЭ��
          ȡ�����ƿ��л�����Ϣ������IPCP Request ��Ϣ��Ȼ�����յ������е�IPCP Request ��Ϣ

 �������  : VOS_UINT32 ulRpIdx
             UCHAR* szIpV6Addr
             UCHAR* szPriDns
             UCHAR* szSecDns
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StartIPV6CP(VOS_UINT32 ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6CpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_572);
        PPPC_INFO_LOG1("\r\n PPP_StartIPV6CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_573);
        PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: User IP is exist!");
        return VOS_ERR;
    }

    /* �����ַ */
    VOS_MemCpy(pstPppInfo->usPeerIPv6Addr, szIpV6Addr, PDN_IPV6ADDR_LEN);
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;

    /* ��Э�̣�ֱ�ӱ����ַ �˴���Э�̱�ǿ��Ʋ�ס ʹ��Э�̽׶ο��� */
    if ((VOS_UINT16)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1297);
        PPPC_WARNING_LOG("\r\n PPP_StartIPV6CP: Renego!");
        return VOS_OK;
    }

    /* û�п��ƿ� */
    if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
    {
        /* ���򴴽����ƿ飬����Э�� */
        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1298);
            PPPC_WARNING_LOG(" \r\n PPP_StartIPV6CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

        PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: IPV6CP CB is VOS_NULL_PTR!");
    }

    pstIpV6CpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;

    /* ��ʼ��IPV6CP���ƿ� ȡ��IPV6CP���ƿ������ݣ��ȷ�Request��Ϣ��Ȼ���յ� */
    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* ��������Ϣ*/
    if (pstIpV6CpInfo->pucIpv6cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1299);
        pHead    = pstIpV6CpInfo->pucIpv6cpMsg;
        pPacket  = pstIpV6CpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpV6CpInfo->ulIpv6cpLen;

        /* �յ��ն˷����ļ�Ȩ���� */
        PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulMsgLen);

        (VOID)PPP_Free(pstIpV6CpInfo->pucIpv6cpMsg);
        pstIpV6CpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
        pstIpV6CpInfo->ulIpv6cpLen = 0;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1300);

    PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: Done!");
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPP_StopIPV4CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV4
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StopIPV4CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_574);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    /* ����ipcp term��Ϣ���ipv4��· */
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
    {
        PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1301);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1302);
        if ((VOS_NULL_PTR != pstIpcpInfo)
            && (PPP_STATE_INITIAL == pstIpcpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1303);
            /* �����INIT״̬��˵�����ڵȴ�PDN�����ַ�����ʧ������Ҫ��LCP Protol Reject */
            pHead    = pstIpcpInfo->pucIpv4cpMsg;
            pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPCP, CONFREQ);

            (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
            pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
            pstIpcpInfo->ulIpv4cpLen = 0;
        }
        PPP_Core_IpcpV4FinProc(pstPppInfo);
    }

    PPPC_INFO_LOG("\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_ReleaseIPV4CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV4���ƿ�
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : y00170683
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_ReleaseIPV4CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_575);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    PPP_Core_IpcpV4FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1304);

    PPPC_INFO_LOG("\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_StopIPV6CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV6
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StopIPV6CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpv6cpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_576);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    /*����ֻ��ipv6����open ״̬��ipv6cp term��Ϣ���ipv6��·�� ����ֱ��ɾ��ipv6cp��Դ��*/
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6)
    {
        PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1305);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1306);
        if ((VOS_NULL_PTR != pstIpv6cpInfo)
            && (PPP_STATE_INITIAL == pstIpv6cpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpv6cpInfo->pucIpv6cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1307);
            /* �����INIT״̬��˵�����ڵȴ�PDN�����ַ�����ʧ������Ҫ��LCP Protol Reject */
            pHead    = pstIpv6cpInfo->pucIpv6cpMsg;
            pPacket  = pstIpv6cpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpv6cpInfo->ulIpv6cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPV6CP, CONFREQ);

            (VOID)PPP_Free(pstIpv6cpInfo->pucIpv6cpMsg);
            pstIpv6cpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
            pstIpv6cpInfo->ulIpv6cpLen = 0;
        }

        PPP_Core_IpcpV6FinProc(pstPppInfo);
    }

    PPPC_INFO_LOG("\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_ReleaseIPV6CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV6���ƿ�
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : y00170683
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_ReleaseIPV6CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_577);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    PPP_Core_IpcpV6FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1308);

    PPPC_INFO_LOG("\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_NotifyIpv6SendRA
 ��������  : ppp֪ͨipv6����ra��Ϣ
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_NotifyIpv6SendRA(VOS_UINT32 ulRpIndex, UCHAR ucPDNId)
{
    VOS_UINT32 ulResult = 0;
    VOS_UINT32 ulPdnIndex = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    /*��ȡrp������*/
    ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(ulRpIndex, (VOID**)&pstRpContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: User %u isn't exist!", ulRpIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_578);
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n PPP_NotifyIpv6SendRA: ucPDNId[%u]!", ucPDNId);
    if (VOS_NULL_BYTE == ucPDNId)
    {
        ucPDNId = 0;
    }
    PPPC_INFO_LOG1(
                 "\r\n PPP_NotifyIpv6SendRA1: ucPDNId[%u]!", ucPDNId);
    if (ucPDNId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: ucPDNId %u isn't valid!", ucPDNId);
        PPP_DBG_ERR_CNT(PPP_PHERR_579);
        return VOS_ERR;
    }

    ulPdnIndex = (VOS_UINT32)pstRpContext->ausPdnIndexArray[ucPDNId];

    /*��ȡPDN������*/
    ulResult = (VOS_UINT32)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: PDN %u isn't exist!", ulPdnIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_580);
        return VOS_ERR;
    }

    PPPC_INFO_LOG3(
                 "\r\n PPP_NotifyIpv6SendRA: ulPdnIndex[%u]bIpV6Used[%u]ulIpv6Timer[%u]!",
                 ulPdnIndex,pstPdnContext->bIpV6Used,pstPdnContext->ulIpv6Timer);

    if (pstPdnContext->bIpV6Used)
    {
        if (0 != pstPdnContext->ulIpv6Timer)
        {
            /* ֹͣIPv6��ʱ�������ٷ���RA��Ϣ */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
                /* ���ӵ�����Ϣ�������˳� */
                PPP_DBG_ERR_CNT(PPP_PHERR_581);
            }
        }

        pstPdnContext->ucIpv6RouteMsgNum = 0;

        /* ֪ͨIPv6����RA��Ϣ */
        ulResult = Ipv6_A11NotifySendRa(pstPdnContext->ulPdnIndex);
        if (VOS_OK != ulResult)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_582);
            PPPC_WARNING_LOG2(
                         "\r\n PPP_NotifyIpv6SendRA: Ipv6_A11NotifySendRa fail pdnindex[%u]!",
                         ulResult,pstPdnContext->ulPdnIndex);
            return VOS_ERR;
        }
        PPP_DBG_OK_CNT(PPP_PHOK_1309);
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_SendFakeIPV4CPReqMsg
 ��������  : PDN��ʱ��PPP�ṩ��PDN���÷���Config Req��Ϣ
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_SendFakeIPV4CPReqMsg(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* ��ȡPPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_583);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV4CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_584);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV4CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* ��ȡIPCP���ƿ� */
    pstIpcpInfo = pstPppInfo->pstIpcpInfo;
    if (VOS_NULL_PTR == pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_585);
            /* Malloc Error */
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_SendFakeIPV4CPReqMsg Malloc IPCP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpcpInfo = pstIpcpInfo;
    }

    PPP_MemSet((void *)pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

    /* �ж��Ƿ���ҪЭ��VJѹ�� */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

    pstFsm = (PPPFSM_S*)&(pstIpcpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* ���첢���ͱ��� */
    PPP_FSM_SendConfigReq(pstFsm);

    /* ���IPCP���ƿ� */
    PPP_ClearCB_IPCP(pstIpcpInfo);
    pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;


    PPP_DBG_OK_CNT(PPP_PHOK_1310);
    PPPC_INFO_LOG("\r\n PPP_SendFakeIPV4CPReqMsg Done !");
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPP_SendFakeIPV6CPReqMsg
 ��������  : PDN��ʱ��PPP�ṩ��PDN���÷���Config Req��Ϣ
 �������  : VOS_UINT32 ulRpIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_SendFakeIPV6CPReqMsg(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6cpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* ��ȡPPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_585);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV6CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_586);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV6CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* ��ȡIPV6CP���ƿ� */
    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if (VOS_NULL_PTR == pstIpV6cpInfo)
    {
        PPP_GETIPV6CPADDR(pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1311);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "\r\nPPP_SendFakeIPV6CPReqMsg Malloc IPv6CP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpV6cpInfo = pstIpV6cpInfo;
    }
    PPP_MemSet((void *)pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    pstFsm = (PPPFSM_S*)&(pstIpV6cpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* ���첢���ͱ��� */
    PPP_FSM_SendConfigReq(pstFsm);

    /* ���IPV6CP���ƿ� */
    PPP_ClearCB_IPV6CP(pstIpV6cpInfo);
    pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1312);
    PPPC_INFO_LOG("\r\n PPP_SendFakeIPV6CPReqMsg Done!");
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveLcpUpFromCore
 ��������  : PPP����յ�LCP_UP�¼�
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveLcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    if ( VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_ReceiveLcpUpFromCore Input para null! ");
        return VOS_ERR;
    }

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    if ( VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_INFO_LOG("\r\nPPP_Shell_ReceiveLcpUpFromCore para null");
        return VOS_ERR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, LCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_587);
        return VOS_ERR;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1313);

    /* ����ͳ��:LCPЭ�̳ɹ����� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulLcpSuccess, PERF_TYPE_PPPC_LCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveLcpUpFromCore: LcpSuccess: %d",
                  g_stPppPerfStatistic.ulLcpSuccess);
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveLcpDownFromCore
 ��������  : PPP����յ�LCP_DOWN�¼�
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Shell_ReceiveLcpDownFromCore(PPPINFO_S *pstPppInfo)
{
    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Enter pstPppInfo->bFailFlag=%d", pstPppInfo->bFailFlag);

    if (PPPLOWEDOWN != pstPppInfo->bFailFlag)
    {

        PPP_DBG_OK_CNT(PPP_PHOK_1314);

        if (LAPRECYCLE == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1315);
            PPPC_INFO_LOG(
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: LAPRECYCLE");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, LAPRECYCLE);
        }
        else if (PPPFADOWN == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1316);
            PPPC_INFO_LOG(
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: PPPFADOWN");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPPFADOWN);
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1317);
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPP_Negotiation_Fail);
        }

        PPPC_INFO_LOG1("\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Notify lower release user %u", pstPppInfo->ulRPIndex);
    }

    /* �������һ�� */
    PPPC_WARNING_LOG1("Into Delete CB", g_astPppPool[pstPppInfo->ulRPIndex].usState);
    if (PPP_CB_STATE_USED == g_astPppPool[pstPppInfo->ulRPIndex].usState)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1318);
        (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);

        PPPC_DeletePppId((VOS_UINT8)pstPppInfo->ulRPIndex);
    }

    PPPC_INFO_LOG("\r\n PPP_Shell_ReceiveLcpDownFromCore Done!");
    return;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_IpcpUpNoIp
 ��������  : IPCPЭ����ɺ��û�ûЭ��ip
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpUpNoIp(PPPINFO_S *pstPppInfo)
{
    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG2("\r\n [ppp]PPP_Shell_IpcpUpNoIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    /* ��CMip�û���ɾ����ջ */

    /*���ipv4��ַ��IPV4�汾����*/
    PPP_DBG_OK_CNT(PPP_PHOK_1319);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;
    PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_Shell_IpcpUpNegotiateIp
 ��������  :  PPP�Ĵ���IpcpUpNegotiateIp�¼��ĺ���
 �������  : PPPINFO_S *pstPppInfo
             PPPLCPINFO_S *pstLcpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpUpNegotiateIp(PPPINFO_S *pstPppInfo, PPPLCPINFO_S *pstLcpInfo)
{

    PPPC_INFO_LOG2("\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    /* �����˼�Ȩ��û�м�Ȩ */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_10);
        PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: is sip no auth: %u",
                      pstPppInfo->ulRPIndex);
        /*����֤����PPPЭ�̳ɹ�*/
        PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

        /* ��IPCP�ɹ�֮������֤�û�PDSN��ȥ����û� ����Ự������������1 */
        A11_ReqNumSubProc(pstPppInfo);
        PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);


        PPP_DBG_ERR_CNT(PPP_PHERR_588);

        return VOS_ERR;
    }
    PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNegotiateIp Done!");
    return VOS_OK;
}


/*****************************************************************************
�� �� ��  : PPP_Shell_IpcpSuccessProc
��������  : PPP�Ĵ���IpcpUp�ɹ���Ĵ�����
�������  : PPPINFO_S *pstPppInfo
�������  : ��
�� �� ֵ  : VOS_OK;VOS_ERR
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2009-03-19
  ��    ��   : c00127007
  �޸�����   : �����ɺ��� for reduce CC

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpSuccessProc(PPPINFO_S *pstPppInfo)
{
    ULONG64 ulNegoTime = 0;
    VOS_UINT32 ulRet;


    PPPC_INFO_LOG("\r\n [ppp]PPP_Shell_IpcpSuccessProc: Enter");
#if 0
    /* ����Ƿ�������cmip�û�DTS2014012102440  */
    if (VOS_OK != PDN_CheckIsCmipCanRun(pstPppInfo->ulRPIndex, 0))
    {
         PPPC_INFO_LOG(MID_PPPC, PDSN_DBGLVL_INFO,
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: dea cmip user for bit1493 is openl !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_DEA_CMIP_FOR_BIT1493);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return VOS_ERR;
    }
#endif

    /* ɾ��Э�̶�ʱ�� */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);


    if (pstPppInfo->bReNego)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1320);
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    /* ����ͳ��:IPCPЭ�̳ɹ����� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPP_DBG_OK_CNT(PPP_PHOK_1321);

    /* ��̬���ӱ���óɹ� */
    pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

    /* PPP��·�����ɹ� */
    pstPppInfo->bPppSuccess = 1;

    /* ��Э�̲���ͳ��( ���ⵥ��:DTS2012051201030 ) */
    if(0 == pstPppInfo->ulNegoEndTime)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1322);
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (VOS_UINT32)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
    }

    /* ��ʱ����,��¼�ı������ */

    if (pstPppInfo->bReNego)
    {
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (VOS_NULL_PTR != pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->bReqSendAck = VOS_FALSE;
    }

    /* �ͷ�L2TP���ƿ� */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, IPCP_INFOR))
    {
        PPPC_INFO_LOG(
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: PPP_SendUserInfo fail !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_590);
        return VOS_ERR;
    }

    ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* IPCP�ɹ�ʱ���� */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveIpcpUpFromCore
 ��������  : PPP�Ĵ���IpcpUp�¼��ĺ���
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-03-19
    ��    ��   : c00127007
    �޸�����   : �����ɺ��� for reduce CC

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveIpcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    VOS_UINT32 ulRet = VOS_OK;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;


    PPPC_INFO_LOG("\r\n [ppp]PPP_Shell_ReceiveIpcpUpFromCore: Enter");

    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstLcpInfo = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;


    if(pstIpcpInfo->stGotOptions.neg_vj)
    {
        /* ѡ���ӿ����ӿ���DPEID */
        if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
        {
            ulRet = (VOS_UINT32)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
            if (VOS_OK != ulRet)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_11);
                /* �ӿ�����λ�����û���Ҳ�Ѿ��ﵽ���ޣ������� */
                PPP_DBG_ERR_CNT(PPP_PHERR_591);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
                return VOS_ERR;
            }

            ulRet = (VOS_UINT32)PPP_CompCheckVjUserNum(&ucDmpuId);
            if(VOS_OK != ulRet)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_592);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
                return VOS_ERR;
            }

            pstPppInfo->ucDmpuId = ucDmpuId;
            pstPppInfo->ucDpeId  = ucDpeId;
        }

        if((VOS_FALSE == pstPppInfo->bVjFlag) && (VOS_TRUE == pstPppInfo->bMppcFlag))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1323);
        }
        /* END of liushuang*/
        PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_VJ);
    }


    /*Э����IP��ַ*/
    ulRet = PPP_Shell_IpcpUpNegotiateIp(pstPppInfo, pstLcpInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_593);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1324);
    return PPP_Shell_IpcpSuccessProc(pstPppInfo);
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_IpV6cpUpNoIp
 ��������  : IPV6CPЭ����ɺ��û�û��Э��IP
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpUpNoIp( PPPINFO_S *pstPppInfo )
{

    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    /* IPV6CPЭ��û��Э���û�IP��ֱ��֪ͨPDNɾ����ջ����֧��CMIPV6 */

    /*���ipv6��ַ��IPV6�汾����*/
    PPP_DBG_OK_CNT(PPP_PHOK_1325);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;
    PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_Shell_IpV6cpUpNegotiateIp
 ��������  : ipv6cp�׶�Э����ip��sip����up������
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpUpNegotiateIp( PPPINFO_S *pstPppInfo )
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG4(
                 "\r\n PPP_Shell_Ipv6cpUpNegotiateIp: ipcp up (negotiate ip) addr:%02x:%02x:%02x:%02x",
                 pstPppInfo->usPeerIPv6Addr[0],pstPppInfo->usPeerIPv6Addr[1],pstPppInfo->usPeerIPv6Addr[2],pstPppInfo->usPeerIPv6Addr[3]);

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ( VOS_NULL_PTR == pstLcpInfo )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_594);
        PPPC_INFO_LOG("\r\n PPP_Shell_IpV6cpUpNegotiateIp: lcp cb is null");
        return VOS_ERR;
    }

    /* �����˼�Ȩ��û�м�Ȩ */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_12);
        PPP_DBG_ERR_CNT(PPP_PHERR_595);
        PPPC_INFO_LOG1(
                     "\r\n PPP_Shell_Ipv6cpUpNegotiateIp 2: is sip no auth: %u",
                     pstPppInfo->ulRPIndex);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        /* ����ͳ��:IPv6CPЭ�̳ɹ����� DTS2012060402399 */
        A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);
        return VOS_ERR;
    }
    PPPC_INFO_LOG("\r\n PPP_Shell_IpV6cpUpNegotiateIp Done!");
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_IpV6cpSuccessProc
 ��������  : shell�㴦��ipv6cp�ɹ��Ĵ�����
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��12��
    ��    ��   : T62595
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpSuccessProc( PPPINFO_S *pstPppInfo )
{
    PDN_PPP_NCP_UP_S                    stNcpUpInfo = { 0 };
    ULONG64                             ulNegoTime = 0;
    VOS_UINT32                          ulRet;

    /* ����ͳ�� */

    /* IPV6CP�ɹ���PPP֪ͨPDN */
    VOS_MemCpy(stNcpUpInfo.aucIpV6Addr, pstPppInfo->usPeerIPv6Addr,PDN_IPV6ADDR_LEN);

    /* Added start by y00202564 at 2012-03-08 for ipv6����ͳ�� */
    /* ����ͳ��:IPv6CPЭ�̳ɹ����� */
    PPP_DBG_OK_CNT(PPP_PHOK_1326);
    PPPC_INFO_LOG(  "\r\n PPP_Shell_IpV6cpSuccessProc: IPV6_PerfStatistic Success:Enter !");

    A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);

    /* PPP��·�����ɹ� */
    pstPppInfo->bPppSuccess = 1;

    /* ɾ��Э�̶�ʱ�� */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);

    if(0 == pstPppInfo->ulNegoEndTime)
    {
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (VOS_UINT32)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
        PPP_DBG_OK_CNT(PPP_PHOK_1327);
    }

    /* ��̬���ӱ���óɹ� */
    pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

    /* ��ʱ���� */

    if (pstPppInfo->bReNegoV6)
    {
        pstPppInfo->bReNegoV6 = 0;

        /*ipcp���ƿ�Ϊ�ջ���v4��Э�̱����Ч���ͷſ��ƿ�*/
        if (((pstPppInfo->pstPppRenegoInfo)&&(VOS_NULL_PTR == pstPppInfo->pstIpcpInfo))
            || ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNego)))
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    (VOID)PPP_NotifyIpv6SendRA(pstPppInfo->ulRPIndex, VOS_NULL_BYTE);

    (VOID)PPP_SendUserInfo(pstPppInfo, IPCPV6_INFOR);

    ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* IPV6CP�ɹ�ʱ���� */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveIpV6cpUpFromCore
 ��������  : shell���յ����Ĳ�IPV6CP-UP�¼��Ĵ�����
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��12��
    ��    ��   : T62595
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveIpV6cpUpFromCore(  PPPINFO_S *pstPppInfo )
{
    PPPIPV6CPINFO_S* pstIpV6cpInfo = VOS_NULL_PTR;
    VOS_UINT32 ulRet = VOS_ERR;

    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if ( VOS_NULL_PTR == pstIpV6cpInfo )
    {
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
        PPP_DBG_ERR_CNT(PPP_PHERR_597);
        return VOS_ERR;
    }

    /* δЭ��ipΪCMIP���� */
    if (0 == pstIpV6cpInfo->stHisOptions.neg_addr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_598);
        (VOID)PPP_Shell_IpV6cpUpNoIp(pstPppInfo);
        return VOS_ERR;
    }

    /*Э����IP��ַ*/
    ulRet = PPP_Shell_IpV6cpUpNegotiateIp(pstPppInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_599);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1328);
    return PPP_Shell_IpV6cpSuccessProc(pstPppInfo);
}



/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveCcpUpFromCore
 ��������  : ��Core�յ�CCP UP�¼�����
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��7��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveCcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    VOS_UINT32 ulResult = 0;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;


    pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
    if (VOS_NULL_PTR == pstCcpInfo)
    {
         return VOS_ERR;
    }

    switch(pstCcpInfo->ucPppCompType)
    {
        case PPPCOMP_MPPC:
        {
            /* ѡ���ӿ����ӿ���DPEID */
            if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
            {
                ulResult = (VOS_UINT32)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
                if (VOS_OK != ulResult)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_600);
                    return VOS_ERR;
                }

                ulResult = (VOS_UINT32)PPP_CompCheckMppcUserNum(&ucDmpuId);
                if(VOS_OK != ulResult)
                {
                     /* �ӿ�����λ�����û���Ҳ�Ѿ��ﵽ���ޣ�����ֹCCP */
                     PPP_DBG_ERR_CNT(PPP_PHERR_601);
                     return VOS_ERR;
                }

                pstPppInfo->ucDmpuId = ucDmpuId;
                pstPppInfo->ucDpeId  = ucDpeId;
            }

            if((VOS_FALSE == pstPppInfo->bMppcFlag) && (VOS_TRUE == pstPppInfo->bVjFlag))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1329);
            }
            /* END of liushuang */

            PPP_DBG_OK_CNT(PPP_PHOK_1330);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_MPPC);
            break;
        }
        case PPPCOMP_LZS0:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1331);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS0);
            break;
        }
        case PPPCOMP_LZS1:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1332);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS1);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_602);
            PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_ReceiveCcpUpFromCore: Unknow compress type %d",
                      pstCcpInfo->ucPppCompType);
            return VOS_ERR;
        }
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, SCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_603);
        return VOS_ERR;
    }

    /* ����ͳ�� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulCcpSuccess, PERF_TYPE_PPPC_CCP_NEGO_SUCC, pstPppInfo->bEhrpdUser);


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveCcpDownFromCore
 ��������  : ��Core�յ�CCP Down�¼�����
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��7��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Shell_ReceiveCcpDownFromCore(PPPINFO_S *pstPppInfo)
{

    if (pstPppInfo->bMppcFlag)
    {
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_MPPC);
        PPP_DBG_OK_CNT(PPP_PHOK_1333);
    }
    if (pstPppInfo->bLzs0Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1334);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS0);
    }
    if (pstPppInfo->bLzs1Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1335);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS1);
    }


    /* BEGIN: Added for PN:���ݴ������ by wangyong 00138171, 2013/11/22 */
    if (PPPA11DOWNNOLCPTER == pstPppInfo->bFailFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1336);
    }
    /* END:   Added for PN:���ݴ������ by wangyong 00138171, 2013/11/22 */
#if 0
    /* ֪ͨA11���������ļ�A10�� */
    (VOID)A11_PPPC_SendUsrInfor(pstPppInfo->ulRPIndex,
                        &stUsrinfo,
                        SCP_INFOR);
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveFreePeerIpFromCore
 ��������  : ���ں˽����¼��Ľӿں���
 �������  : pstPppInfo:PPP���ƿ�
             ulCmd:������
             pPara:�¼��Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveEventFromCore(PPPINFO_S *pstPppInfo,
                                     VOS_UINT32      ulCmd,
                                     CHAR *     pPara)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT32 ulPdnIndex = 0;

    PPPC_INFO_LOG1(
        "\r\n [ppp]PPP_Shell_ReceiveEventFromCore: Enter ulCmd: %d", ulCmd);

    if (!pstPppInfo || (ulCmd >= PPP_EVENT_CTSEND))
    {
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_LCP_UP:
        {
            /* �·�LCP�û���Ϣ*/
            ulResult = PPP_Shell_ReceiveLcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_LCP_DOWN:
        {
            PPP_Shell_ReceiveLcpDownFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;

            break;
        }

        case PPP_IPV6CP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpV6cpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPV6CP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;


            /*��ȡrp������*/
            ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOID**)&pstRpContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
            {
                break;
            }

            ulPdnIndex = (VOS_UINT32)pstRpContext->ausPdnIndexArray[0];

            /*��ȡPDN������*/
            ulResult = (VOS_UINT32)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_604);
                break;
            }

            /* ֹͣIPv6��ʱ�������ٷ���RA��Ϣ */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
               /* ���ӵ�����Ϣ�������˳� */
               PPP_DBG_ERR_CNT(PPP_PHERR_605);
            }
            pstPdnContext->ulIpv6Timer = 0;

            break;
        }
        /* BEGIN: Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
        case PPP_VSNCP_UP:
        {
            ulResult = PPP_Shell_ReceiveVSNCPUpFromCore(pstPppInfo);
            break;
        }
        case PPP_VSNCP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            break;
        }
        /* END:   Added for PN:PDSN�ں� by wangyong 00138171, 2013/1/19 */
        case PPP_CCP_UP:
        {
            ulResult = PPP_Shell_ReceiveCcpUpFromCore(pstPppInfo);
            break;
        }
        case PPP_CCP_DOWN:
        {
            PPP_Shell_ReceiveCcpDownFromCore(pstPppInfo);
            break;
        }
        default:
            break;
    }

    return ulResult;
}
/*****************************************************************************
 �� �� ��  : PPP_Shell_GetPacketFromCore
 ��������  : �ں˷��ͱ��ĺ���
 �������  : pstPppInfo:PPP���ƿ�
             pPacket:�ַ�������ʽ���ڵı���
             ulLen:���ĳ���
             usProtocol:PPPЭ���
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_GetPacketFromCore(CHAR * pstPppInfo,
                                  UCHAR* pHead,
                                  UCHAR* pPacket,
                                  VOS_UINT32  ulLen,
                                  VOS_UINT16 usProtocol)
{
    PMBUF_S *pMbuf = VOS_NULL_PTR;
    VOS_UINT32 ulRetCode = 0;

    PPPC_INFO_LOG(  "\r\n [ppp]PPP_Shell_GetPacketFromCore: Enter");

    if (VOS_NULL_PTR == pstPppInfo)
    {
        return VOS_ERR;
    }

    ShowCode(pPacket, (VOS_UINT16)ulLen);

    /* ������� */
    /*
     |------------- PPP_RESERVED_PACKET_HEADER ----------|
     |                   |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |       ...         |       |       |       |       |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                                                   |
    pHead                                               pPacket
     */

    /* ��Ϣ���� */
    PPP_OmMsgTrc(((PPPINFO_S*)pstPppInfo)->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_OUT,
                 0, &(((PPPINFO_S*)pstPppInfo)->stIMSI), ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

    /* ����MBUF */
    pMbuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, ulLen);
    if (VOS_NULL_PTR == pMbuf)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_606);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: PMBUF_GetMbuf is NULL!");
        return VOS_ERR;
    }

    ulRetCode = PMBUF_CopyDataFromBufferToPMBuf(pMbuf,
                                              0,
                                              ulLen,
                                              (UCHAR *)pPacket,
                                              MID_PPPC);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_607);
        (VOS_VOID)PMBUF_Destroy(pMbuf);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: MBUF_CopyDataFromBufferToMBuf fail!");
        return VOS_ERR;
    }

    /* ����ͳ��:����Э�̱������� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulSendNego, PERF_TYPE_PPPC_SEND_NEGO_PKT_NUM, ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

    /* PPPC���ͼ��ظ�Э�̱���ʱ����ʹ��HDLCӲ����װ */
#if 0 /*(FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)*/
    return PPPC_HDLC_HARD_ProcProtocolPacket(((PPPINFO_S *)pstPppInfo)->ulRPIndex, pMbuf, 0, usProtocol);
#else
    return PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pMbuf, usProtocol);
#endif
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveNegoPacket
 ��������  : ����Э�̱��ĺ���,
 �������  : pMbuf:����
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveNegoPacket(PMBUF_S *pMbuf, VOS_UINT8 ucPppId)
{
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset = 0;
    UCHAR *pHead = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR ucLcpTerminateFlg = VOS_FALSE;
    CTTF_PPPC_TRACE_DATA_STRU *pstMntnInfo  = VOS_NULL_PTR;


    PPPC_INFO_LOG(  "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: Enter");

    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNego: %d", g_stPppPerfStatistic.ulReceiveNego);

    if (VOS_NULL_PTR == pMbuf)
    {
        /* ����ͳ��:��ЧЭ�̱�����*/

        PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d", g_stPppPerfStatistic.ulReceiveNegoErr);

        PPP_DBG_ERR_CNT(PPP_PHERR_608);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ucPppId);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG2(
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d, User %d isn't exist!",
                      g_stPppPerfStatistic.ulReceiveNegoErr, ucPppId);

        PPP_DBG_ERR_CNT(PPP_PHERR_611);
        return VOS_ERR;
    }

    pstPppInfo->bIsAsync = pstPppInfo->bSynAsyConvert;
    if (pstPppInfo->bSynAsyConvert && pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stWantOptions.neg_asyncmap  = 1;
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stAllowOptions.neg_asyncmap = 1;
    }

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pMbuf);

    /* ��ά�ɲ� */
    pstMntnInfo = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                   PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
    if (VOS_NULL_PTR != pstMntnInfo)
    {
        PS_MEM_SET(pstMntnInfo, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;

        if (PPPC_RAT_MODE_1X == PPPC_GetRatMode())
        {
            pstMntnInfo->ulSenderPid     = MSPS_PID_1X_FRLP;
            pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
            /* �յ���PPPЭ�̱�������һ */
            PPPC_1X_IncreaseNegoRcvCnt();
        }
        else
        {
            pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
            pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_GetRatMode();
            pstMntnInfo->ucStreamNum     = PPPC_HRPD_GetStreamNumber(ucPppId);
            /* �յ���PPPЭ�̱�������һ */
            PPPC_HRPD_IncreaseNegoRcvCnt();
        }

        pstMntnInfo->ulLength        = ulLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pstMntnInfo->aucValue);

        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        PPP_Free(pstMntnInfo);

        (VOS_VOID)pstMntnInfo;

        pstMntnInfo = VOS_NULL_PTR;
    }

    if (ulLen > PPP_DEFAULT_NEGO_PACKET_LEN)
    {
        PPPC_WARNING_LOG2(
                  "[ppp]: ReceiveNegoErr: %d, ulLength %d is too long!",
                  g_stPppPerfStatistic.ulReceiveNegoErr, ulLen);

        return VOS_OK;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /*mode by z0012969 for c05 �����Ż�*/
    pHead = g_ucPppRcvPacketHead;
    PPP_MemSet((void *)g_ucPppRcvPacketHead, 0,  PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER);

    (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pHead + ulOffset);

    /* BEGIN: Added for PN:DTS2013111600091 ���岻������������������ȥ�����ƽ��ʱ����OMȥ���ͷ� by y00170683, 2013/11/19 */
    PPP_CheckIsLcpTerminateMsg(pstPppInfo, pHead + ulOffset, ulLen, &ucLcpTerminateFlg);
    /* END:   Added for PN:DTS2013111600091 ���岻������������������ȥ�����ƽ��ʱ����OMȥ���ͷ� by y00170683, 2013/11/19 */

    /* �����ں˴��� */
    PPP_Core_ReceivePacketFromShell(pstPppInfo, pHead, pHead + ulOffset, ulLen);
    (VOS_VOID)pstMntnInfo;

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_Shell_ISLIoCtl
��������  : �ӵײ�����¼��Ľӿں���
�������  : USM_LAP2_MSG_S* pstMsg
�������  : pstPppInfo:PPPC���ƿ�ָ��
            ulCmd:������,����Ϊ����ֵ:
                  ISLUP:�ײ�UP
                  ISLDOWN:�ײ�DOWN                                                          ISPCFSWITCH:BS/PCF�л�
                  ISLRENEGO:�ײ���Э��
                  PPPC_L2TPUP:L2TP���͸�PPP��UP�¼�
                  PPPC_L2TPDOWN:L2TP���͸�PPP��DOWN�¼�
            pPara:�¼��Ĳ���,һ�������ΪNULL
                  L2TP��LNS�˱�ISLUPʱ������ԤЭ�̽��
�� �� ֵ  : VOS_OK;VOS_ERR
���ú���  :

��������  :

�޸���ʷ     :
1.��    ��   : 2000��04��04��
  ��    ��   : Deng Yi Ou
  �޸�����   : �����ɺ���
2.��    ��   : 2012��10��22��
  ��    ��   : luofang
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_ISLIoCtl(VOS_UINT32 ulRPIndex, VOS_UINT32 ulCmd, char *pPara)
{
    VOS_UINT32 ulA10Index  = 0;
    VOS_UINT32 ulReRpIndex = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    PPPRENOGOINFO stPppRenegoInfo = {0};


    PPPC_INFO_LOG2(  "\r\n [ppp]PPP_Shell_ISLIoCtl: Enter ulRPIndex %u, ulCmd %d", ulRPIndex, ulCmd);

    if (!(ulRPIndex <= PPP_MAX_USER_NUM)
        || (ulCmd >= ISLTUEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_615);
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_ISLDOWN:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1337);

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* SNMP������: ��������ͳ��ԭ��ֵ: pcf����ȥ�� */
                PPP_SNMP_PERF_SET_FAILREASON_PCF_RELEASE(pstPppInfo, pstPppInfo->pulCurrFsm);

                /* PPPЭ�̹����У��յ�PCF���ͷ����� ��������Ự��������������1 */
                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_OK_CNT(PPP_PHOK_1338);

                PPP_Core_ReceiveEventFromShell(pstPppInfo, (VOS_UINT32)PPPISLDOWN, VOS_NULL_PTR);
                (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);

                PPPC_DeletePppId((VOS_UINT8)pstPppInfo->ulRPIndex);
                PPP_DBG_OK_CNT(PPP_PHOK_1339);
            }
            else
            {
                PPPC_INFO_LOG1(
                        "\r\n [ppp]PPP_Shell_ISLIoCtl: PPPINFO index %d IS NULL!", ulRPIndex);

                return VOS_ERR;
            }
            break;
        }

        case ISPCFSWITCH:
        {
            if (VOS_NULL_PTR == pPara)
            {
                return VOS_ERR;
            }

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);
            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* ����RP INDEX */
                VOS_MemCpy(&g_astPppPool[*(VOS_UINT32*)pPara], pstPppInfo, sizeof(PPPINFO_S));

                g_astPppPool[*(VOS_UINT32*)pPara].ulRPIndex = *(VOS_UINT32*)pPara;
                g_astPppPool[ulRPIndex].usState = PPP_CB_STATE_FREE;
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_617);
                PPPC_INFO_LOG(
                            "\r\n [ppp]PPP_Shell_ISLIoCtl: ISPCFSWITCH: PPPINFO IS NULL!");
                return VOS_ERR;
            }
            break;
        }
        case ISLRENEGO:
        {
            /*�ײ��ϱ���PPPЭ�̱�������A10Index����Ҫת����RpIndex��Ϊ�˱��ֽӿ�ͳһ��
            ���ﻹ��ʹ��ulRPIndex��Ϊ��Σ����б����ֵΪ�ײ��������A10Index*/
            ulA10Index = ulRPIndex;
#if 0
            enReturn = (VOS_UINT32)SDB_GetRpContextByA10Index(ulA10Index,
                                                         (VOS_UINT32*)&ulReRpIndex,
                                                         (UCHAR**)&pstRpContext);
            if ((enReturn != SDB_SUCCESS) || (VOS_NULL_PTR == pstRpContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_618);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER008);
                return VOS_ERR;
            }
#endif
            PPP_DBG_OK_CNT(PPP_PHOK_1340);

            PPPC_INFO_LOG1(
                         "\r\n [ppp]PPP_Shell_ISLIoCtl: NP notify user %u RENEGO", ulReRpIndex);
            /*lint -e774*/
            GETPPPINFOPTRBYRP(pstPppInfo, ulReRpIndex);
            /*lint +e774*/
            if (VOS_NULL_PTR != pstPppInfo)
            {
                pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
                pstIpv6cpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;
                pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;

                PPP_DBG_OK_CNT(PPP_PHOK_1341);

                PPP_MemSet((VOID*)&stPppRenegoInfo, 0, sizeof(stPppRenegoInfo));

                if ( (pstIpcpInfo&&(PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
                    || ((pstIpv6cpInfo) && (PPP_STATE_OPENED == pstIpv6cpInfo->stFsm.ucState)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1342);

                    if (pstIpcpInfo)
                    {
                        pstPppInfo->bReNego = 1;
                        stPppRenegoInfo.ucIpcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpOptions, (VOID*)&pstIpcpInfo->stGotOptions,
                        sizeof(PPP_IPCP_OPTION_S));
                    }
                    if (pstIpv6cpInfo)
                    {
                        pstPppInfo->bReNegoV6 = 1;
                        stPppRenegoInfo.ucIpV6cpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpV6Options, (VOID*)&pstIpv6cpInfo->stGotOptions,
                        sizeof(PPP_IPV6CP_OPTION_S));
                    }

                    /* ͨ�ô��������Ƿ�˫ջ�û� */
                    if (pstCcpInfo && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
                    {
                        stPppRenegoInfo.ucCcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stCcpOptions, (VOID*)&pstCcpInfo->stGotOptions,
                        sizeof(PPP_CCP_options_S));
                    }

                    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);
                    //(VOID)PPP_NodeDelete(ulReRpIndex);
                    (VOID)PPP_NodeAdd(ulReRpIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

                    if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                    {
                        pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(sizeof(PPPRENOGOINFO));
                        if(VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo )
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_619);
                            (VOID)vos_printf("\r\n PPP_Shell_ISLIoCtl PPP_Malloc Failed!~!!");
                            return VOS_ERR;
                        }
                        PPP_MemSet((void*)pstPppInfo->pstPppRenegoInfo, 0, sizeof(PPPRENOGOINFO));
                    }

                    if (VOS_NULL_PTR != pstPppInfo->pstPppRenegoInfo)
                    {
                        (VOID)VOS_MemCpy(pstPppInfo->pstPppRenegoInfo, (VOID*)&stPppRenegoInfo,
                        sizeof(PPPRENOGOINFO));
                    }

                    PPP_DBG_OK_CNT(PPP_PHOK_1343);
                    pstPppInfo->bPpcAAAFlag = 0;

                    PPP_Core_ReceiveEventFromShell(pstPppInfo, PPPISLRENEGO, VOS_NULL_PTR);
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_620);
                PPPC_INFO_LOG(
                             "\r\n [ppp]PPP_Shell_ISLIoCtl: ISLRENEGO: PPPINFO IS VOS_NULL_PTR!");
                return VOS_ERR;
            }
            break;
        }
        default:
            break;
    }
    (VOS_VOID)ulA10Index;
    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ײ㷢�ͱ���,���ñ�����ǰ�����Mbuf��Ԥ����PPP����ͷ�ռ� *
* MODIFY DATE  ��modified by gxf for GGSN80 20030218                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                pMbuf:MBUF��ʽ���ڵı���                                   *
*                usProtocol:PPPЭ���                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_Shell_GetPacketFromCore��PPP_Shell_NiOutput��          *
*                MP_Transmit                                                *
****************************************************************************/
VOS_UINT32 PPP_Shell_SendPacketToISL(PPPINFO_S *pstPppInfo,
                               PMBUF_S *   pMbuf,
                               VOS_UINT16     usProtocol)
{
    /* ������� */

    /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
                                  pMbuf->pData
    */
    UCHAR* pBuf = VOS_NULL_PTR;
    VOS_UINT32 ulResult;
    VOS_UINT32 ulHeadLen;
    PPPLCPINFO_S* pstLcpInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG3(
                "\r\n PPP_Shell_SendPacketToISL: enter pstPppInfo=0x%x, pMbuf = 0x%x, usProtocol = 0x%x",
                pstPppInfo, pMbuf, usProtocol);

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstPppInfo->pstLcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_621);
        /* Added start by gaofeng 00127633 at 2008-07-08 PDSN V9R7C01B025 for ���� */
        (VOS_VOID)PMBUF_Destroy(pMbuf);
        /* Added end by gaofeng 00127633 at 2008-07-08 PDSN V9R7C01B025 for ���� */
        return VOS_ERR;
    }

    /* ��ñ���ָ�� */
    pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

   /* ���ӱ��ĳ��� */
   if ((pstPppInfo->bIsAsync)
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       ulHeadLen = PPP_HDRLEN;
   }
   else
   {
       ulHeadLen = PPP_HDRLEN - 2; /* ȥ��ff03 */
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* ��Э����ѹ���Ĵ��� */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       ulHeadLen -= 1;
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/

   PMBUF_PREPEND_MEMORY_SPACE(pMbuf, ulHeadLen, MID_PPPC, ulResult);

   if (ulResult == 0)
   {
       /* ok */
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_622);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_SendPacketToISL: Mbuf is NULL!");
           return VOS_ERR;
       }
   }
   else
   {
       PPP_DBG_ERR_CNT(PPP_PHERR_623);
       /* failed */
       PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "MBUF_PREPEND_MEMORY_SPACE Err!!");
       (VOS_VOID)PMBUF_Destroy(pMbuf);
       return VOS_ERR;
   }

   /* ��ñ���ָ�� */
   pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

   /* ������� */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
   pMbuf->pData
   pBuf
    */

   /* ��PPP����ͷ */
   /*PPP_MAKEHEADER(pBuf, usProtocol) ;*/
   if (pstPppInfo->bIsAsync
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       PPP_PUTCHAR(PPP_ALLSTATIONS, pBuf);
       PPP_PUTCHAR(PPP_UI, pBuf);
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* ��Э����ѹ���Ĵ��� */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       PPP_PUTCHAR(usProtocol, pBuf);
   }
   else
   {
       PPP_PUTSHORT(usProtocol, pBuf);
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/


   /* ������� */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |  ff   |   03  |    protocol   |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                               |
   pMbuf->pData                    |
                                   pBuf
    */

   /* ͬ/�첽ת�� */
   if (pstPppInfo->bSynAsyConvert)
   {
        /* ����PPPЭ��RFC1661��LCP����ѡ����ACCMѡ�����LCP���Ĳ����첽ӳ�� */
       pMbuf = PPP_SynToAsy(pMbuf,
                (usProtocol == PPP_LCP ? 0x00000000 : pstPppInfo->ulRemoteAccm));
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_624);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Syn To Asy Error!!");
           return VOS_ERR;
       }
   }

   if (1 == pstPppInfo->bPppClient)
   {
       /* ���ͱ��� */
       ulResult = PPPC_ULSendNegoFrame(pMbuf, pstPppInfo->ulRPIndex);

#ifdef PPPC_ST
       ulResult =VOS_OK;
#endif

        if (VOS_ERR == ulResult)
        {
           PPP_DBG_ERR_CNT(PPP_PHERR_625);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Send Packet Fail!!");
           return VOS_ERR;
        }
    }
    else
    {
       /* �ͷ�pMbuf */
        PMBUF_Destroy(pMbuf);
        PPP_DBG_ERR_CNT(PPP_PHERR_867);
        PPPC_WARNING_LOG1(
                    "\r\n PPP_Shell_SendPacketToISL: PPP mode err not client %d", pstPppInfo->bPppClient);
    }
    (VOS_VOID)pMbuf;
    (VOS_VOID)pBuf;
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveAAAResult
 ��������  : PPP�յ�AAA�ظ��ļ�Ȩ��Ϣ
 �������  : AAA_AUTHRSP_S *pstMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Shell_ReceiveAAAResult(AAA_AUTHRSP_S *pstMsg)
{
#if 0
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucValid = 0;
    VOS_UINT32 ulIndex = 0;
    VOS_UINT32 ulResult = 0;
    USM_PPP_LINKUP_RESULT_S stMsg ={0};  /* PPP Link up ֪ͨUSM����Ϣ�ṹ�� */
    /*��μ��*/
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_INFO_LOG( "\r\nPPP_Shell_ReceiveAAAResult Input para null!");
        return ;
    }

    ulIndex = pstMsg->ulSDBIndex;
    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_626);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER023);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: User %d isn't exist!", ulIndex);
        return;
    }

    if (pstMsg->ulMsgType != AAA_PPPC_CREAT_RSP)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_627);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER022);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP ReceiveAAAResult: Msg Type Error!!");
        return;
    }

    ucValid = ((VOS_NULL_PTR == pstPppInfo->pstPapInfo)
          || ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucServerState != PAP_STATE_WAIT_AAA)
          && ((VOS_NULL_PTR == pstPppInfo->pstChapInfo)
          || ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucServerState != CHAP_STATE_WAITING_AAA);
    if (ucValid)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_628);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: User %d state is wrong.", ulIndex);
        return;
    }

    /*��֤�ɹ�*/
    if (VOS_OK == pstMsg->ucResult)
    {
        /* ���AAA�·�������ͷ� L2TP,��ο�����ȥ���û� */
        ucValid = ((TUNNEL_L2TP != pstMsg->usTunnelType[0]) && (0 != pstMsg->usTunnelType[0]))
                &&(VOS_TRUE == SOFTPARA_BIT1478);
        if(ucValid)
        {
            /* ȥ���û� */
            PPP_DBG_ERR_CNT(PPP_PHERR_629);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_L2TPTUNLPARA_ERR);
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            return;
        }

        /*���� PDN_CheckL2tpUser()�����ж�*/
        ulResult = PDN_CheckL2tpUser(pstPppInfo->usCDBIndex,pstMsg);
        /*�����L2TP�û���ֱ��֪ͨUSM*/
        if(VOS_OK == ulResult)
        {
            /* ��䷢��USM����Ϣ�ṹ�� */
            stMsg.pucMsg = (UCHAR *)pstMsg;
            stMsg.ulRpIndex = pstPppInfo->ulRPIndex;
            stMsg.usDomainIndex = pstPppInfo->usCDBIndex;
            stMsg.usVirtualDomainIndex = pstPppInfo->usVirtualDomainIdx;
            VOS_MemCpy(stMsg.aucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

            (VOID)USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                          E_USM_MSGTYPE_PPP2USM_SETUP,
                                          (UCHAR *)&stMsg);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            return;
        }

    }
    else
    {
        /* AUTHģ�鷵��ʧ��ʱ����������Ự��������������1*/
        switch(pstMsg->ucResult)
        {
            case AAA_AUTH_FAIL:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);

                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_ERR_CNT(PPP_PHERR_630_AUTH_FAIL);

                break;
            }
            case AAA_AUTH_SRV_ERR:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);

                A11_ReqNumSubProc(pstPppInfo);

                PPP_DBG_ERR_CNT(PPP_PHERR_631);
                break;
            }
            default:
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_632);
                break;
            }
        }
    }

    /*���򣬻ظ���Ȩ��Ϣ.Ȼ����PPP_Core_NetworkPhase������
    ��������֤����Э�̺��������̣���֪ͨUSM*/
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_633);
        PPPC_INFO_LOG(
                   "\r\n PPP_Shell_ReceiveAAAResult:pstLcpInfo null");
        return;
    }

    /* ��chap\papģ�鴦�� */
    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1344);
        PPP_CHAP_ReceiveAAAResult(pstMsg);
    }
    if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1345);
        PPP_PAP_ReceiveAAAResult(pstMsg);
    }

    PPPC_INFO_LOG( "\r\n PPP_Shell_ReceiveAAAResult success !");
#endif
    return;
}


/****************************************************************************
* CREATE DATE  ��2009-03-20                                                 *
* CREATED BY   ��c00127007                                                  *
* FUNCTION     :                                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��PPPINFO_S* pstPppInfo                                      *
*                VOS_UINT32 ulType                                               *
* OUTPUT       ��                                                           *
* RETURN       ��VOID                                                       *
* CALLED BY    ��PPP_SendUserInfo                                           *
****************************************************************************/
VOID PPP_SendLcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    /* �·�Э�̽����A11 */
    pstUsrinfo->usMtu  = pstPppInfo->usMtu;
    pstUsrinfo->ulAccm = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);
    pstUsrinfo->ulMagicNum = pstLcpInfo->stGotOptions.magicnumber;
    pstUsrinfo->ulRpIndex = pstPppInfo->ulRPIndex;

    /* ͬ���첽��־ */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bSynAsyConvert ? A11_PPP_FLAG_SYNASY : 0);

    /* �ս�������־ */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bPppMode ? A11_PPP_FLAG_MODE : 0);

    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_pcompression ? A11_PPP_FLAG_PFC : 0);
    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_accompression ? A11_PPP_FLAG_ACFC : 0);

    return;
}

/****************************************************************************
* CREATE DATE  ��2009-03-20                                                 *
* CREATED BY   ��c00127007                                                  *
* FUNCTION     :                                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��PPPINFO_S* pstPppInfo                                      *
*                VOS_UINT32 ulType                                               *
* OUTPUT       ��                                                           *
* RETURN       ��VOID                                                       *
* CALLED BY    ��PPP_SendUserInfo                                           *
****************************************************************************/
VOID PPP_SendIpcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
     PPPIPCPINFO_S*  pstIpcpInfo = (PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo);
     PPP_CCP_INFO_S* pstCcpInfo  = (PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo);

     /*����PPP��Ϣ���û���Ϣ*/
     if ((VOS_NULL_PTR != pstIpcpInfo)
        && (PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
     {
          pstUsrinfo->ulPppFlag |= pstIpcpInfo->stGotOptions.neg_vj ? A11_PPP_FLAG_VJ : 0;
          pstUsrinfo->ucmaxslotindex = pstIpcpInfo->stGotOptions.maxslotindex;
     }

     if ((VOS_NULL_PTR != pstCcpInfo)
        && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
     {
         switch (pstCcpInfo->ucPppCompType)
         {
             case PPPCOMP_MPPC:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_MPPC;
                 break;
             case PPPCOMP_LZS0:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS0;
                 break;
             case PPPCOMP_LZS1:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS1;
                 break;
             default:
                 break;
         }
     }

     pstUsrinfo->ucPPPConFlag = (UCHAR)((pstUsrinfo->ulPppFlag) & (0xFFFFFFFC));

     if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
     {
         if (MAX_DMPU_NUM > pstPppInfo->ucDmpuId)
         {
             pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId + PPP_CPU_2_ON_SPU;  /* �ӿ�ID���߼�IDҪת��Ϊʵ��CPUID */
             pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
         }
     }
     else
     {
        pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId;
        pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
     }
     return;
}

/****************************************************************************
* CREATE DATE  ��2004/01/31                                                 *
* CREATED BY   ��heyajun                                                    *
* FUNCTION     :                                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��                                                           *
*                                                                           *
*                                                                           *
* OUTPUT       ��                                                           *
* RETURN       ���ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR                            *
* CALLED BY    ��                                                           *
****************************************************************************/
VOS_UINT32 PPP_SendUserInfo(PPPINFO_S* pstPppInfo, VOS_UINT32 ulType)
{
    A11_PPPC_USR_INFOR_S stUsrinfo = {0};

    if(LCP_INFOR == ulType)
    {
        PPP_SendLcpPreProc(pstPppInfo, &stUsrinfo);
    }
    else if ((IPCP_INFOR == ulType) || (SCP_INFOR == ulType))
    {
        PPP_SendIpcpPreProc(pstPppInfo, &stUsrinfo);
    }

    /* TODO:c00184031����PPP��Ϣ���û���Ϣ,�ο�����������g_stPppCallBacks.pfUpIoCtl */

    return VOS_OK;

}

/*End WGGSN_B03_L2TP_PPPC_COMP*/
/* Added start by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

  /*=======================================================================
   *  ��������:  GTPC_EncapUpdatePdpContextReqV1
   *  �������:  2004/01/28
   *  ��    ��:
   *  ��������:  GTPC�ṩ��PPPCģ���PPP���ķ�װ�ӿ�
   *  �������:  pMbuf        ��װ��PPPЭ����Ϣ��MBUF�ṹָ��
   *  �������:  ��
   *  ��������:  GTPC_SUCCESS            ���ɹ�
   *             GTPC_FAILURE            ��ʧ��
   *  ȫ�ֱ���:  ��
   *  ����˵��:  B03 ��������
   *  ���ú���:  *
   *  ��������:
   *=======================================================================*/
  VOS_VOID ShowCode(VOS_UINT8 *pucMsg, VOS_UINT16 usLen)
  {
      UCHAR ucMaxPerLine = 16;
      UCHAR ucCodeCount = 0, ucLine = 1;

      if ((VOS_NULL_PTR == pucMsg) || (usLen == 0))
      {
          return;
      }

      if (VRP_NO == g_ulPppDebugSwitch)
      {
          return;
      }

      (VOID)VOS_OutPrintf("\r\n #######Begin Decode Message#######\r\n");
      (VOID)VOS_OutPrintf("[%u]  ", ucLine++);

      while (usLen > 0)
      {
          (VOID)VOS_OutPrintf("%.2x ", *pucMsg );

          if (0 == (++ucCodeCount % ucMaxPerLine))
          {
              (VOID)VOS_OutPrintf("\r\n");
              if (ucLine < 10)
              {
                  (VOID)VOS_OutPrintf("[%u]  ", ucLine++);
              }
              else
              {
                  (VOID)VOS_OutPrintf("[%u] ", ucLine++);
              }
          }

          usLen--;
          pucMsg++;
      }

      (VOID)VOS_OutPrintf("\r\n#######End Decode Message#######\r\n");

      return;
  }

/* BEGIN: Added for PN:��ƽ̨ by wangyong 00138171, 2012/10/9 */
/*****************************************************************************
�� �� ��  : PPP_Shell_OutPut
��������  : ppp�����ṩ�ķ��ͺ���
�������  : VOS_UINT32 ulRpindex
           PMBUF_S *pstPMBuffNew
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��9��26��
  ��    ��   : wangyong 00138171
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_OutPut(VOS_UINT32 ulRpindex, PMBUF_S *pstPMBuffNew, VOS_UINT16 usProtocol)
{
  PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN��ָ��PPP���ƿ��ָ��*/
  VOS_UINT32 ulResult = 0;

  /* ��ȡPPPC���ƿ�ָ��*/
  GETPPPINFOPTRBYRP(pstPppInfo, ulRpindex);

  if (VOS_NULL_PTR == pstPppInfo)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_635);
      (VOID)PMBUF_Destroy((PMBUF_S*)pstPMBuffNew);
      return VOS_ERR;
  }

  /* ����PPP��ǵķ��ͺ��� */
  ulResult = PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pstPMBuffNew, (VOS_UINT16)usProtocol);
  if (VOS_OK != ulResult)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_636);
      return VOS_ERR;
  }
  return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_CM_GetAuthFlag
��������  : ppp���ṩ��CM��ȡ�Ƿ�����֤�û��ı�ʾ
�������  : VOS_UINT32 ulPdnIndex
            UCHAR * pucAuthFlag
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��12��14��
��    ��   : zhaichao 00129699
�޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_CM_GetAuthFlag(VOS_UINT32 ulPdnIndex,UCHAR * pucAuthFlag)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    if (pucAuthFlag == VOS_NULL_PTR)
    {
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : input pointer is null");
        return VOS_ERR;
    }

    (VOID)SDB_GetPdnContextByIndex(ulPdnIndex, (VOS_VOID **)&pstPdnContext);
    if (VOS_NULL_PTR == pstPdnContext)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_637);
        PPPC_INFO_LOG1(
                "\r\nPPP PPP_CM_GetAuthFlag : get pdn context error %d",ulPdnIndex);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
    if ((!pstPppInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_638);
        PPPC_WARNING_LOG1(
                 "\r\n PPP_CM_GetAuthFlag: Find RpIndex is wrong, ulRpIndex:%u", ulPdnIndex);
        return VOS_ERR;
    }

    *pucAuthFlag = 0;
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_639);
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag pstLcpInfo is null no auth !");
        return VOS_ERR;
    }

    if (E_PDNTYPE_CMIP == pstPdnContext->ucPdnType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1346);
        *pucAuthFlag = 1;
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : cmip user");
        return VOS_OK;
    }

    if ((1 == pstLcpInfo->stGotOptions.neg_chap) || (1 == pstLcpInfo->stGotOptions.neg_upap))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1347);
        *pucAuthFlag = 1;
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : used chap/pap auth");
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_SetSendSTRFlag
��������  : �ṩ��DIAM AUTH���ã����÷���STR���
�������  : VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��03��06��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOID PPP_SetSendSTRFlag(VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT32 ulRet = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_640);
        PPPC_INFO_LOG(  "\r\n [ppp]PPP_SetSendSTRFlag: pstPppInfo is null!");
        return;
    }

    PPPC_INFO_LOG3(
                 "\r\n [ppp]PPP_SetSendSTRFlag: ulAuthSessionState[%u] usPeerId[%u]ucAAAType[%u]!",
                 ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);

    if (VOS_TRUE == ulAuthSessionState)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1348);
        if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1349);
            /* ɾ���ϵ�hash */
            ulRet = Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex);
            if (ulRet != VOS_OK)
            {
                PPPC_WARNING_LOG3("[ppp]PPP_SetSendSTRFlag: Diam_AUTHHostRemoveByAAACBIndex fail[%u] usPeerId[%u]ucAAAType[%u]!",
                             ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
                PPP_DBG_ERR_CNT(PPP_PHERR_641);
            }

        }
        pstPppInfo->usPeerId = VOS_NULL_WORD;
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;

    }

    return;
}


/*****************************************************************************
�� �� ��  : PPP_GetIPCPNakHandlingFlag
��������  : �ṩ��PDN���ã���ȡIPCP NAK HANDLING
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��12��06��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_GetIPCPNakHandlingFlag(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_642);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: pstPppInfo is null!");
        return VOS_FALSE;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: bIPCPNakHandFlag[%u]!",
                 pstPppInfo->bIPCPNakHandFlag);

    return pstPppInfo->bIPCPNakHandFlag;
}


/*****************************************************************************
�� �� ��  : PPP_GetPeerID
��������  : �ṩ��DIAM AUTH���ã���ȡ������ID
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��03��06��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_GetPeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusPeerId)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_643);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetPeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetPeerID: usPeerId[%u]!",
                 pstPppInfo->usPeerId);

    *pusPeerId = pstPppInfo->usPeerId;

    return VOS_OK;
}



/*****************************************************************************
�� �� ��  : PPP_GetAAAType
��������  : �ṩ��DIAM AUTH���ã���ȡ����������
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��03��06��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_GetAAAType(VOS_UINT32 ulRpIndex, UCHAR *pucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_644);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetAAAType: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetAAAType: ucAAAType[%u]!",
                 pstPppInfo->ucAAAType);
    *pucAAAType = pstPppInfo->ucAAAType;
    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_UpdatePeerID
��������  : �ṩ��DIAM AUTH���ã����·�����ID
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��10��20��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_UpdatePeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 usPeerId, UCHAR ucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    VOS_UINT32 ulRet = 0;
    VOS_UINT16 usOldPeerId = 0;
    UCHAR ucOldAAAType = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_645);
        PPPC_WARNING_LOG("\r\n [ppp]PPP_UpdatePeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    ulRet = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOS_VOID **)&pstRpContext);
    if ((VOS_NULL_PTR == pstRpContext) || (ulRet != VOS_OK))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_646);
        PPPC_WARNING_LOG2(
                     "\r\n [ppp]PPP_UpdatePeerID: SDB_GetRpContextByIndex fail[%u] index[%u]!",
                     ulRet, pstPppInfo->ulRPIndex);
        return VOS_ERR;
    }

    PPPC_INFO_LOG3(
                 "\r\n [ppp]PPP_UpdatePeerID: usPeerId[%u][%u] aaatype[%u]!",
                 pstPppInfo->usPeerId, usPeerId, ucAAAType);

    PPP_DBG_OK_CNT(PPP_PHOK_1350);
    usOldPeerId = pstPppInfo->usPeerId;
    ucOldAAAType = pstPppInfo->ucAAAType;
    pstPppInfo->usPeerId = usPeerId;
    pstPppInfo->ucAAAType = ucAAAType;

    /* ���� */
    if ((USM_STATE_ACTIVE == pstRpContext->ucUsmState)
        && ((pstPppInfo->usPeerId != usOldPeerId)
        || (pstPppInfo->ucAAAType != ucOldAAAType)))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1351);
    }

    return VOS_OK;
}


/*****************************************************************************
�� �� ��  : PPP_JudgeIsDynAAAResource
��������  : �ṩ��DIAM AUTH���ã��˲鶯̬aaa��Դ
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��11��05��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_JudgeIsDynAAAResource(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusDynAAAIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pusDynAAAIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_647);
        PPPC_WARNING_LOG("\r\n [ppp]PPP_CheckDynAAAResource: pusDynAAAIndex is null!");
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_648);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_CheckDynAAAResource: pstPppInfo is null!");
        return VOS_ERR;
    }


    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1352);
        *pusDynAAAIndex = pstPppInfo->usPeerId;
        PPPC_INFO_LOG2(
                     "\r\n [ppp]PPP_CheckDynAAAResource: usPeerId[%u]aaatype[%u]!",
                     pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
        return VOS_OK;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1353);

    return VOS_ERR;
}


/*****************************************************************************
�� �� ��  : PPP_GetNowUTCInSec
��������  : �ṩ��USM���ã���ȡʱ���
�������  : VOS_UINT32 ulRpIndex
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��03��06��
   ��    ��   : wangyong 00138171
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_GetNowUTCInSec(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_649);
        PPPC_WARNING_LOG1(
                     "\r\n [ppp]PPP_GetNowUTCInSec: pstPppInfo is null!ulRpIndex=%u", ulRpIndex);
        return VOS_NULL_DWORD;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetNowUTCInSec: ulNowUTCInSec[%u]!",
                 pstPppInfo->ulNowUTCInSec);

    return pstPppInfo->ulNowUTCInSec;
}

/*****************************************************************************
 �� �� ��  : PPP_GetLocalL2tpCsi
 ��������  : ��ȡ����l2tp�����csi
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT64
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��2��
    ��    ��   : y00138047
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT64 PPP_GetLocalL2tpCsi(VOID)
{
    return g_ullPppLocalL2tpCsi;
}

/*****************************************************************************
 *  ��������:       PPP_CheckIsLcpTerminateMsg
 *  �������:       2013-11-19
 *  ��    ��:       y00170683
 *  ��������:       ����Ƿ���LCP-terminate��Ϣ
 *  �������:       PPPINFO_S *pstPppInfo, UCHAR *pucPacket, VOS_UINT32 ulLen
 *  �������:       UCHAR *pucLcpTerminateFlg
 *  ��������:       VOID
 *  ����˵��:       DTS2013111600091
 *  ���ú���:
 *  ��������:
*****************************************************************************/
VOID PPP_CheckIsLcpTerminateMsg(PPPINFO_S *pstPppInfo, UCHAR *pucPacket, VOS_UINT32 ulLen, UCHAR *pucLcpTerminateFlg)
{
    UCHAR ucCode = 0;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT16 usProtocol = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPppInfo))
    {
        return;
    }
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return;
    }
#endif

    /* ���Э���,������PPPͷ���� */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, pucPacket, &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        return;
    }

    /* �ƶ�ָ�� */
    pucPacket += ulOffset;
    ulLen -= ulOffset;

    PPP_GETCHAR(ucCode, pucPacket);
    (VOS_VOID)pucPacket;

    if (PPP_LCP == usProtocol)
    {
        if ((ulLen > PPP_LCP_NEGO_PACKET_MAX_LEN) || (ulLen < FSM_HDRLEN)
            || ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo)))
        {
            return;
        }
        if (TERMREQ == ucCode)
        {
            *pucLcpTerminateFlg = VOS_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 *  ��������:       PPP_SlaveBoardDiscardMsMsg
 *  �������:       2013-11-19
 *  ��    ��:       y00170683
 *  ��������:       ���岻����MS���͵���Ϣ
 *  �������:       PDN_CONTEXT_S *pstPdnContext, UCHAR ucSlaveReleaseFlg
 *  �������:
 *  ��������:       VOS_UINT32, ֻ������ʱ�ŷ���ERR
 *  ����˵��:       DTS2013111600091
 *  ���ú���:
 *  ��������:
*****************************************************************************/
VOS_UINT32 PPP_SlaveBoardDiscardMsMsg(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR ucSlaveReleaseFlg)
{
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return VOS_ERR;
    }
#endif

    if (VOS_NULL_PTR == pstRpContext)
    {
        return VOS_OK;
    }

    /* ���岻��Ҫ������ͷ���Ϣ */
    if (VOS_FALSE == ucSlaveReleaseFlg)
    {
        return VOS_OK;
    }

    pstRpContext->bSlaveReleaseFlg = VOS_TRUE;
    PPP_DBG_ERR_CNT(PPP_PHERR_650_MS_SLAVE_REL);

    return VOS_OK;
}


#define __PPP_L2TP_PROC__

/*****************************************************************************
�� �� ��  : PPP_L2tpMsgProc
��������  : PPPģ���յ�L2TP��Ϣ�Ĵ�����
�������  : PPPC_L2TP_NOTIFY_INFO *pstMsg
           VOS_UINT32 ulMsgCode
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��12��13��
  ��    ��   :ZHAICHAO
  �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_L2tpMsgProc(VOID *pstMsg, VOS_UINT32 ulMsgCode)
{
#if 0
    VOS_UINT32 ulRet = VOS_OK;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    VOS_UINT32 ulPdnIndex = 0;

    if ( VOS_NULL_PTR == pstMsg )
    {
         PPPC_INFO_LOG(  "\r\n [ppp]PPP_L2tpMsgProc: input para is null!");
         return ;
    }

    /* ����Ѿ����������ж� */
    switch (ulMsgCode)
    {
         case PPP_MSG_CODE_L2TP_UP:
         {
             L2TP_NOTIFY_PPPC_UP_INFO* pstL2tpUpMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_008);

             PPP_DBG_OK_CNT(PPP_PHOK_1356);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpUpMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_652);
                 return;
             }

             (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_ClearCB(pstPppInfo);
             }

             /* �Ƿ�ɾ��ppp���ƿ� */
             (VOID)PDN_L2tpUp(ulPdnIndex, pstMsg);
             break ;
         }
         case PPP_MSG_CODE_L2TP_DOWN:
         {
             L2TP_NOTIFY_PPPC_DOWN_INFO* pstL2tpDownMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_009);

             PPP_DBG_OK_CNT(PPP_PHOK_1357);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpDownMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_653);
                 return ;
             }

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);
             }
             else
             {
                 pstL2tpDownMsg->usFailReason = L2TP_DEA_CALL_BY_LNS;
             }

             (VOID)PDN_L2tpDown(ulPdnIndex, pstMsg);
             break ;
         }
         default:
         {
             PPP_DBG_ERR_CNT(PPP_PHERR_654);
             VOS_DBGASSERT(0);
             PPPC_INFO_LOG(
                                  "\r\n PPP_L2tpMsgProc: Proc l2tp msg faild! MsgCode[%d].",
                                  ulMsgCode);
             break;
         }
    }
#endif
    return;
}

 /*****************************************************************************
   �� �� ��  : PPP_Shell_NotifyL2tpUp
   ��������  : PPP֪ͨL2TP����L2tp���
   �������  : VOS_UINT32 ulIndex
               L2TP_PPPPARA_S *pstPPPPara
   �������  : ��
   �� �� ֵ  : VOS_UINT32
   ���ú���  :
   ��������  :

   �޸���ʷ      :
    1.��    ��   : 2012��10��17��
      ��    ��   : luofang
      �޸�����   : �����ɺ���

  *****************************************************************************/
VOS_UINT32 PPP_Shell_NotifyL2tpUp(VOS_UINT32 ulIndex, L2TP_PPPPARA_S *pstPPPPara )
{
#if 0
    VOS_UINT32         ulResult = 0;
    SDB_RETURNCODE_E   enSdbReturn = SDB_SUCCESS;
    SDB_PDSN_RP_CONTEXT_S *pstContext = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1358);
    PPPC_INFO_LOG( ( VOS_UINT32 )  "\r\n PPP_NotifyL2tpUp: Call %lu up in.", ulIndex );

    if (VOS_NULL_PTR == pstPPPPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_655);
        PPPC_INFO_LOG( ( VOS_UINT32 )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp: pstPPPPara is null" );
        return VOS_ERR;
    }

    enSdbReturn = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulIndex, ( UCHAR** )&pstContext );
    if ( ( SDB_SUCCESS != enSdbReturn   )  || ( VOS_NULL_PTR == pstContext  ) )
    {
        /* �������Ĳ����� */
        PPPC_INFO_LOG( ( VOS_UINT32 )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp The PDP Context dose not exist %lu", enSdbReturn);
        PPP_DBG_ERR_CNT(PPP_PHERR_656);
        return VOS_ERR;
    }

    PPP_L2tpUpPreProc(pstPPPPara, pstContext,ulIndex);

    ulResult = PPP_SendMsgToL2tp(L2TP_MSGCODE_UP,
                                    (UCHAR *)pstPPPPara,
                                    sizeof(L2TP_PPPPARA_S));

    PPPC_INFO_LOG( ( VOS_UINT32 )  "\r\n PPP_NotifyL2tpUp  exit %lu spu type %lu", ulResult, g_enPppBoardType);

    if (VOS_OK != ulResult)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_657);
        return VOS_ERR ;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1359);
#endif
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_NotifyL2tpDown
 ��������  : PPPģ��֪ͨL2TPģ��Down
 �������  : VOS_UINT32 ulRPIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode)
{
#if 0
    VOS_UINT32 ulResult = VOS_OK;
    L2TP_DOWNPARA_S stL2tpDown = {0};

    stL2tpDown.ulPdpindex   = PDN_PDNScIndexToPDNGlobalIndex(pstPdnContext->ulPdnIndex);
    stL2tpDown.ulTeidc      = pstPdnContext->ulTeidc;
    stL2tpDown.ulGiifIndex  = pstPdnContext->stL2tp.ulIfIndex;
    stL2tpDown.usLocalTID   = pstPdnContext->stL2tp.usLocalTid;
    stL2tpDown.usLocalSID   = pstPdnContext->stL2tp.usLocalSid;
    stL2tpDown.ucScid       = (UCHAR)PPP_SELF_CMPIDXINSG;

    ulResult = PPP_SendMsgToL2tp(ucMsgCode,
                                    (UCHAR *)&stL2tpDown,
                                    sizeof(L2TP_DOWNPARA_S));

    if ( VOS_OK != ulResult )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_658);
        PPPC_INFO_LOG(
                    "\r\n [ppp]PPP_Shell_NotifyL2tpDown: PPP_SendMsgToL2tp error %u,%u",
                    ulResult, ucMsgCode);
        return VOS_ERR;
    }
#endif
    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_L2tpUpPreProc
��������  :  ���������������L2TP����
�������  : L2TP_PPPPARA_S * pstPPPPara
           SDB_GSPU_CONTEXT_S *pstContext
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��10��17��
  ��    ��   : luofang
  �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_L2tpUpPreProc(L2TP_PPPPARA_S * pstPPPPara, SDB_PDSN_RP_CONTEXT_S *psRpContext,VOS_UINT32 ulIndex)
{
#if 0
    UCHAR szTempImsi[M_IMSI_LEN] = {0}; /*Imsi to string*/
    VOS_UINT32 imsiLen = 0;
    VOS_UINT32 i = 0;  /*IMSI Lenth*/
    CHAR szCallFromId[CALL_FROMID_LENTH] = {0};
    UCHAR aucMsisdn[A11_MSISDN_LEN] = {0};
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL_PTR;
    UCHAR ucMDNFlag = 0;
    VOS_UINT32 ulRet = 0;

    if ((VOS_NULL_PTR == pstPPPPara) || (VOS_NULL_PTR == psRpContext))
    {
        PPPC_INFO_LOG(  "\r\nPPP_L2tpUpPreProc input para is null");
        return;
    }


    ImsiToString(psRpContext->stImsi, szTempImsi);     /*Convert IMSI to string for variable IMSI*/

    ulRet = A11_GetDomainByIndex(psRpContext->usDomainIndex, &pstDomain);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_659);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_LOG, "\r\nPPP_L2tpUpPreProc Get Domain configure fail!");
        return;
    }

    ucMDNFlag = pstDomain->ucL2tpAttribute;

    if((HSGW_DOMAIN_L2TP_ATTRIBUTE_MDN == ucMDNFlag) && (VOS_TRUE == psRpContext->ucMsisdnFlag)) /* �ж�AAA�Ƿ��·��˸��ֶ� */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1360);
        A11_BCDToString(psRpContext->szMsisdn, aucMsisdn, 15);
        PTM_StrNCpy(pstPPPPara->stSessionInfo.szDialingNumber, aucMsisdn, L2TP_DIALINGNUM_LEN-1);
    }
    else
    {
        /*ȡIMSI��Ϊ�û����룬18����ο���*/
        if (g_ulSoftPara534 & 0x01)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1361);
            VOS_MemCpy(pstPPPPara->stSessionInfo.szDialingNumber, szTempImsi,
            VOS_StrLen((CHAR *)szTempImsi));
        }
        else
        {
            imsiLen = VOS_StrLen((CHAR *)szTempImsi);
            if ((imsiLen >= 10) && (imsiLen <= 15))
            {
                for (i = 0; i < 10; i++)
                {
                    szCallFromId[i] = (CHAR)szTempImsi[i + imsiLen - 10];
                }

                szCallFromId[10] = '\0';
                VOS_StrCpy(pstPPPPara->stSessionInfo.szDialingNumber, szCallFromId);
            }
            else
            {
                PPPC_INFO_LOG(  "\r\n PPP_L2tpUpPreProc IMSI Length Error: %d \r\n", imsiLen);
            }
        }
    }

    VOS_StrCpy(pstPPPPara->stSessionInfo.szDialedNumber, "8888");

    pstPPPPara->stSessionInfo.bBearTypeUsed = VOS_TRUE;
    pstPPPPara->stSessionInfo.ulBearType = BEARER_TYPE_BOTH;
    pstPPPPara->stSessionInfo.ulFramType = FRAMING_TYPE_BOTH;
    pstPPPPara->stSessionInfo.bPrivateGroupIdUsed = VOS_TRUE;
#endif
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_L2tpProc
 ��������  : L2TP�û�����
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��6��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

2.��    ��   : 2012��12��13��
  ��    ��   : zhaichao 00129699
  �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPP_Shell_L2tpProc(VOS_UINT32 ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN��ָ��PPP���ƿ��ָ��*/

    if (VOS_NULL_PTR == pstL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_660);
        return VOS_ERR;
    }

    /* ��ȡPPPC���ƿ�ָ��*/
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_661);
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstPppInfo->pL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_662);
        return VOS_ERR;
    }

    VOS_MemCpy(&(pstL2tpPara->stSessionInfo),
                pstPppInfo->pL2tpPara,
                sizeof(L2TP_SESSIONPARA_S));

    pstL2tpPara->stSessionInfo.bLcpOptionUsed   = VOS_TRUE;
    pstL2tpPara->stSessionInfo.bProxyAuthenUsed = VOS_TRUE;

    /*��l2tp�û�,֪ͨl2tp up*/
    /* ֪ͨL2TP������� */

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_663);
        return VOS_ERR;
    }

    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1362);
        PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1363);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1364);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_L2tpProc: Receive unexpected message!!");
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    if (VOS_ERR == PPP_Shell_NotifyL2tpUp(pstPppInfo->ulRPIndex, pstL2tpPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_664);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: PPP_Shell_NotifyL2tpUp failed");
        pstPppInfo->bFailFlag = PPPL2TPDOWN;
        /* BEGIN: D by h50774 for PS10.1���ģ���PDN״̬������ʧ�ܼ���, 2013/1/3 */
        /* PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo); */
        /* END  : D by h50774 for PS10.1���ģ���PDN״̬������ʧ�ܼ���, 2013/1/3 */
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1365);
    pstPppInfo->bAuthFlag = VOS_TRUE;
    pstPppInfo->bPppSuccess = 1;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_SendMsgToL2tp
 ��������  : ������Ϣ��LAC�߳�
 �������  : UCHAR ucMsgCode
             UCHAR* pucMsg
             VOS_UINT32 ulMsgLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_SendMsgToL2tp(UCHAR ucMsgCode, UCHAR* pucMsg, VOS_UINT32 ulMsgLen )
{
#if 0
    VOS_UINT32 ulRet = VOS_OK;

    if (VOS_NULL_PTR == pucMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_665);
        PPPC_INFO_LOG(  "\r\n [ppp]PPP_SendMsgToL2tp : Input ptr is null");
        return VOS_ERR;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)    /*SPUD��*/
    {
        ulRet = PPP_SendRtMsg(PPP_SELF_CSI, g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_PPPC, ucMsgCode, pucMsg, ulMsgLen);
        if ( VOS_OK != ulRet )
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_666);
            PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_LOG ,
                        "\r\n %s:  PPP_SendMsgToL2tp error, the ret = 0x%lx, msgcode %d. ",
                        (CHAR *)(__FUNCTION__), ulRet, ucMsgCode );
            return VOS_ERR;
        }
    }
    else
    {
        ulRet = PPP_SendURTMsg(g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_FCM, ucMsgCode, pucMsg, ulMsgLen);
        if (VOS_OK != ulRet)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_667);
            PPPC_INFO_LOG( MID_PPPC, PPP_DEBUG_LOG,
                        "\r\n PPP_SendMsgToL2tp: Call PPP_SendURTMsg ret %lu msgcode %d.", ulRet, ucMsgCode);
            return VOS_ERR;
        }
    }

    PPPC_INFO_LOG(
                "\r\n PPP_SendMsgToL2tp:  send message to lac succ. ");
#endif
    return VOS_OK ;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
