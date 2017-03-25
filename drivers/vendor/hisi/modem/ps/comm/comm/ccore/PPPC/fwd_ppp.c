/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : fwd_ppp.c
  �� �� ��   : ����
  ��    ��   : zhangnan 68158
  ��������   : 2007��07��19��
  ����޸�   :
  ��������   : PPPģ�鴦����
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2007��07��14��
    ��    ��   : zhangnan 68158
    �޸�����   : �����ļ�

 2.��    ��  : 2007-07-23
    ��    ��  :zhangna 68158
    ��    ��  :���Э�鱨�����͵ķ�װ

 3.��    ��  : 2007-07-30
    ��    ��  :zhangna 68158
    ��    ��  �޸ĺ������

 4.��    ��  : 2007-08-02
    ��    ��  :zhangnan 68158
    ��    ��  ��װ������Ϣͷʱ,ʹ�����¶���� ENCAP_TOCP_INFO_S�ṹ����ʾ��װ�ĳ���,���ڸ���MBUF
                �¶�������ʱ���� ENCAP_TOCP_INFO_S *pstEncapHd ����ָ���װ��Ϣͷ,���� " ��װ��Ϣͷ�� " �еļ���
                ��װװ����Ϣͷ�����������ʽ
 5.��    ��  : 2008-01-29
    ��    ��  :zhangnan 68158
    ��    ��  :��������ֻ���ؽ������������������ô�ͳһ��������һ������ֵ��ʾͬ�����ģ�����������Ƿ���
 6.��    ��  : 2008-02-15
    ��    ��  :zhangnan 68158
    ��    ��  :�޸Ļ�ȡGTPU���ֶεĺ꣬�Ż�Ϊֻ��һ�����������ټ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "PppInterface.h"
