/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmEncode.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module to encode.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "CnasEhsmEncode.h"
#include "CnasEhsmDecode.h"
#include "CnasEhsmComFunc.h"


/* To Do: Need to add EHSM to PPP interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_ENCODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/


#if 0
/*****************************************************************************
 Function Name   : CNAS_EHSM_EncodeIpcpContent
 Description     : IPCP��������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_EHSM_EncodeIpcpContent
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpIndex;
    VOS_UINT32                          ulTmpIndex2;
    VOS_UINT16                          usItemId;
    VOS_UINT32                          ulSum;

    pTmpucSendMsg   = pucSendMsg;
    ulSum           = *pulLength;
    ulTmpIndex      = 0;
    ulTmpIndex2     = 0;
    usItemId        = 0;

    if (EHSM_APS_PDN_TYPE_IPV6 == enPdnType)
    {
        CNAS_NORMAL_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodeIpcpContent:PDN type is ipv6!");

        *pulLength = ulSum;

        return ;
    }

    /*IPCP for DNS Server begin*/
    usItemId = CNAS_EHSM_PCO_ITEM_TYPE_IPCP;
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)((usItemId & CNAS_EHSM_HIGH_BYTE)
                                                    >> CNAS_EHSM_MOVEMENT_8_BITS);
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)(usItemId & CNAS_EHSM_LOW_BYTE);

    /*����IPCP��Ԫ����index��ͳ�Ƴ��Ⱥ����*/
    ulTmpIndex = ulSum++;

    /*��дIPCP���� rfc 1661 5.1 Configure-request */
    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     Code      |  Identifier   |            Length             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Options ...
    +-+-+-+-+
    */
    pTmpucSendMsg[ulSum++] = CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_REQ;

    pTmpucSendMsg[ulSum++] = 0;/*id*/

    /*����IPCP����������Ԫ����index��ͳ�Ƴ��Ⱥ���룬����ռ��2���ֽڣ�
      ʵ�ʲ��ᳬ��һ���ֽڣ���˼�¼��index�ڵ�2���ֽڴ�*/
    pTmpucSendMsg[ulSum++] = 0;
    ulTmpIndex2 = ulSum++;

    /*��дIPCP Options����*/
    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     Type      |    Length     |           IP-Address
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            IP-Address (cont)       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    pTmpucSendMsg[ulSum++] = CNAS_EHSM_IPCP_OPTIONS_PRI_DNS_ADDR;
    pTmpucSendMsg[ulSum++] = CNAS_EHSM_IPCP_OPTION_DNS_LEN;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = CNAS_EHSM_IPCP_OPTIONS_SEC_DNS_ADDR;
    pTmpucSendMsg[ulSum++] = CNAS_EHSM_IPCP_OPTION_DNS_LEN;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;
    pTmpucSendMsg[ulSum++] = 0;

    /*������Ӧ������Ϣ*/
    pTmpucSendMsg[ulTmpIndex2] = (VOS_UINT8)((ulSum - ulTmpIndex) -1);
    pTmpucSendMsg[ulTmpIndex]  = (VOS_UINT8)((ulSum - ulTmpIndex) -1);
    /*IPCP for DNS Server end*/

    *pulLength = ulSum;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_EncodeIpv4AllocMode
 Description     : ����IPV4 ��ȡ��ʽ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_EHSM_EncodeIpv4AllocMode
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT16                          usItemId;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;

    ulSum           = *pulLength;
    pTmpucSendMsg     = pucSendMsg;
    usItemId        = 0;

    if (EHSM_APS_PDN_TYPE_IPV6 == enPdnType)
    {
        CNAS_NORMAL_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodeIpv4AllocMode:PDN type is ipv6!");

        *pulLength = ulSum;

        return ;
    }

    /*��ֵContainer ID:IP address allocation via NAS signalling */
    usItemId = CNAS_EHSM_PCO_ITEM_TYPE_NAS_SIGNALING;
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)((usItemId & CNAS_EHSM_HIGH_BYTE)
                                                    >> CNAS_EHSM_MOVEMENT_8_BITS);
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)(usItemId & CNAS_EHSM_LOW_BYTE);

    /*��ֵContainer LEN:IP address allocation via NAS signalling */
    pTmpucSendMsg[ulSum++] = 0;

    *pulLength                          = ulSum;
    return;
}


