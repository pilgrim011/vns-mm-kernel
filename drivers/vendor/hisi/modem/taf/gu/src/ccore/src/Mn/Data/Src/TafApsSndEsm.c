/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndEsm.c��
  �� �� ��   : ����
  ��    ��   : w00316404
  ��������   : 2015��12��7��
  ����޸�   :
  ��������   : ��Esm����Ϣ���ͺ���
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ļ�

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsSndEsm.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDESM_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPdpSetupReq
 ��������  : ����ID_APP_ESM_PDP_SETUP_REQ��Ϣ����
 �������  : pstSetPdpCtxStateReq       - +CGACT������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactPdpSetupReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    APP_ESM_PDP_SETUP_REQ_STRU         *pstPsActReq;
    VOS_UINT32                          ulLoop;

    /* ������Ϣ */
    pstPsActReq = (APP_ESM_PDP_SETUP_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_SETUP_REQ_STRU));

    if (VOS_NULL_PTR == pstPsActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmSetCgactPdpSetupReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstPsActReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstPsActReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstPsActReq, ID_APP_ESM_PDP_SETUP_REQ);

    /* ����copy����CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstSetPdpCtxStateReq->stCidListStateInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    /* ��д��Ϣ���� */
    pstPsActReq->enSetupType         = APP_ESM_PDP_SETUP_TYPE_NORMAL;
    pstPsActReq->ulCid               = ulLoop;

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstPsActReq);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPdpReleaseReq
 ��������  : ����ID_APP_ESM_PDP_RELEASE_REQ��Ϣ����
 �������  : pstSetPdpCtxStateReq       - +CGACT������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactPdpReleaseReq(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    APP_ESM_PDP_RELEASE_REQ_STRU       *pstPsDeactReq;
    VOS_UINT32                          ulLoop;

    /* ������Ϣ */
    pstPsDeactReq = (APP_ESM_PDP_RELEASE_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));

    if (VOS_NULL_PTR == pstPsDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmSetCgactPdpReleaseReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstPsDeactReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstPsDeactReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstPsDeactReq, ID_APP_ESM_PDP_RELEASE_REQ);

    /* ����copy����CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstSetPdpCtxStateReq->stCidListStateInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    /* ��д��Ϣ���� */
    pstPsDeactReq->ulCid               = ulLoop;

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstPsDeactReq);

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmSetCgactReq
 ��������  : +CGACT REQ��ں���
 �������  : ucPdpId                    - APSʵ������
             pstSetPdpCtxStateReq       - +CGACT������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmSetCgactMsgDistr(
    VOS_UINT8                           ucPdpId,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
)
{
    if (APS_ESM_PDP_STATE_ACTIVE == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        TAF_APS_SndEsmSetCgactPdpSetupReq(pstSetPdpCtxStateReq);
    }
    else
    {
        TAF_APS_SndEsmSetCgactPdpReleaseReq(pstSetPdpCtxStateReq);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPppDialSetupReq
 ��������  : ����ID_APP_ESM_PDP_SETUP_REQ��Ϣ, ���𲦺�
 �������  : pstPppDialOrigReq          - ���Ų���
             pstAuthInfo                - ��Ȩ��Ϣ
             pstIpcpInfo                - IPCP��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPppDialSetupReq(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo
)
{
    APP_ESM_PDP_SETUP_REQ_STRU         *pstReq;

    /* ������Ϣ */
    pstReq = (APP_ESM_PDP_SETUP_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_SETUP_REQ_STRU));

    if (VOS_NULL_PTR == pstReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPppDialSetupReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstReq, ID_APP_ESM_PDP_SETUP_REQ);

    /* ��д��Ϣ���� */
    pstReq->enSetupType             = APP_ESM_PDP_SETUP_TYPE_PPP;
    pstReq->ulCid                   = pstPppDialOrigReq->stPppDialParaInfo.ucCid;

    PS_MEM_CPY((VOS_UINT8*)(&pstReq->stPppInfo.stAuthInfo),
               (VOS_UINT8*)(pstAuthInfo),
               sizeof(APP_ESM_AUTH_INFO_STRU));

    PS_MEM_CPY((VOS_UINT8*)(&pstReq->stPppInfo.stIpcpInfo),
               (VOS_UINT8*)(pstIpcpInfo),
               sizeof(APP_ESM_IPCP_INFO_STRU));

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstReq);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmNdisconnReq
 ��������  : ����ID_APP_ESM_NDISCONN_REQ��Ϣ, ���𲦺�
 �������  : pstCallOrigReq             - ���Ų���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_SndEsmNdisconnReq(
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq
)
{
    APP_ESM_NDISCONN_REQ_STRU          *pstReq;

    /* ������Ϣ */
    pstReq = (APP_ESM_NDISCONN_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_NDISCONN_REQ_STRU));
    if (VOS_NULL_PTR == pstReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmNdisconnReq: Memory alloc failed.");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstReq, ID_APP_ESM_NDISCONN_REQ);

    /* ��д��Ϣ���� */
    pstReq->ulCid                       = pstCallOrigReq->stDialParaInfo.ucCid;

    pstReq->bitOpPdnType                = 1;
    pstReq->bitOpApn                    = 1;  /* ȱʡ�����޹�����CID*/
    pstReq->bitOpGwAuth                 = 1;

    pstReq->bitOpIpv4AddrAlloc          = pstCallOrigReq->stDialParaInfo.bitOpIpv4AddrAlloc;
    pstReq->bitOpPcscfDiscovery         = pstCallOrigReq->stDialParaInfo.bitOpPcscfDiscovery;
    pstReq->bitOpImCnSignalFlg          = pstCallOrigReq->stDialParaInfo.bitOpImCnSignalFlg;

    pstReq->enIpv4AddrAlloc             = pstCallOrigReq->stDialParaInfo.enIpv4AddrAlloc;
    pstReq->enPcscfDiscovery            = pstCallOrigReq->stDialParaInfo.enPcscfDiscovery;
    pstReq->enImCnSignalFlg             = pstCallOrigReq->stDialParaInfo.enImCnSignalFlg;

    pstReq->enPdnType                   = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ((VOS_TRUE                      == pstCallOrigReq->stDialParaInfo.bitOpReqType)
     && (TAF_PDP_REQUEST_TYPE_HANDOVER == pstCallOrigReq->stDialParaInfo.enPdpRequestType))
    {
        pstReq->enPdnReqestType = APP_ESM_PDN_REQUEST_TYPE_HANDOVER;
    }
    else
    {
        pstReq->enPdnReqestType = APP_ESM_PDN_REQUEST_TYPE_INITIAL;
    }

    if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpEmergencyInd)
    {
        pstReq->enEmergencyInd          = pstCallOrigReq->stDialParaInfo.enEmergencyInd;
    }
    else
    {
        pstReq->enEmergencyInd          = APS_L4A_PDP_NOT_FOR_EMC;
    }


    if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpApn)
    {
        pstReq->stApnInfo.ucApnLen      = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucApn);
        PS_MEM_CPY(pstReq->stApnInfo.aucApnName,
                   pstCallOrigReq->stDialParaInfo.aucApn,
                   pstReq->stApnInfo.ucApnLen);

        PIH_GetVsimAPN(APS_L4A_MAX_APN_LEN, pstReq->stApnInfo.aucApnName, &pstReq->stApnInfo.ucApnLen);
    }

    if ( (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpAuthType )
      && (TAF_PDP_AUTH_TYPE_NONE != pstCallOrigReq->stDialParaInfo.enAuthType))
    {
        /* USER NAME*/
        if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpUserName)
        {
            pstReq->stGwAuthInfo.ucUserNameLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucUserName);
            PS_MEM_CPY(pstReq->stGwAuthInfo.aucUserName,
                       pstCallOrigReq->stDialParaInfo.aucUserName,
                       sizeof(pstReq->stGwAuthInfo.aucUserName));
        }

        /* PASSWORD*/
        if (VOS_TRUE == pstCallOrigReq->stDialParaInfo.bitOpPassWord)
        {
            pstReq->stGwAuthInfo.ucPwdLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucPassWord);
            PS_MEM_CPY(pstReq->stGwAuthInfo.aucPwd,
                       pstCallOrigReq->stDialParaInfo.aucPassWord,
                       sizeof(pstReq->stGwAuthInfo.aucPwd));
        }

        pstReq->stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstCallOrigReq->stDialParaInfo.enAuthType;
    }

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstReq);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPdpModifyReq
 ��������  : ����ID_APP_ESM_PDP_MODIFY_REQ��Ϣ, �Ͽ�����
 �������  : pstCallModifyReq           - �޸�EPS���ز���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpModifyReq(
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq
)
{
    APP_ESM_INQ_PARA_REQ_STRU          *pstModifyReq;
    VOS_UINT32                          ulLoop;

    /* ������Ϣ */
    pstModifyReq = (APP_ESM_INQ_PARA_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_INQ_PARA_REQ_STRU));

    if (VOS_NULL_PTR == pstModifyReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpModifyReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstModifyReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstModifyReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstModifyReq, ID_APP_ESM_PDP_MODIFY_REQ);

    /* ��д��Ϣ���� */

    /* �������е�CID */
    for (ulLoop = 1; ulLoop <= TAF_MAX_CID; ulLoop++ )
    {
        if(pstCallModifyReq->stCidListInfo.aucCid[ulLoop])
        {
            break;
        }
    }

    pstModifyReq->ulCid                 = ulLoop;

    if ( pstModifyReq->ulCid == TAF_MAX_CID + 1 )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstModifyReq);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmCallModifyReq: cid is error.");
        return;
    }

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstModifyReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPdpReleaseReq
 ��������  : ����ID_APP_ESM_PDP_RELEASE_REQ��Ϣ, �Ͽ�����
 �������  : pstCalEndReq               - �Ͽ����Ų���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpReleaseReq(
    TAF_PS_CALL_END_REQ_STRU           *pstCalEndReq
)
{
    APP_ESM_PDP_RELEASE_REQ_STRU       *pstReleaseReq;

    /* ������Ϣ */
    pstReleaseReq = (APP_ESM_PDP_RELEASE_REQ_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));

    if (VOS_NULL_PTR == pstReleaseReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpReleaseReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstReleaseReq), 0x00, TAF_APS_GET_MSG_LENGTH(pstReleaseReq));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstReleaseReq, ID_APP_ESM_PDP_RELEASE_REQ);

    /* ��д��Ϣ���� */
    pstReleaseReq->ulCid = pstCalEndReq->ucCid;

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstReleaseReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEsmPdpManagerRsp
 ��������  : ����ID_APP_ESM_PDP_MANAGE_RSP��Ϣ, Ӧ�����缤��
 �������  : ulSetupRslt           - Ӧ��EPS�����Ƿ����
             ucCid                 - CID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEsmPdpManagerRsp(
    APS_ESM_BEARER_ACT_RESULT_ENUM_UINT32   ulSetupRslt,
    VOS_UINT8                               ucCid
)
{
    APP_ESM_PDP_MANAGER_RSP_STRU       *pstManageRsp;

    /* ������Ϣ */
    pstManageRsp = (APP_ESM_PDP_MANAGER_RSP_STRU*)TAF_APS_ALLOC_MSG_WITH_HDR(
                            sizeof(APP_ESM_PDP_MANAGER_RSP_STRU));

    if (VOS_NULL_PTR == pstManageRsp)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEsmPdpManagerRsp: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(TAF_APS_GET_MSG_ENTITY(pstManageRsp), 0x00, TAF_APS_GET_MSG_LENGTH(pstManageRsp));

    /* ��д��Ϣͷ */
    TAF_APS_CFG_ESM_MSG_HDR(pstManageRsp, ID_APP_ESM_PDP_MANAGER_RSP);

    /* ��д��Ϣ���� */
    pstManageRsp->ulCid                 = ucCid;
    pstManageRsp->ulSetupRslt           = ulSetupRslt;

    /* ������Ϣ */
    TAF_APS_SEND_MSG(pstManageRsp);

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