#include "fwd_ppp_private.h"
#include "pppc_ctrl.h"
#include "fwd_ppp.h"
#include "TTFMem.h"
#include "TTFLink.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_FWD_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
PPP_REBUILD_INCOMPLETE_SLICE_STRU   g_stPppRebuildIncompleteSliceStat = {0};
VOS_UINT8                           g_aucPppRebuildSynSliceBuffer[3600];
VOS_UINT16                          g_usPppSynSliceBufUsedLen = 0;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : FWD_PppFillDataInfo
 ��������  : ��д��Ҫ��ȡ������
 �������  : pstIP: ԭʼ���ݵ�ip��Ϣָ��
             pstUlDataInfo: ��ȡ�����ݵ�ָ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-23
    ��    ��   : d00314740
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID FWD_PppFillDataInfo
(
    VOS_UINT8                          *pucPppData,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    IP4_S                              *pstIp;
    VOS_UINT8                           ucIpHdLen;
    VOS_UINT32                          ulProtocol;
    VOS_UINT8                           ucIcmpType;
    VOS_UINT32                          ulIcmpOtherHd;

    if ((VOS_NULL_PTR == pucPppData) || (VOS_NULL_PTR == pstUlDataInfo))
    {
        PPPC_WARNING_LOG("null ptr when fill high layer data info");
        return;
    }

    pstIp       = (IP4_S *)pucPppData;
    ucIpHdLen   = pstIp->ip_chHLen * 4;
    ulProtocol  = pstIp->ip_chPr;

    PS_MEM_SET(pstUlDataInfo, 0x0, sizeof(PS_DATA_EXT_INFO_STRU));

    /* �����Ż�����ȡtrace.
        ucPri, ulBirthTime ��δʹ��
        R���� usStartSN, usEndSN ��rrlp ��д
        F���� usStartSN, usEndSN ��ppp ��д*/
    pstUlDataInfo->enDataType   = (IPV4_VERSION == pstIp->ip_chVer) ?
        (PS_DATA_FLOW_TYPE_IPV4_PACKET) : (PS_DATA_FLOW_TYPE_IPV6_PACKET);

    if ((PS_DATA_HIGH_LAYER_TCP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_UDP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_ICMP_TYPE != ulProtocol)
        && (PS_DATA_HIGH_LAYER_ICMPV6_TYPE) != ulProtocol)
    {
        ulProtocol  = (IPV4_VERSION == pstIp->ip_chVer) ?
            (PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE) : (PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE);
    }

    pstUlDataInfo->stHighLayerInfo.ulChoice = ulProtocol;

    switch (ulProtocol)
    {
        case PS_DATA_HIGH_LAYER_TCP_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usIpId           = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usDataLen        = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usSrcPort
                = VOS_NTOHS(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->usSrcPort);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.usDstPort
                = VOS_NTOHS(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->usDstPort);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.ulAckSeq
                = VOS_NTOHL(((PPP_TRACE_TCP4_STRU *)(pucPppData + ucIpHdLen))->ulAck);
            pstUlDataInfo->stHighLayerInfo.u.stTcpInfo.enIncludeHttp    = PS_FALSE;
            break;
        case PS_DATA_HIGH_LAYER_UDP_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usIpId           = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usDataLen        = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usSrcPort
                = VOS_NTOHS(((PPP_TRACE_UDP4_STRU *)(pucPppData + ucIpHdLen))->usSrcPort);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.usDstPort
                = VOS_NTOHS(((PPP_TRACE_UDP4_STRU *)(pucPppData + ucIpHdLen))->usDstPort);
            pstUlDataInfo->stHighLayerInfo.u.stUdpInfo.enIncludeDns     = PS_FALSE;
            break;
        case PS_DATA_HIGH_LAYER_ICMP_TYPE:
            ucIcmpType    = ((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ucType;
            ulIcmpOtherHd = VOS_NTOHL(((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ulOtherHd);

            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIpId        = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usDataLen     = VOS_NTOHS(pstIp->ip_usLen);
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.ucType        = ucIcmpType;
            if ((ICMP_TYPE_ECHO_REPLY == (ICMP_TYPE_ENUM_UINT8)ucIcmpType)
                || (ICMP_TYPE_ECHO_REQUEST == (ICMP_TYPE_ENUM_UINT8)ucIcmpType))
            {
                pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIcmpId  = PPPC_GET_HIGH_16_BITS(ulIcmpOtherHd);
                pstUlDataInfo->stHighLayerInfo.u.stIcmpv4Info.usIcmpSn  = PPPC_GET_LOW_16_BITS(ulIcmpOtherHd);
            }
            break;
        case PS_DATA_HIGH_LAYER_ICMPV6_TYPE:
            ucIcmpType    = ((PPP_TRACE_ICMP_STRU *)(pucPppData + ucIpHdLen))->ucType;

            pstUlDataInfo->stHighLayerInfo.u.stIcmpv6Info.ucType        = ucIcmpType;
            pstUlDataInfo->stHighLayerInfo.u.stIcmpv6Info.usDataLen     = VOS_NTOHS(pstIp->ip_usLen);
            break;
        case PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usIpId     = VOS_NTOHS(pstIp->ip_usId);
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usDataLen  = VOS_NTOHS(pstIp->ip_usLen);
            break;
        case PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE:
            pstUlDataInfo->stHighLayerInfo.u.stIpv4OtherTypeInfo.usDataLen  = VOS_NTOHS(pstIp->ip_usLen);
            break;
        default:
            PPPC_WARNING_LOG1("wrong protocol for ppp ul trace", ulProtocol);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : FWD_PppParse
 ��������  : ���²���������PPPͷ�ĳ���
 �������  : VOS_UINT8 *pcuPppHead   PPPͷ
 �������  : VOS_UINT32 *pulHdLen    PPPͷ�ĳ���
 �� �� ֵ  : PPP_IS_DATA    :    ���ݱ���
             PPP_IS_LCP_ECHO:    ECHO����
             PPP_IS_LCP_SIG :    Э�̱���
             PPP_IS_ASYN    :    �첽����
             PPP_IS_OTHER_SIG  :   ���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��29��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppParse
(
    VOS_UINT8                          *pcuPppHead,
    VOS_UINT32                         *pulHdLen,
    FWD_PKT_TYPE_ENUM_UINT8            *penIpVersion
)
{
    VOS_UINT16 usPppHdFlg=0;
    VOS_UINT32 ulPPPHLen = 0;
    VOS_UINT32 ret = 0;
    *pulHdLen=0;
    /* ͬ�첽��� */
    if (PPP_H_ASYN == (*pcuPppHead))
    {
        return (PPP_PARSE_R_ASYN);
    }

    /*��ַ�������ж�,����һ�ֽڶ��뷽ʽ��,*/
    usPppHdFlg = pcuPppHead[0];
    usPppHdFlg = (PF_USHORT)((usPppHdFlg << 8)|(PF_USHORT)pcuPppHead[1]);
    if ( PPP_H_ACF ==  usPppHdFlg)
    {
        ulPPPHLen +=2;
        usPppHdFlg = pcuPppHead[ulPPPHLen+0];
        usPppHdFlg = (PF_USHORT)((usPppHdFlg << 8)|(PF_USHORT)pcuPppHead[ulPPPHLen+1]);
    }

    /*Э�����ж�*/
    /*Modified Start by lijun 00129916 2010-03-02 for AX4D13910 �޸�PPP��������*/
    /*���ݱ��ģ�Э������ѹ��*/
    if ((PPP_H_PF_IPV4 == usPppHdFlg) ||(PPP_H_PF_IPV6 == usPppHdFlg))
    {
        *penIpVersion = (PPP_H_PF_IPV4 == usPppHdFlg) ? FWD_PKT_TYPE_IPV4 : FWD_PKT_TYPE_IPV6;
        ulPPPHLen +=2;
        ret = PPP_PARSE_R_DATA;
    }
    /*���ݱ��ġ�Э����ѹ��*/
    else if ((PPP_H_PFC_IPV4 == (PF_UCHAR)(usPppHdFlg >> 8)) ||(PPP_H_PFC_IPV6 == (PF_UCHAR)(usPppHdFlg >> 8)))
    {
        *penIpVersion = (PPP_H_PFC_IPV4 == (PF_UCHAR)(usPppHdFlg >> 8)) ? FWD_PKT_TYPE_IPV4 : FWD_PKT_TYPE_IPV6;
        ulPPPHLen +=1;
        ret = PPP_PARSE_R_DATA;
    }
    /*LCP����*/
    else if (PPP_H_PF_LCP == usPppHdFlg)
    {
        PF_UCHAR *pucLcpData = VOS_NULL_PTR;
        PF_UCHAR ucLcpCode=0;
        ulPPPHLen +=2;
        pucLcpData = pcuPppHead + ulPPPHLen;
        ucLcpCode =  GET_CODE_FROM_LCP_PKT(pucLcpData);

        if (PPP_H_LCP_ECHOREQ == ucLcpCode)
        {
            ret = PPP_PARSE_R_LCP_ECHO_REQ;
        }
        /* begin: add by zhangnan 68158 at 2012-02-21 for PPP Echo �����޷����� */
        else if (PPP_H_LCP_ECHOREP == ucLcpCode)
        {
            ret = PPP_PARSE_R_LCP_ECHO_REPLY;
        }
        /* end  :add by zhangnan 68158 at 2012-02-21 for PPP Echo �����޷����� */
        else /*ucCode !=0X09 */
        {
            ret = PPP_PARSE_R_LCP_SIG;
        }
    }
    /*Added start by wangyixing 00167384 at 2013-2-4 for HSGW����*/
    else if (PPP_H_PF_VSNP == usPppHdFlg)
    {
        /*ƫ�Ƶ�Э��,Э������ѹ��*/
        ulPPPHLen +=2;
        ret = PPP_PARSE_R_VSCP_DATA;
    }
    else if(PPP_H_PF_VSNP == (PF_UCHAR)(usPppHdFlg >> 8))
    {
        /*ƫ�Ƶ�Э��,Э����ѹ��*/
        ulPPPHLen +=1;
        ret = PPP_PARSE_R_VSCP_DATA;
    }
    /*Added end by wangyixing 00167384 at 2013-2-4 for HSGW����*/
    else
    {
        /*Modified by t00127644 for DTS2010073002901
        Э������жϵ�һ���ֽڸ�4bit�Ƿ�>=8,���>=,����Ϊ�������,����PPP,������Ϊ���ķǷ�,����*/
        if(((usPppHdFlg>>12)&0xf)>= 8)
        {
            ret = PPP_PARSE_R_OTHER_SIG;
        }
        else
        {
            ret = PPP_PARSE_R_ERR_SIG;
        }
    }
    *pulHdLen = ulPPPHLen;
    return ret;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetLcpMagicNum
 ��������  : ��ȡ����ħ����
 �������  : ��

 �������  : pulPppMagicNum    ħ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetLcpMagicNum(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppMagicNum)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* �ڲ����ã���֤��ηǿ� */
    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_908);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG("LCP is Null!");
        PPP_DBG_ERR_CNT(PPP_PHERR_857);
        return VOS_ERR;
    }

    *pulPppMagicNum = pstLcpInfo->stGotOptions.magicnumber;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppDecap
 ��������  : PPP���Ľ��װ
 �������  : pstMBuf        PPP����
             enPktType      ��������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID FWD_PppDecap
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    VOS_UINT8                          *pucPppData;
    VOS_UINT8                          *pucLcpData ;
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulLcpMagicNum = 0;
    VOS_UINT32                          ulPPPType;
    VOS_UINT32                          lHdLen = 0;
    VOS_UINT32                          ulMagicNum;
    VOS_UINT32                          ulRet;
    PMBUF_S                            *pstSynMBuf = VOS_NULL_PTR;
    PMBUF_S                            *pstMBuf = VOS_NULL_PTR;
    FWD_PKT_TYPE_ENUM_UINT8             enIpVersion;
    PPPINFO_S                          *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucMinBody = 8;  /* LCP������С����Ϊ8 */
    VOS_UINT16                          usLcpLen = 0;

    /* �Խ��װ��PPP �� ���� */
    PPP_DBG_OK_CNT(PPP_PHOK_1478);

    pucPppData  = pstData->pData;

    ulPPPType = FWD_PppParse( pucPppData, &lHdLen, &enIpVersion);

    PPPC_INFO_LOG3("FWD_PppDecap : lHdLen:0x%x, ulPPPType:0x%x\n", lHdLen, ulPPPType,ucPppId);

    switch (ulPPPType)
    {
        case PPP_PARSE_R_ASYN:

            PPP_DBG_ERR_CNT(PPP_PHERR_839);

            break;

        case PPP_PARSE_R_DATA:
            TTF_MEM_REMOVE_FROM_HDR(pstData, (VOS_UINT16)lHdLen);

            ulRet = PPPC_1XHrpdGetPdnId((VOS_UINT16)ucPppId, &ucPdnId);
            if (VOS_OK == ulRet)
            {
                PPP_SendRlpDlDatatoCds(usStartSeq, usEndSeq, ucPdnId, pstData, ucRatMode);
            }
            else
            {
                TTF_MemFree(MSPS_PID_PPPC,pstData);
                pstData = VOS_NULL_PTR;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1479);
            break;

        case PPP_PARSE_R_VSCP_DATA:


            /* ��ȡPDN ID */
            ucPdnId = pucPppData[lHdLen];
            lHdLen++;
            TTF_MEM_REMOVE_FROM_HDR(pstData, (VOS_UINT16)lHdLen);

            PPP_SendRlpDlDatatoCds(usStartSeq, usEndSeq, ucPdnId, pstData, ucRatMode);
            break;

        case PPP_PARSE_R_LCP_ECHO_REQ:

            pucLcpData = pucPppData + lHdLen;

            GET_LENGTH_FROM_LCP_PKT(pucLcpData, usLcpLen);
            if (usLcpLen < ucMinBody)
            {
                PPPC_WARNING_LOG1("Lcp Echo Req Len Error", usLcpLen);
                return;
            }

            /*����ĺ��ڶ�ȡMagicNumberʱ�Ѿ������������������ת�� */
            GET_MAGICNUM_FROM_LCP_PKT(pucLcpData,ulLcpMagicNum);
            ulRet   = FWD_PppGetLcpMagicNum(ucPppId, &ulMagicNum);
            if (VOS_OK != ulRet)
            {
                TTF_MemFree(MSPS_PID_PPPC,pstData);
                pstData = VOS_NULL_PTR;
                PPP_DBG_ERR_CNT(PPP_PHERR_840);
                (VOS_VOID)pstData;
                return;
            }

            /*�޸�ԭ����ΪECHO_REPLY ����*/
            pucLcpData[LCP_MAGICNUM_OFFSET+3] = (PF_UCHAR)(ulMagicNum & 0X000000FFL);
            pucLcpData[LCP_MAGICNUM_OFFSET+2] = (PF_UCHAR)((ulMagicNum & 0X0000FF00L)>>8);
            pucLcpData[LCP_MAGICNUM_OFFSET+1] = (PF_UCHAR)((ulMagicNum & 0X00FF0000L)>>16);
            pucLcpData[LCP_MAGICNUM_OFFSET+0] = (PF_UCHAR)((ulMagicNum & 0XFF000000L)>>24);
            pucLcpData[LCP_CODE_OFFSET] = PPP_H_LCP_ECHOREP;

            /* ��ȡPPPC���ƿ�ָ��*/
            GETPPPINFOPTRBYRP(pstPppInfo, ucPppId);
            /* for pclint */
            if(VOS_NULL_PTR == pstPppInfo)
            {
                TTF_MemFree(MSPS_PID_PPPC, pstData);
                return ;
            }
            pstMBuf = PPPC_AdapterTtfMemorytoMBuf(pstData);
            /* ͬ/�첽ת�� */
            if (pstPppInfo->bSynAsyConvert)
            {
                pstMBuf = PPP_SynToAsy(pstMBuf, 0xffffffff);
                if (pstMBuf == VOS_NULL_PTR)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_836);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Echo Reply Syn To Asy Error!!");
                    return;
                }
            }
            /* ���ͱ��� */
            ulRet = PPPC_ULSendNegoFrame(pstMBuf, pstPppInfo->ulRPIndex);
            if (VOS_ERR == ulRet)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_837);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Send Echo Reply Fail!!");
                return;
            }
            (VOS_VOID)ulLcpMagicNum;
            return;

        case PPP_PARSE_R_LCP_ECHO_REPLY:
        case PPP_PARSE_R_LCP_SIG:
        case PPP_PARSE_R_OTHER_SIG:
            pstSynMBuf = PPPC_AdapterTtfMemorytoMBuf(pstData);
            PPP_Shell_ReceiveNegoPacket(pstSynMBuf, ucPppId);
            PMBUF_Destroy(pstSynMBuf);
            pstSynMBuf = VOS_NULL_PTR;
            break;

        default:

            PPP_DBG_ERR_CNT(PPP_PHERR_858);
            break;
    }
    (VOS_VOID)pstData;
    (VOS_VOID)pstSynMBuf;
    return;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetWantLcpFcFlag
 ��������  : ��ȡЭ�̵�Э��ѹ����
 �������  : ��

 �������  : pulPppFcFlag    Э��ѹ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetWantLcpFcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppFcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;

    /* �ڲ����ã���֤��ηǿ� */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_905);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_859);
        return VOS_ERR;
    }

    *pulPppFcFlag = pstLcpInfo->stWantOptions.neg_pcompression;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetWantLcpAcfcFlag
 ��������  : ��ȡЭ�̵ĵ�ַѹ����
 �������  : ��

 �������  : pulPppAcfcFlag   ��ַѹ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetWantLcpAcfcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppAcfcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* �ڲ����ã���֤��ηǿ� */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_906);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Ac Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_860);
        return VOS_ERR;
    }

    *pulPppAcfcFlag = pstLcpInfo->stWantOptions.neg_accompression;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetHisLcpFcFlag
 ��������  : ��ȡЭ�̵�Э��ѹ����
 �������  : ��

 �������  : pulPppFcFlag    Э��ѹ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisLcpFcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppFcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;

    /* �ڲ����ã���֤��ηǿ� */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_905);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Fc Flag Fail!%d\r\n",ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_859);
        return VOS_ERR;
    }

    *pulPppFcFlag = pstLcpInfo->stHisOptions.neg_pcompression;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetHisLcpAcfcFlag
 ��������  : ��ȡЭ�̵ĵ�ַѹ����
 �������  : ��

 �������  : pulPppAcfcFlag   ��ַѹ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisLcpAcfcFlag(VOS_UINT8 ucPppId, VOS_UINT32  *pulPppAcfcFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* �ڲ����ã���֤��ηǿ� */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_906);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp Ac Fc Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_860);
        return VOS_ERR;
    }

    *pulPppAcfcFlag = pstLcpInfo->stHisOptions.neg_accompression;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppGetHisAccm
 ��������  : ��ȡ�Զ˿����ַ�ӳ����
 �������  : ��

 �������  : pulAccmFlag   ��ַѹ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��29��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FWD_PppGetHisAccm(VOS_UINT8 ucPppId, VOS_UINT32  *pulAccmFlag)
{
    PPPLCPINFO_S                       *pstLcpInfo;


    /* �ڲ����ã���֤��ηǿ� */

    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("PPP ID is invlid\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_910);
        return VOS_ERR;
    }

    pstLcpInfo   = (PPPLCPINFO_S*)g_astPppPool[ucPppId].pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_WARNING_LOG1("LCP is Null, Get Lcp ACCM Flag Fail!%d\r\n", ucPppId);
        PPP_DBG_ERR_CNT(PPP_PHERR_911);
        return VOS_ERR;
    }

    *pulAccmFlag = pstLcpInfo->stHisOptions.asyncmap;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FWD_PppEncap
 ��������  : ��װPPP����ͷ
 �������  : ucPdnId        ���غ�
             pstMBuf        PPP����
             enPktType      ��������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 FWD_PppEncap