/*****************************************************************************
 Function Name   : CNAS_EHSM_EncodeIpv4DnsReq
 Description     : ����IPV4 DNS����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_EHSM_EncodeIpv4DnsReq
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT16                          usItemId;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;

    ulSum           = *pulLength;
    pTmpucSendMsg     = pucSendMsg;
    usItemId        = 0;

    if (EHSM_APS_PDN_TYPE_IPV6 == enPdnType)
    {
        CNAS_NORMAL_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodeIpv4DnsReq:PDN type is ipv6!");

        *pulLength = ulSum;

        return ;
    }

    /*��ֵContainer ID:DNS Server IPv4 Address Request */
    usItemId = CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4;
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)((usItemId & CNAS_EHSM_HIGH_BYTE)
                                                    >> CNAS_EHSM_MOVEMENT_8_BITS);
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)(usItemId & CNAS_EHSM_LOW_BYTE);

    /*��ֵContainer LEN:DNS Server IPv4 Address Request */
    pTmpucSendMsg[ulSum++] = 0;

    *pulLength                          = ulSum;
    return;
}


/*****************************************************************************
 Function Name   : CNAS_EHSM_EncodePcoBcm
 Description     : ����BCM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_EHSM_EncodePcoBcm
(
    VOS_UINT8                          *pucSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;

    ulSum           = *pulLength;
    pTmpucSendMsg   = pucSendMsg;
    usItemId        = 0;

    /*��ֵMS Support of Network Requested Bearer Control indicator */
    usItemId = CNAS_EHSM_PCO_ITEM_TYPE_BCM;
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)((usItemId & CNAS_EHSM_HIGH_BYTE)
                                                    >> CNAS_EHSM_MOVEMENT_8_BITS);
    pTmpucSendMsg[ulSum++] = (VOS_UINT8)(usItemId & CNAS_EHSM_LOW_BYTE);

    /*��ֵContainer LEN:MS Support of Network Requested Bearer Control indicator */
    pTmpucSendMsg[ulSum++] = 0;

    *pulLength                          = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_EncodeIpv6DnsReq
 Description     : ����IPV6 DNS����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_EHSM_EncodeIpv6DnsReq
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT16                          usItemId;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;

    usItemId        = 0;
    ulSum           = *pulLength;
    pTmpucSendMsg     = pucSendMsg;

    if ((EHSM_APS_PDN_TYPE_IPV6 == enPdnType)
     || (EHSM_APS_PDN_TYPE_IPV4V6== enPdnType))
    {
        /*��ֵContainer ID:DNS Server IPv6 Address Request */
        usItemId = CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6;
        pTmpucSendMsg[ulSum++] = (VOS_UINT8)((usItemId & CNAS_EHSM_HIGH_BYTE)
                                                        >> CNAS_EHSM_MOVEMENT_8_BITS);
        pTmpucSendMsg[ulSum++] = (VOS_UINT8)(usItemId & CNAS_EHSM_LOW_BYTE);

        /*��ֵContainer LEN:DNS Server IPv6 Address Request */
        pTmpucSendMsg[ulSum++] = 0;
    }

    *pulLength                          = ulSum;
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_RandomBytes
 ��������  : ���������
 �������  : VOS_UINT8                           *pucBuf
             VOS_UINT16                           usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��06��
    ��    ��   : y00314741
    �޸�����   : ��ֲMN_APS_RandomBytes����, �޸ĺ�������

*****************************************************************************/
VOS_VOID CNAS_EHSM_RandomBytes(
    VOS_UINT8                          *pucBuf,
    VOS_UINT8                           usLen
)
{
    VOS_UINT8                           usLoop;

    for (usLoop = 0; usLoop < usLen; ++usLoop)
    {
        pucBuf[usLoop] = (VOS_UINT8)VOS_Rand(0xff);
    }

    return;
}

