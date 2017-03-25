/************************************************************************
*                                                                      *
*                             Vsncp_encode.c                           *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2012/12/15                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��VSNCPģ�����Ա���                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������VSNCPЭ��ģ���ȫ���ӿں������ڲ�������            *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_ENCODE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_StrToAPNLabel
 ��������  : ��APN�ַ���ת��Ϊlabel
 �������  : UCHAR *pApnLabel, UCHAR *pApnStr
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_StrToAPNLabel(UCHAR *pApnLabel, UCHAR *pApnStr)
{
    UCHAR ucApnStrLen = 0;
    UCHAR i = 0;

    if ((VOS_NULL_PTR == pApnLabel) || (VOS_NULL_PTR == pApnStr))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    ucApnStrLen = (UCHAR)VOS_StrLen((VOS_CHAR *)pApnStr);
    if ((0 == ucApnStrLen) || (100 <= ucApnStrLen))
    {
        PPPC_WARNING_LOG1("ucApnStrLen ERR!\r\n", ucApnStrLen);

        return VOS_ERR;
    }

    if ('.' == *pApnStr)
    {
        PPPC_WARNING_LOG1((VOS_UINT8 *)("first is err!\r\n"), *pApnStr);
        return VOS_ERR;
    }

    for (i = 0; i <= ucApnStrLen; i++)
    {
        *(pApnLabel + i) = *(pApnStr + i);
    }
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_VSNCP_PDNIDEncode
 ��������  : PDN ID����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_PDNIDEncode(UCHAR *pucPacket,
                            PDN_CONTEXT_S *pstPDNContext,
                            VOS_UINT32 *pulLen,
                            PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDNID, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_PDNID_LEN, pucPacket);
    PPP_PUTCHAR(pstPDNContext->stEhrpd.ucPdnId, pucPacket);

    *pulLen = VSNCP_OPTION_PDNID_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_VSNCP_APNEncode
 ��������  : APN����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_APNEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          VOS_UINT32 *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucAPNLen = 0;
    VOS_UINT32 ulRet = 0;
    UCHAR *pucAPN = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* apn���� */
    ucAPNLen = pstPDNContext->stEhrpd.stApn.ucApnLen;
    if (ucAPNLen > M_CFG_MAX_APN_STRING_LEN)
    {
        ucAPNLen = M_CFG_MAX_APN_STRING_LEN;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_APN, pucPacket);
    /* ������Ҫ��һ��label�ĳ��� */
    PPP_PUTCHAR((ucAPNLen + VSNCP_CODE_ID_LEN), pucPacket);

    pucAPN = pstPDNContext->stEhrpd.stApn.aucApn;

    /* ת��Ϊlabel */
    ulRet = PPP_VSNCP_StrToAPNLabel(pucPacket, pucAPN);
    if (ulRet != VOS_OK)
    {
        return VOS_ERR;
    }

    *pulLen = (ucAPNLen + VSNCP_CODE_ID_LEN);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_VSNCP_PDNTypeEncode
 ��������  : PDNType����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_PDNTypeEncode(UCHAR *pucPacket,
                              PDN_CONTEXT_S *pstPDNContext,
                              VOS_UINT32 *pulLen,
                              PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPdnType = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }
    /*ucPdnType = ((pstPDNContext->ucPdnCapability) & (pstVsncpInfo->ucPdnType));*/
    ucPdnType = (UCHAR)(pstPDNContext->stEhrpd.enPdnType);

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_TYPE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_PDNTYPE_LEN, pucPacket);
    PPP_PUTCHAR(ucPdnType, pucPacket);

    *pulLen = VSNCP_OPTION_PDNTYPE_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}