(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucCdsData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          ulAccmValue,
    VOS_UINT32                         *pulAsynLen
)
{
    VOS_UINT8                          *pucPppData;
    IP4_S                              *pstIP;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           ucIpVer;
    VOS_UINT8                           ucPppProto;
    VOS_UINT32                          ulPppFcFlag;
    VOS_UINT32                          ulPppAcfcFlag;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSduLen = 0;
    VOS_UINT8                          *pucHeadPtr;

    /* 1X��HRPDͷ���������Ϊ4���ֽ�ff030021,eHRPDͷ���5���ֽ�ff03005bxx(pdn id) */
    VOS_UINT8                           aucHeadData[8];
    /* ��¼ͷ������ */
    VOS_UINT16                          usFrameLen = 0;


    /* ����ָ��Ϊ�ջ������ݳ���Ϊ0ֱ���˳�,�����ͷ��ڴ� */
    if ((VOS_NULL_PTR == pucCdsData) || (0 == usDataLen) || (usDataLen > PPPC_MAX_FRAME_LEN))
    {
        PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", usDataLen);
        return VOS_ERR;
    }

    PS_MEM_SET(aucHeadData, 0, sizeof(aucHeadData));
    pucHeadPtr = &(aucHeadData[0]);

    pucPppData = pucCdsData;

    /*
    ��PPP��װ��������������� :
    1.����GTP��L2TP֮��,��ʱ�ռ乻��
    2.��ͨ���б��ģ���PPP��װ��(����PPP�ս�),����ʱ��ppp��װ,��װͷ�����Ԥ����512�ֽ���
     ���ǵ�Ч��,���ﲻ�����,��һ����װGTPʱ�������
    */

    ulRet = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_907);
        return VOS_ERR;
    }

    ulRet   = FWD_PppGetHisLcpAcfcFlag(ucPppId, &ulPppAcfcFlag);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_861);
        return VOS_ERR;
    }

    ulRet   = FWD_PppGetHisLcpFcFlag(ucPppId, &ulPppFcFlag);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_862);
        return VOS_ERR;
    }

    /*����ַ������*/
    if (PPP_ACFC_0 == ulPppAcfcFlag)
    {
        *pucHeadPtr     = 0xff;
        pucHeadPtr++;
        *pucHeadPtr     = 0x03;
        pucHeadPtr++;
        usFrameLen     += 2;
    }

    /* ���ж�Э�����Ƿ�ѹ��,�����ѹ��,Э�����һ���ֽ���0,�ڶ����ֽ��ں������,
       ֮���Խ�Э�������д����ΪeHRPD������Э������IPv4��IPv6����VSNP,�Һ���
       ��Ҫ��һ���ֽڵ�PDN ID */
    if(PPP_PFC_1 != ulPppFcFlag)
    {
        *pucHeadPtr     = 0;
        pucHeadPtr++;
        usFrameLen     += 1;
    }

    /*���Э����*/
    if (PPPC_RAT_MODE_EHRPD == PPPC_GetRatMode())
    {
        ucPppProto      = PPP_H_PFC_VSNP;
        *pucHeadPtr     = ucPppProto;
        pucHeadPtr++;
        *pucHeadPtr     = ucPdnId;
        pucHeadPtr++;
        usFrameLen += 2;
    }
    else
    {
        pstIP = (IP4_S *)pucPppData;
        ucIpVer = pstIP->ip_chVer;
        (IPV4_VERSION == ucIpVer)?(ucPppProto = PPP_H_PFC_IPV4):(ucPppProto = PPP_H_PFC_IPV6);
        *pucHeadPtr = ucPppProto;
        pucHeadPtr++;
        usFrameLen += 1;
    }

    /* ͬ��ת�첽 */
    ulSduLen = PPP_UlDataSynToAsy(aucHeadData, usFrameLen, pucCdsData, usDataLen, ulAccmValue);
    *pulAsynLen = ulSduLen;

    (VOS_VOID)pucHeadPtr;
    return VOS_OK;
}