/*****************************************************************************
 Function Name  : CNAS_EHSM_EncodePco()
 Description    : EHSMģ����װPCO��Ϣ����
 Input          : VOS_UINT8 *pucSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_EncodePco
(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType,
    VOS_UINT8                                               ucPdnId,
    VOS_UINT8                                              *pucSendMsg,
    VOS_UINT32                                             *pulLength
)
{
    VOS_UINT8                          *pTmpucSendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulSum;
    VOS_UINT16                          usIdentifier;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearInfo = VOS_NULL_PTR;
    CNAS_EHSM_CONFIG_HEAD_STRU          stConfigHead;
    CNAS_EHSM_CONFIG_OPTION_HEAD_STRU   stCfgOptionHdr;
    VOS_UINT16                          usPapLen;
    VOS_UINT8                           aucAuthChapChalVal[CNAS_EHSM_CHAP_CHALLENGE_LEN];
    VOS_UINT8                           aucAuthChapRespVal[CNAS_EHSM_CHAP_MD5_LEN];
    TAF_MSG_DIGEST_FIVE_CTX             stMdCtx;
#ifdef DMT
    VOS_UINT8                           aucDmtAuthChapChalVal[CNAS_EHSM_CHAP_CHALLENGE_LEN] = {0x46, 0x17, 0x73, 0xa4,
                                                                                               0xa1, 0x10, 0xa3, 0xff,
                                                                                               0x27, 0xeb, 0xcb, 0x99,
                                                                                               0xba, 0xd8, 0xc9, 0xf6};

#endif

    pTmpucSendMsg       = pucSendMsg;
    ulSum               = *pulLength;
    pstLocalPdnBearInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);


    pTmpucSendMsg[ulSum++] = CNAS_EHSM_PCO_CONFIG_PROTOCOL;

    if (CNAS_EHSM_AUTH_TYPE_PAP == pstLocalPdnBearInfo->enAuthType)
    {
        /*-----------------------------------------------------------
            Config protocol header (PAP)
            |  code  | identifier | length |
            | username length |  username  |
            | password length |  password  |
         ------------------------------------------------------------*/
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: enAuthType is PAP");

        usPapLen     = sizeof(CNAS_EHSM_CONFIG_HEAD_STRU) + sizeof(VOS_UINT8)
                        + pstLocalPdnBearInfo->ucUserNameLen+ sizeof(VOS_UINT8)
                        + pstLocalPdnBearInfo->ucPwdLen;

        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_PAP);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);

        NAS_MEM_SET_S(&stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        stConfigHead.ucCode       = CNAS_EHSM_PAP_REQ;
        stConfigHead.ucIdentifier = 0x00;
        stConfigHead.usLength     = HOST_TO_NETWORK(usPapLen);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_HEAD_STRU);

        pTmpucSendMsg[ulSum] = pstLocalPdnBearInfo->ucUserNameLen;
        ulSum        = ulSum + sizeof(VOS_UINT8);

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), pstLocalPdnBearInfo->aucUserName, pstLocalPdnBearInfo->ucUserNameLen);
        ulSum        = ulSum + pstLocalPdnBearInfo->ucUserNameLen;

        pTmpucSendMsg[ulSum] = pstLocalPdnBearInfo->ucPwdLen;
        ulSum        = ulSum + sizeof(VOS_UINT8);

        if (0 != pstLocalPdnBearInfo->ucPwdLen)
        {
            NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), pstLocalPdnBearInfo->aucPwd, pstLocalPdnBearInfo->ucPwdLen);
            ulSum        = ulSum + pstLocalPdnBearInfo->ucPwdLen;
        }
    }


    if (CNAS_EHSM_AUTH_TYPE_CHAP == pstLocalPdnBearInfo->enAuthType)
    {
        /*----------------------------------------------------------------------------
             Config protocol header (CHAP)
            |  code(chal)  | identifier | length |
            |    chal length    |   challenge    |
            |  username                          |
             Config protocol header (CHAP)
            |  code(resp)  | identifier | length |
            |  MD5 length  |   MD5 value         |
            |  username                          |
        -----------------------------------------------------------------------------*/
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: enAuthType is CHAP");

        /*-----------------------------------------------------------------------------
         CHAP Challenge Packet
         ------------------------------------------------------------------------------*/
        usPapLen     = sizeof(CNAS_EHSM_CONFIG_HEAD_STRU) + sizeof(VOS_UINT8)
                       + CNAS_EHSM_CHAP_CHALLENGE_LEN + pstLocalPdnBearInfo->ucUserNameLen;

        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_CHAP);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);

        NAS_MEM_SET_S(&stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        stConfigHead.ucCode       = CNAS_EHSM_CHAP_CHALLENGE;
        stConfigHead.ucIdentifier = 0x00;
        stConfigHead.usLength     = HOST_TO_NETWORK(usPapLen);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_HEAD_STRU);

        pTmpucSendMsg[ulSum] = CNAS_EHSM_CHAP_CHALLENGE_LEN;
        ulSum        = ulSum + sizeof(VOS_UINT8);