/*****************************************************************************
 �� �� ��  : PPP_VSNCP_AttachTypeEncode
 ��������  : AttachType����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_AttachTypeEncode(UCHAR *pucPacket,
                                 PDN_CONTEXT_S *pstPDNContext,
                                 VOS_UINT32 *pulLen,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_ATTACH_TYPE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_ATTACHTYPE_LEN, pucPacket);
    /*PPP_PUTCHAR(pstVsncpInfo->ucAttchType, pucPacket);*/
    PPP_PUTCHAR(pstPDNContext->stEhrpd.enAttachType, pucPacket);

    *pulLen = VSNCP_OPTION_ATTACHTYPE_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_PDNAddressEncode
 ��������  : PDNAddress����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_PDNAddressEncode(UCHAR *pucPacket,
                                 PDN_CONTEXT_S *pstPDNContext,
                                 VOS_UINT32 *pulLen,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR                               ucLen = 1;   /* ��ʼ��Ϊ1 */
    UCHAR                               ucPdnType = 0;
    UCHAR                              *pucAddress = VOS_NULL_PTR;
    VOS_UINT8                          *pucLenPos;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }



    ucPdnType = (UCHAR)(pstPDNContext->stEhrpd.stPdnAddress.enPdnType);
    pucAddress = pstPDNContext->stEhrpd.stPdnAddress.aucAddress;

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_ADDR, pucPacket);
    pucLenPos = pucPacket;
    PPP_PUTCHAR((ucLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHAR(ucPdnType, pucPacket);

    if (CNAS_CTTF_EHRPD_ATTACH_TYPE_HANDOVER == pstPDNContext->stEhrpd.enAttachType)
    {
        if (VSNCP_OPTION_PDNTYPE_IPV4 == ucPdnType)
        {
            ucLen += VSNCP_OPTION_PDN_IPV4_LEN;
            PPP_PUTCHARPTR(pucAddress, pucPacket, VSNCP_OPTION_PDN_IPV4_LEN);
        }
        else if (VSNCP_OPTION_PDNTYPE_IPV6 == ucPdnType)
        {
            ucLen += VSNCP_OPTION_PDN_IPV6_LEN;
            PPP_PUTCHARPTR(pucAddress, pucPacket, VSNCP_OPTION_PDN_IPV6_LEN);
        }
        else
        {
            ucLen += (VSNCP_OPTION_PDN_IPV6_LEN + VSNCP_OPTION_PDN_IPV4_LEN);
            PPP_PUTCHARPTR(pucAddress, pucPacket, (VSNCP_OPTION_PDN_IPV6_LEN + VSNCP_OPTION_PDN_IPV4_LEN));
        }
    }

    /* ˢ�³��� */
    *pucLenPos = (ucLen + VSNCP_CODE_ID_LEN);
    *pulLen = (ucLen + VSNCP_CODE_ID_LEN);

    (VOS_VOID)pucPacket;
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_VSNCP_AddressAllocCauseEncode
 ��������  : AddressAllocCause����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_AddressAllocCauseEncode(UCHAR *pucPacket,
                                        PDN_CONTEXT_S *pstPDNContext,
                                        VOS_UINT32 *pulLen,
                                        PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPdnIndicatorCause = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    ucPdnIndicatorCause = pstPDNContext->stEhrpd.ucAddressAllocCause;

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN, pucPacket);
    PPP_PUTCHAR(ucPdnIndicatorCause, pucPacket);

    *pulLen = VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_VSNCP_PCOEncode
 ��������  : PCO����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_PCOEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          VOS_UINT32 *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPcoLen = 0;
    UCHAR *pucPco = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if (0 == pstPDNContext->stEhrpd.stPco.ucPcoLen)
    {
        PPPC_WARNING_LOG("ucPcoLen is 0!\r\n");
        *pulLen = 0;
        return VOS_OK;
    }

    ucPcoLen = pstPDNContext->stEhrpd.stPco.ucPcoLen;
    pucPco = pstPDNContext->stEhrpd.stPco.aucPco;

    if (ucPcoLen > VSNCP_OPTION_PCO_MAX_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1456);
        ucPcoLen = VSNCP_OPTION_PCO_MAX_LEN;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_PCO, pucPacket);
    PPP_PUTCHAR((ucPcoLen + VSNCP_CODE_ID_LEN), pucPacket);
    /*lint -e670*/
    PPP_PUTCHARPTR(pucPco, pucPacket, ucPcoLen);
    /*lint +e670*/
    *pulLen = (ucPcoLen + VSNCP_CODE_ID_LEN);

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_IPV4DefRouterEncode
 ��������  : IPV4DefRouter����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_IPV4DefRouterEncode(UCHAR *pucPacket,
                                    PDN_CONTEXT_S *pstPDNContext,
                                    VOS_UINT32 *pulLen,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_IPV4_DEFRTADDR, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_IPV4_DEFROUT_LEN, pucPacket);
    /*PPP_PUTADDR(pstPDNContext->stEhrpd.ulRouterAddrV4, pucPacket);*/

    PPP_PUTCHARPTR(pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress,
                   pucPacket, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    *pulLen = VSNCP_OPTION_IPV4_DEFROUT_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_IPV6LinkLocalEncode
 ��������  : IPV6LinkLocal����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_IPV6LinkLocalEncode(UCHAR *pucPacket,
                                    PDN_CONTEXT_S *pstPDNContext,
                                    VOS_UINT32 *pulLen,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_LINK_LOCAL_ADDR, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_IPV6_LINKLOCAL_LEN, pucPacket);
    PPP_PUTCHARPTR((pstPDNContext->stEhrpd.aucLinkLocalAddr + VSNCP_OPTION_PDN_IPV6_LEN),
                   pucPacket,
                   VSNCP_OPTION_PDN_IPV6_LEN);

    *pulLen = VSNCP_OPTION_IPV6_LINKLOCAL_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_GetAMBRLength
 ��������  : ��ȡAPMBR����
 �������  : VOS_UINT32 ulAMBR
 �������  : ��
 �� �� ֵ  : UCHAR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
UCHAR PPP_VSNCP_GetAMBRLength(VOS_UINT32 ulAMBR)
{
    VOS_UINT32 ulAmbrKbps = 0;
    UCHAR ucAMBRLen = 0;

    /* ת��ΪKBPS */
    ulAmbrKbps = ulAMBR/1000;

    if (ulAmbrKbps >= VSNCP_AMBR_256M_65280M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_3;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_130M_256M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_17M_128M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_8700K_16000K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_576K_8640K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_64K_568K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }

    return (UCHAR)((UCHAR)(ucAMBRLen * 2) + VSNCP_CODE_ID_LEN);
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_TransAMBR
 ��������  : AMBR ת��Ϊ 3�ֽ�
 �������  : VOS_UINT32 ulAMBR, UCHAR pucAMBR
 �������  : ��
 �� �� ֵ  : UCHAR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
UCHAR PPP_VSNCP_TransAMBR(VOS_UINT32 ulAMBR, UCHAR *pucAMBR)
{
    UCHAR ucOffset = 0;
    VOS_UINT32 ulAmbrKbps = 0;
    UCHAR ucAMBRLen = 0;
    VOS_UINT32 ulValueStart = 0;
    VOS_UINT32 ulValueStep = 0;
    UCHAR ucBitStart = 0;

    /* ת��ΪKBPS */
    ulAmbrKbps = ulAMBR/1000;

    /* ���AAA�·�Ϊ0����Я��ΪȫF */
    if (0 == ulAmbrKbps)
    {
        pucAMBR[ucOffset] = VSNCP_AMBR_ZERO;
        return VSNCP_AMBR_LEN_1;
    }

    if (ulAmbrKbps >= VSNCP_AMBR_256M_65280M_START)
    {
        ulValueStart = VSNCP_AMBR_256M_65280M_START;
        ulValueStep = VSNCP_AMBR_256M_65280M_STEP;
        ucBitStart = VSNCP_AMBR_256M_65280M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_3;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_256M_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_130M_256M_START)
    {
        ulValueStart = VSNCP_AMBR_130M_256M_START;
        ulValueStep = VSNCP_AMBR_130M_256M_STEP;
        ucBitStart = VSNCP_AMBR_130M_256M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_17M_128M_START)
    {
        if (ulAmbrKbps > VSNCP_AMBR_17M_128M_END)
        {
            ulAmbrKbps = VSNCP_AMBR_17M_128M_END;
        }
        ulValueStart = VSNCP_AMBR_17M_128M_START;
        ulValueStep = VSNCP_AMBR_17M_128M_STEP;
        ucBitStart = VSNCP_AMBR_17M_128M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_8700K_16000K_START)
    {
        if (ulAmbrKbps > VSNCP_AMBR_8700K_16000K_END)
        {
            ulAmbrKbps = VSNCP_AMBR_8700K_16000K_END;
        }
        ulValueStart = VSNCP_AMBR_8700K_16000K_START;
        ulValueStep = VSNCP_AMBR_8700K_16000K_STEP;
        ucBitStart = VSNCP_AMBR_8700K_16000K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_576K_8640K_START)
    {
        ulValueStart = VSNCP_AMBR_576K_8640K_START;
        ulValueStep = VSNCP_AMBR_576K_8640K_STEP;
        ucBitStart = VSNCP_AMBR_576K_8640K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_64K_568K_START)
    {
        ulValueStart = VSNCP_AMBR_64K_568K_START;
        ulValueStep = VSNCP_AMBR_64K_568K_STEP;
        ucBitStart = VSNCP_AMBR_64K_568K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else
    {
        ulValueStart = VSNCP_AMBR_1K_63K_START;
        ulValueStep = VSNCP_AMBR_1K_63K_STEP;
        ucBitStart = VSNCP_AMBR_1K_63K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }

    *(pucAMBR + ucOffset) = ucBitStart + (UCHAR)((ulAmbrKbps - ulValueStart) / ulValueStep);

    return ucAMBRLen;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_AmbrEncode
 ��������  : Ambr����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : t00265288
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_AmbrEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          VOS_UINT32 *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)

{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if (0 == pstVsncpInfo->ucAMBRLen)
    {
        PPPC_WARNING_LOG("ucAMBRLen is 0!\r\n");
        *pulLen = 0;
        return VOS_OK;
    }

    /* ���浽��Ϣ�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_APN_AMBR, pucPacket);
    PPP_PUTCHAR((pstVsncpInfo->ucAMBRLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHARPTR(pstVsncpInfo->aucAMBR, pucPacket, pstVsncpInfo->ucAMBRLen);

    *pulLen = pstVsncpInfo->ucAMBRLen + VSNCP_CODE_ID_LEN;

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_DefAPNIndEncode
 ��������  : DefAPNInd����
 �������  : UCHAR *pucPacket,
             PDN_CONTEXT_S *pstPDNContext
             VOS_UINT32 *pulLen
             PDN_PPP_VSNCP_REQ_S *pstVsncpInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_VSNCP_DefAPNIndEncode(UCHAR *pucPacket,
                                PDN_CONTEXT_S *pstPDNContext,
                                VOS_UINT32 *pulLen,
                                PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucDefAPNInd = VSNCP_OPTION_NOT_DEF_APN;
    VOS_UINT32 ulRet = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if ('\0' == pstVsncpInfo->szApn[0])
    {
        /* �Ƿ���default apn */
        ulRet = USM_IsDefaultApn(pstPDNContext->ulRpIndex, pstPDNContext->stEhrpd.usApnIndex);
        if (VOS_TRUE == ulRet)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1457);
            ucDefAPNInd = VSNCP_OPTION_DEF_APN;
            /* ���浽��Ϣ�� */
            PPP_PUTCHAR(PPP_VSNCP_CO_DEFAULT_APN_IND, pucPacket);
            PPP_PUTCHAR(VSNCP_OPTION_DEF_APN_IND_LEN, pucPacket);
            PPP_PUTCHAR(ucDefAPNInd, pucPacket);
            *pulLen = VSNCP_OPTION_DEF_APN_IND_LEN;
        }
    }

    (VOS_VOID)pucPacket;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_VSNCP_OptionEncodeReg
 ��������  : vsncp���Ա��뺯��ע��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : wangyong 00138171
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_VSNCP_OptionEncodeReg(VOS_VOID)
{
    /* vsncp option���뺯��ע�� */
    /*lint -e63*/
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDNID, PPP_VSNCP_PDNIDEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_APN, PPP_VSNCP_APNEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_TYPE, PPP_VSNCP_PDNTypeEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_ADDR, PPP_VSNCP_PDNAddressEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_PCO, PPP_VSNCP_PCOEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_IPV4_DEFRTADDR, PPP_VSNCP_IPV4DefRouterEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE, PPP_VSNCP_AddressAllocCauseEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_LINK_LOCAL_ADDR, PPP_VSNCP_IPV6LinkLocalEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_APN_AMBR, PPP_VSNCP_AmbrEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_DEFAULT_APN_IND, PPP_VSNCP_DefAPNIndEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_ATTACH_TYPE, PPP_VSNCP_AttachTypeEncode);
    /*lint +e63*/
    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