/******************************************************************************
�� �� ��  : FWD_PppRebuildIncompleteSliceStatInit
��������  : ��g_stPppRebuildIncompleteSliceStat���
�������  :

�������  : NA
ȫ�ֱ���  : NA
�� �� ֵ  : NA
���ú���  : NA
��������  : NA

�޸���ʷ      :
1.��    ��   : ������ 2015��8��28��
��    ��   : zWX297122
�޸�����   : �����ɺ���

******************************************************************************/
VOS_VOID FWD_PppRebuildIncompleteSliceStatInit()
{
    PS_MEM_SET(&g_stPppRebuildIncompleteSliceStat, 0, sizeof(g_stPppRebuildIncompleteSliceStat));
}

/******************************************************************************
�� �� ��  : FWD_PppRebuildIgnoreContinuousSeqFlag
��������  : PPP��Ƭ��������7E
�������  :
            VOS_UINT8                      *pData,
            VOS_UINT16                      usUsed,
            TTF_MEM_ST                     *pstData,
            VOS_UINT32                     *ulSeqOffsetToModify
�������  : NA
ȫ�ֱ���  : NA
�� �� ֵ  : NA
���ú���  : NA
��������  : NA

�޸���ʷ      :
1.��    ��   : ������ 2015��8��13��
��    ��   : zWX297122
�޸�����   : �����ɺ���

******************************************************************************/
VOS_VOID FWD_PppRebuildIgnoreContinuousSeqFlag
(
    VOS_UINT8                      *pData,
    VOS_UINT16                      usUsed,
    VOS_UINT32                     *ulSeqOffsetToModify
)
{
    VOS_UINT32                      ulSeqOffset = *ulSeqOffsetToModify;


    /* ��������7E  ������*/
    while ((ulSeqOffset < usUsed) && (PPP_FLAG_SEQ == pData[ulSeqOffset]))
    {
        ulSeqOffset++;
    }

    if(ulSeqOffset >= usUsed)
    {
        g_stPppRebuildIncompleteSliceStat.usLastByteSeq = 1;
    }
    else
    {
        g_stPppRebuildIncompleteSliceStat.usLastByteSeq = 0;
    }

    *ulSeqOffsetToModify = ulSeqOffset;

}