#ifdef DMT
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), aucDmtAuthChapChalVal, CNAS_EHSM_CHAP_CHALLENGE_LEN);
#else
        NAS_MEM_SET_S(aucAuthChapChalVal, sizeof(aucAuthChapChalVal), 0, sizeof(aucAuthChapChalVal));
        CNAS_EHSM_RandomBytes(aucAuthChapChalVal, CNAS_EHSM_CHAP_CHALLENGE_LEN);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), aucAuthChapChalVal, CNAS_EHSM_CHAP_CHALLENGE_LEN);
#endif
        ulSum        = ulSum + CNAS_EHSM_CHAP_CHALLENGE_LEN;

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), pstLocalPdnBearInfo->aucUserName, pstLocalPdnBearInfo->ucUserNameLen);
        ulSum        = ulSum + pstLocalPdnBearInfo->ucUserNameLen;

        /*-----------------------------------------------------------------------------
         CHAP Response Packet
         ------------------------------------------------------------------------------*/
        usPapLen     = sizeof(CNAS_EHSM_CONFIG_HEAD_STRU) + sizeof(VOS_UINT8)
                       + CNAS_EHSM_CHAP_MD5_LEN + pstLocalPdnBearInfo->ucUserNameLen;

        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_CHAP);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);

        NAS_MEM_SET_S(&stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        stConfigHead.ucCode       = CNAS_EHSM_CHAP_RESPONSE;
        stConfigHead.ucIdentifier = 0x00;
        stConfigHead.usLength     = HOST_TO_NETWORK(usPapLen);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_HEAD_STRU);

        pTmpucSendMsg[ulSum] = CNAS_EHSM_CHAP_MD5_LEN;
        ulSum        = ulSum + sizeof(VOS_UINT8);

        if (0 == pstLocalPdnBearInfo->ucPwdLen)
        {
            CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: Incorrect Para");
            return CNAS_EHSM_FAILURE;
        }

        NAS_MEM_SET_S(aucAuthChapRespVal, sizeof(aucAuthChapRespVal), 0, sizeof(aucAuthChapRespVal));
        NAS_MEM_SET_S(&stMdCtx, sizeof(TAF_MSG_DIGEST_FIVE_CTX), 0, sizeof(TAF_MSG_DIGEST_FIVE_CTX));

        /* Msg Digest Five �㷨���� auth chap response value */
        TAF_InitMsgDigestFiveCtxt(&stMdCtx);
        TAF_UpdateMsgDigestFiveCtxt(&stMdCtx, &(stConfigHead.ucIdentifier), sizeof(VOS_UINT8));
        TAF_UpdateMsgDigestFiveCtxt(&stMdCtx, pstLocalPdnBearInfo->aucPwd, pstLocalPdnBearInfo->ucPwdLen);
#ifdef DMT
        TAF_UpdateMsgDigestFiveCtxt(&stMdCtx, aucDmtAuthChapChalVal, CNAS_EHSM_CHAP_CHALLENGE_LEN);
#else
        TAF_UpdateMsgDigestFiveCtxt(&stMdCtx, aucAuthChapChalVal, CNAS_EHSM_CHAP_CHALLENGE_LEN);
