/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndPpp.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��10��21��
  ����޸�   :
  ��������   : TAF APSģ�鷢����Ϣ��PPP�ĺ���ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsApi.h"
#include  "MnApsComm.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "TafApsComFunc.h"
#include  "TafApsDecode.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "taf_aps_ppp_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_PPP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_FillPppActReqInfoWithCardSipContent
 ��������  : PPP act reqʹ�ÿ��еļ�Ȩ����
 �������  :
 �������  : VOS_UINT8                          *pucUserName,
             VOS_UINT8                          *pucPswd,
             VOS_UINT8                          *pucAuthType
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_FillPppActReqInfoWithCardSipContent(
    VOS_UINT8                          *pucUserName,
    VOS_UINT8                          *pucPswd,
    VOS_UINT8                          *pucAuthType
)
{
    TAF_APS_3GPD_SIP_INFO_STRU          st3GpdSipInfo;
    VOS_UINT32                          ulReadUserProfileRslt;
    VOS_UINT32                          ulReadPppPapSsRslt;

    PS_MEM_SET(&st3GpdSipInfo, 0, sizeof(TAF_APS_3GPD_SIP_INFO_STRU));
    ulReadUserProfileRslt = TAF_APS_Get3GpdPppSipNaiInfoFromCard(&st3GpdSipInfo);
    ulReadPppPapSsRslt    = TAF_APS_Get3GpdPppSipPapSsInfoFromCard(&st3GpdSipInfo);

    if (VOS_TRUE == ulReadUserProfileRslt)
    {
        VOS_StrNCpy((VOS_CHAR*)pucUserName,
                    (VOS_CHAR*)st3GpdSipInfo.aucNaiStr,
                    TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);


    }
    if ((VOS_TRUE == ulReadPppPapSsRslt) && (TAF_PDP_AUTH_TYPE_PAP == st3GpdSipInfo.enPppAuthType))
    {
        VOS_StrNCpy((VOS_CHAR*)pucPswd,
                    (VOS_CHAR*)st3GpdSipInfo.aucPapSsStr,
                    TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);
    }
    *pucAuthType = TAF_APS_MapApsAuthTypeToPpp(st3GpdSipInfo.enPppAuthType);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppActReq
 ��������  : ֪ͨPPPģ��PPPЭ�̼���
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��27��
    ��    ��   : Y00213812
    �޸�����   : ʹ��NDISDUP����AUTHDATA�����õ��û�����������Ϊ��Ȩ����
*****************************************************************************/
VOS_VOID  TAF_APS_SndPppActReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_ACT_REQ_STRU               *pstPppActReq;

    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg       = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    pstPppActReq    = (APS_PPP_ACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_ACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppActReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppActReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_ACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppActReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppActReq->enMsgId       = ID_APS_PPP_ACT_REQ;
    pstPppActReq->usOpId        = 0;
    pstPppActReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    pstPppActReq->enPdnType     = TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    switch(pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):

            if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_MODEM;

                TAF_APS_FillPppActReqInfoWithCardSipContent(pstPppActReq->aucUserName,
                                                            pstPppActReq->aucPassword,
                                                           &pstPppActReq->enAuthType);
            }
            else
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_AP;

                VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucUserName,
                            (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucUserName,
                            TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);

                VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucPassword,
                            (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucPassWord,
                            TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);

                pstPppActReq->enAuthType = TAF_APS_MapApsAuthTypeToPpp(pstCallOrigReq->stDialParaInfo.enAuthType);
            }


            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
            PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

            if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
            {
                pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_MODEM;

                TAF_APS_FillPppActReqInfoWithCardSipContent(pstPppActReq->aucUserName,
                                                            pstPppActReq->aucPassword,
                                                           &pstPppActReq->enAuthType);

                /* ������chap��Ȩ���� */
                if (TAF_APS_PPP_AUTH_TYPE_PAP != pstPppActReq->enAuthType)
                {
                    PS_MEM_SET(pstPppActReq->aucUserName, 0, TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN + 1);
                    PS_MEM_SET(pstPppActReq->aucPassword, 0, TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN + 1);
                    pstPppActReq->enAuthType = TAF_APS_PPP_AUTH_TYPE_NONE;
                }
            }
            else
            {
                /* MODEM����ʱ��ֻ֧��PAP���͵ļ�Ȩ */
                if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
                 && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
                {
                    ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                                     pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                                     pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

                    if (VOS_OK == ulResult)
                    {
                        pstPppActReq->ulNaiSource = TAF_APS_PPP_NAI_FROM_AP;
                        PS_MEM_CPY(pstPppActReq->aucUserName,
                                   stAuthInfo.unAuthParam.stPapParam.aucUsername,
                                   stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                        PS_MEM_CPY(pstPppActReq->aucPassword,
                                   stAuthInfo.unAuthParam.stPapParam.aucPassword,
                                   stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);

                        pstPppActReq->enAuthType = TAF_APS_PPP_AUTH_TYPE_PAP;
                    }
                }
            }
            break;

        default:
            break;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppActReq);

}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppDeactReq
 ��������  : ֪ͨPPPģ��PPPЭ��ȥ����
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDeactReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_REQ_STRU             *pstPppDeactReq;

    pstPppDeactReq = (APS_PPP_DEACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactReq->enMsgId       = ID_APS_PPP_DEACT_REQ;

    pstPppDeactReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);


    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactReq);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppDeactInd
 ��������  : ֪ͨPPPģ��PPPֱ��ȥ����
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDeactInd(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_IND_STRU             *pstPppDeactInd;

    pstPppDeactInd = (APS_PPP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_IND_STRU));

    if (VOS_NULL_PTR == pstPppDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactInd->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactInd->enMsgId       = ID_APS_PPP_DEACT_IND;

    pstPppDeactInd->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactInd);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppModeChangeNotify
 ��������  : ֪ͨPPPģ��PPPģʽ�ı�֪ͨ
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppModeChangeNotify(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_MODE_CHANGE_NTF_STRU       *pstPppModeChangeNty;

    pstPppModeChangeNty = (APS_PPP_MODE_CHANGE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_MODE_CHANGE_NTF_STRU));

    if (VOS_NULL_PTR == pstPppModeChangeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppModeChangeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppModeChangeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_MODE_CHANGE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppModeChangeNty->ulReceiverPid = MSPS_PID_PPPC;
    pstPppModeChangeNty->enMsgId       = ID_APS_PPP_MODE_CHANGE_NTF;
    pstPppModeChangeNty->usOpId        = 0;
    pstPppModeChangeNty->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppModeChangeNty);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppModeChangeNotify
 ��������  : ֪ͨPPPģ��AT���õĲ���ģʽ
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDialModeNotify(
    VOS_UINT16                          usClientId
)
{
    APS_PPP_DIAL_MODE_NTF_STRU         *pstDialModeNty;

    pstDialModeNty = (APS_PPP_DIAL_MODE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DIAL_MODE_NTF_STRU));

    if (VOS_NULL_PTR == pstDialModeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDialModeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDialModeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DIAL_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDialModeNty->ulReceiverPid        = MSPS_PID_PPPC;
    pstDialModeNty->enMsgId              = ID_APS_PPP_DIAL_MODE_NTF;
    pstDialModeNty->usOpId               = 0;
    pstDialModeNty->usClientId           = usClientId;
    pstDialModeNty->enDialMode           = (VOS_UINT8)TAF_APS_GetFsmCtxCdataDialMode();

    PS_SEND_MSG(WUEPS_PID_TAF, pstDialModeNty);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppLinkStatusNotify
 ��������  : APS Notify current link status to PPP module
 �������  : VOS_UINT8                           ucPdpId
             TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndPppLinkStatusNotify(
    VOS_UINT8                           ucPdpId,
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus
)
{
    APS_PPP_LINK_STATUS_NTF_STRU       *pstLinkStatusNtf;

    pstLinkStatusNtf = (APS_PPP_LINK_STATUS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_LINK_STATUS_NTF_STRU));

    if (VOS_NULL_PTR == pstLinkStatusNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppLinkStatusNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLinkStatusNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_LINK_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstLinkStatusNtf->ulReceiverPid = MSPS_PID_PPPC;
    pstLinkStatusNtf->enMsgId       = ID_APS_PPP_LINK_STATUS_NTF;
    pstLinkStatusNtf->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstLinkStatusNtf->enLinkStatus  = enLinkStatus;

    PS_SEND_MSG(WUEPS_PID_TAF, pstLinkStatusNtf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetPppLinkStatus
 ��������  : �ṩ��L2��ѯ�տ���·�Ľӿ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  ucLinkStatus;

    ucLinkStatus = TAF_APS_PPP_LINK_NOT_EXISTED;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        switch (TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            case TAF_APS_CDATA_AIR_LINK_NO_LINK:
                ucLinkStatus = TAF_APS_PPP_LINK_NOT_EXISTED;
                break;

            case TAF_APS_CDATA_AIR_LINK_CONNECTING:
                ucLinkStatus = TAF_APS_PPP_LINK_CONNING;
                break;

            case TAF_APS_CDATA_AIR_LINK_DISCONNECTING:
                ucLinkStatus = TAF_APS_PPP_LINK_DISCING;
                break;

            case TAF_APS_CDATA_AIR_LINK_CONNECTED:
                ucLinkStatus = TAF_APS_PPP_LINK_CONNECTED;
                break;

            default:
                break;
        }
    }

    return ucLinkStatus;
}


#endif






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