/******************************************************************************
 �� �� ��  : FWD_PppRebuild
 ��������  : PPP��Ƭ�������鴦��
             ���pstData�Ѿ�ƫ�Ƶ���PPPͷ
             �����ͷ�pstData
 �������  :
            VOS_UINT16                          usSeqNr,
            TTF_MEM_ST                         *pstData,
            PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
 �������  : NA
 ȫ�ֱ���  : NA
 �� �� ֵ  :
 ���ú���  : NA
 ��������  : NA

 �޸���ʷ      :
  1.��    ��   : ������ 2015��8��13��
    ��    ��   : zWX297122
    �޸�����   : �����ɺ���

******************************************************************************/
VOS_VOID FWD_PppRebuild
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    VOS_UINT8                          *pData = pstData->pData;
    VOS_UINT16                          usUsed = pstData->usUsed;
    PPP_REBUILD_INCOMPLETE_SLICE_STRU  *pstPppCurRebuildStat = &g_stPppRebuildIncompleteSliceStat;
    VOS_UINT32                          ulSeqOffset = 0;
    VOS_UINT8                           ucThisByteSeq;
    VOS_UINT8                           ucHasStartSeq;
    TTF_MEM_ST                         *pstTtfMem;


    /* ��Byte�����Ƭ */
    while (ulSeqOffset < usUsed)
    {
        ucThisByteSeq = (pData[ulSeqOffset] == PPP_FLAG_SEQ);
        ucHasStartSeq = (pstPppCurRebuildStat->usHasStartFlag == 1);

        if (ucThisByteSeq && !ucHasStartSeq)
        {
            pstPppCurRebuildStat->usHasStartFlag = 1;
            pstPppCurRebuildStat->usStartSeq = usSeqNr;
            ulSeqOffset++;
        }
        else if (!ucThisByteSeq && !ucHasStartSeq)
        {
            ulSeqOffset++;
        }
        else if (!ucThisByteSeq && ucHasStartSeq)
        {
            pstPppCurRebuildStat->usLastByteSeq = 0;
            PPP_AsyToSyn(pData[ulSeqOffset]);
            ulSeqOffset++;
        }
        else
        {
            if(pstPppCurRebuildStat->usLastByteSeq == 1)
            {
                FWD_PppRebuildIgnoreContinuousSeqFlag(pData, usUsed, &ulSeqOffset);
                pstPppCurRebuildStat->usStartSeq= usSeqNr;
            }
            else
            {
                pstPppCurRebuildStat->usEndSeq = usSeqNr;
                if(1 == PPP_AsyToSyn(pData[ulSeqOffset]))
                {
                    pstTtfMem = TTF_MemBlkCopyAlloc(MSPS_PID_PPPC,
                                    TTF_MEM_POOL_ID_DL_PDU, g_aucPppRebuildSynSliceBuffer, g_usPppSynSliceBufUsedLen);
                    if (VOS_NULL_PTR == pstTtfMem)
                    {
                        return;
                    }
                    FWD_PppDecap(pstPppCurRebuildStat->usStartSeq, pstPppCurRebuildStat->usEndSeq, pstTtfMem, ucRatMode, ucPppId);
                }
                g_usPppSynSliceBufUsedLen = 0;
                FWD_PppRebuildIgnoreContinuousSeqFlag(pData, usUsed, &ulSeqOffset);
            }
        }

    }
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