#endif
        TAF_EndMsgDigestFive(aucAuthChapRespVal, &stMdCtx);

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), aucAuthChapRespVal, CNAS_EHSM_CHAP_MD5_LEN);
        ulSum        = ulSum + CNAS_EHSM_CHAP_MD5_LEN;

        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), pstLocalPdnBearInfo->aucUserName, pstLocalPdnBearInfo->ucUserNameLen);
        ulSum        = ulSum + pstLocalPdnBearInfo->ucUserNameLen;
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_IPV4 == enPdnType)||(CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6 == enPdnType))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: Ipv4 DNS IPCP");

        /* Adding IPv4 DNS request to pco via IPCP */
        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_IPCP);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        usPapLen     = CNAS_EHSM_IPCP_REQ_ID_LEN;
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);

        NAS_MEM_SET_S(&stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        stConfigHead.ucCode       = CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_REQ;
        stConfigHead.ucIdentifier = CNAS_EHSM_IPCP_REQ_ID;
        stConfigHead.usLength     = HOST_TO_NETWORK(usPapLen);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stConfigHead, sizeof(CNAS_EHSM_CONFIG_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_HEAD_STRU);

        /* Primary ipv4 DNS server option */
        NAS_MEM_SET_S(&stCfgOptionHdr, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU));
        stCfgOptionHdr.uctype     = CNAS_EHSM_IPCP_OPTIONS_PRI_DNS_ADDR;
        stCfgOptionHdr.ucLength   = CNAS_EHSM_IPCP_PRIMARY_DNS_LEN;
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stCfgOptionHdr, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU);

        NAS_MEM_SET_S(&pTmpucSendMsg[ulSum], sizeof(VOS_UINT32), 0, sizeof(VOS_UINT32));
        ulSum        = ulSum + sizeof(VOS_UINT32);

        /* Secondary ipv4 DNS server option */
        NAS_MEM_SET_S(&stCfgOptionHdr, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU), 0, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU));
        stCfgOptionHdr.uctype     = CNAS_EHSM_IPCP_OPTIONS_SEC_DNS_ADDR;
        stCfgOptionHdr.ucLength   = CNAS_EHSM_IPCP_SECONDARY_DNS_LEN;
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &stCfgOptionHdr, sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU));
        ulSum        = ulSum + sizeof(CNAS_EHSM_CONFIG_OPTION_HEAD_STRU);

        NAS_MEM_SET_S(&pTmpucSendMsg[ulSum], sizeof(VOS_UINT32), 0, sizeof(VOS_UINT32));
        ulSum        = ulSum + sizeof(VOS_UINT32);

        /* Adding IPv4 DNS request to pco via Container */
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: Ipv4 DNS Container");

        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        usPapLen     = CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4_LEN;
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_IPV6 == enPdnType) || (CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6== enPdnType))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: Ipv6 DNS");

        /* Adding IPv4 DNS request to pco via IPCP */
        usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6);
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
        ulSum        = ulSum + sizeof(VOS_UINT16);

        usPapLen     = CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6_LEN;
        NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
        ulSum        = ulSum + sizeof(VOS_UINT8);
    }

    CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco: NAS SIGNALING");

    /* Adding IPv4 DNS request to pco via IPCP */
    usIdentifier = HOST_TO_NETWORK(CNAS_EHSM_PCO_ITEM_TYPE_NAS_SIGNALING);
    NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usIdentifier, sizeof(VOS_UINT16));
    ulSum        = ulSum + sizeof(VOS_UINT16);

    usPapLen     = CNAS_EHSM_PCO_ITEM_TYPE_NAS_SIGNALING_LEN;
    NAS_MEM_CPY_S(&pTmpucSendMsg[ulSum], (CNAS_CTTF_EHRPD_MAX_PCO_LEN - ulSum), &usPapLen, sizeof(VOS_UINT8));
    ulSum        = ulSum + sizeof(VOS_UINT8);

    if(ulSum <= CNAS_EHSM_MAX_PCO_BYTE)
    {
        *pulLength = ulSum;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco:WARNING:NAS->SM Message PCO Length slop over!");
        return CNAS_EHSM_FAILURE;
    }

    return CNAS_EHSM_SUCCESS;
}
/*****************************************************************************
 Function Name  : CNAS_EHSM_EncodeNwPDNValue()
 Description    : EHSMģ����װpdn address ��Ϣ����
 Input          : VOS_UINT8 *pucSendMsg,

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_EncodeNwPDNValue
(
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAdrrInfo,
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU   *pstSendMsg
)
{
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;

    pucTmpMsg        = pstSendMsg->aucAddress;

    /*����PDN��ַ����*/
    pstSendMsg->enPdnType = CNAS_EHSM_MapEhsmPdnTypeToCttf(pstPdnAdrrInfo->enPdnType);

    switch(pstPdnAdrrInfo->enPdnType)
    {
        /*�����IPV4���͵�ַ���򱣴棬IPV4��ַ��4���ֽ�*/
        case CNAS_EHSM_PDN_TYPE_IPV4:
            NAS_MEM_CPY_S(&pucTmpMsg[0], CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN, &(pstPdnAdrrInfo->aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            break;

        /*�����IPV6���͵�ַ���򱣴棬IPV4��ַ��16���ֽ�,����*/
        case CNAS_EHSM_PDN_TYPE_IPV6:
            /*���IPV6��ʽ�ĵ�ַ*/
            NAS_MEM_CPY_S(&pucTmpMsg[0], CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN, pstPdnAdrrInfo->aucIpv6Addr + CNAS_EHSM_IPV6_IF_OFFSET, CNAS_EHSM_IPV6_IF_LEN);
            break;

        /*���֧��IPV4��IPV6��ַ����λ���棬����*/
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
            /*���δ��IPV4��IPV6��ַ*/
            NAS_MEM_CPY_S(&pucTmpMsg[0], 
                          CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN, 
                          &(pstPdnAdrrInfo->aucIpv6Addr[0 + CNAS_EHSM_IPV6_IF_OFFSET]), 
                          CNAS_EHSM_IPV6_IF_LEN);
            NAS_MEM_CPY_S(&pucTmpMsg[0 + CNAS_EHSM_IPV6_IF_OFFSET], 
                          (CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN - CNAS_EHSM_IPV6_IF_OFFSET), 
                          &(pstPdnAdrrInfo->aucIpv4Addr[0]), 
                          CNAS_EHSM_IPV4_ADDR_LEN);
            break;
        default:
            NAS_MEM_SET_S(pstSendMsg->aucAddress, sizeof(pstSendMsg->aucAddress), 0, sizeof(pstSendMsg->aucAddress));
            break;
    }

    return CNAS_EHSM_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_EncodeApn
 ��������  : APN����
 �������  : CONST CNAS_EHSM_APN_STRU            *pstApn
             VOS_UINT8                           *pucApn
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��10��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_EHSM_EncodeApn(
    CONST CNAS_EHSM_APN_STRU           *pstApn,
    VOS_UINT8                          *pucApn,
    VOS_UINT8                          *pucApnLen
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucLenPosition;

    i               = 0;
    j               = 0;
    ucLenPosition   = 0;

    /*APN����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
    if (0 == pstApn->ucApnLen)
    {
        pucApn[0]   = 0;
        *pucApnLen  = 0;
        return;
    }

    for (i = 0; (i < pstApn->ucApnLen) && (i < CNAS_EHSM_MAX_APN_LEN ); i++)
    {
        /*�ӵ�0����Ч�ַ���ʼ���*/
        if (pstApn->aucApn[i] != '.')
        {
            /*�������Ч�ַ������俽��*/
            pucApn[i + 1] = pstApn->aucApn[i];
            /*��Ч�ַ�����1*/
            j++;
        }
        else
        {
            /*����ַ���'.'�����.��ǰ��Ч�ַ�������*/
            pucApn[ucLenPosition] = j;

            /*��ʼ��һ����Ч�ַ��εĳ����ۼ�*/
            j = 0;

            /*��һ����Ч�ַ��������λ��*/
            ucLenPosition = i + 1;
        }
    }

    /*������һ����Ч�ַ��ĳ���*/
    pucApn[ucLenPosition] = j;

    /*����APN�ĳ���*/
    *pucApnLen  = pstApn->ucApnLen + 1;
    return;
}

/*lint -restore*/

#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



