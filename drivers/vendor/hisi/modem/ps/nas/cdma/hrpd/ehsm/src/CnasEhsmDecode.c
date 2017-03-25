/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmDecode.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :EHSM module to deccode.
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
#include "CnasEhsmDecode.h"
#include "CnasEhsmComFunc.h"
#include "CnasEhsmEncode.h"
#include "CnasEhsmDecode.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
#if 1
#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_DECODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Item
 Description     : ����PCO��Ԫ�е�IP���P-CSCF IPV4 ADDRESS��P-CSCF IPV6
                   ADDRESS��DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == CNAS_EHSM_IPV4_ADDR_LEN)
    {
        NAS_MEM_CPY_S(pstIpAddr->aucIpV4Addr,
                      CNAS_EHSM_IPV4_ADDR_LEN,
                      &pucMsg[ulSum],
                      CNAS_EHSM_IPV4_ADDR_LEN);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoIpv4Item:IP address length is illegal");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Item
 Description     : ����PCO��Ԫ�е�IP���P-CSCF IPV6 ADDRESS��DNS SERVER IPV6 ADDRESS
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == CNAS_EHSM_IPV6_ADDR_LEN)
    {
        NAS_MEM_CPY_S(pstIpAddr->aucIpV6Addr,
                      CNAS_EHSM_IPV6_ADDR_LEN,
                      &pucMsg[ulSum],
                      CNAS_EHSM_IPV6_ADDR_LEN);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoIpv6Item:IP address length is illegal");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Dns
 Description     : ����PCO��Ԫ�е�IPV6 DNS SERVER
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* DNS SERVER�洢���������������� */
    if (pstPco->ucIpv6DnsSerNum >= CNAS_EHSM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum = *pulSum + ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv6Item( &pucTmpMsg[ulSum],
                                            &pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* �����ȡ��IPv6 DNS����Ϊȫ�㣬���������޴�DNS��������DNS���� */
        if (PS_MEM_CMP(&pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum],
                            pstEmptyIpv6Addr,
                            sizeof(CNAS_EHSM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);

    *pulSum = *pulSum + ulSum;

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Dns
 Description     : ����PCO��Ԫ�е�IPV4 DNS SERVER
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* DNS SERVER�洢���������������� */
    if (pstPco->ucIpv4DnsSerNum >= CNAS_EHSM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* �����ȡ��IPv4 DNS����Ϊȫ�㣬���������޴�DNS��������DNS���� */
        if (PS_MEM_CMP(&pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum],
                            pstEmptyIpv4Addr,
                            sizeof(CNAS_EHSM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Pcscf
 Description     : ����PCO��Ԫ�е�IPV4 P-CSCF
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Pcscf
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* P-CSCF�洢���������������� */
    if (pstPco->ucIpv4PcscfNum >= CNAS_EHSM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* �����ȡ��IPv4 P-CSCF����Ϊȫ�㣬���������޴�P-CSCF��������P-CSCF���� */
        if (PS_MEM_CMP(&pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum],
                            pstEmptyIpv4Addr,
                            sizeof(CNAS_EHSM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Pcscf
 Description     : ����PCO��Ԫ�е�IPV6 P-CSCF
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Pcscf
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* P-CSCF�洢���������������� */
    if (pstPco->ucIpv6PcscfNum >= CNAS_EHSM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv6Item(&pucTmpMsg[ulSum], &pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* �����ȡ��IPv4 P-CSCF����Ϊȫ�㣬���������޴�P-CSCF��������P-CSCF���� */
        if (PS_MEM_CMP(&pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum],
                            pstEmptyIpv6Addr,
                            sizeof(CNAS_EHSM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Pcscf
 Description     : ����PCO��Ԫ�е�IPV6 P-CSCF
                   ��
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeLocalAddress
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum
)
{
    VOS_UINT32                          ulSum;

    ulSum               = 0;

    /* ������������ */
    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);

    *pulSum += ulSum;

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoBcm
 Description     : ����PCO��Ԫ�е�BCM
 Input           : pucMsg
 Output          : pstPco
 Return          : VOS_VOID

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_EHSM_DecodePcoBcm
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    /* Э��涨BCM�����ݳ���Ϊ1������Ϊ1������Դ��� */
    if (1 != ucItemLen)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoBcm:BCM len illegal!");
        return ;
    }

    /* Э��涨BCM�ĺϷ�ֵΪSM_ESM_BCM_MS_ONLY��SM_ESM_BCM_MS_NW */

    pstPco->enBcm       = pucMsg[ulSum];
    pstPco->bitOpBcm    = CNAS_EHSM_OP_TRUE;
}


/*****************************************************************************
 Function Name   : CNAS_EHSM_ValidatePcoLen
 Description     : �ж�IPCP��Ԫ���ȵĺϷ���
 Input           : pucMsg       -- �տ���Ϣ����
                   ucIpcpLength -- IPCP�ṹ����
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���
*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidateIpcpLen
(
     VOS_UINT8                         *pucMsg
)
{
    VOS_UINT8                           ucTmpLength;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucSum;

    pucTmpMsg           = pucMsg;
    ucTmpLength = 0;
    ucSum     = 0;

    /* ��ȡ�ܳ��� */
    ucTmpLength |= (VOS_UINT8)((pucTmpMsg[2] << 8));
    ucTmpLength |= pucTmpMsg[3];

    /* �ж��Ƿ���Զ�ȡ���� */
    if (ucTmpLength < (ucSum + CNAS_EHSM_IPCP_PACKET_HEAD_LEN))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP length is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* ����IPCP��ͷ���� */
    ucSum += CNAS_EHSM_IPCP_PACKET_HEAD_LEN;

    /* ͳ�����еĳ��� */
    while (ucTmpLength > ucSum)
    {
#if 0
        /* �ж��Ƿ���Զ�ȡ���� */
        if (ucTmpLength < ((ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) - 1))
        {
            CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP Opt length is illegal!");

            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
        }
#endif
        /* �жϳ��Ȳ���Ϊ0��������ѭ�� */
        if (0 == pucTmpMsg[(ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) - 1])
        {
            CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP Opt length is 0!");

            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
        }
        ucSum += pucTmpMsg[(ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) -1];
    }

    /* �ж��ܳ����Ƿ���� */
    if (ucTmpLength != ucSum)
    {
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_CheckIpAddrIsEmpty
 Description     : ���IP��ַ�Ƿ�Ϊ��
 Input           :
 Output          : None
 Return          : BOOL

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/

VOS_UINT8 CNAS_EHSM_CheckIpv4AddrIsEmpty( CNAS_EHSM_IPV4_ADDR_STRU *pstIpAddr)
{
    if ( (0 == pstIpAddr->aucIpV4Addr[0])
        && (0 == pstIpAddr->aucIpV4Addr[1])
        && (0 == pstIpAddr->aucIpV4Addr[2])
        && (0 == pstIpAddr->aucIpV4Addr[3]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
/*****************************************************************************
 Function Name   : CNAS_EHSM_OptimizeDnsServer
 Description     : �������DNS
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_EHSM_OptimizeDnsServer
(
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    VOS_UINT8                           ucPriDnsNoExist;
    VOS_UINT8                           ucSecDnsNoExist;

    ucPriDnsNoExist = VOS_TRUE;
    ucSecDnsNoExist = VOS_TRUE;

    ucPriDnsNoExist = CNAS_EHSM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[0]));
    ucSecDnsNoExist = CNAS_EHSM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[1]));

    if ((VOS_TRUE == ucPriDnsNoExist) && (VOS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        NAS_MEM_CPY_S((VOS_VOID*)&(pstPco->astIpv4DnsServer[0]),
                      sizeof(CNAS_EHSM_IPV4_ADDR_STRU),
                      (VOS_VOID*)&(pstPco->astIpv4DnsServer[1]),
                      sizeof(CNAS_EHSM_IPV4_ADDR_STRU));
        return;
    }

    if ((VOS_FALSE == ucPriDnsNoExist) && (VOS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        return;
    }

    if ((VOS_TRUE == ucPriDnsNoExist) && (VOS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 0;
        return;
    }

    if ((VOS_FALSE == ucPriDnsNoExist) && (VOS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 2;
        return;
    }

}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeIpcpOptionContent
 Description     : ����IPCP Option����
 Input           :
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
      1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeIpcpOptionContent
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
     VOS_UINT8                         *pucTmpMsg = VOS_NULL_PTR;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enRslt;
    VOS_UINT32                          ulOptionLen;
    VOS_UINT32                          ulTempSum;

    ulTempSum = *pulSum;
    ulOptionLen = 0;
    pucTmpMsg           = pucMsg;

    CNAS_INFO_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:configure-type:", pucMsg[*pulSum]);

    /* ��鵱ǰ�Ŀ�ѡ���ܳ�����ȷ */
    enRslt = CNAS_EHSM_ValidateIpcpLen(pucMsg + ulTempSum);
    if (CNAS_EHSM_CAUSE_SUCCESS != enRslt)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpOptionContent:Lenth is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }


    /*�����IPCP option���� */
    ulOptionLen |= (VOS_UINT8)((pucTmpMsg[ulTempSum + 2] << 8));
    ulOptionLen |= pucTmpMsg[ulTempSum + 3];


    /* ����ͷ���ṹ */
    ulTempSum += CNAS_EHSM_IPCP_PACKET_HEAD_LEN;

    while (ulTempSum < (*pulSum + ulOptionLen))
    {
        switch (pucTmpMsg[ulTempSum])
        {
            /* ������DNS Server��Ϣ */
            case CNAS_EHSM_IPCP_OPTIONS_PRI_DNS_ADDR:

                /*����type�ֽ�*/
                ulTempSum++;

                /* �жϳ����Ƿ�Ϸ� */
                if (CNAS_EHSM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:DNS Lenth is illegal!");
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /*����length�ֽ�*/
                ulTempSum++;

                NAS_MEM_CPY_S((VOS_VOID*)pstPco->astIpv4DnsServer[0].aucIpV4Addr,
                              CNAS_EHSM_IPV4_ADDR_LEN,
                              (VOS_VOID*)&pucTmpMsg[ulTempSum],
                              CNAS_EHSM_IPV4_ADDR_LEN);


                /* ����IP��ַ */
                ulTempSum += CNAS_EHSM_IPV4_ADDR_LEN;

                break;


            case CNAS_EHSM_IPCP_OPTIONS_SEC_DNS_ADDR:

                /*����type�ֽ�*/
                ulTempSum++;

                /* �жϳ����Ƿ�Ϸ� */
                if (CNAS_EHSM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:DNS Lenth is illegal!");
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /*����length�ֽ�*/
                ulTempSum++;

                NAS_MEM_CPY_S((VOS_VOID*)pstPco->astIpv4DnsServer[1].aucIpV4Addr,
                              CNAS_EHSM_IPV4_ADDR_LEN,
                              (VOS_VOID*)&pucTmpMsg[ulTempSum],
                              CNAS_EHSM_IPV4_ADDR_LEN);


                /* ����IP��ַ */
                ulTempSum += CNAS_EHSM_IPV4_ADDR_LEN;

                break;

            default:
                /* �жϳ��Ȳ���Ϊ0��������ѭ�� */
                if (0 == pucTmpMsg[ulTempSum + 1])
                {
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /* ������Ԫ���� */
                ulTempSum += pucTmpMsg[ulTempSum + 1];

                break;
        }
    }
    *pulSum = ulTempSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeIpcpContent
 Description     : ����IPCP������
IPCP
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Options ...
+-+-+-+-+

IP:
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |           IP-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         IP-Address (cont)       |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Primary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Primary-NBNS-Address (cont)  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

NBNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Secondary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Secondary-NBNS-Address (cont) |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeIpcpContent
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    CNAS_EHSM_CAUSE_ENUM_UINT8          enRslt;
    VOS_UINT8                           ucTmpLength;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;

    enRslt              = CNAS_EHSM_CAUSE_ERROR;
    ucTmpLength         = 0;
    ulSum               = 0;
    pucTmpMsg           = pucMsg;

    /* ��ȡlength�� */
    ucTmpLength = pucTmpMsg[ulSum++];

#if 0
    /* �ж������Ƿ�ΪCONFIGURE_NAK,Ϊ��ǿ���������,�ɽ���NAK/ACK/REJ/REQ*/
    if(pucTmpMsg[ulSum] != CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_NAK)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:code is illegal!");
    }
#endif

    /* �ж��ܳ����Ƿ�Ϸ� */
    if (ucTmpLength < CNAS_EHSM_IPCP_PACKET_HEAD_LEN)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:IPCP length is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    while (ucTmpLength > (ulSum -1))
    {
        enRslt = CNAS_EHSM_DecodeIpcpOptionContent(pucTmpMsg, &ulSum, pstPco);
        if (CNAS_EHSM_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_ValidatePcoLen
 Description     : �ж�PCO��Ԫ���ȵĺϷ���
 Input           : pucMsg      -- �տ���Ϣ����
                   ucPcoLength -- PCO�ṹ����
 Output          : usDecodeLen -- Ҫ����ĳ���
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidatePcoLen
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucPcoLength,
    VOS_UINT16                         *pusDecodeLen
)
{
    VOS_UINT8                           ucAllPcoLength;
    VOS_UINT8                           ucPrePcoLength;
    VOS_UINT8                          *pTmp = VOS_NULL_PTR;
    VOS_UINT8                          *pucTemp = VOS_NULL_PTR;

    ucAllPcoLength  = 0;
    ucPrePcoLength  = 0;
    pTmp            = pucMsg;
    pucTemp         = VOS_NULL_PTR;
    /* ���PCO����Ϊ0���򷵻�ʧ�� */
    if (0 == ucPcoLength)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidatePcoLen:Pco length is 0!");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* ���PCO��Ԫֻ��������Э����򷵻سɹ� */
    if (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL == ucPcoLength)
    {
        *pusDecodeLen = CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    /* �жϳ����Ƿ�Ϸ� */
    if(ucPcoLength < (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL + CNAS_EHSM_SUM_LEN_OF_ID_LEN))
    {
         CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidatePcoLen:Pco length is between (1,4)!");
         return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    pucTemp = &(pTmp[CNAS_EHSM_PCO_ITEM_LEN_OFFSET]);

    /* ��ȡ����packet filter��ռ���ֽ��� */
    ucPrePcoLength = pTmp[CNAS_EHSM_PCO_ITEM_LEN_OFFSET];
    ucAllPcoLength = ucPrePcoLength + (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL
                                                    + CNAS_EHSM_SUM_LEN_OF_ID_LEN);
    /*���˴�����Ϊ�ɽ����ĳ���Ϊ1����������CONFIGURATION PROTOCOL*/
    *pusDecodeLen = CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;

    while (ucPcoLength >= ucAllPcoLength)
    {
         *pusDecodeLen = ucAllPcoLength;
         /* �жϳ����Ƿ�Ϸ� */
         if ((ucAllPcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN) > ucPcoLength)
         {
             break;
         }

         /* �ۼ���һ��ĳ��� */
         ucAllPcoLength =   ucAllPcoLength +
                            pucTemp[ucPrePcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN]
                            + CNAS_EHSM_SUM_LEN_OF_ID_LEN;

         /* ��ָ��ָ����һ��ĳ�����Ԫ��λ�� */
         pucTemp = &(pucTemp[ucPrePcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN]);

         /* ������һ��ĳ�����Ԫ��ֵ */
         ucPrePcoLength = *pucTemp;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoContent
 Description     : ����PCO����
 Input           : pucMsg---------------------�տ���Ϣ����
                   pstMsgIE-------------------�����Ŀտ���Ϣ
 Output          : pulIndex-------------------�˺����������Ϣ����ָ��
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoContent
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco = VOS_NULL_PTR;
    VOS_UINT16                          usPcoItemId;
    CNAS_EHSM_IPV6_ADDR_STRU            stEmptyIpv6Addr;
    CNAS_EHSM_IPV4_ADDR_STRU            stEmptyIpv4Addr;

    ulSum               = 0;
    pucTmpMsg           = pucMsg;
    pstPco              = pstMsgIE;
    usPcoItemId         = 0;

    NAS_MEM_SET_S(&stEmptyIpv6Addr, sizeof(CNAS_EHSM_IPV6_ADDR_STRU), 0, sizeof(CNAS_EHSM_IPV6_ADDR_STRU));
    NAS_MEM_SET_S(&stEmptyIpv4Addr, sizeof(CNAS_EHSM_IPV4_ADDR_STRU), 0, sizeof(CNAS_EHSM_IPV4_ADDR_STRU));
    /* ���PCO�����ѹرգ���ֱ������PCO���ݲ����سɹ� */
#if 0
    if (CNAS_EHSM_PCO_OFF  == CNAS_EHSM_GetPcoFlag())
    {
        CNAS_EHSM_NORM_LOG("CNAS_EHSM_DecodePcoContent:PCO fuction is closed!");

        return CNAS_EHSM_SUCCESS;
    }
#endif
    /* �ж�PCOЯ����Э���Ƿ���ȷ */
    if (CNAS_EHSM_PCO_CONFIG_PROTOCOL != (pucTmpMsg[ulSum++] & CNAS_EHSM_HIGH_5_BIT_MASK))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoContent:Pco Configaration Proctocol error!");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* ��һ����PCO��Я���ĸ������� */
    while (usMsgLen > ulSum)
    {
        usPcoItemId = ((VOS_UINT16)pucTmpMsg[ulSum++] << CNAS_EHSM_MOVEMENT_8_BITS);
        usPcoItemId = usPcoItemId | (pucTmpMsg[ulSum++]);

        switch (usPcoItemId)
        {
            case CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6:
                CNAS_EHSM_DecodePcoIpv6Dns(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum,
                                                    &stEmptyIpv6Addr);
                break;
            case CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV4:

                CNAS_EHSM_DecodePcoIpv4Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                break;
            case CNAS_EHSM_PCO_ITEM_TYPE_BCM:
                CNAS_EHSM_DecodePcoBcm(&pucTmpMsg[ulSum], pstPco);
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4:

                CNAS_EHSM_DecodePcoIpv4Dns(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_IPCP:
                /*LV��ʽ����*/
                (VOS_VOID)CNAS_EHSM_DecodeIpcpContent(&pucTmpMsg[ulSum],pstPco);
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV6:

                CNAS_EHSM_DecodePcoIpv6Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv6Addr);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG:
                pstPco->bitOpImsCnSignalFlag = CNAS_EHSM_OP_TRUE;
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_LOCAL_ADDRESS:
                (VOS_VOID)CNAS_EHSM_DecodeLocalAddress(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum);
                break;

            default:
                /* ������������ */
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;
        }
    }
    /*���µ���DNS */
    CNAS_EHSM_OptimizeDnsServer(pstPco);

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name  : CNAS_EHSM_DecodePco()
 Description    : SMģ�����PCO��Ϣ
 Input          :

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
/*lint -e415 -e416 -e661 -e662*/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePco
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
)
{
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;
    VOS_UINT16                          usDecodeLen;

    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;
    /*��ӡ����ú���*/
    CNAS_INFO_LOG(UEPS_PID_EHSM,   "CNAS_EHSM_DecodePco is entered");

    enEhsmCause = CNAS_EHSM_ValidatePcoLen(pucMsg,(VOS_UINT8)usMsgLen,&usDecodeLen);
    if (CNAS_EHSM_CAUSE_SUCCESS != enEhsmCause)
    {
        /*������Ϣ���ʧ��*/
        CNAS_INFO_LOG(UEPS_PID_EHSM,  "CNAS_EHSM_DecodeNwPco:CNAS_EHSM_ValidatePcoLen failed!");
        return enEhsmCause;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoContent(usDecodeLen, pucMsg, pstMsgIE);
    if (CNAS_EHSM_CAUSE_SUCCESS != enEhsmCause)
    {
        return enEhsmCause;
    }


    return CNAS_EHSM_CAUSE_SUCCESS;
}/*lint +e415 +e416 +e661 +e662*/

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeNwPDNValue
 Description     : PDN��ַ����
 Input           :VOS_UINT16             usMsgLen
                VOS_UINT8             *pucMsg
                CNAS_EHSM_NW_MSG_STRU   *pstMsgIE
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.��    ��    : 2015��6��8��
    ��    ��    : f00279542
    �޸�����    : �����ɺ���

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeNwPDNValue
(
    VOS_UINT16                          usMsgLen,
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_PDN_ADDR_STRU            *pstMsgIE
)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    CNAS_EHSM_PDN_ADDR_STRU            *pstPDNInfo;

    ulSum            = 0;
    pucTmpMsg        = pucMsg;
    pstPDNInfo       = pstMsgIE;

    /*�ж�PDN ADDRESS���ݳ����Ƿ����Э��淶��Ŀǰֻ����IPV4�ĵ�ַ*/

    /*�ڴ�ռ��ʼ��*/
    NAS_MEM_SET_S((VOS_VOID*)pstPDNInfo, sizeof(CNAS_EHSM_PDN_ADDR_STRU), 0, sizeof(CNAS_EHSM_PDN_ADDR_STRU));

    /*����PDN��ַ����*/
    pstPDNInfo->enPdnType = pucTmpMsg[ulSum++];

    /* jump three pad */
    ulSum += 3;

    switch(pstPDNInfo->enPdnType)
    {
        /*�����IPV4���͵�ַ���򱣴棬IPV4��ַ��4���ֽ�*/
        case CNAS_EHSM_PDN_TYPE_IPV4:
            NAS_MEM_CPY_S(pstPDNInfo->aucIpv4Addr, CNAS_EHSM_IPV4_ADDR_LEN, &pucTmpMsg[ulSum], CNAS_EHSM_IPV4_ADDR_LEN);
            break;

        /*�����IPV6���͵�ַ���򱣴棬IPV4��ַ��16���ֽ�,����*/
        case CNAS_EHSM_PDN_TYPE_IPV6:
            /*���IPV6��ʽ�ĵ�ַ*/
            NAS_MEM_CPY_S((pstPDNInfo->aucIpv6Addr + CNAS_EHSM_IPV6_IF_OFFSET),  
                          (CNAS_EHSM_IPV6_ADDR_LEN - CNAS_EHSM_IPV6_IF_OFFSET),
                          &pucTmpMsg[ulSum], 
                          CNAS_EHSM_IPV6_IF_LEN);
            break;

        /*���֧��IPV4��IPV6��ַ����λ���棬����*/
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
            /*���δ��IPV4��IPV6��ַ*/
            NAS_MEM_CPY_S((pstPDNInfo->aucIpv6Addr + CNAS_EHSM_IPV6_IF_OFFSET),
                          (CNAS_EHSM_IPV6_ADDR_LEN - CNAS_EHSM_IPV6_IF_OFFSET),
                          &pucTmpMsg[ulSum], 
                          CNAS_EHSM_IPV6_IF_LEN);
            NAS_MEM_CPY_S(pstPDNInfo->aucIpv4Addr, CNAS_EHSM_IPV4_ADDR_LEN, &pucTmpMsg[ulSum+CNAS_EHSM_IPV6_IF_LEN], CNAS_EHSM_IPV4_ADDR_LEN);

            break;
        default:
            CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeEsmPDN:WARNING:NW->SM Invalid mandatory information1!");
            NAS_MEM_SET_S((VOS_VOID*)pstPDNInfo, sizeof(CNAS_EHSM_PDN_ADDR_STRU), 0, sizeof(CNAS_EHSM_PDN_ADDR_STRU));
            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*lint -restore*/

#endif /* FEATURE_UE_MODE_CDMA */
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



